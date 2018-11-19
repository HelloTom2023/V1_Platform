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


/*Function implement AREA*/
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
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_EXTERN_API uint8 CanTp_RxIndicationFunction(uint8 ChNo, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_TP_EXTERN_API uint8 CanTp_RxIndicationFunction(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
{
	uint8 ret = E_NOT_OK;
	uint8 ret_subfunc = E_OK;

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
			break;

		case CANTP_FRAME_TYPE_FC:
			CanTp_Debug_OutputInfo(_T("CanTp Recv FC...\n"));

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
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionSF(uint8 ChNo, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionSF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
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
		uint8 i = 0x00;

		CanTp_RecvPduCtrInfo.TotalDataLength = DataLength;
		CanTp_RecvPduCtrInfo.RecvDataLength = DataLength;
		memcpy(CanTp_RecvPduCtrInfo.ReqData, &ptr_Data[1], CanTp_RecvPduCtrInfo.RecvDataLength);

		CanTp_DcmPdu.BusChannel = ChNo;
		CanTp_DcmPdu.PduType = 0x00;
		CanTp_DcmPdu.MsgType = CanTp_RecvPduCtrInfo.ReqMsgType;
		CanTp_DcmPdu.DataLength = CanTp_RecvPduCtrInfo.TotalDataLength;
		memcpy(CanTp_DcmPdu.ReqData, CanTp_RecvPduCtrInfo.ReqData, CanTp_DcmPdu.DataLength);

		CanTp_Debug_OutputInfo(_T("BusChannel = %d,PduType = 0x%d,MsgType = 0x%x,DataLength = %d,ReqData : [",\
				CanTp_DcmPdu.BusChannel,CanTp_DcmPdu.PduType,CanTp_DcmPdu.MsgType,CanTp_DcmPdu.DataLength));
		for(i = 0x00; i<DataLength; i++)
		{
			CanTp_Debug_OutputInfo(_T("0x%x ",CanTp_DcmPdu.ReqData[i]));
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
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFF(uint8 ChNo, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
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

	/*check diagnostic message data length*/
	DataLength = (uint16) ( ((ptr_Data[0] & 0x0F) << 8 ) | (ptr_Data[1]) );
	if(DataLength > 7)
	{
		CanTp_RecvPduCtrInfo.TotalDataLength = DataLength;
		CanTp_RecvPduCtrInfo.RecvDataLength = 6;
		memcpy(CanTp_RecvPduCtrInfo.ReqData, &ptr_Data[2], CanTp_RecvPduCtrInfo.RecvDataLength);
		ret = E_OK;
		/*Send flow control frame */

	}
	else
	{
		ret = E_PARAM_INVALID;
	}

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
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_WriteRecvBuffer(uint8 chno, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_TP_LOCAL_API uint8 CanTp_WriteRecvBuffer(uint8 chno, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
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
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_ReadRecvBuffer(uint8* ptr_chno, uint16* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc)
#else
CAN_TP_LOCAL_API uint8 CanTp_ReadRecvBuffer(uint8* ptr_chno, uint32* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc)
#endif
{
	uint8 ret = E_OK;


	return ret;
}

/*********************************File End*********************************/
