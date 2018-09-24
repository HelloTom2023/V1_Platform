/**********************************************************
 * @file        Hero_Func.c
 * @purpose    Hero Functions 
 * @version    0.01
 * @date        28. June. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          28.June.2012        v0.01        created
 *  
  **********************************************************/
#define HERO_FUNC_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
#ifdef D_AUDIO_ASP_HERO

/* ========================= Function Announcement  =================== */


/* ========================= public variable ==================== */




/* ========================= private variable =================== */

#ifdef D_HERO_V03
// Spurious signal
static const uint8_t Tab_SpuriosSignalInit1[] = 
{
    0xFF, 0x00, 0x04, 0x01, 0x84, 0xFE, 0xC5, 0xFF, 0xC7 
};
static const uint8_t Tab_SpuriosSignalInit2[]    =
{
    0xFF, 0x00, 0x04, 0x0D, 0x68, 0x01, 0x2C, 0x23, 0xD2, 0xFE, 0xC5, 0x24, 0xAE, 0x01, 0x3B, 0x27,
    0x06, 0xFE, 0xC0, 0x27, 0x2E ,0x01 ,0x3B, 0x27, 0x7E, 0x01, 0x3B, 0x27, 0xA6 ,0x01, 0x2C, 0x27, 
    0xCE, 0xFE, 0xD4, 0x20, 0x9E, 0xFE ,0xD4, 0x25, 0xC1, 0xFE, 0xD4, 0x29, 0xE5, 0xFE, 0xC5, 0x29,
    0xEA, 0x01, 0x2C, 0x24, 0x0E, 0xFE, 0xD4, 0x28, 0x2D, 0x01, 0x2C, 0x29 ,0xEF, 0x01, 0x2C, 0x22,
    0xE7, 0x01, 0x2C, 0x22, 0xF1, 0xFE, 0xD4, 0x21, 0xA2 ,0xFE, 0xD4, 0x22, 0x88  
};    
static const uint8_t Tab_SpuriosSignalInit3[]    =
{ 
    0xFF,0x00,0x04,0x01,0xC0,0x00,0x00,0xFD,0xE8,0x80,0x01,0x43,0xD4,0x00,0x01,0x46,
    0x2D,0x80,0x01,0x6C,0x74,0x00,0x01,0x6E,0xCD,0x80,0x01,0x95,0x14,0x00,0x01,0x97, 
    0x6D
};
static const uint8_t Tab_SpuriosSignalInit4[]= 
{
    0xFF,0x00,0x04,0x01,0xE8,0x00,0x00,0x02, 0x97
};

//Host I2S Spurious
static const uint8_t Tab_I2sSpuriousInit[] =
{ 
    0xFF,0xFF, 0xFF, 0xB0, 0x74, 0x00,0x00,0x00,0xFF
};
//VCO operation point control
static const uint8_t Tab_VcoControlInit1[] =
{ 
    0xF0,0x80,0x00,0x5C,0x00,0xF6,0x1D,0x14,0x00,0x50,0x10,0x7C,0x60,0x80,0x0A,0x7C, 
    0x00,0x00,0x00,0x40,0x00,0x06,0x1D,0x49,0x00,0x00,0x10,0x40,0x00,0x00,0x1B,0x49, 
    0x00,0x00,0xF4,0x40,0x00,0x01,0x1A,0x49,0x00,0x80,0x2A,0x5C,0x02,0xF0,0x1A,0x14, 
    0x00,0x50,0x90,0x14,0x00,0xF6,0x1C,0x68,0x00,0x01,0xFF,0x14,0x00,0x90,0x50,0x50, 
    0x00,0x01,0x00,0x14,0x00,0x30,0x00,0x7C,0x10,0x80,0x16,0x7C,0x58,0xD4,0x10,0x68, 
    0x00,0x02,0x00,0x08,0x00,0x50,0x50,0x14,0x00,0x30,0x10,0x5C,0x03,0xF0,0x1B,0x14, 
    0x00,0x30,0xC0,0x7C,0x10,0x80,0x1D,0x14,0x00,0x70,0x10,0x5C,0x00,0xF6,0x1E,0x14, 
    0x00,0x50,0x10,0x14,0x00,0xD0,0x10,0x14,0x00,0xF6,0x1E,0x5C,0x00,0xF6,0x1D,0x14, 
    0x00,0x30,0x00,0x7C,0x10,0x80,0x27,0x14,0x00,0x50,0xD0,0x14,0x00,0xE0,0x10,0x14, 
    0x00,0x70,0x10,0x14,0x00,0xF6,0x1E,0x14,0x00,0x50,0xD0,0x14,0x00,0xD0,0x10,0x7F, 
    0xFC,0x01,0x15,0x14,0x00,0xF0,0x1A,0x7C,0x00,0x00,0x00,0x68,0x00,0x10,0x00,0x5C, 
    0x00,0xF0,0x20,0x14,0x00,0x50,0x10,0x50,0x00,0x00,0x01,0x14,0x00,0x30,0x00,0x7C, 
    0x58,0x54,0x50,0x7F,0xFC,0x01,0x1B,0x7C,0x68,0x74,0x10,0x26,0x00,0xF0,0x0A
};
static const uint8_t Tab_VcoControlInit2[] =
{ 
    0xF0,0x01,0x15,0x00,0x05,0xBA
};
static const uint8_t Tab_VcoControlInit3[] =
{ 
    0xF0,0x01,0x14,0x00,0x80,0x00
};
#endif//D_HERO_V03    

//Scaling Table
static const sMemAddr_Data Tab_ScalingInit[] = 
{
    {I2CDRV_X_MEM,    HDSP_X_Vol_Boost12dB_REL,0x000000}, //for volume :select FixedBoost 48.16
    {I2CDRV_X_MEM,    HDSP_X_Vol_OneOverMaxBoostP,    HDSP_X_Vol_OneOverMaxBoostP_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_UpScalF,        HDSP_Y_Vol_UpScalF_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_UpScalR,        HDSP_Y_Vol_UpScalR_Data}, 
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_UpScalSwL,    HDSP_Y_Vol_UpScalSwL_Data}, 
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_UpScalSwR,    HDSP_Y_Vol_UpScalSwR_Data}, 
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ScalF,        HDSP_Y_Vol_ScalF_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ScalR,        HDSP_Y_Vol_ScalR_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ScalSwL,        HDSP_Y_Vol_ScalSwL_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ScalSwR,        HDSP_Y_Vol_ScalSwR_Data}, 
    {I2CDRV_X_MEM,HDSP_X_Vol_OneOverMaxBoostS_REL,HDSP_X_Vol_OneOverMaxBoostS_Data},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_UpScalS_REL,HDSP_Y_Vol_UpScalS_Data},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_ScalS_REL,HDSP_Y_Vol_ScalS_Data},
    //End flag
    {I2CDRV_INVALID,    0,            0},
};
//Channel Gain
static const sMemAddr_Data Tab_ChanGainInit[] = 
{
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainPFL,    HDSP_Y_Vol_ChanGainPFL_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainPFR,    HDSP_Y_Vol_ChanGainPFR_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainPRL,    HDSP_Y_Vol_ChanGainPRL_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainPRR,    HDSP_Y_Vol_ChanGainPRR_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainSwL,    HDSP_Y_Vol_ChanGainSwL_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainSwR,    HDSP_Y_Vol_ChanGainSwR_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainSL,    HDSP_Y_Vol_ChanGainSL_Data}, 
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainSR,    HDSP_Y_Vol_ChanGainSR_Data},
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainN,    HDSP_Y_Vol_ChanGainN_Data}, 
    {I2CDRV_Y_MEM,    HDSP_Y_Vol_ChanGainT,    HDSP_Y_Vol_ChanGainT_Data}, 
    //End Flag
    {I2CDRV_INVALID,    0,            0},
};

static const sMemAddr_Data Tab_AudioPointer[] = 
{
    //UBass Connection
    {I2CDRV_X_MEM,HDSP_X_AUB2_InPntr_REL,HDSP_X_Loudf_OutL_REL}, //Input
    //{I2CDRV_X_MEM,HDSP_X_FInPntr_REL,HDSP_X_AUB2_out1_REL},     //Output
    //{I2CDRV_X_MEM,HDSP_X_RInPntr_REL,HDSP_X_AUB2_out1_REL},
    //{I2CDRV_X_MEM,HDSP_X_SwFInPntr_REL,HDSP_X_AUB2_out1_REL},
    //{I2CDRV_X_MEM,HDSP_X_SwRInPntr_REL,HDSP_X_AUB2_out1_REL},

    {I2CDRV_X_MEM,    HDSP_X_GPF2_InPntr_REL,    HDSP_X_SwOutL_REL},  //Sw Path
    /*//lkm20140609_delt //keilee20140617 for 88.7HZganrao
    {I2CDRV_X_MEM,    HDSP_X_HIIS0Outpntr_REL,    HDSP_X_GPF2_OutL_REL}, 

    {I2CDRV_X_MEM,    HDSP_X_HIIS1Outpntr_REL,    HDSP_X_SecOutL_REL},  //rear audio path
*/
    {I2CDRV_X_MEM,HDSP_X_Sup_ExtInPntr_REL,HDSP_X_Chime_Cl_Out}, 
    //end flag
    {I2CDRV_INVALID,    0,            0},
};

// Beep Type: Low Frequency  1KHZ
static const sMemAddr_Data Tab_WholeChimeLow[] = 
{
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_SeqStat_Bk_REL,0x07FF},
#if (ASR_SET_48 == ASR_SETTING)   
    {I2CDRV_X_MEM,HDSP_X_Tsq_CrosFStp_Bk_REL,0x011111},
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArLinStpA_Bk_REL,0x011111},
#else
    {I2CDRV_X_MEM,HDSP_X_Tsq_CrosFStp_Bk_REL,0x012937},
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArLinStpA_Bk_REL,0x012937},
#endif    
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_ArType_Bk_REL,0x0001},
#if (ASR_SET_48 == ASR_SETTING)  
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArRelCoef_Bk_REL,0x7EF011},
    {I2CDRV_X_MEM,HDSP_X_Tsq_TA_Bk_REL,0x0001FE},// 170ms
    {I2CDRV_X_MEM,HDSP_X_Tsq_TB_Bk_REL,0x00005A},// 30ms
#else
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArRelCoef_Bk_REL,0x7ED821},
    {I2CDRV_X_MEM,HDSP_X_Tsq_TA_Bk_REL,0x0001D5},// 170ms
    {I2CDRV_X_MEM,HDSP_X_Tsq_TB_Bk_REL,0x000053},// 30ms
#endif    

    {I2CDRV_X_MEM,HDSP_X_Tsq_repeate_Bk_REL,0x0002},    // 1 times
    
    {I2CDRV_X_MEM,HDSP_X_Tsq_ChangeThreshold_REL,0x4026E7},
    {I2CDRV_X_MEM,HDSP_X_Tsq_DecayThreshold_REL,0x000000},
    //{I2CDRV_Y_MEM,HDSP_Y_Tsq_ChimeVol_Bk_REL,0x03CA},  //Volume
    //Slot1
#if (ASR_SET_48 == ASR_SETTING)    
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x03D5}, //Frequency L
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Htone_Bk_REL,0x07EE},    //Frequency H
#else
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x01FD}, //Frequency L
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Htone_Bk_REL,0x07EB},    //Frequency H
#endif    
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Vtone_Bk_REL,0x0DFE},
#if (ASR_SET_48 == ASR_SETTING)    
    {I2CDRV_X_MEM,HDSP_X_Tsq_T1_Bk_REL,0x000258}, // 200 ms  (bigger than TP)
#else  
    {I2CDRV_X_MEM,HDSP_X_Tsq_T1_Bk_REL,0x000227}, // 200 ms  (bigger than TP)
#endif
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Clip_Bk_REL,0x0080},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Type_Bk_REL,0x0000},

    //No Need Other Slot... Because of Time...
    
    {I2CDRV_X_MEM,HDSP_X_Tsq_addmul_Bk_REL,0x000000},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c02_Bk_REL,0x0B24},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c1_Bk_REL,0x0FFF},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c3_Bk_REL,0x0FFF},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_Copied_REL,0x0800},
    //End Flag
    {I2CDRV_INVALID,0,0},        
};
// Beep Type: High Frequency  1.5KHZ
static const sMemAddr_Data Tab_WholeChimeHigh[] = 
{
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_SeqStat_Bk_REL,0x07FF},
#if (ASR_SET_48 == ASR_SETTING)   
    {I2CDRV_X_MEM,HDSP_X_Tsq_CrosFStp_Bk_REL,0x011111},
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArLinStpA_Bk_REL,0x011111},
#else
    {I2CDRV_X_MEM,HDSP_X_Tsq_CrosFStp_Bk_REL,0x012937},
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArLinStpA_Bk_REL,0x012937},
#endif  
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_ArType_Bk_REL,0x0001},
#if (ASR_SET_48 == ASR_SETTING)  
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArRelCoef_Bk_REL,0x7EF011},
    {I2CDRV_X_MEM,HDSP_X_Tsq_TA_Bk_REL,0x0001FE},// 170ms
    {I2CDRV_X_MEM,HDSP_X_Tsq_TB_Bk_REL,0x00005A},// 30ms
#else
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArRelCoef_Bk_REL,0x7ED821},
    {I2CDRV_X_MEM,HDSP_X_Tsq_TA_Bk_REL,0x0001D5},// 170ms
    {I2CDRV_X_MEM,HDSP_X_Tsq_TB_Bk_REL,0x000053},// 30ms
#endif   
    
    {I2CDRV_X_MEM,HDSP_X_Tsq_repeate_Bk_REL,0x0002},    // 1 times
    
    {I2CDRV_X_MEM,HDSP_X_Tsq_ChangeThreshold_REL,0x4026E7},
    {I2CDRV_X_MEM,HDSP_X_Tsq_DecayThreshold_REL,0x000000},
    //{I2CDRV_Y_MEM,HDSP_Y_Tsq_ChimeVol_Bk_REL,0x03CA},  //Volume
    //Slot1
#if (ASR_SET_48 == ASR_SETTING)       
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x052F}, //Frequency L
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Htone_Bk_REL,0x07D8},    //Frequency H
#else
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x0343}, //Frequency L
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Htone_Bk_REL,0x07D1},    //Frequency H
#endif
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Vtone_Bk_REL,0x0DFE},
#if (ASR_SET_48 == ASR_SETTING)    
    {I2CDRV_X_MEM,HDSP_X_Tsq_T1_Bk_REL,0x000258}, // 200 ms  (bigger than TP)
#else  
    {I2CDRV_X_MEM,HDSP_X_Tsq_T1_Bk_REL,0x000227}, // 200 ms  (bigger than TP)
#endif
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Clip_Bk_REL,0x0080},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Type_Bk_REL,0x0000},

    //No Need Other Slot... Because of Time...
    
    {I2CDRV_X_MEM,HDSP_X_Tsq_addmul_Bk_REL,0x000000},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c02_Bk_REL,0x0B24},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c1_Bk_REL,0x0FFF},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c3_Bk_REL,0x0FFF},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_Copied_REL,0x0800},
    //End Flag
    {I2CDRV_INVALID,0,0},            
};
// Beep Type: High Frequency  2KHZ
static const sMemAddr_Data Tab_WholeChimeTyre[] = 
{
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_SeqStat_Bk_REL,0x07FF},
#if (ASR_SET_48 == ASR_SETTING)   
    {I2CDRV_X_MEM,HDSP_X_Tsq_CrosFStp_Bk_REL,0x011111},
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArLinStpA_Bk_REL,0x011111},
#else
    {I2CDRV_X_MEM,HDSP_X_Tsq_CrosFStp_Bk_REL,0x012937},
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArLinStpA_Bk_REL,0x012937},
#endif  
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_ArType_Bk_REL,0x0001},
#if (ASR_SET_48 == ASR_SETTING)  
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArRelCoef_Bk_REL,0x7EF011},
    {I2CDRV_X_MEM,HDSP_X_Tsq_TA_Bk_REL,0x0001FE},// 170ms
    {I2CDRV_X_MEM,HDSP_X_Tsq_TB_Bk_REL,0x00005A},// 30ms
#else
    {I2CDRV_X_MEM,HDSP_X_Tsq_ArRelCoef_Bk_REL,0x7ED821},
    {I2CDRV_X_MEM,HDSP_X_Tsq_TA_Bk_REL,0x0001D5},// 170ms
    {I2CDRV_X_MEM,HDSP_X_Tsq_TB_Bk_REL,0x000053},// 30ms
#endif   
    
    {I2CDRV_X_MEM,HDSP_X_Tsq_repeate_Bk_REL,0x0002},    // 1 times
    
    {I2CDRV_X_MEM,HDSP_X_Tsq_ChangeThreshold_REL,0x4026E7},
    {I2CDRV_X_MEM,HDSP_X_Tsq_DecayThreshold_REL,0x000000},
    //{I2CDRV_Y_MEM,HDSP_Y_Tsq_ChimeVol_Bk_REL,0x03CA},  //Volume
    //Slot1
#if (ASR_SET_48 == ASR_SETTING)       
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x01BB}, //Frequency L
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Htone_Bk_REL,0x07BA},    //Frequency H
#else
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x0352}, //Frequency L
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1b1Htone_Bk_REL,0x07AD},    //Frequency H
#endif
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Vtone_Bk_REL,0x0DFE},
#if (ASR_SET_48 == ASR_SETTING)    
    {I2CDRV_X_MEM,HDSP_X_Tsq_T1_Bk_REL,0x000258}, // 200 ms  (bigger than TP)
#else  
    {I2CDRV_X_MEM,HDSP_X_Tsq_T1_Bk_REL,0x000227}, // 200 ms  (bigger than TP)
#endif
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Clip_Bk_REL,0x0080},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_T1Type_Bk_REL,0x0000},

    //No Need Other Slot... Because of Time...
    
    {I2CDRV_X_MEM,HDSP_X_Tsq_addmul_Bk_REL,0x000000},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c02_Bk_REL,0x0B24},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c1_Bk_REL,0x0FFF},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_c3_Bk_REL,0x0FFF},
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_Copied_REL,0x0800},
    //End Flag
    {I2CDRV_INVALID,0,0},            
};
//Fast Beep Table
static const sMemAddr_Data Tab_FastChime[] = 
{
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_Copied_REL,0x0800},
    //End Flag
    {I2CDRV_INVALID,0,0},                
};
// Beep Stop
static const sMemAddr_Data Tab_StopChime[] = 
{
    {I2CDRV_Y_MEM,HDSP_Y_Tsq_SeqStat_REL,0x0000},
    {I2CDRV_X_MEM,HDSP_X_Tsq_repeate_REL,0x800000},
    //end flag
    {I2CDRV_INVALID,0,0},        
};
//Input/Output Config
static const uint8_t Tab_InOutInit[][2] = 
{
    //Analog Input
    {IN_ID_AD0,AD_IN_HCM_1V},
    {IN_ID_AD1,AD_IN_HCM_1V},
    {IN_ID_AD2,AD_IN_DIF_1V},
    {IN_ID_AD3,AD_IN_DIF_1V},
    
    //I2S Input
    {IN_ID_I2S0,I2S_IN_PHILIP},
    {IN_ID_I2S1,I2S_IN_PHILIP},
    {IN_ID_I2S2,I2S_IN_PHILIP},
    {ID_HOST_I2S,I2S_IN_PHILIP},
    {IN_ID_HOST,I2S_IN_PHILIP},
    /*//lkm20140609_delt //keilee20140617
    {OUT_ID_HOST0,I2S_IN_PHILIP},
    {OUT_ID_HOST1,I2S_IN_PHILIP},
    {OUT_ID_HOST2,I2S_IN_PHILIP},
    */
    //SPDIF Input 
    {IN_ID_SPDIF,SPDIF_IN_ANALOG},    
    {ID_SPDIF_CONFIG,SPDIF_CONFIG_3},        // 25 ~48

    //DAC
    {ID_FRONT_DAC,AD_DA_ENABLE},    
    {ID_REAR_DAC,AD_DA_ENABLE},    
    
    //ADC
    {ID_ADC,AD_DA_ENABLE},    

    //End Flag
    {0x00,0x00},
};

//GPIO Config
static const uint8_t Tab_GpioConfig[][3] = 
{
    {HERO_GPIO_0,(GPIO_HERO_RDSINT >> 8),(GPIO_HERO_RDSINT & 0xFF)},
    {HERO_GPIO_4,(GPIO_HERO_FASTMUTE >> 8),(GPIO_HERO_FASTMUTE & 0xFF)},
    //End Flag
    {0x00,0x00,0x00},
};

//Loudness--Treble: BandPF
static const uint16_t Tab_Loudness_Treble[] =
{
#if (ASR_SET_48 == ASR_SETTING) 
    0x0343,0x0EA4,0x0152,0x0000,0x0EAE, 
    0x012C,0x0F79,0x01BD,0x0000,0x0E43,
#else
    0x02CF,0x0ED2,0x0169,0x0000,0x0E97,    // 7KHz
    0x00A0,0x0FB5,0x01DB,0x0000,0x0E25,    // 10KHz
#endif
};
//Loudness--Bass: 1st Shelving LPF
static const uint16_t Tab_Loudness_Bass[] =
{
#if (ASR_SET_48 == ASR_SETTING) 
    0x028F,0x03F9,0x0000,0x0000,0x0571,0x0006,0x0000,0x0000,
    0x0454,0x03E5,0x0000,0x0000,0x03AC,0x001A,0x0000,0x0000,
#else
    0x05D9,0x03F8,0x0000,0x0000,0x0226,0x0007,0x0000,0x0000,     // 50Hz
    0x01E0,0x03E3,0x0000,0x0000,0x061F,0x001C,0x0000,0x0000,    // 200Hz
#endif
};
//Config
static const sMemAddr_Data Tab_Loudness_Config[] = 
{
    {I2CDRV_Y_MEM,HDSP_Y_Loudf_MaxBstB_REL,0x04A0}, //Bass Max Bst  15DB     
    {I2CDRV_Y_MEM,HDSP_Y_Loudf_MaxBstT_REL,0x0453}, //Treble Max Bst 10DB
    //{I2CDRV_Y_MEM,HDSP_Y_Loudf_OffsB_REL,0x0020},  //For Dynamic
    //{I2CDRV_Y_MEM,HDSP_Y_Loudf_OffsT_REL,0x0010}, //For Dynamic
    //{I2CDRV_Y_MEM,HDSP_Y_Loudf_KpBL_REL,0x02B6}, //For Dynamic
    //{I2CDRV_Y_MEM,HDSP_Y_Loudf_KpBH_REL,0x0809}, //For Dynamic
    //{I2CDRV_Y_MEM,HDSP_Y_Loudf_KmBL_REL,0x0273}, //For Dynamic
    //{I2CDRV_Y_MEM,HDSP_Y_Loudf_KmBH_REL,0x0012}, //For Dynamic
    //End Flag
    {I2CDRV_INVALID,0,0},
};

//Subwoofer Create Table
static const sMemAddr_Data Tab_Create_StereoSw[] = 
{
    {I2CDRV_Y_MEM,HDSP_Y_Vol_FLonSwL_REL,0x400},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_FRonSwL_REL,0x000},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_RLonSwL_REL,0x400},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_RRonSwL_REL,0x000},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_FLonSwR_REL,0x000},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_FRonSwR_REL,0x400},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_RLonSwR_REL,0x000},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_RRonSwR_REL,0x400},
    //End Flag
    {I2CDRV_INVALID,0,0},
};

static const sMemAddr_Data Tab_Create_MonoSw[] = 
{
    {I2CDRV_Y_MEM,HDSP_Y_Vol_FLonSwL_REL,0x400},    //Centre
    {I2CDRV_Y_MEM,HDSP_Y_Vol_FRonSwL_REL,0x400},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_RLonSwL_REL,0x000},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_RRonSwL_REL,0x000},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_FLonSwR_REL,0x200},    //Sw
    {I2CDRV_Y_MEM,HDSP_Y_Vol_FRonSwR_REL,0x200},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_RLonSwR_REL,0x200},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_RRonSwR_REL,0x200},
    //End Flag
    {I2CDRV_INVALID,0,0},
};


//Source Scaling Table
static const sMemAddr_Data Tab_SrcScaling[] = 
{
    //{I2CDRV_Y_MEM,HDSP_Y_Vol_SrcScalP_REL,0x0400},    //Primary Src Scaler Gain +0
    {I2CDRV_Y_MEM,HDSP_Y_Vol_SrcScalS_REL,0x0400},    //Secondary Src Scaler Gain +0
    {I2CDRV_Y_MEM,HDSP_Y_Vol_SrcScalN_REL,0x0400},
    {I2CDRV_Y_MEM,HDSP_Y_Vol_SrcScalT_REL,0x0400},
    //End Flag
    {I2CDRV_INVALID,0,0},
};

static const uint16_t Tab_NavPhone_Filter1Coefs[10]=
{
       0x0000 ,0x0200 ,0x06F2 ,0x0ECA ,0x0000,0x0000,0x021C,0x026A,0x0000,0x0000 
};

static const uint16_t Tab_NavPhone_Filter2Coefs[10]=
{
       0x0000 ,0x0200 ,0x01F2 ,0x0E07 ,0x0000,0x0000,0x041B,0x03F1,0x0000,0x0000
};


/* ========================= Code Part =================== */
/**********************************************************
 * @function    Hero_Transmit
 * @brief      Start transmit specific datum to Hero
 * @param      uint8_t* Dat
 *                 uint8_t Num
 *            void* CallBack
 *            uint8_t Step
 * @retval     NULL
 **********************************************************/
void Hero_Transmit(uint8_t* Dat,uint8_t Num,void* CallBack, uint8_t Step)
{
    uint8_t QueueResult = FALSE;

    sHero.I2cResult = I2C_RET_WAIT;
    Memcpy_U8(Dat,sHero.DrvBuffer,Num);
    QueueResult = Hero_WritePdat(sHero.DrvBuffer,Num,CallBack);
    if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
    {
        sHero.DrvLayerStep = Step;
        sAudio.DrvOverTime = HeroDelay(T120MS);
        sAudio.DrvDesertTime = HeroDelay(T140MS);
    }
    else
    {    // Failed to Queue in IIC Buffer...
        //..
        sHero.ErrId = HERO_ERR_IIC_QUEUE;
    }
}
/**********************************************************
 * @function    Hero_ReadCommon
 * @brief      Read Datum From HERO and Poll Result Into static Buffer
 * @param      HERO_DRIVER_TYPE_ENUM PID
 *                 uint8_t Num
 * @retval     Result of Execute
 **********************************************************/
uint8_t Hero_ReadCommon(HERO_DRIVER_TYPE_ENUM PID,uint8_t Reg,uint8_t Num)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;   
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    
    //Check Driver Controller, If Not Busy, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            sHero.I2cResult = I2C_RET_WAIT;
            QueueResult = Hero_ReadPdat(Reg,&sHero.ReadBuff[Reg],Num,(void*)Hero_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                sHero.DrvLayerStep = OPERATION_1;
                sAudio.DrvOverTime = HeroDelay(T120MS);
                sAudio.DrvDesertTime = HeroDelay(T140MS);
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //..
                sHero.ErrId = HERO_ERR_IIC_QUEUE;
            }
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sHero.I2cResult)
            {
                Result = SUBLAYER_ERROR;
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_WriteCommon
 * @brief      Write One Command to HERO
 * @param      HERO_DRIVER_TYPE_ENUM PID
 *                 uint8_t* Dat
 *                 uint8_t Num
 * @retval     Result
 **********************************************************/
uint8_t Hero_WriteCommon(HERO_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;   
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            Hero_Transmit(Dat,Num,(void*)Hero_CallBack_Common,OPERATION_1);
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sHero.I2cResult)
            {
                Result = SUBLAYER_ERROR;
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_WriteMemData
 * @brief      Write Low Level Cmd to Hero
 * @param      HERO_DRIVER_TYPE_ENUM PID
 *            uint8_t MemType
 *            uint16_t Addr
 *            uint8_t Len
 * @retval     Result
 **********************************************************/
uint8_t Hero_WriteMemData(HERO_DRIVER_TYPE_ENUM PID, uint8_t MemType, uint16_t Addr,uint8_t Len,int32_t*  pData)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[56];
    uint8_t ByteOrder;
    uint8_t Index;

    ByteOrder = 0;
    Buffer[ByteOrder++] = 0xF2;    // updated only for DSP2 
    
    switch(MemType)
    {
        case I2CDRV_X_MEM:
            Buffer[ByteOrder++] = (uint8_t)((Addr & 0xFF00) >> 8);// Memory location address MSB 
            Buffer[ByteOrder++] = (uint8_t)(Addr & 0xFF);        // Memory location address LSB 
            for(Index = 0;Index< Len;Index++)        //Fill send buffer
            {
                Buffer[ByteOrder++] = (uint8_t)((pData[Index] & 0xFF0000) >> 16);
                Buffer[ByteOrder++] = (uint8_t)((pData[Index] & 0xFF00) >> 8);
                Buffer[ByteOrder++] = (uint8_t)(pData[Index] & 0xFF);
            }
            break;

        case I2CDRV_Y_MEM:
            Buffer[ByteOrder++] = 0x40 |(uint8_t)((Addr & 0xFF00) >> 8);//Memory location address MSB
            Buffer[ByteOrder++] = (uint8_t)(Addr & 0xFF);//Memory location address LSB 
            for(Index = 0;Index < Len;Index++)
            {
                Buffer[ByteOrder++] = (uint8_t)((pData[Index] & 0xFF00) >> 8);
                Buffer[ByteOrder++] = (uint8_t)(pData[Index] & 0xFF);
            }
            break;
            
        case I2CDRV_EP_MEM:
            Buffer[ByteOrder++] = 0x80 | (uint8_t)((Addr & 0xFF00) >> 8);//Memory location address MSB 
            Buffer[ByteOrder++] = (uint8_t)(Addr & 0xFF);//Memory location address LSB 
            break;
            
        default:
            ByteOrder = 0;
            break;
    }
#if 0 //Manually Controlled        
    if(0 == ByteOrder)
    {
        return SUBLAYER_ERROR;    
    }
#endif    
    Result = Hero_WriteCommon(PrivateID, Buffer, ByteOrder);

    return (Result);
}
/**********************************************************
 * @function    Hero_WriteMemData
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_WriteMemWord(HERO_DRIVER_TYPE_ENUM PID, uint8_t MemType, uint16_t Addr, int32_t  Data)
{
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Hero_WriteMemData(PID,MemType,Addr,1,&Data);

    return (Result);
}
/**********************************************************
 * @function    Hero_WriteMemData
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_WriteMemTab(HERO_DRIVER_TYPE_ENUM PID,const sMemAddr_Data *Tab)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    //Check WriteMemTab is in use....:Locked and DrvID different
    if((DRV_LOCKED == sHero.DrvLock) && (PID != sHero.LockID))
    {
        return (SUBLAYER_DOING);
    }

    if(I2CDRV_INVALID != (Tab+sHero.MemTblStep)->Type)
    {
        if(DRV_UNLOCK == sHero.DrvLock)
        {
            sHero.DrvLock = DRV_LOCKING; //Lock Drv Until Ends sending mem table
            sHero.LockID = PID;
        }
    
        SubResult = Hero_WriteMemWord(PID,(Tab+sHero.MemTblStep)->Type, (Tab+sHero.MemTblStep)->Addr,(Tab+sHero.MemTblStep)->Data);
        if(SUBLAYER_DONE == SubResult)
        {
            sHero.MemTblStep++;
        }
    }
    else
    {
        sHero.DrvLock = DRV_UNLOCK; //Ends, Release Drv
        sHero.MemTblStep = 0;
        Result = SUBLAYER_DONE;
    }

    //Error Occurs
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sHero.DrvLock = DRV_UNLOCK; //Ends, Release Drv
        sHero.MemTblStep = 0;
    }

    return (Result);
}
#if 0 //Close EasyProgram Check
/**********************************************************
 * @function    Hero_EasyProgrammChk
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_EasyProgrammChk(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_EASYP_CHK;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[3];   
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        case OPERATION_0:
            Buffer[0] = 0xF2;
            Buffer[1] = (uint8_t)(HDSP_X_EasyP_Index>>8);      //addr is 2 bytes
            Buffer[2] = (uint8_t)HDSP_X_EasyP_Index;    
            Hero_Transmit(Buffer,3,(void*)Hero_EasyProgrammChk,OPERATION_1);
            break;

        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                sHero.ReadBuff[0] = 0xFF;
                sHero.ReadBuff[1] = 0xFF;
                sHero.ReadBuff[2] = 0xFF;
                sHero.I2cResult = I2C_RET_WAIT;
                QueueResult = Hero_DirectReadDat(sHero.ReadBuff,3,(void*)Hero_CallBack_Common);
                if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
                {
                    sHero.DrvLayerStep = OPERATION_2;
                    sAudio.DrvOverTime = HeroDelay(T120MS);
                    sAudio.DrvDesertTime = HeroDelay(T140MS);
                }
                else
                {    // Failed to Queue in IIC Buffer...
                    //..
                }
            }
            break;

        case OPERATION_2:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                //if((0 != sHero.ReadBuff[0]) && (0 != sHero.ReadBuff[1]) && (0 != sHero.ReadBuff[2]))
                if((0 != sHero.ReadBuff[0]) || (0 != sHero.ReadBuff[1]) || (0 != sHero.ReadBuff[2]))    
                {
                    sHero.DrvLayerStep = OPERATION_0;    // ReCheck
                }
                else
                {
                    Result = SUBLAYER_DONE;
                }
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    if(I2C_RET_ERR == sHero.I2cResult)
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
#endif
/**********************************************************
 * @function    Hero_EasyProgrammWrite
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_EasyProgrammWrite(HERO_DRIVER_TYPE_ENUM PID,uint32_t Data)
{
    uint8_t PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[6];
    
    Buffer[0] = 0xF2;
    Buffer[1] = (uint8_t)(HDSP_X_EasyP_Index >> 8);
    Buffer[2] = (uint8_t)HDSP_X_EasyP_Index;
    Buffer[3] = (uint8_t)(Data >> 16);                 
    Buffer[4] = (uint8_t)(Data >> 8); 
    Buffer[5] = (uint8_t)Data;

    Result = Hero_WriteCommon(PrivateID,Buffer,6);        

    return (Result);
}
#if 0 //Close EasyProgram Check
/**********************************************************
 * @function    Hero_EasyProgrammWrite
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_EasyProgramm(HERO_DRIVER_TYPE_ENUM PID,uint32_t Data)
{
    uint8_t PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sHero.EasyPStep)
    {
        case HERO_EASYP_CHK:
            SubResult = Hero_EasyProgrammChk(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SpecialGotoStep(sHero.EasyPStep,HERO_EASYP_WRITE);
            }
            break;

        case HERO_EASYP_WRITE:
            SubResult = Hero_EasyProgrammWrite(PID,Data);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.EasyPStep = 0;
                Result = SUBLAYER_DONE;    
            }
            break;

        default:
            sHero.EasyPStep = 0;
            Result = SUBLAYER_ERROR;    
            break;
    }

    return (Result);
}
#endif
/**********************************************************
 * @function    Hero_EasyProgrammWrite
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_ScratchDataWrite(HERO_DRIVER_TYPE_ENUM PID,uint16_t address,uint8_t dataLength,uint16_t*  pData)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t byteOrder = 0, idx;
    uint8_t buffer[56];
    uint32_t numOfBytes;
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    if(DRV_UNLOCK == sHero.DrvLock)
    {
        sHero.DrvLock = DRV_LOCKED; //Lock DrvUntil Scratch Write Ends
        sHero.LockID = PID;
    }
    
    byteOrder = 0;

    switch(sHero.ScratchStep)
    {
    #if 0 //Close EasyProgram Check
        case OPERATION_0:
            SubResult = Hero_EasyProgrammChk(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.ScratchStep = OPERATION_1;
            }
            break;
    #endif    

        case OPERATION_0:
            buffer[byteOrder++] = 0xF2;
            buffer[byteOrder++] = 0x40 |(uint8_t)((HDSP_Y_UpdatC_Coeff0_REL & 0xff00) >> 8);
            buffer[byteOrder++] = (uint8_t)(HDSP_Y_UpdatC_Coeff0_REL & 0xff);
            for(idx = 0;idx < dataLength;idx++)
            {
                buffer[byteOrder++] = (uint8_t)((pData[idx] & 0xff00)>>8);
                buffer[byteOrder++] = (uint8_t)(pData[idx] & 0xff);
            }
            numOfBytes = byteOrder;

            sHero.I2cResult = I2C_RET_WAIT;
            Memcpy_U8(buffer,sHero.DrvBuffer,numOfBytes);
            QueueResult = Hero_WritePdat(sHero.DrvBuffer,numOfBytes,(void*)Hero_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                sHero.ScratchStep = OPERATION_1;
                sAudio.DrvOverTime = HeroDelay(T120MS);
                sAudio.DrvDesertTime = HeroDelay(T140MS);
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //..
                sHero.ErrId = HERO_ERR_IIC_QUEUE;
            }
            break;
            
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                buffer[byteOrder++] = (uint8_t)(0xF2);
                buffer[byteOrder++] = (uint8_t)((HDSP_X_SrcSw_OrMask_REL & 0xFF00) >> 8);
                buffer[byteOrder++] = (uint8_t)(HDSP_X_SrcSw_OrMask_REL & 0xFF);
                buffer[byteOrder++] = (uint8_t)(0);
                buffer[byteOrder++] = (uint8_t)((address & 0xFF00) >> 8);
                buffer[byteOrder++] = (uint8_t)(address & 0xFF);
                numOfBytes = byteOrder;
                sHero.I2cResult = I2C_RET_WAIT;
                Memcpy_U8(buffer,sHero.DrvBuffer,numOfBytes);
                QueueResult = Hero_WritePdat(sHero.DrvBuffer,numOfBytes,(void*)Hero_CallBack_Common);
                if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
                {
                    sHero.ScratchStep = OPERATION_2;
                    sAudio.DrvOverTime = HeroDelay(T120MS);
                    sAudio.DrvDesertTime = HeroDelay(T140MS);
                }
                else
                {    // Failed to Queue in IIC Buffer...
                    //..
                    sHero.ErrId = HERO_ERR_IIC_QUEUE;
                }
            }
            break;
            
        case OPERATION_2:       
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                buffer[byteOrder++] = (uint8_t)(0xF2);
                buffer[byteOrder++] = (uint8_t)((HDSP_X_EasyP_Index_REL & 0xFF00) >> 8);
                buffer[byteOrder++] = (uint8_t)(HDSP_X_EasyP_Index_REL & 0xFF);
                buffer[byteOrder++] = 0;
                buffer[byteOrder++] = 0;
                buffer[byteOrder++] = (uint8_t)(dataLength & 0xFF);
                numOfBytes = byteOrder;
                sHero.I2cResult = I2C_RET_WAIT;
                Memcpy_U8(buffer,sHero.DrvBuffer,numOfBytes);
                QueueResult = Hero_WritePdat(sHero.DrvBuffer,numOfBytes,(void*)Hero_CallBack_Common);
                if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
                {
                    sHero.ScratchStep = OPERATION_3;
                    sAudio.DrvOverTime = HeroDelay(T120MS);
                    sAudio.DrvDesertTime = HeroDelay(T140MS);
                }
                else
                {    // Failed to Queue in IIC Buffer...
                    //..
                    sHero.ErrId = HERO_ERR_IIC_QUEUE;
                }
            }
            break;

        case OPERATION_3:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                sHero.ScratchStep = OPERATION_0;
                Result = SUBLAYER_DONE;
                sHero.DrvLock = DRV_UNLOCK; //Release Drv 
            }
            break;
    }

    if(I2C_RET_ERR == sHero.I2cResult)    
    {
        Result = SUBLAYER_ERROR;
        sHero.ScratchStep = OPERATION_0;
        sHero.DrvLock = DRV_UNLOCK; //Release Drv 
    }
    
    return (Result);
}
/**********************************************************
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_TransDouble2XYHexData( uint8_t Type, double DoubleData,int32_t *BufferP)
{
    uint32_t Data;
    double DoubleData1;

    if((DoubleData<-1.0000)||(DoubleData>1.0000))       // over flow,hero just use the data between -1.0~1.0
    {
        return 0;
    }

    if(BufferP==NULL)
    {
        return 0;
    }

    if(Type == HERO_YDATA)      //Y memory data 12 bits
    {
        if(DoubleData == 1)
        {
            Data = 0x7FFF;
        }
        else
        {
            DoubleData1=DoubleData*((double)2048);
            if(DoubleData1>0) DoubleData1+=0.5;
            else DoubleData1-=0.5;
            Data=(int32_t)(DoubleData1);        //see UM for calculate
        }
        *BufferP=Data;
    }
    else if(Type==HERO_XDATA)//X memory data
    {
        if(DoubleData==1)
        {
            Data=0x7FFFFF;
        }
        else
        {
            DoubleData1=DoubleData*((double)8388608);
            if(DoubleData1>0) DoubleData1+=0.5;
            else DoubleData1-=0.5;
            Data=(int32_t)(DoubleData1);    //see UM for calculate
        }
        *BufferP=Data;        
    }
    else if(Type==HERO_2YDATA)        // 2 Y memory data
    {
        if(DoubleData==1)
        {
            Data=0x7FFFFF;
        }
        else
        {
            DoubleData1=DoubleData*((double)8388608);
            if(DoubleData1>0)
                 DoubleData1+=0.5;
            else
                 DoubleData1-=0.5;
            Data=(int32_t)(DoubleData1);    //see UM for calculate
        }

        *BufferP=(Data>>12);
        *BufferP&=0x0FFF;
        BufferP++;
        *BufferP=Data&0x0FFF;
        *BufferP>>=1;
    }

    return( 1 );
}

//1 Initialize Related Functions
#ifdef D_HERO_V03
/**********************************************************
 * @function    Hero_Init_ImproveAudioA
 * @brief      Improve Audio Setting A For V1C
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Init_ImproveAudioA(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_INIT_AUDIO_A;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[4];    
    
    Buffer[0] = 0xE1;  
    Buffer[1] = 0xC1;
    Buffer[2] = 0xBC; 
    Buffer[3] = 0x11;

    Result = Hero_WriteCommon(PrivateID,Buffer,4);

    return (Result);
}
/**********************************************************
 * @function    Hero_Init_ImproveRadioSettingA
 * @brief      Improve Radio Setting A For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Init_ImproveRadioA(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_INIT_RADIO_A;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[6];   
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        //Prepare for AM divider/IFAD if Bus is Idle
        case OPERATION_0:        
            Buffer[0]=0xE1;      
            Buffer[1]=0xD0;
            Buffer[2]=0x61; 
            Buffer[3]=0x23;
            Hero_Transmit(Buffer,4,(void*)Hero_Init_ImproveRadioA,OPERATION_1);
            break;

        //Prepare for AM divider/IQC : Execute by CallBack
        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xE1;      
                Buffer[1]=0xB0;
                Buffer[2]=0x56; 
                Buffer[3]=0x65;
                Hero_Transmit(Buffer,4,(void*)Hero_Init_ImproveRadioA,OPERATION_2);
            }
            break;
            
        //Set IQC : Execute by CallBack
        case OPERATION_2:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF0;  
                Buffer[1]=0x00;
                Buffer[2]=0x46; 
                Buffer[3]=0x01;
                Buffer[4]=0x10;
                Buffer[5]=0x22;
                Hero_Transmit(Buffer,6,(void*)Hero_CallBack_Common,OPERATION_3);
            }
            break;    

        // Check Result
        case OPERATION_3:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_Init_ImproveRadioSettingA2
 * @brief      Improve Radio Setting A2 For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Init_ImproveRadioA2(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_INIT_RADIO_A2;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[9];   
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        // Prepare setting VCO operation point control
        case OPERATION_0:        
            Buffer[0]=0xE1;      
            Buffer[1]=0x40;
            Buffer[2]=0xD9; 
            Buffer[3]=0xB1;
            Hero_Transmit(Buffer,4,(void*)Hero_Init_ImproveRadioA2,OPERATION_1);
            break;

        //Image suppression
        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF0;     
                Buffer[1] = 0x00;
                Buffer[2] = 0x46; 
                Buffer[3] = 0x01;
                Buffer[4] = 0x10;
                Buffer[5] = 0x22;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioA2,OPERATION_2);
            }
            break;
            
        // FM Startup
        case OPERATION_2:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xFF;  
                Buffer[1]=0xFF;
                Buffer[2]=0xFF; 
                Buffer[3]=0xB0;
                Buffer[4]=0x3C;
                Buffer[5]=0x10;
                Buffer[6]=0x00;
                Buffer[7]=0x01;
                Buffer[8]=0x00;
                Hero_Transmit(Buffer,9,(void*)Hero_Init_ImproveRadioA2,OPERATION_3);
            }
            break;    
            
        case OPERATION_3:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;     
                Buffer[1] = 0xC0;
                Buffer[2] = 0x60; 
                Buffer[3] = 0x00;
                Buffer[4] = 0x20;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00;
                Buffer[7] = 0x00;
                Buffer[8] = 0x04;
                Hero_Transmit(Buffer,9,(void*)Hero_Init_ImproveRadioA2,OPERATION_4);
            }
            break;
            
        // Host I2S Spurious signal
        case OPERATION_4:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;     
                Buffer[1] = 0xFF;
                Buffer[2] = 0xFF; 
                Buffer[3] = 0xB0;
                Buffer[4] = 0x74;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00;
                Buffer[7] = 0x00;
                Buffer[8] = 0xFF;
                Hero_Transmit(Buffer,9,(void*)Hero_CallBack_Common,OPERATION_5);
            }
            break;    
            
        // Check Result
        case OPERATION_5:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }
    
    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_Init_SpuriosSignal
 * @brief      Initialize Spurios Signal Setting For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Init_SpuriosSignal(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_SPURIOUS_SIGNAL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        // Prepare setting VCO operation point control
        case OPERATION_0:    
            Hero_Transmit((uint8_t *)Tab_SpuriosSignalInit1,9,(void*)Hero_Init_SpuriosSignal,OPERATION_1);
            break;

        //Image suppression
        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                Hero_Transmit((uint8_t *)Tab_SpuriosSignalInit2,77,(void*)Hero_Init_SpuriosSignal,OPERATION_2);
            }
            break;
            
        // FM Startup
        case OPERATION_2:
            if(I2C_RET_SUCCESS == eState)
            {
                Hero_Transmit((uint8_t *)Tab_SpuriosSignalInit3,33,(void*)Hero_Init_SpuriosSignal,OPERATION_3);
            }
            break;    
            
        case OPERATION_3:
            if(I2C_RET_SUCCESS == eState)
            {    
                Hero_Transmit((uint8_t *)Tab_SpuriosSignalInit4,9,(void*)Hero_CallBack_Common,OPERATION_4);
            }
            break;
            
        // Check Result
        case OPERATION_4:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }
    
    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_Init_SpuriosSignal
 * @brief      Initialize Spurios Signal Setting For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Init_IISVco(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_SPURIOUS_SIGNAL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        // Prepare setting VCO operation point control
        case OPERATION_0:    
            Hero_Transmit((uint8_t *)Tab_I2sSpuriousInit,9,(void*)Hero_Init_IISVco,OPERATION_1);
            break;

        //Image suppression
        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                Hero_Transmit((uint8_t *)Tab_VcoControlInit1,0xCF,(void*)Hero_Init_IISVco,OPERATION_2);
            }
            break;
            
        // FM Startup
        case OPERATION_2:
            if(I2C_RET_SUCCESS == eState)
            {
                Hero_Transmit((uint8_t *)Tab_VcoControlInit2,6,(void*)Hero_Init_IISVco,OPERATION_3);
            }
            break;    
            
        case OPERATION_3:
            if(I2C_RET_SUCCESS == eState)
            {
                Hero_Transmit((uint8_t *)Tab_VcoControlInit3,6,(void*)Hero_CallBack_Common,OPERATION_4);
            }
            break;
            
        // Check Result
        case OPERATION_4:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }
    
    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_Init_ImproveRadioSettingB
 * @brief      Improve Radio Setting B For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Init_ImproveRadioB(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_INIT_RADIO_B;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[6];   
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        //IF ADC performance
        case OPERATION_0:        
            Buffer[0]=0xF8;  
            Buffer[1]=0x00;
            Buffer[2]=0x11; 
            Buffer[3]=0x00;
            Buffer[4]=0xDC;
            Buffer[5]=0x00;
            Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_1);
            break;

        //Audio Rear output startup
        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF2;  
                Buffer[1]=0x06;
                Buffer[2]=0xE9; 
                Buffer[3]=0x7F;
                Buffer[4]=0xFF;
                Buffer[5]=0xFF;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_2);
            }
            break;
            
        // AM LO frequency    
        case OPERATION_2:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF0;  
                Buffer[1]=0x40;
                Buffer[2]=0x0A; 
                Buffer[3]=0x07;
                Buffer[4]=0xFF;
                Hero_Transmit(Buffer,5,(void*)Hero_Init_ImproveRadioB,OPERATION_3);
            }
            break;    

        case OPERATION_3:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF8;  
                Buffer[1]=0x00;
                Buffer[2]=0x0E; 
                Buffer[3]=0x00;
                Buffer[4]=0x00;
                Buffer[5]=0x36;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_4);
            }
            break;

        case OPERATION_4:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF8;  
                Buffer[1]=0x00;
                Buffer[2]=0x0D; 
                Buffer[3]=0x80;
                Buffer[4]=0x00;
                Buffer[5]=0x00;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_5);
            }
            break;    

        case OPERATION_5:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF8;  
                Buffer[1]=0x00;
                Buffer[2]=0x0E; 
                Buffer[3]=0x00;
                Buffer[4]=0x00;
                Buffer[5]=0x37;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_6);
            }
            break;        
            
        case OPERATION_6:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF8;  
                Buffer[1]=0x00;
                Buffer[2]=0x0E; 
                Buffer[3]=0x00;
                Buffer[4]=0x00;
                Buffer[5]=0x36;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_7);
            }
            break;    
            
        case OPERATION_7:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF8;  
                Buffer[1]=0x00;
                Buffer[2]=0x0D; 
                Buffer[3]=0x00;
                Buffer[4]=0x00;
                Buffer[5]=0x01;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_8);
            }
            break;    
            
        case OPERATION_8:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF8;  
                Buffer[1]=0x00;
                Buffer[2]=0x0E; 
                Buffer[3]=0x00;
                Buffer[4]=0x00;
                Buffer[5]=0x5B;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_9);
            }
            break;    

        case OPERATION_9:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF8;  
                Buffer[1]=0x00;
                Buffer[2]=0x0E; 
                Buffer[3]=0x00;
                Buffer[4]=0x00;
                Buffer[5]=0x5A;
                Hero_Transmit(Buffer,6,(void*)Hero_Init_ImproveRadioB,OPERATION_10);
            }
            break;        

        case OPERATION_10:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xF0;  
                Buffer[1]=0x40;
                Buffer[2]=0x0A; 
                Buffer[3]=0x00;
                Buffer[4]=0x00;
                Hero_Transmit(Buffer,5,(void*)Hero_CallBack_Common,OPERATION_11);
            }
            break;    

        case OPERATION_11:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;    

        default:
            Result = SUBLAYER_ERROR;
            break;
    }
    
    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_Init_ImproveAudioB
 * @brief      Improve Audio Setting B For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Init_ImproveAudioB(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_INIT_AUDIO_B;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[13];   
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        //ADC performance
        case OPERATION_0:        
            Buffer[0] = 0xFF;  
            Buffer[1] = 0xC0;
            Buffer[2] = 0x60; 
            Buffer[3] = 0x70;
            Buffer[4] = 0x20;
            Buffer[5] = 0x0A;
            Buffer[6] = 0x00;
            Buffer[7] = 0xB5;
            Buffer[8] = 0xBE;
            Buffer[9] = 0x00;
            Buffer[10] = 0x12;
            Buffer[11] = 0x73;
            Buffer[12] = 0xC8;
            Hero_Transmit(Buffer,13,(void*)Hero_Init_ImproveAudioB,OPERATION_1);
            break;

        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;  
                Buffer[1] = 0xC0;
                Buffer[2] = 0x60; 
                Buffer[3] = 0x70;
                Buffer[4] = 0x18;
                Buffer[5] = 0x47;
                Buffer[6] = 0x00;
                Buffer[7] = 0xF8;
                Buffer[8] = 0x00;
                Buffer[9] = 0x47;
                Buffer[10] = 0x00;
                Buffer[11] = 0xF8;
                Buffer[12] = 0x00;
                Hero_Transmit(Buffer,13,(void*)Hero_Init_ImproveAudioB,OPERATION_2);
            }
            break;
            
        case OPERATION_2:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;  
                Buffer[1] = 0xC0;
                Buffer[2] = 0x60; 
                Buffer[3] = 0x70;
                Buffer[4] = 0x2C;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00;
                Buffer[7] = 0x07;
                Buffer[8] = 0x00;
                Hero_Transmit(Buffer,9,(void*)Hero_Init_ImproveAudioB,OPERATION_3);
            }
            break;    
            
        case OPERATION_3:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xFF;  
                Buffer[1]=0xC0;
                Buffer[2]=0x60; 
                Buffer[3]=0x70;
                Buffer[4]=0x48;
                Buffer[5]=0x00;
                Buffer[6]=0x11;
                Buffer[7]=0x80;
                Buffer[8]=0x80;
                Hero_Transmit(Buffer,9,(void*)Hero_Init_ImproveAudioB,OPERATION_4);
            }
            break;    
            
        case OPERATION_4:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0]=0xFF;  
                Buffer[1]=0xC0;
                Buffer[2]=0x60; 
                Buffer[3]=0x70;
                Buffer[4]=0x50;
                Buffer[5]=0x00;
                Buffer[6]=0x10;
                Buffer[7]=0x80;
                Buffer[8]=0x80;
                Hero_Transmit(Buffer,9,(void*)Hero_CallBack_Common,OPERATION_5);
            }
            break;        

        case OPERATION_5:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }
    
    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_Init_ImproveAudioC
 * @brief      Improve Audio Setting C For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Init_ImproveAudioC(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_INIT_AUDIO_C;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[9];   
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sHero.DrvLayerStep)
    {
        case OPERATION_0:        
            Buffer[0] = 0xFF;  
            Buffer[1] = 0xC0;
            Buffer[2] = 0x60; 
            Buffer[3] = 0x70;
            Buffer[4] = 0x2C;
            Buffer[5] = 0x00;
            Buffer[6] = 0x00;
            Buffer[7] = 0x01;
            Buffer[8] = 0x00;
            Hero_Transmit(Buffer,9,(void*)Hero_Init_ImproveAudioC,OPERATION_1);
            break;

        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;  
                Buffer[1] = 0xC0;
                Buffer[2] = 0x60; 
                Buffer[3] = 0x70;
                Buffer[4] = 0x48;
                Buffer[5] = 0x00;
                Buffer[6] = 0x11;
                Buffer[7] = 0x80;
                Buffer[8] = 0x80;
                Hero_Transmit(Buffer,9,(void*)Hero_Init_ImproveAudioC,OPERATION_2);
            }
            break;
            
        case OPERATION_2:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;  
                Buffer[1] = 0xC0;
                Buffer[2] = 0x60; 
                Buffer[3] = 0x70;
                Buffer[4] = 0x50;
                Buffer[5] = 0x00;
                Buffer[6] = 0x10;
                Buffer[7] = 0x80;
                Buffer[8] = 0x80;
                Hero_Transmit(Buffer,9,(void*)Hero_CallBack_Common,OPERATION_3);
            }
            break;    

        case OPERATION_3:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }
    
    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);
    
    return (Result);
}
#endif//D_HERO_V03
/**********************************************************
 * @function    Hero_Keycode
 * @brief      Enter KeyCode for Enhanced Functions
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_Keycode(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_KEYCODE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[4];   
        
    Buffer[0] = HERO_SUBADDR_KEYCODE;
    Buffer[1] = 0x6B;//0x02;//0x80;
    Buffer[2] = 0xA9;//0x70;//0x00;
    Buffer[3] = 0x2F;//0x61;//0x01;

    Result = Hero_WriteCommon(PrivateID,Buffer,4);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_UserCase
 * @brief      Select Audio Case
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_UserCase(uint8_t eState)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_USECASE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[2];   
    
    Buffer[0] = HERO_SUBADDR_USECASE;
#if (ASR_SET_48 == ASR_SETTING) 
    Buffer[1] = ((HERO_USECASE << 4) | 0x01);
#else
    Buffer[1] = (HERO_USECASE << 4);
#endif
    Result = Hero_WriteCommon(PrivateID,Buffer,2);

    return (Result);
}
/**********************************************************
 * @function    Hero_AcitveDevice
 * @brief      Active Device
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_AcitveDevice(uint8_t eState)
{
    uint8_t PrivateID = HERO_IIC_ACTIVE_DEVICE;
    uint8_t Result = SUBLAYER_DOING;

    Result = Hero_UpdatePll(eState,PrivateID,HERO_MODE_SEARCH,TUNER_FM_START,TUNER_CURRENT_FREQ);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_UpdatePll
 * @brief      Control PLL : MODE&BAND&FREQ
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_UpdatePll(uint8_t eState,uint8_t PID,uint8_t Mode,uint8_t Band,uint16_t Freq)
{
    uint8_t PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[4];   

    if((Band > TUNER_AM_START) && ((Band > TUNER_AM_END)))
        Buffer[1] = 2;  // MW     
    else    
        Buffer[1] = 0;  // FM WORLD     
    Buffer[0] = 0x00;
    Buffer[1] +=  Mode;
    Buffer[2] =  ((Freq >> 8) & 0x00FF);
    Buffer[3] = (Freq & 0xFF);

    Result = Hero_WriteCommon(PrivateID,Buffer,4);

    return (Result);
}
/**********************************************************
 * @function    Hero_InitPeripheral
 * @brief      Initialize Peripheral
 * @param      uint8_t eState                
 * @retval     Result
 **********************************************************/
uint8_t Hero_InitPeripheral(uint8_t eState)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_INIT_PERIPHERAL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[3];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }
    
    Buffer[0] = 0xA9;

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (0x00 == sHero.DrvLayerStep))
    {
        Buffer[1] = Tab_InOutInit[sHero.DrvLayerStep][0]; //ID
        Buffer[2] = Tab_InOutInit[sHero.DrvLayerStep][1]; //Config
         audio_printf(_T("Hero_InitPeripheral:%d, %d\n",Buffer[1], Buffer[2]));
        if(0x00 == Tab_InOutInit[sHero.DrvLayerStep + 1][0])
        {
            Hero_Transmit(Buffer,3,(void *)Hero_CallBack_Common,(sHero.DrvLayerStep + 1));
        }
        else
        {
            Hero_Transmit(Buffer,3,(void *)Hero_InitPeripheral,(sHero.DrvLayerStep + 1));
        }
    }

    if(I2C_RET_SUCCESS == sHero.I2cResult)
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);

    return (Result);
}
/**********************************************************
 * @function    Hero_ConfigGpio
 * @brief      Config GPIO's Special Function
 * @param      uint8_t eState                
 * @retval     Result
 **********************************************************/
uint8_t Hero_ConfigGpio(uint8_t eState)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_CONFIG_GPIO;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[4];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Hero_CheckDrvState(PrivateID);
    if(HERO_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(HERO_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }
    
    Buffer[0] = 0xC0;

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (0x00 == sHero.DrvLayerStep))
    {
        Buffer[1] = Tab_GpioConfig[sHero.DrvLayerStep][0]; //ID
        Buffer[2] = Tab_GpioConfig[sHero.DrvLayerStep][1]; //Config
        Buffer[3] = Tab_GpioConfig[sHero.DrvLayerStep][2]; //Config
        
        if((0x00 == Tab_GpioConfig[sHero.DrvLayerStep + 1][1])
            && (0x00 == Tab_GpioConfig[sHero.DrvLayerStep + 1][2]))
        {
            Hero_Transmit(Buffer,4,(void *)Hero_CallBack_Common,(sHero.DrvLayerStep + 1));
        }
        else
        {
            Hero_Transmit(Buffer,4,(void *)Hero_ConfigGpio,(sHero.DrvLayerStep + 1));
        }
    }

    if(I2C_RET_SUCCESS == sHero.I2cResult)
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sHero.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Hero_ClearDrvState(Result);

    return (Result);
}
/**********************************************************
 * @function    Hero_DrvLimiterConfigSel
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvLimiterConfigSel(uint8_t Config)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_LIMITER_CONFIG_SEL;
    uint8_t Result = SUBLAYER_DOING;

    if(1 == Config) 
    {
        Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_Limit_LimitRSOnSec);
    }
    else if(2 == Config)
    {  
        Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_Limit_LimitRSOnRear);
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvLimiterSet(eAudioChannel section,int8_t gain,uint8_t onoff)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_LIMITER_SET;
    uint8_t Result = SUBLAYER_DOING;
    int32_t MinGain;
    uint16_t Address;
    
    MinGain = (int32_t)(~((uint32_t)(Tab_Db2Lin[-gain]+1)*4096));

    if(MinGain > 0x7FFFFF)
        MinGain = 0x7FFFFF;

    if(AUDIO_OFF == onoff)
        MinGain = 0x800000;

    switch(section)
    {
        case Front:
            Address = HDSP_X_FCLim_MinGainFR;
            break;
            
        case Rear:
        case Secondary:    
            Address = HDSP_X_FCLim_MinGainRS;
            break;
            
        case SubCenter:
            Address = HDSP_X_FCLim_MinGainSwL;
            break;
            
        case SubWoofer:
            Address = HDSP_X_FCLim_MinGainSwR;
            break;
    }

    Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM, Address, MinGain);

    return (Result);
}
/**********************************************************
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvLimiterFlagGenerSet(eAudioChannel section,int8_t clipdetectMask,uint32_t polarity)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_FLAG_GENE_SET;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    int32_t Mask = (int32_t)clipdetectMask;
    uint16_t Address;

    switch(sHero.LimiterFGS)
    {
        case OPERATION_0:
            switch(section)
            {
                case Front:    
                    Address = HDSP_X_FCLim_FlgGenMaskFR;    
                    break;
                    
                case Rear:
                case Secondary:    
                    Address = HDSP_X_FCLim_FlgGenMaskRS;    
                    break;
                    
                case SubCenter:    
                    Address = HDSP_X_FCLim_FlgGenMaskSwL;    
                    break;
                    
                case SubWoofer:    
                    Address = HDSP_X_FCLim_FlgGenMaskSwR;    
                    break;
            }
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM, Address, Mask);    
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SpecialGotoStep(sHero.LimiterFGS, OPERATION_1);
            }
            break;
            
        case OPERATION_1:
            //Mask = (int32_t)polarity;
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM, HDSP_X_FCLim_FlgGenDSPIO_Polarity, (int32_t)polarity);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.LimiterFGS = 0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            SubResult = SUBLAYER_ERROR;    
            break;
    }
    
    if(SUBLAYER_ERROR == SubResult)
    {
        Result = SUBLAYER_ERROR;    
    }
    
    return (Result);
}
/**********************************************************
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvSoftClipDetectSet(uint8_t section,int8_t ThreGain)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SOFT_CLIP_DETECT;
    uint8_t Result = SUBLAYER_DOING;
    uint16_t addr;
    int32_t Threshold = (int32_t)(((uint32_t)Tab_Db2Lin[-ThreGain]+1)*4096); 
    
    if(Threshold > 0x7FFFFF)
        Threshold = 0x7FFFFF;
    
    switch(section)
    {
        case SCD0:
            addr=HDSP_X_SCD_Thresh0;
            break;

        case SCD1:
            addr=HDSP_X_SCD_Thresh1;
            break;

        case SCD2:
            addr=HDSP_X_SCD_Thresh2;
            break;

        case SCD3:
            addr=HDSP_X_SCD_Thresh3;
            break;
    }
      Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM, addr, Threshold);

    return (Result);
}


/**********************************************************
 * @function    Hero_PinConnect
 * @brief      Config GPIO's Special Function
 * @param      uint8_t GPIO_Num
 *                 uint32_t FeatureID
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvFastMuteConfig(uint8_t Polarity,double FallTime,double RiseTime)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_FASTMUTE_CONFIG;
    uint8_t Result = SUBLAYER_DOING;    
    uint8_t SubResult = SUBLAYER_DOING;    
    double Data1;
    int32_t Data;

    switch(sHero.FastMuteConfig)
    {
        case OPERATION_0:    // Fall time
            if(Polarity)
            {
                Data1=0.8*4.0/(44.1*FallTime);
            }
            else
            {
                Data1=0.0-0.8*4.0/(44.1*FallTime);
            }
            Hero_TransDouble2XYHexData(HERO_XDATA,Data1,&Data);
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_X_Mute_StpAttDac,Data);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SpecialGotoStep(sHero.FastMuteConfig, OPERATION_1);
            }
            break;

        case OPERATION_1:    // Rise time
            if(Polarity)
            {
                Data1=0.8*4.0/(44.1*RiseTime);
            }
            else
            {
                Data1=0.0-0.8*4.0/(44.1*RiseTime);
            }
            Hero_TransDouble2XYHexData(HERO_XDATA,Data1,&Data);
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_X_Mute_StpRelDac,Data);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.FastMuteConfig = 0;
                Result = SUBLAYER_DONE;
            }
            break;
    }

    if(SUBLAYER_ERROR == SubResult)
    {
        Result = SUBLAYER_ERROR;    
    }    
    
    return (Result);
}
/**********************************************************
 * @function    Hero_RadioConfigInit
 * @brief      Config Radio Init
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_RadioConfigInit(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_RADIO_CONFIG;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[3];    
    
    Buffer[0] = 0xC9;    //set audio sample rate frequency shift mode
    Buffer[1] = 0x02;
    Buffer[2] = 0x01;
            
    Result = Hero_WriteCommon(PrivateID,Buffer,3);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_RadioInitAll
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_RadioInitAll(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_RADIO_INIT;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t IIcDataBuff[29];

    if(0)//TUNER_BAND_AM)     // Closed Temp
    {
	    IIcDataBuff[0] = 0x03;
	    IIcDataBuff[1] = NXP663X_AM_TUNER;
	    IIcDataBuff[2] = NXP663X_AM_OPT; 
	    IIcDataBuff[3] = NXP663X_AM_RADIO;
	    IIcDataBuff[4] = NXP663X_AM_SIGNAL;

	    IIcDataBuff[5] = NXP663X_AM_BWCTRL;
	    IIcDataBuff[6] = NXP663X_AM_SPECIAL;
	    IIcDataBuff[7] = NXP663X_AM_RDS;
	    IIcDataBuff[8] = 0;
	    IIcDataBuff[9] = 0;
	    IIcDataBuff[10] = NXP663X_AM_LEV_OFFSET;
	    //Softmute 
	    IIcDataBuff[11] = NXP663X_AM_SM_TIME;
	    IIcDataBuff[12] = NXP663X_AM_SM_DET;
	    IIcDataBuff[13] = NXP663X_AM_SM_LEV; 
	    IIcDataBuff[14] = NXP663X_AM_SM_NM;
	    IIcDataBuff[15] = NXP663X_AM_SM_LIM; 
	    //high cut
	    IIcDataBuff[16] = NXP663X_AM_HC_TIME;
	    IIcDataBuff[17] = NXP663X_AM_HC_DET;
	    IIcDataBuff[18] = NXP663X_AM_HC_LEV;
	    IIcDataBuff[19] = NXP663X_AM_HC_NM;
	    IIcDataBuff[20] = NXP663X_AM_HC_LIM;
	    IIcDataBuff[21] = NXP663X_AM_HC_LOC;
	    //stereo
	    IIcDataBuff[22] = NXP663X_AM_ST_TIME;
	    IIcDataBuff[23] = NXP663X_AM_ST_DET;
	    IIcDataBuff[24] = NXP663X_AM_ST_LEV;
	    IIcDataBuff[25] = NXP663X_AM_ST_NM;
	    IIcDataBuff[26] = NXP663X_AM_ST_LIM;
	    IIcDataBuff[27] = NXP663X_AM_STHB_DET;
	    IIcDataBuff[28] = NXP663X_AM_STHB_LNM; 
    }
	else
    {
		IIcDataBuff[0] = 0x03;
		IIcDataBuff[1] = NXP663X_FM_TUNER;
		IIcDataBuff[2] = NXP663X_FM_OPT; 
		IIcDataBuff[3] = NXP663X_FM_RADIO;
		IIcDataBuff[4] = NXP663X_FM_SIGNAL;

		IIcDataBuff[5] = NXP663X_FM_BWCTRL;
		IIcDataBuff[6] = NXP663X_FM_SPECIAL;
		IIcDataBuff[7] = NXP663X_FM_RDS;
		IIcDataBuff[8] = 0;
		IIcDataBuff[9] = 0;
		IIcDataBuff[10] = NXP663X_FM_LEV_OFFSET;
		//Softmute 
		IIcDataBuff[11] = NXP663X_FM_SM_TIME;
		IIcDataBuff[12] = NXP663X_FM_SM_DET;
		IIcDataBuff[13] = NXP663X_FM_SM_LEV; 
		IIcDataBuff[14] = NXP663X_FM_SM_NM;
		IIcDataBuff[15] = NXP663X_FM_SM_LIM; 
		//high cut
		IIcDataBuff[16] = NXP663X_FM_HC_TIME;
		IIcDataBuff[17] = NXP663X_FM_HC_DET;
		IIcDataBuff[18] = NXP663X_FM_HC_LEV;
		IIcDataBuff[19] = NXP663X_FM_HC_NM;
		IIcDataBuff[20] = NXP663X_FM_HC_LIM;
		IIcDataBuff[21] = NXP663X_FM_HC_LOC;
		//stereo
		IIcDataBuff[22] = NXP663X_FM_ST_TIME;
		IIcDataBuff[23] = NXP663X_FM_ST_DET;
		IIcDataBuff[24] = NXP663X_FM_ST_LEV;
		IIcDataBuff[25] = NXP663X_FM_ST_NM;
		IIcDataBuff[26] = NXP663X_FM_ST_LIM;
		IIcDataBuff[27] = NXP663X_FM_STHB_DET;
		IIcDataBuff[28] = NXP663X_FM_STHB_LNM;
    }
            
    Result = Hero_WriteCommon(PrivateID,IIcDataBuff,29);
    
    return (Result);
}
/**********************************************************
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
 uint8_t Hero_DrvSetPSInput(Audio_Stream_t Stream,eAudio_InputSource Input)
{
    HERO_DRIVER_TYPE_ENUM PrivateID =  HERO_IIC_SET_PS_INPUT;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buff[2];

    if(PrimaryStr == Stream)
    {
        Buff[0] = 0x20;
    }
    else
    {
        Buff[0] = 0x28;
    }
    Buff[1] = Input;    // AIN3 is Not Available 

    Result = Hero_WriteCommon(PrivateID, Buff, 2);

    return (Result);
}
/**********************************************************
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvSetNavInput(eAudio_InputSource Input)
{
    HERO_DRIVER_TYPE_ENUM PrivateID =  HERO_IIC_SET_NAV_INPUT;
    uint8_t Result = SUBLAYER_DOING;
    
    switch(Input)
    {
        case INPUT_SOURCE_AIN3:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_EasyP_Index,HDSP_EASYP_SrcSw_AIN3onNav);
            break;
        case INPUT_SOURCE_IIS0:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_pSRCInputFlag2,HDSP_X_InputFlagIIS0);
            break;
        case INPUT_SOURCE_IIS1:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_pSRCInputFlag2,HDSP_X_InputFlagIIS1);
            break;
        case INPUT_SOURCE_IIS2:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_pSRCInputFlag2,HDSP_X_InputFlagIIS2);
            break;
        case INPUT_SOURCE_SPDIF:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_pSRCInputFlag2,HDSP_X_InputFlagSPDIF);
            break;
        default:
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvSetPhoneInput(eAudio_InputSource Input)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_PHONE_INPUT;
    uint8_t Result = SUBLAYER_DOING;
    
    switch(Input)
    {
        case INPUT_SOURCE_AIN2:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_EasyP_Index,HDSP_EASYP_SrcSw_AIN2onPhone);
            break;
            
        case INPUT_SOURCE_IIS0:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_pSRCInputFlag3,HDSP_X_InputFlagIIS0);
            break;
            
        case INPUT_SOURCE_IIS1:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_pSRCInputFlag3,HDSP_X_InputFlagIIS1);
            break;
            
        case INPUT_SOURCE_IIS2:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_pSRCInputFlag3,HDSP_X_InputFlagIIS2);
            break;
            
        case INPUT_SOURCE_SPDIF:
            Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_pSRCInputFlag3,HDSP_X_InputFlagSPDIF);
            break;
            
        default:
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvSetInputAnalogMode(eAudio_InputSource Input,eInput_Analog_Mode mode)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_ANALOG_MODE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buff[3];
    
    Buff[0] = 0xA9;
    
    /*check parameters*/
    if((Input < INPUT_SOURCE_AIN0) || (Input > INPUT_SOURCE_AIN3))
        return (SUBLAYER_DONE);
        
    Buff[1] = Input-INPUT_SOURCE_AIN0;//trans to the realy channel ID
    Buff[2] = mode;
    Result = Hero_WriteCommon(PrivateID, Buff, 3);

    return (Result);
}
/**********************************************************
 * @function    Hero_DrvSetVolume
 * @brief      Set Volume
 * @param      uint8_t Volume    
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvSetVolume(uint8_t Volume, uint8_t Type)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_DRV_SET_VOL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    int32_t Volume_Data01,Volume_Data02;
    uint32_t Addr;
    int8_t VoldB;    
    uint8_t Temp;

    VoldB = Tab_VolDbLev[Volume];    
    VoldB -= (sAudioDat.sInfo.VolCurveDelta-2); //Temporary .....    //减小sAudioDat.sInfo.VolCurveDelta的修正偏移量,可以调节音量增益.....20161105

    switch(Type) //Get Address
    {
        case SYSTEM_FRONT: //System Front
            Addr = HDSP_Y_Vol_Main1P;
            break;

        case SYSTEM_REAR:  //System Front
            Addr = HDSP_Y_Vol_Main1S;
            break;

        case SYSTEM_ALL:  //System All
            Addr = HDSP_Y_Vol_Main1P;
            break;
    }

    if(VoldB >= 0.0)            
    {
        Volume_Data01 = 0x07FF;
        Volume_Data02 = Tab_Db2Lin[H_VolMaxP - VoldB];
    }
    else if(VoldB >= (-H_LoudBoostMaxP))
    {
        Volume_Data01 = Tab_Db2Lin[-VoldB];
        Volume_Data02 = Tab_Db2Lin[H_VolMaxP];
    }
    else if(VoldB >= (H_VolMaxP - H_LoudBoostMaxP - H_FixedBoostP))
    {
        Volume_Data01 = Tab_Db2Lin[H_LoudBoostMaxP];
        Volume_Data02 = Tab_Db2Lin[H_VolMaxP - H_LoudBoostMaxP - VoldB];
    }
    else
    {
        Volume_Data01 = Tab_Db2Lin[H_VolMaxP - VoldB - H_FixedBoostP];
        Volume_Data02 = 0x008;
    }
    
    switch(sAudio.DrvVolStep)
    {
        case OPERATION_0:
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,Addr,Volume_Data01);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_1;
            }
            break;

        case OPERATION_1:
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,(Addr+1),Volume_Data02);
            if(SUBLAYER_DONE == SubResult)
            {    
                if(SYSTEM_ALL == Type)
                {
                    sAudio.DrvVolStep = OPERATION_2;
                }
                else
                {
                    sAudio.DrvVolStep = OPERATION_4;
                }
            }
            break;

        case OPERATION_2:
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,(Addr+2),Volume_Data01); //the primary volume will be divided to 2 prara
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_3;
            }
            break;

        case OPERATION_3:
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,(Addr+3),Volume_Data02);//the primary volume will be divided to 2 prara
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_4;
            }
            break;
        
        case OPERATION_4:    //Loudness: Maybe Not Need
            if((LOUDNESS_ON == sAudioDat.sBasic.sLoudnessMode)     //Need to Set Newly boost for Primary Channel
                && ((SYSTEM_FRONT == Type) || (SYSTEM_ALL == Type)))
            {    
                if((Volume >= 30) || (0 == Volume)) //Volume == 30, 8DB
                {
                    Volume_Data01 = 0x07FF; //No Boost
                }
                else
                {
                    Temp = Tab_Loudness_B_Curve[(30 * sAudioDat.sBasicBK.sLoudness.BassCutOff) + Volume];
                    if(0 == Temp)
                    {
                        Volume_Data01 = 0x07FF;
                    }
                    else
                    {
                        Volume_Data01 = (int32_t)Hero_Calc_LoudBoost(0,Temp);    
                    }
                }
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Loudf_StatLev_REL,Volume_Data01);
                if(SUBLAYER_DONE == SubResult)
                {
                #ifdef D_AUDIO_ENABLE_LDT  
                    sAudio.DrvVolStep = OPERATION_5;
                #else
                    sAudio.DrvVolStep = OPERATION_0; //Clear 
                    Result = SUBLAYER_DONE;
                #endif
                }
            }
            else
            {
                sAudio.DrvVolStep = OPERATION_0; //Clear 
                Result = SUBLAYER_DONE;
            }
            Result = SUBLAYER_DONE;
            break;

        //Loudness:Treble Boost
    #ifdef D_AUDIO_ENABLE_LDT  
        case OPERATION_5:
            if((Volume >= 30) || (0 == Volume)) //Volume == 30, 8DB
            {
                Volume_Data01 = 0x07FF; //No Boost
            }
            else
            {
                Temp = Tab_Loudness_T_Curve[(30 * sAudioDat.sBasicBK.sLoudness.TrebleCentre) + Volume];
                if(0 == Temp)
                {
                    Volume_Data01 = 0x07FF;
                }
                else
                {
                    Volume_Data01 = (int32_t)Hero_Calc_LoudBoost(1,Temp);    
                }
            }
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Loudf_StatLevT_REL,Volume_Data01);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_0; //Clear 
                Result = SUBLAYER_DONE;
            }
            break;    
      #endif      
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_NavPhoneVol
 * @brief      Set Nav or Phone Channel Volume
 * @param      uint8_t Val        
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Hero_NavPhoneVol(uint8_t Val,uint8_t Type)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_NAV_PHONE_VOL;
    uint8_t Result = SUBLAYER_DOING;
    int8_t VolVal;
    int32_t VolDat;
    uint16_t Addr;

    if(0 == Type) //Navi Channel
    {
        Addr    = HDSP_Y_Vol_Nav_REL; 
    }
    else //Phone Channel
    {
        Addr    = HDSP_Y_Vol_Phon_REL; 
    }

    //Get Actually Volume Db Value
    VolVal = (Tab_VolDbLev[Val] / 2) + CHANNEL_VOL_DELTA;      
    //VolDat = Tab_Db2Lin[12 - VolVal];
    VolDat = Tab_NaviPhone_Vol[12 - VolVal];
    
    Result = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,Addr,VolDat);

    return (Result);
}
/**********************************************************
 * @function    Hero_SetVolume
 * @brief      Improve Radio Setting For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
 /*				地址
I2CW S C0 n F2  42 CE  05 ED 00 7E 03 D9 0C FD 02 99 06 18 0F D4  P 
	42 CE : 命令写PEQ 数据   
	05 ED 00 7E 03 D9 0C FD 02 99 06 18 0F D4 : 数据两个字节表示一个数据
I2CW  S C0 n F2 02 B8 00 03 E7 P 
	02 B8 : 写入的地址掩码      
	00 03 E7  : 具体地址
I2CW S C0 n F2 02 B9 00 00 07 P 
	02 B9 : 长度指引
	00 00 07:  具体数据长度
*/
uint8_t Hero_DrvPEQSet(eAudioChannel Channel, uint8_t Band, uint16_t* Coefs)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_PEQ;
    uint8_t Result = SUBLAYER_DOING;
    uint16_t Label = 0;
    uint8_t filterCoefficients = 10;

        switch (Channel)
    {
        case FrontLeft:/*front left*/
            switch (Band)
            {
                case BAND1:
                    Label = (uint16_t)(HDSP_Y_EqFL_b10L_REL);
                    filterCoefficients = 7;
                    break;

                case BAND2:
                    Label = (uint16_t)(HDSP_Y_EqFL_b20L_REL);
                    filterCoefficients = 7;
                    break;

                case BAND3:
                    Label = (uint16_t)(HDSP_Y_EqFL_b30L_REL);
                    filterCoefficients = 7;
                    break;
                    
                case BAND4: 
                    Label = (uint16_t)(HDSP_Y_EqFL_b40L_REL);
                    filterCoefficients = 7;
                    break;

                case BAND5:
                    Label = (uint16_t)(HDSP_Y_EqFL_b50L_REL);
                    filterCoefficients = 10;
                    break;

                case BAND6:
                    Label = (uint16_t)(HDSP_Y_EqFL_b60L_REL);
                    filterCoefficients = 10;
                    break;

                case BAND7:
                    Label = (uint16_t)(HDSP_Y_EqFL_b70L_REL);
                    filterCoefficients = 10;
                    break;

                default:
                    filterCoefficients = 0;
                    break;
            }
            break;

        case FrontRight:/*front right*/
            switch (Band)
            {
                case BAND1:
                    Label = (uint16_t)(HDSP_Y_EqFR_b10L_REL);
                    filterCoefficients = 7;
                    break;

                case BAND2:
                    Label = (uint16_t)(HDSP_Y_EqFR_b20L_REL);
                    filterCoefficients = 7;
                    break;

                case BAND3:
                    Label = (uint16_t)(HDSP_Y_EqFR_b30L_REL);
                    filterCoefficients = 7;
                    break;

                case BAND4: 
                    Label = (uint16_t)(HDSP_Y_EqFR_b40L_REL);
                    filterCoefficients = 7;
                    break;

                case BAND5:
                    Label = (uint16_t)(HDSP_Y_EqFR_b50L_REL);
                    filterCoefficients = 10;
                    break;

                case BAND6:
                    Label = (uint16_t)(HDSP_Y_EqFR_b60L_REL);
                    filterCoefficients = 10;
                    break;

                case BAND7:
                    Label = (uint16_t)(HDSP_Y_EqFR_b70L_REL);
                    filterCoefficients = 10;
                    break;

                default:
                    filterCoefficients = 0;
                    break;
            }
            break;

        case RearLeft:/*rear left*/
            switch (Band)
            {
                case BAND1:
                Label = (uint16_t)(HDSP_Y_EqRL_b10L_REL);
                filterCoefficients = 7;
                break;

                case BAND2:
                Label = (uint16_t)(HDSP_Y_EqRL_b20L_REL);
                filterCoefficients = 7;
                break;

                case BAND3:
                Label = (uint16_t)(HDSP_Y_EqRL_b30L_REL);
                filterCoefficients = 7;
                break;

                case BAND4: 
                Label = (uint16_t)(HDSP_Y_EqRL_b40L_REL);
                filterCoefficients = 7;
                break;

                case BAND5:
                Label = (uint16_t)(HDSP_Y_EqRL_b50L_REL);
                break;

                case BAND6:
                Label = (uint16_t)(HDSP_Y_EqRL_b60L_REL);
                break;

                case BAND7:
                Label = (uint16_t)(HDSP_Y_EqRL_b70L_REL);
                break;        
                default:
                filterCoefficients = 0;
                break;
            }
            break;

        case RearRight:
            switch (Band)
            {
                case BAND1:
                Label = (uint16_t)(HDSP_Y_EqRR_b10L_REL);
                filterCoefficients = 7;
                break;

                case BAND2:
                Label = (uint16_t)(HDSP_Y_EqRR_b20L_REL);
                filterCoefficients = 7;
                break;

                case BAND3:
                Label = (uint16_t)(HDSP_Y_EqRR_b30L_REL);
                filterCoefficients = 7;
                break;

                case BAND4: 
                Label = (uint16_t)(HDSP_Y_EqRR_b40L_REL);
                filterCoefficients = 7;
                break;

                case BAND5:
                Label = (uint16_t)(HDSP_Y_EqRR_b50L_REL);
                break;

                case BAND6:
                Label = (uint16_t)(HDSP_Y_EqRR_b60L_REL);
                break;

                case BAND7:
                Label = (uint16_t)(HDSP_Y_EqRR_b70L_REL);
                break;

                default:
                filterCoefficients = 0;
                break;
            }
            break;
#if 0
        case SubWoofer: /* SubWoofer pointer is located at 'Center pointer' + Center Order * 5 */
        /* 'IIRFilterOrder' is the order of the IIR filter
        e.g. if the order of Center = 2 the SubWoofer pointer is at 
        2 * 5 = 10 addresses further                          */
        switch (Band)
        {
        case BAND1:
        Label = (uint16_t)(HDSP_Y_EqSwC_b00L_REL + (IIRFilterOrder * 5));
        break;

        case BAND2:
        Label = (uint16_t)(HDSP_Y_EqSwC_b10L_REL + (IIRFilterOrder * 5));
        break;

        case BAND3:
        Label = (uint16_t)(HDSP_Y_EqSwC_b20L_REL + (IIRFilterOrder * 5));
        break;

        case BAND4: 
        Label = (uint16_t)(HDSP_Y_EqSwC_b30L_REL + (IIRFilterOrder * 5));
        break;

        default:
        filterCoefficients = 0;
        break;
        }
        break;

        case Center:
        switch (Band)
        {
        case BAND1:
        Label = (uint16_t)(HDSP_Y_EqSwC_b00L_REL);
        break;

        case BAND2:
        Label = (uint16_t)(HDSP_Y_EqSwC_b10L_REL);
        break;

        case BAND3:
        Label = (uint16_t)(HDSP_Y_EqSwC_b20L_REL);
        break;

        case BAND4: 
        Label = (uint16_t)(HDSP_Y_EqSwC_b30L_REL);
        break;

        default:
        filterCoefficients = 0;
        break;
        }
        break;
#endif
        default:
            filterCoefficients = 0;
            break;
    }
    /*write data to hero*/
    if(filterCoefficients)
        Result = Hero_ScratchDataWrite(PrivateID,Label,filterCoefficients,Coefs);
    else
        Result = SUBLAYER_DONE;
       return (Result);
}
/**********************************************************
 * @function    Hero_SetDcFilter
 * @brief      Hero Set DC Filter
 * @param      uint8_t Val
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetDcFilter(uint8_t Val, uint8_t Type)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_DC_FILTER;
    uint8_t Result = SUBLAYER_DOING;
    int32_t Coeffs[3];
    uint16_t Label = 0;
    float TmpA,TmpB;

    if(SYSTEM_FRONT == Type)
    {
        Label = HDSP_Y_DCfilt_a1A_REL;
    }
    else if(SYSTEM_REAR == Type)
    {
        Label = HDSP_Y_DCfilt_a1B_REL;
    }

    if(0 == Val)    //DC Filter Off, Set Flat Response
    {
        Coeffs[0] = 0x000;    //Convert to Hex
        Coeffs[1] = 0x000;
        Coeffs[2] = 0x800;
    }
    else
    {
        //Total Math account cost about 100us!!!!!
        TmpB = PI * ((Val * 3.5) / ASRate - 0.25);
        TmpA = -tanf(TmpB);  //a1 value
        TmpB = TmpA;
        TmpA *= 2048;
        Coeffs[0] = RoundChange(TmpA,0);  //Convert to HEX and Round
    
        TmpB = -0.5 - (0.5 * TmpB);  //b0 value
        TmpB *= 2048;
        Coeffs[1] = RoundChange(TmpB,0);    //Convert to Hex and Round
        Coeffs[1] &= 0x0FFF;
        Coeffs[2] = Coeffs[1];
    }

    Result = Hero_WriteMemData(PrivateID,I2CDRV_Y_MEM,Label,3,Coeffs);

    return (Result);
}
/**********************************************************
 * @function    Hero_SetVolume
 * @brief      Improve Radio Setting For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvNavPhoneFilterSet(eAudio_Feature_t Feature, uint32_t Section, uint16_t* Coefs)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_NAV_PHONE_FILTER;
    uint8_t Result = SUBLAYER_DOING;
    uint16_t Label = 0;

    switch (Feature)
    {
        case NavigationFilter:/*nav filter*/
            switch (Section)
            {
                case 0:
                    Label = HDSP_Y_EqN_b00L_REL;
                    break;
                case 1:
                    Label = HDSP_Y_EqN_b10L_REL;
                    break;   
                default:
                    break;   
            }
            break;   

        case PhoneFilter:/*phone filter*/
            switch (Section)
            {
                case 0:
                    Label = HDSP_Y_EqT_b00L_REL;
                    break;

                case 1:
                    Label = HDSP_Y_EqT_b10L_REL;                   
                    break;   
                default:
                    break;   
                }
                break; 

            default:
                break;   
    }
    
    /*write data to hero*/
    if(Label != 0)
    {
        Result = Hero_ScratchDataWrite(PrivateID,
                                    Label,
                                    10,
                                    Coefs);
    }
    else
    {
        Result = SUBLAYER_DONE;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Hero_DrvSuperPositionGain
 * @brief      Improve Radio Setting For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_NavPhoneFilterInit(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sHero.ThirdLayerStep)
    {
        /*Nav Filter set :band pass (100hz--3400hz)*/
        case OPERATION_0:
            SubResult = Hero_DrvNavPhoneFilterSet(NavigationFilter,0,(uint16_t*)Tab_NavPhone_Filter1Coefs);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.ThirdLayerStep = OPERATION_1;
            }
            break;

        case OPERATION_1:
            SubResult = Hero_DrvNavPhoneFilterSet(NavigationFilter,1,(uint16_t*)Tab_NavPhone_Filter2Coefs);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.ThirdLayerStep = OPERATION_2;
            }
            break;
            
        /*Phone Filter set: band pass (100hz--3400hz)*/
        case OPERATION_2:
            SubResult = Hero_DrvNavPhoneFilterSet(PhoneFilter,0,(uint16_t*)Tab_NavPhone_Filter1Coefs);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.ThirdLayerStep = OPERATION_3;
            }
            break;

        case OPERATION_3:
            SubResult = Hero_DrvNavPhoneFilterSet(PhoneFilter,1,(uint16_t*)Tab_NavPhone_Filter2Coefs);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.ThirdLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        case OPERATION_4:

            break;
    }

    return (Result);
}


//------------------------------------------------------------------
//1 Audio Related Functions
/**********************************************************
 * @function    Hero_ScalingInit
 * @brief      Initial Scaling Strategy
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_ScalingInit(void)
{    
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_INIT_SCALINGINT;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Hero_WriteMemTab(PrivateID,Tab_ScalingInit);

    return (Result);
}
/**********************************************************
 * @function    Hero_InitChanGain
 * @brief      Initial Channel Gain
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_InitChanGain(void)
{    
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_INIT_CHANNEL_GAIN;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Hero_WriteMemTab(PrivateID,Tab_ChanGainInit);

    return (Result);
}
/**********************************************************
 * @function    Hero_SetChanGain
 * @brief      Initialize Channel Gain
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetChanGain(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_CHANNEL_GAIN;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;    
    uint16_t Addr;
    int32_t Data;

    switch(sAudio.ChanGainCtl)
    {
        case CHANGAIN_CTL_FL: //Set Primary Front Left Channel
            if(sAudio.ChanGainMask & CHANGAIN_MASK_FL)
            {
                Data = Tab_Db2Lin[H_ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_FL]];
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_ChanGainPFL_REL,Data); 
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ChanGainMask &= (~CHANGAIN_MASK_FL);
                sAudio.ChanGainCtl = CHANGAIN_CTL_FR;
            }
            break;

        case CHANGAIN_CTL_FR:
            if(sAudio.ChanGainMask & CHANGAIN_MASK_FR)
            {
                Data = Tab_Db2Lin[H_ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_FR]];
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_ChanGainPFR_REL,Data); 
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ChanGainMask &= (~CHANGAIN_MASK_FR);
                sAudio.ChanGainCtl = CHANGAIN_CTL_RL;
            }
            break;

        case CHANGAIN_CTL_RL:
            if(sAudio.ChanGainMask & CHANGAIN_MASK_RL)
            {
                Data = Tab_Db2Lin[H_ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_RL]];
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_ChanGainPRL_REL,Data); 
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ChanGainMask &= (~CHANGAIN_MASK_RL);
                sAudio.ChanGainCtl = CHANGAIN_CTL_RR;
            }
            break;    

        case CHANGAIN_CTL_RR:
            if(sAudio.ChanGainMask & CHANGAIN_MASK_RR)
            {
                Data = Tab_Db2Lin[H_ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_RR]];
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_ChanGainPRR_REL,Data); 
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ChanGainMask &= (~CHANGAIN_MASK_RR);
                sAudio.ChanGainCtl = CHANGAIN_CTL_SWL;
            }
            break;    

        case CHANGAIN_CTL_SWL:
            if(sAudio.ChanGainMask & CHANGAIN_MASK_SWL)
            {
                Data = Tab_Db2Lin[H_ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_SWL]];
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_ChanGainSwL_REL,Data); 
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ChanGainMask &= (~CHANGAIN_MASK_SWL);
                sAudio.ChanGainCtl = CHANGAIN_CTL_SWR;
            }
            break;    

        case CHANGAIN_CTL_SWR:
            if(sAudio.ChanGainMask & CHANGAIN_MASK_SWR)
            {
                Data = Tab_Db2Lin[H_ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_SWR]];
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_ChanGainSwR_REL,Data); 
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ChanGainMask &= (~CHANGAIN_MASK_SWR);
                Result = SUBLAYER_DONE;
                sAudio.ChanGainCtl = CHANGAIN_CTL_FL;
            }
            break;    
    }

    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.ChanGainCtl = CHANGAIN_CTL_FL;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_SrcScalingInit
 * @brief      Initialize source scaling settings...
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_SrcScalingInit(void)
{    
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SRC_SCALER;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Hero_WriteMemTab(PrivateID,Tab_SrcScaling);

    return (Result);
}
/**********************************************************
 * @function    Hero_SetSrcScaler
 * @brief      Initialize source scaling settings...
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetSrcScaler(uint8_t Type, uint8_t Val)
{    
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SRC_SCALER;
    uint8_t Result = SUBLAYER_DOING;
    uint16_t Addr;
    int32_t Data;
    
    if(SYSTEM_FRONT == Type)    
    {
        Addr = HDSP_Y_Vol_SrcScalP_REL;
    }
    else if(SYSTEM_REAR == Type)
    {
        Addr = HDSP_Y_Vol_SrcScalS_REL;    
    }
    
    Data = Tab_Db2Lin[12 - Val];
    
    Result = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,Addr,Data); //the primary volume will be divided to 2 prara

    return (Result);
}
/**********************************************************
 * @function    Hero_AudioPointer
 * @brief      Connect Audio Pointer
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_AudioPointer(void)
{    
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_AUDIO_POINTER;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Hero_WriteMemTab(PrivateID,Tab_AudioPointer);

    return (Result);
}
/**********************************************************
 * @function    Hero_SetLoudness
 * @brief      Set Loudness On/Off
 * @param      NULL        
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetLoudness(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_LOUDNESS;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Coeffs;

    switch(sAudio.LoudnessCtl)
    {
        //Initialize Loudness Mode: Static Independent
        case LOUD_CTL_INIT:
            if(sAudio.LoudnessMask & LOUD_MASK_INIT)    
            {
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_EasyP_Index_REL,HDSP_EASYP_Loudf_StaticIndep);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.LoudnessCtl = LOUD_CTL_CONFIG;
                }
            }
            else
            {
                sAudio.LoudnessCtl = LOUD_CTL_ON_OFF;
            }
            break;
            
        //Load Config
        case LOUD_CTL_CONFIG:
            SubResult = Hero_WriteMemTab(PrivateID,Tab_Loudness_Config);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.LoudnessMask &= (~LOUD_MASK_INIT);
                sAudio.LoudnessCtl = LOUD_CTL_ON_OFF;
            }
            break;

        //Set Loudness ON.OFF
        case LOUD_CTL_ON_OFF:
            if(sAudio.LoudnessMask & LOUD_MASK_ON_OFF)
            {
                if(LOUDNESS_ON == sAudioDat.sBasic.sLoudnessMode)
                {
                    sAudio.LoudnessMask |= (LOUD_MASK_BASS_COF | LOUD_MASK_TREBLE_CF); 
                    sAudio.LoudnessCtl = LOUD_CTL_BASS_COF;
                }
                else
                {
                    sAudio.LoudnessCtl = LOUD_CTL_OFF_BASS;
                }
            }
            else
            {
                sAudio.LoudnessCtl = LOUD_CTL_BASS_COF;
            }
            break;

        //Set Bass Boost to Zero
        case LOUD_CTL_OFF_BASS:
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Loudf_StatLev_REL,0x07FF);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.LoudnessCtl = LOUD_CTL_OFF_TREBLE;
                //If coupled, "HDSP_Y_Loudf_StatLevT_REL" is not needed
            }
            break;

        //Set Treble Boost to Zero
        case LOUD_CTL_OFF_TREBLE:
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Loudf_StatLevT_REL,0x07FF);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.LoudnessCtl = LOUD_CTL_END;
            }
            break;

        //Load Bass Coefficient
        case LOUD_CTL_BASS_COF:
            if(sAudio.LoudnessMask & LOUD_MASK_BASS_COF)
            {
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_Loudf_a1bL_REL,8,(uint16_t*)(&Tab_Loudness_Bass[8 * sAudioDat.sBasicBK.sLoudness.BassCutOff]));
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.LoudnessMask &= (~LOUD_MASK_BASS_COF);
                sAudio.LoudnessCtl = LOUD_CTL_TREBLE_CF;
            }    
            break;

        //Load Treble Coefficient
        case LOUD_CTL_TREBLE_CF:
            if(sAudio.LoudnessMask & LOUD_MASK_TREBLE_CF)    
            {
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_Loudf_a1t_REL,5,(uint16_t*)(&Tab_Loudness_Treble[5 * sAudioDat.sBasicBK.sLoudness.TrebleCentre]));
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.LoudnessMask &= (~LOUD_MASK_TREBLE_CF);
                sAudio.LoudnessCtl = LOUD_CTL_END;
            }
            break;

        case LOUD_CTL_END:
            sAudio.LoudnessCtl = LOUD_CTL_INIT;
            if(sAudio.LoudnessMask & LOUD_MASK_ON_OFF)
            {
                sAudio.LoudnessMask &= (~LOUD_MASK_ON_OFF);
                //Re-Set Volume with specific loudness boost: Closed ,not sure needed!
                //SendMessageToAudio(MSG_TO_AUDIO_OPERATE,AUDIO_OP_VOL_SEL,sAudioDat.sInfo.CurrentlyVol);
            }
            Result = SUBLAYER_DONE;
            break;
    }

    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.LoudnessCtl = LOUD_CTL_INIT;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_DrvSuperPositionGain
 * @brief      Improve Radio Setting For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvSuperPositionGain(HERO_DRIVER_TYPE_ENUM PID,uint8_t AddOnIndex, int8_t PresetGain) 
{
    uint8_t Result = SUBLAYER_DOING;
    HERO_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Length = 1;    //control every speaker alone
    uint16_t Label = 0;
    int32_t Gain[4];

    if((-100) == PresetGain) // Mix OFF
    {
        Gain[0] = 0x0FFF;    
        Gain[1] = 0x0FFF;    
        Gain[2] = 0x0FFF;    
        Gain[3] = 0x0FFF;    
    }
    else
    {
        Gain[0] = 0x1000 - Tab_Db2Lin[-PresetGain];    //First Gain
        Gain[1] = 0x1000 - Tab_Db2Lin[-PresetGain];    //Sencond Gain
        Gain[2] = 0x1000 - Tab_Db2Lin[-PresetGain];    //Third Gain
        Gain[3] = 0x1000 - Tab_Db2Lin[-PresetGain];    // Fourth gain
    }
    switch(AddOnIndex)
    {
        case P_MIX_NAV_FL: //Primary mix with Nav FL
            Label = HDSP_Y_Sup_NonFL_REL;
            break;
        case P_MIX_NAV_FR: 
            Label = HDSP_Y_Sup_NonFR_REL;
            break;
        case P_MIX_NAV_RL: 
            Label = HDSP_Y_Sup_NonRL_REL;
            break;
        case P_MIX_NAV_RR: 
            Label = HDSP_Y_Sup_NonRR_REL;
            break;
        case P_MIX_NAV_FRONT:
            Label = HDSP_Y_Sup_NonFL_REL;
            Length = 2;
            break;
        case P_MIX_NAV_REAR:
            Label = HDSP_Y_Sup_NonRL_REL;
            Length = 2;
            break;
        case P_MIX_NAV_ALL:
            Label = HDSP_Y_Sup_NonFL_REL;
            Length = 4;
            break;
            
        case P_MIX_PHONE_FL: //Primary mix with Phone FL
            Label = HDSP_Y_Sup_TonFL_REL;
            break;
        case P_MIX_PHONE_FR: 
            Label = HDSP_Y_Sup_TonFR_REL;
            break;
        case P_MIX_PHONE_RL: 
            Label = HDSP_Y_Sup_TonRL_REL;
            break;
        case P_MIX_PHONE_RR: 
            Label = HDSP_Y_Sup_TonRR_REL;
            break;
        case P_MIX_PHONE_FRONT:
            Label = HDSP_Y_Sup_TonFL_REL;
            Length = 2;
            break;
        case P_MIX_PHONE_REAR:
            Label = HDSP_Y_Sup_TonRL_REL;
            Length = 2;
            break;
        case P_MIX_PHONE_ALL:
            Label = HDSP_Y_Sup_TonFL_REL;
            Length = 4;
            break;
            
        case P_MIX_CHIME_FL: //Chime FL mix to Primary
            Label = HDSP_Y_Sup_ChionFL_REL;
            break;
        case P_MIX_CHIME_FR: 
            Label = HDSP_Y_Sup_ChionFR_REL;
            break;
        case P_MIX_CHIME_RL: 
            Label = HDSP_Y_Sup_ChionRL_REL;
            break;
        case P_MIX_CHIME_RR: 
            Label = HDSP_Y_Sup_ChionRR_REL;
            break;    
        case P_MIX_CHIME_FRONT:
            Label = HDSP_Y_Sup_ChionFL_REL;
            Length = 2;
            break;
        case P_MIX_CHIME_REAR:
            Label = HDSP_Y_Sup_ChionRL_REL;
            Length = 2;
            break;
        case P_MIX_CHIME_ALL:
            Label = HDSP_Y_Sup_ChionFL_REL;
            Length = 4;
            break; 

        case P_MIX_EXT_FL:
            Label = HDSP_Y_Sup_ExtonFL_REL;
            break;
        case P_MIX_EXT_FR:
            Label = HDSP_Y_Sup_ExtonFR_REL;
            break;            
        case P_MIX_EXT_FRONT:
            Label = HDSP_Y_Sup_ExtonFL_REL;
            Length = 2;
            break;            
        case P_MIX_EXT_ALL:
            Label = HDSP_Y_Sup_ExtonFL_REL;
            Length = 4;
            break;

        case S_MIX_CHIME_LEFT:    // Chime Front mix to Secondary
            Label = HDSP_Y_Sup_ChionSL_REL;
            break;
        case S_MIX_CHIME_RIGHT:
            Label = HDSP_Y_Sup_ChionSR_REL;
            break;
        case S_MIX_CHIME_ALL:
            Label = HDSP_Y_Sup_ChionSL_REL;
            Length = 2;
            break;
    }

    if((-100) == PresetGain) // Mix OFF
    {
        Label = HDSP_Y_Sup_NonFL_REL;
        Length = 2;   
    }

    Result = Hero_WriteMemData(PrivateID,I2CDRV_Y_MEM,Label,Length,Gain);

    return (Result);
}
/**********************************************************
 * @function    Hero_SetChimeMode
 * @brief      Set the Specific Chime
 * @param      uint8_t Mode:                
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetChimeMode(uint8_t Mode)
{
    uint8_t PrivateID = HERO_IIC_SET_CHIMEMODE;
    uint8_t Result = SUBLAYER_DOING;

    if(Mode == sAudio.BeepLast)
    {
        Result = Hero_WriteMemTab(PrivateID,Tab_FastChime);
    }
    else
    {
        switch(Mode)
        {
            case BEEP_TYPE_ALERT:
                Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_Chime_PSAlt); 
                break;
    
            case BEEP_TYPE_SEATBELT:
                Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_Chime_PSFsb); //see the para in UM
                break;
    
            case BEEP_TYPE_CONFIRMATION:
                Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_Chime_PSBle1); //see the para in UM
                break;
                
            case BEEP_TYPE_IGNITION:
                Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_Chime_PSKii); //see the para in UM
                break;
                
            case BEEP_TYPE_CRUISE:
                Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_Chime_PSCci); //see the para in UM
                break;
                
            case BEEP_TYPE_ORDINARY:
            case BEEP_TYPE_USER:    
            case BEEP_TYPE_KEY_ACK:
            case BEEP_TYPE_KEY_NCK:     
                if(BEEP_TYPE_SET_LOW == sAudioDat.sInfo.BeepType)
                {
                    Result = Hero_WriteMemTab(PrivateID,Tab_WholeChimeLow);
                }
                else if(BEEP_TYPE_SET_HIGH == sAudioDat.sInfo.BeepType)
                {
                    Result = Hero_WriteMemTab(PrivateID,Tab_WholeChimeHigh);
                }
                else
                {
                    Result = SUBLAYER_DONE;
                }
                break;

            case BEEP_TYPE_TYRE_ALERT:       
                Result = Hero_WriteMemTab(PrivateID,Tab_WholeChimeTyre);
                break;
                
            default:
                break;
        }
    }

    //Sync Last Chime Mode
    if(SUBLAYER_DONE == Result)
    {
        sAudio.BeepLast = Mode;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_DrvSetChimeMasterVol
 * @brief      Setup Chime Volume
 * @param      uint8_t vol:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvSetChimeMasterVol(uint8_t vol)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_CHIME_VOL;    
    uint8_t Result = SUBLAYER_DOING;
    int32_t Data;

    Data = Tab_Db2Lin[vol];     //Changed by deefisher

    Result = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM, HDSP_Y_Tsq_ChimeVol_Bk_REL,Data);

    return (Result);
}
/**********************************************************
 * @function    Hero_SetVolume
 * @brief      Improve Radio Setting For V1C
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_BeepInit(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sHero.ThirdLayerStep)
    {
        //Enable Chime
        case OPERATION_0:
            SubResult = Hero_EasyProgrammWrite(HERO_IIC_BEEPINIT,HDSP_EASYP_Chime_Enable); 
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.ThirdLayerStep = OPERATION_1;
            }
            break;

        //Impose Chime on Channel : Front 
        case OPERATION_1:
            SubResult = Hero_BeepPos(sAudioDat.sInfo.BeepPos);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.ThirdLayerStep = OPERATION_2;
            }
            break;

        //Set Beep Volume
        case OPERATION_2:
            SubResult = Hero_BeepVol(sAudioDat.sAdv.BeepVol);
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.ThirdLayerStep = 0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            sHero.ThirdLayerStep = 0;
            Result = SUBLAYER_STEP_ERROR;
            break;
    }    

    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;    
        sHero.ThirdLayerStep = 0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Hero_BeepVol
 * @brief      Set Beep Volume
 * @param      uint8_t Val:                
 * @retval     Result
 **********************************************************/
uint8_t Hero_BeepVol(uint8_t Val)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t VolVal;

    //40~0 equal to 0~ -66db
    VolVal = (66 - (Tab_BeepVolume[Val] * 66)/BEEP_VOL_MAX);
    
    Result = Hero_DrvSetChimeMasterVol(VolVal);

    return (Result);
}
/**********************************************************
 * @function    Hero_BeepVol
 * @brief      Set Beep Position
 * @param      uint8_t Val:                
 * @retval     Result
 **********************************************************/
uint8_t Hero_BeepPos(uint8_t Pos)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t DirectPos;

    //Transfer Ordinary Position to Chime Directly Control Position
    switch(Pos)
    {
        case MIX_TYPE_FL: //Front left speaker
            DirectPos = P_MIX_CHIME_FL;
            break;

        case MIX_TYPE_FR://Front Right speaker
            DirectPos = P_MIX_CHIME_FR;
            break;

        case MIX_TYPE_FRONT:
            DirectPos = P_MIX_CHIME_FRONT;    
            break;

        case MIX_TYPE_ALL:
            DirectPos = P_MIX_CHIME_ALL;
            break;    
    }

    Result = Hero_DrvSuperPositionGain(HERO_IIC_SET_IMPOSE,DirectPos,0);

    return (Result);
}
/**********************************************************
 * @function    Hero_Beep
 * @brief      Set the Specific Beep
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
uint8_t Hero_Beep(uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Hero_SetChimeMode(Type);

    return (Result);
}
/**********************************************************
 * @function    Hero_BeepStop
 * @brief      Stop Currently Beeping
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
uint8_t Hero_BeepStop(void)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Hero_WriteMemTab(HERO_IIC_BEEPSTOP,Tab_StopChime);

    return (Result);
}
/**********************************************************
 * @function    Hero_SoftMute
 * @brief      Set Channel Soft Mute
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_SoftMute(uint16_t Channel,uint8_t MuteData)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SOFTMUTE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t Action = 0;
    uint16_t Addr;
    int32_t Dat;

    if(MUTE_ON == MuteData)
    {
        Dat = 0x0000;
    }
    else
    {
        Dat = 0x07FF;
    }

    while(0 == Action)
    {
        switch(sAudio.SoftMuteStep)
        {    
            //Overall Primary Channel
            case OPERATION_0:
                if(Channel & HERO_CH_P)        
                {
                    Action = 1;
                    Addr = HDSP_Y_Mute_P_REL;
                }
                break;

            //OverAll Secondary channel    
            case OPERATION_1:
                if(Channel & HERO_CH_S)        
                {
                    Action = 1;
                    Addr = HDSP_Y_Mute_S_REL;
                }
                break;    
                
            //overall navigation channel
            case OPERATION_2:
                if(Channel & HERO_CH_NAV)        
                {
                    Action = 1;
                    Addr = HDSP_Y_Mute_N_REL;
                }
                break;
                
            //overall phone channel        
            case OPERATION_3:
                if(Channel & HERO_CH_PHONE)        
                {
                    Action = 1;
                    Addr = HDSP_Y_Mute_T_REL;
                }
                break;    
                
            //front left channel
            case OPERATION_4:
                if(Channel & HERO_CH_PFL)        
                {
                    Action = 1;
                    Addr = HDSP_Y_MuteSix_FL_REL;
                }
                break;
                
            //front right channel    
            case OPERATION_5:    
                if(Channel & HERO_CH_PFR)        
                {
                    Action = 1;    
                    Addr = HDSP_Y_MuteSix_FR_REL;
                }
                break;
                
            //rear left channel    
            case OPERATION_6:
                if(Channel & HERO_CH_PRL)        
                {
                    Action = 1;    
                    Addr = HDSP_Y_MuteSix_RL_REL;
                }
                break;
                
            //rear right channel    
            case OPERATION_7:    
                if(Channel & HERO_CH_PRR)        
                {
                    Action = 1;
                    Addr = HDSP_Y_MuteSix_RR_REL;
                }
                break;
                
            //subwoofer left channel    
            case OPERATION_8:
                if(Channel & HERO_CH_SWL)        
                {
                    Action = 1;
                    Addr = HDSP_Y_MuteSix_SwL_REL;
                }
                break;
                
            //subwoofer right channel    
            case OPERATION_9:
                if(Channel & HERO_CH_SWR)        
                {
                    Action = 1;
                    Addr = HDSP_Y_MuteSix_SwR_REL;
                }
                break;
                
            default:
                sAudio.SoftMuteStep = OPERATION_0;
                break;    
        }

        if(1 == Action)
        {
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,Addr,Dat);
        }

        
        if(SUBLAYER_DONE == SubResult)
        {
            Action = 0;
        }
        
        if(SubResult > SUBLAYER_DONE) //Error Occurs
        {
            Result = SubResult;
            sAudio.SoftMuteStep = OPERATION_0;
            break;
        }
        
        if(0 == Action)
        {
            sAudio.SoftMuteStep++;
        }
        
        if(sAudio.SoftMuteStep > OPERATION_9)
        {
            sAudio.SoftMuteStep = 0;
            Result = SUBLAYER_DONE;
            break;
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_GetMaxTone
 * @brief      Get Max Gain Value of Tone
 * @param      NULL                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_GetMaxTone(void)
{
    uint8_t MaxTone;

    if((sAudioDat.sBasic.sBass.Gain >= sAudioDat.sBasic.sMid.Gain) && (sAudioDat.sBasic.sBass.Gain >= sAudioDat.sBasic.sTreble.Gain))
    {
        MaxTone = sAudioDat.sBasic.sBass.Gain;
    }
    else if((sAudioDat.sBasic.sMid.Gain >= sAudioDat.sBasic.sBass.Gain) && (sAudioDat.sBasic.sMid.Gain >= sAudioDat.sBasic.sTreble.Gain)) 
    {
        MaxTone = sAudioDat.sBasic.sMid.Gain;
    }
    else if((sAudioDat.sBasic.sTreble.Gain >= sAudioDat.sBasic.sBass.Gain) && (sAudioDat.sBasic.sTreble.Gain >= sAudioDat.sBasic.sMid.Gain)) 
    {
        MaxTone = sAudioDat.sBasic.sTreble.Gain;
    }    

    return (MaxTone);
}
/**********************************************************
 * @function    Hero_GetMaxGeq
 * @brief      Get Max Gain Value of Graphic Equalizer
 * @param      NULL                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_GetMaxGeq(void)
{
    uint8_t i,Temp;

    if(GEQ_MODE_CUSTOM == sAudioDat.sBasic.Type)
    {
        Temp = sAudioDat.sGeq.sBuffer[0].Gain;
        for(i = 1; i < GEQ_MAX_NUM; i++)
        {
            if(Temp < sAudioDat.sGeq.sBuffer[i].Gain)
            {
                Temp = sAudioDat.sGeq.sBuffer[i].Gain;
            }    
        }
    }
    else
    {
        Temp = Tab_Geq_Max_Gain[sAudioDat.sBasic.Type];
    }

    return (Temp);
}
/**********************************************************
 * @function    Hero_DrvBassSet
 * @brief      Set Bass 
 * @param      uint8_t Stream
 *            PN_ATTRI_STRUCT sBass
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvBassSet(uint8_t Stream,PN_ATTRI_STRUCT sBass)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_BASS;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Label = 0;
    uint8_t MaxTone;
    
    switch(sAudio.DrvBassStep)
    {
        //Calc Bass Related Filter's Coefficients
        case BASS_CTL_CALC:
            Hero_Calc_Bass(sBass,sHero.BassCoefBuffer);
            if(sBass.Gain >= 0)  //Calc Gain
            { 
                sHero.BassCoefBuffer[10] = Tab_Db2Lin[24 - sBass.Gain] - 0x080;
            }
            else
            {
                sHero.BassCoefBuffer[10] = 0x080 - Tab_Db2Lin[24 + sBass.Gain];
            }
            sAudio.DrvBassStep = BASS_CTL_SET;
            break;

        //Set Bass related  Filter's Coefficients
        case BASS_CTL_SET:
            if(PrimaryStr == Stream)
            {
                Label = HDSP_Y_BMT_a1bHP_REL;    // must be Actual Address!!!!
            }
            else if(SecondaryStr==Stream)
            {
                Label = HDSP_Y_BMT_a1bHS_REL;
            }
            
            SubResult = Hero_ScratchDataWrite(PrivateID,Label,11,sHero.BassCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvBassStep = BASS_CTL_SCALER;
            }
            break;

        //Dynamic Update Pre-Scaler
        case BASS_CTL_SCALER:
            MaxTone = Hero_GetMaxTone();
            if((MaxTone - 12) > 0)
            {
                sAudio.UltraScaler += (MaxTone - 12); 
                sHero.BassCoefBuffer[0] =  Tab_Db2Lin[MaxTone - 12];
            }
            else
            {
                sHero.BassCoefBuffer[0] =  0x7FF;
            }
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_DesScalBMTP_REL,(int32_t)sHero.BassCoefBuffer[0]);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvBassStep = BASS_CTL_CALC;
                Result = SUBLAYER_DONE;
            }
            break;
    }

    //Sync With Error Result----
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.DrvBassStep = BASS_CTL_CALC;
    }    

    return (Result);
}
/**********************************************************
 * @function    Hero_SetBass
 * @brief      Set Bass 
 * @param      PN_FILTER_STRUCT sBass
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetBass(PN_FILTER_STRUCT sBass,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t tStream;
    PN_ATTRI_STRUCT sTmpBass;
    
    if(SYSTEM_FRONT == Type) 
    {
        tStream = PrimaryStr;
    }
    else if(SYSTEM_REAR == Type) 
    {
        tStream = SecondaryStr;
    }
#ifdef D_TONE_EQ
    if(GEQ_MODE_CUSTOM == sAudioDat.sBasic.Type)
    {
        sTmpBass.Gain = (int8_t)(sBass.Gain - (AUDIO_BASS_MAX / 2));
        sTmpBass.CF = 100;
        sTmpBass.Q = 1.0;
    }
    else
    {
    	#ifdef D_TUNER_EQ//snake20160905
    	if((sAudio.SysChannel == SRC_TYPE_TUNER)&&(Mult_Struct.TestTuner != OPEN_TESTTUNER)) 
		{
            sTmpBass.Gain  = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 0].Gain-(AUDIO_BASS_MAX / 2);
            sTmpBass.CF = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 0].CF;
            sTmpBass.Q = 1.0;
    	}
		else
		{
	        sTmpBass.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 0].Gain - (AUDIO_BASS_MAX / 2);
	        sTmpBass.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 0].CF;
	        sTmpBass.Q = 1.0;
		}
		#else
			sTmpBass.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 0].Gain - (AUDIO_BASS_MAX / 2);
			sTmpBass.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 0].CF;
			sTmpBass.Q = 1.0;
		#endif
    }
#else
    sTmpBass.Gain = (int8_t)(sBass.Gain - (AUDIO_BASS_MAX / 2));
    sTmpBass.CF = Tab_Bass_CF[sBass.CF];
    sTmpBass.Q = Tab_Filter_Q[sBass.Q];
#endif        
    Result = Hero_DrvBassSet(tStream, sTmpBass);

    return (Result);
}
/**********************************************************
 * @function    Hero_DrvMidSet
 * @brief      Hero Set Tone: Middle
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvMidSet(uint8_t Stream,PN_ATTRI_STRUCT sMid)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_MID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Label = 0;
    uint8_t MaxTone;
    
    switch(sAudio.DrvMidStep)
    {
        case MID_CTL_CALC:
            Hero_Calc_Mid(sMid,sHero.MidCoefBuffer);
            sAudio.DrvMidStep = MID_CTL_SET;
            break;

        case MID_CTL_SET:
            if(PrimaryStr == Stream)
            {
                Label = HDSP_Y_BMT_a1mHP_REL; // must be Actual Address!!!!
            }
            else if(SecondaryStr == Stream)
            {
                Label = HDSP_Y_BMT_a1mHS_REL;
            }
            
            SubResult = Hero_ScratchDataWrite(PrivateID,Label,7,sHero.MidCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvMidStep = MID_CTL_SCALER;
            }
            break;

        case MID_CTL_SCALER:
            MaxTone = Hero_GetMaxTone();    
            if((MaxTone - 12) > 0)
            {
                sAudio.UltraScaler += (MaxTone - 12); 
                sHero.MidCoefBuffer[0] =  Tab_Db2Lin[MaxTone - 12];
            }
            else
            {
                sHero.MidCoefBuffer[0] =  0x7FF;
            }
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_DesScalBMTP_REL,(int32_t)sHero.MidCoefBuffer[0]);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvMidStep = MID_CTL_CALC;
                Result = SUBLAYER_DONE;
            }
            break;
    }

    //Sync With Error Result----
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.DrvMidStep = MID_CTL_CALC;
    }    
    
    return (Result);
}
/**********************************************************
 * @function    Hero_SetMid
 * @brief      Set Middle 
 * @param      PN_FILTER_STRUCT sMid
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetMid(PN_FILTER_STRUCT sMid,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t tStream;
    PN_ATTRI_STRUCT sTmpMid;
    
    if(SYSTEM_FRONT == Type) 
    {
        tStream = PrimaryStr;    
    }
    else if(SYSTEM_REAR == Type) 
    {
        tStream = SecondaryStr;
    }
#ifdef D_TONE_EQ
    if(GEQ_MODE_CUSTOM == sAudioDat.sBasic.Type)
    {
        sTmpMid.Gain = (int8_t)(sMid.Gain - (AUDIO_MID_MAX / 2));
        sTmpMid.CF = 1000;
        sTmpMid.Q = 1.0;
    }
    else
    {
		#ifdef D_TUNER_EQ //snake20160905
		if((sAudio.SysChannel == SRC_TYPE_TUNER)&&(Mult_Struct.TestTuner != OPEN_TESTTUNER))// 200160104 snake
		{
            sTmpMid.Gain  = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 1].Gain - (AUDIO_BASS_MAX / 2);
            sTmpMid.CF = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 1].CF;
            sTmpMid.Q = 1.0;
    	}
		else
		{
	        sTmpMid.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 1].Gain - (AUDIO_MID_MAX / 2);
	        sTmpMid.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 1].CF;
	        sTmpMid.Q = 1.0;
		}
		#else
			sTmpMid.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 1].Gain - (AUDIO_MID_MAX / 2);
			sTmpMid.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 1].CF;
			sTmpMid.Q = 1.0;
		#endif
    }
#else
    sTmpMid.Gain = (int8_t)(sMid.Gain - (AUDIO_MID_MAX / 2));
    sTmpMid.CF = Tab_Middle_CF[sMid.CF];
    sTmpMid.Q = Tab_Filter_Q[sMid.Q];
#endif    

    Result = Hero_DrvMidSet(tStream,sTmpMid);

    return (Result);
}
/**********************************************************
 * @function    Hero_DrvMidSet
 * @brief      Hero Set Tone: Middle
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_DrvTrebSet(uint8_t Stream,PN_ATTRI_STRUCT sTreble)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_TREBLE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Label = 0;
    uint8_t MaxTone;
    
    switch(sAudio.DrvTrebleStep)
    {
        case TREBLE_CTL_CALC:
            Hero_Calc_Treble(sTreble,sHero.TrebleCoefBuffer);
            sAudio.DrvTrebleStep = TREBLE_CTL_SET;
            break;

        case TREBLE_CTL_SET:
            if (PrimaryStr == Stream)
            {
                Label = HDSP_Y_BMT_a1tP_REL;    // must be Actual Address!!!!
            }
            else if(SecondaryStr == Stream)
            {
                Label = HDSP_Y_BMT_a1tS_REL;
            }
            
            SubResult = Hero_ScratchDataWrite(PrivateID,Label,6,sHero.TrebleCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvTrebleStep = TREBLE_CTL_SCALER;
            }
            break;

        case TREBLE_CTL_SCALER:
            MaxTone = Hero_GetMaxTone();    
            if((MaxTone - 12) > 0)
            {
                sAudio.UltraScaler += (MaxTone - 12); 
                sHero.TrebleCoefBuffer[0] =  Tab_Db2Lin[MaxTone - 12];
            }
            else
            {
                sHero.TrebleCoefBuffer[0] =  0x7FF;
            }
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_DesScalBMTP_REL,(int32_t)sHero.TrebleCoefBuffer[0]);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvTrebleStep = TREBLE_CTL_CALC;
                Result = SUBLAYER_DONE;
            }
            break;
    }

    //Sync With Error Result----
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.DrvTrebleStep = TREBLE_CTL_CALC;
    }    
    
    return (Result);
}
/**********************************************************
 * @function    Hero_SetTreble
 * @brief      Set Treble 
 * @param      PN_FILTER_STRUCT sTreble
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetTreble(PN_FILTER_STRUCT sTreble,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t tStream;
    PN_ATTRI_STRUCT sTmpTreble;
    
    if(SYSTEM_FRONT == Type) 
    {
        tStream = PrimaryStr;
    }
    else if(SYSTEM_REAR == Type) 
    {
        tStream = SecondaryStr;
    }
    
#ifdef D_TONE_EQ
    if(GEQ_MODE_CUSTOM == sAudioDat.sBasic.Type)
    {
        sTmpTreble.Gain = (int8_t)(sTreble.Gain - (AUDIO_TREBLE_MAX / 2));
        sTmpTreble.CF = 12500;
        sTmpTreble.Q = 1.0;
    }
    else
    {
    	#ifdef D_TUNER_EQ //snake20160905
		if((sAudio.SysChannel == SRC_TYPE_TUNER)&&(Mult_Struct.TestTuner != OPEN_TESTTUNER))// 200160104 snake
		{
            sTmpTreble.Gain  = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 2].Gain - (AUDIO_TREBLE_MAX / 2);
            sTmpTreble.CF = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 2].CF;
            sTmpTreble.Q = 1.0;
    	}
		else
		{
	        sTmpTreble.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 2].Gain - (AUDIO_TREBLE_MAX / 2);
	        sTmpTreble.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 2].CF;
	        sTmpTreble.Q = 1.0;
		}
		#else
			sTmpTreble.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 2].Gain - (AUDIO_TREBLE_MAX / 2);
			sTmpTreble.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 2].CF;
			sTmpTreble.Q = 1.0;
		#endif
    }
#else
    sTmpTreble.Gain = (int8_t)(sTreble.Gain - (AUDIO_TREBLE_MAX / 2));
    sTmpTreble.CF = Tab_Treble_CF[sTreble.CF];
    sTmpTreble.Q = Tab_Filter_Q[sTreble.Q];
#endif    

    Result = Hero_DrvTrebSet(tStream,sTmpTreble);

    return (Result);
}
/**********************************************************
 * @function    Hero_SetBalFad
 * @brief      Hero Set Bal&Fad
 * @param      NULL
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetBalFad(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_BF;
    int32_t Coeffs[2];
    uint8_t Bal,Fad;

    Bal = sAudioDat.sBasic.Balance;
    Fad = sAudioDat.sBasic.Fader;
    
    switch(sAudio.BalFadCtl)
    {
        //Set Balance FL FR
        case BF_CTL_BAL_LR:
            if(sAudio.BalFadMask & BF_MASK_BAL)
            {
                //Calculate 
                if (Bal >= (AUDIO_BALANCE_MAX / 2))
                {
                    Coeffs[0] = Tab_Db2Lin[Tab_BF_Atten[Bal - (AUDIO_BALANCE_MAX / 2)]];
                    Coeffs[1] = 0x07FFUL;/* ~ +1 */
                }
                else
                {
                    Coeffs[0] = 0x07FFUL;/* ~ +1 */
                    Coeffs[1] = Tab_Db2Lin[Tab_BF_Atten[(AUDIO_BALANCE_MAX / 2) - Bal]];
                }
                SubResult = Hero_WriteMemData(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_BalPL_REL,2,Coeffs);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.BalFadMask &= ~(BF_MASK_BAL);
                    sAudio.BalFadCtl =  BF_CTL_BAL_SW;
                }
            }
            else
            {
                sAudio.BalFadCtl = BF_CTL_FAD_FR;
            }
            break;

        //Set Balance Center/Subwoofer
        case BF_CTL_BAL_SW:
            //Calculate 
            if (Bal >= (AUDIO_BALANCE_MAX / 2))
            {
                Coeffs[0] = Tab_Db2Lin[Tab_BF_Atten[Bal - (AUDIO_BALANCE_MAX / 2)]];// 2db Per Step
                Coeffs[1] = 0x07FFUL;/* ~ +1 */
            }
            else
            {
                Coeffs[0] = 0x07FFUL;/* ~ +1 */
                Coeffs[1] = Tab_Db2Lin[Tab_BF_Atten[(AUDIO_BALANCE_MAX / 2) - Bal]];// 2db Per Step
            }

            Coeffs[0] = ((Coeffs[0] + Coeffs[1]) / 2);
            Coeffs[1] = Coeffs[0];
            SubResult = Hero_WriteMemData(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_BalSwL_REL,2,Coeffs);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.BalFadCtl = BF_CTL_FAD_FR;
            }
            break;

        //Set Fader F R
        case BF_CTL_FAD_FR:
            if(sAudio.BalFadMask & BF_MASK_FAD)
            {
                //Calculate 
                if (Fad >= (AUDIO_FADER_MAX / 2))
                {
                    Coeffs[0] = Tab_Db2Lin[Tab_BF_Atten[Fad - (AUDIO_FADER_MAX / 2)]];// 2db Per Step
                    Coeffs[1] = 0x07FFUL;/* ~ +1 */
                }
                else
                {
                    Coeffs[0] = 0x07FFUL;/* ~ +1 */
                    Coeffs[1] = Tab_Db2Lin[Tab_BF_Atten[(AUDIO_FADER_MAX / 2) - Fad]];// 2db Per Step
                }
                SubResult = Hero_WriteMemData(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_FadF_REL,2,Coeffs);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.BalFadCtl =  BF_CTL_FAD_SW;
                }
            }
            else
            {
                sAudio.BalFadCtl =  OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        //Set Fader Center/Subwoofer
        case BF_CTL_FAD_SW:
            //Calculate 
            if (Fad >= (AUDIO_FADER_MAX / 2))
            {
                Coeffs[0] = Tab_Db2Lin[Tab_BF_Atten[Fad - (AUDIO_FADER_MAX / 2)]];
                Coeffs[1] = 0x07FFUL;/* ~ +1 */
            }
            else
            {
                Coeffs[0] = 0x07FFUL;/* ~ +1 */
                Coeffs[1] = Tab_Db2Lin[Tab_BF_Atten[(AUDIO_FADER_MAX / 2) - Fad]];
            }
            Coeffs[0] = ((Coeffs[0] + Coeffs[1]) / 2);
            Coeffs[1] = Coeffs[0];
            SubResult = Hero_WriteMemData(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_FadSwL_REL,2,Coeffs);

            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.BalFadMask &= ~(BF_MASK_FAD);
                sAudio.BalFadCtl =  OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;
    }

    //Sync With Error Result----
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.BalFadCtl =  OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Hero_SetGeq
 * @brief      Set a specific GEQ Mode
 * @param      uint8_t Typel            
 * @retval     Result
 **********************************************************/
#define GEQ_BAND ((sAudio.GeqStep - GEQ_BAND1_CALC) / 2)
uint8_t Hero_SetGeq(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_GEQ;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    PN_ATTRI_STRUCT sTmpGeq;
    uint8_t ExecutedFlag = 1;
    uint8_t MaxGeq;

    while(1 == ExecutedFlag) //speed up efficiency, avoid idle step  
    {
        switch(sAudio.GeqStep)
        {
            //Init Graphic Equalizer
            case GEQ_INIT:
                if(GEQ_MASK_INIT & sAudio.GeqMask)
                {
                    sAudio.GeqStep = GEQ_ENABLE_ADD4;
                }
                else
                {
                    sAudio.GeqStep = GEQ_BAND1_CALC;
                }
                break;

            case GEQ_ENABLE_ADD4:
                ExecutedFlag = 0;
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_EasyP_Index_REL,HDSP_EASYP_GraphEQ_9Band_Enable);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_INIT);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND1_CALC;
                }
                break;

            //Calculate Band's Related coefficients    
            case GEQ_BAND1_CALC:
            case GEQ_BAND2_CALC:
            case GEQ_BAND3_CALC:
            case GEQ_BAND4_CALC: //actually Band 6
            case GEQ_BAND5_CALC: //actually Band 7    
            case GEQ_BAND6_CALC: //actually Band 4
            case GEQ_BAND7_CALC: //actually Band 5
            case GEQ_BAND8_CALC:
            case GEQ_BAND9_CALC:
                if((0x0001 << (GEQ_BAND + 1)) & sAudio.GeqMask)
                {
                    ExecutedFlag = 0;

                    sTmpGeq.Gain = (sAudioDat.sGeq.sBuffer[GEQ_BAND + EQ_BAND_1].Gain - AUDIO_GEQ_MAX/2);
                    sTmpGeq.Q = Tab_Filter_Q[sAudioDat.sGeq.sBuffer[GEQ_BAND + EQ_BAND_1].Q];
                    sTmpGeq.CF = Tab_Geq_Band_CF[(GEQ_BAND) * 3 + sAudioDat.sGeq.sBuffer[GEQ_BAND].CF];

                    if(sAudio.GeqStep >= GEQ_BAND6_CALC)
                    {
                        Hero_Calc_Eq(0,sTmpGeq,sHero.GeqCoefBuffer);
                    }
                    else
                    {
                        Hero_Calc_Eq(1,sTmpGeq,sHero.GeqCoefBuffer);
                    }
                    sAudio.GeqStep++;
                }
                else
                {
                    sAudio.GeqStep += 2;
                }
                break;

            //Set Band1 Related Value
            case GEQ_BAND1_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_GEq_b10L_REL,7,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND1);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND2_CALC;
                }
                break;

            //Set Band2 Related Value
            case GEQ_BAND2_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_GEq_b20L_REL,7,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND2);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND3_CALC;
                }
                break;

            //Set Band3 Related Value
            case GEQ_BAND3_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_GEq_b30L_REL,7,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND3);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND4_CALC;
                }
                break;

            //Set Band6 Related Value
            case GEQ_BAND4_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_EQ4_b10L_REL,7,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND4);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND5_CALC;
                }
                break;    

            //Set Band7 Related Value
            case GEQ_BAND5_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_EQ4_b20L_REL,7,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND5);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND6_CALC;
                }
                break;            

            //Set Band6 Related Value
            case GEQ_BAND6_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_GEq_b40_REL,4,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND6);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND7_CALC;
                }
                break;    

            //Set Band7 Related Value
            case GEQ_BAND7_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_GEq_b50_REL,4,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND7);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND8_CALC;
                }
                break;        

            //Set Band8 Related Value
            case GEQ_BAND8_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_EQ4_b30_REL,4,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND8);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND9_CALC;
                }
                break;    

            //Set Band9 Related Value
            case GEQ_BAND9_SET:
                ExecutedFlag = 0;
                SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_EQ4_b40_REL,4,sHero.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND9);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND_END;
                }
                break;        


            //All Done!
            //Dynamic Update Pre-Scaler
            case GEQ_BAND_END:
                ExecutedFlag = 0;
                MaxGeq = Hero_GetMaxGeq();
                if((MaxGeq - 12) > 0)
                {
                    sAudio.UltraScaler += (MaxGeq - 12); 
                    sHero.GeqCoefBuffer[0] =  Tab_Db2Lin[MaxGeq - 12];
                }
                else
                {
                    sHero.GeqCoefBuffer[0] =  0x7FF;
                }
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_DesScalGEq_REL,(int32_t)sHero.GeqCoefBuffer[0]);
                if(SUBLAYER_DONE == SubResult)
                {
                    Result = SUBLAYER_DONE;
                    sAudio.GeqStep = OPERATION_0;
                }
                break;
                
            default:
                ExecutedFlag = 0;
                sAudio.GeqStep = OPERATION_0;
                break;
        }

        //Error Occurs!
        if(SubResult > SUBLAYER_DONE)
        {
            ExecutedFlag = 0;
            Result =     SubResult;
            sAudio.GeqStep = OPERATION_0;
        }
    }
    return (Result);
}
/**********************************************************
 * @function    Hero_DelayLine
 * @brief      Set Delay Line
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Hero_DelayLine(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_DELAY_LINE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    int32_t Data;

    switch(sAudio.DelayCtl)
    {
        case HERO_DELAY_STEP_WAIT:
            sAudio.DelayCtl = HERO_DELAY_STEP_MUTE;
            if(0x00 == (sAudio.DelayLineMask & DELAY_MASK_AR))
            {
                sAudio.DelayWait = AudioDelay(T200MS);
            }
            break;
    
        //Mute Before Adjust ....
        case HERO_DELAY_STEP_MUTE:
            if(0 != sAudio.DelayWait)
                break;
        #if 1
            if(0x00 == (sAudio.DelayLineMask & DELAY_MASK_AR))
            {
                Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_MUTE,SYSTEM_FRONT);
            }
            sAudio.DelayCtl = HERO_DELAY_STEP_FL;
        #else
            SubResult = Hero_SoftMute(HERO_CH_P,MUTE_ON);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = HERO_DELAY_STEP_FL;
            }
        #endif
            break;
    
        //Set Delay of Front Left Speaker
        case HERO_DELAY_STEP_FL:
            if((sAudio.sAchAttri[sAudio.SysChannel].MuteState & MASK_F_SMUTE)
                || (sAudio.DelayLineMask & DELAY_MASK_AR))
            {
                if(sAudio.DelayLineMask & DELAY_MASK_FL)
                {
                    //Calculate Delay Time and Send to register
                    Data = (RoundChange(sAudioDat.sAdv.DelayCustom[DELAY_LINE_FL] * (ASRate / 10000),1) + 1);
                    SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_Delay_Length1_In_REL,Data);
                }
                else
                {
                    SubResult = SUBLAYER_DONE;
                }
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.DelayCtl = HERO_DELAY_STEP_FR;
                }
            }
            break;

        //Set Delay of Front Right Speaker
        case HERO_DELAY_STEP_FR:
            if(sAudio.DelayLineMask & DELAY_MASK_FR)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange(sAudioDat.sAdv.DelayCustom[DELAY_LINE_FR] * (ASRate / 10000),1) + 1);
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_Delay_Length2_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = HERO_DELAY_STEP_RL;
            }
            break;

        //Set Delay of Rear Left Speaker
        case HERO_DELAY_STEP_RL:
            if(sAudio.DelayLineMask & DELAY_MASK_RL)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange(sAudioDat.sAdv.DelayCustom[DELAY_LINE_RL] * (ASRate / 10000),1) + 1);
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_Delay_Length3_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = HERO_DELAY_STEP_RR;
            }
            break;

        //Set Delay of Rear Right Speaker
        case HERO_DELAY_STEP_RR:
            if(sAudio.DelayLineMask & DELAY_MASK_RR)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange(sAudioDat.sAdv.DelayCustom[DELAY_LINE_RR] * (ASRate / 10000),1) + 1);
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_Delay_Length4_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = HERO_DELAY_STEP_SWL;
            }
            break;

        //Set Delay of SW Left Speaker
        case HERO_DELAY_STEP_SWL:
            if(sAudio.DelayLineMask & DELAY_MASK_SWL)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange(sAudioDat.sAdv.DelayCustom[DELAY_LINE_SWL] * (ASRate / 10000),1) + 1);
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_Delay_Length5_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = HERO_DELAY_STEP_SWR;
            }
            break;

        //Set Delay of SW Right Speaker
        case HERO_DELAY_STEP_SWR:
            if(sAudio.DelayLineMask & DELAY_MASK_SWR)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange(sAudioDat.sAdv.DelayCustom[DELAY_LINE_SWR] * (ASRate / 10000),1) + 1);
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_Delay_Length6_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = HERO_DELAY_STEP_ACTIVE;
            }
            break;

        //Activate Settings!
        case HERO_DELAY_STEP_ACTIVE:
            if(sAudio.DelayLineMask)
            {
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_Delay_InitFlag_REL,0x7FFFFF);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = HERO_DELAY_STEP_END;
                if(0x00 == (sAudio.DelayLineMask & DELAY_MASK_AR))
                {
                    Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_UNMUTE,SYSTEM_FRONT);
                }      
            }
            break;

        //All Done, Ends!
        case HERO_DELAY_STEP_END:
        #if 0
            SubResult = Hero_SoftMute(HERO_CH_P,MUTE_OFF);
            if(SUBLAYER_DONE == SubResult)
        #else
            if((0x00 == (sAudio.sAchAttri[sAudio.SysChannel].MuteState & MASK_F_SMUTE)) 
                || (sAudio.DelayLineMask & DELAY_MASK_AR))
        #endif    
            {
                Result = SUBLAYER_DONE;
                sAudio.DelayLineMask = 0;
                sAudio.DelayCtl = HERO_DELAY_STEP_WAIT;
            }
            break;

        default:
            sAudio.DelayCtl = HERO_DELAY_STEP_WAIT;
            break;
    }

    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.DelayCtl = HERO_DELAY_STEP_WAIT;
    }
    
    return(Result);
}
/**********************************************************
 * @function    Hero_SetPhaseShifter
 * @brief      Set Signal Phase Shifter of a specific channel
 * @param      uint8_t Typel            
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetPhaseShifter(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_PHASE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    int32_t Setting[6];
    uint8_t i;
    switch(sAudio.PhaseCtl)
    {
        case OPERATION_0: //Wait
            sAudio.PhaseWait = AudioDelay(T100MS);
            sAudio.PhaseCtl = OPERATION_1;
            break;

        case OPERATION_1: //Mute
            if(0 != sAudio.PhaseWait)
                break;
            if(0x01 == sAudio.PhaseMask)
            {
                Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_MUTE,SYSTEM_FRONT);
                sAudio.PhaseWait = AudioDelay(T150MS);
            }
            sAudio.PhaseCtl = OPERATION_2;
            break;

        case OPERATION_2:   //Set Phase
            if(0 != sAudio.PhaseWait)
                break;
            if((sAudio.sAchAttri[sAudio.SysChannel].MuteState & MASK_F_SMUTE)
                || (0x00 == sAudio.PhaseMask))
            {
                for(i = 0; i < 6; i++)
                {
                    //if(sAudioDat.sInfo.PhaseShifter & (0x01 << i))    //FL
                    if(PHASE_SHIFT_ON == sAudioDat.sAdv.PhaseShifter[i])
                    {
                        Setting[i] = 0x800;    //inversion required
                    }
                    else
                    {
                        Setting[i] = 0x7FF;
                    }
                }
                
                SubResult = Hero_WriteMemData(PrivateID,I2CDRV_Y_MEM,HDSP_Y_Vol_SignFL_REL,6,Setting);                if(SUBLAYER_DONE == SubResult)
                if(SUBLAYER_DONE == SubResult)
                {
                     sAudio.PhaseCtl = OPERATION_3;   
                }
            }
            break;

        case OPERATION_3:   //De-Mute
            if(0x01 == sAudio.PhaseMask)
            {
                Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_UNMUTE,SYSTEM_FRONT);
               sAudio.PhaseWait = AudioDelay(T150MS);
            }
            sAudio.PhaseCtl = OPERATION_4; 
            break;

        case OPERATION_4: //End
            if(0 != sAudio.XoverDelay)
                break;
            if((0x00 == (sAudio.sAchAttri[sAudio.SysChannel].MuteState & MASK_F_SMUTE)) 
                || (0x00 == sAudio.PhaseMask))
            {
                sAudio.PhaseCtl = OPERATION_0;
                Result = SUBLAYER_DONE; 
            }
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_SetUltraBass
 * @brief      Set UltraBass
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetUltraBass(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_ULTRA_BASS;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    int8_t Tmp;
    int32_t Data;    
    float Scaler;
    
    switch(sAudio.UltraBassCtl)
    {
        //UltraBass Enable or Disable
        case UBASS_CTL_ENABLE:
            if(UBASS_MASK_ENABLE & sAudio.UltraBassMask)
            {
                if(UBASS_ENABLE == sAudioDat.sAdv.sUltraBass.Setting)    
                {
                    Data = 0x03;
                    sAudio.UltraBassMask |= (UBASS_MASK_LEVEL | UBASS_MASK_SCALER);
                }
                else
                {
                    Data = 0x00;
                }
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_AUB2_Mode_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.UltraBassMask &= (~UBASS_MASK_ENABLE);
                sAudio.UltraBassCtl = UBASS_CTL_LEVEL;
            }
            break;

        //Set UltraBass Enhancement Gain
        case UBASS_CTL_LEVEL:
            if(UBASS_MASK_LEVEL & sAudio.UltraBassMask)
            {
                Scaler = powf(10.0,(sAudioDat.sAdv.sUltraBass.BoostLevel / 20.0));
                Scaler /= 16;
                Data = RoundChange(Scaler * 8388608,1);
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_AUB2_AGCMaxGain_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.UltraBassMask &= (~UBASS_MASK_LEVEL);
                sAudio.UltraBassCtl = UBASS_CTL_SCALER;
            }
            break;

        //Set UltraBass Compensate Scaler
        case UBASS_CTL_SCALER:
            if(UBASS_MASK_SCALER & sAudio.UltraBassMask)
            {
                Tmp = -3 - sAudioDat.sInfo.UbassTargetLev;
            }
            else
            {
                Tmp = -15;
            }
            Scaler = powf(10.0,(Tmp / 20.0));
            Data = RoundChange(Scaler * 8388608,1);
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_AUB2_TargetLevel_REL,Data);    

            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.UltraBassMask &= (~UBASS_MASK_SCALER);
                sAudio.UltraBassCtl = UBASS_CTL_ENABLE;
                Result = SUBLAYER_DONE;
            }
            break;    
    }

    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result =     SubResult;
        sAudio.UltraBassCtl = UBASS_CTL_ENABLE;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Hero_SetSubwoofer
 * @brief      Set Subwoofer
 * @param      NULL        
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetSubwoofer(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_SW;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    LHP_ATTRI_STRUCT sFilter;

    switch(sAudio.SwCtl)
    {
        //Create Subwoofer: Stereo Subwoofer
        case SW_CTL_CREATE:
            if(SW_MASK_CREATE & sAudio.SwMask)
            {
                if(1)   //Stereo Sw
                {
                    SubResult = Hero_WriteMemTab(PrivateID,Tab_Create_StereoSw);
                }
                else    //Center+Sw
                {
                    SubResult = Hero_WriteMemTab(PrivateID,Tab_Create_MonoSw);
                }
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.SwCtl = SW_CTL_INIT;
                sAudio.SwMask &= (~SW_MASK_CREATE);
            }
            break;

        case SW_CTL_INIT:
            if(SUBWOOFER_OFF == sAudioDat.sBasic.sSubWooferSwitch)
            {
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_EasyP_Index_REL,HDSP_EASYP_GPF2_Disable);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.SwCtl = SW_CTL_END;
                }
            }
            else
            {
                SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_EasyP_Index_REL,HDSP_EASYP_GPF2_headroom);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.SwCtl = SW_CTL_CALC;
                }
            }
            break;

        //Calc Sw...
        case SW_CTL_CALC:
            sFilter.Gain = (int8_t)(sAudioDat.sBasicBK.sSubWoofer.Level - 6);
            sFilter.CoF = 200;    //Temp, max value of x-over
            Hero_Calc_1stLP(sFilter,sHero.SwCoefBuffer); 
            sAudio.SwCtl = SW_CTL_SET;
            break;

        case SW_CTL_SET:
            SubResult = Hero_ScratchDataWrite(PrivateID,HDSP_Y_IIR2GPF2_b0L_REL,10,sHero.SwCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.SwCtl = SW_CTL_END;
            }
            break;

        case SW_CTL_END:
            sAudio.SwCtl = SW_CTL_INIT;
            Result = SUBLAYER_DONE;
            break;
    }
    
    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result =     SubResult;
        sAudio.SwCtl = SW_CTL_INIT;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_CCInit
 * @brief      Initialize Click Clack
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Hero_CCInit(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_INIT_CLICKCLACK;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sAudio.ClickClackCtl)
    {
        case OPERATION_0:
            SubResult = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_ClickClack_Disable); 
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ClickClackCtl = OPERATION_1;
            }
            break;

        //Set Control Method: FLAG Driven
        case OPERATION_1:
            SubResult = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_WavTab_UseIOFlag,(int32_t)(CC_CTL_FLAG));
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ClickClackCtl = OPERATION_2;
            }
            break;

        case OPERATION_2:
            SubResult = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_ClickClack_Enable); 
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ClickClackCtl = OPERATION_3;
            }
            break;

        //Set Click_Clack Position
        case OPERATION_3:
            SubResult = Hero_DrvSuperPositionGain(PrivateID,P_MIX_EXT_FRONT,(-20));
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ClickClackCtl = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;
    }

    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.ClickClackCtl = 0;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_CCSet
 * @brief      Set Click Clack
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Hero_CCSet(uint8_t Mode)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_INIT_CLICKCLACK;
    uint8_t Result = SUBLAYER_DOING;
    int32_t Temp;

    if(0 == Mode)
    {
        Temp = CLICK_DAT;
    }
    else
    {
        Temp = CLACK_DAT;
    }

    Result = Hero_WriteMemWord(PrivateID,I2CDRV_X_MEM,HDSP_X_WavTab_Control,Temp);

    return (Result);
}
/**********************************************************
 * @function    Hero_CCEnable
 * @brief      Enable Click Clack
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Hero_CCEnable(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_INIT_CLICKCLACK;
    uint8_t Result = SUBLAYER_DOING;

    Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_ClickClack_Enable); 

    return (Result);
}
/**********************************************************
 * @function    Hero_CCDisable
 * @brief      Disable Click Clack
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Hero_CCDisable(void)
{
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_INIT_CLICKCLACK;
    uint8_t Result = SUBLAYER_DOING;

    Result = Hero_EasyProgrammWrite(PrivateID,HDSP_EASYP_ClickClack_Disable); 

    return (Result);
}
/**********************************************************
 * @function    Hero_Calc_Bass
 * @brief      Calc Bass 2nd Order Peak coefficients
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Hero_Calc_Bass(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float t,a2b,a1b,b0b,b2b;
    float Temp;
    uint32_t Coef,a2bHex,a1bHex,b0bHex,b2bHex;

    Coef = 8388608;
    //Calc t Value
    t = (2 * PI * sFilter.CF) / ASRate;
    
    Temp = (t / (2 * sFilter.Q));

    //Calc values
    a2b = ((-0.5) * (1 - Temp)) / (1 + Temp);
    a1b = (0.5 - a2b) * cosf(t);
    b0b = (0.5 + a2b) / 2;
    b2b = -b0b;

    //Convert Cofficient ....to Hex
    a1bHex = RoundChange(a1b * Coef,1);    
    *Result = (a1bHex >> 12) & 0xFFF;
    *(Result + 1) = (a1bHex & 0xFFF) >> 1;        //Double Precision Convert
    

    a2bHex = RoundChange(a2b * Coef,1);
    *(Result + 3) = (a2bHex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 2) = (a2bHex >> 12) & 0xFFF;
    
    b0bHex = RoundChange(b0b * Coef,1);
    *(Result + 5) = (b0bHex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 4) = (b0bHex >> 12) & 0xFFF;
    
    *(Result + 6) = 0x0000; //b1b        //Double Precision Convert
    *(Result + 7) = 0x0000;
    
    b2bHex = RoundChange(b2b * Coef,1);
    *(Result + 9) = (b2bHex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 8) = (b2bHex >> 12) & 0xFFF;
}
/**********************************************************
 * @function    Hero_Calc_Mid
 * @brief      Calc 2nd Order Peak/Notch coefficients
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Hero_Calc_Mid(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float t,G,D,a2,a1,b0;
    float Temp;
    int8_t Gdb;
    uint8_t PrecisionFlag;
    uint32_t Coef,b0Hex,a1Hex,a2Hex,GainHex;

    Coef = 8388608;
    //Transfer Gain to actual value
    Gdb = sFilter.Gain;

    //Calc t Value
    t = (2 * PI * sFilter.CF) / ASRate;
    //Calc D value
    if(Gdb >= 0)
    {
        D = 1.0;
    }
    else
    {
        D = 1 / powf(10.0,(Gdb / 20.0));
    }
    //Calc Temp Value
    Temp = (D * t) / (2 * sFilter.Q);

    //Calc coefficients
    a2 = ((-0.5) * (1 - Temp)) / (1 + Temp);
    a1 = ((0.5 - a2) * (cosf(t)));
    b0 = ((0.5 + a2) / 2);

    //a1 convert to HEX
    a1Hex = RoundChange(a1 * Coef,1);
    *(Result + 1) = (a1Hex & 0xFFF) >> 1;    //Double Precision Convert
    *(Result + 0) = (a1Hex >> 12) & 0xFFF;
    
    //a2 convert to HEX
    a2Hex = RoundChange(a2 * Coef,1);    
    *(Result + 3) = (a2Hex & 0xFFF) >> 1;    //Double Precision Convert
    *(Result + 2) = (a2Hex >> 12) & 0xFFF;

    //b0 convert to HEX
    b0Hex = RoundChange(b0 * Coef,1);    
    *(Result + 5)= (b0Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 4) = (b0Hex >> 12) & 0xFFF;

    //Gain convert to HEX
    GainHex = (Tab_Db2Lin[24 - Gdb] - 0x80);  //Directly Get from linear table
    *(Result + 6) = GainHex & 0xFFF;
}
/**********************************************************
 * @function    Hero_Calc_Treble
 * @brief      Calc 2nd Order Peak/Notch coefficients
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Hero_Calc_Treble(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float t,G,D,a2,a1,b0,b2;
    float Temp;
    int8_t Gdb;
    uint8_t PrecisionFlag;
    uint32_t Coef,b0Hex,b2Hex,a1Hex,a2Hex,GainHex;

    Coef = 2048;

    //Transfer Gain to actual value
    Gdb = sFilter.Gain;

    //Calc t Value
    t = (2 * PI * sFilter.CF) / ASRate;
    //Calc D value
    if(Gdb >= 0)
    {
        D = 1.0;
    }
    else
    {
        D = 1 / powf(10.0,(Gdb / 20.0));
    }
    //Calc Temp Value
    Temp = (D * t) / (2 * sFilter.Q);

    //Calc coefficients
    a2 = ((-0.5) * (1 - Temp)) / (1 + Temp);
    a1 = ((0.5 - a2) * (cosf(t)));
    b0 = ((0.5 + a2) / 2);
    b2 = -b0;

    //a1 convert to HEX
    a1Hex = RoundChange(a1 * Coef,0);
    *(Result + 0) = a1Hex & 0xFFF;    //Sigle Precision convert

    //a2 convert to HEX
    a2Hex = RoundChange(a2 * Coef,0);    
    *(Result + 1) = a2Hex & 0xFFF;    //Sigle Precision convert

    //b0 convert to HEX
    b0Hex = RoundChange(b0 * Coef,0);    
    *(Result + 2) = b0Hex & 0xFFF;         //Sigle Precision convert

    *(Result + 3) = 0x000;
    
    //b2 convert to HEX
    b2Hex = RoundChange(b2 * Coef,0);    
    *(Result + 4) = b2Hex & 0xFFF;         //Sigle Precision convert

    
    //Gain convert to HEX
    GainHex = (Tab_Db2Lin[24 - Gdb] - 0x80);  //Directly Get from linear table
    *(Result + 5) = GainHex & 0xFFF;
}
/**********************************************************
 * @function    Hero_Calc_Eq
 * @brief      Calc 2nd Order Peak/Notch coefficients
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Hero_Calc_Eq(uint8_t Flag,PN_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float t,G,D,a2,a1,b0;
    float Temp;
    int8_t Gdb;
    uint8_t PrecisionFlag;
    uint32_t Coef,b0Hex,a1Hex,a2Hex,GainHex;

    //check band whether double precision
    if(1 == Flag)
    {
        Coef = 8388608;
        PrecisionFlag = 1;
    }
    else    //Sigle precision
    {    
        Coef = 2048;
        PrecisionFlag = 0;
    }

    //Transfer Gain to actual value
    Gdb = sFilter.Gain;

    //Calc t Value
    t = (2 * PI * sFilter.CF) / ASRate;
    //Calc D value
    if(Gdb >= 0)
    {
        D = 1.0;
    }
    else
    {
        D = 1 / powf(10.0,(Gdb / 20.0));
    }
    //Calc Temp Value
    Temp = (D * t) / (2 * sFilter.Q);

    //Calc coefficients
    a2 = ((-0.5) * (1 - Temp)) / (1 + Temp);
    a1 = ((0.5 - a2) * (cosf(t)));
    b0 = ((0.5 + a2) / 2);

    //b0 convert to HEX
    b0Hex = RoundChange(b0 * Coef,Flag);    
    if(1 == PrecisionFlag)
    {
        *Result = (b0Hex & 0xFFF) >> 1;        //Double Precision Convert
        *(Result + 1) = (b0Hex >> 12) & 0xFFF;
    }
    else
    {
        *Result = b0Hex & 0xFFF;         //Sigle Precision convert
    }

    //a2 convert to HEX
    a2Hex = RoundChange(a2 * Coef,Flag);    
    if(1 == PrecisionFlag)
    {
        *(Result + 2) = (a2Hex & 0xFFF) >> 1;    //Double Precision Convert
        *(Result + 3) = (a2Hex >> 12) & 0xFFF;
    }
    else
    {
        *(Result + 1) = a2Hex & 0xFFF;    //Sigle Precision convert
    }

    //a1 convert to HEX
    a1Hex = RoundChange(a1 * Coef,Flag);
    if(1 == PrecisionFlag)
    {
        *(Result + 4) = (a1Hex & 0xFFF) >> 1;    //Double Precision Convert
        *(Result + 5) = (a1Hex >> 12) & 0xFFF;
    }
    else
    {
        *(Result + 2) = a1Hex & 0xFFF;    //Sigle Precision convert
    }        
    //Gain convert to HEX
    //GainHex = RoundChange(G * 2048,0);    
    GainHex = (Tab_Db2Lin[12 - Gdb] - 0x200);  //Directly Get from linear table
    if(1 == PrecisionFlag)
    {
        *(Result + 6) = GainHex & 0xFFF;
    }
    else
    {
        *(Result + 3) = GainHex & 0xFFF;
    }
}
/**********************************************************
 * @function    Hero_Calc_LoudBoost
 * @brief      Calc 4th order Low/High Pass Filter  Cofficient
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint16_t Hero_Calc_LoudBoost(uint8_t Type, uint8_t Level)
{
    float TempBst;
    float BstCoef;
    uint16_t BstHex;    

    TempBst = (powf(10.0,(Level / 20.0)) - 1);

    if(0 == Type) //Bass
    {
        BstCoef = (1 - sqrtf(TempBst / 4.6234));
    }
    else //Treble
    {
        BstCoef = (1 - sqrtf(TempBst / 2.1623));    
    }

    BstHex = RoundChange(BstCoef * 2048,0);    
    
    return (BstHex & 0x7FF);
}
/**********************************************************
 * @function    Hero_Calc_2ndLHP
 * @brief      Calc 2nd order Low/High Pass Filter  Cofficient
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Hero_Calc_2ndLHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float t0,t1,G,a1,a2,b0,b1,b2;
    float TempSL2,Tempt0t0;
    uint32_t Coef,b0Hex,b1Hex,b2Hex,a1Hex,a2Hex;

    //All Cost 200US!!

    Coef = 8388608;
    TempSL2 = sqrtf(2.0);
    //Calc G Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0,t1 Value
    t0 = tanf((PI * sFilter.CoF) / ASRate);
    Tempt0t0 = (t0 * t0);
    t1 = 1 + (TempSL2 * t0) + Tempt0t0;

    //Calc a1,a2,b0,b1,b2 Value
    a1 = (1 - Tempt0t0) / t1;
    a2 = ((TempSL2 * t0) / t1) - 0.5;
    b0 = (G * Tempt0t0) / (2 * t1);
    b1 = 2 * b0;
    b2 = b0;

    //Convert to HEX
    b0Hex = RoundChange(b0 * Coef,1);    
    *Result = (b0Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 1) = (b0Hex >> 12) & 0xFFF;
    
    b1Hex = RoundChange(b1 * Coef,1);
    *(Result + 2) = (b1Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 3) = (b1Hex >> 12) & 0xFFF;
    
    b2Hex = RoundChange(b2 * Coef,1);
    *(Result + 4) = (b2Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 5) = (b2Hex >> 12) & 0xFFF;
    
    a1Hex = RoundChange(a1 * Coef,1);
    *(Result + 6) = (a1Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 7) = (a1Hex >> 12) & 0xFFF;
    
    a2Hex = RoundChange(a2 * Coef,1);
    *(Result + 8) = (a2Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 9) = (a2Hex >> 12) & 0xFFF;
}
/**********************************************************
 * @function    Hero_Calc_2ndLHP
 * @brief      Calc 2nd order Low/High Pass Filter  Cofficient
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Hero_Calc_NavPhoneVol(int8_t Vol, uint16_t* Result)
{
    float TempVal;
    uint32_t TempHex;
    
    //Calc Value
    TempVal = (powf(10.0,(Vol / 20.0))) / 4;
    TempHex = RoundChange(TempVal * 2048,0);    
    *Result = TempHex;
}
/**********************************************************
 * @function    Hero_Calc_1stLP
 * @brief      Calculate 2nd order IIR as 1st order LP
 * @param     LHP_ATTRI_STRUCT sFilter  
 *                  uint16_t* Result
 * @retval     NULL
 **********************************************************/
void Hero_Calc_1stLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float g,a1,b0;
    uint32_t Coef,b0Hex,a1Hex;

    Coef = 8388608;

    //Calc Value
    g = powf(10.0,(sFilter.Gain / 20.0));
    a1 = (-0.5) * (tanf(PI * (sFilter.CoF / ASRate - 0.25)));
    b0 = g * (0.25 - 0.5 * a1);

    //Convert to HEX
    b0Hex = RoundChange(b0 * Coef,1);       //Double Precision Convert
    *Result = (b0Hex & 0xFFF) >> 1;                 //b0L
    *(Result + 1) = (b0Hex >> 12) & 0xFFF;      //b0H
    
    *(Result + 2) = *Result;        
    *(Result + 3) = *(Result + 1);
    
    *(Result + 4) = 0x0000;
    *(Result + 5) = 0x0000;
    
    a1Hex = RoundChange(a1 * Coef,1);
    *(Result + 6) = (a1Hex & 0xFFF) >> 1;     
    *(Result + 7) = (a1Hex >> 12) & 0xFFF;
    
    *(Result + 8) = 0x0000;    
    *(Result + 9) = 0x0000;
}
/**********************************************************
 * @function    Hero_Calc_1stHP
 * @brief      Calculate 2nd order IIR as 1st order HP
 * @param     LHP_ATTRI_STRUCT sFilter  
 *                  uint16_t* Result
 * @retval     NULL
 **********************************************************/
void Hero_Calc_1stHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float g,a1,b0,b1;
    uint32_t Coef,b0Hex,b1Hex,a1Hex;

    Coef = 8388608;

    //Calc Value
    g = powf(10.0,(sFilter.Gain / 20.0));
    a1 = (-0.5) * (tanf(PI * (sFilter.CoF / ASRate - 0.25)));
    b0 = g * (0.25 + 0.5 * a1);
    b1 = -b0;

    //Convert to HEX
    b0Hex = RoundChange(b0 * Coef,1);    
    *Result = (b0Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 1) = (b0Hex >> 12) & 0xFFF;
    
    b1Hex = RoundChange(b1 * Coef,1);
    *(Result + 2) = (b1Hex & 0xFFF) >> 1;       
    *(Result + 3) = (b1Hex >> 12) & 0xFFF;
    
    *(Result + 4) = 0x0000;       
    *(Result + 5) = 0x0000;
    
    a1Hex = RoundChange(a1 * Coef,1);
    *(Result + 6) = (a1Hex & 0xFFF) >> 1;      
    *(Result + 7) = (a1Hex >> 12) & 0xFFF;
    
    *(Result + 8) = 0x0000;       
    *(Result + 9) = 0x0000;
}
/**********************************************************
 * @function    Hero_Calc_2ndPN
 * @brief      Calculate 2nd order IIR as 2nd Peak/notch Filter
 * @param     PN_ATTRI_STRUCT sFilter  
 *                  uint16_t* Result
 * @retval     NULL
 **********************************************************/
void Hero_Calc_2ndPN(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float t0,G,B,a2,a1,b0,b1,b2;
    float TempM;
    uint32_t Coef,a2Hex,a1Hex,b0Hex,b1Hex,b2Hex;

    Coef = 8388608;

    //Calc G Actual Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0 Actual Value
    t0 = (2 * PI * sFilter.CF) / ASRate;

    //Calc b Actual Value
    if(G >= 1.0)
    {
        B = t0 / (2 * sFilter.Q);
    }
    else
    {
        B = t0 / (2 * G * sFilter.Q);
    }

    //Calc Coefficients Value
    a2 = (-0.5) * (1 - B) / (1 + B);
    a1 = (0.5 - a2) * cosf(t0);
    TempM = (G - 1) * (0.25 + 0.5 * a2);
    b0 = TempM + 0.5;
    b1 = -a1;
    b2 = -(TempM) - a2;

    //Convert Cofficient ....to Hex
    b0Hex = RoundChange(b0 * Coef,1);    
    *Result = (b0Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 1) = (b0Hex >> 12) & 0xFFF;
    
    b1Hex = RoundChange(b1 * Coef,1);
    *(Result + 2) = (b1Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 3) = (b1Hex >> 12) & 0xFFF;
    
    b2Hex = RoundChange(b2 * Coef,1);
    *(Result + 4) = (b2Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 5) = (b2Hex >> 12) & 0xFFF;
    
    a1Hex = RoundChange(a1 * Coef,1);
    *(Result + 6) = (a1Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 7) = (a1Hex >> 12) & 0xFFF;
    
    a2Hex = RoundChange(a2 * Coef,1);
    *(Result + 8) = (a2Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 9) = (a2Hex >> 12) & 0xFFF;
}
/**********************************************************
 * @function    Hero_Calc_2ndLP
 * @brief      Calc 2nd order Low Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
 * @retval     Result
 **********************************************************/
void Hero_Calc_2ndLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float t0,t1,G,a1,a2,b0,b1,b2;
    float TempSL2,Tempt0t0;
    uint32_t Coef,b0Hex,b1Hex,b2Hex,a1Hex,a2Hex;

    //All Cost 200US!!

    Coef = 8388608;
    TempSL2 = sqrtf(2.0);
    //Calc G Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0,t1 Value
    t0 = tanf((PI * sFilter.CoF) / ASRate);
    Tempt0t0 = (t0 * t0);
    t1 = 1 + (TempSL2 * t0) + Tempt0t0;

    //Calc a1,a2,b0,b1,b2 Value
    a1 = (1 - Tempt0t0) / t1;
    a2 = ((TempSL2 * t0) - 1 - Tempt0t0) / (2 * t1);
    b0 = (G * Tempt0t0) / (2 * t1);
    b1 = 2 * b0;
    b2 = b0;

    //Convert to HEX
    b0Hex = RoundChange(b0 * Coef,1);    
    *Result = (b0Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 1) = (b0Hex >> 12) & 0xFFF;
    
    b1Hex = RoundChange(b1 * Coef,1);
    *(Result + 2) = (b1Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 3) = (b1Hex >> 12) & 0xFFF;
    
    b2Hex = RoundChange(b2 * Coef,1);
    *(Result + 4) = (b2Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 5) = (b2Hex >> 12) & 0xFFF;
    
    a1Hex = RoundChange(a1 * Coef,1);
    *(Result + 6) = (a1Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 7) = (a1Hex >> 12) & 0xFFF;
    
    a2Hex = RoundChange(a2 * Coef,1);
    *(Result + 8) = (a2Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 9) = (a2Hex >> 12) & 0xFFF;
}
/**********************************************************
 * @function    Hero_Calc_2ndHP
 * @brief      Calc 2nd order High Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
 * @retval     Result
 **********************************************************/
void Hero_Calc_2ndHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
{
    float t0,t1,G,a1,a2,b0,b1,b2;
    float TempSL2,Tempt0t0;
    uint32_t Coef,b0Hex,b1Hex,b2Hex,a1Hex,a2Hex;

    //All Cost 200US!!

    Coef = 8388608;
    TempSL2 = sqrtf(2.0);
    //Calc G Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0,t1 Value
    t0 = tanf((PI * sFilter.CoF) / ASRate);
    Tempt0t0 = (t0 * t0);
    t1 = 1 + (TempSL2 * t0) + Tempt0t0;

    //Calc a1,a2,b0,b1,b2 Value
    a1 = (1 - Tempt0t0) / t1;
    a2 = ((TempSL2 * t0) - 1 - Tempt0t0) / (2 * t1);
    b0 = G / (2 * t1);
    b1 = -2 * b0;
    b2 = b0;

    //Convert to HEX
    b0Hex = RoundChange(b0 * Coef,1);    
    *Result = (b0Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 1) = (b0Hex >> 12) & 0xFFF;
    
    b1Hex = RoundChange(b1 * Coef,1);
    *(Result + 2) = (b1Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 3) = (b1Hex >> 12) & 0xFFF;
    
    b2Hex = RoundChange(b2 * Coef,1);
    *(Result + 4) = (b2Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 5) = (b2Hex >> 12) & 0xFFF;
    
    a1Hex = RoundChange(a1 * Coef,1);
    *(Result + 6) = (a1Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 7) = (a1Hex >> 12) & 0xFFF;
    
    a2Hex = RoundChange(a2 * Coef,1);
    *(Result + 8) = (a2Hex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 9) = (a2Hex >> 12) & 0xFFF;
}
/**********************************************************
 * @function    Hero_Calc_3rdLP
 * @brief      Calc 3rd order Low Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
  *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Hero_Calc_3rdLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
{
    float t0,t1,G,a01,a02,b00,b01,b02,a11,a12,b10,b11,b12;
    float Tempt0t0;
    uint32_t Coef,b00Hex,b01Hex,b02Hex,b10Hex,b11Hex,b12Hex,a01Hex,a02Hex,a11Hex,a12Hex;

    Coef = 8388608;
    //Calc G Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0,t1 Value
    t0 = tanf((PI * sFilter.CoF) / ASRate);
    Tempt0t0 = (t0 * t0);
    t1 = 1 + t0 + Tempt0t0;

    //Calc a1,a2,b0,b1,b2 Value
    a01 = (1 - t0) / (2 + 2 * t0);
    a11 = (1 - Tempt0t0) / t1;
    a12 = (t0 - Tempt0t0 - 1) / (2 * t1);
    b00 = (G * t0) / (2 * t0 + 2);
    b01 = b00;
    b10 = Tempt0t0 / (2 * t1);
    b11 = 2 * b10;
    b12 = b10;

    //Convert to HEX
    if(0 == Mode)
    {
        b00Hex = RoundChange(b00 * Coef,1);    
        *Result = (b00Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b00Hex >> 12) & 0xFFF;
        
        b01Hex = RoundChange(b01 * Coef,1);
        *(Result + 2) = (b01Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b01Hex >> 12) & 0xFFF;
        
        //b02Hex = RoundChange(b02 * Coef,1);
        *(Result + 4) = 0x0000;        
        *(Result + 5) = 0x0000;
        
        a01Hex = RoundChange(a01 * Coef,1);
        *(Result + 6) = (a01Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a01Hex >> 12) & 0xFFF;
        
        //a02Hex = RoundChange(a02 * Coef,1);
        *(Result + 8) = 0x0000;       
        *(Result + 9) = 0x0000;  
    }
    else
    {
        b10Hex = RoundChange(b10 * Coef,1);    
        *Result = (b10Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b10Hex >> 12) & 0xFFF;

        b11Hex = RoundChange(b11 * Coef,1);
        *(Result + 2) = (b11Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b11Hex >> 12) & 0xFFF;

        b12Hex = RoundChange(b12 * Coef,1);
        *(Result + 4) = (b12Hex & 0xFFF) >> 1;         
        *(Result + 5) = (b12Hex >> 12) & 0xFFF;

        a11Hex = RoundChange(a11 * Coef,1);
        *(Result + 6) = (a11Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a11Hex >> 12) & 0xFFF;

        a12Hex = RoundChange(a12 * Coef,1);
        *(Result + 8) = (a12Hex & 0xFFF) >> 1;          
        *(Result + 9) = (a12Hex >> 12) & 0xFFF; 
    }
}
/**********************************************************
 * @function    Hero_Calc_3rdHP
 * @brief      Calc 3rd order High Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
 *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Hero_Calc_3rdHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
{
    float t0,t1,G,a01,a02,b00,b01,b02,a11,a12,b10,b11,b12;
    float Tempt0t0;
    uint32_t Coef,b00Hex,b01Hex,b02Hex,b10Hex,b11Hex,b12Hex,a01Hex,a02Hex,a11Hex,a12Hex;

    Coef = 8388608;
    //Calc G Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0,t1 Value
    t0 = tanf((PI * sFilter.CoF) / ASRate);
    Tempt0t0 = (t0 * t0);
    t1 = 1 + t0 + Tempt0t0;

    //Calc a1,a2,b0,b1,b2 Value
    a01 = (1 - t0) / (2 + 2 * t0);
    a11 = (1 - Tempt0t0) / t1;
    a12 = (t0 - Tempt0t0 - 1) / (2 * t1);
    b00 = G / (2 * t0 + 2);
    b01 = -b00;
    b10 = 1 / (2 * t1);
    b11 = -2 * b10;
    b12 = b10;

    //Convert to HEX
    if(0 == Mode)
    {
        b00Hex = RoundChange(b00 * Coef,1);    
        *Result = (b00Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b00Hex >> 12) & 0xFFF;
        
        b01Hex = RoundChange(b01 * Coef,1);
        *(Result + 2) = (b01Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b01Hex >> 12) & 0xFFF;
        
        //b02Hex = RoundChange(b02 * Coef,1);
        *(Result + 4) = 0x0000;        
        *(Result + 5) = 0x0000;
        
        a01Hex = RoundChange(a01 * Coef,1);
        *(Result + 6) = (a01Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a01Hex >> 12) & 0xFFF;
        
        //a02Hex = RoundChange(a02 * Coef,1);
        *(Result + 8) = 0x0000;       
        *(Result + 9) = 0x0000;  
    }
    else
    {
        b10Hex = RoundChange(b10 * Coef,1);    
        *Result = (b10Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b10Hex >> 12) & 0xFFF;

        b11Hex = RoundChange(b11 * Coef,1);
        *(Result + 2) = (b11Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b11Hex >> 12) & 0xFFF;

        b12Hex = RoundChange(b12 * Coef,1);
        *(Result + 4) = (b12Hex & 0xFFF) >> 1;         
        *(Result + 5) = (b12Hex >> 12) & 0xFFF;

        a11Hex = RoundChange(a11 * Coef,1);
        *(Result + 6) = (a11Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a11Hex >> 12) & 0xFFF;

        a12Hex = RoundChange(a12 * Coef,1);
        *(Result + 8) = (a12Hex & 0xFFF) >> 1;          
        *(Result + 9) = (a12Hex >> 12) & 0xFFF; 
    }
}
/**********************************************************
 * @function    Hero_Calc_4thLP
 * @brief      Calc 4th order Low Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
  *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Hero_Calc_4thLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
{
    float t0,t1,t2,G,a01,a02,b00,b01,b02,a11,a12,b10,b11,b12;
    float Tempt0t0,TmpCos18t0,TmpCos38t0;
    uint32_t Coef,b00Hex,b01Hex,b02Hex,b10Hex,b11Hex,b12Hex,a01Hex,a02Hex,a11Hex,a12Hex;

    Coef = 8388608;
    //Calc G Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0,t1 Value
    t0 = tanf((PI * sFilter.CoF) / ASRate);
    Tempt0t0 = (t0 * t0);
    TmpCos18t0 = (t0 * cosf(PI / 8));
    TmpCos38t0 = (t0 * cosf((3 * PI) / 8));
    t1 = 1 + (2 * TmpCos18t0) + Tempt0t0;
    t2 = 1 + (2 * TmpCos38t0) + Tempt0t0;
    
    //Calc a1,a2,b0,b1,b2 Value
    a01 = (1 - Tempt0t0) / t1;
    a02 = (2 * TmpCos18t0 - 1 - Tempt0t0) / (2 * t1);
    a11 = (1 - Tempt0t0) / t2;
    a12 = (2 * TmpCos38t0 - 1 - Tempt0t0) / (2 * t2);
    b00 = Tempt0t0 / (2 * t1);
    b01 = 2 * b00;
    b02 = b00;
    b10 = (G * Tempt0t0) / (2 * t2);
    b11 = 2 * b10;
    b12 = b10;

    //Convert to HEX
    if(0 == Mode)
    {
        b00Hex = RoundChange(b00 * Coef,1);    
        *Result = (b00Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b00Hex >> 12) & 0xFFF;
        
        b01Hex = RoundChange(b01 * Coef,1);
        *(Result + 2) = (b01Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b01Hex >> 12) & 0xFFF;
        
        b02Hex = RoundChange(b02 * Coef,1);
        *(Result + 4) = (b02Hex & 0xFFF) >> 1;       
        *(Result + 5) = (b02Hex >> 12) & 0xFFF;
        
        a01Hex = RoundChange(a01 * Coef,1);
        *(Result + 6) = (a01Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a01Hex >> 12) & 0xFFF;
        
        a02Hex = RoundChange(a02 * Coef,1);
        *(Result + 8) = (a02Hex & 0xFFF) >> 1;     
        *(Result + 9) = (a02Hex >> 12) & 0xFFF;  
    }
    else
    {
        b10Hex = RoundChange(b10 * Coef,1);    
        *Result = (b10Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b10Hex >> 12) & 0xFFF;

        b11Hex = RoundChange(b11 * Coef,1);
        *(Result + 2) = (b11Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b11Hex >> 12) & 0xFFF;

        b12Hex = RoundChange(b12 * Coef,1);
        *(Result + 4) = (b12Hex & 0xFFF) >> 1;         
        *(Result + 5) = (b12Hex >> 12) & 0xFFF;

        a11Hex = RoundChange(a11 * Coef,1);
        *(Result + 6) = (a11Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a11Hex >> 12) & 0xFFF;

        a12Hex = RoundChange(a12 * Coef,1);
        *(Result + 8) = (a12Hex & 0xFFF) >> 1;          
        *(Result + 9) = (a12Hex >> 12) & 0xFFF; 
    }
}
/**********************************************************
 * @function    Hero_Calc_4thHP
 * @brief      Calc 4th order High Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
  *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Hero_Calc_4thHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
{
    float t0,t1,t2,G,a01,a02,b00,b01,b02,a11,a12,b10,b11,b12;
    float Tempt0t0,TmpCos18t0,TmpCos38t0;
    uint32_t Coef,b00Hex,b01Hex,b02Hex,b10Hex,b11Hex,b12Hex,a01Hex,a02Hex,a11Hex,a12Hex;

    Coef = 8388608;
    //Calc G Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0,t1 Value
    t0 = tanf((PI * sFilter.CoF) / ASRate);
    Tempt0t0 = (t0 * t0);
    TmpCos18t0 = (t0 * cosf(PI / 8));
    TmpCos38t0 = (t0 * cosf((3 * PI) / 8));
    t1 = 1 + 2 * TmpCos18t0 + Tempt0t0;
    t2 = 1 + 2 * TmpCos38t0 + Tempt0t0;
    
    //Calc a1,a2,b0,b1,b2 Value
    a01 = (1 - Tempt0t0) / t1;
    a02 = (2 * TmpCos18t0 - 1 - Tempt0t0) / (2 * t1);
    a11 = (1 - Tempt0t0) / t2;
    a12 = (2 * TmpCos38t0 - 1 - Tempt0t0) / (2 * t2);
    b00 = 1 / (2 * t1);
    b01 = -2 * b00;
    b02 = b00;
    b10 = G / (2 * t2);
    b11 = -2 * b10;
    b12 = b10;

    //Convert to HEX
    if(0 == Mode)
    {
        b00Hex = RoundChange(b00 * Coef,1);    
        *Result = (b00Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b00Hex >> 12) & 0xFFF;
        
        b01Hex = RoundChange(b01 * Coef,1);
        *(Result + 2) = (b01Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b01Hex >> 12) & 0xFFF;
        
        b02Hex = RoundChange(b02 * Coef,1);
        *(Result + 4) = (b02Hex & 0xFFF) >> 1;          
        *(Result + 5) = (b02Hex >> 12) & 0xFFF;
        
        a01Hex = RoundChange(a01 * Coef,1);
        *(Result + 6) = (a01Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a01Hex >> 12) & 0xFFF;
        
        a02Hex = RoundChange(a02 * Coef,1);
        *(Result + 8) = (a02Hex & 0xFFF) >> 1;      
        *(Result + 9) = (a02Hex >> 12) & 0xFFF; 
    }
    else
    {
        b10Hex = RoundChange(b10 * Coef,1);    
        *Result = (b10Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b10Hex >> 12) & 0xFFF;

        b11Hex = RoundChange(b11 * Coef,1);
        *(Result + 2) = (b11Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b11Hex >> 12) & 0xFFF;

        b12Hex = RoundChange(b12 * Coef,1);
        *(Result + 4) = (b12Hex & 0xFFF) >> 1;         
        *(Result + 5) = (b12Hex >> 12) & 0xFFF;

        a11Hex = RoundChange(a11 * Coef,1);
        *(Result + 6) = (a11Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a11Hex >> 12) & 0xFFF;

        a12Hex = RoundChange(a12 * Coef,1);
        *(Result + 8) = (a12Hex & 0xFFF) >> 1;          
        *(Result + 9) = (a12Hex >> 12) & 0xFFF; 
    }
}
/**********************************************************
 * @function    Hero_Calc_3rdLP_By21
 * @brief      Calc 3rd order Low Pass Filter  Cofficient
 *                  the 3rd order LP is a 2nd cascaded with 1st
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
  *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Hero_Calc_3rdLP_By21(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
{
    float t0,t1,G,a01,a02,b00,b01,b02,a11,a12,b10,b11,b12;
    float Tempt0t0;
    uint32_t Coef,b00Hex,b01Hex,b02Hex,b10Hex,b11Hex,b12Hex,a01Hex,a02Hex,a11Hex,a12Hex;

    Coef = 8388608;
    //Calc G Value
    G = powf(10.0,(sFilter.Gain / 20.0));

    //Calc t0,t1 Value
    t0 = tanf((PI * sFilter.CoF) / ASRate);
    Tempt0t0 = (t0 * t0);
    t1 = 1 + t0 + Tempt0t0;

    //Calc Value
    a01 = (1 - Tempt0t0) / t1;
    a02 = (t0 - Tempt0t0 - 1) / (2 * t1);
    b00 = Tempt0t0 / (2 * t1);
    b01 = 2 * b00; 
    b02 = b00;
    a11 = (1 - t0) / (2 + 2 * t0);
    b10 = (G * t0) / (2 * t0 + 2);
    b11 = b10;

    //Convert to HEX
    if(0 == Mode)
    {
        b00Hex = RoundChange(b00 * Coef,1);    
        *Result = (b00Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b00Hex >> 12) & 0xFFF;
        
        b01Hex = RoundChange(b01 * Coef,1);
        *(Result + 2) = (b01Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b01Hex >> 12) & 0xFFF;
        
        b02Hex = RoundChange(b02 * Coef,1);
        *(Result + 4) = (b02Hex & 0xFFF) >> 1;        
        *(Result + 5) = (b02Hex >> 12) & 0xFFF;
        
        a01Hex = RoundChange(a01 * Coef,1);
        *(Result + 6) = (a01Hex & 0xFFF) >> 1;        
        *(Result + 7) = (a01Hex >> 12) & 0xFFF;
        
        a02Hex = RoundChange(a02 * Coef,1);
        *(Result + 8) = (a02Hex & 0xFFF) >> 1;       
        *(Result + 9) = (a02Hex >> 12) & 0xFFF;  
    }
    else
    {
        b10Hex = RoundChange(b10 * Coef,1);    
        *Result = (b10Hex & 0xFFF) >> 1;        
        *(Result + 1) = (b10Hex >> 12) & 0xFFF;

        b11Hex = RoundChange(b11 * Coef,1);
        *(Result + 2) = (b11Hex & 0xFFF) >> 1;       
        *(Result + 3) = (b11Hex >> 12) & 0xFFF;

        a11Hex = RoundChange(a11 * Coef,1);
        *(Result + 4) = (a11Hex & 0xFFF) >> 1;        
        *(Result + 5) = (a11Hex >> 12) & 0xFFF;
    }
}




#if 0
/**********************************************************
 * @function    Hero_InitAudioPointer
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
 uint8_t Hero_InitAudioPointer(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sHero.SubStep)
    {
        //select limiter configuration 1
        case OPERATION_0:
            SubResult = Hero_DrvLimiterConfigSel(1);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_1);
            }
            break;
            
        //set  front&rear limiter  -1db,    
        case OPERATION_1:
            SubResult = Hero_DrvLimiterSet(Front,-1,AUDIO_ON);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_2);
            }
            break;
            
        //set subcenter limiter  
        case OPERATION_2:
            SubResult = Hero_DrvLimiterSet(SubCenter,-1,AUDIO_ON);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_3);
            }
            break;
            
        //set subwoofer limiter 
        case OPERATION_3:
            SubResult = Hero_DrvLimiterSet(SubWoofer,-1,AUDIO_ON);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_4);
            }
            break;
            
        // Front/Rear Limiter Flag generator set,SCD0  ,hight active
        case OPERATION_4:
            SubResult = Hero_DrvLimiterFlagGenerSet(Front,LimiterFlag_Mask_SCD0,(uint32_t)0);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_5);
            }
            break;
            
        //SubCenter Limiter Flag generator set,SCD1  high active    
        case OPERATION_5:
            SubResult = Hero_DrvLimiterFlagGenerSet(SubCenter,LimiterFlag_Mask_SCD1,(uint32_t)0);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_6);
            }
            break;
            
        //Subwoofer Limiter Flag generator set,SCD2 , high active
        case OPERATION_6:
            SubResult = Hero_DrvLimiterFlagGenerSet(SubWoofer,LimiterFlag_Mask_SCD2,(uint32_t)0);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_7);
            }
            break;    
            
        //Set Clip detector 0 treshold gain=-20 dbFS
        case OPERATION_7:
            SubResult = Hero_DrvSoftClipDetectSet(SCD0,-20);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_8);
            }
            break;    
            
        //Set Clip detector 1 treshold gain=-20 dbFS
        case OPERATION_8:
            SubResult = Hero_DrvSoftClipDetectSet(SCD1,-20);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(OPERATION_9);
            }
            break;    
            
        //Set Clip detector 2 treshold gain=-20 dbFS
        case OPERATION_9:
            SubResult = Hero_DrvSoftClipDetectSet(SCD2,-20);
            if(SUBLAYER_DONE == SubResult)
            {
                Result = SUBLAYER_DONE;    
            }
            break;                
            
        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    if(SUBLAYER_ERROR == SubResult)
    {
        Result = SUBLAYER_ERROR;    
    }
    
    return (Result);    
}
#endif

/**********************************************************
 * @function    Hero_Calc_SwAddr
 * @brief      Calc Sw Eq Addr
 * @param      uint8_t SwL
 *                  uint8_t SwR
  *                 uint8_t Mode
 * @retval     Result
 **********************************************************/
uint16_t Hero_Calc_SwAddr(uint8_t SwL, uint8_t SwR, uint8_t Mode)
{
    uint16_t Result = ADSP_Y_EqSw_b00L_REL; 

    if(1 == Mode) //SwL2
    {
        if((FILTER_3RD == SwL) || (FILTER_4TH == SwL))
        {
            Result = ADSP_Y_EqSw_b10L_REL; 
        }
    }
    else if(2 == Mode)   //SwR 1
    {
        if((FILTER_1ST == SwL) || (FILTER_2ND == SwL))
        {
            Result = ADSP_Y_EqSw_b10L_REL; 
        }
        else if(FILTER_3RD == SwL)
        {
            Result = ADSP_Y_EqSw_a11L_REL; 
        }
        else if(FILTER_4TH == SwL)
        {
            Result = ADSP_Y_EqSw_b20L_REL; 
        }
    }
    else if(3 == Mode) //SwR2
    {
        if(FILTER_FLAT == SwL) 
        {
            Result = ADSP_Y_EqSw_b10L_REL; 
        }
        if((FILTER_1ST == SwL) || (FILTER_2ND == SwL))
        {
            Result = ADSP_Y_EqSw_b20L_REL; 
        }
        else if(FILTER_3RD == SwL)
        {
            Result = ADSP_Y_EqSw_a21L_REL; 
        }
        else if(FILTER_4TH == SwL)
        {
            Result = ADSP_Y_EqSwC_b30L_REL; 
        }
    }
    
    return (Result);
}

uint8_t Hero_PeqInit(void)
{
uint8_t Channel;
uint8_t Band;
uint8_t i= 0 ;
uint8_t Result ;
	if((BAND1 == sAudio.PeqBandSetp)&&(FrontLeft == sAudio.PeqChannelSetp))
	{
		for(i = 0; i < 10; i++)
		{
			sHero.XoverCoefBuffer[i] = 0x0000;
		}
		sHero.XoverCoefBuffer[1] = 0x0400;
	}
	if(sAudio.PeqResult == SUBLAYER_DONE)
	{		
#if D_DEBUG_AUDIO && D_PRINT_EN
		audio_printf(_T("PeqChannel: %d , PeqBand: %d   \n",sAudio.PeqChannelSetp,sAudio.PeqBandSetp));
#endif

		sAudio.PeqBandSetp ++ ;
		if(sAudio.PeqBandSetp >= (BAND6 + 1))
		{
			sAudio.PeqBandSetp = BAND1 ;
			sAudio.PeqChannelSetp ++ ;
			if(sAudio.PeqChannelSetp >= (RearRight +1))
			{
				sAudio.PeqChannelSetp = Center ;
				sAudio.PeqBandSetp = BAND1 ;
			}
		}
	}
	
	if (sAudio.PeqChannelSetp == Center)
	{
		sAudio.PeqChannelSetp = FrontLeft ;
		Result = SUBLAYER_DONE ;
	}
	else	
	{
	 	sAudio.PeqResult = Hero_DrvPEQSet(sAudio.PeqChannelSetp, sAudio.PeqBandSetp, sHero.XoverCoefBuffer);
		Result = SUBLAYER_DOING ;
	}
	return Result ;
	
}

/**********************************************************
 * @function    Dirana_SetCrossOver
 * @brief      Set CrossOver
 * @param      Null            
 * @retval     Result
 **********************************************************/
#define SWL_SLOPE   sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope
#define SWR_SLOPE   sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope
#define SWL_ADDR1   Hero_Calc_SwAddr(SWL_SLOPE,SWR_SLOPE,0)
#define SWL_ADDR2   Hero_Calc_SwAddr(SWL_SLOPE,SWR_SLOPE,1)
#define SWR_ADDR1   Hero_Calc_SwAddr(SWL_SLOPE,SWR_SLOPE,2)
#define SWR_ADDR2   Hero_Calc_SwAddr(SWL_SLOPE,SWR_SLOPE,3)

uint8_t Hero_SetCrossOver(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SET_PEQ;//49
    uint8_t Result = SUBLAYER_DOING;   
    uint8_t SubResult = SUBLAYER_DOING;
    LHP_ATTRI_STRUCT sTmp;
    uint8_t i;
    uint16_t  aXoverCoefBuf[10] = {0,0x0400,0,0, 0,0,0,0,  0,0 } ;
	
    switch(sAudio.XoverCtl)
    {
        case XOVER_CTL_DELAY:
            sAudio.XoverDelay = AudioDelay(T200MS);
            sAudio.XoverCtl = XOVER_CTL_MUTE;
            break;
    
        case XOVER_CTL_MUTE:
            if(0 != sAudio.XoverDelay)
                break;
            if(0x00 == (0x80 & sAudio.XoverMask))// audio reg 初始化的时候，不需要单独静音处理， 设置时，需要静音
            {
                Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_MUTE,SYSTEM_FRONT);
                sAudio.XoverDelay = AudioDelay(T150MS);
            }
	    else
	    {
		sAudio.PeqChannelSetp = FrontLeft ;
		sAudio.PeqBandSetp = BAND1 ;
	    }
            sAudio.XoverCtl = XOVER_CTL_INIT_F_R;
            break;
    
        //Initialize Cross Over:Front  Rear
        case XOVER_CTL_INIT_F_R:
            if(0 != sAudio.XoverDelay)
                break;
            if((sAudio.sAchAttri[sAudio.SysChannel].MuteState & MASK_F_SMUTE)
                || (sAudio.XoverMask & 0x80))// 在audio init 的时候，赋值 0xff .
            {
                if(XOVER_MASK_INIT & sAudio.XoverMask)// 在audio init 的时候，级联PEQ的67 两个2阶滤波器
                {
			SubResult = Hero_PeqInit();
			//SubResult = Hero_EasyProgrammWrite(PrivateID,ADSP_EASYP_GPF67_Enable);    
	               // hero 初始化的时候，需要将BAND0-7设置成Flat 状态 ?  前4个 是否可以设置成flat
                }
                else
                {
                    SubResult = SUBLAYER_DONE;
                }
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.XoverMask &= (~XOVER_MASK_INIT);
                    sAudio.XoverCtl = XOVER_CTL_CALC_FRONT1;
                }
            }
            break;

        //Calc Front HPF..according slope setting
        case XOVER_CTL_CALC_FRONT1:
            if(XOVER_MASK_FRONT & sAudio.XoverMask)
            {   //Flat response...
                if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                    || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope))
                {
                    for(i = 0; i < 10; i++)
                    {
                        sHero.XoverCoefBuffer[i] = 0x0000;
                    }
                    sHero.XoverCoefBuffer[1] = 0x0400;
                }
                else
                {
	         	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
			if(sTmp.Gain > 0)
				sTmp.Gain = 0 ;
				
                    sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].CoF];
                    //Calculate Filter Coefficient according Slope setting
                    if(XOVER_SLOPE_6 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
                    {
                        Hero_Calc_1stHP(sTmp,sHero.XoverCoefBuffer);                        
                    }
                    else if(XOVER_SLOPE_12 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
                    {
                        Hero_Calc_2ndHP(sTmp,sHero.XoverCoefBuffer);    
                    }
                    else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
                    {
                        Hero_Calc_3rdHP(sTmp,sHero.XoverCoefBuffer,0);    
                    }
                    else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
                    {
                        Hero_Calc_4thHP(sTmp,sHero.XoverCoefBuffer,0);  
                    }
                }
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT1_LEFT;
            }
            else
            {
                sAudio.XoverCtl = XOVER_CTL_CALC_REAR1;
                sAudio.XoverMask &= (~XOVER_MASK_FRONT);
            }
            break;
            
        //Set Front HPF 1
        case XOVER_CTL_SET_FRONT1_LEFT:
	 	SubResult = Hero_DrvPEQSet(FrontLeft, BAND6, sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT1_LEFT_REAR;
            }
            break;


        case XOVER_CTL_SET_FRONT1_LEFT_REAR:	
	 	SubResult = Hero_DrvPEQSet(FrontLeft, BAND7, aXoverCoefBuf);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT1_RIGHT_REAR;
            }
			
        case XOVER_CTL_SET_FRONT1_RIGHT_REAR:
	 	SubResult = Hero_DrvPEQSet(FrontRight, BAND7, aXoverCoefBuf);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT1_RIGHT;
            }

		
        case XOVER_CTL_SET_FRONT1_RIGHT:
	 	SubResult = Hero_DrvPEQSet(FrontRight, BAND6, sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                    || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope))
                {
                    sAudio.XoverMask &= (~XOVER_MASK_FRONT);
                    sAudio.XoverCtl = XOVER_CTL_CALC_REAR1;
					
                }
                else
                {
                    if(sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope >= XOVER_SLOPE_18)
                    {
                         sAudio.XoverCtl = XOVER_CTL_CALC_FRONT2;
                    }
                    else
                    {
                        sAudio.XoverMask &= (~XOVER_MASK_FRONT);
                        sAudio.XoverCtl = XOVER_CTL_CALC_REAR1;
                    }
                }
            }
            break;



        case XOVER_CTL_CALC_FRONT2:
         	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
		if(sTmp.Gain > 0)
			sTmp.Gain = 0 ;
            //sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
            sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].CoF];
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
            {
                Hero_Calc_3rdHP(sTmp,sHero.XoverCoefBuffer,1);
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT2_LEFT;
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
            {
                Hero_Calc_4thHP(sTmp,sHero.XoverCoefBuffer,1);  
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT2_LEFT;
            }
            break;
            
        //Set Front HPF2    
        case XOVER_CTL_SET_FRONT2_LEFT:
	   SubResult = Hero_DrvPEQSet(FrontLeft, BAND7, sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT2_RIGHT;
            }
            break;
        case XOVER_CTL_SET_FRONT2_RIGHT:
	   SubResult = Hero_DrvPEQSet(FrontRight, BAND7, sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverMask &= (~XOVER_MASK_FRONT);
                sAudio.XoverCtl = XOVER_CTL_CALC_REAR1;
            }
            break;

			
        //Calc Rear HPF
        case XOVER_CTL_CALC_REAR1:
            if(XOVER_MASK_REAR & sAudio.XoverMask)
            {
                if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                    || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope))
                {
                    for(i = 0; i < 10; i++)
                    {
                        sHero.XoverCoefBuffer[i] = 0x0000;
                    }
                    sHero.XoverCoefBuffer[1] = 0x0400;
                }
                else
                {
	         	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
			if(sTmp.Gain > 0)
				sTmp.Gain = 0 ;
                    //sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Level - 12;
                    sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].CoF];
                    if(XOVER_SLOPE_6 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
                    {
                        Hero_Calc_1stHP(sTmp,sHero.XoverCoefBuffer);                        
                    }
                    else if(XOVER_SLOPE_12 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
                    {
                        Hero_Calc_2ndHP(sTmp,sHero.XoverCoefBuffer);    
                    }
                    else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
                    {
                        Hero_Calc_3rdHP(sTmp,sHero.XoverCoefBuffer,0);    
                    }
                    else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
                    {
                        Hero_Calc_4thHP(sTmp,sHero.XoverCoefBuffer,0);  
                    }
                }       
                sAudio.XoverCtl = XOVER_CTL_SET_REAR1_LEFT;
            }
            else
            {
                sAudio.XoverMask &= (~XOVER_MASK_REAR);
                sAudio.XoverCtl = XOVER_CTL_DEMUTE;
            }
            break;
            
        //Set Rear HPF 1
        case XOVER_CTL_SET_REAR1_LEFT:
	   SubResult = Hero_DrvPEQSet(RearLeft, BAND6, sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
			sAudio.XoverCtl = XOVER_CTL_SET_REAR1_LEFT_REAR;            
		}
            break;

        case XOVER_CTL_SET_REAR1_LEFT_REAR:	
	 	SubResult = Hero_DrvPEQSet(RearLeft, BAND7, aXoverCoefBuf);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_SET_REAR1_RIGHT_REAR;
            }
			
        case XOVER_CTL_SET_REAR1_RIGHT_REAR:
	 	SubResult = Hero_DrvPEQSet(RearRight, BAND7, aXoverCoefBuf);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_SET_REAR1_RIGHT;
            }

			
        case XOVER_CTL_SET_REAR1_RIGHT:
	   SubResult = Hero_DrvPEQSet(RearRight, BAND6, sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                    || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope))
                {
                    sAudio.XoverMask &= (~XOVER_MASK_REAR);
                    sAudio.XoverCtl = XOVER_CTL_DEMUTE;
                }
                else
                {
                    if(sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope >= XOVER_SLOPE_18)
                    {
                         sAudio.XoverCtl = XOVER_CTL_CALC_REAR2;
                    }
                    else
                    {
                        sAudio.XoverMask &= (~XOVER_MASK_REAR);
                        sAudio.XoverCtl = XOVER_CTL_DEMUTE;
                    }
                }
            }
            break;



        case XOVER_CTL_CALC_REAR2:
         	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
		if(sTmp.Gain > 0)
			sTmp.Gain = 0 ;
            sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].CoF];
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
            {
                Hero_Calc_3rdHP(sTmp,sHero.XoverCoefBuffer,1);
                sAudio.XoverCtl = XOVER_CTL_SET_REAR2_LEFT;
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
            {
                Hero_Calc_4thHP(sTmp,sHero.XoverCoefBuffer,1);  
                sAudio.XoverCtl = XOVER_CTL_SET_REAR2_LEFT;
            }
            break;
            
        //Set Rear HPF2    

        case XOVER_CTL_SET_REAR2_LEFT:
            SubResult = Hero_DrvPEQSet(RearLeft, BAND7, sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_SET_REAR2_RIGHT;
            }
            break;  
        case XOVER_CTL_SET_REAR2_RIGHT:
            SubResult = Hero_DrvPEQSet(RearRight, BAND7, sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverMask &= (~XOVER_MASK_REAR);
                sAudio.XoverCtl = XOVER_CTL_DEMUTE;
            }
            break;  


        case XOVER_CTL_INIT_SWL:
            if(XOVER_MASK_SW & sAudio.XoverMask)
            {
                int32_t TmpDat;
                if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                    || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope))
                {
                    TmpDat = ADSP_EASYP_PEQ_Center_IIR_passthrough;
                }
                else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    TmpDat = ADSP_EASYP_PEQ_Center_IIR3;
                }
                else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    TmpDat = ADSP_EASYP_PEQ_Center_IIR4_headroom;
                }
                else 
                {
                    TmpDat = ADSP_EASYP_PEQ_Center_IIR2_headroom;
                }
                SubResult = Hero_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,TmpDat);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.XoverCtl = XOVER_CTL_CALC_SWL1;
                }
            }
            else
            {
                sAudio.XoverCtl = XOVER_CTL_DEMUTE;
                sAudio.XoverMask &= (~XOVER_MASK_SW);
            }
            break;

        case XOVER_CTL_CALC_SWL1:
            if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                    || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope))
            {
                sAudio.XoverCtl = XOVER_CTL_INIT_SWR;
            }
            else
            {
         	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
		if(sTmp.Gain > 0)
			sTmp.Gain = 0 ;
                sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].CoF];
                if(XOVER_SLOPE_6 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Hero_Calc_1stLP(sTmp,sHero.XoverCoefBuffer);                        
                }
                else if(XOVER_SLOPE_12 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Hero_Calc_2ndLP(sTmp,sHero.XoverCoefBuffer);    
                }
                else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) //NOTE: 3rd Filter's struction
                {
                    Hero_Calc_3rdLP_By21(sTmp,sHero.XoverCoefBuffer,0);    
                }
                else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Hero_Calc_4thLP(sTmp,sHero.XoverCoefBuffer,0);  
                }
                sAudio.XoverCtl = XOVER_CTL_SET_SWL1;
            }
            break;

        case XOVER_CTL_SET_SWL1:
            SubResult = Hero_ScratchDataWrite(PrivateID,SWL_ADDR1,10,sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)    
            {
                if(sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope >= XOVER_SLOPE_18)
                {
                     sAudio.XoverCtl = XOVER_CTL_CALC_SWL2;
                }
                else
                {
                    sAudio.XoverCtl = XOVER_CTL_INIT_SWR;
                }
            }
            break;

        case XOVER_CTL_CALC_SWL2:
	     	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
		if(sTmp.Gain > 0)
			sTmp.Gain = 0 ;
            sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].CoF];
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) //NOTE: 3rd Filter's struction
            {
                Hero_Calc_3rdLP_By21(sTmp,sHero.XoverCoefBuffer,1);    
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                Hero_Calc_4thLP(sTmp,sHero.XoverCoefBuffer,1);  
            }
            sAudio.XoverCtl = XOVER_CTL_SET_SWL2;
            break;

        case XOVER_CTL_SET_SWL2:
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) 
            {
                SubResult = Hero_ScratchDataWrite(PrivateID,SWL_ADDR2,6,sHero.XoverCoefBuffer);
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                SubResult = Hero_ScratchDataWrite(PrivateID,SWL_ADDR2,10,sHero.XoverCoefBuffer);
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_INIT_SWR;
            }
            break;

        case XOVER_CTL_INIT_SWR:
            {
            int32_t TmpDat;
            if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope))
            {
                TmpDat = ADSP_EASYP_PEQ_Sw_IIR_passthrough;
            }
            else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                TmpDat = ADSP_EASYP_PEQ_Sw_IIR3;
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                TmpDat = ADSP_EASYP_PEQ_Sw_IIR4_headroom;
            }
            else 
            {
                TmpDat = ADSP_EASYP_PEQ_Sw_IIR2_headroom;
            }
            SubResult = Hero_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,TmpDat);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_CALC_SWR1;
            }
            }
            break;
            
        case XOVER_CTL_CALC_SWR1:
            if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                    || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope))
            {
                sAudio.XoverCtl = XOVER_CTL_DEMUTE;
                sAudio.XoverMask &= (~XOVER_MASK_SW);
            }
            else
            {
         	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
		if(sTmp.Gain > 0)
			sTmp.Gain = 0 ;
                sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].CoF];
                if(XOVER_SLOPE_6 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Hero_Calc_1stLP(sTmp,sHero.XoverCoefBuffer);                        
                }
                else if(XOVER_SLOPE_12 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Hero_Calc_2ndLP(sTmp,sHero.XoverCoefBuffer);    
                }
                else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) //NOTE: 3rd Filter's struction
                {
                    Hero_Calc_3rdLP_By21(sTmp,sHero.XoverCoefBuffer,0);    
                }
                else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Hero_Calc_4thLP(sTmp,sHero.XoverCoefBuffer,0);  
                }
                sAudio.XoverCtl = XOVER_CTL_SET_SWR1;
            }
            break;
            
        case XOVER_CTL_SET_SWR1:
            SubResult = Hero_ScratchDataWrite(PrivateID,SWR_ADDR1,10,sHero.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)    
            {

                if(sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope >= XOVER_SLOPE_18)
                {
                     sAudio.XoverCtl = XOVER_CTL_CALC_SWR2;
                }
                else
                {
                    sAudio.XoverCtl = XOVER_CTL_DEMUTE;
                    sAudio.XoverMask &= (~XOVER_MASK_SW);
                }
            }
            break;
            
        case XOVER_CTL_CALC_SWR2:
         	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
		if(sTmp.Gain > 0)
			sTmp.Gain = 0 ;
            sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].CoF];
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) //NOTE: 3rd Filter's struction
            {
                Hero_Calc_3rdLP_By21(sTmp,sHero.XoverCoefBuffer,1);    
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                Hero_Calc_4thLP(sTmp,sHero.XoverCoefBuffer,1);  
            }
            sAudio.XoverCtl = XOVER_CTL_SET_SWR2;
            break;
            
        case XOVER_CTL_SET_SWR2:
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) 
            {
                SubResult =Hero_ScratchDataWrite(PrivateID,SWR_ADDR2,6,sHero.XoverCoefBuffer);
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                SubResult = Hero_ScratchDataWrite(PrivateID,SWR_ADDR2,10,sHero.XoverCoefBuffer);
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverCtl = XOVER_CTL_DEMUTE;
                sAudio.XoverMask &= (~XOVER_MASK_SW);
            }
            break;

        case XOVER_CTL_DEMUTE:
            if(0x00 == (0x80 & sAudio.XoverMask))
            {
                Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_UNMUTE,SYSTEM_FRONT);
                sAudio.XoverDelay = AudioDelay(T300MS);
            }
             sAudio.XoverCtl = XOVER_CTL_END;
            break;

        //All Done!!
        case XOVER_CTL_END:
            if(0 != sAudio.XoverDelay)
                break;
            if((0x00 == (sAudio.sAchAttri[sAudio.SysChannel].MuteState & MASK_F_SMUTE)) 
                || (0x80 & sAudio.XoverMask))
            {
                sAudio.XoverMask &= 0x7F;
                Result = SUBLAYER_DONE;
                sAudio.XoverCtl = 0;
            }
            break;
    }

    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.XoverCtl = 0;
        sAudio.XoverDelay = 0;
    }

    return (Result);
}


uint8_t Hero_SrcScalerToZero(uint8_t Type)
{    
    HERO_DRIVER_TYPE_ENUM PrivateID = HERO_IIC_SRC_SCALER;
    uint8_t Result = SUBLAYER_DOING;
    uint16_t Addr;
    int32_t Data;
    
    if(SYSTEM_FRONT == Type)    
    {
        Addr = HDSP_Y_Vol_SrcScalP_REL;
    }
    else if(SYSTEM_REAR == Type)
    {
        Addr = HDSP_Y_Vol_SrcScalS_REL;    
    }
    
    Data = 0x0000;
    
    Result = Hero_WriteMemWord(PrivateID,I2CDRV_Y_MEM,Addr,Data); //the primary volume will be divided to 2 prara

    return (Result);
}


#endif//D_AUDIO_ASP_HERO


