#ifndef _MEDIA_H_
#define _MEDIA_H_

#ifndef _MEDIA_C_
#define _MEDIA_ extern
#else
#define _MEDIA_
#endif

#if D_DEBUG_MEDIA && D_PRINT_EN
#define media_printf(x) x
#else
#define media_printf(x)
#endif

#include "..\media\media_msg.h"

typedef enum{
    MEDIA_STATE_START,
    MEDIA_STATE_RUNNING,
    MEDIA_STATE_WAIT_SLEEP,
    MEDIA_STATE_SLEEP,
    MEDIA_STATE_OFF,
    MEDIA_STATE_LVI,

    MEDIA_STATE_UPDATE,		//APU update mode
    MEDIA_STATE_NUM
}eMEDIA_STATE;

typedef enum{
    MEDIA_STATE_STEP_0,
    MEDIA_STATE_STEP_1,
    MEDIA_STATE_STEP_2,
    MEDIA_STATE_STEP_3,
    MEDIA_STATE_STEP_4,
    MEDIA_STATE_STEP_5,
    MEDIA_STATE_STEP_6,
    MEDIA_STATE_STEP_6_0,
    MEDIA_STATE_STEP_6_1,
    MEDIA_STATE_STEP_7,
    MEDIA_STATE_STEP_8,
    MEDIA_STATE_STEP_9,
    MEDIA_STATE_STEP_10,
    MEDIA_STATE_STEP_11,
    MEDIA_STATE_STEP_12,
    MEDIA_STATE_STEP_13,
    MEDIA_STATE_STEP_N
}eMEDIA_STATE_STEP;


#pragma pack(1)
typedef union {
    struct{
        bit_t         bDevConnect    :1;		//when COMM connect
        bit_t         bDevAwake      :1;		// hardware IO port valid
        bit_t         bUnLocked      :1;
        bit_t         bAPUCheckEn  :1;
        bit_t         bUpData        :1;		// software update
        bit_t	   bOSEnter	    :1;
	 bit_t	   bTestMode	    :1;
	 bit_t	   bPowerOn		:1;
    }field;
    uint8_t byte;
}uMEDIA_DEV_FLAG;

typedef struct {
    eMEDIA_STATE       eState;     /*main state*/
    uint8_t            eSubState;  /*Slave state*/
    uint8_t		eSyncState;
    uint8_t		eBakState;	/**/
    uint16_t           iTimer;     /*Device timer*/
    uint8_t            cCnt;       /*Action conter*/
    uint8_t		BspUpdateCnt;/*用于对策上电直接黑屏，同时MCU误进烧录模式的问题2017-01-24*/	
    uint8_t		SecondCnt;	/* 1 s counter */
    uint16_t           cSysTimeSendCnt;	// bolte  用于一个小时给OS发送一次时间/*当没有GPS时，用MCU的时钟*/
    uint8_t     SendTimeCnt; //snake 校准使用
    uint32_t		MediaStartupTimeoutValue;
    eOP_PM_STATE       ePmState;   /*Save the PM state*/
    uMEDIA_DEV_FLAG    uDevFlag;
    uint8_t 		WaitSleepBeforOsReadyFlag	:1; /*在OS_READY 收到前，执行关闭ACC的WAIT_SLEEP模式*/
    uint8_t       TFTStateFlag:    2;	/*同意界面后触摸屏失效后BSP通过IO口通知MCU开关屏*/
    uint8_t       Reserved  :5;
}tMEDIA_CTRL_BLOCK;

typedef struct {
    uint8_t            GpioState;
    uint8_t	      GpioLastState;
    uint8_t            GpioDelayCnt;
    uint8_t 	      tftResetStep;
    uint8_t            tftResetDelay;
}tMEDIA_TFTRESET_BLOCK;

//extern uint8_t FristEolReq;

#define D_MEDIA_MSG_QUE_DEEP   5

#define _MEDIA_TASK_TIMING_    _4MS_
#define _MEDIA_CORE_TIMING_    D_xTICK(1)
#define _MEDIA_TASK_TICK_      _set_timing_xms_base_core_tick(_MEDIA_TASK_TIMING_)
#define _MEDIA_CORE_TICK_      _set_timing_core_tick_num(_MEDIA_CORE_TIMING_)
#define _set_timing_xms_base_media_task_tick(x) ((x/_MEDIA_TASK_TIMING_)-1)

#define _APU_WAIT_PMIC_TIMING			_set_timing_xms_base_media_task_tick(50)
#define _APU_WAIT_UPDATE_TIMING      _set_timing_xms_base_media_task_tick(1000)		//WAIT CPU UPDATE TIMEOUT
#define _APU_WAIT_RESET_TIMING       _set_timing_xms_base_media_task_tick(1000)
#define _APU_WAIT_START_IO_TIMING    _set_timing_xms_base_media_task_tick(6000)
#define _APU_WAIT_SLEEP_CMD_TIMING   _set_timing_xms_base_media_task_tick(6000)
#define _APU_WAIT_SLEEP_IO_TIMING    _set_timing_xms_base_media_task_tick(6000)
#define _APU_WAIT_POWER_OFF_TIMING	_set_timing_xms_base_media_task_tick(3000)
#define _APU_HOLD_OFF_TIMING         _set_timing_xms_base_media_task_tick(200)
/*Power on, wait APU comm time*/
#define _APU_WAIT_START_TIMING    _set_timing_xms_base_media_task_tick(3000)	
#define _APU_WAIT_COMM_TIMING    _set_timing_xms_base_media_task_tick(6000)
#define _APU_HEART_CHK_TIMING    _set_timing_xms_base_media_task_tick(2000)	//Heart check cycle.

#define _TFT12V_RESET_TIME		_set_timing_xms_base_media_task_tick(200)

 #define _set_timing_xms_base_os_tick(x)    (x*1000/250 - 1)
#define  _PMIC_ON_TIME	   	_set_timing_xms_base_os_tick(50)
#define  _APU_RESET_TIME1		_set_timing_xms_base_os_tick(500)
#define  _APU_RESET_TIME2		_set_timing_xms_base_os_tick(400)
#define  _APU_RESET_TIME3		_set_timing_xms_base_os_tick(100)
#define  _APU_WAIT_START1		_set_timing_xms_base_os_tick(1500)
#define  _APU_WAIT_START2		_set_timing_xms_base_os_tick(3000)
#define  _APU_SEND_RVERSE_STATE_TIMEOUT  _set_timing_xms_base_os_tick(1000)
#define  _APU_CUT_OFF_TIME		_set_timing_xms_base_os_tick(500)	// 核心板异常时的断电时间

#define _SendFullMsgToMedia MDI_SendFullMsgToMedia
#define _SendMsgToMedia(gid,sid,buf)  MDI_SendMsgToMedia(gid,sid,(void*)(buf))
#define _InsertMsgToMedia(gid,sid,buf) MDI_InsertMsgToMedia(gid,sid,(void*)(buf))

extern tMEDIA_CTRL_BLOCK   l_tMediaCB;
_MEDIA_ eQUE_ERROR MDI_SendFullMsgToMedia(uint16_t id,uint16_t iSid,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3);
_MEDIA_ eQUE_ERROR MDI_SendMsgToMedia(uint16_t id,uint16_t iSid,uint8_t* p_cBuf);
_MEDIA_ eQUE_ERROR MDI_InsertMsgToMedia(uint16_t id,uint16_t iSid,uint8_t* p_cBuf);
_MEDIA_ void 		MDI_SendUiccToMedia(uint8_t UiccCode, uint8_t Param);

_MEDIA_ bool MDI_TaskCreate(void);
#endif
