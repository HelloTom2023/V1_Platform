#ifndef _MULT_FUNCTION_H_

#define _MULT_FUNCTION_H_

#ifdef _MULT_FUNCTION_C_
#define _MULT_FUNCTION_
#else
#define _MULT_FUNCTION_ extern
#endif


#define D_MULT_FUNCTION_MSG_QUE_DEEP		8

typedef enum
{
	NORMAL_STATUS,
	AVM_REVERSE_STATUS		
}STATUS_REVERSE;

_MULT_FUNCTION_	uint8_t g_cBaseBR;
_MULT_FUNCTION_	STATUS_REVERSE g_status_avm_reverse;

_MULT_FUNCTION_ tTASK_CTRL_BLOCK g_tMult_FunctionTaskCB;

_MULT_FUNCTION_	void Mult_Function_Task(EVENT iEvt,eTASK_STATE eState);
_MULT_FUNCTION_	uint8_t Mult_Function_TaskCreate(void);
_MULT_FUNCTION_ uint8_t AUX_InsertDet(void);
_MULT_FUNCTION_ uint8_t  ILL_InsertDet(void);//snake20160819_add
_MULT_FUNCTION_ uint8_t AVM_KeyDet(void);//lkm201404003_add
_MULT_FUNCTION_ void PanelLed_SwitchDeal(uint8_t Status);//snake20160816 add
_MULT_FUNCTION_ void PanelLed_PWMDeal(void);

_MULT_FUNCTION_ uint8_t Camera_OnOffDet(void);
_MULT_FUNCTION_ void Monitor_TempOn(uint8_t flag);

_MULT_FUNCTION_ void Mult_VirtualTimer(void);
_MULT_FUNCTION_ void BattADC_Process(uint8_t level);
_MULT_FUNCTION_ void Mult_WriteFacCfgToCache(uint8_t FacCfgID,uint8_t FacCfgData);


#define OPEN_TESTTUNER		1
#define CLOSE_TESTTUNER		0
#define AUX_SCAN_CNT 5

#if D_DEBUG_MULT && D_PRINT_EN
#define mult_printf(x)  x
#else
#define mult_printf(x)
#endif

typedef struct
{
	uint16_t FuncDelay;
	uint8_t  TestTuner;
	uint8_t  Test_flag;
	uint16_t   time_tick;
	
	uint8_t AccState:1;
	uint8_t AccStateBK:1;
	uint8_t IllState:1;
	uint8_t IllStateBK:1;
	uint8_t ApuEnterSys:1;
	uint8_t ApuEnterSysBK:1;
	uint8_t Reserved:2;
	
}MULT_STRUCT;

typedef union{        
       uint8_t a_cData[sizeof(void*)];
       void*         p_cData;
}TEST_DATA;

typedef struct
{
       uint8_t   LENGTH;
       uint8_t   GID;
       uint8_t   SID;
 /*------------DATA[0]--------------------------------*/	
        uint8_t  srctype0;
 /*------------DATA[1]--------------------------------*/	
	uint8_t  srctype1;
 	uint8_t  srctype2;
 	uint8_t  srcGid;
 	uint8_t  srcSid;
 	uint8_t  srcD[4];
}SrcTypeStruc;

typedef struct
{
	/*
	//---------------------------------------//
	uint8_t g_tAVMVol            :7  ;//remember current vol 
	uint8_t  g_tBackdropVolFlag          :1;////Param 1 :in BackdropVol status ,0:not
	//--------------------------------------//
	uint8_t g_tMonitorOff             :1;    //Param 1 :in monitor off source ,0:not
	uint8_t gAvmOrBlindStatus                 :1;  //Param 1 :in AvmOrBlind ,0:not   in AvmOrBlind
	uint8_t BlindPressFlag        :1;   //Param 1 :Reverse,0:normal   in monitor
	uint8_t g_tAvmStatus              :2;   //Param 1:first AVM then reverse  control in monitor
	//uint8_t  g_tBTAppTone           :2;   //Param 1 :BTPhone App Tone ,0:others
	uint8_t  g_tBTAppexit    :1;
	//--------------------------------------------//
	uint8_t  Volbackup;
	*/
	uint8_t g_tBlindStatus        :1;   //Param 1 :blind,0:normal  
	uint8_t g_tReverseStatus     :1;   //Param 1 :Reverse,0:normal  
	uint8_t g_tUpdataReverseParameter       :1;
	uint8_t g_tUpdataBlindParameter          :1;
	uint8_t g_tCanbusWakeUpFlag :1;
}HMI_STATUS_FLAG_STRUCT;

typedef struct
{
	union
	{
        uint8_t Byte1;
        struct
        {
            bit_t ECO_Exist         :1;        // bit_t 0.
            bit_t AVM_Exist         :1;        // bit_t 1.
            bit_t Blind_Exist         :1;        // bit_t 2.
            bit_t AutoFold_Exist 		:1;
            bit_t RearAssist_Exist 		:1;  //Rear Reverse Assist
            bit_t CdBox_Exist 		:1;
            bit_t Reserve : 2;
        }Bits1;
	}FacCfg1;
	union
	{
		uint8_t Byte2;
		struct
		{
			uint8_t Reserved:8;
		}Bits2;
	}FacCfg2;
}FacMcuFlag_t;

_MULT_FUNCTION_		FacMcuFlag_t FacCfg;
_MULT_FUNCTION_		HMI_STATUS_FLAG_STRUCT   HMIStatusFlag;  //keilee 20140614 
_MULT_FUNCTION_		MULT_STRUCT Mult_Struct;
_MULT_FUNCTION_		SrcTypeStruc SrcType;

#define _SendFullMsgToMult_Func(gid,sid,d0,d1,d2,d3)  	OS_PostFullMsgDir(&g_tMult_FunctionTaskCB,(uint16_t)(gid),(uint16_t)(sid),(uint8_t)(d0),(uint8_t)(d1),(uint8_t)(d2),(uint8_t)(d3))
#define _SendMsgToMult_Func(gid,sid,buf)                      	OS_PostMsgDir(&g_tMult_FunctionTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf))
#define _InsertMsgToMult_Func(gid,sid,buf) 			OS_InsertMsgDir(&g_tMult_FunctionTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf),0)

//#define DEBUG_TUNER_UPDATE
//#define DEBUG_GEQ_PEQ
#endif

