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



/*Macro definition AREA*/
/****************************************************************************
 * @function	Com_CanIf_SetTxListMsgIdDlcData
 * @brief		Set Message Id,Dlc,Data to CanIf TxMsgList Buffer
 * @param  		ChNo :  input parameters
 *				MsgId : input parameters
 *				ptr_Index : output parameters
 * @retval 		ret : function operate result
 * @attention   NULL
****************************************************************************/
#define Com_CanIf_SetTxListMsgIdDlcData(MsgId,Dlc,ptr_Data)		(MsgId,Dlc,ptr_Data)


/*Function declaration AREA*/




#endif /*_VFB_COM_H*/
/*********************************File End*********************************/
