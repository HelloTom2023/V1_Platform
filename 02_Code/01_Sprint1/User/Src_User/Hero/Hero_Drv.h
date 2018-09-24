/**********************************************************
 * @file        Hero_Drv.h
 * @purpose    Definition of Hero Driver
 * @version    0.01
 * @date        30.Aug. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        30.Aug.2012              v0.01        created
 *  
  **********************************************************/
#ifndef HERO_DRV_H
#define HERO_DRV_H


#ifdef D_AUDIO_ASP_HERO
#ifdef HERO_DRV_C
#define EXTERN
#else
#define EXTERN extern 
#endif


/*------------------------------
HOST_WS_P   HOST_BCK_P   CS Address
       0                  0                 C0  Used!
       0                  1                 C2
       1                  0                 C4
       1                  1                 C6     
--------------------------------*/
#define HERO_CS_ADDR     0xC0    // Chip Select Address

//..................................................................................................
//4  DiRaNa IIC Related: Start

#define HERO_IIC    I2C1 //Used I2c Port
#define Hero_WriteDat(Dat,Num,CallBack) I2C_Write(HERO_IIC,HERO_CS_ADDR,FALSE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Hero_WritePdat(Dat,Num,CallBack) I2C_Write(HERO_IIC,HERO_CS_ADDR,TRUE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Hero_ReadDat(Reg,Dat,Num,CallBack)    I2C_ReadFromSubAdd(HERO_IIC,HERO_CS_ADDR,Reg,FALSE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Hero_ReadPdat(Reg,Dat,Num,CallBack) I2C_ReadFromSubAdd(HERO_IIC,HERO_CS_ADDR,Reg,TRUE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Hero_DirectReadDat(Dat,Num,CallBack)  I2C_Read(HERO_IIC,HERO_CS_ADDR,TRUE,Dat,Num,TRUE,CallBack,I2C_350KBPS)

//4  DiRaNa IIC Related: End
//...................................................................................................


//...................................................................................................
//4 Typedef Struct&Enum : Start

//Hero Driver  Status
typedef enum hero_drv_status_enum
{
    HERO_DRV_IDLE = 0,
    HERO_DRV_BUSY,
    HERO_DRV_ERROR,
}HERO_DRV_STATUS_ENUM;

// Hero Driver Type
typedef enum hero_driver_type_enum
{
    HERO_IIC_NULL = 0,
    HERO_IIC_SET_VOL,
    HERO_IIC_SET_BASS,
    HERO_IIC_SET_MID,
    HERO_IIC_SET_TREBLE,
    HERO_IIC_SET_BALANCE,
    HERO_IIC_SET_FADER,    
    HERO_IIC_SET_BF,
    HERO_IIC_INIT_AUDIO_A,
    HERO_IIC_INIT_RADIO_A,
    HERO_IIC_INIT_RADIO_A2,
    HERO_IIC_SPURIOUS_SIGNAL,
    HERO_IIC_IIS_VCO,
    HERO_IIC_KEYCODE,
    HERO_IIC_USECASE,
    HERO_IIC_AUDIO_POINTER,
    HERO_IIC_ACTIVE_DEVICE,
    HERO_IIC_INIT_AUDIO_B,
    HERO_IIC_INIT_RADIO_B,
    HERO_IIC_INIT_AUDIO_C,
    HERO_IIC_INIT_DAC,
    HERO_IIC_INIT_PERIPHERAL,    // Config IN Mode : SPDIF, AD, I2S
    HERO_IIC_CONFIG_GPIO,
    HERO_IIC_RADIO_CONFIG,
    HERO_IIC_RADIO_INIT,
    HERO_IIC_INIT_ADC,
    HERO_IIC_INIT_SCALINGINT,
    HERO_IIC_INIT_CHANNEL_GAIN,
    HERO_IIC_SET_CHANNEL_GAIN,
    HERO_IIC_SOFTMUTE,
    HERO_IIC_SET_PS_INPUT,    // Primary ,Secondary Input
    HERO_IIC_SET_NAV_INPUT,
    HERO_IIC_SET_PHONE_INPUT,
    HERO_IIC_SET_ANALOG_MODE,
    HERO_IIC_EASYP_CHK,
    
    HERO_IIC_AUDIO_START,
    HERO_IIC_LIMITER_CONFIG_SEL,
    HERO_IIC_LIMITER_SET,
    HERO_IIC_FLAG_GENE_SET,
    HERO_IIC_SOFT_CLIP_DETECT,
    HERO_IIC_SET_LOUDNESS,
    HERO_IIC_DRV_SET_VOL,
    HERO_IIC_SET_NAV_PHONE_VOL,
    HERO_IIC_INIT_VOL,
    HERO_IIC_SET_GEQ,
    HERO_IIC_SET_PEQ,
    HERO_IIC_DELAY_LINE,
    HERO_IIC_SET_PHASE,
    HERO_IIC_SET_ULTRA_BASS,
    HERO_IIC_SET_SW,
    HERO_IIC_SRC_SCALER,
    HERO_IIC_DC_FILTER,
    HERO_IIC_INIT_CLICKCLACK,
    HERO_IIC_AUDIO_END,
    
    HERO_IIC_NAV_PHONE_FILTER,
    HERO_IIC_FASTMUTE_CONFIG,
    HERO_IIC_RADIO_INIT_ALL,
    HERO_IIC_RADIO_SET_BAND,
    HERO_IIC_RADIO_SET_FREQ,
    HERO_IIC_RADIO_GET_QUAL,
    HERO_IIC_RADIO_GET_INFO,
    HERO_IIC_RADIO_CHG_MODE,
    HERO_IIC_UPDATEPLL,
    HERO_IIC_BEEPINIT,
    HERO_IIC_BEEPSTOP,
    HERO_IIC_SET_IMPOSE,
    HERO_IIC_SET_CHIME_VOL,
    HERO_IIC_SET_CHIMEMODE,
    HERO_IIC_SWITCH_ST,        //Switch Force Mono Setting
    HERO_IIC_RDS_FETCH_BLOCK,
    HERO_IIC_RDS_RESET_DECODER,
    HERO_IIC_AF_UPDATE,
    HERO_IIC_AF_JUMP,
    HERO_IIC_SET_BW,
    HERO_IIC_GET_AF_QUAL,
    HERO_IIC_GET_CF_QUAL,
    
    
}HERO_DRIVER_TYPE_ENUM;

//Hero Control Struct
#pragma pack(1)
typedef struct hero_struct
{
    //Init State
    bit_t InitDone:1;
    
    // Driver Control Parameters
    uint8_t DrvState;            // Driver Control State Flag: Busy, Idle, Error
    HERO_DRIVER_TYPE_ENUM DrvID;            // Current Executing Drv Function ID
    uint8_t DrvLayerStep;        // Driver Layer Control Step    
    uint8_t I2cResult;            // I2c  Control Result
    uint8_t DrvLock;    //Flag to Sign: IIC is locked, it can be used only while unlocked
    HERO_DRIVER_TYPE_ENUM LockID;            // Lock ID
#ifdef D_HERO_V03
    uint8_t DrvBuffer[220];    
#else
    uint8_t DrvBuffer[40];
#endif
    // Control Step&Delay
    uint8_t ErrId;

    uint8_t SubStep;    //Hero Control SubStep, Sublayer of a Step
    uint8_t ThirdLayerStep;    //Hero Control ThirdLayerStep        
    uint8_t MemTblStep;
    uint8_t LimiterFGS;
    uint8_t ScratchStep;
    uint8_t FastMuteConfig;

    uint16_t BassCoefBuffer[11];    //Temporary coefficient for Bass
    uint16_t MidCoefBuffer[7];
    uint16_t TrebleCoefBuffer[6];
    uint16_t GeqCoefBuffer[7];    //Load temporary coefficient for Graphic Equalizer
    uint16_t SwCoefBuffer[10];    //Load temporary coefficient for Subwoofer
    uint16_t XoverCoefBuffer[10];    //Temporary coefficient for Xover
    // Buffer
    uint8_t ReadBuff[16];    //
    uint8_t ReadBackChk[4];    
}HERO_STRUCT;

//4 Typedef Struct&Enum : End
//...................................................................................................



#define HERO_TICK_BASE    2
#define HeroDelay(x)        (x)/HERO_TICK_BASE


//--------------------------------------------------------------
//3  Declare :Start

EXTERN HERO_STRUCT sHero;

EXTERN uint8_t Hero_CheckDrvState(HERO_DRIVER_TYPE_ENUM DrvID);
EXTERN uint8_t Hero_CallBack_Common(uint8_t eState);
EXTERN void Hero_ClearDrvState(uint8_t Result);

//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN

#endif //D_AUDIO_ASP_HERO

#endif//HERO_DRV_H

