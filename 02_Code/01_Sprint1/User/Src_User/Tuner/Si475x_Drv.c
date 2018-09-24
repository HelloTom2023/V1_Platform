/**********************************************************
 * @file        Si475x_Drv.c
 * @purpose    Functions of Si475x Driver
 * @version    0.01
 * @date        26. Sep. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          26.Sep.2012        v0.01        created
 *  
  **********************************************************/
#define SI475X_DRV_C
/* ========================= File include ======================= */
#include "Si475x_Drv.h"
/* ========================= Function Announcement  =================== */

/* ========================= public variable ==================== */

/* ========================= private variable =================== */

/* ========================= Code Part =================== */




/**********************************************************
 * @function    Si475x_WriteData
 * @brief      Write Datum to Si475X, Si475X use IIC 1
 * @param      uint8_t *Dat: Datum except CS
 *            uint8_t Num:
 * @retval     Result
 **********************************************************/
uint8_t Si475x_WriteData(uint8_t *Dat,uint8_t Num)
{
    uint8_t ChipSel;

    ChipSel = SI475X_CS_ADDR;
    // Select IIC Mode
    I2C1_SetUserMode(I2C_NORMAL_MODE);
    
    // Add Specific Datum to Buffer
    I2C1_Start();
    I2C1_SendData(&ChipSel,1,I2C_ACK,I2C_ACK); // Send Chip Address
    I2C1_SendData(Dat,Num,I2C_ACK,I2C_ACK);    // Subaddress and Datum
    I2C1_Stop();
}
/**********************************************************
 * @function    Si475x_CallBack_Common
 * @brief      Si475x Common CallBack Function
 *                 Get Result of Currently IIC Command
 * @param      uint8_t eState                    
 * @retval     Result
 **********************************************************/
uint8_t Si475x_CallBack_Common(uint8_t eState)
{
    sSi475x.DrvResult = eState;

    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Ak4220_CheckDrvState
 * @brief      Check Driver Control whether IDLE
 *                 Cuz,Use Same Driver Control Parameter       
 * @param      AK4220_DRIVER_TYPE_ENUM DrvID                    
 * @retval     Driver State: IDLE,BUSY,ERROR
 **********************************************************/
uint8_t Si475x_CheckDrvState(SI475X_DRIVER_TYPE_ENUM DrvID)
{
    uint8_t Result = SI475X_DRV_IDLE;

    if(SI475X_DRV_IDLE == sSi475x.DrvState)    //Driver In Idle, New Required is Accepted
    {
        sSi475x.DrvStep = OPERATION_0;
        sSi475x.DrvID = DrvID;
        sSi475x.DrvState = AK4220_DRV_BUSY;
    }
    else if(sSi475x.DrvID != DrvID)    //New Required DrvID is not Same as Currently Run, Drive is Busy
    {
        Result = SI475X_DRV_BUSY;
    }

    return (Result);
}
/**********************************************************
 * @function    Si475x_WriteCommon
 * @brief         Commonly Write Datum to Si475x, Only one Packet     
 * @param      SI475X_DRIVER_TYPE_ENUM PID
 *            uint8_t* Dat
 *            uint8_t Num
 * @retval     Result
 **********************************************************/
uint8_t Si475x_WriteCommon(SI475X_DRIVER_TYPE_ENUM PID, uint8_t* Dat, uint8_t Num)
{
    SI475X_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;   
    
    //Check Driver Control State, If Not Busy, Send Command
    if(SI475X_DRV_BUSY == Si475x_CheckDrvState(PrivateID))
        return (SUBLAYER_DOING);

    switch(sSi475x.DrvStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            if(BUSY == Si475x_IIC_CheckBus())    //Check IIC Bus State
                break;
            
            Si475x_WriteData(Dat,Num);
            sSi475x.DrvResult = I2C_RET_WAIT;
            Si475x_IIC_CallBack(Si475x_CallBack_Common);
            sSi475x.DrvStep = OPERATION_1;
            break;

        //Check Result
        case OPERATION_1:
            if(TRANS_SUCCESS == sSi475x.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(TRANS_GENERAL_ERR == sSi475x.DrvResult)
            {
                Result = SUBLAYER_ERROR;
            }
            break;
            
        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    if((SUBLAYER_DONE == Result) || (SUBLAYER_ERROR == Result))
    {
        sSi475x.DrvState = SI475X_DRV_IDLE;
    }
    
    return (Result);
}





