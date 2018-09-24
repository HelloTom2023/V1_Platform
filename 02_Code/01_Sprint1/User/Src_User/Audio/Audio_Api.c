/**********************************************************
 * @file        Audio_Api.c
 * @purpose    API Functions of Audio
 * @version    0.01
 * @date        18. Oct. 2012
 * @author    Deefisher.Lyu
 * @brief       To Delivery Audio's Info to Other Task 
 *                 Other Task Use these API get Info
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          18.Oct.2012        v0.01        created
 *  
  **********************************************************/
#define AUDIO_API_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= public variable ==================== */


/* ========================= private variable =================== */

/* ========================= Function Announcement  =================== */

/* ========================= Code Part =================== */
/**********************************************************
 * @function    RoundChange
 * @brief      Round
 * @param      double Val
 *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
int32_t RoundChange(double Val, uint8_t Mode)
{
    int32_t Result = 0;
    int32_t TmpVal = (int32_t)Val;

    //Positive
    if(Val >= 0)
    {
        if((Val - TmpVal) >= 0.5)    //Round 
        {
            Result = TmpVal + 1;
        }
        else
        {
            Result = TmpVal;
        }
    }
    else    //Negative
    {
        if((-(Val - TmpVal)) >= 0.5)
        {
            Result = TmpVal - 1;
        }
        else
        {
            Result = TmpVal;
        }
    }

    if(0 == Mode)
    {
        if(Result > 2047)
        {
            Result = 2047;
        }
    }
    else if(1 == Mode)
    {
        if(Result > 8388607)
        {
            Result = 8388607;
        }
    }

    return (Result);
}

/**********************************************************
 * @function    Audio_Api_GetReadyState
 * @brief      Return Audio Ready Info: 0 Not Ready; 1 Ready 
 *            Bit0: Audio Task Ready
 *            Bit1: Asp Init Ready
 *            Bit2: Amp Init Ready
 *            Bit3: Switch Init Ready
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetReadyState(void)
{
    return (sAudio.ReadyState);
}
/**********************************************************
 * @function    Audio_Api_GetVolume
 * @brief      Return Currently Volume
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetVolume(void)
{
    return (sAudioKeep.CurrentlyVol);
}
/**********************************************************
 * @function    Audio_Api_GetVolType
 * @brief      Return Currently Volume Type
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetVolType(void)
{
    return (Audio_GetVolType());
}
/**********************************************************
 * @function    Audio_Api_GetBass
 * @brief      Return Currently Bass Setting
 * @param      None                    
 * @retval     Result
 **********************************************************/
PN_FILTER_STRUCT Audio_Api_GetBass(void)
{
    return (sAudioDat.sBasic.sBass);
}
/**********************************************************
 * @function    Audio_Api_GetMid
 * @brief      Return Currently Middle Setting
 * @param      None                    
 * @retval     Result
 **********************************************************/
PN_FILTER_STRUCT Audio_Api_GetMid(void)
{
    return (sAudioDat.sBasic.sMid);
}
/**********************************************************
 * @function    Audio_Api_GetTreble
 * @brief      Return Currently Treble Setting
 * @param      None                    
 * @retval     Result
 **********************************************************/
PN_FILTER_STRUCT Audio_Api_GetTreble(void)
{
    return (sAudioDat.sBasic.sTreble);
}
/**********************************************************
 * @function    Audio_Api_GetBalance
 * @brief      Return Currently Balance Value
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetBalance(void)
{
    return (sAudioDat.sBasic.Balance);
}
/**********************************************************
 * @function    Audio_Api_GetFader
 * @brief      Return Currently Fader Value
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetFader(void)
{
    return (sAudioDat.sBasic.Fader);
}
/**********************************************************
 * @function    Audio_Api_GetSubwoofer
 * @brief      Return Subwoofer Setting
 * @param      Null                
 * @retval     Result
 **********************************************************/
SW_ATTRI_STRUCT Audio_Api_GetSubwoofer(void)
{
    return (sAudioDat.sBasicBK.sSubWoofer);
}
/**********************************************************
 * @function    Audio_Api_GetLoudness
 * @brief      Return Loudness Setting
 * @param      Null                
 * @retval     Result
 **********************************************************/
LOUDNESS_ATTRI_STRUCT Audio_Api_GetLoudness(void)
{
    return (sAudioDat.sBasicBK.sLoudness);
}
/**********************************************************
 * @function    Audio_Api_GetBasicInfo
 * @brief      Return Audio Basic Settings
 * @param      Null                
 * @retval     Result
 **********************************************************/
AUDIO_BASIC_STRUCT* Audio_Api_GetBasicInfo(void)
{
    return ((AUDIO_BASIC_STRUCT*)(&sAudioDat.sBasic));
}
/**********************************************************
 * @function    Audio_Api_GetMute
 * @brief      Return Mute State: 1 Mute; 0 Unmute
 *                 The State Only Sign Currently Channel's
 *            b0:Key Mute State 
 *            b1:Soft Mute State
 *            b2:Hard Mute State
 *            b3:Rear Key Mute State
 *            b4:Rear Soft Mute State
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetMute(void)
{
    return (sAudio.MuteState);
}
/**********************************************************
 * @function    Audio_Api_GetAchMute
 * @brief      Return Audio Channel's Mute Attribute
 * @param      uint8_t Ach                    
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetAchMute(uint8_t Ach)
{
    return (sAudio.sAchAttri[Ach].MuteState);
}
/**********************************************************
 * @function    Audio_Api_GetDelayLine
 * @brief      Return Audio Delay Line Setting
 * @param      Null                
 * @retval     Result
 **********************************************************/
uint8_t* Audio_Api_GetDelayLine(void)
{
    return (sAudioDat.sAdv.DelayCustom);
}
/**********************************************************
 * @function    Audio_Api_GetDelayPreset
 * @brief      Return Audio Delay Line Preset
 * @param      Null                
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetDelayPreset(void)
{
    return (sAudioDat.sAdv.DelayPreset);
}
/**********************************************************
 * @function    Audio_Api_GetDcFilter
 * @brief      Return DC Filter Setting
 * @param      Null                
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetDcFilter(void)
{
    return (sAudioDat.sAdv.DcFilter);
}
/**********************************************************
 * @function    Audio_Api_GetGeq
 * @brief      Return Geq Detaled setting
 * @param      Null                
 * @retval     Result
 **********************************************************/
AUDIO_GEQ_STRUCT* Audio_Api_GetGeq(void)
{
    return ((AUDIO_GEQ_STRUCT*)(&sAudioDat.sGeq));
}
/**********************************************************
 * @function    Audio_Api_GetChanGain
 * @brief      Return Audio Source&Speaker Gain Settings
 * @param      Null                
 * @retval     Result
 **********************************************************/
AUDIO_CHANGAIN_STRUCT* Audio_Api_GetChanGain(void)
{
    return ((AUDIO_CHANGAIN_STRUCT*)(&sAudioDat.sGain));
}
/**********************************************************
 * @function    Audio_Api_GetPeq
 * @brief      Return Peq Detaled setting
 * @param      Null                
 * @retval     Result
 **********************************************************/
PN_FILTER_STRUCT* Audio_Api_GetPeq(void)
{
    return (&(sAudioPeq.sBuffer[0][0]));
}
/**********************************************************
 * @function    Audio_Api_GetPeqMode
 * @brief      Return PEQ Mode
 * @param      Null                
 * @retval     Result
 **********************************************************/
uint8_t Audio_Api_GetPeqMode(void)
{
    return (sAudioPeq.Type);
}
/**********************************************************
 * @function    Audio_Api_GetPhaseShifter
 * @brief      Return Phase Shifter Setting
 * @param      Null                
 * @retval     Result
 **********************************************************/
uint8_t* Audio_Api_GetPhaseShifter(void)
{
    return (sAudioDat.sAdv.PhaseShifter);
}

