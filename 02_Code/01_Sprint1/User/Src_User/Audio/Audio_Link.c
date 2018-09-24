/**********************************************************
 * @file        Audio_Link.c
 * @purpose    LinkLayer for Audio
 * @version    0.01
 * @date        26. Nov. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          26.Nov.2012        v0.01        created
 *  
  **********************************************************/
#define AUDIO_LINK_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= public variable ==================== */

/* ========================= private variable =================== */

/* ========================= Code Part =================== */

//4 ASP Startup Related...Start
/**********************************************************
 * @function    Audio_Asp_OpenPwr
 * @brief      Open Power of ASP
 * @param    NULL                    
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_Asp_OpenPwr(void)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_OpenPower();    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_Asp_Reset
 * @brief      Reset Asp Module
 * @param    NULL                    
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_Asp_Reset(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
    sAudioKeep.AspModule = AUDIO_ASP_HERO;
    sAudio.AspCheck = 1;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_Reset();    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_Asp_Register
 * @brief      Initialize Register of ASP
 * @param    NULL                    
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_Asp_Register(void)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_Register();    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
//4 ASP Startup Related...End
/**********************************************************
 * @function    Audio_SetVolume
 * @brief      Set Volume
 * @param    uint8_t VolVal      
 *                  uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetVolume(uint8_t VolVal, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_DrvSetVolume(VolVal,Type);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_SetNaviVol
 * @brief      Set Navigation Channel Volume
 * @param    uint8_t VolVal      
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetNaviVol(uint8_t VolVal)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_NavPhoneVol(VolVal,0);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_SetBtVol
 * @brief      Set Phone Channel Volume
 * @param    uint8_t VolVal      
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetBtVol(uint8_t VolVal)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_NavPhoneVol(VolVal,1);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_SetBass
 * @brief      Set Bass
 * @param    PN_FILTER_STRUCT sBass   
 *                  uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetBass(PN_FILTER_STRUCT sBass,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetBass(sBass,Type);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_SetMid
 * @brief      Set Middle
 * @param    PN_FILTER_STRUCT sMid   
 *                  uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetMid(PN_FILTER_STRUCT sMid,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetMid(sMid,Type);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_SetTreble
 * @brief      Set Treble
 * @param    PN_FILTER_STRUCT sTreble   
 *                  uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetTreble(PN_FILTER_STRUCT sTreble,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetTreble(sTreble,Type);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_Asp_SwitchAch
 * @brief      Switch Ach
 * @param   uint8_t Ach 
 *                  uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_Asp_SwitchAch(uint8_t Ach, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SwitchAch(Ach,Type);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_Beep
 * @brief      Set Beep
 * @param   uint8_t Type 
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_Beep(uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_Beep(Type);    
    }
#endif//D_AUDIO_ASP_HERO


    return (Result);
}
/**********************************************************
 * @function    Audio_BeepStop
 * @brief      Stop Beep
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_BeepStop(void)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_BeepStop();    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_BeepPos
 * @brief      Set Beep Position
 * @param   uint8_t Pos 
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_BeepSetPos(uint8_t Pos)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_BeepPos(Pos);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_BeepVol
 * @brief      Set Beep Volume
 * @param   uint8_t Val 
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_BeepSetVol(uint8_t Val)
{
    uint8_t Result = SUBLAYER_DOING;

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_BeepVol(Val);    
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_SetMixRoute
 * @brief      Set Mix Route..
 * @param   uint8_t Src
 *              uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetMixRoute(uint8_t Src, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = SUBLAYER_DONE;
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetMixSrc
 * @brief      Set Mix Source..
 * @param   uint8_t Src
 *              uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetMixSrc(uint8_t Src, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetMixSrc(Src,Type);
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetMixPos
 * @brief      Set Mix Position..
 * @param   uint8_t Src
 *              uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetMixPos(uint8_t Src, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_ConfigMix(Src,Type,-1);//keilee 20140529 
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetMixGain
 * @brief      Set Mix Gain..
 * @param   uint8_t Src
 *              uint8_t Type
 *              uint8_t Gain
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetMixGain(uint8_t Src, uint8_t Type, uint8_t Gain)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
    }
#endif//D_AUDIO_ASP_HERO
    
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Audio_SetBalFad
 * @brief      Set Balance Fader
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetBalFad(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetBalFad();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetDcFilter
 * @brief      Set DC Filter..
 * @param   uint8_t Val
 *              uint8_t Type
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetDcFilter(uint8_t Val, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetDcFilter(Val,Type);
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetDelayLine
 * @brief      Set Delay line
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetDelayLine(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_DelayLine();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetGeq
 * @brief      Set Graphic Equalizer
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetGeq(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetGeq();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetPeq
 * @brief      Set Parametric Equalizer
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetPeq(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = SUBLAYER_DONE;
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetPhaseShifter
 * @brief      Set Phase Shifter
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetPhaseShifter(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetPhaseShifter();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetLoudness
 * @brief      Set Loudness
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetLoudness(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetLoudness();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetSubwoofer
 * @brief      Set Subwoofer
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetSubwoofer(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetSubwoofer();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetChanGain
 * @brief      Set Channel Gain
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetChanGain(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetChanGain();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetUltraBass
 * @brief      Set UltraBass
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetUltraBass(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetUltraBass();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetCrossOver
 * @brief      Set Cross Over
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetCrossOver(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
  	 Result =  Hero_SetCrossOver();
       // Result = SUBLAYER_DONE;
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_CC_Enable
 * @brief      Click Clack Enable
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_CC_Enable(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_CCEnable();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_CC_Disable
 * @brief      Click Clack Disable
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_CC_Disable(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_CCDisable();
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SetClickClack
 * @brief     Set Click Clack
 * @param   
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetClickClack(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_CCSet(Mode);
    }
#endif//D_AUDIO_ASP_HERO
    
    return (Result);
}
/**********************************************************
 * @function    Audio_SoftMute
 * @brief      Audio SoftMute Channel
 * @param      uint8_t Channel: Front Channel, Rear Channel
 *            uint8_t Type: Mute On, Mute Off
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_SoftMute(uint8_t Channel,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint16_t TmpChannel;

    if(SYSTEM_FRONT == Channel)
    {
        TmpChannel = 0x0100;    //Primary
    }
    else if(SYSTEM_REAR == Channel)
    {
        TmpChannel = 0x0200;    //Secondary
    }
    else if(SYSTEM_ALL == Channel)
    {
        TmpChannel = (0x0100 | 0x0200);
    }
    
#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SoftMute(TmpChannel,Type);
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}
/**********************************************************
 * @function    Audio_SetSrcScaler
 * @brief      Set Source Scaler
 * @param    
 * @retval    Result of execute
 **********************************************************/
uint8_t Audio_SetSrcScaler(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t ScalerVal = (AUDIO_SRC_SCALER_MAX / 2);
    
    ScalerVal = Audio_GetSourceScaler(sAudio.SysChannel);

#ifdef D_AUDIO_ASP_HERO
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        Result = Hero_SetSrcScaler(SYSTEM_FRONT,ScalerVal);  
    }
#endif//D_AUDIO_ASP_HERO

    return (Result);
}

