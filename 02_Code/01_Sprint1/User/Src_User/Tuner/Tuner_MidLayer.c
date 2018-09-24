/**********************************************************
 * @file        Tuner_MidLayer.c
 * @purpose     
 * @version    0.01
 * @date        11. July. 2012
 * @author    Deefisher.Lyu
 * @brief        
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          11.July.2012        v0.01        created
 *  
  **********************************************************/
#define TUNER_MIDLAYER_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= public variable ==================== */

/* ========================= private variable =================== */
/*static*/ const TUNER_REGION_STRUCT sTunerRegion[REGION_MAX] =
{
    //Europe 1: EURO
    8750,8750,9000,9800,10600,10800,
    522,522,603,999,1404,1620,
    0,0,0,0,0,0,
    5,
    0,
    9,
    5,
    //Europe 2: ORIT
    8750,8750,9000,9800,10600,10800,
    522,522,603,999,1404,1620,
    6500,6500,6710,7040,7220,7400,
     5,
    5,
    9,
    7,
    //AUST
    8750,8750,9000,9800,10600,10800,
    522,522,603,999,1404,1710,
    0,0,0,0,0,0,
    10,
    0,
    9,
    5,
    //Middle East
    8750,8750,9000,9800,10600,10800,
    531,531,603,999,1404,1602,
    0,0,0,0,0,0,
    10,
    0,
    9,
    5,
    //USA1
    8750,8750,9000,9800,10600,10800,
    530,530,600,1000,1400,1620,
    0,0,0,0,0,0,
    10,
    0,
    10,
    5,
    //USA2
    8750,8750,9010,9810,10610,10790,
    530,530,600,1000,1400,1620,
    0,0,0,0,0,0,
    20,
    0,
    10,
    5,
    //USA3
    8750,8750,9010,9810,10610,10790,
    530,530,600,1000,1400,1710,
    0,0,0,0,0,0,
    20,
    0,
    10,
    5,
    //USA4
    8750,8750,9010,9810,10610,10800,
    530,530,600,1000,1400,1710,
    0,0,0,0,0,0,
    10,
    0,
    10,
    5,
    //SouthEast Asia
    //8750,9000,9500,9800,10600,10800,
    //531,540,603,999,1404,1629,
    8750,8750,8750,8750,8750,10800,
    531,531,531,531,531,1629,
    0,0,0,0,0,0,
    10,
    0,
    9,
    5,
    //Japan
    7600,7600,8000,8400,8800,9000,
    522,522,603,999,1404,1629,
    0,0,0,0,0,0,
    10,
    0,
    9,
    5,

	//South America 1
    8750,8750,8750,8750,8750,10800,
    520,520,520,520,520,1600,
    0,0,0,0,0,0,
    10,
    0,
    10,
    5,

	//South America 2
    8750,8750,8750,8750,8750,10800,
    520,520,520,520,520,1620,
    0,0,0,0,0,0,
    20,
    0,
    10,
    5,

};

/* ========================= Code Part =================== */


/**********************************************************
 * @function    Tuner_PowerOn
 * @brief      Open Power Supply and Some Parameter Initialize   
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_PowerOn(void)
{
    uint8_t Result = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.MidLayerDelay))
        return (Result);
    
    switch(sTuner.MidLayerStep)
    {
        // Open Power Supply
        case TUNER_PWRON_OPEN_POWER:    //Currently Project:No Power Control
            //Sync Module Type
            if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
            {
                sTuner.ModuleType = TUNER_MODULE_TEF6638;
            }

            // IO Port Config:Rds Int Pin
            IO_Set(IO_IDX_RDS_INT0,PIN_INPUT,VALID);
            //GPIO_Config(GPIO_RDS_INT_DDR,GPIO_MODE_INPUT);
            // Power&Antenna
            sTunerKeep.AntPwr = g_tSysSettingRomData.TunerAntPwr;
            if(sTunerKeep.AntPwr)
            {
                //PM_UnitPowerSet(PM_UNIT_ANT,ON);
                IO_Set(IO_IDX_PHANTOM_POWER1,PIN_OUTPUT,VALID);
                IO_Set(IO_IDX_PHANTOM_POWER2,PIN_OUTPUT,VALID);
            }
            sTuner.bDatumReady = 0;
            Tuner_GotoMidStep(TUNER_PWRON_INIT_VARIABLE);
            break;
            
        // Variable Initialize
        case TUNER_PWRON_INIT_VARIABLE:        
            sTuner.MidLayerStep = OPERATION_0;
            Result = SUBLAYER_DONE;
            break;    

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_ResetModule
 * @brief      Reset Tuner Module
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_LoadDatum(void)
{
    uint8_t Result = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.MidLayerDelay))
        return (Result);
    
    switch(sTuner.MidLayerStep)
    {
    
        //Check&Read Datum
        case TUNER_LOAD_RAM_CHK:
            if(OS_RamCheck((void*)&sTunerDat,(sizeof(TUNER_DATUM_STRUCT)-sizeof(uint16_t)),
                           (void*)&(sTunerDat.CheckSum)))
            {
                /*Ram check OK, no need to load from eeprom*/
                sTuner.MidLayerStep = TUNER_LOAD_END;
            }
            else
            {
                sTuner.MidLayerStep = TUNER_LOAD_DEFAULT;
            }
            break;

        //Load Default Datum
        case TUNER_LOAD_DEFAULT:
            Tuner_VariableReset();
            OS_CreateRamChkBlock((void*)&sTunerDat,
                                (sizeof(TUNER_DATUM_STRUCT)-sizeof(uint16_t)),
                                (void*)&(sTunerDat.CheckSum));
            sTuner.MidLayerStep = TUNER_LOAD_END;
            break;

        //Load End...
        case TUNER_LOAD_END:
            Tuner_VariableInit();
            //All Parameter Check
            Tuner_VariableCheck();
            Result = SUBLAYER_DONE;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_InitRegister
 * @brief      Initialize Tuner's Boot Registers
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_InitRegister(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
        
	    if(DelayNotExpired(sTuner.MidLayerDelay))
        return (Result);
    
    switch(sTuner.MidLayerStep)
    {    
        // Load Boot Datum
        case TUNER_REG_BOOT:    //An Overtime Judgement is needed here!!!!
            SubResult = Tuner_InitBoot();
            if(SUBLAYER_DONE == SubResult)
            {
                Tuner_GotoMidStep(TUNER_REG_RDS);
            }
            break;

        // Set Rds Related Registers
        case TUNER_REG_RDS:
            SubResult = Tuner_InitRds();
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.MidLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_ResumeLast
 * @brief      Resume Last State(Band and Frequency)
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_ResumeLast(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.MidLayerDelay))
        return (Result);
    
    switch(sTuner.MidLayerStep)
    {
        // Initialize Specific Variable before Resume Band
        case TUNER_RESUME_INIT:        
            Tuner_BandInit();
            Tuner_GotoMidStep(TUNER_RESUME_BAND);
            break;

        // Resume Last Band    
        case TUNER_RESUME_BAND:
            SubResult = Tuner_SetBand();    
            if(SUBLAYER_DONE == SubResult)
            {
                Tuner_GotoMidStep(TUNER_RESUME_FREQ);
            }
            break;

        // Resume Last Frequency
        case TUNER_RESUME_FREQ:        
            SubResult = Tuner_SetFreq(TUNER_CURRENT_FREQ);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.MidLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_OperateBreak
 * @brief      New Operation Input, Break Currently State, Break 
 *            Currently Operations
 * @param      None                    
 * @retval     Result Of Executing
 **********************************************************/
uint8_t Tuner_Pre_Break(uint8_t Id)
{
    uint8_t Result = TRUE; 

    if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)        // AMS Save
    {   
        Tuner_SortStationAccordFreq(sTuner.asAmsBuff, sTuner.AmsValidStaNum); 
            #ifndef D_TUNER_LIST
        Tuner_SortPreset();
    #else
        _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_LIST,&sTunerKeep);
    #endif
    }
    else if(sTuner.uSeekState.sSsBitMap.bPresetScan)
    {
        if(OP_TUNER_SET_PRESET_SCAN == Id)
        {
            Result = FALSE;  //Newly Seek action only used to break 
        }
    }
    if(sTuner.uSeekState.SsTotal) 
    {
//        if((OP_TUNER_SET_SEEK_DEC == Id) || (OP_TUNER_SET_SEEK_INC == Id)
//            || (OP_TUNER_SET_AMS == Id) || (OP_TUNER_SET_SCAN == Id)
//            || (OP_TUNER_SET_PTY_SEEK == Id)||(OP_TUNER_SET_PAUSE ==Id) )    
	 if(OP_TUNER_STOP_SEEK == Id)
        {
            Result = FALSE;  //Newly Seek action only used to break 
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_OperateBreak
 * @brief      New Operation Input, Break Currently State, Break 
 *            Currently Operations
 * @param      None                    
 * @retval     Result Of Executing
 **********************************************************/
uint8_t Tuner_OperateBreak(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sTuner.BreakCtl)
    {
        // if AMSing, Do result sort and save
        case TUNER_BREAK_SORT:        
            //new action coming when seeking,Stop and switch to Idle
            if(sTuner.uSeekState.SsTotal) 
            {
                Tuner_GotoStep(TUNER_FUNC_IDLE);    
            }
            if(sTuner.uSeekState.sSsBitMap.bPresetScan)
            {
                SubResult = Tuner_SetFreq(TUNER_CURRENT_FREQ);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.BreakCtl = TUNER_BREAK_SEEK;
            }
            break;

        // If Seeking, Break Seek Mode     
        case TUNER_BREAK_SEEK:            
            if(sTuner.uSeekState.SsTotal)
            {    //Exit Seek Mode...
                SubResult = Tuner_SeekConfig(TUNER_MODE_PRESET);
                if(SUBLAYER_DONE == SubResult)
                {
                    sTuner.BreakCtl = TUNER_BREAK_MUTE;
                }
            }
            else
            {
                sTuner.BreakCtl = TUNER_BREAK_AF;
            }
            break;

        // If Seeking, Break Seek Mute
        case TUNER_BREAK_MUTE:        
            SubResult = Tuner_ReqMute(MUTE_OFF,TUNER_MID_OP);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.BreakCtl = TUNER_BREAK_AF;
            }
            break;
            
        // If AF Checking ,Break !
        case TUNER_BREAK_AF:        
            SubResult = Tuner_BreakAF();
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.BreakCtl = TUNER_BREAK_END;
            }
            break;

        // Break End!    
        case TUNER_BREAK_END:        
            if(sTuner.uSeekState.SsTotal)
            {
                sTuner.uSeekState.SsTotal = 0;    // Reset Seek State
            }
            sTuner.BreakCtl = OPERATION_0;
            Result = SUBLAYER_DONE;
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        sTuner.BreakCtl = OPERATION_0;
        Result = SubResult;
    }

    return (Result);    
}
/**********************************************************
 * @function    Tuner_InputLogic
 * @brief      Dispose the logic of input requirement
 *            Transfer logic operation to commonly operation
 * @param      tMSG_BUF* Msg                    
 * @retval     NULL
 **********************************************************/
void Tuner_InputLogic(tMSG_BUF* pMsg)
{
    uint16_t MsgSid = (pMsg->iSid);    
    #define MsgDat     pMsg->uData.a_cData[0]
    #define MsgDat1     pMsg->uData.a_cData[0]
    #define MsgDat2     pMsg->uData.a_cData[1]
    #define MsgDat3     pMsg->uData.a_cData[2]
    #define MsgDat4     pMsg->uData.a_cData[3]    

    sTuner.CommonCode = TUNER_COMMON_NULL;
    sTuner.uBakSeekState.SsTotal = 0x00;
	
    if(FALSE == Tuner_Pre_Break(MsgSid))
    {
        MsgSid = OP_TUNER_SET_BREAK;
    }

	hmi_printf(_T("Tuner_InputLogic:Sid = %d,MsgDat = %d %d %d %d\n",MsgSid,MsgDat1,MsgDat2,MsgDat3,MsgDat4));
	
    switch(MsgSid)
    {
        //Sync All Data
        case OP_TUNER_SET_SYNC:
            sTuner.bSyncData = 1;
            break;
    
        // switch to FM band, or switch in the FM band
        case OP_TUNER_SET_BAND_FM:    
            if(!TUNER_BAND_FM)
            {
                sTuner.bReInitBand = 1;
            }
            TUNER_CURRENT_BAND++;
            if(TUNER_BAND_FM)
            {
                TUNER_CURRENT_BAND = TUNER_FM_START;
            } 
            sTuner.CommonCode = TUNER_COMMON_BAND;
            break;
            
        // switch to AM band, or switch in the AM band    
        case OP_TUNER_SET_BAND_AM:    
            if(!TUNER_BAND_AM)
            {
                sTuner.bReInitBand = 1;
            }
            TUNER_CURRENT_BAND++;
            if((TUNER_CURRENT_BAND > TUNER_AM_END) || (TUNER_CURRENT_BAND < TUNER_AM_START))
                TUNER_CURRENT_BAND = TUNER_AM_START;
            sTuner.CommonCode = TUNER_COMMON_BAND;    
            break;
            
        // switch to OIRT band, or switch in the OIRT band    
        case OP_TUNER_SET_BAND_OIRT:    
            if(!TUNER_BAND_OIRT)
            {
                sTuner.bReInitBand = 1;    
            }
            TUNER_CURRENT_BAND++;
            if((TUNER_CURRENT_BAND > TUNER_OIRT_END) || (TUNER_CURRENT_BAND < TUNER_OIRT_START))
                TUNER_CURRENT_BAND = TUNER_OIRT_START;
            sTuner.CommonCode = TUNER_COMMON_BAND;
            break;    

        // Band Increace
        case OP_TUNER_SET_BAND:
        case OP_TUNER_SET_BAND_INC:	
            sTuner.bReInitBand = 1;
       #ifdef D_TUNER_LIST
            if(TUNER_BAND_FM)
            {
                TUNER_CURRENT_BAND = TUNER_BAND_AM1;
            }
            else
            {
                TUNER_CURRENT_BAND = TUNER_BAND_FM1;
            }
       #else
            if(TUNER_FM_END == TUNER_CURRENT_BAND)
            {
                if(7 == sTuner.BandNum)
                {
                    TUNER_CURRENT_BAND = TUNER_OIRT_START;    
                }
                else
                {
                    TUNER_CURRENT_BAND = TUNER_AM_START;    
                }
            }
            else if(TUNER_OIRT_END == TUNER_CURRENT_BAND)
            {
                TUNER_CURRENT_BAND = TUNER_AM_START;
            }
            else
            {
                TUNER_CURRENT_BAND++;
                if(TUNER_CURRENT_BAND > (sTuner.BandNum-1))
                {
                    TUNER_CURRENT_BAND = TUNER_FM_START;
                }
                else
                    sTuner.bReInitBand = 0;
            }
	#endif//D_TUNER_LIST  
            sTuner.CommonCode = TUNER_COMMON_BAND;
            break;
            
        // Band Decrease    
        case OP_TUNER_SET_BAND_DEC:	
            sTuner.bReInitBand = 1;
            if(TUNER_AM_START == TUNER_CURRENT_BAND)
            {
                if(7 == sTuner.BandNum)
                {
                    TUNER_CURRENT_BAND = TUNER_OIRT_END;
                }
                else
                {
                    TUNER_CURRENT_BAND = TUNER_FM_END;
                }
            }
            else if(TUNER_OIRT_START == TUNER_CURRENT_BAND)
            {
                TUNER_CURRENT_BAND = TUNER_FM_END;
            }
            else if(TUNER_CURRENT_BAND)
            {
                TUNER_CURRENT_BAND--;
                sTuner.bReInitBand = 0;
            }
            else
            {
                TUNER_CURRENT_BAND = TUNER_AM_END;
            }
            sTuner.CommonCode = TUNER_COMMON_BAND;
            break;

        // Band Directly Select
        case OP_TUNER_SET_BAND_SEL:	
            //Filter State that need reinit band
            if(((TUNER_FM_START == MsgDat) && (!TUNER_BAND_FM))     
                || ((TUNER_AM_START == MsgDat) && (!TUNER_BAND_AM))
                || ((TUNER_OIRT_START == MsgDat) && (!TUNER_BAND_OIRT)))
            {
                sTuner.bReInitBand = 1;
            }
            
            if(TUNER_CURRENT_BAND != MsgDat)
            {
                TUNER_CURRENT_BAND = MsgDat;
                sTuner.CommonCode = TUNER_COMMON_BAND;
            }
            break;

        // Step Increase Currently Frequency
        case OP_TUNER_SET_STEP_INC: 	
            Tuner_StepChangeFreq(DIRECTION_UP);
            sTuner.CommonCode = TUNER_COMMON_FREQ;
            break;

        // Step Decrease Currently Frequency
        case OP_TUNER_SET_STEP_DEC: 	
            Tuner_StepChangeFreq(DIRECTION_DN);
            sTuner.CommonCode = TUNER_COMMON_FREQ;
            break;

        //Directly Tune to A Frequency
        case OP_TUNER_SET_DIRECT_TUNE:
		sTunerKeep.bPausestate = 0;	
            sTuner.DirectFreq = (uint16_t)((MsgDat1 << 8) | (MsgDat2));
            if((sTuner.DirectFreq >= FM_FREQ_MIN) && (sTuner.DirectFreq <= FM_FREQ_MAX))
            {
                if(!TUNER_BAND_FM)
                {
                    sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].FMStep; 
                }
            }
            else if((sTuner.DirectFreq >= AM_FREQ_MIN) && (sTuner.DirectFreq <= AM_FREQ_MAX))
            {
                if(!TUNER_BAND_AM)
                {
                    sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].AMStep; 
                }
            }
            else if((sTuner.DirectFreq >= OIRT_FREQ_MIN) && (sTuner.DirectFreq <= OIRT_FREQ_MAX))
            {
                if(!TUNER_BAND_OIRT)
                {
                    sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].OIRTStep; 
                }
            }
            
            if(0 != (sTuner.DirectFreq % sTuner.TuneStep))
            {    // Mend Illegal Frequency
                sTuner.DirectFreq = ((sTuner.DirectFreq / sTuner.TuneStep) * sTuner.TuneStep);
            }
            if((sTuner.DirectFreq >= FM_FREQ_MIN) && (sTuner.DirectFreq <= FM_FREQ_MAX))
            {
                if(TUNER_BAND_FM)
                {
                    sTuner.CommonCode = TUNER_COMMON_FREQ;
                    TUNER_CURRENT_FREQ = sTuner.DirectFreq;
                    // update the preset attribute of the new frequency
                    TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
                    sTuner.CommonCode = TUNER_COMMON_FREQ;
                }
                else
                {
                    sTuner.CommonCode = TUNER_COMMON_BAND;
                    TUNER_CURRENT_BAND = TUNER_BAND_FM1;
                    sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq = sTuner.DirectFreq;
                }
            }
            else if((sTuner.DirectFreq >= AM_FREQ_MIN) && (sTuner.DirectFreq <= AM_FREQ_MAX))
            {
                if(TUNER_BAND_AM)
                {
                    sTuner.CommonCode = TUNER_COMMON_FREQ;
                    TUNER_CURRENT_FREQ = sTuner.DirectFreq;
                    // update the preset attribute of the new frequency
                    TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
                    sTuner.CommonCode = TUNER_COMMON_FREQ;
                }
                else
                {
                    sTuner.CommonCode = TUNER_COMMON_BAND;
                    TUNER_CURRENT_BAND = TUNER_BAND_AM1;
                    sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq = sTuner.DirectFreq;
                }
            }
            else if((sTuner.DirectFreq >= OIRT_FREQ_MIN) && (sTuner.DirectFreq <= OIRT_FREQ_MAX))
            {
                if(TUNER_BAND_OIRT)
                {
                    sTuner.CommonCode = TUNER_COMMON_FREQ;
                    TUNER_CURRENT_FREQ = sTuner.DirectFreq;
                    // update the preset attribute of the new frequency
                    TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
                    sTuner.CommonCode = TUNER_COMMON_FREQ;
                }
                else
                {
                    sTuner.CommonCode = TUNER_COMMON_BAND;
                    TUNER_CURRENT_BAND = TUNER_BAND_OIRT1;
                    sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq = sTuner.DirectFreq;
                }
            }
            break;    

        // Call Specific Preset
        case OP_TUNER_SET_PRESET1:    
        case OP_TUNER_SET_PRESET2:
        case OP_TUNER_SET_PRESET3:
        case OP_TUNER_SET_PRESET4:
        case OP_TUNER_SET_PRESET5:
        case OP_TUNER_SET_PRESET6:
    #ifdef D_TUNER_LIST
            TUNER_CURRENT_PRESET = MsgDat + 1;
            TUNER_CURRENT_FREQ = sTunerKeep.ValidList[TUNER_CURRENT_PRESET - 1];
            sTuner.CommonCode = TUNER_COMMON_FREQ;
            if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)
            {
              sTuner.uSeekState.sSsBitMap.bBreak = 1;
            }
    #else
            TUNER_CURRENT_PRESET = (MsgSid -OP_TUNER_SET_PRESET1 + 1);
            //if(TUNER_CURRENT_FREQ != sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET-1])
            {
                TUNER_CURRENT_FREQ = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET-1];
                sTuner.CommonCode = TUNER_COMMON_FREQ;
            }
    #endif
	     sTunerKeep.bPausestate = 0;	
            break;

        // Save Currently Frequency to Specific Preset
        case OP_TUNER_SET_SAVE1:    
        case OP_TUNER_SET_SAVE2:
        case OP_TUNER_SET_SAVE3:
        case OP_TUNER_SET_SAVE4:
        case OP_TUNER_SET_SAVE5:
        case OP_TUNER_SET_SAVE6:
    #ifdef D_TUNER_LIST			
            TUNER_CURRENT_PRESET = (MsgDat & 0x3f)+1;//snake20160915
            if(TUNER_BAND_FM)
            {
              sTunerKeep.FmList[TUNER_CURRENT_PRESET - 1] = TUNER_CURRENT_FREQ;
            }
            else
            {
              sTunerKeep.AmList[TUNER_CURRENT_PRESET - 1] = TUNER_CURRENT_FREQ;
            }
            sTunerKeep.ValidList[TUNER_CURRENT_PRESET - 1] = TUNER_CURRENT_FREQ;

		if(sTuner.bDatumReady)
            {
                OS_CreateRamChkBlock((void*)&sTunerDat,
                            (sizeof(TUNER_DATUM_STRUCT)-sizeof(uint16_t)),
                            (void*)&(sTunerDat.CheckSum));
            }
            _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_LIST,&sTunerKeep);
    #else
            TUNER_CURRENT_PRESET = (MsgSid - OP_TUNER_SET_SAVE1 + 1);
            sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET - 1] = TUNER_CURRENT_FREQ; 
            if(sTuner.bDatumReady)
            {
                OS_CreateRamChkBlock((void*)&sTunerDat,
                            (sizeof(TUNER_DATUM_STRUCT)-sizeof(uint16_t)),
                            (void*)&(sTunerDat.CheckSum));
            }
            //Output One Preset of the Preset List Sync  
            _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_ONE_PRESET,&sTunerDat);
    #endif
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;    

        //Up Goto Next Preset Station
        case OP_TUNER_SET_PRESET_INC:    
    #ifdef D_TUNER_LIST
            if(!sTunerKeep.ListNum)
            break;
            if(TUNER_CURRENT_PRESET<sTunerKeep.ListNum-1)
                TUNER_CURRENT_PRESET ++;
            else if(TUNER_CURRENT_PRESET>=sTunerKeep.ListNum-1)
                TUNER_CURRENT_PRESET=0;
            
            TUNER_CURRENT_FREQ =sTunerKeep.ValidList[TUNER_CURRENT_PRESET] ;
            sTuner.CommonCode = TUNER_COMMON_FREQ;
    #else
            TUNER_CURRENT_PRESET ++;
            if(TUNER_CURRENT_PRESET >= TUNER_PRESET_END)
            {
              TUNER_CURRENT_PRESET = TUNER_PRESET_1;
            
              if(TUNER_FM_END == TUNER_CURRENT_BAND)
                  TUNER_CURRENT_BAND = TUNER_FM_START;
              else if(TUNER_AM_END == TUNER_CURRENT_BAND)
                  TUNER_CURRENT_BAND = TUNER_AM_START;
              else if(TUNER_OIRT_END == TUNER_CURRENT_BAND)
                  TUNER_CURRENT_BAND = TUNER_OIRT_START;
              else
                  TUNER_CURRENT_BAND ++;
            }
            TUNER_CURRENT_FREQ = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET - 1];
            sTuner.CommonCode = TUNER_COMMON_FREQ;
    #endif
            break;

        //Down Goto Next Preset Station
        case OP_TUNER_SET_PRESET_DEC:    
    #ifdef D_TUNER_LIST
            if(!sTunerKeep.ListNum)
            break;
            if(!TUNER_CURRENT_PRESET)
            {
              TUNER_CURRENT_PRESET=sTunerKeep.ListNum-1;
            }
            else if(TUNER_CURRENT_PRESET>0)
            {
              TUNER_CURRENT_PRESET --;
            }	
            TUNER_CURRENT_FREQ =sTunerKeep.ValidList[TUNER_CURRENT_PRESET] ;
            sTuner.CommonCode = TUNER_COMMON_FREQ;
    #else
            if(TUNER_CURRENT_PRESET <= TUNER_PRESET_1)
            {
              if(TUNER_PRESET_1 == TUNER_CURRENT_PRESET) 
              {
                if(TUNER_FM_START == TUNER_CURRENT_BAND)
                    TUNER_CURRENT_BAND = TUNER_FM_END;
                else if(TUNER_AM_START == TUNER_CURRENT_BAND)
                    TUNER_CURRENT_BAND = TUNER_AM_END;
                else if(TUNER_OIRT_START == TUNER_CURRENT_BAND)
                    TUNER_CURRENT_BAND = TUNER_OIRT_END;
                else
                    TUNER_CURRENT_BAND --;
              }
              TUNER_CURRENT_PRESET = TUNER_PRESET_6;
            }
            else
            {
              TUNER_CURRENT_PRESET --;
            }
            TUNER_CURRENT_FREQ = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET - 1];
            sTuner.CommonCode = TUNER_COMMON_FREQ;
    #endif
            break;
                
        //Preset Scan
        case OP_TUNER_SET_PRESET_SCAN:
            sTuner.uBakSeekState.sSsBitMap.bPresetScan = 1;
            sTuner.CommonCode = TUNER_COMMON_PSCAN;
            break;

        // Manual Seek UP
        case OP_TUNER_SET_SEEK_INC: 	
            sTuner.bBakSeekDirect = DIRECTION_UP;
            sTuner.uBakSeekState.sSsBitMap.bSeek = 1;
            sTuner.CommonCode = TUNER_COMMON_SEEK;
            break;

        //Manual Seek Down
        case OP_TUNER_SET_SEEK_DEC: 	
            sTuner.bBakSeekDirect = DIRECTION_DN;
            sTuner.uBakSeekState.sSsBitMap.bSeek = 1;
            sTuner.CommonCode = TUNER_COMMON_SEEK;
            break;
            
        // Auto Memory Scan
        case OP_TUNER_SET_AMS:	
            sTuner.bBakSeekDirect = DIRECTION_UP;
            sTuner.uBakSeekState.sSsBitMap.bAutoMemSeek = 1;
            sTuner.CommonCode = TUNER_COMMON_SEEK;
            break;    
            
        // Auto Scan
        case OP_TUNER_SET_SCAN:	
            sTuner.bBakSeekDirect = DIRECTION_UP;
            sTuner.uBakSeekState.sSsBitMap.bAutoScan = 1;
            sTuner.CommonCode = TUNER_COMMON_SEEK;
            break;    

        case OP_TUNER_SET_PTY_SEEK:
            if(PtySetting)
            {
                sTuner.bBakSeekDirect = DIRECTION_UP;
                sTuner.uBakSeekState.sSsBitMap.bPTYSeek = 1;
                sTuner.CommonCode = TUNER_COMMON_SEEK;
            }
            break;

        case OP_TUNER_SET_PTY_INC:
        case OP_TUNER_SET_PTY_DEC:
            break;

        //PTY Select
        case OP_TUNER_SET_PTY_SEL: //Get Selected  Pty ID
            sTuner.PtySelect = MsgDat;
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;    

        //PTY Setting
        case OP_TUNER_SET_PTY:
            PtySetting ^= 1;
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;
            
        //TA Setting
        case OP_TUNER_SET_TA:
            TaSetting ^= 1;
            //Clear TA Related State
            if(TA_SET_OFF == TaSetting)
            {

            }
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;

        //AF Setting    
        case OP_TUNER_SET_AF:    //REG must sync with AF setting
            AfSetting ^= 1;
            //Clear AF Related State
            if(AF_SET_OFF == AfSetting)
            {
                //REG must be off at same time
                sTunerKeep.bBakReg = RegSetting;
                RegSetting = 0;
            }
            else
            {
                //Retrieve REG setting
                RegSetting = sTunerKeep.bBakReg;
            }
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;                

        //REG Setting
        case OP_TUNER_SET_REG:
            RegSetting ^= 1;
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;    

        //Loc Dx Switch..
        case OP_TUNER_SET_LOC_DX:
            LocDxSetting ^= 1;
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;
	//pause when ui set
	 case OP_TUNER_SET_PAUSE:
		if(MsgDat)
		{
			//_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE_REQ,SOURCE_TUNER,TYPE_F_S_MUTE,0,0);
			sTunerKeep.bPausestate=1;
		}
		else
		{
			//_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE_REQ,SOURCE_TUNER,TYPE_F_S_UNMUTE,0,0);
			sTunerKeep.bPausestate=0;
		}

		break;
      
        //Stereo Setting
        case OP_TUNER_SET_STEREO:
            StereoSetting ^= 1;
            if(STEREO_MONO == StereoSetting)
            {
                sTuner.bStereoMono = 0;
            }
            sTuner.CommonCode = TUNER_COMMON_ST;
            break;    

        //EON Setting
        case OP_TUNER_SET_EON:
            EonSetting ^= 1;
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;   
        case OP_TUNER_SET_BREAK:
            sTuner.CommonCode = TUNER_COMMON_BREAK;
            break;

    }
    //Queue In Valid Operation Triggerred by Message
    if(TUNER_COMMON_NULL != sTuner.CommonCode)
    {
        Tuner_OpQueueIn(sTuner.CommonCode);
    }
}
/**********************************************************
 * @function    Tuner_SeekConfig
 * @brief      Config Tuner Mode: Seek Mode Or Preset Mode        
 * @param      uint8_t Mode : Seek or Preset                    
 * @retval     None
 **********************************************************/
uint8_t Tuner_SeekConfig(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.MidLayerDelay))
        return (Result);
    
    switch(sTuner.MidLayerStep)
    {
        // Initialize seek related variables
        case TUNER_SC_VARIABLE:
            if(TUNER_MODE_PRESET == Mode)
            {
                Tuner_GotoMidStep(TUNER_SC_MODE);
                break;
            }
            
            // Set Start Frequency
        #ifdef D_TUNER_SEEK_A_CIRCLE
            sTuner.SeekStartFreq = TUNER_CURRENT_FREQ;
            sTuner.bSeekWrapAround = 1;    // Check Wrap Around!!
        #else
            if(DIRECTION_UP == sTuner.bSeekDirect)    
            {
                sTuner.SeekStartFreq = sTuner.FreqMax;
            }
            else
            {
                sTuner.SeekStartFreq = sTuner.FreqMin;
            }

            // Check Wrap Around!!
            if(sTuner.SeekStartFreq == TUNER_CURRENT_FREQ)
            {
                sTuner.bSeekWrapAround = 1;
            }
        #endif//D_TUNER_SEEK_A_CIRCLE
        
            // Seek Station Check Delay : FM AM DX LOC
            if(TUNER_BAND_AM)
            {
                sTuner.SeekChkDelay = TunerDelay(T80MS);
            }
            else
            {
                sTuner.SeekChkDelay = TunerDelay(T30MS);
            }
            
            // Ams Buffer Reset
            if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)
            {
                uint8_t u8Temp;
            #ifndef D_TUNER_AMS_CURRENT_BAND    
                uint8_t u8BandNum;
            
                u8BandNum = (TUNER_PRESET_MAX * (sTuner.BandEnd - sTuner.BandStart + 1));
                if(TUNER_BAND_FM)
                {
                    TUNER_CURRENT_BAND = TUNER_BAND_FM1;
                }
                else if(TUNER_BAND_AM)
                {
                    TUNER_CURRENT_BAND = TUNER_BAND_AM1;
                }
                else
                {
                    TUNER_CURRENT_BAND = TUNER_BAND_OIRT1;
                }
            
                for(u8Temp = 0; u8Temp < u8BandNum; u8Temp++)
                {
                    sTuner.asAmsBuff[u8Temp].Qual = 0;
                    sTuner.asAmsBuff[u8Temp].Freq = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][u8Temp];
                }
    
                //Currently
                TUNER_CURRENT_FREQ = sTuner.FreqMin;
                TUNER_CURRENT_PRESET = TUNER_PRESET_1;
                sTuner.SeekStartFreq = sTuner.FreqMin;
                sTuner.AmsValidStaNum = 0;
				
            #else
                for (u8Temp = 0; u8Temp < TUNER_PRESET_MAX; u8Temp++)
                {
                    sTuner.asAmsBuff[u8Temp].Freq = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][u8Temp];
                    sTuner.asAmsBuff[u8Temp].Qual = 0;
                }      
                sTuner.SeekStartFreq = TUNER_CURRENT_FREQ;
                sTuner.SeekPresetBak = TUNER_CURRENT_PRESET;

                #ifdef D_TUNER_LIST
                for (u8Temp = 0; u8Temp < LIST_BUFFER_MAX; u8Temp++)
                {
                    sTuner.asTmpList[u8Temp].Freq = 0;
                    sTuner.asTmpList[u8Temp].Qual = 0;
                }
                sTuner.UpdateListBak = TUNER_CURRENT_FREQ;
                sTuner.SeekStartFreq = sTuner.FreqMin;
                sTuner.SeekPresetBak = TUNER_CURRENT_PRESET;
                TUNER_CURRENT_FREQ = sTuner.FreqMin;
                sTuner.TmpListNum = 0;
                #endif
		
            #endif//D_TUNER_AMS_CURRENT_BAND    
                sTuner.bSeekWrapAround = 1;
            }

            // Correct Abnormal Frequency to  Standard
            if(((TUNER_CURRENT_FREQ - sTuner.FreqMin) % sTuner.TuneStep) != 0)
            {
                TUNER_CURRENT_FREQ = \
                    ((TUNER_CURRENT_FREQ - sTuner.FreqMin) / sTuner.TuneStep) \
                        * sTuner.TuneStep + sTuner.FreqMin;
                if(DIRECTION_DN == sTuner.bSeekDirect)
                {
                    TUNER_CURRENT_FREQ += sTuner.TuneStep;
                    if(TUNER_CURRENT_FREQ > sTuner.FreqMax)
                        TUNER_CURRENT_FREQ = sTuner.FreqMax;
                }
            }

            if((TUNER_BAND_FM) && (5 == sTuner.TuneStep))
            {
                if(TUNER_CURRENT_FREQ % 10)
                {
                    TUNER_CURRENT_FREQ += sTuner.TuneStep;
                    if(TUNER_CURRENT_FREQ > sTuner.FreqMax)
                        TUNER_CURRENT_FREQ = sTuner.FreqMax;
                }
            }
        #ifdef D_TUNER_SEEK_A_CIRCLE
            sTuner.SeekStartFreq = TUNER_CURRENT_FREQ;
        #endif
            Tuner_GotoMidStep(TUNER_SC_MODE);
            break;
            
        // Set Seek Mode
        case TUNER_SC_MODE:
            SubResult = Tuner_ConfigMode(Mode);
            if(SUBLAYER_DONE == SubResult)
            {
                Tuner_GotoMidStep(TUNER_SC_SET_FREQ);
            }
            break;

        // Set Start Frequency
        case TUNER_SC_SET_FREQ:
            SubResult = Tuner_SetFreq(TUNER_CURRENT_FREQ);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.MidLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;            
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
    }    

    return (Result);
}
/**********************************************************
 * @function    Tuner_SeekFirst
 * @brief      Seek the firstly frequency of currently band while 
 *            Doing Auto Memory Scan
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_SeekFirst(void)
{
    return (Tuner_ChkQual(QUAL_CHK_NORMAL));
}
/**********************************************************
 * @function    Tuner_ChkQual
 * @brief      Check Currently Station whether a valid Station    
 * @param      None                
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_ChkQual(uint8_t ChkMode)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.MidLayerDelay))
        return (Result);    
    
    switch(sTuner.MidLayerStep)
    {
        // Initialize check quality related variables
        case TUNER_CHK_QUAL_PREPARE:
            sTuner.bGoodStation = 0;
            TunerSetDelay(sTuner.MidLayerDelay,sTuner.SeekChkDelay);    // Check Delay
            Tuner_GotoMidStep(TUNER_CHK_QUAL_CHECK);
            break;

        // Get Quality and Checking!
        case TUNER_CHK_QUAL_CHECK:
            SubResult = Tuner_CheckStation(ChkMode);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.MidLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
    }    

    return (Result);    
}
/**********************************************************
 * @function    Tuner_RdsSeekStatus
 * @brief      Return Rds Seek Result
 * @param      None                    
 * @retval     Rds Seek Result
 **********************************************************/
uint8_t Tuner_RdsSeekStatus(void)
{
    uint8_t Result = RDS_SEEKSTATUS_SEEKING;

    if(TUNER_BAND_FM)
    {
        if(sTuner.uSeekState.sSsBitMap.bPTYSeek)
        {
            //if(sRds.PtyValid == sTuner.PtySelect)
            if(sRds.Pty == sTuner.PtySelect)
            {
                Result = 1;
            }
        }
        else if(TaSetting)
        {
            //if(sRds.TAValid || sRds.TPValid)
            if(sRds.TA || sRds.TPValid)
            {
                Result = 1;
            }
        }
        else if(AfSetting)
        {
            if((sRds.Level >= 1) || (sRds.MaxLevel >= 1))
            {
                Result = 1;
            }
        }
        else
        {
            Result = 1;
        }
    }
    else
    {
        Result = 1;
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_Preview
 * @brief      Preview Got Station
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Preview(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.MidLayerDelay))
        return (Result);
    
    switch(sTuner.MidLayerStep)
    {
        // Exit Seek Mode for Preview
        case TUNER_PREVIEW_CONFIG:    
            SubResult = Tuner_PreviewConfig();
            if(SUBLAYER_DONE == SubResult)
            {
                Tuner_GotoMidStep(TUNER_PREVIEW_UNMUTE);
            }    
            break;

        // Release Mute firstly, then goto PREVIEW step
        case TUNER_PREVIEW_UNMUTE:        
            SubResult = Tuner_ReqMute(MUTE_OFF,TUNER_MID_SEEK);
            if(SUBLAYER_DONE == SubResult)
            {
                Tuner_GotoMidStep(TUNER_PREVIEW_PREVIEW);
            }            
            break;

        // Call Specific Drv for Preview 
        case TUNER_PREVIEW_PREVIEW:    
            //if(TUNER_SUBLAYER_DONE == SubResult)
            {    
                if(sTuner.uSeekState.sSsBitMap.bAutoScan)
                    sTuner.MidLayerOverTime = TunerDelay(T5S);
                else if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)
                    sTuner.MidLayerOverTime = TunerDelay(T3S);
                Tuner_GotoMidStep(TUNER_PREVIEW_REMAIN);
            }
            break;

        // Remain Preview for Specific Time
        case TUNER_PREVIEW_REMAIN:        
            if(OverTimeExpired(sTuner.MidLayerOverTime))
            {
                Tuner_GotoMidStep(TUNER_PREVIEW_MUTE);
            }
            break;

        // comeback to Mute state, go on seeking
        case TUNER_PREVIEW_MUTE:        
            SubResult = Tuner_ReqMute(MUTE_ON,TUNER_MID_SEEK);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.MidLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }    
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
    }    

    return (Result);    
}
/**********************************************************
 * @function    Tuner_SaveAll
 * @brief      Tuner Save Important Datum to EEPROM
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_SaveAll(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Tuner_PowerOff
 * @brief      Close Tuner Power according Currently Setup(RDS Setting)
 *                 while Src Change or Power State Change
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_PowerOff(void)
{
    if((sTuner.PwrState == 0))    // System Off or Src Switch but No Rds Setting On
       // ||(!(TaSetting || AfSetting)))
    {
        // Close Power and Antenna Power
        //PM_UnitPowerSet(PM_UNIT_ANT,OFF);
        // Reset IO Port To Sleep State
        IO_Set(IO_IDX_PHANTOM_POWER1,PIN_OUTPUT,INVALID);
        IO_Set(IO_IDX_PHANTOM_POWER2,PIN_OUTPUT,INVALID);
    }

    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Tuner_VariableCheck
 * @brief      Check Parameters from EEPROM
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_VariableCheck(void)
{
    //Sync Region Setting
    sTunerKeep.Region = g_tSysRomData.uGenBlock.tBlock.cRadioField;
    if(sTunerKeep.Region >= REGION_MAX)
    {
        sTunerKeep.Region = REGION_EUROPE;
    }
    //sTunerKeep.RdsSetting 
    sTunerKeep.AntPwr = g_tSysRomData.uGenBlock.tBlock.tFlag4.bAntennaSupply;
    sTunerKeep.AntGainAttn = g_tSysRomData.uGenBlock.tBlock.AntGain;    
    if(sTunerKeep.AntGainAttn > ANT_GAIN_42DB)
    {
        sTunerKeep.AntGainAttn = ANT_GAIN_0DB;
    }

	#ifndef R103_H15T_OVERSEAS  //国内版强制设置为东南亚
	  sTunerKeep.Region = REGION_USER;
	#endif

	  
    if(TUNER_CURRENT_BAND >= TUNER_BAND_MAX)
    {
        TUNER_CURRENT_BAND = TUNER_BAND_FM1;
    }
#ifdef D_TUNER_LIST
    if(TUNER_CURRENT_PRESET > sTunerKeep.ListNum)
    {
      TUNER_CURRENT_PRESET = TUNER_PRESET_NULL;
    }
#else
    if(TUNER_CURRENT_PRESET > TUNER_PRESET_MAX)
    {
        TUNER_CURRENT_PRESET = TUNER_PRESET_NULL;
    }
#endif
	sTuner.BandNum = sTunerRegion[sTunerKeep.Region].BandNum;
	sTuner.bDatumReady = 1;

	//if(sTunerKeep.bPausestate == 1)
		sTunerKeep.bPausestate = 0;	
}
/**********************************************************
 * @function    Tuner_VariableReset
 * @brief      Reset All of  Variables of Tuner to Default Value While 
 *            Tuner Task Cold Start or Switch Band.
 *            Settings and ~~
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_VariableReset(void)
{
    //According to Recieved Msg, Reset Info Variables by Reading from EEPROM
        //or do nothing because of info parameter are keep same in the RAM 
    uint8_t u8Temp1 = 0;
    uint8_t u8Temp2 = 0;
    uint8_t u8Temp3 = 0;
    //4~~~Settings
    sTunerKeep.Region = REGION_USER;//默认收音区域,国内版是东南亚  海外版是南美洲
    g_tSysRomData.uGenBlock.tBlock.cRadioField = sTunerKeep.Region;//snake20170210 将复位之后的收音区域存储到EEPROM中
    sTunerKeep.RdsSetting = RDS_SET_RDS;
    StereoSetting = STEREO_AUTO;    //Default :Force Mono Off
    LocDxSetting = TUNER_DX;// Default DX 
    TaSetting = TA_SET_OFF;
    AfSetting = AF_SET_OFF;
    RegSetting = REG_SET_OFF;
    EonSetting = EON_SET_OFF;
    PtySetting = PTY_SET_OFF;
    sTunerKeep.sBakSetting.Total = sTunerDat.sSetting.Total;
    
    // Reset Preset List to Default
    for(u8Temp1 = 0; u8Temp1 < TUNER_PRESET_MAX; u8Temp1++)
    {
    for(u8Temp2=0;u8Temp2<TUNER_BAND_AM1;u8Temp2++)
    	{
        sTunerDat.sInfo.Preset[u8Temp2][u8Temp1] = sTunerRegion[sTunerKeep.Region].BandFM[u8Temp1];
    	}
    for(u8Temp2=TUNER_AM_START;u8Temp2<TUNER_OIRT_START;u8Temp2++)
    	{
        sTunerDat.sInfo.Preset[u8Temp2][u8Temp1] = sTunerRegion[sTunerKeep.Region].BandAM[u8Temp1];
        sTunerDat.sInfo.Preset[u8Temp2+2][u8Temp1] = sTunerRegion[sTunerKeep.Region].BandOIRT[u8Temp1];
    	}
   
    }
    sTuner.BandNum = sTunerRegion[sTunerKeep.Region].BandNum;

    //Reset Valid List
    for(u8Temp1 = 0; u8Temp1 < VSCAN_BUFFER_MAX; u8Temp1++)
    {
        sTunerKeep.ValidList[u8Temp1] = 0; // All Reset to Zero, Means no valid frequency yet!!
    }
#ifdef D_TUNER_LIST
    sTunerKeep.ListNum = 0;
    sTunerKeep.AmListNum = 1;// 15  snake20161021 当没有搜索到有效电台的时候,只发送一个电台信息给OS...长安要求的做法
    sTunerKeep.FmListNum = 1;// 15 

    for(u8Temp1 = 0; u8Temp1 < LIST_BUFFER_MAX; u8Temp1++)
    {
      sTunerKeep.FmList[u8Temp1] = FM_FREQ_MIN; // All Reset to FM_FREQ_MIN, Means no valid frequency yet!!
      sTunerKeep.AmList[u8Temp1] = AM_FREQ_MIN; // All Reset to AM_FREQ_MIN, Means no valid frequency yet!!
    }
#endif//D_TUNER_LIST 


    // Reset Band Attribute 
    for(u8Temp1 = 0; u8Temp1 < TUNER_BAND_MAX; u8Temp1++)
    {
        sTunerKeep.asBandAttri[u8Temp1].Preset = TUNER_PRESET_1;    
        sTunerKeep.asBandAttri[u8Temp1].Freq = sTunerDat.sInfo.Preset[u8Temp1][0];
    }
    //Reset PS List
    for(u8Temp1 = 0; u8Temp1 < (TUNER_FM_END + 1); u8Temp1++)
    {
        for(u8Temp2 = 0; u8Temp2 < TUNER_PRESET_MAX; u8Temp2++)
        {
            for(u8Temp3 = 0; u8Temp3 < 8; u8Temp3++)
            {
                sTunerKeep.PsList[u8Temp1][u8Temp2][u8Temp3] = ' ';
            }
        }
    }
    
    // Reset Currently Info 
    TUNER_CURRENT_BAND = TUNER_BAND_FM1;
    TUNER_CURRENT_PRESET = sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Preset;
    TUNER_CURRENT_FREQ = sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq;
    sTuner.BandStart = TUNER_FM_START; 
    sTuner.BandEnd = TUNER_FM_END;     

    sTunerKeep.ValidNumber = 0;
    sTunerKeep.ValidHighlight = 0;
    sTunerKeep.AntPwr = 1;
    sTunerKeep.AntGainAttn = ANT_GAIN_0DB;

	sTunerKeep.bPausestate = 0;
	sTunerKeep.bBakPause = 0;	
}
/**********************************************************
 * @function    Tuner_FmPresetReset
 * @brief      Tuner_FmPresetReset
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_FmPresetReset(void)
{
    uint8_t u8Temp1 = 0;
    uint8_t u8Temp2 = 0;
    uint8_t u8Temp3 = 0;

    
    // Reset Preset List to Default
    for(u8Temp1 = 0; u8Temp1 < TUNER_PRESET_MAX; u8Temp1++)
    {
    for(u8Temp2=0;u8Temp2<TUNER_BAND_AM1;u8Temp2++)
    	{
        sTunerDat.sInfo.Preset[u8Temp2][u8Temp1] = sTunerRegion[sTunerKeep.Region].BandFM[u8Temp1];
    	}
    }
}

/**********************************************************
 * @function    Tuner_FmPresetReset
 * @brief      Tuner_FmPresetReset
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_AmPresetReset(void)
{
    uint8_t u8Temp1 = 0;
    uint8_t u8Temp2 = 0;
    uint8_t u8Temp3 = 0;

    
    // Reset Preset List to Default
    for(u8Temp1 = 0; u8Temp1 < TUNER_PRESET_MAX; u8Temp1++)
    {
    for(u8Temp2=TUNER_AM_START;u8Temp2<TUNER_OIRT_START;u8Temp2++)
    	{
        sTunerDat.sInfo.Preset[u8Temp2][u8Temp1] = sTunerRegion[sTunerKeep.Region].BandAM[u8Temp1];
        sTunerDat.sInfo.Preset[u8Temp2+2][u8Temp1] = sTunerRegion[sTunerKeep.Region].BandOIRT[u8Temp1];
    	}
   
    }

}

/**********************************************************
 * @function    Tuner_VariableInit
 * @brief      Initialize Specific Variables While
 *            Tuner Task Warm Start.
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_VariableInit(void)
{
	sTuner.uSeekState.SsTotal = 0;    // Reset Seek State
	sTuner.ReqMuteStep = OPERATION_0;
	sTuner.ReqMuteLock = TUNER_MID_NULL;
	sTuner.DispPS[0] = 0xFF;
	sTuner.DispRT[0] = 0xFF;

	sTuner.BandChk = 0xFF;
	sTuner.PresetChk = 0xFF;
	sTuner.SignalStrChk = 0xFF;
	sTuner.StateChk = 0xFF;
	sTuner.FreqChk = 0xFF;
	sTuner.SettingChk = 0xFF;
	sTuner.PtySelect = 1;
	sTuner.PtyChk = 0xFF;
	
	sTuner.ValidDelay = TunerDelay(T30S);
	sTuner.bTrigger = 0;
}
/**********************************************************
 * @function    Tuner_BandInit
 * @brief      Initialize related variables of Currently Band             
 * @param      None                    
 * @retval     None
 **********************************************************/
void Tuner_BandInit(void)
{
    // Band Related Frequency range and Tune step
    if(TUNER_BAND_OIRT)
    {
        sTuner.FreqMin = OIRT_FREQ_MIN;
        sTuner.FreqMax = OIRT_FREQ_MAX;
        sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].OIRTStep; 
        sTuner.BandStart = TUNER_OIRT_START; 
        sTuner.BandEnd = TUNER_OIRT_END;     
    }
    else if(TUNER_BAND_AM)
    {
        sTuner.FreqMin = AM_FREQ_MIN;
        sTuner.FreqMax = AM_FREQ_MAX;
        sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].AMStep; 
        sTuner.BandStart = TUNER_AM_START; 
        sTuner.BandEnd = TUNER_AM_END;     
    }
    else
    {
        sTuner.FreqMin = FM_FREQ_MIN;
        sTuner.FreqMax = FM_FREQ_MAX;
        sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].FMStep; 
        sTuner.BandStart = TUNER_FM_START; 
        sTuner.BandEnd = TUNER_FM_END;     
    }

    TUNER_CURRENT_FREQ = sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq;
    TUNER_CURRENT_PRESET = sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Preset;
    if(TUNER_CURRENT_PRESET == TUNER_PRESET_NULL)
        TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
		sTunerKeep.ValidHighlight = TUNER_CURRENT_PRESET;
}


/**********************************************************
 * @function    Tuner_SetRadioArea
 * @brief      Set Radio Area.设置频点范围,步进,当前频点恢复到默认最小值,清除收藏列表...
 * @param      uint8_t Region:  Radio Area                
 * @retval     None
 //snake20170215
 **********************************************************/
void Tuner_SetRadioArea(uint8_t Region)
{
    uint8_t u8Temp1 = 0;
	uint8_t i;
	
	sTunerKeep.Region = Region;
	if(TUNER_BAND_OIRT)
    {
    	//设置频点范围
        sTuner.FreqMin = OIRT_FREQ_MIN;
        sTuner.FreqMax = OIRT_FREQ_MAX;
		//设置当前频点
		TUNER_CURRENT_FREQ = OIRT_FREQ_MIN;
		//设置步进
        sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].OIRTStep; 
		//设置开始结束
        sTuner.BandStart = TUNER_OIRT_START; 
        sTuner.BandEnd = TUNER_OIRT_END;
		
    }
    else if(TUNER_BAND_AM)
    {
        sTuner.FreqMin = AM_FREQ_MIN;
        sTuner.FreqMax = AM_FREQ_MAX;
		
		TUNER_CURRENT_FREQ = AM_FREQ_MIN;
		
        sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].AMStep; 
        sTuner.BandStart = TUNER_AM_START; 
        sTuner.BandEnd = TUNER_AM_END;     
    }
    else
    {
        sTuner.FreqMin = FM_FREQ_MIN;
        sTuner.FreqMax = FM_FREQ_MAX;
		TUNER_CURRENT_FREQ = FM_FREQ_MIN;
        sTuner.TuneStep = sTunerRegion[sTunerKeep.Region].FMStep; 
        sTuner.BandStart = TUNER_FM_START; 
        sTuner.BandEnd = TUNER_FM_END;     
    }

	Tuner_debug(_T("new--sTunerKeep.Region = %d-------AM:%ld~%ld,FM:%ld~%ld\n",sTunerKeep.Region,AM_FREQ_MIN,AM_FREQ_MAX,FM_FREQ_MIN,FM_FREQ_MAX));
		
	
    if(TUNER_CURRENT_PRESET == TUNER_PRESET_NULL)
        TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
	sTunerKeep.ValidHighlight = TUNER_CURRENT_PRESET;

	//清空收藏列表
    sTunerKeep.ListNum = 1;
    sTunerKeep.AmListNum = 1;// 15  snake20161021 当没有搜索到有效电台的时候,只发送一个电台信息给OS...长安要求的做法
    sTunerKeep.FmListNum = 1;// 15 

    for(u8Temp1 = 0; u8Temp1 < LIST_BUFFER_MAX; u8Temp1++)
    {
      sTunerKeep.FmList[u8Temp1] = FM_FREQ_MIN; // All Reset to FM_FREQ_MIN, Means no valid frequency yet!!
      sTunerKeep.AmList[u8Temp1] = AM_FREQ_MIN; // All Reset to AM_FREQ_MIN, Means no valid frequency yet!!
    }

	
  if(TUNER_BAND_FM)
  {
    for(u8Temp1 = 0; u8Temp1 < LIST_BUFFER_MAX; u8Temp1++)
    {
      sTunerKeep.FmList[u8Temp1] = FM_FREQ_MIN; // All Reset to FM_FREQ_MIN, Means no valid frequency yet!!
      sTunerKeep.ValidList[u8Temp1] = FM_FREQ_MIN; //Reset Valid List
    }
  }
  else if(TUNER_BAND_AM)
  {
    for(u8Temp1 = 0; u8Temp1 < LIST_BUFFER_MAX; u8Temp1++)
    {
      sTunerKeep.AmList[u8Temp1] = AM_FREQ_MIN; // All Reset to AM_FREQ_MIN, Means no valid frequency yet!!
      sTunerKeep.ValidList[u8Temp1] = AM_FREQ_MIN; //Reset Valid List
    }
  }
  
  	Tuner_FmPresetReset();
	Tuner_AmPresetReset();
	// Reset Band Attribute 20170404
	for(i=0;i<TUNER_BAND_MAX;i++)
	{
        sTunerKeep.asBandAttri[i].Preset = TUNER_PRESET_1;    
        sTunerKeep.asBandAttri[i].Freq = sTunerDat.sInfo.Preset[i][0];
	}
	//snake20170324  设置当前频点
	Tuner_SetFreq(TUNER_CURRENT_FREQ);
  
	_SendMsgToHMI(MS_SRC_UPLOAD_INFO,/*(SRC_TYPE_TUNER<<8)|*/OP_TUNER_UPD_VALID_LIST,&sTunerKeep);

	_SendMsgToHMI(MS_SRC_UPLOAD_INFO,/*(SRC_TYPE_TUNER<<8)|*/OP_TUNER_UPD_AREA,&sTunerKeep);
}


/**********************************************************
 * @function    Tuner_GotoStep
 * @brief      Switch Midlayer Function Control Step
 * @param      uint8_t x : Step Will Goto                    
 * @retval     None
 **********************************************************/
void Tuner_GotoMidStep(uint8_t x)
{
    sTuner.MidLayerStep = x;
    sTuner.DriverLayerStep = OPERATION_0;
}
/**********************************************************
 * @function    Tuner_StepChangeFreq
 * @brief      Step Change Currently Frequency         
 * @param      None                
 * @retval     None
 **********************************************************/
void Tuner_StepChangeFreq(uint8_t Direct)
{
    uint8_t TmpStep;

    TmpStep = sTuner.TuneStep;
    if((TUNER_BAND_FM) && sTuner.uSeekState.SsTotal)
    {
        if(5 == sTuner.TuneStep)
        {
            TmpStep = 10;
        }
    }

    if(Direct == DIRECTION_UP)    // Increase
    {
        TUNER_CURRENT_FREQ += TmpStep;
        if(TUNER_CURRENT_FREQ > sTuner.FreqMax)
            TUNER_CURRENT_FREQ = sTuner.FreqMin;
    }
    else if(Direct == DIRECTION_DN)    // Decrease
    {
        TUNER_CURRENT_FREQ -= TmpStep;
        if(TUNER_CURRENT_FREQ < sTuner.FreqMin)
            TUNER_CURRENT_FREQ = sTuner.FreqMax;
    }
    // update the preset attribute of the new frequency
    TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
}
/**********************************************************
 * @function    Tuner_SortPreset
 * @brief      Sort Received Station and Fresh new Preset List
 *            while Stop AMS 
 * @param      None                
 * @retval     None
 **********************************************************/
void Tuner_SortPreset(void)
{
    uint8_t u8Temp = 0;
#ifndef D_TUNER_AMS_CURRENT_BAND        
    uint8_t u8BandNum;
    uint16_t* Tmp;

    if(TUNER_BAND_FM)
    {
        Tmp = (uint16_t *)sTunerRegion[sTunerKeep.Region].BandFM;
    }
    else if(TUNER_BAND_AM)
    {
        Tmp = (uint16_t *)sTunerRegion[sTunerKeep.Region].BandAM;
    }
    else
    {
        Tmp = (uint16_t *)sTunerRegion[sTunerKeep.Region].BandOIRT;
    }
    u8BandNum = (TUNER_PRESET_MAX * (sTuner.BandEnd - sTuner.BandStart + 1));

    //Reset Preset List to Default
//    for (u8Temp = 0; u8Temp < TUNER_PRESET_MAX; u8Temp++)
//    {
//        sTunerDat.sInfo.Preset[sTuner.BandStart + (u8Temp / 6)][(u8Temp % 6)] = Tmp[u8Temp];
//    }
//    for(u8Temp = TUNER_PRESET_MAX; u8Temp < u8BandNum; u8Temp++)
//        sTunerDat.sInfo.Preset[sTuner.BandStart + (u8Temp / 6)][(u8Temp % 6)] = sTuner.FreqMin;
    
    //Get The New Preset List
    for (u8Temp = 0; u8Temp < u8BandNum; u8Temp++)
    {
        if(0 == sTuner.asAmsBuff[u8Temp].Qual) //Valid Station Check
            break;
        
        sTunerDat.sInfo.Preset[sTuner.BandStart + (u8Temp / 6)][(u8Temp % 6)] = sTuner.asAmsBuff[u8Temp].Freq;
    } 
    
    // Reinit Band's Attribute
    for(u8Temp = sTuner.BandStart; u8Temp < (sTuner.BandEnd + 1); u8Temp++)
    {
        sTunerKeep.asBandAttri[u8Temp].Preset = TUNER_PRESET_1;    
        sTunerKeep.asBandAttri[u8Temp].Freq = sTunerDat.sInfo.Preset[u8Temp][0];
    }

    // Get Currently Infoes
    if(TUNER_BAND_FM)
        TUNER_CURRENT_BAND = TUNER_BAND_FM1;
    else if(TUNER_BAND_OIRT)
        TUNER_CURRENT_BAND = TUNER_BAND_OIRT1;
    else 
        TUNER_CURRENT_BAND = TUNER_BAND_AM1;

    TUNER_CURRENT_PRESET = TUNER_PRESET_1;
    TUNER_CURRENT_FREQ = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET - 1];

    // Output Newly Band Related Preset List
    _SendMsgToHMI(MS_SRC_UPLOAD_INFO,OP_TUNER_UPD_CURRENT_BAND,&sTunerDat);
#else
    //Check Got Valid Station?
  #ifdef D_TUNER_LIST
    if(sTuner.FuncStep == TUNER_PWROFF_SORT)
    {
    #ifdef D_TUNER_SCANBREAK
      TUNER_CURRENT_FREQ = sTuner.UpdateListBak;
      TUNER_CURRENT_PRESET = sTuner.SeekPresetBak;
    #endif
    }
    else
    {
      sTunerKeep.ListNum = 0;
      if(TUNER_BAND_FM)
      {
        for(u8Temp = 0; u8Temp < LIST_BUFFER_MAX; u8Temp++)
        {
          sTunerKeep.FmList[u8Temp] = FM_FREQ_MIN; // All Reset to FM_FREQ_MIN, Means no valid frequency yet!!
          sTunerKeep.ValidList[u8Temp] = FM_FREQ_MIN; //Reset Valid List
        }
      }
      else if(TUNER_BAND_AM)
      {
        for(u8Temp = 0; u8Temp < LIST_BUFFER_MAX; u8Temp++)
        {
          sTunerKeep.AmList[u8Temp] = AM_FREQ_MIN; // All Reset to AM_FREQ_MIN, Means no valid frequency yet!!
          sTunerKeep.ValidList[u8Temp] = AM_FREQ_MIN; //Reset Valid List
        }
      }
      
      for(u8Temp = 0; u8Temp < LIST_BUFFER_MAX; u8Temp++)
      {
        if(0 == sTuner.asTmpList[u8Temp].Freq)
        {
			
			if(u8Temp == 0)
			{
				if(TUNER_BAND_FM)
				{
					sTunerKeep.FmListNum = 1;
					sTunerKeep.ListNum = sTunerKeep.FmListNum;
				}
				else
				{
					sTunerKeep.AmListNum = 1;
					sTunerKeep.ListNum = sTunerKeep.AmListNum;
				}
			}
			
			break;
        }
        sTunerKeep.ValidList[u8Temp] = sTuner.asTmpList[u8Temp].Freq;
        if(LIST_BUFFER_MAX==sTunerKeep.ListNum)
	  	break;
        sTunerKeep.ListNum += 1;
        if(TUNER_BAND_FM)
        {
          sTunerKeep.FmList[u8Temp] = sTuner.asTmpList[u8Temp].Freq;
          sTunerKeep.FmListNum = sTunerKeep.ListNum;
        }
        else
        {
          sTunerKeep.AmList[u8Temp] = sTuner.asTmpList[u8Temp].Freq;
          sTunerKeep.AmListNum = sTunerKeep.ListNum;
        }
      }
      TUNER_CURRENT_FREQ = sTunerKeep.ValidList[0];
      TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
    }
    //Update Band Attri
    sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq = TUNER_CURRENT_FREQ;
    sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Preset = TUNER_CURRENT_PRESET;
    _SendMsgToHMI(MS_SRC_UPLOAD_INFO,OP_TUNER_UPD_CURRENT_BAND,&sTunerDat);
    _SendMsgToHMI(MS_SRC_UPLOAD_INFO,(SRC_TYPE_TUNER<<8)|OP_TUNER_UPD_VALID_LIST,&sTunerKeep);
  #else
    if(sTuner.asAmsBuff[0].Qual > 0)
    {
        //Get The New Preset List
        for (u8Temp = 0; u8Temp < TUNER_PRESET_MAX; u8Temp++)
        {
            if(sTuner.asAmsBuff[u8Temp].Qual > 0)
                sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][u8Temp] = sTuner.asAmsBuff[u8Temp].Freq;
        }
    
        // Reinit Band's Attribute
        sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Preset = TUNER_PRESET_1;    
        sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Freq = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][0];

        TUNER_CURRENT_PRESET = TUNER_PRESET_1;
        TUNER_CURRENT_FREQ = sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][TUNER_CURRENT_PRESET - 1];

        // Output Newly Band Related Preset List
        _SendMsgToHMI(MS_SRC_UPLOAD_INFO,OP_TUNER_UPD_CURRENT_BAND,&sTunerDat);
    }
    else
    {
        //TUNER_CURRENT_PRESET = sTuner.SeekPresetBak;
        //sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Preset = TUNER_CURRENT_PRESET;  
        TUNER_CURRENT_PRESET = Tuner_CheckPreset(TUNER_CURRENT_FREQ);
        sTunerKeep.asBandAttri[TUNER_CURRENT_BAND].Preset = TUNER_CURRENT_PRESET;
    }
  #endif
#endif//D_TUNER_AMS_CURRENT_BAND    
} 
/**********************************************************
 * @function    Tuner_BreakAF
 * @brief      Break AF Checking          
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_BreakAF(void)
{
    uint8_t Result = SUBLAYER_DOING;

    //Result = Rds_BreakAFCheck();
    Result = SUBLAYER_DONE;
    
    return (Result);
}
/**********************************************************
 * @function    Tuner_InsertNewStation
 * @brief      Insert New Valid Station to Temporary Buffer and Insert
 *            to the rightly Position according Quality 
 * @param      TUNER_AMS_MEM_STRUCT *psDest
 *            TUNER_AMS_MEM_STRUCT *psNewStation
 * @retval     None
 **********************************************************/
void Tuner_InsertNewStation(TUNER_AMS_MEM_STRUCT *psDest,TUNER_AMS_MEM_STRUCT *psNewStation, uint8_t Num)
{
    uint8_t u8Temp1,u8Temp2;    // Loop control 
    uint8_t u8BuffNum = Num;    

    // Insert NewStation to Rightly Position
    for(u8Temp1 = 0; u8Temp1 < u8BuffNum; u8Temp1++)
    {
        if(psNewStation->Qual > psDest[u8Temp1].Qual)
        {
            //Got a Better Station, Insert and Move Old station's position, desert the last one!
            for(u8Temp2 = (u8BuffNum - 1); u8Temp2 > u8Temp1; u8Temp2--)
            {
                psDest[u8Temp2] = psDest[u8Temp2 - 1];    
            }
            // Insert the New One!
            psDest[u8Temp1] = *psNewStation;
            break;
        }
    }
}

/**********************************************************
 * @function    Tuner_SortStationAccordFreq 长安要求按顺序从小到大保存
1、不影响之前搜索流程，
2、如果有超出18 个台时，还是按之前流程检出18个最强台
       最后再按频率大小排序
 **********************************************************/
void Tuner_SortStationAccordFreq(TUNER_AMS_MEM_STRUCT *psDest,uint8_t Num)
{
    uint8_t i,j;
    uint8_t QualTmp;
    uint16_t FreqTmp;
	uint8_t TempNum = Num;

    for( i = 0 ; i < Num; i++)//排序...
    {
        CLEAR_WATCHDOG();
        for( j = (i+1) ; j < Num ; j++)
        {	
        	if((psDest[i].Freq > psDest[j].Freq) || (psDest[i].Freq == 0))
        	{
				FreqTmp = psDest[i].Freq;
				psDest[i].Freq = psDest[j].Freq;
				psDest[j].Freq = FreqTmp;
#if 0			
			QualTmp = psDest[i].Qual;
			psDest[i].Qual = psDest[j].Qual;
			psDest[j].Qual = QualTmp;
#endif			
			}
			else if(psDest[i].Freq == psDest[j].Freq)//snake20161021对重复的电台进行过滤 
			{
				psDest[j].Freq = 0;
			}
		}
    }

	//去除多余的电台
	for(i = 0;i <= Num;i++)
	{
		if(psDest[0].Freq == 0)
			TempNum--;
	}
	Num = TempNum;
	
}
/**********************************************************
 * @function    Tuner_ReqMute
 * @brief      Require New Mute State from Audio Task
 *            Check Result and Return Execute State
 * @param      uint8_t Mode: Require Mute Type                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_ReqMute(uint8_t Mode, uint8_t MuteId)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t TmpMuteType;

    //Set Locked ID
    if(TUNER_MID_NULL == sTuner.ReqMuteLock)
    {
        sTuner.ReqMuteLock = MuteId;
    }

    //Check Locked: Mute Require in Use
    //if(MuteId != sTuner.ReqMuteLock)
    {
       // return (SUBLAYER_DOING);
    }

    switch(sTuner.ReqMuteStep)
    {
        //Require Mute from Audio Task
        case TUNER_MUTE_REQ:    
            if(MUTE_ON == Mode)
            {    
                TmpMuteType = TYPE_F_S_MUTE;
            }
            else
            {
                TmpMuteType = TYPE_F_S_UNMUTE;
            }
            _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE_REQ,SOURCE_TUNER,TmpMuteType,0,0);
            sTuner.ReqMuteDelay = TunerDelay(T100MS);
            sTuner.ReqMuteStep = TUNER_MUTE_CHK;
            break;
            
        // Check Mute State.
        case TUNER_MUTE_CHK:
            if(MUTE_ON == Mode)
            {
                if(MASK_F_SMUTE & Audio_Api_GetAchMute(SOURCE_TUNER))
                {
                    sTuner.ReqMuteStep = OPERATION_0;
                    sTuner.ReqMuteLock = TUNER_MID_NULL;
                    Result = SUBLAYER_DONE;
                }
            }
            else
            {
                if(0x00 == (MASK_F_SMUTE & Audio_Api_GetAchMute(SOURCE_TUNER)))
                {
                    sTuner.ReqMuteStep = OPERATION_0;
                    sTuner.ReqMuteLock = TUNER_MID_NULL;
                    Result = SUBLAYER_DONE;
                }
            }
            if(0 == sTuner.ReqMuteDelay) // Time out
            {
                sTuner.ReqMuteStep = OPERATION_0;
                sTuner.ReqMuteLock = TUNER_MID_NULL;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            sTuner.ReqMuteStep = OPERATION_0;
            sTuner.ReqMuteLock = TUNER_MID_NULL;
            break;
    }

    return (Result);    
}
#ifdef D_TUNER_LIST
/**********************************************************
 * @function    Tuner_CheckPreset
 * @brief      Check the Specific Frequency whether is a Preset of
 *            Currently Band
 * @param      uint16_t u16Freq                    
 * @retval     None
 **********************************************************/
uint8_t Tuner_CheckPreset(uint16_t u16Freq)
{
     uint8_t Temp = 0; 
     for (Temp = 0; Temp < LIST_BUFFER_MAX; Temp++)
     {
		if(TUNER_BAND_FM)
		{
			if(sTunerKeep.FmList[Temp] == u16Freq)
			{
				return (Temp + 1);
			}
		}
		else if(TUNER_BAND_AM)
		{
			if(sTunerKeep.AmList[Temp] == u16Freq)
			{
				return (Temp + 1);
			}
		}
     }  
    return (TUNER_PRESET_NULL);
}
#else
/**********************************************************
 * @function    Tuner_CheckPreset
 * @brief      Check the Specific Frequency whether is a Preset of
 *            Currently Band
 * @param      uint16_t u16Freq                    
 * @retval     None
 **********************************************************/
uint8_t Tuner_CheckPreset(uint16_t u16Freq)
{
    uint8_t Temp = 0;
    
     for (Temp = 0; Temp < TUNER_PRESET_MAX; Temp++)
     {
         if(sTunerDat.sInfo.Preset[TUNER_CURRENT_BAND][Temp] == u16Freq)
        {
            return (Temp + 1);
        }
     }
    
    return (TUNER_PRESET_NULL);
}
#endif

