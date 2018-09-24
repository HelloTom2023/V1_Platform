/**********************************************************
 * @file        Dirana3_Drv.c
 * @purpose    Functions of Dirana Driver
 * @version    0.01
 * @date        18.Dec. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          18.Dec.2012        v0.01        created
 *  
  **********************************************************/
#define DIRANA3_DRV_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
#ifdef D_AUDIO_ASP_DIRANA
/* ========================= Function Announcement  =================== */
/* ========================= public variable ==================== */
/* ========================= private variable =================== */

/* ========================= Code Part =================== */

/**********************************************************
 * @function    Dirana_CheckDrvState
 * @brief      Check Driver Control whether IDLE
 *                 Use Same Driver Control Parameter       
 * @param      DIRANA_DRIVER_TYPE_ENUM DrvID                    
 * @retval     Driver State: IDLE,BUSY,ERROR
 **********************************************************/
uint8_t Dirana_CheckDrvState(DIRANA_DRIVER_TYPE_ENUM DrvID)
{
    uint8_t Result = DIRANA_DRV_IDLE;

    //Check Lock Flag, If Locked, can not be used, and return busy state
    if((DRV_LOCKED == sDirana.DrvLock) && (DrvID != sDirana.LockID))
    {
        return (DIRANA_DRV_BUSY);
    }

    //Check State..
    if(DIRANA_DRV_IDLE == sDirana.DrvState)    //Driver In Idle, New Required is Accepted
    {
        sDirana.DrvLayerStep = OPERATION_0;
        sDirana.DrvID = DrvID;
        sDirana.DrvState = DIRANA_DRV_BUSY;
    }
    else if(sDirana.DrvID != DrvID)    //New Required DrvID is not Same as Currently Run, Drive is Busy
    {
        Result = DIRANA_DRV_BUSY;

        //To Desert Last IIC Drv Action
        // only to sign Current Command was desert by another command 
        if(OverTimeExpired(sAudio.DrvOverTime) && OverTimeExpired(sAudio.DrvDesertTime))
        {
            sDirana.DrvLayerStep = OPERATION_0;
            sDirana.DrvID = DrvID;
            sDirana.DrvState = DIRANA_DRV_BUSY;
            Result = DIRANA_DRV_IDLE;
            
        }
    }
    else if(sDirana.DrvID == DrvID)
    {
        //Time Out Error Occurs......
        if(OverTimeExpired(sAudio.DrvOverTime))
        {
            sDirana.DrvLayerStep = OPERATION_0;  //Clear State, Cuz...Retry...
            sDirana.DrvID = DIRANA_IIC_NULL;
            sDirana.DrvState = DIRANA_DRV_IDLE;
            Result = DIRANA_DRV_ERROR;
            
        }        
    }

    //Drv Idle, Lock required,--->locked
    if(DIRANA_DRV_IDLE == Result)
    {
        if((DRV_LOCKING == sDirana.DrvLock) && (DrvID == sDirana.LockID))
        {
            sDirana.DrvLock = DRV_LOCKED;
        }
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_ClearDrvState
 * @brief      Set Driver State to IDLE when Sub Done or Sub Error
 * @param      None                    
 * @retval     None
 **********************************************************/
void Dirana_ClearDrvState(uint8_t Result)
{
    if(Result >= SUBLAYER_DONE)    //Error Or Done!
    {
        //Clear Lock Flag, if Error Occur
        if(Result > SUBLAYER_DONE)
        {
            sDirana.DrvLock = DRV_UNLOCK; //Release Drv if Error Occurs
        }
    
        sDirana.DrvState = DIRANA_DRV_IDLE;
        sDirana.DrvLayerStep = OPERATION_0;
        sDirana.DrvID = DIRANA_IIC_NULL;
    }
}
/**********************************************************
 * @function    Dirana_CallBack_Common
 * @brief      Dirana Common CallBack Function
 *                 Get Result of Currently IIC Command
 * @param      uint8_t eState                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_CallBack_Common(uint8_t Result)
{
    sDirana.I2cResult = Result;

    //add restriction for advance audio IIC driver speed
    if(sDirana.DrvID < DIRANA_IIC_AUDIO_END)
    {
        //OS_EventPost(TASK_ID_AUDIO,EVT_AUDIO_CALLBACK);
    }

    return (0); //IIC Drive Use :Do Not Reset IIC
}
#endif//D_AUDIO_ASP_DIRANA

