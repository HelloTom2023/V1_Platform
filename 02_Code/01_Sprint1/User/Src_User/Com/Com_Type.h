/****************************************************************************
* File Name : Com_Type.h
*
* Modules : Communication server Layer head file
*
* Summary :
*
*
* Reference Documents : None
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-20
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef COM_TYPE_H_
#define COM_TYPE_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Com_Cfg_Define.h"


typedef struct Com_BusMsgStruct_Type_Tag
{
	//uint8 Index;
	uint8 ChNo;
	uint32 MsgId;
	uint8 MsgDlc;
	uint8 MsgData[8];
}Com_BusMsgStruct_Type;


typedef struct Com_BuffControlInformation_Type_Tag
{
	uint8 WriteIndex;
	uint8 ReadIndex;
}Com_BuffControlInformation_Type;




#endif /* COM_TYPE_H_ */
