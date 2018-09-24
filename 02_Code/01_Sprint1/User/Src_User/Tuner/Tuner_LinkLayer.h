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
#ifndef TUNER_LINKLAYER_H
#define TUNER_LINKLAYER_H

#ifdef TUNER_LINKLAYER_C
#define EXTERN
#else
#define EXTERN extern
#endif//TUNER_LINKLAYER_C

//............................................................................................
//4 Tuner Link Layer Control Step Definitions : Start



//4Tuner Link Layer Control Step Definitions : End
//............................................................................................


//--------------------------------------------------------------
//3 Function Declare :Start

EXTERN uint8_t Tuner_OpenPower(void);
EXTERN uint8_t Tuner_ResetModule(void);
EXTERN uint8_t Tuner_InitBoot(void);
EXTERN uint8_t Tuner_InitRds(void);
EXTERN uint8_t Tuner_SetBand(void);
EXTERN uint8_t Tuner_SetFreq(uint16_t Freq);
EXTERN uint8_t Tuner_ConfigMode(uint8_t Mode);
EXTERN uint8_t Tuner_CheckStation(uint8_t ChkMode);
EXTERN uint8_t Tuner_SeekNext(uint8_t Mode);
EXTERN uint8_t Tuner_PreviewConfig(void);
EXTERN uint8_t Tuner_GetQualVal(void);
EXTERN uint8_t Tuner_GetInfoes(void);
EXTERN uint8_t Tuner_GetSignalStr(void);
EXTERN uint8_t Tuner_SwtichST(void);
EXTERN uint8_t Tuner_GetStereoFlag(void);
EXTERN uint8_t Tuner_GetAfQuality(uint16_t Freq, uint8_t Num);

EXTERN uint8_t Tuner_SetBw(uint8_t Mode,uint8_t Bw);
EXTERN uint8_t Rds_AF_Update(uint16_t FreqAf);   
EXTERN uint8_t Rds_AF_Jump(uint8_t FreqAf);         
EXTERN uint8_t Rds_GetCFQual(uint8_t Num);        
EXTERN uint8_t Rds_GetAfQual(uint16_t Freq, uint8_t Num);     
EXTERN uint8_t Rds_AfSwitch(uint8_t Mode);        
EXTERN void Rds_FetchBlockDat(void);
EXTERN uint8_t Rds_ResetDecoder(void);    

//3 Function Declare :End
//--------------------------------------------------------------


//--------------------------------------------------------------
//3  Definitions:Start

// Check Driver Bus State
#define Tuner_CheckBusState()    I2C0_Busy()    

typedef enum iic_drv_type_enum
{
    IIC_DRV_TYPE_IDLE = 0,
    IIC_DRV_NXP6638_INITIALALL,
    IIC_DRV_NXP6638_SENDCMD,
        
}IIC_DRV_TYPE_ENUM;


//3 Definitions:End
//--------------------------------------------------------------

#undef EXTERN

#endif//TUNER_LINKLAYER_H

