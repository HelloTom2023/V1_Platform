/****************************************************************************
* File Name : VFB_CanTp.h
*
* Modules : Virtual Function Bus base on CAN Transport Layer
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-25
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_VFB_CAN_TP_H
#define	_VFB_CAN_TP_H

/*Include head files AREA*/
#include "..\Common\Common.h"


/*Macro definition AREA*/



/*Function declaration AREA*/

/****************************************************************************
 * @function	CanTp_MemSetValue
 * @brief		set value to ptr_DestData
 * @param  		ptr_DestData :  output parameters , target data pointer
 *				Value : input parameters , needs to be set values
 *				DataLength : input parameters, data length.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
#define CanTp_MemSetValue(ptr_DestData,Value,DataLength)		CommFunc_MemSetValue(ptr_DestData,Value,DataLength)

/****************************************************************************
 * @function	CanTp_MemCopyData
 * @brief		set value to ptr_DestData
 * @param  		ptr_DestData :  output parameters , target data pointer
 *				ptr_SoureData : output parameters , source data pointer
 *				DataLength : input parameters, data length.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
#define CanTp_MemCopyData(ptr_DestData,ptr_SoureData,DataLength)		CommFunc_MemCopyData(ptr_DestData,ptr_SoureData,DataLength)





#endif /*_VFB_CAN_TP_H*/
/*********************************File End*********************************/
