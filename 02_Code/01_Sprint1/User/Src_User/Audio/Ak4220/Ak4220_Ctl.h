/**********************************************************
 * @file        Ak4220_Ctl.h
 * @purpose    Definition of Ak4220 Control
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
#ifndef AK4220_CTL_H
#define AK4220_CTL_H

#ifdef AK4220_CTL_C
#define EXTERN 
#else
#define EXTERN extern 
#endif//AK4220_CTL_C

//............................................................................................
//4 Ak4220 Control Step Definitions : Start

// Ak4220 Reset Step
typedef enum ak4220_rst_step_enum
{
    AK4220_RST_CONFIG = 0,        //Config Reset Pin
    AK4220_RST_ACTIVE,         // Set to RESET
    AK4220_RST_DEACTIVE,        // Set to Normal
    AK4220_RST_CHK_BUS,        //Check BUS Status
    AK4220_RST_CHK_DEV,        // Check Device Status
    AK4220_RST_END,            // Reset End
}AK4220_RST_STEP_ENUM;


typedef struct ak4220_ach_tab_struct
{
    uint8_t DummyAch;   //Logistic Ach
    uint8_t ActualFront;    // Actual Ach for Front
    //uint8_t ActualRear;     //Actual Ach for Rear
}AK4220_ACH_TAB_STRUCT;

typedef struct ak4220_vch_tab_struct
{
    uint8_t DummyVch;   //Logistic vch
    uint8_t ActualFront;    // Actual Vch for Front
    //uint8_t ActualRear;     //Actual Vch for Rear
}AK4220_VCH_TAB_STRUCT;

//4 Ak4220 Control Step Definitions : End
//............................................................................................


//............................................................................................
//4 Ak4220 Control Definitions : Start

//Output Config
#define AK4220_VOUT_FRONT    AK4220_OUT_V1
#define AK4220_VOUT_REAR1    AK4220_OUT_V2
#define AK4220_VOUT_REAR2    AK4220_OUT_V3

//4 Ak4220 Control Definitions : End
//............................................................................................



//--------------------------------------------------------------
//3  Declare :Start

EXTERN void Ak4220_InitVariable(void);
EXTERN uint8_t Ak4220_OpenPower(void);
EXTERN uint8_t Ak4220_Reset(void);
EXTERN uint8_t Ak4220_Register(void);
EXTERN uint8_t Ak4220_GpioCtl(uint8_t Gpio, uint8_t Attri);
EXTERN uint8_t Ak4220_SwitchAch(uint8_t Ach, uint8_t Type);
EXTERN uint8_t Ak4220_SwitchVch(uint8_t Vch, uint8_t Type);
EXTERN uint8_t Ak4220_SetMixSrc(uint8_t Src, uint8_t Type);
EXTERN uint8_t Ak4220_CheckVideo(void);
EXTERN uint8_t Ak4220_SetRst(void);    
EXTERN uint8_t Ak4220_ClearRst(void);    

//3  Declare :End
//--------------------------------------------------------------

#undef EXTERN

#endif//AK4220_CTL_H

