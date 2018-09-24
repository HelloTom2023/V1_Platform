/**********************************************************
 * @file        Video_Fms6501.h
 * @purpose    Definition of Fms6501
 * @version    0.01
 * @date        02.Feb. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        02.Feb.2013              v0.01        created
 *  
  **********************************************************/
#ifndef VIDEO_FMS6501_H
#define VIDEO_FMS6501_H

#ifdef D_VIDEO_SWITCH_FMS6501
#ifdef VIDEO_FMS6501_C
#define EXTERN
#else
#define EXTERN extern
#endif//VIDEO_FMS6501_C

//Chip IIC Address
#define FMS6501_CS_ADDR    0x86    //PIN ADDR TO HIGH:0x86; TO LOW:0x06

//............................................................................................
//4 Control Step Definitions : Start

// Startup Steps
typedef enum fms_register_step_enum
{
    FMS_REGISTER_DEFAULT_OUT = 0,    //Config to Default Out
    FMS_REGISTER_CLAMP_BIAS,            //Config Bias/Clamp Setting
    FMS_REGISTER_END,                    //Register Init Ends
}FMS_REGISTER_ENUM;

//4 Control Step Definitions : End
//............................................................................................


//............................................................................................
//4 FMS Related Def: Start
//Channel Enable or Power Down:
#define FMS_CH_PWRDN    0
#define FMS_CH_ENABLE    1
#define FMS_CH_MASK    7

//Channel Gain
#define FMS_GAIN_6DB    0x00
#define FMS_GAIN_7DB    0x01
#define FMS_GAIN_8DB    0x02    
#define FMS_GAIN_9DB    0x03
#define FMS_GAIN_MASK    5

#define FMS_INPUT_OFF    0x00
#define FMS_INPUT_IN1    0x01
#define FMS_INPUT_IN2    0x02
#define FMS_INPUT_IN3    0x03
#define FMS_INPUT_IN4    0x04
#define FMS_INPUT_IN5    0x05
#define FMS_INPUT_IN6    0x06
#define FMS_INPUT_IN7    0x07
#define FMS_INPUT_IN8    0x08
#define FMS_INPUT_IN9    0x09
#define FMS_INPUT_IN10    0x0A
#define FMS_INPUT_IN11    0x0B
#define FMS_INPUT_IN12    0x0C

#define FMS_CLAMP    1
#define FMS_BIAS    0

#define FMS_DEFAULT_OUT1    (0x80 | FMS_INPUT_OFF | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_DEFAULT_OUT2    (0x80 | FMS_INPUT_OFF | (FMS_GAIN_6DB << FMS_GAIN_MASK))        
#define FMS_DEFAULT_OUT3    (0x80 | FMS_INPUT_OFF | (FMS_GAIN_6DB << FMS_GAIN_MASK))        
#define FMS_DEFAULT_OUT4    (0x80 | FMS_INPUT_OFF | (FMS_GAIN_6DB << FMS_GAIN_MASK))        
#define FMS_DEFAULT_OUT5    (FMS_INPUT_OFF)         
#define FMS_DEFAULT_OUT6    (FMS_INPUT_OFF)        
#define FMS_DEFAULT_OUT7    (0x80 | FMS_INPUT_OFF | (FMS_GAIN_6DB << FMS_GAIN_MASK))        
#define FMS_DEFAULT_OUT8    (0x80 | FMS_INPUT_OFF | (FMS_GAIN_6DB << FMS_GAIN_MASK))        
#define FMS_DEFAULT_OUT9    (0x80 | FMS_INPUT_OFF | (FMS_GAIN_6DB << FMS_GAIN_MASK))        

//4 FMS Related Def: Start
//............................................................................................


//--------------------------------------------------------------
//4 FMS Typedef Struct&Enum:Start

//FMS Input Connections
#define FMS_DVD_Y        (0x80 | FMS_INPUT_IN2 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_DVD_U        (0x80 | FMS_INPUT_IN3 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_DVD_V        (0x80 | FMS_INPUT_IN1 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_CDC            (0x80 | FMS_INPUT_IN5 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_AK_FRONT    (0x80 | FMS_INPUT_IN4 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_AK_REAR1    (0x80 | FMS_INPUT_IN5 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_AK_REAR2    (0x80 | FMS_INPUT_IN6 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_AUX2_Y        (0x80 | FMS_INPUT_IN10 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_AUX2_PB    (0x80 | FMS_INPUT_IN11 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_AUX2_PR    (0x80 | FMS_INPUT_IN12 | (FMS_GAIN_6DB << FMS_GAIN_MASK))
#define FMS_AUX2_CVBS    (0x80 | FMS_INPUT_IN10 | (FMS_GAIN_6DB << FMS_GAIN_MASK))

//FMS Output Connections
#define FMS_FRONT_Y        FMS_REG_OUT1    //To Decorder
#define FMS_FRONT_U        FMS_REG_OUT2
#define FMS_FRONT_V        FMS_REG_OUT3
#define FMS_FRONT_CVBS        FMS_REG_OUT4
#define FMS_REAR_Y            FMS_REG_OUT7    //To Rear
#define FMS_REAR_U            FMS_REG_OUT8    
#define FMS_REAR_V            FMS_REG_OUT9
#define FMS_REAR_CVBS1        FMS_REG_OUT9
#define FMS_REAR_CVBS2        FMS_REG_OUT8


//Fms6501 Struct
typedef struct fms6501_struct
{
    uint8_t Ready;     //device ready to control    
    
    //Control Parameters
    uint8_t Step;
    uint8_t UpdateStep;    //Update Register Step
    uint8_t DrvStep;    //Driver Control Step
    uint8_t DrvResult;
    
    //Register Buffer
    uint8_t RegBuff[9];
}FMS6501_STRUCT;

EXTERN FMS6501_STRUCT sFms6501;

#define FMS_REG_OUT1    sFms6501.RegBuff[0]
#define FMS_REG_OUT2    sFms6501.RegBuff[1]
#define FMS_REG_OUT3    sFms6501.RegBuff[2]
#define FMS_REG_OUT4    sFms6501.RegBuff[3]
#define FMS_REG_OUT5    sFms6501.RegBuff[4]
#define FMS_REG_OUT6    sFms6501.RegBuff[5]
#define FMS_REG_OUT7    sFms6501.RegBuff[6]
#define FMS_REG_OUT8    sFms6501.RegBuff[7]
#define FMS_REG_OUT9    sFms6501.RegBuff[8]


#define Fms6501_IIC_CheckBus()    I2C_Busy(I2C1)    
#define Fms6501_IIC_CallBack(x)     I2C_CallBack(I2C1,(x))

//4 FMS Typedef Struct&Enum:End
//--------------------------------------------------------------



//--------------------------------------------------------------
//3  Declare :Start

EXTERN void Fms6501_InitVariable(void);
EXTERN uint8_t Fms6501_Regsiter(void);
EXTERN uint8_t Fms6501_SwitchVch(uint8_t Vch, uint8_t Type);

//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN

#endif//D_VIDEO_SWITCH_FMS6501

#endif//VIDEO_FMS6501_H

