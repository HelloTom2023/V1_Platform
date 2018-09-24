/**********************************************************
 * @file        Audio_Public.h
 * @purpose    Public Definitions of Audio
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
#ifndef AUDIO_PUBLIC_H
#define AUDIO_PUBLIC_H

#include "..\config\type.h"
//--------------------------------------------
//3 Audio Related Structs: Start

// Audio Channel Attribute
#pragma pack(1)
typedef struct ach_attri_struct
{
    uint8_t VolState;        // audio channel's private volume attribute: bit0~bit6 volume value, bit7 static or controllable 
    uint8_t MuteState;    // audio channel's private mute state 
    //uint8_t SrcScaler;        //Related Source Scaling Value: -6db ~ +6db    
    // ...more private attribute can be added 
}ACH_ATTRI_STRUCT;

// Mix Req struct
#pragma pack(1)
typedef struct mix_req_struct
{
    uint8_t Src;    //required source
    uint8_t Pos;    //required position
}MIX_REQ_STRUCT;

// Bal&Fad Attribute
#pragma pack(1)
typedef struct bal_fad_preset_struct
{
    uint8_t Bal;        // Bal
    uint8_t Fad;        // Fad
}BF_PRESET_STRUCT;

// Filter Attribute
#pragma pack(1)
typedef struct peak_notch_filter_struct
{
    uint8_t Gain;        // Filter's Gains
    uint8_t CF;        // Filter's Centre Frequency
    uint8_t Q;        // Filter's Quality Factor
}PN_FILTER_STRUCT;

// Filter Attribute
#pragma pack(1)
typedef struct geq_preset_struct
{
    uint16_t CF;        // Filter's CF
    uint8_t Gain;        // Filter's Gain
}GEQ_PRESET_STRUCT;

//Peak/Notch Attribute
#pragma pack(1)
typedef struct pn_attri_struct
{
    uint16_t CF;        // Filter's CF
    int8_t Gain;        // Filter's Gain
    float Q;
}PN_ATTRI_STRUCT;

//Low/High Pass Attribute
#pragma pack(1)
typedef struct lhp_attri_struct
{
    uint16_t CoF;        // Filter's CF
    int8_t Gain;        // Filter's Gain
    float Q;
}LHP_ATTRI_STRUCT;

// Low Pass Filter Attribute
#pragma pack(1)
typedef struct lhp_filter_struct
{
    uint8_t Gain;        // Filter's Gains
    uint8_t CoF;        // Filter's Cut off Frequency
    uint8_t Q;        // Filter's Quality Factor
}LHP_FILTER_STRUCT;

//Subwoofer
#pragma pack(1)
typedef struct subwoofer_attri_struct
{
   // uint8_t Setting;    // Setting : On or Off
    uint8_t CoF;        //CutOff Frequency    
    uint8_t Level;    // Subwoofer Gain
    uint8_t Slope;    
}SW_ATTRI_STRUCT;

//Xover
#pragma pack(1)
typedef struct xover_attri_struct
{
    uint8_t Level;    // Gain
    uint8_t CoF;        //CutOff Frequency
    uint8_t Slope;    
}XOVER_ATTRI_STRUCT;

// Loudness Attribute
#pragma pack(1)
typedef struct loudness_attri_struct
{
   // uint8_t Setting;        // Setting : On or Off
    uint8_t BassCutOff;    // Bass Cut off Frequency
    uint8_t TrebleCentre;    //Treble Centre frequency
}LOUDNESS_ATTRI_STRUCT;

//Mute Buffer
#pragma pack(1)
typedef struct mute_buffer_struct
{
    uint8_t MuteType;    //Mute Type: Soft/Hard Mute/Unmute
    uint8_t AchId;
    uint8_t SysType;
}MUTE_BUFFER_STRUCT;

//ACH Switch Require
#pragma pack(1)
typedef struct ach_req_buffer
{
    uint8_t Req;        //Required Ach
    uint8_t Type;        //Required Type
}ACH_BUFFER_STRUCT;

//Beep Attribute Struct
#pragma pack(1)
typedef struct beep_struct
{
    uint8_t Type;        //Beep Type: also the priority
    //uint8_t Repetition;    //Beep Repetition
    //uint8_t Vol;            // Beep Vol
    // ...more private attribute can be added 
}BEEP_STRUCT;

//UltraBass Attribute Struct
#pragma pack(1)
typedef struct ultra_bass_struct
{
    uint8_t Setting;    //ON,Off Setting
    uint8_t BoostLevel;    // Max Enhancement Gain
}ULTRA_BASS_STRUCT;

//3 Audio Related Structs: End
//--------------------------------------------



//--------------------------------------------
//3 Audio Related Def&Enum: Start

//Bass Centre Frequency
typedef enum bass_cf_enum
{
    BASS_CF_60 = 0,
    BASS_CF_80,
    BASS_CF_100,
    BASS_CF_200,
}BASS_CF_ENUM;

//Mid Centre Frequency
typedef enum mid_cf_enum
{
    MID_CF_500 = 0,
    MID_CF_800,
    MID_CF_1000,
    MID_CF_1500,
}MID_CF_ENUM;

//Treble Centre Frequency
typedef enum treble_cf_enum
{
    TREBLE_CF_10K = 0,
    TREBLE_CF_12_5K,
    TREBLE_CF_15K,
    TREBLE_CF_17_5K,
}TREBLE_CF_ENUM;

//Q Enum
typedef enum filter_q_enum
{
    Q_0P7 = 0,
    Q_1P0,
    Q_1P5,
}Q_ENUM;

// DC Filter 
typedef enum dc_filter_enum
{
    DC_OFF = 0,
    DC_ON,
}DC_FILTER_ENUM;

//Audio Sample Rate
#define ASF_44K    (44100.0)
#define ASF_48K    (48000.0)

#define ASR_SET_44  0
#define ASR_SET_48  1
#define ASR_SETTING     ASR_SET_44  

#if (ASR_SET_48 == ASR_SETTING)
#define ASRate  ASF_48K  
#else
#define ASRate  ASF_44K  
#endif

//Phase Shifter
#define PHASE_SHIFT_ON        0x01
#define PHASE_SHIFT_OFF        0x00

//Audio Channel Mode
#define AUDIO_2CH_MODE    0 // 2 Stereo Channel Mode
#define AUDIO_6CH_MODE    1 // 5.1 Channel Mode

// 4.2 Type
#define OUT_SW_STEREO     0
#define OUT_SW_CENTER   1

//Speaker Channel Define
#define CHANNEL_FL        0
#define CHANNEL_FR        1
#define CHANNEL_RL        2
#define CHANNEL_RR        3
#define CHANNEL_SWL    4
#define CHANNEL_SWR    5

//Equalizer Band
#define EQ_BAND_1    0
#define EQ_BAND_2    1
#define EQ_BAND_3    2
#define EQ_BAND_4    3
#define EQ_BAND_5    4
#define EQ_BAND_6    5
#define EQ_BAND_7    6
#define EQ_BAND_8    7
#define EQ_BAND_9    8
#define EQ_BAND_10    9
#define EQ_BAND_11    10
#define EQ_BAND_12    11

// Audio Source Channels : Logic Channel, the Priority is from high to low 
typedef enum audio_channel_enum
{
    ACH_AV_OFF = 0,
    ACH_BT_CALL,        // BT Incoming Call 
    ACH_CAM,
    ACH_TA,                // Abrupt TA Playback
    ACH_NAVI_AUDIO,
    //4--------------------------------------
    ACH_SOURCE,        // Source ACH Start,No priority difference ,below this 
    //4--------------------------------------
    ACH_MAX,
}AUDIO_CHANNEL_ENUM;

#define AUDIO_ASP_HERO      0x11
#define AUDIO_ASP_DIRANA   0x22
#define AUDIO_ASP_NULL       0x5A

//AD Type
#define AD_IN_DIF_2V    0
#define AD_IN_DIF_1V    1
#define AD_IN_HCM_2V    2
#define AD_IN_HCM_1V    3
#define AD_IN_HCM_P5V    4
#define AD_IN_IPOD        5

//I2S Type
#define I2S_IN_PHILIP    0
#define I2S_IN_LSB_16    1
#define I2S_IN_LSB_18    2
#define I2S_IN_LSB_20    3
#define I2S_IN_LSB_24    4
#define I2S_IN_OFF        5


//3 Audio Related Def&Enum: End
//--------------------------------------------


//--------------------------------------------
//4 Beep Defs: Start

#define BEEP_BUFFER_MAX 10

//Beep Setup Mask
#define BEEP_MASK_VOL     0x01
#define BEEP_MASK_POS    0x02
#define BEEP_MASK_RECONFIG    0x04    //Reconfig Flag

//Beep Volume
#define BEEP_VOL_MAX 40
#define BEEP_VOL  30
#define BEEP_VOL_LOW    25
#define BEEP_VOL_MID    30
#define BEEP_VOL_HIGH    35

typedef enum beep_vol_set
{
    BEEP_VOL_SET_LOW = 0,
    BEEP_VOL_SET_MID,
    BEEP_VOL_SET_HIGH,    
    BEEP_VOL_SET_MAX,
}BEEP_VOL_SET_ENUM;

typedef enum beep_type_set
{
    BEEP_TYPE_SET_OFF = 0, // Beep Off
    BEEP_TYPE_SET_LOW,
    BEEP_TYPE_SET_HIGH,
    BEEP_TYPE_SET_MAX,
}BEEP_TYPE_SET_ENUM;

#define BEEP_DEFAULT_TYPE		BEEP_TYPE_SET_LOW
//Beep Type
typedef enum audio_beep_type
{
    // MultiMedia Beep Type
    BEEP_TYPE_ORDINARY = 0,        // Ordinary Beep 
    BEEP_TYPE_KEY_ACK,        //Key Pressed Beep
    BEEP_TYPE_KEY_NCK,        //Key Pressed Beep
    BEEP_TYPE_TYRE_ALERT,

    //Car Body Beep Type
    BEEP_TYPE_VALID_KEY,        // Short Beeping for Valid Special Original Key
    BEEP_TYPE_INVALID_KEY,    // Long Beeping for Invalid Special Original Key
    BEEP_TYPE_ALERT,
    BEEP_TYPE_SEATBELT,
    BEEP_TYPE_CRUISE,
    BEEP_TYPE_CONFIRMATION,
    BEEP_TYPE_IGNITION,
    BEEP_TYPE_USER,
    BEEP_TYPE_NULL = 0xFF,
}BEEP_TYPE_ENUM;

//Beep Repetition Type
typedef enum beep_repetition_type
{
    BEEP_RPT_NULL = 0,    //Signs to switch off specific beep
    BEEP_RPT_ONCE,
    BEEP_RPT_NUMERABLE,    //6 times for some vehicle's fasten seat belt warning...
    BEEP_RPT_CONTINUOUS,
}BEEP_RPT_ENUM;

//Beep Switch
typedef enum beep_switch_enum
{
    BEEP_OFF = 0,
    BEEP_ON,
}BEEP_SWITCH_ENUM;

//4 Beep Defs: End!
//--------------------------------------------


//--------------------------------------------
//4 Tone Defs: Start

//Bass Set Step
typedef enum bass_step_enum
{
    BASS_CTL_CALC = 0,    // Calc newly bass 
    BASS_CTL_SET,        // Set newly Bass
    BASS_CTL_SCALER,    //Update Pre-Scaler
    BASS_CTL_END,
}BASS_STEP_ENUM;

//Middle Set Step
typedef enum mid_step_enum
{
    MID_CTL_CALC = 0,    // Calc newly Middle 
    MID_CTL_SET,        // Set newly Middle
    MID_CTL_SCALER,    //Update Pre-Middle
    MID_CTL_END,
}MID_STEP_ENUM;

//Treble Set Step
typedef enum treble_step_enum
{
    TREBLE_CTL_CALC = 0,    // Calc newly Treble 
    TREBLE_CTL_SET,        // Set newly Treble
    TREBLE_CTL_SCALER,    //Update Pre-Scaler
    TREBLE_CTL_END,
}TREBLE_STEP_ENUM;

//4 Tone Defs: End!
//--------------------------------------------


//--------------------------------------------
//4 Bal&Fad  Defs: Start

//Bal&Fad Preset Mode...
#define BF_PRESET_MIDDLE    0    //Middle In the Car
#define BF_PRESET_FL        1    //Front Left Seat
#define BF_PRESET_FR        2    //Front Right Seat
#define BF_PRESET_RL        3    //Rear Left  Seat
#define BF_PRESET_RR        4    //Rear Right Seat
#define BF_PRESET_CUSTOM    5    //Custom Defined...
#define BF_PRESET_MAX        (BF_PRESET_CUSTOM)

//Control Step
#define BF_CTL_BAL_LR    0
#define BF_CTL_BAL_SW    1
#define BF_CTL_FAD_FR    2
#define BF_CTL_FAD_SW    3

//Mask Bit
#define BF_MASK_BAL        0x01
#define BF_MASK_FAD        0x02

//4 Bal&Fad Defs: End!
//--------------------------------------------


//--------------------------------------------
//4 Mix Defs: Start!

//Mix Position..
typedef enum mix_pos_enum
{
    P_MIX_NAV_FL = 0,    // Primary mix with Nav FL
    P_MIX_NAV_FR,
    P_MIX_NAV_RL,
    P_MIX_NAV_RR,
    P_MIX_NAV_FRONT,
    P_MIX_NAV_REAR,
    P_MIX_NAV_ALL,
    P_MIX_PHONE_FL,    // Primary mix with Phone FL
    P_MIX_PHONE_FR,
    P_MIX_PHONE_RL,
    P_MIX_PHONE_RR,
    P_MIX_PHONE_FRONT,
    P_MIX_PHONE_REAR,
    P_MIX_PHONE_ALL,
    P_MIX_CHIME_FL,    // Chime FL mix to Primary
    P_MIX_CHIME_FR,
    P_MIX_CHIME_RL,
    P_MIX_CHIME_RR,
    P_MIX_CHIME_FRONT,
    P_MIX_CHIME_REAR,
    P_MIX_CHIME_ALL,
    P_MIX_EXT_FL,
    P_MIX_EXT_FR,
    P_MIX_EXT_FRONT,
    P_MIX_EXT_ALL,
    S_MIX_CHIME_LEFT,    // Chime Front mix to Secondary
    S_MIX_CHIME_RIGHT,
    S_MIX_CHIME_ALL,
}MIX_POS_ENUM;

//audio mix type
typedef enum mix_type_enum
{
    MIX_TYPE_OFF = 0,
    MIX_TYPE_FL,
    MIX_TYPE_FR,
    MIX_TYPE_FRONT,
    MIX_TYPE_RL,
    MIX_TYPE_RR,
    MIX_TYPE_REAR,
    MIX_TYPE_ALL,
    MIX_TYPE_MAX,
}MIX_TYPE_ENUM;

//Mix Level: System Volume Attenuation
#define MIX_ATTN_SET_OFF     0    //Seams Mix Off, Switch to the System Audio Channel Directly    
#define MIX_ATTN_SET_LOW     1
#define MIX_ATTN_SET_MID     2
#define MIX_ATTN_SET_HIGH     3
#define MIX_ATTN_SET_MAX       MIX_ATTN_SET_HIGH 

//Mix Attn Value(System Volume Attenuation to...)
#define MIX_ATTN_LOW    12
#define MIX_ATTN_MID    16
#define MIX_ATTN_HIGH    20

//Delta from Primary Channel Vol to Navi Channel Vol(Phone Channel Vol) 
#define CHANNEL_VOL_DELTA    1    

//Mix Status
#define MIX_STATUS_OFF         0x00
#define MIX_STATUS_NAVI    0x01
#define MIX_STATUS_BT        0x02

#define NAVI_MODE_SRC   0       //Navi As a Source
#define NAVI_MODE_MIX   1      //Navi just as a audio source  and mix to currently audio channel 
#define NAVI_MODE_INSERT    2    //Navi just as a audio source and insert when valid
#define NAVI_MODE_MAX       NAVI_MODE_INSERT

//4 Mix Defs: End!
//--------------------------------------------


//--------------------------------------------
//4 Delay Line Defs: Start

#define DELAY_LINE_FL    0    //Front Left Speaker
#define DELAY_LINE_FR    1    
#define DELAY_LINE_RL    2
#define DELAY_LINE_RR    3
#define DELAY_LINE_SWL    4
#define DELAY_LINE_SWR    5    
#define DELAY_LINE_AL    6    //Additional Left
#define DELAY_LINE_AR    7    //Additional Right
#define DELAY_LINE_MAX    (DELAY_LINE_SWR + 1)    

#define DELAY_MAX_TIME    392    //39.2ms

#define DELAY_MASK_FL        0x01
#define DELAY_MASK_FR        0x02
#define DELAY_MASK_RL        0x04
#define DELAY_MASK_RR        0x08
#define DELAY_MASK_SWL        0x10
#define DELAY_MASK_SWR    0x20
#define DELAY_MASK_AL        0x40
#define DELAY_MASK_AR        0x80

//Delay Preset
#define DELAY_PRESET_FLAT        0    //Delay Line Off
#define DELAY_PRESET_FL        1    //Temporary Defs
#define DELAY_PRESET_FR        2
#define DELAY_PRESET_RL        3
#define DELAY_PRESET_RR        4
#define DELAY_PRESET_CUSTOM    5
#define DELAY_PRESET_MAX    DELAY_PRESET_CUSTOM

//Car Style
#define CAR_STYLE_SMALL    0
#define CAR_STYLE_MIDDLE    1
#define CAR_STYLE_BIG        2
#define CAR_STYLE_MAX        (CAR_STYLE_BIG + 1)

#define PRESET_VAL_MAX  100


//Speaker Position of Small Car:Length
#define S_LEN_FL2FL      50     //Length of Small Car Front Left speaker to Front Left Seat
#define S_LEN_FR2FL     175
#define S_LEN_RL2FL     150
#define S_LEN_RR2FL     225
#define S_LEN_SWL2FL
#define S_LEN_SWR2FL

#define S_LEN_FL2FR     175
#define S_LEN_FR2FR     50
#define S_LEN_RL2FR     225
#define S_LEN_RR2FR    150
#define S_LEN_SWL2FR
#define S_LEN_SWR2FR

#define S_LEN_FL2RL         150
#define S_LEN_FR2RL         225
#define S_LEN_RL2RL         50
#define S_LEN_RR2RL         175
#define S_LEN_SWL2RL
#define S_LEN_SWR2RL

#define S_LEN_FL2RR         225
#define S_LEN_FR2RR         150
#define S_LEN_RL2RR         175
#define S_LEN_RR2RR         50
#define S_LEN_SWL2RR
#define S_LEN_SWR2RR

//Speaker Delay Setting of Small Car
#define S_FL_FL       (uint8_t)(((S_LEN_RR2FL - S_LEN_FL2FL) * 100) / 343) 
#define S_FL_FR       (uint8_t)(((S_LEN_RR2FL - S_LEN_FR2FL) * 100) / 343)  
#define S_FL_RL        (uint8_t)(((S_LEN_RR2FL - S_LEN_RL2FL) * 100) / 343) 
#define S_FL_RR        (uint8_t)(((S_LEN_RR2FL - S_LEN_RR2FL) * 100) / 343) 
#define S_FL_SWL       0
#define S_FL_SWR       0

#define S_FR_FL       (uint8_t)(((S_LEN_RL2FR - S_LEN_FL2FR) * 100) / 343) 
#define S_FR_FR       (uint8_t)(((S_LEN_RL2FR - S_LEN_FR2FR) * 100) / 343)  
#define S_FR_RL        (uint8_t)(((S_LEN_RL2FR - S_LEN_RL2FR) * 100) / 343) 
#define S_FR_RR        (uint8_t)(((S_LEN_RL2FR - S_LEN_RR2FR) * 100) / 343) 
#define S_FR_SWL       0
#define S_FR_SWR       0

#define S_RL_FL       (uint8_t)(((S_LEN_FR2RL - S_LEN_FL2RL) * 100) / 343) 
#define S_RL_FR       (uint8_t)(((S_LEN_FR2RL - S_LEN_FR2RL) * 100) / 343)  
#define S_RL_RL        (uint8_t)(((S_LEN_FR2RL - S_LEN_RL2RL) * 100) / 343) 
#define S_RL_RR        (uint8_t)(((S_LEN_FR2RL - S_LEN_RR2RL) * 100) / 343) 
#define S_RL_SWL       0
#define S_RL_SWR       0

#define S_RR_FL       (uint8_t)(((S_LEN_FL2RR - S_LEN_FL2RR) * 100) / 343) 
#define S_RR_FR       (uint8_t)(((S_LEN_FL2RR - S_LEN_FR2RR) * 100) / 343)  
#define S_RR_RL        (uint8_t)(((S_LEN_FL2RR - S_LEN_RL2RR) * 100) / 343) 
#define S_RR_RR        (uint8_t)(((S_LEN_FL2RR - S_LEN_RR2RR) * 100) / 343) 
#define S_RR_SWL       0
#define S_RR_SWR       0

//Speaker Position of Middle Car:Length
#define M_LEN_FL2FL      50     //Length of Middle Car Front Left speaker to Front Left Seat
#define M_LEN_FR2FL     175
#define M_LEN_RL2FL     150
#define M_LEN_RR2FL     225
#define M_LEN_SWL2FL
#define M_LEN_SWR2FL

#define M_LEN_FL2FR     175
#define M_LEN_FR2FR     50
#define M_LEN_RL2FR     225
#define M_LEN_RR2FR    150
#define M_LEN_SWL2FR
#define M_LEN_SWR2FR

#define M_LEN_FL2RL         150
#define M_LEN_FR2RL         225
#define M_LEN_RL2RL         50
#define M_LEN_RR2RL         175
#define M_LEN_SWL2RL
#define M_LEN_SWR2RL

#define M_LEN_FL2RR         225
#define M_LEN_FR2RR         150
#define M_LEN_RL2RR         175
#define M_LEN_RR2RR         50
#define M_LEN_SWL2RR
#define M_LEN_SWR2RR

//Speaker Delay Setting of Middle Car
#define M_FL_FL       (uint8_t)(((M_LEN_RR2FL - M_LEN_FL2FL) * 100) / 343) 
#define M_FL_FR       (uint8_t)(((M_LEN_RR2FL - M_LEN_FR2FL) * 100) / 343)  
#define M_FL_RL        (uint8_t)(((M_LEN_RR2FL - M_LEN_RL2FL) * 100) / 343) 
#define M_FL_RR        (uint8_t)(((M_LEN_RR2FL - M_LEN_RR2FL) * 100) / 343) 
#define M_FL_SWL       0
#define M_FL_SWR       0

#define M_FR_FL       (uint8_t)(((M_LEN_RL2FR - M_LEN_FL2FR) * 100) / 343) 
#define M_FR_FR       (uint8_t)(((M_LEN_RL2FR - M_LEN_FR2FR) * 100) / 343)  
#define M_FR_RL        (uint8_t)(((M_LEN_RL2FR - M_LEN_RL2FR) * 100) / 343) 
#define M_FR_RR        (uint8_t)(((M_LEN_RL2FR - M_LEN_RR2FR) * 100) / 343) 
#define M_FR_SWL       0
#define M_FR_SWR       0

#define M_RL_FL       (uint8_t)(((M_LEN_FR2RL - M_LEN_FL2RL) * 100) / 343) 
#define M_RL_FR       (uint8_t)(((M_LEN_FR2RL - M_LEN_FR2RL) * 100) / 343)  
#define M_RL_RL        (uint8_t)(((M_LEN_FR2RL - M_LEN_RL2RL) * 100) / 343) 
#define M_RL_RR        (uint8_t)(((M_LEN_FR2RL - M_LEN_RR2RL) * 100) / 343) 
#define M_RL_SWL       0
#define M_RL_SWR       0

#define M_RR_FL       (uint8_t)(((M_LEN_FL2RR - M_LEN_FL2RR) * 100) / 343) 
#define M_RR_FR       (uint8_t)(((M_LEN_FL2RR - M_LEN_FR2RR) * 100) / 343)  
#define M_RR_RL        (uint8_t)(((M_LEN_FL2RR - M_LEN_RL2RR) * 100) / 343) 
#define M_RR_RR        (uint8_t)(((M_LEN_FL2RR - M_LEN_RR2RR) * 100) / 343) 
#define M_RR_SWL       0
#define M_RR_SWR       0

//Speaker Position of Large Car:Length
#define L_LEN_FL2FL      50     //Length of Small Car Front Left speaker to Front Left Seat
#define L_LEN_FR2FL     175
#define L_LEN_RL2FL     150
#define L_LEN_RR2FL     225
#define L_LEN_SWL2FL
#define L_LEN_SWR2FL

#define L_LEN_FL2FR     175
#define L_LEN_FR2FR     50
#define L_LEN_RL2FR     225
#define L_LEN_RR2FR    150
#define L_LEN_SWL2FR
#define L_LEN_SWR2FR

#define L_LEN_FL2RL         150
#define L_LEN_FR2RL         225
#define L_LEN_RL2RL         50
#define L_LEN_RR2RL         175
#define L_LEN_SWL2RL
#define L_LEN_SWR2RL

#define L_LEN_FL2RR         225
#define L_LEN_FR2RR         150
#define L_LEN_RL2RR         175
#define L_LEN_RR2RR         50
#define L_LEN_SWL2RR
#define L_LEN_SWR2RR

//Speaker Delay Setting
#define L_FL_FL       (uint8_t)(((L_LEN_RR2FL - L_LEN_FL2FL) * 100) / 343) 
#define L_FL_FR       (uint8_t)(((L_LEN_RR2FL - L_LEN_FR2FL) * 100) / 343)  
#define L_FL_RL        (uint8_t)(((L_LEN_RR2FL - L_LEN_RL2FL) * 100) / 343) 
#define L_FL_RR        (uint8_t)(((L_LEN_RR2FL - L_LEN_RR2FL) * 100) / 343) 
#define L_FL_SWL       0
#define L_FL_SWR       0

#define L_FR_FL       (uint8_t)(((L_LEN_RL2FR - L_LEN_FL2FR) * 100) / 343) 
#define L_FR_FR       (uint8_t)(((L_LEN_RL2FR - L_LEN_FR2FR) * 100) / 343)  
#define L_FR_RL        (uint8_t)(((L_LEN_RL2FR - L_LEN_RL2FR) * 100) / 343) 
#define L_FR_RR        (uint8_t)(((L_LEN_RL2FR - L_LEN_RR2FR) * 100) / 343) 
#define L_FR_SWL       0
#define L_FR_SWR       0

#define L_RL_FL       (uint8_t)(((L_LEN_FR2RL - L_LEN_FL2RL) * 100) / 343) 
#define L_RL_FR       (uint8_t)(((L_LEN_FR2RL - L_LEN_FR2RL) * 100) / 343)  
#define L_RL_RL        (uint8_t)(((L_LEN_FR2RL - L_LEN_RL2RL) * 100) / 343) 
#define L_RL_RR        (uint8_t)(((L_LEN_FR2RL - L_LEN_RR2RL) * 100) / 343) 
#define L_RL_SWL       0
#define L_RL_SWR       0

#define L_RR_FL       (uint8_t)(((L_LEN_FL2RR - L_LEN_FL2RR) * 100) / 343) 
#define L_RR_FR       (uint8_t)(((L_LEN_FL2RR - L_LEN_FR2RR) * 100) / 343)  
#define L_RR_RL        (uint8_t)(((L_LEN_FL2RR - L_LEN_RL2RR) * 100) / 343) 
#define L_RR_RR        (uint8_t)(((L_LEN_FL2RR - L_LEN_RR2RR) * 100) / 343) 
#define L_RR_SWL       0
#define L_RR_SWR       0




//4 Delay LIne Defs: End!
//--------------------------------------------

//--------------------------------------------
//4 Graphic Equalizer Defs: Start

//G-EQ Definition
#define GEQ_MAX_NUM 9       //5    //Max Band Number

#define GEQ_MODE_STANDARD         0
#define GEQ_MODE_POP                   1
#define GEQ_MODE_ROCK                 2
#define GEQ_MODE_JAZZ                   3
#define GEQ_MODE_CLASSICL           4    
#define GEQ_MODE_SPEECH             5   
#define GEQ_MODE_CUSTOM             6   
#define GEQ_MODE_MAX        GEQ_MODE_CUSTOM

//Graphic Equalizer Update Step
typedef enum geq_step_enum
{
    GEQ_INIT = 0,
    GEQ_ENABLE_ADD4,    //Enable Additional 4 Band    
    GEQ_BAND1_CALC,
    GEQ_BAND1_SET,
    GEQ_BAND2_CALC,
    GEQ_BAND2_SET,
    GEQ_BAND3_CALC,
    GEQ_BAND3_SET,
    GEQ_BAND4_CALC,
    GEQ_BAND4_SET,
    GEQ_BAND5_CALC,
    GEQ_BAND5_SET,
    GEQ_BAND6_CALC,
    GEQ_BAND6_SET,
    GEQ_BAND7_CALC,
    GEQ_BAND7_SET,
    GEQ_BAND8_CALC,
    GEQ_BAND8_SET,
    GEQ_BAND9_CALC,
    GEQ_BAND9_SET,
    GEQ_BAND_END,      //Dynamic Update Pre-Scaler
}GEQ_STEP_ENUM;

//GEQ Mask Bit
#define GEQ_MASK_INIT            0x0001
#define GEQ_MASK_BAND1        0x0002
#define GEQ_MASK_BAND2        0x0004
#define GEQ_MASK_BAND3        0x0008
#define GEQ_MASK_BAND4        0x0010
#define GEQ_MASK_BAND5        0x0020
#define GEQ_MASK_BAND6        0x0040
#define GEQ_MASK_BAND7        0x0080
#define GEQ_MASK_BAND8        0x0100
#define GEQ_MASK_BAND9        0x0200

//4 Graphic Equalizer Defs: End
//--------------------------------------------


//--------------------------------------------
//4 Loudness Defs: Start

//Loudness Update Step
typedef enum loudness_step_enum
{
    LOUD_CTL_INIT = 0,
    LOUD_CTL_CONFIG,    
    LOUD_CTL_ON_OFF,
    LOUD_CTL_OFF_BASS,
    LOUD_CTL_OFF_TREBLE,
    LOUD_CTL_BASS_COF,
    LOUD_CTL_TREBLE_CF,
    LOUD_CTL_END,    
}LOUDNESS_STEP_ENUM;

#define LOUD_MASK_INIT            0x01    //Initialize Loudness
#define LOUD_MASK_ON_OFF        0x02    //     
#define LOUD_MASK_BASS_COF    0x04    //Bass Cut off frequency
#define LOUD_MASK_TREBLE_CF    0x08    //Treble Centre Frequency

#define AUDIO_LOUD_B_COF_MAX        2            
#define AUDIO_LOUD_B_BST_MAX        12        
#define AUDIO_LOUD_T_CF_MAX        2
#define AUDIO_LOUD_T_BST_MAX        4    

//Bass Cut-Off Frequency
typedef enum ld_bass_cof_enum
{
    LDB_COF_50 = 0,
    LDB_COF_200,
}LDB_COF_ENUM;

//Treble Centre Frequency
typedef enum ld_treble_cf_enum
{
    LDT_CF_7K = 0,
    LDT_CF_10K,
}LDT_CF_ENUM;

//4 Loudness Defs: End!
//--------------------------------------------


//------------------------------------------------
//4 Source Scaling :Start

//Scaling Source
typedef enum scaling_src_enum
{
    SS_SRC_TUNER = 0,
    SS_SRC_DISC,
    SS_SRC_CDBOX,
    SS_SRC_TV,
    SS_SRC_NAVI,
    SS_SRC_R_AUX,
    SS_SRC_DTV,
    SS_SRC_SD,
    SS_SRC_XM,
    SS_SRC_IPOD,
    SS_SRC_USB,
    SS_SRC_DAB,
    SS_SRC_F_AUX,
    SS_SRC_BT_PHONE,
    SS_SRC_SIRIUS,
    SS_SRC_HD_RADIO,
    SS_SRC_INTERNET,
    SS_SRC_BT_MUSIC,
    SS_SRC_MIRRORLINK,
    SS_SRC_THIRD_APP,
    SS_SRC_MAX,
}SCALING_SOURCE_ENUM;

#define SRC_SCALER_MAX      12

//4 Source Scaling :End!
//------------------------------------------------


//------------------------------------------------
//4 SubWoofer :Start!

//Subwoofer Update Step
typedef enum subwoofer_step_enum
{
    SW_CTL_CREATE = 0,    //Config: Create SubWoofer
    SW_CTL_INIT,
    SW_CTL_CALC,
    SW_CTL_SET,
    SW_CTL_CNNT_SWL,    
    SW_CTL_CALC_SWL_1,
    SW_CTL_CALC_SWL_2,
    SW_CTL_SET_SWL_1,
    SW_CTL_SET_SWL_2,
    SW_CTL_CNNT_SWR,
    SW_CTL_CALC_SWR_1,
    SW_CTL_CALC_SWR_2,
    SW_CTL_SET_SWR_1,
    SW_CTL_SET_SWR_2,
    SW_CTL_END,    
}SUBWOOFER_STEP_ENUM;

//Subwoofer Cut-Off Frequency
typedef enum subwoofer_cof_enum
{
    SW_FLAT = 0,
    SW_COF_55,    
    SW_COF_85,
    SW_COF_120,
    SW_COF_160,
}SW_COF_ENUM;

//Mask Bit Def
#define SW_MASK_CREATE 0x01     
#define SW_MASK_INIT    0x01
#define SW_MASK_SWL    0x02
#define SW_MASK_SWR    0x04

#define AUDIO_SW_COF_MAX        4            
#define AUDIO_SW_GAIN_MAX        12        
#define AUDIO_SW_Q_MAX        2

#define SUBWOOFER_OFF    0x00
#define SUBWOOFER_ON    0x01

//4Subwoofer :End!
//------------------------------------------------


//------------------------------------------------
//4 X Cross :Start!

//Xover's Channel
#define CO_CH_F_HPF      0//X Over Channel: Front HPF
#define CO_CH_R_HPF    1//X Over Channel: Rear HPF
#define CO_CH_SW_LPF    2//X Over Channel: Subwoofer LPF

//Xover Preset
#define XOVER_PRESET_FLAT    0
#define XOVER_PRESET_1        1
#define XOVER_PRESET_2        2
#define XOVER_PRESET_3        3
#define XOVER_PRESET_CUSTOM    4
#define XOVER_PRESET_MAX        XOVER_PRESET_CUSTOM

//X-Over Slope   对应滤波器的阶数
#define XOVER_SLOPE_FLAT    0
#define XOVER_SLOPE_6           1
#define XOVER_SLOPE_12        2
#define XOVER_SLOPE_18        3
#define XOVER_SLOPE_24        4
#define XOVER_SLOPE_MAX     XOVER_SLOPE_24

#define FILTER_FLAT 0
#define FILTER_1ST  1
#define FILTER_2ND  2
#define FILTER_3RD  3
#define FILTER_4TH  4

#define XOVER_LEVEL_0DB     12
#define XOVER_LEVEL_MAX    18

//X-Over Cut-off Frequency
typedef enum xover_cof_enum
{
    XOVER_COF_20 = 0,
    XOVER_COF_25,    
    XOVER_COF_31P5,    
    XOVER_COF_40,
    XOVER_COF_50,
    XOVER_COF_63,
    XOVER_COF_80,
    XOVER_COF_100,
    XOVER_COF_125,
    XOVER_COF_160,
    XOVER_COF_200,
    XOVER_COF_MAX,
}XOVER_COF_ENUM;

//X Over Mask
#define XOVER_MASK_INIT     0x01
#define XOVER_MASK_FRONT     0x02    //
#define XOVER_MASK_REAR     0x04
#define XOVER_MASK_SW         0x08		// 重低音
#define XOVER_MASK_CENTER   0x10       // 中置

//Xover Update Step
typedef enum xover_step_enum
{   
    XOVER_CTL_DELAY = 0,
    XOVER_CTL_MUTE,
    XOVER_CTL_INIT_F_R,    //Initilize 
    XOVER_CTL_CALC_FRONT1,  
    XOVER_CTL_SET_FRONT1,
    XOVER_CTL_SET_FRONT1_LEFT,
    XOVER_CTL_SET_FRONT1_LEFT_REAR,
    XOVER_CTL_SET_FRONT1_RIGHT_REAR,
    XOVER_CTL_SET_FRONT1_RIGHT,
    XOVER_CTL_CALC_FRONT2,  //For filters cascaded by 2nd order filters
    XOVER_CTL_SET_FRONT2,
    XOVER_CTL_SET_FRONT2_LEFT,
    XOVER_CTL_SET_FRONT2_RIGHT,
    XOVER_CTL_CALC_REAR1,
    XOVER_CTL_SET_REAR1,
    XOVER_CTL_SET_REAR1_LEFT,
    XOVER_CTL_SET_REAR1_LEFT_REAR,
    XOVER_CTL_SET_REAR1_RIGHT_REAR,
    XOVER_CTL_SET_REAR1_RIGHT,
    XOVER_CTL_CALC_REAR2,
    XOVER_CTL_SET_REAR2,
    XOVER_CTL_SET_REAR2_LEFT,
    XOVER_CTL_SET_REAR2_RIGHT,
    XOVER_CTL_INIT_SWL,
    XOVER_CTL_CALC_SWL1,
    XOVER_CTL_SET_SWL1,
    XOVER_CTL_CALC_SWL2,
    XOVER_CTL_SET_SWL2,
    XOVER_CTL_INIT_SWR,
    XOVER_CTL_CALC_SWR1,
    XOVER_CTL_SET_SWR1,
    XOVER_CTL_CALC_SWR2,
    XOVER_CTL_SET_SWR2, 
    XOVER_CTL_DEMUTE,
    XOVER_CTL_END,    
}XOVER_STEP_ENUM;


//4 X Cross :End!
//------------------------------------------------


//------------------------------------------------
//4  PEQ : Start

#define PEQ_MAX_NUM 11

//Parametric Equalizer Update Step
typedef enum peq_step_enum
{
    //PEQ_INIT = 0,
    PEQ_BAND1_CALC_FL = 0,
    PEQ_BAND1_SET_FL,
    PEQ_BAND1_CALC_FR,
    PEQ_BAND1_SET_FR,
    PEQ_BAND1_CALC_RL,
    PEQ_BAND1_SET_RL,
    PEQ_BAND1_CALC_RR,
    PEQ_BAND1_SET_RR,    
    PEQ_BAND2_CALC_FL,
    PEQ_BAND2_SET_FL,
    PEQ_BAND2_CALC_FR,
    PEQ_BAND2_SET_FR,
    PEQ_BAND2_CALC_RL,
    PEQ_BAND2_SET_RL,
    PEQ_BAND2_CALC_RR,
    PEQ_BAND2_SET_RR,    
    PEQ_BAND3_CALC_FL,
    PEQ_BAND3_SET_FL,
    PEQ_BAND3_CALC_FR,
    PEQ_BAND3_SET_FR,
    PEQ_BAND3_CALC_RL,
    PEQ_BAND3_SET_RL,
    PEQ_BAND3_CALC_RR,
    PEQ_BAND3_SET_RR,    
    PEQ_BAND4_CALC_FL,
    PEQ_BAND4_SET_FL,
    PEQ_BAND4_CALC_FR,
    PEQ_BAND4_SET_FR,
    PEQ_BAND4_CALC_RL,
    PEQ_BAND4_SET_RL,
    PEQ_BAND4_CALC_RR,
    PEQ_BAND4_SET_RR,    
    PEQ_BAND5_CALC_FL,
    PEQ_BAND5_SET_FL,
    PEQ_BAND5_CALC_FR,
    PEQ_BAND5_SET_FR,
    PEQ_BAND5_CALC_RL,
    PEQ_BAND5_SET_RL,
    PEQ_BAND5_CALC_RR,
    PEQ_BAND5_SET_RR,    
    PEQ_BAND6_CALC_FL,
    PEQ_BAND6_SET_FL,
    PEQ_BAND6_CALC_FR,
    PEQ_BAND6_SET_FR,
    PEQ_BAND6_CALC_RL,
    PEQ_BAND6_SET_RL,
    PEQ_BAND6_CALC_RR,
    PEQ_BAND6_SET_RR,    
    PEQ_BAND7_CALC_FL,
    PEQ_BAND7_SET_FL,
    PEQ_BAND7_CALC_FR,
    PEQ_BAND7_SET_FR,
    PEQ_BAND7_CALC_RL,
    PEQ_BAND7_SET_RL,
    PEQ_BAND7_CALC_RR,
    PEQ_BAND7_SET_RR,    
    PEQ_BAND8_CALC_FL,
    PEQ_BAND8_SET_FL,
    PEQ_BAND8_CALC_FR,
    PEQ_BAND8_SET_FR,
    PEQ_BAND8_CALC_RL,
    PEQ_BAND8_SET_RL,
    PEQ_BAND8_CALC_RR,
    PEQ_BAND8_SET_RR,    
    PEQ_BAND9_CALC_FL,
    PEQ_BAND9_SET_FL,
    PEQ_BAND9_CALC_FR,
    PEQ_BAND9_SET_FR,
    PEQ_BAND9_CALC_RL,
    PEQ_BAND9_SET_RL,
    PEQ_BAND9_CALC_RR,
    PEQ_BAND9_SET_RR,    
    PEQ_BAND10_CALC_FL,
    PEQ_BAND10_SET_FL,
    PEQ_BAND10_CALC_FR,
    PEQ_BAND10_SET_FR,
    PEQ_BAND10_CALC_RL,
    PEQ_BAND10_SET_RL,
    PEQ_BAND10_CALC_RR,
    PEQ_BAND10_SET_RR,    
    PEQ_BAND11_CALC_FL,
    PEQ_BAND11_SET_FL,
    PEQ_BAND11_CALC_FR,
    PEQ_BAND11_SET_FR,
    PEQ_BAND11_CALC_RL,
    PEQ_BAND11_SET_RL,
    PEQ_BAND11_CALC_RR,
    PEQ_BAND11_SET_RR,        
    PEQ_BAND_END,    
}PEQ_STEP_ENUM;

#define PEQ_MASK_BAND1        0x0001
#define PEQ_MASK_BAND2        0x0002
#define PEQ_MASK_BAND3        0x0004
#define PEQ_MASK_BAND4        0x0008
#define PEQ_MASK_BAND5        0x0010
#define PEQ_MASK_BAND6        0x0020
#define PEQ_MASK_BAND7        0x0040
#define PEQ_MASK_BAND8        0x0080
#define PEQ_MASK_BAND9        0x0100
#define PEQ_MASK_BAND10        0x0200
#define PEQ_MASK_BAND11        0x0400

#define PEQ_MODE_FLAT         0
#define PEQ_MODE_HALL        1
#define PEQ_MODE_FIELD        2
#define PEQ_MODE_ROOM        3
#define PEQ_MODE_CUSTOM    4    //Usr Defined
#define PEQ_MODE_MAX        PEQ_MODE_CUSTOM

#define PEQ_GAIN_DELTA        12

//4  PEQ : End
//------------------------------------------------


//-----------------------------------------------
//4 Channel Gain: Start

//Channel Gain Control Mask
#define CHANGAIN_MASK_FL        0x0001
#define CHANGAIN_MASK_FR        0x0002
#define CHANGAIN_MASK_RL        0x0004
#define CHANGAIN_MASK_RR        0x0008
#define CHANGAIN_MASK_SWL        0x0010
#define CHANGAIN_MASK_SWR    0x0020
#define CHANGAIN_MASK_SL        0x0040
#define CHANGAIN_MASK_SR        0x0080
#define CHANGAIN_MASK_N        0x0100    //Navigation
#define CHANGAIN_MASK_T        0x0200    //Telephone

//Channel Gain Update Step
typedef enum chan_gain_step_enum
{
    CHANGAIN_CTL_FL = 0,    
    CHANGAIN_CTL_FR,    
    CHANGAIN_CTL_RL,
    CHANGAIN_CTL_RR,
    CHANGAIN_CTL_SWL,
    CHANGAIN_CTL_SWR,
}CHANGAIN_STEP_ENUM;

//4 Channel Gain: End!
//-----------------------------------------------


//-----------------------------------------------
//4 Ultra Bass: Start

#define UBASS_ENABLE 1
#define UBASS_DISABLE 0

//Mask Bit
#define UBASS_MASK_ENABLE    0x01
#define UBASS_MASK_LEVEL    0x02
#define UBASS_MASK_SCALER    0x04

//Control Step
#define UBASS_CTL_ENABLE     0
#define UBASS_CTL_LEVEL     1
#define UBASS_CTL_SCALER     2

#define UBASS_BST_MAX   24

//4Ultra Bass: End!
//-----------------------------------------------

#define VOL_TYPE_SYS         0
#define VOL_TYPE_BT         1
#define VOL_TYPE_NAV         2
#define VOL_TYPE_APP    3

//-----------------------------------------------
//4 Click-Clack :Start

#define CLICKCLACK_ON   1
#define CLICKCLACK_OFF 0

#define CC_CTL_FLAG 0x000001
#define CC_CTL_IIC      0x000000

#define CLICK_DAT   0xFFFFFF
#define CLACK_DAT   0x000001

#define CC_MASK_INIT           0x01    
#define CC_MASK_ENABLE       0x02
#define CC_MASK_DISABLE     0x04

//Click-Clack Control Step
typedef enum click_clack_step_enum
{
    CC_CTL_IDLE = 0,   
    CC_CTL_ENABLE,
    CC_CTL_CLICK,    
    CC_CTL_CLACK,
    CC_CTL_DISABLE,
    CC_CTL_END,
}CLICKCLACK_STEP_ENUM;


//4Click-Clack: End!
//-----------------------------------------------


#endif//AUDIO_PUBLIC_H

