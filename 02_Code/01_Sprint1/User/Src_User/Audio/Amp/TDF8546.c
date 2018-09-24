/* ========================= File include ======================= */
#include "..\..\config\inc.h"
/* ========================= Function Announcement  =================== */
#ifdef D_AMP_TDF8546

#define DEFAULT_IB1 0x05//0x83
#define DEFAULT_IB2 0x77//0x47    //Default Mute
#define DEFAULT_IB3 0x10//0x00
#define DEFAULT_IB4 0x01//0x24
#define DEFAULT_IB5 0x90 //0x90   // 0x00 Disable Best Efficiency   


#define TDF8546_MUTE        0x07
#define TDF8546_UNMUTE      0x00

/**********************************************************
 * @function    TDF8546_OpenPower
 * @brief      Open  Power
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Amp_OpenPower(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    TDF8546_Reset
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

    switch(AmpCtl.Step)
    {
        //Check IIC Bus Status
        case AMP_RST_CHK_BUS:    //Check Related IIC Task Status
            if(OS_TaskIsActive(TASK_ID_I2C2))
            {
                AmpCtl.Step = AMP_RST_CHK_DEV;
            }
            else
            {
                SubResult = OS_TaskStart(TASK_ID_I2C2);
                if(TRUE == SubResult)
                {
                    AmpCtl.Step = AMP_RST_CHK_DEV;
                    AmpCtl.ChkCnt = 0;
                }
                else
                {    //Re-Check Bus
                    //AmpCtl.Delay = AmpDelay(T50MS);
                }
            }
            IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,INVALID);
            AmpCtl.Delay = AmpDelay(T20MS);
            break;

        //Check AK Device Status
        case AMP_RST_CHK_DEV:
            AmpCtl.DrvResult = I2C_RET_WAIT;
            QueueResult = I2C_CheckDevice(AMP_IIC,AMP_CS_ADDR,TRUE,(void *)Amp_CallBack_Common,I2C_74KBPS);    
            if(TRUE == QueueResult)  //Command Successfully Queued in IIC Buffer...
            {
                AmpCtl.Step = AMP_RST_END;    
            }
            else
            {    // Failed to Queue in IIC Buffer...  Retry Later...
                //...
                AmpCtl.Step = OPERATION_0;
            }
            break;

        //Reset Ends!
        case AMP_RST_END:
            if(I2C_RET_SUCCESS == AmpCtl.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == AmpCtl.DrvResult)
            {
		      AmpCtl.Step = AMP_RST_CHK_DEV;  
                    AmpCtl.Delay = AmpDelay(T20MS);
            }
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
 * @function    TDF8546_Register
 * @brief      Initialize TDF8546's Registers
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Amp_Register(void)
{
    uint8_t Result = SUBLAYER_DOING;

    AmpCtl.DrvBuff[0] = DEFAULT_IB1;
    AmpCtl.DrvBuff[1] = DEFAULT_IB2;
    AmpCtl.DrvBuff[2] = DEFAULT_IB3;
    AmpCtl.DrvBuff[3] = DEFAULT_IB4;
    AmpCtl.DrvBuff[4] = DEFAULT_IB5;

    if(MODULE_NONE == AmpCtl.Module)
    {
        return (SUBLAYER_DONE);
    }

    Result = Amp_WriteCommon(AmpCtl.DrvBuff,5);
    
    if(Result == SUBLAYER_DONE)
    {
        AmpCtl.Ready = 1;
    }
    
    return (Result);
}
/**********************************************************
 * @function    TDF8546_Mute
 * @brief      
 * @param      uint8_t Mode                    
 * @retval     Result
 **********************************************************/
uint8_t Amp_Mute(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;

    if(MUTE_OFF== Mode)
    {
     	AmpCtl.DrvBuff[1] &= (~ TDF8546_MUTE);
    }
    else
    {
     	AmpCtl.DrvBuff[1] = DEFAULT_IB2;
    }

    if(MODULE_NONE == AmpCtl.Module)
    {
        return (SUBLAYER_DONE);
    }

    Result = Amp_WriteCommon(AmpCtl.DrvBuff,5);
    
    return (Result);    
}
/**********************************************************
 * @function    TDF8546_Detect
 * @brief      Detect TDF status
 * @param    NULL                 
 * @retval     NULL
 **********************************************************/
void Amp_Detect(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }    
    
    if(DelayNotExpired(AmpCtl.Delay))
    {
        return;
    }    

    if(MODULE_NONE == AmpCtl.Module)
    {
        return;
    }

    Result = Amp_ReadCommon(5);
    if(SUBLAYER_DONE == Result)
    {
        AmpCtl.Delay = AmpDelay(T5S);
#if 1
        if(IO_Get(IO_IDX_AMP_CLIP,PIN_INPUT,TRUE))
        {
                //Clip Detected
         #ifdef UDS_ENABLE_MACRO
		 Uds_UpdateDTCStatus(DTC_ID_AMP_CLIP, DTC_AVILABILITY_MASK);
	  #endif
        }
        else
        {
	  #ifdef UDS_ENABLE_MACRO
		 Uds_UpdateDTCStatus(DTC_ID_AMP_CLIP, 0x00);
	  #endif
        }
        //Analyse TDF status data
         #ifdef UDS_ENABLE_MACRO
		 
        if((AmpCtl.DrvRead[0] & 0x30) == 0x00)
        {
		Uds_UpdateDTCStatus(DTC_ID_SPK_FL_SC, 0x00);
		Uds_UpdateDTCStatus(DTC_ID_SPK_FL_OC, 0x00);
	 }
	 else if((AmpCtl.DrvRead[0] & 0x30) == 0x20)			//open circle
        {
		Uds_UpdateDTCStatus(DTC_ID_SPK_FL_SC, 0x00);
		Uds_UpdateDTCStatus(DTC_ID_SPK_FL_OC, DTC_AVILABILITY_MASK);
	 }
	 else
	 {
		Uds_UpdateDTCStatus(DTC_ID_SPK_FL_SC, DTC_AVILABILITY_MASK);
		Uds_UpdateDTCStatus(DTC_ID_SPK_FL_OC, 0x00);
	 }

	 if((AmpCtl.DrvRead[1] & 0x30) == 0x00)
        {
		Uds_UpdateDTCStatus(DTC_ID_SPK_RR_SC, 0x00);
		Uds_UpdateDTCStatus(DTC_ID_SPK_RR_OC, 0x00);
	 }
	 else if((AmpCtl.DrvRead[1] & 0x30) == 0x20)			//open circle
        {
		Uds_UpdateDTCStatus(DTC_ID_SPK_RR_SC, 0x00);
		Uds_UpdateDTCStatus(DTC_ID_SPK_RR_OC, DTC_AVILABILITY_MASK);
	 }
	 else
	 {
		Uds_UpdateDTCStatus(DTC_ID_SPK_RR_SC, DTC_AVILABILITY_MASK);
		Uds_UpdateDTCStatus(DTC_ID_SPK_RR_OC, 0x00);
	 }

	 if((AmpCtl.DrvRead[2] & 0x30) == 0x00)
        {
		Uds_UpdateDTCStatus(DTC_ID_SPK_RL_SC, 0x00);
		Uds_UpdateDTCStatus(DTC_ID_SPK_RL_OC, 0x00);
	 }
	 else if((AmpCtl.DrvRead[2] & 0x30) == 0x20)			//open circle
        {
		Uds_UpdateDTCStatus(DTC_ID_SPK_RL_SC, 0x00);
		Uds_UpdateDTCStatus(DTC_ID_SPK_RL_OC, DTC_AVILABILITY_MASK);
	 }
	 else
	 {
		Uds_UpdateDTCStatus(DTC_ID_SPK_RL_SC, DTC_AVILABILITY_MASK);
		Uds_UpdateDTCStatus(DTC_ID_SPK_RL_OC, 0x00);
	 }

	 if((AmpCtl.DrvRead[3] & 0x30) == 0x00)
        {
		Uds_UpdateDTCStatus(DTC_ID_SPK_FR_SC, 0x00);
		Uds_UpdateDTCStatus(DTC_ID_SPK_FR_OC, 0x00);
	 }
	 else if((AmpCtl.DrvRead[3] & 0x30) == 0x20)			//open circle
        {
		Uds_UpdateDTCStatus(DTC_ID_SPK_FR_SC, 0x00);
		Uds_UpdateDTCStatus(DTC_ID_SPK_FR_OC, DTC_AVILABILITY_MASK);
	 }
	 else
	 {
		Uds_UpdateDTCStatus(DTC_ID_SPK_FR_SC, DTC_AVILABILITY_MASK);
		Uds_UpdateDTCStatus(DTC_ID_SPK_FR_OC, 0x00);
	 }
        #endif
#endif
    }
    else if(SUBLAYER_ERROR == Result)
    {
        AmpCtl.Delay = AmpDelay(T5S);
    }
}



#endif//D_AMP

