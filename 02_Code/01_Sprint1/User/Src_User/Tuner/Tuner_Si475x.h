/**********************************************************
 * @file        Tuner_Si475x.h
 * @purpose    Definition of Tuner Si475x
 * @version    0.01
 * @date        16.July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        16.July.2012              v0.01        created
 *  
  **********************************************************/
#ifndef TUNER_SI475X_H
#define TUNER_SI475X_H

#ifdef TUNER_SI475X_C
#define EXTERN
#else
#define EXTERN extern
#endif//TUNER_SI475X_C

//............................................................................................
//4 Si475x IIC Device Address Selection---Start
/*------------------------------
A1           A0              CS Address
Floating    Floating       C6
Floating    GND            C4     Used!
GND         Floating       C2
GND         GND            C0     
--------------------------------*/
#define SI475X_CS_ADDR     0xC4    //Si475x Chip Selection Address         
//4 Si475x IIC Device Address Selection---End
//............................................................................................

//............................................................................................
//4 Si475x Control Step Definitions : Start
 
// Si475x Reset Steps
typedef enum si475x_reset_enum
{
    SI475X_RESET_ACTIVE = 0,    // Reset....
    SI475X_RESET_DEACTIVE,    // Deactive Reset
    SI475X_RESET_END,            // Reset End
}SI475X_RESET_ENUM;


//4 Si475x Control Step Definitions : End
//............................................................................................


// Reset Control Definition
#define Si475x_SetReset()        Hero_PinConnect(HERO_GPIO_8,GPIO_FUNID_OUTPUT_LOW);
#define Si475x_ClearReset()    Hero_PinConnect(HERO_GPIO_8,GPIO_FUNID_OUTPUT_HIGH);



#undef EXTERN

#endif//TUNER_SI475X_H

