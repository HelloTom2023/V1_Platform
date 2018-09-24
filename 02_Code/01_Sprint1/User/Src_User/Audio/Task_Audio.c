/**********************************************************
 * @file        Task_Audio.c
 * @purpose    
 * @version    0.01
 * @date        10. July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          10.July.2012        v0.01        created
 *  
  **********************************************************/
#define TASK_AUDIO_C


/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= Function Announcement  =================== */

/* ========================= public variable ==================== */

/* ========================= private variable =================== */

//extern tEEP_DATA_BLOCK l_tEepAudioRomData;
//extern const tEEP_DATA lc_tEepAudioRom;

#if CAN_DEBUG_AUDIO
CanMsgStruct AudioDbgMsg;
#endif

// Function Array
void (*const Tab_AudioFunc[])(void) = 
{
    Audio_Func_Startup,
    Audio_Func_Idle,
    Audio_Func_PwrOff,
};
/* ========================= Code Part =================== */


/**********************************************************
 * @function    Audio_GotoStep
 * @brief      Switch Function Control Step
 * @param      uint8_t x : Step Will Goto                    
 * @retval     None
 **********************************************************/
void Audio_GotoStep(uint8_t x)
{
    sAudio.FuncStep = x;
    sAudio.MidStep = 0;
}
/**********************************************************
 * @function    Audio_Func_Error
 * @brief      Tuner Specific Step Execute Error, Judge Error or Do Retry
 *            >>Debug Usage 
 * @param      uint8_t ErrType: Error Type                    
 * @retval     None
 **********************************************************/
 void Audio_Func_Error(uint8_t ErrType)
{
    //Debug Usage!!!
    if(SUBLAYER_STEP_ERROR ==  ErrType)
    {

    }
    else if(SUBLAYER_PARAMETER_ERROR ==  ErrType)
    {
        
    }

    //Retry....
    sAudio.FuncRetryCnt++;
    if(sAudio.FuncRetryCnt < 4)        //Retry three times 
    {
        sAudio.MidStep = OPERATION_0;    // Go Back to Last Step
    }
    else
    {
        // Reserved for Error Disposal
    }
}
/**********************************************************
 * @function    Audio_Func_Startup
 * @brief      Audio Startup: Include AMP startup ,ASP startup and 
 *            audio matrix startup    
 * @param      None                    
 * @retval     None
 **********************************************************/
void Audio_Func_Startup(void)
{
    uint8_t Result = SUBLAYER_DOING;

    AudioSetSysState(AUDIO_SYS_STARTUP);
    sAudio.StarUp = 0;
    
    switch(sAudio.FuncStep)
    {
        //Audio Startup start, Initial specific parameters and Hard Mute Audio Output
        case AUDIO_STARTUP_INIT:
            sAudio.bDatumReady = 0;
            Audio_GotoStep(AUDIO_STARTUP_LOAD);
            Audio_FastHardMute(MUTE_ON);//yangyan --2014.08.07
            sAudio.FuncDelay = AudioDelay(T500MS);//delay 100ms
            sAudio.AspCheckCnt = 0;  
            sAudio.AspCheckNum = 0;
            break;

        case AUDIO_STARTUP_LOAD:
            if(sAudio.FuncDelay)return;//yangyan --2014.08.07
            //Change the init process:ASP->Switcher->AMP
            Result = Audio_LoadDatum();
            if(SUBLAYER_DONE == Result)
            {
                Audio_GotoStep(AUDIO_STARTUP_ASP);//yangyan --2014.08.07
                AmpCtl.Module = MODULE_EXIST;
                PM_UnitPowerSet(PM_UNIT_AUDIO,TRUE);
                sAudio.FuncDelay = AudioDelay(T50MS);//delay 20ms//yangyan --2014.08.07
                if( AUDIO_ASP_HERO != sAudioKeep.AspModule)  
                {
                    sAudio.AspCheck = 1; // Start Asp Module Checking
                    sAudioKeep.AspModule = AUDIO_ASP_HERO;   
                }
                else
                {
                    sAudio.AspCheck = 0; 
                }
            }
            break;

        //AMP Startup: Power & Reset & Initialize
        case AUDIO_STARTUP_AMP:
            if(sAudio.FuncDelay)return;//yangyan --2014.08.07
            
            Result = Audio_AmpStartup();
            if(SUBLAYER_DONE == Result)
            {
                sAudio.ReadyState |= AMP_READY; //Set Ready Flag 
                Audio_GotoStep(AUDIO_STARTUP_END);
                sAudio.FuncDelay = AudioDelay(T1P5S);//delay 100ms
                
            }
            break;

        //ASP Startup: Power & Reset & Initialize
        case AUDIO_STARTUP_ASP:
            Result = Audio_AspStartup();
            if(sAudio.AspCheckNum > 10)
            {
                _SendMsgToHMI(MS_SYS_AUDIO_STATE,OP_DEV_STATE_NOCONNECT,NULL);
                _SendMsgToHMI(MS_SYS_DEV_TYPE,DEV_IDX_TUNER,0);
                Audio_GotoStep(AUDIO_STARTUP_INIT);
            }
            else if(SUBLAYER_DONE == Result)
            {
                sAudio.ReadyState |= ASP_READY; //Set Ready Flag
                Audio_GotoStep(AUDIO_STARTUP_SWITCH);
            }
            break;

        //Audio Matrix IC Startup: Power & Reset & Initialize    
        case AUDIO_STARTUP_SWITCH:
            Result = Audio_SwitchStartup();
            if(SUBLAYER_DONE == Result)
            {
                sAudio.ReadyState |= SWITCH_READY;
                Audio_GotoStep(AUDIO_STARTUP_AMP);
            }
            break;

        //Audio Startup OK
        case AUDIO_STARTUP_END:   //Feedback Power On Done to Power Task
            if(sAudio.FuncDelay)return;
            sAudio.ReadyState |= AUDIO_READY;
            Audio_GotoStep(AUDIO_FUNC_IDLE);
            _SendMsgToHMI(MS_SYS_AUDIO_STATE,OP_DEV_STATE_NORMAL,NULL);
            _SendMsgToHMI(MS_SYS_DEV_TYPE,DEV_IDX_TUNER,sAudioKeep.AspModule);
            IO_ResetState(IO_IDX_TEL_MUTE_DET,INVALID);
	    if( l_tMediaCB.uDevFlag.field.bUnLocked)		
            Audio_FastHardMute(MUTE_OFF);  //yangyan --2014.08.07
            sAudio.StarUp = 1;
            sAudio.SyncStep = 0;
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }
    
    // Step Error Disposal
    if(Result > SUBLAYER_DONE)
    {
        Audio_Func_Error(Result);
    }
#if CAN_DEBUG_AUDIO
	AudioDbgMsg.Data[0] = sAudio.FuncStep;
	AudioDbgMsg.Data[1] = sAudio.AspCheck;
       AudioDbgMsg.Data[2] = sAudioKeep.AspModule;
	AudioDbgMsg.Data[3] =  sAudio.ReadyState;
	AudioDbgMsg.Data[4] = sAudio.SysChannel;
#endif
}
/**********************************************************
 * @function    Audio_Func_Idle
 * @brief      Audio Idle State
 * @param      None                    
 * @retval     None
 **********************************************************/
void Audio_Func_Idle(void)
{
    AudioSetSysState(AUDIO_SYS_RUN);
    
    IO_Scan(IO_IDX_TEL_MUTE_DET,PIN_INPUT);
    //Update UBass Scaler
    if(sAudio.UltraScaler != sAudioDat.sInfo.UbassTargetLev)
    {
        sAudioDat.sInfo.UbassTargetLev = sAudio.UltraScaler;
        if(UBASS_ENABLE == sAudioDat.sAdv.sUltraBass.Setting)    
        {
                Audio_OpQueueIn(AUDIO_COMMON_UBASS);
            sAudio.UltraBassMask |= UBASS_MASK_SCALER;
        }
    }
}
/**********************************************************
 * @function    Audio_Func_PwrOff
 * @brief      Power Off Audio Task, Save and Reset Parameters
 *            Close Power and Feedback
 * @param      None                    
 * @retval     None
 **********************************************************/
void Audio_Func_PwrOff(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
    if(DelayNotExpired(sAudio.FuncDelay))
        return;
    
    AudioSetSysState(AUDIO_SYS_PWROFF);
    
    switch(sAudio.FuncStep)
    {
        // Sort Currently Situation, and Initialize Some Parameters 
        case AUDIO_PWROFF_SORT:
            {
//            uint8_t i;
//            for(i = 0; i < 3; i++)
//            {
//                sAudioDat.sAdv.sCustomXover[i].CoF = sAudioKeep.sBakXover[i].CoF;
//                sAudioDat.sAdv.sCustomXover[i].Level = sAudioKeep.sBakXover[i].Level;
//                sAudioDat.sAdv.sCustomXover[i].Slope = sAudioKeep.sBakXover[i].Slope;
//            }
//            for(i = 0; i < DELAY_LINE_MAX; i++)
//            {
//                sAudioDat.sAdv.DelayCustom[i] = sAudioKeep.BakDelay[i];
//            }
//            for(i = 0; i < GEQ_MAX_NUM; i++)
//            {
//                sAudioDat.sGeq.sBuffer[i].CF = sAudioKeep.sBakGeq[i].CF;
//                sAudioDat.sGeq.sBuffer[i].Gain = sAudioKeep.sBakGeq[i].Gain;
//                sAudioDat.sGeq.sBuffer[i].Q = sAudioKeep.sBakGeq[i].Q;
//                sAudioDat.sGeq.GainTbl[3 * i + 0] = sAudioKeep.sBakGain[3 * i + 0];
//                sAudioDat.sGeq.GainTbl[3 * i + 1] = sAudioKeep.sBakGain[3 * i + 1];
//                sAudioDat.sGeq.GainTbl[3 * i + 2] = sAudioKeep.sBakGain[3 * i + 2];
//            }
            Audio_FastHardMute(MUTE_ON);
            sAudio.ReadyState = 0x00;
            Audio_GotoStep(AUDIO_PWROFF_SAVE);
            }
            break;

        //Save Parameters to eeprom
        case AUDIO_PWROFF_SAVE:
            Audio_GotoStep(AUDIO_PWROFF_POWER);  
            sAudio.FuncDelay = AudioDelay(T100MS);
            break;

        //Close Related Power
        case AUDIO_PWROFF_POWER:
            PM_UnitPowerSet(PM_UNIT_AUDIO,FALSE);
            Audio_GotoStep(AUDIO_PWROFF_END);
            break;

        //Power Off Ends!
        case AUDIO_PWROFF_END:
            AudioSetSysState(AUDIO_SYS_SLEEP);
            Audio_GotoStep(AUDIO_FUNC_SLEEP);
            OS_TaskStop(TASK_ID_AUDIO); // Stop Audio Task
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }
    
    // Step Error Disposal
    if(Result > SUBLAYER_DONE)
    {
        Audio_Func_Error(Result);
    }
}
/**********************************************************
 * @function    Audio_ResetInfoVariable
 * @brief      Reset Info: by hand or read from eeprom
 * @param      None
 * @retval     None
 **********************************************************/
void Audio_ResetInfoVariable(void)
{
    uint8_t i;
    extern tEEP_DATA_BLOCK l_tEepSysRomData;
    //4 Basic Audio Settings...

    sAudioDat.sInfo.ChanModeSet = AUDIO_2CH_MODE;
    sAudioDat.sInfo.SwCenMode = OUT_SW_STEREO;
    //Volume & Tone 
    sAudioDat.sBasicBK.DefaultMediaVolume =  g_tSysRomData.tAudioBlock.SysVol;
    sAudioDat.sBasicBK.DefaultNaviVol = g_tSysRomData.tAudioBlock.NaviVol;
#ifdef D_BT_CSR    
    sAudioDat.sBasicBK.DefaultPhoneVol = 30;  //Increase CSR BT Volume
#else
    sAudioDat.sBasicBK.DefaultPhoneVol = g_tSysRomData.tAudioBlock.BtVol;
#endif
    sAudioDat.sBasicBK.DefaultPromptVol = g_tSysRomData.tAudioBlock.AppVol;
    sAudioKeep.SysVol = sAudioDat.sBasicBK.DefaultMediaVolume;
    sAudioKeep.NaviVol = sAudioDat.sBasicBK.DefaultNaviVol;
    sAudioKeep.BtVol = sAudioDat.sBasicBK.DefaultPhoneVol;
    sAudioKeep.AppVol = sAudioDat.sBasicBK.DefaultPromptVol;
    sAudioKeep.CurrentlyVol = sAudioKeep.SysVol;
    sAudioKeep.RearVol = sAudioKeep.SysVol;    
    sAudioDat.sInfo.VolCurveDelta = 14;//12;//18;//26 //Default Val
    
    sAudioDat.sBasic.sBass.Gain = g_tSysRomData.tAudioBlock.BassGain;
    sAudioDat.sBasic.sBass.CF = 0;
    sAudioDat.sBasic.sBass.Q = Q_1P0;
    sAudioDat.sBasic.sMid.Gain = g_tSysRomData.tAudioBlock.MidGain;
    sAudioDat.sBasic.sMid.CF = 0;
    sAudioDat.sBasic.sMid.Q = Q_1P0;
    sAudioDat.sBasic.sTreble.Gain = g_tSysRomData.tAudioBlock.TrebleGain;
    sAudioDat.sBasic.sTreble.CF = 0;
    sAudioDat.sBasic.sTreble.Q = Q_1P0;

    //Bal&Fad
    sAudioDat.sBasic.Balance = g_tSysRomData.tAudioBlock.Balance;
    sAudioDat.sBasic.Fader = g_tSysRomData.tAudioBlock.Fader;

    sAudio.Fader_Media = sAudioDat.sBasic.Fader;
    sAudio.Balance_media = sAudioDat.sBasic.Balance;

    //Subwoofer
    sAudioDat.sBasic.sSubWooferSwitch = SUBWOOFER_ON;
    sAudioDat.sBasicBK.sSubWoofer.CoF = XOVER_COF_80;    //Pass Through
    sAudioDat.sBasicBK.sSubWoofer.Level = 7;    //0DB
    sAudioDat.sBasicBK.sSubWoofer.Slope = XOVER_SLOPE_FLAT; 

    //CrossOVer
    sAudioDat.sAdv.XoverPreset = XOVER_PRESET_FLAT;
    sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].CoF = XOVER_COF_80;
    sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level = XOVER_LEVEL_0DB;
    sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope = XOVER_SLOPE_FLAT;
    sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].CoF = XOVER_COF_80;
    sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Level = XOVER_LEVEL_0DB;
    sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope = XOVER_SLOPE_FLAT;
    sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].CoF = XOVER_COF_80;
    sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Level = XOVER_LEVEL_0DB;
    sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope = XOVER_SLOPE_FLAT;    
    sAudioKeep.sBakXover[CO_CH_F_HPF].CoF = XOVER_COF_80;
    sAudioKeep.sBakXover[CO_CH_F_HPF].Level = XOVER_LEVEL_0DB;
    sAudioKeep.sBakXover[CO_CH_F_HPF].Slope = XOVER_SLOPE_FLAT;
    sAudioKeep.sBakXover[CO_CH_R_HPF].CoF = XOVER_COF_80;
    sAudioKeep.sBakXover[CO_CH_R_HPF].Level = XOVER_LEVEL_0DB;
    sAudioKeep.sBakXover[CO_CH_R_HPF].Slope = XOVER_SLOPE_FLAT;
    sAudioKeep.sBakXover[CO_CH_SW_LPF].CoF = XOVER_COF_80;
    sAudioKeep.sBakXover[CO_CH_SW_LPF].Level = XOVER_LEVEL_0DB;
    sAudioKeep.sBakXover[CO_CH_SW_LPF].Slope = XOVER_SLOPE_FLAT;    

    //Loudness...
    sAudioDat.sBasic.sLoudnessMode = LOUDNESS_OFF;
    sAudioDat.sBasicBK.sLoudness.BassCutOff = LDB_COF_50;
    sAudioDat.sBasicBK.sLoudness.TrebleCentre = LDT_CF_7K;

    //Beep Related ..
    sAudioDat.sAdv.BeepVol = BEEP_VOL_SET_LOW;
    sAudioDat.sInfo.BeepType = BEEP_DEFAULT_TYPE;
    sAudioDat.sInfo.BeepPos = MIX_TYPE_FRONT;     

    //Delay Line...
    sAudioDat.sAdv.CarStyle = CAR_STYLE_MIDDLE;
	
	#ifdef DEBUG_GEQ_PEQ
	sAudioDat.sAdv.DelayPreset = DELAY_PRESET_CUSTOM;
	for(i = 0; i < DELAY_LINE_MAX; i++)
	{
		sAudioDat.sAdv.DelayCustom[i] = 0;    //Reset Delay Line Setting
		sAudioKeep.BakDelay[i] = 0;
	}
	
	sAudioDat.sAdv.DelayCustom[DELAY_LINE_FL] = 0;
	sAudioDat.sAdv.DelayCustom[DELAY_LINE_FR] = 0;
	sAudioDat.sAdv.DelayCustom[DELAY_LINE_RL] = 8;
	sAudioDat.sAdv.DelayCustom[DELAY_LINE_RR] = 8;    
	#else
	sAudioDat.sAdv.DelayPreset = DELAY_PRESET_FLAT;
	for(i = 0; i < DELAY_LINE_MAX; i++)
	{
		sAudioDat.sAdv.DelayCustom[i] = 0;    //Reset Delay Line Setting
		sAudioKeep.BakDelay[i] = 0;
	}
	#endif

	/*********************************/

    //DC Filter
    sAudioDat.sAdv.DcFilter = 0;    //Default setting: OFF
    
    //Phase Shifter
    for(i = 0; i < 6; i++)
    {
        sAudioDat.sAdv.PhaseShifter[i] = 0x00;        //All Inversion OFF! 
    }
    
    //Graphic Equalizer
    sAudioDat.sBasic.Type = g_tSysRomData.tAudioBlock.Type;
    for(i = 0; i < GEQ_MAX_NUM; i++)
    {
        sAudioDat.sGeq.sBuffer[i].CF = 0;
        sAudioDat.sGeq.sBuffer[i].Gain = AUDIO_GEQ_MAX/2;
        sAudioDat.sGeq.sBuffer[i].Q = Q_1P0;
        sAudioDat.sGeq.GainTbl[3 * i + 0] = AUDIO_GEQ_MAX/2;
        sAudioDat.sGeq.GainTbl[3 * i + 1] = AUDIO_GEQ_MAX/2;
        sAudioDat.sGeq.GainTbl[3 * i + 2] = AUDIO_GEQ_MAX/2;
        sAudioKeep.sBakGeq[i].CF = 0;
        sAudioKeep.sBakGeq[i].Gain = AUDIO_GEQ_MAX/2;
        sAudioKeep.sBakGeq[i].Q = Q_1P0;
        sAudioKeep.sBakGain[3 * i + 0] = AUDIO_GEQ_MAX/2;
        sAudioKeep.sBakGain[3 * i + 1] = AUDIO_GEQ_MAX/2;
        sAudioKeep.sBakGain[3 * i + 2] = AUDIO_GEQ_MAX/2;
    }

    //Parametric Equalizer
    sAudioPeq.Type = PEQ_MODE_FLAT;
    for(i = 0; i < PEQ_MAX_NUM; i++)
    {
        sAudioPeq.sBuffer[CHANNEL_FL][i].CF = 0;
        sAudioPeq.sBuffer[CHANNEL_FL][i].Gain = PEQ_GAIN_DELTA;
        sAudioPeq.sBuffer[CHANNEL_FL][i].Q = Q_1P0;
        sAudioPeq.sBuffer[CHANNEL_FR][i].CF = 0;
        sAudioPeq.sBuffer[CHANNEL_FR][i].Gain = PEQ_GAIN_DELTA;
        sAudioPeq.sBuffer[CHANNEL_FR][i].Q = Q_1P0;
        sAudioPeq.sBuffer[CHANNEL_RL][i].CF = 0;
        sAudioPeq.sBuffer[CHANNEL_RL][i].Gain = PEQ_GAIN_DELTA;
        sAudioPeq.sBuffer[CHANNEL_RL][i].Q = Q_1P0;
        sAudioPeq.sBuffer[CHANNEL_RR][i].CF = 0;
        sAudioPeq.sBuffer[CHANNEL_RR][i].Gain = PEQ_GAIN_DELTA;
        sAudioPeq.sBuffer[CHANNEL_RR][i].Q = Q_1P0;        
    }

    //Channel Gain
    for(i = 0; i < 6; i++)
    {
        sAudioDat.sGain.ChanGainTbl[i] = 0;    //Default : 0DB
    }

    //Source Scaling
    for(i = 0; i < SS_SRC_MAX; i++)
    {
        sAudioDat.sGain.ScalerTbl[i] = (AUDIO_SRC_SCALER_MAX / 2);
    }

	sAudioDat.sGain.ScalerTbl[SS_SRC_CDBOX] = (AUDIO_SRC_SCALER_MAX / 2 + 2);
	sAudioDat.sGain.ScalerTbl[SS_SRC_DISC] = (AUDIO_SRC_SCALER_MAX / 2 - 6);	
	sAudioDat.sGain.ScalerTbl[SS_SRC_USB] = ((AUDIO_SRC_SCALER_MAX / 2));//20150819_edit
	sAudioDat.sGain.ScalerTbl[SS_SRC_TUNER] = ((AUDIO_SRC_SCALER_MAX / 2) );//snake20161107 -2
	sAudioDat.sGain.ScalerTbl[SS_SRC_SD] = ((AUDIO_SRC_SCALER_MAX / 2));//20150819_edit
	sAudioDat.sGain.ScalerTbl[SS_SRC_IPOD] = ((AUDIO_SRC_SCALER_MAX / 2) + 1);//20150819_edit
	sAudioDat.sGain.ScalerTbl[SS_SRC_NAVI] = ((AUDIO_SRC_SCALER_MAX / 2) + 4);
	sAudioDat.sGain.ScalerTbl[SS_SRC_F_AUX] = ((AUDIO_SRC_SCALER_MAX / 2 - 3));
	sAudioDat.sGain.ScalerTbl[SS_SRC_R_AUX] = ((AUDIO_SRC_SCALER_MAX / 2 - 3) );
	sAudioDat.sGain.ScalerTbl[SS_SRC_BT_MUSIC] = ((AUDIO_SRC_SCALER_MAX / 2) - 1);//3
	//sAudioDat.sGain.ScalerTbl[SS_SRC_MIRRORLINK] = ((AUDIO_SRC_SCALER_MAX / 2 + 1));//3
	sAudioDat.sGain.ScalerTbl[SS_SRC_DTV] = ((AUDIO_SRC_SCALER_MAX / 2) + 4);
	sAudioDat.sGain.ScalerTbl[SS_SRC_THIRD_APP] = ((AUDIO_SRC_SCALER_MAX / 2) - 2);

    //UltraBass
    sAudioDat.sAdv.sUltraBass.Setting = UBASS_DISABLE;
    sAudioDat.sAdv.sUltraBass.BoostLevel = 15; 
    sAudioDat.sInfo.UbassTargetLev = 12;
    sAudio.UltraScaler = 12;

    //Ach Active Buffer
    for(i = 0; i < ACH_MAX; i++)
    {
        sAudio.AchActBuffer[i] = SRC_TYPE_NUM;
    }
    sAudio.AchActRear = SRC_TYPE_NUM;

    sAudioDat.sBasic.MixAttn = MIX_ATTN_SET_HIGH;// MIX_ATTN_SET_MID;//keilee20140523
    sAudioDat.sBasic.MixPos = MIX_TYPE_FL;
}
/**********************************************************
 * @function    Audio_Variable2Eep
 * @brief      Sync Datum to Eep
 * @param      None
 * @retval     None
 **********************************************************/
void Audio_Variable2Eep(void)
{
    uint8_t i;
    
    sAudioEep.E_BeepVol = sAudioDat.sAdv.BeepVol;
    sAudioEep.E_CarStyle = sAudioDat.sAdv.CarStyle;
    for(i = 0; i < 6; i++)
    {
        sAudioEep.E_ChanGain[i] = sAudioDat.sGain.ChanGainTbl[i];
    }
    for(i = 0; i < SS_SRC_MAX; i++)
    {
        sAudioEep.E_SrcScaler[i] = sAudioDat.sGain.ScalerTbl[i];
    } 
    sAudio.bSyncToEep = 1;
}
/**********************************************************
 * @function    Audio_VariableCheck
 * @brief      Check Audio Variable
 * @param      None
 * @retval     None
 **********************************************************/
void Audio_VariableCheck(void)
{
    uint8_t i;

    audio_printf(_T("Audio_VariableCheck()\n"));
    if((sAudioDat.sBasicBK.DefaultMediaVolume > AUDIO_VOL_MAX) || (0 == sAudioDat.sBasicBK.DefaultMediaVolume))
    {
        sAudioDat.sBasicBK.DefaultMediaVolume = AUDIO_VOL_MAX/2;
    }
    if((sAudioDat.sBasicBK.DefaultNaviVol > AUDIO_VOL_MAX) || (0 == sAudioDat.sBasicBK.DefaultNaviVol))
    {
        sAudioDat.sBasicBK.DefaultNaviVol = AUDIO_VOL_MAX/2;
    }
    if((sAudioDat.sBasicBK.DefaultPhoneVol > AUDIO_VOL_MAX) || (0 == sAudioDat.sBasicBK.DefaultPhoneVol))
    {
        sAudioDat.sBasicBK.DefaultPhoneVol = AUDIO_VOL_MAX/2;
    }    
    if((sAudioDat.sBasicBK.DefaultPromptVol > AUDIO_VOL_MAX) || (0 == sAudioDat.sBasicBK.DefaultPromptVol))
    {
        sAudioDat.sBasicBK.DefaultPromptVol = AUDIO_VOL_MAX/2;
    }   
	/*自杨工增加了开关ACC对音视频的初始化后，开关ACC会执行到此部分，
	导致对大于16的音量值不记忆，先屏蔽掉， zhaowenlong, 20140821 */
  //  if((sAudioKeep.SysVol >= sAudioDat.sBasicBK.DefaultMediaVolume) /*|| (0 == sAudioKeep.SysVol)*/)
  //  {
  //      sAudioKeep.SysVol = sAudioDat.sBasicBK.DefaultMediaVolume;
 //   }
 //   else
    if(sAudioKeep.SysVol<AUDIO_VOL_MIN)//20140605keilee
    {
        sAudioKeep.SysVol = AUDIO_VOL_MIN;
    }
    else  if(sAudioKeep.SysVol>20)
    {
        sAudioKeep.SysVol = 20; //sAudioDat.sBasicBK.DefaultMediaVolume;
    }	 
#if 0
    if((sAudioKeep.NaviVol >= 25/*sAudioDat.sBasicBK.DefaultNaviVol*/)  /*|| (0 == sAudioKeep.NaviVol)*/)
    {
        sAudioKeep.NaviVol = 25; //sAudioDat.sBasic.DefaultNaviVol;
    }
    else if(sAudioKeep.NaviVol<AUDIO_VOL_MIN)
    {
        sAudioKeep.NaviVol = AUDIO_VOL_MIN;
    }
#endif
    if((sAudioKeep.BtVol >= 20/*sAudioDat.sBasicBK.DefaultPhoneVol*/) || (0 == sAudioKeep.BtVol))
    {
        sAudioKeep.BtVol = 20;
    }
    else if(sAudioKeep.BtVol<AUDIO_VOL_MIN)
    {
        sAudioKeep.BtVol = AUDIO_VOL_MIN;
    }
    if((sAudioKeep.AppVol >= 20/*sAudioDat.sBasicBK.DefaultPromptVol*/) /*|| (0 == sAudioKeep.AppVol)*/)
    {
        sAudioKeep.AppVol = 20; //sAudioDat.sBasicBK.DefaultPromptVol;
    }
    else if(sAudioKeep.AppVol<AUDIO_VOL_MIN)
    {
        sAudioKeep.AppVol = AUDIO_VOL_MIN;
    }
    
    sAudioDat.sInfo.BeepType = g_tSysRomData.uGenBlock.tBlock.tFlag2.bBeep_Flag;
    if(sAudioDat.sInfo.BeepType >= BEEP_TYPE_SET_MAX)
    {
        sAudioDat.sInfo.BeepType = BEEP_DEFAULT_TYPE;
    }
    if(AUDIO_ASP_HERO != sAudioKeep.AspModule)
    {
        sAudioKeep.AspModule = AUDIO_ASP_NULL;  //Goto Check ASP Type
    }
    for(i = 0; i < 3; i++)
    {
        sAudioKeep.sBakXover[i].CoF = sAudioDat.sAdv.sCustomXover[i].CoF;
        sAudioKeep.sBakXover[i].Level = sAudioDat.sAdv.sCustomXover[i].Level;
        sAudioKeep.sBakXover[i].Slope = sAudioDat.sAdv.sCustomXover[i].Slope;
    }
    for(i = 0; i < DELAY_LINE_MAX; i++)
    {
        sAudioKeep.BakDelay[i] = sAudioDat.sAdv.DelayCustom[i];
    }
    for(i = 0; i < GEQ_MAX_NUM; i++)
    {
        sAudioKeep.sBakGeq[i].CF = sAudioDat.sGeq.sBuffer[i].CF;
        sAudioKeep.sBakGeq[i].Gain = sAudioDat.sGeq.sBuffer[i].Gain;
        sAudioKeep.sBakGeq[i].Q = sAudioDat.sGeq.sBuffer[i].Q;
        sAudioKeep.sBakGain[3 * i + 0] = sAudioDat.sGeq.GainTbl[3 * i + 0];
        sAudioKeep.sBakGain[3 * i + 1] = sAudioDat.sGeq.GainTbl[3 * i + 1];
        sAudioKeep.sBakGain[3 * i + 2] = sAudioDat.sGeq.GainTbl[3 * i + 2];
    }


	
	sAudio.bDatumReady = 1;
	//Feedback Mute Release Flag...make sure APP display same as controlled state..
	_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);

	_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SYS_VOL_ALL,NULL);
}
/**********************************************************
 * @function    Audio_InitVariable
 * @brief      Initialize Audio Variable
 * @param      None
 * @retval     None
 **********************************************************/
void Audio_InitVariable(void)
{
    uint8_t i;

    sAudio.SysChannel = SRC_TYPE_NUM;        //Currently Ach Related Variable Initialize
    sAudio.RearChannel = SRC_TYPE_NUM;
    sAudio.SysChanMode = AUDIO_2CH_MODE;
    for(i = 0; i < SRC_TYPE_NUM; i++)
    {
        sAudio.sAchAttri[i].MuteState = 0x00;
    }
    sAudio.bNotDispVol = 0;
    
    //Operation Control...
    sAudio.OpCtl = OPERATION_0;
    sAudio.OpHead = 0;
    sAudio.OpTail = 0;

    //Initialize Mute Related..
    sAudio.MuteEvtCtl = MUTE_EVT_IDLE;        //Evt Mute Control Related Variable Initialize
    sAudio.MuteCtlHead = 0;
    sAudio.MuteCtlTail = 0;
    sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;    //Key Mute Control Related Variable Initialize
    sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_NULL;
    sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_IDLE;
    sAudio.KeyMuteReq[SYSTEM_REAR] = MUTE_NULL;
    sAudio.MuteState = 0x00;
    sAudio.KeyMuteFlag = 0x00;
    sAudio.KeyMuteState = 0x00;

    //Initialize ACH Related..
    sAudio.AchCtl[SYSTEM_FRONT] = ACH_SWITCH_IDLE;
    sAudio.AchCtl[SYSTEM_REAR] = ACH_SWITCH_IDLE;
    sAudio.AchReqed[SYSTEM_FRONT] = SRC_TYPE_NUM;
    sAudio.AchReqed[SYSTEM_REAR] = SRC_TYPE_NUM;

    //Initialize Beep Related Parameters
    sAudio.BeepCtl = BEEP_CTL_IDLE;
    sAudio.BeepTail = 0;
    sAudio.BeepHead = 0;
    for(i = 0; i < BEEP_BUFFER_MAX; i++)
    {
        sAudio.sBeepBuffer[i].Type = BEEP_TYPE_NULL;
    }
    sAudio.sBeepCurrent.Type = BEEP_TYPE_NULL;
    sAudio.BeepSetupCtl = 0;        
    sAudio.BeepSetupMask = 0;             
    sAudio.BeepLast = BEEP_TYPE_NULL;

    //Initialize Mix Related..
    sAudio.MixCtl = MIX_CTL_IDLE;
    sAudio.MixHead = 0;
    sAudio.MixTail = 0;
    sAudio.MixStatus = MIX_STATUS_OFF;

    //Delay Line
    sAudio.DelayCtl = OPERATION_0;
    sAudio.DelayLineMask = 0x00;

    //Graphic Equazlier
    sAudio.GeqStep = OPERATION_0;
    sAudio.GeqMask = 0x0000;

    //Loudness
    sAudio.LoudnessMask = 0x00;
    sAudio.LoudnessCtl = OPERATION_0;

    //SubWoofer
    sAudio.SwMask = 0x00;
    sAudio.SwCtl = OPERATION_0;
    //Xover
    sAudio.XoverCtl = 0;
    sAudio.XoverMask = 0;

    //Parametric Equalizer
    sAudio.PeqStep = OPERATION_0;
    sAudio.PeqMask[CHANNEL_FL] = 0x0000;
    sAudio.PeqMask[CHANNEL_FR] = 0x0000;
    sAudio.PeqMask[CHANNEL_RL] = 0x0000;
    sAudio.PeqMask[CHANNEL_RR] = 0x0000;

    //Channel Gain
    sAudio.ChanGainCtl = 0;
    sAudio.ChanGainMask = 0;

    //UltraBass
    sAudio.UltraBassCtl = 0;
    sAudio.UltraBassMask = 0;

    sAudio.DrvVolStep = OPERATION_0; 
    sAudio.BalFadCtl = OPERATION_0;
    sAudio.DrvBassStep = OPERATION_0;
    sAudio.DrvMidStep = OPERATION_0;
    sAudio.DrvTrebleStep = OPERATION_0;
    
#ifdef D_AUDIO_ASP_HERO    
    Hero_InitVariable();
#endif//D_AUDIO_ASP_HERO


    Amp_InitVariable();

    for(i = 0 ; i < ACH_MAX;i++)
    {
        sAudio.AchActBuffer[i] = SRC_TYPE_NUM;
    }
    sAudio.ReadyState = 0x00;

//	sAudioDat.sBasic.Type = GEQ_MODE_STANDARD;
}
/**********************************************************
 * @function    Audio_ColdInit
 * @brief      Cold Start, Reset All of Audio 
 * @param      None
 * @retval     None
 **********************************************************/
void Audio_ColdInit(void)
{
    Audio_ResetInfoVariable();//Pre-Reset, For Data Sync Usage..
    Audio_GotoStep(0);
    AudioSetSysState(AUDIO_SYS_SLEEP);    
}
/**********************************************************
 * @function    Audio_WarmInit
 * @brief      Warm Start, Initialize All of Audio 
 * @param      None
 * @retval     None
 **********************************************************/
void Audio_WarmInit(void)
{
    //Audio Parameters Init
    Audio_GotoStep(0);
    AudioSetSysState(AUDIO_SYS_SLEEP);    
}
/**********************************************************
 * @function    Audio_VirTimer
 * @brief      Virtual Timer: 2ms tick
 * @param      None
 * @retval     None
 **********************************************************/
void Audio_VirTimer(void)
{
    if(sAudio.TestDelayNave)sAudio.TestDelayNave--;
    if(sAudio.FuncDelay)sAudio.FuncDelay--;
    if(sAudio.LoadDatumDly)sAudio.LoadDatumDly--;

    if(sAudio.AspDelay)sAudio.AspDelay--;
    if(sAudio.DrvOverTime)sAudio.DrvOverTime--;
    if(sAudio.DrvDesertTime)sAudio.DrvDesertTime--;
    
    if(sAudio.KeyMuteDly[SYSTEM_FRONT])sAudio.KeyMuteDly[SYSTEM_FRONT]--;
    if(sAudio.KeyMuteDly[SYSTEM_REAR])sAudio.KeyMuteDly[SYSTEM_REAR]--;
    if(sAudio.ClickClackDelay)sAudio.ClickClackDelay--;
    if(sAudio.AchDelay[SYSTEM_FRONT])sAudio.AchDelay[SYSTEM_FRONT]--;
    if(sAudio.AchDelay[SYSTEM_REAR])sAudio.AchDelay[SYSTEM_REAR]--;

    if(sAudio.XoverDelay)sAudio.XoverDelay--;
    if(sAudio.DelayWait)sAudio.DelayWait--;
    if(sAudio.PhaseWait)sAudio.PhaseWait--;
    //Beep Delay
    if(sAudio.BeepDelay)
    {
        sAudio.BeepDelay--;
    }

    if(sAudio.SyncTimer)
    {
        sAudio.SyncTimer--;
    }


	Amp_TimerDeal();
}
/**********************************************************
 * @function    Audio_GetVolType
 * @brief      Return Currently Volume Type
 * @param      Null
 * @retval     Vol Type
 **********************************************************/
 uint8_t Audio_GetVolType(void)
{
    uint8_t Type;
    uint8_t SaveFlag = 0;	
    extern tEEP_DATA_BLOCK l_tEepSysRomData;
    if(MIX_STATUS_BT & sAudio.MixStatus)
    {
        Type = VOL_TYPE_BT;
        sAudioKeep.BtVol = sAudioKeep.CurrentlyVol;
    }
    else if((SRC_TYPE_BT_PHONE == sAudio.SysChannel) || (SRC_TYPE_3G_PHONE == sAudio.SysChannel))
    {
        Type = VOL_TYPE_BT;
        sAudioKeep.BtVol = sAudioKeep.CurrentlyVol;
    }
    else if(MIX_STATUS_NAVI & sAudio.MixStatus)
    {    
        Type = VOL_TYPE_NAV;
        sAudioKeep.NaviVol = sAudioKeep.CurrentlyVol;
    }
    else if((SRC_TYPE_NAVI == sAudio.SysChannel) || (SRC_TYPE_NAVI_AUDIO == sAudio.SysChannel))
    {
        Type = VOL_TYPE_NAV;
        sAudioKeep.NaviVol = sAudioKeep.CurrentlyVol;
    }
    else
    {
        Type = VOL_TYPE_SYS;
        sAudioKeep.SysVol = sAudioKeep.CurrentlyVol;
    }
#ifdef D_VOL_CHANA
  // if((HMIStatusFlag.g_tBTAppTone&0x01) == VOL_TYPE_BT)
  	if(SysWorkStatusGrp.SysBtCallFlag)
       {
       Type = VOL_TYPE_BT;
       sAudioKeep.BtVol = sAudioKeep.CurrentlyVol ;	
       }
	else if(MIX_STATUS_NAVI & sAudio.MixStatus)//snake20160917
	{
		Type = VOL_TYPE_NAV;
		sAudioKeep.NaviVol= sAudioKeep.CurrentlyVol;
	}
    else // if((Type != VOL_TYPE_BT)&&((HMIStatusFlag.g_tBTAppTone&0x01) == VOL_TYPE_SYS))
    {
	Type = VOL_TYPE_SYS;
	sAudioKeep.SysVol = sAudioKeep.CurrentlyVol;
    }
#endif
     if(g_tSysRomData.tAudioBlock.SysVol != sAudioKeep.SysVol)	
     {
     	g_tSysRomData.tAudioBlock.SysVol= sAudioKeep.SysVol;
	SaveFlag = 1;
     }
     if(g_tSysRomData.tAudioBlock.BtVol != sAudioKeep.BtVol)
     {
     	g_tSysRomData.tAudioBlock.BtVol= sAudioKeep.BtVol;
	SaveFlag = 1;
     }
     if(g_tSysRomData.tAudioBlock.NaviVol != sAudioKeep.NaviVol)
     {
    	 g_tSysRomData.tAudioBlock.NaviVol= sAudioKeep.NaviVol;
	SaveFlag = 1;
     }
     g_tSysRomData.tAudioBlock.AppVol= sAudioKeep.AppVol;

     if(1==SaveFlag)
     {
	     g_tSysRomData.tScrBlock.cBaseBR= g_BKHandLevel;
	     EEP_CreateBlockChkSum(&l_tEepSysRomData);
	     EEP_WriteStart(&l_tEepSysRomData,1);
     }
    return (Type);
}
/**********************************************************
 * @function    Audio_OutputInfoes
 * @brief      Output Audio Related Infoes
 * @param      Null
 * @retval     Null
 **********************************************************/
void Audio_OutputInfoes(void)
{
    static uint8_t SysVol = 0xFF;    //Temp...Front System Volume 
    static uint8_t RearVol = 0xFF;    //Temp...Rear System Volume 
    static PN_FILTER_STRUCT sTmpBass;
    static PN_FILTER_STRUCT sTmpMid;
    static PN_FILTER_STRUCT sTmpTreble;
    static uint8_t TmpBal = 0xFF;
    static uint8_t TmpFad = 0xFF;
    static uint8_t TmpEQType = 0xff;
    uint8_t BasicSet = 0;     

    if(sAudio.FuncStep <= AUDIO_STARTUP_LOAD)
        return;

//    if(sAudio.bSyncToEep)  //Sync Datum to Eep
//    {
//            EEP_CreateBlockChkSum(&l_tEepAudioRomData);
//        if(TRUE == EEP_WriteStart(&l_tEepAudioRomData,1))
//        {
//            sAudio.bSyncToEep = 0;
//        }
//    }
    
    //Output Volume
    if(SysVol != sAudioKeep.CurrentlyVol) 
    {
        SysVol = sAudioKeep.CurrentlyVol;
        if(!sAudio.bNotDispVol)
        {
            _SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,SysVol,Audio_GetVolType(),0,0);
        }
        else
            sAudio.bNotDispVol = 0;
    }
    
    if(RearVol != sAudioKeep.RearVol)
    {
        RearVol = sAudioKeep.RearVol;
        _SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_RVOL,RearVol,0,0,0);
    }

    //Output Tone: Bass
    if((sTmpBass.Gain != sAudioDat.sBasic.sBass.Gain) 
        || (sTmpBass.CF != sAudioDat.sBasic.sBass.CF)
        || (sTmpBass.Q != sAudioDat.sBasic.sBass.Q))
    {
        sTmpBass = sAudioDat.sBasic.sBass;
        BasicSet = 1;
        _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BASS,&sAudioDat.sBasic);
    }
    
    //Output Tone: Middle
    if((sTmpMid.Gain != sAudioDat.sBasic.sMid.Gain) 
        || (sTmpMid.CF != sAudioDat.sBasic.sMid.CF)
        || (sTmpMid.Q != sAudioDat.sBasic.sMid.Q))
    {
        sTmpMid = sAudioDat.sBasic.sMid;
        if(0 == BasicSet)
        {
            BasicSet = 1;
            _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MID,&sAudioDat.sBasic);
        }
    }
    
    //Output Tone: Treble
    if((sTmpTreble.Gain != sAudioDat.sBasic.sTreble.Gain) 
        || (sTmpTreble.CF != sAudioDat.sBasic.sTreble.CF)
        || (sTmpTreble.Q != sAudioDat.sBasic.sTreble.Q))
    {
        sTmpTreble = sAudioDat.sBasic.sTreble;
        if(0 == BasicSet)
        {
            BasicSet = 1;
            _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_TREBLE,&sAudioDat.sBasic);
        }
    }    

    //Output Balance
    if(TmpBal != sAudioDat.sBasic.Balance)
    {
        TmpBal = sAudioDat.sBasic.Balance;
        if(0 == BasicSet)
        {
            BasicSet = 1;
            _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BAL,&sAudioDat.sBasic);
        }
    }

    //Output Fader
    if(TmpFad != sAudioDat.sBasic.Fader)
    {
        TmpFad = sAudioDat.sBasic.Fader;
        if(0 == BasicSet)
        {
            BasicSet = 1;
            _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_FAD,&sAudioDat.sBasic);
        }
    }

    if(sAudio.StarUp && (0 == sAudio.SyncTimer))
    {
        switch(sAudio.SyncStep)
        {
            case 0:
            default:
                break;
            case 1:
               _SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,sAudioKeep.SysVol,VOL_TYPE_SYS,0,0);
                sAudio.SyncStep ++;
                sAudio.SyncTimer = 20;            
            break;
            case 2:
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BASIC,&sAudioDat.sBasic);
                sAudio.SyncStep ++;
                sAudio.SyncTimer = 40;//_set_timing_xms_base_aud_task_tick(500);
                break;
            case 3:
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_XOVER,&sAudioDat.sAdv);
                sAudio.SyncStep ++;
                sAudio.SyncTimer = 40;//_set_timing_xms_base_aud_task_tick(500);
                break;

            case 4:
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_CHGAIN,&sAudioDat.sGain);
                sAudio.SyncStep ++;
                sAudio.SyncTimer = 40;//_set_timing_xms_base_aud_task_tick(500);
                break;
            case 5:
                _SendMsgToHMI(MS_UI_UPLOAD_INFO,OP_INFO_VERSION,NULL);
                sAudio.SyncStep ++;
            break;
        }
    }
}
/**********************************************************
 * @function    Audio_Manager
 * @brief      Main Functions of Audio
 * @param      None
 * @retval     None
 **********************************************************/
void Audio_Manager(void)
{
    // Execute Audio Functions while Task Not Sleep
    if(AUDIO_SYS_SLEEP != AudioGetSysState())
    {
        //Main Control Functions
        (*Tab_AudioFunc[((sAudio.FuncStep >> 4) & 0x0F)])();    

        //Audio Operation Disposal
        Audio_OpDisposal();

        //ACH Manager
        Audio_AchSwitchMgr();

        //Beep Manager
        Audio_BeepDisposal();

        //Mix Manager
        Audio_MixDisposal();

        //Output Related Infoes    
        Audio_OutputInfoes();

        Audio_ClickClack();

        Audio_AmpDetect();

    }
    
    //Mute Manager: KeyMute and Event Mute
    Audio_MuteEvtDisposal();
    Audio_KeyMuteDisposal();
}
/**********************************************************
 * @function    Audio_MsgHandler
 * @brief      Dispose Messages received
 * @param      tMSG_BUF* Msg
 * @retval     None
 **********************************************************/

void Audio_MsgHandler(tMSG_BUF* pMsg)
{
    #define MsgId     pMsg->Id
    #define MsgSid     pMsg->iSid

    switch(MsgId)  
    {
        //4Power Manager Related Message
        case MS_PM_STATE:
            switch(MsgSid)
            {
            	  case OP_PM_STATE_STANDBY:  
			break;
                case OP_PM_STATE_ON:
		  IO_Set(IO_IDX_MCU2DSP_PWR, PIN_OUTPUT,VALID); 	
            //    case OP_PM_STATE_STANDBY:  /*remove this state, null deal 20140924 */
                    if(!OS_TaskIsActive(TASK_ID_AUDIO))
                    {
                        OS_TaskStart(TASK_ID_AUDIO); // Start Audio Task
                    }
                    sAudio.PwrState = 1;
                    //Startup Audio Task:Re-Start while not in running state..
                    if(AUDIO_SYS_RUN != AudioGetSysState())
                    {
                        AudioSetSysState(AUDIO_SYS_STARTUP);
                        Audio_GotoStep(AUDIO_FUNC_STARTUP);
                    }
                    break;

                case OP_PM_STATE_WAIT_SLEEP: //Do nothing ...
                    //yangyan --2014.08.07
                    //sAudio.PwrState = 0;
                    //if(sAudio.MixStatus & MIX_STATUS_NAVI)
                    //{
                    //    Audio_MixQueueIn(SRC_TYPE_NAVI_AUDIO,MIX_TYPE_OFF);
                    //}
                    //break;

                default:	
 
                    IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
                    //Rear System
                    IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
                    
                    sAudio.PwrState = 0;
                    //Goto Shut Off Tuner and Close Power 
                    _SendMsgToHMI(MS_SYS_AUDIO_STATE,OP_DEV_STATE_OFF,NULL);
                    if(AudioGetSysState() <= AUDIO_SYS_PWROFF)
                    {
                        //Save Audio Block
                        if(sAudio.bDatumReady)
                        {
                            OS_CreateRamChkBlock((void*)&sAudioDat,
                                    (sizeof(AUDIO_DATUM_STRUCT)-sizeof(uint16_t)),
                                    (void*)&(sAudioDat.CheckSum));
                        }
                        AudioSetSysState(AUDIO_SYS_PWROFF);
                        Audio_GotoStep(AUDIO_FUNC_PWROFF);
                    }
                    break;
            }
            break;
            
        //4Audio Related Message
        case MS_AUDIO_CMD:    
            //Audio Not Ready~~Desert All Message!!!
            if(!(sAudio.ReadyState & AUDIO_READY))
            {
                break;
            }
            Audio_InputLogic(pMsg);
            break;

        case MS_SYS_LOAD_FACTORY_INFO:  //Load Default and Re-Init
		Audio_ResetInfoVariable();
		//Audio_InitVariable();
		Audio_VariableCheck();
            break;

        case MS_SYS_APU_INFO:
            if(OP_DEV_STATE_CONNECTED == MsgSid)
            {
                sAudio.SyncStep = 1;
                sAudio.SyncTimer = 400;
            }  
	    if(OP_DEV_STATE_ENTER == MsgSid)		
	   	{
	   	       Audio_FastHardMute(MUTE_OFF);
			//外置功放解静音
		       CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_OFF);

		}
            break;
        case MS_SYS_DISC_INFO:
            if(OP_DEV_STATE_NORMAL == MsgSid)
            {
                if(sAudio.SysState == AUDIO_SYS_RUN)
                {
                    _SendMsgToHMI(MS_SYS_DEV_TYPE,DEV_IDX_TUNER,sAudioKeep.AspModule);
                }
            }         
            break;
        case MS_SYS_DEV_TYPE:
		#if 0
            if(DEV_IDX_MPEG == MsgSid)
            {
                uint8_t cMpegType = (uint8_t)((uint32_t)(pMsg->uData.p_cData));
                /* cMsgType =
                typedef enum{
                       SOLUTION_NONE,
                       SOLUTION_ZORAN,
                       SOLUTION_SUNPLUS,
                       SOLUTION_NUM
                    };

                if this time the audio chip is init,resetting the audio para;
                else,set a flag, when the audio chip init complete,set the para!
                */
			if( cMpegType == SOLUTION_ZORAN )	 			
		                   sAudioDat.sGain.ScalerTbl[SS_SRC_DISC] = ((AUDIO_SRC_SCALER_MAX / 2)+ 0);
			else if( cMpegType == SOLUTION_SUNPLUS )	
		                   sAudioDat.sGain.ScalerTbl[SS_SRC_DISC] = ((AUDIO_SRC_SCALER_MAX / 2)+ 3);
			if((sAudio.SysChannel == SRC_TYPE_DISC_AUDIO)
				||(sAudio.SysChannel == SRC_TYPE_DISC_VIDEO)
				||(sAudio.SysChannel == SRC_TYPE_DVD))
			{
	                    sAudio.CommonCode = AUDIO_COMMON_SRC_SCALER;
			}
            }      
	#endif
            break;
    }
    
    #undef MsgId
    #undef MsgSid
}
/**********************************************************
 * @function    Audio_Task
 * @brief      a periodic task for Audio module
 * @param      EVENT Evt
 *                 eTASK_STATE eState
 * @retval     None
 **********************************************************/
void AUD_Task(EVENT Evt,eTASK_STATE eState)
{
    if(Evt & EVT_COLD_INIT)    //Cold Start, Reset Parameters
    {
        Audio_FastHardMute(MUTE_ON);
        Audio_ColdInit();
    }

    if(Evt & EVT_WARM_INIT)    //Warm Start, Initialize Parameters
    {
        Audio_FastHardMute(MUTE_ON);
        Audio_WarmInit();
    }

    if(Evt & EVT_MSG_READY)
    {
        tMSG_BUF tMsg;
        if(QUE_ERR_NONE == OS_GetMsgDir(&g_tAudTaskCB,&tMsg))
        {
            Audio_MsgHandler(&tMsg);
        }
    }
    
    
    switch(eState)
    {
        case TASK_STATE_READY:
            
            break;

        case TASK_STATE_RUNNING:
        case TASK_STATE_STOP:
        if(Evt & EVT_TASK_TICK_READY)
        {
            //Audio Main Control
            Audio_Manager();
    
            // Virtual Tick
            Audio_VirTimer();
        }
            break;    
		default:
			break;
    }
}

bool AUD_Init(void)
{
    IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
    //IO_Set(IO_IDX_LINE_MUTE,PIN_OUTPUT,VALID); 
    IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
    IO_Set(IO_IDX_DSP_RESET,PIN_OUTPUT,INVALID);
    //IO_Set(IO_IDX_D3_INIT_FLG,PIN_INPUT,VALID);
    IO_Set(IO_IDX_DSP_FAST_MUTE,PIN_INPUT,VALID);  //Not Used Yet
    IO_Set(IO_IDX_AMP_CLIP,PIN_INPUT,VALID);  //Not Used Yet
    IO_Set(IO_IDX_AK4220_RESET,PIN_OUTPUT,INVALID);  
    //IO_Set(io_idx_tv_sel,PIN_OUTPUT,INVALID);   

    return (TRUE);
}
bool AUD_DInit(void)
{
    IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
    IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
    IO_Set(IO_IDX_DSP_RESET,PIN_INPUT,VALID);
    //IO_Set(IO_IDX_D3_INIT_FLG,PIN_INPUT,INVALID);
    IO_Set(IO_IDX_DSP_FAST_MUTE,PIN_INPUT,VALID);  //Not Used Yet
    IO_Set(IO_IDX_AMP_CLIP,PIN_INPUT,VALID);  //Not Used Yet
    IO_Set(IO_IDX_AK4220_RESET,PIN_INPUT,VALID);  //Notice:POP noise
    
    return (TRUE);
}

static const tTASK_BLOCK l_tAudioTCB = {
    "AUD",
    _AUD_TASK_TICK_,
    _AUD_CORE_TICK_,
    AUD_Task,
    AUD_Init,
    AUD_DInit,
};

tRING_QUE l_tAudMsgQue;
tMSG_BUF la_tAudMsgBuf[D_AUD_MSG_QUE_DEEP];



bool AUD_TaskCreate(void)
{
#ifdef D_TONE_EQ
  	UserGeq[0].CF = 100;
	UserGeq[0].Gain =  AUDIO_BASS_MAX/2;
	UserGeq[1].CF = 2000;
	UserGeq[1].Gain =  AUDIO_MID_MAX/2;
	UserGeq[2].CF = 9000;
	UserGeq[2].Gain =  AUDIO_TREBLE_MAX/2;
#endif

#if CAN_DEBUG_AUDIO
	AudioDbgMsg.CAN_Id = CAN_ID_INNER;
	AudioDbgMsg.CANMsgDlc = 8;
#endif
   //Audio_ColdInit();
   //EEP_CreateEepDataBlock(&l_tEepAudioRomData,&lc_tEepAudioRom);
    return OS_TaskCreate(TASK_ID_AUDIO,&g_tAudTaskCB,&l_tAudioTCB,&l_tAudMsgQue,la_tAudMsgBuf,D_AUD_MSG_QUE_DEEP);
}


#undef TASK_AUDIO_C

