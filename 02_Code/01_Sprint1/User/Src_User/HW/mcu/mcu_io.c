#define _APPIO_C_
#include "..\..\config\inc.h"



#pragma pack(1)
typedef struct{
    
    uint8_t cTimer;              //扫描计时器
    union{
        struct{
            bit_t cCurrVal   :1;   //当前状态
            bit_t bEnScan    :1;   //是否参与被扫描
            bit_t bAction    :1;   //状态发生变化
        }tValue;
        uint8_t cValue;
    }uIOValue;
    tPIN_PHYSICAL_MAP* p_tMap;
}tIO_PIN_CB;



#pragma pack(1)
typedef struct{
    uint8_t bScan;
    uint8_t cTimer;
    uint8_t cIdx,cTmpIdx;               //区域序号
    uint8_t cCurrIdx,cLastIdx;  //有效值序号
    tADC_PHYSICAL_MAP* p_tMap;
}tIO_ADC_CB;




#pragma pack(1)
typedef struct{
    uint8_t cTiming;
    uint8_t bScan;
    uint8_t cCurrIdx,cTargIdx;
    tPWM_PHYSICAL_MAP* p_tMap;
}tIO_PWM_CB;


#pragma pack(1)
typedef struct{ 
    eIO_TYPE         eType;
    uint8_t          cIOID;
}tIO_MAP;


/*All 128 IO define*/
const tIO_MAP lc_atLogic2PinMap[] ={
   { IO_TYPE_PIN, IO_PIN_AMP_STANDBY} ,  /* IO_IDX_AMP_STANDBY , P1_0*/
   { IO_TYPE_PIN, IO_PIN_AMP_MUTE} ,  /* IO_IDX_AMP_MUTE , P1_1*/
   { IO_TYPE_PWM, IO_PWM_PM_SNT_FREQ} ,  /* IO_IDX_PM_SNT_FREQ , P0_0*/
   { IO_TYPE_PIN, IO_PIN_CAN0_STB} ,  /* IO_IDX_CAN1_STB , P0_1*/
   { IO_TYPE_INT, IO_INT_LOW_POWER} ,  /* IO_IDX_LOW_POWER , P0_2*/
   { IO_TYPE_PIN, IO_PIN_ACC_WAKE} ,    /* IO_IDX_ACC_WAKE , P0_3*/
   { IO_TYPE_INT, IO_INT_RDS_INT0} ,  /* IO_IDX_RDS_INT0 , P0_4*/
   { IO_TYPE_PIN, IO_PIN_DSP_CLICK} ,  /* IO_IDX_DSP_CLICK , P0_5*/
   { IO_TYPE_PIN, IO_PIN_ILL_WAKE} ,  /* IO_IDX_ILL_WAKE , P0_6*/ //snake20160819
   { IO_TYPE_I2C, IO_I2C_MCU_SDA1} ,  /* IO_IDX_MCU_SDA1 , P4_0*/
   { IO_TYPE_I2C, IO_I2C_MCU_SCL1} ,  /* IO_IDX_MCU_SCL1 , P4_1*/
   { IO_TYPE_PIN, IO_PIN_CAN1_STB} ,  /* IO_IDX_CAN1_STB , P4_2*/
   { IO_TYPE_UART, IO_UART_UART0_TXD} ,  /* IO_IDX_UART0_TXD , P3L_0*/
   { IO_TYPE_UART, IO_UART_UART0_RXD} ,  /* IO_IDX_UART0_RXD , P3L_1*/
   { IO_TYPE_NUSE, IO_NUSE_SCI_MUX} ,  /* IO_IDX_SCI_MUX , P3L_2*/
   { IO_TYPE_CAN, IO_CAN_CAN1_TXD} ,  /* IO_IDX_CAN1_TXD , P3L_3*/
   { IO_TYPE_CAN, IO_CAN_CAN1_RXD} ,  /* IO_IDX_CAN1_RXD , P3L_4*/
   { IO_TYPE_PWM, IO_PWM_TFT_CTRL},  /* IO_IDX_TFT_EN , P3L_5*/
   { IO_TYPE_CAN, IO_CAN_CAN0_TXD} ,  /* IO_IDX_CAN0_TXD , P3L_6*/
   { IO_TYPE_CAN, IO_CAN_CAN0_RXD} ,  /* IO_IDX_CAN0_RXD , P3L_7*/
   { IO_TYPE_I2C, IO_I2C_MCU_SDA0} ,  /* IO_IDX_UART2_TXD , P3H_0*/
   { IO_TYPE_I2C, IO_I2C_MCU_SCL0} ,  /* IO_IDX_UART2_RXD , P3H_1*/
   { IO_TYPE_PWM, IO_PWM_KEY_LED} ,  /* IO_IDX_KEY_PWM , P5_0*/
   //{ IO_TYPE_PWM, IO_PWM_CAR_SPEED}, /* IO_IDX_SPEED_PULSE , P5_1*/
   { IO_TYPE_PWM, IO_PWM_PANEL_LED2} ,  /* IO_IDX_PANEL_LED2 , P5_1*/
   //{ IO_TYPE_PIN, IO_PIN_MCU2DR_PWR} ,  /* IO_IDX_MCU2DR_PWR , P5_2*/
   { IO_TYPE_PWM, IO_PWM_PANEL_LED1} ,  /* IO_IDX_PANEL_LED1 , P5_2*/
   { IO_TYPE_SPI, IO_SPI_CAYMAN_MISO} ,  /* IO_IDX_CAYMAN_MISO , P5_3*/
   { IO_TYPE_SPI, IO_SPI_CAYMAN_MOS1} ,  /* IO_IDX_CAYMAN_MOS1 , P5_4*/
   { IO_TYPE_SPI, IO_SPI_CAYMAN_SCK} ,    /* IO_IDX_CAYMAN_SCK , P5_5*/
   { IO_TYPE_PIN, IO_PIN_DVD_POWER} ,  /* IO_IDX_DVD_POWER , P6L_0*/
   { IO_TYPE_PIN, IO_PIN_APU_BCK_POWER} ,  /* IO_IDX_APU_BCK_POWER , P6L_1*/
   { IO_TYPE_PIN, IO_PIN_DSP_FAST_MUTE} ,  /* IO_IDX_DSP_FAST_MUTE , P6L_2*/
   { IO_TYPE_PIN, IO_PIN_MCU2AV_SW2} ,  /* IO_IDX_MCU2AV_SW2 , P6L_3*/
   { IO_TYPE_PIN, IO_PIN_MCU2AV_SW1} ,  /* IO_IDX_MCU2AV_SW1 , P6L_4*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_0} ,  /* IO_IDX_RESV_0 , P6L_5*/
   { IO_TYPE_PIN, IO_PIN_AMP_CLIP} ,  /* IO_IDX_AMP_CLIP , P6L_6*/
   { IO_TYPE_PIN, IO_PIN_AK4220_RESET} ,  /* IO_IDX_AK4220_RESET , P6L_7*/
   { IO_TYPE_PIN, IO_PIN_DS927A_PWR} ,  /* IO_IDX_DS927A_PWR , P6H_0*/
   { IO_TYPE_I2C, IO_I2C_RES_SDA} ,  /* IO_IDX_RES_SDA , P6H_1*/
   { IO_TYPE_PIN, IO_PIN_7186_BOOT0} ,  /* IO_IDX_RES_SCL , P6H_2*/// { IO_TYPE_I2C, IO_I2C_RES_SCL} ,  /* IO_IDX_RES_SCL , P6H_2*/
   { IO_TYPE_PIN, IO_PIN_7186_BOOT1} ,  /* IO_IDX_IR_IN , P6H_3*///{ IO_TYPE_TIP, IO_TIP_IR_IN} ,  /* IO_IDX_IR_IN , P6H_3*/
   { IO_TYPE_TIP, IO_TIP_OWC} ,  /* IO_IDX_OWC , P6H_4*/
   { IO_TYPE_PIN, IO_PIN_DNL_VPP} ,  /* IO_IDX_DNL_VPP , P6H_5*/
   { IO_TYPE_PIN, IO_PIN_TEST1} ,  /* IO_IDX_TEST1 , P6H_6*/
   { IO_TYPE_PIN, IO_PIN_CAYMAN_RESET} ,  /* IO_IDX_CAYMAN_RESET , P6H_7*/
   { IO_TYPE_UART, IO_UART_UART3_RXD} ,  /* IO_IDX_UART3_RXD , P8_0*/
   { IO_TYPE_UART, IO_UART_UART3_TXD} ,  /* IO_IDX_UART3_TXD , P8_1*/
   { IO_TYPE_I2C, IO_I2C_MCU_SDA2} ,  /* IO_IDX_MCU_SDA2 , P9L_0*/
   { IO_TYPE_I2C, IO_I2C_MCU_SCL2} ,  /* IO_IDX_MCU_SCL2, P9L_1*/
   { IO_TYPE_PWM, IO_PWM_FAN_CTRL} ,  /* IO_IDX_FAN_CTRL , P9L_2*/
   { IO_TYPE_PIN, IO_PIN_CAN0_ERR},  /* IO_IDX_CAN0_ERR , P9L_3*/
   { IO_TYPE_PIN, IO_PIN_APU_LOWPWR} ,  /* IO_IDX_APU_LOWPWR , P9L_4*/
   { IO_TYPE_PIN, IO_PIN_CPU_STATE} ,  /* IO_IDX_RADAR_ID , P9L_5*/
   { IO_TYPE_PIN, IO_PIN_RADAR_DATA} ,    /* IO_IDX_RADAR_DATA , P9L_6*/
   { IO_TYPE_SPI, IO_SPI_APU_MISO} ,  /* IO_IDX_APU_MISO , P9L_7*/
   { IO_TYPE_SPI, IO_SPI_APU_MOSI} ,  /* IO_IDX_APU_MOSI , P9H_0*/
   { IO_TYPE_SPI, IO_SPI_APU_SCK} ,  /* IO_IDX_APU_SCK , P9H_1*/
   { IO_TYPE_SPI, IO_SPI_MCU_MISO} ,  /* IO_IDX_MCU_MISO , P9H_2*/
   { IO_TYPE_SPI, IO_SPI_MCU_MOSI} ,  /* IO_IDX_MCU_MOSI , P9H_3*/
   { IO_TYPE_SPI, IO_SPI_MCU_SCK} ,  /* IO_IDX_MCU_SCK , P9H_4*/
   { IO_TYPE_PIN, IO_PIN_VOL_A} ,  /* IO_IDX_VOL_A , P9H_5*/
   { IO_TYPE_PIN, IO_PIN_TUNE_A} ,    /* IO_IDX_TUNE_A , P9H_6*/
   { IO_TYPE_PIN, IO_PIN_NAVI_AUDIO} ,  /* IO_IDX_NAVI_AUDIO , P9H_7*/
   { IO_TYPE_PIN, IO_PIN_MCU2DSP_PWR} ,    /* IO_IDX_MCU2DSP_PWR , PCD_0*/
   { IO_TYPE_PIN, IO_PIN_DTV_AUX_SEL} ,  /* IO_IDX_DTV_AUX_SEL , PCD_1*/
   { IO_TYPE_PIN, IO_PIN_VOL_B} ,  /* IO_IDX_VOL_B , PCD_2*/
   { IO_TYPE_PIN, IO_PIN_TUNE_B} ,    /* IO_IDX_TUNE_B , PCD_3*/
   { IO_TYPE_PIN, IO_PIN_DVD_AUX_RGB} ,  /* IO_IDX_DVD_AUX_RGB , PCS_0*/
   { IO_TYPE_PIN, IO_PIN_MHL_AUX_SEL} ,  /* IO_IDX_RESV_2 , PCS_1*/
   { IO_TYPE_PIN, IO_PIN_USB_SW2} ,  /* IO_IDX_RESV_3 , PCS_2*/
   { IO_TYPE_PIN, IO_PIN_USB_SW1} ,  /* IO_IDX_RESV_4 , PCS_3*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_5} ,  /* IO_IDX_RESV_5 , PCM_0*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_6} ,  /* IO_IDX_RESV_6 , PCM_1*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_7} ,  /* IO_IDX_RESV_7 , PCM_2*/
   { IO_TYPE_PIN, IO_PIN_USB_HOST} ,  /* IO_IDX_USB_HOST , PCM_3*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_9} ,  /* IO_IDX_RESV_9 , PCM_4*/
   { IO_TYPE_PIN, IO_PIN_APU_CS} ,    /* IO_IDX_APU_CS , PCM_5*/
   { IO_TYPE_PIN, IO_PIN_SYS_5V} ,    /* IO_IDX_SYS_5V , PCS_4*/
   { IO_TYPE_PIN, IO_PIN_APU_RESET} ,  /* IO_IDX_APU_RESET , PCS_5*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_10} ,  /* IO_IDX_RESV_10 , PCS_6*/
   { IO_TYPE_PIN, IO_PIN_CAN0_WAKE} ,  /* IO_IDX_CAN0_WAKE , PCS_7*/
   { IO_TYPE_PIN, IO_PIN_I2S_SEL} ,  /* IO_IDX_I2S_SEL , PCT_0*/
   { IO_TYPE_PIN, IO_PIN_APU_POWER} ,  /* IO_IDX_APU_POWER , PCT_1*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_12} ,  /* IO_IDX_RESV_12 , PCT_2*/
   { IO_TYPE_PIN, IO_PIN_8836A_PWR} ,  /* IO_IDX_8836A_PWR , PCT_3*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_13} ,  /* IO_IDX_RESV_13 , PCT_4*/
   { IO_TYPE_PIN, IO_PIN_PHANTOM_POWER1} ,    /* IO_IDX_PHANTOM_POWER1 , PCT_5*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_14} ,  /* IO_IDX_RESV_14 , PCT_6*/
   { IO_TYPE_PIN, IO_PIN_PHANTOM_POWER2} ,    /* IO_IDX_PHANTOM_POWER2 , PCT_7*/
   { IO_TYPE_PIN, IO_PIN_REAR_MUTE} ,  /* IO_IDX_REAR_MUTE , PDLL_0*/
   { IO_TYPE_PIN, IO_PIN_CAYMAN_CS} ,  /* IO_IDX_CAYMAN_CS , PDLL_1*/
   { IO_TYPE_PIN, IO_PIN_DSP_RESET} ,  /* IO_IDX_DSP_RESET , PDLL_2*/
  { IO_TYPE_PIN, IO_PIN_TFT_POWER_EN} ,  /* IO_IDX_TFT_POWER_EN , PDLL_3*/// { IO_TYPE_PIN, IO_PIN_LINE_MUTE} ,  /* IO_IDX_LINE_MUTE , PDLL_3*/
   { IO_TYPE_PIN, IO_PIN_LOCAL_ACC} ,  /* IO_IDX_LOCAL_ACC , PDLL_4*/
   { IO_TYPE_NUSE, IO_NUSE_FLMD1} ,  /* IO_IDX_FLMD1 , PDLL_5*/
   { IO_TYPE_PIN, IO_PIN_DISC_LED} ,  /* IO_IDX_DISC_LED , PDLL_6*/
   { IO_TYPE_PIN, IO_PIN_POWER_LED} ,  /* IO_IDX_POWER_LED , PDLL_7*/
   { IO_TYPE_PIN, IO_PIN_TFT_3V3} ,  /* IO_IDX_TFT_3V3 , PDLH_0*/
   { IO_TYPE_PIN, IO_PIN_TFT_VGL} ,  /* IO_IDX_TFT_VGL , PDLH_1*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_16} ,  /* IO_IDX_RESV_16 , PDLH_2*/
   { IO_TYPE_NUSE, IO_NUSE_RESV_17} ,  /* IO_IDX_RESV_17 , PDLH_3*/
   { IO_TYPE_PIN, IO_PIN_AVM_DET} ,  /* IO_PIN_AVM_DET , PDLH_4*/
   { IO_TYPE_PIN, IO_PIN_SWC_SEL1} ,  /* IO_IDX_SWC_SEL1 , PDLH_5*/
   { IO_TYPE_PIN, IO_PIN_SWC_SEL2} ,  /* IO_IDX_SWC_SEL2 , PDLH_6*/
   { IO_TYPE_PIN, IO_PIN_REVERSE_OUT} ,  /* IO_IDX_REVERSE_OUT , PDLH_7*/
   { IO_TYPE_PIN, IO_PIN_SLEEP_5V} ,  /* IO_IDX_SLEEP_5V , PDH_0*/
   { IO_TYPE_PIN, IO_PIN_REAR_LVDS_PND} ,    /* IO_IDX_REAR_LVDS_PND , PDH_1*/
   { IO_TYPE_PIN, IO_PIN_DSP_AVDET} ,  /* IO_IDX_DSP_AVDET , PDH_2*/
   { IO_TYPE_PIN, IO_PIN_POWER_CTRL1} ,  /* IO_IDX_POWER_CTRL1 , PDH_3*/
   { IO_TYPE_PIN, IO_PIN_POWER_CTRL2} ,  /* IO_IDX_POWER_CTRL2 , PDH_4*/
   { IO_TYPE_PIN, IO_PIN_POWER_EN} ,  /* IO_IDX_POWER_EN , PDH_5*/
   { IO_TYPE_PIN, IO_PIN_CAN0_EN} ,  /* IO_IDX_CAN0_EN , PDH_6*/
   { IO_TYPE_PIN, IO_PIN_AUX_DET} ,  /* IO_IDX_AUX_DET , PDH_7*/
   #ifdef D_ILL_ADC_CHECK
   { IO_TYPE_ADC, IO_ADC_ILL_DET} ,  /* IO_IDX_ILL_DET , P7H_7*/
   #else
   { IO_TYPE_PIN, IO_PIN_ILL_DET} ,  /* IO_IDX_ILL_DET , P7H_7*/
   #endif
   { IO_TYPE_PIN, IO_PIN_DISC_IN_DET} ,  /* IO_IDX_DISC_IN_DET , P7H_6*/
   { IO_TYPE_PIN, IO_PIN_7186_RESET_DUT1} ,  /* IO_IDX_7186_RESET_DUT1 , P7H_5*/
   { IO_TYPE_PIN, IO_PIN_REVERSE_DET} ,  /* IO_IDX_REVERSE_DET , P7H_4*/
   { IO_TYPE_PIN, IO_PIN_TEL_MUTE_DET} ,  /* IO_IDX_TEL_MUTE_DET , P7H_3*/
   { IO_TYPE_PIN, IO_PIN_PARKING_DET} ,  /* IO_IDX_PARKING_DET , P7H_2*/
   { IO_TYPE_PIN, IO_PIN_7186_DUT_BOOT_EN1} ,  /* IO_IDX_7186_DUT_BOOT_EN1 , P7H_1*/// { IO_TYPE_PIN, IO_PIN_REAR_LVDS_EN} ,  /* IO_IDX_REAR_LVDS_EN , P7H_1*/
   { IO_TYPE_PIN, IO_PIN_DS927B_PWR} ,  /* IO_IDX_DS927B_PWR , P7H_0*/
   { IO_TYPE_ADC, IO_ADC_BATTERY_DET} ,  /* IO_IDX_BATTERY_DET , P7L_7*/
   { IO_TYPE_PIN, IO_PIN_MODULE_DET} ,    /* IO_IDX_MODULE_DET , P7L_6*/
   { IO_TYPE_PIN, IO_PIN_8836B_PWR} ,  /* IO_IDX_8836B_PWR , P7L_5*/
   { IO_TYPE_ADC, IO_ADC_TEMP_DET} ,  /* IO_IDX_TEMP_DET , P7L_4*/
   { IO_TYPE_ADC, IO_ADC_SWC1_DET} ,  /* IO_IDX_SWC1_DET , P7L_3*/
   { IO_TYPE_ADC, IO_ADC_SWC2_DET} ,  /* IO_IDX_SWC2_DET , P7L_2*/
   { IO_TYPE_ADC, IO_ADC_KEY1_DET} ,  /* IO_IDX_KEY1_DET , P7L_1*/
   { IO_TYPE_ADC, IO_ADC_KEY2_DET} ,  /* IO_IDX_KEY2_DET , P7L_0*/  
};
#if D_DEBUG_IO && D_PRINT_EN

typedef struct{
    uint8_t bOut;
    char_t* p_tName;
}tIO_NAME_OUT;

const tIO_NAME_OUT lc_atIONameTab[] = {
     {1  ,"AMP_STANDBY>P1_0"},
     {1  ,"AMP_MUTE>P1_1"},
     {1  ,"PM_SNT_FREQ>P0_0"},
     {1  ,"CAN0_STB>P0_1"},
     {1  ,"LOW_POWER>P0_2"},
     {1  ,"CAYMAN_SPI_INT>P0_3"},
     {1  ,"RDS_INT0>P0_4"},
     {1  ,"DSP_CLICK>P0_5"},
     {1  ,"RDS_INT2>P0_6"},
     {1  ,"MCU_SDA0>P4_0"},
     {1  ,"MCU_SCL0>P4_1"},
     {1  ,"CAN2_STB>P4_2"},
     {1  ,"UART0_TXD>P3L_0"},
     {1  ,"UART0_RXD>P3L_1"},
     {1  ,"SCI_MUX>P3L_2"},
     {1  ,"CAN1_TXD>P3L_3"},
     {1  ,"CAN1_RXD>P3L_4"},
     {1  ,"TFT_EN>P3L_5"},
     {1  ,"CAN0_TXD>P3L_6"},
     {1  ,"CAN0_RXD>P3L_7"},
     {1  ,"UART2_TXD>P3H_0"},
     {1  ,"UART2_RXD>P3H_1"},
     {1  ,"KEY_PWM>P5_0"},
     {1  ,"KEY_RLED>P5_1"},
     {1  ,"KEY_GLED>P5_2"},
     {1  ,"CAYMAN_MISO>P5_3"},
     {1  ,"CAYMAN_MOS1>P5_4"},
     {1  ,"CAYMAN_SCK>P5_5"},
     {1  ,"DVD_POWER>P6L_0"},
     {1  ,"APU_BCK_POWER>P6L_1"},
     {1  ,"DSP_FAST_MUTE>P6L_2"},
     {1  ,"D3_INIT_FLG>P6L_3"},
     {1  ,"ACC_DET>P6L_4"},
     {1  ,"RESV_0>P6L_5"},
     {1  ,"AMP_CLIP>P6L_6"},
     {1  ,"AK4220_RESET>P6L_7"},
     {1  ,"LINBUS_WAKEUP>P6H_0"},
     {1  ,"RES_BUS>P6H_1"},
     {1  ,"LINBUS_NSLP>P6H_2"},
     {1  ,"IR_IN>P6H_3"},
     {1  ,"OWC>P6H_4"},
     {1  ,"DNL_VPP>P6H_5"},
     {1  ,"I2C_IRQ>P6H_6"},
     {1  ,"CAYMAN_RESET>P6H_7"},
     {1  ,"UART3_RXD>P8_0"},
     {1  ,"UART3_TXD>P8_1"},
     {1  ,"MCU_SDA1>P9L_0"},
     {1  ,"MCU_SCL1>P9L_1"},
     {1  ,"FAN_CTRL>P9L_2"},
     {1  ,"CAN_ERR>P9L_3"},
     {1  ,"SPEED>P9L_4"},
     {1  ,"RADAR_ID>P9L_5"},
     {1  ,"RADAR_DATA>P9L_6"},
     {0  ,"APU_MISO>P9L_7"},
     {0  ,"APU_MOSI>P9H_0"},
     {0  ,"APU_SCK>P9H_1"},
     {1  ,"MCU_MISO>P9H_2"},
     {1  ,"MCU_MOSI>P9H_3"},
     {1  ,"MCU_SCK>P9H_4"},
     {1  ,"VOL_A>P9H_5"},
     {1  ,"TUNE_A>P9H_6"},
     {0  ,"APU_IRQ>P9H_7"},
     {1  ,"MCU_CS>PCD_0"},
     {1  ,"RESV_1>PCD_1"},
     {1  ,"VOL_B>PCD_2"},
     {1  ,"TUNE_B>PCD_3"},
     {1  ,"DVD_AUX_RGB>PCS_0"},
     {1  ,"RESV_2>PCS_1"},
     {1  ,"RESV_3>PCS_2"},
     {1  ,"RESV_4>PCS_3"},
     {1  ,"RESV_5>PCM_0"},
     {1  ,"RESV_6>PCM_1"},
     {1  ,"RESV_7>PCM_2"},
     {1  ,"RESV_8>PCM_3"},
     {1  ,"RESV_9>PCM_4"},
     {0  ,"APU_CS>PCM_5"},
     {1  ,"SYS_5V>PCS_4"},
     {1  ,"APU_RESET>PCS_5"},
     {1  ,"RESV_10>PCS_6"},
     {1  ,"RESV_11>PCS_7"},
     {1  ,"I2S_SEL>PCT_0"},
     {1  ,"APU_POWER>PCT_1"},
     {1  ,"RESV_12>PCT_2"},
     {1  ,"APU_SLEEP>PCT_3"},
     {1  ,"RESV_13>PCT_4"},
     {1  ,"PHANTOM_POWER1>PCT_5"},
     {1  ,"RESV_14>PCT_6"},
     {1  ,"PHANTOM_POWER2>PCT_7"},
     {1  ,"REAR_MUTE>PDLL_0"},
     {1  ,"CAYMAN_CS>PDLL_1"},
     {1  ,"DSP_RESET>PDLL_2"},
     {1  ,"TFT_POWER_EN>PDLL_3"},
     {1  ,"RESV_15>PDLL_4"},
     {1  ,"FLMD1>PDLL_5"},
     {1  ,"DISC_LED>PDLL_6"},
     {1  ,"POWER_LED>PDLL_7"},
     {1  ,"TFT_3V3>PDLH_0"},
     {1  ,"TFT_VGL>PDLH_1"},
     {1  ,"RESV_16>PDLH_2"},
     {1  ,"RESV_17>PDLH_3"},
     {1  ,"RESV_18>PDLH_4"},
     {1  ,"SWC_SEL1>PDLH_5"},
     {1  ,"SWC_SEL2>PDLH_6"},
     {1  ,"REVERSE_OUT>PDLH_7"},
     {1  ,"SLEEP_5V>PDH_0"},
     {1  ,"APU_STATUS>PDH_1"},
     {1  ,"DSP_AVDET>PDH_2"},
     {1  ,"POWER_CTRL1>PDH_3"},
     {1  ,"POWER_CTRL2>PDH_4"},
     {1  ,"POWER_EN>PDH_5"},
     {1  ,"CAN1_EN>PDH_6"},
     {1  ,"AUX_DET>PDH_7"},
     {1  ,"ILL_DET>P7H_7"},
     {1  ,"DISC_IN_DET>P7H_6"},
     {1  ,"DVD_RESET>P7H_5"},
     {1  ,"REVERSE_DET>P7H_4"},
     {1  ,"TEL_MUTE_DET>P7H_3"},
     {1  ,"PARKING_DET>P7H_2"},
     {1  ,"PHANTOM_DIAG1>P7H_1"},
     {1  ,"PHANTOM_DIAG2>P7H_0"},
     {1  ,"BATTERY_DET>P7L_7"},
     {1  ,"MODULE_DET>P7L_6"},
     {1  ,"LIGHT_SENSOR>P7L_5"},
     {1  ,"TEMP_DET>P7L_4"},
     {1  ,"SWC1_DET>P7L_3"},
     {1  ,"SWC2_DET>P7L_2"},
     {1  ,"KEY1_DET>P7L_1"},
     {1  ,"KEY2_DET>P7L_0"},
     {1  ,"TFT_ENPIN>P35"},
};
#endif
const tPIN_PHYSICAL_MAP lc_atPinHwMapTab[]={

    { 0, PIN_P1_0,       0,0/*snake20160918   0*/,10 ,10,  NULL    },        /* IO_IDX_AMP_STANDBY , P1_0*/
    { 0, PIN_P1_1,       0,0/*snake20160918   0*/,10 ,10,  NULL    },        /* IO_IDX_AMP_MUTE , P1_1*/
  //  { 0, PIN_P0_0,       0,1,10 ,10,  NULL    },        /* IO_IDX_PM_SNT_FREQ , P0_0*/
    { 0, PIN_P0_1,       0,1,10 ,10,  NULL    },        /* IO_IDX_CAN1_STB , P0_1*/
    //{ 0, PIN_P0_2,       0,0,10 ,10,  NULL    },        /* IO_IDX_LOW_POWER , P0_2*/
    { 0, PIN_P0_3,       0,1,10 ,10,  NULL    },        /* IO_IDX_ACC_WAKE , P0_3*/
    //{ 0, PIN_P0_4,       0,0,10 ,10,  NULL    },        /* IO_IDX_RDS_INT0 , P0_4*/
    { 0, PIN_P0_5,       0,0,10 ,10,  NULL    },        /* IO_IDX_DSP_CLICK , P0_5*/
    { 0, PIN_P0_6,       0,0,10 ,10,  NULL    },        /* IO_IDX_ILL_WAKE , P0_6*/
    //{ 0, PIN_P4_0,       0,0,10 ,10,  NULL    },        /* IO_IDX_MCU_SDA1 , P4_0*/
    //{ 0, PIN_P4_1,       0,0,10 ,10,  NULL    },        /* IO_IDX_MCU_SCL1 , P4_1*/
    { 0, PIN_P4_2,       0,1,10 ,10,  NULL    },        /* IO_IDX_CAN1_STB , P4_2*/
    //{ 0, PIN_P3L_0,      0,0,10 ,10,  NULL    },        /* IO_IDX_UART0_TXD , P3L_0*/
    //{ 0, PIN_P3L_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_UART0_RXD , P3L_1*/
    //{ 0, PIN_P3L_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_SCI_MUX , P3L_2*/
    //{ 0, PIN_P3L_3,      0,0,10 ,10,  NULL    },        /* IO_IDX_CAN1_TXD , P3L_3*/
    //{ 0, PIN_P3L_4,      0,0,10 ,10,  NULL    },        /* IO_IDX_CAN1_RXD , P3L_4*/
   // { 0, PIN_P3L_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_TFT_EN_IO , P3L_5*/
   // { 0, PIN_P3L_6,      0,1,10 ,10,  NULL    },        /* IO_IDX_CAN0_TXD , P3L_6*/
    //{ 0, PIN_P3L_7,      0,0,10 ,10,  NULL    },        /* IO_IDX_CAN0_RXD , P3L_7*/
    //{ 0, PIN_P3H_0,      0,0,10 ,10,  NULL    },        /* IO_IDX_UART2_TXD , P3H_0*/
   // { 0, PIN_P3H_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_UART2_RXD , P3H_1*/
    //{ 0, PIN_P5_0,       0,0,10 ,10,  NULL    },        /* IO_IDX_KEY_PWM , P5_0*/
    //{ 0, PIN_P5_1,       0,1,10 ,10,  NULL    },        /* IO_IDX_SPEED_PULSE , P5_1*/
    //{ 0, PIN_P5_2,       0,1,10 ,10,  NULL    },        /* IO_IDX_MCU2DR_PWR , P5_2*/
    //{ 0, PIN_P5_3,       0,0,10 ,10,  NULL    },        /* IO_IDX_CAYMAN_MISO , P5_3*/
    //{ 0, PIN_P5_4,       0,0,10 ,10,  NULL    },        /* IO_IDX_CAYMAN_MOS1 , P5_4*/
    //{ 0, PIN_P5_5,       0,0,10 ,10,  NULL    },        /* IO_IDX_CAYMAN_SCK , P5_5*/
    { 0, PIN_P6L_0,      0,1,10 ,10,  NULL    },        /* IO_IDX_DVD_POWER , P6L_0*/
    { 0, PIN_P6L_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_APU_BCK_POWER , P6L_1*/
    { 0, PIN_P6L_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_DSP_FAST_MUTE , P6L_2*/
    { 0, PIN_P6L_3,      0,0,10 ,10,  NULL    },        /* IO_IDX_MCU2AV_SW2 , P6L_3*/
    { 0, PIN_P6L_4,      0,0,10 ,10,  NULL    },        /* IO_IDX_MCU2AV_SW1 , P6L_4*/
    //{ 0, PIN_P6L_5,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_0 , P6L_5*/
    { 0, PIN_P6L_6,      0,0,10 ,10,  NULL    },        /* IO_IDX_AMP_CLIP , P6L_6*/
    { 0, PIN_P6L_7,      0,0,10 ,10,  NULL    },        /* IO_IDX_AK4220_RESET , P6L_7*/
    { 0, PIN_P6H_0,      0,1,10 ,10,  NULL    },        /* IO_IDX_DS927A_PWR , P6H_0*/
    //{ 0, PIN_P6H_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_RES_SDA , P6H_1*/
   { 0, PIN_P6H_2,      0,1,10 ,10,  NULL    },        /* IO_IDX_7186_BOOT0 , P6H_2*/ // { 0, PIN_P6H_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_RES_SCL , P6H_2*/
   { 0, PIN_P6H_3,      0,1,10 ,10,  NULL    },        /* IO_IDX_7186_BOOT1 , P6H_3*///{ 0, PIN_P6H_3,      0,0,10 ,10,  NULL    },        /* IO_IDX_IR_IN , P6H_3*/
    //{ 0, PIN_P6H_4,      0,0,10 ,10,  NULL    },        /* IO_IDX_OWC , P6H_4*/
    { 0, PIN_P6H_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_DNL_VPP , P6H_5*/
    { 0, PIN_P6H_6,      0,1,10 ,10,  NULL    },        /* IO_IDX_TEST1 , P6H_6*/
    { 0, PIN_P6H_7,      0,0,10 ,10,  NULL    },        /* IO_IDX_CAYMAN_RESET , P6H_7*/
    //{ 0, PIN_P8_0,       0,0,10 ,10,  NULL    },        /* IO_IDX_UART3_RXD , P8_0*/
    //{ 0, PIN_P8_1,       0,0,10 ,10,  NULL    },        /* IO_IDX_UART3_TXD , P8_1*/
    //{ 0, PIN_P9L_0,      0,0,10 ,10,  NULL    },        /* IO_IDX_MCU_SDA2 , P9L_0*/
    //{ 0, PIN_P9L_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_MCU_SCL2, P9L_1*/
    //{ 0, PIN_P9L_2,      0,1,10 ,10,  NULL    },        /* IO_IDX_FAN_CTRL , P9L_2*/
    { 0, PIN_P9L_3,      0,1,10 ,10,  NULL    },        /* IO_IDX_CAN0_ERR , P9L_3*/
    { 0, PIN_P9L_4,      0,1,10 ,10,  NULL    },        /* IO_IDX_APU_LOWPWR , P9L_4*/
    { 0, PIN_P9L_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_CPU_STATE , P9L_5*/
    { 0, PIN_P9L_6,      0,1,10 ,10,  NULL    },        /* IO_IDX_RADAR_DATA , P9L_6*/
    //{ 0, PIN_P9L_7,      0,0,10 ,10,  NULL    },        /* IO_IDX_APU_MISO , P9L_7*/
    //{ 0, PIN_P9H_0,      0,0,10 ,10,  NULL    },        /* IO_IDX_APU_MOSI , P9H_0*/
    //{ 0, PIN_P9H_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_APU_SCK , P9H_1*/
    //{ 0, PIN_P9H_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_MCU_MISO , P9H_2*/
    //{ 0, PIN_P9H_3,      0,0,10 ,10,  NULL    },        /* IO_IDX_MCU_MOSI , P9H_3*/
    //{ 0, PIN_P9H_4,      0,0,10 ,10,  NULL    },        /* IO_IDX_MCU_SCK , P9H_4*/
    { 0, PIN_P9H_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_VOL_A , P9H_5*/
    { 0, PIN_P9H_6,      0,1,10 ,10,  NULL    },        /* IO_IDX_TUNE_A , P9H_6*/
    { 0, PIN_P9H_7,      0,1,10 ,10,  NULL    },        /* IO_IDX_NAVI_AUDIO , P9H_7*/
    { 0, PIN_PCD_0,      0,1,10 ,10,  NULL    },        /* IO_IDX_MCU2DSP_PWR , PCD_0*/
    { 0, PIN_PCD_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_DTV_AUX_SEL , PCD_1*/
    { 0, PIN_PCD_2,      0,1,10 ,10,  NULL    },        /* IO_IDX_VOL_B , PCD_2*/
    { 0, PIN_PCD_3,      0,1,10 ,10,  NULL    },        /* IO_IDX_TUNE_B , PCD_3*/
    { 0, PIN_PCS_0,      0,1,10 ,10,  NULL    },        /* IO_IDX_DVD_AUX_RGB , PCS_0*/
    { 0, PIN_PCS_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_MHL_AUX_SEL , PCS_1*/
    { 0,PIN_PCS_2,      0,1,10 ,10 ,  NULL} ,        /* IO_IDX_USB_SW2 , PCS_2*/
    { 0,PIN_PCS_3,      0,1,10 ,10 ,  NULL} ,        /* IO_IDX_USB_SW1 , PCS_3*/
    //{ 0, PIN_PCM_0,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_5 , PCM_0*/
    //{ 0, PIN_PCM_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_6 , PCM_1*/
    //{ 0, PIN_PCM_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_7 , PCM_2*/
    { 0,PIN_PCM_3,      0,1,10 ,10 ,  NULL} ,        /* IO_IDX_USB_HOST , PCM_3*/
    //{ 0, PIN_PCM_4,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_9 , PCM_4*/
    { 0, PIN_PCM_5,      0,0,10 ,10,  NULL    },        /* IO_IDX_APU_CS , PCM_5*/
    { 0, PIN_PCS_4,      0,1,10 ,10,  NULL    },        /* IO_IDX_SYS_5V , PCS_4*/
    { 0, PIN_PCS_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_APU_RESET , PCS_5*/
    //{ 0, PIN_PCS_6,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_10 , PCS_6*/
    { 0,PIN_PCS_7,      0,1,10 ,10,  NULL } ,        /* IO_IDX_CAN0_WAKE , PCS_7*/
    { 0, PIN_PCT_0,      0,0,10 ,10,  NULL    },        /* IO_IDX_I2S_SEL , PCT_0*/
    { 0, PIN_PCT_1,      0,1,10 ,10,  NULL    },        /* IO_IDX_APU_POWER , PCT_1*/
    //{ 0, PIN_PCT_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_12 , PCT_2*/
    { 0, PIN_PCT_3,      0,1,10 ,10,  NULL    },        /* IO_IDX_8836A_PWR , PCT_3*/
    //{ 0, PIN_PCT_4,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_13 , PCT_4*/
    { 0, PIN_PCT_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_PHANTOM_POWER1 , PCT_5*/
    //{ 0, PIN_PCT_6,      0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_14 , PCT_6*/
    { 0, PIN_PCT_7,      0,1,10 ,10,  NULL    },        /* IO_IDX_PHANTOM_POWER2 , PCT_7*/
    { 0, PIN_PDLL_0,     0,0,10 ,10,  NULL    },        /* IO_IDX_REAR_MUTE , PDLL_0*/
    { 0, PIN_PDLL_1,     0,0,10 ,10,  NULL    },        /* IO_IDX_CAYMAN_CS , PDLL_1*/
    { 0, PIN_PDLL_2,     0,0,10 ,10,  NULL    },        /* IO_IDX_DSP_RESET , PDLL_2*/
    { 0, PIN_PDLL_3,     0,1,10 ,10,  NULL    },        /* IO_IDX_TFT_POWER_EN , PDLL_3*/
    { 0,PIN_PDLL_4,      0,1, 5,  35,  NULL} ,        /* IO_IDX_LOCAL_ACC , PDLL_4*/
    //{ 0, PIN_PDLL_5,     0,0,10 ,10,  NULL    },        /* IO_IDX_FLMD1 , PDLL_5*/
    { 0, PIN_PDLL_6,     0,1,10 ,10,  NULL    },        /* IO_IDX_DISC_LED , PDLL_6*/
    { 0, PIN_PDLL_7,     0,1,10 ,10,  NULL    },        /* IO_IDX_POWER_LED , PDLL_7*/
    { 0, PIN_PDLH_0,     0,1,10 ,10,  NULL    },        /* IO_IDX_TFT_3V3 , PDLH_0*/
    { 0, PIN_PDLH_1,     0,1,10 ,10,  NULL    },        /* IO_IDX_TFT_VGL , PDLH_1*/
    //{ 0, PIN_PDLH_2,     0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_16 , PDLH_2*/
    //{ 0, PIN_PDLH_3,     0,0,10 ,10,  NULL    },        /* IO_IDX_RESV_17 , PDLH_3*/
    {0, PIN_PDLH_4,     0,0,10 ,10,  NULL } ,        /* IO_IDX_AVM_DET , PDLH_4*/
    { 0, PIN_PDLH_5,     0,1,10 ,10,  NULL    },        /* IO_IDX_SWC_SEL1 , PDLH_5*/
    { 0, PIN_PDLH_6,     0,1,10 ,10,  NULL    },        /* IO_IDX_SWC_SEL2 , PDLH_6*/
    { 0, PIN_PDLH_7,     0,1,10 ,10,  NULL    },        /* IO_IDX_REVERSE_OUT , PDLH_7*/
    { 0, PIN_PDH_0,      0,1,10 ,10,  NULL    },        /* IO_IDX_SLEEP_5V , PDH_0*/
    { 0, PIN_PDH_1,      0,1,10 ,10,  NULL    },        /* IO_IDX_APU_REAR_LVDS_PND , PDH_1*/
    { 0, PIN_PDH_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_DSP_AVDET , PDH_2*/
    { 0, PIN_PDH_3,      0,1,10 ,10,  NULL    },        /* IO_IDX_POWER_CTRL1 , PDH_3*/
    { 0, PIN_PDH_4,      0,1,10 ,10,  NULL    },        /* IO_IDX_POWER_CTRL2 , PDH_4*/
    { 0, PIN_PDH_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_POWER_EN , PDH_5*/
    { 0, PIN_PDH_6,      0,1,10 ,10,  NULL    },        /* IO_IDX_CAN0_EN , PDH_6*/
    { 0, PIN_PDH_7,      0,1,10 ,10,  NULL    },        /* IO_IDX_AUX_DET , PDH_7*/
    { 0, PIN_P7H_7,      0,0,10 ,10,  NULL    },        /* IO_IDX_ILL_DET , P7H_7*/
    { 0, PIN_P7H_6,      0,0,10 ,10,  NULL    },        /* IO_IDX_DISC_IN_DET , P7H_6*/
    { 0, PIN_P7H_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_7186_RESET_DUT1 , P7H_5*/
    { 0, PIN_P7H_4,      0,1,100 ,100,  NULL    },        /* IO_IDX_REVERSE_DET , P7H_4*/
    { 0, PIN_P7H_3,      0,1,10 ,10,  NULL    },        /* IO_IDX_TEL_MUTE_DET , P7H_3*/
    { 0, PIN_P7H_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_PARKING_DET , P7H_2*/
    { 0, PIN_P7H_1,      0,1,10 ,10,  NULL    },        /* IO_IDX_7186_DUT_BOOT_EN1 , P7H_1*/
    { 0, PIN_P7H_0,      0,1,10 ,10,  NULL    },        /* IO_IDX_DS927B_PWR , P7H_0*/
    //{ 0, PIN_P7L_7,      0,0,10 ,10,  NULL    },        /* IO_IDX_BATTERY_DET , P7L_7*/
    { 0, PIN_P7L_6,      0,1,10 ,10,  NULL    },        /* IO_IDX_MODULE_DET , P7L_6*/
    { 0, PIN_P7L_5,      0,1,10 ,10,  NULL    },        /* IO_IDX_8836B_PWR , P7L_5*/
    //{ 0, PIN_P7L_4,      0,0,10 ,10,  NULL    },        /* IO_IDX_TEMP_DET , P7L_4*/
    //{ 0, PIN_P7L_3,      0,0,10 ,10,  NULL    },        /* IO_IDX_SWC1_DET , P7L_3*/
    //{ 0, PIN_P7L_2,      0,0,10 ,10,  NULL    },        /* IO_IDX_SWC2_DET , P7L_2*/
    //{ 0, PIN_P7L_1,      0,0,10 ,10,  NULL    },        /* IO_IDX_KEY1_DET , P7L_1*/
    //{ 0, PIN_P7L_0,      0,0,10 ,10,  NULL    },        /* IO_IDX_KEY2_DET , P7L_0*/
    
};

const uint8_t lc_acADCHwMapTab[] ={

    ADC_CH15,   /* IO_IDX_ILL_DET , P7H_7*/
    ADC_CH7 ,   /* IO_IDX_BATTERY_DET , P7L_7*/
    ADC_CH4 ,   /* IO_IDX_TEMP_DET , P7L_4*/
    ADC_CH3 ,   /* IO_IDX_SWC1_DET , P7L_3*/
    ADC_CH2 ,   /* IO_IDX_SWC2_DET , P7L_2*/
    ADC_CH1 ,   /* IO_IDX_KEY1_DET , P7L_1*/
    ADC_CH0 ,   /* IO_IDX_KEY2_DET , P7L_0*/
};

typedef struct{
    uint32_t lFreq;
    uint8_t  cDuty;
}tPWM_DEF_SET;
const tPWM_DEF_SET lc_atPWMSetMapTab[] ={
    {PWM_KHz(480), 50 },  /* IO_IDX_PM_SNT_FREQ , P0_0*/
    {PWM_Hz(160) , 50 },  /* IO_IDX_KEY_PWM , P5_0*/
    {PWM_Hz(160) , 50 },  /* IO_IDX_PANEL_LED2 , P5_1*/
    {PWM_Hz(160) , 50 },  /* IO_IDX_PANEL_LED1 , P5_2*/
    {PWM_KHz(20) , 50 },  /* IO_IDX_FAN_CTRL , P9L_2*/ 
    //{PWM_Hz(160) , 50 },  /* IO_IDX_SPEED_PULSE , P9L_3*/
    {PWM_KHz(32) , 50 },   /* IO_IDX_TFT_EN_PWM  , P3L_5*/ //snake20160921    1HKz

};

typedef struct{
    tIO_PIN_CB tPin[IO_PIN_N];
    tIO_ADC_CB tADC[IO_ADC_N];
    tIO_PWM_CB tPWM[IO_PWM_N];
}tIO_CTRL_BLOCK;

tIO_CTRL_BLOCK l_tIOCB;

void IO_PinSetDefMap(uint8_t cIdx)
{
    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;
    tIO_PIN_CB* p_tIOCB = &(l_tIOCB.tPin[cIOID]);
    eIO_TYPE eType = lc_atLogic2PinMap[cIdx].eType;
    if(eType == IO_TYPE_PIN)
    {
        p_tIOCB->p_tMap = (tPIN_PHYSICAL_MAP*)&lc_atPinHwMapTab[cIOID];
    }
}

void IO_PinInit(uint8_t cIdx,tPIN_PHYSICAL_MAP* p_tMap)
{

    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;
    tIO_PIN_CB* p_tIOCB = &(l_tIOCB.tPin[cIOID]);
    eIO_TYPE eType = lc_atLogic2PinMap[cIdx].eType;
    if(eType == IO_TYPE_PIN)
    {
        io_print(_T(lc_atIONameTab[cIdx].p_tName));
        io_print(_T("Init IOID:%d,Block:%lx,pin:%d\n",cIOID,(uint32_t)p_tIOCB,p_tMap->cPhyID));
        p_tIOCB->p_tMap = p_tMap;
    }
    PM_UnitPowerSet(PM_UNIT_AUDIO,FALSE);
   
}


void IO_ADCInit(uint8_t cIdx,tADC_PHYSICAL_MAP* p_tMap)
{
    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;
    tIO_ADC_CB* p_tIOCB = &(l_tIOCB.tADC[cIOID]);
    p_tIOCB->p_tMap = p_tMap;
    if(p_tMap)
    {
        p_tIOCB->cCurrIdx = p_tMap->cValidNum;
        p_tIOCB->cLastIdx = p_tMap->cValidNum;
        p_tIOCB->cIdx =p_tMap->cNum;
    }
    
}

void IO_PWMInit(uint8_t cIdx,tPWM_PHYSICAL_MAP* p_tMap)
{
    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;
    tIO_PWM_CB* p_tIOCB = &(l_tIOCB.tPWM[cIOID]);
    p_tIOCB->p_tMap = p_tMap;
    p_tIOCB->cCurrIdx = 0xff;
    p_tIOCB->cTargIdx = 0xff;
}


void IO_Scan_Set(uint8_t cIdx,bool enble)
{
    eIO_TYPE eType = lc_atLogic2PinMap[cIdx].eType;
    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;

    if(cIdx >= IO_IDX_N)return;
    
    if(eType == IO_TYPE_PIN && cIOID < IO_PIN_N)
    {
        
        tIO_PIN_CB* p_tIOCB = &(l_tIOCB.tPin[cIOID]);
        if(p_tIOCB->p_tMap)
        {
            uint8_t cPhyID = p_tIOCB->p_tMap->cPhyID;
            
            uint8_t cValue = p_tIOCB->uIOValue.tValue.cCurrVal;
            if(cValue)p_tIOCB->cTimer = p_tIOCB->p_tMap->cInvalidTime;
            else p_tIOCB->cTimer = p_tIOCB->p_tMap->cValidTime;
            p_tIOCB->uIOValue.tValue.bEnScan = enble;
        }
    }
    else if(eType == IO_TYPE_PWM && cIOID < IO_PWM_N)
    {
        tIO_PWM_CB* p_tIOCB = &(l_tIOCB.tPWM[cIOID]);
        if(p_tIOCB->p_tMap )
        {
            p_tIOCB->bScan = enble;
        }
    }
    else if(eType == IO_TYPE_ADC && cIOID < IO_ADC_N)
    {
        tIO_ADC_CB* p_tIOCB = &(l_tIOCB.tADC[cIOID]);
        if(p_tIOCB->p_tMap )
        {
            p_tIOCB->bScan = enble;
        }
    }
}




//
//扫描过程。检测IO变化。
//返回>1: 正常检测 bit7:检测到状态发生变化 bit0-6:当前状态
//返回0: 不进行检测
//
void IO_Scan(uint8_t cIdx,uint8_t dir)
{
    eIO_TYPE eType = lc_atLogic2PinMap[cIdx].eType;
    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;
    if(cIdx < IO_IDX_N)
    {
        switch(eType)
        {
            case IO_TYPE_PIN:
                if(cIOID < IO_PIN_N)
                {
                    tIO_PIN_CB* p_tIOCB = &(l_tIOCB.tPin[cIOID]);
                
                    uint8_t cPhyID = p_tIOCB->p_tMap->cPhyID;
                    uint8_t bit = INVALID;
                
                    if(/*FALSE == p_tIOCB->uIOValue.tValue.bEnScan||*/ NULL == p_tIOCB->p_tMap)
                    {
                        return;
                    }
                
                    if(p_tIOCB->p_tMap->bSoftPin)
                    {
                        if(p_tIOCB->p_tMap->p_cBuff)
				bit = *(p_tIOCB->p_tMap->p_cBuff);
                    }
                    else 
			{
				bit = v850_get_pin(cPhyID,(ePIN_DIRECTION)dir);
                    	}
                   
                    if(p_tIOCB->cTimer)
                    {
                        p_tIOCB->cTimer --;
                    }
                    else                                 
                    {
                        /*Multy sampling*/
                        if (bit == (p_tIOCB->p_tMap->cValidVal))   
                        {
                            p_tIOCB->uIOValue.tValue.cCurrVal = VALID;     
                        }
                        else 
                        {
                            p_tIOCB->uIOValue.tValue.cCurrVal = INVALID; 
                        }
                            
                        _SendMsgToHMI(MS_SYS_IO_INFO,cIdx,p_tIOCB->uIOValue.tValue.cCurrVal);
                        
                        #if D_DEBUG_IO && D_PRINT_EN
                        if(lc_atIONameTab[cIdx].bOut)
                        {
                            io_print(_T("IO: "));
                            io_print(_T(lc_atIONameTab[cIdx].p_tName));
                            io_print(_T("(%d)  is action to %d in %lx \n",cIdx,bit,OS_GetOsTick()));
                        }
                        #endif
                        
                    }
                    
                    if( bit == (p_tIOCB->p_tMap->cValidVal) 
                        && p_tIOCB->uIOValue.tValue.cCurrVal == VALID ) 
                    {
                        p_tIOCB->cTimer = p_tIOCB->p_tMap->cInvalidTime;   /*Valid --> inValid timing*/
                    }
                    else if( bit != (p_tIOCB->p_tMap->cValidVal) 
                        && p_tIOCB->uIOValue.tValue.cCurrVal == INVALID )
                    {
                        p_tIOCB->cTimer = p_tIOCB->p_tMap->cValidTime;    /*inValid --> Valid timing*/
                    }

                
            
                }
            break;

            case IO_TYPE_ADC:
                if(cIOID < IO_ADC_N)
                {
                    tIO_ADC_CB* p_tIOCB = &(l_tIOCB.tADC[cIOID]);
                    
                    uint8_t cPhyID = lc_acADCHwMapTab[cIOID];
					
                    if(0 == p_tIOCB->bScan)
				return;
                    
                    if(p_tIOCB->p_tMap && p_tIOCB->p_tMap->p_tVal)
                    {
                        uint8_t i,cValidIdx,cNextIdx;
                        bool    bValid = FALSE;
                        uint8_t idx = 0xff;
                        uint8_t val = 0;
                        
                        if(!p_tIOCB->p_tMap->bSoftAdc)
    						val =(uint8_t)(v850_get_adc(cPhyID)>>2);
                        else if(p_tIOCB->p_tMap->p_AdcBuff)
    						val = *(p_tIOCB->p_tMap->p_AdcBuff);
    					
                        for(i = 0; i < p_tIOCB->p_tMap->cNum; i ++)
                        {
                            if(val >= p_tIOCB->p_tMap->p_tVal[i].cVMin
                               && val <= p_tIOCB->p_tMap->p_tVal[i].cVMax)
                            {
                                idx = i;
                                cValidIdx = p_tIOCB->p_tMap->p_tVal[i].cIdx;
                                cNextIdx = p_tIOCB->p_tMap->p_tVal[i].cNextIdx;
                                bValid = p_tIOCB->p_tMap->p_tVal[i].bValid;
                                
                                break;
                            }
                        }
                    
                        if(i < p_tIOCB->p_tMap->cNum)   /*Your table must include all ADC range*/
                        {
                            if(idx != p_tIOCB->cIdx)
                            {
                                p_tIOCB->cIdx = idx;
                                p_tIOCB->cTimer = p_tIOCB->p_tMap->p_tVal[idx].cValidTime;
                                if(bValid)
                                {
                                    p_tIOCB->cCurrIdx = cValidIdx;
                                }
                                else
                                {
                                    if(p_tIOCB->cLastIdx != cValidIdx
                                       && p_tIOCB->cLastIdx != cNextIdx)
                                    {
                                        p_tIOCB->cCurrIdx = cValidIdx;
                                    }
                                }
                                
                            }
            
                            if(p_tIOCB->cTimer)
                            {
                                p_tIOCB->cTimer--;
                            }
                            else
                            {
                                if (p_tIOCB->cCurrIdx != p_tIOCB->cLastIdx)   
                                {
                                    _SendMsgToHMI(MS_SYS_IO_INFO,cIdx,p_tIOCB->cCurrIdx);
                                    p_tIOCB->cLastIdx = p_tIOCB->cCurrIdx;
                                }
                            }
                        }
                                
                        #if  0//D_DEBUG_IO && D_PRINT_EN
                        if(lc_atIONameTab[cIdx].bOut)
                        {
                            io_print(_T("IO: "));
                            io_print(_T(lc_atIONameTab[cIdx].p_tName));
                            io_print(_T("(%d)  is action to %d in %lx \n",cIdx,idx,OS_GetOsTick()));
                        }
                        #endif
                    }
                        
                }
            break;

            case IO_TYPE_PWM:
                if(cIOID < IO_PWM_N)
                {
                    tIO_PWM_CB* p_tIOCB = &(l_tIOCB.tPWM[cIOID]);
                    
                    if(p_tIOCB->bScan && p_tIOCB->p_tMap)
                    {
                        if(p_tIOCB->p_tMap->p_cDuty || p_tIOCB->p_tMap->p_lFreq)
                        {
                            if(0 == p_tIOCB->cTiming)
                            {   
                                uint8_t cDuty = lc_atPWMSetMapTab[cIOID].cDuty;
                                uint32_t lFreq = lc_atPWMSetMapTab[cIOID].lFreq;
                                if(p_tIOCB->cCurrIdx != p_tIOCB->cTargIdx)
                                {
                                    if(p_tIOCB->cCurrIdx < p_tIOCB->cTargIdx)
                                    {
                                        p_tIOCB->cCurrIdx ++;
                                    }
                                    else if(p_tIOCB->cCurrIdx > p_tIOCB->cTargIdx)
                                    {
                                        p_tIOCB->cCurrIdx --;
                                    }
                                
                                    if(p_tIOCB->cCurrIdx < p_tIOCB->p_tMap->cNum)
                                    {
                                        if(p_tIOCB->p_tMap->p_cDuty)cDuty = p_tIOCB->p_tMap->p_cDuty[p_tIOCB->cCurrIdx];
                                        if(p_tIOCB->p_tMap->p_lFreq)lFreq  = p_tIOCB->p_tMap->p_lFreq[p_tIOCB->cCurrIdx];
                                        
                                        v850_set_pwm(cIOID,cDuty,lFreq);
                                    }
                                    
                                    p_tIOCB->cTiming = p_tIOCB->p_tMap->cTiming;
                                    #if 0//D_DEBUG_IO && D_PRINT_EN
                                    if(lc_atIONameTab[cIdx].bOut)
                                    {
                                        io_print(_T("IO: "));
                                        io_print(_T(lc_atIONameTab[cIdx].p_tName));
                                        io_print(_T("auto set freq:%ld,duty %d,%lx \n",lFreq,cDuty,OS_GetOsTick()));
                                    }
                                    #endif
                                }
                            }else{
                                p_tIOCB->cTiming --; 
                            }
                        }
                    }
                }
            break;
        }
    }
        
}


/*******************************************************************************
*Get IO State , the stable or wink state .
*
*******************************************************************************/

uint8_t IO_Get(uint8_t cIdx,uint8_t dir,bool bStable)
{
    uint8_t re = INVALID;
    eIO_TYPE eType = lc_atLogic2PinMap[cIdx].eType;
    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;
    
	if(cIdx >= IO_IDX_N)return 0;

    switch(eType)
    {
        case IO_TYPE_PIN:
            if(cIOID < IO_PIN_N)
            {
                tIO_PIN_CB* p_tIOCB = &(l_tIOCB.tPin[cIOID]);
                if(p_tIOCB->p_tMap)
                {
                    if(bStable)
                    {
                        re = p_tIOCB->uIOValue.tValue.cCurrVal;
                    }
                    else
                    { 
                        uint8_t cPhyID = p_tIOCB->p_tMap->cPhyID;
                        uint8_t v = INVALID;
                        if(p_tIOCB->p_tMap->bSoftPin)
                        {
                            if(p_tIOCB->p_tMap->p_cBuff)
					v = *(p_tIOCB->p_tMap->p_cBuff);
                        }
                        else 
                        {
				v = v850_get_pin(cPhyID,(ePIN_DIRECTION)dir);
                        }
                        
                        if(v == p_tIOCB->p_tMap->cValidVal)
				re = VALID;
                    }
                }
            }
        break;

        case IO_TYPE_ADC:
            if(cIOID < IO_ADC_N)
            {
                tIO_ADC_CB* p_tIOCB = &(l_tIOCB.tADC[cIOID]);
                uint8_t cPhyID = lc_acADCHwMapTab[cIOID];
                if(bStable)
                {
                    if(p_tIOCB->p_tMap)
                    {
                        re = p_tIOCB->cLastIdx;
                    }
                }
                else 
                {
                    if(p_tIOCB->p_tMap)
                    {
                        if(!p_tIOCB->p_tMap->bSoftAdc)
    						re =(uint8_t)(v850_get_adc(cPhyID)>>2);
                        else if(p_tIOCB->p_tMap->p_AdcBuff)
    						re = *(p_tIOCB->p_tMap->p_AdcBuff);
                    }
                    else re =(uint8_t)(v850_get_adc(cPhyID)>>2);
                }
            }
        break;

        default:
        break;
    }     
   
    return (re);
}




bool IO_Set(uint8_t cIdx,uint8_t dir,uint8_t cValue)
{
    uint8_t re = 0;
    
    eIO_TYPE eType = lc_atLogic2PinMap[cIdx].eType;
    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;
    
    if(cIdx >= IO_IDX_N)return 0;
    
#if D_DEBUG_IO && D_PRINT_EN
    if(lc_atIONameTab[cIdx].bOut)
    {
        io_print(_T("SetIO: "));
        io_print(_T(lc_atIONameTab[cIdx].p_tName));
        io_print(_T(" (%d-(%d)),Set Valid:%d ,%lx \n",cIdx,dir,cValue,OS_GetOsTick()));
    }
#endif
        
  
    switch(eType)
    {
        case IO_TYPE_PIN:
            if(cIOID < IO_PIN_N)
            {
                tIO_PIN_CB* p_tIOCB = &(l_tIOCB.tPin[cIOID]);
                uint8_t cPhyID = p_tIOCB->p_tMap->cPhyID;
                
                if(p_tIOCB->p_tMap)
                {
                    uint8_t bit = p_tIOCB->p_tMap->cValidVal;
                    if(INVALID == cValue)bit = !bit;
                    if(p_tIOCB->p_tMap->bSoftPin)
                    {
                        if(p_tIOCB->p_tMap->p_cBuff)
                        {
                            *(p_tIOCB->p_tMap->p_cBuff) = bit;
                            re = TRUE;
                        }
                    }
                    else
                    {
                        v850_set_pin(cPhyID,(ePIN_DIRECTION)dir/*,p_tIOCB->p_tMap->boper_drain*/,bit);
                        //bit = v850_get_pin(cPhyID,dir/*,p_tIOCB->p_tMap->boper_drain*/);
                        re = (bit == cValue);
                    }
                }
            }
        break;
        case IO_TYPE_PWM:
            if(cIOID < IO_PWM_N)
            {
                
                tIO_PWM_CB* p_tIOCB = &(l_tIOCB.tPWM[cIOID]);
                uint32_t lFreq = lc_atPWMSetMapTab[cIOID].lFreq;
                
                uint8_t i = cValue;
                re = TRUE;
                if(p_tIOCB->p_tMap )
                { 
                    uint8_t  duty = lc_atPWMSetMapTab[cIOID].cDuty;
                    if(i >= p_tIOCB->p_tMap->cNum)i = 0;  /*此时，入口的cValue是对应PWM的索引*/
                    
                    p_tIOCB->cTargIdx = i;
                    if(!p_tIOCB->bScan)
                    {   
                        p_tIOCB->cCurrIdx = i;
                        if(p_tIOCB->p_tMap->p_cDuty)duty = p_tIOCB->p_tMap->p_cDuty[i];
                        if(p_tIOCB->p_tMap->p_lFreq)lFreq  = p_tIOCB->p_tMap->p_lFreq[i];
                        re = v850_set_pwm(cIOID,duty,lFreq);
                    }
                    
                }
                else{
                    re = v850_set_pwm(cIOID,cValue,lFreq);
                }
            }
        break;
        case IO_TYPE_ADC:
            if(cIOID < IO_ADC_N)
            {
                tIO_ADC_CB* p_tIOCB = &(l_tIOCB.tADC[cIOID]);
                if(p_tIOCB->p_tMap)
                {
                    if(p_tIOCB->p_tMap->bSoftAdc && p_tIOCB->p_tMap->p_AdcBuff)
                    {
                        *(p_tIOCB->p_tMap->p_AdcBuff) = cValue;
                    }
                    else
                    {
                        p_tIOCB->cLastIdx = cValue;
                    }
                    re = TRUE;
                }
            }
        break;
            
        default:
        break;
    }

    return (re);                           /*Setting is successfuly?*/
}


/*******************************************************************************
*Set IO State , and then restart scan .
*
*******************************************************************************/

void IO_ResetState(uint8_t cIdx,uint8_t cValue)
{
    eIO_TYPE eType = lc_atLogic2PinMap[cIdx].eType;
    uint8_t cIOID = lc_atLogic2PinMap[cIdx].cIOID;

    if(cIdx >= IO_IDX_N)return;
    
    switch(eType)
    {
        case IO_TYPE_ADC:
            if(cIOID < IO_ADC_N)
            {
                tIO_ADC_CB* p_tIOCB = &(l_tIOCB.tADC[cIOID]);
                if( p_tIOCB->p_tMap)
                {
                    uint8_t idx = p_tIOCB->cCurrIdx;
                    p_tIOCB->cCurrIdx = p_tIOCB->p_tMap->cValidNum;
                    p_tIOCB->cLastIdx = p_tIOCB->p_tMap->cValidNum;
                    p_tIOCB->cIdx = p_tIOCB->p_tMap->cNum;
                    if(p_tIOCB->p_tMap->p_tVal)
				p_tIOCB->cTimer = p_tIOCB->p_tMap->p_tVal[cIdx].cValidTime;
                }
            }
        break;
        case IO_TYPE_PIN:
            if(cIOID < IO_PIN_N)
            {
                uint8_t cTimer = 0;
                
                tIO_PIN_CB* p_tIOCB = &(l_tIOCB.tPin[cIOID]);
                
                
                p_tIOCB->uIOValue.tValue.cCurrVal = cValue;
                if(p_tIOCB->p_tMap)
                {
                    if(cValue)cTimer = p_tIOCB->p_tMap->cInvalidTime;
                    else cTimer = p_tIOCB->p_tMap->cValidTime;
                }
                p_tIOCB->cTimer = cTimer;
            }
        break;
        case IO_TYPE_PWM:
            if(cIOID < IO_PWM_N)
            {
                tIO_PWM_CB* p_tIOCB = &(l_tIOCB.tPWM[cIOID]);
                p_tIOCB->cCurrIdx = 0xff;
                p_tIOCB->cTargIdx = 0xff;
                IO_Set(cIdx,PIN_OUTPUT,cValue);
            }
        break;
    }
}



void IO_Init(void)
{
    uint8_t i;
    
    
    for(i = 0;i < IO_IDX_N;i++)
    {
        IO_PinSetDefMap(i);
        IO_Scan_Set(i,INVALID);

        IO_ResetState(i,INVALID);
    }

    v850_pwm_init();
}

