/**********************************************************
 * @file        Tuner_MidLayer.h
 * @purpose    Definition of Tuner Middle Layer
 * @version    0.01
 * @date        11. July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        11.July.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TUNER_MIDLAYER_H
#define TUNER_MIDLAYER_H

#ifdef TUNER_MIDLAYER_C
#define EXTERN
#else
#define EXTERN extern
#endif//TUNER_MIDLAYER_C

//............................................................................................
//4 Tuner Middle Layer Control Step Definitions : Start

// Power On Steps
typedef enum tuner_pwron_enum
{
    TUNER_PWRON_OPEN_POWER = 0,    // Open Tuner Module's Power Supply
    TUNER_PWRON_INIT_VARIABLE,        // Initialize Variable
    TUNER_PWRON_END,                    // Power On End
}TUNER_PWRON_ENUM;

// Load Datum Steps
typedef enum tuner_load_datum_enum
{
   
    TUNER_LOAD_RAM_CHK,     //Load Default
    TUNER_LOAD_DEFAULT,       //Error
    TUNER_LOAD_END,               // End
}TUNER_LOAD_DATUM_ENUM;

// Initialize Registers Steps
typedef enum tuner_register_enum
{
    TUNER_REG_BOOT = 0,    // Open Tuner Module's Power Supply
    TUNER_REG_RDS,        // Reset Variable
    TUNER_REG_END,        // Initialize Variable
}TUNER_REGISTER_ENUM;

// Resume Steps
typedef enum tuner_resume_enum
{
    TUNER_RESUME_INIT = 0,        // Resume Init: Initialize Band Variable
    TUNER_RESUME_BAND,            // Resume Band
    TUNER_RESUME_FREQ,            // Resume Frequency
    TUNER_RESUME_END,            // Resume End
}TUNER_RESUME_ENUM;

// Break Steps
typedef enum tuner_break_enum
{
    TUNER_BREAK_SORT = 0,     // Do Ams Save if necessary
    TUNER_BREAK_SEEK,                // Execute Break Currently State if it is necessary
    TUNER_BREAK_MUTE,            // Break Mute For Seek
    TUNER_BREAK_AF,                // Break AF 
    TUNER_BREAK_END,                // Break End
}TUNER_BREAK_ENUM;

//Seek Config Steps
typedef enum tuner_seek_config_enum
{
    TUNER_SC_VARIABLE = 0,     // Initialize seek related variables
    TUNER_SC_SET_FREQ,        // Set Start Frequency
    TUNER_SC_MODE,            // Set Seek Mode
    TUNER_SC_END,                // Seek Config End
}TUNER_SEEK_CONFIG_ENUM;

//Seek First Steps
typedef enum tuner_seek_first_enum
{
    TUNER_SF_PREPARE = 0,         // Initialize seek related variables
    TUNER_SF_CHECK,            // Get Quality
    TUNER_SF_END,                //Seek First End
}TUNER_SEEK_FIRST_ENUM;

//Check Quality Steps
typedef enum tuner_chk_qual_enum
{
    TUNER_CHK_QUAL_PREPARE = 0,         // Initialize check quality related variables
    TUNER_CHK_QUAL_CHECK,            // Get Quality and Checking!
    TUNER_CHK_QUAL_END,                //Check Quality End
}TUNER_CHK_QUAL_ENUM;

//Preview Control Steps
typedef enum tuner_preview_enum
{
    TUNER_PREVIEW_CONFIG = 0,    // Config: Exit Seek Mode to Preview    
    TUNER_PREVIEW_UNMUTE,        // Release Seek Mute
    TUNER_PREVIEW_PREVIEW,        // Set Preview
    TUNER_PREVIEW_REMAIN,        // 
    TUNER_PREVIEW_MUTE,            // Preview Overtime, Go back to Mute and go on Seek
    TUNER_PREVIEW_END,            // Preview End
}TUNER_PREVIEW_ENUM;

//4Tuner Middle Layer  Control Step Definitions : End
//............................................................................................


//............................................................................................
//4 Tuner Band&Preset Definitions : Start

// Band 
typedef enum tuner_band_enum
{
    TUNER_BAND_FM1 = 0,
    TUNER_BAND_FM2,
    TUNER_BAND_FM3,
    TUNER_BAND_AM1,
    TUNER_BAND_AM2,
    TUNER_BAND_OIRT1,
    TUNER_BAND_OIRT2,
    TUNER_BAND_END,
}TUNER_BAND_ENUM;

#define TUNER_FM_START        TUNER_BAND_FM1
#define TUNER_FM_END        TUNER_BAND_FM3
#define TUNER_AM_START    TUNER_BAND_AM1
#define TUNER_AM_END        TUNER_BAND_AM2
#define TUNER_OIRT_START    TUNER_BAND_OIRT1
#define TUNER_OIRT_END        TUNER_BAND_OIRT2
#define TUNER_BAND_MAX    TUNER_BAND_END

// Preset
typedef enum tuner_preset_enum
{
    TUNER_PRESET_NULL = 0,
    TUNER_PRESET_1,
    TUNER_PRESET_2,
    TUNER_PRESET_3,
    TUNER_PRESET_4,
    TUNER_PRESET_5,
    TUNER_PRESET_6,
    TUNER_PRESET_END,
}TUNER_PRESET_ENUM;

//snake20160915 
#ifdef D_TUNER_LIST
#define TUNER_PRESET_MAX 50
#else
#define TUNER_PRESET_MAX TUNER_PRESET_6
#endif
//Band Attribute Struct
typedef struct band_attri_struct
{
    uint8_t Preset;    // Band's Last Preset 
    uint16_t Freq;    // Band's Last Frequency
}BAND_ATTRI_STRUCT;

//4 Tuner Band&Preset Definitions : End
//............................................................................................


//............................................................................................
//4 Tuner Self-Used Struct: Start
// Default Struct of region
typedef struct tuner_region_struct 
{
    uint16_t BandFM[6];        // FM1 Default Preset
    uint16_t BandAM[6];        // AM1 Default Preset
    uint16_t BandOIRT[6];    // OIRT1 Default Preset
    uint8_t FMStep;
    uint8_t OIRTStep;
    uint8_t AMStep;
    uint8_t BandNum;
} TUNER_REGION_STRUCT; 

//Seek Station Struct
typedef struct tuner_ams_mem_struct
{
    uint16_t Freq;    //valid station's frequency
    uint8_t Qual;     // valid station's quality
}TUNER_AMS_MEM_STRUCT;

// Seek State struct
typedef struct tuner_seek_bit_struct
{
    bit_t bSeek:1;
    bit_t bAutoMemSeek:1;
    bit_t bAutoScan:1;
    bit_t bBreak:1;
    bit_t bTASeek:1;
    bit_t bPresetScan:1;
    bit_t bPause:1;//no use
    bit_t bPTYSeek:1;
}TUNER_SB_STRUCT;

typedef union tuner_seek_state_union
{
    uint8_t SsTotal;    // Seek State Total
    TUNER_SB_STRUCT sSsBitMap; //Seek State Bit Map
}TUNER_SS_UNION;

// Setting struct
#pragma pack(1)
typedef struct tuner_setting_bit_struct
{
    bit_t bLocDxSetting:1;
    bit_t bStereoSetting:1;
    bit_t bTaSetting:1;
    bit_t bAfSetting:1;
    bit_t bPtySetting:1;
    bit_t bRegSetting:1;
    bit_t bEonSetting:1;
    bit_t breserved:1;
}TUNER_SETTING_BIT_STRUCT;

#pragma pack(1)
typedef union tuner_setting_union
{
    uint8_t Total;    // Setting Total
    TUNER_SETTING_BIT_STRUCT sMap; //Setting Bit Map
}TUNER_SETTING_UNION;

#define VSCAN_BUFFER_MAX    100   
#define LIST_BUFFER_MAX   50   
#define T_OP_BUFFER_MAX    10
// Tuner Struct
typedef struct tuner_struct
{
    bit_t DevInit :1;        //yangyan --2014.08.07 1:Chip is ready 0: Wait chip
    bit_t PwrState:1;       //Power State
    uint8_t SysState;        // Tuner Task State
    uint8_t SysBakState;
    uint8_t ZoneState;  //Currently Zone State
    //4 Control Related Parameters
    uint8_t FuncStep;        // Mainly Function Control
    uint16_t FuncOverTime;    // OverTime of Function Control
    uint8_t FuncRetryCnt;        // Specific Step Error, Retry Counter    
    uint8_t MidLayerStep;            // MiddleLayer Control Step 
    uint8_t MidLayerDelay;        // MiddleLayer Control Delay
    uint16_t MidLayerOverTime;      // MiddleLayer Timeout Delay
    uint8_t DriverLayerStep;
    uint16_t DriverLayerDelay; 
    uint8_t BreakCtl;
    uint8_t GetInfoDelay;    //Get Info Control Delay

    uint8_t CommonCode;        // Common Command Code : Set Freq, Set Band...    
    uint8_t OpCtl;    
    uint8_t OpHead;
    uint8_t OpTail;
    uint8_t OpBuffer[T_OP_BUFFER_MAX];

    //Require Mute Control
    uint8_t ReqMuteStep;        //Require Mute Control Step
    uint8_t ReqMuteDelay;    //
    uint8_t ReqMuteLock;

    uint8_t LoadDatumRet;
    uint8_t LoadDatumDly;
    uint8_t LoadDatumCnt;

    uint8_t ModuleType; //Tuner Module Type
    //4 Tuner Attribute Related Parameters

    TUNER_SS_UNION uBakSeekState;        // Tuner Seek State 
    uint8_t BandStart;    //start band number of specific band
    uint8_t BandEnd;        //end band number of specific band
    uint16_t FreqMin;        // the minimum of currently Band and Region
    uint16_t FreqMax;    // the maximum of currently Band and Region
    uint8_t TuneStep;    // the Tune Step of currently Band and Region
    uint8_t BandNum;    // Band Number of Currently Region
    
    TUNER_AMS_MEM_STRUCT asAmsBuff[18];    //4Buffer Max Number should same as Max Preset number of One Band
    uint8_t SeekChkDelay;    // Check Quality delay after Set Frequency while Seeking
    uint16_t SeekStartFreq;    // Start Frequency of Seek
    uint8_t SeekPresetBak;    //Bak Preset While start AMS seek
    uint16_t DirectFreq;
    uint16_t SectFreq;
    
#ifdef D_TUNER_LIST
    uint8_t TmpListNum;
    uint16_t UpdateListBak;
    TUNER_AMS_MEM_STRUCT asTmpList[LIST_BUFFER_MAX];
#endif
	uint8_t AmsValidStaNum;
    
    TUNER_SS_UNION uSeekState;        // Tuner Seek State 
    
    uint16_t PscanDelay;

    uint8_t PtySelect;//Selected PTY ID

    //Stereo Parameters
    uint8_t StereoYesCnt;    //With Stereo Counter for
    uint8_t StereoNoCnt;    //No Stereo Counter for
    
    uint8_t SignalStr;    // Currently Signal Strength
    uint16_t PeriodicOut; 
    
    
    bit_t bSeekDirect:1;        // Seek Direction
    bit_t bBakSeekDirect:1;        // Seek Direction
    bit_t bGoodStation:1;    // Quality Result of the Seleced Station
    bit_t bReInitBand:1;    // Reinitialize Band Setting
    bit_t bSeekWrapAround:1;    // Need Wrap Around Flag
    bit_t bSyncData:1;
    bit_t bBakRdsSetting:1;
    bit_t bStereoMono:1;    // Stereo Mono Flag
    bit_t bDatumReady:1;    //parameter ready
    bit_t bTrigger:1;

    //4 Valid List Control...
    uint8_t ValidCtl;
    uint16_t ValidChkDly;    //Valid Check Delay between
    uint16_t ValidDelay;        //Delay between getting valid list
    uint16_t ValidCheckFreq;
    TUNER_AMS_MEM_STRUCT asValidBuff[VSCAN_BUFFER_MAX]; //Temporary Valid List Buffer
#ifdef D_VSCAN_QUEUE_BASE_ORDER     
    uint16_t ValidUpdateDelay;// Update newly Valid List Timer...// every 3S? 5S?
#endif//D_VSCAN_QUEUE_BASE_ORDER 
    bit_t bValidChecked:1;    //Checking Flag,for Parameter Reset usage
    
    //Rds Related
    uint8_t GetAfQualCtl;
    uint8_t GetAfQualNum;
    uint8_t GetAfQualDelay;

    uint8_t GetCfQualCtl;        //Get CF Quality Step
    uint8_t GetCfQualNum;    // Get Cf Qulity Number
    uint8_t GetCfQualDelay;

    uint8_t Smeter;
    uint8_t Fof;
    uint8_t Multipath;
    uint8_t AdjChannel;

    uint8_t FastAfSmeter;
    uint8_t FastAfAdjChannel;
    uint8_t FastAfMultipath;    
    uint8_t FastAfFof;        //FOF

    uint16_t TempSmeter;
    uint16_t TempAdjChannel;
    uint16_t TempMultipath;    
    uint16_t TempFof;        //FOF

    uint8_t DispPS[8];
    uint8_t DispRT[64];

    //Output Check
    uint8_t BandChk;
    uint8_t PresetChk;
    uint8_t SignalStrChk;
    uint8_t StateChk;
    uint16_t FreqChk;
    uint8_t SettingChk;
    uint8_t PtyChk;
    uint8_t PwrFreq;
    //4 Sub-Tuner Attribute Related Parameters
    //uint8_t SubFuncStep;        // Sub-Tuner Function Step
    //uint16_t SubFuncDelay;    // Sub-Tuner Function Delay    
    //uint8_t SubRetryCnt;        // Error Retry Counter
    //uint8_t SubDrvStep;        //Sub-Tuner Driver Layer Control Step
    //uint8_t SubDrvDelay;        // Sub-Tuner Driver Layer Controla Delay
}TUNER_STRUCT;

// Tuner Struct
typedef struct tuner_info_struct
{
    //Infoes...
    uint8_t CurrentBand;        // Currently Band
    uint8_t CurrentPreset;    // Currently Preset Number
    uint16_t CurrentFreq;        // Currently Frequency
    uint16_t Preset[TUNER_BAND_MAX][TUNER_PRESET_MAX];    // Currently Preset Buffer
}TUNER_INFO_STRUCT;

//Parameters will keep while MCU with power
typedef struct tuner_keep_struct
{
    BAND_ATTRI_STRUCT asBandAttri[TUNER_BAND_MAX]; // Currently Band Attribute    
    uint8_t ValidNumber;    //Valid Station Number
    uint8_t ValidHighlight;    //Highlight number of Valid list
    uint16_t ValidList[VSCAN_BUFFER_MAX];    //Valid List...    
    uint8_t PsList[TUNER_FM_END + 1][TUNER_PRESET_MAX][8];
#ifdef D_TUNER_LIST
    uint8_t ListNum;		//Number of Fm/Am List
    uint8_t FmListNum;
    uint8_t AmListNum;
    uint16_t FmList[LIST_BUFFER_MAX];
    uint16_t AmList[LIST_BUFFER_MAX];
#endif//D_TUNER_LIST

    //Settings..
    TUNER_SETTING_UNION sBakSetting;

    uint8_t Region;        // Tuner Region Setting
    uint8_t RdsSetting;    // Rds Setting: Rds On, Rds Off, RBDS On    
    uint8_t AntPwr;
    uint8_t AntGainAttn;
    
    bit_t bBakReg:1;   
    bit_t bPausestate:1; 
    bit_t bBakPause:1; 	
}TUNER_KEEP_STRUCT;

//Tuner Datum: Datum Saved in Eeprom
#pragma pack(1)
typedef struct tuner_datum_struct
{
    TUNER_SETTING_UNION sSetting;    //Setting FLag~~
    TUNER_INFO_STRUCT sInfo;
    uint16_t CheckSum;
}TUNER_DATUM_STRUCT;


//4 Tuner Self-Used Struct: End
//............................................................................................


//............................................................................................
//4 Tuner Self-Used Enum: Start
// Tuner System State
typedef enum tuner_system_state_enum
{
    TUNER_SYS_STARTUP = 0x00,        // Tuner System in INIT State
    TUNER_SYS_RUN,        // Tuner System is Running
    TUNER_SYS_PWROFF,    // Tuner System is Power Off
    TUNER_SYS_SLEEP,        // Tuner System Sleeped!!
}TUNER_SYSTEM_STATE_ENUM;

// Commonly Operations
typedef enum tuner_common_operate_enum
{
    TUNER_COMMON_NULL = 0,    // Nothing to Do
    TUNER_COMMON_FREQ,        // Commonly Operate: Set Frequency
    TUNER_COMMON_BAND,        // Commonly Operate: Set Band
    TUNER_COMMON_SEEK,        // Commonly Operate: Seek
    TUNER_COMMON_PSCAN,            // Commonly Preset Scan
    TUNER_COMMON_ST,            // Commonly Op: Stereo Setup switch
    TUNER_COMMON_BREAK,
    TUNER_COMMON_END,
}TUNER_COMMON_OPERATE_ENUM;

//Rds Seek Status
typedef enum rds_seek_status_enum
{
    RDS_SEEKSTATUS_SEEKING = 0,
    RDS_SEEKSTATUS_OK,
    RDS_SEEKSTATUS_FAIL,
}RDS_SEEK_STATUS_ENUM;

//4Tuner Self-Used Enum: End
//............................................................................................



//............................................................................................
//3 Public Definitions : Start

// Tuner Mode 
typedef enum tuner_mode_enum
{
    TUNER_MODE_PWRDN = 0,
    TUNER_MODE_PRESET,    
    TUNER_MODE_SEEK,
}TUNER_MODE_ENUM;

#define QUAL_CHK_NORMAL    1    //Read Signal Quality
#define QUAL_CHK_SEEK        0    //Read Seek Quality

// Tune/Seek Direction
typedef enum tuner_dirction_enum
{
    DIRECTION_UP = 0,
    DIRECTION_DN,
}TUNER_DIRECTION_ENUM;

// Mute Steps
typedef enum tuner_mute_enum
{
    TUNER_MUTE_REQ = 0,
    TUNER_MUTE_CHK,
    TUNER_MUTE_END,
}TUNER_MUTE_ENUM;

// Rds Setting
typedef enum rds_setting_enum
{
    RDS_SET_OFF = 0,
    RDS_SET_RDS,
    RDS_SET_RBDS,
}RDS_SETTING_ENUM;

//Stereo Setting
#define STEREO_MONO     1    //Stereo Setting: Force Mono
#define STEREO_AUTO    0    //Stereo Setting:Audio

//DX LOC Setting
#define TUNER_LOC    1    //Tuner Setting: LOC
#define TUNER_DX    0    //Tuner Setting: DX

//TA Setting
#define TA_SET_ON    1    
#define TA_SET_OFF    0

//AF Setting
#define AF_SET_ON    1
#define AF_SET_OFF     0

//REG Setting
#define REG_SET_ON        1
#define REG_SET_OFF        0

//PTY Setting
#define PTY_SET_OFF        0
#define PTY_SET_ON        1

//EON Setting
#define EON_SET_OFF        0
#define EON_SET_ON        1

//Tuner Mute ID
#define TUNER_MID_NULL     0
#define TUNER_MID_SEEK         1
#define TUNER_MID_OP        2


//3Public Definitions : End
//............................................................................................


//--------------------------------------------------------------
//3 Function Declare :Start

EXTERN TUNER_STRUCT sTuner;

//Un-Initial Parameters: Tuner Informations
#pragma section data "no_init" begin    
EXTERN TUNER_KEEP_STRUCT sTunerKeep;
EXTERN TUNER_DATUM_STRUCT sTunerDat;
#pragma section data "no_init" end
extern const TUNER_REGION_STRUCT sTunerRegion[];

EXTERN uint8_t Tuner_PowerOn(void);
EXTERN uint8_t Tuner_InitRegister(void);
EXTERN uint8_t Tuner_ResumeLast(void);
EXTERN uint8_t Tuner_OperateBreak(void);
EXTERN uint8_t Tuner_SeekConfig(uint8_t Mode);
EXTERN uint8_t Tuner_SeekFirst(void);
EXTERN uint8_t Tuner_ChkQual(uint8_t ChkMode);
EXTERN uint8_t Tuner_RdsSeekStatus(void);
EXTERN uint8_t Tuner_Preview(void);
EXTERN uint8_t Tuner_SaveAll(void);
EXTERN uint8_t Tuner_PowerOff(void);
EXTERN void Tuner_VariableCheck(void);
EXTERN void Tuner_VariableReset(void);
EXTERN void Tuner_VariableInit(void);
EXTERN void Tuner_BandInit(void);
EXTERN void Tuner_GotoMidStep(uint8_t x);
EXTERN void Tuner_StepChangeFreq(uint8_t Direct);
EXTERN void Tuner_SortPreset(void);
EXTERN uint8_t Tuner_BreakAF(void);
EXTERN void Tuner_InsertNewStation(TUNER_AMS_MEM_STRUCT *psDest,TUNER_AMS_MEM_STRUCT *psNewStation, uint8_t Num);
EXTERN void Tuner_SortStationAccordFreq(TUNER_AMS_MEM_STRUCT *psDest,uint8_t Num);
EXTERN uint8_t Tuner_ReqMute(uint8_t Mode, uint8_t MuteId);
EXTERN uint8_t Tuner_CheckPreset(uint16_t u16Freq);

//3 Function Declare :End
//--------------------------------------------------------------


//--------------------------------------------------------------
//3  Self-Definitions:Start

#define FM_FREQ_MIN sTunerRegion[sTunerKeep.Region].BandFM[0]
#define FM_FREQ_MAX sTunerRegion[sTunerKeep.Region].BandFM[5]
#define AM_FREQ_MIN sTunerRegion[sTunerKeep.Region].BandAM[0]
#define AM_FREQ_MAX sTunerRegion[sTunerKeep.Region].BandAM[5]

/*
#define FM_FREQ_MIN 8750
#define FM_FREQ_MAX 10800
#define AM_FREQ_MIN 531
#define AM_FREQ_MAX 1629
*/
#define OIRT_FREQ_MIN sTunerRegion[sTunerKeep.Region].BandOIRT[0]
#define OIRT_FREQ_MAX sTunerRegion[sTunerKeep.Region].BandOIRT[5]


#define TaSetting        sTunerDat.sSetting.sMap.bTaSetting
#define AfSetting        sTunerDat.sSetting.sMap.bAfSetting
#define EonSetting    sTunerDat.sSetting.sMap.bEonSetting
#define RegSetting    sTunerDat.sSetting.sMap.bRegSetting
#define LocDxSetting    sTunerDat.sSetting.sMap.bLocDxSetting
#define StereoSetting    sTunerDat.sSetting.sMap.bStereoSetting
#define PtySetting    sTunerDat.sSetting.sMap.bPtySetting

//3 Self-Definitions:End
//--------------------------------------------------------------

#undef EXTERN

#endif

