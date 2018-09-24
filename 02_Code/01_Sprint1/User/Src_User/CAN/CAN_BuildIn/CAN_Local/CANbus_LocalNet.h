#ifndef  _CANBUS_LOCAL_NET_H
#define _CANBUS_LOCAL_NET_H

#ifdef CANBUS_LOCAL_C
#define CANBUS_LOCAL		
#else
#define CANBUS_LOCAL     extern 
#endif

#if  D_PRINT_EN
#define InnerCAN_Dbg(x)  			x
#else
#define InnerCAN_Dbg(x)
#endif


typedef struct
{
	uint16_t DTV;
	uint16_t FCP;
	uint16_t LRHD;
	uint16_t RRHD;
}TIMER_STRUCT;

typedef struct
{
	uint16_t CurNo;
	uint16_t TotalNo;
	uint8_t    PlaySecond;
	uint16_t    PlayMinute;
	uint8_t	TotalSecond;
	uint16_t   TotalMinute;
}HUMediaInfoStruct;

#define DTV_DYNAMIC_CHK_EN			0		/*DTV dynamic check */


#define CAN_RXID_INNER_KEY				0x612
#define CAN_RXID_INNER_TEST				0x7f0
#define CAN_RXID_INNER_OSEK				0x400

#define CAN_RXID_INNER_LRHD_0			0x520
#define CAN_RXID_INNER_LRHD_1			0x525
#define CAN_RXID_INNER_RRHD_0			0x530
#define CAN_RXID_INNER_RRHD_1			0x535
#define CAN_RXID_INNER_FCP				0x540
#define CAN_RXID_INNER_DTV_0				0x550
#define CAN_RXID_INNER_DTV_VER			0x551//DTV Version
#define CAN_RXID_INNER_DTV_CAST			0x555
#define CAN_RXID_INNER_DTV_LIST			0x556
#define CAN_RXID_INNER_DTV_CA			0x557

#define CAN_TXID_INNER_HU_510			0x510//cycle state
#define CAN_TXID_INNER_HU_515			0x515//radio frequency
#define CAN_TXID_INNER_HU_516			0x516//media information
#define CAN_TXID_INNER_HU_517			0x517//song title
#define CAN_TXID_INNER_HU_518			0x518//event request.


#define CAN_TX_INNER_CYCLE				TIMER_100MS

#define CAN_INNER_SYS_SLEEP			0x00
#define CAN_INNER_SYS_STANDBY		0x01
#define CAN_INNER_SYS_NORMAL			0x02
#define CAN_INNER_SYS_INVALID			0x07

extern TIMER_STRUCT		InnerTimerStr;
extern CanMsgStruct			HUInnerCycleMsg;

CANBUS_LOCAL void CANbus_InnerInit(void);
CANBUS_LOCAL void CANbus_InnerTimerHandler(void);
CANBUS_LOCAL void CANbus_InnerWriteAccStatus(uint8_t status);
CANBUS_LOCAL void CANbus_InnerWriteSysStatus(uint8_t status);
CANBUS_LOCAL void CANbus_InnerWriteIllStatus(uint8_t ill);
CANBUS_LOCAL void CANbus_InnerWriteControlMode(uint8_t mode);
CANBUS_LOCAL void CANbus_InnerWriteIllLevel(uint8_t level);
CANBUS_LOCAL void CANbus_InnerWriteRadioBand(uint8_t band);
CANBUS_LOCAL void CANbus_InnerWriteReverseStatus(uint8_t status);
CANBUS_LOCAL void CANbus_InnerReqSendMsg(uint32_t MsgId, uint16_t index);
CANBUS_LOCAL void CANbus_InnerWritePlayTime(uint8_t *pData);
CANBUS_LOCAL void CANbus_InnerWritePlayInfo(uint8_t *pData);
CANBUS_LOCAL void CANbus_InnerWriteMediaTitle(uint8_t *pData);
CANBUS_LOCAL void CANbus_InnerWriteRadioInfo(void);
/****************************************************************************
 * @function	CANbus_InnerStartSendMsg
 * @brief  	HU set initial periodic message buffer
 * @param  	flag
 * @retval 	null
 * @attention:  null
****************************************************************************/
CANBUS_LOCAL void CANbus_InnerStartSendMsg(uint8_t flag);

/****************************************************************************
 * @function	CANbus_InnerDTVHandler
 * @brief  	DTV CAN BUS message handler
 * @param  	pRxMsg: received message
 * @retval 	null
 * @attention:  null
****************************************************************************/
CANBUS_LOCAL void CANbus_InnerDTVHandler(CanMsgStruct *pRxMsg);

/****************************************************************************
 * @function	CANbus_InnerFCPHandler
 * @brief  	FCP (Front Control Panel) CAN BUS message handler
 * @param  	pRxMsg: received message
 * @retval 	null
 * @attention:  null
****************************************************************************/
CANBUS_LOCAL void CANbus_InnerFCPHandler(CanMsgStruct *pRxMsg);

/****************************************************************************
 * @function	CANbus_InnerRHDHandler
 * @brief  	RHD (Rear HeaD rest) CAN BUS message handler
 * @param  	pRxMsg: received message
 * @retval 	null
 * @attention:  null
****************************************************************************/
CANBUS_LOCAL void CANbus_InnerRHDHandler(CanMsgStruct *pRxMsg);

CANBUS_LOCAL ExtMediaDataStruct*pCAN_GetExtDtvInfoData(void);

CANBUS_LOCAL void CANbus_InnerSendExtDataToApu(SegTransCtlStruct *pStr);
CANBUS_LOCAL void CANbus_InnerLoop(void);

#endif

