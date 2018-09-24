/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CANbus_NetLayer.h
* Target MCU:		V850SJ3
* Module:
* Summary:		CAN module network layer header file
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
#ifndef _CANBUS_NETLAYER_
#define _CANBUS_NETLAYER_

#define CAN_MSG_BUFF_NUM         	10          	/* Receive Msg Buffer Max Number */
#define CANMSG_RCV_FILTER_EN		1	/* same message filter switch */
#define CAN_RCV_FILTER_NUM		20		/* max number of receive message filter buffer*/
#define CAN_PERIODIC_POOL_SIZE      10		/*periodic send message , the max number */

typedef struct 
{
	uint8_t ReceivedNum;
	uint8_t Point_read;
	uint8_t Point_write;
}BuffPointStruct;

CAN_EXTERN uint16_t CANbusMsgSendCnt[CAN_IDMAX];
/****************************************************************************
 * @function	CANbus_NetLayerVarInit
 * @brief  	net layer Var  initialization
 * @param  	null				
 * @retval 	null
****************************************************************************/
CAN_EXTERN void 	CANbus_NetLayerVarInit(void);
/****************************************************************************
 * @function	CANbus_NetLayerReadMsgBuffer
 * @brief  	read a message to the netlayer
 * @param  	pRxMessage: the point to the received message to store				
 * @retval 	0:read a CAN message successful
 *			1: failed, no message or message duplicate
 * @attention   called by this application only, user not used
****************************************************************************/
CAN_EXTERN uint8_t  	CANbus_NetLayerReadMsgBuffer(CanMsgStruct *pRxMessage);
/****************************************************************************
 * @function	CANbus_NetLayerSendManager
 * @brief  	net layer message send manager
 * @param  	null				
 * @retval 	null
 * @attention   called by application layer only, user not used
****************************************************************************/
CAN_EXTERN void 	CANbus_NetLayerSendManager(uint8_t chno);
/****************************************************************************
 * @function	CANbus_NetLayerOneShotSendMsg
 * @brief  	net layer one-shot send a message
 * @param  	pTxMsg: point to the transmite message buffer				
 * @retval 	null
 * @attention   if message is not periodic, user can call this function to send a message
****************************************************************************/
CAN_EXTERN void 	CANbus_NetLayerOneShotSendMsg(CanMsgStruct *pTxMsg);
/****************************************************************************
 * @function	CANbus_NetLayerPeriodicSendMsg
 * @brief  	net layer periodic send message
 * @param  	pTxMsg: point to the transmite message buffer
 *			cycleTime: Cycle time
 * @retval 	0: ok
 *			other: not ok
****************************************************************************/
CAN_EXTERN uint8_t 	CANbus_NetLayerPeriodicSendMsg(CanMsgStruct *pTxMsg, uint16_t cycleTime);

/****************************************************************************
 * @function	CANbus_NetLayerCanclePeriodicMsgSend
 * @brief  	net layer cancle periodic message treansmit, the message ID is given in the parameter
 * @param  	MsgId: the CAN message Id which request to cancle				
 * @retval 	null
 * @attention   
****************************************************************************/
CAN_EXTERN void 	CANbus_NetLayerCanclePeriodicMsgSend(uint8_t chno, uint32_t MsgId);

/****************************************************************************
 * @function	CANbus_NetLayerStopAllSend
 * @brief  	net layer stop all Transmit message
 * @param  	null				
 * @retval 	null
 * @attention   
****************************************************************************/
CAN_EXTERN void 	CANbus_NetLayerStopAllSend(uint8_t chno);

/****************************************************************************
 * @function	CANbus_NetLayerTimerDeal
 * @brief  	net layer Timer deal
 * @param  	null				
 * @retval 	null
****************************************************************************/
CAN_EXTERN void 	CANbus_NetLayerTimerDeal(void);
/****************************************************************************
 * @function	CANbus_NetLayerClearWakeupStatus
 * @brief  	clear the CAN bus netlayer wakeup status
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
CAN_EXTERN void 	CANbus_NetLayerClearWakeupStatus(uint8_t chno);
/****************************************************************************
 * @function	CANbus_NetLayerGetWakeupStatus
 * @brief  	get the CAN bus netlayer wakeup status
 * @param  	null		
 * @retval 	0:not wakeup
 *			1: wakeup
 * @attention   null
****************************************************************************/
CAN_EXTERN uint8_t 	CANbus_NetLayerGetWakeupStatus(uint8_t chno);
CAN_EXTERN void CANbus_NetLayerClearFilterBuff(uint8_t index);

CAN_EXTERN void CANbus_MsgSendReqCallBack(uint8_t chno, uint32_t TxMsgId);
CAN_EXTERN void CANbus_RecvInterruptCallBack(uint8_t chno);
CAN_EXTERN void CANbus_Ch0SendInterruptCallBack(void);
CAN_EXTERN void CANbus_Ch1SendInterruptCallBack(void);
CAN_EXTERN void CANbus_ErrorInterruptCallBack(uint8_t chno);

#endif

/****************************************************************************
***                                                FILE END
****************************************************************************/


