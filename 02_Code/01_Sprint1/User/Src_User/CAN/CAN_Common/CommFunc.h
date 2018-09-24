/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CommFunc.h
* Target MCU:		common 
* Module:
* Summary:		the common function header file
*----------------------------------------------------------------------------
* Author:			zhaowenlong
* version:			V0.1
* Date:			2013-4-20
* Description:		first version
*----------------------------------------------------------------------------
* Modify:			
* version:
* Date:
* Description:
****************************************************************************/
#ifndef  _COMMON_FUNC_H
#define _COMMON_FUNC_H

#ifndef _COMMON_FUNC_C
#define COMMFUNC_EXTERN		extern
#else
#define COMMFUNC_EXTERN
#endif

#ifndef uint8_t
#define uint8_t  unsigned char
#endif

#ifndef int8_t
#define int8_t    signed char
#endif

#ifndef uint16_t
#define uint16_t  unsigned short
#endif
#ifndef uint32_t
#define uint32_t unsigned int
#endif

#ifndef TRUE
#define TRUE       1
#endif

#ifndef FALSE
#define FALSE      0
#endif

#define _U16_BIT0				0x0001
#define _U16_BIT1				0x0002
#define _U16_BIT2				0x0004
#define _U16_BIT3				0x0008
#define _U16_BIT4				0x0010
#define _U16_BIT5				0x0020
#define _U16_BIT6				0x0040
#define _U16_BIT7				0x0080
#define _U16_BIT8				0x0100
#define _U16_BIT9				0x0200
#define _U16_BIT10			0x0400
#define _U16_BIT11			0x0800
#define _U16_BIT12			0x1000
#define _U16_BIT13			0x2000
#define _U16_BIT14			0x4000
#define _U16_BIT15			0x8000

#define _U8_BIT0				0x01
#define _U8_BIT1				0x02
#define _U8_BIT2				0x04
#define _U8_BIT3				0x08
#define _U8_BIT4				0x10
#define _U8_BIT5				0x20
#define _U8_BIT6				0x40
#define _U8_BIT7				0x80

#define TIMER_BASE			_CANBUS_TASK_TIMING_        /*2	*/
#define TIMER_10000MS                (10000/TIMER_BASE)
#define TIMER_5500MS                  (5500/TIMER_BASE)
#define TIMER_5000MS                  (5000/TIMER_BASE)
#define TIMER_4000MS                  (4000/TIMER_BASE)
#define TIMER_3000MS                  (3000/TIMER_BASE)
#define TIMER_2500MS                  (2500/TIMER_BASE)
#define TIMER_2000MS                  (2000/TIMER_BASE)
#define TIMER_1500MS                  (1500/TIMER_BASE)
#define TIMER_1000MS                  (1000/TIMER_BASE)
#define TIMER_900MS                    (900/TIMER_BASE)
#define TIMER_800MS                    (800/TIMER_BASE)
#define TIMER_750MS                    (750/TIMER_BASE)
#define TIMER_700MS                    (700/TIMER_BASE)
#define TIMER_600MS                    (600/TIMER_BASE)
#define TIMER_500MS                    (500/TIMER_BASE)
#define TIMER_400MS                    (400/TIMER_BASE)
#define TIMER_300MS			(300/TIMER_BASE)
#define TIMER_260MS                    (260/TIMER_BASE)
#define TIMER_250MS                    (250/TIMER_BASE)
#define TIMER_200MS                    (200/TIMER_BASE)
#define TIMER_150MS			(150/TIMER_BASE)
#define TIMER_120MS                    (120/TIMER_BASE)
#define TIMER_100MS                    (100/TIMER_BASE)
#define TIMER_90MS                    	(90/TIMER_BASE)
#define TIMER_80MS                    	(80/TIMER_BASE)
#define TIMER_70MS                    	(70/TIMER_BASE)
#define TIMER_60MS                    	(60/TIMER_BASE)
#define TIMER_50MS                    	(50/TIMER_BASE)
#define TIMER_40MS			(40/TIMER_BASE)
#define TIMER_30MS			(30/TIMER_BASE)
#define TIMER_25MS                    	(25/TIMER_BASE)
#define TIMER_20MS                    	(20/TIMER_BASE)
#define TIMER_10MS                    	(10/TIMER_BASE)
#define TIMER_5MS                    	(5/TIMER_BASE)
#define TIMER_2MS                    	(2/TIMER_BASE)
#define TIMER_xMS(x)			(x/TIMER_BASE)

#define TIMER_xS(x)			(x)			/* UNIT: S */


/****************************************************************************
 * @function	MemoryCompare
 * @brief  	check two memory same or not
 * @param  	p1: point to memory 1;
 *			p2: point to memory 2;
 *			num: the num of memory size
 * @retval 	0: same; 1: different
 ****************************************************************************/
COMMFUNC_EXTERN uint8_t 	MemoryCompare(uint8_t *p1, uint8_t *p2, uint8_t num);
/****************************************************************************
 * @function	GetTheMaxValue
 * @brief  	get the max value of two values
 * @param  	value1: value 1
 *			value2: value 2
 * @retval 	the max value
 ****************************************************************************/
COMMFUNC_EXTERN uint8_t 	GetTheMaxValue(uint8_t value1, uint8_t value2);
COMMFUNC_EXTERN uint8_t 	CheckRepeatData(uint8_t *input,uint8_t len);
COMMFUNC_EXTERN void 	Memory8Copy(uint8_t *pDes, uint8_t *pSrc, uint16_t num);
COMMFUNC_EXTERN void 	FillU8Memory(uint8_t *pMemory, uint16_t len, uint8_t FillData);
COMMFUNC_EXTERN uint8_t 	CheckData_XOR(uint8_t *pData, uint8_t len);

#endif
/****************************************************************************
 * **                                        FILE END
****************************************************************************/

