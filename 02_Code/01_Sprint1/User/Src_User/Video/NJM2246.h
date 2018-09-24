#ifndef _NJM2246_H_
#define _NJM2246_H_

#ifdef _NJM2246_C_
#define _NJM2246_ 
#else
#define _NJM2246_ extern 
#endif


typedef struct njm2246_vch_tab_struct
{
    uint8_t DummyVch;   //Logistic vch
    uint8_t ActualFront;    // Actual Vch for Front
}NJM2246_VCH_TAB_STRUCT;



// Video Input Enum
typedef enum njm2246_vin_enum
{
    NJM2246_VIN_OFF = 0,        
    NJM2246_VIN_1,        // Video Input Channel 1
    NJM2246_VIN_2,
    NJM2246_VIN_3,
}NJM2246_VIN_ENUM;

_NJM2246_	uint8_t Njm2246_SwitchVch(uint8_t Vch, uint8_t Type);
#endif

