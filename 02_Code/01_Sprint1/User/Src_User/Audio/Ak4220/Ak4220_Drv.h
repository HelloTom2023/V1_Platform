/**********************************************************
 * @file        Ak4220_Drv.h
 * @purpose    Definition of Ak4220 Driver
 * @version    0.01
 * @date        17.Sep. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        17.Sep.2012              v0.01        created
 *  
  **********************************************************/
#ifndef AK4220_DRV_H
#define AK4220_DRV_H


#ifdef AK4220_DRV_C
#define EXTERN 
#else
#define EXTERN extern 
#endif//AK4220_DRV_C

//............................................................................................
//4 Ak4220 IIC Related---Start

/*
0---0---1---0---0---CAD1---CAD0---RW
*/
/*------------------------------
CAD1           CAD0              CS Address
0                  0                   0x20   Used!
0                  1                   0x22    
1                  0                   0x24
1                  1                   0x26    
--------------------------------*/
#define AK4220_CS_ADDR     0x20    //Ak4220 Chip Selection Address     

#define AK4220_IIC    I2C2 //Used I2c Port
#define Ak4220_WriteDat(Dat,Num,CallBack)   I2C_Write(AK4220_IIC,AK4220_CS_ADDR,FALSE,Dat,Num,TRUE,CallBack,I2C_74KBPS)
#define Ak4220_WritePdat(Dat,Num,CallBack) I2C_Write(AK4220_IIC,AK4220_CS_ADDR,TRUE,Dat,Num,TRUE,CallBack,I2C_74KBPS)
#define Ak4220_ReadDat(Dat,Num,CallBack)    I2C_ReadFromSubAdd(AK4220_IIC,AK4220_CS_ADDR,0x00,FALSE,Dat,Num,TRUE,CallBack,I2C_74KBPS)
#define Ak4220_ReadPdat(Dat,Num,CallBack) I2C_ReadFromSubAdd(AK4220_IIC,AK4220_CS_ADDR,0x00,TRUE,Dat,Num,TRUE,CallBack,I2C_74KBPS)

//4 Ak4220 IIC Related---End
//............................................................................................

//-------------------------------------------------------
//2 Ak4220 Related Def: Start
// AK4220 Register Address
#define AK4220_REG_PD_RST        0    // power down & reset
#define AK4220_REG_INPUT1        1    // Input Selector 1        
#define AK4220_REG_INPUT2        2    // Input Selector 2    
#define AK4220_REG_INPUT3        3    // Input Selector 3    
#define AK4220_REG_DET1          4    // Detection Control 1
#define AK4220_REG_DET2          5    // Detection Control 2
#define AK4220_REG_DET3          6    // Detection Control 3
#define AK4220_REG_GPIO          7    // Parallel Output
#define AK4220_REG_DETECTION     8    // AV Detection        // Read Only Register

//Ak4220 Output Enum
typedef enum ak4220_out_enum
{
    AK4220_OUT_A1,        	// Audio Output Channel 1(Rear channel1)
    AK4220_OUT_A2,		// Rear Channel 2
    AK4220_OUT_A3,		// Front Channel
    AK4220_OUT_V1,        	// Video Output Channel 1(Front Channel)
    AK4220_OUT_V2,    	//Rear Channel 1
    AK4220_OUT_V3,		//Rear Channel 2
    AK4220_OUT_OFF,
}AK4220_OUT_ENUM;

//AK4220 Input Enum
typedef enum ak4220_ain_enum
{
    AK4220_AIN_OFF = 0,        
    AK4220_AIN_1,        // Audio Input Channel 1
    AK4220_AIN_2,
    AK4220_AIN_3,
    AK4220_AIN_4,
    AK4220_AIN_5,
    AK4220_AIN_6,
    AK4220_AIN_7,
}AK4220_AIN_ENUM;

// Video Input Enum
typedef enum ak4220_vin_enum
{
    AK4220_VIN_OFF = 0,        
    AK4220_VIN_1,        // Video Input Channel 1
    AK4220_VIN_2,
    AK4220_VIN_3,
    AK4220_VIN_4,
    AK4220_VIN_5,
    AK4220_VIN_6,
    AK4220_VIN_NA,
}AK4220_VIN_ENUM;

//Gpio Enum
typedef enum ak4220_gpio_enum
{
    AK4220_GPIO_0 = 0,        // GPIO 0
    AK4220_GPIO_1,
    AK4220_GPIO_2,
    AK4220_GPIO_3,
    AK4220_GPIO_4,
}AK4220_GPIO_ENUM;

//2 Ak4220 Related Def: End
//-------------------------------------------------------


//............................................................................................
//4 Ak4220 Control Enum : Start

//Ak4220 Driver Type
typedef enum ak4220_driver_type_enum
{
    AK4220_IIC_IDLE = 0,
    AK4220_IIC_REGISTER,        // Initialize Registers
    AK4220_IIC_SET_GPIO,        // Control Gpio
    AK4220_IIC_UPDATE_ALL,    // Update All
    AK4220_IIC_SWITCH_ACH,    // Switch Audio Channel
    AK4220_IIC_SWITCH_VCH,    // Switch Video Channel
    AK4220_IIC_SET_MIX,        //Set Mix Src Set Mix Route
    AK4220_IIC_READ,            //Read Status
}AK4220_DRIVER_TYPE_ENUM;

//Ak4220 Driver  Status
typedef enum ak4220_drv_status_enum
{
    AK4220_DRV_IDLE = 0,
    AK4220_DRV_BUSY,
    AK4220_DRV_ERROR,
}AK4220_DRV_STATUS_ENUM;

//4 Ak4220 Control Enum : End
//............................................................................................

#pragma pack(1)
//AK4220 Struct
typedef struct ak4220_struct
{
    uint8_t Ready;     //device ready to control    
    
    //Driver Control
    uint8_t DrvStep;        //Driver Control Step
    uint8_t DrvResult;    //Driver Execute Result 
    uint8_t DrvID;
    uint8_t DrvState;
    uint8_t DrvOverTime;
    uint8_t DrvBuff[10];
    uint8_t DrvRead[8];
    // Ak Control
    uint8_t Step;
    uint8_t Delay;
    //Register Buffer
    uint8_t RegBuff[8];
}AK4220_STRUCT;

#define AK4220_TICK_BASE        2
#define Ak4220Delay(x)            (x)/AK4220_TICK_BASE

//--------------------------------------------------------------
//3  Declare :Start

EXTERN AK4220_STRUCT sAk4220;

EXTERN uint8_t Ak4220_CallBack_Common(uint8_t Result);
EXTERN uint8_t Ak4220_WriteCommon(AK4220_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num);
EXTERN uint8_t Ak4220_ReadCommon(void);

//3  Declare :End
//--------------------------------------------------------------


#define AK4220_GPIO_H    1
#define AK4220_GPIO_L    0

#define REG_DAT_PD_RST        sAk4220.RegBuff[0]// power down & reset
#define REG_DAT_INPUT1        sAk4220.RegBuff[1]    // Input Selector 1        
#define REG_DAT_INPUT2        sAk4220.RegBuff[2]    // Input Selector 2    
#define REG_DAT_INPUT3        sAk4220.RegBuff[3]    // Input Selector 3    
#define REG_DAT_DET1        sAk4220.RegBuff[4]    // Detection Control 1
#define REG_DAT_DET2        sAk4220.RegBuff[5]    // Detection Control 2
#define REG_DAT_DET3        sAk4220.RegBuff[6]    // Detection Control 3
#define REG_DAT_GPIO        sAk4220.RegBuff[7]    // Parallel Output
#define REG_DAT_DETECTION    sAk4220.RegBuff[8]    // AV Detection

#define DEFAULT_PD_RST            0x03//0x13    //PW 0; BIAS ON;SAGN OFF to DC Output;
#define DEFAULT_INPUT1            0x00    //Output A1 V1: OFF        
#define DEFAULT_INPUT2            0x00    //Output A2 V2: OFF    
#define DEFAULT_INPUT3            0x00    //Output A3 V3: OFF    
#define DEFAULT_DET1            0x00      // Detection Control 1
#define DEFAULT_DET2            0x40    // Detection Control 2
#define DEFAULT_DET3            0xB2    // Int Sel : VDET, VDMD Sel: 1
#define DEFAULT_GPIO            0x1F    // Parallel Output
#define DEFAULT_DETECTION        0x00    //Read Register, It is Ignored to write

#define INT_V_AL_AR    0        // Int trigger: Video or Audio L or Audio R
#define INT_V_AL        1        // Int trigger: Video or Audio L
#define INT_V_AR    2        // Int trigger: Video or Audio R
#define INT_V        3        // Int trigger: Video
#define INT_AL_AR    4        // Int trigger: Audio L or Audio R
#define INT_AL        5        // Int trigger: Audio L 
#define INT_AR        6        // Int trigger: Audio R
#define INT_HI_Z        7        // Int pin = "Hi-Z"


#undef EXTERN

#endif//AK4220_DRV_H

