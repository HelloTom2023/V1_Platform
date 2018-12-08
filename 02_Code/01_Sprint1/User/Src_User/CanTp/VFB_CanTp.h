/****************************************************************************
* File Name : VFB_CanTp.h
*
* Modules : Virtual Function Bus base on CAN Transport Layer
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
#ifndef	_VFB_CAN_TP_H
#define	_VFB_CAN_TP_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "..\Debug\Debug.h"
#include "..\Dcm\Dcm.h"

/*Macro definition AREA*/



/*Function declaration AREA*/
/****************************************************************************
 * @function	CanTp_CanIf_UpdateTxListMsgData
 * @brief  		update Data to CanIf_CanMsgTxList
 * @param		ChNo :
 * 				MsgId :
 * 				Dlc :
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
#define CanTp_CanIf_UpdateTxListMsgData(ChNo, MsgId, ptr_Data)		CanIf_UpdateTxListMsgData(ChNo, MsgId, ptr_Data)

/****************************************************************************
 * @function	CanTp_CanIf_UpdateTxListMsgDlcData
 * @brief  		update Dlc,Data to CanIf_CanMsgTxList
 * @param		ChNo :
 * 				MsgId :
 * 				Dlc :
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
#define CanTp_CanIf_UpdateTxListMsgDlcData(ChNo,MsgId,Dlc,ptr_Data)		CanIf_UpdateTxListMsgDlcData(ChNo,MsgId,Dlc,ptr_Data)

/****************************************************************************
 * @function	CanTp_NotificationDiagReqInfoToDcm
 * @brief  		send diagnostic data to Dcm modules
 * @param  		ChNo: input parameters,bus channel index.
 *				ReqType : input parameters,the diagnostic request message type.
 *				DataLength : input parameters,the diagnostic request data length
 *				ptr_Data : input parameters,the diagnostic request data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
#define CanTp_NotificationDiagReqInfoToDcm(ChNo,ReqType,DataLength,ptr_Data)	Dcm_RxDiagRequestInfo(ChNo,ReqType,DataLength,ptr_Data)

/****************************************************************************
 * @function	CanTp_Debug_OutputInfo
 * @brief
 * @param
 * @retval
 * @attention
****************************************************************************/
#define CanTp_Debug_OutputInfo(x)		Debug_CanTp_OutputInfo(x)





#endif /*_VFB_CAN_TP_H*/
/*********************************File End*********************************/
