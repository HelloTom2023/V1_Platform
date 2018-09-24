/***********************( Copyright infomation )********************************
 * FILE      :
 * INFOMATIN :
 * VERSION   : v00
 * DATA      : 22/05, 2013
 * AUTHOR    : koller yang
 *
 * UPDATE    :
 * ---------------------------------------------
 *   | INFOMATION  2013-11-2     2014-3-2   2014-06-08
 *   | VERSION     v0.1           v0.2        v0.3
 *   | AUTHOR      koller
 *   -------------------------------------------
 *     |  Rewrite it one and one time!! Fuck this code!
 *     |  
 ******************************************************************************/
#define _PM_C_
#include "..\..\..\User\src_user\config\inc.h"
//#include "..\..\..\..\Code_user\User\src_user\config\inc.h"

#define PM_GetMsg(buf)            OS_GetMsgDir(&g_tPMTaskCB,(tMSG_BUF*)(buf))

extern void PM_Lv5686Init(void);



extern const tPM_DELAY_TIME_TAB lc_tPMDlyTimingTab;

/*******************************************************************************
*TFT POWER(VHL,12V) must be set befor setting TFT_EN when open tft.
*When close it, do adversely.
*******************************************************************************/
void PM_TftPowerManage(void)
{   
    l_tTftCB.iTimer ++;
    switch(l_tTftCB.eState)
    {
        case PM_TFT_OFF:
        break;
        case PM_TFT_DEV_ON:
		{
			PM_UnitPowerSet(PM_UNIT_TFT , ON);
			l_tTftCB.eState = PM_TFT_FB_ON;
			l_tTftCB.iTimer = 0;
			pm_printf(_T("PM_TFT_DEV_ON\n"));
		}
        break;
        case PM_TFT_FB_ON:
			IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,ON);
			IO_Set(IO_IDX_TFT_VGL,PIN_OUTPUT,ON);
			l_tTftCB.iTimer = 0;
			l_tTftCB.eState = PM_TFT_LED_ON;
			pm_printf(_T("PM_TFT_FB_ON\n"));
	        break;
		case PM_TFT_LED_ON: 
           // if(l_tTftCB.iTimer > l_tTftCB.iEnTimming)
		{
			_SendMsgToHMI(MS_PM_TFT_INFO,OP_DEV_STATE_NORMAL,NULL);
			l_tTftCB.iTimer =  _set_timing_xms_base_pwr_task_tick(20);
			l_tTftCB.eState  = PM_TFT_ON;

			l_tTftCB.tCurrPwmLevel = PM_GetTftBLValue();
			pm_printf(_T("PM_TFT_LED_ON\n"));
			pm_printf(_T("CurrPwmlevel = %d,tLastPwmLevel = %d\n",l_tTftCB.tCurrPwmLevel,l_tTftCB.tLastPwmLevel));
		}
        break;
        
        case PM_TFT_ON: 
	#ifdef D_TFT_OPEN_GRADIENT //snake20160922
            if(l_tTftCB.iTimer  > _set_timing_xms_base_pwr_task_tick(20))//Dalay 20
            {
                uint8_t cTmpBL = l_tTftCB.tCurrPwmLevel;					
                if(cTmpBL > l_tTftCB.tLastPwmLevel)
				{
				//l_tTftCB.tLastPwmLevel ++;
				l_tTftCB.tLastPwmLevel = l_tTftCB.tLastPwmLevel +2;
				IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT,l_tTftCB.tLastPwmLevel);
				pm_printf(_T("+++++TFT PwmLevel:%d\n",l_tTftCB.tLastPwmLevel));

				}   
				else if(l_tTftCB.tLastPwmLevel == cTmpBL+1)
				{
					IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT, l_tTftCB.tLastPwmLevel);
					//pm_printf(_T(" cTmpBL=%x\n", cTmpBL);
				}
				else if(l_tTftCB.tLastPwmLevel > cTmpBL)
				{
					// l_tTftCB.tLastPwmLevel --;
					l_tTftCB.tLastPwmLevel = l_tTftCB.tLastPwmLevel -2;
					IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT,l_tTftCB.tLastPwmLevel);
					pm_printf(_T("----TFT PwmLevel:%d\n",l_tTftCB.tLastPwmLevel));

				}
                
            	l_tTftCB.iTimer = 0;
            }
	#else
	            IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT, l_tTftCB.tCurrPwmLevel);
	            pm_printf(_T("TFT PwmLevel:l_tTftCB.tCurrPwmLevel = %d,l_tTftCB.tLastPwmLevel = %d\n",l_tTftCB.tCurrPwmLevel,l_tTftCB.tLastPwmLevel));
	#endif
        break;
        
        case PM_TFT_LED_OFF:
            IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT,0);
	      pm_printf(_T("PM_TFT_LED_OFF\n"));
            l_tTftCB.iTimer = 0;
            l_tTftCB.eState --;
        break;
        
        case PM_TFT_FB_OFF:
            if(l_tTftCB.iTimer > l_tTftCB.iEnTimming)
            {
				PM_UnitPowerSet(PM_UNIT_TFT , OFF);
				l_tTftCB.eState --;
				_SendMsgToHMI(MS_PM_TFT_INFO,OP_DEV_STATE_OFF,NULL);
				pm_printf(_T("PM_TFT_FB_OFF\n"));
            }
        break;
        
        case PM_TFT_DEV_OFF:
            #if 0
            if(l_tTftCB.iTimer  > (l_tPwrCB.pDlyTab->iTftOff>>1))
            {
                IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,OFF);
                IO_Set(IO_IDX_TFT_VGL,PIN_OUTPUT,OFF);
                l_tTftCB.iTimer = 0;
                l_tTftCB.eState --;
            }
            #endif
        break;
	case PM_TFT_BLOFF:
		break;
       
    }
}


/******************************************************************************
*Control TFT Power , only set the state. Then the state machine will auto to do.
*
*******************************************************************************/
void PM_TftPowerSet(bool bOnOff,uint16_t iEnTimming)
{
    uint8_t temp = g_tMcuDevState.uIOState.bits.LCD_Disp;
	
    l_tTftCB.iTimer = 0;
    
    if(bOnOff)
    {
        if((l_tTftCB.eState < PM_TFT_DEV_ON) || (l_tTftCB.eState == PM_TFT_BLOFF))
        {
            l_tTftCB.eState = PM_TFT_DEV_ON;
            l_tTftCB.iEnTimming = l_tPwrCB.pDlyTab->iTftOn + iEnTimming;
            l_tTftCB.tLastPwmLevel = 0;
            pm_printf(_T("--SetTftOn--\n"));
	     g_tMcuDevState.uIOState.bits.LCD_Disp = 1;
        }
    }
    else
    {
        if(l_tTftCB.eState > PM_TFT_LED_OFF)
        {
            l_tTftCB.eState = PM_TFT_LED_OFF;
            pm_printf(_T("--SetTftOFF--\n"));
	     g_tMcuDevState.uIOState.bits.LCD_Disp = 0;
        }
    }
    
    if(temp != g_tMcuDevState.uIOState.bits.LCD_Disp)
    {
		if( l_tPwrCB.eDispLayerState == PM_DISPLAYER_DISABLE)
		{
			g_tMcuDevState.uIOState.bits.LCD_Disp = 0;
		}
		_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
    }
}

void PM_TftInit(void)
{
	IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,OFF);
	IO_Set(IO_IDX_TFT_VGL,PIN_OUTPUT,OFF);
	IO_Set(IO_IDX_PANEL_LED2,PIN_OUTPUT,OFF);
	IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,OFF);
	
	IO_Set(IO_IDX_KEY_PWM,PIN_OUTPUT,OFF);

	API_MemClear((uint8_t*)&l_tTftCB,sizeof(tPM_TFT_CTRL_BLOCK));
	l_tTftCB.tCurrPwmLevel = 70;
	l_tTftCB.tLastPwmLevel = 70;
	l_tTftCB.iEnTimming = l_tPwrCB.pDlyTab->iTftOn;
	l_tTftCB.TftTempCloseFlag = 0;
}


void PM_DisplayClose(void)
{	
	IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,0);
	IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT,0);
	l_tTftCB.tLastPwmLevel = 0;
	pm_printf(_T("--PM_DisplayClose()--\n"));
}

/*******************************************************************************/
/***     PM MODE  Entry and check ***/

/*******************************************************************************/
/* Check the battery voltage.Notice:AD resout is different if SYS Power is ON or OFF
/*******************************************************************************/
void PM_BatteryCheck(void)
{
    eBATTERY_STATE eTagState = BAT_STATE_NUM;
    uint8_t  bak =  l_tPwrCB.uIOFlag.field.bBatErr;
    
    if(l_tPwrCB.iBatDlyTimer)
	l_tPwrCB.iBatDlyTimer --;
    
    if(l_tPwrCB.cBatVolIdx < PM_BATLEV_LOW_ON 
       || l_tPwrCB.cBatVolIdx > PM_BATLEV_HIGHT_ON)
    {
        eTagState = BAT_STATE_ERR;
    }
    else if(l_tPwrCB.cBatVolIdx == PM_BATLEV_NORMAL)
    {
        eTagState = BAT_STATE_IDLE;
    }
    
    switch(l_tPwrCB.eBatState)
    {
        case BAT_STATE_IDLE:
             if(BAT_STATE_ERR == eTagState)
             {
                 l_tPwrCB.eBatState++;
                 l_tPwrCB.uIOFlag.field.bBatErr = 1;
                 pm_printf(_T("Voltage Err,BatLev:%d\n",l_tPwrCB.cBatVolIdx));
             }
             if(l_tPwrCB.iBatDlyTimer == 0)
             {
                  l_tPwrCB.iBatDlyTimer = _set_timing_sec_base_pwr_task_tick(3);   
                  _SendMsgToHMI(MS_SYS_DEV_STATE,DEV_IDX_BATTERY,l_tPwrCB.cBatVolIdx);
                 // pm_printf(_T("Voltage:0x%x, Flag:%x\n",l_tPwrCB.cBatVolIdx,l_tPwrCB.uIOFlag.byte));
             }
        break;
        default:
             if(BAT_STATE_IDLE == eTagState)
             {
                 l_tPwrCB.eBatState = BAT_STATE_IDLE;
                 l_tPwrCB.uIOFlag.field.bBatErr = 0;
                 pm_printf(_T("Voltage Resume check start\n"));
             }
             
        break;
       
    }

	if(bak !=  l_tPwrCB.uIOFlag.field.bBatErr)
	{
		g_tMcuDevState.uIOState.bits.PowerProtectState  = l_tPwrCB.uIOFlag.field.bBatErr;
		_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
	}
}



/*******************************************************************************
*
* PM mode exchange
*
********************************************************************************/
#if D_DEBUG_POWER && D_PRINT_EN

const char* const lc_PmModeName[] = {
    "PM_MODE_ENTERY",
    "PM_MODE_CHECK",
    "PM_MODE_STANDBY",
    "PM_MODE_ON",
    
    "PM_MODE_ECONOMY",
    "PM_MODE_WAIT_SLEEP",
    "PM_MODE_SLEEP",
    "PM_MODE_OFF",
    "PM_MODE_BAT_ERR",
    "PM_MODE_LVI", 
    "PM_MODE_TEMP_ON",   
};
#endif

void PM_EnterMode(ePM_MODE eMode)
{
    uint8_t Op = (l_tPwrCB.eMode<<4)|l_tPwrCB.eStep;
    
    if(eMode == l_tPwrCB.eMode )return;
    if(Op < ((PM_MODE_CHECK<<4)|PM_STATE_STEP_3))return;

    Op = 0xFF;
    
    switch(l_tPwrCB.eMode)
    {
         case PM_MODE_LVI:
         case PM_MODE_SLEEP:
         case PM_MODE_OFF:
             v850_nmi_lvi_enable();
             PM_IoRestartScan();
         break;

         case PM_MODE_CHECK:
             PM_IoRestartScan();
         break;
	  default:
	  	break;
       
    }
    
    PM_ExitModeHook(l_tPwrCB.eMode);
    pm_printf(_T("<------PM exit Mode:"));
    pm_printf(_T(lc_PmModeName[l_tPwrCB.eMode]));
    pm_printf(_T("\n"));
    
    if(eMode < PM_MODE_NUM)
    {
        if((1<<eMode) & l_tPwrCB.pDlyTab->iDisplayerEN)
        {
            if(l_tPwrCB.eDispLayerState != PM_DISPLAYER_IDLE)
            {
                l_tPwrCB.eDispLayerState = PM_DISPLAYER_ENABLE;
            }
        }
        else
        {
            if(l_tPwrCB.eDispLayerState != PM_DISPLAYER_DISABLE)
            {
                l_tPwrCB.eDispLayerState = PM_DISPLAYER_WAIT_CLOSE;
            }
        }

        l_tPwrCB.eStep = PM_STATE_STEP_0;
        l_tPwrCB.iTimer = 0;
        
        switch(eMode)
        {
            case PM_MODE_LVI:
                v850_nmi_lvi_disable();
		   SysWorkStatusGrp.SysBtCallFlag = 0;
				g_tSysRomData.DevelopFlag = 0;
                /*MUTE*/
                //Rear System
                IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
                
                /*Clear LVI flag*/
                l_tPwrCB.uIOFlag.field.bLvi = 0;
                /*Set BAT AD check err,wait for it resum*/
                l_tPwrCB.uIOFlag.field.bBatErr = 1;
                l_tPwrCB.eBatState = BAT_STATE_ERR;
                
                l_tPwrCB.cBatVolIdx = 0;
		l_tTftCB.eState = PM_TFT_OFF;//lkm20150710_add
                IO_Set(IO_IDX_BATTERY_DET,PIN_INPUT,OFF);
                /*Mute tft*/
                IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT,OFF);
                PM_Lv5686Init();
                Op = OP_PM_STATE_LVI;
            break;
            
            case PM_MODE_SLEEP:
                Op = OP_PM_STATE_SLEEP;
		l_tTftCB.eState = PM_TFT_OFF;//lkm20150721_add		
            break;

            case PM_MODE_STANDBY:
                /*MUTE  Rear System*/
                //IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
                if(l_tPwrCB.eMode == PM_MODE_ON)
                {
                    Op = OP_PM_STATE_STANDBY;
                    l_tPwrCB.eStep = PM_STATE_STEP_2;
                }

                PM_UnitPowerSet(PM_UNIT_MAIN,ON);
//                PM_UnitPowerSet(PM_UNIT_FAN,ON);
                OS_TaskStart(TASK_ID_EEPROM);
                l_tPwrCB.uSetFlag.field.bPowerOn = 0;
            break;

            case PM_MODE_ON:
                l_tPwrCB.uSetFlag.field.bPowerOn = 1;
            case PM_MODE_ECONOMY:
                if(l_tPwrCB.eMode == PM_MODE_STANDBY
                   || l_tPwrCB.eMode == PM_MODE_WAIT_SLEEP)
                {
                    Op = OP_PM_STATE_ON;
                    l_tPwrCB.eStep = PM_STATE_STEP_2;
                }
 
                PM_UnitPowerSet(PM_UNIT_MAIN,ON);
//                PM_UnitPowerSet(PM_UNIT_FAN,ON);
                OS_TaskStart(TASK_ID_EEPROM);
                
            break;

            case PM_MODE_OFF:
                v850_nmi_lvi_disable();
                Op = OP_PM_STATE_OFF;
                l_tTftCB.eState = PM_TFT_OFF;//lkm20150715_add
                g_tSysRomData.DevelopFlag = 0;
            break;
            
            case PM_MODE_WAIT_SLEEP:
                Op = OP_PM_STATE_WAIT_SLEEP;
                PM_UnitPowerSet(PM_UNIT_FAN,OFF);
            break;

            case PM_MODE_BATTERY_ERROR:
                Op = OP_PM_STATE_BATERR;
                //Front System
                //Rear System
                IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
                PM_UnitPowerSet(PM_UNIT_FAN,OFF);
            break;
            default:
		break;
        }
        
        PM_EnterModeHook(eMode);
        if(Op < 0xff)
		_SendMsgToHMI(MS_PM_STATE,Op,NULL);
        l_tPwrCB.eMode = eMode;
        
        
        pm_printf(_T("----->PM go to Mode:"));
        pm_printf(_T(lc_PmModeName[eMode]));
        pm_printf(_T("||||||\n"));
    }
}


void PM_ExtReqHandle(void)
{
    ePM_MODE eTargMode = PM_MODE_NUM;
    switch(l_tPwrCB.eExtReqPmState)
    {
        case OP_PM_STATE_ON:
        {
            eTargMode = (PM_MODE_ON);
        }
        break;
        case OP_PM_STATE_STANDBY:
        {
            eTargMode = (PM_MODE_STANDBY);
        }
        break;
        case OP_PM_STATE_WAIT_SLEEP:
        {
            eTargMode = (PM_MODE_WAIT_SLEEP);
        }
        break;
        case OP_PM_STATE_SLEEP:
        {
            eTargMode = (PM_MODE_SLEEP);
        }
        break;
        case OP_PM_STATE_OFF:
            eTargMode = (PM_MODE_OFF);
        break;
        
    }

    if(eTargMode < PM_MODE_NUM
       && eTargMode != l_tPwrCB.eMode)
    {
        PM_EnterMode(eTargMode);
    }
    
}

/*******************************************************************************
*Check system temperature
*
********************************************************************************/



/*******************************************************************************/
/*
/* check ACC line and battery voltage,get the low power interrupt
/*
/*******************************************************************************/
void PM_IOCheck(void)
{
    uint8_t flag; 
    uint8_t bit;
    
    IO_Scan(IO_IDX_ACC_WAKE,PIN_INPUT);
    IO_Scan(IO_IDX_ILL_WAKE,PIN_INPUT);//snake20160922
    if(!HMIStatusFlag.g_tUpdataBlindParameter)
    	IO_Scan(IO_IDX_REVERSE_DET,PIN_INPUT);
    IO_Scan(IO_IDX_DISC_IN_DET,PIN_INPUT);
    IO_Scan(IO_IDX_ILL_DET,PIN_INPUT);
    IO_Scan(IO_IDX_NAVI_AUDIO,PIN_INPUT);
    IO_Scan(IO_IDX_BATTERY_DET,PIN_INPUT);
    IO_Scan(IO_IDX_TEMP_DET,PIN_INPUT);
}


void isrPM_LviOccur(void)
{
    l_tPwrCB.uIOFlag.field.bLvi = !(IO_GET_LVI_DET && 1);

}


void PM_EntryHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{

    switch(l_tPwrCB.eStep)
    {
        case PM_STATE_STEP_0:
            if(l_tPwrCB.iTimer  > PWR_TIME_START)
            {
                //IO_Set(IO_IDX_POWER_LED,PIN_OUTPUT,INVALID);
                l_tPwrCB.eStep = PM_STATE_STEP_1;    
                l_tPwrCB.iTimer = 0;
                pm_printf(_T("pwr_cold_start\n"));
                ////////////////////////////////////////////////////////////////////
                OS_TaskStart(TASK_ID_HMI);
                PM_IoInit();
                PM_Lv5686Init(); /*Sys_5v is low,so the chip is no output,init the ctrl io*/
                _SendMsgToHMI(MS_SYS_DEV_ON_MCU_INFO,MCU_DEV_IDX_IO,OP_DEV_STATE_NORMAL);
            }
        break;

        case PM_STATE_STEP_1:
	     if(l_tPwrCB.iTimer  > PWR_TIME_START)
	     	{
	            l_tPwrCB.uIOFlag.field.bLvi = 0;
	            /*Set eeprom power on*/
	            PM_UnitPowerSet(PM_UNIT_MAIN,ON);
		      //IO_Set(IO_IDX_MCU2DR_PWR,PIN_OUTPUT,ON);	
			  //IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,ON);
	            v850_nmi_lvi_enable();
	            
	            l_tPwrCB.eMode = PM_MODE_CHECK;
	            l_tPwrCB.iTimer = 0;
	            l_tPwrCB.eStep = PM_STATE_STEP_0;
	     	}
        break;
        default:
            l_tPwrCB.eStep = PM_STATE_STEP_0;
	  break;
    }
}

void PM_CheckHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{
	switch(l_tPwrCB.eStep)
	{
		case PM_STATE_STEP_0:
		/*Wait for IO/Voltage stable*/
		if(l_tPwrCB.iTimer  >  PWR_TIME_CHK)		// 50ms
		{
			l_tPwrCB.iTimer = 0; 
			l_tPwrCB.eStep ++;  
			PM_UnitPowerSet(PM_UNIT_APU, ON);
			IO_Set(IO_IDX_APU_RESET, PIN_OUTPUT,VALID);//复位
		}
		break;

		case PM_STATE_STEP_1:
		/*Start read eeprom*/
		pm_printf(_T("EEPROM Check and load romdata Start! %lx\n",OS_GetOsTick()));
		l_tPwrCB.eStep ++;    
		l_tPwrCB.iTimer = 0;
		l_tPwrCB.eEEPState = OP_DEV_STATE_OFF;
		OS_TaskStop(TASK_ID_EEPROM);
		OS_TaskStart(TASK_ID_EEPROM);
		break;

		case PM_STATE_STEP_2:
		/*2 sec delay time out or read succesfuly*/
		if(l_tPwrCB.iTimer > _set_timing_sec_base_pwr_task_tick(2) || l_tPwrCB.eEEPState == OP_DEV_STATE_NORMAL)
		{
			pm_printf(_T("PM_Eep CheckOK! %lx\n",OS_GetOsTick()));
			l_tPwrCB.eStep ++;    
			l_tPwrCB.iTimer = 0;
			OS_TaskStop(TASK_ID_EEPROM);
		}
		break;

		case PM_STATE_STEP_3:
		if(l_tPwrCB.uIOFlag.field.bBatErr || 0 == l_tPwrCB.uIOFlag.field.bSysWakeOn)
		{
			PM_EnterMode(PM_MODE_SLEEP);
			PM_UnitPowerSet(PM_UNIT_MAIN,OFF);
			PM_UnitPowerSet(PM_UNIT_APU, OFF);
		}
		else
		{
			if(OP_PM_STATE_INVALID == l_tPwrCB.eExtReqPmState)
			{
				/*Extern control is invalid*/
				if(l_tPwrCB.uSetFlag.field.bPowerOn)
				PM_EnterMode(PM_MODE_ON);
				else 
				PM_EnterMode(PM_MODE_STANDBY);
			}
			else
			{
				PM_ExtReqHandle();
			}
		}
		break;

		default:
		l_tPwrCB.eStep = PM_STATE_STEP_0;
		break;
	}
}


/*******************************************************************************/
/***     PM MODE  Economy ***/

void PM_EcnomyHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{
    if(l_tPwrCB.uIOFlag.field.bBatErr)
    {
        PM_EnterMode(PM_MODE_BATTERY_ERROR);
    }
    else 
    {        
        switch(l_tPwrCB.eStep)
        {
            case PM_STATE_STEP_0:
                if(l_tPwrCB.iTimer >/* l_tPwrCB.pDlyTab->iWaitSysPowerStable*/PWR_TIME_WAIT_STABLE)
                {
                    l_tPwrCB.iTimer = 0;
                    l_tPwrCB.eStep ++;
                }
            break;
            case PM_STATE_STEP_1:
                _SendMsgToHMI(MS_PM_STATE,OP_PM_STATE_ON,NULL);
                l_tPwrCB.eStep ++;
            break;
            default:
                ;
        }
        
        if(OP_PM_STATE_INVALID == l_tPwrCB.eExtReqPmState)
        { 
            uint32_t lTimer = g_tSysSettingRomData.iEconomyTime;
            if(g_tSysRomData.uGenBlock.tBlock.tFlag5.SleepTimeSet<3)
            {
                lTimer = _set_timing_sec_base_pwr_task_tick(60*2);
            }
            
            if(l_tPwrCB.uIOFlag.field.bSysWakeOn && 0 == l_tPwrCB.uIOFlag.field.bBatErr)
            {
                PM_EnterMode(PM_MODE_ON);
            }
            /*Extern control is invalid*/
            else if(l_tPwrCB.iTimer  > lTimer) //小时模式
            {
                PM_EnterMode(PM_MODE_SLEEP);
            }
            
        }
        else
        {
            PM_ExtReqHandle();
        }

        
    }
    
}
/*******************************************************************************/
/***     PM MODE  ON and Standby ***/
void PM_StdbyHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{
    
    if(l_tPwrCB.uIOFlag.field.bBatErr)
    {
        PM_EnterMode(PM_MODE_BATTERY_ERROR);
    }
    else 
    {
        switch(l_tPwrCB.eStep)
        {
            case PM_STATE_STEP_0:
                if(l_tPwrCB.iTimer >/* l_tPwrCB.pDlyTab->iWaitSysPowerStable*/PWR_TIME_WAIT_STABLE)
                {
                    l_tPwrCB.iTimer = 0;
                    l_tPwrCB.eStep ++;
                }
            break;
            case PM_STATE_STEP_1:
                _SendMsgToHMI(MS_PM_STATE,OP_PM_STATE_STANDBY,NULL);
                l_tPwrCB.eStep ++;
            break;
            default:
                break;
        }
        
        if(OP_PM_STATE_INVALID == l_tPwrCB.eExtReqPmState)
        {
            /*Extern control is invalid*/
            if(!l_tPwrCB.uIOFlag.field.bSysWakeOn)  
            {
                PM_EnterMode(PM_MODE_WAIT_SLEEP);
            }
        }
        else
        {
            PM_ExtReqHandle();
        }
    }

    
}


void PM_OnHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{
    if(l_tPwrCB.uIOFlag.field.bBatErr)
    {
        PM_EnterMode(PM_MODE_BATTERY_ERROR);
    }
    else 
    {        
        switch(l_tPwrCB.eStep)
        {
            case PM_STATE_STEP_0:
                if(l_tPwrCB.iTimer > /*l_tPwrCB.pDlyTab->iWaitSysPowerStable*/PWR_TIME_WAIT_STABLE)
                {
                    l_tPwrCB.iTimer = 0;
                    l_tPwrCB.eStep ++;
                }
            break;
            case PM_STATE_STEP_1:
                _SendMsgToHMI(MS_PM_STATE,OP_PM_STATE_ON,NULL);
                l_tPwrCB.eStep ++;
		 //IO_Set(IO_IDX_MCU2DR_PWR,PIN_OUTPUT,ON);	
		 //IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,ON);
            break;
            default:
                break;
        }
        
        if(OP_PM_STATE_INVALID == l_tPwrCB.eExtReqPmState)
        {
            /*Extern control is invalid*/
            if(!l_tPwrCB.uIOFlag.field.bSysWakeOn) 
            {
                PM_EnterMode(PM_MODE_WAIT_SLEEP);
            }
            
        }
        else
        {
            PM_ExtReqHandle();
        }
    }

}

/*******************************************************************************/
/***     PM MODE  WaitSleep and Sleep ***/

void PM_WaitSleepHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{
    if(l_tPwrCB.uIOFlag.field.bBatErr) /*Sleep quickly*/
    {
 #if 0		//对标东软，不主动进入SLEEP模式。2016-06-02
        if(l_tPwrCB.iTimer > _set_timing_sec_base_pwr_task_tick(6))
        {
            PM_EnterMode(PM_MODE_SLEEP);
        }
#endif
    }
    else 
    {    
        uint32_t iTimer = g_tSysSettingRomData.iWaitSleepTime;
        if(g_tSysRomData.uGenBlock.tBlock.tFlag5.SleepTimeSet<3)
        {
            iTimer = _set_timing_sec_base_pwr_task_tick(6);
        }
		
        if(l_tPwrCB.eExtReqPmState == OP_PM_STATE_INVALID) 
        {
            if( l_tPwrCB.uIOFlag.field.bSysWakeOn 
                && 0 == l_tPwrCB.uSetFlag.field.bForceSleep )
            {
                if(l_tPwrCB.uSetFlag.field.bPowerOn)
                {
                     PM_EnterMode(PM_MODE_ON);
                }
                else
                {
                    PM_EnterMode(PM_MODE_STANDBY);
                }
            }

            if(l_tPwrCB.iTimer  > iTimer) /**/
            {
                PM_EnterMode(PM_MODE_SLEEP);
            }
        }
        else
        {
            PM_ExtReqHandle();
        }
        
    }
}


void PM_SleepHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{
    
    switch(l_tPwrCB.eStep)
    {
        case PM_STATE_STEP_0:
            if(l_tPwrCB.iTimer > _set_timing_xms_base_pwr_task_tick(200))
            {
                l_tPwrCB.iTimer = 0;
                l_tPwrCB.eStep ++;
            }
        break;

	 default:
		break;
    }

    if(!l_tPwrCB.uIOFlag.field.bBatErr)
    {        
    
        if(OP_PM_STATE_INVALID == l_tPwrCB.eExtReqPmState
                   || OP_PM_STATE_N == l_tPwrCB.eExtReqPmState)
        {
             l_tPwrCB.eExtReqPmState = OP_PM_STATE_INVALID;
             if(l_tPwrCB.uIOFlag.field.bSysWakeOn 
                && 0 == l_tPwrCB.uSetFlag.field.bForceSleep)
             {
                 if(l_tPwrCB.uSetFlag.field.bPowerOn)
                 {
                      PM_EnterMode(PM_MODE_ON);
                 }
                 else
                 {
                      PM_EnterMode(PM_MODE_STANDBY);
                 }
             }
        }
        else 
        {
             PM_ExtReqHandle();
        }
            
        
    }
    
}

typedef struct{
	uint8_t lastState	:1;
	uint8_t StableState	:1;
	uint8_t checkCnt;
}IOScanStruct;
IOScanStruct    Illumi;
uint8_t IllumiCheckResult(void)
{
	if(P0&0X40)		//ILL
	{
		if(Illumi.lastState == 0)
		{
			Illumi.checkCnt = 1;
		}
		else
		{
			Illumi.checkCnt++;
			if(Illumi.checkCnt>=5)
			{
				Illumi.checkCnt = 0;
				Illumi.StableState = 0;
			}
		}
		Illumi.lastState = 1; 
	}
	else
	{
		if(Illumi.lastState == 1)
		{
			Illumi.checkCnt = 1;
		}
		else
		{
			Illumi.checkCnt++;
			if(Illumi.checkCnt>=5)
			{
				Illumi.checkCnt = 0;
				Illumi.StableState = 1;
			}
		}
		Illumi.lastState = 0;
	}
	return Illumi.StableState;
}

/*******************************************************************************/
/***     PM MODE  OFF and LVI ***/
void PM_OffHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{
    eOP_PM_AWAKE_EVENT eEvt = OP_PM_AWAKE_NONE;
            
    switch(l_tPwrCB.eStep)
    {
        case PM_STATE_STEP_0:
            if((l_tPwrCB.eAPUState == OP_DEV_STATE_OFF) &&
		  (l_tPwrCB.iTimer > _set_timing_xms_base_pwr_task_tick(200)))
            {
                uint8_t re = 0;
                tTASK_CTRL_BLOCK* p_tTask = OS_TaskListGetHead();
                while(p_tTask)
                {
                    if(TASK_ID_STOP_NOMAL_MASK == (p_tTask->Id & TASK_ID_STOP_NOMAL_MASK ))
                    {
                        OS_TaskStopDir(p_tTask);
                        pm_printf(_T("Task ID:%d stop---",p_tTask->Id));
                        if(OS_TaskIsActiveDir(p_tTask))
                        {
                            re ++;
                            pm_printf(_T("faild!",p_tTask->Id));
                        }
                        pm_printf(_T("\n"));
                    }
                    p_tTask = OS_TaskListGetNext(p_tTask);
                   
                }
                
                if(0 == re)
                {
                    l_tPwrCB.iTimer = 0;
                    l_tPwrCB.eStep ++;
                    PM_UnitPowerSet(PM_UNIT_ALL,OFF);
                }
            }
      	break;
		case PM_STATE_STEP_1:
            if(!l_tPwrCB.uIOFlag.field.bSysWakeOn)
			{
				uint8_t i = 0,j = 0,re=INVALID;
				pm_printf(_T("MCU Enter Sleep State---\n"));
				PM_SleepInit();

				PM_OffSetIO();

				cpu_lowpower();

				Illumi.checkCnt = 0;
				Illumi.lastState = 0;
				Illumi.StableState = 0;

				g_flag_isr.byte1 = 0x00;
				iEvt = OP_PM_AWAKE_ACC;
				while(1)
				{	
					CLEAR_WATCHDOG();
					//g_flag_isr.bit1.flag_acc = IO_Get(IO_IDX_ACC_WAKE, PIN_INPUT, FALSE);
					g_flag_isr.bit1.flag_acc = IO_Get(IO_IDX_LOCAL_ACC, PIN_INPUT, FALSE);
					if(g_flag_isr.bit1.flag_acc)
					{
						g_flag_isr.bit1.flag_ill = 0;
						g_flag_isr.bit1.flag_acc = 0;
						OSTS = 0x06;			// set OSC valid time.
						Disable_INTP0_Trigger();
						Disable_INTP3_Trigger();
						cpu_awake();
						cpu_init();
						PM_Lv5686Init();
						break;
					}

				#ifdef D_ILL_WAKEUP  //snake20160922 for R103-H15T   cheack ill int add
					//g_flag_isr.bit1.flag_ill = IO_Get(IO_IDX_ILL_DET, PIN_INPUT, FALSE);
					if(g_flag_isr.bit1.flag_ill)
					{
						g_flag_isr.bit1.flag_ill = 0;
						g_flag_isr.bit1.flag_acc = 0;
						OSTS = 0x06;			// set OSC valid time.
						Disable_INTP0_Trigger();
						Disable_INTP3_Trigger();
						cpu_awake();
						cpu_init();
						PM_Lv5686Init();
						break;
					}
				#else
					if(IllumiCheckResult())		//ILL ON
					{
						if(g_flag_isr.bit1.flag_ill == 0)
						{
							PM_Lv5686Init();	
							IO_Set(IO_IDX_PM_SNT_FREQ,PIN_OUTPUT,0);
							IO_Set(IO_IDX_SYS_5V,PIN_OUTPUT,1);
//							PM_UnitPowerSet(PM_UNIT_FAN, ON);	
							PMC5 &= (~0X01);
							PM5 &= (~0X01);
							P5 |= 0X01;			// Open Key led.
							g_flag_isr.bit1.flag_ill = 1;
							//	SleepIO_Output(0, 1);
						}
					}
					else if(g_flag_isr.bit1.flag_ill == 1)
					{
						g_flag_isr.bit1.flag_ill = 0;
						P5 &= (~0X01);			// Open Key led.
						PM_UnitPowerSet(PM_UNIT_FAN, OFF);		//close FAN POWER
						IO_Set(IO_IDX_SYS_5V,PIN_OUTPUT,0);
						//SleepIO_Output(0, 0);
						PM_SleepInit();
						PM_OffSetIO();
						cpu_lowpower();
					}
			#endif
				}
				_SendMsgToHMI(MS_PM_AWAKE,OP_PM_STATE_OFF,eEvt);
				IO_ResetState(IO_IDX_ACC_WAKE,INVALID);
				l_tMediaCB.uDevFlag.field.bUpData = 0;
				pm_printf(_T("MCU Exit Sleep State---\n"));
			}
            IO_ResetState(IO_IDX_ACC_WAKE,INVALID);
            l_tPwrCB.eStep = PM_STATE_STEP_2;
            l_tPwrCB.iTimer = 0;
        	break;
        
        case PM_STATE_STEP_2:
            if(l_tPwrCB.iTimer  > _set_timing_xms_base_pwr_task_tick(1000L))
            {
                l_tPwrCB.eStep = PM_STATE_STEP_1;
            }
            
        break;
        default:
            l_tPwrCB.eStep = PM_STATE_STEP_0;
	 break;
    }
    
    if(!l_tPwrCB.uIOFlag.field.bBatErr)
    {
        if(OP_PM_STATE_INVALID == l_tPwrCB.eExtReqPmState
                   || OP_PM_STATE_N == l_tPwrCB.eExtReqPmState)
       { 
            l_tPwrCB.eExtReqPmState = OP_PM_STATE_INVALID;
            if(l_tPwrCB.uIOFlag.field.bSysWakeOn 
                && 0 == l_tPwrCB.uSetFlag.field.bForceSleep )
            {
                if(l_tPwrCB.uSetFlag.field.bPowerOn)
                {
                    PM_EnterMode(PM_MODE_ON);
                }
                else
                {
                    PM_EnterMode(PM_MODE_STANDBY);
                }
            }
        }
        else
        {
		if((l_tMediaCB.eState  == MEDIA_STATE_SLEEP) &&
			((l_tMediaCB.eSubState == MEDIA_STATE_STEP_2)||
			((l_tMediaCB.eSubState == MEDIA_STATE_STEP_3))))
        	   	{
        	   	
        	   	}
		else
		{
			PM_ExtReqHandle();
		}
            
        }
    }
}

extern eOP_PM_AWAKE_EVENT PM_GetAwakeEvent(eOP_PM_AWAKE_EVENT eIdx);


void PM_LviHandle(EVENT iEvt)
{
    switch(l_tPwrCB.eStep)
    {
        case PM_STATE_STEP_0:
        {
            /*Stop other task*/
            uint8_t re = 0;
            tTASK_CTRL_BLOCK* p_tTask = OS_TaskListGetHead();

            
            while(p_tTask)
            {
                if(TASK_ID_STOP_LVI_MASK == (p_tTask->Id & TASK_ID_STOP_LVI_MASK ))
                {
                    OS_TaskStopDir(p_tTask);
                    pm_printf(_T("Task ID:%d stop---",p_tTask->Id));
                    if(OS_TaskIsActiveDir(p_tTask))
                    {
                        re ++;
                        pm_printf(_T(" faild!",p_tTask->Id));
                    }
                    pm_printf(_T("\n"));
                }
                p_tTask = OS_TaskListGetNext(p_tTask);
            }
            
            PM_SleepInit();
            (void)PM_GetAwakeEvent(OP_PM_AWAKE_BAT_ERR);

            PM_LviSetIO();
            
            cpu_lowpower();
            l_tPwrCB.iTimer = 0;
            l_tPwrCB.iBatDlyTimer = 0;
            l_tPwrCB.eExtReqPmState = OP_PM_STATE_N;
            
            while(1)
            {
                eOP_PM_AWAKE_EVENT eEvt = OP_PM_AWAKE_NONE;
                uint32_t lTimer = 0 ;
                CLEAR_WATCHDOG();
                
                cpu_awake();
                
                lTimer = OS_GetWatchSecond();
                if(l_tPwrCB.cOSSecond != (uint8_t)lTimer)
                {
                    l_tPwrCB.iTimer ++;
                    l_tPwrCB.cOSSecond = (uint8_t)lTimer;
		      if(l_tPwrCB.iTimer>=5)
		      	{
				l_tMediaCB.uDevFlag.field.bUpData = 0;
			}
                    pm_printf(_T("RTC Sec in LVI:   %d  \n",(uint8_t)l_tPwrCB.iTimer));
                }
                
                if(l_tPwrCB.iTimer > _set_timing_sec_base_rtc(10))
                {
                    cpu_init();
                    PM_EnterMode(PM_MODE_OFF);
                    return;
                }
                else
                {
                    eEvt = PM_GetAwakeEvent(OP_PM_AWAKE_BAT_ERR);
                    cpu_sleep();
                    if(eEvt == OP_PM_AWAKE_NONE)
                    {
                        cpu_init();
                        break;
                    }
                }
               
            }
            
            _SendMsgToHMI(MS_PM_AWAKE,OP_PM_STATE_LVI,OP_PM_AWAKE_BAT_ERR);
            IO_ResetState(IO_IDX_BATTERY_DET,0);
            IO_ResetState(IO_IDX_ACC_WAKE,INVALID);
            
            l_tPwrCB.eStep ++;
            l_tPwrCB.iTimer = 0;
            v850_nmi_lvi_enable();
        }    
        break;
        case PM_STATE_STEP_1:
        {
            /*Wait for cpu sleep in MCU_LOW_POWER_MODE*/
         //   if(/* INVALID == IO_Get(IO_IDX_APU_STATUS,PIN_INPUT,TRUE)
           //     ||*/ l_tPwrCB.iTimer  > _set_timing_sec_base_pwr_task_tick(6))
            {
                l_tPwrCB.eStep ++;
                l_tPwrCB.iTimer = 0;
            }
        }
        break;    
        case PM_STATE_STEP_2:
            if(l_tPwrCB.uIOFlag.field.bBatErr == 0)
            {
                if(OP_PM_STATE_INVALID == l_tPwrCB.eExtReqPmState
                   || OP_PM_STATE_N == l_tPwrCB.eExtReqPmState)
                {
                    PM_EnterMode(PM_MODE_SLEEP);
                    l_tPwrCB.eExtReqPmState = OP_PM_STATE_INVALID;
                }
                else
                {
                    PM_ExtReqHandle();
                }
		
            }
        break;
        default:;
    }
}


/*******************************************************************************/
/***     PM MODE  Temp ON ***/
void PM_TempHandle(EVENT iEvt,tMSG_BUF* p_tMsg)
{

    switch(l_tPwrCB.eAwakeEvt)
    {
        case OP_PM_AWAKE_EJCKEY:
            if(p_tMsg->Id == MS_SYS_DISC_INFO)
            {
                 if(p_tMsg->uData.a_cData[0] == 0)
                 {
                     l_tPwrCB.iTimer = _set_timing_xms_base_pwr_task_tick(6);
                 }
            }

            if(l_tPwrCB.iTimer  > _set_timing_sec_base_pwr_task_tick(10))
            {
                PM_EnterMode(PM_MODE_OFF);
            }
        break;

        case OP_PM_AWAKE_DISCIN:
        break;
    }
}
/*******************************************************************************/
void PM_DisplayProc(void)
{
    switch(l_tPwrCB.eDispLayerState)
    {
        case PM_DISPLAYER_DISABLE:
        break;

        case PM_DISPLAYER_WAIT_CLOSE:
            PM_DisplayClose();
            l_tPwrCB.eDispLayerState = PM_DISPLAYER_DISABLE;
        break;
        case PM_DISPLAYER_ENABLE:
            PM_DisplayClose();
            l_tPwrCB.eDispLayerState = PM_DISPLAYER_IDLE;
        break;
        case PM_DISPLAYER_IDLE:
            PM_TftPowerManage();
        break;
    }
}


/*******************************************************************************/
typedef void (*fPmModeFunction)(EVENT iEvt,tMSG_BUF* p_tMsg);

const fPmModeFunction l_pfPMModeProc[] = {
    PM_EntryHandle,     //PM_MODE_ENTERY,
    PM_CheckHandle,     //PM_MODE_CHECK,
    PM_StdbyHandle,     //PM_MODE_STANDBY,
    PM_OnHandle,        //PM_MODE_ON,
    
    PM_EcnomyHandle,    //PM_MODE_ECONOMY,
    PM_WaitSleepHandle, //PM_MODE_WAIT_SLEEP,
    PM_SleepHandle,     //PM_MODE_SLEEP,
    PM_OffHandle,       //PM_MODE_OFF,
    
    PM_WaitSleepHandle,  //PM_MODE_BATTERY_ERROR
    PM_LviHandle,       //PM_MODE_LVI,
    PM_TempHandle,      //PM_MODE_TEMP_ON,
    NULL,               //PM_MODE_NUM
    
};        /*PM main state*/

void PM_CloseBackLight_temp(uint8_t param)
{
	if(param == TFT_BL_ON)
	{
		//if(l_tTftCB.TftTempCloseFlag)
		if(!g_tMcuDevState.uIOState.bits.LCD_Disp)//LCD close state
		{
			l_tTftCB.TftTempCloseFlag = 0;
			PM_TftPowerSet(1,0);
		}
	}
	else
	//if(g_tMcuDevState.uIOState.bits.LCD_Disp)
	{
		PM_DisplayClose();
		l_tTftCB.eState = PM_TFT_BLOFF;
		l_tTftCB.TftTempCloseFlag = 1;
		g_tMcuDevState.uIOState.bits.LCD_Disp = 0;
	 	_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);//Updata to APU
	}
	pm_printf(_T("PM_CloseBackLight_temp:%d\n",param));
}
void PM_MsgHandle(tMSG_BUF* p_tMsg)
{
    uint16_t cMsgID = p_tMsg->Id;
    uint16_t cMsgOp = p_tMsg->iSid;
    
    switch(cMsgID)
    {
         
        case MS_PM_SET_STATE:
            switch(cMsgOp)
            {
                case OP_DEV_STATE_RESET:
                    PM_EnterMode(PM_MODE_ENTERY);
                break;
            }
        break;
        
        case MS_SYS_APU_INFO:
            {
                l_tPwrCB.eAPUState = (eOP_DEV_STATE_TYPE)((uint8_t)cMsgOp);
            }
        break;


        case MS_PM_TFT_BL_CMD:
		pm_printf(_T("MS_PM_TFT_BL_CMD:%d\n",(uint8_t)cMsgOp));
		if(l_tMediaCB.eState == MEDIA_STATE_RUNNING)
		{
			if(cMsgOp == TFT_BL_ON)
			{
				PM_TftPowerSet(1,0);
			}
			else
			{
				PM_DisplayClose();
				l_tTftCB.eState = PM_TFT_BLOFF;
				if(g_tMcuDevState.uIOState.bits.LCD_Disp)
				{
					g_tMcuDevState.uIOState.bits.LCD_Disp = 0;
					_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
				}
			}
		}
        break;

	case MS_PM_TFT_8836:
		if( l_tMediaCB.eState == MEDIA_STATE_RUNNING)
		{
		/*	if(cMsgOp == 0)
			{
				IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT,0);
			}
			else
			{
				IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT,l_tTftCB.tLastPwmLevel);
			}
			*/
				
		}
		break;
        case MS_SYS_BUS_INFO:
            l_tPwrCB.eExtReqPmState = (eOP_PM_STATE)((uint8_t)cMsgOp);
	     pm_printf(_T("PM Rcv CAN Req:%d\n",l_tPwrCB.eExtReqPmState));
        break;
       
        case MS_SYS_BUS_IO_INFO:
        break;

        case MS_PM_TFT_INFO:
            if(OP_DEV_STATE_UPDATA == cMsgOp)
            {
               l_tTftCB.tCurrPwmLevel = PM_GetTftBLValue();
            }
        break;  
        case MS_SYS_DEV_STATE:
            if(DEV_IDX_EEPROM == cMsgOp)
            {
                l_tPwrCB.eEEPState = (eOP_DEV_STATE_TYPE)((uint8_t)(uint32_t)(p_tMsg->uData.p_cData));
            }
        break;

        case MS_SYS_IO_INFO:
        {
            uint8_t cIoValue = ((uint8_t)(uint32_t)(p_tMsg->uData.p_cData));
            switch(cMsgOp)
            {
                case IO_IDX_ACC_WAKE:
                    l_tPwrCB.uIOFlag.field.bSysWakeOn = cIoValue &&1;
		      pm_printf(_T("PM Rcv ACC_wake: %d\n",cIoValue));
                break;
                case IO_IDX_BATTERY_DET:
                    l_tPwrCB.cBatVolIdx = cIoValue;
                    pm_printf(_T("PM Rcv Battery lev: %d\n",cIoValue));
                break;

                case IO_IDX_TEMP_DET:
                    pm_printf(_T("Temp lev: %d\n",cIoValue));
                    IO_Set(IO_IDX_FAN_CTRL,PIN_OUTPUT,cIoValue);
                break;
            }
        }
        break;
        
    }
}

void TemperatureChkTest(void)
{
	uint8_t Value = 0;
	Value = 	IO_Get(IO_IDX_TEMP_DET,PIN_INPUT, 0);
	pm_printf(_T("-------Temperature AD :%d\n",Value));
}

//
//任务主程序
//
void PM_Task(EVENT iEvt,eTASK_STATE eStep)
{
    //此任务不会挂起。总在运行态
    if(l_tPwrCB.eMode > PM_MODE_ENTERY)
    {
        if(l_tPwrCB.uIOFlag.field.bLvi)
        {
               PM_EnterMode(PM_MODE_LVI);
               OS_PostEventDir(&g_tPMTaskCB,EVT_TASK_TICK_READY);
        }
        if( iEvt & EVT_TASK_TICK_READY )
        {
            PM_IOCheck();
	     PM_BatteryCheck();//低电检测
            PM_DisplayProc();
			PanelLed_PWMDeal();//led
        }
    }

    if(iEvt & EVT_RTC_SECOND)
    {
    	 //IO_Set(IO_IDX_MCU2DR_PWR,PIN_OUTPUT,ON);	
    	 //IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,ON);
        //ERROR(_T("Bat vol is : %d\n",IO_Get(IO_IDX_BATTERY_DET,1,0)));
        g_tSysStateDbgInfo.PMState = (l_tPwrCB.eMode<<4)|(l_tPwrCB.eStep);
    }
    
     if(iEvt & EVT_MSG_READY)
    {
    	 tMSG_BUF tMsgBuf;
        if(QUE_ERR_NONE == PM_GetMsg(&tMsgBuf))
        {
         //   pm_printf(_T("--PM RxMsg:%ix - %ix - %x \n",tMsgBuf.Id,tMsgBuf.iSid,tMsgBuf.uData.a_cData[0]));
            PM_MsgHandle(&tMsgBuf);
            PM_MsgHandHook(&tMsgBuf);
        }
    }
    if( iEvt & EVT_TASK_TICK_READY )
    {   
        fPmModeFunction pFuc = l_pfPMModeProc[l_tPwrCB.eMode];
        if(pFuc)
        {
            tMSG_BUF tMsgBuf;
            tMsgBuf.Id = 0;
           
            l_tPwrCB.iTimer ++;
            pFuc(iEvt,&tMsgBuf);
        }
    }

}

uint8_t PM_Init(void)
{
    API_MemClear((uint8_t*)(&l_tPwrCB),sizeof(tPM_CTRL_BLOCK));
    l_tPwrCB.pDlyTab = &lc_tPMDlyTimingTab;
    l_tPwrCB.uSetFlag.field.bPowerOn = 1;
    
    l_tPwrCB.cBatVolIdx = PM_BATLEV_NORMAL;
    IO_Init();
    PM_TftInit();
    return TRUE;
}


static const tTASK_BLOCK l_tPMTaskAttr = 
{
    "POWER",
    _PM_TASK_TICK_,
    _PM_CORE_TICK_,
    PM_Task,
    PM_Init,
    NULL,
};

tMSG_BUF l_tPwrMsgBuf[D_PWR_MSG_QUE_DEEP];
tRING_QUE l_tPwrMsgQue;

bool PM_TaskCreate(void)
{
    uint8_t re = FALSE;
    SYS_Init();

	g_flag_isr.byte1 = 0x00;
	
    re = (uint8_t)OS_TaskCreate(TASK_ID_PWR,&g_tPMTaskCB,&l_tPMTaskAttr,&l_tPwrMsgQue,l_tPwrMsgBuf,D_PWR_MSG_QUE_DEEP);
    re &= OS_TaskStart(TASK_ID_PWR);

    return re;
}



