#ifndef  _KEYPAD_H_
#define  _KEYPAD_H_

#ifdef _KEYPAD_C_
#define _KEYPAD_
#else 
#define _KEYPAD_    extern
#endif

#define D_ENCODE_SCAN_IN_INT  1//不同之处在于，边沿中断后电平变化了下；而循环扫描检测的是实时电平

#define D_ENCODE_SPEED_CTRL   1

#if D_DEBUG_KEY && D_PRINT_EN
#define key_printf(x) x
#else
#define key_printf(x)
#endif
#if D_DEBUG_ENCODE && D_PRINT_EN
#define encode_printf(x) x
#else
#define encode_printf(x)
#endif


#define D_MAX_KEY_CHANNEL_NUM       2
#define D_MAX_ENC_CHANNEL_NUM       2
#define D_MAX_BUS_CHANNEL_NUM       1

#define D_PANNEL_KEY_CHANNEL_NUM    4
#define D_ENC_KEY_CHANNEL_NUM       2 
#define D_BUS_KEY_CHANNEL_NUM       1

#define D_ALL_KEY_CHANNEL_NUM       (D_PANNEL_KEY_CHANNEL_NUM  + D_BUS_KEY_CHANNEL_NUM)     

#define _KEY_PLUS_V_(x)             ((x)*100)
#define _KEY_V_(x)                  ((((x)*100)*(((x) == 3.3)?255:256))/_KEY_PLUS_V_(3.3))


typedef enum{
    HMI_KEY_DEV_NONE,
    HMI_KEY_DEV_KEY1,
    HMI_KEY_DEV_KEY2,
    HMI_KEY_DEV_SWC1,
    HMI_KEY_DEV_SWC2,
    HMI_KEY_DEV_ENCODE1,
    HMI_KEY_DEV_ENCODE2,
    HMI_KEY_DEV_BUSLINE,
    HMI_KEY_DEV_FIR,
    HMI_KEY_DEV_RIR,
    HMI_KEY_DEV_UI,
    HMI_KEY_DEV_ADPBUS,
    HMI_KEY_TMP_START,
    
    HMI_KEY_DEV_TMPSWC1,
    HMI_KEY_DEV_TMPSWC2,

    HMI_KEY_DEV_N
}eHMI_KEY_DEV;

////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
typedef struct {
    uint8_t      cPhyValue;          //物理识别值
    uint8_t      clogicValue;        //逻辑值   
}tKEY_LOGIC_MAP;

#pragma pack(1)
typedef struct {
    
    uint8_t cAttr;                   //按键属性，可扩张，此处作按键AD的误差值
    uint8_t cIdleMax;                //空闲范围.减少平时扫描的时间.
    uint8_t cValidTime;              //按键有效时间uin
    uint8_t cNum;                    //按键个数
    tKEY_LOGIC_MAP    tKeyMap[20];   //按键表
    
}tKEY_MAP;

typedef struct{
	uint8_t keyCode;
	uint8_t keySource;
	uint8_t keyAttri;
	uint8_t keyState;
}eKEY_DATA_STATE;

typedef struct
{
	uint16_t Timer;
	uint8_t EnterFlag		:1;
	uint8_t MODEKeyState		:1;
	uint8_t VRKeyState		:1;
	uint8_t UsbModeStep;
	uint16_t UsbModeTimer;
}AutoTestStruct;
////////////////////////////////////////////////////////////////////////////////
#include "swc.h"

extern eKEY_DATA_STATE KeyInfoStr;
_KEYPAD_ void    HMI_KeyInit           (void);
_KEYPAD_ void    HMI_KeyTask           (EVENT iEvt);
_KEYPAD_ void    isrHMI_ScanEncode(uint8_t cIdx,uint8_t vol);
_KEYPAD_ void    SendKeyMsgToMedia(tMSG_BUF* p_tMsg);
_KEYPAD_ void    AutoTestKeyCheck(tMSG_BUF* p_tMsg);
_KEYPAD_ void    HMI_AutoTestInit(void);

////////////////////////////////////////////////////////////////////////////////


#endif //__KEYPAD_H__

