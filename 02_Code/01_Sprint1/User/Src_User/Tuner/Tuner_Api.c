/**********************************************************
 * @file        Tuner_Api.c
 * @purpose    API Functions of Tuner
 * @version    0.01
 * @date        9. Oct. 2012
 * @author    Deefisher.Lyu
 * @brief       To Delivery Tuner's Info to Other Task 
 *                 Other Task Use these API get Info
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          9.Oct.2012        v0.01        created
 *  
  **********************************************************/
#define TUNER_API_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= public variable ==================== */


/* ========================= private variable =================== */

/* ========================= Function Announcement  =================== */

/* ========================= Code Part =================== */

/**********************************************************
 * @function    Tuner_Api_GetCurrently
 * @brief      Return Currently Info:Band, Preset, Frequency
 * @param      uint8_t* Buff                    
 * @retval     None
 **********************************************************/
void Tuner_Api_GetCurrently(uint8_t* Buff)
{
    Buff[0] = sTunerDat.sInfo.CurrentBand;
    Buff[1] = sTunerDat.sInfo.CurrentPreset;
    Buff[2] = (uint8_t)(sTunerDat.sInfo.CurrentFreq >> 8);
    Buff[3] = (uint8_t)(sTunerDat.sInfo.CurrentFreq & 0x00FF);
}
/**********************************************************
 * @function    Tuner_Api_GetBand
 * @brief      Return Currently Band Number
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetBand(void)
{
    return (sTunerDat.sInfo.CurrentBand);
}
/**********************************************************
 * @function    Tuner_Api_GetPreset
 * @brief      Return Currently Preset Number
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetPreset(void)
{
    return (sTunerDat.sInfo.CurrentPreset);
}
/**********************************************************
 * @function    Tuner_Api_GetFreq
 * @brief      Return Currently Frequency
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint16_t Tuner_Api_GetFreq(void)
{
    return (sTunerDat.sInfo.CurrentFreq);
}
/**********************************************************
 * @function    Tuner_Api_GetSpecifyPrst
 * @brief      Return Specific Preset 
 * @param      uint8_t Band    
 *            uint8_t Preset
 * @retval     Result
 **********************************************************/
uint16_t Tuner_Api_GetSpecifyPrst(uint8_t Band, uint8_t Preset)
{
    return (sTunerDat.sInfo.Preset[Band][Preset - 1]);
}
/**********************************************************
 * @function    Tuner_Api_GetPresetList
 * @brief      Return Preset List
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint16_t* Tuner_Api_GetPresetList(void)
{
    return (sTunerDat.sInfo.Preset[0]);
}
/**********************************************************
 * @function    Tuner_Api_GetValidList
 * @brief      Return Valid List
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint16_t* Tuner_Api_GetValidList(void)
{
    return (sTunerKeep.ValidList);
}
/**********************************************************
 * @function    Tuner_Api_GetValidHightlight
 * @brief      Return Valid List Highlight Number
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetValidHightlight(void)
{
    return (sTunerKeep.ValidHighlight);
}
/**********************************************************
 * @function    Tuner_Api_GetStereoMono
 * @brief      Return Stereo Mono Flag
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetStereoMono(void)
{
    return (sTuner.bStereoMono);
}
/**********************************************************
 * @function    Tuner_Api_GetPauseState
 * @brief      Return Pause State Flag
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetPauseState(void)
{
    return (sTunerKeep.bPausestate);
}

/**********************************************************
 * @function    Tuner_Api_GetSeekState
 * @brief      Return Seek State
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetSeekState(void)
{
    return (sTuner.uSeekState.SsTotal);
}
/**********************************************************
 * @function    Tuner_Api_GetSignalStr
 * @brief      Return Currently Signal Strength
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetSignalStr(void)
{
    return (sTuner.SignalStr);
}
/**********************************************************
 * @function    Tuner_Api_GetSetting
 * @brief      Return Currently Tuner Relative Setting
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetSetting(void)
{
    return (sTunerDat.sSetting.Total); 
}
/**********************************************************
 * @function    Tuner_Api_GetRdsSetting
 * @brief      Return Currently Tuner Relative Setting
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetRdsSetting(void)
{
    return (sTunerKeep.RdsSetting);
}
/**********************************************************
 * @function    Tuner_Api_GetRegion
 * @brief      Return Region Setting
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetRegion(void)
{
    return (sTunerKeep.Region);
}
/**********************************************************
 * @function    Tuner_Api_GetAfSetting
 * @brief      Return AF Setting
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetAfSetting(void)
{
    return (sTunerDat.sSetting.sMap.bAfSetting);
}
/**********************************************************
 * @function    Tuner_Api_GetRtNum
 * @brief      Return RadioText Number
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Tuner_Api_GetRtNum(void)
{
    return (sRds.NumRT);
}
/**********************************************************
 * @function	Tuner_Api_GetCfLev
 * @brief  	Return CF Level
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t Tuner_Api_GetCfLev(void)
{
	return (sTuner.Smeter);
}
/**********************************************************
 * @function	Tuner_Api_GetCfAdj
 * @brief  	Return CF Adjacent Channel
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetCfAdj(void)
{
	return (sTuner.AdjChannel);
}
/**********************************************************
 * @function	Tuner_Api_GetCfMul
 * @brief  	Return CF Multipath
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetCfMul(void)
{
	return (sTuner.Multipath);
}
/**********************************************************
 * @function	Tuner_Api_GetCfFof
 * @brief  	Return CF FoF
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetCfFof(void)
{
	return (sTuner.Fof);
}
/**********************************************************
 * @function	Tuner_Api_GetAfLev
 * @brief  	Return AF Level
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetAfLev(void)
{
	return (sTuner.FastAfSmeter);
}
/**********************************************************
 * @function	Tuner_Api_GetAfAdj
 * @brief  	Return AF Adjacent Channel
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetAfAdj(void)
{
	return (sTuner.FastAfAdjChannel);
}
/**********************************************************
 * @function	Tuner_Api_GetAfMul
 * @brief  	Return AF Multipath
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetAfMul(void)
{
	return (sTuner.FastAfMultipath);
}
/**********************************************************
 * @function	Tuner_Api_GetAfFof
 * @brief  	Return AF FoF
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetAfFof(void)
{
	return (sTuner.FastAfFof );
}
/**********************************************************
 * @function	Tuner_Api_GetTP
 * @brief  	Return TP Status
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetTP(void)
{
	return (sRds.TPValid);
}
/**********************************************************
 * @function	Tuner_Api_GetTA
 * @brief  	Return TA Status
 * @param  	None					
 * @retval 	Result
 **********************************************************/
uint8_t  Tuner_Api_GetTA(void)
{
	return (sRds.TAValid);
}

