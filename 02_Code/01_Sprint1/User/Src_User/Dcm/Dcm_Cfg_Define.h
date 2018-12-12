/****************************************************************************
* File Name : Dcm_Cfg_Define.h
*
* Modules : Diagnostic communication management layer configuration file
*
* Summary :	1.configuration parameters,micro define
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-02
* Description : 1.Create the file.
* 				2.Initialization Version
****************************************************************************/
#ifndef	_DCM_CFG_DEFINE_H_
#define	_DCM_CFG_DEFINE_H_

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "Dcm_Type.h"

/*Macro definition AREA*/
/*
 * Define P2Server and P2*Server parameters
 * used for diagnostic session control service and NRC78 timer
 * */
#define DCM_SESSION_P2SM_0		(500)
#define DCM_SESSION_P2ESM_0		(5000)
#define DCM_SESSION_P2SM_1		(25)
#define DCM_SESSION_P2ESM_1		(2000)
#define DCM_SESSION_P2SM_2		(50)
#define DCM_SESSION_P2ESM_2		(5000)
#define DCM_SESSION_P2SM_3		(0)
#define DCM_SESSION_P2ESM_3		(0)
#define DCM_SESSION_P2SM_4		(0)
#define DCM_SESSION_P2ESM_4		(0)
#define DCM_SESSION_P2SM_5		(0)
#define DCM_SESSION_P2ESM_5		(0)
#define DCM_SESSION_P2SM_6		(0)
#define DCM_SESSION_P2ESM_6		(0)
#define DCM_SESSION_P2SM_7		(0)
#define DCM_SESSION_P2ESM_7		(0)

#endif /*_DCM_CFG_DEFINE_H_*/
/*********************************File End*********************************/
