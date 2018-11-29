/****************************************************************************
* File Name : CanTp.c
*
* Modules : CAN Transport Layer source file
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-25
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/

/*Include head files AREA*/
#include "CanTp.h"
#include "CanTp_Cfg_Table.h" /*The table only used by CanTp.C*/


/*Macro definition AREA*/




/*Variable declaration AREA*/
static CanTp_ProtocolControlUnitStruct_Type CanTp_ProtocolControlUnit;

/*Function implement AREA*/
/****************************************************************************
 * @function	CanTp_InitFunction
 * @brief  		init cantp parameters
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
CAN_TP_EXTERN_API void CanTp_InitFunction(void)
{
	/*Init CanTp_RecvPduCtrInfo*/
	CanTp_RecvPduCtrInfo.Data = CanTp_RecvPudBuffer;
}

/****************************************************************************
 * @function	CanTp_MainFunction
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
CAN_TP_EXTERN_API void CanTp_MainFunction(void)
{
	CanTp_TxManagementFunction();
}

/****************************************************************************
 * @function	CanTp_TxManagementFunction
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
CAN_TP_LOCAL_API void CanTp_TxManagementFunction(void)
{

}

/****************************************************************************
 * @function	CanTp_RxIndicationFunction
 * @brief  		Indication the can to receive can message
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_EXTERN_API uint8 CanTp_RxIndicationFunction(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint8 ret_subfunc = E_OK;

#if 1 /*Debug used*/
	static uint8 init_flag = 0x00;

	if(init_flag == 0x00)
	{
		CanTp_InitFunction();
		init_flag = 0x01;
	}
#endif

	/*Check the input pointer is NULL*/
	if(NULL == ptr_Data)
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*doing nothing*/
	}


	CanTp_Debug_OutputInfo(_T("CanTp Notification Recv Data:\nCanChNo = %d,CanMsgId = 0x%lx,CanMsgDlc = %d,Data = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",	\
			ChNo,MsgId,Dlc,ptr_Data[0],ptr_Data[1],ptr_Data[2],ptr_Data[3],ptr_Data[4],ptr_Data[5],ptr_Data[6],ptr_Data[7]));


	/*Check the buffer is idle*/
	/*the buffer is in the used,the ecu will response NRC21*/

	switch(CommFunc_BitShiftRigth(ptr_Data[0],0x04) & 0x0F)
	{
		case CANTP_FRAME_TYPE_SF:
			CanTp_Debug_OutputInfo(_T("CanTp Recv SF...\n"));
			CanTp_RxIndicationFunctionSF(ChNo, MsgId, ptr_Data, Dlc);
			break;

		case CANTP_FRAME_TYPE_FF:
			CanTp_Debug_OutputInfo(_T("CanTp Recv FF...\n"));
			CanTp_RxIndicationFunctionFF(ChNo, MsgId, ptr_Data, Dlc);
			break;

		case CANTP_FRAME_TYPE_CF:
			CanTp_Debug_OutputInfo(_T("CanTp Recv CF...\n"));
			CanTp_RxIndicationFunctionCF(ChNo, MsgId, ptr_Data, Dlc);
			break;

		case CANTP_FRAME_TYPE_FC:
			CanTp_Debug_OutputInfo(_T("CanTp Recv FC...\n"));
			CanTp_RxIndicationFunctionFC(ChNo, MsgId, ptr_Data, Dlc);
			break;
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionSF
 * @brief  		Indication the can transport to receive can message with single frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionSF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint8 DataLength = 0x00;

	/*Dlc Check. this is not ISO 15765 Mandatory rule*/
	if(Dlc < 8)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*check diagnostic message id*/

	CanTp_RecvPduCtrInfo.RecvLockFlag = 0x01;
	CanTp_RecvPduCtrInfo.FrameType = CANTP_FRAME_TYPE_SF;
	CanTp_RecvPduCtrInfo.MsgId = MsgId;

	if(MsgId == CANTP_DIAG_PHY_ADDR)
	{
		CanTp_RecvPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_PHY;
	}
	else
	{
		CanTp_RecvPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_FUNC;
	}

	/*check diagnostic message data length*/
	DataLength = (uint8) (ptr_Data[0] & 0x0F);
	if((DataLength >= 1) && (DataLength <= 7))
	{
		CanTp_ProtocolDataUnitStruct_Type CanTp_DcmPdu;
		uint8 ReqDataArray[7];
		uint8 i = 0x00;

		CanTp_DcmPdu.Data = ReqDataArray;

		CanTp_RecvPduCtrInfo.TotalDataLength = DataLength;
		CanTp_RecvPduCtrInfo.RecvDataLength = DataLength;
		memcpy(CanTp_RecvPduCtrInfo.Data, &ptr_Data[1], CanTp_RecvPduCtrInfo.RecvDataLength);

		CanTp_DcmPdu.BusChannel = ChNo;
		CanTp_DcmPdu.PduType = 0x00;
		CanTp_DcmPdu.ReqType = CanTp_RecvPduCtrInfo.ReqMsgType;
		CanTp_DcmPdu.DataLength = CanTp_RecvPduCtrInfo.TotalDataLength;
		memcpy(CanTp_DcmPdu.Data, CanTp_RecvPduCtrInfo.Data, CanTp_DcmPdu.DataLength);

		CanTp_Debug_OutputInfo(_T("Diag Info:BusChannel = %d,PduType = 0x%d,ReqType = 0x%x,DataLength = %d,ReqData : [",\
				CanTp_DcmPdu.BusChannel,CanTp_DcmPdu.PduType,CanTp_DcmPdu.ReqType,CanTp_DcmPdu.DataLength));
		for(i = 0x00; i<DataLength; i++)
		{
			CanTp_Debug_OutputInfo(_T("0x%x ",CanTp_DcmPdu.Data[i]));
		}
		CanTp_Debug_OutputInfo(_T("]\n"));

		/*notification to dcm modules*/

		ret = E_OK;
	}
	else
	{
		ret = E_PARAM_INVALID;
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionFF
 * @brief  		Indication the can transport to receive can message with first frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint16 DataLength = 0x00;

	/*Dlc Check. this is not ISO 15765 Mandatory rule*/
	if(Dlc < 8)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}


	CanTp_RecvPduCtrInfo.RecvLockFlag = 0x01;
	CanTp_RecvPduCtrInfo.FrameType = CANTP_FRAME_TYPE_FF;
	CanTp_RecvPduCtrInfo.MsgId = MsgId;

	if(MsgId == CANTP_DIAG_PHY_ADDR)
	{
		CanTp_RecvPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_PHY;
	}
	else
	{
		CanTp_RecvPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_FUNC;
	}

	/*Get the message length*/
	DataLength = (uint16) ( ((ptr_Data[0] & 0x0F) << 8 ) | (ptr_Data[1]) );
	/*check diagnostic message data length*/
	if(DataLength > 7)
	{
		CanTp_RecvPduCtrInfo.SN = 0x01;
		CanTp_RecvPduCtrInfo.TotalDataLength = DataLength;
		CanTp_RecvPduCtrInfo.RecvDataLength = 6;
		memcpy(CanTp_RecvPduCtrInfo.Data, &ptr_Data[2], CanTp_RecvPduCtrInfo.RecvDataLength);
		ret = E_OK;

		/*Send flow control frame*/
		CanTp_TxDiagMsgFC(CANTP_FS_TYPE_CTS);
	}
	else
	{
		CanTp_RecvPduCtrInfo.RecvLockFlag = 0x00;
		ret = E_MSG_FORMAT_ERROR;
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionCF
 * @brief  		Indication the can transport to receive can message with consecutive frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionCF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint16 DataLength = 0x00;
	uint8 SequenceNumber = 0x00;

	/*Dlc Check. this is not ISO 15765 Mandatory rule*/
	if(Dlc < 8)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*Set the frame type flag*/
	CanTp_RecvPduCtrInfo.FrameType = CANTP_FRAME_TYPE_CF;

	/*Check the diagnostic message id*/
	/*if the consecutive frame id is not equal the first frame,ignore the message*/
	if(CanTp_RecvPduCtrInfo.MsgId != MsgId)
	{
		CanTp_RecvPduCtrInfo.RecvLockFlag = 0x00;
		ret = E_MSG_TYPE_ERROR;
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*Get Sequence Number*/
	SequenceNumber = ptr_Data[0] & 0x0F;
	/*Check SN,and SN error handling*/
	if(SequenceNumber != CanTp_RecvPduCtrInfo.SN)
	{
		ret = E_WRONG_SN;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*SN Control*/
	CanTp_RecvPduCtrInfo.SN++;
	if(CanTp_RecvPduCtrInfo.SN > 0x0F)
	{
		CanTp_RecvPduCtrInfo.SN = 0x00;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the SN Range*/
	if(CanTp_RecvPduCtrInfo.SN == CanTp_ProtocolControlUnit.BS)
	{
		/*Send flow control frame*/
		CanTp_TxDiagMsgFC(CANTP_FS_TYPE_CTS);
	}
	else
	{
		/*Doing nothing*/
	}

	/*check diagnostic message data length*/
	if((CanTp_RecvPduCtrInfo.RecvDataLength + 7) >= CanTp_RecvPduCtrInfo.TotalDataLength)/*this frame is last frame message*/
	{
		memcpy((CanTp_RecvPduCtrInfo.Data + CanTp_RecvPduCtrInfo.RecvDataLength), \
				&ptr_Data[1], \
				(CanTp_RecvPduCtrInfo.TotalDataLength - CanTp_RecvPduCtrInfo.RecvDataLength));
		CanTp_RecvPduCtrInfo.RecvDataLength = CanTp_RecvPduCtrInfo.TotalDataLength;
		ret = E_OK;
	}
	else
	{
		memcpy((CanTp_RecvPduCtrInfo.Data + CanTp_RecvPduCtrInfo.RecvDataLength), \
					&ptr_Data[1], (0x07));
		CanTp_RecvPduCtrInfo.RecvDataLength = CanTp_RecvPduCtrInfo.RecvDataLength + 7;
		ret = E_OK;
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionFC
 * @brief  		Indication the can transport to receive can message with Flow control frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFC(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint16 DataLength = 0x00;

	/*Dlc Check. this is not ISO 15765 Mandatory rule*/
	if(Dlc < 8)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*Set the frame type flag*/
	CanTp_RecvPduCtrInfo.FrameType = CANTP_FRAME_TYPE_FC;

	/*Check the diagnostic message id*/
	CanTp_ProtocolControlUnit.FS = ptr_Data[0] & 0X0F;
	CanTp_ProtocolControlUnit.BS = ptr_Data[1];
	CanTp_ProtocolControlUnit.STmin = ptr_Data[2];

	/*
	 * add code
	 *
	 * control strategy
	 * */

}

/****************************************************************************
 * @function	CanTp_TxCanFrame
 * @brief  		Send diagnostic message function
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
  *				Dlc : input parameters,the can message data length
*				ptr_Data : input parameters,the can message data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_TxCanFrame(uint8 ChNo, uint32 MsgId, uint8 Dlc, uint8* ptr_Data)
{
	return CanTp_CanIf_UpdateTxListMsgDlcData(ChNo,MsgId,Dlc,ptr_Data);
}

/****************************************************************************
 * @function	CanTp_TxDiagMsgSF
 * @brief  		Send diagnostic message function of single frame
 * @param  		ResponsePDU : input parameters, response protocol data unit
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_TxDiagMsgSF(CanTp_ProtocolDataUnitStruct_Type ResponsePDU)
{
	uint8 ret = E_NOT_OK;
	uint8 data[8] = {0x00};

	/*Check the PDU data length*/
	if(ResponsePDU.DataLength > 0x08)
	{
		ret = E_MSG_FORMAT_ERROR;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	memset(data, CANTP_PADDING_BYTE, 0x08);

	data[0] = CommFunc_BitShiftLeft(CANTP_FRAME_TYPE_SF,0x04) | ResponsePDU.DataLength;
	memcpy(&data[1], ResponsePDU.Data, ResponsePDU.DataLength);

	ret = CanTp_CanIf_UpdateTxListMsgDlcData(ResponsePDU.BusChannel, CANTP_DIAG_RESP_ADDR, 0x08, data);

	return ret;
}

/****************************************************************************
 * @function	CanTp_TxDiagMsgFF
 * @brief  		Send diagnostic message function of first frame
 * @param  		ResponsePDU : input parameters, response protocol data unit
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_TxDiagMsgFF(CanTp_ProtocolDataUnitStruct_Type ResponsePDU)
{
	uint8 ret = E_NOT_OK;
	uint8 data[8] = {0x00};

	/*Check the PDU data length*/
	if(ResponsePDU.DataLength <= 0x07)
	{
		ret = E_MSG_FORMAT_ERROR;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	data[0] = CommFunc_BitShiftLeft(CANTP_FRAME_TYPE_FF,0x04) | (ResponsePDU.DataLength & 0x0F00);
	data[1] = ResponsePDU.DataLength & 0x00FF;

	memcpy(&data[2], ResponsePDU.Data, 0x06);

	ret = CanTp_CanIf_UpdateTxListMsgDlcData(ResponsePDU.BusChannel, CANTP_DIAG_RESP_ADDR, 0x08, data);

	return ret;
}

/****************************************************************************
 * @function	CanTp_TxDiagMsgCF
 * @brief  		Send diagnostic message function of consecutive frame
 * @param  		SN : input parameters,
 * 				ResponsePDU : input parameters, response protocol data unit
 * 				DataOffset : input parameters, show start offset address of response PDU
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_TxDiagMsgCF(uint8 SN,CanTp_ProtocolDataUnitStruct_Type ResponsePDU,uint8 DataOffset)
{

	uint8 ret = E_NOT_OK;
	uint8 RecvDataLength = 0x00;
	uint8 data[8] = {0x00};

	memset(data, CANTP_PADDING_BYTE, 0x08);

	data[0] = CommFunc_BitShiftLeft(CANTP_FRAME_TYPE_FF,0x04) | SN;

	if((DataOffset + 0x07) > ResponsePDU.DataLength )
	{
		RecvDataLength = ResponsePDU.DataLength - DataOffset;
	}
	else
	{
		RecvDataLength = 0x07;
	}

	memcpy(&data[1], ResponsePDU.Data, RecvDataLength);

	ret = CanTp_CanIf_UpdateTxListMsgDlcData(ResponsePDU.BusChannel, CANTP_DIAG_RESP_ADDR, 0x08, data);

	return CommFunc_BitShiftLeft(RecvDataLength, 0x04) | ret;
}

/****************************************************************************
 * @function	CanTp_TxDiagMsgFC
 * @brief  		Send diagnostic message function of flow control frame
 * @param  		FlowStatus : input parameters
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_TxDiagMsgFC(uint8 FlowStatus)
{
	uint8 ret = E_NOT_OK;
	uint8 data[8] = {0x00};

	memset(data, CANTP_PADDING_BYTE, 0x08);

	data[0] = CommFunc_BitShiftLeft(CANTP_FRAME_TYPE_CF,0x04) | FlowStatus;
	data[1] = CANTP_PARAM_BS;
	data[2] = CANTP_PARAM_STMIN;

	/*In this version,can tp only support single channel of can bus*/
	ret = CanTp_CanIf_UpdateTxListMsgDlcData(0x00, CANTP_DIAG_RESP_ADDR, 0x08, data);

	return ret;
}

/****************************************************************************
 * @function	CanTp_WriteRecvBuffer
 * @brief  		write can message to cantp buffer
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_WriteRecvBuffer(uint8 chno, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
{
	uint8 ret = E_OK;


	return ret;
}

/****************************************************************************
 * @function	CanTp_ReadRecvBuffer
 * @brief  		read can message to cantp buffer
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_ReadRecvBuffer(uint8* ptr_chno, uint32* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc)
{
	uint8 ret = E_OK;


	return ret;
}

/*********************************File End*********************************/
