/**********************************************************
 * @file        Tuner_Dirana.h
 * @purpose    Definition of Tuner Dirana
 * @version    0.01
 * @date        24. Jan. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        24.Jan.2013              v0.01        created
 *  
  **********************************************************/
#ifndef TUNER_DIRANA_H
#define TUNER_DIRANA_H

#ifdef TUNER_DIRANA_C
#define EXTERN
#else
#define EXTERN extern
#endif//TUNER_DIRANA_C


//............................................................................................
//4 DiRaNa Control Step Definitions : Start

// Set Band Steps
typedef enum dirana_set_band_enum
{
    DIRANA_BAND_INIT_PARA = 0,
    DIRANA_BAND_SET_BAND,   // Set Band   
    DIRANA_BAND_REGISTER,    // Initialize band related registers
    DIRANA_BAND_SET_EX1,
    DIRANA_BAND_END,                // End
}DIRANA_SET_BAND_ENUM;

// Set Freq Steps
typedef enum dirana_set_freq_enum
{
    DIRANA_FREQ_SET,                // Set Freq
    DIRANA_FREQ_END,                // End
}DIRANA_SET_FREQ_ENUM;

// Check Station  Steps
typedef enum dirana_qual_check_enum
{
    DIRANA_QUAL_GET,        // Get Station Quaility        
    DIRANA_QUAL_CHK,      // Check Station Quality
    DIRANA_QUAL_END,        // Check End        
}DIRANA_QUAL_CHECK_ENUM;


// Get AF Quality  Steps
typedef enum dirana_get_af_qual_enum
{
    DIRANA_AF_QUAL_INIT = 0,    // Initial Before Get a AF Quallity    
    DIRANA_AF_QUAL_UPDATE,      // AF_Update
    DIRANA_AF_QUAL_GET,         //Read AF Quality
    DIRANA_AF_QUAL_END,        // Check End        
}DIRANA_AF_QUAL_ENUM;


//4 DiRaNa Layer Control Step Definitions : End
//............................................................................................

//LEV = (DB+8)*2

#define SIGNALSTR_10DB    ((10+8)*2)
#define SIGNALSTR_15DB    ((15+8)*2)
#define SIGNALSTR_20DB    ((20+8)*2)
#define SIGNALSTR_25DB    ((25+8)*2)
#define SIGNALSTR_30DB    ((30+8)*2)
#define SIGNALSTR_35DB    ((35+8)*2)
#define SIGNALSTR_40DB    ((40+8)*2)
#define SIGNALSTR_45DB    ((45+8)*2)
#define SIGNALSTR_50DB    ((50+8)*2)
#define SIGNALSTR_55DB    ((55+8)*2)
#define SIGNALSTR_60DB    ((60+8)*2)

#define NOISE_USN_LEV0        ((255 * 15) / 100)
#define NOISE_USN_LEV1        ((255 * 25) / 100)
#define NOISE_USN_LEV2        ((255 * 35) / 100)
#define NOISE_USN_LEV3        ((255 * 45) / 100)

#define NOISE_WAM_LEV0        ((255 * 15) / 100)
#define NOISE_WAM_LEV1        ((255 * 25) / 100)
#define NOISE_WAM_LEV2        ((255 * 35) / 100)
#define NOISE_WAM_LEV3        ((255 * 45) / 100)

#define SIGNALSTR_FM_LEV0        SIGNALSTR_15DB
#define SIGNALSTR_FM_LEV1        SIGNALSTR_30DB    
#define SIGNALSTR_FM_LEV2        SIGNALSTR_45DB

#define SIGNALSTR_AM_DELTA SIGNALSTR_15DB
#define SIGNALSTR_AM_LEV0        SIGNALSTR_35DB 
#define SIGNALSTR_AM_LEV1        SIGNALSTR_45DB    
#define SIGNALSTR_AM_LEV2        SIGNALSTR_55DB


#define TUNER_MASK_PRIMARY        0x00
#define TUNER_MASK_SECONDARY        0x60


//
#define REG_STATUS    0x00
#define REG_LEVEL    0x01
#define REG_USN        0x02
#define REG_WAM    0x03    
#define REG_FOF        0x04
#define REG_IFBW    0x05
#define REG_MOD    0x06
#define REG_VER         0x13


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

EXTERN uint8_t Tuner_Dirana_Reset(void);
EXTERN uint8_t Tuner_Dirana_InitBoot(void);
EXTERN uint8_t Tuner_Dirana_InitRds(void);
EXTERN uint8_t Dirana_SetBand(void);
EXTERN uint8_t Dirana_SetFreq(uint16_t Freq);
EXTERN uint8_t Dirana_ConfigMode(uint8_t Mode);
EXTERN uint8_t Dirana_CheckStation(uint8_t ChkMode);
EXTERN uint8_t Dirana_SeekNext(uint8_t Mode);
EXTERN uint8_t Dirana_InitialAll(void);
EXTERN uint8_t Dirana_SetAntenna(void);
EXTERN uint8_t Dirana_SendCmd(DIRANA_DRIVER_TYPE_ENUM PID, uint8_t Band, uint16_t Freq, uint8_t Mode);
EXTERN uint8_t Dirana_GetQualVal(void);
EXTERN uint8_t Dirana_SwitchST(uint8_t Mode);
EXTERN uint8_t Dirana_GetSignalStr(void);
EXTERN uint8_t Dirana_GetStereoFlag(void);
EXTERN uint8_t Dirana_GetInfoes(void);
EXTERN uint8_t Dirana_AF_Jump(uint8_t Freq);
EXTERN uint8_t Dirana_SetBw(uint8_t Mode,uint8_t Bw);
EXTERN uint8_t Dirana_GetAfQuality(uint16_t Freq, uint8_t Num);
EXTERN uint8_t Dirana_GetCFQuality(uint8_t Num);
EXTERN uint8_t Dirana_AfSwitch(uint8_t Mode);
EXTERN void Dirana_FetchBlockDat(void);
EXTERN uint8_t Dirana_ResetDecoder(void);



//2 Declare : End
//............................................................................................

#undef EXTERN

#endif//TUNER_DIRANA_H


