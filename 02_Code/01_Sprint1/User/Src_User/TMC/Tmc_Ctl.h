/**********************************************************
 * @file        Tmc_Ctl.h
 * @purpose    Definition of TMC Control
 * @version    0.01
 * @date        22.Aug. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        22.Aug.2013              v0.01        created
 *  
  **********************************************************/
#ifndef TMC_CTL_H
#define TMC_CTL_H

#ifdef TMC_CTL_C
#define EXTERN
#else
#define EXTERN extern
#endif//TMC_CTl_C



#define TMC_MSG_QUE_DEEP        8  

#define _TMC_TASK_TIMING_        _2MS_
#define _TMC_CORE_TIMING_        _10MS_  //Not used Yet in Tuner Task
#define _TMC_TASK_TICK_            _set_timing_xms_base_core_tick(_TMC_TASK_TIMING_)
#define _TMC_CORE_TICK_            _set_timing_xms_base_core_tick(_TMC_CORE_TIMING_)

#define _SendFullMsgToTmc(gid,sid,d0,d1,d2,d3)     OS_PostFullMsgDir(&g_tTmcTaskCB,(uint16_t)(gid),(uint16_t)(sid),(uint8_t)(d0),(uint8_t)(d1),(uint8_t)(d2),(uint8_t)(d3))
#define _SendMsgToTmc(gid,sid,buf)                      OS_PostMsgDir(&g_tTmcTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf))
#define _InsertMsgToVTmc(gid,sid,buf)                      OS_InsertMsgDir(&g_tTmcTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf),0)


//-----------------------------------------------------
//4 Control Steps Enum: Start



#define TMC_FUNC_STARTUP     0x00
#define TMC_FUNC_RUN        0x10
#define TMC_FUNC_PWROFF     0x20

// Startup Steps
typedef enum tmc_startup_enum
{
    TMC_STARTUP_POWER = TMC_FUNC_STARTUP,    // Open Power Supply
    TMC_STARTUP_RESET,        // Reset Module
    TMC_STARTUP_REGISTER,        // Initialize Registers
    TMC_STARTUP_END,            // Startup End
}TMC_STARTUP_ENUM;

// Running Steps
typedef enum tmc_run_enum
{
    TMC_RUN_SET_FREQ = TMC_FUNC_RUN,    // Set/Change Frequency
    TMC_RUN_CHK_RDS,        // Check Rds
    TMC_RUN_GET_TMC,        // Get TMC Info
}TMC_RUN_ENUM;

//4 Control Steps Enum: End
//-----------------------------------------------------



typedef struct tmc_struct
{
    uint8_t SysState;
    uint8_t FuncStep;
    uint8_t FuncDelay;

}TMC_STRUCT;

// System State
typedef enum tmc_system_state_enum
{
    TMC_SYS_STARTUP = 0,    //  System in INIT State
    TMC_SYS_RUN,            //  System is Running
    TMC_SYS_PWROFF,        //  System is Power Off
    TMC_SYS_SLEEP,        //  System Sleeped!!
}TMC_SYSTEM_STATE_ENUM;


EXTERN tTASK_CTRL_BLOCK g_tTmcTaskCB;
EXTERN TMC_STRUCT sTmc;


#define TmcSetSysState(x)    sTmc.SysState = (x)
#define TmcGetSysState()    sTmc.SysState


#endif//TMC_CTL_H

