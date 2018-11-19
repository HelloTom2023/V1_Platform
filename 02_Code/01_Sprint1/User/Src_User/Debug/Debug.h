/****************************************************************************
* File Name : Debug.h
*
* Modules : Debug modules head file
*
* Summary :
*
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-11-04
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_DEBUG_H
#define	_DEBUG_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Debug_Cfg_Define.h"
#include "VFB_Debug.h"


/*Macro definition AREA*/
#define _DEBUG_C	/*define use Debug.c*/

#ifndef _DEBUG_C
#define DEBUG_API_CALL
#define DEBUG_API_LOCAL
#else
#define DEBUG_EXTERN_API extern
#define DEBUG_LOCAL_API static
#endif /*_DEBUG_C*/


/*Variable declaration AREA*/


/*Function declaration AREA*/
/****************************************************************************
 * @function	Debug_Can_OutputInfo
 * @brief
 * @param
 * @retval
 * @attention
****************************************************************************/
#if (DEBUG_CAN == ON)
#define Debug_Can_OutputInfo(x)		(x)
#else
#define Debug_Can_OutputInfo(x)
#endif

/****************************************************************************
 * @function	Debug_CanIf_OutputInfo
 * @brief
 * @param
 * @retval
 * @attention
****************************************************************************/
#if (DEBUG_CANIF == ON)
#define Debug_CanIf_OutputInfo(x)		(x)
#else
#define Debug_CanIf_OutputInfo(x)
#endif

/****************************************************************************
 * @function	Debug_Com_OutputInfo
 * @brief
 * @param
 * @retval
 * @attention
****************************************************************************/
#if (DEBUG_COM == ON)
#define Debug_Com_OutputInfo(x)		(x)
#else
#define Debug_Com_OutputInfo(x)
#endif

/****************************************************************************
 * @function	Debug_ComUser_OutputInfo
 * @brief
 * @param
 * @retval
 * @attention
****************************************************************************/
#if (DEBUG_COMUSER == ON)
#define Debug_ComUser_OutputInfo(x)		(x)
#else
#define Debug_ComUser_OutputInfo(x)
#endif

/****************************************************************************
 * @function	Debug_CanTp_OutputInfo
 * @brief
 * @param
 * @retval
 * @attention
****************************************************************************/
#if (DEBUG_CANTP == ON)
#define Debug_CanTp_OutputInfo(x)		(x)
#else
#define Debug_CanTp_OutputInfo(x)
#endif


#endif /*_DEBUG_H*/
/*********************************File End*********************************/
