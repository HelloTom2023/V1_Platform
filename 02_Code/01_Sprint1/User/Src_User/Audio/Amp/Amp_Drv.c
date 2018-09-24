#include "..\..\Config\inc.h"

AMP_STRUCT AmpCtl;

/**********************************************************
 * @function    Amp_CallBack_Common
 * @brief      Amp Common CallBack Function
 *                 Get Result of Currently IIC Command
 * @param      uint8_t eState                    
 * @retval     Result
 **********************************************************/
uint8_t Amp_CallBack_Common(uint8_t Result)
{
    AmpCtl.DrvResult = Result;

    return (0); //IIC Driver Use: Do not Reset IIC
}
/**********************************************************
 * @function    TDF8546_WriteCommon
 * @brief         Commonly Write Datum to TDF8546, Only one Packet     
 * @param       uint8_t* Dat  
 *                  uint8_t Num 
 * @retval     Result
 **********************************************************/
uint8_t Amp_WriteCommon(uint8_t* pDat, uint8_t Num)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;
    
    switch(AmpCtl.DrvStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            AmpCtl.DrvResult = I2C_RET_WAIT;
            //Memcpy_U8(Dat,AmpCtl.DrvBuff,Num);
            QueueResult = Amp_WritePdat(pDat,Num,(void *)Amp_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                AmpCtl.DrvOverTime = AmpDelay(T100MS);
                AmpCtl.DrvStep = OPERATION_1;
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //....
            }
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == AmpCtl.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if((I2C_RET_ERR == AmpCtl.DrvResult) || (OverTimeExpired(AmpCtl.DrvOverTime)))
            {
                Result = SUBLAYER_ERROR;
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Err Occurs!
    if(Result >= SUBLAYER_DONE)
    {
        AmpCtl.DrvStep = OPERATION_0;
    }
    
    return (Result);
}
uint8_t Amp_ReadCommon(uint8_t num)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;

    switch(AmpCtl.DrvStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            AmpCtl.DrvResult = I2C_RET_WAIT;
            QueueResult = Amp_Read(AmpCtl.DrvRead,num,(void *)Amp_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                AmpCtl.DrvOverTime = AmpDelay(T100MS);
                AmpCtl.DrvStep = OPERATION_1;
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //....
            }
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == AmpCtl.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if((I2C_RET_ERR == AmpCtl.DrvResult) || (OverTimeExpired(AmpCtl.DrvOverTime)))
            {
                Result = SUBLAYER_ERROR;
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Err Occurs!
    if(Result >= SUBLAYER_DONE)
    {
        AmpCtl.DrvStep = OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Amp_InitVariable
 * @brief      Initialize Variable
 * @param      None                    
 * @retval     Result
 **********************************************************/
void Amp_InitVariable(void)
{
     AmpCtl.Ready = 0;
     AmpCtl.Step = 0;
     AmpCtl.Delay = 0;
     AmpCtl.DrvStep = 0;
}

void Amp_TimerDeal(void)
{
	if(AmpCtl.Delay)
	 	AmpCtl.Delay--;
    	if(AmpCtl.DrvOverTime)
		AmpCtl.DrvOverTime--;
}


