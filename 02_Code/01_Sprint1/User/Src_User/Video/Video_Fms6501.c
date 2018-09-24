/**********************************************************
 * @file        Video_Fms6501.c
 * @purpose    
 * @version    0.01
 * @date        02.Feb. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          02.Feb.2013        v0.01        created
 *  
  **********************************************************/
#define VIDEO_FMS6501_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
#ifdef D_VIDEO_SWITCH_FMS6501
/* ========================= Function Announcement  =================== */


/* ========================= public variable ==================== */

/* ========================= private variable =================== */


/* ========================= Code Part =================== */

/**********************************************************
 * @function    Fms6501_CallBack_Common
 * @brief      Fms6501 Common CallBack Function
 *                 Get Result of Currently IIC Command
 * @param      uint8_t eState                    
 * @retval     Result
 **********************************************************/
uint8_t Fms6501_CallBack_Common(uint8_t eState)
{
    sFms6501.DrvResult = eState;

    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Fms6501_WriteData
 * @brief      Write Datum to Fms6501
 * @param      uint8_t *Dat: Datum except CS
 *            uint8_t Num:
 * @retval     Result
 **********************************************************/
uint8_t Fms6501_WriteData(uint8_t *Dat,uint8_t Num)
{
    uint8_t ChipSel;

    ChipSel = FMS6501_CS_ADDR;
    // Select IIC Mode to HERO Control Mode
    I2C1_SetUserMode(I2C_FMS6501_MODE);
    
    // Add Specific Datum to Buffer
    I2C1_Start();
    I2C1_SendData(&ChipSel,1,I2C_ACK,I2C_ACK); // Send Chip Address
    I2C1_SendData(Dat,Num,I2C_ACK,I2C_ACK);    // Subaddress and Datum
    I2C1_Stop();

    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Fms_WriteCommon
 * @brief         Commonly Write Datum to FMS6501, Only one Packet     
 * @param      uint8_t* Dat    
 *            uint8_t Num
 * @retval     Result
 **********************************************************/
uint8_t Fms6501_WriteCommon(uint8_t* Dat, uint8_t Num)
{
    uint8_t Result = SUBLAYER_DOING;   
    
    switch(sFms6501.DrvStep)
    {
        // Send Datum if Bus is Idle
        case OPERATION_0:
            if(BUSY == Fms6501_IIC_CheckBus())    //Check IIC Bus State
                break;
            
            Fms6501_WriteData(Dat,Num);
            sFms6501.DrvResult = TRANS_START;
            Fms6501_IIC_CallBack(Fms6501_CallBack_Common);
            sFms6501.DrvStep = OPERATION_1;
            break;

        //Check Result
        case OPERATION_1:
            if(TRANS_SUCCESS == sFms6501.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(TRANS_GENERAL_ERR == sFms6501.DrvResult)
            {
                Result = SUBLAYER_ERROR;
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Clear State while Execute Done!
    if(Result >= SUBLAYER_DONE)
    {
        sFms6501.DrvStep = OPERATION_0;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Fms6501_Update
 * @brief      Update All Fms6501's Register               
 * @param      NULL                    
 * @retval     Result
 **********************************************************/
uint8_t Fms6501_Update(void)  //disturb will never happen, no need reset paramter on other place
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t Buffer[2];

    //Update Each Out Config One By One
    switch(sFms6501.UpdateStep)
    {
        //Out1 Config: Y to Decorder
        case OPERATION_0:
            Buffer[0] = 0x01;    // Start SubAddress
            Buffer[1] = FMS_REG_OUT1;    //FMS_REG_OUT1;    
            SubResult = Fms6501_WriteCommon(Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.UpdateStep = OPERATION_1;
            }
            break;

        //Out2 Config: PB to Decorder
        case OPERATION_1:
            Buffer[0] = 0x02;    // Start SubAddress
            Buffer[1] = FMS_REG_OUT2;    //FMS_REG_OUT1;    
            SubResult = Fms6501_WriteCommon(Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.UpdateStep = OPERATION_2;
            }
            break;
            
        //Out3 Config: PR to Decorder
        case OPERATION_2:
            Buffer[0] = 0x03;    // Start SubAddress
            Buffer[1] = FMS_REG_OUT3;    //FMS_REG_OUT1;    
            SubResult = Fms6501_WriteCommon(Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.UpdateStep = OPERATION_3;
            }
            break;    

        //Out4 Config:To Decorder CVBS
        case OPERATION_3:
            Buffer[0] = 0x04;    // Start SubAddress
            Buffer[1] = FMS_REG_OUT4;    //FMS_REG_OUT1;    
            SubResult = Fms6501_WriteCommon(Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.UpdateStep = OPERATION_4;
            }
            break;

        //Out7 Config: REAR_V
        case OPERATION_4:
            Buffer[0] = 0x07;    // Start SubAddress
            Buffer[1] = FMS_REG_OUT7;    //FMS_REG_OUT1;    
            SubResult = Fms6501_WriteCommon(Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.UpdateStep = OPERATION_5;
            }
            break;

        //Out8 Config: REAR_Y/CVBS2
        case OPERATION_5:
            Buffer[0] = 0x08;    // Start SubAddress
            Buffer[1] = FMS_REG_OUT8;    //FMS_REG_OUT1;    
            SubResult = Fms6501_WriteCommon(Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.UpdateStep = OPERATION_6;
            }
            break;
            
        //Out9 Config    : REAR_U/CVBS1
        case OPERATION_6:
            Buffer[0] = 0x09;    // Start SubAddress
            Buffer[1] = FMS_REG_OUT9;    //FMS_REG_OUT1;    
            SubResult = Fms6501_WriteCommon(Buffer,2);
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.UpdateStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Error Occurs...
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sFms6501.UpdateStep = OPERATION_0;    //Reset State
    }

    return (Result);
}
/**********************************************************
 * @function    Fms6501_Update
 * @brief      Update All Fms6501's Register               
 * @param      NULL                    
 * @retval     Result
 **********************************************************/
uint8_t Fms6501_ClampBias(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[3];

    //Set All Clamp
    Buffer[0] = 0x1D;    // Start SubAddress
    Buffer[1] = 0xFF;    //Clamp1
    Buffer[2] = 0x0F;    //Clamp2
    
    Result = Fms6501_WriteCommon(Buffer,3);
    
    return (Result);
}
/**********************************************************
 * @function    Fms6501_Regsiter
 * @brief      Update All Fms6501's Register               
 * @param      NULL                    
 * @retval     Result
 **********************************************************/
uint8_t Fms6501_Regsiter(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    switch(sFms6501.Step)
    {
        //Default OUT Set
        case FMS_REGISTER_DEFAULT_OUT: 
            SubResult = Fms6501_Update();
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.Step = FMS_REGISTER_CLAMP_BIAS;
            }
            break;

        //Clamp/Bias Set
        case FMS_REGISTER_CLAMP_BIAS: 
            SubResult = Fms6501_ClampBias();
            if(SUBLAYER_DONE == SubResult)
            {
                sFms6501.Step = FMS_REGISTER_DEFAULT_OUT;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;

    }

    if(SubResult > SUBLAYER_DONE)
    {
        Result = SUBLAYER_ERROR;
        sFms6501.Step = OPERATION_0; //Reset
    }

    return (Result);
}
/**********************************************************
 * @function    Fms6501_InitVariable
 * @brief      Initialize Variable
 * @param      None                    
 * @retval     Result
 **********************************************************/
void Fms6501_InitVariable(void)
{
    //Control Parameters 
    sFms6501.Step = 0;
    sFms6501.UpdateStep = 0;
    sFms6501.DrvStep = OPERATION_0;

    //Regsiters
    FMS_REG_OUT1 = FMS_DEFAULT_OUT1;
    FMS_REG_OUT2 = FMS_DEFAULT_OUT2;
    FMS_REG_OUT3 = FMS_DEFAULT_OUT3;
    FMS_REG_OUT4 = FMS_DEFAULT_OUT4;
    FMS_REG_OUT5 = FMS_DEFAULT_OUT5;
    FMS_REG_OUT6 = FMS_DEFAULT_OUT6;
    FMS_REG_OUT7 = FMS_DEFAULT_OUT7;
    FMS_REG_OUT8 = FMS_DEFAULT_OUT8;
    FMS_REG_OUT9 = FMS_DEFAULT_OUT9;
    
    sFms6501.Ready = 0;
}
/**********************************************************
 * @function    Fms6501_GetVch
 * @brief      Transfer Logical VCH to Physical VCH of FMS6501             
 * @param      uint8_t Vch
 *            uint8_t Type
 * @retval     NULL
 **********************************************************/
void Fms6501_GetVch(uint8_t Vch, uint8_t Type)
{
    switch(Vch)
    {
        //DISC: YUV
        case VCH_DISC:
            //Set Front System route
            if((SYSTEM_ALL == Type) || ((SYSTEM_FRONT == Type)))
            {
                FMS_FRONT_Y = FMS_DVD_Y;    //Y
                FMS_FRONT_U = FMS_DVD_U;    //U
                FMS_FRONT_V = FMS_DVD_V;    //V
                FMS_FRONT_CVBS = FMS_AK_FRONT; //CVBS From AK
            }
            //Set Rear System route 
            if((SYSTEM_ALL == Type) || ((SYSTEM_REAR == Type)))
            {
            #if 1//def D_REAR_VIDEO_CVBS    //Rear System Use Cvbs Mode 
                FMS_REAR_Y = FMS_INPUT_OFF;
                FMS_REAR_CVBS1 = FMS_AK_REAR1;
                FMS_REAR_CVBS2 = FMS_AK_REAR2;
            #else
                FMS_REAR_Y = FMS_DVD_Y;    //Y
                FMS_REAR_U = FMS_DVD_U;    //U
                FMS_REAR_V = FMS_DVD_V;    //V
            #endif//D_REAR_VIDEO_CVBS
            }
            break;
    #if 0    
        //AUX2: YPBPR
        case VCH_R_AUX:
            //Set Front System route
            if((SYSTEM_ALL == Type) || (SYSTEM_FRONT == Type))
            {
                FMS_FRONT_Y = FMS_AUX2_Y;    //Y
                FMS_FRONT_U = FMS_AUX2_PB;    //U
                FMS_FRONT_V = FMS_AUX2_PR;    //V
                FMS_FRONT_CVBS = FMS_AUX2_CVBS;
            }
            //Set Rear System route 
            if((SYSTEM_ALL == Type) || (SYSTEM_REAR == Type))
            {
            #ifdef D_REAR_VIDEO_CVBS    //Rear System Use Cvbs Mode 
                FMS_REAR_Y = FMS_INPUT_OFF;
                FMS_REAR_CVBS1 = FMS_AUX2_CVBS;    //CVBS
                FMS_REAR_CVBS2 = FMS_AUX2_CVBS;    //CVBS
            #else
                FMS_REAR_Y = FMS_AUX2_Y;    //Y
                FMS_REAR_U = FMS_AUX2_PB;    //U
                FMS_REAR_V = FMS_AUX2_PR;    //V
            #endif//D_REAR_VIDEO_CVBS
            }
            break;    
    #endif
    
        //CVBS From AK
        case VCH_CDC:    //AK V1
        case VCH_IPOD:    //AK V1
        case VCH_XM:    //AK V2
        case VCH_F_AUX:    //Front Aux   AK V4
        case VCH_AUX3:
        case VCH_R_AUX:
        case VCH_DTV:    //AK V3
        case VCH_ATV:    //AK V3
            //Set Front System route
            if((SYSTEM_ALL == Type) || ((SYSTEM_FRONT == Type)))
            {
                FMS_FRONT_Y = FMS_INPUT_OFF;    //Y
                FMS_FRONT_U = FMS_INPUT_OFF;    //U
                FMS_FRONT_V = FMS_INPUT_OFF;    //V
                FMS_FRONT_CVBS = FMS_AK_FRONT; //CVBS From AK
            }
            //Set Rear System route 
            if((SYSTEM_ALL == Type) || ((SYSTEM_REAR == Type)))
            {
                FMS_REAR_Y = FMS_INPUT_OFF;
                FMS_REAR_CVBS1 = FMS_AK_REAR1;
                FMS_REAR_CVBS2 = FMS_AK_REAR2;
            }
            break;    

        //AK V6    

        default:
            //Set Front System route
            if((SYSTEM_ALL == Type) || ((SYSTEM_FRONT == Type)))
            {
                FMS_FRONT_Y = FMS_INPUT_OFF;    //Y
                FMS_FRONT_U = FMS_INPUT_OFF;    //U
                FMS_FRONT_V = FMS_INPUT_OFF;    //V
                FMS_FRONT_CVBS = FMS_INPUT_OFF; //CVBS From AK
            }
            //Set Rear System route 
            if((SYSTEM_ALL == Type) || ((SYSTEM_REAR == Type)))
            {
                FMS_REAR_Y = FMS_INPUT_OFF;
                FMS_REAR_CVBS1 = FMS_INPUT_OFF;
                FMS_REAR_CVBS2 = FMS_INPUT_OFF;
            }
            break;
    }
}
/**********************************************************
 * @function    Ak4220_SwitchVch
 * @brief      AMP startup 
 *            include: Power ,Reset, Initialize
 * @param      uint8_t Vch: Required Video Channel
 *            uint8_t Type: Required Type
 * @retval     result of execute
 **********************************************************/
uint8_t Fms6501_SwitchVch(uint8_t Vch, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    //Get System New Logic Vch Config: transfer to Physical Ch
    Fms6501_GetVch(Vch,Type);

    //Set Newly Ach
    Result = Fms6501_Update();

    return (Result);
}
#endif //D_VIDEO_SWITCH_FMS6501

