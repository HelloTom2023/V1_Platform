/****************************************************************************
* File Name : Com.c
*
* Modules : Communication server Layer source file
*
* Summary : 1.handle application message
*			2.message conversion to PDU handle.
*			3.
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-20
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/

/*Include head files AREA*/
#include "Com.h"
#include "Com_Cfg_Table.h"/*The table only used by Com.C*/


/*Macro definition AREA*/




/*Variable declaration AREA*/


/*Function implement AREA*/
/****************************************************************************
 * @function	Com_Init
 * @brief
 * @param  		NULL
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API void Com_Init(void)
{

}

/****************************************************************************
 * @function	Com_MainFunction
 * @brief
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API void Com_MainFunction(void)
{
	Com_RxMainFunction();
	Com_TxMainFunction();
}

/****************************************************************************
 * @function	Com_RxMainFunction
 * @brief
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API void Com_RxMainFunction(void)
{

}

/****************************************************************************
 * @function	Com_TxMainFunction
 * @brief
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API void Com_TxMainFunction(void)
{
	Com_TxManagementFunction();
}

/****************************************************************************
 * @function	Com_TxManagementFunction
 * @brief
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API void Com_TxManagementFunction(void)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 TxListLength = sizeof(Com_BusTxMsgList)/sizeof(Com_BusMsgStruct_Type);
	uint8 DataUpdateFlag = 0x00;
	Com_BusMsgStruct_Type Com_BusTxMsgInfo;

	for(Index = 0x00; Index < TxListLength; Index++)
	{
		/*Get Update flag */
		ret = Com_GetTxMsgListUpdate(Index,&DataUpdateFlag);

		/*check the result*/
		if(E_OK != ret)
		{
			/*Reserved : after add DET module*/
		}
		else
		{
			/*Doing nothing*/
		}

		/*Check update flag*/
		if(0x01 == DataUpdateFlag)
		{
			ret = Com_GetTxMsgListChNoMsgIdDlcData(Index, &Com_BusTxMsgInfo.ChNo, &Com_BusTxMsgInfo.MsgId, \
						&Com_BusTxMsgInfo.MsgDlc, Com_BusTxMsgInfo.MsgData);
			if(E_OK == ret)
			{
				ret = Com_CanIf_UpdateTxListMsgData(Com_BusTxMsgInfo.ChNo, Com_BusTxMsgInfo.MsgId, Com_BusTxMsgInfo.MsgData);
				if(E_OK == ret)
				{
					Com_SetTxMsgListUpdate(Index, 0x00);/*Clear the update flag*/
				}
				else
				{
					/*doing nothing*/
				}
			}
			else
			{
				/*Doing nothing*/
			}
		}
		else/*Have new data */
		{
			/*Reserved : after add DET module*/
		}
	}
}

/****************************************************************************
 * @function	Com_RxNotificationFunction
 * @brief		transmit application message to communication server layer
 * @param  		ChNo :  input parameters , CAN channel index(if the mcu only one Can controller,the param shall setting to 0)
 *				MsgId : input parameters, the receive can message id.
 *				ptr_Data : output parameters, the receive can message data
 *				Dlc : input parameters, the receive can message dlc.
 * @retval 		ret :
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API uint8 Com_RxNotificationFunction(uint8 ChNo,uint32 MsgId,uint8* ptr_Data,uint8 Dlc)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;

	/*Check parameters is valid*/
	if(COM_CANCONTROLLERCHANNELNUMBER <= ChNo)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_Data)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the Com_BusRxMsgList is full*/
	ret = Com_CheckRxMsgListIsFull(&Index);
	if( (E_OK == ret) || (E_ARRAY_FULL == ret) )
	{
		/*Search the message id in the array index*/
		ret = Com_GetRxMsgListIndex(ChNo, MsgId, &Index);
		if( (E_OK == ret) || (E_RET_NOT_FOUND == ret) )
		{
			/*write data to Com_BusRxMsgList*/
			/*
			 * Note :
			 * 1. if the Com_BusRxMsgList is full,and in the Com_BusRxMsgList not search message id. Sw will write data to Com_BusRxMsgList[0]
			 * 2. if the Com_BusRxMsgList is full,and in the Com_BusRxMsgList search message id. Sw will write data to Com_GetRxMsgListIndex return index for Com_BusRxMsgList.
			 * 3. if the Com_BusRxMsgList is not full,and in the Com_BusRxMsgList not search message id. Sw will write data to Com_CheckRxMsgListIsFull return index for Com_BusRxMsgList.
			 * 4. if the Com_BusRxMsgList is not full,and in the Com_BusRxMsgList search message id. Sw will write data to Com_GetRxMsgListIndex return index for Com_BusRxMsgList.
			 *
			 * Propose :
			 * The length of the user defined Com_BusRxMsgList array should be more than the the ecu will send the message number.
			 * */

			/*Com_Debug_OutputInfo(_T("Com Recv Msg:\nChNo = %d,MsgId = 0x%lx,Dlc = %d,Data = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",	\
					ChNo,MsgId,Dlc,ptr_Data[0],ptr_Data[1],ptr_Data[2],ptr_Data[3],ptr_Data[4],ptr_Data[5],ptr_Data[6],ptr_Data[7]));
			*/

			Com_SetRxMsgListChNoMsgIdDlcData(Index, ChNo, MsgId, Dlc, ptr_Data);
			//Com_SetRxMsgListUpdate(Index,0x01);
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

	return ret;
}

/****************************************************************************
 * @function	Com_CheckRxMsgListIsFull
 * @brief		check Com_BusRxMsgList is full
 * @param  		ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_CheckRxMsgListIsFull(uint8 *ptr_Index)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check pointer is NULL*/
	if(NULL == ptr_Index)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the array is full.*/
	for(Index = 0x00; Index < RxMsgListLength; Index++)
	{
		if( (0x00 == Com_BusRxMsgList[Index].ChNo) && \
				(0x00 == Com_BusRxMsgList[Index].MsgId) && \
				(0x00 == Com_BusRxMsgList[Index].MsgDlc))
		{
			*ptr_Index = Index;
			return E_OK;
		}
		else
		{
			/*Doing nothing*/
		}
	}

	ret = E_ARRAY_FULL;
	return ret;
}

/****************************************************************************
 * @function	Com_GetRxMsgListIndex
 * @brief		get Com_BusRxMsgList Index base on ChNo and MsgId
 * @param  		ChNo :  input parameters
 *				MsgId : input parameters
 *				ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListIndex(uint8 ChNo,uint32 MsgId,uint8 *ptr_Index)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(COM_CANCONTROLLERCHANNELNUMBER <= ChNo)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_Index)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Search Message Id and bus channel number*/
	for(Index = 0x00; Index < RxMsgListLength; Index++)
	{
		if( (Com_BusRxMsgList[Index].MsgId == MsgId) && (Com_BusRxMsgList[Index].ChNo == ChNo) )
		{
			*ptr_Index = Index;
			return E_OK;
		}
		else
		{
			/*Doing nothing*/
		}
	}

	ret = E_RET_NOT_FOUND;
	return ret;
}

/****************************************************************************
 * @function	Com_GetRxMsgListUpdate
 * @brief		get Com_BusRxMsgList Update base on Index
 * @param  		Index :  input parameters
 *				ptr_Updata : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListUpdate(uint8 Index,uint8 *ptr_Update)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_Update)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message id base on index*/
	*ptr_Update = Com_BusRxMsgList[Index].Update;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetRxMsgListChNo
 * @brief		get Com_BusRxMsgList ChNo base on Index
 * @param  		Index :  input parameters
 *				ptr_ChNo : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListChNo(uint8 Index,uint8 *ptr_ChNo)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_ChNo)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message id base on index*/
	*ptr_ChNo = Com_BusRxMsgList[Index].ChNo;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetRxMsgListMsgId
 * @brief		get Com_BusRxMsgList MsgId base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgId : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListMsgId(uint8 Index,uint32 *ptr_MsgId)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgId)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message id base on index*/
	*ptr_MsgId = Com_BusRxMsgList[Index].MsgId;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetRxMsgListMsgDlc
 * @brief		get Com_BusRxMsgList MsgDlc base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgDlc : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListMsgDlc(uint8 Index,uint8 *ptr_MsgDlc)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgDlc)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message dlc base on index*/
	*ptr_MsgDlc = Com_BusRxMsgList[Index].MsgDlc;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetRxMsgListMsgData
 * @brief		get Com_BusRxMsgList MsgData base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgData : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListMsgData(uint8 Index,uint8 *ptr_MsgData)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgData)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message data base on index*/
	//ptr_MsgData = Com_BusRxMsgList[Index].MsgData;
	memcpy(ptr_MsgData, Com_BusRxMsgList[Index].MsgData, 8);

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetRxMsgListChNoMsgIdDlcData
 * @brief		get Com_BusRxMsgList ChNo,MsgId,MsgDlc,MsgData base on Index
 * @param  		Index :  input parameters
 * 				ptr_ChNo : output parameters
 * 				ptr_MsgId : output parameters
 * 				ptr_MsgDlc : output parameters
 *				ptr_MsgData : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListChNoMsgIdDlcData(uint8 Index,uint8 *ptr_ChNo,uint32 *ptr_MsgId,uint8 *ptr_MsgDlc,uint8 *ptr_MsgData)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if( (NULL == ptr_ChNo) || (NULL == ptr_MsgId) || (NULL == ptr_MsgDlc) || (NULL == ptr_MsgData) )
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_ChNo = Com_BusRxMsgList[Index].ChNo;
	*ptr_MsgId = Com_BusRxMsgList[Index].MsgId;
	*ptr_MsgDlc = Com_BusRxMsgList[Index].MsgDlc;
	//ptr_MsgData = Com_BusRxMsgList[Index].MsgData;
	memcpy(ptr_MsgDlc, Com_BusRxMsgList[Index].MsgData, 8);

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetRxMsgListUpdate
 * @brief		set Com_BusRxMsgList Update base on Index
 * @param  		Index :  input parameters
 *				Update : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListUpdate(uint8 Index,uint8 Update)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Set Update flag base on index*/
	Com_BusRxMsgList[Index].Update = Update;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetRxMsgListChNo
 * @brief		set Com_BusRxMsgList ChNo base on Index
 * @param  		Index :  input parameters
 *				ChNo : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListChNo(uint8 Index,uint8 ChNo)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	if(COM_CANCONTROLLERCHANNELNUMBER <= ChNo)
	{
			return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Set message id base on index*/
	Com_BusRxMsgList[Index].ChNo = ChNo;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetRxMsgListMsgId
 * @brief		set Com_BusRxMsgList MsgId base on Index
 * @param  		Index :  input parameters
 *				MsgId : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListMsgId(uint8 Index,uint32 MsgId)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Set message id base on index*/
	Com_BusRxMsgList[Index].MsgId = MsgId;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetRxMsgListMsgDlc
 * @brief		set Com_BusRxMsgList MsgDlc base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgDlc : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListMsgDlc(uint8 Index,uint8 MsgDlc)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*set message dlc base on index*/
	Com_BusRxMsgList[Index].MsgDlc = MsgDlc;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetRxMsgListMsgData
 * @brief		set Com_BusRxMsgList MsgData base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgData : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListMsgData(uint8 Index,uint8 *ptr_MsgData)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgData)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*set message data base on index*/
	memcpy(Com_BusRxMsgList[Index].MsgData, ptr_MsgData, 8);

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetRxMsgListMsgIdDlcData
 * @brief		set Com_BusRxMsgList ChNo,MsgId,MsgDlc,MsgData base on Index
 * @param  		Index :  input parameters
 * 				ChNo : input parameters
 * 				MsgId : input parameters
 * 				MsgDlc : input parameters
 *				ptr_MsgData : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListChNoMsgIdDlcData(uint8 Index,uint8 ChNo,uint32 MsgId,uint8 MsgDlc,uint8 *ptr_MsgData)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	if(ChNo >= COM_CANCONTROLLERCHANNELNUMBER)
	{
			return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgData)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	Com_BusRxMsgList[Index].ChNo = ChNo;
	Com_BusRxMsgList[Index].MsgId = MsgId;
	Com_BusRxMsgList[Index].MsgDlc = MsgDlc;
	memcpy(Com_BusRxMsgList[Index].MsgData, ptr_MsgData, 8);

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_ReadRxMsgListSignal
 * @brief
 * @param  		Index :  input parameters
 * 				FormatType : input parameters.
 * 							 if the FormatType is 0x01,the can message data format is Intel format
 * 							 if the FormatType is 0x00,the can message data format is Motorola format
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : output parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
COM_LOCAL_API uint8 Com_ReadRxMsgListSignal(uint8 Index,uint8 FormatType,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);
	uint8 DataByteIndex = 0x00;
	uint8 DataBitIndex = 0x00;
	uint8 PtrByteIndex = 0x00;
	uint8 PtrBitIndex = 0x00;
	uint8 ReadLength = 0x00;

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*The length check base on can message data*/
	if(Length >= 64)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_SignalValue)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*check the message format*/
	if((0x00 != FormatType) && (0x01 != FormatType))
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get byte position in the message data array*/
	DataByteIndex = StartBit / 8;
	/*Get bit position in the one byte*/
	DataBitIndex = StartBit % 8;
	/*Initialization the ptr_SignalValue byte and bit control*/
	PtrByteIndex = 0x00;
	PtrBitIndex = 0x00;

	for(ReadLength = 0x00; ReadLength < Length; 	)
	{
		ptr_SignalValue[PtrByteIndex] = ptr_SignalValue[PtrByteIndex] | 	\
				CommFunc_BitShiftLeft(	\
						(CommFunc_BitShiftRigth(Com_BusRxMsgList[Index].MsgData[DataByteIndex],DataBitIndex) & CommFunc_GetBitMask(0x01)),	\
						PtrBitIndex);

		PtrBitIndex++;
		DataBitIndex++;
		/*Check the MsgData[] byte is full*/
		if(DataBitIndex >= 0x08)/*DataBitIndex range is 0~7*/
		{
			DataBitIndex = 0x00;
			if(0x00 == FormatType)/*Motorola Format*/
			{
				DataByteIndex--;
			}
			else /*if(0x01 == FormatType)  // Intel Format*/
			{
				DataByteIndex++;
			}
		}
		else
		{
			/*Doing nothing*/
		}
		/*Check the ptr_SignalValue[] byte is full*/
		if(PtrBitIndex >= 0x08)/*PtrBitIndex range is 0~7*/
		{
			PtrBitIndex = 0x00;
			PtrByteIndex++;
		}
		else
		{
			/*Doing nothing*/
		}

		/*read data from MsgData number of times,loop control*/
		ReadLength++;
	}

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_WriteRxMsgListSignal
 * @brief
 * @param  		Index :  input parameters
 * 				FormatType : input parameters.
 * 							 if the FormatType is 0x01,the can message data format is Intel format
 * 							 if the FormatType is 0x00,the can message data format is Motorola format
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : input parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
COM_LOCAL_API uint8 Com_WriteRxMsgListSignal(uint8 Index,uint8 FormatType,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue)
{
	uint8 ret = E_NOT_OK;
	uint8 RxMsgListLength = sizeof(Com_BusRxMsgList) / sizeof(Com_BusMsgStruct_Type);
	uint8 DataByteIndex = 0x00;
	uint8 DataBitIndex = 0x00;
	uint8 PtrByteIndex = 0x00;
	uint8 PtrBitIndex = 0x00;
	uint8 WroteLength = 0x00;

	/*Check parameters is valid*/
	if(RxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*The length check base on can message data*/
	if(Length >= 64)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_SignalValue)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*check the message format*/
	if((0x00 != FormatType) && (0x01 == FormatType))
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get byte position in the message data array*/
	DataByteIndex = StartBit / 8;
	/*Get bit position in the one byte*/
	DataBitIndex = StartBit % 8;
	/*Initialization the ptr_SignalValue byte and bit control*/
	PtrByteIndex = 0x00;
	PtrBitIndex = 0x01;

	for(WroteLength = 0x00; WroteLength < Length; 	)
	{
		Com_BusRxMsgList[Index].MsgData[DataByteIndex] =  Com_BusRxMsgList[Index].MsgData[DataByteIndex] |	\
				CommFunc_BitShiftLeft(	\
						CommFunc_BitShiftRigth(ptr_SignalValue[PtrByteIndex], PtrBitIndex) & CommFunc_GetBitMask(0x01), \
						DataBitIndex);
		PtrBitIndex++;
		DataBitIndex++;
		/*Check the MsgData[] byte is full*/
		if(DataBitIndex >= 0x07)
		{
			DataBitIndex = 0x00;
			if(0x00 == FormatType)/*Motorola Format*/
			{
				DataByteIndex--;
			}
			else /*if(0x01 == FormatType)  // Intel Format*/
			{
				DataByteIndex++;
			}
		}
		else
		{
			/*Doing nothing*/
		}
		/*Check the ptr_SignalValue[] byte is full*/
		if(PtrBitIndex >= 0x08)
		{
			PtrBitIndex = 0x01;
			PtrByteIndex++;
		}
		else
		{
			/*Doing nothing*/
		}

		/*write data to MsgData number of times,loop control*/
		WroteLength++;
	}

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_ReadRxSignal
 * @brief
 * @param 		FormatType : input parameters.
 * 							 if the FormatType is 0x01,the can message data format is Intel format
 * 							 if the FormatType is 0x00,the can message data format is Motorola format
 * 				ChNo : input parameters
 * 				MsgId : input parameters
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : output parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
COM_EXTERN_API uint8 Com_ReadRxSignal(uint8 FormatType,uint8 ChNo,uint32 MsgId,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 MsgCheckRet = 0x00;

	ret = Com_GetRxMsgListIndex(ChNo,MsgId,&Index);
	if(E_OK != ret)
	{
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*get the message timout result*/
	ret = Com_CanIf_GetRxMessageCheckRet_Timeout(ChNo,MsgId,&MsgCheckRet);
	ret = Com_ReadRxMsgListSignal(Index,FormatType,StartBit,Length,ptr_SignalValue);
	if(0x01 == MsgCheckRet)/*If the check result is timeout,set timeout flag*/
	{
		ret = E_MSG_TIMEOUT;
	}
	else
	{
		/*Doing nothing*/
	}

	return ret;
}


/****************************************************************************
 * @function	Com_CheckTxMsgListIsFull
 * @brief		check Com_BusTxMsgList is full
 * @param  		ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_CheckTxMsgListIsFull(uint8 *ptr_Index)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check pointer is NULL*/
	if(NULL == ptr_Index)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the array is full.*/
	for(Index = 0x00; Index < TxMsgListLength; Index++)
	{
		if( (0x00 == Com_BusTxMsgList[Index].ChNo) && \
				(0x00 == Com_BusTxMsgList[Index].MsgId) && \
				(0x00 == Com_BusTxMsgList[Index].MsgDlc))
		{
			*ptr_Index = Index;
			return E_OK;
		}
		else
		{
			/*Doing nothing*/
		}
	}

	ret = E_ARRAY_FULL;
	return ret;
}

/****************************************************************************
 * @function	Com_GetTxMsgListIndex
 * @brief		get Com_BusTxMsgList Index base on ChNo and MsgId
 * @param  		ChNo :  input parameters
 *				MsgId : input parameters
 *				ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListIndex(uint8 ChNo,uint32 MsgId,uint8 *ptr_Index)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(COM_CANCONTROLLERCHANNELNUMBER <= ChNo)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_Index)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Search Message Id and bus channel number*/
	for(Index = 0x00; Index < TxMsgListLength; Index++)
	{
		if( (Com_BusTxMsgList[Index].MsgId == MsgId) && (Com_BusTxMsgList[Index].ChNo == ChNo) )
		{
			*ptr_Index = Index;
			return E_OK;
		}
		else
		{
			/*Doing nothing*/
		}
	}

	ret = E_RET_NOT_FOUND;
	return ret;
}

/****************************************************************************
 * @function	Com_GetTxMsgListUpdate
 * @brief		get Com_BusTxMsgList Update base on Index
 * @param  		Index :  input parameters
 *				ptr_Updata : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListUpdate(uint8 Index,uint8 *ptr_Update)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_Update)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message id base on index*/
	*ptr_Update = Com_BusTxMsgList[Index].Update;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetTxMsgListChNo
 * @brief		get Com_BusTxMsgList ChNo base on Index
 * @param  		Index :  input parameters
 *				ptr_ChNo : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListChNo(uint8 Index,uint8 *ptr_ChNo)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_ChNo)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message id base on index*/
	*ptr_ChNo = Com_BusTxMsgList[Index].ChNo;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetTxMsgListMsgId
 * @brief		get Com_BusTxMsgList MsgId base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgId : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListMsgId(uint8 Index,uint32 *ptr_MsgId)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgId)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message id base on index*/
	*ptr_MsgId = Com_BusTxMsgList[Index].MsgId;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetTxMsgListMsgDlc
 * @brief		get Com_BusTxMsgList MsgDlc base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgDlc : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListMsgDlc(uint8 Index,uint8 *ptr_MsgDlc)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgDlc)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message dlc base on index*/
	*ptr_MsgDlc = Com_BusTxMsgList[Index].MsgDlc;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetTxMsgListMsgData
 * @brief		get Com_BusTxMsgList MsgData base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgData : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListMsgData(uint8 Index,uint8 *ptr_MsgData)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgData)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get message data base on index*/
	//ptr_MsgData = Com_BusTxMsgList[Index].MsgData;
	memcpy(ptr_MsgData, Com_BusTxMsgList[Index].MsgData, 8);

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_GetTxMsgListChNoMsgIdDlcData
 * @brief		get Com_BusTxMsgList ChNo,MsgId,MsgDlc,MsgData base on Index
 * @param  		Index :  input parameters
 * 				ptr_ChNo : output parameters
 * 				ptr_MsgId : output parameters
 * 				ptr_MsgDlc : output parameters
 *				ptr_MsgData : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListChNoMsgIdDlcData(uint8 Index,uint8 *ptr_ChNo,uint32 *ptr_MsgId,uint8 *ptr_MsgDlc,uint8 *ptr_MsgData)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if( (NULL == ptr_ChNo) || (NULL == ptr_MsgId) || (NULL == ptr_MsgDlc) || (NULL == ptr_MsgData) )
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	*ptr_ChNo = Com_BusTxMsgList[Index].ChNo;
	*ptr_MsgId = Com_BusTxMsgList[Index].MsgId;
	*ptr_MsgDlc = Com_BusTxMsgList[Index].MsgDlc;
	//ptr_MsgData = Com_BusTxMsgList[Index].MsgData;
	memcpy(ptr_MsgDlc, Com_BusTxMsgList[Index].MsgData, 8);

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetTxMsgListUpdate
 * @brief		set Com_BusTxMsgList Update base on Index
 * @param  		Index :  input parameters
 *				Update : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListUpdate(uint8 Index,uint8 Update)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Set Update flag base on index*/
	Com_BusTxMsgList[Index].Update = Update;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetTxMsgListChNo
 * @brief		set Com_BusTxMsgList ChNo base on Index
 * @param  		Index :  input parameters
 *				ChNo : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListChNo(uint8 Index,uint8 ChNo)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	if(COM_CANCONTROLLERCHANNELNUMBER <= ChNo)
	{
			return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Set message id base on index*/
	Com_BusTxMsgList[Index].ChNo = ChNo;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetTxMsgListMsgId
 * @brief		set Com_BusTxMsgList MsgId base on Index
 * @param  		Index :  input parameters
 *				MsgId : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListMsgId(uint8 Index,uint32 MsgId)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Set message id base on index*/
	Com_BusTxMsgList[Index].MsgId = MsgId;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetTxMsgListMsgDlc
 * @brief		set Com_BusTxMsgList MsgDlc base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgDlc : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListMsgDlc(uint8 Index,uint8 MsgDlc)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*set message dlc base on index*/
	Com_BusTxMsgList[Index].MsgDlc = MsgDlc;

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetTxMsgListMsgData
 * @brief		set Com_BusTxMsgList MsgData base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgData : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListMsgData(uint8 Index,uint8 *ptr_MsgData)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgData)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*set message data base on index*/
	memcpy(Com_BusTxMsgList[Index].MsgData, ptr_MsgData, 8);

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_SetTxMsgListChNoMsgIdDlcData
 * @brief		set Com_BusTxMsgList ChNo,MsgId,MsgDlc,MsgData base on Index
 * @param  		Index :  input parameters
 * 				ChNo : input parameters
 * 				MsgId : input parameters
 * 				MsgDlc : input parameters
 *				ptr_MsgData : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListChNoMsgIdDlcData(uint8 Index,uint8 ChNo,uint32 MsgId,uint8 MsgDlc,uint8 *ptr_MsgData)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	if(ChNo >= COM_CANCONTROLLERCHANNELNUMBER)
	{
			return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_MsgData)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	Com_BusTxMsgList[Index].ChNo = ChNo;
	Com_BusTxMsgList[Index].MsgId = MsgId;
	Com_BusTxMsgList[Index].MsgDlc = MsgDlc;
	memcpy(Com_BusTxMsgList[Index].MsgData, ptr_MsgData, 8);

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_ReadTxMsgListSignal
 * @brief
 * @param  		Index :  input parameters
 * 				FormatType : input parameters.
 * 							 if the FormatType is 0x01,the can message data format is Intel format
 * 							 if the FormatType is 0x00,the can message data format is Motorola format
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : output parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
COM_LOCAL_API uint8 Com_ReadTxMsgListSignal(uint8 Index,uint8 FormatType,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);
	uint8 DataByteIndex = 0x00;
	uint8 DataBitIndex = 0x00;
	uint8 PtrByteIndex = 0x00;
	uint8 PtrBitIndex = 0x00;
	uint8 ReadLength = 0x00;

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*The length check base on can message data*/
	if(Length >= 64)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_SignalValue)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*check the message format*/
	if((0x00 != FormatType) && (0x01 == FormatType))
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get byte position in the message data array*/
	DataByteIndex = StartBit / 8;
	/*Get bit position in the one byte*/
	DataBitIndex = StartBit % 8;
	/*Initialization the ptr_SignalValue byte and bit control*/
	PtrByteIndex = 0x00;
	PtrBitIndex = 0x01;

	for(ReadLength = 0x00; ReadLength >=Length; 	)
	{

		ptr_SignalValue[PtrByteIndex] = ptr_SignalValue[PtrByteIndex] | 	\
				CommFunc_BitShiftLeft(	\
						(CommFunc_BitShiftRigth(Com_BusTxMsgList[Index].MsgData[DataByteIndex],DataBitIndex) & CommFunc_GetBitMask(0x01)),	\
						PtrBitIndex);
		PtrBitIndex++;
		DataBitIndex++;
		/*Check the MsgData[] byte is full*/
		if(DataBitIndex >= 0x07)
		{
			DataBitIndex = 0x00;
			if(0x00 == FormatType)/*Motorola Format*/
			{
				DataByteIndex--;
			}
			else /*if(0x01 == FormatType)  // Intel Format*/
			{
				DataByteIndex++;
			}
		}
		else
		{
			/*Doing nothing*/
		}
		/*Check the ptr_SignalValue[] byte is full*/
		if(PtrBitIndex >= 0x08)
		{
			PtrBitIndex = 0x01;
			PtrByteIndex++;
		}
		else
		{
			/*Doing nothing*/
		}

		/*read data from MsgData number of times,loop control*/
		ReadLength++;
	}

	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_WriteTxMsgListSignal
 * @brief
 * @param  		Index :  input parameters
 * 				FormatType : input parameters.
 * 							 if the FormatType is 0x01,the can message data format is Intel format
 * 							 if the FormatType is 0x00,the can message data format is Motorola format
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : input parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
COM_LOCAL_API uint8 Com_WriteTxMsgListSignal(uint8 Index,uint8 FormatType,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue)
{
	uint8 ret = E_NOT_OK;
	uint8 TxMsgListLength = sizeof(Com_BusTxMsgList) / sizeof(Com_BusMsgStruct_Type);
	uint8 DataByteIndex = 0x00;
	uint8 DataBitIndex = 0x00;
	uint8 PtrByteIndex = 0x00;
	uint8 PtrBitIndex = 0x00;
	uint8 WroteLength = 0x00;

	/*Check parameters is valid*/
	if(TxMsgListLength <= Index)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*The length check base on can message data*/
	if(Length >= 64)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_SignalValue)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*check the message format*/
	if((0x00 != FormatType) && (0x01 != FormatType))
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get byte position in the message data array*/
	DataByteIndex = StartBit / 8;
	/*Get bit position in the one byte*/
	DataBitIndex = StartBit % 8;
	/*Initialization the ptr_SignalValue byte and bit control*/
	PtrByteIndex = 0x00;
	PtrBitIndex = 0x00;

	/*clear the signal value*/
	for(WroteLength = 0x00; WroteLength < Length; 	)
	{
		Com_BusTxMsgList[Index].MsgData[DataByteIndex] =  Com_BusTxMsgList[Index].MsgData[DataByteIndex] &	\
				(~(CommFunc_BitShiftLeft(CommFunc_GetBitMask(0x01), DataBitIndex)));

		PtrBitIndex++;
		DataBitIndex++;
		/*Check the MsgData[] byte is full*/
		if(DataBitIndex >= 0x08)
		{
			DataBitIndex = 0x00;
			if(0x00 == FormatType)/*Motorola Format*/
			{
				DataByteIndex--;
			}
			else /*if(0x01 == FormatType)  // Intel Format*/
			{
				DataByteIndex++;
			}
		}
		else
		{
			/*Doing nothing*/
		}
		/*Check the ptr_SignalValue[] byte is full*/
		if(PtrBitIndex >= 0x08)
		{
			PtrBitIndex = 0x00;
			PtrByteIndex++;
		}
		else
		{
			/*Doing nothing*/
		}

		/*write data to MsgData number of times,loop control*/
		WroteLength++;
	}

	/*Com_Debug_OutputInfo(_T("Clean : MsgId = 0x%lx,Data = %x %x %x %x %x %x %x %x\n",Com_BusTxMsgList[Index].MsgId,\
				Com_BusTxMsgList[Index].MsgData[0],Com_BusTxMsgList[Index].MsgData[1],Com_BusTxMsgList[Index].MsgData[2],Com_BusTxMsgList[Index].MsgData[3],	\
				Com_BusTxMsgList[Index].MsgData[4],Com_BusTxMsgList[Index].MsgData[5],Com_BusTxMsgList[Index].MsgData[6],Com_BusTxMsgList[Index].MsgData[7]));
	 */

	/*Get byte position in the message data array*/
	DataByteIndex = StartBit / 8;
	/*Get bit position in the one byte*/
	DataBitIndex = StartBit % 8;
	/*Initialization the ptr_SignalValue byte and bit control*/
	PtrByteIndex = 0x00;
	PtrBitIndex = 0x00;

	/*write the signal value*/
	for(WroteLength = 0x00; WroteLength < Length; 	)
	{
		Com_BusTxMsgList[Index].MsgData[DataByteIndex] =  Com_BusTxMsgList[Index].MsgData[DataByteIndex] |	\
				CommFunc_BitShiftLeft(	\
						(CommFunc_BitShiftRigth(ptr_SignalValue[PtrByteIndex], PtrBitIndex) & CommFunc_GetBitMask(0x01)), \
						DataBitIndex);

		PtrBitIndex++;
		DataBitIndex++;
		/*Check the MsgData[] byte is full*/
		if(DataBitIndex >= 0x08)
		{
			DataBitIndex = 0x00;
			if(0x00 == FormatType)/*Motorola Format*/
			{
				DataByteIndex--;
			}
			else /*if(0x01 == FormatType)  // Intel Format*/
			{
				DataByteIndex++;
			}
		}
		else
		{
			/*Doing nothing*/
		}
		/*Check the ptr_SignalValue[] byte is full*/
		if(PtrBitIndex >= 0x08)
		{
			PtrBitIndex = 0x00;
			PtrByteIndex++;
		}
		else
		{
			/*Doing nothing*/
		}

		/*write data to MsgData number of times,loop control*/
		WroteLength++;
	}

	/*Set TxMsgList Data update flag*/
	Com_SetTxMsgListUpdate(Index, 0x01);
/*
	Com_Debug_OutputInfo(_T("write : MsgId = 0x%lx,Data = %x %x %x %x %x %x %x %x\n",Com_BusTxMsgList[Index].MsgId,\
			Com_BusTxMsgList[Index].MsgData[0],Com_BusTxMsgList[Index].MsgData[1],Com_BusTxMsgList[Index].MsgData[2],Com_BusTxMsgList[Index].MsgData[3],	\
			Com_BusTxMsgList[Index].MsgData[4],Com_BusTxMsgList[Index].MsgData[5],Com_BusTxMsgList[Index].MsgData[6],Com_BusTxMsgList[Index].MsgData[7]));
*/
	ret = E_OK;
	return ret;
}

/****************************************************************************
 * @function	Com_WriteTxSignal
 * @brief		1.the function called by com application.And set signal to Tx message list.
 * 				2.In the main function,will polling get tx message list and send to down layer(canif module)
 * @param  		FormatType : input parameters.
 * 							 if the FormatType is 0x01,the can message data format is Intel format
 * 							 if the FormatType is 0x00,the can message data format is Motorola format
 * 				ChNo : input parameters
 * 				MsgId : input parameters
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : input parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
COM_EXTERN_API uint8 Com_WriteTxSignal(uint8 FormatType,uint8 ChNo,uint32 MsgId,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	Com_BusMsgStruct_Type Com_BusTxMsgInfo;

	ret = Com_GetTxMsgListIndex(ChNo,MsgId,&Index);

	/*
	 * write signal to the Tx Message List.
	 * */
	if(E_RET_NOT_FOUND == ret)
	{
		Com_SetTxMsgListMsgId(Index,ChNo);
		Com_SetTxMsgListMsgId(Index,MsgId);
	}
	else
	{
		/*Doing nothing*/
	}

	if( (E_OK == ret) || (E_RET_NOT_FOUND == ret))
	{
		ret = Com_WriteTxMsgListSignal(Index,FormatType,StartBit,Length,ptr_SignalValue);
	}
	else
	{
		/*Doing nothing*/
	}

	return ret;
}

/****************************************************************************
 * @function	Com_ImmediatelyWriteTxSignal
 * @brief		1.If used this function,the signal direct write to can if tx message list.and not store the Com Tx message list.
 * 				2.
 * @param  		FormatType : input parameters.
 * 							 if the FormatType is 0x01,the can message data format is Intel format
 * 							 if the FormatType is 0x00,the can message data format is Motorola format
 * 				ChNo : input parameters
 * 				MsgId : input parameters
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : input parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
COM_EXTERN_API uint8 Com_ImmediatelyWriteTxSignal(uint8 FormatType,uint8 ChNo,uint32 MsgId,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue)
{
	uint8 ret = E_NOT_OK;
	Com_BusMsgStruct_Type Com_BusTxMsgInfo;
	uint8 DataByteIndex = 0x00;
	uint8 DataBitIndex = 0x00;
	uint8 PtrByteIndex = 0x00;
	uint8 PtrBitIndex = 0x00;
	uint8 WroteLength = 0x00;

	/*The length check base on can message data*/
	if(Length >= 64)
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check pointer is NULL*/
	if(NULL == ptr_SignalValue)
	{
		return E_PARAM_NULLPTR;
	}
	else
	{
		/*Doing nothing*/
	}

	/*check the message format*/
	if((0x00 != FormatType) && (0x01 != FormatType))
	{
		return E_PARAM_RANGE_OVERFLOW;
	}
	else
	{
		/*Doing nothing*/
	}

	Com_BusTxMsgInfo.ChNo = ChNo;
	Com_BusTxMsgInfo.MsgId = MsgId;
	/*get canif tx list data base on ChNo and MsgId*/
	Com_CanIf_GetTxListMsgDlcData(Com_BusTxMsgInfo.ChNo, Com_BusTxMsgInfo.MsgId, &Com_BusTxMsgInfo.MsgDlc, Com_BusTxMsgInfo.MsgData);

	/*Get byte position in the message data array*/
	DataByteIndex = StartBit / 8;
	/*Get bit position in the one byte*/
	DataBitIndex = StartBit % 8;
	/*Initialization the ptr_SignalValue byte and bit control*/
	PtrByteIndex = 0x00;
	PtrBitIndex = 0x00;

	/*clear the signal value*/
	for(WroteLength = 0x00; WroteLength < Length; 	)
	{
		Com_BusTxMsgInfo.MsgData[DataByteIndex] =  Com_BusTxMsgInfo.MsgData[DataByteIndex] &	\
				(~(CommFunc_BitShiftLeft(CommFunc_GetBitMask(0x01), DataBitIndex)));

		PtrBitIndex++;
		DataBitIndex++;
		/*Check the MsgData[] byte is full*/
		if(DataBitIndex >= 0x08)
		{
			DataBitIndex = 0x00;
			if(0x00 == FormatType)/*Motorola Format*/
			{
				DataByteIndex--;
			}
			else /*if(0x01 == FormatType)  // Intel Format*/
			{
				DataByteIndex++;
			}
		}
		else
		{
			/*Doing nothing*/
		}
		/*Check the ptr_SignalValue[] byte is full*/
		if(PtrBitIndex >= 0x08)
		{
			PtrBitIndex = 0x00;
			PtrByteIndex++;
		}
		else
		{
			/*Doing nothing*/
		}

		/*write data to MsgData number of times,loop control*/
		WroteLength++;
	}

	/*Com_Debug_OutputInfo(_T("Clean : MsgId = 0x%lx,Data = %x %x %x %x %x %x %x %x\n",Com_BusTxMsgList[Index].MsgId,\
				Com_BusTxMsgList[Index].MsgData[0],Com_BusTxMsgList[Index].MsgData[1],Com_BusTxMsgList[Index].MsgData[2],Com_BusTxMsgList[Index].MsgData[3],	\
				Com_BusTxMsgList[Index].MsgData[4],Com_BusTxMsgList[Index].MsgData[5],Com_BusTxMsgList[Index].MsgData[6],Com_BusTxMsgList[Index].MsgData[7]));
	 */

	/*Get byte position in the message data array*/
	DataByteIndex = StartBit / 8;
	/*Get bit position in the one byte*/
	DataBitIndex = StartBit % 8;
	/*Initialization the ptr_SignalValue byte and bit control*/
	PtrByteIndex = 0x00;
	PtrBitIndex = 0x00;

	/*write the signal value*/
	for(WroteLength = 0x00; WroteLength < Length; 	)
	{
		Com_BusTxMsgInfo.MsgData[DataByteIndex] =  Com_BusTxMsgInfo.MsgData[DataByteIndex] |	\
				CommFunc_BitShiftLeft(	\
						(CommFunc_BitShiftRigth(ptr_SignalValue[PtrByteIndex], PtrBitIndex) & CommFunc_GetBitMask(0x01)), \
						DataBitIndex);

		PtrBitIndex++;
		DataBitIndex++;
		/*Check the MsgData[] byte is full*/
		if(DataBitIndex >= 0x08)
		{
			DataBitIndex = 0x00;
			if(0x00 == FormatType)/*Motorola Format*/
			{
				DataByteIndex--;
			}
			else /*if(0x01 == FormatType)  // Intel Format*/
			{
				DataByteIndex++;
			}
		}
		else
		{
			/*Doing nothing*/
		}
		/*Check the ptr_SignalValue[] byte is full*/
		if(PtrBitIndex >= 0x08)
		{
			PtrBitIndex = 0x00;
			PtrByteIndex++;
		}
		else
		{
			/*Doing nothing*/
		}

		/*write data to MsgData number of times,loop control*/
		WroteLength++;
	}

	/*Com_Debug_OutputInfo(_T("ret = %d....Com_WriteSignalTxImmediately : MsgId = 0x%lx,Data = %x %x %x %x %x %x %x %x\n",ret,Com_BusTxMsgInfo.MsgId,\
			Com_BusTxMsgInfo.MsgData[0],Com_BusTxMsgInfo.MsgData[1],Com_BusTxMsgInfo.MsgData[2],Com_BusTxMsgInfo.MsgData[3],Com_BusTxMsgInfo.MsgData[4],
			Com_BusTxMsgInfo.MsgData[5],Com_BusTxMsgInfo.MsgData[6],Com_BusTxMsgInfo.MsgData[7]));
	 */

	/*Update Data to CanIf*/
	Com_CanIf_UpdateTxListMsgData(Com_BusTxMsgInfo.ChNo, Com_BusTxMsgInfo.MsgId, Com_BusTxMsgInfo.MsgData);

	return ret;
}



/*********************************File End*********************************/
