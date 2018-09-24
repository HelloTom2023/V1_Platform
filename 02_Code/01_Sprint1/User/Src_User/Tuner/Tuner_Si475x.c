/**********************************************************
 * @file        Tuner_Si475x.c
 * @purpose    Tuner Module Si475x Control Function, Tuner Driver Part
 * @version    0.01
 * @date        16.July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          16.July.2012        v0.01        created
 *  
  **********************************************************/
#define TUNER_SI475X_C
/* ========================= File include ======================= */

/* ========================= Function Announcement  =================== */

/* ========================= public variable ==================== */

/* ========================= private variable =================== */

/* ========================= Code Part =================== */


/**********************************************************
 * @function    Si475x_PwrOn
 * @brief      Open Si475x Module Power Supply
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Si475x_PwrOn(void)
{
    return (SUBLAYER_DONE);    // Si475x No Power Control
}
/**********************************************************
 * @function    Si475x_Reset
 * @brief      Reset Si475x Module
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Si475x_Reset(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.SubDrvDelay))
        return;
    
    switch(sTuner.SubDrvStep)
    {
        //Set Reset Pin to Low, Active Reset Function
        case SI475X_RESET_ACTIVE:
            SubResult = Si475x_SetReset();
            if(SUBLAYER_DONE == SubResult)
            {    
                sTuner.SubDrvDelay = TunerDelay(T20MS);    // Set Delay for Reset Remain Time
                sTuner.SubDrvStep = SI475X_RESET_DEACTIVE;
            }
            break;

        //Set Reset Pin to High, Deactive Reset Function
        case SI475X_RESET_DEACTIVE:
            SubResult = Si475x_ClearReset();    
            if(SUBLAYER_DONE == SubResult)
            {
                sTuner.SubDrvDelay = TunerDelay(T20MS);    // Set Delay for Stable Delay
                sTuner.SubDrvStep = SI475X_RESET_END;
            }
            break;

        //Stable Delay Over, IIC Command is Allowed
        case SI475X_RESET_END:
            Result = SUBLAYER_DONE;
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Si475x_InitRegister
 * @brief      Initialize Si475x Registers
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Si475x_InitRegister(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t Buffer[6];

    if(DelayNotExpired(sTuner.SubDrvDelay))
        return;    
    
    switch(sTuner.SubDrvStep)
    {
        case OPERATION_0: //First POWER_UP& Delay
            Buffer[0] = 0x01;
            Buffer[0] = 0x75;
            Buffer[0] = 0x27;
            Buffer[0] = 0x07;
            Buffer[0] = 0x10;
            Buffer[0] = 0x01;
            
            break;

        case OPERATION_1: // Second POWER_UP

            break;
        
        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Si475x_ResumeLast
 * @brief      Resume Last state
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Si475x_ResumeLast(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sTuner.SubDrvDelay))
        return;    
    
    switch(sTuner.SubDrvStep)
    {

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Si475x_PowerUp
 * @brief      Power Up Si475x
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
 uint8_t Si475x_PowerUp(uint8_t Mode,uint8_t Band)
{
    SI475X_DRIVER_TYPE_ENUM PrivateID = SI475X_IIC_POWER_UP;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[6];    

    Buffer[0] = SI475X_COM_POWER_UP;    
    Buffer[1] = 0x75;    
    Buffer[2] = 0x27;    
    Buffer[3] = 0x07;    

    if(TUNER_BAND_FM)
    Buffer[4] = 0x10;    // FM Receiver
    Buffer[4] = 0x20;    // AM Receiver
    
    Buffer[5] = 0x01;    // Pre-Boot
    Buffer[5] = 0x11;    // Boot: Normal Operation    

    
    Result = Si475x_WriteCommon(PrivateID, Buffer, 2);

    return (Result);    
}
/**********************************************************
 * @function    Si475x_ConfigAudioPin
 * @brief      Config Analog Audio Pin
 * @param      None                    
 * @retval     Result of Executing
 **********************************************************/
uint8_t Si475x_ConfigAudioPin(void)
{
    SI475X_DRIVER_TYPE_ENUM PrivateID = SI475X_IIC_CONFIG_AUDIO_PIN;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[2];

    Buffer[0] = 0x1B;                    //ANA_AUDIO_PIN_CFG: SubAddress
    Buffer[1] = AUDIO_CFG_DISABLE;    //Disable Audio Output

    Result = Si475x_WriteCommon(PrivateID, Buffer, 2);

    return (Result);
}



