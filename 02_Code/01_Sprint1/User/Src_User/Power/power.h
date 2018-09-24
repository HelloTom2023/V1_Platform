#ifndef _PM_H_
#define _PM_H_

#ifndef _PM_C_
#define _PM_    extern
#else
#define _PM_ 
#endif


#ifndef _PM_USER_C_
#define _PMU_    extern
#else
#define _PMU_ 
#endif

#if D_DEBUG_POWER && D_PRINT_EN
#define pm_printf(x)   x
#else
#define pm_printf(x)
#endif



#define _PM_TASK_TIMING_              _4MS_
#define _PM_CORE_TIMING_              _1MS_
#define _PM_TASK_TICK_                _set_timing_xms_base_core_tick(_PM_TASK_TIMING_)
#define _PM_CORE_TICK_                _set_timing_xms_base_core_tick(_PM_CORE_TIMING_)
#define _set_timing_xms_base_pwr_task_tick(x) ((x/_PM_TASK_TIMING_)-1)
#define _set_timing_xms_base_pwr_core_tick(x) ((x/_PM_CORE_TIMING_)-1)
#define _set_timing_sec_base_pwr_task_tick(x) ((x*1000/_PM_TASK_TIMING_)-1)


#define D_PWR_MSG_QUE_DEEP      5
#define D_BPWR_UPDATE_INFO_TIME         _set_timing_xms_base_pwr_task_tick(1000)
#define D_BPWR_ERR_VALID_TIME           _set_timing_xms_base_pwr_task_tick(50)
#define D_BPWR_ERR_RESUME_TIME          _set_timing_xms_base_pwr_task_tick(500)
#define D_DEFAULT_TFT_ON_DELAY_TIMMING  _set_timing_xms_base_pwr_task_tick(200)
#define D_ECONOMY_HOLD_TIME             _set_timing_xms_base_pwr_task_tick(6000L)

#define D_TFT_BL_LEV_NUM     10 // snake20160922 14
#define D_TFT_MIN_BL         7
#define D_TFT_MAX_BL         100

#define LEVEL_ILL					17
#define LEVEL_VAILD					9


#define PWR_TIME_START		_set_timing_xms_base_pwr_task_tick(30L)
#define PWR_TIME_CHK			_set_timing_xms_base_pwr_task_tick(50L)
#define PWR_TIME_WAIT_STABLE	_set_timing_xms_base_pwr_task_tick(30L)

#define TFT_BL_ON		1
#define TFT_BL_OFF		0

/*长安要求B+ 低于6.5V时做防抖，以免立即重启*/
#define LVI_6POINT5V_KEEP_TIME	50	// 50 * 1ms


uint8_t  g_BKAutoLevel;
uint8_t  g_BKHandLevel;
typedef enum{
    PM_BATLEV_LOWEST,
    PM_BATLEV_LOW_OFF,
    PM_BATLEV_LOW_ON,
    PM_BATLEV_NORMAL,
    PM_BATLEV_HIGHT_ON,
    PM_BATLEV_HIGHT_OFF,
    PM_BATLEV_HIGHTEST,

    PM_BATLEV_N
}ePM_BATTERY_LEV;


typedef enum{
    PM_MODE_ENTERY,
    PM_MODE_CHECK,
    PM_MODE_STANDBY,
    PM_MODE_ON,
    
    PM_MODE_ECONOMY,
    PM_MODE_WAIT_SLEEP,
    PM_MODE_SLEEP,
    PM_MODE_OFF,
    PM_MODE_BATTERY_ERROR,
    PM_MODE_LVI,
    
    PM_MODE_TEMP_ON,
    PM_MODE_NUM
    
}ePM_MODE;        /*PM main state*/


typedef enum{
    PM_DISPLAYER_DISABLE,
    PM_DISPLAYER_WAIT_CLOSE,
    PM_DISPLAYER_ENABLE,
    PM_DISPLAYER_IDLE,
    
    PM_DISPLAYER_SN
    
}ePM_DISPLAYER_STATE;        /*PM display state*/


typedef enum{
    PM_UNIT_MAIN,
    PM_UNIT_APU,
    PM_UNIT_APU_BKP,
    PM_UNIT_APU_SLEEP,
    PM_UNIT_ANT,
    PM_UNIT_TUNER,
    PM_UNIT_DSP,
    PM_UNIT_AUDIO,
    PM_UNIT_AMP,
    PM_UNIT_TFT ,
    PM_UNIT_TFT_VHL,
    PM_UNIT_TFT_EN,
    PM_UNIT_IPOD,
    PM_UNIT_DTV,
    PM_UNIT_RADAR,
    PM_UNIT_XM,
    PM_UINT_DISC,
    PM_UNIT_PHANTTOM,
    PM_UNIT_FAN,
    PM_UNIT_KEY_LED,

    PM_UNIT_ALL,
    PM_UNIT_NUM
}ePM_UNIT;


typedef enum{
    PM_TFTLED_ALL,
    PM_TFTLED_R,
    PM_TFTLED_G,
    PM_TFTLED_B,
    PM_TFTLED_NUM,
    
}ePM_TFT_LED_TYPE;

typedef enum{
   PM_STATE_STEP_0,
   PM_STATE_STEP_1,
   PM_STATE_STEP_2,
   PM_STATE_STEP_3,
   PM_STATE_STEP_4,
   PM_STATE_STEP_5,
   PM_STATE_STEP_6,
   PM_STATE_STEP_7,
   PM_STATE_STEP_8,
   
   PM_STATE_STEP_N
}ePM_STEP;           /*PM Sub state*/

#pragma pack(1)
typedef struct{
    uint16_t iDisplayerEN; /*1/0:standby mode,tft ON / OFF*/
    uint16_t iTftOn;        /*Tft on delay,when set tft on,first set main power on, delay,than set black light on*/
 
    uint16_t iStart;        /*When mcu reset,delay this time than run task*/
    uint16_t iCheck;
    uint16_t iWaitSysPowerStable;
    
}tPM_DELAY_TIME_TAB;

typedef union
{
 	uint8_t  byte1;
	struct
	{
		uint8_t	flag_ill		:1;//ill
		uint8_t	flag_watchtime	:1;//rtc
		uint8_t	flag_acc			:1;//acc
		uint8_t	reserve			:5;
	}bit1;
}Flag_isr;


#pragma pack(1)
typedef union{
    uint8_t byte;
    struct{
        bit_t bLvi         :1;
        bit_t bBatErr      :1;
        bit_t bSysWakeOn       :1;
        bit_t bResValid    :1;
        bit_t bParkValid   :1;
        bit_t bIllValid    :1;
        
    }field;
    
}uPM_IO_FLAG;

#pragma pack(1)
typedef union{
    uint8_t byte;
    struct{
        bit_t  bForceSleep   :1;   //Ç¿ÖÆÐÝÃß»òÕß¹Ø»ú
        bit_t  bPowerOn       :1;   //ÊÇ·ñÉÏµç¿ª»ú,ÉÏµç×Ô¶¯¿ª»ú
        bit_t  bEcnomy       :1;   //Ç¿ÐÐ¿ª»ú
    }field;
}uPM_STATE_FLAG;

typedef enum {
    BAT_STATE_IDLE,
    BAT_STATE_WAIT_ERR,
    BAT_STATE_ERR,
    BAT_STATE_WAIT_RESUME,

    BAT_STATE_NUM
}eBATTERY_STATE;

#pragma pack(1)
typedef struct  power_control_block{
    ePM_MODE                  eMode;
    ePM_DISPLAYER_STATE       eDispLayerState;
    eOP_PM_STATE              eExtReqPmState;


    ePM_BATTERY_LEV           cBatVolIdx;
    eBATTERY_STATE            eBatState;
    uint16_t                  iBatDlyTimer;
    
    uPM_IO_FLAG               uIOFlag;

    uPM_STATE_FLAG            uSetFlag;    
    uint32_t                  iTimer;
    ePM_STEP                  eStep;       
    
    const tPM_DELAY_TIME_TAB* pDlyTab;      
    eOP_PM_AWAKE_EVENT        eAwakeEvt;
    uint8_t                   cOSSecond;

    eOP_DEV_STATE_TYPE        eAPUState;

    eOP_DEV_STATE_TYPE        eEEPState;
    eOP_DEV_STATE_TYPE        eDiscState;

    
}tPM_CTRL_BLOCK;

/*******************************************************************************/
/*** TFT power and Led power ****/
typedef enum{
    PM_TFT_OFF,            /*Tft hold in off state*/
    PM_TFT_DEV_OFF,        /*Set tft main power off in this state*/
    PM_TFT_FB_OFF,         /*Set backup light off*/
    PM_TFT_LED_OFF,        /*Set tft backup led power off*/
    PM_TFT_DEV_ON,         /*Set tft main power on in this state*/
    PM_TFT_FB_ON,          /*Set backup light on*/
    PM_TFT_LED_ON,         /*Set tft backup led power on*/
    PM_TFT_ON,             /*Tft hold in on state*/
    PM_TFT_BLOFF,		/*back light off STATE */
    PM_TFT_STATE_NUM
}ePM_TFT_STATE;               /*TFT Power state */


#pragma pack(1)
typedef struct{
    uint8_t         cBLLevel;
    uint8_t         cLedLev;
    uint8_t         cLedRLev;
    uint8_t         cLedGLev;
    uint8_t         cLedBLev;
}tPM_TFT_DATA;


#pragma pack(1)
typedef struct{
    ePM_TFT_STATE     eState;
    uint16_t           iTimer;
    uint16_t           iEnTimming;    
    
    uint8_t           tCurrPwmLevel;
	uint8_t 		tLastPwmLevel;
	uint8_t	TftTempCloseFlag	:1;
    
}tPM_TFT_CTRL_BLOCK;

_PM_ tPM_TFT_CTRL_BLOCK l_tTftCB;

_PM_  tPM_CTRL_BLOCK l_tPwrCB;


#define _SendMsgToPM(id,sid,buf)       OS_PostMsgDir(&g_tPMTaskCB,(MSG_ID)id,(uint16_t)sid,(void*)(buf))
#define _SendFullMsgToPM(id,sid,b0,b1,b2,b3)       OS_PostFullMsgDir(&g_tPMTaskCB,(MSG_ID)(id),(uint16_t)(sid),(uint8_t)(b0),(uint8_t)(b1),(uint8_t)(b2),(uint8_t)(b3))



_PM_ tTASK_CTRL_BLOCK g_tPMTaskCB;
_PM_ Flag_isr  g_flag_isr;

_PMU_ eOP_PM_AWAKE_EVENT PM_SleepTask(void);
_PMU_ bool PM_UnitPowerSetHook       (ePM_UNIT eUnit, bool bOnOff);
_PMU_ void PM_MsgHandHook            (tMSG_BUF* p_tMsg);
_PMU_ void PM_EnterModeHook          (ePM_MODE eMode);
_PMU_ void PM_ExitModeHook           (ePM_MODE eMode);

_PMU_ void PM_OffSetIO               (void);
_PMU_ void PM_LviSetIO               (void);
_PMU_ void PM_SleepSetIO             (void);


_PMU_ void PM_IoInit                 (void);
_PMU_ uint8_t PM_GetTftBLValue       (void);
_PMU_ void PM_IoRestartScan          (void);

_PM_ void isrPM_LviOccur             (void);
_PM_ bool PM_TaskCreate              (void);
 
_PM_ void PM_UnitPowerSet            (ePM_UNIT eUnit,bool bOnOff);
_PM_ void PM_DisplayerCtrl           (bool bOnOff,uint16_t cEnTimming);
_PM_ void PM_TftPowerSet             (bool bOnOff,uint16_t cEnTimming);
_PM_ void PM_DisplayClose            (void);
_PM_ void PM_CloseBackLight_temp(uint8_t param);


#endif

