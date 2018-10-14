/****************************************************************************
* File Name : CanIf_Type.h
*
* Modules : CAN Interface Layer head file
*
* Summary : 1.The file define use data type in can interface layer.
* 			2.The module between CAN Driver and CanTP modules.
*
*
* Reference Documents : None
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-04
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef CANIF_TYPE_H_
#define CANIF_TYPE_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "CanIf_Cfg_Define.h"


typedef struct CanIf_CanMsgStruct_Type_Tag
{
	uint8 CanChNo;
#if(CANIF_CANMESSAGEIDTYPE == STANDARD)
	uint16 CanMsgId;
#else
	uint32 CanMsgId;
#endif
	uint8 CanMsgDlc;
#if (CANIF_CONRTOLLERTYPE == CANFD)
	uint8 CanData[64];
#else
	uint8 CanData[8];
#endif
}CanIf_CanMsgStruct_Type;

#if ((CANIF_RECEIVERMESSAGESOTFFILTER == ENABLE) || (CANIF_RECEIVERMESSAGEDLCCHECK == ENABLE))
typedef struct CanIf_CanMsgSoftFilterDlcCheck_Type_Tag
{
	uint8 Index;
	uint8 CanChNo;
#if(CANIF_CANMESSAGEIDTYPE == STANDARD)
	uint16 CanMsgId;
#else
	uint32 CanMsgId;
#endif
	uint8 Dlc;
}CanIf_CanMsgSoftFilterDlcCheck_Type;
#endif

typedef struct CanIf_BuffControlInformation_Type_Tag
{
	uint8 WriteIndex;
	uint8 ReadIndex;
}CanIf_BuffControlInformation_Type;


#endif /* CANIF_TYPE_H_ */
