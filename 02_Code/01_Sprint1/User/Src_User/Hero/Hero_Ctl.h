/**********************************************************
 * @file        Hero_Ctl.h
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
#ifndef HERO_CTL_H
#define HERO_CTL_H


#ifdef D_AUDIO_ASP_HERO

#ifdef HERO_CTL_C
#define EXTERN
#else
#define EXTERN extern 
#endif//HERO_CTL_C
//............................................................................................
//4 Hero Control Step Definitions : Start

// Hero Reset Step
typedef enum hero_reset_step_enum
{
    HERO_RESET_CONFIG = 0,    //Config Reset Pin
    HERO_RESET_ACTIVE,         // Set to RESET
    HERO_RESET_DEACTIVE,        // Set to Normal
    HERO_RESET_CHK_BUS,
    HERO_RESET_CHK_DEV,
    HERO_RESET_END,            // Reset End
}HERO_RESET_STEP_ENUM;

// Hero Init Register
typedef enum hero_register_step_enum
{
    HERO_REGISTER_RADIO_A = 0,
    HERO_REGISTER_AUDIO_A,
    HERO_REGISTER_RADIO_A2,
    HERO_REGISTER_SPURIOUS_SIGNAL,
    HERO_REGISTER_IIS_VCO,
    HERO_REGISTER_KEYCODE,
    HERO_REGISTER_USECASE,
    HERO_REGISTER_ACTIVE,
    HERO_REGISTER_RADIO_B,
    HERO_REGISTER_AUDIO_B,
    HERO_REGISTER_PERIPHERAL,
    HERO_REGISTER_AUDIO_POINTER,
    
    HERO_REGISTER_GPIO,
    HERO_REGISTER_SOURCE,
    HERO_REGISTER_INIT_AUDIO,
    HERO_REGISTER_INIT_RADIO,
    HERO_REGISTER_AUDIO_C,
    HERO_REGISTER_TEST1,
    HERO_REGISTER_TEST2,
    HERO_REGISTER_TEST3,
    HERO_REGISTER_TEST4,
    HERO_REGISTER_TEST5,
    HERO_REGISTER_END,
}HERO_REGISTER_STEP_ENUM;

//HERO_REGISTER_DAC SubStep
typedef enum hero_dac_step_enum
{
    HERO_DAC_FRONT = 0,
    HERO_DAC_REAR,
    HERO_DAC_END,
}HERO_DAC_STEP_ENUM;

//Hero_InitAudio SubStep
typedef enum hero_init_audio_enum
{
    HERO_AUDIO_SCALING = 0,
    HERO_AUDIO_CHANNEL_GAIN,
    HERO_AUDIO_AUDIO_POINTER,
    HERO_AUDIO_SOFTMUTE,
    HERO_AUDIO_LOUDNESS,
    HERO_AUDIO_VOLUME1,
    HERO_AUDIO_VOLUME2,
    HERO_AUDIO_GSA,
    HERO_AUDIO_BF,
    HERO_AUDIO_TONE,
    HERO_AUDIO_BASS,
    HERO_AUDIO_MID,
    HERO_AUDIO_TREBLE,
    HERO_AUDIO_GEQ,
    HERO_AUDIO_PEQ,
    HERO_AUDIO_DC_FILTER,
    HERO_AUDIO_NAV_PHONE_FILTER,
    HERO_AUDIO_COMP_EXP,    //compressor, expander
    HERO_AUDIO_BEEP,
    HERO_AUDIO_CLICKCLACK,
    HERO_AUDIO_SRCSCALER,
    HERO_AUDIO_PHASE_SHIFT,
    HERO_AUDIO_UBASS,
    HERO_AUDIO_POLYCHIME,
    HERO_AUDIO_DELAY,
    HERO_AUDIO_NAV_VOL,
    HERO_AUDIO_SUBWOOFER,
    HERO_AUDIO_END,
}HERO_INIT_AUDIO_ENUM;

//Easy Programme Step
typedef enum hero_easy_p_enum
{
    HERO_EASYP_CHK = 0,
    HERO_EASYP_WRITE,
    HERO_EASYP_END,
}HERO_EASY_P_ENUM;


#define HERO_ERR_NULL     0
#define HERO_ERR_IIC_START            1
#define HERO_ERR_IIC_QUEUE        2
#define HERO_ERR_3        3


typedef struct hero_ach_tab_struct
{
    uint8_t DummyAch;   //Logistic Ach
    uint8_t ActualAch;    // Actual Ach for Front
}HERO_ACH_TAB_STRUCT;

//4 Hero Control Step Definitions : Start
//............................................................................................


//............................................................................................
//4 Hero Control Definitions : Start


#define Hero_SpecialGotoStep(x,y)    {\
                                    (x) = (y);\
                                    sHero.DrvLayerStep = 0;\
                                }\

//4 Hero Control Definitions : End
//............................................................................................


//--------------------------------------------------------------
//3  Declare :Start

EXTERN void Hero_InitVariable(void);
EXTERN uint8_t Hero_OpenPower(void);
EXTERN uint8_t Hero_Reset(void);
EXTERN uint8_t Hero_Register(void);
EXTERN uint8_t Hero_InitRadio(void);
EXTERN uint8_t Hero_SourceInputSel(Audio_Stream_t stream,eAudio_InputSource Input,eInput_Analog_Mode mode,double scal );
EXTERN uint8_t Hero_InitAudio(void);
EXTERN uint8_t Hero_SwitchAch(uint8_t Ach, uint8_t Type);
EXTERN uint8_t Hero_SetMixSrc(uint8_t Src,uint8_t Type);
EXTERN uint8_t Hero_ConfigMix(uint8_t Src,uint8_t Type,int8_t Gain);

//3  Declare :End
//--------------------------------------------------------------


#undef EXTERN

#endif//D_AUDIO_ASP_HERO

#endif//HERO_CTL_H


