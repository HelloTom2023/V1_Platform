/****************************************************************************
* File Name : CanIf_Cfg_Table.h
*
* Modules : CAN Interface Layer user configuration table file
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-26
* Description : 1.Create the file.
* 				2.Initialization Version
****************************************************************************/
#ifndef	_CANIF_CFG_TABLE_H
#define	_CANIF_CFG_TABLE_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "CanIf_Type.h"
#include "CanIf_Cfg_Define.h"

/*
 * Do not modify the array name
 *
 * If you ChNo is 0xFF,mean the array is end.
 * */
CanIf_CanMsgRxManagementDataBuffer_Type CanIf_CanMsgRxList[] =
{
		/*Index,ChNo,	MsgValid, 			MsgRxMode, 					MsgCheckRet,	MsgCheckMode,	Timeout,	CurrentTime,  	MsgId, 	Dlc,*/
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x32A,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x320,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x347,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x2E0,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x612,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x613,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x3D0,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_EVENT,		0x00,			0x07,			1000,		0,				0x706,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_EVENT,		0x00,			0x07,			1000,		0,				0x7DF,	8},
		{0,		0xFF,	CANIF_MSG_INVALID,	CANIF_MSG_MODE_NONE,		0x00,			0x0,			0	,		0,				0x0,	0}
};

/*
 * Do not modify the array name
 *
 * If you ChNo is 0xFF,mean the array is end.
 *
 * Note :
 * 1.the CycleTime and CurrentTime is counter
 * 2.the real time is CycleTime or CurrentTime * Task Tick
 *
 *
 * */
CanIf_CanMsgTxManagementDataBuffer_Type CanIf_CanMsgTxList[] =
{
		/*Index,ChNo, MsgValid, 			MsgTxMode, 					CycleTime,	CurrentTime,	TransmissionCounter,	TransmittedCounter,	MsgId,	Dlc,	Data*/
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	50,			0,				0,						0,					0x2F8,	8,		{1,2,3,4,0,0,0,0}},
		{1,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	50,			0,				0,						0,					0x2F9,	8,		{0,0,0,0,5,6,7,8}},
		{2,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	500,		0,				0,						0,					0x500,	8,		{9,0,0,0,0,0,0,0}},
		{3,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	500,		0,				0,						0,					0x501,	8,		{0,0,0,0,0,0,0,0}},
		{4,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_EVENT,		0,			0,				0,						0,					0x70E,	8,		{0,0,0,0,0,0,0,0}},
		{10,	0xFF,	CANIF_MSG_INVALID,	CANIF_MSG_MODE_NONE,		0,			0,				0,						0,					0xffff,	8,		{0,0,0,0,0,0,0,0}}
};





#endif /*_CANIF_CFG_TABLE_H*/
/*********************************File End*********************************/
