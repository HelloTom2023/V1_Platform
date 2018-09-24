/****************************************************************************
* copyright:		JX Coagent Co.ltd.
* filename:		CANbus_AppLayer.c
* Target MCU:		Common Protocol Stack Source File
* Module:
* Summary:		Road vehicles---Unified diagnostic services(UDS),
*				Based on ISO_DIS14229-1_2005, IS015765-1,2,3,
*				Some Service is based on CHANGAN diagnostic reference.
*----------------------------------------------------------------------------
* Author:			zhaowenlong
* version:			V0.1
* Date:			2013-5-10
* Description:		first version
*----------------------------------------------------------------------------
* Modify:			
* version:
* Date:
* Description:
****************************************************************************/
#define _UDS_MODULE_C
#include "..\..\..\config\inc.h"


#ifdef UDS_ENABLE_MACRO


UdsNetTimingParamStruct  	UdsNetTimingParam;
UdsAppTimingParamStruct   	UdsAppTimingParam;
UDS_NET_INFO 			UdsNetInfo;
UDS_APP_INFO   			UdsAppInfo;
UUDT_PDU				UUDT_PduR_Msg;
USDT_PDU				USDT_PduR_Msg,USDT_PduT_Msg;
DTCStateStruct			UdsDTCState;
#if UDS_SVC_RC_EN
UDSRoutineStruct			UdsRoutineState;
#endif
#if UDS_SVC_IOCBI_EN
UDS_IOC_StateStruct		UdsIOCState;
#endif
#if UDS_SVC_RD_EN
UDSDownLoadStateStruct	UdsDownLoadState;
#endif
static uint8_t  				MsgCommCfgTbl[3];

#define SubFunctionSupport(index)              (UdsServiceCfgTbl[index].subFuntion)

void Uds_ServiceHandler(UDS_MSG_TYPE MsgType, uint8_t curServiceIdInx);

/****************************************************************************
 * @function	Uds_BusMsgConfig
 * @brief  	According the UDS service, config the Message comm TX/RX state
 * @param  	null
 * @retval 	null
****************************************************************************/
void Uds_BusMsgConfig(void)
{
	uint8_t index1 = 0xff;
	uint8_t index2 = 0xff;

	switch(UdsAppInfo.CommunicationType)
	{
		case COMM_TYPE_NCM:
			index1 = MSG_NCM;
			break;
		case COMM_TYPE_NWMCM:
			index1 = MSG_NWMCM;
			break;
		case COMM_TYPE_NCM_NWMCM:
			index1 = MSG_NCM;
			index2 = MSG_NWMCM;
			break;
		default:
			break;
	}
	switch(UdsAppInfo.subControlType)
	{
		case COMM_ENRX_ENTX:
			if(index1!= 0xff)
			{
				MsgCommCfgTbl[index1] = (index1<<4) |MSG_TRANS_TX|MSG_TRANS_RX;
			}
			if(index2!= 0xff)
			{
				MsgCommCfgTbl[index2] = (index2<<4) |MSG_TRANS_TX|MSG_TRANS_RX;
			}
			break;
		case COMM_ENRX_DSTX:
			if(index1!= 0xff)
			{
				MsgCommCfgTbl[index1] = (index1<<4) |MSG_TRANS_RX;
			}
			if(index2!= 0xff)
			{
				MsgCommCfgTbl[index2] = (index2<<4) |MSG_TRANS_RX;
			}
			break;
		case COMM_DSRX_ENTX:
			if(index1!= 0xff)
			{
				MsgCommCfgTbl[index1] = (index1<<4) |MSG_TRANS_TX;
			}
			if(index2!= 0xff)
			{
				MsgCommCfgTbl[index2] = (index2<<4) |MSG_TRANS_TX;
			}
			break;
		case COMM_DSRX_DSTX:
			if(index1!= 0xff)
			{
				MsgCommCfgTbl[index1] = (index1<<4);
			}
			if(index2!= 0xff)
			{
				MsgCommCfgTbl[index2] = (index2<<4);
			}
			break;
		default:
			break;
	}

	//在开启通信的时候,增加以下对全部报文的发送请求
	if(TRUE == Uds_GetMsgTransEnableState(MSG_NCM, MSG_TRANS_TX))
	{
		CANUser_SendMsg500();
		CANUser_SendMsg501();
		CANUser_SendMsg2F8();
	}
}

/****************************************************************************
 * @function	Uds_GetMsgTransEnableState
 * @brief  	Get the message COMM state
 * @param  	MsgType: refer the	MSG_TYPE_ENUM
 *			TransType: MSG_TRANS_TX//MSG_TRANS_RX
 * @retval 	TRUE: enable
 *			FALSE:disable
****************************************************************************/
uint8_t Uds_GetMsgTransEnableState(MSG_TYPE_ENUM  MsgType, MSG_TRANS_TYPE TransType)
{
	if(MsgType>MSG_UDS)
	{
		return FALSE;
	}
	if(TransType == MSG_TRANS_TX || TransType == MSG_TRANS_RX)
	{
		if(MsgCommCfgTbl[MsgType]&TransType)
		{
			return TRUE;
		}
	}
	return FALSE;
}

/****************************************************************************
 * @function	Uds_GetDTCSettingState
 * @brief  	Get DTC setting state
 * @param  	null
 * @retval 	STATE_ON/ STATE_OFF
****************************************************************************/
uint8_t Uds_GetDTCSettingState(void)
{
	return UdsDTCState.DTCSwitch;
}

static void Uds_RefreshDid_ADS(void)
{
	uint8_t i;
	/*write the session mode */
	i = Uds_GetDidIndex(DID_ADS);
	if(0xff != i)
	{
		DID_STRUCT *pTbl = Uds_GetDIDCfgTable();
		pTbl[i].pParam[0] = UdsAppInfo.DiagSessionType;
		pTbl[i].ByteLen = 1;
	}
	/*-----------------------------*/
}

/****************************************************************************
 * @function	Uds_DefaultInit
 * @brief  	UDS defaultInit
 * @param  	null
 * @retval 	null
****************************************************************************/
void Uds_DefaultInit(void)
{
	UdsAppInfo.ModuleState 		= UDS_STATE_OFF;
	UdsAppInfo.CurMsgDealDoneFlag	= WORK_OK;
	UdsAppInfo.curFrameType 		= NULL_NPCI;

	UdsAppInfo.SecurityState.SecurityAccess = UDS_LOCKED_STATE;
	UdsAppInfo.SecurityState.SecurityAccessStatus 	=UDS_SA_IDLE;
	UdsAppInfo.SecurityState.invalidSecurKeyCount	=0; 
	UdsAppInfo.SecurityState.ServerLockedFlag = UDS_UNLOCKED_STATE;
	
	UdsAppInfo.DiagSessionType		=SESSION_DEFAULT;

	UdsAppInfo.RDBPI_Info.transmissionMode = 0x04;

	UdsNetInfo.ServerRspStatus		 =DIAG_IDLE;
	UdsNetInfo.TimeBase				 =TIMER_BASE;

	UdsDTCState.DTCAvilabilityMask 	= 0xff;
#if UDS_SVC_IOCBI_EN
	UdsIOCState.IOControlState 		= 0;
#endif
#if UDS_SVC_RC_EN
	UdsRoutineState.RoutineState		= ROUTINE_STOP;
#endif
#if (UDS_SVC_RD_EN ||UDS_SVC_RU_EN)
	UdsDownLoadState.Step			= DWLD_IDLE;
#endif

	UdsNetTimingParam.timer_N_Ar	= 0;
	UdsNetTimingParam.timer_N_As	= 0;
	UdsNetTimingParam.timer_N_Br	= 0;
	UdsNetTimingParam.timer_N_Bs	= 0;
	UdsNetTimingParam.timer_N_Cr	= 0;
	UdsNetTimingParam.timer_N_Cs	= 0;
	UdsAppTimingParam.timer_S3Server = 0;

	Uds_CANInit();

	Uds_RefreshDid_ADS();
}

/****************************************************************************
 * @function	Uds_ColdInit
 * @brief  	Cold start UDS initialization
 * @param  	null
 * @retval 	null
****************************************************************************/
void Uds_ColdInit(void)
{
	Uds_DefaultInit();
	/*
	UdsAppInfo.subControlType		=COMM_ENRX_ENTX; 
	UdsAppInfo.CommunicationType	=COMM_TYPE_NCM_NWMCM; 
	UdsDTCState.DTCSwitch 			= STATE_ON;
	Uds_BusMsgConfig();
	*/
	Uds_DTCSwitchInit();
	Uds_CommControlInit();
	hmi_printf(_T("-----uds_ColdInit-------\n"));
}

/****************************************************************************
 * @function	Uds_CommControlInit
 * @brief  	warm start UDS initialization CommControl param
 * @param  	null
 * @retval 	null
****************************************************************************/
void Uds_CommControlInit(void)
{
	UdsAppInfo.subControlType		=COMM_ENRX_ENTX; /*enable RX & TX*/
	UdsAppInfo.CommunicationType	=COMM_TYPE_NCM_NWMCM; 
	Uds_BusMsgConfig();
}

/****************************************************************************
 * @function	Uds_DTCSwitchInit
 * @brief  	warm start UDS initialization DTC Switch param
 * @param  	null
 * @retval 	null
****************************************************************************/
void Uds_DTCSwitchInit(void)
{
	UdsDTCState.DTCSwitch 			= STATE_ON;
}

/****************************************************************************
 * @function	Uds_EnterWorkInit
 * @brief  	enter UDS work mode init
 * @param  	null
 * @retval 	null
****************************************************************************/
void Uds_EnterWorkInit(void)
{
	UdsAppInfo.CurMsgDealDoneFlag	= WORK_OK;
	UdsAppInfo.DiagSessionType		=SESSION_DEFAULT;
	UdsNetInfo.ServerRspStatus		=DIAG_IDLE;
	UdsAppInfo.SecurityState.SecurityAccess = UDS_LOCKED_STATE;

	UdsNetTimingParam.timer_N_Ar	= 0;
	UdsNetTimingParam.timer_N_As	= 0;
	UdsNetTimingParam.timer_N_Br	= 0;
	UdsNetTimingParam.timer_N_Bs	= 0;
	UdsNetTimingParam.timer_N_Cr	= 0;
	UdsNetTimingParam.timer_N_Cs	= 0;
	UdsAppTimingParam.timer_S3Server = 0;

	Uds_CANInit();

	Uds_RefreshDid_ADS();
}

/****************************************************************************
 * @function	Uds_GetMsgDealState
 * @brief  	enter UDS message deal state
 * @param  	null
 * @retval 	1: done, 0: not done
****************************************************************************/
uint8_t Uds_GetMsgDealState(void)
{
	if(UdsAppInfo.ModuleState == UDS_STATE_OFF)
	{
		UdsAppInfo.CurMsgDealDoneFlag = WORK_OK;
	}
	return UdsAppInfo.CurMsgDealDoneFlag;
}

/****************************************************************************
 * @function	Uds_NetTimerHandler
 * @brief  	UDS netlayer Timing parameter handler
 * @param  	null
 * @retval 	null
****************************************************************************/
void Uds_NetTimerHandler(void)
{

	if(UdsNetTimingParam.timer_N_Ar>0)
	{
		UdsNetTimingParam.timer_N_Ar--;
	}
	if(UdsNetTimingParam.timer_N_As>0)
	{
		UdsNetTimingParam.timer_N_As--;
	}
	if(UdsNetTimingParam.timer_N_Br>0)
	{
		UdsNetTimingParam.timer_N_Br--;
	}
	if(UdsNetTimingParam.timer_N_Bs>0)
	{
		UdsNetTimingParam.timer_N_Bs--;
	}
	if(UdsNetTimingParam.timer_N_Cr>0)
	{
		UdsNetTimingParam.timer_N_Cr--;
	}
	if(UdsNetTimingParam.timer_N_Cs>0)
	{
		UdsNetTimingParam.timer_N_Cs--;
	}
}

/****************************************************************************
 * @function	Uds_AppTimerHandler
 * @brief  	UDS application layer Timing parameter handler
 * @param  	null
 * @retval 	null
****************************************************************************/
void Uds_AppTimerHandler(void)
{
	if(UdsAppInfo.DiagSessionType != SESSION_DEFAULT)
	{
	/*	if(UdsAppTimingParam.timer_S3Client>=UdsNetInfo.TimeBase)
		{
			UdsAppTimingParam.timer_S3Client-=UdsNetInfo.TimeBase;
		}*/
		if(UdsAppTimingParam.timer_S3Server>=UdsNetInfo.TimeBase)
		{
			UdsAppTimingParam.timer_S3Server-=UdsNetInfo.TimeBase;
			if(UdsAppTimingParam.timer_S3Server < UdsNetInfo.TimeBase)
			{
				//超时,恢复到默认会话模式...CC,CDTCS恢复默认配置
				Uds_DefaultInit();
				Uds_CommControlInit();
				Uds_DTCSwitchInit();
			}
		}
	}

	if(UdsAppInfo.SecurityState.ServerLockedFlag == UDS_LOCKED_STATE)
	{
		if(UdsAppInfo.SecurityState.LockedTime>0)
		{
			UdsAppInfo.SecurityState.LockedTime--;
		}
		if(UdsAppInfo.SecurityState.LockedTime == 0)
		{
			UdsAppInfo.SecurityState.ServerLockedFlag = UDS_UNLOCKED_STATE;
		}
	}
	#if UDS_SVC_RDBPI_EN
	if(UdsAppInfo.RDBPI_Info.GapCount>0)
	{
		UdsAppInfo.RDBPI_Info.GapCount--;
	}
	if(UdsAppInfo.RDBPI_Info.PeriodSendCount>0)
	{
		UdsAppInfo.RDBPI_Info.PeriodSendCount--;
	}
	#endif
}

/****************************************************************************
 * @function	Uds_GetServiceIndexFromCfgTbl
 * @brief  	UDS get the service ID index from the config table
 * @param  	ServiceId: service ID
 * @retval 	index
****************************************************************************/
static uint8_t Uds_GetServiceIndexFromCfgTbl(uint8_t ServiceId)
{
	uint8_t i = 0;
	uint8_t num = Uds_GetCfgTblTotalNum();

	for(i = 0; i<num;i++)
	{
		if(UdsServiceCfgTbl[i].ServiceId == ServiceId)
		{
			return i;
		}
	}
	return 0xff;
}

static uint8_t Uds_ChkSubFunctionSupport(uint8_t serviceIndex , uint8_t ReqFunc)
{
	uint8_t i = 0;
	for(i = 0 ; i < UdsServiceCfgTbl[serviceIndex].SubFunctionNum; i ++)
	{
		if(UdsServiceCfgTbl[serviceIndex].ListOfSubFunction[i] == ReqFunc)
		{
			return TRUE;								
		}
	}
	return FALSE;
}

static uint8_t Uds_ChkServiceAddressingSupprot(uint8_t servieIndex)
{
	if((UdsServiceCfgTbl[servieIndex].PhysicalAddress == NOT_SUPPORT  
		&& UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
		||(UdsServiceCfgTbl[servieIndex].FunctionalAddress == NOT_SUPPORT  
		&& UdsNetInfo.TargetAddrType == UDS_FUNC_ADDR))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

static uint8_t Uds_ChkSessionModeSupport(uint8_t curServiceIdInx)
{
	if((UdsServiceCfgTbl[curServiceIdInx].DefaultSession == NOT_SUPPORT
		&& UdsAppInfo.DiagSessionType == SESSION_DEFAULT) 
		||(UdsServiceCfgTbl[curServiceIdInx].ProgrammingSession == NOT_SUPPORT
		&& UdsAppInfo.DiagSessionType  == SESSION_PROGRAM)
		||(UdsServiceCfgTbl[curServiceIdInx].ExtendedSession == NOT_SUPPORT
		&& UdsAppInfo.DiagSessionType == SESSION_EXTENDED))
	{
		return SNSIAS;
	}
	else if(UdsAppInfo.SecurityState.SecurityAccess == UDS_LOCKED_STATE 
		&& ((UdsServiceCfgTbl[curServiceIdInx].DefaultSession == SUPPORT_UNLOCK
			&& UdsAppInfo.DiagSessionType	 == SESSION_DEFAULT)
		|| (UdsServiceCfgTbl[curServiceIdInx].ProgrammingSession == SUPPORT_UNLOCK
			&& UdsAppInfo.DiagSessionType  == SESSION_PROGRAM)
		|| (UdsServiceCfgTbl[curServiceIdInx].ExtendedSession == SUPPORT_UNLOCK
		    && UdsAppInfo.DiagSessionType == SESSION_EXTENDED)))
	{
		return SAD; /*条件不满足*/
	}
	else
	{
		return 0;
	}
}

#if UDS_SVC_RDBPI_EN
static void Uds_GetRDBPITimeCycle(void)
{
	if(UdsAppInfo.RDBPI_Info.transmissionMode == 0x01)
	{
		UdsAppInfo.RDBPI_Info.PeriodSendCount = SLOW_RATE_TIME;
	}
	else if(UdsAppInfo.RDBPI_Info.transmissionMode == 0x01)
	{
		UdsAppInfo.RDBPI_Info.PeriodSendCount = MEDIUM_RATE_TIME;
	}
	else if(UdsAppInfo.RDBPI_Info.transmissionMode == 0x01)
	{
		UdsAppInfo.RDBPI_Info.PeriodSendCount = FAST_RATE_TIME;
	}
}
static uint8_t Uds_SendPeriodRDBPIHandle(void)
{

	if(UdsAppInfo.RDBPI_Info.transmissionMode>=4)
	{
		return  0;
	}
       if(NULL == Uds_GetRDBPIPoint())
       {
		return 0;
	}
	if(UdsAppInfo.RDBPI_Info.PeriodSendCount == 0)
	{
		RDBPI_INFO_STRUCT *pInfo = &UdsAppInfo.RDBPI_Info;
		pInfo->PeriodSendIndex = 0;
		Uds_GetRDBPITimeCycle();
		pInfo->GapCount = 0;
	}
		
	if((UdsAppInfo.RDBPI_Info.GapCount==0) &&(UdsAppInfo.RDBPI_Info.PeriodSendCount > 0))
	{
		//send gap message
		RDBPI_STRUCT *pRDBPI = Uds_GetRDBPIPoint();
		RDBPI_INFO_STRUCT *pInfo = &UdsAppInfo.RDBPI_Info;

		UdsAppInfo.RDBPI_Info.GapCount = UdsAppInfo.RDBPI_Info.GapValue;
		if(pInfo->PeriodSendIndex< pInfo->IdNum)
		{
			uint8_t index = pInfo->PeriodIdBuffer[pInfo->PeriodSendIndex];
			uint8_t buffer[7];
			uint8_t i;

			if(index < PDID_MAX_NUM)
			{
				buffer[0]	=pRDBPI[index].PD_Id;
				for(i = 0; i < pRDBPI[index].ByteLen;i ++)
				{
					buffer[i+1]= pRDBPI[index].Byte[i];
				}
				Uds_RDBPI_SendMsg( pRDBPI[index].ByteLen+1, buffer);
				pInfo->PeriodSendIndex++;
			}
		}
	}

	return 1;
}
#endif

void Uds_ServerRspStatus_Handler(void)
{
	uint8_t temp = 0;
	uint8_t i = 0;
	uint16_t index = 0;
	
	switch(UdsNetInfo.ServerRspStatus)
	{
		case DIAG_SEND_SF:
			Uds_SendSingleFrameMsg(USDT_PduT_Msg.A_Data.ParamLength, 
							USDT_PduT_Msg.A_Data.SI, 
							USDT_PduT_Msg.A_Data.Parameter);
			UdsNetInfo.ServerRspStatus = DIAG_IDLE;
			Uds_Debug(printf("\r\nUDS send SF"));
			break;
		case DIAG_SEND_FF:
			temp = Uds_SendFirstFrameMsg(&USDT_PduT_Msg);
			USDT_PduT_Msg.SN = 0;
			USDT_PduT_Msg.TransParamNum= temp;		// have Send 5 data
			UdsNetInfo.ServerRspStatus	=DIAG_WAIT_FC; // wait for Flow Control frame
			UdsNetTimingParam.timer_N_Bs=N_Bs_MAX;// setting the wait for FC timeout time
			Uds_Debug(printf("\r\nUDS send FF"));
			//Uds_TestRcvFCFrame();		//TEST
			break;	
		case DIAG_SEND_FC: 
						
			Uds_SendFlowConFrame(UdsNetInfo.FlowStatus, BLOCK_SIZE,ST_MIN);
			UdsNetInfo.ServerRspStatus	=DIAG_WAIT_CF;
			UdsNetTimingParam.timer_N_Cr = N_Cr_MAX;
			Uds_Debug(printf("\r\nUDS send FC"));
			break;	
		case DIAG_SEND_CF:
			if(UdsNetTimingParam.timer_N_Cs>0)
			{
				break;
			}
			Uds_Debug(printf("\r\nUDS send CF"));
			UdsNetTimingParam.timer_N_Cs=UdsNetInfo.Time_Cs;
			
			USDT_PduT_Msg.SN ++ ;
			USDT_PduT_Msg.BS ++;
			if(USDT_PduT_Msg.SN>0x0f)
			{
				USDT_PduT_Msg.SN = 0;
			}

			USDT_PduT_Msg.TransParamNum+= Uds_SendContinueFrameMsg(&USDT_PduT_Msg, &temp);
			
			if(temp ==1)
			{
				UdsNetInfo.ServerRspStatus	=DIAG_IDLE;
			}
			else if(USDT_PduT_Msg.BS== UdsNetInfo.BlockSize)
			{
				UdsNetInfo.ServerRspStatus	=DIAG_WAIT_FC;
				UdsNetTimingParam.timer_N_Bs=N_Bs_MAX;
			}
			break;
		case DIAG_WAIT_FC:             //wait for Flow Control Frame
			if(UdsNetTimingParam.timer_N_Bs==0)       /* wait timeout deal */
			{
				//abort message transmit
				UdsNetInfo.ServerRspStatus	=DIAG_IDLE;
				Uds_Debug(printf("\r\nUDS wait FC timeout"));
			}
			break;
		case DIAG_WAIT_CF:		// wait for Continune Frame
			if(UdsNetTimingParam.timer_N_Cr == 0)
			{
				// wait CF timeout 
				//abort message transmit
				UdsNetInfo.ServerRspStatus	=DIAG_IDLE;
				Uds_Debug(printf("\r\nUDS wait CF timeout"));
			}
			break;
		case DIAG_CF_RCV_END:	// continue Frame Recieve Ok
			Uds_ServiceHandler(MSG_TYPE_USDT,  UdsAppInfo.curServiceIdInx);
			UdsNetInfo.ServerRspStatus	=DIAG_IDLE;
			break;
#if UDS_SVC_RDBPI_EN
		case DIAG_SEND_RDBPI:
			if(Uds_SendPeriodRDBPIHandle() == 0)
			{
				UdsNetInfo.ServerRspStatus	=DIAG_IDLE;
			}
			break;
#endif
		case DIAG_IDLE:
			break;
		default:
			break;
	}
}

#if UDS_SVC_DSC_EN
void Uds_DiagSessionControl_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t session_type = 0;
	uint8_t i = 0;
	if(MsgType != MSG_TYPE_UUDT)
	{
		return;
	}
	if(UUDT_PduR_Msg.A_Data.ParamLength !=0)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	session_type = UUDT_PduR_Msg.A_Data.SubFunc;
	 if(UdsAppInfo.DiagSessionType == SESSION_DEFAULT 
	 	&& session_type == SESSION_PROGRAM)
	{
		Uds_Response_Negative(CNC);
		return;
	}
	else if(UdsAppInfo.DiagSessionType == SESSION_PROGRAM 
		&& session_type == SESSION_EXTENDED)
	{
		Uds_Response_Negative(CNC);	
		return;
	}
	if(UdsAppInfo.DiagSessionType == SESSION_EXTENDED 
		&& (session_type == SESSION_DEFAULT 
		|| session_type == SESSION_PROGRAM
		|| session_type == SESSION_EXTENDED))
	{
		UdsAppInfo.SecurityState.SecurityAccess	=UDS_LOCKED_STATE;
		UdsAppInfo.SecurityState.SecurityAccessStatus   =UDS_SA_IDLE;
	}
	UdsAppInfo.DiagSessionType = session_type;
	/*write the session mode */
	Uds_RefreshDid_ADS();
	/*-----------------------------*/
	if(!(UUDT_PduR_Msg.A_Data.suppressPosRspMsg))
	{
		Uds_SessionControl_PosRsp(session_type);
	}
	if(UdsAppInfo.DiagSessionType == SESSION_DEFAULT)
	{
		Uds_DefaultInit();
	}
	else
	{
		UdsAppTimingParam.timer_S3Server = S3server_MAX;
//		UdsAppTimingParam.timer_S3Client = S3client_MAX;
	}
	
}
#endif
#if UDS_SVC_ECUR_EN
void Uds_EcuReset_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t ResetType;
	if(MsgType != MSG_TYPE_UUDT)
	{
		return;
	}
	if(UUDT_PduR_Msg.A_Data.ParamLength!= 0)
	{
		Uds_Response_Negative(IMLOIF);
		return;
	}
	ResetType = UUDT_PduR_Msg.A_Data.SubFunc;
	if((ResetType >=0x01) && (ResetType<=0x03))
	{
		if(!UUDT_PduR_Msg.A_Data.suppressPosRspMsg)
		{
			Uds_EcuReset_PosRsp(ResetType);
		}
		//request system to reset according the type
		UdsFbl_ResetSystem(ResetType);			
	}
	else
	{
		if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			Uds_Response_Negative(SFNS);
	}
	
}
#endif
#if UDS_SVC_SA_EN
void Uds_SecurityAccess_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t SubFunc;
	uint8_t ParamLen;
	uint8_t *pParam;

	if(MsgType == MSG_TYPE_UUDT)
	{
		SubFunc = UUDT_PduR_Msg.A_Data.SubFunc;
		ParamLen = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam     = UUDT_PduR_Msg.A_Data.Parameter;
	}
	else
	{
		SubFunc   = USDT_PduR_Msg.A_Data.SubFunc;
		ParamLen = USDT_PduR_Msg.A_Data.ParamLength;
		pParam 	=  USDT_PduR_Msg.A_Data.Parameter;
	}

	if(SubFunc == UDS_SA_SEED)
	{
		if(ParamLen != 0)
		{
			Uds_Response_Negative(IMLOIF);
			return;
		}
		if((UdsAppInfo.SecurityState.ServerLockedFlag ==UDS_LOCKED_STATE)  && UdsAppInfo.SecurityState.LockedTime)
		{
			Uds_Response_Negative(RTDNE);//SecurityAccess timeout
			return;
		}
		#if 0
			if(UdsAppInfo.SecurityState.SecurityAccessStatus != UDS_SA_IDLE)
			{
				Uds_Response_Negative(RSE);
				return;
			}
		#else
			//snake 20160803 解锁状态下,再次发送seed,回复正响应
			if(UdsAppInfo.SecurityState.SecurityAccess == UDS_UNLOCKED_STATE)
			{
				Uds_SecurityAccessSeed_PosRsp();
				return;
			}
		#endif
		
		UdsAppInfo.SecurityState.invalidSecurKeyCount = 0;
		UdsAppInfo.SecurityState.SecurityAccessStatus = UDS_SA_SEED;
		Uds_SecurityAccess_PosRsp(UDS_SA_SEED, SECURITY_KEY_LENGTH);
	}
	else if(SubFunc == UDS_SA_SENDKEY)
	{
		uint8_t SecurityKey[SECURITY_KEY_LENGTH];
		if(ParamLen != SECURITY_KEY_LENGTH)
		{
			Uds_Response_Negative(IMLOIF);
			return;
		}
		if((UdsAppInfo.SecurityState.ServerLockedFlag ==UDS_LOCKED_STATE))
		{
			Uds_Response_Negative(RTDNE);
			return;
		}
		if(UdsAppInfo.SecurityState.SecurityAccessStatus != UDS_SA_SEED)
		{
			Uds_Response_Negative(RSE);
			return;
		}
		//Uds_GetSecurityKey(Uds_GetSecuritySeedPoint(), SecurityKey, SECURITY_KEY_LENGTH);
		Uds_LevelOneKeyArith(Uds_GetSecuritySeedPoint(), SecurityKey);
		if(MemoryCompare(SecurityKey, pParam, SECURITY_KEY_LENGTH))
		{
			UdsAppInfo.SecurityState.invalidSecurKeyCount++;
			if(UdsAppInfo.SecurityState.invalidSecurKeyCount>=3)
			{
				UdsAppInfo.SecurityState.invalidSecurKeyCount = 0;
				UdsAppInfo.SecurityState.LockedTime = SERVER_LOCKTIME_MAX;//强制锁定10s
				UdsAppInfo.SecurityState.ServerLockedFlag = UDS_LOCKED_STATE;
				Uds_Response_Negative(ENOA);
			}
			else
			{
				Uds_Response_Negative(IK);
			}
		}
		else
		{
			UdsAppInfo.SecurityState.invalidSecurKeyCount = 0;
			UdsAppInfo.SecurityState.SecurityAccess = UDS_UNLOCKED_STATE;
			UdsAppInfo.SecurityState.SecurityAccessStatus = UDS_SA_IDLE;
			
			Uds_SecurityAccess_PosRsp(UDS_SA_SENDKEY, SECURITY_KEY_LENGTH);
		}
	}

}
#endif
#if UDS_SVC_CC_EN
void Uds_CommControl_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t ControlType;
	uint8_t CommType;
	if(MsgType != MSG_TYPE_UUDT)
	{
		return;
	}
	if(UUDT_PduR_Msg.FrameDataLen != 3)
	{
		Uds_Response_Negative(IMLOIF);
		return;
	}
	
	ControlType = UUDT_PduR_Msg.A_Data.SubFunc;
	CommType = UUDT_PduR_Msg.A_Data.Parameter[0];
	
	if(ControlType>COMM_DSRX_DSTX)
	{
		if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			Uds_Response_Negative(SFNS);
		return;
	}
	if((CommType<COMM_TYPE_NCM) ||(CommType >COMM_TYPE_NCM_NWMCM))
	{
		Uds_Response_Negative(ROOR);
		return;
	}
	if(UdsAppInfo.DiagSessionType != SESSION_EXTENDED)
	{
		Uds_Response_Negative(CNC);
		return;
	}
	UdsAppInfo.subControlType = ControlType;
	UdsAppInfo.CommunicationType = UUDT_PduR_Msg.A_Data.Parameter[0];
	Uds_BusMsgConfig();
	
	if(!UUDT_PduR_Msg.A_Data.suppressPosRspMsg)
	{
		Uds_CommControl_PosRsp(ControlType);
	}
}
#endif
#if UDS_SVC_TP_EN
void Uds_TesterPresent_Handle(UDS_MSG_TYPE MsgType)
{
	if(MsgType != MSG_TYPE_UUDT)
	{
		return;
	}
	if(UUDT_PduR_Msg.A_Data.ParamLength !=0)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	if(!(UUDT_PduR_Msg.A_Data.suppressPosRspMsg))
	{
		Uds_TesterPresent_PosRsp();
	}
	UdsAppTimingParam.timer_S3Server = S3server_MAX;
}
#endif
#if UDS_SVC_CDTCS_EN
void Uds_ControlDTCSetting_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t SubFunc = 0;
	uint8_t suppressPosRspMsgIndBit = 0;
	if(MsgType != MSG_TYPE_UUDT)
	{
		return;
	}
	SubFunc = UUDT_PduR_Msg.A_Data.SubFunc;
	suppressPosRspMsgIndBit = UUDT_PduR_Msg.A_Data.suppressPosRspMsg;
	if(SubFunc == 0x01 || SubFunc == 0x02)
	{
		if(UUDT_PduR_Msg.FrameDataLen != 2)
		{
			Uds_Response_Negative(IMLOIF);
			return;
		}
		if(SubFunc == 0x01)			//open DTC setting
		{
			UdsDTCState.DTCSwitch = STATE_ON;
		}
		else if(SubFunc == 0x02)		//close DTC setting
		{
			UdsDTCState.DTCSwitch = STATE_OFF;
		}
		if(!suppressPosRspMsgIndBit)
		{
			Uds_ControlDTCSetting_PosRsp(SubFunc);
		}
	}
}
#endif
#if UDS_SVC_WDBI_EN
void Uds_WriteDataById_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t temp;
	uint8_t index;
	uint8_t *pParam;
	uint16_t DataIdentifier;
	uint8_t i;
	DID_STRUCT* pDIDTbl = Uds_GetDIDCfgTable();
	uint8_t DidTotalNum = Uds_GetDIDTblTotalNum();
	if(MsgType == MSG_TYPE_UUDT)
	{
		temp = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
	}
	else
	{
		temp = USDT_PduR_Msg.A_Data.ParamLength;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
	}

	if(temp<3)
	{
		Uds_Response_Negative(IMLOIF);
		return;
	}
	DataIdentifier = (pParam[0]<<8) |pParam[1];
	for(i = 0;i< DidTotalNum;i++)
	{
		if(DataIdentifier == pDIDTbl[i].DID_Id)
		{
			break;
		}
	}
	if(i == DidTotalNum)
	{
		if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			Uds_Response_Negative(ROOR);
		return;
	}

	if(pDIDTbl[i].Attribute != ATTRI_WRITE)
	{
		Uds_Response_Negative(ROOR);
		return;	/*if the DID is not write attribute, Can not be write!!*/
	}
	index = i;
#if 0
	if((temp-2) > pDIDTbl[i].ByteLen)
	{
		Uds_Response_Negative(ROOR);
		return;
	}
#else
	    if((temp-2) != pDIDTbl[i].ByteLen)
	    {
			Uds_Response_Negative(IMLOIF);
			return;
	    }
#endif
	/*
	* please add EEPROM PROGRAM operation to store this information
	*/
	if(UdsFbl_StoreDIDToSystem(DataIdentifier, pParam+2, temp-2))
	{
		/*write failed !*/
		Uds_Response_Negative(GPF);
	}
	else
	{
		Memory8Copy(pDIDTbl[index].pParam, pParam+2, temp-2);
		pDIDTbl[index].ByteLen = temp-2;
		Uds_WriteDataById_PosRsp(DataIdentifier);
	}
}
#endif
#if UDS_SVC_CDTCI_EN
void Uds_ClearDiagInfo_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t ClearState = 0;
	uint8_t GroupOfDTC[3];
	DTC_STRUCT *pDTCTable;
	if(MsgType != MSG_TYPE_UUDT)
	{
		return;
	}
	if(UUDT_PduR_Msg.FrameDataLen!=4)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	Memory8Copy(GroupOfDTC, &UUDT_PduR_Msg.A_Data.Parameter[0], 3);

	pDTCTable = Uds_GetDTCTable();
	while(1)
	{
		if((pDTCTable->DTCHighByte) == 0x00)
		{
			break;
		}
		#if 1 //snake20160803 完全匹配
		if(((GroupOfDTC[0]==0xff) && (GroupOfDTC[1]==0xff) && (GroupOfDTC[2]==0xff))	//clear all group
			|| ((pDTCTable->DTCHighByte == GroupOfDTC[0]) && (pDTCTable->DTCMiddleByte == GroupOfDTC[1]) && (pDTCTable->DTCLowByte == GroupOfDTC[2])))
		#else
		if((GroupOfDTC[0] == 0xff) || 
		   ((pDTCTable->DTCHighByte & GroupOfDTC[0]) == GroupOfDTC[0]))
		#endif
		{	
			if(pDTCTable->IsSupport == SUPPORT)//snake20160804 只有支持的DTC才进行清除
			{
				pDTCTable->DTCStatus = 0x00;
				ClearState = 1;
			}
		}
		pDTCTable++;
	}
	if(ClearState == 1)//snake20160803
	{
		UdsFbl_StoreDTCToSystem();//写入失败,返回否定响应CNC???
		Uds_ClearDTCInfo_PosRsp();
	}
	else
	{
		if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			Uds_Response_Negative(ROOR);	
	}

}
#endif
#if UDS_SVC_RDTCI_EN
void Uds_ReadDTCInfo_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t SubFunc;
	uint8_t ParamLength;
	uint8_t *pParam;
	DTC_STRUCT *pDTCTable = Uds_GetDTCTable();

	if(MsgType == MSG_TYPE_UUDT)
	{
		SubFunc = UUDT_PduR_Msg.A_Data.SubFunc;
		ParamLength = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
	}
	else
	{
		SubFunc = USDT_PduR_Msg.A_Data.SubFunc;
		ParamLength = USDT_PduR_Msg.A_Data.ParamLength;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
	}
	if(SubFunc == 0x01)   // report Number of DTC By StatusMask
	{
		uint8_t StatusMask;
		uint8_t SendBuffer[6];
		uint16_t i = 0;
		if(ParamLength != 1)
		{
			Uds_Response_Negative(IMLOIF);	
			return;
		}
		StatusMask = pParam[0];
		UdsDTCState.DTCAvilabilityMask = DTC_AVILABILITY_MASK;//snake20160725 for ISO14229-2006 PAGE186
		while(pDTCTable->DTCHighByte)
		{
			//if the DTCStatusMask is bit-wise logically ANDed with the DTC's actual status and the result is non-zero, then a match has occurred
			if(pDTCTable->IsSupport == SUPPORT)//snake20160804
			{
				if(pDTCTable->DTCStatus & StatusMask)
				{
					i++;
				}
			}
			pDTCTable++;
		}
		SendBuffer[0] = UdsDTCState.DTCAvilabilityMask; 
		//SendBuffer[1] = 0x01; /*ISO14229-1DTCFormat*/
		SendBuffer[1] = 0x00; /*snake 20160509 ISO15031-6 DTCFormat*/
		SendBuffer[2] =( i>>8) &0xff;
		SendBuffer[3] = i &0xff;      //number
		Uds_ReadDTCInfo_PosRsp(SubFunc, SendBuffer, 4);
	}
	else if(SubFunc == 0x02)// report DTC by StatusMask
	{
		uint8_t StatusMask;
		uint8_t *pTxParam = USDT_PduT_Msg.A_Data.Parameter;
		uint8_t i = 0;
		if(ParamLength != 1)
		{
			Uds_Response_Negative(IMLOIF);	
			return;
		}
		StatusMask = pParam[0];
		UdsDTCState.DTCAvilabilityMask = DTC_AVILABILITY_MASK;
		USDT_PduT_Msg.A_Data.SI = SERVE_RDTCI + UDS_SI_OFFSET;
		USDT_PduT_Msg.A_Data.SubFunc = SubFunc;
		*pTxParam++ = SubFunc;
		*pTxParam++ = UdsDTCState.DTCAvilabilityMask; 
		USDT_PduT_Msg.A_Data.ParamLength = 2;

		while(pDTCTable->DTCHighByte)
		{
			if(pDTCTable->IsSupport == SUPPORT)//snake20160804
			{
				if(pDTCTable->DTCStatus & StatusMask)
				{
					*pTxParam++ = pDTCTable->DTCHighByte;
					*pTxParam++ = pDTCTable->DTCMiddleByte;
					*pTxParam++ = pDTCTable->DTCLowByte;
					*pTxParam++ = pDTCTable->DTCStatus;
					USDT_PduT_Msg.A_Data.ParamLength+=4;
				}
			}
			pDTCTable++;
		}
		USDT_PduT_Msg.FrameDataLen = USDT_PduT_Msg.A_Data.ParamLength+1;
		Uds_USDT_TxMsgHandle(&USDT_PduT_Msg);
		
	}
	else if(SubFunc == 0x0A)// report supported DTC
	{
		uint8_t *pTxParam = USDT_PduT_Msg.A_Data.Parameter;
		uint8_t i = 0;
		if(ParamLength != 0)
		{
			Uds_Response_Negative(IMLOIF);	
			return;
		}
		USDT_PduT_Msg.A_Data.SI = SERVE_RDTCI + UDS_SI_OFFSET;
		USDT_PduT_Msg.A_Data.SubFunc = SubFunc;
		*pTxParam++ = SubFunc;//snake20160905
		*pTxParam++ = DTC_AVILABILITY_MASK; 
		USDT_PduT_Msg.A_Data.ParamLength = 2;

		while(pDTCTable->DTCHighByte)
		{
			if(pDTCTable->IsSupport == SUPPORT)//snake20160804
			{
				*pTxParam++ = pDTCTable->DTCHighByte;
				*pTxParam++ = pDTCTable->DTCMiddleByte;
				*pTxParam++ = pDTCTable->DTCLowByte;
				*pTxParam++ = pDTCTable->DTCStatus;
				USDT_PduT_Msg.A_Data.ParamLength+=4;
			}
			pDTCTable++;
		}
		USDT_PduT_Msg.FrameDataLen = USDT_PduT_Msg.A_Data.ParamLength+1;
		Uds_USDT_TxMsgHandle(&USDT_PduT_Msg);
	}
}

#endif
#if UDS_SVC_IOCBI_EN
//not support function address
void Uds_InOutControlById_Handle(UDS_MSG_TYPE MsgType)
{
	uint16_t DataIdentifier;
	uint8_t ParamLength;
	uint8_t *pParam;
	uint8_t index = 0;

	if(MsgType == MSG_TYPE_UUDT)
	{
		ParamLength = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
	}
	else
	{
		ParamLength = USDT_PduR_Msg.A_Data.ParamLength;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
	}
	DataIdentifier = (pParam[0]<<8) |pParam[1];

	/*
	//snake20160804 报文的长度是根据定义来进行判断的...
	if(ParamLength<3)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}*/

	/* judge DataIdentifier Arange */
	index= 0;
	while(IOControlTable[index].DID !=0x0000)
	{
		if(IOControlTable[index].DID == DataIdentifier)
		{
			break;
		}
		index++;
	}

	//snake20160804
	if((ParamLength>IOControlTable[index].OptionLen+3)||(ParamLength<3))
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	
	if(IOControlTable[index].DID ==0x0000)//Parameter not support ...none
	{
		if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)//snake20160804
			Uds_Response_Negative(ROOR);	
		return;
	}
	IOControlTable[index].ControlParameter = pParam[2];
	IOControlTable[index].pOption = &pParam[3];
	IOControlTable[index].OptionLen = ParamLength-3;

	if(IOControlTable[index].ControlParameter> IOC_shortTermAdjustment)
	{
		Uds_Response_Negative(ROOR);	
	}
	else
	{
		Uds_UserIOControlHook(index);
	}
}
#endif
#if UDS_SVC_RD_EN
void Uds_RequestDownload_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t ParamLength;
	uint8_t *pParam;
	uint8_t temp1;
	uint8_t temp2;
	uint8_t i = 0;

	uint32_t memoryStartAddr;
	uint32_t memorySize;
	
	if(MsgType == MSG_TYPE_UUDT)
	{
		ParamLength = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
	}
	else
	{
		ParamLength = USDT_PduR_Msg.A_Data.ParamLength;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
	}

	if(ParamLength<2)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	UdsDownLoadState.CompressionMode = (pParam[0]>>4)&0x0f;// get the compression mode
	UdsDownLoadState.EncryptingMode = pParam[0]&0x0f;	//get the encrypting mode

	// judge the pParam[0] data valid
	//if unvalid ,return the ROOR negative response
	/*if()
	{
		Uds_Response_Negative(ROOR);	
		return;
	}*/
	
	temp1 = (pParam[1]>>4)&0x0f;	// memory length
	temp2 = pParam[1]&0x0f;		// start address length

	if(ParamLength != (temp1+temp2+2))
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	if(temp2 >4)
	{
		Uds_Response_Negative(ROOR);	
		return;
	}
	memoryStartAddr = 0;
	for(i = 0;i<temp2;i++)
	{
		memoryStartAddr = memoryStartAddr<<8;
		memoryStartAddr |= pParam[i+2];
	}

	memorySize = 0;
	for(i = 0;i<temp1;i++)
	{
		memorySize = memorySize<<8;
		memorySize |= pParam[temp2+i+2];
	}
	// check memoryStartAddr and memorySize valid
	if(!UdsFbl_CheckAddressValid(memoryStartAddr, memorySize))
	{
		Uds_Response_Negative(ROOR);	
		return;
	}
	UdsDownLoadState.MemoryStartAddr = memoryStartAddr;
	UdsDownLoadState.MemorySize = memorySize;
	UdsDownLoadState.Sequence = 0;
	UdsDownLoadState.Step = DWLD_REQ;
	// must give active response
	Uds_RequestDownload_PosRsp(UdsDownLoadState.AckMaxBlockSize);
	
}
#endif
#if UDS_SVC_TD_EN
void Uds_TransferData_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t ParamLength;
	uint8_t *pParam;
	uint8_t temp;
	uint8_t SuppressPosRspBit;
	uint8_t i = 0;

	if(UdsDownLoadState.Step != DWLD_REQ)
	{
		return;
	}
	
	if(MsgType == MSG_TYPE_UUDT)
	{
		ParamLength = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
		SuppressPosRspBit = UUDT_PduR_Msg.A_Data.suppressPosRspMsg;
	}
	else
	{
		ParamLength = USDT_PduR_Msg.A_Data.ParamLength;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
		SuppressPosRspBit = USDT_PduR_Msg.A_Data.suppressPosRspMsg;
	}

	if(ParamLength<2)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	temp = UdsDownLoadState.Sequence;
	temp= (temp+1)&0xff;
	if(temp != pParam[0])
	{
		Uds_Response_Negative(RSE);	
		return;
	}
	UdsDownLoadState.Sequence = temp;
	UdsDownLoadState.Step = DWLD_TRANS;
	//deal the block data
	// 1. data start position: pParam[1], num = pParam[0]-1;
	// 2. encrypting reverse
	// 3. depression deal
	// 4. deal programming deal

	if(!SuppressPosRspBit)
	{
		Uds_TransferData_PosRsp(UdsDownLoadState.Sequence);
	}
}
#endif
#if UDS_SVC_RTE_EN
void Uds_RequestTransferExit_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t SuppressPosRspBit;
	if(MsgType != MSG_TYPE_UUDT)
	{
		return;
	}
	if(UdsDownLoadState.Step == DWLD_IDLE)
	{
		Uds_Response_Negative(RSE);	
		return;
	}
	UdsDownLoadState.Step = DWLD_IDLE;
	SuppressPosRspBit = UUDT_PduR_Msg.A_Data.suppressPosRspMsg;
	if(!SuppressPosRspBit)
	{
		Uds_RequestTransferExit_PosRsp();
	}
}
#endif
#if UDS_SVC_RC_EN
/****************************************************************************
 * @function	Uds_RoutineIdValidCheck
 * @brief  	check routine valid
 * @param  	Rid: Routine ID		
 * @retval 	when vliad,return the index in the Routine table; when unvalid, return 0xff.
****************************************************************************/
static uint8_t Uds_RoutineIdValidCheck(uint16_t RId)
{
	uint8_t i = 0;

	uint16_t *pTable = &UdsRoutineIdTable[0];
	
	while(1)
	{
		if(pTable[i] == UDS_ROUTINE_ID_TAB_END)
		{
			return 0xff;
		}
		else if(pTable[i] == RId)
		{
			return i;
		}
		i++;
	}
}
void Uds_RoutineControl_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t ParamLength;
	uint8_t SubFunc;
	uint8_t SuppressPosRspBit;
	uint8_t *pParam;
	uint16_t RoutineId;
	
	if(MsgType == MSG_TYPE_UUDT)
	{
		ParamLength = UUDT_PduR_Msg.A_Data.ParamLength;
		SubFunc = UUDT_PduR_Msg.A_Data.SubFunc;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
		SuppressPosRspBit = UUDT_PduR_Msg.A_Data.suppressPosRspMsg;
	}
	else
	{
		ParamLength = USDT_PduR_Msg.A_Data.ParamLength;
		SubFunc = USDT_PduR_Msg.A_Data.SubFunc;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
		SuppressPosRspBit = USDT_PduR_Msg.A_Data.suppressPosRspMsg;
	}

	if(ParamLength<2)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	RoutineId = (pParam[0]<<8) |pParam[1];

	if(0xff == Uds_RoutineIdValidCheck(RoutineId))
	{
		Uds_Response_Negative(ROOR);	
		return;
	}
	
	if(SubFunc == ROUTINE_START)		//Start Routine
	{
		UdsRoutineState.RoutineState = SubFunc;
		UdsRoutineState.RoutineId = RoutineId;
		if(!SuppressPosRspBit)
		{
			Uds_RoutineControl_PosRsp(SubFunc, RoutineId, (uint8_t *)0, 0);
		}
	}
	else if(SubFunc == ROUTINE_STOP)	//Stop Routine
	{
		if(UdsRoutineState.RoutineState != ROUTINE_START)
		{
			Uds_Response_Negative(RSE);	
			return;
		}
		UdsRoutineState.RoutineState = ROUTINE_STOP;
		if(!SuppressPosRspBit)
		{
			Uds_RoutineControl_PosRsp(SubFunc, RoutineId, (uint8_t *)0, 0);
		}
	}
	else if(SubFunc == ROUTINE_REQRESULT)  // Request Routine results
	{
		if(UdsRoutineState.RoutineState != ROUTINE_START)
		{
			Uds_Response_Negative(RSE);	
			return;
		}
		UdsRoutineState.RoutineState = ROUTINE_REQRESULT;
		if(!SuppressPosRspBit)
		{
			Uds_RoutineControl_PosRsp(SubFunc, RoutineId, 
				UdsRoutineState.Result, UdsRoutineState.ResultLen); 
		}
	}
	else					// other sub function, not definition
	{
		Uds_Response_Negative(SFNS);	
	}
}
#endif
#if UDS_SVC_ATP_EN
void Uds_AccessTimingParm_Handler(UDS_MSG_TYPE MsgType)
{
	
}
#endif
#if UDS_SVC_SDT_EN
void Uds_SecuDataTrans_Handler(UDS_MSG_TYPE MsgType)
{

}
#endif
#if UDS_SVC_ROE_EN
void Uds_RespOnEvent_Handler(UDS_MSG_TYPE MsgType)
{
	
}
#endif
#if UDS_SVC_LC_EN
void Uds_LinkControl_Handler(UDS_MSG_TYPE MsgType)
{
	
}
#endif
#if UDS_SVC_RSDBI_EN
void Uds_ReadScaleDataById_Handler(UDS_MSG_TYPE MsgType)
{
	
}
#endif
#if UDS_SVC_DDDI_EN
void Uds_DynDefDataId_Handler(UDS_MSG_TYPE MsgType)
{
	
}
#endif
/****************************************************************************
 * @function	Uds_ReadMemoryByAddr_Handle
 * @brief  	RMBA service handler
 * @param  	MsgType: MessageType: 		MSG_TYPE_UUDT//MSG_TYPE_USDT		
 * @retval 	null
****************************************************************************/
#if UDS_SVC_RMBA_EN
//not support function address
void Uds_ReadMemoryByAddr_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t ParamLength;
	uint8_t *pParam;
	uint8_t temp1;
	uint8_t temp2;
	uint8_t i = 0;

	uint32_t memoryStartAddr;
	uint32_t memorySize;
	
	if(MsgType == MSG_TYPE_UUDT)
	{
		ParamLength = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
	}
	else
	{
		ParamLength = USDT_PduR_Msg.A_Data.ParamLength;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
	}

	if(ParamLength<1)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	temp1 = (pParam[0]>>4)&0x0f;	/* memory length	*/
	temp2 = pParam[0]&0x0f;		/* start address length */

	if(ParamLength != (temp1+temp2+1))
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}

	if(temp2 >4)
	{
		Uds_Response_Negative(ROOR);	
		return;
	}
	memoryStartAddr = 0;
	for(i = 0;i<temp2;i++)
	{
		memoryStartAddr = memoryStartAddr<<8;
		memoryStartAddr |= pParam[i+1];
	}

	memorySize = 0;
	for(i = 0;i<temp1;i++)
	{
		memorySize = memorySize<<8;
		memorySize |= pParam[temp2+i+1];
	}
	if(!UdsFbl_CheckAddressValid(memoryStartAddr, memorySize))
	{
		// check the memory start and end address.
		Uds_Response_Negative(ROOR);
		return;
	}
	
	if(memorySize > N_BUFFER_SIZE)
	{
		Uds_Response_Negative(ROOR);	
		return;
	}
	USDT_PduT_Msg.A_Data.SI = SERVE_RMBA+ UDS_SI_OFFSET;
	USDT_PduT_Msg.A_Data.ParamLength = memorySize;
	USDT_PduT_Msg.FrameDataLen = USDT_PduT_Msg.A_Data.ParamLength+1;
	Memory8Copy(USDT_PduT_Msg.A_Data.Parameter, (uint8_t *)memoryStartAddr, memorySize);
	Uds_USDT_TxMsgHandle(&USDT_PduT_Msg);
}
#endif
#if UDS_SVC_WMBA_EN
//not support function address
void Uds_WriteMemoryByAddr_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t ParamLength;
	uint8_t *pParam;
	uint8_t temp1;
	uint8_t temp2;
	uint8_t i = 0;

	uint32_t memoryStartAddr;
	uint32_t memorySize;
	
	if(MsgType == MSG_TYPE_UUDT)
	{
		ParamLength = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
	}
	else
	{
		ParamLength = USDT_PduR_Msg.A_Data.ParamLength;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
	}

	if(ParamLength<1)
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	temp1 = (pParam[0]>>4)&0x0f;	// memory length
	temp2 = pParam[0]&0x0f;		// start address length

	if(temp2 >4)
	{
		Uds_Response_Negative(ROOR);	
		return;
	}
	memoryStartAddr = 0;
	for(i = 0;i<temp2;i++)
	{
		memoryStartAddr = memoryStartAddr<<8;
		memoryStartAddr |= pParam[i+1];
	}

	memorySize = 0;
	for(i = 0;i<temp1;i++)
	{
		memorySize = memorySize<<8;
		memorySize |= pParam[temp2+i+1];
	}

	if(ParamLength != (temp1+temp2+memorySize+1))
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	if(!UdsFbl_CheckAddressValid(memoryStartAddr, memorySize))
	{
		// check the memory start and end address.
		Uds_Response_Negative(ROOR);
		return;
	}

	// write the data to the address, please ensure the type: RAM/ EEPROM/ FLASH

	USDT_PduT_Msg.A_Data.SI = SERVE_WMBA+ UDS_SI_OFFSET;
	USDT_PduT_Msg.A_Data.ParamLength = temp1+temp2+1;
	USDT_PduT_Msg.FrameDataLen = USDT_PduT_Msg.A_Data.ParamLength+1;
	Memory8Copy(USDT_PduT_Msg.A_Data.Parameter, &pParam[0], USDT_PduT_Msg.A_Data.ParamLength);
	Uds_USDT_TxMsgHandle(&USDT_PduT_Msg);

}
#endif
/****************************************************************************
 * @function	Uds_ReadDataByPeriodId_Handle
 * @brief  	RDBPI service handler
 * @param  	MsgType: MessageType: 		MSG_TYPE_UUDT//MSG_TYPE_USDT		
 * @retval 	null
****************************************************************************/
#if UDS_SVC_RDBPI_EN
void Uds_ReadDataByPeriodId_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t temp;
	uint8_t transType;
	uint8_t i,j;
	uint8_t* pParam;
	RDBPI_STRUCT *pRDBPI = Uds_GetRDBPIPoint();

	if(NULL == pRDBPI)
	{
		return;
	}
	
	if(MsgType == MSG_TYPE_UUDT)
	{
		temp = UUDT_PduR_Msg.A_Data.ParamLength;
		pParam = UUDT_PduR_Msg.A_Data.Parameter;
	}
	else
	{
		temp = USDT_PduR_Msg.A_Data.ParamLength;
		pParam = USDT_PduR_Msg.A_Data.Parameter;
	}
	transType = *pParam;
	if(transType==0x00 || transType>0x04)
	{
		Uds_Response_Negative(ROOR);	
		return;
	}
	if(transType== 0x04)
	{
		RDBPI_INFO_STRUCT *pInfo = &UdsAppInfo.RDBPI_Info;
		RDBPI_STRUCT *pRDBPI = Uds_GetRDBPIPoint();
		uint8_t Did = pParam[1];
		uint8_t i = 0;
		if(temp!= 2)
		{
			Uds_Response_Negative(IMLOIF);	
			return;
		}
		if(UdsAppInfo.RDBPI_Info.transmissionMode == 4)
		{
			return;
		}
		for(i = 0;i< pInfo->IdNum; i++)
		{
			if(pRDBPI[pInfo->PeriodIdBuffer[i]].PD_Id == Did)
			{
				for(; i<pInfo->IdNum; i++)
				{
					pInfo->PeriodIdBuffer[i] = pInfo->PeriodIdBuffer[i+1];
				}
				pInfo->IdNum --;
				if(pInfo->IdNum == 0)
				{
					UdsAppInfo.RDBPI_Info.transmissionMode = 4;
				}
				break;
			}
		}
		return;
	}

	if((temp-1)> PDID_MAX_NUM)
	{
		Uds_Response_Negative(ROOR);	
		return;
	}
	if(CheckRepeatData(pParam+1, temp-1))
	{
		Uds_Response_Negative(ROOR);	
		return;
	}

	for(i = 0 ; i <temp-1 ; i ++)
	{
		for(j = 0; j < PDID_MAX_NUM; j ++)
		{		
			if(pParam[i+1] == pRDBPI[j].PD_Id)
			{
				UdsAppInfo.RDBPI_Info.PeriodIdBuffer[i] = j;
				break;
			}
		}
		if(j == PDID_MAX_NUM)
		{
			Uds_Response_Negative(ROOR);	
			return;
		}
	}
	UdsAppInfo.RDBPI_Info.IdNum = temp-1;
	UdsAppInfo.RDBPI_Info.transmissionMode = transType;
	UdsAppInfo.RDBPI_Info.PeriodSendIndex = 0;
	UdsNetInfo.ServerRspStatus = DIAG_SEND_RDBPI;
	Uds_GetRDBPITimeCycle();
	UdsAppInfo.RDBPI_Info.GapValue = UdsAppInfo.RDBPI_Info.PeriodSendCount/(UdsAppInfo.RDBPI_Info.IdNum+1) +1;
	UdsAppInfo.RDBPI_Info.GapCount = UdsAppInfo.RDBPI_Info.GapValue;
	if(UdsAppInfo.RDBPI_Info.GapCount>TIMER_20MS)
	{
		UdsAppInfo.RDBPI_Info.GapCount=TIMER_20MS;
	}
	Uds_ReadDataByPeriodId_PosRsp();
}
#endif
#if UDS_SVC_RDBI_EN
void Uds_ReadDataById_Handle(UDS_MSG_TYPE MsgType)
{
	uint8_t temp = 0;
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t flag = 0;
	uint16_t dataIdentifier[20];
	uint8_t index[20];

	uint8_t DidTblNum = Uds_GetDIDTblTotalNum();
	DID_STRUCT* pDIDTbl = Uds_GetDIDCfgTable();

	uint8_t ParSupportNum =0;
	uint16_t RspParLen =0;

	uint8_t *ptr1;
	uint8_t *ptr2;

	if(DidTblNum>50)//snake20160803  20
	{
		/*if DidTblNum larger than 20(the size of dataIdentifier), return it , report the exception */
		return; 
	}
	
	if(MsgType == MSG_TYPE_UUDT)
	{
		temp = UUDT_PduR_Msg.A_Data.ParamLength;
	}
	else
	{
		temp = USDT_PduR_Msg.A_Data.ParamLength;
	}
	if(((temp % 2) != 0) ||(temp == 0))
	{
		Uds_Response_Negative(IMLOIF);	
		return;
	}
	if(temp > (2*DidTblNum))   /*each DID is 2 bytes */
	{
		if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			Uds_Response_Negative(ROOR);	
		return;
	}
	j = 0;
	for(i = 0 ; i < temp  ; i +=2)
	{
		if(MsgType == MSG_TYPE_UUDT)
		{
			dataIdentifier[j]	=(uint16_t)(UUDT_PduR_Msg.A_Data.Parameter[i] << 8) + UUDT_PduR_Msg.A_Data.Parameter[i+1];		
		}
		else
		{
			dataIdentifier[j]	=(uint16_t)(USDT_PduR_Msg.A_Data.Parameter[i] << 8) + USDT_PduR_Msg.A_Data.Parameter[i+1];		
		}
		j ++;
	}
	for(j = 0 ; j < (temp / 2); j ++) 
	{
		flag =0;
		for(i = 0 ; i <DidTblNum; i ++)
		{
			if(dataIdentifier[j] == pDIDTbl[i].DID_Id)
			{
				index[ParSupportNum++]	=i; 
				RspParLen += pDIDTbl[i].ByteLen;
				flag =1;
			}
		}
		if(flag== 0)
		{
			break;
		}
	}
	if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
	{
		if(flag == 0)
		{
			Uds_Response_Negative(ROOR);
			return ;
		}
	}
	else
	{
		if(flag == 0)
		{
			/*not ack for function addressing */
			return ;
		}
	}
	if(MsgType == MSG_TYPE_UUDT)
	{
		USDT_PduT_Msg.A_Data.SI = UUDT_PduR_Msg.A_Data.SI + UDS_SI_OFFSET;
	}
	else
	{
		USDT_PduT_Msg.A_Data.SI = USDT_PduR_Msg.A_Data.SI + UDS_SI_OFFSET;
	}
	USDT_PduT_Msg.A_Data.ParamLength = RspParLen+ 2* ParSupportNum;
	USDT_PduT_Msg.FrameDataLen = USDT_PduT_Msg.A_Data.ParamLength+1;

	ptr1 = &USDT_PduT_Msg.A_Data.Parameter[0];
	for(i = 0;i< ParSupportNum; i++)
	{
		ptr2 = pDIDTbl[index[i]].pParam;
		*ptr1++ = (dataIdentifier[i]>>8)&0xff;
		*ptr1++ = dataIdentifier[i]&0xff;
		Memory8Copy(ptr1,  ptr2, pDIDTbl[index[i]].ByteLen);
		ptr1+= pDIDTbl[index[i]].ByteLen;
	}
	
	Uds_USDT_TxMsgHandle(&USDT_PduT_Msg);
}
#endif
void Uds_ServiceHandler(UDS_MSG_TYPE MsgType, uint8_t curServiceIdInx)
{
	Uds_Debug(_T("UDS ServiceHandler,curServiceIdInx = %x\n",curServiceIdInx));
	switch(UdsServiceCfgTbl[curServiceIdInx].ServiceId)
	{
#if UDS_SVC_DSC_EN
		case SERVE_DSC:
			Uds_DiagSessionControl_Handle(MsgType);
		break;
#endif
#if UDS_SVC_ECUR_EN
		case SERVE_ECUR:
			Uds_EcuReset_Handle(MsgType);
		break;
#endif
#if UDS_SVC_SA_EN
		case SERVE_SA:
			Uds_SecurityAccess_Handle(MsgType);
		break;
#endif
#if UDS_SVC_CC_EN
		case SERVE_CC:
			Uds_CommControl_Handle(MsgType);
		break;
#endif
#if UDS_SVC_TP_EN
		case SERVE_TP:
			Uds_TesterPresent_Handle(MsgType);
		break;
#endif
#if UDS_SVC_CDTCS_EN
		case SERVE_CDTCS:
			Uds_ControlDTCSetting_Handle(MsgType);
		break;
#endif
#if UDS_SVC_RDBI_EN
		case SERVE_RDBI:
			Uds_ReadDataById_Handle(MsgType);
		break;
#endif
#if UDS_SVC_RMBA_EN
		case SERVE_RMBA:
			Uds_ReadMemoryByAddr_Handle(MsgType);
		break;
#endif
#if UDS_SVC_WMBA_EN
		case SERVE_WMBA:
			Uds_WriteMemoryByAddr_Handle(MsgType);
			break;
#endif
#if UDS_SVC_RDBPI_EN
		case SERVE_RDBPI:
			Uds_ReadDataByPeriodId_Handle(MsgType);
		break;
#endif
#if UDS_SVC_WDBI_EN
		case SERVE_WDBI:
			Uds_WriteDataById_Handle(MsgType);
		break;
#endif
#if UDS_SVC_CDTCI_EN
		case SERVE_CDTCI:
			Uds_ClearDiagInfo_Handle(MsgType);
		break;
#endif
#if UDS_SVC_RDTCI_EN
		case SERVE_RDTCI:
			Uds_ReadDTCInfo_Handle(MsgType);
		break;
#endif
#if UDS_SVC_IOCBI_EN
		case SERVE_IOCBI:
			Uds_InOutControlById_Handle(MsgType);
		break;
#endif
#if UDS_SVC_RD_EN
		case SERVE_RD:
			Uds_RequestDownload_Handle(MsgType);
		break;
#endif
#if UDS_SVC_TD_EN
		case SERVE_TD:
			Uds_TransferData_Handle(MsgType);
		break;
#endif
#if UDS_SVC_RTE_EN
		case SERVE_RTE:
			Uds_RequestTransferExit_Handle(MsgType);
		break;
#endif
#if UDS_SVC_RC_EN
		case SERVE_RC:
			Uds_RoutineControl_Handle(MsgType);
		break;
#endif
#if UDS_SVC_ATP_EN
		case SERVE_ATP:
			Uds_AccessTimingParm_Handler(MsgType);
		break;
#endif
#if UDS_SVC_SDT_EN
		case SERVE_SDT:
			Uds_SecuDataTrans_Handler(MsgType);
		break;
#endif
#if UDS_SVC_ROE_EN
		case SERVE_ROE:
			Uds_RespOnEvent_Handler(MsgType);
		break;
#endif
#if UDS_SVC_LC_EN
		case SERVE_LC:
			Uds_LinkControl_Handler(MsgType);
		break;
#endif
#if UDS_SVC_RSDBI_EN
		case SERVE_RSDBI:
			Uds_ReadScaleDataById_Handler(MsgType);
		break;
#endif
#if UDS_SVC_DDDI_EN
		case SERVE_DDDI:
			Uds_DynDefDataId_Handler(MsgType);
		break;
#endif
		default:
			Uds_Response_Negative(SNS);
		break;
	}
}


uint8_t Uds_SingleFrameHandler(UUDT_PDU *pUUDT)
{
	uint8_t temp;
	
	if((pUUDT->FrameDataLen == 0) ||(pUUDT->FrameDataLen >= 8))
	{
		/*SF_DL = 0(or >=8) should not response 2016.4.28 */
		return 0;
	}

	pUUDT->A_Data.SI = pUUDT->pData[0];
	UdsAppInfo.curServiceIdInx = Uds_GetServiceIndexFromCfgTbl(pUUDT->A_Data.SI);
	UdsAppInfo.CurServiceId = pUUDT->A_Data.SI;
	//Uds_Debug(_T("UdsAppInfo.curServiceIdInx = %d,UdsAppInfo.CurServiceId = %d\n",UdsAppInfo.curServiceIdInx,UdsAppInfo.CurServiceId));
	
	if(UdsAppInfo.curServiceIdInx != 0xff)
	{
		if(TRUE == Uds_ChkServiceAddressingSupprot(UdsAppInfo.curServiceIdInx))
		{
			if(SubFunctionSupport(UdsAppInfo.curServiceIdInx) == YES_SUB_FUNC)
			{
				if((pUUDT->FrameDataLen<2) ||(pUUDT->FrameDataLen >= 8))
				{
					Uds_Response_Negative(IMLOIF);
					return 0;
				}
				pUUDT->A_Data.ParamLength = pUUDT->FrameDataLen -2;
				#if 0
					pUUDT->A_Data.SubFunc = pUUDT->pData[1] & 0x7f;
				#else //snake20160803 有部分的server id 不存在抑制正响应的功能
					if((pUUDT->A_Data.SI != SERVE_SA) || (pUUDT->A_Data.SI != SERVE_RDTCI))//snake 20160516 这些服务存在抑制正响应之说..
						pUUDT->A_Data.SubFunc = pUUDT->pData[1] & 0x7f;
					else 
						pUUDT->A_Data.SubFunc = pUUDT->pData[1];
				#endif
				
				if(pUUDT->A_Data.ParamLength>0)
				{
					Memory8Copy(pUUDT->A_Data.Parameter, &pUUDT->pData[2], pUUDT->A_Data.ParamLength);
				}
				pUUDT->A_Data.suppressPosRspMsg = pUUDT->pData[1] &0x80;

				if(FALSE == Uds_ChkSubFunctionSupport(UdsAppInfo.curServiceIdInx, pUUDT->A_Data.SubFunc))
				{
					if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
						Uds_Response_Negative(SFNS);
					return 0;
				}
			}
			else
			{
				// sub function not support
				if((pUUDT->FrameDataLen<1) ||(pUUDT->FrameDataLen >= 8))
				{
					Uds_Response_Negative(IMLOIF);
					return 0;
				}
				pUUDT->A_Data.ParamLength = pUUDT->FrameDataLen -1;
				pUUDT->A_Data.SubFunc = 0xff;
				pUUDT->A_Data.suppressPosRspMsg = 0x00;//snake20160803
				if(pUUDT->A_Data.ParamLength>0)
				{
					Memory8Copy(pUUDT->A_Data.Parameter, &pUUDT->pData[1], pUUDT->A_Data.ParamLength);
				}
			}
		}
		else
		{
			// addressing type not support
			return 2;
		}

		temp = Uds_ChkSessionModeSupport(UdsAppInfo.curServiceIdInx);
		if(temp != 0x00)
		{
			Uds_Response_Negative(temp);
			return 0;
		}
		else
		{
			UdsAppInfo.LastFrameType = UdsAppInfo.curFrameType;
			Uds_ServiceHandler(MSG_TYPE_UUDT,  UdsAppInfo.curServiceIdInx);
		}
	}
	else
	{
		// not support Service Id
		if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			Uds_Response_Negative(SNS);
	}
	
	return 0;
}

void Uds_Restart_S3serverTimer(void)
{
	UdsNetTimingParam.timer_N_Bs = 0;	/*等待流控制帧的等待时间*/
	UdsNetTimingParam.timer_N_Cr = 0;	/*接收连续帧的等待时间*/
	UdsAppTimingParam.timer_S3Server = S3server_MAX;
}

uint8_t Uds_FirstFrameHandler(USDT_PDU *pUSDT, uint8_t num)
{
	uint8_t temp = 0;
	
	pUSDT->A_Data.SI = pUSDT->pData[0];
	UdsAppInfo.curServiceIdInx = Uds_GetServiceIndexFromCfgTbl(pUSDT->A_Data.SI);
	UdsAppInfo.CurServiceId = pUSDT->A_Data.SI;
#if 1
	if((pUSDT->FrameDataLen==0) || (pUSDT->FrameDataLen<8))
	{
		//Uds_Response_Negative(IMLOIF);//snake20160711delete;ignore it
		return 0;
	}

	if(pUSDT->FrameDataLen > N_BUFFER_SIZE)
	{
		UdsNetInfo.FlowStatus = FS_OVERFLOW;
		UdsNetInfo.ServerRspStatus	=DIAG_SEND_FC; 
		Uds_Restart_S3serverTimer();
		return 0;
	}
	
	pUSDT->LastSN = 0;
	if(SubFunctionSupport(UdsAppInfo.curServiceIdInx) == YES_SUB_FUNC)
	{
		pUSDT->A_Data.SubFunc = pUSDT->pData[1] & 0x7f;
		pUSDT->A_Data.ParamLength	=pUSDT->FrameDataLen - 2;
		pUSDT->TransParamNum = num-2;
		pUSDT->A_Data.suppressPosRspMsg = pUSDT->pData[1] & 0x80;
		Memory8Copy(pUSDT->A_Data.Parameter, &pUSDT->pData[2], num-2);
		Uds_Debug(_T("Service Id support SubFunction!!!\n"));
	}
	else
	{
		pUSDT->A_Data.ParamLength = pUSDT->FrameDataLen - 1;
		pUSDT->A_Data.suppressPosRspMsg = 0;        /* init to 0 */
		pUSDT->TransParamNum = num-1;
		Memory8Copy(pUSDT->A_Data.Parameter, &pUSDT->pData[1], num-1);
		Uds_Debug(_T("Service Id not support SubFunction!!!\n"));
	}
	
	UdsAppInfo.LastFrameType = UdsAppInfo.curFrameType;
	UdsNetInfo.FlowStatus = CONTINUE_SEND;
	UdsNetInfo.ServerRspStatus	=DIAG_SEND_FC;
#else
	if(UdsAppInfo.curServiceIdInx != 0xff)
	{
		if(TRUE == Uds_ChkServiceAddressingSupprot(UdsAppInfo.curServiceIdInx))
		{
			if(pUSDT->FrameDataLen==0)
			{
				// invalid frameDataLen, ignore it!!
				return 0;
			}
			if(pUSDT->FrameDataLen<8)
			{
				Uds_Response_Negative(IMLOIF);
				return 0;
			}
			if(pUSDT->FrameDataLen > N_BUFFER_SIZE)
			{
				UdsNetInfo.FlowStatus = FS_OVERFLOW;
				UdsNetInfo.ServerRspStatus	=DIAG_SEND_FC; 
				Uds_Restart_S3serverTimer();
				return 0;
			}
			temp = Uds_ChkSessionModeSupport(UdsAppInfo.curServiceIdInx);
			if(temp != 0x00)
			{
				Uds_Response_Negative(temp);
				return 0;
			}
			
			pUSDT->LastSN = 0;
			
			if(SubFunctionSupport(UdsAppInfo.curServiceIdInx) == YES_SUB_FUNC)
			{
				pUSDT->A_Data.SubFunc = pUSDT->pData[1] & 0x7f;
				pUSDT->A_Data.ParamLength	=pUSDT->FrameDataLen - 2;
				pUSDT->TransParamNum = num-2;
				pUSDT->A_Data.suppressPosRspMsg = pUSDT->pData[1] & 0x80;
				if(FALSE == Uds_ChkSubFunctionSupport(UdsAppInfo.curServiceIdInx, pUSDT->A_Data.SubFunc))
				{
					Uds_Response_Negative(SFNS);
					return 0;
				}
				else
				{
					Memory8Copy(pUSDT->A_Data.Parameter, &pUSDT->pData[2], num-2);
					UdsAppInfo.LastFrameType = UdsAppInfo.curFrameType;
					UdsNetInfo.FlowStatus = CONTINUE_SEND;
					UdsNetInfo.ServerRspStatus	=DIAG_SEND_FC; 
				}
			}
			else
			{
				pUSDT->A_Data.ParamLength	=pUSDT->FrameDataLen - 1;
				pUSDT->A_Data.suppressPosRspMsg = 0;        /* init to 0 */
				pUSDT->TransParamNum = num-1;
				Memory8Copy(pUSDT->A_Data.Parameter, &pUSDT->pData[1], num-1);
				UdsAppInfo.LastFrameType = UdsAppInfo.curFrameType;
				UdsNetInfo.FlowStatus = CONTINUE_SEND;
				UdsNetInfo.ServerRspStatus	=DIAG_SEND_FC; 
			}
			
		}

	}
	else
	{
		// not support Service Id
		Uds_Response_Negative(SNS);
		return 0;
	}
#endif
}

void Uds_ContinueFrameHandler(USDT_PDU *pUSDT, uint8_t num)
{
	uint8_t i = 0;
	uint8_t temp = 0;
	/* if last Frame is not FF, return */
	if((UdsAppInfo.LastFrameType  != FF_NPCI) &&(UdsAppInfo.LastFrameType  != CF_NPCI))
	{
		return; 
	}
	if((pUSDT->SN == 0 && pUSDT->LastSN== 0x0f)
		|| ( (pUSDT->LastSN < 0x0f) && (pUSDT->SN == (pUSDT->LastSN + 1))))

	{
		pUSDT->LastSN	=pUSDT->SN;
	}
	else
	{
		UdsNetInfo.ServerRspStatus= DIAG_IDLE;
		return;
	}
	UdsAppInfo.LastFrameType = UdsAppInfo.curFrameType;
	for(i = 0; i<num; i++)
	{
		if((pUSDT->TransParamNum) < (pUSDT->A_Data.ParamLength))
		{
			pUSDT->A_Data.Parameter[pUSDT->TransParamNum++] = pUSDT->pData[i];
			if((pUSDT->TransParamNum) == (pUSDT->A_Data.ParamLength))
			{
				UdsNetInfo.ServerRspStatus	=DIAG_CF_RCV_END;
				pUSDT->SN	=0;	
				UdsAppTimingParam.timer_S3Client=S3client_MAX;	
				break;
			}
		}
	}
#if 1//snake0803
	if(UdsNetInfo.ServerRspStatus == DIAG_CF_RCV_END)
	{
		if(UdsAppInfo.curServiceIdInx != 0xff)
		{
			if(TRUE == Uds_ChkServiceAddressingSupprot(UdsAppInfo.curServiceIdInx))
			{
				temp = Uds_ChkSessionModeSupport(UdsAppInfo.curServiceIdInx);
				Uds_Debug(_T("uds_CF:temp = 0x%x\n",temp));
				if(temp != 0x00)
				{
					Uds_Response_Negative(temp);
					UdsNetInfo.ServerRspStatus	= DIAG_IDLE;
					return ;
				}
		
				Uds_Debug(_T("uds_CF:pUSDT->LastSN = %d\n",pUSDT->LastSN));
				if(SubFunctionSupport(UdsAppInfo.curServiceIdInx) == YES_SUB_FUNC)
				{
					if(FALSE == Uds_ChkSubFunctionSupport(UdsAppInfo.curServiceIdInx, pUSDT->A_Data.SubFunc))
					{
						if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)//snake20160726
							Uds_Response_Negative(SFNS);
						UdsNetInfo.ServerRspStatus	= DIAG_IDLE;
						return ;
					}
				}
			}

		}
		else
		{
			// not support Service Id
			if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)//snake20160726
				Uds_Response_Negative(SNS);
			UdsNetInfo.ServerRspStatus	= DIAG_IDLE;
			return ;
		}
	}
#endif
	UdsNetTimingParam.timer_N_Cr = N_Cr_MAX;
}

void Uds_FlowControlFrameHandler(USDT_PDU *pUSDT)
{

	if(pUSDT->FS > FS_OVERFLOW)
	{
		Uds_Restart_S3serverTimer();
		UdsNetInfo.ServerRspStatus = DIAG_IDLE;
		return ;
	}
	if(pUSDT->STmin>0x7f)
	{
		// system Timing not support!(unit: ms, not support us unit)
		return;
	}
	
	UdsAppInfo.LastFrameType = UdsAppInfo.curFrameType;
	if(pUSDT->FS == CONTINUE_SEND) /*allow continnue to send next message */
	{
		UdsNetInfo.ServerRspStatus	=DIAG_SEND_CF;
		UdsNetInfo.STmin = pUSDT->STmin/TIMER_BASE;
		UdsNetInfo.BlockSize = pUSDT->BS;
		USDT_PduT_Msg.BS = 0;            /*clear BS to count the BlockSize num */
		Uds_Restart_S3serverTimer();
		if(UdsNetInfo.STmin< (ST_MIN/TIMER_BASE))
		{
			UdsNetInfo.Time_Cs = ST_MIN/TIMER_BASE;
		}
		else if(UdsNetInfo.STmin<= N_Cs_MAX)
		{
			UdsNetInfo.Time_Cs = UdsNetInfo.STmin;
		}
		else
		{
			UdsNetInfo.Time_Cs = N_Cs_MAX;
		}
		UdsNetInfo.Time_Cs+=1;
		UdsNetTimingParam.timer_N_Cs=UdsNetInfo.Time_Cs; /*为CS 增加一个时间间隔 2016-4-29 */
	}
	/* the frame size overflow the Receiver 's buffer size */
	else if(pUSDT->FS ==  FS_OVERFLOW) /**/
	{	
		if(UdsNetInfo.ServerRspStatus == DIAG_SEND_FF)//snake20160725 for ISO15765-2-2004 PAGE21
		{
			Uds_Restart_S3serverTimer();
			UdsNetInfo.ServerRspStatus = DIAG_IDLE;
		}
	}
	else if(pUSDT->FS == WAIT_NEXT_FC)
	{
		// request the sender to wait next FC
		Uds_Restart_S3serverTimer();
		UdsNetTimingParam.timer_N_Bs=N_Bs_MAX;
	}
}

static void Uds_AppFrameHandler(void)
{
	if(UdsAppInfo.curFrameType != NULL_NPCI)
	{
		Uds_Debug(printf("\r\nUDS Receive Frame: %d", UdsAppInfo.curFrameType));
		if(UdsAppInfo.DiagSessionType != SESSION_DEFAULT)//snake20160726
		{
			Uds_Debug(_T("timer_S3Server value reset\n"));
			UdsAppTimingParam.timer_S3Server = S3server_MAX;
		}
		switch(UdsAppInfo.curFrameType)
		{
			case SF_NPCI:
				Uds_SingleFrameHandler(&UUDT_PduR_Msg);
				break;
			case FF_NPCI:
				Uds_FirstFrameHandler(&USDT_PduR_Msg,6);
				break;
			case CF_NPCI:
				Uds_ContinueFrameHandler(&USDT_PduR_Msg, 7);
				break;
			case FC_NPCI:
				Uds_FlowControlFrameHandler(&USDT_PduR_Msg);
				break;	
			default:
				break;
		}
		UdsAppInfo.curFrameType = NULL_NPCI;
	}	
}
#if UDS_SVC_RC_EN
void Uds_RoutineService_Handler(void)
{
	if(UdsRoutineState.RoutineState == ROUTINE_STOP)
	{
		return;
	}
	if(UdsRoutineState.RoutineId == 0xff01)
	{
		// Routine1 handler
	}
	else if(UdsRoutineState.RoutineId == 0xff02)
	{
		// Routine2 handler
	}
}
#endif
void Uds_ProtocolStackMain(void)
{
	if(UdsAppInfo.ModuleState == UDS_STATE_OFF)
	{
		return;
	}
	switch(UdsAppInfo.ModuleState)
	{
		case UDS_STATE_REQON:
			Uds_EnterWorkInit();
			UdsAppInfo.ModuleState = UDS_STATE_ON;
			Uds_Debug(printf("\r\nUDS ON"));
			//break;          //direct execute next state 
		case UDS_STATE_ON:
			Uds_AppFrameHandler();
			Uds_ServerRspStatus_Handler();
			#if UDS_SVC_RC_EN
			Uds_RoutineService_Handler();		//Routine Control service Handler
			#endif
			break;
		default:
			UdsAppInfo.ModuleState = UDS_STATE_OFF;
			break;
	}
	UdsAppInfo.CurMsgDealDoneFlag = WORK_OK;
}

void Uds_Close(void)
{
	UdsAppInfo.ModuleState = UDS_STATE_OFF;
	Uds_Debug(printf("\r\nUDS Closed"));
}

void Uds_TimerHandler(void)
{
	if(UdsAppInfo.ModuleState == UDS_STATE_ON)
	{
		Uds_NetTimerHandler();
		Uds_AppTimerHandler();
	}
}
#endif
/****************************************************************************
 * **                                        FILE END
****************************************************************************/



