#define _MEDIA_DRIVER_C_

#include "..\config\inc.h"
#include "media_driver.h"


tTASK_CTRL_BLOCK l_tMediaTaskCB;

#pragma pack(1)

tRING_QUE l_tMediaMsgQue;
tMSG_BUF l_tMediaMsgBuf[D_MEDIA_MSG_QUE_DEEP];
tMEDIA_CTRL_BLOCK   l_tMediaCB;
tMEDIA_TFTRESET_BLOCK l_tMediaTftCB;

#pragma section data "no_init" begin
uint8_t isOsNormalStart;	// 0: ready to Updata  1:normal start
#pragma section data "no_init" end

#if D_DEBUG_MEDIA && D_PRINT_EN
const char* const la_strMediaModeName[]={
    "  Start  ",
    " Running ",
    "WAITSLEEP",
    "  SLEEP ",
    "   OFF   ",
    "   LVI   ",
};
#endif




#define TFT_RESET_STOP		0x00
#define TFT_RESET_CHK		0x01
#define TFT_RESET_DELAY	0X02

#define TFT_EVENT_INIT		0x00
#define TFT_EVENT_RESET      0x01
#define TFT_EVENT_OK            0x02
#define TFT_EVENT_UPDATE    0x03		/*APU PC update state*/

#define TFT_POWER_OFF  0x01
#define TFT_POWER_ON    0x02
//uint8_t FristEolReq=0;

void MEDIA_TftResetInit(void)
{
	l_tMediaTftCB.GpioDelayCnt = 0;
	l_tMediaTftCB.GpioLastState = 0xff;
	l_tMediaTftCB.GpioState = 0;
	l_tMediaTftCB.tftResetDelay = 0;
	l_tMediaTftCB.tftResetStep = TFT_RESET_STOP;
}
void MEDIA_ScanGpioState(void)
{
	uint8_t state = 0x00;
	
	if((l_tMediaCB.ePmState == OP_PM_STATE_SLEEP)
	||(l_tMediaCB.ePmState == OP_PM_STATE_WAIT_SLEEP)
	||(l_tMediaCB.ePmState == OP_PM_STATE_OFF)
	||(l_tMediaCB.ePmState == OP_PM_STATE_LVI)
	||(l_tMediaCB.ePmState == OP_PM_STATE_STANDBY)
	||(l_tMediaCB.ePmState == OP_PM_STATE_ERR)
	||(l_tMediaCB.ePmState == OP_PM_STATE_BATERR)
	)
	return;
	
	if(INVALID== IO_Get(IO_IDX_CPU_STATE,PIN_INPUT,DISABLE))
	{
		state |= BIT1;
	}
	if(INVALID== IO_Get(IO_IDX_NAVI_AUDIO,PIN_INPUT,DISABLE))
	{
		state |= BIT0;
	}
	if(l_tMediaTftCB.GpioLastState != state)
	{
		l_tMediaTftCB.GpioDelayCnt= 0;
	}
	else
	{
		l_tMediaTftCB.GpioDelayCnt++;
		if(l_tMediaTftCB.GpioDelayCnt>=2)
		{
			l_tMediaTftCB.GpioDelayCnt= 2;
			if(l_tMediaTftCB.GpioState != l_tMediaTftCB.GpioLastState)
			{
				l_tMediaTftCB.GpioState = l_tMediaTftCB.GpioLastState;
				media_printf(_T("Media GPIO state = %x \n", l_tMediaTftCB.GpioState));
			}
		}
	}
	l_tMediaTftCB.GpioLastState = state;
}

void MEDIA_TftResetRoutine(void)
{
	MEDIA_ScanGpioState();
	switch(l_tMediaTftCB.tftResetStep)
	{

		case TFT_RESET_CHK:
		if(l_tMediaCB.uDevFlag.field.bDevConnect==1)
			{
			      if((l_tMediaTftCB.GpioState == TFT_EVENT_RESET)&&( l_tMediaCB.TFTStateFlag!=TFT_POWER_OFF))
			      	{		                      
					PM_UnitPowerSet(PM_UNIT_TFT , OFF);	
					 l_tMediaCB.TFTStateFlag=TFT_POWER_OFF;
					media_printf(_T("******TFT OFF\n"));
			      	}
					//os reboot之后给屏断电之后,不会给屏上电了...
				 else if(((l_tMediaTftCB.GpioState == TFT_EVENT_INIT)||(l_tMediaTftCB.GpioState == TFT_EVENT_OK))&&( l_tMediaCB.TFTStateFlag!=TFT_POWER_ON))
				 {
                                   PM_UnitPowerSet(PM_UNIT_TFT , ON);	
				       l_tMediaCB.TFTStateFlag=TFT_POWER_ON;				
				      media_printf(_T("******TFT ON\n"));
				 }
				 l_tMediaTftCB.tftResetStep = TFT_RESET_CHK;
			}
		else if(l_tMediaTftCB.GpioState == TFT_EVENT_RESET)
			{
				l_tMediaTftCB.tftResetStep = TFT_RESET_DELAY;
				l_tMediaTftCB.tftResetDelay = _TFT12V_RESET_TIME;
				PM_UnitPowerSet(PM_UNIT_TFT , OFF);
				media_printf(_T("Media TFT Reset!\n"));
			}
			break;
		case TFT_RESET_DELAY:
			if(l_tMediaTftCB.tftResetDelay == 0)
			{
				l_tMediaTftCB.tftResetStep = TFT_RESET_CHK;
				PM_UnitPowerSet(PM_UNIT_TFT , ON);
			}
			break;
		case TFT_RESET_STOP:
		default:
			break;
	}
}

/*Enter state,do something*/
/* Do not ignore duplicate IO or Power uinte operation*/
void MEDIA_EnterState(eMEDIA_STATE eState)
{   
    switch(eState)
    {
        case MEDIA_STATE_START:
			PM_TftPowerSet(OFF,0);
			IO_Set(IO_IDX_APU_LOWPWR, PIN_OUTPUT,INVALID); 
			IO_Set(IO_IDX_APU_RESET, PIN_OUTPUT,VALID); 
			OS_TaskStart(TASK_ID_MEDIA_DRV);
			l_tMediaCB.eBakState = 0xff;
			l_tMediaCB.cCnt = 0;
	        break;

        case MEDIA_STATE_RUNNING:
			if(fTw8836.ADI7186InitProgramme == 1)//snake20161109
			{
				if(IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE))//snake20161101
				{
					PM_TftPowerSet(ON,0);
					media_printf(_T("MEDIA Function go to RUNNING STATE....OPEN TFT!!!!!\n"));
				}
			}
	        break;
        
        case MEDIA_STATE_WAIT_SLEEP:
		     l_tMediaCB.eBakState = (l_tMediaCB.eState<<4)|l_tMediaCB.eSubState;
            PM_TftPowerSet(OFF,0);
	        break;
                
        case MEDIA_STATE_LVI:
			PM_TftPowerSet(OFF,0);
			l_tMediaCB.uDevFlag.field.bDevConnect = 0;
			PM_UnitPowerSet(PM_UNIT_APU,OFF);
			break;
       
        case MEDIA_STATE_SLEEP:
            PM_TftPowerSet(OFF,0);
            l_tMediaCB.uDevFlag.field.bUnLocked = 0;
        break;

        case MEDIA_STATE_OFF:
			PM_TftPowerSet(OFF,0);
			(void)OS_TaskStop(TASK_ID_MEDIA_DRV);
			PM_UnitPowerSet(PM_UNIT_APU, OFF);
			l_tMediaCB.uDevFlag.field.bDevConnect = 0;
			l_tMediaCB.uDevFlag.field.bUnLocked = 0;
			l_tMediaTftCB.tftResetStep = TFT_RESET_STOP;
	        break;
	        
		case MEDIA_STATE_UPDATE:
		break;
            
			default:
			break;
        
    }
    /*In this state,save the PM msg,because this state,the timing cant be interrupt*/
    media_printf(_T("MediaState "));
    media_printf(_T(la_strMediaModeName[l_tMediaCB.eState]));
    media_printf(_T(" ==> "));
    media_printf(_T(la_strMediaModeName[eState]));
    media_printf(_T(",EVT = %d \n", l_tMediaCB.ePmState ));

    l_tMediaCB.eState = eState;

    if((eState == MEDIA_STATE_RUNNING) &&
	((l_tMediaCB.eBakState>>4) == MEDIA_STATE_RUNNING))
    {
	l_tMediaCB.eSubState = l_tMediaCB.eBakState&0x0f;
	l_tMediaCB.eBakState = 0xff;
    }
    else
    {
    	l_tMediaCB.eSubState = MEDIA_STATE_STEP_0;
    }
    l_tMediaCB.iTimer = 0;
}


void MEDIA_StartHandle(void)
{
    switch(l_tMediaCB.eSubState)
    {   
    	 case MEDIA_STATE_STEP_0:
			l_tMediaCB.iTimer = 0;
			l_tMediaCB.uDevFlag.field.bDevConnect = 0;
			l_tMediaCB.uDevFlag.field.bDevAwake = 0;
			l_tMediaCB.uDevFlag.field.bTestMode = 0;
			l_tMediaTftCB.tftResetStep = TFT_RESET_STOP;
			l_tMediaCB.eSubState = MEDIA_STATE_STEP_1;
			l_tMediaCB.MediaStartupTimeoutValue = _APU_WAIT_START1;
			l_tMediaCB.TFTStateFlag=0;
			OS_ClearOsTick();
        	break;
	 case MEDIA_STATE_STEP_1:
	 	if(OS_GetOsTick() >= _PMIC_ON_TIME)
             {
			l_tMediaCB.eSubState = MEDIA_STATE_STEP_2;
			PM_UnitPowerSet(PM_UNIT_APU, ON);
			PM_UnitPowerSet(PM_UNIT_TFT , ON);
			IO_Set(IO_IDX_APU_RESET,PIN_OUTPUT,VALID);
			media_printf(_T("MEDIA_STATE_STEP_2:0x%lx\n",OS_GetOsTick()));
			OS_ClearOsTick();
			l_tMediaCB.iTimer = 0;
		}
		break;		
        case MEDIA_STATE_STEP_2:		//generate RESET pulse
		IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,0);
	 	if(OS_GetOsTick() >= _APU_RESET_TIME1)
 		{
			l_tMediaCB.eSubState = MEDIA_STATE_STEP_3;
			media_printf(_T("MEDIA_STATE_STEP_3:0x%lx\n",OS_GetOsTick()));
			IO_Set(IO_IDX_APU_RESET, PIN_OUTPUT,INVALID); 
			IO_Set(IO_IDX_USB_HOST, PIN_OUTPUT,VALID); 	//Select USB HOST mode
			l_tMediaCB.iTimer = 0;
			l_tMediaTftCB.tftResetStep = TFT_RESET_CHK;
			OS_ClearOsTick();
 		}
        	break;

        case MEDIA_STATE_STEP_3:	
		if(OS_GetOsTick() <=  l_tMediaCB.MediaStartupTimeoutValue)
		{
			if(l_tMediaTftCB.GpioState == TFT_EVENT_OK)
			{
				media_printf(_T("_APU_TEST_TIMING 0x%lx\n",OS_GetOsTick()));
				l_tMediaCB.cCnt = 0;
				l_tMediaCB.iTimer = 0;			
				MEDIA_EnterState(MEDIA_STATE_RUNNING);
			}
			else if(((l_tMediaTftCB.GpioState == TFT_EVENT_UPDATE)&&
				(l_tMediaCB.iTimer >=  _APU_WAIT_UPDATE_TIMING)
				||(l_tMediaCB.uDevFlag.field.bUpData))
				)
			{
				isOsNormalStart = 0;
				media_printf(_T("APU inform enter PC update mode....l_tMediaCB.uDevFlag.field.bUpData = %d\n",l_tMediaCB.uDevFlag.field.bUpData));
				l_tMediaCB.uDevFlag.field.bUpData = 1;
				l_tMediaCB.iTimer = 0;		
				l_tMediaTftCB.tftResetStep = TFT_RESET_STOP;
				_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_ACK,BEEP_ON,0,0);//BEEP Indicator.
				MEDIA_EnterState(MEDIA_STATE_UPDATE);
			}
			else if(l_tMediaTftCB.GpioState == TFT_EVENT_RESET)
			{
				if(l_tMediaCB.MediaStartupTimeoutValue != _APU_WAIT_START2)
				{
					l_tMediaCB.MediaStartupTimeoutValue = _APU_WAIT_START2;
					OS_ClearOsTick();
					l_tMediaCB.iTimer = 0;		
					media_printf(_T("Event_RESET, change timer: START2\n"));
				}
			}
		}
		else
		{
#if 0		// bolte 核心板异常复位
			l_tMediaCB.iTimer = 0;
			l_tMediaCB.eSubState = MEDIA_STATE_STEP_2;
			l_tMediaTftCB.tftResetStep = TFT_RESET_STOP;
			OS_ClearOsTick();
			media_printf(_T("Wait starting time out,Reset APU\n"));
			IO_Set(IO_IDX_APU_RESET,PIN_OUTPUT,VALID);
			/*change reset timeout wait timer value */
			if(l_tMediaCB.MediaStartupTimeoutValue != _APU_WAIT_START2)
			{
				l_tMediaCB.MediaStartupTimeoutValue = _APU_WAIT_START2;
			}
			else
			{
				l_tMediaCB.MediaStartupTimeoutValue = _APU_WAIT_START1;
			}
			l_tMediaCB.cCnt ++ ;
			media_printf(_T("reset cnt = %d\n", l_tMediaCB.cCnt));
#endif			
#if 1		// bolte 核心板异常复位要求对核心板断电
			l_tMediaCB.iTimer = 0;
			l_tMediaCB.eSubState = MEDIA_STATE_STEP_4;
			l_tMediaTftCB.tftResetStep = TFT_RESET_STOP;
			OS_ClearOsTick();
			media_printf(_T(" [cut off power of core board]\n"));
			PM_UnitPowerSet(PM_UNIT_APU, OFF);
			PM_UnitPowerSet(PM_UNIT_TFT , OFF);		
			IO_Set(IO_IDX_APU_RESET,PIN_OUTPUT,VALID);
			/*change reset timeout wait timer value */
			if(l_tMediaCB.MediaStartupTimeoutValue != _APU_WAIT_START2)
			{
				l_tMediaCB.MediaStartupTimeoutValue = _APU_WAIT_START2;
			}
			else
			{
				l_tMediaCB.MediaStartupTimeoutValue = _APU_WAIT_START1;
			}
			l_tMediaCB.cCnt ++ ;
			media_printf(_T("reset cnt = %d\n", l_tMediaCB.cCnt));
#endif			

		}
        break;
		
	case MEDIA_STATE_STEP_4:
		if(OS_GetOsTick() >= _APU_CUT_OFF_TIME)
		{
			OS_ClearOsTick();
			PM_UnitPowerSet(PM_UNIT_APU, ON);
			PM_UnitPowerSet(PM_UNIT_TFT , ON);		
			l_tMediaCB.eSubState = MEDIA_STATE_STEP_0;
		}
		break;
		
	 default:
	 	MEDIA_EnterState(MEDIA_STATE_START);
	  	break;

    }

    if(OP_PM_STATE_WAIT_SLEEP < l_tMediaCB.ePmState)
    { 
        MEDIA_EnterState(MEDIA_STATE_OFF);
    }
}

void MEDIA_SyncDeal(void)
{

	switch(l_tMediaCB.eSyncState)
    {  
    
        case MEDIA_STATE_STEP_1:
		if(l_tMediaCB.uDevFlag.field.bDevConnect)
             {
                l_tMediaCB.eSyncState = MEDIA_STATE_STEP_2;
		  l_tMediaCB.uDevFlag.field.bOSEnter = 0;
		  l_tMediaCB.SecondCnt = 7;
		  media_printf(_T("media Connected!\n"));
             }
	#if 1 //调节7186的时候,暂时把等待BSP OK的消息屏蔽
	
	      /*if(l_tMediaCB.uDevFlag.field.bDevAwake)
	      {
			//BSP 发送过来的BOOT_OK(0xff) 状态
	      }
             else*/ //snake20170109  不管是不是boot_ok都需要做超时判断...
             {
			if( 0 == isOsNormalStart)		// OS Updata
			{
			 	if(l_tMediaCB.SecondCnt >= 200)
			 	{
					l_tMediaCB.SecondCnt = 0;
					MEDIA_EnterState(MEDIA_STATE_START);
				}
			}
			else							// normal start
			{
				if(l_tMediaCB.SecondCnt >= 25)
				{
					l_tMediaCB.SecondCnt = 0;
					media_printf(_T("Wait BSP BOOT_OK uart msg timeout l_tMediaCB.uDevFlag.field.bDevAwake = %d---\n",l_tMediaCB.uDevFlag.field.bDevAwake));
					MEDIA_EnterState(MEDIA_STATE_START);
				}
			}
		}
	#endif
           
        break;
	case MEDIA_STATE_STEP_2:	
		OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_VERSION,NULL);
		media_printf(_T("media Send Version\n"));
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_3;
	 	break;
	 case MEDIA_STATE_STEP_3:
	 	OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_SYS_TIME_BASE,NULL);
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_4;
	 	break;
	 case MEDIA_STATE_STEP_4:
	 	OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_DEVICESTATUS,(void *)&g_tMcuDevState);
		OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_VOL_ALL,NULL);
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_5;
	 	break;
	 case MEDIA_STATE_STEP_5:
	 	OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SETTING,
	 									SID_MCU_TX_GENERALSETTING,
	 									(void *)&(g_tSysRomData.uGenBlock));
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_6;
		break;
	 case MEDIA_STATE_STEP_6:
	 	OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SETTING,
	 									SID_MCU_TX_SCREENSETTING,
	 									(void *)&(g_tSysRomData.tScrBlock));
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_6_0;

		break;
	case MEDIA_STATE_STEP_6_0://snake20170215 同步开发者选项状态
		//g_tSysRomData.DevelopFlag = 1;
		OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SETTING,
	 									SID_MCU_TX_DEVELOP,
	 									(void *)&(g_tSysRomData.DevelopFlag));
		media_printf(_T("send DevelopFlag: %d\n",g_tSysRomData.DevelopFlag));
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_6_1;
		break;
	case MEDIA_STATE_STEP_6_1:
		if(SysWorkStatusGrp.SysAutoTestEnter)
		{
			OS_PostFullMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_CMD,
												SID_MCU_TX_CMD,
												UICC_TEST_CMD, 0x01, 0,0);   	
			media_printf(_T("Send AutoTest :1\n"));
		}
		else
		{
			OS_PostFullMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_CMD,
												SID_MCU_TX_CMD,
												UICC_TEST_CMD, 0x00, 0,0);   	
			media_printf(_T("Send AutoTest :0\n"));
		}
		SysWorkStatusGrp.SysAutoTestEnter = 0;
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_7;

		break;
	case MEDIA_STATE_STEP_7:		// send memory POWER on/off information
		l_tMediaCB.uDevFlag.field.bAPUCheckEn = 1;
		if(g_tSysSettingRomData.uApuFuncFlag.field.bSysPowerOn)
		{
			/*Request Enter Warn-menu */
			media_printf(_T("Request Enter Warn\n"));
			_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD, UICC_OPEN_MENU, 0x05, 0, 0);
			l_tMediaCB.eSyncState = MEDIA_STATE_STEP_10;
		}
		else
		{
			/*Request Enter Standby-menu */
			media_printf(_T("Request Enter Standby\n"));
			_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD, UICC_OPEN_MENU, 0x06, 0, 0);
			l_tMediaCB.eSyncState = MEDIA_STATE_STEP_8;
			l_tMediaCB.iTimer = 0;
		}
		break;
	case MEDIA_STATE_STEP_8:		//when Power-off state, check Power on event
		if(g_tSysSettingRomData.uApuFuncFlag.field.bSysPowerOn)
		{
			l_tMediaCB.eSyncState = MEDIA_STATE_STEP_10;
		}
		else if((l_tMediaCB.uDevFlag.field.bAPUCheckEn)&&
			(!l_tMediaCB.uDevFlag.field.bTestMode)&&
			(l_tMediaCB.iTimer>_APU_HEART_CHK_TIMING))
	 	{
			l_tMediaCB.iTimer = 0;
			l_tMediaCB.cCnt++;
		#if 1
			media_printf(_T("[8]  OS heart Send,cnt = %x\n",l_tMediaCB.cCnt));
			_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
			if(l_tMediaCB.cCnt>=5)
			{
				media_printf(_T("[8]  OS App timeout!-------------\n"));
				_SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_RESET,NULL);
			}
		#endif
		}
		break;
	case MEDIA_STATE_STEP_9:		// Enter POWER-ON state, send memory source information
		_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD, UICC_FRONT_SRC, SysMemSource.MediaSource, 0, 0);
		 if(SysMemSource.NaviSource == SOURCE_NAVI)
		 {
			_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD, UICC_FRONT_SRC, SOURCE_NAVI, 0, 0);
		 }
		 media_printf(_T("Send Memory media Source\n"));
		 l_tMediaCB.eSyncState = MEDIA_STATE_STEP_10;
		break;
	case MEDIA_STATE_STEP_10:
		_SendMsgToSRC(MS_SRC_SYS_CMD,OP_SRC_DATA_SYNC,NULL);
		media_printf(_T("media Send Source Sync\n"));
		l_tMediaCB.iTimer = 0;
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_11;
		break;
	 case MEDIA_STATE_STEP_11:
		if(l_tMediaCB.cSysTimeSendCnt >= 3600)	//BOLTE 1个小时给GPS发送一次TIMEBASE
		{
			l_tMediaCB.cSysTimeSendCnt = 0;
			l_tMediaCB.SendTimeCnt++;
			if(l_tMediaCB.SendTimeCnt >= 8)//snake20161220 每8个小时减1,作为修复...
			{
				l_tMediaCB.SendTimeCnt = 0;
				OS_SetWatchSecond(OS_GetWatchSecond()-1);
			}
			
			OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_SYS_TIME_BASE,NULL);
		}
	 	if((l_tMediaCB.uDevFlag.field.bAPUCheckEn)&&
			(!l_tMediaCB.uDevFlag.field.bTestMode)&&
			(l_tMediaCB.iTimer>_APU_HEART_CHK_TIMING))
	 	{
			l_tMediaCB.iTimer = 0;
			l_tMediaCB.cCnt++;
			#if 1
			media_printf(_T("[11]  OS heart Send,cnt = %x\n",l_tMediaCB.cCnt));
			_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
			if(l_tMediaCB.cCnt>=5)
			{
				media_printf(_T("[11]  OS App timeout!-------------\n"));
				_SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_RESET,NULL);	
			}
			//bolte
			#endif
		}
    		break;
	 case MEDIA_STATE_STEP_12:
        default:
		l_tMediaCB.eSyncState = MEDIA_STATE_STEP_1;
	      break;
    }
}


void MEDIA_RunningHandle(void)
{
    switch(l_tMediaCB.eSubState)
    {
        case MEDIA_STATE_STEP_0:
	     OS_PostMsgDir(&l_tMediaTaskCB,MS_SYS_APU_INFO,OP_DEV_STATE_NOCONNECT,NULL);	  
            l_tMediaCB.eSubState ++;
            l_tMediaCB.iTimer = 0;
	     l_tMediaCB.SecondCnt = 0;
	     l_tMediaCB.eSyncState = MEDIA_STATE_STEP_1;
        break;
	default:
		MEDIA_SyncDeal();
		break;
    }
   
    if(OP_PM_STATE_STANDBY < l_tMediaCB.ePmState)
    {
        switch(l_tMediaCB.ePmState)
        {
            case OP_PM_STATE_WAIT_SLEEP:
                MEDIA_EnterState(MEDIA_STATE_WAIT_SLEEP);   
            break;

            case OP_PM_STATE_SLEEP:
            case OP_PM_STATE_LVI:
            case OP_PM_STATE_BATERR:
                MEDIA_EnterState(MEDIA_STATE_SLEEP);   
            break;

            default:
                MEDIA_EnterState(MEDIA_STATE_OFF);   
            break;
        }

    }
}


void MEDIA_WaitSleepHandle(void)
{
    switch(l_tMediaCB.eSubState)
    {
        case MEDIA_STATE_STEP_0:
	     PM_TftPowerSet(OFF,0);		// close screen
            l_tMediaCB.iTimer = 0;
            l_tMediaCB.eSubState++;
            if(l_tMediaCB.uDevFlag.field.bDevConnect)
            {
           		media_printf(_T("media Send ACC off\n"));
			l_tMediaCB.WaitSleepBeforOsReadyFlag = 0;
			OS_PostFullMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_CMD,SID_MCU_TX_CMD,UICC_POWER, OP_APU_WAIT_SLEEP_ON, 0,0);   
            }
	     else
	     {
			l_tMediaCB.WaitSleepBeforOsReadyFlag = 1;
	     }
        break;
        case MEDIA_STATE_STEP_1:
        default:
            if(l_tMediaCB.ePmState < OP_PM_STATE_WAIT_SLEEP)
            {
                if(l_tMediaCB.uDevFlag.field.bDevConnect)               
                {
                	media_printf(_T("media Send ACC on\n"));
                    OS_PostFullMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_CMD,SID_MCU_TX_CMD, UICC_POWER, OP_APU_WAIT_SLEEP_OFF, 0,0);
                    MEDIA_EnterState(MEDIA_STATE_RUNNING);
                }
                else 
                {
                 //   MEDIA_EnterState(MEDIA_STATE_START);
                    MEDIA_EnterState(MEDIA_STATE_RUNNING);
                }
            } 
            else if(OP_PM_STATE_WAIT_SLEEP < l_tMediaCB.ePmState)
            {
                MEDIA_EnterState(MEDIA_STATE_SLEEP);
            }
            else
            {
		if((l_tMediaCB.WaitSleepBeforOsReadyFlag) &&
			(l_tMediaCB.uDevFlag.field.bDevConnect))
		{
			l_tMediaCB.WaitSleepBeforOsReadyFlag = 0;
			media_printf(_T("media Send ACC off\n"));
			OS_PostFullMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_CMD,SID_MCU_TX_CMD,UICC_POWER, OP_APU_WAIT_SLEEP_ON, 0,0);   
		}
		MEDIA_SyncDeal();
	     }
        break;

    }

}


void MEDIA_SleepHandle(void)
{
    switch(l_tMediaCB.eSubState)
    {
        case MEDIA_STATE_STEP_0:
	     PM_TftPowerSet(OFF,0);
 			
            if(l_tMediaCB.uDevFlag.field.bDevConnect)               
            {
                /* go to wait sleep cmd*/
                media_printf(_T("It will wait sleep cmd\n"));
                l_tMediaCB.eSubState = MEDIA_STATE_STEP_1;
                OS_PostFullMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_CMD,SID_MCU_TX_CMD, UICC_POWER, OP_APU_SLEEP_ON, 0,0);
            }
            else
            {
                /* go to wait sleep io*/
                l_tMediaCB.eSubState = MEDIA_STATE_STEP_2;
            }
            l_tMediaCB.iTimer = 0;
           
        break;
        case MEDIA_STATE_STEP_1:
            /*wait for cmd*/
            if(0 == l_tMediaCB.uDevFlag.field.bDevConnect
               || l_tMediaCB.iTimer > _APU_WAIT_SLEEP_CMD_TIMING)
            {
                l_tMediaCB.eSubState = MEDIA_STATE_STEP_2;
                l_tMediaCB.iTimer = 0;
                media_printf(_T("APU App pwr off ready\n"));
            }
	     if(l_tMediaCB.ePmState < OP_PM_STATE_WAIT_SLEEP)
            {
                MEDIA_EnterState(MEDIA_STATE_RUNNING);                   
            } 
            else if(OP_PM_STATE_OFF == l_tMediaCB.ePmState)
            {
                MEDIA_EnterState(MEDIA_STATE_OFF); 
            }
        break;
        case MEDIA_STATE_STEP_2:
		MEDIA_EnterState(MEDIA_STATE_OFF); 
		IO_Set(IO_IDX_APU_RESET, PIN_OUTPUT,VALID); 
        break;
        default:
	  break;

    }
}

void MEDIA_OffHandle(void)
{
    switch(l_tMediaCB.eSubState)
    {
        case MEDIA_STATE_STEP_0:
		media_printf(_T("Media off handler\n"));
	     	OS_PostMsgDir(&l_tMediaTaskCB,MS_SYS_APU_INFO,OP_DEV_STATE_OFF,NULL);
		l_tMediaCB.eSubState++;
        break;
	 case MEDIA_STATE_STEP_1:
	 	if(l_tMediaCB.ePmState
	           && l_tMediaCB.ePmState < OP_PM_STATE_SLEEP)
	        {
	        if(HMIStatusFlag.g_tCanbusWakeUpFlag == 0) //snake20170207
				MEDIA_EnterState(MEDIA_STATE_START);
			
	        }
	 break;
	 default:
	 	break;
    }
}
/*
 * 在售后维修或内部验证过程中，如果APU需要用电脑的升级工具进行更新OS软件，
 * MCU进入下面的升级过程中，MCU不对核心板复位，直到MCU断电重启才能退出。
 * 2015-10-26 by zhaowenlong.
 */

void MEDIA_UpdateHandle(void)
{
	if((l_tMediaCB.ePmState == OP_PM_STATE_OFF) ||
	   (l_tMediaCB.ePmState == OP_PM_STATE_LVI))
	 {
		MEDIA_EnterState(MEDIA_STATE_OFF);
	 }
	else if(l_tMediaTftCB.GpioState == TFT_EVENT_OK)
	{
		l_tMediaCB.cCnt = 0;
		l_tMediaCB.iTimer = 0;			
		_SendMsgToVideo(MS_PM_TFT_8836,0,NULL);
		MEDIA_EnterState(MEDIA_STATE_RUNNING);
		l_tMediaCB.uDevFlag.field.bUpData = 0;
	}
}

uint8_t MEDIA_Init(void)
{
    API_MemClear((uint8_t*)&l_tMediaCB,sizeof(tMEDIA_CTRL_BLOCK));
    l_tMediaCB.eBakState = 0xff;
    MEDIA_TftResetInit();
    MEDIA_EnterState(MEDIA_STATE_START);
    if(!OS_RamCheck((void*)&g_tApuDevState,(sizeof(tAPU_DEV_BLOCK)-2),(void*)(&(g_tApuDevState.iCheckSum))))
    {
         API_MemClear((uint8_t*)&g_tApuDevState,sizeof(tAPU_DEV_BLOCK));
         OS_CreateRamChkBlock((void*)&g_tApuDevState,(sizeof(tAPU_DEV_BLOCK)-2),(void*)(&(g_tApuDevState.iCheckSum)));
    }

    media_printf(_T("Media task start\n"));
    return TRUE;
}

uint8_t MEDIA_DInit(void)
{
    media_printf(_T("Media task stop\n"));
    IO_Set(IO_IDX_USB_HOST, PIN_OUTPUT,VALID); 	//Select USB slave mode
    MEDIA_EnterState(MEDIA_STATE_OFF);
    return TRUE;
}


void MEDIA_MsgHandle(tMSG_BUF *p_tMsg)
{
    uint16_t iMsgClass = p_tMsg->Id;
    uint16_t Op = p_tMsg->iSid;
     uint8_t msg[5]={0};
    if(iMsgClass == MS_PM_STATE)
    {
            
        switch(Op)
        {
            case OP_PM_STATE_ON:
            case OP_PM_STATE_STANDBY:
                if(!OS_TaskIsActive(TASK_ID_MEDIA))
                {
                    (void)OS_TaskStart(TASK_ID_MEDIA);
                } 
            break;
            case OP_PM_STATE_LVI:
                if(OS_TaskIsActive(TASK_ID_MEDIA))
                {
                        MEDIA_EnterState(MEDIA_STATE_OFF);
                        Op = OP_PM_STATE_OFF;
                }
            break;
            case OP_PM_STATE_BATERR:
                Op = OP_PM_STATE_WAIT_SLEEP;
            break;

            case OP_PM_STATE_OFF:
                Op = OP_PM_STATE_OFF;
            default:
		    break;
        }
        l_tMediaCB.ePmState = (eOP_PM_STATE)Op;
        media_printf(_T("MDI change PM = %d\n", l_tMediaCB.ePmState));
    }
    else if(iMsgClass == MS_SYS_APU_INFO)
    {      
            switch(Op)
            {
                case OP_DEV_STATE_CONNECTED:
		media_printf(_T("APU Connected---\n"));
		l_tMediaCB.uDevFlag.field.bDevConnect = 1;

		if(fTw8836.ADI7186InitProgramme == 1)//判断ADV7186的参数是否写完...
		{
			if(IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE))//snake20161101
			{
				//发送亮屏信号 
				PM_TftPowerSet(ON,0);
				g_tMcuDevState.uIOState.bits.LCD_Disp = 1;//在PM_TftPowerSet函数中发送了状态标志...
				_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
			}
		}
		isOsNormalStart = 1;
		l_tMediaCB.uDevFlag.field.bTestMode = 0;
		_SendMsgToHMI(MS_SYS_APU_INFO,Op,NULL);

		#ifdef R103_H15T_OVERSEAS //如果是海外版,强制设置为运动型   海外版的默认车型为运动型...
			CAN_LoadDefaultEOLByCarType(l_tBusData.DID_F1FA_DATA,CAR_TYPE,DID_F1FA_LENGTH);
			media_printf(_T("this car type is R103-H15T_OVERSEAS!!!!!!!!\n"));
		#endif

		media_printf(_T("l_tBusData.DID_ID_F1FA: %x %x %x %x %x %x\n",l_tBusData.DID_F1FA_DATA[0],l_tBusData.DID_F1FA_DATA[1],
			l_tBusData.DID_F1FA_DATA[2],l_tBusData.DID_F1FA_DATA[3],l_tBusData.DID_F1FA_DATA[4],l_tBusData.DID_F1FA_DATA[5]));
		CANAPI_LoadEOLInfo(DID_ID_F1FA,l_tBusData.DID_F1FA_DATA,DID_F1FA_LENGTH);


		/*
		*  在正常工作过程后，如果核心板异常自动复位，
		*  在核心板起来发送OS_RADAY 后，MCU需要改变状态机，重新
		*  走一遍开机同步流程。 2015-8-24 by ZWL.
		*/
		if((l_tMediaCB.eState == MEDIA_STATE_RUNNING) && (l_tMediaCB.eSyncState > MEDIA_STATE_STEP_1))
		{
			l_tMediaCB.eSubState = MEDIA_STATE_STEP_1;
			l_tMediaCB.eSyncState = MEDIA_STATE_STEP_1;
		}
                break;
                case OP_DEV_STATE_UPDATA:
                    l_tMediaCB.uDevFlag.field.bDevConnect = 1;
                    l_tMediaCB.uDevFlag.field.bUpData = 1;
					media_printf(_T("DVD enter updata mode......\n"));
                break;
                case OP_DEV_STATE_SLEEP_READY: 
                    media_printf(_T("APU APP Power Off Ready---\n"));
                    l_tMediaCB.uDevFlag.field.bDevConnect = 0;
                break;
                case OP_DEV_STATE_SLEEP:
                    media_printf(_T("APU Sleep---\n"));
                    l_tMediaCB.uDevFlag.field.bDevConnect = 0;
                    _SendMsgToHMI(MS_SYS_APU_INFO,OP_DEV_STATE_SLEEP,NULL);
                break;
                case OP_DEV_STATE_ERR:
                    l_tMediaCB.uDevFlag.field.bDevConnect = 0;
                    OS_TaskStop(TASK_ID_MEDIA_DRV);
                    l_tMediaCB.eSubState = MEDIA_STATE_STEP_0;
                    l_tMediaCB.eState = MEDIA_STATE_START;
                    
                break;
                case OP_DEV_STATE_RESET:
                     if(NULL == p_tMsg->uData.p_cData)
                     {
                         DI();
                         //Rear System
                         IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
                         IO_Set(IO_IDX_TFT_EN_IO,PIN_OUTPUT,OFF);
                         API_LoopDleay(60000);
                         IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
                         IO_Set(IO_IDX_APU_RESET,PIN_OUTPUT,VALID);
				API_LoopDleay(60000);
				API_LoopDleay(60000);
				API_LoopDleay(60000);		
                         PM_UnitPowerSet(PM_UNIT_ALL,OFF);
                         while(1){};
                     }
                break;
                case OP_DEV_STATE_TEST:
			 if(NULL == p_tMsg->uData.p_cData)
			 {
			      isOsNormalStart = 0;
				l_tMediaCB.uDevFlag.field.bTestMode = 1;
			 }
			 else
			 {
			      isOsNormalStart = 1;
				l_tMediaCB.uDevFlag.field.bTestMode = 0;
			 }
                break;
                case OP_DEV_STATE_LOCK:
			l_tMediaCB.uDevFlag.field.bUnLocked = 0;
                    OS_PostFullMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_CMD,SID_MCU_TX_CMD,UICC_OPEN_MENU,0x04,0,0);
                break;  
		   case OP_DEV_STATE_LINKREQ:
			if(l_tMediaCB.uDevFlag.field.bAPUCheckEn)
			{
				l_tMediaCB.iTimer = 0;		//clear counter.
				l_tMediaCB.cCnt = 0;
			}
			break;
		  case OP_DEV_STATE_NORMAL:
		  case OP_DEV_STATE_ENTER:
			 l_tMediaCB.uDevFlag.field.bOSEnter = 1;
			 if(0 == l_tMediaCB.uDevFlag.field.bUnLocked)
			 {
				_SendMsgToAudio(MS_SYS_APU_INFO,OP_DEV_STATE_ENTER,NULL);
			 }
			 l_tMediaCB.uDevFlag.field.bUnLocked = 1;
			 g_tSysRomData.DevelopFlag  = 0;//将开发者模式的状态清除...
			_SendMsgToHMI(MS_SYS_APU_INFO,OP_DEV_STATE_NORMAL,NULL);
			break;
		  case OP_DEV_STATE_BOOTOK:
			l_tMediaCB.uDevFlag.field.bDevAwake = 1;
			media_printf(_T("Receive android bsp UART Msg--\n"));
			break;
		  case OP_DEV_STATE_POWERON:
		  	if(!g_tSysSettingRomData.uApuFuncFlag.field.bSysPowerOn)
		  	{
				g_tSysSettingRomData.uApuFuncFlag.field.bSysPowerOn = 1;
				OS_CreateRamChkBlock((void*)&g_tSysSettingRomData,
										sizeof(tSYS_SETTING_ROM_DATA)-2,
										&(g_tSysSettingRomData.iCheckSum));
			}
			_SendMsgToHMI(MS_SYS_APU_INFO,Op,NULL);
		  	break;
		  case OP_DEV_STATE_POWEROFF:
		  	if(g_tSysSettingRomData.uApuFuncFlag.field.bSysPowerOn)
		  	{
				g_tSysSettingRomData.uApuFuncFlag.field.bSysPowerOn = 0;
				OS_CreateRamChkBlock((void*)&g_tSysSettingRomData,
										sizeof(tSYS_SETTING_ROM_DATA)-2,
										&(g_tSysSettingRomData.iCheckSum));
			}
			_SendMsgToHMI(MS_SYS_APU_INFO,Op,NULL);
		  	break;
               default:
                    _SendMsgToHMI(MS_SYS_APU_INFO,Op,NULL);
			break;
            }
    }
}

void MEDIA_Task(EVENT iEvt,eTASK_STATE eState)
{
    tMSG_BUF  tMsg;
    /*Task msg handle*/
    if(iEvt & EVT_MSG_READY)
    {
        if(QUE_ERR_NONE == OS_GetMsgDir(&l_tMediaTaskCB,&tMsg))
        {
            MEDIA_MsgHandle(&tMsg);
        }
    }
     if(iEvt & EVT_RTC_SECOND)
     {
     		l_tMediaCB.SecondCnt++;
		l_tMediaCB.cSysTimeSendCnt++;
		if(l_tMediaCB.uDevFlag.field.bDevConnect)
		{
			
			if(l_tMediaCB.SecondCnt>=10)
			{
				l_tMediaCB.SecondCnt = 0;
				OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_SYS_STATE_INFO,NULL);
			}
		}
		   // media_printf(_T("******** l_tMediaTftCB.GpioState= %d\n", l_tMediaTftCB.GpioState)); 
		  // media_printf(_T("******** l_tMediaCB.uDevFlag.field.bDevConnect= %d\n", l_tMediaCB.uDevFlag.field.bDevConnect)); 
			
     }

    if(iEvt & EVT_TASK_TICK_READY)
    {
        l_tMediaCB.iTimer ++;
	 if(l_tMediaTftCB.tftResetDelay>0)
	 {
		l_tMediaTftCB.tftResetDelay--;
	 }
	
        if( TASK_STATE_RUNNING == eState )
        {    
            eMEDIA_STATE eMediaState = l_tMediaCB.eState;
            switch(eMediaState)
            {
                
                /*Start, Power on CPU*/
                case MEDIA_STATE_START:
			MEDIA_StartHandle();
                break;
    
                /*CPU is running*/
                case MEDIA_STATE_RUNNING:		
			MEDIA_RunningHandle();
                break;
    
                /*Wait sleep,Send cmd to cpu*/
                case MEDIA_STATE_WAIT_SLEEP:
			MEDIA_WaitSleepHandle();
                break;
    
                /*Sleep,wait power off of awake*/
                case MEDIA_STATE_SLEEP:
			MEDIA_SleepHandle();
                break;         
		   case MEDIA_STATE_LVI:
                case MEDIA_STATE_OFF:
			MEDIA_OffHandle();
                break;
		   case MEDIA_STATE_UPDATE:
		   	MEDIA_UpdateHandle();
		   	break;
                default:
			break;
            }
             MEDIA_TftResetRoutine();
        }

	g_tSysStateDbgInfo.MediaState = (l_tMediaCB.eState<<4)|(l_tMediaCB.eSubState);
	g_tSysStateDbgInfo.MediaDevFlag = l_tMediaCB.uDevFlag.byte;
    }
}

void MDI_SendUiccToMedia(uint8_t UiccCode, uint8_t Param)
{
	if(l_tMediaCB.uDevFlag.field.bDevConnect)
	{
		 OS_PostFullMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_CMD,SID_MCU_TX_CMD, UiccCode, Param, 0,0);
	}
}

////////////////////////////////////////////////////////////////////////////////


static const tTASK_BLOCK lc_tMediaTCB = {
    "MEDIA",
    _MEDIA_TASK_TICK_,
    _MEDIA_CORE_TICK_,
    MEDIA_Task,
    MEDIA_Init,
    MEDIA_DInit,
};


bool MDI_TaskCreate(void)
{
    uint8_t re = OS_TaskCreate(TASK_ID_MEDIA,&l_tMediaTaskCB,&lc_tMediaTCB,&l_tMediaMsgQue,l_tMediaMsgBuf,D_MEDIA_MSG_QUE_DEEP);
    re &= MDI_DriverCreate();
    return re;
}


/*Media Msg send fuction*/
/******************************************************************************/
eQUE_ERROR MDI_SendFullMsgToMedia(uint16_t id,uint16_t iSid,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(id == MS_UI_UPLOAD_INFO)
    {

        if(l_tMediaCB.uDevFlag.field.bDevConnect)
        {
            re = OS_PostFullMsgDir(&l_tMediaDrvTaskCB,(MSG_ID)(iSid>>8),(uint16_t)iSid,d0,d1,d2,d3);
        }
        else
        {
            media_printf(_T("In CommState %d can't send\n",l_tMediaCB.eState));
        }

    }
    else
    {
        re = OS_PostFullMsgDir(&l_tMediaTaskCB,(MSG_ID)(id),(uint16_t)iSid,d0,d1,d2,d3);
    }

    return re;
}


eQUE_ERROR MDI_SendMsgToMedia(uint16_t id,uint16_t iSid,uint8_t* p_cBuf)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(id == MS_UI_UPLOAD_INFO)
    {
        if(l_tMediaCB.uDevFlag.field.bDevConnect)
        {
            re = OS_PostMsgDir(&l_tMediaDrvTaskCB,(MSG_ID)(iSid>>8),(uint16_t)iSid,(void*)p_cBuf);
        }
        else
        {
            media_printf(_T("In CommState %d can't send\n",l_tMediaCB.eState));
        }
  #if 0      
        if(FristEolReq==1)
        {
		FristEolReq=0;
		re = OS_PostMsgDir(&l_tMediaDrvTaskCB,(MSG_ID)(iSid>>8),(uint16_t)iSid,(void*)p_cBuf);
        }
#endif		
    }
    else
    {
        re = OS_PostMsgDir(&l_tMediaTaskCB,(MSG_ID)(id),(uint16_t)iSid,(void*)p_cBuf);
    }

    return re;
}

eQUE_ERROR MDI_InsertMsgToMedia(uint16_t id,uint16_t iSid,uint8_t* p_cBuf)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(id == MS_UI_UPLOAD_INFO)
    {
        if(l_tMediaCB.uDevFlag.field.bDevConnect)
        {
            re = OS_InsertMsgDir(&l_tMediaDrvTaskCB,(MSG_ID)(iSid>>8),(uint16_t)iSid,(void*)p_cBuf,1);
        }
        else
        {
            media_printf(_T("In CommState %d can't send\n",l_tMediaCB.eState));
        }

    }
    else
    {
        re = OS_InsertMsgDir(&l_tMediaTaskCB,(MSG_ID)(id),(uint16_t)iSid,(void*)p_cBuf,1);
    }

    return re;
}



