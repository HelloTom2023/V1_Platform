/****************************************************************************
* File Name : CanIf_Cfg_Define.h
*
* Modules : CAN Interface Layer configuration file
*
* Summary :	1.configuration parameters,micro define
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-26
* Description : 1.Create the file.
* 				2.Initialization Version
****************************************************************************/
#ifndef	_CANIF_CFG_DEFINE_H
#define	_CANIF_CFG_DEFINE_H

/*Include head files AREA*/
#include "..\Common\Common.h"


/*Macro definition AREA*/
#ifndef CAN
#define CAN		0
#endif

#ifndef CANFD
#define CANFD	1
#endif

/*If you use the macro define,the can message id data type shall be uint16*/
#ifndef STANDARD
#define STANDARD	(0)
#endif

/*If you use the macro define,the can message id data type shall be uint32*/
#ifndef EXPANSION
#define EXPANSION	(1)
#endif

/*the function parameters configuration*/
/*The can controller support max can channel number*/
#define CANIF_CANCONTROLLERCHANNELNUMBER					1
/*The parameters define can receive buffer number in can interface layer*/
#define CANIF_RECEIVEBUFFERNUMBER							50
/*The can controller support hardware receive buffer max number*/
#define CANIF_CONTROLLERHWBUFFERNUMBER						31
/*The can controller support can bus type.*/
#define CANIF_CONRTOLLERTYPE								CAN
/*The can interface layer can message id type.STANDARD : 11Bit, EXPANSION : 29Bit*/
#define CANIF_CANMESSAGEIDTYPE								EXPANSION
/*The can interface layer soft filter switch*/
#define CANIF_RECEIVERMESSAGESOTFFILTER						ENABLE
/*The can interface layer message DLC check switch*/
#define CANIF_RECEIVERMESSAGEDLCCHECK						ENABLE
/*Diagnostic message channel id*/
#define CANIF_DIAG_CHANNEL_ADDR								(0)
/*Diagnostic physical message id*/
#define CANIF_DIAG_PHY_ADDR									(0x7A0)
/*Diagnostic function message id*/
#define CANIF_DIAG_FUNC_ADDR								(0x7DF)
/*Network managements message channel id*/
#define CANIF_NM_CHANNEL_ADDR								(0)
/*Network managements base id*/
#define CANIF_NM_BASE_ADDR									(0x400)
/*Network managements mask code*/
#define CANIF_NM_MASK_CODE									(0x0FF)

/*can interface layer application interface enable switch*/
#define CANIF_INITCONTROLLER_API							ENABLE
#define CANIF_DEFAULTINITCONTROLLER_API						ENABLE
#define CANIF_READCONTROLLERMSGBUFFINDEX_API				ENABLE
#define CANIF_READCONTROLLERMSGBUFFDATA_API					ENABLE



/*The interface between Can Interface Layer and Can Transport Layer */
#define CANIF_CANTP_RECVNOTIFICATION_API					ENABLE





#endif /*_CANIF_CFG_DEFINE_H*/
/*********************************File End*********************************/
