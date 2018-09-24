#define _MEDIA_USER_FUNC_C_
#include "..\config\inc.h"

#if _COMPILER_ == _IAR_EWV850_
__no_init uint8_t l_cIapType @ 0xffffA000;
#else
#pragma section data "iap_share_ram" begin
uint8_t  l_cIapType;   //共享内存，暂时起不到作用
#pragma section data "iap_share_ram" end
#endif

TouchInfoStruct	ApuTouchInfo;

/*通讯协议增加一条APU发到MCU的命令(GID = B0，SID = 0X03)
APU发送此命令时，MCU返回APU定死的数据，方便APU前期确认
自己的代码。
*/
void Mcu_Send_ApuDebugData(uint8_t* buf,uint8_t len)
{
	uint8_t sendBuf[255],i;
	uint16_t cCRC = 0;
       uint8_t cLen = len; 

       cLen += 8;
       sendBuf[TBBID_SDEV] = D_MCU_DEV_ID;
       sendBuf[TBBID_RDEV] = D_APU_DEV_ID;
       sendBuf[TBBID_PID]  = 0;
       sendBuf[TBBID_GID]  = buf[0];
       sendBuf[TBBID_PKG_LEN] = cLen;
       sendBuf[TBBID_CHKS1] = 0x00;
       sendBuf[TBBID_CHKS2] = 0x00;
       sendBuf[TBBID_SID] = buf[1];
	   
	for(i = 0 ; i < len ; i++)
	{
		sendBuf[TBBID_DATA+i] = buf[i+2];   
	}
   
       cCRC = OS_CalCrc16(&sendBuf[TBBID_PID], cLen-2);
      
       sendBuf[TBBID_CHKS1] = cCRC&0xff;
       sendBuf[TBBID_CHKS2] = (cCRC>>8)&0xff;
	   
	v850_uart3_Send(sendBuf,cLen);
	
}


void MDI_RxCmd(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
    if( SID_MCU_RX_COMMAND== cSid)
    {
        _SendFullMsgToHMI(MS_INPUT_UI,p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3],cLen);
	 media_printf(_T("RxCmd: %x-%x\n",p_cRxdata[0],p_cRxdata[1]));
    }
    else if(SID_MCU_RX_REQPACKAGE == cSid)
    {
	_SendFullMsgToHMI(MS_INPUT_REQDATA,p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3],cLen);
	media_printf(_T("Request Package: %x-%x\n",p_cRxdata[0],p_cRxdata[1]));
    }
    else if(SID_MCU_RX_APU_DEBUG_DATA == cSid)	// bolte
    {
    	Mcu_Send_ApuDebugData(p_cRxdata,cLen-2);
    }
}

void MDI_RxSysInfo(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
    if(cSid == SID_MCU_RX_OS_TYPE)
    {
        g_tApuDevState.eUiOSType = p_cRxdata[0]%UI_OS_N;
        OS_CreateRamChkBlock((void*)&g_tApuDevState,(sizeof(tAPU_DEV_BLOCK)-2),(void*)(&(g_tApuDevState.iCheckSum)));
    }
    else if(cSid == SID_MCU_RX_OS_STATUS)
    {
        uint8_t Op = OP_DEV_STATE_N;
	 media_printf(_T("OS State:%d-%x\n",cSid,p_cRxdata[0]));
        switch(p_cRxdata[0])
        {
            case APU_LINKREQ:
			Op = OP_DEV_STATE_LINKREQ;
	     		break;
	     case APU_SYS_ENTER:
			Op = OP_DEV_STATE_ENTER;
			media_printf(_T("---APU_SYS_ENTER----\n"));
		 	break;
            case APU_UPDATA_START:
                	Op = OP_DEV_STATE_UPDATA;
            		break;
            case APU_OS_READY:
					
                	Op = OP_DEV_STATE_CONNECTED;
                	break;
            case APU_POWER_OFF_READY:
                	Op = OP_DEV_STATE_SLEEP_READY;
                	break;
            case APU_REQ_UPDATA:
            case APU_UPDATA_END:
                	Op = OP_DEV_STATE_RESET;
            		break; 
            case APU_SYSTEM_LOCK:
                	Op = OP_DEV_STATE_LOCK;
            		break;
            case APU_SYSTEM_UNLOCK:
                	Op = OP_DEV_STATE_NORMAL;
            		break;
	     case APU_TEST_MODE:
		 	Op = OP_DEV_STATE_TEST;
		 	break;
	     case APU_BOOT_OK:
		   	Op = OP_DEV_STATE_BOOTOK;
	     		break;
	     case APU_WARN_MENU_ON:		//APU enter "WARN MENU"
		 	Op = OP_DEV_STATE_POWERON;
		 	break;
	     default:
		 	break;
        }

        if(Op < OP_DEV_STATE_N)
        {
            _SendMsgToMedia(MS_SYS_APU_INFO,Op,NULL);
        }
    }
    else if(cSid == SID_MCU_RX_TOUCH_DATA)
    {
		//Touch information Deal.
		if(cLen >=5)
		{
			ApuTouchInfo.PixX = (p_cRxdata[1]<<8)|p_cRxdata[0];
			ApuTouchInfo.PixY = (p_cRxdata[3]<<8)|p_cRxdata[2];
			ApuTouchInfo.State = p_cRxdata[4];		
			//media_printf(_T("X=%ldY=%ldS=%ld\n",ApuTouchInfo.PixX, ApuTouchInfo.PixY,ApuTouchInfo.State));
			//_SendMsgToSRC(MS_INPUT_TOUCH, 0x00, &ApuTouchInfo);
			SendCoordinateToBus();
		}
    }
}

void MDI_RxSeting(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
#define _ptr p_cRxdata

	if(cSid == SID_MCU_RX_SET_VEHICLE)
	{
		CANTask_VehicleMsgHandler(p_cRxdata);	
	}
	else
	{
		_SendFullMsgToHMI(MS_UI_SETTING,cSid,_ptr[0],_ptr[1],_ptr[2],_ptr[3]);
		media_printf(_T("RxSeting: %x-%x-%x-%x\n",p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3]));
	}

#undef _ptr
}

uint8_t TimeArray[10]={0};
void MDI_RxRTC(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
	tRTC_BLOCK tTmp;
    media_printf(_T("MDI_RxRTC %x\n",cSid));
    media_printf(_T("%x:%x:%x,%x\n",p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3]));
    switch(cSid)
    {
        case SID_MCU_RX_TIME_BASE:
        {
            uint32_t lSec = 0;
            uint32_t temp = p_cRxdata[3];
            lSec += temp<<24;
            temp = p_cRxdata[2];
            lSec += temp<<16;
            temp = p_cRxdata[1];
            lSec += temp<<8;
            temp = p_cRxdata[0];
            lSec += temp;
	      l_tMediaCB.cSysTimeSendCnt = 0;	
		  l_tMediaCB.SendTimeCnt = 0;
            OS_SetWatchSecond(lSec);
        }
        break;
        
        case SID_MCU_RX_DATE:
            TimeArray[0] = p_cRxdata[0];
            TimeArray[1] = p_cRxdata[1];
            TimeArray[2] = p_cRxdata[2];
            TimeArray[3] = p_cRxdata[3];
			//CANUser_SystemTime(TimeArray, 0);
        break;

        case SID_MCU_RX_GPS_TIME:
        {
            tTmp.cHour = p_cRxdata[0];
            tTmp.cMin= p_cRxdata[1];
            tTmp.cSec= p_cRxdata[2];
            TimeArray[4] = p_cRxdata[0];
           TimeArray[5]= p_cRxdata[1];
           TimeArray[6]= p_cRxdata[2];
            OS_SetRTC(&tTmp);
        }
        break;
    }
}

void MDI_RxMediaInfo(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
	#ifdef CAN_INNER_ENABLE
	    switch(cSid)
	    {
	     case SID_MCU_RX_PLAY_TITLE:
	        CANbus_InnerWriteMediaTitle(p_cRxdata);
	        break;
	    case SID_MCU_RX_PLAY_TIME:
	        CANbus_InnerWritePlayTime(p_cRxdata);
	        break;
	    case SID_MCU_RX_PLAY_INFO:
	        CANbus_InnerWritePlayInfo(p_cRxdata);
	        break;
	    default:
	        break;
	    }
	#endif
}
#define D_EOL_DEBUG
void MDI_RxCanInfo(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
	uint8_t buffer[3];
	EOLCfgStruct *pEOLCfg=pCAN_GetEOLStr();
	buffer[0] = cLen+2;
	buffer[1] = GID_MCU_RX_CAN_CTL;
	buffer[2] = cSid;
	switch(cSid)
	{
		case SID_MCU_RX_NAVI_CMD:
			CANTask_NAVIMsgHandler(p_cRxdata);
			break;
		case SID_MCU_RX_DTV_CMD:
			CANTask_DTVMsgHandler(p_cRxdata);
			break;
		case SID_MCU_RX_EOL_CMD:
			#ifdef D_EOL_DEBUG
			media_printf(_T("Data Old:%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n",p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3],
				p_cRxdata[4],p_cRxdata[5],p_cRxdata[6],p_cRxdata[7],p_cRxdata[8],p_cRxdata[9],p_cRxdata[10],
				p_cRxdata[11],p_cRxdata[12],p_cRxdata[13],p_cRxdata[14],p_cRxdata[15]));
			#endif
			
			Memory8Copy(pEOLCfg->EOLState.Param, p_cRxdata, 16);

			p_cRxdata[0] = (pEOLCfg->EOLState.bits.GWSupport<<7) | (pEOLCfg->EOLState.bits.GPSAntSupport<<6) | (pEOLCfg->EOLState.bits.WIFIAntSupport<<5) |
				(pEOLCfg->EOLState.bits.RRSSupport<<4) | (pEOLCfg->EOLState.bits.AUXSupport<<3) | ((pEOLCfg->EOLState.bits.PACSupport-1)<<2) |
				(pEOLCfg->EOLState.bits.TPMSSupport<<1) | pEOLCfg->EOLState.bits.DVRSupport;
			p_cRxdata[1] = 0x00;
			p_cRxdata[2] = 0x00;
			p_cRxdata[3] = 0x00;
			p_cRxdata[4] = 0x00;
			p_cRxdata[5] = 0x00;

			#ifdef D_EOL_DEBUG
			media_printf(_T("Data New:%x %x %x %x %x %x\n",p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3],p_cRxdata[4],p_cRxdata[5]));
			media_printf(_T("-----DVR:%x TPMS:%x PAC:%x AUX:%x RRS:%x WIFI:%x GPS:%x GW:%x \n",pEOLCfg->EOLState.bits.DVRSupport,pEOLCfg->EOLState.bits.TPMSSupport,pEOLCfg->EOLState.bits.PACSupport,
				pEOLCfg->EOLState.bits.AUXSupport,pEOLCfg->EOLState.bits.RRSSupport,pEOLCfg->EOLState.bits.WIFIAntSupport,pEOLCfg->EOLState.bits.GPSAntSupport,pEOLCfg->EOLState.bits.GWSupport));
			#endif
			
			CANTask_EOLMsgHandler(p_cRxdata);
			break;
		case SID_MCU_RX_UIKEY_CMD:
			break;
		case SID_MCU_RX_Latitude_CMD:
			CANUser_SetLatitude(p_cRxdata, 0);
			break;
		case SID_MCU_RX_NAVI_SPEED_LIMIT_CMD:	
			CANUser_SetNaviSpeedLimit(p_cRxdata,0);
			break;
		case SID_MCU_RX_MAINTAIN_DATA_CMD:	
			CANUser_SetMaintainData(p_cRxdata,0);
			break;
		case SID_MCU_RX_DATA_TIME_CMD:
			CANUser_SystemTime(p_cRxdata,0);
			//media_printf(_T("%d-%d-%d  %d:%d:%d\n",p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3],p_cRxdata[4],p_cRxdata[5]));
			//media_printf(_T("Data:%x %x %x %x %x %x %x %x\n",p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3],p_cRxdata[4],p_cRxdata[5]));
			break;
		default:
			break;
	}
}

void MDI_RxDeviceInfo(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
    union {
        uint8_t byte[2];
        uint16_t word;
    }uWord;
    if(cSid == SID_MCU_RX_DEVICESTATUS)
    {
	    uWord.byte[0] = p_cRxdata[0];
	    uWord.byte[1] = p_cRxdata[1];
	    _SendMsgToHMI(MS_SYS_DEV_ON_APU_INFO,uWord.word,NULL);
	    
	    media_printf(_T("DEV State:%x%x\n", p_cRxdata[0],p_cRxdata[1]));
    }
}


void MDI_RxSwcInfo(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
    switch(cSid)
    {
        case SID_MCU_RX_SWC_RUNMODE:
            _SendMsgToHMI(MS_HMI_SWC_SETTING,OP_SWC_SET_MODE,p_cRxdata[0]);
        break;

        case SID_MCU_RX_SWC_KEYCODE:
            _SendMsgToHMI(MS_HMI_SWC_SETTING,OP_SWC_SET_UICC,p_cRxdata[0]);
        break;
    }
}


void MDI_RxProjectInfo(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
	uint8_t i;
	media_printf(_T("MDI_RxProjectInfo:sid=%d  ",cSid));
	for(i=0;i<cLen;i++)
	{
		media_printf(_T("p_cRxdata[%d]=%x  ",i,p_cRxdata[i]));
	}
	media_printf(_T("\n"));
	switch(cSid)
	{
		case CAN_PRJ_ID_CHANA_S401:
			media_printf(_T("===CAN_PRJ_ID_CHANA_S401===\n"));
			CANTask_RxBusDataDeal(cSid,  p_cRxdata,  cLen);
			break;
		case CAN_PRJ_ID_CHANA_R103H://snake20160831
			media_printf(_T("===CAN_PRJ_ID_CHANA_R103H===\n"));
			CANTask_RxBusDataDeal(cSid,  p_cRxdata,  cLen);
			break;
		default:
			break;
	}

}


void MDI_RxMcuUpdata(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
    if((uint8_t)OP_LOAD_MCU_UPDATECMD == cSid)
    {
        //仅仅用于欺骗编译器,防止共享变量因未使用而优化掉
        
        l_cIapType = 0; //欺骗编译器
        if(l_cIapType != p_cRxdata[0])
        {
            DI();
            l_cIapType = p_cRxdata[0];
            /*Clear all SRAM data*/
            OS_ClearNoInitBlock();
            //Front System
            IO_Set(IO_IDX_APU_BCK_POWER,PIN_OUTPUT,INVALID);
            //Rear System
            API_LoopDleay(60000);API_LoopDleay(60000);
            IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
            IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
            IO_Set(IO_IDX_TFT_EN_IO,PIN_OUTPUT,ON);
            OS_Init();
        }
    }
}
void MDI_Rx8836Updata(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
       uint8_t i;
	switch(cSid)
	{
          case SID_MCU_RX_8836_UPDATECMD:
		  _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_8836_UPDATECONFIRM,NULL);
		  _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_8836_REQUPDATEKEY,NULL);
		    media_printf(_T("8836_UpdateCmd\n"));
	        break;
	   case SID_MCU_RX_8836_UPDATEKEY:
	   	if((p_cRxdata[0]==0x56)&&(p_cRxdata[1]==0xAE))
	   	{
			Tw8836_SetUpgradeStatus(0);
	   	}
	        break;
	   case SID_MCU_RX_8836_UPDATEDATA:
//	   	if( fTw8836.Tw8836_UpgradeOKFlage==1)
//	   	{
//			fTw8836.Tw8836_UpgradeOKFlage=0;
//	   	}
//		else
		{
			fTw8836.Tw8836_PacketId=(p_cRxdata[1]<<8)|p_cRxdata[0];
			 media_printf(_T("1-fTw8836.Tw8836_PacketId=%ix\n", fTw8836.Tw8836_PacketId));
			//fTw8836.Tw8836_PacketId++;
			API_MemCopy(&p_cRxdata[2],(uint8_t*)(&fTw8836.OsdBuffData[1]),64);
			
		/*	for(i=0;i<64;i++)
	       { 		
	         	  media_printf(_T(" -%x",fTw8836.Tw8836_UpgradeData[i]));
	        }
	        
			media_printf(_T("\n"));
			*/
			Tw8836_SetUpgradeStatus(1);
		}
              break;
	   case SID_MCU_RX_8836_UPDATECHECKSUM://8836 enable mcu
		Tw8836_SetUpgradeStatus(2);
		break;
		
		
	}

}

void MDI_RxFct(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{

}


void MDI_RxPackgeHook(uint8_t gid,uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
	//media_printf(_T("-----RX %x-%x---%x-%x-%x-%x-%x-%x-----\n",gid,cSid,p_cRxdata[0],p_cRxdata[1],p_cRxdata[2],p_cRxdata[3],p_cRxdata[4],p_cRxdata[5]));
	uint8_t i;
    	uint8_t *buf;
    	buf = (uint8_t*)p_cRxdata;
#if 0
	media_printf(_T("********RX %x-%x\n",gid,cSid));
	for(i=0;i<5;i++)
	{
		media_printf(_T("[%d]=%x",i,buf[i]));
	}
	media_printf(_T("\n"));
#endif
}


const fMEDIA_RXDATA_ANALYZE gpa_fMediaUserRxPkgAnalyze[] = {
    MDI_RxCmd,
    MDI_RxSysInfo,
    MDI_RxSeting,
    MDI_RxRTC,
    MDI_RxMediaInfo,
    MDI_RxCanInfo,
    MDI_RxDeviceInfo,
    MDI_RxSwcInfo,
    MDI_RxProjectInfo,
    MDI_RxMcuUpdata,
    MDI_Rx8836Updata,
    MDI_RxFct,
    NULL,
    NULL,
    NULL,
    NULL,
};

const tMEDIA_RX_FUCNTION_BLOCK g_tMediaRxPkgAnalyzeFunctionTab = {
    GID_MCU_RX_NUM,
    gpa_fMediaUserRxPkgAnalyze,
};


 void MDI_TxPackgeHook(uint8_t gid,uint8_t cSid,void*  p_cSrcBuf)
{
    uint8_t i;
    uint8_t *buf;
    buf = (uint8_t*)p_cSrcBuf;
#if 0
    media_printf(_T("********TX %x-%x\n",gid,cSid));
    for(i=0;i<10;i++)
    {
	    media_printf(_T("[%d]=%x",i,buf[i]));
    }
    media_printf(_T("\n"));
#endif	
}
 

uint8_t MDI_TxCmd(uint8_t cSid,void* p_cSrcBuf,uint8_t* p_cDstBuf)
{
    uint8_t re = 0;

    if(cSid == SID_MCU_TX_CMD)
    {
    	    uMSG_DATA uBuf;
	    uBuf.p_cData = p_cSrcBuf;
	    p_cDstBuf[1] = uBuf.a_cData[0];
	    p_cDstBuf[2] = uBuf.a_cData[1];

	media_printf(_T("TxCmd: cSid = %x,%x-%x\n",cSid,p_cDstBuf[1],p_cDstBuf[2]));
	re = 3;
    }
    else if(cSid == SID_MCU_TX_QUERY_STATE)
    	{
		p_cDstBuf[1] = 0x00;
		re = 2;
	}
    return re;
}

uint8_t MDI_TxSystemInfo(uint8_t cSid,void*  p_cSrcBuf,uint8_t* p_cDstBuf)
{
    uint8_t re = 0;
    
    p_cDstBuf[0] = cSid;

    switch(cSid)
    {
        case (uint8_t)OP_INFO_VERSION:
        {
            uint8_t cALen;
            
            cALen = API_StrLen((uint8_t*)ga_cSoftwareVer,0x20);
            API_MemCopy((uint8_t*)ga_cSoftwareVer,&p_cDstBuf[1],cALen);
    
            re = 1+cALen;
        }
        break;
        case (uint8_t)OP_INFO_KEYDATA:
        {
            re =  sizeof(eKEY_DATA_STATE);
            API_MemCopy((uint8_t *)&KeyInfoStr,&p_cDstBuf[1],re);
			media_printf(_T("Key Info:code = 0x%x,source = %d, attri = %d,state = %d\n",KeyInfoStr.keyCode,
				KeyInfoStr.keySource,KeyInfoStr.keyAttri,KeyInfoStr.keyState));
            return (re+1);
        }
        break;
        
        case (uint8_t)OP_INFO_VOLUME:
        {
            uMSG_DATA uBuf;
            uBuf.p_cData = p_cSrcBuf;
            p_cDstBuf[1] = uBuf.a_cData[0];
            p_cDstBuf[2] = uBuf.a_cData[1];
	     media_printf(_T("Volume Info: -%x-%d\n",p_cDstBuf[1],p_cDstBuf[2]));
            re = 3;
        }
        break;
        case (uint8_t)OP_INFO_DEVICESTATUS:
	{
		uint8_t Buff[2];
		re = sizeof(tDEV_ON_MCU_STATE);
		API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
		media_printf(_T("===TDev -%x-%x-%x-%x =\n",p_cDstBuf[1],p_cDstBuf[2],p_cDstBuf[3],p_cDstBuf[4]));
		re+=1;
		g_tMcuDevState.uIOState.bits.FirstPowerOnFlag = 0;		/*Clear First Power On Flag */
        }
        break;
        case (uint8_t)OP_INFO_SYS_TIME_BASE:		// bolte
        {
            uint32_t lTime = OS_GetWatchSecond();
            p_cDstBuf[4] = (uint8_t)(lTime>>24);
            p_cDstBuf[3] = (uint8_t)(lTime>>16);
            p_cDstBuf[2] = (uint8_t)(lTime>>8);
            p_cDstBuf[1] = (uint8_t)(lTime);
            re = 5;
	   media_printf(_T("OP_INFO_SYS_TIME_BASE-%lx =\n",lTime));		
        }
        break;
	case (uint8_t)OP_INFO_SYS_VOL_ALL:
		p_cDstBuf[1] = sAudioKeep.SysVol;
		p_cDstBuf[2] = sAudioKeep.BtVol;
		p_cDstBuf[3] = sAudioKeep.AppVol;
		p_cDstBuf[4] = sAudioKeep.NaviVol;
            	re = 5;
		break;
	case (uint8_t)OP_INFO_SYS_STATE_INFO:
		re = sizeof(sSYS_STATE_DBG_INFO);
		API_MemCopy((uint8_t *)&g_tSysStateDbgInfo,&p_cDstBuf[1],re);
		re+=1;
		break;
	default:
		break;
    }
    return re;
}

uint8_t MDI_TxSeting(uint8_t cSid,void*  p_cSrcBuf,uint8_t* p_cDstBuf)
{
    uint8_t re = 0;
    p_cDstBuf[0] = cSid;
    
    switch(cSid)
    {
        case (uint8_t)OP_INFO_ASP_SETTING:
            re = sizeof(AUDIO_ADV_STRUCT);
            API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
            re+=1;
        break;

        case (uint8_t)OP_INFO_AUDIOSETTING:
            re = sizeof(AUDIO_BASIC_STRUCT);
            API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
            re+=1;
        break;


        case (uint8_t)OP_INFO_CH_GAIN:
            re = sizeof(AUDIO_CHANGAIN_STRUCT);
            API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
            re+=1;
        break;

        case (uint8_t)OP_INFO_6CH_VOLSETTING:
        break;

        case (uint8_t)OP_INFO_GENERALSETTING:
            re = sizeof(tSYS_GENERAL_SETTING);
            API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
            re+=1;
        break;
        case (uint8_t)OP_INFO_SCREENSETTING:
            re = sizeof(tSYS_SCREEN_SETTING);
            API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
            re+=1;
            re = 4;
        break;
		case (uint8_t)OP_INFO_DEVELOP:
            API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],1);
			re = 2;
			media_printf(_T("--------OP_INFO_DEVELOP--------%d\n",p_cDstBuf[1]));
			break;
    }
    return re;
}

uint8_t MDI_TxRadio(uint8_t cSid,void* p_cSrcBuf,uint8_t* p_cDstBuf)
{
    uint8_t i;
    uint8_t re = 0;
    uMSG_DATA uBuf;
    TUNER_DATUM_STRUCT* psTmp = (TUNER_DATUM_STRUCT*)p_cSrcBuf;
    TUNER_KEEP_STRUCT* psKeep = (TUNER_KEEP_STRUCT*)p_cSrcBuf;
    uBuf.p_cData = p_cSrcBuf;

    p_cDstBuf[0] = cSid;
    switch(cSid)
    {
        case (uint8_t)OP_INFO_RADIOINFO:
            p_cDstBuf[1] = psTmp->sInfo.CurrentBand;
            p_cDstBuf[2] = psTmp->sInfo.CurrentPreset;
            p_cDstBuf[3] = Tuner_Api_GetValidHightlight();
            p_cDstBuf[4] = (uint8_t)(psTmp->sInfo.CurrentFreq);
            p_cDstBuf[5] = (uint8_t)(psTmp->sInfo.CurrentFreq >> 8);
            p_cDstBuf[6] = Tuner_Api_GetSeekState();
            media_printf(_T(">>Radio Freq Updata>>  %id  <<\n",psTmp->sInfo.CurrentFreq));
            if(psTmp->sSetting.sMap.bLocDxSetting)
            {
                p_cDstBuf[6] |= 0x10;  //Loc Dx Mask
            }
            else
            {
                p_cDstBuf[6] &= (~0x10);
            }
            if(Tuner_Api_GetStereoMono())
            {
                p_cDstBuf[6] |= 0x08; // Stereo Mono Mask
            }
            else
            {
                p_cDstBuf[6] &= (~0x08);
            }
	     if(Tuner_Api_GetPauseState())
	     	{
	     	 p_cDstBuf[6] |= 0x40; // Pause
	     	}
		 else
		  {
		  p_cDstBuf[6] &= (~0x40);	
		  }
            re = 7;
            break;

        case (uint8_t)OP_INFO_RADIOPRESETFREQLIST:
            for(i = 0; i < TUNER_PRESET_MAX; i++)
            {
                p_cDstBuf[(2 * i) + 1] = (uint8_t)(psTmp->sInfo.Preset[psTmp->sInfo.CurrentBand][i]); 
                p_cDstBuf[(2 * i) + 2] = (uint8_t)(psTmp->sInfo.Preset[psTmp->sInfo.CurrentBand][i] >> 8);     
            }
            re = (2 * TUNER_PRESET_MAX) + 1;
            break;

        case (uint8_t)OP_INFO_RADIOSTATIONLIST:
			#ifdef D_TUNER_LIST
				re = psKeep->ListNum;
			#else
            	re = psKeep->ValidNumber;
			#endif
      		media_printf(_T(">>>>Radio List updata>>>>List ValidNumber : %d\n",re));
	        if(re>LIST_BUFFER_MAX)
	     	{
			    re = LIST_BUFFER_MAX;
		    }
		    p_cDstBuf[1] = re;
		    
            for(i = 0; i < p_cDstBuf[1]; i++)
            {
                p_cDstBuf[(2 * i) + 2] = (uint8_t)(psKeep->ValidList[i]); 
                p_cDstBuf[(2 * i) + 3] = (uint8_t)(psKeep->ValidList[i] >> 8); 
				media_printf(_T(">>>>Freq = %id\n",psKeep->ValidList[i]));
            }
            re = (2 * p_cDstBuf[1]) + 2;
            break;

        case (uint8_t)OP_INFO_RADIOSIGNALLEVEL:
            p_cDstBuf[1] = Tuner_Api_GetSignalStr();
            re = 2;
            break;

        case (uint8_t)OP_INFO_RDS_INFO:
            p_cDstBuf[1] = 0x00; //Clear
            if(psTmp->sSetting.sMap.bStereoSetting)
            {
                p_cDstBuf[1] |= 0x01;  //ST Mono  Mask
            }
            else
            {
                p_cDstBuf[1] &= (~0x01);
            }
            if(psTmp->sSetting.sMap.bAfSetting)
            {
                p_cDstBuf[1] |= 0x04;  //AF Setting  Mask
            }
            else
            {
                p_cDstBuf[1] &= (~0x04);
            }
            if(psTmp->sSetting.sMap.bTaSetting)
            {
                p_cDstBuf[1] |= 0x08;  //TA Setting  Mask
            }
            else
            {
                p_cDstBuf[1] &= (~0x08);
            }
            if(psTmp->sSetting.sMap.bPtySetting)
            {
                p_cDstBuf[1] |= 0x10;  //PTY Setting  Mask
            }
            else
            {
                p_cDstBuf[1] &= (~0x10);
            }
            if(psTmp->sSetting.sMap.bEonSetting)
            {
                p_cDstBuf[1] |= 0x20;  //EON Setting  Mask
            }
            else
            {
                p_cDstBuf[1] &= (~0x20);
            }
            if(psTmp->sSetting.sMap.bRegSetting)
            {
                p_cDstBuf[1] |= 0x40;  //REG Setting Mask
            }
            else
            {
                p_cDstBuf[1] &= (~0x40);
            }

            //TP Flag : mask 0x02
             if(Tuner_Api_GetTP())
            {
                p_cDstBuf[1] |= 0x02; 
            }
            else
            {
                p_cDstBuf[1] &= (~0x02);
            }           
            //TA Flag: mask 0x80
             if(Tuner_Api_GetTA())
            {
                p_cDstBuf[1] |= 0x80;  
            }
            else
            {
                p_cDstBuf[1] &= (~0x80);
            }               

            re = 2;
            break;

        case (uint8_t)OP_INFO_RDS_CURRPTY:
            p_cDstBuf[1] = uBuf.a_cData[0];
            re = 2;
            break;

        case (uint8_t)OP_INFO_RDS_PS_NAME:
            API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],8);
            re = 9;
            break;

        case (uint8_t)OP_INFO_RDS_RT_INFO:
            re = Tuner_Api_GetRtNum();
            API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
            re += 1;
            break;
		case (uint8_t) OP_INFO_RADIOAREA: //snake20170214 
			p_cDstBuf[1] = psKeep->Region;
			re = 2;
			break;
        default:
            break;
    }

    return re;
}



uint8_t MDI_TxSwc(uint8_t cSid,void*  p_cSrcBuf,uint8_t* p_cDstBuf)
{
    uint8_t re = 0;
    uMSG_DATA uBuf;
    uBuf.p_cData = p_cSrcBuf;

    switch(cSid)
    {
        case (uint8_t)OP_INFO_SWC_ALLSETTING:
        break;
        case (uint8_t)OP_INFO_SWC_KEY_STATE:
            p_cDstBuf[1] = uBuf.a_cData[0];
            p_cDstBuf[2] = uBuf.a_cData[1];
            p_cDstBuf[3] = uBuf.a_cData[2];
            
            re = 4;
        break;
        
        case (uint8_t)OP_INFO_SWC_RUNMODE:
            p_cDstBuf[1] = (p_cSrcBuf != NULL);
            re = 2;
        break;
        case (uint8_t)OP_INFO_SWC_ERROR_CODE:
        break;
        
    }
    return re;
}

uint8_t MDI_TxCanInfo(uint8_t cSid,void*  p_cSrcBuf,uint8_t* p_cDstBuf)
{
	uint8_t re = 0;
	uint8_t* pData = (uint8_t*)p_cSrcBuf;
	uint8_t flag = 0;

	p_cDstBuf[0] = pData[1];
	//hmi_printf(_T("MDI_TxCanInfo:pData[1] = 0x%x\n",pData[1]));
	switch(pData[1])
	{
		case OP_CAN_TX_DTV_LIST:
		case OP_CAN_TX_DTV_CAST:
		case OP_CAN_TX_DTV_CA:
		case OP_CAN_TX_CAR_VIN:
			flag = 1;
			break;
		case OP_CAN_TX_PRJ_SPCL:
			flag = 2;
			break;
		default:
			flag = 0;
			break;
	}
	re = pData[0]-2;			//这个长度字节中多了一个LENGTH字节。
	if(flag==0)
	{
		API_MemCopy(&pData[2],&p_cDstBuf[1],re);
	}
	else if(flag == 1)
	{
		ExtMediaDataStruct *ptr = (ExtMediaDataStruct *)p_cSrcBuf;
		uint8_t len = ptr->Ctl.length;
		p_cDstBuf[0] = ptr->SID;
		API_MemCopy(ptr->Ctl.Data, &p_cDstBuf[1],len);
		if(ptr->Info.length >100)
		{	/* check length ,total databuffer length shoudn't over 240 , add by zwl at 2014-10-27*/
			ptr->Info.length = 100;
			hmi_printf(_T("Warn: CAN msg filt buffer overflow!!!\n",ptr->Info.length));
		}
		re = ptr->Info.length+len;
		API_MemCopy(ptr->Info.pData, &p_cDstBuf[1+len],ptr->Info.length);
	}
	else if(flag == 2)
	{
		p_cDstBuf[1] = CAN_PRJ_ID_CHANA_C201;		//Project number card.
		API_MemCopy(&pData[2],&p_cDstBuf[2],pData[0]-2);
		re = re+1;
	}
	return (re+1);
}

uint8_t MDI_TxMcuUpdata(uint8_t cSid,void*  p_cSrcBuf,uint8_t* p_cDstBuf)
{
    uint8_t re = 0;
    return re;
}
uint8_t MDI_Tx8836Updata(uint8_t cSid,void*  p_cSrcBuf,uint8_t* p_cDstBuf)
{
       uint8_t re = 0;
       p_cDstBuf[0]=cSid;
	switch(cSid)
    {
        case (uint8_t)OP_INFO_8836_UPDATECONFIRM:
	{
		re = 1;
		media_printf(_T("OP_INFO_8836_UPDATECONFIRM=%x\n",cSid));
	}
        break;
        case (uint8_t)OP_INFO_8836_REQUPDATEKEY:
	{
		re = 1;
		 media_printf(_T("OP_INFO_8836_REQUPDATEKEY=%x\n",cSid));
	}
        break;
	case (uint8_t)OP_INFO_8836_REQUPDATEDATA:
	{
             re=3;
             p_cDstBuf[1]=(fTw8836.Tw8836_PacketId)&0xff;
	      p_cDstBuf[2]=((fTw8836.Tw8836_PacketId)>>8)&0xff;
	    //  media_printf(_T("DstBuf[1]=%x,DstBuf[2]=%x\n", p_cDstBuf[1], p_cDstBuf[2]));
	      media_printf(_T("OP_INFO_8836_REQUPDATEDATA=%x\n",cSid));
	}
	break;
}
    return re;
}

uint8_t MDI_TxFct(uint8_t cSid,void*  p_cSrcBuf,uint8_t* p_cDstBuf)
{
    uint8_t re = 0;
    uint8_t* pFctData = (uint8_t*)p_cSrcBuf;
    uMSG_DATA uBuf;
    uBuf.p_cData = p_cSrcBuf;
    p_cDstBuf[0] = cSid;
#if 0
    switch(cSid)
    {
        case (uint8_t)OP_INFO_FCT_CMD:
	{
		re = 1;
		p_cDstBuf[1] =uBuf.a_cData[0];
	}
        break;
        case (uint8_t)OP_INFO_FCT_FUNCSWITCH:
	{
		re = 1;
		p_cDstBuf[1] =uBuf.a_cData[0];
	}
        break;
        case (uint8_t)OP_INFO_FCT_MEDIACONTROL:
	{
		re = 2;
		p_cDstBuf[1] =uBuf.a_cData[0];
		p_cDstBuf[2] =uBuf.a_cData[1];
	}
        break;
        case (uint8_t)OP_INFO_FCT_BLUETOOTH:
	{
		if((0 == uBuf.a_cData[2])||(0 == uBuf.a_cData[3]))
		{	
			if(APU_FCT_BT_ON_OFF == uBuf.a_cData[0])
			{
				re = 2;
				p_cDstBuf[1] =uBuf.a_cData[0];
				p_cDstBuf[2] =uBuf.a_cData[1];
			}
			else if((APU_FCT_BT_REQ_MAC == uBuf.a_cData[0])
			||(APU_FCT_BT_REQ_BT_STATE == uBuf.a_cData[0])
			||(APU_FCT_BT_REQ_BT_NAME == uBuf.a_cData[0])
			||(APU_FCT_BT_REQ_BT_VERSION == uBuf.a_cData[0])
			||(APU_FCT_BT_REQ_RF_QUALITY == uBuf.a_cData[0]))
			{
				re = 1;
				p_cDstBuf[1] =uBuf.a_cData[0];
			}
		}
		else if(APU_FCT_BT_CHG_BT_NAME == pFctData[0])
		{
			re=g_tFCT.tDataBuf.BTDevNameL;
			API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
		}
		else if(APU_FCT_BT_DIAL_CALL == pFctData[0])
		{
			re=g_tFCT.tDataBuf.BTDialNumL;
			API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
		}	
	}
        break;
        case (uint8_t)OP_INFO_FCT_GPS:
	{
		 if((APU_FCT_GPS_SIMULATA_ROUTE == uBuf.a_cData[0])
		||(APU_FCT_GPS_REQ_RET_QUALITY == uBuf.a_cData[0])
		||(APU_FCT_GPS_REQ_RET_GYRO_INFO == uBuf.a_cData[0])
		||(APU_FCT_GPS_REQ_RET_TMC_INFO == uBuf.a_cData[0]))
		{
			re = 1;
			p_cDstBuf[1] =uBuf.a_cData[0];
		}
	}
        break;
        case (uint8_t)OP_INFO_FCT_TPMS:
	{
		re = 2;
		API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
	}
        break;
        case (uint8_t)OP_INFO_FCT_VIDEOSET:
	{
		re = 3;
		p_cDstBuf[1] =uBuf.a_cData[0];
		p_cDstBuf[2] =uBuf.a_cData[1];
		p_cDstBuf[3] =uBuf.a_cData[2];
	}
        break;
        case (uint8_t)OP_INFO_FCT_WIFI:
	{
		if((0 == uBuf.a_cData[2])||(0 == uBuf.a_cData[3]))
		{	
			if(APU_FCT_WIFI_ON_OFF == uBuf.a_cData[0])
			{
				re = 2;
				p_cDstBuf[1] =uBuf.a_cData[0];
				p_cDstBuf[2] =uBuf.a_cData[1];
			}
			else if(APU_FCT_WIFI_REQ_ISSI == uBuf.a_cData[0])
			{
				re = 1;
				p_cDstBuf[1] =uBuf.a_cData[0];
			}
		}
		else if(APU_FCT_WIFI_LINK_AP == pFctData[0])
		{
			re = g_tFCT.tDataBuf.WifiApNamePinL;
			API_MemCopy(p_cSrcBuf,&p_cDstBuf[1],re);
		}
	}
        break;
        case (uint8_t)OP_INFO_FCT_REQVERSION:
	{
		re = 1;
		p_cDstBuf[1] =uBuf.a_cData[0];
	}
        break;
		
		
    }
#endif
	re+=1;
	return (re);
}

uint8_t MDI_TxPrjInfo(uint8_t cSid,void*  p_cSrcBuf,uint8_t* p_cDstBuf)
{
	uint8_t re = 0;
	uint8_t* pData = (uint8_t*)p_cSrcBuf;
	uint8_t i;
	#if 0
	media_printf(_T("==MDI_TxPrjInfo cSid=%d",cSid));
	for(i=0;i<6;i++)
	{
		media_printf(_T("[%d]=%x",i,pData[i]));	
	}
	media_printf(_T("\n"));
	#endif
	switch(pData[0])
	{	
		case CAN_PRJ_ID_CHANA_C201:
			break;
		case CAN_PRJ_ID_CHANA_S301:
			break;
		case CAN_PRJ_ID_CHANA_CD101:
			break;
		case CAN_PRJ_ID_CHANA_S401:
			switch(pData[1])
			{
				case USERID_APU_TX_DVR_SETREQ:
					re = sizeof(CarDvrDataStruct);
							 API_MemCopy(p_cSrcBuf,&p_cDstBuf[0],re);
					break;
				default:
					break;
			}
			break;
		case CAN_PRJ_ID_CHANA_R103H:
			switch(pData[1])
			{
				case USERID_APU_TX_DVR_SETREQ:
					re = sizeof(CarDvrDataStruct);
					API_MemCopy(p_cSrcBuf,&p_cDstBuf[0],re);
					break;
				case USERID_APU_TX_DVR_VER:
					re = sizeof(CarDvrVerStruct);
					API_MemCopy(p_cSrcBuf,&p_cDstBuf[0],re);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	return re;
}


const fMEDIA_TXDATA_ANALYZE gpa_fMediaUserTxPkgGenerate[] = {
    MDI_TxCmd,
    MDI_TxSeting,
    MDI_TxSystemInfo,
    MDI_TxRadio,
    MDI_TxSwc,
    MDI_TxCanInfo,
    MDI_TxMcuUpdata,
    MDI_Tx8836Updata,
    MDI_TxFct,
    MDI_TxPrjInfo,
    NULL,
    NULL,
};

const tMEDIA_TX_FUCNTION_BLOCK g_tMediaTxPkgGenerateFunctionTab = {
    GID_MCU_TX_NUM,
    gpa_fMediaUserTxPkgGenerate,
};

