#ifndef _SRC_H_
#define _SRC_H_

#ifdef _SRC_C_
#define _SRC_
#else
#define _SRC_ extern
#endif

#if D_DEBUG_SOURCE && D_PRINT_EN
#define src_printf(x) x
#else
#define src_printf(x)
#endif

#if D_DEBUG_Camera&& D_PRINT_EN
#define Camera_printf(x) x
#else
#define Camera_printf(x)
#endif
#define D_UPDATA_RUNTIME_SRC  1 /*if runtime source is changed ,updata source id to cpu when ever */


#define D_SRC_MSG_QUE_DEEP   20

#define _SRC_TASK_TIMING_    _2MS_
#define _SRC_CORE_TIMING_    _2MS_
#define _SRC_TASK_TICK_      _set_timing_xms_base_core_tick(_SRC_TASK_TIMING_)
#define _SRC_CORE_TICK_      _set_timing_core_tick_num(_SRC_CORE_TIMING_)
#define _set_timing_xms_base_src_task_tick(x) ((x/_SRC_TASK_TIMING_)-1)







typedef enum{
    SRCSYS_INIT,
    SRCSYS_WAIT_START,
    SRCSYS_RUNNING,
    SRCSYS_SLEEP,

    SRCSYS_NUM
}eSOURCE_SYS_STATE;

typedef enum{
    SRCSW_STATE_IDLE,
    SRCSW_STATE_MUTE_AUDIO,
    SRCSW_STATE_UPLOAD_DATA,
    SRCSW_STATE_MUTE_VIDEO,
    SRCSW_STATE_END,
    
}eSOURCE_SWITCH_STATE;

typedef struct
{
	eSOURCE_ID NaviSource;
	eSOURCE_ID MediaSource;
}MEM_SOURCE;

extern MEM_SOURCE    SysMemSource;

#define _SendMsgToSRC(id,op,buf)             OS_PostMsgDir(&g_tSysSrcTaskCB,(MSG_ID)id, (uint16_t)op,(void *) buf)
#define _SendFullMsgToSRC(id,op,d0,d1,d2,d3) OS_PostFullMsgDir(&g_tSysSrcTaskCB,(MSG_ID)id, (uint16_t)op, (uint8_t)d0, (uint8_t)d1, (uint8_t)d2, (uint8_t)d3)
#define _InsertMsgToSRC(id,op,buf)           OS_InsertMsgDir(&g_tSysSrcTaskCB,(MSG_ID)id, (uint16_t)op,(void *) buf,0)
 

_SRC_ tTASK_CTRL_BLOCK g_tSysSrcTaskCB;


_SRC_ uint8_t    SRC_TaskCreate             (void);
#endif



