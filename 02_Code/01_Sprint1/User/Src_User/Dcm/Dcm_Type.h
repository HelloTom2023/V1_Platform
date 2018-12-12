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
 * diagnostic request message data,not converted to PDU
 * */
typedef struct Dcm_RxDiagRequestData_Struct_Type_Tag
{
	uint8 ChNo;			/*bus channel number*/
	uint8 ReqType; 		/*0: physical ; 1: function . when the pdutype is 0x00,this parameter is valid*/
	uint16 DataLength;
	uint8 *Data;		/*note : if you want to use the data element,you will init the pointer*/
}Dcm_RxDiagRequestData_Struct_Type;

/*
 * the following data send to CanTp modules
 * diagnostic response message data,is PDU converted to message data
 * */
typedef struct Dcm_TxDiagResponseData_Struct_Type_Tag
{
	uint8 ChNo;			/*bus channel number*/
	uint16 DataLength;
	uint8 *Data;		/*note : if you want to use the data element,you will init the pointer*/
}Dcm_TxDiagResponseData_Struct_Type;

/*
 * diagnostic request type
 * used for indication the diagnostic message id type
 * */
typedef enum Dcm_DiagRequestTpye_Enum_Type_Tag
{
	DCM_REQ_TYPE_PHY = 0x00,
	DCM_REQ_TYPE_FUNC = 0x01,
	DCM_REQ_TYPE_NONE
}Dcm_DiagRequestTpye_Enum_Type;

/*
 * the following data is request to PDU format.
 * used for dcm service protocol,and the request data from CanTp modules.
 *
 * */
typedef struct Dcm_RequestPDU_Struct_Type_Tag
{
	uint8 ChNo;								/*bus channel number*/
	Dcm_DiagRequestTpye_Enum_Type ReqType;
	uint8 SI;								/*Service Identifier,located : Dcm_RxDiagRequestStruct_Type.Data[0]*/
	uint8 SPRMIB;							/*suppressPosRspMsgIndicationBit,located : Dcm_RxDiagRequestStruct_Type.Data[1] bit7*/
	uint8 SubFunc;   						/*sub-function parameter value,located : Dcm_RxDiagRequestStruct_Type.Data[1] bit0~bit6, and this paramters rang is 0x00~0x7F*/
	uint16 DataLength;						/*Parameter data length,the data length not include the sub function id*/
	uint8 *Data;							/*note : if you want to use the data element,you will init the pointer*/
}Dcm_RequestPDU_Struct_Type;

/*
 * diagnostic positive response PDU
 * */
typedef struct Dcm_PositiveResponsePDUStruct_Type_Tag
{
	uint8 ChNo;				/*bus channel number*/
	uint8 SI;				/*Service Identifier*/
	uint8 SubFunc;   		/*sub-function parameter value,located : request data byte0 bit0~bit6, and this paramters rang is 0x00~0x7F*/
	uint16 DataLength;		/*Parameter data length,the data length not include the sub function id*/
	uint8 *Data;			/*note : if you want to use the data element,you will init the pointer*/
}Dcm_PositiveResponsePDU_Struct_Type;

/*
 * diagnostic negative response PDU
 * */
typedef struct Dcm_NegativeResponsePDUStruct_Type_Tag
{
	uint8 ChNo;				/*bus channel number*/
	uint8 SI;				/*Service Identifier*/
	uint8 SubFunc;   		/*sub-function parameter value,located : request data byte0 bit0~bit6, and this parameters rang is 0x00~0x7F*/
	uint8 NRC;				/*negative response codes*/
}Dcm_NegativeResponsePDU_Struct_Type;

/*
 * diagnostic service perform state machine
 * */
typedef enum Dcm_DiagServicePerformStatus_Enum_Type_Tag
{
	DCM_SERVICE_STATUS_INIT,
	DCM_SERVICE_STATUS_IDLE,
	DCM_SERVICE_STATUS_REQ,
	DCM_SERVICE_STATUS_RUN,
	DCM_SERVICE_STATUS_COMPLETED,
	DCM_SERVICE_STATUS_ERROR,
	DCM_SERVICE_STATUS_NONE
}Dcm_DiagServicePerformStatus_Enum_Type;

/*
 * Diagnostic service response type
 * */
typedef enum Dcm_DiagServiceResponseType_Enum_Type_Tag
{
	DCM_RESPONSE_TYPE_INIT,		/*Initiation Status,If process services function will setting to this status*/
	DCM_RESPONSE_TYPE_POSITIVE, /*Positive Response status.If process service function complete and shall response positive pud */
	DCM_RESPONSE_TYPE_NEGATIVE, /*Negative Response status.If process service function complete and shall response negative pud*/
	DCM_RESPONSE_TYPE_NOTTXNRC,	/*not be transmitted Negative Response status.If process service function complete,the ECU generated NRC but shall be not response negative pud*/
	DCM_RESPONSE_TYPE_MAX
}Dcm_DiagServiceResponseType_Enum_Type;

/*
 * UDS diagnostic service protocol control information
 *
 * */
typedef struct Dcm_UdsServiceProtocolCtrInfo_Struct_Type_Tag
{
	uint8 Index;											/*indication the SID in the service list located*/
	uint8 ChNo;												/*bus channel number*/
	Dcm_DiagRequestTpye_Enum_Type ReqType;
	uint8 SI;												/*Service Identifier*/
	uint8 SubFunc;   										/*sub-function parameter value,located : request data byte0 bit0~bit6, and this parameters rang is 0x00~0x7F*/
	Dcm_DiagServicePerformStatus_Enum_Type MachineState;	/*diagnostic service perform state machine*/
	Dcm_DiagServiceResponseType_Enum_Type ResType;			/*diagnostic response PDU type*/
}Dcm_UdsServiceProtocolCtrInfo_Struct_Type;

/*
 * UDS diagnostic support service table type
 *
 * */
typedef struct Dcm_SupportServiceList_Struct_Type_Tag
{
	uint8 Index;
	uint8 ChNo;													/* bus channel number*/
	uint8 SI;													/* Service Identifier*/
	uint8 SupportSPRMIB;										/* 0x01:support suppressPosRspMsgIndicationBit; 0x00:not support suppressPosRspMsgIndicationBit*/
	uint8 SupportReqType;										/* 0x01: support this type request; 0x00 : not support this type request
																 * bit0 : indication Physical request; bit1 : indication functional request
																*/
}Dcm_SupportServiceList_Struct_Type;

/*
 * UDS diagnostic support sub function table type of diagnostic services
 *
 * */
typedef struct Dcm_SupportSubFunctionList_Struct_Type_Tag
{
	uint8 Index;
	uint8 ChNo;													/* bus channel number*/
	uint8 SubId;												/* Sub function Identifier*/
	uint8 SupportSeesion;										/* 0x01:support this session ; 0x00:not support this session*/
	uint8 SupportSecurityLevel;									/* 0x01: support this security level; 0x00 : not support this security level*/
}Dcm_SupportSubFunctionList_Struct_Type;

/*
 * session type structure
 * */
typedef struct Dcm_SessionType_Struct_Type_Tag
{
	uint8 PreSessionType;
	uint8 CurrentSessionType;
}Dcm_SessionType_Struct_Type;

/*
 * security level structure
 * */
typedef struct Dcm_SecurityLevel_Struct_Type_Tag
{
	uint8 PreSecurityLevel;
	uint8 CurrentSecurityLevel;
}Dcm_SecurityLevel_Struct_Type;

#endif /* _DCM_TYPE_H_ */
