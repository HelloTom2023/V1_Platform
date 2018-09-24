/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CommFunc.c
* Target MCU:		common 
* Module:
* Summary:		the common function
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
#define _COMMON_FUNC_C
#include "..\..\config\inc.h"

uint8_t MemoryCompare(uint8_t *p1, uint8_t *p2, uint8_t num)
{
	uint8_t i = 0;
	
	for(i = 0; i<num; i++)
	{
		if((*p1) != (*p2))
		{
			return 1;                 // not same
		}
		p1++;
		p2++;
	}
	return 0;                                 // same all
}

uint8_t GetTheMaxValue(uint8_t value1, uint8_t value2)
{
	if(value1 >=value2)
	{
		return value1;
	}
	else
	{
		return value2;
	}
}

void Memory8Copy(uint8_t *pDes, uint8_t *pSrc, uint16_t num)
{
	uint8_t i = 0;
	if(num == 0)
	{
		return;
	}
	for(i = 0;i<num;i++)
	{
		*pDes = *pSrc;
		pDes++;
		pSrc++;
	}
}
void FillU8Memory(uint8_t *pMemory, uint16_t len, uint8_t FillData)
{
	while(len--)
	{
		*pMemory++ = FillData;
	}
}

uint8_t CheckData_XOR(uint8_t *pData, uint8_t len)
{
	uint8_t Result = 0;
	if(len ==0)
	{
		return 0xff;
	}
	while(len--)
	{
		Result ^= *pData;
		pData++;
	}
	return Result;
}

// check result: have repeat : return 1;
//else return 0;
uint8_t CheckRepeatData(uint8_t *input,uint8_t len)
{
	uint8_t i,j;

	for(i = 0; i < len; i ++)
	{
		for(j = i+1; j < len; j ++)
		{
			if(input[i] == input[j])
			{
				return 1;
			}
		}
	}
	return 0;
}

/****************************************************************************
 * **                                        FILE END
****************************************************************************/

