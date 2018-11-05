/****************************************************************************
* File Name : Com_Cfg_Define.h
*
* Modules : communication handle server Layer configuration file
*
* Summary :	1.configuration parameters,micro define
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-20
* Description : 1.Create the file.
* 				2.Initialization Version
****************************************************************************/
#ifndef	_COM_CFG_DEFINE_H
#define	_COM_CFG_DEFINE_H

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
#define COM_CANCONTROLLERCHANNELNUMBER						1
#define COM_RXLIST_NUMBER									(Com_CanIf_GetRxListElementNumber)
#define COM_TXLIST_NUMBER									(Com_CanIf_GetTxListElementNumber)


#endif /*_COM_CFG_DEFINE_H*/
/*********************************File End*********************************/
