/****************************************************************************
* File Name : CanIf.h
*
* Modules : CAN Interface Layer head file
*
* Summary :
*
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
#ifndef	_CAN_IF_H
#define	_CAN_IF_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "CanIf_Type.h"
#include "CanIf_Cfg_Define.h"
#include "VFB_CanIf.h"


/*Macro definition AREA*/
#define _CAN_IF_C	/*define use CanIf.c*/

#ifndef _CAN_IF_C
#define CAN_IF_API_CALL
#define CAN_IF_API_LOCAL
#else
#define CAN_IF_EXTERN_API extern
#define CAN_IF_LOCAL_API static
#endif /*_CAN_IF_C*/


/*Variable declaration AREA*/
CanIf_CanMsgStruct_Type CanIf_CanRecvMsgBuff[CANIF_RECEIVEBUFFERNUMBER];
CanIf_BuffControlInformation_Type CanIf_CanRecvMsgBuffCtrInfo;
CanIf_CanMsgTxManagementControlInfomation_Type CanIf_CanTxMsgCtrInfo;


/*Function declaration AREA*/
/****************************************************************************
 * @function	CanIf_Init
 * @brief  		can interface layer init function.
 * @param  		NULL
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API void CanIf_Init(void);

/****************************************************************************
 * @function	CanIf_MainFunction
 * @brief  		can interface layer main function.
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API void CanIf_MainFunction(void);

/****************************************************************************
 * @function	CANbus_RecvInterruptCallBack
 * @brief  		the CAN BUS receive interrupt call back function.
 * @param  		ChNo: input parameters,CAN channel index.
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_RecvInterruptCallback(uint8 ChNo);

/****************************************************************************
 * @function	CanIf_SendInterruptCallback
 * @brief  		the CAN BUS send interrupt call back function.
 * @param  		ChNo: input parameters,CAN channel index.
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SendInterruptCallback(uint8 ChNo);

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
CAN_IF_LOCAL_API uint8 CanIf_WriteRecvBuffer(uint8 chno, uint16 MsgId, uint8* ptr_Data, uint8 Dlc);
#else
CAN_IF_LOCAL_API uint8 CanIf_WriteRecvBuffer(uint8 chno, uint32 MsgId, uint8* ptr_Data, uint8 Dlc);
#endif

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
CAN_IF_LOCAL_API uint8 CanIf_ReadRecvBuffer(uint8* ptr_chno, uint16* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc);
#else
CAN_IF_LOCAL_API uint8 CanIf_ReadRecvBuffer(uint8* ptr_chno, uint32* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc);
#endif

/****************************************************************************
 * @function	CanIf_MainFunction
 * @brief  		the can interface layer receive message main function
 * @param
 * @retval
 * @attention   null
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_RxMainFunction(void);

/****************************************************************************
 * @function	CanIf_RxManagementFunction
 * @brief  		handles the rx buffer data
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_RxManagementFunction(void);

/****************************************************************************
 * @function	CanIf_MsgIdCheck
 * @brief  		software filter
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_MsgIdCheck(uint8 ChNo, uint32 MsgId);

/****************************************************************************
 * @function	CanIf_MsgDlcCheck
 * @brief
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters.
 * 				Dlc : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_MsgDlcCheck(uint8 ChNo, uint32 MsgId,uint8 Dlc);

/****************************************************************************
 * @function	CanIf_MsgTimeoutCheck
 * @brief
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_MsgTimeoutCheck(void);

/****************************************************************************
 * @function	CanIf_OverloadMsgTimeoutTimer
 * @brief
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_OverloadMsgTimeoutTimer(uint8 ChNo, uint32 MsgId);

/****************************************************************************
 * @function	CanIf_RxTimerHandleFunction
 * @brief  		the can interface layer handle the Rx message timer and counter
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_RxTimerHandleFunction(void);

/****************************************************************************
 * @function	CanIf_GetRxListElementNumber
 * @brief  		get CanIf_CanMsgRxList Data element number
 * @param
 * @retval		ret : Data element number
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_GetRxListElementNumber(void);

/****************************************************************************
 * @function	CanIf_GetRxListIndex
 * @brief  		get CanIf_CanMsgRxList index base on ChNo and MsgId
 * @param		ptr_Index : output parameters,
 * 				ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListIndex(uint8* ptr_Index, uint8 ChNo, uint32 MsgId);

/****************************************************************************
 * @function	CanIf_GetRxListChNo
 * @brief  		get CanIf_CanMsgRxList ChNo base on Index
 * @param		Index : input parameters,
 * 				ptr_ChNo : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListChNo(uint8 Index, uint8* ptr_ChNo);

/****************************************************************************
 * @function	CanIf_GetRxListMsgType
 * @brief  		get CanIf_CanMsgRxList MsgType base on ChNo and MsgId
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters,
 * 				ptr_MsgType : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListMsgType(uint8 ChNo, uint32 MsgId, uint8* ptr_MsgType);

/****************************************************************************
 * @function	CanIf_GetRxListMsgRxMode
 * @brief  		get CanIf_CanMsgRxList MsgRxMode base on Index
 * @param		Index : input parameters,
 * 				ptr_MsgRxMode : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListMsgRxMode(uint8 Index, uint8* ptr_MsgRxMode);

/****************************************************************************
 * @function	CanIf_GetRxListMsgCheckMode
 * @brief  		get CanIf_CanMsgRxList MsgCheckMode base on Index
 * @param		Index : input parameters,
 * 				ptr_MsgCheckMode : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListMsgCheckMode(uint8 Index, uint8* ptr_MsgCheckMode);

/****************************************************************************
 * @function	CanIf_GetRxListTimeout
 * @brief  		get CanIf_CanMsgRxList Timeout base on Index
 * @param		Index : input parameters,
 * 				ptr_Timeout : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListTimeout(uint8 Index, uint16* ptr_Timeout);

/****************************************************************************
 * @function	CanIf_GetRxListCurrentTime
 * @brief  		get CanIf_CanMsgRxList CurrentTime base on Index
 * @param		Index : input parameters,
 * 				ptr_CurrentTime : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListCurrentTime(uint8 Index, uint16* ptr_CurrentTime);

/****************************************************************************
 * @function	CanIf_GetRxListMsgId
 * @brief  		get CanIf_CanMsgRxList MsgId base on Index
 * @param		Index : input parameters,
 * 				ptr_MsgId : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListMsgId(uint8 Index, uint32* ptr_MsgId);

/****************************************************************************
 * @function	CanIf_GetRxListDlc
 * @brief  		get CanIf_CanMsgRxList Dlc base on Index
 * @param		Index : input parameters,
 * 				ptr_Dlc : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListDlc(uint8 Index, uint32* ptr_Dlc);

/****************************************************************************
 * @function	CanIf_GetRxListCheckRet_Timeout
 * @brief
 * @param		Index : input parameters,
 * 				ptr_TimeoutFlag : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetRxListCheckRet_Timeout(uint8 Index, uint8* ptr_TimeoutFlag);

/****************************************************************************
 * @function	CanIf_GetRxMessageCheckRet_Timeout
 * @brief		get the receive message timeout check result  base on ChNo and MsgId
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters,
 * 				ptr_TimeoutFlag : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_GetRxMessageCheckRet_Timeout(uint8 ChNo, uint32 MsgId,uint8* ptr_TimeoutFlag);

/****************************************************************************
 * @function	CanIf_SetRxListCurrentTime
 * @brief  		set CanIf_CanMsgRxList CurrentTime base on Index
 * @param		Index : input parameters,
 * 				CurrentTime : input parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_SetRxListCurrentTime(uint8 Index, uint16 CurrentTime);

/****************************************************************************
 * @function	CanIf_TxMainFunction
 * @brief  		the can interface layer transmit message main function
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxMainFunction(void);

/****************************************************************************
 * @function	CanIf_TxMainFunction
 * @brief  		the can interface layer transmit message main function
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxManagementFunction(void);

/****************************************************************************
 * @function	CanIf_TxTimerHandleFunction
 * @brief  		the can interface layer handle the tx message timer and counter
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxTimerHandleFunction(void);

/****************************************************************************
 * @function	CanIf_CanControllerTxHardwareBuffIndexVaildCheck
 * @brief  		can interface layer check can controller Tx hardware buffer Index
 * @param		ptr_bufNo : input and output parameter,controller hardware buffer index
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_CanControllerTxHardwareBuffIndexVaildCheck(uint8* ptr_bufNo);

/****************************************************************************
 * @function	CanIf_GetTxListElementNumber
 * @brief  		get CanIf_CanMsgTxList Data element number
 * @param
 * @retval		ret : Data element number
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_GetTxListElementNumber(void);

/****************************************************************************
 * @function	CanIf_GetTxListIndex
 * @brief  		get CanIf_CanMsgTxList index base on ChNo and MsgId
 * @param		ptr_Index : output parameters,
 * 				ChNo : input parameters,
 * 				MsgId : input parameters.
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API uint8 CanIf_GetTxListIndex(uint8* ptr_Index, uint8 ChNo, uint32 MsgId);

/****************************************************************************
 * @function	CanIf_SetTxListChNo
 * @brief  		set CanIf_CanMsgTxList ChNo
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				ChNo :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListChNo(uint8 Index, uint8 ChNo);

/****************************************************************************
 * @function	CanIf_SetTxListMsgType
 * @brief  		set CanIf_CanMsgTxList MsgType
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgType :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListMsgType(uint8 Index, uint8 MsgType);

/****************************************************************************
 * @function	CanIf_SetTxListMsgTxMode
 * @brief  		set CanIf_CanMsgTxList MsgTxMode
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgTxMode :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListMsgTxMode(uint8 Index, uint8 MsgTxMode);

/****************************************************************************
 * @function	CanIf_SetTxListCycleTime
 * @brief  		set CanIf_CanMsgTxList CycleTime
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				CycleTime :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListCycleTime(uint8 Index, uint16 CycleTime);

/****************************************************************************
 * @function	CanIf_SetTxListCurrentTime
 * @brief  		set CanIf_CanMsgTxList CurrentTime
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				CurrentTime :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListCurrentTime(uint8 Index, uint16 CurrentTime);

/****************************************************************************
 * @function	CanIf_SetTxListTransmissionCounter
 * @brief  		set CanIf_CanMsgTxList TransmissionCounter
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				TransmissionCounter :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListTransmissionCounter(uint8 Index, uint8 TransmissionCounter);

/****************************************************************************
 * @function	CanIf_SetTxListTransmittedCounter
 * @brief  		set CanIf_CanMsgTxList TransmittedCounter
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				TransmittedCounter :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListTransmittedCounter(uint8 Index, uint8 TransmittedCounter);

/****************************************************************************
 * @function	CanIf_SetTxListMsgId
 * @brief  		set CanIf_CanMsgTxList MsgId
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				MsgId :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListMsgId(uint8 Index, uint32 MsgId);

/****************************************************************************
 * @function	CanIf_SetTxListDlc
 * @brief  		set CanIf_CanMsgTxList Dlc
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				Dlc :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListDlc(uint8 Index, uint8 Dlc);

/****************************************************************************
 * @function	CanIf_SetTxListData
 * @brief  		set CanIf_CanMsgTxList Data
 * @param		Index : will set CanIf_CanMsgTxList index
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SetTxListData(uint8 Index, uint8 *ptr_Data, uint8 Dtatlength);

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
CAN_IF_EXTERN_API uint8 CanIf_SetTxListMsgIdDlcData(uint8 Index, uint32 MsgId,uint8 Dlc, uint8 *ptr_Data);

/****************************************************************************
 * @function	CanIf_UpdateTxListMsgData
 * @brief  		update CanIf_CanMsgTxList Data base on ChNo and MsgId
 * @param		ChNo :
 * 				MsgId :
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_UpdateTxListMsgData(uint8 ChNo,uint32 MsgId, uint8 *ptr_Data);

/****************************************************************************
 * @function	CanIf_UpdateTxListMsgDlcData
 * @brief  		update CanIf_CanMsgTxList Dlc,Data base on ChNo and MsgId
 * @param		ChNo :
 * 				MsgId :
 * 				Dlc :
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_UpdateTxListMsgDlcData(uint8 ChNo,uint32 MsgId,uint8 Dlc, uint8 *ptr_Data);

/****************************************************************************
 * @function	CanIf_GetTxListMsgData
 * @brief  		get CanIf_CanMsgTxList Data base on ChNo and MsgId
 * @param		ChNo : input parameters
 * 				MsgId : input parameters
 * 				ptr_Data : output parameters
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_GetTxListMsgData(uint8 ChNo,uint32 MsgId, uint8 *ptr_Data);

/****************************************************************************
 * @function	CanIf_GetTxListMsgDlcData
 * @brief  		get CanIf_CanMsgTxList Dlc,Data base on ChNo and MsgId
 * @param		ChNo : input parameters
 * 				MsgId : input parameters
 * 				ptr_Dlc : output parameters
 * 				ptr_Data : output parameters
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_GetTxListMsgDlcData(uint8 ChNo,uint32 MsgId,uint8 *ptr_Dlc, uint8 *ptr_Data);





#endif /*_CAN_IF_H*/
/*********************************File End*********************************/
