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
	/*Init Can messae buffer operate control information*/
	CanIf_CanRecvMsgBuffCtrInfo.ReadIndex = 0x00;
	CanIf_CanRecvMsgBuffCtrInfo.WriteIndex = 0x00;

	/*Init message receive buffer*/
	CanIf_MemSetValue(CanIf_CanRecvMsgBuff,0x00,CANIF_RECEIVEBUFFERNUMBER);
}


/****************************************************************************
 * @function	CANbus_RecvInterruptCallBack
 * @brief  		the CAN BUS receive interrupt call back function.
 * @param  		ChNo: input parameters,CAN channel index.
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_RecvInterruptCallback(uint8 ChNo)
{
	uint8 BufIndex;
	uint8 ret = E_NOT_OK;
	uint8 ret_subfunc = E_OK;

	/*get hardware buffer index*/
	BufIndex = CanIf_GetControllerMsgBuffIndex(ChNo);

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
		CanIf_GetControllerMsgBuffData(ChNo, BufIndex, &CanRecvMsg.CanMsgId, CanRecvMsg.CanData, &CanRecvMsg.CanMsgDlc);

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
 * @attention   null
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
 * @attention   null
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
 * @attention   null
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
 * @param
 * @retval
 * @attention   null
****************************************************************************/
CAN_IF_EXTERN_API void CanIf_RxMainFunction(void)
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
 * @param
 * @retval
 * @attention   null
****************************************************************************/
CAN_IF_EXTERN_API void CanIf_TxMainFunction(void)
{

}



/*********************************File End*********************************/
