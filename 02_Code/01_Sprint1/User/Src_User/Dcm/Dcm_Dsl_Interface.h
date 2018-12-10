/****************************************************************************
* File Name : Dcm_Dsp_Implement.h
*
* Modules : Diagnostic communication management modules submodules
*           DSL : Diagnostic Session Layer
*                 Implement diagnostic Session and security level manager
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-10
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_DCM_DSL_INTERFACE_H_
#define	_DCM_DSL_INTERFACE_H_

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
 * @function	Dsl_InitFunction
 * @brief  		Initiation DSL modules parameters
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsl_InitFunction(void);

/****************************************************************************
 * @function	Dsl_SetSeesionType
 * @brief  		set seesion type
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsl_SetSeesionType(uint8 SesType);

/****************************************************************************
 * @function	Dsl_SetSeesionType
 * @brief  		set seesion type
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsl_SetSecurityLevel(uint8 SecLevel);

#endif /*_DCM_DSL_INTERFACE_H_*/
/*********************************File End*********************************/
