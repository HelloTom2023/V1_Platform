/**********************************************************
 * @file        Audio_Func.h
 * @purpose    Definition of Audio_Func
 * @version    0.01
 * @date        24. July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        24.July.2012              v0.01        created
 *  
  **********************************************************/
#ifndef AUDIO_FUNC_H
#define AUDIO_FUNC_H

#ifdef AUDIO_FUNC_C
#define EXTERN
#else
#define EXTERN extern
#endif//AUDIO_FUNC_C

//............................................................................................
//4 Audio Middle Layer Control Step Definitions : Start

// Load Datum Steps
typedef enum audio_load_datum_enum
{
    AUDIO_LOAD_CHECK = 0,    // Check Datum
    AUDIO_LOAD_DEFAULT,     //Load Default
    AUDIO_LOAD_ERROR,       //Error
    AUDIO_LOAD_END,               // End
}AUDIO_LOAD_DATUM_ENUM;


// AMP Startup Steps
typedef enum amp_startup_enum
{
    AMP_STARTUP_POWER = 0,    // Open AMP Power Supply
    AMP_STARTUP_RESET,        // Reset AMP Module
    AMP_STARTUP_REGISTER,    // Initialize AMP Registers
    AMP_STARTUP_END,            // AMP Startup End
}AMP_STARTUP_ENUM;

// ASP Startup Steps
typedef enum asp_startup_enum
{
    ASP_STARTUP_POWER = 0,    // Open ASP Power Supply
    ASP_STARTUP_RESET,        // Reset ASP Module
    ASP_STARTUP_REGISTER,    // Initialize ASP Registers
    ASP_STARTUP_END,            // ASP Startup End
}ASP_STARTUP_ENUM;

// Switch Startup Steps
typedef enum switch_startup_enum
{
    SWITCH_STARTUP_POWER = 0,    // Open Switch Power Supply
    SWITCH_STARTUP_RESET,        // Reset Switch Module
    SWITCH_STARTUP_REGISTER,        // Initialize Switch Registers
    SWITCH_STARTUP_END,            // Switch Startup End
}SWITCH_STARTUP_ENUM;

//Beep Control Step
typedef enum beep_ctl_enum
{
    BEEP_CTL_IDLE = 0,        // Idle State, wait for newly requirement input
    BEEP_CTL_SET,            //Set the desired beep
    BEEP_CTL_BEEPING,        // Ring The Specific Beep: Numerable or Continous, Checking End
    BEEP_CTL_STOP,            //Stop Currently Beep, Check whether detele
    BEEP_CTL_END,            // End Currently Beep and Delete
}BEEP_CTL_ENUM;

//Beep Setup Step
typedef enum beep_setup_ctl
{
    BEEP_SETUP_IDLE = 0,    //Idle
    BEEP_SETUP_VOL,        //Setup Volume
    BEEP_SETUP_POS,        //Setup Beep Position
}BEEP_SETUP_CTL_ENUM;

//Mix Control Step
typedef enum mix_ctl_enum
{
    MIX_CTL_IDLE = 0,        // Idle State, wait for newly requirement input
    MIX_CTL_ROUTE,        //Set Route
    MIX_CTL_SRC,            // Select Mix Source
    MIX_CTL_POS,            // Select Mix Position
    MIX_CTL_ATTN,            //Set System Volume Attenuation
    MIX_CTL_VOL,            //Set Mix Gain
    MIX_CTL_END,            // Mix Ends
}MIX_CTL_ENUM;

//Mute Control Steps
typedef enum audio_mute_enum
{
    AUDIO_MUTE_IDLE = 0,        //Idle State: Check Whether Execute Mute&Unmute
    AUDIO_MUTE_FADE_OUT,        //Fade Out before Mute    声音逐渐减小到0
    AUDIO_MUTE_SOFT_MUTE,    //Soft Mute Current Channel  软件静音
    AUDIO_MUTE_SMUTE_CHK,	// 检测软件静音
    AUDIO_MUTE_HARD_MUTE,    // Hard Mute Current Channel  硬件静音
    AUDIO_MUTE_HMUTE_CHK,   // 检测硬件静音
    AUDIO_MUTE_SETVOL,		   // 设置音量为零	
    AUDIO_MUTE_HARD_UNMUTE,    // Hard Unmute 硬件解静音
    AUDIO_MUTE_HUNMUTE_CHK,
    AUDIO_MUTE_SOFT_UNMUTE,    // Softe Unmute
    AUDIO_MUTE_SUNMUTE_CHK,
    AUDIO_MUTE_FADE_IN,        // Fade In  声音逐渐增大
    AUDIO_MUTE_END,            // Mute End
}AUDIO_MUTE_ENUM;

#if 0		//Key Mute FADE_IN/OUT Deal.
#define AUDIO_MUTE_START    AUDIO_MUTE_FADE_OUT
#define AUDIO_UNMUTE_START    AUDIO_MUTE_SETVOL
#else		//kEY Mute:FADE_IN/SOFT MUTE OUT
#define AUDIO_MUTE_START	AUDIO_MUTE_SOFT_MUTE
#define AUDIO_UNMUTE_START    AUDIO_MUTE_SETVOL
#endif

//Event Mute Control Step
typedef enum mute_evt_ctl_step
{
    MUTE_EVT_IDLE = 0,
    MUTE_EVT_FRONT,    //Front System Mute Implement
    MUTE_EVT_REAR,    //Rear System Mute Implement    
    MUTE_EVT_END,
}MUTE_EVT_CTL_STEP;

//Ach Switch Control Steps
typedef enum ach_switch_enum
{
    ACH_SWITCH_IDLE = 0,        //Idle State: Check Whether A newly ACH Switch Req is ready
    ACH_SWITCH_FAD_OUT,   //Fade Out before mute  声音渐变减小
    ACH_SWITCH_MUTE,            //Mute Firstly...
    ACH_SWITCH_SRC,    
    ACH_SWITCH_VCH,
    ACH_SWITCH_SWITCH,        //Switch the Switch Channel     
    ACH_SWITCH_ASP,            //Switch the Asp Channel         
    ACH_SWITCH_VOL,            //Switch to Newly Ach's Volume Setting
    ACH_SWITCH_DEMUTE,
    ACH_SWITCH_FAD_IN,
    ACH_SWITCH_TRANSITION,
    ACH_SWITCH_END,            // Ach Switch End
}ACH_SWITCH_ENUM;
#define ACH_SWITCH_START    ACH_SWITCH_FAD_OUT

//Source Switch triggerred by ACH Switch Command
typedef enum src_switch_enum
{
    SRC_SWITCH_IDLE = 0,        //Idle State: Check Whether A newly ACH Switch Req is ready
    SRC_SWITCH_MUTE,
    SRC_SWITCH_SRC,
    SRC_SWITCH_VCH,
    SRC_SWITCH_ACH,
    SRC_SWITCH_DEMUTE,
    SRC_SWITCH_END,            // Ach Switch End
}SRC_SWITCH_ENUM;

//Audio Operation Dispose Step
typedef enum operation_ctl_enum
{
    OP_CTL_IDLE = 0,        //Idle State, wait for newly requirement input
    OP_CTL_EXECUTE,        //Execute Newly Operation
    OP_CTL_END,            //Executed!
}OP_CTL_ENUM;

//4 Audio Middle Layer Control Step Definitions : End
//............................................................................................


//............................................................................................
//4 Audio Relataed Typedef Struct&Enum : Start

#define ACH_BUFFER_MAX        3    //Max number of Ach Requirement Buffer 
#define MUTE_BUFFER_MAX 15
#define MIX_BUFFER_MAX    4
#define OP_BUFFER_MAX    10    //Operation  Buffer Max Number

// Audio Parameter Struct
#pragma pack(1)
typedef struct audio_struct
{
    bit_t PwrState:1;       //Power State
    uint8_t SysState;    //Audio Task State
    uint8_t ReadyState;    //Audio Ready State: Bit0--Audio Task Ready; Bit1--Asp Init Ready; Bit2--Amp Init Ready
                            // Bit3 Switch Init Ready
    bit_t StarUp:1;
    bit_t SyncStep:6;
    uint16_t  SyncTimer;
    //4 Control Related Parameters
    uint8_t FuncStep;        // Audio System State Control Step
    uint16_t FuncDelay;    
    uint8_t MidStep;        // Middle Layer Control Step
    uint8_t FuncRetryCnt;    //Retry Counter when Error Occur

    uint8_t LoadDatumRet;
    uint8_t LoadDatumDly;
    uint8_t LoadDatumCnt;
    
    uint8_t AspCheck;   // Asp Module Check Flag
    uint8_t AspStep;    //Asp Control Step
    uint16_t AspDelay;   //Asp Control Delay
    uint8_t AspCheckCnt; 
    uint8_t AspCheckNum; 

    uint8_t DrvOverTime;    //Asp Control: Driver Over Timer
    uint8_t DrvDesertTime;  // Asp Control: Dirver Desert Time
    
    //4 Operation Control
    uint8_t CommonCode;        // Common Command Code : Set Freq, Set Band...    
    uint8_t OpCtl;    //Mix Set Step Control
    uint8_t OpHead;
    uint8_t OpTail;
    uint8_t OpBuffer[OP_BUFFER_MAX];

    //4 Audio Channel
    uint8_t AchCtl[2];    //Switch Audio Channel Control
    uint8_t AchActBuffer[ACH_MAX];    //All Actived ACH Buffer,The first one will be set.    
    uint8_t AchActRear;    //Only Source ACH available, Newly will replace old one
    uint8_t AchReqed[2];    //Required ACH, Waiting or Being Implemented...   Front System + Rear System
    uint16_t AchDelay[2];
    uint8_t AchVol;
    uint8_t AchFade;
    uint8_t AspAchCtl;
    uint8_t SrcInputSelStep;    
	uint8_t CurrentAudioSourceId;//snake20161224
    //4 Volume Related..
    uint8_t DrvVolStep;     //Set Volume Step: continuously set volume related registers
    bit_t bNotDispVol:1;

    uint8_t HintVol;
    
    //4 Audio Parameters
    uint8_t SysChannel;    // Currently System Audio Channel
    uint8_t RearChannel;    //Currently Rear Channel
    uint8_t SysChanMode;    //Currently System Channel Mode
    ACH_ATTRI_STRUCT sAchAttri[SRC_TYPE_NUM];    // Audio Channel Attribute
    
    //4 Beep Related Parameters
    uint8_t BeepCtl;
    uint8_t BeepDelay;
    uint8_t BeepHead;
    uint8_t BeepTail;
    BEEP_STRUCT sBeepBuffer[BEEP_BUFFER_MAX];    // Ready Buffer
    BEEP_STRUCT sBeepCurrent;    //Currently Running Beep    
    uint8_t BeepLast;    //Record Last Beep Type
    uint8_t BeepSetupCtl;        // Config Update control step
    uint8_t BeepSetupMask; //Mask Byte, Sign which Config should be update

    //4 Mix Related Parameters
    uint8_t MixCtl;    //Mix Set Step Control
    uint8_t MixHead;
    uint8_t MixTail;
    MIX_REQ_STRUCT sMixBuffer[MIX_BUFFER_MAX];
    uint8_t MixStatus;

    //4 Delay Line
    uint8_t DelayCtl;    //Delay Line Update control step
    uint8_t DelayLineMask;        //Mask sign which speaker's delay setting will be updated
    uint8_t DelayWait; //Delay Control Wait

    //4 Phase Shifter
    uint8_t PhaseCtl;
    uint8_t PhaseWait;
    uint8_t PhaseMask;

    //4 Tone Parameters
    uint8_t DrvBassStep;
    uint8_t DrvMidStep;
    uint8_t DrvTrebleStep;

    //4 Bal&Fad..
    uint8_t BalFadCtl;
    uint8_t BalFadMask;        
    /*Media Balance & Fader */
    uint8_t Fader_Media;
    uint8_t Balance_media;
    
    //4 Graphic Equalizer
    uint16_t GeqMask;    //Geq Mask Flag, Sign which band need to be updated
    uint8_t GeqStep;
    
    //4Parametric Equalizer
    uint8_t PeqStep;
    uint16_t PeqMask[4];    
    uint8_t PeqChannelSetp;
    uint8_t PeqBandSetp;
    uint8_t PeqResult;

    //4 Loudness
    uint8_t LoudnessCtl;
    uint8_t LoudnessMask;

    //4Subwoofer
    uint8_t SwCtl;
    uint8_t SwMask;

    //4X Cross
    uint8_t XoverCtl;        //  Xover 状态机 控制单步
    uint8_t XoverMask;    //  根据  滤波器类型  表示对应哪个喇叭起作用 
    uint8_t XoverDelay;

    //4 Ultra Bass
    uint8_t UltraBassCtl;
    uint8_t UltraBassMask;
    uint8_t UltraScaler;

    //4 Channel Gain
    uint8_t ChanGainCtl;
    uint16_t ChanGainMask;
    
    //4Click-Clack
    uint8_t ClickClackCtl;
    uint16_t ClickClackDelay;
    uint8_t ClickClackFlag;
    uint8_t ClickClackType;
    
    //4 Mute Related Parameters
    uint8_t MuteState;
    
    uint8_t MuteEvtCtl;    //Control Parameter
    uint8_t MuteCtlHead;    // Mute Evt Required Buffer Head
    uint8_t MuteCtlTail;    // Mute Evt Required Buffer Tail
    MUTE_BUFFER_STRUCT sMuteBuff[MUTE_BUFFER_MAX];    // Mute Evt Required Buffer
    
    uint8_t KeyMuteStep[2];        // Key Mute Step Control: Key Mute Dispose in a flow 
    uint8_t KeyMuteReq[2];        // Mute Req: Mute On or Mute Off
    uint8_t KeyMuteDly[2];        // Mute Delay
    uint8_t MuteVol[2];            // Mute Fade Control Volume    
    uint8_t KeyMuteState;
    uint8_t KeyMuteFlag;    // Key Mute Flag
    uint8_t ForceDeMute;

    uint8_t SoftMuteStep;
    bit_t bPowerOffMute:1;
    bit_t bFadeFlag:1;        // Sign Now is Fading
    bit_t bRearFadeFlag:1;
    bit_t bSyncToEep:1;
    bit_t bDatumReady:1;
    uint16_t TestDelayNave;
}AUDIO_STRUCT;

#pragma pack(1)
typedef struct 
{
    bit_t  F_MediaVol_Set     :1;  // Bit0:1: use default set value, 0: use last media volume value.
    bit_t  F_PhoneVol_Set      :1;  // Bit1:1: use default set value, 0: use last phone volume value.
    bit_t  F_NaviVol_Set          :1;  // Bit2:1: use default set value, 0: use last Navi volume value.
    bit_t  F_PromptVol_Set      :2;  // Bit3-4: 0: Close, 1: use default value, 2: use last prompt volume.
    bit_t  F_WarningVol_Set      :2;  // Bit5-6: 0: Close, 1: use default value, 2: use last warning volume.
    bit_t  F_Reserved         :1;  // Reserved for future use.
}VOL_SETTING_FLG;

//Audio Basic Setting Struct
#pragma pack(1)

typedef struct audio_basic_struct
{
      uint8_t Type;        //Currently EQ Type, Same as GEQ Preset

     PN_FILTER_STRUCT sBass;    
     PN_FILTER_STRUCT sMid;
     PN_FILTER_STRUCT sTreble;
   //4 Balance&Fader
    uint8_t Fader;
    uint8_t Balance;
 //4Subwoofer
    uint8_t  sSubWooferSwitch;
  //4Loudness
    uint8_t  sLoudnessMode;   

    uint8_t MixPos;         //Mix Position, only for Navi
    uint8_t MixAttn;        //System Volume Attenuation

}AUDIO_BASIC_STRUCT;
#pragma pack(1)
typedef struct audio_basic_struct_append
{
    //4Subwoofer
    SW_ATTRI_STRUCT sSubWoofer;
    //4Loudness
    LOUDNESS_ATTRI_STRUCT sLoudness;   
     VOL_SETTING_FLG sFlg;
    
    uint8_t DefaultMediaVolume; //Media default set volume value.
    uint8_t DefaultPhoneVol;        //Phone default set volume value.
    uint8_t DefaultNaviVol;     //Default set volume for Navi broadcast.
    uint8_t DefaultPromptVol;        //Reserved for Default set volume for prompt tone.
    uint8_t DefaultWarningVol;    //Reserved for Default set volume for warning tone.

    uint8_t Mix_Set_Flag;         //Mix Position, only for Navi

}AUDIO_BASIC_STRUCT_APPEND;

//Audio Channel Gain Struct : Source Gain and Speaker Gain
#pragma pack(1)
typedef struct audio_chan_gain_struct
{
    //4 Source Scaling
    uint8_t ScalerTbl[SS_SRC_MAX];    
    //4Channel Gain
    uint8_t ChanGainTbl[6];    
}AUDIO_CHANGAIN_STRUCT;

// Audio Infoes Parameter Struct
#pragma pack(1)
typedef struct audio_info_struct
{
    //4 5.1CH Mode Control
    uint8_t ChanModeSet;
    //4 Type Selection for 4.2
    uint8_t SwCenMode;  // Sw+Center Type Selection
    //4 Volume...
    uint8_t VolCurveDelta;        //Volume Delta for Volume Curve
    //4Beep
    uint8_t BeepPos;         //Attribute: Beep Position
    uint8_t BeepType;    //Ordinary Beep type
    //4 Ultra Bass
    uint8_t UbassTargetLev;    // Compensate downscaler of Target Input
}AUDIO_INFO_STRUCT;

// Audio Graphic Equalizer Struct
#pragma pack(1)
typedef struct audio_geq_struct
{
    //4Graphic Equalizer
  //  uint8_t Type;        //Currently EQ Type, Same as GEQ Preset
    PN_FILTER_STRUCT sBuffer[GEQ_MAX_NUM];    //GEQ detal info for each band
    uint8_t GainTbl[GEQ_MAX_NUM * 3];
}AUDIO_GEQ_STRUCT;

#pragma pack(1)
typedef struct audio_peq_struct
{
    //4Parametric Equalizer
    uint8_t Type;
    PN_FILTER_STRUCT sBuffer[4][PEQ_MAX_NUM];
}AUDIO_PEQ_STRUCT;

// Audio Advanced Feature Struct
#pragma pack(1)
typedef struct audio_adv_struct
{
    uint8_t DelayPreset;                    //Preset of Delay Line Setting
    uint8_t DelayCustom[DELAY_LINE_MAX];     //Each Speaker's Delay Setting
    uint8_t DcFilter;                        //Dc Filter Cut-off Frequency 
    uint8_t PhaseShifter[6];                //Phase Shifter state of Each Channel
    //4CrossOver
    uint8_t XoverPreset;  //Cross Over Preset... NUM --- Flat p1 P2 P3 Custom
    XOVER_ATTRI_STRUCT sCustomXover[3];   // 滤波器类型  前置高通，后置高通  中低音低通
    ULTRA_BASS_STRUCT sUltraBass;
    uint8_t BeepVol;        //Attribute: Beep Volume 
    uint8_t CarStyle;    //Car Style: Small or Big?  
}AUDIO_ADV_STRUCT;

#pragma pack(1)
typedef struct audio_datum_struct
{
    AUDIO_BASIC_STRUCT sBasic;
    AUDIO_BASIC_STRUCT_APPEND sBasicBK;
    AUDIO_INFO_STRUCT sInfo;
    AUDIO_CHANGAIN_STRUCT sGain;
    AUDIO_GEQ_STRUCT sGeq;
    AUDIO_ADV_STRUCT sAdv;
    uint16_t CheckSum;
}AUDIO_DATUM_STRUCT;

#pragma pack(1)
typedef struct audio_keep_struct
{
    uint8_t CurrentlyVol;    //Currently Volume : Control and Display Usage
    uint8_t SysVol;        //System Volume
    uint8_t NaviVol;        //Navi Volume
    uint8_t BtVol;        // BT Volume
    uint8_t AppVol;     //APP Prompt volume
    uint8_t RearVol;        //Currently Rear Volume 
    uint8_t AspModule;  //ASP Module Type
    uint8_t BakDelay[DELAY_LINE_MAX];  //Datum bak for transfer, because of FIXED protocol
    XOVER_ATTRI_STRUCT sBakXover[3];  //Datum bak for transfer, because of FIXED protocol   
    PN_FILTER_STRUCT sBakGeq[GEQ_MAX_NUM];    //GEQ detal info for each band
    uint8_t sBakGain[GEQ_MAX_NUM * 3];
}AUDIO_KEEP_STRUCT;

#pragma pack(1)
typedef struct audio_eep_struct
{
    uint8_t E_BeepVol;     
    uint8_t E_CarStyle;   
    uint8_t E_SrcScaler[SS_SRC_MAX];    
    uint8_t E_ChanGain[6];  
    uint16_t E_CheckSum;
}AUDIO_EEP_STRUCT;

//4 Audio Relataed Typedef Struct&Enum : End
//............................................................................................


typedef enum mute_type_enum
{
    TYPE_F_S_MUTE = 0,        //Front System Soft Mute
    TYPE_F_H_MUTE,        //Hard Mute
    TYPE_F_KS_MUTE,        //Key Soft Mute
    TYPE_F_KH_MUTE,        //Key Hard Mute
    TYPE_F_K_MUTE,
    TYPE_F_S_UNMUTE,        //Soft UnMute
    TYPE_F_H_UNMUTE,        //Hard UnMute
    TYPE_F_KS_UNMUTE,        //Key Soft UnMute
    TYPE_F_KH_UNMUTE,        //Key Hard UnMute
    TYPE_F_K_UNMUTE,
    TYPE_F_CURRENT_MUTE,
    TYPE_F_CURRENT_UNMUTE,
    TYPE_R_S_MUTE,        //Rear System Soft Mute
    TYPE_R_H_MUTE,        //Hard Mute
    TYPE_R_KS_MUTE,        //Key Soft Mute
    TYPE_R_KH_MUTE,        //Key Hard Mute
    TYPE_R_S_UNMUTE,        //Soft UnMute
    TYPE_R_H_UNMUTE,        //Hard UnMute
    TYPE_R_KS_UNMUTE,        //Key Soft UnMute
    TYPE_R_KH_UNMUTE,    //Key Hard UnMute
    TYPE_R_CURRENT_MUTE,
    TYPE_R_CURRENT_UNMUTE,
}MUTE_TYPE_ENUM;

#define MASK_F_KMUTE        0x01    //Front System Key Mute
#define MASK_F_SMUTE           0x02    //Front System Soft Mute
#define MASK_F_HMUTE         0x04    //Front System Hard Mute
#define MASK_R_KMUTE        0x08    //Rear System Key Mute
#define MASK_R_SMUTE        0x10    //Rear System Key Mute
#define MASK_R_HMUTE        0x20    //Rear System Key Mute

#define MASK_KMUTE_FS    0x01     //Front Soft
#define MASK_KMUTE_FH    0x02    //Front Hard
#define MASK_KMUTE_RS    0x04    //Rear Soft
#define MASK_KMUTE_RH    0x08    //Rear Hard

#define AUDIO_REQ_NULL            0
#define AUDIO_REQ_MUTE        1
#define AUDIO_REQ_UNMUTE        2

#define AUDIO_VOL_MIN            10
#define AUDIO_VOL_DEFULT_SYS     15    
#define AUDIO_VOL_DEFULT_NAVI     40
#define AUDIO_VOL_DEFULT_BT     20
#define AUDIO_VOL_DEFULT_APP     20
#define AUDIO_VOL_MAX            40
#define AUDIO_VOL_MAX_BT         30

#define AUDIO_BASS_MAX            24 //  14  //Gain: -12 ~ + 12 //snake20160919
#define AUDIO_MID_MAX           24 // 14
#define AUDIO_TREBLE_MAX        24 // 14
#define AUDIO_BALANCE_MAX        16  //14 //18    //L9~0~R9
#define AUDIO_FADER_MAX        16 // 14    //F9~0~R9

#define AUDIO_BASS_CF_MAX        3
#define AUDIO_BASS_Q_MAX        2
#define AUDIO_MID_CF_MAX        3
#define AUDIO_MID_Q_MAX        2
#define AUDIO_TREBLE_CF_MAX    3    
#define AUDIO_TREBLE_Q_MAX    2
#define AUDIO_GEQ_MAX            14
#define AUDIO_SRC_SCALER_MAX    12
#define AUDIO_GEQ_GAIN_MAX      14
#define AUDIO_GEQ_CF_MAX        2
#define AUDIO_GEQ_Q_MAX         2

#define AUDIO_DC_MAX        (200000/35)

#define AUDIO_DRV_VOL_MIN        0x0F    // Mute, Next -80Db
#define AUDIO_DRV_VOL_MAX        0x78    //+24DB

#define AUDIO_VOL_REVERSE            10

#define LOUDNESS_ON    1
#define LOUDNESS_OFF    0

// Common Command
typedef enum audio_common_enum
{
    AUDIO_COMMON_NULL = 0,
    AUDIO_COMMON_VOL,    //Set Front System Volume
    AUDIO_COMMON_REARVOL,    //Set Rear System Volume
    AUDIO_COMMON_BASS,
    AUDIO_COMMON_MID,
    AUDIO_COMMON_TREBLE,
    AUDIO_COMMON_BF,    //Set Balance Fader
    AUDIO_COMMON_GEQ,        //G-EQ 
    AUDIO_COMMON_PEQ,
    AUDIO_COMMON_DC,        //DC Filter
    AUDIO_COMMON_DELAY,    //Delay Line    
    AUDIO_COMMON_PHASESHIFT,    //Phase Shift
    AUDIO_COMMON_LOUDNESS,
    AUDIO_COMMON_SUBWOOFER,
    AUDIO_COMMON_CHANGAIN,
    AUDIO_COMMON_UBASS,
    AUDIO_COMMON_XOVER,
    AUDIO_COMMON_HINT_VOL, //fade in&out selected volume value
    AUDIO_COMMON_HINT_EXIT, //Exit hinting Volume Setting
    AUDIO_COMMON_SRC_SCALER,
}AUDIO_COMMON_ENUM;

//--------------------------------------------------------------
//3  Definitions :Start


#define Switch_OpenPower()            		SUBLAYER_DONE
#define Switch_Reset()                			SUBLAYER_DONE
#define Switch_Register()                		SUBLAYER_DONE
#define Audio_SwitchSwitchAch(x,y)        	Hc4053_SwitchAch((x),(y))


#define Audio_AmpDetect()   Amp_Detect()

//3  Definitions :End
//--------------------------------------------------------------


//--------------------------------------------------------------
//3  Declare :Start

extern const uint8_t Tab_DelayPreset[];
extern const uint16_t Tab_Db2Lin[];
extern const uint8_t Tab_BeepVolume[];
extern const uint16_t Tab_NaviPhone_Vol[];
extern const int8_t Tab_VolDbLev[];
extern const uint16_t Tab_Bass_CF[];
extern const uint16_t Tab_Middle_CF[];
extern const uint16_t Tab_Treble_CF[]; 
extern const uint8_t Tab_BF_Atten[];
extern const float Tab_Filter_Q[];
extern const uint8_t Tab_Loudness_B_Curve[];
extern const uint8_t Tab_Loudness_T_Curve[]; 
extern const uint8_t Tab_XoverCoF[];
extern const uint16_t Tab_Geq_Band_CF[];
extern const uint8_t Tab_Geq_Max_Gain[];
extern const GEQ_PRESET_STRUCT Tab_Geq_Band[];
#ifdef D_TONE_EQ
extern const GEQ_PRESET_STRUCT Tab_Tone_Eq[];
#ifdef D_TUNER_EQ
extern const GEQ_PRESET_STRUCT Tab_Tone_Tuner_Eq[];
#endif
#endif
    
EXTERN AUDIO_STRUCT sAudio;

//Un-Initial Parameters: Audio Informations
#pragma section data "no_init" begin    
EXTERN AUDIO_KEEP_STRUCT sAudioKeep;
EXTERN AUDIO_DATUM_STRUCT sAudioDat;
EXTERN AUDIO_PEQ_STRUCT sAudioPeq;
EXTERN AUDIO_EEP_STRUCT sAudioEep;
#ifdef D_TONE_EQ
EXTERN GEQ_PRESET_STRUCT UserGeq[3];
#endif
#pragma section data "no_init" end



EXTERN uint8_t Audio_FastHardMute(uint8_t Mode);
EXTERN uint8_t Audio_LoadDatum(void);
EXTERN uint8_t Audio_AmpStartup(void);
EXTERN uint8_t Audio_AspStartup(void);
EXTERN uint8_t Audio_SwitchStartup(void);
EXTERN void Audio_InputLogic(tMSG_BUF* Msg);
EXTERN uint8_t Audio_InputExecute(uint8_t Req);
EXTERN void Audio_MuteQueueIn(uint8_t Ach, MUTE_TYPE_ENUM Type, uint8_t Sys);

EXTERN void Audio_MuteEvtDisposal(void);
EXTERN void Audio_KeyMuteDisposal(void);
EXTERN void Audio_AchQueueIn(uint8_t Req, uint8_t Type);
EXTERN void Audio_SetChannel(eSOURCE_ZONE eZone,const tSOURCE* tSrc,uint8_t AudPri);
EXTERN void Audio_AchSwitchMgr(void);
EXTERN void Audio_BeepQueueIn(uint8_t Type, uint8_t Attri);
EXTERN void Audio_BeepDisposal(void);
EXTERN void Audio_BeepConfig(void);
EXTERN void Audio_MixQueueIn(uint8_t Src, uint8_t Pos);
EXTERN void Audio_MixDisposal(void);
EXTERN uint8_t Audio_GetSourceScaler(uint8_t ACH);
EXTERN uint8_t Audio_ChgScalerChk(uint8_t Src);
EXTERN void Audio_OpQueueIn(uint8_t Op);
EXTERN void Audio_OpDisposal(void);
EXTERN void Audio_CC_QueueIn(uint8_t Flag, uint8_t Type);
EXTERN void Audio_ClickClack(void);
EXTERN void Audio_SyncVolume(uint8_t Ach);

//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN

#if D_DEBUG_AUDIO && D_PRINT_EN
#define audio_printf(x)  x
#else
#define audio_printf(x)
#endif
#endif//AUDIO_FUNC_H

