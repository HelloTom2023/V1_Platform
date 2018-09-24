#ifndef  _SWC_H_
#define  _SWC_H_

#ifdef _SWC_C_
#define _SWC_
#else
#define _SWC_ extern
#endif

#if D_DEBUG_SWC && D_PRINT_EN
#define swc_printf(x)  x
#else
#define swc_printf(x)
#endif


#define D_SWC_KEY_MAX_NUM_ON_CH            15
#define D_SWC_KEY_CHANNEL_NUM              2
#define D_SWC_PLUS_RESISTANCE_NUM          0x02


typedef struct {
    uint8_t        cResistanceIdx[D_SWC_KEY_CHANNEL_NUM];
    tKEY_MAP       tSwcLogicMap[D_SWC_KEY_CHANNEL_NUM];
    uint16_t       iChkSum;
}tSWC_ROM_DATA;


typedef enum{
    OP_SWC_NONE,
    OP_SWC_SET_MODE,
    OP_SWC_SET_UICC,
    OP_SWC_SET_LOGIC_VALUE,

    OP_SWC_N
}eSWC_OP;

typedef enum{
    SWC_RX_MODE_START,
    SWC_RX_MODE_CLEAR,
    SWC_RX_MODE_SAVE,
    SWC_RX_MODE_EXIT,
    SWC_RX_MODE_N
}eSWC_RX_MODE;


typedef enum{
    SWC_TX_MODE_START,
    SWC_TX_MODE_EXIT,
    SWC_TX_MODE_N
}eSWC_TX_MODE;

_SWC_ void HMI_SWCMsgHandle(tMSG_BUF* p_tMsg);
_SWC_ void HMI_SWCInit(void);
_SWC_ void HMI_SWCProc(void);
_SWC_ void HMI_SWCRomDataInit(void);


#endif
