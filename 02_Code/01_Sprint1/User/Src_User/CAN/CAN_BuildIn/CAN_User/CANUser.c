#define _CAN_USER_C
#include "..\..\..\config\inc.h"

#ifdef  CAN_MODULE_ENABLE
#define CANUser_debug(x)		//x

typedef struct
{
	uint8_t ReverseSignalCnt		:4;
	uint8_t ReverseValidFlag		:1;
	uint8_t ECOChgFlag			:1;
	uint8_t TUIDReq				:2;
	uint8_t AVMexitFlag			:4;
	uint8_t CANMsgSendflag		:4;
	uint8_t ECOTimer;
	uint8_t TUIDRegState			:2;
	uint8_t TUIDRegCnt			:4;
	uint8_t AvmSlipInfoFlag			:1;
	uint8_t Reserved				:1;
}CANUSER_VAR_STRUCT;
CANUSER_VAR_STRUCT CANUserVar;

uint16_t AvmDispTime;

uint8_t AvmCnt=0;
uint8_t AvmDelay=0;
uint8_t ID2F9CanMsgSendFlag = 0;
uint16_t AC_ID330Cnt=0;
uint16_t InnerCanCnt=0;
uint8_t CurrExtTempValid,PreExtTempValid;
uint8_t ID5F0BLMCnt = 0;
uint8_t  PreFuelLevel = 0xFF;

void CANUser_Msg500And501Init(void);
CANUSER_EXTERN void CANUser_Null(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_LightOffDelaySettingDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_TurnBlinkTimeSettingDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_KeyDoorUnlockSettingDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_DriveDoorLockSettingDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_ParkDoorUnlockSettingDeal(uint8_t *pMsg, uint8_t len);

CANUSER_EXTERN void CANUser_AccCtlDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_FcwDataDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_AutoBrakeDataDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_BsdDataDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_CtaDataDeal(uint8_t *pMsg, uint8_t len);	
CANUSER_EXTERN void CANUser_RcwDataDeal(uint8_t *pMsg, uint8_t len);		
CANUSER_EXTERN void CANUser_LdwSensitivityDataDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SlaSwitchDataDeal(uint8_t *pMsg, uint8_t len);  
CANUSER_EXTERN void CANUser_HmaDataDeal(uint8_t *pMsg, uint8_t len);	
CANUSER_EXTERN void CANUser_DrlDataDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_CamLineDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_ACGlassHeatDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_ACECOSwitch(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_AirSensitivity(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_Pollen_Filter_Switch(uint8_t *pMsg, uint8_t len);

CANUSER_EXTERN void CANUser_ACWindLevelStepAdjDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_ACSeatHeatDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_TboxVINMsgHandler(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_TboxPhoneMsgHandler(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_MaintainDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_RemoteSearch_Deal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_LampDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_IllDeal(uint8_t *pMsg, uint8_t len);

CANUSER_EXTERN void CANUser_SysIllDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_WindowDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_DoorDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_RearBagDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_WiperDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_EngineDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_CruiseDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_NAVIDATADeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_TboxCmdDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_AutowindSet(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_TimeSendDeal(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_Dummy(uint8_t *pMsg, uint8_t len);





//S401
CANUSER_EXTERN void CANUser_SetACRefrigeration(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetACCircleMode(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetACSwitch(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetACWindRegion(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetACWindTemp(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetACWindMode(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetACWindLevel(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetACAuto(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetACDefrost(uint8_t *pMsg, uint8_t len);

CANUSER_EXTERN void CANUser_SetAtmospher(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetSeatState(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_WiperDeal(uint8_t *pMsg, uint8_t len);

CANUSER_EXTERN void CANUser_SetMirrorState(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetRecover(uint8_t *pMsg, uint8_t len);

CANUSER_EXTERN void CANUser_SetNaviInfo(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetExtAmp(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetDvrInfo(uint16_t param,uint8_t *pTxdata);
CANUSER_EXTERN void CANUser_SetAvmSlipInfo(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetAVMCmd(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetAcReset(uint8_t *pMsg, uint8_t len);
CANUSER_EXTERN void CANUser_SetAvmOutCmd(void);
CANUSER_EXTERN void CANUser_SetAvmInCmd(void);



// Function Array
void ( *const pCANUserFuncTbl[] )(uint8_t *pMsg, uint8_t len) = 
{
	CANUser_CamLineDeal,			       	/* index = 0 */

	//{add s401
	CANUser_SetAtmospher,		        /* index = 1 */
	//}add s401

	CANUser_LampDeal,				/* index = 2 */
	CANUser_WindowDeal,			      	/* index = 3 */
	CANUser_DoorDeal,			        /* index = 4 */
	CANUser_WiperDeal,                       	/* index = 5 */

	//{add s401
	CANUser_SetMirrorState,			/* index = 6 */
	//}add s401
	
	CANUser_CruiseDeal,			        /* index = 7 */
	CANUser_MaintainDeal,				/* index = 8 */
	
	//{add s401
	CANUser_SetAVMCmd,				/* index = 9 */
	//}add s401

	CANUser_RemoteSearch_Deal,		/* index = 0x0a */
	CANUser_TboxCmdDeal,			/* index = 0x0b */
	CANUser_TimeSendDeal,			/* index = 0x0c */
	CANUser_Dummy,				 	/* index = 0x0d */
	
	//{add s401
	CANUser_SetAvmSlipInfo,			/* index = 0x0e */
	CANUser_SetNaviInfo,				/* index = 0x0f */
	//}add s401

	//空调部分设置
	//{add s401
	CANUser_SetACSwitch,				/* index = 0x10 */
	CANUser_SetACWindTemp,			/* index = 0x11 */
	CANUser_SetACWindMode,			/* index = 0x12 */
	CANUser_SetACWindLevel,			/* index = 0x13 */
	CANUser_SetACRefrigeration,		/* index = 0x14 */
	CANUser_SetACAuto,				/* index = 0x15 */
	CANUser_SetACCircleMode,			/* index = 0x16 */
	CANUser_SetACWindRegion,			/* index = 0x17 */
	CANUser_SetACDefrost,			/* index = 0x18 */
	//}add s401
	CANUser_ACGlassHeatDeal,			/* index = 0x19 */
	CANUser_ACECOSwitch,			/* index = 0x1a */
	CANUser_AirSensitivity,			/* index = 0x1b */
	CANUser_Pollen_Filter_Switch,		/* index = 0x1c */	
	CANUser_ACSeatHeatDeal,			/* index = 0x1d */
	CANUser_TboxVINMsgHandler,		/* index = 0x1e */
	CANUser_TboxPhoneMsgHandler,		/* index = 0x1f */
	CANUser_AutowindSet,				/* index = 0x20 */

	//{add s401
	CANUser_SetExtAmp,			/* index = 0x21 */
	CANUser_SetRecover,				/* index = 0x22 */
	CANUser_SetSeatState,				/* index = 0x23 */
	CANUser_SetAcReset, 			/* index = 0x24 */

	//{add s401
	CANUser_Null,				/*index = 0x25*/	
	CANUser_LightOffDelaySettingDeal,   /*index = 0x26*/
	CANUser_TurnBlinkTimeSettingDeal,  /*index = 0x27*/
	CANUser_KeyDoorUnlockSettingDeal,  /*index = 0x28*/
	CANUser_DriveDoorLockSettingDeal,  /*index = 0x29*/
	CANUser_ParkDoorUnlockSettingDeal,  /*index = 0x2A*/
	CANUser_SetAvmInCmd,	/*index = 0x2B*/
	//}add s401
	/*****************************
	主动安全START
	*****************************/
	CANUser_AccCtlDeal,					/*index = 0x2C*/
	CANUser_FcwDataDeal,					/*index = 0x2D*/
	CANUser_AutoBrakeDataDeal,			/*index = 0x2E*/
	CANUser_BsdDataDeal,					/*index = 0x2F*/
	CANUser_Null,						/*index = 0x30*/
	CANUser_CtaDataDeal,				/*index = 0x31*/
	CANUser_RcwDataDeal,				/*index = 0x32*/
	CANUser_LdwSensitivityDataDeal,				/*index = 0x33*/
	CANUser_SlaSwitchDataDeal,				/*index = 0x34*/
	CANUser_HmaDataDeal,				/*index = 0x35*/
	CANUser_DrlDataDeal,				/*index = 0x36*/
	/*****************************
	主动安全END
	*****************************/
	
};

//next table define the DataArray for used CAN data struct(reference for "CAN_Msg.h")
CANMsgType CANUser_UsedMsgData[] = 
{
	{OMS_CAN_TX_CAR, 	OP_CAN_TX_CAR_MAINTAIN},
	{OMS_CAN_TX_CAR,	OP_CAN_TX_CAR_SPEED},
	{OMS_CAN_TX_CAR,	OP_CAN_TX_CAR_SYS},// dont send this message.(S301 no use)
	{OMS_CAN_TX_CAR, 	OP_CAN_TX_ECU_STATE},
	{OMS_CAN_TX_CAR,	OP_CAN_TX_CAR_ODO},
	//{OMS_CAN_TX_CAR, 	OP_CAN_TX_CAR_ECO},
	{OMS_CAN_TX_CAR, 	OP_CAN_TX_CAR_VIN},
	{OMS_CAN_TX_AC,	OP_CAN_TX_AC_OUTTEMP},
	{OMS_CAN_TX_KCP,	OP_CAN_TX_KCP_VER},
	{OMS_CAN_TX_CAR,	OP_CAN_TX_RADAR_STATE},	
};


#pragma section data "no_init" begin
//this section,when CPU reset,the data can not be initialized if the power on
//DvdCANMsgInfoStruct  DvdCANMsgInfo;

static uint8_t InnerCanBuff[8];
static uint8_t Body600Buff[8];//触发发送
static uint8_t Body601Buff[8];//触发发送
static uint8_t Body2F8Buff[8];//100ms
static uint8_t Body2F9Buff[8];//100ms
static uint8_t Body2FABuff[8];//100ms
uint8_t Body513Buff[8];//100ms
static uint8_t Body500Buff[8];//1000ms
static uint8_t Body501Buff[8];//1000ms
static uint8_t Body580Buff[8];//1000ms


#pragma section data "no_init" end

/****************************************************************************
 * @function	CANUser_GetFuncTblSize
 * @brief  	get the function table size number.
 * @param  	null
 * @retval 	uint8_t 
 * @attention:  don't modify this function.
****************************************************************************/
uint8_t CANUser_GetFuncTblSize(void)
{
	uint8_t num = sizeof(pCANUserFuncTbl)/sizeof(void *);
	return num;
}

uint8_t CANUser_GetUsedMsgNum(void)
{
	return sizeof(CANUser_UsedMsgData)/sizeof(CANMsgType);
}

/****************************************************************************
 * @function	CANUser_InitParam
 * @brief  	can module parameter initialize
 * @param  	point to the config structure.
 * @retval 	null 
 * @attention:  modify this function according application.
****************************************************************************/
void CANUser_InitParam(CAN_USED_CFG *pCfg)
{
	uint8_t i = 0;
	CAN_INIT_STRUCT CANinitParam;
#ifdef UDS_ENABLE_MACRO
	UDS_CAN_CFG		UdsConfig;
#endif

/* CAN 0 initparam */
#ifdef CAN_BODY_ENABLE
	CANinitParam.can_Id = CAN_ID_BODY;
	CANinitParam.can_BpsType = CAN_BPS_500K;
	CANinitParam.can_SendBuffNum = 5;/* 2 for oneshot(one is netmanger msg,one is tx test msg), 2 for peridoic */

	CANinitParam.can_RecvFilter[i++] = CAN_RXID_GW_32A;
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_GW_320; //AT车速信号
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_BCM_347;
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_ESP_368;
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_ESP_218;//MT的车速信号
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_PAC_3D0;
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_RRS_2E0;
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_DVR_612;
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_DVR_613;
	
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_FACTORY_TEST_001;
		
#ifdef UDS_ENABLE_MACRO
	CANinitParam.can_RecvFilter[i++] = CAN_UDS_RXID_PHY;
	CANinitParam.can_RecvFilter[i++] = CAN_UDS_RXID_FUNC;
#endif
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_TEST;

	if(i>CAN_RCV_FILTER_MAX)
	{
		i = CAN_RCV_FILTER_MAX;
	}
	CANinitParam.can_RecvFilterNum = i;
	
#ifdef NM_ENABLE_MACRO
	CANinitParam.MASKValidNum = 1;
	CANinitParam.can_RecvFilterCmp[0] = 0x400;		//osek nm message
	CANinitParam.can_RecvMASK[0] = 0x0ff;
#else
	CANinitParam.MASKValidNum = 0;
#endif
	CANinitParam.validFlag = 1;
	CANbus_AppLayerSetInitParam(&CANinitParam);
#else
	CANinitParam.can_Id = CAN_ID_BODY;
	CANinitParam.MASKValidNum = 0;
	CANinitParam.can_SendBuffNum = 0;
	CANinitParam.can_RecvFilterNum = 0;
	CANinitParam.validFlag = 0;
	CANbus_AppLayerSetInitParam(&CANinitParam);
#endif

/* CAN 1 initparam */
#ifdef CAN_INNER_ENABLE
	i = 0;
	CANinitParam.can_Id = CAN_ID_INNER;
	CANinitParam.can_BpsType = CAN_BPS_125K;
	CANinitParam.can_SendBuffNum = 3;	/* 1 for oneshot, 1 for peridoic */
	//CANinitParam.can_RecvFilter[i++] = CAN_RXID_INNER_KEY;
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_INNER_TEST;
	if(i>CAN_RCV_FILTER_MAX)
	{
		i = CAN_RCV_FILTER_MAX;
	}
	CANinitParam.can_RecvFilterNum = i;
	CANinitParam.MASKValidNum = 1;		
	CANinitParam.can_RecvFilterCmp[0] = 0x500;
	CANinitParam.can_RecvMASK[0] = 0x0ff;
	CANinitParam.validFlag = 1;
	CANbus_AppLayerSetInitParam(&CANinitParam);
	CANbus_InnerInit();
#else
	CANinitParam.can_Id = CAN_ID_INNER;
	CANinitParam.MASKValidNum = 0;
	CANinitParam.can_SendBuffNum = 0;
	CANinitParam.can_RecvFilterNum = 0;
	CANinitParam.validFlag = 0;
	CANbus_AppLayerSetInitParam(&CANinitParam);
#endif

/* UDS config */
#ifdef UDS_ENABLE_MACRO
	UdsConfig.UseId = CAN_ID0;
	UdsConfig.TxMsgId = CAN_TXID_DIAG;
	UdsConfig.RxPhyId = CAN_UDS_RXID_PHY;
	UdsConfig.RxFuncId = CAN_UDS_RXID_FUNC;
	Uds_CANConfigEnter(&UdsConfig);
#endif
#if 1
	pCfg->UsedCANNum = 0;
	pCfg->UsedCANId[pCfg->UsedCANNum] = CAN_ID_BODY;
	pCfg->UsedCANNum ++;
	pCfg->UsedCANId[pCfg->UsedCANNum] = CAN_ID_INNER;
	pCfg->UsedCANNum ++;
#endif
#if 0
/* init config */ 
#ifdef NM_ENABLE_MACRO
#ifdef CAN_INNER_ENABLE
	pCfg->UsedCANNum = 1;
	pCfg->UsedCANId[0] = CAN_ID_INNER;
#endif

#else

#ifdef CAN_BODY_ENABLE
	pCfg->UsedCANId[pCfg->UsedCANNum] = CAN_ID_BODY;
	pCfg->UsedCANNum ++;
#endif

#ifdef CAN_INNER_ENABLE
	pCfg->UsedCANId[pCfg->UsedCANNum] = CAN_ID_INNER;
	pCfg->UsedCANNum ++;
#endif
#endif
#endif

AvmDispTime=0;

}

/****************************************************************************
 * @function	CANUser_InitWorkOn
 * @brief  	when system rework from sleep,Init user application
 * @param  	null
 * @retval 	null
 * @attention:  if not used, please dummy it.
****************************************************************************/
void CANUser_InitWorkOn(void)
{
	uint8_t i = 0, msg[5];
	
#ifdef CAN_BODY_ENABLE
	pCAN_GetTBOXData()->Car_TBOX_Request = 0;
	CANUserVar.CANMsgSendflag = 0;
	CANUserVar.AVMexitFlag = 0;
	CANUserVar.TUIDReq = 0;
	CANUserVar.TUIDRegCnt = 0;
   
//	Body2F8Buff[5] = 0x00;		/*navi code clear */
#endif
#ifdef CAN_INNER_ENABLE
	//CANbus_InnerInit();
#endif
	TaskCAN_debug(_T("CANUser_InitWorkOn\n"));
	for(i = 0;i< CAN_RXID_END_FILTER; i++)
	{
		CANbus_NetLayerClearFilterBuff(i);
	}
	CANUser_Msg500And501Init();
	//CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
	CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, TIMER_100MS);
	//CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
	//CANUser_SetBodyCanMsgPeriodic(Body2FABuff, CAN_TX_ID2FA, TIMER_100MS);
	CANUser_SetBodyCanMsgPeriodic(Body500Buff, CAN_TX_ID500, TIMER_1000MS);
	CANUser_SetBodyCanMsgPeriodic(Body501Buff, CAN_TX_ID501, TIMER_1000MS);
	//CANUser_SetBodyCanMsgPeriodic(Body580Buff, CAN_TX_ID580, TIMER_1000MS);
	//外置功放进静音
	//CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_ON);
}

void CANUser_InnerReset(void)
{
	CAN_INIT_STRUCT CANinitParam;
/* CAN 1 initparam */
#ifdef CAN_INNER_ENABLE
	int i = 0;
	CANinitParam.can_Id = CAN_ID_INNER;
	CANinitParam.can_BpsType = CAN_BPS_125K;
	CANinitParam.can_SendBuffNum = 3;	/* 1 for oneshot, 1 for peridoic */
	//CANinitParam.can_RecvFilter[i++] = CAN_RXID_INNER_KEY;
	CANinitParam.can_RecvFilter[i++] = CAN_RXID_INNER_TEST;
	if(i>CAN_RCV_FILTER_MAX)
	{
		i = CAN_RCV_FILTER_MAX;
	}
	CANinitParam.can_RecvFilterNum = i;
	CANinitParam.MASKValidNum = 1;		
	CANinitParam.can_RecvFilterCmp[0] = 0x500;
	CANinitParam.can_RecvMASK[0] = 0x0ff;
	CANinitParam.validFlag = 1;
	CANbus_AppLayerSetInitParam(&CANinitParam);
	CANbus_InnerInit();
#else
	CANinitParam.can_Id = CAN_ID_INNER;
	CANinitParam.MASKValidNum = 0;
	CANinitParam.can_SendBuffNum = 0;
	CANinitParam.can_RecvFilterNum = 0;
	CANinitParam.validFlag = 0;
	CANbus_AppLayerSetInitParam(&CANinitParam);
#endif

//    CANbus_EnableCANTransceiver(CAN_ID_INNER, CAN_TRANSCEIVER_MODE_SLEEP);
    CANbus_StartupHandler(CAN_TYPE_INNER);		

}

/****************************************************************************
 * @function	CANUser_TaskTickHook
 * @brief  	hook function for task time tick deal
 * @param  	tickBase: the timer base(unit: ms)
 * @retval 	null
 * @attention:  if not used, please dummy it.
****************************************************************************/
void CANUser_TaskTickHook(uint8_t tickBase)
{
	uint8_t msg[5];
	//next code: when data sync ok, send ECO data periodic
	CarDvrDataStruct *pData   =pCAN_GetDvrData();
	FrontACDataStruct *FrontData=pCAN_GetFrontACData();
	CarAVMDataStruct *AData = pCAN_GetAVMData();
	TPMSDataStruct	*pTpmsData = pCAN_GetTPMSData();
	RadarStatusDataStruct *pRadarData =pCAN_GetRadarStatusData();//雷达数据...
	
	if(sCANModule.DataSyncStatus == CAN_MSG_SYNC_END)
	{
		if(CANUserVar.ECOTimer == 0)
		{
			CANUserVar.ECOTimer = TIMER_100MS;
		}
		else
		{
			CANUserVar.ECOTimer--;
		}
	}
	
	// next code: inspect the ECU state.
	if((BodyECUStatus.AllECU_State) &&(BodyECUStatus.Timer_AllEcu))
	{
		BodyECUStatus.Timer_AllEcu--;
		if(BodyECUStatus.Timer_AllEcu == 0)
		{
			BodyECUStatus.AllECU_State = 0;
		}
	}
	
	if((BodyECUStatus.BCM_State) &&(BodyECUStatus.Timer_BCM))
	{
		BodyECUStatus.Timer_BCM--;
		if(BodyECUStatus.Timer_BCM == 0)
		{
			BodyECUStatus.BCM_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_BCM, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	
	if((BodyECUStatus.BCM347_State) &&(BodyECUStatus.Timer_BCM347))
	{
		BodyECUStatus.Timer_BCM347--;
		if(BodyECUStatus.Timer_BCM347 == 0)
		{
			BodyECUStatus.BCM347_State = 0;
			pTpmsData->TpmsOnlineState = 0;
			CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_TPMS_DATA, 1);
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_BCM_347, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	
	if((BodyECUStatus.GW_State) &&(BodyECUStatus.Timer_GW))
	{
		BodyECUStatus.Timer_GW--;
		if(BodyECUStatus.Timer_GW == 0)
		{
			BodyECUStatus.GW_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_GW, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	if((BodyECUStatus.GW320_State) &&(BodyECUStatus.Timer_GW320))
	{
		BodyECUStatus.Timer_GW320--;
		if(BodyECUStatus.Timer_GW320 == 0)
		{
			BodyECUStatus.GW320_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_GW_320, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	if((BodyECUStatus.GW32A_State) &&(BodyECUStatus.Timer_GW32A))
	{
		BodyECUStatus.Timer_GW32A--;
		if(BodyECUStatus.Timer_GW32A == 0)
		{
			BodyECUStatus.GW32A_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_GW_32A, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	
	if((BodyECUStatus.AC_State) &&(BodyECUStatus.Timer_AC))
	{
		BodyECUStatus.Timer_AC--;
		if(BodyECUStatus.Timer_AC == 0)
		{
			BodyECUStatus.AC_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_AC, DTC_AVILABILITY_MASK);
			Uds_UpdateDTCStatus(DTC_ID_BUS_AC_330, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	if((BodyECUStatus.ESP_State) &&(BodyECUStatus.Timer_ESP))
	{
		BodyECUStatus.Timer_ESP--;
		if(BodyECUStatus.Timer_ESP == 0)
		{
			BodyECUStatus.ESP_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_ESP, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	if((BodyECUStatus.ESP218_State) &&(BodyECUStatus.Timer_ESP218))
	{
		BodyECUStatus.Timer_ESP218--;
		if(BodyECUStatus.Timer_ESP218 == 0)
		{
			BodyECUStatus.ESP218_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_ESP_218, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	if((BodyECUStatus.ESP368_State) &&(BodyECUStatus.Timer_ESP368))
	{
		BodyECUStatus.Timer_ESP368--;
		if(BodyECUStatus.Timer_ESP368 == 0)
		{
			BodyECUStatus.ESP368_State = 0;
			#ifdef UDS_ENABLE_MACRO
				Uds_UpdateDTCStatus(DTC_ID_BUS_ESP_368, DTC_AVILABILITY_MASK);
			#endif
		}
	}
	if((BodyECUStatus.EMS_State) &&(BodyECUStatus.Timer_EMS))
	{
		BodyECUStatus.Timer_EMS--;
		if(BodyECUStatus.Timer_EMS == 0)
		{
			BodyECUStatus.EMS_State = 0;
			#ifdef UDS_ENABLE_MACRO
				Uds_UpdateDTCStatus(DTC_ID_BUS_EMS, DTC_AVILABILITY_MASK);
				Uds_UpdateDTCStatus(DTC_ID_BUS_EMS_255, DTC_AVILABILITY_MASK);
			#endif
		}
	}
	
	if((BodyECUStatus.IP_State) &&(BodyECUStatus.Timer_IP))
	{
		BodyECUStatus.Timer_IP--;
		if(BodyECUStatus.Timer_IP == 0)
		{
			BodyECUStatus.IP_State = 0;
			#ifdef UDS_ENABLE_MACRO
				Uds_UpdateDTCStatus(DTC_ID_BUS_IP, DTC_AVILABILITY_MASK);
			#endif
		}
	}

	if((BodyECUStatus.DVR_State) &&(BodyECUStatus.Timer_DVR))
	{
		BodyECUStatus.Timer_DVR--;
		if(BodyECUStatus.Timer_DVR == 0)
		{
			BodyECUStatus.DVR_State = 0;
			pData->DVR_ConnectedState = 0;
			TaskCAN_debug(_T("---Clear:pData->DVR_ConnectedState = %d\n",pData->DVR_ConnectedState));
			CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_SETREQ, 1);
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_DVR, DTC_AVILABILITY_MASK);
		#endif
		}
	}

	if((BodyECUStatus.DVR612_State) &&(BodyECUStatus.Timer_DVR612))
	{
		BodyECUStatus.Timer_DVR612--;
		if(BodyECUStatus.Timer_DVR612 == 0)
		{
			BodyECUStatus.DVR612_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_DVR_612, DTC_AVILABILITY_MASK);
		#endif
		}
	}

	if((BodyECUStatus.DVR613_State) &&(BodyECUStatus.Timer_DVR613))
	{
		BodyECUStatus.Timer_DVR613--;
		if(BodyECUStatus.Timer_DVR613== 0)
		{
			BodyECUStatus.DVR613_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_DVR_613, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	
	if((BodyECUStatus.RRS_State) &&(BodyECUStatus.Timer_RRS))
	{
		BodyECUStatus.Timer_RRS--;
		if(BodyECUStatus.Timer_RRS == 0)
		{
			BodyECUStatus.RRS_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_RRS, DTC_AVILABILITY_MASK);
		#endif
		
		#ifdef R103_H15T_OVERSEAS //海外版的雷达自适应
			pRadarData->RadarSysStatus = 0x0;
			CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_RADAR_STATE, 1);	
		#endif
		}
	}
	if((BodyECUStatus.LCM_State) &&(BodyECUStatus.Timer_LCM))
	{
		BodyECUStatus.Timer_LCM--;
		if(BodyECUStatus.Timer_LCM == 0)
		{
			BodyECUStatus.LCM_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_LCM, DTC_AVILABILITY_MASK);
		#endif
		}
	}

	if((BodyECUStatus.Tbox_State) &&(BodyECUStatus.Timer_TBOX))
	{
		BodyECUStatus.Timer_TBOX--;
		if(BodyECUStatus.Timer_TBOX == 0)
		{
			BodyECUStatus.Tbox_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_TBOX, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	
	if((BodyECUStatus.PEPS_State) &&(BodyECUStatus.Timer_PEPS))
	{
		BodyECUStatus.Timer_PEPS--;
		if(BodyECUStatus.Timer_PEPS == 0)
		{
			BodyECUStatus.PEPS_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_PEPS, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	
	if((BodyECUStatus.IP_State) &&(BodyECUStatus.Timer_IP))
	{
		BodyECUStatus.Timer_IP--;
		if(BodyECUStatus.Timer_IP == 0)
		{
			BodyECUStatus.IP_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_IP, DTC_AVILABILITY_MASK);
		#endif
		}
	}
	
	if((BodyECUStatus.PAC_State) &&(BodyECUStatus.Timer_PAC))
	{
		BodyECUStatus.Timer_PAC--;
		if(BodyECUStatus.Timer_PAC == 0)
		{
			BodyECUStatus.PAC_State = 0;
		#ifdef UDS_ENABLE_MACRO
			Uds_UpdateDTCStatus(DTC_ID_BUS_PAC, DTC_AVILABILITY_MASK);
		#endif
		}
	}

#ifdef CAN_INNER_ENABLE
	CANbus_InnerTimerHandler();
#endif

	if(AvmCnt)
	{
		AvmCnt--;
		if(AvmCnt<=10)
		{
			//全景退出
			/*msg[0] = OP_CAN_RX_VEHICLE_AVM;
			
			msg[1] = 0;
			msg[2] = 0;
			
			msg[3] = 0;
			msg[4] = 0;
			
			CANTask_VehicleMsgHandler(msg);
			*/
			 memset(Body2F8Buff,0,8);
		}
		CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, CAN_TX_INNER_CYCLE);	
	}
	if(CANTask_GetSysACCState())
	{
		InnerCanCnt++;
		if(InnerCanCnt>3500)
		{
			CANUser_InnerReset();
			InnerCanCnt=0;
		}
		if(++AC_ID330Cnt > 2500 )
		{
			AC_ID330Cnt = 0;
			CurrExtTempValid = 0;
			FrontData->OutsideTemperature=0xFF;
	             if(l_tMediaCB.uDevFlag.field.bDevConnect)
				CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);

		}
	}

}


/****************************************************************************
 * @function	CANUser_NetLayerRcvMsgHook
 * @brief  	before filter, when CAN BUS netlayer received message, a hook to extra deal.
 * @param  	pRxMessage:    the received message point
  * @retval 	null
 * @attention:  if not need ,please clear it .
****************************************************************************/
void CANUser_NetLayerRcvMsgHook(CanMsgStruct *pRxMessage)
{
	CarDvrDataStruct *pData   =pCAN_GetDvrData();
	TPMSDataStruct	*pTpmsData = pCAN_GetTPMSData();
	EOLCfgStruct *pEOLCfg =pCAN_GetEOLStr();//半自适应下线配置,不改变EEPROM的数据,只将数据传送给OS
	RadarStatusDataStruct *pRadarData =pCAN_GetRadarStatusData();//雷达数据...
	
#ifdef CAN_INNER_ENABLE
	if(pRxMessage->CAN_Id == CAN_ID_INNER)
	{
		switch(pRxMessage->CANMsgId)
		{
			//reset timer, used for timeout handler
			case CAN_RXID_INNER_DTV_0:
				InnerTimerStr.DTV = TIMER_1000MS;		
				break;
			case CAN_RXID_INNER_LRHD_0:
				InnerTimerStr.LRHD = TIMER_1000MS;
				break;
			case CAN_RXID_INNER_RRHD_0:
				InnerTimerStr.RRHD = TIMER_1000MS;
				break;
			case CAN_RXID_INNER_FCP:
				InnerCanCnt=0;
				InnerTimerStr.FCP= TIMER_1500MS;
				break;
			default:
				break;
		}
	}
#endif
#ifdef CAN_BODY_ENABLE
	if(pRxMessage->CAN_Id == CAN_ID_BODY)
	{
		BodyECUStatus.Timer_AllEcu= ECU_ALL_CYCLE_TIME;
		BodyECUStatus.AllECU_State = 1;
		switch(pRxMessage->CANMsgId)
		{
			case CAN_RXID_GW_32A:
			case CAN_RXID_GW_320:
			case CAN_RXID_GW_2FF:
				BodyECUStatus.Timer_GW = ECU_GW_CYCLE_TIME;
				if(!BodyECUStatus.GW_State)
				{
					BodyECUStatus.GW_State = 1;
					#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_GW, 0x00);
					#endif
				}
				if(CAN_RXID_GW_32A == pRxMessage->CANMsgId)
				{
					BodyECUStatus.Timer_GW32A= ECU_GW_CYCLE_TIME;
					if(!BodyECUStatus.GW32A_State)
					{
						BodyECUStatus.GW32A_State = 1;
						#ifdef UDS_ENABLE_MACRO
								Uds_UpdateDTCStatus(DTC_ID_BUS_GW_32A, 0x00);
						#endif
					}
				}
				else if(CAN_RXID_GW_320 == pRxMessage->CANMsgId)
				{
					BodyECUStatus.Timer_GW320= ECU_GW_CYCLE_TIME;
					if(!BodyECUStatus.GW320_State)
					{
						BodyECUStatus.GW320_State = 1;
						#ifdef UDS_ENABLE_MACRO
								Uds_UpdateDTCStatus(DTC_ID_BUS_GW_320, 0x00);
						#endif
					}
				}
				break;
			case CAN_RXID_BCM_288:
			case CAN_RXID_BCM_347:
			case CAN_RXID_BCM_349:
			case CAN_RXID_BCM_5FF:
				BodyECUStatus.Timer_BCM= ECU_BCM_CYCLE_TIME;
				if(!BodyECUStatus.BCM_State)
				{
					BodyECUStatus.BCM_State = 1;
					#ifdef UDS_ENABLE_MACRO
						Uds_UpdateDTCStatus(DTC_ID_BUS_BCM, 0x00);
					#endif
				}
				
				if(CAN_RXID_BCM_347 == pRxMessage->CANMsgId)
				{
					BodyECUStatus.Timer_BCM347= ECU_BCM_CYCLE_TIME;
					if(!pEOLCfg->EOLState.bits.TPMSSupport)//snake20170208 tpms自适应
					{
						pEOLCfg->EOLState.bits.TPMSSupport = 1;
						CANTask_SendApiData(OMS_CAN_TX_SYS, OP_CAN_TX_EOL, 1);
						TaskCAN_debug(_T("------EOL NotSupport TPMS ,but Rcv TPMS CanMsg....send EOL to APU----\n"));
					}
					if(!BodyECUStatus.BCM347_State)
					{
						BodyECUStatus.BCM347_State = 1;
						pTpmsData->TpmsOnlineState = 1;
						CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_TPMS_DATA, 1);
						#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_BCM_347, 0x00);
						#endif
					}
				}
				break;
			case CAN_RXID_AVM_3E0:
				BodyECUStatus.Timer_AVM= ECU_AVM_CYCLE_TIME;
				if(!BodyECUStatus.AVM_State)
				{
					BodyECUStatus.AVM_State = 1;
					#ifdef UDS_ENABLE_MACRO
					Uds_UpdateDTCStatus(DTC_ID_BUS_AVM, 0x00);
					#endif
				}
				break;
			case CAN_RXID_TBOX:
				BodyECUStatus.Timer_TBOX= ECU_TBOX_CYCLE_TIME;
				if(!BodyECUStatus.Tbox_State)
				{
					BodyECUStatus.Tbox_State = 1;
					#ifdef UDS_ENABLE_MACRO
						Uds_UpdateDTCStatus(DTC_ID_BUS_TBOX, 0x00);
					#endif
				}
				break;
			case CAN_RXID_PEPS_266:
				BodyECUStatus.Timer_PEPS= ECU_PEPS_CYCLE_TIME;
				if(!BodyECUStatus.PEPS_State)
				{
					BodyECUStatus.PEPS_State = 1;
					#ifdef UDS_ENABLE_MACRO
						Uds_UpdateDTCStatus(DTC_ID_BUS_PEPS, 0x00);
					#endif
				}
				break;
			case CAN_RXID_IP:
			case CAN_RXID_IP_380:
			case CAN_RXID_IP_280:
			case CAN_RXID_IP_260:
				BodyECUStatus.Timer_IP= ECU_IP_CYCLE_TIME;
				if(!BodyECUStatus.IP_State)
				{
					BodyECUStatus.IP_State = 1;
					#ifdef UDS_ENABLE_MACRO
						Uds_UpdateDTCStatus(DTC_ID_BUS_IP, 0x00);
					#endif
				}
				break;
			case CAN_RXID_AC:// CAN_RXID_DSM_330 
			//case CAN_RXID_DSM_330:
			case CAN_RXID_DSM_340:
			case CAN_RXID_DSM_352:
				BodyECUStatus.Timer_AC= ECU_AC_CYCLE_TIME;
				if(!BodyECUStatus.AC_State)
				{
					BodyECUStatus.AC_State = 1;
					#ifdef UDS_ENABLE_MACRO  
					Uds_UpdateDTCStatus(DTC_ID_BUS_AC, 0x00);
					Uds_UpdateDTCStatus(DTC_ID_BUS_AC_330, 0x00);
					#endif
				}
				break;
			case CAN_RXID_DVR_612:
			case CAN_RXID_DVR_613:
				if(!pEOLCfg->EOLState.bits.DVRSupport)//snake20170208 DVR半自适应
				{
					pEOLCfg->EOLState.bits.DVRSupport = 1;
					CANTask_SendApiData(OMS_CAN_TX_SYS, OP_CAN_TX_EOL, 1);
					TaskCAN_debug(_T("------EOL NotSupport DVR ,but Rcv DVR CanMsg....send EOL to APU----\n"));
				}
				BodyECUStatus.Timer_DVR= ECU_DVR_CYCLE_TIME;
				if(!BodyECUStatus.DVR_State)
				{
					BodyECUStatus.DVR_State = 1;
					pData->DVR_ConnectedState = 1;
					TaskCAN_debug(_T("---Set:pData->DVR_ConnectedState = %d\n",pData->DVR_ConnectedState));
					CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_SETREQ, 1);
					#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_DVR, 0x00);
					#endif
				}

				if(CAN_RXID_DVR_612 == pRxMessage->CANMsgId)
				{
					BodyECUStatus.Timer_DVR612= ECU_DVR_CYCLE_TIME;
					if(!BodyECUStatus.DVR612_State)
					{
						BodyECUStatus.DVR612_State = 1;
						#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_DVR_612, 0x00);
						#endif
					}
				}
				if(CAN_RXID_DVR_613 == pRxMessage->CANMsgId)
				{
					BodyECUStatus.Timer_DVR613= ECU_DVR_CYCLE_TIME;
					if(!BodyECUStatus.DVR613_State)
					{
						BodyECUStatus.DVR613_State = 1;
						#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_DVR_613, 0x00);
						#endif
					}
				}
				break;
			case CAN_RXID_RRS_2E0:
				#ifdef R103_H15T_OVERSEAS //海外版的雷达自适应
					pRadarData->RadarSysStatus = 0x2;
					CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_RADAR_STATE, 1);	
				#endif
				BodyECUStatus.Timer_RRS= ECU_RRS_CYCLE_TIME;
				if(!BodyECUStatus.RRS_State)
				{
					BodyECUStatus.RRS_State = 1;
					#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_RRS, 0x00);
					#endif
				}
				break;
			case CAN_RXID_ESP_218:
			case CAN_RXID_ESP_368:
				BodyECUStatus.Timer_ESP= ECU_ESP_CYCLE_TIME;
				if(!BodyECUStatus.ESP_State)
				{
					BodyECUStatus.ESP_State = 1;
					#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_ESP, 0x00);
					#endif
				}
				if(CAN_RXID_ESP_218 == pRxMessage->CANMsgId)
				{
					BodyECUStatus.Timer_ESP218= ECU_ESP_CYCLE_TIME;
					if(!BodyECUStatus.ESP218_State)
					{
						BodyECUStatus.ESP218_State = 1;
						#ifdef UDS_ENABLE_MACRO
								Uds_UpdateDTCStatus(DTC_ID_BUS_ESP_218, 0x00);
						#endif
					}
				}
				else if(CAN_RXID_ESP_368== pRxMessage->CANMsgId)
				{
					BodyECUStatus.Timer_ESP368= ECU_ESP_CYCLE_TIME;
					if(!BodyECUStatus.ESP368_State)
					{
						BodyECUStatus.ESP368_State = 1;
						#ifdef UDS_ENABLE_MACRO
								Uds_UpdateDTCStatus(DTC_ID_BUS_ESP_368, 0x00);
						#endif
					}
				}
				break;
			case CAN_RXID_EMS_255:
				BodyECUStatus.Timer_EMS= ECU_EMS_CYCLE_TIME;
				if(!BodyECUStatus.EMS_State)
				{
					BodyECUStatus.EMS_State = 1;
					#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_EMS, 0x00);
							Uds_UpdateDTCStatus(DTC_ID_BUS_EMS_255, 0x00);
					#endif
				}
				break;
				
			case CAN_RXID_LCM_5F0:
				BodyECUStatus.Timer_LCM= ECU_LCM_CYCLE_TIME;
				if(!BodyECUStatus.LCM_State)
				{
					BodyECUStatus.LCM_State = 1;
					#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_LCM, 0x00);
					#endif
				}
				break;
			case CAN_RXID_PAC_3D0:
				BodyECUStatus.Timer_PAC = ECU_PAC_CYCLE_TIME;
				if(!BodyECUStatus.PAC_State)
				{
					BodyECUStatus.PAC_State = 1;
					#ifdef UDS_ENABLE_MACRO
							Uds_UpdateDTCStatus(DTC_ID_BUS_PAC, 0x00);
					#endif
				}
				break;
			default:
				break;
		}
	}
#endif
}

/****************************************************************************
 * @function	CANUser_RcvFilterPreDeal
 * @brief  	config the receive filter used by the CANbus_NetLayer.c
 *			give the filter buffer to the reveived message.
 *			if you want to filter the same message, you should config it.
 * @param  	pRxMessage:    the received message point
 *			pFilterBuffer:    the filter message buffer, an array , the size if defined by macro of
 *						CAN_RCV_FILTER_NUM
 * @retval 	the point the the filter buffer
 * @attention:  if need filter, please give the buffer, otherwise, not deal.
****************************************************************************/
CanMsgStruct * CANUser_RcvFilterPreDeal(CanMsgStruct *pRxMessage, 
                                           					CanMsgStruct *pFilterBuffer)
{
	CanMsgStruct *pBak = (CanMsgStruct *)0;
	CANUser_NetLayerRcvMsgHook(pRxMessage);//先做在线判断,在做报文过滤...
	if(pRxMessage->CAN_Id == CAN_ID_INNER)
	{
	/*--------give the inner CAN message buffer-----(start)----------------*/
		
		switch(pRxMessage->CANMsgId)
			{
			case CAN_RXID_INNER_KEY:
				pBak = &pFilterBuffer[CAN_RXID_KEY_FILTER];
				break;
			case CAN_RXID_INNER_LRHD_0:
				pBak = &pFilterBuffer[CAN_RXID_LRHD_FILTER];
				break;
			case CAN_RXID_INNER_LRHD_1:
				break;
			case CAN_RXID_INNER_RRHD_0:
				pBak = &pFilterBuffer[CAN_RXID_RRHD_FILTER];
				break;
			case CAN_RXID_INNER_RRHD_1:
				break;
			case CAN_RXID_INNER_FCP:
				pBak = &pFilterBuffer[CAN_RXID_FCP_FILTER];
				break;
			case CAN_RXID_INNER_DTV_0:
				pBak = &pFilterBuffer[CAN_RXID_DTV_FILTER];
				break;
			case CAN_RXID_INNER_DTV_VER:
				pBak = &pFilterBuffer[CAN_RXID_DTV_VER_FILTER];
				break;
			default:
				break;	
			}
	/*--------give the inner CAN message buffer-----(end)-----------------*/
	}
	else
	{
	/*--------give the vehicle body CAN message buffer-----(start)----------*/
		switch(pRxMessage->CANMsgId)
		{
			case CAN_RXID_GW_32A:
				//pBak = &pFilterBuffer[CAN_RXID_GW_FILTER];
				break;
			case CAN_RXID_IP:
				pBak = &pFilterBuffer[CAN_RXID_IP_FILTER];
				break;
			case CAN_RXID_BCM_288:		/*not filter BCM Message */
				break;
			case CAN_RXID_PEPS_266:
				//pBak = &pFilterBuffer[CAN_RXID_PEPS_FILTER];
				break;
			case CAN_RXID_DSM_330:		/*not filter */
				AC_ID330Cnt = 0;
				//pBak = &pFilterBuffer[CAN_RXID_330_FILTER];
				break;
			case CAN_RXID_DSM_340:
				//pBak = &pFilterBuffer[CAN_RXID_340_FILTER];
				break;
			case CAN_RXID_DSM_352:
				pBak = &pFilterBuffer[CAN_RXID_352_FILTER];
				break;
			case CAN_RXID_BCM_349:
//				pBak = &pFilterBuffer[CAN_RXID_349_FILTER];
				break;
			case CAN_RXID_AVM_3E0:
				//pBak = &pFilterBuffer[CAN_RXID_AVM_FILTER];
				break;
			case CAN_RXID_DVR_612:
				pBak = &pFilterBuffer[CAN_RXID_DVR_612_FILTER];//snake20160901
				break;
			case CAN_RXID_DVR_613://snake20160901
				pBak = &pFilterBuffer[CAN_RXID_DVR_613_FILTER];
				break;
			case CAN_RXID_RRS_2E0:
				pBak = &pFilterBuffer[CAN_RXID_2E0_FILTER];
				break;
			case CAN_RXID_ESP_320:/*car speed signal not filter */
				break;
			case CAN_RXID_LCM_5F0:
				//pBak = &pFilterBuffer[CAN_RXID_5F0_FILTER];
				break;
			case CAN_RXID_IGN_2B0:
				//pBak = &pFilterBuffer[CAN_RXID_2B0_FILTER];
				break;
			case CAN_RXID_BCM_5FF:
				pBak = &pFilterBuffer[CAN_RXID_5FF_FILTER];
				break;

			case CAN_RXID_IP_380:
				//pBak = &pFilterBuffer[CAN_RXID_2B0_FILTER];
				break;

			case CAN_RXID_GW_2FF:
				pBak = &pFilterBuffer[CAN_RXID_2FF_FILTER];
				break;
				
			default:
				break;
		}
	/*--------give the vehicle body CAN message buffer-----(end)----------*/
	}
	return pBak;
}




/****************************************************************************
 * @function	CANUser_MsgFilter_Step2
 * @brief  	second step message filter. used for the filted same message
 *				------reveived message----------
 *							|
 *                                      		|CANUser_RcvFilterPreDeal()
 *                                                     |
 *                             ------filtered the same message, notify receive unsame  message---
 *							|
 *							|CANUser_MsgFilter_Step2()
 *							|
 *		----------get same message, which need deal.notify receive special message----
 *							|
 *							|
 *		-----------filter the unused message----------
 * @param  	1. pRxMessage: the message point
 * @retval 	0: not filter; 1: filtered
 * @attention:  because it is the second step filter. only for same message.
****************************************************************************/
uint8_t CANUser_MsgFilter_Step2(CanMsgStruct *pRxMessage)
{
	if((pRxMessage->CAN_Id == CAN_ID_INNER) &&(pRxMessage->CANMsgId == CAN_RXID_INNER_KEY))
	{
		if(pRxMessage->Data[3] &0xc0)
		{
			return 0;	/* find the message that not need filter */
		}
		
	}
	return 1;			/*filter this message */
}
/****************************************************************************
 * @function	CANbus_MsgSendReqCallBack
 * @brief  	when send a message. there is a callback function to extra deal.
 * @param  	chno:    the CAN bus channel.
 *			uint32_t:    current send CAN BUS message id.
 * @retval 	null
 * @attention:  if you dont need this callback, please ensure the function is null function.you should
 *			not delete this function.
****************************************************************************/
void CANbus_MsgSendReqCallBack(uint8_t chno, uint32_t TxMsgId)
{
	if(chno == CAN_ID_BODY)
	{
		if(CAN_TX_ID2F9 == TxMsgId)	
		{
			if( 1==ID2F9CanMsgSendFlag )
			{
				ID2F9CanMsgSendFlag = 2;
			}
			else if( 2==ID2F9CanMsgSendFlag )
			{
				ID2F9CanMsgSendFlag = 0;
				memset(Body2F9Buff,0,8);
				CANUser_SetBodyCanMsgPeriodic(Body2F9Buff,CAN_TX_ID2F9,TIMER_100MS);
			}
		}
		else if(CAN_TX_ID2F8 == TxMsgId)
		{
			//CANUser_SetBodyCanMsgPeriodic(Body2F8Buff,CAN_TX_ID2F8,TIMER_100MS);
			if(SendCanMsgManage.SendMsg2DVR_Cnt!=0)
			{	
				SendCanMsgManage.SendMsg2DVR_Cnt--; 	
				TaskCAN_debug(_T("--SendCanMsgManage.SendMsg2DVR_Cnt = %d\n",SendCanMsgManage.SendMsg2DVR_Cnt));
			}
			else
			{
				if(SendCanMsgManage.SendMsg2DVR)
				{
					TaskCAN_debug(_T("------Body2F8 buffer clear------\n"));
					SendCanMsgManage.SendMsg2DVR = 0;
					SendCanMsgManage.SendMsg2DVR_Cnt = 0;
					Body2F8Buff[0] = Body2F8Buff[0] & 0xc0;//保证倒车模式信号不被清除...
					memset(&Body2F8Buff[1],0,7);
					CANUser_SetBodyCanMsgPeriodic(Body2F8Buff,CAN_TX_ID2F8,TIMER_100MS);
				}
			}
		}
	}
#ifdef CAN_INNER_ENABLE
	else
	{
		CANbus_InnerReqSendCallBack(TxMsgId);
	}
#endif
}


/****************************************************************************
 * @function	CANUser_Msg500And501Init
 * @brief  	对canbus中GPS和时间信息进行初始化设置
 * @param  	null
 * @retval 	null
 * @attention:  
****************************************************************************/
void CANUser_Msg500And501Init(void)
{
	//snake20161021 时间信息默认为发送无效的时间标志
	Body501Buff[0] = 0x80;//data and time is invalid
	
	//snake20161017获取EEPROM中GPS信息
	Body500Buff[0] = (uint8_t)((GpsInfo.Longitude & 0xff000000) >> 24);
	Body500Buff[1] = (uint8_t)((GpsInfo.Longitude & 0x00ff0000) >> 16);
	Body500Buff[2] = (uint8_t)((GpsInfo.Longitude & 0x0000ff00) >> 8);
	Body500Buff[3] = (uint8_t)((GpsInfo.Longitude & 0x000000ff));
	Body500Buff[4] = (uint8_t)((GpsInfo.Latitude & 0xff000000) >> 24);
	Body500Buff[5] = (uint8_t)((GpsInfo.Latitude & 0x00ff0000) >> 16);
	Body500Buff[6] = (uint8_t)((GpsInfo.Latitude & 0x0000ff00) >> 8);
	Body500Buff[7] = (uint8_t)((GpsInfo.Latitude & 0x000000ff));
	Body500Buff[0] |= 0x80;//GPS定位无效.
	if(GpsInfo.LongitudeFlag)
		Body500Buff[0] |= 0x10;
	else
		Body500Buff[0] &= 0xef;

	if(GpsInfo.LatitudeFlag)
		Body500Buff[4] |= 0x08;
	else
		Body500Buff[4] &= 0xf7;
	#if 1
	TaskCAN_debug(_T("\n\n------------------------Body500Buff:%x %x %x %x %x %x %x %x\n\n",Body500Buff[0],Body500Buff[1],Body500Buff[2],
		Body500Buff[3],Body500Buff[4],Body500Buff[5],Body500Buff[6],Body500Buff[7]));
	#endif


}
/****************************************************************************
 * @function	CANUser_ParamColdInit
 * @brief  	CANUser parameter initlization
 * @param  	null
 * @retval 	null
 * @attention:  used for the cold init. if not use, clear the function content.
****************************************************************************/
void CANUser_ParamColdInit(void)
{
	memset(InnerCanBuff,0,8);
	memset(Body2F8Buff,0,8);
	memset(Body2F9Buff,0,8);
	memset(Body2FABuff,0,8);
//	memset(Body513Buff,0,8);
	memset(Body600Buff,0,8);
	memset(Body601Buff,0,8);
	memset(Body500Buff,0,8);
	memset(Body501Buff,0,8);
	memset(Body580Buff,0,8);
	CANUser_Msg500And501Init();
	
#if 0
	Body513Buff[4] |= 0x01;	//碰撞预警默认开bolte
	Body513Buff[5] |= (0x01<<2);	//自动制动默认开
	Body513Buff[5] |=(0x02<<3); //并线辅助默认开
	Body513Buff[6] |=(0x02<<4);//倒车横向预警默认开
	Body513Buff[6] |=(0x02<<2);//倒车横向预警默认开
#endif	
	
#if 0	
	Body513Buff[6] &= 0xFC;//bit01置0
	Body513Buff[4] |= 0x01;//bit0置1
	Body513Buff[5] |= 0x04;//bit2置1
#endif
	
	CANUserVar.CANMsgSendflag = 0;
	//CANUserVar.AVMexitFlag = 0;
	CANUserVar.ReverseSignalCnt = 0;
	CANUserVar.ReverseValidFlag = 0;

	CANUserVar.TUIDRegState 	= 0;
	CANUserVar.TUIDRegCnt	= 0;

	CANUserVar.AvmSlipInfoFlag = 0;

	BodyECUStatus.GW_State = 0;
	BodyECUStatus.GW320_State = 0;
	BodyECUStatus.GW32A_State = 0;
	BodyECUStatus.BCM_State = 0;
	BodyECUStatus.BCM347_State = 0;
	BodyECUStatus.AVM_State = 0;
	BodyECUStatus.Tbox_State = 0;
	BodyECUStatus.PEPS_State = 0;
	BodyECUStatus.AC_State = 0;
	BodyECUStatus.IP_State = 0;
	BodyECUStatus.AllECU_State = 0;
	BodyECUStatus.DVR612_State = 0;
	BodyECUStatus.DVR613_State = 0;
	BodyECUStatus.DVR_State = 0;
	BodyECUStatus.RRS_State = 0;
	BodyECUStatus.ESP_State = 0;
	BodyECUStatus.ESP218_State = 0;
	BodyECUStatus.ESP368_State = 0;
	BodyECUStatus.EMS_State = 0;
	BodyECUStatus.LCM_State = 0;
	BodyECUStatus.PAC_State = 0;


	AvmExistFlag = 0;
}
/****************************************************************************
 * @function	CANUser_ParamWarmInit
 * @brief  	CANUser parameter initlization
 * @param  	null
 * @retval 	null
 * @attention:  used for the warm init. if not use, clear the function content.
****************************************************************************/
void CANUser_ParamWarmInit(void)
{
	
}

void CANUser_TryToSendCANMsg(uint8_t CANch)
{
	CanMsgStruct TxMsg;
	TxMsg.CAN_Id = CANch;		
	TxMsg.CANMsgDlc = 8;
	if(CANch == CAN_ID_BODY)
	{
		TxMsg.CANMsgId  = CAN_TX_ID2F8;
	}
	else
	{
		TxMsg.CANMsgId  = CAN_TXID_INNER_HU_510;
	}

	TxMsg.Data[0] = Body2F8Buff[0];
	TxMsg.Data[1] = 0x00;
	TxMsg.Data[2] = 0x00;
	TxMsg.Data[3] = 0x00;
	TxMsg.Data[4] = 0x00;
	TxMsg.Data[5] = 0x00;
	TxMsg.Data[6] = 0x00;
	TxMsg.Data[7] = 0x00;
	CANbus_NetLayerOneShotSendMsg(&TxMsg);
}
/****************************************************************************
 * @function	CANUser_StartSendInitMsg
 * @brief  	when CAN bus MOdule init ok, call this function to start send the message.
 * @param  	CANch: CAN BUS channel.
 * @retval 	null
 * @attention:  
****************************************************************************/
void CANUser_StartSendInitMsg(uint8_t CANch)
{
	uint8_t msg[5];
	if(CANch == CAN_ID_BODY)
	{	
		#if (PROJECT_CODE == CHANGAN_S401)
			CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
			CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, TIMER_100MS);
			CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
			CANUser_SetBodyCanMsgPeriodic(Body2FABuff, CAN_TX_ID2FA, TIMER_100MS);
			CANUser_SetBodyCanMsgPeriodic(Body500Buff, CAN_TX_ID500, TIMER_1000MS);
			CANUser_SetBodyCanMsgPeriodic(Body501Buff, CAN_TX_ID501, TIMER_1000MS);
			CANUser_SetBodyCanMsgPeriodic(Body580Buff, CAN_TX_ID580, TIMER_1000MS);
			//外置功放进静音
			CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_ON);
		#elif(PROJECT_CODE == CHANGAN_R103_H15T)
			CANUser_Msg500And501Init();//对GPS和时间的buffer进行初始化
			CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, TIMER_100MS);
			CANUser_SetBodyCanMsgPeriodic(Body500Buff, CAN_TX_ID500, TIMER_1000MS);
			CANUser_SetBodyCanMsgPeriodic(Body501Buff, CAN_TX_ID501, TIMER_1000MS);
		#endif
	}
	#ifdef CAN_INNER_ENABLE
	else
	{
		CANbus_InnerStartSendMsg(0);
	}
	#endif
}

/****************************************************************************
 * @function	CANUser_SendMsg500
 * @brief  	when CAN bus MOdule init ok, call this function to start send the message.
 * @param  	CANch: null
 * @retval 	null
 * @attention:  
****************************************************************************/
void CANUser_SendMsg500(void)
{
	CANUser_SetBodyCanMsgPeriodic(Body500Buff, CAN_TX_ID500, TIMER_1000MS);
}

/****************************************************************************
 * @function	CANUser_SendMsg501
 * @brief  	when CAN bus MOdule init ok, call this function to start send the message.
 * @param  	CANch: null
 * @retval 	null
 * @attention:  
****************************************************************************/
void CANUser_SendMsg501(void)
{
	CANUser_SetBodyCanMsgPeriodic(Body501Buff, CAN_TX_ID501, TIMER_1000MS);
}

/****************************************************************************
 * @function	CANUser_SendMsg2f8
 * @brief  	when CAN bus MOdule init ok, call this function to start send the message.
 * @param  	CANch: null
 * @retval 	null
 * @attention:  
****************************************************************************/
void CANUser_SendMsg2F8(void)
{
	CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, TIMER_100MS);
}
/****************************************************************************
 * @function	CANUser_Dummy
 * @brief  	dummy function , no work, just used as a function address.
 * @param  	parameter :dont use
 * @retval 	null
 * @attention:  please dont delete this function.
****************************************************************************/
void CANUser_Dummy(uint8_t *pMsg, uint8_t len)
{
}
/****************************************************************************
 * @function	CANUser_TimeSendDeal
 * @brief  	Send RTC clock to CAN BUS
 * @param  	pMsg = NULL, len = 0
 * @retval 	null
 * @attention:  please dont delete this function.
****************************************************************************/
void CANUser_TimeSendDeal(uint8_t *pMsg, uint8_t len)
{
	tRTC_BLOCK  RtcTime;
	OS_GetRTC(&RtcTime);
	/*
	 *	将时间根据项目的具体需要可以发送到总线上去。
	 *    add your own code next place.....
	 */
}

void CANUser_Null(uint8_t *pMsg, uint8_t len)
{
	
}

void CANUser_LightOffDelaySettingDeal(uint8_t *pMsg, uint8_t len)/*伴我回家灯光延时*/
{
	uint8_t light;

	light = pMsg[1];

	if(light < 8)
	{
		Body601Buff[1] &= 0xF8;
		Body601Buff[1] |= light;
	}
	CANUser_SetBodyCanMsgOnce(Body601Buff, CAN_TX_ID601);
}

void CANUser_TurnBlinkTimeSettingDeal(uint8_t *pMsg, uint8_t len)/*转向灯光闪烁次数*/
{
	uint8_t time;

	time = pMsg[1];

	if(time < 8)
	{
		Body601Buff[1] &= 0xc7;
		Body601Buff[1] |= (time << 3);
	}
	CANUser_SetBodyCanMsgOnce(Body601Buff, CAN_TX_ID601);
}

void CANUser_KeyDoorUnlockSettingDeal(uint8_t *pMsg, uint8_t len)/*遥控钥匙解锁模式*/
{
	uint8_t status;

	status = pMsg[1];

	if(status < 4)
	{
		Body601Buff[0] &= 0x3F;
		Body601Buff[0] |= (status << 6);
	}
	CANUser_SetBodyCanMsgOnce(Body601Buff, CAN_TX_ID601);
}

void CANUser_DriveDoorLockSettingDeal(uint8_t *pMsg, uint8_t len)/*行车自动落锁*/
{
	uint8_t status;

	status = pMsg[1];

	if(status < 4)
	{
		Body601Buff[0] &= 0xF3;
		Body601Buff[0] |= (status << 2);
	}
	CANUser_SetBodyCanMsgOnce(Body601Buff, CAN_TX_ID601);
}

void CANUser_ParkDoorUnlockSettingDeal(uint8_t *pMsg, uint8_t len)/*驻车自动解锁*/
{
	uint8_t status;

	status = pMsg[1];

	if(status < 4)
	{
		Body601Buff[0] &= 0xCF;
		Body601Buff[0] |= (status << 4);
	}
	CANUser_SetBodyCanMsgOnce(Body601Buff, CAN_TX_ID601);
}

void CAN_Get_Body513Data(void)
{
	CarAccCtrlStruct* pAccData = pCAN_GetVehicleAccCrlData();
	CarFcwStruct* pFcwData = pCAN_GetFcwData();
	CarRcwStruct* pRcwData = pCAN_GetRcwData();
	CarLdwSensStruct* pLdwData = pCAN_GetLdwData();
	CarLightDataStruct* pLight = pCAN_GetCarLightData();
	
	Body513Buff[6] &= 0xFC;					// BYTE6 bit01 
	Body513Buff[6] |=pAccData->DesWarnMode;
	if(1 == pFcwData->FcwEnable)
	{
		Body513Buff[4] &= 0xFE;
		Body513Buff[4] |= 0x01;
	}
	else if(0 == pFcwData->FcwEnable)
	{
		Body513Buff[4] &= 0xFE;
//		Body513Buff[4] |= 0x01;
	}
	if(1 == pFcwData->AutoBrakeEnable)
	{
		Body513Buff[5] &= 0xFb;
		Body513Buff[5] |= 0x04;
	}
	else if(0 == pFcwData->AutoBrakeEnable)
	{
		Body513Buff[5] &= 0xFb;
//		Body513Buff[4] |= 0x01;
	}
	if(1 == pRcwData->BsdEnable)	//on
	{
		Body513Buff[5] &= 0xE7;
		Body513Buff[5] |= (0x02<<3);
	}
	else if(0 == pRcwData->BsdEnable)//off
	{
		Body513Buff[5] &= 0xE7;
		Body513Buff[5] |= (0x01<<3);
	}
	if(1 == pRcwData->CtaEnable)	// on		
	{
		Body513Buff[6] &= 0xcf;
		Body513Buff[6] |= (0x02<<4);
	}
	else if(0 == pRcwData->CtaEnable)	//off
	{
		Body513Buff[6] &= 0xcf;
		Body513Buff[6] |= (0x01<<4);
	}
	if(1 == pRcwData->RcwEnable)	// on		
	{
		Body513Buff[6] &= 0xf3;
		Body513Buff[6] |= (0x02<<2);
	}
	else if(0 == pRcwData->RcwEnable)	//off
	{
		Body513Buff[6] &= 0xc3;
		Body513Buff[6] |= (0x01<<2);
	}
	if(1 == pLdwData->LdwSensDat)		// 标准
	{
		Body513Buff[4] &= 0xcf;
		Body513Buff[4] |= (0x01<<4);
		
	}
	else if(0 == pLdwData->LdwSensDat) // 高
	{
		Body513Buff[4] &= 0xcf;
	}
	if(1 == pLdwData->SlaEnable)	// ON
	{
		Body513Buff[6] &= 0xBF;
		Body513Buff[6] |= (0x01<<6);
	}
	else if(0 == pLdwData->SlaEnable)	// OFF
	{
		Body513Buff[6] &= 0xBF;
	}
	if(1 == pLight->HmaEnable)		// ON
	{
		Body513Buff[6] &= 0x7F;
		Body513Buff[6] |= (0x01<<7);
	}
	else if(0 == pLight->HmaEnable)	//OFF
	{
		Body513Buff[6] &= 0x7F;
	}

}



/***************主动安全部分********************/
/****************巡航目标提示音*************************/
void CANUser_AccCtlDeal(uint8_t *pMsg, uint8_t len)	// BYTE6 bit10
{
	CarAccCtrlStruct* pAccData = pCAN_GetVehicleAccCrlData();
	
	if(pMsg[1] <4)
	{
		pAccData->DesWarnMode = pMsg[1];
		l_tBusData.VehicleData1.Acc_desWarnMode = pAccData->DesWarnMode;
		CAN_VehicleEepStore();
	}

	Body513Buff[6] &= 0xFC;					// BYTE6 bit01 
	Body513Buff[6] |=pAccData->DesWarnMode;

	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
	
}
/****************前碰撞预警*************************/
void CANUser_FcwDataDeal(uint8_t *pMsg, uint8_t len) // BYTE4 bit0
{
	CarFcwStruct* pFcwData = pCAN_GetFcwData();
	
	if(pMsg[1] < 2)
	{
		pFcwData->FcwEnable = pMsg[1];
		l_tBusData.VehicleData1.Fcw_crashWarnEnable = pFcwData->FcwEnable;
		CAN_VehicleEepStore();
	}

	if(1 == pFcwData->FcwEnable)
	{
		Body513Buff[4] &= 0xFE;
		Body513Buff[4] |= 0x01;
	}
	else if(0 == pFcwData->FcwEnable)
	{
		Body513Buff[4] &= 0xFE;
//		Body513Buff[4] |= 0x01;
	}
	
	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
}
/****************碰撞缓解*************************/
void CANUser_AutoBrakeDataDeal(uint8_t *pMsg, uint8_t len) // BYTE5 bit2
{
	CarFcwStruct* pFcwData = pCAN_GetFcwData();
	
	if(pMsg[1] < 2)
	{
		pFcwData->AutoBrakeEnable = pMsg[1];
		l_tBusData.VehicleData1.Fcw_autobrakeEnable = pFcwData->AutoBrakeEnable;
		CAN_VehicleEepStore();
	}


	if(1 == pFcwData->AutoBrakeEnable)
	{
		Body513Buff[5] &= 0xFb;
		Body513Buff[5] |= 0x04;
	}
	else if(0 == pFcwData->AutoBrakeEnable)
	{
		Body513Buff[5] &= 0xFb;
//		Body513Buff[4] |= 0x01;
	}

	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
}

/****************并线辅助*************************/

void CANUser_BsdDataDeal(uint8_t *pMsg, uint8_t len)	// BYTE5 bit34
{
	CarRcwStruct* pRcwData = pCAN_GetRcwData();
	
	if(pMsg[1] < 2)
	{
		pRcwData->BsdEnable = pMsg[1];
		l_tBusData.VehicleData1.Rcw_bsdEnable = pRcwData->BsdEnable;
		CAN_VehicleEepStore();
	}


	if(1 == pRcwData->BsdEnable)	//on
	{
		Body513Buff[5] &= 0xE7;
		Body513Buff[5] |= (0x02<<3);
	}
	else if(0 == pRcwData->BsdEnable)//off
	{
		Body513Buff[5] &= 0xE7;
		Body513Buff[5] |= (0x01<<3);
	}

	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
}

/****************倒车横向预警*************************/
void CANUser_CtaDataDeal(uint8_t *pMsg, uint8_t len)	// BYTE6 bit54
{
	CarRcwStruct* pRcwData = pCAN_GetRcwData();
	
	if(pMsg[1] < 2)
	{
		pRcwData->CtaEnable = pMsg[1];
		l_tBusData.VehicleData1.Rcw_ctaEnable = pRcwData->CtaEnable;
		CAN_VehicleEepStore();
	}


	if(1 == pRcwData->CtaEnable)	// on		
	{
		Body513Buff[6] &= 0xcf;
		Body513Buff[6] |= (0x02<<4);
	}
	else if(0 == pRcwData->CtaEnable)	//off
	{
		Body513Buff[6] &= 0xcf;
		Body513Buff[6] |= (0x01<<4);
	}

	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
}
/****************后追尾预警*************************/
void CANUser_RcwDataDeal(uint8_t *pMsg, uint8_t len)		// BYTE6 bit32
{
	CarRcwStruct* pRcwData = pCAN_GetRcwData();
	
	if(pMsg[1] < 2)
	{
		pRcwData->RcwEnable = pMsg[1];
		l_tBusData.VehicleData1.Rcw_crashWarnEnable = pRcwData->RcwEnable;
		CAN_VehicleEepStore();
	}


	if(1 == pRcwData->RcwEnable)	// on		
	{
		Body513Buff[6] &= 0xf3;
		Body513Buff[6] |= (0x02<<2);
	}
	else if(0 == pRcwData->RcwEnable)	//off
	{
		Body513Buff[6] &= 0xc3;
		Body513Buff[6] |= (0x01<<2);
	}

	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
}
/****************车道辅助灵敏度*************************/
void CANUser_LdwSensitivityDataDeal(uint8_t *pMsg, uint8_t len)//BYTE4 bit54
{
	CarLdwSensStruct* pLdwData = pCAN_GetLdwData();
	
	if(pMsg[1] < 2)
	{
		pLdwData->LdwSensDat = pMsg[1];
		l_tBusData.VehicleData1.Ldw_sensitivity = pLdwData->LdwSensDat;
		CAN_VehicleEepStore();
	}


	if(1 == pLdwData->LdwSensDat)		// 标准
	{
		Body513Buff[4] &= 0xcf;
		Body513Buff[4] |= (0x01<<4);
		
	}
	else if(0 == pLdwData->LdwSensDat) // 高
	{
		Body513Buff[4] &= 0xcf;
	}

	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
}
/****************限速标志识别*************************/
void CANUser_SlaSwitchDataDeal(uint8_t *pMsg, uint8_t len)  // BYTE6 bit6
{
	CarLdwSensStruct* pLdwData = pCAN_GetLdwData();
	
	if(pMsg[1] < 2)
	{
		pLdwData->SlaEnable = pMsg[1];
		l_tBusData.VehicleData2.Ldw_slaSwitch = pLdwData->SlaEnable;
		CAN_VehicleEepStore();
	}

	
	if(1 == pLdwData->SlaEnable)	// ON
	{
		Body513Buff[6] &= 0xBF;
		Body513Buff[6] |= (0x01<<6);
	}
	else if(0 == pLdwData->SlaEnable)	// OFF
	{
		Body513Buff[6] &= 0xBF;
	}

	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
}

/****************自动远光灯*************************/

void CANUser_HmaDataDeal(uint8_t *pMsg, uint8_t len)	// BYTE6 bit7
{
	CarLightDataStruct* pLight = pCAN_GetCarLightData();
	
	if(pMsg[1] < 2)
	{
		pLight->HmaEnable = pMsg[1];
		l_tBusData.VehicleData2.Ldw_hmaEnable = pLight->HmaEnable;
		CAN_VehicleEepStore();
	}

	
	if(1 == pLight->HmaEnable)		// ON
	{
		Body513Buff[6] &= 0x7F;
		Body513Buff[6] |= (0x01<<7);
	}
	else if(0 == pLight->HmaEnable)	//OFF
	{
		Body513Buff[6] &= 0x7F;
	}

	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
}

/****************行车灯*************************/
void CANUser_DrlDataDeal(uint8_t *pMsg, uint8_t len)	// ID 601  BYTE0 bit01
{
	CarLightDataStruct* pLight = pCAN_GetCarLightData();
	
	if(pMsg[1] < 2)
		pLight->DriveLightEnable = pMsg[1];

	if(1 == pLight->DriveLightEnable)		// ON
	{
		Body601Buff[0] &= 0xFC;
		Body601Buff[0] |= 0x02;
	}
	else if(0 == pLight->DriveLightEnable)	//OFF
	{
		Body601Buff[0] &= 0xFC;
	}

	CANUser_SetBodyCanMsgOnce(Body601Buff, CAN_TX_ID601);
	
}


/****************************************************/

void CANUser_CamLineDeal(uint8_t *pMsg, uint8_t len)
{
	uint8_t temp = 0;
	CarPACDataStruct *pPacData = pCAN_GetCarPACData();
	switch(pMsg[1])
	{
	case 0x00:/*路边停车模式*/	
		temp = 0;
		CANUser_debug(_T("CamLine\n"));	
		break;
	case 0x01:/*倒车入库模式*/
		temp = 1;
		CANUser_debug(_T("CamLine1\n"));	
		break;
	case 0x02:/*普通镜头模式*/
		temp = 2;
		CANUser_debug(_T("CamLine2\n"));	
		break;
	case 0x10://切换至下一模式（不指定具体模式)
		temp = (Body2F8Buff[0]>>6)&0xff;
		if(temp<2)
		{
			temp ++;
		}
		else
		{
			temp = 0;
		}
		CANUser_debug(_T("CamLine3,temp:%d\n",temp));	
		break;
		default :
			break;
	}
	Body2F8Buff[0] &= 0x3f;
	Body2F8Buff[0] |= (temp<<6);
	TaskCAN_debug(_T("-----camLine---mode = %d\n",temp));
	CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, CAN_TX_INNER_CYCLE);
	
	pPacData->ParkMode = temp;
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_PAC, 0);
}

void CANUser_AutowindSet(uint8_t *pMsg, uint8_t len)
{

}
void CANUser_ACGlassHeatDeal(uint8_t *pMsg, uint8_t len)
{

}
void CANUser_ACECOSwitch(uint8_t *pMsg, uint8_t len)
{

}
void CANUser_AirSensitivity(uint8_t *pMsg, uint8_t len)
{

}
void CANUser_Pollen_Filter_Switch(uint8_t *pMsg, uint8_t len)
{

}
void CANUser_ACWindLevelStepAdjDeal(uint8_t *pMsg, uint8_t len)
{
	
}

void CANUser_ACSeatHeatDeal(uint8_t *pMsg, uint8_t len)
{
	
}
void CANUser_TboxVINMsgHandler(uint8_t *pMsg, uint8_t len)
{
	if(NULL==pMsg)
	{
		return;
	}
	CAN_EepStore(DID_ID_F190, pMsg, len);
}
void CANUser_TboxPhoneMsgHandler(uint8_t *pMsg, uint8_t len)
{
	if(NULL==pMsg)
	{
		return;
	}
	CAN_EepStore(DID_TBOXREGNUM, pMsg, len);
}

void CANUser_MaintainDeal(uint8_t *pMsg, uint8_t len)
{
	if(pMsg[1] == 1)		/* vehicle need maintain */
	{
		Body2F8Buff[0] |= 0x10;
		CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, CAN_TX_INNER_CYCLE);
	}
	else
	{
		Body2F8Buff[0] &= ~0X10;
		CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, CAN_TX_INNER_CYCLE);
	}
}

void CANUser_RemoteSearch_Deal(uint8_t *pMsg, uint8_t len)
{
}

void CANUser_TboxCmdDeal(uint8_t *pMsg, uint8_t len)
{
}

void CANUser_LampDeal(uint8_t *pMsg, uint8_t len)
{
}

void CANUser_IllDeal(uint8_t *pMsg, uint8_t len)
{
}


void CANUser_WindowDeal(uint8_t *pMsg, uint8_t len)
{
	
}
void CANUser_DoorDeal(uint8_t *pMsg, uint8_t len)
{
	
}
void CANUser_RearBagDeal(uint8_t *pMsg, uint8_t len)
{

}
void CANUser_EngineDeal(uint8_t *pMsg, uint8_t len)
{
	
}
void CANUser_CruiseDeal(uint8_t *pMsg, uint8_t len)
{
	
}
/****************************************************************************
 * @function    CANAVMMsgDeal
 * @brief   deal with the CAN bus AVM data
 * @param   pRxMessage: CAN Receive message point
 * @retval  null
 * @attention:  null
****************************************************************************/
static void CANAVMMsgDeal(uint8_t State)
{
	CarAVMDataStruct *pAVM = pCAN_GetAVMData();

	pAVM->CarAvmState = State;
	CANTask_SendApiData(OMS_CAN_TX_CAR, OP_CAN_TX_AVM_INFO, 1);
}
/****************************************************************************
 * @function    CANBCMSystemDataDeal
 * @brief   deal with the CAN bus SystemFailureFlag data
 * @param   pRxMessage: CAN Receive message point
 * @retval  null
 * @attention:  null
****************************************************************************/
static void CANBCMSysDataDeal(CanMsgStruct *pRxMessage)
{
     uint8_t state1 = 0;

   	CarEcuDataStruct  *pData=pCAN_GetEcuData();

	if(pRxMessage->CANMsgDlc != 8)
	{
		return;
	}

	if(pData == NULL)
	{
		return;
	}

	if((pRxMessage->Data[7]) &0x01)  /*BCM系统故障*/
	{
		state1=1;
	}

	if(pData->BCM_System != state1)
	{
		pData->BCM_System = state1;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_ECU_STATE, 0);
	}

}

/****************************************************************************
 * @function    CANRxTestDataDeal
 * @brief   	receive test message(0x7f0) handler
 * @param   	pRxMessage: CAN Receive message point
 * @retval  	null
 * @attention:  just used for test.
****************************************************************************/
static void CANRxTestDataDeal(CanMsgStruct *pRxMessage)
{
	uint32_t Key = (pRxMessage->Data[4]<<24)|(pRxMessage->Data[5]<<16)|\
				(pRxMessage->Data[6]<<8)|pRxMessage->Data[7];
	if(Key != 0x12345678)
	{
		return;
	}
	
	switch(pRxMessage->Data[0])
	{
		case 0xf0:		/*read system software version */
			CANbus_InforOutputReq(pRxMessage->CAN_Id, (uint8_t*)ga_cSoftwareVer, 
				(uint8_t)API_StrLen((uint8_t*)ga_cSoftwareVer,0x20));
			break;
		case 0xf1:		/*read CAN Module version */
			#ifdef CAN_MODULE_ENABLE
			CANbus_InforOutputReq(pRxMessage->CAN_Id, (uint8_t*)CAN_MODULE_VERSION, 
				sizeof(CAN_MODULE_VERSION));
			#endif
			break;
		case 0xf2:		/*read UDS module version */
			#ifdef  UDS_ENABLE_MACRO
			CANbus_InforOutputReq(pRxMessage->CAN_Id, (uint8_t*)UDS_MODULE_VERSION, 
				sizeof(UDS_MODULE_VERSION));
			#endif
			break;
		case 0xf3:		/*read OSEK NM module version */
			#ifdef  NM_ENABLE_MACRO
			CANbus_InforOutputReq(pRxMessage->CAN_Id, (uint8_t*)NM_MODULE_VERSION, 
				sizeof(NM_MODULE_VERSION));
			#endif
			break;
		case 0xf4:		/*Receive-Send Test */
			CANbus_InforOutputReq(pRxMessage->CAN_Id, (uint8_t*)pRxMessage->Data, 1);
			break;
		case 0xf5:
			while(1);		/*WDT timeout to reset the system.*/
			break;
		case 0xf6:		/* Audio Debug */
			_SendFullMsgToHMI(MS_UI_SETTING,
							      /*SID*/pRxMessage->Data[1],
							      pRxMessage->Data[2],
							      pRxMessage->Data[3],
							      0x00,0x00);
			break;
		case 0xf7:	/*UICC command debug */
			_SendFullMsgToHMI(MS_INPUT_UI,
								pRxMessage->Data[1],
								pRxMessage->Data[2],0x00, 0x00,4);
			break;
		#ifdef CAN_INNER_ENABLE
		case 0x00:
			CANbus_InnerWriteDtvCmd(pRxMessage->Data[1]);
			break;
		case 0x01:
			CANbus_InnerWriteSourceType(pRxMessage->Data[1]);
			break;
		case 0x02:	
			CANTask_SendApiData(OMS_CAN_TX_DTV,OP_CAN_TX_DTV_VER, 0);
			break;
		#endif
		case 0x03:
			CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_SPEED, 0);
			break;
		case 0x04:
			CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_MAINTAIN, 0);
			break;
		case 0x05:	/*EEPROM test */
			CAN_EepStore(DID_ID_F190, pRxMessage->Data, 8);
			break;
		case 0x06:
			//TDF8546_RegisterTestWrite(&(pRxMessage->Data[1]));
			break;
		default:
			break;
	}
}

void CANRxFactoryTestDeal(CanMsgStruct *pRxMessage)
{/*条件限制*/
	if((0xFE == pRxMessage->Data[0])
	&&(0xDC == pRxMessage->Data[1])
	&&(0xBA == pRxMessage->Data[2])
	&&(0x98 == pRxMessage->Data[3])
	&&(0x76 == pRxMessage->Data[4])
	&&(0x54 == pRxMessage->Data[5])
	&&(0x32 == pRxMessage->Data[6])
	&&(0x1F == pRxMessage->Data[7])
	)
	{

		if(IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE)==0)
		{
			TaskCAN_debug(_T("ACC OFF.....CAN Msg Control Power OFF:OP_PM_STATE_ON----->OP_PM_STATE_OFF!!!!\n"));
			
			CANTask_SetCanPMStateStructState(3);
			CANTask_SetCanPMSateStructACCOffTimer1S(0);
			CANTask_SetCanPMSateStructWaitTimer1S(0);

		}
		else
			TaskCAN_debug(_T("ACC ON.....MCU Revice Power OFF msg!!!!\n"));
	}	
}

void CANRxDvrDataDeal(CanMsgStruct *pRxMessage)
{
#if 0
	CarDvrDataStruct *pData   =pCAN_GetDvrData();
	uint8_t temp;
	uint8_t i;
	
	if(pData == NULL)
	{
		return;
	}


	temp = pRxMessage->Data[0] &0xC0;
	if(0x80==temp)
	{ 
		pData->EnableStatu = 0x02;
	}
	else if(0x40==temp)
	{
		pData->EnableStatu = 0x01;
	}

	temp = pRxMessage->Data[0] &0x30;
	if(0x20==temp)
	{ 
		pData->TapeStatu = 0x02;
	}
	else if(0x10==temp)
	{
		pData->TapeStatu = 0x01;
	}

	temp = pRxMessage->Data[0] &0x0C;
	if(0x08==temp)
	{ 
		pData->ResolutionStatu = 0x02;
	}
	else if(0x04==temp)
	{
		pData->ResolutionStatu = 0x01;
	}

	temp = pRxMessage->Data[0] &0x03;
	if(0x01==temp)
	{ 
		pData->RecordingStatu = 0x01;
	}
	else if(0x02==temp)
	{
		pData->RecordingStatu = 0x02;
	}else if(0x03==temp)
	{
		pData->RecordingStatu = 0x03;
	}

	temp = pRxMessage->Data[1] &0x80;
	if(0x80==temp)
	{
		pData->SystemError = 0x01;
	}else if(0x00==temp)
	{
		pData->SystemError = 0x00;
	}

	temp = pRxMessage->Data[1] & 0x60;
	if(0x00==temp)
	{
		pData->RebroadcastStatu= 0x00;
	}else if(0x20==temp)
	{
		pData->RebroadcastStatu = 0x01;
	}else if(0x40==temp)
	{
		pData->RebroadcastStatu = 0x02;
	}
	else if(0x60 == temp)
	{
		pData->RebroadcastStatu = 0x03;
	}

	temp = pRxMessage->Data[1] &0x03;
	if(0x02==temp)
	{
		pData->PhotographResult= 0x02;
	}else if(0x01==temp)
	{
		pData->PhotographResult = 0x01;
	}else if(0x00==temp)
	{
		pData->PhotographResult = 0x00;
	}

	temp = pRxMessage->Data[2] &0xC0;
	if(0x80==temp)
	{
		pData->SdcardStatu = 0x02;
	}else if(0x40==temp)
	{
		pData->SdcardStatu = 0x01;
	}else if(0x00==temp)
	{
		pData->SdcardStatu = 0x00;
	}

	temp = pRxMessage->Data[2] &0x30;
	if(0x20==temp)
	{
		pData->RealtimeDisplayStatu = 0x02;
	}else if(0x10==temp)
	{
		pData->RealtimeDisplayStatu = 0x01;
	}

	temp = pRxMessage->Data[2] &0x0C;
	if(0x08==temp)
	{
		pData->SystemImprintStatu = 0x02;
	}else if(0x04==temp)
	{
		pData->SystemImprintStatu = 0x01;
	}

	temp = pRxMessage->Data[2] &0x03;
	if(0x02==temp)
	{
		pData->SDCapacityStatu = 0x02;
	}else if(0x01==temp)
	{
		pData->SDCapacityStatu = 0x01;
	}	

	temp = pRxMessage->Data[3] &0xC0;
	if(0x80==temp)
	{
		pData->ErrorRecordStatu = 0x02;
	}else if(0x40==temp)
	{
		pData->ErrorRecordStatu = 0x01;
	}
	temp = pRxMessage->Data[3] &0x30;
	if(0x20==temp)
	{
		pData->EmergencyRecordStatu = 0x02;
	}else if(0x10==temp)
	{
		pData->EmergencyRecordStatu = 0x01;
	}else if(0x00==temp)
	{
		pData->EmergencyRecordStatu = 0x00;
	}else if(0x30==temp)
	{
		pData->EmergencyRecordStatu = 0x03;
	}
	temp = pRxMessage->Data[3] &0x0E;
	temp >>=1;
	pData->DVRSdFormatStatus = temp;
	TaskCAN_debug(_T("===CANRxDvrDataDeal\n"));
	CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_S401,USERID_APU_TX_DVR_SETREQ, 1);
#endif
}


/****************************************************************************
 * @function	TJA1041_WorkModeSel
 * @brief  	TJA1041 CAN transceiver mode select
 * @param  	mode	
 * @retval 	null
 * @attention   null
****************************************************************************/
void CAN0_Transceiver_WorkModeSel(uint8_t  mode)
{
	switch(mode)
	{
		case CAN_TRANSCEIVER_MODE_NORMAL:
			IO_Set(IO_IDX_CAN0_EN,PIN_OUTPUT,1);
			IO_Set(IO_IDX_CAN0_STB,PIN_OUTPUT,1);
			break;

		case CAN_TRANSCEIVER_MODE_LISTEN_ONLY:
			IO_Set(IO_IDX_CAN0_EN,PIN_OUTPUT,0);
			IO_Set(IO_IDX_CAN0_STB,PIN_OUTPUT,1);
			break;
			
		case CAN_TRANSCEIVER_MODE_STANDBY:
			IO_Set(IO_IDX_CAN0_EN,PIN_OUTPUT,0);
			IO_Set(IO_IDX_CAN0_STB,PIN_OUTPUT,0);
			break;
			
		case CAN_TRANSCEIVER_MODE_SLEEP:
			IO_Set(IO_IDX_CAN0_EN,PIN_OUTPUT,1);
			IO_Set(IO_IDX_CAN0_STB,PIN_OUTPUT,0);
			break;
			
		default:
			break;
	}
}

void CAN1_Transceiver_WorkModeSel(uint8_t mode)
{
	switch(mode)
	{
		case CAN_TRANSCEIVER_MODE_NORMAL:
			IO_Set(IO_IDX_CAN1_STB,PIN_OUTPUT,0);
			break;
		case CAN_TRANSCEIVER_MODE_LISTEN_ONLY:
			IO_Set(IO_IDX_CAN1_STB,PIN_OUTPUT,0);
			break;
		case CAN_TRANSCEIVER_MODE_STANDBY:
			IO_Set(IO_IDX_CAN1_STB,PIN_OUTPUT,1);
			break;
		case CAN_TRANSCEIVER_MODE_SLEEP:
			IO_Set(IO_IDX_CAN1_STB,PIN_OUTPUT,1);
			break;
		default:
			break;
	}
}

/****************************************************************************
 * @function	CANbus_GetTransceiverErrorState
 * @brief  	This function get the CAN transceiver error state.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_GetTransceiverErrorState(uint8_t chno)
{

	if(chno==0)
	{
		if(IO_Get(IO_IDX_CAN0_ERR, PIN_INPUT, FALSE))
		{
			return 1;		
		}
		else
		{
			return 0;		
		}
	}
	else
	{
		return 1;
	}
}

/****************************************************************************
 * @function	CANUser_DebugInfoOutput
 * @brief  	use can module to output the system information. maximum is 8 byte.
 * @param  	can_id: CAN BUS channel
 *			pBuffer: point to the data buffer.
 *			len: size of the data buffer.
 * @retval 	null
 * @attention:  when buffer size oversize 8, only output the first 8 data.
****************************************************************************/
void CANUser_DebugInfoOutput(uint8_t can_id, uint8_t *pBuffer, uint8_t len)
{
	CanMsgStruct TestMsg;
	
	if(len>8)
	{
		len = 8;
	}
	
	TestMsg.CAN_Id = can_id;
	TestMsg.CANMsgId = CAN_TXID_TEST;		/* use 0x7ff as the send message ID */
	TestMsg.CANMsgDlc = len;
	Memory8Copy(&TestMsg.Data[0], pBuffer, len);
	CANbus_AppLayerSendOneShotMsg(&TestMsg);
}





























/********************************************************/
/****************私有CAN 数据发送函数************/
/********************************************************/
void CANUser_SetInnerCanMsg(uint8_t *pMsg, uint32_t CAN_ID)
{
	#ifdef CAN_BODY_ENABLE
	uint8_t i;
	CanMsgStruct TxMsg;
	TxMsg.CAN_Id = CAN_ID_INNER;// use channel 0
	TxMsg.CANMsgDlc = 8;
	TxMsg.CANMsgId  = CAN_ID;
	
	TxMsg.Data[0] = pMsg[0];
	TxMsg.Data[1] = pMsg[1];
	TxMsg.Data[2] = pMsg[2];
	TxMsg.Data[3] = pMsg[3];
	TxMsg.Data[4] = pMsg[4];
	TxMsg.Data[5] = pMsg[5];
	TxMsg.Data[6] = pMsg[6];
	TxMsg.Data[7] = pMsg[7];
	#if 0
	TaskCAN_debug(_T("私有CanMsgOnce:%ix",CAN_ID));
	for(i=0;i<8;i++)
	{
		TaskCAN_debug(_T("[%d]=%x",i,pMsg[i]));	
	}
	TaskCAN_debug(_T("\n"));	
	#endif
	CANbus_AppLayerSendPeriodicMsg(&TxMsg, TIMER_200MS);
	#endif
}


/********************************************************/
/****************公共CAN 数据发送函数************/
/********************************************************/
void CANUser_SetBodyCanMsgOnce(uint8_t *pMsg, uint32_t CAN_ID)
{
#ifdef CAN_BODY_ENABLE
	uint8_t i;
	CanMsgStruct TxMsg;
	TxMsg.CAN_Id = CAN_ID_BODY;// use channel 0
	TxMsg.CANMsgDlc = 8;
	TxMsg.CANMsgId  = CAN_ID;
	
	TxMsg.Data[0] = pMsg[0];
	TxMsg.Data[1] = pMsg[1];
	TxMsg.Data[2] = pMsg[2];
	TxMsg.Data[3] = pMsg[3];
	TxMsg.Data[4] = pMsg[4];
	TxMsg.Data[5] = pMsg[5];
	TxMsg.Data[6] = pMsg[6];
	TxMsg.Data[7] = pMsg[7];
	#if 0
	TaskCAN_debug(_T("公共CanMsgOnce:%ix",CAN_ID));
	for(i=0;i<8;i++)
	{
		TaskCAN_debug(_T("[%d]=%x",i,pMsg[i]));	
	}
	TaskCAN_debug(_T("\n"));	
	#endif
	CANbus_AppLayerSendOneShotMsg(&TxMsg);
#endif
}

void CANUser_SetBodyCanMsgPeriodic(uint8_t *pMsg, uint32_t CAN_ID, uint16_t cycleTime)
{
#ifdef CAN_BODY_ENABLE
	uint8_t i;
	CanMsgStruct TxMsg;
	TxMsg.CAN_Id = CAN_ID_BODY;
	TxMsg.CANMsgDlc = 8;
	TxMsg.CANMsgId  = CAN_ID;
	
	TxMsg.Data[0] = pMsg[0];
	TxMsg.Data[1] = pMsg[1];
	TxMsg.Data[2] = pMsg[2];
	TxMsg.Data[3] = pMsg[3];
	TxMsg.Data[4] = pMsg[4];
	TxMsg.Data[5] = pMsg[5];
	TxMsg.Data[6] = pMsg[6];
	TxMsg.Data[7] = pMsg[7];
	#if 0
	TaskCAN_debug(_T("公共CanMsgPeriodic:%ix",CAN_ID));
	for(i=0;i<8;i++)
	{
		TaskCAN_debug(_T("[%d]=%x",i,pMsg[i]));	
	}
	TaskCAN_debug(_T("\n"));	
	#endif
	CANbus_AppLayerSendPeriodicMsg(&TxMsg, cycleTime);
#endif
}































/********************************************************/
/*********************接收数据分析*****************/
/********************************************************/
//R103-H15T  TPMS   500ms 
//#define D_TPMS_DEBUG
static void CANBcm347Deal(CanMsgStruct *pRxMessage)
{
	uint32_t TempState;

	TPMSDataStruct	*pTpmsData = pCAN_GetTPMSData();

	if(pRxMessage->CANMsgDlc != 8)
	{
		return;
	}

	#ifdef D_TPMS_DEBUG
	TaskCAN_debug(_T("CAN Receive Msg From 0x347:%x %x %x %x %x %x %x %x\n",pRxMessage->Data[0],
		pRxMessage->Data[1],pRxMessage->Data[2],pRxMessage->Data[3],pRxMessage->Data[4],
		pRxMessage->Data[5],pRxMessage->Data[6],pRxMessage->Data[7]));
	#endif

	
	//信号状态
	pTpmsData->SignalStatus = (pRxMessage->Data[0] >> 7) & 0x01;
	//系统故障信息
	pTpmsData->SystemFailure = (pRxMessage->Data[7] & 0x01);
	//胎压信号有效标志位
	pTpmsData->TirePresureSignalStatus = (pRxMessage->Data[6]>> 7) & 0x01;
	//节点在线标志
	pTpmsData->TpmsOnlineState = 1;
	
	//温度报警
	pTpmsData->FL_temperatureWarn = ((pRxMessage->Data[0] >> 6) & 0x01);
	pTpmsData->FR_temperatureWarn = ((pRxMessage->Data[0] >> 5) & 0x01);
	pTpmsData->RR_temperatureWarn = ((pRxMessage->Data[0] >> 4) & 0x01);
	pTpmsData->RL_temperatureWarn = ((pRxMessage->Data[0] >> 3) & 0x01);

	//温度值
	switch(pRxMessage->Data[0] & 0x07)
	{
		case 0x01:
				pTpmsData->FL_tyreTemperature = pRxMessage->Data[5];
			break;
		case 0x02:
				pTpmsData->FR_tyreTemperature = pRxMessage->Data[5];
			break;
		case 0x03:
				pTpmsData->RR_tyreTemperature = pRxMessage->Data[5];
			break;
		case 0x04:
				pTpmsData->RL_tyreTemperature = pRxMessage->Data[5];
			break;
		default:
			//pTpmsData->FL_tyreTemperature = 0x00;
			//pTpmsData->FR_tyreTemperature = 0x00;
			//pTpmsData->RR_tyreTemperature = 0x00;
			//pTpmsData->RL_tyreTemperature = 0x00;
			break;
	}
			
	//胎压值
	pTpmsData->FL_tyrePressure = pRxMessage->Data[1];
	pTpmsData->FR_tyrePressure = pRxMessage->Data[2];
	pTpmsData->RR_tyrePressure = pRxMessage->Data[3];
	pTpmsData->RL_tyrePressure = pRxMessage->Data[4];

	//胎压报警值
	//过滤保留位数据,不上发给OS
	if((((pRxMessage->Data[6]>>4) & 0x07) != 0x03) && (((pRxMessage->Data[6]>>4) & 0x07) != 0x07) )
		pTpmsData->FL_WarnStatus = (pRxMessage->Data[6]>>4) & 0x07;
	if(((pRxMessage->Data[6] & 0x07) != 0x03) && ((pRxMessage->Data[6] & 0x07) != 0x07) )
		pTpmsData->FR_WarnStatus = pRxMessage->Data[6] & 0x07;
	if((((pRxMessage->Data[7]>>5) & 0x07) != 0x03) && (((pRxMessage->Data[7]>>5) & 0x07) != 0x07) )
		pTpmsData->RR_WarnStatus = (pRxMessage->Data[7]>>5) & 0x07;
	if((((pRxMessage->Data[7]>>2) & 0x07) != 0x03) && (((pRxMessage->Data[7]>>2) & 0x07) != 0x07) )
		pTpmsData->RL_WarnStatus = (pRxMessage->Data[7]>>2) & 0x07;


	#ifdef D_TPMS_DEBUG
		TaskCAN_debug(_T("信号状态:%d\n",pTpmsData->SignalStatus));
		TaskCAN_debug(_T("系统故障:%d\n",pTpmsData->SystemFailure));
		TaskCAN_debug(_T("胎压信号状态:%d\n",pTpmsData->TirePresureSignalStatus));
		TaskCAN_debug(_T("温度值[Hex]:%x-%x-%x-%x(FL-FR-RR-RL)\n",pTpmsData->FL_tyreTemperature,
			pTpmsData->FR_tyreTemperature,pTpmsData->RR_tyreTemperature,pTpmsData->RL_tyreTemperature));
		TaskCAN_debug(_T("温度报警:%d-%d-%d-%d(FL-FR-RR-RL)\n",pTpmsData->FL_temperatureWarn,
			pTpmsData->FR_temperatureWarn,pTpmsData->RR_temperatureWarn,pTpmsData->RL_temperatureWarn));
		TaskCAN_debug(_T("胎压值[Hex]:%x-%x-%x-%x(FL-FR-RR-RL)\n",pTpmsData->FL_tyrePressure,
			pTpmsData->FR_tyrePressure,pTpmsData->RR_tyrePressure,pTpmsData->RR_tyrePressure));
		TaskCAN_debug(_T("胎压报警:%d-%d-%d-%d(FL-FR-RR-RL)\n",pTpmsData->FL_WarnStatus,
			pTpmsData->FR_WarnStatus,pTpmsData->RR_WarnStatus,pTpmsData->RL_WarnStatus));
	#endif

	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_TPMS_DATA, 1);//snake20160901 real send
	
}

//#define D_DVR_DEBUG
static void CANDvr612Deal(CanMsgStruct *pRxMessage)
{
	uint8_t DvrInfoUpdata = 0;
	CarDvrDataStruct *pData   = pCAN_GetDvrData();
	CarDvrVerStruct *pVer = pCAN_GetDvrVer();

	/*if(pRxMessage->CANMsgDlc != 8)  //snake20160901
	{
		return;
	}*/
	
	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("CAN Receive Msg From 0x612:%x %x %x %x %x %x %x %x\n",pRxMessage->Data[0],
		pRxMessage->Data[1],pRxMessage->Data[2],pRxMessage->Data[3],pRxMessage->Data[4],
		pRxMessage->Data[5],pRxMessage->Data[6],pRxMessage->Data[7]));
	#endif
	
	pData->DVR_ConnectedState = 1;//DVR的连接状态,在报文丢失的时候,此标志清0

	//DATA[0]  setting state result
	if(pData->DVR_ResolutionStatus != (pRxMessage->Data[0] & 0xc0) >> 6)
	{
		DvrInfoUpdata = 1;
		pData->DVR_ResolutionStatus = (pRxMessage->Data[0] & 0xc0) >> 6;
	}
	if(pData->DVR_RecordingCycleSetStatus != (pRxMessage->Data[0] & 0x30) >> 4)
	{
		DvrInfoUpdata = 1;
		pData->DVR_RecordingCycleSetStatus = (pRxMessage->Data[0] & 0x30) >> 4;
	}
	if(pData->DVR_TapeSetStatus != (pRxMessage->Data[0] & 0x0c) >> 2)
	{
		DvrInfoUpdata = 1;
		pData->DVR_TapeSetStatus = (pRxMessage->Data[0] & 0x0c) >> 2;	
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pData->DVR_ResolutionStatus = %x\n",pData->DVR_ResolutionStatus));
	TaskCAN_debug(_T("pData->DVR_RecordingCycleSetStatus = %x\n",pData->DVR_RecordingCycleSetStatus));
	TaskCAN_debug(_T("pData->DVR_TapeSetStatus = %x\n",pData->DVR_TapeSetStatus));
	#endif
	
	//DATA[1]  system state and sdCard state
	if(pData->DVR_SystemStatus != (pRxMessage->Data[1] & 0xf0) >> 4)
	{
		DvrInfoUpdata = 1;
		pData->DVR_SystemStatus = (pRxMessage->Data[1] & 0xf0) >> 4;
	}
	if(pData->DVR_SDcardStatus != (pRxMessage->Data[3] & 0x07))
	{
		DvrInfoUpdata = 1;
		pData->DVR_SDcardStatus = (pRxMessage->Data[3] & 0x07);	
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pData->DVR_SystemStatus = %x\n",pData->DVR_SystemStatus));
	TaskCAN_debug(_T("pData->DVR_SDcardStatus = %x\n",pData->DVR_SDcardStatus));
	#endif
	
	//DATA[5]  Page  Attribute
	if(pData->DVR_PageAttribute != (pRxMessage->Data[0] & 0x03))
	{
		DvrInfoUpdata = 1;
		pData->DVR_PageAttribute = (pRxMessage->Data[0] & 0x03);	
	}
	//DATA[6] DATA[7] page number
	if(pData->DVR_CurrentPageNum != pRxMessage->Data[7])
	{
		DvrInfoUpdata = 1;
		pData->DVR_CurrentPageNum = pRxMessage->Data[7];
	}
	if(pData->DVR_TotalPageNum != pRxMessage->Data[6])
	{
		DvrInfoUpdata = 1;
		pData->DVR_TotalPageNum = pRxMessage->Data[6];	
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pData->DVR_PageAttribute = %x\n",pData->DVR_PageAttribute));
	TaskCAN_debug(_T("pData->DVR_CurrentPageNum = %x\n",pData->DVR_CurrentPageNum));
	TaskCAN_debug(_T("pData->DVR_TotalPageNum = %x\n",pData->DVR_TotalPageNum));
	#endif
	
	//DATA[8] error info
	if(pData->DVR_ErrorStatus_PowerError != (pRxMessage->Data[3] & 0x10) >> 4)
	{
		DvrInfoUpdata = 1;
		pData->DVR_ErrorStatus_PowerError = (pRxMessage->Data[3] & 0x10) >> 4;
	}
	if(pData->DVR_ErrorStatus_SystemError != (pRxMessage->Data[3] & 0x20) >> 5)
	{
		DvrInfoUpdata = 1;
		pData->DVR_ErrorStatus_SystemError = (pRxMessage->Data[3] & 0x20) >> 5;	
	}
	if(pData->DVR_ErrorStatus_KeyError != (pRxMessage->Data[3] & 0x40) >> 6)
	{
		DvrInfoUpdata = 1;
		pData->DVR_ErrorStatus_KeyError = (pRxMessage->Data[3] & 0x40) >> 6;
	}
	if(pData->DVR_ErrorStatus_SDCardError != (pRxMessage->Data[3] & 0x80) >> 7)
	{
		DvrInfoUpdata = 1;
		pData->DVR_ErrorStatus_SDCardError = (pRxMessage->Data[3] & 0x80) >> 7;
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pData->DVR_ErrorStatus_PowerError = %x\n",pData->DVR_ErrorStatus_PowerError));
	TaskCAN_debug(_T("pData->DVR_ErrorStatus_SystemError = %x\n",pData->DVR_ErrorStatus_SystemError));
	TaskCAN_debug(_T("pData->DVR_ErrorStatus_KeyError = %x\n",pData->DVR_ErrorStatus_KeyError));
	TaskCAN_debug(_T("pData->DVR_ErrorStatus_SDCardError = %x\n",pData->DVR_ErrorStatus_SDCardError));
	#endif
	
	if(DvrInfoUpdata == 1)
	{
		CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_SETREQ, 1);
	}
	
	//版本和容量信息.
	if(pVer->DvrVersion_Year != pRxMessage->Data[4])
	{
		DvrInfoUpdata = 2;
		pVer->DvrVersion_Year = pRxMessage->Data[4]; //整数
	}
	if(pVer->DvrVersion_Month != pRxMessage->Data[5])
	{
		DvrInfoUpdata = 2;
		pVer->DvrVersion_Month = pRxMessage->Data[5];//小数
	}

	//容量信息
	if((pRxMessage->Data[3]&0x08)>>3) //剩余容量
	{
		DvrInfoUpdata = 2;
		pVer->DVR_SDResidualCapacity_Integer = pRxMessage->Data[2];
		pVer->DVR_SDResidualCapacity_Decimals = pRxMessage->Data[1] & 0x0f;
	}
	else //总容量
	{
		DvrInfoUpdata = 2;
		pVer->DVR_SDTotalCapacity_Integer = pRxMessage->Data[2];
		pVer->DVR_SDTotalCapacity_Decimals = pRxMessage->Data[1] & 0x0f;
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pVer->DvrVersion_Year = %x\n",pVer->DvrVersion_Year));
	TaskCAN_debug(_T("pVer->DvrVersion_Month = %x\n",pVer->DvrVersion_Month));
	TaskCAN_debug(_T("pVer->DVR_SDTotalCapacity_Integer = %x\n",pVer->DVR_SDTotalCapacity_Integer));
	TaskCAN_debug(_T("pVer->DVR_SDTotalCapacity_Decimals = %x\n",pVer->DVR_SDTotalCapacity_Decimals));
	TaskCAN_debug(_T("pVer->DVR_SDResidualCapacity_Integer = %x\n",pVer->DVR_SDResidualCapacity_Integer));
	TaskCAN_debug(_T("pVer->DVR_SDResidualCapacity_Decimals = %x\n",pVer->DVR_SDResidualCapacity_Decimals));
	#endif
	
	if(DvrInfoUpdata == 2)
	{
		CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_VER, 1);
	}
		
}
//envent msg real send to apu
static void CANDvr613Deal(CanMsgStruct *pRxMessage)
{
	uint8_t DvrInfoUpdata = 0;
	CarDvrDataStruct *pData   =pCAN_GetDvrData();

	/*if(pRxMessage->CANMsgDlc != 8)
	{
		return;
	}*/
	
	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("CAN Receive Msg From 0x613:%x %x %x %x %x %x %x %x\n",pRxMessage->Data[0],
		pRxMessage->Data[1],pRxMessage->Data[2],pRxMessage->Data[3],pRxMessage->Data[4],
		pRxMessage->Data[5],pRxMessage->Data[6],pRxMessage->Data[7]));
	#endif

	pData->DVR_ConnectedState = 1;//DVR的连接状态,在报文丢失的时候,此标志清0

	//snake20160919 比较数据是否变化,在发送给APP
	//state information
	//DATA[2]  command operation result
	if(pData->DVR_DestinationPageResult != (pRxMessage->Data[1] & 0X03))
	{
		DvrInfoUpdata = 1;
		pData->DVR_DestinationPageResult = pRxMessage->Data[1] & 0X03;
	}
	if(pData->DVD_RestoreFactorySettingResult != ((pRxMessage->Data[1] & 0X0C) >> 2))
	{
		DvrInfoUpdata = 1;
		pData->DVD_RestoreFactorySettingResult = (pRxMessage->Data[1] & 0X0C) >> 2;
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pData->DVR_DestinationPageResult = %x\n",pData->DVR_DestinationPageResult));
	TaskCAN_debug(_T("pData->DVD_RestoreFactorySettingResult = %x\n",pData->DVD_RestoreFactorySettingResult));
	#endif
	
	if(pData->DVR_SDFormatResult != ((pRxMessage->Data[1] & 0X30) >> 4))
	{
		DvrInfoUpdata = 1;
		pData->DVR_SDFormatResult = (pRxMessage->Data[1] & 0X30) >> 4;
	}
	if(pData->DVR_PhotographResult != ((pRxMessage->Data[0] & 0XC0) >> 6))
	{
		DvrInfoUpdata = 1;		
		pData->DVR_PhotographResult = (pRxMessage->Data[0] & 0XC0) >> 6;
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pData->DVR_SDFormatResult = %x\n",pData->DVR_SDFormatResult));
	TaskCAN_debug(_T("pData->DVR_PhotographResult = %x\n",pData->DVR_PhotographResult));
	#endif

	//DATA[3]  commandList operation result
	if(pData->DVR_CommandResult != ((pRxMessage->Data[1] & 0XC0) >> 6))
	{
		DvrInfoUpdata = 1;
		pData->DVR_CommandResult = (pRxMessage->Data[1] & 0XC0) >> 6;
	}
	if(pData->DVD_ProgrammingModeResult != ((pRxMessage->Data[2] & 0XE0) >> 5))
	{
		DvrInfoUpdata = 1;
		pData->DVD_ProgrammingModeResult = (pRxMessage->Data[2] & 0XE0) >> 5;
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pData->DVR_CommandResult = %x\n",pData->DVR_CommandResult));
	TaskCAN_debug(_T("pData->DVD_ProgrammingModeResult = %x\n",pData->DVD_ProgrammingModeResult));
	#endif
	
	//DATA[4]  commandList
	if(pData->DVR_CommandList != (pRxMessage->Data[0] & 0X3F))
	{
		DvrInfoUpdata = 1;
		pData->DVR_CommandList = (pRxMessage->Data[0] & 0X3F);
	}

	#ifdef D_DVR_DEBUG
	TaskCAN_debug(_T("pData->DVR_CommandList = %x\n",pData->DVR_CommandList));
	#endif
	
	if(DvrInfoUpdata)
		CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_SETREQ, 1);

}

static void CANFuelLevelDeal(CanMsgStruct *pRxMessage)
{
	FuelLevelStruct *pFuel = pCAN_GetCarFuelLevelData();

	pFuel->CurrFuelLevel = pRxMessage->Data[1] & 0x0F;

	if(2 == pFuel->CurrFuelLevel )
	{
		if(PreFuelLevel != pFuel->CurrFuelLevel)
		{
			if(CANTask_GetSysACCState() && l_tMediaCB.uDevFlag.field.bDevConnect)
			{
				PreFuelLevel = pFuel->CurrFuelLevel;
				CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_FUEL_LEVEL, 1);
			}
		}
	}
	else if(1 == pFuel->CurrFuelLevel || 0 == pFuel->CurrFuelLevel)
	{
		if(0 == CANTask_GetSysACCState())
		{
			PreFuelLevel = 0xFF;
		}
		if(PreFuelLevel != pFuel->CurrFuelLevel)
		{
			if(CANTask_GetSysACCState() && l_tMediaCB.uDevFlag.field.bDevConnect)
			{
				PreFuelLevel = pFuel->CurrFuelLevel;
				CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_FUEL_LEVEL, 1);
			}
		}
	}
#if 0	
	else if(0 == pFuel->CurrFuelLevel)
	{
		if(0 == CANTask_GetSysACCState())
		{
			PreFuelLevel = 0xFF;
		}
		if(PreFuelLevel != pFuel->CurrFuelLevel)
		{
			if(CANTask_GetSysACCState() && l_tMediaCB.uDevFlag.field.bDevConnect)
			{
				PreFuelLevel = pFuel->CurrFuelLevel;
				CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_FUEL_LEVEL, 1);
			}
		}
	}
#endif	
	else
	{
		PreFuelLevel = pFuel->CurrFuelLevel;
	}
}



static void CANBcm349Deal(CanMsgStruct *pRxMessage)
{
	CarPEPSDataStruct *pData = pCAN_GetPEPSData();
	CarECOInfoStruct *pECO = pCAN_GetVehicleECOData();
	CanPmStruct *pCanPmData = pCAN_GetCarCanPmData();

	static uint16_t sendCnt = 0;

	CanPmRecTimer = 0;	//用于当ID349丢失时的计数
	
	if(pData == NULL)
	{
		return;
	}
#if 1
	pCanPmData->Car_State = pRxMessage->Data[1] & 0x0C;
	pCanPmData->Car_State = pCanPmData->Car_State >> 2;
	
	pCanPmData->Car_PMLevel = pRxMessage->Data[0] & 0x38;
	pCanPmData->Car_PMLevel >>= 3;

	pCanPmData->Car_LowPowerWarn = pRxMessage->Data[0] & 0x07;
#endif
	if(CANTask_GetSysACCState() && l_tMediaCB.uDevFlag.field.bDevConnect )	
	{
		if((++sendCnt%4) == 0)	// 4*500ms = 2S 
		{
			CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAN_PM_DATA, 1);
		}
	}
	if((0 == pCanPmData->Car_State && 2 == pCanPmData->Car_PMLevel && 2 == pCanPmData->Car_LowPowerWarn)
	||(2 == pCanPmData->Car_State && 2 == pCanPmData->Car_PMLevel && 2 == pCanPmData->Car_LowPowerWarn)
	)
	{
		CanPmEnterStandbyFlg = 1;
		CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);//Wait sleep mode
	}
	else if(1 == CanPmEnterStandbyFlg)
	{
		CanPmEnterStandbyFlg = 0;
		CANTask_SendPMReqest(OP_PM_STATE_ON);//exit sleep mode
	}
}

static void CANBcm352Deal(CanMsgStruct *pRxMessage)
{
	CarRMirrorDataStruct *pData1 = pCAN_GetRearMirrorData();
	CarSeatDataStruct *pData2 = pCAN_GetSeatData();

	uint8_t temp1 = 0x00, temp2 = 0x00;

	if((pData1 == NULL)||(pData2 == NULL))
	{
		return;
	}

	temp1 = pRxMessage->Data[2] & 0x03;
	if((pRxMessage->Data[2] & 0x03)==0x01)
		pData1->RearAssist=0;
	if((pRxMessage->Data[2] & 0x03)==0x02)
		pData1->RearAssist=1;
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_RMIRROR, 1);

	temp2 = pRxMessage->Data[0] & 0xC0;
	temp2>>=6;
	if(temp2 != pData2->SeatAutoSet)
	{
		pData2->SeatAutoSet=temp2;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_SEAT, 1);
	}
}

uint8_t iCnt = 0x00;
static void CANBcm340Deal(CanMsgStruct *pRxMessage)
{
	uint8_t NewData=0, OldData=0;
	FrontACDataStruct *FrontData=pCAN_GetFrontACData();
	RearACDataStruct  *RearData = pCAN_GetRearACData();
	
	
	if((FrontData==NULL)||(RearData==NULL)) { return; }
	
	//前排自动调节
	NewData=pRxMessage->Data[0]&0x60;//0b0110 0000
	NewData >>= 5;
	if(NewData != FrontData->AutoMode)
	{
		FrontData->AutoMode =NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	//前吹风模式
	NewData=pRxMessage->Data[0]&0x07;//0b0000 0111
	if(NewData != (FrontData->ACState&0x07))
	{
		FrontData->ACState &= 0xF8;//0b1111 1000
		FrontData->ACState|=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	//前温区切换
	NewData=pRxMessage->Data[0] & 0x18;//0b0001 1000
	NewData >>= 3;
	if(NewData != FrontData->DualSwitch)//温区有变化
	{
		FrontData->DualSwitch=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	//主驾驶温度
	NewData=pRxMessage->Data[3]&0x03;//0b0000 0011
	NewData<<=3;
	NewData|=pRxMessage->Data[4]>>5; //0b1110 0000
	if(NewData != FrontData->LeftTemperature)
	{
		FrontData->LeftTemperature=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	//副驾驶温度
	NewData=pRxMessage->Data[4]&0x1F;//0b0001 1111
	if(NewData != FrontData->RightTemperature)
	{
		FrontData->RightTemperature=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	//前内外循环
	NewData=pRxMessage->Data[5]&0x07;//0b0000 0111 
	if(NewData != FrontData->CycleMode)
	{
		FrontData->CycleMode=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	//前AC开关消息
	NewData=pRxMessage->Data[0]&0x80;//0b1000 0000 
	NewData>>=7;
	if(NewData != FrontData->ACSwitch)
	{
		FrontData->ACSwitch=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}




	//后吹风模式
	NewData=pRxMessage->Data[1]&0xC0;//0b1100 0000 
	NewData>>=6;
	if(NewData != RearData->WindMode)
	{
		RearData->WindMode=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_REAR, 1);
	}
	//后排自动模式
	NewData=pRxMessage->Data[1]&0x30;//0b0011 0000 
	NewData>>=4;
	if(NewData != RearData->AutoMode)
	{
		RearData->AutoMode=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_REAR, 1);
	}
	//后排风量值
	NewData=pRxMessage->Data[1]&0x0F;//0b0000 1111
	if(NewData != RearData->WindLevel)
	{
		RearData->WindLevel=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_REAR, 1);
	}
	//后排温度调节
	NewData=pRxMessage->Data[3]&0x7C;//0b0111 1100
	NewData>>=2;
	if(NewData != RearData->LeftTemperature)
	{
		RearData->LeftTemperature=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_REAR, 1);
	}
	
	//浮屏信息显示
	NewData=pRxMessage->Data[5]&0x20;//0b0010 0000
	if(NewData)
	{
		iCnt=1;
		FrontData->InsideTemperature=0x01;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	else
	{
		if (iCnt ) iCnt++;
		if(iCnt > 3)
		{
			iCnt = 0;
			FrontData->InsideTemperature=0x00;
		}
	}
}

static void CANBcm330Deal(CanMsgStruct *pRxMessage)
{
	uint8_t NewData = 0;
	
	
	FrontACDataStruct *FrontData=pCAN_GetFrontACData();
	
	//前排风量值
	NewData=pRxMessage->Data[3]>>4;//0b1111 0000
	if(NewData != FrontData->WindLevel)
	{
		FrontData->WindLevel=NewData;
		TaskCAN_debug(_T("CANBcm340Deal %d:\n ",NewData));
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	//车外温度值

	if((pRxMessage->Data[6] & 0x01)||(0xFF == pRxMessage->Data[7]))	    // temp invalid 
	{
		CurrExtTempValid = 0;
		if(1 == PreExtTempValid)
		{
			FrontData->OutsideTemperature=0xFF;
//			CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
			PreExtTempValid = 0;
		}
	}
	else		// temp valid
	{
		CurrExtTempValid = 1;
		NewData=pRxMessage->Data[7];
		if(NewData != FrontData->OutsideTemperature)
		{
			FrontData->OutsideTemperature=NewData;
			CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
		}
		if(0 == PreExtTempValid)
		{
			FrontData->OutsideTemperature=NewData;
			CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
			PreExtTempValid = 1;
		}
	}
}

static void CANBcm288Deal(CanMsgStruct *pRxMessage)
{
	uint8_t NewData = 0 , AccState = 0;
	static uint8_t delaycnt = 0;
	
	FrontACDataStruct *FrontData=pCAN_GetFrontACData();
	CANVehicleStateStruct *pData = pCAN_GetVehicleState();
	CarSystemDataStruct *pSysData=pCAN_GetSystemData();
	CarECOInfoStruct *pECO = pCAN_GetVehicleECOData();

	if(pRxMessage->CANMsgDlc<6)
	{
		return;
	}

	//后除霜反馈
	NewData=pRxMessage->Data[4]&0x03;//0b0000 0011
	if(NewData != FrontData->RearDefrost)
	{
		FrontData->RearDefrost=NewData;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
	}
	if(++delaycnt >= 5)
	{
		delaycnt = 0;
		if(0 == CANTask_GetRemoteStartState())
		{
			//ACC
			AccState=pRxMessage->Data[5]&0x0C;
			AccState>>=2;

			if(pECO->AccPowerStatus != AccState)
			{
				pECO->AccPowerStatus = AccState;
				CANUserVar.ECOChgFlag = 1;
			}
			if(AccState == 0x00)
			{
				pData->CAN_Acc = 0;
				memset(Body501Buff,0,8);//ACC OFF 清除时间
			}
			if(AccState == 0x01)
			{
				pData->CAN_Acc = 1;
			}
			if(AccState == 0x02)
			{
				pData->CAN_Acc = 2;
			}
			if(AccState == 0x03)
			{
				pData->CAN_Acc = 3;
			}

			if(pSysData->ACC_Status != AccState)
			{
				pSysData->ACC_Status = AccState;
				CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_SYS, 0);
			}
		}
	}
}

static void CANPEPSDataDeal(CanMsgStruct *pRxMessage)
{
    	uint8_t state1 = 0;

	CANVehicleStateStruct *pData = pCAN_GetVehicleState();
	uint8_t peps = 0;


	if(pRxMessage->CANMsgDlc!=8)
	{
		return;
	}

	state1 = pRxMessage->Data[0] &0x0C;
	state1>>=2;
	#if 1	
	peps = pRxMessage->Data[4] & 0xC0;
	peps = peps>>6;

	if(3 != peps)
	{
		if(1 == peps)
		{
			pData->CAN_peps = 1;
		}
		else if(0 == peps)
		{
			pData->CAN_peps = 0;
		}
	}
     #endif	
	if(state1==1)//解锁
	{
		pData->CAN_Lock = 0;
	}
	if(state1==2)//解锁
	{
		pData->CAN_Lock = 0;
	}

	state1 = pRxMessage->Data[0] &0x03;
	if(state1==1)//闭锁
	{
		pData->CAN_Lock = 1;
	}
	if(state1==2)//闭锁
	{
		pData->CAN_Lock = 1;
	}
}
static void CANAvmDataDeal(CanMsgStruct *pRxMessage)
{
	CarAVMDataStruct *pData = pCAN_GetAVMData();
	AvmExistFlag = 1;
	if((pRxMessage->Data[0]&0x40)||(pRxMessage->Data[0]&0x44))
	{
	        	if((pRxMessage->Data[0]&0x0C)==0x00)//全屏
			{
			      CANAVMMsgDeal(1);
			}
			if((pRxMessage->Data[0]&0x0C)==0x04)//半屏
			{
			      CANAVMMsgDeal(2);
			}
	}
      if(pData->ADIINITFlag==1)
  	{
		if(pRxMessage->Data[0] &0x40)
		{//Yes display  	      	
				if(pData->CarAVMReq==0)
				  {
					pData->CarAVMReq = 1;
					_SendMsgToSRC(MS_SRC_SET_FLOAT_TYPE, SRC_TYPE_REVERSE, 1);
					_SendMsgToSRC(MS_INPUT_UI,UICC_STOP_SEEK,NULL); 
				   }
		}
		else
		{//No display  
					if(pData->CarAVMReq==1)
					{
						pData->CarAVMReq = 0;
						_SendMsgToSRC(MS_SRC_SET_FLOAT_TYPE, SRC_TYPE_REVERSE, 0);
						_SendMsgToSRC(MS_INPUT_UI,UICC_STOP_SEEK,NULL); 
					}			
	       }
  	}

}


static void CANRadarDataDeal(CanMsgStruct *pRxMessage)
{
	RadarStatusDataStruct *pRadarData =pCAN_GetRadarStatusData();

	#if 0
	TaskCAN_debug(_T("===CANRadarDataDeal %x,%x,%x\n",
		pRxMessage->Data[0],pRxMessage->Data[1],pRxMessage->Data[2]));
	#endif
	
	pRadarData->RRM_Distance = pRxMessage->Data[0]>>4;//后右中
	pRadarData->LRM_Distance = pRxMessage->Data[0]&0x0f;//后左中

	pRadarData->RRC_Distance = pRxMessage->Data[1]>>4;//后右角
	pRadarData->LRC_Distance = pRxMessage->Data[1]&0x0f;//后左角
	
	pRadarData->RFC_Distance = pRxMessage->Data[2]>>4;//前右角
	pRadarData->LFC_Distance = pRxMessage->Data[2]&0x0f;//前左角

	
	//pRadarData->LFM_Distance = pRxMessage->Data[3]>>4;//前左中
	//pRadarData->RFM_Distance = pRxMessage->Data[3]&0x0f;//前右中
	pRadarData->LFM_Distance = 0x00;//前左中  //R103-H15T只有6个雷达....
	pRadarData->RFM_Distance = 0x00;//前右中
	
	pRadarData->LRS_Distance = 0x00;//8个雷达与12个雷达共用一条协议所以要清零
    pRadarData->RRS_Distance = 0x00;
	   
	pRadarData->RFS_Distance = 0x00;   
	pRadarData->LFS_Distance = 0x00;   

	#if 0 
	//前左 前右 后右 后中右 后中左 后左
	TaskCAN_debug(_T("Six Radar Data:%d %d %d %d %d %d\n",pRadarData->LFC_Distance,pRadarData->RFC_Distance,
		pRadarData->RRC_Distance,pRadarData->RRM_Distance,pRadarData->LRM_Distance,pRadarData->LRC_Distance));
	#endif
	
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_RADAR_STATE, 1);	
}


#define SPEED_VALUE_H		(7*100000/5625)		/*7KM/H*/
#define SPEED_VALUE_L		(5*100000/5625)		/*5KM/H*/
#define SPEED_CNT			5
static void CANEspDataDeal(CanMsgStruct *pRxMessage)
{
	CarSpeedDataStruct *ptr=pCAN_GetVehicleSpeed();
	uint8_t speedH = 0;
	uint8_t speedL = 0;
	uint32_t speed = 0;
	uint8_t speedFlag = 0;//0:speed valid   1:speed not valid
	uint8_t UpdataFlag = 0;
	
	if(pRxMessage->CANMsgId == CAN_RXID_GW_320)//AT的车速信号
	{
		speedFlag = (pRxMessage->Data[1]&0x40) >> 6;

		if(!speedFlag)
		{
			speedH = pRxMessage->Data[1]&0x1f;
			speedL = pRxMessage->Data[2];
			speed = (speedH<<8)|speedL;
		}
		else //车速无效
		{
			sCANModule.SpeedCnt = 0;
			return;
		}
	}
	else   //MT的车速信号
	{
		speedFlag = (pRxMessage->Data[4]&0x20) >> 5;
		if(!speedFlag)
		{
			speedH = pRxMessage->Data[4]&0x1f;
			speedL = pRxMessage->Data[5];
			speed = (speedH<<8)|speedL;
		}
		else
		{
			sCANModule.SpeedCnt = 0;
			return;
		}
	}

	
	if(sCANModule.DisVideo==1)
	{
		if(speed<=SPEED_VALUE_L)
		{
			sCANModule.SpeedCnt++;
			if(sCANModule.SpeedCnt>=SPEED_CNT)
			{
				sCANModule.DisVideo = 0;
				UpdataFlag = 1;
			}
		}
		else
			sCANModule.SpeedCnt = 0;
	}
	else if(sCANModule.DisVideo==0)
	{
		if(speed>=SPEED_VALUE_H)
		{
			sCANModule.SpeedCnt++;
			if(sCANModule.SpeedCnt>=SPEED_CNT)
			{
				sCANModule.DisVideo = 1;
				UpdataFlag = 1;
			}
		}
		else
			sCANModule.SpeedCnt = 0;
	}
	else if(sCANModule.DisVideo == 3)
	{
		UpdataFlag = 1;
		if(speed<SPEED_VALUE_H)
			sCANModule.DisVideo = 0;
		else
			sCANModule.DisVideo = 1;
	}

	//TaskCAN_debug(_T("sCANModule.DisVideo = %d,UpdataFlag = %d\n",sCANModule.DisVideo,UpdataFlag));

	speed  =(int) (speed*0.05625+0.5);//keilee20140803
	speedH = (speed>>8)&0xff;
	speedL = speed&0xff;
	ptr->SpeedHbyte = speedH;
	ptr->SpeedLbyte = speedL;
	if(1 == UpdataFlag)
	{
		if(0==sCANModule.DisVideo)
		{
			g_tMcuDevState.uDetect.bits.VideoDisable = 0;
		}
		else if(1==sCANModule.DisVideo)
		{
			g_tMcuDevState.uDetect.bits.VideoDisable = 1;
		}

		TaskCAN_debug(_T("-------speed:%ld KM\n",speed));
		TaskCAN_debug(_T("--------VideoDisable:%d\n",g_tMcuDevState.uDetect.bits.VideoDisable));

		_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);			
	}
}
#undef SPEED_VALUE_H
#undef SPEED_VALUE_L
#undef SPEED_CNT

static void CANLCMDataDeal(CanMsgStruct *pRxMessage)
{
	uint8_t CanBackLightLevel = 0;
	uint8_t Lightness;
	uint8_t RearAutoFold;
	uint8_t driveLight;
	
	CarLightDataStruct *point = pCAN_GetCarLightData();
	CarRMirrorDataStruct *pMirror=pCAN_GetRearMirrorData();

	//氛围灯亮度
	 Lightness=((pRxMessage->Data[0]>>2)&0x07)-1;
	 Lightness<<=2;
	 if(Lightness!=(point->lightness))
	 {
	 	point->lightness = Lightness;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_LIGHT, 1);
	 }

	//日间行车灯
	driveLight = (pRxMessage->Data[0])&0x03;
	if(driveLight != point->DriveLightEnable)
	{
		point->DriveLightEnable = driveLight;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_LIGHT, 1);
	}
	
	//后视镜自动折叠
	RearAutoFold=(pRxMessage->Data[1]&0x03);
	if(RearAutoFold!=(pMirror->RearAutoFold))
	{
		pMirror->RearAutoFold = RearAutoFold;
		CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_RMIRROR, 1);
	}
	
	//亮度调节
	 if(0==g_tSysRomData.uGenBlock.tBlock.tFlag3.bAuto_Dimmer_Set)
	 {
		return;
	 }
	 CanBackLightLevel = pRxMessage->Data[1]>>3;
	 ID5F0BLMCnt++;
	 if((CanBackLightLevel==g_BKAutoLevel)&&(20>ID5F0BLMCnt))
	 {	 	
	 	return;
	 }
	 else
	 {
	 	TaskCAN_debug(_T("===CANLCMDataDeal g_BKAutoLevel=%d\n",g_BKAutoLevel));
		ID5F0BLMCnt = 0;
		 g_BKAutoLevel = CanBackLightLevel;
		 if(0==CanBackLightLevel)//小灯关
		 { 
			g_tMcuDevState.uIOState.bits.Illumi_On = 0;
		 }
		 else//小灯开
		 {  
			g_tMcuDevState.uIOState.bits.Illumi_On = 1;	
		 }
		 g_tSysRomData.tScrBlock.cBaseBR= g_BKAutoLevel;
		 _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);//告知os小灯变化
		 //_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SCREENSETTING,&(g_tSysRomData.tScrBlock));//告知os亮度等级
		_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);//调节亮度
	 }
}

static void CANIGNDataDeal(CanMsgStruct *pRxMessage)
{
    	uint8_t state1 = 0;
	CarECOInfoStruct *pECO = pCAN_GetVehicleECOData();

	if(pRxMessage->CANMsgDlc!=8)
	{
		return;
	}

	state1 = pRxMessage->Data[0] &0x30;
	state1 = state1>>4;
	if(state1 == 0x02)//开启发动机
	{
		pECO->EngineStatus=1;
	}
	else
	{
		pECO->EngineStatus=0;
	}
}

static void CANRearWiperDeal(CanMsgStruct *pRxMessage)
{
    	uint8_t state1 = 0;
	CarWiperDataStruct *pWiper = pCAN_GetCarWiperData();
	CarLightDataStruct* pLight = pCAN_GetCarLightData();
	CarDoorLockDataStruct* pDoorLock = pCAN_GetCarDoorLockData();

	if(pRxMessage->CANMsgDlc!=8)
	{
		return;
	}
	if(pRxMessage->Data[0]>>6==0x01)
	pWiper->	RearWiper = 0;
	if(pRxMessage->Data[0]>>6==0x02)
	pWiper->	RearWiper = 1;
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_WIPER, 1);

	pLight->lightOffDelay = (pRxMessage->Data[1])&0x07;
	pLight->lightBlinkTime = (pRxMessage->Data[2])&0x07;
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_CAR_LIGHT, 1);

	pDoorLock->DoorOpenMode = ((pRxMessage->Data[0])&0x30) >>4;
	pDoorLock->DriveLock = (pRxMessage->Data[0])&0x03;
	pDoorLock->ParkUnlock = ((pRxMessage->Data[0])&0x0c)>>2;
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_DOOR_LOCK_INFO, 1);
	
	
}


static void CANTotalOdoMeterDeal(CanMsgStruct *pRxMessage)
{
	
}



static void CANGMRadarDeal(CanMsgStruct *pRxMessage)
{
      RadarStatusDataStruct *pRadarData =pCAN_GetRadarStatusData();
      if(pRxMessage->CANMsgDlc!=8)
	{
		return;
	}
       pRadarData->RRM_Distance = pRxMessage->Data[0]>>4;//后右中
	pRadarData->LRM_Distance = pRxMessage->Data[0]&0x0f;//后左中

	pRadarData->RRC_Distance = pRxMessage->Data[1]>>4;//后右角
	pRadarData->LRC_Distance = pRxMessage->Data[1]&0x0f;//后左角
	
	pRadarData->RFC_Distance = pRxMessage->Data[2]>>4;//前右角
	pRadarData->LFC_Distance = pRxMessage->Data[2]&0x0f;//前左角

	pRadarData->LFM_Distance = pRxMessage->Data[3]>>4;//前左中
	pRadarData->RFM_Distance = pRxMessage->Data[3]&0x0f;//前右中


	pRadarData->LRS_Distance =pRxMessage->Data[6]>>5;      //左后侧
	pRadarData->RRS_Distance =( pRxMessage->Data[4]>>3)&0x07;//右后侧

       pRadarData->LFS_Distance =pRxMessage->Data[7]&0x07;        //左前侧
	pRadarData->RFS_Distance =(pRxMessage->Data[6]>>2)&0x07;//右前侧
	
	

	//TaskCAN_debug(_T("===pRadarData %d,%d,%d,",pRadarData->LRM_Distance,pRadarData->RRM_Distance,pRadarData->LRC_Distance);
	//TaskCAN_debug(_T("%d,%d,%d\n",pRadarData->RRC_Distance,pRadarData->LFC_Distance,pRadarData->RFC_Distance);
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_RADAR_STATE, 1);	


}


void CANUser_ReceiveCANMsgHandler(CanMsgStruct *pRxMsg)
{
#ifdef CAN_BODY_ENABLE
	if(pRxMsg->CAN_Id == CAN_ID_BODY)
	{
		switch(pRxMsg->CANMsgId)
		{		      
			case CAN_RXID_TEST:
				CANRxTestDataDeal(pRxMsg);
				break;
				
			//S401
			case CAN_RXID_BCM_349:
				CANBcm349Deal(pRxMsg);
				break;
				
			case CAN_RXID_DSM_352:
				CANBcm352Deal(pRxMsg);//后视镜设置反馈
				break;
				
			case CAN_RXID_DSM_340:
				TaskCAN_debug(_T("----CAN_RXID_DSM_340----\n"));
				CANBcm340Deal(pRxMsg);
				break;
				
			case CAN_RXID_DSM_330:
				CANBcm330Deal(pRxMsg);
				break;
				
			case CAN_RXID_DVR_612:
				//TaskCAN_debug(_T("=====CAN_RXID_DVR_612=====\n"));
			#if (PROJECT_CODE == CHANGAN_S401)
				CANRxDvrDataDeal(pRxMsg);//S401
			#elif (PROJECT_CODE == CHANGAN_R103_H15T)
				CANDvr612Deal(pRxMsg);//R103-H15T
			#endif
				break;
			case CAN_RXID_FACTORY_TEST_001:
				CANRxFactoryTestDeal(pRxMsg);
				break;
					
			case CAN_RXID_AVM_3E0:	
				CANAvmDataDeal(pRxMsg);
				break;
				
			case CAN_RXID_BCM_288:
				CANBcm288Deal(pRxMsg);
				break;
				
			case CAN_RXID_PEPS_266:
				CANPEPSDataDeal(pRxMsg);
				break;
				
			case CAN_RXID_RRS_2E0:
				CANRadarDataDeal(pRxMsg);
				break;
				
			/*case CAN_RXID_ESP_320:
				CANEspDataDeal(pRxMsg);
				break;
			*/
			
			case CAN_RXID_LCM_5F0:
				CANLCMDataDeal(pRxMsg);
				break;
				
			case CAN_RXID_IGN_2B0:
				CANIGNDataDeal(pRxMsg);
				break;

			case CAN_RXID_BCM_5FF:
				CANRearWiperDeal(pRxMsg);
				break;
				
			case CAN_RXID_IP_380:
				CANFuelLevelDeal(pRxMsg);
				CANTotalOdoMeterDeal(pRxMsg);
				break;

			case CAN_RXID_GW_2FF:
				CANGMRadarDeal(pRxMsg);
				break;
			//R103-H15T
			case CAN_RXID_BCM_347:
				//TaskCAN_debug(_T("=====CAN_RXID_BCM_347=====\n"));
				CANBcm347Deal(pRxMsg);
				break;
			case CAN_RXID_DVR_613:
				//TaskCAN_debug(_T("=====CAN_RXID_DVR_613=====\n"));
				CANDvr613Deal(pRxMsg);
				break;	
			case CAN_RXID_ESP_218://AT车速信号  snake20161028add
			case CAN_RXID_GW_320://MT车速信号
				CANEspDataDeal(pRxMsg);
				break;
		}
	}
#endif

#ifdef CAN_INNER_ENABLE
	if(pRxMsg->CAN_Id == CAN_ID_INNER)
	{
		switch(pRxMsg->CANMsgId)
		{
			case CAN_RXID_INNER_TEST:
				CANRxTestDataDeal(pRxMsg);
				break;
				
			case CAN_RXID_INNER_LRHD_0:
			case CAN_RXID_INNER_RRHD_0:
			case CAN_RXID_INNER_LRHD_1:
			case CAN_RXID_INNER_RRHD_1:
				CANbus_InnerRHDHandler(pRxMsg);
				break;
				
			case CAN_RXID_INNER_FCP:
				CANbus_InnerFCPHandler(pRxMsg);
				break;
				
			case CAN_RXID_INNER_DTV_0:
			case CAN_RXID_INNER_DTV_CAST:
			case CAN_RXID_INNER_DTV_LIST:
			case CAN_RXID_INNER_DTV_CA:
			case CAN_RXID_INNER_DTV_VER:
				CANbus_InnerDTVHandler(pRxMsg);
				break;
				
		}
	}
#endif
}













/********************************************************/
/*********************空调控制设置*****************/
/********************************************************/
void CANUser_SetACWindTemp(uint8_t *pMsg, uint8_t len)
{//温度设置
	uint8_t temp = 0x00;
	FrontACDataStruct *FrontData=pCAN_GetFrontACData();
	RearACDataStruct  *RearData = pCAN_GetRearACData();
	switch(pMsg[0])//主驾、副驾、后排
	{	//主驾
		case OP_CAN_RX_FLAC_TEMP_ADJ:
				if(pMsg[1]==0xfd)
			{
				temp = 0x1f;
			}
			else if(pMsg[1]==0xfe)
			{
				temp = 0x01;
			}
			else if(pMsg[1]==0xfb)
			{
				temp = 0x20;
			}
			else if(pMsg[1]==0xfc)
			{
				temp = 0x21;//18到32度
			}
			else
			{
				temp = pMsg[1];
			}
			Body2F9Buff[1]=temp;//低6位为有效位
			break;
			
		case OP_CAN_RX_ACR_FLAC_TEMP_ADJ:
			Body2F9Buff[1]=pMsg[1];//低6位为有效位
			break;
			
		//副驾
		case OP_CAN_RX_FRAC_TEMP_ADJ:
			if(pMsg[1]==0xfb)
			{
				temp = 0x01;
			}
			if(pMsg[1]==0xfc)
			{
				temp = 0x02;
			}
			temp <<= 6;//转换到7、8位
			Body2F9Buff[1]=temp;
			break;
			
		//后排
		case OP_CAN_RX_RAC_TEMP_ADJ:
			if(pMsg[1]==0xfb)
			{
				temp = 0x01;
			}
			if(pMsg[1]==0xfc)
			{
				temp = 0x02;
			}
			temp <<= 4;//转换到4、5位
			Body2F9Buff[3]=temp;
			break;
	}
	
	Body2F9Buff[5]&=0b10011111;
	if(pMsg[0]==OP_CAN_RX_ACR_FLAC_TEMP_ADJ)
		Body2F9Buff[5]|=0x40;//voice
	else
		Body2F9Buff[5]|=0x20;//touch
	
	//TaskCAN_debug(_T("CANUser_SetACWindTemp"));
	ID2F9CanMsgSendFlag = 1;
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
}

void CANUser_SetACWindMode(uint8_t *pMsg, uint8_t len)
{//出风模式
	uint8_t temp = 0;

	if(pMsg[0]==OP_CAN_RX_ACR_FAC_WIND_MODE)
	{
		Body2F9Buff[2]=pMsg[1];
		Body2F9Buff[5]&=0b10011111;
		Body2F9Buff[5]|=0x40;//voice
	}
	else
	{
		if(pMsg[0]==OP_CAN_RX_FAC_WIND_MODE)//前排吹风模式
		{
			if(pMsg[1]==0x05)//MODE
			{
				temp = 0x05;
			}
			Body2F9Buff[2]=temp;
		}
		
		if(pMsg[0]==OP_CAN_RX_RAC_WIND_MODE)//后排吹风模式
		{
			if(pMsg[1]==0x04)//MODE
			{
				temp = 0x04;
			}
			Body2F9Buff[5]=temp;
		}

		Body2F9Buff[5]&=0b10011111;
		Body2F9Buff[5]|=0x20;//touch
	}

	ID2F9CanMsgSendFlag = 1;
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
}

void CANUser_SetACWindLevel(uint8_t *pMsg, uint8_t len)
{//风量调节
	FrontACDataStruct *FrontData=pCAN_GetFrontACData();
	uint8_t temp = 0;
	if(pMsg[0]==OP_CAN_RX_ACR_FAC_WIND_LEVEL_ADJ)
	{
		Body2F9Buff[2]=pMsg[1]<<4;
		Body2F9Buff[5]&=0b10011111;
		Body2F9Buff[5]|=0x40;//voice
	}
	else
	{
		if(pMsg[1]==0x00)//decrease
		{
			temp = 0x0a;
		}
		if(pMsg[1]==0x01)//increase
		{
			temp = 0x09;
		}
		if(pMsg[1]>=0x02)//风速等级
		{
			temp=pMsg[1]-1;
		}
		
		if(pMsg[0]==OP_CAN_RX_FAC_WIND_LEVEL_ADJ)//前排风量调节
		{
			temp<<=4;
			Body2F9Buff[2]|=temp;
		}
		if(pMsg[0]==OP_CAN_RX_RAC_WIND_LEVEL_ADJ)//后排风量调节
		{
			Body2F9Buff[3]=temp;
		}
		
		Body2F9Buff[5]&=0b10011111;
		Body2F9Buff[5]|=0x20;//touch
	}

//	if((FrontData->WindLevel != 0)&&(pMsg[1]!=0x00))
	{
		ID2F9CanMsgSendFlag = 1;
		CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);

	}
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	//CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
//	memset(Body2F9Buff,0,8);
}

void CANUser_SetACAuto(uint8_t *pMsg, uint8_t len)
{//AUTO 设置
	uint8_t temp = 0;
	if(pMsg[1]==0x01)//Auto On
	{
		temp=1;
	}
	if(pMsg[0]==OP_CAN_RX_ACF_AUTO_SET)//前自动
	{
		temp<<=6;
		Body2F9Buff[0]=temp;
	}
	if(pMsg[0]==OP_CAN_RX_ACR_AUTO_SET)//后自动
	{
		Body2F9Buff[0]=temp;
	}
	
	Body2F9Buff[5]&=0b10011111;
	Body2F9Buff[5]|=0x20;//touch
	
	ID2F9CanMsgSendFlag = 1;
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
}

void CANUser_SetACRefrigeration(uint8_t *pMsg, uint8_t len)
{//制冷开关
	if(pMsg[1]==0x01)//A/c On
	{
		Body2F9Buff[4]=0x04;//0b00000100
	}
	
	Body2F9Buff[5]&=0b10011111;
	Body2F9Buff[5]|=0x20;//touch
	
	ID2F9CanMsgSendFlag = 1;
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
}

void CANUser_SetACCircleMode(uint8_t *pMsg, uint8_t len)
{//循环模式, 此协议APU->MCU是直接用的CAN 协议指令
	uint8_t temp = 0;
	if(pMsg[0]==OP_CAN_RX_ACR_AC_CIRCLE_MODE)
	{
		Body2F9Buff[4]=pMsg[1]<<4;
		Body2F9Buff[5]&=0b10011111;
		Body2F9Buff[5]|=0x40;//voice
	}
	else
	{
		temp = pMsg[1];
		temp<<=4;
		Body2F9Buff[4]=temp;
		Body2F9Buff[5]&=0b10011111;
		Body2F9Buff[5]|=0x20;//touch
	}
	
	ID2F9CanMsgSendFlag = 1;
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
}

void CANUser_SetACWindRegion(uint8_t *pMsg, uint8_t len)
{//风区设置SYNC
	if(pMsg[1]==0x01)//AC SYNC ON , 返回4 种模式CS95
	{
		Body2F9Buff[4]=0x01;//0b00000011
	}
	
	Body2F9Buff[5]&=0b10011111;
	Body2F9Buff[5]|=0x20;//touch
	
	ID2F9CanMsgSendFlag = 1;
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
}

void CANUser_SetACDefrost(uint8_t *pMsg, uint8_t len)
{//除霜设置
	FrontACDataStruct *FrontData=pCAN_GetFrontACData();
	uint8_t temp = 0;
	if(pMsg[0]==OP_CAN_RX_ACR_AC_FRONT_DEFROST)//前除霜
	{
			Body2F9Buff[0]=pMsg[1]<<2;
			Body2F9Buff[5]&=0b10011111;
			Body2F9Buff[5]|=0x40;//voice
	}
	else
	{
		if(pMsg[1] == 0x03)	// DERROST Off
		{
			temp = 3;
		}
		if(pMsg[0]==OP_CAN_RX_AC_FRONT_DEFROST)//前除霜
		{
			temp<<=2;
			Body2F9Buff[0]=temp;
		
			Body2F9Buff[5]&=0b10011111;
			Body2F9Buff[5]|=0x20;//touch
		}
		if(pMsg[0]==OP_CAN_RX_AC_REAR_DEFROST)//后除霜
		{//BCM上
			temp<<=3;
			Body2F9Buff[5]=temp;
			
			Body2F9Buff[5]&=0b10011111;
			Body2F9Buff[5]|=0x20;//touch
		}
	}
	ID2F9CanMsgSendFlag = 1;
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
}

void CANUser_SetACSwitch(uint8_t *pMsg, uint8_t len)
{//前后空调开关
	uint8_t temp = 0;
	if(pMsg[0]==OP_CAN_RX_ACR_FAC_SWITCH)//pMsg[0]语音触屏标示
	{
		if(pMsg[1]==0x01)//语音开启
		{
			temp=1;
			temp<<=6;
			Body2F9Buff[0]=temp;
		}
		if(pMsg[1]==0x00)//语音关闭
		{
			temp=1;
			temp<<=4;//0b11001111
			Body2F9Buff[0]=temp;
		}
		Body2F9Buff[5]&=0b10011111;
		Body2F9Buff[5]|=0x40;//voice
	}
	else
	{
		if(pMsg[1]==0x00)//触屏关闭
		{
			temp=1;
		}
		if(pMsg[0]==OP_CAN_RX_FAC_SWITCH)//前开关
		{
			temp<<=4;//0b11001111
			Body2F9Buff[0]=temp;
		}
		if(pMsg[0]==OP_CAN_RX_RAC_SWITCH)//后开关
		{
			temp<<=6;//0b00111111
			Body2F9Buff[3]=temp;
		}
		Body2F9Buff[5]&=0b10011111;
		Body2F9Buff[5]|=0x20;//touch
	}
	
	ID2F9CanMsgSendFlag = 1;
//	CANUser_SetBodyCanMsgOnce(Body2F9Buff, CAN_TX_ID2F9);
	CANUser_SetBodyCanMsgPeriodic(Body2F9Buff, CAN_TX_ID2F9, TIMER_100MS);
}

void CANUser_SetAcReset(uint8_t *pMsg, uint8_t len)
{//进入APP请求数据
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_REAR,  1);
	CANTask_SendApiData(OMS_CAN_TX_CAR,OP_CAN_TX_AC_FRONT, 1);
}







/********************************************************/
/********************车辆设置部分******************/
/********************************************************/
//氛围灯设置
void CANUser_SetAtmospher(uint8_t *pMsg, uint8_t len)
{
	uint8_t Colour=0, Bright=0;
	//颜色设置
	if(pMsg[1]==0x00)//关闭氛围灯
	{
		;
	}
	if(pMsg[1]==0x0f)//打开氛围灯
	{
		;
	}
	if(pMsg[1]>=0x01 && pMsg[1]<=0x07)//颜色设置
	{
		Colour=pMsg[1];
	}
	
	//亮度设置
	if(pMsg[1]==0xF0)//关闭
	{
		Bright=0;
	}
	if((pMsg[1] >= 0xF1) && (pMsg[1] <= 0xF6))//亮度设置L11~L16
	{
		Bright=pMsg[1]-0xF0+1;
	}
	
	//按照协议移位存放
	Body600Buff[6]&=0x03;//0b11111100 清除Bright和Colour 数据段
	Body600Buff[6]|=(Bright <<5);
	Body600Buff[6]|=(Colour<<2);
	CANUser_SetBodyCanMsgOnce(Body600Buff, CAN_TX_ID600);
}

//后视镜后设置
void CANUser_SetMirrorState(uint8_t *pMsg, uint8_t len)
{
	CarPEPSDataStruct *pData = pCAN_GetPEPSData();
	//if(pMsg[0]==OP_CAN_RX_VEHICLE_RMIR_LEFT)
	{
		uint8_t temp = 0;
		if(pMsg[1]==0x06)
		{//倒车辅助打开
			Body600Buff[7]&=0xFC;//0b11111100
			Body600Buff[7]|=0x02;
		}
		if(pMsg[1]==0x07)
		{//倒车辅助关闭
			Body600Buff[7]&=0xFC;//0b11111100
			Body600Buff[7]|=0x01;
		}
		
		if(pMsg[1]==0x08)
		{//自动折叠打开
			Body600Buff[5]&=0x3F;//0b00111111
			Body600Buff[5]|=0x80;
		}
		if(pMsg[1]==0x09)
		{//自动折叠关闭
			Body600Buff[5]&=0x3F;//0b00111111
			Body600Buff[5]|=0x40;
		}
	}
	CANUser_SetBodyCanMsgOnce(Body600Buff, CAN_TX_ID600);
}

//座椅礼让设置
void CANUser_SetSeatState(uint8_t *pMsg, uint8_t len)
{
	uint8_t temp = 0;
	if(pMsg[1]==0x01)//0b00111111 off
	{
		temp = 0x01;
	}
	if(pMsg[1]==0x02)//0b00111111 On
	{
		temp = 0x02;
	}
	
	Body600Buff[1]&=0x3F;//0b00111111
	temp <<= 6;
	Body600Buff[1]|=temp;
	CANUser_SetBodyCanMsgOnce(Body600Buff, CAN_TX_ID600);
}


//后雨刮设置
void CANUser_WiperDeal(uint8_t *pMsg, uint8_t len)
{
	uint8_t temp = 0;
	if(pMsg[1]==0x00)//0b00111111 off
	{
		temp = 0x01;
	}
	if(pMsg[1]==0x01)//0b00111111 On
	{
		temp = 0x02;
	}
	
	Body600Buff[4]&=0x3F;//0b00111111
	temp <<= 6;
	Body600Buff[4]|=temp;
	CANUser_SetBodyCanMsgOnce(Body600Buff, CAN_TX_ID600);
}



//恢复车辆设置BOLTE
void CANUser_SetRecover(uint8_t *pMsg, uint8_t len) //
{
	uint8_t i,temp = 0;

	//后视镜倒车辅助默认开
	Body600Buff[7]&=0xFC;//0b11111100
	Body600Buff[7]|=0x02;

	//后视镜自动折叠默认开
	Body600Buff[5]&=0x3F;//0b00111111
	Body600Buff[5]|=0x80;

	//座椅礼让设置默认打开
	Body600Buff[1]&=0x3F;//0b00111111
	Body600Buff[1]|=0x80;

	//后雨刮设置默认打开
	Body600Buff[4]&=0x3F;//0b00111111
	Body600Buff[4]|=0x80;

	//氛围灯
	Body600Buff[6] = 0x40;	// 氛围灯默认值LEVEL1
	CANUser_SetBodyCanMsgOnce(Body600Buff, CAN_TX_ID600);

	API_LoopDleay(60000);	//需要有一定时间间隔才能连续发送两帧
	
	//车灯
	Body601Buff[1] &= 0xF8;
	Body601Buff[1] |= 0x02;	//跟随灯光回家默认值2
	
	Body601Buff[1] &= 0xC7;
	Body601Buff[1] |= 0x08;	//变道闪光次数默认1

	Body601Buff[0] &= 0xFC;
	Body601Buff[0] |= 0x01;	//日间行车灯默认关

	//门锁
	Body601Buff[0] &= 0xF3;
//	Body601Buff[0] |= 0x01	//行车自动落锁

	Body601Buff[0] &= 0xCF;
//	Body601Buff[0] |= 0x01	//熄火自动解锁

	Body601Buff[0] &= 0x3F;
	Body601Buff[0] |= 0x40;	//遥控解锁模式
	CANUser_SetBodyCanMsgOnce(Body601Buff, CAN_TX_ID601);

#ifdef D_CAN_VEHICLE_SET_STORE_IN_EEPROM
	CANbus_VehicleVariableReset();//本地记忆变量复位
	CAN_VehicleEepStore();	//记入EEPROM
	CANUser_VehicleOsVaribleReset();	//发送OS的数据复位
	memset(Body513Buff,0,8);		
	CAN_Get_Body513Data();		//总线数据发送的数据复位
	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
#endif
	
}


//导航信息设置
void CANUser_SetNaviInfo(uint8_t *pMsg, uint8_t len)
{
	uint16_t NaviCode = 0, TempCode = 0;
	TempCode=pMsg[1];
	TempCode<<=8;
	TempCode|=pMsg[0];
	
	if(TempCode==1)
	{
		NaviCode = 1;
	}
	else if((TempCode>=2)&&(TempCode<=3))
	{
		NaviCode = 2;
	}
	else if((TempCode>=5)&&(TempCode<=6))
	{
		NaviCode = 3;
	}
	else if(TempCode==7)
	{
		NaviCode = 4;
	}
	else if(TempCode==9)
	{
		NaviCode = 5;
	}
	else if((TempCode>=306)&&(TempCode<=310))
	{
		NaviCode = pMsg[0]-300;
	}
	else if((TempCode>=11)&&(TempCode<=14))
	{
		NaviCode = pMsg[0];
	}
	else if((TempCode>=15)&&(TempCode<=16))
	{
		NaviCode = 15;
	}
	else if((TempCode==10 )||(TempCode==17  )||(TempCode==20  )||(TempCode==116)||(TempCode==187)||
	           (TempCode==282)||(TempCode==294)||(TempCode==321)||(TempCode==322))
	{
		NaviCode = 16;
	}
	else if((TempCode==21 )||(TempCode==36  )||(TempCode==79  )||(TempCode==100)||(TempCode==115)||
	           (TempCode==117)||(TempCode==120)||(TempCode==128)||(TempCode==130)||(TempCode==149)||
	           (TempCode==150)||(TempCode==167)||(TempCode==169)||(TempCode==186)||(TempCode==188)||
	           (TempCode==193)||(TempCode==208)||(TempCode==281)||(TempCode==283)||(TempCode==293)||
	           (TempCode==295)||(TempCode==305)||(TempCode==319)||(TempCode==320)||(TempCode==325)||
	           (TempCode==326))
	{
		NaviCode = 17;
	}
	else if((TempCode==28 )||(TempCode==35  )||(TempCode==78  )||(TempCode==99  )||(TempCode==114)||
	           (TempCode==118)||(TempCode==119)||(TempCode==127)||(TempCode==129)||(TempCode==148)||
	           (TempCode==151)||(TempCode==152)||(TempCode==166)||(TempCode==168)||(TempCode==185)||
	           (TempCode==189)||(TempCode==192)||(TempCode==207)||(TempCode==279)||(TempCode==290)||
	           (TempCode==291)||(TempCode==302)||(TempCode==303)||(TempCode==317)||(TempCode==318)||
	           (TempCode==323)||(TempCode==324))
	{
		NaviCode = 18;
	}
	else if((TempCode==27 )||(TempCode==37  )||(TempCode==38  )||(TempCode==63  )||(TempCode==64)||
	           (TempCode==65)||(TempCode==85)||(TempCode==123)||(TempCode==133)||(TempCode==172)||
	           (TempCode==194)||(TempCode==209)||(TempCode==210)||(TempCode==289)||(TempCode==301))
	{
		NaviCode = 19;
	}
	else if((TempCode==22 )||(TempCode==39  )||(TempCode==40  )||(TempCode==60  )||(TempCode==61)||
	           (TempCode==62)||(TempCode==80)||(TempCode==124)||(TempCode==134)||(TempCode==173)||
	           (TempCode==195)||(TempCode==211)||(TempCode==212)||(TempCode==284)||(TempCode==296))
	{
		NaviCode = 20;
	}
	else if((TempCode==26 )||(TempCode==41  )||(TempCode==42  )||(TempCode==69  )||(TempCode==70)||
	           (TempCode==71)||(TempCode==84)||(TempCode==213)||(TempCode==214)||(TempCode==288)||
	           (TempCode==300))
	{
		NaviCode = 21;
	}
	else if((TempCode==23 )||(TempCode==43  )||(TempCode==44  )||(TempCode==66  )||(TempCode==67)||
	           (TempCode==68)||(TempCode==81)||(TempCode==215)||(TempCode==216)||(TempCode==285)||
	           (TempCode==297))
	{
		NaviCode = 22;
	}
	else if((TempCode==25 )||(TempCode==45  )||(TempCode==46  )||(TempCode==75  )||(TempCode==76)||
	           (TempCode==77)||(TempCode==83)||(TempCode==125)||(TempCode==135)||(TempCode==174)||
	           (TempCode==196)||(TempCode==217)||(TempCode==218)||(TempCode==287)||(TempCode==299))
	{
		NaviCode = 23;
	}
	else if((TempCode==24 )||(TempCode==47  )||(TempCode==48  )||(TempCode==72  )||(TempCode==73)||
	           (TempCode==74)||(TempCode==82)||(TempCode==126)||(TempCode==136)||(TempCode==175)||
	           (TempCode==197)||(TempCode==219)||(TempCode==220)||(TempCode==286)||(TempCode==298))
	{
		NaviCode = 24;
	}
	else if((TempCode==58 )||(TempCode==97  )||(TempCode==112  )||(TempCode==121  )||(TempCode==131)||
	           (TempCode==155)||(TempCode==170))
	{
		NaviCode = 25;
	}
	else if((TempCode==59 )||(TempCode==98  )||(TempCode==113  )||(TempCode==122  )||(TempCode==132)||
	           (TempCode==156)||(TempCode==171))
	{
		NaviCode = 26;
	}
	else if((TempCode==33 )||(TempCode==313  )||(TempCode==314  ))
	{
		NaviCode = 27;
	}
	else if((TempCode==34 )||(TempCode==315  )||(TempCode==316  ))
	{
		NaviCode = 28;
	}
	else if((TempCode==29 )||(TempCode==86  )||(TempCode==101  )||(TempCode==137  )||(TempCode==153)||
	           (TempCode==190)||(TempCode==221)||(TempCode==311))
	{
		NaviCode = 29;
	}
	else if((TempCode==30 )||(TempCode==87  )||(TempCode==102  )||(TempCode==138  )||(TempCode==154)||
	           (TempCode==191)||(TempCode==222)||(TempCode==312))
	{
		NaviCode = 30;
	}
	else if((TempCode==55 )||(TempCode==94  )||(TempCode==109  )||(TempCode==145  )||(TempCode==163)||
	           (TempCode==182)||(TempCode==204)||(TempCode==229))
	{
		NaviCode = 31;
	}
	else if((TempCode==57 )||(TempCode==96  )||(TempCode==111  )||(TempCode==147  )||(TempCode==165)||
	           (TempCode==184)||(TempCode==206)||(TempCode==231))
	{
		NaviCode = 32;
	}
	else if((TempCode==56 )||(TempCode==95  )||(TempCode==110  )||(TempCode==146  )||(TempCode==164)||
	           (TempCode==183)||(TempCode==205)||(TempCode==230)||(TempCode==234)||(TempCode==280)||(TempCode==292)||(TempCode==304))
	{
		NaviCode = 33;
	}
	else if((TempCode==49 )||(TempCode==88  )||(TempCode==103  )||(TempCode==139  )||(TempCode==157)||
	           (TempCode==176)||(TempCode==198)||(TempCode==223))
	{
		NaviCode = 34;
	}
	else if((TempCode==54 )||(TempCode==93  )||(TempCode==108  )||(TempCode==144  )||(TempCode==162)||
	           (TempCode==181)||(TempCode==203)||(TempCode==228))
	{
		NaviCode = 35;
	}
	else if((TempCode==50 )||(TempCode==89  )||(TempCode==104  )||(TempCode==140  )||(TempCode==158)||
	           (TempCode==177)||(TempCode==199)||(TempCode==224)||(TempCode==232))
	{
		NaviCode = 36;
	}
	else if((TempCode==53 )||(TempCode==92  )||(TempCode==107  )||(TempCode==143  )||(TempCode==161)||
	           (TempCode==180)||(TempCode==202)||(TempCode==227)||(TempCode==233))
	{
		NaviCode = 37;
	}
	else if((TempCode==51 )||(TempCode==90  )||(TempCode==105  )||(TempCode==141  )||(TempCode==159)||
	           (TempCode==178)||(TempCode==200)||(TempCode==225))
	{
		NaviCode = 38;
	}
	else if((TempCode==52 )||(TempCode==91  )||(TempCode==106  )||(TempCode==142  )||(TempCode==160)||
	           (TempCode==179)||(TempCode==201)||(TempCode==226))
	{
		NaviCode = 39;
	}
	else if((TempCode==18 )||(TempCode==31  ))
	{
		NaviCode = 40;
	}
	else if((TempCode==19 )||(TempCode==32  ))
	{
		NaviCode = 41;
	}
	else if((TempCode>=235)&&(TempCode<=238))
	{
		NaviCode = 42;
	}
	else if((TempCode>=239)&&(TempCode<=242))
	{
		NaviCode = 43;
	}
	else if((TempCode>=243)&&(TempCode<=246))
	{
		NaviCode = 44;
	}
	else if((TempCode>=247)&&(TempCode<=250))
	{
		NaviCode = 45;
	}
	else if((TempCode>=251)&&(TempCode<=254))
	{
		NaviCode = 46;
	}
	else if((TempCode>=255)&&(TempCode<=258))
	{
		NaviCode = 47;
	}
	else if((TempCode>=259)&&(TempCode<=262))
	{
		NaviCode = 48;
	}
	else if((TempCode>=263)&&(TempCode<=266))
	{
		NaviCode = 49;
	}
	else if((TempCode>=267)&&(TempCode<=270))
	{
		NaviCode = 50;
	}
	else if((TempCode>=271)&&(TempCode<=274))
	{
		NaviCode = 51;
	}
	else if((TempCode>=275)&&(TempCode<=278))
	{
		NaviCode = 52;
	}
	else if(TempCode==327)
	{
		NaviCode = 53;
	}
	else if(TempCode==328)
	{
		NaviCode = 54;
	}

	Body2F8Buff[5] = NaviCode;//编号
	Body2F8Buff[4] = pMsg[2];
	Body2F8Buff[3] = pMsg[3];
	Body2F8Buff[2] = pMsg[4]&0x01;
	CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, TIMER_100MS);
}

void CANUser_SetLatitude(uint8_t *pMsg, uint8_t len)
{
	uint8_t temp;
	uint32_t Longitude = 0;//经度
	uint32_t Latitude = 0;//纬度

	//数据有效   有效,将此位清0...
	if(pMsg[8])//GPS有效
	{
		Body500Buff[0] = 0x00;
		GpsInfo.GpsValid = 0;

		temp =pMsg[0];
		if(temp>>7 == 1)
		{
			temp&=0x0f;
			temp|=0x10;//西经
			GpsInfo.LongitudeFlag = 1;
		}
		else
			GpsInfo.LongitudeFlag = 0;
		
		Body500Buff[0] = temp;//pMsg[1];//经度
		Body500Buff[1] = pMsg[1];
		Body500Buff[2] = pMsg[2];
		Body500Buff[3] = pMsg[3];

		temp =pMsg[4];
		if(temp>>7 == 1)
		{
			temp &= 0x0f;
			temp |= 0x08;
			GpsInfo.LatitudeFlag = 1;
		}
		else
			GpsInfo.LatitudeFlag = 0;
		
		Body500Buff[4] = temp;//pMsg[5];//纬度
		Body500Buff[5] = pMsg[5];
		Body500Buff[6] = pMsg[6];
		Body500Buff[7] = pMsg[7];
		
		GpsInfo.Longitude = (uint32_t)((pMsg[0]&0x0f) << 24 | pMsg[1] << 16 | pMsg[2] << 8 | pMsg[3]);
		GpsInfo.Latitude = (uint32_t)((pMsg[4]&0x0f) << 24 | pMsg[5] << 16 | pMsg[6] << 8 | pMsg[7]);
		
	}
	else
	{
		Body500Buff[0] |= 0x80;
		GpsInfo.GpsValid = 1;
	}
	
	#if 0
	TaskCAN_debug(_T("GpsValid = %d.....LatitudeFlag:%d  Longitude = %ld,LatitudeFlag:%d  Latitude = %ld\n",GpsInfo.GpsValid,
	GpsInfo.LongitudeFlag,GpsInfo.Longitude,GpsInfo.LatitudeFlag,GpsInfo.Latitude));
	TaskCAN_debug(_T("Longitude And Latitude Data:%x %x %x %x %x %x %x %x\n",pMsg[0],pMsg[1],pMsg[2],pMsg[3],pMsg[4],pMsg[5],pMsg[6],pMsg[7]));
	TaskCAN_debug(_T("Body500Buff Data:%x %x %x %x %x %x %x %x\n",Body500Buff[0],Body500Buff[1],
		Body500Buff[2],Body500Buff[3],Body500Buff[4],Body500Buff[5],Body500Buff[6],Body500Buff[7]));
	#endif
	
	CANUser_SetBodyCanMsgPeriodic(Body500Buff, CAN_TX_ID500, TIMER_1000MS);
}

void CANUser_SetNaviSpeedLimit(uint8_t *pMsg, uint8_t len)
{
#if 1//添加导航限速信息
	Body2FABuff[0] = pMsg[0];	// country code
	if(pMsg[1] < 11)
	{
		Body2FABuff[3] &= 0xF8;
		switch(pMsg[1])
		{
			case 0:
				Body2FABuff[3] |= 0x05;
				break;

			case 1:
			case 2:
				Body2FABuff[3] |= 0x04;
				break;

			case 3:
			case 4:
				Body2FABuff[3] |= 0x03;
				break;

			case 5:
			case 6:
			case 7:
				Body2FABuff[3] |= 0x02;
				break;
			case 8:
				Body2FABuff[3] |= 0x01;
				break;

			case 9:
			case 10:
				Body2FABuff[3] |= 0x00;
				break;
				
		}

#if 0		
		if(0 == pMsg[1])
		{
			Body2FABuff[3] &= 0xF8;
			Body2FABuff[3] |= 0x05;
		}
		Body2FABuff[3] = pMsg[1];	//road type
#endif		
	}
	Body2FABuff[1] = pMsg[2]/5;	//speed value 
	if(pMsg[3] <= 1)
	{
		Body2FABuff[2] &= 0xF3;
		Body2FABuff[2] |= (pMsg[3]<<2);	// speed limited status
	}
	
	if(pMsg[4] <= 2)
	{
		Body2FABuff[2] &= 0xCF;
		Body2FABuff[2] |= (pMsg[4]<<4);	// speed uint
	}
	if(0 == pMsg[5])
		Body2FABuff[3] &= 0x7F;			// navi status
	else
		Body2FABuff[3] |= 0x80;
	
	CANUser_SetBodyCanMsgPeriodic(Body2FABuff, CAN_TX_ID2FA, TIMER_100MS);
#endif

}
#ifdef CAN_API_CAR_MAINTAIN_EN
extern CarMaintainInfoStruct	CAN_CarMaintainState;
#endif

void CANUser_SetMaintainData(uint8_t *pMsg, uint8_t len)
{
	uint32_t i,data[4],MaintainTemp;
	
	MaintainTemp = 0;
	for(i = 0 ; i < 4 ; i++)
	{
		data[i] = pMsg[i];
		data[i] = (data[i] << (i*8));
		MaintainTemp += data[i];
	}

	CAN_CarMaintainState.SettingMileage = MaintainTemp;
	
}


void CANUser_SystemTime(uint8_t *pMsg, uint8_t len)
{
	uint16_t temp;
	memset(Body501Buff,0,8);
	
	temp  =pMsg[0];
	temp<<=8;
	temp|=pMsg[1];
	if(temp==1970)//data and time is inValid
	{
		Body501Buff[0] |= 0x80;
	}
	else
	{
		Body501Buff[0] &= 0x7f;
	
		Body501Buff[1] |= (temp-2013)<<4;//年
		Body501Buff[1] |=pMsg[2]; //月
		Body501Buff[2] =  pMsg[3];//日
		
		Body501Buff[3] =pMsg[4];//时
		Body501Buff[4] =pMsg[5];//分
		Body501Buff[5] =pMsg[6];//秒
	}
	CANUser_SetBodyCanMsgPeriodic(Body501Buff, CAN_TX_ID501, TIMER_1000MS);
	
	#if 0
	TaskCAN_debug(_T("System Data And Time:%ld-%d-%d  %d:%d:%d\n",temp,pMsg[2],pMsg[3],pMsg[4],pMsg[5],pMsg[6]));
	TaskCAN_debug(_T("Body501Buff Data:%x %x %x %x %x %x %x %x\n",Body501Buff[0],Body501Buff[1],
		Body501Buff[2],Body501Buff[3],Body501Buff[4],Body501Buff[5],Body501Buff[6],Body501Buff[7]));
	#endif
}





/********************************************************/
/********************外挂模块设置******************/
/********************************************************/
//外置功放设置
void CANUser_SetExtAmp(uint8_t *pMsg, uint8_t len)
{
	memset(InnerCanBuff, 0, 8);
	InnerCanBuff[0] = pMsg[1];
	InnerCanBuff[1] = pMsg[2];
	CANUser_SetInnerCanMsg(InnerCanBuff, CAN_TX_ID2E9);
}

//AVM 坐标设置
void CANUser_SetAvmSlipInfo(uint8_t *pMsg, uint8_t len)
{
	int16_t Temp = 0;

	Body513Buff[0] = pMsg[1];//x
	Body513Buff[1] = pMsg[2];

	Temp  =  pMsg[3];
	Temp <<= 8;
	Temp |= pMsg[4];

	Temp=0x10000 - Temp;
	Body513Buff[2] = Temp>>8;//y
	Body513Buff[3] = Temp>>0;

	if(ApuTouchInfo.State== 0x00)
	{
		memset(Body513Buff,0,8);
	}
	else
	{
		Body513Buff[5] = 0x20;
	}
	CANUserVar.AvmSlipInfoFlag = 1;
	CANUser_SetBodyCanMsgPeriodic(Body513Buff, CAN_TX_ID513, TIMER_100MS);
	//CANUser_SetBodyCanMsgOnce(Body513Buff, CAN_TX_ID513);
}

//AVM 指令设置
void CANUser_SetAVMCmd(uint8_t *pMsg, uint8_t len)
{
	if(pMsg[0] == OP_CAN_RX_VEHICLE_AVM)
	{
		if(pMsg[1] == 0x02)
		{//进入请求
			Body2F8Buff[0] &= 0xCF;
			Body2F8Buff[0] |= 0x20;
		}
		if(pMsg[1] == 0x01)
		{//退出请求
			Body2F8Buff[0] &= 0xCF;
			Body2F8Buff[0] |= 0x10;
		}
		if(pMsg[1] == 0x00)
		{//无请求
			Body2F8Buff[0] &= ~0x30;
		}
		CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, CAN_TX_INNER_CYCLE);//AVM打开或者关闭的处理
	}
}

void CANUser_SetAvmOutCmd(void)
{
	CarAVMDataStruct *pData = pCAN_GetAVMData();
	uint8_t msg[5];
	
	if((pData->CarAVMReq==1)&&(Reverse_Flag==0))
	{
		//全景退出
		msg[0] = OP_CAN_RX_VEHICLE_AVM;
		
		msg[1] = 1;
		msg[2] = 0;
		
		msg[3] = 0;
		msg[4] = 0;
		
		CANTask_VehicleMsgHandler(msg);
		AvmCnt=150;
	}
}


void CANUser_SetAvmInCmd(void)
{
	CarAVMDataStruct *pData = pCAN_GetAVMData();
	uint8_t msg[5];
	
	//全景进入
	msg[0] = OP_CAN_RX_VEHICLE_AVM;
	
	msg[1] = 2;
	msg[2] = 0;
	
	msg[3] = 0;
	msg[4] = 0;
	
	CANUser_SetAVMCmd(msg, 0);
	AvmCnt=150;
}

void CANUser_SetAmpCmd(uint8_t Type, uint8_t Cmd)
{
	uint8_t msg[4];
	msg[0] = OP_CAN_RX_VEHICLE_SetAmp;
	msg[1] = Type;
	msg[2] = Cmd;
	msg[3] = 0;
	msg[4] = 0;
	CANTask_VehicleMsgHandler(msg);
}




//行车记录仪设置
void CANUser_SetDvrInfo(uint16_t param,uint8_t *pTxdata)
{
	uint8_t SendFlag2F8Id = 0;
	uint8_t SendFlag600Id = 0;
	CarDvrDataStruct *pData = pCAN_GetDvrData();

	TaskCAN_debug(_T("===CANUser_SetDvrInfo %x\n",pTxdata[1]));		
	
	if(param == OP_LOAD_PRJS401_DATA)
	{
	 	switch(pTxdata[1])   
	 	{
			case 0x00:
				
			break;
			case 0x01://DVR使能设置请求关闭
			        Body600Buff[5] &=~0x0C;   
				Body600Buff[5] |=0x04;
				SendFlag600Id = 1;
			break;
			case 0x02://DVR使能设置请求打开
				Body600Buff[5] &=~0x0C;
				Body600Buff[5] |=0x08;
				SendFlag600Id = 1;
			break;
			case 0x03://录音设置请求关闭
				Body600Buff[5] &=~0x30;
				Body600Buff[5] |=0x10;
				SendFlag600Id = 1;
			break;
			case 0x04://录音设置请求打开
				Body600Buff[5] &=~0x30;
				Body600Buff[5] |=0x20;
				SendFlag600Id = 1;
			break;
			case 0x05://录制时长设置请求1min模式.
				Body600Buff[5] &=~0x03;
				Body600Buff[5] |=0x01;
				SendFlag600Id = 1;
			break;
			case 0x06://录制时长设置请求3min模式.
				Body600Buff[5] &=~0x03;
				Body600Buff[5] |=0x02;
				SendFlag600Id = 1;
			break;
			case 0x07://录制时长设置请求5min模式.
				Body600Buff[5] |=0x03;
				SendFlag600Id = 1;
			break;
			case 0x08://分辨率设置请求1080P模式
				Body600Buff[4] &=~0x30;
				Body600Buff[4] |=0x10;
				SendFlag600Id = 1;
			break;
			case 0x09://分辨率设置请求720P模式
				Body600Buff[4] &=~0x30;
				Body600Buff[4] |=0x20;
				SendFlag600Id = 1;
			break;
			case 0x0a://SD卡容量查询请求显示
				Body2F8Buff[6] &=~0x03;
				Body2F8Buff[6] |=0x02;
				SendFlag2F8Id = 1;
			break;
			case 0x0b://SD卡容量查询请求退出
				Body2F8Buff[6] &=~0x03;
				Body2F8Buff[6] |=0x01;
				SendFlag2F8Id = 1;
			break;
			case 0x0c://故障信息显示请求进入
				Body2F8Buff[7] &=~0xC0;
				Body2F8Buff[7] |=0x80;
				SendFlag2F8Id = 1;
			break;
			case 0x0d://故障信息显示请求退?
				Body2F8Buff[7] &=~0xC0;
				Body2F8Buff[7] |=0x40;
				SendFlag2F8Id = 1;
			break;
			case 0x0e://系统版本信息查询请求显示
				Body2F8Buff[6] &=~0x0C;
				Body2F8Buff[6] |=0x08;
				SendFlag2F8Id = 1;
			break;
			case 0x0f://系统版本信息查询请求退出
				Body2F8Buff[6] &=~0x0C;
				Body2F8Buff[6] |=0x04;
				SendFlag2F8Id = 1;
			break;
			case 0x10://DVR实时显示请求进入
				Body2F8Buff[6] &=~0xC0;
				Body2F8Buff[6] |=0x80;
				SendFlag2F8Id = 1;
			break;
			case 0x11://DVR实时显示请求退出.
				Body2F8Buff[6] &=~0xC0;
				Body2F8Buff[6] |=0x40;
				SendFlag2F8Id = 1;
			break;
			case 0x12://回放请求进入
				Body2F8Buff[6] &=~0x30;
				Body2F8Buff[6] |=0x20;
				SendFlag2F8Id = 1;
			break;
			case 0x13://回放请求退出
				Body2F8Buff[6] &=~0x30;
				Body2F8Buff[6] |=0x10;
				SendFlag2F8Id = 1;
			break;
			case 0x14://拍照请求.
				Body600Buff[7] &=~0x0C;
				Body600Buff[7] |=0x04;
				SendFlag600Id = 1;
			break;
			case 0x15://进入dvr_app
			    if(g_tMcuDevState.uIOState.bits.Reverse_Flag == 0)
		        {
					fTw8836.ADI7186CvbsDetStep=OPERATION_1;
					fTw8836.ADI7186DVRFlag=1;
					//_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_DVR,1);
		        }
				CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_S401,USERID_APU_TX_DVR_SETREQ, 1);
			break;
			case 0x16://退出dvr_app
				fTw8836.ADI7186CvbsDetStep=OPERATION_0;
				fTw8836.ADI7186DVRFlag=0;
				//_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_DVR,0);
			break;
			case 0x20://语音设置中文
				Body600Buff[4] &=~0x0F;
				Body600Buff[4] |=0x01;
				SendFlag600Id = 1;
			break;
			case 0x21://语音设置英文
				Body600Buff[4] &=~0x0F;
				Body600Buff[4] &=0x02;
				SendFlag600Id = 1;
			break;

			case 0x22: // 请求格式化SD卡bit17bit16 0:inactive 1:cancel format 2:format 3:reserved
				Body600Buff[2] &=~0x03;
				Body600Buff[2] |=0x02;
				SendFlag600Id = 1;
				break;
				
			default:
			break;
		}

		if(1==SendFlag2F8Id)
		{
			CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, CAN_TX_INNER_CYCLE);
			memset(Body2F8Buff,0,8);
		}
		if(1==SendFlag600Id)
		{
			CANUser_SetBodyCanMsgOnce(Body600Buff, CAN_TX_ID600);
			memset(Body600Buff,0,8);
		}
	}
	else if(param == OP_LOAD_PRJR103H_INFO)
	{
		//TaskCAN_debug(_T("R103-H15T_DVR_CMD:GID = 0x%x,SID = 0x%x\n",pTxdata[1],pTxdata[2]));
		SendFlag2F8Id = 1;
		switch(pTxdata[1])
		{
			case 0x00:
			{
				switch(pTxdata[2])
				{
					case 0x01://off tape
						Body2F8Buff[0] &= 0xc0;
						Body2F8Buff[0] |= 0x01;
						break;
					case 0x02://on tape
						Body2F8Buff[0] &= 0xc0;
						Body2F8Buff[0] |= 0x02;
						break;
					case 0x03:// 1080p
						Body2F8Buff[1] |= 0x40;
						break;
					case 0x04://720p
						Body2F8Buff[1] |= 0x80;
						break;
					case 0x05:// 1min
						Body2F8Buff[1] |= 0x10;
						break;	
					case 0x06:// 3min
						Body2F8Buff[1] |= 0x20;
						break;
					case 0x07:// 5min
						Body2F8Buff[1] |= 0x30;
						break;
					case 0x08: // open dvr app;synchronization msg
						TaskCAN_debug(_T("open DVR app!!!!\n"));
						#if 1 //只切通道,不切源
						if((g_tMcuDevState.uIOState.bits.Reverse_Flag == 0) || (g_tMcuDevState.uDetect.bits.Blind_Flag == 0))
			        	{
							//fTw8836.ADI7186CvbsDetStep=OPERATION_1;
							//pData->DVR_VideoSignalLockStatus = 0x0;
							fTw8836.CurrentCvbsChannel = 0;
							fTw8836.ADI7186DVRFlag=1;
			        	}
						#else
							_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_DVR,1);
						#endif
						CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_SETREQ, 1);
						CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_VER, 1);
						break;
					case 0x09://colse dvr app,stop msg synchronization
						TaskCAN_debug(_T("close DVR app!!!!\n"));
						#if 1
							//fTw8836.ADI7186CvbsDetStep=OPERATION_0;
							//pData->DVR_VideoSignalLockStatus = 0x0;
							fTw8836.CurrentCvbsChannel = 0;
							fTw8836.ADI7186DVRFlag=0;
							//CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_SETREQ, 1);
						#else
							_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_DVR,0);
						#endif
					default://no request
						Body2F8Buff[0] &= 0xfc;//clear bits
						Body2F8Buff[1] &= 0x0f;
						SendFlag2F8Id = 0;
						break;
				}
			}
				break;
			case 0x01:
			{
				switch(pTxdata[2])
				{
					case 0x01:
						Body2F8Buff[0] &= 0xc0;
						Body2F8Buff[0] |= 0x20;
						break;
					case 0x02:
						Body2F8Buff[0] &= 0xc0;
						Body2F8Buff[0] |= 0x10;
						break;
					case 0x03:
						Body2F8Buff[0] &= 0xc0;
						Body2F8Buff[0] |= 0x08;
						break;
					case 0x04:
						Body2F8Buff[0] &= 0xc0;
						Body2F8Buff[0] |= 0x04;
						break;
					default:
						Body2F8Buff[0] &= 0x03;
						SendFlag2F8Id = 0;
						break;
				}
				break;
			}
			case 0x02:
			{
				if((pTxdata[2]<=0x24) && (pTxdata[2]>=0x00))//pMsg[1] is beween 0x00 and 0x24
				{
					Body2F8Buff[2] = pTxdata[2]<<2;
					//TaskCAN_debug(_T("Body2F8Buff[2] = %x, SendFlag2F8Id = %d\n",Body2F8Buff[2],SendFlag2F8Id));
				}
				
				else
					SendFlag2F8Id = 0;
					
				break;
			}
			case 0x03:
			{
				Body2F8Buff[1] &= 0xf3;//清除原始数据...
				Body2F8Buff[1] |=  0x04;
				Body2F8Buff[3] =  pTxdata[2];
				break;
			}
			case 0x04:
			{
				Body2F8Buff[1] &= 0xf3;
				Body2F8Buff[1] |=  0x08;
				Body2F8Buff[3] =  pTxdata[2];
				break;
			}
			case 0x05:
			{
				Body2F8Buff[1] &= 0xf3;
				Body2F8Buff[1] |=  0x0c;
				Body2F8Buff[3] =  pTxdata[2];
				break;
			}
			default:
				SendFlag2F8Id = 0;
				break;
		}
		if(1==SendFlag2F8Id)
		{
			SendCanMsgManage.SendMsg2DVR = 1;
			SendCanMsgManage.SendMsg2DVR_Cnt = 3;
			//TaskCAN_debug(_T("--------Body2f8 buffer updata-------\n"));
			CANUser_SetBodyCanMsgPeriodic(Body2F8Buff, CAN_TX_ID2F8, TIMER_100MS);
		}
		

	}
}

#endif		//end #ifdef  D_CANBUS_IN
