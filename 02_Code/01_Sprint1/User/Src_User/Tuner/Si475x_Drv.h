/**********************************************************
 * @file        Si475x_Drv.h
 * @purpose    Definition of Si475x Driver
 * @version    0.01
 * @date        26.Sep. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        26.Sep.2012              v0.01        created
 *  
  **********************************************************/
#ifndef SI475X_DRV_H
#define SI475X_DRV_H

#ifdef SI475X_DRV_C
#include "Global.h"
#include "I2C_Driver.h"

#define EXTERN 
#else
#define EXTERN extern 
#endif//SI475X_DRV_C


//Si475x Common Command Register 
#define SI475X_COM_POWER_UP            0x01
#define SI475X_COM_PART_INFO            0x02
#define SI475X_COM_POWER_DOWN        0x11
#define SI475X_COM_FUNC_INFO            0x12
#define SI475X_COM_SET_PROPERTY        0x13
#define SI475X_COM_GET_PROPERTY        0x14
#define SI475X_COM_GET_INT_STATUS        0x15
#define SI475X_COM_AGC_STATUS            0x17
#define SI475X_COM_AUDIO_PIN_CFG        0x1B
#define SI475X_COM_INTB_PIN_CFG        0x1C

//Si475x FM Command Register
#define SI475X_FM_TUNE_FREQ        0x30 //Tune FM receiver
#define SI475X_FM_SEEK_START        0x31
#define SI475X_FM_RSQ_STATUS        0x32
#define SI475X_FM_ACF_STATUS        0x35
#define SI475X_FM_RDS_STATUS        0x36
#define SI475X_FM_RDS_BLOCKCNT    0x37    

//Si475x FM Command Register
#define SI475X_AM_TUNE_FREQ        0x40 //tune AM receiver to a frequency in 1Khz Steps
#define SI475X_AM_SEEK_START        0x41 //    
#define SI475X_AM_RSQ_STATUS        0x42 //
#define SI475X_AM_ACF_STATUS        0x45 //
#define SI475X_AM_AGC_STATUS        0x47 //


// Audio Config 
#define AUDIO_CFG_NO_MODIFY    0    // Not Modify behavior
#define AUDIO_CFG_DISABLE        1    // Disable Audio Output
#define AUDIO_CFG_ENABLE        2    // Enable Audio Output
#define AUDIO_CFG_MPX            3    // LOUT For MPX, ROUT Disabled




typedef struct si475x_struct
{
    uint8_t DrvStep;        //Driver Control Step
    uint8_t DrvResult;        //Driver Execute Result 
    uint8_t DrvID;
    uint8_t DrvState;
}SI475X_STRUCT;


//............................................................................................
//4 Si475x Control Enum : Start

//Si475x Driver Type
typedef enum si475x_driver_type_enum
{
    SI475X_IIC_IDLE = 0,
    SI475X_IIC_POWER_UP,
    SI475X_IIC_CONFIG_AUDIO_PIN,
}SI475X_DRIVER_TYPE_ENUM;

//Si475x Driver  Status
typedef enum si475x_drv_status_enum
{
    SI475X_DRV_IDLE = 0,
    SI475X_DRV_BUSY,
    SI475X_DRV_ERROR,
}SI475X_DRV_STATUS_ENUM;

//4 Si475x Control Enum : End
//............................................................................................


#define Si475x_IIC_CheckBus()        I2C_Busy(I2C1)    
#define Si475x_IIC_CallBack(x)     I2C_CallBack(I2C1,(x))

//--------------------------------------------------------------
//3  Declare :Start

EXTERN SI475X_STRUCT sSi475x;
EXTERN uint8_t Si475x_WriteCommon(SI475X_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num);

//3  Declare :End
//--------------------------------------------------------------



#undef EXTERN

#endif//SI475X_DRV_H

