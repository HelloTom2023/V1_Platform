/****************************************************************************
* copyright:		JX Coagent Co.ltd.
* filename:		can_cfg.h
* Target MCU:		null
* Module:			CAN module
* Summary:		1.CAN module config file. include: CAN module, UDS on CAN, OSEK NM on CAN
*				2. user should not modify this config file. just for reference only.
*----------------------------------------------------------------------------
* Author:			zhaowenlong
* version:			
* Date:			2013-11-13
* Description:		first version
*----------------------------------------------------------------------------
* Modify:			
* version:
* Date:
* Description:
****************************************************************************/
#ifndef _CAN_CFG_H
#define _CAN_CFG_H

#include "..\CAN_Common\CommFunc.h"

typedef struct
{
	uint32_t CANMsgId;
	uint8_t Data[8];
	uint8_t CANMsgDlc;
	uint8_t CAN_Id;
}CanMsgStruct;

#define CANMSG_TYPEMASK_APP		_U16_BIT0		/*Application message */
#define CANMSG_TYPEMASK_NM		_U16_BIT1		/*OSEK NM message    */
#define CANMSG_TYPEMASK_UDS		_U16_BIT2		/*UDS Diagnostic message */

#if 1
/*if use CAN inner module,please enable the macro */
#define CAN_MODULE_ENABLE
/****************************************************************************
* name:		CAN Module version management(used for NEC V850 only)
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		CAN_131106_V01
* Description:   1. initial version, arrange the module.
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		CAN_131113_V02
* Description:   1. CANbus_NetLayer.c// modify the macro "CAN_RCV_FILTER_NUM" to 20.
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		CAN_131130_V03
* Description:   1.CANbus_DriverLayer.c // CAN Reive Filter Config,use MASK function.
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		CAN_131220_V04
* Description:   1.CANbus_AppLayer.c //debug: shutdown CAN module need shut down transceiver
*							//enter sleep mode,switch transceiver to sleep mode.
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		CAN_140323_V05
* Description:   1.CANbus_AppLayer.c //debug: bus off handler.
*			2. CANbus_DriverLayer.c//add transmit interruput. 
*			3// adjust the file structure
****************************************************************************/
#define CAN_MODULE_VERSION           "CAN_140323_V05"
#define D_CANBUS_APP_DBG_EN		0
#define D_CANBUS_NET_DBG_EN		0
#define D_CANBUS_DRV_DBG_EN		0
#define D_CANBUS_SEG_DBG_EN		0
	#if 1
#define UDS_ENABLE_MACRO
/****************************************************************************
* name:		UDS on CAN protocol stack version management
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		UDS_131113_V00
* Description:   1. initial version, arrange the UDS disanostic module.
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		UDS_140325_V01
* Description:   1. add ECUR soft reset deal.
*----------------------------------------------------------------------------
* Modify:			zhaowenlong
* version:		UDS_141027_V02
* Description:   	modify WDBI service,debug; modify RDBI bug.
****************************************************************************/
#define UDS_MODULE_VERSION           "UDS_141027_V02"
#define D_UDS_DBG_EN				0
//#define ENABLE_UDS_DTC
	#endif
	#if 0
#define NM_ENABLE_MACRO    
/****************************************************************************
* name:		OSEK Network Management(NM) protocol stack version management
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		NM_131113_V00
* Description:   1. initial version, arrange the NM OSEK module.
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		NM_140210_V01
* Description:   1. according CHANA project modify parameter. 2. modify Timing deal.
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		NM_140315_V02
* Description:  1. modify the design bug.
*----------------------------------------------------------------------------
* Modify:		zhaowenlong	
* version:		NM_140323_V03
* Description:  1. modify the transmitted handler.
****************************************************************************/
#define NM_MODULE_VERSION             "NM_140323_V03"
#define CAN_NM_DBG_EN			0
	#endif
#endif

/* Total number of CAN channel */

#define	CAN_ID0			0
#define 	CAN_ID1			1
#define	CAN_IDMAX			2

#ifndef _CAN_MODULE_C
#define CAN_EXTERN	extern
#else
#define CAN_EXTERN
#endif

#ifndef _UDS_MODULE_C
#define UDS_EXTERN 	extern 
#else
#define UDS_EXTERN 
#endif

#ifndef _NM_MODULE_C
#define NM_EXTERN	extern 
#else
#define NM_EXTERN 
#endif

#ifdef CAN_MODULE_ENABLE
#include "CAN_Module\CANbus_DriverLayer.h"
#include "CAN_Module\CANbus_NetLayer.h"
#include "CAN_Module\CANbus_AppLayer.h"
#endif


#ifdef UDS_ENABLE_MACRO
#include "CAN_UDS\Uds_Cfg.h"
#include "CAN_UDS\Uds_App.h"
#include "CAN_UDS\Uds_CAN.h"
#include "CAN_UDS\Uds_Fbl.h"
#endif


#ifdef NM_ENABLE_MACRO
#include "OSEK_NM\CAN_NM_OSEK.h"
#include "OSEK_NM\CAN_NM_interface.h"
#include"CAN_UDS\Uds_DTC.h"

#endif


#endif
/****************************************************************************
* -----------------------------END FILE---------------------------------------
****************************************************************************/


