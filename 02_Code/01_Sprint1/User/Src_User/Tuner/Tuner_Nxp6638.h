/**********************************************************
 * @file        Tuner_Nxp6638.h
 * @purpose    Definition of Tuner Nxp6638
 * @version    0.01
 * @date        27. June. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        27.June.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TUNER_NXP6638_H
#define TUNER_NXP6638_H

#ifdef D_TUNER_MODULE_HERO
#ifdef TUNER_NXP6638_C
#define EXTERN
#else
#define EXTERN extern
#endif//TASK_TUNER_C


//............................................................................................
//4 Nxp6638 Control Step Definitions : Start

// Set Band Steps
typedef enum nxp6638_set_band_enum
{
    NXP6638_BAND_INIT_PARA = 0,
    NXP6638_BAND_SET_BAND,  
    NXP6638_BAND_REGISTER,    // Initialize band related registers
    NXP6638_BAND_SET_EX1,                // Set Band
    NXP6638_BAND_END,                // End
}NXP6638_SET_BAND_ENUM;

// Set Freq Steps
typedef enum nxp6638_set_freq_enum
{
    NXP6638_FREQ_SET,                // Set Freq
    NXP6638_FREQ_END,                // End
}NXP6638_SET_FREQ_ENUM;

// Check Station  Steps
typedef enum nxp6638_qual_check_enum
{
    NXP6638_QUAL_GET,        // Get Station Quaility        
    NXP6638_QUAL_CHK,      // Check Station Quality
    NXP6638_QUAL_END,        // Check End        
}NXP6638_QUAL_CHECK_ENUM;

// Get AF Quality  Steps
typedef enum hero_get_af_qual_enum
{
    HERO_AF_QUAL_INIT = 0,    // Initial Before Get a AF Quallity    
    HERO_AF_QUAL_UPDATE,      // AF_Update
    HERO_AF_QUAL_GET,         //Read AF Quality
    HERO_AF_QUAL_END,        // Check End        
}HERO_AF_QUAL_ENUM;


//4Nxp6638 Layer Control Step Definitions : End
//............................................................................................


//
#define REG_STATUS    0x00
#define REG_LEVEL    0x01
#define REG_USN        0x02
#define REG_WAM    0x03    
#define REG_FOF        0x04
#define REG_IFBW    0x05
#define REG_MOD    0x06


//Fetch Rds Group
#define REG_RDS_STATUS  0x07
#define REG_RDS_A_H    0x08
#define REG_RDS_A_L        0x09
#define REG_RDS_B_H    0x0A
#define REG_RDS_B_L        0x0B
#define REG_RDS_C_H    0x0C
#define REG_RDS_C_L        0x0D
#define REG_RDS_D_H    0x0E    
#define REG_RDS_D_L    0x0F
#define REG_RDS_ERR    0x10

#define RDS_NO_ERR 0
#define RDS_SMALL_ERR 1
#define RDS_LARGE_ERR 2
#define RDS_ALL_ERR 3

#define RDS_ERR_LEVEL    RDS_NO_ERR

//............................................................................................
//2 Declare : Start

EXTERN uint8_t Tuner_Hero_Reset(void);
EXTERN uint8_t Tuner_Hero_InitBoot(void);
EXTERN uint8_t Tuner_Hero_InitRds(void);
EXTERN uint8_t Tuner_Hero_SetBand(void);
EXTERN uint8_t Tuner_Hero_SetFreq(uint16_t Freq);
EXTERN uint8_t Tuner_Hero_ConfigMode(uint8_t Mode);
EXTERN uint8_t Tuner_Hero_CheckStation(uint8_t ChkMode);
EXTERN uint8_t Tuner_Hero_SeekNext(uint8_t Mode);
EXTERN uint8_t Tuner_Hero_InitialAll(void);
EXTERN uint8_t Tuner_Hero_SendCmd(HERO_DRIVER_TYPE_ENUM PID,uint8_t Band, uint16_t Freq, uint8_t Mode);
EXTERN uint8_t Tuner_Hero_SwitchST(uint8_t Mode);
EXTERN uint8_t Tuner_Hero_GetQualVal(void);
EXTERN uint8_t Tuner_Hero_GetSignalStr(void);
EXTERN uint8_t Tuner_Hero_GetStereoFlag(void);
EXTERN uint8_t Tuner_Hero_GetInfoes(void);
EXTERN uint8_t Tuner_Hero_InitialAll_TestMode(void);
//2 Declare : End
//............................................................................................

#undef EXTERN

#endif//D_TUNER_MODULE_HERO

#endif//TUNER_NXP6638_H

