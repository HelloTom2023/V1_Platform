#ifndef _UDS_CFG_H
#define _UDS_CFG_H

#if D_UDS_DBG_EN&&D_PRINT_EN
#define Uds_Debug(x)		x
#else
#define Uds_Debug(x)
#endif

#if (PROJECT_CODE == CHANGAN_R103_H15T)
	#define DTC_AVILABILITY_MASK (0x09) //snake20160803
#elif(PROJECT_CODE == CHANGAN_S401)
	#define DTC_AVILABILITY_MASK (0x0f) //snake20160805
#else
	#define DTC_AVILABILITY_MASK (0x08)
#endif
/*******************USER CONFIG AREA**************************/
typedef enum{
	//speaker and amp DTC
	DTC_ID_SPK_FL_SC,  //short circuit to GND
	DTC_ID_SPK_FL_OC,  //open circuit
	DTC_ID_SPK_FR_SC,
	DTC_ID_SPK_FR_OC,
	DTC_ID_SPK_RL_SC,
	DTC_ID_SPK_RL_OC,
	DTC_ID_SPK_RR_SC,
	DTC_ID_SPK_RR_OC,
	DTC_ID_AMP_CLIP,
	//power DTC
	DTC_ID_VOLT_LOW,
	DTC_ID_VOLT_HIGH,
	
	//canbus off DTC
	//在R103-H15T中,对于车身来说,就是分为BODY和PT,但是对于DVD而言就是高速CAN...
	DTC_ID_BODY_BUS_OFF,//body bus   
	DTC_ID_PT_BUS_OFF,//pt bus

	DTC_ID_BUS_GW, // Missing ECU DTC
	DTC_ID_BUS_GW_32A,
	//DTC_ID_BUS_GW_2B0, //Message timeout DTC
	DTC_ID_BUS_GW_320,
	
	DTC_ID_BUS_BCM,
	DTC_ID_BUS_BCM_347,
	//DTC_ID_BUS_BCM_288,	

	DTC_ID_BUS_ESP,
	DTC_ID_BUS_ESP_218,
	DTC_ID_BUS_ESP_368,

	DTC_ID_BUS_AC,
	DTC_ID_BUS_AC_330,
	
	DTC_ID_BUS_EMS,
	DTC_ID_BUS_EMS_255,

	DTC_ID_BUS_RRS,

	DTC_ID_BUS_DVR_612,
	DTC_ID_BUS_DVR_613,
	DTC_ID_BUS_DVR,

	DTC_ID_BUS_PAC,
	
	//snake 20160804
	DTC_ID_BUS_KEYBOARD,

	DTC_ID_BUS_LCM,

	DTC_ID_BUS_PEPS,

	DTC_ID_BUS_TBOX,

	DTC_ID_BUS_AVM,

	DTC_ID_BUS_IP,
	
	//hardware check  snake20160804
	DTC_ID_AMP_SC_GND,  //short circuit to GND
	DTC_ID_AMP_SC_POWER,  //short circuit to POWER
	DTC_ID_AMP_OC,
	
	DTC_ID_SPK_SC_GND,  
	DTC_ID_SPK_SC_POWER, 
	DTC_ID_SPK_OC,
	
	DTC_ID_GPS_SC_GND,  
	DTC_ID_GPS_SC_POWER,  
	DTC_ID_GPS_OC,
	
	DTC_ID_TUNER_SC_GND,  
	DTC_ID_TUNER_SC_POWER,  
	DTC_ID_TUNER_OC,

	DTC_ID_VALID_END,
}eDTCIndex;

/*******************USER CONFIG AREA END**********************/

/*
*  UDS Service Enable Switch Macro(UDS_App inner used, user should not attention )
*/

#define UDS_SVC_DSC_EN			1
#define UDS_SVC_ECUR_EN		1
#define UDS_SVC_SA_EN			1
#define UDS_SVC_CC_EN			1
#define UDS_SVC_TP_EN			1
#define UDS_SVC_CDTCS_EN		1
#define UDS_SVC_RDBI_EN		1
#define UDS_SVC_RDBPI_EN		1
#define UDS_SVC_WDBI_EN		1
#define UDS_SVC_WMBA_EN		1
#define UDS_SVC_RMBA_EN		1
#define UDS_SVC_CDTCI_EN		1
#define UDS_SVC_RDTCI_EN		1
#define UDS_SVC_IOCBI_EN		1
#define UDS_SVC_RD_EN			0
#define UDS_SVC_RU_EN			0
#define UDS_SVC_TD_EN			0
#define UDS_SVC_RTE_EN			0
#define UDS_SVC_RC_EN			0

#define UDS_SVC_ATP_EN			0		//Access Timing Parameter
#define UDS_SVC_SDT_EN			0		// Secured Data Transmission
#define UDS_SVC_ROE_EN			0		//Response On Event
#define UDS_SVC_LC_EN			0		//Link control
#define UDS_SVC_RSDBI_EN		0		//Read Scaling Data by Identifier
#define UDS_SVC_DDDI_EN		0		//Dynamically Defined Data Identifier

#define UDS_MAJOR_VERSION		10  /* 1.0*/
#define UDS_MINOR_VERSION		10
#define UDS_PATCH_VERSION		10


/*two internal state of  CanTp module */
#define UDS_DIAG_OFF				0
#define UDS_DIAG_ON				1

/*security state  */
#define UDS_LOCKED_STATE			0
#define UDS_UNLOCKED_STATE		1

#define UDS_SA_IDLE		0
#define UDS_SA_SEED		1
#define UDS_SA_SENDKEY	2

typedef enum
{
	COMM_ENRX_ENTX = 0x00,
	COMM_ENRX_DSTX,
	COMM_DSRX_ENTX,
	COMM_DSRX_DSTX
}UDS_CC_CONTROL_TYPE;

typedef enum
{
	COMM_TYPE_NCM	= 0x01,					//normal control message
	COMM_TYPE_NWMCM,						//network management control message
	COMM_TYPE_NCM_NWMCM					//Normal and NM message
}UDS_CC_COMM_TYPE;


/*session mode*/
typedef enum
{
	SESSION_DEFAULT		=1,
	SESSION_PROGRAM	=2,
	SESSION_EXTENDED	=3,
	SESSION_EndOfLine 	= 0x40 /*下线检测模式*/
}UDS_SESSION_UNION;

typedef enum
{
	SUPPORT	= 0,			
	SUPPORT_UNLOCK,		
	NOT_SUPPORT	,		
}SUPPORT_TYPE_ENUM;

#define SERVE_DSC			0X10	/*mode control*/
#define SERVE_ECUR		0X11	/*ecu reset*/
#define SERVE_CDTCI		0X14	/*clear diagnostic information*/
#define SERVE_RDTCI		0X19	/*read DTC from server*/
#define SERVE_RDBI		0X22	/*read data by identifier*/
#define SERVE_RSDBI		0X24	 /*ReadScalingDataByIdentifier*/
#define SERVE_SA			0X27	/*security access*/
#define SERVE_CC			0X28	/*communcate control*/
#define SERVE_TP			0X3E	/*Tester present*/
#define SERVE_CDTCS		0X85	/*control DTC set*/
#define SERVE_RDBPI		0X2A	/*read data by period identifier*/
#define SERVE_RMBA		0X23	/*read memory by address*/
#define SERVE_DDDI		0X2C	/*DynamicallyDefineDataIdentifier*/
#define SERVE_WDBI		0X2E	/*write data by identifier*/
#define SERVE_IOCBI		0X2F	/*Input Output control by identifier*/
#define SERVE_RC			0X31	/*routine control*/
#define SERVE_RD			0X34	/*Request download */
#define SERVE_TD			0X36	/*Transfer */
#define SERVE_RTE			0X37	/*request transfer exit */
#define SERVE_WMBA		0X3D	/*write memory by address*/
#define SERVE_ATP			0X83   /*AccessTimingParameter*/
#define SERVE_SDT			0X84  /*SecuredDataTransmission*/
#define SERVE_ROE		0X86	/*ResponseOnEvent*/
#define SERVE_LC			0X87	/*LinkControl*/


#define UDS_SI_OFFSET		0X40
#define UDS_NR_SI			0X7F

/*NRC define*/
#define PR  				0X00   /*positiveResponse*/
/*1-10 ISOSAEReserved*/
#define GR				0X10	/*否定响应不属于定义中任意一项时，服务器使用此否定码*/
#define SNS				0x11	/*serviceNotSupported*/
#define SFNS				0x12  /*sub function not supported*/
#define IMLOIF	 		0x13  /*incorrect message length or invalid format*/
#define RTL				0X14	/*responseTooLong*/
/*15-20 ISOSAEReserved*/
#define BRR				0X21	/*busyRepeatRequest*/
#define CNC				0x22  /*conditions not correct*/
/*23 ISOSAEReserved*/
#define RSE				0x24
/*25-30 ISOSAEReserved*/
#define ROOR				0x31  /*request out of range*/
/*32 ISOSAEReserved*/
#define SAD				0x33  /*security access denied*/
/*34 ISOSAEReserved*/
#define IK				0x35  /*invalid key*/
#define ENOA				0x36  /*exceed number of attempts*/
#define RTDNE				0x37  /*required time delay not expired*/
/*38-4F reservedByExtendedDataLinkSecurityDocument*/
/*50-6F ISOSAEReserved*/
#define UDNA				0X70  /*uploadDownloadNotAccepted*/
#define TDS				0X71	/*transferDataSuspended*/
#define GPF				0x72  /*generalProgrammingFailure*/
#define WBSC				0X73  /*wrongBlockSequenceCounter*/
/*74-77 ISOSAEReserved*/
#define RCRRP				0X78  /*requestCorrectlyReceived-ResponsePending*/
/*79-7D ISOSAEReserved*/
#define SFNSIAS			0X7E  /*subFunctionNotSupportedInActiveSession*/
#define SNSIAS			0X7F  /*serviceNotSupportedInActiveSession*/
/*80 ISOSAEReserved*/
#define RPMTH			0X81	/*rpmTooHigh*/
#define RPMTL				0X82	/*rpmTooLow*/
#define EIR				0X83	/*engineIsRunning*/
#define EINR				0x84	/*engineIsNotRunning*/
#define ERTTL				0x85   /*engineRunTimeTooLow*/
#define TEMPTH			0x86	/*temperatureTooHigh*/
#define TEMPTL			0x87	/*temperatureTooLow*/
#define VSTH				0x88	/*vehicleSpeedTooHigh*/
#define VSTL				0x89	/*vehicleSpeedTooLow*/
#define TPTH				0x8a	/*throttle/PedalTooHigh*/
#define TPTL				0x8b	/*throttle/PedalTooLow*/
#define TRNIN				0x8c	/*transmissionRangeNotInNeutral*/
#define TRNIG				0x8d	/*transmissionRangeNotInGear*/

#define BSNC				0x8f	/*brakeSwitch(es)NotClosed (Brake Pedal not pressed or not applied)*/
#define SLNIP				0x90	/*shifterLeverNotInPark*/
#define TCCL				0x91	/*torqueConverterClutchLocked*/
#define VTH				0x92	/*voltageTooHigh*/
#define VTL				0x93	/*voltageTooLow*/


#define SECURITY_ACCESS_MAX_TIMES	3

typedef enum
{
	SF_NPCI			=0,	/*single frame*/
	FF_NPCI	,		/*the first frame*/
	CF_NPCI	,		/*consecutive frame*/
	FC_NPCI	,		/*flow control frame*/
	NULL_NPCI
}PDU_TYPE;

/*FC  FS status*/
typedef enum
{
	CONTINUE_SEND	=0,
	WAIT_NEXT_FC,
	FS_OVERFLOW
}UDS_FS_TYPE;

typedef enum
{
	UDS_FUNC_ADDR		=0,
	UDS_PHY_ADDR		=1
}TA_TYPE;


#define UDS_ROUTINE_ID_TAB_END		0x0000		/*table end flag */
#define UDS_ROUTINE_ID_ERASE			0xff00		/*start erase routine */
#define UDS_ROUTINE_ID_CHK			0x0202		/*start check routine*/
#define UDS_ROUTINE_ID_CHK_DESIGN	0xff01		/*check design reliable*/
#define UDS_ROUTINE_ID_CHK_PRE		0x0203		/*check program prepare status*/
#define UDS_ROUTINE_ID_BOOT_RVD		0xf518		/*boot reserved */


typedef struct
{
	uint8_t ServiceId;
	uint8_t DefaultSession;
	uint8_t ProgrammingSession;
	uint8_t ExtendedSession;
	uint8_t PhysicalAddress;
	uint8_t FunctionalAddress;
	uint8_t subFuntion;  			/*0-without subFunction 1-with SubFunction */
	uint8_t SubFunctionNum;  		/*Valid subFunction number  */
	uint8_t ListOfSubFunction[10];	/*Sub function Lists , the max number is 10 */
}UdsServiceCfgStruct;


#define ECUR_HR				1 	/*hard reset*/
#define ECUR_KOFFONR		2 	/*key off-on reset */	
#define ECUR_SR				3 	/*soft reset*/	


/*<N_Result_USDT>*/
#define N_OK					0
#define N_TIMEOUT_A		1 /*数据帧经过数据链路层的发送时间*/
#define N_TIMEOUT_Bs		2 /*发送方接收流控制帧的等待时间*/
#define N_TIMEOUT_Cr		3 /*接收方接收连续帧的等待时间*/
#define N_WRONG_SN			4
#define N_UNEXP_NPDU		5 /*unexpected protocol data unit*/
#define N_WFT_OVRN			6

/*network layer timing parameters define  unit-ms*/
#define N_As_Ar_MAX				TIMER_70MS
#define N_Bs_MAX				TIMER_150MS
#define N_Br_MAX				TIMER_70MS
#define N_Cs_MAX				TIMER_70MS
#define N_Cr_MAX				TIMER_150MS /* wait for receive CF MSG timeout */
#define SERVER_LOCKTIME_MAX	TIMER_10000MS

#define BLOCK_SIZE			8	/*发送方连续发送连续帧的数目*/
#define ST_MIN				20 /*两个连续帧之间最小时间间隔*/
#define N_WFT_MAX			0  /*等待流控制帧最大发送次数*/
/*application layer timing parameter - ECU*/
#define P2server_MAX			50
#define P2xserver_MAX			5000
#define S3server_MAX			5000
#define S3client_MAX			4000

/*application layer timing parameter - TESTER*/
#define P2client_MIN			TIMER_100MS
#define P2xclient_MIN			TIMER_5500MS
#define P3client_phys_MIN		TIMER_100MS
#define P3client_func_MIN		TIMER_100MS
#define P3client_MAX			TIMER_4000MS


/*<N_Result_ChangeParameter>*/

#define N_RX_OK				1
#define N_WRONG_PARAMETER   	2
#define N_WRONG_VALUE		3

#define N_BUFFER_SIZE			200 // netlayer receive USDT buffer max size

#define NO_SUB_FUNC			0
#define YES_SUB_FUNC			1

#define EMPTY_FILLER_BYTE		0x00

#define DTC_SET_ON			1
#define DTC_SET_OFF			2

#define SECURITY_KEY_LENGTH	4

#define DID_BYTE_NUM_MAX		15

#define ATTRI_READONLY		0		/*Read only   */ // data type is const
#define ATTRI_WRITE		1		/*could write */ //write to eeprom
#define ATTRI_READ         2      /*Read         */ //ECU can change data，but tester not write

typedef struct
{
	uint16_t	DID_Id;
	uint8_t 	ByteLen;
	uint8_t*   pParam;
	uint8_t     Attribute;				/**/
	SUPPORT_TYPE_ENUM IsSupport;//snake20160804 
}DID_STRUCT;

typedef struct
{
	uint8_t   DTCHighByte;
	uint8_t   DTCMiddleByte; /*DTC = (DTCHighByte << 8 )+ DTCMiddleByte*/
	uint8_t   DTCLowByte; 
	uint8_t   DTCStatus;  
	SUPPORT_TYPE_ENUM IsSupport;//snake20160804
}DTC_STRUCT;

/*
 *	DTCstatusMask/statusOfDTC bit define
 */

#define DTC_MASK_FAIL					BIT0		/*testFailed */
#define DTC_MASK_FAIL_THISCYCLE		BIT1		/*testFailedThisMonitoringCycle */
#define DTC_MASK_PENDING				BIT2		/*pendingDTC */
#define DTC_MASK_CONFIRM				BIT3		/*confirmedDTC */
#define DTC_MASK_RUN_LASTCLEAR  		BIT4		/*testNotCompletedSinceLastClear */
#define DTC_MASK_FAIL_LASTCLEAR		BIT5		/*testFailedSinceLastClear */
#define DTC_MASK_RUN_THISCYCLE		BIT6		/*testNotCompletedThisMonitoringCycle */
#define DTC_MASK_WARN_INDREQ			BIT7		/*warningIndicatorRequested */

#define FAST_RATE_TIME		TIMER_30MS
#define SLOW_RATE_TIME		TIMER_500MS
#define MEDIUM_RATE_TIME	TIMER_300MS

#define PDID_MAX_NUM		20

#define DID_ADS				0xD100	/*the DID of active diagnostic session */

#define DID_TBOXREGNUM		0xFD02	/* TBox Register Phone Number */


#define DID_ID_FD01        0xFD01 /* End of Line */
#define DID_ID_F184        0xF184
#define DID_ID_F18C        0xF18C /* ECU Serial Number */
#define DID_ID_F190        0xF190	/* Vehicle Identify Number */
#define DID_ID_F1A0        0xF1A0
#define DID_ID_F1A2        0xF1A2 /*Vehicle Manufacturing Date in CACV‘s production line */
#define DID_ID_F1FA        0xF1FA //EOL H15T
#define DID_ID_F1F8        0XF1F8
#define DID_ID_F101        0XF101


#define DID_LEN_PHONE		11
//snake 20160712
#define DID_FD01_LENGTH		16 // 1 snake20161027 
#define DID_LEN_PHONE    11
#define DID_F184_LENGTH   7
#define DID_F18C_LENGTH   13
#define DID_F190_LENGTH		17
#define DID_F1A0_LENGTH		1
#define DID_F1A2_LENGTH		4
#define DID_F1FA_LENGTH		6
#define DID_F1F8_LENGTH       16
#define DID_F101_LENGTH   2

enum
{
	//R103-H15T
	CAR_TYPE_SEL_R103_H15T_AT_WISDOM = 0,//AT智能型 BB03
	CAR_TYPE_SEL_R103_H15T_MT_WISDOM,    //MT智能型 BBO3
	CAR_TYPE_SEL_R103_H15T_MT_LUXURY,    //MT豪华型 BB03
	CAR_TYPE_SEL_R103_H15T_MT_LINK,      //MT智联型 BB03
	CAR_TYPE_SEL_R103_H15T_AT_SPORTS,    //AT运动型 BB03
	CAR_TYPE_SEL_R103_H15T_MT_SPORTS,    //MT运动型 BB07
	CAR_TYPE_SEL_R103_H15T_MT_A5D4,      //MT智能操控包
	CAR_TYPE_SEL_R103_H15T_MT_A5D5,      //MT安全品质包  
	CAR_TYPE_SEL_R103_H15T_MT_A5D6,      //MT靓丽造型包 + 智能操控包
	CAR_TYPE_SEL_R103_H15T_MT_A5D7,      //MT靓丽造型包 + 安全品质包
	CAR_TYPE_SEL_R103_H15T_MT_A5D8,      //MT舒适畅享包 + 智能操控包	
	CAR_TYPE_SEL_R103_H15T_MT_A5D9,      //MT舒适畅享包 + 安全品质包

	//R103-17款
	CAR_TYPE_SEL_R103_17_STANDARD,     //标准型
	CAR_TYPE_SEL_R103_17_SPORTS,       //运动型 BB08
	CAR_TYPE_SEL_R103_17_LUXURY,       //豪华型 BB05
	CAR_TYPE_SEL_R103_17_WISDOM,       //智能型 BB05

	CAR_TYPE_SEL_DEFAULT,         //默认为AT智能型 BB03  海外版为运动型
	CAR_TYPE_SEL_MAX
};

typedef  struct 
{
	uint8_t PD_Id;
	uint8_t Byte[5];
	uint8_t ByteLen;
}RDBPI_STRUCT;

typedef struct
{
	uint16_t DID;
	uint8_t  ControlParameter;
	uint8_t  OptionLen;
	uint8_t *pOption;
}IOCONTROL_STRUCT;


/*DID List-----type is ATTRI_READ-----*/
extern uint8_t DID_6700[1];
extern uint8_t DID_6701[3];
extern uint8_t DID_6702[1];
extern uint8_t DID_6703[10];
extern uint8_t DID_6704[6];
extern uint8_t DID_6705[2];

UDS_EXTERN void  			Uds_LevelOneKeyArith(const uint8_t vseed[4],uint8_t GetLevelOnekey[4]);
UDS_EXTERN uint8_t 			Uds_GetCfgTblTotalNum(void);
UDS_EXTERN uint8_t  			Uds_GetDIDTblTotalNum(void);
UDS_EXTERN uint8_t 			Uds_GetDidIndex(uint16_t did);
UDS_EXTERN uint8_t * 			Uds_GetSecuritySeedPoint(void);
UDS_EXTERN RDBPI_STRUCT *	Uds_GetRDBPIPoint(void);
UDS_EXTERN DTC_STRUCT*		Uds_GetDTCTable(void);
UDS_EXTERN uint16_t*  		Uds_GetRoutineIdTable(void);
UDS_EXTERN DID_STRUCT*		Uds_GetDIDCfgTable(void);
UDS_EXTERN void 				Uds_UpdateDTCStatus(eDTCIndex DtcIndex, uint8_t status);
UDS_EXTERN  const uint8_t *pUds_GetCarTypeDefaultEOL(uint8_t CarType);
extern  const  	UdsServiceCfgStruct  	UdsServiceCfgTbl[];
extern  uint16_t 				UdsRoutineIdTable[];
extern IOCONTROL_STRUCT  	IOControlTable[];

#endif

/****************************************************************************
 * **                                        FILE END
****************************************************************************/


