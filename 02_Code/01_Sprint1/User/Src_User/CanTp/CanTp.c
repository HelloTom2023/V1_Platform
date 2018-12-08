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
	/*Init CanTp_RxPduCtrInfo parameters*/
	CanTp_RxPduCtrInfo.Data = CanTp_RxPudBuffer;

	/*Init CanTp_TxPduCtrInfo parameters*/
	CanTp_TxPduCtrInfo.BusChannel = 0x00;
	CanTp_TxPduCtrInfo.Data = CanTp_TxPudBuffer;
	CanTp_TxPduCtrInfo.MsgId = CANTP_DIAG_RESP_ADDR;
	CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_IDLE;
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
/*需要考虑一下这个函数的执行周期，因为CANTP的时间参数的实现，需要依赖于主函数的执行情况*/
uint16 snake_debug_counter = 0x00;
CAN_TP_LOCAL_API void CanTp_TxManagementFunction(void)
{
	uint8 data[128] = {0x00,0x00,0x00};

	switch(CanTp_TxPduCtrInfo.TxMachineState)
	{
		case CANTP_TXMS_IDLE:
		{
			/*doing nothing*/
			/*test code*/
			/*snake_debug_counter++;
			if(snake_debug_counter >= 5000)
			{
				snake_debug_counter = 0x00;
				CanTp_TxPduCtrInfo.BusChannel = 0x00;
				CanTp_TxPduCtrInfo.Data = data;
				CanTp_TxPduCtrInfo.MsgId = CANTP_DIAG_RESP_ADDR;
				CanTp_TxPduCtrInfo.TotalDataLength ++;
				CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_TX_REQ;
				CanTp_TxPduCtrInfo.TxDataLength = 0x00;
			}*/
			break;
		}

		case CANTP_TXMS_TX_REQ:
		{
			/*check the pdu type*/
			/*if the data length is more than 0x07,modules need to send multiple frames.*/
			if(CanTp_TxPduCtrInfo.TotalDataLength > 0x07)
			{
				CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_TX_FF;
				/*init control parameters*/
				CanTp_TxPduCtrInfo.TxDataLength = 0x00;
				CanTp_TxPduCtrInfo.SN = 0x01;
			}
			else
			{
				CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_TX_SF;
			}
			break;
		}

		case CANTP_TXMS_TX_SF:
		{
			CanTp_Debug_OutputInfo(_T("CanTp Send SF....TotalDataLength = %d\n",CanTp_TxPduCtrInfo.TotalDataLength));
			CanTp_TxDiagMsgSF(	CanTp_TxPduCtrInfo.BusChannel,	\
								CanTp_TxPduCtrInfo.MsgId, \
								CanTp_TxPduCtrInfo.TotalDataLength, \
								CanTp_TxPduCtrInfo.Data);
			CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_TX_OVER;
			break;
		}

		case CANTP_TXMS_TX_FF:
		{
			CanTp_Debug_OutputInfo(_T("CanTp Send FF....TotalDataLength = %d\n",CanTp_TxPduCtrInfo.TotalDataLength));
			CanTp_TxDiagMsgFF(	CanTp_TxPduCtrInfo.BusChannel,	\
								CanTp_TxPduCtrInfo.MsgId, \
								CanTp_TxPduCtrInfo.TotalDataLength, \
								CanTp_TxPduCtrInfo.Data);
			CanTp_TxPduCtrInfo.TxDataLength = 0x06;
			CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_WT_FC;
			break;
		}

		case CANTP_TXMS_WT_FC:
		{
			/*
			 * wait strategy
			 *
			 * reserved :
			 *
			 * */
			CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_TX_CF;
			break;
		}

		case CANTP_TXMS_TX_CF:
		{
			uint8 ret = 0x00;
			uint8 TxDataLength = 0x00;

			ret = CanTp_TxDiagMsgCF(	CanTp_TxPduCtrInfo.BusChannel,	\
								CanTp_TxPduCtrInfo.MsgId, \
								CanTp_TxPduCtrInfo.TotalDataLength, \
								CanTp_TxPduCtrInfo.SN,	\
								CanTp_TxPduCtrInfo.Data,	\
								CanTp_TxPduCtrInfo.TxDataLength);
			/*
			 * check the function perform result
			 *
			 * reserved :
			 * add Repeat sending strategy
			 * */

			TxDataLength = CommFunc_BitShiftRigth(ret,0x04) & 0x0F;

			CanTp_TxPduCtrInfo.TxDataLength = CanTp_TxPduCtrInfo.TxDataLength + TxDataLength;

			if(CanTp_TxPduCtrInfo.TxDataLength == CanTp_TxPduCtrInfo.TotalDataLength)
			{
				CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_TX_OVER;
			}
			else
			{
				CanTp_TxPduCtrInfo.SN++;
				/*SN Control*/
				if(CanTp_TxPduCtrInfo.SN > 0x0F)
				{
					CanTp_TxPduCtrInfo.SN = 0x00;
				}
				else
				{
					/*Doing nothing*/
				}

				/*Check the SN Range*/
				/*
				 * If ecu is Transmitter,it will wait flow control.
				 * so check  receives flow control frame BS parameters equal with CanTp_TxPduCtrInfo.SN
				 * */
				if(CanTp_TxPduCtrInfo.SN == CanTp_ProtocolControlUnit.BS)
				{
					/*if the send consecutive frame times equal BS,the ecu will wait flow control frame*/
					CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_WT_FC;
				}
				else
				{
					/*Doing nothing*/
				}
			}
			break;
		}

		case CANTP_TXMS_TX_OVER:
		{
			CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_IDLE;
			break;
		}

		default:
		{
			/*Doing nothing*/
			break;
		}
	}
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

	CanTp_RxPduCtrInfo.RxLockFlag = 0x01;
	CanTp_RxPduCtrInfo.FrameType = CANTP_FRAME_TYPE_SF;
	CanTp_RxPduCtrInfo.MsgId = MsgId;

	if(MsgId == CANTP_DIAG_PHY_ADDR)
	{
		CanTp_RxPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_PHY;
	}
	else
	{
		CanTp_RxPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_FUNC;
	}

	/*check diagnostic message data length*/
	DataLength = (uint8) (ptr_Data[0] & 0x0F);
	if((DataLength >= 1) && (DataLength <= 7))
	{
		uint8 i = 0x00;

		CanTp_RxPduCtrInfo.TotalDataLength = DataLength;
		CanTp_RxPduCtrInfo.RxDataLength = DataLength;
		memcpy(CanTp_RxPduCtrInfo.Data, &ptr_Data[1], CanTp_RxPduCtrInfo.RxDataLength);

		/*notification to dcm modules*/
		CanTp_NotificationDiagnosticRequestData(CanTp_RxPduCtrInfo);

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


	CanTp_RxPduCtrInfo.RxLockFlag = 0x01;
	CanTp_RxPduCtrInfo.FrameType = CANTP_FRAME_TYPE_FF;
	CanTp_RxPduCtrInfo.MsgId = MsgId;

	if(MsgId == CANTP_DIAG_PHY_ADDR)
	{
		CanTp_RxPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_PHY;
	}
	else
	{
		CanTp_RxPduCtrInfo.ReqMsgType = CANTP_MSG_TYPE_REQ_FUNC;
	}

	/*Get the message length*/
	DataLength = (uint16) ( ((ptr_Data[0] & 0x0F) << 8 ) | (ptr_Data[1]) );
	/*check diagnostic message data length*/
	if(DataLength > 7)
	{
		CanTp_RxPduCtrInfo.SN = 0x01;
		CanTp_RxPduCtrInfo.TotalDataLength = DataLength;
		CanTp_RxPduCtrInfo.RxDataLength = 6;
		memcpy(CanTp_RxPduCtrInfo.Data, &ptr_Data[2], CanTp_RxPduCtrInfo.RxDataLength);
		ret = E_OK;

		/*Send flow control frame*/
		CanTp_TxDiagMsgFC(CANTP_FS_TYPE_CTS);
	}
	else
	{
		CanTp_RxPduCtrInfo.RxLockFlag = 0x00;
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
	CanTp_RxPduCtrInfo.FrameType = CANTP_FRAME_TYPE_CF;

	/*Check the diagnostic message id*/
	/*if the consecutive frame id is not equal the first frame,ignore the message*/
	if(CanTp_RxPduCtrInfo.MsgId != MsgId)
	{
		CanTp_RxPduCtrInfo.RxLockFlag = 0x00;
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
	if(SequenceNumber != CanTp_RxPduCtrInfo.SN)
	{
		ret = E_WRONG_SN;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*SN Control*/
	CanTp_RxPduCtrInfo.SN++;
	if(CanTp_RxPduCtrInfo.SN > 0x0F)
	{
		CanTp_RxPduCtrInfo.SN = 0x00;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the SN Range*/
	/*
	 * If ecu is Recipient,it will send flow control.
	 * so check  receives consecutive frame SN parameters equal with CANTP_PARAM_BS
	 * */
	if(CanTp_RxPduCtrInfo.SN == CANTP_PARAM_BS)
	{
		/*Send flow control frame*/
		CanTp_TxDiagMsgFC(CANTP_FS_TYPE_CTS);
	}
	else
	{
		/*Doing nothing*/
	}

	/*check diagnostic message data length*/
	if((CanTp_RxPduCtrInfo.RxDataLength + 7) >= CanTp_RxPduCtrInfo.TotalDataLength)/*this frame is last frame message*/
	{
		memcpy((CanTp_RxPduCtrInfo.Data + CanTp_RxPduCtrInfo.RxDataLength), \
				&ptr_Data[1], \
				(CanTp_RxPduCtrInfo.TotalDataLength - CanTp_RxPduCtrInfo.RxDataLength));
		CanTp_RxPduCtrInfo.RxDataLength = CanTp_RxPduCtrInfo.TotalDataLength;

		/*the cantp receives data shall notification to Dcm modules*/
		CanTp_NotificationDiagnosticRequestData(CanTp_RxPduCtrInfo);

		ret = E_OK;
	}
	else
	{
		memcpy((CanTp_RxPduCtrInfo.Data + CanTp_RxPduCtrInfo.RxDataLength), \
					&ptr_Data[1], (0x07));
		CanTp_RxPduCtrInfo.RxDataLength = CanTp_RxPduCtrInfo.RxDataLength + 7;
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
	CanTp_RxPduCtrInfo.FrameType = CANTP_FRAME_TYPE_FC;

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
	/*CanTp_Debug_OutputInfo(_T("CanTp_TxCanFrame :\n ChNo = %d,MsgId = 0x%lx Data = [%x %x %x %x %x %x %x %x]\n",\
				ChNo,MsgId,ptr_Data[0],ptr_Data[1],ptr_Data[2],ptr_Data[3],ptr_Data[4],ptr_Data[5],ptr_Data[6],ptr_Data[7]));
				*/
	return CanTp_CanIf_UpdateTxListMsgDlcData(ChNo,MsgId,Dlc,ptr_Data);
}

/****************************************************************************
 * @function	CanTp_TxDiagMsgSF
 * @brief  		Send diagnostic message function of single frame
 * @param  		ChNo : input parameters, diagnostic transport channel
 * 				MsgId : input parameters, diagnostic message id
 * 				SF_DL : input parameters, diagnostic single frame data length
 * 				ptr_ResponseData : input parameters, diagnostic response data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_TxDiagMsgSF(uint8 ChNo,uint32 MsgId,uint8 SF_DL,uint8* ptr_ResponseData)
{
	uint8 ret = E_NOT_OK;
	uint8 data[8] = {0x00};

	/*Check the point is null*/
	if(NULL == ptr_ResponseData)
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	memset(data, CANTP_PADDING_BYTE, 0x08);

	data[0] = CommFunc_BitShiftLeft(CANTP_FRAME_TYPE_SF,0x04) | SF_DL;
	memcpy(&data[1], ptr_ResponseData, SF_DL);

	CanTp_Debug_OutputInfo(_T("CanTp_TxDiagMsgSF :\n ChNo = %d,MsgId = 0x%lx Data = [%x %x %x %x %x %x %x %x]\n",\
			ChNo,MsgId,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]));

	ret = CanTp_TxCanFrame(ChNo, MsgId, 0x08, data);

	return ret;
}

/****************************************************************************
 * @function	CanTp_TxDiagMsgFF
 * @brief  		Send diagnostic message function of first frame
 * @param  		ChNo : input parameters, diagnostic transport channel
 * 				MsgId : input parameters, diagnostic message id
 * 				FF_DL : input parameters, diagnostic first frame data length
 * 				ptr_ResponseData : input parameters, diagnostic response data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_TxDiagMsgFF(uint8 ChNo,uint32 MsgId,uint32 FF_DL,uint8* ptr_ResponseData)
{
	uint8 ret = E_NOT_OK;
	uint8 data[8] = {0x00};

	/*Check the point is null*/
	if(NULL == ptr_ResponseData)
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	data[0] = CommFunc_BitShiftLeft(CANTP_FRAME_TYPE_FF,0x04) | (FF_DL & 0x0F00);
	data[1] = FF_DL & 0x00FF;

	memcpy(&data[2], ptr_ResponseData, 0x06);

	CanTp_Debug_OutputInfo(_T("CanTp_TxDiagMsgFF :\n ChNo = %d,MsgId = 0x%lx Data = [%x %x %x %x %x %x %x %x]\n",\
				ChNo,MsgId,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]));

	ret = CanTp_TxCanFrame(ChNo, MsgId, 0x08, data);

	return ret;
}

/****************************************************************************
 * @function	CanTp_TxDiagMsgCF
 * @brief  		Send diagnostic message function of consecutive frame
 * @param  		ChNo : input parameters, diagnostic transport channel
 * 				MsgId : input parameters, diagnostic message id
 * 				FF_DL : input parameters, diagnostic first frame data length
 * 				SN :input parameters, diagnostic CF SN parameters
 * 				ptr_ResponseData : input parameters, diagnostic response data
 * 				DataOffset : input parameters, show start offset address of response data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_TxDiagMsgCF(uint8 ChNo,uint32 MsgId,uint32 FF_DL,uint8 SN,uint8* ptr_ResponseData,uint8 DataOffset)
{

	uint8 ret = E_NOT_OK;
	uint8 RxDataLength = 0x00;
	uint8 data[8] = {0x00};

	/*Check the point is null*/
	if(NULL == ptr_ResponseData)
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	memset(data, CANTP_PADDING_BYTE, 0x08);

	data[0] = CommFunc_BitShiftLeft(CANTP_FRAME_TYPE_CF,0x04) | SN;

	if((DataOffset + 0x07) > FF_DL )
	{
		RxDataLength = FF_DL - DataOffset;
	}
	else
	{
		RxDataLength = 0x07;
	}

	memcpy(&data[1], (ptr_ResponseData + DataOffset), RxDataLength);

	CanTp_Debug_OutputInfo(_T("CanTp_TxDiagMsgCF :\n ChNo = %d,MsgId = 0x%lx Data = [%x %x %x %x %x %x %x %x]\n",\
					ChNo,MsgId,data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]));

	ret = CanTp_TxCanFrame(ChNo, MsgId, 0x08, data);

	return CommFunc_BitShiftLeft(RxDataLength, 0x04) | ret;
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

	data[0] = CommFunc_BitShiftLeft(CANTP_FRAME_TYPE_FC,0x04) | FlowStatus;
	data[1] = CANTP_PARAM_BS;
	data[2] = CANTP_PARAM_STMIN;

	CanTp_Debug_OutputInfo(_T("CanTp_TxDiagMsgFC :\n Data = [%x %x %x %x %x %x %x %x]\n",\
						data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]));

	/*In this version,can tp only support single channel of can bus*/
	ret = CanTp_TxCanFrame(0x00, CANTP_DIAG_RESP_ADDR, 0x08, data);

	return ret;
}

/****************************************************************************
 * @function	CanTp_NotificationDiagnosticRequestData
 * @brief  		send diagnostic data to Dcm modules
 * @param  		DiagReqData : intput parameters,
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_NotificationDiagnosticRequestData(CanTp_RxPduControlInformation_Type DiagReqData)
{
	uint8 ret = E_NOT_OK;

	if(DiagReqData.TotalDataLength == DiagReqData.RxDataLength)
	{
		ret = CanTp_NotificationDiagReqInfoToDcm(	DiagReqData.BusChannel,	\
													DiagReqData.ReqMsgType,	\
													DiagReqData.TotalDataLength,	\
													DiagReqData.Data);

	}
	else
	{
		/*Doing nothing*/
	}

	return ret;
}

/****************************************************************************
 * @function	CanTp_ReceiveDiagnosticResponseData
 * @brief  		receive diagnostic response data from Dcm modules
 * @param  		ChNo : intput parameters,
 * 				DatLength : input parameters, diagnostic response data length
 * 				ptr_Data : input parameters,diagnostic response data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_EXTERN_API uint8 CanTp_ReceiveDiagnosticResponseData(uint8 ChNo,uint16 DataLength,uint8* ptr_Data)
{
	uint8 ret = E_NOT_OK;

	/*Input parameters check*/
	if(NULL == ptr_Data)
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*
	 * clear this parameters : unlock the diagnostic PDU receive flag
	 * mean the can tp modules can be receive next diagnostic PDU
	 * */
	CanTp_RxPduCtrInfo.RxLockFlag = 0x00;

	/*Check the tx machine state*/
	/*can tp modules have PDU being sending in the time, can tp shall be ignore this PDU*/
	if(CANTP_TXMS_IDLE != CanTp_TxPduCtrInfo.TxMachineState)
	{
		ret = E_STATUS_ERROR;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Receive the pdu from DCM modules*/
	/*
	 * if the data length equal 0.
	 * mean the dcm modules perform diagnostic request,but not response.
	 * */
	if(DataLength > 0x00)
	{
		CanTp_TxPduCtrInfo.BusChannel = ChNo;
		CanTp_TxPduCtrInfo.TotalDataLength = DataLength;
		memcpy(CanTp_TxPduCtrInfo.Data, ptr_Data,DataLength);
		CanTp_TxPduCtrInfo.TxMachineState = CANTP_TXMS_TX_REQ;
	}
	else
	{
		/*Doing nothing*/
	}

	ret = E_OK;

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
