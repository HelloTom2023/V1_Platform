/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		canbus.h
* Target MCU:		V850SJ3
* Module:
* Summary:		CAN bus header file
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
#ifndef  _CANBUS_H_
#define  _CANBUS_H_

#ifdef  _CANBUS_C
#define	_CANBUS_ 
#else
#define _CANBUS_		extern
#endif

#define CAN_MODULE_V850CAN		// use V850 inner CAN module.

#include "can_cfg.h"
#include "..\CAN_Common\ByteDataBufferManager.h"
#include "..\CAN_Common\CAN_Api.h"
#include "..\CAN_Common\CAN_Msg.h"
#include "CAN_User\CANUser.h"
#include "CAN_User\CANUser_Api.h"
#include "CAN_Module\CANbus_SegTrans.h"
#include "CAN_Local\CANbus_LocalNet.h"


#define CAN_TYPE_BODY		0	/*used to connect vehicle body CAN bus */
#define CAN_TYPE_INNER		1	/*used to connect inner entertainment CAN bus */

#if D_DEBUG_CANBUS&& D_PRINT_EN
#define TaskCAN_debug(x)  			x
#else
#define TaskCAN_debug(x)
#endif


//----------------------------------------

#define D_CANBUS_MSG_QUE_DEEP		8  

#define _CANBUS_TASK_TIMING_		_2MS_
#define _CANBUS_CORE_TIMING_		_3MS_
#define _CANBUS_TASK_TICK_			_set_timing_xms_base_core_tick(_CANBUS_TASK_TIMING_)
#define _CANBUS_CORE_TICK_			_set_timing_xms_base_core_tick(_CANBUS_CORE_TIMING_)
#define _set_timing_xms_base_canbus_task_tick(x)        ((x/_CANBUS_TASK_TIMING_ - 1))
#define _set_timing_xms_base_canbus_core_tick(x)        ((x/_CANBUS_CORE_TIMING_ - 1))

#define _SendFullMsgToCanbus(gid,sid,d0,d1,d2,d3)  	OS_PostFullMsgDir(&g_tCanTaskCB,(uint16_t)(gid),(uint16_t)(sid),(uint8_t)(d0),(uint8_t)(d1),(uint8_t)(d2),(uint8_t)(d3))
#define _SendMsgToCanbus(gid,sid,buf)                      	OS_PostMsgDir(&g_tCanTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf))
#define _InsertMsgToCANbus(gid,sid,buf) 			OS_InsertMsgDir(&g_tCanTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf),0)

#define ECU_TIMEOUT_CNT	10
#define ECU_GW_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)// 10*100
#define ECU_BCM_CYCLE_TIME			(TIMER_500MS*ECU_TIMEOUT_CNT)// 5*500
#define ECU_AVM_CYCLE_TIME			(TIMER_200MS*ECU_TIMEOUT_CNT)
#define ECU_TBOX_CYCLE_TIME		(TIMER_100MS*ECU_TIMEOUT_CNT)
#define ECU_PEPS_CYCLE_TIME		(TIMER_40MS*ECU_TIMEOUT_CNT)
#define ECU_ALL_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)
#define ECU_AC_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)
#define ECU_IP_CYCLE_TIME			(TIMER_50MS*ECU_TIMEOUT_CNT)
#define ECU_DVR_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)
#define ECU_RRS_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)
#define ECU_ESP_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)
#define ECU_EMS_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)
#define ECU_LCM_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)
#define ECU_PAC_CYCLE_TIME			(TIMER_100MS*ECU_TIMEOUT_CNT)

/*next structure used for: CAN message periodic spy */
typedef struct
{
	uint16_t Timer_AllEcu;		/*All ECU message timer */
	uint16_t Timer_GW;		/*GW message timer*/
	uint16_t Timer_GW320; 
	uint16_t Timer_GW32A;
	uint16_t Timer_BCM;		/*BCM message timer */
	uint16_t Timer_BCM347;
	uint16_t Timer_BCM610;		/*BCM message timer */
	uint16_t Timer_RMRA;		/*BCM message timer */
	uint16_t Timer_AVM;		/*AVM message timer */
	uint16_t Timer_TBOX;		/*TBOX message timer */
	uint16_t Timer_PEPS;		/*PEPS message timer */
	uint16_t Timer_AC;		/*AC message timer */
	uint16_t Timer_IP;		/*IP message timer */
	uint16_t Timer_DVR612;
	uint16_t Timer_DVR613;
	uint16_t Timer_DVR;		/*DVR message timer */
	uint16_t Timer_RRS;		/*RRS message timer */
	uint16_t Timer_ESP;
	uint16_t Timer_ESP218;
	uint16_t Timer_ESP368;
	uint16_t Timer_EMS;
	uint16_t Timer_LCM;
	uint16_t Timer_PAC;
	
	/*next bit: 0- not exist; 1-exist */
	uint8_t GW_State		:1;	
	uint8_t GW320_State:1;
	uint8_t GW32A_State:1;
	uint8_t	BCM_State		:1;
	uint8_t BCM347_State:1;
	uint8_t	AVM_State		:1;
	uint8_t Tbox_State		:1;
	uint8_t	PEPS_State		:1;
	uint8_t AC_State		:1;
	uint8_t IP_State			:1;
	uint8_t AllECU_State		:1;
	uint8_t DVR612_State		:1;
	uint8_t DVR613_State		:1;
	uint8_t DVR_State		:1;
	uint8_t RRS_State		:1;
	uint8_t ESP_State:1;
	uint8_t ESP218_State:1;
	uint8_t ESP368_State:1;
	uint8_t EMS_State:1;
	uint8_t LCM_State:1;
	uint8_t PAC_State:1;	
}BCAN_ECU_STR;

typedef enum can_module_sys_enum
{
	CAN_SYS_OFF,
	CAN_SYS_ON,
	CAN_SYS_SLEEP
}CAN_SYS_STATE_ENUM;

// Function Control Step
#define CAN_FUNC_STARTUP 			0x00	 
#define CAN_FUNC_OPERATION		0x10	
#define CAN_FUNC_PWROFF			0x20
#define CAN_FUNC_BUSOFF			0x30

typedef enum can_operation_enum
{
	CAN_OPERATION_IDLE = CAN_FUNC_OPERATION,
	CAN_OPERATION_TX,
	CAN_OPERATION_RX,
	CAN_OPERATION_END
}CAN_OPERATION_ENUM;

typedef enum can_busoff_enum
{
	CAN_BUSOFF_INIT = CAN_FUNC_BUSOFF,
	CAN_BUSOFF_DEAL,
	CAN_BUSOFF_END
}CAN_BUSOFF_ENUM;


#pragma pack(1)
typedef struct{
	uint8_t Acc_desWarnMode:2;
	uint8_t Fcw_crashWarnEnable:1;
	uint8_t Fcw_autobrakeEnable:1;
	uint8_t Rcw_bsdEnable:1;
	uint8_t Rcw_ctaEnable:1;
	uint8_t Rcw_crashWarnEnable:1;
	uint8_t Ldw_sensitivity:1;
}tCanVechSet_Data1;

typedef struct{
	uint8_t Ldw_slaSwitch:1;
	uint8_t Ldw_hmaEnable:1; 
	uint8_t Reserved:6;
}tCanVechSet_Data2;

typedef struct{
	uint32_t Longitude;
	uint32_t Latitude;
	uint8_t LongitudeFlag:1;//0,东经;1，西经
	uint8_t LatitudeFlag:1; //0,北纬;1,南纬
	uint8_t GpsValid:1;     //GPS数据有效...  0:有效;1,无效
	uint8_t Reserved:5;
}tCanGpsInfo;

#pragma pack(1)
typedef struct{
#ifdef UDS_ENABLE_MACRO
	//uint8_t VIN[DID_LENTH_VIN];
	//uint8_t EcuSerialNum[DID_LENTH_SN];
	//uint8_t EolCfg[DID_FD01_LENTH];
	uint8_t Phone[DID_LEN_PHONE];//add it by ztqin 20150109

	uint8_t DID_F184_DATA[DID_F184_LENGTH]; 
	uint8_t DID_F18C_DATA[DID_F18C_LENGTH]; //Ecu Serial Num
	uint8_t DID_F190_DATA[DID_F190_LENGTH]; //VIN
	uint8_t DID_F1A0_DATA[DID_F1A0_LENGTH]; 
	uint8_t DID_F1A2_DATA[DID_F1A2_LENGTH]; 
	uint8_t DID_F1FA_DATA[DID_F1FA_LENGTH];//H15T EOL 
	uint8_t DID_F1F8_DATA[DID_F1F8_LENGTH];//S401 EOL
	
	uint8_t DID_FD01_DATA[DID_FD01_LENGTH];
	uint8_t DID_F101_DATA[DID_F101_LENGTH];
	
#endif
//建议后续的项目,这个数据块不存储其他的数据,仅仅用于存储车辆的配置信息...
#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
	tCanVechSet_Data1 VehicleData1;
	tCanVechSet_Data2 VehicleData2;
#endif
	tCanGpsInfo GpsInfo;
	uint8_t SpecialCode;
	uint16_t iCheckSum;
}tBUS_EEP_DATA;
#pragma pack(4)

#pragma section data "no_init" begin
_CANBUS_   tBUS_EEP_DATA 	l_tBusData;
_CANBUS_   tCanGpsInfo GpsInfo;
#pragma section data "no_init" end


typedef struct
{
	uint8_t  	SysState;	
	uint8_t  	CANMode[CAN_IDMAX];
	uint8_t 	BusOffMode[CAN_IDMAX];
	uint8_t	DataSyncStatus;
	uint16_t	Ticks_Count;
	uint8_t	ProtectFlag		:1;	/*voltage protect flag */
	uint8_t 	DisVideo			:2;	/*disable video watch: 0-enable, 1-disable 3- unvalid state */
	uint8_t	SpeedCnt			:5;	
	/*----------*/
	uint8_t     Reserved			:8;
}CANModuleStruct;

typedef struct
{
    uint8_t APUStatus;
    uint8_t ACC		:2;
	uint8_t ILL     :2; //snake20160921 
    uint8_t SpiReady	:2;		/*SPI comm is ready, could sync data */
} SysStatusStruct;

//snake 2016817
#pragma pack(1)
typedef struct
{
	//send msg to apu manage

	//seng msg to canbus manage
	uint8_t SendMsg2DVR:1;//0:send default ;1:send cmd data
	uint8_t SendMsg2Canbus_Reserved1_7  : 7;

	uint8_t SendMsg2DVR_Cnt;
}CAN_MSG_SEND_MANAGE_STRUCT;
#pragma pack(4)


#define CAN_MSG_SYNC_NO		0	/*have not sync */
#define CAN_MSG_SYNC_ON1		1	/*sync running */
#define CAN_MSG_SYNC_ON2		2	/*sync running */
#define CAN_MSG_SYNC_END		3	/*sync end */


extern tTASK_CTRL_BLOCK g_tCanTaskCB;
extern uint8_t Can_Vol_Reverse;   
extern uint8_t AvmExistFlag;
extern SysStatusStruct   SystemStatus;//snake20160816 set extern
_CANBUS_ CAN_MSG_SEND_MANAGE_STRUCT SendCanMsgManage;


_CANBUS_  CANModuleStruct sCANModule;
_CANBUS_  BCAN_ECU_STR	BodyECUStatus;	/* body CAN ECU state variable */
#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
_CANBUS_  void CANbus_VehicleVariableReset(void);
#endif

_CANBUS_  bool   	CANbus_TaskCreate(void);
_CANBUS_  void   	CANTask_SendKnobInfo(uint8_t type, uint8_t dir, uint8_t diff);
_CANBUS_  void 	CANTask_SendApiData(uint8_t param, uint8_t sid, uint8_t flag);
//_CANBUS_  void 	CAN_EepStore(uint16_t DID, uint8_t *pData, uint8_t len);
_CANBUS_ uint8_t CAN_EepStore(uint16_t DID, uint8_t *pData, uint8_t len);
_CANBUS_  void 	TestIO1_Output(uint8_t mode, uint8_t level);
_CANBUS_  void 	CAN0_LocalWakeup(uint8_t type, uint8_t level);
_CANBUS_  uint8_t CanBus_GetEepOpState(void);
_CANBUS_  void 	CANTask_VehicleMsgHandler(uint8_t *pMsg);
_CANBUS_  void 	CANTask_DTVMsgHandler(uint8_t* pMsg);
_CANBUS_  void 	CANTask_NAVIMsgHandler(uint8_t* pMsg);
_CANBUS_  void 	CANTask_EOLMsgHandler(uint8_t *pMsg);

_CANBUS_ void CANTask_RxBusDataDeal(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen);
//CAN_API void CAN_LoadDefaultEOLByCarType(uint8_t *pData,uint8_t CarType);
CAN_API void CAN_LoadDefaultEOLByCarType(uint8_t *pData,uint8_t CarType,uint8_t len);
CAN_API uint8_t CANTask_GetRemoteStartState(void);
#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
CAN_API void CAN_VehicleEepStore(void);
#endif

extern uint8_t CANTask_SetCanPMStateStructState(uint8_t state);
extern uint8_t CANTask_GetCanPMStateStructState(void);


#endif

