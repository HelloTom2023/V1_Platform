#define _HC4053_C_
/* ========================= File include ======================= */
#include "..\config\inc.h"


const HC4053_ACH_TAB_STRUCT Tab_74hcAch_Hero[] =
{
	{(uint8_t)SRC_TYPE_F_AUX,(uint8_t)HC4053_AIN_X0_Z0},
	{(uint8_t)SRC_TYPE_DTV,(uint8_t)HC4053_AIN_X1_Z1}, 
	{(uint8_t)SRC_TYPE_CDBOX,(uint8_t)HC4053_AIN_X1_Z1}, 
	{(uint8_t)SRC_TYPE_NUM,(uint8_t)HC4053_AIN_OFF},    //End Flag..
};

/**********************************************************
 * @function    Hc4053_SwitchVch
 * @brief      4053 Vch Switch
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
uint8_t Hc4053_SwitchAch(uint8_t Ach, uint8_t Type)
{
	HC4053_ACH_TAB_STRUCT* pTmpAch;
	uint8_t  temp,length,ActualFront;

	Type = Type;
	
	pTmpAch = (HC4053_ACH_TAB_STRUCT*)(&(Tab_74hcAch_Hero[0]));
	length = sizeof(Tab_74hcAch_Hero)/sizeof(HC4053_ACH_TAB_STRUCT);
	

	for(temp = 0 ;temp < length ; temp++)	
	{
		if(Ach == pTmpAch[temp].DummyAch)
		{
			ActualFront = pTmpAch[temp].ActualFront;
			break;
		}
	}

	switch(ActualFront)
	{
		case HC4053_AIN_X0_Z0:
			IO_Set(IO_IDX_DTV_AUX_SEL, PIN_OUTPUT,INVALID); 
			break;

		case HC4053_AIN_X1_Z1:
			IO_Set(IO_IDX_DTV_AUX_SEL, PIN_OUTPUT,VALID); 
			break;
	
		default:
			break;
			
	}

	return SUBLAYER_DONE;
}

