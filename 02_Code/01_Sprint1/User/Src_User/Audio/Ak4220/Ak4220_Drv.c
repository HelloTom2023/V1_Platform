/**********************************************************
 * @file        Ak4220_Drv.c
 * @purpose    Functions of Ak4220 Driver
 * @version    0.01
 * @date        17. Sep. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          17.Sep.2012        v0.01        created
 *  Deefisher.Lyu        09.July.2013        v0.02    
  **********************************************************/
#define AK4220_DRV_C
/* ========================= File include ======================= */
#include "..\..\config\inc.h"
#ifdef D_SWITCH_AK4220    //Used Ak4220
/* ========================= Function Announcement  =================== */

/* ========================= public variable ==================== */

/* ========================= private variable =================== */

/* ========================= Code Part =================== */


/**********************************************************
 * @function    Ak4220_CheckDrvState
 * @brief      Check Driver Control whether IDLE
 *                 Cuz,Use Same Driver Control Parameter       
 * @param      AK4220_DRIVER_TYPE_ENUM DrvID                    
 * @retval     Driver State: IDLE,BUSY,ERROR
 **********************************************************/
uint8_t Ak4220_CheckDrvState(AK4220_DRIVER_TYPE_ENUM DrvID)
{
    uint8_t Result = AK4220_DRV_IDLE;

    if(AK4220_DRV_IDLE == sAk4220.DrvState)    //Driver In Idle, New Required is Accepted
    {
        sAk4220.DrvStep = OPERATION_0;
        sAk4220.DrvID = DrvID;
        sAk4220.DrvState = AK4220_DRV_BUSY;
    }
    else if(sAk4220.DrvID != DrvID)    //New Required DrvID is not Same as Currently Run, Drive is Busy
    {
        Result = AK4220_DRV_BUSY;
    }
    else if(sAk4220.DrvID == DrvID)
    {
        //Time Out Error Occurs......
        if(OverTimeExpired(sAk4220.DrvOverTime))
        {
            Result = AK4220_DRV_ERROR;
            sAk4220.DrvStep = OPERATION_0; //Clear State, Cuz...Retry...
            sAk4220.DrvID = AK4220_IIC_IDLE;
            sAk4220.DrvState = AK4220_DRV_IDLE;
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Ak4220_CallBack_Common
 * @brief      AK4220 Common CallBack Function
 *                 Get Result of Currently IIC Command
 * @param      uint8_t eState                    
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_CallBack_Common(uint8_t Result)
{
    sAk4220.DrvResult = Result;

    return (0); //IIC Driver Use: Do not Reset IIC
}
/**********************************************************
 * @function    Ak4220_WriteCommon
 * @brief         Commonly Write Datum to AK4220, Only one Packet     
 * @param      AK4220_DRIVER_TYPE_ENUM PID
 *            uint8_t* Dat
 *            uint8_t Num
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_WriteCommon(AK4220_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num)
{
    AK4220_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Ak4220_CheckDrvState(PrivateID);
    if(AK4220_DRV_BUSY == DrvState) // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(AK4220_DRV_ERROR == DrvState)    //TimeOut Error Occurs!
    {
        return (SUBLAYER_ERROR);
    }

    switch(sAk4220.DrvStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            sAk4220.DrvResult = I2C_RET_WAIT;
            Memcpy_U8(Dat,sAk4220.DrvBuff,Num);
            QueueResult = Ak4220_WritePdat(sAk4220.DrvBuff,Num,(void *)Ak4220_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                sAk4220.DrvOverTime = Ak4220Delay(T100MS);
                sAk4220.DrvStep = OPERATION_1;
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //....
            }
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sAk4220.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sAk4220.DrvResult)
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
        sAk4220.DrvState = AK4220_DRV_IDLE;
        sAk4220.DrvStep = OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Ak4220_ReadCommon
 * @brief      Commonly read from register
 * @param      
 * @retval     result of execute
 **********************************************************/
uint8_t Ak4220_ReadCommon(void)
{
    AK4220_DRIVER_TYPE_ENUM PrivateID = AK4220_IIC_READ;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;
    uint8_t DrvState;    

    //Check Driver Control State, If Not Busy, Send Command
    DrvState = Ak4220_CheckDrvState(PrivateID);
    if(AK4220_DRV_BUSY == DrvState) // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(AK4220_DRV_ERROR == DrvState)    //TimeOut Error Occurs!
    {
        return (SUBLAYER_ERROR);
    }

    switch(sAk4220.DrvStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            sAk4220.DrvResult = I2C_RET_WAIT;
            QueueResult = Ak4220_ReadPdat(sAk4220.DrvRead,8,(void *)Ak4220_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                sAk4220.DrvOverTime = Ak4220Delay(T100MS);
                sAk4220.DrvStep = OPERATION_1;
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //....
            }
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sAk4220.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sAk4220.DrvResult)
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
        sAk4220.DrvState = AK4220_DRV_IDLE;
        sAk4220.DrvStep = OPERATION_0;
    }
    
    return (Result);
}
#endif

