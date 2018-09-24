/**********************************************************
 * @file       Mult_Function.c
 * @purpose    Functions of Mult_Function
 * @version    0.01
 * @date        05. March. 2014
 * @author    LKM
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *                         
 *  
  **********************************************************/
#define _MULT_FUNCTION_C_
#include "..\config\inc.h"



#define LEVEL1					1		/*< 6.5V*/
#define LEVEL2					2		/*<6.9V*/
#define LEVEL3					3		/*<8.7V*/
#define LEVEL4					4		/*<9.5V*/
#define LEVEL5					5		/*<17.6V*/
#define LEVEL6					6		/*<18.0V*/	
#define LEVEL7					7		/*>18.0V*/
typedef enum{
	BATT_STATE_NORMAL,
	BATT_STATE_HVI,//over 18V
	BATT_STATE_LVI1,//close screen
	BATT_STATE_LVI2//close bus
}ADC_BATT_STATE;

#define AD_BATT_NUM			10		/*Sample num */


uint8_t VoltChgDirection;		//up
uint8_t BattADCCurState;


tRING_QUE 	Mult_Function_TaskMsgQue;
tMSG_BUF	Mult_Function_TaskMsgBuf[D_MULT_FUNCTION_MSG_QUE_DEEP];


static uint8_t Flag_Refresh;
static uint8_t last_level=LEVEL2;


void BattADCInit(void)
{
       last_level=LEVEL2;
	VoltChgDirection = 1;		//up
	BattADCCurState = BATT_STATE_LVI2;

}


void HmiStatusFlagInit(void)
{
	HMIStatusFlag.g_tBlindStatus = 0;
	HMIStatusFlag.g_tReverseStatus = 0;
	HMIStatusFlag.g_tUpdataReverseParameter = 0;
	HMIStatusFlag.g_tUpdataBlindParameter = 0;
	HMIStatusFlag.g_tCanbusWakeUpFlag = 0;
//	HMIStatusFlag.g_tAVMVol=0;
//	HMIStatusFlag.g_tBackdropVolFlag=0;
//	HMIStatusFlag.g_tMonitorOff=1;  // xjh modify for note 3 in svn
//	HMIStatusFlag.gAvmOrBlindStatus=0;
//	HMIStatusFlag.BlindPressFlag=0;
//	HMIStatusFlag.g_tAvmStatus=0; 	
//	//HMIStatusFlag.g_tBTAppTone=0;
//	HMIStatusFlag.g_tBTAppexit=0;
//	HMIStatusFlag.Volbackup=0;
}

uint8_t Mult_Function_Init(void)
{
	BattADCInit();
	HmiStatusFlagInit();
	IO_Scan_Set(IO_IDX_AUX_DET,ENABLE);
	IO_Scan_Set(IO_IDX_AVM_DET,ENABLE);
	#ifndef D_ILL_ADC_CHECK  //snake20160822 add
	IO_Scan(IO_IDX_ILL_DET,ENABLE);
	#endif
	
	Mult_Struct.FuncDelay = 0;
	Mult_Struct.AccState = 0;
	Mult_Struct.AccStateBK = 0;
	Mult_Struct.IllState = 0;
	Mult_Struct.IllStateBK = 0;
	Mult_Struct.ApuEnterSys = 0;
	Mult_Struct.ApuEnterSysBK = 0;
	
	g_status_avm_reverse = NORMAL_STATUS;
	Flag_Refresh = 0;

	SrcType.LENGTH = sizeof(SrcTypeStruc);
	SrcType.GID = 0x67;
	SrcType.SID = 0x03;
	SrcType.srctype0 = 0x00;
	SrcType.srctype1 = 0x00;
	SrcType.srctype2 = 0x00;

	return TRUE;
}

/**********************************************************
 * @function    Camera_OnOffDet
 * @brief      
 * @param      
 * @retval     
 **********************************************************/
//uint8_t Camera_OnOffDet(void)
//{
//	if((g_tMcuDevState.uIOState.bits.Reverse_Flag)||(HMIStatusFlag.gAvmOrBlindStatus))
//	   return 1;
//	else 
//	   return 0;
//}
/**********************************************************
 * @function    Monitor_TempOn
 * @brief      
 * @param      
 * @retval     
 **********************************************************/
void Monitor_TempOn(uint8_t flag)
{
   //   hmi_printf(_T("Monitor_TempOn:%d,%d\n",flag,HMIStatusFlag.g_tMonitorOff));
     // if(OFF == HMIStatusFlag.g_tMonitorOff)
    //      _SendFullMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_UICC_CMD,UICC_TFT_STANDBY,flag,0,0);
 }
/**********************************************************
 * @function    AUX_InsertDet
 * @brief      check aux insert state run it in 12ms tick
 * @param      PortStatus    ==> Port status of disc insert pin
 * @retval     TURE
 **********************************************************/
uint8_t AUX_InsertDet(void)
{
	 uint8_t re = FALSE;
  	 static uint8_t cnt = 0;
	cnt++;
	if(cnt >= 5)		//by hmc  20160812  需要延时检测AUX，防止在插拔耳机过程中多次进入或者退出的情况
	{	
		IO_Scan(IO_IDX_AUX_DET,PIN_INPUT);
		cnt = 0;
	}
	return re;
}
/**********************************************************
 * @function    ILL_InsertDet
 * @brief      check ill open state run it in 12ms tick
 * @param      PortStatus    ==> Port status of ill open check pin
 * @retval     TURE
 **********************************************************/
uint8_t ILL_InsertDet(void)
{
	 uint8_t re = FALSE;
	IO_Scan(IO_IDX_ILL_DET,PIN_INPUT);
	return re;
}

/**********************************************************
 * @function    AVM_InsertDet
 * @brief      check aux insert state run it in 12ms tick
 * @param      PortStatus    ==> Port status of disc insert pin
 * @retval     TURE
 **********************************************************/

uint8_t AVM_KeyDet(void)
{
    uint8_t re = FALSE;
     IO_Scan(IO_IDX_AVM_DET,PIN_INPUT);
    return re;
}

/**********************************************************
* @function   PanelLed_SwitchDeal
* @brief      
* @param      led switch Status ON/OFF
* @retval     null
**********************************************************/
void PanelLed_SwitchDeal(uint8_t Status)
{
	uint8_t IllState = 0;
	uint8_t Duty = 0;
	#ifndef D_ILL_ADC_CHECK
	IllState = IO_Get(IO_IDX_ILL_DET,PIN_INPUT, FALSE);
	#else
	IllState = g_tMcuDevState.uIOState.bits.Illumi_On;
	#endif

	Mult_Struct.ApuEnterSys = l_tMediaCB.uDevFlag.field.bUnLocked;
	
    if(Status)
   	{
		Duty = IllState?8:95;
		IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,Duty);
		if(!SRC_GetSrcBlockBaseType (SRC_TYPE_AVOFF,SRC_LIST_RUNTIME ) && Mult_Struct.ApuEnterSys)//check avoff state
		{
			IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,Duty);
		}
    }
	else
	{
		IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,Duty);
		IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,Duty);
	}
}

/**********************************************************
* @function   PanelLed_PWMDeal
* @brief      
* @param      
* @retval     null
**********************************************************/
void PanelLed_PWMDeal(void)
{
	uint8_t Duty = 0;
	Mult_Struct.AccState = IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT, FALSE);
	#ifndef D_ILL_ADC_CHECK//snake20160822 
	Mult_Struct.IllState = IO_Get(IO_IDX_ILL_DET,PIN_INPUT, FALSE);
	#else
	Mult_Struct.IllState = g_tMcuDevState.uIOState.bits.Illumi_On;
	#endif
	
	Mult_Struct.ApuEnterSys = l_tMediaCB.uDevFlag.field.bUnLocked;
	
	if(Mult_Struct.AccState != Mult_Struct.AccStateBK)
	{
		mult_printf(_T("ACC STATE CHANGE:%d----->%d\n",Mult_Struct.AccStateBK,Mult_Struct.AccState));
		Mult_Struct.AccStateBK = Mult_Struct.AccState;
		if(Mult_Struct.AccState)
		{
			Duty = Mult_Struct.IllState?8:95;
			IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,Duty);
			if(!SRC_GetSrcBlockBaseType(SRC_TYPE_AVOFF,SRC_LIST_RUNTIME ) && Mult_Struct.ApuEnterSys)//check avoff state
			{
				IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,Duty);
			}
		}
		else
		{
			#ifdef D_ILL_WAKEUP
				Duty = Mult_Struct.IllState?8:0;
			#else
				Duty = 0;
			#endif
			if(Duty)
			{
				IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,Duty);
				if(!SRC_GetSrcBlockBaseType (SRC_TYPE_AVOFF,SRC_LIST_RUNTIME ) && Mult_Struct.ApuEnterSys)//check avoff state
				{
					IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,Duty);
				}
			}
			else
			{
				IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,Duty);
				IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,Duty);
			}
		}
	}

	if(Mult_Struct.IllState != Mult_Struct.IllStateBK)
	{
		mult_printf(_T("ILL STATE CHANGE:%d----->%d\n",Mult_Struct.IllStateBK,Mult_Struct.IllState));
		Mult_Struct.IllStateBK = Mult_Struct.IllState;
		if(Mult_Struct.IllState)
		{
			Duty = 8;//Mult_Struct.AccState?8:0;
			IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,Duty);
			if(!SRC_GetSrcBlockBaseType (SRC_TYPE_AVOFF,SRC_LIST_RUNTIME ) && Mult_Struct.ApuEnterSys)//check avoff state
			{
				IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,Duty);
			}
		}
		else
		{
			Duty = Mult_Struct.AccState?95:0;
			IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,Duty);
			if(!SRC_GetSrcBlockBaseType (SRC_TYPE_AVOFF,SRC_LIST_RUNTIME ) && Mult_Struct.ApuEnterSys)//check avoff state
			{
				IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,Duty);
			}
		}
		mult_printf(_T("[ILL]---Duty = %d\n",Duty));
	}

	if(Mult_Struct.ApuEnterSys != Mult_Struct.ApuEnterSysBK)
	{
		mult_printf(_T("System STATE CHANGE:%d----->%d\n",Mult_Struct.ApuEnterSysBK,Mult_Struct.ApuEnterSys));
		Mult_Struct.ApuEnterSysBK = Mult_Struct.ApuEnterSys;
		if(Mult_Struct.ApuEnterSys)
		{
			Duty = Mult_Struct.IllState?8:95;
			IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,Duty);
			IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,Duty);
		}
	}
}


void Mult_VirtualTimer(void)
{
    //if(Mult_Struct.FuncDelay)Mult_Struct.FuncDelay--;
}

void Mult_Function_Task(EVENT iEvt,eTASK_STATE eState)
{
	EOLCfgStruct *pEOLCfg=pCAN_GetEOLStr();
	if(eState == TASK_STATE_READY)
	{
		if((!OS_TaskIsActive(TASK_ID_MULT_FUNCTION))&&(OS_TaskIsActive(TASK_ID_HMI)))
		{
			OS_TaskStart(TASK_ID_MULT_FUNCTION);
		}
	}
	else if(eState == TASK_STATE_RUNNING)
	{
		if(iEvt & EVT_TASK_TICK_READY)
		{
			if(Mult_Struct.FuncDelay < 400)
			{
				Mult_Struct.FuncDelay++;
				return;
			}
			else
			{
				if(Flag_Refresh == 0)
				{
					Flag_Refresh = 1;
					_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);//upgrade backlight level
				}			
				AVM_KeyDet();
				//AVMReverseHandler();
				
				#ifdef D_AUX_EOL
				if(pEOLCfg->EOLState.bits.AUXSupport)
				#endif
					AUX_InsertDet();
				
				#ifndef D_ILL_ADC_CHECK //snake20160822
					ILL_InsertDet();
				#endif
			}
		}
	}

	if(iEvt & EVT_MSG_READY)
	{
		tMSG_BUF tMsg;
		if(QUE_ERR_NONE == OS_GetMsgDir(&g_tMult_FunctionTaskCB,&tMsg))
		{
			if(tMsg.Id == IO_IDX_BATTERY_DET)
			{
				BattADC_Process((uint8_t)tMsg.iSid);
				mult_printf(_T("BAT Idx = %d\n",(uint8_t)tMsg.iSid));
			}
			else if(tMsg.Id == MS_PM_STATE)
			{
				switch(tMsg.iSid)
				{
					case OP_PM_STATE_OFF:
						Mult_Struct.FuncDelay = 0;	
						Flag_Refresh = 0;
						break;

					default:
						break;
				}
			}
		}
	}

	
}

static const tTASK_BLOCK Mult_Function_TCB = 
{
	"MULT_FUNCTION",
	_set_timing_xms_base_core_tick(_10MS_),
	_set_timing_xms_base_core_tick(_10MS_),
	Mult_Function_Task,
	Mult_Function_Init,
	NULL,
};


bool Mult_Function_TaskCreate(void)
{
	BattADCInit();
	return OS_TaskCreate(TASK_ID_MULT_FUNCTION, 
	               			&g_tMult_FunctionTaskCB,
					&Mult_Function_TCB,
					&Mult_Function_TaskMsgQue,
					Mult_Function_TaskMsgBuf,
					D_MULT_FUNCTION_MSG_QUE_DEEP);
}


	
void BattADC_Process(uint8_t level)
{

	//static uint8_t last_level = LEVEL2;
	uint8_t level_true;

	switch(level)
	{
		case PM_BATLEV_LOWEST:/*V < 6.5V*/
			level = LEVEL1;
			break;

		case PM_BATLEV_LOW_OFF:/*6.9V < V < 9.0V*/
			level = LEVEL3;
			break;

		case PM_BATLEV_LOW_ON:/*9.0V < V <9.5V*/
			level = LEVEL4;
			break;
			
		case PM_BATLEV_NORMAL:/*9.5V < V < 17.6V*/
			level = LEVEL5;
			break;
			
		case PM_BATLEV_HIGHT_ON:/*17.6V < V < 18V*/
			level = LEVEL6;
			break;
			
		case PM_BATLEV_HIGHT_OFF:/*V > 18V*/
			level = LEVEL7;
			break;
			
		case PM_BATLEV_HIGHTEST:/*6.9V < V < 9.0V*/
			level = LEVEL7;
			break;

		default:
			break;
	}
	
	if(level > last_level)
	{
		VoltChgDirection = 1;
	}
	else
	{
		VoltChgDirection = 0;
	}
	
	last_level = level;

	switch(BattADCCurState)
	{
		case BATT_STATE_NORMAL:
			if(VoltChgDirection)
			{
				if(level == LEVEL7)
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_H,NULL);
					 BattADCCurState = BATT_STATE_HVI;
				}				
			}
			else
			{
				if(level == LEVEL1)
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_C,NULL);
					 BattADCCurState = BATT_STATE_LVI2;
				}
				else if((level == LEVEL3)||(level == LEVEL2))
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_B,NULL);
					 BattADCCurState = BATT_STATE_LVI1;
				}
			}
			break;
			
		case BATT_STATE_HVI:
			if(VoltChgDirection == 0)
			{	
				if(level == LEVEL1)
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_C,NULL);
					 BattADCCurState = BATT_STATE_LVI2;
				}
				else if((level == LEVEL3)||(level == LEVEL2))
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_B,NULL);
					 BattADCCurState = BATT_STATE_LVI1;
				}
				else if((level == LEVEL5)||(level == LEVEL4))
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_A,NULL);
					 BattADCCurState = BATT_STATE_NORMAL;
				}
			}
			break;
			
		case BATT_STATE_LVI1:
			if(VoltChgDirection)
			{
				if(level == LEVEL7)
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_H,NULL);
					 BattADCCurState = BATT_STATE_HVI;
				}
				else if((level == LEVEL5)||(level == LEVEL6))
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_F,NULL);
					 BattADCCurState = BATT_STATE_NORMAL;
				}
			}
			else
			{
				if(level == LEVEL1)
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_C,NULL);
					 BattADCCurState = BATT_STATE_LVI2;
				}
			}
			break;
			
		case BATT_STATE_LVI2:
			if(VoltChgDirection)
			{
				if(level == LEVEL7)
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_H,NULL);
					 BattADCCurState = BATT_STATE_HVI;
				}
				else if((level == LEVEL5)||(level == LEVEL6))
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_F,NULL);
					 BattADCCurState = BATT_STATE_NORMAL;
				}
				else if((level == LEVEL3)||(level == LEVEL4))
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_E,NULL);
					 BattADCCurState = BATT_STATE_LVI1;
				}
				else if(level == LEVEL2)
				{
					 _SendMsgToCanbus(MS_OTHER_VOLTAGE,OP_OTHER_D,NULL);
					 BattADCCurState = BATT_STATE_LVI1;				
				}
			}
			break;
			
		default:
			break;
	}
}
