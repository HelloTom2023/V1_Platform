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
 * @brief  		set session type
 * @param  		SesType : input parameters , will be setting session type value
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsl_SetSessionType(uint8 SesType)
{
	Dsl_SessionType.PreSessionType = Dsl_SessionType.CurrentSessionType;
	Dsl_SessionType.CurrentSessionType = SesType;
}

/****************************************************************************
 * @function	Dsl_GetSessionType
 * @brief  		get session type
 * @param  		SesType : output parameters
 * @retval 		ret : function error event value
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsl_GetSessionType(uint8* ptr_SesType)
{
	uint8 ret = E_NOT_OK;

	/*Input parameters check*/
	if(NULL == ptr_SesType)
	{
		ret = E_PARAM_NULLPTR;
	}
	else
	{
		*ptr_SesType = Dsl_SessionType.CurrentSessionType;
		ret = E_OK;
	}

	return ret;
}

/****************************************************************************
 * @function	Dsl_SetSecurityLevel
 * @brief  		set security level
 * @param  		SecLevel : input parameters,will be setting security level value
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsl_SetSecurityLevel(uint8 SecLevel)
{
	Dsl_SecurityLevel.PreSecurityLevel = Dsl_SecurityLevel.CurrentSecurityLevel;
	Dsl_SecurityLevel.CurrentSecurityLevel = SecLevel;
}

/****************************************************************************
 * @function	Dsl_GetSecurityLevel
 * @brief  		get security type
 * @param  		SecLevel : output parameters
 * @retval 		ret : function error event value
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsl_GetSecurityLevel(uint8* ptr_SecLevel)
{
	uint8 ret = E_NOT_OK;

	/*Input parameters check*/
	if(NULL == ptr_SecLevel)
	{
		ret = E_PARAM_NULLPTR;
	}
	else
	{
		*ptr_SecLevel = Dsl_SecurityLevel.CurrentSecurityLevel;
		ret = E_OK;
	}

	return ret;
}

/****************************************************************************
 * @function	Dsl_GetSessionP2ServerMax
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsl_GetSessionP2ServerMax(uint8 Index,uint16* P2ServerMax)
{
	uint8 ret = DCM_E_NOT_OK;

	/*Check Input parameters*/
	if(NULL == P2ServerMax)
	{
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get P2Server and P2*Server parameters*/
	switch(Index)
	{
		case 0x00:
		{
			*P2ServerMax = Dsl_GetSessionP2SM(0);
			ret = DCM_E_OK;
			break;
		}
		case 0x01:
		{
			*P2ServerMax = Dsl_GetSessionP2SM(1);
			ret = DCM_E_OK;
			break;
		}
		case 0x02:
		{
			*P2ServerMax = Dsl_GetSessionP2SM(2);
			ret = DCM_E_OK;
			break;
		}
		case 0x03:
		{
			*P2ServerMax = Dsl_GetSessionP2SM(3);
			ret = DCM_E_OK;
			break;
		}
		case 0x04:
		{
			*P2ServerMax = Dsl_GetSessionP2SM(4);
			ret = DCM_E_OK;
			break;
		}
		case 0x05:
		{
			*P2ServerMax = Dsl_GetSessionP2SM(5);
			ret = DCM_E_OK;
			break;
		}
		case 0x06:
		{
			*P2ServerMax = Dsl_GetSessionP2SM(6);
			ret = DCM_E_OK;
			break;
		}
		case 0x07:
		{
			*P2ServerMax = Dsl_GetSessionP2SM(7);
			ret = DCM_E_OK;
			break;
		}
		default:
		{
			ret = DCM_E_NOT_OK;
		}
	}
	return ret;
}

/****************************************************************************
 * @function	Dsl_GetSessionP2_ServerMax
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsl_GetSessionP2_ServerMax(uint8 Index,uint16* P2_ServerMax)
{
	uint8 ret = DCM_E_NOT_OK;

	/*Check Input parameters*/
	if(NULL == P2_ServerMax)
	{
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Get P2Server and P2*Server parameters*/
	switch(Index)
	{
		case 0x00:
		{
			*P2_ServerMax = Dsl_GetSessionP2ESM(0);
			ret = DCM_E_OK;
			break;
		}
		case 0x01:
		{
			*P2_ServerMax = Dsl_GetSessionP2ESM(1);
			ret = DCM_E_OK;
			break;
		}
		case 0x02:
		{
			*P2_ServerMax = Dsl_GetSessionP2ESM(2);
			ret = DCM_E_OK;
			break;
		}
		case 0x03:
		{
			*P2_ServerMax = Dsl_GetSessionP2ESM(3);
			ret = DCM_E_OK;
			break;
		}
		case 0x04:
		{
			*P2_ServerMax = Dsl_GetSessionP2ESM(4);
			ret = DCM_E_OK;
			break;
		}
		case 0x05:
		{
			*P2_ServerMax = Dsl_GetSessionP2ESM(5);
			ret = DCM_E_OK;
			break;
		}
		case 0x06:
		{
			*P2_ServerMax = Dsl_GetSessionP2ESM(6);
			ret = DCM_E_OK;
			break;
		}
		case 0x07:
		{
			*P2_ServerMax = Dsl_GetSessionP2ESM(7);
			ret = DCM_E_OK;
			break;
		}
		default:
		{
			ret = DCM_E_NOT_OK;
		}
	}
	return ret;
}

#endif /*_DCM_DSL_IMPLEMENT_H_*/
/*********************************File End*********************************/
