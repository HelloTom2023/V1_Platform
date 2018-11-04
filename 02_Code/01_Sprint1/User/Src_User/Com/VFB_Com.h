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
