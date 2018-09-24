/**********************************************************
 * @file        Tuner_SubModule.c
 * @purpose    SubTuner Function
 * @version    0.01
 * @date        16.July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          16.July.2012        v0.01        created
 *  
  **********************************************************/
#define TUNER_SUBMODULE_C
/* ========================= File include ======================= */

/* ========================= Function Announcement  =================== */

/* ========================= public variable ==================== */


/* ========================= private variable =================== */

/* ========================= Code Part =================== */

/**********************************************************
 * @function    SubTuner_Func_Startup
 * @brief      Sub-Tuner Startup: Power on, Reset, Initialize registers,
 *            Resume Last State
 * @param      None                    
 * @retval     None
 **********************************************************/
void SubTuner_Func_Startup(void)
{
    uint8_t Result = TUNER_SUBLAYER_DOING;

    if(TunerDelayNotExpired(sTuner.SubFuncDelay))
        return;
    
    switch(sTuner.SubFuncStep)
    {
        // Tuner Module Power On and Related Parameter Initialize
        case SUBTUNER_STARTUP_PWRON:    
            Result = Si475x_PwrOn();
            if(TUNER_SUBLAYER_DONE == Result)
            {
                SubTuner_GotoStep(SUBTUNER_STARTUP_RESET);
            }
            break;
            
        // Reset Tuner Module
        case SUBTUNER_STARTUP_RESET:    
            Result = Si475x_Reset();
            if(TUNER_SUBLAYER_DONE == Result)
            {
                SubTuner_GotoStep(SUBTUNER_STARTUP_INIT);
            }
            break;
            
        // Initialize Tuner Module, Load Boot Datum to  Registers    
        case SUBTUNER_STARTUP_INIT:        
            Result = Si475x_InitRegister();
            if(TUNER_SUBLAYER_DONE == Result)
            {
                SubTuner_GotoStep(SUBTUNER_STARTUP_RESUME);
            }
            break;
            
        // Resume Last State: Resume Band, Resume Freq    
        case SUBTUNER_STARTUP_RESUME:    
            Result = Si475x_ResumeLast();
            if(TUNER_SUBLAYER_DONE == Result)
            {
                SubTuner_GotoStep(TUNER_STARTUP_END);
            }
            break;

        // Startup Ends, Goto IDLE State
        case SUBTUNER_STARTUP_END:        
            SubTuner_GotoStep(SUBTUNER_FUNC_IDLE);
            break;    
    
        default:
            Result = TUNER_SUBLAYER_ERROR;
            break;
    }

    // Step Error Disposal
    if(TUNER_SUBLAYER_ERROR == Result)        
    {
        SubTuner_Func_Error();
    }
}
/**********************************************************
 * @function    Tuner_Func_Idle
 * @brief      Tuner Stay in Idle State
 *                 Waiting for Incoming Operation
 * @param      None                    
 * @retval     None
 **********************************************************/
void SubTuner_Func_Idle(void)
{
    uint8_t Result = TUNER_SUBLAYER_DOING;

    if(TunerDelayNotExpired(sTuner.SubFuncDelay))
        return;

    // Goto Get a New Valid Station List per 1 minutes
    SubTuner_GotoStep(SUBTUNER_FUNC_VALIDSEEK);
}
/**********************************************************
 * @function    SubTuner_Func_ValidSeek
 * @brief      Do Valid Frequency List Seeking 
 *                 In Background via Sub-Tuner
 * @param      None                    
 * @retval     None
 **********************************************************/
void SubTuner_Func_ValidSeek(void)
{
    uint8_t Result = TUNER_SUBLAYER_DOING;
    TUNER_AMS_MEM_STRUCT asNewStation;
    
    if(!(TimerHasExpired(sTuner.SubFuncDelay)))
        return;

    switch(sTuner.SubFuncStep)
    {
        case SUBTUNER_VS_CONFIG:
            Result = Si475x_ConfigSeek(SEEK_MODE);
            if(TUNER_SUBLAYER_DONE == Result)
            {
                SubTuner_GotoStep(TUNER_STARTUP_END);
            }
            break;
            
        case SUBTUNER_VS_FIRST
            Result = Si475x_SeekFirst(SEEK_MODE);
            if(TUNER_SUBLAYER_DONE == Result)
            {
                SubTuner_GotoStep(TUNER_STARTUP_END);
            }
            break;
        
        case SUBTUNER_VS_NEXT:
            Result = Si475x_SeekNext();
            if(TUNER_SUBLAYER_DONE == Result)
            {
                SubTuner_GotoStep(TUNER_STARTUP_END);
            }
            break;
            
        case SUBTUNER_VS_CHK_QUAL:
            Result = Si475x_ChkQual(SEEK_MODE);
            if(TUNER_SUBLAYER_DONE == Result)
            {
                SubTuner_GotoStep(TUNER_STARTUP_END);
            }
            break;

        case SUBTUNER_VS_GOOD:
            
            break;
            
        case SUBTUNER_VS_EXIT:
            
            break;
            
        case SUBTUNER_VS_END    

            break;
        
        default:
            Result = TUNER_SUBLAYER_ERROR;    
            break;
    }

    // Sub Error Disposal
    if(Result == TUNER_SUBLAYER_ERROR)        
    {    
        SubTuner_Func_Error();
    }
}
/**********************************************************
 * @function    Tuner_Func_PwrOff
 * @brief      Power Off Tuner because Souce Switch or Power State 
 *            Change, Include Datum Saving and Power Control
 * @param      None                    
 * @retval     None
 **********************************************************/
void SubTuner_Func_PwrOff(void)
{
    uint8_t Result = TUNER_SUBLAYER_DOING;

    if(TunerDelayNotExpired(sTuner.SubFuncDelay))
        return;
    
    switch(sTuner.SubFuncStep)
    {
        case SUBTUNER_PWROFF_SORT:
            SubTuner_GotoStep(SUBTUNER_PWROFF_POWER);
            break;

        case SUBTUNER_PWROFF_POWER:
            SubTuner_GotoStep(SUBTUNER_PWROFF_END);
            break;

        case SUBTUNER_PWROFF_END:
            break;
    
        default:
            Result = TUNER_SUBLAYER_ERROR;
            break;
    }

    // Step Error Disposal
    if(TUNER_SUBLAYER_ERROR == Result)        
    {    
        SubTuner_Func_Error();
    }
}

/**********************************************************
 * @function    SubTuner_GotoStep
 * @brief       Sub-Tuner Control Which Steps Goto
 *            
 * @param      None                    
 * @retval     None
 **********************************************************/
void SubTuner_GotoStep(uint16_t x)
{
    sTuner.SubFuncStep = x;
    sTuner.SubDrvStep = 0;
    sTuner.SubDrvDelay = 0;
    sTuner.SubRetryCnt = 0;
}
/**********************************************************
 * @function    SubTuner_Func_Error
 * @brief      SubTuner Specific Step Execute Error, Judge Error or Do Retry
 *            >>Debug Usage 
 * @param      None                    
 * @retval     None
 **********************************************************/
 void SubTuner_Func_Error(void)
{
    sTuner.SubRetryCnt++;
    if(sTuner.SubRetryCnt < 4)        //Retry three times 
    { 
        sTuner.SubFuncStep &= 0xF0; // Go Back to Last Step
        sTuner.SubDrvStep = 0;
    }
    else
    {
        // Reserved for Error Disposal
    }
}

