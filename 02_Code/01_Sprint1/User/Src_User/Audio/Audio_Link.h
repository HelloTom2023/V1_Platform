/**********************************************************
 * @file        Audio_Link.h
 * @purpose    Definition of Audio Link
 * @version    0.01
 * @date        26. Nov. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        26.Nov.2012              v0.01        created
 *  
  **********************************************************/
#ifndef AUDIO_LINK_H
#define AUDIO_LINK_H

#ifdef AUDIO_LINK_C
#define EXTERN
#else
#define EXTERN extern
#endif//AUDIO_LINK_C

EXTERN uint8_t Audio_Asp_OpenPwr(void);
EXTERN uint8_t Audio_Asp_Reset(void);
EXTERN uint8_t Audio_Asp_Register(void);
EXTERN uint8_t Audio_SetVolume(uint8_t VolVal, uint8_t Type);
EXTERN uint8_t Audio_SetNaviVol(uint8_t VolVal);
EXTERN uint8_t Audio_SetBtVol(uint8_t VolVal);
EXTERN uint8_t Audio_SetBass(PN_FILTER_STRUCT sBass,uint8_t Type);
EXTERN uint8_t Audio_SetMid(PN_FILTER_STRUCT sMid,uint8_t Type);
EXTERN uint8_t Audio_SetTreble(PN_FILTER_STRUCT sTreble,uint8_t Type);
EXTERN uint8_t Audio_Asp_SwitchAch(uint8_t Ach, uint8_t Type);
EXTERN uint8_t Audio_Beep(uint8_t Type);
EXTERN uint8_t Audio_BeepStop(void);
EXTERN uint8_t Audio_BeepSetPos(uint8_t Pos);
EXTERN uint8_t Audio_BeepSetVol(uint8_t Val);
EXTERN uint8_t Audio_SetMixRoute(uint8_t Src, uint8_t Type);
EXTERN uint8_t Audio_SetMixSrc(uint8_t Src, uint8_t Type);
EXTERN uint8_t Audio_SetMixPos(uint8_t Src, uint8_t Type);
EXTERN uint8_t Audio_SetMixGain(uint8_t Src, uint8_t Type, uint8_t Gain);
EXTERN uint8_t Audio_SetBalFad(void);
EXTERN uint8_t Audio_SetDcFilter(uint8_t Val, uint8_t Type);
EXTERN uint8_t Audio_SetDelayLine(void);
EXTERN uint8_t Audio_SetGeq(void);
EXTERN uint8_t Audio_SetPeq(void);
EXTERN uint8_t Audio_SetPhaseShifter(void);
EXTERN uint8_t Audio_SetLoudness(void);
EXTERN uint8_t Audio_SetSubwoofer(void);
EXTERN uint8_t Audio_SetChanGain(void);
EXTERN uint8_t Audio_SetUltraBass(void);
EXTERN uint8_t Audio_SetCrossOver(void);
EXTERN uint8_t Audio_CC_Enable(void);
EXTERN uint8_t Audio_CC_Disable(void);
EXTERN uint8_t Audio_SetClickClack(uint8_t Mode);
EXTERN uint8_t Audio_SoftMute(uint8_t Channel,uint8_t Type);
EXTERN uint8_t Audio_SetSrcScaler(void);


#undef EXTERN

#endif//AUDIO_LINK_H

