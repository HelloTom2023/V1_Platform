/****************************************************************************
* File Name : VFB_Can_V850.h
*
* Modules : the file is used for can driver virtual function bus layer.
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-31
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_VFB_CAN_V850_H
#define	_VFB_CAN_V850_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "..\..\..\config\inc.h"
#include "..\CanIf\CanIf.h"


/*Macro definition AREA*/
/****************************************************************************
 * @function	Can_V850_CanIf_RecvInterruptCallback
 * @brief  		mapping to CanIf_RecvInterruptCallback function
 * @param  		ChNo: input parameters,CAN channel index.
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
#define Can_V850_CanIf_RecvInterruptCallback(ChNo)		CanIf_RecvInterruptCallback(ChNo)




#endif /*_VFB_CAN_V850_H*/
/*********************************File End*********************************/
