/*     7     6     5     4     3     2     1    0
IICCn IICEn LRELn WRELn SPIEn WTIMn ACKEn STTn SPTn
*/
#pragma pack(1)
typedef union{
    uint8_t byte;
     struct{
        bit_t    SPT:1;
        bit_t    STT:1;
        bit_t    ACKE:1;
        bit_t    WTIM:1;
        bit_t    SPIE:1;
        bit_t    WREL:1;
        bit_t    IREL:1;
        bit_t    EN:1;
    }field;
}reg_IICCn_t;

/*     7     6     5   4    3     2     1    0
IICSn MSTSn ALDn EXCn COIn TRCn ACKDn STDn SPDn
*/
#pragma pack(1)    
typedef union{
    uint8_t byte;
     struct{
        bit_t    SPD:1;
        bit_t    STD:1;
        bit_t    ACKD:1;
        bit_t    TRC:1;
        bit_t    COI:1;
        bit_t    EXC:1;
        bit_t    ALD:1;
        bit_t    MSTS:1;
    }field;
}reg_IICSn_t;


/*     7     6      5 4 3 2   1      0
IICFn STCFn IICBSYn 0 0 0 0 STCENn IICRSVn
*/
#pragma pack(1)
typedef union{
    uint8_t byte;
     struct{
        bit_t    RSV:1;
        bit_t    STCEN:1;
        bit_t    rev:4;
        bit_t    BSY:1;
        bit_t    STCF:1;
    }field;
}reg_IICFn_t;

/*     7 6   5    4    3    2   1     0
IICCLn 0 0 CLDn DADn SMCn DFCn CLn1 CLn0
*/
#pragma pack(1)
typedef union{
    uint8_t byte;
     struct{
        bit_t    CL0:1;
        bit_t    CL1:1;
        
        bit_t    DFC:1;
        bit_t    SMC:1;
        bit_t    DAD:1;
        bit_t    CLD:1;
        bit_t    rev:2;
    }field;
}reg_IICCLn_t;



#define reg_i2c_add_offset                      0x10
#define regIICD0 (uint8_t*)0xFFFFFD80 
#define regIICD1 (uint8_t*)0xFFFFFD90 
#define regIICD2 (uint8_t*)0xFFFFFDA0 
#define regIICDn_BASS (void*)0xFFFFFD80 

#define regIICC0 (reg_IICCn_t*)0xFFFFFD82 
#define regIICC1 (reg_IICCn_t*)0xFFFFFD92 
#define regIICC2 (reg_IICCn_t*)0xFFFFFDA2 
#define regIICCn_BASS (void*)0xFFFFFD82 

#define regIICS0 (reg_IICSn_t*)0xFFFFFD86 
#define regIICS1 (reg_IICSn_t*)0xFFFFFD96 
#define regIICS2 (reg_IICSn_t*)0xFFFFFDA6 
#define regIICSn_BASS (void*)0xFFFFFD86 

#define regIICF0 (reg_IICFn_t*)0xFFFFFD8A 
#define regIICF1 (reg_IICFn_t*)0xFFFFFD9A 
#define regIICF2 (reg_IICFn_t*)0xFFFFFDAA 
#define regIICFn_BASS (void*)0xFFFFFD8A 


#define regIICSVA0 (uint8_t*)0xFFFFFD83 
#define regIICSVA1 (uint8_t*)0xFFFFFD93 
#define regIICSVA2 (uint8_t*)0xFFFFFDA3 
#define regIICSVAn_BASS (void*)0xFFFFFD83 

#define regIICCL0 (reg_IICCLn_t*)0xFFFFFD84 
#define regIICCL1 (reg_IICCLn_t*)0xFFFFFD94 
#define regIICCL2 (reg_IICCLn_t*)0xFFFFFDA4 
#define regIICCLn_BASS (void*)0xFFFFFD84 

#define regIICX0 (byte_field*)0xFFFFFD85 
#define regIICX1 (byte_field*)0xFFFFFD95 
#define regIICX2 (byte_field*)0xFFFFFDA5 
#define regIICXn_BASS (void*)0xFFFFFD85 

#define regOCKS0  (void*)0xFFFFF340 
#define regOCKS1  (void*)0xFFFFF344 

////////////////////////////////////////////////////////////////////////////////
#define D_WAIT_START_CONDITION_LOOP  1000


typedef enum{
    I2C0,
    I2C1,
    I2C2,

    I2CN
}eI2C_TYPE;


typedef enum{
    I2C_0kbps,
    
    I2C_74KBPS,
    I2C_96KBPS,
    I2C_350KBPS,

    I2C_SPEED_n
}eI2C_SPEED;

//命令返回状态值
typedef enum{
    I2C_RET_IDLE,       //i2c正空闲
    I2C_RET_WAIT,       //等待操作返回
    I2C_RET_SUCCESS,    //操作结束
    I2C_RET_ERR,        //操作出错
    I2C_RET_TIMEOUT,
#ifdef D_TW8836_I2C0_EN
    I2C_RET_NOSUBADDR,
#endif
    I2C_RET_NUM
}eI2C_RET;

typedef enum{
    I2C_ERR_NONE,
    I2C_ERR_HW,
    I2C_ERR_QUE,
    I2C_ERR_BUSY,
    I2C_ERR_START,
    I2C_ERR_ADD,
    I2C_ERR_ACK,
    I2C_ERR_STOP,
    I2C_ERR_TIMEOUT,
    I2C_ERR_RESUME,

    I2C_ERR_NUM,
}eI2C_ERROR;


//命令类型定义
typedef enum{
    I2C_NCMD,
    I2C_CMD_CHK,
    I2C_CMD_WRITE_DEFAULT,
    I2C_CMD_WRITE_SUBADD,
    I2C_CMD_READ_DEFAULT,
    I2C_CMD_READ_SUBADD,

    I2C_CMD_n
    
}eI2C_CMD;
//
//设备命令块
//
#define D_I2C_DEV_QUE_DEEP   10             //驱动队列深度  
#define D_I2C_DEV_BUFF_LEN   10             //缓冲区长度
typedef uint8_t (*fCALL_BACK)(uint8_t);         //返回1，重启动I2C

#pragma pack(1)
typedef union{
    uint8_t*      p_cRet;
    fCALL_BACK   p_fFunc;
}uI2C_CALL_BACK;

#pragma pack(1)
typedef struct _i2c_cmd_block{  
    eI2C_CMD           eCmd;
    eI2C_SPEED         eSpeed;
    uint8_t            cAddr;
    uint8_t            eSubAddr;
    uint8_t            cLen; 
    
    union{
         struct{
             bit_t       bCallBackIsFunc :1;
             bit_t       bDataIsPoint    :1;
             bit_t       rev:6;
         }tField;
         uint8_t cByte;
    }uFlag; 
    
    union{
        uint8_t*           p_cBuff;
        uint8_t            a_cBuff[D_I2C_DEV_BUFF_LEN];
    }uData;
    
    uI2C_CALL_BACK  uCallBack;
    
}tI2C_CMD_BLOCK;




//
//I2C寄存器映射表
//
#pragma pack(1)
typedef struct{
    //控制寄存器
    void*  Dn_reg;
    void*  Cn_reg;
    void*  CLn_reg;
    void*  Fn_reg;
    void*  Sn_reg;
    void*  SVAn_reg;
    void*  Xn_reg;
    void*  ICn_reg;

    //端口寄存器
    void*  P_reg;
    void*  PM_reg;
    void*  PMC_reg;
    void*  PF_reg;
    void*  PFC_reg;
    void*  PFCE_reg;
    
    uint8_t SCL;
    uint8_t SDA;      
}tI2C_REG_ADD;



_V850_ bool I2C_DeviceInit(eI2C_TYPE,bool);
_V850_ void I2C_DeviceSetSpeed(eI2C_TYPE,eI2C_SPEED);
_V850_ uint8_t I2C_DeviceRelease(eI2C_TYPE n);
_V850_ uint8_t I2C_DeviceStart(eI2C_TYPE,tI2C_CMD_BLOCK*,uint8_t*);
_V850_ void isrI2C0_Comm(void);
_V850_ void isrI2C1_Comm(void);
_V850_ void isrI2C2_Comm(void);


