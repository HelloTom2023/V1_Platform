/**********************************************************
 * @file        Task_Tuner.c
 * @purpose    Tuner Function, Control Block
 * @version    0.02
 * @date        27. June. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          27.June.2012        v0.01        created
 *  Deefisher.Lyu          19.July.2012        v0.02        Finish the Whole frame
 *  Deefisher.Lyu        5.July.2013         v0.03                                                                             
  **********************************************************/
#define TASK_TUNER_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= Function Announcement  =================== */
void Tuner_Func_Startup(void);
void Tuner_Func_Idle(void);
void Tuner_Func_Seek(void);
void Tuner_Func_PScan(void);
void Tuner_Func_PwrOff(void);
void Tuner_UpdateInfoes(void);
void Tuner_OutputInfoes(void);
void Tuner_Func_Error(uint8_t ErrType);
/* ========================= public variable ==================== */


/* ========================= private variable =================== */


// Function Array
void ( *const Tab_TunerFunc[] )(void) = {
    Tuner_Func_Startup,
    Tuner_Func_Idle,
    Tuner_Func_Seek,
    Tuner_Func_PScan,
    Tuner_Func_PwrOff,
};

/* ========================= Code Part =================== */

/**********************************************************
 * @function    Tuner_Func_Error
 * @brief      Tuner Specific Step Execute Error, Judge Error or Do Retry
 *            >>Debug Usage 
 * @param      uint8_t ErrType: Error Type                    
 * @retval     None
 **********************************************************/
void Tuner_Func_Error(uint8_t ErrType)
{
    //Debug Usage!!!
    if(SUBLAYER_STEP_ERROR ==  ErrType)
    {

    }
    else if(SUBLAYER_PARAMETER_ERROR ==  ErrType)
    {
        
    }

    //Retry if Error Occur
    sTuner.FuncRetryCnt++;
    if(sTuner.FuncRetryCnt < 4)        //Retry three times 
    {
        sTuner.MidLayerStep = OPERATION_0;    // Go Back to Last Step
        sTuner.DriverLayerStep = OPERATION_0;
    }
    else
    {
        // Reserved for Error Disposal
    }
}
/**********************************************************
 * @function    Tuner_GotoStep
 * @brief      Switch Function Control Step
 * @param      uint8_t x : Step Will Goto                    
 * @retval     None
 **********************************************************/
void Tuner_GotoStep(uint8_t x)
{
    //Step Set and Reset
    sTuner.FuncStep = x;
    sTuner.MidLayerStep = OPERATION_0;
    sTuner.DriverLayerStep = OPERATION_0;
    //Retry Counter Reset
    sTuner.FuncRetryCnt = 0;
}
/**********************************************************
 * @function    Tuner_Func_Startup
 * @brief      Tuner Startup: Power on, Reset, Initialize registers,
 *            Resume Last State
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_Func_Startup(void)
{
    uint8_t Result = SUBLAYER_DOING;
    //yangyan --2014.08.07
    if(!sTuner.DevInit)return;

    TunerSetSysState(TUNER_SYS_STARTUP); //Set Sub-System State

    switch(sTuner.FuncStep)
    {
        // Tuner Module Power On and Related Parameter Initialize
        case TUNER_STARTUP_PWRON:    
            Result = Tuner_PowerOn();
            if(SUBLAYER_DONE == Result)
            {
            	   Tuner_debug(_T("Tuner Power On OK\n"));
                Tuner_GotoStep(TUNER_STARTUP_RESET);
            }
            break;
            
        // Reset Tuner Module
        case TUNER_STARTUP_RESET:    
            Result = Tuner_ResetModule();
            if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_STARTUP_LOAD);
                sTuner.LoadDatumDly = TunerDelay(T500MS);
            }
            break;

        //Load Datum from EEPROM
        case TUNER_STARTUP_LOAD:
            Result = Tuner_LoadDatum();
           if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_STARTUP_INIT);
            }
            break;
            
        // Initialize Tuner Module, Load Boot Datum to  Registers    
        case TUNER_STARTUP_INIT:        
            Result = Tuner_InitRegister();
            if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_STARTUP_RESUME);
            }
            break;
            
        // Resume Last State: Resume Band, Resume Freq    
        case TUNER_STARTUP_RESUME:    
            Result = Tuner_ResumeLast();
            if(SUBLAYER_DONE == Result)
            {    
                //Feedback Tuner Active Done
                //Startup Done, Goto Idle waiting for newly actions
                sTuner.uSeekState.SsTotal = 0;    // Clear Seek Flag and Exit   
                Tuner_GotoStep(TUNER_FUNC_IDLE);
                
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    // Step Error Disposal
    if(Result > SUBLAYER_DONE)    
    {    
        Tuner_Func_Error(Result);
    }
}
/**********************************************************
 * @function    Tuner_Func_Idle
 * @brief      Tuner Stay in Idle State
 *                 Waiting for Incoming Operation
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_Func_Idle(void)
{
    //yangyan --2014.08.07
    if(!sTuner.DevInit)
    {
        Tuner_GotoStep(TUNER_FUNC_STARTUP);
        TunerSetSysState(TUNER_SYS_STARTUP);
    }
    
    if(TUNER_BAND_AM)
    {
        if(((TUNER_CURRENT_FREQ >= 750) && (TUNER_CURRENT_FREQ <= 850))
           || (TUNER_CURRENT_FREQ >= 1550))
        {
            if(5 != sTuner.PwrFreq)
            {
                IO_Set(IO_IDX_PM_SNT_FREQ,PIN_OUTPUT,1);  //500K
                sTuner.PwrFreq = 5;
            }
        }
        else
        {
            if(9 != sTuner.PwrFreq)
            {
                IO_Set(IO_IDX_PM_SNT_FREQ,PIN_OUTPUT,0); //900K
                sTuner.PwrFreq = 9;
            }
        }
    }
    else
    {
        if(9 != sTuner.PwrFreq)
        {
            IO_Set(IO_IDX_PM_SNT_FREQ,PIN_OUTPUT,0);  //500K
            sTuner.PwrFreq = 9;
        }
    }

    TunerSetSysState(TUNER_SYS_RUN);
}
/**********************************************************
 * @function    Tuner_Func_Seek
 * @brief      Tuner Seek, Include Most of Seek Action and Scan 
 *            Action: Manual Seek, Auto Memory Seek, 
 *                 TA Seek,PTY Seek,Scan,PI Seek 
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_Func_Seek(void)
{
    uint8_t Result = SUBLAYER_DOING;

    if(0x00 == sTuner.uSeekState.SsTotal)
    {
        return;
    }
    
    switch(sTuner.FuncStep)
    {
        // Mute Firstly Before Seek
        case TUNER_SEEK_MUTE:    
            Result = Tuner_ReqMute(MUTE_ON,TUNER_MID_SEEK);
            if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_SEEK_CONFIG);
		  sTunerKeep.bPausestate = 0;		
            }
            break;    

        // Set Module to Seek Mode, Set Specific Parameters
        case TUNER_SEEK_CONFIG:    
            Result = Tuner_SeekConfig(TUNER_MODE_SEEK);
            if(SUBLAYER_DONE == Result)
            {
                if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)    // Need Check Firstly Frequency while AMSing
                {
                    Tuner_GotoStep(TUNER_SEEK_FIRST);
                }
                else        // Goto Check Next Station of Currently while Manual Seeking
                {
                    Tuner_GotoStep(TUNER_SEEK_NEXT);
                }
            }
            break;

        // Check First station, Include Check Quality, especially for AMS, 
        case TUNER_SEEK_FIRST: 
            Result = Tuner_SeekFirst();
            if(SUBLAYER_DONE == Result)
            {
                // Got a Valid Station, ~~Y
                if(sTuner.bGoodStation)
                {	// Check Whether Need goto Check Rds State
                    if((!TunerRdsSettingOn())	|| (!TUNER_BAND_FM))
                    {	// Not Need Check Rds, Station Valid
                        Tuner_GotoStep(TUNER_SEEK_GOOD);
                    }
                    else
                    {	// Goto Check Rds					//Fixed time for rds checking
                        TunerSetOverTime(sTuner.FuncOverTime,TunerDelay(T500MS));
                        Tuner_GotoStep(TUNER_SEEK_CHK_RDS);
                    }
                }
                else
                {	// Goto Check Next Frequency
                    Tuner_GotoStep(TUNER_SEEK_NEXT);
                }
            }
            break;

        // Goto Seek Next Frequency
        case TUNER_SEEK_NEXT:    
            // Check Whether Wrap Aound!
            if((sTuner.SeekStartFreq == TUNER_CURRENT_FREQ)
                && (!sTuner.bSeekWrapAround )
                && (!sTuner.uSeekState.sSsBitMap.bAutoScan))
            {    // Wrap Around!,Same as Seek End
                if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)
                {    // AMSing ,goto Saving
                    if(sTuner.uSeekState.sSsBitMap.bBreak)
                    {
                      Tuner_GotoStep(TUNER_SEEK_EXIT);
                    }
                    else
                    {
                      Tuner_GotoStep(TUNER_SEEK_AMS_SAVE);
                    }
                }
                else
                {    // Normally Seek, goto EXIT
                    Tuner_GotoStep(TUNER_SEEK_EXIT);
                }
            }

			else if((sTuner.SeekStartFreq == TUNER_CURRENT_FREQ)
			&& (!sTuner.bSeekWrapAround )
			&&(sTuner.uSeekState.sSsBitMap.bAutoScan))
			{
				Tuner_GotoStep(TUNER_SEEK_EXIT); // xjh modif for 15HCBH-878
			}

            else
            {    
                sTuner.bSeekWrapAround = 0; //Clear Wrap Around Flag
                // Seek Next
                Result = Tuner_SeekNext(sTuner.bSeekDirect);
                if(SUBLAYER_DONE == Result)
                {
                    Rds_ResetAll(); //Reset Rds Related...
                    Tuner_GotoStep(TUNER_SEEK_CHK_QUAL);
                }
            }
            break;
            
        // Check Quality
        case TUNER_SEEK_CHK_QUAL:
            Result = Tuner_ChkQual(QUAL_CHK_SEEK);
            if(SUBLAYER_DONE == Result)
            {
                if(sTuner.bGoodStation)
                {	// Check Whether Need goto Check Rds State
                    if((!TunerRdsSettingOn())	|| (!TUNER_BAND_FM))
                    {	// Not Need Check Rds, Station Valid
                        Tuner_GotoStep(TUNER_SEEK_GOOD);
                    }
                    else
                    {	// Goto Check Rds						//Fixed Time..
                        TunerSetOverTime(sTuner.FuncOverTime,TunerDelay(T500MS));
                        Tuner_GotoStep(TUNER_SEEK_CHK_RDS);
                    }
                }
                else
                {    // Goto Check Next Frequency
                    Tuner_GotoStep(TUNER_SEEK_NEXT);
                }
            }
            break;

        // Check Specific Rds Info
        case TUNER_SEEK_CHK_RDS:    
            if(OverTimeExpired(sTuner.FuncOverTime))    
            {    // OverTime, Specific Rds not Got
                Tuner_GotoStep(TUNER_SEEK_NEXT);
            }
            else
            {
                if(Tuner_RdsSeekStatus())	// Specific Rds Info Got, Station Valid
                {
                    Tuner_GotoStep(TUNER_SEEK_GOOD);
                }
            }
            break;

        // Got A Valid Station, Do What Needed
        case TUNER_SEEK_GOOD:
            if(sTuner.uSeekState.sSsBitMap.bSeek || sTuner.uSeekState.sSsBitMap.bPTYSeek)
            {    // Manual Seek Got a Valid Station, goto Exit
                Tuner_GotoStep(TUNER_SEEK_EXIT);
                break;
            }
            else if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)
            {    // Saved Valid Station into AMS Temporary Buffer
             #ifdef D_TUNER_LIST
            	sTuner.TmpListNum += 1;
                if(sTuner.TmpListNum > LIST_BUFFER_MAX)
                {
                    Tuner_GotoStep(TUNER_SEEK_AMS_SAVE);
                }
                else
                {
         			if(((TUNER_BAND_FM)&&(TUNER_CURRENT_FREQ>=FM_FREQ_MIN)&&(TUNER_CURRENT_FREQ<=FM_FREQ_MAX)) ||
						((TUNER_BAND_AM)&&(TUNER_CURRENT_FREQ>=AM_FREQ_MIN)&&(TUNER_CURRENT_FREQ<=AM_FREQ_MAX)))
                    	sTuner.asTmpList[sTuner.TmpListNum - 1].Freq = TUNER_CURRENT_FREQ;
					else
                		sTuner.TmpListNum -= 1;
					
					if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)
					{
					    Tuner_GotoStep(TUNER_SEEK_NEXT);
					}
					else if(sTuner.uSeekState.sSsBitMap.bAutoScan)
					{
						Tuner_GotoStep(TUNER_SEEK_PREVIEW);
					}
                }
                break;
           #else
                TUNER_AMS_MEM_STRUCT sNewStation;
                uint8_t u8BuffNum;

                sNewStation.Freq = TUNER_CURRENT_FREQ;
                sNewStation.Qual = Tuner_GetQualVal();
                // Got Buffer Number according Currently Band and Preset max number
                u8BuffNum = TUNER_PRESET_MAX * (sTuner.BandEnd - sTuner.BandStart + 1);
		   if(sTuner.AmsValidStaNum < u8BuffNum)
		  	 sTuner.AmsValidStaNum++ ;		
                Tuner_InsertNewStation(sTuner.asAmsBuff,&sNewStation,u8BuffNum); 
				#endif 
            }
            if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)
                Tuner_GotoStep(TUNER_SEEK_NEXT); 
		else	
                Tuner_GotoStep(TUNER_SEEK_PREVIEW);        // Goto Preview while AMS or Scan
            break;
            
        // Preview Currently Valid Station
        case TUNER_SEEK_PREVIEW:    
            Result = Tuner_Preview();
            if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_SEEK_NEXT); // Goto Seek Next Valid Station
            }
            break;
            
        // Sort AMS Buff,Save to Preset Buff
        case TUNER_SEEK_AMS_SAVE: 
			#ifdef D_TUNER_LIST
            Tuner_SortStationAccordFreq(sTuner.asTmpList, sTuner.TmpListNum); 
			#else
            Tuner_SortStationAccordFreq(sTuner.asAmsBuff, sTuner.AmsValidStaNum); 
            #endif
            Tuner_SortPreset();
            Tuner_GotoStep(TUNER_SEEK_EXIT);
            break;

        //Seek End ,Exit Seek Mode go back to Preset Mode
        case TUNER_SEEK_EXIT:    
            Result = Tuner_SeekConfig(TUNER_MODE_PRESET);
            if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_SEEK_UNMUTE);
            }
            break;

        // Seek End, Release Mute 
        case TUNER_SEEK_UNMUTE:        
            Result = Tuner_ReqMute(MUTE_OFF,TUNER_MID_SEEK);
            if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_SEEK_END);
            }
            break;

        // Seek End, Go Back To IDLE state
        case TUNER_SEEK_END:
            sTuner.uSeekState.SsTotal = 0;    // Clear Seek Flag and Exit     
            Tuner_GotoStep(TUNER_FUNC_IDLE);
       
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;    
            break;
    }

    // Step Error Disposal
    if(SUBLAYER_ERROR == Result)        
    {    
        Tuner_Func_Error(Result);
    }
}
/**********************************************************
 * @function    Tuner_Func_PScan
 * @brief      Preset Scan
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_Func_PScan(void)
{
    uint8_t Result = SUBLAYER_DOING;

    if(0x00 == sTuner.uSeekState.SsTotal) 
    {
        return;
    }
    
    switch(sTuner.FuncStep)
    {
        //Start Pscan, config and PS first preset
        case TUNER_PSCAN_START:
            //goto the first band and first preset
        #ifndef D_TUNER_PSCAN_CURRENT_BAND //Scan All band or currently band    
            if(TUNER_CURRENT_BAND != sTuner.BandStart)
            {
                TUNER_CURRENT_BAND = sTuner.BandStart;
                
                // Output Newly Band Related Preset List
                _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENT_BAND,&sTunerInfo);
            }
        #endif//D_TUNER_PSCAN_CURRENT_BAND    
            TUNER_CURRENT_PRESET = TUNER_PRESET_1;
            TUNER_CURRENT_FREQ = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET - 1];
            Tuner_GotoStep(TUNER_PSCAN_NEXT);
            break;

        //Pscan Next Preset    
        case TUNER_PSCAN_NEXT:
            Result = Tuner_SetFreq(TUNER_CURRENT_FREQ);
            if(SUBLAYER_DONE == Result)
            {
                sTuner.PscanDelay = TunerDelay(T5S);
                Tuner_GotoStep(TUNER_PSCAN_CHECK);
            }
            break;

        //Check End?    
        case TUNER_PSCAN_CHECK:
            if(DelayHasExpired(sTuner.PscanDelay))
            {
                TUNER_CURRENT_PRESET++;
                if(TUNER_CURRENT_PRESET > TUNER_PRESET_MAX)
                {
                    TUNER_CURRENT_PRESET = TUNER_PRESET_1;
                #ifndef D_TUNER_PSCAN_CURRENT_BAND //Scan All band or currently band        
                    TUNER_CURRENT_BAND++;
                    if(TUNER_CURRENT_BAND > sTuner.BandEnd)
                    {
                        TUNER_CURRENT_BAND = sTuner.BandStart;
                #endif//D_TUNER_PSCAN_CURRENT_BAND    
                        TUNER_CURRENT_FREQ = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET - 1];
                        Tuner_GotoStep(TUNER_PSCAN_END); //Preset Scan Ends
                        break;
                #ifndef D_TUNER_PSCAN_CURRENT_BAND //Scan All band or currently band            
                    }
                    
                    // Output Newly Band Related Preset List
                    _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENT_BAND,&sTunerInfo);
                #endif//D_TUNER_PSCAN_CURRENT_BAND
                }
                TUNER_CURRENT_FREQ = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET - 1];
                Tuner_GotoStep(TUNER_PSCAN_NEXT); //goto Pscan next preset
            }
            break;

        //Pscan Ends!    
        case TUNER_PSCAN_END:
            Result = Tuner_SetFreq(TUNER_CURRENT_FREQ);
            if(SUBLAYER_DONE == Result)
            {
            #ifndef D_TUNER_PSCAN_CURRENT_BAND //Scan All band or currently band    
                // Output Newly Band Related Preset List
                _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENT_BAND,&sTunerDat);
            #endif//D_TUNER_PSCAN_CURRENT_BAND
                sTuner.uSeekState.SsTotal = 0;    // Clear Seek Flag and Exit         
                Tuner_GotoStep(TUNER_FUNC_IDLE);
            }
            break;    
            
        default:
            Result = SUBLAYER_STEP_ERROR;    
            break;
    }
    
    // Step Error Disposal
    if(SUBLAYER_ERROR == Result)        
    {    
        Tuner_Func_Error(Result);
    }
}
/**********************************************************
 * @function    Tuner_Func_PwrOff
 * @brief      Power Off Tuner because Souce Switch or Power State 
 *            Change, Include Datum Saving and Power Control
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_Func_PwrOff(void)
{
    uint8_t Result = SUBLAYER_DOING;

    TunerSetSysState(TUNER_SYS_PWROFF);
    
    switch(sTuner.FuncStep)
    {
        // Sort Currently Situation, and Initialize Some Parameters 
        case TUNER_PWROFF_SORT:
            if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)    // Sort if AMSing
            {
                //Update Band Attri
                sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq = TUNER_CURRENT_FREQ;
                TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
                sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Preset = TUNER_CURRENT_PRESET;
		Tuner_SortStationAccordFreq(sTuner.asAmsBuff, sTuner.AmsValidStaNum); 
                Tuner_SortPreset();
                if(sTuner.bDatumReady)
                {
                    OS_CreateRamChkBlock((void*)&sTunerDat,
                                (sizeof(TUNER_DATUM_STRUCT)-sizeof(uint16_t)),
                                (void*)&(sTunerDat.CheckSum));
                }
            }                
            // Set Some Paremeters         
            Tuner_VariableInit();
            //if Related Rds Setting is On, Do not Deactive Tuner Source...
            if((1 == sTuner.PwrState) && (TaSetting || AfSetting))
            {
                if(TUNER_SYS_RUN == sTuner.SysBakState)
                {
                    Tuner_GotoStep(TUNER_FUNC_IDLE);
                }
                else //if(TUNER_SYS_STARTUP == sTuner.SysBakState)  //Re-Start while in ..Other State include Startup and Poweroff, 
                {
                    Tuner_GotoStep(TUNER_FUNC_STARTUP);
                } 
                //Set System Front On, while Rds On, 
                sTuner.ZoneState |= SYS_MASK_FRONT;
                return;
            }
            Tuner_GotoStep(TUNER_PWROFF_SAVE);
            break;

        // Save Specific Parameters to EEPROM    
        case TUNER_PWROFF_SAVE:
            Result = Tuner_SaveAll();
            if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_PWROFF_POWER);
            }
            break;

        // Control Power to Off According Condition
        case TUNER_PWROFF_POWER:
            Result = Tuner_PowerOff();
            if(SUBLAYER_DONE == Result)
            {
                Tuner_GotoStep(TUNER_PWROFF_END);
                sTuner.ZoneState = 0x00;
                TunerSetSysState(TUNER_SYS_SLEEP); 
                sTuner.FuncOverTime = TunerDelay(T2S);
            }
            break;

        // End
        case TUNER_PWROFF_END:
            if(sTuner.FuncOverTime)return;
            //PM_UnitPowerSet(PM_UNIT_ANT,OFF);
            TunerSetSysState(TUNER_SYS_SLEEP); 
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;    
            break;
    }

    // Step Error Disposal
    if(SUBLAYER_ERROR == Result)        
    {    
        Tuner_Func_Error(Result);
    }
}
/**********************************************************
 * @function    Tuner_UpdateInfoes
 * @brief      
 * @param      NULL
 * @retval     NULL
 **********************************************************/
void Tuner_UpdateInfoes(void)
{
    uint8_t Result = SUBLAYER_DOING;

    //Filter: State can not read Infoes
    if(TUNER_SYS_RUN != TunerGetSysState()) 
    {
        return;
    }
    
    if((sTuner.FuncStep & 0xF0) < TUNER_FUNC_IDLE)
    {
        return;
    }
    
    if(TUNER_FUNC_IDLE != (sTuner.FuncStep & 0xF0))
    {
        return;
    }

    if(DelayNotExpired(sTuner.GetInfoDelay))
        return;

    Result = Tuner_GetInfoes();
    if(SUBLAYER_DONE == Result)
    {
        //Update Stereo
        if(STEREO_AUTO == StereoSetting)
        {
            if(0 == Tuner_GetStereoFlag())
            {
                sTuner.StereoYesCnt = 0;
                sTuner.StereoNoCnt++;
                if(sTuner.StereoNoCnt > 2)
                {
                    if(1 == sTuner.bStereoMono)
                    {
                        _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENTLY,&sTunerDat);
                    }
                    sTuner.bStereoMono = 0;
                }
            }
            else
            {
                sTuner.StereoNoCnt = 0;
                sTuner.StereoYesCnt++;
                if(sTuner.StereoYesCnt > 2)
                {
                    if(0 == sTuner.bStereoMono)
                    {
                        _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENTLY,&sTunerDat);
                    }
                    sTuner.bStereoMono = 1;
                }
            }
        }
        //Update Signal Strength
        sTuner.SignalStr = Tuner_GetSignalStr();    
        sTuner.GetInfoDelay = TunerDelay(T500MS);
    }

    if(Result > SUBLAYER_DONE)
    {
        sTuner.GetInfoDelay = TunerDelay(T500MS);
    }
}
/**********************************************************
 * @function    Tuner_ValidScan
 * @brief      Get Valid Station List at background               
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_ValidScan(void)
{
    uint8_t Result = SUBLAYER_DOING;
    TUNER_AMS_MEM_STRUCT sNewStation;
    uint8_t Temp,i,TempValidNum;

    if(TUNER_SYS_RUN != TunerGetSysState())
    {
        return;
    }
    
    //Only Do Valid Scan in the FM Band!
    if(!TUNER_BAND_FM)
        return;
    
    //Tuner Idle & Rds Idle
    if((TUNER_FUNC_IDLE != sTuner.FuncStep)) //||)
    {
        sTuner.bValidChecked = 1; //Sign VScan has be interrupted...
        return;
    }    

    //Conditions can not execute Valid List Scan...
    //if(DelayNotExpired(sTuner.ValidDelay))
     //   return;

    if(sTuner.bValidChecked)
    {
        sTuner.bValidChecked = 0;
        sTuner.GetAfQualCtl = 0;    //Clear Step
    }

    //Update Newly Valid List per 3 seconds
#ifdef D_VSCAN_QUEUE_BASE_ORDER 
    if(0 == sTuner.ValidUpdateDelay)
    {
        sTuner.ValidUpdateDelay = TunerDelay(T10S); // 5 Seconds
        TempValidNum = 0;
        //Sync partial newly valid list, combined with partial old valid station
        for(Temp = 0; Temp < VSCAN_BUFFER_MAX; Temp++)
        {
            //Same Position: Newly Bigger Than Old, Directly replace with newly one
            if(sTuner.asValidBuff[Temp].Freq > sTunerKeep.ValidList[Temp])
            {
                sTunerKeep.ValidList[Temp] = sTuner.asValidBuff[Temp].Freq;
                TempValidNum++;
            }
            //Same Position: Newly same as Old, if all zero, valid list combined, otherwise number counter increased by 1
            else if(sTuner.asValidBuff[Temp].Freq == sTunerKeep.ValidList[Temp])
            {
                if(0 == sTuner.asValidBuff[Temp].Freq)
                {
                    break; //all synced, newly valid list was combined!
                }
                else
                {
                    TempValidNum++;
                }
            }
            //Same Position: Newly smaller than Old, Insert newly
            else//(sTuner.asValidBuff[Temp].Freq < sTunerInfo.ValidList[Temp])
            {
                if(0 == sTuner.asValidBuff[Temp].Freq)
                {
                    //Delete the same and smaller one, then move each station to left one by one
                    if(sTunerKeep.ValidList[Temp] <=  sTunerKeep.ValidList[Temp - 1])
                    {
                        for(i = Temp; i < (VSCAN_BUFFER_MAX - 1); i++)
                        {
                            sTunerKeep.ValidList[i] = 0; 
                            if(0 != sTunerKeep.ValidList[i + 1])
                            {
                                sTunerKeep.ValidList[i] = sTunerKeep.ValidList[i + 1];
                            }
                            else
                            {
                                break;
                            }
                        }
                        sTunerKeep.ValidList[i] = 0; //Clear Last
                    }
                    //else
                    {
                        //Old bigger than the left one, do nothing but increase number counter by 1
                    }
                    TempValidNum++; //Increase Valid Number by One
                }
                else
                {
                    //Move the Old to the Right one by one :(Here can be set more efficiently with new method...???)
                    for(i = (VSCAN_BUFFER_MAX - 1); i > Temp; i--)
                    {
                        sTunerKeep.ValidList[i] = sTunerKeep.ValidList[i - 1];
                    }
                    //Insert Newly Valid Station
                    sTunerKeep.ValidList[Temp] = sTuner.asValidBuff[Temp].Freq;
                    TempValidNum++;
                }
            }
        }
        //Sync newly Valid Station Number and Send message
        sTunerKeep.ValidNumber = TempValidNum;
        sTunerKeep.ValidHighlight = 0;
        if(0 != sTunerKeep.ValidNumber)
        {
            for(Temp = 0; Temp < VSCAN_BUFFER_MAX; Temp++) //Get Currently Highlight
            {
                if(sTunerKeep.ValidList[Temp] > TUNER_CURRENT_FREQ)
                {
                    break;
                }
                else if(sTunerKeep.ValidList[Temp] == TUNER_CURRENT_FREQ)
                {
                    sTunerKeep.ValidHighlight = (Temp + 1);
                }
            }
            _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_LIST,&sTunerKeep);
        }
    }    
    else
    {
        sTuner.ValidUpdateDelay--;  //Decrease Periodly update timer
    }
#endif//D_VSCAN_QUEUE_BASE_ORDER     
    
    if(DelayNotExpired(sTuner.ValidChkDly))
        return;

    switch(sTuner.ValidCtl)
    {
        //Initialize Related...before Scan
        case TUNER_VSCAN_INIT:
            sTuner.GetAfQualCtl = 0;    
            sTuner.ValidCheckFreq = sTuner.FreqMin;
            for(Temp = 0; Temp < VSCAN_BUFFER_MAX; Temp++)
            {
                sTuner.asValidBuff[Temp].Qual = 0;
                sTuner.asValidBuff[Temp].Freq = 0;
            }
            sTuner.ValidCtl = TUNER_VSCAN_RESUME;
            break;

        //Resume Check Stations
        case TUNER_VSCAN_RESUME:    
            Result = Tuner_GetAfQuality(sTuner.ValidCheckFreq,1);
            if(SUBLAYER_DONE == Result)
            {
                //Queue in the station according to signal strength
                sNewStation.Freq = sTuner.ValidCheckFreq;
                sNewStation.Qual = sTuner.FastAfSmeter;
                //It is necessary to judge WAM/USN/FOF to filtrate the point near strong station
                    //Maybe the Valid Check TH a little lower than normally seek TH is better?
                if((sTuner.FastAfSmeter > 50)//56)
                    && (sTuner.FastAfAdjChannel < 51)//51)        //20% USN
                    && (sTuner.FastAfMultipath < 38)//38)    //15% WAM
                    && ((sTuner.FastAfFof&0x7F) < 15))//10))            //10K FOF
                {    
                #ifndef D_VSCAN_QUEUE_BASE_ORDER //D_VSCAN_QUEUE_BASE_FS
                    //Queue Station according to Field Strength 
                    Tuner_InsertNewStation(sTuner.asValidBuff,&sNewStation,VSCAN_BUFFER_MAX);
                #else
                    //Queue Station from small to big : based on order
                    for(Temp = 0; Temp < VSCAN_BUFFER_MAX; Temp++)
                    {
                        if(0 == sTuner.asValidBuff[Temp].Freq)
                        {
                            sTuner.asValidBuff[Temp].Freq = sNewStation.Freq;
                            break;
                        }
                    }
                #endif//D_VSCAN_QUEUE_BASE_ORDER
                }
                
                sTuner.ValidCheckFreq += sTuner.TuneStep;
                if(5 == sTuner.TuneStep)    //Filtrate: 50Khz Point
                {
                    sTuner.ValidCheckFreq += sTuner.TuneStep;
                }
                
                //Check Whether Ends!
                if((sTuner.ValidCheckFreq > sTuner.FreqMax) //All Frequency Checked!
                    || ((VSCAN_BUFFER_MAX ==sTunerKeep.ValidNumber) //Have Got Max Number Valid Station., Ignore Left Frequency..
                    && (sTuner.ValidCheckFreq > sTunerKeep.ValidList[VSCAN_BUFFER_MAX - 1])))    
                {
                    sTuner.ValidCtl = TUNER_VSCAN_END;
                }
                else
                {
                    sTuner.ValidChkDly = TunerDelay(T5S);  // Small Delay will cause noise
                }
            }
            break;

        //Check Ends, Update Newly Valid List
        case TUNER_VSCAN_END:
            //Sync to Vald List Buffer
            if(sTuner.ValidCheckFreq > sTuner.FreqMax) //Re-Get Valid Number and Highlight Index,
            {                                // Only When Seek Over the Band
                sTunerKeep.ValidHighlight = 0;
                sTunerKeep.ValidNumber = 0;
                for(Temp = 0; Temp < VSCAN_BUFFER_MAX; Temp++)
                {
                    sTunerKeep.ValidList[Temp] = sTuner.asValidBuff[Temp].Freq;
                    if(sTuner.asValidBuff[Temp].Freq > 0)
                    {
                        sTunerKeep.ValidNumber++;    
                    }
                    if(sTuner.asValidBuff[Temp].Freq == TUNER_CURRENT_FREQ)
                    {
                        sTunerKeep.ValidHighlight = (Temp + 1);
                    }
                }
            }
            //to HMI, Sync Newly Valid List
            _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_LIST,&sTunerKeep);
            sTuner.ValidDelay = TunerDelay(T20S);
            sTuner.ValidCtl = TUNER_VSCAN_INIT;
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    // Step Error Disposal
    if(Result > SUBLAYER_DONE)
    {
        sTuner.ValidDelay = TunerDelay(T1S);
        sTuner.ValidCtl = TUNER_VSCAN_INIT;
    }
}
/**********************************************************
 * @function    Tuner_InputExecute
 * @brief      Execute Specific Action!!!!!!!!!!
 * @param      None                    
 * @retval     result of execute
 **********************************************************/
uint8_t Tuner_InputExecute(uint8_t Req)
{
    uint8_t Result = SUBLAYER_DOING;
        
    switch(Req)
    {
        // Commonly Operate: Set Frequency        
        case TUNER_COMMON_FREQ:
            Result = Tuner_SetFreq(TUNER_CURRENT_FREQ);
            break;
            
        // Commonly Operate: Set Band
        case TUNER_COMMON_BAND:    
            Result = Tuner_SetBand();
            break;
            
        // Commonly Op: Stereo Setup switch
        case TUNER_COMMON_ST:    
            Result = Tuner_SwtichST();    
            break;

        // Commonly Operate: Seek
        case TUNER_COMMON_SEEK:
            sTuner.bSeekDirect = sTuner.bBakSeekDirect;
            sTuner.uSeekState = sTuner.uBakSeekState;
            Tuner_GotoStep(TUNER_FUNC_SEEK);
            Result = SUBLAYER_DONE;
            break;
            
        // Commonly Preset Scan
        case TUNER_COMMON_PSCAN:    
            sTuner.uSeekState = sTuner.uBakSeekState;
            Tuner_GotoStep(TUNER_FUNC_PSCAN);
            Result = SUBLAYER_DONE;
            break;
                
        //Do Nothing
        case TUNER_COMMON_NULL:
        default:
            Result = SUBLAYER_DONE;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_OpQueueIn
 * @brief      Queue In Operation to Buffer
 * @param      uint8_t Op
 * @retval     NULL
 **********************************************************/
void Tuner_OpQueueIn(uint8_t Op)
{
    sTuner.OpBuffer[sTuner.OpTail] = Op;    

    sTuner.OpTail++;
    if(sTuner.OpTail >= T_OP_BUFFER_MAX)
        sTuner.OpTail = 0;
}
/**********************************************************
 * @function    Tuner_OpChkMute
 * @brief      Check Whether Need Mute Action
 * @param      uint8_t Op
 * @retval     NULL
 **********************************************************/
uint8_t Tuner_OpChkMute(uint8_t Op)
{
    uint8_t Result = 1;

    switch(Op)
    {
        case TUNER_COMMON_SEEK:
        case TUNER_COMMON_PSCAN:
            Result = 0;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_OpDisposal
 * @brief      Operation Disposal
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Tuner_OpDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;

    //Filter:
    if(TUNER_SYS_RUN != TunerGetSysState())
    {
        return;
    }
    
    switch(sTuner.OpCtl)
    {
        //Idle, Waiting for Requirment
        case T_OP_CTL_IDLE:
            if(sTuner.OpTail != sTuner.OpHead) 
            {
                sTuner.OpCtl = T_OP_CTL_BREAK;
                sTuner.BreakCtl = 0;
                //Clear Specific Funcion module's control step
                sTuner.BreakCtl = OPERATION_0;
            }
            break;

        //Newly Action will Break Currently...    
        case T_OP_CTL_BREAK:
            Result = Tuner_OperateBreak();
            if(SUBLAYER_DONE == Result)
            {
                sTuner.OpCtl = T_OP_CTL_MUTE;
                if((TUNER_COMMON_NULL == sTuner.OpBuffer[sTuner.OpHead])
                    || TUNER_COMMON_BREAK == sTuner.OpBuffer[sTuner.OpHead])
                {
                    sTuner.OpCtl = T_OP_CTL_END;
                }
            }
            break;

        //Mute, if Needed
        case T_OP_CTL_MUTE:
            if(1 == Tuner_OpChkMute(sTuner.OpBuffer[sTuner.OpHead]))
            {
                Result = Tuner_ReqMute(MUTE_ON,TUNER_MID_OP);
            }
            else 
            {
                Result = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == Result)
            {
                sTuner.OpCtl = T_OP_CTL_EXECUTE;
            }
            break;
            
        //Execute Required Operation...
        case T_OP_CTL_EXECUTE:
            Result = Tuner_InputExecute(sTuner.OpBuffer[sTuner.OpHead]);
            if(SUBLAYER_DONE == Result)
            {
                sTuner.OpCtl = T_OP_CTL_DEMUTE;
            }
            break;

        //De-Mute
        case T_OP_CTL_DEMUTE:
            if(1 == Tuner_OpChkMute(sTuner.OpBuffer[sTuner.OpHead]))
            {
                Result = Tuner_ReqMute(MUTE_OFF,TUNER_MID_OP);
            }
            else 
            {
                Result = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == Result)
            {
                sTuner.OpCtl = T_OP_CTL_END;
            }
            break;
            
        //Required Operation is Done, Go to Next...
        case T_OP_CTL_END:
     		if(TUNER_COMMON_SEEK != sTuner.OpBuffer[sTuner.OpHead])	
		{
			sTunerKeep.bPausestate = 0;
		}	
			
            sTuner.OpHead++;
            if(sTuner.OpHead >= T_OP_BUFFER_MAX)
            {
                sTuner.OpHead = 0;
            }
            sTuner.OpCtl = T_OP_CTL_IDLE;
            break;
            
        default:
            break;
    }
}
/**********************************************************
 * @function    Tuner_VirTimer
 * @brief      Tuner's Virtual Timer          
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_VirTimer(void)
{
    static uint8_t Timer_10MS = 0;
    static uint8_t Timer_100MS = 0;
    static uint8_t Timer_1S = 0;

    sTuner.PeriodicOut++;
    if(sTuner.FuncOverTime)sTuner.FuncOverTime--;
    if(sTuner.MidLayerDelay)sTuner.MidLayerDelay--;
    if(sTuner.MidLayerOverTime)sTuner.MidLayerOverTime--;
    if(sTuner.DriverLayerDelay)sTuner.DriverLayerDelay--;
    if(sTuner.GetInfoDelay)sTuner.GetInfoDelay--;
    if(sTuner.ReqMuteDelay)sTuner.ReqMuteDelay--;
    //Preset Scan Delay Counter
    if(sTuner.PscanDelay)sTuner.PscanDelay--;
    if(sTuner.ValidDelay)sTuner.ValidDelay--;
    if(sTuner.ValidChkDly)sTuner.ValidChkDly--;
    if(sTuner.GetAfQualDelay)sTuner.GetAfQualDelay--;
    if(sRds.AFSwitchDelay)sRds.AFSwitchDelay--;
    if(sTuner.LoadDatumDly)sTuner.LoadDatumDly--;

    Timer_10MS += 1;
    if(Timer_10MS >= 5) //10MS Tick
    {
        Rds_Timer10ms();
        Timer_10MS = 0;
        Timer_100MS += 1;
    }
    if(Timer_100MS >= 10) // 100MS Tick
    {
        Rds_Timer100ms();
        Timer_100MS = 0;
        Timer_1S += 1;
    }
    if(Timer_1S >= 10) // 1S Tick
    {
        Rds_Timer1s();
        Timer_1S = 0;
    }
    if(sRds.RegularReadDelay) sRds.RegularReadDelay--;

}
/**********************************************************
 * @function    Tuner_ColdInit
 * @brief      Cold Start, Reset All of Audio 
 * @param      None
 * @retval     None
 **********************************************************/
void Tuner_ColdInit(void)
{
    Tuner_VariableReset(); //Pre-Reset Variable for System Sync Usage...
    Tuner_GotoStep(0);
    TunerSetSysState(TUNER_SYS_SLEEP);
}
/**********************************************************
 * @function    Tuner_WarmInit
 * @brief      Warm Start, Initialize All of Tuner 
 * @param      None
 * @retval     None
 **********************************************************/
void Tuner_WarmInit(void)
{
    Tuner_GotoStep(0);
    TunerSetSysState(TUNER_SYS_SLEEP);
}
/**********************************************************
 * @function    Tuner_ResetInit
 * @brief      Warm Start, Initialize All of Tuner 
 * @param      None
 * @retval     None
 **********************************************************/
void Tuner_ResetInit(eSOURCE_TYPE eType)
{
	sTuner.ZoneState = 0x00;
	sTunerKeep.bBakReg = 0x00;
	sTunerKeep.bPausestate=0x00; 
	sTunerKeep.sBakSetting.Total = 0x00;
	Tuner_GotoStep(0);
	TunerSetSysState(TUNER_SYS_SLEEP);
}
/**********************************************************
 * @function  Tuner_Active
 * @brief      Active Tuner Source
 * @param    eSOURCE_ZONE sZone
 * @retval     NULL
 **********************************************************/
void Tuner_Active(eSOURCE_TYPE eType,eSOURCE_ZONE sZone)
{
    if(SRC_ZONE_FRONT == sZone)
    {
        sTuner.ZoneState |= SYS_MASK_FRONT;
    }
    else if(SRC_ZONE_REAR == sZone)
    {
        sTuner.ZoneState |= SYS_MASK_REAR;
    }

    // Re-Startup while Tuner Not Running....
    if(TUNER_SYS_RUN != TunerGetSysState()) 
    {
        TunerSetSysState(TUNER_SYS_STARTUP);
        Tuner_GotoStep(TUNER_FUNC_STARTUP);
	 PM_UnitPowerSet(PM_UNIT_ANT,ON);
    }
}
/**********************************************************
 * @function    Tuner_Deactive
 * @brief      Deactive Tuner Source
 * @param      eSOURCE_ZONE sZone
 * @retval     NULL
 **********************************************************/
void Tuner_Deactive(eSOURCE_TYPE eType,eSOURCE_ZONE sZone)
{
    if(SRC_ZONE_FRONT == sZone)
    {
        sTuner.ZoneState &= (~SYS_MASK_FRONT);
    }
    else if(SRC_ZONE_REAR == sZone)
    {
        sTuner.ZoneState &= (~SYS_MASK_REAR);
    }

    //Re-Power Tuner Task..
    if((0x00 == sTuner.ZoneState) && (TunerGetSysState() <= TUNER_SYS_PWROFF))
    {
        //Save Tuner Block
        if(sTuner.bDatumReady)
        {
            OS_CreateRamChkBlock((void*)&sTunerDat,
                        (sizeof(TUNER_DATUM_STRUCT)-sizeof(uint16_t)),
                        (void*)&(sTunerDat.CheckSum));
        }
        sTuner.SysBakState = sTuner.SysState; //Bak Currently Tuner System State
        TunerSetSysState(TUNER_SYS_PWROFF);
        Tuner_GotoStep(TUNER_FUNC_PWROFF);
    }
}
/**********************************************************
 * @function	Tuner_TaCheck
 * @brief  	Check TA Status
 * @param  	NULL
 * @retval 	NULL
 **********************************************************/
void Tuner_TaCheck(void)
{
    
#if 0
    if(TaSetting && (sRds.F_EONEnable) && (0 == sRds.F_InTASwitch))	// EONTA switch
    {
        if(sRds.F_GetNewEONTA
            && sRds.EONTA
            && sRds.F_GetEONAFList
            && (0 == sRds.F_InEONTASwitch)
            && (0 == sRds.InTADelayTimer)
            && (0 == sRds.EnterEONTADelayTimer)
            && sRds.EONTP
            && (sRds.EONAFNum > 0))  // Added by Deefisher
        {
            sRds.EnterTADelayTimer=0;
            Rds_SwitchToEONTa();
            Radio_ReqTaAudioOn();	//Req Ta Audio On
            RadioOut_Status();
        }
        if(sRds.F_InEONTASwitch && (sRds.InTADelayTimer == 0))
        {
            if((!(sRds.TA && sRds.TP)) || NotRdsStation)
            {
                if(sRds.TAWaitAFCheckTimer == 0)
                {
                    EONTaSwitchBack();
                    Radio_ReqTaAudioOff();	//Req Ta Audio Off
                    RadioOut_Status();
                    if(sRds.TA)
                        sRds.EnterTADelayTimer = 30;
                }
            }
            else
                sRds.TAWaitAFCheckTimer = 10; // 1S
        }
    }
#endif
    if((TaSetting) && (0 == sRds.F_InEONTASwitch))
    {
        //TA Valid and Not In TA Switched Status
        if((sRds.TAValid && sRds.TPValid) && (0 == sRds.F_InTASwitch))
        {
            sRds.EnterTADelayTimer = 30; // 200ms delay chk
        }
        //After Stable Delay, Goto Broadcast TA audio
        if((sRds.EnterTADelayTimer <= 28) && (sRds.EnterTADelayTimer > 0))
        {
            sRds.EnterTADelayTimer = 0;
            if((sRds.TAValid && sRds.TPValid) && (0 == sRds.F_InTASwitch))
            {
                Rds_SwitchToTa();
                //Require For TA Audio On and Update TA Broadcasting Icon
                _SendMsgToHMI(MS_SRC_SET_TOP_TYPE,SRC_TYPE_RDS_TA,TRUE);    
                //_SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_RDS_UPD_STATUS,sRds.RT);
            }
        }

        if(sRds.F_InTASwitch && (0 == sRds.InTADelayTimer))		
        {   //TA away, go back ..
            if((NotRdsStation) || ((0 == sRds.TAValid) || (0 == sRds.TPValid)))
            {
                if(sRds.TAWaitAFCheckTimer == 0)
                {				
                    Rds_TaSwitchBack();
                    //Require For TA Audio Off and Update TA Broadcasting Icon
                    _SendMsgToHMI(MS_SRC_SET_TOP_TYPE,SRC_TYPE_RDS_TA,FALSE);    
                    //_SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_RDS_UPD_STATUS,sRds.RT);

                    if(sRds.EONTA)
                    {
                        sRds.EnterEONTADelayTimer = 30;
                    }
                }
            }
            else
            {
                sRds.TAWaitAFCheckTimer = 10;  // 1s
            }
        }
    }
}
/**********************************************************
 * @function	Tuner_RdsOutput
 * @brief  	Output Rds Information
 * @param  	
 * @retval 	None
 **********************************************************/
void Tuner_RdsOutput(void)
{
    static uint8_t SavedTP = 0xFF;
    static uint8_t SavedTA = 0xFF;
    uint8_t RdsInfo = 0; 
    uint8_t Temp;
     
    //Filter: states that no need rds disposal
    if((RDS_SET_OFF == (Tuner_Api_GetRdsSetting())) || ((Tuner_Api_GetBand()) > TUNER_FM_END))
    {
        return;
    }

    //Filter:
    if(TUNER_SYS_RUN != TunerGetSysState())
    {
        return;
    }  

    //Sync Icon Flags: Rds Icon, TA, TP, AF
    if(RdsStation)
    {
        if(sRds.IconDisp == 0)
        {
            sRds.IconDisp = 1;
            //Update Rds Icon:Set
        }
    }
    else if(sRds.IconDisp != 0)
    {
        sRds.IconDisp = 0;
        //Update Rds Icon:Clear
    }

    if(sRds.F_GetNewTP)
    {
        sRds.F_GetNewTP = 0;
        //Update TP Icon
        if(SavedTP != sRds.TPValid)
        {
            _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_RDS_UPD_STATUS,&sTunerDat);
            SavedTP = sRds.TPValid;
            RdsInfo = 1;
        }
    }

    if(sRds.F_GetNewTA)
    {
        sRds.F_GetNewTA = 0;
        //Update TA Icon
        if(SavedTA != sRds.TAValid)
        {
            if(0 == RdsInfo)
                _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_RDS_UPD_STATUS,&sTunerDat);
            SavedTA = sRds.TAValid;
        }
    }

    if(sTuner.uSeekState.SsTotal)  
        return;

    if(sRds.F_GetNewPty) //Output Newly PTY Info
    {
        sRds.F_GetNewPty = 0;	
        if(sTuner.PtyChk != sRds.PtyValid)
        {
            _SendFullMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_RDS_UPD_CURRENT_PTY,sRds.PtyValid,0,0,0);
            sTuner.PtyChk = sRds.PtyValid;
        }
    }	

    if(sRds.F_GetNewPS) //Output Newly PS Info
    {
        sRds.F_GetNewPS = 0;
        for(Temp = 0; Temp < 8; Temp++)
        {
            if(sRds.PS[Temp] != sTuner.DispPS[Temp])
                break;
        }
        if(Temp < 8)
        {
            _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_RDS_UPD_PS_NAME,sRds.PS);
            for(Temp = 0; Temp < 8; Temp++)
            {
                sTuner.DispPS[Temp] = sRds.PS[Temp];
            }
        }
    }
    
    if(sRds.F_GetNewRT)
    {
        sRds.F_GetNewRT = 0;
        for(Temp = 0; Temp < 64; Temp++)
        {
            if(sRds.RT[Temp] != sTuner.DispRT[Temp])
                break;
        }
        if(Temp < 64)
        {
            _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_RDS_UPD_RT,sRds.RT);
            for(Temp = 0; Temp < 64; Temp++)
            {
                sTuner.DispRT[Temp] = sRds.RT[Temp];
            }
        }
    }
}
/**********************************************************
 * @function    Tuner_OutputInfoes
 * @brief      
 * @param      
 * @retval     None
 **********************************************************/
void Tuner_OutputInfoes(void)
{
  uint8_t Temp = 0;
  TUNER_OUTPUT_MSG_CHANGE_ENUM Msg_Change_Index = OP_TUNER_CHANGE_NULL;

	if(sTuner.FuncStep <= TUNER_STARTUP_LOAD)
		return;

	if((sTuner.OpCtl > T_OP_CTL_IDLE)&&(sTuner.OpCtl <= T_OP_CTL_EXECUTE))
		return;
	
    //Output:Rds Related Infoes...
    Tuner_RdsOutput();

    //Output Current Band
    if(sTuner.BandChk != TUNER_CURRENT_BAND)
    {
        sTuner.BandChk = TUNER_CURRENT_BAND;
//    _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENT_BAND,&sTunerDat);
#ifdef D_TUNER_LIST
    //Check Got Valid Station?
    if(TUNER_BAND_FM)
    {
      sTunerKeep.ListNum = sTunerKeep.FmListNum;
      for (Temp = 0; Temp < sTunerKeep.ListNum; Temp++)
      {
        sTunerKeep.ValidList[Temp] = sTunerKeep.FmList[Temp];
      }
    }
    else if(TUNER_BAND_AM)
    {
      sTunerKeep.ListNum = sTunerKeep.AmListNum;
      for (Temp = 0; Temp < sTunerKeep.ListNum; Temp++)
      {
        sTunerKeep.ValidList[Temp] = sTunerKeep.AmList[Temp];
      }
    }
#endif//D_TUNER_LIST
    if(OP_TUNER_CHANGE_NULL == Msg_Change_Index)
    {
      Msg_Change_Index = OP_TUNER_CHANGE_BAND;
    }

  }
    //Output Current Preset
    if(sTuner.PresetChk != TUNER_CURRENT_PRESET)
    {
        //Saved Newly Preset and Saved Band Attribute
        sTuner.PresetChk = TUNER_CURRENT_PRESET;
        //Update Band Attribute
        sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Preset = sTuner.PresetChk;
    if(OP_TUNER_CHANGE_NULL == Msg_Change_Index)
    {
      Msg_Change_Index = OP_TUNER_CHANGE_PRESET;
    }
    }

    //Output Current Frequency
    if(sTuner.FreqChk != TUNER_CURRENT_FREQ)
  {
    //Saved Newly Frequency and Saved Band Attribute
    sTuner.FreqChk = TUNER_CURRENT_FREQ;
    //Updata Band Attribute
    sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq = sTuner.FreqChk;    
    if(sTunerKeep.ValidList[TUNER_CURRENT_PRESET - 1] != TUNER_CURRENT_FREQ)
    {
      //Sync Valid List Highlight
      sTunerKeep.ValidHighlight = 0; 
#ifndef D_TUNER_LIST    //Update List Highlight    
      for(Temp = 0; Temp < sTunerKeep.ValidNumber; Temp++)
      {
        if(sTunerKeep.ValidList[Temp] == TUNER_CURRENT_FREQ)
        {
          sTunerKeep.ValidHighlight = (Temp + 1);
          break;
        }
      }
#else
      for(Temp = 0; Temp < sTunerKeep.ListNum; Temp++)
      {
        if(sTunerKeep.ValidList[Temp] == TUNER_CURRENT_FREQ)   
        {
          sTunerKeep.ValidHighlight = (Temp + 1);
          break;
        }
      }
      TUNER_CURRENT_PRESET = sTunerKeep.ValidHighlight;
#endif
    }
    if(OP_TUNER_CHANGE_NULL == Msg_Change_Index)
    {
      Msg_Change_Index = OP_TUNER_CHANGE_FREQ;
    }
  }

  //Output Seek State
  if(sTuner.StateChk != sTuner.uSeekState.SsTotal)
  {
    sTuner.StateChk = sTuner.uSeekState.SsTotal;
    if(OP_TUNER_CHANGE_NULL == Msg_Change_Index)
    {     
      Msg_Change_Index = OP_TUNER_CHANGE_STATE;
    }
  }

  //Output Setting
  if(sTuner.SettingChk != sTunerDat.sSetting.Total) 
  {
    sTuner.SettingChk = sTunerDat.sSetting.Total;
    if(OP_TUNER_CHANGE_NULL == Msg_Change_Index)
    {
      Msg_Change_Index = OP_TUNER_CHANGE_SETTING;
    }
  }
    
    //Output Current Signal Strength
    #if 0
    if(SignalStr != sTuner.SignalStr)
    {
        SignalStr = sTuner.SignalStr;
        _SendFullMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_SIGNAL_STR,sTuner.SignalStr,0,0,0);
    }
    #else
    if(sTuner.PeriodicOut >= TunerDelay(T2S))
    {
    sTuner.PeriodicOut = 0;
    if(OP_TUNER_CHANGE_NULL == Msg_Change_Index)
    {
      Msg_Change_Index = OP_TUNER_CHANGE_PERIODICOUT;
    }
  }
    #endif
    

  //Sync All Datum
  if(sTuner.bSyncData)
  {
    Msg_Change_Index = OP_TUNER_CHANGE_SYNCDATA;
    sTuner.bSyncData = 0;
  }
  
  switch(Msg_Change_Index)
  {
    case OP_TUNER_CHANGE_NULL:
      break;
    case OP_TUNER_CHANGE_BAND:
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_LIST,&sTunerKeep);
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_HIGHLIGHT,&sTunerDat);
      break;
    case OP_TUNER_CHANGE_PRESET:
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENT_PRESET,&sTunerDat);
      break;
    case OP_TUNER_CHANGE_SIGNALSTR:
      break;
    case OP_TUNER_CHANGE_STATE:
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_SEEK_STATE,&sTunerDat);
      break;
    case OP_TUNER_CHANGE_FREQ:
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_HIGHLIGHT,&sTunerDat);
      break;
    case OP_TUNER_CHANGE_SETTING:
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENTLY,&sTunerDat);
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_SETTING,&sTunerDat);
      break;
    case OP_TUNER_CHANGE_PTY:
      break;
    case OP_TUNER_CHANGE_PERIODICOUT:
      _SendFullMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_SIGNAL_STR,sTuner.SignalStr,0,0,0);
      break;
    case OP_TUNER_CHANGE_SYNCDATA:
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_SETTING,&sTunerDat);
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENTLY,&sTunerDat);
#ifndef D_TUNER_LIST 
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_ONE_PRESET,&sTunerDat);
#endif
      _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_LIST,&sTunerKeep);
      break;
    default:
      break;
  }
  Msg_Change_Index = OP_TUNER_CHANGE_NULL;
}


void Tuner_DataSync(eSOURCE_TYPE eType)
{
    Tuner_debug(_T("----------TunerSync\n"));
    sTuner.bSyncData = 1;
}

void Tuner_Ctrl_Pause(void)
{
      uint8_t Result = SUBLAYER_DOING;
	  
	if(sTunerKeep.bBakPause != sTunerKeep.bPausestate)
	{
		sTunerKeep.bBakPause = sTunerKeep.bPausestate;
		sTuner.bTrigger = 1;
		
		if(sTuner.bSyncData)
		{
			
		}
		else
		{
			_SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_CURRENT_FREQ,&sTunerDat);
		}
	}
		
	if(sTuner.bTrigger)
	{
		if(sTunerKeep.bPausestate)
		{
			Result = Hero_SrcScalerToZero(SYSTEM_FRONT);
		}
		else
		{
			Result = Audio_SetSrcScaler();
		}

		if(Result == SUBLAYER_DONE)
		{
			sTuner.bTrigger = 0;
		}
	}
}
/**********************************************************
 * @function    Tuner_Manager
 * @brief                     
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_Manager(void)
{
    //Tuner Function Control
    if(TUNER_SYS_SLEEP != TunerGetSysState())
    {
        // Main Function Gather, Include State Control
        (*Tab_TunerFunc[((sTuner.FuncStep >> 4) & 0x0F)])();    

        Tuner_OpDisposal();

        // Update Infoes
        Tuner_UpdateInfoes();

        // Output Infoes
        Tuner_OutputInfoes();

        //BackGround Valid Frequency List Scan      
//        Tuner_ValidScan();  
		
//        Rds_Main();
        //Tuner_TaCheck();
    }

 	Tuner_Ctrl_Pause(); 	
}
/**********************************************************
 * @function    Tuner_MsgHandler
 * @brief      Message Handler
 * @param      NULL
 * @retval     NULL
 **********************************************************/
eSOURCE_MSG_RETURN Tuner_GlbMsgHandler(eSOURCE_TYPE eType,tMSG_BUF* pMsg)
{
    uint16_t Op = pMsg->iSid;
    if(pMsg->Id == MS_PM_STATE)
    {
        uint8_t bAntPwr = FALSE;
        switch(Op)
        {
            case OP_PM_STATE_ON:  
                //yangyan --2014.08.07
                if(0 == sTuner.PwrState)
                {
                    Tuner_Active(SRC_TYPE_TUNER,SRC_ZONE_FRONT);
                }
                sTuner.PwrState = 1;
                bAntPwr = TRUE;
                break;
                
            case OP_PM_STATE_STANDBY:
                if(1 == sTuner.PwrState)   //Goto Standby Mode, No Source Switch to TUNER, so switch according POWER STATE
                {
                	if(sAudio.SysChannel == 0)
                	{
	                	Tuner_Deactive(SRC_TYPE_TUNER,SRC_ZONE_FRONT);
	                	sTuner.PwrState = 0;//yangyan --2014.08.07
                	}
                }
                break;
    	     //case OP_PM_STATE_BATERR: //snake20160922 ??S401
            case OP_PM_STATE_WAIT_SLEEP: //Do Nothing...
      			//_SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_SEEK_STATE,&sTunerDat);
                if(1 == sTuner.PwrState)   //Goto Standby Mode, No Source Switch to TUNER, so switch according POWER STATE
                {
                	if(sAudio.SysChannel == 0)//当前通道为tuner的时候,才进行stop
                	{
	                    Tuner_Deactive(SRC_TYPE_TUNER,SRC_ZONE_FRONT);
	                    sTuner.PwrState = 0;
                	}
                }
                #if 0
                sTuner.PwrState = 0;
                if(TunerGetSysState() <= TUNER_SYS_PWROFF) 
                {
                    //Save Tuner Block
                    if(sTuner.bDatumReady)
                    {
                        OS_CreateRamChkBlock((void*)&sTunerDat,
                                    (sizeof(TUNER_DATUM_STRUCT)-sizeof(uint16_t)),
                                    (void*)&(sTunerDat.CheckSum));
                    }
                    sTuner.SysBakState = sTuner.SysState; //Bak Currently Tuner System State
                    TunerSetSysState(TUNER_SYS_PWROFF);
                    Tuner_GotoStep(TUNER_FUNC_PWROFF);
                }
                #endif
                break;
    
            default:
                sTuner.PwrState = 0;
			if((sTuner.uSeekState.sSsBitMap.bAutoMemSeek))
			{
		            Tuner_SortStationAccordFreq(sTuner.asAmsBuff, sTuner.AmsValidStaNum); // 按频率大小排序
		            Tuner_SortPreset();
			}
                //if(TunerGetSysState() <= TUNER_SYS_PWROFF) 
                {
                    //Save Tuner Block
                    if(sTuner.bDatumReady)
                    {
                        OS_CreateRamChkBlock((void*)&sTunerDat,
                                    (sizeof(TUNER_DATUM_STRUCT)-sizeof(uint16_t)),
                                    (void*)&(sTunerDat.CheckSum));
                    }
                    sTuner.SysBakState = sTuner.SysState; //Bak Currently Tuner System State
                    sTuner.ZoneState = 0x00;
                    TunerSetSysState(TUNER_SYS_SLEEP);  
                }
    
            
                break;
        }
        PM_UnitPowerSet(PM_UNIT_ANT,bAntPwr);
    }
    else if(pMsg->Id == MS_SRC_SYS_CMD)
    {
        switch(Op)
        {
             //4 Tuner Related Message
            case OP_SRC_DATA_SYNC:
            {
                Tuner_DataSync(SRC_TYPE_TUNER);
                Tuner_debug(_T("Sync TUNER DATA============\n"));
            }
            break;
        }
    }
    else if(pMsg->Id == MS_SYS_LOAD_FACTORY_INFO)
    {
		Tuner_VariableReset(); //Pre-Reset Variable for System Sync Usage...
    }
   else if(pMsg->Id == MS_SYS_AUDIO_STATE)
	{
	    //yangyan --2014.08.07
	    if(OP_DEV_STATE_CONNECTED == Op
               || OP_DEV_STATE_NORMAL== Op)
               sTuner.DevInit = TRUE;
            else 
		sTuner.DevInit = FALSE;
	}

    return 0;
}


const uint8_t la_KeyToTunerMsgMap[][2]=
{
    CK_NUM1,                   OP_TUNER_SET_PRESET1,
    CK_NUM2,                   OP_TUNER_SET_PRESET2,
    CK_NUM3,                   OP_TUNER_SET_PRESET3,
    CK_NUM4,                   OP_TUNER_SET_PRESET4,
    CK_NUM5,                   OP_TUNER_SET_PRESET5,
    CK_NUM6,                   OP_TUNER_SET_PRESET6,
//    CK_STEP_DEC,            OP_TUNER_SET_STEP_DEC,
    CK_LEFT,                OP_TUNER_SET_STEP_DEC,
    CK_RIGHT,               OP_TUNER_SET_STEP_INC,
 //   CK_STEP_INC,            OP_TUNER_SET_STEP_INC,

    CK_UP,                  OP_TUNER_SET_PRESET_INC,
    CK_NEXT,                OP_TUNER_SET_PRESET_INC,
    CK_PRE,                 OP_TUNER_SET_PRESET_DEC,
    CK_DOWN,                OP_TUNER_SET_PRESET_DEC,
    CK_SCAN,                OP_TUNER_SET_SCAN,
    CK_SEEK_DOWN,           OP_TUNER_SET_SEEK_DEC,
    CK_SEEK_UP,             OP_TUNER_SET_SEEK_INC,

    CK_NONE,                CK_NONE,
};


eSOURCE_MSG_RETURN Tuner_MsgHandler(eSOURCE_TYPE eType,eSOURCE_ZONE eZone,tMSG_BUF* pMsg,bool bSrcActive)
{
    tMSG_BUF tBuff;
    eSOURCE_MSG_RETURN re = SRC_MSG_ANALYZE;
    uint16_t Op = pMsg->iSid;
    
    tBuff.iSid = 0;
    tBuff.uData.p_cData = pMsg->uData.p_cData;
    
    switch(pMsg->Id)  
    {

        case MS_SRC_DISTRIBUTE_CMD:
            if((uint8_t)(Op>>8) == (uint8_t)eType)
            {
                tBuff.iSid = (uint8_t)Op;
		 re = SRC_MSG_IGNORE;
            }
            break;
        
        case MS_INPUT_KEY:
        case MS_INPUT_FIR:
            re = SRC_MSG_IGNORE;
		#if 0	/*TUNER 不自动处理MCU的按键，只处理UI下发的*/
			if((lc_bSrcKeyOpTransTab[(uint8_t)Op]))
				//&&((uint8_t)Op != OP_KEY_ACTION_LP))
			{
				uint8_t cKey = tBuff.uData.a_cData[0];
				uint8_t i;
				
				if((uint8_t)Op == OP_KEY_ACTION_LP)
				{
					if(CK_PRE == cKey )
						cKey	 = CK_SEEK_DOWN ;   
					else if (CK_NEXT == cKey )
						cKey	 = CK_SEEK_UP ;
				}
				
		                for(i=0;;i++)
		                {
		                    if(la_KeyToTunerMsgMap[i][0] == CK_NONE)break;
		                    if(la_KeyToTunerMsgMap[i][0]== cKey)
		                    {
		                        tBuff.iSid = la_KeyToTunerMsgMap[i][1];
		                        re = SRC_MSG_ANALYZE;
		                    }
		                }
			}
			#endif
           
        break;
        case MS_INPUT_UI:
        {
		re = SRC_MSG_RETURN_N;
            switch(Op)
            {
                case UICC_FREQ_LIST_TS:
                {
                    uint8_t cIdx = (pMsg->uData.a_cData[0])& 0x3f;
                    uint8_t cType = (pMsg->uData.a_cData[0])>>6;
					hmi_printf(_T("UICC_FREQ_LIST_TS:--cIdx = %d,cType = %d\n",cIdx,cType));
                    if(TUNER_PRESET_MAX >= cIdx)
                    {
                        if(0 == cType)
						{
							tBuff.iSid = OP_TUNER_SET_PRESET1+cIdx;
							if(tBuff.iSid>=OP_TUNER_SET_PRESET6)//snake20160914
								tBuff.iSid = OP_TUNER_SET_PRESET6;
                        }
                        else if(3 == cType)
						{
							tBuff.iSid = OP_TUNER_SET_SAVE1+cIdx;
							if(tBuff.iSid>=OP_TUNER_SET_SAVE6) //snake20160915
								tBuff.iSid = OP_TUNER_SET_SAVE6;
                        }
                    }
                   
                 }
                break;    
        
                case UICC_SCAN_TS:		
                    tBuff.iSid = OP_TUNER_SET_SCAN;
                    break;    
        
                case UICC_ASPS_LONG_TS:	
                    tBuff.iSid = OP_TUNER_SET_AMS;
                    break;
                case UICC_ASPS_TS:		
                    tBuff.iSid = OP_TUNER_SET_PRESET_SCAN;
                    break;    
                    
                case UICC_BAND_TS: // 0: inc, SEL: 12345	
                /*
                    if(0 == pMsg->uData.a_cData[0])
                    {
                        tBuff.iSid = OP_TUNER_SET_BAND_INC;
                    }
                    else if(pMsg->uData.a_cData[0] <= 5)
                    {
                        tBuff.iSid = OP_TUNER_SET_BAND_SEL;
                        tBuff.uData.a_cData[0] = pMsg->uData.a_cData[0] - 1;
                    }
                    */
                    tBuff.iSid = OP_TUNER_SET_BAND_INC;
                    break;    
        
                case UICC_STEP_DOWN_TS:		
                    tBuff.iSid = OP_TUNER_SET_STEP_INC ;
                    break;
        
                case UICC_STEP_UP_TS: 		
                    tBuff.iSid = OP_TUNER_SET_STEP_DEC ;
                    break;    
        
                case UICC_NEXT_TS:			
                    tBuff.iSid = OP_TUNER_SET_SEEK_INC ;
                    break;
					
                case UICC_PREV_TS:		
                    tBuff.iSid = OP_TUNER_SET_SEEK_DEC;
                    break;    

                case UICC_PREV_PRESET_TS:
                    tBuff.iSid = OP_TUNER_SET_PRESET_DEC ;
                    break;
                            
                case UICC_NEXT_PRESET_TS:
                    tBuff.iSid = OP_TUNER_SET_PRESET_INC ;
                    break;
		   case UICC_RADIO_INFO_TS:
		   	 tBuff.iSid = OP_TUNER_SET_SYNC ;
		   	break;
                case UICC_AF_TS:
                    tBuff.iSid = OP_TUNER_SET_AF ;
                    break;
                    
                case UICC_TA_TS:
                    tBuff.iSid = OP_TUNER_SET_TA ;
                    break;
                    
                case UICC_REG_TS:
                    tBuff.iSid = OP_TUNER_SET_REG ;
                    break;
                    
                case UICC_EON_TS:
                    tBuff.iSid = OP_TUNER_SET_EON ;
                    break;
                    
                case UICC_PTY_ENABLE_TS:
                    tBuff.iSid = OP_TUNER_SET_PTY ;
                    break;    
        
                case UICC_PTY_TS:
                    tBuff.iSid = OP_TUNER_SET_PTY_SEL ;
                    break;
                    
                case UICC_LOC_TS:
                    tBuff.iSid = OP_TUNER_SET_LOC_DX ;
                    break;   
                    
                case UICC_PTY_SEEK_TS:
                    tBuff.iSid = OP_TUNER_SET_PTY_SEEK ;
                break;
		   case UICC_RADIO_PAUSE:
                    tBuff.iSid = OP_TUNER_SET_PAUSE ;
                break;
			
		  case UICC_STOP_SEEK:
		  	tBuff.iSid = OP_TUNER_STOP_SEEK ;
		  	break;
			
                default:
                    re = SRC_MSG_IGNORE;
                      
            }
        }
        break;
        default:;
             
    }
    if( SRC_ZONE_REAR == eZone  
        || 0 == bSrcActive 
        || 0 ==  tBuff.iSid
        || TUNER_SYS_RUN != (TunerGetSysState()))
    {
        return SRC_MSG_IGNORE;
    }
    Tuner_InputLogic(&tBuff);
    
    return re;
}
/**********************************************************
 * @function    Tuner_Task
 * @brief      A Periodic task for Tuner module
 * @param      EVENT Evt
 *                 eTASK_STATE eState
 * @retval     NULL
 **********************************************************/
void Tuner_Task(eSOURCE_TYPE eType,EVENT Evt, eTASK_STATE eState)
{
    if(Evt & EVT_COLD_INIT)    //Cold Start, Reset Parameters
    {
        Tuner_ColdInit();
    }

    if(Evt & EVT_WARM_INIT)    //Warm Start, Initialize Parameters
    {
        Tuner_WarmInit();
    }
    
    if(Evt & EVT_TASK_TICK_READY)
    {
        Tuner_VirTimer();//Tuner Virtual Timer

        Tuner_Manager();
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

uint8_t l_cTunerSeriesRunflag;
#pragma section data "no_init" begin  

tSOURCE l_tSourceTuner; //Tuner Source Node...
tSOURCE l_tSourceRDSTA;
#pragma section data "no_init" end 


const tSOURCE_CTRL_BLOCK lc_tSrcTunerAttri = 
{
    /*function*/
    Tuner_ResetInit,
    Tuner_DataSync,
    Tuner_Task,
    NULL,
    Tuner_Active, //start
    Tuner_Deactive, //stop
    Tuner_MsgHandler,
    Tuner_GlbMsgHandler,
};

/**********************************************************
 * @function    Tuner_Deactive
 * @brief      Deactive Tuner Source
 * @param      eSOURCE_ZONE sZone
 * @retval     NULL
 **********************************************************/
#define _TUNER_FLAG_ la_cSrcFlagDefault[SRC_TYPE_TUNER]
#define _RDSTA_FLAG_ la_cSrcFlagDefault[SRC_TYPE_RDS_TA]
void Tuner_CreateSrc(void) 
{
    uint8_t i;

    i = SRC_Create(&l_tSourceTuner,SOURCE_TUNER,SRC_TYPE_TUNER,"TUNER",&lc_tSrcTunerAttri,SRC_PRI_NORMAL,_TUNER_FLAG_,&l_cTunerSeriesRunflag);
    i = SRC_Create(&l_tSourceRDSTA,SOURCE_TUNER,SRC_TYPE_RDS_TA,"RDS TA",NULL,SRC_PRI_RDS,_RDSTA_FLAG_,&l_cTunerSeriesRunflag);
}

#undef TASK_TUNER_C

