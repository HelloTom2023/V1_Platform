/****************************************************************************
* File Name : VFB_Com.h
*
* Modules :
*
* Summary :
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
#ifndef	_VFB_COM_H
#define	_VFB_COM_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Com_Cfg_Define.h"
#include "..\..\..\config\inc.h"
#include "..\CanIf\CanIf.h"
#include "..\Debug\Debug.h"

/*Macro definition AREA*/
/****************************************************************************
 * @function	Com_CanIf_UpdateTxListMsgData
 * @brief  		update Data to CanIf_CanMsgTxList
 * @param		ChNo :
 * 				MsgId :
 * 				Dlc :
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
#define Com_CanIf_UpdateTxListMsgData(ChNo, MsgId, ptr_Data)		CanIf_UpdateTxListMsgData(ChNo, MsgId, ptr_Data)

/****************************************************************************
 * @function	Com_CanIf_UpdateTxListMsgDlcData
 * @brief  		update Dlc,Data to CanIf_CanMsgTxList
 * @param		ChNo :
 * 				MsgId :
 * 				Dlc :
 * 				ptr_Data :
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
#define Com_CanIf_UpdateTxListMsgDlcData(ChNo,MsgId,Dlc,ptr_Data)		CanIf_UpdateTxListMsgDlcData(ChNo,MsgId,Dlc,ptr_Data)

/****************************************************************************
 * @function	Com_CanIf_GetTxListMsgData
 * @brief  		get CanIf_CanMsgTxList Data base on ChNo and MsgId
 * @param		ChNo : input parameters
 * 				MsgId : input parameters
 * 				ptr_Data : output parameters
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
#define Com_CanIf_GetTxListMsgData(ChNo,MsgId,ptr_Data)			CanIf_GetTxListMsgData(ChNo,MsgId,ptr_Data)

/****************************************************************************
 * @function	Com_CanIf_GetTxListMsgDlcData
 * @brief  		get CanIf_CanMsgTxList Dlc,Data base on ChNo and MsgId
 * @param		ChNo : input parameters
 * 				MsgId : input parameters
 * 				ptr_Dlc : output parameters
 * 				ptr_Data : output parameters
 * @retval		ret : operation return value
 * @attention   NULL
****************************************************************************/
#define Com_CanIf_GetTxListMsgDlcData(ChNo,MsgId,ptr_Dlc,ptr_Data)		CanIf_GetTxListMsgDlcData(ChNo, MsgId,ptr_Dlc,ptr_Data)

/****************************************************************************
 * @function	Com_CanIf_GetRxListElementNumber
 * @brief  		get CanIf_CanMsgTxList Data element number
 * @param
 * @retval		ret : Data element number
 * @attention   NULL
****************************************************************************/
#define Com_CanIf_GetRxListElementNumber		CanIf_GetRxListElementNumber

/****************************************************************************
 * @function	Com_CanIf_GetTxListElementNumber
 * @brief  		get CanIf_CanMsgTxList Data element number
 * @param
 * @retval		ret : Data element number
 * @attention   NULL
****************************************************************************/
#define Com_CanIf_GetTxListElementNumber		CanIf_GetTxListElementNumber

/****************************************************************************
 * @function	CanIf_GetRxMessageCheckRet_Timeout
 * @brief		get the receive message timeout check result  base on ChNo and MsgId
 * @param		ChNo : input parameters,
 * 				MsgId : input parameters,
 * 				ptr_TimeoutFlag : output parameters,
 * @retval		ret : function operate reslut
 * @attention   NULL
****************************************************************************/
#define  Com_CanIf_GetRxMessageCheckRet_Timeout(ChNo,MsgId,ptr_TimeoutFlag)		CanIf_GetRxMessageCheckRet_Timeout(ChNo,MsgId,ptr_TimeoutFlag)

/****************************************************************************
 * @function	CanIf_Debug_OutputInfo
 * @brief
 * @param
 * @retval
 * @attention
****************************************************************************/
#define Com_Debug_OutputInfo(x)		Debug_Com_OutputInfo(x)


/*Function declaration AREA*/




#endif /*_VFB_COM_H*/
/*********************************File End*********************************/
