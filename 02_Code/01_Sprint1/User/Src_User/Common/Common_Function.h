/****************************************************************************
* File Name : Common_Function.h
*
* Modules : Common function head files.
*
* Summary : Declaration system common function.
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-09
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_COMMON_FUNCTION_H
#define	_COMMON_FUNCTION_H

/*Include head files AREA*/
#include "common_Type.h"
#include <string.h>

/*Macro definition AREA*/
#define _COMMON_FUNCTION_C		/*Define the system use Common_Function.c*/

#ifndef _COMMON_FUNCTION_C		/*Define function type in Common_Function.c*/
#define COMMON_FUNCTION_EXTERN_API
#define COMMON_FUNCTION_LOCAL_API
#else
#define COMMON_FUNCTION_EXTERN_API extern
#define COMMON_FUNCTION_LOCAL_API static
#endif

/****************************************************************************
 * @function	CommFunc_MemSetValue
 * @brief		set value to ptr_DestData
 * @param  		ptr_DestData :  output parameters , target data pointer
 *				Value : input parameters , needs to be set values
 *				DataLength : input parameters, data length.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
#define CommFunc_MemSetValue(ptr_DestData,Value,DataLength)		memset(ptr_DestData,Value,DataLength)

/****************************************************************************
 * @function	CommFunc_MemCopyData
 * @brief		set value to ptr_DestData
 * @param  		ptr_DestData :  output parameters , target data pointer
 *				ptr_SoureData : output parameters , source data pointer
 *				DataLength : input parameters, data length.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
#define CommFunc_MemCopyData(ptr_DestData,ptr_SoureData,DataLength)		memset(ptr_DestData,ptr_SoureData,DataLength)






#endif /*_COMMON_FUNCTION_H*/
/*********************************File End*********************************/
