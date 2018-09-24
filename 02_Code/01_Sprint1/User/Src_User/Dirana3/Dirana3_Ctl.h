/**********************************************************
 * @file        Dirana3_Ctl.h
 * @purpose    Definitions of Hero Control
 * @version    0.01
 * @date        24. Aug. 2012
 * @author    Deefisher.Lyu
 * @brief        
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          24.Aug.2012        v0.01        created
 *  
  **********************************************************/
#ifndef DIRANA3_CTL_H
#define DIRANA3_CTL_H

#ifdef DIRANA3_CTL_C
#define EXTERN
#else
#define EXTERN extern 
#endif//DIRANA3_CTL_C

//Dirana3 Boot Mode Selection..
#define DIRANA_BOOT_FROM_ROM    0
#define DIRANA_BOOT_FROM_FLASH    1
#define DIRANA_BOOT_FROM_VIP        2

#define DIRANA_BOOT_MODE DIRANA_BOOT_FROM_FLASH

//............................................................................................
//4 Dirana3 Control Step Definitions : Start

// Dirana Reset Step
typedef enum dirana_reset_step_enum
{
    DIRANA_RESET_CONFIG = 0,    //Config Reset Pin
    DIRANA_RESET_ACTIVE,         // Set to RESET
    DIRANA_RESET_DEACTIVE,    // Set to Normal
    DIRANA_RESET_CHK_BUS,    //Check IIC Bus
    DIRANA_RESET_CHK_DEV,    //Check D3 Device
    DIRANA_RESET_END,            // Reset End
}DIRANA_RESET_STEP_ENUM;

// Dirana Init Register
typedef enum dirana_register_step_enum
{
    DIRANA_REGISTER_KEYCODE = 0,        //Load Keycode for enhanced feature
    DIRANA_REGISTER_PATCH,
    DIRANA_REGISTER_IMAGE,    //Load Image for core or load patch
    DIRANA_REGISTER_START_APP,        //Start Application and Detect GPIO4
    DIRANA_REGISTER_REQ_INIT,
    DIRANA_REGISTER_ALIGNMENT,        //AM/WX Alignments
    DIRANA_REGISTER_ADPLL0,    //Start ADPLL0
    DIRANA_REGISTER_ADPLL1,    //Start ADPLL1
    DIRANA_REGISTER_SPECIAL_P,    //Fm whistle avoidance, other i dont know what to do..........
    DIRANA_REGISTER_P_RADIO,    //Init Primary Radio 
    DIRANA_REGISTER_SPECIAL_S,
    DIRANA_REGISTER_S_RADIO,    //Init Secondary Radio
    DIRANA_REGISTER_GPIO,
    DIRANA_REGISTER_SRC,    //Sample Rate Converter
    DIRANA_REGISTER_INIT_AUDIO,
    DIRANA_REGISTER_TEST1,
    DIRANA_REGISTER_TEST2,
    DIRANA_REGISTER_TEST3,
    DIRANA_REGISTER_TEST4,
    DIRANA_REGISTER_TEST5,
    DIRANA_REGISTER_END,
}DIRANA_REGISTER_STEP_ENUM;


//Dirana_InitAudio SubStep
typedef enum dirana_init_audio_enum
{
    DIRANA_AUDIO_SRC,            //Channel Sample Rate Converter
    DIRANA_AUDIO_ASR,
    DIRANA_AUDIO_XOVER,
    DIRANA_AUDIO_CHIME,
    DIRANA_AUDIO_CLICKCLACK,
    DIRANA_AUDIO_GSA,                //Graphic Spectrum Analyzer
    DIRANA_AUDIO_PERIPHERAL,        //Input/Output Peripheral 
    DIRANA_AUDIO_HOST,    //Config Host IIS
    DIRANA_AUDIO_POINTER,    //Audio Pointer Connection
    DIRANA_AUDIO_SCALING,            //Scaling Model
    DIRANA_AUDIO_COM_EXP,        //Compressor/Expander
    DIRANA_AUDIO_GEQ,
    DIRANA_AUDIO_LOUDNESS,
    DIRANA_AUDIO_ULTRA_BASS,    //Ultra Bass
    DIRANA_AUDIO_SOFTCLIPPER,
    DIRANA_AUDIO_DOWNMIXER,
    DIRANA_AUDIO_VOLUME,
    DIRANA_AUDIO_CH_GAIN,
    DIRANA_AUDIO_BALANCE,
    DIRANA_AUDIO_FADER,
    DIRANA_AUDIO_BF,    //Bal&Fad
    DIRANA_AUDIO_TONE,
    DIRANA_AUDIO_BASS,
    DIRANA_AUDIO_MID,
    DIRANA_AUDIO_TREBLE,
    DIRANA_AUDIO_DC_FILTER,
    DIRANA_AUDIO_IBOC,
    DIRANA_AUDIO_DEEMPHASIS,
    DIRANA_AUDIO_SRCSCALER,
    DIRANA_AUDIO_PHASE_SHIFT,
    DIRANA_AUDIO_FASTMUTE,
    DIRANA_AUDIO_DELAYLINE,
    DIRANA_AUDIO_SUBWOOFER,
    DIRANA_AUDIO_LIMITER,
    DIRANA_AUDIO_QPD,
    DIRANA_AUDIO_PHONE_NAV,
    DIRANA_AUDIO_GPFILTER,
    DIRANA_AUDIO_PEQ,
    DIRANA_AUDIO_GPIO,
    DIRANA_AUDIO_END,
}DIRANA_INIT_AUDIO_ENUM;

typedef struct dirana_ach_tab_struct
{
    uint8_t DummyAch;   //Logistic Ach
    uint8_t ActualAch;    // Actual Ach for Front
}DIRANA_ACH_TAB_STRUCT;


//4 Dirana3 Control Step Definitions : End
//............................................................................................

//--------------------------------------------------------------
//3  Declare :Start

EXTERN void Dirana_GotoStep(uint8_t Step);
EXTERN void Dirana_SubGotoStep(uint8_t Step);
EXTERN void Dirana_InitVariable(void);
EXTERN uint8_t Dirana_OpenPower(void);
EXTERN uint8_t Dirana_Reset(void);
EXTERN uint8_t Dirana_Register(void);
EXTERN uint8_t Dirana_Patch(void);
EXTERN uint8_t Dirana_InitAudio(void);
EXTERN uint8_t Dirana_SwitchAch(uint8_t Ach, uint8_t Type);
EXTERN uint8_t Dirana_SetMixSrc(uint8_t Src,uint8_t Type);
EXTERN uint8_t Dirana_ConfigMix(uint8_t Src,uint8_t Type,int8_t Gain);

//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN

#endif//DIRANA3_CTL_H

