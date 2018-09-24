/**********************************************************
 * @file        Tef700x_Drv.h
 * @purpose    Definition of Tef700x Driver
 * @version    0.01
 * @date        22.Aug. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        22.Aug.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TEF700X_DRV_H
#define TEF700X_DRV_H


#ifdef TEF700X_DRV_C
#define EXTERN 
#else
#define EXTERN extern 
#endif//TEF700X_DRV_C

//............................................................................................
//4 Tef700x IIC Related---Start

/*
1---1---0---0---1---x---x---RW
*/
/*------------------------------
ADDRESS                         CS Address
Grounded               00             0xC8   Used!
Floating                 01                0xCA    
Connect to Vcc       10             0xCC

--------------------------------*/
#define TEF700X_CS_ADDR     0xC8    //Tef700x Chip Selection Address     

#define TEF700X_IIC    I2C2 //Used I2c Port
#define Tef700x_WriteDat(Dat,Num,CallBack) I2C_Write(TEF700X_IIC,TEF700X_CS_ADDR,FALSE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Tef700x_WritePdat(Dat,Num,CallBack) I2C_Write(TEF700X_IIC,TEF700X_CS_ADDR,TRUE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Tef700x_ReadDat(Reg,Dat,Num,CallBack)    I2C_ReadFromSubAdd(TEF700X_IIC,TEF700X_CS_ADDR,0x00,FALSE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Tef700x_ReadPdat(Reg,Dat,Num,CallBack) I2C_ReadFromSubAdd(TEF700X_IIC,TEF700X_CS_ADDR,Reg,TRUE,Dat,Num,TRUE,CallBack,I2C_350KBPS)
#define Tef700x_DirectReadDat(Dat,Num,CallBack)  I2C_Read(TEF700X_IIC,TEF700X_CS_ADDR,TRUE,Dat,Num,TRUE,CallBack,I2C_350KBPS)



//4 Tef700x IIC Related---End
//............................................................................................

//-------------------------------------------------------
//2 Tef700x Related Def: Start

#define TEF700X_STATUS         0x00
#define TEF700X_LEVEL         0x01
#define TEF700X_USN         0x02
#define TEF700X_WAM         0x03
#define TEF700X_IFC             0x04
#define TEF700X_RDS         0x05
#define TEF700X_AH             0x06
#define TEF700X_AL             0x07
#define TEF700X_BH             0x08
#define TEF700X_BL             0x09
#define TEF700X_CH             0x0A
#define TEF700X_CL             0x0B
#define TEF700X_DH             0x0C
#define TEF700X_DL             0x0D
#define TEF700X_ERR         0x0E
#define TEF700X_DEE         0x0F

//2 Tef700x Related Def: End
//-------------------------------------------------------


//............................................................................................
//4 Tef700x Control Enum : Start

//TEF700X Driver Type
typedef enum tef700x_driver_type_enum
{
    TEF700X_IIC_IDLE = 0,
    TEF700X_IIC_REGISTER,        // Initialize Registers
    TEF700X_IIC_IR,        //  
    TEF700X_IIC_FREQ,    //Set Frequency
    TEF700X_IIC_READ,            //Read Status
}TEF700X_DRIVER_TYPE_ENUM;

//TEF700X Driver  Status
typedef enum tef700x_drv_status_enum
{
    TEF700X_DRV_IDLE = 0,
    TEF700X_DRV_BUSY,
    TEF700X_DRV_ERROR,
}TEF700X_DRV_STATUS_ENUM;

//4 Tef700x Control Enum : End
//............................................................................................


//TEF700X Struct
typedef struct tef700x_struct
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
}TEF700X_STRUCT;

#define TEF700X_TICK_BASE        2
#define Tef700xDelay(x)            (x)/TEF700X_TICK_BASE

//--------------------------------------------------------------
//3  Declare :Start

EXTERN TEF700X_STRUCT sTef700x;

EXTERN uint8_t Tef700x_CallBack_Common(uint8_t Result);
EXTERN uint8_t Tef700x_WriteCommon(TEF700X_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num);
EXTERN uint8_t Tef700x_ReadCommon(uint8_t Num);

//3  Declare :End
//--------------------------------------------------------------


#undef EXTERN

#endif//TEF700X_DRV_H

