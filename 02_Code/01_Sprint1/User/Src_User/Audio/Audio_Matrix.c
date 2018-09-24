


/**********************************************************
 * @function    Audio_GetInChannel
 * @brief      AMP startup 
 *            include: Power ,Reset, Initialize
 * @param      None                    
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_SwitchGetAin(uint8_t Src)
{
    uint8_t Result;

    //Input Parameter Check
#if 0    
    if(Src >= ACH_MAX)    
    {
        return (RESULT_PARA_ERR);
    }
#endif

    switch(Src)
    {    
        //Physical AIN 1 Config:

        //Physical AIN 2 Config:
        case ACH_TV:
        case ACH_ATV:
        //case ACH_DTV:        // Inside DTV
        case ACH_DAB:
        case ACH_2G:
        case ACH_3G:
            Result = AK4220_AIN_2;
            break;

        //Physical AIN 3 Config:
        case ACH_AUX3:    
        case ACH_DTV:        // External DTV
            Result = AK4220_AIN_3;
            break;

        //Physical AIN 4 Config:
        case ACH_XM:
        case ACH_R_AUX:
            Result = AK4220_AIN_4;
            break;

        //Physical AIN 5 Config:
        case ACH_F_AUX:
        case ACH_CDC:
            Result = AK4220_AIN_5;
            break;

        //Physical AIN 6 Config:
        case ACH_ORIG_AUX:
            Result = AK4220_AIN_6;
            break;

        //Physical AIN 7 Config:
        case ACH_ORIG_BT:
        case ACH_ONSTAR:
        case ACH_PARROT    :
            Result = AK4220_AIN_7;
            break;

        //Not Used Switch Physical Channel:
        default:
            Result = AK4220_AIN_OFF;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Audio_GetInChannel
 * @brief      AMP startup 
 *            include: Power ,Reset, Initialize
 * @param      None                    
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_SwitchGetAout(uint8_t Src)
{
    uint8_t Result;

    switch(Src)
    {    
        //Physical AOUT 1 Config:

        //Physical AOUT 2 Config:

        //Physical AOUT 3 Config:
        case ACH_TV:
        case ACH_ATV:
        case ACH_DTV:        
        case ACH_DAB:
        case ACH_2G:
        case ACH_3G:
        case ACH_AUX3:    
        case ACH_DTV:
        case ACH_XM:
        case ACH_R_AUX:
        case ACH_F_AUX:
        case ACH_CDC:    
        case ACH_ORIG_AUX:    
        case ACH_ORIG_BT:
        case ACH_ONSTAR:
        case ACH_PARROT    :    
            Result = AK4220_OUT_A3;    
            break;
        
        default:
            Result = AK4220_OUT_OFF;
            break;
    }

    return (Result);
}



