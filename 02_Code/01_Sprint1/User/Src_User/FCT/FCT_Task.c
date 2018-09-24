/**********************************************************
 * @file       Task_FCT.c
 * @purpose    Definition for one wire communication to MPEG
 * @version 0.01
 * @date        21. Jan. 2013
 * @author    Plage
 * @brief
 ***********************************************************
 *    History:                                                                    
 *    <write/modify>        <time>        <version >      <desc>        
 *    Plage                    21. Jan. 2013     v0.01        created
 *    
  **********************************************************/

#define _TASK_FCT_C
#include "..\config\inc.h"

#define D_FCT_MSG_QUE_DEEP           20

#define _FCT_TASK_TIMING_              _2MS_
#define _FCT_CORE_TIMING_              _10MS_
#define _FCT_TASK_TICK_                _set_timing_xms_base_core_tick(_FCT_TASK_TIMING_)
#define _FCT_CORE_TICK_                _set_timing_xms_base_core_tick(_FCT_CORE_TIMING_)

tRING_QUE l_tFctMsgQue;
tMSG_BUF la_tFctMsgBuf[D_FCT_MSG_QUE_DEEP];

#if 0
  uint8_t  *paFctSoftVer[]=
{
    g_tFCT.tDataBuf.SoftOsVer_25,
    g_tFCT.tDataBuf.SoftBootVer_25,
    g_tFCT.tDataBuf.SoftAppVer_30,
    g_tFCT.tDataBuf.SoftMcuVer_30,
    g_tFCT.tDataBuf.SoftMpegVer_39,
    g_tFCT.tDataBuf.SoftDivxVer_13,
    g_tFCT.tDataBuf.SoftUuidVer_19,
    g_tFCT.tDataBuf.SoftWifiVer_20,
    g_tFCT.tDataBuf.SoftMapVer_25,
};
#endif

   uint8_t aFctSoftVerLength[]=
{
    SOFT_OS_VER_25,
    SOFT_BOOT_VER_25,
    SOFT_APP_VER_30,
    SOFT_MCU_VER_30,
    SOFT_MPEG_VER_39,
    SOFT_DIVX_VER_13,
    SOFT_UUID_VER_19,
    SOFT_WIFI_VER_20,
    SOFT_MAP_VER_25,
};

void FctTest(void)
{    
	static uint8_t Track;
	Track ++ ;
	if(Track> 6)
	Track = 1 ;

	if(Track == 1)
	{
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][0] = 0x0E ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][1] = 0x80 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][2] = 0x01 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][3] = 0x02 ;   
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][4] = 0x46 ;   

		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][5] = 0x43 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][6] = 0x54 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][7] = 0x49 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][8] = 0x4E ;   
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][9] = 0x00 ;   
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][10] = 0x16 ;   
		FCT_SetPasswordFlag(TRUE) ;
		FCT_SetManagerState(PASSWORD_STATE);
	}
	else 	if(Track == 2)
	{
	#if 1
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][0] = 0x08 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][1] = 0x01 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][2] = 0x01 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][3] = 0x02 ;   
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][4] = SOURCE_SD_AUDIO ;    
		FCT_REC_FLAG = TRUE ;
		g_tFCT.tTomcuRx.cRxRecIndex ++ ;
		g_tFCT.tTomcuRx.cRxRecIndex %= TOMCU_RX_COM_SIZE ;
		#endif
		//_SendMsgToSRC(MS_SRC_SET_FRONT_UIID,SOURCE_F_AUX,NULL);	 
	}
	else 	if(Track == 6)
	{
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][0] = 0x0C ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][1] = 0x80 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][2] = 0x02 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][3] = 0x02 ;   
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][4] = 0x46 ;   

		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][5] = 0x43 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][6] = 0x54 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][7] = 0x4E ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][8] = 0x4F ;   
		FCT_SetPasswordFlag(TRUE) ;
		FCT_SetManagerState(PASSWORD_STATE);
	}
	else 	if(Track == 7)
	{
	 	_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_CMD, APU_FCT_LOAD_FACTORY,0,0,0);
	}
	else
	{
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][0] = 0x08 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][1] = 0x03 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][2] = 0x01 ;    
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][3] = 0x02 ;   
		g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][4] = Track ;    
		FCT_REC_FLAG = TRUE ;
		g_tFCT.tTomcuRx.cRxRecIndex ++ ;
		g_tFCT.tTomcuRx.cRxRecIndex %= TOMCU_RX_COM_SIZE ;
	}
}




/**********************************************************
 * @function    FCT_Password
 * @brief      SWC  function test
 * @param       
 *                    
 * @retval     None
 **********************************************************/
void FCT_Password(void)
{
    if(PC_TO_FCT_SID == FCT_START)
    {
        if ((g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][4] = 'F')
            &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][5] = 'C')
            &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][6] = 'T')
            &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][7] = 'I')
            &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][8] = 'N')
           )
        {
         FCT_SendFCTEnter();  
         FCT_SetSwFlag(TRUE);
         FCT_SetManagerState(WORK_STATE);
	 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_CMD, APU_FCT_TEST_START,0,0,0);
        }
    }
    else if(PC_TO_FCT_SID == FCT_OVER)
    {
        if ((g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][4] = 'F')
            &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][5] = 'C')
            &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][6] = 'T')
            &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][7] = 'N')
            &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][8] = 'O')
           )
        {
            FCT_SendFCTOut() ;
            FCT_SetSwFlag(FALSE) ;
            FCT_SetManagerState(WORK_STATE);
	 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_CMD, APU_FCT_TEST_FINISHED,0,0,0);
        }
    }
}

/* 自动测试功能 开关标志  */
uint8_t FCT_GetPasswordFlag(void)
{
     return  FCT_PASSWORD_FLAG ;
}
/* 自动测试功能 开关标志设置  */
void FCT_SetPasswordFlag( uint8_t State)
{
    if( State == TRUE)
        FCT_PASSWORD_FLAG = TRUE ;
    else
        FCT_PASSWORD_FLAG = FALSE ;
}

/* 自动测试功能 开关标志  */
uint8_t FCT_GetSwFlag(void)
{
     return  FCT_FLAG ;
}
/* 自动测试功能 开关标志设置  */
void FCT_SetSwFlag( uint8_t State)
{
    if( State == TRUE)
        FCT_FLAG = TRUE ;
    else
        FCT_FLAG = FALSE ;
}
/* 重复发送标准  */
uint8_t FCT_GetRepeatFlag(void)
{
     return  FCT_REPEAT_FLAG ;
}
/* 重复发送标准设置  */
void FCT_SetRepeatFlag( uint8_t State)
{
    if( State == TRUE)
        FCT_REPEAT_FLAG = TRUE ;
    else
        FCT_REPEAT_FLAG = FALSE ;
}
/*    */

uint8_t FCT_GetComOverFlag(void)
{
     return  FCT_COM_OVER_FLAG ;
}
/*    */

void FCT_SetComOverFlag( uint8_t State)
{
    if( State == TRUE)
        FCT_COM_OVER_FLAG = TRUE ;
    else
        FCT_COM_OVER_FLAG = FALSE ;
}

/*发送完成 ，等待应答标志*/
uint8_t FCT_GetSendOKWaitAckFlag(void)
{
     return  SEND_OK_WAIT_ACK ;
}
/*发送完成 ，等待应答标志设置*/

void FCT_SetSendOKWaitAckFlag( uint8_t State)
{
    if( State == TRUE)
        SEND_OK_WAIT_ACK = TRUE ;
    else
        SEND_OK_WAIT_ACK = FALSE ;
}


uint8_t FCT_GetStateSameFlag(void)
{
     return  g_tFCT.tFCTMsgDef.tBit.StateSameFlag  ;
}

void FCT_SetStateSameFlag( uint8_t State)
{
    if( State == TRUE)
    {
        g_tFCT.tFctCount.u16TUpdataMsgToPcTimer = 25 ;
        g_tFCT.tFCTMsgDef.tBit.StateSameFlag = TRUE ;
    }
    else
         g_tFCT.tFCTMsgDef.tBit.StateSameFlag = FALSE ;
}


void FCTInit(void)
{
    // FCT_UARTA3_Init();
    // FCT_UARTA3_Start();
    g_tFCT.tUartRecDataStep =  FCT_FRAME_HEAD_FIRST;
    FCT_REC_FLAG = FALSE ;
    FCT_SetPasswordFlag(FALSE) ;
    FCT_SetSwFlag (FALSE) ;
    FCT_SetRepeatFlag(FALSE);
    FCT_RepeatSendCountZero();
    FCT_SetSendOKWaitAckFlag(FALSE);
    FCT_SetManagerState(PASSWORD_STATE);
    g_tFCT.tTopcTx.gpUarta3TxAddress = NULL ;
    g_tFCT.tTopcTx.gUarta3TxCnt = 0 ;
    g_tFCT.ptFctMsg.Id = OP_FCT_TO_HMI_START;
}

/**********************************************************
 * @function    FCT_ColdOrWarmInit
 * @brief      Cold Start, Reset All of Audio 
 * @param      None
 * @retval     None
 **********************************************************/
uint8_t FCT_ColdOrWarmInit(void) 
{
    //Tuner Task Tick Reset
    FCTInit();
    return 1 ;
}

uint8_t FCT_Disable(void)
{
  //  FCT_UARTA3_Stop();
    return 1 ;
}


void FCT_PasswordManage(void)
{
    
#if 1
    if(FCT_GetPasswordFlag() == TRUE)
    {
        FCT_SetPasswordFlag(FALSE) ;
        
         if(PC_TO_FCT_GID == OP_FCT_PASSWORD_128)
            FCT_Password();
    }
#else
     if(PC_TO_FCT_GID == OP_FCT_PASSWORD_128)
        FCT_Password();
#endif
}

void FCT_RepeatSendCountZero(void)
{
    g_tFCT.tAckSystem.RepSendCount = 0 ;
}


void FCT_SetRepSendCause(uint8_t uCause)
{
    g_tFCT.tAckSystem.RepSendCause = uCause ;
}


void FCT_SendRepeatManage(void)
{

    if (  !FCT_GetSwFlag() )
        return ;
    
    if ( g_tFCT.tAckSystem.RepSendCause == ACK_ERROR)
        g_tFCT.tFctCount.cAckErrorCoun++ ;
    
    if (g_tFCT.tAckSystem.RepSendCause == NACK_DELAYMS_WAIT) //发了数据 200MS内没有应答， 
    {
        FCT_SetRepSendCause(REP_STATE_NULL);
        g_tFCT.tFctCount.cAckErrorCoun = 0 ;
        FCT_SetRepeatFlag(FALSE);
        
         FCT_UARTA3_SendData(g_tFCT.tAckSystem.SendArray,g_tFCT.tAckSystem.SendArray[2]);
        
        g_tFCT.tAckSystem.RepSendCount ++ ;
        if(g_tFCT.tAckSystem.RepSendCount >=4)
        {
            g_tFCT.tAckSystem.RepSendCount = 0 ;
            FCT_SetSwFlag(FALSE);
        }        
    }
    else if ((FCT_GetRepeatFlag()) &&( g_tFCT.tAckSystem.RepSendCause == ACK_ERROR)&&(g_tFCT.tFctCount.cAckErrorCoun >=20))//发了数据 有应答，但是应答表示帧错误的信息
    {
        FCT_SetRepSendCause(REP_STATE_NULL);
        g_tFCT.tFctCount.cAckErrorCoun = 0 ;
        FCT_SetRepeatFlag(FALSE);
        
         FCT_UARTA3_SendData(g_tFCT.tAckSystem.SendArray,g_tFCT.tAckSystem.SendArray[2]);    
        g_tFCT.tAckSystem.RepSendCount ++ ;
        if(g_tFCT.tAckSystem.RepSendCount >=4)
        {
            g_tFCT.tAckSystem.RepSendCount = 0 ;
            FCT_SetSwFlag(FALSE);
        }        
    }
    
}

void  FCT_HmiIdToPcId(uint8_t Gid, uint8_t Sid, tMSG_BUF* p_tMsgBuf )
{
    uint8_t Couent ;
    uint8_t Array[5];
    uint8_t *pt ;
    pt = p_tMsgBuf->uData.p_cData ;
    Array[4] = 0xff ;
    //Couent = OP_FCT_SOURCE_1 ;
    Couent = 0 ;
     if(((Gid == OP_FCT_RADIO_4 )&&(Sid == SET_FREQ ))
        ||((Gid == OP_FCT_RADIO_4 )&&(Sid == RETURN_CUR_FREQ ))
        ||((Gid == OP_FCT_GPS_6 )&&(Sid == LONGITUDE_LATITUDE ))
        ||((Gid == OP_FCT_MEDIA_3 )&&(Sid == MEDIA_CONTROL ))
        ||((Gid == OP_FCT_SOURCE_1 )&&(Sid == SOURCE_SW ))
        )
    {
        Array[4] = 2 ;
        Array[0] = p_tMsgBuf->uData.a_cData[0] ;
        Array[1] = p_tMsgBuf->uData.a_cData[1] ;
        FCT_SendDataResult(Gid , Sid,Array , Array[4]);
    }
    else if(((Gid == OP_FCT_VIDEO_SET_12 )&&(Sid == VIDEO_SET ))
        ||((Gid == OP_FCT_CUR_STATE_15 )&&(Sid == CUR_STATE ))
        )
    {
        Array[4] = 3 ;
        Array[0] = p_tMsgBuf->uData.a_cData[0] ;
        Array[1] = p_tMsgBuf->uData.a_cData[1] ;
        Array[2] = p_tMsgBuf->uData.a_cData[2] ;
        FCT_SendDataResult(Gid , Sid,Array , Array[4]);
    }
    else if((Gid == OP_FCT_RADIO_4 )&&(Sid == RDS_SATE ))
    {
        g_tFCT.tDataBuf.RdsInfo_10[0] = RDS_INFO - 1 ;
        for(Couent = 0 ; Couent < (RDS_INFO - 1) ; Couent ++)
        {
            g_tFCT.tDataBuf.RdsInfo_10[Couent + 1] = pt[Couent];
        }
        FCT_SendDataResult(Gid , Sid,g_tFCT.tDataBuf.RdsInfo_10 , (RDS_INFO - 1));
    }
    else if(Gid == OP_FCT_BT_5 )
    {
	if(Sid == RET_MAC_ADDRESS )
	{
		 if(g_tFCT.tDataBuf.BTMacAddL >= BT_MAC_ADD)
		 	g_tFCT.tDataBuf.BTMacAddL = BT_MAC_ADD ;
	 
	        for(Couent = 0 ; Couent < (g_tFCT.tDataBuf.BTMacAddL - 1) ; Couent ++)
	        {
	            g_tFCT.tDataBuf.BTMacAdd_16[Couent] = pt[Couent];
	        }
	        FCT_SendDataResult(Gid , Sid,g_tFCT.tDataBuf.BTMacAdd_16 , g_tFCT.tDataBuf.BTMacAddL);
	}
	else if(Sid == RET_WRITE_BT_NAME )
	{
		 if(g_tFCT.tDataBuf.BTDevNameL >= BT_DEV_NAME)
		 	g_tFCT.tDataBuf.BTDevNameL = BT_DEV_NAME ;
	 
	        for(Couent = 0 ; Couent < (g_tFCT.tDataBuf.BTDevNameL - 1) ; Couent ++)
	        {
	            g_tFCT.tDataBuf.BTDevName_16[Couent] = pt[Couent];
	        }
	        FCT_SendDataResult(Gid , Sid,g_tFCT.tDataBuf.BTDevName_16 , g_tFCT.tDataBuf.BTDevNameL);
	}
	else if(Sid == RET_VER_ADD_NAME )
	{
		 if(g_tFCT.tDataBuf.BTVerL >= BT_SOFT_VER)
		 	g_tFCT.tDataBuf.BTVerL = BT_SOFT_VER ;
	 
	        for(Couent = 0 ; Couent < (g_tFCT.tDataBuf.BTVerL - 1) ; Couent ++)
	        {
	            g_tFCT.tDataBuf.BTVer_16[Couent] = pt[Couent];
	        }
	        FCT_SendDataResult(Gid , Sid,g_tFCT.tDataBuf.BTVer_16 , g_tFCT.tDataBuf.BTVerL);
	}

    }
    else if((Gid == OP_FCT_GPS_6 )&&(Sid == RET_INFO ))
    {
	 if(g_tFCT.tDataBuf.GPSInfoL>= GPS_INFO)
	 	g_tFCT.tDataBuf.GPSInfoL = GPS_INFO ;	
        for(Couent = 0 ; Couent < (g_tFCT.tDataBuf.GPSInfoL - 1) ; Couent ++)
        {
            g_tFCT.tDataBuf.GPSInfo_22[Couent + 1] = pt[Couent];
        }
        FCT_SendDataResult(Gid , Sid,g_tFCT.tDataBuf.GPSInfo_22 , g_tFCT.tDataBuf.GPSInfoL);
    }
    else if((Gid == OP_FCT_TMPS_8 )&&(Sid == PARTNERSHIP_RET_INFO ))
    {
        g_tFCT.tDataBuf.TmpsInfo_26[0] = TMPS_INFO - 1 ;
        for(Couent = 0 ; Couent < (TMPS_INFO - 1) ; Couent ++)
        {
            g_tFCT.tDataBuf.TmpsInfo_26[Couent + 1] = pt[Couent];
        }
        FCT_SendDataResult(Gid , Sid,g_tFCT.tDataBuf.TmpsInfo_26 , (TMPS_INFO - 1));
    }
    else if((Gid == OP_FCT_AUDIO_SET_11 )&&(Sid == AUDIO_SET_VAL ))
    {
        g_tFCT.tDataBuf.AudioSet_30[0] = AUDIO_SET_VAL - 1 ;
        for(Couent = 0 ; Couent < (AUDIO_SET_VAL - 1) ; Couent ++)
        {
            g_tFCT.tDataBuf.AudioSet_30[Couent + 1] = pt[Couent];
        }
        FCT_SendDataResult(Gid , Sid,g_tFCT.tDataBuf.AudioSet_30 , (AUDIO_SET_VAL - 1));
    }

    else if((Gid == OP_FCT_SEQ_NUM_17 )&&(Sid == SEQ_NUM ))
    {
        g_tFCT.tDataBuf.SeqNum_39[0] = SEQ_NUM_39 - 1 ;
        for(Couent = 0 ; Couent < (SEQ_NUM_39 - 1) ; Couent ++)
        {
            g_tFCT.tDataBuf.SeqNum_39[Couent + 1] = pt[Couent];
        }
        FCT_SendDataResult(Gid , Sid,g_tFCT.tDataBuf.SeqNum_39 , (SEQ_NUM - 1));
    }
    else if((Gid == OP_FCT_SOFT_VER_18 ) 
        &&((Sid >= SOFT_OS_VER ) && (Sid <= SOFT_MAP_VER )))
    {
	 if(g_tFCT.tDataBuf.SoftVerL>= SOFT_VER_40)
	 	g_tFCT.tDataBuf.SoftVerL = SOFT_VER_40 ;	
        for(Couent = 0 ; Couent < g_tFCT.tDataBuf.SoftVerL  ; Couent ++)
        {
            g_tFCT.tDataBuf.SoftVer_40[Couent] = pt[Couent];
        }
        FCT_SendDataResult(Gid , Sid, g_tFCT.tDataBuf.SoftVer_40 , g_tFCT.tDataBuf.SoftVerL );

		
    }
    else
    {
        Array[4] = 1 ;
        Array[0] = p_tMsgBuf->uData.a_cData[0] ;

        if((Gid == OP_FCT_RADIO_4 )&&(Sid == SELECTED_FM_OR_AM ))
        {
            if(TUNER_BAND_FM)
                Array[0] = 0 ;
            else if(TUNER_BAND_AM)
                Array[0] = 1 ;
        }
        if((Gid == OP_FCT_RADIO_4 )&&(Sid == RADIO_SEEK ))
        {
            if(sTuner.uBakSeekState.sSsBitMap.bSeek == 1)
            {
                if(sTuner.bBakSeekDirect == DIRECTION_UP)
                {
                    Array[0] = 0 ;
                }
                else if(sTuner.bBakSeekDirect == DIRECTION_DN)
                {
                    Array[0] = 1 ;
                }
            }
            if(sTuner.uBakSeekState.sSsBitMap.bAutoMemSeek == 1)
                Array[0] = 2 ;

            if(sTuner.uSeekState.SsTotal == 0)
                Array[0] = 3 ;

        }        
        FCT_SendDataResult(Gid , Sid,Array , Array[4]);

    }
}


void FCT_WorkManager(void)
{
uint8_t  Count ;
uint8_t  Global_ID ;
uint8_t  Sub_ID ;

uint8_t  Length ;
#if  0 // 测试用 
     FCT_SetSwFlag(TRUE);
#endif
     if (FCT_REC_FLAG == FALSE)
        return ;
     

    if (  !FCT_GetSwFlag() )
        return ;
    
    Global_ID = g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.uRxProcessIndex][1] ;
    Sub_ID = g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.uRxProcessIndex][2] ;    


    if (g_tFCT.tTomcuRx.cRxRecIndex != g_tFCT.tTomcuRx.uRxProcessIndex)
    {
        Length = g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.uRxProcessIndex][0] ;
        //Global_ID = g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.uRxProcessIndex][1] ;
        //Sub_ID = g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.uRxProcessIndex][2] ;    
        if (Length <= 11)
        {
            for(Count = 0 ; Count <= (Length - 7) ; Count ++)
                
                g_tFCT.sFctInfo.a_cData[Count] = g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.uRxProcessIndex][Count + 4] ;
             _SendFullMsgToHMI((OP_FCT_TO_HMI_START + Global_ID),Sub_ID,  g_tFCT.sFctInfo.a_cData[0],  g_tFCT.sFctInfo.a_cData[1], g_tFCT.sFctInfo.a_cData[2], g_tFCT.sFctInfo.a_cData[3] );
        }
        else
        {
             FCT_DataBufAdd(Global_ID ,Sub_ID, Length );    
            _SendMsgToHMI( (OP_FCT_TO_HMI_START + Global_ID),Sub_ID,  g_tFCT.sFctInfo.p_cData);

        }
        g_tFCT.tTomcuRx.uRxProcessIndex ++ ;
        g_tFCT.tTomcuRx.uRxProcessIndex %= TOPC_TX_COM_SIZE ;    


        if (g_tFCT.tTomcuRx.cRxRecIndex == g_tFCT.tTomcuRx.uRxProcessIndex)
            FCT_REC_FLAG = FALSE ;
    }     
}

uint8_t *  FCT_ArrayDataUp(uint8_t * Array, uint8_t Length)
{
    uint8_t Count ;
    for(Count = 0 ; Count <= (Length - 7) ; Count ++)
        Array[Count ] = g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.uRxProcessIndex][Count + 4] ;
    return Array ;
}

 void FCT_DataBufAdd (uint8_t  Global_ID,uint8_t  S_ID, uint8_t Length)
{
     if ((Global_ID == OP_FCT_BT_5)&&(S_ID == RET_WRITE_BT_NAME))
    {
   	 g_tFCT.tDataBuf.BTDevNameL = Length - 7 + 1;
   	 g_tFCT.tDataBuf.BTDevName_16[0] = APU_FCT_BT_CHG_BT_NAME ;
        g_tFCT.sFctInfo.p_cData = FCT_ArrayDataUp(&g_tFCT.tDataBuf.BTDevName_16[1] ,Length ) ;
    }
    else if ((Global_ID == OP_FCT_BT_5)&&(S_ID == DIAL_UP))
    {
   	 g_tFCT.tDataBuf.BTDialNumL = Length - 7 + 1;
   	 g_tFCT.tDataBuf.BTDialNum_16[0] = APU_FCT_BT_DIAL_CALL ;
        g_tFCT.sFctInfo.p_cData = FCT_ArrayDataUp(&g_tFCT.tDataBuf.BTDialNum_16[1] ,Length ) ;
    }
    else if ((Global_ID == OP_FCT_AUDIO_SET_11)&&(S_ID == AUDIO_SET))
    {
        g_tFCT.sFctInfo.p_cData = FCT_ArrayDataUp(g_tFCT.tDataBuf.AudioSet_30 ,Length ) ;
    }
    else if ((Global_ID == OP_FCT_WIFI_LINK_13)&&(S_ID == WIFI_LINK_AP))
    {
   	 g_tFCT.tDataBuf.WifiApNamePinL = Length - 7 + 1;
   	 g_tFCT.tDataBuf.WifiApNamePin[0] = APU_FCT_WIFI_LINK_AP ;
        g_tFCT.sFctInfo.p_cData = FCT_ArrayDataUp(&g_tFCT.tDataBuf.WifiApNamePin[1] ,Length ) ;
    }
    else if ((Global_ID == OP_FCT_SEQ_NUM_17)&&(S_ID == SEQ_NUM))
    {
        g_tFCT.sFctInfo.p_cData = FCT_ArrayDataUp(g_tFCT.tDataBuf.SeqNum_39 ,Length ) ;
    }        
}
void FCT_SetManagerState(uint8_t uState)
{
    g_tFCT.tPcMesMagState = uState ;
}

 void FCT_MsgToHmiHandler(void)
 {
#if  D_FCT_WAIT_ACK_EN == 0      //test
    FCT_SetSendOKWaitAckFlag(FALSE);
    FCT_SetRepeatFlag(FALSE);
#endif

    
    switch(g_tFCT.tPcMesMagState)
    {
        case PASSWORD_STATE :
        {
            FCT_PasswordManage();
#if  0      //test
            FCT_SetSwFlag(TRUE);
            FCT_SetManagerState(WORK_STATE);     
#endif
        }
        break;
        case WAIT_ACK_STATE :
        {
            g_tFCT.tFctCount.u16NoAckCount ++ ;
            if (g_tFCT.tFctCount.u16NoAckCount >= 50 ) //  大于或等于200MS  没有收到应答信号，重复发送一次
            {
                g_tFCT.tFctCount.u16NoAckCount = 0 ;
                FCT_SetRepSendCause(NACK_DELAYMS_WAIT);
                FCT_SetManagerState(REPEAT_STATE);
#if  D_FCT_WAIT_ACK_EN == 0      //test
            FCT_SetManagerState(WORK_STATE);     
#endif

            }
        }
        break;
        case REPEAT_STATE :
        {
            g_tFCT.tFctCount.u16NoAckCount = 0 ;
            FCT_SendRepeatManage();

#if  D_FCT_WAIT_ACK_EN == 0      //test
            FCT_SetManagerState(WORK_STATE);     
#endif

        }
        break;
        case WORK_STATE :
        {
            g_tFCT.tFctCount.u16NoAckCount = 0 ;
            FCT_WorkManager();
        }
        break;
        default:
            break;
    }
}


 void  FCT_MsgToPcHandler(tMSG_BUF* p_tMsgBuf)
 {
    #define MegID        ( p_tMsgBuf->Id )
    #define MegSubID  (uint8_t)( p_tMsgBuf->iSid)

    if (  !FCT_GetSwFlag() )
        return ;

    if((g_tFCT.ptFctMsg.Id  != MegID) || (g_tFCT.ptFctMsg.iSid  != MegSubID))
        return ;

    if ((MegID > OP_FCT_TO_HMI_START) && (MegID < OP_FCT_TO_HMI_END))
    {
        FCT_HmiIdToPcId(MegID,MegSubID, p_tMsgBuf);
    }
         
}
    
void FctTimerHandler(void)
{
    if(g_tFCT.tFctCount.u16TempTimer > 0 )
        g_tFCT.tFctCount.u16TempTimer -- ;
    if(g_tFCT.tFctCount.u16TUpdataMsgToPcTimer > 0 )
        g_tFCT.tFctCount.u16TUpdataMsgToPcTimer -- ;
    if(g_tFCT.tFctCount.cReMsgDelay > 0 )
        g_tFCT.tFctCount.cReMsgDelay -- ;    
}

void SetUpdataMsgToPcTimer(uint16_t  Val)
{
    g_tFCT.tFctCount.u16TUpdataMsgToPcTimer = Val ;
}


/**********************************************************
 * @function    Task_FCT
 * @brief      a periodic task for TCT module
 * @param      EVENT iEvt:
 *                   eTASK_STATE state:
 * @retval     None
 **********************************************************/
void Task_FCT(EVENT iEvt,eTASK_STATE state)
{
    tMSG_BUF tMsgBuf;

      if( iEvt & EVT_TASK_TICK_READY)    
      {

         FctTimerHandler();

        if (g_tFCT.tFctCount.cReMsgDelay == 0)
        {
            FCT_MsgToHmiHandler();
        }    
     
         
        if (g_tFCT.tFctCount.u16TempTimer == 0)
        {
            g_tFCT.tFctCount.u16TempTimer = 2000 ;
		//	FctTest();	
            //FCT_SendAsk(ACK_OK,22,22);
        }    
        if (g_tFCT.tFctCount.u16TUpdataMsgToPcTimer == 0)
        {
            g_tFCT.tFctCount.u16TUpdataMsgToPcTimer = 25 ;
         //  FCT_DataResultToPc(&g_tFCT.ptFctMsg);
        }        
    }
    else if(iEvt & EVT_MSG_READY)    // Msg Disposal
    {        
        (void)OS_GetMsgDir(&g_tFCT.tFctTaskCB,&tMsgBuf);
         FCT_MsgToPcHandler(&tMsgBuf);
    }

    switch(state)
    {
        case TASK_STATE_RUNNING:
        {
            
     }
        break;
        case TASK_STATE_READY:
        {
         OS_TaskStart(TASK_ID_FCT);
     }
        break;
        case TASK_STATE_STOP:
        {
            
     }
        break;
    }
}

static const tTASK_BLOCK It_fct_task = {
    "FCT",
    _FCT_TASK_TICK_ ,
    _FCT_CORE_TICK_ ,
     Task_FCT,
     FCT_ColdOrWarmInit,
     FCT_Disable,
//     FCT_Disable,
};


uint8_t FCT_TaskCreat(void)
{
    uint8_t ReturnVal;
    OS_TaskCreate(TASK_ID_FCT,&g_tFCT.tFctTaskCB, &It_fct_task,&l_tFctMsgQue,la_tFctMsgBuf,D_FCT_MSG_QUE_DEEP);
    // OS_TaskStart(TASK_ID_FCT);
    return ReturnVal ;
}




