#ifndef   _UDS_APP_H
#define  _UDS_APP_H

#ifndef STATE_ON
#define STATE_ON		1
#endif

#ifndef STATE_OFF
#define STATE_OFF		0
#endif

typedef enum
{
	WORK_OK,
	WORK_RUN
}WORK_STATE_ENUM;

typedef enum
{
	ROUTINE_START = 1,
	ROUTINE_STOP,
	ROUTINE_REQRESULT,
}UDS_ROUTINE_ENUM;

typedef enum
{
	UDS_STATE_OFF,
	UDS_STATE_REQON,
	UDS_STATE_ON,
	UDS_STATE_END
}UDS_STATE_ENUM;

typedef enum
{
	MSG_TYPE_UUDT,
	MSG_TYPE_USDT
}UDS_MSG_TYPE;

typedef enum
{
	DIAG_IDLE,
	DIAG_SEND_SF,
	DIAG_SEND_FF,
	DIAG_SEND_CF,
	DIAG_SEND_FC,
	DIAG_SEND_RDBPI,
	DIAG_WAIT_CF,
	DIAG_WAIT_FC,
	DIAG_CF_RCV_END,
	DIAG_WAIT_EXIT
}UDS_STEP_ENUM;

typedef enum
{
	DWLD_IDLE = 0,
	DWLD_REQ =  1,
	DWLD_TRANS = 0x10,
}UDS_DWLD_STATE_ENUM;


typedef struct{
	uint16_t timer_N_Ar;
	uint16_t timer_N_As;
	uint16_t timer_N_Br;
	uint16_t timer_N_Bs;
	uint16_t timer_N_Cr;
	uint16_t timer_N_Cs;	
}UdsNetTimingParamStruct;

typedef struct{
	uint16_t timer_S3Server;
	uint16_t timer_S3Client;
}UdsAppTimingParamStruct;

typedef struct{
	uint8_t MessageType;                 	//diagnositcs , remote diagnostics
	//uint8_t SourceAddr;
	//uint8_t TargetAddr;
	uint8_t TargetAddrType;			//physical, functional
	uint8_t FrameType;
	uint8_t FlowStatus;
	uint8_t BlockSize;
	uint8_t STmin;
	uint8_t Time_Cs;
	uint8_t ServerRspStatus;
	uint8_t TimeBase;			/*UDS time base, unit is ms */
}UDS_NET_INFO;

typedef struct
{
	uint8_t SI; 	  		/*request service ID*/
	uint8_t SubFunc;
	uint8_t ParamLength; 	/*total response or con data len*/ 
	uint8_t suppressPosRspMsg;
	uint8_t Parameter[8]; 	/*data buffer*/
}N_UUDT;


typedef struct
{
	uint8_t SI; 	  		/*request service ID*/
	uint8_t SubFunc;
	uint16_t ParamLength; 	/*total response or con data len*/ 	
	uint8_t suppressPosRspMsg;
	uint8_t Parameter[N_BUFFER_SIZE]; /*data buffer */
}N_USDT;

typedef struct
{
	PDU_TYPE 	PduType;
	uint8_t 			FrameDataLen;/*SF_DL */
	uint8_t*			pData;
	N_UUDT 		A_Data;
}UUDT_PDU;



typedef struct
{
	PDU_TYPE  	PduType;
	uint16_t 			FrameDataLen;/*FF_DL,SN*/
	uint16_t			TransParamNum;
	uint8_t  			SN;
	uint8_t			LastSN;
	uint8_t  			BS;
	uint8_t			FS;
	uint8_t			STmin;
	uint8_t*			pData;
	N_USDT 		A_Data;
}USDT_PDU;

typedef struct{
	uint8_t SecurityAccess;
	uint8_t SecurityAccessStatus;
	uint8_t invalidSecurKeyCount;
	uint8_t ServerLockedFlag;
//	uint8_t SecurityKey[SECURITY_KEY_LENGTH];
	uint16_t LockedTime;
}UDS_SECUR_STATE;

typedef struct
{
	uint8_t   PeriodIdBuffer[PDID_MAX_NUM];
	uint8_t   IdNum;
	uint8_t   transmissionMode; 
	uint8_t   PeriodSendIndex;
	uint8_t   GapCount;
	uint8_t	GapValue;
	uint16_t   PeriodSendCount;
}RDBPI_INFO_STRUCT;


typedef struct{
	
	UDS_STATE_ENUM		ModuleState; 
	uint8_t CurMsgDealDoneFlag;
	uint8_t curFrameType;
	uint8_t LastFrameType;
	uint8_t CurServiceId;
	uint8_t curServiceIdInx;
	uint8_t suppressPosRspMsgIndBit;
	uint8_t ExitUnDefaultSessionReq;
	uint8_t DiagSessionType;
/* comm */
	uint8_t subControlType;
	uint8_t CommunicationType;
	uint8_t transmissionMode;
	UDS_SECUR_STATE	SecurityState;
	RDBPI_INFO_STRUCT RDBPI_Info;
}UDS_APP_INFO;

typedef struct
{
	uint8_t DTCSwitch;			// DTC setting on/off switch
	uint8_t DTCAvilabilityMask; 	//DTCStatusAvailabilityMask: supported state bit mask by the server
}DTCStateStruct;

typedef struct
{
	uint8_t IOControlState;
}UDS_IOC_StateStruct;

typedef struct
{
	uint8_t RoutineState;
	uint16_t RoutineId;
	uint8_t optionParam[5];
	uint8_t Result[10];
	uint8_t ResultLen;
}UDSRoutineStruct;

typedef struct
{
	uint8_t Step;
	uint8_t CompressionMode;
	uint8_t EncryptingMode;
	uint8_t AckMaxBlockSize;
	uint8_t Sequence;
	uint32_t MemoryStartAddr;
	uint8_t MemorySize;
}UDSDownLoadStateStruct;

typedef struct{
	unsigned short  request				:1;
	unsigned short  FF_indication			:1;
	unsigned short  indication			:1;
	unsigned short  confirm   			:1;
}NetCommServiceStruct;

typedef enum
{
	MSG_NCM 	= 0,			// normal application mesage
	MSG_NWMCM,				// Network management message
	MSG_UDS,				// UDS message
	MSG_NUMBER				//message type number
}MSG_TYPE_ENUM;
typedef enum
{
	MSG_TRANS_TX = 0x01,
	MSG_TRANS_RX = 0x02
}MSG_TRANS_TYPE;

typedef enum
{
	/*This value identifies a "hard reset" condition which simulates the power-on / start-up sequence 
	typically performed after a server has been previously disconnected from its power supply (i.e. 
	battery). The performed action is implementation specific and not defined by the standard. It 
	might result in the re-initialization of both volatile memory and non-volatile memory locations to 
	predetermined values. */
	UDS_ECUR_HARD 		= 1,	/* Hard Reset */
	/*This value identifies a condition similar to the driver turning the ignition key off and back on. This 
	reset condition should simulate a key-off-on sequence (i.e. interrupting the switched power 
	supply). The performed action is implementation specific and not defined by the standard. 
	Typically the values of non-volatile memory locations are preserved; volatile memory will be 
	initialized */
	UDS_ECUR_KEYOFFON,		/*Key off-on Reset */
	/*This value identifies a "soft reset" condition, which causes the server to immediately restart the 
	application program if applicable. The performed action is implementation specific and not 
	defined by the standard. A typical action is to restart the application without reinitializing of 
	previously learned configuration data, adaptive factors and other long-term adjustments. */
	UDS_ECUR_SOFT			/*Soft reset */
}ECUR_TYPE_ENUM;

typedef enum
{
	/*This value shall indicate to the server that the client does no longer have control about the input 
       signal, internal parameter or output signal referenced by the inputOutputLocalIdentifier. */
	IOC_returnControlToECU		=0,
	/*  This  value  shall  indicate  to  the  server  that  it  is  requested  to  reset  the  input  signal,  internal 
	parameter or output signal referenced by the inputOutputLocalIdentifier to its default state.  */
	IOC_resetToDefault			=1,
	/* This value shall indicate to the server that it is requested to freeze the current state of the input 
	signal, internal parameter or output signal referenced by the inputOutputLocalIdentifier. */
	IOC_freezeCurrentState		=2,
	/*This  value  shall  indicate  to  the  server  that  it  is  requested  to  adjust  the  input  signal,  internal 
	parameter  or  output  signal  referenced  by  the  inputOutputLocalIdentifier  in  RAM  to  the  value(s) 
	included  in  the  controlOption  parameter(s).  (e.g.  set  Idle  Air  Control  Valve  to  a  specific  step 
	number, set pulse width of valve to a specific value/duty cycle).  */
	IOC_shortTermAdjustment	=3,
}IOC_PARAM_ENUM;


extern UDS_NET_INFO 			UdsNetInfo;
extern UDS_APP_INFO   			UdsAppInfo;
extern UUDT_PDU				UUDT_PduR_Msg;
extern USDT_PDU				USDT_PduR_Msg;
extern USDT_PDU				USDT_PduT_Msg;


UDS_EXTERN 	void 	Uds_ProtocolStackMain(void);
UDS_EXTERN 	uint8_t 	Uds_GetMsgDealState(void);
UDS_EXTERN	uint8_t 	Uds_GetMsgTransEnableState(MSG_TYPE_ENUM MsgType, MSG_TRANS_TYPE TransType);
/****************************************************************************
 * @function	Uds_GetDTCSettingState
 * @brief  	Get DTC setting state
 * @param  	null
 * @retval 	STATE_ON/ STATE_OFF
****************************************************************************/
UDS_EXTERN	 uint8_t 	Uds_GetDTCSettingState(void);
UDS_EXTERN	 void 	Uds_ColdInit(void);
UDS_EXTERN   void Uds_CommControlInit(void);
UDS_EXTERN   void Uds_DTCSwitchInit(void);

UDS_EXTERN	 void   	Uds_TimerHandler(void);
UDS_EXTERN	 void 	Uds_Close(void);

UDS_EXTERN   void 	Uds_ClearDTCInfoHook(void);
UDS_EXTERN	 void 	Uds_UserIOControlHook(uint8_t index);


#endif

/****************************************************************************
 * **                                        FILE END
****************************************************************************/


