/****************************************************************************
* File Name : ComUser.c
*
* Modules : Communication user modules source file
*
* Summary : 1.handle application message
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

/*Include head files AREA*/
#include "ComUser.h"



/*Macro definition AREA*/




/*Variable declaration AREA*/


/*Function implement AREA*/
/****************************************************************************
 * @function	ComUser_MainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_MainFunction(void)
{
	ComUser_RxMainFunction();
	ComUser_TxMainFunction();
}

/****************************************************************************
 * @function	ComUser_RxMainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_RxMainFunction(void)
{

}

/****************************************************************************
 * @function	ComUser_RxMainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_TxMainFunction(void)
{

}

/*********************************File End*********************************/
