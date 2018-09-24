/*-------------------------------------------------------------------------
 *      Declarations of Peripheral I/O registers; I/O register bits;
 *      Interrupt/Exeption vectors; Trap vectors and; V850E only; Callt
 *      vectors for V850ES microcontroller uPD70F3365.
 *
 *
 *-------------------------------------------------------------------------*/

typedef  unsigned short __IO_REG16;
typedef  unsigned char  __IO_REG8;
typedef  unsigned long  __IO_REG32;

typedef  struct{
    unsigned   no0:1;
    unsigned   no1:1;
    unsigned   no2:1;
    unsigned   no3:1;
    unsigned   no4:1;
    unsigned   no5:1;
    unsigned   no6:1;
    unsigned   no7:1;
}__IO_REG8_BIT;


typedef  struct{
    unsigned   no0:1;
    unsigned   no1:1;
    unsigned   no2:1;
    unsigned   no3:1;
    unsigned   no4:1;
    unsigned   no5:1;
    unsigned   no6:1;
    unsigned   no7:1;
    unsigned   no8:1;
    unsigned   no9:1;
    unsigned   no10:1;
    unsigned   no11:1;
    unsigned   no12:1;
    unsigned   no13:1;
    unsigned   no14:1;
    unsigned   no15:1;
}__IO_REG16_BIT;


/*******************************************************************************
*
*  register addr
*
********************************************************************************/
#define  addr_PDL           (((void*)0xFFFFF004))
#define  addr_PDLL          (((void*)0xFFFFF004))
#define  addr_PDLH          (((void*)0xFFFFF005))
#define  addr_PDH           (((void*)0xFFFFF006))

#define  addr_PCS           (((void*)0xFFFFF008))
#define  addr_PCT           (((void*)0xFFFFF00A))
#define  addr_PCM           (((void*)0xFFFFF00C))
#define  addr_PCD           (((void*)0xFFFFF00E))

#define  addr_PMDL          (((void*)0xFFFFF024))
#define  addr_PMDLL         (((void*)0xFFFFF024))
#define  addr_PMDLH         (((void*)0xFFFFF025))
#define  addr_PMDH          (((void*)0xFFFFF026))
#define  addr_PMCS          (((void*)0xFFFFF028))
#define  addr_PMCT          (((void*)0xFFFFF02A))
#define  addr_PMCM          (((void*)0xFFFFF02C))
#define  addr_PMCD          (((void*)0xFFFFF02E))
 
#define  addr_PMCDL         (((void*)0xFFFFF044))
#define  addr_PMCDLL        (((void*)0xFFFFF044))
#define  addr_PMCDLH        (((void*)0xFFFFF045))
#define  addr_PMCDH         (((void*)0xFFFFF046))
#define  addr_PMCCS         (((void*)0xFFFFF048))
#define  addr_PMCCT         (((void*)0xFFFFF04A))
#define  addr_PMCCM         (((void*)0xFFFFF04C))
 
#define  addr_BPC           (((void*)0xFFFFF064))
#define  addr_BSC           (((void*)0xFFFFF066))
 
#define  addr_VSWC          (((void*)0xFFFFF06E))
 
#define  addr_DSA0L         (((void*)0xFFFFF080))
#define  addr_DSA0H         (((void*)0xFFFFF082))
#define  addr_DDA0L         (((void*)0xFFFFF084))
#define  addr_DDA0H         (((void*)0xFFFFF086))
#define  addr_DSA1L         (((void*)0xFFFFF088))
#define  addr_DSA1H         (((void*)0xFFFFF08A))
#define  addr_DDA1L         (((void*)0xFFFFF08C))
#define  addr_DDA1H         (((void*)0xFFFFF08E))
#define  addr_DSA2L         (((void*)0xFFFFF090))
#define  addr_DSA2H         (((void*)0xFFFFF092))
#define  addr_DDA2L         (((void*)0xFFFFF094))
#define  addr_DDA2H         (((void*)0xFFFFF096))
#define  addr_DSA3L         (((void*)0xFFFFF098))
#define  addr_DSA3H         (((void*)0xFFFFF09A))
#define  addr_DDA3L         (((void*)0xFFFFF09C))
#define  addr_DDA3H         (((void*)0xFFFFF09E))
 
#define  addr_DBC0          (((void*)0xFFFFF0C0))
#define  addr_DBC1          (((void*)0xFFFFF0C2))
#define  addr_DBC2          (((void*)0xFFFFF0C4))
#define  addr_DBC3          (((void*)0xFFFFF0C6))
 
#define  addr_DADC0         (((void*)0xFFFFF0D0))
#define  addr_DADC1         (((void*)0xFFFFF0D2))
#define  addr_DADC2         (((void*)0xFFFFF0D4))
#define  addr_DADC3         (((void*)0xFFFFF0D6))
 
#define  addr_DCHC0         (((void*)0xFFFFF0E0))
#define  addr_DCHC1         (((void*)0xFFFFF0E2))
#define  addr_DCHC2         (((void*)0xFFFFF0E4))
#define  addr_DCHC3         (((void*)0xFFFFF0E6))
 
#define  addr_IMR0          (((void*)0xFFFFF100))
#define  addr_IMR0L         (((void*)0xFFFFF100))
#define  addr_IMR0H         (((void*)0xFFFFF101))
#define  addr_IMR1          (((void*)0xFFFFF102))
#define  addr_IMR1L         (((void*)0xFFFFF102))
#define  addr_IMR1H         (((void*)0xFFFFF103))
#define  addr_IMR2          (((void*)0xFFFFF104))
#define  addr_IMR2L         (((void*)0xFFFFF104))
#define  addr_IMR2H         (((void*)0xFFFFF105))
#define  addr_IMR3          (((void*)0xFFFFF106))
#define  addr_IMR3L         (((void*)0xFFFFF106))
#define  addr_IMR3H         (((void*)0xFFFFF107))
#define  addr_IMR4          (((void*)0xFFFFF108))
#define  addr_IMR4L         (((void*)0xFFFFF108))
#define  addr_IMR4H         (((void*)0xFFFFF109))
 
#define  addr_LVIIC         (((void*)0xFFFFF110))
#define  addr_PIC0          (((void*)0xFFFFF112))
#define  addr_PIC1          (((void*)0xFFFFF114))
#define  addr_PIC2          (((void*)0xFFFFF116))
#define  addr_PIC3          (((void*)0xFFFFF118))
#define  addr_PIC4          (((void*)0xFFFFF11A))
#define  addr_PIC5          (((void*)0xFFFFF11C))
#define  addr_PIC6          (((void*)0xFFFFF11E))
#define  addr_PIC7          (((void*)0xFFFFF120))
#define  addr_TQ0OVIC       (((void*)0xFFFFF122))
#define  addr_TQ0CCIC0      (((void*)0xFFFFF124))
#define  addr_TQ0CCIC1      (((void*)0xFFFFF126))
#define  addr_TQ0CCIC2      (((void*)0xFFFFF128))
#define  addr_TQ0CCIC3      (((void*)0xFFFFF12A))
#define  addr_TP0OVIC       (((void*)0xFFFFF12C))
#define  addr_TP0CCIC0      (((void*)0xFFFFF12E))
#define  addr_TP0CCIC1      (((void*)0xFFFFF130))
#define  addr_TP1OVIC       (((void*)0xFFFFF132))
#define  addr_TP1CCIC0      (((void*)0xFFFFF134))
#define  addr_TP1CCIC1      (((void*)0xFFFFF136))
#define  addr_TP2OVIC       (((void*)0xFFFFF138))
#define  addr_TP2CCIC0      (((void*)0xFFFFF13A))
#define  addr_TP2CCIC1      (((void*)0xFFFFF13C))
#define  addr_TP3OVIC       (((void*)0xFFFFF13E))
#define  addr_TP3CCIC0      (((void*)0xFFFFF140))
#define  addr_TP3CCIC1      (((void*)0xFFFFF142))
#define  addr_TP4OVIC       (((void*)0xFFFFF144))
#define  addr_TP4CCIC0      (((void*)0xFFFFF146))
#define  addr_TP4CCIC1      (((void*)0xFFFFF148))
#define  addr_TP5OVIC       (((void*)0xFFFFF14A))
#define  addr_TP5CCIC0      (((void*)0xFFFFF14C))
#define  addr_TP5CCIC1      (((void*)0xFFFFF14E))
#define  addr_TM0EQIC0      (((void*)0xFFFFF150))
#define  addr_CB0RIC        (((void*)0xFFFFF152))
#define  addr_IICIC1        (((void*)0xFFFFF152))
#define  addr_CB0TIC        (((void*)0xFFFFF154))
#define  addr_CB1RIC        (((void*)0xFFFFF156))
#define  addr_CB1TIC        (((void*)0xFFFFF158))
#define  addr_CB2RIC        (((void*)0xFFFFF15A))
#define  addr_CB2TIC        (((void*)0xFFFFF15C))
#define  addr_CB3RIC        (((void*)0xFFFFF15E))
#define  addr_CB3TIC        (((void*)0xFFFFF160))
#define  addr_CB4RIC        (((void*)0xFFFFF162))
#define  addr_UA0RIC        (((void*)0xFFFFF162))
#define  addr_CB4TIC        (((void*)0xFFFFF164))
#define  addr_UA0TIC        (((void*)0xFFFFF164))
#define  addr_IICIC2        (((void*)0xFFFFF166))
#define  addr_UA1RIC        (((void*)0xFFFFF166))
#define  addr_UA1TIC        (((void*)0xFFFFF168))
#define  addr_IICIC0        (((void*)0xFFFFF16A))
#define  addr_UA2RIC        (((void*)0xFFFFF16A))
#define  addr_UA2TIC        (((void*)0xFFFFF16C))
#define  addr_ADIC          (((void*)0xFFFFF16E))
#define  addr_DMAIC0        (((void*)0xFFFFF170))
#define  addr_DMAIC1        (((void*)0xFFFFF172))
#define  addr_DMAIC2        (((void*)0xFFFFF174))
#define  addr_DMAIC3        (((void*)0xFFFFF176))
#define  addr_KRIC          (((void*)0xFFFFF178))
#define  addr_WTIIC         (((void*)0xFFFFF17A))
#define  addr_WTIC          (((void*)0xFFFFF17C))
#define  addr_ERRIC         (((void*)0xFFFFF17E))
#define  addr_ERRIC0        (((void*)0xFFFFF17E))
#define  addr_STAIC         (((void*)0xFFFFF180))
#define  addr_WUPIC0        (((void*)0xFFFFF180))
#define  addr_IEIC1         (((void*)0xFFFFF182))
#define  addr_RECIC0        (((void*)0xFFFFF182))
#define  addr_IEIC2         (((void*)0xFFFFF184))
#define  addr_TRXIC0        (((void*)0xFFFFF184))
#define  addr_ERRIC1        (((void*)0xFFFFF186))
#define  addr_WUPIC1        (((void*)0xFFFFF188))
#define  addr_RECIC1        (((void*)0xFFFFF18A))
#define  addr_TRXIC1        (((void*)0xFFFFF18C))
#define  addr_PIC8          (((void*)0xFFFFF18E))
#define  addr_TP6OVIC       (((void*)0xFFFFF190))
#define  addr_TP6CCIC0      (((void*)0xFFFFF192))
#define  addr_TP6CCIC1      (((void*)0xFFFFF194))
#define  addr_TP7OVIC       (((void*)0xFFFFF196))
#define  addr_TP7CCIC0      (((void*)0xFFFFF198))
#define  addr_TP7CCIC1      (((void*)0xFFFFF19A))
#define  addr_TP8OVIC       (((void*)0xFFFFF19C))
#define  addr_TP8CCIC0      (((void*)0xFFFFF19E))
#define  addr_TP8CCIC1      (((void*)0xFFFFF1A0))
#define  addr_CB5RIC        (((void*)0xFFFFF1A2))
#define  addr_CB5TIC        (((void*)0xFFFFF1A4))
#define  addr_UA3RIC        (((void*)0xFFFFF1A6))
#define  addr_UA3TIC        (((void*)0xFFFFF1A8))
 
#define  addr_ISPR          (((void*)0xFFFFF1FA))
#define  addr_PRCMD         (((void*)0xFFFFF1FC))
#define  addr_PSC           (((void*)0xFFFFF1FE))
#define  addr_ADA0M0        (((void*)0xFFFFF200))
#define  addr_ADA0M1        (((void*)0xFFFFF201))
#define  addr_ADA0S         (((void*)0xFFFFF202))
#define  addr_ADA0M2        (((void*)0xFFFFF203))
#define  addr_ADA0PFM       (((void*)0xFFFFF204))
#define  addr_ADA0PFT       (((void*)0xFFFFF205))
 
#define  addr_ADA0CR0       (((void*)0xFFFFF210))
#define  addr_ADA0CR0H      (((void*)0xFFFFF211))
#define  addr_ADA0CR1       (((void*)0xFFFFF212))
#define  addr_ADA0CR1H      (((void*)0xFFFFF213))
#define  addr_ADA0CR2       (((void*)0xFFFFF214))
#define  addr_ADA0CR2H      (((void*)0xFFFFF215))
#define  addr_ADA0CR3       (((void*)0xFFFFF216))
#define  addr_ADA0CR3H      (((void*)0xFFFFF217))
#define  addr_ADA0CR4       (((void*)0xFFFFF218))
#define  addr_ADA0CR4H      (((void*)0xFFFFF219))
#define  addr_ADA0CR5       (((void*)0xFFFFF21A))
#define  addr_ADA0CR5H      (((void*)0xFFFFF21B))
#define  addr_ADA0CR6       (((void*)0xFFFFF21C))
#define  addr_ADA0CR6H      (((void*)0xFFFFF21D))
#define  addr_ADA0CR7       (((void*)0xFFFFF21E))
#define  addr_ADA0CR7H      (((void*)0xFFFFF21F))
#define  addr_ADA0CR8       (((void*)0xFFFFF220))
#define  addr_ADA0CR8H      (((void*)0xFFFFF221))
#define  addr_ADA0CR9       (((void*)0xFFFFF222))
#define  addr_ADA0CR9H      (((void*)0xFFFFF223))
#define  addr_ADA0CR10      (((void*)0xFFFFF224))
#define  addr_ADA0CR10H     (((void*)0xFFFFF225))
#define  addr_ADA0CR11      (((void*)0xFFFFF226))
#define  addr_ADA0CR11H     (((void*)0xFFFFF227))
#define  addr_ADA0CR12      (((void*)0xFFFFF228))
#define  addr_ADA0CR12H     (((void*)0xFFFFF229))
#define  addr_ADA0CR13      (((void*)0xFFFFF22A))
#define  addr_ADA0CR13H     (((void*)0xFFFFF22B))
#define  addr_ADA0CR14      (((void*)0xFFFFF22C))
#define  addr_ADA0CR14H     (((void*)0xFFFFF22D))
#define  addr_ADA0CR15      (((void*)0xFFFFF22E))
#define  addr_ADA0CR15H     (((void*)0xFFFFF22F))
 
#define  addr_DA0CS0        (((void*)0xFFFFF280))
#define  addr_DA0CS1        (((void*)0xFFFFF281))
#define  addr_DA0M          (((void*)0xFFFFF282))
 
#define  addr_KRM           (((void*)0xFFFFF300))
 
#define  addr_SELCNT0       (((void*)0xFFFFF308))
 
#define  addr_CRCIN         (((void*)0xFFFFF310))
#define  addr_CRCD          (((void*)0xFFFFF312))
 
#define  addr_NFC           (((void*)0xFFFFF318))
 
#define  addr_PRSM1         (((void*)0xFFFFF320))
#define  addr_PRSCM1        (((void*)0xFFFFF321))
 
#define  addr_PRSM2         (((void*)0xFFFFF324))
#define  addr_PRSCM2        (((void*)0xFFFFF325))
 
#define  addr_PRSM3         (((void*)0xFFFFF328))
#define  addr_PRSCM3        (((void*)0xFFFFF329))
 
#define  addr_OCKS0         (((void*)0xFFFFF340))
 
#define  addr_OCKS1         (((void*)0xFFFFF344))
 
#define  addr_OCKS2         (((void*)0xFFFFF348))
 
#define  addr_BCR           (((void*)0xFFFFF360))
#define  addr_PSR           (((void*)0xFFFFF361))
#define  addr_SSR           (((void*)0xFFFFF362))
#define  addr_USR           (((void*)0xFFFFF363))
#define  addr_ISR           (((void*)0xFFFFF364))
#define  addr_ESR           (((void*)0xFFFFF365))
#define  addr_UAR           (((void*)0xFFFFF366))
#define  addr_SAR           (((void*)0xFFFFF368))
#define  addr_PAR           (((void*)0xFFFFF36A))
#define  addr_RSA           (((void*)0xFFFFF36C))
#define  addr_CDR           (((void*)0xFFFFF36E))
#define  addr_DLR           (((void*)0xFFFFF36F))
#define  addr_DR            (((void*)0xFFFFF370))
#define  addr_FSR           (((void*)0xFFFFF371))
#define  addr_SCR           (((void*)0xFFFFF372))
#define  addr_CCR           (((void*)0xFFFFF373))
 
#define  addr_P0            (((void*)0xFFFFF400))
#define  addr_P1            (((void*)0xFFFFF402))
 
#define  addr_P3            (((void*)0xFFFFF406))
#define  addr_P3L           (((void*)0xFFFFF406))
#define  addr_P3H           (((void*)0xFFFFF407))
#define  addr_P4            (((void*)0xFFFFF408))
#define  addr_P5            (((void*)0xFFFFF40A))
#define  addr_P6            (((void*)0xFFFFF40C))
#define  addr_P6L           (((void*)0xFFFFF40C))
#define  addr_P6H           (((void*)0xFFFFF40D))
#define  addr_P7L           (((void*)0xFFFFF40E))
#define  addr_P7H           (((void*)0xFFFFF40F))
#define  addr_P8            (((void*)0xFFFFF410))
#define  addr_P9            (((void*)0xFFFFF412))
#define  addr_P9L           (((void*)0xFFFFF412))
#define  addr_P9H           (((void*)0xFFFFF413))
 
#define  addr_PM0           (((void*)0xFFFFF420))
#define  addr_PM1           (((void*)0xFFFFF422))
 
#define  addr_PM3           (((void*)0xFFFFF426))
#define  addr_PM3L          (((void*)0xFFFFF426))
#define  addr_PM3H          (((void*)0xFFFFF427))
#define  addr_PM4           (((void*)0xFFFFF428))
#define  addr_PM5           (((void*)0xFFFFF42A))
#define  addr_PM6           (((void*)0xFFFFF42C))
#define  addr_PM6L          (((void*)0xFFFFF42C))
#define  addr_PM6H          (((void*)0xFFFFF42D))
#define  addr_PM7L          (((void*)0xFFFFF42E))
#define  addr_PM7H          (((void*)0xFFFFF42F))
#define  addr_PM8           (((void*)0xFFFFF430))
#define  addr_PM9           (((void*)0xFFFFF432))
#define  addr_PM9L          (((void*)0xFFFFF432))
#define  addr_PM9H          (((void*)0xFFFFF433))
 
#define  addr_PMC0          (((void*)0xFFFFF440))
 
#define  addr_PMC3          (((void*)0xFFFFF446))
#define  addr_PMC3L         (((void*)0xFFFFF446))
#define  addr_PMC3H         (((void*)0xFFFFF447))
#define  addr_PMC4          (((void*)0xFFFFF448))
#define  addr_PMC5          (((void*)0xFFFFF44A))
#define  addr_PMC6          (((void*)0xFFFFF44C))
#define  addr_PMC6L         (((void*)0xFFFFF44C))
#define  addr_PMC6H         (((void*)0xFFFFF44D))
 
#define  addr_PMC8          (((void*)0xFFFFF450))
#define  addr_PMC9          (((void*)0xFFFFF452))
#define  addr_PMC9L         (((void*)0xFFFFF452))
#define  addr_PMC9H         (((void*)0xFFFFF453))
 
#define  addr_PFC0          (((void*)0xFFFFF460))
 
#define  addr_PFC3          (((void*)0xFFFFF466))
#define  addr_PFC3L         (((void*)0xFFFFF466))
#define  addr_PFC3H         (((void*)0xFFFFF467))
#define  addr_PFC4          (((void*)0xFFFFF468))
#define  addr_PFC5          (((void*)0xFFFFF46A))
 
#define  addr_PFC6H         (((void*)0xFFFFF46D))
 
#define  addr_PFC9          (((void*)0xFFFFF472))
#define  addr_PFC9L         (((void*)0xFFFFF472))
#define  addr_PFC9H         (((void*)0xFFFFF473))
 
#define  addr_DWC0          (((void*)0xFFFFF484))
 
#define  addr_AWC           (((void*)0xFFFFF488))
#define  addr_BCC           (((void*)0xFFFFF48A))
 
#define  addr_TQ0CTL0       (((void*)0xFFFFF540))
#define  addr_TQ0CTL1       (((void*)0xFFFFF541))
#define  addr_TQ0IOC0       (((void*)0xFFFFF542))
#define  addr_TQ0IOC1       (((void*)0xFFFFF543))
#define  addr_TQ0IOC2       (((void*)0xFFFFF544))
#define  addr_TQ0OPT0       (((void*)0xFFFFF545))
#define  addr_TQ0CCR0       (((void*)0xFFFFF546))
#define  addr_TQ0CCR1       (((void*)0xFFFFF548))
#define  addr_TQ0CCR2       (((void*)0xFFFFF54A))
#define  addr_TQ0CCR3       (((void*)0xFFFFF54C))
#define  addr_TQ0CNT        (((void*)0xFFFFF54E))
 
#define  addr_TP0CTL0       (((void*)0xFFFFF590))
#define  addr_TP0CTL1       (((void*)0xFFFFF591))
#define  addr_TP0IOC0       (((void*)0xFFFFF592))
#define  addr_TP0IOC1       (((void*)0xFFFFF593))
#define  addr_TP0IOC2       (((void*)0xFFFFF594))
#define  addr_TP0OPT0       (((void*)0xFFFFF595))
#define  addr_TP0CCR0       (((void*)0xFFFFF596))
#define  addr_TP0CCR1       (((void*)0xFFFFF598))
#define  addr_TP0CNT        (((void*)0xFFFFF59A))
 
#define  addr_TP1CTL0       (((void*)0xFFFFF5A0))
#define  addr_TP1CTL1       (((void*)0xFFFFF5A1))
#define  addr_TP1IOC0       (((void*)0xFFFFF5A2))
#define  addr_TP1IOC1       (((void*)0xFFFFF5A3))
#define  addr_TP1IOC2       (((void*)0xFFFFF5A4))
#define  addr_TP1OPT0       (((void*)0xFFFFF5A5))
#define  addr_TP1CCR0       (((void*)0xFFFFF5A6))
#define  addr_TP1CCR1       (((void*)0xFFFFF5A8))
#define  addr_TP1CNT        (((void*)0xFFFFF5AA))
 
#define  addr_TP2CTL0       (((void*)0xFFFFF5B0))
#define  addr_TP2CTL1       (((void*)0xFFFFF5B1))
#define  addr_TP2IOC0       (((void*)0xFFFFF5B2))
#define  addr_TP2IOC1       (((void*)0xFFFFF5B3))
#define  addr_TP2IOC2       (((void*)0xFFFFF5B4))
#define  addr_TP2OPT0       (((void*)0xFFFFF5B5))
#define  addr_TP2CCR0       (((void*)0xFFFFF5B6))
#define  addr_TP2CCR1       (((void*)0xFFFFF5B8))
#define  addr_TP2CNT        (((void*)0xFFFFF5BA))
 
#define  addr_TP3CTL0       (((void*)0xFFFFF5C0))
#define  addr_TP3CTL1       (((void*)0xFFFFF5C1))
#define  addr_TP3IOC0       (((void*)0xFFFFF5C2))
#define  addr_TP3IOC1       (((void*)0xFFFFF5C3))
#define  addr_TP3IOC2       (((void*)0xFFFFF5C4))
#define  addr_TP3OPT0       (((void*)0xFFFFF5C5))
#define  addr_TP3CCR0       (((void*)0xFFFFF5C6))
#define  addr_TP3CCR1       (((void*)0xFFFFF5C8))
#define  addr_TP3CNT        (((void*)0xFFFFF5CA))
 
#define  addr_TP4CTL0       (((void*)0xFFFFF5D0))
#define  addr_TP4CTL1       (((void*)0xFFFFF5D1))
#define  addr_TP4IOC0       (((void*)0xFFFFF5D2))
#define  addr_TP4IOC1       (((void*)0xFFFFF5D3))
#define  addr_TP4IOC2       (((void*)0xFFFFF5D4))
#define  addr_TP4OPT0       (((void*)0xFFFFF5D5))
#define  addr_TP4CCR0       (((void*)0xFFFFF5D6))
#define  addr_TP4CCR1       (((void*)0xFFFFF5D8))
#define  addr_TP4CNT        (((void*)0xFFFFF5DA))
 
#define  addr_TP5CTL0       (((void*)0xFFFFF5E0))
#define  addr_TP5CTL1       (((void*)0xFFFFF5E1))
#define  addr_TP5IOC0       (((void*)0xFFFFF5E2))
#define  addr_TP5IOC1       (((void*)0xFFFFF5E3))
#define  addr_TP5IOC2       (((void*)0xFFFFF5E4))
#define  addr_TP5OPT0       (((void*)0xFFFFF5E5))
#define  addr_TP5CCR0       (((void*)0xFFFFF5E6))
#define  addr_TP5CCR1       (((void*)0xFFFFF5E8))
#define  addr_TP5CNT        (((void*)0xFFFFF5EA))
 
#define  addr_TP6CTL0       (((void*)0xFFFFF5F0))
#define  addr_TP6CTL1       (((void*)0xFFFFF5F1))
#define  addr_TP6IOC0       (((void*)0xFFFFF5F2))
#define  addr_TP6IOC1       (((void*)0xFFFFF5F3))
#define  addr_TP6IOC2       (((void*)0xFFFFF5F4))
#define  addr_TP6OPT0       (((void*)0xFFFFF5F5))
#define  addr_TP6CCR0       (((void*)0xFFFFF5F6))
#define  addr_TP6CCR1       (((void*)0xFFFFF5F8))
#define  addr_TP6CNT        (((void*)0xFFFFF5FA))
 
#define  addr_TP7CTL0       (((void*)0xFFFFF600))
#define  addr_TP7CTL1       (((void*)0xFFFFF601))
#define  addr_TP7IOC0       (((void*)0xFFFFF602))
#define  addr_TP7IOC1       (((void*)0xFFFFF603))
#define  addr_TP7IOC2       (((void*)0xFFFFF604))
#define  addr_TP7OPT0       (((void*)0xFFFFF605))
#define  addr_TP7CCR0       (((void*)0xFFFFF606))
#define  addr_TP7CCR1       (((void*)0xFFFFF608))
#define  addr_TP7CNT        (((void*)0xFFFFF60A))
 
#define  addr_TP8CTL0       (((void*)0xFFFFF610))
#define  addr_TP8CTL1       (((void*)0xFFFFF611))
#define  addr_TP8IOC0       (((void*)0xFFFFF612))
#define  addr_TP8IOC1       (((void*)0xFFFFF613))
#define  addr_TP8IOC2       (((void*)0xFFFFF614))
#define  addr_TP8OPT0       (((void*)0xFFFFF615))
#define  addr_TP8CCR0       (((void*)0xFFFFF616))
#define  addr_TP8CCR1       (((void*)0xFFFFF618))
#define  addr_TP8CNT        (((void*)0xFFFFF61A))
 
#define  addr_WTM           (((void*)0xFFFFF680))
 
#define  addr_TM0CTL0       (((void*)0xFFFFF690))
 
#define  addr_TM0CMP0       (((void*)0xFFFFF694))
 
#define  addr_OSTS          (((void*)0xFFFFF6C0))
#define  addr_PLLS          (((void*)0xFFFFF6C1))
 
#define  addr_WDTM2         (((void*)0xFFFFF6D0))
#define  addr_WDTE          (((void*)0xFFFFF6D1))
 
#define  addr_RTBL0         (((void*)0xFFFFF6E0))
#define  addr_RTBH0         (((void*)0xFFFFF6E2))
#define  addr_RTPM0         (((void*)0xFFFFF6E4))
#define  addr_RTPC0         (((void*)0xFFFFF6E5))
 
#define  addr_RTBL1         (((void*)0xFFFFF6F0))
#define  addr_RTBH1         (((void*)0xFFFFF6F2))
#define  addr_RTPM1         (((void*)0xFFFFF6F4))
#define  addr_RTPC1         (((void*)0xFFFFF6F5))
 
#define  addr_PFCE3L        (((void*)0xFFFFF706))
 
#define  addr_PFCE5         (((void*)0xFFFFF70A))
 
#define  addr_PFCE9         (((void*)0xFFFFF712))
#define  addr_PFCE9L        (((void*)0xFFFFF712))
#define  addr_PFCE9H        (((void*)0xFFFFF713))
 
#define  addr_SYS           (((void*)0xFFFFF802))
 
#define  addr_RCM           (((void*)0xFFFFF80C))
 
#define  addr_DTFR0         (((void*)0xFFFFF810))
#define  addr_DTFR1         (((void*)0xFFFFF812))
#define  addr_DTFR2         (((void*)0xFFFFF814))
#define  addr_DTFR3         (((void*)0xFFFFF816))
 
#define  addr_PSMR          (((void*)0xFFFFF820))
#define  addr_CKC           (((void*)0xFFFFF822))
#define  addr_LOCKR         (((void*)0xFFFFF824))
 
#define  addr_PCC           (((void*)0xFFFFF828))
 
#define  addr_PLLCTL        (((void*)0xFFFFF82C))
#define  addr_CCLS          (((void*)0xFFFFF82E))
 
#define  addr_CORAD0        (((void*)0xFFFFF840))
#define  addr_CORAD0L       (((void*)0xFFFFF840))
#define  addr_CORAD0H       (((void*)0xFFFFF842))
#define  addr_CORAD1        (((void*)0xFFFFF844))
#define  addr_CORAD1L       (((void*)0xFFFFF844))
#define  addr_CORAD1H       (((void*)0xFFFFF846))
#define  addr_CORAD2        (((void*)0xFFFFF848))
#define  addr_CORAD2L       (((void*)0xFFFFF848))
#define  addr_CORAD2H       (((void*)0xFFFFF84A))
#define  addr_CORAD3        (((void*)0xFFFFF84C))
#define  addr_CORAD3L       (((void*)0xFFFFF84C))
#define  addr_CORAD3H       (((void*)0xFFFFF84E))

#define  addr_C0INTS         (((void*)0x03FEC058))
#define  addr_C1INTS         (((void*)0x03FEC658))
#define  addr_CLM           (((void*)0xFFFFF870))
 
#define  addr_CORCN         (((void*)0xFFFFF880))
 
#define  addr_RESF          (((void*)0xFFFFF888))
 
#define  addr_LVIM          (((void*)0xFFFFF890))
#define  addr_LVIS          (((void*)0xFFFFF891))
#define  addr_RAMS          (((void*)0xFFFFF892))
 
#define  addr_PRSM0         (((void*)0xFFFFF8B0))
#define  addr_PRSCM0        (((void*)0xFFFFF8B1))
 
#define  addr_OCDM          (((void*)0xFFFFF9FC))
#define  addr_PEMU1         (((void*)0xFFFFF9FE))
#define  addr_UA0CTL0       (((void*)0xFFFFFA00))
#define  addr_UA0CTL1       (((void*)0xFFFFFA01))
#define  addr_UA0CTL2       (((void*)0xFFFFFA02))
#define  addr_UA0OPT0       (((void*)0xFFFFFA03))
#define  addr_UA0STR        (((void*)0xFFFFFA04))
#define  addr_UA0RX         (((void*)0xFFFFFA06))
#define  addr_UA0TX         (((void*)0xFFFFFA07))
 
#define  addr_UA1CTL0       (((void*)0xFFFFFA10))
#define  addr_UA1CTL1       (((void*)0xFFFFFA11))
#define  addr_UA1CTL2       (((void*)0xFFFFFA12))
#define  addr_UA1OPT0       (((void*)0xFFFFFA13))
#define  addr_UA1STR        (((void*)0xFFFFFA14))
#define  addr_UA1RX         (((void*)0xFFFFFA16))
#define  addr_UA1TX         (((void*)0xFFFFFA17))
 
#define  addr_UA2CTL0       (((void*)0xFFFFFA20))
#define  addr_UA2CTL1       (((void*)0xFFFFFA21))
#define  addr_UA2CTL2       (((void*)0xFFFFFA22))
#define  addr_UA2OPT0       (((void*)0xFFFFFA23))
#define  addr_UA2STR        (((void*)0xFFFFFA24))
#define  addr_UA2RX         (((void*)0xFFFFFA26))
#define  addr_UA2TX         (((void*)0xFFFFFA27))
 
#define  addr_UA3CTL0       (((void*)0xFFFFFA30))
#define  addr_UA3CTL1       (((void*)0xFFFFFA31))
#define  addr_UA3CTL2       (((void*)0xFFFFFA32))
#define  addr_UA3OPT0       (((void*)0xFFFFFA33))
#define  addr_UA3STR        (((void*)0xFFFFFA34))
#define  addr_UA3RX         (((void*)0xFFFFFA36))
#define  addr_UA3TX         (((void*)0xFFFFFA37))
 
#define  addr_INTF0         (((void*)0xFFFFFC00))
 
#define  addr_INTF3         (((void*)0xFFFFFC06))
 
#define  addr_INTF8         (((void*)0xFFFFFC10))
 
#define  addr_INTF9H        (((void*)0xFFFFFC13))
 
#define  addr_INTR0         (((void*)0xFFFFFC20))
 
#define  addr_INTR3         (((void*)0xFFFFFC26))
 
#define  addr_INTR8         (((void*)0xFFFFFC30))
 
#define  addr_INTR9H        (((void*)0xFFFFFC33))
 
#define  addr_PF0           (((void*)0xFFFFFC60))
 
#define  addr_PF3           (((void*)0xFFFFFC66))
#define  addr_PF3L          (((void*)0xFFFFFC66))
#define  addr_PF3H          (((void*)0xFFFFFC67))
#define  addr_PF4           (((void*)0xFFFFFC68))
#define  addr_PF5           (((void*)0xFFFFFC6A))
#define  addr_PF6           (((void*)0xFFFFFC6C))
#define  addr_PF6L          (((void*)0xFFFFFC6C))
#define  addr_PF6H          (((void*)0xFFFFFC6D))
 
#define  addr_PF8           (((void*)0xFFFFFC70))
#define  addr_PF9           (((void*)0xFFFFFC72))
#define  addr_PF9L          (((void*)0xFFFFFC72))
#define  addr_PF9H          (((void*)0xFFFFFC73))
 
#define  addr_PRDSELL       (((void*)0xFFFFFCC8))
#define  addr_PRDSELH       (((void*)0xFFFFFCCA))
 
#define  addr_CB0CTL0       (((void*)0xFFFFFD00))
#define  addr_CB0CTL1       (((void*)0xFFFFFD01))
#define  addr_CB0CTL2       (((void*)0xFFFFFD02))
#define  addr_CB0STR        (((void*)0xFFFFFD03))
#define  addr_CB0RX         (((void*)0xFFFFFD04))
#define  addr_CB0RXL        (((void*)0xFFFFFD04))
#define  addr_CB0TX         (((void*)0xFFFFFD06))
#define  addr_CB0TXL        (((void*)0xFFFFFD06))
 
#define  addr_CB1CTL0       (((void*)0xFFFFFD10))
#define  addr_CB1CTL1       (((void*)0xFFFFFD11))
#define  addr_CB1CTL2       (((void*)0xFFFFFD12))
#define  addr_CB1STR        (((void*)0xFFFFFD13))
#define  addr_CB1RX         (((void*)0xFFFFFD14))
#define  addr_CB1RXL        (((void*)0xFFFFFD14))
#define  addr_CB1TX         (((void*)0xFFFFFD16))
#define  addr_CB1TXL        (((void*)0xFFFFFD16))
 
#define  addr_CB2CTL0       (((void*)0xFFFFFD20))
#define  addr_CB2CTL1       (((void*)0xFFFFFD21))
#define  addr_CB2CTL2       (((void*)0xFFFFFD22))
#define  addr_CB2STR        (((void*)0xFFFFFD23))
#define  addr_CB2RX         (((void*)0xFFFFFD24))
#define  addr_CB2RXL        (((void*)0xFFFFFD24))
#define  addr_CB2TX         (((void*)0xFFFFFD26))
#define  addr_CB2TXL        (((void*)0xFFFFFD26))
 
#define  addr_CB3CTL0       (((void*)0xFFFFFD30))
#define  addr_CB3CTL1       (((void*)0xFFFFFD31))
#define  addr_CB3CTL2       (((void*)0xFFFFFD32))
#define  addr_CB3STR        (((void*)0xFFFFFD33))
#define  addr_CB3RX         (((void*)0xFFFFFD34))
#define  addr_CB3RXL        (((void*)0xFFFFFD34))
#define  addr_CB3TX         (((void*)0xFFFFFD36))
#define  addr_CB3TXL        (((void*)0xFFFFFD36))
 
#define  addr_CB4CTL0       (((void*)0xFFFFFD40))
#define  addr_CB4CTL1       (((void*)0xFFFFFD41))
#define  addr_CB4CTL2       (((void*)0xFFFFFD42))
#define  addr_CB4STR        (((void*)0xFFFFFD43))
#define  addr_CB4RX         (((void*)0xFFFFFD44))
#define  addr_CB4RXL        (((void*)0xFFFFFD44))
#define  addr_CB4TX         (((void*)0xFFFFFD46))
#define  addr_CB4TXL        (((void*)0xFFFFFD46))
 
#define  addr_CB5CTL0       (((void*)0xFFFFFD50))
#define  addr_CB5CTL1       (((void*)0xFFFFFD51))
#define  addr_CB5CTL2       (((void*)0xFFFFFD52))
#define  addr_CB5STR        (((void*)0xFFFFFD53))
#define  addr_CB5RX         (((void*)0xFFFFFD54))
#define  addr_CB5RXL        (((void*)0xFFFFFD54))
#define  addr_CB5TX         (((void*)0xFFFFFD56))
#define  addr_CB5TXL        (((void*)0xFFFFFD56))
 
#define  addr_IIC0          (((void*)0xFFFFFD80))
#define  addr_IICC0         (((void*)0xFFFFFD82))
#define  addr_SVA0          (((void*)0xFFFFFD83))
#define  addr_IICCL0        (((void*)0xFFFFFD84))
#define  addr_IICX0         (((void*)0xFFFFFD85))
#define  addr_IICS0         (((void*)0xFFFFFD86))
 
#define  addr_IICF0         (((void*)0xFFFFFD8A))
 
#define  addr_IIC1          (((void*)0xFFFFFD90))
#define  addr_IICC1         (((void*)0xFFFFFD92))
#define  addr_SVA1          (((void*)0xFFFFFD93))
#define  addr_IICCL1        (((void*)0xFFFFFD94))
#define  addr_IICX1         (((void*)0xFFFFFD95))
#define  addr_IICS1         (((void*)0xFFFFFD96))
 
#define  addr_IICF1         (((void*)0xFFFFFD9A))
 
#define  addr_IIC2          (((void*)0xFFFFFDA0))
#define  addr_IICC2         (((void*)0xFFFFFDA2))
#define  addr_SVA2          (((void*)0xFFFFFDA3))
#define  addr_IICCL2        (((void*)0xFFFFFDA4))
#define  addr_IICX2         (((void*)0xFFFFFDA5))
#define  addr_IICS2         (((void*)0xFFFFFDA6))
 
#define  addr_IICF2         (((void*)0xFFFFFDAA))
 
#define  addr_EXIMC         (((void*)0xFFFFFFBE))


#if 0 == D_USE_COMILER_REG_MAP

#define PM6H6		 (((__IO_REG8_BIT*)(addr_PM6H))->no6)
#define P6H6			 (((__IO_REG8_BIT*)(addr_P6H))->no6)
#define PMC6H6		 (((__IO_REG8_BIT*)(addr_PMC6H))->no6)

#define  PDL                (*((__IO_REG16*)addr_PDL))
#define  PDLL               (*((__IO_REG8*) addr_PDLL))
#define  PDLH               (*((__IO_REG8*) addr_PDLH))
#define  PDH                (*((__IO_REG8*) addr_PDH))
#define  PCS                (*((__IO_REG8*) addr_PCS))
#define  PCT                (*((__IO_REG8*) addr_PCT))
#define  PCM                (*((__IO_REG8*) addr_PCM))
#define  PCD                (*((__IO_REG8*) addr_PCD))

#define  PMDL               (*((__IO_REG16*)addr_PMDL))
#define  PMDLL              (*((__IO_REG8*) addr_PMDLL))
#define  PMDLH              (*((__IO_REG8*) addr_PMDLH))
#define  PMDH               (*((__IO_REG8*) addr_PMDH))
#define  PMCS               (*((__IO_REG8*) addr_PMCS))
#define  PMCT               (*((__IO_REG8*) addr_PMCT))
#define  PMCM               (*((__IO_REG8*) addr_PMCM))
#define  PMCD               (*((__IO_REG8*) addr_PMCD))

#define  PMCDL              (*((__IO_REG16*)addr_PMCDL))
#define  PMCDLL             (*((__IO_REG8*) addr_PMCDLL))
#define  PMCDLH             (*((__IO_REG8*) addr_PMCDLH))
#define  PMCDH              (*((__IO_REG8*) addr_PMCDH))
#define  PMCCS              (*((__IO_REG8*) addr_PMCCS))
#define  PMCCT              (*((__IO_REG8*) addr_PMCCT))
#define  PMCCM              (*((__IO_REG8*) addr_PMCCM))

#define  BPC                (*((__IO_REG16*)addr_BPC))
#define  BSC                (*((__IO_REG16*)addr_BSC))

#define  VSWC               (*((__IO_REG8*) addr_VSWC))

#define  DSA0L              (*((__IO_REG16*)addr_DSA0L))
#define  DSA0H              (*((__IO_REG16*)addr_DSA0H))
#define  DDA0L              (*((__IO_REG16*)addr_DDA0L))
#define  DDA0H              (*((__IO_REG16*)addr_DDA0H))
#define  DSA1L              (*((__IO_REG16*)addr_DSA1L))
#define  DSA1H              (*((__IO_REG16*)addr_DSA1H))
#define  DDA1L              (*((__IO_REG16*)addr_DDA1L))
#define  DDA1H              (*((__IO_REG16*)addr_DDA1H))
#define  DSA2L              (*((__IO_REG16*)addr_DSA2L))
#define  DSA2H              (*((__IO_REG16*)addr_DSA2H))
#define  DDA2L              (*((__IO_REG16*)addr_DDA2L))
#define  DDA2H              (*((__IO_REG16*)addr_DDA2H))
#define  DSA3L              (*((__IO_REG16*)addr_DSA3L))
#define  DSA3H              (*((__IO_REG16*)addr_DSA3H))
#define  DDA3L              (*((__IO_REG16*)addr_DDA3L))
#define  DDA3H              (*((__IO_REG16*)addr_DDA3H))

#define  DBC0               (*((__IO_REG16*)addr_DBC0))
#define  DBC1               (*((__IO_REG16*)addr_DBC1))
#define  DBC2               (*((__IO_REG16*)addr_DBC2))
#define  DBC3               (*((__IO_REG16*)addr_DBC3))

#define  DADC0              (*((__IO_REG16*)addr_DADC0))
#define  DADC1              (*((__IO_REG16*)addr_DADC1))
#define  DADC2              (*((__IO_REG16*)addr_DADC2))
#define  DADC3              (*((__IO_REG16*)addr_DADC3))

#define  DCHC0              (*((__IO_REG8*) addr_DCHC0))
#define  DCHC1              (*((__IO_REG8*) addr_DCHC1))
#define  DCHC2              (*((__IO_REG8*) addr_DCHC2))
#define  DCHC3              (*((__IO_REG8*) addr_DCHC3))

#define  IMR0               (*((__IO_REG16*)addr_IMR0))
#define  IMR0L              (*((__IO_REG8*) addr_IMR0L))
#define  IMR0H              (*((__IO_REG8*) addr_IMR0H))
#define  IMR1               (*((__IO_REG16*)addr_IMR1))
#define  IMR1L              (*((__IO_REG8*) addr_IMR1L))
#define  IMR1H              (*((__IO_REG8*) addr_IMR1H))
#define  IMR2               (*((__IO_REG16*)addr_IMR2))
#define  IMR2L              (*((__IO_REG8*) addr_IMR2L))
#define  IMR2H              (*((__IO_REG8*) addr_IMR2H))
#define  IMR3               (*((__IO_REG16*)addr_IMR3))
#define  IMR3L              (*((__IO_REG8*) addr_IMR3L))
#define  IMR3H              (*((__IO_REG8*) addr_IMR3H))
#define  IMR4               (*((__IO_REG16*)addr_IMR4))
#define  IMR4L              (*((__IO_REG8*) addr_IMR4L))
#define  IMR4H              (*((__IO_REG8*) addr_IMR4H))

#define  LVIIC              (*((__IO_REG8*) addr_LVIIC))
#define  PIC0               (*((__IO_REG8*) addr_PIC0))
#define  PIC1               (*((__IO_REG8*) addr_PIC1))
#define  PIC2               (*((__IO_REG8*) addr_PIC2))
#define  PIC3               (*((__IO_REG8*) addr_PIC3))
#define  PIC4               (*((__IO_REG8*) addr_PIC4))
#define  PIC5               (*((__IO_REG8*) addr_PIC5))
#define  PIC6               (*((__IO_REG8*) addr_PIC6))
#define  PIC7               (*((__IO_REG8*) addr_PIC7))
#define  TQ0OVIC            (*((__IO_REG8*) addr_TQ0OVIC))
#define  TQ0CCIC0           (*((__IO_REG8*) addr_TQ0CCIC0))
#define  TQ0CCIC1           (*((__IO_REG8*) addr_TQ0CCIC1))
#define  TQ0CCIC2           (*((__IO_REG8*) addr_TQ0CCIC2))
#define  TQ0CCIC3           (*((__IO_REG8*) addr_TQ0CCIC3))
#define  TP0OVIC            (*((__IO_REG8*) addr_TP0OVIC))
#define  TP0CCIC0           (*((__IO_REG8*) addr_TP0CCIC0))
#define  TP0CCIC1           (*((__IO_REG8*) addr_TP0CCIC1))
#define  TP1OVIC            (*((__IO_REG8*) addr_TP1OVIC))
#define  TP1CCIC0           (*((__IO_REG8*) addr_TP1CCIC0))
#define  TP1CCIC1           (*((__IO_REG8*) addr_TP1CCIC1))
#define  TP2OVIC            (*((__IO_REG8*) addr_TP2OVIC))
#define  TP2CCIC0           (*((__IO_REG8*) addr_TP2CCIC0))
#define  TP2CCIC1           (*((__IO_REG8*) addr_TP2CCIC1))
#define  TP3OVIC            (*((__IO_REG8*) addr_TP3OVIC))
#define  TP3CCIC0           (*((__IO_REG8*) addr_TP3CCIC0))
#define  TP3CCIC1           (*((__IO_REG8*) addr_TP3CCIC1))
#define  TP4OVIC            (*((__IO_REG8*) addr_TP4OVIC))
#define  TP4CCIC0           (*((__IO_REG8*) addr_TP4CCIC0))
#define  TP4CCIC1           (*((__IO_REG8*) addr_TP4CCIC1))
#define  TP5OVIC            (*((__IO_REG8*) addr_TP5OVIC))
#define  TP5CCIC0           (*((__IO_REG8*) addr_TP5CCIC0))
#define  TP5CCIC1           (*((__IO_REG8*) addr_TP5CCIC1))
#define  TM0EQIC0           (*((__IO_REG8*) addr_TM0EQIC0))
#define  CB0RIC             (*((__IO_REG8*) addr_CB0RIC))
#define  IICIC1             (*((__IO_REG8*) addr_IICIC1))
#define  CB0TIC             (*((__IO_REG8*) addr_CB0TIC))
#define  CB1RIC             (*((__IO_REG8*) addr_CB1RIC))
#define  CB1TIC             (*((__IO_REG8*) addr_CB1TIC))
#define  CB2RIC             (*((__IO_REG8*) addr_CB2RIC))
#define  CB2TIC             (*((__IO_REG8*) addr_CB2TIC))
#define  CB3RIC             (*((__IO_REG8*) addr_CB3RIC))
#define  CB3TIC             (*((__IO_REG8*) addr_CB3TIC))
#define  CB4RIC             (*((__IO_REG8*) addr_CB4RIC))
#define  UA0RIC             (*((__IO_REG8*) addr_UA0RIC))
#define  CB4TIC             (*((__IO_REG8*) addr_CB4TIC))
#define  UA0TIC             (*((__IO_REG8*) addr_UA0TIC))
#define  IICIC2             (*((__IO_REG8*) addr_IICIC2))
#define  UA1RIC             (*((__IO_REG8*) addr_UA1RIC))
#define  UA1TIC             (*((__IO_REG8*) addr_UA1TIC))
#define  IICIC0             (*((__IO_REG8*) addr_IICIC0))
#define  UA2RIC             (*((__IO_REG8*) addr_UA2RIC))
#define  UA2TIC             (*((__IO_REG8*) addr_UA2TIC))
#define  ADIC               (*((__IO_REG8*) addr_ADIC))
#define  DMAIC0             (*((__IO_REG8*) addr_DMAIC0))
#define  DMAIC1             (*((__IO_REG8*) addr_DMAIC1))
#define  DMAIC2             (*((__IO_REG8*) addr_DMAIC2))
#define  DMAIC3             (*((__IO_REG8*) addr_DMAIC3))
#define  KRIC               (*((__IO_REG8*) addr_KRIC))
#define  WTIIC              (*((__IO_REG8*) addr_WTIIC))
#define  WTIC               (*((__IO_REG8*) addr_WTIC))
#define  ERRIC              (*((__IO_REG8*) addr_ERRIC))
#define  ERRIC0             (*((__IO_REG8*) addr_ERRIC0))
#define  STAIC              (*((__IO_REG8*) addr_STAIC))
#define  WUPIC0             (*((__IO_REG8*) addr_WUPIC0))
#define  IEIC1              (*((__IO_REG8*) addr_IEIC1))
#define  RECIC0             (*((__IO_REG8*) addr_RECIC0))
#define  IEIC2              (*((__IO_REG8*) addr_IEIC2))
#define  TRXIC0             (*((__IO_REG8*) addr_TRXIC0))
#define  ERRIC1             (*((__IO_REG8*) addr_ERRIC1))
#define  WUPIC1             (*((__IO_REG8*) addr_WUPIC1))
#define  RECIC1             (*((__IO_REG8*) addr_RECIC1))
#define  TRXIC1             (*((__IO_REG8*) addr_TRXIC1))
#define  PIC8               (*((__IO_REG8*) addr_PIC8))
#define  TP6OVIC            (*((__IO_REG8*) addr_TP6OVIC))
#define  TP6CCIC0           (*((__IO_REG8*) addr_TP6CCIC0))
#define  TP6CCIC1           (*((__IO_REG8*) addr_TP6CCIC1))
#define  TP7OVIC            (*((__IO_REG8*) addr_TP7OVIC))
#define  TP7CCIC0           (*((__IO_REG8*) addr_TP7CCIC0))
#define  TP7CCIC1           (*((__IO_REG8*) addr_TP7CCIC1))
#define  TP8OVIC            (*((__IO_REG8*) addr_TP8OVIC))
#define  TP8CCIC0           (*((__IO_REG8*) addr_TP8CCIC0))
#define  TP8CCIC1           (*((__IO_REG8*) addr_TP8CCIC1))
#define  CB5RIC             (*((__IO_REG8*) addr_CB5RIC))
#define  CB5TIC             (*((__IO_REG8*) addr_CB5TIC))
#define  UA3RIC             (*((__IO_REG8*) addr_UA3RIC))
#define  UA3TIC             (*((__IO_REG8*) addr_UA3TIC))

#define  ISPR               (*((__IO_REG8*) addr_ISPR))
#define  PRCMD              (*((__IO_REG8*) addr_PRCMD))
#define  PSC                (*((__IO_REG8*) addr_PSC))
#define  ADA0M0             (*((__IO_REG8*) addr_ADA0M0))
#define  ADA0M1             (*((__IO_REG8*) addr_ADA0M1))
#define  ADA0S              (*((__IO_REG8*) addr_ADA0S))
#define  ADA0M2             (*((__IO_REG8*) addr_ADA0M2))
#define  ADA0PFM            (*((__IO_REG8*) addr_ADA0PFM))
#define  ADA0PFT            (*((__IO_REG8*) addr_ADA0PFT))

#define  ADA0CR0            (*((__IO_REG16*)addr_ADA0CR0))
#define  ADA0CR0H           (*((__IO_REG8*) addr_ADA0CR0H))
#define  ADA0CR1            (*((__IO_REG16*)addr_ADA0CR1))
#define  ADA0CR1H           (*((__IO_REG8*) addr_ADA0CR1H))
#define  ADA0CR2            (*((__IO_REG16*)addr_ADA0CR2))
#define  ADA0CR2H           (*((__IO_REG8*) addr_ADA0CR2H))
#define  ADA0CR3            (*((__IO_REG16*)addr_ADA0CR3))
#define  ADA0CR3H           (*((__IO_REG8*) addr_ADA0CR3H))
#define  ADA0CR4            (*((__IO_REG16*)addr_ADA0CR4))
#define  ADA0CR4H           (*((__IO_REG8*) addr_ADA0CR4H))
#define  ADA0CR5            (*((__IO_REG16*)addr_ADA0CR5))
#define  ADA0CR5H           (*((__IO_REG8*) addr_ADA0CR5H))
#define  ADA0CR6            (*((__IO_REG16*)addr_ADA0CR6))
#define  ADA0CR6H           (*((__IO_REG8*) addr_ADA0CR6H))
#define  ADA0CR7            (*((__IO_REG16*)addr_ADA0CR7))
#define  ADA0CR7H           (*((__IO_REG8*) addr_ADA0CR7H))
#define  ADA0CR8            (*((__IO_REG16*)addr_ADA0CR8))
#define  ADA0CR8H           (*((__IO_REG8*) addr_ADA0CR8H))
#define  ADA0CR9            (*((__IO_REG16*)addr_ADA0CR9))
#define  ADA0CR9H           (*((__IO_REG8*) addr_ADA0CR9H))
#define  ADA0CR10           (*((__IO_REG16*)addr_ADA0CR10))
#define  ADA0CR10H          (*((__IO_REG8*) addr_ADA0CR10H))
#define  ADA0CR11           (*((__IO_REG16*)addr_ADA0CR11))
#define  ADA0CR11H          (*((__IO_REG8*) addr_ADA0CR11H))
#define  ADA0CR12           (*((__IO_REG16*)addr_ADA0CR12))
#define  ADA0CR12H          (*((__IO_REG8*) addr_ADA0CR12H))
#define  ADA0CR13           (*((__IO_REG16*)addr_ADA0CR13))
#define  ADA0CR13H          (*((__IO_REG8*) addr_ADA0CR13H))
#define  ADA0CR14           (*((__IO_REG16*)addr_ADA0CR14))
#define  ADA0CR14H          (*((__IO_REG8*) addr_ADA0CR14H))
#define  ADA0CR15           (*((__IO_REG16*)addr_ADA0CR15))
#define  ADA0CR15H          (*((__IO_REG8*) addr_ADA0CR15H))

#define  DA0CS0             (*((__IO_REG8*) addr_DA0CS0))
#define  DA0CS1             (*((__IO_REG8*) addr_DA0CS1))
#define  DA0M               (*((__IO_REG8*) addr_DA0M))

#define  KRM                (*((__IO_REG8*) addr_KRM))

#define  SELCNT0            (*((__IO_REG8*) addr_SELCNT0))

#define  CRCIN              (*((__IO_REG8*) addr_CRCIN))
#define  CRCD               (*((__IO_REG16*)addr_CRCD))

#define  NFC                (*((__IO_REG8*) addr_NFC))

#define  PRSM1              (*((__IO_REG8*) addr_PRSM1))
#define  PRSCM1             (*((__IO_REG8*) addr_PRSCM1))

#define  PRSM2              (*((__IO_REG8*) addr_PRSM2))
#define  PRSCM2             (*((__IO_REG8*) addr_PRSCM2))

#define  PRSM3              (*((__IO_REG8*) addr_PRSM3))
#define  PRSCM3             (*((__IO_REG8*) addr_PRSCM3))

#define  OCKS0              (*((__IO_REG8*) addr_OCKS0))

#define  OCKS1              (*((__IO_REG8*) addr_OCKS1))

#define  OCKS2              (*((__IO_REG8*) addr_OCKS2))

#define  BCR                (*((__IO_REG8*) addr_BCR))
#define  PSR                (*((__IO_REG8*) addr_PSR))
#define  SSR                (*((__IO_REG8*) addr_SSR))
#define  USR                (*((__IO_REG8*) addr_USR))
#define  ISR                (*((__IO_REG8*) addr_ISR))
#define  ESR                (*((__IO_REG8*) addr_ESR))
#define  UAR                (*((__IO_REG16*)addr_UAR))
#define  SAR                (*((__IO_REG16*)addr_SAR))
#define  PAR                (*((__IO_REG16*)addr_PAR))
#define  RSA                (*((__IO_REG16*)addr_RSA))
#define  CDR                (*((__IO_REG8*) addr_CDR))
#define  DLR                (*((__IO_REG8*) addr_DLR))
#define  DR                 (*((__IO_REG8*) addr_DR))
#define  FSR                (*((__IO_REG8*) addr_FSR))
#define  SCR                (*((__IO_REG8*) addr_SCR))
#define  CCR                (*((__IO_REG8*) addr_CCR))

#define  P0                 (*((__IO_REG8*) addr_P0))
#define  P1                 (*((__IO_REG8*) addr_P1))

#define  P3                 (*((__IO_REG16*)addr_P3))
#define  P3L                (*((__IO_REG8*) addr_P3L))
#define  P3H                (*((__IO_REG8*) addr_P3H))
#define  P4                 (*((__IO_REG8*) addr_P4))
#define  P5                 (*((__IO_REG8*) addr_P5))
#define  P6                 (*((__IO_REG16*)addr_P6))
#define  P6L                (*((__IO_REG8*) addr_P6L))
#define  P6H                (*((__IO_REG8*) addr_P6H))
#define  P7L                (*((__IO_REG8*) addr_P7L))
#define  P7H                (*((__IO_REG8*) addr_P7H))
#define  P8                 (*((__IO_REG8*) addr_P8))
#define  P9                 (*((__IO_REG16*)addr_P9))
#define  P9L                (*((__IO_REG8*) addr_P9L))
#define  P9H                (*((__IO_REG8*) addr_P9H))

#define  PM0                (*((__IO_REG8*) addr_PM0))
#define  PM1                (*((__IO_REG8*) addr_PM1))

#define  PM3                (*((__IO_REG16*)addr_PM3))
#define  PM3L               (*((__IO_REG8*) addr_PM3L))
#define  PM3H               (*((__IO_REG8*) addr_PM3H))
#define  PM4                (*((__IO_REG8*) addr_PM4))
#define  PM5                (*((__IO_REG8*) addr_PM5))
#define  PM6                (*((__IO_REG16*)addr_PM6))
#define  PM6L               (*((__IO_REG8*) addr_PM6L))
#define  PM6H               (*((__IO_REG8*) addr_PM6H))
#define  PM7                (*((__IO_REG16*) addr_PM7L))
#define  PM7L               (*((__IO_REG8*) addr_PM7L))
#define  PM7H               (*((__IO_REG8*) addr_PM7H))
#define  PM8                (*((__IO_REG8*) addr_PM8))
#define  PM9                (*((__IO_REG16*)addr_PM9))
#define  PM9L               (*((__IO_REG8*) addr_PM9L))
#define  PM9H               (*((__IO_REG8*) addr_PM9H))

#define  PMC0               (*((__IO_REG8*) addr_PMC0))

#define  PMC3               (*((__IO_REG16*)addr_PMC3))
#define  PMC3L              (*((__IO_REG8*) addr_PMC3L))
#define  PMC3H              (*((__IO_REG8*) addr_PMC3H))
#define  PMC4               (*((__IO_REG8*) addr_PMC4))
#define  PMC5               (*((__IO_REG8*) addr_PMC5))
#define  PMC6               (*((__IO_REG16*)addr_PMC6))
#define  PMC6L              (*((__IO_REG8*) addr_PMC6L))
#define  PMC6H              (*((__IO_REG8*) addr_PMC6H))

#define  PMC8               (*((__IO_REG8*) addr_PMC8))
#define  PMC9               (*((__IO_REG16*)addr_PMC9))
#define  PMC9L              (*((__IO_REG8*) addr_PMC9L))
#define  PMC9H              (*((__IO_REG8*) addr_PMC9H))

#define  PFC0               (*((__IO_REG8*) addr_PFC0))

#define  PFC3               (*((__IO_REG16*)addr_PFC3))
#define  PFC3L              (*((__IO_REG8*) addr_PFC3L))
#define  PFC3H              (*((__IO_REG8*) addr_PFC3H))
#define  PFC4               (*((__IO_REG8*) addr_PFC4))
#define  PFC5               (*((__IO_REG8*) addr_PFC5))

#define  PFC6H              (*((__IO_REG8*) addr_PFC6H))

#define  PFC9               (*((__IO_REG16*)addr_PFC9))
#define  PFC9L              (*((__IO_REG8*) addr_PFC9L))
#define  PFC9H              (*((__IO_REG8*) addr_PFC9H))

#define  DWC0               (*((__IO_REG16*)addr_DWC0))

#define  AWC                (*((__IO_REG16*)addr_AWC))
#define  BCC                (*((__IO_REG16*)addr_BCC))

#define  TQ0CTL0            (*((__IO_REG8*) addr_TQ0CTL0))
#define  TQ0CTL1            (*((__IO_REG8*) addr_TQ0CTL1))
#define  TQ0IOC0            (*((__IO_REG8*) addr_TQ0IOC0))
#define  TQ0IOC1            (*((__IO_REG8*) addr_TQ0IOC1))
#define  TQ0IOC2            (*((__IO_REG8*) addr_TQ0IOC2))
#define  TQ0OPT0            (*((__IO_REG8*) addr_TQ0OPT0))
#define  TQ0CCR0            (*((__IO_REG16*)addr_TQ0CCR0))
#define  TQ0CCR1            (*((__IO_REG16*)addr_TQ0CCR1))
#define  TQ0CCR2            (*((__IO_REG16*)addr_TQ0CCR2))
#define  TQ0CCR3            (*((__IO_REG16*)addr_TQ0CCR3))
#define  TQ0CNT             (*((__IO_REG16*)addr_TQ0CNT))

#define  TP0CTL0            (*((__IO_REG8*) addr_TP0CTL0))
#define  TP0CTL1            (*((__IO_REG8*) addr_TP0CTL1))
#define  TP0IOC0            (*((__IO_REG8*) addr_TP0IOC0))
#define  TP0IOC1            (*((__IO_REG8*) addr_TP0IOC1))
#define  TP0IOC2            (*((__IO_REG8*) addr_TP0IOC2))
#define  TP0OPT0            (*((__IO_REG8*) addr_TP0OPT0))
#define  TP0CCR0            (*((__IO_REG16*)addr_TP0CCR0))
#define  TP0CCR1            (*((__IO_REG16*)addr_TP0CCR1))
#define  TP0CNT             (*((__IO_REG16*)addr_TP0CNT))

#define  TP1CTL0            (*((__IO_REG8*) addr_TP1CTL0))
#define  TP1CTL1            (*((__IO_REG8*) addr_TP1CTL1))
#define  TP1IOC0            (*((__IO_REG8*) addr_TP1IOC0))
#define  TP1IOC1            (*((__IO_REG8*) addr_TP1IOC1))
#define  TP1IOC2            (*((__IO_REG8*) addr_TP1IOC2))
#define  TP1OPT0            (*((__IO_REG8*) addr_TP1OPT0))
#define  TP1CCR0            (*((__IO_REG16*)addr_TP1CCR0))
#define  TP1CCR1            (*((__IO_REG16*)addr_TP1CCR1))
#define  TP1CNT             (*((__IO_REG16*)addr_TP1CNT))

#define  TP2CTL0            (*((__IO_REG8*) addr_TP2CTL0))
#define  TP2CTL1            (*((__IO_REG8*) addr_TP2CTL1))
#define  TP2IOC0            (*((__IO_REG8*) addr_TP2IOC0))
#define  TP2IOC1            (*((__IO_REG8*) addr_TP2IOC1))
#define  TP2IOC2            (*((__IO_REG8*) addr_TP2IOC2))
#define  TP2OPT0            (*((__IO_REG8*) addr_TP2OPT0))
#define  TP2CCR0            (*((__IO_REG16*)addr_TP2CCR0))
#define  TP2CCR1            (*((__IO_REG16*)addr_TP2CCR1))
#define  TP2CNT             (*((__IO_REG16*)addr_TP2CNT))

#define  TP3CTL0            (*((__IO_REG8*) addr_TP3CTL0))
#define  TP3CTL1            (*((__IO_REG8*) addr_TP3CTL1))
#define  TP3IOC0            (*((__IO_REG8*) addr_TP3IOC0))
#define  TP3IOC1            (*((__IO_REG8*) addr_TP3IOC1))
#define  TP3IOC2            (*((__IO_REG8*) addr_TP3IOC2))
#define  TP3OPT0            (*((__IO_REG8*) addr_TP3OPT0))
#define  TP3CCR0            (*((__IO_REG16*)addr_TP3CCR0))
#define  TP3CCR1            (*((__IO_REG16*)addr_TP3CCR1))
#define  TP3CNT             (*((__IO_REG16*)addr_TP3CNT))

#define  TP4CTL0            (*((__IO_REG8*) addr_TP4CTL0))
#define  TP4CTL1            (*((__IO_REG8*) addr_TP4CTL1))
#define  TP4IOC0            (*((__IO_REG8*) addr_TP4IOC0))
#define  TP4IOC1            (*((__IO_REG8*) addr_TP4IOC1))
#define  TP4IOC2            (*((__IO_REG8*) addr_TP4IOC2))
#define  TP4OPT0            (*((__IO_REG8*) addr_TP4OPT0))
#define  TP4CCR0            (*((__IO_REG16*)addr_TP4CCR0))
#define  TP4CCR1            (*((__IO_REG16*)addr_TP4CCR1))
#define  TP4CNT             (*((__IO_REG16*)addr_TP4CNT))

#define  TP5CTL0            (*((__IO_REG8*) addr_TP5CTL0))
#define  TP5CTL1            (*((__IO_REG8*) addr_TP5CTL1))
#define  TP5IOC0            (*((__IO_REG8*) addr_TP5IOC0))
#define  TP5IOC1            (*((__IO_REG8*) addr_TP5IOC1))
#define  TP5IOC2            (*((__IO_REG8*) addr_TP5IOC2))
#define  TP5OPT0            (*((__IO_REG8*) addr_TP5OPT0))
#define  TP5CCR0            (*((__IO_REG16*)addr_TP5CCR0))
#define  TP5CCR1            (*((__IO_REG16*)addr_TP5CCR1))
#define  TP5CNT             (*((__IO_REG16*)addr_TP5CNT))

#define  TP6CTL0            (*((__IO_REG8*) addr_TP6CTL0))
#define  TP6CTL1            (*((__IO_REG8*) addr_TP6CTL1))
#define  TP6IOC0            (*((__IO_REG8*) addr_TP6IOC0))
#define  TP6IOC1            (*((__IO_REG8*) addr_TP6IOC1))
#define  TP6IOC2            (*((__IO_REG8*) addr_TP6IOC2))
#define  TP6OPT0            (*((__IO_REG8*) addr_TP6OPT0))
#define  TP6CCR0            (*((__IO_REG16*)addr_TP6CCR0))
#define  TP6CCR1            (*((__IO_REG16*)addr_TP6CCR1))
#define  TP6CNT             (*((__IO_REG16*)addr_TP6CNT))

#define  TP7CTL0            (*((__IO_REG8*) addr_TP7CTL0))
#define  TP7CTL1            (*((__IO_REG8*) addr_TP7CTL1))
#define  TP7IOC0            (*((__IO_REG8*) addr_TP7IOC0))
#define  TP7IOC1            (*((__IO_REG8*) addr_TP7IOC1))
#define  TP7IOC2            (*((__IO_REG8*) addr_TP7IOC2))
#define  TP7OPT0            (*((__IO_REG8*) addr_TP7OPT0))
#define  TP7CCR0            (*((__IO_REG16*)addr_TP7CCR0))
#define  TP7CCR1            (*((__IO_REG16*)addr_TP7CCR1))
#define  TP7CNT             (*((__IO_REG16*)addr_TP7CNT))

#define  TP8CTL0            (*((__IO_REG8*) addr_TP8CTL0))
#define  TP8CTL1            (*((__IO_REG8*) addr_TP8CTL1))
#define  TP8IOC0            (*((__IO_REG8*) addr_TP8IOC0))
#define  TP8IOC1            (*((__IO_REG8*) addr_TP8IOC1))
#define  TP8IOC2            (*((__IO_REG8*) addr_TP8IOC2))
#define  TP8OPT0            (*((__IO_REG8*) addr_TP8OPT0))
#define  TP8CCR0            (*((__IO_REG16*)addr_TP8CCR0))
#define  TP8CCR1            (*((__IO_REG16*)addr_TP8CCR1))
#define  TP8CNT             (*((__IO_REG16*)addr_TP8CNT))

#define  WTM                (*((__IO_REG8*) addr_WTM))

#define  TM0CTL0            (*((__IO_REG8*) addr_TM0CTL0))

#define  TM0CMP0            (*((__IO_REG16*)addr_TM0CMP0))

#define  OSTS               (*((__IO_REG8*) addr_OSTS))
#define  PLLS               (*((__IO_REG8*) addr_PLLS))

#define  WDTM2              (*((__IO_REG8*) addr_WDTM2))
#define  WDTE               (*((__IO_REG8*) addr_WDTE))

#define  RTBL0              (*((__IO_REG8*) addr_RTBL0))
#define  RTBH0              (*((__IO_REG8*) addr_RTBH0))
#define  RTPM0              (*((__IO_REG8*) addr_RTPM0))
#define  RTPC0              (*((__IO_REG8*) addr_RTPC0))

#define  RTBL1              (*((__IO_REG8*) addr_RTBL1))
#define  RTBH1              (*((__IO_REG8*) addr_RTBH1))
#define  RTPM1              (*((__IO_REG8*) addr_RTPM1))
#define  RTPC1              (*((__IO_REG8*) addr_RTPC1))

#define  PFCE3L             (*((__IO_REG8*) addr_PFCE3L))

#define  PFCE5              (*((__IO_REG8*) addr_PFCE5))

#define  PFCE9              (*((__IO_REG16*)addr_PFCE9))
#define  PFCE9L             (*((__IO_REG8*) addr_PFCE9L))
#define  PFCE9H             (*((__IO_REG8*) addr_PFCE9H))

#define  SYS                (*((__IO_REG8*) addr_SYS))

#define  RCM                (*((__IO_REG8*) addr_RCM))

#define  DTFR0              (*((__IO_REG8*) addr_DTFR0))
#define  DTFR1              (*((__IO_REG8*) addr_DTFR1))
#define  DTFR2              (*((__IO_REG8*) addr_DTFR2))
#define  DTFR3              (*((__IO_REG8*) addr_DTFR3))

#define  PSMR               (*((__IO_REG8*) addr_PSMR))
#define  CKC                (*((__IO_REG8*) addr_CKC))
#define  LOCKR              (*((__IO_REG8*) addr_LOCKR))

#define  PCC                (*((__IO_REG8*) addr_PCC))

#define  PLLCTL             (*((__IO_REG8*) addr_PLLCTL))
#define  CCLS               (*((__IO_REG8*) addr_CCLS))

#define  CORAD0             (*((__IO_REG32*)addr_CORAD0))
#define  CORAD0L            (*((__IO_REG16*)addr_CORAD0L))
#define  CORAD0H            (*((__IO_REG16*)addr_CORAD0H))
#define  CORAD1             (*((__IO_REG32*)addr_CORAD1))
#define  CORAD1L            (*((__IO_REG16*)addr_CORAD1L))
#define  CORAD1H            (*((__IO_REG16*)addr_CORAD1H))
#define  CORAD2             (*((__IO_REG32*)addr_CORAD2))
#define  CORAD2L            (*((__IO_REG16*)addr_CORAD2L))
#define  CORAD2H            (*((__IO_REG16*)addr_CORAD2H))
#define  CORAD3             (*((__IO_REG32*)addr_CORAD3))
#define  CORAD3L            (*((__IO_REG16*)addr_CORAD3L))
#define  CORAD3H            (*((__IO_REG16*)addr_CORAD3H))

#define  C0INTS            (*((__IO_REG16*)addr_C0INTS))
#define  C1INTS            (*((__IO_REG16*)addr_C1INTS))
#define  CLM                (*((__IO_REG8*) addr_CLM))

#define  CORCN              (*((__IO_REG8*) addr_CORCN))

#define  RESF               (*((__IO_REG8*) addr_RESF))

#define  LVIM               (*((__IO_REG8*) addr_LVIM))
#define  LVIS               (*((__IO_REG8*) addr_LVIS))
#define  RAMS               (*((__IO_REG8*) addr_RAMS))

#define  PRSM0              (*((__IO_REG8*) addr_PRSM0))
#define  PRSCM0             (*((__IO_REG8*) addr_PRSCM0))

#define  OCDM               (*((__IO_REG8*) addr_OCDM))
#define  PEMU1              (*((__IO_REG8*) addr_PEMU1))
#define  UA0CTL0            (*((__IO_REG8*) addr_UA0CTL0))
#define  UA0CTL1            (*((__IO_REG8*) addr_UA0CTL1))
#define  UA0CTL2            (*((__IO_REG8*) addr_UA0CTL2))
#define  UA0OPT0            (*((__IO_REG8*) addr_UA0OPT0))
#define  UA0STR             (*((__IO_REG8*) addr_UA0STR))
#define  UA0RX              (*((__IO_REG8*) addr_UA0RX))
#define  UA0TX              (*((__IO_REG8*) addr_UA0TX))

#define  UA1CTL0            (*((__IO_REG8*) addr_UA1CTL0))
#define  UA1CTL1            (*((__IO_REG8*) addr_UA1CTL1))
#define  UA1CTL2            (*((__IO_REG8*) addr_UA1CTL2))
#define  UA1OPT0            (*((__IO_REG8*) addr_UA1OPT0))
#define  UA1STR             (*((__IO_REG8*) addr_UA1STR))
#define  UA1RX              (*((__IO_REG8*) addr_UA1RX))
#define  UA1TX              (*((__IO_REG8*) addr_UA1TX))

#define  UA2CTL0            (*((__IO_REG8*) addr_UA2CTL0))
#define  UA2CTL1            (*((__IO_REG8*) addr_UA2CTL1))
#define  UA2CTL2            (*((__IO_REG8*) addr_UA2CTL2))
#define  UA2OPT0            (*((__IO_REG8*) addr_UA2OPT0))
#define  UA2STR             (*((__IO_REG8*) addr_UA2STR))
#define  UA2RX              (*((__IO_REG8*) addr_UA2RX))
#define  UA2TX              (*((__IO_REG8*) addr_UA2TX))

#define  UA3CTL0            (*((__IO_REG8*) addr_UA3CTL0))
#define  UA3CTL1            (*((__IO_REG8*) addr_UA3CTL1))
#define  UA3CTL2            (*((__IO_REG8*) addr_UA3CTL2))
#define  UA3OPT0            (*((__IO_REG8*) addr_UA3OPT0))
#define  UA3STR             (*((__IO_REG8*) addr_UA3STR))
#define  UA3RX              (*((__IO_REG8*) addr_UA3RX))
#define  UA3TX              (*((__IO_REG8*) addr_UA3TX))

#define  INTF0              (*((__IO_REG8*) addr_INTF0))

#define  INTF3              (*((__IO_REG8*) addr_INTF3))

#define  INTF8              (*((__IO_REG8*) addr_INTF8))

#define  INTF9H             (*((__IO_REG8*) addr_INTF9H))

#define  INTR0              (*((__IO_REG8*) addr_INTR0))

#define  INTR3              (*((__IO_REG8*) addr_INTR3))

#define  INTR8              (*((__IO_REG8*) addr_INTR8))

#define  INTR9H             (*((__IO_REG8*) addr_INTR9H))

#define  PF0                (*((__IO_REG8*) addr_PF0))

#define  PF3                (*((__IO_REG16*)addr_PF3))
#define  PF3L               (*((__IO_REG8*) addr_PF3L))
#define  PF3H               (*((__IO_REG8*) addr_PF3H))
#define  PF4                (*((__IO_REG8*) addr_PF4))
#define  PF5                (*((__IO_REG8*) addr_PF5))
#define  PF6                (*((__IO_REG16*)addr_PF6))
#define  PF6L               (*((__IO_REG8*) addr_PF6L))
#define  PF6H               (*((__IO_REG8*) addr_PF6H))

#define  PF8                (*((__IO_REG8*) addr_PF8))
#define  PF9                (*((__IO_REG16*)addr_PF9))
#define  PF9L               (*((__IO_REG8*) addr_PF9L))
#define  PF9H               (*((__IO_REG8*) addr_PF9H))

#define  PRDSELL            (*((__IO_REG16*)addr_PRDSELL))
#define  PRDSELH            (*((__IO_REG16*)addr_PRDSELH))

#define  CB0CTL0            (*((__IO_REG8*) addr_CB0CTL0))
#define  CB0CTL1            (*((__IO_REG8*) addr_CB0CTL1))
#define  CB0CTL2            (*((__IO_REG8*) addr_CB0CTL2))
#define  CB0STR             (*((__IO_REG8*) addr_CB0STR))
#define  CB0RX              (*((__IO_REG16*)addr_CB0RX))
#define  CB0RXL             (*((__IO_REG8*) addr_CB0RXL))
#define  CB0TX              (*((__IO_REG16*)addr_CB0TX))
#define  CB0TXL             (*((__IO_REG8*) addr_CB0TXL))

#define  CB1CTL0            (*((__IO_REG8*) addr_CB1CTL0))
#define  CB1CTL1            (*((__IO_REG8*) addr_CB1CTL1))
#define  CB1CTL2            (*((__IO_REG8*) addr_CB1CTL2))
#define  CB1STR             (*((__IO_REG8*) addr_CB1STR))
#define  CB1RX              (*((__IO_REG16*)addr_CB1RX))
#define  CB1RXL             (*((__IO_REG8*) addr_CB1RXL))
#define  CB1TX              (*((__IO_REG16*)addr_CB1TX))
#define  CB1TXL             (*((__IO_REG8*) addr_CB1TXL))

#define  CB2CTL0            (*((__IO_REG8*) addr_CB2CTL0))
#define  CB2CTL1            (*((__IO_REG8*) addr_CB2CTL1))
#define  CB2CTL2            (*((__IO_REG8*) addr_CB2CTL2))
#define  CB2STR             (*((__IO_REG8*) addr_CB2STR))
#define  CB2RX              (*((__IO_REG16*)addr_CB2RX))
#define  CB2RXL             (*((__IO_REG8*) addr_CB2RXL))
#define  CB2TX              (*((__IO_REG16*)addr_CB2TX))
#define  CB2TXL             (*((__IO_REG8*) addr_CB2TXL))

#define  CB3CTL0            (*((__IO_REG8*) addr_CB3CTL0))
#define  CB3CTL1            (*((__IO_REG8*) addr_CB3CTL1))
#define  CB3CTL2            (*((__IO_REG8*) addr_CB3CTL2))
#define  CB3STR             (*((__IO_REG8*) addr_CB3STR))
#define  CB3RX              (*((__IO_REG16*)addr_CB3RX))
#define  CB3RXL             (*((__IO_REG8*) addr_CB3RXL))
#define  CB3TX              (*((__IO_REG16*)addr_CB3TX))
#define  CB3TXL             (*((__IO_REG8*) addr_CB3TXL))

#define  CB4CTL0            (*((__IO_REG8*) addr_CB4CTL0))
#define  CB4CTL1            (*((__IO_REG8*) addr_CB4CTL1))
#define  CB4CTL2            (*((__IO_REG8*) addr_CB4CTL2))
#define  CB4STR             (*((__IO_REG8*) addr_CB4STR))
#define  CB4RX              (*((__IO_REG16*)addr_CB4RX))
#define  CB4RXL             (*((__IO_REG8*) addr_CB4RXL))
#define  CB4TX              (*((__IO_REG16*)addr_CB4TX))
#define  CB4TXL             (*((__IO_REG8*) addr_CB4TXL))

#define  CB5CTL0            (*((__IO_REG8*) addr_CB5CTL0))
#define  CB5CTL1            (*((__IO_REG8*) addr_CB5CTL1))
#define  CB5CTL2            (*((__IO_REG8*) addr_CB5CTL2))
#define  CB5STR             (*((__IO_REG8*) addr_CB5STR))
#define  CB5RX              (*((__IO_REG16*)addr_CB5RX))
#define  CB5RXL             (*((__IO_REG8*) addr_CB5RXL))
#define  CB5TX              (*((__IO_REG16*)addr_CB5TX))
#define  CB5TXL             (*((__IO_REG8*) addr_CB5TXL))

#define  IIC0               (*((__IO_REG8*) addr_IIC0))
#define  IICC0              (*((__IO_REG8*) addr_IICC0))
#define  SVA0               (*((__IO_REG8*) addr_SVA0))
#define  IICCL0             (*((__IO_REG8*) addr_IICCL0))
#define  IICX0              (*((__IO_REG8*) addr_IICX0))
#define  IICS0              (*((__IO_REG8*) addr_IICS0))

#define  IICF0              (*((__IO_REG8*) addr_IICF0))

#define  IIC1               (*((__IO_REG8*) addr_IIC1))
#define  IICC1              (*((__IO_REG8*) addr_IICC1))
#define  SVA1               (*((__IO_REG8*) addr_SVA1))
#define  IICCL1             (*((__IO_REG8*) addr_IICCL1))
#define  IICX1              (*((__IO_REG8*) addr_IICX1))
#define  IICS1              (*((__IO_REG8*) addr_IICS1))

#define  IICF1              (*((__IO_REG8*) addr_IICF1))

#define  IIC2               (*((__IO_REG8*) addr_IIC2))
#define  IICC2              (*((__IO_REG8*) addr_IICC2))
#define  SVA2               (*((__IO_REG8*) addr_SVA2))
#define  IICCL2             (*((__IO_REG8*) addr_IICCL2))
#define  IICX2              (*((__IO_REG8*) addr_IICX2))
#define  IICS2              (*((__IO_REG8*) addr_IICS2))

#define  IICF2              (*((__IO_REG8*) addr_IICF2))

#define  EXIMC              (*((__IO_REG8*) addr_EXIMC))


     

/***********************************************
 *       Peripheral I/O bit declarations
 ***********************************************/


#define E00                 (((__IO_REG8_BIT*)(addr_DCHC0))->no0)
#define STG0                (((__IO_REG8_BIT*)(addr_DCHC0))->no1)
#define INIT0               (((__IO_REG8_BIT*)(addr_DCHC0))->no2)
#define TC0                 (((__IO_REG8_BIT*)(addr_DCHC0))->no7)
 
#define E11                 (((__IO_REG8_BIT*)(addr_DCHC1))->no0)
#define STG1                (((__IO_REG8_BIT*)(addr_DCHC1))->no1)
#define INIT1               (((__IO_REG8_BIT*)(addr_DCHC1))->no2)
#define TC1                 (((__IO_REG8_BIT*)(addr_DCHC1))->no7)
 
#define E22                 (((__IO_REG8_BIT*)(addr_DCHC2))->no0)
#define STG2                (((__IO_REG8_BIT*)(addr_DCHC2))->no1)
#define INIT2               (((__IO_REG8_BIT*)(addr_DCHC2))->no2)
#define TC2                 (((__IO_REG8_BIT*)(addr_DCHC2))->no7)
 
#define E33                 (((__IO_REG8_BIT*)(addr_DCHC3))->no0)
#define STG3                (((__IO_REG8_BIT*)(addr_DCHC3))->no1)
#define INIT3               (((__IO_REG8_BIT*)(addr_DCHC3))->no2)
#define TC3                 (((__IO_REG8_BIT*)(addr_DCHC3))->no7)
 
#define LVIMK               (((__IO_REG8_BIT*)(addr_LVIIC))->no6)
#define LVIIF               (((__IO_REG8_BIT*)(addr_LVIIC))->no7)
 
#define PMK0                (((__IO_REG8_BIT*)(addr_PIC0))->no6)
#define PIF0                (((__IO_REG8_BIT*)(addr_PIC0))->no7)
 
#define PMK1                (((__IO_REG8_BIT*)(addr_PIC1))->no6)
#define PIF1                (((__IO_REG8_BIT*)(addr_PIC1))->no7)
 
#define PMK2                (((__IO_REG8_BIT*)(addr_PIC2))->no6)
#define PIF2                (((__IO_REG8_BIT*)(addr_PIC2))->no7)
 
#define PMK3                (((__IO_REG8_BIT*)(addr_PIC3))->no6)
#define PIF3                (((__IO_REG8_BIT*)(addr_PIC3))->no7)
 
#define PMK4                (((__IO_REG8_BIT*)(addr_PIC4))->no6)
#define PIF4                (((__IO_REG8_BIT*)(addr_PIC4))->no7)
 
#define PMK5                (((__IO_REG8_BIT*)(addr_PIC5))->no6)
#define PIF5                (((__IO_REG8_BIT*)(addr_PIC5))->no7)
 
#define PMK6                (((__IO_REG8_BIT*)(addr_PIC6))->no6)
#define PIF6                (((__IO_REG8_BIT*)(addr_PIC6))->no7)
 
#define PMK7                (((__IO_REG8_BIT*)(addr_PIC7))->no6)
#define PIF7                (((__IO_REG8_BIT*)(addr_PIC7))->no7)
 
#define TQ0OVMK             (((__IO_REG8_BIT*)(addr_TQ0OVIC))->no6)
#define TQ0OVIF             (((__IO_REG8_BIT*)(addr_TQ0OVIC))->no7)
 
#define TQ0CCMK0            (((__IO_REG8_BIT*)(addr_TQ0CCIC0))->no6)
#define TQ0CCIF0            (((__IO_REG8_BIT*)(addr_TQ0CCIC0))->no7)
 
#define TQ0CCMK1            (((__IO_REG8_BIT*)(addr_TQ0CCIC1))->no6)
#define TQ0CCIF1            (((__IO_REG8_BIT*)(addr_TQ0CCIC1))->no7)
 
#define TQ0CCMK2            (((__IO_REG8_BIT*)(addr_TQ0CCIC2))->no6)
#define TQ0CCIF2            (((__IO_REG8_BIT*)(addr_TQ0CCIC2))->no7)
 
#define TQ0CCMK3            (((__IO_REG8_BIT*)(addr_TQ0CCIC3))->no6)
#define TQ0CCIF3            (((__IO_REG8_BIT*)(addr_TQ0CCIC3))->no7)
 
#define TP0OVMK             (((__IO_REG8_BIT*)(addr_TP0OVIC))->no6)
#define TP0OVIF             (((__IO_REG8_BIT*)(addr_TP0OVIC))->no7)
 
#define TP0CCMK0            (((__IO_REG8_BIT*)(addr_TP0CCIC0))->no6)
#define TP0CCIF0            (((__IO_REG8_BIT*)(addr_TP0CCIC0))->no7)
 
#define TP0CCMK1            (((__IO_REG8_BIT*)(addr_TP0CCIC1))->no6)
#define TP0CCIF1            (((__IO_REG8_BIT*)(addr_TP0CCIC1))->no7)
 
#define TP1OVMK             (((__IO_REG8_BIT*)(addr_TP1OVIC))->no6)
#define TP1OVIF             (((__IO_REG8_BIT*)(addr_TP1OVIC))->no7)
 
#define TP1CCMK0            (((__IO_REG8_BIT*)(addr_TP1CCIC0))->no6)
#define TP1CCIF0            (((__IO_REG8_BIT*)(addr_TP1CCIC0))->no7)
 
#define TP1CCMK1            (((__IO_REG8_BIT*)(addr_TP1CCIC1))->no6)
#define TP1CCIF1            (((__IO_REG8_BIT*)(addr_TP1CCIC1))->no7)
 
#define TP2OVMK             (((__IO_REG8_BIT*)(addr_TP2OVIC))->no6)
#define TP2OVIF             (((__IO_REG8_BIT*)(addr_TP2OVIC))->no7)
 
#define TP2CCMK0            (((__IO_REG8_BIT*)(addr_TP2CCIC0))->no6)
#define TP2CCIF0            (((__IO_REG8_BIT*)(addr_TP2CCIC0))->no7)
 
#define TP2CCMK1            (((__IO_REG8_BIT*)(addr_TP2CCIC1))->no6)
#define TP2CCIF1            (((__IO_REG8_BIT*)(addr_TP2CCIC1))->no7)
 
#define TP3OVMK             (((__IO_REG8_BIT*)(addr_TP3OVIC))->no6)
#define TP3OVIF             (((__IO_REG8_BIT*)(addr_TP3OVIC))->no7)
 
#define TP3CCMK0            (((__IO_REG8_BIT*)(addr_TP3CCIC0))->no6)
#define TP3CCIF0            (((__IO_REG8_BIT*)(addr_TP3CCIC0))->no7)
 
#define TP3CCMK1            (((__IO_REG8_BIT*)(addr_TP3CCIC1))->no6)
#define TP3CCIF1            (((__IO_REG8_BIT*)(addr_TP3CCIC1))->no7)
 
#define TP4OVMK             (((__IO_REG8_BIT*)(addr_TP4OVIC))->no6)
#define TP4OVIF             (((__IO_REG8_BIT*)(addr_TP4OVIC))->no7)
 
#define TP4CCMK0            (((__IO_REG8_BIT*)(addr_TP4CCIC0))->no6)
#define TP4CCIF0            (((__IO_REG8_BIT*)(addr_TP4CCIC0))->no7)
 
#define TP4CCMK1            (((__IO_REG8_BIT*)(addr_TP4CCIC1))->no6)
#define TP4CCIF1            (((__IO_REG8_BIT*)(addr_TP4CCIC1))->no7)
 
#define TP5OVMK             (((__IO_REG8_BIT*)(addr_TP5OVIC))->no6)
#define TP5OVIF             (((__IO_REG8_BIT*)(addr_TP5OVIC))->no7)
 
#define TP5CCMK0            (((__IO_REG8_BIT*)(addr_TP5CCIC0))->no6)
#define TP5CCIF0            (((__IO_REG8_BIT*)(addr_TP5CCIC0))->no7)
 
#define TP5CCMK1            (((__IO_REG8_BIT*)(addr_TP5CCIC1))->no6)
#define TP5CCIF1            (((__IO_REG8_BIT*)(addr_TP5CCIC1))->no7)
 
#define TM0EQMK0            (((__IO_REG8_BIT*)(addr_TM0EQIC0))->no6)
#define TM0EQIF0            (((__IO_REG8_BIT*)(addr_TM0EQIC0))->no7)
 
#define CB0RMK              (((__IO_REG8_BIT*)(addr_IICIC1))->no6)
#define IICMK1              (((__IO_REG8_BIT*)(addr_IICIC1))->no6)
#define CB0RIF              (((__IO_REG8_BIT*)(addr_IICIC1))->no7)
#define IICIF1              (((__IO_REG8_BIT*)(addr_IICIC1))->no7)
 
#define CB0TMK              (((__IO_REG8_BIT*)(addr_CB0TIC))->no6)
#define CB0TIF              (((__IO_REG8_BIT*)(addr_CB0TIC))->no7)
 
#define CB1RMK              (((__IO_REG8_BIT*)(addr_CB1RIC))->no6)
#define CB1RIF              (((__IO_REG8_BIT*)(addr_CB1RIC))->no7)
 
#define CB1TMK              (((__IO_REG8_BIT*)(addr_CB1TIC))->no6)
#define CB1TIF              (((__IO_REG8_BIT*)(addr_CB1TIC))->no7)
 
#define CB2RMK              (((__IO_REG8_BIT*)(addr_CB2RIC))->no6)
#define CB2RIF              (((__IO_REG8_BIT*)(addr_CB2RIC))->no7)
 
#define CB2TMK              (((__IO_REG8_BIT*)(addr_CB2TIC))->no6)
#define CB2TIF              (((__IO_REG8_BIT*)(addr_CB2TIC))->no7)
 
#define CB3RMK              (((__IO_REG8_BIT*)(addr_CB3RIC))->no6)
#define CB3RIF              (((__IO_REG8_BIT*)(addr_CB3RIC))->no7)
 
#define CB3TMK              (((__IO_REG8_BIT*)(addr_CB3TIC))->no6)
#define CB3TIF              (((__IO_REG8_BIT*)(addr_CB3TIC))->no7)
 
#define CB4RMK              (((__IO_REG8_BIT*)(addr_UA0RIC))->no6)
#define UA0RMK              (((__IO_REG8_BIT*)(addr_UA0RIC))->no6)
#define CB4RIF              (((__IO_REG8_BIT*)(addr_UA0RIC))->no7)
#define UA0RIF              (((__IO_REG8_BIT*)(addr_UA0RIC))->no7)
 
#define CB4TMK              (((__IO_REG8_BIT*)(addr_UA0TIC))->no6)
#define UA0TMK              (((__IO_REG8_BIT*)(addr_UA0TIC))->no6)
#define CB4TIF              (((__IO_REG8_BIT*)(addr_UA0TIC))->no7)
#define UA0TIF              (((__IO_REG8_BIT*)(addr_UA0TIC))->no7)
 
#define IICMK2              (((__IO_REG8_BIT*)(addr_UA1RIC))->no6)
#define UA1RMK              (((__IO_REG8_BIT*)(addr_UA1RIC))->no6)
#define IICIF2              (((__IO_REG8_BIT*)(addr_UA1RIC))->no7)
#define UA1RIF              (((__IO_REG8_BIT*)(addr_UA1RIC))->no7)
 
#define UA1TMK              (((__IO_REG8_BIT*)(addr_UA1TIC))->no6)
#define UA1TIF              (((__IO_REG8_BIT*)(addr_UA1TIC))->no7)
 
#define IICMK0              (((__IO_REG8_BIT*)(addr_UA2RIC))->no6)
#define UA2RMK              (((__IO_REG8_BIT*)(addr_UA2RIC))->no6)
#define IICIF0              (((__IO_REG8_BIT*)(addr_UA2RIC))->no7)
#define UA2RIF              (((__IO_REG8_BIT*)(addr_UA2RIC))->no7)
 
#define UA2TMK              (((__IO_REG8_BIT*)(addr_UA2TIC))->no6)
#define UA2TIF              (((__IO_REG8_BIT*)(addr_UA2TIC))->no7)
 
#define ADMK                (((__IO_REG8_BIT*)(addr_ADIC))->no6)
#define ADIF                (((__IO_REG8_BIT*)(addr_ADIC))->no7)
 
#define DMAMK0              (((__IO_REG8_BIT*)(addr_DMAIC0))->no6)
#define DMAIF0              (((__IO_REG8_BIT*)(addr_DMAIC0))->no7)
 
#define DMAMK1              (((__IO_REG8_BIT*)(addr_DMAIC1))->no6)
#define DMAIF1              (((__IO_REG8_BIT*)(addr_DMAIC1))->no7)
 
#define DMAMK2              (((__IO_REG8_BIT*)(addr_DMAIC2))->no6)
#define DMAIF2              (((__IO_REG8_BIT*)(addr_DMAIC2))->no7)
 
#define DMAMK3              (((__IO_REG8_BIT*)(addr_DMAIC3))->no6)
#define DMAIF3              (((__IO_REG8_BIT*)(addr_DMAIC3))->no7)
 
#define KRMK                (((__IO_REG8_BIT*)(addr_KRIC))->no6)
#define KRIF                (((__IO_REG8_BIT*)(addr_KRIC))->no7)
 
#define WTIMK               (((__IO_REG8_BIT*)(addr_WTIIC))->no6)
#define WTIIF               (((__IO_REG8_BIT*)(addr_WTIIC))->no7)
 
#define WTMK                (((__IO_REG8_BIT*)(addr_WTIC))->no6)
#define WTIF                (((__IO_REG8_BIT*)(addr_WTIC))->no7)
 
#define ERRMK               (((__IO_REG8_BIT*)(addr_ERRIC0))->no6)
#define ERRMK0              (((__IO_REG8_BIT*)(addr_ERRIC0))->no6)
#define ERRIF               (((__IO_REG8_BIT*)(addr_ERRIC0))->no7)
#define ERRIF0              (((__IO_REG8_BIT*)(addr_ERRIC0))->no7)
 
#define STAMK               (((__IO_REG8_BIT*)(addr_WUPIC0))->no6)
#define WUPMK0              (((__IO_REG8_BIT*)(addr_WUPIC0))->no6)
#define STAIF               (((__IO_REG8_BIT*)(addr_WUPIC0))->no7)
#define WUPIF0              (((__IO_REG8_BIT*)(addr_WUPIC0))->no7)
 
#define IEMK1               (((__IO_REG8_BIT*)(addr_RECIC0))->no6)
#define RECMK0              (((__IO_REG8_BIT*)(addr_RECIC0))->no6)
#define IEIF1               (((__IO_REG8_BIT*)(addr_RECIC0))->no7)
#define RECIF0              (((__IO_REG8_BIT*)(addr_RECIC0))->no7)
 
#define IEMK2               (((__IO_REG8_BIT*)(addr_TRXIC0))->no6)
#define TRXMK0              (((__IO_REG8_BIT*)(addr_TRXIC0))->no6)
#define IEIF2               (((__IO_REG8_BIT*)(addr_TRXIC0))->no7)
#define TRXIF0              (((__IO_REG8_BIT*)(addr_TRXIC0))->no7)
 
#define ERRMK1              (((__IO_REG8_BIT*)(addr_ERRIC1))->no6)
#define ERRIF1              (((__IO_REG8_BIT*)(addr_ERRIC1))->no7)
 
#define WUPMK1              (((__IO_REG8_BIT*)(addr_WUPIC1))->no6)
#define WUPIF1              (((__IO_REG8_BIT*)(addr_WUPIC1))->no7)
 
#define RECMK1              (((__IO_REG8_BIT*)(addr_RECIC1))->no6)
#define RECIF1              (((__IO_REG8_BIT*)(addr_RECIC1))->no7)
 
#define TRXMK1              (((__IO_REG8_BIT*)(addr_TRXIC1))->no6)
#define TRXIF1              (((__IO_REG8_BIT*)(addr_TRXIC1))->no7)
 
#define PMK8                (((__IO_REG8_BIT*)(addr_PIC8))->no6)
#define PIF8                (((__IO_REG8_BIT*)(addr_PIC8))->no7)
 
#define TP6OVMK             (((__IO_REG8_BIT*)(addr_TP6OVIC))->no6)
#define TP6OVIF             (((__IO_REG8_BIT*)(addr_TP6OVIC))->no7)
 
#define TP6CCMK0            (((__IO_REG8_BIT*)(addr_TP6CCIC0))->no6)
#define TP6CCIF0            (((__IO_REG8_BIT*)(addr_TP6CCIC0))->no7)
 
#define TP6CCMK1            (((__IO_REG8_BIT*)(addr_TP6CCIC1))->no6)
#define TP6CCIF1            (((__IO_REG8_BIT*)(addr_TP6CCIC1))->no7)
 
#define TP7OVMK             (((__IO_REG8_BIT*)(addr_TP7OVIC))->no6)
#define TP7OVIF             (((__IO_REG8_BIT*)(addr_TP7OVIC))->no7)
 
#define TP7CCMK0            (((__IO_REG8_BIT*)(addr_TP7CCIC0))->no6)
#define TP7CCIF0            (((__IO_REG8_BIT*)(addr_TP7CCIC0))->no7)
 
#define TP7CCMK1            (((__IO_REG8_BIT*)(addr_TP7CCIC1))->no6)
#define TP7CCIF1            (((__IO_REG8_BIT*)(addr_TP7CCIC1))->no7)
 
#define TP8OVMK             (((__IO_REG8_BIT*)(addr_TP8OVIC))->no6)
#define TP8OVIF             (((__IO_REG8_BIT*)(addr_TP8OVIC))->no7)
 
#define TP8CCMK0            (((__IO_REG8_BIT*)(addr_TP8CCIC0))->no6)
#define TP8CCIF0            (((__IO_REG8_BIT*)(addr_TP8CCIC0))->no7)
 
#define TP8CCMK1            (((__IO_REG8_BIT*)(addr_TP8CCIC1))->no6)
#define TP8CCIF1            (((__IO_REG8_BIT*)(addr_TP8CCIC1))->no7)
 
#define CB5RMK              (((__IO_REG8_BIT*)(addr_CB5RIC))->no6)
#define CB5RIF              (((__IO_REG8_BIT*)(addr_CB5RIC))->no7)
 
#define CB5TMK              (((__IO_REG8_BIT*)(addr_CB5TIC))->no6)
#define CB5TIF              (((__IO_REG8_BIT*)(addr_CB5TIC))->no7)
 
#define UA3RMK              (((__IO_REG8_BIT*)(addr_UA3RIC))->no6)
#define UA3RIF              (((__IO_REG8_BIT*)(addr_UA3RIC))->no7)
 
#define UA3TMK              (((__IO_REG8_BIT*)(addr_UA3TIC))->no6)
#define UA3TIF              (((__IO_REG8_BIT*)(addr_UA3TIC))->no7)
 
#define ISPR0               (((__IO_REG8_BIT*)(addr_ISPR))->no0)
#define ISPR1               (((__IO_REG8_BIT*)(addr_ISPR))->no1)
#define ISPR2               (((__IO_REG8_BIT*)(addr_ISPR))->no2)
#define ISPR3               (((__IO_REG8_BIT*)(addr_ISPR))->no3)
#define ISPR4               (((__IO_REG8_BIT*)(addr_ISPR))->no4)
#define ISPR5               (((__IO_REG8_BIT*)(addr_ISPR))->no5)
#define ISPR6               (((__IO_REG8_BIT*)(addr_ISPR))->no6)
#define ISPR7               (((__IO_REG8_BIT*)(addr_ISPR))->no7)
 
#define STP                 (((__IO_REG8_BIT*)(addr_PSC))->no1)
#define INTM                (((__IO_REG8_BIT*)(addr_PSC))->no4)
#define NMI0M               (((__IO_REG8_BIT*)(addr_PSC))->no5)
#define NMI1M               (((__IO_REG8_BIT*)(addr_PSC))->no6)
 
#define ADA0EF              (((__IO_REG8_BIT*)(addr_ADA0M0))->no0)
#define ADA0CE              (((__IO_REG8_BIT*)(addr_ADA0M0))->no7)
 
#define ADA0PFE             (((__IO_REG8_BIT*)(addr_ADA0PFM))->no7)
 
#define DA0CE0              (((__IO_REG8_BIT*)(addr_DA0M))->no4)
#define DA0CE1              (((__IO_REG8_BIT*)(addr_DA0M))->no5)
 
#define ISEL0               (((__IO_REG8_BIT*)(addr_SELCNT0))->no0)
#define ISEL1               (((__IO_REG8_BIT*)(addr_SELCNT0))->no1)
#define ISEL3               (((__IO_REG8_BIT*)(addr_SELCNT0))->no3)
#define ISEL4               (((__IO_REG8_BIT*)(addr_SELCNT0))->no4)
#define ISEL6               (((__IO_REG8_BIT*)(addr_SELCNT0))->no6)
 
#define BGCE1               (((__IO_REG8_BIT*)(addr_PRSM1))->no4)
 
#define BGCE2               (((__IO_REG8_BIT*)(addr_PRSM2))->no4)
 
#define BGCE3               (((__IO_REG8_BIT*)(addr_PRSM3))->no4)
 
#define ENSLVRX             (((__IO_REG8_BIT*)(addr_BCR))->no3)
#define ENSLVTX             (((__IO_REG8_BIT*)(addr_BCR))->no4)
#define ALLRQ               (((__IO_REG8_BIT*)(addr_BCR))->no5)
#define MSTRQ               (((__IO_REG8_BIT*)(addr_BCR))->no6)
#define ENIEBUS             (((__IO_REG8_BIT*)(addr_BCR))->no7)
 
#define IEMODE              (((__IO_REG8_BIT*)(addr_PSR))->no6)
#define ENCLK               (((__IO_REG8_BIT*)(addr_PSR))->no7)
 
#define STATTX              (((__IO_REG8_BIT*)(addr_SSR))->no0)
#define STATRX              (((__IO_REG8_BIT*)(addr_SSR))->no1)
#define STATLOCK            (((__IO_REG8_BIT*)(addr_SSR))->no2)
#define STATSLV             (((__IO_REG8_BIT*)(addr_SSR))->no4)
 
#define ACKF                (((__IO_REG8_BIT*)(addr_USR))->no3)
#define ALLTRNS             (((__IO_REG8_BIT*)(addr_USR))->no4)
#define ARBIT               (((__IO_REG8_BIT*)(addr_USR))->no5)
#define SLVRQ               (((__IO_REG8_BIT*)(addr_USR))->no6)
 
#define ENDFRAM             (((__IO_REG8_BIT*)(addr_ISR))->no2)
#define ENDTRNS             (((__IO_REG8_BIT*)(addr_ISR))->no3)
#define STATUSF             (((__IO_REG8_BIT*)(addr_ISR))->no4)
#define STARTF              (((__IO_REG8_BIT*)(addr_ISR))->no5)
#define IEERR               (((__IO_REG8_BIT*)(addr_ISR))->no6)
 
#define DEFLAG              (((__IO_REG8_BIT*)(addr_ESR))->no0)
#define WERR                (((__IO_REG8_BIT*)(addr_ESR))->no2)
#define OERR                (((__IO_REG8_BIT*)(addr_ESR))->no3)
#define UERR                (((__IO_REG8_BIT*)(addr_ESR))->no4)
#define NERR                (((__IO_REG8_BIT*)(addr_ESR))->no5)
#define PERR                (((__IO_REG8_BIT*)(addr_ESR))->no6)
#define TERR                (((__IO_REG8_BIT*)(addr_ESR))->no7)
 
#define TQ0CE               (((__IO_REG8_BIT*)(addr_TQ0CTL0))->no7)
 
#define TQ0EEE              (((__IO_REG8_BIT*)(addr_TQ0CTL1))->no5)
#define TQ0EST              (((__IO_REG8_BIT*)(addr_TQ0CTL1))->no6)
 
#define TQ0OE0              (((__IO_REG8_BIT*)(addr_TQ0IOC0))->no0)
#define TQ0OE1              (((__IO_REG8_BIT*)(addr_TQ0IOC0))->no2)
#define TQ0OE2              (((__IO_REG8_BIT*)(addr_TQ0IOC0))->no4)
#define TQ0OE3              (((__IO_REG8_BIT*)(addr_TQ0IOC0))->no6)
 
#define TQ0OVF              (((__IO_REG8_BIT*)(addr_TQ0OPT0))->no0)
 
#define TP0CE               (((__IO_REG8_BIT*)(addr_TP0CTL0))->no7)
 
#define TP0EEE              (((__IO_REG8_BIT*)(addr_TP0CTL1))->no5)
#define TP0EST              (((__IO_REG8_BIT*)(addr_TP0CTL1))->no6)
 
#define TP0OE0              (((__IO_REG8_BIT*)(addr_TP0IOC0))->no0)
#define TP0OE1              (((__IO_REG8_BIT*)(addr_TP0IOC0))->no2)
 
#define TP0OVF              (((__IO_REG8_BIT*)(addr_TP0OPT0))->no0)
 
#define TP1CE               (((__IO_REG8_BIT*)(addr_TP1CTL0))->no7)
 
#define TP1EEE              (((__IO_REG8_BIT*)(addr_TP1CTL1))->no5)
#define TP1EST              (((__IO_REG8_BIT*)(addr_TP1CTL1))->no6)
 
#define TP1OE0              (((__IO_REG8_BIT*)(addr_TP1IOC0))->no0)
#define TP1OE1              (((__IO_REG8_BIT*)(addr_TP1IOC0))->no2)
 
#define TP1OVF              (((__IO_REG8_BIT*)(addr_TP1OPT0))->no0)
 
#define TP2CE               (((__IO_REG8_BIT*)(addr_TP2CTL0))->no7)
 
#define TP2EEE              (((__IO_REG8_BIT*)(addr_TP2CTL1))->no5)
#define TP2EST              (((__IO_REG8_BIT*)(addr_TP2CTL1))->no6)
 
#define TP2OE0              (((__IO_REG8_BIT*)(addr_TP2IOC0))->no0)
#define TP2OE1              (((__IO_REG8_BIT*)(addr_TP2IOC0))->no2)
 
#define TP2OVF              (((__IO_REG8_BIT*)(addr_TP2OPT0))->no0)
 
#define TP3CE               (((__IO_REG8_BIT*)(addr_TP3CTL0))->no7)
 
#define TP3EEE              (((__IO_REG8_BIT*)(addr_TP3CTL1))->no5)
#define TP3EST              (((__IO_REG8_BIT*)(addr_TP3CTL1))->no6)
 
#define TP3OE0              (((__IO_REG8_BIT*)(addr_TP3IOC0))->no0)
#define TP3OE1              (((__IO_REG8_BIT*)(addr_TP3IOC0))->no2)
 
#define TP3OVF              (((__IO_REG8_BIT*)(addr_TP3OPT0))->no0)
 
#define TP4CE               (((__IO_REG8_BIT*)(addr_TP4CTL0))->no7)
 
#define TP4EEE              (((__IO_REG8_BIT*)(addr_TP4CTL1))->no5)
#define TP4EST              (((__IO_REG8_BIT*)(addr_TP4CTL1))->no6)
 
#define TP4OE0              (((__IO_REG8_BIT*)(addr_TP4IOC0))->no0)
#define TP4OE1              (((__IO_REG8_BIT*)(addr_TP4IOC0))->no2)
 
#define TP4OVF              (((__IO_REG8_BIT*)(addr_TP4OPT0))->no0)
 
#define TP5CE               (((__IO_REG8_BIT*)(addr_TP5CTL0))->no7)
 
#define TP5EEE              (((__IO_REG8_BIT*)(addr_TP5CTL1))->no5)
#define TP5EST              (((__IO_REG8_BIT*)(addr_TP5CTL1))->no6)
 
#define TP5OE0              (((__IO_REG8_BIT*)(addr_TP5IOC0))->no0)
#define TP5OE1              (((__IO_REG8_BIT*)(addr_TP5IOC0))->no2)
 
#define TP5OVF              (((__IO_REG8_BIT*)(addr_TP5OPT0))->no0)
 
#define TP6CE               (((__IO_REG8_BIT*)(addr_TP6CTL0))->no7)
 
#define TP6EEE              (((__IO_REG8_BIT*)(addr_TP6CTL1))->no5)
#define TP6EST              (((__IO_REG8_BIT*)(addr_TP6CTL1))->no6)
 
#define TP6OE0              (((__IO_REG8_BIT*)(addr_TP6IOC0))->no0)
#define TP6OE1              (((__IO_REG8_BIT*)(addr_TP6IOC0))->no2)
 
#define TP6OVF              (((__IO_REG8_BIT*)(addr_TP6OPT0))->no0)
 
#define TP7CE               (((__IO_REG8_BIT*)(addr_TP7CTL0))->no7)
 
#define TP7EEE              (((__IO_REG8_BIT*)(addr_TP7CTL1))->no5)
#define TP7EST              (((__IO_REG8_BIT*)(addr_TP7CTL1))->no6)
 
#define TP7OE0              (((__IO_REG8_BIT*)(addr_TP7IOC0))->no0)
#define TP7OE1              (((__IO_REG8_BIT*)(addr_TP7IOC0))->no2)
 
#define TP7OVF              (((__IO_REG8_BIT*)(addr_TP7OPT0))->no0)
 
#define TP8CE               (((__IO_REG8_BIT*)(addr_TP8CTL0))->no7)
 
#define TP8EEE              (((__IO_REG8_BIT*)(addr_TP8CTL1))->no5)
#define TP8EST              (((__IO_REG8_BIT*)(addr_TP8CTL1))->no6)
 
#define TP8OE0              (((__IO_REG8_BIT*)(addr_TP8IOC0))->no0)
#define TP8OE1              (((__IO_REG8_BIT*)(addr_TP8IOC0))->no2)
 
#define TP8OVF              (((__IO_REG8_BIT*)(addr_TP8OPT0))->no0)
 
#define WTM0                (((__IO_REG8_BIT*)(addr_WTM))->no0)
#define WTM1                (((__IO_REG8_BIT*)(addr_WTM))->no1)
 
#define TM0CE               (((__IO_REG8_BIT*)(addr_TM0CTL0))->no7)
 
#define RTPOE0              (((__IO_REG8_BIT*)(addr_RTPC0))->no7)
 
#define RTPOE1              (((__IO_REG8_BIT*)(addr_RTPC1))->no7)
 
#define PRERR               (((__IO_REG8_BIT*)(addr_SYS))->no0)
 
#define RSTOP               (((__IO_REG8_BIT*)(addr_RCM))->no0)
 
#define DF0                 (((__IO_REG8_BIT*)(addr_DTFR0))->no7)
 
#define DF1                 (((__IO_REG8_BIT*)(addr_DTFR1))->no7)
 
#define DF2                 (((__IO_REG8_BIT*)(addr_DTFR2))->no7)
 
#define DF3                 (((__IO_REG8_BIT*)(addr_DTFR3))->no7)
 
#define PSM0                (((__IO_REG8_BIT*)(addr_PSMR))->no0)
#define PSM1                (((__IO_REG8_BIT*)(addr_PSMR))->no1)
 
#define LOCK                (((__IO_REG8_BIT*)(addr_LOCKR))->no0)
 
#define CK3                 (((__IO_REG8_BIT*)(addr_PCC))->no3)
#define CLS                 (((__IO_REG8_BIT*)(addr_PCC))->no4)
#define MCK                 (((__IO_REG8_BIT*)(addr_PCC))->no6)
 
#define PLLON               (((__IO_REG8_BIT*)(addr_PLLCTL))->no0)
#define SELPLL              (((__IO_REG8_BIT*)(addr_PLLCTL))->no1)
 
#define CLME                (((__IO_REG8_BIT*)(addr_CLM))->no0)
 
#define LVIF                (((__IO_REG8_BIT*)(addr_LVIM))->no0)
#define LVIMD               (((__IO_REG8_BIT*)(addr_LVIM))->no1)
#define LVION               (((__IO_REG8_BIT*)(addr_LVIM))->no7)
 
#define RAMF                (((__IO_REG8_BIT*)(addr_RAMS))->no0)
 
#define BGCE0               (((__IO_REG8_BIT*)(addr_PRSM0))->no4)
 
#define OCDM0               (((__IO_REG8_BIT*)(addr_OCDM))->no0)
 
#define UA0DIR              (((__IO_REG8_BIT*)(addr_UA0CTL0))->no4)
#define UA0RXE              (((__IO_REG8_BIT*)(addr_UA0CTL0))->no5)
#define UA0TXE              (((__IO_REG8_BIT*)(addr_UA0CTL0))->no6)
#define UA0PWR              (((__IO_REG8_BIT*)(addr_UA0CTL0))->no7)
 
#define UA0SRF              (((__IO_REG8_BIT*)(addr_UA0OPT0))->no7)
 
#define UA0OVE              (((__IO_REG8_BIT*)(addr_UA0STR))->no0)
#define UA0FE               (((__IO_REG8_BIT*)(addr_UA0STR))->no1)
#define UA0PE               (((__IO_REG8_BIT*)(addr_UA0STR))->no2)
#define UA0TSF              (((__IO_REG8_BIT*)(addr_UA0STR))->no7)
 
#define UA1DIR              (((__IO_REG8_BIT*)(addr_UA1CTL0))->no4)
#define UA1RXE              (((__IO_REG8_BIT*)(addr_UA1CTL0))->no5)
#define UA1TXE              (((__IO_REG8_BIT*)(addr_UA1CTL0))->no6)
#define UA1PWR              (((__IO_REG8_BIT*)(addr_UA1CTL0))->no7)
 
#define UA1SRF              (((__IO_REG8_BIT*)(addr_UA1OPT0))->no7)
 
#define UA1OVE              (((__IO_REG8_BIT*)(addr_UA1STR))->no0)
#define UA1FE               (((__IO_REG8_BIT*)(addr_UA1STR))->no1)
#define UA1PE               (((__IO_REG8_BIT*)(addr_UA1STR))->no2)
#define UA1TSF              (((__IO_REG8_BIT*)(addr_UA1STR))->no7)
 
#define UA2DIR              (((__IO_REG8_BIT*)(addr_UA2CTL0))->no4)
#define UA2RXE              (((__IO_REG8_BIT*)(addr_UA2CTL0))->no5)
#define UA2TXE              (((__IO_REG8_BIT*)(addr_UA2CTL0))->no6)
#define UA2PWR              (((__IO_REG8_BIT*)(addr_UA2CTL0))->no7)
 
#define UA2SRF              (((__IO_REG8_BIT*)(addr_UA2OPT0))->no7)
 
#define UA2OVE              (((__IO_REG8_BIT*)(addr_UA2STR))->no0)
#define UA2FE               (((__IO_REG8_BIT*)(addr_UA2STR))->no1)
#define UA2PE               (((__IO_REG8_BIT*)(addr_UA2STR))->no2)
#define UA2TSF              (((__IO_REG8_BIT*)(addr_UA2STR))->no7)
 
#define UA3DIR              (((__IO_REG8_BIT*)(addr_UA3CTL0))->no4)
#define UA3RXE              (((__IO_REG8_BIT*)(addr_UA3CTL0))->no5)
#define UA3TXE              (((__IO_REG8_BIT*)(addr_UA3CTL0))->no6)
#define UA3PWR              (((__IO_REG8_BIT*)(addr_UA3CTL0))->no7)
 
#define UA3SRF              (((__IO_REG8_BIT*)(addr_UA3OPT0))->no7)
 
#define UA3OVE              (((__IO_REG8_BIT*)(addr_UA3STR))->no0)
#define UA3FE               (((__IO_REG8_BIT*)(addr_UA3STR))->no1)
#define UA3PE               (((__IO_REG8_BIT*)(addr_UA3STR))->no2)
#define UA3TSF              (((__IO_REG8_BIT*)(addr_UA3STR))->no7)
 
#define CB0SCE              (((__IO_REG8_BIT*)(addr_CB0CTL0))->no0)
#define CB0DIR              (((__IO_REG8_BIT*)(addr_CB0CTL0))->no4)
#define CB0RXE              (((__IO_REG8_BIT*)(addr_CB0CTL0))->no5)
#define CB0TXE              (((__IO_REG8_BIT*)(addr_CB0CTL0))->no6)
#define CB0PWR              (((__IO_REG8_BIT*)(addr_CB0CTL0))->no7)
 
#define CB0OVE              (((__IO_REG8_BIT*)(addr_CB0STR))->no0)
#define CB0TSF              (((__IO_REG8_BIT*)(addr_CB0STR))->no7)
 
#define CB1SCE              (((__IO_REG8_BIT*)(addr_CB1CTL0))->no0)
#define CB1DIR              (((__IO_REG8_BIT*)(addr_CB1CTL0))->no4)
#define CB1RXE              (((__IO_REG8_BIT*)(addr_CB1CTL0))->no5)
#define CB1TXE              (((__IO_REG8_BIT*)(addr_CB1CTL0))->no6)
#define CB1PWR              (((__IO_REG8_BIT*)(addr_CB1CTL0))->no7)
 
#define CB1OVE              (((__IO_REG8_BIT*)(addr_CB1STR))->no0)
#define CB1TSF              (((__IO_REG8_BIT*)(addr_CB1STR))->no7)
 
#define CB2SCE              (((__IO_REG8_BIT*)(addr_CB2CTL0))->no0)
#define CB2DIR              (((__IO_REG8_BIT*)(addr_CB2CTL0))->no4)
#define CB2RXE              (((__IO_REG8_BIT*)(addr_CB2CTL0))->no5)
#define CB2TXE              (((__IO_REG8_BIT*)(addr_CB2CTL0))->no6)
#define CB2PWR              (((__IO_REG8_BIT*)(addr_CB2CTL0))->no7)
 
#define CB2OVE              (((__IO_REG8_BIT*)(addr_CB2STR))->no0)
#define CB2TSF              (((__IO_REG8_BIT*)(addr_CB2STR))->no7)
 
#define CB3SCE              (((__IO_REG8_BIT*)(addr_CB3CTL0))->no0)
#define CB3DIR              (((__IO_REG8_BIT*)(addr_CB3CTL0))->no4)
#define CB3RXE              (((__IO_REG8_BIT*)(addr_CB3CTL0))->no5)
#define CB3TXE              (((__IO_REG8_BIT*)(addr_CB3CTL0))->no6)
#define CB3PWR              (((__IO_REG8_BIT*)(addr_CB3CTL0))->no7)
 
#define CB3OVE              (((__IO_REG8_BIT*)(addr_CB3STR))->no0)
#define CB3TSF              (((__IO_REG8_BIT*)(addr_CB3STR))->no7)
 
#define CB4SCE              (((__IO_REG8_BIT*)(addr_CB4CTL0))->no0)
#define CB4DIR              (((__IO_REG8_BIT*)(addr_CB4CTL0))->no4)
#define CB4RXE              (((__IO_REG8_BIT*)(addr_CB4CTL0))->no5)
#define CB4TXE              (((__IO_REG8_BIT*)(addr_CB4CTL0))->no6)
#define CB4PWR              (((__IO_REG8_BIT*)(addr_CB4CTL0))->no7)
 
#define CB4OVE              (((__IO_REG8_BIT*)(addr_CB4STR))->no0)
#define CB4TSF              (((__IO_REG8_BIT*)(addr_CB4STR))->no7)
 
#define CB5SCE              (((__IO_REG8_BIT*)(addr_CB5CTL0))->no0)
#define CB5DIR              (((__IO_REG8_BIT*)(addr_CB5CTL0))->no4)
#define CB5RXE              (((__IO_REG8_BIT*)(addr_CB5CTL0))->no5)
#define CB5TXE              (((__IO_REG8_BIT*)(addr_CB5CTL0))->no6)
#define CB5PWR              (((__IO_REG8_BIT*)(addr_CB5CTL0))->no7)
 
#define CB5OVE              (((__IO_REG8_BIT*)(addr_CB5STR))->no0)
#define CB5TSF              (((__IO_REG8_BIT*)(addr_CB5STR))->no7)
 
#define SPT0                (((__IO_REG8_BIT*)(addr_IICC0))->no0)
#define STT0                (((__IO_REG8_BIT*)(addr_IICC0))->no1)
#define ACKE0               (((__IO_REG8_BIT*)(addr_IICC0))->no2)
#define WTIM0               (((__IO_REG8_BIT*)(addr_IICC0))->no3)
#define SPIE0               (((__IO_REG8_BIT*)(addr_IICC0))->no4)
#define WREL0               (((__IO_REG8_BIT*)(addr_IICC0))->no5)
#define LREL0               (((__IO_REG8_BIT*)(addr_IICC0))->no6)
#define IICE0               (((__IO_REG8_BIT*)(addr_IICC0))->no7)
 
#define DAD0                (((__IO_REG8_BIT*)(addr_IICCL0))->no4)
#define CLD0                (((__IO_REG8_BIT*)(addr_IICCL0))->no5)
 
#define CLX0                (((__IO_REG8_BIT*)(addr_IICX0))->no0)
 
#define SPD0                (((__IO_REG8_BIT*)(addr_IICS0))->no0)
#define STD0                (((__IO_REG8_BIT*)(addr_IICS0))->no1)
#define ACKD0               (((__IO_REG8_BIT*)(addr_IICS0))->no2)
#define TRC0                (((__IO_REG8_BIT*)(addr_IICS0))->no3)
#define COI0                (((__IO_REG8_BIT*)(addr_IICS0))->no4)
#define EXC0                (((__IO_REG8_BIT*)(addr_IICS0))->no5)
#define ALD0                (((__IO_REG8_BIT*)(addr_IICS0))->no6)
#define MSTS0               (((__IO_REG8_BIT*)(addr_IICS0))->no7)
 
#define IICRSV0             (((__IO_REG8_BIT*)(addr_IICF0))->no0)
#define STCEN0              (((__IO_REG8_BIT*)(addr_IICF0))->no1)
#define IICBSY0             (((__IO_REG8_BIT*)(addr_IICF0))->no6)
#define STCF0               (((__IO_REG8_BIT*)(addr_IICF0))->no7)
 
#define SPT1                (((__IO_REG8_BIT*)(addr_IICC1))->no0)
#define STT1                (((__IO_REG8_BIT*)(addr_IICC1))->no1)
#define ACKE1               (((__IO_REG8_BIT*)(addr_IICC1))->no2)
#define WTIM1               (((__IO_REG8_BIT*)(addr_IICC1))->no3)
#define SPIE1               (((__IO_REG8_BIT*)(addr_IICC1))->no4)
#define WREL1               (((__IO_REG8_BIT*)(addr_IICC1))->no5)
#define LREL1               (((__IO_REG8_BIT*)(addr_IICC1))->no6)
#define IICE1               (((__IO_REG8_BIT*)(addr_IICC1))->no7)
 
#define DAD1                (((__IO_REG8_BIT*)(addr_IICCL1))->no4)
#define CLD1                (((__IO_REG8_BIT*)(addr_IICCL1))->no5)
 
#define CLX1                (((__IO_REG8_BIT*)(addr_IICX1))->no0)
 
#define SPD1                (((__IO_REG8_BIT*)(addr_IICS1))->no0)
#define STD1                (((__IO_REG8_BIT*)(addr_IICS1))->no1)
#define ACKD1               (((__IO_REG8_BIT*)(addr_IICS1))->no2)
#define TRC1                (((__IO_REG8_BIT*)(addr_IICS1))->no3)
#define COI1                (((__IO_REG8_BIT*)(addr_IICS1))->no4)
#define EXC1                (((__IO_REG8_BIT*)(addr_IICS1))->no5)
#define ALD1                (((__IO_REG8_BIT*)(addr_IICS1))->no6)
#define MSTS1               (((__IO_REG8_BIT*)(addr_IICS1))->no7)
 
#define IICRSV1             (((__IO_REG8_BIT*)(addr_IICF1))->no0)
#define STCEN1              (((__IO_REG8_BIT*)(addr_IICF1))->no1)
#define IICBSY1             (((__IO_REG8_BIT*)(addr_IICF1))->no6)
#define STCF1               (((__IO_REG8_BIT*)(addr_IICF1))->no7)
 
#define SPT2                (((__IO_REG8_BIT*)(addr_IICC2))->no0)
#define STT2                (((__IO_REG8_BIT*)(addr_IICC2))->no1)
#define ACKE2               (((__IO_REG8_BIT*)(addr_IICC2))->no2)
#define WTIM2               (((__IO_REG8_BIT*)(addr_IICC2))->no3)
#define SPIE2               (((__IO_REG8_BIT*)(addr_IICC2))->no4)
#define WREL2               (((__IO_REG8_BIT*)(addr_IICC2))->no5)
#define LREL2               (((__IO_REG8_BIT*)(addr_IICC2))->no6)
#define IICE2               (((__IO_REG8_BIT*)(addr_IICC2))->no7)
 
#define DAD2                (((__IO_REG8_BIT*)(addr_IICCL2))->no4)
#define CLD2                (((__IO_REG8_BIT*)(addr_IICCL2))->no5)
 
#define CLX2                (((__IO_REG8_BIT*)(addr_IICX2))->no0)
 
#define SPD2                (((__IO_REG8_BIT*)(addr_IICS2))->no0)
#define STD2                (((__IO_REG8_BIT*)(addr_IICS2))->no1)
#define ACKD2               (((__IO_REG8_BIT*)(addr_IICS2))->no2)
#define TRC2                (((__IO_REG8_BIT*)(addr_IICS2))->no3)
#define COI2                (((__IO_REG8_BIT*)(addr_IICS2))->no4)
#define EXC2                (((__IO_REG8_BIT*)(addr_IICS2))->no5)
#define ALD2                (((__IO_REG8_BIT*)(addr_IICS2))->no6)
#define MSTS2               (((__IO_REG8_BIT*)(addr_IICS2))->no7)
 
#define IICRSV2             (((__IO_REG8_BIT*)(addr_IICF2))->no0)
#define STCEN2              (((__IO_REG8_BIT*)(addr_IICF2))->no1)
#define IICBSY2             (((__IO_REG8_BIT*)(addr_IICF2))->no6)
#define STCF2               (((__IO_REG8_BIT*)(addr_IICF2))->no7)




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

#endif

/*******************************************************************************
*
* reg struct.
* Insert the dummy byte to make the address is in series!!
*
********************************************************************************/
    
typedef union{
    __IO_REG16 iReg;
    __IO_REG16_BIT  bReg;
}__IO_REG16_t;

typedef union{
    __IO_REG8 iReg;
    __IO_REG8_BIT  bReg;
}__IO_REG8_t;

typedef  struct v850_reg_map 
{
    
/*PDL      */ __IO_REG16_t*   rPDL;
/*PDLL     */ __IO_REG8_t*    rPDLL;
/*PDLH     */ __IO_REG8_t*    rPDLH;
/*PDH      */ __IO_REG8_t*    rPDH;
/*PCS      */ __IO_REG8_t*    rPCS;
/*PCT      */ __IO_REG8_t*    rPCT;
/*PCM      */ __IO_REG8_t*    rPCM;
/*PCD      */ __IO_REG8_t*    rPCD;
    
/*PMDL     */ __IO_REG16_t*   rPMDL;
/*PMDLL    */ __IO_REG8_t*    rPMDLL;
/*PMDLH    */ __IO_REG8_t*    rPMDLH;
/*PMDH     */ __IO_REG8_t*    rPMDH;
/*PMCS     */ __IO_REG8_t*    rPMCS;
/*PMCT     */ __IO_REG8_t*    rPMCT;
/*PMCM     */ __IO_REG8_t*    rPMCM;
/*PMCD     */ __IO_REG8_t*    rPMCD;
    
/*PMCDL    */ __IO_REG16_t*   rPMCDL;
/*PMCDLL   */ __IO_REG8_t*    rPMCDLL;
/*PMCDLH   */ __IO_REG8_t*    rPMCDLH;
/*PMCDH    */ __IO_REG8_t*    rPMCDH;
/*PMCCS    */ __IO_REG8_t*    rPMCCS;
/*PMCCT    */ __IO_REG8_t*    rPMCCT;
/*PMCCM    */ __IO_REG8_t*    rPMCCM;
    
/*BPC      */ __IO_REG16_t*   rBPC;
/*BSC      */ __IO_REG16_t*   rBSC;
    
/*VSWC     */ __IO_REG8_t*    rVSWC;
    
/*DSA0L    */ __IO_REG16_t*   rDSA0L;
/*DSA0H    */ __IO_REG16_t*   rDSA0H;
/*DDA0L    */ __IO_REG16_t*   rDDA0L;
/*DDA0H    */ __IO_REG16_t*   rDDA0H;
/*DSA1L    */ __IO_REG16_t*   rDSA1L;
/*DSA1H    */ __IO_REG16_t*   rDSA1H;
/*DDA1L    */ __IO_REG16_t*   rDDA1L;
/*DDA1H    */ __IO_REG16_t*   rDDA1H;
/*DSA2L    */ __IO_REG16_t*   rDSA2L;
/*DSA2H    */ __IO_REG16_t*   rDSA2H;
/*DDA2L    */ __IO_REG16_t*   rDDA2L;
/*DDA2H    */ __IO_REG16_t*   rDDA2H;
/*DSA3L    */ __IO_REG16_t*   rDSA3L;
/*DSA3H    */ __IO_REG16_t*   rDSA3H;
/*DDA3L    */ __IO_REG16_t*   rDDA3L;
/*DDA3H    */ __IO_REG16_t*   rDDA3H;
    
/*DBC0     */ __IO_REG16_t*   rDBC0;
/*DBC1     */ __IO_REG16_t*   rDBC1;
/*DBC2     */ __IO_REG16_t*   rDBC2;
/*DBC3     */ __IO_REG16_t*   rDBC3;
    
/*DADC0    */ __IO_REG16_t*   rDADC0;
/*DADC1    */ __IO_REG16_t*   rDADC1;
/*DADC2    */ __IO_REG16_t*   rDADC2;
/*DADC3    */ __IO_REG16_t*   rDADC3;
    
/*DCHC0    */ __IO_REG8_t*    rDCHC0;
/*DCHC1    */ __IO_REG8_t*    rDCHC1;
/*DCHC2    */ __IO_REG8_t*    rDCHC2;
/*DCHC3    */ __IO_REG8_t*    rDCHC3;
    
/*IMR0     */ __IO_REG16_t*   rIMR0;
/*IMR0L    */ __IO_REG8_t*    rIMR0L;
/*IMR0H    */ __IO_REG8_t*    rIMR0H;
/*IMR1     */ __IO_REG16_t*   rIMR1;
/*IMR1L    */ __IO_REG8_t*    rIMR1L;
/*IMR1H    */ __IO_REG8_t*    rIMR1H;
/*IMR2     */ __IO_REG16_t*   rIMR2;
/*IMR2L    */ __IO_REG8_t*    rIMR2L;
/*IMR2H    */ __IO_REG8_t*    rIMR2H;
/*IMR3     */ __IO_REG16_t*   rIMR3;
/*IMR3L    */ __IO_REG8_t*    rIMR3L;
/*IMR3H    */ __IO_REG8_t*    rIMR3H;
/*IMR4     */ __IO_REG16_t*   rIMR4;
/*IMR4L    */ __IO_REG8_t*    rIMR4L;
/*IMR4H    */ __IO_REG8_t*    rIMR4H;
    
/*LVIIC    */ __IO_REG8_t*    rLVIIC;
/*PIC0     */ __IO_REG8_t*    rPIC0;
/*PIC1     */ __IO_REG8_t*    rPIC1;
/*PIC2     */ __IO_REG8_t*    rPIC2;
/*PIC3     */ __IO_REG8_t*    rPIC3;
/*PIC4     */ __IO_REG8_t*    rPIC4;
/*PIC5     */ __IO_REG8_t*    rPIC5;
/*PIC6     */ __IO_REG8_t*    rPIC6;
/*PIC7     */ __IO_REG8_t*    rPIC7;
/*TQ0OVIC  */ __IO_REG8_t*    rTQ0OVIC;
/*TQ0CCIC0 */ __IO_REG8_t*    rTQ0CCIC0;
/*TQ0CCIC1 */ __IO_REG8_t*    rTQ0CCIC1;
/*TQ0CCIC2 */ __IO_REG8_t*    rTQ0CCIC2;
/*TQ0CCIC3 */ __IO_REG8_t*    rTQ0CCIC3;
/*TP0OVIC  */ __IO_REG8_t*    rTP0OVIC;
/*TP0CCIC0 */ __IO_REG8_t*    rTP0CCIC0;
/*TP0CCIC1 */ __IO_REG8_t*    rTP0CCIC1;
/*TP1OVIC  */ __IO_REG8_t*    rTP1OVIC;
/*TP1CCIC0 */ __IO_REG8_t*    rTP1CCIC0;
/*TP1CCIC1 */ __IO_REG8_t*    rTP1CCIC1;
/*TP2OVIC  */ __IO_REG8_t*    rTP2OVIC;
/*TP2CCIC0 */ __IO_REG8_t*    rTP2CCIC0;
/*TP2CCIC1 */ __IO_REG8_t*    rTP2CCIC1;
/*TP3OVIC  */ __IO_REG8_t*    rTP3OVIC;
/*TP3CCIC0 */ __IO_REG8_t*    rTP3CCIC0;
/*TP3CCIC1 */ __IO_REG8_t*    rTP3CCIC1;
/*TP4OVIC  */ __IO_REG8_t*    rTP4OVIC;
/*TP4CCIC0 */ __IO_REG8_t*    rTP4CCIC0;
/*TP4CCIC1 */ __IO_REG8_t*    rTP4CCIC1;
/*TP5OVIC  */ __IO_REG8_t*    rTP5OVIC;
/*TP5CCIC0 */ __IO_REG8_t*    rTP5CCIC0;
/*TP5CCIC1 */ __IO_REG8_t*    rTP5CCIC1;
/*TM0EQIC0 */ __IO_REG8_t*    rTM0EQIC0;
/*CB0RIC   */ __IO_REG8_t*    rCB0RIC;
/*IICIC1   */ __IO_REG8_t*    rIICIC1;
/*CB0TIC   */ __IO_REG8_t*    rCB0TIC;
/*CB1RIC   */ __IO_REG8_t*    rCB1RIC;
/*CB1TIC   */ __IO_REG8_t*    rCB1TIC;
/*CB2RIC   */ __IO_REG8_t*    rCB2RIC;
/*CB2TIC   */ __IO_REG8_t*    rCB2TIC;
/*CB3RIC   */ __IO_REG8_t*    rCB3RIC;
/*CB3TIC   */ __IO_REG8_t*    rCB3TIC;
/*CB4RIC   */ __IO_REG8_t*    rCB4RIC;
/*UA0RIC   */ __IO_REG8_t*    rUA0RIC;
/*CB4TIC   */ __IO_REG8_t*    rCB4TIC;
/*UA0TIC   */ __IO_REG8_t*    rUA0TIC;
/*IICIC2   */ __IO_REG8_t*    rIICIC2;
/*UA1RIC   */ __IO_REG8_t*    rUA1RIC;
/*UA1TIC   */ __IO_REG8_t*    rUA1TIC;
/*IICIC0   */ __IO_REG8_t*    rIICIC0;
/*UA2RIC   */ __IO_REG8_t*    rUA2RIC;
/*UA2TIC   */ __IO_REG8_t*    rUA2TIC;
/*ADIC     */ __IO_REG8_t*    rADIC;
/*DMAIC0   */ __IO_REG8_t*    rDMAIC0;
/*DMAIC1   */ __IO_REG8_t*    rDMAIC1;
/*DMAIC2   */ __IO_REG8_t*    rDMAIC2;
/*DMAIC3   */ __IO_REG8_t*    rDMAIC3;
/*KRIC     */ __IO_REG8_t*    rKRIC;
/*WTIIC    */ __IO_REG8_t*    rWTIIC;
/*WTIC     */ __IO_REG8_t*    rWTIC;
/*ERRIC    */ __IO_REG8_t*    rERRIC;
/*ERRIC0   */ __IO_REG8_t*    rERRIC0;
/*STAIC    */ __IO_REG8_t*    rSTAIC;
/*WUPIC0   */ __IO_REG8_t*    rWUPIC0;
/*IEIC1    */ __IO_REG8_t*    rIEIC1;
/*RECIC0   */ __IO_REG8_t*    rRECIC0;
/*IEIC2    */ __IO_REG8_t*    rIEIC2;
/*TRXIC0   */ __IO_REG8_t*    rTRXIC0;
/*ERRIC1   */ __IO_REG8_t*    rERRIC1;
/*WUPIC1   */ __IO_REG8_t*    rWUPIC1;
/*RECIC1   */ __IO_REG8_t*    rRECIC1;
/*TRXIC1   */ __IO_REG8_t*    rTRXIC1;
/*PIC8     */ __IO_REG8_t*    rPIC8;
/*TP6OVIC  */ __IO_REG8_t*    rTP6OVIC;
/*TP6CCIC0 */ __IO_REG8_t*    rTP6CCIC0;
/*TP6CCIC1 */ __IO_REG8_t*    rTP6CCIC1;
/*TP7OVIC  */ __IO_REG8_t*    rTP7OVIC;
/*TP7CCIC0 */ __IO_REG8_t*    rTP7CCIC0;
/*TP7CCIC1 */ __IO_REG8_t*    rTP7CCIC1;
/*TP8OVIC  */ __IO_REG8_t*    rTP8OVIC;
/*TP8CCIC0 */ __IO_REG8_t*    rTP8CCIC0;
/*TP8CCIC1 */ __IO_REG8_t*    rTP8CCIC1;
/*CB5RIC   */ __IO_REG8_t*    rCB5RIC;
/*CB5TIC   */ __IO_REG8_t*    rCB5TIC;
/*UA3RIC   */ __IO_REG8_t*    rUA3RIC;
/*UA3TIC   */ __IO_REG8_t*    rUA3TIC;
    
/*ISPR     */ __IO_REG8_t*    rISPR;
/*PRCMD    */ __IO_REG8_t*    rPRCMD;
/*PSC      */ __IO_REG8_t*    rPSC;
/*ADA0M0   */ __IO_REG8_t*    rADA0M0;
/*ADA0M1   */ __IO_REG8_t*    rADA0M1;
/*ADA0S    */ __IO_REG8_t*    rADA0S;
/*ADA0M2   */ __IO_REG8_t*    rADA0M2;
/*ADA0PFM  */ __IO_REG8_t*    rADA0PFM;
/*ADA0PFT  */ __IO_REG8_t*    rADA0PFT;
    
/*ADA0CR0  */ __IO_REG16_t*   rADA0CR0;
/*ADA0CR0H */ __IO_REG8_t*    rADA0CR0H;
/*ADA0CR1  */ __IO_REG16_t*   rADA0CR1;
/*ADA0CR1H */ __IO_REG8_t*    rADA0CR1H;
/*ADA0CR2  */ __IO_REG16_t*   rADA0CR2;
/*ADA0CR2H */ __IO_REG8_t*    rADA0CR2H;
/*ADA0CR3  */ __IO_REG16_t*   rADA0CR3;
/*ADA0CR3H */ __IO_REG8_t*    rADA0CR3H;
/*ADA0CR4  */ __IO_REG16_t*   rADA0CR4;
/*ADA0CR4H */ __IO_REG8_t*    rADA0CR4H;
/*ADA0CR5  */ __IO_REG16_t*   rADA0CR5;
/*ADA0CR5H */ __IO_REG8_t*    rADA0CR5H;
/*ADA0CR6  */ __IO_REG16_t*   rADA0CR6;
/*ADA0CR6H */ __IO_REG8_t*    rADA0CR6H;
/*ADA0CR7  */ __IO_REG16_t*   rADA0CR7;
/*ADA0CR7H */ __IO_REG8_t*    rADA0CR7H;
/*ADA0CR8  */ __IO_REG16_t*   rADA0CR8;
/*ADA0CR8H */ __IO_REG8_t*    rADA0CR8H;
/*ADA0CR9  */ __IO_REG16_t*   rADA0CR9;
/*ADA0CR9H */ __IO_REG8_t*    rADA0CR9H;
/*ADA0CR10 */ __IO_REG16_t*   rADA0CR10;
/*ADA0CR10H*/ __IO_REG8_t*    rADA0CR10H;
/*ADA0CR11 */ __IO_REG16_t*   rADA0CR11;
/*ADA0CR11H*/ __IO_REG8_t*    rADA0CR11H;
/*ADA0CR12 */ __IO_REG16_t*   rADA0CR12;
/*ADA0CR12H*/ __IO_REG8_t*    rADA0CR12H;
/*ADA0CR13 */ __IO_REG16_t*   rADA0CR13;
/*ADA0CR13H*/ __IO_REG8_t*    rADA0CR13H;
/*ADA0CR14 */ __IO_REG16_t*   rADA0CR14;
/*ADA0CR14H*/ __IO_REG8_t*    rADA0CR14H;
/*ADA0CR15 */ __IO_REG16_t*   rADA0CR15;
/*ADA0CR15H*/ __IO_REG8_t*    rADA0CR15H;
    
/*DA0CS0   */ __IO_REG8_t*    rDA0CS0;
/*DA0CS1   */ __IO_REG8_t*    rDA0CS1;
/*DA0M     */ __IO_REG8_t*    rDA0M;
    
/*KRM      */ __IO_REG8_t*    rKRM;
    
/*SELCNT0  */ __IO_REG8_t*    rSELCNT0;
    
/*CRCIN    */ __IO_REG8_t*    rCRCIN;
/*CRCD     */ __IO_REG16_t*   rCRCD;
    
/*NFC      */ __IO_REG8_t*    rNFC;
    
/*PRSM1    */ __IO_REG8_t*    rPRSM1;
/*PRSCM1   */ __IO_REG8_t*    rPRSCM1;
    
/*PRSM2    */ __IO_REG8_t*    rPRSM2;
/*PRSCM2   */ __IO_REG8_t*    rPRSCM2;
    
/*PRSM3    */ __IO_REG8_t*    rPRSM3;
/*PRSCM3   */ __IO_REG8_t*    rPRSCM3;
    
/*OCKS0    */ __IO_REG8_t*    rOCKS0;
    
/*OCKS1    */ __IO_REG8_t*    rOCKS1;
    
/*OCKS2    */ __IO_REG8_t*    rOCKS2;
    
/*BCR      */ __IO_REG8_t*    rBCR;
/*PSR      */ __IO_REG8_t*    rPSR;
/*SSR      */ __IO_REG8_t*    rSSR;
/*USR      */ __IO_REG8_t*    rUSR;
/*ISR      */ __IO_REG8_t*    rISR;
/*ESR      */ __IO_REG8_t*    rESR;
/*UAR      */ __IO_REG16_t*   rUAR;
/*SAR      */ __IO_REG16_t*   rSAR;
/*PAR      */ __IO_REG16_t*   rPAR;
/*RSA      */ __IO_REG16_t*   rRSA;
/*CDR      */ __IO_REG8_t*    rCDR;
/*DLR      */ __IO_REG8_t*    rDLR;
/*DR       */ __IO_REG8_t*    rDR;
/*FSR      */ __IO_REG8_t*    rFSR;
/*SCR      */ __IO_REG8_t*    rSCR;
/*CCR      */ __IO_REG8_t*    rCCR;
    
/*P0       */ __IO_REG8_t*    rP0;
/*P1       */ __IO_REG8_t*    rP1;
    
/*P3       */ __IO_REG16_t*   rP3;
/*P3L      */ __IO_REG8_t*    rP3L;
/*P3H      */ __IO_REG8_t*    rP3H;
/*P4       */ __IO_REG8_t*    rP4;
/*P5       */ __IO_REG8_t*    rP5;
/*P6       */ __IO_REG16_t*   rP6;
/*P6L      */ __IO_REG8_t*    rP6L;
/*P6H      */ __IO_REG8_t*    rP6H;
/*P7L      */ __IO_REG8_t*    rP7L;
/*P7H      */ __IO_REG8_t*    rP7H;
/*P8       */ __IO_REG8_t*    rP8;
/*P9       */ __IO_REG16_t*   rP9;
/*P9L      */ __IO_REG8_t*    rP9L;
/*P9H      */ __IO_REG8_t*    rP9H;
    
/*PM0      */ __IO_REG8_t*    rPM0;
/*PM1      */ __IO_REG8_t*    rPM1;
    
/*PM3      */ __IO_REG16_t*   rPM3;
/*PM3L     */ __IO_REG8_t*    rPM3L;
/*PM3H     */ __IO_REG8_t*    rPM3H;
/*PM4      */ __IO_REG8_t*    rPM4;
/*PM5      */ __IO_REG8_t*    rPM5;
/*PM6      */ __IO_REG16_t*   rPM6;
/*PM6L     */ __IO_REG8_t*    rPM6L;
/*PM6H     */ __IO_REG8_t*    rPM6H;
/*PM7      */ __IO_REG16_t*   rPM7;
/*PM7L     */ __IO_REG8_t*    rPM7L;
/*PM7H     */ __IO_REG8_t*    rPM7H;
/*PM8      */ __IO_REG8_t*    rPM8;
/*PM9      */ __IO_REG16_t*   rPM9;
/*PM9L     */ __IO_REG8_t*    rPM9L;
/*PM9H     */ __IO_REG8_t*    rPM9H;
    
/*PMC0     */ __IO_REG8_t*    rPMC0;
    
/*PMC3     */ __IO_REG16_t*   rPMC3;
/*PMC3L    */ __IO_REG8_t*    rPMC3L;
/*PMC3H    */ __IO_REG8_t*    rPMC3H;
/*PMC4     */ __IO_REG8_t*    rPMC4;
/*PMC5     */ __IO_REG8_t*    rPMC5;
/*PMC6     */ __IO_REG16_t*   rPMC6;
/*PMC6L    */ __IO_REG8_t*    rPMC6L;
/*PMC6H    */ __IO_REG8_t*    rPMC6H;
    
/*PMC8     */ __IO_REG8_t*    rPMC8;
/*PMC9     */ __IO_REG16_t*   rPMC9;
/*PMC9L    */ __IO_REG8_t*    rPMC9L;
/*PMC9H    */ __IO_REG8_t*    rPMC9H;
    
/*PFC0     */ __IO_REG8_t*    rPFC0;
    
/*PFC3     */ __IO_REG16_t*   rPFC3;
/*PFC3L    */ __IO_REG8_t*    rPFC3L;
/*PFC3H    */ __IO_REG8_t*    rPFC3H;
/*PFC4     */ __IO_REG8_t*    rPFC4;
/*PFC5     */ __IO_REG8_t*    rPFC5;
    
/*PFC6H    */ __IO_REG8_t*    rPFC6H;
    
/*PFC9     */ __IO_REG16_t*   rPFC9;
/*PFC9L    */ __IO_REG8_t*    rPFC9L;
/*PFC9H    */ __IO_REG8_t*    rPFC9H;
    
/*DWC0     */ __IO_REG16_t*   rDWC0;
    
/*AWC      */ __IO_REG16_t*   rAWC;
/*BCC      */ __IO_REG16_t*   rBCC;

/*TQ0CTL0  */ __IO_REG8_t*    rTQ0CTL0;
/*TQ0CTL1  */ __IO_REG8_t*    rTQ0CTL1;
/*TQ0IOC0  */ __IO_REG8_t*    rTQ0IOC0;
/*TQ0IOC1  */ __IO_REG8_t*    rTQ0IOC1;
/*TQ0IOC2  */ __IO_REG8_t*    rTQ0IOC2;
/*TQ0OPT0  */ __IO_REG8_t*    rTQ0OPT0;
/*TQ0CCR0  */ __IO_REG16_t*   rTQ0CCR0;
/*TQ0CCR1  */ __IO_REG16_t*   rTQ0CCR1;
/*TQ0CCR2  */ __IO_REG16_t*   rTQ0CCR2;
/*TQ0CCR3  */ __IO_REG16_t*   rTQ0CCR3;
/*TQ0CNT   */ __IO_REG16_t*   rTQ0CNT;
    
/*TP0CTL0  */ __IO_REG8_t*    rTP0CTL0;
/*TP0CTL1  */ __IO_REG8_t*    rTP0CTL1;
/*TP0IOC0  */ __IO_REG8_t*    rTP0IOC0;
/*TP0IOC1  */ __IO_REG8_t*    rTP0IOC1;
/*TP0IOC2  */ __IO_REG8_t*    rTP0IOC2;
/*TP0OPT0  */ __IO_REG8_t*    rTP0OPT0;
/*TP0CCR0  */ __IO_REG16_t*   rTP0CCR0;
/*TP0CCR1  */ __IO_REG16_t*   rTP0CCR1;
/*TP0CNT   */ __IO_REG16_t*   rTP0CNT;
    
/*TP1CTL0  */ __IO_REG8_t*    rTP1CTL0;
/*TP1CTL1  */ __IO_REG8_t*    rTP1CTL1;
/*TP1IOC0  */ __IO_REG8_t*    rTP1IOC0;
/*TP1IOC1  */ __IO_REG8_t*    rTP1IOC1;
/*TP1IOC2  */ __IO_REG8_t*    rTP1IOC2;
/*TP1OPT0  */ __IO_REG8_t*    rTP1OPT0;
/*TP1CCR0  */ __IO_REG16_t*   rTP1CCR0;
/*TP1CCR1  */ __IO_REG16_t*   rTP1CCR1;
/*TP1CNT   */ __IO_REG16_t*   rTP1CNT;
    
/*TP2CTL0  */ __IO_REG8_t*    rTP2CTL0;
/*TP2CTL1  */ __IO_REG8_t*    rTP2CTL1;
/*TP2IOC0  */ __IO_REG8_t*    rTP2IOC0;
/*TP2IOC1  */ __IO_REG8_t*    rTP2IOC1;
/*TP2IOC2  */ __IO_REG8_t*    rTP2IOC2;
/*TP2OPT0  */ __IO_REG8_t*    rTP2OPT0;
/*TP2CCR0  */ __IO_REG16_t*   rTP2CCR0;
/*TP2CCR1  */ __IO_REG16_t*   rTP2CCR1;
/*TP2CNT   */ __IO_REG16_t*   rTP2CNT;
    
/*TP3CTL0  */ __IO_REG8_t*    rTP3CTL0;
/*TP3CTL1  */ __IO_REG8_t*    rTP3CTL1;
/*TP3IOC0  */ __IO_REG8_t*    rTP3IOC0;
/*TP3IOC1  */ __IO_REG8_t*    rTP3IOC1;
/*TP3IOC2  */ __IO_REG8_t*    rTP3IOC2;
/*TP3OPT0  */ __IO_REG8_t*    rTP3OPT0;
/*TP3CCR0  */ __IO_REG16_t*   rTP3CCR0;
/*TP3CCR1  */ __IO_REG16_t*   rTP3CCR1;
/*TP3CNT   */ __IO_REG16_t*   rTP3CNT;
    
/*TP4CTL0  */ __IO_REG8_t*    rTP4CTL0;
/*TP4CTL1  */ __IO_REG8_t*    rTP4CTL1;
/*TP4IOC0  */ __IO_REG8_t*    rTP4IOC0;
/*TP4IOC1  */ __IO_REG8_t*    rTP4IOC1;
/*TP4IOC2  */ __IO_REG8_t*    rTP4IOC2;
/*TP4OPT0  */ __IO_REG8_t*    rTP4OPT0;
/*TP4CCR0  */ __IO_REG16_t*   rTP4CCR0;
/*TP4CCR1  */ __IO_REG16_t*   rTP4CCR1;
/*TP4CNT   */ __IO_REG16_t*   rTP4CNT;
    
/*TP5CTL0  */ __IO_REG8_t*    rTP5CTL0;
/*TP5CTL1  */ __IO_REG8_t*    rTP5CTL1;
/*TP5IOC0  */ __IO_REG8_t*    rTP5IOC0;
/*TP5IOC1  */ __IO_REG8_t*    rTP5IOC1;
/*TP5IOC2  */ __IO_REG8_t*    rTP5IOC2;
/*TP5OPT0  */ __IO_REG8_t*    rTP5OPT0;
/*TP5CCR0  */ __IO_REG16_t*   rTP5CCR0;
/*TP5CCR1  */ __IO_REG16_t*   rTP5CCR1;
/*TP5CNT   */ __IO_REG16_t*   rTP5CNT;
    
/*TP6CTL0  */ __IO_REG8_t*    rTP6CTL0;
/*TP6CTL1  */ __IO_REG8_t*    rTP6CTL1;
/*TP6IOC0  */ __IO_REG8_t*    rTP6IOC0;
/*TP6IOC1  */ __IO_REG8_t*    rTP6IOC1;
/*TP6IOC2  */ __IO_REG8_t*    rTP6IOC2;
/*TP6OPT0  */ __IO_REG8_t*    rTP6OPT0;
/*TP6CCR0  */ __IO_REG16_t*   rTP6CCR0;
/*TP6CCR1  */ __IO_REG16_t*   rTP6CCR1;
/*TP6CNT   */ __IO_REG16_t*   rTP6CNT;
    
/*TP7CTL0  */ __IO_REG8_t*    rTP7CTL0;
/*TP7CTL1  */ __IO_REG8_t*    rTP7CTL1;
/*TP7IOC0  */ __IO_REG8_t*    rTP7IOC0;
/*TP7IOC1  */ __IO_REG8_t*    rTP7IOC1;
/*TP7IOC2  */ __IO_REG8_t*    rTP7IOC2;
/*TP7OPT0  */ __IO_REG8_t*    rTP7OPT0;
/*TP7CCR0  */ __IO_REG16_t*   rTP7CCR0;
/*TP7CCR1  */ __IO_REG16_t*   rTP7CCR1;
/*TP7CNT   */ __IO_REG16_t*   rTP7CNT;
    
/*TP8CTL0  */ __IO_REG8_t*    rTP8CTL0;
/*TP8CTL1  */ __IO_REG8_t*    rTP8CTL1;
/*TP8IOC0  */ __IO_REG8_t*    rTP8IOC0;
/*TP8IOC1  */ __IO_REG8_t*    rTP8IOC1;
/*TP8IOC2  */ __IO_REG8_t*    rTP8IOC2;
/*TP8OPT0  */ __IO_REG8_t*    rTP8OPT0;
/*TP8CCR0  */ __IO_REG16_t*   rTP8CCR0;
/*TP8CCR1  */ __IO_REG16_t*   rTP8CCR1;
/*TP8CNT   */ __IO_REG16_t*   rTP8CNT;
    
/*WTM      */ __IO_REG8_t*    rWTM;
    
/*TM0CTL0  */ __IO_REG8_t*    rTM0CTL0;
    
/*TM0CMP0  */ __IO_REG16_t*   rTM0CMP0;
    
/*OSTS     */ __IO_REG8_t*    rOSTS;
/*PLLS     */ __IO_REG8_t*    rPLLS;
    
/*WDTM2    */ __IO_REG8_t*    rWDTM2;
/*WDTE     */ __IO_REG8_t*    rWDTE;
    
/*RTBL0    */ __IO_REG8_t*    rRTBL0;
/*RTBH0    */ __IO_REG8_t*    rRTBH0;
/*RTPM0    */ __IO_REG8_t*    rRTPM0;
/*RTPC0    */ __IO_REG8_t*    rRTPC0;
    
/*RTBL1    */ __IO_REG8_t*    rRTBL1;
/*RTBH1    */ __IO_REG8_t*    rRTBH1;
/*RTPM1    */ __IO_REG8_t*    rRTPM1;
/*RTPC1    */ __IO_REG8_t*    rRTPC1;
    
/*PFCE3L   */ __IO_REG8_t*    rPFCE3L;
    
/*PFCE5    */ __IO_REG8_t*    rPFCE5;
    
/*PFCE9    */ __IO_REG16_t*   rPFCE9;
/*PFCE9L   */ __IO_REG8_t*    rPFCE9L;
/*PFCE9H   */ __IO_REG8_t*    rPFCE9H;
    
/*SYS      */ __IO_REG8_t*    rSYS;
    
/*RCM      */ __IO_REG8_t*    rRCM;
    
/*DTFR0    */ __IO_REG8_t*    rDTFR0;
/*DTFR1    */ __IO_REG8_t*    rDTFR1;
/*DTFR2    */ __IO_REG8_t*    rDTFR2;
/*DTFR3    */ __IO_REG8_t*    rDTFR3;
    
/*PSMR     */ __IO_REG8_t*    rPSMR;
/*CKC      */ __IO_REG8_t*    rCKC;
/*LOCKR    */ __IO_REG8_t*    rLOCKR;
    
/*PCC      */ __IO_REG8_t*    rPCC;
    
/*PLLCTL   */ __IO_REG8_t*    rPLLCTL;
/*CCLS     */ __IO_REG8_t*    rCCLS;
    
/*CORAD0   */ __IO_REG32*     rCORAD0;
/*CORAD0L  */ __IO_REG16_t*   rCORAD0L;
/*CORAD0H  */ __IO_REG16_t*   rCORAD0H;
/*CORAD1   */ __IO_REG32*     rCORAD1;
/*CORAD1L  */ __IO_REG16_t*   rCORAD1L;
/*CORAD1H  */ __IO_REG16_t*   rCORAD1H;
/*CORAD2   */ __IO_REG32*     rCORAD2;
/*CORAD2L  */ __IO_REG16_t*   rCORAD2L;
/*CORAD2H  */ __IO_REG16_t*   rCORAD2H;
/*CORAD3   */ __IO_REG32*     rCORAD3;
/*CORAD3L  */ __IO_REG16_t*   rCORAD3L;
/*CORAD3H  */ __IO_REG16_t*   rCORAD3H;
    
/*CLM      */ __IO_REG8_t*    rCLM;
    
/*CORCN    */ __IO_REG8_t*    rCORCN;
    
/*RESF     */ __IO_REG8_t*    rRESF;
    
/*LVIM     */ __IO_REG8_t*    rLVIM;
/*LVIS     */ __IO_REG8_t*    rLVIS;
/*RAMS     */ __IO_REG8_t*    rRAMS;
    
/*PRSM0    */ __IO_REG8_t*    rPRSM0;
/*PRSCM0   */ __IO_REG8_t*    rPRSCM0;
    
/*OCDM     */ __IO_REG8_t*    rOCDM;
/*PEMU1    */ __IO_REG8_t*    rPEMU1;
/*UA0CTL0  */ __IO_REG8_t*    rUA0CTL0;
/*UA0CTL1  */ __IO_REG8_t*    rUA0CTL1;
/*UA0CTL2  */ __IO_REG8_t*    rUA0CTL2;
/*UA0OPT0  */ __IO_REG8_t*    rUA0OPT0;
/*UA0STR   */ __IO_REG8_t*    rUA0STR;
/*UA0RX    */ __IO_REG8_t*    rUA0RX;
/*UA0TX    */ __IO_REG8_t*    rUA0TX;
    
/*UA1CTL0  */ __IO_REG8_t*    rUA1CTL0;
/*UA1CTL1  */ __IO_REG8_t*    rUA1CTL1;
/*UA1CTL2  */ __IO_REG8_t*    rUA1CTL2;
/*UA1OPT0  */ __IO_REG8_t*    rUA1OPT0;
/*UA1STR   */ __IO_REG8_t*    rUA1STR;
/*UA1RX    */ __IO_REG8_t*    rUA1RX;
/*UA1TX    */ __IO_REG8_t*    rUA1TX;
    
/*UA2CTL0  */ __IO_REG8_t*    rUA2CTL0;
/*UA2CTL1  */ __IO_REG8_t*    rUA2CTL1;
/*UA2CTL2  */ __IO_REG8_t*    rUA2CTL2;
/*UA2OPT0  */ __IO_REG8_t*    rUA2OPT0;
/*UA2STR   */ __IO_REG8_t*    rUA2STR;
/*UA2RX    */ __IO_REG8_t*    rUA2RX;
/*UA2TX    */ __IO_REG8_t*    rUA2TX;
    
/*UA3CTL0  */ __IO_REG8_t*    rUA3CTL0;
/*UA3CTL1  */ __IO_REG8_t*    rUA3CTL1;
/*UA3CTL2  */ __IO_REG8_t*    rUA3CTL2;
/*UA3OPT0  */ __IO_REG8_t*    rUA3OPT0;
/*UA3STR   */ __IO_REG8_t*    rUA3STR;
/*UA3RX    */ __IO_REG8_t*    rUA3RX;
/*UA3TX    */ __IO_REG8_t*    rUA3TX;
    
/*INTF0    */ __IO_REG8_t*    rINTF0;
    
/*INTF3    */ __IO_REG8_t*    rINTF3;
    
/*INTF8    */ __IO_REG8_t*    rINTF8;
    
/*INTF9H   */ __IO_REG8_t*    rINTF9H;
    
/*INTR0    */ __IO_REG8_t*    rINTR0;
    
/*INTR3    */ __IO_REG8_t*    rINTR3;
    
/*INTR8    */ __IO_REG8_t*    rINTR8;
    
/*INTR9H   */ __IO_REG8_t*    rINTR9H;
    
/*PF0      */ __IO_REG8_t*    rPF0;
    
/*PF3      */ __IO_REG16_t*   rPF3;
/*PF3L     */ __IO_REG8_t*    rPF3L;
/*PF3H     */ __IO_REG8_t*    rPF3H;
/*PF4      */ __IO_REG8_t*    rPF4;
/*PF5      */ __IO_REG8_t*    rPF5;
/*PF6      */ __IO_REG16_t*   rPF6;
/*PF6L     */ __IO_REG8_t*    rPF6L;
/*PF6H     */ __IO_REG8_t*    rPF6H;
    
/*PF8      */ __IO_REG8_t*    rPF8;
/*PF9      */ __IO_REG16_t*   rPF9;
/*PF9L     */ __IO_REG8_t*    rPF9L;
/*PF9H     */ __IO_REG8_t*    rPF9H;
    
/*PRDSELL  */ __IO_REG16_t*   rPRDSELL;
/*PRDSELH  */ __IO_REG16_t*   rPRDSELH;
    
/*CB0CTL0  */ __IO_REG8_t*    rCB0CTL0;
/*CB0CTL1  */ __IO_REG8_t*    rCB0CTL1;
/*CB0CTL2  */ __IO_REG8_t*    rCB0CTL2;
/*CB0STR   */ __IO_REG8_t*    rCB0STR;
/*CB0RX    */ __IO_REG16_t*   rCB0RX;
/*CB0RXL   */ __IO_REG8_t*    rCB0RXL;
/*CB0TX    */ __IO_REG16_t*   rCB0TX;
/*CB0TXL   */ __IO_REG8_t*    rCB0TXL;
    
/*CB1CTL0  */ __IO_REG8_t*    rCB1CTL0;
/*CB1CTL1  */ __IO_REG8_t*    rCB1CTL1;
/*CB1CTL2  */ __IO_REG8_t*    rCB1CTL2;
/*CB1STR   */ __IO_REG8_t*    rCB1STR;
/*CB1RX    */ __IO_REG16_t*   rCB1RX;
/*CB1RXL   */ __IO_REG8_t*    rCB1RXL;
/*CB1TX    */ __IO_REG16_t*   rCB1TX;
/*CB1TXL   */ __IO_REG8_t*    rCB1TXL;
    
/*CB2CTL0  */ __IO_REG8_t*    rCB2CTL0;
/*CB2CTL1  */ __IO_REG8_t*    rCB2CTL1;
/*CB2CTL2  */ __IO_REG8_t*    rCB2CTL2;
/*CB2STR   */ __IO_REG8_t*    rCB2STR;
/*CB2RX    */ __IO_REG16_t*   rCB2RX;
/*CB2RXL   */ __IO_REG8_t*    rCB2RXL;
/*CB2TX    */ __IO_REG16_t*   rCB2TX;
/*CB2TXL   */ __IO_REG8_t*    rCB2TXL;
    
/*CB3CTL0  */ __IO_REG8_t*    rCB3CTL0;
/*CB3CTL1  */ __IO_REG8_t*    rCB3CTL1;
/*CB3CTL2  */ __IO_REG8_t*    rCB3CTL2;
/*CB3STR   */ __IO_REG8_t*    rCB3STR;
/*CB3RX    */ __IO_REG16_t*   rCB3RX;
/*CB3RXL   */ __IO_REG8_t*    rCB3RXL;
/*CB3TX    */ __IO_REG16_t*   rCB3TX;
/*CB3TXL   */ __IO_REG8_t*    rCB3TXL;
    
/*CB4CTL0  */ __IO_REG8_t*    rCB4CTL0;
/*CB4CTL1  */ __IO_REG8_t*    rCB4CTL1;
/*CB4CTL2  */ __IO_REG8_t*    rCB4CTL2;
/*CB4STR   */ __IO_REG8_t*    rCB4STR;
/*CB4RX    */ __IO_REG16_t*   rCB4RX;
/*CB4RXL   */ __IO_REG8_t*    rCB4RXL;
/*CB4TX    */ __IO_REG16_t*   rCB4TX;
/*CB4TXL   */ __IO_REG8_t*    rCB4TXL;
    
/*CB5CTL0  */ __IO_REG8_t*    rCB5CTL0;
/*CB5CTL1  */ __IO_REG8_t*    rCB5CTL1;
/*CB5CTL2  */ __IO_REG8_t*    rCB5CTL2;
/*CB5STR   */ __IO_REG8_t*    rCB5STR;
/*CB5RX    */ __IO_REG16_t*   rCB5RX;
/*CB5RXL   */ __IO_REG8_t*    rCB5RXL;
/*CB5TX    */ __IO_REG16_t*   rCB5TX;
/*CB5TXL   */ __IO_REG8_t*    rCB5TXL;
    
/*IIC0     */ __IO_REG8_t*    rIIC0;
/*IICC0    */ __IO_REG8_t*    rIICC0;
/*SVA0     */ __IO_REG8_t*    rSVA0;
/*IICCL0   */ __IO_REG8_t*    rIICCL0;
/*IICX0    */ __IO_REG8_t*    rIICX0;
/*IICS0    */ __IO_REG8_t*    rIICS0;
    
/*IICF0    */ __IO_REG8_t*    rIICF0;
    
/*IIC1     */ __IO_REG8_t*    rIIC1;
/*IICC1    */ __IO_REG8_t*    rIICC1;
/*SVA1     */ __IO_REG8_t*    rSVA1;
/*IICCL1   */ __IO_REG8_t*    rIICCL1;
/*IICX1    */ __IO_REG8_t*    rIICX1;
/*IICS1    */ __IO_REG8_t*    rIICS1;
    
/*IICF1    */ __IO_REG8_t*    rIICF1;
    
/*IIC2     */ __IO_REG8_t*    rIIC2;
/*IICC2    */ __IO_REG8_t*    rIICC2;
/*SVA2     */ __IO_REG8_t*    rSVA2;
/*IICCL2   */ __IO_REG8_t*    rIICCL2;
/*IICX2    */ __IO_REG8_t*    rIICX2;
/*IICS2    */ __IO_REG8_t*    rIICS2;
    
/*IICF2    */ __IO_REG8_t*    rIICF2;
    
/*EXIMC    */ __IO_REG8_t*    rEXIMC;

}tMCU_REG_MAP;


