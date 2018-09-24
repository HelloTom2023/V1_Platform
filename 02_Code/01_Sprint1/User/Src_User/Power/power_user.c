#define _PM_USER_C_
#include "..\config\inc.h"


#define Threshold_NormalToLow		101//08V
#define Threshold_LowToNormal		114//09V
#define Threshold_NormalToHigh		226//18V
#define Threshold_HighToNormal		221//17.6V

#ifndef D_ILL_ADC_CHECK 
const uint8_t Duty_PWM[] = {15,18,21,25,28,32,40,45,50,55,60};//snake20160922 <-黑夜模式 ----- 白天模式->
#else
const uint8_t Duty_PWM[] = {
							0*1,	/*0%*/
							6*1,	/*18%*/
							11*1,	/*20%*/
							16*1,	/*21%*/
							21*1,	/*23%*/
							16*1,	/*25%*//*5*/
							31*1,	/*27%*/
							36*1,	/*30%*/
							41*1,	/*32%*/
							46*1,	/*35%*/
							51*1,	/*38%*//*10*/
							56*1,	/*41%*/
							61*1,	/*45%*/
							66*1,	/*49%*/
							72*1,	/*53%*/
							76*1,	/*58%*//*15*/
							81*1,	/*63%*/
							86*1,	/*68%*/
							91*1,	/*74%*/
							96*1,	/*80%*/
							105*1,	/*87%*//*20*/
							//95*1,	/*95%*/
							//100*1	/*100%*/
};
#endif

const uint8_t Duty_PWMHand[] = {
							20*1,	/**///-5
							20*1,	/**/
							30*1,	/**///-4
							30*1,	/**/
							40*1,	/**///-3
							40*1,	/**/
							50*1,	/**///-2
							50*1,	/**/
							60*1,	/**///-1
							60*1,	/**/
							70*1,	/**///0
							70*1,	/**/
							80*1,	/**/// 1
							80*1,	/**/
							85*1,	/**/// 2
							85*1,	/**/
							90*1,	/**/// 3
							90*1,	/**/
							95*1,	/**/// 4
							95*1,	/**/
							100*1,	/**/// 5
							100*1,	/**/
};

const uint8_t Duty_PWMCan[] = {
							100*1,	      /*0%*/ /*此等级为白天模式，设置亮度固定为100*/
							5*1,	      /*18%*/
							10*1,	/*20%*/
							15*1,	/*21%*/
							20*1,	/*23%*/
							25*1,	/*25%*//*5*/
							30*1,	/*27%*/
							35*1,	/*30%*/
							40*1,	/*32%*/
							45*1,	/*35%*/
							50*1,	/*38%*//*10*/
							55*1,	/*41%*/
							60*1,	/*45%*/
							65*1,	/*49%*/
							70*1,	/*53%*/
							75*1,	/*58%*//*15*/
							80*1,	/*63%*/
							85*1,	/*68%*/
							90*1,	/*74%*/
							95*1,	/*80%*/
							100*1,	/*87%*//*20*/
							100*1,	/*95%*/
};
#if 0
const uint8_t Duty_PWM[] = {
							0*1,	/*0%*/
							18*1,	/*18%*/
							20*1,	/*20%*/
							21*1,	/*21%*/
							23*1,	/*23%*/
							25*1,	/*25%*//*5*/
							27*1,	/*27%*/
							30*1,	/*30%*/
							32*1,	/*32%*/
							35*1,	/*35%*/
							38*1,	/*38%*//*10*/
							41*1,	/*41%*/
							45*1,	/*45%*/
							49*1,	/*49%*/
							53*1,	/*53%*/
							58*1,	/*58%*//*15*/
							63*1,	/*63%*/
							68*1,	/*68%*/
							74*1,	/*74%*/
							80*1,	/*80%*/
							87*1,	/*87%*//*20*/
							95*1,	/*95%*/
							100*1	/*100%*/
};
#endif

static const uint8_t lc_PmDelayTableMask[] = {'P','w','t','_','M','a','p'};//flash标记
/*电源DCDC频率*/
const uint32_t lc_lPMFreqTab[] = {700000,900000};
const tPWM_PHYSICAL_MAP la_tPMDCCtrlFreqMap = {
    2,NULL,lc_lPMFreqTab,_set_timing_xms_base_pwr_task_tick(50)
};


/*温度传感器阀值*/
const tADC_VALUE la_tTempValue[] = {

	{1,0,0,153  ,255 ,_set_timing_xms_base_pwr_task_tick(100)}, /*Temerature < 50'*/

	{0,0,1,151 ,153 ,_set_timing_xms_base_pwr_task_tick(100)},     
	{1,1,1,134 ,151 ,_set_timing_xms_base_pwr_task_tick(100)},    /*50 < Temerature < 60'*/
       
	{0,1,2,132 ,134 ,_set_timing_xms_base_pwr_task_tick(100)},     
	{1,2,2,118 ,132 ,_set_timing_xms_base_pwr_task_tick(100)},    /*60 < Temerature < 70'*/
	
	{0,2,3,116 ,118 ,_set_timing_xms_base_pwr_task_tick(100)},    
	{1,3,3,0    ,116 ,_set_timing_xms_base_pwr_task_tick(100)},    /*70 < Temerature*/
       
};

const tADC_PHYSICAL_MAP la_tTempDetRange = {
    0,7,4,la_tTempValue,NULL
};


const uint8_t lc_aFanPwmDuty[] ={
    0,80,90,100,  //对应4个阀值时候的占空比
};

const tPWM_PHYSICAL_MAP la_tFanPwmCtrlMap = {
    4,lc_aFanPwmDuty,NULL,_set_timing_xms_base_pwr_task_tick(50)
};

#define FILTER_TIME			150
/*调光器阀值*/
const tADC_VALUE la_tIllValue[LEVEL_ILL] = {
	{1,0,0,  0  , 58 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)}, 

	{0,0,1,  58 , 62 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},
	{1,1,1,  62 , 78 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},   

	{0,1,2,  78 , 82 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},
	{1,2,2,  82 , 98 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},   

	{0,2,3,  98 , 102,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},   
	{1,3,3,  102 ,126,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)}, 

	{0,3,4,  126 ,130 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},
	{1,4,4,  130 ,148,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)}, 

	{0,4,5,  148 ,152 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},
	{1,5,5,  152 ,170,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)}, 

	{0,5,6,  170 ,174 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},
	{1,6,6,  174 ,193,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)}, 

	{0,6,7,  193 ,197 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},
	{1,7,7,  197 ,228,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)}, 

	{0,7,8, 228 ,232 ,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)},
	{1,8,8, 232 ,255,_set_timing_xms_base_pwr_task_tick(FILTER_TIME)}, 	        
};


const tADC_PHYSICAL_MAP la_tIllDetRange = {
    0,LEVEL_ILL,LEVEL_VAILD,la_tIllValue,NULL
};

const uint8_t Vlot_DutyRatio[] = {70,60,60,50,50,40,40,30};
const uint8_t KeyLight_DutyRatio[] = {70,60,50,40,30,20,10,10};


static uint8_t sl_cIllBuff;
const tADC_VALUE la_tIllSoftValue[] = {
     {1,0,0,  0 ,20 ,_set_timing_xms_base_pwr_task_tick(100)},	 
	 {1,1,1,  120 ,40 ,_set_timing_xms_base_pwr_task_tick(100)},    
	 {1,2,2,  40 ,60 ,_set_timing_xms_base_pwr_task_tick(100)},   
	 {1,3,3,  60 ,80 ,_set_timing_xms_base_pwr_task_tick(100)},   
	 {1,4,4,  80 ,100,_set_timing_xms_base_pwr_task_tick(100)},   
	 {1,5,5,  100  ,128 ,_set_timing_xms_base_pwr_task_tick(100)},	 
	 {1,6,6,  128 ,150 ,_set_timing_xms_base_pwr_task_tick(100)},	 
	 {1,7,7,  150 ,172 ,_set_timing_xms_base_pwr_task_tick(100)},	
	 {1,8,8,  172 ,195 ,_set_timing_xms_base_pwr_task_tick(100)},	
	 {1,9,9,  195 ,230,_set_timing_xms_base_pwr_task_tick(100)},  
	 {1,10,10,230 ,255,_set_timing_xms_base_pwr_task_tick(100)}, 
};
const tADC_PHYSICAL_MAP la_tILLDetSoftRang = {

    1,11,11,la_tIllSoftValue,&sl_cIllBuff
};
/*********两组阀值:防止开关机因为电压不同而影响到AD检测************************/
/*
BATT+     AD input  ON_AD value     OFF_state AD
19.0V   xxxx    233                 237
18.5V   xxxx    227                 231
18.0V   xxxx    222                 226
17.5V   xxxx    215                 219
17.0V   xxxx    209                 213
16.5V   xxxx    202                 207
10.0V   xxxx    120                 125
9.5V    xxxx    113                 119
9.0V    xxxx    107                 113
 
*/
/*****************************电压值  低压关 低压开 高压开  高压关 *************/
const tADC_VALUE la_tBatRangeON[] = {
    {1,PM_BATLEV_LOWEST,0,   0,   79,_set_timing_xms_base_pwr_task_tick(30) },          /*V < 6.5v*/
    {0,PM_BATLEV_LOWEST,PM_BATLEV_LOW_OFF,  79, 87,_set_timing_xms_base_pwr_task_tick(50) },          /*6.5v < V < 6.9v */
    {1,PM_BATLEV_LOW_OFF,0,  87, Threshold_NormalToLow,_set_timing_xms_base_pwr_task_tick(50) },          /*6.9v < V < 9v */
    {1,PM_BATLEV_LOW_ON,0,   Threshold_NormalToLow,Threshold_LowToNormal,_set_timing_xms_base_pwr_task_tick(50) },          /*9.0v < V < 9.5v*/
    {1,PM_BATLEV_NORMAL,0,   Threshold_LowToNormal,Threshold_HighToNormal,_set_timing_xms_base_pwr_task_tick(600)},          /*9.5v < V < 17.6v*//*400MS CHANGE TO 600MS,MAKE SURE THE SYS5V IS LOW*/
    {1,PM_BATLEV_HIGHT_ON,0, Threshold_HighToNormal,Threshold_NormalToHigh,_set_timing_xms_base_pwr_task_tick(100)},          /*17.6v < V < 18v*/
    {1,PM_BATLEV_HIGHT_OFF,0,Threshold_NormalToHigh,240,_set_timing_xms_base_pwr_task_tick(100) },          /*18v < V*/
    {1,PM_BATLEV_HIGHTEST,0, 240,255,_set_timing_xms_base_pwr_task_tick(50) },         /*6.9v < V < 9.0v */
};

const tADC_VALUE la_tBatRangeOFF[] = {
    {1,PM_BATLEV_LOWEST,0,   0,   79,_set_timing_xms_base_pwr_task_tick(30) },          /*V < 6.5v*/
    {0,PM_BATLEV_LOWEST,PM_BATLEV_LOW_OFF, 79, 87,_set_timing_xms_base_pwr_task_tick(50) },          /*6.5v < V < 6.9v */
    {1,PM_BATLEV_LOW_OFF,0,  87, Threshold_NormalToLow,_set_timing_xms_base_pwr_task_tick(50) },          /*6.9v < V < 9v */
    {1,PM_BATLEV_LOW_ON,0,   Threshold_NormalToLow,Threshold_LowToNormal,_set_timing_xms_base_pwr_task_tick(50) },          /*9.0v < V < 9.5v*/
    {1,PM_BATLEV_NORMAL,0,   Threshold_LowToNormal,Threshold_HighToNormal,_set_timing_xms_base_pwr_task_tick(600)},          /*9.5v < V < 17.6v*/
    {1,PM_BATLEV_HIGHT_ON,0, Threshold_HighToNormal,Threshold_NormalToHigh,_set_timing_xms_base_pwr_task_tick(100)},          /*17.6v < V < 18v*/
    {1,PM_BATLEV_HIGHT_OFF,0,Threshold_NormalToHigh,240,_set_timing_xms_base_pwr_task_tick(100) },          /*18v < V*/
    {1,PM_BATLEV_HIGHTEST,0, 240,255,_set_timing_xms_base_pwr_task_tick(50) },         /*6.9v < V < 9.0v */
};


const tADC_PHYSICAL_MAP la_tBatThresMap_ON = {
    0,8,7,la_tBatRangeON,NULL
};

const tADC_PHYSICAL_MAP la_tBatThresMap_OFF = {
    0,8,7,la_tBatRangeOFF,NULL
};


const tPM_DELAY_TIME_TAB lc_tPMDlyTimingTab ={
    /*Tft Set timing*/
   /*
	*  according JX PM requirment, need mask PM_MODE_STANDBY;
	*  please attention!!!!!!! 
	*  marked by zhaowenlong, 20140710
	*/
   /* (1<<PM_MODE_STANDBY)|*/(1<<PM_MODE_ON)|(1<<PM_MODE_ECONOMY),
     _set_timing_xms_base_pwr_task_tick(200L),

    /*Power delay*/
     _set_timing_xms_base_pwr_task_tick(50L),
     _set_timing_xms_base_pwr_task_tick(100L),
     _set_timing_xms_base_pwr_task_tick(30L),
};



void PM_EnterModeHook(ePM_MODE eMode)
{
}


void PM_ExitModeHook(ePM_MODE eMode)
{
}

/******************************************************************************/



typedef enum{    
    PMOUT_ILM_300MA_P15,   /*EN = M | EM = H*/
    PMOUT_AUDIO_500_P9,    /*EN = M | EM = H*/
    PMOUT_EXT1_500MA_P3,   /*EN = M | EM = H*/
    PMOUT_AMP_300MA_P1,    /* EM = H*/
    
    PMOUT_EXT2_500MA_P11,  /*CTL1 = M | CTL1 = H*/
    PMOUT_EXT4_500MA_P13,  /*CTL1 = H*/

    PMOUT_ANT_300MA_P2,    /*CTL2 = M | CTL2 = H*/
    PMOUT_EXT3_350MA_P12,  /* CTL2 = H*/
    

    PMOUT_NUM
}ePM_LV5686_OUTPUT;

typedef enum {
    PMIN_PIN_EN,
    PMIN_PIN_CTL1,
    PMIN_PIN_CTL2,

    PMIN_PIN_NUM
}ePM_LV5686_INPUT_PIN;


typedef enum {
    PMIN_STATE_LOW  ,
    PMIN_STATE_MIDD ,
    PMIN_STATE_HIGHT,
    PMIN_STATE_NUM
}ePM_LV5686_INPUT_STATE;

typedef struct{
    ePM_LV5686_OUTPUT eStart;
    ePM_LV5686_OUTPUT eEnd;
    uint8_t cIoIdx;
}tLV5686_IN_OUT_MAP;

typedef struct{
    ePM_LV5686_INPUT_PIN   eCtlPin;
    
    ePM_LV5686_INPUT_STATE ePinState;
}tLV5686_CTL_IO_MAP;


tLV5686_IN_OUT_MAP l_tLv5686InOutMap[PMIN_PIN_NUM] ={
    {PMOUT_ILM_300MA_P15,PMOUT_AMP_300MA_P1,IO_IDX_POWER_EN},
    {PMOUT_EXT2_500MA_P11,PMOUT_EXT4_500MA_P13,IO_IDX_POWER_CTRL1},
    {PMOUT_ANT_300MA_P2,PMOUT_EXT3_350MA_P12,IO_IDX_POWER_CTRL2},
    
};

tLV5686_CTL_IO_MAP l_tLv5686CtlIOMap[PMOUT_NUM] = {

    {PMIN_PIN_EN, PMIN_STATE_MIDD},

    {PMIN_PIN_EN, PMIN_STATE_MIDD},
    {PMIN_PIN_EN, PMIN_STATE_MIDD},

    {PMIN_PIN_EN, PMIN_STATE_HIGHT},


    {PMIN_PIN_CTL1, PMIN_STATE_MIDD},
    {PMIN_PIN_CTL1, PMIN_STATE_HIGHT},

    {PMIN_PIN_CTL2, PMIN_STATE_MIDD},
    {PMIN_PIN_CTL2, PMIN_STATE_HIGHT},

};



uint8_t  la_tPmLv5696OutState[PMOUT_NUM];          /*save dev output state*/
uint8_t  la_tPmLv5686CtlPinState[PMIN_PIN_NUM];    /*save control pin state*/

void PM_Lv5686_Driver(uint8_t cIdx,uint8_t bOnOff)
{
    if(cIdx < PMOUT_NUM)
    {
        ePM_LV5686_OUTPUT i;
        ePM_LV5686_OUTPUT eStart,eEnd;
        ePM_LV5686_INPUT_PIN eCtrPin = l_tLv5686CtlIOMap[cIdx].eCtlPin;
        ePM_LV5686_INPUT_STATE eCtlPinState = PMIN_STATE_LOW;
        ePM_LV5686_INPUT_STATE eCtlPinStateLast = la_tPmLv5686CtlPinState[eCtrPin];
        eStart = l_tLv5686InOutMap[eCtrPin].eStart;
        eEnd = l_tLv5686InOutMap[eCtrPin].eEnd;
        
        /*Set Current Output state: ON or OFF*/
        if(bOnOff)eCtlPinState = l_tLv5686CtlIOMap[cIdx].ePinState;  
        la_tPmLv5696OutState[cIdx] = bOnOff;

        /*Scan the output pins controled by the same input pin*/
        for(i = eStart;i <= eEnd; i++)
        {
            ePM_LV5686_INPUT_STATE targState = PMIN_STATE_LOW;
            if(la_tPmLv5696OutState[i])targState = l_tLv5686CtlIOMap[i].ePinState;
            if(targState > eCtlPinState)eCtlPinState = targState;
        }

        /*reflash input pin*/
        if(eCtlPinStateLast != eCtlPinState)
        {
            uint8_t cPinDir = PIN_OUTPUT;
            uint8_t cValue = INVALID;
            if(eCtlPinState == PMIN_STATE_MIDD)cPinDir = PIN_INPUT;
            else if(eCtlPinState == PMIN_STATE_HIGHT)cValue = VALID;
            la_tPmLv5686CtlPinState[eCtrPin] = eCtlPinState;
            IO_Set(l_tLv5686InOutMap[eCtrPin].cIoIdx,cPinDir,cValue);
        }
    }
    
}

void PM_Lv5686Init(void)
{
    uint8_t i;
    API_MemClear(la_tPmLv5696OutState,PMOUT_NUM);
    API_MemClear(la_tPmLv5686CtlPinState,PMIN_STATE_NUM);
    for(i = 0; i < PMIN_PIN_NUM;i++)
    {
        la_tPmLv5686CtlPinState[i] = PMIN_STATE_LOW;
        IO_Set(l_tLv5686InOutMap[i].cIoIdx,PIN_OUTPUT,INVALID);
    }
}



/******************************************************************************
*  Control the power switch of all units  
*  IF some unit power is output by a same com,you must create mutex flag to control
*******************************************************************************/

void PM_UnitPowerSet(ePM_UNIT eUnit,bool bOnOff)
{
    
    switch(eUnit)
    {
        case PM_UNIT_MAIN:		//control DC-DC
			IO_Set(IO_IDX_PM_SNT_FREQ,PIN_OUTPUT,0);
			IO_Set(IO_IDX_SYS_5V,PIN_OUTPUT,bOnOff);
			IO_Set(IO_IDX_7186_BOOT0,PIN_OUTPUT,VALID);
			IO_Set(IO_IDX_7186_BOOT1,PIN_OUTPUT,VALID);
			IO_Set(IO_IDX_7186_DUT_BOOT_EN1,PIN_OUTPUT,VALID);
			IO_Set(IO_IDX_8836A_PWR,PIN_OUTPUT,VALID);

			//IO_Set(IO_IDX_7186_RESET_DUT1,PIN_OUTPUT,INVALID);
			if(bOnOff)IO_ADCInit(IO_IDX_BATTERY_DET,(tADC_PHYSICAL_MAP*)&la_tBatThresMap_ON);
			else IO_ADCInit(IO_IDX_BATTERY_DET,(tADC_PHYSICAL_MAP*)&la_tBatThresMap_OFF);
			// IO_Set(IO_IDX_LINE_MUTE, PIN_OUTPUT, VALID);
			//IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,bOnOff);
			//IO_Set(IO_IDX_TFT_VGL,PIN_OUTPUT,bOnOff);
			pm_printf(_T("--PMSetMain:%d %lx\n",bOnOff,OS_GetOsTick()));
			break;
     
        case PM_UNIT_APU:		//CB_PWR_CTL(Open APU 5V)
#if 1
			IO_Set(IO_IDX_TFT_POWER_EN, PIN_OUTPUT, bOnOff);
			if(bOnOff == 1)
			{
				IO_Set(IO_IDX_APU_LOWPWR, PIN_OUTPUT,INVALID); 
			}
			else
			{
				IO_Set(IO_IDX_APU_LOWPWR, PIN_OUTPUT,VALID); 
			}
#else 
			IO_Set(IO_IDX_SYS_5V,PIN_OUTPUT,bOnOff);
			IO_Set(IO_IDX_TFT_POWER_EN, PIN_OUTPUT, bOnOff);
			IO_Set(IO_IDX_AMP_STANDBY, PIN_OUTPUT, VALID);
			IO_Set(IO_IDX_FAN_CTRL,PIN_OUTPUT,0); 
			PM_Lv5686_Driver(PMOUT_AUDIO_500_P9, bOnOff);
			PM_Lv5686_Driver(PMOUT_ILM_300MA_P15, bOnOff);
			PM_Lv5686_Driver(PMOUT_ANT_300MA_P2, bOnOff);
			PM_Lv5686_Driver(PMOUT_EXT3_350MA_P12, bOnOff);
#endif
	     pm_printf(_T("--  PMSetAPU:%d--%lx\n",bOnOff,OS_GetOsTick()));
        break;
        case PM_UNIT_APU_BKP:
            IO_Set(IO_IDX_APU_BCK_POWER,PIN_OUTPUT,bOnOff);
            pm_printf(_T("--  PMSetBKP:%d--%lx\n",bOnOff,OS_GetOsTick()));
        break;
        case PM_UNIT_APU_SLEEP:
            IO_Set(IO_IDX_SLEEP_5V,PIN_OUTPUT,bOnOff);
            pm_printf(_T("--  PMSetSL5V:%d--%lx\n",bOnOff,OS_GetOsTick()));
        break;
        case PM_UNIT_ANT:
            PM_Lv5686_Driver(PMOUT_ANT_300MA_P2, bOnOff);
        break;
        case PM_UNIT_AMP:
        case PM_UNIT_FAN:
            PM_Lv5686_Driver(PMOUT_AMP_300MA_P1, bOnOff);
        break;
        case PM_UNIT_TFT :
            //PM_Lv5686_Driver(PMOUT_EXT2_500MA_P11, bOnOff);
            IO_Set(IO_IDX_TFT_POWER_EN, PIN_OUTPUT, bOnOff);
			pm_printf(_T("--  PM_UNIT_TFT:%d--%lx\n",bOnOff,OS_GetOsTick()));        
			break;
        case PM_UNIT_DTV:
            PM_Lv5686_Driver(PMOUT_EXT4_500MA_P13, bOnOff);
        break;
        case PM_UNIT_RADAR:
            PM_Lv5686_Driver(PMOUT_EXT3_350MA_P12, bOnOff);
            pm_printf(_T("--  PM_UNIT_RADAR:%d--\n",bOnOff));
        break;
        case PM_UNIT_TFT_VHL:
            IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,bOnOff);
            IO_Set(IO_IDX_TFT_VGL,PIN_OUTPUT,bOnOff);
	     pm_printf(_T("--  PM_UNIT_TFT_VHL:%d--%lx\n",bOnOff,OS_GetOsTick()));		
        break;
        case PM_UINT_DISC:
            IO_Set(IO_IDX_DVD_POWER,PIN_OUTPUT,bOnOff);
        break;
        case PM_UNIT_AUDIO:
            PM_Lv5686_Driver(PMOUT_AUDIO_500_P9, bOnOff);
        break;
        case PM_UNIT_KEY_LED:
            PM_Lv5686_Driver(PMOUT_ILM_300MA_P15, bOnOff);
        break;
        case PM_UNIT_PHANTTOM:
            PM_Lv5686_Driver(PMOUT_EXT1_500MA_P3, bOnOff);
        break;
        case PM_UNIT_ALL:		
            if(OFF == bOnOff)
            {
                IO_Set(IO_IDX_TFT_EN_PWM,PIN_OUTPUT,OFF);
                IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,OFF);
                IO_Set(IO_IDX_TFT_VGL,PIN_OUTPUT,OFF);
                PM_Lv5686Init();
		   IO_Set(IO_IDX_APU_LOWPWR, PIN_OUTPUT,VALID); 
                IO_Set(IO_IDX_SLEEP_5V,PIN_OUTPUT,OFF);
                IO_Set(IO_IDX_APU_BCK_POWER,PIN_OUTPUT,OFF);
                IO_Set(IO_IDX_SYS_5V,PIN_OUTPUT,OFF);// bolte
                IO_Set(IO_IDX_POWER_LED,PIN_OUTPUT,OFF);
                
            }
        break;
        
    }
}

/******************************************************************************* 
 *
 * This fuction is called in the PM_ENTRY MODE
 *
 ******************************************************************************/
void PM_IoInit(void)
{
    IO_Set(IO_IDX_APU_RESET, PIN_OUTPUT,VALID); 
    IO_Set(IO_IDX_REVERSE_OUT,PIN_OUTPUT,INVALID);                    //倒车信号初始化
    //io init
    IO_Set(IO_IDX_APU_LOWPWR, PIN_OUTPUT,VALID); 
    
    IO_ADCInit(IO_IDX_BATTERY_DET,(tADC_PHYSICAL_MAP*)&la_tBatThresMap_OFF);
    IO_ADCInit(IO_IDX_TEMP_DET,(tADC_PHYSICAL_MAP*)&la_tTempDetRange);
	#ifdef D_ILL_ADC_CHECK //snake20160822
    IO_ADCInit(IO_IDX_ILL_DET,(tADC_PHYSICAL_MAP*)&la_tIllDetRange);
	#endif
    //IO_PWMInit(IO_IDX_PM_SNT_FREQ,(tPWM_PHYSICAL_MAP*)&la_tPMDCCtrlFreqMap);
    IO_PWMInit(IO_IDX_FAN_CTRL,(tPWM_PHYSICAL_MAP*)&la_tFanPwmCtrlMap);
    IO_Set(IO_IDX_FAN_CTRL,PIN_OUTPUT,0); 
    IO_Set(IO_IDX_KEY_PWM,PIN_OUTPUT,OFF);
  //  IO_Set(IO_IDX_SPEED_PULSE,PIN_OUTPUT,OFF);
    //IO_Set(IO_IDX_KEY_GLED,PIN_OUTPUT,OFF);
    //IO_Set(IO_IDX_MCU2DR_PWR,PIN_OUTPUT,OFF);
    IO_Set(IO_IDX_POWER_LED,PIN_OUTPUT,OFF);
    
    /*Set io scan */
    IO_Scan_Set(IO_IDX_ACC_WAKE, VALID);
    IO_Get(IO_IDX_ACC_WAKE,PIN_INPUT,INVALID); 

    IO_Get(IO_IDX_DISC_IN_DET,PIN_INPUT,INVALID);
    IO_Scan_Set(IO_IDX_DISC_IN_DET,VALID);

    IO_Get(IO_IDX_NAVI_AUDIO,PIN_INPUT,INVALID);
    IO_Scan_Set(IO_IDX_NAVI_AUDIO,VALID);
    
    IO_Get(IO_IDX_REVERSE_DET,PIN_INPUT,INVALID);
    IO_Scan_Set(IO_IDX_REVERSE_DET,VALID);

    IO_Get(IO_IDX_ILL_DET,PIN_INPUT,INVALID);
    IO_Scan_Set(IO_IDX_ILL_DET,VALID);
    
    IO_Get(IO_IDX_MODULE_DET,PIN_INPUT,INVALID);
    IO_Get(IO_IDX_ILL_DET,PIN_INPUT,INVALID);
    IO_Scan_Set(IO_IDX_BATTERY_DET,VALID);
    IO_Get(IO_IDX_BATTERY_DET,PIN_INPUT,INVALID);
    IO_Scan_Set(IO_IDX_TEMP_DET,VALID);
    IO_Get(IO_IDX_TEMP_DET,PIN_INPUT,INVALID);
    
    IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
    IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
}


/******************************************************************************* 
 *
 * Reflash the IO state when power on
 *
 ******************************************************************************/
void PM_IoRestartScan(void)
{
	
    IO_ResetState(IO_IDX_ILL_DET,INVALID);
   // IO_ResetState(IO_IDX_PARKING_DET,INVALID);
    IO_ResetState(IO_IDX_TEMP_DET,INVALID);
    IO_ResetState(IO_IDX_FAN_CTRL,0);
    /*MUTE  Front System*/
    /*MUTE  Rear System*/
    IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
   IO_ResetState(IO_IDX_REVERSE_DET,INVALID);	  /*解决倒车开机不进倒车*/
}


/******************************************************************************* 
 *
 * In any time and any condition,compute the tft black light level
 *
 ******************************************************************************/
uint8_t PM_GetTftBLValue(void)
{

	#ifndef D_ILL_ADC_CHECK //snake20160922 不使用调光器
		uint8_t Duty;
		uint8_t level = g_tSysRomData.tScrBlock.cBaseBR;
		if((g_tMcuDevState.uIOState.bits.Reverse_Flag) || (g_tMcuDevState.uDetect.bits.Blind_Flag))
		{
			Duty = Duty_PWM[10];
			pm_printf(_T("ReverseDuty =%d\n",Duty));		
		}
		else
		{
			if(g_tSysRomData.uGenBlock.tBlock.tFlag3.bAuto_Dimmer_Set)
			{
				pm_printf(_T("==auto   "));
				if(IO_Get(IO_IDX_ILL_DET,PIN_INPUT,TRUE)==1)//ILL ON
				{
					Duty = Duty_PWM[0];
				}
				else
				{
					Duty = Duty_PWM[10];
				}
			}
			else
			{
				pm_printf(_T("==hand   "));
				if(level > D_TFT_BL_LEV_NUM)
					level = D_TFT_BL_LEV_NUM;
				
				Duty = Duty_PWM[level];
			}
			pm_printf(_T("Duty =%d\n",Duty));		
		}
	#else
		uint8_t Duty;
		uint8_t level = SysWorkStatusGrp.SysILLlevel;

		pm_printf(_T("LEVEL parameter  = %x\n", level));
		if(level >= (LEVEL_VAILD-1))		// ILL off STATE
		{
			level = LEVEL_VAILD-2;
		}
		/*
		*	1. NEXT Part: get the TFT pwm duty value.
		*/
		if(!g_tMcuDevState.uIOState.bits.Reverse_Flag)		//非倒车状态
		{
			if(g_tSysRomData.uGenBlock.tBlock.tFlag3.bAuto_Dimmer_Set)//auto mode
			{
				pm_printf(_T("==auto   "));
				pm_printf(_T("g_BKAutoLevel =%d   ",g_BKAutoLevel));
				if(g_BKAutoLevel < 0)
				{
					g_BKAutoLevel = 0;
				}
				else if(g_BKAutoLevel>= sizeof(Duty_PWMCan))
				{
					g_BKAutoLevel = sizeof(Duty_PWMCan);
				}
				Duty = Duty_PWMCan[g_BKAutoLevel];
			}
			else//hand mode
			{
				extern tEEP_DATA_BLOCK l_tEepSysRomData;
				pm_printf(_T("==hand   g_BKHandLevel =%d  %d ",g_BKHandLevel,g_tSysRomData.tScrBlock.cBaseBR));
				if(g_BKHandLevel < 0)
				{
					g_BKHandLevel = 0;
				}
				else if(g_BKHandLevel>= sizeof(Duty_PWMHand))
				{
					g_BKHandLevel = sizeof(Duty_PWMHand);	
				}
				g_tSysRomData.tScrBlock.cBaseBR= g_BKHandLevel;	
				EEP_CreateBlockChkSum(&l_tEepSysRomData);
				EEP_WriteStart(&l_tEepSysRomData,1);
				Duty = Duty_PWMHand[g_BKHandLevel];
			}
			pm_printf(_T("Duty =%d\n",Duty));
		}
		else if((g_tMcuDevState.uIOState.bits.Reverse_Flag) || (g_tMcuDevState.uDetect.bits.Blind_Flag))
		{
			Duty = 100;
			pm_printf(_T("ReverseDuty =%d\n",Duty));
		}
		/*
		*	2. NEXT Part: deal key light control.
		*/
		if(g_tMcuDevState.uIOState.bits.Illumi_On == 0x0)
		{
			IO_Set(IO_IDX_KEY_PWM,PIN_OUTPUT,0);
			pm_printf(_T("KEY led off!\n"));
		}
		else
		{
			IO_Set(IO_IDX_KEY_PWM,PIN_OUTPUT,KeyLight_DutyRatio[level]);
			pm_printf(_T("KEY led on!\n"));
		}
		//Duty = 100;//xiaolei tiaoshi add
#endif
	
	return Duty;

}

/******************************************************************************/


typedef struct{
   uint8_t (*pf_GetValue)(uint8_t min,uint8_t max);
   uint8_t cValidMin,cValidMax;
   uint8_t cValidCnt;
  
   eOP_PM_AWAKE_EVENT eEvt; 
   
}tOP_PM_AWAKE_DET_BLOCK;


typedef struct{
    uint8_t cEvtCnt[OP_PM_AWAKE_EVT_N];
    uint8_t cLastState[OP_PM_AWAKE_EVT_N];
    const tOP_PM_AWAKE_DET_BLOCK* p_tDetBlock;

    uint8_t cTaskStep;
    
}tPM_SLEEP_BLOCK;

tPM_SLEEP_BLOCK l_tPMSleepCB;


void PM_MsgHandHook(tMSG_BUF* p_tMsg)
{
    uint16_t cMsgID = p_tMsg->Id;
    uint16_t cMsgOp = p_tMsg->iSid;
    
    switch(cMsgID)
    {
        
        case MS_SYS_APU_INFO:

        break;
        
        case MS_SYS_BUS_INFO:
               
        break;

    }
}




uint8_t PM_AwakeDetAcc(uint8_t min,uint8_t max)
{
    uint8_t re = IO_Get(IO_IDX_ACC_WAKE,PIN_INPUT,FALSE);
    return re;
}

uint8_t PM_AwakeDetIll(uint8_t min,uint8_t max)//snake20160922
{
    uint8_t re = IO_Get(IO_IDX_ILL_DET,PIN_INPUT,FALSE);
    return re;
}

uint8_t PM_AwakeDetDiscIn(uint8_t min,uint8_t max)
{
    uint8_t re = INVALID;//IO_Get(IO_IDX_DISC_IN_DET,PIN_INPUT,FALSE);
    return re;
}


uint8_t PM_AwakeDetKey1(uint8_t min,uint8_t max)
{
    uint8_t re = INVALID;
    uint8_t cVal = IO_Get(IO_IDX_KEY1_DET,PIN_INPUT,FALSE);
    if(cVal >= min && cVal < max)re = VALID;
    return re;
}

uint8_t PM_AwakeDetKey2(uint8_t min,uint8_t max)
{
    uint8_t re = INVALID;
    uint8_t cVal = IO_Get(IO_IDX_KEY2_DET,PIN_INPUT,FALSE);
    if(cVal >= min && cVal < max)re = VALID;
    return re & IO_Get(IO_IDX_DISC_IN_DET,PIN_INPUT,FALSE);
}

uint8_t PM_AwakeDetBattery(uint8_t min,uint8_t max)
{
    uint8_t re = INVALID;
    uint8_t cVal = IO_Get(IO_IDX_BATTERY_DET,PIN_INPUT,FALSE);
    if(cVal < min || cVal > max)re = VALID;
    return re;
}


const tOP_PM_AWAKE_DET_BLOCK l_tAwakeDetTab[] = {
    
    {PM_AwakeDetAcc,0,0,1,OP_PM_AWAKE_ACC},
    {PM_AwakeDetDiscIn,0,0,5,OP_PM_AWAKE_DISCIN},
    
    {PM_AwakeDetKey1,0,7,3,OP_PM_AWAKE_PWRKEY},
    {PM_AwakeDetKey2,156,169,3,OP_PM_AWAKE_EJCKEY},
    {PM_AwakeDetBattery,87,Threshold_NormalToHigh,3,OP_PM_AWAKE_BAT_ERR},
    {PM_AwakeDetIll,0,0,1,OP_PM_AWAKE_ILL},//snake20160922
    {NULL,0,0,0,OP_PM_AWAKE_NONE},

};

void PM_SleepInit(void)
{
    API_MemClear((uint8_t*)&l_tPMSleepCB,sizeof(tPM_SLEEP_BLOCK));
    l_tPMSleepCB.p_tDetBlock = (const tOP_PM_AWAKE_DET_BLOCK*)&l_tAwakeDetTab;
}



eOP_PM_AWAKE_EVENT PM_GetAwakeEvent(eOP_PM_AWAKE_EVENT eIdx)
{
    eOP_PM_AWAKE_EVENT re = OP_PM_AWAKE_EVT_N;
    uint8_t i = 0;
    const tOP_PM_AWAKE_DET_BLOCK* p_tBlock = NULL;
    eOP_PM_AWAKE_EVENT eCheckIdx = OP_PM_AWAKE_EVT_N;

    if(l_tPMSleepCB.p_tDetBlock && p_tBlock->pf_GetValue)
    {
        uint8_t cCurrState = INVALID;

        while(eCheckIdx)
        {
            p_tBlock = &(l_tPMSleepCB.p_tDetBlock[i]);
            eCheckIdx = p_tBlock->eEvt;
            if(eCheckIdx == eIdx)
			break;
            else
			i++;
        }

        if(p_tBlock)
        {

            if(p_tBlock->pf_GetValue)
			cCurrState = p_tBlock->pf_GetValue(p_tBlock->cValidMin,p_tBlock->cValidMax);
            
		if(cCurrState != l_tPMSleepCB.cLastState[i])
		{
			l_tPMSleepCB.cEvtCnt[i] = 1;
			l_tPMSleepCB.cLastState[i] = cCurrState;
		} 
		else
		{
			l_tPMSleepCB.cEvtCnt[i] ++;
		}
		if(l_tPMSleepCB.cEvtCnt[i]  >=  p_tBlock->cValidCnt)
		{
			if(cCurrState == VALID)
			{
				re = p_tBlock->eEvt;
			}
			else
			{ 
				re = OP_PM_AWAKE_NONE;
			}
		}

        }
    }

    return re;
}

eOP_PM_AWAKE_EVENT PM_GetAllAwakeEvent(void)
{
    eOP_PM_AWAKE_EVENT re = OP_PM_AWAKE_NONE;
    uint8_t i;
    for(i = (OP_PM_AWAKE_NONE+1);i < OP_PM_AWAKE_EVT_N ;i++)
    {
        re = PM_GetAwakeEvent(i);
        if(re && re < OP_PM_AWAKE_EVT_N)break;
    }

    return re;
}


eOP_PM_AWAKE_EVENT PM_SleepTask(void)
{
    eOP_PM_AWAKE_EVENT re = OP_PM_AWAKE_NONE;
    
    
    if(l_tPMSleepCB.cTaskStep == 0)
    {
        /*Get the event init state,than if state change,go next*/
        (void)PM_GetAllAwakeEvent();
        l_tPMSleepCB.cTaskStep ++;
    }
    else
    {
        re = PM_GetAllAwakeEvent();
    }
        

    return re;
}



void PM_LviSetIO(void)
{
	IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,OFF);
	IO_Set(IO_IDX_TFT_VGL,PIN_OUTPUT,OFF);

	IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
	//Rear System
	IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);

	IO_Set(IO_IDX_APU_RESET, PIN_OUTPUT,VALID);

	// Reset IO Port To Sleep State
	IO_Set(IO_IDX_PHANTOM_POWER1,PIN_OUTPUT,INVALID);
	IO_Set(IO_IDX_PHANTOM_POWER2,PIN_OUTPUT,INVALID);
	PM_UnitPowerSet(PM_UNIT_ALL, OFF);
	IO_ADCInit(IO_IDX_BATTERY_DET,(tADC_PHYSICAL_MAP*)&la_tBatThresMap_OFF);
	BattADCInit();
}



void PM_SleepSetIO(void)
{
	IO_Set(IO_IDX_TFT_3V3,PIN_OUTPUT,OFF);
	IO_Set(IO_IDX_TFT_VGL,PIN_OUTPUT,OFF);

	//IO_Set(IO_IDX_APU_POWER,PIN_OUTPUT,OFF);
	IO_Set(IO_IDX_APU_LOWPWR, PIN_OUTPUT,VALID); 
	IO_Set(IO_IDX_APU_RESET, PIN_OUTPUT,VALID);
	/*release mute*/
	IO_Set(IO_IDX_AMP_STANDBY,PIN_INPUT,VALID);
	IO_Set(IO_IDX_REAR_MUTE,PIN_INPUT,VALID);

	// Reset IO Port To Sleep State
	IO_Set(IO_IDX_PHANTOM_POWER1,PIN_OUTPUT,INVALID);
	IO_Set(IO_IDX_PHANTOM_POWER2,PIN_OUTPUT,INVALID);
	IO_ADCInit(IO_IDX_BATTERY_DET,(tADC_PHYSICAL_MAP*)&la_tBatThresMap_OFF);
}


void PM_OffSetIO(void)
{
	PM_Lv5686Init();

	IO_Set(IO_IDX_AMP_STANDBY,PIN_INPUT,VALID);
	#ifdef D_AMP_TDA7388
	IO_Set(IO_IDX_AMP_MUTE,PIN_INPUT,VALID);
	#endif
	//Rear System
	IO_Set(IO_IDX_REAR_MUTE,PIN_INPUT,VALID);

	IO_Set(IO_IDX_APU_RESET, PIN_INPUT,VALID);

	// Reset IO Port To Sleep State
	IO_Set(IO_IDX_PHANTOM_POWER1,PIN_OUTPUT,INVALID);
	IO_Set(IO_IDX_PHANTOM_POWER2,PIN_OUTPUT,INVALID);
	IO_ADCInit(IO_IDX_BATTERY_DET,(tADC_PHYSICAL_MAP*)&la_tBatThresMap_OFF);
}


