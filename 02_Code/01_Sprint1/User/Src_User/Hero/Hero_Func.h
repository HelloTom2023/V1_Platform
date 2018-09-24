/**********************************************************
 * @file        Hero_Func.h
 * @purpose    Definition of Hero Function
 * @version    0.01
 * @date        28. May. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        28.May.2012              v0.01        created
 *  
  **********************************************************/
#ifndef HERO_FUNC_H
#define HERO_FUNC_H

#ifdef D_AUDIO_ASP_HERO
#ifdef HERO_FUNC_C
#define EXTERN
#else
#define EXTERN extern
#endif//HERO_FUNC_C


//Hero Delay Update Step
typedef enum hero_delay_step_enum
{
    HERO_DELAY_STEP_WAIT = 0,
    HERO_DELAY_STEP_MUTE,
    HERO_DELAY_STEP_FL,
    HERO_DELAY_STEP_FR,
    HERO_DELAY_STEP_RL,
    HERO_DELAY_STEP_RR,
    HERO_DELAY_STEP_SWL,
    HERO_DELAY_STEP_SWR,
    //HERO_DELAY_STEP_AL,
    //HERO_DELAY_STEP_AR,
    HERO_DELAY_STEP_ACTIVE,
    HERO_DELAY_STEP_END,    
}HERO_DELAY_STEP_ENUM;





//----------------------------------------
//4 Scaling Config: Start

//Scaler config-------------Primary
#define H_FixedBoostP         48
#define H_VolMaxP            18
#define H_LoudBoostMaxP    15
#define H_ToneBoostMaxP    0
#define H_GeqRespMaxP        12
#define H_PeqRespMaxP        12
#define H_ChanGainMaxP    6

//Scaler Config : Nav/Phone
#define H_FixedBoostNP            24
#define H_VolMaxNP                18
#define H_PhoneChanGainMax    6            
#define H_NavChanGainMax        6

//Scaler Datum---------------
//FixedBoost
#define HDSP_X_Vol_Boost12dB_Data    0x000000    //48.16Db        
//OneOverMaxBoost
#define HDSP_X_Vol_OneOverMaxBoostP_Data  0x2026F3    //Related to: (GeqMaxResp+ToneBoostMaxP) 12DB
#define HDSP_X_Vol_OneOverMaxBoostS_Data  0x2026F3    //Related to: ToneBoostMaxS 12DB
//Fixed Down-Scaler:Peq
#define HDSP_Y_Vol_ScalF_Data           0x0202  // Related to : Max Front Channel PEQ Response:12DB                
#define HDSP_Y_Vol_ScalR_Data           0x0202  //                       
#define HDSP_Y_Vol_ScalSwL_Data     0x0202  //                    
#define HDSP_Y_Vol_ScalSwR_Data     0x0202  //
#define HDSP_Y_Vol_ScalS_Data           0x07FF //EQ Max to Zero
#define HDSP_Y_Vol_ScalS2_Data           0x07FF //EQ Max to Zero
//UpScaler
#define HDSP_Y_Vol_UpScalF_Data         0x07FF      //Front compensation:0
#define HDSP_Y_Vol_UpScalR_Data     0x07FF       //Rear compensation:0
#define HDSP_Y_Vol_UpScalSwL_Data     0x07FF    //Subwoofer left compensation:0 
#define HDSP_Y_Vol_UpScalSwR_Data     0x07FF    //Subwoofer right compensation    :0
#define HDSP_Y_Vol_UpScalS_Data         0x0202  // Upscaler 12DB
#define HDSP_Y_Vol_UpScalS2_Data     0x0202 

//Channel Gain---------
#define HDSP_Y_Vol_ChanGainPFL_Data        0x0400 //Primary Front Left Channel Gain
#define HDSP_Y_Vol_ChanGainPFR_Data    0x0400
#define HDSP_Y_Vol_ChanGainPRL_Data    0x0400
#define HDSP_Y_Vol_ChanGainPRR_Data    0x0400
#define HDSP_Y_Vol_ChanGainSwL_Data    0x0400
#define HDSP_Y_Vol_ChanGainSwR_Data    0x0400
#define HDSP_Y_Vol_ChanGainSL_Data        0x0400
#define HDSP_Y_Vol_ChanGainSR_Data        0x0400
#define HDSP_Y_Vol_ChanGainS2L_Data     0x0400
#define HDSP_Y_Vol_ChanGainS2R_Data    0x0400
#define HDSP_Y_Vol_ChanGainN_Data        0x0400
#define HDSP_Y_Vol_ChanGainT_Data        0x0400

//4 Scaling Config: End
//----------------------------------------



/*sub address define*/
#define HERO_SUBADDR_KEYCODE 0xE1
#define HERO_SUBADDR_USECASE 0x3F

#define HERO_USECASE 2

/*DAC ID Define*/
#define PERIHERALID_RDAC 0x32
#define PERIHERALID_FDAC 0x33

#define PERIHERALID_ADC    0x28

#define HERO_PERIPHERAL_ON    0
#define HERO_PERIPHERAL_OFF    1

#define   AUDIO_ON        1
#define   AUDIO_OFF       0

#define IN_ID_AD0         0x00  
#define IN_ID_AD1         0x01
#define IN_ID_AD2         0x02
#define IN_ID_AD3         0x03
#define IN_ID_I2S0         0x0A  
#define IN_ID_I2S1         0x0B
#define IN_ID_I2S2         0x0C
#define ID_HOST_I2S         0x14    //In&Out
#define IN_ID_HOST        0x15
#define IN_ID_SPDIF         0x1E
#define ID_SPDIF_CONFIG    0x1F

#define OUT_ID_HOST0     0x16
#define OUT_ID_HOST1     0x17
#define OUT_ID_HOST2     0x18

#define ID_ADC            0x28
#define ID_FRONT_DAC    0x32
#define ID_REAR_DAC        0x33

#define SPDIF_IN_ANALOG    0
#define SPDIF_IN_DIGITAL    1
#define SPDIF_IN_OFF        2

#define AD_DA_ENABLE    0
#define AD_DA_DISABLE    1

#define SPDIF_CONFIG_1    0    // 8 ~23
#define SPDIF_CONFIG_2    1    // 12~46
#define SPDIF_CONFIG_3    2    // 25 ~48

/*Hero GPIO Config number define*/
#define HERO_GPIO_0 0
#define HERO_GPIO_1 1
#define HERO_GPIO_2 2
#define HERO_GPIO_3 3
#define HERO_GPIO_4 4
#define HERO_GPIO_5 5
#define HERO_GPIO_6 6
#define HERO_GPIO_7 7
#define HERO_GPIO_8 8

/*GPIO function ID*/
#define GPIO_HERO_RDSINT        0x0001
#define GPIO_HERO_FASTMUTE     0x110F
#define GPIO_HERO_DEEMPHASIS     0x110C
#define GPIO_HERO_HDRADIOBLENDING 0x1107
#define GPIO_HERO_LIMITER         0x1106
#define GPIO_HERO_CLICKCLACK     0x1105
#define GPIO_HERO_OUTPUT_LOW      0xFFF0
#define GPIO_HERO_OUTPUT_HIGH     0xFFF1
#define GPIO_DISCONNCT             0xFFF2

#define HERO_DRV_CTL_END    0xFE    

// I2c writ memory type define
typedef enum hero_mem_type_enum
{
    I2CDRV_EP_MEM = 0,
    I2CDRV_X_MEM,
    I2CDRV_Y_MEM,
    I2CDRV_INVALID,
}HERO_MEM_TYPE_ENUM;


#pragma pack(1)
typedef struct
{
    uint8_t Type;
    uint16_t Addr;
    int32_t Data;
}sMemAddr_Data;

typedef enum Audio_Channel
{
    Mono        = 1,
    Front       = 2,
    Rear        = 3,
    Left        = 4,
    Right       = 5,
    FrontLeft   = 6,
    FrontRight  = 7,
    RearLeft    = 8,
    RearRight   = 9,
    Center      = 10,
    SubWoofer   = 11,
    SubCenter   = 12,
    Navigation  = 13,
    Phone       = 14,
    Chime       = 15,
    PDC         = 16,
    Secondary   = 17    /* Used for Sink Select Connect */
} eAudioChannel;
/*Audio Limiter/Clip Detect function mask define*/
#define LimiterFlag_Mask_SCD0      0x01
#define LimiterFlag_Mask_SCD1      0x02
#define LimiterFlag_Mask_SCD2      0x04
#define LimiterFlag_Mask_SCD3      0x08
#define LimiterFlag_Mask_GPIO0    (1<<9)
#define LimiterFlag_Mask_GPIO1    (1<<10)
#define LimiterFlag_Mask_GPIO2   (1<<11)
#define LimiterFlag_Mask_GPIO3    (1<<12)
#define LimiterFlag_Mask_GPIO4    (1<<13)
#define LimiterFlag_Mask_GPIO5    (1<<14)
#define LimiterFlag_Mask_GPIO6    (1<<15)
#define LimiterFlag_Mask_GPIO7    (1<<16)
#define LimiterFlag_Mask_GPIO8    (1<<17)
/*software clip detector define*/
typedef enum
{
    SCD0=0,
    SCD1,
    SCD2,
    SCD3
}eSoftwareClipDetect;

/*Audio PEQ Feature*/
typedef enum{
    BAND1=0,
    BAND2,
    BAND3,
    BAND4,
    BAND5,
    BAND6,
    BAND7,
    PEQ_BAND_MAX,
}ePeqBand;

/*Audio common define*/
#define DOUBLE_PI        3.141592

#define HERO_XDATA 0
#define HERO_YDATA 1
#define HERO_2YDATA    2


/*---------------audio channel define-------------------------*/
#define HERO_CH_PFL 0x0001   //front left channel     
#define HERO_CH_PFR 0x0002    //front right channel
#define HERO_CH_PRL 0x0004    //rear left channel
#define HERO_CH_PRR 0x0008    //rear right channel
#define HERO_CH_SWL 0x0010    //subwoofer left channel
#define HERO_CH_SWR 0x0020    //subwoofer right channel
#define HERO_CH_SL 0x0040    //secondary left channel
#define HERO_CH_SR 0x0080    //secondary right channel
#define HERO_CH_P 0x0100         //overall primary channel
#define HERO_CH_S 0x0200        //overall secondary channel
#define HERO_CH_NAV 0x0400        //overall navigation channel
#define HERO_CH_PHONE 0x0800        //overall phone channel
/*---------------end of audio channel define-------------------------*/



//--------------------------------------------------------------
//3  Declare :Start

EXTERN uint8_t Hero_ReadCommon(HERO_DRIVER_TYPE_ENUM PID,uint8_t Reg,uint8_t Num);
EXTERN uint8_t Hero_WriteCommon(HERO_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num);
EXTERN uint8_t Hero_Init_ImproveRadioA(uint8_t eState);
EXTERN uint8_t Hero_Init_ImproveAudioA(void);
EXTERN uint8_t Hero_Init_ImproveAudioA(void);
EXTERN uint8_t Hero_Init_ImproveRadioA2(uint8_t eState);
EXTERN uint8_t Hero_Init_SpuriosSignal(uint8_t eState);
EXTERN uint8_t Hero_Init_IISVco(uint8_t eState);
EXTERN uint8_t Hero_Keycode(void);
EXTERN uint8_t Hero_UserCase(uint8_t eState);
EXTERN uint8_t Hero_AcitveDevice(uint8_t eState);
EXTERN uint8_t Hero_UpdatePll(uint8_t eState,uint8_t PID,uint8_t Mode,uint8_t Band,uint16_t Freq);
EXTERN uint8_t Hero_Init_ImproveRadioB(uint8_t eState);
EXTERN uint8_t Hero_Init_ImproveAudioB(uint8_t eState);
EXTERN uint8_t Hero_Init_ImproveAudioC(uint8_t eState);
EXTERN uint8_t Hero_RadioConfigInit(void);
EXTERN uint8_t Hero_RadioInitAll(void);
EXTERN uint8_t Hero_DrvLimiterConfigSel(uint8_t Config);
EXTERN uint8_t Hero_DrvLimiterSet(eAudioChannel section,int8_t gain,uint8_t onoff);
//EXTERN uint8_t Hero_DrvLimiterFlagGenerSet(eAudioChannel section,int8_t clipdetectMask,uint32_t polarity);
EXTERN uint8_t Hero_DrvSoftClipDetectSet(uint8_t section,int8_t ThreGain);
EXTERN uint8_t Hero_DrvFastMuteConfig(uint8_t Polarity,double FallTime,double RiseTime);
EXTERN uint8_t Hero_ScalingInit(void);
EXTERN uint8_t Hero_InitChanGain(void);
EXTERN uint8_t Hero_SetChanGain(void);
EXTERN uint8_t Hero_SrcScalingInit(void);
EXTERN uint8_t Hero_WriteMemWord(HERO_DRIVER_TYPE_ENUM PID, uint8_t MemType, uint16_t Addr, int32_t  Data);
EXTERN uint8_t Hero_DrvSetNavInput(eAudio_InputSource Input);
EXTERN uint8_t Hero_DrvSetPhoneInput(eAudio_InputSource Input);
EXTERN uint8_t Hero_DrvSetPSInput(Audio_Stream_t Stream,eAudio_InputSource Input);
EXTERN uint8_t Hero_DrvSetInputAnalogMode(eAudio_InputSource Input,eInput_Analog_Mode mode);
EXTERN uint8_t Hero_DrvPEQSet(eAudioChannel Channel, uint8_t Band, uint16_t* Coefs);
EXTERN uint8_t Hero_DrvSuperPositionGain(HERO_DRIVER_TYPE_ENUM PID,uint8_t AddOnIndex, int8_t PresetGain);
EXTERN uint8_t Hero_SoftMute(uint16_t Channel,uint8_t MuteData);
EXTERN uint8_t Hero_NavPhoneFilterInit(void);
EXTERN uint8_t Hero_SetChimeMode(uint8_t Mode);


EXTERN uint8_t Hero_SetDcFilter(uint8_t Val, uint8_t Type);
EXTERN uint8_t Hero_BeepInit(void);
EXTERN uint8_t Hero_BeepVol(uint8_t Val);
EXTERN uint8_t Hero_BeepPos(uint8_t Pos);
EXTERN uint8_t Hero_Beep(uint8_t Type);
EXTERN uint8_t Hero_BeepStop(void);
EXTERN uint8_t Hero_SetBass(PN_FILTER_STRUCT sBass,uint8_t Type);
EXTERN uint8_t Hero_SetMid(PN_FILTER_STRUCT sMid,uint8_t Type);
EXTERN uint8_t Hero_SetTreble(PN_FILTER_STRUCT sTreble,uint8_t Type);
EXTERN uint8_t Hero_AudioPointer(void);
EXTERN uint8_t Hero_DrvSetVolume(uint8_t Volume, uint8_t Type);
EXTERN uint8_t Hero_NavPhoneVol(uint8_t Val,uint8_t Type);
EXTERN uint8_t Hero_ConfigGpio(uint8_t eState);
EXTERN uint8_t Hero_SetBalFad(void);
EXTERN uint8_t Hero_SetGeq(void);
EXTERN uint8_t Hero_DelayLine(void);
EXTERN uint8_t Hero_SetPhaseShifter(void);
EXTERN uint8_t Hero_SetUltraBass(void);
EXTERN uint8_t Hero_CCInit(void);
EXTERN uint8_t Hero_CCSet(uint8_t Mode);
EXTERN uint8_t Hero_CCEnable(void);
EXTERN uint8_t Hero_CCDisable(void);
EXTERN int32_t RoundChange(double Val, uint8_t Mode);
EXTERN void Hero_Calc_Bass(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_Mid(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_Treble(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_Eq(uint8_t Flag,PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN uint16_t Hero_Calc_LoudBoost(uint8_t Type, uint8_t Level);
EXTERN void Hero_Calc_2ndLHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_NavPhoneVol(int8_t Vol, uint16_t* Result);
EXTERN void Hero_Calc_1stLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_1stHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_2ndPN(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_2ndLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_2ndHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Hero_Calc_3rdLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN void Hero_Calc_3rdHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN void Hero_Calc_4thLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN void Hero_Calc_4thHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN void Hero_Calc_3rdLP_By21(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN uint8_t Hero_SrcScalerToZero(uint8_t Type);

//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN 

#endif//D_AUDIO_ASP_HERO

#endif//HERO_FUNC_H

