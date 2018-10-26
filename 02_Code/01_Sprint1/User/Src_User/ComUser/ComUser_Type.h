/****************************************************************************
* File Name : ComUser_Type.h
*
* Modules : Communication user modules head file
*
* Summary :
*
*
* Reference Documents : None
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-26
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef COM_USER_TYPE_H_
#define COM_USER_TYPE_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "ComUser_Cfg_Define.h"


typedef struct ComUser_BusMsgStruct_Type_Tag
{
	uint8 ChNo;
	uint32 MsgId;
	uint8 MsgDlc;
	uint8 MsgData[8];
}ComUser_BusMsgStruct_Type;




#endif /* COM_USER_TYPE_H_ */
