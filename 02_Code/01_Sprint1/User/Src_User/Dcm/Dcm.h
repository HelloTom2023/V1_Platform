/****************************************************************************
* File Name : Dcm.h
*
* Modules : Diagnostic communication management Layer head file
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
#ifndef	_DCM_H_
#define	_DCM_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Dcm_Type.h"
#include "Dcm_Cfg_Define.h"
#include "VFB_Dcm.h"
#include "Dcm_TypeStack.h"

/*Macro definition AREA*/
#define _DCM_C_	/*define use CanTp.c*/

#ifndef _DCM_C_
#define DCM_EXTERN_API
#define DCM_LOCAL_API
#else
#define DCM_EXTERN_API extern
#define DCM_LOCAL_API static
#endif /*_DCM_C_*/





/*Variable Define AREA*/
uint8 ReqDataBuffer[DCM_REQBUFF_SIZE];
uint8 PosResDataBuffer[DCM_POSRESBUF_SIZE];
//Dcm_RequestPDU_Struct_Type Dcm_ReqPDU;
//Dcm_PositiveResponsePDU_Struct_Type Dcm_PosResPDU;
//Dcm_NegativeResponsePDU_Struct_Type Dcm_NegResPDU;
Dcm_UdsServiceProtocolCtrInfo_Struct_Type Dsp_UdsServiceCtrInfo[DCM_SUPPORT_BUS_CHNO_MAX]; /*One set of data for each bus*/
Dcm_SessionType_Struct_Type Dsl_SessionType;
Dcm_SecurityLevel_Struct_Type Dsl_SecurityLevel;

/*Function declaration AREA*/
/****************************************************************************
 * @function	Dcm_InitFunction
 * @brief  		init Dcm parameters
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_EXTERN_API void Dcm_InitFunction(void);

/****************************************************************************
 * @function	Dcm_MainFunction
 * @brief  		init Dcm parameters
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_EXTERN_API void Dcm_MainFunction(void);

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
DCM_EXTERN_API uint8 Dcm_RxDiagRequestInfo(uint8 ChNo, uint8 ReqType, uint16 DataLength,uint8* ptr_Data);

/****************************************************************************
 * @function	Dcm_TxDiagResponseInfo
 * @brief  		Indication the can to receive can message
 * @param  		ChNo: input parameters,bus channel index.
  *				DataLength : input parameters,the diagnostic response data length
 *				ptr_Data : input parameters,the diagnostic response data
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
DCM_EXTERN_API uint8 Dcm_TxDiagResponseInfo(uint8 ChNo, uint16 DataLength, uint8* ptr_Data);


#endif /*_DCM_H_*/
/*********************************File End*********************************/
