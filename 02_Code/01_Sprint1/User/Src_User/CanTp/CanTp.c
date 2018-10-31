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

	/**/
	//if()

	switch(ptr_Data[0] & 0xF0)
	{
		case CANTP_FRAME_TYPE_SF:
			CanTp_RxIndicationFunctionSF(ChNo, MsgId, ptr_Data, Dlc);
			break;

		case CANTP_FRAME_TYPE_FF:

			break;

		case CANTP_FRAME_TYPE_CF:

			break;

		case CANTP_FRAME_TYPE_FC:

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

	/*check diagnostic channel and message id*/
	if( (CANTP_DIAG_CHANNEL_ADDR == ChNo) && ((MsgId == CANTP_DIAG_PHY_ADDR) || (MsgId == CANTP_DIAG_FUNC_ADDR)) )
	{
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
			CanTp_RecvPduCtrInfo.TotalDataLength = DataLength;
			CanTp_RecvPduCtrInfo.RecvDataLength = DataLength;
			memcpy(CanTp_RecvPduCtrInfo.ReqData, &ptr_Data[1], CanTp_RecvPduCtrInfo.RecvDataLength);
			ret = E_OK;
		}
		else
		{
			ret = E_PARAM_INVALID;
		}

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

	/*check diagnostic channel and message id*/
	if( (CANTP_DIAG_CHANNEL_ADDR == ChNo) && ((MsgId == CANTP_DIAG_PHY_ADDR) || (MsgId == CANTP_DIAG_FUNC_ADDR)) )
	{
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
