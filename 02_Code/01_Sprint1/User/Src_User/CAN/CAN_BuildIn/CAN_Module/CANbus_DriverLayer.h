/****************************************************************************
* copyright:		JX Coagent Co.ltd.
* filename:		CANbus_NetLayer.h
* Target MCU:		V850SJ3
* Module:			CAN Module
* Summary:		CAN module CAN Bus phyiscal  layer Driver header file
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
#ifndef     _v850_CAN_DRV_
#define     _v850_CAN_DRV_


#define CAN_RCV_FILTER_MAX		23

#define CAN_INT_TX_EN				1

typedef struct
{
	uint8_t validFlag;
	uint8_t can_Id;			/*CAN_ID0, CAN_ID1 */
	uint8_t can_BpsType;		/*CAN_BPS_100K, CAN_BPS_125K, CAN_BPS_250K, CAN_BPS_500K*/
	uint8_t can_SendBuffNum;	/* Send Message buffer number, 1 for direct oneshot send, other for periodic send */
	uint8_t can_RecvFilterNum;	/* The num of the receive filter Buffer number , max value is 15 */
	uint16_t can_RecvFilter[CAN_RCV_FILTER_MAX];	/* only support Standard data frame */
/*
  *  next config the MASK TABLE
  */
	uint8_t  MASKValidNum;			/* MASK valid num, maximum is 4, if not use the MASK, please ensure value 0 */
	uint16_t can_RecvFilterCmp[4];	/*recv mask compare value */
	uint16_t can_RecvMASK[4];		/*4 reveive filter rigister value , compare is 0, uncompare is 1 */
}CAN_INIT_STRUCT;

// CAN baudRate macro
#define CAN_BPS_100K		0
#define CAN_BPS_125K		1
#define CAN_BPS_250K		2
#define CAN_BPS_500K		3

#define STB_TJA1040_ON	1
#define STB_TJA1041_ON	0

//MCU critical enter and exit macro
#define CAN_ENTER_CRITICAL_REGION()		__asm("di")
#define CAN_EXIT_CRITICAL_REGION()		__asm("ei")
// CAN Transceiver work mode!
#define CAN_TRANSCEIVER_MODE_NORMAL			0	//normal mode
#define CAN_TRANSCEIVER_MODE_LISTEN_ONLY		1	//listern only mode
#define CAN_TRANSCEIVER_MODE_STANDBY		2	//standby mode
#define CAN_TRANSCEIVER_MODE_SLEEP			3	//sleep mode
// CAN Controller work mode!!
#define CAN_WORKMODE_INIT				0		
#define CAN_WORKMODE_NORMAL			1
#define CAN_WORKMODE_LISTENONLY			2
#define CAN_WORKMODE_TEST				3
// CAN interrupt type
#define CAN_INT_REC						0
#define CAN_INT_TX						1
#define CAN_INT_WAKEUP					2
#define CAN_INT_ERROR					3
// function declare
CAN_EXTERN uint8_t CANWakeupStatus;
CAN_EXTERN void CANbus_DefaultInit(uint8_t chno);
/****************************************************************************
 * @function	CANbus_ChShutDown
 * @brief  	This function forcibly shuts down CAN-controller.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: OK, other : fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_ChShutDown(uint8_t chno);
/****************************************************************************
 * @function	CANbus_ChGetBusStatus
 * @brief  	This function acquires the CAN channel's bus status.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	return INFO value
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_ChGetBusStatus(uint8_t chno);
/****************************************************************************
 * @function	CANbus_GetIntBuffNumber
 * @brief  	This function acquires the CAN message buffer index when receive inttrupt accor
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0~31
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_GetIntBuffNumber(uint8_t chno);
/****************************************************************************
 * @function	CANbus_ChEnable
 * @brief  	This function enable the CAN Controller channal
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: OK, other : fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_ChEnable(uint8_t chno, CAN_INIT_STRUCT *pInitParam);
/****************************************************************************
 * @function	CANbus_EnableCANTransceiver
 * @brief  	This function eanble the CAN transceiver to enter mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			mode: CAN_TRANSCEIVER_MODE_NORMAL//CAN_TRANSCEIVER_MODE_LISTEN_ONLY
 *				CAN_TRANSCEIVER_MODE_STANDBY//CAN_TRANSCEIVER_MODE_SLEEP
 * @retval 	null
 * @attention   null
****************************************************************************/
CAN_EXTERN  void 	CANbus_EnableCANTransceiver(uint8_t chno, uint8_t mode);
/****************************************************************************
 * @function	CANbus_IsBusOffStatus
 * @brief  	This function acquires the BUS off stauts
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: bus ok, 1: busoff
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_IsBusOffStatus(uint8_t chno);
/****************************************************************************
 * @function	CANbus_EnterSleepMode
 * @brief  	This function acquires the CAN controller enter to sleep mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_EnterSleepMode(uint8_t chno);
/****************************************************************************
 * @function	CANbus_ExitSleepMode
 * @brief  	This function acquires the CAN controller exit sleep mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_ExitSleepMode(uint8_t chno);
/****************************************************************************
 * @function	CANbus_SetNormalMode
 * @brief  	This function setting  the CAN controller to enter normal mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_SetNormalMode(uint8_t chno);
/****************************************************************************
 * @function	CANbus_SetListenOnlyMode
 * @brief  	This function setting  the CAN controller to enter listen only mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   just read bus data, not send data.
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_SetListenOnlyMode(uint8_t chno);
/****************************************************************************
 * @function	CANbus_SetSelfTestMode
 * @brief  	This function setting  the CAN controller to enter Self-test mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t CANbus_SetSelfTestMode(uint8_t chno);
/****************************************************************************
 * @function	CANbus_ChSetInitMode
 * @brief  	This function setting  the CAN controller to enter initialization  mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t	CANbus_ChSetInitMode(uint8_t chno);
/****************************************************************************
 * @function	CANbus_GetMode
 * @brief  	This function acquires the CAN channel's operation mode and power-saving mode.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t	CANbus_GetMode(uint8_t chno);
/****************************************************************************
 * @function	CANbus_MsgSetDat
 * @brief  	This function sets data to the CAN channel's message buffer.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 *			p_data :	start address of area for storing message data
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t	CANbus_MsgSetDat(uint8_t chno, uint8_t bufno, uint8_t* p_data);
/****************************************************************************
 * @function	CANbus_MsgSetIdDataDlc
 * @brief  	This function sets the CAN-ID, data and data length to the CAN  message buffer.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 *			p_data :	start address of area for storing message data
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t	CANbus_MsgSetIdDataDlc(uint8_t chno, uint8_t bufno, uint32_t canid, uint8_t* p_data, uint8_t dlc);
/****************************************************************************
 * @function	CANbus_MsgGetDatDlc
 * @brief  	This function acquires the data and data length from the CAN  message buffer.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 *			p_data :	start address of area for storing message data
 *			p_dlc :	Start address of area for storing message length
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t	CANbus_MsgGetDatDlc(uint8_t chno, uint8_t bufno, uint8_t* p_data, uint8_t* p_dlc);
/****************************************************************************
 * @function	CANbus_MsgGetIdDataDlc
 * @brief  	This function acquires the CAN-ID.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 *			canid :	start address of area for storing CAN-ID
 *			p_data :	start address of area for storing message data
 *			dlc :	start address of area for storing message length
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t	CANbus_MsgGetIdDataDlc(uint8_t chno, uint8_t bufno, uint32_t* canid, uint8_t* p_data, uint8_t* dlc);
/****************************************************************************
 * @function	CANbus_MsgTxReq
 * @brief  	This function sets the transmit request bit in the CAN channel's message buffer.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CAN_EXTERN 	uint8_t	CANbus_MsgTxReq(uint8_t chno, uint8_t bufno);

/****************************************************************************
 * @function	CANbus_RecoveryFromBusOff
 * @brief  	This function recovery the CAN transceiver from the busoff state.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	null
 * @attention   null
****************************************************************************/
CAN_EXTERN 	void CANbus_RecoveryFromBusOff(uint8_t chno);

/****************************************************************************
 * @function	CANbus_ErrorDeal
 * @brief  	This function deal the error state
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	null
 * @attention   null
****************************************************************************/
CAN_EXTERN 	void CANbus_ErrorDeal(uint8_t chno);

/****************************************************************************
 * @function	CANbus_Init
 * @brief  	This function initializes the CAN module. the port, interrput as so on
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	null
 * @attention   null
****************************************************************************/
CAN_EXTERN 	void CANbus_Init(uint8_t chno);

/****************************************************************************
 * @function	CAN0_INTWUP
 * @brief  	This function is wakeup interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
CAN_EXTERN 	void CAN0_INTWUP(void);
CAN_EXTERN 	void CAN0_INTREC(void);
CAN_EXTERN 	void CAN0_INTTRX(void);
CAN_EXTERN 	void CAN0_INTERR(void);

/****************************************************************************
 * @function	CAN1_INTWUP
 * @brief  	This function is wakeup interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
CAN_EXTERN 	void CAN1_INTWUP(void);
CAN_EXTERN 	void CAN1_INTREC(void);
CAN_EXTERN 	void CAN1_INTTRX(void);
CAN_EXTERN 	void CAN1_INTERR(void);

#endif

/****************************************************************************
***                                                FILE END
****************************************************************************/

