//系统需要直接读取/设置IO状态的端口，一般都只是在中断中使用
#define IO_GET_LVI_DET    (P0  & 0x04)
#define IO_GET_MEDIA_IRQ  (P9H & 0x80)
#define IO_GET_ENCODE_A   (P9H & 0x20)
#define IO_GET_ENCODE_B   (PCD & 0x04)
#define IO_GET_ENCODE_C   (P9H & 0x40)
#define IO_GET_ENCODE_D   (PCD & 0x08)

#define IO_SET_DISC_COMM_LINE_LOW()   do{P6H &= 0xef;PM6H &= 0xef;}while(0)
#define IO_SET_DISC_COMM_LINE_HIGH()  do{P6H |= 0x10;PM6H &= 0xef;}while(0)
#define IO_GET_DISC_COMM_LINE         (P6H & 0x10)

/*******************************************************************************
* IO register 
* Port n mode register (PMn: n = 0, 1, 3 to 9, CD, CM, CS, CT, DH, DL)
* Port n mode control register (PMCn: n = 0, 3 to 6, 8, 9, CM, CS, CT, DH, DL)
* Port n function control register (PFCn: n = 0, 3 to 6, 9)
* Port n function control expansion register (PFCEn: n = 3, 5, 9)
* Port n function register (PFn: n = 0, 3 to 6, 8, 9)
*******************************************************************************/

typedef enum{
    PIN_LOW,
    PIN_HIGHT,

    PIN_LEVEL_n
}ePIN_LEVEL;

typedef enum{
    PIN_OUTPUT,
    PIN_INPUT,

    PIN_MD_n
}ePIN_DIRECTION;

typedef enum{
    PIN_CMOS,
    PIN_OD,

    PIN_ODM_n
}ePIN_OD_MODE;

typedef enum{
    PIO_P0,
    PIO_P1,
    PIO_P3L,
    PIO_P3H,
    PIO_P4,
    PIO_P5,
    PIO_P6L,
    PIO_P6H,
    PIO_P7L,
    PIO_P7H,
    PIO_P8,
    PIO_P9L,
    PIO_P9H,
    PIO_PCD,
    PIO_PCT,
    PIO_PCS,
    PIO_PCM,
    PIO_PDLL,
    PIO_PDLH,
    PIO_PDH,

    PIO_n
}ePIO_IDX;


typedef enum{
    PIN_P0_0 ,
    PIN_P0_1 ,
    PIN_P0_2 ,
    PIN_P0_3 ,
    PIN_P0_4 ,
    PIN_P0_5 ,
    PIN_P0_6 ,
    PIN_P0_7 ,
    PIN_P1_0 ,      /*8*/
    PIN_P1_1 ,
    PIN_P1_2 ,
    PIN_P1_3 ,
    PIN_P1_4 ,
    PIN_P1_5 ,
    PIN_P1_6 ,
    PIN_P1_7 ,      
    PIN_P3L_0 ,     /*16*/
    PIN_P3L_1 ,
    PIN_P3L_2 ,
    PIN_P3L_3 ,
    PIN_P3L_4 ,
    PIN_P3L_5 ,
    PIN_P3L_6 ,
    PIN_P3L_7 ,
    PIN_P3H_0 ,     /*24*/ 
    PIN_P3H_1 ,
    PIN_P3H_2 ,
    PIN_P3H_3 ,
    PIN_P3H_4 ,
    PIN_P3H_5 ,
    PIN_P3H_6 ,
    PIN_P3H_7 ,
    PIN_P4_0 ,      /*32*/
    PIN_P4_1 ,
    PIN_P4_2 ,
    PIN_P4_3 ,
    PIN_P4_4 ,
    PIN_P4_5 ,
    PIN_P4_6 ,
    PIN_P4_7 ,
    PIN_P5_0 ,      /*40*/
    PIN_P5_1 ,
    PIN_P5_2 ,
    PIN_P5_3 ,
    PIN_P5_4 ,
    PIN_P5_5 ,
    PIN_P5_6 ,
    PIN_P5_7 ,
    PIN_P6L_0 ,     /*48*/
    PIN_P6L_1 ,
    PIN_P6L_2 ,
    PIN_P6L_3 ,
    PIN_P6L_4 ,
    PIN_P6L_5 ,
    PIN_P6L_6 ,
    PIN_P6L_7 ,
    PIN_P6H_0 ,     /*56*/
    PIN_P6H_1 ,
    PIN_P6H_2 ,
    PIN_P6H_3 ,
    PIN_P6H_4 ,
    PIN_P6H_5 ,
    PIN_P6H_6 ,
    PIN_P6H_7 ,
    PIN_P7L_0 ,     /*64*/
    PIN_P7L_1 ,
    PIN_P7L_2 ,
    PIN_P7L_3 ,
    PIN_P7L_4 ,
    PIN_P7L_5 ,
    PIN_P7L_6 ,
    PIN_P7L_7 ,
    PIN_P7H_0 ,     /*72*/
    PIN_P7H_1 ,
    PIN_P7H_2 ,
    PIN_P7H_3 ,
    PIN_P7H_4 ,
    PIN_P7H_5 ,
    PIN_P7H_6 ,
    PIN_P7H_7 ,
    PIN_P8_0 ,      /*80*/
    PIN_P8_1 ,
    PIN_P8_2 ,
    PIN_P8_3 ,
    PIN_P8_4 ,
    PIN_P8_5 ,
    PIN_P8_6 ,
    PIN_P8_7 ,
    PIN_P9L_0 ,     /*88*/
    PIN_P9L_1 ,
    PIN_P9L_2 ,
    PIN_P9L_3 ,
    PIN_P9L_4 ,
    PIN_P9L_5 ,
    PIN_P9L_6 ,
    PIN_P9L_7 ,
    PIN_P9H_0 ,     /*96*/
    PIN_P9H_1 ,
    PIN_P9H_2 ,
    PIN_P9H_3 ,
    PIN_P9H_4 ,
    PIN_P9H_5 ,
    PIN_P9H_6 ,
    PIN_P9H_7 ,
    PIN_PCD_0 ,     /*104*/
    PIN_PCD_1 ,
    PIN_PCD_2 ,
    PIN_PCD_3 ,
    PIN_PCD_4 ,
    PIN_PCD_5 ,
    PIN_PCD_6 ,
    PIN_PCD_7 ,
    PIN_PCT_0 ,     /*112*/
    PIN_PCT_1 ,
    PIN_PCT_2 ,
    PIN_PCT_3 ,
    PIN_PCT_4 ,
    PIN_PCT_5 ,
    PIN_PCT_6 ,
    PIN_PCT_7 ,
    PIN_PCS_0 ,     /*120*/
    PIN_PCS_1 ,
    PIN_PCS_2 ,
    PIN_PCS_3 ,
    PIN_PCS_4 ,
    PIN_PCS_5 ,
    PIN_PCS_6 ,
    PIN_PCS_7 ,
    PIN_PCM_0 ,     /*128*/
    PIN_PCM_1 ,
    PIN_PCM_2 ,
    PIN_PCM_3 ,
    PIN_PCM_4 ,
    PIN_PCM_5 ,
    PIN_PCM_6 ,
    PIN_PCM_7 ,
    PIN_PDLL_0 ,    /*136*/
    PIN_PDLL_1 ,
    PIN_PDLL_2 ,
    PIN_PDLL_3 ,
    PIN_PDLL_4 ,
    PIN_PDLL_5 ,
    PIN_PDLL_6 ,
    PIN_PDLL_7 ,
    PIN_PDLH_0 ,    /*144*/
    PIN_PDLH_1 ,
    PIN_PDLH_2 ,
    PIN_PDLH_3 ,
    PIN_PDLH_4 ,
    PIN_PDLH_5 ,
    PIN_PDLH_6 ,
    PIN_PDLH_7 ,
    PIN_PDH_0 ,     /*152*/
    PIN_PDH_1 ,
    PIN_PDH_2 ,
    PIN_PDH_3 ,
    PIN_PDH_4 ,
    PIN_PDH_5 ,
    PIN_PDH_6 ,
    PIN_PDH_7 ,

    PIN_N          /*160*/
    
}ePIN_IDX;

typedef enum{
    ADC_CH0,
    ADC_CH1,
    ADC_CH2,
    ADC_CH3,
    ADC_CH4,
    ADC_CH5,
    ADC_CH6,
    ADC_CH7,
    ADC_CH8,
    ADC_CH9,
    ADC_CH10,
    ADC_CH11,
    ADC_CH12,
    ADC_CH13,
    ADC_CH14,
    ADC_CH15,
    
    ADC_CHN,
}eADC_IDX;

typedef enum{
    PWM_TMQ,
    PWM_TM,
    PWM_TP,

    PWM_N
}ePWM_IDX;

//idx   : io口命名
//od    : oper drain mode or CMOS mode 开漏输出或者推挽输出
//dir   : io口方向，输出还是输入  
//valid : 有效值，非指定io的电平，指的是io起作用的电平
//dly   : 延时采样 or 直接取端口电平

_V850_ void     v850_io_init(void);
_V850_ bool     v850_get_pin(uint8_t idx,ePIN_DIRECTION dir/*,ePIN_OD_MODE od*/);
_V850_ void     v850_set_pin(uint8_t idx,ePIN_DIRECTION dir/*,ePIN_OD_MODE od*/,bool pv);
_V850_ uint16_t v850_get_adc(uint8_t idx);
_V850_ bool     v850_set_pwm(uint8_t idx,uint8_t duty,uint32_t lFreq);
_V850_ void     v850_pwm_init(void);

_V850_ void     v850_intp4_init(void);
_V850_ void     v850_intp5_init(void);
_V850_ void     v850_intp4_enable(void);
_V850_ void     v850_intp5_enable(void);


