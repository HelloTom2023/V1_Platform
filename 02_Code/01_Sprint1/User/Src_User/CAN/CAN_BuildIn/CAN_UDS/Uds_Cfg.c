#define _UDS_MODULE_C
#include "..\..\..\config\inc.h"

#ifdef UDS_ENABLE_MACRO

/*
*  UDS Service Enable Switch Macro
*/

#define USR_UDS_SVC_DSC_EN		1
#define USR_UDS_SVC_ECUR_EN		1
#define USR_UDS_SVC_SA_EN			1
#define USR_UDS_SVC_CC_EN			1		//added 20140716
#define USR_UDS_SVC_TP_EN			1
#define USR_UDS_SVC_CDTCS_EN		1
#define USR_UDS_SVC_RDBI_EN		1
#define USR_UDS_SVC_RDBPI_EN		0
#define USR_UDS_SVC_WDBI_EN		1
#define USR_UDS_SVC_WMBA_EN		0
#define USR_UDS_SVC_RMBA_EN		1
#define USR_UDS_SVC_CDTCI_EN		1
#define USR_UDS_SVC_RDTCI_EN		1
#define USR_UDS_SVC_IOCBI_EN		1
#define USR_UDS_SVC_RD_EN			0
#define USR_UDS_SVC_RU_EN			0
#define USR_UDS_SVC_TD_EN			0
#define USR_UDS_SVC_RTE_EN		0
#define USR_UDS_SVC_RC_EN			0

#define USR_UDS_SVC_ATP_EN		0		//Access Timing Parameter
#define USR_UDS_SVC_SDT_EN		0		// Secured Data Transmission
#define USR_UDS_SVC_ROE_EN		0		//Response On Event
#define USR_UDS_SVC_LC_EN			0		//Link control
#define USR_UDS_SVC_RSDBI_EN		0		//Read Scaling Data by Identifier
#define USR_UDS_SVC_DDDI_EN		0		//Dynamically Defined Data Identifier

const  UdsServiceCfgStruct  UdsServiceCfgTbl[]=
{	
#if	USR_UDS_SVC_DSC_EN&&UDS_SVC_DSC_EN
	/*mode control*/
	{
		SERVE_DSC  ,  
		SUPPORT,   NOT_SUPPORT,   SUPPORT,    
		SUPPORT,    SUPPORT, 
		YES_SUB_FUNC,
		2, 0x01,0x03,0x02,
	 },
#endif
#if USR_UDS_SVC_ECUR_EN&&UDS_SVC_ECUR_EN
	/*ecu reset*/
	{
		SERVE_ECUR , 
		SUPPORT,   NOT_SUPPORT,  SUPPORT,    
		SUPPORT,    SUPPORT, 
		YES_SUB_FUNC, 
		1, 0x03,0x01,
	},
#endif
#if USR_UDS_SVC_SA_EN&&UDS_SVC_SA_EN
	/*security access*/
	{
		SERVE_SA   ,  
		NOT_SUPPORT,   NOT_SUPPORT,       SUPPORT,    
		SUPPORT,NOT_SUPPORT, 
		YES_SUB_FUNC,
		2, 0x01,0x02,
	},
#endif
#if USR_UDS_SVC_CC_EN&&UDS_SVC_CC_EN
	/*communcate control*/
	{
		SERVE_CC   ,  
		NOT_SUPPORT,   NOT_SUPPORT,       SUPPORT,    
		SUPPORT,    SUPPORT, 
		YES_SUB_FUNC,
		4, 0x00,0x01,0x02,0x03,
	},
#endif
#if USR_UDS_SVC_TP_EN&&UDS_SVC_TP_EN
	/*Tester present*/
	{
		SERVE_TP,  
		SUPPORT,   NOT_SUPPORT,       SUPPORT,    
		SUPPORT,    SUPPORT, 
		YES_SUB_FUNC,
		1, 0x00,
	},
#endif
#if USR_UDS_SVC_CDTCS_EN&&UDS_SVC_CDTCS_EN
	/*control DTC set*/
	{
		SERVE_CDTCS,  
		NOT_SUPPORT,NOT_SUPPORT,       SUPPORT,    
		SUPPORT,    SUPPORT, 
		YES_SUB_FUNC,
		2, 0x01,0x02,	
	}, 
#endif	
#if USR_UDS_SVC_RDBI_EN&&UDS_SVC_RDBI_EN
	 /*read data by identifier*/
	{
		SERVE_RDBI ,    
		SUPPORT,NOT_SUPPORT,       SUPPORT,    
		SUPPORT,	   SUPPORT,  
		NO_SUB_FUNC,
		1, 0x00,
	}, 
#endif
#if USR_UDS_SVC_RDBPI_EN&&UDS_SVC_RDBPI_EN
	/*read data by period identifier*/
	{
		SERVE_RDBPI,
		SUPPORT,       SUPPORT,       SUPPORT,    
		SUPPORT,NOT_SUPPORT, YES_SUB_FUNC,
		4, 0x01,0x02,0x03,0x04,
	},
#endif
#if USR_UDS_SVC_WDBI_EN&&UDS_SVC_WDBI_EN
	/*write data by  identifier*/
	{
		SERVE_WDBI ,   
		NOT_SUPPORT,   NOT_SUPPORT,SUPPORT_UNLOCK,    
		SUPPORT,NOT_SUPPORT,  
		NO_SUB_FUNC,
		0, 0x00,0x02,0x03,0x40,
	}, 
#endif
#if USR_UDS_SVC_RMBA_EN&&UDS_SVC_RMBA_EN
 	/*read memory by address*/
	{
		SERVE_RMBA ,
		SUPPORT,NOT_SUPPORT,       SUPPORT,    
		SUPPORT,NOT_SUPPORT,  NO_SUB_FUNC,
		0, 0x00,0x00,0x00,
	},
#endif
#if USR_UDS_SVC_WMBA_EN&&UDS_SVC_WMBA_EN
	/*write memory by address*/
	{
		SERVE_WMBA ,
		NOT_SUPPORT,SUPPORT_UNLOCK,SUPPORT_UNLOCK,    
		SUPPORT,NOT_SUPPORT,  
		NO_SUB_FUNC,
		0,0x00,0x02,0x03,0x40,
	}, 
#endif
#if USR_UDS_SVC_CDTCI_EN&&UDS_SVC_CDTCI_EN
	 /*clear diagnostic information*/
	{
		SERVE_CDTCI,   
		SUPPORT,NOT_SUPPORT,       SUPPORT,   
		SUPPORT,    SUPPORT,  
		NO_SUB_FUNC,
		0,0x00,0x02,0x03,0x40,
	},
#endif
#if USR_UDS_SVC_RDTCI_EN&&UDS_SVC_RDTCI_EN
	/*read DTC from server*/
	{
		SERVE_RDTCI, 
		SUPPORT,NOT_SUPPORT,       SUPPORT,   
		SUPPORT,    SUPPORT, 
		YES_SUB_FUNC,
		3,0x01,0x02,0x0A,
	},
#endif	
#if USR_UDS_SVC_IOCBI_EN&&UDS_SVC_IOCBI_EN
	 /*Input Output control by identifier*/
	{
		SERVE_IOCBI,   
		SUPPORT,SUPPORT,SUPPORT,    
		SUPPORT,NOT_SUPPORT,  
		NO_SUB_FUNC,
		0, 0x00,0x00,
	}, 
#endif
#if USR_UDS_SVC_RC_EN&&UDS_SVC_RC_EN
	/*routine control*/
	{
		SERVE_RC,
		NOT_SUPPORT,SUPPORT_UNLOCK,SUPPORT_UNLOCK,    
		SUPPORT,NOT_SUPPORT ,
		YES_SUB_FUNC,
		3, 0x01,0x02,0x03,
	},
#endif
#if USR_UDS_SVC_RD_EN&&UDS_SVC_RD_EN
	  /*Request download */
	{
		SERVE_RD,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,    
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0, 0x00,0x00,
	},
#endif
#if USR_UDS_SVC_TD_EN&&UDS_SVC_TD_EN
	 /*Transfer */
	{
		SERVE_TD   ,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,    
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0,0x00,0x00,
	}, 
#endif
#if USR_UDS_SVC_RTE_EN&&UDS_SVC_RTE_EN
	  /*request transfer exit */
	{
		SERVE_RTE ,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,   
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0,0x00,0x00,
	}, 
#endif
#if USR_UDS_SVC_ATP_EN&&UDS_SVC_ATP_EN
	 /* AccessTimingParameter */
	{
		SERVE_ATP,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,   
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0,0x00,0x00,
	}, 
#endif
#if USR_UDS_SVC_SDT_EN&&UDS_SVC_SDT_EN
	 /* Secured Data Transmission  */
	{
		SERVE_SDT,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,   
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0,0x00,0x00,
	}, 
#endif
#if USR_UDS_SVC_ROE_EN&&UDS_SVC_ROE_EN
	 /* Response On Event */
	{
		SERVE_ROE,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,   
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0,0x00,0x00,
	}, 
#endif
#if USR_UDS_SVC_LC_EN&&UDS_SVC_LC_EN
	 /* Link Control */
	{
		SERVE_LC,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,   
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0,0x00,0x00,
	}, 
#endif
#if USR_UDS_SVC_RSDBI_EN&&UDS_SVC_RSDBI_EN
	/* Read Scaling Data by Identifier */
	{
		SERVE_RSDBI,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,   
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0,0x00,0x00,
	}, 
#endif
#if USR_UDS_SVC_DDDI_EN&&UDS_SVC_DDDI_EN
	/* Dynamically Defined Data Identifier */
	{
		SERVE_DDDI,
		NOT_SUPPORT,SUPPORT_UNLOCK,   NOT_SUPPORT,   
		SUPPORT,NOT_SUPPORT , NO_SUB_FUNC,
		0,0x00,0x00,
	}, 
#endif
};


#if (USR_UDS_SVC_WDBI_EN || USR_UDS_SVC_RDBI_EN)
const uint8_t gEOLList[CAR_TYPE_SEL_MAX][6]=
{
	/***********R103-H15T**************/
	{0xF7,0x00,0x00,0x00,0x00,0x00},//AT智能型 BB03
	{0x77,0x00,0x00,0x00,0x00,0x00},//MT智能型 BB03
	{0x76,0x00,0x00,0x00,0x00,0x00},//MT豪华型 BB03
	{0x76,0x00,0x00,0x00,0x00,0x00},//MT智联型 BB03
	{0x84,0x00,0x00,0x00,0x00,0x00},//AT运动型 BB03
	{0x04,0x00,0x00,0x00,0x00,0x00},//MT运动型 BB07
	
	{0x34,0x00,0x00,0x00,0x00,0x00},//MT智能操控包              A5D4
	{0x77,0x00,0x00,0x00,0x00,0x00},//MT安全品质包              A5D5
	{0x34,0x00,0x00,0x00,0x00,0x00},//MT靓丽造型包 + 智能操控包 A5D6
	{0x77,0x00,0x00,0x00,0x00,0x00},//MT靓丽造型包 + 安全品质包 A5D7
	{0x34,0x00,0x00,0x00,0x00,0x00},//MT舒适畅享包 + 智能操控包 A5D8	
	{0x77,0x00,0x00,0x00,0x00,0x00},//MT舒适畅享包 + 安全品质包 A5D9
	
	/************R103-17**************/
	{0x00,0x00,0x00,0x00,0x00,0x00},//标准型
	{0x00,0x00,0x00,0x00,0x00,0x00},//运动型 BB08
	{0x74,0x00,0x00,0x00,0x00,0x00},//豪华型 BB05
	{0x74,0x00,0x00,0x00,0x00,0x00},//智能型 BB05

	/************默认配置*************/
	#ifdef R103_H15T_OVERSEAS
	{0x08,0x00,0x00,0x00,0x00,0x00},//运动型
	#else
	{0xF7,0x00,0x00,0x00,0x00,0x00},//默认   AT智能型
	#endif
};

//support 0x22 serve
/*CACV ECU Application Software Version Number*/
const uint8_t DID_F080[8] = {'S','W',':','C','.','0','.','1'};
/*CACV ECU Boot Software Version Number*/
const uint8_t DID_F081[8] = {'S','W',':','C','.',0xff,'.',0xff};//预留接口,不使用,全部为0XFF的都为预留
/*CACV ECU Calibration Software Version Number*/
const uint8_t DID_F082[8] = {'S','W',':','C','.',0xff,'.',0xff};
/*CACV ECU Hardware Version Number*/
const uint8_t DID_F089[8] = {'H','W',':','C','.','0','.','1'};
/*CACV ECU Software Version Number */
const uint8_t DID_F189[8] = {'S','W',':','C','.','0','.','1'};
/*ECU Part Number*/
#if (PROJECT_CODE == CHANGAN_R103_H15T)
	const uint8_t DID_F187[21] = {'3','6','0','8','0','1','0','-','M','K','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' '};
#elif (PROJECT_CODE == CHANGAN_S401)
	const uint8_t DID_F187[11] = {'7','9','0','0','0','3','0','A','P','0','4'};//S401件号
#else//defult
	const uint8_t DID_F187[21] = {'3','6','0','8','0','1','0','-','M','K','0','1',' ',' ',' ',' ',' ',' ',' ',' ',' '};
#endif
/*ECU Supplier Identification Code*/
const uint8_t DID_F18A[7] = {'S',  '1',  '1', '9',  '7',  '1', ' '};
/*Network Information Data Identifier*/
const uint8_t DID_F120[4] = {'A','0','.','1'};
/*Function Specification Data Identifier */
const uint8_t DID_F121[4] = {'A','0','.','1'};
/*Diagnostic Definition DataIdentifier */
const uint8_t DID_F122[4] = {'A','0','.','1'};	
/*Supplier ECU Application Software Version Number */
const uint8_t DID_F083[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
/*Supplier ECU Boot Software Version Number */
const uint8_t DID_F084[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
/*Supplier ECU Calibration Software Version Number */
const uint8_t DID_F085[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
#if (PROJECT_CODE == CHANGAN_R103_H15T)
	/*Supplier ECU Hardware Version Number */
	const uint8_t DID_F193[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	/*Supplier ECU Software Version Number */
	const uint8_t DID_F195[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
#elif (PROJECT_CODE == CHANGAN_S401)
	const uint8_t DID_F193[16] = {'H','W',':','3','.','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	const uint8_t DID_F195[16] = {'S','W',':','3','.','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
#else
	const uint8_t DID_F193[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	const uint8_t DID_F195[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
#endif

/*system Supplier ECU Serial Number*/
const uint8_t DID_F110[28] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};

/*Radio Mode*/
uint8_t DID_6700[1] = {0XFF};
/*Radio Frequency*/
uint8_t DID_6701[3] = {0XFF,0XFF,0XFF};
/*Current Radio VOL*/
uint8_t DID_6702[1] = {0XFF};
/*HU BT Name*/
uint8_t DID_6703[10]= {0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF};
/*HU BT MAC ADDR*/
uint8_t DID_6704[6] = {0XFF,0XFF,0XFF,0XFF,0XFF,0XFF};
/*Total tracks in current selected device*/
uint8_t DID_6705[2] = {0XFF,0XFF};



// support 0x22 and 0x2e serve
/*Application Data Fingerprint Data Identifier*/
uint8_t DID_F184[DID_F184_LENGTH] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff};
/*ECU Serial Number*/
uint8_t DID_F18C[DID_F18C_LENGTH] = {0,0,0,1,0,0,0,1,0x07,0xe0,0xff,8,5};
/*Vehicle Identification Number*/
uint8_t DID_F190[DID_F190_LENGTH] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40};
/*ECU Mode Configuration*/
uint8_t DID_F1A0[DID_F1A0_LENGTH] = {0XFF};
/*Vehicle Manufacturing Date in CACV‘s production line*/
uint8_t DID_F1A2[DID_F1A2_LENGTH] = {0XFF,0XFF,0XFF,0XFF};
/*CACV  System Configuration*/
uint8_t DID_F1FA[DID_F1FA_LENGTH] = {0x77,0x00,0x00,0x00,0x00,0x00};//默认

/*System Network Configuration Data Identifier*///S401
uint8_t DID_F101[DID_F101_LENGTH] = {0x7F,0X00};

/*TBOX Register Phone Number */
uint8_t DID_FD02[11] = {'1','3','5','0','0','0','0','0','0','0','0'};// not support


/*------------EOL----------------------/
/*HU Config At EOL*/
uint8_t DID_FD01[DID_FD01_LENGTH] = {0x01};//{0x3e, 0x60} 暂时预留,长安没有给具体的定义
/*S401  system configuration*/
uint8_t DID_F1F8[DID_F1F8_LENGTH] = {0x00,0x00,0x00,0x02,0x0E,0x13,0x00,0x81,0x00,0x0C,0x00,0xB8,0xF7,0x2B,0x1D,0x01};//EOL


DID_STRUCT  DIDList[] = 
{
#if (PROJECT_CODE == CHANGAN_R103_H15T)
	/*CACV ECU Application Software Version Number*/
	{0xF080,8,(uint8_t *)DID_F080,ATTRI_READONLY},
	/*CACV ECU Boot Software Version Number*/
	{0xF081,8,(uint8_t *)DID_F081,ATTRI_READONLY},
	/*CACV ECU Calibration Software Version Number*/
	{0xF082,8,(uint8_t *)DID_F082,ATTRI_READONLY},
	/*CACV ECU Hardware Version Number*/
	{0xF089,8,(uint8_t *)DID_F089,ATTRI_READONLY},
	/*CACV ECU Software Version Number*/
	{0xF189,8,(uint8_t *)DID_F189, ATTRI_READONLY},
	/*ECU Part Number*/
	{0xF187,21,(uint8_t *)DID_F187,ATTRI_READONLY},
	/*ECU Supplier Identification Code */
	{0xF18A, 7, (uint8_t *)DID_F18A, ATTRI_READONLY},//4
	/*NetworkinformationDataIdentifier */
	{0xF120, 4, (uint8_t *)DID_F120, ATTRI_READONLY},
	/*FunctionSpecificationDataIdentifier */
	{0xF121, 4, (uint8_t *)DID_F121, ATTRI_READONLY},
	/*DiagnosticDefinitionDataIdentifier */
	{0xF122, 4, (uint8_t *)DID_F122, ATTRI_READONLY},
	/*Supplier ECU Application Software Version Number */
	{0xF083, 8, (uint8_t *)DID_F083, ATTRI_READONLY},//4
	/*Supplier ECU Boot Software Version Number */
	{0xF084, 8, (uint8_t *)DID_F084, ATTRI_READONLY},
	/*Supplier ECU Calibration Software Version Number */
	{0xF085, 8, (uint8_t *)DID_F085, ATTRI_READONLY},
	/*Supplier ECU Hardware Version Number */
	{0xF193, 8, (uint8_t *)DID_F193, ATTRI_READONLY},	
	/*Supplier ECU Software Version Number */
	{0xF195, 8, (uint8_t *)DID_F195, ATTRI_READONLY},	

	/*Application Data Fingerprint Data Identifier*/
	{0xF184, DID_F184_LENGTH, DID_F184,ATTRI_WRITE},
	/*ECUSerialNumberDataIdentifier */
	{0xF18C, DID_F18C_LENGTH, DID_F18C,ATTRI_WRITE},
	/*Vehicle Identification Number*/
	{0xF190, DID_F190_LENGTH, DID_F190,ATTRI_WRITE},
	/*ECU Mode Configuration*/
	{0xF1A0, DID_F1A0_LENGTH, DID_F1A0,ATTRI_WRITE},
	/*Vehicle Manufacturing Date in CACV‘s production line */
	{0xF1A2, DID_F1A2_LENGTH, DID_F1A2,ATTRI_WRITE},
	/*System Configuration*/
	{0xF1FA, DID_F1FA_LENGTH, DID_F1FA,ATTRI_WRITE},
	/*HUConfigAtEOL */
	{0xFD01, DID_FD01_LENGTH, DID_FD01,ATTRI_WRITE},
#elif (PROJECT_CODE == CHANGAN_S401)
	/*CACV ECU Hardware Version Number*/
	{0xF089,8,(uint8_t *)DID_F089,ATTRI_READONLY},
	/*CACV ECU Software Version Number*/
	{0xF189,8,(uint8_t *)DID_F189, ATTRI_READONLY},
	/*ECU Part Number*/
	{0xF187,11,(uint8_t *)DID_F187,ATTRI_READONLY},
	/*ECU Supplier Identification Code */
	{0xF18A, 7, (uint8_t *)DID_F18A, ATTRI_READONLY},//4
	/*NetworkinformationDataIdentifier */
	{0xF120, 4, (uint8_t *)DID_F120, ATTRI_READONLY},
	/*FunctionSpecificationDataIdentifier */
	{0xF121, 4, (uint8_t *)DID_F121, ATTRI_READONLY},
	/*DiagnosticDefinitionDataIdentifier */
	{0xF122, 4, (uint8_t *)DID_F122, ATTRI_READONLY},
	/*system Supplier ECUHardware Version Number*/
	{0xF193, 16, (uint8_t *)DID_F193, ATTRI_READONLY},	
	/*Supplier ECU Software Version Number */
	{0xF195, 16, (uint8_t *)DID_F195, ATTRI_READONLY},
	/*system Supplier ECU Serial Number*/
	{0xF110, 28, (uint8_t *)DID_F110, ATTRI_READONLY},

	/*Radio Mode*/
	{0x6700, 1, (uint8_t *)DID_6700, ATTRI_READ},
	/*Radio Frequency*/
	{0x6701, 3, (uint8_t *)DID_6701, ATTRI_READ},
	/*Current Radio VOL*/
	{0x6702, 1, (uint8_t *)DID_6702, ATTRI_READ},
	/*HU BT Name*/
	{0x6703, 10,(uint8_t *)DID_6703, ATTRI_READ},
	/*HU BT MAC ADDR*/
	{0x6704, 6, (uint8_t *)DID_6704, ATTRI_READ},
	/*Total tracks in current selected device*/
	{0x6705, 2, (uint8_t *)DID_6705, ATTRI_READ},
	
	/*ECUSerialNumberDataIdentifier */
	{0xF18C, DID_F18C_LENGTH, DID_F18C,ATTRI_WRITE},
	/*Vehicle Identification Number*/
	{0xF190, DID_F190_LENGTH, DID_F190,ATTRI_WRITE},
	/*System Configuration*/
	{0xF1F8, DID_F1F8_LENGTH, DID_F1F8,ATTRI_WRITE},
	/*System Network Configuration Data Identifier*/
	{0xF101, DID_F101_LENGTH, DID_F101,ATTRI_WRITE},
#else

#endif
};
#endif

/*DTC LIST TABLE */
/*
 * attention: next table just place the used DTC, if not use, you should mask it. 
 */
DTC_STRUCT 	DTC_Tbl[]=
{
	#if ((CAR_TYPE_AT) && (!CAR_TYPE_MT))//AT
		//speaker and amp DTC
		{0x95,0x00,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FL_SC*/  //short circuit
		{0x95,0x00,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FL_OC*/  //open circuit
		{0x95,0x02,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FR_SC*/
		{0x95,0x02,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FR_OC*/
		{0x95,0x04,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_RL_SC*/
		{0x95,0x04,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_RL_OC*/
		{0x95,0x06,0x11,0x00,NOT_SUPPORT},   /*DTC_ID_SPK_RR_SC*/
		{0x95,0x06,0x13,0x00,NOT_SUPPORT},   /*DTC_ID_SPK_RR_OC*/
		{0x95,0x08,0x55,0x00,NOT_SUPPORT},   /*DTC_ID_AMP_CLIP */

		//power DTC
		{0xD1,0x01,0x16,0x00,SUPPORT},	/*DTC_ID_VOLT LOW */
		{0xD1,0x00,0x17,0x00,SUPPORT},	/*DTC_ID_VOLT HIGH */

		//canbus off DTC	
		{0xC0,0x19,0x88,0x00,SUPPORT},	/*DTC_ID_BODY_BUS_OFF*/
		{0xC0,0x01,0x88,0x00,NOT_SUPPORT},	/*DTC_ID_PT_BUS_OFF*/

		{0xC1,0x47,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_GW*/
		{0xD1,0x75,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_GW_32A*/
		//{0xD1,0x72,0x87,0x00},	/*DTC_ID_BUS_GW_2B0*/
		{0xD1,0x73,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_GW_320*/

		{0xC1,0x40,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_BCM*/
		{0xD1,0x48,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_BCM_347*/
		//{0xD1,0x47,0x87,0x00},	/*DTC_ID_BUS_BCM_288*/

		{0xC1,0x22,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_ESP*/
		{0xD1,0x35,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_ESP_218*/
		{0xD1,0x38,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_ESP_368*/

		{0xC1,0x64,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_AC*/
		{0xD1,0x45,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_AC_330*/

		{0xC1,0x00,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_EMS*/
		{0xD1,0x25,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_EMS_255*/

		{0xC1,0x59,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_RRS*/

		{0xD1,0x9C,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR_612*/
		{0xD1,0xC6,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR_613*/
		{0xD1,0x13,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR*/

		{0xD1,0xC3,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_PAC*/
	#elif ((!CAR_TYPE_AT) && (CAR_TYPE_MT))//MT
		//speaker and amp DTC
		{0x95,0x00,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FL_SC*/  //short circuit
		{0x95,0x00,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FL_OC*/  //open circuit
		{0x95,0x02,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FR_SC*/
		{0x95,0x02,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FR_OC*/
		{0x95,0x04,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_RL_SC*/
		{0x95,0x04,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_RL_OC*/
		{0x95,0x06,0x11,0x00,NOT_SUPPORT},   /*DTC_ID_SPK_RR_SC*/
		{0x95,0x06,0x13,0x00,NOT_SUPPORT},   /*DTC_ID_SPK_RR_OC*/
		{0x95,0x08,0x55,0x00,NOT_SUPPORT},   /*DTC_ID_AMP_CLIP */

		//power DTC
		{0xD1,0x01,0x16,0x00,SUPPORT},	/*DTC_ID_VOLT LOW */
		{0xD1,0x00,0x17,0x00,SUPPORT},	/*DTC_ID_VOLT HIGH */

		//canbus off DTC	
		{0xC0,0x19,0x88,0x00,NOT_SUPPORT},	/*DTC_ID_BODY_BUS_OFF*/
		{0xC0,0x01,0x88,0x00,SUPPORT},	/*DTC_ID_PT_BUS_OFF*/

		{0xC1,0x47,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_GW*/
		{0xD1,0x75,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_GW_32A*/
		//{0xD1,0x72,0x87,0x00},	/*DTC_ID_BUS_GW_2B0*/
		{0xD1,0x73,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_GW_320*/

		{0xC1,0x40,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_BCM*/
		{0xD1,0x48,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_BCM_347*/
		//{0xD1,0x47,0x87,0x00},	/*DTC_ID_BUS_BCM_288*/

		{0xC1,0x22,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_ESP*/
		{0xD1,0x35,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_ESP_218*/
		{0xD1,0x38,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_ESP_368*/

		{0xC1,0x64,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_AC*/
		{0xD1,0x45,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_AC_330*/

		{0xC1,0x00,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_EMS*/
		{0xD1,0x25,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_EMS_255*/

		{0xC1,0x59,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_RRS*/
		
		{0xD1,0x9C,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR_612*/
		{0xD1,0xC6,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR_613*/
		{0xD1,0x13,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR*/

		{0xD1,0xC3,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_PAC*/
	#else//all
		//speaker and amp DTC
		{0x95,0x00,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FL_SC*/  //short circuit
		{0x95,0x00,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FL_OC*/  //open circuit
		{0x95,0x02,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FR_SC*/
		{0x95,0x02,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_FR_OC*/
		{0x95,0x04,0x11,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_RL_SC*/
		{0x95,0x04,0x13,0x00,NOT_SUPPORT},	/*DTC_ID_SPK_RL_OC*/
		{0x95,0x06,0x11,0x00,NOT_SUPPORT},   /*DTC_ID_SPK_RR_SC*/
		{0x95,0x06,0x13,0x00,NOT_SUPPORT},   /*DTC_ID_SPK_RR_OC*/
		{0x95,0x08,0x55,0x00,NOT_SUPPORT},   /*DTC_ID_AMP_CLIP */

		//power DTC
		{0xD1,0x01,0x16,0x00,SUPPORT},	/*DTC_ID_VOLT LOW */
		{0xD1,0x00,0x17,0x00,SUPPORT},	/*DTC_ID_VOLT HIGH */

		//canbus off DTC	
		{0xC0,0x19,0x88,0x00,SUPPORT},	/*DTC_ID_BODY_BUS_OFF*/
		{0xC0,0x01,0x88,0x00,SUPPORT},	/*DTC_ID_PT_BUS_OFF*/

		{0xC1,0x47,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_GW*/
		{0xD1,0x75,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_GW_32A*/
		//{0xD1,0x72,0x87,0x00},	/*DTC_ID_BUS_GW_2B0*/
		{0xD1,0x73,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_GW_320*/

		{0xC1,0x40,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_BCM*/
		{0xD1,0x48,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_BCM_347*/
		//{0xD1,0x47,0x87,0x00},	/*DTC_ID_BUS_BCM_288*/

		{0xC1,0x22,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_ESP*/
		{0xD1,0x35,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_ESP_218*/
		{0xD1,0x38,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_ESP_368*/

		{0xC1,0x64,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_AC*/
		{0xD1,0x45,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_AC_330*/

		{0xC1,0x00,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_EMS*/
		{0xD1,0x25,0x87,0x00,NOT_SUPPORT},	/*DTC_ID_BUS_EMS_255*/

		{0xC1,0x59,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_RRS*/

		{0xD1,0x9C,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR_612*/
		{0xD1,0xC6,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR_613*/
		{0xD1,0x13,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_DVR*/

		{0xD1,0xC3,0x87,0x00,SUPPORT},	/*DTC_ID_BUS_PAC*/
	#endif
	
	{0x00,0x00,0x00,0x00},	/*DTC_ID_VALID_END*/
};

#if USR_UDS_SVC_RDBPI_EN
const RDBPI_STRUCT	RDBPI_Tbl[]=
{
	0xF1,1,0x00,0x00,0x00,0x00,0x00,
	0XF2,1,0x00,0x00,0x00,0x00,0x00,
	0XF3,1,0x00,0x00,0x00,0x00,0x00,
	0XF4,1,0x00,0x00,0x00,0x00,0x00,
	0xF5,1,0x00,0x00,0x00,0x00,0x00,
	0XF6,1,0x00,0x00,0x00,0x00,0x00,
	0XF7,1,0x00,0x00,0x00,0x00,0x00,
	0XF8,1,0x00,0x00,0x00,0x00,0x00,
	0xF9,1,0x00,0x00,0x00,0x00,0x00,
	0XFA,1,0x00,0x00,0x00,0x00,0x00,
	0xD1,1,0x00,0x00,0x00,0x00,0x00,
	0XD2,1,0x00,0x00,0x00,0x00,0x00,
	0XD3,1,0x00,0x00,0x00,0x00,0x00,
	0XD4,1,0x00,0x00,0x00,0x00,0x00,
	0xD5,1,0x00,0x00,0x00,0x00,0x00,
	0XD6,1,0x00,0x00,0x00,0x00,0x00,
	0XD7,1,0x00,0x00,0x00,0x00,0x00,
	0XD8,1,0x00,0x00,0x00,0x00,0x00,
	0xD9,1,0x00,0x00,0x00,0x00,0x00,
	0XDA,1,0x00,0x00,0x00,0x00,0x00,
};
#endif

#if UDS_SVC_IOCBI_EN
IOCONTROL_STRUCT  IOControlTable[]=
{
	{0x67e0, 0x00,0x00,NULL},
	{0x67e1, 0x00,0x00,NULL},
	{0x67e2, 0x00,0x00,NULL},
	{0x67e3, 0x00,0x00,NULL},
	{0x67e4, 0x00,0x00,NULL},
	{0x67e5, 0x00,0x00,NULL},
	{0x0000, 0x00,0x00,NULL},
};
#endif

uint16_t UdsRoutineIdTable[] = {UDS_ROUTINE_ID_ERASE, \
						UDS_ROUTINE_ID_CHK, \
					       	UDS_ROUTINE_ID_CHK_DESIGN, \
					       	UDS_ROUTINE_ID_CHK_PRE,\
					      	UDS_ROUTINE_ID_BOOT_RVD,\
					      	UDS_ROUTINE_ID_TAB_END};

const uint8_t UdsSecuritySeed[SECURITY_KEY_LENGTH]   = {0x12,0x34,0x56,0x78};

#if SECURITY_KEY_LENGTH != 4
#error "Param 'SECURITY_KEY_LENGTH' was wrong!"
#endif

void  Uds_LevelOneKeyArith(const uint8_t vseed[4],uint8_t GetLevelOnekey[4])
{
	uint8_t vKey1[4],vKey2[4] = {0,0,0,0};
	uint8_t i,j,vshift,vRshift,vLshift;
	uint32_t tempkey = 0; 

	uint8_t AppKeyConst[4] = {0x71, 0xf9, 0x6c, 0x1D};

	if(SECURITY_KEY_LENGTH != 4)
	{
		return;
	}
	
	for(i = 4;i > 0;i--)
	{
		vKey1[i - 1] = (uint8_t)(vseed[i - 1] ^ AppKeyConst[i - 1]);
						
		vRshift = 0x80;
		vLshift = 0x01;
		
		for(j = 0;j < 8;j++)
		{
			if(vseed[4 - i] & vRshift)
			{
				vKey2[i - 1] |= vLshift;
			}
			vRshift >>= 1;
			vLshift <<= 1;
		}				    	        
				
		vKey2[i - 1] = (uint8_t)(vKey2[i - 1] ^ AppKeyConst[i - 1]);
		
		vshift = (uint8_t)((4 - i) << 3);
		tempkey += (uint32_t)((uint32_t)((uint32_t)vKey1[i - 1] << (uint32_t)vshift) + \
					       (uint32_t)((uint32_t)vKey2[i - 1] << (uint32_t)vshift));
		
		GetLevelOnekey[i - 1] = (uint8_t)(tempkey >> vshift);
	}
		
}

void Uds_UpdateDTCStatus(eDTCIndex DtcIndex, uint8_t status)
{
	if(DtcIndex>= DTC_ID_VALID_END)
	{
		return;
	}
	if(STATE_ON != Uds_GetDTCSettingState())
	{
		return;
	}
	switch(DtcIndex)
	{
		case DTC_ID_BUS_GW:
		case DTC_ID_BUS_GW_320:
		case DTC_ID_BUS_GW_32A:
		case DTC_ID_BUS_BCM:
		case DTC_ID_BUS_BCM_347:
		case DTC_ID_BUS_ESP:
		case DTC_ID_BUS_ESP_218:
		case DTC_ID_BUS_ESP_368:
		case DTC_ID_BUS_AC:
		case DTC_ID_BUS_AC_330:
		case DTC_ID_BUS_EMS:
		case DTC_ID_BUS_EMS_255:
		case DTC_ID_BUS_RRS:
		case DTC_ID_BUS_DVR:
		case DTC_ID_BUS_KEYBOARD:
		case DTC_ID_BUS_LCM:
		case DTC_ID_BUS_PEPS:
		case DTC_ID_BUS_TBOX:
		case DTC_ID_BUS_PAC:
		case DTC_ID_BUS_AVM:
		case DTC_ID_BUS_IP:
			if(TRUE == Uds_GetMsgTransEnableState(MSG_NCM, MSG_TRANS_RX))
			{
				//if(DTC_Tbl[DtcIndex].IsSupport == SUPPORT) //snake20160804
				{
					DTC_Tbl[DtcIndex].DTCStatus = status;
				}
			}
			break;
		case DTC_ID_SPK_FL_SC:
		case DTC_ID_SPK_FR_SC:
		case DTC_ID_SPK_RL_SC:
		case DTC_ID_SPK_RR_SC:
		case DTC_ID_SPK_FL_OC:
		case DTC_ID_SPK_FR_OC:
		case DTC_ID_SPK_RL_OC:
		case DTC_ID_SPK_RR_OC:
		case DTC_ID_AMP_CLIP:
		case DTC_ID_VOLT_LOW:
		case DTC_ID_VOLT_HIGH:
		case DTC_ID_AMP_OC:
		case DTC_ID_AMP_SC_GND:
		case DTC_ID_AMP_SC_POWER:
		case DTC_ID_SPK_OC:
		case DTC_ID_SPK_SC_GND:
		case DTC_ID_SPK_SC_POWER:
		case DTC_ID_GPS_OC:
		case DTC_ID_GPS_SC_GND:
		case DTC_ID_GPS_SC_POWER:
		case DTC_ID_TUNER_OC:
		case DTC_ID_TUNER_SC_GND:
		case DTC_ID_TUNER_SC_POWER:
		case DTC_ID_BODY_BUS_OFF:
		case DTC_ID_PT_BUS_OFF:
			//if(DTC_Tbl[DtcIndex].IsSupport == SUPPORT) //snake20160804
			{
				DTC_Tbl[DtcIndex].DTCStatus = status;
			}
			break;
		default:
			break;
	}
}

uint8_t Uds_GetCfgTblTotalNum(void)
{
	return sizeof(UdsServiceCfgTbl)/ sizeof(UdsServiceCfgStruct);
}

DID_STRUCT*	Uds_GetDIDCfgTable(void)
{
#if (USR_UDS_SVC_WDBI_EN || USR_UDS_SVC_RDBI_EN)
	return &DIDList[0];
#else
       return NULL;
#endif
}

uint8_t  Uds_GetDIDTblTotalNum(void)
{
#if (USR_UDS_SVC_WDBI_EN || USR_UDS_SVC_RDBI_EN)
	return sizeof(DIDList)/sizeof(DID_STRUCT);
#else
       return 0;
#endif
}

uint8_t Uds_GetDidIndex(uint16_t did)
{
	uint8_t i = 0;
	uint8_t total = Uds_GetDIDTblTotalNum();
	
	for(i = 0; i< total; i++)
	{
		if(did == DIDList[i].DID_Id)
		{
			return i;
		}
	}

	return 0xff;
}

uint8_t * Uds_GetSecuritySeedPoint(void)
{
	return (uint8_t*)&UdsSecuritySeed[0];
}

DTC_STRUCT     *Uds_GetDTCTable(void)
{
	return &DTC_Tbl[0];
}

RDBPI_STRUCT * Uds_GetRDBPIPoint(void)
{
#if USR_UDS_SVC_RDBPI_EN
	return (RDBPI_STRUCT*)&RDBPI_Tbl[0];
#else
       return NULL;
#endif
}

const uint8_t *pUds_GetCarTypeDefaultEOL(uint8_t CarType)
{
	const uint8_t * pCarTypeDefaultEOL=NULL;
#if (USR_UDS_SVC_WDBI_EN || USR_UDS_SVC_RDBI_EN)	
	if(CarType>=CAR_TYPE_SEL_MAX)
	{
		return pCarTypeDefaultEOL;
	}
	pCarTypeDefaultEOL=gEOLList[CarType];
#endif	
	return pCarTypeDefaultEOL;
}

void Uds_UserIOControlHook(uint8_t index)
{
	//accoring your project to execute the application.
	// note that: dont forget to give the response(passive/active).
	uint16_t Did = IOControlTable[index].DID;
	uint8_t ControlParam = IOControlTable[index].ControlParameter;
	uint8_t RespParam[6];
	uint8_t RespLen = 0;

	RespParam[0] = Did>>8;
	RespParam[1] = Did&0xff;
	RespParam[2] = ControlParam;
	switch(Did)
	{
		case 0x67e0:		//BackLight ON/OFF
			if(ControlParam== IOC_returnControlToECU)
			{
				RespLen = 3;
				
			}
			else if(ControlParam== IOC_resetToDefault)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_shortTermAdjustment)
			{
				uint8_t param =  IOControlTable[index].pOption[0];
				if(param<=1)
				{
					 _SendMsgToPM(MS_PM_TFT_BL_CMD, param, NULL);
					 RespParam[3] = param; 
					 RespLen = 4;
				}
			}
			else
			{
				Uds_Response_Negative(ROOR);	
			}
			break;
		case 0x67e1:		//KeyPad BackLight ON/OFF
			if(ControlParam== IOC_returnControlToECU)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_resetToDefault)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_shortTermAdjustment)
			{
				uint8_t param =  IOControlTable[index].pOption[0];
				if(param<=1)
				{
				//	 need add execute code.
					 RespParam[3] = param; 
					 RespLen = 4;
				}
			}
			else
			{
				Uds_Response_Negative(ROOR);	
			}
			break;
		case 0x67e2:		//BlueTooth ON/OFF
			if(ControlParam== IOC_returnControlToECU)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_resetToDefault)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_shortTermAdjustment)
			{
				uint8_t param =  IOControlTable[index].pOption[0];
				if(param<=1)
				{
					 MDI_SendUiccToMedia(UICC_BT_CTL, param);
					 RespParam[3] = param; 
					 RespLen = 4;
				}
			}
			else
			{
				Uds_Response_Negative(ROOR);	
			}
			break;
		case 0x67e3:		//Audio MUTE/UNMUTE
			if(ControlParam== IOC_returnControlToECU)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_resetToDefault)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_shortTermAdjustment)
			{
				uint8_t param =  IOControlTable[index].pOption[0];
				if(param<=1)
				{
					_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE,0,0,0,0);  
					 RespParam[3] = param; 
					 RespLen = 4;
				}
			}
			else
			{
				Uds_Response_Negative(ROOR);	
			}
			break;
		case 0x67e4:		//Media play/pause
			if(ControlParam== IOC_returnControlToECU)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_resetToDefault)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_shortTermAdjustment)
			{
				uint8_t param =  IOControlTable[index].pOption[0];
				if(param<=1)
				{
					 MDI_SendUiccToMedia(UICC_MEDIA_CTL, param);
					 RespParam[3] = param; 
					 RespLen = 4;
				}
			}
			else
			{
				Uds_Response_Negative(ROOR);	
			}
			break;
		case 0x67e5:		//PAC power on/off
			if(ControlParam== IOC_returnControlToECU)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_resetToDefault)
			{
				RespLen = 3;
			}
			else if(ControlParam== IOC_shortTermAdjustment)
			{
				uint8_t param =  IOControlTable[index].pOption[0];
				if(param<=1)
				{
					 PM_UnitPowerSet(PM_UNIT_RADAR,param);
					 RespParam[3] = param; 
					 RespLen = 4;
				}
			}
			else
			{
				Uds_Response_Negative(ROOR);	
			}
			break;
		default:
			Uds_Response_Negative(ROOR);	
			break;
	}

	if(RespLen>0)
	{
		Uds_IOControl_PosRsp(RespParam, RespLen);
	}
}
#endif
/****************************************************************************
 * **                                        FILE END
****************************************************************************/


