/****************************************************************************
* File Name : CanIf_Cfg_Table.h
*
* Modules : CAN Interface Layer configuration file
*
* Summary : 1.configuration parameters Table
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



CanIf_CanMsgSoftFilterDlcCheck_Type CanIf_CanMsgSoftFilterDlcCheckTable[] =
{/*		Index	CanChNo,	CanMsgId,	Dlc*/
		{0,		0,		0x100,		8},
		{1,		0,		0x105,		8},
		{2,		0,		0x2E0,		8},
		{3,		0,		0x3F0,		8},
		{4,		0,		0x520,		8},
		{5,		0,		0x801,		6},
		{6,		0,		0x310,		8},
		{7,		0,		0x405,		8},
		{8,		0,		0x7A0,		8},
		{9,		0,		0x7DF,		8},
		{10,		0xff,	0x00,		0x00}
};

/*The array name not modify*/
CanIf_CanMsgTxManagementDataBuffer_Type CanIf_CanMsgTxList[] =
{
		/*ChNo, MsgValid, MsgTxMode, CycleTime, CurrentTime, TransmissionCounter, TransmittedCounter, 	MsgId, Dlc,	 Data*/
		{0,		1,			0,			100,		0,				0,						0,			0x121,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			0,			100,		0,				0,						0,			0x123,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			0,			100,		0,				0,						0,			0x125,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			0,			100,		0,				0,						0,			0x321,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			0,			100,		0,				0,						0,			0x221,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			0,			100,		0,				0,						0,			0x521,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			1,			10,			0,				3,						0,			0x621,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			0,			100,		0,				0,						0,			0x126,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			0,			100,		0,				0,						0,			0x171,	8,	{0,0,0,0,0,0,0,0}},
		{0,		1,			0,			100,		0,				0,						0,			0x191,	8,	{0,0,0,0,0,0,0,0}},
		{0,	  0xff,			0,			100,		0,				0,						0,			0xffff,	8,	{0,0,0,0,0,0,0,0}}
};





#endif /*_CANIF_CFG_TABLE_H*/
/*********************************File End*********************************/
