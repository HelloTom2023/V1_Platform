/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CANbus_AppLayer.c
* Target MCU:		V850SJ3
* Module:
* Summary:		CAN module Application layer source code
*----------------------------------------------------------------------------
* Author:			zhaowenlong
* version:			V0.1
* Date:			2013-4-20
* Description:		first version
*----------------------------------------------------------------------------
* Modify:			
* version:
* Date:
* Description:
****************************************************************************/
#define _CAN_MODULE_C
#include "..\..\..\config\inc.h"

#ifdef CAN_MODULE_ENABLE	

#if D_PRINT_EN &&  D_CANBUS_APP_DBG_EN
#define	CANbus_DebugOutput(x)		x
#else
#define	CANbus_DebugOutput(x)
#endif

BusOffStateStruct 	CanBusOffState[CAN_IDMAX];
CANAppLayerStruct 	CanAppLayerState[CAN_IDMAX];

CAN_INIT_STRUCT 	CANInitParam[CAN_IDMAX];
uint8_t  			CANTxMsgStatus[CAN_IDMAX];

TransCtlStruct		CANInfoStr;

void CANbus_SetTxReqStatusBit(uint8_t  canch, uint8_t MsgTypeMask)
{
	CANTxMsgStatus[canch] |= MsgTypeMask;
}

void CANbus_ClearTxReqStatusBit(uint8_t  canch, uint8_t MsgTypeMask)
{
	CANTxMsgStatus[canch] &= ~MsgTypeMask;
}

uint8_t CANbus_GetCurTxReqStatusBit(uint8_t  canch, uint8_t MsgTypeMask)
{
	return (CANTxMsgStatus[canch] & MsgTypeMask);
}

uint8_t CANbus_JudgeCANIdValid(uint8_t can_id)
{
	if(can_id < CAN_IDMAX)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/****************************************************************************
 * @function	CANbus_AppLayerColdInit
 * @brief  	Cold initialization
 * @param  	null				
 * @retval 	null
****************************************************************************/
void CANbus_AppLayerColdInit(void)
{
	uint8_t i = 0;
	CANbus_NetLayerVarInit();

	for(i = 0; i<CAN_IDMAX;i++)
	{
		CanAppLayerState[i].CANopMode = CAN_APP_MODE_IDLE;
		CANTxMsgStatus[i] = 0x00;
		CanAppLayerState[i].RstCnt = 0;
		CanAppLayerState[i].RcvChkTimer = CAN_RCV_CHK_TIME_MAX;
	}

	CANInfoStr.state = 0x00;

#ifdef UDS_ENABLE_MACRO
	Uds_ColdInit();
#endif
}
/****************************************************************************
 * @function	CANbus_AppLayerTimerDeal
 * @brief  	AppLayer Timer deal
 * @param  	null				
 * @retval 	null
****************************************************************************/
void CANbus_AppLayerRealTimerDeal(void)
{
	CANbus_NetLayerTimerDeal();
	#ifdef UDS_ENABLE_MACRO
	Uds_TimerHandler();
	#endif

	#ifdef NM_ENABLE_MACRO
	gILTiCanNMBase+=2;
	#endif
}

void CANbus_AppLayerSoftTimerDeal(uint8_t chno)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[chno];
	BusOffStateStruct *pBusoff = &CanBusOffState[chno];
	
	 if(pApp->CANopMode == CAN_APP_MODE_BUSOFF)
	 {
		if(pBusoff->Timer>0)
		{
			pBusoff->Timer--;
		}
		if(pBusoff->Timer1>0)
		{
			pBusoff->Timer1--;
		}
	 }
	 else if(pApp->CANopMode == CAN_APP_MODE_ON)
	 {
		 if(pApp->RcvChkTimer>0)
		 {
			pApp->RcvChkTimer--;
		 }
	 }
}

/****************************************************************************
 * @function	CANbus_StartupHandler
 * @brief  	CAN module startup handler
 * @param  	chno:  the CAN channl				
 * @retval 	0: 		complete
 *			other: 	not complete
****************************************************************************/
uint8_t CANbus_StartupHandler(uint8_t chno)
{
	uint8_t Retval = 1;
	CANAppLayerStruct *pApp = &CanAppLayerState[chno];
	
	if(chno >= CAN_IDMAX)
	{
		return  2;
	}

	#if 0
	switch(pApp->Startup_Step)
	{
	case CAN_STARTUP_PWRON:
		CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_STANDBY);
		//CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_NORMAL);
		pApp->Startup_Step = CAN_STARTUP_INIT1;
	//	break;
	case CAN_STARTUP_INIT1:
		if(CANbus_ChEnable(chno, &CANInitParam[chno]) == 0)
		{
			pApp->Startup_Step = CAN_STARTUP_INIT2;
		}
		break;
	case CAN_STARTUP_INIT2:
		if(CANbus_SetNormalMode(chno) == 0)
		{
			pApp->Startup_Step= CAN_STARTUP_INIT3;
		}
		break;
	case CAN_STARTUP_INIT3:
		CANbus_Init(chno);
		CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_NORMAL);
		if(CANbus_IsBusOffStatus(chno))
		{
			CANbus_RecoveryFromBusOff(chno);
		}
		else
		{
			Retval = 0;
		}
		break;
	default:
		break;
	}
	return Retval;
	#else
	//CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_STANDBY);
	CANbus_ChEnable(chno, &CANInitParam[chno]) ;
	CANbus_SetNormalMode(chno);
	CANbus_Init(chno);
	CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_NORMAL);
	return 0;
	#endif
}
/****************************************************************************
 * @function	CANbus_BusOffHandler
 * @brief  	CAN bus Bus-off exception  handler
 * @param  	chno:  the CAN channl				
 * @retval 	0: 		OK
 *			other: 	not OK
****************************************************************************/
//#define BUSOFF_DEAL_DELAY			/*采用延时的方式处理BUS OFF恢复*/
uint8_t CANbus_BusOffHandler(uint8_t chno)
{
	uint8_t retval = 1;
	CANAppLayerStruct *pApp = &CanAppLayerState[chno];
	BusOffStateStruct	*pBusoff = &CanBusOffState[chno];
	
	if(chno >= CAN_IDMAX)
	{
		return  2;
	}


	switch(pBusoff->BusoffStep)
	{
		case CANAPP_BUSOFF_START:
			pBusoff->BusOffCount = 1;
			pBusoff->ResetCount = 1;
			pBusoff->Timer = BUSOFF_RECOVERY_QUICK;
			CANbusMsgSendCnt[chno] = 1;
			CANbus_DebugOutput(_T("BusOff SetTime:50ms\n"));
			pBusoff->BusoffStep = CANAPP_BUSOFF_DELAY;
			break;
		case CANAPP_BUSOFF_DELAY:
			#ifdef BUSOFF_DEAL_DELAY
			if((CANbus_IsBusOffStatus(chno) == 0))
			#else
			if((CANbus_IsBusOffStatus(chno) == 0) &&(CANbusMsgSendCnt[chno] == 0))
			#endif
			{
				pBusoff->BusoffStep = CANAPP_BUSOFF_END;
			}
			else if(pBusoff->Timer == 0)
			{
				if(pBusoff->ResetCount >= BUSOFF_RECOVERY_QUICK_CNT)
				{
					pBusoff->ResetCount = BUSOFF_RECOVERY_QUICK_CNT;
					pBusoff->Timer = BUSOFF_RECOVERY_SLOW;
					CANbus_DebugOutput(_T("BusOff SetTime:slow\n"));
				}
				else
				{
					pBusoff->Timer = BUSOFF_RECOVERY_QUICK;
					CANbus_DebugOutput(_T("BusOff SetTime:quick\n"));
				}
				pBusoff->BusoffStep = CANAPP_BUSOFF_STEP1;
			}
			break;
		case CANAPP_BUSOFF_DELAY1:
			if(pBusoff->Timer1 == 0)
			{
				pBusoff->BusoffStep = CANAPP_BUSOFF_DELAY;
			}
			break;
		case CANAPP_BUSOFF_STEP1:
			#if 0
			CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_NORMAL);
			CANbus_RecoveryFromBusOff(chno);
			#endif
			CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_SLEEP);
			CANbus_DefaultInit(chno);
			CANbus_StartupHandler(chno);
			CANbusMsgSendCnt[chno] = 0;
			CANUser_TryToSendCANMsg(chno);
			CANbus_DebugOutput(_T("CAN BusOff Try to send Msg\n"));
			pBusoff->ResetCount++;
			pBusoff->BusOffCount++;
			#ifdef BUSOFF_DEAL_DELAY
			pBusoff->Timer1 = TIMER_20MS;
			pBusoff->BusoffStep = CANAPP_BUSOFF_DELAY1;
			#else
			pBusoff->BusoffStep = CANAPP_BUSOFF_DELAY;
			#endif
			break;
		case CANAPP_BUSOFF_END:
			pApp->CANopMode = CAN_APP_MODE_ON;
			retval = 0;
			break;
		default:
			break;
	}
	return retval;
}
/****************************************************************************
 * @function	CANbus_AppLayerSleepDeal
 * @brief  	CAN bus Sleep mode  handler
 * @param  	chno:  the CAN channl				
 * @retval 	0: 		exit sleep
 *			other: 	sleep
****************************************************************************/
uint8_t CANbus_AppLayerSleepDeal(uint8_t chno)
{
	uint8_t RetVal = 1;

	CANAppLayerStruct *pApp = &CanAppLayerState[chno];
	
	if(chno >= CAN_IDMAX)
	{
		return  2;
	}

	switch(pApp->CANSleepStep)
	{
		case CANAPP_SLEEP_REQ:
			CANbus_EnterSleepMode(chno);
			CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_SLEEP);
			CANbus_NetLayerClearWakeupStatus(chno);
			pApp->CANSleepStep = CANAPP_SLEEP_WAKE_CHK;
			break;
		case CANAPP_SLEEP_WAKE_CHK:
			if(CANbus_NetLayerGetWakeupStatus(chno))
			{
				CANbus_NetLayerClearWakeupStatus(chno);
				pApp->CANSleepStep = CANAPP_SLEEP_WAKE_INIT;
			}
			break;
		case CANAPP_SLEEP_WAKE_INIT:
			if(!CANbus_ExitSleepMode(chno))
			{
				CANbus_EnableCANTransceiver(chno, CAN_TRANSCEIVER_MODE_NORMAL);
				pApp->CANSleepStep = CANAPP_SLEEP_EXIT;
				RetVal = 0;
			}
			break;
		case CANAPP_SLEEP_EXIT:
			RetVal = 0;
			break;
		default:
			break;
	}
	return RetVal;
}

void CANbus_AppLayerSetInitParam(CAN_INIT_STRUCT *pInitParam)
{
	uint8_t index = pInitParam->can_Id;
	uint8_t i = 0;

	if(pInitParam->can_RecvFilterNum > CAN_RCV_FILTER_MAX)
	{
		return;
	}

	if(pInitParam->MASKValidNum > 4)
	{
		return;
	}
	CANInitParam[index].validFlag = pInitParam->validFlag;
	CANInitParam[index].can_Id = index;
	CANInitParam[index].can_BpsType = pInitParam->can_BpsType;
	CANInitParam[index].can_RecvFilterNum = pInitParam->can_RecvFilterNum;
	CANInitParam[index].can_SendBuffNum = pInitParam->can_SendBuffNum;
	CANInitParam[index].MASKValidNum = pInitParam->MASKValidNum;

	for(i = 0; i<pInitParam->can_RecvFilterNum; i++)
	{
		CANInitParam[index].can_RecvFilter[i] = pInitParam->can_RecvFilter[i];
	}
	
	for(i = 0; i<pInitParam->MASKValidNum; i++)
	{
		CANInitParam[index].can_RecvFilterCmp[i] = pInitParam->can_RecvFilterCmp[i];
		CANInitParam[index].can_RecvMASK[i] = pInitParam->can_RecvMASK[i];
	}
	
}

/****************************************************************************
 * @function	CANbus_AppLayerHandler
 * @brief  	CAN module Application deal
 * @param  	chno:  the CAN channl				
 * @retval 	null
****************************************************************************/
void CANbus_AppLayerHandler(uint8_t CANCh)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[CANCh];
	BusOffStateStruct	*pBusoff = &CanBusOffState[CANCh];
	
	if(CANCh >= CAN_IDMAX)
	{
		return;
	}

	switch(pApp->CANopMode)
	{
		case CAN_APP_MODE_START:
			CANbus_DebugOutput(_T("CAN %x modue Init\n", CANCh));
			pApp->Startup_Step = CAN_STARTUP_PWRON;
			pApp->CANopMode = CAN_APP_MODE_INIT;
			CANbus_DefaultInit(CANCh);
			//CANbus_NetLayerVarInit();
			//break;
		case CAN_APP_MODE_INIT:
			if(!CANbus_StartupHandler(CANCh))
			{
				pApp->CANopMode = CAN_APP_MODE_ON;
				pApp->RcvChkTimer = CAN_RCV_CHK_TIME_MAX;
				CANbus_DebugOutput(_T("CAN work on\n"));
			}
			break;
		case CAN_APP_MODE_ON:
			if(CANbus_IsBusOffStatus(CANCh))
			{
				CANbus_DebugOutput(_T("CAN %x busoff\n", CANCh));
				pBusoff->BusoffStep = CANAPP_BUSOFF_START;
				pApp->CANopMode = CAN_APP_MODE_BUSOFF;
				CANbus_NetLayerStopAllSend(CANCh);
				CANbus_BusOffHandler(CANCh);
			}
			else
			{
				CANbus_NetLayerSendManager(CANCh);
			//	#ifdef UDS_ENABLE_MACRO
			//	if(CANCh == UdsCANConfig.UseId)
			//	{
			//		Uds_ProtocolStackMain();
			//	}
			//	#endif
				if((pApp->RcvChkTimer) == 0)
				{
					if(pApp->RstCnt<CAN_RCV_LOST_RST_CNT)
					{
						pApp->RstCnt ++;
						CANbus_AppLayerReqSwitchMode(CANCh, CAN_APP_MODE_START);
					}
				}
			}
			break;
		case CAN_APP_MODE_BUSOFF:
			if(!CANbus_BusOffHandler(CANCh))
			{
				pApp->CANopMode = CAN_APP_MODE_ON;
				
				CANbus_DebugOutput(_T("CAN %x resume OK\n", CANCh));
			}
			break;
		case CAN_APP_MODE_OFF:
			CANbus_DebugOutput(_T("CAN module off:%d\n", CANCh));
			CANbus_ChShutDown(CANCh);
			CANbus_EnableCANTransceiver(CANCh, CAN_TRANSCEIVER_MODE_SLEEP);	/* sleep , 20131220*/
		//	#ifdef UDS_ENABLE_MACRO
		//	if(CANCh == UdsCANConfig.UseId)
		//	{
		//		Uds_Close();
		//	}
		//	#endif
			pApp->CANopMode = CAN_APP_MODE_IDLE;
			break;
		case CAN_APP_MODE_SLEEP:
			if(!CANbus_AppLayerSleepDeal(CANCh))
			{
				pApp->CANopMode = CAN_APP_MODE_ON;
				CANbus_DebugOutput(_T("CAN wakeup OK:%d\n",CANCh));
			}
			break;
		case CAN_APP_MODE_IDLE:
			break;
		default:
			pApp->CANopMode = CAN_APP_MODE_START;
			break;
	}
}
/****************************************************************************
 * @function	CANbus_AppLayerReqShutDown
 * @brief  	request shut down CAN bus
 * @param  	chno:  the CAN channl				
 * @retval 	null
****************************************************************************/
void CANbus_AppLayerReqShutDown(uint8_t chno)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[chno];

	pApp->CANopMode = CAN_APP_MODE_OFF;

}
/****************************************************************************
 * @function	CANbus_AppLayerReqSleep
 * @brief  	request  CAN bus to enter sleep mode 
 * @param  	Null		
 * @retval 	null
****************************************************************************/
void CANbus_AppLayerReqSleep(uint8_t chno)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[chno];

	pApp->CANopMode = CAN_APP_MODE_SLEEP;
	pApp->CANSleepStep = CANAPP_SLEEP_REQ;
	CANbus_DebugOutput(_T("CAN request sleep\n"));
}
/****************************************************************************
 * @function	CANbus_AppLayerReqSwitchMode
 * @brief  	request  CAN bus to switch work mode
 * @param  	mode : work mode		
 * @retval 	null
****************************************************************************/
void CANbus_AppLayerReqSwitchMode(uint8_t chno, CANAPP_MODE_ENUM mode)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[chno];
	switch(mode)
	{
		case CAN_APP_MODE_START:
			pApp->Startup_Step = CAN_STARTUP_PWRON;
			break;
		case CAN_APP_MODE_SLEEP:
			pApp->CANSleepStep = CANAPP_SLEEP_REQ;
			break;
		case CAN_APP_MODE_BUSOFF:
			CanBusOffState[chno].BusoffStep = CANAPP_BUSOFF_START;
			break;
		default:
			break;
	}
	pApp->CANopMode = mode;
}
/****************************************************************************
 * @function	CANBus_AppLayerGetMode
 * @brief  	get work mode 
 * @param  	null
 * @retval 	work mode
****************************************************************************/
uint8_t  CANBus_AppLayerGetMode(uint8_t chno)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[chno];

	return pApp->CANopMode;
}
/****************************************************************************
 * @function	CANbus_AppLayerGetMsg
 * @brief  	Get CAN message,  use query mode
 * @param  	pRxMessage : a point to the Receive MSG struct buffer
 * @retval 	0: get a message
 *                     other: not get valid messge
 * @attention:   just get the user application message. UDS/NM message not deal 
****************************************************************************/
uint8_t   CANbus_AppLayerGetMsg(CanMsgStruct *pRxMessage)
{
	uint8_t status;
#ifdef UDS_ENABLE_MACRO
	if(Uds_GetMsgDealState() == WORK_RUN)
	{
		// because UDS messge and the normal message use the same receive buffer.
		//when read the message, we shoud ensure the UDS message have deal OK!
		return 1;
	}
#endif
	status = CANbus_NetLayerReadMsgBuffer(pRxMessage);
#ifdef UDS_ENABLE_MACRO
	if( status == 0)
	{
		if((pRxMessage->CAN_Id == UdsCANConfig.UseId) &&	\
		    ((pRxMessage->CANMsgId == UdsCANConfig.RxPhyId) ||(pRxMessage->CANMsgId == UdsCANConfig.RxFuncId))
		    )
		{
			// UDS MESSAGE HANDLER
			Uds_CANMsgRcvHandler(pRxMessage);
			return 1;
		}
	}
#endif
	return status;
}
/****************************************************************************
 * @function	CANbus_AppLayerSendPeriodicMsg
 * @brief  	periodic send message
 * @param  	pTxMsg: point to the translate mesage buffer
 *                     cycleTime: periodic cycle time
 * @retval 	0: ok
 *                     other: some exception produce
 * @attention:  the maximum number of periodic msg buffer is controled 
                         by macro "CAN_PERIODIC_POOL_SIZE"
****************************************************************************/
uint8_t CANbus_AppLayerSendPeriodicMsg(CanMsgStruct *pTxMsg, uint16_t cycleTime)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[pTxMsg->CAN_Id];

	if(pApp->CANopMode == CAN_APP_MODE_ON)
	{
		#if 0 //snake20170322
		//对于报文数据装入到寄存器中,我觉得不需要进行通信的判断,直接装入即可.
		//在canbus_netlayer中的发送请求之前会进行通信的判断,所以也不会出现关闭通信的时候,误发送报文出去的情况...
		//若在这里进行判断,就会导致下面问题:
		// 1.在关闭ACC的时候,关闭了通信.
		// 2.开启ACC的时候,在没有开启通信开关的之前,进行buffer的载入.
		// 3.会导致出现发送出来的报文的数据全部为0
		//出现问题的原因是:
		// 1.由于在将can的缓存数据装入到V850寄存器之前,进行了判断,导致数据没有装入到寄存器中.
		// 2.由于ACC启动的时候,对CAN模块进行了失能,就会导致V850 CAN模块的数据缓存寄存器的数据全部恢复为默认值0x00
		// 3.为什么调用CANbus_NetLayerPeriodicSendMsg函数,但是还可以正常的发送出报文?
		//   是因为关闭ACC,没有清除CANPeriodicMsgStatePool数组,由于CANbus_NetLayerPeriodicSendMsg函数的调用,导致启动了发送的请求,但是没有装入数据,所以报文可以正常的发送,但是数据全部为0...
		//    CANPeriodicMsgStatePool数组只有在冷启动的时候,才会进行初始化.
		#ifdef UDS_ENABLE_MACRO
		if((pTxMsg ->CAN_Id == UdsCANConfig.UseId) && 	\
		    (pTxMsg->CANMsgId  != UdsCANConfig.TxMsgId))
		{
			if(TRUE != Uds_GetMsgTransEnableState(MSG_NCM, MSG_TRANS_TX))
			{
				return 1;
			}
		}
		#endif
		#endif
		
		CANbus_DebugOutput(_T("CAN request Send:%d\n",pTxMsg ->CAN_Id));
		return CANbus_NetLayerPeriodicSendMsg(pTxMsg, cycleTime);
	}
	else
	{
		return 1;
	}
}
/****************************************************************************
 * @function	CANbus_AppLayerSendOneShotMsg
 * @brief  	send a message just one
 * @param  	pTxMsg: point to the translate mesage buffer
 * @retval 	null
 * @attention:  
 ****************************************************************************/
void CANbus_AppLayerSendOneShotMsg(CanMsgStruct *pTxMsg)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[pTxMsg->CAN_Id];


	if(pApp->CANopMode == CAN_APP_MODE_ON)
	{
		#ifdef UDS_ENABLE_MACRO
		if((pTxMsg ->CAN_Id == UdsCANConfig.UseId) && 	\
		    (pTxMsg->CANMsgId  != UdsCANConfig.TxMsgId))
		{
			if(TRUE != Uds_GetMsgTransEnableState(MSG_NCM, MSG_TRANS_TX))
			{
				return;
			}
		}
		#endif
		#ifdef NM_ENABLE_MACRO
		if(pTxMsg->CAN_Id == NM_NetNode.CAN_Id)
		{
			if(!gILCanNMNormalMsgActive)
			{
				return;
			}
		}
		#endif
		CANbus_NetLayerOneShotSendMsg(pTxMsg);
	}
}

/****************************************************************************
 * @function	CANbus_AppLayerSendNMMsg
 * @brief  	send OSEK Network Managerment Message.
 * @param  	pTxMsg: point to the translate mesage buffer
 * @retval 	0- send normal 1- not send
 * @attention:  
 ****************************************************************************/
uint8_t CANbus_AppLayerSendNMMsg(CanMsgStruct *pTxMsg)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[pTxMsg->CAN_Id];

	if(pApp->CANopMode == CAN_APP_MODE_ON)
	{
		#ifdef UDS_ENABLE_MACRO
		if((pTxMsg ->CAN_Id == UdsCANConfig.UseId) && 	\
		    (pTxMsg->CANMsgId  != UdsCANConfig.TxMsgId))
		{
			if(TRUE != Uds_GetMsgTransEnableState(MSG_NWMCM, MSG_TRANS_TX))
			{
				return 1;
			}
		}
		#endif
		CANbus_NetLayerOneShotSendMsg(pTxMsg);
		return 0;
	}
	return 1;
}

void CANbus_AppLayerClearRcvChkState(uint8_t chno)
{
	CANAppLayerStruct *pApp = &CanAppLayerState[chno];
	pApp->RstCnt = 0;
	pApp->RcvChkTimer = CAN_RCV_CHK_TIME_MAX;
}

void CANbus_InforOutputReq(uint8_t chno, uint8_t *pBuffer, uint8_t len)
{
	CANInfoStr.state = 1;
	CANInfoStr.BusCh = chno;
	CANInfoStr.Timer = TIMER_20MS;
	CANInfoStr.pData = pBuffer;
	CANInfoStr.size = len;
	CANInfoStr.TransIndex = 0;
	CANInfoStr.TransNum = 0;
}

void CANbus_InforOutputMain(void)
{
	if(CANInfoStr.state)
	{
		if(CANInfoStr.Timer>0)
		{
			CANInfoStr.Timer--;
		}

		if(CANInfoStr.Timer > 0)
		{
			return;
		}
		CANInfoStr.Timer = TIMER_20MS;
		/**********************************/
		{
			CanMsgStruct TxMsg;
			TxMsg.CAN_Id = CANInfoStr.BusCh;
			TxMsg.CANMsgId = 0x7ff;
			TxMsg.Data[0] = CANInfoStr.TransIndex;
			if((CANInfoStr.TransNum+7)>=CANInfoStr.size)
			{
				TxMsg.CANMsgDlc = CANInfoStr.size-CANInfoStr.TransNum+1;
				CANInfoStr.state = 0;
			}
			else
			{
				TxMsg.CANMsgDlc = 8;
				
			}
			Memory8Copy(&TxMsg.Data[1], CANInfoStr.pData+CANInfoStr.TransNum,TxMsg.CANMsgDlc-1);
			CANInfoStr.TransNum+= (TxMsg.CANMsgDlc-1);
			CANInfoStr.TransIndex++;
			CANbus_AppLayerSendOneShotMsg(&TxMsg);
		}
		/**********************************/
	}
}

#endif
/****************************************************************************
 * **                                        FILE END
****************************************************************************/

