/****************************************************************************
* File Name : CanTp_Cfg_Define.h
*
* Modules : CAN Transport Layer configuration file
*
* Summary :	1.configuration parameters,micro define
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-09
* Description : 1.Create the file.
* 				2.Initialization Version
****************************************************************************/
#ifndef	_CANTP_CFG_DEFINE_H
#define	_CANTP_CFG_DEFINE_H

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
/*The parameters define can receive buffer number in can transport layer*/
#define CANTP_RECEIVEBUFFERNUMBER							5
/*The can controller support can bus type.*/
#define CANTP_CONRTOLLERTYPE								CAN
/*The can transport layer can message id type.STANDARD : 11Bit, EXPANSION : 29Bit*/
#define CANTP_CANMESSAGEIDTYPE								EXPANSION


/*Diagnostic message channel id*/
#define CANTP_DIAG_CHANNEL_ADDR								(0)
/*Diagnostic physical message id*/
#define CANTP_DIAG_PHY_ADDR									(0x7A0)
/*Diagnostic function message id*/
#define CANTP_DIAG_FUNC_ADDR								(0x7DF)




#endif /*_CANTP_CFG_DEFINE_H*/
/*********************************File End*********************************/
