/**********************************************************
 * @file        Audio_Api.h
 * @purpose    Definition of Audio API
 * @version    0.01
 * @date        18.Oct. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        18.Oct.2012              v0.01        created
 *  
  **********************************************************/
#ifndef AUDIO_API_H
#define AUDIO_API_H

#ifdef AUDIO_API_C
#define EXTERN
#else
#define EXTERN extern
#endif//AUDIO_API_C


//--------------------------------------------------------------
//1 Declare: Start

EXTERN uint8_t Audio_Api_GetReadyState(void);
EXTERN uint8_t Audio_Api_GetVolume(void);
EXTERN uint8_t Audio_Api_GetVolType(void);
EXTERN PN_FILTER_STRUCT Audio_Api_GetBass(void);
EXTERN PN_FILTER_STRUCT Audio_Api_GetMid(void);
EXTERN PN_FILTER_STRUCT Audio_Api_GetTreble(void);
EXTERN uint8_t Audio_Api_GetBalance(void);
EXTERN uint8_t Audio_Api_GetFader(void);
EXTERN SW_ATTRI_STRUCT Audio_Api_GetSubwoofer(void);
EXTERN LOUDNESS_ATTRI_STRUCT Audio_Api_GetLoudness(void);
EXTERN AUDIO_BASIC_STRUCT* Audio_Api_GetBasicInfo(void);
EXTERN uint8_t Audio_Api_GetMute(void);
EXTERN uint8_t Audio_Api_GetAchMute(uint8_t Ach);
EXTERN uint8_t* Audio_Api_GetDelayLine(void);
EXTERN uint8_t Audio_Api_GetDelayPreset(void);
EXTERN uint8_t Audio_Api_GetDcFilter(void);
EXTERN AUDIO_GEQ_STRUCT* Audio_Api_GetGeq(void);
EXTERN AUDIO_CHANGAIN_STRUCT* Audio_Api_GetChanGain(void);
EXTERN PN_FILTER_STRUCT* Audio_Api_GetPeq(void);
EXTERN uint8_t Audio_Api_GetPeqMode(void);
EXTERN uint8_t* Audio_Api_GetPhaseShifter(void);
EXTERN int32_t RoundChange(double Val, uint8_t Mode);
//1 Declare: End
//--------------------------------------------------------------

#undef EXTERN

#endif//AUDIO_API_H

