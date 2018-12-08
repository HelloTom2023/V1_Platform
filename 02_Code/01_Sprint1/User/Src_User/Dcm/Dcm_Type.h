/****************************************************************************
* File Name : Dcm_Type.h
*
* Modules : Diagnostic Communication management Layer head file
*
* Summary : 1.The file define use data type in diagnostic communication layer.
*
*
*
* Reference Documents : None
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-02
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef _DCM_TYPE_H_
#define _DCM_TYPE_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Dcm_Cfg_Define.h"

/*
 * the following data from to CanTp modules
 * */
typedef struct Dcm_RxDiagRequestStruct_Type_Tag
{
	uint8 BusChannel;
	uint8 ReqType; 		/*0: physical ; 1: function . when the pdutype is 0x00,this parameter is valid*/
	uint16 DataLength;
	uint8 *Data;		/*note : if you want to use the data element,you will init the pointer*/
}Dcm_RxDiagRequestStruct_Type;

/*
 * the following data send to CanTp modules
 * */
typedef struct Dcm_TxDiagResponseStruct_Type_Tag
{
	uint8 BusChannel;
	uint16 DataLength;
	uint8 *Data;		/*note : if you want to use the data element,you will init the pointer*/
}Dcm_TxDiagResponseStruct_Type;

#endif /* _DCM_TYPE_H_ */
