/****************************************************************************
* File Name : VFB_CanIf.h
*
* Modules : Virtual Function Bus base on CAN Interface Layer
*
* Summary : 1.The module user encapsulates the Can Driver Layer APIs.
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
#ifndef	_VFB_CAN_IF_H
#define	_VFB_CAN_IF_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "CanIf_Cfg_Define.h"
#include "..\..\..\config\inc.h"
#include "..\CanTp\CanTp.h"




/*Macro definition AREA*/
/****************************************************************************
 * @function	CanIf_InitController
 * @brief		the CAN Controller Init function.
 * @param  		ChNo : input parameters,CAN channel index(if the mcu only one Can controller,the param shall setting to 0)
 * @retval 		null
 * @attention   null
****************************************************************************/
#if (CANIF_INITCONTROLLER_API == ENABLE)
#define CanIf_InitController(ChNo)	CANbus_Init(ChNo)
#else
#define CanIf_InitController(ChNo)
#endif

/****************************************************************************
 * @function	CanIf_DefaultInitController
 * @brief		the CAN Controller default init function.
 * @param  		ChNo : input parameters,CAN channel index(if the mcu only one Can controller,the param shall setting to 0)
 * @retval 		null
 * @attention   null
****************************************************************************/
#if (CANIF_DEFAULTINITCONTROLLER_API == ENABLE)
#define CanIf_DefaultInitController(ChNo)	CANbus_DefaultInit(ChNo)
#else
#define CanIf_DefaultInitController(ChNo)
#endif

/****************************************************************************
 * @function	CanIf_GetControllerMsgBuffIndex
 * @brief		get can controller hardware message buffer index.
 * @param  		ChNo : input parameters,CAN channel index(if the mcu only one Can controller,the param shall setting to 0)
 * @retval 		ret_value : the buffer index,the value range depend on mcu types.
 * @attention   null
****************************************************************************/
#if (CANIF_READCONTROLLERMSGBUFFINDEX_API == ENABLE)
#define CanIf_GetControllerMsgBuffIndex(ChNo)	CANbus_GetIntBuffNumber(ChNo)
#else
#define CanIf_GetControllerMsgBuffIndex(ChNo)
#endif

/****************************************************************************
 * @function	CanIf_GetControllerMsgBuffData
 * @brief		get can controller hardware message buffer data,include Can message id,dlc and data.
 * @param  		ChNo :  input parameters , CAN channel index(if the mcu only one Can controller,the param shall setting to 0)
 *				BuffNo : input parameters ,the buffer index,the user shall use API of CanIf_GetControllerMsgBuffIndex to get.
 *				ptr_MsgId : output parameters, the receive can message id.
 *				ptr_Data : output parameters, the receive can message data
 *				ptr_Dlc : output parameters, the receive can message dlc.
 * @retval 		ret_value : the buffer index,the value range depend on mcu types.
 * @attention   null
****************************************************************************/
#if (CANIF_READCONTROLLERMSGBUFFDATA_API == ENABLE)
#define CanIf_GetControllerMsgBuffData(ChNo,BufNo,ptr_MsgId,ptr_Data,ptr_Dlc)	CANbus_MsgGetIdDataDlc(ChNo,BufNo,ptr_MsgId,ptr_Data,ptr_Dlc)
#else
#define CanIf_GetControllerMsgBuffData(ChNo,BufNo,ptr_MsgId,ptr_Data,ptr_Dlc)
#endif






/****************************************************************************
 * @function	CanIf_CanTp_RecvNotificationFunction
 * @brief		transmit diagnostic message to can transport layer
 * @param  		ChNo :  input parameters , CAN channel index(if the mcu only one Can controller,the param shall setting to 0)
 *				ptr_MsgId : output parameters, the receive can message id.
 *				ptr_Data : output parameters, the receive can message data
 *				ptr_Dlc : output parameters, the receive can message dlc.
 * @retval 		ret_value : the buffer index,the value range depend on mcu types.
 * @attention   null
****************************************************************************/
#if (CANIF_CANTP_RECVNOTIFICATION_API == ENABLE)
#define CanIf_CanTp_RecvNotificationFunction(ChNo,MsgId,ptr_Data,Dlc)	CanTp_RxIndicationFunction(ChNo,MsgId,ptr_Data,Dlc)
#else
#define CanIf_CanTp_RecvNotificationFunction(ChNo,MsgId,ptr_Data,Dlc)
#endif





/****************************************************************************
 * @function	CanIf_MemSetValue
 * @brief		set value to ptr_DestData
 * @param  		ptr_DestData :  output parameters , target data pointer
 *				Value : input parameters , needs to be set values
 *				DataLength : input parameters, data length.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
#define CanIf_MemSetValue(ptr_DestData,Value,DataLength)		CommFunc_MemSetValue(ptr_DestData,Value,DataLength)

/****************************************************************************
 * @function	CanIf_MemCopyData
 * @brief		set value to ptr_DestData
 * @param  		ptr_DestData :  output parameters , target data pointer
 *				ptr_SoureData : output parameters , source data pointer
 *				DataLength : input parameters, data length.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
#define CanIf_MemCopyData(ptr_DestData,ptr_SoureData,DataLength)		CommFunc_MemCopyData(ptr_DestData,ptr_SoureData,DataLength)



/*Function declaration AREA*/






#endif /*_VFB_CAN_IF_H*/
/*********************************File End*********************************/
