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

/*Do not modify the array name*/
CanIf_CanMsgRxManagementDataBuffer_Type CanIf_CanMsgRxList[] =
{
		/*Index,ChNo,	MsgValid, 			MsgRxMode, 					MsgCheckRet,	MsgCheckMode,	Timeout,	CurrentTime,  	MsgId, 	Dlc,*/
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x340,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x350,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x360,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x370,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x380,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_EVENT,		0x00,			0x07,			1000,		0,				0x390,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x540,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x740,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x840,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0xA40,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x140,	8},
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	0x00,			0x07,			1000,		0,				0x240,	8},
		{0,		0xFF,	CANIF_MSG_INVALID,	CANIF_MSG_MODE_NONE,		0x00,			0x0,			0	,		0,				0x0,	0}
};

/*Do not modify the array name*/
CanIf_CanMsgTxManagementDataBuffer_Type CanIf_CanMsgTxList[] =
{
		/*Index,ChNo, MsgValid, 			MsgTxMode, 					CycleTime,	CurrentTime,	TransmissionCounter,	TransmittedCounter,	MsgId,	Dlc,	Data*/
		{0,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x121,	8,		{0,0,0,0,0,0,0,0}},
		{1,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x123,	8,		{0,0,0,0,0,0,0,0}},
		{2,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x125,	8,		{0,0,0,0,0,0,0,0}},
		{3,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x321,	8,		{0,0,0,0,0,0,0,0}},
		{4,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x221,	8,		{0,0,0,0,0,0,0,0}},
		{5,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x521,	8,		{0,0,0,0,0,0,0,0}},
		{6,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_EVENT,		10,			0,				3,						0,					0x621,	8,		{0,0,0,0,0,0,0,0}},
		{7,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x126,	8,		{0,0,0,0,0,0,0,0}},
		{8,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x171,	8,		{0,0,0,0,0,0,0,0}},
		{9,		0,		CANIF_MSG_VALID,	CANIF_MSG_MODE_PERIODIC,	100,		0,				0,						0,					0x191,	8,		{0,0,0,0,0,0,0,0}},
		{10,	0xFF,	CANIF_MSG_INVALID,	CANIF_MSG_MODE_NONE,		0,			0,				0,						0,					0xffff,	8,		{0,0,0,0,0,0,0,0}}
};





#endif /*_CANIF_CFG_TABLE_H*/
/*********************************File End*********************************/
