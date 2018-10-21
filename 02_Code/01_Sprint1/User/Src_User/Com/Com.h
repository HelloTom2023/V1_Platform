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
#include "Com_Cfg_Table.h"
#include "VFB_Com.h"


/*Macro definition AREA*/
#define _COM_C	/*define use CanIf.c*/

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


#endif /*_COM_H*/
/*********************************File End*********************************/
