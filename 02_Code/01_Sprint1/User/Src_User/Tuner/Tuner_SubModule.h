/**********************************************************
 * @file        Task_SubModule.h
 * @purpose    Annoucement of Sub Tuner
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
#ifndef TUNER_SUBMODULE_H
#define TUNER_SUBMODULE_H

#ifdef TUNER_SUBMODULE_C
#define EXTERN
#else
#define EXTERN extern
#endif//TUNER_SUBMODULE_C


//............................................................................................
//4 Sub-Tuner Control Step Definitions : Start
// Sub-Tuner Control Steps
#define SUBTUNER_FUNC_STARTUP    0x00
#define SUBTUNER_FUNC_IDLE        0x10
#define SUBTUNER_FUNC_VALIDSEEK    0x20
#define SUBTUNER_FUNC_PWROFF        0x30

// Sub-Startup Steps
typedef enum subtuner_startup_enum
{
    SUBTUNER_STARTUP_PWRON = SUBTUNER_FUNC_STARTUP,    // Open Power Supply
    SUBTUNER_STARTUP_RESET,        // Reset Tuner Module
    SUBTUNER_STARTUP_INIT,        // Initialize Tuner's Boot Registers
    SUBTUNER_STARTUP_RESUME,    // Resume Last: Band and Frequency 
    SUBTUNER_STARTUP_END,        // Power On End, Goto IDLE State, Waiting For New Operations
}SUBTUNER_STARTUP_ENUM;

// Sub-Idle Steps
typedef enum subtuner_idle_enum
{
    SUBTUNER_IDLE_END = SUBTUNER_FUNC_IDLE,
}SUBTUNER_IDLE_ENUM;

// Sub-Valid List Seek Steps
typedef enum subtuner_valid_seek_enum
{
    SUBTUNER_VS_CONFIG = SUBTUNER_FUNC_STARTUP,    // Config: Set Seek Mode , Set Specific Parameters
    SUBTUNER_VS_FIRST,            // Check First frequency 
    SUBTUNER_VS_NEXT,                // Change the Frequency to Next
    SUBTUNER_VS_CHK_QUAL,        // Check Quality
    SUBTUNER_VS_GOOD,            // Got a Valid Station, Saved
    SUBTUNER_VS_EXIT,                // Seek End, Exit Seek Mode and Save the New Valid List    
    SUBTUNER_VS_END,                // Seek End
}SUBTUNER_VALID_SEEK_ENUM;

// Sub-Tuner Power Off Steps
typedef enum subtuner_pwroff_enum
{
    SUBTUNER_PWROFF_SORT = SUBTUNER_FUNC_PWROFF,    // Sort Currently Situation, and Initialize Some Parameters 
    SUBTUNER_PWROFF_POWER,        // Control Power to Off According Condition
    SUBTUNER_PWROFF_END,        // End
}SUBTUNER_PWROFF_ENUM;
//4 Sub-Tuner Control Step Definitions : End
//............................................................................................
//4 


#undef EXTERN

#endif//TUNER_SUBMODULE_H

