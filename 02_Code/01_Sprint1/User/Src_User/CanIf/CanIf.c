/****************************************************************************
* File Name : CanIf.c
*
* Modules : CAN Interface Layer source file
*
* Summary : 1.The module between CAN Driver layer and Can Server layer modules.
*			2.The module user encapsulates the Can Driver Layer APIs.
*			3.Implements can message receive,transmission and message data handle.
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-26
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/

/*Include head files AREA*/
#include "CanIf.h"



/*Macro definition AREA*/




/*Variable declaration AREA*/


/*Function implement AREA*/
/****************************************************************************
 * @function	CanIf_Init
 * @brief  		can interface layer init function.
 * @param  		NULL
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API void CanIf_Init(void)
{
	/*Init the CanIf_CanTxMsgCtrInfo*/
	CanIf_CanTxMsgCtrInfo.HwBufNo = 0x00;
	CanIf_CanTxMsgCtrInfo.TxListIndex = 0x00;

	/*Init Can message buffer operate control information*/
	CanIf_CanRecvMsgBuffCtrInfo.ReadIndex = 0x00;
	CanIf_CanRecvMsgBuffCtrInfo.WriteIndex = 0x00;

	/*Init message receive buffer*/
	memset(CanIf_CanRecvMsgBuff,0x00,CANIF_RECEIVEBUFFERNUMBER);
}

/****************************************************************************
 * @function	CanIf_MainFunction
 * @brief  		can interface layer main function.
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API void CanIf_MainFunction(void)
{
	CanIf_RxMainFunction();
	CanIf_TxMainFunction();
}


/****************************************************************************
 * @function	CANbus_RecvInterruptCallBack
 * @brief  		the CAN BUS receive interrupt call back function.
 * @param  		ChNo: input parameters,CAN channel index.
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_RecvInterruptCallback(uint8 ChNo)
{
	uint8 BufIndex;
	uint8 ret = E_NOT_OK;
	uint8 ret_subfunc = E_OK;

	/*get hardware buffer index*/
	BufIndex = CanIf_GetControllerHwMsgBuffIndex(ChNo);

	if(BufIndex <= CANIF_CONTROLLERHWBUFFERNUMBER)
	{
		CanIf_CanMsgStruct_Type  CanRecvMsg;

		/*get can message id,data and dlc from controller hardware buffer*/
		CanRecvMsg.CanChNo = ChNo;
		/*
		 * If the CANIF_CANMESSAGEIDTYPE is STANDARD,the sturct elements CanMsgId data type is uint16,
		 * but the CanIf_GetControllerMsgBuffData function parameters data type is uint32.
		 * When the CANIF_CANMESSAGEIDTYPE is STANDARD,the function parameter has a type mismatch problem.
		 * */
		CanIf_GetControllerMsgInfo(ChNo, BufIndex, &CanRecvMsg.CanMsgId, CanRecvMsg.CanData, &CanRecvMsg.CanMsgDlc);

		/*notification application layer callback : PreCopy Function callback*/
		if(E_OK != CanIf_PreCopy(CanRecvMsg.CanChNo, CanRecvMsg.CanMsgId, CanRecvMsg.CanData, CanRecvMsg.CanMsgDlc))
		{
			ret = E_NOT_OK;
		}
		else
		{
			/*write data to CanIf_CanRecvMsgBuf buffer*/
			ret = CanIf_WriteRecvBuffer(CanRecvMsg.CanChNo, CanRecvMsg.CanMsgId, CanRecvMsg.CanData, CanRecvMsg.CanMsgDlc);
		}
	}

	return ret;
}

/****************************************************************************
 * @function	CanIf_SendInterruptCallback
 * @brief  		the CAN BUS send interrupt call back function.
 * @param  		ChNo: input parameters,CAN channel index.
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SendInterruptCallback(uint8 ChNo)
{
	uint8 ret = E_NOT_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_WriteRecvBuffer
 * @brief  		write can message to canif buffer
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_IF_LOCAL_API uint8 CanIf_WriteRecvBuffer(uint8 chno, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_IF_LOCAL_API uint8 CanIf_WriteRecvBuffer(uint8 chno, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
{
	uint8 ret = E_OK;

	/*Check Write index is valid*/
	if(CanIf_CanRecvMsgBuffCtrInfo.WriteIndex >= CANIF_RECEIVEBUFFERNUMBER)
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}

	if(E_OK == ret)
	{
		/*write data to buffer*/
		CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.WriteIndex].CanChNo = chno;
		CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.WriteIndex].CanMsgId = MsgId;
		CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.WriteIndex].CanMsgDlc = Dlc;
		memcpy(CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.WriteIndex].CanData,ptr_Data,Dlc);

		/*write point ++ */
		CanIf_CanRecvMsgBuffCtrInfo.WriteIndex++;
		if(CanIf_CanRecvMsgBuffCtrInfo.WriteIndex >= CANIF_RECEIVEBUFFERNUMBER)
		{
			CanIf_CanRecvMsgBuffCtrInfo.WriteIndex = 0x00;
		}
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_ReadRecvBuffer
 * @brief  		read can message to canif buffer
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_IF_LOCAL_API uint8 CanIf_ReadRecvBuffer(uint8* ptr_chno, uint16* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc)
#else
CAN_IF_LOCAL_API uint8 CanIf_ReadRecvBuffer(uint8* ptr_chno, uint32* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc)
#endif
{
	uint8 ret = E_OK;

	/*Check Read index is valid*/
	if(CanIf_CanRecvMsgBuffCtrInfo.ReadIndex >= CANIF_RECEIVEBUFFERNUMBER)
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}

	if(E_OK == ret)
	{
		/*write data to buffer*/
		*ptr_chno = CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.ReadIndex].CanChNo;
		*ptr_MsgId = CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.ReadIndex].CanMsgId;
		*ptr_Dlc = CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.ReadIndex].CanMsgDlc;
		memcpy(ptr_Data, CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.ReadIndex].CanData,CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.ReadIndex].CanMsgDlc);

		/*write point ++ */
		CanIf_CanRecvMsgBuffCtrInfo.ReadIndex++;
		if(CanIf_CanRecvMsgBuffCtrInfo.ReadIndex >= CANIF_RECEIVEBUFFERNUMBER)
		{
			CanIf_CanRecvMsgBuffCtrInfo.ReadIndex = 0x00;
		}
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_RxMainFunction
 * @brief  		the can interface layer receive message main function
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_RxMainFunction(void)
{
	CanIf_RxManagementFunction();
	CanIf_RxTimerHandleFunction();
	CanIf_MsgTimeoutCheck();
}

/****************************************************************************
 * @function	CanIf_RxManagementFunction
 * @brief  		handles the rx buffer data
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_RxManagementFunction(void)
{
	CanIf_CanMsgStruct_Type ReadCanRecvMsg;

	/*check the can receive message buffer is new data*/
	if(CanIf_CanRecvMsgBuffCtrInfo.ReadIndex != CanIf_CanRecvMsgBuffCtrInfo.WriteIndex)
	{
		/*Read data and notification to Can Transport layer*/
		CanIf_ReadRecvBuffer(&ReadCanRecvMsg.CanChNo, &ReadCanRecvMsg.CanMsgId , ReadCanRecvMsg.CanData , &ReadCanRecvMsg.CanMsgDlc);

		/*have other idea : in the receive interrupt callback function check message.*/
		/*Message id check*/
		if(E_OK != CanIf_MsgIdCheck(ReadCanRecvMsg.CanChNo, ReadCanRecvMsg.CanMsgId) )
		{
			return;
		}
		else
		{
			/*Doing nothing*/
		}

		/*overload the message timeout timer*/
		CanIf_OverloadMsgTimeoutTimer(ReadCanRecvMsg.CanChNo, ReadCanRecvMsg.CanMsgId);

		/*Check Dlc*/
		if(E_OK != CanIf_MsgDlcCheck(ReadCanRecvMsg.CanChNo, ReadCanRecvMsg.CanMsgId, ReadCanRecvMsg.CanMsgDlc))
		{
			return;
		}
		else
		{
			/*Doing nothing*/
		}

		if((CANIF_DIAG_CHANNEL_ADDR != ReadCanRecvMsg.CanChNo) &&
				((CANIF_DIAG_PHY_ADDR == ReadCanRecvMsg.CanMsgId) || (CANIF_DIAG_FUNC_ADDR == ReadCanRecvMsg.CanMsgId)))
		{
			/*Notification to CAN Transport Layer*/
			CanIf_CanTp_RecvNotificationFunction(ReadCanRecvMsg.CanChNo, ReadCanRecvMsg.CanMsgId, ReadCanRecvMsg.CanData, ReadCanRecvMsg.CanMsgDlc);
		}
		else if((CANIF_NM_CHANNEL_ADDR != ReadCanRecvMsg.CanChNo) && (CANIF_NM_BASE_ADDR == (ReadCanRecvMsg.CanMsgId & CANIF_NM_MASK_CODE) ) )
		{
			/*Notification to can network managements layer*/

		}
		else
		{
			/*Notification to communication server layer*/
			CanIf_Com_RxNotificationFunction(ReadCanRecvMsg.CanChNo, ReadCanRecvMsg.CanMsgId, ReadCanRecvMsg.CanData, ReadCanRecvMsg.CanMsgDlc);
		}
	}
}

/****************************************************************************
 * @function	CanIf_MsgIdCheck
 * @brief  		software filter
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_MsgIdCheck(uint8 ChNo, uint32 MsgId)
{
	uint8 ret = E_NOT_OK;
	uint8 index = 0x00;

	/*get the message id in RxList index*/
	ret = CanIf_GetRxListIndex(&index,ChNo,MsgId);
	if(E_OK != ret)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*check the message is valid*/
	if(CANIF_MSG_VALID != CanIf_CanMsgRxList[index].MsgValid)
	{
		return E_MSG_INVALID;
	}
	else
	{
		/*doing nothing*/
	}

	/*Check MsgCheckMode*/
	if(CANIF_CHECK_MODE_ID == (CanIf_CanMsgRxList[index].MsgCheckMode & CANIF_CHECK_MODE_ID) )
	{
		/*compare the message id*/
		if(MsgId == CanIf_CanMsgRxList[index].MsgId)
		{
			CanIf_CanMsgRxList[index].MsgCheckRet = CanIf_CanMsgRxList[index].MsgCheckRet & (~CANIF_CHECK_MODE_ID);
			ret = E_OK;
		}
		else
		{
			CanIf_CanMsgRxList[index].MsgCheckRet = CanIf_CanMsgRxList[index].MsgCheckRet | CANIF_CHECK_MODE_ID;
			ret = E_NOT_OK;
		}
	}
	else
	{
		CanIf_CanMsgRxList[index].MsgCheckRet = CanIf_CanMsgRxList[index].MsgCheckRet & (~CANIF_CHECK_MODE_ID);
		/*if you message not support message id check,return E_OK*/
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_MsgDlcCheck
 * @brief
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters.
 * 				Dlc : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_MsgDlcCheck(uint8 ChNo, uint32 MsgId,uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint8 index = 0x00;

	/*get the message id in RxList index*/
	ret = CanIf_GetRxListIndex(&index,ChNo,MsgId);
	if(E_OK != ret)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*check the message is valid*/
	if(CANIF_MSG_VALID != CanIf_CanMsgRxList[index].MsgValid)
	{
		return E_MSG_INVALID;
	}
	else
	{
		/*doing nothing*/
	}

	/*Check MsgCheckMode*/
	if(CANIF_CHECK_MODE_DLC == (CanIf_CanMsgRxList[index].MsgCheckMode & CANIF_CHECK_MODE_DLC) )
	{
		/*compare the message dlc*/
		if(Dlc == CanIf_CanMsgRxList[index].Dlc)
		{
			CanIf_CanMsgRxList[index].MsgCheckRet = CanIf_CanMsgRxList[index].MsgCheckRet & (~CANIF_CHECK_MODE_DLC);
			ret = E_OK;
		}
		else
		{
			CanIf_CanMsgRxList[index].MsgCheckRet = CanIf_CanMsgRxList[index].MsgCheckRet | CANIF_CHECK_MODE_DLC;
			ret = E_NOT_OK;
		}
	}
	else
	{
		CanIf_CanMsgRxList[index].MsgCheckRet = CanIf_CanMsgRxList[index].MsgCheckRet & (~CANIF_CHECK_MODE_DLC);
		/*if you message not support message dlc check,return E_OK*/
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_MsgTimeoutCheck
 * @brief
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_MsgTimeoutCheck(void)
{
	uint8 index = 0x00;
	uint8 RxListLength = sizeof(CanIf_CanMsgRxList) / sizeof(CanIf_CanMsgRxManagementDataBuffer_Type);

	for(index = 0 ; index < RxListLength ; index++)
	{
		/*check the message is valid*/
		if(CANIF_MSG_VALID != CanIf_CanMsgRxList[index].MsgValid)
		{
			/*if the message is invalid,break current loop,and start next loop*/
			continue;
		}
		else
		{
			/*doing nothing*/
		}

		/*Check MsgRxMode is CANIF_MSG_MODE_PERIODIC or CANIF_MSG_MODE_MIXED*/
		if(	(CANIF_MSG_MODE_PERIODIC != CanIf_CanMsgRxList[index].MsgRxMode) && \
				(CANIF_MSG_MODE_MIXED != CanIf_CanMsgRxList[index].MsgRxMode)	)
		{
			/*if the message is not PERIODIC or MIXED message,break current loop,and start next loop*/
			continue;
		}
		else
		{
			/*doing nothing*/
		}

		/*check the message check mode support timeout check*/
		if(CANIF_CHECK_MODE_TIMEOUT != (CanIf_CanMsgRxList[index].MsgCheckMode & CANIF_CHECK_MODE_TIMEOUT) )
		{
			/*if the message is not support CANIF_CHECK_MODE_TIMEOUT,break current loop,and start next loop*/
			continue;
		}
		else
		{
			/*doing nothing*/
		}

		/*check the timer is timeout*/
		if(0x00 == CanIf_CanMsgRxList[index].CurrentTime)
		{
			CanIf_CanMsgRxList[index].MsgCheckRet = CanIf_CanMsgRxList[index].MsgCheckRet | CANIF_CHECK_MODE_TIMEOUT;
		}
		else
		{
			/*doing nothing*/
		}
	}
}

/****************************************************************************
 * @function	CanIf_OverloadMsgTimeoutTimer
 * @brief
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_OverloadMsgTimeoutTimer(uint8 ChNo, uint32 MsgId)
{
	uint8 ret = E_NOT_OK;
	uint8 index = 0x00;

	/*get the message id in RxList index*/
	ret = CanIf_GetRxListIndex(&index,ChNo,MsgId);
	if(E_OK != ret)
	{
		return ret;
	}
	else
	{
		/*doing nothing*/
	}

	/*check the message is valid*/
	if(CANIF_MSG_VALID != CanIf_CanMsgRxList[index].MsgValid)
	{
		return E_MSG_INVALID;
	}
	else
	{
		/*doing nothing*/
	}

	/*Check MsgRxMode is CANIF_MSG_MODE_PERIODIC or CANIF_MSG_MODE_MIXED*/
	if(	(CANIF_MSG_MODE_PERIODIC == CanIf_CanMsgRxList[index].MsgRxMode) || \
			(CANIF_MSG_MODE_MIXED == CanIf_CanMsgRxList[index].MsgRxMode)	)
	{
		/*check the message check mode support timeout check*/
		if(CANIF_CHECK_MODE_TIMEOUT == (CanIf_CanMsgRxList[index].MsgCheckMode & CANIF_CHECK_MODE_TIMEOUT) )
		{
			/*Over load Timeout Timer*/
			CanIf_CanMsgRxList[index].CurrentTime = CanIf_CanMsgRxList[index].Timeout;
			/*Update the timeout check result*/
			//if(CANIF_CHECK_MODE_TIMEOUT == (CanIf_CanMsgRxList[index].MsgCheckRet & CANIF_CHECK_MODE_TIMEOUT))
			{
				CanIf_CanMsgRxList[index].MsgCheckRet = CanIf_CanMsgRxList[index].MsgCheckRet & (~CANIF_CHECK_MODE_TIMEOUT);
			}
		}
		else
		{
			/*doing nothing*/
		}
	}
	else
	{
		/*doing nothing*/
	}

	return ret;
}

/****************************************************************************
 * @function	CanIf_RxTimerHandleFunction
 * @brief  		the can interface layer handle the Rx message timer and counter
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_RxTimerHandleFunction(void)
{
	uint8 index = 0x00;
	uint8 RxListLength = sizeof(CanIf_CanMsgRxList) / sizeof(CanIf_CanMsgRxManagementDataBuffer_Type);

	for(index = 0 ; index < RxListLength ; index++)
	{
		/*check the message is valid*/
		if(CANIF_MSG_VALID != CanIf_CanMsgRxList[index].MsgValid)
		{
			/*if the message is invalid,break current loop,and start next loop*/
			continue;
		}
		else
		{
			/*doing nothing*/
		}

		/*Check MsgRxMode is CANIF_MSG_MODE_PERIODIC or CANIF_MSG_MODE_MIXED*/
		if(	(CANIF_MSG_MODE_PERIODIC != CanIf_CanMsgRxList[index].MsgRxMode) && \
				(CANIF_MSG_MODE_MIXED != CanIf_CanMsgRxList[index].MsgRxMode)	)
		{
			/*if the message is not PERIODIC or MIXED message,break current loop,and start next loop*/
			continue;
		}
		else
		{
			/*doing nothing*/
		}

		/*check the message check mode support timeout check*/
		if(CANIF_CHECK_MODE_TIMEOUT != (CanIf_CanMsgRxList[index].MsgCheckMode & CANIF_CHECK_MODE_TIMEOUT) )
		{
			/*if the message is not support CANIF_CHECK_MODE_TIMEOUT,break current loop,and start next loop*/
			continue;
		}
		else
		{
			/*doing nothing*/
		}

		/*update timeout timer : CurrentTime*/
		if(0x00 != CanIf_CanMsgRxList[index].CurrentTime)
		{
			CanIf_CanMsgRxList[index].CurrentTime --;
		}
		else
		{
			/*doing nothing*/
		}
	}
}

/****************************************************************************
 * @function	CanIf_GetRxListIndex
 * @brief  		get CanIf_CanMsgRxList index base on ChNo and MsgId
 * @param		ptr_Index : output parameters,
 * 				ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListIndex(uint8* ptr_Index, uint8 ChNo, uint32 MsgId)
{
	uint8 ret = E_NOT_OK;
	uint8 index = 0x00;

	/*check input parameters is valid*/
	if(NULL == ptr_Index)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	if(ChNo >= CANIF_CANCONTROLLERCHANNELNUMBER)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	for(index = 0;  ;index++)
	{
		if(0xff == CanIf_CanMsgRxList[index].ChNo)
		{
			return E_RET_NOT_FOUND; /*not found*/
		}
		else
		{
			/*Doing nothing*/
		}

		if( (ChNo == CanIf_CanMsgRxList[index].ChNo ) && (MsgId == CanIf_CanMsgRxList[index].MsgId) )
		{
			*ptr_Index = index;
			return E_OK;
		}
		else
		{
			/*Doing nothing*/
		}
	}

	return ret;
}

/****************************************************************************
 * @function	CanIf_GetRxListChNo
 * @brief  		get CanIf_CanMsgRxList ChNo base on Index
 * @param		Index : input parameters,
 * 				ptr_ChNo : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListChNo(uint8 Index, uint8* ptr_ChNo)
{
	uint8 ret = E_NOT_OK;

	/*check input parameters is valid*/
	if(NULL == ptr_ChNo)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_ChNo = CanIf_CanMsgRxList[Index].ChNo;
	ret = E_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_GetRxListMsgValid
 * @brief  		get CanIf_CanMsgRxList MsgValid base on Index
 * @param		Index : input parameters,
 * 				ptr_MsgValid : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListMsgValid(uint8 Index, uint8* ptr_MsgValid)
{
	uint8 ret = E_NOT_OK;

	/*check input parameters is valid*/
	if(NULL == ptr_MsgValid)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_MsgValid = CanIf_CanMsgRxList[Index].MsgValid;
	ret = E_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_GetRxListMsgRxMode
 * @brief  		get CanIf_CanMsgRxList MsgRxMode base on Index
 * @param		Index : input parameters,
 * 				ptr_MsgRxMode : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListMsgRxMode(uint8 Index, uint8* ptr_MsgRxMode)
{
	uint8 ret = E_NOT_OK;

	/*check input parameters is valid*/
	if(NULL == ptr_MsgRxMode)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_MsgRxMode = CanIf_CanMsgRxList[Index].MsgRxMode;
	ret = E_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_GetRxListMsgCheckMode
 * @brief  		get CanIf_CanMsgRxList MsgCheckMode base on Index
 * @param		Index : input parameters,
 * 				ptr_MsgCheckMode : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListMsgCheckMode(uint8 Index, uint8* ptr_MsgCheckMode)
{
	uint8 ret = E_NOT_OK;

	/*check input parameters is valid*/
	if(NULL == ptr_MsgCheckMode)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_MsgCheckMode = CanIf_CanMsgRxList[Index].MsgCheckMode;
	ret = E_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_GetRxListTimeout
 * @brief  		get CanIf_CanMsgRxList Timeout base on Index
 * @param		Index : input parameters,
 * 				ptr_Timeout : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListTimeout(uint8 Index, uint16* ptr_Timeout)
{
	uint8 ret = E_NOT_OK;

	/*check input parameters is valid*/
	if(NULL == ptr_Timeout)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_Timeout = CanIf_CanMsgRxList[Index].Timeout;
	ret = E_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_GetRxListCurrentTime
 * @brief  		get CanIf_CanMsgRxList CurrentTime base on Index
 * @param		Index : input parameters,
 * 				ptr_CurrentTime : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListCurrentTime(uint8 Index, uint16* ptr_CurrentTime)
{
	uint8 ret = E_NOT_OK;

	/*check input parameters is valid*/
	if(NULL == ptr_CurrentTime)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_CurrentTime = CanIf_CanMsgRxList[Index].CurrentTime;
	ret = E_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_GetRxListMsgId
 * @brief  		get CanIf_CanMsgRxList MsgId base on Index
 * @param		Index : input parameters,
 * 				ptr_MsgId : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListMsgId(uint8 Index, uint32* ptr_MsgId)
{
	uint8 ret = E_NOT_OK;

	/*check input parameters is valid*/
	if(NULL == ptr_MsgId)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_MsgId = CanIf_CanMsgRxList[Index].MsgId;
	ret = E_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_GetRxListDlc
 * @brief  		get CanIf_CanMsgRxList Dlc base on Index
 * @param		Index : input parameters,
 * 				ptr_Dlc : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListDlc(uint8 Index, uint32* ptr_Dlc)
{
	uint8 ret = E_NOT_OK;

	/*check input parameters is valid*/
	if(NULL == ptr_Dlc)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_Dlc = CanIf_CanMsgRxList[Index].Dlc;
	ret = E_OK;

	return ret;
}

/****************************************************************************
 * @function	CanIf_SetRxListCurrentTime
 * @brief  		set CanIf_CanMsgRxList CurrentTime base on Index
 * @param		Index : input parameters,
 * 				CurrentTime : input parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_SetRxListCurrentTime(uint8 Index, uint16 CurrentTime)
{
	uint8 ret = E_OK;

	CanIf_CanMsgRxList[Index].CurrentTime = CurrentTime;

	return ret;
}


/****************************************************************************
 * @function	CanIf_TxMainFunction
 * @brief  		the can interface layer transmit message main function
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxMainFunction(void)
{
	CanIf_TxTimerHandleFunction();
	CanIf_TxManagementFunction();
}

/****************************************************************************
 * @function	CanIf_TxMainFunction
 * @brief  		the can interface layer transmit message main function
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxManagementFunction(void)
{
	/*Check the can controller hareware buffer is valid*/
	CanIf_CanControllerTxHardwareBuffIndexVaildCheck(&CanIf_CanTxMsgCtrInfo.HwBufNo);

	/*Check if the array is end*/
	if(0xff == CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].ChNo)
	{
		CanIf_CanTxMsgCtrInfo.TxListIndex = 0x00;
		return;
	}
	/*Check if the message is valid*/
	else if(1 == CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].MsgValid)
	{
		if(CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].CurrentTime >= CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].CycleTime)
		{
			if(0 == CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].MsgTxMode)/*Periodic*/
			{
				/*Setting message to can controller hardware buffer*/
				CanIf_SetControllerMsgInfo(CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].ChNo, \
						CanIf_CanTxMsgCtrInfo.HwBufNo, \
						CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].MsgId,  \
						CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].Data, \
						CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].Dlc);
				/*Request send message*/
				CanIf_ReqControllerTxMsg(CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].ChNo, \
						CanIf_CanTxMsgCtrInfo.HwBufNo);
				/*can controller hardware buffer index control*/
				CanIf_CanTxMsgCtrInfo.HwBufNo++;
				/*reset cycle timer*/
				CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].CurrentTime = 0x00;
			}
			else if(1 == CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].MsgTxMode)/*Event*/
			{
				if(CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].TransmittedCounter < CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].TransmissionCounter)
				{
					/*Setting message to can controller hardware buffer*/
					CanIf_SetControllerMsgInfo(CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].ChNo, \
							CanIf_CanTxMsgCtrInfo.HwBufNo, \
							CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].MsgId,  \
							CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].Data, \
							CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].Dlc);
					/*Request send message*/
					CanIf_ReqControllerTxMsg(CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].ChNo, \
							CanIf_CanTxMsgCtrInfo.HwBufNo);
					/*can controller hardware buffer index control*/
					CanIf_CanTxMsgCtrInfo.HwBufNo++;
					/*reset cycle timer*/
					CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].CurrentTime = 0x00;
					/*transmit times control information update*/
					CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].TransmittedCounter++;
				}
				else
				{
					/*Doing nothing*/
				}
			}
		}
	}
	else
	{
		/*Doing nothing*/
	}
	/*can TX message list index control*/
	CanIf_CanTxMsgCtrInfo.TxListIndex++;
}

/****************************************************************************
 * @function	CanIf_TxTimerHandleFunction
 * @brief  		the can interface layer handle the tx message timer and counter
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxTimerHandleFunction(void)
{
	uint8 index = 0x00;

	for(index = 0x00; 	; index++)
	{
		/*Check if the array is end*/
		if(0xff == CanIf_CanMsgTxList[index].MsgValid)
		{
			break;
		}
		/*Check if the message is valid*/
		else if(1 == CanIf_CanMsgTxList[index].MsgValid)
		{
			if(0 == CanIf_CanMsgTxList[index].MsgTxMode)/*Periodic*/
			{
				//if(CanIf_CanMsgTxList[CanIf_CanMsgTxListIndex].CurrentTime <= CanIf_CanMsgTxList[CanIf_CanMsgTxListIndex].CycleTime)
				{
					CanIf_CanMsgTxList[index].CurrentTime++;
				}
			}
			else if(1 == CanIf_CanMsgTxList[index].MsgTxMode)/*Event*/
			{
				if(CanIf_CanMsgTxList[index].TransmittedCounter < CanIf_CanMsgTxList[index].TransmissionCounter)
				{
					//if(CanIf_CanMsgTxList[CanIf_CanMsgTxListIndex].CurrentTime <= CanIf_CanMsgTxList[CanIf_CanMsgTxListIndex].CycleTime)
					{
						CanIf_CanMsgTxList[index].CurrentTime++;
					}
				}
				else
				{
					/*Doing nothing*/
				}
			}
			else
			{
				/*Doing nothing*/
			}
		}
		else
		{
			/*Doing nothing*/
		}

	}
}

/****************************************************************************
 * @function	CanIf_CanControllerTxHardwareBuffIndexVaildCheck
 * @brief  		can interface layer check can controller Tx hardware buffer Index
 * @param		ptr_bufNo : input and output parameter,controller hardware buffer index
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_CanControllerTxHardwareBuffIndexVaildCheck(uint8* ptr_bufNo)
{
	if(*ptr_bufNo >= CANIF_CONTROLLERHWBUFFERNUMBER_TX)
	{
		*ptr_bufNo = 0x00;
	}
}

/****************************************************************************
 * @function	CanIf_SetTxListChNo
 * @brief  		set CanIf_CanMsgTxList ChNo
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				ChNo :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListChNo(uint8 Index, uint8 ChNo)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Check the ChNo is vaild*/
		if(ChNo >= CANIF_CANCONTROLLERCHANNELNUMBER)
		{
			ret = E_PARAM_RANGE_OVERFLOW;
		}
		else
		{
			CanIf_CanMsgTxList[Index].ChNo = ChNo;
			ret = E_OK;
		}
	}

	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListMsgValid
 * @brief  		set CanIf_CanMsgTxList MsgValid
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgValid :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListMsgValid(uint8 Index, uint8 MsgValid)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*it will add check data vaild rules.*/
		CanIf_CanMsgTxList[Index].MsgValid = MsgValid;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListMsgTxMode
 * @brief  		set CanIf_CanMsgTxList MsgTxMode
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgTxMode :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListMsgTxMode(uint8 Index, uint8 MsgTxMode)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*it will add check data vaild rules.*/
		CanIf_CanMsgTxList[Index].MsgTxMode = MsgTxMode;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListCycleTime
 * @brief  		set CanIf_CanMsgTxList CycleTime
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				CycleTime :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListCycleTime(uint8 Index, uint16 CycleTime)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*it will add check data vaild rules.*/
		CanIf_CanMsgTxList[Index].CycleTime = CycleTime;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListCurrentTime
 * @brief  		set CanIf_CanMsgTxList CurrentTime
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				CurrentTime :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListCurrentTime(uint8 Index, uint16 CurrentTime)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*it will add check data vaild rules.*/
		CanIf_CanMsgTxList[Index].CurrentTime = CurrentTime;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListTransmissionCounter
 * @brief  		set CanIf_CanMsgTxList TransmissionCounter
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				TransmissionCounter :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListTransmissionCounter(uint8 Index, uint8 TransmissionCounter)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*it will add check data vaild rules.*/
		CanIf_CanMsgTxList[Index].TransmissionCounter = TransmissionCounter;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListTransmittedCounter
 * @brief  		set CanIf_CanMsgTxList TransmittedCounter
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				TransmittedCounter :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListTransmittedCounter(uint8 Index, uint8 TransmittedCounter)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*it will add check data vaild rules.*/
		CanIf_CanMsgTxList[Index].TransmittedCounter = TransmittedCounter;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListMsgId
 * @brief  		set CanIf_CanMsgTxList MsgId
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgId :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListMsgId(uint8 Index, uint32 MsgId)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*it will add check data vaild rules.*/
		CanIf_CanMsgTxList[Index].MsgId = MsgId;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListDlc
 * @brief  		set CanIf_CanMsgTxList Dlc
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				Dlc :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListDlc(uint8 Index, uint8 Dlc)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*it will add check data vaild rules.*/
		CanIf_CanMsgTxList[Index].Dlc = Dlc;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListData
 * @brief  		set CanIf_CanMsgTxList Data
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListData(uint8 Index, uint8 *ptr_Data, uint8 Dtatlength)
{
	uint8 ret = E_NOT_OK;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		ret = E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		if(NULL != ptr_Data)
		{
			if(Dtatlength <= 8)
			{
				memcpy(ptr_Data, CanIf_CanMsgTxList[Index].Data, Dtatlength);
				ret = E_OK;
			}
			else
			{
				/*Doing nothing*/
			}
		}
		else
		{
			ret = E_PARAM_NULLPTR;
		}
	}
	return ret;
}

/****************************************************************************
 * @function	CanIf_SetTxListMsgIdDlcData
 * @brief  		set CanIf_CanMsgTxList MsgId,Dlc,Data
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgId :
 * 				Dlc :
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListMsgIdDlcData(uint8 Index, uint32 MsgId,uint8 Dlc, uint8 *ptr_Data)
{
	uint8 ret = E_NOT_OK;
	uint8 DataLength = 0x00;

	/*Check the index is vaild*/
	if(Index >= (sizeof(CanIf_CanMsgTxList)/sizeof(CanIf_CanMsgTxManagementDataBuffer_Type)) )
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check ptr_Data is valid*/
	if(NULL == ptr_Data)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	CanIf_CanMsgTxList[Index].MsgId = MsgId;
	CanIf_CanMsgTxList[Index].Dlc = Dlc;
	DataLength = Dlc;
	memcpy(ptr_Data, CanIf_CanMsgTxList[Index].Data, DataLength);
	ret = E_OK;

	return ret;
}

/*********************************File End*********************************/
