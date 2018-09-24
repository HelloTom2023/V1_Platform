/*-------------------------------------------------------------------------
 *      Declarations of Peripheral I/O registers, I/O register bits,
 *      Interrupt/Exeption vectors, Trap vectors and, V850E only, Callt
 *      vectors for V850ES microcontroller uPD70F3365.
 *
 *      This header file can be used by both the V850 assembler, AV850,
 *      and the V850 C/C++ compiler, ICCV850.
 *
 *      This header file is generated from the device file:
 *          DF3365.800
 *          Format version 2.18, File version 1.10 
 *
 *-------------------------------------------------------------------------*/

#ifndef __IO70F3365_H__
#define __IO70F3365_H__

#if ((__TID__ >> 8) & 0x7F) != 85
#error "IO70F3365.H file for use with AV850 / ICCV850 only"
#endif

#if ((__TID__ >> 4) & 0x0F) != 1
#error "IO70F3365.H file for use with AV850 / ICCV850 option -v1 only"
#endif

#pragma language=extended
#pragma system_include

/***********************************************
 *       I/O register macros
 ***********************************************/

#include "io_macros.h"

/***********************************************
 *       Peripheral I/O register declarations
 ***********************************************/


__IO_REG16(     PDL,             0xFFFFF004,  __READ_WRITE )
__IO_REG8_BIT(  PDLL,            0xFFFFF004,  __READ_WRITE )
__IO_REG8_BIT(  PDLH,            0xFFFFF005,  __READ_WRITE )
__IO_REG8_BIT(  PDH,             0xFFFFF006,  __READ_WRITE )
__IO_REG8_BIT(  PCS,             0xFFFFF008,  __READ_WRITE )
__IO_REG8_BIT(  PCT,             0xFFFFF00A,  __READ_WRITE )
__IO_REG8_BIT(  PCM,             0xFFFFF00C,  __READ_WRITE )
__IO_REG8_BIT(  PCD,             0xFFFFF00E,  __READ_WRITE )

__IO_REG16(     PMDL,            0xFFFFF024,  __READ_WRITE )
__IO_REG8_BIT(  PMDLL,           0xFFFFF024,  __READ_WRITE )
__IO_REG8_BIT(  PMDLH,           0xFFFFF025,  __READ_WRITE )
__IO_REG8_BIT(  PMDH,            0xFFFFF026,  __READ_WRITE )
__IO_REG8_BIT(  PMCS,            0xFFFFF028,  __READ_WRITE )
__IO_REG8_BIT(  PMCT,            0xFFFFF02A,  __READ_WRITE )
__IO_REG8_BIT(  PMCM,            0xFFFFF02C,  __READ_WRITE )
__IO_REG8_BIT(  PMCD,            0xFFFFF02E,  __READ_WRITE )

__IO_REG16(     PMCDL,           0xFFFFF044,  __READ_WRITE )
__IO_REG8_BIT(  PMCDLL,          0xFFFFF044,  __READ_WRITE )
__IO_REG8_BIT(  PMCDLH,          0xFFFFF045,  __READ_WRITE )
__IO_REG8_BIT(  PMCDH,           0xFFFFF046,  __READ_WRITE )
__IO_REG8_BIT(  PMCCS,           0xFFFFF048,  __READ_WRITE )
__IO_REG8_BIT(  PMCCT,           0xFFFFF04A,  __READ_WRITE )
__IO_REG8_BIT(  PMCCM,           0xFFFFF04C,  __READ_WRITE )

__IO_REG16(     BPC,             0xFFFFF064,  __READ_WRITE )
__IO_REG16(     BSC,             0xFFFFF066,  __READ_WRITE )

__IO_REG8(      VSWC,            0xFFFFF06E,  __READ_WRITE )

__IO_REG16(     DSA0L,           0xFFFFF080,  __READ_WRITE )
__IO_REG16(     DSA0H,           0xFFFFF082,  __READ_WRITE )
__IO_REG16(     DDA0L,           0xFFFFF084,  __READ_WRITE )
__IO_REG16(     DDA0H,           0xFFFFF086,  __READ_WRITE )
__IO_REG16(     DSA1L,           0xFFFFF088,  __READ_WRITE )
__IO_REG16(     DSA1H,           0xFFFFF08A,  __READ_WRITE )
__IO_REG16(     DDA1L,           0xFFFFF08C,  __READ_WRITE )
__IO_REG16(     DDA1H,           0xFFFFF08E,  __READ_WRITE )
__IO_REG16(     DSA2L,           0xFFFFF090,  __READ_WRITE )
__IO_REG16(     DSA2H,           0xFFFFF092,  __READ_WRITE )
__IO_REG16(     DDA2L,           0xFFFFF094,  __READ_WRITE )
__IO_REG16(     DDA2H,           0xFFFFF096,  __READ_WRITE )
__IO_REG16(     DSA3L,           0xFFFFF098,  __READ_WRITE )
__IO_REG16(     DSA3H,           0xFFFFF09A,  __READ_WRITE )
__IO_REG16(     DDA3L,           0xFFFFF09C,  __READ_WRITE )
__IO_REG16(     DDA3H,           0xFFFFF09E,  __READ_WRITE )

__IO_REG16(     DBC0,            0xFFFFF0C0,  __READ_WRITE )
__IO_REG16(     DBC1,            0xFFFFF0C2,  __READ_WRITE )
__IO_REG16(     DBC2,            0xFFFFF0C4,  __READ_WRITE )
__IO_REG16(     DBC3,            0xFFFFF0C6,  __READ_WRITE )

__IO_REG16(     DADC0,           0xFFFFF0D0,  __READ_WRITE )
__IO_REG16(     DADC1,           0xFFFFF0D2,  __READ_WRITE )
__IO_REG16(     DADC2,           0xFFFFF0D4,  __READ_WRITE )
__IO_REG16(     DADC3,           0xFFFFF0D6,  __READ_WRITE )

__IO_REG8_BIT(  DCHC0,           0xFFFFF0E0,  __READ_WRITE )
__IO_REG8_BIT(  DCHC1,           0xFFFFF0E2,  __READ_WRITE )
__IO_REG8_BIT(  DCHC2,           0xFFFFF0E4,  __READ_WRITE )
__IO_REG8_BIT(  DCHC3,           0xFFFFF0E6,  __READ_WRITE )

__IO_REG16(     IMR0,            0xFFFFF100,  __READ_WRITE )
__IO_REG8_BIT(  IMR0L,           0xFFFFF100,  __READ_WRITE )
__IO_REG8_BIT(  IMR0H,           0xFFFFF101,  __READ_WRITE )
__IO_REG16(     IMR1,            0xFFFFF102,  __READ_WRITE )
__IO_REG8_BIT(  IMR1L,           0xFFFFF102,  __READ_WRITE )
__IO_REG8_BIT(  IMR1H,           0xFFFFF103,  __READ_WRITE )
__IO_REG16(     IMR2,            0xFFFFF104,  __READ_WRITE )
__IO_REG8_BIT(  IMR2L,           0xFFFFF104,  __READ_WRITE )
__IO_REG8_BIT(  IMR2H,           0xFFFFF105,  __READ_WRITE )
__IO_REG16(     IMR3,            0xFFFFF106,  __READ_WRITE )
__IO_REG8_BIT(  IMR3L,           0xFFFFF106,  __READ_WRITE )
__IO_REG8_BIT(  IMR3H,           0xFFFFF107,  __READ_WRITE )
__IO_REG16(     IMR4,            0xFFFFF108,  __READ_WRITE )
__IO_REG8_BIT(  IMR4L,           0xFFFFF108,  __READ_WRITE )
__IO_REG8_BIT(  IMR4H,           0xFFFFF109,  __READ_WRITE )

__IO_REG8_BIT(  LVIIC,           0xFFFFF110,  __READ_WRITE )
__IO_REG8_BIT(  PIC0,            0xFFFFF112,  __READ_WRITE )
__IO_REG8_BIT(  PIC1,            0xFFFFF114,  __READ_WRITE )
__IO_REG8_BIT(  PIC2,            0xFFFFF116,  __READ_WRITE )
__IO_REG8_BIT(  PIC3,            0xFFFFF118,  __READ_WRITE )
__IO_REG8_BIT(  PIC4,            0xFFFFF11A,  __READ_WRITE )
__IO_REG8_BIT(  PIC5,            0xFFFFF11C,  __READ_WRITE )
__IO_REG8_BIT(  PIC6,            0xFFFFF11E,  __READ_WRITE )
__IO_REG8_BIT(  PIC7,            0xFFFFF120,  __READ_WRITE )
__IO_REG8_BIT(  TQ0OVIC,         0xFFFFF122,  __READ_WRITE )
__IO_REG8_BIT(  TQ0CCIC0,        0xFFFFF124,  __READ_WRITE )
__IO_REG8_BIT(  TQ0CCIC1,        0xFFFFF126,  __READ_WRITE )
__IO_REG8_BIT(  TQ0CCIC2,        0xFFFFF128,  __READ_WRITE )
__IO_REG8_BIT(  TQ0CCIC3,        0xFFFFF12A,  __READ_WRITE )
__IO_REG8_BIT(  TP0OVIC,         0xFFFFF12C,  __READ_WRITE )
__IO_REG8_BIT(  TP0CCIC0,        0xFFFFF12E,  __READ_WRITE )
__IO_REG8_BIT(  TP0CCIC1,        0xFFFFF130,  __READ_WRITE )
__IO_REG8_BIT(  TP1OVIC,         0xFFFFF132,  __READ_WRITE )
__IO_REG8_BIT(  TP1CCIC0,        0xFFFFF134,  __READ_WRITE )
__IO_REG8_BIT(  TP1CCIC1,        0xFFFFF136,  __READ_WRITE )
__IO_REG8_BIT(  TP2OVIC,         0xFFFFF138,  __READ_WRITE )
__IO_REG8_BIT(  TP2CCIC0,        0xFFFFF13A,  __READ_WRITE )
__IO_REG8_BIT(  TP2CCIC1,        0xFFFFF13C,  __READ_WRITE )
__IO_REG8_BIT(  TP3OVIC,         0xFFFFF13E,  __READ_WRITE )
__IO_REG8_BIT(  TP3CCIC0,        0xFFFFF140,  __READ_WRITE )
__IO_REG8_BIT(  TP3CCIC1,        0xFFFFF142,  __READ_WRITE )
__IO_REG8_BIT(  TP4OVIC,         0xFFFFF144,  __READ_WRITE )
__IO_REG8_BIT(  TP4CCIC0,        0xFFFFF146,  __READ_WRITE )
__IO_REG8_BIT(  TP4CCIC1,        0xFFFFF148,  __READ_WRITE )
__IO_REG8_BIT(  TP5OVIC,         0xFFFFF14A,  __READ_WRITE )
__IO_REG8_BIT(  TP5CCIC0,        0xFFFFF14C,  __READ_WRITE )
__IO_REG8_BIT(  TP5CCIC1,        0xFFFFF14E,  __READ_WRITE )
__IO_REG8_BIT(  TM0EQIC0,        0xFFFFF150,  __READ_WRITE )
__IO_REG8_BIT(  CB0RIC,          0xFFFFF152,  __READ_WRITE )
__IO_REG8_BIT(  IICIC1,          0xFFFFF152,  __READ_WRITE )
__IO_REG8_BIT(  CB0TIC,          0xFFFFF154,  __READ_WRITE )
__IO_REG8_BIT(  CB1RIC,          0xFFFFF156,  __READ_WRITE )
__IO_REG8_BIT(  CB1TIC,          0xFFFFF158,  __READ_WRITE )
__IO_REG8_BIT(  CB2RIC,          0xFFFFF15A,  __READ_WRITE )
__IO_REG8_BIT(  CB2TIC,          0xFFFFF15C,  __READ_WRITE )
__IO_REG8_BIT(  CB3RIC,          0xFFFFF15E,  __READ_WRITE )
__IO_REG8_BIT(  CB3TIC,          0xFFFFF160,  __READ_WRITE )
__IO_REG8_BIT(  CB4RIC,          0xFFFFF162,  __READ_WRITE )
__IO_REG8_BIT(  UA0RIC,          0xFFFFF162,  __READ_WRITE )
__IO_REG8_BIT(  CB4TIC,          0xFFFFF164,  __READ_WRITE )
__IO_REG8_BIT(  UA0TIC,          0xFFFFF164,  __READ_WRITE )
__IO_REG8_BIT(  IICIC2,          0xFFFFF166,  __READ_WRITE )
__IO_REG8_BIT(  UA1RIC,          0xFFFFF166,  __READ_WRITE )
__IO_REG8_BIT(  UA1TIC,          0xFFFFF168,  __READ_WRITE )
__IO_REG8_BIT(  IICIC0,          0xFFFFF16A,  __READ_WRITE )
__IO_REG8_BIT(  UA2RIC,          0xFFFFF16A,  __READ_WRITE )
__IO_REG8_BIT(  UA2TIC,          0xFFFFF16C,  __READ_WRITE )
__IO_REG8_BIT(  ADIC,            0xFFFFF16E,  __READ_WRITE )
__IO_REG8_BIT(  DMAIC0,          0xFFFFF170,  __READ_WRITE )
__IO_REG8_BIT(  DMAIC1,          0xFFFFF172,  __READ_WRITE )
__IO_REG8_BIT(  DMAIC2,          0xFFFFF174,  __READ_WRITE )
__IO_REG8_BIT(  DMAIC3,          0xFFFFF176,  __READ_WRITE )
__IO_REG8_BIT(  KRIC,            0xFFFFF178,  __READ_WRITE )
__IO_REG8_BIT(  WTIIC,           0xFFFFF17A,  __READ_WRITE )
__IO_REG8_BIT(  WTIC,            0xFFFFF17C,  __READ_WRITE )
__IO_REG8_BIT(  ERRIC,           0xFFFFF17E,  __READ_WRITE )
__IO_REG8_BIT(  ERRIC0,          0xFFFFF17E,  __READ_WRITE )
__IO_REG8_BIT(  STAIC,           0xFFFFF180,  __READ_WRITE )
__IO_REG8_BIT(  WUPIC0,          0xFFFFF180,  __READ_WRITE )
__IO_REG8_BIT(  IEIC1,           0xFFFFF182,  __READ_WRITE )
__IO_REG8_BIT(  RECIC0,          0xFFFFF182,  __READ_WRITE )
__IO_REG8_BIT(  IEIC2,           0xFFFFF184,  __READ_WRITE )
__IO_REG8_BIT(  TRXIC0,          0xFFFFF184,  __READ_WRITE )
__IO_REG8_BIT(  ERRIC1,          0xFFFFF186,  __READ_WRITE )
__IO_REG8_BIT(  WUPIC1,          0xFFFFF188,  __READ_WRITE )
__IO_REG8_BIT(  RECIC1,          0xFFFFF18A,  __READ_WRITE )
__IO_REG8_BIT(  TRXIC1,          0xFFFFF18C,  __READ_WRITE )
__IO_REG8_BIT(  PIC8,            0xFFFFF18E,  __READ_WRITE )
__IO_REG8_BIT(  TP6OVIC,         0xFFFFF190,  __READ_WRITE )
__IO_REG8_BIT(  TP6CCIC0,        0xFFFFF192,  __READ_WRITE )
__IO_REG8_BIT(  TP6CCIC1,        0xFFFFF194,  __READ_WRITE )
__IO_REG8_BIT(  TP7OVIC,         0xFFFFF196,  __READ_WRITE )
__IO_REG8_BIT(  TP7CCIC0,        0xFFFFF198,  __READ_WRITE )
__IO_REG8_BIT(  TP7CCIC1,        0xFFFFF19A,  __READ_WRITE )
__IO_REG8_BIT(  TP8OVIC,         0xFFFFF19C,  __READ_WRITE )
__IO_REG8_BIT(  TP8CCIC0,        0xFFFFF19E,  __READ_WRITE )
__IO_REG8_BIT(  TP8CCIC1,        0xFFFFF1A0,  __READ_WRITE )
__IO_REG8_BIT(  CB5RIC,          0xFFFFF1A2,  __READ_WRITE )
__IO_REG8_BIT(  CB5TIC,          0xFFFFF1A4,  __READ_WRITE )
__IO_REG8_BIT(  UA3RIC,          0xFFFFF1A6,  __READ_WRITE )
__IO_REG8_BIT(  UA3TIC,          0xFFFFF1A8,  __READ_WRITE )

__IO_REG8_BIT(  ISPR,            0xFFFFF1FA,  __READ       )
__IO_REG8(      PRCMD,           0xFFFFF1FC,  __WRITE      )
__IO_REG8_BIT(  PSC,             0xFFFFF1FE,  __READ_WRITE )
__IO_REG8_BIT(  ADA0M0,          0xFFFFF200,  __READ_WRITE )
__IO_REG8_BIT(  ADA0M1,          0xFFFFF201,  __READ_WRITE )
__IO_REG8_BIT(  ADA0S,           0xFFFFF202,  __READ_WRITE )
__IO_REG8_BIT(  ADA0M2,          0xFFFFF203,  __READ_WRITE )
__IO_REG8_BIT(  ADA0PFM,         0xFFFFF204,  __READ_WRITE )
__IO_REG8_BIT(  ADA0PFT,         0xFFFFF205,  __READ_WRITE )

__IO_REG16(     ADA0CR0,         0xFFFFF210,  __READ       )
__IO_REG8(      ADA0CR0H,        0xFFFFF211,  __READ       )
__IO_REG16(     ADA0CR1,         0xFFFFF212,  __READ       )
__IO_REG8(      ADA0CR1H,        0xFFFFF213,  __READ       )
__IO_REG16(     ADA0CR2,         0xFFFFF214,  __READ       )
__IO_REG8(      ADA0CR2H,        0xFFFFF215,  __READ       )
__IO_REG16(     ADA0CR3,         0xFFFFF216,  __READ       )
__IO_REG8(      ADA0CR3H,        0xFFFFF217,  __READ       )
__IO_REG16(     ADA0CR4,         0xFFFFF218,  __READ       )
__IO_REG8(      ADA0CR4H,        0xFFFFF219,  __READ       )
__IO_REG16(     ADA0CR5,         0xFFFFF21A,  __READ       )
__IO_REG8(      ADA0CR5H,        0xFFFFF21B,  __READ       )
__IO_REG16(     ADA0CR6,         0xFFFFF21C,  __READ       )
__IO_REG8(      ADA0CR6H,        0xFFFFF21D,  __READ       )
__IO_REG16(     ADA0CR7,         0xFFFFF21E,  __READ       )
__IO_REG8(      ADA0CR7H,        0xFFFFF21F,  __READ       )
__IO_REG16(     ADA0CR8,         0xFFFFF220,  __READ       )
__IO_REG8(      ADA0CR8H,        0xFFFFF221,  __READ       )
__IO_REG16(     ADA0CR9,         0xFFFFF222,  __READ       )
__IO_REG8(      ADA0CR9H,        0xFFFFF223,  __READ       )
__IO_REG16(     ADA0CR10,        0xFFFFF224,  __READ       )
__IO_REG8(      ADA0CR10H,       0xFFFFF225,  __READ       )
__IO_REG16(     ADA0CR11,        0xFFFFF226,  __READ       )
__IO_REG8(      ADA0CR11H,       0xFFFFF227,  __READ       )
__IO_REG16(     ADA0CR12,        0xFFFFF228,  __READ       )
__IO_REG8(      ADA0CR12H,       0xFFFFF229,  __READ       )
__IO_REG16(     ADA0CR13,        0xFFFFF22A,  __READ       )
__IO_REG8(      ADA0CR13H,       0xFFFFF22B,  __READ       )
__IO_REG16(     ADA0CR14,        0xFFFFF22C,  __READ       )
__IO_REG8(      ADA0CR14H,       0xFFFFF22D,  __READ       )
__IO_REG16(     ADA0CR15,        0xFFFFF22E,  __READ       )
__IO_REG8(      ADA0CR15H,       0xFFFFF22F,  __READ       )

__IO_REG8(      DA0CS0,          0xFFFFF280,  __READ_WRITE )
__IO_REG8(      DA0CS1,          0xFFFFF281,  __READ_WRITE )
__IO_REG8_BIT(  DA0M,            0xFFFFF282,  __READ_WRITE )

__IO_REG8_BIT(  KRM,             0xFFFFF300,  __READ_WRITE )

__IO_REG8_BIT(  SELCNT0,         0xFFFFF308,  __READ_WRITE )

__IO_REG8(      CRCIN,           0xFFFFF310,  __READ_WRITE )
__IO_REG16(     CRCD,            0xFFFFF312,  __READ_WRITE )

__IO_REG8(      NFC,             0xFFFFF318,  __READ_WRITE )

__IO_REG8_BIT(  PRSM1,           0xFFFFF320,  __READ_WRITE )
__IO_REG8(      PRSCM1,          0xFFFFF321,  __READ_WRITE )

__IO_REG8_BIT(  PRSM2,           0xFFFFF324,  __READ_WRITE )
__IO_REG8(      PRSCM2,          0xFFFFF325,  __READ_WRITE )

__IO_REG8_BIT(  PRSM3,           0xFFFFF328,  __READ_WRITE )
__IO_REG8(      PRSCM3,          0xFFFFF329,  __READ_WRITE )

__IO_REG8(      OCKS0,           0xFFFFF340,  __READ_WRITE )

__IO_REG8(      OCKS1,           0xFFFFF344,  __READ_WRITE )

__IO_REG8(      OCKS2,           0xFFFFF348,  __READ_WRITE )

__IO_REG8_BIT(  BCR,             0xFFFFF360,  __READ_WRITE )
__IO_REG8_BIT(  PSR,             0xFFFFF361,  __READ_WRITE )
__IO_REG8_BIT(  SSR,             0xFFFFF362,  __READ       )
__IO_REG8_BIT(  USR,             0xFFFFF363,  __READ       )
__IO_REG8_BIT(  ISR,             0xFFFFF364,  __READ_WRITE )
__IO_REG8_BIT(  ESR,             0xFFFFF365,  __READ_WRITE )
__IO_REG16(     UAR,             0xFFFFF366,  __READ_WRITE )
__IO_REG16(     SAR,             0xFFFFF368,  __READ_WRITE )
__IO_REG16(     PAR,             0xFFFFF36A,  __READ       )
__IO_REG16(     RSA,             0xFFFFF36C,  __READ       )
__IO_REG8(      CDR,             0xFFFFF36E,  __READ_WRITE )
__IO_REG8(      DLR,             0xFFFFF36F,  __READ_WRITE )
__IO_REG8(      DR,              0xFFFFF370,  __READ_WRITE )
__IO_REG8(      FSR,             0xFFFFF371,  __READ       )
__IO_REG8(      SCR,             0xFFFFF372,  __READ       )
__IO_REG8(      CCR,             0xFFFFF373,  __READ       )

__IO_REG8_BIT(  P0,              0xFFFFF400,  __READ_WRITE )
__IO_REG8_BIT(  P1,              0xFFFFF402,  __READ_WRITE )

__IO_REG16(     P3,              0xFFFFF406,  __READ_WRITE )
__IO_REG8_BIT(  P3L,             0xFFFFF406,  __READ_WRITE )
__IO_REG8_BIT(  P3H,             0xFFFFF407,  __READ_WRITE )
__IO_REG8_BIT(  P4,              0xFFFFF408,  __READ_WRITE )
__IO_REG8_BIT(  P5,              0xFFFFF40A,  __READ_WRITE )
__IO_REG16(     P6,              0xFFFFF40C,  __READ_WRITE )
__IO_REG8_BIT(  P6L,             0xFFFFF40C,  __READ_WRITE )
__IO_REG8_BIT(  P6H,             0xFFFFF40D,  __READ_WRITE )
__IO_REG8_BIT(  P7L,             0xFFFFF40E,  __READ_WRITE )
__IO_REG8_BIT(  P7H,             0xFFFFF40F,  __READ_WRITE )
__IO_REG8_BIT(  P8,              0xFFFFF410,  __READ_WRITE )
__IO_REG16(     P9,              0xFFFFF412,  __READ_WRITE )
__IO_REG8_BIT(  P9L,             0xFFFFF412,  __READ_WRITE )
__IO_REG8_BIT(  P9H,             0xFFFFF413,  __READ_WRITE )

__IO_REG8_BIT(  PM0,             0xFFFFF420,  __READ_WRITE )
__IO_REG8_BIT(  PM1,             0xFFFFF422,  __READ_WRITE )

__IO_REG16(     PM3,             0xFFFFF426,  __READ_WRITE )
__IO_REG8_BIT(  PM3L,            0xFFFFF426,  __READ_WRITE )
__IO_REG8_BIT(  PM3H,            0xFFFFF427,  __READ_WRITE )
__IO_REG8_BIT(  PM4,             0xFFFFF428,  __READ_WRITE )
__IO_REG8_BIT(  PM5,             0xFFFFF42A,  __READ_WRITE )
__IO_REG16(     PM6,             0xFFFFF42C,  __READ_WRITE )
__IO_REG8_BIT(  PM6L,            0xFFFFF42C,  __READ_WRITE )
__IO_REG8_BIT(  PM6H,            0xFFFFF42D,  __READ_WRITE )
__IO_REG8_BIT(  PM7L,            0xFFFFF42E,  __READ_WRITE )
__IO_REG8_BIT(  PM7H,            0xFFFFF42F,  __READ_WRITE )
__IO_REG8_BIT(  PM8,             0xFFFFF430,  __READ_WRITE )
__IO_REG16(     PM9,             0xFFFFF432,  __READ_WRITE )
__IO_REG8_BIT(  PM9L,            0xFFFFF432,  __READ_WRITE )
__IO_REG8_BIT(  PM9H,            0xFFFFF433,  __READ_WRITE )

__IO_REG8_BIT(  PMC0,            0xFFFFF440,  __READ_WRITE )

__IO_REG16(     PMC3,            0xFFFFF446,  __READ_WRITE )
__IO_REG8_BIT(  PMC3L,           0xFFFFF446,  __READ_WRITE )
__IO_REG8_BIT(  PMC3H,           0xFFFFF447,  __READ_WRITE )
__IO_REG8_BIT(  PMC4,            0xFFFFF448,  __READ_WRITE )
__IO_REG8_BIT(  PMC5,            0xFFFFF44A,  __READ_WRITE )
__IO_REG16(     PMC6,            0xFFFFF44C,  __READ_WRITE )
__IO_REG8_BIT(  PMC6L,           0xFFFFF44C,  __READ_WRITE )
__IO_REG8_BIT(  PMC6H,           0xFFFFF44D,  __READ_WRITE )

__IO_REG8_BIT(  PMC8,            0xFFFFF450,  __READ_WRITE )
__IO_REG16(     PMC9,            0xFFFFF452,  __READ_WRITE )
__IO_REG8_BIT(  PMC9L,           0xFFFFF452,  __READ_WRITE )
__IO_REG8_BIT(  PMC9H,           0xFFFFF453,  __READ_WRITE )

__IO_REG8_BIT(  PFC0,            0xFFFFF460,  __READ_WRITE )

__IO_REG16(     PFC3,            0xFFFFF466,  __READ_WRITE )
__IO_REG8_BIT(  PFC3L,           0xFFFFF466,  __READ_WRITE )
__IO_REG8_BIT(  PFC3H,           0xFFFFF467,  __READ_WRITE )
__IO_REG8_BIT(  PFC4,            0xFFFFF468,  __READ_WRITE )
__IO_REG8_BIT(  PFC5,            0xFFFFF46A,  __READ_WRITE )

__IO_REG8_BIT(  PFC6H,           0xFFFFF46D,  __READ_WRITE )

__IO_REG16(     PFC9,            0xFFFFF472,  __READ_WRITE )
__IO_REG8_BIT(  PFC9L,           0xFFFFF472,  __READ_WRITE )
__IO_REG8_BIT(  PFC9H,           0xFFFFF473,  __READ_WRITE )

__IO_REG16(     DWC0,            0xFFFFF484,  __READ_WRITE )

__IO_REG16(     AWC,             0xFFFFF488,  __READ_WRITE )
__IO_REG16(     BCC,             0xFFFFF48A,  __READ_WRITE )

__IO_REG8_BIT(  TQ0CTL0,         0xFFFFF540,  __READ_WRITE )
__IO_REG8_BIT(  TQ0CTL1,         0xFFFFF541,  __READ_WRITE )
__IO_REG8_BIT(  TQ0IOC0,         0xFFFFF542,  __READ_WRITE )
__IO_REG8_BIT(  TQ0IOC1,         0xFFFFF543,  __READ_WRITE )
__IO_REG8_BIT(  TQ0IOC2,         0xFFFFF544,  __READ_WRITE )
__IO_REG8_BIT(  TQ0OPT0,         0xFFFFF545,  __READ_WRITE )
__IO_REG16(     TQ0CCR0,         0xFFFFF546,  __READ_WRITE )
__IO_REG16(     TQ0CCR1,         0xFFFFF548,  __READ_WRITE )
__IO_REG16(     TQ0CCR2,         0xFFFFF54A,  __READ_WRITE )
__IO_REG16(     TQ0CCR3,         0xFFFFF54C,  __READ_WRITE )
__IO_REG16(     TQ0CNT,          0xFFFFF54E,  __READ       )

__IO_REG8_BIT(  TP0CTL0,         0xFFFFF590,  __READ_WRITE )
__IO_REG8_BIT(  TP0CTL1,         0xFFFFF591,  __READ_WRITE )
__IO_REG8_BIT(  TP0IOC0,         0xFFFFF592,  __READ_WRITE )
__IO_REG8_BIT(  TP0IOC1,         0xFFFFF593,  __READ_WRITE )
__IO_REG8_BIT(  TP0IOC2,         0xFFFFF594,  __READ_WRITE )
__IO_REG8_BIT(  TP0OPT0,         0xFFFFF595,  __READ_WRITE )
__IO_REG16(     TP0CCR0,         0xFFFFF596,  __READ_WRITE )
__IO_REG16(     TP0CCR1,         0xFFFFF598,  __READ_WRITE )
__IO_REG16(     TP0CNT,          0xFFFFF59A,  __READ       )

__IO_REG8_BIT(  TP1CTL0,         0xFFFFF5A0,  __READ_WRITE )
__IO_REG8_BIT(  TP1CTL1,         0xFFFFF5A1,  __READ_WRITE )
__IO_REG8_BIT(  TP1IOC0,         0xFFFFF5A2,  __READ_WRITE )
__IO_REG8_BIT(  TP1IOC1,         0xFFFFF5A3,  __READ_WRITE )
__IO_REG8_BIT(  TP1IOC2,         0xFFFFF5A4,  __READ_WRITE )
__IO_REG8_BIT(  TP1OPT0,         0xFFFFF5A5,  __READ_WRITE )
__IO_REG16(     TP1CCR0,         0xFFFFF5A6,  __READ_WRITE )
__IO_REG16(     TP1CCR1,         0xFFFFF5A8,  __READ_WRITE )
__IO_REG16(     TP1CNT,          0xFFFFF5AA,  __READ       )

__IO_REG8_BIT(  TP2CTL0,         0xFFFFF5B0,  __READ_WRITE )
__IO_REG8_BIT(  TP2CTL1,         0xFFFFF5B1,  __READ_WRITE )
__IO_REG8_BIT(  TP2IOC0,         0xFFFFF5B2,  __READ_WRITE )
__IO_REG8_BIT(  TP2IOC1,         0xFFFFF5B3,  __READ_WRITE )
__IO_REG8_BIT(  TP2IOC2,         0xFFFFF5B4,  __READ_WRITE )
__IO_REG8_BIT(  TP2OPT0,         0xFFFFF5B5,  __READ_WRITE )
__IO_REG16(     TP2CCR0,         0xFFFFF5B6,  __READ_WRITE )
__IO_REG16(     TP2CCR1,         0xFFFFF5B8,  __READ_WRITE )
__IO_REG16(     TP2CNT,          0xFFFFF5BA,  __READ       )

__IO_REG8_BIT(  TP3CTL0,         0xFFFFF5C0,  __READ_WRITE )
__IO_REG8_BIT(  TP3CTL1,         0xFFFFF5C1,  __READ_WRITE )
__IO_REG8_BIT(  TP3IOC0,         0xFFFFF5C2,  __READ_WRITE )
__IO_REG8_BIT(  TP3IOC1,         0xFFFFF5C3,  __READ_WRITE )
__IO_REG8_BIT(  TP3IOC2,         0xFFFFF5C4,  __READ_WRITE )
__IO_REG8_BIT(  TP3OPT0,         0xFFFFF5C5,  __READ_WRITE )
__IO_REG16(     TP3CCR0,         0xFFFFF5C6,  __READ_WRITE )
__IO_REG16(     TP3CCR1,         0xFFFFF5C8,  __READ_WRITE )
__IO_REG16(     TP3CNT,          0xFFFFF5CA,  __READ       )

__IO_REG8_BIT(  TP4CTL0,         0xFFFFF5D0,  __READ_WRITE )
__IO_REG8_BIT(  TP4CTL1,         0xFFFFF5D1,  __READ_WRITE )
__IO_REG8_BIT(  TP4IOC0,         0xFFFFF5D2,  __READ_WRITE )
__IO_REG8_BIT(  TP4IOC1,         0xFFFFF5D3,  __READ_WRITE )
__IO_REG8_BIT(  TP4IOC2,         0xFFFFF5D4,  __READ_WRITE )
__IO_REG8_BIT(  TP4OPT0,         0xFFFFF5D5,  __READ_WRITE )
__IO_REG16(     TP4CCR0,         0xFFFFF5D6,  __READ_WRITE )
__IO_REG16(     TP4CCR1,         0xFFFFF5D8,  __READ_WRITE )
__IO_REG16(     TP4CNT,          0xFFFFF5DA,  __READ       )

__IO_REG8_BIT(  TP5CTL0,         0xFFFFF5E0,  __READ_WRITE )
__IO_REG8_BIT(  TP5CTL1,         0xFFFFF5E1,  __READ_WRITE )
__IO_REG8_BIT(  TP5IOC0,         0xFFFFF5E2,  __READ_WRITE )
__IO_REG8_BIT(  TP5IOC1,         0xFFFFF5E3,  __READ_WRITE )
__IO_REG8_BIT(  TP5IOC2,         0xFFFFF5E4,  __READ_WRITE )
__IO_REG8_BIT(  TP5OPT0,         0xFFFFF5E5,  __READ_WRITE )
__IO_REG16(     TP5CCR0,         0xFFFFF5E6,  __READ_WRITE )
__IO_REG16(     TP5CCR1,         0xFFFFF5E8,  __READ_WRITE )
__IO_REG16(     TP5CNT,          0xFFFFF5EA,  __READ       )

__IO_REG8_BIT(  TP6CTL0,         0xFFFFF5F0,  __READ_WRITE )
__IO_REG8_BIT(  TP6CTL1,         0xFFFFF5F1,  __READ_WRITE )
__IO_REG8_BIT(  TP6IOC0,         0xFFFFF5F2,  __READ_WRITE )
__IO_REG8_BIT(  TP6IOC1,         0xFFFFF5F3,  __READ_WRITE )
__IO_REG8_BIT(  TP6IOC2,         0xFFFFF5F4,  __READ_WRITE )
__IO_REG8_BIT(  TP6OPT0,         0xFFFFF5F5,  __READ_WRITE )
__IO_REG16(     TP6CCR0,         0xFFFFF5F6,  __READ_WRITE )
__IO_REG16(     TP6CCR1,         0xFFFFF5F8,  __READ_WRITE )
__IO_REG16(     TP6CNT,          0xFFFFF5FA,  __READ       )

__IO_REG8_BIT(  TP7CTL0,         0xFFFFF600,  __READ_WRITE )
__IO_REG8_BIT(  TP7CTL1,         0xFFFFF601,  __READ_WRITE )
__IO_REG8_BIT(  TP7IOC0,         0xFFFFF602,  __READ_WRITE )
__IO_REG8_BIT(  TP7IOC1,         0xFFFFF603,  __READ_WRITE )
__IO_REG8_BIT(  TP7IOC2,         0xFFFFF604,  __READ_WRITE )
__IO_REG8_BIT(  TP7OPT0,         0xFFFFF605,  __READ_WRITE )
__IO_REG16(     TP7CCR0,         0xFFFFF606,  __READ_WRITE )
__IO_REG16(     TP7CCR1,         0xFFFFF608,  __READ_WRITE )
__IO_REG16(     TP7CNT,          0xFFFFF60A,  __READ       )

__IO_REG8_BIT(  TP8CTL0,         0xFFFFF610,  __READ_WRITE )
__IO_REG8_BIT(  TP8CTL1,         0xFFFFF611,  __READ_WRITE )
__IO_REG8_BIT(  TP8IOC0,         0xFFFFF612,  __READ_WRITE )
__IO_REG8_BIT(  TP8IOC1,         0xFFFFF613,  __READ_WRITE )
__IO_REG8_BIT(  TP8IOC2,         0xFFFFF614,  __READ_WRITE )
__IO_REG8_BIT(  TP8OPT0,         0xFFFFF615,  __READ_WRITE )
__IO_REG16(     TP8CCR0,         0xFFFFF616,  __READ_WRITE )
__IO_REG16(     TP8CCR1,         0xFFFFF618,  __READ_WRITE )
__IO_REG16(     TP8CNT,          0xFFFFF61A,  __READ       )

__IO_REG8_BIT(  WTM,             0xFFFFF680,  __READ_WRITE )

__IO_REG8_BIT(  TM0CTL0,         0xFFFFF690,  __READ_WRITE )

__IO_REG16(     TM0CMP0,         0xFFFFF694,  __READ_WRITE )

__IO_REG8(      OSTS,            0xFFFFF6C0,  __READ_WRITE )
__IO_REG8(      PLLS,            0xFFFFF6C1,  __READ_WRITE )

__IO_REG8(      WDTM2,           0xFFFFF6D0,  __READ_WRITE )
__IO_REG8(      WDTE,            0xFFFFF6D1,  __READ_WRITE )

__IO_REG8_BIT(  RTBL0,           0xFFFFF6E0,  __READ_WRITE )
__IO_REG8_BIT(  RTBH0,           0xFFFFF6E2,  __READ_WRITE )
__IO_REG8_BIT(  RTPM0,           0xFFFFF6E4,  __READ_WRITE )
__IO_REG8_BIT(  RTPC0,           0xFFFFF6E5,  __READ_WRITE )

__IO_REG8_BIT(  RTBL1,           0xFFFFF6F0,  __READ_WRITE )
__IO_REG8_BIT(  RTBH1,           0xFFFFF6F2,  __READ_WRITE )
__IO_REG8_BIT(  RTPM1,           0xFFFFF6F4,  __READ_WRITE )
__IO_REG8_BIT(  RTPC1,           0xFFFFF6F5,  __READ_WRITE )

__IO_REG8_BIT(  PFCE3L,          0xFFFFF706,  __READ_WRITE )

__IO_REG8_BIT(  PFCE5,           0xFFFFF70A,  __READ_WRITE )

__IO_REG16(     PFCE9,           0xFFFFF712,  __READ_WRITE )
__IO_REG8_BIT(  PFCE9L,          0xFFFFF712,  __READ_WRITE )
__IO_REG8_BIT(  PFCE9H,          0xFFFFF713,  __READ_WRITE )

__IO_REG8_BIT(  SYS,             0xFFFFF802,  __READ_WRITE )

__IO_REG8_BIT(  RCM,             0xFFFFF80C,  __READ_WRITE )

__IO_REG8_BIT(  DTFR0,           0xFFFFF810,  __READ_WRITE )
__IO_REG8_BIT(  DTFR1,           0xFFFFF812,  __READ_WRITE )
__IO_REG8_BIT(  DTFR2,           0xFFFFF814,  __READ_WRITE )
__IO_REG8_BIT(  DTFR3,           0xFFFFF816,  __READ_WRITE )

__IO_REG8_BIT(  PSMR,            0xFFFFF820,  __READ_WRITE )
__IO_REG8_BIT(  CKC,             0xFFFFF822,  __READ_WRITE )
__IO_REG8_BIT(  LOCKR,           0xFFFFF824,  __READ       )

__IO_REG8_BIT(  PCC,             0xFFFFF828,  __READ_WRITE )

__IO_REG8_BIT(  PLLCTL,          0xFFFFF82C,  __READ_WRITE )
__IO_REG8_BIT(  CCLS,            0xFFFFF82E,  __READ       )

__IO_REG32(     CORAD0,          0xFFFFF840,  __READ_WRITE )
__IO_REG16(     CORAD0L,         0xFFFFF840,  __READ_WRITE )
__IO_REG16(     CORAD0H,         0xFFFFF842,  __READ_WRITE )
__IO_REG32(     CORAD1,          0xFFFFF844,  __READ_WRITE )
__IO_REG16(     CORAD1L,         0xFFFFF844,  __READ_WRITE )
__IO_REG16(     CORAD1H,         0xFFFFF846,  __READ_WRITE )
__IO_REG32(     CORAD2,          0xFFFFF848,  __READ_WRITE )
__IO_REG16(     CORAD2L,         0xFFFFF848,  __READ_WRITE )
__IO_REG16(     CORAD2H,         0xFFFFF84A,  __READ_WRITE )
__IO_REG32(     CORAD3,          0xFFFFF84C,  __READ_WRITE )
__IO_REG16(     CORAD3L,         0xFFFFF84C,  __READ_WRITE )
__IO_REG16(     CORAD3H,         0xFFFFF84E,  __READ_WRITE )

__IO_REG8_BIT(  CLM,             0xFFFFF870,  __READ_WRITE )

__IO_REG8_BIT(  CORCN,           0xFFFFF880,  __READ_WRITE )

__IO_REG8_BIT(  RESF,            0xFFFFF888,  __READ_WRITE )

__IO_REG8_BIT(  LVIM,            0xFFFFF890,  __READ_WRITE )
__IO_REG8(      LVIS,            0xFFFFF891,  __READ_WRITE )
__IO_REG8_BIT(  RAMS,            0xFFFFF892,  __READ_WRITE )

__IO_REG8_BIT(  PRSM0,           0xFFFFF8B0,  __READ_WRITE )
__IO_REG8(      PRSCM0,          0xFFFFF8B1,  __READ_WRITE )

__IO_REG8_BIT(  OCDM,            0xFFFFF9FC,  __READ_WRITE )
__IO_REG8_BIT(  PEMU1,           0xFFFFF9FE,  __READ_WRITE )
__IO_REG8_BIT(  UA0CTL0,         0xFFFFFA00,  __READ_WRITE )
__IO_REG8(      UA0CTL1,         0xFFFFFA01,  __READ_WRITE )
__IO_REG8(      UA0CTL2,         0xFFFFFA02,  __READ_WRITE )
__IO_REG8_BIT(  UA0OPT0,         0xFFFFFA03,  __READ_WRITE )
__IO_REG8_BIT(  UA0STR,          0xFFFFFA04,  __READ_WRITE )
__IO_REG8(      UA0RX,           0xFFFFFA06,  __READ       )
__IO_REG8(      UA0TX,           0xFFFFFA07,  __READ_WRITE )

__IO_REG8_BIT(  UA1CTL0,         0xFFFFFA10,  __READ_WRITE )
__IO_REG8(      UA1CTL1,         0xFFFFFA11,  __READ_WRITE )
__IO_REG8(      UA1CTL2,         0xFFFFFA12,  __READ_WRITE )
__IO_REG8_BIT(  UA1OPT0,         0xFFFFFA13,  __READ_WRITE )
__IO_REG8_BIT(  UA1STR,          0xFFFFFA14,  __READ_WRITE )
__IO_REG8(      UA1RX,           0xFFFFFA16,  __READ       )
__IO_REG8(      UA1TX,           0xFFFFFA17,  __READ_WRITE )

__IO_REG8_BIT(  UA2CTL0,         0xFFFFFA20,  __READ_WRITE )
__IO_REG8(      UA2CTL1,         0xFFFFFA21,  __READ_WRITE )
__IO_REG8(      UA2CTL2,         0xFFFFFA22,  __READ_WRITE )
__IO_REG8_BIT(  UA2OPT0,         0xFFFFFA23,  __READ_WRITE )
__IO_REG8_BIT(  UA2STR,          0xFFFFFA24,  __READ_WRITE )
__IO_REG8(      UA2RX,           0xFFFFFA26,  __READ       )
__IO_REG8(      UA2TX,           0xFFFFFA27,  __READ_WRITE )

__IO_REG8_BIT(  UA3CTL0,         0xFFFFFA30,  __READ_WRITE )
__IO_REG8(      UA3CTL1,         0xFFFFFA31,  __READ_WRITE )
__IO_REG8(      UA3CTL2,         0xFFFFFA32,  __READ_WRITE )
__IO_REG8_BIT(  UA3OPT0,         0xFFFFFA33,  __READ_WRITE )
__IO_REG8_BIT(  UA3STR,          0xFFFFFA34,  __READ_WRITE )
__IO_REG8(      UA3RX,           0xFFFFFA36,  __READ       )
__IO_REG8(      UA3TX,           0xFFFFFA37,  __READ_WRITE )

__IO_REG8_BIT(  INTF0,           0xFFFFFC00,  __READ_WRITE )

__IO_REG8_BIT(  INTF3,           0xFFFFFC06,  __READ_WRITE )

__IO_REG8_BIT(  INTF8,           0xFFFFFC10,  __READ_WRITE )

__IO_REG8_BIT(  INTF9H,          0xFFFFFC13,  __READ_WRITE )

__IO_REG8_BIT(  INTR0,           0xFFFFFC20,  __READ_WRITE )

__IO_REG8_BIT(  INTR3,           0xFFFFFC26,  __READ_WRITE )

__IO_REG8_BIT(  INTR8,           0xFFFFFC30,  __READ_WRITE )

__IO_REG8_BIT(  INTR9H,          0xFFFFFC33,  __READ_WRITE )

__IO_REG8_BIT(  PF0,             0xFFFFFC60,  __READ_WRITE )

__IO_REG16(     PF3,             0xFFFFFC66,  __READ_WRITE )
__IO_REG8_BIT(  PF3L,            0xFFFFFC66,  __READ_WRITE )
__IO_REG8_BIT(  PF3H,            0xFFFFFC67,  __READ_WRITE )
__IO_REG8_BIT(  PF4,             0xFFFFFC68,  __READ_WRITE )
__IO_REG8_BIT(  PF5,             0xFFFFFC6A,  __READ_WRITE )
__IO_REG16(     PF6,             0xFFFFFC6C,  __READ_WRITE )
__IO_REG8_BIT(  PF6L,            0xFFFFFC6C,  __READ_WRITE )
__IO_REG8_BIT(  PF6H,            0xFFFFFC6D,  __READ_WRITE )

__IO_REG8_BIT(  PF8,             0xFFFFFC70,  __READ_WRITE )
__IO_REG16(     PF9,             0xFFFFFC72,  __READ_WRITE )
__IO_REG8_BIT(  PF9L,            0xFFFFFC72,  __READ_WRITE )
__IO_REG8_BIT(  PF9H,            0xFFFFFC73,  __READ_WRITE )

__IO_REG16(     PRDSELL,         0xFFFFFCC8,  __READ       )
__IO_REG16(     PRDSELH,         0xFFFFFCCA,  __READ       )

__IO_REG8_BIT(  CB0CTL0,         0xFFFFFD00,  __READ_WRITE )
__IO_REG8_BIT(  CB0CTL1,         0xFFFFFD01,  __READ_WRITE )
__IO_REG8(      CB0CTL2,         0xFFFFFD02,  __READ_WRITE )
__IO_REG8_BIT(  CB0STR,          0xFFFFFD03,  __READ_WRITE )
__IO_REG16(     CB0RX,           0xFFFFFD04,  __READ       )
__IO_REG8(      CB0RXL,          0xFFFFFD04,  __READ       )
__IO_REG16(     CB0TX,           0xFFFFFD06,  __READ_WRITE )
__IO_REG8(      CB0TXL,          0xFFFFFD06,  __READ_WRITE )

__IO_REG8_BIT(  CB1CTL0,         0xFFFFFD10,  __READ_WRITE )
__IO_REG8_BIT(  CB1CTL1,         0xFFFFFD11,  __READ_WRITE )
__IO_REG8(      CB1CTL2,         0xFFFFFD12,  __READ_WRITE )
__IO_REG8_BIT(  CB1STR,          0xFFFFFD13,  __READ_WRITE )
__IO_REG16(     CB1RX,           0xFFFFFD14,  __READ       )
__IO_REG8(      CB1RXL,          0xFFFFFD14,  __READ       )
__IO_REG16(     CB1TX,           0xFFFFFD16,  __READ_WRITE )
__IO_REG8(      CB1TXL,          0xFFFFFD16,  __READ_WRITE )

__IO_REG8_BIT(  CB2CTL0,         0xFFFFFD20,  __READ_WRITE )
__IO_REG8_BIT(  CB2CTL1,         0xFFFFFD21,  __READ_WRITE )
__IO_REG8(      CB2CTL2,         0xFFFFFD22,  __READ_WRITE )
__IO_REG8_BIT(  CB2STR,          0xFFFFFD23,  __READ_WRITE )
__IO_REG16(     CB2RX,           0xFFFFFD24,  __READ       )
__IO_REG8(      CB2RXL,          0xFFFFFD24,  __READ       )
__IO_REG16(     CB2TX,           0xFFFFFD26,  __READ_WRITE )
__IO_REG8(      CB2TXL,          0xFFFFFD26,  __READ_WRITE )

__IO_REG8_BIT(  CB3CTL0,         0xFFFFFD30,  __READ_WRITE )
__IO_REG8_BIT(  CB3CTL1,         0xFFFFFD31,  __READ_WRITE )
__IO_REG8(      CB3CTL2,         0xFFFFFD32,  __READ_WRITE )
__IO_REG8_BIT(  CB3STR,          0xFFFFFD33,  __READ_WRITE )
__IO_REG16(     CB3RX,           0xFFFFFD34,  __READ       )
__IO_REG8(      CB3RXL,          0xFFFFFD34,  __READ       )
__IO_REG16(     CB3TX,           0xFFFFFD36,  __READ_WRITE )
__IO_REG8(      CB3TXL,          0xFFFFFD36,  __READ_WRITE )

__IO_REG8_BIT(  CB4CTL0,         0xFFFFFD40,  __READ_WRITE )
__IO_REG8_BIT(  CB4CTL1,         0xFFFFFD41,  __READ_WRITE )
__IO_REG8(      CB4CTL2,         0xFFFFFD42,  __READ_WRITE )
__IO_REG8_BIT(  CB4STR,          0xFFFFFD43,  __READ_WRITE )
__IO_REG16(     CB4RX,           0xFFFFFD44,  __READ       )
__IO_REG8(      CB4RXL,          0xFFFFFD44,  __READ       )
__IO_REG16(     CB4TX,           0xFFFFFD46,  __READ_WRITE )
__IO_REG8(      CB4TXL,          0xFFFFFD46,  __READ_WRITE )

__IO_REG8_BIT(  CB5CTL0,         0xFFFFFD50,  __READ_WRITE )
__IO_REG8_BIT(  CB5CTL1,         0xFFFFFD51,  __READ_WRITE )
__IO_REG8(      CB5CTL2,         0xFFFFFD52,  __READ_WRITE )
__IO_REG8_BIT(  CB5STR,          0xFFFFFD53,  __READ_WRITE )
__IO_REG16(     CB5RX,           0xFFFFFD54,  __READ       )
__IO_REG8(      CB5RXL,          0xFFFFFD54,  __READ       )
__IO_REG16(     CB5TX,           0xFFFFFD56,  __READ_WRITE )
__IO_REG8(      CB5TXL,          0xFFFFFD56,  __READ_WRITE )

__IO_REG8(      IIC0,            0xFFFFFD80,  __READ_WRITE )
__IO_REG8_BIT(  IICC0,           0xFFFFFD82,  __READ_WRITE )
__IO_REG8(      SVA0,            0xFFFFFD83,  __READ_WRITE )
__IO_REG8_BIT(  IICCL0,          0xFFFFFD84,  __READ_WRITE )
__IO_REG8_BIT(  IICX0,           0xFFFFFD85,  __READ_WRITE )
__IO_REG8_BIT(  IICS0,           0xFFFFFD86,  __READ       )

__IO_REG8_BIT(  IICF0,           0xFFFFFD8A,  __READ_WRITE )

__IO_REG8(      IIC1,            0xFFFFFD90,  __READ_WRITE )
__IO_REG8_BIT(  IICC1,           0xFFFFFD92,  __READ_WRITE )
__IO_REG8(      SVA1,            0xFFFFFD93,  __READ_WRITE )
__IO_REG8_BIT(  IICCL1,          0xFFFFFD94,  __READ_WRITE )
__IO_REG8_BIT(  IICX1,           0xFFFFFD95,  __READ_WRITE )
__IO_REG8_BIT(  IICS1,           0xFFFFFD96,  __READ       )

__IO_REG8_BIT(  IICF1,           0xFFFFFD9A,  __READ_WRITE )

__IO_REG8(      IIC2,            0xFFFFFDA0,  __READ_WRITE )
__IO_REG8_BIT(  IICC2,           0xFFFFFDA2,  __READ_WRITE )
__IO_REG8(      SVA2,            0xFFFFFDA3,  __READ_WRITE )
__IO_REG8_BIT(  IICCL2,          0xFFFFFDA4,  __READ_WRITE )
__IO_REG8_BIT(  IICX2,           0xFFFFFDA5,  __READ_WRITE )
__IO_REG8_BIT(  IICS2,           0xFFFFFDA6,  __READ       )

__IO_REG8_BIT(  IICF2,           0xFFFFFDAA,  __READ_WRITE )

__IO_REG8_BIT(  EXIMC,           0xFFFFFFBE,  __READ_WRITE )

/***********************************************
 *       Peripheral I/O bit declarations
 ***********************************************/

#ifdef __IAR_SYSTEMS_ICC__

#define E00               DCHC0_bit.no0
#define STG0              DCHC0_bit.no1
#define INIT0             DCHC0_bit.no2
#define TC0               DCHC0_bit.no7

#define E11               DCHC1_bit.no0
#define STG1              DCHC1_bit.no1
#define INIT1             DCHC1_bit.no2
#define TC1               DCHC1_bit.no7

#define E22               DCHC2_bit.no0
#define STG2              DCHC2_bit.no1
#define INIT2             DCHC2_bit.no2
#define TC2               DCHC2_bit.no7

#define E33               DCHC3_bit.no0
#define STG3              DCHC3_bit.no1
#define INIT3             DCHC3_bit.no2
#define TC3               DCHC3_bit.no7

#define LVIMK             LVIIC_bit.no6
#define LVIIF             LVIIC_bit.no7

#define PMK0              PIC0_bit.no6
#define PIF0              PIC0_bit.no7

#define PMK1              PIC1_bit.no6
#define PIF1              PIC1_bit.no7

#define PMK2              PIC2_bit.no6
#define PIF2              PIC2_bit.no7

#define PMK3              PIC3_bit.no6
#define PIF3              PIC3_bit.no7

#define PMK4              PIC4_bit.no6
#define PIF4              PIC4_bit.no7

#define PMK5              PIC5_bit.no6
#define PIF5              PIC5_bit.no7

#define PMK6              PIC6_bit.no6
#define PIF6              PIC6_bit.no7

#define PMK7              PIC7_bit.no6
#define PIF7              PIC7_bit.no7

#define TQ0OVMK           TQ0OVIC_bit.no6
#define TQ0OVIF           TQ0OVIC_bit.no7

#define TQ0CCMK0          TQ0CCIC0_bit.no6
#define TQ0CCIF0          TQ0CCIC0_bit.no7

#define TQ0CCMK1          TQ0CCIC1_bit.no6
#define TQ0CCIF1          TQ0CCIC1_bit.no7

#define TQ0CCMK2          TQ0CCIC2_bit.no6
#define TQ0CCIF2          TQ0CCIC2_bit.no7

#define TQ0CCMK3          TQ0CCIC3_bit.no6
#define TQ0CCIF3          TQ0CCIC3_bit.no7

#define TP0OVMK           TP0OVIC_bit.no6
#define TP0OVIF           TP0OVIC_bit.no7

#define TP0CCMK0          TP0CCIC0_bit.no6
#define TP0CCIF0          TP0CCIC0_bit.no7

#define TP0CCMK1          TP0CCIC1_bit.no6
#define TP0CCIF1          TP0CCIC1_bit.no7

#define TP1OVMK           TP1OVIC_bit.no6
#define TP1OVIF           TP1OVIC_bit.no7

#define TP1CCMK0          TP1CCIC0_bit.no6
#define TP1CCIF0          TP1CCIC0_bit.no7

#define TP1CCMK1          TP1CCIC1_bit.no6
#define TP1CCIF1          TP1CCIC1_bit.no7

#define TP2OVMK           TP2OVIC_bit.no6
#define TP2OVIF           TP2OVIC_bit.no7

#define TP2CCMK0          TP2CCIC0_bit.no6
#define TP2CCIF0          TP2CCIC0_bit.no7

#define TP2CCMK1          TP2CCIC1_bit.no6
#define TP2CCIF1          TP2CCIC1_bit.no7

#define TP3OVMK           TP3OVIC_bit.no6
#define TP3OVIF           TP3OVIC_bit.no7

#define TP3CCMK0          TP3CCIC0_bit.no6
#define TP3CCIF0          TP3CCIC0_bit.no7

#define TP3CCMK1          TP3CCIC1_bit.no6
#define TP3CCIF1          TP3CCIC1_bit.no7

#define TP4OVMK           TP4OVIC_bit.no6
#define TP4OVIF           TP4OVIC_bit.no7

#define TP4CCMK0          TP4CCIC0_bit.no6
#define TP4CCIF0          TP4CCIC0_bit.no7

#define TP4CCMK1          TP4CCIC1_bit.no6
#define TP4CCIF1          TP4CCIC1_bit.no7

#define TP5OVMK           TP5OVIC_bit.no6
#define TP5OVIF           TP5OVIC_bit.no7

#define TP5CCMK0          TP5CCIC0_bit.no6
#define TP5CCIF0          TP5CCIC0_bit.no7

#define TP5CCMK1          TP5CCIC1_bit.no6
#define TP5CCIF1          TP5CCIC1_bit.no7

#define TM0EQMK0          TM0EQIC0_bit.no6
#define TM0EQIF0          TM0EQIC0_bit.no7

#define CB0RMK            IICIC1_bit.no6
#define IICMK1            IICIC1_bit.no6
#define CB0RIF            IICIC1_bit.no7
#define IICIF1            IICIC1_bit.no7

#define CB0TMK            CB0TIC_bit.no6
#define CB0TIF            CB0TIC_bit.no7

#define CB1RMK            CB1RIC_bit.no6
#define CB1RIF            CB1RIC_bit.no7

#define CB1TMK            CB1TIC_bit.no6
#define CB1TIF            CB1TIC_bit.no7

#define CB2RMK            CB2RIC_bit.no6
#define CB2RIF            CB2RIC_bit.no7

#define CB2TMK            CB2TIC_bit.no6
#define CB2TIF            CB2TIC_bit.no7

#define CB3RMK            CB3RIC_bit.no6
#define CB3RIF            CB3RIC_bit.no7

#define CB3TMK            CB3TIC_bit.no6
#define CB3TIF            CB3TIC_bit.no7

#define CB4RMK            UA0RIC_bit.no6
#define UA0RMK            UA0RIC_bit.no6
#define CB4RIF            UA0RIC_bit.no7
#define UA0RIF            UA0RIC_bit.no7

#define CB4TMK            UA0TIC_bit.no6
#define UA0TMK            UA0TIC_bit.no6
#define CB4TIF            UA0TIC_bit.no7
#define UA0TIF            UA0TIC_bit.no7

#define IICMK2            UA1RIC_bit.no6
#define UA1RMK            UA1RIC_bit.no6
#define IICIF2            UA1RIC_bit.no7
#define UA1RIF            UA1RIC_bit.no7

#define UA1TMK            UA1TIC_bit.no6
#define UA1TIF            UA1TIC_bit.no7

#define IICMK0            UA2RIC_bit.no6
#define UA2RMK            UA2RIC_bit.no6
#define IICIF0            UA2RIC_bit.no7
#define UA2RIF            UA2RIC_bit.no7

#define UA2TMK            UA2TIC_bit.no6
#define UA2TIF            UA2TIC_bit.no7

#define ADMK              ADIC_bit.no6
#define ADIF              ADIC_bit.no7

#define DMAMK0            DMAIC0_bit.no6
#define DMAIF0            DMAIC0_bit.no7

#define DMAMK1            DMAIC1_bit.no6
#define DMAIF1            DMAIC1_bit.no7

#define DMAMK2            DMAIC2_bit.no6
#define DMAIF2            DMAIC2_bit.no7

#define DMAMK3            DMAIC3_bit.no6
#define DMAIF3            DMAIC3_bit.no7

#define KRMK              KRIC_bit.no6
#define KRIF              KRIC_bit.no7

#define WTIMK             WTIIC_bit.no6
#define WTIIF             WTIIC_bit.no7

#define WTMK              WTIC_bit.no6
#define WTIF              WTIC_bit.no7

#define ERRMK             ERRIC0_bit.no6
#define ERRMK0            ERRIC0_bit.no6
#define ERRIF             ERRIC0_bit.no7
#define ERRIF0            ERRIC0_bit.no7

#define STAMK             WUPIC0_bit.no6
#define WUPMK0            WUPIC0_bit.no6
#define STAIF             WUPIC0_bit.no7
#define WUPIF0            WUPIC0_bit.no7

#define IEMK1             RECIC0_bit.no6
#define RECMK0            RECIC0_bit.no6
#define IEIF1             RECIC0_bit.no7
#define RECIF0            RECIC0_bit.no7

#define IEMK2             TRXIC0_bit.no6
#define TRXMK0            TRXIC0_bit.no6
#define IEIF2             TRXIC0_bit.no7
#define TRXIF0            TRXIC0_bit.no7

#define ERRMK1            ERRIC1_bit.no6
#define ERRIF1            ERRIC1_bit.no7

#define WUPMK1            WUPIC1_bit.no6
#define WUPIF1            WUPIC1_bit.no7

#define RECMK1            RECIC1_bit.no6
#define RECIF1            RECIC1_bit.no7

#define TRXMK1            TRXIC1_bit.no6
#define TRXIF1            TRXIC1_bit.no7

#define PMK8              PIC8_bit.no6
#define PIF8              PIC8_bit.no7

#define TP6OVMK           TP6OVIC_bit.no6
#define TP6OVIF           TP6OVIC_bit.no7

#define TP6CCMK0          TP6CCIC0_bit.no6
#define TP6CCIF0          TP6CCIC0_bit.no7

#define TP6CCMK1          TP6CCIC1_bit.no6
#define TP6CCIF1          TP6CCIC1_bit.no7

#define TP7OVMK           TP7OVIC_bit.no6
#define TP7OVIF           TP7OVIC_bit.no7

#define TP7CCMK0          TP7CCIC0_bit.no6
#define TP7CCIF0          TP7CCIC0_bit.no7

#define TP7CCMK1          TP7CCIC1_bit.no6
#define TP7CCIF1          TP7CCIC1_bit.no7

#define TP8OVMK           TP8OVIC_bit.no6
#define TP8OVIF           TP8OVIC_bit.no7

#define TP8CCMK0          TP8CCIC0_bit.no6
#define TP8CCIF0          TP8CCIC0_bit.no7

#define TP8CCMK1          TP8CCIC1_bit.no6
#define TP8CCIF1          TP8CCIC1_bit.no7

#define CB5RMK            CB5RIC_bit.no6
#define CB5RIF            CB5RIC_bit.no7

#define CB5TMK            CB5TIC_bit.no6
#define CB5TIF            CB5TIC_bit.no7

#define UA3RMK            UA3RIC_bit.no6
#define UA3RIF            UA3RIC_bit.no7

#define UA3TMK            UA3TIC_bit.no6
#define UA3TIF            UA3TIC_bit.no7

#define ISPR0             ISPR_bit.no0
#define ISPR1             ISPR_bit.no1
#define ISPR2             ISPR_bit.no2
#define ISPR3             ISPR_bit.no3
#define ISPR4             ISPR_bit.no4
#define ISPR5             ISPR_bit.no5
#define ISPR6             ISPR_bit.no6
#define ISPR7             ISPR_bit.no7

#define STP               PSC_bit.no1
#define INTM              PSC_bit.no4
#define NMI0M             PSC_bit.no5
#define NMI1M             PSC_bit.no6

#define ADA0EF            ADA0M0_bit.no0
#define ADA0CE            ADA0M0_bit.no7

#define ADA0PFE           ADA0PFM_bit.no7

#define DA0CE0            DA0M_bit.no4
#define DA0CE1            DA0M_bit.no5

#define ISEL0             SELCNT0_bit.no0
#define ISEL1             SELCNT0_bit.no1
#define ISEL3             SELCNT0_bit.no3
#define ISEL4             SELCNT0_bit.no4
#define ISEL6             SELCNT0_bit.no6

#define BGCE1             PRSM1_bit.no4

#define BGCE2             PRSM2_bit.no4

#define BGCE3             PRSM3_bit.no4

#define ENSLVRX           BCR_bit.no3
#define ENSLVTX           BCR_bit.no4
#define ALLRQ             BCR_bit.no5
#define MSTRQ             BCR_bit.no6
#define ENIEBUS           BCR_bit.no7

#define IEMODE            PSR_bit.no6
#define ENCLK             PSR_bit.no7

#define STATTX            SSR_bit.no0
#define STATRX            SSR_bit.no1
#define STATLOCK          SSR_bit.no2
#define STATSLV           SSR_bit.no4

#define ACKF              USR_bit.no3
#define ALLTRNS           USR_bit.no4
#define ARBIT             USR_bit.no5
#define SLVRQ             USR_bit.no6

#define ENDFRAM           ISR_bit.no2
#define ENDTRNS           ISR_bit.no3
#define STATUSF           ISR_bit.no4
#define STARTF            ISR_bit.no5
#define IEERR             ISR_bit.no6

#define DEFLAG            ESR_bit.no0
#define WERR              ESR_bit.no2
#define OERR              ESR_bit.no3
#define UERR              ESR_bit.no4
#define NERR              ESR_bit.no5
#define PERR              ESR_bit.no6
#define TERR              ESR_bit.no7

#define TQ0CE             TQ0CTL0_bit.no7

#define TQ0EEE            TQ0CTL1_bit.no5
#define TQ0EST            TQ0CTL1_bit.no6

#define TQ0OE0            TQ0IOC0_bit.no0
#define TQ0OE1            TQ0IOC0_bit.no2
#define TQ0OE2            TQ0IOC0_bit.no4
#define TQ0OE3            TQ0IOC0_bit.no6

#define TQ0OVF            TQ0OPT0_bit.no0

#define TP0CE             TP0CTL0_bit.no7

#define TP0EEE            TP0CTL1_bit.no5
#define TP0EST            TP0CTL1_bit.no6

#define TP0OE0            TP0IOC0_bit.no0
#define TP0OE1            TP0IOC0_bit.no2

#define TP0OVF            TP0OPT0_bit.no0

#define TP1CE             TP1CTL0_bit.no7

#define TP1EEE            TP1CTL1_bit.no5
#define TP1EST            TP1CTL1_bit.no6

#define TP1OE0            TP1IOC0_bit.no0
#define TP1OE1            TP1IOC0_bit.no2

#define TP1OVF            TP1OPT0_bit.no0

#define TP2CE             TP2CTL0_bit.no7

#define TP2EEE            TP2CTL1_bit.no5
#define TP2EST            TP2CTL1_bit.no6

#define TP2OE0            TP2IOC0_bit.no0
#define TP2OE1            TP2IOC0_bit.no2

#define TP2OVF            TP2OPT0_bit.no0

#define TP3CE             TP3CTL0_bit.no7

#define TP3EEE            TP3CTL1_bit.no5
#define TP3EST            TP3CTL1_bit.no6

#define TP3OE0            TP3IOC0_bit.no0
#define TP3OE1            TP3IOC0_bit.no2

#define TP3OVF            TP3OPT0_bit.no0

#define TP4CE             TP4CTL0_bit.no7

#define TP4EEE            TP4CTL1_bit.no5
#define TP4EST            TP4CTL1_bit.no6

#define TP4OE0            TP4IOC0_bit.no0
#define TP4OE1            TP4IOC0_bit.no2

#define TP4OVF            TP4OPT0_bit.no0

#define TP5CE             TP5CTL0_bit.no7

#define TP5EEE            TP5CTL1_bit.no5
#define TP5EST            TP5CTL1_bit.no6

#define TP5OE0            TP5IOC0_bit.no0
#define TP5OE1            TP5IOC0_bit.no2

#define TP5OVF            TP5OPT0_bit.no0

#define TP6CE             TP6CTL0_bit.no7

#define TP6EEE            TP6CTL1_bit.no5
#define TP6EST            TP6CTL1_bit.no6

#define TP6OE0            TP6IOC0_bit.no0
#define TP6OE1            TP6IOC0_bit.no2

#define TP6OVF            TP6OPT0_bit.no0

#define TP7CE             TP7CTL0_bit.no7

#define TP7EEE            TP7CTL1_bit.no5
#define TP7EST            TP7CTL1_bit.no6

#define TP7OE0            TP7IOC0_bit.no0
#define TP7OE1            TP7IOC0_bit.no2

#define TP7OVF            TP7OPT0_bit.no0

#define TP8CE             TP8CTL0_bit.no7

#define TP8EEE            TP8CTL1_bit.no5
#define TP8EST            TP8CTL1_bit.no6

#define TP8OE0            TP8IOC0_bit.no0
#define TP8OE1            TP8IOC0_bit.no2

#define TP8OVF            TP8OPT0_bit.no0

#define WTM0              WTM_bit.no0
#define WTM1              WTM_bit.no1

#define TM0CE             TM0CTL0_bit.no7

#define RTPOE0            RTPC0_bit.no7

#define RTPOE1            RTPC1_bit.no7

#define PRERR             SYS_bit.no0

#define RSTOP             RCM_bit.no0

#define DF0               DTFR0_bit.no7

#define DF1               DTFR1_bit.no7

#define DF2               DTFR2_bit.no7

#define DF3               DTFR3_bit.no7

#define PSM0              PSMR_bit.no0
#define PSM1              PSMR_bit.no1

#define LOCK              LOCKR_bit.no0

#define CK3               PCC_bit.no3
#define CLS               PCC_bit.no4
#define MCK               PCC_bit.no6

#define PLLON             PLLCTL_bit.no0
#define SELPLL            PLLCTL_bit.no1

#define CLME              CLM_bit.no0

#define LVIF              LVIM_bit.no0
#define LVIMD             LVIM_bit.no1
#define LVION             LVIM_bit.no7

#define RAMF              RAMS_bit.no0

#define BGCE0             PRSM0_bit.no4

#define OCDM0             OCDM_bit.no0

#define UA0DIR            UA0CTL0_bit.no4
#define UA0RXE            UA0CTL0_bit.no5
#define UA0TXE            UA0CTL0_bit.no6
#define UA0PWR            UA0CTL0_bit.no7

#define UA0SRF            UA0OPT0_bit.no7

#define UA0OVE            UA0STR_bit.no0
#define UA0FE             UA0STR_bit.no1
#define UA0PE             UA0STR_bit.no2
#define UA0TSF            UA0STR_bit.no7

#define UA1DIR            UA1CTL0_bit.no4
#define UA1RXE            UA1CTL0_bit.no5
#define UA1TXE            UA1CTL0_bit.no6
#define UA1PWR            UA1CTL0_bit.no7

#define UA1SRF            UA1OPT0_bit.no7

#define UA1OVE            UA1STR_bit.no0
#define UA1FE             UA1STR_bit.no1
#define UA1PE             UA1STR_bit.no2
#define UA1TSF            UA1STR_bit.no7

#define UA2DIR            UA2CTL0_bit.no4
#define UA2RXE            UA2CTL0_bit.no5
#define UA2TXE            UA2CTL0_bit.no6
#define UA2PWR            UA2CTL0_bit.no7

#define UA2SRF            UA2OPT0_bit.no7

#define UA2OVE            UA2STR_bit.no0
#define UA2FE             UA2STR_bit.no1
#define UA2PE             UA2STR_bit.no2
#define UA2TSF            UA2STR_bit.no7

#define UA3DIR            UA3CTL0_bit.no4
#define UA3RXE            UA3CTL0_bit.no5
#define UA3TXE            UA3CTL0_bit.no6
#define UA3PWR            UA3CTL0_bit.no7

#define UA3SRF            UA3OPT0_bit.no7

#define UA3OVE            UA3STR_bit.no0
#define UA3FE             UA3STR_bit.no1
#define UA3PE             UA3STR_bit.no2
#define UA3TSF            UA3STR_bit.no7

#define CB0SCE            CB0CTL0_bit.no0
#define CB0DIR            CB0CTL0_bit.no4
#define CB0RXE            CB0CTL0_bit.no5
#define CB0TXE            CB0CTL0_bit.no6
#define CB0PWR            CB0CTL0_bit.no7

#define CB0OVE            CB0STR_bit.no0
#define CB0TSF            CB0STR_bit.no7

#define CB1SCE            CB1CTL0_bit.no0
#define CB1DIR            CB1CTL0_bit.no4
#define CB1RXE            CB1CTL0_bit.no5
#define CB1TXE            CB1CTL0_bit.no6
#define CB1PWR            CB1CTL0_bit.no7

#define CB1OVE            CB1STR_bit.no0
#define CB1TSF            CB1STR_bit.no7

#define CB2SCE            CB2CTL0_bit.no0
#define CB2DIR            CB2CTL0_bit.no4
#define CB2RXE            CB2CTL0_bit.no5
#define CB2TXE            CB2CTL0_bit.no6
#define CB2PWR            CB2CTL0_bit.no7

#define CB2OVE            CB2STR_bit.no0
#define CB2TSF            CB2STR_bit.no7

#define CB3SCE            CB3CTL0_bit.no0
#define CB3DIR            CB3CTL0_bit.no4
#define CB3RXE            CB3CTL0_bit.no5
#define CB3TXE            CB3CTL0_bit.no6
#define CB3PWR            CB3CTL0_bit.no7

#define CB3OVE            CB3STR_bit.no0
#define CB3TSF            CB3STR_bit.no7

#define CB4SCE            CB4CTL0_bit.no0
#define CB4DIR            CB4CTL0_bit.no4
#define CB4RXE            CB4CTL0_bit.no5
#define CB4TXE            CB4CTL0_bit.no6
#define CB4PWR            CB4CTL0_bit.no7

#define CB4OVE            CB4STR_bit.no0
#define CB4TSF            CB4STR_bit.no7

#define CB5SCE            CB5CTL0_bit.no0
#define CB5DIR            CB5CTL0_bit.no4
#define CB5RXE            CB5CTL0_bit.no5
#define CB5TXE            CB5CTL0_bit.no6
#define CB5PWR            CB5CTL0_bit.no7

#define CB5OVE            CB5STR_bit.no0
#define CB5TSF            CB5STR_bit.no7

#define SPT0              IICC0_bit.no0
#define STT0              IICC0_bit.no1
#define ACKE0             IICC0_bit.no2
#define WTIM0             IICC0_bit.no3
#define SPIE0             IICC0_bit.no4
#define WREL0             IICC0_bit.no5
#define LREL0             IICC0_bit.no6
#define IICE0             IICC0_bit.no7

#define DAD0              IICCL0_bit.no4
#define CLD0              IICCL0_bit.no5

#define CLX0              IICX0_bit.no0

#define SPD0              IICS0_bit.no0
#define STD0              IICS0_bit.no1
#define ACKD0             IICS0_bit.no2
#define TRC0              IICS0_bit.no3
#define COI0              IICS0_bit.no4
#define EXC0              IICS0_bit.no5
#define ALD0              IICS0_bit.no6
#define MSTS0             IICS0_bit.no7

#define IICRSV0           IICF0_bit.no0
#define STCEN0            IICF0_bit.no1
#define IICBSY0           IICF0_bit.no6
#define STCF0             IICF0_bit.no7

#define SPT1              IICC1_bit.no0
#define STT1              IICC1_bit.no1
#define ACKE1             IICC1_bit.no2
#define WTIM1             IICC1_bit.no3
#define SPIE1             IICC1_bit.no4
#define WREL1             IICC1_bit.no5
#define LREL1             IICC1_bit.no6
#define IICE1             IICC1_bit.no7

#define DAD1              IICCL1_bit.no4
#define CLD1              IICCL1_bit.no5

#define CLX1              IICX1_bit.no0

#define SPD1              IICS1_bit.no0
#define STD1              IICS1_bit.no1
#define ACKD1             IICS1_bit.no2
#define TRC1              IICS1_bit.no3
#define COI1              IICS1_bit.no4
#define EXC1              IICS1_bit.no5
#define ALD1              IICS1_bit.no6
#define MSTS1             IICS1_bit.no7

#define IICRSV1           IICF1_bit.no0
#define STCEN1            IICF1_bit.no1
#define IICBSY1           IICF1_bit.no6
#define STCF1             IICF1_bit.no7

#define SPT2              IICC2_bit.no0
#define STT2              IICC2_bit.no1
#define ACKE2             IICC2_bit.no2
#define WTIM2             IICC2_bit.no3
#define SPIE2             IICC2_bit.no4
#define WREL2             IICC2_bit.no5
#define LREL2             IICC2_bit.no6
#define IICE2             IICC2_bit.no7

#define DAD2              IICCL2_bit.no4
#define CLD2              IICCL2_bit.no5

#define CLX2              IICX2_bit.no0

#define SPD2              IICS2_bit.no0
#define STD2              IICS2_bit.no1
#define ACKD2             IICS2_bit.no2
#define TRC2              IICS2_bit.no3
#define COI2              IICS2_bit.no4
#define EXC2              IICS2_bit.no5
#define ALD2              IICS2_bit.no6
#define MSTS2             IICS2_bit.no7

#define IICRSV2           IICF2_bit.no0
#define STCEN2            IICF2_bit.no1
#define IICBSY2           IICF2_bit.no6
#define STCF2             IICF2_bit.no7

#endif /* __IAR_SYSTEMS_ICC__ */

/***********************************************
 *       Interrupt/Exeption table declarations
 ***********************************************/

#define RESET_vector             (0x0000)
#define NMI_vector               (0x0010)
#define INTWDT2_vector           (0x0020)
#define DBG0_vector              (0x0060)
#define ILGOP_vector             (0x0060)
#define SECURITY_ID_vector       (0x0070)
#define INTLVI_vector            (0x0080)
#define INTP0_vector             (0x0090)
#define INTP1_vector             (0x00A0)
#define INTP2_vector             (0x00B0)
#define INTP3_vector             (0x00C0)
#define INTP4_vector             (0x00D0)
#define INTP5_vector             (0x00E0)
#define INTP6_vector             (0x00F0)
#define INTP7_vector             (0x0100)
#define INTTQ0OV_vector          (0x0110)
#define INTTQ0CC0_vector         (0x0120)
#define INTTQ0CC1_vector         (0x0130)
#define INTTQ0CC2_vector         (0x0140)
#define INTTQ0CC3_vector         (0x0150)
#define INTTP0OV_vector          (0x0160)
#define INTTP0CC0_vector         (0x0170)
#define INTTP0CC1_vector         (0x0180)
#define INTTP1OV_vector          (0x0190)
#define INTTP1CC0_vector         (0x01A0)
#define INTTP1CC1_vector         (0x01B0)
#define INTTP2OV_vector          (0x01C0)
#define INTTP2CC0_vector         (0x01D0)
#define INTTP2CC1_vector         (0x01E0)
#define INTTP3OV_vector          (0x01F0)
#define INTTP3CC0_vector         (0x0200)
#define INTTP3CC1_vector         (0x0210)
#define INTTP4OV_vector          (0x0220)
#define INTTP4CC0_vector         (0x0230)
#define INTTP4CC1_vector         (0x0240)
#define INTTP5OV_vector          (0x0250)
#define INTTP5CC0_vector         (0x0260)
#define INTTP5CC1_vector         (0x0270)
#define INTTM0EQ0_vector         (0x0280)
#define INTCB0R_vector           (0x0290)
#define INTIIC1_vector           (0x0290)
#define INTCB0T_vector           (0x02A0)
#define INTCB1R_vector           (0x02B0)
#define INTCB1T_vector           (0x02C0)
#define INTCB2R_vector           (0x02D0)
#define INTCB2T_vector           (0x02E0)
#define INTCB3R_vector           (0x02F0)
#define INTCB3T_vector           (0x0300)
#define INTCB4R_vector           (0x0310)
#define INTUA0R_vector           (0x0310)
#define INTCB4T_vector           (0x0320)
#define INTUA0T_vector           (0x0320)
#define INTIIC2_vector           (0x0330)
#define INTUA1R_vector           (0x0330)
#define INTUA1T_vector           (0x0340)
#define INTIIC0_vector           (0x0350)
#define INTUA2R_vector           (0x0350)
#define INTUA2T_vector           (0x0360)
#define INTAD_vector             (0x0370)
#define INTDMA0_vector           (0x0380)
#define INTDMA1_vector           (0x0390)
#define INTDMA2_vector           (0x03A0)
#define INTDMA3_vector           (0x03B0)
#define INTKR_vector             (0x03C0)
#define INTWTI_vector            (0x03D0)
#define INTWT_vector             (0x03E0)
#define INTC0ERR_vector          (0x03F0)
#define INTERR_vector            (0x03F0)
#define INTC0WUP_vector          (0x0400)
#define INTSTA_vector            (0x0400)
#define INTC0REC_vector          (0x0410)
#define INTIE1_vector            (0x0410)
#define INTC0TRX_vector          (0x0420)
#define INTIE2_vector            (0x0420)
#define INTC1ERR_vector          (0x0430)
#define INTC1WUP_vector          (0x0440)
#define INTC1REC_vector          (0x0450)
#define INTC1TRX_vector          (0x0460)
#define INTP8_vector             (0x0470)
#define INTTP6OV_vector          (0x0480)
#define INTTP6CC0_vector         (0x0490)
#define INTTP6CC1_vector         (0x04A0)
#define INTTP7OV_vector          (0x04B0)
#define INTTP7CC0_vector         (0x04C0)
#define INTTP7CC1_vector         (0x04D0)
#define INTTP8OV_vector          (0x04E0)
#define INTTP8CC0_vector         (0x04F0)
#define INTTP8CC1_vector         (0x0500)
#define INTCB5R_vector           (0x0510)
#define INTCB5T_vector           (0x0520)
#define INTUA3R_vector           (0x0530)
#define INTUA3T_vector           (0x0540)

/***********************************************
 *       Trap vectors
 ***********************************************/

#define TRAP00_vector      (0x00)
#define TRAP01_vector      (0x01)
#define TRAP02_vector      (0x02)
#define TRAP03_vector      (0x03)
#define TRAP04_vector      (0x04)
#define TRAP05_vector      (0x05)
#define TRAP06_vector      (0x06)
#define TRAP07_vector      (0x07)
#define TRAP08_vector      (0x08)
#define TRAP09_vector      (0x09)
#define TRAP0A_vector      (0x0A)
#define TRAP0B_vector      (0x0B)
#define TRAP0C_vector      (0x0C)
#define TRAP0D_vector      (0x0D)
#define TRAP0E_vector      (0x0E)
#define TRAP0F_vector      (0x0F)
#define TRAP10_vector      (0x10)
#define TRAP11_vector      (0x11)
#define TRAP12_vector      (0x12)
#define TRAP13_vector      (0x13)
#define TRAP14_vector      (0x14)
#define TRAP15_vector      (0x15)
#define TRAP16_vector      (0x16)
#define TRAP17_vector      (0x17)
#define TRAP18_vector      (0x18)
#define TRAP19_vector      (0x19)
#define TRAP1A_vector      (0x1A)
#define TRAP1B_vector      (0x1B)
#define TRAP1C_vector      (0x1C)
#define TRAP1D_vector      (0x1D)
#define TRAP1E_vector      (0x1E)
#define TRAP1F_vector      (0x1F)

#pragma language=default

#endif /* __IO70F3365_H__ */
