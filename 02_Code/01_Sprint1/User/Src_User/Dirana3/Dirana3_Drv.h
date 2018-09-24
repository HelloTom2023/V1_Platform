/**********************************************************
 * @file        Dirana3_Drv.h
 * @purpose    Definition of Dirana Driver
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
#ifndef DIRANA3_DRV_H
#define DIRANA3_DRV_H


#ifdef DIRANA3_DRV_C
#define EXTERN
#else
#define EXTERN extern 
#endif//DIRANA3_DRV_C

//...................................................................................................
//4  DiRaNa IIC Related: Start

#define DIRANA_CS_ADDR     0x38    // Chip Select Address

#define DIRANA_IIC    I2C1 //Used I2c Port
#define Dirana_WriteDat(Dat,Num,CallBack) I2C_Write(DIRANA_IIC,DIRANA_CS_ADDR,FALSE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Dirana_WritePdat(Dat,Num,CallBack) I2C_Write(DIRANA_IIC,DIRANA_CS_ADDR,TRUE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Dirana_ReadDat(Reg,Dat,Num,CallBack)    I2C_ReadFromSubAdd(DIRANA_IIC,DIRANA_CS_ADDR,Reg,FALSE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Dirana_ReadPdat(Reg,Dat,Num,CallBack) I2C_ReadFromSubAdd(DIRANA_IIC,DIRANA_CS_ADDR,Reg,TRUE,Dat,Num,TRUE,CallBack,I2C_350KBPS)

//4  DiRaNa IIC Related: End
//...................................................................................................

//...................................................................................................
//4 Typedef Struct&Enum : Start

//Dirana Driver  Status
typedef enum dirana_drv_status_enum
{
    DIRANA_DRV_IDLE = 0,
    DIRANA_DRV_BUSY,
    DIRANA_DRV_ERROR,
}DIRANA_DRV_STATUS_ENUM;

// Dirana Driver Type
typedef enum dirana_driver_type_enum
{
    DIRANA_IIC_NULL = 0,
    DIRANA_IIC_KEYCODE, 
    DIRANA_IIC_PREPARE, //Prepare for Boot
    DIRANA_IIC_PATCH1,
    DIRANA_IIC_PATCH2,
    DIRANA_IIC_PATCH3,
    DIRANA_IIC_PATCH4,
    DIRANA_IIC_IMAGE_PATCH,    //Load Image or Patch
    DIRANA_IIC_START_APP,    //start application
    DIRANA_IIC_REQ_INIT,
    DIRANA_IIC_ALIGNMENT,
    DIRANA_IIC_START_PLL0,    //start AD PLL0
    DIRANA_IIC_START_PLL1,    //start AD PLL1
    DIRANA_IIC_SPECIAL_P,
    DIRANA_IIC_INIT_RADIO,
    DIRANA_IIC_SPECIAL_S,
    DIRANA_IIC_ENABLE_SRC,    //Enable Sample Rate Converter
    DIRANA_IIC_SET_ASR, //Set Audio Sample Rate
    DIRANA_IIC_GPIO_CONFIG,    //Set GPIO Feature
    DIRANA_IIC_INIT_PERIPHERAL,
    DIRANA_IIC_CONFIG_HOST,    //Config Host IIS Mode
    DIRANA_IIC_INIT_SCALING,
    DIRANA_IIC_SRC_SCALING,
    DIRANA_IIC_INIT_CHANNEL_GAIN,
    DIRANA_IIC_SET_CHANNEL_GAIN,
    DIRANA_IIC_AUDIO_POINTER,
    DIRANA_IIC_SOFTMUTE,
    DIRANA_IIC_SET_VOL,
    DIRANA_IIC_SET_NAV_PHONE_VOL,
    DIRANA_IIC_SET_INPUT,
    DIRANA_IIC_UPDATE_PLL,
    DIRANA_IIC_SET_CHIMEMODE,
    DIRANA_IIC_SET_CHIME_VOL,
    DIRANA_IIC_BEEPINIT,
    DIRANA_IIC_BEEPSTOP,
    DIRANA_IIC_SET_IMPOSE,
    DIRANA_IIC_SET_BASS,
    DIRANA_IIC_SET_MID,
    DIRANA_IIC_SET_TREBLE,
    DIRANA_IIC_SET_BAL,    //Set Balance
    DIRANA_IIC_SET_FAD,    //Set Fader
    DIRANA_IIC_SET_BF,        //Set Balance Fader
    DIRANA_IIC_SET_DCFILTER,
    DIRANA_IIC_DELAY_LINE,    //Set Delay Line
    DIRANA_IIC_SET_GEQ,    //Set Graphic Equazer
    DIRANA_IIC_SET_PHASE,    //Set Phase Shifter
    DIRANA_IIC_SET_LOUDNESS,    //Set Loudness
    DIRANA_IIC_SET_SW,    //Set Subwoofer
    DIRANA_IIC_SET_PEQ,    //Set Parametric Equalizer    
    DIRANA_IIC_SET_XOVER,    //Set Over Cross
    DIRANA_IIC_SET_ULTRA_BASS,    //Set Ultra Bass
    DIRANA_IIC_INIT_CLICKCLACK,
    DIRANA_IIC_DE_EMPHASIS,
    DIRANA_IIC_SET_SOFTCLIPPER,
    DIRANA_IIC_AUDIO_END,
    
    DIRANA_IIC_RADIO_SET_BAND,
    DIRANA_IIC_RADIO_SET_FREQ,
    DIRANA_IIC_RADIO_SET_ANT,
    DIRANA_IIC_RADIO_CHG_MODE,
    DIRANA_IIC_RADIO_GET_QUAL,
    DIRANA_IIC_SWITCH_ST,
    DIRANA_IIC_RADIO_GET_INFO,
    DIRANA_IIC_RDS_FETCH_BLOCK,
    DIRANA_IIC_RDS_RESET_DECODER,
    DIRANA_IIC_AF_UPDATE,
    DIRANA_IIC_AF_JUMP,
    DIRANA_IIC_SET_BW,
    DIRANA_IIC_GET_AF_QUAL,
    DIRANA_IIC_GET_CF_QUAL,
    
}DIRANA_DRIVER_TYPE_ENUM;

//Dirana Control Struct
#pragma pack(1)
typedef struct dirana_struct
{
    //Init State
    bit_t InitDone:1;
    
    // Driver Control Parameters
    uint8_t DrvState;            // Driver Control State Flag: Busy, Idle, Error
    DIRANA_DRIVER_TYPE_ENUM DrvID;            // Current Executing Drv Function ID
    uint8_t DrvLayerStep;        // Driver Layer Control Step    
    uint8_t I2cResult;            // I2c  Control Result
    uint8_t DrvLock;    //Flag to Sign: IIC is locked, it can be used only while unlocked
    DIRANA_DRIVER_TYPE_ENUM LockID;            // Lock ID
    uint8_t DrvBuffer[40];

    // Buffer
    uint8_t ReadBuff[25];    //
    uint8_t ReadBackChk[4];    
    // Control Step&Delay
    uint16_t OverTime;    //Over Time Counter
    uint8_t SubStep;    //Dirana Control SubStep, Sublayer of a Step
    uint8_t ThirdLayerStep;    //Dirana Control ThirdLayerStep        

    //Parameters
    uint16_t GeqCoefBuffer[7];    //Load temporary coefficient for Graphic Equalizer
    uint16_t SwCoefBuffer[10];    //Load temporary coefficient for Subwoofer
    uint16_t PeqCoefBuffer[10];    //Temporary coefficient for Parametric Equalizer
    uint16_t BassCoefBuffer[11];    //Temporary coefficient for Bass
    uint16_t MidCoefBuffer[7];
    uint16_t TrebleCoefBuffer[6];
    uint16_t XoverCoefBuffer[10];    //Temporary coefficient for Xover
    //Special Control Step
    uint8_t BootStep;
    uint8_t MemTblStep;     //Memory Table Write Control Step
    uint8_t ScratchStep;    //Scratch Write Control Step
}DIRANA_STRUCT;

//4 Typedef Struct&Enum : End
//...................................................................................................



#define DIRANA_TICK_BASE    2
#define DiranaDelay(x)        (x)/DIRANA_TICK_BASE


//--------------------------------------------------------------
//3  Declare :Start

EXTERN DIRANA_STRUCT sDirana;

EXTERN uint8_t Dirana_CheckDrvState(DIRANA_DRIVER_TYPE_ENUM DrvID);
EXTERN void Dirana_ClearDrvState(uint8_t Result);
EXTERN uint8_t Dirana_CallBack_Common(uint8_t Result);

//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN

#endif//DIRANA3_DRV_H


