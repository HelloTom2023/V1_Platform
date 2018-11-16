/****************************************************************************
* File Name : ComUser.h
*
* Modules : Communication user modules head file
*
* Summary :
*
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-26
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_COM_USER_H
#define	_COM_USER_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "ComUser_Type.h"
#include "ComUser_Cfg_Define.h"
#include "ComUser_Cfg_Table.h"
#include "VFB_ComUser.h"


/*Macro definition AREA*/
#define _COM_USER_C	/*define use ComUser.c*/

#ifndef _COM_USER_C
#define COM_USER_API_CALL
#define COM_USER_API_LOCAL
#else
#define COM_USER_EXTERN_API extern
#define COM_USER_LOCAL_API static
#endif /*_COM_USER_C*/


/*Variable declaration AREA*/


/*Function declaration AREA*/
/****************************************************************************
 * @function	ComUser_Init
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_Init(void);

/****************************************************************************
 * @function	ComUser_MainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_MainFunction(void);

/****************************************************************************
 * @function	ComUser_RxMainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_RxMainFunction(void);

/****************************************************************************
 * @function	ComUser_RxMainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_TxMainFunction(void);


#endif /*_COM_USER_H*/
/*********************************File End*********************************/
