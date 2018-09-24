/**********************************************************
 * @file        Tuner_Nxp6638.c
 * @purpose    Tuner Module Nxp6638 Control Function, Tuner Driver Part
 * @version    0.01
 * @date        27. June. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          27.June.2012        v0.01        created
 *  
  **********************************************************/
#define TUNER_NXP6638_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= public variable ==================== */

#ifdef D_TUNER_MODULE_HERO
/* ========================= private variable =================== */



/* ========================= Code Part =================== */


/**********************************************************
 * @function    Tuner_Hero_Reset
 * @brief      Reset Hero Module
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_Reset(void)    // Hero already done  Reset
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Tuner_Hero_InitBoot
 * @brief      Initialize Boot Registers of Nxp6638
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_InitBoot(void)    //Maybe Should Add Radio Init All here Again
{
    uint8_t Result = SUBLAYER_DOING;
    
    if(sHero.InitDone)    
    {
        Result = SUBLAYER_DONE;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Tuner_Hero_InitRds
 * @brief      Initialize Rds Related Registers of Nxp6638
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t  Tuner_Hero_InitRds(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Tuner_Hero_SetBand
 * @brief      Set Currently Band to Nxp6638
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_SetBand(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sTuner.DriverLayerStep)
    {
        case NXP6638_BAND_INIT_PARA:
            Tuner_BandInit();
            if(TUNER_BAND_AM)
            {
                _SendFullMsgToAudio(MS_AUDIO_CMD, OP_AUD_TUNER_SCALER ,1,0,0,0);
            }
            else
            {
                _SendFullMsgToAudio(MS_AUDIO_CMD, OP_AUD_TUNER_SCALER ,0,0,0,0);
            }
            sTuner.PtyChk = 0xFF;
            Rds_ResetAll(); //Reset Rds Related...
            sTuner.DriverLayerStep = NXP6638_BAND_SET_BAND;
            break;
            
        // Initialize Band Related Registers
        case NXP6638_BAND_SET_BAND:    
            SubResult = Tuner_Hero_SendCmd(HERO_IIC_RADIO_SET_BAND,TUNER_CURRENT_BAND,TUNER_CURRENT_FREQ,HERO_MODE_PRESET);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.DriverLayerStep = NXP6638_BAND_REGISTER;
            }
            break;

        // Set Currently Band
		case NXP6638_BAND_REGISTER:
			if(Mult_Struct.TestTuner == CLOSE_TESTTUNER)
			{
				SubResult = Tuner_Hero_InitialAll();
			}
			else if(Mult_Struct.TestTuner == OPEN_TESTTUNER)
			{
				SubResult = Tuner_Hero_InitialAll_TestMode();
			}	
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
        sTuner.DriverLayerStep = OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Tuner_Hero_SetFreq
 * @brief      Set Currently Frequency to Nxp6638
 * @param      uint16_t Freq                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_SetFreq(uint16_t Freq)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sTuner.DriverLayerStep)
    {
        // Set  Frequency
        case NXP6638_FREQ_SET:
            SubResult = Tuner_Hero_SendCmd(HERO_IIC_RADIO_SET_FREQ,TUNER_CURRENT_BAND,Freq,HERO_MODE_PRESET);
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
        sTuner.DriverLayerStep = 0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Tuner_Hero_ConfigMode
 * @brief      Nxp6638 Config Tuner Mode
 * @param      uint8_t Mode                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_ConfigMode(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t TmpMode;

    // Transfer Mode 
    if(TUNER_MODE_SEEK == Mode)
    {
        TmpMode =  HERO_MODE_SEARCH;
    }
    else //if(Mode == TUNER_MODE_PRESET)
    {
        TmpMode =  HERO_MODE_PRESET;
    }
    
    Result = Tuner_Hero_SendCmd(HERO_IIC_RADIO_CHG_MODE,TUNER_CURRENT_BAND,TUNER_CURRENT_FREQ,TmpMode);

    return (Result);
}
/**********************************************************
 * @function    Tuner_Hero_CheckStation
 * @brief      Nxp6638 Config Tuner Mode
 * @param      uint8_t ChkMode                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_CheckStation(uint8_t ChkMode)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_RADIO_GET_QUAL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Lev = 0;

    Result = Hero_ReadCommon(PrivateID,REG_STATUS,5);
    if(SUBLAYER_DONE == Result)
    {
        if(TUNER_BAND_AM)    // AM BAND
        {
            //Set Level TH, check LOC Flag
            Lev = HERO_AM_LEV_TH;
            if(TUNER_LOC == LocDxSetting)
            {
                Lev += HERO_AM_LOC_DELTA;
            }
        
            if((sHero.ReadBuff[HERO_LEVEL] >= Lev)
                && (sHero.ReadBuff[HERO_USN] >= 0x80)
                && (sHero.ReadBuff[HERO_USN] <= 0xF0)
                && ((sHero.ReadBuff[HERO_FOF] & 0x7F) < HERO_AM_FOF_TH))
            {
                sTuner.bGoodStation = 1;
            }
        }
        else     // FM World
        {
			/*
        	if(Mult_Struct.TestTuner == OPEN_TESTTUNER)
			{
			
				Lev = HERO_FM_LEV_TH;
	            if(TUNER_LOC == LocDxSetting)
	            {
	                Lev += HERO_FM_LOC_DELTA;
	            }     
	            
	            if((sHero.ReadBuff[HERO_LEVEL] >= Lev)       
	                && (sHero.ReadBuff[HERO_USN] < HERO_FM_USN_TH)     
	                && (sHero.ReadBuff[HERO_WAM] < HERO_FM_WAM_TH)   
	                && ((sHero.ReadBuff[HERO_FOF] & 0x7F) < HERO_FM_FOF_TH))    
	            {
	                sTuner.bGoodStation = 1;
	            }
			}
			else*/
			{
				/*
	            //Set Level TH, check LOC Flag
	            Lev = HERO_FM_LEV_TH;
	            if(TUNER_LOC == LocDxSetting)
	            {
	                Lev += HERO_FM_LOC_DELTA;
	            }     
	            
	            if((sHero.ReadBuff[HERO_LEVEL] >= Lev)       
	                && (sHero.ReadBuff[HERO_USN] < HERO_FM_USN_TH)     
	                && (sHero.ReadBuff[HERO_WAM] < HERO_FM_WAM_TH)   
	                && ((sHero.ReadBuff[HERO_FOF] & 0x7F) < HERO_FM_FOF_TH))    
	            {
	                sTuner.bGoodStation = 1;
	            }
				*/
				
				Lev = 0x3E;
	            
	            if((sHero.ReadBuff[HERO_LEVEL] >= Lev)       
	                && (sHero.ReadBuff[HERO_USN] < 0x48)     
	                && (sHero.ReadBuff[HERO_WAM] < 0x40)   
	                && ((sHero.ReadBuff[HERO_FOF] & 0x7F) < HERO_FM_FOF_TH))    
	            {
	                sTuner.bGoodStation = 1;
	            }
			}
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_Hero_SeekNext
 * @brief      Nxp6638 Seek Next Station
 * @param      uint8_t Mode                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_SeekNext(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sTuner.DriverLayerStep)
    {
        // Change to Next Frequency
        case OPERATION_0:
            Tuner_StepChangeFreq(Mode);
            sTuner.DriverLayerStep = OPERATION_1;
            break;

        // Set to Currently Frequency
        case OPERATION_1:
            SubResult = Tuner_Hero_SendCmd(HERO_IIC_RADIO_SET_FREQ,TUNER_CURRENT_BAND,TUNER_CURRENT_FREQ,HERO_MODE_SEARCH);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.DriverLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;
    
        default:
            Result = SUBLAYER_STEP_ERROR;
            sTuner.DriverLayerStep = OPERATION_0;
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
 * @function    Tuner_Hero_InitialAll
 * @brief      Nxp6638 Initialize All registers
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_InitialAll(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_RADIO_INIT_ALL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t IIcDataBuff[29];
    
    if(TUNER_BAND_AM)
    {
	    IIcDataBuff[0] = 0x03;
	    IIcDataBuff[1] = NXP663X_AM_TUNER;
	    IIcDataBuff[2] = NXP663X_AM_OPT; 
	    IIcDataBuff[3] = NXP663X_AM_RADIO;
	    IIcDataBuff[4] = NXP663X_AM_SIGNAL;

	    IIcDataBuff[5] = NXP663X_AM_BWCTRL;
	    IIcDataBuff[6] = NXP663X_AM_SPECIAL;
	    IIcDataBuff[7] = NXP663X_AM_RDS;
	    IIcDataBuff[8] = 0;
	    IIcDataBuff[9] = 0;
	    IIcDataBuff[10] = NXP663X_AM_LEV_OFFSET;
	    //Softmute 
	    IIcDataBuff[11] = NXP663X_AM_SM_TIME;
	    IIcDataBuff[12] = NXP663X_AM_SM_DET;
	    IIcDataBuff[13] = NXP663X_AM_SM_LEV; 
	    IIcDataBuff[14] = NXP663X_AM_SM_NM;
	    IIcDataBuff[15] = NXP663X_AM_SM_LIM; 
	    //high cut
	    IIcDataBuff[16] = NXP663X_AM_HC_TIME;
	    IIcDataBuff[17] = NXP663X_AM_HC_DET;
	    IIcDataBuff[18] = NXP663X_AM_HC_LEV;
	    IIcDataBuff[19] = NXP663X_AM_HC_NM;
	    IIcDataBuff[20] = NXP663X_AM_HC_LIM;
	    IIcDataBuff[21] = NXP663X_AM_HC_LOC;
	    //stereo
	    IIcDataBuff[22] = NXP663X_AM_ST_TIME;
	    IIcDataBuff[23] = NXP663X_AM_ST_DET;
	    IIcDataBuff[24] = NXP663X_AM_ST_LEV;
	    IIcDataBuff[25] = NXP663X_AM_ST_NM;
	    IIcDataBuff[26] = NXP663X_AM_ST_LIM;
	    IIcDataBuff[27] = NXP663X_AM_STHB_DET;
	    IIcDataBuff[28] = NXP663X_AM_STHB_LNM;
    }
    else
    {
	    IIcDataBuff[0] = 0x03;
	    IIcDataBuff[1] = NXP663X_FM_TUNER;
	    IIcDataBuff[2] = NXP663X_FM_OPT; 
	    IIcDataBuff[3] = NXP663X_FM_RADIO;
	    IIcDataBuff[4] = NXP663X_FM_SIGNAL;

	    IIcDataBuff[5] = NXP663X_FM_BWCTRL;
	    IIcDataBuff[6] = NXP663X_FM_SPECIAL;
	    IIcDataBuff[7] = NXP663X_FM_RDS;
	    IIcDataBuff[8] = 0;
	    IIcDataBuff[9] = 0;
	    IIcDataBuff[10] = NXP663X_FM_LEV_OFFSET;
	    //Softmute 
	    IIcDataBuff[11] = NXP663X_FM_SM_TIME;
	    IIcDataBuff[12] = NXP663X_FM_SM_DET;
	    IIcDataBuff[13] = NXP663X_FM_SM_LEV; 
	    IIcDataBuff[14] = NXP663X_FM_SM_NM;
	    IIcDataBuff[15] = NXP663X_FM_SM_LIM; 
	    //high cut
	    IIcDataBuff[16] = NXP663X_FM_HC_TIME;
	    IIcDataBuff[17] = NXP663X_FM_HC_DET;
	    IIcDataBuff[18] = NXP663X_FM_HC_LEV;
	    IIcDataBuff[19] = NXP663X_FM_HC_NM;
	    IIcDataBuff[20] = NXP663X_FM_HC_LIM;
	    IIcDataBuff[21] = NXP663X_FM_HC_LOC;
	    //stereo
	    IIcDataBuff[22] = NXP663X_FM_ST_TIME;
	    IIcDataBuff[23] = NXP663X_FM_ST_DET;
	    IIcDataBuff[24] = NXP663X_FM_ST_LEV;
	    IIcDataBuff[25] = NXP663X_FM_ST_NM;
	    IIcDataBuff[26] = NXP663X_FM_ST_LIM;
	    IIcDataBuff[27] = NXP663X_FM_STHB_DET;
	    IIcDataBuff[28] = NXP663X_FM_STHB_LNM;
    }

    Result = Hero_WriteCommon(PrivateID, IIcDataBuff, 29);

    return (Result);
}


uint8_t Tuner_Hero_InitialAll_TestMode(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_RADIO_INIT_ALL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t IIcDataBuff[29];
    

    if(TUNER_BAND_AM)
    {
	    IIcDataBuff[0] = 0x03;
	    IIcDataBuff[1] = 0x0A;
	    IIcDataBuff[2] = 0x00; 
	    IIcDataBuff[3] = 0xE8;
	    IIcDataBuff[4] = 0x06;

	    IIcDataBuff[5] = 0x05;
	    IIcDataBuff[6] = 0x00;
	    IIcDataBuff[7] = 0x41;
	    IIcDataBuff[8] = 0;
	    IIcDataBuff[9] = 0;
	    IIcDataBuff[10] = 38;
	    //Softmute 
	    IIcDataBuff[11] = 0x25;
	    IIcDataBuff[12] = 0x93;
	    IIcDataBuff[13] = 0x52; 
	    IIcDataBuff[14] = 0x35;
	    IIcDataBuff[15] = 0x04; 
	    //high cut
	    IIcDataBuff[16] = 0x12;
	    IIcDataBuff[17] = 0x3F;
	    IIcDataBuff[18] = 0x5B;
	    IIcDataBuff[19] = 0x55;
	    IIcDataBuff[20] = 0x01;
	    IIcDataBuff[21] = 0x05;
	    //stereo
	    IIcDataBuff[22] = 0x75;
	    IIcDataBuff[23] = 0x3F;
	    IIcDataBuff[24] = 0x4A;
	    IIcDataBuff[25] = 0x33;
	    IIcDataBuff[26] = 0x00;
	    IIcDataBuff[27] = 0x3F;
	    IIcDataBuff[28] = 0x13;
    }
    else
    {
	    IIcDataBuff[0] = 0x03;
	    IIcDataBuff[1] = 0x00;
	    IIcDataBuff[2] = 0x00; 
	    IIcDataBuff[3] = 0xEE;
	    IIcDataBuff[4] = 0x01;

	    IIcDataBuff[5] = 0x0B;
	    IIcDataBuff[6] = 0x00;
	    IIcDataBuff[7] = 0x41;
	    IIcDataBuff[8] = 0;
	    IIcDataBuff[9] = 0;
	    IIcDataBuff[10] = 45;
	    //Softmute 
	    IIcDataBuff[11] = 0x65;
	    IIcDataBuff[12] = 0x15;
	    IIcDataBuff[13] = 0x42; 
	    IIcDataBuff[14] = 0x77;
	    IIcDataBuff[15] = 0x09; 
	    //high cut
	    IIcDataBuff[16] = 0x09;
	    IIcDataBuff[17] = 0xBF;
	    IIcDataBuff[18] = 0x75;
	    IIcDataBuff[19] = 0x77;
	    IIcDataBuff[20] = 0x90;
	    IIcDataBuff[21] = 0x00;
	    //stereo
	    IIcDataBuff[22] = 0x75;
	    IIcDataBuff[23] = 0x3F;
	    IIcDataBuff[24] = 0x4A;
	    IIcDataBuff[25] = 0x33;
	    IIcDataBuff[26] = 0x00;
	    IIcDataBuff[27] = 0x3F;
	    IIcDataBuff[28] = 0x13;
    }		

    Result = Hero_WriteCommon(PrivateID, IIcDataBuff, 29);

    return (Result);
}
/**********************************************************
 * @function    Tuner_Hero_SendCmd
 * @brief      Send PLL command to Nxp6638
 * @param      uint8_t Band
 *                 uint16_t Freq
 *                 uint8_t Mode
 * @retval      Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_SendCmd(HERO_DRIVER_TYPE_ENUM PID,uint8_t Band, uint16_t Freq, uint8_t Mode)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = PID;
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
    
    Buffer[0] = 0x00;
    Buffer[1] += Mode;
    Buffer[2] =  ((Freq>>8)&0x00FF);
    Buffer[3] = (Freq&0xFF);
            
    Result = Hero_WriteCommon(PrivateID, Buffer, 4);

    //Ignore ReadBack

    return (Result);
}
/**********************************************************
 * @function    Tuner_Hero_SwitchST
 * @brief     
 * @param      uint8_t Mode
 * @retval      Result of Executing
 **********************************************************/
uint8_t Tuner_Hero_SwitchST(uint8_t Mode)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SWITCH_ST;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[2];

    Buffer[0] = 0x06;    //SIGNAL

    if(STEREO_MONO == Mode)
    {
        Buffer[1] = (NXP663X_SIGNAL | 0x80);
    }
    else
    {
        Buffer[1] = (NXP663X_SIGNAL & 0x7F);
    }
    
    Result = Hero_WriteCommon(PrivateID, Buffer, 2);

    return (Result);
}
/**********************************************************
 * @function    Tuner_Hero_GetQualVal
 * @brief      Get Quality Value
 * @param      None                    
 * @retval     Quality Value of Currently Station 
 **********************************************************/
uint8_t Tuner_Hero_GetQualVal(void)
{
    return (sHero.ReadBuff[HERO_LEVEL]);
}
/**********************************************************
 * @function    Tuner_Hero_GetSignalStr
 * @brief      Get Quality Value
 * @param      None                    
 * @retval     Quality Value of Currently Station 
 **********************************************************/
uint8_t Tuner_Hero_GetSignalStr(void)
{
    uint8_t Result = 0;
    uint8_t QualVal = sHero.ReadBuff[HERO_LEVEL];
    uint8_t ValWAM = sHero.ReadBuff[HERO_WAM];
    uint8_t ValUSN = sHero.ReadBuff[HERO_USN];

    if(TUNER_BAND_FM)
    {
        if(QualVal < HERO_SIGSTR_FM_LEV0)
        {
            Result = 0;
        }
        else if(QualVal < HERO_SIGSTR_FM_LEV1)
        {
            Result = 1;
            if((ValWAM > HERO_WAM_LEV3) || (ValUSN > HERO_USN_LEV3))
            {
                Result = 0;
            }
        }
        else if(QualVal < HERO_SIGSTR_FM_LEV2)
        {
            Result = 2;
            if((ValWAM > HERO_WAM_LEV3) || (ValUSN > HERO_USN_LEV3))
            {
                Result = 0;
            }
            else if((ValWAM > HERO_WAM_LEV2) || (ValUSN > HERO_USN_LEV2))
            {
                Result = 1;
            }
        }
        else
        {
            Result = 3;
            if((ValWAM > HERO_WAM_LEV3) || (ValUSN > HERO_USN_LEV3))
            {
                Result = 0;
            }
            else if((ValWAM > HERO_WAM_LEV2) || (ValUSN > HERO_USN_LEV2))
            {
                Result = 1;
            }
            else if((ValWAM > HERO_WAM_LEV1) || (ValUSN > HERO_USN_LEV1))
            {
                Result = 2;
            }
        }
    }
    else
    {
        if(QualVal < HERO_SIGSTR_AM_LEV0)
        {
            Result = 0;
        }
        else if(QualVal < HERO_SIGSTR_AM_LEV1)
        {
            Result = 1;
        }
        else if(QualVal < HERO_SIGSTR_AM_LEV2)
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
 * @function    Tuner_Hero_GetStereoFlag
 * @brief      Get Quality Value
 * @param      None                    
 * @retval     Quality Value of Currently Station 
 **********************************************************/
uint8_t Tuner_Hero_GetStereoFlag(void)
{
    return ((sHero.ReadBuff[HERO_STATUS] >> 3) & 0x01);    
}
/**********************************************************
 * @function    Tuner_Hero_GetInfoes
 * @brief      Get Quality Value
 * @param      None                    
 * @retval     Quality Value of Currently Station 
 **********************************************************/
uint8_t Tuner_Hero_GetInfoes(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_RADIO_GET_INFO;
    uint8_t Result = SUBLAYER_DOING;

    Result = Hero_ReadCommon(PrivateID,REG_STATUS,5);

    return (Result);
}

//1 Rds Relative Functions: Start


/**********************************************************
 * @function    Hero_AF_Update
 * @brief      AF Update to alternative Frequency
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_AF_Update(uint16_t FreqAf)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Tuner_Hero_SendCmd(HERO_IIC_AF_UPDATE,TUNER_CURRENT_BAND,FreqAf,HERO_MODE_UPDATE);

    return (Result);
}
/**********************************************************
 * @function    Hero_AF_Jump
 * @brief      Jump to alternative Frequency
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_AF_Jump(uint8_t FreqAf)
{
    uint8_t Result = SUBLAYER_DOING;
    uint16_t Freq;
    
    Freq = (uint16_t)(FreqAf * 10) + 8750; 

    Result = Tuner_Hero_SendCmd(HERO_IIC_AF_JUMP,TUNER_CURRENT_BAND,Freq,HERO_MODE_JUMP);

    return (Result);    
}
/**********************************************************
 * @function    Hero_SetBw
 * @brief      Set Bandwidth
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetBw(uint8_t Mode,uint8_t Bw)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[3];
    
    Buffer[0] = 0x03; // BW CTL
    Buffer[1] = Bw;

    Result = Hero_WriteCommon(HERO_IIC_SET_BW,Buffer,2);

    return (Result);
}
/**********************************************************
 * @function    Hero_GetAfQuality
 * @brief      Get Alternative Frequency's Quality 
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_GetAfQuality(uint16_t Freq, uint8_t Num)
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
        case HERO_AF_QUAL_INIT:
            sTuner.TempSmeter = 0;
            sTuner.TempAdjChannel = 0;
            sTuner.TempMultipath = 0;
            sTuner.TempFof = 0;
            sTuner.GetAfQualNum = 0;
            sTuner.GetAfQualDelay = 0;
            sTuner.GetAfQualCtl = HERO_AF_QUAL_UPDATE;
            break;

        //AF Update: Update Alternative Frequency
        case HERO_AF_QUAL_UPDATE:
            SubResult = Hero_AF_Update(Freq);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.GetAfQualCtl = HERO_AF_QUAL_GET;
                sTuner.GetAfQualDelay = TunerDelay(T4MS); //Approx. 2ms
            }
            break;

        //Get Qual: Read Back AF's Quality
        case HERO_AF_QUAL_GET:
            SubResult = Hero_ReadCommon(HERO_IIC_GET_AF_QUAL,REG_STATUS,5);
            if(SUBLAYER_DONE == SubResult)
            {    //AFs's Quality Available: QRS = 111
                if(0xE0 == (sHero.ReadBuff[HERO_STATUS] & 0xE0))
                {
                    sTuner.TempSmeter += sHero.ReadBuff[HERO_LEVEL];
                    sTuner.TempAdjChannel += sHero.ReadBuff[HERO_USN];
                    sTuner.TempMultipath += sHero.ReadBuff[HERO_WAM];
                    sTuner.TempFof += (sHero.ReadBuff[HERO_FOF] & 0x7F);

                    sTuner.GetAfQualNum++;
                    if(sTuner.GetAfQualNum == Num)
                    {    //Get Quality Done!..
                        sTuner.FastAfSmeter = sTuner.TempSmeter / Num;
                        sTuner.FastAfAdjChannel = sTuner.TempAdjChannel / Num;
                        sTuner.FastAfMultipath = sTuner.TempMultipath / Num;
                        sTuner.FastAfFof = sTuner.TempFof / Num;
                        sTuner.GetAfQualCtl = HERO_AF_QUAL_INIT;
                        Result = SUBLAYER_DONE;
                    }
                    else
                    {    //Go on Get AF Quality
                        sTuner.GetAfQualCtl = HERO_AF_QUAL_UPDATE;
                    }
					//sTuner.GetAfQualDelay = TunerDelay(T200MS);
                }
                else // Avoid Locked!!! QRS 111 maybe destroyed outside ,, re-do!
                {
                    sTuner.GetAfQualCtl = HERO_AF_QUAL_INIT;
                    sTuner.GetAfQualDelay = TunerDelay(T10MS);
                }
            }
            break;

        default:
            sTuner.GetAfQualCtl = HERO_AF_QUAL_INIT;
            Result = SUBLAYER_STEP_ERROR;
            break;

    }

    //Error Occurs!!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sTuner.GetAfQualCtl = HERO_AF_QUAL_INIT;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_GetCFQuality
 * @brief      Get Currently Frequency's Quality 
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_GetCFQuality(uint8_t Num)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_GET_CF_QUAL;
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
            SubResult = Hero_ReadCommon(PrivateID,REG_STATUS,5);
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.TempSmeter +=  sHero.ReadBuff[HERO_LEVEL];
                sTuner.TempFof += (sHero.ReadBuff[HERO_FOF]&0x7F);
                sTuner.TempMultipath += sHero.ReadBuff[HERO_WAM];
                sTuner.TempAdjChannel += sHero.ReadBuff[HERO_USN];
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
 * @function    Hero_AfSwitch
 * @brief      
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_AfSwitch(uint8_t Mode)
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
                SubResult = Hero_GetCFQuality(3);  //recheck quality~~
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
                SubResult = Hero_AF_Jump(sRds.AF[0]);
            }
            else
            {
                SubResult = Hero_AF_Jump(sRds.AF[sRds.AFCheckPoint]);
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
                SubResult = Hero_SetBw(0,0); // Switch Back to Auto BW Control
                sRds.bDissChanged = 0;
            }
            else
            {
                SubResult = Hero_SetBw(0,10);
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
 * @function    Hero_FetchBlockDat
 * @brief      Fetch Rds Block Datum
 * @param      None                
 * @retval     Result
 **********************************************************/
void Hero_FetchBlockDat(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateId = HERO_IIC_RDS_FETCH_BLOCK;
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
                return;
            }
            
            //Read Newly Block
            Result = Hero_ReadCommon(PrivateId,REG_RDS_STATUS,10);
            if(SUBLAYER_DONE == Result)
            {
                sRds.bDataAvailable = 0; //Clear Int Flag

                if(sHero.ReadBuff[HERO_RDS_STATUS] & 0x80)    // RDAV: Rds available
                {
                    if(sHero.ReadBuff[HERO_RDS_STATUS] & 0x20) //First PI
                    {
                        //Get First PI, Saved for AF Usage, Or Do AF PI Check Here!!

                        //Other Infoes will be desert, because of they will become available at the next data available!
                    #ifdef D_RDS_REGULAR_READ    
                        sRds.RegularReadDelay = TunerDelay(T50MS);
                    #endif//D_RDS_REGULAR_READ
                        return;
                    }

                    // Get Block Error Flag
                    sRds.BlockAQual = ((sHero.ReadBuff[HERO_RDS_ERR] >> 6) & 0x03);
                    sRds.BlockBQual = ((sHero.ReadBuff[HERO_RDS_ERR] >> 4) & 0x03);
                    sRds.BlockCQual = ((sHero.ReadBuff[HERO_RDS_ERR] >> 2) & 0x03);
                    sRds.BlockDQual = (sHero.ReadBuff[HERO_RDS_ERR] & 0x03);

                    // Get Block Data
                    sRds.BlockA = (uint16_t)(sHero.ReadBuff[HERO_RDS_AH] << 8) + sHero.ReadBuff[HERO_RDS_AL];
                    sRds.BlockB = (uint16_t)(sHero.ReadBuff[HERO_RDS_BH] << 8) + sHero.ReadBuff[HERO_RDS_BL];
                    sRds.BlockC = (uint16_t)(sHero.ReadBuff[HERO_RDS_CH] << 8) + sHero.ReadBuff[HERO_RDS_CL];
                    sRds.BlockD = (uint16_t)(sHero.ReadBuff[HERO_RDS_DH] << 8) + sHero.ReadBuff[HERO_RDS_DL];

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
            Result = Hero_ReadCommon(PrivateId,REG_RDS_A_H,1);
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
 * @function    Hero_ResetDecoder
 * @brief      Reset Rds Decoder
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_ResetDecoder(void)
{
#if 0
    HERO_DRIVER_TYPE_ENUM PrivateId = HERO_IIC_RDS_RESET_DECODER;
    uint8_t Result = SUBLAYER_DOING;    
    uint8_t IIcDataBuff[2];
    
    IIcDataBuff[0] = 0x09;
    IIcDataBuff[1] = (NXP663X_RDS|0x80);  

    Result = Hero_WriteCommon(PrivateId,IIcDataBuff,2);

    return (Result);
#else
    // Not Need because of automatic restart of RDS after tuning...
    return (SUBLAYER_DONE);
#endif
}

#endif//D_TUNER_MODULE_HERO

