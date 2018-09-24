/**********************************************************
 * @file        Tef700x_Drv.c
 * @purpose    Functions of Tef700x Driver
 * @version    0.01
 * @date        22.Aug. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          22.Aug.2013        v0.01        created
  **********************************************************/
#define TEF700X_DRV_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= Function Announcement  =================== */
/* ========================= public variable ==================== */

/* ========================= private variable =================== */

/* ========================= Code Part =================== */


/**********************************************************
 * @function    Tef700x_CheckDrvState
 * @brief      Check Driver Control whether IDLE
 *                 Cuz,Use Same Driver Control Parameter       
 * @param      TEF700X_DRIVER_TYPE_ENUM DrvID                    
 * @retval     Driver State: IDLE,BUSY,ERROR
 **********************************************************/
uint8_t Tef700x_CheckDrvState(TEF700X_DRIVER_TYPE_ENUM DrvID)
{
    uint8_t Result = TEF700X_DRV_IDLE;

    if(TEF700X_DRV_IDLE == sTef700x.DrvState)    //Driver In Idle, New Required is Accepted
    {
        sTef700x.DrvStep = OPERATION_0;
        sTef700x.DrvID = DrvID;
        sTef700x.DrvState = TEF700X_DRV_BUSY;
    }
    else if(sTef700x.DrvID != DrvID)    //New Required DrvID is not Same as Currently Run, Drive is Busy
    {
        Result = TEF700X_DRV_BUSY;
    }
    else if(sTef700x.DrvID == DrvID)
    {
        //Time Out Error Occurs......
        if(OverTimeExpired(sTef700x.DrvOverTime))
        {
            Result = TEF700X_DRV_ERROR;
            sTef700x.DrvStep = OPERATION_0; //Clear State, Cuz...Retry...
            sTef700x.DrvID = TEF700X_IIC_IDLE;
            sTef700x.DrvState = TEF700X_DRV_IDLE;
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Tef700x_CallBack_Common
 * @brief      Tef700x Common CallBack Function
 *                 Get Result of Currently IIC Command
 * @param      uint8_t eState                    
 * @retval     Result
 **********************************************************/
uint8_t Tef700x_CallBack_Common(uint8_t Result)
{
    sTef700x.DrvResult = Result;

    return (0); //IIC Driver Use: Do not Reset IIC
}
/**********************************************************
 * @function    Tef700x_WriteCommon
 * @brief         Commonly Write Datum to Tef700x, Only one Packet     
 * @param      TEF700X_DRIVER_TYPE_ENUM PID
 *            uint8_t* Dat
 *            uint8_t Num
 * @retval     Result
 **********************************************************/
uint8_t Tef700x_WriteCommon(TEF700X_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num)
{
    TEF700X_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;
    uint8_t DrvState;
    
    //Check Driver Controller, If in Idle State, Send Command
    DrvState = Tef700x_CheckDrvState(PrivateID);    //4Not Need if Single Called 
    if(TEF700X_DRV_BUSY == DrvState) // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(TEF700X_DRV_ERROR == DrvState)    //TimeOut Error Occurs!
    {
        return (SUBLAYER_ERROR);
    }

    switch(sTef700x.DrvStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            sTef700x.DrvResult = I2C_RET_WAIT;
            Memcpy_U8(Dat,sTef700x.DrvBuff,Num);
            QueueResult = Tef700x_WritePdat(sTef700x.DrvBuff,Num,(void *)Tef700x_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                sTef700x.DrvOverTime = Tef700xDelay(T100MS);
                sTef700x.DrvStep = OPERATION_1;
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //....
            }
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sTef700x.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sTef700x.DrvResult)
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
        sTef700x.DrvState = TEF700X_DRV_IDLE;
        sTef700x.DrvStep = OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Tef700x_ReadCommon
 * @brief      Commonly read from register
 * @param      
 * @retval     result of execute
 **********************************************************/
uint8_t Tef700x_ReadCommon(uint8_t Num)
{
    TEF700X_DRIVER_TYPE_ENUM PrivateID = TEF700X_IIC_READ;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;
    uint8_t DrvState;    

    //Check Driver Control State, If Not Busy, Send Command
    DrvState = Tef700x_CheckDrvState(PrivateID);
    if(TEF700X_DRV_BUSY == DrvState) // Driver Controller Is Busy
    {
        return (SUBLAYER_DOING);
    }
    else if(TEF700X_DRV_ERROR == DrvState)    //TimeOut Error Occurs!
    {
        return (SUBLAYER_ERROR);
    }

    switch(sTef700x.DrvStep)
    {
        // Send Datum if Bus is Idle    
        case OPERATION_0:
            sTef700x.DrvResult = I2C_RET_WAIT;
            QueueResult = Tef700x_DirectReadDat(sTef700x.DrvRead,Num,(void *)Tef700x_CallBack_Common);
            if(TRUE == QueueResult) //Command Successfully Queued in IIC Buffer...
            {
                sTef700x.DrvOverTime = Tef700xDelay(T100MS);
                sTef700x.DrvStep = OPERATION_1;
            }
            else
            {    // Failed to Queue in IIC Buffer...
                //....
            }
            break;

        //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == sTef700x.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sTef700x.DrvResult)
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
        sTef700x.DrvState = TEF700X_DRV_IDLE;
        sTef700x.DrvStep = OPERATION_0;
    }
    
    return (Result);
}

