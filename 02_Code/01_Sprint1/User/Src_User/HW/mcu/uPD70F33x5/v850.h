/*
*******************************************************************************
**
**  Device :    uPD70F3355
**
**  Compiler :    CA850
**
**  Creation date:    2013-3-27
**  
*******************************************************************************
*/
#ifndef _V850_H_
#define _V850_H_



#ifndef _V850_C_
#define _V850_  extern
#else
#define _V850_
#endif

#if _COMPILER_ == _IAR_EWV850_
#include <intrinsics.h>
#include "io70f3355.h"

#define DI()   __DI()    
#define EI()   __EI()       
#define NOP()  __NOP()     
#define HALT() __HALT()     

#else
#if D_USE_COMILER_REG_MAP
#pragma ioreg                    //编译器相关，使能CA850内部寄存器定义
#endif

#include "v850_reg.h"


#define    EI()    __asm("ei")
#define    DI()    __asm("di")
#define    NOP()    __asm("nop")
#define    HALT()    __asm("halt")
#endif


#define CLEAR_WATCHDOG()     (WDTE = 0xac)




typedef    unsigned short    MD_STATUS;

#define    MD_ON        1
#define    MD_OFF        0

#define    MD_TRUE        1
#define    MD_FALSE    0

/* Status list definition */
#define    MD_STATUSBASE        0x00
#define    MD_OK                (MD_STATUSBASE + 0x0)    /* register setting OK */
#define    MD_RESET            (MD_STATUSBASE + 0x1)    /* reset input */
#define    MD_SENDCOMPLETE        (MD_STATUSBASE + 0x2)    /* send data complete */
#define    MD_ADDRESSMATCH        (MD_STATUSBASE + 0x3)    /* IIC slave address match */
#define    MD_OVF                (MD_STATUSBASE + 0x4)    /* timer count overflow */
#define    MD_SPT                (MD_STATUSBASE + 0x7)    /* IIC stop */
#define    MD_NACK                (MD_STATUSBASE + 0x8)    /* IIC no ACK */
#define    MD_SLAVE_SEND_END    (MD_STATUSBASE + 0x9)    /* IIC slave send end */
#define    MD_SLAVE_RCV_END    (MD_STATUSBASE + 0x0A)    /* IIC slave receive end */
#define    MD_MASTER_SEND_END    (MD_STATUSBASE + 0x0B)    /* IIC master send end */
#define    MD_MASTER_RCV_END    (MD_STATUSBASE + 0x0C)    /* IIC master receive end */
#define    MD_UNDEREXEC        (MD_STATUSBASE + 0x0D)    /* DMA transfer under execute */
#define    MD_COMPLETED        (MD_STATUSBASE + 0x0E)    /* DMA transfer completed */

/* Error list definition */
#define    MD_ERRORBASE        0x80
#define    MD_ERROR            (MD_ERRORBASE + 0x0)    /* error */
#define    MD_RESOURCEERROR    (MD_ERRORBASE + 0x1)    /* no resource available */
#define    MD_PARITYERROR        (MD_ERRORBASE + 0x2)    /* UARTn parity error n=0,1,2 */
#define    MD_OVERRUNERROR        (MD_ERRORBASE + 0x3)    /* UARTn overrun error n=0,1,2 */
#define    MD_FRAMEERROR        (MD_ERRORBASE + 0x4)    /* UARTn frame error n=0,1,2 */
#define    MD_ARGERROR            (MD_ERRORBASE + 0x5)    /* Error agrument input error */
#define    MD_TIMINGERROR        (MD_ERRORBASE + 0x6)    /* Error timing operation error */
#define    MD_SETPROHIBITED    (MD_ERRORBASE + 0x7)    /* setting prohibited */
#define    MD_ODDBUF            (MD_ERRORBASE + 0x8)    /* in 16bit transfer mode,buffer size should be even */
#define    MD_DATAEXISTS        (MD_ERRORBASE + 0x9)    /* Data to be transferred next exists in TXBn register */
#define    MD_STSERROR            (MD_ERRORBASE + 0x0A)    /* CAN status error */
#define    MD_ALRDYSTART        (MD_ERRORBASE + 0x0B)    /* CAN-controller is already started error */
#define    MD_NOMSG            (MD_ERRORBASE + 0x0C)    /* CAN message not received */


/*
*******************************************************************************
**    Register bit define
*******************************************************************************
*/
/*
    Processor clock control register (PCC)
*/
#define    CG_PCC_INITIALVALUE            0x03
/* Use of subclock on-chip feedback resistor (FRC) */
#define    CG_SUBCLK_FEEDBACK_USE        0x00    /* subclock on-chip feedback resistor connected */
#define    CG_SUBCLK_FEEDBACK_UNUSE    0x80    /* subclock on-chip feedback resistor not connected */
/* Main clock osillator control (MCK) */
#define    CG_MAINCLK_ENABLE            0x00    /* main clock oscillation enabled */
#define    CG_MAINCLK_STOP                0x40    /* main clock oscillation stopped */
/* Use of main clock on-chip feedback resistor (MFRC) */
#define    CG_MAINCLK_FEEDBACK_USE        0x00    /* main clock feedback resistor connected */
#define    CG_MAINCLK_FEEDBACK_UNUSE    0x20    /* main clock feedback resistor not connected */
/* Status of CPU clock fCPU (CLS) */
#define    CG_CPUCLK_MAINCLK            0x00    /* main clock operation */
#define    CG_CPUCLK_SUBCLK            0x10    /* subclock operation */
/* Clock(fCLK/fCPU) selection (CK3~0) */
#define    CG_CPUCLK                    0x0f
#define    CG_CPUCLK_MAIN0                0x00    /* fCPU = fXX */
#define    CG_CPUCLK_MAIN1                0x01    /* fCPU = fXX/2 */
#define    CG_CPUCLK_MAIN2                0x02    /* fCPU = fXX/4 */
#define    CG_CPUCLK_MAIN3                0x03    /* fCPU = fXX/8 */
#define    CG_CPUCLK_MAIN4                0x04    /* fCPU = fXX/16 */
#define    CG_CPUCLK_MAIN5                0x05    /* fCPU = fXX/32 */
#define    CG_CPUCLK_SUB                0x0B    /* fXT */

/*
    Internal oscillator mode register (RCM)
*/
/* Oscillation/stop of internal oscillator (RSTOP) */
#define    CG_INTER_OSC_ON                0x00    /* internal oscillator oscillation */
#define    CG_INTER_OSC_OFF            0x01    /* internal oscillator stopped */

/*
    CPU operation clock status register (CCLS)
*/
/* CPU operation clock status (CCLSF) */
#define    CG_CPUCLK_STATUS_MAINORSUB    0x00    /* operating on main clock(fX) or subclock(fXT) */
#define    CG_CPUCLK_STATUS_INTEROSC    0x01    /* operating on internal oscillation clock(fR) */

/*
    Lock register (LOCKR)
*/
/* PLL lock status check (LOCK) */
#define    CG_PLLSTATUS_LOCK        0x00    /* locked status */
#define    CG_PLLSTATUS_UNLOCK        0x01    /* unlocked status */

/*
    PLL control register (PLLCTL)
*/
#define    CG_PLLCTL_INITIALVALUE    0x01
/* CPU operation clock selection register (SELPLL) */
#define    CG_CPUCLK_CLKTHROUGH    0x00    /* clock-through mode */
#define    CG_CPUCLK_PLL            0x02    /* PLL mode */
/* PLL operation stop register (PLLON) */
#define    CG_CPUCLK_PLLOFF        0x00    /* PLL stopped */
#define    CG_CPUCLK_PLLON            0x01    /* PLL operating */

/*
    Clock control register (CKC)
*/
#define    CG_CKC_INITIALVALUE        0x0A
/* Internal system clock(fXX) in PLL mode */
#define    CG_CPUCLK_4PLL            0x00    /* fXX = 4* fX (fX = 2.5 to 5.0 MHz) */
#define    CG_CPUCLK_8PLL            0x01    /* fXX = 8* fX (fX = 2.5 to 4.0 MHz) */

/*
    PLL lockup time specification register (PLLS)
*/
#define    CG_PLLS_INITIALVALUE    0x03
/* PLL lockup time selection (PLLS2~0) */
#define    CG_PLLLOCKUP_SEL0        0x00    /* 2^10/fX */
#define    CG_PLLLOCKUP_SEL1        0x01    /* 2^11/fX*/
#define    CG_PLLLOCKUP_SEL2        0x02    /* 2^12/fX */
#define    CG_PLLLOCKUP_SEL3        0x03    /* 2^13/fX (default value) */

/*
    Power save control register (PSC)
*/
/* Stand-by mode release control by occurrence of INTWDT2 signal (NMI1M) */
#define    CG_STANDBY_INTWDT2EN    0x00    /* enable releasing stand-by mode by INTWDT2 signal */
#define    CG_STANDBY_INTWDT2DIS    0x40    /* disable releasing stand-by mode by INTWDT2 signal */
/* Stand-by mode release control by NMI pin input (NMI0M) */
#define    CG_STANDBY_NMIEN        0x00    /* enable releasing stand-by mode by NMI pin input */
#define    CG_STANDBY_NMIDIS        0x20    /* disable releasing stand-by mode by NMI pin input */
/* Stand-by mode release control by maskable interrupt request signal (NMI0M) */
#define    CG_STANDBY_MASKIEN        0x00    /* enable releasing stand-by mode by maskable interrupt request signal */
#define    CG_STANDBY_MASKIDIS        0x10    /* disable releasing stand-by mode by maskable interrupt request signal */
/* Setting of stand-by mode (STP) */
#define    CG_STANDBY_UNUSE        0x00    /* normal mode */
#define    CG_STANDBY_USE            0x02    /* stand-by mode */

/*
    Power save mode control register (PSMR)
*/
/* Specification of operation in software stand-by mode (PSM1~0) */
#define    CG_POWERSAVE_IDLE1        0x00    /* IDLE1, sub-IDLE modes */
#define    CG_POWERSAVE_STOP1        0x01    /* STOP, sub-IDLE modes */
#define    CG_POWERSAVE_IDLE2        0x02    /* IDLE2, sub-IDLE modes */
#define    CG_POWERSAVE_STOP2        0x03    /* STOP mode */

/*
    Clock monitor mode register (CLM)
*/
/* Clock monitor operation enable or disable (CLME) */
#define    CG_MONITOR_ENABLE        0x01    /* enable clock monitor operation */
#define    CG_MONITOR_DISABLE        0x00    /* disable clock monitor operation */

/*
    Watchdog Timer 2 mode register (WDTM2)
*/
/* Selection of operation mode (WDM21, WDM20) */
#define    WDT2_OPERMODE_STOP        0x00    /* stops operation */
#define    WDT2_OPERMODE_NONMASK    0x20    /* non-maskable interrupt request mode (generation of INTWDT2) */
#define    WDT2_OPERMODE_RESET        0x40    /* reset mode (generation of RESWDT2) */
/* Selection of clock mode (WDCS24,WDCS23) */
#define    WDT2_CLKMODE_INTEROSC    0x00    /* use internal oscillator */
#define    WDT2_CLKMODE_MAINCLK    0x08    /* use Main clock */
#define    WDT2_CLKMODE_SUBCLK        0x10    /* use subclock */
/* Watchdog Timer 2 clock Selection (WDCS22~WDCS20) */
#define    WDT2_CLOCK_SEL0            0x00    /* 2^12/fR or 2^18/fXX or 2^9/fXT */
#define    WDT2_CLOCK_SEL1            0x01    /* 2^13/fR or 2^19/fXX or 2^10/fXT */
#define    WDT2_CLOCK_SEL2            0x02    /* 2^14/fR or 2^20/fXX or 2^11/fXT */
#define    WDT2_CLOCK_SEL3            0x03    /* 2^15/fR or 2^21/fXX or 2^12/fXT */
#define    WDT2_CLOCK_SEL4            0x04    /* 2^16/fR or 2^22/fXX or 2^13/fXT */
#define    WDT2_CLOCK_SEL5            0x05    /* 2^17/fR or 2^23/fXX or 2^14/fXT */
#define    WDT2_CLOCK_SEL6            0x06    /* 2^18/fR or 2^24/fXX or 2^15/fXT */
#define    WDT2_CLOCK_SEL7            0x07    /* 2^19/fR or 2^25/fXX or 2^16/fXT */

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define    CG_MAINOSC_FREQ            4
#define    CG_VSWC_VALUE              0x11
#define    CG_LOCK_WAITTIME           2000
#define    CG_FBRG_PRSM0              0x0
#define       CG_FBRG_PRSCM0              0x3d


/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void CLOCK_Init(void);
void WDT2_Restart(void);
void CG_ReadResetSource(void);
/* Start user code for definition. Do not edit comment generated here */
/* End user code for definition. Do not edit comment generated here */

/*
    UARTAn control register 0(UAnCTL0)
*/
#define    UARTA_UAnCTL0_INITIALVALUE        0x10
/* UARTAn operation control(UAnPWR) */
#define    UARTA_OPERATION_DISABLE            0x00    /* disable UARTAn operation (UARTAn reset asynchronously) */
#define    UARTA_OPERATION_ENABLE            0x80    /* enable UARTAn operation */
/* Transmission operation enable(UAnTXE) */
#define    UARTA_TRANSMISSION_DISABLE        0x00    /* disable transmission operation */
#define    UARTA_TRANSMISSION_ENABLE        0x40    /* enable transmission operation */
/* Reception operation enable(UAnRXE) */
#define    UARTA_RECEPTION_DISABLE            0x00    /* disable reception operation */
#define    UARTA_RECEPTION_ENABLE            0x20    /* enable reception operation */
/* Transfer direction selection(UAnDIR) */
#define    UARTA_TRANSFDIR_MSB                0x00    /* MSB-first transfer */
#define    UARTA_TRANSFDIR_LSB                0x10    /* LSB-first transfer */
/* Parity selection during transmission/reception(UAnPS1,UAnPS0) */
#define    UARTA_PARITY_NONE                0x00    /* no parity output/Reception with no parity */
#define    UARTA_PARITY_ZREO                0x04    /* 0 parity output/Reception with 0 parity */
#define    UARTA_PARITY_ODD                0x08    /* odd parity output/Odd parity check */
#define    UARTA_PARITY_EVEN                0x0C    /* even parity output/Even parity check */
/* Specification of data character length of 1 frame of transmit/receive data(UAnCL) */
#define    UARTA_DATALENGTH_7BIT            0x00    /* 7 bits */
#define    UARTA_DATALENGTH_8BIT            0x02    /* 8 bits */
/* Specification of length of stop bit for transmit data(UAnSL) */
#define    UARTA_STOPLENGTH_1BIT            0x00    /* 1 bit */
#define    UARTA_STOPLENGTH_2BIT            0x01    /* 2 bits */

/*
    UARTAn base clock selects register(UAnCTL1)
*/
/* UAnCTL1 register(UAnCKS3, UAnCKS2, UAnCKS1, UAnCKS0) */
#define    UARTA_BASECLK_FXX_1                0x00    /* fXX */
#define    UARTA_BASECLK_FXX_2                0x01    /* fXX/2 */
#define    UARTA_BASECLK_FXX_4                0x02    /* fXX/4 */
#define    UARTA_BASECLK_FXX_8                0x03    /* fXX/8 */
#define    UARTA_BASECLK_FXX_16            0x04    /* fXX/16 */
#define    UARTA_BASECLK_FXX_32            0x05    /* fXX/32 */
#define    UARTA_BASECLK_FXX_64            0x06    /* fXX/64 */
#define    UARTA_BASECLK_FXX_128            0x07    /* fXX/128 */
#define    UARTA_BASECLK_FXX_256            0x08    /* fXX/256 */
#define    UARTA_BASECLK_FXX_512            0x09    /* fXX/512 */
#define    UARTA_BASECLK_FXX_1024            0x0A    /* fXX/1024 */
#define    UARTA_BASECLK_ASCKA0            0x0B    /* external clock (ASCKA0 pin) */

/*
    UARTAn option control register 0 (UAnOPT0)
*/
#define    UARTA_UAnOPT0_INITIALVALUE        0x14
/* Transmit data level bit(UAnTDL) */
#define    UARTA_TRAN_DATALEVEL_NORMAL        0x00    /* normal output of transfer data */
#define    UARTA_TRAN_DATALEVEL_INVERTED    0x02    /* inverted output of transfer data */
/* Receive data level bit(UAnRDL) */
#define    UARTA_REC_DATALEVEL_NORMAL        0x00    /* normal input of transfer data */
#define    UARTA_REC_DATALEVEL_INVERTED    0x01    /* inverted input of transfer data */

/*
    CSIBn control register 0 (CBnCTL0)
*/
/* Specification of CSIBn operation disable/enable (CBnPWR)*/
#define CSIB_OPERATION_DISABLE    0x00    /* disable CSIBn operation and reset the CBnSTR register */
#define CSIB_OPERATION_ENABLE    0x80    /* enable CSIBn operation */
/* Specification of transmit operation disable/enable (CBnTXE)*/
#define CSIB_TRANSMIT_DISABLE    0x00    /* disable transmit operation */
#define CSIB_TRANSMIT_ENABLE    0x40    /* enable transmit operation */
/* Specification of receive operation disable/enable (CBnRXE)*/
#define CSIB_RECEIVE_DISABLE    0x00    /* disable receive operation */
#define CSIB_RECEIVE_ENABLE        0x20    /* enable receive operation */
/* Specification of transfer direction mode (MSB/LSB) (CBnDIR) */
#define CSIB_DATA_MSB            0x00    /* MSB first */ 
#define CSIB_DATA_LSB            0x10    /* LSB first */
/* Transfer mode specification (CBnTMS) */
#define CSIB_MODE_SINGLE        0x00    /* single transfer mode */
#define    CSIB_MODE_CONTINUOUS    0x02    /* continuous transfer mode */
/* Specification of start transfer disable/enable (CBnSCE) */
#define CSIB_STARTTRG_INVALID    0x00    /* communication start trigger invalid */
#define    CSIB_STARTTRG_VALID        0x01    /* communication start trigger valid */

/*
    CSIBn control register 1 (CBnCTL1)
*/
/* Specification of data transmission/reception timing in relation to SCKBn (CBnCKP, CBnDAP) */
#define    CSIB_DATA_TIMING1        0x00    /* communication type 1 */
#define    CSIB_DATA_TIMING2        0x08    /* communication type 2 */
#define    CSIB_DATA_TIMING3        0x10    /* communication type 3 */
#define    CSIB_DATA_TIMING4        0x18    /* communication type 4 */
/* Specification of input clock (CBnCKS2,CBnCKS1,CBnCKS0) */
#define    CSIB_CLOCK_1            0x00    /* fXX /2 */
#define    CSIB_CLOCK_2            0x01    /* fXX/4 */
#define    CSIB_CLOCK_3            0x02    /* fXX /8 */    
#define    CSIB_CLOCK_4            0x03    /* fXX /16 */
#define    CSIB_CLOCK_5            0x04    /* fXX /32 */
#define    CSIB_CLOCK_6            0x05    /* fXX /64 */
#define    CSIB_CLOCK_7            0x06    /* fBRGm */
#define    CSIB_CLOCK_EXT            0x07    /* external clock SCKBn */

/*
    CSIBn control register 2 (CBnCTL2)
*/
/* Serial register bit length (CBnCL3,CBnCL2,CBnCL1,CBnCL0) */
#define    CSIB_DATA_LENGTH_8        0x00    /* 8 bits */
#define    CSIB_DATA_LENGTH_9        0x01    /* 9 bits */
#define    CSIB_DATA_LENGTH_10        0x02    /* 10 bits */
#define    CSIB_DATA_LENGTH_11        0x03    /* 11 bits */
#define    CSIB_DATA_LENGTH_12        0x04    /* 12 bits */
#define    CSIB_DATA_LENGTH_13        0x05    /* 13 bits */
#define    CSIB_DATA_LENGTH_14        0x06    /* 14 bits */
#define    CSIB_DATA_LENGTH_15        0x07    /* 15 bits */
#define    CSIB_DATA_LENGTH_16        0x08    /* 16 bits */

/*
    CSIBn status register (CBnSTR)
*/
/* Communication status flag (CBnTSF) */
#define CSIB_COMMUNICATION_STOP    0x00    /* communication stopped */
#define CSIB_COMMUNICATING        0x80    /* communicating */
/* Overrun error flag (CBnOVE) */
#define CSIB_OVERRUN_NONE        0x00    /* no overrun */
#define CSIB_OVERRUN            0x01    /* overrun */

/*
    BRGm prescaler mode registers (PRSMm)
*/
/* Baud rate output(BGCEm) */
#define    CSIB_FBRGM_DISABLE        0x00    /* baudrate output disabled */
#define    CSIB_FBRGM_ENABLE        0x10    /* baudrate output enabled */
/* Input clock selection (BGCSm1,BGCSm0) */
#define    CSIB_FBGCS_0            0x00    /* fXX */    
#define    CSIB_FBGCS_1            0x01    /* fXX/2 */
#define    CSIB_FBGCS_2            0x02    /* fXX/4 */
#define    CSIB_FBGCS_3            0x03    /* fXX/8 */

/*
    IIC control register (IICCn)
*/
/* IIC operation enable    (IICEn)    */
#define    IIC_OPERATION                0x80
#define    IIC_OPERATION_DISABLE        0x00    /* stop operation */
#define    IIC_OPERATION_ENABLE        0x80    /* enable operation */
/* Exit    from communications    (LRELn)    */
#define    IIC_COMMUNICATION            0x40
#define    IIC_COMMUNICATION_NORMAL    0x00    /* normal operation    */
#define    IIC_COMMUNICATION_EXIT        0x40    /* exit    from current communication */
/* Wait    cancellation (WRELn) */
#define    IIC_WAITCANCEL                0x20
#define    IIC_WAIT_NOTCANCEL            0x00    /* do not cancel wait */
#define    IIC_WAIT_CANCEL                0x20    /* cancel wait */
/* Generation of interrupt when    stop condition (SPIEn) */
#define    IIC_STOPINT                    0x10
#define    IIC_STOPINT_DISABLE            0x00    /* disable */
#define    IIC_STOPINT_ENABLE            0x10    /* enable */
/* Wait    and interrupt generation (WTIMn) */
#define    IIC_WAITINT                    0x08
#define    IIC_WAITINT_CLK8FALLING        0x00    /* generate at the eighth clock falling edge */
#define    IIC_WAITINT_CLK9FALLING        0x08    /* generated at the ninth clock falling edge */
/* Acknowledgement control (ACKEn) */
#define    IIC_ACK                        0x04
#define    IIC_ACK_DISABLE                0x00    /* disable acknowledgement */
#define    IIC_ACK_ENABLE                0x04    /* enable acknowledgement */
/* Start condition trigger (STTn) */
#define    IIC_STARTCONDITION            0x02
#define    IIC_START_NOTGENERATE        0x00    /* do not generate start condition */
#define    IIC_START_GENERATE            0x02    /* generate start condition */
/* Stop    condition trigger (SPTn) */
#define    IIC_STOPCONDITION            0x01
#define    IIC_STOP_NOTGENERATE        0x00    /* do not generate stop condition */
#define    IIC_STOP_GENERATE            0x01    /* generate stop condition */

/*
    IIC    Status Register    (IICSn)
*/
/* Master device status (MSTSn) */
#define    IIC_MASTERSTATUS            0x80
#define    IIC_STATUS_NOTMASTER        0x00    /* slave device status or communication standby status */
#define    IIC_STATUS_MASTER            0x80    /* master device communication status */
/* Detection of arbitration    loss (ALDn) */
#define    IIC_ARBITRATION                0x40
#define    IIC_ARBITRATION_NO            0x00    /* arbitration win or no arbitration */
#define    IIC_ARBITRATION_LOSS        0x40    /* arbitration loss */
/* Detection of extension code reception (EXCn) */
#define    IIC_EXTENSIONCODE            0x20
#define    IIC_EXTCODE_NOT                0x00    /* extension code not received */
#define    IIC_EXTCODE_RECEIVED        0x20    /* extension code received */
/* Detection of matching addresses (COIn) */
#define    IIC_ADDRESSMATCH            0x10
#define    IIC_ADDRESS_NOTMATCH        0x00    /* addresses do not match */
#define    IIC_ADDRESS_MATCH            0x10    /* addresses match */
/* Detection of transmit/receive status    (TRCn) */
#define    IIC_STATUS                    0x08
#define    IIC_STATUS_RECEIVE            0x00    /* receive status */
#define    IIC_STATUS_TRANSMIT            0x08    /* transmit status */
/* Detection of acknowledge signal (ACKDn) */
#define    IIC_ACKDETECTION            0x04
#define    IIC_ACK_NOTDETECTED            0x00    /* ACK signal was not detected */
#define    IIC_ACK_DETECTED            0x04    /* ACK signal was detected */
/* Detection of start condition (STDn) */
#define    IIC_STARTDETECTION            0x02
#define    IIC_START_NOTDETECTED        0x00    /* start condition not detected */
#define    IIC_START_DETECTED            0x02    /* start condition detected */
/* Detection of stop condition (SPDn) */
#define    IIC_STOPDETECTION            0x01
#define    IIC_STOP_NOTDETECTED        0x00    /* stop    condition not detected */
#define    IIC_STOP_DETECTED            0x01    /* stop    condition detected */

/*
    IIC    Flag Register (IICFn)
*/
/* STTn    clear flag (STCFn) */
#define    IIC_STARTFLAG                0x80
#define    IIC_STARTFLAG_GENERATE        0x00    /* generate start condition */
#define    IIC_STARTFLAG_UNSUCCESSFUL    0x80    /* start condition generation unsuccessful */
/* IIC bus status flag (IICBSYn)    */
#define    IIC_BUSSTATUS                0x40
#define    IIC_BUS_RELEASE                0x00    /* bus release status */
#define    IIC_BUS_COMMUNICATION        0x40    /* bus communication status */
/* Initial start enable trigger (STCENn)    */
#define    IIC_STARTWITHSTOP            0x02
#define    IIC_START_WITHSTOP            0x00    /* generation of a start condition upon detection of a stop condition */
#define    IIC_START_WITHOUTSTOP        0x02    /* generation of a start condition without detecting a stop condition */
/* Communication reservation function disable bit (IICRSVn) */
#define    IIC_RESERVATION                0x01
#define    IIC_RESERVATION_ENABLE        0x00    /* enable communication reservation */
#define    IIC_RESERVATION_DISABLE        0x01    /* disable communication reservation */

/*
    IIC clock selection register (IICCLn)
*/
#define IICCL_INITIALVALUE             0x00
/* Detection of SCL0n pin level (CLDn) */
#define    IIC_SCLLEVEL                0x20
#define    IIC_SCL_LOW                    0x00    /* clock line at low level */
#define    IIC_SCL_HIGH                0x20    /* clock line at high level */
/* Detection of SDA0 pin level (DADn) */
#define    IIC_SDALEVEL                0x10
#define    IIC_SDA_LOW                    0x00    /* data    line at low level */
#define    IIC_SDA_HIGH                0x10    /* data    line at high level */
/* Operation mode switching (SMCn) */
#define    IIC_OPERATIONMODE            0x08
#define    IIC_MODE_STANDARD            0x00    /* operates in standard mode */
#define    IIC_MODE_HIGHSPEED            0x08    /* operates in high-speed mode */
/* Digital filter operation control (DFCn) */
#define    IIC_DIGITALFILTER            0x04
#define    IIC_FILTER_OFF                0x00    /* digital filter off */
#define    IIC_FILTER_ON                0x04    /* digital filter on */
/* Operation mode switching (CLn1, CLn0) */
#define    IIC_CLOCKSELECTION            0x03
/*    Combine of (CLn1, CLn0)*/
#define    IIC_CLOCK0                    0x00
#define    IIC_CLOCK1                    0x01
#define    IIC_CLOCK2                    0x02
#define    IIC_CLOCK3                    0x03

/*
    IIC division clock select register (OCKSn)
*/
#define    IIC_SELECTED0                0x10
#define    IIC_SELECTED1                0x11
#define    IIC_SELECTED2                0x12
#define    IIC_SELECTED3                0x13
#define    IIC_SELECTED4                0x18

/*
    IIC function expansion register    0 (IICXn)
*/
/* IIC clock expension (CLXn) */
#define    IIC_CLOCKEXPENSION            0x01
#define    IIC_EXPENSION0                0x00
#define    IIC_EXPENSION1                0x01

#define ADDRESS_COMPLETE            0x80
#define IIC_MASTER_FLAG_CLEAR        0x00


/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
#if D_PRINT_EN
_V850_ void v850_putc(uint8_t d);
#else
#define v850_putc(d) 
#endif
#include "v850_clock.h"
#include "v850_dma.h"
#include "v850_timer.h"
#include "v850_io.h"
#include "v850_i2c.h"
#include "v850_spi.h"
#include "v850_uart.h"

_V850_ void v850_enter_lp_mode(void);
_V850_ void v850_sleep(void);
_V850_ void v850_awake(void);
_V850_ void v850_init(void);

_V850_ void v850_adc_stop(void);
_V850_ void v850_Enter_Sub_Idle(void);

_V850_ void  INTP3_Init(void);
_V850_ void INTP3_Enable(void);
_V850_ void INTP3_Disable(void);
_V850_ void INTP3_isr(void);
_V850_ void  INTP0_Init(void);
_V850_ void INTP0_Enable(void);
_V850_ void INTP0_Disable(void);
_V850_ void INTP0_isr(void);
_V850_ void v850_EnterStop(void);
_V850_ void Disable_External_Interrupt(void);
_V850_ void Close_Peripheral(void);
_V850_ void WakeUp_Mode(void);	
_V850_ void Disable_INTP0_Trigger(void);
_V850_ void Disable_INTP3_Trigger(void);
_V850_ void Enable_INTP0_Trigger(void);
_V850_ void Enable_INTP3_Trigger(void);
#endif

