#ifndef  _APPAIO_H_
#define  _APPAIO_H_

#ifdef _APPIO_C_
#define _APPIO_
#else 
#define _APPIO_    extern
#endif


#if D_DEBUG_IO && D_PRINT_EN
#define io_print(x) x
#else
#define io_print(x)
#endif
typedef enum{
    IO_TYPE_PIN,
    IO_TYPE_ADC,
    IO_TYPE_I2C,
    IO_TYPE_UART,
    IO_TYPE_SPI,
    IO_TYPE_CAN,
    IO_TYPE_PWM,
    IO_TYPE_INT,
    IO_TYPE_TIP,

    IO_TYPE_NUSE,
    IO_TYPE_NUM
}eIO_TYPE;

typedef enum{
    IO_IDX_AMP_STANDBY,   /*P1__0^^ANO0*/
    IO_IDX_AMP_MUTE,      /*P1__1^^ANO1*/
    IO_IDX_PM_SNT_FREQ,   /*P0__0^^TOP61*/
    IO_IDX_CAN0_STB,      /*P0__1^^TOP60*/
    IO_IDX_LOW_POWER,     /*P0__2^^LP_INT*/
    IO_IDX_ACC_WAKE,	/*P0__3^^INTP0-ADTRG*/
    IO_IDX_RDS_INT0,      /*P0__4^^INTP1*/
    IO_IDX_DSP_CLICK,     /*p0__5^^DRST*/
    IO_IDX_ILL_WAKE,      /*P0__6^^INTP3*/
    IO_IDX_MCU_SDA1,      /*P4__0^^SIB0-SDA01*/
    IO_IDX_MCU_SCL1,      /*P4__1^^S0B0-SCL01*/
    IO_IDX_CAN1_STB,      /*P4__2^^SCKB0*/
    IO_IDX_UART0_TXD,     /*P3__0^^TXD0-SOB4*/
    IO_IDX_UART0_RXD,     /*P3__1^^RXD0-SIB4*/
    IO_IDX_SCI_MUX,       /*P3__2^^TIP00-SKB4*/
    IO_IDX_CAN1_TXD,      /*P3__3^^TIP01-CTXD1*/
    IO_IDX_CAN1_RXD,      /*P3__4^^TIP10-CRXD1*/
    IO_IDX_TFT_EN_PWM ,   /*P3__5^^TIP11*/
    IO_IDX_CAN0_TXD,      /*P3__6^^IETX0-CTXD0*/
    IO_IDX_CAN0_RXD,      /*P3__7^^IERX0-CRXD0*/
    IO_IDX_UART2_TXD,     /*P3H__0^^TXD2-SDA0*/
    IO_IDX_UART2_RXD,     /*P3H__1^^RXD2-SCL0*/
    IO_IDX_KEY_PWM,       /*P5__0^^KR0-TOQ01*/
	IO_IDX_PANEL_LED2,// IO_IDX_SPEED_PULSE,      /*P5__1^^KR1-TOQ02*/ // power led
    IO_IDX_PANEL_LED1, //IO_IDX_MCU2DR_PWR,      /*P5__2^^DDI-TOQ03*/ //six led
    IO_IDX_CAYMAN_MISO,   /*P5__3^^DDO-TOQ00-SIB2*/
    IO_IDX_CAYMAN_MOS1,   /*P5__4^^DCK-RTP04-SOB2*/
    IO_IDX_CAYMAN_SCK,    /*P5__5^^DMS-TOQ00-SCKB2*/
    IO_IDX_DVD_POWER,     /*P6L__0^^RTP10*/
    IO_IDX_APU_BCK_POWER, /*P6L__1^^RTP11*/
    IO_IDX_DSP_FAST_MUTE, /*P6L__2^^RTP12*/
    IO_IDX_MCU2AV_SW2,   /*P6L__3^^RTP13*/
    IO_IDX_MCU2AV_SW1,       /*P6L__4^^RTP14*/
    IO_IDX_RESV_0,        /*P6L__5^^RTP15*/
    IO_IDX_AMP_CLIP,      /*P6L__6^^SIB5*/
    IO_IDX_AK4220_RESET,  /*P6L__7^^SOB5*/
    IO_IDX_DS927A_PWR, /*P6H__0^^SCK5*/
    IO_IDX_RES_SDA,       /*P6H__1^^TIP70*/
    IO_IDX_7186_BOOT0,   /*P6H__2 */// IO_IDX_RES_SCL,   /*P6H__2 */
    IO_IDX_7186_BOOT1,     /*P6H__3^^TIP71*///  IO_IDX_IR_IN,         /*P6H__3^^TIP71*/
    IO_IDX_OWC,           /*P6H__4^^RTP80*/
    IO_IDX_DNL_VPP,       /*P6H__5^^TOP81*/
    IO_IDX_TEST1,       /*P6H__6^^ */
    IO_IDX_CAYMAN_RESET,  /*P6H__7^^ */
    IO_IDX_UART3_RXD,     /*P8__0^^RXD3-INTP8*/
    IO_IDX_UART3_TXD,     /*P8__1^^TXD3*/
    IO_IDX_MCU_SDA2,      /*P9L__0^^A0-KR6-TXDA1*/
    IO_IDX_MCU_SCL2,      /*P9L__1^^A1-KR7-RXDA1*/
    IO_IDX_FAN_CTRL,      /*P9L__2^^A2-TOP41*/
    IO_IDX_CAN0_ERR,       /*P9L__3^^A3-TOP40*/
    IO_IDX_APU_LOWPWR, /*P9L__4^^A4-TOP31*/
    IO_IDX_CPU_STATE,      /*P9L__5^^A5-TOP30*/
    IO_IDX_RADAR_DATA,    /*P9L__6^^A6-TOP21*/
    IO_IDX_APU_MISO,      /*P9L__7^^A7-SIB1-TOP20*/
    IO_IDX_APU_MOSI,      /*P9H__0^^A8-SOB1*/
    IO_IDX_APU_SCK,       /*P9H__1^^A9-SCK1*/
    IO_IDX_MCU_MISO,      /*P9H__2^^A10-SIB3*/
    IO_IDX_MCU_MOSI,      /*P9H__3^^A11-SOB3*/
    IO_IDX_MCU_SCK,       /*P9H__4^^A12-SCK3*/
    IO_IDX_VOL_A,         /*P9H__5^^A13-INTP4*/
    IO_IDX_TUNE_A,        /*P9H__6^^A14-INTP5-TOP51*/
    IO_IDX_NAVI_AUDIO,       /*P9H__7^^A15-INTP6-TOP50*/
    IO_IDX_MCU2DSP_PWR,        /*PCD__0^^ */
    IO_IDX_DTV_AUX_SEL,        /*PCD__1^^ */
    IO_IDX_VOL_B,         /*PCD__2^^ */
    IO_IDX_TUNE_B,        /*PCD__3^^ */
    IO_IDX_DVD_AUX_RGB,   /*PCS__0^^CS0*/
    IO_IDX_MHL_AUX_SEL,        /*PCS__1^^CS1*/
    IO_IDX_USB_SW2 ,       /*PCS__2^^CS2*/
    IO_IDX_USB_SW1,        /*PCS__3^^CS3*/
    IO_IDX_RESV_5,        /*PCM__0^^WAIT*/
    IO_IDX_RESV_6,        /*PCM__1^^CLOCKOUT*/
    IO_IDX_RESV_7,        /*PCM__2^^HLDAK*/
    IO_IDX_USB_HOST,        /*PCM__3^^HLDRQ*/
    IO_IDX_RESV_9,        /*PCM__4^^ */
    IO_IDX_APU_CS,        /*PCM__5^^ */
    IO_IDX_SYS_5V,        /*PCS__4^^ */
    IO_IDX_APU_RESET,     /*PCS__5^^ */
    IO_IDX_RESV_10,       /*PCS__6^^ */
    IO_IDX_CAN0_WAKE,       /*PCS__7^^ */
    IO_IDX_I2S_SEL,       /*PCT__0^^WR0*/
    IO_IDX_APU_POWER,     /*PCT__1^^WR1 */
    IO_IDX_RESV_12,       /*PCT__2^^ */
    IO_IDX_8836A_PWR,     /*PCT__3^^ */
    IO_IDX_RESV_13,       /*PCT__4^^RD*/
    IO_IDX_PHANTOM_POWER1,/*PCT__5^^ */
    IO_IDX_RESV_14,       /*PCT__6^^ASTB */
    IO_IDX_PHANTOM_POWER2,/*PCT__7^^ */
    IO_IDX_REAR_MUTE,     /*PDLL__0^^AD0*/
    IO_IDX_CAYMAN_CS,     /*PDLL__1^^AD1*/
    IO_IDX_DSP_RESET,     /*PDLL__2^^AD2*/
    IO_IDX_TFT_POWER_EN,     /*PDLL__3^^AD3*/
    IO_IDX_LOCAL_ACC,       /*PDLL__4^^AD4*/
    IO_IDX_FLMD1,         /*PDLL__5^^AD5-FLMD1*/
    IO_IDX_DISC_LED,      /*PDLL__6^^AD6*/
    IO_IDX_POWER_LED,     /*PDLL__7^^AD7*/
    IO_IDX_TFT_3V3,       /*PDLH__0^^AD8*/
    IO_IDX_TFT_VGL,       /*PDLH__1^^AD9*/
    IO_IDX_RESV_16,       /*PDLH__2^^AD10*/
    IO_IDX_RESV_17,       /*PDLH__3^^AD11*/
    IO_IDX_AVM_DET,       /*PDLH__4^^AD12*/
    IO_IDX_SWC_SEL1,      /*PDLH__5^^AD13*/
    IO_IDX_SWC_SEL2,      /*PDLH__6^^AD14*/
    IO_IDX_REVERSE_OUT,   /*PDLH__7^^AD15*/
    IO_IDX_SLEEP_5V,      /*PDH__0^^AD16*/
    IO_IDX_REAR_LVDS_PND,    /*PDH__1^^AD17*/
    IO_IDX_DSP_AVDET,     /*PDH__2^^AD18*/
    IO_IDX_POWER_CTRL1,   /*PDH__3^^AD19*/
    IO_IDX_POWER_CTRL2,   /*PDH__4^^AD20*/
    IO_IDX_POWER_EN,      /*PDH__5^^AD21*/
    IO_IDX_CAN0_EN,       /*PDH__6^^AD22*/
    IO_IDX_AUX_DET,       /*PDH__7^^AD23*/
    IO_IDX_ILL_DET,       /*P7H__7^^ANI15*/
    IO_IDX_DISC_IN_DET,   /*P7H__6^^ANI14*/
    IO_IDX_7186_RESET_DUT1,     /*P7H__5^^ANI13*/ // IO_IDX_DVD_RESET,     /*P7H__5^^ANI13*/
    IO_IDX_REVERSE_DET,   /*P7H__4^^ANI12*/
    IO_IDX_TEL_MUTE_DET,  /*P7H__3^^ANI11*/
    IO_IDX_PARKING_DET,   /*P7H__2^^ANI10*/
    IO_IDX_7186_DUT_BOOT_EN1, /*P7H__1^^ANI9*/
    IO_IDX_DS927B_PWR, /*P7H__0^^ANI8*/
    IO_IDX_BATTERY_DET,   /*P7L__7^^ANI7*/
    IO_IDX_MODULE_DET,    /*P7L__6^^ANI8*/
    IO_IDX_8836B_PWR,  /*P7L__5^^ANI9*/
    IO_IDX_TEMP_DET,      /*P7L__4^^ANI4*/
    IO_IDX_SWC1_DET,      /*P7L__3^^ANI3*/
    IO_IDX_SWC2_DET,      /*P7L__2^^ANI2*/
    IO_IDX_KEY1_DET,      /*P7L__1^^ANI1*/
    IO_IDX_KEY2_DET,      /*P7L__0^^ANI0*/

    IO_IDX_TFT_EN_IO,     /*P3__5^^TIP11*/
    
    IO_IDX_N
    
}eIO_IDX;

typedef enum{
    
    IO_PIN_AMP_STANDBY,      /* IO_IDX_AMP_STANDBY , P1_0*/
    IO_PIN_AMP_MUTE,         /* IO_IDX_AMP_MUTE , P1_1*/
  //  IO_PIN_PM_SNT_FREQ,      /* IO_IDX_PM_SNT_FREQ , P0_0*/
    IO_PIN_CAN0_STB,         /* IO_IDX_CAN1_STB , P0_1*/
    //IO_PIN_LOW_POWER,        /* IO_IDX_LOW_POWER , P0_2*/
    IO_PIN_ACC_WAKE,   /* IO_IDX_ACC_WAKE , P0_3*/
    //IO_PIN_RDS_INT0,       /* IO_IDX_RDS_INT0 , P0_4*/
    IO_PIN_DSP_CLICK,        /* IO_IDX_DSP_CLICK , P0_5*/
    IO_PIN_ILL_WAKE,         /* IO_IDX_ILL_WAKE, P0_6*/
    //IO_PIN_MCU_SDA1,         /* IO_IDX_MCU_SDA1 , P4_0*/
    //IO_PIN_MCU_SCL1,         /* IO_IDX_MCU_SCL1 , P4_1*/
    IO_PIN_CAN1_STB,         /* IO_IDX_CAN1_STB , P4_2*/
    //IO_PIN_UART0_TXD,        /* IO_IDX_UART0_TXD , P3L_0*/
   // IO_PIN_UART0_RXD,        /* IO_IDX_UART0_RXD , P3L_1*/
    //IO_PIN_SCI_MUX,          /* IO_IDX_SCI_MUX , P3L_2*/
    //IO_PIN_CAN1_TXD,         /* IO_IDX_CAN1_TXD , P3L_3*/
    //IO_PIN_CAN1_RXD,         /* IO_IDX_CAN1_RXD , P3L_4*/
   // IO_PIN_TFT_EN_IO,          /* IO_IDX_TFT_EN_IO , P3L_5*/
    //IO_PIN_CAN0_TXD,         /* IO_IDX_CAN0_TXD , P3L_6*/
    //IO_PIN_CAN0_RXD,         /* IO_IDX_CAN0_RXD , P3L_7*/
    //IO_PIN_UART2_TXD,        /* IO_IDX_UART2_TXD , P3H_0*/
   // IO_PIN_UART2_RXD,        /* IO_IDX_UART2_RXD , P3H_1*/
    //IO_PIN_KEY_PWM,          /* IO_IDX_KEY_PWM , P5_0*/
    //IO_PIN_KEY_RLED,         /* IO_IDX_SPEED_PULSE , P5_1*/
    //IO_PIN_ONE_LED,          /* IO_IDX_ONE_LED , P5_1*/
    //IO_PIN_MCU2DR_PWR,         /* IO_IDX_MCU2DR_PWR , P5_2*/
    //IO_PIN_PANEL_LED1,         /* IO_IDX_PANEL_LED1 , P5_2*/
    //IO_PIN_CAYMAN_MISO,      /* IO_IDX_CAYMAN_MISO , P5_3*/
    //IO_PIN_CAYMAN_MOS1,      /* IO_IDX_CAYMAN_MOS1 , P5_4*/
    //IO_PIN_CAYMAN_SCK,       /* IO_IDX_CAYMAN_SCK , P5_5*/
    IO_PIN_DVD_POWER,        /* IO_IDX_DVD_POWER , P6L_0*/
    IO_PIN_APU_BCK_POWER,    /* IO_IDX_APU_BCK_POWER , P6L_1*/
    IO_PIN_DSP_FAST_MUTE,    /* IO_IDX_DSP_FAST_MUTE , P6L_2*/
    IO_PIN_MCU2AV_SW2,      /* IO_IDX_MCU2AV_SW2 , P6L_3*/
    IO_PIN_MCU2AV_SW1,          /* IO_IDX_MCU2AV_SW1 , P6L_4*/
    //IO_PIN_RESV_0,           /* IO_IDX_RESV_0 , P6L_5*/
    IO_PIN_AMP_CLIP,         /* IO_IDX_AMP_CLIP , P6L_6*/
    IO_PIN_AK4220_RESET,     /* IO_IDX_AK4220_RESET , P6L_7*/
    IO_PIN_DS927A_PWR,    /* IO_IDX_DS927A_PWR , P6H_0*/
    //IO_PIN_RES_SDA,          /* IO_IDX_RES_SDA , P6H_1*/
    IO_PIN_7186_BOOT0,      /* IO_IDX_7186_BOOT0 , P6H_2*/// //IO_PIN_RES_SCL,      /* IO_IDX_RES_SCL , P6H_2*/
    IO_PIN_7186_BOOT1,            /* IO_IDX_7186_BOOT1 , P6H_3*/ //IO_PIN_IR_IN,            /* IO_IDX_IR_IN , P6H_3*/
    //IO_PIN_OWC,              /* IO_IDX_OWC , P6H_4*/
    IO_PIN_DNL_VPP,          /* IO_IDX_DNL_VPP , P6H_5*/
    IO_PIN_TEST1,          /* IO_IDX_TEST1 , P6H_6*/
    IO_PIN_CAYMAN_RESET,     /* IO_IDX_CAYMAN_RESET , P6H_7*/
    //IO_PIN_UART3_RXD,        /* IO_IDX_UART3_RXD , P8_0*/
    //IO_PIN_UART3_TXD,        /* IO_IDX_UART3_TXD , P8_1*/
    //IO_PIN_MCU_SDA2,         /* IO_IDX_MCU_SDA2 , P9L_0*/
    //IO_PIN_MCU_SCL2,         /* IO_IDX_MCU_SCL2, P9L_1*/
    //IO_PIN_FAN_CTRL,         /* IO_IDX_FAN_CTRL , P9L_2*/
    IO_PIN_CAN0_ERR,          /* IO_IDX_CAN0_ERR , P9L_3*/
    IO_PIN_APU_LOWPWR,   /* IO_IDX_APU_LOWPWR , P9L_4*/
    IO_PIN_CPU_STATE,         /* IO_IDX_CPU_STATE , P9L_5*/
    IO_PIN_RADAR_DATA,       /* IO_IDX_RADAR_DATA , P9L_6*/
    //IO_PIN_APU_MISO,         /* IO_IDX_APU_MISO , P9L_7*/
    //IO_PIN_APU_MOSI,         /* IO_IDX_APU_MOSI , P9H_0*/
    //IO_PIN_APU_SCK,          /* IO_IDX_APU_SCK , P9H_1*/
    //IO_PIN_MCU_MISO,         /* IO_IDX_MCU_MISO , P9H_2*/
    //IO_PIN_MCU_MOSI,         /* IO_IDX_MCU_MOSI , P9H_3*/
    //IO_PIN_MCU_SCK,          /* IO_IDX_MCU_SCK , P9H_4*/
    IO_PIN_VOL_A,            /* IO_IDX_VOL_A , P9H_5*/
    IO_PIN_TUNE_A,           /* IO_IDX_TUNE_A , P9H_6*/
    IO_PIN_NAVI_AUDIO,   /* IO_IDX_NAVI_AUDIO , P9H_7*/
    IO_PIN_MCU2DSP_PWR,           /* IO_IDX_MCU2DSP_PWR , PCD_0*/
    IO_PIN_DTV_AUX_SEL,           /* IO_IDX_DTV_AUX_SEL , PCD_1*/
    IO_PIN_VOL_B,            /* IO_IDX_VOL_B , PCD_2*/
    IO_PIN_TUNE_B,           /* IO_IDX_TUNE_B , PCD_3*/
    IO_PIN_DVD_AUX_RGB,      /* IO_IDX_DVD_AUX_RGB , PCS_0*/
    IO_PIN_MHL_AUX_SEL,           /* IO_IDX_RESV_2 , PCS_1*/
    IO_PIN_USB_SW2,           /* IO_IDX_USB_SW2 , PCS_2*/
    IO_PIN_USB_SW1,           /* IO_IDX_USB_SW1 , PCS_3*/
    //IO_PIN_RESV_5,           /* IO_IDX_RESV_5 , PCM_0*/
    //IO_PIN_RESV_6,           /* IO_IDX_RESV_6 , PCM_1*/
    //IO_PIN_RESV_7,           /* IO_IDX_RESV_7 , PCM_2*/
    IO_PIN_USB_HOST,           /* IO_IDX_USB_HOST , PCM_3*/
    //IO_PIN_RESV_9,           /* IO_IDX_RESV_9 , PCM_4*/
    IO_PIN_APU_CS,           /* IO_IDX_APU_CS , PCM_5*/
    IO_PIN_SYS_5V,           /* IO_IDX_SYS_5V , PCS_4*/
    IO_PIN_APU_RESET,        /* IO_IDX_APU_RESET , PCS_5*/
    //IO_PIN_RESV_10,          /* IO_IDX_RESV_10 , PCS_6*/
    IO_PIN_CAN0_WAKE,     /* IO_IDX_CAN0_WAKE , PCS_7*/
    IO_PIN_I2S_SEL,          /* IO_IDX_I2S_SEL , PCT_0*/
    IO_PIN_APU_POWER,        /* IO_IDX_APU_POWER , PCT_1*/
    //IO_PIN_RESV_12,          /* IO_IDX_RESV_12 , PCT_2*/
    IO_PIN_8836A_PWR,        /* IO_IDX_8836A_PWR , PCT_3*/
    //IO_PIN_RESV_13,          /* IO_IDX_RESV_13 , PCT_4*/
    IO_PIN_PHANTOM_POWER1,   /* IO_IDX_PHANTOM_POWER1 , PCT_5*/
    //IO_PIN_RESV_14,          /* IO_IDX_RESV_14 , PCT_6*/
    IO_PIN_PHANTOM_POWER2,   /* IO_IDX_PHANTOM_POWER2 , PCT_7*/
    IO_PIN_REAR_MUTE,        /* IO_IDX_REAR_MUTE , PDLL_0*/
    IO_PIN_CAYMAN_CS,        /* IO_IDX_CAYMAN_CS , PDLL_1*/
    IO_PIN_DSP_RESET,        /* IO_IDX_DSP_RESET , PDLL_2*/
    IO_PIN_TFT_POWER_EN,        /* IO_IDX_LINE_MUTE , PDLL_3*/
    IO_PIN_LOCAL_ACC,          /* IO_IDX_LOCAL_ACC , PDLL_4*/
    //IO_PIN_FLMD1,            /* IO_IDX_FLMD1 , PDLL_5*/
    IO_PIN_DISC_LED,         /* IO_IDX_DISC_LED , PDLL_6*/
    IO_PIN_POWER_LED,        /* IO_IDX_POWER_LED , PDLL_7*/
    IO_PIN_TFT_3V3,          /* IO_IDX_TFT_3V3 , PDLH_0*/
    IO_PIN_TFT_VGL,          /* IO_IDX_TFT_VGL , PDLH_1*/
    //IO_PIN_RESV_16,          /* IO_IDX_RESV_16 , PDLH_2*/
    //IO_PIN_RESV_17,          /* IO_IDX_RESV_17 , PDLH_3*/
    IO_PIN_AVM_DET,          /* IO_IDX_AVM_DET , PDLH_4*/
    IO_PIN_SWC_SEL1,         /* IO_IDX_SWC_SEL1 , PDLH_5*/
    IO_PIN_SWC_SEL2,         /* IO_IDX_SWC_SEL2 , PDLH_6*/
    IO_PIN_REVERSE_OUT,      /* IO_IDX_REVERSE_OUT , PDLH_7*/
    IO_PIN_SLEEP_5V,         /* IO_IDX_SLEEP_5V , PDH_0*/
    IO_PIN_REAR_LVDS_PND,       /* IO_IDX_REAR_LVDS_PND , PDH_1*/
    IO_PIN_DSP_AVDET,        /* IO_IDX_DSP_AVDET , PDH_2*/
    IO_PIN_POWER_CTRL1,      /* IO_IDX_POWER_CTRL1 , PDH_3*/
    IO_PIN_POWER_CTRL2,      /* IO_IDX_POWER_CTRL2 , PDH_4*/
    IO_PIN_POWER_EN,         /* IO_IDX_POWER_EN , PDH_5*/
    IO_PIN_CAN0_EN,          /* IO_IDX_CAN0_EN , PDH_6*/
    IO_PIN_AUX_DET,          /* IO_IDX_AUX_DET , PDH_7*/
    IO_PIN_ILL_DET,          /* IO_IDX_ILL_DET , P7H_7*/
    IO_PIN_DISC_IN_DET,      /* IO_IDX_DISC_IN_DET , P7H_6*/
    IO_PIN_7186_RESET_DUT1,        /* IO_IDX_7186_RESET_DUT1 , P7H_5*/// IO_PIN_DVD_RESET,        /* IO_IDX_DVD_RESET , P7H_5*/
    IO_PIN_REVERSE_DET,      /* IO_IDX_REVERSE_DET , P7H_4*/
    IO_PIN_TEL_MUTE_DET,     /* IO_IDX_TEL_MUTE_DET , P7H_3*/
    IO_PIN_PARKING_DET,      /* IO_IDX_PARKING_DET , P7H_2*/
    IO_PIN_7186_DUT_BOOT_EN1,    /* IO_IDX_7186_DUT_BOOT_EN1 , P7H_1*/  // IO_PIN_REAR_LVDS_EN,    /* IO_IDX_REAR_LVDS_EN , P7H_1*/
    IO_PIN_DS927B_PWR,    /* IO_IDX_DS927B_PWR , P7H_0*/
    //IO_PIN_BATTERY_DET,      /* IO_IDX_BATTERY_DET , P7L_7*/
    IO_PIN_MODULE_DET,       /* IO_IDX_MODULE_DET , P7L_6*/
    IO_PIN_8836B_PWR,     /* IO_IDX_8836B_PWR , P7L_5*/
    //IO_PIN_TEMP_DET,         /* IO_IDX_TEMP_DET , P7L_4*/
    //IO_PIN_SWC1_DET,         /* IO_IDX_SWC1_DET , P7L_3*/
    //IO_PIN_SWC2_DET,         /* IO_IDX_SWC2_DET , P7L_2*/
    //IO_PIN_KEY1_DET,         /* IO_IDX_KEY1_DET , P7L_1*/
    //IO_PIN_KEY2_DET,         /* IO_IDX_KEY2_DET , P7L_0*/
    

    IO_PIN_N
    
}eIO_PIN_IDX;

typedef enum{
    IO_PWM_PM_SNT_FREQ,/* IO_IDX_PM_SNT_FREQ , P0_0*/
    IO_PWM_KEY_LED,    /* IO_IDX_KEY_PWM , P5_0*/
    IO_PWM_PANEL_LED2,    /*IO_IDX_PANEL_LED2 , P5_1*/
	IO_PWM_PANEL_LED1,    /*IO_IDX_PANEL_LED1 , P5_2*/
    IO_PWM_FAN_CTRL,   /* IO_IDX_FAN_CTRL , P9L_2*/
    IO_PWM_TFT_CTRL,   /* IO_IDX_TFT_EN_PWM  , P3L_5*/
    IO_PWM_N
}eIO_PWM_IDX;

typedef enum{
    IO_I2C_MCU_SDA1,/* IO_IDX_MCU_SDA1 , P4_0*/
    IO_I2C_MCU_SCL1,/* IO_IDX_MCU_SCL1, P4_1*/
    IO_I2C_MCU_SDA0,/* IO_IDX_UART2_TXD , P3H_0*/
    IO_I2C_MCU_SCL0,/* IO_IDX_UART2_RXD , P3H_1*/
    IO_I2C_MCU_SDA2,/* IO_IDX_MCU_SDA2, P9L_0*/
    IO_I2C_MCU_SCL2,/* IO_IDX_MCU_SCL2, P9L_1*/

    IO_I2C_RES_SDA,     	/* IO_IDX_RES_SDA , P6H_1*/
    IO_I2C_RES_SCL,     	/* IO_IDX_RES_SCL , P6H_2*/
    IO_I2C_N
    
}eIO_I2C_IDX;

typedef enum{
    IO_NUSE_RESV_0, /* IO_IDX_RESV_0 , P6L_5*/
    //IO_NUSE_RESV_1, /* IO_IDX_RESV_1 , PCD_1*/
    IO_NUSE_RESV_2, /* IO_IDX_RESV_2 , PCS_1*/
    //IO_NUSE_RESV_3, /* IO_IDX_RESV_3 , PCS_2*/
    //IO_NUSE_RESV_4, /* IO_IDX_RESV_4 , PCS_3*/
    IO_NUSE_RESV_5, /* IO_IDX_RESV_5 , PCM_0*/
    IO_NUSE_RESV_6, /* IO_IDX_RESV_6 , PCM_1*/
    IO_NUSE_RESV_7, /* IO_IDX_RESV_7 , PCM_2*/
//    IO_NUSE_RESV_8, /* IO_IDX_RESV_8 , PCM_3*/
    IO_NUSE_RESV_9, /* IO_IDX_RESV_9 , PCM_4*/
    IO_NUSE_RESV_10,/* IO_IDX_RESV_10 , PCS_6*/
//    IO_NUSE_RESV_11,/* IO_IDX_RESV_11 , PCS_7*/
    IO_NUSE_RESV_12,/* IO_IDX_RESV_12 , PCT_2*/
    IO_NUSE_RESV_13,/* IO_IDX_RESV_13 , PCT_4*/
    IO_NUSE_RESV_14,/* IO_IDX_RESV_14 , PCT_6*/
//    IO_NUSE_RESV_15,/* IO_IDX_RESV_15 , PDLL_4*/
    IO_NUSE_RESV_16,/* IO_IDX_RESV_16 , PDLH_2*/
    IO_NUSE_RESV_17,/* IO_IDX_RESV_17 , PDLH_3*/
    //IO_NUSE_RESV_18,/* IO_IDX_RESV_18 , PDLH_4*/
    IO_NUSE_SCI_MUX,/* IO_IDX_SCI_MUX , P3L_2*/
    IO_NUSE_FLMD1,  /* IO_IDX_FLMD1 , PDLL_5*/

    IO_NUSE_N
}eIO_NOUSE_IDX;

typedef enum{
    IO_ADC_ILL_DET,    /* IO_IDX_ILL_DET , P7H_7*/
    IO_ADC_BATTERY_DET,/* IO_IDX_BATTERY_DET , P7L_7*/
    IO_ADC_TEMP_DET,   /* IO_IDX_TEMP_DET , P7L_4*/
    IO_ADC_SWC1_DET,   /* IO_IDX_SWC1_DET , P7L_3*/
    IO_ADC_SWC2_DET,   /* IO_IDX_SWC2_DET , P7L_2*/
    IO_ADC_KEY1_DET,   /* IO_IDX_KEY1_DET , P7L_1*/
    IO_ADC_KEY2_DET,   /* IO_IDX_KEY2_DET , P7L_0*/

    IO_ADC_N
}eIO_ADC_IDX;

typedef enum{
    IO_UART_UART0_TXD,/* IO_IDX_UART0_TXD , P3L_0*/
    IO_UART_UART0_RXD,/* IO_IDX_UART0_RXD , P3L_1*/
    //IO_UART_UART2_TXD,/* IO_IDX_UART2_TXD , P3H_0*/
   // IO_UART_UART2_RXD,/* IO_IDX_UART2_RXD , P3H_1*/
    IO_UART_UART3_RXD,/* IO_IDX_UART3_RXD , P8_0*/
    IO_UART_UART3_TXD,/* IO_IDX_UART3_TXD , P8_1*/

    IO_UART_N
}eIO_UART_IDX;

typedef enum{

    IO_SPI_CAYMAN_MISO,/* IO_IDX_CAYMAN_MISO , P5_3*/
    IO_SPI_CAYMAN_MOS1,/* IO_IDX_CAYMAN_MOS1 , P5_4*/
    IO_SPI_CAYMAN_SCK, /* IO_IDX_CAYMAN_SCK , P5_5*/
    IO_SPI_APU_MISO,   /* IO_IDX_APU_MISO , P9L_7*/
    IO_SPI_APU_MOSI,   /* IO_IDX_APU_MOSI , P9H_0*/
    IO_SPI_APU_SCK,    /* IO_IDX_APU_SCK , P9H_1*/
    IO_SPI_MCU_MISO,   /* IO_IDX_MCU_MISO , P9H_2*/
    IO_SPI_MCU_MOSI,   /* IO_IDX_MCU_MOSI , P9H_3*/
    IO_SPI_MCU_SCK,    /* IO_IDX_MCU_SCK , P9H_4*/

    IO_SPI_N
}eIO_SPI_N;

typedef enum{

    IO_INT_LOW_POWER,     /* IO_IDX_LOW_POWER , P0_2*/
    IO_INT_RDS_INT0,      /* IO_IDX_RDS_INT0 , P0_4*/
    IO_INT_ILL_WAKE,      /* IO_IDX_ILL_WAKE , P0_6*/
//    IO_INT_RES_BUS,       /* IO_IDX_RES_SDA , P6H_1*/
    IO_INT_RADAR_ID,      /* IO_IDX_RADAR_ID , P9L_5*/
    
    IO_INT_N
}eIO_INT_IDX;

typedef enum{
    IO_TIP_IR_IN,/* IO_IDX_IR_IN , P6H_3*/
    IO_TIP_OWC,  /* IO_IDX_OWC , P6H_4*/
   // IO_TIP_SPEED,/* IO_IDX_SPEED , P9L_4*/
    IO_TIO_N
}eIO_TIO_IDX;

typedef enum{
    IO_CAN_CAN1_TXD,/* IO_IDX_CAN1_TXD , P3L_3*/
    IO_CAN_CAN1_RXD,/* IO_IDX_CAN1_RXD , P3L_4*/
    IO_CAN_CAN0_TXD,/* IO_IDX_CAN0_TXD , P3L_6*/
    IO_CAN_CAN0_RXD,/* IO_IDX_CAN0_RXD , P3L_7*/
    IO_CAN_N
}eIO_CAN_IDX;

#pragma pack(1)
typedef union{
    uint8_t byte;
    struct{
        bit_t    bIoState :1;
        bit_t    rev      :6;
        bit_t    bAction  :1;
    }field;
    
}uIO_SCAN_RET;

#define B_IO_ACTION      BIT7
#define B_IO_STATE       BIT0

#pragma pack(1)
typedef struct{
    bool    bValid;                      /*1:此区域是有效区域,2:此区域是用于消除噪音的无效区域*/
    uint8_t cIdx;                        /*有效区域识别号，如果此区域无效，则填其依附的前一有效区识别号*/
    uint8_t cNextIdx;                    /*如果此区域无效，则填其依附的后一有效区识别号，区域有效，忽略此项 */
    uint8_t cVMin,cVMax;
    uint8_t cValidTime;
}tADC_VALUE;

#pragma pack(1)
typedef struct{
    uint8_t bSoftAdc;
    uint8_t cNum;                       /*总区域个数*/        
    uint8_t cValidNum;                  /*有效区域个数*/
    const tADC_VALUE* p_tVal;
    uint8_t* p_AdcBuff;
}tADC_PHYSICAL_MAP;

#pragma pack(1)
typedef struct{
    uint8_t  cNum;
    const uint8_t* p_cDuty;
    const uint32_t* p_lFreq;
    uint8_t  cTiming;
}tPWM_PHYSICAL_MAP;

#pragma pack(1)
typedef struct{
    uint8_t  bSoftPin;
    uint8_t  cPhyID;
    uint8_t  bOD;
    uint8_t  cValidVal;
    uint8_t  cValidTime;
    uint8_t  cInvalidTime;
    uint8_t* p_cBuff;
}tPIN_PHYSICAL_MAP;


#pragma pack(1)
typedef struct{
    uint8_t  cPhyID;
    uint8_t  cDir;
    uint8_t  cVal;
}tIO_PIN_TAB;


#define PWM_MHz(x)    (x*1000000L)
#define PWM_KHz(x)    (x*1000L)
#define PWM_Hz(x)     (x)




_APPIO_ uint8_t       IO_Get          (uint8_t cIdx, uint8_t dir, bool delay);
_APPIO_ bool          IO_Set          (uint8_t cIdx, uint8_t dir, uint8_t val );
_APPIO_ void          IO_Scan         (uint8_t cIdx, uint8_t dir );
_APPIO_ void          IO_Scan_Set     (uint8_t cIdx, bool enble);
_APPIO_ void          IO_ResetState   (uint8_t cIdx, uint8_t cValue);
_APPIO_ void          IO_Init         (void);
_APPIO_ void          IO_ADCInit      (uint8_t cIdx,tADC_PHYSICAL_MAP* p_tMap);
_APPIO_ void          IO_PWMInit      (uint8_t cIdx,tPWM_PHYSICAL_MAP* p_tMap);
_APPIO_ void          IO_PinInit      (uint8_t cIdx,tPIN_PHYSICAL_MAP* p_tMap);
_APPIO_ void          IO_PinSetDefMap (uint8_t cIdx);


#endif

