/*
*******************************************************************************
**    Register bit define
*******************************************************************************
*/
/* 
    TMP control register 0 (TPnCTL0)
*/
/* TMP operation control (TPnCE) */
#define    TMP_OPERATION_DISABLE        0x00    /* disable internal operating clock operation (asynchronously reset TMPn) */
#define    TMP_OPERATION_ENABLE        0x80    /* enable internal operating clock operation */
/* Internal count clock selection (TPnCKS2,TPnCKS1,TPnCKS0) */
#define    TMP_INTERNAL_CLOCK0            0x00    /* fXX */
#define    TMP_INTERNAL_CLOCK1            0x01    /* fXX/2 */
#define    TMP_INTERNAL_CLOCK2            0x02    /* fXX/4 */
#define    TMP_INTERNAL_CLOCK3            0x03    /* fXX/8 */
#define    TMP_INTERNAL_CLOCK4            0x04    /* fXX/16 */
#define    TMP_INTERNAL_CLOCK5            0x05    /* fXX/32 */
#define    TMP_INTERNAL_CLOCK6            0x06    /* fXX/64 or fXX/256 */
#define    TMP_INTERNAL_CLOCK7            0x07    /* fXX/128 or fXX/512 */

/* 
    TMP control register 1 (TPnCTL1)
*/
/* Software trigger control (TPnEST) */
#define    TMP_SOFTTRIGGER_OFF            0x00    /* no operation */
#define    TMP_SOFTTRIGGER_ON            0x40    /* in one-shot pulse mode: One-shot pulse software trigger */
                                            /* in external trigger pulse output mode: Pulse output software trigger */
/* Count clock selection (TPnEEE) */
#define    TMP_INTERNAL_CLOCK            0x00    /* use the internal clock (clock selected with bits TPnCKS2 to TPnCKS0) */
#define    TMP_EXTERNAL_CLOCK            0x20    /* use the external clock from the TIPn0 input pin */ 
/* Timer mode selection (TPnMD2,TPnMD1,TPnMD0) */
#define    TMP_MODE_INTERVAL            0x00    /* interval timer mode */
#define    TMP_MODE_EXTERNALCOUNT        0x01    /* external event counter mode */
#define    TMP_MODE_EXTERNALTRG        0x02    /* external trigger pulse output mode */
#define    TMP_MODE_ONESHOT            0x03    /* one-shot pulse mode */
#define    TMP_MODE_PWM                0x04    /* PWM mode */
#define    TMP_MODE_FREERUNNING        0x05    /* free-running mode */
#define    TMP_MODE_PULSEMEASURE        0x06    /* pulse width measurement mode */

/* 
    TMP I/O control register 0 (TPnIOC0)
*/
/* TOPn0 pin output level setting (TPnOL0) */
#define    TMP_OUTPUT0_NORMAL            0x00    /* normal output */
#define    TMP_OUTPUT0_INVERTED        0x02    /* inverted output */
/* TOPn0 pin output setting (TPnOE0) */
#define    TMP_OUTPUT0_DISABLE            0x00    /* disable timer output */
#define    TMP_OUTPUT0_ENABLE            0x01    /* enable timer output (TOPn0 pin outputs pulses) */
/* TOPn1 pin output level setting (TPnOL1) */
#define    TMP_OUTPUT1_NORMAL            0x00    /* normal output */
#define    TMP_OUTPUT1_INVERTED        0x08    /* inverted output */
/* TOPn1 pin output setting (TPnOE1) */
#define    TMP_OUTPUT1_DISABLE            0x00    /* disable timer output */
#define    TMP_OUTPUT1_ENABLE            0x04    /* enable timer output (TOPn1 pin outputs pulses) */

/* 
    TMP I/O control register 1 (TPnIOC1)
*/
/* Capture trigger input signal (TIPn1 pin) valid edge setting (TPnIS3,TPnIS2) */
#define    TMP_INPUT1_EDGE_NONE        0x00    /* detect no edge (capture operation is invalid) */
#define    TMP_INPUT1_EDGE_RISING        0x04    /* detection of rising edge */
#define    TMP_INPUT1_EDGE_FALLING        0x08    /* detection of falling edge */
#define    TMP_INPUT1_EDGE_BOTH        0x0c    /* detection of both edges */
/* Capture trigger input signal (TIPn0 pin) valid edge setting (TPnIS1,TPnIS0) */
#define    TMP_INPUT0_EDGE_NONE        0x00    /* detect no edge (capture operation is invalid) */
#define    TMP_INPUT0_EDGE_RISING        0x01    /* detection of rising edge */
#define    TMP_INPUT0_EDGE_FALLING        0x02    /* detection of falling edge */
#define    TMP_INPUT0_EDGE_BOTH        0x03    /* detection of both edges */

/* 
    TMP I/O control register 2 (TPnIOC2)
*/
/* External event count input signal (TIPn0 pin) valid edge setting (TPnEES1,TPnEES0) */
#define    TMP_EXTCOUNT_EDGE_NONE        0x00    /* detect no edge (external event count is invalid) */
#define    TMP_EXTCOUNT_EDGE_RISING    0x04    /* detection of rising edge */
#define    TMP_EXTCOUNT_EDGE_FALLING    0x08    /* detection of falling edge */
#define    TMP_EXTCOUNT_EDGE_BOTH        0x0c    /* detection of both edges */
/* External trigger input signal (TIPn0 pin) valid edge setting (TPnETS1,TPnETS0) */
#define    TMP_EXTTRIGGER_EDGE_NONE    0x00    /* detect no edge (external trigger is invalid) */
#define    TMP_EXTTRIGGER_EDGE_RISING    0x01    /* detection of rising edge */
#define    TMP_EXTTRIGGER_EDGE_FALLING    0x02    /* detection of falling edge */
#define    TMP_EXTTRIGGER_EDGE_BOTH    0x03    /* detection of both edges */

/* 
    TMP option register 0 (TPnOPT0)
*/
/* TPnCCR1 register capture/compare selection (TPnCCS1) */
#define    TMP_CCR1_COMPARE            0x00    /* compare register */
#define    TMP_CCR1_CAPTURE            0x20    /* capture register */
/* TPnCCR0 register capture/compare selection (TPnCCS0) */
#define    TMP_CCR0_COMPARE            0x00    /* compare register */
#define    TMP_CCR0_CAPTURE            0x10    /* capture register */
/* TMPn overflow detection flag (TPnOVF) */
#define TMP_OVERFLOW_OCCUR            0x01    /* overflow occurred */
#define TMP_OVERFLOW_CLEAR            0x00    /* clear overflow */

/* 
    TMQ0 control register 0 (TQ0CTL0)
*/
/* TMQ operation control (TQ0CE) */
#define    TMQ_OPERATION_DISABLE        0x00    /* disable internal operating clock operation (asynchronously reset TMQ0) */
#define    TMQ_OPERATION_ENABLE        0x80    /* enable internal operating clock operation */
/* Internal count clock selection (TQ0CKS2,TQ0CKS1,TQ0CKS0) */
#define    TMQ_INTERNAL_CLOCK0            0x00    /* fXX */
#define    TMQ_INTERNAL_CLOCK1            0x01    /* fXX/2 */
#define    TMQ_INTERNAL_CLOCK2            0x02    /* fXX/4 */
#define    TMQ_INTERNAL_CLOCK3            0x03    /* fXX/8 */
#define    TMQ_INTERNAL_CLOCK4            0x04    /* fXX/16 */
#define    TMQ_INTERNAL_CLOCK5            0x05    /* fXX/32 */
#define    TMQ_INTERNAL_CLOCK6            0x06    /* fXX/64 */
#define    TMQ_INTERNAL_CLOCK7            0x07    /* fXX/128 */

/* 
    TMQ0 control register 1 (TQ0CTL1)
*/
/* Software trigger control (TQ0EST) */
#define    TMQ_SOFTTRIGGER_OFF            0x00    /* no operation */
#define    TMQ_SOFTTRIGGER_ON            0x40    /* in one-shot pulse mode: One-shot pulse software trigger */
                                            /* in external trigger pulse output mode: Pulse output software trigger */
/* Count clock selection (TQ0EEE) */
#define    TMQ_INTERNAL_CLOCK            0x00    /* use the internal clock (clock selected with bits TQ0CKS2 to TQ0CKS0) */
#define    TMQ_EXTERNAL_CLOCK            0x20    /* use the external clock from the TIQ00 input pin */ 
/* Timer mode selection (TQ0MD2,TQ0MD1,TQ0MD0) */
#define    TMQ_MODE_INTERVAL            0x00    /* interval timer mode */
#define    TMQ_MODE_EXTERNALCOUNT        0x01    /* external event counter mode */
#define    TMQ_MODE_EXTERNALTRG        0x02    /* external trigger pulse output mode */
#define    TMQ_MODE_ONESHOT            0x03    /* one-shot pulse mode */
#define    TMQ_MODE_PWM                0x04    /* PWM mode */
#define    TMQ_MODE_FREERUNNING        0x05    /* free-running mode */
#define    TMQ_MODE_PULSEMEASURE        0x06    /* pulse width measurement mode */

/* 
    TMQ0 I/O control register 0 (TQ0IOC0)
*/
/* TOQ00 pin output level setting (TQ0OL0) */
#define    TMQ_OUTPUT0_NORMAL            0x00    /* normal output */
#define    TMQ_OUTPUT0_INVERTED        0x02    /* inverted output */
/* TOQ00 pin output setting (TQ0OE0) */
#define    TMQ_OUTPUT0_DISABLE            0x00    /* disable timer output */
#define    TMQ_OUTPUT0_ENABLE            0x01    /* enable timer output (TOQ00 pin outputs pulses) */
/* TOQ01 pin output level setting (TQ0OL1) */
#define    TMQ_OUTPUT1_NORMAL            0x00    /* normal output */
#define    TMQ_OUTPUT1_INVERTED        0x08    /* inverted output */
/* TOQ01 pin output setting (TQ0OE1) */
#define    TMQ_OUTPUT1_DISABLE            0x00    /* disable timer output */
#define    TMQ_OUTPUT1_ENABLE            0x04    /* enable timer output (TOQ01 pin outputs pulses) */
/* TOQ02 pin output level setting (TQ0OL2) */
#define    TMQ_OUTPUT2_NORMAL            0x00    /* normal output */
#define    TMQ_OUTPUT2_INVERTED        0x20    /* inverted output */
/* TOQ02 pin output setting (TQ0OE2) */
#define    TMQ_OUTPUT2_DISABLE            0x00    /* disable timer output */
#define    TMQ_OUTPUT2_ENABLE            0x10    /* enable timer output (TOQ02 pin outputs pulses) */
/* TOQ03 pin output level setting (TQ0OL3) */
#define    TMQ_OUTPUT3_NORMAL            0x00    /* normal output */
#define    TMQ_OUTPUT3_INVERTED        0x80    /* inverted output */
/* TOQ03 pin output setting (TQ0OE3) */
#define    TMQ_OUTPUT3_DISABLE            0x00    /* disable timer output */
#define    TMQ_OUTPUT3_ENABLE            0x40    /* enable timer output (TOQ03 pin outputs pulses) */

/* 
    TMQ0 I/O control register 1 (TQ0IOC1)
*/
/* Capture trigger input signal (TIQ00 pin) valid edge setting (TQ0IS1,TQ0IS0) */
#define    TMQ_INPUT0_EDGE_NONE        0x00    /* detect no edge (capture operation is invalid) */
#define    TMQ_INPUT0_EDGE_RISING        0x01    /* detection of rising edge */
#define    TMQ_INPUT0_EDGE_FALLING        0x02    /* detection of falling edge */
#define    TMQ_INPUT0_EDGE_BOTH        0x03    /* detection of both edges */
/* Capture trigger input signal (TIQ01 pin) valid edge setting (TQ0IS3,TQ0IS2) */
#define    TMQ_INPUT1_EDGE_NONE        0x00    /* detect no edge (capture operation is invalid) */
#define    TMQ_INPUT1_EDGE_RISING        0x04    /* detection of rising edge */
#define    TMQ_INPUT1_EDGE_FALLING        0x08    /* detection of falling edge */
#define    TMQ_INPUT1_EDGE_BOTH        0x0c    /* detection of both edges */
/* Capture trigger input signal (TIQ02 pin) valid edge setting (TQ0IS5,TQ0IS4) */
#define    TMQ_INPUT2_EDGE_NONE        0x00    /* detect no edge (capture operation is invalid) */
#define    TMQ_INPUT2_EDGE_RISING        0x10    /* detection of rising edge */
#define    TMQ_INPUT2_EDGE_FALLING        0x20    /* detection of falling edge */
#define    TMQ_INPUT2_EDGE_BOTH        0x30    /* detection of both edges */
/* Capture trigger input signal (TIQ03 pin) valid edge setting (TQ0IS7,TQ0IS6) */
#define    TMQ_INPUT3_EDGE_NONE        0x00    /* detect no edge (capture operation is invalid) */
#define    TMQ_INPUT3_EDGE_RISING        0x40    /* detection of rising edge */
#define    TMQ_INPUT3_EDGE_FALLING        0x80    /* detection of falling edge */
#define    TMQ_INPUT3_EDGE_BOTH        0xc0    /* detection of both edges */

/* 
    TMQ0 I/O control register 2 (TQ0IOC2)
*/
/* External event count input signal (TIQ00 pin) valid edge setting (TQ0EES1,TQ0EES0) */
#define    TMQ_EXTCOUNT_EDGE_NONE        0x00    /* detect no edge (external event count is invalid) */
#define    TMQ_EXTCOUNT_EDGE_RISING    0x04    /* detection of rising edge */
#define    TMQ_EXTCOUNT_EDGE_FALLING    0x08    /* detection of falling edge */
#define    TMQ_EXTCOUNT_EDGE_BOTH        0x0c    /* detection of both edges */
/* External trigger input signal (TIQ00 pin) valid edge setting (TQ0ETS1,TQ0ETS0) */
#define    TMQ_EXTTRIGGER_EDGE_NONE    0x00    /* detect no edge (external trigger is invalid) */
#define    TMQ_EXTTRIGGER_EDGE_RISING    0x01    /* detection of rising edge */
#define    TMQ_EXTTRIGGER_EDGE_FALLING    0x02    /* detection of falling edge */
#define    TMQ_EXTTRIGGER_EDGE_BOTH    0x03    /* detection of both edges */

/* 
    TMQ0 option register 0 (TQ0OPT0)
*/
/* TQ0CCR3 register capture/compare selection (TQ0CCS3) */
#define    TMQ_CCR3_COMPARE            0x00    /* compare register */
#define    TMQ_CCR3_CAPTURE            0x80    /* capture register */
/* TQ0CCR2 register capture/compare selection (TQ0CCS2) */
#define    TMQ_CCR2_COMPARE            0x00    /* compare register */
#define    TMQ_CCR2_CAPTURE            0x40    /* capture register */
/* TQ0CCR1 register capture/compare selection (TQ0CCS1) */
#define    TMQ_CCR1_COMPARE            0x00    /* compare register */
#define    TMQ_CCR1_CAPTURE            0x20    /* capture register */
/* TQ0CCR0 register capture/compare selection (TQ0CCS0) */
#define    TMQ_CCR0_COMPARE            0x00    /* compare register */
#define    TMQ_CCR0_CAPTURE            0x10    /* capture register */
/* TMQ0 overflow detection flag (TQ0OVF) */
#define TMQ_OVERFLOW_OCCUR            0x01    /* overflow occurred */
#define TMQ_OVERFLOW_CLEAR            0x00    /* clear overflow */

/* 
    TMM0 control register 0 (TM0CTL0)
*/
/* TMM0 operation control (TM0CE) */
#define    TMM_OPERATION_DISABLE        0x00    /* disable internal operating clock operation (asynchronously reset TMM0) */
#define    TMM_OPERATION_ENABLE        0x80    /* enable internal operating clock operation */
/* Internal count clock selection (TM0CKS2,TM0CKS1,TM0CKS0) */
#define    TMM_INTERNAL_CLOCK0            0x00    /* fXX */
#define    TMM_INTERNAL_CLOCK1            0x01    /* fXX/2 */
#define    TMM_INTERNAL_CLOCK2            0x02    /* fXX/4 */
#define    TMM_INTERNAL_CLOCK3            0x03    /* fXX/64 */
#define    TMM_INTERNAL_CLOCK4            0x04    /* fXX/512 */
#define    TMM_INTERNAL_CLOCK5            0x05    /* INTWT */
#define    TMM_INTERNAL_CLOCK6            0x06    /* fR/8 */
#define    TMM_INTERNAL_CLOCK7            0x07    /* fXT */


/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/

/* TMM0 compare register 0 (TM0CMP0) */
#define TMM0_CMP0_VALUE            0x3E7F    // 500us  0.0005/(1/32M)-1 = 15999 = 0x63F
enum TMChannel { TMCHANNEL0, TMCHANNEL1, TMCHANNEL2, TMCHANNEL3 };

/******************************************************************************/
/*Timer TMP6 (TOP61) is used to control DCDC switch frequency!*/
_V850_ void v850_tmp6_init(void);
_V850_ void v850_tmp6_set_duty(uint8_t duty);
_V850_ void v850_tmp6_set_freq(uint32_t freq);
_V850_ void v850_tmp6_start(void);
_V850_ void v850_tmp6_stop(void);
/******************************************************************************/
/*Timer TMM0 is used to the system time tick!*/

_V850_ void v850_tmm0_init(void);
_V850_ void v850_tmm0_start(void);
_V850_ void v850_tmm0_stop(void);

/******************************************************************************/
/*Timer TMP8 (TOP81) is used to control OWC receive and TMP5 is output!*/

_V850_ void v850_tmp8_init(void);
_V850_ void v850_tmp8_set_captrue(void);
_V850_ void v850_tmp8_start(void);
_V850_ void v850_tmp8_stop(void);


_V850_ void v850_tmp5_init(void);
_V850_ void v850_tmp5_start(void);
_V850_ void v850_tmp5_stop(void);
_V850_ void v850_tmp5_set_ccr0(int16_t iTiming);

/******************************************************************************/
/*Timer TMP1 (TOP11) is used to control TFT black light!*/

_V850_ void v850_tmp1_init(void);
_V850_ void v850_tmp1_start(void);
_V850_ void v850_tmp1_stop(void);
_V850_ void v850_tmp1_set_duty(uint8_t duty);
_V850_ void v850_tmp1_set_freq(uint32_t freq);

/******************************************************************************/
/*Timer TMP4 (TOP41) is used to control Fan speed!*/

_V850_ void v850_tmp4_init(void);
_V850_ void v850_tmp4_start(void);
_V850_ void v850_tmp4_stop(void);
_V850_ void v850_tmp4_set_duty(uint8_t duty);
_V850_ void v850_tmp4_set_freq(uint32_t freq);

/******************************************************************************/
/*Timer TMQ0 (TOQ01~TOQ03) is used to control KEY led!*/

_V850_ void v850_tmq0_init(void);
_V850_ void v850_tmq0_start(void);
_V850_ void v850_tmq0_stop(void);
_V850_ void v850_tmq0_set_duty(uint8_t idx,uint8_t duty);
_V850_ void v850_tmq0_set_freq(uint32_t freq);


