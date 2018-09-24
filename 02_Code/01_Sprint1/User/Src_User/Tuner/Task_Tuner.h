/**********************************************************
 * @file        Task_Tuner.h
 * @purpose    Definition of Task Tuner
 * @version    0.01
 * @date        27. June. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        27.June.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TASK_TUNER_H
#define TASK_TUNER_H


#ifdef TASK_TUNER_C
#define EXTERN
#else
#define EXTERN extern
#endif//TASK_TUNER_C

#if D_DEBUG_RADIO && D_PRINT_EN
#define Tuner_debug(x)  			x
#else
#define Tuner_debug(x) 
#endif


#include "..\tuner\tuner_msg.h"
//............................................................................................
//4 Tuner Task Related Def : Start

#define D_TUNER_MSG_QUE_DEEP        8  

#define _TUNER_TASK_TIMING_        _2MS_
#define _TUNER_CORE_TIMING_        _10MS_  //Not used Yet in Tuner Task
#define _TUNER_TASK_TICK_            _set_timing_xms_base_core_tick(_TUNER_TASK_TIMING_)
#define _TUNER_CORE_TICK_            _set_timing_xms_base_core_tick(_TUNER_CORE_TIMING_)

#define _GetMsgToTuner(Buff)                           OS_GetMsg(TASK_ID_TUNER,(tMSG_BUF*)Buff)
#define _SendFullMsgToTuner(gid,sid,d0,d1,d2,d3)     OS_PostFullMsg(TASK_ID_TUNER,(uint16_t)(gid),(uint16_t)(sid),(uint8_t)(d0),(uint8_t)(d1),(uint8_t)(d2),(uint8_t)(d3))
#define _SendMsgToTuner(gid,sid,buf)                      OS_PostMsg(TASK_ID_TUNER,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf))
#define _InsertMsgToTuner(gid,sid,buf)                      OS_InsertMsg(TASK_ID_TUNER,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf),0)

//4 Tuner Task Related Def : End!
//............................................................................................


//............................................................................................
//4 Tuner Control Step Definitions : Start

// Function Control Step
#define TUNER_FUNC_STARTUP     0x00     
#define TUNER_FUNC_IDLE        0x10    
#define TUNER_FUNC_SEEK        0x20
#define TUNER_FUNC_PSCAN        0x30
#define TUNER_FUNC_PWROFF        0x40

// Startup Steps
typedef enum tuner_startup_enum
{
    TUNER_STARTUP_PWRON = TUNER_FUNC_STARTUP,    // Open Power Supply
    TUNER_STARTUP_RESET,        // Reset Tuner Module
    TUNER_STARTUP_LOAD,     //Load Datum...from eeprom
    TUNER_STARTUP_INIT,        // Initialize Tuner's Boot Registers
    TUNER_STARTUP_RESUME,    // Resume Last: Band and Frequency 
    TUNER_STARTUP_END,        // Power On End, Goto IDLE State, Waiting For New Operations
}TUNER_STARTUP_ENUM;

// Idle Steps
typedef enum tuner_idle_enum
{
    TUNER_IDLE_END = TUNER_FUNC_IDLE,
}TUNER_IDLE_ENUM;

// Commonly Operation Steps
typedef enum tuner_operate_enum
{
    TUNER_OPERATE_BREAK = 0,//TUNER_FUNC_OPERATE,    // Break : Break AF, Break Last state
    TUNER_OPERATE_LOGIC ,        //Dispose incoming operation's logic
    TUNER_OPERATE_SWITCH,     //Switch to the Rightly State to execute incoming operation
    TUNER_OPERATE_MUTE,        // Mute before Set(Set Band, Set Frequency)
    TUNER_OPERATE_SET,        // Set Band Or Set Frequency
    TUNER_OPERATE_UNMUTE,    // Release Mute
    TUNER_OPERATE_END,        // Operation End
}TUNER_OPERATE_ENUM;

// Seek Steps
typedef enum tuner_seek_enum
{
    TUNER_SEEK_MUTE = TUNER_FUNC_SEEK,    // Mute first
    TUNER_SEEK_CONFIG    ,        // Config: Set Seek Mode , Set Specific Parameters
    TUNER_SEEK_FIRST,            // Check First frequency ,specially for AMS use
    TUNER_SEEK_NEXT,            // Change the Frequency to Next
    TUNER_SEEK_CHK_QUAL,        // Check Quality
    TUNER_SEEK_CHK_RDS,        // Check Specific Rds State
    TUNER_SEEK_GOOD,            // Got A Good Station, Do What Need
    TUNER_SEEK_PREVIEW,        // Preview Seeked Good Station, include preview exit
    TUNER_SEEK_AMS_SAVE,        // Save Stations for Auto Memory Scan 
    TUNER_SEEK_EXIT,            // Seek End, Exit Seek Mode    
    TUNER_SEEK_UNMUTE,        // Seek End, Release Mute ,Unmute 
    TUNER_SEEK_END,            // Seek End
}TUNER_SEEK_ENUM;

// Preset Scan Steps
typedef enum tuner_psan_enum
{
    TUNER_PSCAN_START = TUNER_FUNC_PSCAN,    // start, do some config
    TUNER_PSCAN_NEXT,        // ps next preset
    TUNER_PSCAN_CHECK,    // check ps state, whether ends.
    TUNER_PSCAN_END,        // ps ends!
}TUNER_PSCAN_ENUM;

// Tuner Power Off Steps
typedef enum tuner_pwroff_enum
{
    TUNER_PWROFF_SORT = TUNER_FUNC_PWROFF,    // Sort Currently Situation, and Initialize Some Parameters 
    TUNER_PWROFF_SAVE,            // Save Specific Parameters to EEPROM
    TUNER_PWROFF_POWER,            // Control Power to Off According Condition
    TUNER_PWROFF_END,            // End
}TUNER_PWROFF_ENUM;

// Valid Scan Steps
typedef enum tuner_vscan_step_enum
{
    TUNER_VSCAN_INIT = 0,        //Initialize before Scan
    TUNER_VSCAN_RESUME,    // Resume Scan Frequency... 
    TUNER_VSCAN_END,            // End!
}TUNER_VSCAN_STEP_ENUM;

//Tuner Operation Dispose Step
typedef enum t_operation_ctl_enum
{
    T_OP_CTL_IDLE = 0,        //Idle State, wait for newly requirement input
    T_OP_CTL_BREAK,
    T_OP_CTL_MUTE,
    T_OP_CTL_EXECUTE,        //Execute Newly Operation
    T_OP_CTL_DEMUTE,
    T_OP_CTL_END,            //Executed!
}T_OP_CTL_ENUM;


//4Tuner Control Step Definitions : End
//............................................................................................



//--------------------------------------------------------------
//3 Tuner Self-Definitions:Start

#define TUNER_CURRENT_BAND    sTunerDat.sInfo.CurrentBand
#define TUNER_BAND_FM ((TUNER_CURRENT_BAND >= TUNER_FM_START) && (TUNER_CURRENT_BAND <= TUNER_FM_END))
#define TUNER_BAND_AM ((TUNER_CURRENT_BAND >= TUNER_AM_START) && (TUNER_CURRENT_BAND <= TUNER_AM_END))
#define TUNER_BAND_OIRT ((TUNER_CURRENT_BAND >= TUNER_OIRT_START) && (TUNER_CURRENT_BAND <= TUNER_OIRT_END))

#define TUNER_CURRENT_PRESET    sTunerDat.sInfo.CurrentPreset
#define TUNER_CURRENT_FREQ    sTunerDat.sInfo.CurrentFreq

#define TunerSetSysState(x)    sTuner.SysState = (x)
#define TunerGetSysState()    sTuner.SysState

#define TunerDelay(x)        (x)/2
#define TunerSetDelay(x,y)        (x) = (y)
#define TunerSetOverTime(x,y)        (x) = (y)

#define TunerRdsSettingOn()        (TaSetting || AfSetting || sTuner.uSeekState.sSsBitMap.bPTYSeek)

//3 Tuner Self-Definitions:End
//--------------------------------------------------------------


//--------------------------------------------------------------
//3  Declare :Start

EXTERN void Tuner_VirTimer(void);
EXTERN eSOURCE_MSG_RETURN Tuner_MsgHandler(eSOURCE_TYPE eType,eSOURCE_ZONE eZone,tMSG_BUF* pMsg,bool bSrcActive);
EXTERN void Tuner_ColdInit(void);
EXTERN void Tuner_WarmInit(void); 
EXTERN void Tuner_Active(eSOURCE_TYPE eType,eSOURCE_ZONE sZone);
EXTERN void Tuner_Deactive(eSOURCE_TYPE eType,eSOURCE_ZONE sZone);
EXTERN void Tuner_CreateSrc(void);
EXTERN void Tuner_Task(eSOURCE_TYPE eType,EVENT Evt, eTASK_STATE eState);

//3 Declare :End
//--------------------------------------------------------------

#undef EXTERN

#endif//TASK_TUNER_H

