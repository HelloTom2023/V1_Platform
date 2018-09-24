/**********************************************************
 * @file        Dirana3_Func.h
 * @purpose    Definition of Dirana Function
 * @version    0.01
 * @date        18.Dec. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        18.Dec.2012              v0.01        created
 *  
  **********************************************************/
#ifndef DIRANA3_FUNC_H
#define DIRANA3_FUNC_H

#ifdef DIRANA3_FUNC_C
#define EXTERN
#else
#define EXTERN extern
#endif//DIRANA3_FUNC_C


//Boot Step: Image Load Step
typedef enum dirana_boot_step_enum
{
    DIRANA_BOOT_BBP0 = 0,
    DIRANA_BOOT_BBP1,
    DIRANA_BOOT_BBP2,
    DIRANA_BOOT_ABB0,        //ABB-SRC
    DIRANA_BOOT_ABB1,        //ABB-AUD
    DIRANA_BOOT_ARM0,    //Cotex M0 Upper
    DIRANA_BOOT_ARM1,    //Cotex M0 Lower
    DIRANA_BOOT_CHECK,    //Check Boot Result and Delay
    DIRANA_BOOT_END,
}DIRANA_BOOT_ENUM;


//Delay Update Step
typedef enum dirana_delay_step_enum
{
    DIRANA_DELAY_STEP_WAIT = 0,
    DIRANA_DELAY_STEP_MUTE,
    DIRANA_DELAY_STEP_FL,
    DIRANA_DELAY_STEP_FR,
    DIRANA_DELAY_STEP_RL,
    DIRANA_DELAY_STEP_RR,
    DIRANA_DELAY_STEP_SWL,
    DIRANA_DELAY_STEP_SWR,
    //DIRANA_DELAY_STEP_AL,
    //DIRANA_DELAY_STEP_AR,
    DIRANA_DELAY_STEP_ACTIVE,
    DIRANA_DELAY_STEP_END,    
}DIRANA_DELAY_STEP_ENUM;

//sub address define
#define DIRANA_SUBADDR_KEYCODE 0xE1

#define P_RADIO        0
#define S_RADIO        1


//Memory Type Define
typedef enum dirana_mem_type_enum
{
    MEM_TYPE_P = 0,    //P Memory
    MEM_TYPE_X,        //X Memory
    MEM_TYPE_Y,        //Y Memory
    MEM_TYPE_SX,        //SDSP X Memory
    MEM_TYPE_SY,        //SDSP Y Memory
    MEM_INVALID,
}DIRANA_MEM_TYPE_ENUM;


//Memory buffer struct
#pragma pack(1)
typedef struct mem_buffer_struct
{
    uint8_t Type;        //Memory Type
    uint16_t Addr;    //Address
    int32_t Data;    //Data
}MEM_BUFFER_STRUCT;

//Datum buffer struct
#pragma pack(1)
typedef struct dat_buffer_struct
{
    uint8_t Addr;    //Address
    uint8_t Data;    //Data
}DAT_BUFFER_STRUCT;

//Dirana 3 Input/Output Defines
#define IN_ID_AIN0     0x00
#define IN_ID_AIN1     0x01  
#define IN_ID_AIN2     0x02
#define IN_ID_AIN3     0x03
#define IN_ID_AIN4     0x04
#define IN_ID_AIN5     0x05  
#define IN_ID_IIS0     0x0A 
#define IN_ID_IIS1     0x0B 
#define IN_ID_IIS2     0x0C  
#define IN_ID_IIS3     0x0D  
#define IN_ID_IIS9     0x0E  
#define IN_ID_HOST_A     0x15    //Host IIS A 4 5  
#define IN_ID_HOST_B     0x1B      //Host IIS B 6 7 8
#define IN_ID_SPDIF0        0x1E
#define IN_ID_SPDIF1            0x20
#define IN_CONFIG_SPDIF0    0x1F
#define IN_CONFIG_SPDIF1    0x21
#define IN_CONFIG_HOSTA    0x35
#define IN_CONFIG_HOSTB    0x36

#define OUT_ID_HOST0     0x16
#define OUT_ID_HOST1     0x17
#define OUT_ID_HOST2     0x18
#define OUT_ID_HOST3     0x19
#define OUT_CONFIG_HOST    0x1A    //Host IIS output format
#define OUT_ID_SPDIF0    0x22
#define OUT_ID_SPDIF1    0x23

#define AUDIO_ADC        0x28
#define AUDIO_DAC01    0x32
#define AUDIO_DAC23    0x33
#define AUDIO_DAC45    0x34    

#define SPDIF_IN_ANALOG    0
#define SPDIF_IN_DIGITAL    1
#define SPDIF_IN_OFF        2

#define SPDIF_FS_LOW    0    //7.5khz~28.0khz
#define SPDIF_FS_MID    1    //13.4khz~50.4khz
#define SPDIF_FS_HIGH    2    //33.5khz~126.1khz

#define PERIPHERAL_ON    0
#define PERIPHERAL_OFF    1

#define HOST_CONFIG_SYNC    1
#define HOST_CONFIG_ASYNC 0

//----------------------------------------
//4 Scaling Config: Start

//Scaler config-------------Primary
#define FixedBoostP         48
#define VolMaxP            18
#define LoudBoostMaxP    15
#define ToneBoostMaxP    0
#define GeqRespMaxP        12
#define PeqRespMaxP        12
#define ChanGainMaxP    6

//Scaler Config : Nav/Phone
#define FixedBoostNP            24
#define VolMaxNP                18
#define PhoneChanGainMax    6            
#define NavChanGainMax        6

//Scaler Datum---------------
//FixedBoost
#define ADSP_X_Vol_Boost12dB_Data    0x000000    //48.16Db        
//OneOverMaxBoost
#define ADSP_X_Vol_OneOverMaxBoostP_Data  0x2026F3    //Related to: (GeqMaxResp+ToneBoostMaxP) 12DB
#define ADSP_X_Vol_OneOverMaxBoostS_Data  0x2026F3    //Related to: ToneBoostMaxS 12DB
//Fixed Down-Scaler:Peq
#define ADSP_Y_Vol_ScalF_Data           0x0202  // Related to : Max Front Channel PEQ Response:12DB                
#define ADSP_Y_Vol_ScalR_Data           0x0202  //                       
#define ADSP_Y_Vol_ScalSwL_Data     0x0202  //                    
#define ADSP_Y_Vol_ScalSwR_Data     0x0202  //
#define ADSP_Y_Vol_ScalS_Data           0x07FF //EQ Max to Zero
#define ADSP_Y_Vol_ScalS2_Data           0x07FF //EQ Max to Zero
//UpScaler
#define ADSP_Y_Vol_UpScalF_Data         0x07FF      //Front compensation:0
#define ADSP_Y_Vol_UpScalR_Data     0x07FF       //Rear compensation:0
#define ADSP_Y_Vol_UpScalSwL_Data     0x07FF    //Subwoofer left compensation:0 
#define ADSP_Y_Vol_UpScalSwR_Data     0x07FF    //Subwoofer right compensation    :0
#define ADSP_Y_Vol_UpScalS_Data         0x0202  // Upscaler 12DB
#define ADSP_Y_Vol_UpScalS2_Data     0x0202 

//Channel Gain---------
#define ADSP_Y_Vol_ChanGainPFL_Data        0x0400 //Primary Front Left Channel Gain
#define ADSP_Y_Vol_ChanGainPFR_Data    0x0400
#define ADSP_Y_Vol_ChanGainPRL_Data    0x0400
#define ADSP_Y_Vol_ChanGainPRR_Data    0x0400
#define ADSP_Y_Vol_ChanGainSwL_Data    0x0400
#define ADSP_Y_Vol_ChanGainSwR_Data    0x0400
#define ADSP_Y_Vol_ChanGainSL_Data        0x0400
#define ADSP_Y_Vol_ChanGainSR_Data        0x0400
#define ADSP_Y_Vol_ChanGainS2L_Data     0x0400
#define ADSP_Y_Vol_ChanGainS2R_Data    0x0400
#define ADSP_Y_Vol_ChanGainN_Data        0x0400
#define ADSP_Y_Vol_ChanGainT_Data        0x0400

//4 Scaling Config: End
//----------------------------------------



/*---------------audio channel define-------------------------*/
#define DIRANA_CH_PFL 0x0001   //front left channel     
#define DIRANA_CH_PFR 0x0002    //front right channel
#define DIRANA_CH_PRL 0x0004    //rear left channel
#define DIRANA_CH_PRR 0x0008    //rear right channel
#define DIRANA_CH_SWL 0x0010    //subwoofer left channel
#define DIRANA_CH_SWR 0x0020    //subwoofer right channel
#define DIRANA_CH_SL 0x0040    //secondary left channel
#define DIRANA_CH_SR 0x0080    //secondary right channel
#define DIRANA_CH_P 0x0100         //overall primary channel
#define DIRANA_CH_S 0x0200        //overall secondary channel
#define DIRANA_CH_NAV 0x0400        //overall navigation channel
#define DIRANA_CH_PHONE 0x0800        //overall phone channel
/*---------------end of audio channel define-------------------------*/



//Audio Stream Define, Audio Channel
#define STREAM_PRIMARY    1
#define STREAM_SECONDARY    2
#define STREAM_2SECONDARY    3
#define STREAM_NAVI        4
#define STREAM_PHONE        5

/*Audio Input define*/
typedef enum input_source_enum
{
    INPUT_SRC_P_RADIO = 0,
    INPUT_SRC_S_RADIO,
    INPUT_SRC_IDLE,
    INPUT_SRC_AIN01 = 0x08,
    INPUT_SRC_AIN23,
    INPUT_SRC_AIN45,    //Optional locked by key code       
    INPUT_SRC_TDM0 = 0x0C,
    INPUT_SRC_TDM1,
    INPUT_SRC_TDM2,
    INPUT_SRC_TDM3,
    INPUT_SRC_TDM4 = 0x04,
    INPUT_SRC_TDM5,
    INPUT_SRC_IIS0 = 0x10,
    INPUT_SRC_IIS1,
    INPUT_SRC_IIS2,
    INPUT_SRC_IIS3 = 0x18,
    INPUT_SRC_HOSTIIS4 = 0x13,
    INPUT_SRC_HOSTIIS5,
    INPUT_SRC_HOSTIIS6 = 0x1A,
    INPUT_SRC_HOSTIIS7,
    INPUT_SRC_HOSTIIS8,
    INPUT_SRC_IIS9,    //0x1D
    INPUT_SRC_SPDIF0 = 0x15,    
    INPUT_SRC_SPDIF1,    
    INPUT_SRC_NOISE=0x1E,
    INPUT_SRC_SINE,
    INPUT_SRC_MAX,
}INPUT_SRC_ENUM;

// GPIO function ID: Tuner Feature; Can Combined
#define GPIO_FUNID_P_RDSINT    0x0101
#define GPIO_FUNID_S_RDSINT    0x0102
#define GPIO_FUNID_P_QSI        0x0103
#define GPIO_FUNID_S_QSI        0x0104
#define GPIO_FUNID_P_FQCI        0x0105
#define GPIO_FUNID_S_FQCI        0x0106
//GPIO Function ID: Sad
#define GPIO_FUNID_SAD_A    0x1100
#define GPIO_FUNID_SAD_B    0x1101
#define GPIO_FUNID_SAD_C    0x1102
//Gpio Function ID: Audio
#define GPIO_FUNID_CLICKCLACK        0x3000
#define GPIO_FUNID_CLIP_LIMITER1    0x3001
#define GPIO_FUNID_CLIP_LIMITER2    0x3002
#define GPIO_FUNID_CLIP_LIMITER3    0x3003
#define GPIO_FUNID_CLIP_LIMITER4    0x3004
#define GPIO_FUNID_CLIP_LIMITER5    0x3005
#define GPIO_CLIP_LOW_MASK    0x0200    
#define GPIO_FUNID_DEEMPHASIS    0x3006
#define GPIO_FUNID_FASTMUTE    0x3007
#define GPIO_FUNID_HDBLEND    0x3008
//Gpio Function ID: Generic Feature
#define GPIO_FUNID_OUTPUT_LOW    0x0107
#define GPIO_FUNID_OUTPUT_HIGH    0x0108
#define GPIO_FUNID_READ            0x0000
#define GPIO_FUNID_ENABLE_OPTION    0xFFFF


//Dirana GPIO Config number define
typedef enum dirana_gpio_enum
{
    DIRANA_GPIO_0 = 0,
    DIRANA_GPIO_1,
    DIRANA_GPIO_2,
    DIRANA_GPIO_3,
    DIRANA_GPIO_4,
    DIRANA_GPIO_5,
    DIRANA_GPIO_6,
    DIRANA_GPIO_7,
    DIRANA_GPIO_8,
    DIRANA_GPIO_9,
    DIRANA_GPIO_10,
    DIRANA_GPIO_11,
    DIRANA_GPIO_12,
    DIRANA_GPIO_13,
    DIRANA_GPIO_14,
    DIRANA_GPIO_15,
    DIRANA_GPIO_16,
    DIRANA_GPIO_17,
    DIRANA_GPIO_18,
    DIRANA_GPIO_19,
    DIRANA_GPIO_20,
    DIRANA_GPIO_21,
    DIRANA_GPIO_22,
    DIRANA_GPIO_23,
    DIRANA_GPIO_24,
}DIRANA_GPIO_ENUM;

#define BAND1_CH ((sAudio.PeqStep - PEQ_BAND1_CALC_FL) / 2)
#define BAND2_CH ((sAudio.PeqStep - PEQ_BAND2_CALC_FL) / 2)
#define BAND3_CH ((sAudio.PeqStep - PEQ_BAND3_CALC_FL) / 2)
#define BAND4_CH ((sAudio.PeqStep - PEQ_BAND4_CALC_FL) / 2)
#define BAND5_CH ((sAudio.PeqStep - PEQ_BAND5_CALC_FL) / 2)
#define BAND6_CH ((sAudio.PeqStep - PEQ_BAND6_CALC_FL) / 2)
#define BAND7_CH ((sAudio.PeqStep - PEQ_BAND7_CALC_FL) / 2)
#define BAND8_CH ((sAudio.PeqStep - PEQ_BAND8_CALC_FL) / 2)
#define BAND9_CH ((sAudio.PeqStep - PEQ_BAND9_CALC_FL) / 2)
#define BAND10_CH ((sAudio.PeqStep - PEQ_BAND10_CALC_FL) / 2)
#define BAND11_CH ((sAudio.PeqStep - PEQ_BAND11_CALC_FL) / 2)



EXTERN void Dirana_Transmit(uint8_t* Dat,uint8_t Num,void* CallBack, uint8_t Step);
EXTERN uint8_t Dirana_ReadCommon(DIRANA_DRIVER_TYPE_ENUM PID,uint8_t Reg,uint8_t Num);
EXTERN uint8_t Dirana_WriteCommon(DIRANA_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num);
EXTERN uint8_t Dirana_WriteMemData(DIRANA_DRIVER_TYPE_ENUM PID,uint8_t MemType,uint16_t Addr,uint8_t Len,int32_t* pData);
EXTERN uint8_t Dirana_WriteMemWord(DIRANA_DRIVER_TYPE_ENUM PID, uint8_t MemType, uint16_t Addr, int32_t  Data);
EXTERN uint8_t Dirana_WriteMemTab(DIRANA_DRIVER_TYPE_ENUM PID,const MEM_BUFFER_STRUCT *Tab);
//EXTERN uint8_t Dirana_ScratchDataWrite(DIRANA_DRIVER_TYPE_ENUM PID,uint32_t Address,uint8_t DataLength,uint16_t* pData);
EXTERN uint8_t Dirana_Keycode(uint8_t eState);
EXTERN uint8_t Dirana_Patch1(uint8_t eState);
EXTERN uint8_t Dirana_Patch2(uint8_t eState);
EXTERN uint8_t Dirana_Patch3(uint8_t eState);
EXTERN uint8_t Dirana_Patch4(uint8_t eState);
EXTERN uint8_t Dirana_ReqInit(uint8_t eState);
EXTERN uint8_t Dirana_BootPrepare(uint8_t Num);
EXTERN uint8_t Dirana_ImagePatch(void);
EXTERN uint8_t Dirana_StartApp(void);
EXTERN uint8_t Dirana_Alignment(uint8_t eState);
EXTERN uint8_t Dirana_StartPLL0(uint8_t eState);
EXTERN uint8_t Dirana_StartPLL1(uint8_t eState);
EXTERN uint8_t Dirana_SpecialActiveP(uint8_t eState);
EXTERN uint8_t Dirana_InitRadio(uint8_t Type);
EXTERN uint8_t Dirana_SpecialActiveS(uint8_t eState);
EXTERN uint8_t Dirana_Enable_SRC(void);
EXTERN uint8_t Dirana_Set_SampleRate(uint8_t SampleRate);
EXTERN uint8_t Dirana_GpioConnect(uint8_t eState);
EXTERN uint8_t Dirana_InitPeripheral(uint8_t eState);
EXTERN uint8_t Dirana_Deemphasis(void);
EXTERN uint8_t Dirana_AudioPointer(void);
EXTERN uint8_t Dirana_ScalingInit(void);
EXTERN uint8_t Dirana_DrvSetVol(uint8_t Volume, uint8_t Type);
EXTERN uint8_t Dirana_InitChannelGain(void);
EXTERN uint8_t Dirana_SetChannelGain(void);
EXTERN uint8_t Dirana_SoftMute(uint16_t Channel,uint8_t MuteData);
EXTERN uint8_t Dirana_DrvSetInput(uint8_t Stream,uint8_t Input);
EXTERN uint8_t Dirana_SourceInputSel(uint8_t Stream,uint8_t Input,uint8_t Mode,float64_t Scal);
EXTERN uint8_t Dirana_UpdatePll(uint8_t Type,uint8_t Mode, uint8_t Band, uint16_t Freq);
EXTERN uint8_t Dirana_SrcScalingInit(void);
EXTERN uint8_t Dirana_DrvSuperPositionGain(DIRANA_DRIVER_TYPE_ENUM PID,uint8_t AddOnIndex, int8_t PresetGain); 
EXTERN uint8_t Dirana_SetChimeMode(uint8_t Mode);
EXTERN uint8_t Dirana_DrvSetChimeMasterVol(uint8_t Vol);
EXTERN uint8_t Dirana_BeepInit(void);
EXTERN uint8_t Dirana_BeepVol(uint8_t Val);
EXTERN uint8_t Dirana_BeepPos(uint8_t Pos);
EXTERN uint8_t Dirana_Beep(uint8_t Type);
EXTERN uint8_t Dirana_BeepStop(void);
EXTERN uint8_t Dirana_SetBass(PN_FILTER_STRUCT sBass,uint8_t Type);
EXTERN uint8_t Dirana_SetMid(PN_FILTER_STRUCT sMid,uint8_t Type);
EXTERN uint8_t Dirana_SetTreble(PN_FILTER_STRUCT sTreble,uint8_t Type);
EXTERN uint8_t Dirana_SetBalFad(void);
EXTERN uint8_t Dirana_SetDcFilter(uint8_t Val, uint8_t Type);
EXTERN uint8_t Dirana_NavPhoneVol(uint8_t Val,uint8_t Type);
EXTERN uint8_t Dirana_DelayLine(void);
EXTERN uint8_t Dirana_SetGeq(void);
EXTERN uint8_t Dirana_SetPhaseShifter(void);
EXTERN uint8_t Dirana_SetLoudness(void);
EXTERN uint8_t Dirana_SetSrcScaler(uint8_t Type, uint8_t Val);
EXTERN  uint8_t Dirana_SetSubwoofer(void);
EXTERN uint8_t Dirana_SetPeq(void);
EXTERN uint16_t Dirana_GetPeqAddr(uint8_t Step);
EXTERN uint8_t Dirana_SetUltraBass(void);
EXTERN uint8_t Dirana_SetCrossOver(void);
EXTERN uint8_t Dirana_CCInit(void);
EXTERN uint8_t Dirana_CCSet(uint8_t Mode);
EXTERN uint8_t Dirana_CCEnable(void);
EXTERN uint8_t Dirana_CCDisable(void);
EXTERN void Dirana_Calc_Eq(uint8_t Flag,PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_FB_2ndPN(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_Bass(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_Mid(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_Treble(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN uint16_t Dirana_Calc_LoudBoost(uint8_t Type, uint8_t Level);
EXTERN void Dirana_Calc_LDB(uint8_t Freq, uint16_t* Result);
EXTERN void Dirana_Calc_LDT(uint16_t Freq,float Q, uint16_t* Result);
EXTERN void Dirana_Calc_SupSmoothAR(uint8_t Time,uint16_t* Result);
EXTERN void Dirana_Calc_1stLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_1stHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_2ndPN(PN_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_2ndLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_2ndHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result);
EXTERN void Dirana_Calc_3rdLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN void Dirana_Calc_3rdHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN void Dirana_Calc_4thLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN void Dirana_Calc_4thHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN void Dirana_Calc_3rdLP_By21(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode);
EXTERN uint16_t Dirana_Calc_SwAddr(uint8_t SwL, uint8_t SwR, uint8_t Mode);
EXTERN void Dirana_Calc_Chime_SinWave(uint16_t Freq,uint16_t* Result);

#undef EXTERN

#endif//DIRANA3_FUNC_H

