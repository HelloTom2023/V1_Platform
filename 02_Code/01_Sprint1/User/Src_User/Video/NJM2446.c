#define _NJM2246_C_
/* ========================= File include ======================= */
#include "..\config\inc.h"

//-Logistic Vch-, -Physical Vch for Sys_Front-, -Physical Vch for Rear_Front- 
const NJM2246_VCH_TAB_STRUCT Tab_NJMVch_Hero[] =
{
/*
	{(uint8_t)SRC_TYPE_F_AUX,(uint8_t)NJM2246_VIN_1},
	{(uint8_t)SRC_TYPE_NUM,(uint8_t)NJM2246_VIN_2},//Night vision
	{(uint8_t)SRC_TYPE_DTV,(uint8_t)NJM2246_VIN_3},
	{(uint8_t)SRC_TYPE_NUM,(uint8_t)NJM2246_VIN_OFF},    //End Flag..
*/
	{(uint8_t)SRC_TYPE_DVR,(uint8_t)NJM2246_VIN_1},//{(uint8_t)SRC_TYPE_CAMERA,(uint8_t)NJM2246_VIN_1},
	{(uint8_t)SRC_TYPE_NUM,(uint8_t)NJM2246_VIN_2},//Night vision
	{(uint8_t)SRC_TYPE_REVERSE,(uint8_t)NJM2246_VIN_3},
	{(uint8_t)SRC_TYPE_NUM,(uint8_t)NJM2246_VIN_OFF},    //End Flag..	
};


/*
SW1			SW2			OUTPUT
L			L			VIN1
H			L			VIN2
L/H			H			VIN3
*/
/**********************************************************
 * @function    Njm2246_SwitchVch
 * @brief      2246 Vch Switch
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
 // 3 input video,1 output 
uint8_t Njm2246_SwitchVch(uint8_t Vch, uint8_t Type)
{

	NJM2246_VCH_TAB_STRUCT* pTmpVch;
	uint8_t  temp,length,ActualFront;

	Type = Type;
	
	pTmpVch = (NJM2246_VCH_TAB_STRUCT*)(&(Tab_NJMVch_Hero[0]));
	length = sizeof(Tab_NJMVch_Hero)/sizeof(NJM2246_VCH_TAB_STRUCT);
	

	for(temp = 0 ;temp < length ; temp++)	
	{
		if(Vch == pTmpVch[temp].DummyVch)
		{
			ActualFront = pTmpVch[temp].ActualFront;
			break;
		}
	}

	switch(ActualFront)
	{
		case NJM2246_VIN_1:
			IO_Set(IO_IDX_MCU2AV_SW1, PIN_OUTPUT,INVALID); 
			IO_Set(IO_IDX_MCU2AV_SW2, PIN_OUTPUT,INVALID); 
			break;

		case NJM2246_VIN_2:
			IO_Set(IO_IDX_MCU2AV_SW1, PIN_OUTPUT,VALID); 
			IO_Set(IO_IDX_MCU2AV_SW2, PIN_OUTPUT,INVALID); 
			break;

		case NJM2246_VIN_3:
			IO_Set(IO_IDX_MCU2AV_SW1, PIN_OUTPUT,VALID); 
			IO_Set(IO_IDX_MCU2AV_SW2, PIN_OUTPUT,VALID); 
			break;
			
		default:
			break;
			
	}

	return SUBLAYER_DONE;
}
