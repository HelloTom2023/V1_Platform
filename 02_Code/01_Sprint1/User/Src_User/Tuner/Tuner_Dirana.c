/**********************************************************
 * @file        Tuner_Dirana.c
 * @purpose    Tuner Module Dirana Control Function, Tuner Driver Part
 * @version    0.01
 * @date        24.Jan. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          24.Jan.2013        v0.01        created
 *  
  **********************************************************/
#define TUNER_DIRANA_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= public variable ==================== */

#ifdef D_TUNER_MODULE_DIRANA
/* ========================= private variable =================== */



/* ========================= Code Part =================== */


/**********************************************************
 * @function    Tuner_Dirana_Reset
 * @brief      Reset Dirana Module
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Dirana_Reset(void)    // DiRaNa 3 already done  Reset
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Tuner_Dirana_InitBoot
 * @brief      Initialize Boot Registers of Dirana3
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Dirana_InitBoot(void)    //Maybe Should Add Radio Init All here Again
{
    uint8_t Result = SUBLAYER_DOING;
    
    if(sDirana.InitDone)    
    {
        sTuner.DiranaMask = TUNER_MASK_PRIMARY;    // Default:Primary Radio of D3 as the Primary Tuner 
        Result = SUBLAYER_DONE;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Tuner_Dirana_InitRds
 * @brief      Initialize Rds Related Registers of Dirana 3
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Dirana_InitRds(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Dirana_SetBand
 * @brief      Set Currently Band to Dirana
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Dirana_SetBand(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    if(DelayNotExpired(sTuner.DriverLayerDelay))
        return (Result);  
    
    switch(sTuner.DriverLayerStep)
    {
        case DIRANA_BAND_INIT_PARA:
            Tuner_BandInit();

            sTuner.bReInitBand = 0;
            //Reconfig Rds Infoes and Settings
            //maybe it will be better doing this by Display itself
            if(TUNER_BAND_FM)
            {
                //Retrieve Rds Setting
                if(sTuner.bBakRdsSetting)
                {
                    sTunerDat.sSetting.Total |= (sTunerKeep.sBakSetting.Total & 0xFC);
                }
                sTuner.bBakRdsSetting = 0;
            }
            else if(!(TUNER_BAND_FM))
            {
                //Bakup Related Rds Setting
                if(0 == sTuner.bBakRdsSetting)
                {
                    sTunerKeep.sBakSetting.Total = sTunerDat.sSetting.Total;
                    sTuner.bBakRdsSetting = 1;
                    //Clear Rds Setting
                    sTunerDat.sSetting.sMap.bAfSetting = 0;
                    sTunerDat.sSetting.sMap.bRegSetting = 0;
                    sTunerDat.sSetting.sMap.bTaSetting = 0;
                    sTunerDat.sSetting.sMap.bPtySetting = 0;
                    sTunerDat.sSetting.sMap.bEonSetting = 0;
                }
                //Clear Rds Display
            }
            sTuner.PtyChk = 0xFF;
            Rds_ResetAll(); //Reset Rds Related...
            sTuner.DriverLayerStep = DIRANA_BAND_SET_BAND;
            break;
            
        // Initialize Band Related Registers
        case DIRANA_BAND_SET_BAND:    
            SubResult = Dirana_SendCmd(DIRANA_IIC_RADIO_SET_FREQ,TUNER_CURRENT_BAND,TUNER_CURRENT_FREQ,DIRANA_MODE_PRESET);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.DriverLayerStep = DIRANA_BAND_REGISTER;
                sTuner.DriverLayerDelay = TunerDelay(T10MS);
            }
            break;

        //
       case DIRANA_BAND_REGISTER:
            SubResult = Dirana_InitialAll();
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.DriverLayerStep = DIRANA_BAND_SET_EX1;
                sTuner.DriverLayerDelay = TunerDelay(T20MS);
            }    
            break;
            
        // 
        case DIRANA_BAND_SET_EX1:
            SubResult = Dirana_SetAntenna();
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.DriverLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            } 
            break;
        
        default:
            sTuner.DriverLayerStep = OPERATION_0;
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sTuner.DriverLayerStep = OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_SetFreq
 * @brief      Set Currently Frequency to Dirana
 * @param      uint16_t Freq                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Dirana_SetFreq(uint16_t Freq)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sTuner.DriverLayerStep)
    {
        // Set  Frequency
        case DIRANA_FREQ_SET:
            SubResult = Dirana_SendCmd(DIRANA_IIC_RADIO_SET_FREQ,TUNER_CURRENT_BAND,Freq,DIRANA_MODE_PRESET);
            if(SUBLAYER_DONE == SubResult)
            {
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
 * @function    Dirana_ConfigMode
 * @brief      Config Tuner Mode: Search or Preset
 * @param      uint8_t Mode                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Dirana_ConfigMode(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t TmpMode;

    // Transfer Mode 
    if(TUNER_MODE_SEEK == Mode)
    {
        TmpMode =  DIRANA_MODE_SEARCH;
    }
    else //if(Mode == TUNER_MODE_PRESET)
    {
        TmpMode =  DIRANA_MODE_PRESET;
    }
    
    Result = Dirana_SendCmd(DIRANA_IIC_RADIO_CHG_MODE,TUNER_CURRENT_BAND,TUNER_CURRENT_FREQ,TmpMode);

    return (Result);
}
/**********************************************************
 * @function    Dirana_CheckStation
 * @brief      Check Currently Station's state
 * @param      uint8_t ChkMode                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Dirana_CheckStation(uint8_t ChkMode)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_RADIO_GET_QUAL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Lev = 0;

    Result = Dirana_ReadCommon(PrivateID,REG_STATUS,5);
    if(SUBLAYER_DONE == Result)
    {
        if(TUNER_BAND_AM)    // AM BAND
        {
            //Set Level TH, check LOC Flag
            Lev = DIRANA_AM_LEV_TH;
            if(TUNER_LOC == LocDxSetting)
            {
                Lev += DIRANA_AM_LOC_DELTA;
            }
            
            if((sDirana.ReadBuff[DIRANA_LEVEL] >= Lev)
                && (sDirana.ReadBuff[DIRANA_USN] >= 0x80)
                && (sDirana.ReadBuff[DIRANA_USN] <= 0xF0)
                && ((sDirana.ReadBuff[DIRANA_FOF] & 0x7F) < DIRANA_AM_FOF_TH))
            {
                sTuner.bGoodStation = 1;
            }
        }
        else     // FM World
        {
            //Set Level TH, check LOC Flag
            Lev = DIRANA_FM_LEV_TH;
            if(TUNER_LOC == LocDxSetting)
            {
                Lev += DIRANA_FM_LOC_DELTA;
            }
        
            if((sDirana.ReadBuff[DIRANA_LEVEL] >= Lev)       
                && (sDirana.ReadBuff[DIRANA_USN] < DIRANA_FM_USN_TH)     
                && (sDirana.ReadBuff[DIRANA_WAM] < DIRANA_FM_WAM_TH)   
                && ((sDirana.ReadBuff[DIRANA_FOF] & 0x7F) < DIRANA_FM_FOF_TH))    
            {
                sTuner.bGoodStation = 1;
            }
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_SeekNext
 * @brief      Dirana Seek Next Station
 * @param      uint8_t Mode                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Dirana_SeekNext(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sTuner.DriverLayerStep)
    {
        // Change to Next Frequency
        case OPERATION_0:
            Tuner_StepChangeFreq(Mode);
            //filter 50khz point
            sTuner.DriverLayerStep = OPERATION_1;
            break;

        // Set to Currently Frequency
        case OPERATION_1:
            SubResult = Dirana_SendCmd(DIRANA_IIC_RADIO_SET_FREQ,TUNER_CURRENT_BAND,TUNER_CURRENT_FREQ,DIRANA_MODE_SEARCH);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.DriverLayerStep = OPERATION_0;
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
 * @function    Dirana_InitialAll
 * @brief      Dirana Initialize All registers for Primay Tuner
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Dirana_InitialAll(void)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_InitRadio(P_RADIO);

    return (Result);
}
/**********************************************************
 * @function    Dirana_SetAntenna
 * @brief      
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Dirana_SetAntenna(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_RADIO_SET_ANT;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[2];

    Buffer[0] = 0x04;

    if(TUNER_BAND_AM)  
    {
    #if 0
        if((sAudioDat.sBasicBK.DefaultMediaVolume > 20) &&
        (sAudioDat.sBasicBK.DefaultMediaVolume < 28))
        {
            Buffer[1] = (0x04 | 0x80 | ((sAudioDat.sBasicBK.DefaultMediaVolume - 20) << 4));
        }
    #else
        Buffer[1] = 0x04;   //ANT Passive , ATT 0db, SEL 1
    #endif
    }
    else
    {
        Buffer[1] = 0x00;
    }
    
    Result = Dirana_WriteCommon(PrivateID, Buffer, 2);

    return (Result);
}
/**********************************************************
 * @function    Dirana_SendCmd
 * @brief      Send PLL command to Dirana
 *            Used for: Set Band, Set Freq, and so on..
 * @param      DIRANA_DRIVER_TYPE_ENUM PID
 *            uint8_t Band
 *                 uint16_t Freq
 *                 uint8_t Mode
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SendCmd(DIRANA_DRIVER_TYPE_ENUM PID, uint8_t Band, uint16_t Freq, uint8_t Mode)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[4];

    if((Band >= TUNER_AM_START) && (Band <= TUNER_AM_END))
    {
        Buffer[1] = 2;  // AM
    }
    else
    {
        Buffer[1] = 0;  // FM WORLD    
    }
    // Reserved for LW SW    
    
    Buffer[0] = (0x00 | sTuner.DiranaMask);
    Buffer[1] += Mode;
    Buffer[2] =  ((Freq>>8)&0x00FF);
    Buffer[3] = (Freq&0xFF);
            
    Result = Dirana_WriteCommon(PrivateID, Buffer, 4);

    //Ignore ReadBack

    return (Result);
}
/**********************************************************
 * @function    Dirana_SwitchST
 * @brief      Switch ST Setting
 * @param      uint8_t Mode
 * @retval      Result of Executing
 **********************************************************/
uint8_t Dirana_SwitchST(uint8_t Mode)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SWITCH_ST;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[2];

    Buffer[0] = 0x06;    //SIGNAL

    if(STEREO_MONO == Mode)
    {
        Buffer[1] = (DIRANA_SIGNAL | 0x80);
    }
    else
    {
        Buffer[1] = (DIRANA_SIGNAL & 0x7F);
    }
    
    Result = Dirana_WriteCommon(PrivateID, Buffer, 2);

    return (Result);
}
/**********************************************************
 * @function    Dirana_GetQualVal
 * @brief      Get Quality Value
 * @param      None                    
 * @retval     Quality Value of Currently Station 
 **********************************************************/
uint8_t Dirana_GetQualVal(void)
{
    return (sDirana.ReadBuff[DIRANA_LEVEL]);
}
/**********************************************************
 * @function    Dirana_GetSignalStr
 * @brief      Get Signal Strength
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GetSignalStr(void)
{
    uint8_t Result = 0;
    uint8_t QualVal = sDirana.ReadBuff[DIRANA_LEVEL];
    uint8_t ValWAM = sDirana.ReadBuff[DIRANA_WAM];
    uint8_t ValUSN = sDirana.ReadBuff[DIRANA_USN];

    if(TUNER_BAND_FM)
    {
        if(QualVal < SIGNALSTR_FM_LEV0)
        {
            Result = 0;
        }
        else if(QualVal < SIGNALSTR_FM_LEV1)
        {
            Result = 1;
            if((ValWAM > NOISE_WAM_LEV3) || (ValUSN > NOISE_USN_LEV3))
            {
                Result = 0;
            }
        }
        else if(QualVal < SIGNALSTR_FM_LEV2)
        {
            Result = 2;
            if((ValWAM > NOISE_WAM_LEV3) || (ValUSN > NOISE_USN_LEV3))
            {
                Result = 0;
            }
            else if((ValWAM > NOISE_WAM_LEV2) || (ValUSN > NOISE_USN_LEV2))
            {
                Result = 1;
            }
        }
        else
        {
            Result = 3;
            if((ValWAM > NOISE_WAM_LEV3) || (ValUSN > NOISE_USN_LEV3))
            {
                Result = 0;
            }
            else if((ValWAM > NOISE_WAM_LEV2) || (ValUSN > NOISE_USN_LEV2))
            {
                Result = 1;
            }
            else if((ValWAM > NOISE_WAM_LEV1) || (ValUSN > NOISE_USN_LEV1))
            {
                Result = 2;
            }
        }
    }
    else
    {
        if(QualVal < SIGNALSTR_AM_LEV0)
        {
            Result = 0;
        }
        else if(QualVal < SIGNALSTR_AM_LEV1)
        {
            Result = 1;
        }
        else if(QualVal < SIGNALSTR_AM_LEV2)
        {
            Result = 2;
        }
        else
        {
            Result = 3;
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_GetStereoFlag
 * @brief      Get Stereo Flag
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GetStereoFlag(void)
{
    return ((sDirana.ReadBuff[DIRANA_STATUS] >> 3) & 0x01);    
}
/**********************************************************
 * @function    Dirana_GetInfoes
 * @brief      Get Quality Value
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GetInfoes(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_RADIO_GET_INFO;
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_ReadCommon(PrivateID,REG_STATUS,5);

    return (Result);
}

//1 Rds Relative Functions: Start


/**********************************************************
 * @function    Dirana_AF_Update
 * @brief      AF Update to alternative Frequency
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_AF_Update(uint16_t FreqAf)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_SendCmd(DIRANA_IIC_AF_UPDATE,TUNER_CURRENT_BAND,FreqAf,DIRANA_MODE_UPDATE);

    return (Result);
}
/**********************************************************
 * @function    Dirana_AF_Jump
 * @brief      Jump to alternative Frequency
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_AF_Jump(uint8_t FreqAf)
{
    uint8_t Result = SUBLAYER_DOING;
    uint16_t Freq;
    
    Freq = (uint16_t)(FreqAf * 10) + 8750; 

    Result = Dirana_SendCmd(DIRANA_IIC_AF_JUMP,TUNER_CURRENT_BAND,Freq,DIRANA_MODE_JUMP);

    return (Result);    
}
/**********************************************************
 * @function    Dirana_SetBw
 * @brief      Set Bandwidth
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetBw(uint8_t Mode,uint8_t Bw)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[3];
    
    Buffer[0] = 0x03; // BW CTL
    Buffer[1] = Bw;

    Result = Dirana_WriteCommon(DIRANA_IIC_SET_BW,Buffer,2);

    return (Result);
}
/**********************************************************
 * @function    Dirana_GetAfQuality
 * @brief      Get Alternative Frequency's Quality 
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GetAfQuality(uint16_t Freq, uint8_t Num)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.GetAfQualDelay))
    {
        return (SUBLAYER_DOING);
    }
    
    switch(sTuner.GetAfQualCtl)
    {
        //Initialize Related Parameters
        case DIRANA_AF_QUAL_INIT:
            sTuner.TempSmeter = 0;
            sTuner.TempAdjChannel = 0;
            sTuner.TempMultipath = 0;
            sTuner.TempFof = 0;
            sTuner.GetAfQualNum = 0;
            sTuner.GetAfQualDelay = 0;
            sTuner.GetAfQualCtl = DIRANA_AF_QUAL_UPDATE;
            break;

        //AF Update: Update Alternative Frequency
        case DIRANA_AF_QUAL_UPDATE:
            SubResult = Dirana_AF_Update(Freq);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.GetAfQualCtl = DIRANA_AF_QUAL_GET;
                sTuner.GetAfQualDelay = TunerDelay(T4MS); //Approx. 2ms
            }
            break;

        //Get Qual: Read Back AF's Quality
        case DIRANA_AF_QUAL_GET:
            SubResult = Dirana_ReadCommon(DIRANA_IIC_GET_AF_QUAL,REG_STATUS,5);
            if(SUBLAYER_DONE == SubResult)
            {    //AFs's Quality Available: QRS = 111
                if(0xE0 == (sDirana.ReadBuff[DIRANA_STATUS] & 0xE0))
                {
                    sTuner.TempSmeter += sDirana.ReadBuff[DIRANA_LEVEL];
                    sTuner.TempAdjChannel += sDirana.ReadBuff[DIRANA_USN];
                    sTuner.TempMultipath += sDirana.ReadBuff[DIRANA_WAM];
                    sTuner.TempFof += (sDirana.ReadBuff[DIRANA_FOF] & 0x7F);

                    sTuner.GetAfQualNum++;
                    if(sTuner.GetAfQualNum == Num)
                    {    //Get Quality Done!..
                        sTuner.FastAfSmeter = sTuner.TempSmeter / Num;
                        sTuner.FastAfAdjChannel = sTuner.TempAdjChannel / Num;
                        sTuner.FastAfMultipath = sTuner.TempMultipath / Num;
                        sTuner.FastAfFof = sTuner.TempFof / Num;
                        sTuner.GetAfQualCtl = DIRANA_AF_QUAL_INIT;
                        Result = SUBLAYER_DONE;
                    }
                    else
                    {    //Go on Get AF Quality
                        sTuner.GetAfQualCtl = DIRANA_AF_QUAL_UPDATE;
                    }
					//sTuner.GetAfQualDelay = TunerDelay(T200MS);
                }
                else // Avoid Locked!!! QRS 111 maybe destroyed outside ,, re-do!
                {
                    sTuner.GetAfQualCtl = DIRANA_AF_QUAL_INIT;
                    sTuner.GetAfQualDelay = TunerDelay(T10MS);
                }
            }
            break;

        default:
            sTuner.GetAfQualCtl = DIRANA_AF_QUAL_INIT;
            Result = SUBLAYER_STEP_ERROR;
            break;

    }

    //Error Occurs!!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sTuner.GetAfQualCtl = DIRANA_AF_QUAL_INIT;
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_GetCFQuality
 * @brief      Get Currently Frequency's Quality 
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GetCFQuality(uint8_t Num)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_GET_CF_QUAL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sTuner.GetCfQualCtl)
    {
        // Para Init
        case 0:
            sTuner.TempSmeter = 0;
            sTuner.TempFof = 0;
            sTuner.TempMultipath = 0;
            sTuner.TempAdjChannel = 0;
            sTuner.GetCfQualNum = 0;
            sTuner.GetCfQualCtl = 1;
            break;

         // Get CF
        case 1:
            SubResult = Dirana_ReadCommon(PrivateID,REG_STATUS,5);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.TempSmeter +=  sDirana.ReadBuff[DIRANA_LEVEL];
                sTuner.TempFof += (sDirana.ReadBuff[DIRANA_FOF]&0x7F);
                sTuner.TempMultipath += sDirana.ReadBuff[DIRANA_WAM];
                sTuner.TempAdjChannel += sDirana.ReadBuff[DIRANA_USN];
                sTuner.GetCfQualNum++;
                
                if(sTuner.GetCfQualNum == Num)  // CF Quality Got !
                {
                    sTuner.Smeter = sTuner.TempSmeter/Num;
                    sTuner.Fof = sTuner.TempFof/Num;
                    sTuner.Multipath = sTuner.TempMultipath/Num;
                    sTuner.AdjChannel = sTuner.TempAdjChannel/Num;
                    sTuner.GetCfQualCtl = 0;
                    Result = SUBLAYER_DONE;
                }
            }
            break;

        default:
            sTuner.GetCfQualCtl = 0;
            break;
    }

    //Error Occurs!!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sTuner.GetCfQualCtl = 0;
    }    

    return (Result);
}
/**********************************************************
 * @function    Dirana_AfSwitch
 * @brief      
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_AfSwitch(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    if(sRds.AFSwitchDelay)
    {
        return SUBLAYER_DOING;
    }

    switch(sRds.AFSwitchStep)
    {
        case 0: 
            sTuner.GetCfQualCtl = 0;    
            sRds.AFSwitchStep++;
            break;
            
        case 1:
            if(Mode == 1)
            {
                SubResult = Dirana_GetCFQuality(3);  //recheck quality~~
                if(SUBLAYER_DONE == SubResult)
                {
                    sRds.AFSmeter[sRds.AFCheckPoint] = sTuner.Smeter;
                    //if((sRds.AFSmeter[sRds.AFCheckPoint] > Smeter_DB20)
                    if((sRds.AFSmeter[sRds.AFCheckPoint] > Smeter_DB25)
                    #if 1  // More Strict to Disable Function
                        &&(sTuner.AdjChannel < Adjchannel_TH)
                    #endif
                        &&(sTuner.Fof < Detuning_TH))
                    {
                    #ifndef D_DISA_DUMMY_PI
                        sRds.AFDisable[sRds.AFCheckPoint] = sRds.AFCheckDisable1S;
                    #endif
                    }
                    sRds.AFSwitchStep++;
                }
            }
            else
            {
                if(sRds.F_PIMuteEnable)
                {
                    Rds_Mute(MUTE_ON);
                }
                sRds.AFSwitchDelay = 5;    // 10MS
                sRds.AFSwitchStep++;
            }
            break;
            
        case 2:
            if(Mode == 1)
            {
                SubResult = Dirana_AF_Jump(sRds.AF[0]);
            }
            else
            {
                SubResult = Dirana_AF_Jump(sRds.AF[sRds.AFCheckPoint]);
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sRds.AFSwitchDelay = 5;    // 9MS
            #ifdef D_RDS_REGULAR_READ
                sRds.RegularReadDelay = TunerDelay(T50MS);; // delay for rds read
            #endif
                sRds.AFSwitchStep++;
            }
            break;

        case 3:
            if(Mode == 1)
            {
                SubResult = Dirana_SetBw(0,0); // Switch Back to Auto BW Control
                sRds.bDissChanged = 0;
            }
            else
            {
                SubResult = Dirana_SetBw(0,10);
                sRds.bDissChanged = 1;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sRds.AFSwitchDelay = 5;     // 10 ms  ,need to be splitted
                sRds.AFSwitchStep++;
            }
            break;

        case 4:    
            SubResult = Rds_AfChkInit();
            if(SUBLAYER_DONE == SubResult)
            {
                if(Mode == 1)
                {
                    Rds_Mute(MUTE_OFF);
                }
                else
                {
                    if(sRds.AFSmeter[sRds.AFCheckPoint] > Smeter_DB40)
                        sRds.AFCheckWaitTimer = 30; // 300 ms
                    else
                        sRds.AFCheckWaitTimer = 60;
                }
                Result = SUBLAYER_DONE;
            }
            break;
        
        default:
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_FetchBlockDat
 * @brief      Fetch Rds Block Datum
 * @param      None                
 * @retval     Result
 **********************************************************/
void Dirana_FetchBlockDat(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateId = DIRANA_IIC_RDS_FETCH_BLOCK;
    uint8_t Result = SUBLAYER_DOING;
    
    switch(sRds.FetchBlockCtl)
    {
        //Get Newly Block if Valid
        case OPERATION_0:
            //Check Valid Bit or Waiting for Periodly Read Flag
            if(sRds.RegularReadDelay
            #ifndef D_RDS_REGULAR_READ    
                || (0 == sRds.bDataAvailable)
            #endif//D_RDS_REGULAR_READ     
                )
            {
                break;
            }

            //Read Newly Block
            Result = Dirana_ReadCommon(PrivateId,REG_STATUS,17);
            if(SUBLAYER_DONE == Result)
            {
                sRds.bDataAvailable = 0; //Clear Int Flag
                if((0x05 != (sDirana.ReadBuff[DIRANA_STATUS] >> 5))   //QRS
                    || (0x00 == (sDirana.ReadBuff[DIRANA_STATUS] | 0x10)) //Rds Flag
                    || (sDirana.ReadBuff[DIRANA_LEVEL] < DIRANA_FM_LEV_TH) //Signal Str
                    || (sDirana.ReadBuff[DIRANA_USN] > DIRANA_FM_USN_TH))  //
                {
                    #ifdef D_RDS_REGULAR_READ    
                        sRds.RegularReadDelay = TunerDelay(T30MS);
                    #endif//D_RDS_REGULAR_READ
                        break;
                }

                if((sDirana.ReadBuff[DIRANA_RDS_STATUS] & 0x80) && (sDirana.ReadBuff[DIRANA_RDS_STATUS] & 0x02))    // RDAV: Rds available
                {
                    if(sDirana.ReadBuff[DIRANA_RDS_STATUS] & 0x20) //First PI
                    {
                        //Get First PI, Saved for AF Usage, Or Do AF PI Check Here!!
                        //Other Infoes will be desert, because of they will become available at the next data available!
                    #ifdef D_RDS_REGULAR_READ    
                        sRds.RegularReadDelay = TunerDelay(T30MS);
                    #endif//D_RDS_REGULAR_READ
                        break;
                    }
                    // Get Block Error Flag
                    sRds.BlockAQual = ((sDirana.ReadBuff[DIRANA_RDS_ERR] >> 6) & 0x03);
                    sRds.BlockBQual = ((sDirana.ReadBuff[DIRANA_RDS_ERR] >> 4) & 0x03);
                    sRds.BlockCQual = ((sDirana.ReadBuff[DIRANA_RDS_ERR] >> 2) & 0x03);
                    sRds.BlockDQual = (sDirana.ReadBuff[DIRANA_RDS_ERR] & 0x03);

                    // Get Block Data
                    sRds.BlockA = (uint16_t)(sDirana.ReadBuff[DIRANA_RDS_AH] << 8) + sDirana.ReadBuff[DIRANA_RDS_AL];
                    sRds.BlockB = (uint16_t)(sDirana.ReadBuff[DIRANA_RDS_BH] << 8) + sDirana.ReadBuff[DIRANA_RDS_BL];
                    sRds.BlockC = (uint16_t)(sDirana.ReadBuff[DIRANA_RDS_CH] << 8) + sDirana.ReadBuff[DIRANA_RDS_CL];
                    sRds.BlockD = (uint16_t)(sDirana.ReadBuff[DIRANA_RDS_DH] << 8) + sDirana.ReadBuff[DIRANA_RDS_DL];

                    // Error Check
                    if(sRds.BlockAQual <= RDS_ERR_LEVEL)
                    {
                        sRds.F_GetBlockA = 1;
			    sRds.bGotBlock = 1;
			}
			if(sRds.BlockBQual <= RDS_ERR_LEVEL)
			{
			    sRds.F_GetBlockB = 1;
			    sRds.bGotBlock = 1;
			}
			if(sRds.BlockCQual <= RDS_ERR_LEVEL)
			{
			    sRds.F_GetBlockC = 1;
			    sRds.bGotBlock = 1;
			}
			if(sRds.BlockDQual <= RDS_ERR_LEVEL)
			{
			    sRds.F_GetBlockD = 1;
			    sRds.bGotBlock = 1;
                    }
                    //Save Newly Valid Blocks and Set flag for datum analyse
                    Rds_PushToLast();
                    sRds.FetchBlockCtl = OPERATION_1;
                }
                else
                {    //No Rds Data Available, Reset and Re-Fetch blocks when datum ready()
                #ifdef D_RDS_REGULAR_READ    
                    sRds.RegularReadDelay = TunerDelay(T50MS);
                #endif//D_RDS_REGULAR_READ
                }
            }
            break;

        //Clear DA Flag
        case OPERATION_1:
            //Read for Clear
            Result = Dirana_ReadCommon(PrivateId,REG_RDS_A_H,1);
            if(SUBLAYER_DONE == Result)
            {
                sRds.FetchBlockCtl = OPERATION_0;
            #ifdef D_RDS_REGULAR_READ    
                sRds.RegularReadDelay = TunerDelay(T50MS);
            #endif//D_RDS_REGULAR_READ
            }
            break;

        default:
            sRds.FetchBlockCtl = OPERATION_0;
            break;
    }

    //Error Occurs!!
    if(Result > SUBLAYER_DONE)
    {
        sRds.FetchBlockCtl = OPERATION_0;
        sRds.RegularReadDelay = TunerDelay(T10MS);
    }    
}
/**********************************************************
 * @function    Dirana_ResetDecoder
 * @brief      Reset Rds Decoder
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_ResetDecoder(void)
{
#if 0
    DIRANA_DRIVER_TYPE_ENUM PrivateId = DIRANA_IIC_RDS_RESET_DECODER;
    uint8_t Result = SUBLAYER_DOING;    
    uint8_t IIcDataBuff[2];
    
    IIcDataBuff[0] = 0x09;
    IIcDataBuff[1] = (DIRANA_RDS|0x80);  

    Result = Dirana_WriteCommon(PrivateId,IIcDataBuff,2);

    return (Result);
#else
    // Not Need because of automatic restart of RDS after tuning...
    return (SUBLAYER_DONE);
#endif
}



#endif//D_TUNER_MODULE_DIRANA

