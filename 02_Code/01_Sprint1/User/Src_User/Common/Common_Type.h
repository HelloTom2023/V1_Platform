/****************************************************************************
* File Name : Common_Type.h
*
* Modules : Common Data type files.
*
* Summary : The modules suitable for all types of mcu platforms.
*           Add code portability.
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-26
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_COMMON_TYPE_H
#define	_COMMON_TYPE_H

/*Include head files AREA*/


/*Macro definition AREA*/
#ifndef NULL
#define NULL		((void*)0)
#endif

#ifndef uint8
#define uint8		unsigned char
#endif

#ifndef int8
#define int8		signed char
#endif

#ifndef uint16
#define uint16		unsigned short
#endif

#ifndef uint32
#define uint32		unsigned int
#endif

/*function return value enumeration define*/
#ifndef E_OK
#define E_OK								(0)
#endif

#ifndef E_NOT_OK
#define E_NOT_OK							(1)
#endif

#ifndef E_CANMSGDLC_ERROR
#define E_CANMSGDLC_ERROR					(2)
#endif

/*The range of parameters values is overflowed*/
#ifndef E_PARAM_RANGE_OVERFLOW
#define E_PARAM_RANGE_OVERFLOW				(3)
#endif

/*The parameters is invalid*/
#ifndef E_PARAM_INVALID
#define E_PARAM_INVALID						(4)
#endif

/*The parameters is a NULL pointer*/
#ifndef E_PARAM_NULLPTR
#define E_PARAM_NULLPTR						(5)
#endif

/*Search function result is not found*/
#ifndef E_RET_NOT_FOUND
#define E_RET_NOT_FOUND						(6)
#endif

/*Message is invalid*/
#ifndef E_MSG_INVALID
#define E_MSG_INVALID						(7)
#endif

/*Array is full*/
#ifndef E_ARRAY_FULL
#define E_ARRAY_FULL						(8)
#endif

/*Array is empty*/
#ifndef E_ARRAY_EMPTY
#define E_ARRAY_EMPTY						(9)
#endif

/*The macro indication the bus message is timeout*/
#ifndef E_MSG_TIMEOUT
#define E_MSG_TIMEOUT						(10U)
#endif

/*boolean type*/
#ifndef TRUE
#define TRUE	(1)
#endif

#ifndef FALSE
#define FALSE	(0)
#endif

#ifndef ON
#define ON		(1)
#endif

#ifndef OFF
#define OFF		(0)
#endif

#ifndef ENABLE
#define ENABLE	(1)
#endif

#ifndef DISABLE
#define DISABLE	(0)
#endif

/*bit define*/
#ifndef _BIT0_
#define _BIT0_	(0x01)
#endif

#ifndef _BIT1_
#define _BIT1_	(0x02)
#endif

#ifndef _BIT2_
#define _BIT2_	(0x04)
#endif

#ifndef _BIT3_
#define _BIT3_	(0x08)
#endif

#ifndef _BIT4_
#define _BIT4_	(0x10)
#endif

#ifndef _BIT5_
#define _BIT5_	(0x20)
#endif

#ifndef _BIT6_
#define _BIT6_	(0x40)
#endif

#ifndef _BIT7_
#define _BIT7_	(0x80)
#endif

#ifndef _BIT8_
#define _BIT8_	(0x0100)
#endif

#ifndef _BIT9_
#define _BIT9_	(0x0200)
#endif

#ifndef _BIT10_
#define _BIT10_	(0x0400)
#endif

#ifndef _BIT11_
#define _BIT11_	(0x0800)
#endif

#ifndef _BIT12_
#define _BIT12_	(0x1000)
#endif

#ifndef _BIT13_
#define _BIT13_	(0x2000)
#endif

#ifndef _BIT14_
#define _BIT14_	(0x4000)
#endif

#ifndef _BIT15_
#define _BIT15_	(0x8000)
#endif

#ifndef _BIT16_
#define _BIT16_	(0x010000)
#endif

#ifndef _BIT17_
#define _BIT17_	(0x020000)
#endif

#ifndef _BIT18_
#define _BIT18_	(0x040000)
#endif

#ifndef _BIT19_
#define _BIT19_	(0x080000)
#endif

#ifndef _BIT20_
#define _BIT20_	(0x100000)
#endif

#ifndef _BIT21_
#define _BIT21_	(0x200000)
#endif

#ifndef _BIT22_
#define _BIT22_	(0x400000)
#endif

#ifndef _BIT23_
#define _BIT23_	(0x800000)
#endif

#ifndef _BIT24_
#define _BIT24_	(0x01000000)
#endif

#ifndef _BIT25_
#define _BIT25_	(0x02000000)
#endif

#ifndef _BIT26_
#define _BIT26_	(0x04000000)
#endif

#ifndef _BIT27_
#define _BIT27_	(0x08000000)
#endif

#ifndef _BIT28_
#define _BIT28_	(0x10000000)
#endif

#ifndef _BIT29_
#define _BIT29_	(0x20000000)
#endif

#ifndef _BIT30_
#define _BIT30_	(0x40000000)
#endif

#ifndef _BIT31_
#define _BIT31_	(0x80000000)
#endif

/*bit mask define*/
#ifndef _MASK_1_BIT_
#define _MASK_1_BIT_	(0x01)
#endif

#ifndef _MASK_2_BIT_
#define _MASK_2_BIT_	(0x03)
#endif

#ifndef _MASK_3_BIT_
#define _MASK_3_BIT_	(0x07)
#endif

#ifndef _MASK_4_BIT_
#define _MASK_4_BIT_	(0x0F)
#endif

#ifndef _MASK_5_BIT_
#define _MASK_5_BIT_	(0x1F)
#endif

#ifndef _MASK_6_BIT_
#define _MASK_6_BIT_	(0x3F)
#endif

#ifndef _MASK_7_BIT_
#define _MASK_7_BIT_	(0x7F)
#endif

#ifndef _MASK_8_BIT_
#define _MASK_8_BIT_	(0xFF)
#endif

#ifndef _MASK_9_BIT_
#define _MASK_9_BIT_	(0x01FF)
#endif

#ifndef _MASK_10_BIT_
#define _MASK_10_BIT_	(0x03FF)
#endif

#ifndef _MASK_11_BIT_
#define _MASK_11_BIT_	(0x07FF)
#endif

#ifndef _MASK_12_BIT_
#define _MASK_12_BIT_	(0x0FFF)
#endif

#ifndef _MASK_13_BIT_
#define _MASK_13_BIT_	(0x1FFF)
#endif

#ifndef _MASK_14_BIT_
#define _MASK_14_BIT_	(0x3FFF)
#endif

#ifndef _MASK_15_BIT_
#define _MASK_15_BIT_	(0x7FFF)
#endif

#ifndef _MASK_16_BIT_
#define _MASK_16_BIT_	(0xFFFF)
#endif





#endif /*_COMMON_TYPE_H*/
/*********************************File End*********************************/
