/****************************************************************************
* File Name : Dcm_Cfg_Table.h
*
* Modules : Diagnostic communication management Layer configuration file
*
* Summary : 1.configuration parameters Table
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-02
* Description : 1.Create the file.
* 				2.Initialization Version
****************************************************************************/
#ifndef	_DCM_CFG_TABLE_H_
#define	_DCM_CFG_TABLE_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Dcm_Type.h"
#include "Dcm_Cfg_Define.h"

/*
 * the diagnostic support service table
 * must not rename the array name
 * */
const Dcm_SupportServiceList_Struct_Type Dsp_SupportServiceList[] =
{
		/*Index,	ChNo,	SI	,	SupportSPRMIB, SupportReqType*/
		{0x00,		0x00,	0x10,	0x01		 , 0x03},
		{0x01,		0x00,	0x11,	0x01		 , 0x03},
		{0x02,		0x00,	0x14,	0x01		 , 0x03},
		{0x03,		0x00,	0x19,	0x01		 , 0x03},
		{0x04,		0x00,	0x22,	0x01		 , 0x03},
		{0x05,		0x00,	0x27,	0x01		 , 0x03},
		{0x06,		0x00,	0x28,	0x01		 , 0x03},
		{0x07,		0x00,	0x2E,	0x01		 , 0x03},
		{0x08,		0x00,	0x2F,	0x01		 , 0x03},
		{0x09,		0x00,	0x31,	0x01		 , 0x03},
		{0x0A,		0x00,	0x3E,	0x01		 , 0x03},
		{0x0B,		0x00,	0x85,	0x01		 , 0x03},
		{0xFF,		0x00,	0x00,	0x00		 , 0x00}
};

/*
 * 0x10 service support sub function list
 *
 * Note : the list Index range is 0x00~0x07
 * */
Dcm_SupportSubFunctionList_Struct_Type Dsp_Services_0x10_SupportFunctionList[] =
{
		/*Index,	ChNo,	SubId ,	SupportSeesion, SupportSecurityLevel*/
		{0x00,		0x00,	0x01,	0xE0		  , 0xE0},
		{0x01,		0x00,	0x02,	0x60		  , 0xE0},
		{0x02,		0x00,	0x03,	0xA0		  , 0xE0},
		{0xFF,		0x00,	0x00,	0x00		  , 0x00},
};

/*
 * 0x11 service support sub function list
 * */
Dcm_SupportSubFunctionList_Struct_Type Dsp_Services_0x11_SupportFunctionList[] =
{
		/*Index,	ChNo,	SubId ,	SupportSeesion, SupportSecurityLevel*/
		{0x00,		0x00,	0x01,	0x60		  , 0xE0},
		{0x01,		0x00,	0x02,	0x60		  , 0xE0},
		{0x02,		0x00,	0x03,	0x60		  , 0xE0},
		{0xFF,		0x00,	0x00,	0x00		  , 0x00},
};




#endif /*_DCM_CFG_TABLE_H_*/
/*********************************File End*********************************/
