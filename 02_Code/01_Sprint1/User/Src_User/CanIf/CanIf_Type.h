/****************************************************************************
* File Name : CanIf_Type.h
*
* Modules : CAN Interface Layer data type define head file
*
* Summary :
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

typedef enum CanIf_MsgType_Type_Tag
{
	CANIF_MSG_TYPE_APP,
	CANIF_MSG_TYPE_DIAG,
	CANIF_MSG_TYPE_NM,
	CANIF_MSG_TYPE_NONE
}CanIf_MsgType_Type;

typedef enum CanIf_MsgMode_Type_Tag
{
	CANIF_MSG_MODE_PERIODIC,
	CANIF_MSG_MODE_EVENT,
	CANIF_MSG_MODE_MIXED,
	CANIF_MSG_MODE_NONE
}CanIf_MsgMode_Type;

/*imeout signal substitute value mode*/
#define CANIF_TIMEOUT_SIGNAL_VALUE_MODE_INIT		(0x00U)
#define CANIF_TIMEOUT_SIGNAL_VALUE_MODE_REPLACE		(0x01U)
/*Can interface layer message check mode*/
#define CANIF_CHECK_MODE_TIMEOUT_SIGNAL_VALUE		(0x01)
#define CANIF_CHECK_MODE_DLC						(0x02)
#define CANIF_CHECK_MODE_TIMEOUT					(0x04)

typedef struct CanIf_CanMsgRxManagementDataBuffer_Type_Tag
{
	uint8 Index;
	uint8 ChNo;
	CanIf_MsgType_Type MsgType;		/*the parameters show the message type. when the message type is not CANIF_MSG_TYPE_NONE can be check.*/
	CanIf_MsgMode_Type MsgRxMode;	/*when the message is periodic can be time out check.*/
	uint8 MsgCheckMode; 			/*bit0:Timeout signal substitute value mode [0:if the message timeout,get init value; 1:if the message timeout ,get last value],
	 	 	 	 	 	 	 	 	 *bit1:DLC check, bit2:timeout check*/
	uint8 MsgCheckRet;				/*0:check result is ok, 1:check result is not ok.    bit0:Reserved, bit1:DLC check result, bit2:timeout check result*/
	uint16 Timeout;
	uint16 CurrentTime;
	uint32 MsgId;
	uint8 Dlc;
	uint8 Data[8];					/*Init value*/
}CanIf_CanMsgRxManagementDataBuffer_Type;


typedef struct CanIf_CanMsgTxManagementDataBuffer_Type_Tag
{
	uint8 Index;
	uint8 ChNo;
	CanIf_MsgType_Type MsgType;	 /*when the message type is not CANIF_MSG_TYPE_NONE can be tx.*/
	CanIf_MsgMode_Type MsgTxMode;
	uint16 CycleTime;
	uint16 CurrentTime;
	uint8 TransmissionCounter;	/*If the MsgTxMode is Event,the parameters show the message send times*/
	uint8 TransmittedCounter;
	uint32 MsgId;
	uint8 Dlc;
	uint8 Data[8];
}CanIf_CanMsgTxManagementDataBuffer_Type;

typedef struct CanIf_CanMsgTxManagementControlInfomation_Type_Tag
{
	uint8 HwBufNo;	/*Can controller hardware buffer index*/
	uint8 TxListIndex; /*can message tx list index*/
}CanIf_CanMsgTxManagementControlInfomation_Type;

typedef struct CanIf_BuffControlInformation_Type_Tag
{
	uint8 WriteIndex;
	uint8 ReadIndex;
}CanIf_BuffControlInformation_Type;


#endif /* CANIF_TYPE_H_ */
