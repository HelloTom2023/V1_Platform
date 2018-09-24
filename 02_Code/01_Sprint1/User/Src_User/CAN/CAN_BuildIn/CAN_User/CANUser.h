#ifndef _CANBUS_APP_USER
#define _CANBUS_APP_USER

#ifndef _CAN_USER_C
#define CANUSER_EXTERN		extern
#else
#define CANUSER_EXTERN
#endif

#define PRODUCT_CHANA_C201

#if 1
#define CAN_INNER_ENABLE
#endif
#if 1
#define CAN_BODY_ENABLE
#endif

//#define CAN_PM_ROUTINE_EN			//CAN BUS PoweManger Routine Enable


#define CAN_TXID_DIAG					0x70e
#define CAN_TXID_TEST					0x7ff

////////////////////S301-protocol//////////////////////
//#define CAN_RXID_GW					0x2B0
//#define CAN_RXID_GW_326				0x326
//#define CAN_RXID_GW_373				0x373
//#define CAN_RXID_IP						0x280
//#define CAN_RXID_BCM_288					0x288
//#define CAN_RXID_BCM_347				0x347
//#define CAN_RXID_ESCL					0x276
//#define CAN_RXID_PAC					0x3D0
//#define CAN_RXID_RRS					0x2E0
//#define CAN_RXID_AC						0x330
#define CAN_RXID_TBOX					0x296
//#define CAN_RXID_RMRA					0x3f0//rear mirror 

/*******C201-15*******************/
//#define CAN_RXID_EMS_265				0x265
//#define CAN_RXID_TCU					0x268
//#define CAN_RXID_ESP					0x218
#define CAN_RXID_IP						0x270
//#define CAN_RXID_PAC					0X3d0
//#define CAN_RXID_GW					CAN_RXID_ESP


//S401 RX
#define CAN_RXID_BCM_349				0x349
#define CAN_RXID_DSM_352				0x352
#define CAN_RXID_DSM_340				0x340//空调1
#define CAN_RXID_DSM_330				0x330//空调2
//#define CAN_RXID_DVR_612				0x612
#define CAN_RXID_AVM_3E0				0x3E0
#define CAN_RXID_BCM_288				0x288
#define CAN_RXID_PEPS_266				0x266
//#define CAN_RXID_RRS_2E0				0x2E0
#define CAN_RXID_ESP_320				0x320//车速信号
#define CAN_RXID_LCM_5F0				0x5F0//背光亮度
#define CAN_RXID_IGN_2B0				0x2B0//发动机状态
#define CAN_RXID_BCM_5FF				0x5FF//雨刮
#define CAN_RXID_IP_380				0x380//剩余油量等级
#define CAN_RXID_IP_280               0X280
#define CAN_RXID_IP_260               0X260
#define CAN_RXID_GW_2FF               0x2FF
#define CAN_RXID_GW_2B0               0X2B0
#define CAN_RXID_GW_326               0X326
#define CAN_RXID_GW_373               0X373
#define CAN_RXID_GW_2A8               0X2A8

//R103-H15T
#define CAN_RXID_GW						CAN_RXID_GW_32A   
#define CAN_RXID_BCM						CAN_RXID_BCM_347  
#define CAN_RXID_ESP                       CAN_RXID_ESP_368
#define CAN_RXID_RRS						CAN_RXID_RRS_2E0
#define CAN_RXID_EMS						CAN_RXID_EMS_255
#define CAN_RXID_AC						CAN_RXID_AC_330

#define CAN_RXID_GW_320                    0X320  //snake20160727  Receive but don't deal
#define CAN_RXID_GW_32A                    0x32A  //snake20160523  Receive but don't deal
#define CAN_RXID_BCM_347                   0x347 //tpms data msg  snake20160523
#define CAN_RXID_ESP_218                   0x218  //snake20160727  Receive but don't deal
#define CAN_RXID_ESP_368                   0x368  //snake20160523  Receive but don't deal
#define CAN_RXID_RRS_2E0					0x2E0
#define CAN_RXID_DVR_612					0X612
#define CAN_RXID_DVR_613					0X613
#define CAN_RXID_AC_330					0X330//snake20160727  Receive but don't deal
#define CAN_RXID_EMS_255					0X255//snake20160727  Receive but don't deal
#define CAN_RXID_PAC_3D0                   0X3D0

#define CAN_RXID_FACTORY_TEST_001		0x001//用于产线测试板快速进入待机模式

#define CAN_UDS_RXID_PHY				0x706//physical address 
#if(PROJECT_CODE == CHANGAN_R103_H15T)
	#define CAN_UDS_RXID_FUNC				0x7DF//function address 
#elif(PROJECT_CODE == CHANGAN_S401)
	#define CAN_UDS_RXID_FUNC				0x77F//function address 
#endif
typedef enum{
	//CAN_RXID_GW_FILTER,
	//CAN_RXID_BCM_FILTER,
	//CAN_RXID_PEPS_FILTER,
	//CAN_RXID_ESCL_FILTER,
	//CAN_RXID_PAC_FILTER,
	//CAN_RXID_RRS_FILTER,
	//CAN_RXID_AC_FILTER,
	//CAN_RXID_AVM_FILTER,
	//CAN_RXID_TBOX_FILTER,
	CAN_RXID_IP_FILTER,
	CAN_RXID_DVR_612_FILTER,
	CAN_RXID_DVR_613_FILTER,
	CAN_RXID_330_FILTER,
	CAN_RXID_340_FILTER,
	CAN_RXID_352_FILTER,
	CAN_RXID_349_FILTER,
	CAN_RXID_2E0_FILTER,
	CAN_RXID_320_FILTER,
	CAN_RXID_5F0_FILTER,
	CAN_RXID_2B0_FILTER,
	CAN_RXID_5FF_FILTER,
	CAN_RXID_2FF_FILTER,
	
/*-----------INNER CAN SYSTEM-------------*/
	CAN_RXID_DTV_FILTER,
	CAN_RXID_DTV_VER_FILTER,
	CAN_RXID_FCP_FILTER,
	CAN_RXID_LRHD_FILTER,
	CAN_RXID_RRHD_FILTER,
	CAN_RXID_KEY_FILTER,
	CAN_RXID_END_FILTER
}eCAN_FILTER_INDEX;

//S401 
#define CAN_TX_ID2F8				0x2F8//行车记录仪
#define CAN_TX_ID513				0x513//AVM SLIP message ID 
#define CAN_TX_ID2F9				0x2F9//设置空调
#define CAN_TX_ID600				0x600//车辆设置
#define CAN_TX_ID601				0x601//车辆设置
#define CAN_TX_ID2FA				0x2FA//导航限速
#define CAN_TX_ID500				0x500//经纬度
#define CAN_TX_ID501				0x501//时间
#define CAN_TX_ID2E9				0x2E9//外置功放
#define CAN_TX_ID580				0x580//里程保养


//////////////////////////////////////////////////////
#define CAN_RXID_TEST				0X6F0//0x7f0


// next define used for select the CAN receiver.
#define STB_CAN0_ON				STB_TJA1041_ON
#define STB_CAN1_ON				STB_TJA1040_ON

#define CAN_ID_BODY					CAN_ID0
#define CAN_ID_INNER				CAN_ID1

typedef struct
{
	uint8_t UsedCANNum;
	/*max num = 2, the first Id must used for vehicle body, local CAN can't put this */
	uint8_t UsedCANId[2];
	/*used for config body can or inner can*/
	//uint8_t CanTypeCfg[2];
	/*OSEK NM CAN ID select */
	uint8_t NMCanId;
}CAN_USED_CFG;

extern uint8_t AvmCnt;
extern void ( *const pCANUserFuncTbl[] )(uint8_t *pMsg, uint8_t len);
extern CANMsgType CANUser_UsedMsgData[];

CANUSER_EXTERN uint32_t CanPmRecTimer;
CANUSER_EXTERN uint8_t CanPmEnterStandbyFlg;

#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
CANUSER_EXTERN void CAN_Get_Body513Data(void);

#endif
CANUSER_EXTERN uint8_t CANUser_GetFuncTblSize(void);
CANUSER_EXTERN uint8_t CANUser_GetUsedMsgNum(void);
CANUSER_EXTERN void CANUser_InitParam(CAN_USED_CFG* pCfg);
CANUSER_EXTERN void CANUser_TaskTickHook(uint8_t tickBase);
CANUSER_EXTERN void CANUser_UdsCfg(void);
CANUSER_EXTERN void CANUser_StartSendInitMsg(uint8_t CANch);
CANUSER_EXTERN	void CANUser_SendMsg500(void);
CANUSER_EXTERN	void CANUser_SendMsg501(void);
CANUSER_EXTERN void CANUser_SendMsg2F8(void);
CANUSER_EXTERN void CANUser_SetBodyCanMsgOnce(uint8_t *pMsg, uint32_t CAN_ID);
CANUSER_EXTERN void CANUser_SetBodyCanMsgPeriodic(uint8_t *pMsg, uint32_t CAN_ID, uint16_t cycleTime);
CANUSER_EXTERN void CANUser_ParamColdInit(void);
CANUSER_EXTERN void CANUser_ParamWarmInit(void);
CANUSER_EXTERN void CANUser_ReceiveCANMsgHandler(CanMsgStruct *pRxMsg);

CANUSER_EXTERN void CANUser_TryToSendCANMsg(uint8_t CANch);
CANUSER_EXTERN void CANUser_InitWorkOn(void);

CANUSER_EXTERN CanMsgStruct * 	CANUser_RcvFilterPreDeal(CanMsgStruct *pRxMessage, CanMsgStruct *pFilterBuffer);
CANUSER_EXTERN uint8_t  CANUser_MsgFilter_Step2(CanMsgStruct *pRxMessage);

CANUSER_EXTERN void CANUser_SetAvmOutCmd(void);
CANUSER_EXTERN void CANUser_SetAvmInCmd(void);
CANUSER_EXTERN void CANUser_SetAmpCmd(uint8_t Type, uint8_t Cmd);


/****************************************************************************
 * @function	CANbus_GetTransceiverErrorState
 * @brief  	This function get the CAN transceiver error state.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
CANUSER_EXTERN uint8_t CANbus_GetTransceiverErrorState(uint8_t chno);
CANUSER_EXTERN void  CANUser_DebugInfoOutput(uint8_t can_id, uint8_t *pBuffer, uint8_t len);
CANUSER_EXTERN void CANUser_SetBodyCanMsgOnce(uint8_t *MSG, uint32_t CAN_ID);

#endif

