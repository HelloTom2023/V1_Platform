/****************************************************************************
* File Name : Dcm_Dsp_Implement.h
*
* Modules : Diagnostic communication management modules submodules
*           DSP : Diagnostic Service Processing
*                 Implement diagnostic service protocol function
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-08
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_DCM_DSP_INTERFACE_H_
#define	_DCM_DSP_INTERFACE_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Dcm_Type.h"
#include "Dcm_Cfg_Define.h"
#include "VFB_Dcm.h"
#include "Dcm.h"

/*Macro definition AREA*/





/*Variable Define AREA*/



/*Function declaration AREA*/
/****************************************************************************
 * @function	Dsp_MainFunction
 * @brief  		NULL
 * @param  		ChNo : Input parameters, bus channel.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsp_MainFunction(uint8 ChNo);

/****************************************************************************
 * @function	Dsp_TxDiagResponsePositivePDU
 * @brief  		NULL
 * @param  		ChNo : Input parameters, bus channel
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
DCM_EXTERN_API uint8 Dsp_TxDiagResponsePositivePDU(uint8 ChNo);

/****************************************************************************
 * @function	Dsp_TxDiagResponseNegativePDU
 * @brief  		NULL
 * @param  		ChNo : Input parameters, bus channel
 * 				SID : input parameters, services identifier.
 * 				NRC : Input parameters, NRC
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
DCM_EXTERN_API uint8 Dsp_TxDiagResponseNegativePDU(uint8 ChNo,uint8 SID,uint8 NRC);

/****************************************************************************
 * @function	Dsp_CheckServicesIsSupportSubFunction
 * @brief  		NULL
 * @param  		SID : Input parameters, diagnostic services id
 * @retval 		DCM_E_NOT_OK : the SID not support sub function.
 *              DCM_E_OK : the SID support sub function.
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckServicesIsSupportSubFunction(uint8 SID);

/****************************************************************************
 * @function	Dsp_CheckServicesIsSupport
 * @brief  		NULL
 * @param  		SID : Input parameters, diagnostic services id
 * @retval 		0xff : the SID not support.
 *              0x00 ~ 0xfe : the SID in the list index
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckServicesIsSupport(uint8 SID);

/****************************************************************************
 * @function	Dsp_CheckSubFunctionIsSupport
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters
 * 				SubId : Input parameters, diagnostic services sub function id
 * @retval 		0xff : the sub id not support.
 *              0x00 ~ 0xfe : the sub id in the list index
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckSubFunctionIsSupport(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8 SubId);

/****************************************************************************
 * @function	Dsp_CheckServicesIsSupportInActiveSession
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters
 * @retval 		E_OK : Check OK
 * 				E_NOT_OK : Check failure
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckServicesIsSupportInActiveSession(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList);

/****************************************************************************
 * @function	Dsp_CheckSubFunctionIsSupportInActiveSession
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters
 * 				SubId : Input parameters
 * @retval 		E_OK : Check OK
 * 				E_NOT_OK : Check failure
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckSubFunctionIsSupportInActiveSession(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8 SubId);

/****************************************************************************
 * @function	Dsp_ChecksuppressPosRspMsgIndicationBitIsSupport
 * @brief  		NULL
 * @param  		SID : Input parameters, diagnostic services id
 * @retval 		DCM_E_OK : support.
 *              DCM_E_NOT_OK : not support
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckSuppressPosRspMsgIndicationBitIsSupport(uint8 SID);

/****************************************************************************
 * @function	Dsp_GetServicesSessionTypeMask
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters,
 * 				ptr_SesTypeMask : output parameters,
 * @retval 		ret : function error event value
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_GetServicesSessionTypeMask(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8* ptr_SesTypeMask);

/****************************************************************************
 * @function	Dsp_GetSubFunctionSessionTypeMask
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters,
 * 				SubId : Input parameters,
 * 				ptr_SesTypeMask : output parameters,
 * @retval 		ret : function error event value
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_GetSubFunctionSessionTypeMask(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8 SubId,uint8* ptr_SesTypeMask);

/****************************************************************************
 * @function	Dsp_GetServicesSecurityLevelMask
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters,
 * 				ptr_SecLevelMask : output parameters,
 * @retval 		ret : function error event value
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_GetServicesSecurityLevelMask(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8* ptr_SecLevelMask);

/****************************************************************************
 * @function	Dsp_GetDTCGroupTypeOfClearDiagnosticInformationIsSupport
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters,
 * 				DTCGroupTypes : input parameters,
 * @retval 		DCM_E_OK : support
 * 				DCM_E_NOT_OK : not support
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_GetDTCGroupTypeOfClearDiagnosticInformationIsSupport(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8 DTCGroupTypes);

/****************************************************************************
 * @function	Dsp_ServicesFunction_Process
 * @brief  		process the diagnostic services
 * @param  		ChNo : Input parameters, bus channel
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_Process(uint8 ChNo);

/****************************************************************************
 * @function	Dsp_ServicesFunction_DiagnosticSessionControl
 * @brief  		Diagnostic service $10 handling
 * @param  		ChNo : Input parameters, Bus channel
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_DiagnosticSessionControl(uint8 ChNo);

/****************************************************************************
 * @function	Dsp_ServicesFunction_ECUReset
 * @brief  		Diagnostic service $11 handling
 * @param  		ChNo : Input parameters,Bus Channel.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_ECUReset(uint8 ChNo);

/****************************************************************************
 * @function	Dsp_ServicesFunction_ClearDiagnosticInformation
 * @brief  		Diagnostic service $14 handling
 * @param  		ChNo : Input parameters,Bus Channel.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_ClearDiagnosticInformation(uint8 ChNo);

#endif /*_DCM_DSP_INTERFACE_H_*/
/*********************************File End*********************************/
