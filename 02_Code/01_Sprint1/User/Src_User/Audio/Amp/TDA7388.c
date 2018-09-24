/* ========================= File include ======================= */
#include "..\..\config\inc.h"
/* ========================= Function Announcement  =================== */
#ifdef D_AMP_TDA7388
/**********************************************************
 * @function    TDA7388_OpenPower
 * @brief      Open  Power
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Amp_OpenPower(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    TDA7388_Reset
 * @brief     
 * @param      Null
 * @retval     Result
 **********************************************************/
uint8_t Amp_Reset(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;
	
    if(DelayNotExpired(AmpCtl.Delay))
    {
        return (SUBLAYER_DOING);
    }
	Result = SUBLAYER_DONE;
	
    switch(AmpCtl.Step)
    {
        case AMP_RST_CHK_BUS:    //Check Related IIC Task Status
            IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,INVALID);
            AmpCtl.Delay = AmpDelay(T20MS);
            break;

        //Check AK Device Status
        case AMP_RST_CHK_DEV:
			if(DelayNotExpired(AmpCtl.Delay))
            	AmpCtl.Step = AMP_RST_END;    
            break;

        //Reset Ends!
        case AMP_RST_END:
			IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
			 Result = SUBLAYER_DONE;
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            AmpCtl.Step = OPERATION_0;
            break;
    }
    //Error Occurs...
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        AmpCtl.Step = OPERATION_0;
    } 
    
    return (Result);
}
/**********************************************************
 * @function    TDA7388_Register
 * @brief      Initialize TDF8546's Registers
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Amp_Register(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    TDA7388_Mute
 * @brief      
 * @param      uint8_t Mode                    
 * @retval     Result
 **********************************************************/
uint8_t Amp_Mute(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;

    if(MUTE_OFF== Mode)
    {
    	IO_Set(IO_IDX_AMP_MUTE,PIN_OUTPUT,INVALID);
    }
    else
    {
    	IO_Set(IO_IDX_AMP_MUTE,PIN_OUTPUT,VALID);
    }

    Result = SUBLAYER_DONE;//snake20160815
    return (Result);    
}
/**********************************************************
 * @function    TDA7388_Detect
 * @brief      TDA7388ÎÞÕï¶Ï¹¦ÄÜ
 * @param    NULL                 
 * @retval     NULL
 **********************************************************/
void Amp_Detect(void)
{
	return;    
}


#endif




