/****************************************************************************
* File Name : ComUser_Cfg_Define.h
*
* Modules : communication user modules configuration file
*
* Summary :	1.configuration parameters,micro define
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-26
* Description : 1.Create the file.
* 				2.Initialization Version
****************************************************************************/
#ifndef	_COM_USER_CFG_DEFINE_H
#define	_COM_USER_CFG_DEFINE_H

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
#define COM_USER_CANCONTROLLERCHANNELNUMBER						1
#define COM_USER_MESSAGE_FORMAT									(0)	/*Motorola Format*/



#endif /*_COM_USER_CFG_DEFINE_H*/
/*********************************File End*********************************/
