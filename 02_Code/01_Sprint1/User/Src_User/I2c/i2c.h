#ifndef _I2C_H_
#define _I2C_H_

#include "SoftI2c.h"


#ifndef _I2C_C_
#define _I2C_  extern
#else
#define _I2C_
#endif

#if D_DEBUG_I2C && D_PRINT_EN
#define i2c_printf(x) x
#else
#define i2c_printf(x)
#endif


#define _I2C_TASK_TIMING_                   _4MS_
#define _I2C_CORE_TIMING_                   _1MS_
#define _I2C_TASK_TICK_                     _set_timing_xms_base_core_tick(_I2C_TASK_TIMING_)
#define _I2C_CORE_TICK_                     _set_timing_xms_base_core_tick(_I2C_CORE_TIMING_)
#define _set_timing_xms_base_i2c_tick(x)        ((x/_I2C_TASK_TIMING_ - 1))
#define _set_timing_xms_base_i2c_core_tick(x)   ((x/_I2C_CORE_TIMING_ - 1))

//#define I2C0_EN

typedef enum{
    I2C_STATE_OFF,
    I2C_STATE_IDLE,
    I2C_STATE_WAIT_TRANSE,
    
    I2C_STATE_WAIT_STOP,
    I2C_STATE_CALL_BACK,
    I2C_STATE_RESET,
    I2C_STATE_REPEAT_START,
    I2C_STATE_WAIT_RESUME,
    I2C_STATE_NUM
}eI2C_STATE;



#pragma pack(1)
typedef struct{
    eQUE_ERROR      eState;
    uint8_t         cHead;
    uint8_t         cTail;
    uint8_t         cMax;
    tI2C_CMD_BLOCK* p_tCmd;
}tI2C_CMD_QUE;

#pragma pack(1)
typedef struct {
    eI2C_STATE      eState;
    uint8_t         cByteCnt;
    uint8_t         cTimer;

    tRING_QUE       tCmdQue;
    uint8_t         cCmdCnt;

    eI2C_ERROR      eErr;
}tI2C_CTRL_BLOCK;


_I2C_ tTASK_CTRL_BLOCK g_tI2C0TaskCB;
_I2C_ tTASK_CTRL_BLOCK g_tI2C1TaskCB;
_I2C_ tTASK_CTRL_BLOCK g_tI2C2TaskCB;

_I2C_ tI2C_CTRL_BLOCK* I2C_GetCtrlBlock(eI2C_TYPE n);

//_I2C_ bool I2C_Ch1TaskCreate(void);
_I2C_ bool I2C_Ch1TaskStart(void);

//_I2C_ bool I2C_Ch2TaskCreate(void);
_I2C_ bool I2C_Ch2TaskStart(void);
_I2C_ eI2C_ERROR I2C_GetLastErr(eI2C_TYPE eType);

_I2C_ void I2C_TaskCreate(void);


_I2C_ uint8_t I2C_CheckDevice    (eI2C_TYPE ,uint8_t ,bool ,void* ,eI2C_SPEED);
_I2C_ uint8_t I2C_Read           (eI2C_TYPE ,uint8_t ,bool ,uint8_t* ,uint8_t ,bool ,void* ,eI2C_SPEED);
_I2C_ uint8_t I2C_Write          (eI2C_TYPE ,uint8_t ,bool ,uint8_t* ,uint8_t ,bool ,void* ,eI2C_SPEED);
_I2C_ uint8_t I2C_ReadFromSubAdd (eI2C_TYPE ,uint8_t ,uint8_t ,bool ,uint8_t* ,uint8_t ,bool ,void* ,eI2C_SPEED);
_I2C_ uint8_t I2C_WriteToSubAdd  (eI2C_TYPE ,uint8_t ,uint8_t ,bool ,uint8_t* ,uint8_t ,bool ,void* ,eI2C_SPEED);    

#endif

