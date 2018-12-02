/****************************************************************************
* File Name : DcmUser.h
*
* Modules : Diagnostic communication management application Layer head file
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-02
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_DCM_USER_H_
#define	_DCM_USER_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "DcmUser_Type.h"
#include "DcmUser_Cfg_Define.h"
#include "VFB_DcmUser.h"


/*Macro definition AREA*/
#define _DCM_USER_C_	/*define use CanTp.c*/

#ifndef _DCM_USER_C_
#define DCM_USER_EXTERN_API
#define DCM_USER_LOCAL_API
#else
#define DCM_USER_EXTERN_API extern
#define DCM_USER_LOCAL_API static
#endif /*_DCM_USER_C_*/





/*Variable Define AREA*/


/*Function declaration AREA*/


#endif /*_DCM_USER_H_*/
/*********************************File End*********************************/
