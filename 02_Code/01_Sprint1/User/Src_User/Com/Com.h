/****************************************************************************
* File Name : Com.h
*
* Modules : Communication server Layer head file
*
* Summary :
*
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
#ifndef	_COM_H
#define	_COM_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Com_Type.h"
#include "Com_Cfg_Define.h"
#include "VFB_Com.h"


/*Macro definition AREA*/
#define _COM_C	/*define use Com.c*/

#ifndef _COM_C
#define COM_API_CALL
#define COM_API_LOCAL
#else
#define COM_EXTERN_API extern
#define COM_LOCAL_API static
#endif /*_COM_C*/


/*Variable declaration AREA*/


/*Function declaration AREA*/
/****************************************************************************
 * @function	Com_Init
 * @brief
 * @param  		NULL
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API void Com_Init(void);

/****************************************************************************
 * @function	Com_MainFunction
 * @brief
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API void Com_MainFunction(void);

/****************************************************************************
 * @function	Com_RxMainFunction
 * @brief
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API void Com_RxMainFunction(void);

/****************************************************************************
 * @function	Com_TxMainFunction
 * @brief
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API void Com_TxMainFunction(void);

/****************************************************************************
 * @function	Com_TxManagementFunction
 * @brief
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API void Com_TxManagementFunction(void);

/****************************************************************************
 * @function	Com_RecvNotificationFunction
 * @brief		transmit application message to communication server layer
 * @param  		ChNo :  input parameters , CAN channel index(if the mcu only one Can controller,the param shall setting to 0)
 *				MsgId : input parameters, the receive can message id.
 *				ptr_Data : output parameters, the receive can message data
 *				Dlc : input parameters, the receive can message dlc.
 * @retval 		ret :
 * @attention   NULL
****************************************************************************/
COM_EXTERN_API uint8 Com_RxNotificationFunction(uint8 ChNo,uint32 MsgId,uint8* ptr_Data,uint8 Dlc);

/****************************************************************************
 * @function	Com_CheckRxMsgListIsFull
 * @brief		check Com_BusRxMsgList is full
 * @param  		ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_CheckRxMsgListIsFull(uint8 *ptr_Index);

/****************************************************************************
 * @function	Com_GetRxMsgListIndex
 * @brief		get Com_BusRxMsgList Index base on ChNo and MsgId
 * @param  		ChNo :  input parameters
 *				MsgId : input parameters
 *				ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListIndex(uint8 ChNo,uint32 MsgId,uint8 *ptr_Index);

/****************************************************************************
 * @function	Com_GetRxMsgListUpdate
 * @brief		get Com_BusRxMsgList Update base on Index
 * @param  		Index :  input parameters
 *				ptr_Updata : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListUpdate(uint8 Index,uint8 *ptr_Update);

/****************************************************************************
 * @function	Com_GetRxMsgListChNo
 * @brief		get Com_BusRxMsgList ChNo base on Index
 * @param  		Index :  input parameters
 *				ptr_ChNo : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListChNo(uint8 Index,uint8 *ptr_ChNo);

/****************************************************************************
 * @function	Com_GetRxMsgListMsgId
 * @brief		get Com_BusRxMsgList MsgId base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgId : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListMsgId(uint8 Index,uint32 *ptr_MsgId);

/****************************************************************************
 * @function	Com_GetRxMsgListMsgDlc
 * @brief		get Com_BusRxMsgList MsgDlc base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgDlc : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListMsgDlc(uint8 Index,uint8 *ptr_MsgDlc);

/****************************************************************************
 * @function	Com_GetRxMsgListMsgData
 * @brief		get Com_BusRxMsgList MsgData base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgData : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetRxMsgListMsgData(uint8 Index,uint8 *ptr_MsgData);

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
COM_LOCAL_API uint8 Com_GetRxMsgListChNoMsgIdDlcData(uint8 Index,uint8 *ptr_ChNo,uint32 *ptr_MsgId,uint8 *ptr_MsgDlc,uint8 *ptr_MsgData);

/****************************************************************************
 * @function	Com_SetRxMsgListUpdate
 * @brief		set Com_BusRxMsgList Update base on Index
 * @param  		Index :  input parameters
 *				Update : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListUpdate(uint8 Index,uint8 Update);

/****************************************************************************
 * @function	Com_SetRxMsgListChNo
 * @brief		set Com_BusRxMsgList ChNo base on Index
 * @param  		Index :  input parameters
 *				ChNo : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListChNo(uint8 Index,uint8 ChNo);

/****************************************************************************
 * @function	Com_SetRxMsgListMsgId
 * @brief		set Com_BusRxMsgList MsgId base on Index
 * @param  		Index :  input parameters
 *				MsgId : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListMsgId(uint8 Index,uint32 MsgId);

/****************************************************************************
 * @function	Com_SetRxMsgListMsgDlc
 * @brief		set Com_BusRxMsgList MsgDlc base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgDlc : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListMsgDlc(uint8 Index,uint8 MsgDlc);

/****************************************************************************
 * @function	Com_SetRxMsgListMsgData
 * @brief		set Com_BusRxMsgList MsgData base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgData : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetRxMsgListMsgData(uint8 Index,uint8 *ptr_MsgData);

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
COM_LOCAL_API uint8 Com_SetRxMsgListChNoMsgIdDlcData(uint8 Index,uint8 ChNo,uint32 MsgId,uint8 MsgDlc,uint8 *ptr_MsgData);

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
COM_LOCAL_API uint8 Com_ReadRxMsgListSignal(uint8 Index,uint8 FormatType,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue);

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
COM_LOCAL_API uint8 Com_WriteRxMsgListSignal(uint8 Index,uint8 FormatType,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue);

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
COM_EXTERN_API uint8 Com_ReadRxSignal(uint8 FormatType,uint8 ChNo,uint32 MsgId,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue);

/****************************************************************************
 * @function	Com_CheckTxMsgListIsFull
 * @brief		check Com_BusTxMsgList is full
 * @param  		ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_CheckTxMsgListIsFull(uint8 *ptr_Index);

/****************************************************************************
 * @function	Com_GetTxMsgListIndex
 * @brief		get Com_BusTxMsgList Index base on ChNo and MsgId
 * @param  		ChNo :  input parameters
 *				MsgId : input parameters
 *				ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListIndex(uint8 ChNo,uint32 MsgId,uint8 *ptr_Index);

/****************************************************************************
 * @function	Com_GetTxMsgListUpdate
 * @brief		get Com_BusTxMsgList Update base on Index
 * @param  		Index :  input parameters
 *				ptr_Updata : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListUpdate(uint8 Index,uint8 *ptr_Update);

/****************************************************************************
 * @function	Com_GetTxMsgListChNo
 * @brief		get Com_BusTxMsgList ChNo base on Index
 * @param  		Index :  input parameters
 *				ptr_ChNo : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListChNo(uint8 Index,uint8 *ptr_ChNo);

/****************************************************************************
 * @function	Com_GetTxMsgListMsgId
 * @brief		get Com_BusTxMsgList MsgId base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgId : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListMsgId(uint8 Index,uint32 *ptr_MsgId);

/****************************************************************************
 * @function	Com_GetTxMsgListMsgDlc
 * @brief		get Com_BusTxMsgList MsgDlc base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgDlc : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListMsgDlc(uint8 Index,uint8 *ptr_MsgDlc);

/****************************************************************************
 * @function	Com_GetTxMsgListMsgData
 * @brief		get Com_BusTxMsgList MsgData base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgData : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_GetTxMsgListMsgData(uint8 Index,uint8 *ptr_MsgData);

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
COM_LOCAL_API uint8 Com_GetTxMsgListChNoMsgIdDlcData(uint8 Index,uint8 *ptr_ChNo,uint32 *ptr_MsgId,uint8 *ptr_MsgDlc,uint8 *ptr_MsgData);

/****************************************************************************
 * @function	Com_SetTxMsgListUpdate
 * @brief		set Com_BusTxMsgList Update base on Index
 * @param  		Index :  input parameters
 *				Update : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListUpdate(uint8 Index,uint8 Update);

/****************************************************************************
 * @function	Com_SetTxMsgListChNo
 * @brief		set Com_BusTxMsgList ChNo base on Index
 * @param  		Index :  input parameters
 *				ChNo : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListChNo(uint8 Index,uint8 ChNo);

/****************************************************************************
 * @function	Com_SetTxMsgListMsgId
 * @brief		set Com_BusTxMsgList MsgId base on Index
 * @param  		Index :  input parameters
 *				MsgId : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListMsgId(uint8 Index,uint32 MsgId);

/****************************************************************************
 * @function	Com_SetTxMsgListMsgDlc
 * @brief		set Com_BusTxMsgList MsgDlc base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgDlc : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListMsgDlc(uint8 Index,uint8 MsgDlc);

/****************************************************************************
 * @function	Com_SetTxMsgListMsgData
 * @brief		set Com_BusTxMsgList MsgData base on Index
 * @param  		Index :  input parameters
 *				ptr_MsgData : input parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
COM_LOCAL_API uint8 Com_SetTxMsgListMsgData(uint8 Index,uint8 *ptr_MsgData);

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
COM_LOCAL_API uint8 Com_SetTxMsgListChNoMsgIdDlcData(uint8 Index,uint8 ChNo,uint32 MsgId,uint8 MsgDlc,uint8 *ptr_MsgData);

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
COM_LOCAL_API uint8 Com_ReadTxMsgListSignal(uint8 Index,uint8 FormatType,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue);

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
COM_LOCAL_API uint8 Com_WriteTxMsgListSignal(uint8 Index,uint8 FormatType,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue);

/****************************************************************************
 * @function	Com_WriteSignalTxImmediately
 * @brief
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
COM_EXTERN_API uint8 Com_ImmediatelyWriteTxSignal(uint8 FormatType,uint8 ChNo,uint32 MsgId,uint8 StartBit,uint8 Length,uint8 *ptr_SignalValue);




#endif /*_COM_H*/
/*********************************File End*********************************/
