/****************************************************************************
* File Name : CanIf.c
*
* Modules : CAN Interface Layer source file
*
* Summary : 1.The module between CAN Driver and CanTP modules.
*			2.The module user encapsulates the Can Driver Layer APIs.
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
	CanIf_MemSetValue(CanIf_CanRecvMsgBuff,0x00,CANIF_RECEIVEBUFFERNUMBER);
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

		/*Add notification application layer callback*/
		/*PreCopy Function callback*/


#if ( (CANIF_RECEIVERMESSAGESOTFFILTER == ENABLE) || (CANIF_RECEIVERMESSAGEDLCCHECK == ENABLE) )
		ret_subfunc = CanIf_RecvSoftFilterDlcCheck(CanRecvMsg.CanChNo, CanRecvMsg.CanMsgId, CanRecvMsg.CanData, CanRecvMsg.CanMsgDlc);
		if(E_CANMSGDLC_ERROR == ret_subfunc)
		{
			/*process DLC ERROR ,eg.Notification other layer*/
			/*Reserved*/
		}
		else if(E_NOT_OK == ret_subfunc)
		{
			/*Doing nothing*/
		}
		else
#endif
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

}

#if ((CANIF_RECEIVERMESSAGEDLCCHECK == ENABLE) || (CANIF_RECEIVERMESSAGEDLCCHECK == ENABLE))
/****************************************************************************
 * @function	CanIf_RecvSoftFilter
 * @brief  		can receive message software filter.
 * 				the function filter rules base on can message id and DLC .
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_IF_LOCAL_API uint8 CanIf_RecvSoftFilterDlcCheck(uint8 chno, uint16 MsgId, uint8* ptr_Data, uint8 Dlc)
#else
CAN_IF_LOCAL_API uint8 CanIf_RecvSoftFilterDlcCheck(uint8 chno, uint32 MsgId, uint8* ptr_Data, uint8 Dlc)
#endif
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;

	for(Index = 0; ; Index++)
	{
		if(0xff == CanIf_CanMsgSoftFilterDlcCheckTable[Index].CanChNo)
		{
			break;
		}

		if((chno == CanIf_CanMsgSoftFilterDlcCheckTable[Index].CanChNo) && (MsgId == CanIf_CanMsgSoftFilterDlcCheckTable[Index].CanMsgId))
		{
			ret = E_OK;
#if (CANIF_RECEIVERMESSAGEDLCCHECK == ENABLE)
			if(Dlc != CanIf_CanMsgSoftFilterDlcCheckTable[Index].Dlc)
			{
				ret = E_CANMSGDLC_ERROR;
			}
#endif
			break;
		}
	}
	return ret;
}
#endif

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
		CanIf_MemCopyData(CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.WriteIndex].CanData,ptr_Data,Dlc);

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
		CanIf_MemCopyData(ptr_Data, CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.ReadIndex].CanData,CanIf_CanRecvMsgBuff[CanIf_CanRecvMsgBuffCtrInfo.ReadIndex].CanMsgDlc);

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
	CanIf_CanMsgStruct_Type ReadCanRecvMsg;

	/*check the can receive message buffer is new data*/
	if(CanIf_CanRecvMsgBuffCtrInfo.ReadIndex != CanIf_CanRecvMsgBuffCtrInfo.WriteIndex)
	{
		/*Read data and notification to Can Transport layer*/
		CanIf_ReadRecvBuffer(&ReadCanRecvMsg.CanChNo, &ReadCanRecvMsg.CanMsgId , ReadCanRecvMsg.CanData , &ReadCanRecvMsg.CanMsgDlc);


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
			/*Notification to communication layer*/

		}
	}
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
	if(0xff == CanIf_CanMsgTxList[CanIf_CanTxMsgCtrInfo.TxListIndex].MsgValid)
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
 * @function	CanIf_SetChNo2TxList
 * @brief  		set CanIf_CanMsgTxList ChNo
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				ChNo :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetChNo2TxList(uint8 Index, uint8 ChNo)
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
 * @function	CanIf_SetMsgValid2TxList
 * @brief  		set CanIf_CanMsgTxList MsgValid
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgValid :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetMsgValid2TxList(uint8 Index, uint8 MsgValid)
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
 * @function	CanIf_SetMsgTxMode2TxList
 * @brief  		set CanIf_CanMsgTxList MsgTxMode
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgTxMode :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetMsgTxMode2TxList(uint8 Index, uint8 MsgTxMode)
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
 * @function	CanIf_SetCycleTime2TxList
 * @brief  		set CanIf_CanMsgTxList CycleTime
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				CycleTime :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetCycleTime2TxList(uint8 Index, uint16 CycleTime)
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
 * @function	CanIf_SetCycleTime2TxList
 * @brief  		set CanIf_CanMsgTxList CurrentTime
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				CurrentTime :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetCurrentTime2TxList(uint8 Index, uint16 CurrentTime)
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
 * @function	CanIf_SetTransmissionCounter2TxList
 * @brief  		set CanIf_CanMsgTxList TransmissionCounter
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				TransmissionCounter :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTransmissionCounter2TxList(uint8 Index, uint8 TransmissionCounter)
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
 * @function	CanIf_SetTransmittedCounter2TxList
 * @brief  		set CanIf_CanMsgTxList TransmittedCounter
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				TransmittedCounter :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTransmittedCounter2TxList(uint8 Index, uint8 TransmittedCounter)
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
 * @function	CanIf_SetMsgId2TxList
 * @brief  		set CanIf_CanMsgTxList MsgId
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgId :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetMsgId2TxList(uint8 Index, uint32 MsgId)
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
 * @function	CanIf_SetDlc2TxList
 * @brief  		set CanIf_CanMsgTxList Dlc
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				Dlc :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetDlc2TxList(uint8 Index, uint8 Dlc)
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
 * @function	CanIf_SetData2TxList
 * @brief  		set CanIf_CanMsgTxList Data
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetData2TxList(uint8 Index, uint8 *ptr_Data, uint8 Dtatlength)
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
 * @function	CanIf_SetMsgIdDlcData2TxList
 * @brief  		set CanIf_CanMsgTxList MsgId,Dlc,Data
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgId :
 * 				Dlc :
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetMsgIdDlcData2TxList(uint8 Index, uint32 MsgId,uint8 Dlc, uint8 *ptr_Data)
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
