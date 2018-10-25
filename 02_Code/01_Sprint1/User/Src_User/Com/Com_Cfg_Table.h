/****************************************************************************
* File Name : Com_Cfg_Table.h
*
* Modules : Communication server Layer configuration file
*
* Summary : 1.configuration parameters Table
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-20
* Description : 1.Create the file.
* 				2.Initialization Version
****************************************************************************/
#ifndef	_COM_CFG_TABLE_H
#define	_COM_CFG_TABLE_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Com_Type.h"
#include "Com_Cfg_Define.h"

/*do not modify the array name. and the array length is configurable*/
/*Note :
 * the length if this array should be the same as the number of message that need to be received
 * */
Com_BusMsgStruct_Type Com_BusRxMsgList[10];/*the communication receive message number*/
/*Note :
 * the length if this array should be the same as the number of message that need to be sent
 * */
Com_BusMsgStruct_Type Com_BusTxMsgList[10];/*the communication send message number*/

#endif /*_COM_CFG_TABLE_H*/
/*********************************File End*********************************/
