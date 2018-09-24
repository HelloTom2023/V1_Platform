/**********************************************************
 * @file        Ak4220_Ctl.c
 * @purpose    Functions of Ak4220 Control
 * @version    0.01
 * @date        15. Sep. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          15.Sep.2012        v0.01        created
 *  
  **********************************************************/
#define AK4220_CTL_C
/* ========================= File include ======================= */
#include "..\..\config\inc.h"
#ifdef D_SWITCH_AK4220
/* ========================= Function Announcement  =================== */
uint8_t Ak4220_Update(AK4220_DRIVER_TYPE_ENUM PID);
uint8_t Ak4220_SelChannel(uint8_t Input, uint8_t Output);
uint8_t Ak4220_GetAin(uint8_t Src);
uint8_t Ak4220_GetVin(uint8_t Src);
/* ========================= public variable ==================== */

/* ========================= private variable =================== */

#ifdef D_AUDIO_ASP_HERO
//-Logistic Ach-, -Physical Ach for Sys_Front-, -Physical Ach for Rear_Front- 
const AK4220_ACH_TAB_STRUCT Tab_AkAch_Hero[] =
{
     {(uint8_t)SRC_TYPE_F_AUX,(uint8_t)AK4220_AIN_2},
    {(uint8_t)SRC_TYPE_REAR_BOX,(uint8_t)AK4220_AIN_3},
    {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)AK4220_AIN_5},
    {(uint8_t)SRC_TYPE_TV,(uint8_t)AK4220_AIN_3},
    {(uint8_t)SRC_TYPE_DTV,(uint8_t)AK4220_AIN_3},  //Ext TV  
  {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)AK4220_AIN_2},
  {(uint8_t)SRC_TYPE_DVD,(uint8_t)AK4220_AIN_6},
   {(uint8_t)SRC_TYPE_CDBOX,(uint8_t)AK4220_AIN_6},
   {(uint8_t)SRC_TYPE_NAVI,(uint8_t)AK4220_AIN_5},
    {(uint8_t)SRC_TYPE_CAMERA,(uint8_t)AK4220_AIN_5},
    {(uint8_t)SRC_TYPE_CAR_TBOX,(uint8_t)AK4220_AIN_5},
   {(uint8_t)SRC_TYPE_AVOFF, (uint8_t)AK4220_AIN_OFF},
    
    {(uint8_t)SRC_TYPE_NUM,(uint8_t)AK4220_AIN_OFF},    //End Flag..
};
//-Logistic Vch-, -Physical Vch for Sys_Front-, -Physical Vch for Rear_Front- 
const AK4220_VCH_TAB_STRUCT Tab_AkVch_Hero[] =
{
    {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)AK4220_VIN_1},
    {(uint8_t)SRC_TYPE_IPOD_VIDEO,(uint8_t)AK4220_VIN_1},
    {(uint8_t)SRC_TYPE_MHL,(uint8_t)AK4220_VIN_1}, 
    {(uint8_t)SRC_TYPE_XM,(uint8_t)AK4220_VIN_2},
    {(uint8_t)SRC_TYPE_TV,(uint8_t)AK4220_VIN_4},
    {(uint8_t)SRC_TYPE_DTV,(uint8_t)AK4220_VIN_3},
   {(uint8_t)SRC_TYPE_DISC_AUDIO,(uint8_t)AK4220_VIN_5}, // modif jira HCS-4184  DVD Audio rear sys enable
   {(uint8_t)SRC_TYPE_DISC_VIDEO,(uint8_t)AK4220_VIN_5},
    {(uint8_t)SRC_TYPE_F_AUX,(uint8_t)AK4220_VIN_1},
   {(uint8_t)SRC_TYPE_NAVI,(uint8_t)AK4220_VIN_6},
    {(uint8_t)SRC_TYPE_AVOFF, (uint8_t)AK4220_VIN_4},
    {(uint8_t)SRC_TYPE_NUM,(uint8_t)AK4220_VIN_OFF},    //End Flag..
};
#endif//D_AUDIO_ASP_HERO

#ifdef D_AUDIO_ASP_DIRANA
//-Logistic Ach-, -Physical Ach for Sys_Front-, -Physical Ach for Rear_Front- 
const AK4220_ACH_TAB_STRUCT Tab_AkAch_D3[] =
{
#ifdef D_BT_CSR    
    {(uint8_t)SRC_TYPE_BT_PHONE,(uint8_t)AK4220_AIN_1},
#endif// D_BT_CSR   
    {(uint8_t)SRC_TYPE_NAVI_AUDIO,(uint8_t)AK4220_AIN_1},
    {(uint8_t)SRC_TYPE_APP_TONE,(uint8_t)AK4220_AIN_1},
    {(uint8_t)SRC_TYPE_VR,(uint8_t)AK4220_AIN_1},
    {(uint8_t)SRC_TYPE_IPOD_VIDEO,(uint8_t)AK4220_AIN_1},
    {(uint8_t)SRC_TYPE_F_AUX,(uint8_t)AK4220_AIN_3},    //Temporary, Actually AIN_2
    {(uint8_t)SRC_TYPE_DTV,(uint8_t)AK4220_AIN_3},
    {(uint8_t)SRC_TYPE_TV,(uint8_t)AK4220_AIN_3},
    {(uint8_t)SRC_TYPE_3G_PHONE,(uint8_t)AK4220_AIN_4},
    {(uint8_t)SRC_TYPE_XM,(uint8_t)AK4220_AIN_4},
    {(uint8_t)SRC_TYPE_CDBOX,(uint8_t)AK4220_AIN_5},
    {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)AK4220_AIN_5},    //Temporary, Actually AIN_6
    {(uint8_t)SRC_TYPE_CAR_MEDIA,(uint8_t)AK4220_AIN_6},
    {(uint8_t)SRC_TYPE_CAR_SYNC,(uint8_t)AK4220_AIN_6},
    {(uint8_t)SRC_TYPE_CAR_OnSTAR,(uint8_t)AK4220_AIN_7},
    {(uint8_t)SRC_TYPE_MHL,(uint8_t)AK4220_AIN_5},

    {(uint8_t)SRC_TYPE_NUM,(uint8_t)AK4220_AIN_OFF},    //End Flag..
};
//-Logistic Vch-, -Physical Vch for Sys_Front-, -Physical Vch for Rear_Front- 
const AK4220_VCH_TAB_STRUCT Tab_AkVch_D3[] =
{
    {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)AK4220_VIN_1},
    {(uint8_t)SRC_TYPE_IPOD_VIDEO,(uint8_t)AK4220_VIN_1},
    {(uint8_t)SRC_TYPE_XM,(uint8_t)AK4220_VIN_2},    
    {(uint8_t)SRC_TYPE_DTV,(uint8_t)AK4220_VIN_3},
    {(uint8_t)SRC_TYPE_TV,(uint8_t)AK4220_VIN_3},
    {(uint8_t)SRC_TYPE_F_AUX,(uint8_t)AK4220_VIN_4},
    {(uint8_t)SRC_TYPE_DISC_VIDEO,(uint8_t)AK4220_VIN_5},

    {(uint8_t)SRC_TYPE_NUM,(uint8_t)AK4220_VIN_OFF},    //End Flag..
};
#endif//D_AUDIO_ASP_DIRANA
/* ========================= Code Part =================== */

/**********************************************************
 * @function    Ak4220_InitVariable
 * @brief      Initialize Variable
 * @param      None                    
 * @retval     Result
 **********************************************************/
void Ak4220_InitVariable(void)
{
    sAk4220.Step = 0;
    sAk4220.Delay = 0;

    sAk4220.DrvStep = OPERATION_0;
    sAk4220.DrvID = AK4220_IIC_IDLE;
    sAk4220.DrvState = AK4220_DRV_IDLE;

    REG_DAT_PD_RST = DEFAULT_PD_RST;        
    REG_DAT_INPUT1 = DEFAULT_INPUT1;        
    REG_DAT_INPUT2 = DEFAULT_INPUT2;        
    REG_DAT_INPUT3 = DEFAULT_INPUT3;        
    REG_DAT_DET1 = DEFAULT_DET1;        
    REG_DAT_DET2 = DEFAULT_DET2;        
    REG_DAT_DET3 = DEFAULT_DET3;        
    REG_DAT_GPIO = DEFAULT_GPIO;        
    sAk4220.Ready = 0;
}
/**********************************************************
 * @function    Ak4220_OpenPower
 * @brief      Open Ak4220's Power
 *                 (Ak4220's Power is Opened default while System is running)
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_OpenPower(void)
{
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Ak4220_CheckReady
 * @brief      Get Ak4220 Ready flag
 * @param      Null
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_SetRst(void)            
{
    IO_Set(IO_IDX_AK4220_RESET,PIN_OUTPUT,VALID);    
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Ak4220_CheckReady
 * @brief      Get Ak4220 Ready flag
 * @param      Null
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_ClearRst(void)            
{
    IO_Set(IO_IDX_AK4220_RESET,PIN_OUTPUT,INVALID);    
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Ak4220_Reset
 * @brief      Reset Ak4220
 *                 (Ak4220's Reset Pin is HERO's GPIO 4)
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_Reset(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;

    if(DelayNotExpired(sAk4220.Delay))
    {
        return (SUBLAYER_DOING);
    }
    
    switch(sAk4220.Step)
    {
        //Reset Config
        case AK4220_RST_CONFIG:
            SubResult = Ak4220_ClearRst();
            if(SUBLAYER_DONE == SubResult)
            {
                sAk4220.Step = AK4220_RST_ACTIVE;
            }
            break;

        //Enable Reset ...and Delay
        case AK4220_RST_ACTIVE:
            SubResult = Ak4220_SetRst();
            if(SUBLAYER_DONE == SubResult)
            {
                sAk4220.Delay = Ak4220Delay(T10MS);
                sAk4220.Step = AK4220_RST_DEACTIVE;
            }
            break;

        //Reset Ends! Disable and a little delay
        case AK4220_RST_DEACTIVE:
            SubResult = Ak4220_ClearRst();
            if(SUBLAYER_DONE == SubResult)
            {
                sAk4220.Delay = Ak4220Delay(T10MS);
                sAk4220.Step = AK4220_RST_CHK_BUS;
            }
            break;

        //Check IIC Bus Status
        case AK4220_RST_CHK_BUS:    //Check Related IIC Task Status
            if(OS_TaskIsActive(TASK_ID_I2C2))
            {
                sAk4220.Step = AK4220_RST_CHK_DEV;
            }
            else
            {
                SubResult = OS_TaskStart(TASK_ID_I2C2);
                if(TRUE == SubResult)
                {
                    sAk4220.Step = AK4220_RST_CHK_DEV;
                }
                else
                {    //Re-Check Bus
                    sAk4220.Delay = Ak4220Delay(T50MS);
                }
            }
            break;

        //Check AK Device Status
        case AK4220_RST_CHK_DEV:
            sAk4220.DrvResult = I2C_RET_WAIT;
            QueueResult = I2C_CheckDevice(AK4220_IIC,AK4220_CS_ADDR,TRUE,(void *)Ak4220_CallBack_Common,I2C_74KBPS);    
            if(TRUE == QueueResult)  //Command Successfully Queued in IIC Buffer...
            {
                sAk4220.Step = AK4220_RST_END;    
            }
            else
            {    // Failed to Queue in IIC Buffer...  Retry Later...
                //...
                sAk4220.Step = OPERATION_0;
            }
            break;

        //Reset Ends!
        case AK4220_RST_END:
            if(I2C_RET_SUCCESS == sAk4220.DrvResult)
            {
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_ERR == sAk4220.DrvResult)
            {
                Result = SUBLAYER_ERROR;
                sAk4220.Step = OPERATION_0;
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            sAk4220.Step = OPERATION_0;
            break;
    }

    //Error Occurs...
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAk4220.Step = OPERATION_0;
    }    

    return (Result);
}
/**********************************************************
 * @function    Ak4220_Register
 * @brief      Initialize Ak4220's Registers
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_Register(void)
{
    AK4220_DRIVER_TYPE_ENUM PrivateID = AK4220_IIC_REGISTER;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[9];

    Buffer[0] = 0x00;    // Start SubAddress
    Buffer[1] = DEFAULT_PD_RST;
    Buffer[2] = DEFAULT_INPUT1;
    Buffer[3] = DEFAULT_INPUT2;
    Buffer[4] = DEFAULT_INPUT3;
    Buffer[5] = DEFAULT_DET1;
    Buffer[6] = DEFAULT_DET2;
    Buffer[7] = DEFAULT_DET3; //Detect Mode 1, Only Detect Video
    Buffer[8] = DEFAULT_GPIO;

    Result = Ak4220_WriteCommon(PrivateID,Buffer,9);
    
    if(Result == SUBLAYER_DONE)
    {
        sAk4220.Ready = 1;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Ak4220_Update
 * @brief      Update All Ak4220's Register
 *            1. Switch Channel: Audio & Video & Det Sel                         
 * @param      AK4220_DRIVER_TYPE_ENUM PID                    
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_Update(AK4220_DRIVER_TYPE_ENUM PID)
{
    AK4220_DRIVER_TYPE_ENUM PrivateID = PID;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[9];

    Buffer[0] = 0;    // Start SubAddress
    Buffer[1] = REG_DAT_PD_RST;
    Buffer[2] = REG_DAT_INPUT1;
    Buffer[3] = REG_DAT_INPUT2;
    Buffer[4] = REG_DAT_INPUT3;
    Buffer[5] = REG_DAT_DET1;
    Buffer[6] = REG_DAT_DET2;
    Buffer[7] = REG_DAT_DET3;
    Buffer[8] = REG_DAT_GPIO;

    Result = Ak4220_WriteCommon(PrivateID,Buffer,9);
    
    return (Result);
}
/**********************************************************
 * @function    Ak4220_GpioCtl
 * @brief      Control Gpio output 
 *                 Output Low, or Set to Hi-z 
 * @param      uint8_t Gpio
 *                 uint8_t Attri
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_GpioCtl(uint8_t Gpio, uint8_t Attri)
{
    AK4220_DRIVER_TYPE_ENUM PrivateID = AK4220_IIC_SET_GPIO;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Buffer[2];    
    
    if(GPIO_OUTPUT_LOW == Attri)
    {
        REG_DAT_GPIO &= ((~Attri) << Gpio); //Config "0"    to output low
    }
    else 
    {
        REG_DAT_GPIO |= (Attri << Gpio); 
    }
    Buffer[0] = AK4220_REG_GPIO;    // SubAddress
    Buffer[1] = REG_DAT_GPIO;        // Data
    
    Result = Ak4220_WriteCommon(PrivateID,Buffer,2);

    return (Result);
}
/**********************************************************
 * @function    Ak4220_SelChannel
 * @brief      Set Channel Register:Audio Channel&Video Channel           
 * @param      uint8_t Input        
 *            uint8_t Output
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_SelChannel(uint8_t Input, uint8_t Output)
{
    uint8_t Position; 

    // Parameter Check..
    if((Output > AK4220_OUT_V3) || (Output < AK4220_OUT_A1))
        return (RESULT_PARA_ERR);

    // Get Register Address
    Position = (Output % 3) + 1;

    // Set New Channel Selection
    if(Output > AK4220_OUT_A3)    //Video Channel Sel
    {
        sAk4220.RegBuff[Position] &= 0x0F;
        sAk4220.RegBuff[Position] |= (Input << 4);    
    }
    else    // Audio Channel Sel
    {
        sAk4220.RegBuff[Position] &= 0xF0;
        sAk4220.RegBuff[Position] |= Input;
    }
    
    return (RESULT_SUCCESS);
}
/**********************************************************
 * @function    Ak4220_GetAin
 * @brief      Get Physical Audio Channel 
 *            According to Required Source
 * @param      uint8_t Src                
 * @retval     Result of Audio Channel
 **********************************************************/
uint8_t Ak4220_GetAin(uint8_t Src)
{
    uint8_t Result = AK4220_AIN_OFF;
    uint8_t Temp = 0;
    AK4220_ACH_TAB_STRUCT* pTmpAch;
    
#ifdef D_AUDIO_ASP_HERO    
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        pTmpAch = (AK4220_ACH_TAB_STRUCT*)(&(Tab_AkAch_Hero[0]));
    }
#endif//D_AUDIO_ASP_HERO

#ifdef D_AUDIO_ASP_DIRANA    
    if(AUDIO_ASP_DIRANA == sAudioKeep.AspModule)
    {
        pTmpAch = (AK4220_ACH_TAB_STRUCT*)(&(Tab_AkAch_D3[0]));
    }
#endif//D_AUDIO_ASP_DIRANA

    while(SRC_TYPE_NUM != pTmpAch[Temp].DummyAch)
    {
        if(Src == pTmpAch[Temp].DummyAch)
        {
            Result = pTmpAch[Temp].ActualFront;
            break;
        }
        Temp++;
    }

    return (Result);
}
/**********************************************************
 * @function    Ak4220_GetVin
 * @brief      Get Physical Video Channel 
 *            According to Required Source
 * @param      uint8_t Src                
 * @retval     Result of Video Channel
 **********************************************************/
uint8_t Ak4220_GetVin(uint8_t Src)
{
    uint8_t Result = AK4220_VIN_OFF;
    uint8_t Temp = 0;
    AK4220_VCH_TAB_STRUCT* pTmpVch;

    if((AUDIO_ASP_HERO != sAudioKeep.AspModule) && (AUDIO_ASP_DIRANA != sAudioKeep.AspModule))
        return (Result);
    
#ifdef D_AUDIO_ASP_HERO    
    if(AUDIO_ASP_HERO == sAudioKeep.AspModule)
    {
        pTmpVch = (AK4220_VCH_TAB_STRUCT*)(&(Tab_AkVch_Hero[0]));
    }
#endif//D_AUDIO_ASP_HERO

#ifdef D_AUDIO_ASP_DIRANA    
    if(AUDIO_ASP_DIRANA == sAudioKeep.AspModule)
    {
        pTmpVch = (AK4220_VCH_TAB_STRUCT*)(&(Tab_AkVch_D3[0]));
    }
#endif//D_AUDIO_ASP_DIRANA

    while(SRC_TYPE_NUM != pTmpVch[Temp].DummyVch)
    {
        if(Src == pTmpVch[Temp].DummyVch)
        {
            Result = pTmpVch[Temp].ActualFront;
            break;
        }
        Temp++;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Ak4220_SetMixSrc
 * @brief      Set Mix Route
 * @param      uint8_t Src
 *            uint8_t Type
 * @retval     result of execute
 **********************************************************/
uint8_t Ak4220_SetMixSrc(uint8_t Src, uint8_t Type)
{
    AK4220_DRIVER_TYPE_ENUM PrivateID = AK4220_IIC_SET_MIX;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t TempAin;

    TempAin = Ak4220_GetAin(Src);

    //Get System New Logic Ach Config: transfer to Physical Ch
    Ak4220_SelChannel(TempAin, AK4220_OUT_A2);    

    //Set Newly Ach
    Result = Ak4220_Update(PrivateID);

    return (Result);
}
/**********************************************************
 * @function    Ak4220_FillAch
 * @brief      Setup Audio Input
 * @param      uint8_t FrontAch
 *            uint8_t RearAch
 * @retval     Result of execute
 **********************************************************/
void Ak4220_FillAch(uint8_t Ach, uint8_t Type)
{
    uint8_t TempAin;

    if((SYSTEM_FRONT == Type) || (SYSTEM_ALL == Type)) //Set Front System ACH
    {
        //Get Front System Physical Input Channel
        TempAin = Ak4220_GetAin(Ach);

        //Front System Channel
        Ak4220_SelChannel(TempAin, AK4220_OUT_A3);   
	#ifdef  D_CODE_FOR_JX
	 Ak4220_SelChannel(TempAin, AK4220_OUT_A2);
	 Ak4220_SelChannel(TempAin, AK4220_OUT_A1);
	 #endif
    }

    if((SYSTEM_REAR == Type) || (SYSTEM_ALL == Type))    //Set Rear System ACH
    {
        //Get Rear System Physical Input Channel
        TempAin = Ak4220_GetAin(Ach);    

        // Rear1 Audio 
        Ak4220_SelChannel(TempAin, AK4220_OUT_A2);           
        // Rear2 Audio
        Ak4220_SelChannel(TempAin, AK4220_OUT_A1);    
    }
}
/**********************************************************
 * @function    Ak4220_FillVch
 * @brief      Setup Video Input
 * @param      uint8_t Src                    
 * @retval     result of execute
 **********************************************************/
void Ak4220_FillVch(uint8_t Src, uint8_t Type)
{
    uint8_t TempVin;

    TempVin = Ak4220_GetVin(Src);
    
    if(AK4220_VIN_NA == TempVin)
    {
        return;
    }
    audio_printf(_T("Ak4220_FillVch:Src =%d, Type = %d\n",Src, Type));
    //Front System Channel
    if((SYSTEM_FRONT == Type) || (SYSTEM_ALL == Type))
    {
        // Front System Video
        Ak4220_SelChannel(TempVin, AK4220_VOUT_FRONT);    
        
        //Sel Detect Input: Set The Newly Input 
        REG_DAT_DET1 &= 0x0F;
        REG_DAT_DET1 |= (TempVin << 4);
    }

    //Rear System Channel
    if((SYSTEM_REAR == Type) || (SYSTEM_ALL == Type))
    {
        // Rear1 Video 
        Ak4220_SelChannel(TempVin, AK4220_VOUT_REAR1);        

        // Rear2 Video
        Ak4220_SelChannel(TempVin, AK4220_VOUT_REAR2);    
    }
}
/**********************************************************
 * @function    Ak4220_SwitchAch
 * @brief      Switch to Newly ACH 
 *            include: Front System and Rear System
 * @param      uint8_t Ach: Required Audio Channel
 *            uint8_t Type: Channel Type(Front or Rear)
 * @retval     Result of execute
 **********************************************************/
uint8_t Ak4220_SwitchAch(uint8_t Ach, uint8_t Type)
{
    AK4220_DRIVER_TYPE_ENUM PrivateID = AK4220_IIC_SWITCH_ACH;
    uint8_t Result = SUBLAYER_DOING;

    //Get System New Logic Ach Config: transfer to Physical Ch
    Ak4220_FillAch(Ach,Type);

    //Set Newly Ach
    Result = Ak4220_Update(PrivateID);

    return (Result);
}
/**********************************************************
 * @function    Ak4220_SwitchVch
 * @brief      Switch to Newly VCH 
 *            include: Front System and Rear System
 * @param      uint8_t Vch: Required Video Channel
 *            uint8_t Type: Required Type
 * @retval     result of execute
 **********************************************************/
uint8_t Ak4220_SwitchVch(uint8_t Vch, uint8_t Type)
{
    AK4220_DRIVER_TYPE_ENUM PrivateID = AK4220_IIC_SWITCH_VCH;
    uint8_t Result = SUBLAYER_DOING;

    //Get System New Logic Vch Config: transfer to Physical Ch
    Ak4220_FillVch(Vch,Type);

    //Set Newly Ach
    Result = Ak4220_Update(PrivateID);

    return (Result);
}
/**********************************************************
 * @function    Ak4220_CheckVideo
 * @brief      Detect Currently VCH Video State 
 * @param      Null
 * @retval     Result
 **********************************************************/
uint8_t Ak4220_CheckVideo(void)
{
    uint8_t Result;

    return (Result);
}
#endif

