/****************************************************************************
* File Name : Dcm.c
*
* Modules : Diagnostic Communication management Layer source file
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-02
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/

/*Include head files AREA*/
#include "Dcm.h"
#include "Dcm_Cfg_Table.h" /*The table only used by Dcm.C*/
#include "Dcm_ServiceProtocol_Interface.h"
#include "Dcm_ServiceProtocol_Implement.h"

/*Macro definition AREA*/




/*Variable declaration AREA*/


/*Function implement AREA*/
/****************************************************************************
 * @function	Dcm_InitFunction
 * @brief  		Initiation DCM parameters
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_EXTERN_API void Dcm_InitFunction(void)
{
	/*Initiation Dcm_ReqPDU*/
	Dcm_ReqPDU.Data = ReqDataBuffer;

	/*Initiation Dcm_PosResPDU*/
	Dcm_PosResPDU.Data = PosResDataBuffer;
}

/****************************************************************************
 * @function	Dcm_MainFunction
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_EXTERN_API void Dcm_MainFunction(void)
{

}

/****************************************************************************
 * @function	Dcm_RxDiagRequestInfo
 * @brief  		Receive the diagnostic from Tp layer
 * @param  		ChNo: input parameters,bus channel index.
 *				ReqType : input parameters,the diagnostic request message type.
 *				DataLength : input parameters,the diagnostic request data length
 *				ptr_Data : input parameters,the diagnostic request data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
DCM_EXTERN_API uint8 Dcm_RxDiagRequestInfo(uint8 ChNo, uint8 ReqType, uint16 DataLength,uint8* ptr_Data)
{
	uint8 ret = E_NOT_OK;
	uint8 i = 0;

	/*Check the input parameters*/
	if(NULL == ptr_Data)
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*doing noting*/
	}

	/*Debug information*/
	Dcm_Debug_OutputInfo(_T("Dcm_RxDiagRequestInfo:\n ChNo = %d,ReqType = %d,DataLength = %d [",\
			ChNo,ReqType,DataLength));
	for(i = 0; i < DataLength; i++)
	{
		Dcm_Debug_OutputInfo(_T("%x ",ptr_Data[i]));
	}
	Dcm_Debug_OutputInfo(_T("]\n"));

	/*
	 * Convert diagnostic message to request PDU
	 * The diagnostic message from CanTp modules
	 * The request PDU used for diagnostic service
	 * */
	Dcm_ReqPDU.ChNo = ChNo;
	Dcm_ReqPDU.ReqType = (Dcm_DiagRequestTpye_Enum_Type) ReqType;
	Dcm_ReqPDU.SI = ptr_Data[0];
	Dcm_ReqPDU.SubFunc = ptr_Data[1] & 0x7F;
	Dcm_ReqPDU.SPRMIB = CommFunc_BitShiftRigth(ptr_Data[1],0x07) & 0x01;
	Dcm_ReqPDU.DataLength = DataLength;
	memcpy(Dcm_ReqPDU.Data, ptr_Data, DataLength);

	/*
	 * Update uds service protocol control information
	 * */
	Dcm_UdsServiceCtrInfo.ChNo = Dcm_ReqPDU.ChNo;
	Dcm_UdsServiceCtrInfo.ReqType = Dcm_ReqPDU.ReqType;
	Dcm_UdsServiceCtrInfo.SI = Dcm_ReqPDU.SI;
	Dcm_UdsServiceCtrInfo.SubFunc = Dcm_ReqPDU.SubFunc;
	Dcm_UdsServiceCtrInfo.MachineState = DCM_SERVICE_STATUS_REQ;

	return ret;
}

/****************************************************************************
 * @function	Dcm_TxDiagResponseInfo
 * @brief  		Indication the can to receive can message
 * @param  		ChNo: input parameters,bus channel index.
  *				DataLength : input parameters,the diagnostic response data length
 *				ptr_Data : input parameters,the diagnostic response data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
DCM_EXTERN_API uint8 Dcm_TxDiagResponseInfo(uint8 ChNo, uint16 DataLength, uint8* ptr_Data)
{
	uint8 ret = E_NOT_OK;
	uint8 i = 0x00;

	/*Check the input parameters*/
	if(NULL == ptr_Data)
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*doing noting*/
	}

	/*Debug information*/
	Dcm_Debug_OutputInfo(_T("Dcm_TxDiagResponseInfo:\n ChNo = %d,,DataLength = %d [",ChNo,DataLength));
	for(i = 0; i < DataLength; i++)
	{
		Dcm_Debug_OutputInfo(_T("%x ",ptr_Data[i]));
	}
	Dcm_Debug_OutputInfo(_T("]\n"));

	/*Send the diagnostic response PDU to CanTp modules*/
	ret = Dcm_CanTp_SendDiagnosticResponseData(ChNo,DataLength,ptr_Data);

	return ret;
}

/*********************************File End*********************************/
