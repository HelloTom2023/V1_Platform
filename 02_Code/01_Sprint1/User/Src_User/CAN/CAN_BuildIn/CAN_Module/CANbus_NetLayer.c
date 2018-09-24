/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CANbus_NetLayer.c
* Target MCU:		V850SJ3
* Module:
* Summary:		CAN module network layer source code
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

#if D_PRINT_EN && D_CANBUS_NET_DBG_EN
#define	CANbus_NetLayerDebug(x)		x
#else
#define	CANbus_NetLayerDebug(x)
#endif

extern CAN_INIT_STRUCT CANInitParam[CAN_IDMAX];

typedef struct
{
	uint8_t bufNo;			/* the buffer Number  to the message */
	uint8_t CanId;
	uint8_t validFlag;		/* buffer valid flag: when used, is valid*/
	uint16_t cycle;		/*periodic message cycle time */
	uint16_t curtime;		/* cur timer count*/
	uint32_t FrameId;		/* the frame ID of this buffer */
}PeriodicMsgStateStruct;


PeriodicMsgStateStruct CANPeriodicMsgStatePool[CAN_PERIODIC_POOL_SIZE];

/*#if (CAN_PERIODIC_POOL_SIZE+1) > CAN0_NUM_SEND_DRVBUF
#error "The Netlayer PeriodicMsgStatePool size overflow the SEND driver Buffer!"
#endif*/
typedef struct
{
	uint8_t FirstMsgFlag:  		1;
	uint8_t Reserved:			7;
	uint8_t LastMsgIndex;	
}NetLayerStateFlagStruct;

NetLayerStateFlagStruct		NetLayerStateFlag;

BuffPointStruct   CANbus_RxBuffPointManage;

CanMsgStruct  CAN_MsgRxBuf[CAN_MSG_BUFF_NUM];

#if CANMSG_RCV_FILTER_EN
/* each Recv ID use a buffer to compare*/
CanMsgStruct  CANbus_NetMsgRxBakBuf[CAN_RCV_FILTER_NUM];
#endif

/****************************************************************************
 * @function	CANbus_NetLayerVarInit
 * @brief  	net layer Var  initialization
 * @param  	null				
 * @retval 	null
****************************************************************************/
void CANbus_NetLayerVarInit(void)
{
	uint8_t i = 0;
	uint8_t j = 0;
	CANbus_RxBuffPointManage.Point_read = 0;
	CANbus_RxBuffPointManage.Point_write = 0;
	CANbus_RxBuffPointManage.ReceivedNum = 0;
#if CANMSG_RCV_FILTER_EN
	for(i =0; i<CAN_RCV_FILTER_NUM;i++)
	{
		CANbus_NetMsgRxBakBuf[i].CANMsgDlc = 0;
	}
#endif
#if CAN_IDMAX >= 1
	i = 0;
	if(CANInitParam[0].validFlag)
	{
		if(CANInitParam[0].can_SendBuffNum>1)
		{
			j = 1;
			for(i = 0; i<(CANInitParam[0].can_SendBuffNum-1);i++)
			{
				if(i>=CAN_PERIODIC_POOL_SIZE)
				{
					break;
				}
				CANPeriodicMsgStatePool[i].bufNo = j++;
				CANPeriodicMsgStatePool[i].CanId = CANInitParam[0].can_Id;
				CANPeriodicMsgStatePool[i].curtime = 0x00;
				CANPeriodicMsgStatePool[i].cycle = 0xff;
				CANPeriodicMsgStatePool[i].validFlag = 0;
			}
		}
	}
#endif
#if CAN_IDMAX == 2
	if(CANInitParam[0].can_SendBuffNum<=1)
	{
		CANInitParam[0].can_SendBuffNum = 1;
	}
	if(CANInitParam[1].validFlag)
	{
		if(CANInitParam[1].can_SendBuffNum>1)
		{
			j = 1;
			for(i = CANInitParam[0].can_SendBuffNum-1; i<CAN_PERIODIC_POOL_SIZE;i++)
			{
				CANPeriodicMsgStatePool[i].bufNo = j++;
				CANPeriodicMsgStatePool[i].CanId = CANInitParam[1].can_Id;
				CANPeriodicMsgStatePool[i].curtime = 0x00;
				CANPeriodicMsgStatePool[i].cycle = 0xff;
				CANPeriodicMsgStatePool[i].validFlag = 0;
			}
		}
	}
#endif
	for(; i<CAN_PERIODIC_POOL_SIZE;i++)
	{
		CANPeriodicMsgStatePool[i].validFlag = 0;
	}

	CANWakeupStatus = 0;

	NetLayerStateFlag.FirstMsgFlag = 1;
	NetLayerStateFlag.LastMsgIndex = 0;

	CANbusMsgSendCnt[0] = 0;
	CANbusMsgSendCnt[1] = 0;
}

void CANbus_NetLayerClearFilterBuff(uint8_t index)
{
	CANbus_NetMsgRxBakBuf[index].CANMsgDlc = 0;
}

uint16_t CANbus_NetLayerGetInitTime(uint8_t curIndex)
{
	uint16_t temp = 0;
	uint16_t RetVal;
	if(NetLayerStateFlag.FirstMsgFlag == 1)
	{	
		RetVal= TIMER_20MS;
	}
	else
	{
		temp = CANPeriodicMsgStatePool[NetLayerStateFlag.LastMsgIndex].curtime;
		if(temp > TIMER_20MS)
		{
			RetVal= (temp-TIMER_20MS);
		}
		else
		{
			RetVal= temp+(TIMER_100MS-TIMER_20MS);
		}
	}
	NetLayerStateFlag.LastMsgIndex = curIndex;
	NetLayerStateFlag.FirstMsgFlag=0;

	return RetVal;
}
/****************************************************************************
 * @function	CANbus_NetLayerTimerDeal
 * @brief  	net layer Timer deal
 * @param  	null				
 * @retval 	null
****************************************************************************/
void CANbus_NetLayerTimerDeal(void)
{
	uint8_t i = 0;
	for(i = 0;i<CAN_PERIODIC_POOL_SIZE; i++)
	{
		if(CANPeriodicMsgStatePool[i].validFlag == 1)
		{
			if(CANPeriodicMsgStatePool[i].curtime>0)
			{
				CANPeriodicMsgStatePool[i].curtime--;
			}
		}
	}
}

/****************************************************************************
 * @function	CANbus_NetLayerPeriodicSendMsg
 * @brief  	net layer periodic send message
 * @param  	pTxMsg: point to the transmite message buffer
 *			cycleTime: Cycle time
 * @retval 	0: ok
 *			other: not ok
****************************************************************************/
uint8_t CANbus_NetLayerPeriodicSendMsg(CanMsgStruct *pTxMsg, uint16_t cycleTime)
{
	uint8_t index = 0;
	PeriodicMsgStateStruct *pPool;
	for(index = 0; index< CAN_PERIODIC_POOL_SIZE; index++)
	{
		pPool = &CANPeriodicMsgStatePool[index];
		// judge the TxMsg id is in the pool or not, if yes, refresh it 
		if(pPool->validFlag == 1) 
		{
			if((pPool->CanId == pTxMsg->CAN_Id) &&(pPool->FrameId == pTxMsg->CANMsgId))
			{
				if(cycleTime != pPool->cycle)
				{
				// if the cycle time changed, use the new cycle time.
					pPool->cycle = cycleTime;
					//pPool->curtime = cycleTime;
					pPool->curtime = CANbus_NetLayerGetInitTime(index);
				}
				CANbus_MsgSetDat(pTxMsg->CAN_Id, pPool->bufNo, pTxMsg->Data);
				return 0;
			}
		}
	}
	// add the Id to the pool.
	for(index = 0; index< CAN_PERIODIC_POOL_SIZE; index++)
	{
		pPool = &CANPeriodicMsgStatePool[index];
		if((pPool->validFlag == 0) && (pPool->CanId == pTxMsg->CAN_Id))
		{
			pPool->cycle  = cycleTime;
			//pPool->curtime = cycleTime;
			pPool->curtime = CANbus_NetLayerGetInitTime(index);
			pPool->FrameId = pTxMsg->CANMsgId;
			pPool->validFlag = 1;
			CANbus_MsgSetIdDataDlc(pTxMsg->CAN_Id, pPool->bufNo, 
								pTxMsg->CANMsgId, pTxMsg->Data, pTxMsg->CANMsgDlc);
			return 0;
		}
	}
	return 1;
}
/****************************************************************************
 * @function	CANbus_NetLayerOneShotSendMsg
 * @brief  	net layer one-shot send a message
 * @param  	pTxMsg: point to the transmite message buffer				
 * @retval 	null
 * @attention   if message is not periodic, user can call this function to send a message
****************************************************************************/
void CANbus_NetLayerOneShotSendMsg(CanMsgStruct *pTxMsg)
{
	if(CANbusMsgSendCnt[pTxMsg->CAN_Id]<=0xfffe)
	{
		CANbusMsgSendCnt[pTxMsg->CAN_Id]++;
	}
	CANbus_MsgSetIdDataDlc(pTxMsg->CAN_Id, 0, pTxMsg->CANMsgId, pTxMsg->Data, pTxMsg->CANMsgDlc);
	CANbus_MsgTxReq(pTxMsg->CAN_Id, 0);
}
/****************************************************************************
 * @function	CANbus_NetLayerStopAllSend
 * @brief  	net layer stop all Transmit message
 * @param  	null				
 * @retval 	null
 * @attention   
****************************************************************************/
void CANbus_NetLayerStopAllSend(uint8_t chno)
{
	uint8_t i = 0;
	for(i = 0; i< CAN_PERIODIC_POOL_SIZE;i++)
	{
		if(CANPeriodicMsgStatePool[i].CanId == chno)
		{
			CANPeriodicMsgStatePool[i].validFlag = 0;
		}
	}
}
/****************************************************************************
 * @function	CANbus_NetLayerCanclePeriodicMsgSend
 * @brief  	net layer cancle periodic message treansmit, the message ID is given in the parameter
 * @param  	MsgId: the CAN message Id which request to cancle				
 * @retval 	null
 * @attention   
****************************************************************************/
void CANbus_NetLayerCanclePeriodicMsgSend(uint8_t chno, uint32_t MsgId)
{
	uint8_t i = 0;
	for(i = 0; i< CAN_PERIODIC_POOL_SIZE;i++)
	{
		if((CANPeriodicMsgStatePool[i].FrameId == MsgId) &&(CANPeriodicMsgStatePool[i].CanId == chno))
		{
			CANPeriodicMsgStatePool[i].validFlag = 0;
			return;
		}
	}
}
/****************************************************************************
 * @function	CANbus_NetLayerSendManager
 * @brief  	net layer message send manager
 * @param  	null				
 * @retval 	null
 * @attention   called by application layer only, user not used
****************************************************************************/
void CANbus_NetLayerSendManager(uint8_t chno)
{
	uint8_t i = 0;

	PeriodicMsgStateStruct *pPool = &CANPeriodicMsgStatePool[0];

	#ifdef NM_ENABLE_MACRO
	if(chno == NM_NetNode.CAN_Id)
	{
		if(!gILCanNMNormalMsgActive)
		{
			return;
		}
	}
	#endif
	
	for(i = 0; i< CAN_PERIODIC_POOL_SIZE;i++)
	{
		pPool = &CANPeriodicMsgStatePool[i];
		if((pPool->validFlag) &&(pPool->CanId == chno))
		{
			if(pPool->curtime == 0)
			{
				if(TRUE == Uds_GetMsgTransEnableState(MSG_NCM, MSG_TRANS_TX))
				{
					CANbus_MsgSendReqCallBack(chno, pPool->FrameId);
					CANbus_MsgTxReq(chno, pPool->bufNo);
					
					pPool->curtime = pPool->cycle;
					return ;
				}
			}
		}
		
	}
}
/****************************************************************************
 * @function	CANbus_NetLayerMessageFilter
 * @brief  	net layer message receive filter, if the message same to the last, filter it.
 * @param  	pRxMessage: the point to the received message to check				
 * @retval 	0: the message same to the last
 *			1: different message
 * @attention   called by this file only, user not used
****************************************************************************/
static uint8_t CANbus_NetLayerMessageFilter(CanMsgStruct *pRxMessage)
{

#if  CANMSG_RCV_FILTER_EN
	CanMsgStruct *pBak = (CanMsgStruct *)0;

	pBak = CANUser_RcvFilterPreDeal(pRxMessage, CANbus_NetMsgRxBakBuf);

	if(pBak >=&CANbus_NetMsgRxBakBuf[CAN_RCV_FILTER_NUM])
	{
		return 1;
	}
	if(pBak != (CanMsgStruct *)0)
	{
		if(pBak->CANMsgDlc == pRxMessage->CANMsgDlc)
		{
			if(MemoryCompare(pBak->Data, pRxMessage->Data, pBak->CANMsgDlc))
			{
				Memory8Copy((uint8_t *)pBak,(uint8_t *)pRxMessage, sizeof(CanMsgStruct));
				return 1;
			}
		}
		else
		{
			Memory8Copy((uint8_t *)pBak,(uint8_t *)pRxMessage, sizeof(CanMsgStruct));
			return 1;
		}
	}
	else
	{
		return 1;		/* the message not config filter,all need to receive and deal. */
	}
	if(!CANUser_MsgFilter_Step2(pRxMessage))
	{
		return 1;
	}
	return 0;
#else
	return 1;
#endif
}

/****************************************************************************
 * @function	CANbus_NetLayerReadMsgBuffer
 * @brief  	read a message to the netlayer
 * @param  	pRxMessage: the point to the received message to store				
 * @retval 	0:read a CAN message successful
 *			1: failed, no message or message duplicate
 * @attention   called by this application only, user not used
****************************************************************************/
uint8_t  CANbus_NetLayerReadMsgBuffer(CanMsgStruct *pRxMessage)
{
	uint8_t i,j;

	if(CANbus_RxBuffPointManage.ReceivedNum==0)
	{
		return 1;
	}
	
	i = CANbus_RxBuffPointManage.Point_read;
		
	pRxMessage->CANMsgId	=CAN_MsgRxBuf[i].CANMsgId;
	pRxMessage->CANMsgDlc	=CAN_MsgRxBuf[i].CANMsgDlc;
	pRxMessage->CAN_Id = CAN_MsgRxBuf[i].CAN_Id;
	
	for(j = 0; j < pRxMessage->CANMsgDlc; j ++)
	{
		pRxMessage->Data[j]	=CAN_MsgRxBuf[i].Data[j];
	}
	CAN_ENTER_CRITICAL_REGION();
	CANbus_RxBuffPointManage.ReceivedNum--;
	i++;
	if(i>=CAN_MSG_BUFF_NUM)
	{
		i = 0;
	}
	CANbus_RxBuffPointManage.Point_read = i;
	CANbus_NetLayerDebug(_T("CAN Read: %d\n", CANbus_RxBuffPointManage.ReceivedNum));
	CAN_EXIT_CRITICAL_REGION();	
	return 0;
}
/****************************************************************************
 * @function	CANbus_NetLayerWriteMsgBuff
 * @brief  	write a message to the receive buffer
 * @param  	pRxMessage: the point to the received message to store				
 * @retval 	0:write a CAN message successful
 *			1: failed,  message duplicate
 * @attention   called by the CAN receive interruput only, user not used
****************************************************************************/
static uint8_t  CANbus_NetLayerWriteMsgBuff(CanMsgStruct *pRxMessage)
{
	uint8_t index = CANbus_RxBuffPointManage.Point_write;
	uint8_t j = 0;

	if(CANbus_NetLayerMessageFilter(pRxMessage) == 0)
	{
		CANbus_NetLayerDebug(_T("CAN msg Filter!\n"));
		return 1;
	}
	CAN_MsgRxBuf[index].CAN_Id  = pRxMessage->CAN_Id;
	CAN_MsgRxBuf[index].CANMsgId = pRxMessage->CANMsgId;
	CAN_MsgRxBuf[index].CANMsgDlc = pRxMessage->CANMsgDlc;
	
	for(j = 0;j<pRxMessage->CANMsgDlc;j++)
	{
		CAN_MsgRxBuf[index].Data[j] = pRxMessage->Data[j];
	}
	index++;
	if(index>=CAN_MSG_BUFF_NUM)
	{
		index = 0;
	}
	CANbus_RxBuffPointManage.Point_write = index;
	CANbus_RxBuffPointManage.ReceivedNum++;
	if(CANbus_RxBuffPointManage.ReceivedNum>CAN_MSG_BUFF_NUM)
	{
		CANbus_RxBuffPointManage.ReceivedNum = CAN_MSG_BUFF_NUM;
		CANbus_RxBuffPointManage.Point_read = CANbus_RxBuffPointManage.Point_write;
	}
	CANbus_NetLayerDebug(_T("CAN Recv: %d\n", CANbus_RxBuffPointManage.ReceivedNum));
	return 0;
}
/****************************************************************************
 * @function	CANbus_NetLayerGetWakeupStatus
 * @brief  	get the CAN bus netlayer wakeup status
 * @param  	null		
 * @retval 	0:not wakeup
 *			1: wakeup
 * @attention   null
****************************************************************************/
uint8_t CANbus_NetLayerGetWakeupStatus(uint8_t chno)
{
	if(chno == 0)
	{
		return CANWakeupStatus&_U8_BIT0;
	}
	else
	{
		return CANWakeupStatus&_U8_BIT1;
	}
}
/****************************************************************************
 * @function	CANbus_NetLayerClearWakeupStatus
 * @brief  	clear the CAN bus netlayer wakeup status
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
void CANbus_NetLayerClearWakeupStatus(uint8_t chno)
{
	if(chno == 0)
	{
		CANWakeupStatus &= ~_U8_BIT0;
	}
	else
	{
		CANWakeupStatus &= ~_U8_BIT1;
	}
}

/****************************************************************************
 * @function	CANbus_RecvInterruptCallBack
 * @brief  	the CAN BUS receive interrupt callback function.
 * @param  	chno: CAN channal
 * @retval 	null
 * @attention   null
****************************************************************************/
void CANbus_RecvInterruptCallBack(uint8_t chno)
{
	uint8_t bufNo;

	bufNo = CANbus_GetIntBuffNumber(chno);
	
	if(bufNo <=31)
	{
		CanMsgStruct  CANRxMsgBuff;
		CANbus_MsgGetIdDataDlc(chno, bufNo, &CANRxMsgBuff.CANMsgId, 
							&CANRxMsgBuff.Data[0], &CANRxMsgBuff.CANMsgDlc);
		CANRxMsgBuff.CAN_Id = chno;
		CANbus_AppLayerClearRcvChkState(chno);
#ifdef NM_ENABLE_MACRO
		if(chno== NM_NetNode.CAN_Id)
		{
			NM_NetNode.Wakeup = 1;
		}
#endif
#ifdef UDS_ENABLE_MACRO
		if((CANRxMsgBuff.CAN_Id == UdsCANConfig.UseId)&&
		   ((CANRxMsgBuff.CANMsgId == UdsCANConfig.RxFuncId) ||(CANRxMsgBuff.CANMsgId == UdsCANConfig.RxPhyId)))
		{
			CANbus_NetLayerWriteMsgBuff(&CANRxMsgBuff);
		}
		else 
		{
			#ifdef NM_ENABLE_MACRO
			if((CANRxMsgBuff.CAN_Id == NM_NetNode.CAN_Id) &&
				((CANRxMsgBuff.CANMsgId & 0xf00) == 0x400))
			{
				if(TRUE == Uds_GetMsgTransEnableState(MSG_NWMCM, MSG_TRANS_RX))
				{
					NM_WriteMsgBuff(&CANRxMsgBuff);
				}
				return;
			}
			#endif
			if(TRUE == Uds_GetMsgTransEnableState(MSG_NCM, MSG_TRANS_RX))
			{
				CANbus_NetLayerWriteMsgBuff(&CANRxMsgBuff);
			}
		}
#else
		#ifdef NM_ENABLE_MACRO
		if((CANRxMsgBuff.CAN_Id == NM_NetNode.CAN_Id) &&
			((CANRxMsgBuff.CANMsgId & 0xf00) == 0x400))
		{
			NM_WriteMsgBuff(&CANRxMsgBuff);
			return;
		}
		#endif
		CANbus_NetLayerWriteMsgBuff(&CANRxMsgBuff);
#endif
	}
}

void CANbus_Ch0SendInterruptCallBack(void)
{
	if(CANbusMsgSendCnt[0]>0)
	{
		CANbusMsgSendCnt[0]--;
	}
	#ifdef NM_ENABLE_MACRO
	if(NM_NetNode.CAN_Id == 0)
	{
		if(NM_NetNode.MsgSendStatus == NM_MSG_SEND_REQ)
		{
			NM_NetNode.MsgSendStatus = NM_MSG_SEND_END;
			gILCanNMMsgTransitFlag = 1;
		}
	}
	#endif
}
void CANbus_Ch1SendInterruptCallBack(void)
{
	if(CANbusMsgSendCnt[1]>0)
	{
		CANbusMsgSendCnt[1]--;
	}
	#ifdef NM_ENABLE_MACRO
	if(NM_NetNode.CAN_Id == 1)
	{
		if(NM_NetNode.MsgSendStatus == NM_MSG_SEND_REQ)
		{
			NM_NetNode.MsgSendStatus = NM_MSG_SEND_END;
			gILCanNMMsgTransitFlag = 1;
		}
	}
	#endif
}
/****************************************************************************
 * @function	CANbus_ErrorInterruptCallBack
 * @brief  	the CAN BUS error interrupt callback function.
 * @param  	chno: CAN channal	
 * @retval 	null
 * @attention   null
****************************************************************************/
void CANbus_ErrorInterruptCallBack(uint8_t chno)
{
	
}
#endif
/****************************************************************************
***                                                FILE END
****************************************************************************/


