/****************************************************************************
* File Name : Dcm_Dsl_Implement.h
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
#ifndef	_DCM_DSL_IMPLEMENT_H_
#define	_DCM_DSL_IMPLEMENT_H_

/*Include head files AREA*/
#include "Dcm_Dsl_Interface.h"

/*Macro definition AREA*/




/*Variable Define AREA*/


/*Function implements AREA*/
/****************************************************************************
 * @function	Dsl_InitFunction
 * @brief  		Initiation DSL modules parameters
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsl_InitFunction(void)
{
	/*Initiation Dsl_SessionType variable*/
	Dsl_SessionType.PreSessionType = 0x01;
	Dsl_SessionType.CurrentSessionType = 0x01;

	/*Initiation Dsl_SecurityLevel variable*/
	Dsl_SecurityLevel.PreSecurityLevel = 0x00;
	Dsl_SecurityLevel.CurrentSecurityLevel = 0x00;
}

/****************************************************************************
 * @function	Dsl_SetSeesionType
 * @brief  		set seesion type
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsl_SetSeesionType(uint8 SesType)
{
	Dsl_SessionType.PreSessionType = Dsl_SessionType.CurrentSessionType;
	Dsl_SessionType.CurrentSessionType = SesType;
}

/****************************************************************************
 * @function	Dsl_SetSeesionType
 * @brief  		set seesion type
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsl_SetSecurityLevel(uint8 SecLevel)
{
	Dsl_SecurityLevel.PreSecurityLevel = Dsl_SecurityLevel.CurrentSecurityLevel;
	Dsl_SecurityLevel.CurrentSecurityLevel = SecLevel;
}

#endif /*_DCM_DSL_IMPLEMENT_H_*/
/*********************************File End*********************************/
