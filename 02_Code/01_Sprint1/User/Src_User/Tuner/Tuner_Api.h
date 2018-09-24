/**********************************************************
 * @file        Tuner_LinkLayer.h
 * @purpose    Definition of Tuner Link Layer
 * @version    0.01
 * @date        2. July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        2.July.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TUNER_API_H
#define TUNER_API_H

#ifdef TUNER_API_C
#define EXTERN
#else
#define EXTERN extern
#endif//TUNER_API_C



//--------------------------------------------------------------
//1 Declare: Start

EXTERN void Tuner_Api_GetCurrently(uint8_t* Buff);
EXTERN uint8_t Tuner_Api_GetBand(void);
EXTERN uint8_t Tuner_Api_GetPreset(void);
EXTERN uint16_t Tuner_Api_GetFreq(void);
EXTERN uint16_t Tuner_Api_GetSpecifyPrst(uint8_t Band, uint8_t Preset);
EXTERN uint16_t* Tuner_Api_GetPresetList(void);
EXTERN uint16_t* Tuner_Api_GetValidList(void);
EXTERN uint8_t Tuner_Api_GetValidHightlight(void);
EXTERN uint8_t Tuner_Api_GetStereoMono(void);
EXTERN uint8_t Tuner_Api_GetPauseState(void);
EXTERN uint8_t Tuner_Api_GetSeekState(void);
EXTERN uint8_t Tuner_Api_GetSignalStr(void);
EXTERN uint8_t Tuner_Api_GetSetting(void);
EXTERN uint8_t Tuner_Api_GetRdsSetting(void);
EXTERN uint8_t Tuner_Api_GetRegion(void);
EXTERN uint8_t Tuner_Api_GetAfSetting(void);
EXTERN uint8_t  Tuner_Api_GetCfLev(void);
EXTERN uint8_t Tuner_Api_GetCfAdj(void);
EXTERN uint8_t  Tuner_Api_GetCfMul(void);
EXTERN uint8_t  Tuner_Api_GetCfFof(void);
EXTERN uint8_t  Tuner_Api_GetAfLev(void);
EXTERN uint8_t  Tuner_Api_GetAfAdj(void);
EXTERN uint8_t  Tuner_Api_GetAfMul(void);
EXTERN uint8_t  Tuner_Api_GetAfFof(void);
EXTERN uint8_t  Tuner_Api_GetTP(void);
EXTERN uint8_t  Tuner_Api_GetTA(void);

//1 Declare: End
//--------------------------------------------------------------


#undef EXTERN

#endif//TUNER_API_H

