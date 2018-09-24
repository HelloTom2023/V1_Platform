/**********************************************************
 * @file        Hero_Drv.c
 * @purpose    Functions of Hero Driver
 * @version    0.01
 * @date        30. Aug. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          30.Aug.2012        v0.01        created
 *  
  **********************************************************/
#define HERO_DRV_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
#ifdef D_AUDIO_ASP_HERO    
/* ========================= Function Announcement  =================== */
/* ========================= public variable ==================== */
/* ========================= private variable =================== */

/* ========================= Code Part =================== */

/**********************************************************
 * @function    Hero_CheckDrvState
 * @brief      Check Driver Control whether IDLE
 *                 Use Same Driver Control Parameter       
 * @param      HERO_DRIVER_TYPE_ENUM DrvID                    
 * @retval     Driver State: IDLE,BUSY,ERROR
 **********************************************************/
uint8_t Hero_CheckDrvState(HERO_DRIVER_TYPE_ENUM DrvID)
{
    uint8_t Result = HERO_DRV_IDLE;

    //Check Lock Flag, If Locked, can not be used, and return busy state
    if((DRV_LOCKED == sHero.DrvLock) && (DrvID != sHero.LockID))
    {
        return (HERO_DRV_BUSY);
    }

    if(HERO_DRV_IDLE == sHero.DrvState)    //Driver In Idle, New Required is Accepted
    {
        sHero.DrvLayerStep = OPERATION_0;
        sHero.DrvID = DrvID;
        sHero.DrvState = HERO_DRV_BUSY;
    }
    else if(sHero.DrvID != DrvID)    //New Required DrvID is not Same as Currently Run, Drive is Busy
    {
        Result = HERO_DRV_BUSY;

        //To Desert Last IIC Drv Action
        if(OverTimeExpired(sAudio.DrvOverTime) && OverTimeExpired(sAudio.DrvDesertTime))
        {
            sHero.DrvLayerStep = OPERATION_0;
            sHero.DrvID = DrvID;
            sHero.DrvState = HERO_DRV_BUSY;
            Result = HERO_DRV_IDLE;
        }
    }
    else if(sHero.DrvID == DrvID)
    {
        //Time Out Error Occurs......
        if(OverTimeExpired(sAudio.DrvOverTime))
        {
            sHero.DrvLayerStep = OPERATION_0;  //Clear State, Cuz...Retry...
            sHero.DrvID = HERO_IIC_NULL;
            sHero.DrvState = HERO_DRV_IDLE;
            Result = HERO_DRV_ERROR;
        }        
    }

    //Drv Idle, Lock required,--->locked
    if(HERO_DRV_IDLE == Result)
    {
        if((DRV_LOCKING == sHero.DrvLock) && (DrvID == sHero.LockID))
        {
            sHero.DrvLock = DRV_LOCKED;
        }
    }
    
    return (Result);
}
/**********************************************************
 * @function    Hero_ClearDrvState
 * @brief      Set Driver State to IDLE when Sub Done or Sub Error
 * @param      None                    
 * @retval     None
 **********************************************************/
void Hero_ClearDrvState(uint8_t Result)
{
    if(Result >= SUBLAYER_DONE)    //Error Or Done!
    {
        sHero.DrvState = HERO_DRV_IDLE;
        sHero.DrvLayerStep = OPERATION_0;
        sHero.DrvID = HERO_IIC_NULL;
    }
}
/**********************************************************
 * @function    Hero_CallBack_Common
 * @brief      Hero Common CallBack Function
 *                 Get Result of Currently IIC Command
 * @param      uint8_t eState                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_CallBack_Common(uint8_t eState)
{
    sHero.I2cResult = eState;
    
    //add restriction for advance audio IIC driver speed
    if(sHero.DrvID < HERO_IIC_AUDIO_END)
    {
        //OS_EventPost(TASK_ID_AUDIO,EVT_AUDIO_CALLBACK);
    }
    
    return (0); //IIC Drive Use :Do Not Reset IIC
}
#endif//D_AUDIO_ASP_HERO    

