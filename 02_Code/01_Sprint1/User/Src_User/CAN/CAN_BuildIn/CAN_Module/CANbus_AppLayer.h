/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CANbus_AppLayer.h
* Target MCU:		V850SJ3
* Module:
* Summary:		CAN module Application layer header file
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
#ifndef _CANBUS_APPLAYER_H
#define _CANBUS_APPLAYER_H

#define CAN_RCV_CHK_TIME_MAX		TIMER_2000MS
#define CAN_RCV_LOST_RST_CNT		3

typedef enum can_mode_enum
{
	CAN_APP_MODE_START = 0,
	CAN_APP_MODE_INIT = 1,
	CAN_APP_MODE_IDLE,
	CAN_APP_MODE_OFF,
	CAN_APP_MODE_BUSOFF,
	CAN_APP_MODE_SLEEP,
	CAN_APP_MODE_ON = 0x10,
	CAN_APP_MODE_PRESLEEP,
}CANAPP_MODE_ENUM;

typedef enum can_startup_enum
{
	CAN_STARTUP_PWRON,	// Open Power Supply
	CAN_STARTUP_INIT1,		
	CAN_STARTUP_INIT2,	
	CAN_STARTUP_INIT3,	
	CAN_STARTUP_END,		
}CAN_STARTUP_ENUM;

typedef enum canapp_busoff_enum
{
	CANAPP_BUSOFF_START,
	CANAPP_BUSOFF_STEP1,		
	CANAPP_BUSOFF_STEP2,	
	CANAPP_BUSOFF_DELAY,
	CANAPP_BUSOFF_DELAY1,
	CANAPP_BUSOFF_END,		
}CANAPP_BUSOFF_ENUM;

typedef enum canapp_sleep_enum
{
	CANAPP_SLEEP_REQ,
	CANAPP_SLEEP_WAKE_CHK,		
	CANAPP_SLEEP_WAKE_INIT,	
	CANAPP_SLEEP_EXIT,		
}CANAPP_SLEEP_ENUM;

typedef struct{
	CAN_STARTUP_ENUM  Startup_Step;
	CANAPP_MODE_ENUM CANopMode;
	CANAPP_SLEEP_ENUM CANSleepStep;
	uint8_t      BusOffStatus;
	uint8_t	  RstCnt;			/*CAN module couldn't receive message, Reset module count number */
	uint16_t	  RcvChkTimer;	/*CAN receive message check timer, when overtime 2s , reset CAN */
}CANAppLayerStruct;

typedef struct{
	uint8_t BusoffStep;
	uint8_t ResetCount;
	uint8_t BusOffCount;
	uint16_t Timer;
	uint8_t Timer1;
}BusOffStateStruct;

typedef struct
{
	uint8_t state		:1;
	uint8_t BusCh		:2;
	uint8_t reserved	:5;
	uint8_t *pData;
	uint8_t size;
	uint8_t TransIndex;
	uint8_t TransNum;
	uint8_t Timer;
}TransCtlStruct;	

#define BUSOFF_RECOVERY_QUICK         TIMER_50MS
#define BUSOFF_RECOVERY_QUICK_CNT	  10		// Quick Recovery count. (5 for zotye)
#define BUSOFF_RECOVERY_SLOW          TIMER_1000MS

CAN_EXTERN uint8_t CANbus_JudgeCANIdValid(uint8_t can_id);

/****************************************************************************
 * @function	CANbus_SetTxReqStatusBit
 *			CANbus_ClearTxReqStatusBit
 *			CANbus_GetCurTxReqStatusBit
 * @brief  	CAN message Transmit Request status operation.
 *			there are three type message: APP/NM/UDS, when request send the message.we 
 *			mark the correspond status bit to 1, when dealed done, we can clear the status bit.
 *			we also can read the status bit by the function of CANbus_GetCurTxReqStatusBit.
 * @param  	null				
 * @retval 	null
 ****************************************************************************/
CAN_EXTERN void 	CANbus_SetTxReqStatusBit(uint8_t  canch, uint8_t MsgTypeMask);
CAN_EXTERN void 	CANbus_ClearTxReqStatusBit(uint8_t  canch, uint8_t MsgTypeMask);
CAN_EXTERN uint8_t 	CANbus_GetCurTxReqStatusBit(uint8_t  canch, uint8_t MsgTypeMask);

/****************************************************************************
 * @function	CANbus_AppLayerSetInitParam
 * @brief  	setting initialization parameter to the can module.
 * @param  	null				
 * @retval 	null
 ****************************************************************************/
CAN_EXTERN void 	CANbus_AppLayerSetInitParam(CAN_INIT_STRUCT *pInitParam);

/****************************************************************************
 * @function	CANbus_AppLayerColdInit
 * @brief  	Cold initialization
 * @param  	null				
 * @retval 	null
 ****************************************************************************/
CAN_EXTERN void 	CANbus_AppLayerColdInit(void);

/****************************************************************************
 * @function	CANbus_AppLayerTimerDeal
 * @brief  	AppLayer Timer deal
 * @param  	null				
 * @retval 	null
 ****************************************************************************/
CAN_EXTERN void 	CANbus_AppLayerRealTimerDeal(void);
CAN_EXTERN void 	CANbus_AppLayerSoftTimerDeal(uint8_t chno);

/****************************************************************************
 * @function	CANbus_AppLayerHandler
 * @brief  	CAN module Application deal
 * @param  	chno:  the CAN channl				
 * @retval 	null
 ****************************************************************************/
CAN_EXTERN void 	CANbus_AppLayerHandler(uint8_t CANCh);

/****************************************************************************
 * @function	CANbus_AppLayerGetMsg
 * @brief  	Get CAN message,  use query mode
 * @param  	pRxMessage : a point to the Receive MSG struct buffer
 * @retval 	0: get a message
 *                     other: not get valid messge
 * @attention:   just get the user application message. UDS/NM message not deal 
 *****************************************************************/
CAN_EXTERN uint8_t   CANbus_AppLayerGetMsg(CanMsgStruct *pRxMessage);

/****************************************************************************
 * @function	CANBus_AppLayerGetMode
 * @brief  	get work mode 
 * @param  	null
 * @retval 	work mode
 ****************************************************************************/
CAN_EXTERN uint8_t  CANBus_AppLayerGetMode(uint8_t chno);

/****************************************************************************
 * @function	CANbus_AppLayerReqSwitchMode
 * @brief  	request  CAN bus to switch work mode
 * @param  	mode : work mode		
 * @retval 	null
 ****************************************************************************/
CAN_EXTERN void 	CANbus_AppLayerReqSwitchMode(uint8_t chno, CANAPP_MODE_ENUM  mode);

/****************************************************************************
 * @function	CANbus_AppLayerReqShutDown
 * @brief  	request shut down CAN bus
 * @param  	chno:  the CAN channl				
 * @retval 	null
 ****************************************************************************/
CAN_EXTERN void 	CANbus_AppLayerReqShutDown(uint8_t chno);

/****************************************************************************
 * @function	CANbus_AppLayerReqSleep
 * @brief  	request  CAN bus to enter sleep mode 
 * @param  	Null		
 * @retval 	null
 ****************************************************************************/
CAN_EXTERN void 	CANbus_AppLayerReqSleep(uint8_t chno);

/****************************************************************************
 * @function	CANbus_AppLayerSendPeriodicMsg
 * @brief  	periodic send message
 * @param  	pTxMsg: point to the translate mesage buffer
 *                     cycleTime: periodic cycle time
 * @retval 	0: ok
 *                     other: some exception produce
 * @attention:  the maximum number of periodic msg buffer is controled 
                         by macro "CAN_PERIODIC_POOL_SIZE"
 ***************************************************************************/
CAN_EXTERN uint8_t 	CANbus_AppLayerSendPeriodicMsg(CanMsgStruct *pTxMsg, uint16_t cycleTime);

/****************************************************************************
 * @function	CANbus_AppLayerSendOneShotMsg
 * @brief  	send a message just one
 * @param  	pTxMsg: point to the translate mesage buffer
 * @retval 	null
 * @attention:  
 ****************************************************************************/
CAN_EXTERN void 	CANbus_AppLayerSendOneShotMsg(CanMsgStruct *pTxMsg);

/****************************************************************************
 * @function	CANbus_AppLayerSendNMMsg
 * @brief  	send OSEK Network Managerment Message.
 * @param  	pTxMsg: point to the translate mesage buffer
 * @retval 	0- send normal 1- not send
 * @attention:  
 ****************************************************************************/
CAN_EXTERN uint8_t 	CANbus_AppLayerSendNMMsg(CanMsgStruct *pTxMsg);

CAN_EXTERN void 		CANbus_AppLayerClearRcvChkState(uint8_t chno);

CAN_EXTERN void 		CANbus_InforOutputReq(uint8_t chno, uint8_t *pBuffer, uint8_t len);
CAN_EXTERN void 		CANbus_InforOutputMain(void);
#endif

/****************************************************************************
***                                                FILE END
****************************************************************************/


