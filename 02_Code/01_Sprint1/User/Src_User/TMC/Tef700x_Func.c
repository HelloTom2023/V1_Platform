/**********************************************************
 * @file        Tef700x_Func.c
 * @purpose    TEF700x Control Functions
 * @version    0.01
 * @date        22. Aug. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          22.Aug.2013        v0.01        created                                                                        
  **********************************************************/
#define TEF700X_FUNC_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= Function Announcement  =================== */

/* ========================= public variable ==================== */


/* ========================= private variable =================== */



/* ========================= Code Part =================== */

/**********************************************************
 * @function    Tef700x_InitVariable
 * @brief      Initialize Variable
 * @param      None                    
 * @retval     Result
 **********************************************************/
void Tef700x_InitVariable(void)
{
    sTef700x.Step = 0;
    sTef700x.Delay = 0;

    sTef700x.DrvStep = OPERATION_0;
    sTef700x.DrvID = TEF700X_IIC_IDLE;
    sTef700x.DrvState = TEF700X_DRV_IDLE;

    sTef700x.Ready = 0;
}
/**********************************************************
 * @function    Tef700x_InitReg
 * @brief      Initialize All User Register
 * @param                  
 * @retval     Result
 **********************************************************/
uint8_t Tef700x_InitReg(void)
{
    TEF700X_DRIVER_TYPE_ENUM PrivateID = TEF700X_IIC_REGISTER;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t Buffer[7];
    
    switch(sTef700x.Step)
    {
        case OPERATION_0:
            Buffer[0] = 0x00;     //SubAddress
            Buffer[1] = 0x07;    //Automatic Inject Mode
            Buffer[2] = 0xAA;     //Frequency
            Buffer[3] = 0x02;     // Lowest AGC; BW 120Khz
            Buffer[4] = 0x01;     //MPX ADC Clock : 13.68
            Buffer[5] = 0x51;
            Buffer[6] = 0x00;

            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,7);    
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_1;
            }
            break;

    
        case OPERATION_1:
            Buffer[0] = 0x00;
            Buffer[1] = 0x05;
            Buffer[2] = 0xF0;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,3);
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_2;
            }
            break;
            
        case OPERATION_2:
            Buffer[0] = 0x05;
            Buffer[1] = 0x02;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_3;
            }
            break;

        case OPERATION_3:
            Buffer[0] = 0x0B;
            Buffer[1] = 0x20;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_4;
            }
            break;

        case OPERATION_4:
            Buffer[0] = 0x0B;
            Buffer[1] = 0x30;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_5;
            }
            break;

        case OPERATION_5:
            Buffer[0] = 0x00;
            Buffer[1] = 0x07;
            Buffer[2] = 0x30;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,3);
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_6;
            }
            break;    

        case OPERATION_6:
            Buffer[0] = 0x00;
            Buffer[1] = 0x07;
            Buffer[2] = 0xA8;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,3);
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_7;
            }
            break;    

        case OPERATION_7:
            Buffer[0] = 0x0B;
            Buffer[1] = 0x10;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_8;
            }
            break;    

        case OPERATION_8:
            Buffer[0] = 0x0B;
            Buffer[1] = 0x00;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sTef700x.Step = OPERATION_9;
            }
            break;    

        case OPERATION_9:
            Buffer[0] = 0x05;
            Buffer[1] = 0x00;
            SubResult = Tef700x_WriteCommon(PrivateID,Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                Result = SUBLAYER_DONE;
                sTef700x.Step = OPERATION_0;
            }
            break;    
    }

    //Error Occurs
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sTef700x.Step = OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Tef700x_SetFreq
 * @brief      Set Frequency
 * @param      NULL            
 * @retval     Result
 **********************************************************/
uint8_t Tef700x_SetFreq(uint16_t Freq)
{
    uint8_t Result = SUBLAYER_DOING;
    TEF700X_DRIVER_TYPE_ENUM PrivateID = TEF700X_IIC_FREQ;
    uint8_t Buffer[3];

    Buffer[0] = 0x00;
    Buffer[1] = (uint8_t)((Freq / 5) >> 8);    
    Buffer[2] = (uint8_t)((Freq / 5) & 0xFF);    

    Result = Tef700x_WriteCommon(PrivateID,Buffer,3);

    return (Result);
}
/**********************************************************
 * @function    Tef700x_FetchBlock
 * @brief      Fetch Tef700x Rds Block
 * @param      NULL            
 * @retval     Result
 **********************************************************/



