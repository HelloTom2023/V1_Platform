/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CAN_Api.h
* Target MCU:		V850SJ3
* Module:
* Summary:		CAN module Api interface to other module to exchange data ram
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
#define _CAN_API_C
#include "..\..\config\inc.h"


#pragma section data "no_init" begin
/* this section,when CPU re set,the data can not be initialized if the power on	*/
#ifdef CAN_API_CAR_LIGHT_EN
CarLightDataStruct          CAN_CarLightDataStr;
#endif
#ifdef CAN_API_CAR_DOOR_LOCK_EN
CarDoorLockDataStruct CAN_CarDoorLockStr;
#endif

#ifdef CAN_API_CAR_WIPER_EN
CarWiperDataStruct        CAN_CarWiperDataStr;
#endif
#ifdef CAN_API_CAR_WINDOW_EN
CarWindowDataStruct      CAN_CarWindowDataStr;
#endif
#ifdef CAN_API_CAR_DOOR_EN
CarDoorStateDataStruct   CAN_CarDoorStateStr;
#endif
#ifdef CAN_API_CAR_SEAT_EN
CarSeatDataStruct           CAN_CarSeatDataStr;
#endif
#ifdef CAN_API_CAR_RMIRROR_EN
CarRMirrorDataStruct      CAN_CarRMirrorDataStr;
#endif
#ifdef CAN_API_CAR_MAINTAIN_EN
CarMaintainInfoStruct	CAN_CarMaintainState;
#endif
#ifdef CAN_API_CAR_ECU_STATUS_EN
CarEcuDataStruct           CAN_CarEcuDataStr;
#endif
#ifdef CAN_API_CAR_BSD_EN
CarBSDDataStruct          CAN_CarBSDDataStr;
#endif
#ifdef CAN_API_CAR_PAC_EN
CarPACDataStruct         CAN_CarPACDataStr;
#endif
#ifdef CAN_API_CAR_TBOX_EN
TBOXDataStruct            CAN_TBOXDataStr;
TboxTUIDStruct		CAN_TboxTUIDStr;
#endif
#ifdef CAN_API_CAR_AVM_EN
CarAVMDataStruct         CAN_CarAVMDataStr;
#endif
#ifdef CAN_API_CAR_ODO_EN
CarODODataStruct         CAN_CarODODataStr;
#endif
#ifdef CAN_API_CAR_SYS_EN
CarSystemDataStruct     CAN_CarSystemDataStr;
#endif
#ifdef CAN_API_CAR_PEPS_EN
CarPEPSDataStruct         CAN_CarPEPSDataStr;
#endif
#ifdef CAN_API_AC_FRONT_EN
//FrontACDataStruct         CAN_FrontACDataStr;
#endif 
#ifdef CAN_API_AC_REAR_EN
//RearACDataStruct          CAN_RearACDataStr;
#endif
#ifdef CAN_API_AC_SEATHEAT_EN
ACSeatHeatDataStruct    CAN_SeatHeatDataStr;
#endif
#ifdef CAN_API_RADAR_EN
RadarStatusDataStruct     CAN_RadarStatusDataStr;
RadarDataStruct 		CAN_RadarDataStr;
#endif
#ifdef CAN_API_TPMS_EN
TPMSDataStruct  		CAN_TPMSDataStr;
#endif
#ifdef CAN_API_CAR_SPEED_EN
CarSpeedDataStruct         CAN_CarSpeedDataStr;
#endif
#ifdef CAN_API_CAR_ANGLE_EN
CarAngleDataStruct         CAN_CarAngleDataStr;
#endif
#ifdef CAN_API_AC_OUTTEMP_EN
CarOutsideTempDataStruct  CAN_OutsideTempDataStr;
#endif
#ifdef HU_API_NAVI_INFO_EN
NaviInforamtionStruct        HU_NaviInfoDataStr;
#endif
#ifdef CAN_API_DTV_EN
 DTVStateInfoStruct   	CAN_DTVStateInfoStr;
DTVVersionStruct		CAN_DTVVersionStr;
#endif
FCPVersionStruct		CAN_FCPVersionStr;
CANKeyStateStruct		CAN_RcvKeyState;
uint32_t   DataInitCodeId;

CANVehicleStateStruct	CAN_VehicleStateStr;
CANStateDataStruct	CAN_SysStateStr;
#ifdef UDS_ENABLE_MACRO
EOLCfgStruct			CAN_EOLCfgStr;
ExtMediaDataStruct		VINDataStr;
#endif
#ifdef CAN_API_CAR_ECO_EN
CarECOInfoStruct		CAN_ECOInfoStr;
#endif

#ifdef CAN_API_DVR_INFO_EN
CarDvrDataStruct         CAN_CarDvrDataStr;
CarDvrVerStruct         CAN_CarDvrVerStr;
#endif

#ifdef CAN_FUEL_LEVEL_WARN_EN
FuelLevelStruct         CAN_FuelLevelStr;
#endif

CanPmStruct         CAN_CanPmStr;
CarAccCtrlStruct	CAN_AccCtrlStr;
CarFcwStruct		CAN_FcwStr;
CarRcwStruct		CAN_RcwStr;
CarLdwSensStruct CAN_LdwStr;

#pragma section data "no_init" end

uint8_t MediaRxCANByteBuffer[100];
ByteBufferMangerStruct MediaRxCANByteBufferManager;

/*when the data structure is not constant, 
  * the data don't need bakup, we can use
 * next variable to transmit data.
 */
CommonDataStruct		CAN_CommonDataStr;

void CAN_Api_Init(void)
{
	uint8_t len = 0;

	//if(DataInitCodeId == 0x12345678)
	//{
	//	return;
	//}
#ifdef CAN_API_CAR_ANGLE_EN
	CAN_CarAngleDataStr.LENGTH = sizeof(CarAngleDataStruct);
	//CAN_CarAngleDataStr.GID = LMS_CAN_TX_CAR;
	CAN_CarAngleDataStr.SID = OP_CAN_TX_CAR_ANGLE;
	CAN_CarAngleDataStr.Angle = 0xff;
#endif
#ifdef CAN_API_CAR_SPEED_EN
	CAN_CarSpeedDataStr.LENGTH = sizeof(CarSpeedDataStruct);
	CAN_CarSpeedDataStr.SID = OP_CAN_TX_CAR_SPEED;
	CAN_CarSpeedDataStr.SpeedHbyte = 0x00;
	CAN_CarSpeedDataStr.SpeedLbyte = 0x00;
#endif
#ifdef CAN_API_AC_OUTTEMP_EN
	CAN_OutsideTempDataStr.LENGTH = sizeof(CarOutsideTempDataStruct);
	CAN_OutsideTempDataStr.SID = OP_CAN_TX_AC_OUTTEMP;
	CAN_OutsideTempDataStr.OutsideTempValue = 0xff;
#endif
#ifdef CAN_API_CAR_PAC_EN
	CAN_CarPACDataStr.LENGTH = sizeof(CarPACDataStruct);
	CAN_CarPACDataStr.SID = OP_CAN_TX_CAR_PAC;
	CAN_CarPACDataStr.ParkMode=0x00;
#endif
#ifdef CAN_API_RADAR_EN
	CAN_RadarDataStr.LENGTH = sizeof(RadarDataStruct);
	CAN_RadarDataStr.SID = OP_CAN_TX_RADAR_DATA;
 	CAN_RadarDataStr.FLM_Radar_Info = 0x00;
	CAN_RadarDataStr.FL_Radar_Info = 0x00;
	CAN_RadarDataStr.FRM_Radar_Info = 0x00;
	CAN_RadarDataStr.FR_Radar_Info = 0x00;
	CAN_RadarDataStr.RLM_Radar_Info = 0x00;
	CAN_RadarDataStr.RL_Radar_Info = 0x00;
	CAN_RadarDataStr.RRM_Radar_Info = 0x00;
	CAN_RadarDataStr.RR_Radar_Info = 0x00;

	CAN_RadarStatusDataStr.LENGTH = sizeof(RadarStatusDataStruct);
	CAN_RadarStatusDataStr.SID = OP_CAN_TX_RADAR_STATE;
	CAN_RadarStatusDataStr.NearestDistance = 0x00;
	CAN_RadarStatusDataStr.NearestPosition = 0x00;
	CAN_RadarStatusDataStr.Reserved = 0x00;
	CAN_RadarStatusDataStr.LRM_Distance = 0x00;
	CAN_RadarStatusDataStr.RRM_Distance = 0x00;
	CAN_RadarStatusDataStr.LRC_Distance = 0x00;	
	CAN_RadarStatusDataStr.RRC_Distance = 0x00;
	CAN_RadarStatusDataStr.LFC_Distance = 0x00;
	CAN_RadarStatusDataStr.RFC_Distance = 0x00;
	CAN_RadarStatusDataStr.LFM_Distance = 0x00;
	CAN_RadarStatusDataStr.RFM_Distance = 0x00;
	CAN_RadarStatusDataStr.RRS_Distance = 0x00;
	CAN_RadarStatusDataStr.LRS_Distance = 0x00;
	CAN_RadarStatusDataStr.LFS_Distance = 0x00;
	CAN_RadarStatusDataStr.RFS_Distance = 0x00;
	
	CAN_RadarStatusDataStr.RadarFailureFlag = 0;
	CAN_RadarStatusDataStr.RadarSysStatus = 0;
#endif
#ifdef CAN_API_TPMS_EN
	CAN_TPMSDataStr.LENGTH = sizeof(TPMSDataStruct);
	CAN_TPMSDataStr.SID = OP_CAN_TX_TPMS_DATA;
	CAN_TPMSDataStr.SystemFailure=0;
	CAN_TPMSDataStr.SignalStatus = 0;
	CAN_TPMSDataStr.TirePresureSignalStatus = 1;
	CAN_TPMSDataStr.TpmsOnlineState = 0;
	CAN_TPMSDataStr.FL_temperatureWarn=0;
	CAN_TPMSDataStr.FR_temperatureWarn=0;
	CAN_TPMSDataStr.RL_temperatureWarn=0;
	CAN_TPMSDataStr.RR_temperatureWarn=0;
	CAN_TPMSDataStr.FL_tyrePressure = 0xff;
	CAN_TPMSDataStr.FL_tyreTemperature = 0xff;//显示为 --
	CAN_TPMSDataStr.FR_tyrePressure = 0xff;
	CAN_TPMSDataStr.FR_tyreTemperature = 0xff;
	CAN_TPMSDataStr.RL_tyrePressure = 0xff;
	CAN_TPMSDataStr.RL_tyreTemperature = 0xff;
	CAN_TPMSDataStr.RR_tyrePressure = 0xff;
	CAN_TPMSDataStr.RR_tyreTemperature = 0xff;
	CAN_TPMSDataStr.FL_WarnStatus=0;
	CAN_TPMSDataStr.FR_WarnStatus= 0;
	CAN_TPMSDataStr.RL_WarnStatus=0;
	CAN_TPMSDataStr.RR_WarnStatus=0;
#endif

#ifdef CAN_API_CAR_LIGHT_EN
	CAN_CarLightDataStr.LENGTH = sizeof(CarLightDataStruct);
	CAN_CarLightDataStr.SID = OP_CAN_TX_CAR_LIGHT;
      CAN_CarLightDataStr.Lamp=0x00;
      CAN_CarLightDataStr.Atmpspher=0x00;
      CAN_CarLightDataStr.lightness=(0x01 << 2);
	CAN_CarLightDataStr.lightBlinkTime=1;
	CAN_CarLightDataStr.lightOffDelay=2;
	CAN_CarLightDataStr.DriveLightEnable=1;
//	CAN_CarLightDataStr.HmaEnable = 0;
#endif
#ifdef CAN_API_CAR_WIPER_EN
	CAN_CarWiperDataStr.LENGTH = sizeof(CarWiperDataStruct);
	CAN_CarWiperDataStr.SID = OP_CAN_TX_CAR_WIPER;
	 CAN_CarWiperDataStr.FrontWiper=0x01;
	 CAN_CarWiperDataStr.RearWiper=0x01;
#endif

#ifdef CAN_FUEL_LEVEL_WARN_EN
	CAN_FuelLevelStr.LENGTH = sizeof(FuelLevelStruct);
	CAN_FuelLevelStr.SID = OP_CAN_TX_FUEL_LEVEL;
	 CAN_FuelLevelStr.CurrFuelLevel = 0x08;
#endif

	CAN_CanPmStr.LENGTH = sizeof(CanPmStruct);
	CAN_CanPmStr.SID = OP_CAN_TX_CAN_PM_DATA;
	CAN_CanPmStr.Car_LowPowerWarn = 0;
	CAN_CanPmStr.Car_PMLevel = 0;
	CAN_CanPmStr.Car_State = 0;


#ifdef CAN_API_CAR_WINDOW_EN
	CAN_CarWindowDataStr.LENGTH = sizeof(CarWindowDataStruct);
	CAN_CarWindowDataStr.SID = OP_CAN_TX_CAR_ANGLE;
	 CAN_CarWindowDataStr.FL_Window=0x00;
	 CAN_CarWindowDataStr.FR_Window=0x00;
	 CAN_CarWindowDataStr.HeadWindow=0x00;
	 CAN_CarWindowDataStr.RL_Window=0x00;
	 CAN_CarWindowDataStr.RR_Window=0x00;
#endif
#ifdef CAN_API_CAR_DOOR_EN
	 CAN_CarDoorStateStr.LENGTH = sizeof(CarDoorStateDataStruct);
	 CAN_CarDoorStateStr.SID = OP_CAN_TX_CAR_DOOR;
	 CAN_CarDoorStateStr.Engine_door_Status=0;
	 CAN_CarDoorStateStr.FL_CarDoor_Status=0;
	 CAN_CarDoorStateStr.FR_CarDoor_Status=0;
	 CAN_CarDoorStateStr.RearBag_Status	=0;
	 CAN_CarDoorStateStr.RL_CarDoor_Status=0;
	 CAN_CarDoorStateStr.RR_CarDoor_Status=0;
	 CAN_CarDoorStateStr.sunroof_door_satus = 0;
	 CAN_CarDoorStateStr.Reserved = 0;
#endif
#ifdef CAN_API_CAR_DOOR_LOCK_EN
	CAN_CarDoorLockStr.LENGTH = sizeof(CarDoorLockDataStruct);
	CAN_CarDoorLockStr.SID = OP_CAN_TX_DOOR_LOCK_INFO;
        CAN_CarDoorLockStr.DoorOpenMode = 0; 
        CAN_CarDoorLockStr.DriveLock = 0;
        CAN_CarDoorLockStr.ParkUnlock = 0;
#endif

/***********主动安全设置*************BOLTE*/
	CAN_AccCtrlStr.LENGTH = sizeof(CarAccCtrlStruct);
	CAN_AccCtrlStr.SID = OP_CAN_TX_ACC_CONTROL_DATA;
//	CAN_AccCtrlStr.DesWarnMode = 0;

	CAN_FcwStr.LENGTH = sizeof(CarFcwStruct);
	CAN_FcwStr.SID = OP_CAN_TX_FCW_DATA;
//	CAN_FcwStr.AutoBrakeEnable = 1;
//	CAN_FcwStr.FcwEnable = 1;

	CAN_RcwStr.LENGTH = sizeof(CarRcwStruct);
	CAN_RcwStr.SID = OP_CAN_TX_RCW_DATA;
//	CAN_RcwStr.BsdEnable = 1;
//	CAN_RcwStr.CtaEnable = 1;
//	CAN_RcwStr.RcwEnable = 1;

	CAN_LdwStr.LENGTH = sizeof(CarLdwSensStruct);
	CAN_LdwStr.SID = OP_CAN_ROAD_ASSISTANT;
//	CAN_LdwStr.LdwSensDat = 0;
//	CAN_LdwStr.SlaEnable = 1;
	
/******************************************/

#ifdef CAN_API_CAR_SEAT_EN
	CAN_CarSeatDataStr.LENGTH = sizeof(CarSeatDataStruct);
	CAN_CarSeatDataStr.SID = OP_CAN_TX_CAR_SEAT;
	 CAN_CarSeatDataStr.FL_Seat=0;
	 CAN_CarSeatDataStr.FR_Seat=0;
	 CAN_CarSeatDataStr.RL_Seat=0;
	 CAN_CarSeatDataStr.RR_Seat=0;
	 CAN_CarSeatDataStr.SeatAutoSet=1;	//座椅礼让默认关闭
#endif
#ifdef CAN_API_CAR_RMIRROR_EN
	CAN_CarRMirrorDataStr.LENGTH = sizeof(CarRMirrorDataStruct);
	CAN_CarRMirrorDataStr.SID = OP_CAN_TX_CAR_RMIRROR;
	 CAN_CarRMirrorDataStr.Left_RMirror=0x00;
	 CAN_CarRMirrorDataStr.Right_RMirror=0x00;
	 CAN_CarRMirrorDataStr.RearAssist = 1;
	 CAN_CarRMirrorDataStr.RearAutoFold = 2;
	 CAN_CarRMirrorDataStr.Reserved = 0;
#endif
#ifdef CAN_API_CAR_ECU_STATUS_EN
	CAN_CarEcuDataStr.LENGTH = sizeof(CarEcuDataStruct);
	CAN_CarEcuDataStr.SID = OP_CAN_TX_ECU_STATE;
	 CAN_CarEcuDataStr.ABS_System=0;
	 CAN_CarEcuDataStr.AC_System=0;
	 CAN_CarEcuDataStr.BCM_System=0;
	 CAN_CarEcuDataStr.BSD_System=0;
	 CAN_CarEcuDataStr.ElecLock_System=0;
	 CAN_CarEcuDataStr.Electronic_Program=0;
	 CAN_CarEcuDataStr.EPB_System=0;
	 CAN_CarEcuDataStr.IP_System=0;
	 CAN_CarEcuDataStr.LampAimSys=0;
	 CAN_CarEcuDataStr.MIL_System=0;
	 CAN_CarEcuDataStr.PAC_System=0;
	 CAN_CarEcuDataStr.PEP_System=0;
	 CAN_CarEcuDataStr.RRS_System=0;
	 CAN_CarEcuDataStr.SafeAir_System=0;
	 CAN_CarEcuDataStr.TBOX_System=0;
	 CAN_CarEcuDataStr.TPM_System=0;
	 CAN_CarEcuDataStr.EPS_System=0;
	 CAN_CarEcuDataStr.EBD_System=0;
	 CAN_CarEcuDataStr.Engine_Error=0;
	 CAN_CarEcuDataStr.Refrigerant_TEMP=0;
	 CAN_CarEcuDataStr.Engine_Speed=0;
	 CAN_CarEcuDataStr.Throttle_Position=0;
	 CAN_CarEcuDataStr.ACC_Pedal=0;
#endif
#ifdef CAN_API_CAR_BSD_EN
	CAN_CarBSDDataStr.LENGTH = sizeof(CarBSDDataStruct);
	CAN_CarBSDDataStr.SID = OP_CAN_TX_CAR_BSD;
	 CAN_CarBSDDataStr.Communication_status=0;
	 CAN_CarBSDDataStr.Left_BSD_Status=0;
	 CAN_CarBSDDataStr.Left_Senser_Status=0;
	 CAN_CarBSDDataStr.Right_BSD_Status=0;
	 CAN_CarBSDDataStr.Right_Senser_Status=0;
#endif
#ifdef CAN_API_CAR_TBOX_EN
 	CAN_TBOXDataStr.LENGTH = sizeof(TBOXDataStruct);
	CAN_TBOXDataStr.SID = OP_CAN_TX_CAR_TBOX;
	 CAN_TBOXDataStr.Car_TBOX_PhoneStatus=0x00;
	 CAN_TBOXDataStr.Car_TBOX_Request=0;
	 CAN_TBOXDataStr.Exist = 0;
	 CAN_TBOXDataStr.PartChange = 0;
	 CAN_TBOXDataStr.Reserved1 = 0;

	 CAN_TboxTUIDStr.LENGTH = sizeof(TboxTUIDStruct);
	 CAN_TboxTUIDStr.SID = OP_CAN_TX_TBOX_TUID;
#endif
#ifdef CAN_API_CAR_AVM_EN
	CAN_CarAVMDataStr.LENGTH = sizeof(CarAVMDataStruct);
	CAN_CarAVMDataStr.SID = OP_CAN_TX_AVM_INFO;
    CAN_CarAVMDataStr.CarAVMReq=0;
    CAN_CarAVMDataStr.BlindReq=0;
    CAN_CarAVMDataStr.BlindReqBk=0;

#endif
#ifdef CAN_API_CAR_ODO_EN
	CAN_CarODODataStr.LENGTH = sizeof(CarODODataStruct);
	CAN_CarODODataStr.SID = OP_CAN_TX_CAR_ODO;
	CAN_CarODODataStr.TotalOdometerH = 0;
	CAN_CarODODataStr.TotalOdometerM = 0;
	CAN_CarODODataStr.TotalOdometerL = 0;
#endif
#ifdef CAN_API_CAR_SYS_EN
	CAN_CarSystemDataStr.LENGTH = sizeof(CarSystemDataStruct);
	CAN_CarSystemDataStr.SID = OP_CAN_TX_CAR_SYS;
	 CAN_CarSystemDataStr.ACC_Status=1;		//default ign = acc
	 CAN_CarSystemDataStr.Car_Gear_Position=0xff;
	 CAN_CarSystemDataStr.Engine_Status=3;
	 CAN_CarSystemDataStr.HandBrake_Status=3;
	 CAN_CarSystemDataStr.Vehicle_Cruise=3;
#endif
#ifdef CAN_API_CAR_PEPS_EN
	CAN_CarPEPSDataStr.LENGTH = sizeof(CarPEPSDataStruct);
	CAN_CarPEPSDataStr.SID = OP_CAN_TX_CAR_PEPS;
	 CAN_CarPEPSDataStr.Key_Position_Status=0xff;
	 CAN_CarPEPSDataStr.Remote_information=0xff;
	 CAN_CarPEPSDataStr.LockSignal = 0x00;
#endif
#ifdef CAN_API_AC_FRONT_EN	
	CAN_FrontACDataStr.LENGTH = sizeof(FrontACDataStruct);
	CAN_FrontACDataStr.SID = OP_CAN_TX_AC_FRONT;
	 CAN_FrontACDataStr.ACPowerSwitch=3;
	 CAN_FrontACDataStr.ACSwitch=3;
	 CAN_FrontACDataStr.ACState=0x00;
	 CAN_FrontACDataStr.AutoMode=0x0f;
	 CAN_FrontACDataStr.CycleMode=3;
	 CAN_FrontACDataStr.DualSwitch=3;
	 CAN_FrontACDataStr.InsideTemperature=0x00;
	 CAN_FrontACDataStr.OutsideTemperature=0xff;
	 CAN_FrontACDataStr.FrontDefrost=3;
	 CAN_FrontACDataStr.LeftTemperature=0xff;
	 CAN_FrontACDataStr.RearDefrost=3;
	 CAN_FrontACDataStr.RightTemperature=0xff;
	 CAN_FrontACDataStr.WindLevel=0xff;
#endif
#ifdef CAN_API_AC_REAR_EN
	CAN_RearACDataStr.LENGTH = sizeof(RearACDataStruct);
	CAN_RearACDataStr.SID = OP_CAN_TX_AC_REAR;
        CAN_RearACDataStr.ACPowerSwitch=3;
	 CAN_RearACDataStr.ACSwitch=3;
	 CAN_RearACDataStr.AirQualityFlag=3;
	 CAN_RearACDataStr.AirSensisty=3;
	 CAN_RearACDataStr.AutoMode=0x0f;
	 CAN_RearACDataStr.CycleMode=3;
	 CAN_RearACDataStr.DualSwitch=3;
	 CAN_RearACDataStr.ECOMode=3;
	 CAN_RearACDataStr.FrontDefrost=3;
	 CAN_RearACDataStr.LeftTemperature=0xff;
	 CAN_RearACDataStr.PollenFilter=3;
	 CAN_RearACDataStr.RearDefrost=3;
	 CAN_RearACDataStr.RearMrrorHeat=3;
	 CAN_RearACDataStr.RightTemperature=0xff;
	 CAN_RearACDataStr.WindAreaControl=0x0f;
	 CAN_RearACDataStr.WindLevel=0xff;
	 CAN_RearACDataStr.WindMode=0xff;
#endif
#ifdef CAN_API_AC_SEATHEAT_EN
	CAN_SeatHeatDataStr.LENGTH = sizeof(ACSeatHeatDataStruct);
	CAN_SeatHeatDataStr.SID = OP_CAN_TX_AC_SEATHEAT;
	 CAN_SeatHeatDataStr.FL_Seat_Heat=0xff;
	 CAN_SeatHeatDataStr.FR_Seat_Heat=0xff;
	 CAN_SeatHeatDataStr.Rear_Seat_Heat=0xff;
#endif
#ifdef CAN_API_CAR_MAINTAIN_EN
	CAN_CarMaintainState.LENGTH = sizeof(CarMaintainInfoStruct);
	CAN_CarMaintainState.SID = OP_CAN_TX_CAR_MAINTAIN;
	CAN_CarMaintainState.CurOilMileageHbit = 0xff;
	CAN_CarMaintainState.CurOilMileageMbit = 0xff;
	CAN_CarMaintainState.CurOilMileageLbit = 0xff;
	CAN_CarMaintainState.OilConsumer = 0xff;
	CAN_CarMaintainState.OilConsumerMs=0xff;
	CAN_CarMaintainState.SpareBattPercent = 0xff;
	CAN_CarMaintainState.SpareOil = 0xffff;
	CAN_CarMaintainState.SpareOilPercent = 0xff;
	CAN_CarMaintainState.TotalMileageHbit = 0xff;
	CAN_CarMaintainState.TotalMileageMbit = 0xff;
	CAN_CarMaintainState.TotalMileageLbit = 0xff;
	CAN_CarMaintainState.CurOilMileageHbit=0xff;
	CAN_CarMaintainState.CurOilMileageLbit=0xff;
	CAN_CarMaintainState.CurOilMileageMbit=0xff;
	CAN_CarMaintainState.CarMaintainMileHbit=0xff;
	CAN_CarMaintainState.CarMaintainMileLbit=0xff;
	CAN_CarMaintainState.RemindSwitch = 1;
	CAN_CarMaintainState.SettingMileage = 5000;
	CAN_CarMaintainState.RemindTime = 3;
	
#endif

#ifdef CAN_API_CAR_ECO_EN
	CAN_ECOInfoStr.LENGTH = sizeof(CarECOInfoStruct);
	CAN_ECOInfoStr.SID = OP_CAN_TX_CAR_ECO;
	CAN_ECOInfoStr.AccPedal = 0;
	CAN_ECOInfoStr.AccPowerStatus = 0;		//*
	CAN_ECOInfoStr.ActualGear = 0x0e;				//*
	CAN_ECOInfoStr.BrakePedalStatus = 0x03;		//*
	CAN_ECOInfoStr.EngineSpeedH = 0xff;			//*
	CAN_ECOInfoStr.EngineSpeedL = 0xff;			//*
	CAN_ECOInfoStr.EngineStatus = 0;		//*
	CAN_ECOInfoStr.FuelConsumptionH = 0xff;	//*
	CAN_ECOInfoStr.FuelConsumptionL = 0xff;	//*
	CAN_ECOInfoStr.FuelCutOff = 0;
	CAN_ECOInfoStr.RealEngTorqH = 0;		//*
	CAN_ECOInfoStr.RealEngTorqL = 0;		//*
	CAN_ECOInfoStr.SpeedH = 0x1f;			//*
	CAN_ECOInfoStr.SpeedL = 0xff;			//*
	CAN_ECOInfoStr.TotalOdometerH = 0xff;	//*
	CAN_ECOInfoStr.TotalOdometerL = 0xff;	//*
	CAN_ECOInfoStr.TotalOdometerM = 0xff;	//*
	CAN_ECOInfoStr.IdleStopStatus = 0;
	CAN_ECOInfoStr.ClutchPedalStatus = 0;
	CAN_ECOInfoStr.KeyInsert = 0;
	CAN_ECOInfoStr.FrictionTorqH = 0x00;
	CAN_ECOInfoStr.FrictionTorqL = 0x00;
	CAN_ECOInfoStr.TorqueConstant = 0xff;
	CAN_ECOInfoStr.Reserved1 = 0;
	CAN_ECOInfoStr.CruiseControlStatus=0;
	CAN_ECOInfoStr.Reserved2=0;	
	CAN_ECOInfoStr.GearDisplay=0x0f;	
#endif

#ifdef HU_API_NAVI_INFO_EN
	HU_NaviInfoDataStr.distanceToNext = 0xffffffff;
	HU_NaviInfoDataStr.NaviIdentification = 0;
#endif
#ifdef CAN_API_DTV_EN
	CAN_DTVStateInfoStr.LENGTH=sizeof(DTVStateInfoStruct);
	CAN_DTVStateInfoStr.SID=OP_CAN_TX_DTV_STATE;
	CAN_DTVStateInfoStr.Broadcast = 0;
	CAN_DTVStateInfoStr.CurrentStationIndex = 0;
	CAN_DTVStateInfoStr.Signal = 0;
	CAN_DTVStateInfoStr.TotalStationNum = 0;
	CAN_DTVStateInfoStr.WorkMode = 0;
	CAN_DTVStateInfoStr.Exist = 0;
	CAN_DTVStateInfoStr.StationType = 1;	/*default TV Video program*/

	CAN_DTVVersionStr.LENGTH = sizeof(DTVVersionStruct);
	CAN_DTVVersionStr.SID = OP_CAN_TX_DTV_VER;
	CAN_DTVVersionStr.BoxVersion[0] = '-';
	CAN_DTVVersionStr.BoxVersion[1] = '-';
	CAN_DTVVersionStr.BoxVersion[2] = '-';
	CAN_DTVVersionStr.BoxVersion[3] = '-';
	CAN_DTVVersionStr.ModuleVersion[0] = '-';
	CAN_DTVVersionStr.ModuleVersion[1] = '-';
	CAN_DTVVersionStr.ModuleVersion[2] = '-';
	CAN_DTVVersionStr.ModuleVersion[3] = '-';
#endif

	CAN_FCPVersionStr.LENGTH = sizeof(FCPVersionStruct);
	//CAN_FCPVersionStr.GID = LMS_CAN_TX_KCP;
	CAN_FCPVersionStr.SID = OP_CAN_TX_KCP_VER;
	CAN_FCPVersionStr.VerHighByte = '-';
	CAN_FCPVersionStr.VerLowByte = '-';
	
	CAN_RcvKeyState.keyState = 0;
	CAN_RcvKeyState.keyValue = 0xff;

	CAN_VehicleStateStr.CAN_Acc = 3;
	CAN_VehicleStateStr.CAN_door = 3;
	CAN_VehicleStateStr.CAN_Lock = 3;
	CAN_VehicleStateStr.CAN_peps = 3;

	CAN_SysStateStr.LENGTH = sizeof(CANStateDataStruct);
	CAN_SysStateStr.SID = 0x01;
	CAN_SysStateStr.State = 0x00;

	CAN_CommonDataStr.SID = 0x00;
	CAN_CommonDataStr.LENGTH = 0x00;
	
#ifdef UDS_ENABLE_MACRO
	CAN_EOLCfgStr.LENGTH = sizeof(EOLCfgStruct);
	CAN_EOLCfgStr.SID = OP_CAN_TX_EOL;
	{
		DID_STRUCT *pTable = Uds_GetDIDCfgTable();
		uint8_t index = 0;
		#if (PROJECT_CODE == CHANGAN_S401)
			index = Uds_GetDidIndex(DID_ID_F1F8);
		#elif (PROJECT_CODE == CHANGAN_R103_H15T)
			index = Uds_GetDidIndex(DID_ID_F1FA);
		#endif
		if(index != 0xff)
		{	/*去掉此句，防止配置恢复到默认顶配*/
//			CAN_LoadDefaultEOLByCarType(pTable[index].pParam, CAR_TYPE);
//			CAN_LoadDefaultEOLByCarType(CAN_EOLCfgStr.Param, CAR_TYPE);
		}
	}
	//VINDataStr.GID = LMS_CAN_TX_CAR;
	VINDataStr.SID = OP_CAN_TX_CAR_VIN;
	VINDataStr.Ctl.length = 0;
	VINDataStr.Info.length = DID_F190_LENGTH;
	VINDataStr.Info.pData = l_tBusData.DID_F190_DATA;
	VINDataStr.LENGTH = VINDataStr.Ctl.length+VINDataStr.Info.length+3;
#endif

#ifdef CAN_API_DVR_INFO_EN
	#if 0
		CAN_CarDvrDataStr.PrjCode = 0x03;
		CAN_CarDvrDataStr.USERID = 0x01;
		CAN_CarDvrDataStr.EnableStatu = 0x00;
		CAN_CarDvrDataStr.TapeStatu = 0x2;
		CAN_CarDvrDataStr.ResolutionStatu = 0x2;
		CAN_CarDvrDataStr.RecordingStatu = 0x2;
		CAN_CarDvrDataStr.SystemError = 0x1;
		CAN_CarDvrDataStr.RebroadcastStatu= 0x2;
		CAN_CarDvrDataStr.PhotographResult= 0x2;
		CAN_CarDvrDataStr.SdcardStatu = 0x2;
		CAN_CarDvrDataStr.RealtimeDisplayStatu = 0x2;
		CAN_CarDvrDataStr.SystemImprintStatu = 0x2;
		CAN_CarDvrDataStr.SDCapacityStatu = 0x2;
		CAN_CarDvrDataStr.ErrorRecordStatu = 0x2;
		CAN_CarDvrDataStr.EmergencyRecordStatu = 0x2;
		CAN_CarDvrDataStr.DVRSignalLockStatu= 0x00;
		CAN_CarDvrDataStr.Exist= 0x0;
	#else
		//date
		CAN_CarDvrDataStr.PrjCode = 0x04;
		CAN_CarDvrDataStr.USERID = 0x01;
		CAN_CarDvrDataStr.DVR_SettingStatusReserved = 0;
		CAN_CarDvrDataStr.DVR_RecordingCycleSetStatus = 0;
		CAN_CarDvrDataStr.DVR_ResolutionStatus = 0;
		CAN_CarDvrDataStr.DVR_VideoSignalLockStatus = 0;
		CAN_CarDvrDataStr.DVR_TapeSetStatus = 0;
		CAN_CarDvrDataStr.DVR_SDcardStatus = 0;
		CAN_CarDvrDataStr.DVR_ConnectedState = 0;
		CAN_CarDvrDataStr.DVR_SystemStatus = 0;
		CAN_CarDvrDataStr.DVR_DestinationPageResult = 0;
		CAN_CarDvrDataStr.DVD_RestoreFactorySettingResult = 0;
		CAN_CarDvrDataStr.DVR_SDFormatResult = 0;
		CAN_CarDvrDataStr.DVR_PhotographResult = 0;
		CAN_CarDvrDataStr.DVR_CommandResult = 0;
		CAN_CarDvrDataStr.DVD_ProgrammingModeResult = 0;
		CAN_CarDvrDataStr.DVR_CommandList = 0;
		CAN_CarDvrDataStr.DVR_PageAttribute = 0;
		CAN_CarDvrDataStr.DATA5_Reserved = 0;
		CAN_CarDvrDataStr.DVR_CurrentPageNum = 0;
		CAN_CarDvrDataStr.DVR_TotalPageNum = 0;
		CAN_CarDvrDataStr.DVR_ErrorStatus_Reserved = 0;
		CAN_CarDvrDataStr.DVR_ErrorStatus_PowerError = 0;
		CAN_CarDvrDataStr.DVR_ErrorStatus_SystemError = 0;
		CAN_CarDvrDataStr.DVR_ErrorStatus_KeyError = 0;
		CAN_CarDvrDataStr.DVR_ErrorStatus_SDCardError = 0;

		//ver
		CAN_CarDvrVerStr.PrjCode = 0x04;
		CAN_CarDvrVerStr.USERID = 0x02;
		CAN_CarDvrVerStr.DvrVersion_Year = 0;
		CAN_CarDvrVerStr.DvrVersion_Month = 0;
		CAN_CarDvrVerStr.DvrVersion_Day = 0;
		CAN_CarDvrVerStr.DVR_SDTotalCapacity_Integer = 0;
		CAN_CarDvrVerStr.DVR_SDTotalCapacity_Decimals = 0;
		CAN_CarDvrVerStr.DVR_SDResidualCapacity_Integer = 0;
		CAN_CarDvrVerStr.DVR_SDResidualCapacity_Decimals = 0;
	#endif
#endif
	MediaRxCANByteBufferManager.BufferSize = 100;
	MediaRxCANByteBufferManager.Delta = 0;
	MediaRxCANByteBufferManager.pDataBuffer = MediaRxCANByteBuffer;
	MediaRxCANByteBufferManager.ReadPoint = 0;
	MediaRxCANByteBufferManager.WritePoint = 0;
	MediaRxCANByteBufferManager.MsgNum = 0;
	DataInitCodeId = 0x12345678;

	CANUser_ApiInit();
		
}

#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
void	CANUser_VehicleOsVaribleReset(void)
{
	CAN_CarLightDataStr.HmaEnable = 0;
	CAN_AccCtrlStr.DesWarnMode = 0;
	CAN_FcwStr.AutoBrakeEnable = 1;
	CAN_FcwStr.FcwEnable = 1;
	CAN_RcwStr.BsdEnable = 1;
	CAN_RcwStr.CtaEnable = 1;
	CAN_RcwStr.RcwEnable = 1;
	CAN_LdwStr.LdwSensDat = 0;
	CAN_LdwStr.SlaEnable = 1;
}
#endif

ByteBufferMangerStruct *pCAN_GetMediaRxCANByteBuffer(void)
{
	return  &MediaRxCANByteBufferManager;
}

CANKeyStateStruct  *	pCAN_GetCANkeyState(void)
{
	return (&CAN_RcvKeyState);
}

CANVehicleStateStruct *		pCAN_GetVehicleState(void)
{
	return (&CAN_VehicleStateStr);
}

CANStateDataStruct *pCAN_GetCANSysStateStr(void)
{
	return (&CAN_SysStateStr);
}

EOLCfgStruct *pCAN_GetEOLStr(void)		
{
#ifdef UDS_ENABLE_MACRO
	return (&CAN_EOLCfgStr);
#else
	return NULL;
#endif
}

ExtMediaDataStruct	* pCAN_GetVINStr(void)
{
#ifdef UDS_ENABLE_MACRO
	return (&VINDataStr);
#else
	return NULL;
#endif
}

CommonDataStruct	* pCAN_GetCommonStr(void)
{
	return (&CAN_CommonDataStr);
}
/****************************************************************************
* @function:CanAPI_LoadTboxPhoneInfo
 * @brief:get tbox phone number from eeprom
 * @param:"pTboxphone"->store tbox phone number 
                     "Len"->the length of tbox phone number
 * @retval:NULL
 ****************************************************************************/
void CanAPI_LoadTboxPhoneInfo(uint8_t *pTboxphone,uint8_t Len)
{
	uint8_t i;
	CommonDataStruct *pCommData=pCAN_GetCommonStr();
	
	if((NULL==pCommData)||(NULL==pTboxphone)||(Len>11))
	{
		return;
	}
	pCommData->SID=OP_CAN_TX_TBOX_PHONE;
	pCommData->LENGTH=Len+2;
	for(i=0;i<Len;i++)
	{
		pCommData->DATA[i]=pTboxphone[i];
	}
}

//为了兼容长安商用车和乘用车下线配置的功能.增加下线配置的参数... snake20160806
void CANAPI_LoadEOLInfo(uint16_t did,uint8_t*pData, uint8_t len)
{
	uint8_t i=0;
	uint8_t flag = 0;
	EOLCfgStruct *pEOLCfg=pCAN_GetEOLStr();
	
	if((NULL==pData)||(NULL==pEOLCfg))
	{
		return;
	}

	switch(did)
	{

		case DID_ID_F1F8:
			if(len> DID_F1F8_LENGTH)
				return;
			flag = 1;
			break;
		case DID_ID_F1FA:
			if(len> DID_F1FA_LENGTH)
				return;
			//将未使用的位,设置为默认值
			pEOLCfg->EOLState.Param[0] = 0x00;
			pEOLCfg->EOLState.Param[1] = 0x00;
			pEOLCfg->EOLState.Param[2] = 0x00;
			pEOLCfg->EOLState.Param[3] = 0x00;
			pEOLCfg->EOLState.Param[4] = 0x05;
			pEOLCfg->EOLState.Param[5] = 0x09;//(pEOLCfg->EOLState.Param[5] & 0x01) | 0x08; //NVAI
			pEOLCfg->EOLState.Param[6] = 0x00;
			pEOLCfg->EOLState.Param[7] = (pEOLCfg->EOLState.Param[7] & 0x06) | 0x08; //PAC
			pEOLCfg->EOLState.Param[8] = (pEOLCfg->EOLState.Param[8] & 0x01); //RRS
			pEOLCfg->EOLState.Param[9] = 0x04;
			pEOLCfg->EOLState.Param[10] = 0x00;
			pEOLCfg->EOLState.Param[11] = (pEOLCfg->EOLState.Param[11] & 0x38) | 0x40; //DVR TPMS AUX
			pEOLCfg->EOLState.Param[12] = 0x06;
			pEOLCfg->EOLState.Param[13] = 0x01;
			pEOLCfg->EOLState.Param[14] = (pEOLCfg->EOLState.Param[14] & 0x70) | 0x0a; //GPS WIFI GW
			pEOLCfg->EOLState.Param[15] = 0x00;
			
			//snake20161104 协议转换
			pEOLCfg->EOLState.bits.DVRSupport = pData[0] & 0x01;
			pEOLCfg->EOLState.bits.TPMSSupport = (pData[0]>>1)&0x01;
			pEOLCfg->EOLState.bits.PACSupport = ((pData[0]>>2)&0x01) +1;
			pEOLCfg->EOLState.bits.AUXSupport = (pData[0]>>3)&0x01;
			pEOLCfg->EOLState.bits.RRSSupport = (pData[0]>>4)&0x01;//雷达...
			pEOLCfg->EOLState.bits.WIFIAntSupport = (pData[0]>>5)&0x01;//wifi...
			//pEOLCfg->EOLState.bits.NAVISupport = (pData[0]>>6)&0x01;//NAVI
			pEOLCfg->EOLState.bits.GPSAntSupport = (pData[0]>>6)&0x01;//NAVI
			pEOLCfg->EOLState.bits.GWSupport = (pData[0]>>7)&0x01;//GW
			flag = 0;

			#ifdef D_AUX_EOL
				//当配置成不带AUX的时候,将AUX的输入设置为0...
				if(!pEOLCfg->EOLState.bits.AUXSupport)
				{
					g_tMcuDevState.uConnetState.bits.Aux_In = 0;
					_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
					//TaskCAN_debug(_T("----g_tMcuDevState.uConnetState.bits.Aux_In = %d\n",g_tMcuDevState.uConnetState.bits.Aux_In));
				}
			#endif
			break;
		default://invalid eol data
			return;
		
	}	

	if(flag)
		Memory8Copy(pEOLCfg->EOLState.Param, pData, len);
	//FacCfg.FacCfg1.Byte1 = pData[2];//这两个数据的用处????
	//FacCfg.FacCfg2.Byte2 = pData[3];
	
	#if 1
	TaskCAN_debug(_T("CANAPI_LoadEOLInfo....pEOLCfg:%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n",pEOLCfg->EOLState.Param[0],pEOLCfg->EOLState.Param[1],pEOLCfg->EOLState.Param[2],
		pEOLCfg->EOLState.Param[3],pEOLCfg->EOLState.Param[4],pEOLCfg->EOLState.Param[5],pEOLCfg->EOLState.Param[6],pEOLCfg->EOLState.Param[7],pEOLCfg->EOLState.Param[8],pEOLCfg->EOLState.Param[9],
		pEOLCfg->EOLState.Param[10],pEOLCfg->EOLState.Param[11],pEOLCfg->EOLState.Param[12],pEOLCfg->EOLState.Param[13],pEOLCfg->EOLState.Param[14],pEOLCfg->EOLState.Param[15]));
	TaskCAN_debug(_T("CANAPI_LoadEOLInfo.....DVR:%x TPMS:%x PAC:%x AUX:%x RRS:%x WIFI:%x GPS:%x GW:%x\n",pEOLCfg->EOLState.bits.DVRSupport,pEOLCfg->EOLState.bits.TPMSSupport,pEOLCfg->EOLState.bits.PACSupport,
		pEOLCfg->EOLState.bits.AUXSupport,pEOLCfg->EOLState.bits.RRSSupport,pEOLCfg->EOLState.bits.WIFIAntSupport,pEOLCfg->EOLState.bits.GPSAntSupport,pEOLCfg->EOLState.bits.GWSupport));
	#endif
	CANTask_SendApiData(OMS_CAN_TX_SYS, OP_CAN_TX_EOL, 1);	// vivid ensure send eol data to apu
	
}
 
NaviInforamtionStruct * pCAN_GetHUNaviInfo(void)
{
#ifdef HU_API_NAVI_INFO_EN
	return (&HU_NaviInfoDataStr);
#else
	return NULL;
#endif
}

CarSpeedDataStruct* 	pCAN_GetVehicleSpeed(void)
{
#ifdef CAN_API_CAR_SPEED_EN
	return (&CAN_CarSpeedDataStr);
#else
	return NULL;
#endif
}


CarAngleDataStruct* 	pCAN_GetAngleData(void)
{
#ifdef CAN_API_CAR_ANGLE_EN
	return (&CAN_CarAngleDataStr);
#else
	return NULL;
#endif
}


 CarOutsideTempDataStruct* 	pCAN_GetOutsideTempData(void)
{
#ifdef CAN_API_AC_OUTTEMP_EN
	return (&CAN_OutsideTempDataStr);
#else
	return NULL;
#endif
}


CarMaintainInfoStruct *		pCAN_GetCarMaintainState(void)
{
#ifdef CAN_API_CAR_MAINTAIN_EN
	return (&CAN_CarMaintainState);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetFrontACData
 * @brief  	Get Front AirConditioner information Data Structure
 * @param  	null				
 * @retval 	return the point of the AC structure.
 ****************************************************************************/
 FrontACDataStruct	*pCAN_GetFrontACData(void)
{
#ifdef CAN_API_AC_FRONT_EN
	return (&CAN_FrontACDataStr);
#else
	return NULL;
#endif
}


 CarFuelLevelDataStruct	*pCAN_GetFuelLevelData(void)
{
#ifdef CAN_API_AC_FRONT_EN
	return (&CAN_FuelLevelDataStr);
#else
	return NULL;
#endif
}



/****************************************************************************
* @function	CAN_GetACData
 * @brief  	Get Rear AirConditioner information Data Structure
 * @param  	null				
 * @retval 	return the point of the AC structure.
 ****************************************************************************/
 RearACDataStruct	*pCAN_GetRearACData(void)
{
#ifdef CAN_API_AC_REAR_EN
	return (&CAN_RearACDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetTPMSData
 * @brief  	Get TPMS information Data Structure
 * @param  	null				
 * @retval 	return the point of the TPMS structure.
 ****************************************************************************/
TPMSDataStruct	*pCAN_GetTPMSData(void)
{
#ifdef CAN_API_TPMS_EN
	return (&CAN_TPMSDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetLightData
 * @brief  	Get Light information Data Structure
 * @param  	null				
 * @retval 	return the point of the light structure.
 ****************************************************************************/
CarLightDataStruct*	pCAN_GetCarLightData(void)
{
#ifdef CAN_API_CAR_LIGHT_EN
	return (&CAN_CarLightDataStr);
#else
	return NULL;
#endif
}


CarDoorLockDataStruct*	pCAN_GetCarDoorLockData(void)
{
#ifdef CAN_API_CAR_LIGHT_EN
	return (&CAN_CarDoorLockStr);
#else
	return NULL;
#endif
}



/****************************************************************************
* @function	CAN_GetWiperData
 * @brief  	Get Wiper information Data Structure
 * @param  	null				
 * @retval 	return the point of the Wiper structure.
 ****************************************************************************/
CarWiperDataStruct*pCAN_GetCarWiperData(void)
{
#ifdef CAN_API_CAR_WIPER_EN
	return (&CAN_CarWiperDataStr);
#else
	return NULL;
#endif
}

FuelLevelStruct* pCAN_GetCarFuelLevelData(void)
{
#ifdef CAN_FUEL_LEVEL_WARN_EN
	return (&CAN_FuelLevelStr);
#else
	return NULL;
#endif
}

CanPmStruct* pCAN_GetCarCanPmData(void)
{
#ifdef CAN_FUEL_LEVEL_WARN_EN
	return (&CAN_CanPmStr);
#else
	return NULL;
#endif
}



/****************************************************************************
* @function	CAN_GetwindowData
 * @brief  	Get window information Data Structure
 * @param  	null				
 * @retval 	return the point of the windowData structure.
 ****************************************************************************/
CarWindowDataStruct*	pCAN_GetCarWindowData(void)
{
#ifdef CAN_API_CAR_WINDOW_EN
	return (&CAN_CarWindowDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetDoorStateData
 * @brief  	Get DoorState information Data Structure
 * @param  	null				
 * @retval 	return the point of the DoorState structure.
 ****************************************************************************/
CarDoorStateDataStruct*	pCAN_GetDoorStateData(void)
{
#ifdef CAN_API_CAR_DOOR_EN
	return (&CAN_CarDoorStateStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetSeatData
 * @brief  	Get Seat information Data Structure
 * @param  	null				
 * @retval 	return the point of the Seat structure.
 ****************************************************************************/
CarSeatDataStruct*		pCAN_GetSeatData(void)
{
#ifdef CAN_API_CAR_SEAT_EN
	return (&CAN_CarSeatDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetRearMirrorData
 * @brief  	Get Rear Mirror information Data Structure
 * @param  	null				
 * @retval 	return the point of the Rear Mirror structure.
 ****************************************************************************/
CarRMirrorDataStruct*	pCAN_GetRearMirrorData(void)
{
#ifdef CAN_API_CAR_RMIRROR_EN
	return (&CAN_CarRMirrorDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetEcuData
 * @brief  	Get Ecu information Data Structure
 * @param  	null				
 * @retval 	return the point of the Ecu structure.
 ****************************************************************************/
CarEcuDataStruct*	pCAN_GetEcuData(void)
{
#ifdef CAN_API_CAR_ECU_STATUS_EN
	return (&CAN_CarEcuDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetBSDData
 * @brief  	Get BSD information Data Structure
 * @param  	null				
 * @retval 	return the point of the BSD structure.
 ****************************************************************************/
CarBSDDataStruct*	pCAN_GetBSDData(void)
{
#ifdef CAN_API_CAR_BSD_EN
	return (&CAN_CarBSDDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetCarPackData
 * @brief  	Get CarPack information Data Structure
 * @param  	null				
 * @retval 	return the point of the CarPack structure.
 ****************************************************************************/
CarPACDataStruct*	pCAN_GetCarPACData(void)
{
#ifdef CAN_API_CAR_PAC_EN
	return (&CAN_CarPACDataStr);
#else
	return NULL;
#endif
}
/****************************************************************************
* @function	CAN_GetTBOXData
 * @brief  	Get TBOX information Data Structure
 * @param  	null				
 * @retval 	return the point of the TBOX structure.
 ****************************************************************************/
TBOXDataStruct*	pCAN_GetTBOXData(void)
{
#ifdef CAN_API_CAR_TBOX_EN
	return (&CAN_TBOXDataStr);
#else
	return NULL;
#endif
}

TboxTUIDStruct*	pCAN_GetTboxTUIDData(void)
{
#ifdef CAN_API_CAR_TBOX_EN
	return (&CAN_TboxTUIDStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetAVMData
 * @brief  	Get AVM information Data Structure
 * @param  	null				
 * @retval 	return the point of the AVM structure.
 ****************************************************************************/
CarAVMDataStruct*	pCAN_GetAVMData(void)
{
#ifdef CAN_API_CAR_AVM_EN
	return (&CAN_CarAVMDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetODOData
 * @brief  	Get ODO information Data Structure
 * @param  	null				
 * @retval 	return the point of the ODO structure.
 ****************************************************************************/
CarODODataStruct*	pCAN_GetODOData(void)
{
#ifdef CAN_API_CAR_ODO_EN
	return (&CAN_CarODODataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetSystemData
 * @brief  	Get System information Data Structure
 * @param  	null				
 * @retval 	return the point of the System structure.
 ****************************************************************************/
CarSystemDataStruct*	pCAN_GetSystemData(void)
{
#ifdef CAN_API_CAR_SYS_EN
	return (& CAN_CarSystemDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetPEPSData
 * @brief  	Get PEPS information Data Structure
 * @param  	null				
 * @retval 	return the point of the PEPS structure.
 ****************************************************************************/
CarPEPSDataStruct*	pCAN_GetPEPSData(void)
{
#ifdef CAN_API_CAR_PEPS_EN
	return (&CAN_CarPEPSDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetSeatHeatData
 * @brief  	Get SeatHeat information Data Structure
 * @param  	null				
 * @retval 	return the point of the SeatHeat structure.
 ****************************************************************************/
ACSeatHeatDataStruct*	pCAN_GetSeatHeatData(void)
{
#ifdef CAN_API_AC_SEATHEAT_EN
	return (&CAN_SeatHeatDataStr);
#else
	return NULL;
#endif
}

/****************************************************************************
* @function	CAN_GetRadarData
 * @brief  	Get Radar information Data Structure
 * @param  	null				
 * @retval 	return the point of the Radar structure.
 ****************************************************************************/
RadarDataStruct 	*pCAN_GetRadarData(void)
{
#ifdef CAN_API_RADAR_EN
	return (&CAN_RadarDataStr);
#else
	return NULL;
#endif
}
/****************************************************************************
* @function	CAN_GetRadarStatusData
 * @brief  	Get RadarStatus information Data Structure
 * @param  	null				
 * @retval 	return the point of the RadarStatus structure.
 ****************************************************************************/
RadarStatusDataStruct*	pCAN_GetRadarStatusData(void)
{
#ifdef CAN_API_RADAR_EN
	return (&CAN_RadarStatusDataStr);
#else
	return NULL;
#endif
}
/****************************************************************************
* @function	CAN_GetDTVStateData
 * @brief  	GetDTVState information Data Structure
 * @param  	null				
 * @retval 	return the point of the DTVState structure.
 ****************************************************************************/
DTVStateInfoStruct*	pCAN_GetDTVStateData(void)
{
#ifdef CAN_API_DTV_EN
	return (&CAN_DTVStateInfoStr);
#else
	return NULL;
#endif
}

FCPVersionStruct* 		pCAN_GetFCPVersionData(void)
{
	return (&CAN_FCPVersionStr);
}

DTVVersionStruct	*	pCAN_GetDTVVersionData(void)
{
#ifdef CAN_API_DTV_EN
	return (&CAN_DTVVersionStr);
#else
	return NULL;
#endif
}
CarECOInfoStruct *pCAN_GetVehicleECOData(void)
{
#ifdef CAN_API_CAR_ECO_EN
	return (&CAN_ECOInfoStr);
#else
	return NULL;
#endif
}


CarDvrDataStruct*	pCAN_GetDvrData(void)
{
#ifdef CAN_API_DVR_INFO_EN
	return (&CAN_CarDvrDataStr);
#else
	return NULL;
#endif
}

CarDvrVerStruct*	pCAN_GetDvrVer(void)
{
#ifdef CAN_API_DVR_INFO_EN
	return (&CAN_CarDvrVerStr);
#else
	return NULL;
#endif
}

CarPEPSDataStruct *pCAN_GetVehiclePEPSData(void)
{
#ifdef CAN_API_CAR_PEPS_EN
	return (&CAN_CarPEPSDataStr);
#else
	return NULL;
#endif
}

CarAccCtrlStruct* pCAN_GetVehicleAccCrlData(void)
{
	return (&CAN_AccCtrlStr);
}

CarFcwStruct* pCAN_GetFcwData(void)
{
	return (&CAN_FcwStr);
}


CarRcwStruct* pCAN_GetRcwData(void)
{
	return (&CAN_RcwStr);
}

CarLdwSensStruct* pCAN_GetLdwData(void)
{
	return (&CAN_LdwStr);
}



/****************************************************************************
 * **                                        FILE END
****************************************************************************/


