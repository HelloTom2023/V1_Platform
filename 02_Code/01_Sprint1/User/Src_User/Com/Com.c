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



/*Macro definition AREA*/




/*Variable declaration AREA*/


/*Function implement AREA*/
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

			Com_SetRxMsgListChNoMsgIdDlcData(Index, ChNo, MsgId, Dlc, ptr_Data);
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

/*********************************File End*********************************/
