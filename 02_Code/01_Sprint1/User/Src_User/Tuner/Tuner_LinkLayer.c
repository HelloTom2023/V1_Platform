/**********************************************************
 * @file        Tuner_LinkLayer.c
 * @purpose    Link Layer Functions of Tuner
 * @version    0.01
 * @date        2. July. 2012
 * @author    Deefisher.Lyu
 * @brief       According Specific Application, the Linklayer execute 
 *                 step will not same  
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          2.July.2012        v0.01        created
 *  
  **********************************************************/
#define TUNER_LINKLAYER_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= public variable ==================== */


/* ========================= private variable =================== */

/* ========================= Function Announcement  =================== */

/* ========================= Code Part =================== */

/**********************************************************
 * @function    Tuner_OpenPower
 * @brief      Power On Tuner Module
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_OpenPower(void)    //No Power Control for Currently Project
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Tuner_ResetModule
 * @brief      Reset Tuner Module
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_ResetModule(void)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_Reset();
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Tuner_InitBoot
 * @brief      Initialize Tuner's Boot Registers
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_InitBoot(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO    
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_InitBoot();  
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Tuner_InitRds
 * @brief      Initialize Tuner's Rds Registers: 
 *                 Select Rds Mode, Enable Rds...
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_InitRds(void)
{
    uint8_t Result = SUBLAYER_DOING;

    if(RDS_SET_OFF == sTunerKeep.RdsSetting)
    {
        Result = SUBLAYER_DONE;
    }
    else
    {
    #ifdef D_TUNER_MODULE_HERO    
        if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
        {
            Result = Tuner_Hero_InitRds();    
        }
    #endif//D_TUNER_MODULE_HERO
    }
    
    return (Result);
}
/**********************************************************
 * @function    Tuner_SetBand
 * @brief      Set Currenly Band    
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_SetBand(void)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_TUNER_MODULE_HERO        
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_SetBand();    
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);    
}
/**********************************************************
 * @function    Tuner_SetFreq
 * @brief      Set frequency input            
 * @param      uint16_t Freq: frequency value to be set                    
 * @retval     None
 **********************************************************/
uint8_t Tuner_SetFreq(uint16_t Freq)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_TUNER_MODULE_HERO        
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_SetFreq(Freq);  
    }
#endif//D_TUNER_MODULE_HERO

    //Switch to A new Frequency Done!,Reset Relative Paramters
    if(SUBLAYER_DONE == Result)
    {
        sTuner.StereoNoCnt = 0;
        sTuner.StereoYesCnt = 0;
        sTuner.bStereoMono = 0;
        //Reset Rds Related...
        Rds_ResetAll();
    }

    return (Result);
}
/**********************************************************
 * @function    Tuner_SwtichST
 * @brief      Switch Stereo to: Auto or Forced Mono
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_SwtichST(void)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_TUNER_MODULE_HERO        
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_SwitchST(StereoSetting); 
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);    
}
/**********************************************************
 * @function    Tuner_ConfigMode
 * @brief      Set Tuner's Work Mode        
 * @param      uint8_t Mode: PRESET_MODE,SEARCH_MODE                    
 * @retval     None
 **********************************************************/
uint8_t Tuner_ConfigMode(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_TUNER_MODULE_HERO        
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_ConfigMode(Mode);   
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Tuner_CheckStation
 * @brief      Check Currently Station whether a valid Station        
 * @param      None        
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_CheckStation(uint8_t ChkMode)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO        
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_CheckStation(ChkMode);    
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Tuner_SeekNext
 * @brief      Seek Next Frequency
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_SeekNext(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO        
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_SeekNext(Mode);     
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);    
}
/**********************************************************
 * @function    Tuner_PreviewConfig
 * @brief      Config Before Preview
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_PreviewConfig(void)
{
    uint8_t Result = SUBLAYER_DOING;    
    
#ifdef D_TUNER_MODULE_HERO    
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Tuner_Hero_ConfigMode(TUNER_MODE_PRESET);     
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Tuner_GetQualVal
 * @brief      Check the Specific Frequency whether is a Preset of
 * @param      None                    
 * @retval     Quality Value of Currently Station 
 **********************************************************/
uint8_t Tuner_GetQualVal(void)
{
#ifdef D_TUNER_MODULE_HERO    
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        return (Tuner_Hero_GetQualVal());
    }
#endif//D_TUNER_MODULE_HERO

}
/**********************************************************
 * @function    Tuner_GetSignalStr
 * @brief      Get Currently Signal Strength
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_GetSignalStr(void)
{
#ifdef D_TUNER_MODULE_HERO    
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        return (Tuner_Hero_GetSignalStr());
    }
#endif//D_TUNER_MODULE_HERO

}
/**********************************************************
 * @function    Tuner_GetStereoFlag
 * @brief      Get Currently Stereo Flag
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_GetStereoFlag(void)
{
#ifdef D_TUNER_MODULE_HERO    
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        return (Tuner_Hero_GetStereoFlag());    
    }
#endif//D_TUNER_MODULE_HERO
}
/**********************************************************
 * @function    Tuner_GetInfoes
 * @brief      Get Infoes
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_GetInfoes(void)
{
#ifdef D_TUNER_MODULE_HERO    
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        return (Tuner_Hero_GetInfoes());
    }
#endif//D_TUNER_MODULE_HERO

}
/**********************************************************
 * @function    Tuner_GetAfQuality
 * @brief      Get Alternative Frequency's Quality
 * @param      uint16_t Freq
 *            uint8_t Num
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_GetAfQuality(uint16_t Freq, uint8_t Num)
{
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
        return (Hero_GetAfQuality(Freq,Num));    
#endif//D_TUNER_MODULE_HERO

}
/**********************************************************
 * @function    Tuner_SetBw
 * @brief      Set Tuner Bandwidth
 * @param     uint8_t Mode
 *            uint8_t Bw
 * @retval     Result of Executing
 **********************************************************/
uint8_t Tuner_SetBw(uint8_t Mode,uint8_t Bw)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Hero_SetBw(Mode,Bw);
    }
#endif//D_TUNER_MODULE_HERO


    return (Result);
}
/**********************************************************
 * @function    Rds_AF_Update
 * @brief      AF update
 * @param     uint16_t FreqAf
 * @retval     Result of Executing
 **********************************************************/
uint8_t Rds_AF_Update(uint16_t FreqAf)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Hero_AF_Update(FreqAf);
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Rds_AF_Jump
 * @brief      AF jump
 * @param     uint8_t FreqAf
 * @retval     Result of Executing
 **********************************************************/
uint8_t Rds_AF_Jump(uint8_t FreqAf)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Hero_AF_Jump(FreqAf);
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Rds_GetCFQual
 * @brief      Get Current Frequency ' Quality
 * @param     uint8_t Num
 * @retval     Result of Executing
 **********************************************************/
uint8_t Rds_GetCFQual(uint8_t Num)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Hero_GetCFQuality(Num);
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Rds_GetAfQual
 * @brief      Get AF' Quality
 * @param     uint8_t Num
 * @retval     Result of Executing
 **********************************************************/
uint8_t Rds_GetAfQual(uint16_t Freq, uint8_t Num)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Hero_GetAfQuality(Freq,Num);
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Rds_AfSwitch
 * @brief      AF Switch
 * @param     uint8_t Num
 * @retval     Result of Executing
 **********************************************************/
uint8_t Rds_AfSwitch(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Hero_AfSwitch(Mode);
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}
/**********************************************************
 * @function    Rds_FetchBlockDat
 * @brief     Fetch Block Datum
 * @param   
 * @retval     Result of Executing
 **********************************************************/
void Rds_FetchBlockDat(void)
{
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Hero_FetchBlockDat();
    }
#endif//D_TUNER_MODULE_HERO
}
/**********************************************************
 * @function    Rds_ResetDecoder
 * @brief    
 * @param   
 * @retval     Result of Executing
 **********************************************************/
uint8_t Rds_ResetDecoder(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_TUNER_MODULE_HERO
    if(TUNER_MODULE_TEF6638 == sTuner.ModuleType)
    {
        Result = Hero_ResetDecoder();
    }
#endif//D_TUNER_MODULE_HERO

    return (Result);
}

