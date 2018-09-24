/**********************************************************
 * @file        Task_Video.h
 * @purpose    Definition of Task Video
 * @version    0.01
 * @date        23.Oct. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        23.Oct.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TASK_VIDEO_H
#define TASK_VIDEO_H

#ifdef TASK_VIDEO_C
#define EXTERN
#else
#define EXTERN extern
#endif//TASK_VIDEO_C


//-----------------------------------------------------
//4 Control Steps Enum: Start

//Main Control Steps
#define VIDEO_FUNC_STARTUP     0x00
#define VIDEO_FUNC_IDLE        0x10
#define VIDEO_FUNC_PWROFF        0x20
#define VIDEO_FUNC_SLEEP        0x30

// Startup Steps
typedef enum video_startup_enum
{
    VIDEO_STARTUP_INIT = VIDEO_FUNC_STARTUP,    //Video Startup start, Initial specific parameters
    VIDEO_STARTUP_LOAD, //Load Datum
    VIDEO_ADI7186_RST1,
    VIDEO_ADI7186_RST2,
    VIDEO_ADI7186_RST3,
    VIDEO_STARTUP_SWITCH1,        //matrix switch startup: AK4220
    VIDEO_STARTUP_SWITCH2,        //matrix switch startup: Fms6501
    VIDEO_STARTUP_VSP,            //Video Signal Process IC Startup
    VIDEO_STARTUP_END,            //Video Startup End
}VIDEO_STARTUP_ENUM;

//Power Off Steps
typedef enum video_pwroff_enum
{
    VIDEO_PWROFF_SORT = VIDEO_FUNC_PWROFF,    // Sort Currently Situation, and Initialize Some Parameters 
    VIDEO_PWROFF_SAVE,            // Save Specific Parameters to EEPROM
    VIDEO_PWROFF_POWER,            // Control Power to Off According Condition
    VIDEO_PWROFF_END,            // End
}VIDEO_PWROFF_ENUM;

//Vch Switch Control Steps
typedef enum vch_switch_enum
{
    VCH_SWITCH_IDLE = 0,        //Idle State: Check Whether A newly VCH Switch Req is ready
    VCH_SWITCH_SWITCH1,        //Switch the Switch Channel: Ak4220 
    VCH_SWITCH_SWITCH2,        //Switch the Switch Channel: Fms6501 
    VCH_SWITCH_VSP,            //Switch the Vsp Channel 
    VCH_SWITCH_END,            // Vch Switch End
}VCH_SWITCH_ENUM;

//4 Control Steps Enum: End
//-----------------------------------------------------


//-----------------------------------------------------
//3 Video Related Def&Struct:Start

#define VD_NO_VIDEO    0
#define VD_HAVE_VIDEO    1
#define VD_DETING        2    //Video Detecting

#define VCH_BUFFER_MAX  6 // 3

//VCH Requirement Structure
typedef struct vch_req_buffer
{
    uint8_t Req;        //Required Ach
    uint8_t Type;        //Required Type
}VCH_BUFFER_STRUCT;

// Video Parameter Struct
typedef struct video_struct
{
    uint8_t PwrState;
    uint8_t SysState;        //Video Task State
    uint8_t ReadyState;  //B0: Video all Ready bit

    uint8_t FuncStep;    //Control Step

    uint8_t SysVch;    //Currently Front System Video Channel
    uint8_t RearVch;    //Currently Rear System Video Channel

    //4 Video Channel
    uint8_t VchCtl;    //Switch Audio Channel Control
    uint16_t VchDelay;
    uint8_t VchSwitchEn;
    uint8_t VchHead;
    uint8_t VchTail;
    VCH_BUFFER_STRUCT ReqVch[VCH_BUFFER_MAX];    //Newly Required Ach
	uint8_t CurrentVideoSourceId;
	
    uint16_t VdDelay;    //Video Detect Delay
    uint8_t DetFlag;    //Video Det State, 0: No Video, 1: Have Video
}VIDEO_STRUCT;

// Video System State
typedef enum video_system_state_enum
{
    VIDEO_SYS_STARTUP = 0,    // Video System in INIT State
    VIDEO_SYS_RUN,            // Video System is Running
    VIDEO_SYS_PWROFF,        // Video System is Power Off
    VIDEO_SYS_SLEEP,        // Video System Sleeped!!
}VIDEO_SYSTEM_STATE_ENUM;

//3 Video Related Def&Struct:End
//-----------------------------------------------------

#define VIDEO_TICK_BASE    2
#define VideoDelay(x)        (x)/VIDEO_TICK_BASE

#define VideoSetSysState(x)    sVideo.SysState = (x)
#define VideoGetSysState()    sVideo.SysState

#ifdef D_VIDEO_SWITCH_TW8836
#define Video_ModuleInit()        Tw8836_InitVariable()
#define Video_Switch1Startup()        Tw8836_Regsiter()
#elif defined(D_VIDEO_SWITCH_FMS6501)
#define Video_Switch1Startup()        Fms6501_Regsiter()
#else
#define Video_Switch1Startup()        SUBLAYER_DONE
#endif

#ifdef D_VIDEO_SWITCH_NJM2246
#define Video_Switch2Startup()        SUBLAYER_DONE
#else
#define Video_Switch2Startup()        SUBLAYER_DONE
#endif

#define Video_VspStartup()        SUBLAYER_DONE

#ifdef D_VIDEO_SWITCH_NJM2246
#define Video_ChangeSwitch1Vch(x,y)    Njm2246_SwitchVch((x),(y))
#else
#define Video_ChangeSwitch1Vch(x,y)    SUBLAYER_DONE
#endif

#ifdef D_VIDEO_SWITCH_FMS6501
#define Video_ChangeSwitch2Vch(x,y)    Fms6501_SwitchVch((x),(y))    
#elif defined(D_VIDEO_SWITCH_TW8836)
#define Video_ChangeSwitch2Vch(x,y)    Tw8836_SwitchVch((x),(y))    
#else
#define Video_ChangeSwitch2Vch(x,y) SUBLAYER_DONE
#endif//D_VIDEO_SWITCH_FMS6501

#ifdef D_VIDEO_SWITCH_TW8836
#define Video_LvdsOutEnable()    TW8836_SetLvdsTxEnable()
#endif//D_VIDEO_SWITCH_FMS6501


#define Video_CheckVideo()   VD_NO_VIDEO



#define VIDEO_MSG_QUE_DEEP        8  

#define _VID_TASK_TIMING_        _2MS_
#define _VID_CORE_TIMING_        _10MS_  //Not used Yet in Tuner Task
#define _VID_TASK_TICK_            _set_timing_xms_base_core_tick(_VID_TASK_TIMING_)
#define _VID_CORE_TICK_            _set_timing_xms_base_core_tick(_VID_CORE_TIMING_)

#define _SendFullMsgToVideo(gid,sid,d0,d1,d2,d3)     OS_PostFullMsgDir(&g_tVidTaskCB,(uint16_t)(gid),(uint16_t)(sid),(uint8_t)(d0),(uint8_t)(d1),(uint8_t)(d2),(uint8_t)(d3))
#define _SendMsgToVideo(gid,sid,buf)                      OS_PostMsgDir(&g_tVidTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf))
#define _InsertMsgToVideo(gid,sid,buf)                      OS_InsertMsgDir(&g_tVidTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf),0)

//--------------------------------------------------------------
//3  Declare :Start
EXTERN tTASK_CTRL_BLOCK g_tVidTaskCB;

EXTERN VIDEO_STRUCT sVideo;

EXTERN  void Video_VariableInit(void);
EXTERN void Video_VchQueueIn(uint8_t Req, uint8_t Type);
EXTERN bool VID_TaskCreate(void);
EXTERN void Video_SetChannel(eSOURCE_ZONE eZone,const tSOURCE* tSrc,uint8_t VidPri);

//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN

#if D_DEBUG_VIDEO&& D_PRINT_EN
#define video_printf(x)  x
#else
#define video_printf(x)
#endif

#endif//TASK_VIDEO_H

