/**********************************************************
 * @file        Task_Audio.h
 * @purpose    Definition of Task Audio
 * @version    0.01
 * @date        10. July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        10.July.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TASK_AUDIO_H
#define TASK_AUDIO_H

#ifdef TASK_AUDIO_C
#define EXTERN
#else
#define EXTERN extern
#endif//TASK_AUDIO_C


#include "..\audio\audio_msg.h"
//............................................................................................
//4 Audio Task Related Def : Start

#define D_AUD_MSG_QUE_DEEP        8  

#define _AUD_TASK_TIMING_        _2MS_
#define _AUD_CORE_TIMING_        _10MS_  //Not used in Tuner Task
#define _AUD_TASK_TICK_            _set_timing_xms_base_core_tick(_AUD_TASK_TIMING_)
#define _AUD_CORE_TICK_            _set_timing_xms_base_core_tick(_AUD_CORE_TIMING_)
#define _set_timing_xms_base_aud_task_tick(x)        ((x/_AUD_TASK_TIMING_ - 1))
#define _set_timing_xms_base_aud_core_tick(x)        ((x/_AUD_CORE_TIMING_ - 1))

#define _GetMsgToAudio(Buff)                           OS_GetMsgDir(&g_tAudTaskCB,(tMSG_BUF*)Buff)
#define _SendFullMsgToAudio(gid,sid,d0,d1,d2,d3)     OS_PostFullMsgDir(&g_tAudTaskCB,(uint16_t)(gid),(uint16_t)(sid),(uint8_t)(d0),(uint8_t)(d1),(uint8_t)(d2),(uint8_t)(d3))
#define _SendMsgToAudio(gid,sid,buf)                      OS_PostMsgDir(&g_tAudTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf))
#define _InsertMsgToAudio(gid,sid,buf)                      OS_InsertMsgDir(&g_tAudTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf),0)

//4 Audio Task Related Def : End!
//............................................................................................


//............................................................................................
//4 Audio System Control Step Definitions : Start

#define AUDIO_FUNC_STARTUP     0x00
#define AUDIO_FUNC_IDLE        0x10
#define AUDIO_FUNC_PWROFF        0x20
#define AUDIO_FUNC_SLEEP        0x30

// Startup Steps
typedef enum audio_startup_enum
{
    AUDIO_STARTUP_INIT = AUDIO_FUNC_STARTUP,    //Audio Startup start, Initial specific parameters
    AUDIO_STARTUP_LOAD,
    AUDIO_STARTUP_AMP,            //AMP startup
    AUDIO_STARTUP_ASP,            //ASP startup
    AUDIO_STARTUP_SWITCH,        //matrix switch startup
    AUDIO_STARTUP_END,            //Audio Startup End
}AUDIO_STARTUP_ENUM;

//Power Off Steps
typedef enum audio_pwroff_enum
{
    AUDIO_PWROFF_SORT = AUDIO_FUNC_PWROFF,    // Sort Currently Situation, and Initialize Some Parameters 
    AUDIO_PWROFF_SAVE,            // Save Specific Parameters to EEPROM
    AUDIO_PWROFF_POWER,            // Control Power to Off According Condition
    AUDIO_PWROFF_END,            // End
}AUDIO_PWROFF_ENUM;
//4 Audio System Control Step Definitions : End
//............................................................................................


//--------------------------------------------------------------
//4 Audio Typedef Struct&Enum:Start

// Audio System State
typedef enum audio_system_state_enum
{
    AUDIO_SYS_STARTUP,    // Audio System in INIT State
    AUDIO_SYS_RUN,        // Audio System is Running
    AUDIO_SYS_PWROFF,        // Audio System is Power Off
    AUDIO_SYS_SLEEP,        // Audio System Sleeped!!
}AUDIO_SYSTEM_STATE_ENUM;

//4 Audio Typedef Struct&Enum:Start
//--------------------------------------------------------------



//--------------------------------------------------------------
//4 Audio Self-Definitions:Start

#define AudioSetSysState(x)    sAudio.SysState = (x)
#define AudioGetSysState()    sAudio.SysState

#define AUDIO_TICK_BASE    2
#define AudioDelay(x)        (x)/AUDIO_TICK_BASE

#define AUDIO_READY    BIT0
#define ASP_READY        BIT1
#define AMP_READY        BIT2
#define SWITCH_READY    BIT3

//4 Audio Self-Definitions:End
//--------------------------------------------------------------

EXTERN tTASK_CTRL_BLOCK g_tAudTaskCB;

//--------------------------------------------------------------
//3  Declare :Start

EXTERN void Audio_Func_Startup(void);
EXTERN void Audio_Func_Idle(void);
EXTERN void Audio_Func_PwrOff(void);
EXTERN void Audio_VirTimer(void);
EXTERN void Audio_OutputInfoes(void);
EXTERN void Audio_ColdInit(void);
EXTERN void Audio_WarmInit(void);
EXTERN bool AUD_TaskCreate(void);
EXTERN void Audio_Variable2Eep(void);
EXTERN void Audio_VariableCheck(void);
EXTERN uint8_t Audio_GetVolType(void);
    
//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN

#endif

