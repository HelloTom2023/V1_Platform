/**********************************************************
 * @file        Dirana3_Func.c
 * @purpose    Dirana Functions 
 * @version    0.01
 * @date        18.Dec. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          18.Dec.2012        v0.01        created
 *  
  **********************************************************/
#define DIRANA3_FUNC_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
#ifdef D_AUDIO_ASP_DIRANA
#include "Dirana3_Patch.c"
/* ========================= Function Announcement  =================== */

/* ========================= public variable ==================== */




/* ========================= private variable =================== */

//Keycode Buffer
static const uint8_t Tab_KeyCode[][3] = 
{
#if 0
    {0xD6,0x78,0x33},    // Radio allow XY mem access for all 3 radio DSPs
    {0x67,0xB2,0xCF},// Radio allow MMIO (PDC) memory access for 2 PDCs
    //{0xFA,0x15,0x61},// Radio enable FM Scanning Antenna Diversity
    {0x50,0xA3,0x88},// Radio enable FM Phase Diversity
    //{0xC2,0x7E,0xAF},// Radio enable FM Channel Equalisation
    //{0x1B,0xC1,0xC7},// Radio enable Dual AM using wideband
    {0x2C,0x42,0xA1},// Audio enable Asynchronous I2S outputs
    //{0xC3,0xD2,0x35},// Audio enable TDM4 and TDM5
    {0x2A,0xAB,0xE6},// Generic allow ICC memory access
    {0x51,0xD2,0x09},// Generic allow full memory access
    {0x60,0x7B,0x82}, //UltraBass Keycode 
    {0xC9,0xB9,0x58}, //ADC45
    {0x5E,0x10,0xDC}, //DAC45
#endif    
    {0x5B,0x06,0x76},
    //End of Flag
    {0x00,0x00,0x00},
};
//SDSP: sample rate converter
static const MEM_BUFFER_STRUCT Tab_SampleRC[] = 
{
    {MEM_TYPE_SX,SDSP_X_SRC_CtrlTS0_REL,0x800000}, //Enable: primary 
    {MEM_TYPE_SX,SDSP_X_SRC_CtrlTS1_REL,0x800000}, //Enable: secondary
    {MEM_TYPE_SX,SDSP_X_SRC_CtrlTS2_REL,0x800000}, //Enable: 2nd secondary
    {MEM_TYPE_SX,SDSP_X_SRC_CtrlTS3_REL,0x800000}, //Enable: Navigation
    {MEM_TYPE_SX,SDSP_X_SRC_CtrlTS4_REL,0x800000}, //Enable: Phone
    {MEM_TYPE_SX,SDSP_X_SRC_CtrlTS5_REL,0x800000}, //Enable: IBOC
    //End Flag
    {MEM_INVALID,0,0},
};
//SDSP: sample rate converter
static const MEM_BUFFER_STRUCT Tab_DeEmphasis[] = 
{
    {MEM_TYPE_X,ADSP_X_EasyP_Index_REL,ADSP_EASYP_DCDeemphFilter_NoDmphA}, //Enable: primary 
    {MEM_TYPE_X,ADSP_X_EasyP_Index_REL,ADSP_EASYP_DCDeemphFilter_NoDmphB}, //Enable: secondary
    {MEM_TYPE_X,ADSP_X_EasyP_Index_REL,ADSP_EASYP_DCDeemphFilter_NoDmphC}, //Enable: 2nd secondary
    //End Flag
    {MEM_INVALID,0,0},
};
//Input/Output Config
static const uint8_t Tab_InOutInit[][2] = 
{
    //Analog Input
    {IN_ID_AIN0,AD_IN_HCM_1V},
    {IN_ID_AIN1,AD_IN_HCM_1V},
    {IN_ID_AIN2,AD_IN_HCM_1V},
    {IN_ID_AIN3,AD_IN_HCM_1V},
    {IN_ID_AIN4,AD_IN_HCM_1V},    //Keycode protected
    {IN_ID_AIN5,AD_IN_HCM_1V},    //Keycode protected
    
    //I2S Input
    {IN_ID_IIS0,I2S_IN_PHILIP},
    {IN_ID_IIS1,I2S_IN_PHILIP},
    {IN_ID_IIS2,I2S_IN_PHILIP},
    {IN_ID_IIS3,I2S_IN_PHILIP},
    {IN_ID_IIS9,I2S_IN_PHILIP},
    
    //HOST I2S Input
    {IN_ID_HOST_A,I2S_IN_PHILIP},
    {IN_ID_HOST_B,I2S_IN_PHILIP},
    {IN_CONFIG_HOSTA,HOST_CONFIG_SYNC},
    {IN_CONFIG_HOSTB,HOST_CONFIG_ASYNC},
    
    //Host Output
    {OUT_ID_HOST0,PERIPHERAL_ON},
    {OUT_ID_HOST1,PERIPHERAL_ON},    
    {OUT_ID_HOST2,PERIPHERAL_ON},    
    {OUT_ID_HOST3,PERIPHERAL_ON},    
    {OUT_CONFIG_HOST,I2S_IN_PHILIP},    // Host Out COnfig: Philip

    //SPDIF Input 
    {IN_ID_SPDIF1,SPDIF_IN_ANALOG},    
    {IN_CONFIG_SPDIF1,0x02},       //33.5~126.1

    //DAC
    {AUDIO_DAC01,PERIPHERAL_ON},    
    {AUDIO_DAC23,PERIPHERAL_ON},    
    {AUDIO_DAC45,PERIPHERAL_ON},    //Keycode protected :Analog Subwoofer
    
    //ADC
    {AUDIO_ADC,PERIPHERAL_ON},    

    //End Flag
    {0x00,0x00},
};
//Scaling Initial Table
static const MEM_BUFFER_STRUCT Tab_ScalingInit[] = 
{
    {MEM_TYPE_X,ADSP_X_Vol_Boost12dB_REL,0x000000}, //for volume :select FixedBoost 48.16
    {MEM_TYPE_X,ADSP_X_Vol_OneOverMaxBoostP_REL,ADSP_X_Vol_OneOverMaxBoostP_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_UpScalF_REL,ADSP_Y_Vol_UpScalF_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_UpScalR_REL,ADSP_Y_Vol_UpScalR_Data}, 
    {MEM_TYPE_Y,ADSP_Y_Vol_UpScalSwL_REL,ADSP_Y_Vol_UpScalSwL_Data}, 
    {MEM_TYPE_Y,ADSP_Y_Vol_UpScalSwR_REL,ADSP_Y_Vol_UpScalSwR_Data}, 
    {MEM_TYPE_Y,ADSP_Y_Vol_ScalF_REL,ADSP_Y_Vol_ScalF_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ScalR_REL,ADSP_Y_Vol_ScalR_Data}, 
    {MEM_TYPE_Y,ADSP_Y_Vol_ScalSwL_REL,ADSP_Y_Vol_ScalSwL_Data}, 
    {MEM_TYPE_Y,ADSP_Y_Vol_ScalSwR_REL,ADSP_Y_Vol_ScalSwR_Data}, 
    {MEM_TYPE_X,ADSP_X_Vol_OneOverMaxBoostS_REL,ADSP_X_Vol_OneOverMaxBoostS_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_UpScalS_REL,ADSP_Y_Vol_UpScalS_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_UpScalS2_REL,ADSP_Y_Vol_UpScalS2_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ScalS_REL,ADSP_Y_Vol_ScalS_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ScalS2_REL,ADSP_Y_Vol_ScalS2_Data},
    //End Flag
    {MEM_INVALID,0,0},
};
//Source Scaling Table
static const MEM_BUFFER_STRUCT Tab_SrcScaling[] = 
{
    //{MEM_TYPE_Y,ADSP_Y_Vol_SrcScalP_REL,0x0400},    //Primary Src Scaler Gain +0
    {MEM_TYPE_Y,ADSP_Y_Vol_SrcScalS_REL,0x0400},    //Secondary Src Scaler Gain +0
    {MEM_TYPE_Y,ADSP_Y_Vol_SrcScalS2_REL,0x0400},     // 2nd Secondary Src Scaler Gain +0
    {MEM_TYPE_Y,ADSP_Y_Vol_SrcScalN_REL,0x0400},
    {MEM_TYPE_Y,ADSP_Y_Vol_SrcScalT_REL,0x0400},
    //End Flag
    {MEM_INVALID,0,0},
};
//Audio Pointer Table
static const MEM_BUFFER_STRUCT Tab_AudioPointer[] = 
{
    //UBass Connection
    {MEM_TYPE_X,ADSP_X_AUB2_InPntr_REL,ADSP_X_Loudf_OutL_REL}, //Input
    {MEM_TYPE_X,ADSP_X_FInPntr_REL,ADSP_X_AUB2_out1_REL},     //Output
    {MEM_TYPE_X,ADSP_X_RInPntr_REL,ADSP_X_AUB2_out1_REL},
    {MEM_TYPE_X,ADSP_X_SwFInPntr_REL,ADSP_X_AUB2_out1_REL},
    {MEM_TYPE_X,ADSP_X_SwRInPntr_REL,ADSP_X_AUB2_out1_REL},

    //GPF67 Connection
    {MEM_TYPE_X,ADSP_X_GPF6_InPntr_REL,ADSP_X_FrontOutL_REL}, //Input
    {MEM_TYPE_X,ADSP_X_GPF7_InPntr_REL,ADSP_X_RearOutL_REL},
    {MEM_TYPE_X,ADSP_X_FDACpntr_REL,ADSP_X_GPF6_OutL_REL},    
    {MEM_TYPE_X,ADSP_X_RDACpntr_REL,ADSP_X_GPF7_OutL_REL}, 

    //GPF2
    {MEM_TYPE_X,ADSP_X_GPF2_InPntr_REL,ADSP_X_SwOutL_REL},    //Sw
    {MEM_TYPE_X,ADSP_X_SWDACpntr_REL,ADSP_X_GPF2_OutL_REL},

    //Host Output Connection
    {MEM_TYPE_X,ADSP_X_HIIS0Outpntr_REL,ADSP_X_SecOutL_REL},     //output sel: iis1 outc: rear 1
    {MEM_TYPE_X,ADSP_X_HIIS1Outpntr_REL,ADSP_X_SecOutL_REL},     //output sel:  iis2 outc: rear 2
    {MEM_TYPE_X,ADSP_X_HIIS2Outpntr_REL,ADSP_X_SecOutL_REL},     //output sel:  iis3 outc
    {MEM_TYPE_X,ADSP_X_HIIS3Outpntr_REL,ADSP_X_SecOutL_REL}, //output sel:  iis4 outc

    //{MEM_TYPE_X,ADSP_X_SrcScal6_F_InPntr_REL,ADSP_X_SRC1InL_REL}, //6-Front
    //{MEM_TYPE_X,ADSP_X_SrcScal6_R_InPntr_REL,ADSP_X_SRC1InL_REL}, //6-Rear
    //{MEM_TYPE_X,ADSP_X_SrcScal6_C_InPntr_REL,ADSP_X_SRC1InL_REL}, //6-Centre
    //{MEM_TYPE_X,ADSP_X_SrcScal6_Sw_InPntr_REL,ADSP_X_SRC1InL_REL}, //6-Subwoofer
    {MEM_TYPE_X,ADSP_X_Sup_ExtInPntr_REL,ADSP_X_Chime_Cl_Out_REL},   //Ext Connect to Chime Click Clack
    //End Flag
    {MEM_INVALID,0,0},
};
//Audio Pointer Table for 6 Channel
static const MEM_BUFFER_STRUCT Tab_6ChanAP[] = 
{
    //Compressor and Expander : Available if CmpExp Enable
    //{MEM_TYPE_X,ADSP_X_CompExp_F_InPntr_REL,ADSP_X_Vol_SrcScalOutFL_REL},
    //{MEM_TYPE_X,ADSP_X_CompExp_R_InPntr_REL,ADSP_X_Vol_SrcScalOutRL_REL},
    //{MEM_TYPE_X,ADSP_X_CompExp_C_InPntr_REL,ADSP_X_Vol_SrcScalOutC_REL},
    //{MEM_TYPE_X,ADSP_X_CompExp_Sw_InPntr_REL,ADSP_X_Vol_SrcScalOutSw_REL},
    //Graphic Equalizer
    {MEM_TYPE_X,ADSP_X_GEq_F_InPntr_REL,ADSP_X_Vol_SrcScalOutFL_REL},
    {MEM_TYPE_X,ADSP_X_GEq_R_InPntr_REL,ADSP_X_Vol_SrcScalOutRL_REL},
    {MEM_TYPE_X,ADSP_X_GEq_C_InPntr_REL,ADSP_X_Vol_SrcScalOutC_REL},
    {MEM_TYPE_X,ADSP_X_GEq_Sw_InPntr_REL,ADSP_X_Vol_SrcScalOutSw_REL},
    //Loudness Input Pointer

    //Tone Control--Input Pointer                   //According actual Audio Channel setting 
    {MEM_TYPE_X,ADSP_X_PToneControl6_InPntr_REL,ADSP_X_GEq_OutFL_REL},

    //Volume Input

    //Source Scaler 
    
    //End Flag
    {MEM_INVALID,0,0},
};
//Audio Pointer Table for 2 Channel
static const MEM_BUFFER_STRUCT Tab_2ChanAP[] = 
{
    //UBass Connection
    {MEM_TYPE_X,ADSP_X_AUB2_InPntr_REL,ADSP_X_Loudf_OutL_REL}, //Input
    //End Flag
    {MEM_INVALID,0,0},
};
//Channel Gain Table
static const MEM_BUFFER_STRUCT Tab_ChanGain[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainPFL_REL,ADSP_Y_Vol_ChanGainPFL_Data},// Primary Front Left Channel
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainPFR_REL,ADSP_Y_Vol_ChanGainPFR_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainPRL_REL,ADSP_Y_Vol_ChanGainPRL_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainPRR_REL,ADSP_Y_Vol_ChanGainPRR_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainSwL_REL,ADSP_Y_Vol_ChanGainSwL_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainSwR_REL,ADSP_Y_Vol_ChanGainSwR_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainSL_REL,ADSP_Y_Vol_ChanGainSL_Data}, 
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainSR_REL,ADSP_Y_Vol_ChanGainSR_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainS2L_REL,ADSP_Y_Vol_ChanGainS2L_Data}, 
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainS2R_REL,ADSP_Y_Vol_ChanGainS2R_Data},
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainN_REL,ADSP_Y_Vol_ChanGainN_Data}, 
    {MEM_TYPE_Y,ADSP_Y_Vol_ChanGainT_REL,ADSP_Y_Vol_ChanGainT_Data}, 
    //End Flag
    {MEM_INVALID,0,0},
};
// Beep Type: Low Frequency  1KHZ
static const MEM_BUFFER_STRUCT Tab_WholeChimeLow[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Tsq_SeqStat_Bk_REL,0x07FF},
#if (ASR_SET_48 == ASR_SETTING)   
    {MEM_TYPE_X,ADSP_X_Tsq_CrosFStp_Bk_REL,0x011111},
    {MEM_TYPE_X,ADSP_X_Tsq_ArLinStpA_Bk_REL,0x011111},
#else
    {MEM_TYPE_X,ADSP_X_Tsq_CrosFStp_Bk_REL,0x012937},
    {MEM_TYPE_X,ADSP_X_Tsq_ArLinStpA_Bk_REL,0x012937},
#endif    
    {MEM_TYPE_Y,ADSP_Y_Tsq_ArType_Bk_REL,0x0001},
#if (ASR_SET_48 == ASR_SETTING)  
    {MEM_TYPE_X,ADSP_X_Tsq_ArRelCoef_Bk_REL,0x7EF011},
    {MEM_TYPE_X,ADSP_X_Tsq_TA_Bk_REL,0x0001FE},// 170ms
    {MEM_TYPE_X,ADSP_X_Tsq_TB_Bk_REL,0x00005A},// 30ms
#else 
    {MEM_TYPE_X,ADSP_X_Tsq_ArRelCoef_Bk_REL,0x7ED821},
    {MEM_TYPE_X,ADSP_X_Tsq_TA_Bk_REL,0x0001D5},// 170ms
    {MEM_TYPE_X,ADSP_X_Tsq_TB_Bk_REL,0x000053},// 30ms
#endif  
    {MEM_TYPE_X,ADSP_X_Tsq_repeate_Bk_REL,0x0002},    // 1 times
    
    {MEM_TYPE_X,ADSP_X_Tsq_ChangeThreshold_REL,0x4026E7},
    {MEM_TYPE_X,ADSP_X_Tsq_DecayThreshold_REL,0x000000},
    //{MEM_TYPE_Y,ADSP_Y_Tsq_ChimeVol_Bk_REL,0x03CA},  //Volume
    //Slot1
#if (ASR_SET_48 == ASR_SETTING)   
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x03D5}, //Frequency L
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Htone_Bk_REL,0x07EE},    //Frequency H
#else
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x01FD}, //Frequency L
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Htone_Bk_REL,0x07EB},    //Frequency H
#endif    
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Vtone_Bk_REL,0x0DFE},
#if (ASR_SET_48 == ASR_SETTING)    
    {MEM_TYPE_X,ADSP_X_Tsq_T1_Bk_REL,0x000258}, // 200 ms  (bigger than TP)
#else  
    {MEM_TYPE_X,ADSP_X_Tsq_T1_Bk_REL,0x000227}, // 200 ms  (bigger than TP)
#endif
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Clip_Bk_REL,0x0080},
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Type_Bk_REL,0x0000},

    //No Need Other Slot... Because of Time...
    
    {MEM_TYPE_X,ADSP_X_Tsq_addmul_Bk_REL,0x000000},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c02_Bk_REL,0x0B24},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c1_Bk_REL,0x0FFF},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c3_Bk_REL,0x0FFF},
    {MEM_TYPE_Y,ADSP_Y_Tsq_Copied_REL,0x0800},
    //End Flag
    {MEM_INVALID,0,0},        
};
// Beep Type: High Frequency  1.5KHZ
static const MEM_BUFFER_STRUCT Tab_WholeChimeHigh[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Tsq_SeqStat_Bk_REL,0x07FF},
#if (ASR_SET_48 == ASR_SETTING)   
    {MEM_TYPE_X,ADSP_X_Tsq_CrosFStp_Bk_REL,0x011111},
    {MEM_TYPE_X,ADSP_X_Tsq_ArLinStpA_Bk_REL,0x011111},
#else
    {MEM_TYPE_X,ADSP_X_Tsq_CrosFStp_Bk_REL,0x012937},
    {MEM_TYPE_X,ADSP_X_Tsq_ArLinStpA_Bk_REL,0x012937},
#endif    
    {MEM_TYPE_Y,ADSP_Y_Tsq_ArType_Bk_REL,0x0001},
#if (ASR_SET_48 == ASR_SETTING)  
    {MEM_TYPE_X,ADSP_X_Tsq_ArRelCoef_Bk_REL,0x7EF011},
    {MEM_TYPE_X,ADSP_X_Tsq_TA_Bk_REL,0x0001FE},// 170ms
    {MEM_TYPE_X,ADSP_X_Tsq_TB_Bk_REL,0x00005A},// 30ms
#else
    {MEM_TYPE_X,ADSP_X_Tsq_ArRelCoef_Bk_REL,0x7ED821},
    {MEM_TYPE_X,ADSP_X_Tsq_TA_Bk_REL,0x0001D5},// 170ms
    {MEM_TYPE_X,ADSP_X_Tsq_TB_Bk_REL,0x000053},// 30ms
#endif    
    {MEM_TYPE_X,ADSP_X_Tsq_repeate_Bk_REL,0x0002},    // 1 times
    
    {MEM_TYPE_X,ADSP_X_Tsq_ChangeThreshold_REL,0x4026E7},
    {MEM_TYPE_X,ADSP_X_Tsq_DecayThreshold_REL,0x000000},
    //{MEM_TYPE_Y,ADSP_Y_Tsq_ChimeVol_Bk_REL,0x03CA},  //Volume
    //Slot1
#if (ASR_SET_48 == ASR_SETTING)   
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x052F}, //Frequency L
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Htone_Bk_REL,0x07D8},    //Frequency H
#else    
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x0343}, //Frequency L
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Htone_Bk_REL,0x07D1},    //Frequency H
#endif    
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Vtone_Bk_REL,0x0DFE},
#if (ASR_SET_48 == ASR_SETTING)    
    {MEM_TYPE_X,ADSP_X_Tsq_T1_Bk_REL,0x000258}, // 200 ms  (bigger than TP)
#else  
    {MEM_TYPE_X,ADSP_X_Tsq_T1_Bk_REL,0x000227}, // 200 ms  (bigger than TP)
#endif
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Clip_Bk_REL,0x0080},
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Type_Bk_REL,0x0000},  //Sin... not triangle

    //No Need Other Slot... Because of Time...
    
    {MEM_TYPE_X,ADSP_X_Tsq_addmul_Bk_REL,0x000000},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c02_Bk_REL,0x0B24},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c1_Bk_REL,0x0FFF},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c3_Bk_REL,0x0FFF},
    {MEM_TYPE_Y,ADSP_Y_Tsq_Copied_REL,0x0800},
    //End Flag
    {MEM_INVALID,0,0},        
};

// Beep Type Tyre Alert: High Frequency  2KHZ
static const MEM_BUFFER_STRUCT Tab_WholeChimeTyre[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Tsq_SeqStat_Bk_REL,0x07FF},
#if (ASR_SET_48 == ASR_SETTING)   
    {MEM_TYPE_X,ADSP_X_Tsq_CrosFStp_Bk_REL,0x011111},
    {MEM_TYPE_X,ADSP_X_Tsq_ArLinStpA_Bk_REL,0x011111},
#else
    {MEM_TYPE_X,ADSP_X_Tsq_CrosFStp_Bk_REL,0x012937},
    {MEM_TYPE_X,ADSP_X_Tsq_ArLinStpA_Bk_REL,0x012937},
#endif    
    {MEM_TYPE_Y,ADSP_Y_Tsq_ArType_Bk_REL,0x0001},
#if (ASR_SET_48 == ASR_SETTING)  
    {MEM_TYPE_X,ADSP_X_Tsq_ArRelCoef_Bk_REL,0x7EF011},
    {MEM_TYPE_X,ADSP_X_Tsq_TA_Bk_REL,0x0001FE},// 170ms
    {MEM_TYPE_X,ADSP_X_Tsq_TB_Bk_REL,0x00005A},// 30ms
#else
    {MEM_TYPE_X,ADSP_X_Tsq_ArRelCoef_Bk_REL,0x7ED821},
    {MEM_TYPE_X,ADSP_X_Tsq_TA_Bk_REL,0x0001D5},// 170ms
    {MEM_TYPE_X,ADSP_X_Tsq_TB_Bk_REL,0x000053},// 30ms
#endif    
    {MEM_TYPE_X,ADSP_X_Tsq_repeate_Bk_REL,0x0002},    // 1 times
    
    {MEM_TYPE_X,ADSP_X_Tsq_ChangeThreshold_REL,0x4026E7},
    {MEM_TYPE_X,ADSP_X_Tsq_DecayThreshold_REL,0x000000},
    //{MEM_TYPE_Y,ADSP_Y_Tsq_ChimeVol_Bk_REL,0x03CA},  //Volume
    //Slot1
#if (ASR_SET_48 == ASR_SETTING)   
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x01BB}, //Frequency L
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Htone_Bk_REL,0x07BA},    //Frequency H
#else    
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Ltone_Bk_REL   ,0x0352}, //Frequency L
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1b1Htone_Bk_REL,0x07AD},    //Frequency H
#endif    
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Vtone_Bk_REL,0x0DFE},
#if (ASR_SET_48 == ASR_SETTING)    
    {MEM_TYPE_X,ADSP_X_Tsq_T1_Bk_REL,0x000258}, // 200 ms  (bigger than TP)
#else  
    {MEM_TYPE_X,ADSP_X_Tsq_T1_Bk_REL,0x000227}, // 200 ms  (bigger than TP)
#endif
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Clip_Bk_REL,0x0080},
    {MEM_TYPE_Y,ADSP_Y_Tsq_T1Type_Bk_REL,0x0000},  //Sin... not triangle

    //No Need Other Slot... Because of Time...
    
    {MEM_TYPE_X,ADSP_X_Tsq_addmul_Bk_REL,0x000000},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c02_Bk_REL,0x0B24},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c1_Bk_REL,0x0FFF},
    {MEM_TYPE_Y,ADSP_Y_Tsq_c3_Bk_REL,0x0FFF},
    {MEM_TYPE_Y,ADSP_Y_Tsq_Copied_REL,0x0800},
    //End Flag
    {MEM_INVALID,0,0},        
};

//Fast Beep Table
static const MEM_BUFFER_STRUCT Tab_FastChime[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Tsq_Copied_REL,0x0800},
    //End Flag
    {MEM_INVALID,0,0},        
};
// Beep Stop
static const MEM_BUFFER_STRUCT Tab_StopChime[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Tsq_SeqStat_REL,0x0000},
    {MEM_TYPE_X,ADSP_X_Tsq_repeate_REL,0x800000},
    //end flag
    {MEM_INVALID,    0,            0},    
};

//Loudness--Treble: BandPF
static const uint16_t Tab_Loudness_Treble[] =
{ 
#if (ASR_SET_48 == ASR_SETTING)     // Q = 1.0
    0x02E5,0x0EAA,0x0155,0x0000,0x0EAB,    // 7KHz
    0x00AE,0x0F54,0x01AA,0x0000,0x0E56,    // 10KHz
#else
    0x0357,0x0E84,0x0142,0x0000,0x0EBE,    // 7KHz
    0x0140,0x0F2A,0x0195,0x0000,0x0E6B,    // 10KHz
#endif    
};
//Loudness--Bass: 1st Shelving LPF
static const uint16_t Tab_Loudness_Bass[] =
{
#if (ASR_SET_48 == ASR_SETTING)     // Q = 1.0
    0x0282,0x03F9,0x0000,0x0000,0x057D,0x0006,0x0000,0x0000,     // 50Hz
    0x0459,0x03E5,0x0000,0x0000,0x03A6,0x001A,0x0000,0x0000,    // 200Hz
#else
    0x05D4,0x03F8,0x0000,0x0000,0x022B,0x0007,0x0000,0x0000,     // 50Hz
    0x01DD,0x03E3,0x0000,0x0000,0x0622,0x001C,0x0000,0x0000,   // 200Hz
#endif    
};
//Config
static const MEM_BUFFER_STRUCT Tab_Loudness_Config[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Loudf_MaxBstB_REL,0x04A0}, //Bass Max Bst  15DB     
    {MEM_TYPE_Y,ADSP_Y_Loudf_MaxBstT_REL,0x0453}, //Treble Max Bst 10DB
    //4 Attention !! These Settings related with Sample rate
    //{MEM_TYPE_Y,ADSP_Y_Loudf_OffsB_REL,0x0020},  //For Dynamic
    //{MEM_TYPE_Y,ADSP_Y_Loudf_OffsT_REL,0x0010}, //For Dynamic
    //{MEM_TYPE_Y,ADSP_Y_Loudf_KpBL_REL,0x02B6}, 
    //{MEM_TYPE_Y,ADSP_Y_Loudf_KpBH_REL,0x0809}, //For Dynamic
    //{MEM_TYPE_Y,ADSP_Y_Loudf_KmBL_REL,0x0273}, //For Dynamic
    //{MEM_TYPE_Y,ADSP_Y_Loudf_KmBH_REL,0x0012}, //For Dynamic
    //End Flag
    {MEM_INVALID,0,0},
};

//Subwoofer Create Table
static const MEM_BUFFER_STRUCT Tab_Create_StereoSw[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Vol_FLonSwL_REL,0x400},
    {MEM_TYPE_Y,ADSP_Y_Vol_FRonSwL_REL,0x000},
    {MEM_TYPE_Y,ADSP_Y_Vol_RLonSwL_REL,0x400},
    {MEM_TYPE_Y,ADSP_Y_Vol_RRonSwL_REL,0x000},
    {MEM_TYPE_Y,ADSP_Y_Vol_FLonSwR_REL,0x000},
    {MEM_TYPE_Y,ADSP_Y_Vol_FRonSwR_REL,0x400},
    {MEM_TYPE_Y,ADSP_Y_Vol_RLonSwR_REL,0x000},
    {MEM_TYPE_Y,ADSP_Y_Vol_RRonSwR_REL,0x400},
    //End Flag
    {MEM_INVALID,0,0},
};
static const MEM_BUFFER_STRUCT Tab_Create_MonoSw[] = 
{
    {MEM_TYPE_Y,ADSP_Y_Vol_FLonSwL_REL,0x400},
    {MEM_TYPE_Y,ADSP_Y_Vol_FRonSwL_REL,0x400},
    {MEM_TYPE_Y,ADSP_Y_Vol_RLonSwL_REL,0x000},
    {MEM_TYPE_Y,ADSP_Y_Vol_RRonSwL_REL,0x000},
    {MEM_TYPE_Y,ADSP_Y_Vol_FLonSwR_REL,0x200},
    {MEM_TYPE_Y,ADSP_Y_Vol_FRonSwR_REL,0x200},
    {MEM_TYPE_Y,ADSP_Y_Vol_RLonSwR_REL,0x200},
    {MEM_TYPE_Y,ADSP_Y_Vol_RRonSwR_REL,0x200},
    //End Flag
    {MEM_INVALID,0,0},
};
//Parametric Equalizer Table
static const uint16_t Tab_Peq_Band1_CF[4] =
{
    40,70,100,130,
};
static const uint16_t Tab_Peq_Band2_CF[4] =
{
    160,200,240,280,
};
static const uint16_t Tab_Peq_Band3_CF[4] =
{
    350,400,450,500,
};
static const uint16_t Tab_Peq_Band4_CF[4] =
{
    700,800,900,1000,
};
static const uint16_t Tab_Peq_Band5_CF[4] =
{
    1400,1600,1800,2000,
};
static const uint16_t Tab_Peq_Band6_CF[4] =
{
    2500,3000,3500,4000,
};
static const uint16_t Tab_Peq_Band7_CF[4] =
{
    4500,5000,5500,6000,
};
static const uint16_t Tab_Peq_Band8_CF[4] =
{
    6500,7000,7500,8000,
};
static const uint16_t Tab_Peq_Band9_CF[4] =
{
    8500,9000,9500,10000,
};
static const uint16_t Tab_Peq_Band10_CF[4] =
{
    10500,11000,11500,12000,
};
static const uint16_t Tab_Peq_Band11_CF[4] =
{
    12500,13000,13500,14000,
};


/* ========================= Code Part =================== */
/**********************************************************
 * @function    Dirana_Transmit
 * @brief      Start transmit specific datum to dirana
 * @param      uint8_t* Dat
 *                 uint8_t Num
 *            void* CallBack
 *            uint8_t Step
 * @retval     NULL
 **********************************************************/
void Dirana_Transmit(uint8_t* Dat,uint8_t Num,void* CallBack, uint8_t Step)
{
    uint8_t QueueResult = FALSE;

    sDirana.I2cResult = I2C_RET_WAIT;
    Memcpy_U8(Dat,sDirana.DrvBuffer,Num);
    QueueResult = Dirana_WritePdat(sDirana.DrvBuffer,Num,CallBack);
    if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
    {
        sDirana.DrvLayerStep = Step;
        sAudio.DrvOverTime = DiranaDelay(T120MS);
        sAudio.DrvDesertTime = DiranaDelay(T140MS);
    }
    else
    {    // Failed to Queue in IIC Buffer...
        //..
    }
}
/**********************************************************
 * @function    Dirana_ReadCommon
 * @brief      Read Datum From Dirana and Poll Result Into static Buffer
 * @param      DIRANA_DRIVER_TYPE_ENUM PID
 *                 uint8_t Num
 * @retval     Result of Execute
 **********************************************************/
uint8_t Dirana_ReadCommon(DIRANA_DRIVER_TYPE_ENUM PID,uint8_t Reg,uint8_t Num)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;  
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    
    //Check Driver Controller, If Not Busy, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sDirana.DrvLayerStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            sDirana.I2cResult = I2C_RET_WAIT;
            QueueResult = Dirana_ReadPdat(Reg,&(sDirana.ReadBuff[Reg]),Num,(void*)Dirana_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                sDirana.DrvLayerStep = OPERATION_1;
                sAudio.DrvOverTime = DiranaDelay(T120MS);
                sAudio.DrvDesertTime = DiranaDelay(T140MS);
            }
            else
            {    // Failed to Queue in IIC Buffer...
            //..
            }
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sDirana.I2cResult)
            {
                Result = SUBLAYER_ERROR;
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_WriteCommon
 * @brief      Write One Command to Dirana
 * @param      DIRANA_DRIVER_TYPE_ENUM PID
 *                 uint8_t* Dat
 *                 uint8_t Num
 * @retval     Result
 **********************************************************/
uint8_t Dirana_WriteCommon(DIRANA_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;   
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sDirana.DrvLayerStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            Dirana_Transmit(Dat,Num,(void*)Dirana_CallBack_Common,OPERATION_1);
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sDirana.I2cResult)
            {
                Result = SUBLAYER_ERROR;
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_WriteMemData
 * @brief      Write Low Level Cmd to Dirana
 * @param      DIRANA_DRIVER_TYPE_ENUM PID
 *            uint8_t MemType
 *            uint16_t Addr
 *            uint8_t Len
 *            int32_t* pData
 * @retval     Result
 **********************************************************/
uint8_t Dirana_WriteMemData(DIRANA_DRIVER_TYPE_ENUM PID,uint8_t MemType,uint16_t Addr,uint8_t Len,int32_t* pData)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[56];
    uint8_t ByteOrder;
    uint8_t Index;

    ByteOrder = 0;
    Buffer[ByteOrder++] = 0xF4;    //Low Level Register write
    
    switch(MemType)
    {
        //X Memory Command
        case MEM_TYPE_X:
        case MEM_TYPE_SX:    //SDSP X Memory    
            Buffer[ByteOrder++] = (uint8_t)((Addr & 0x00FF00) >> 8);// Memory location address MSB 
            Buffer[ByteOrder++] = (uint8_t)(Addr & 0x0000FF);        // Memory location address LSB 
            
            for(Index = 0;Index< Len;Index++)        //Fill send buffer
            {
                Buffer[ByteOrder++] = (uint8_t)((pData[Index] & 0xFF0000) >> 16);
                Buffer[ByteOrder++] = (uint8_t)((pData[Index] & 0x00FF00) >> 8);
                Buffer[ByteOrder++] = (uint8_t)(pData[Index] & 0x0000FF);
            }
            //S-DSP X Memory
            if(MEM_TYPE_SX == MemType)
            {
                Buffer[0] = 0xF3;
            }
            break;

        //Y Memory Command
        case MEM_TYPE_Y:
            Buffer[ByteOrder++] = 0x40 |(uint8_t)((Addr & 0x00FF00) >> 8);//Memory location address MSB
            Buffer[ByteOrder++] = (uint8_t)(Addr & 0x0000FF);//Memory location address LSB 

            for(Index = 0;Index < Len;Index++)
            {
                Buffer[ByteOrder++] = (uint8_t)((pData[Index] & 0xFF00) >> 8);
                Buffer[ByteOrder++] = (uint8_t)(pData[Index] & 0x00FF);
            }
            break;
            
        //P Memory Command    
        case MEM_TYPE_P: //Reserved for Dirana3
            break;
            
        default:
            ByteOrder = 0;
            break;
    }
#if 0 //Manually Controlled    
    if(0 == ByteOrder)
        return SUBLAYER_ERROR;    
#endif 
    Result = Dirana_WriteCommon(PrivateID, Buffer, ByteOrder);

    return (Result);
}
/**********************************************************
 * @function    Dirana_WriteMemWord
 * @brief      Write a word 
 * @param      DIRANA_DRIVER_TYPE_ENUM PID
 *            uint8_t MemType
 *            uint16_t Addr
 *            int32_t* pData                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_WriteMemWord(DIRANA_DRIVER_TYPE_ENUM PID, uint8_t MemType, uint16_t Addr, int32_t  Data)
{
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Dirana_WriteMemData(PID,MemType,Addr,1,&Data);

    return (Result);
}
/**********************************************************
 * @function    Dirana_WriteMemTab
 * @brief      Write a Memory table to Dirana
 *            const MEM_BUFFER_STRUCT *Tab
 * @param      DIRANA_DRIVER_TYPE_ENUM PID                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_WriteMemTab(DIRANA_DRIVER_TYPE_ENUM PID,const MEM_BUFFER_STRUCT *Tab)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    //Check WriteMemTab is in use....:Locked and DrvID different
    if((DRV_LOCKED == sDirana.DrvLock) && (PID != sDirana.LockID))
    {
        return (SUBLAYER_DOING);
    }
    
    if(MEM_INVALID != (Tab + sDirana.MemTblStep)->Type)
    {
        if(DRV_UNLOCK == sDirana.DrvLock)
        {
            sDirana.DrvLock = DRV_LOCKING; //Lock Drv Until Ends sending mem table
            sDirana.LockID = PID;
        }
        
        SubResult = Dirana_WriteMemWord(PID,(Tab + sDirana.MemTblStep)->Type,(Tab + sDirana.MemTblStep)->Addr,(Tab + sDirana.MemTblStep)->Data);
        if(SUBLAYER_DONE == SubResult)
        {
            sDirana.MemTblStep++;
        }
    }
    else
    {
        sDirana.DrvLock = DRV_UNLOCK; //Ends, Release Drv
        sDirana.MemTblStep = 0;
        Result = SUBLAYER_DONE;
    }

    //Error Occurs
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sDirana.DrvLock = DRV_UNLOCK; //Ends, Release Drv
        sDirana.MemTblStep = 0;
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_EasyProgrammWrite
 * @brief      EasyPrograme Write a Command
 * @param      DIRANA_DRIVER_TYPE_ENUM PID
 *            uint32_t Data
 * @retval     Result
 **********************************************************/
uint8_t Dirana_EasyProgrammWrite(DIRANA_DRIVER_TYPE_ENUM PID,uint16_t Data)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[6];
    
    Buffer[0] = 0xF4;
    Buffer[1] = 0x00;
    Buffer[2] = 0x93;
    Buffer[3] = 0x00; // Ignore high byte                 
    Buffer[4] = (uint8_t)((Data >> 8) & 0x00FF); 
    Buffer[5] = (uint8_t)(Data & 0x00FF);

    Result = Dirana_WriteCommon(PrivateID,Buffer,6);        

    return (Result);
}
/**********************************************************
 * @function    Dirana_ScratchDataWrite
 * @brief      Scratch Register Write
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_ScratchDataWrite(DIRANA_DRIVER_TYPE_ENUM PID,uint32_t Address,uint8_t DataLength,uint16_t* pData)
{
    uint8_t Result = SUBLAYER_DOING;
    DIRANA_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t byteOrder = 0, Index;
    uint8_t Buffer[56];
    uint8_t numOfBytes;
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    byteOrder = 0;
    
    if(DRV_UNLOCK == sDirana.DrvLock)
    {
        sDirana.DrvLock = DRV_LOCKED; //Lock Drv Until Scratch Write Ends
        sDirana.LockID = PID;
    }
    
    switch(sDirana.ScratchStep)
    {
        //Copy Coefficients To Scratchpad
        case OPERATION_0:
            Buffer[byteOrder++] = 0xF4;    //Address
            Buffer[byteOrder++] = (uint8_t)((ADSP_Y_UpdatC_Coeff0 & 0xFF00) >> 8);
            Buffer[byteOrder++] = (uint8_t)(ADSP_Y_UpdatC_Coeff0 & 0xFF);

            for(Index = 0; Index < DataLength; Index++)    // Datum
            {
                Buffer[byteOrder++] = (uint8_t)((pData[Index] & 0xFF00)>>8);
                Buffer[byteOrder++] = (uint8_t)(pData[Index] & 0xFF);
            }
            numOfBytes = byteOrder;
            sDirana.I2cResult = I2C_RET_WAIT;
            Memcpy_U8(Buffer,sDirana.DrvBuffer,numOfBytes);
            QueueResult = Dirana_WritePdat(sDirana.DrvBuffer,numOfBytes,(void*)Dirana_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                sDirana.ScratchStep = OPERATION_1;
                sAudio.DrvOverTime = DiranaDelay(T120MS);
                sAudio.DrvDesertTime = DiranaDelay(T140MS);
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //..
            }
            break;
            
        //Set Destination Address    
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Buffer[byteOrder++] = (uint8_t)(0xF4);
                Buffer[byteOrder++] = (uint8_t)((ADSP_X_SrcSw_OrDigSrcSelMask & 0xFF00) >> 8);
                Buffer[byteOrder++] = (uint8_t)(ADSP_X_SrcSw_OrDigSrcSelMask & 0xFF);
                Buffer[byteOrder++] = (uint8_t)((Address & 0xFF0000) >> 16);
                Buffer[byteOrder++] = (uint8_t)((Address & 0xFF00) >> 8);
                Buffer[byteOrder++] = (uint8_t)(Address & 0xFF);
                numOfBytes = byteOrder;
                sDirana.I2cResult = I2C_RET_WAIT;
                Memcpy_U8(Buffer,sDirana.DrvBuffer,numOfBytes);
                QueueResult = Dirana_WritePdat(sDirana.DrvBuffer,numOfBytes,(void*)Dirana_CallBack_Common);
                if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
                {
                    sDirana.ScratchStep = OPERATION_2;
                    sAudio.DrvOverTime = DiranaDelay(T120MS);
                    sAudio.DrvDesertTime = DiranaDelay(T140MS);
                }
                else
                {    // Failed to Queue in IIC Buffer...
                    //..
                }
            }
            break;

        //Load Easy Program to Write Scratch    
        case OPERATION_2:       
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Buffer[byteOrder++] = (uint8_t)(0xF4);
                Buffer[byteOrder++] = (uint8_t)((ADSP_X_EasyP_Index & 0xFF00) >> 8);
                Buffer[byteOrder++] = (uint8_t)(ADSP_X_EasyP_Index & 0xFF);
                Buffer[byteOrder++] = 0;
                Buffer[byteOrder++] = 0;
                Buffer[byteOrder++] = DataLength;
                numOfBytes = byteOrder;

                sDirana.I2cResult = I2C_RET_WAIT;
                Memcpy_U8(Buffer,sDirana.DrvBuffer,numOfBytes);
                QueueResult = Dirana_WritePdat(sDirana.DrvBuffer,numOfBytes,(void*)Dirana_CallBack_Common);
                if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
                {
                    sDirana.ScratchStep = OPERATION_3;
                    sAudio.DrvOverTime = DiranaDelay(T120MS);
                    sAudio.DrvDesertTime = DiranaDelay(T140MS);
                }
                else
                {    // Failed to Queue in IIC Buffer...
                    //..
                }
            }
            break;

        //End!
        case OPERATION_3:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                sDirana.DrvLock = DRV_UNLOCK; //Release Drv 
                sDirana.ScratchStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;
    }

    if(I2C_RET_ERR == sDirana.I2cResult)    
    {
        Result = SUBLAYER_ERROR;
        sDirana.ScratchStep = OPERATION_0;
        sDirana.DrvLock = DRV_UNLOCK; //Release Drv 
    }
    
    Dirana_ClearDrvState(Result);

    return (Result);
}
/**********************************************************
 * @function    Dirana3_Keycode
 * @brief      Load KeyCodes for Enhanced Functions
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Keycode(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_KEYCODE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[5];   
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;

    Buffer[0] = 0xE1;  //Subaddress
    Buffer[1] = 0x00;  //always 0 here
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (OPERATION_0 == sDirana.DrvLayerStep))
    {
        Buffer[2] = Tab_KeyCode[sDirana.DrvLayerStep][0]; //H
        Buffer[3] = Tab_KeyCode[sDirana.DrvLayerStep][1]; //M
        Buffer[4] = Tab_KeyCode[sDirana.DrvLayerStep][2]; //L
        
        if(0x00 == Tab_KeyCode[sDirana.DrvLayerStep + 1][0])
        {
            Dirana_Transmit(Buffer,5,(void*)Dirana_CallBack_Common,(sDirana.DrvLayerStep + 1));
        }
        else
        {
            Dirana_Transmit(Buffer,5,(void*)Dirana_Keycode,(sDirana.DrvLayerStep + 1));
        }
    }

    //Transmit Ends and Success
    if(I2C_RET_SUCCESS == sDirana.I2cResult) 
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_Patch1
 * @brief      Patch Update Step1
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Patch1(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_PATCH1;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[25];   
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    uint8_t Temp;

    Buffer[0] = 0xE1;  //Subaddress

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (OPERATION_0 == sDirana.DrvLayerStep))
    {
        for(Temp = 1; Temp < 25; Temp++)
        {
            Buffer[Temp] = Tab_D3_Patch1[sDirana.DrvLayerStep][Temp - 1]; 
        }

        if(0x09 == sDirana.DrvLayerStep)
        {
            Dirana_Transmit(Buffer,25,(void*)Dirana_CallBack_Common,(sDirana.DrvLayerStep + 1));
        }
        else
        {
            Dirana_Transmit(Buffer,25,(void*)Dirana_Patch1,(sDirana.DrvLayerStep + 1));
        }
    }

    //Transmit Ends and Success
    if(I2C_RET_SUCCESS == sDirana.I2cResult) 
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_Patch2
 * @brief      Patch Update 
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Patch2(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_PATCH2;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[17];   
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    uint8_t Temp;

    Buffer[0] = 0xEE;  //Subaddress

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (OPERATION_0 == sDirana.DrvLayerStep))
    {
        for(Temp = 1; Temp < 17; Temp++)
        {
            Buffer[Temp] = Tab_D3_Patch2[sDirana.DrvLayerStep][Temp - 1]; 
        }

        if(0x06 == sDirana.DrvLayerStep)
        {
            Dirana_Transmit(Buffer,17,(void*)Dirana_CallBack_Common,(sDirana.DrvLayerStep + 1));
        }
        else
        {
            Dirana_Transmit(Buffer,17,(void*)Dirana_Patch2,(sDirana.DrvLayerStep + 1));
        }
    }

    //Transmit Ends and Success
    if(I2C_RET_SUCCESS == sDirana.I2cResult) 
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_Patch3
 * @brief      Patch Update 
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Patch3(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_PATCH3;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[17];   
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    uint8_t Temp;

    Buffer[0] = 0xEE;  //Subaddress

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (OPERATION_0 == sDirana.DrvLayerStep))
    {
        for(Temp = 1; Temp < 17; Temp++)
        {
            Buffer[Temp] = Tab_D3_Patch3[sDirana.DrvLayerStep][Temp - 1]; 
        }

        if(0x04 == sDirana.DrvLayerStep)
        {
            Dirana_Transmit(Buffer,17,(void*)Dirana_CallBack_Common,(sDirana.DrvLayerStep + 1));
        }
        else
        {
            Dirana_Transmit(Buffer,17,(void*)Dirana_Patch3,(sDirana.DrvLayerStep + 1));
        }
    }

    //Transmit Ends and Success
    if(I2C_RET_SUCCESS == sDirana.I2cResult) 
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_Patch4
 * @brief      Patch Update
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Patch4(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_PATCH4;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[17];   
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    uint8_t Temp;

    Buffer[0] = 0xEE;  //Subaddress

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (OPERATION_0 == sDirana.DrvLayerStep))
    {
        for(Temp = 1; Temp < 17; Temp++)
        {
            Buffer[Temp] = Tab_D3_Patch4[sDirana.DrvLayerStep][Temp - 1]; 
        }

        if(54 == sDirana.DrvLayerStep)
        {
            Dirana_Transmit(Buffer,17,(void*)Dirana_CallBack_Common,(sDirana.DrvLayerStep + 1));
        }
        else
        {
            Dirana_Transmit(Buffer,17,(void*)Dirana_Patch4,(sDirana.DrvLayerStep + 1));
        }
    }

    //Transmit Ends and Success
    if(I2C_RET_SUCCESS == sDirana.I2cResult) 
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_ReqInit
 * @brief      Required Initialization
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_ReqInit(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_REQ_INIT;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[6];   
    uint8_t DrvState;
    uint8_t QueueResult = FALSE;
    uint8_t Temp;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (OPERATION_0 == sDirana.DrvLayerStep))
    {
        for(Temp = 0; Temp < 6; Temp++)
        {
            Buffer[Temp] = Tab_D3_ReqInit[sDirana.DrvLayerStep][Temp]; 
        }

        if(5 == sDirana.DrvLayerStep)
        {
            Dirana_Transmit(Buffer,6,(void*)Dirana_CallBack_Common,(sDirana.DrvLayerStep + 1));
        }
        else
        {
            Dirana_Transmit(Buffer,6,(void*)Dirana_ReqInit,(sDirana.DrvLayerStep + 1));
        }
    }

    //Transmit Ends and Success
    if(I2C_RET_SUCCESS == sDirana.I2cResult) 
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_BootPrepare
 * @brief      Prepare for Boot
 * @param      uint8_t Num:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_BootPrepare(uint8_t Num)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_PREPARE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[6];   
    uint8_t Temp;

    Buffer[0] = 0xEA;
    for(Temp = 0; Temp < 5; Temp++)
    {
        Buffer[Temp + 1] = Tab_D3_Index[Num][Temp];
    }

    Result = Dirana_WriteCommon(PrivateID,Buffer,6);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_ImagePatch
 * @brief      Boot Image or Load Patch
 *            Boot Image From External Flash or Load Image 
 * @param      Null                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_ImagePatch(void)
{
#if (DIRANA_BOOT_MODE == DIRANA_BOOT_FROM_FLASH)
    uint8_t PrivateID = DIRANA_IIC_IMAGE_PATCH;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult =SUBLAYER_DOING;
    uint8_t Buffer[4]; 

    Buffer[0] = 0xEB; 
    Buffer[2] = 0x00;    //Image Offset
    Buffer[3] = 0x00;    //APP NUM
    switch(sDirana.SubStep)
    {
        //Boot From Externnal Flash: Load BBP0
        case DIRANA_BOOT_BBP0:
            Buffer[1] = 0x00;  //CPU ID
            SubResult = Dirana_WriteCommon(PrivateID,Buffer,4);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.OverTime = DiranaDelay(T5S); //time for GPIO4 Detect overtime
                sDirana.BootStep = sDirana.SubStep;
                Dirana_SubGotoStep(DIRANA_BOOT_CHECK);
            }
            break;

        //Boot From Externnal Flash: Load BBP1
        case DIRANA_BOOT_BBP1:
            Buffer[1] = 0x01;  //CPU ID
            SubResult = Dirana_WriteCommon(PrivateID,Buffer,4);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.OverTime = DiranaDelay(T5S); //time for GPIO4 Detect overtime
                sDirana.BootStep = sDirana.SubStep;
                Dirana_SubGotoStep(DIRANA_BOOT_CHECK);
            }
            break;

        //Boot From Externnal Flash: Load BBP2
        case DIRANA_BOOT_BBP2:
            Buffer[1] = 0x02;  //CPU ID
            SubResult = Dirana_WriteCommon(PrivateID,Buffer,4);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.OverTime = DiranaDelay(T1S); //time for GPIO4 Detect overtime
                sDirana.BootStep = sDirana.SubStep;
                Dirana_SubGotoStep(DIRANA_BOOT_CHECK);
            }
            break;

        //Boot From Externnal Flash: Load ABB-SRC
        case DIRANA_BOOT_ABB0:
            Buffer[1] = 0x03;  //CPU ID
            SubResult = Dirana_WriteCommon(PrivateID,Buffer,4);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.OverTime = DiranaDelay(T1S); //time for GPIO4 Detect overtime
                sDirana.BootStep = sDirana.SubStep;
                Dirana_SubGotoStep(DIRANA_BOOT_CHECK);
            }
            break;

        //Boot From Externnal Flash: Load ABB-AUD
        case DIRANA_BOOT_ABB1:
            Buffer[1] = 0x04;  //CPU ID
            SubResult = Dirana_WriteCommon(PrivateID,Buffer,4);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.OverTime = DiranaDelay(T1S); //time for GPIO4 Detect overtime
                sDirana.BootStep = sDirana.SubStep;
                Dirana_SubGotoStep(DIRANA_BOOT_CHECK);
            }
            break;    

        //Boot From Externnal Flash: Load ARM UPPER
        case DIRANA_BOOT_ARM0:
            Buffer[1] = 0x46;  //CPU ID
            Buffer[2] = 0x0F;    //Image Offset
            SubResult = Dirana_WriteCommon(PrivateID,Buffer,4);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.OverTime = DiranaDelay(T1S); //time for GPIO4 Detect overtime
                sDirana.BootStep = sDirana.SubStep;
                Dirana_SubGotoStep(DIRANA_BOOT_CHECK);
            }
            break;    

        //Boot From Externnal Flash: Load ABB-LOWER
        case DIRANA_BOOT_ARM1:
            Buffer[1] = 0x06;  //CPU ID
            Buffer[3] = 0x01;    //APP NUM
            SubResult = Dirana_WriteCommon(PrivateID,Buffer,4);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.OverTime = DiranaDelay(T1S); //time for GPIO4 Detect overtime
                sDirana.BootStep = sDirana.SubStep;
                Dirana_SubGotoStep(DIRANA_BOOT_CHECK);
            }
            break;

        //Check GPIO4 and Delay
        case DIRANA_BOOT_CHECK:
            //Check GPIO4 State, ok when gpio4 become to high: Sign Module Idle
            if(OverTimeExpired(sDirana.OverTime))
            {
                //Error Occurs!, Feedback to System to Display somethingggggggg
                Result = SUBLAYER_ERROR;
            }
            if(VALID == (IO_Get(IO_IDX_D3_INIT_FLG,PIN_INPUT,FALSE)))
            {
                //after each boot from flash ,50ms is required
                sAudio.AspDelay = DiranaDelay(T50MS);
                if(sDirana.BootStep >= DIRANA_BOOT_ARM1)
                {
                    Dirana_SubGotoStep(DIRANA_BOOT_END);  //Goto Ends!
                }
                else
                {
                    Dirana_SubGotoStep(sDirana.BootStep + 1);    //Goto Boot Next Image
                }
            }
            break;

        //Boot Ends! All Done!
        case DIRANA_BOOT_END:
            sDirana.BootStep = 0;
            sDirana.SubStep = 0;
            Result = SUBLAYER_DONE;
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }
    
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SUBLAYER_ERROR;
        sDirana.BootStep = 0;
        sDirana.SubStep = 0;
    }

    return (Result);
#endif

#if (DIRANA_BOOT_MODE == DIRANA_BOOT_FROM_ROM)
    return (SUBLAYER_DONE);
#endif
}
/**********************************************************
 * @function    Dirana_StartApp
 * @brief      Start Application
 * @param      Null                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_StartApp(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_START_APP;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t Buffer;    
    
    switch(sDirana.SubStep)
    {
        //Send Start APP Command
        case OPERATION_0:    
            Buffer = 0xE8;  
            SubResult = Dirana_WriteCommon(PrivateID,&Buffer,1);
            if(SUBLAYER_DONE == SubResult)
            {
                //before any applications command ,60ms is required while booting from FLASH
                // 250ms is required while booting from rom
                sAudio.AspDelay = DiranaDelay(T60MS);
                sDirana.OverTime = DiranaDelay(T1S); //time for GPIO4 Detect overtime
                Dirana_SubGotoStep(OPERATION_1);
            }
            break;

        //Check GPIO4 
        case OPERATION_1: //Check GPIO4 State, ok when gpio4 become to high: Sign Module Idle
            if(OverTimeExpired(sDirana.OverTime))
            {
                //Error Occurs!, Feedback to System to Display somethingggggggg
            }
            if(VALID == (IO_Get(IO_IDX_D3_INIT_FLG,PIN_INPUT,FALSE)))
            {
                sDirana.SubStep = OPERATION_0; //Clear 
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    if(SubResult > SUBLAYER_DONE)
    {
        Result = SUBLAYER_ERROR;
        sDirana.SubStep = OPERATION_0; //Clear 
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);    
}
/**********************************************************
 * @function    Dirana3_Keycode
 * @brief      Load KeyCodes for Enhanced Functions
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Alignment(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_ALIGNMENT;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[5];  
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sDirana.DrvLayerStep)
    {
        //Am MW WB Level alignment
        case OPERATION_0:        //S 38  F1 40 6D 0F D4 P 
            Buffer[0] = 0xF1;
            Buffer[1] = 0x40;
            Buffer[2] = 0x6D; 
            Buffer[3] = 0x0F;
            Buffer[4] = 0xD4;
            Dirana_Transmit(Buffer,5,(void*)Dirana_Alignment,OPERATION_1);
            break;

        //Am MW WB Level alignment 
        case OPERATION_1:    //S 38  F0 40 43 0F D4 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF0;
                Buffer[1] = 0x40;
                Buffer[2] = 0x43; 
                Buffer[3] = 0x0F;
                Buffer[4] = 0xD4;
                Dirana_Transmit(Buffer,5,(void*)Dirana_Alignment,OPERATION_2);
            }
            break;

        //Am MW WB Level alignment 
        case OPERATION_2:        //S 38  F2 40 FE 0F D4 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF2;
                Buffer[1] = 0x40;
                Buffer[2] = 0xFE; 
                Buffer[3] = 0x0F;
                Buffer[4] = 0xD4;
                Dirana_Transmit(Buffer,5,(void*)Dirana_Alignment,OPERATION_3);
            }
            break;

        //Am MW WB Level alignment 
        case OPERATION_3:        //S 38  F1 42 7F 0F D4 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF1;
                Buffer[1] = 0x42;
                Buffer[2] = 0x7F; 
                Buffer[3] = 0x0F;
                Buffer[4] = 0xD4;
                Dirana_Transmit(Buffer,5,(void*)Dirana_Alignment,OPERATION_4);
            }
            break;

        //AM-lw level alignment: maybe not need     
        case OPERATION_4:    //S 38  F1 40 6C 0F D4 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF1;
                Buffer[1] = 0x40;
                Buffer[2] = 0x6C; 
                Buffer[3] = 0x0F;
                Buffer[4] = 0xD4;
                Dirana_Transmit(Buffer,5,(void*)Dirana_Alignment,OPERATION_5);
            }
            break;

        //AM-lw level alignment: maybe not need          
        case OPERATION_5:    //S 38  F0 40 45 0F D4 P     
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF0;
                Buffer[1] = 0x40;
                Buffer[2] = 0x45; 
                Buffer[3] = 0x0F;
                Buffer[4] = 0xD4;
                Dirana_Transmit(Buffer,5,(void*)Dirana_Alignment,OPERATION_6);
            }
            break;

        //AM-lw level alignment: maybe not need          
        case OPERATION_6:    //S 38  F2 41 00 0F D4 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF2;
                Buffer[1] = 0x41;
                Buffer[2] = 0x00; 
                Buffer[3] = 0x0F;
                Buffer[4] = 0xD4;
                Dirana_Transmit(Buffer,5,(void*)Dirana_Alignment,OPERATION_7);
            }
            break;    

        //AM-lw level alignment: maybe not need         
        case OPERATION_7:    //S 38  F1 42 7E 0F D4 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF1;
                Buffer[1] = 0x42;
                Buffer[2] = 0x7E; 
                Buffer[3] = 0x0F;
                Buffer[4] = 0xD4;
                Dirana_Transmit(Buffer,5,(void*)Dirana_CallBack_Common,OPERATION_8);
            }
            break;    

        // Check Result
        case OPERATION_8:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;    
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_StartPLL0
 * @brief      Start AD PLL0
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_StartPLL0(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_START_PLL0;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[9];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }    

    Buffer[0] = 0xFF;
    Buffer[1] = 0x20;
    Buffer[2] = 0x40; 
    Buffer[3] = 0x00;

    switch(sDirana.DrvLayerStep)
    {
        //disable drift comp
        case OPERATION_0:        //S 38  F0 40 15 07 FF P
            Buffer[0] = 0xF0;
            Buffer[1] = 0x40;
            Buffer[2] = 0x15; 
            Buffer[3] = 0x07;
            Buffer[4] = 0xFF;
            Dirana_Transmit(Buffer,5,(void *)Dirana_StartPLL0,OPERATION_1);
            break;

        //start ADPLL0
        case OPERATION_1:    // S 38  FF 20 40 00 5C 00 00 6D 31 P
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x5C;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00; 
                Buffer[7] = 0x6D;
                Buffer[8] = 0x31;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_2);
            }
            break;

        //start ADPLL0
        case OPERATION_2:        //S 38  FF 20 40 00 60 00 C9 00 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0xC9; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_3);
            }
            break;

        //start ADPLL0
        case OPERATION_3:        //S 38  FF 20 40 00 60 00 C9 40 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0xC9; 
                Buffer[7] = 0x40;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_4);
            }
            break;

        //start ADPLL0 
        case OPERATION_4:    //S 38  FF 20 40 00 5C 00 00 00 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x5C;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_5);
            }
            break;

        //start ADPLL0     
        case OPERATION_5:    //S 38  FF 20 40 00 60 00 96 00 01 P     
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x96; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_6);
            }
            break;

        //start ADPLL0     
        case OPERATION_6:    //S 38  FF 20 40 00 60 00 96 40 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x96; 
                Buffer[7] = 0x40;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_7);
            }
            break;    

        //start ADPLL0         
        case OPERATION_7:    //S 38  FF 20 40 00 5C 00 0A FC 80 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x5C;
                Buffer[5] = 0x00;
                Buffer[6] = 0x0A; 
                Buffer[7] = 0xFC;
                Buffer[8] = 0x80;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_8);
            }
            break;    

        //start ADPLL0    
        case OPERATION_8:    //S 38  FF 20 40 00 60 00 80 00 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x80; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_9);
            }
            break;    

        //start ADPLL0     
        case OPERATION_9:    // S 38  FF 20 40 00 60 00 80 40 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x80; 
                Buffer[7] = 0x40;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL0,OPERATION_10);
            }
            break;    

        //start ADPLL0     
        case OPERATION_10:    //S 38  FF 20 40 00 60 00 00 00 00 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x00;
                Dirana_Transmit(Buffer,9,(void *)Dirana_CallBack_Common,OPERATION_11);
            }
            break;        

        // Check Result
        case OPERATION_11:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;    
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_StartPLL1
 * @brief      Start AD PLL1  
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_StartPLL1(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_START_PLL1;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[9];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }
    
    Buffer[0] = 0xFF;
    Buffer[1] = 0x20;
    Buffer[2] = 0x40; 
    Buffer[3] = 0x10;

    switch(sDirana.DrvLayerStep)
    {
        //start ADPLL1
        case OPERATION_0:        //S 38  FF 20 40 10 5C 00 00 6D 31 P
            Buffer[4] = 0x5C;
            Buffer[5] = 0x00;
            Buffer[6] = 0x00; 
            Buffer[7] = 0x6D;
            Buffer[8] = 0x31;
            Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_1);
            break;

        //start ADPLL1 
        case OPERATION_1:    // S 38  FF 20 40 10 60 00 C9 00 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0xC9; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_2);
            }
            break;

        //start ADPLL1
        case OPERATION_2:        //S 38  FF 20 40 10 60 00 C9 40 01 P
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0xC9; 
                Buffer[7] = 0x40;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_3);
            }
            break;

        //start ADPLL1
        case OPERATION_3:        //S 38  FF 20 40 10 5C 00 00 00 01 P
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x5C;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_4);
            }
            break;

        //start ADPLL1
        case OPERATION_4:    //S 38  FF 20 40 10 60 00 96 00 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x96; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_5);
            }
            break;

        //start ADPLL1     
        case OPERATION_5:    //S 38  FF 20 40 10 60 00 96 40 01 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x96; 
                Buffer[7] = 0x40;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_6);
            }
            break;

        //start ADPLL1     
        case OPERATION_6:    //S 38  FF 20 40 10 5C 00 0A FC 80 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x5C;
                Buffer[5] = 0x00;
                Buffer[6] = 0x0A; 
                Buffer[7] = 0xFC;
                Buffer[8] = 0x80;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_7);
            }
            break;    

        //start ADPLL1     
        case OPERATION_7:    //S 38  FF 20 40 10 60 00 80 00 01 P  
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x80; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_8);
            }
            break;    

        //start ADPLL1     
        case OPERATION_8:    // S 38  FF 20 40 10 60 00 80 40 01 P
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x80; 
                Buffer[7] = 0x40;
                Buffer[8] = 0x01;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_9);
            }
            break;    

        //start ADPLL1     
        case OPERATION_9:    // S 38  FF 20 40 10 60 00 00 00 00 P
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[4] = 0x60;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x00;
                Dirana_Transmit(Buffer,9,(void *)Dirana_StartPLL1,OPERATION_10);
            }
            break;    

        //start ADPLL1    
        case OPERATION_10:    //S 38  F0 40 15 00 00 P
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xF0;
                Buffer[1] = 0x40;
                Buffer[2] = 0x15; 
                Buffer[3] = 0x00;
                Buffer[4] = 0x00;
                Dirana_Transmit(Buffer,5,(void *)Dirana_CallBack_Common,OPERATION_11);
            }
            break;        

        // Check Result
        case OPERATION_11:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;    
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_SpecialActiveP
 * @brief      Special init and active primary radio
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SpecialActiveP(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SPECIAL_P;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[9];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sDirana.DrvLayerStep)
    {
        //I dont know ...
        case OPERATION_0:        //S 38  FF 00 19 4D 60 00 00 00 00 P 
            Buffer[0] = 0xFF;
            Buffer[1] = 0x00;
            Buffer[2] = 0x19; 
            Buffer[3] = 0x4D;
            Buffer[4] = 0x60;
            Buffer[5] = 0x00;
            Buffer[6] = 0x00; 
            Buffer[7] = 0x00;
            Buffer[8] = 0x00;
            Dirana_Transmit(Buffer,9,(void *)Dirana_SpecialActiveP,OPERATION_1);
            break;

        //Enable TMC Clock Output
        case OPERATION_1:    // S 38  C9 03 01 P     
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xC9;
                Buffer[1] = 0x03;
                Buffer[2] = 0x01; 
                Dirana_Transmit(Buffer,3,(void *)Dirana_SpecialActiveP,OPERATION_2);
            }
            break;
            
        //Enable Antenna Buffer Output
        case OPERATION_2:    // S 38  C9 05 02 P     
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xC9;
                Buffer[1] = 0x05;
                Buffer[2] = 0x02; 
                Dirana_Transmit(Buffer,3,(void *)Dirana_SpecialActiveP,OPERATION_3);
            }
            break;

        //Fm whistle avoidance setting: Enable 104.0 suppression
        case OPERATION_3:    // S 38  C9 06 00 P     
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xC9;
                Buffer[1] = 0x06;
                Buffer[2] = 0x00; 
                Dirana_Transmit(Buffer,3,(void *)Dirana_SpecialActiveP,OPERATION_4);
            }
            break;

        //Set the IF Frequency via the ARM to: -300 kHz.
        case OPERATION_4:    //S 38  FF 00 19 4D B8 FF FF FE D4 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;
                Buffer[1] = 0x00;
                Buffer[2] = 0x19; 
                Buffer[3] = 0x4D;
                Buffer[4] = 0xB8;
                Buffer[5] = 0xFF;
                Buffer[6] = 0xFF; 
                Buffer[7] = 0xFE;
                Buffer[8] = 0xD4;
                Dirana_Transmit(Buffer,9,(void *)Dirana_SpecialActiveP,OPERATION_5);
            }
            break;

        //Active Primary Radio
        case OPERATION_5:    
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0x00;
                Buffer[1] = (DIRANA_BAND_FM + DIRANA_MODE_SEARCH);
                //TUNER_CURRENT_FREQ
                Buffer[2] =  ((8750 >> 8) & 0x00FF);
                Buffer[3] = (8750  & 0xFF);
                Dirana_Transmit(Buffer,4,(void *)Dirana_SpecialActiveP,OPERATION_6);
            }
            break;    

        //i have no idea about this
        case OPERATION_6:    //S 38  FF 20 40 01 00 00 00 00 04 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;
                Buffer[1] = 0x20;
                Buffer[2] = 0x40; 
                Buffer[3] = 0x01;
                Buffer[4] = 0x00;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x04;
                Dirana_Transmit(Buffer,9,(void *)Dirana_CallBack_Common,OPERATION_7);
            }
            break;
            
        // Check Result
        case OPERATION_7:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;    
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_InitRadio
 * @brief      Initialize Radio: ICC weak control
 * @param      uint8_t Type                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_InitRadio(uint8_t Type)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_RADIO;
    uint8_t Result = SUBLAYER_DOING;   
    uint8_t IIcDataBuff[29];

    if(P_RADIO == Type)
    {
        IIcDataBuff[0] = 0x03;    //Primary Radio
    }
    else if(S_RADIO)
    {
        IIcDataBuff[0] = 0x63;    //Secondary Radio
    }
        
    IIcDataBuff[1] = DIRANA_TUNER;
    IIcDataBuff[2] = DIRANA_OPT; 
    IIcDataBuff[3] = DIRANA_RADIO;
    IIcDataBuff[4] = DIRANA_SIGNAL;

    IIcDataBuff[5] = DIRANA_BWCTRL;
    IIcDataBuff[6] = DIRANA_SPECIAL;
    IIcDataBuff[7] = DIRANA_RDS;
    IIcDataBuff[8] = 0;
    IIcDataBuff[9] = 0;
    IIcDataBuff[10] = DIRANA_LEV_OFFSET;
    //Softmute 
    IIcDataBuff[11] = DIRANA_SM_TIME;
    IIcDataBuff[12] = DIRANA_SM_DET;
    IIcDataBuff[13] = DIRANA_SM_LEV; 
    IIcDataBuff[14] = DIRANA_SM_NM;
    IIcDataBuff[15] = DIRANA_SM_LIM; 
    //high cut
    IIcDataBuff[16] = DIRANA_HC_TIME;
    IIcDataBuff[17] = DIRANA_HC_DET;
    IIcDataBuff[18] = DIRANA_HC_LEV;
    IIcDataBuff[19] = DIRANA_HC_NM;
    IIcDataBuff[20] = DIRANA_HC_LIM;
    IIcDataBuff[21] = DIRANA_HC_LOC;
    //stereo
    IIcDataBuff[22] = DIRANA_ST_TIME;
    IIcDataBuff[23] = DIRANA_ST_DET;
    IIcDataBuff[24] = DIRANA_ST_LEV;
    IIcDataBuff[25] = DIRANA_ST_NM;
    IIcDataBuff[26] = DIRANA_ST_LIM;
    IIcDataBuff[27] = DIRANA_STHB_DET;
    IIcDataBuff[28] = DIRANA_STHB_LNM;

    if(TUNER_BAND_AM)  
    {
        IIcDataBuff[1] = 0x0A;
  #if 0
        if((sAudioDat.sBasicBK.DefaultMediaVolume > 20) &&
            (sAudioDat.sBasicBK.DefaultMediaVolume < 28))
        {
           IIcDataBuff[2] = (0x04 | 0x80 | ((sAudioDat.sBasicBK.DefaultMediaVolume - 20) << 4));
        }
  #else
        IIcDataBuff[2] = 0x04;   //ANT Passive , ATT 0db
  #endif
        IIcDataBuff[4] = 0x0A;
        IIcDataBuff[11] = 0x65;
        IIcDataBuff[13] = 0x20;
        IIcDataBuff[15] = 0x04;
        IIcDataBuff[16] = 0x12;
        IIcDataBuff[18] = 0x5B;
        IIcDataBuff[21] = 0x05;
    }

    Result = Dirana_WriteCommon(PrivateID,IIcDataBuff,29);

    return(Result);
}
/**********************************************************
 * @function    Dirana_SpecialActiveS
 * @brief      Special init and active secondary radio
 * @param      uint8_t eState:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SpecialActiveS(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SPECIAL_S;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[9];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }
    
    switch(sDirana.DrvLayerStep)
    {
        //Set the IF Frequency via the ARM to: -300 kHz.
        case OPERATION_0:        //S 38  FF 00 19 4D BC FF FF FE D4 P 
            Buffer[0] = 0xFF;
            Buffer[1] = 0x00;
            Buffer[2] = 0x19; 
            Buffer[3] = 0x4D;
            Buffer[4] = 0xBC;
            Buffer[5] = 0xFF;
            Buffer[6] = 0xFF; 
            Buffer[7] = 0xFE;
            Buffer[8] = 0xD4;
            Dirana_Transmit(Buffer,9,(void *)Dirana_SpecialActiveS,OPERATION_1);
            break;

        //Active Secondary Radio
        case OPERATION_1:    
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0x60;
                Buffer[1] = (DIRANA_BAND_FM + DIRANA_MODE_SEARCH);
                Buffer[2] =  ((8750 >> 8) & 0x00FF);
                Buffer[3] = (8750 & 0xFF);
                Dirana_Transmit(Buffer,4,(void *)Dirana_SpecialActiveS,OPERATION_2);
            }
            break;    

        //i have no idea about this
        case OPERATION_2:    //S 38  FF 20 40 11 00 00 00 00 04 P 
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[0] = 0xFF;
                Buffer[1] = 0x20;
                Buffer[2] = 0x40; 
                Buffer[3] = 0x11;
                Buffer[4] = 0x00;
                Buffer[5] = 0x00;
                Buffer[6] = 0x00; 
                Buffer[7] = 0x00;
                Buffer[8] = 0x04;
                Dirana_Transmit(Buffer,9,(void *)Dirana_CallBack_Common,OPERATION_3);
            }
            break;
            
        // Check Result
        case OPERATION_3:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;    
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_Enable_SRC
 * @brief      Enable Sample Rate Converter
 * @param      NULL                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Enable_SRC(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_ENABLE_SRC;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Dirana_WriteMemTab(PrivateID,Tab_SampleRC);

    return (Result);
}
/**********************************************************
 * @function    Dirana_Set_SampleRate
 * @brief      Set Audio Sample rate
 * @param    uint8_t SampleRate                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Set_SampleRate(uint8_t SampleRate)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_ASR;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[2]; 

    Buffer[0] = 0x3F; 
    if(ASR_SET_44 == SampleRate)
    {
        Buffer[1] = 0xC0;    //Audio Power On and AudioSample Rate to 44.1K
    }
    else
    {
        Buffer[1] = 0xC1;    //
    }
    Result = Dirana_WriteCommon(PrivateID,Buffer,2);

    return (Result);
}
/**********************************************************
 * @function    Dirana_GpioConnect
 * @brief      Config Gpio Feature
 * @param      uint8_t eState                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GpioConnect(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_PERIPHERAL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[4];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    Buffer[0] = 0xC0;  //subaddr of the GPIO config

    switch(sDirana.DrvLayerStep)
    {
        //Config:Rds Gpio
        case OPERATION_0:        
            Buffer[1] = DIRANA_GPIO_0;
            Buffer[2] = (uint8_t)(GPIO_FUNID_P_RDSINT >> 8);
            Buffer[3] = (uint8_t)(GPIO_FUNID_P_RDSINT & 0x00FF);
            Dirana_Transmit(Buffer,4,(void *)Dirana_GpioConnect,OPERATION_1);
            break;

        //Config Fast Mute Gpio
        case OPERATION_1:
            if(I2C_RET_SUCCESS == eState)
            {
                Buffer[1] = DIRANA_GPIO_1;
                Buffer[2] = (uint8_t)(GPIO_FUNID_FASTMUTE >> 8);
                Buffer[3] = (uint8_t)(GPIO_FUNID_FASTMUTE & 0x00FF);
                Dirana_Transmit(Buffer,4,(void *)Dirana_CallBack_Common,OPERATION_2);
            }
            break;

        //Config Click Clack Gpio
        case OPERATION_2:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }
    
    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_InitPeripheral
 * @brief      Initialize Peripheral
 * @param      uint8_t eState                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_InitPeripheral(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_PERIPHERAL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[3];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }
    
    Buffer[0] = 0xA9;

    //Start Transmit or Transmit Next
    if((I2C_RET_SUCCESS == eState) || (0x00 == sDirana.DrvLayerStep))
    {
        Buffer[1] = Tab_InOutInit[sDirana.DrvLayerStep][0]; //ID
        Buffer[2] = Tab_InOutInit[sDirana.DrvLayerStep][1]; //Config
        
        if(0x00 == Tab_InOutInit[sDirana.DrvLayerStep + 1][0])
        {
            Dirana_Transmit(Buffer,3,(void *)Dirana_CallBack_Common,(sDirana.DrvLayerStep + 1));
        }
        else
        {
            Dirana_Transmit(Buffer,3,(void *)Dirana_InitPeripheral,(sDirana.DrvLayerStep + 1));
        }
    }

    if(I2C_RET_SUCCESS == sDirana.I2cResult)
    {
        Result = SUBLAYER_DONE;
    }

    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);

    return (Result);
}
#if 0// Directly Set HostIIS when Initialize Peripheral
/**********************************************************
 * @function    Dirana_ConfigHostIIS
 * @brief      Config Host IIS Mode
 * @param      uint8_t eState                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_ConfigHostIIS(uint8_t eState)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_CONFIG_HOST;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[4];   
    uint8_t DrvState;

    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Dirana_CheckDrvState(PrivateID);
    if(DIRANA_DRV_BUSY == DrvState)  // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(DIRANA_DRV_ERROR == DrvState) //TimeOut Error Occurs..
    {
        return (SUBLAYER_ERROR);
    }

    switch(sDirana.DrvLayerStep)
    {
        //Config HostB: Set to Synchronous 
        case OPERATION_0:        
            Buffer[0] = 0xA9;    // Here Reset
            Buffer[1] = 0x36; 
            Buffer[2] = 0x00;
            Dirana_Transmit(Buffer,3,(void *)Dirana_CallBack_Common,OPERATION_1);
            break;
#if 0            
        //Config HostB: Set to Slave
        case OPERATION_1:    // S 38  FF 20 40 00 5C 00 00 6D 31 P
            if(I2C_RET_SUCCESS == eState)                
            {
                Buffer[0] = 0xA8;
                Buffer[1] = 0x03; 
                Dirana_Transmit(Buffer,2,(void *)Dirana_CallBack_Common,OPERATION_1);
            }
            break;
#endif
        //Reserved for HoastA    
        
        // Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                Result = SUBLAYER_DONE;
            }
            break;
            
        default:
            Result = SUBLAYER_ERROR;
            break;
    }
    
    //Error Occured
    if((I2C_RET_ERR == eState) || (I2C_RET_ERR == sDirana.I2cResult))
    {
        Result = SUBLAYER_ERROR;
    }

    Dirana_ClearDrvState(Result);
    
    return (Result);
}
#endif
/**********************************************************
 * @function    Dirana_SetCrossOver
 * @brief      Set CrossOver
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Deemphasis(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_DE_EMPHASIS;
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_WriteMemTab(PrivateID,Tab_DeEmphasis);

    return (Result);    
}
/**********************************************************
 * @function    Dirana_AudioPointer
 * @brief      Set Audio Pointer Connections
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_AudioPointer(void)
{    
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_AUDIO_POINTER;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Dirana_WriteMemTab(PrivateID,Tab_AudioPointer);

    return (Result);
}
/**********************************************************
 * @function    Dirana_ScalingInit
 * @brief      Initial Scaling Setting
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_ScalingInit(void)
{    
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_SCALING;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Dirana_WriteMemTab(PrivateID,Tab_ScalingInit);//write scaling data to Dirana

    return (Result);
}
/**********************************************************
 * @function    Dirana_DrvSetVol
 * @brief      Driver Set Volume of Dirana
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvSetVol(uint8_t Volume, uint8_t Type)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_VOL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    int32_t Volume_Data01,Volume_Data02;
    uint16_t Addr,Addr1;
    int8_t VoldB;
    uint8_t Temp;

    VoldB = Tab_VolDbLev[Volume];    
    VoldB -= sAudioDat.sInfo.VolCurveDelta; //Temporary .....
    
    switch(Type)
    {
        case SYSTEM_FRONT:    //System Front
            Addr = ADSP_Y_Vol_Main1P_REL;
            break;

        case SYSTEM_REAR1: //System Rear 1
            Addr = ADSP_Y_Vol_Main1S_REL;
            break;

        case SYSTEM_REAR2: //System Rear 2
            Addr = ADSP_Y_Vol_Main2S_REL;
            break;

        case SYSTEM_REAR: //System All Rear
            Addr = ADSP_Y_Vol_Main1S_REL;
            Addr1 = ADSP_Y_Vol_Main2S_REL;
            break;    

        case SYSTEM_ALL:  //System All Front and Rear
            Addr = ADSP_Y_Vol_Main1P_REL;
            Addr1 = ADSP_Y_Vol_Main1S_REL;
            break;
    }

    if (VoldB >= 0)
    {
        Volume_Data01 = 0x07FFUL;/* ~ +1 */
        Volume_Data02 = Tab_Db2Lin[VolMaxP - VoldB];
    }
    else if (VoldB >= -LoudBoostMaxP)
    {
        Volume_Data01 = Tab_Db2Lin[-VoldB];
        Volume_Data02 = Tab_Db2Lin[VolMaxP];
    }
    else if (VoldB >= (VolMaxP - LoudBoostMaxP - FixedBoostP))
    {
        Volume_Data01 = Tab_Db2Lin[LoudBoostMaxP];
        Volume_Data02 = Tab_Db2Lin[VolMaxP - LoudBoostMaxP - VoldB];
    }
    else 
    {
        Volume_Data01 = Tab_Db2Lin[VolMaxP - VoldB - FixedBoostP];/* 48 = 20 log 256 */
        Volume_Data02 = 0x008UL;/* = 1/256 */
    }

    switch(sAudio.DrvVolStep)
    {
        //First Main1 for Primary/Secondary/2nd Secondary 
        case OPERATION_0:
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,Addr,Volume_Data01); //the primary volume will be divided to 2 prara
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_1;
            }
            break;

        //First Main2 for Primary/Secondary/2nd Secondary 
        case OPERATION_1:
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,(Addr+1),Volume_Data02);//the primary volume will be divided to 2 prara
            if(SUBLAYER_DONE == SubResult)
            {    
                if(Type >= SYSTEM_REAR)    //All rear or All system
                {
                    sAudio.DrvVolStep = OPERATION_2;
                }
                else
                {    //Finished Volume set, go to end
                    sAudio.DrvVolStep = OPERATION_6;
                }
            }
            break;

        //Next Main1 for Secondary/2nd Secondary     
        case OPERATION_2:
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,Addr1,Volume_Data01); //the primary volume will be divided to 2 prara
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_3;
            }
            break;

        //Next Main2 for Secondary/2nd Secondary         
        case OPERATION_3:
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,(Addr1+1),Volume_Data02);//the primary volume will be divided to 2 prara
            if(SUBLAYER_DONE == SubResult)
            {
                if(Type == SYSTEM_ALL)
                {
                    sAudio.DrvVolStep = OPERATION_4;
                }
                else
                {    //Finished Volume set, go to end
                    sAudio.DrvVolStep = OPERATION_6;
                }
                
            }
            break;

        //Third Main1 for 2nd Secondary 
        case OPERATION_4:
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_Main2S_REL,Volume_Data01); 
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_5;
            }
            break;

        //Third Main2 for 2nd Secondary 
        case OPERATION_5:
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_Main2S2_REL,Volume_Data02); 
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_6;
            }
            break;    
            
        //Loudness:Bass Boost
        case OPERATION_6:    //Loudness Boost Set!!
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
                        Volume_Data01 = (int32_t)Dirana_Calc_LoudBoost(0,Temp);    
                    }
                }
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Loudf_StatLev_REL,Volume_Data01);
                if(SUBLAYER_DONE == SubResult)
                {
                 #ifdef D_AUDIO_ENABLE_LDT   
                    sAudio.DrvVolStep = OPERATION_7;
                 #else
                    sAudio.DrvVolStep = OPERATION_0; //Clear 
                    Result = SUBLAYER_DONE;
                 #endif//D_AUDIO_ENABLE_LDT
                }
            }
            else
            {
                sAudio.DrvVolStep = OPERATION_0; //Clear 
                Result = SUBLAYER_DONE;
            }
            break;
    #ifdef D_AUDIO_ENABLE_LDT 
        //Loudness:Treble Boost
        case OPERATION_7:
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
                    Volume_Data01 = (int32_t)Dirana_Calc_LoudBoost(1,Temp);    
                }
            }
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Loudf_StatLevT_REL,Volume_Data01);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvVolStep = OPERATION_0; //Clear 
                Result = SUBLAYER_DONE;
            }
            break;
       #endif//D_AUDIO_ENABLE_LDT      
    }

    if(SubResult > SUBLAYER_DONE) //Error Occurs...
    {
        Result = SubResult;
        sAudio.DrvVolStep = OPERATION_0; 
    }
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_InitChannelGain
 * @brief      Initialize Channel Gain
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_InitChannelGain(void)
{    
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_CHANNEL_GAIN;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Dirana_WriteMemTab(PrivateID,Tab_ChanGain);

    return (Result);
}
/**********************************************************
 * @function    Dirana_InitChannelGain
 * @brief      Initialize Channel Gain
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetChannelGain(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_CHANNEL_GAIN;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;    
    uint16_t Addr;
    int32_t Data;

    switch(sAudio.ChanGainCtl)
    {
        case CHANGAIN_CTL_FL: //Set Primary Front Left Channel
            if(sAudio.ChanGainMask & CHANGAIN_MASK_FL)
            {
                Data = Tab_Db2Lin[ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_FL]];
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_ChanGainPFL_REL,Data); 
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
                Data = Tab_Db2Lin[ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_FR]];
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_ChanGainPFR_REL,Data); 
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
                Data = Tab_Db2Lin[ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_RL]];
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_ChanGainPRL_REL,Data); 
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
                Data = Tab_Db2Lin[ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_RR]];
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_ChanGainPRR_REL,Data); 
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
                Data = Tab_Db2Lin[ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_SWL]];
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_ChanGainSwL_REL,Data); 
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
                Data = Tab_Db2Lin[ChanGainMaxP - sAudioDat.sGain.ChanGainTbl[CHANNEL_SWR]];
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_ChanGainSwR_REL,Data); 
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
 * @function    Dirana_SrcScalingInit
 * @brief      Initialize source scaling settings...
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SrcScalingInit(void)
{    
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SRC_SCALING;
    uint8_t Result = SUBLAYER_DOING;
    
    Result = Dirana_WriteMemTab(PrivateID,Tab_SrcScaling);

    return (Result);
}
/**********************************************************
 * @function    Dirana_SetSrcScaler
 * @brief      Initialize source scaling settings...
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetSrcScaler(uint8_t Type, uint8_t Val)
{    
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SRC_SCALING;
    uint8_t Result = SUBLAYER_DOING;
    uint16_t Addr;
    int32_t Data;
    
    if(SYSTEM_FRONT == Type)    
    {
        if(AUDIO_6CH_MODE == sAudio.SysChanMode)
        {
            Addr = ADSP_Y_Vol_SrcScalP6_REL;
        }
        else
        {
            Addr = ADSP_Y_Vol_SrcScalP_REL;  
        }
    }
    else if(SYSTEM_REAR == Type)
    {
        Addr = ADSP_Y_Vol_SrcScalS_REL;    
    }
    
    Data = Tab_Db2Lin[12 - Val];
    
    Result = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,Addr,Data); //the primary volume will be divided to 2 prara

    return (Result);
}
/**********************************************************
 * @function    Dirana_SoftMute
 * @brief      Driver Softmute
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SoftMute(uint16_t Channel,uint8_t MuteData)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SOFTMUTE;
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
                if(Channel & DIRANA_CH_P)        
                {
                    Action = 1;
                    Addr = ADSP_Y_Mute_P_REL;
                }
                break;

            //Overall Secondary Channel    
            case OPERATION_1:
                if(Channel & DIRANA_CH_S)        
                {
                    Action = 1;
                    Addr = ADSP_Y_Mute_S_REL;
                }
                break;

            //Overall Navigation Channel    
            case OPERATION_2:
                if(Channel & DIRANA_CH_NAV)        
                {
                    Action = 1;
                    Addr = ADSP_Y_Mute_N_REL;
                }
                break;

            //Overall Phone Channel
            case OPERATION_3:
                if(Channel & DIRANA_CH_PHONE)        
                {
                    Action = 1;
                    Addr = ADSP_Y_Mute_T_REL;
                }
                break;    
        
            //Primary Front Left Channel
            case OPERATION_4:
                if(Channel & DIRANA_CH_PFL)        
                {
                    Action = 1;
                    Addr = ADSP_Y_MuteSix_FL_REL;
                }
                break;
                
            //Primary Front Right Channel    
            case OPERATION_5:    
                if(Channel & DIRANA_CH_PFR)        
                {
                    Action = 1;    
                    Addr = ADSP_Y_MuteSix_FR_REL;
                }
                break;
                
            //Primary Rear Left Channel    
            case OPERATION_6:
                if(Channel & DIRANA_CH_PRL)        
                {
                    Action = 1;    
                    Addr = ADSP_Y_MuteSix_RL_REL;
                }
                break;
                
            //Primary Rear Right Channel    
            case OPERATION_7:    
                if(Channel & DIRANA_CH_PRR)        
                {
                    Action = 7;
                    Addr = ADSP_Y_MuteSix_RR_REL;
                }
                break;
                
            //Subwoofer Left channel    
            case OPERATION_8:
                if(Channel & DIRANA_CH_SWL)        
                {
                    Action = 1;
                    Addr = ADSP_Y_MuteSix_SwL_REL;
                }
                break;
                
            //Subwoofer Right channel    
            case OPERATION_9:
                if(Channel & DIRANA_CH_SWR)        
                {
                    Action = 1;
                    Addr = ADSP_Y_MuteSix_SwR_REL;
                }
                break;

            default:
                sAudio.SoftMuteStep = OPERATION_0;
                break;
        }

        if(1 == Action)
        {    
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,Addr,Dat);
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
            sAudio.SoftMuteStep = OPERATION_0;
            Result = SUBLAYER_DONE;
            break;
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_DrvSetInput
 * @brief      Select input for  Channel 
 * @param      uint8_t Stream
 *            uint8_t Input
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvSetInput(uint8_t Stream,uint8_t Input)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID =  DIRANA_IIC_SET_INPUT;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buff[3];
    uint8_t Num = 0;

    switch(Stream)
    {
        case STREAM_PRIMARY:
            Buff[0] = 0x20;
            Num = 1;
            break;

        case STREAM_SECONDARY:
            Buff[0] = 0x28;
            Num = 1;
            break;

        case STREAM_2SECONDARY:
            Buff[0] = 0x40;
            Num = 1;
            break;

        case STREAM_NAVI:
            Buff[0] = 0xAC;
            Buff[1] = 0x00;
            Num = 2;
            break;

        case STREAM_PHONE:
            Buff[0] = 0xAC;
            Buff[1] = 0x01;
            Num = 2;
            break;
    }

    Buff[Num] = Input;     

    Result = Dirana_WriteCommon(PrivateID, Buff,(Num + 1));

    return (Result);
}
/**********************************************************
 * @function    Dirana_SourceInputSel
 * @brief      Select a Newly Ain Source and Set Input Setting
 * @param      uint8_t stream
 *            uint8_t Input    
 *            uint8_t Mode
 *            double Scal
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SourceInputSel(uint8_t Stream,uint8_t Input,uint8_t Mode,float64_t Scal)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sAudio.SrcInputSelStep)
    {
        //Select Stream's Input
        case OPERATION_0:
            SubResult = Dirana_DrvSetInput(Stream,Input);
            if(SUBLAYER_DONE == SubResult)
            {
                if(STREAM_PRIMARY == Stream) 
                {
                    if(AUDIO_2CH_MODE == sAudio.SysChanMode)
                    {
                        if(0x80 & Input) //Switch to a 6 CH
                        {                       //goto mode switch
                            sAudio.SrcInputSelStep = OPERATION_1;
                            break;
                        }
                    }
                    else if(AUDIO_6CH_MODE == sAudio.SysChanMode)  
                    {
                        if(0x00 == (0x80 & Input))
                        {                       //Switch to 2 CH
                            sAudio.SrcInputSelStep = OPERATION_5;
                            break;
                        }
                    }
                }
                sAudio.SrcInputSelStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        //Switch to 6 CH: Step1 Switch Audio Pointer
        case OPERATION_1:
            
            break;

        //Switch to 6 CH: Step2...
       case OPERATION_2:
            break;

        //Switch to 6 CH:Step3...
        case OPERATION_3:

            break;

        default:
            sAudio.SrcInputSelStep = OPERATION_0;
            Result = SUBLAYER_ERROR;
            break;
    }

    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;    
        sAudio.SrcInputSelStep = OPERATION_0;
    }
    
    return (Result);    
}
/**********************************************************
 * @function    Dirana_UpdatePll
 * @brief      Update PLL: Mode Band Frequency~~
 * @param                      
 * @retval     Result
 **********************************************************/
uint8_t Dirana_UpdatePll(uint8_t Type,uint8_t Mode, uint8_t Band, uint16_t Freq)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_UPDATE_PLL;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[4];   

    if(P_RADIO == Type)    //Primary Radio
    {
        Buffer[0] = 0x00;
    }
    else if(S_RADIO == Type)    //Secondary Radio
    {
        Buffer[0] = 0x60;
    }
    
    Buffer[1] = (Band +Mode);
    Buffer[2] =  ((Freq >> 8) & 0x00FF);
    Buffer[3] = (Freq & 0xFF);
    
    Result = Dirana_WriteCommon(PrivateID,Buffer,4);
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_DrvSuperPositionGain
 * @brief      Set Superposition: Position and Gain
 * @param      DIRANA_DRIVER_TYPE_ENUM PID        
 *            int8_t PresetGain : Max is 0
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvSuperPositionGain(DIRANA_DRIVER_TYPE_ENUM PID,uint8_t AddOnIndex, int8_t PresetGain) 
{
    uint8_t Result = SUBLAYER_DOING;
    DIRANA_DRIVER_TYPE_ENUM PrivateID = PID;
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
    {    //New Expressions, Different With Hero!!!
        Gain[0] = 0x1000 - Tab_Db2Lin[-PresetGain];    //First Gain
        Gain[1] = 0x1000 - Tab_Db2Lin[-PresetGain];    //Sencond Gain
        Gain[2] = 0x1000 - Tab_Db2Lin[-PresetGain];    //Third Gain
        Gain[3] = 0x1000 - Tab_Db2Lin[-PresetGain];    // Fourth gain
    }
    switch(AddOnIndex)
    {
        //Primary Mix with Nav
        case P_MIX_NAV_FL: //Primary mix with Nav FL
            Label = ADSP_Y_Sup_NonFL_REL;
            break;
        case P_MIX_NAV_FR: 
            Label = ADSP_Y_Sup_NonFR_REL;
            break;
        case P_MIX_NAV_RL: 
            Label = ADSP_Y_Sup_NonRL_REL;
            break;
        case P_MIX_NAV_RR: 
            Label = ADSP_Y_Sup_NonRR_REL;
            break;
        case P_MIX_NAV_FRONT:
            Label = ADSP_Y_Sup_NonFL_REL;
            Length = 2;
            break;
        case P_MIX_NAV_REAR:
            Label = ADSP_Y_Sup_NonRL_REL;
            Length = 2;
            break;
        case P_MIX_NAV_ALL:
            Label = ADSP_Y_Sup_NonFL_REL;
            Length = 4;
            break;

        // Primary Mix with Phone    
        case P_MIX_PHONE_FL: //Primary mix with Phone FL
            Label = ADSP_Y_Sup_TonFL_REL;
            break;
        case P_MIX_PHONE_FR: 
            Label = ADSP_Y_Sup_TonFR_REL;
            break;
        case P_MIX_PHONE_RL: 
            Label = ADSP_Y_Sup_TonRL_REL;
            break;
        case P_MIX_PHONE_RR: 
            Label = ADSP_Y_Sup_TonRR_REL;
            break;
        case P_MIX_PHONE_FRONT:
            Label = ADSP_Y_Sup_TonFL_REL;
            Length = 2;
            break;
        case P_MIX_PHONE_REAR:
            Label = ADSP_Y_Sup_TonRL_REL;
            Length = 2;
            break;
        case P_MIX_PHONE_ALL:
            Label = ADSP_Y_Sup_TonFL_REL;
            Length = 4;
            break;

        //Primary Mix with Chime    
        case P_MIX_CHIME_FL: //Chime FL mix to Primary
            Label = ADSP_Y_Sup_ChionFL_REL;
            break;
        case P_MIX_CHIME_FR: 
            Label = ADSP_Y_Sup_ChionFR_REL;
            break;
        case P_MIX_CHIME_RL: 
            Label = ADSP_Y_Sup_ChionRL_REL;
            break;
        case P_MIX_CHIME_RR: 
            Label = ADSP_Y_Sup_ChionRR_REL;
            break;    
        case P_MIX_CHIME_FRONT:
            Label = ADSP_Y_Sup_ChionFL_REL;
            Length = 2;
            break;
        case P_MIX_CHIME_REAR:
            Label = ADSP_Y_Sup_ChionRL_REL;
            Length = 2;
            break;
        case P_MIX_CHIME_ALL:
            Label = ADSP_Y_Sup_ChionFL_REL;
            Length = 4;
            break;    

        case P_MIX_EXT_FL:
            Label = ADSP_Y_Sup_ExtonFL_REL;
            break;
        case P_MIX_EXT_FR:
            Label = ADSP_Y_Sup_ExtonFR_REL;
            break;            
        case P_MIX_EXT_FRONT:
            Label = ADSP_Y_Sup_ExtonFL_REL;
            Length = 2;
            break;            
        case P_MIX_EXT_ALL:
            Label = ADSP_Y_Sup_ExtonFL_REL;
            Length = 4;
            break;
            
        //Secondary Mix with Chime
        case S_MIX_CHIME_LEFT:    // Chime Front mix to Secondary
            Label = ADSP_Y_Sup_ChionSL_REL;
            break;
        case S_MIX_CHIME_RIGHT:
            Label = ADSP_Y_Sup_ChionSR_REL;
            break;
        case S_MIX_CHIME_ALL:
            Label = ADSP_Y_Sup_ChionSL_REL;
            Length = 2;
            break;
    }

    if((-100) == PresetGain) 
    {
        Label = ADSP_Y_Sup_NonFL_REL;
        Length = 2;
    }
    if(0 == Label)
    {
        return (SUBLAYER_ERROR);
    }

    Result = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,Label,Length,Gain);

    return (Result);
}
/**********************************************************
 * @function    Dirana_SetChimeMode
 * @brief      Set the Specific Chime of Dirana
 * @param      uint8_t Mode:                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetChimeMode(uint8_t Mode)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_CHIMEMODE;
    uint8_t Result = SUBLAYER_DOING;

    if(Mode == sAudio.BeepLast)
    {
        Result = Dirana_WriteMemTab(PrivateID,Tab_FastChime);
    }
    else
    {
        switch(Mode)
        {
            case BEEP_TYPE_ALERT:
                Result = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_Chime_PSAlt); 
                break;

            case BEEP_TYPE_SEATBELT:
                Result = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_Chime_PSFsb); 
                break;
        
            case BEEP_TYPE_CONFIRMATION:
                Result = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_Chime_PSBle1); 
                break;
                
            case BEEP_TYPE_IGNITION:
                Result = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_Chime_PSKii);
                break;
                
            case BEEP_TYPE_CRUISE:
                Result = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_Chime_PSCci);
                break;

            case BEEP_TYPE_ORDINARY:
            case BEEP_TYPE_USER:    
            case BEEP_TYPE_KEY_ACK:
                if(BEEP_TYPE_SET_LOW == sAudioDat.sInfo.BeepType)
                {
                    Result = Dirana_WriteMemTab(PrivateID,Tab_WholeChimeLow);
                }
                else if(BEEP_TYPE_SET_HIGH == sAudioDat.sInfo.BeepType)
                {
                    Result = Dirana_WriteMemTab(PrivateID,Tab_WholeChimeHigh);
                }
                else
                {
                    Result = SUBLAYER_DONE;
                }
                break;

            case BEEP_TYPE_TYRE_ALERT:   
            case BEEP_TYPE_KEY_NCK:       
                Result = Dirana_WriteMemTab(PrivateID,Tab_WholeChimeTyre);
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
 * @function    Dirana_DrvSetChimeMasterVol
 * @brief      Setup Chime Volume
 * @param      uint8_t vol:                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvSetChimeMasterVol(uint8_t Vol)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_CHIME_VOL;    
    uint8_t Result = SUBLAYER_DOING;
    int32_t Data;
    
    Data = Tab_Db2Lin[Vol];     //Changed by deefisher

    Result = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y, ADSP_Y_Tsq_ChimeVol_Bk_REL,Data);

    return (Result);
}
/**********************************************************
 * @function    Dirana_BeepInit
 * @brief      Initialize Beep: Enable and Set pos and set volume
 * @param      NULL                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_BeepInit(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sDirana.ThirdLayerStep)
    {
        //Enable Chime
        case OPERATION_0:
            SubResult = Dirana_EasyProgrammWrite(DIRANA_IIC_BEEPINIT,ADSP_EASYP_Chime_Enable); 
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.ThirdLayerStep = OPERATION_1;
            }
            break;

        //Impose Chime on Channel : Front 
        case OPERATION_1:
            SubResult = Dirana_BeepPos(sAudioDat.sInfo.BeepPos);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.ThirdLayerStep = OPERATION_2;
            }
            break;

        //Set Beep Volume
        case OPERATION_2:
            SubResult = Dirana_BeepVol(sAudioDat.sAdv.BeepVol);
            if(SUBLAYER_DONE == SubResult)
            {
                sDirana.ThirdLayerStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            sDirana.ThirdLayerStep = 0;
            Result = SUBLAYER_STEP_ERROR;
            break;
    }    

    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;    
        sDirana.ThirdLayerStep = 0;
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_BeepVol
 * @brief      Set Beep Volume
 * @param      uint8_t Val:                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_BeepVol(uint8_t Val)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t VolVal;

    //40~0 equal to 0~ -66db
    VolVal = (66 - (Tab_BeepVolume[Val] * 66)/BEEP_VOL_MAX);
    
    Result = Dirana_DrvSetChimeMasterVol(VolVal);

    return (Result);
}
/**********************************************************
 * @function    Dirana_BeepPos
 * @brief      Set Beep Position
 * @param      uint8_t Val:                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_BeepPos(uint8_t Pos)
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

    Result = Dirana_DrvSuperPositionGain(DIRANA_IIC_SET_IMPOSE,DirectPos,0);

    return (Result);
}
/**********************************************************
 * @function    Dirana_Beep
 * @brief      Set the Specific Beep
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
uint8_t Dirana_Beep(uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_SetChimeMode(Type);

    return (Result);
}
/**********************************************************
 * @function    Dirana_BeepStop
 * @brief      Stop Currently Beeping
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
uint8_t Dirana_BeepStop(void)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_WriteMemTab(DIRANA_IIC_BEEPSTOP,Tab_StopChime);

    return (Result);
}
/**********************************************************
 * @function    Dirana_GetMaxTone
 * @brief      Get Max Gain Value of Tone
 * @param      NULL                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GetMaxTone(void)
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
 * @function    Dirana_DrvBassSet
 * @brief      Dirana Set Bass 
 * @param      uint8_t Stream
 *            PN_ATTRI_STRUCT sBass
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvBassSet(uint8_t Stream,PN_ATTRI_STRUCT sBass)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_BASS;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Label = 0;
    uint8_t MaxTone;
    
    switch(sAudio.DrvBassStep)
    {
        //Calc Bass Related Filter's Coefficients
        case BASS_CTL_CALC:
            Dirana_Calc_Bass(sBass,sDirana.BassCoefBuffer);
            if(sBass.Gain >= 0)  //Calc Gain
            { 
                sDirana.BassCoefBuffer[10] = Tab_Db2Lin[24 - sBass.Gain] - 0x080;
            }
            else
            {
                sDirana.BassCoefBuffer[10] = 0x080 - Tab_Db2Lin[24 + sBass.Gain];
            }
            sAudio.DrvBassStep = BASS_CTL_SET;
            break;

        //Set Bass related  Filter's Coefficients
        case BASS_CTL_SET:
            if(STREAM_PRIMARY == Stream)
            {
                Label = ADSP_Y_BMT_a1bHP_REL;    // must be Actual Address!!!!
            }
            else if(STREAM_SECONDARY==Stream)
            {
                Label = ADSP_Y_BMT_a1bHS_REL;
            }
            
            SubResult = Dirana_ScratchDataWrite(PrivateID,Label,11,sDirana.BassCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvBassStep = BASS_CTL_SCALER;
            }
            break;

        //Dynamic Update Pre-Scaler
        case BASS_CTL_SCALER:
            MaxTone = Dirana_GetMaxTone();
            if((MaxTone - 12) > 0)
            {
                sAudio.UltraScaler += (MaxTone - 12); 
                sDirana.BassCoefBuffer[0] =  Tab_Db2Lin[MaxTone - 12];
            }
            else
            {
                sDirana.BassCoefBuffer[0] =  0x7FF;
            }
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_DesScalBMTP_REL,(int32_t)sDirana.BassCoefBuffer[0]);
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
 * @function    Dirana_SetBass
 * @brief      Set Bass 
 * @param      PN_FILTER_STRUCT sBass
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetBass(PN_FILTER_STRUCT sBass,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t tStream;
    PN_ATTRI_STRUCT sTmpBass;
    
    if(SYSTEM_FRONT == Type) 
    {
        tStream = STREAM_PRIMARY;
    }
    else if(SYSTEM_REAR == Type) 
    {
        tStream = STREAM_SECONDARY;
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
        sTmpBass.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 0].Gain;
        sTmpBass.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 0].CF;
        sTmpBass.Q = 1.0;
    }
#else
    sTmpBass.Gain = (int8_t)(sBass.Gain - (AUDIO_BASS_MAX / 2));
    sTmpBass.CF = Tab_Bass_CF[sBass.CF];
    sTmpBass.Q = Tab_Filter_Q[sBass.Q];
#endif        
    Result = Dirana_DrvBassSet(tStream, sTmpBass);

    return (Result);
}
/**********************************************************
 * @function    Dirana_DrvMidSet
 * @brief      Dirana Set Tone: Middle
 * @param      uint8_t Stream
 *            PN_ATTRI_STRUCT sMid
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvMidSet(uint8_t Stream,PN_ATTRI_STRUCT sMid)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_MID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Label = 0;
    uint8_t MaxTone;
    
    switch(sAudio.DrvMidStep)
    {
        case MID_CTL_CALC:
            Dirana_Calc_Mid(sMid,sDirana.MidCoefBuffer);
            sAudio.DrvMidStep = MID_CTL_SET;
            break;

        case MID_CTL_SET:
            if(STREAM_PRIMARY == Stream)
            {
                Label = ADSP_Y_BMT_a1mHP_REL; // must be Actual Address!!!!
            }
            else if(STREAM_SECONDARY == Stream)
            {
                Label = ADSP_Y_BMT_a1mHS_REL;
            }
            
            SubResult = Dirana_ScratchDataWrite(PrivateID,Label,7,sDirana.MidCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvMidStep = MID_CTL_SCALER;
            }
            break;

        case MID_CTL_SCALER:
            MaxTone = Dirana_GetMaxTone();    
            if((MaxTone - 12) > 0)
            {
                sAudio.UltraScaler += (MaxTone - 12); 
                sDirana.MidCoefBuffer[0] =  Tab_Db2Lin[MaxTone - 12];
            }
            else
            {
                sDirana.MidCoefBuffer[0] =  0x7FF;
            }
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_DesScalBMTP_REL,(int32_t)sDirana.MidCoefBuffer[0]);
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
 * @function    Dirana_SetMid
 * @brief      Set Middle 
 * @param      PN_FILTER_STRUCT sMid
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetMid(PN_FILTER_STRUCT sMid,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t tStream;
    PN_ATTRI_STRUCT sTmpMid;
    
    if(SYSTEM_FRONT == Type) 
    {
        tStream = STREAM_PRIMARY;    
    }
    else if(SYSTEM_REAR == Type) 
    {
        tStream = STREAM_SECONDARY;
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
        sTmpMid.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 1].Gain;
        sTmpMid.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 1].CF;
        sTmpMid.Q = 1.0;
    }
#else
    sTmpMid.Gain = (int8_t)(sMid.Gain - (AUDIO_MID_MAX / 2));
    sTmpMid.CF = Tab_Middle_CF[sMid.CF];
    sTmpMid.Q = Tab_Filter_Q[sMid.Q];
#endif
    Result = Dirana_DrvMidSet(tStream,sTmpMid);

    return (Result);
}
/**********************************************************
 * @function    Dirana_DrvTrebSet
 * @brief      Dirana3 Set Tone: Treble
 * @param      uint8_t Stream
 *            PN_ATTRI_STRUCT sTreble
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvTrebSet(uint8_t Stream,PN_ATTRI_STRUCT sTreble)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_TREBLE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Label = 0;
    uint8_t MaxTone;
    
    switch(sAudio.DrvTrebleStep)
    {
        case TREBLE_CTL_CALC:
            Dirana_Calc_Treble(sTreble,sDirana.TrebleCoefBuffer);
            sAudio.DrvTrebleStep = TREBLE_CTL_SET;
            break;

        case TREBLE_CTL_SET:
            if (STREAM_PRIMARY == Stream)
            {
                Label = ADSP_Y_BMT_a1tP_REL;    // must be Actual Address!!!!
            }
            else if(STREAM_SECONDARY==Stream)
            {
                Label = ADSP_Y_BMT_a1tS_REL;
            }
            
            SubResult = Dirana_ScratchDataWrite(PrivateID,Label,6,sDirana.TrebleCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvTrebleStep = TREBLE_CTL_SCALER;
            }
            break;

        case TREBLE_CTL_SCALER:
            MaxTone = Dirana_GetMaxTone();    
            if((MaxTone - 12) > 0)
            {
                sAudio.UltraScaler += (MaxTone - 12); 
                sDirana.TrebleCoefBuffer[0] =  Tab_Db2Lin[MaxTone - 12];
            }
            else
            {
                sDirana.TrebleCoefBuffer[0] =  0x7FF;
            }
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_DesScalBMTP_REL,(int32_t)sDirana.TrebleCoefBuffer[0]);
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
 * @function    Dirana_SetTreble
 * @brief      Set Treble 
 * @param      PN_FILTER_STRUCT sTreble
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetTreble(PN_FILTER_STRUCT sTreble,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t tStream;
    PN_ATTRI_STRUCT sTmpTreble;
    
    if(SYSTEM_FRONT == Type) 
    {
        tStream = STREAM_PRIMARY;
    }
    else if(SYSTEM_REAR == Type) 
    {
        tStream = STREAM_SECONDARY;
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
        sTmpTreble.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 2].Gain;
        sTmpTreble.CF = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 2].CF;
        sTmpTreble.Q = 1.0;
    }
#else
    sTmpTreble.Gain = (int8_t)(sTreble.Gain - 12);
    sTmpTreble.CF = Tab_Treble_CF[sTreble.CF];
    sTmpTreble.Q = Tab_Filter_Q[sTreble.Q];
#endif
    Result = Dirana_DrvTrebSet(tStream,sTmpTreble);

    return (Result);
}
#if 0
/**********************************************************
 * @function    Dirana_DrvBalSet
 * @brief      Dirana3 Set Balance
 * @param      uint8_t Level
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvBalSet(uint8_t Level, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_BAL;
    uint16_t Label = 0;
    int32_t Coeffs[2] = {0};
    
    if(SYSTEM_FRONT == Type) 
    {
        Label = ADSP_Y_Vol_BalPL_REL;
    }
    else if(SYSTEM_REAR == Type) 
    {
        Label = ADSP_Y_Vol_BalSL_REL;
    }

    //Calculate 
    if (Level >= (AUDIO_BALANCE_MAX / 2))
    {
        // 2db Per Step
        Coeffs[0] = Tab_Db2Lin[(2 * Level) - AUDIO_BALANCE_MAX];
        Coeffs[1] = 0x07FFUL;/* ~ +1 */
    }
    else
    {
        // 2db Per Step
        Coeffs[0] = 0x07FFUL;/* ~ +1 */
        Coeffs[1] = Tab_Db2Lin[(2 * Level) - AUDIO_BALANCE_MAX];
    }
    
    switch(sAudio.DrvBalStep)
    {
        //Set Balance FL FR
        case OPERATION_0:
            SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,Label,2,Coeffs);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvBalStep =  OPERATION_1;
            }
            break;

        //Set Balance Center/Subwoofer
        case OPERATION_1:
            if(SYSTEM_REAR == Type) 
            {
                SubResult = SUBLAYER_DONE;
            }
            else
            {
                Coeffs[0] = ((Coeffs[0] + Coeffs[1]) / 2);
                Coeffs[1] = Coeffs[0];
                SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_BalSwL_REL,2,Coeffs);
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvBalStep =  OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            sAudio.DrvBalStep =  OPERATION_0;
            break;
    }

    //Sync With Error Result----
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.DrvBalStep =  OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_DrvFadSet
 * @brief      Dirana3 Set Fader
 * @param      uint8_t Level
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DrvFadSet(uint8_t Level, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_FAD;
    uint16_t Label = 0;
    int32_t Coeffs[2] = {0};
    
    Label = ADSP_Y_Vol_FadF_REL;

    //No Secondary Channel Control
    if(SYSTEM_REAR == Type) 
    {
        return (SUBLAYER_DONE);
    }

    //Calculate 
    if (Level >= (AUDIO_FADER_MAX / 2))
    {
        // 2db Per Step
        Coeffs[0] = Tab_Db2Lin[(2 * Level) - AUDIO_FADER_MAX];
        Coeffs[1] = 0x07FFUL;/* ~ +1 */
    }
    else
    {
        // 2db Per Step
        Coeffs[0] = 0x07FFUL;/* ~ +1 */
        Coeffs[1] = Tab_Db2Lin[(2 * Level) - AUDIO_FADER_MAX];
    }
    
    switch(sAudio.DrvFadStep)
    {
        //Set Balance FL FR
        case OPERATION_0:
            SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,Label,2,Coeffs);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvFadStep =  OPERATION_1;
            }
            break;

        //Set Balance Center/Subwoofer
        case OPERATION_1:
            Coeffs[0] = ((Coeffs[0] + Coeffs[1]) / 2);
            Coeffs[1] = Coeffs[0];
            SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_FadSwL_REL,2,Coeffs);

            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DrvFadStep =  OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            sAudio.DrvFadStep =  OPERATION_0;
            break;
    }

    //Sync With Error Result----
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.DrvFadStep =  OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_SetBal
 * @brief      Dirana3 Set Balance
 * @param      uint8_t Level
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetBal(uint8_t Level, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_DrvBalSet(Level,Type);

    return (Result);
}
/**********************************************************
 * @function    Dirana_SetFad
 * @brief      Dirana3 Set Fader
 * @param      uint8_t Level
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetFad(uint8_t Level, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_DrvFadSet(Level,Type);

    return (Result);
}
#endif
/**********************************************************
 * @function    Dirana_SetBalFad
 * @brief      Dirana3 Set Bal&Fad
 * @param      NULL
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetBalFad(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_BF;
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
                SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_BalPL_REL,2,Coeffs);
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
            SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_BalSwL_REL,2,Coeffs);
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
                SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_FadF_REL,2,Coeffs);
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
            SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_FadSwL_REL,2,Coeffs);

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
 * @function    Dirana_SetDcFilter
 * @brief      Dirana3 Set DC Filter
 * @param      uint8_t Val
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetDcFilter(uint8_t Val, uint8_t Type)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_DCFILTER;
    uint8_t Result = SUBLAYER_DOING;
    int32_t Coeffs[3];
    uint16_t Label = 0;
    float TmpA,TmpB;

    if(SYSTEM_FRONT == Type)
    {
        Label = ADSP_Y_DCfilt_a1A_REL;
    }
    else if(SYSTEM_REAR == Type)
    {
        Label = ADSP_Y_DCfilt_a1B_REL;
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
        TmpB = PI * (((Val * 3.5) / ASRate) - 0.25);
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

    Result = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,Label,3,Coeffs);

    return (Result);
}
/**********************************************************
 * @function    Dirana_NavPhoneVol
 * @brief      Initialize Nav Route Volume
 * @param      uint8_t Val        
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_NavPhoneVol(uint8_t Val,uint8_t Type)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_NAV_PHONE_VOL;
    uint8_t Result = SUBLAYER_DOING;
    int8_t VolVal;
    int32_t VolDat;
    uint16_t Addr;

    if(0 == Type) //Navi Channel
    {
        Addr    = ADSP_Y_Vol_Nav_REL; 
    }
    else //Phone Channel
    {
        Addr    = ADSP_Y_Vol_Phon_REL; 
    }

    //Get Actually Volume Db Value
    //4 Temporary Swap Method,...
    VolVal = (Tab_VolDbLev[Val] / 2) + CHANNEL_VOL_DELTA;    
    //VolDat = Tab_Db2Lin[VolVal - VolMaxNP];
    VolDat = Tab_NaviPhone_Vol[12 - VolVal];
    
    Result = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,Addr,VolDat);

    return (Result);
}
/**********************************************************
 * @function    Dirana_DelayLine
 * @brief      Set Delay Line
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_DelayLine(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_DELAY_LINE;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    int32_t Data;

    switch(sAudio.DelayCtl)
    {
        case DIRANA_DELAY_STEP_WAIT:
            sAudio.DelayCtl = DIRANA_DELAY_STEP_MUTE;
            if(0x00 == (sAudio.DelayLineMask & DELAY_MASK_AR))
            {
                sAudio.DelayWait = AudioDelay(T200MS);
            }
            break;
    
        //Mute Before Adjust..
        case DIRANA_DELAY_STEP_MUTE:
            if(0 != sAudio.DelayWait)
                break;
        #if 1
            if(0x00 == (sAudio.DelayLineMask & DELAY_MASK_AR))
            {
                Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_MUTE,SYSTEM_FRONT);
            }
            sAudio.DelayCtl = DIRANA_DELAY_STEP_FL;
        #else
            SubResult = Dirana_SoftMute(DIRANA_CH_P,MUTE_ON);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = DIRANA_DELAY_STEP_FL;
            }
        #endif
            break;
    
        //Set Delay of Front Left Speaker
        case DIRANA_DELAY_STEP_FL:
            if((sAudio.sAchAttri[sAudio.SysChannel].MuteState & MASK_F_SMUTE)
                || (sAudio.DelayLineMask & DELAY_MASK_AR))
            {
                if(sAudio.DelayLineMask & DELAY_MASK_FL)
                {
                    //Calculate Delay Time and Send to register
                    Data = (RoundChange((sAudioDat.sAdv.DelayCustom[DELAY_LINE_FL] * (ASRate / 10000)),1) + 1);
                    SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_Delay_Length1_In_REL,Data);
                }
                else
                {
                    SubResult = SUBLAYER_DONE;
                }
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.DelayCtl = DIRANA_DELAY_STEP_FR;
                }
            }
            break;

        //Set Delay of Front Right Speaker
        case DIRANA_DELAY_STEP_FR:
            if(sAudio.DelayLineMask & DELAY_MASK_FR)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange((sAudioDat.sAdv.DelayCustom[DELAY_LINE_FR] * (ASRate / 10000)),1) + 1);
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_Delay_Length2_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = DIRANA_DELAY_STEP_RL;
            }
            break;

        //Set Delay of Rear Left Speaker
        case DIRANA_DELAY_STEP_RL:
            if(sAudio.DelayLineMask & DELAY_MASK_RL)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange((sAudioDat.sAdv.DelayCustom[DELAY_LINE_RL] * (ASRate / 10000)),1) + 1);
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_Delay_Length3_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = DIRANA_DELAY_STEP_RR;
            }
            break;

        //Set Delay of Rear Right Speaker
        case DIRANA_DELAY_STEP_RR:
            if(sAudio.DelayLineMask & DELAY_MASK_RR)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange((sAudioDat.sAdv.DelayCustom[DELAY_LINE_RR] * (ASRate / 10000)),1) + 1);
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_Delay_Length4_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = DIRANA_DELAY_STEP_SWL;
            }
            break;

        //Set Delay of SW Left Speaker
        case DIRANA_DELAY_STEP_SWL:
            if(sAudio.DelayLineMask & DELAY_MASK_SWL)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange((sAudioDat.sAdv.DelayCustom[DELAY_LINE_SWL] * (ASRate / 10000)),1) + 1);
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_Delay_Length5_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = DIRANA_DELAY_STEP_SWR;
            }
            break;

        //Set Delay of SW Right Speaker
        case DIRANA_DELAY_STEP_SWR:
            if(sAudio.DelayLineMask & DELAY_MASK_SWR)
            {
                //Calculate Delay Time and Send to register
                Data = (RoundChange((sAudioDat.sAdv.DelayCustom[DELAY_LINE_SWR] * (ASRate / 10000)),1) + 1);
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_Delay_Length6_In_REL,Data);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = DIRANA_DELAY_STEP_ACTIVE;
            }
            break;

        //Activate Settings!
        case DIRANA_DELAY_STEP_ACTIVE:
            if(sAudio.DelayLineMask)
            {
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_Delay_InitFlag_REL,0x7FFFFF);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayCtl = DIRANA_DELAY_STEP_END;
                if(0x00 == (sAudio.DelayLineMask & DELAY_MASK_AR))
                {
                    Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_UNMUTE,SYSTEM_FRONT);
                }
            }
            break;

        //All Done, Ends!
        case DIRANA_DELAY_STEP_END:
        #if 0
            SubResult = Dirana_SoftMute(DIRANA_CH_P,MUTE_OFF);
            if(SUBLAYER_DONE == SubResult)
        #else
            if((0x00 == (sAudio.sAchAttri[sAudio.SysChannel].MuteState & MASK_F_SMUTE)) 
                || (sAudio.DelayLineMask & DELAY_MASK_AR))
        #endif    
            {
                Result = SUBLAYER_DONE;
                sAudio.DelayLineMask = 0;
                sAudio.DelayCtl = DIRANA_DELAY_STEP_WAIT;
            }
            break;

        default:
            sAudio.DelayCtl = DIRANA_DELAY_STEP_WAIT;
            break;
    }

    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.DelayCtl = DIRANA_DELAY_STEP_WAIT;
    }
    
    return(Result);
}
/**********************************************************
 * @function    Dirana_GetMaxGeq
 * @brief      Get Max Gain Value of Graphic Equalizer
 * @param      NULL                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GetMaxGeq(void)
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
 * @function    Dirana_SetGeq
 * @brief      Set a specific GEQ Mode
 * @param      uint8_t Typel            
 * @retval     Result
 **********************************************************/
#define GEQ_BAND ((sAudio.GeqStep - GEQ_BAND1_CALC) / 2)
uint8_t Dirana_SetGeq(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_GEQ;
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
                    ExecutedFlag = 0;
                    SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,ADSP_EASYP_GraphEQ_Enable);
                    if(SUBLAYER_DONE == SubResult)
                    {
                        sAudio.GeqStep = GEQ_ENABLE_ADD4;
                    }
                }
                else
                {
                    sAudio.GeqStep = GEQ_BAND1_CALC;
                }
                break;

            case GEQ_ENABLE_ADD4:
                ExecutedFlag = 0;
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,ADSP_EASYP_GraphEQ_additional4Band);
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
                        Dirana_Calc_Eq(0,sTmpGeq,sDirana.GeqCoefBuffer);
                    }
                    else
                    {
                        Dirana_Calc_Eq(1,sTmpGeq,sDirana.GeqCoefBuffer);
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
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_GEq_b10L_REL,7,sDirana.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND1);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND2_CALC;
                }
                break;

            //Set Band2 Related Value
            case GEQ_BAND2_SET:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_GEq_b20L_REL,7,sDirana.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND2);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND3_CALC;
                }
                break;

            //Set Band3 Related Value
            case GEQ_BAND3_SET:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_GEq_b30L_REL,7,sDirana.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND3);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND4_CALC;
                }
                break;

            //Set Band4 Related Value : Actually Band 6
            case GEQ_BAND4_SET:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_EQ4_b10L_REL,7,sDirana.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND4);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND5_CALC;
                }
                break;

            //Set Band5 Related Value: Actually Band 7
            case GEQ_BAND5_SET:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_EQ4_b20L_REL,7,sDirana.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND5);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND6_CALC;
                }
                break;

            //Set Band6 Related Value
            case GEQ_BAND6_SET:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_GEq_b40_REL,4,sDirana.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND6);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND7_CALC;
                }
                break;    

            //Set Band7 Related Value
            case GEQ_BAND7_SET:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_GEq_b50_REL,4,sDirana.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND7);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND8_CALC;
                }
                break;        

            //Set Band8 Related Value
            case GEQ_BAND8_SET:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_EQ4_b30_REL,4,sDirana.GeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.GeqMask &= (~GEQ_MASK_BAND8);    //Clear Step Mask Bit
                    sAudio.GeqStep = GEQ_BAND9_CALC;
                }
                break;    

            //Set Band9 Related Value
            case GEQ_BAND9_SET:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_EQ4_b40_REL,4,sDirana.GeqCoefBuffer);
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
                MaxGeq = Dirana_GetMaxGeq();
                if((MaxGeq - 12) > 0)
                {
                    sAudio.UltraScaler += (MaxGeq - 12); 
                    sDirana.GeqCoefBuffer[0] =  Tab_Db2Lin[MaxGeq - 12];
                }
                else
                {
                    sDirana.GeqCoefBuffer[0] =  0x7FF;
                }
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_DesScalGEq_REL,(int32_t)sDirana.GeqCoefBuffer[0]);
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
 * @function    Dirana_SetPhaseShifter
 * @brief      Set Signal Phase Shifter of a specific channel
 * @param      uint8_t Typel            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetPhaseShifter(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_PHASE;
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
                //Setting[3] = (~Setting[3]) & 0xFFF;  //Patch : force
                
                SubResult = Dirana_WriteMemData(PrivateID,MEM_TYPE_Y,ADSP_Y_Vol_SignFL_REL,6,Setting);
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
 * @function    Dirana_SetLoudness
 * @brief      Set Loudness On/Off
 * @param      NULL        
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetLoudness(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_LOUDNESS;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Coeffs;

    switch(sAudio.LoudnessCtl)
    {
        //Initialize Loudness Mode: Static Independent
        case LOUD_CTL_INIT:
            if(sAudio.LoudnessMask & LOUD_MASK_INIT)    
            {
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,ADSP_EASYP_Loudf_StaticIndep);
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
            SubResult = Dirana_WriteMemTab(PrivateID,Tab_Loudness_Config);
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
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Loudf_StatLev_REL,0x07FF);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.LoudnessCtl = LOUD_CTL_OFF_TREBLE;
                //If coupled, "ADSP_Y_Loudf_StatLevT_REL" is not needed
            }
            break;

        //Set Treble Boost to Zero
        case LOUD_CTL_OFF_TREBLE:
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_Y,ADSP_Y_Loudf_StatLevT_REL,0x07FF);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.LoudnessCtl = LOUD_CTL_END;
            }
            break;

        //Load Bass Coefficient
        case LOUD_CTL_BASS_COF:
            if(sAudio.LoudnessMask & LOUD_MASK_BASS_COF)
            {
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_Loudf_a1bL_REL,8,(uint16_t*)(&Tab_Loudness_Bass[8 * sAudioDat.sBasicBK.sLoudness.BassCutOff]));
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
                SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_Loudf_a1t_REL,5,(uint16_t*)(&Tab_Loudness_Treble[5 * sAudioDat.sBasicBK.sLoudness.TrebleCentre]));
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
                Audio_OpQueueIn(AUDIO_COMMON_VOL);
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
 * @function    Dirana_SetLoudness
 * @brief      Set Loudness On/Off
 * @param      NULL        
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetSubwoofer(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_SW;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    LHP_ATTRI_STRUCT sFilter;

    switch(sAudio.SwCtl)
    {
        //Create Subwoofer: Stereo Subwoofer
        case SW_CTL_CREATE:
            if(SW_MASK_CREATE & sAudio.SwMask)
            {
                if(OUT_SW_STEREO == sAudioDat.sInfo.SwCenMode)   //Stereo Sw
                {
                    SubResult = Dirana_WriteMemTab(PrivateID,Tab_Create_StereoSw);
                }
                else    //Center+Sw
                {
                    SubResult = Dirana_WriteMemTab(PrivateID,Tab_Create_MonoSw);
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
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,ADSP_EASYP_GPF2_Disable);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.SwCtl = SW_CTL_END;
                }
            }
            else
            {
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,ADSP_EASYP_GPF2_headroom);
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
            Dirana_Calc_1stLP(sFilter,sDirana.SwCoefBuffer); 
            sAudio.SwCtl = SW_CTL_SET;
            break;

        case SW_CTL_SET:
            SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_IIR2GPF2_b0L_REL,10,sDirana.SwCoefBuffer);
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
        Result =  SubResult;
        sAudio.SwCtl = SW_CTL_INIT;
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_SetPeq
 * @brief      Set a specific PEQ Mode
 * @param      uint8_t Typel            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetPeq(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_PEQ;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    PN_ATTRI_STRUCT sTmpPeq;
    uint8_t ExecutedFlag = 1;

    while(1 == ExecutedFlag) //speed up efficiency, avoid idle step  
    {    
        switch(sAudio.PeqStep)
        {
            case PEQ_BAND1_CALC_FL:
            case PEQ_BAND1_CALC_FR:
            case PEQ_BAND1_CALC_RL:
            case PEQ_BAND1_CALC_RR:    
                if(PEQ_MASK_BAND1 & sAudio.PeqMask[BAND1_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND1_CH][EQ_BAND_1].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND1_CH][EQ_BAND_1].Q];
                        sTmpPeq.CF = Tab_Peq_Band1_CF[sAudioPeq.sBuffer[BAND1_CH][EQ_BAND_1].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_Eq(1,sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;

            case PEQ_BAND2_CALC_FL:
            case PEQ_BAND2_CALC_FR:
            case PEQ_BAND2_CALC_RL:
            case PEQ_BAND2_CALC_RR:    
                if(PEQ_MASK_BAND2 & sAudio.PeqMask[BAND2_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND2_CH][EQ_BAND_2].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND2_CH][EQ_BAND_2].Q];
                        sTmpPeq.CF = Tab_Peq_Band2_CF[sAudioPeq.sBuffer[BAND2_CH][EQ_BAND_2].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_Eq(1,sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;

            case PEQ_BAND3_CALC_FL:
            case PEQ_BAND3_CALC_FR:
            case PEQ_BAND3_CALC_RL:
            case PEQ_BAND3_CALC_RR:    
                if(PEQ_MASK_BAND3 & sAudio.PeqMask[BAND3_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND3_CH][EQ_BAND_3].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND3_CH][EQ_BAND_3].Q];
                        sTmpPeq.CF = Tab_Peq_Band3_CF[sAudioPeq.sBuffer[BAND3_CH][EQ_BAND_3].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_Eq(1,sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;

            case PEQ_BAND4_CALC_FL:
            case PEQ_BAND4_CALC_FR:
            case PEQ_BAND4_CALC_RL:
            case PEQ_BAND4_CALC_RR:    
                if(PEQ_MASK_BAND4 & sAudio.PeqMask[BAND4_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND4_CH][EQ_BAND_4].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND4_CH][EQ_BAND_4].Q];
                        sTmpPeq.CF = Tab_Peq_Band4_CF[sAudioPeq.sBuffer[BAND4_CH][EQ_BAND_4].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_Eq(1,sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;
                
            case PEQ_BAND5_CALC_FL:
            case PEQ_BAND5_CALC_FR:
            case PEQ_BAND5_CALC_RL:
            case PEQ_BAND5_CALC_RR:    
                if(PEQ_MASK_BAND5 & sAudio.PeqMask[BAND5_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND5_CH][EQ_BAND_5].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND5_CH][EQ_BAND_5].Q];
                        sTmpPeq.CF = Tab_Peq_Band5_CF[sAudioPeq.sBuffer[BAND5_CH][EQ_BAND_5].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_Eq(1,sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;        

            case PEQ_BAND6_CALC_FL:
            case PEQ_BAND6_CALC_FR:
            case PEQ_BAND6_CALC_RL:
            case PEQ_BAND6_CALC_RR:    
                if(PEQ_MASK_BAND6 & sAudio.PeqMask[BAND6_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND6_CH][EQ_BAND_6].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND6_CH][EQ_BAND_6].Q];
                        sTmpPeq.CF = Tab_Peq_Band6_CF[sAudioPeq.sBuffer[BAND6_CH][EQ_BAND_6].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_FB_2ndPN(sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;    

            case PEQ_BAND7_CALC_FL:
            case PEQ_BAND7_CALC_FR:
            case PEQ_BAND7_CALC_RL:
            case PEQ_BAND7_CALC_RR:    
                if(PEQ_MASK_BAND7 & sAudio.PeqMask[BAND7_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND7_CH][EQ_BAND_7].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND7_CH][EQ_BAND_7].Q];
                        sTmpPeq.CF = Tab_Peq_Band7_CF[sAudioPeq.sBuffer[BAND7_CH][EQ_BAND_7].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_FB_2ndPN(sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;    

            case PEQ_BAND8_CALC_FL:
            case PEQ_BAND8_CALC_FR:
            case PEQ_BAND8_CALC_RL:
            case PEQ_BAND8_CALC_RR:    
                if(PEQ_MASK_BAND8 & sAudio.PeqMask[BAND8_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND8_CH][EQ_BAND_8].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND8_CH][EQ_BAND_8].Q];
                        sTmpPeq.CF = Tab_Peq_Band8_CF[sAudioPeq.sBuffer[BAND8_CH][EQ_BAND_8].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_FB_2ndPN(sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;    

            case PEQ_BAND9_CALC_FL:
            case PEQ_BAND9_CALC_FR:
            case PEQ_BAND9_CALC_RL:
            case PEQ_BAND9_CALC_RR:    
                if(PEQ_MASK_BAND9 & sAudio.PeqMask[BAND9_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND9_CH][EQ_BAND_9].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND9_CH][EQ_BAND_9].Q];
                        sTmpPeq.CF = Tab_Peq_Band9_CF[sAudioPeq.sBuffer[BAND9_CH][EQ_BAND_9].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_FB_2ndPN(sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;    

            case PEQ_BAND10_CALC_FL:
            case PEQ_BAND10_CALC_FR:
            case PEQ_BAND10_CALC_RL:
            case PEQ_BAND10_CALC_RR:    
                if(PEQ_MASK_BAND10 & sAudio.PeqMask[BAND10_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND10_CH][EQ_BAND_10].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND10_CH][EQ_BAND_10].Q];
                        sTmpPeq.CF = Tab_Peq_Band10_CF[sAudioPeq.sBuffer[BAND10_CH][EQ_BAND_10].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_FB_2ndPN(sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;    

            case PEQ_BAND11_CALC_FL:
            case PEQ_BAND11_CALC_FR:
            case PEQ_BAND11_CALC_RL:
            case PEQ_BAND11_CALC_RR:    
                if(PEQ_MASK_BAND11 & sAudio.PeqMask[BAND11_CH])
                {
                    ExecutedFlag = 0;
                    if(PEQ_MODE_CUSTOM == sAudioPeq.Type)
                    {
                        sTmpPeq.Gain = (int8_t)(sAudioPeq.sBuffer[BAND11_CH][EQ_BAND_11].Gain - PEQ_GAIN_DELTA);
                        sTmpPeq.Q = Tab_Filter_Q[sAudioPeq.sBuffer[BAND11_CH][EQ_BAND_11].Q];
                        sTmpPeq.CF = Tab_Peq_Band11_CF[sAudioPeq.sBuffer[BAND11_CH][EQ_BAND_11].CF];
                    }
                    else
                    {
                        sTmpPeq.Gain = 0; //Temp...
                        sTmpPeq.Q = 1;
                        sTmpPeq.CF = 100;
                    }
                    Dirana_Calc_FB_2ndPN(sTmpPeq,sDirana.PeqCoefBuffer);
                    sAudio.PeqStep += 1;
                }
                else
                {
                    sAudio.PeqStep += 2;
                }
                break;            
                
            case PEQ_BAND1_SET_FL:
            case PEQ_BAND1_SET_FR:
            case PEQ_BAND1_SET_RL:
            case PEQ_BAND1_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),7,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND1_CH] &= (~PEQ_MASK_BAND1);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;

            case PEQ_BAND2_SET_FL:
            case PEQ_BAND2_SET_FR:
            case PEQ_BAND2_SET_RL:
            case PEQ_BAND2_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),7,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND2_CH] &= (~PEQ_MASK_BAND2);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;

            case PEQ_BAND3_SET_FL:
            case PEQ_BAND3_SET_FR:
            case PEQ_BAND3_SET_RL:
            case PEQ_BAND3_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),7,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND3_CH] &= (~PEQ_MASK_BAND3);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;

            case PEQ_BAND4_SET_FL:
            case PEQ_BAND4_SET_FR:
            case PEQ_BAND4_SET_RL:
            case PEQ_BAND4_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),7,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND4_CH] &= (~PEQ_MASK_BAND4);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;

            case PEQ_BAND5_SET_FL:
            case PEQ_BAND5_SET_FR:
            case PEQ_BAND5_SET_RL:
            case PEQ_BAND5_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),7,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND5_CH] &= (~PEQ_MASK_BAND5);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;

            case PEQ_BAND6_SET_FL:
            case PEQ_BAND6_SET_FR:
            case PEQ_BAND6_SET_RL:
            case PEQ_BAND6_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),10,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND6_CH] &= (~PEQ_MASK_BAND6);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;            

            case PEQ_BAND7_SET_FL:
            case PEQ_BAND7_SET_FR:
            case PEQ_BAND7_SET_RL:
            case PEQ_BAND7_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),10,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND7_CH] &= (~PEQ_MASK_BAND7);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;    

            case PEQ_BAND8_SET_FL:
            case PEQ_BAND8_SET_FR:
            case PEQ_BAND8_SET_RL:
            case PEQ_BAND8_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),10,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND8_CH] &= (~PEQ_MASK_BAND8);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;                

            case PEQ_BAND9_SET_FL:
            case PEQ_BAND9_SET_FR:
            case PEQ_BAND9_SET_RL:
            case PEQ_BAND9_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),10,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND9_CH] &= (~PEQ_MASK_BAND9);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;    

            case PEQ_BAND10_SET_FL:
            case PEQ_BAND10_SET_FR:
            case PEQ_BAND10_SET_RL:
            case PEQ_BAND10_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),10,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND10_CH] &= (~PEQ_MASK_BAND10);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;    

            case PEQ_BAND11_SET_FL:
            case PEQ_BAND11_SET_FR:
            case PEQ_BAND11_SET_RL:
            case PEQ_BAND11_SET_RR:
                ExecutedFlag = 0;
                SubResult = Dirana_ScratchDataWrite(PrivateID,Dirana_GetPeqAddr(sAudio.PeqStep),10,sDirana.PeqCoefBuffer);
                if(SUBLAYER_DONE == SubResult)
                {
                    sAudio.PeqMask[BAND11_CH] &= (~PEQ_MASK_BAND11);    //Clear Step Mask Bit
                    sAudio.PeqStep += 1;
                }
                break;    

            //All Done!!
            case PEQ_BAND_END:
                ExecutedFlag = 0;
                Result = SUBLAYER_DONE;
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
 * @function    Dirana_GetPeqAddr
 * @brief      Calc 2nd order Low/High Pass Filter  Cofficient
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint16_t Dirana_GetPeqAddr(uint8_t Step)
{
    uint16_t Result;
    
    switch(Step)
    {
        case PEQ_BAND1_SET_FL:
            Result = ADSP_Y_EqFL_b10L_REL;
            break;
        case PEQ_BAND1_SET_FR:
            Result = ADSP_Y_EqFR_b10L_REL;
            break;
        case PEQ_BAND1_SET_RL:
            Result = ADSP_Y_EqRL_b10L_REL;
            break;
        case PEQ_BAND1_SET_RR:
            Result = ADSP_Y_EqRR_b10L_REL;
            break;
            
        case PEQ_BAND2_SET_FL:
            Result = ADSP_Y_EqFL_b20L_REL;
            break;
        case PEQ_BAND2_SET_FR:
            Result = ADSP_Y_EqFR_b20L_REL;
            break;
        case PEQ_BAND2_SET_RL:
            Result = ADSP_Y_EqRL_b20L_REL;
            break;
        case PEQ_BAND2_SET_RR:
            Result = ADSP_Y_EqRR_b20L_REL;
            break;
            
        case PEQ_BAND3_SET_FL:
            Result = ADSP_Y_EqFL_b30L_REL;
            break;
        case PEQ_BAND3_SET_FR:
            Result = ADSP_Y_EqFR_b30L_REL;
            break;
        case PEQ_BAND3_SET_RL:
            Result = ADSP_Y_EqRL_b30L_REL;
            break;
        case PEQ_BAND3_SET_RR:
            Result = ADSP_Y_EqRR_b30L_REL;
            break;    
            
        case PEQ_BAND4_SET_FL:
            Result = ADSP_Y_EqFL_b40L_REL;
            break;
        case PEQ_BAND4_SET_FR:
            Result = ADSP_Y_EqFR_b40L_REL;
            break;
        case PEQ_BAND4_SET_RL:
            Result = ADSP_Y_EqRL_b40L_REL;
            break;
        case PEQ_BAND4_SET_RR:
            Result = ADSP_Y_EqRR_b40L_REL;
            break;    
            
        case PEQ_BAND5_SET_FL:
            Result = ADSP_Y_EqFL_b50L_REL;
            break;
        case PEQ_BAND5_SET_FR:
            Result = ADSP_Y_EqFR_b50L_REL;
            break;
        case PEQ_BAND5_SET_RL:
            Result = ADSP_Y_EqRL_b50L_REL;
            break;
        case PEQ_BAND5_SET_RR:
            Result = ADSP_Y_EqRR_b50L_REL;
            break;    
            
        case PEQ_BAND6_SET_FL:
            Result = ADSP_Y_EqFL_b60L_REL;
            break;
        case PEQ_BAND6_SET_FR:
            Result = ADSP_Y_EqFR_b60L_REL;
            break;
        case PEQ_BAND6_SET_RL:
            Result = ADSP_Y_EqRL_b60L_REL;
            break;
        case PEQ_BAND6_SET_RR:
            Result = ADSP_Y_EqRR_b60L_REL;
            break;    
            
        case PEQ_BAND7_SET_FL:
            Result = ADSP_Y_EqFL_b70L_REL;
            break;
        case PEQ_BAND7_SET_FR:
            Result = ADSP_Y_EqFR_b70L_REL;
            break;
        case PEQ_BAND7_SET_RL:
            Result = ADSP_Y_EqRL_b70L_REL;
            break;
        case PEQ_BAND7_SET_RR:
            Result = ADSP_Y_EqRR_b70L_REL;
            break;
            
        case PEQ_BAND8_SET_FL:
            Result = ADSP_Y_EqFL_b80L_REL;
            break;
        case PEQ_BAND8_SET_FR:
            Result = ADSP_Y_EqFR_b80L_REL;
            break;
        case PEQ_BAND8_SET_RL:
            Result = ADSP_Y_EqRL_b80L_REL;
            break;
        case PEQ_BAND8_SET_RR:
            Result = ADSP_Y_EqRR_b80L_REL;
            break;
            
        case PEQ_BAND9_SET_FL:
            Result = ADSP_Y_EqFL_b90L_REL;
            break;
        case PEQ_BAND9_SET_FR:
            Result = ADSP_Y_EqFR_b90L_REL;
            break;
        case PEQ_BAND9_SET_RL:
            Result = ADSP_Y_EqRL_b90L_REL;
            break;
        case PEQ_BAND9_SET_RR:
            Result = ADSP_Y_EqRR_b90L_REL;
            break;
            
        case PEQ_BAND10_SET_FL:
            Result = ADSP_Y_EqFL_b100L_REL;
            break;
        case PEQ_BAND10_SET_FR:
            Result = ADSP_Y_EqFR_b100L_REL;
            break;
        case PEQ_BAND10_SET_RL:
            Result = ADSP_Y_EqRL_b100L_REL;
            break;
        case PEQ_BAND10_SET_RR:
            Result = ADSP_Y_EqRR_b100L_REL;
            break;    
            
        case PEQ_BAND11_SET_FL:
            Result = ADSP_Y_EqFL_b110L_REL;
            break;
        case PEQ_BAND11_SET_FR:
            Result = ADSP_Y_EqFR_b110L_REL;
            break;
        case PEQ_BAND11_SET_RL:
            Result = ADSP_Y_EqRL_b110L_REL;
            break;
        case PEQ_BAND11_SET_RR:
            Result = ADSP_Y_EqRR_b110L_REL;
            break;        
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_SetCrossOver
 * @brief      Set CrossOver
 * @param      Null            
 * @retval     Result
 **********************************************************/
#define SWL_SLOPE   sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope
#define SWR_SLOPE   sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope
#define SWL_ADDR1   Dirana_Calc_SwAddr(SWL_SLOPE,SWR_SLOPE,0)
#define SWL_ADDR2   Dirana_Calc_SwAddr(SWL_SLOPE,SWR_SLOPE,1)
#define SWR_ADDR1   Dirana_Calc_SwAddr(SWL_SLOPE,SWR_SLOPE,2)
#define SWR_ADDR2   Dirana_Calc_SwAddr(SWL_SLOPE,SWR_SLOPE,3)
uint8_t Dirana_SetCrossOver(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_XOVER;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    LHP_ATTRI_STRUCT sTmp;
    uint8_t i;

    switch(sAudio.XoverCtl)
    {
        case XOVER_CTL_DELAY:
            sAudio.XoverDelay = AudioDelay(T200MS);
            sAudio.XoverCtl = XOVER_CTL_MUTE;
            break;
    
	        case XOVER_CTL_MUTE:
            if(0 != sAudio.XoverDelay)
                break;
            if(0x00 == (0x80 & sAudio.XoverMask))
            {
                Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_S_MUTE,SYSTEM_FRONT);
                sAudio.XoverDelay = AudioDelay(T150MS);
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
                if(XOVER_MASK_INIT & sAudio.XoverMask)
                {
                    SubResult = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_GPF67_Enable); 
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
                        sDirana.XoverCoefBuffer[i] = 0x0000;
                    }
                    sDirana.XoverCoefBuffer[1] = 0x0400;
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
                        Dirana_Calc_1stHP(sTmp,sDirana.XoverCoefBuffer);                        
                    }
                    else if(XOVER_SLOPE_12 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
                    {
                        Dirana_Calc_2ndHP(sTmp,sDirana.XoverCoefBuffer);    
                    }
                    else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
                    {
                        Dirana_Calc_3rdHP(sTmp,sDirana.XoverCoefBuffer,0);    
                    }
                    else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
                    {
                        Dirana_Calc_4thHP(sTmp,sDirana.XoverCoefBuffer,0);  
                    }
                }
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT1;
            }
            else
            {
                sAudio.XoverCtl = XOVER_CTL_CALC_REAR1;
                sAudio.XoverMask &= (~XOVER_MASK_FRONT);
            }
            break;
            
        //Set Front HPF 1
        case XOVER_CTL_SET_FRONT1:
            SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_IIR4GPF6_b00L_REL,10,sDirana.XoverCoefBuffer);
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
            sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].CoF];
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
            {
                Dirana_Calc_3rdHP(sTmp,sDirana.XoverCoefBuffer,1);
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT2;
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Slope)
            {
                Dirana_Calc_4thHP(sTmp,sDirana.XoverCoefBuffer,1);  
                sAudio.XoverCtl = XOVER_CTL_SET_FRONT2;
            }
            break;
            
        //Set Front HPF2    
        case XOVER_CTL_SET_FRONT2:
            SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_IIR4GPF6_b10L_REL,10,sDirana.XoverCoefBuffer);
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
                        sDirana.XoverCoefBuffer[i] = 0x0000;
                    }
                    sDirana.XoverCoefBuffer[1] = 0x0400;
                }
                else
                {
	         	sTmp.Gain = sAudioDat.sAdv.sCustomXover[CO_CH_F_HPF].Level - 12;
			if(sTmp.Gain > 0)
				sTmp.Gain = 0 ;
                    sTmp.CoF = Tab_XoverCoF[sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].CoF];
                    if(XOVER_SLOPE_6 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
                    {
                        Dirana_Calc_1stHP(sTmp,sDirana.XoverCoefBuffer);                        
                    }
                    else if(XOVER_SLOPE_12 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
                    {
                        Dirana_Calc_2ndHP(sTmp,sDirana.XoverCoefBuffer);    
                    }
                    else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
                    {
                        Dirana_Calc_3rdHP(sTmp,sDirana.XoverCoefBuffer,0);    
                    }
                    else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
                    {
                        Dirana_Calc_4thHP(sTmp,sDirana.XoverCoefBuffer,0);  
                    }
                }       
                sAudio.XoverCtl = XOVER_CTL_SET_REAR1;
            }
            else
            {
                sAudio.XoverMask &= (~XOVER_MASK_REAR);
                sAudio.XoverCtl = XOVER_CTL_INIT_SWL;
            }
            break;
            
        //Set Rear HPF 1
        case XOVER_CTL_SET_REAR1:
            SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_IIR4GPF7_b00L_REL,10,sDirana.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                if((XOVER_PRESET_FLAT == sAudioDat.sAdv.XoverPreset)
                    || (XOVER_SLOPE_FLAT == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope))
                {
                    sAudio.XoverMask &= (~XOVER_MASK_REAR);
                    sAudio.XoverCtl = XOVER_CTL_INIT_SWL;
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
                        sAudio.XoverCtl = XOVER_CTL_INIT_SWL;
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
                Dirana_Calc_3rdHP(sTmp,sDirana.XoverCoefBuffer,1);
                sAudio.XoverCtl = XOVER_CTL_SET_REAR2;
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_R_HPF].Slope)
            {
                Dirana_Calc_4thHP(sTmp,sDirana.XoverCoefBuffer,1);  
                sAudio.XoverCtl = XOVER_CTL_SET_REAR2;
            }
            break;
            
        //Set Rear HPF2    
        case XOVER_CTL_SET_REAR2:
            SubResult = Dirana_ScratchDataWrite(PrivateID,ADSP_Y_IIR4GPF7_b10L_REL,10,sDirana.XoverCoefBuffer);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.XoverMask &= (~XOVER_MASK_REAR);
                sAudio.XoverCtl = XOVER_CTL_INIT_SWL;
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
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,TmpDat);
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
                    Dirana_Calc_1stLP(sTmp,sDirana.XoverCoefBuffer);                        
                }
                else if(XOVER_SLOPE_12 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Dirana_Calc_2ndLP(sTmp,sDirana.XoverCoefBuffer);    
                }
                else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) //NOTE: 3rd Filter's struction
                {
                    Dirana_Calc_3rdLP_By21(sTmp,sDirana.XoverCoefBuffer,0);    
                }
                else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Dirana_Calc_4thLP(sTmp,sDirana.XoverCoefBuffer,0);  
                }
                sAudio.XoverCtl = XOVER_CTL_SET_SWL1;
            }
            break;

        case XOVER_CTL_SET_SWL1:
            SubResult = Dirana_ScratchDataWrite(PrivateID,SWL_ADDR1,10,sDirana.XoverCoefBuffer);
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
                Dirana_Calc_3rdLP_By21(sTmp,sDirana.XoverCoefBuffer,1);    
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                Dirana_Calc_4thLP(sTmp,sDirana.XoverCoefBuffer,1);  
            }
            sAudio.XoverCtl = XOVER_CTL_SET_SWL2;
            break;

        case XOVER_CTL_SET_SWL2:
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) 
            {
                SubResult = Dirana_ScratchDataWrite(PrivateID,SWL_ADDR2,6,sDirana.XoverCoefBuffer);
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                SubResult = Dirana_ScratchDataWrite(PrivateID,SWL_ADDR2,10,sDirana.XoverCoefBuffer);
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
            SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_EasyP_Index_REL,TmpDat);
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
                    Dirana_Calc_1stLP(sTmp,sDirana.XoverCoefBuffer);                        
                }
                else if(XOVER_SLOPE_12 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Dirana_Calc_2ndLP(sTmp,sDirana.XoverCoefBuffer);    
                }
                else if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) //NOTE: 3rd Filter's struction
                {
                    Dirana_Calc_3rdLP_By21(sTmp,sDirana.XoverCoefBuffer,0);    
                }
                else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
                {
                    Dirana_Calc_4thLP(sTmp,sDirana.XoverCoefBuffer,0);  
                }
                sAudio.XoverCtl = XOVER_CTL_SET_SWR1;
            }
            break;
            
        case XOVER_CTL_SET_SWR1:
            SubResult = Dirana_ScratchDataWrite(PrivateID,SWR_ADDR1,10,sDirana.XoverCoefBuffer);
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
                Dirana_Calc_3rdLP_By21(sTmp,sDirana.XoverCoefBuffer,1);    
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                Dirana_Calc_4thLP(sTmp,sDirana.XoverCoefBuffer,1);  
            }
            sAudio.XoverCtl = XOVER_CTL_SET_SWR2;
            break;
            
        case XOVER_CTL_SET_SWR2:
            if(XOVER_SLOPE_18 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope) 
            {
                SubResult = Dirana_ScratchDataWrite(PrivateID,SWR_ADDR2,6,sDirana.XoverCoefBuffer);
            }
            else if(XOVER_SLOPE_24 == sAudioDat.sAdv.sCustomXover[CO_CH_SW_LPF].Slope)
            {
                SubResult = Dirana_ScratchDataWrite(PrivateID,SWR_ADDR2,10,sDirana.XoverCoefBuffer);
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
/**********************************************************
 * @function    Dirana_CCInit
 * @brief      Initialize Click Clack
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_CCInit(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_CLICKCLACK;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sAudio.ClickClackCtl)
    {
        case OPERATION_0:
            SubResult = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_ClickClack_Disable); 
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ClickClackCtl = OPERATION_1;
            }
            break;

        //Set Control Method: FLAG Driven
        case OPERATION_1:
            //SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_WavTab_UseIOFlag,(int32_t)(CC_CTL_FLAG));
            //if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ClickClackCtl = OPERATION_2;
            }
            break;

        case OPERATION_2:
            //SubResult = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_ClickClack_Enable); 
            //if(SUBLAYER_DONE == SubResult)
            {
                sAudio.ClickClackCtl = OPERATION_3;
            }
            break;

        //Set Click_Clack Position
        case OPERATION_3:
            SubResult = Dirana_DrvSuperPositionGain(PrivateID,P_MIX_EXT_FRONT,(-20));
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
 * @function    Dirana_CCSet
 * @brief      Set Click Clack
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_CCSet(uint8_t Mode)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_CLICKCLACK;
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

    Result = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_WavTab_Control_REL,Temp);

    return (Result);
}
/**********************************************************
 * @function    Dirana_CCEnable
 * @brief      Enable Click Clack
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_CCEnable(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_CLICKCLACK;
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_ClickClack_Enable); 

    return (Result);
}
/**********************************************************
 * @function    Dirana_CCDisable
 * @brief      Disable Click Clack
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_CCDisable(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_INIT_CLICKCLACK;
    uint8_t Result = SUBLAYER_DOING;

    Result = Dirana_EasyProgrammWrite(PrivateID,ADSP_EASYP_ClickClack_Disable); 

    return (Result);
}
/**********************************************************
 * @function    Dirana_SetCrossOver
 * @brief      Set CrossOver
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetUltraBass(void)
{
    DIRANA_DRIVER_TYPE_ENUM PrivateID = DIRANA_IIC_SET_ULTRA_BASS;
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
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_AUB2_Mode_REL,Data);
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
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_AUB2_AGCMaxGain_REL,Data);
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
                if(UBASS_ENABLE == sAudioDat.sAdv.sUltraBass.Setting)
                {
                    Tmp = -3 - sAudioDat.sInfo.UbassTargetLev;
                }
                else
                {
                    Tmp = -15;
                }
                Scaler = powf(10.0,(Tmp / 20.0));
                Data = RoundChange(Scaler * 8388608,1);
                SubResult = Dirana_WriteMemWord(PrivateID,MEM_TYPE_X,ADSP_X_AUB2_TargetLevel_REL,Data);    
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
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
 * @function    Dirana_Calc_Eq
 * @brief      Calc Geq Coefficient
 *          Only For Graphic equalizer
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_Eq(uint8_t Flag,PN_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_FB_2ndPN
 * @brief      Calc Full-Blown 2nd Order Peak/Notch coefficients
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_FB_2ndPN(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_Bass
 * @brief      Calc Bass 2nd Order Peak coefficients
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_Bass(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_Mid
 * @brief      Calc 2nd Order Peak/Notch coefficients
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_Mid(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_Treble
 * @brief      Calc 2nd Order Peak/Notch coefficients
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_Treble(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_LoudBoost
 * @brief      Calc 
 * @param      Null            
 * @retval     Result
 **********************************************************/
uint16_t Dirana_Calc_LoudBoost(uint8_t Type, uint8_t Level)
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
 * @function    Dirana_Calc_LDB
 * @brief      Calc Loudness Bass(Boost) Filter: 1st shelving LPF
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_LDB(uint8_t Freq, uint16_t* Result)
{
    float t0,a1b,b0b;
    float Temp;
    uint32_t Coef,b0bHex,a1bHex;
    
    //All Cost 200US!!
    Coef = 8388608;

    //Calc t0 Value
    t0 = cosf((2*PI * Freq) / ASRate);
    Temp = (t0 - 2) * (t0 - 2);
    //Calc a01,a02,a11,a12,b00,b01,b02,b10,b11,b12 Value
    a1b = 1 - (t0 + sqrtf(Temp - 1))/2;
    b0b = 0.5 - a1b;

    //Convert to HEX
    a1bHex = RoundChange(a1b * Coef,1);    
    *Result = (a1bHex & 0xFFF) >> 1;        //Double Precision Convert
    *(Result + 1) = (a1bHex >> 12) & 0xFFF;

    *(Result + 2) = 0;
    *(Result + 3) = 0;
    
    b0bHex = RoundChange(b0b * Coef,1);
    *(Result + 4) = (b0bHex & 0xFFF) >> 1;    
    *(Result + 5) = (b0bHex >> 12) & 0xFFF;

    *(Result + 6) = 0;
    *(Result + 7) = 0;    
}
/**********************************************************
 * @function    Dirana_Calc_LDT
 * @brief      Calc Loudness Treble(Boost) Filter: 2nd BandPF; Q = 1.0
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_LDT(uint16_t Freq,float Q, uint16_t* Result)
{
    float t0,b0t,b1t,b2t,a1t,a2t;
    float Temp;
    uint32_t Coef,b0tHex,b1tHex,b2tHex,a1tHex,a2tHex;
    
    //All Cost 200US!!
    Coef = 2047;

    //Calc t0 Value
    t0 = (2*PI * Freq) / ASRate;
    Temp = t0 / (2 * Q);
    //Calc a01,a02,a11,a12,b00,b01,b02,b10,b11,b12 Value
    a2t = -0.5 * (1 - Temp) / (1 + Temp);
    b0t = (0.5 + a2t) / 2;
    a1t = (0.5 - a2t) * cosf(t0);
    b2t = -b0t;
    
    //Convert to HEX
    a1tHex = RoundChange(a1t * Coef,0);    
    *Result = a1tHex & 0xFFF;  

    a2tHex = RoundChange(a2t * Coef,0);    
    *(Result + 1) = a2tHex & 0xFFF;        //Double Precision Convert
   
    b0tHex = RoundChange(b0t * Coef,0);
    *(Result + 2) = b0tHex & 0xFFF;    

    *(Result + 3) = 0x0000;    
    
    b2tHex = RoundChange(b2t * Coef,0);
    *(Result + 4) = b2tHex & 0xFFF;        
}
/**********************************************************
 * @function    Dirana_Calc_SupSmoothAR
 * @brief      Calc Smooth Superposition attack/release time
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_SupSmoothAR(uint8_t Time,uint16_t* Result)
{
    float filta,filtb;
    uint32_t Coef,FiltaHex,FiltbHex;

    Coef = 2047;

    filta = expf(-3 / (Time * ASRate / 1000));
    filtb = 1 - filta;

    FiltaHex = RoundChange(filta * Coef,0);
    *Result = FiltaHex & 0xFFF;   
    FiltbHex = RoundChange(filtb * Coef,0);
    *(Result + 1) = FiltbHex & 0xFFF;       
}
/**********************************************************
 * @function    Dirana_Calc_Chime_SinWave
 * @brief      Calc Chime Sine Wave ...
 * @param      Null            
 * @retval     Result
 **********************************************************/
void Dirana_Calc_Chime_SinWave(uint16_t Freq,uint16_t* Result)
{
    float a1b;
    float Temp;
    uint32_t Coef,a1bHex;
    
    //4 Sine vs Triangular
    Coef = 8388608;

    //Calc t0 Value
    a1b = cosf((2*PI * Freq) / ASRate);
    
    a1bHex = RoundChange(a1b * Coef,1);       //Double Precision Convert
    *Result = (a1bHex & 0xFFF) >> 1;                 //b0L
    *(Result + 1) = (a1bHex >> 12) & 0xFFF;      //b0H
}
/**********************************************************
 * @function    Dirana_Calc_1stLP
 * @brief      Calculate 2nd order IIR as 1st order LP
 * @param     LHP_ATTRI_STRUCT sFilter  
 *                  uint16_t* Result
 * @retval     NULL
 **********************************************************/
void Dirana_Calc_1stLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_1stHP
 * @brief      Calculate 2nd order IIR as 1st order HP
 * @param     LHP_ATTRI_STRUCT sFilter  
 *                  uint16_t* Result
 * @retval     NULL
 **********************************************************/
void Dirana_Calc_1stHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_2ndPN
 * @brief      Calculate 2nd order IIR as 2nd Peak/notch Filter
 * @param     PN_ATTRI_STRUCT sFilter  
 *                  uint16_t* Result
 * @retval     NULL
 **********************************************************/
void Dirana_Calc_2ndPN(PN_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_2ndLP
 * @brief      Calc 2nd order Low Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
 * @retval     Result
 **********************************************************/
void Dirana_Calc_2ndLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_2ndHP
 * @brief      Calc 2nd order High Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
 * @retval     Result
 **********************************************************/
void Dirana_Calc_2ndHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result)
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
 * @function    Dirana_Calc_3rdLP
 * @brief      Calc 3rd order Low Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
  *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Dirana_Calc_3rdLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
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
 * @function    Dirana_Calc_3rdHP
 * @brief      Calc 3rd order High Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
 *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Dirana_Calc_3rdHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
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
 * @function    Dirana_Calc_4thLP
 * @brief      Calc 4th order Low Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
  *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Dirana_Calc_4thLP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
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
 * @function    Dirana_Calc_4thHP
 * @brief      Calc 4th order High Pass Filter  Cofficient
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
  *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Dirana_Calc_4thHP(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
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
 * @function    Dirana_Calc_3rdLP_By21
 * @brief      Calc 3rd order Low Pass Filter  Cofficient
 *                  the 3rd order LP is a 2nd cascaded with 1st
 * @param      LHP_ATTRI_STRUCT sFilter
 *                  uint16_t* Result
  *                  uint8_t Mode
 * @retval     Result
 **********************************************************/
void Dirana_Calc_3rdLP_By21(LHP_ATTRI_STRUCT sFilter, uint16_t* Result, uint8_t Mode)
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
/**********************************************************
 * @function    Dirana_Calc_SwAddr
 * @brief      Calc Sw Eq Addr
 * @param      uint8_t SwL
 *                  uint8_t SwR
  *                 uint8_t Mode
 * @retval     Result
 **********************************************************/
uint16_t Dirana_Calc_SwAddr(uint8_t SwL, uint8_t SwR, uint8_t Mode)
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


#endif//D_AUDIO_ASP_DIRANA

