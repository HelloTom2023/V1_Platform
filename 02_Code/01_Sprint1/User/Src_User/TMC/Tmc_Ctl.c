/**********************************************************
 * @file        Tmc_Ctl.c
 * @purpose    TMC Control Functions
 * @version    0.01
 * @date        22. Aug. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          22.Aug.2013        v0.01        created                                                                        
  **********************************************************/
#define TMC_CTL_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= Function Announcement  =================== */
void Tmc_Startup(void);
void Tmc_Running(void);
void Tmc_PwrOff(void);
/* ========================= public variable ==================== */


/* ========================= private variable =================== */
// Main Function Array
void (*const Tab_TmcFunc[])(void) = 
{
    Tmc_Startup,
    Tmc_Running,
    Tmc_PwrOff,
};

/* ========================= Code Part =================== */

/**********************************************************
 * @function    Tmc_OpenPower
 * @brief      Open TMC's Power
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tmc_OpenPower(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Tmc_Reset
 * @brief      Reset TMC Module
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Tmc_Reset(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Tmc_Register
 * @brief      Initialize Register
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Tmc_Register(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Tef700x_InitReg();
        
    return (Result);
}
/**********************************************************
 * @function    Tmc_SetFreq
 * @brief      
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Tmc_SetFreq(uint16_t Val)
{
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Tef700x_SetFreq(Val);
        
    return (Result);
}
/**********************************************************
 * @function    Tmc_Startup
 * @brief      Startup TMC ...
 * @param      None                
 * @retval     Result
 **********************************************************/
void Tmc_Startup(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
    switch(sTmc.FuncStep)
    {
        case TMC_STARTUP_POWER:
            if(sAudio.ReadyState | AUDIO_READY)  //DSP ready , DSP Supply Clock 
            {
                sTmc.FuncStep = TMC_STARTUP_RESET;
            }
            break;

        case TMC_STARTUP_RESET:
            sTmc.FuncStep = TMC_STARTUP_REGISTER;
            break;

        //Initial Register
        case TMC_STARTUP_REGISTER:
            Result = Tmc_Register();
            if(SUBLAYER_DONE == Result)
            {
                sTmc.FuncStep = TMC_FUNC_RUN;
            }
            break;
    }
}
/**********************************************************
 * @function    Tmc_Running
 * @brief      Running of  TMC ...
 * @param      None                
 * @retval     Result
 **********************************************************/
void Tmc_Running(void)
{
    uint8_t Result = SUBLAYER_DOING;

    switch(sTmc.FuncStep)
    {
        case TMC_RUN_SET_FREQ:
            Result = Tmc_SetFreq(8750);
            if(SUBLAYER_DONE == Result)
            {
                sTmc.FuncStep = TMC_RUN_CHK_RDS;
            }
            break;

        case TMC_RUN_CHK_RDS:
            Result = Tef700x_ReadCommon(6);
            //sTmc.FuncStep = TMC_RUN_GET_TMC;
            if(SUBLAYER_DONE == Result)
            {
                sTmc.FuncStep = TMC_RUN_GET_TMC;
            }
            break;

        case TMC_RUN_GET_TMC:
            //sTmc.FuncStep = TMC_RUN_SET_FREQ;
            break;
    }
}
/**********************************************************
 * @function    Tmc_PwrOff
 * @brief      
 * @param      None                
 * @retval     Result
 **********************************************************/
void Tmc_PwrOff(void)
{
}
/**********************************************************
 * @function    Tmc_Manager
 * @brief      
 * @param      None
 * @retval     None
 **********************************************************/
void Tmc_Manager(void)
{
    // Execute Video Functions while Task Not Sleep
    if(TMC_SYS_SLEEP != TmcGetSysState())
    {
        //Main Function Control
        (*Tab_TmcFunc[((sTmc.FuncStep >> 4) & 0x0F)])();    
    }
}
/**********************************************************
 * @function    Tmc_MsgHandler
 * @brief      Dispose Messages received
 * @param      tMSG_BUF* Msg
 * @retval     None
 **********************************************************/
void Tmc_MsgHandler(tMSG_BUF* pMsg)
{
    #define MsgId     pMsg->Id
    #define MsgSid     pMsg->iSid

    switch(MsgId)  
    {
        //4Power Manager Related Message
        case MS_PM_STATE:
            switch(MsgSid)
            {
                case OP_PM_STATE_ON:
                case OP_PM_STATE_STANDBY:
                    //Goto Set System On
                    if(TMC_SYS_RUN != TmcGetSysState())
                    {
                        TmcSetSysState(TMC_SYS_STARTUP);
                        sTmc.FuncStep = TMC_FUNC_STARTUP;
                    }
                    break;
                    
                case OP_PM_STATE_WAIT_SLEEP:
                    break;
                    
               
                default:
                    //Goto Shut Off Tuner and Close Power 
                    if(TmcGetSysState() <= VIDEO_SYS_PWROFF)
                    {
                        TmcSetSysState(TMC_SYS_PWROFF);
                        sTmc.FuncStep = TMC_FUNC_PWROFF;
                    }
                    break;

                
            }
            break;
            
        //4Video Related Message
        
    }
    
    #undef MsgId
    #undef MsgSid   
}
 /**********************************************************
 * @function    Tmc_Task
 * @brief      a periodic task for Video module
 * @param      EVENT Evt
 *                 eTASK_STATE eState
 * @retval     None
 **********************************************************/
void Tmc_Task(EVENT Evt,eTASK_STATE eState)
{
    if(Evt & EVT_COLD_INIT)    //Cold Start, Reset Parameters
    {
        sTmc.FuncStep = TMC_FUNC_STARTUP;
        TmcSetSysState(TMC_SYS_SLEEP);

        //OS_TaskStart(TASK_ID_TMC); // Start Video Task
    }

    if(Evt & EVT_WARM_INIT)    //Warm Start, Initialize Parameters
    {
        sTmc.FuncStep = TMC_FUNC_STARTUP;
        TmcSetSysState(TMC_SYS_SLEEP);

        //OS_TaskStart(TASK_ID_TMC); // Start Video Task
    }

    if(Evt & EVT_MSG_READY)
    {
        tMSG_BUF tMsg;
        if(QUE_ERR_NONE == OS_GetMsgDir(&g_tTmcTaskCB,&tMsg))
        {
            Tmc_MsgHandler(&tMsg);
        }
    }
    
    if(Evt & EVT_TASK_TICK_READY)
    {
        //Video Main Control
        Tmc_Manager();
    }
    
    switch(eState)
    {
        case TASK_STATE_READY:

            break;

        case TASK_STATE_RUNNING:

            break;

        case TASK_STATE_STOP:

            break;    
    }
}




static const tTASK_BLOCK l_tTmcTCB = {
    "TMC",
    _TMC_TASK_TICK_,
    _TMC_CORE_TICK_,
    Tmc_Task,
    NULL,
    NULL,
//    NULL,
};

tRING_QUE l_tTmcMsgQue;
tMSG_BUF la_tTmcMsgBuf[ VIDEO_MSG_QUE_DEEP];

bool Tmc_TaskCreate(void)
{
    return OS_TaskCreate(TASK_ID_TMC,&g_tTmcTaskCB,&l_tTmcTCB,&l_tTmcMsgQue,la_tTmcMsgBuf,VIDEO_MSG_QUE_DEEP);
}



