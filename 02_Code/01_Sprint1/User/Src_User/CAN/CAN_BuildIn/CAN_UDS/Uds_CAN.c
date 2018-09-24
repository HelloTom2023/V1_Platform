/****************************************************************************
* copyright:		JX Coagent Co.ltd.
* filename:		Uds_CAN.c
* Target MCU:		the UDS protocol based on CAN BUS
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
#ifdef CAN_MODULE_ENABLE	

UDS_CAN_CFG  UdsCANConfig;
CanMsgStruct DiagTxMessage;

void Uds_CANConfigEnter(UDS_CAN_CFG *pCfgInput)
{
	UdsCANConfig.UseId = pCfgInput->UseId;
	UdsCANConfig.TxMsgId = pCfgInput->TxMsgId;
	UdsCANConfig.RxPhyId = pCfgInput->RxPhyId;
	UdsCANConfig.RxFuncId = pCfgInput->RxFuncId;
}
/****************************************************************************
 * @function	Uds_CANInit
 * @brief  	Initialize the CAN UDS message
 * @param  	pPDU: point to the PDU	
 * @retval 	null
****************************************************************************/
void Uds_CANInit(void)
{
	DiagTxMessage.CANMsgId = UdsCANConfig.TxMsgId;
	DiagTxMessage.CANMsgDlc = 8;
}

/****************************************************************************
 * @function	Uds_USDT_TxMsgHandle
 * @brief  	Uds USDT tranmitte handler
 * @param  	pPDU: point to the PDU	
 * @retval 	null
****************************************************************************/
void Uds_USDT_TxMsgHandle(USDT_PDU *pPDU)
{
	if(pPDU->FrameDataLen<=7)
	{
		UdsNetInfo.ServerRspStatus = DIAG_SEND_SF;
	}
	else
	{
		UdsNetInfo.ServerRspStatus = DIAG_SEND_FF;
	}
}
/****************************************************************************
 * @function	Uds_SendSingleDiagCANMsg
 * @brief  	The interface to send CAN frame
 * @param  	pMsg: the CAN message point			
 * @retval 	null
****************************************************************************/
static void Uds_SendSingleDiagCANMsg(CanMsgStruct *pMsg)
{
	pMsg->CAN_Id = UdsCANConfig.UseId;
	CANbus_AppLayerSendOneShotMsg(pMsg);
}

/****************************************************************************
 * @function	Uds_Response_Negative
 * @brief  	Uds Negtive Response message
 * @param  	NegCode: response negative code				
 * @retval 	null
****************************************************************************/
void Uds_Response_Negative(uint8_t  NegCode)
{
//	if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
//	{
		DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 3;
		DiagTxMessage.Data[1]	=0x7f;
		DiagTxMessage.Data[2]	=UdsAppInfo.CurServiceId;
		DiagTxMessage.Data[3]	=NegCode;
		DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
		DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
		DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
		DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

		Uds_SendSingleDiagCANMsg(&DiagTxMessage);
		Uds_Debug(printf("Uds Response Negative: %d", NegCode));
//	}
}

/****************************************************************************
 * @function	Uds_SessionControl_PosRsp
 * @brief  	Session Control service Positive Response message
 * @param  	RespCode: response sub function				
 * @retval 	null
****************************************************************************/
void Uds_SessionControl_PosRsp(uint8_t RespCode)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 6;
	DiagTxMessage.Data[1]	=SERVE_DSC + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=RespCode;
	DiagTxMessage.Data[3]	=(P2server_MAX >> 8);
	DiagTxMessage.Data[4]	=(P2server_MAX & 0X0FF);
	DiagTxMessage.Data[5]	=(P2xserver_MAX >> 8);
	DiagTxMessage.Data[6]	=(P2xserver_MAX & 0X0FF);
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);	
}
/****************************************************************************
 * @function	Uds_TesterPresent_PosRsp
 * @brief  	Client TestPresent service Positive Response message
 * @param  	null			
 * @retval 	null
****************************************************************************/
void Uds_TesterPresent_PosRsp(void)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 2;
	DiagTxMessage.Data[1]	=SERVE_TP + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=0x00;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_ControlDTCSetting_PosRsp
 * @brief  	CDTCS service Positive Response message (use CAN bus)
 * @param  	SubFunc: response sub function				
 * @retval 	null
****************************************************************************/
void Uds_ControlDTCSetting_PosRsp(uint8_t SubFunc)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 2;
	DiagTxMessage.Data[1]	=SERVE_CDTCS + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=SubFunc;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);	
}
/****************************************************************************
 * @function	Uds_ClearDTCInfo_PosRsp
 * @brief  	CDTCI service Positive Response message (use CAN bus)
 * @param  	null				
 * @retval 	null
****************************************************************************/
void Uds_ClearDTCInfo_PosRsp(void)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 1;
	DiagTxMessage.Data[1]	=SERVE_CDTCI + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);	
}
/****************************************************************************
 * @function	Uds_ReadDTCInfo_PosRsp
 * @brief  	RDTCI service Positive Response message (use CAN bus)
 * @param  	pParam: pointer to the parameter buffer;
 *			len: parameter length
 *			subFunc: service subfunction.
 * @retval 	null
****************************************************************************/
void Uds_ReadDTCInfo_PosRsp(uint8_t subFunc, uint8_t *pParam, uint8_t len)
{
	if(len>5)
	{
		return;
	}
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + len+2;
	DiagTxMessage.Data[1]	=SERVE_RDTCI + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=subFunc;
	Memory8Copy(&DiagTxMessage.Data[3], pParam, len);
	if(len <5)
	{
		FillU8Memory(&DiagTxMessage.Data[len+3], 5-len, EMPTY_FILLER_BYTE);
	}
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);	
}

/****************************************************************************
 * @function	Uds_SecurityAccess_PosRsp
 * @brief  	SecurityAccess service , send positive response CAN message
 * @param  	the echo to the received sub function
 * @retval 	null.
****************************************************************************/
void Uds_SecurityAccess_PosRsp(uint8_t SubFunc, uint8_t SeedNum)
{
	if(SubFunc == UDS_SA_SEED)
	{
		uint8_t *pSeed = Uds_GetSecuritySeedPoint();
		if(SeedNum>5)
		{
			// when seednum is bigger than 5, it can't use SF, so return it.
			return;
		}
		DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 2+SeedNum;
		DiagTxMessage.Data[1]	=SERVE_SA + UDS_SI_OFFSET;
		DiagTxMessage.Data[2]	=SubFunc;
		Memory8Copy(&DiagTxMessage.Data[3], pSeed, SeedNum);
	}
	else
	{
		DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 2;
		DiagTxMessage.Data[1]	=SERVE_SA + UDS_SI_OFFSET;
		DiagTxMessage.Data[2]	=SubFunc;
		DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
		DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
		DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
		DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
		DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;
	}
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_SecurityAccessSeed_PosRsp
 * @brief  	SecurityAccess service , send positive response CAN message in unlock state
 * @param  	the echo to the received sub function
 * @retval 	null.
****************************************************************************/
void Uds_SecurityAccessSeed_PosRsp(void)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 2+SECURITY_KEY_LENGTH;
	DiagTxMessage.Data[1]	=SERVE_SA + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=UDS_SA_SEED;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}


/****************************************************************************
 * @function	Uds_RoutineControl_PosRsp
 * @brief  	Routine Control  service Positive Response message
 * @param  	SubFunc: sub function 
 *			id: Routine Id
 *			pParam: pointer to the parameter buffer;
 *			len: parameter length
 * @retval 	null
****************************************************************************/
void Uds_RoutineControl_PosRsp(uint8_t SubFunc, uint16_t id, uint8_t* pParam, uint8_t ParamLen)
{
	if((ParamLen+4) > 7)
	{
		USDT_PduT_Msg.A_Data.SI = SERVE_RC+ UDS_SI_OFFSET;
		USDT_PduT_Msg.A_Data.ParamLength = ParamLen+2;
		USDT_PduT_Msg.FrameDataLen = USDT_PduT_Msg.A_Data.ParamLength+2;
		USDT_PduT_Msg.A_Data.Parameter[0] = (id>>8)&0xff;
		USDT_PduT_Msg.A_Data.Parameter[1] = id&0xff;
		Memory8Copy(&USDT_PduT_Msg.A_Data.Parameter[2], pParam, ParamLen);
		Uds_USDT_TxMsgHandle(&USDT_PduT_Msg);
	}
	else
	{
		uint8_t i = ParamLen+5;
		DiagTxMessage.Data[0]	=(SF_NPCI << 4) + ParamLen+4;
		DiagTxMessage.Data[1]	=SERVE_RC+ UDS_SI_OFFSET;
		DiagTxMessage.Data[2]	=SubFunc;
		DiagTxMessage.Data[3]	=(id>>8)&0xff;
		DiagTxMessage.Data[4]	=id&0xff;
		Memory8Copy(&DiagTxMessage.Data[5], pParam, ParamLen);
		for(; i<8;i++)
		{
			DiagTxMessage.Data[i]	=EMPTY_FILLER_BYTE;
		}
		
	}
}
/****************************************************************************
 * @function	Uds_RequestDownload_PosRsp
 * @brief  	RequestDownload service , send positive response CAN message
 * @param  	blocksize: the servicer maximum size of block
 * @retval 	null.
****************************************************************************/
void Uds_RequestDownload_PosRsp(uint8_t blockSize)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 3;
	DiagTxMessage.Data[1]	=SERVE_RD+ UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=0X10;
	DiagTxMessage.Data[3]	=blockSize;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}

/****************************************************************************
 * @function	Uds_CommControl_PosRsp
 * @brief  	CommCtrol service , send positive response CAN message
 * @param  	SubFunc: the acho to the received sub function
 * @retval 	null.
****************************************************************************/
void Uds_CommControl_PosRsp(uint8_t SubFunc)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 2;
	DiagTxMessage.Data[1]	=SERVE_CC  + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=SubFunc;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_WriteDataById_PosRsp
 * @brief  	WriteDataById service , send positive response CAN message
 * @param  	Did: the service Did acho.
 * @retval 	null.
****************************************************************************/
void Uds_WriteDataById_PosRsp(uint16_t Did)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 3;
	DiagTxMessage.Data[1]	=SERVE_WDBI  + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=(Did>>8)&0xff;
	DiagTxMessage.Data[3]	=Did&0xff;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_IOControl_PosRsp
 * @brief  	IOControl service , send positive response CAN message
 * @param  	len: the Frame length of the PDU
 *			pParam: point to the parameter buffer
 * @retval 	null.
****************************************************************************/
void Uds_IOControl_PosRsp(uint8_t *pParam, uint8_t len)
{
	if(len >6)
	{
		return;
	}
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + len+1;
	DiagTxMessage.Data[1]	=SERVE_IOCBI + UDS_SI_OFFSET;
	Memory8Copy(&DiagTxMessage.Data[2], pParam, len);
	if(len <6)
	{
		FillU8Memory(&DiagTxMessage.Data[len+2], 6-len, EMPTY_FILLER_BYTE);
	}

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}

/****************************************************************************
 * @function	Uds_TransferData_PosRsp
 * @brief  	TransferData service  postive response message
 * @param  	Sequence: the sequence of the receive message, which is a acho of the receive param
 * @retval 	null.
****************************************************************************/
void Uds_TransferData_PosRsp(uint8_t Sequence)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 2;
	DiagTxMessage.Data[1]	=SERVE_TD + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=Sequence;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_RequestTransferExit_PosRsp
 * @brief  	Request Transfer Exit service  postive response message
 * @param  	null
 * @retval 	null.
****************************************************************************/
void Uds_RequestTransferExit_PosRsp(void)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 1;
	DiagTxMessage.Data[1]	=SERVE_RTE + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_EcuReset_PosRsp
 * @brief  	ECUReset service  postive response message
 * @param  	null
 * @retval 	null.
****************************************************************************/
void Uds_EcuReset_PosRsp(uint8_t type)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 2;
	DiagTxMessage.Data[1]	=SERVE_ECUR + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=type;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;

	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_ReadDataByPeriodId_PosRsp
 * @brief  	RDBPI service  postive response message
 * @param  	null
 * @retval 	null.
****************************************************************************/
void Uds_ReadDataByPeriodId_PosRsp(void)
{
	DiagTxMessage.Data[0]	=(SF_NPCI << 4) + 1;
	DiagTxMessage.Data[1]	=SERVE_RDBPI + UDS_SI_OFFSET;
	DiagTxMessage.Data[2]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[3]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6]	=EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7]	=EMPTY_FILLER_BYTE;
	
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_RDBPI_SendMsg
 * @brief  	RDBPI service , send CAN message
 * @param  	FrameLen: the Frame length of the PDU
 *			pData: point to the data buffer
 * @retval 	null.
****************************************************************************/
void Uds_RDBPI_SendMsg(uint8_t FrameLen, uint8_t *pData)
{
	if(FrameLen <=7)
	{
		DiagTxMessage.Data[0]	=(SF_NPCI << 4) + FrameLen;
		Memory8Copy(&DiagTxMessage.Data[1], pData, FrameLen);
		if(FrameLen <7)
		{
			FillU8Memory(&DiagTxMessage.Data[FrameLen+1], 7-FrameLen, EMPTY_FILLER_BYTE);
		}
		Uds_SendSingleDiagCANMsg(&DiagTxMessage);
	}
}
/****************************************************************************
 * @function	Uds_SendSingleFrameMsg
 * @brief  	send CAN Single Frame(SF) message
 * @param  	len: the PDU parameter length
 *			ServiceId: the service ID
 *			pParam: point to the parameter buffer.
 * @retval 	null.
****************************************************************************/
void Uds_SendSingleFrameMsg(uint8_t len, uint8_t ServiceId, uint8_t *pParam)
{
	uint8_t i = 0;
	if(len>6)
	{
		return;
	}
	DiagTxMessage.Data[0] = (SF_NPCI << 4) + len + 1;
	DiagTxMessage.Data[1] = ServiceId;
	for(i = 0;i<len;i++)
	{
		DiagTxMessage.Data[i+2] = *pParam++;
	}
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
}
/****************************************************************************
 * @function	Uds_SendFirstFrameMsg
 * @brief  	send CAN First Frame(FF) message
 * @param  	pPDU: the PDU to transmit;
 * @retval 	the number of send frame data.
****************************************************************************/
uint8_t Uds_SendFirstFrameMsg(USDT_PDU *pPDU)
{
	uint8_t temp;
	DiagTxMessage.Data[0]	=(FF_NPCI << 4) + (((pPDU->A_Data.ParamLength+1)  >> 8) & 0x0f);
	DiagTxMessage.Data[1]	=(pPDU->A_Data.ParamLength+1)  & 0x0FF;
	DiagTxMessage.Data[2]	=pPDU->A_Data.SI;
	for(temp = 3 ; temp < 8 ; temp ++)
	{
		DiagTxMessage.Data[temp] =pPDU->A_Data.Parameter[temp - 3];
	}
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
	/* return have send  param num */
	return 5;
}
/****************************************************************************
 * @function	Uds_SendFlowConFrame
 * @brief  	send CAN FlowControl Frame message
 * @param  	Fs: the flow state
 *			Bsize: the block size
 *			STmin: the stmin parameter
 * @retval 	the number of send frame data.
****************************************************************************/
void Uds_SendFlowConFrame(UDS_FS_TYPE Fs,uint8_t Bsize,uint8_t STmin)
{
	DiagTxMessage.Data[0] =(FC_NPCI << 4) + (Fs & 0x07);
	DiagTxMessage.Data[1] =Bsize;
	DiagTxMessage.Data[2] =STmin;
	DiagTxMessage.Data[3] =EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[4] =EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[5] =EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[6] =EMPTY_FILLER_BYTE;
	DiagTxMessage.Data[7] =EMPTY_FILLER_BYTE;
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);
} 

/****************************************************************************
 * @function	Uds_SendContinueFrameMsg
 * @brief  	send CAN Continue Frame message
 * @param  	pPDU: the PDU to transmit;
 *			SendOverFlag: used for get the send complete flag, 
 *			if commplete, the value is 1,other the value is 0.
 * @retval 	the number of send frame data.
****************************************************************************/
uint8_t Uds_SendContinueFrameMsg(USDT_PDU *pPDU, uint8_t *SendOverFlag)
{
	uint16_t index = 0;
	uint8_t i;
	uint8_t SendNum = 0;

	*SendOverFlag = 0;
	
	DiagTxMessage.Data[0]	=(CF_NPCI << 4) + pPDU->SN;

	index = pPDU->TransParamNum;
	if(pPDU->TransParamNum+7 < pPDU->A_Data.ParamLength)
	{
		SendNum = 7;
	}
	else
	{
		SendNum = pPDU->A_Data.ParamLength - pPDU->TransParamNum;
		*SendOverFlag = 1;
	}
		
	for(i = 0; i< SendNum; i++)
	{
		DiagTxMessage.Data[i+1] = pPDU->A_Data.Parameter[index++];
	}
	for(i = SendNum; i<7; i++)
	{
		DiagTxMessage.Data[i+1] = EMPTY_FILLER_BYTE;
	}
	Uds_SendSingleDiagCANMsg(&DiagTxMessage);

	return SendNum;
}
/****************************************************************************
 * @function	Uds_CANMsgRcvHandler
 * @brief  	Deal with the Received CAN uds message
 * @param  	pMsg: point to the received CAN message			
 * @retval 	0: deal done; other:  some fault occur.
****************************************************************************/
uint8_t Uds_CANMsgRcvHandler(CanMsgStruct *pMsg)
{		
	if(pMsg->CANMsgDlc <8)
	{
		Uds_Debug(printf("Uds RcvFrame DLC error!"));
		return 2;
	}
	
	if(pMsg->CANMsgId == UdsCANConfig.RxFuncId)
	{
		UdsNetInfo.TargetAddrType = UDS_FUNC_ADDR;
	}
	else if(pMsg->CANMsgId == UdsCANConfig.RxPhyId)
	{
		UdsNetInfo.TargetAddrType = UDS_PHY_ADDR;
	}
	else
	{
		return 3;
	}
  #if   0//临时添加应对长安电检
	 if((pMsg->Data[0]==0x05)&&(pMsg->Data[1]==0x2F)
	  	&&(pMsg->Data[2]==0x67)&&(pMsg->Data[3]==0xE5)&&(pMsg->Data[4]==0x03))
      	{
           if(pMsg->Data[5]==0x01)
           	{           	       
           	        DiagTxMessage.Data[0]=0x04;
			 DiagTxMessage.Data[4]=0x01;
			  PM_UnitPowerSet(PM_UNIT_RADAR,ON);
        	  }
             else if(pMsg->Data[5]==0x00)
             	{
             	        DiagTxMessage.Data[0]=0x03;
                      DiagTxMessage.Data[4]=0x00;
			 PM_UnitPowerSet(PM_UNIT_RADAR,OFF);
		 }

			 DiagTxMessage.Data[1]=0x6F;
			 DiagTxMessage.Data[2]=0x67;
			 DiagTxMessage.Data[3]=0xE5;
			 DiagTxMessage.Data[5]=0x00;
			 DiagTxMessage.Data[6]=0x00;
			 DiagTxMessage.Data[7]=0x00;
	   Uds_SendSingleDiagCANMsg(&DiagTxMessage);  
	 }
  #endif
	
	if((UdsNetInfo.ServerRspStatus == DIAG_WAIT_FC) ||
	    (UdsNetInfo.ServerRspStatus == DIAG_SEND_CF))
	{
		/*when host is wating FC, received unexpect message, ignore it */
		/*when host is send CF, received unexpect message, ignore it    */
		if((pMsg->Data[0] >> 4) != 3)
		{
			return 4;
		}
	}
	switch(pMsg->Data[0] >> 4)
	{
		case 0:
			if(UdsNetInfo.ServerRspStatus == DIAG_WAIT_CF)
			{
				UdsNetInfo.ServerRspStatus = DIAG_IDLE;
			}
			if(UdsNetInfo.ServerRspStatus == DIAG_IDLE)
			{
				UdsAppInfo.curFrameType = SF_NPCI;
				UdsAppInfo.CurMsgDealDoneFlag = WORK_RUN;
				UUDT_PduR_Msg.PduType = SF_NPCI;		//single frame
				UUDT_PduR_Msg.FrameDataLen =pMsg->Data[0]&0x0f;
				UUDT_PduR_Msg.pData = &(pMsg->Data[1]);
			}
			break;
		case 1:
			if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			{
				if(UdsNetInfo.ServerRspStatus == DIAG_SEND_FC
				||UdsNetInfo.ServerRspStatus == DIAG_SEND_CF)
				{
					// when segment transmit in process, ignored the MSG!!
					break;
				}
				UdsAppInfo.curFrameType = FF_NPCI;		// first frame
				UdsAppInfo.CurMsgDealDoneFlag = WORK_RUN;
				USDT_PduR_Msg.PduType = FF_NPCI;
				USDT_PduR_Msg.FrameDataLen =  ((pMsg->Data[0] & 0x0f) << 8) +pMsg->Data[1] ;
				USDT_PduR_Msg.pData = &pMsg->Data[2];
			}
			break;
		case 2:
			if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			{
				if(UdsNetInfo.ServerRspStatus != DIAG_WAIT_CF)
				{
					break;
				}
				UdsAppInfo.curFrameType = CF_NPCI;		//continue frame
				UdsAppInfo.CurMsgDealDoneFlag = WORK_RUN;
				USDT_PduR_Msg.PduType = CF_NPCI;
				USDT_PduR_Msg.SN= pMsg->Data[0]&0x0f;
				USDT_PduR_Msg.pData = &pMsg->Data[1];
			}
			break;
		case 3:
			if(UdsNetInfo.TargetAddrType == UDS_PHY_ADDR)
			{
				if(UdsNetInfo.ServerRspStatus != DIAG_WAIT_FC
				&& UdsNetInfo.ServerRspStatus != DIAG_SEND_CF)
				{
					break;
				}
				UdsAppInfo.curFrameType = FC_NPCI;		//Flow control frame
				UdsAppInfo.CurMsgDealDoneFlag = WORK_RUN;
				USDT_PduR_Msg.PduType = FC_NPCI;
				USDT_PduR_Msg.FS = pMsg->Data[0]&0x0f;
				USDT_PduR_Msg.BS= pMsg->Data[1];
				USDT_PduR_Msg.STmin = pMsg->Data[2];
			}
			break;
		default:
			break;
	}
	if(UdsAppInfo.ModuleState != UDS_STATE_ON)
	{
		//when receive a msg, start the UDS main thread
		UdsAppInfo.ModuleState = UDS_STATE_REQON;
	}
	return 0;
}
/****************************************************************************
 * @function	Uds_TestRcvFCFrame
 * @brief  	         in order to test receive Flow Control frame, use next function
 * @param  	null		
 * @retval 		null
****************************************************************************/
void Uds_TestRcvFCFrame(void)
{
	CanMsgStruct TestMsg;
	TestMsg.CANMsgDlc = 8;
	TestMsg.CANMsgId = UdsCANConfig.RxPhyId;
	TestMsg.CAN_Id = UdsCANConfig.UseId;
	TestMsg.Data[0] = 0x30;
	TestMsg.Data[1] = 0x04;
	TestMsg.Data[2] = 20;
	Uds_CANMsgRcvHandler(&TestMsg);
}

#endif
#endif
/****************************************************************************
 * **                                        FILE END
****************************************************************************/

