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
* Date	: 2018-10-09
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef CANTP_TYPE_H_
#define CANTP_TYPE_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "CanTp_Cfg_Define.h"

/*
 * Can message structure
 * include : can channel,can message id,can message data,can message data length
 * */
typedef struct CanTp_CanMsgStruct_Type_Tag
{
	uint8 CanChNo;
	uint32 CanMsgId;
	uint8 CanMsgDlc;
	uint8 CanData[8];
}CanTp_CanMsgStruct_Type;

typedef enum CanTp_FlowStatus_Type_Tag
{
	CANTP_FS_TYPE_CTS 	= 0,
	CANTP_FS_TYPE_WT  	= 1,
	CANTP_FS_TYPE_OVFLW = 2,
	CANTP_FS_TYPE_NONE	= 3
}CanTp_FlowStatus_Type;

/*
 * Diagnostic protocol control unit structure
 *
 * */
typedef struct CanTp_ProtocolControlUnitStruct_Type_Tag
{
	uint8 BusChannel;
	uint8 SN;					/*Sequence Number,the parameters located is Consecutive frame.*/
	CanTp_FlowStatus_Type FS; 	/*Flow Status. 0:ContinueToSend(CTS), 1:Wait(WT), 2:Overflow(OVFLW)*/
	uint8 BS; 					/*Block Size*/
	uint8 STmin;				/*Separation Time*/
}CanTp_ProtocolControlUnitStruct_Type;

/*
 *
 * */
typedef struct CanTp_ProtocolDataUnitStruct_Type_Tag
{
	uint8 BusChannel;
	uint8 PduType; 		/*0: request pdu; 1: response pdu*/
	uint8 ReqType; 		/*0: physical ; 1: function . when the pdutype is 0x00,this parameter is valid*/
	uint8 DataLength;
	uint8 *Data;		/*note : if you want to use the data element,you will init the pointer*/
}CanTp_ProtocolDataUnitStruct_Type;

/*
 * Diagnostic protocol data unit Receive control information structure
 * include :
 * */
typedef struct CanTp_RxPduControlInformation_Type_Tag
{
	uint8 RxLockFlag; /*0:idle, wait receive ,1:Receiving ,2:done,receive complete*/
	uint8 BusChannel;
	uint8 FrameType;
	uint8 ReqMsgType;
	uint8 SN;			/*Sequence Number,the parameters located is Consecutive frame.*/
	uint32 MsgId;
	uint8 TotalDataLength;
	uint8 RxDataLength;
	uint8 *Data; /*note : if you want to use the data element,you will init the pointer*/
}CanTp_RxPduControlInformation_Type;

/*Diagnostic Frame type*/
typedef enum CanTp_TxMachineState_Type_Tag
{
	CANTP_TXMS_IDLE = 0,
	CANTP_TXMS_TX_REQ,
	CANTP_TXMS_TX_SF ,
	CANTP_TXMS_TX_FF ,
	CANTP_TXMS_WT_FC ,
	CANTP_TXMS_TX_CF,
	CANTP_TXMS_TX_OVER,
	CANTP_TXMS_NONE
}CanTp_TxMachineState_Type;

/*
 * Diagnostic protocol data unit Send control information structure
 * include :
 * */
typedef struct CanTp_TxPduControlInformation_Type_Tag
{
	CanTp_TxMachineState_Type TxMachineState;
	uint8 BusChannel;
	uint8 SN;			/*Sequence Number,the parameters located is Consecutive frame.*/
	uint32 MsgId;
	uint8 TotalDataLength;
	uint8 TxDataLength;
	uint8 *Data; /*note : if you want to use the data element,you will init the pointer*/
}CanTp_TxPduControlInformation_Type;

typedef struct CanTp_BuffControlInformation_Type_Tag
{
	uint8 WriteIndex;
	uint8 ReadIndex;
}CanTp_BuffControlInformation_Type;

/*Diagnostic Frame type*/
typedef enum CanTp_FrameType_Type_Tag
{
	CANTP_FRAME_TYPE_SF = 0,
	CANTP_FRAME_TYPE_FF = 1,
	CANTP_FRAME_TYPE_CF = 2,
	CANTP_FRAME_TYPE_FC = 3,
	CANTP_FRAME_TYPE_NONE
}CanTp_FrameType_Type;


typedef enum CanTp_MessageType_Type_Tag
{
	CANTP_MSG_TYPE_REQ_PHY	 	= 0,
	CANTP_MSG_TYPE_REQ_FUNC 	= 1,
	CANTP_MSG_TYPE_RESPONSE		= 2,
	CANTP_MSG_TYPE_NONE
}CanTp_MessageType_Type;

#endif /* CANTP_TYPE_H_ */
