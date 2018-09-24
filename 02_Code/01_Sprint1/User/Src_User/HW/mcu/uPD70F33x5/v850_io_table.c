
//IO register 
//Port n io register   (Pn: n = 0, 1, 3 to 9, CD, CM, CS, CT, DH, DL)
//Port n mode register (PMn: n = 0, 1, 3 to 9, CD, CM, CS, CT, DH, DL)
//Port n mode control register (PMCn: n = 0, 3 to 6, 8, 9, CM, CS, CT, DH, DL) Switch to alternate-function mode
//Port n function control register (PFCn: n = 0, 3 to 6, 9)  Alternate-function selection
//Port n function control expansion register (PFCEn: n = 3, 5, 9) 
//Port n function register (PFn: n = 0, 3 to 6, 8, 9),N-ch open-drain setting
#pragma pack(1)
typedef struct {
    bit_t bit0:1;
    bit_t bit1:1;
    bit_t bit2:1;
    bit_t bit3:1;
    bit_t bit4:1;
    bit_t bit5:1;
    bit_t bit6:1;
    bit_t bit7:1;
}tPIN_POS;

#pragma pack(1)
typedef struct{
    void* Pn;   //端口寄存器地址
    void* PMn;  //端口方向寄存器地址
    void* PFn;  //端口输出模式寄存器地址
    void* PMCn; //复用开关寄存器
    void* PFCn; //复用功能选择寄存器
    void* PFCEn;//功能扩展寄存器
}tPIN_REG;

#pragma pack(1)   
typedef struct{
    void* ADCBASEreg;
    void* PMn;
}tADC_REG;

#pragma pack(1)
typedef struct{
    uint8_t  cPinIdx;
    uint8_t  n;
    bool      bInit;/*0:default as input,1:default as output 0;2:default as output 1;Other:do nothing*/
}tPIN_DEF;

#pragma pack(1)
typedef struct{
    uint8_t  cPinIdx;
    uint8_t  n;
}tADC_DEF;



const tPIN_REG tP0_reg    ={addr_P0     ,addr_PM0      ,addr_PF0   ,addr_PMC0   ,addr_PFC0   ,NULL};
const tPIN_REG tP1_reg    ={addr_P1     ,addr_PM1      ,NULL       ,NULL        ,NULL        ,NULL};
const tPIN_REG tP3L_reg   ={addr_P3L    ,addr_PM3L     ,addr_PF3L  ,addr_PMC3L  ,addr_PFC3L  ,addr_PFCE3L};
const tPIN_REG tP3H_reg   ={addr_P3H    ,addr_PM3H     ,addr_PF3H  ,addr_PMC3H  ,addr_PFC3H  ,NULL};
const tPIN_REG tP4_reg    ={addr_P4     ,addr_PM4      ,addr_PF4   ,addr_PMC4   ,addr_PFC4   ,NULL};
const tPIN_REG tP5_reg    ={addr_P5     ,addr_PM5      ,addr_PF5   ,addr_PMC5   ,addr_PFC5   ,addr_PFCE5};
const tPIN_REG tP6L_reg   ={addr_P6L    ,addr_PM6L     ,addr_PF6L  ,addr_PMC6L  ,NULL        ,NULL};
const tPIN_REG tP6H_reg   ={addr_P6H    ,addr_PM6H     ,addr_PF6H  ,addr_PMC6H  ,addr_PFC6H  ,NULL};
const tPIN_REG tP7L_reg   ={addr_P7L    ,addr_PM7L     ,NULL       ,NULL        ,NULL        ,NULL};
const tPIN_REG tP7H_reg   ={addr_P7H    ,addr_PM7H     ,NULL       ,NULL        ,NULL        ,NULL};
const tPIN_REG tP8_reg    ={addr_P8     ,addr_PM8      ,addr_PF8   ,addr_PMC8   ,NULL        ,NULL};
const tPIN_REG tP9L_reg   ={addr_P9L    ,addr_PM9L     ,addr_PF9L  ,addr_PMC9L  ,addr_PFC9L  ,addr_PFCE9L};
const tPIN_REG tP9H_reg   ={addr_P9H    ,addr_PM9H     ,addr_PF9H  ,addr_PMC9H  ,addr_PFC9H  ,addr_PFCE9H};
const tPIN_REG tPCD_reg   ={addr_PCD    ,addr_PMCD     ,NULL       ,NULL        ,NULL        ,NULL};
const tPIN_REG tPCT_reg   ={addr_PCT    ,addr_PMCT     ,NULL       ,addr_PMCCT  ,NULL        ,NULL};
const tPIN_REG tPCS_reg   ={addr_PCS    ,addr_PMCS     ,NULL       ,addr_PMCCS  ,NULL        ,NULL};
const tPIN_REG tPCM_reg   ={addr_PCM    ,addr_PMCM     ,NULL       ,addr_PMCCM  ,NULL        ,NULL};
const tPIN_REG tPDLL_reg  ={addr_PDLL   ,addr_PMDLL    ,NULL       ,addr_PMCDLL ,NULL        ,NULL};
const tPIN_REG tPDLH_reg  ={addr_PDLH   ,addr_PMDLH    ,NULL       ,addr_PMCDLH ,NULL        ,NULL};
const tPIN_REG tPDH_reg   ={addr_PDH    ,addr_PMDH     ,NULL       ,addr_PMCDH  ,NULL        ,NULL};

const tADC_REG tADC_reg  ={addr_ADA0CR0, addr_PM7L};

const tPIN_REG* lc_atRegTab[PIO_n] = {
     /*PIO_P0,*/     &tP0_reg,
     /*PIO_P1,*/     &tP1_reg,
     /*PIO_P3L,*/     &tP3L_reg,
     /*PIO_P3H,*/     &tP3H_reg,
     /*PIO_P4,*/     &tP4_reg,
     /*PIO_P5,*/     &tP5_reg,
     /*PIO_P6L,*/     &tP6L_reg,
     /*PIO_P6H,*/     &tP6H_reg,
     /*PIO_P7L,*/     &tP7L_reg,
     /*PIO_P7H,*/     &tP7H_reg,
     /*PIO_P8,*/     &tP8_reg,
     /*PIO_P9L,*/     &tP9L_reg,
     /*PIO_P9H,*/     &tP9H_reg,
     /*PIO_PCD,*/     &tPCD_reg,
     /*PIO_PCT,*/     &tPCT_reg,
     /*PIO_PCS,*/     &tPCS_reg,
     /*PIO_PCM,*/     &tPCM_reg,
     /*PIO_PDLL,*/     &tPDLL_reg,
     /*PIO_PDLH,*/     &tPDLH_reg,
     /*PIO_PDH,*/     &tPDH_reg,
};


const tPIN_DEF lc_atPinDefTab[PIN_N] = {
    { PIO_P0,0 ,0},
    { PIO_P0,1 ,1},
    { PIO_P0,2 ,0 },
    { PIO_P0,3 ,0 },
    { PIO_P0,4 ,0 },
    { PIO_P0,5 ,0 },
    { PIO_P0,6 ,0 },
    { PIO_P0,7 ,10 },
    { PIO_P1,0 ,1 },
    { PIO_P1,1 ,1 },
    { PIO_P1,2 ,1 },
    { PIO_P1,3 ,1 },
    { PIO_P1,4 ,1 },
    { PIO_P1,5 ,1 },
    { PIO_P1,6 ,1 },
    { PIO_P1,7 ,1 },
    { PIO_P3L,0 ,1 },
    { PIO_P3L,1 ,1 },
    { PIO_P3L,2 ,1 },
    { PIO_P3L,3 ,1 },
    { PIO_P3L,4 ,1 },
    { PIO_P3L,5 ,1 },
    { PIO_P3L,6 ,1 },
    { PIO_P3L,7 ,1 },
    { PIO_P3H,0 ,1 },
    { PIO_P3H,1,1 },
    { PIO_P3H,2,1 },
    { PIO_P3H,3,1 },
    { PIO_P3H,4,1 },
    { PIO_P3H,5,1 },
    { PIO_P3H,6,1 },
    { PIO_P3H,7,1 },
    { PIO_P4,0,1 },
    { PIO_P4,1,1 },
    { PIO_P4,2,1 },
    { PIO_P4,3,1 },
    { PIO_P4,4,1 },
    { PIO_P4,5,1 },
    { PIO_P4,6,1 },
    { PIO_P4,7,1 },
    { PIO_P5,0,1 },
    { PIO_P5,1,1 },
    { PIO_P5,2,1 },
    { PIO_P5,3,1 },
    { PIO_P5,4,1 },
    { PIO_P5,5,1 },
    { PIO_P5,6,1 },
    { PIO_P5,7,1 },
    { PIO_P6L,0,1 },
    { PIO_P6L,1,1 },
    { PIO_P6L,2,1 },
    { PIO_P6L,3,1 },
    { PIO_P6L,4,0 },
    { PIO_P6L,5,1 },
    { PIO_P6L,6,1 },
    { PIO_P6L,7,1 },
    { PIO_P6H,0,1 },
    { PIO_P6H,1,1 },
    { PIO_P6H,2,1 },
    { PIO_P6H,3,1 },
    { PIO_P6H,4,1 },
    { PIO_P6H,5,1 },
    { PIO_P6H,6,1 },
    { PIO_P6H,7,1 },
    { PIO_P7L,0,1 },
    { PIO_P7L,1,1 },
    { PIO_P7L,2,1 },
    { PIO_P7L,3,1 },
    { PIO_P7L,4,1 },
    { PIO_P7L,5,1 },
    { PIO_P7L,6,1 },
    { PIO_P7L,7,1 },
    { PIO_P7H,0,1 },
    { PIO_P7H,1,1 },
    { PIO_P7H,2,1 },
    { PIO_P7H,3,1 },
    { PIO_P7H,4,1 },
    { PIO_P7H,5,1 },
    { PIO_P7H,6,1 },
    { PIO_P7H,7,1 },
    { PIO_P8,0 ,1},
    { PIO_P8,1 ,1},
    { PIO_P8,2 ,1},
    { PIO_P8,3 ,1},
    { PIO_P8,4 ,1},
    { PIO_P8,5 ,1},
    { PIO_P8,6 ,1},
    { PIO_P8,7 ,1},
    { PIO_P9L,0,1 },
    { PIO_P9L,1,1 },
    { PIO_P9L,2,1 },
    { PIO_P9L,3,1 },
    { PIO_P9L,4,1 },
    { PIO_P9L,5,1 },
    { PIO_P9L,6,1 },
    { PIO_P9L,7,1 },
    { PIO_P9H,0,1 },
    { PIO_P9H,1,1 },
    { PIO_P9H,2,1 },
    { PIO_P9H,3,1 },
    { PIO_P9H,4,1 },
    { PIO_P9H,5,1 },
    { PIO_P9H,6,1 },
    { PIO_P9H,7,1 },
    { PIO_PCD,0,1 },
    { PIO_PCD,1,1 },
    { PIO_PCD,2,1 },
    { PIO_PCD,3,1 },
    { PIO_PCD,4,1 },
    { PIO_PCD,5,1 },
    { PIO_PCD,6,1 },
    { PIO_PCD,7,1 },
    { PIO_PCT,0,1 },
    { PIO_PCT,1,1 },
    { PIO_PCT,2,1 },
    { PIO_PCT,3,1 },
    { PIO_PCT,4,1 },
    { PIO_PCT,5,1 },
    { PIO_PCT,6,1 },
    { PIO_PCT,7,1 },
    { PIO_PCS,0,1 },
    { PIO_PCS,1,1 },
    { PIO_PCS,2,1 },
    { PIO_PCS,3,1 },
    { PIO_PCS,4,1 },
    { PIO_PCS,5,1 },
    { PIO_PCS,6,1 },
    { PIO_PCS,7,1 },
    { PIO_PCM,0,1 },
    { PIO_PCM,1,1 },
    { PIO_PCM,2,1 },
    { PIO_PCM,3,1 },
    { PIO_PCM,4,1 },
    { PIO_PCM,5,1 },
    { PIO_PCM,6,1 },
    { PIO_PCM,7,1 },
    { PIO_PDLL,0,1 },
    { PIO_PDLL,1,1 },
    { PIO_PDLL,2,1 },
    { PIO_PDLL,3,1 },
    { PIO_PDLL,4,1 },
    { PIO_PDLL,5,1 },
    { PIO_PDLL,6,1 },
    { PIO_PDLL,7,1 },
    { PIO_PDLH,0,1 },
    { PIO_PDLH,1,1 },
    { PIO_PDLH,2,1 },
    { PIO_PDLH,3,1 },
    { PIO_PDLH,4,1 },
    { PIO_PDLH,5,1 },
    { PIO_PDLH,6,1 },
    { PIO_PDLH,7,1 },
    { PIO_PDH,0 ,1},
    { PIO_PDH,1 ,0},
    { PIO_PDH,2 ,1},
    { PIO_PDH,3 ,1},
    { PIO_PDH,4 ,1},
    { PIO_PDH,5 ,1},
    { PIO_PDH,6 ,1},
    { PIO_PDH,7 ,1},
};


