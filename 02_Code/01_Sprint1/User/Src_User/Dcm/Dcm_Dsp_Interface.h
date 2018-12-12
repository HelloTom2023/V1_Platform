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
#define Dsp_GetSessionP2ServerMax(Index)	DCM_SESSION_P2SM_##Index
#define Dsp_GetSessionP2_ServerMax(Index)	DCM_SESSION_P2ESM_##Index




/*Variable Define AREA*/



/*Function declaration AREA*/
/****************************************************************************
 * @function	Dsp_MainFunction
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsp_MainFunction(void);

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
 * @function	Dsp_ServicesFunction_Process
 * @brief  		process the diagnostic services
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_Process(void);

/****************************************************************************
 * @function	Dsp_ServicesFunction_DiagnosticSessionControl
 * @brief  		Diagnostic service $10 handling
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_DiagnosticSessionControl(void);

/****************************************************************************
 * @function	Dsp_ServicesFunction_ECUReset
 * @brief  		Diagnostic service $11 handling
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_ECUReset(void);

#endif /*_DCM_DSP_INTERFACE_H_*/
/*********************************File End*********************************/
