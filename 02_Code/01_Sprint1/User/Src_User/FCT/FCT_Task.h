#ifndef _TASK_FCT_H
#define _TASK_FCT_H
//关于文件描述的注释
//包含文件
//常量定义
//宏函数定义
//类型定义
//全局变量定义
//内部变量定义
//外部函数说明
//内部函数说明
 #include "FctMsgDef.H "

#ifdef _TASK_FCT_C
#define _FCT_ 
#else
#define _FCT_  extern
#endif

#define _SendMsgToFCT(gid,sid,buf)                OS_PostMsgDir(&g_tFCT.tFctTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf))
#define _SendFullMsgToFCT(id,op,d0,d1,d2,d3)   OS_PostFullMsgDir(&g_tFCT.tFctTaskCB,(MSG_ID)id, (uint16_t)op, (uint8_t)d0, (uint8_t)d1, (uint8_t)d2, (uint8_t)d3)


#define D_FCT_WAIT_ACK_EN    0   // MCU是否等待PC端的每条指令的应答信号  PC端  1: 应答。0: 不应答

#define RESULT_FINISH    1
#define RESULT_DEFEAT    0

#define LOGIC_1            1
#define FCT_HEAD_FIRST         0xEE
#define FCT_HEAD_SECOND    0xFA


#define TOMCU_RX_COM_SIZE          8
#define TOPC_TX_COM_SIZE          8
#define MCU_PC_BUFF_SIZE          40

#define D116_DESIGN_TEAM        0
#define V6_DESIGN_TEAM            1
#define HQ10_DESIGN_TEAM        2

#define REP_STATE_NULL            0
#define NACK_DELAYMS_WAIT        1
#define ACK_ERROR                 2

#define  RDS_INFO                8
#define  BT_INFO			60
#define  BT_MAC_ADD		20
#define  BT_DEV_NAME	20
#define  BT_SOFT_VER		20
#define  BT_DIAL_UP_NUM	23

#define  GPS_INFO                11
#define  TMPS_INFO                11
#define  AUDIO_SET_VAL            19
#define  VIDEO_SET_VAL            3
#define  WIFI_AP_NAME_PIN      19
#define  SEQ_NUM_39                40
#define  SOFT_VER_40                40

#define  SOFT_OS_VER_25            25
#define  SOFT_BOOT_VER_25        25
#define  SOFT_APP_VER_30        30
#define  SOFT_MCU_VER_30        29
#define  SOFT_MPEG_VER_39        39
#define  SOFT_DIVX_VER_13        13
#define  SOFT_UUID_VER_19        19
#define  SOFT_WIFI_VER_20        20
#define  SOFT_MAP_VER_25        25

typedef enum
{
    RETURN_NULL ,
    RETURN_VERDICT_RESULT,
    RETURN_DATA_RESULT,
} RetuenType;

typedef struct  _fct_receive_format_def
{
     uint8_t uLength ;
     uint8_t uGlobal_ID ;
     uint8_t uSub_ID ;
     uint8_t uDataType ;
     uint8_t uCRC ;
}FCT_REC_FORMAT ;


typedef struct 
{
    uint8_t cRxRecIndex ;
    uint8_t uRxProcessIndex ;
    uint8_t Ia_RxBuff[TOMCU_RX_COM_SIZE][MCU_PC_BUFF_SIZE];
    uint8_t RxLength ;
    uint8_t RXCRC ;
    uint8_t RxCount ;
}TOMCU_Rx;

typedef struct 
{
    uint8_t uTxRecIndex ;
    uint8_t uTxProcessIndex ;
    uint8_t Ia_TxBuff[TOPC_TX_COM_SIZE][MCU_PC_BUFF_SIZE];
    uint8_t* gpUarta3TxAddress;     /* uarta2 transmit buffer address */
    uint8_t   gUarta3TxCnt;        /* uarta2 transmit data number */
    uint8_t  SAskArray[8];
}TOPC_Tx;

typedef struct
{
    uint8_t RdsInfo_10[RDS_INFO];
	
  //  uint8_t BTVerMacAdd_16[BT_INFO];
    uint8_t BTMacAdd_16[BT_MAC_ADD];
    uint8_t BTMacAddL;
    uint8_t BTDevName_16[BT_DEV_NAME];
    uint8_t BTDevNameL;
    uint8_t BTVer_16[BT_SOFT_VER];
    uint8_t BTVerL;
    uint8_t BTDialNum_16[BT_DIAL_UP_NUM];
    uint8_t BTDialNumL;
	
    uint8_t GPSInfo_22[GPS_INFO];
    uint8_t GPSInfoL;
    uint8_t TmpsInfo_26[TMPS_INFO];
    uint8_t AudioSet_30[AUDIO_SET_VAL];    
    uint8_t VideoSet[VIDEO_SET_VAL];    
    uint8_t WifiApNamePin[WIFI_AP_NAME_PIN];    
    uint8_t WifiApNamePinL;    
    uint8_t SeqNum_39[SEQ_NUM_39];
    uint8_t SeqNumL;
    uint8_t SoftVer_40[SOFT_VER_40];
    uint8_t SoftVerL;
    uint8_t SrcBackup;
	
#if 0
    uint8_t SoftOsVer_25[SOFT_OS_VER_25];
    uint8_t SoftBootVer_25[SOFT_BOOT_VER_25];
    uint8_t SoftAppVer_30[SOFT_APP_VER_30];
    uint8_t SoftMcuVer_30[SOFT_MCU_VER_30];
    uint8_t SoftMpegVer_39[SOFT_MPEG_VER_39];
    uint8_t SoftDivxVer_13[SOFT_DIVX_VER_13];
    uint8_t SoftUuidVer_19[SOFT_UUID_VER_19];
    uint8_t SoftWifiVer_20[SOFT_WIFI_VER_20];
    uint8_t SoftMapVer_25[SOFT_MAP_VER_25];
#endif
    
}DataBuf_t;

typedef union fct_info_struct
{
       unsigned char a_cData[sizeof(void*)];
       void*         p_cData;
}FCT_INFO_STRUCT;


typedef enum
{
    FCT_FRAME_HEAD_FIRST,
    FCT_FRAME_HEAD_SECOND,
    FCT_FRAME_LENGH,
    FCT_FRAME_DATA,
    FCT_FRAME_CRC,
    FCT_ACK_DATA,
    FCT_ACK_CRC,
    FCT_PASSWORD_DATA,
    FCT_PASSWORD_CRC,
}FCT_UartRecDataStep;



typedef struct
{
    unsigned RecFullFrameFlag        :    1 ;
    unsigned SendFullFrameFlag        :    1 ;
    unsigned AckFlag                :    1 ;
    unsigned AutoTestFlag            :    1 ;
    unsigned PasswordFlag            :    1 ;
    unsigned RepeatFlag            :    1 ;
    unsigned CommunicationOver    :    1 ;
    unsigned SendOKWaitAck        :    1 ;
}FCTFlagBitDef;

typedef union
{
    uint8_t  Byte ;
    FCTFlagBitDef  tBit ;
}FCTFlagDef;


typedef struct
{
    unsigned StateSameFlag    :    1 ;
    unsigned Reserve1        :    1 ;
    unsigned Reserve2        :    1 ;
    unsigned reserve3        :    1 ;
    unsigned reserve4        :    1 ;
    unsigned reserve5        :    1 ;
    unsigned reserve6        :    1 ;
    unsigned reserve7        :    1 ;
}FCTMsgFlagBitDef;

typedef union
{
    uint8_t  Byte ;
    FCTMsgFlagBitDef  tBit ;
}FCTMsgFlagDef;



typedef struct
{
    uint8_t SendArray[130];
    uint8_t RepSendCount;
    uint8_t RepSendCause;
}FCT_AckSystem;

typedef enum
{
    PASSWORD_STATE,
    WAIT_ACK_STATE,
    REPEAT_STATE,
    WORK_STATE,
} PcMessageManagerState;
typedef struct 
{
uint8_t cAckErrorCoun ;
uint16_t u16NoAckCount;    
uint16_t u16TempTimer ;    
uint16_t u16TUpdataMsgToPcTimer ;    
uint8_t cReMsgDelay ;    
}sFctCount;

typedef struct
{
    sFctCount tFctCount;
     FCTFlagDef    tFlagDef ;
    FCTMsgFlagDef tFCTMsgDef ;     
     FCT_UartRecDataStep   tUartRecDataStep;
     FCT_REC_FORMAT        tSendFormat;
     FCT_AckSystem    tAckSystem;
     TOMCU_Rx    tTomcuRx;
     TOPC_Tx       tTopcTx;
     FCT_INFO_STRUCT   sFctInfo ;
     DataBuf_t   tDataBuf ;
     PcMessageManagerState  tPcMesMagState;
     tTASK_CTRL_BLOCK  tFctTaskCB; 
     tMSG_BUF   ptFctMsg ;
} sFCT_BLOCK;

_FCT_  sFCT_BLOCK g_tFCT ;

#define FCT_REC_FLAG             g_tFCT.tFlagDef.tBit.RecFullFrameFlag 
#define FCT_SEND_FLAG            g_tFCT.tFlagDef.tBit.SendFullFrameFlag 
#define FCT_ASK_FLAG              g_tFCT.tFlagDef.tBit.AckFlag 
#define FCT_FLAG                      g_tFCT.tFlagDef.tBit.AutoTestFlag 
#define FCT_PASSWORD_FLAG    g_tFCT.tFlagDef.tBit.PasswordFlag 
#define FCT_REPEAT_FLAG        g_tFCT.tFlagDef.tBit.RepeatFlag 
#define FCT_COM_OVER_FLAG    g_tFCT.tFlagDef.tBit.CommunicationOver 
#define SEND_OK_WAIT_ACK    g_tFCT.tFlagDef.tBit.SendOKWaitAck 


#define ACK_MAIN_COM    g_tFCT.tAckSystem.SendArray[1]
#define ACK_SUB_COM      g_tFCT.tAckSystem.SendArray[2]

#define PC_TO_FCT_GID   g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][1]
#define PC_TO_FCT_SID   g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][2]



_FCT_  void FCT_UartRecMessage (uint8_t R_Data);
_FCT_  void FCT_SendDataResult (uint8_t S_MainCom ,  uint8_t S_SubCom, uint8_t *S_Data , uint8_t Length);
_FCT_  void FCT_SendFullDataResult (uint8_t S_MainCom ,  uint8_t S_SubCom, uint8_t Data0 , uint8_t Data1 ,uint8_t Data2 ,uint8_t Data3,uint8_t Length);
_FCT_  void FCT_SendAsk( uint8_t AskType, uint8_t Gid, uint8_t Sid);
_FCT_  void FCT_SendFCTEnter(void );
_FCT_  void FCT_SendFCTOut(void );
_FCT_  void FCT_Password(void);
_FCT_  uint8_t FCT_GetPasswordFlag(void);
_FCT_  void FCT_SetPasswordFlag( uint8_t State);
_FCT_  uint8_t FCT_GetSwFlag(void);
_FCT_  void FCT_SetSwFlag( uint8_t State);
_FCT_  uint8_t FCT_GetRepeatFlag(void);
_FCT_  void FCT_SetRepeatFlag( uint8_t State);
_FCT_  uint8_t FCT_GetComOverFlag(void);
_FCT_  void FCT_SetComOverFlag( uint8_t State);
_FCT_  uint8_t FCT_GetSendOKWaitAckFlag(void);
_FCT_  void FCT_SetSendOKWaitAckFlag( uint8_t State);
_FCT_  void FCTInit(void);
_FCT_  uint8_t FCT_ColdOrWarmInit(void) ;
_FCT_  void FCT_PasswordManage(void);
_FCT_  void FCT_RepeatSendCountZero(void);
_FCT_  void FCT_SetRepSendCause(uint8_t uCause);
_FCT_  void FCT_SendRepeatManage(void);
_FCT_  void  FCT_HmiIdToPcId(uint8_t Gid, uint8_t Sid, tMSG_BUF* p_tMsgBuf );
_FCT_  uint8_t FCT_PcIdToHmiId(uint8_t Gid,uint8_t Sid);
_FCT_  void FCT_WorkManager(void);
_FCT_  uint8_t *  FCT_ArrayDataUp(uint8_t * Array, uint8_t Length);
_FCT_   void FCT_DataBufAdd (uint8_t  Global_ID,uint8_t  S_ID, uint8_t Length);
_FCT_  void FCT_MsgToHmiHandler(void);
_FCT_  void FCT_DataBufToPc(uint8_t Sid, uint8_t ReturnGid ,uint8_t  ReturnSid, uint8_t Array);
_FCT_  void  FCT_MsgToPcHandler(tMSG_BUF* p_tMsgBuf);
_FCT_  void Task_FCT(EVENT iEvt,eTASK_STATE state);
_FCT_  uint8_t FCT_TaskCreat(void);
_FCT_  void FCT_SetManagerState(uint8_t uState);
_FCT_  void FCT_UARTA3_Init(void);
_FCT_  void FCT_UARTA3_Start(void);
_FCT_  void isrFCT_INTUA3R(void);
_FCT_  void isrFCT_INTUA3T(void);
_FCT_  uint8_t FCT_UARTA3_SendData(uint8_t* txbuf, uint8_t txnum);
_FCT_  void HMI_FCT_Handle(tMSG_BUF* p_tMsg);
_FCT_  uint8_t  FCT_DataResultToPc(tMSG_BUF* p_tMsg);
_FCT_  void SetUpdataMsgToPcTimer(uint16_t  Val);
_FCT_  void FctMediaMsgHandler(uint8_t *pFctMedia);
_FCT_  uint8_t FCT_GetStateSameFlag(void) ;
_FCT_  void FCT_SetStateSameFlag( uint8_t State);
_FCT_  void FctApuTxMcuMsg(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen);
_FCT_  void FctTest(void);
_FCT_  void FctSetSrcBackup(uint8_t SrcCur ) ;


#endif

