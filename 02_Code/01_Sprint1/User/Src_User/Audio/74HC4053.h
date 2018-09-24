#ifndef _HC4053_H_
#define _HC4053_H_

#ifdef _HC4053_C_
#define _HC4053_ 
#else
#define _HC4053_  extern 
#endif

//74HC4053 Input Enum
typedef enum hc4053_ain_enum
{
    HC4053_AIN_OFF = 0,        
    HC4053_AIN_X0_Z0,        // Audio Input Channel 1
    HC4053_AIN_X1_Z1,
}HC4053_AIN_ENUM;

typedef struct hc4053_ach_tab_struct
{
    uint8_t DummyAch;   //Logistic Ach
    uint8_t ActualFront;    // Actual Ach for Front
}HC4053_ACH_TAB_STRUCT;


_HC4053_	uint8_t Hc4053_SwitchAch(uint8_t Ach, uint8_t Type);
#endif

