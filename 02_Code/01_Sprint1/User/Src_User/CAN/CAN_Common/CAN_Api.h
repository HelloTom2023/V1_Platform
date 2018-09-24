/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CAN_Api.h
* Target MCU:		V850SJ3
* Module:
* Summary:		CAN module Api interface to other module to exchange data ram
*				the header file
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
#ifndef    _CAN_API_H
#define    _CAN_API_H

#ifdef _CAN_API_C
#define CAN_API
#else
#define CAN_API     extern
#endif

#define CAN_API_TPMS_EN
#define CAN_API_OBD_EN
#define CAN_API_RADAR_EN
#define CAN_API_DTV_EN
/*-----------------------------------------------*/
#define CAN_API_CAR_LIGHT_EN
#define CAN_API_CAR_WIPER_EN
#define CAN_API_CAR_WINDOW_EN
#define CAN_API_CAR_DOOR_EN
#define CAN_API_CAR_MAINTAIN_EN
#define CAN_API_CAR_ECU_STATUS_EN
#define CAN_API_CAR_BSD_EN
#define CAN_API_CAR_SYS_EN
#define CAN_API_CAR_PEPS_EN
#define CAN_API_CAR_SEAT_EN
#define CAN_API_CAR_RMIRROR_EN
#define CAN_API_CAR_TBOX_EN
#define CAN_API_CAR_AVM_EN
#define CAN_API_CAR_ODO_EN
#define CAN_API_CAR_PAC_EN
#define CAN_API_CAR_SPEED_EN
#define CAN_API_CAR_ANGLE_EN
#define CAN_API_CAR_ECO_EN
#define CAN_API_CAR_DOOR_LOCK_EN
/*-----------------------------------------------*/
#define CAN_API_AC_FRONT_EN
#define CAN_API_AC_REAR_EN
#define CAN_API_AC_SEATHEAT_EN
#define CAN_API_AC_OUTTEMP_EN

#define CAN_API_IP_FUEL_LEVEL_EN


#define HU_API_NAVI_INFO_EN

#define CAN_API_DVR_INFO_EN

#define CAN_FUEL_LEVEL_WARN_EN

#define CAN_PRJ_ID_CHANA_C201		0x00
#define CAN_PRJ_ID_CHANA_S301		0x01
#define CAN_PRJ_ID_CHANA_CD101	        0x02
#define CAN_PRJ_ID_CHANA_S401		0x03
#define CAN_PRJ_ID_CHANA_R103H	        0x04
#define CAN_PRJ_ID_ZOTYE_B17		        0x30

#define USERID_APU_TX_DVR_SETREQ		0x01
#define USERID_APU_TX_DVR_VER       0X02

#define CAR_TYPE   (CAR_TYPE_SEL_DEFAULT)

#pragma pack(1)


typedef struct{
uint8_t   LENGTH;
uint8_t   SID;
uint8_t  Lamp;
uint8_t  Atmpspher ;
uint8_t  lightness ;
uint8_t lightOffDelay;
uint8_t lightBlinkTime;
uint8_t HmaEnable;	//自动远光
uint8_t DriveLightEnable;//行车灯
}CarLightDataStruct;


typedef struct{
uint8_t   LENGTH;
uint8_t   SID;
uint8_t   DoorOpenMode; // 四门或驾驶门
uint8_t   DriveLock;//行车自动落锁
uint8_t   ParkUnlock;//驻车自动解锁
}CarDoorLockDataStruct;


typedef struct{
	uint8_t   LENGTH;
      uint8_t   SID;
	uint8_t FrontWiper  ;
	uint8_t RearWiper;
}CarWiperDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
	uint8_t FL_Window ;
	uint8_t FR_Window  ;
	uint8_t RL_Window  ;
	uint8_t RR_Window  ;
	uint8_t HeadWindow  ;
}CarWindowDataStruct;

typedef struct{	
	uint8_t   LENGTH;
        uint8_t   SID;
/*-----------DATA[3]--------------------------------*/
	uint8_t Reserved		:1;   			//bit0	
	uint8_t  sunroof_door_satus	:1;		//bit1
	uint8_t  Engine_door_Status   :1;		/*引擎盖bit2*/
	uint8_t  RearBag_Status   		:1;		//bit3
	uint8_t  RR_CarDoor_Status   :1;		//bit4
	uint8_t  RL_CarDoor_Status   :1;		//bit5
	uint8_t  FR_CarDoor_Status   :1;		//bit6
	uint8_t  FL_CarDoor_Status   :1;		//bit7

}CarDoorStateDataStruct;

typedef struct{
	uint8_t   LENGTH;
        uint8_t   SID;
/*-----------DATA[3]--------------------------------*/
	uint8_t  FL_Seat    :4;
	uint8_t  FR_Seat    :4;
/*-----------DATA[4]--------------------------------*/
	uint8_t  RL_Seat    :4;
	uint8_t  RR_Seat    :4;
/*-----------DATA[4]--------------------------------*/
	uint8_t SeatAutoSet;
}CarSeatDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
	uint8_t Left_RMirror  ;
	uint8_t Right_RMirror;
	uint8_t RearAssist		:2;
	uint8_t RearAutoFold		:2;
	uint8_t  Reserved		:4;
}CarRMirrorDataStruct;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
	/* (unit: %)*/
	uint8_t SpareOilPercent;
	/* (unit: 0.1L)*/
	uint16_t SpareOil;
	/* (unit: %)*/
	uint8_t SpareBattPercent;		/*used for battary driver vehicle */
	/* (unit: 0.1L/100km)*/
	uint8_t OilConsumer;			/*oil consumer every 100km */
	/*(unit: 0.015L/100ms)*/
	uint8_t OilConsumerMs;          /*oil consumer every 100ms */
	/*--------------------------------------------------*/
	/* (unit: 0.1km) */
	uint8_t TotalMileageLbit;			/*total mileage data low bit  */
	uint8_t TotalMileageMbit;		/*total mileage data middle bit */
	uint8_t TotalMileageHbit;		/*total mileage data high  bit */
	/*--------------------------------------------------*/
	/* (unit: 0.1km) */
	uint8_t CurOilMileageLbit;		/*current oil/batt mileage low bit */
	uint8_t CurOilMileageMbit;		/*current oil/batt mileage middle bit */
	uint8_t CurOilMileageHbit;		/*current oil/batt mileage high bit s*/
	/*-----------DATA[20-23]--------------------------------*/
	uint8_t CarMaintainMileLbit;
	uint8_t CarMaintainMileHbit;
	/*--------------------------------------------------*/
	/*-----------S401 Modify________________________*/
	uint32_t SettingMileage;
	uint8_t RemindSwitch;
	uint8_t RemindTime;

}CarMaintainInfoStruct;




typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
	/*------每一个位表示一个ECU，0-ECU正常，1-ECU故障------*/
	/*-----------DATA[3]--------------------------------*/
	uint8_t BCM_System      :1;          /*车身控制系统*/
	uint8_t ABS_System      :1;          /*防抱死控制系统*/
	uint8_t MIL_System      :1;          /*电喷控制系统*/
	uint8_t EPB_System      :1;           /*电子驻车系统*/
	uint8_t Electronic_Program      :1;/*电子稳定程序*/
	uint8_t ElecLock_System      :1;   /*电子转向锁控制系统*/
	uint8_t SafeAir_System      :1;    /*安全气囊系统*/
	uint8_t PEP_System      :1;         /*无钥匙进入系统*/
	/*-----------DATA[4]--------------------------------*/
       uint8_t LampAimSys    :1;  /*大灯动态调光系统*/
       uint8_t TPM_System   :1 ;  /*胎压监测系统*/
       uint8_t AC_System   :1 ;    /*空调系统*/
       uint8_t PAC_System  :1;     /*泊车辅助系统*/
       uint8_t IP_System  :1 ;       /*仪表*/
       uint8_t TBOX_System  :1;  /*TBOX*/
       uint8_t BSD_System  :1 ;  /*盲区检测系统*/
	uint8_t RRS_System  :1 ;  /*倒车雷达*/
	/*--------------------------------------------------*/
	uint8_t EPS_System			:1;	/* EPS助力转向故障 */
	uint8_t EBD_System			:1;	/* EBD故障 */
	uint8_t Engine_Error			:1;	/* 发动机故障 */
	uint8_t Refrigerant_TEMP		:1;	/* 冷却液温度故障 */
	uint8_t Engine_Speed			:1;	/* 发动机速度故障 */
	uint8_t Throttle_Position		:1;	/* 节气门位置故障 */
	uint8_t ACC_Pedal				:1;	/* 加速踏板故障 */
	uint8_t Reserved				:1;	/* 保留 */
}CarEcuDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
/*-----------DATA[3]--------------------------------*/
	uint8_t Left_BSD_Status    :4  ;
	uint8_t Right_BSD_Status  :4 ;
/*-----------DATA[4]--------------------------------*/
       uint8_t Left_Senser_Status  :1 ;
       uint8_t Right_Senser_Status  :1 ;
       uint8_t Reserved1  :5 ;
	uint8_t Communication_status  :1;
}CarBSDDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
       uint8_t   ParkMode;/*0x00:路边停车0x01:倒车入库模式0x02普通镜头模式*/
}CarPACDataStruct;

typedef struct{
	uint8_t    LENGTH;
       uint8_t     SID;
       uint8_t   SpeedLbyte;
       uint8_t   SpeedHbyte;   
}CarSpeedDataStruct;

typedef struct{
	uint8_t    LENGTH;
       uint8_t     SID;
       uint8_t   Angle;		/*vehicle engine angle data (the wheel angle Range: -90~90)*/
}CarAngleDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
       uint8_t 	Car_TBOX_Request		:2;
	uint8_t	PartChange				:2;
	uint8_t	Reserved1				:3;
	uint8_t	Exist					:1;
       uint8_t 	Car_TBOX_PhoneStatus;
}TBOXDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
       uint8_t   Data[16];
}TboxTUIDStruct;


typedef struct{
       uint8_t   LENGTH;
       uint8_t   SID;
       
/*-----------DATA[0]--------------------------------*/
	uint8_t CarAvmState;
	
/*-----------DATA[1]--------------------------------*/
	uint8_t CarAVMReq:1 ;
	uint8_t BlindReq:1;
	uint8_t BlindReqBk:1;//snake20161202
	uint8_t  ADIINITFlag:1;
	 
}CarAVMDataStruct;

typedef struct{
	uint8_t LENGTH;
	uint8_t SID;
	uint8_t	TotalOdometerL;	
	uint8_t	TotalOdometerM;	
	uint8_t	TotalOdometerH;	
}CarODODataStruct;

typedef struct{
	uint8_t   LENGTH;
        uint8_t   SID;
	uint8_t 	Car_Gear_Position;
/*-----------DATA[1]--------------------------------*/
	uint8_t 	ACC_Status     :2;
	uint8_t 	HandBrake_Status     :2;
	uint8_t	PostionLamp_status:2;
	uint8_t	Reverse_Status	:2;
/*-----------DATA[2]--------------------------------*/
	uint8_t  Engine_Status    :2;
	uint8_t  Vehicle_Cruise   :2;
	uint8_t Reserved2           :4;
}CarSystemDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
	uint8_t 	Key_Position_Status  ;
       uint8_t 	Remote_information;
	uint8_t	LockSignal;
}CarPEPSDataStruct;


typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
       uint8_t   FuelLevel;
}CarFuelLevelDataStruct;


/********主动安全********/

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
       uint8_t   DesWarnMode;
}CarAccCtrlStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
       uint8_t   FcwEnable;
       uint8_t   AutoBrakeEnable;
}CarFcwStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
       uint8_t   BsdEnable;	//并线辅助
       uint8_t   CtaEnable;	//倒车横向预警
       uint8_t   RcwEnable;	//后追尾预警
}CarRcwStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
       uint8_t   LdwSensDat;	//
       uint8_t   SlaEnable;	//

}CarLdwSensStruct;
/********************************/

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
/*-----------DATA[0]--------------------------------*/
	uint8_t ACPowerSwitch :2;// 00: off, 01: on, 11: invalid
       uint8_t ACSwitch            :2;// 00: off, 01: on, 11: invalid
       uint8_t reserved                     :2;//保持APU和MCU协议不变，填补空位
	uint8_t DualSwitch		:2;	// 00: OFF, 01: OPEN, 11: Invalid
	
/*-----------DATA[1-3]--------------------------------*/
	uint8_t 		ACState;
	uint8_t		OutsideTemperature;
	uint8_t		InsideTemperature;
 /*-----------DATA[4]--------------------------------*/
       uint8_t FrontDefrost		:2;   // 00: OFF, 01: OPEN, 11: Invalid
	uint8_t RearDefrost		:2;	// 00: OFF, 01: OPEN, 11: Invalid
	uint8_t AutoMode		:4;	//00: off; 01: auto small, 10: auto big, 11: invalid
 /*-----------DATA[5-7]--------------------------------*/
      uint8_t LeftTemperature;	// 0xff: invalid; 0xfe: LO; 0xfd: HI, 0x00~0x1f: (vitual temp -15) * 2
      uint8_t RightTemperature;	// same with 'LeftTemperature'
     // uint8_t WindMode;
      uint8_t WindLevel;
/*-----------DATA[8]--------------------------------*/
       uint8_t CycleMode		:3;	// 00: inner cycle, 01: outside cycle, 10: inner cycle,:11:outside cycle,100:invalid


}FrontACDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
/*-----------DATA[0]--------------------------------*/
	uint8_t  ACPowerSwitch :2;// 00: off, 01: on, 11: invalid
       uint8_t 	ACSwitch            :2;// 00: off, 01: on, 11: invalid
       uint8_t CycleMode		:2;	// 00: inner cycle, 01: outside cycle 10: auto, 11:invalid
	uint8_t DualSwitch		:2;	// 00: OFF, 01: OPEN, 11: Invalid
 /*-----------DATA[1]--------------------------------*/
       uint8_t FrontDefrost		:2;   // 00: OFF, 01: OPEN, 11: Invalid
	uint8_t RearDefrost		:2;	// 00: OFF, 01: OPEN, 11: Invalid
	uint8_t AutoMode		:4;	//00: off; 01: auto small, 10: auto big, 11: invalid
 /*-----------DATA[2-5]--------------------------------*/
      uint8_t LeftTemperature;	// 0xff: invalid; 0xfe: LO; 0xfd: HI, 0x00~0x1f: (vitual temp -15) * 2
      uint8_t RightTemperature;	// same with 'LeftTemperature'
      uint8_t WindMode;
      uint8_t WindLevel;
 /*------------DATA[6]--------------------------------*/
	uint8_t ECOMode			:2;  // 00: off, 01: on, 11: invalid
 	uint8_t AirSensisty		:2;      // 00: LO, 01: MID, 10: HI 11:invalid
      uint8_t AirQualityFlag		:2; // 00: off, 01: on, 11: invalid
	uint8_t PollenFilter	        :2; // 00: off, 01: on, 11: invalid
 /*------------DATA[7]--------------------------------*/
       uint8_t RearMrrorHeat           :2;	// 00: off, 01: on, 11: invalid
       uint8_t  Reserved                   :2;
	 uint8_t  WindAreaControl    :4;
//-------------------------------------------------------------------------
}RearACDataStruct;

typedef struct{
	uint8_t   LENGTH;
	uint8_t   SID;
	uint8_t   OutsideTempValue;	/*outside temperature: -40~+85: (vitual temp +40)*2  */
}CarOutsideTempDataStruct;

typedef struct{
	uint8_t   LENGTH;
	uint8_t   SID;
	uint8_t FL_Seat_Heat;
	uint8_t FR_Seat_Heat;
	uint8_t Rear_Seat_Heat;
}ACSeatHeatDataStruct;

typedef struct{
	uint8_t   	LENGTH;
       uint8_t   	SID;
 /*------------DATA[0]--------------------------------*/	
	uint8_t 	RadarSysStatus 		:2; 
 	uint8_t	RadarFailureFlag	:1;
	uint8_t 	Reserved       		:5; 
 /*------------DATA[1]--------------------------------*/	
 	uint8_t	NearestPosition		:4;
	uint8_t	NearestDistance		:4;
  /*------------DATA[2]--------------------------------*/	
  	uint8_t	LRM_Distance			:4;
  	uint8_t	RRM_Distance			:4;
  /*------------DATA[3]--------------------------------*/		
	uint8_t	LRC_Distance			:4;
	uint8_t	RRC_Distance			:4;
  /*------------DATA[4]--------------------------------*/	
	uint8_t	LFC_Distance		:4;
	uint8_t	RFC_Distance		:4;
  /*------------DATA[5]--------------------------------*/	
	uint8_t	RFM_Distance		:4;
	uint8_t	LFM_Distance		:4; 
  /*------------DATA[6]--------------------------------*/	
      uint8_t	RRS_Distance		:4;
      uint8_t	LRS_Distance		:4;
  /*------------DATA[7]--------------------------------*/
       uint8_t	RFS_Distance		:4;
	uint8_t	LFS_Distance		:4;

}RadarStatusDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
	uint8_t 	FL_Radar_Info;
	uint8_t 	FLM_Radar_Info;
	uint8_t 	FR_Radar_Info;
	uint8_t 	FRM_Radar_Info;
	uint8_t 	RL_Radar_Info;
	uint8_t 	RLM_Radar_Info;
	uint8_t 	RRM_Radar_Info;
	uint8_t 	RR_Radar_Info;
}RadarDataStruct;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
 /*------------DATA[3]--------------------------------*/	
    uint8_t TpmsOnlineState          :1;//0:节点丢失   1:节点在线
 	uint8_t TirePresureSignalStatus :1;
	uint8_t	SignalStatus		:1;
	uint8_t	RR_temperatureWarn	:1;
	uint8_t	RL_temperatureWarn		:1;
	uint8_t	FR_temperatureWarn	:1;
	uint8_t	FL_temperatureWarn		:1;
	uint8_t	SystemFailure	:1;
  /*-------------------------------------------------*/	
	uint8_t	 FL_tyrePressure;
	uint8_t	 FR_tyrePressure;
	uint8_t	 RL_tyrePressure;
	uint8_t	 RR_tyrePressure;
	uint8_t	 FL_tyreTemperature;
	uint8_t	 FR_tyreTemperature;
	uint8_t	 RL_tyreTemperature;
	uint8_t	 RR_tyreTemperature;
  /*-------------------DATA[12]------------------------------*/
  	uint8_t	 FR_WarnStatus          :4;
	uint8_t	 FL_WarnStatus          :4;
  /*-------------------DATA[13]------------------------------*/	
  	uint8_t	 RR_WarnStatus          :4;
    uint8_t	 RL_WarnStatus          :4;
}TPMSDataStruct;

typedef struct{
	uint8_t   LENGTH;
       uint8_t   SID;
	uint8_t year;		//00~FE:    2000      0XFF: not valid
	uint8_t month;	//01~0c:   ; 0xff: not valid
	uint8_t day;
	uint8_t weekday;
	uint8_t hour;		//used 24hour.
	uint8_t minite;
	uint8_t second;
}DateInforStruct;


typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
	uint8_t 	AccBrakeState;		//bit0~3: ACC STATE; bit4~7: brake state; 0: OFF; 1:ON; 0x0f: invalid
	uint8_t	GearShiftState;		
	uint8_t	IllState;
	uint8_t	ReverseState;		//Reverse State: bit0~3: 0: OFF, 1: ON, 0x0f: invalid
	uint8_t	Reserve;
}CarSwitchInfoStruct;

/* Attention: next eco Structure is different with R103 which has been used by V8 Wanghongbo
2015-10-24 marked */
typedef struct
{
	uint8_t   LENGTH;
       uint8_t   SID;
	uint8_t 	EngineSpeedL;	
	uint8_t	EngineSpeedH;
	uint8_t	RealEngTorqL;		
	uint8_t	RealEngTorqH;	
	uint8_t 	TorqueConstant;
	uint8_t 	FrictionTorqL;
	uint8_t	FrictionTorqH;
	uint8_t	SpeedL;
	uint8_t	SpeedH;
	uint8_t	TotalOdometerL;	
	uint8_t	TotalOdometerM;	
	uint8_t	TotalOdometerH;	
	uint8_t	FuelConsumptionL;
	uint8_t	FuelConsumptionH;
	//uint8_t	EngineThrottlePos;		/*delete this signal */
	uint8_t    AccPedal;
	/*---------------------------*/
	uint8_t	EngineStatus		:2;
	uint8_t	AccPowerStatus		:2;
	uint8_t 	ClutchPedalStatus	:2;
	uint8_t	BrakePedalStatus	:2;
	/*---------------------------*/
	uint8_t 	Reserved1			:1;		/*blank space */
	uint8_t	KeyInsert			:1;		/*vehicle key insert/not */
	uint8_t	FuelCutOff			:1;
	uint8_t	IdleStopStatus		:1;
	uint8_t	ActualGear			:4;
	/*-add it according to DVD_S301_CAN_Matrix(ver:V4.9)*/
	uint8_t     CruiseControlStatus :2;//00=off,01=active,10=standby,11=error
	uint8_t     Reserved2:6;	
	uint8_t	GearDisplay;
}CarECOInfoStruct;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
 /*------------DATA[0]--------------------------------*/	
 	uint8_t Exist				:1;
	uint8_t StationType    		:2;	/*current program type */
 	uint8_t Signal     			:2;
	uint8_t WorkMode			:2;
	uint8_t Broadcast			:1; 
 /*------------DATA[1]--------------------------------*/	
	uint8_t CurrentStationIndex;
 /*------------DATA[2]--------------------------------*/	
 	uint8_t TotalStationNum;
}DTVStateInfoStruct;

typedef struct
{
       uint8_t   LENGTH;
//       uint8_t   GID;
       uint8_t   SID;
 /*------------DATA[0~3]--------------------------------*/	
 	uint8_t  ModuleVersion[4];
 /*------------DATA[4~7]--------------------------------*/	
	uint8_t  BoxVersion[4];
}DTVVersionStruct;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
 /*------------DATA[0]--------------------------------*/	
 	uint8_t  VerHighByte;
 /*------------DATA[1]--------------------------------*/	
	uint8_t  VerLowByte;
}FCPVersionStruct;


typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
 	uint8_t   DATA[50];
}CommonDataStruct;

typedef struct
{
	uint8_t   LENGTH;
	uint8_t   SID;
	
	//uint8_t  Param[16];
	//snake20161104 便于平台化,进行协议转换
	union                          //区分具体的标志位,使用的时候方便
	{
		uint8_t Param[16];
		struct
		{
 			//Param[0]
			bit_t Language                     			   :4; //byte0.0~3  0:Chinese  1:English
			bit_t SellArea                     			   :4; // byte0.4~7 销售区域
			//Param[1]
			bit_t DVDAreaCode               			   :4; //byte1.0~3  DVD区域码  0:无DVD
			bit_t Byte1_Reserve  						   :4; //byte1.4~7  Reserve
			//Param[2]
			uint8_t Byte2_Reserve;   //byte2.0~7  Reserve
			//Param[3]
			bit_t ECOSupport       						   :1; //byte3.0  0:not Support  1:Support
			bit_t TTSSupport       						   :1; //byte3.1  语音设别
			bit_t RDSSupport       						   :1; //byte3.2  收音RDS
			bit_t AppStoreSupport  					   :1; //byte3.3 AppStore
			bit_t Byte3_Reserve  						   :4; //byte3.4~7  reserve
			//Param[4]
			bit_t ShowTime                 				   :1; //byte4.0 时间显示
			bit_t ShowOutsideTemperature  			   :1; //byte4.1 车外温度显示
			bit_t ShowACState              			   :1; //byte4.2  空调状态显示
			bit_t ShowMaintenance          			   :1; //byte4.3  保养提示
			bit_t Byte4_Reserve             			   :4; //byte4.4~7  Reserve
			//Param[5]
			bit_t NAVISupport                 			   :1; //byte5.0  导航功能
			bit_t LightAdjustType          			   :2; //byte5.1~2  调光类型  0:ILL 1:调光控制器 2:ILL+调光控制器
			bit_t LightControlType         			   :2; //byte5.3~4 调光控制器类型  0:无 1:PWM 2:CAN
			bit_t Byte5_Reserve            			   :3; //byte5.5~7  reserve
			//Param[6]
			uint8_t Byte6_Reserve;   //byte6.0~7  Reserve
			//Param[7]
			bit_t AVMSupport               				   :1; //byte7.0   360全景
			bit_t PACSupport       						   :2; //byte7.1~2 摄像头/动态划线 0:无摄像头 1:无泊车图标  2:有泊车图标 
			bit_t BlindAreaSupport     				   :1; //byte7.3   盲区
			bit_t CameraType          					   :3; //byte7.4~6  摄像头种类 0:invalid  1:type1 2:type2 3:type3
			bit_t AutoParkSupport      				   :1;//byte7.7  自动泊车
			//Param[8]
			bit_t RRSSupport                              :1; //byte8.0  倒车雷达
			bit_t RRSTpye                                 :2; //byte8.1~2 倒车雷达类型   0:六探头 1:八探头  2:12探头
			bit_t Byte8_Reserve                           :5;   //byte8.3~7  Reserve
			//Param[9]
			bit_t CALinkSupport     					   :1; //byte9.0 CA_Link
			bit_t MirrorLinkSupport     				   :1; //byte9.1 mirror_Link
			bit_t CarLifeSupport     					   :1; //byte9.2 Carlife
			bit_t CarPlaySupport     					   :1; //byte9.3 CarPlay
			bit_t Byte9_Reserve       					   :4; //byte9.4~7 reserve
			//Param[10]
			uint8_t Byte10_Reserve;   //byte10.0~7  Reserve
			//Param[11]
			bit_t DTVSupport     						   :1; //byte11.0   DTV功能
			bit_t DVDBoxSupport  			               :1; //byte11.1   DVD-BOX
			bit_t CDBoxSupport   						   :1; //byte11.2   CD-BOX
			bit_t DVRSupport   							   :1; //byte11.3   DVR
			bit_t TPMSSupport   						   :1; //byte11.4   TPMS  //bit_t TBoxSupport   :1; //byte11.4   T-Box
			bit_t AUXSupport   							   :1; //byte11.5   AUX
			bit_t MICConfig   							   :2; //byte11.6~7  0:无MIC  1:单MIC  2:双MIC
			//Param[12]
			bit_t FoldMirrorSupport 					   :1; //byte12.0  0:无折叠后视镜  1:有折叠后视镜
			bit_t TFTResolution      			   	 	   :1; //byte12.1  显示屏分辨率
			bit_t TouchType           					   :1; //byte12.2 触摸屏类型 0:电阻屏  1:电容屏
			bit_t BehindTFTSupport    					   :1; //byte12.3 后枕屏接续
			bit_t MirrorSetSupport     				   :1; //byte12.4  后视镜倒车辅助设置
			bit_t SeatSetSupport        				   :1; //byte12.5 座椅礼让设置
			bit_t AmbientLigthSupport    				   :1; //byte12.6 氛围灯调节
			bit_t BackWiperSupport         			   :1; //byte12.7 倒车后雨刮刮刷设置
			//Param[13]
			bit_t PanelCheckType        				   :1; //byte13.0   0:ADC  1:私有CAN
			bit_t CarType                  		 	       :4; //byte13.1~4 
			bit_t ButtonType             				   :2; //byte13.5~6
			bit_t Byte13_Reserve         				   :1; //byte13.7  reserve
			//Param[14]
			bit_t AMPConfig              			       :1; //byte14.0  AMP配置  0:内置AMP  1:外置AMP
			bit_t SpeakerConfig         				   :2; //byte14.1~2  扬声器额定功率  0:invalid  1:25W  2:xxx
			bit_t TunerAntSupport        				   :1; //byte14.3   收音机天线
			bit_t GPSAntSupport         				   :1; //byte14.4    GPS天线
			bit_t WIFIAntSupport                          :1; //byte14.5 WIFI
			bit_t GWSupport                               :1; //byte14.6 GW
			bit_t Byte14_Reserve        				   :1; //byte14.7  reserve 
			//Param[15]
			bit_t DaytimeRunningLigthSetSupport         :1; //byte15.0 日间行车灯设置
			bit_t AutoCruiseSetSupport                   :1; //byte15.1  自适应巡航设置
			bit_t TelligentLaneAssistSupport            :1; //byte15.2  车道辅助系统 
			bit_t AuxiliarySystemSupport                :1; //byte15.3  并线辅助系统
			bit_t Byte15_Reserve                         :4; //byte15.4~7  reserve
		}bits;
	}EOLState;
}EOLCfgStruct;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
 /*------------DATA[0-1]--------------------------------*/	
 	uint8_t  CurrFuelLevel;
}FuelLevelStruct;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
 /*------------DATA[0-3]--------------------------------*/	
 	uint8_t  Car_State;
 	uint8_t  Car_PMLevel;
 	uint8_t  Car_LowPowerWarn;
}CanPmStruct;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
	uint8_t keyValue;
	uint8_t keyState;
}CANKeyStateStruct;

typedef struct{
	uint8_t   LENGTH;
	uint8_t   SID;
	uint8_t   State;	 	/*bit0: 0- deal done; 1- busy */
}CANStateDataStruct;

typedef struct
{
	uint8_t  CAN_Acc :		2;// 0: OFF; 1: ON; 3: unvalid
	uint8_t  CAN_Lock:		2;
	uint8_t  CAN_door:		2;
	uint8_t  CAN_peps:      	2;
}CANVehicleStateStruct;

typedef struct
{
	uint8_t  NaviIdentification;
	uint32_t distanceToNext;
}NaviInforamtionStruct;

typedef struct
{
	uint8_t  length;
	uint8_t  Data[5];
}_DataCtlInfoStruct;

typedef struct
{
	uint8_t  length;
	uint8_t  *pData;
}_DataInfoStruct;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   SID;
       _DataCtlInfoStruct	Ctl;
       _DataInfoStruct	Info;  
	
}ExtMediaDataStruct;



typedef struct{
	uint8_t   PrjCode;
	uint8_t   USERID;
#if 0
	/*-----------DATA[0]--------------------------------*/
	uint8_t   EnableStatu                  :2;//DVR开关
	uint8_t   TapeStatu                     :2;//录音开关
	uint8_t   RecordingStatu             :2;//录制时长
	uint8_t   ResolutionStatu            :2;//分辨率
	/*-----------DATA[1]--------------------------------*/
	uint8_t   RebroadcastStatu        :2;//回放请求结果
	uint8_t   PhotographResult         :2;//拍照请求结果
	uint8_t   RealtimeDisplayStatu   :2;//实时显示状态
	uint8_t   SystemError                  :1;//系统故障
	uint8_t   Exist                               :1;
	/*-----------DATA[2]--------------------------------*/	
	uint8_t   SystemImprintStatu      :2;//系统版本信息查询反馈信号. 
	uint8_t   SDCapacityStatu             :2;//SD卡容量查询反馈信号. 
	uint8_t   ErrorRecordStatu            :2;//故障记录信息查询反馈信号.
	uint8_t   SdcardStatu                    :2;//DVR 存储卡信息.
	/*-----------DATA[3]--------------------------------*/
	uint8_t   EmergencyRecordStatu   :2;//一键紧急录制反馈信号. 、
	uint8_t   DVRSignalLockStatu          :1;//DVR信号LOCK标志位
	uint8_t   DVRSdFormatStatus			:3; // SD卡格式化状态
#else //snake20160817
	//DATA[0]
	//低位在前  高位在后
	uint8_t DVR_SettingStatusReserved         :1;//Reserved
	uint8_t DVR_VideoSignalLockStatus       :1; //视频源锁定标志
	uint8_t DVR_RecordingCycleSetStatus   :2;//录音时长设置
	uint8_t DVR_ResolutionStatus :2;//分辨率设置
	uint8_t DVR_TapeSetStatus :2;//录音开关

	//DATA[1]
	uint8_t DVR_SDcardStatus :3;
	uint8_t DVR_ConnectedState  :1;//DVR连接状态
	uint8_t DVR_SystemStatus: 4;

	//DATA[2]
	uint8_t DVR_DestinationPageResult : 2;
	uint8_t DVD_RestoreFactorySettingResult :2;
	uint8_t DVR_SDFormatResult  :2;
	uint8_t DVR_PhotographResult :2;

	//DATA[3]
	uint8_t DVR_CommandResult :4;
	uint8_t DVD_ProgrammingModeResult :4;//软件升级结果

	//DATA[4]
	uint8_t DVR_CommandList ;

	//DATA[5]
	uint8_t DVR_PageAttribute :2;
	uint8_t DATA5_Reserved :6;

	//DATA[6]
	uint8_t DVR_CurrentPageNum;

	//DATA[7]
	uint8_t DVR_TotalPageNum;

	//DATA[8]
	uint8_t DVR_ErrorStatus_Reserved :4;
	uint8_t DVR_ErrorStatus_PowerError:1;
	uint8_t DVR_ErrorStatus_SystemError :1;
	uint8_t DVR_ErrorStatus_KeyError:1;
	uint8_t DVR_ErrorStatus_SDCardError :1;
#endif
}CarDvrDataStruct;

typedef struct //snake20160817 add 
{
	uint8_t  PrjCode;
	uint8_t  USERID;
	uint8_t  DvrVersion_Year ;
	uint8_t  DvrVersion_Month ;
	uint8_t  DvrVersion_Day ;//Reserved
	uint8_t  DVR_SDTotalCapacity_Integer ;
	uint8_t  DVR_SDTotalCapacity_Decimals ;
	uint8_t  DVR_SDResidualCapacity_Integer ;
	uint8_t  DVR_SDResidualCapacity_Decimals ;
}CarDvrVerStruct;
#pragma pack(4)

//-----------------------------------------------
CAN_API ByteBufferMangerStruct *pCAN_GetMediaRxCANByteBuffer(void);
CAN_API CANVehicleStateStruct *	pCAN_GetVehicleState(void);
CAN_API void 					CAN_Api_Init(void);
CAN_API	NaviInforamtionStruct * 	pCAN_GetHUNaviInfo(void);
CAN_API CANStateDataStruct *	pCAN_GetCANSysStateStr(void);
CAN_API EOLCfgStruct *			pCAN_GetEOLStr(void);
CAN_API ExtMediaDataStruct	* 	pCAN_GetVINStr(void);
CAN_API CommonDataStruct	* 	pCAN_GetCommonStr(void);
CAN_API void CanAPI_LoadTboxPhoneInfo(uint8_t *pTboxphone,uint8_t Len);
//CAN_API void CANAPI_LoadEOLInfo(uint8_t*pData, uint8_t len);
CAN_API void CANAPI_LoadEOLInfo(uint16_t did,uint8_t*pData, uint8_t len);//snake20160806 add


/****************************************************************************
* @function	CAN_GetVehicleSpeed
 * @brief  	Get vehicle speed information Data point
 * @param  	null				
 * @retval 	return the point of the speed.
 ****************************************************************************/
CAN_API CarSpeedDataStruct* 	pCAN_GetVehicleSpeed(void);

/****************************************************************************
* @function	CAN_GetEngineAngle
 * @brief  	Get vehicle Engine angle information Data point
 * @param  	null				
 * @retval 	return the point of the engine angle.
 ****************************************************************************/
CAN_API CarAngleDataStruct* 	pCAN_GetAngleData(void);
/****************************************************************************
* @function	CAN_GetOutsideTemperature
 * @brief  	Get outside temperature information Data point
 * @param  	null				
 * @retval 	return the point of the outside temperature.
 ****************************************************************************/
CAN_API CarOutsideTempDataStruct* pCAN_GetOutsideTempData(void);
CAN_API CarMaintainInfoStruct *	pCAN_GetCarMaintainState(void);
/****************************************************************************
* @function	CAN_GetRadarData
 * @brief  	Get Radar information Data Structure
 * @param  	null				
 * @retval 	return the point of the Radar structure.
 ****************************************************************************/
CAN_API  RadarDataStruct 	*	pCAN_GetRadarData(void);

/****************************************************************************
* @function	CAN_GetACData
 * @brief  	Get AirConditioner information Data Structure
 * @param  	null				
 * @retval 	return the point of the AC structure.
 ****************************************************************************/
CAN_API FrontACDataStruct	*	pCAN_GetFrontACData(void);
CAN_API RearACDataStruct	*	pCAN_GetRearACData(void);
/****************************************************************************
* @function	CAN_GetTPMSData
 * @brief  	Get TPMS information Data Structure
 * @param  	null				
 * @retval 	return the point of the TPMS structure.
 ****************************************************************************/
CAN_API TPMSDataStruct	*	pCAN_GetTPMSData(void);
CAN_API CANKeyStateStruct  *	pCAN_GetCANkeyState(void);
/****************************************************************************
* @function	CAN_GetLightData
 * @brief  	Get Light information Data Structure
 * @param  	null				
 * @retval 	return the point of the light structure.
 ****************************************************************************/
CAN_API CarLightDataStruct*		pCAN_GetCarLightData(void);
/****************************************************************************
* @function	CAN_GetWiperData
 * @brief  	Get Wiper information Data Structure
 * @param  	null				
 * @retval 	return the point of the Wiper structure.
 ****************************************************************************/
CAN_API CarWiperDataStruct*	pCAN_GetCarWiperData(void);
/****************************************************************************
* @function	CAN_GetwindowData
 * @brief  	Get window information Data Structure
 * @param  	null				
 * @retval 	return the point of the windowData structure.
 ****************************************************************************/
CAN_API CarWindowDataStruct*	pCAN_GetCarWindowData(void);
/****************************************************************************
* @function	CAN_GetDoorStateData
 * @brief  	Get DoorState information Data Structure
 * @param  	null				
 * @retval 	return the point of the DoorState structure.
 ****************************************************************************/
CAN_API CarDoorStateDataStruct*	pCAN_GetDoorStateData(void);
/****************************************************************************
* @function	CAN_GetSeatData
 * @brief  	Get Seat information Data Structure
 * @param  	null				
 * @retval 	return the point of the Seat structure.
 ****************************************************************************/
CAN_API CarSeatDataStruct*		pCAN_GetSeatData(void);
/****************************************************************************
* @function	CAN_GetRearMirrorData
 * @brief  	Get Rear Mirror information Data Structure
 * @param  	null				
 * @retval 	return the point of the Rear Mirror structure.
 ****************************************************************************/
CAN_API CarRMirrorDataStruct*	pCAN_GetRearMirrorData(void);
/****************************************************************************
* @function	CAN_GetEcuData
 * @brief  	Get Ecu information Data Structure
 * @param  	null				
 * @retval 	return the point of the Ecu structure.
 ****************************************************************************/
CAN_API CarEcuDataStruct*		pCAN_GetEcuData(void);
/****************************************************************************
* @function	CAN_GetBSDData
 * @brief  	Get BSD information Data Structure
 * @param  	null				
 * @retval 	return the point of the BSD structure.
 ****************************************************************************/
CAN_API CarBSDDataStruct*		pCAN_GetBSDData(void);
/****************************************************************************
* @function	CAN_GetCarPackData
 * @brief  	Get CarPack information Data Structure
 * @param  	null				
 * @retval 	return the point of the CarPack structure.
 ****************************************************************************/
CAN_API CarPACDataStruct*		pCAN_GetCarPACData(void);
/****************************************************************************
* @function	CAN_GetTBOXData
 * @brief  	Get TBOX information Data Structure
 * @param  	null				
 * @retval 	return the point of the TBOX structure.
 ****************************************************************************/
CAN_API TBOXDataStruct*		pCAN_GetTBOXData(void);
CAN_API TboxTUIDStruct*		pCAN_GetTboxTUIDData(void);
/****************************************************************************
* @function	CAN_GetAVMData
 * @brief  	Get AVM information Data Structure
 * @param  	null				
 * @retval 	return the point of the AVM structure.
 ****************************************************************************/
CAN_API CarAVMDataStruct*		pCAN_GetAVMData(void);
/****************************************************************************
* @function	CAN_GetODOData
 * @brief  	Get ODO information Data Structure
 * @param  	null				
 * @retval 	return the point of the ODO structure.
 ****************************************************************************/
CAN_API CarODODataStruct*	pCAN_GetODOData(void);
/****************************************************************************
* @function	CAN_GetSystemData
 * @brief  	Get System information Data Structure
 * @param  	null				
 * @retval 	return the point of the System structure.
 ****************************************************************************/
CAN_API CarSystemDataStruct*	pCAN_GetSystemData(void);
/****************************************************************************
* @function	CAN_GetPEPSData
 * @brief  	Get PEPS information Data Structure
 * @param  	null				
 * @retval 	return the point of the PEPS structure.
 ****************************************************************************/
CAN_API CarPEPSDataStruct*		pCAN_GetPEPSData(void);
/****************************************************************************
* @function	CAN_GetSeatHeatData
 * @brief  	Get SeatHeat information Data Structure
 * @param  	null				
 * @retval 	return the point of the SeatHeat structure.
 ****************************************************************************/
CAN_API ACSeatHeatDataStruct*	pCAN_GetSeatHeatData(void);
/****************************************************************************
* @function	CAN_GetRadarStatusData
 * @brief  	Get RadarStatus information Data Structure
 * @param  	null				
 * @retval 	return the point of the RadarStatus structure.
 ****************************************************************************/
CAN_API RadarStatusDataStruct*	pCAN_GetRadarStatusData(void);
/****************************************************************************
* @function	CAN_GetDTVStateData
 * @brief  	GetDTVState information Data Structure
 * @param  	null				
 * @retval 	return the point of the DTVState structure.
 ****************************************************************************/
CAN_API FuelLevelStruct* pCAN_GetCarFuelLevelData(void);
CAN_API CanPmStruct* pCAN_GetCarCanPmData(void);
CAN_API CarDoorLockDataStruct*	pCAN_GetCarDoorLockData(void);


CAN_API DTVStateInfoStruct*	pCAN_GetDTVStateData(void);
CAN_API DTVVersionStruct*		pCAN_GetDTVVersionData(void);
CAN_API CarECOInfoStruct *	pCAN_GetVehicleECOData(void);
CAN_API CarPEPSDataStruct *	pCAN_GetVehiclePEPSData(void);
CAN_API FCPVersionStruct* 		pCAN_GetFCPVersionData(void);
CAN_API CarDvrDataStruct*		pCAN_GetDvrData(void);
CAN_API CarDvrVerStruct*	pCAN_GetDvrVer(void);
CAN_API CarAccCtrlStruct* pCAN_GetVehicleAccCrlData(void);
CAN_API CarFcwStruct* pCAN_GetFcwData(void);
CAN_API CarRcwStruct* pCAN_GetRcwData(void);
CAN_API CarLdwSensStruct* pCAN_GetLdwData(void);
#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
void	CANUser_VehicleOsVaribleReset(void);
#endif

#endif
#ifdef CAN_API_AC_FRONT_EN
FrontACDataStruct         CAN_FrontACDataStr;
#endif 
#ifdef CAN_API_AC_REAR_EN
RearACDataStruct          CAN_RearACDataStr;
#endif

#ifdef CAN_API_IP_FUEL_LEVEL_EN
CarFuelLevelDataStruct CAN_FuelLevelDataStr;
#endif
/****************************************************************************
 * **                                        FILE END
****************************************************************************/


