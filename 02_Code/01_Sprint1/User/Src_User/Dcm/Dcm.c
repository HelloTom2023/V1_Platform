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
#include "Dcm_Dsl_Interface.h"
#include "Dcm_Dsl_Implement.h"
#include "Dcm_Dsp_Interface.h"
#include "Dcm_Dsp_Implement.h"


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
	uint8 i = 0x00;

	Dsl_InitFunction();

	for(i = 0x00; i < DCM_SUPPORT_BUS_CHNO_MAX;i++)
	{
		/*Initiation Dsp_UdsServiceCtrInfo*/
		Dsp_UdsServiceCtrInfo[i].ChNo = i;
		Dsp_UdsServiceCtrInfo[i].Index = 0x00;
		Dsp_UdsServiceCtrInfo[i].MachineState = DCM_SERVICE_STATUS_IDLE;
		Dsp_UdsServiceCtrInfo[i].SI = 0x00;
		Dsp_UdsServiceCtrInfo[i].SubFunc = 0x00;
		Dsp_UdsServiceCtrInfo[i].ReqType = DCM_REQ_TYPE_NONE;
		Dsp_UdsServiceCtrInfo[i].SPRMIB = 0x00;
		Dsp_UdsServiceCtrInfo[i].ReqDL = 0x00;
		Dsp_UdsServiceCtrInfo[i].ReqData = ReqDataBuffer;
		Dsp_UdsServiceCtrInfo[i].ResType = DCM_RESPONSE_TYPE_INIT;
		Dsp_UdsServiceCtrInfo[i].PosResDL = 0x00;
		Dsp_UdsServiceCtrInfo[i].PosResData = PosResDataBuffer;
		Dsp_UdsServiceCtrInfo[i].NRC = 0x00;
	}

}

/****************************************************************************
 * @function	Dcm_MainFunction
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
uint8 Dcm_Init_Flag = 0x00;/*only used for debug*/
DCM_EXTERN_API void Dcm_MainFunction(void)
{
	uint8 i = 0x00;
	/*
	 * Debug code
	 * */
	if(Dcm_Init_Flag == 0x00)
	{
		Dcm_Init_Flag = 0x01;
		Dcm_InitFunction();
	}

	for(i = 0x00; i < DCM_SUPPORT_BUS_CHNO_MAX; i++)
	{
		Dsp_MainFunction(i);
	}

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
	 * Check the diagnostic service handler machine state
	 * */
	if(DCM_SERVICE_STATUS_INIT == Dsp_UdsServiceCtrInfo[ChNo].MachineState)
	{
		/*Reserved : it will report DET*/
		/*If the DCM in this status,mean the Dcm module initiation not complete.*/
	}
	else if(DCM_SERVICE_STATUS_IDLE != Dsp_UdsServiceCtrInfo[ChNo].MachineState)
	{
		/*
		 * if the MachineState is not IDLE,it mean the dcm is busy. so dcm shall be response NRC21
		 * */
		Dsp_TxDiagResponseNegativePDU(ChNo,ptr_Data[0],DCM_NRC_BRR);
	}
	else
	{
		/*
		 * Convert diagnostic message to request PDU
		 * The diagnostic message from CanTp modules
		 * The request PDU used for diagnostic service
		 * */
		/*Check if the services supports sub function*/
		if(DCM_E_OK == Dsp_CheckServicesIsSupportSubFunction(ptr_Data[0]))
		{
			Dsp_UdsServiceCtrInfo[ChNo].ChNo = ChNo;
			Dsp_UdsServiceCtrInfo[ChNo].ReqType = (Dcm_DiagRequestTpye_Enum_Type) ReqType;
			Dsp_UdsServiceCtrInfo[ChNo].SI = ptr_Data[0];
			Dsp_UdsServiceCtrInfo[ChNo].SubFunc = ptr_Data[1] & 0x7F;
			Dsp_UdsServiceCtrInfo[ChNo].SPRMIB = CommFunc_BitShiftRigth(ptr_Data[1],0x07) & 0x01;
			Dsp_UdsServiceCtrInfo[ChNo].ReqDL = DataLength-2;/*The DataLength will decrease the SID and SubFunction Bytes*/
			memcpy(Dsp_UdsServiceCtrInfo[ChNo].ReqData, &ptr_Data[2], Dsp_UdsServiceCtrInfo[ChNo].ReqDL);

			Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_REQ;
		}
		else
		{
			Dsp_UdsServiceCtrInfo[ChNo].ChNo = ChNo;
			Dsp_UdsServiceCtrInfo[ChNo].ReqType = (Dcm_DiagRequestTpye_Enum_Type) ReqType;
			Dsp_UdsServiceCtrInfo[ChNo].SI = ptr_Data[0];
			Dsp_UdsServiceCtrInfo[ChNo].SubFunc = 0x00; /*Initiation default value*/
			Dsp_UdsServiceCtrInfo[ChNo].SPRMIB = 0x00;  /*Initiation default value*/
			Dsp_UdsServiceCtrInfo[ChNo].ReqDL = DataLength-1;/*The DataLength will decrease the SID and SubFunction Bytes*/
			memcpy(Dsp_UdsServiceCtrInfo[ChNo].ReqData, &ptr_Data[1], Dsp_UdsServiceCtrInfo[ChNo].ReqDL);

			Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_REQ;
		}

	}

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
