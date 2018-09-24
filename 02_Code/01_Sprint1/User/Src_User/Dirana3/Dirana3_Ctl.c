/**********************************************************
 * @file        Dirana3_Ctl.c
 * @purpose    Dirana Control
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
#define DIRANA3_CTL_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
#ifdef D_AUDIO_ASP_DIRANA    
/* ========================= public variable ==================== */

/* ========================= private variable =================== */
//-Logistic Ach-, -Physical Ach-
static const DIRANA_ACH_TAB_STRUCT Tab_Ach_Dirana[] =
{
    {(uint8_t)SRC_TYPE_TUNER,(uint8_t)INPUT_SRC_P_RADIO},
    {(uint8_t)SRC_TYPE_RDS_TA,(uint8_t)INPUT_SRC_P_RADIO},
    {(uint8_t)SRC_TYPE_NAVI,(uint8_t)INPUT_SRC_AIN01},    
    {(uint8_t)SRC_TYPE_NAVI_AUDIO,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_APP_TONE,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_VR,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_USB,(uint8_t)INPUT_SRC_HOSTIIS6},   
    {(uint8_t)SRC_TYPE_USB_AUDIO,(uint8_t)INPUT_SRC_HOSTIIS6},
    {(uint8_t)SRC_TYPE_USB_VIDEO,(uint8_t)INPUT_SRC_HOSTIIS6},
    {(uint8_t)SRC_TYPE_SD,(uint8_t)INPUT_SRC_HOSTIIS6},    
    {(uint8_t)SRC_TYPE_SD_AUDIO,(uint8_t)INPUT_SRC_HOSTIIS6},
    {(uint8_t)SRC_TYPE_SD_VIDEO,(uint8_t)INPUT_SRC_HOSTIIS6},
    {(uint8_t)SRC_TYPE_IPOD,(uint8_t)INPUT_SRC_HOSTIIS6},    
    {(uint8_t)SRC_TYPE_IPOD_AUDIO,(uint8_t)INPUT_SRC_HOSTIIS6},
    {(uint8_t)SRC_TYPE_IPOD_VIDEO,(uint8_t)INPUT_SRC_HOSTIIS6},
    {(uint8_t)SRC_TYPE_MIRROR_LINK,(uint8_t)INPUT_SRC_HOSTIIS6},
    {(uint8_t)SRC_TYPE_DVD,(uint8_t)INPUT_SRC_SPDIF1},
    {(uint8_t)SRC_TYPE_DISC_AUDIO,(uint8_t)INPUT_SRC_SPDIF1},
    {(uint8_t)SRC_TYPE_DISC_VIDEO,(uint8_t)INPUT_SRC_SPDIF1},
#ifdef D_BT_CSR    
    {(uint8_t)SRC_TYPE_BT_MUSIC,(uint8_t)INPUT_SRC_HOSTIIS6},
    {(uint8_t)SRC_TYPE_BT_PHONE,(uint8_t)INPUT_SRC_AIN01},   
#else
    {(uint8_t)SRC_TYPE_BT_MUSIC,(uint8_t)INPUT_SRC_IIS0},
    {(uint8_t)SRC_TYPE_BT_PHONE,(uint8_t)INPUT_SRC_IIS0},   
#endif//D_BT_CSR
    {(uint8_t)SRC_TYPE_MHL,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_F_AUX,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_DTV,(uint8_t)INPUT_SRC_AIN01},   
    {(uint8_t)SRC_TYPE_3G_PHONE,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_XM,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_CAR_MEDIA,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_CAR_SYNC,(uint8_t)INPUT_SRC_AIN01},
    {(uint8_t)SRC_TYPE_CAR_OnSTAR,(uint8_t)INPUT_SRC_AIN01},

    {(uint8_t)SRC_TYPE_NUM,0x00},    //End Flag..
};

//-Logistic Ach-, -Physical Ach-
static const DIRANA_ACH_TAB_STRUCT Tab_Rach_Dirana[] =
{
    {(uint8_t)SRC_TYPE_F_AUX,(uint8_t)INPUT_SRC_AIN23},
    {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)INPUT_SRC_AIN23},
    {(uint8_t)SRC_TYPE_DTV,(uint8_t)INPUT_SRC_AIN23},   
    {(uint8_t)SRC_TYPE_DISC_VIDEO,(uint8_t)INPUT_SRC_SPDIF1},   
    {(uint8_t)SRC_TYPE_IPOD_VIDEO,(uint8_t)INPUT_SRC_HOSTIIS6},   
    
    {(uint8_t)SRC_TYPE_NUM,0x00},    //End Flag..
};
/* ========================= Code Part =================== */
/**********************************************************
 * @function    Dirana_GotoStep
 * @brief      Goto Specific Step
 * @param      uint8_t Step                    
 * @retval     None
 **********************************************************/
void Dirana_GotoStep(uint8_t Step)
{
    sAudio.AspStep = Step;
    
    sDirana.SubStep = 0;
    sDirana.ThirdLayerStep = 0;
    sDirana.DrvLayerStep = 0;
    
    //Specail Control Step Initialize    

}
/**********************************************************
 * @function    Dirana_SubGotoStep
 * @brief      Goto Specific Sublayer Step
 * @param      uint8_t Step                    
 * @retval     None
 **********************************************************/
void Dirana_SubGotoStep(uint8_t Step)
{
    sDirana.SubStep = Step;
    sDirana.ThirdLayerStep = 0;
    sDirana.DrvLayerStep = 0;

    //Specail Control Step Initialize    

}
/**********************************************************
 * @function    Dirana_InitVariable
 * @brief      Initialize Dirana's Variables
 * @param      None    
 * @retval     None
 **********************************************************/
void Dirana_InitVariable(void)
{
    sAudio.AspStep = 0;    // Dirana Control Variable
    sAudio.AspDelay = 0;

    sDirana.DrvLayerStep = 0;    // Driver Control Variable
    sDirana.DrvState = DIRANA_DRV_IDLE;
    sDirana.DrvID = DIRANA_IIC_NULL;
    sDirana.DrvLock = DRV_UNLOCK;
    sDirana.LockID = DIRANA_IIC_NULL;

    sDirana.MemTblStep = 0;
    sDirana.ScratchStep = 0;
    sDirana.InitDone = 0;
}
/**********************************************************
 * @function    Dirana_OpenPower
 * @brief      Open Dirana's Power
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Dirana_OpenPower(void)
{
    sDirana.InitDone = 0;
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Dirana_Reset
 * @brief      Reset Dirana
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Reset(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t QueueResult = FALSE;
    
    if(DelayNotExpired(sAudio.AspDelay))
    {
        return (SUBLAYER_DOING);
    }
    
    switch(sAudio.AspStep)
    {
        //Config before Reset, Config Reset Pin
        case DIRANA_RESET_CONFIG:
            sDirana.InitDone = 0;
            //Reset Pin Config:output mode
            IO_Set(IO_IDX_DSP_RESET,PIN_OUTPUT,INVALID);

            //Gpio4 Pin Config:input mode
            IO_Set(IO_IDX_D3_INIT_FLG,PIN_INPUT,VALID);
            
            sAudio.AspDelay = DiranaDelay(T4MS);
            Dirana_GotoStep(DIRANA_RESET_ACTIVE);
            break;

        // Reset Dirana
        case DIRANA_RESET_ACTIVE:
            IO_Set(IO_IDX_DSP_RESET,PIN_OUTPUT,VALID);
            sAudio.AspDelay = DiranaDelay(T300MS);    //as GUI, GUI actvie Low for 200ms
            Dirana_GotoStep(DIRANA_RESET_DEACTIVE);
            break;

        // Release Reset
        case DIRANA_RESET_DEACTIVE: //
            IO_Set(IO_IDX_DSP_RESET,PIN_OUTPUT,INVALID);
            //To start issuing boot command ,10ms is required
            sAudio.AspDelay = DiranaDelay(T10MS);
            sDirana.OverTime = DiranaDelay(T1S); //time for GPIO4 Detect overtime
            Dirana_GotoStep(DIRANA_RESET_CHK_BUS);
            break;

        //Check IIC Bus
        case DIRANA_RESET_CHK_BUS:
            if(OS_TaskIsActive(TASK_ID_I2C1))
            {
                Dirana_GotoStep(DIRANA_RESET_CHK_DEV);
            }
            else
            {
                SubResult = OS_TaskStart(TASK_ID_I2C1);
                if(TRUE == SubResult)
                {
                    Dirana_GotoStep(DIRANA_RESET_CHK_DEV);
                }
                else
                {    //Re-Check Bus
                    sAudio.AspDelay = DiranaDelay(T50MS);
                }
            }
            break;

        //Check D3 Device
        case DIRANA_RESET_CHK_DEV:
            sDirana.I2cResult = I2C_RET_WAIT;
            QueueResult = I2C_CheckDevice(DIRANA_IIC,DIRANA_CS_ADDR,TRUE,(void *)Dirana_CallBack_Common,I2C_350KBPS);    
            if(TRUE == QueueResult)  //Command Successfully Queued in IIC Buffer...
            {
                Dirana_GotoStep(DIRANA_RESET_END);
            }
            else
            {    // Failed to Queue in IIC Buffer...  Retry Later...
                //...
                sAudio.AspStep = 0;
            }
            break;

        // Reset End
        case DIRANA_RESET_END:    //Detect GPIO4, Until GPIO4 sign module idle
            if(I2C_RET_SUCCESS == sDirana.I2cResult)
            {
                sAudio.AspCheck = 0; //Asp Module Confirmed..
                if(OverTimeExpired(sDirana.OverTime))
                {
                    //Error Occurs!, Feedback to System to Display somethingggggggg
                }        
                if(VALID == (IO_Get(IO_IDX_D3_INIT_FLG,PIN_INPUT,FALSE)))
                {
                    Result = SUBLAYER_DONE;    
                }

                
            }
            else if(I2C_RET_ERR == sDirana.I2cResult)
            {
                sAudio.AspCheckCnt++;
                if(1 == sAudio.AspCheck
                   || sAudio.AspCheckCnt >sAudio.AspCheckNum)
                {
                    sAudio.AspStep = 0;
                    sAudio.AspDelay = 0;
                    sAudioKeep.AspModule = AUDIO_ASP_HERO;
                    sAudio.AspCheckCnt = 0;  
                    sAudio.AspCheckNum ++;
                }
                else
                {
                    Result = SUBLAYER_ERROR;
                    sAudio.AspStep = 0;
                    //Device Checking,
                }
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_Register
 * @brief      Initialize Dirana Specific Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Register(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sAudio.AspDelay))
    {
        return (SUBLAYER_DOING);
    }
    
    switch(sAudio.AspStep)
    {
        //Load Keycodes for Enhanced Features
        case DIRANA_REGISTER_KEYCODE:    //Should Detect GPIO4 State in this phase
            //SubResult = Dirana_Keycode(I2C_RET_WAIT);
           // if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_PATCH);
            }
            break;

        //Load Dsp Patch Datum
        case DIRANA_REGISTER_PATCH:
            SubResult = Dirana_Patch();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_IMAGE);
                sDirana.BootStep = 0; //Clear Boot Step
            }
            break;
            
        //Load Image for DSP Core and Patch
        case DIRANA_REGISTER_IMAGE://Should Detect GPIO4 State in this phase
            SubResult = Dirana_ImagePatch();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_START_APP);
            }
            break;

        //Exit Boot and Start Application    
        case DIRANA_REGISTER_START_APP:
            SubResult = Dirana_StartApp();
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.AspDelay = DiranaDelay(T60MS); //necessary for waiting D3 ready to get APPLICATION INIT
                Dirana_GotoStep(DIRANA_REGISTER_REQ_INIT);
            }
            break;

         case DIRANA_REGISTER_REQ_INIT:
            SubResult = Dirana_ReqInit(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_ALIGNMENT);
            }  
            break;

        //Initialize Alignments: AM MW WX LW
        case DIRANA_REGISTER_ALIGNMENT:
            SubResult = Dirana_Alignment(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_ADPLL0);
            }
            break;

        //Start ADPLL0    
        case DIRANA_REGISTER_ADPLL0:
            SubResult = Dirana_StartPLL0(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_ADPLL1);
            }
            break;

        //Start ADPLL1
        case DIRANA_REGISTER_ADPLL1:
            SubResult = Dirana_StartPLL1(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_GPIO);
            }
            break;

        //Initialize GPIO
        case DIRANA_REGISTER_GPIO:
            SubResult = Dirana_GpioConnect(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_SPECIAL_P);
            }
            break;

        //Fm whistle avoidance,active, other i dont know what to do..........
        case DIRANA_REGISTER_SPECIAL_P:
            SubResult = Dirana_SpecialActiveP(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_P_RADIO);
            }
            break;

        //Initialize  Primary Radio
        case DIRANA_REGISTER_P_RADIO:
            SubResult = Dirana_InitRadio(P_RADIO);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_SPECIAL_S);
            }    
            break;

        //Fm whistle avoidance,active, other i dont know what to do..........
        case DIRANA_REGISTER_SPECIAL_S:
            SubResult = Dirana_SpecialActiveS(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_S_RADIO);
            }
            break;    

        //Initialize Secondary Radio
        case DIRANA_REGISTER_S_RADIO:
            SubResult = Dirana_InitRadio(S_RADIO);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_INIT_AUDIO);
            }
            break;

        //Initial All Audio Related Registers
        case DIRANA_REGISTER_INIT_AUDIO:
            SubResult = Dirana_InitAudio();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_TEST1);
            }    
            break;

        case DIRANA_REGISTER_TEST1:    //Sel Default source
            SubResult = Dirana_SoftMute(0xFFFF,MUTE_OFF);  // Release Navi/Phone Mute...
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_TEST2);
            }    
            break;

        case DIRANA_REGISTER_TEST2:
            SubResult = Dirana_DrvSetInput(STREAM_PRIMARY,INPUT_SRC_IDLE);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_GotoStep(DIRANA_REGISTER_TEST3);
            }
            break;

        case DIRANA_REGISTER_TEST3:
            SubResult = Dirana_DrvSetInput(STREAM_SECONDARY,INPUT_SRC_IDLE);
            if(SUBLAYER_DONE == SubResult)
            {
                //SubResult = Audio_FastHardMute(MUTE_OFF);    
                //if(SUBLAYER_DONE == SubResult)
                {
                    Dirana_GotoStep(DIRANA_REGISTER_END);
                }
            }
            break;

        case DIRANA_REGISTER_END:
            sDirana.InitDone = 1;
            sAudio.AspStep = 0;
            Result = SUBLAYER_DONE;
            break;

        //Step Error Occured!
        default:
            Result = SUBLAYER_STEP_ERROR;    
            sAudio.AspStep = 0;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_Patch
 * @brief      Patch...Update
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_Patch(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sDirana.SubStep)
    {
        //Patch Tab 1
        case OPERATION_0:
            SubResult = Dirana_Patch1(I2C_RET_WAIT); 
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(OPERATION_1);
            }    
            break;

        case OPERATION_1:
            SubResult = Dirana_BootPrepare(0);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(OPERATION_2);
            }  
            break;

        //Patch Tab 2
        case OPERATION_2:
            SubResult = Dirana_Patch2(I2C_RET_WAIT); 
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(OPERATION_3);
            }    
            break;
            
        case OPERATION_3:
            SubResult = Dirana_BootPrepare(1);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(OPERATION_4);
            }  
            break;
            
        //Patch Tab3
        case OPERATION_4:
            SubResult = Dirana_Patch3(I2C_RET_WAIT); 
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(OPERATION_5);
            }    
            break;
            
        case OPERATION_5:
            SubResult = Dirana_BootPrepare(2);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(OPERATION_6);
            }  
            break;
            
        //Patch Tab4
        case OPERATION_6:
            SubResult = Dirana_Patch4(I2C_RET_WAIT); 
            if(SUBLAYER_DONE == SubResult)
            {
                Result = SUBLAYER_DONE;
                sDirana.SubStep = 0;
            }    
            break;
    }
    
    if(SUBLAYER_ERROR == SubResult)
    {
        Result = SUBLAYER_ERROR;  
        sDirana.SubStep = 0;
    }
    
    return (Result);    
}
/**********************************************************
 * @function    Dirana_InitAudio
 * @brief      Initialize Dirana Specific Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_InitAudio(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sDirana.SubStep)
    {
        //Enable Sample Rate Converter    
        case DIRANA_AUDIO_SRC:
            SubResult = Dirana_Enable_SRC();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_ASR);
            }
            break;

        //Set Audio Sample Rate and Enable AudioPower
        case DIRANA_AUDIO_ASR:
            SubResult = Dirana_Set_SampleRate(ASR_SETTING);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_XOVER);
                sAudio.XoverMask = 0xFF;
            }
            break;
            
        //Set Cross Over Setting
        case DIRANA_AUDIO_XOVER:
            SubResult = Dirana_SetCrossOver();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_CHIME);
            }
            break;

        //Chime Setting
        case DIRANA_AUDIO_CHIME:
            SubResult = Dirana_BeepInit();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_CLICKCLACK);
            }
            break;

        case DIRANA_AUDIO_CLICKCLACK:
            SubResult = Dirana_CCInit();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_PERIPHERAL);
            }
            break;

        //Graphic Spectrum AnalyZe: Not Used Yet!!
        case DIRANA_AUDIO_GSA:
            break;

        //Input/Output Peripheral Initial
        case DIRANA_AUDIO_PERIPHERAL:
            SubResult = Dirana_InitPeripheral(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_POINTER);
            }
            break;

    #if 0    // Directly Set HostIIS when Initialize Peripheral
        //Config Host IIS 
        case DIRANA_AUDIO_HOST:
            SubResult = Dirana_ConfigHostIIS(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_POINTER);
            }
            break;
    #endif
    
        //Audio Pointer Initial
        case DIRANA_AUDIO_POINTER:
            SubResult = Dirana_AudioPointer();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_SCALING);
            }
            break;

        //Scaling Strategy 
        case DIRANA_AUDIO_SCALING:
            SubResult = Dirana_ScalingInit();
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.GeqMask = 0xFFFF;    //Set Geq Mask: Inital and Set all bands!
                Dirana_SubGotoStep(DIRANA_AUDIO_GEQ);
            }
            break;

        //Compressor Expander
        case DIRANA_AUDIO_COM_EXP:
            break;
            
        //Graphic Equalizer
        case DIRANA_AUDIO_GEQ:
            SubResult = Dirana_SetGeq();
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.LoudnessMask = 0xFF;    //Set Loudness Mask: Inital and Set all!
                Dirana_SubGotoStep(DIRANA_AUDIO_LOUDNESS);
            }
            break;

        //Loudness    
        case DIRANA_AUDIO_LOUDNESS:
            SubResult = Dirana_SetLoudness();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_ULTRA_BASS);
                sAudio.UltraBassMask = 0xFF;
            }
            break;

        //Config Ultra Bass..
        case DIRANA_AUDIO_ULTRA_BASS:
            SubResult = Dirana_SetUltraBass();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_VOLUME);
            }
            break;
            
        case DIRANA_AUDIO_SOFTCLIPPER:
        case DIRANA_AUDIO_DOWNMIXER:
            break;

        //Set Volume
        case DIRANA_AUDIO_VOLUME:
            SubResult = Dirana_DrvSetVol(30,SYSTEM_REAR);  //Initialize Rear Volume
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_CH_GAIN);
            }
            break;

        //Initial Channel Gain
        case DIRANA_AUDIO_CH_GAIN:
            SubResult = Dirana_InitChannelGain();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_BF);
                sAudio.BalFadCtl = 0;
                sAudio.BalFadMask = 0xFF;
            }
            break;

        //Retrieve Last Bal&Fad
        case DIRANA_AUDIO_BF:
            SubResult = Dirana_SetBalFad();        
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_BASS);
                sAudio.DrvBassStep = OPERATION_0;
            }
            break;

        //Retrieve Bass Setting    
        case DIRANA_AUDIO_TONE:
        case DIRANA_AUDIO_BASS:    
            SubResult = Dirana_SetBass(sAudioDat.sBasic.sBass,SYSTEM_FRONT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_MID);
                sAudio.DrvMidStep = OPERATION_0;
            }
            break;

        //Retrieve Middle Setting
        case DIRANA_AUDIO_MID:
            SubResult = Dirana_SetMid(sAudioDat.sBasic.sMid,SYSTEM_FRONT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_TREBLE);
                sAudio.DrvTrebleStep = OPERATION_0;                
            }
            break;

        //Retrieve Treble Setting
        case DIRANA_AUDIO_TREBLE:
            SubResult = Dirana_SetTreble(sAudioDat.sBasic.sTreble,SYSTEM_FRONT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_DC_FILTER);
            }
            break;

        //Dc Filter~    
        case DIRANA_AUDIO_DC_FILTER:
            SubResult = Dirana_SetDcFilter(sAudioDat.sAdv.DcFilter,SYSTEM_FRONT);
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_DEEMPHASIS);
            }
            break;
            
        //HD Radio, IBOC Blend
        case DIRANA_AUDIO_IBOC:
            break;
            
        case DIRANA_AUDIO_DEEMPHASIS:
            SubResult = Dirana_Deemphasis();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_SRCSCALER);
            }
            break;

        //Source Scaling of Channel: No Need, this will load while set a newly ACH    
        case DIRANA_AUDIO_SRCSCALER:
            SubResult = Dirana_SrcScalingInit();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_PHASE_SHIFT);
                sAudio.PhaseMask = 0;
            }
            break;

        //Phase Shifter
        case DIRANA_AUDIO_PHASE_SHIFT:
            SubResult = Dirana_SetPhaseShifter();
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.DelayLineMask = 0xFF;
                sAudio.DelayCtl = 0;
                Dirana_SubGotoStep(DIRANA_AUDIO_DELAYLINE);
            }
            break;
    
        case DIRANA_AUDIO_FASTMUTE:
            break;

        //Delay Line...    
        case DIRANA_AUDIO_DELAYLINE:
            SubResult = Dirana_DelayLine();
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.SwMask = 0xFF;
                Dirana_SubGotoStep(DIRANA_AUDIO_SUBWOOFER);
            }
            break;

        //SubWoofer    
        case DIRANA_AUDIO_SUBWOOFER:
            SubResult = Dirana_SetSubwoofer();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_PHONE_NAV);
            }
            break;
            
        case DIRANA_AUDIO_LIMITER:
        case DIRANA_AUDIO_QPD:
            break; 
            
        case DIRANA_AUDIO_PHONE_NAV:
            SubResult = Dirana_NavPhoneVol(20,0);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.PeqMask[CHANNEL_FL] = 0xFFFF;
                sAudio.PeqMask[CHANNEL_FR] = 0xFFFF;
                sAudio.PeqMask[CHANNEL_RL] = 0xFFFF;
                sAudio.PeqMask[CHANNEL_RR] = 0xFFFF;
                Dirana_SubGotoStep(DIRANA_AUDIO_PEQ);
            }
            break;
            
        case DIRANA_AUDIO_GPFILTER:
            break;

        case DIRANA_AUDIO_PEQ:
            SubResult = Dirana_SetPeq();
            if(SUBLAYER_DONE == SubResult)
            {
                Dirana_SubGotoStep(DIRANA_AUDIO_END);
            }
            break;
            
        //Initial GPIO connection
        case DIRANA_AUDIO_GPIO:
            break;
            
        case DIRANA_AUDIO_END:
            Result = SUBLAYER_DONE;
            break;
            
        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    if(SUBLAYER_ERROR == SubResult)
    {
        Result = SUBLAYER_ERROR;    
    }
    
    return (Result);    
}
/**********************************************************
 * @function    Dirana_GetAin
 * @brief      Transfer Logic ACH to Physical Channel
 * @param      uint8_t Src                
 * @retval     Result
 **********************************************************/
uint8_t Dirana_GetAin(uint8_t Src, uint8_t Type)
{
    uint8_t Result = INPUT_SRC_IDLE;
    uint8_t Temp = 0;
    DIRANA_ACH_TAB_STRUCT* pTmpAch;
    
    //Input Parameter Check...

    if(SYSTEM_FRONT == Type)
    {
        pTmpAch = (DIRANA_ACH_TAB_STRUCT*)(&(Tab_Ach_Dirana[0]));
    }
    else if(SYSTEM_REAR == Type)
    {
        pTmpAch = (DIRANA_ACH_TAB_STRUCT*)(&(Tab_Rach_Dirana[0]));
    }
    
    while(SRC_TYPE_NUM != pTmpAch[Temp].DummyAch)
    {
        if(Src == pTmpAch[Temp].DummyAch)
        {
            Result = pTmpAch[Temp].ActualAch;
            break;
        }
        Temp++;
    }

    if((AUDIO_6CH_MODE == sAudioDat.sInfo.ChanModeSet) && (SYSTEM_FRONT == Type))
    {
        if((SRC_TYPE_DVD == Src) || (SRC_TYPE_DISC_AUDIO == Src) || (SRC_TYPE_DISC_VIDEO == Src))
        {
            Result |= 0x80; //Switch to 6-Ch mode
        }
    }
    
    return (Result);
}
/**********************************************************
 * @function    Dirana_SwitchAch
 * @brief      Switch ACH
 * @param      uint8_t Ach
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SwitchAch(uint8_t Ach, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t PhysicalCh = 0xFF;
    uint8_t ScalerVal = (AUDIO_SRC_SCALER_MAX / 2);

    switch(sAudio.AspAchCtl)
    {
        //Switch Front System Channel 
        case OPERATION_0:
            if((SYSTEM_FRONT == Type) || (SYSTEM_ALL == Type))
            {
                //Get Front System New Logic Ach Config: transfer to Physical Ch
                PhysicalCh = Dirana_GetAin(Ach,SYSTEM_FRONT); 
                //Switch Front System Channel
                SubResult = Dirana_SourceInputSel(STREAM_PRIMARY,PhysicalCh,0,0);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.AspAchCtl = OPERATION_1;
                sAudio.SrcInputSelStep = OPERATION_0;
            }
            break;

        //Switch Rear System Channel
        case OPERATION_1:
            if((SYSTEM_REAR == Type) || (SYSTEM_ALL == Type))
            {
                //Get Rear System New Logic Ach Config: transfer to Physical Ch
                PhysicalCh = Dirana_GetAin(Ach,SYSTEM_REAR);    

                //Switch Rear System Channel
                SubResult = Dirana_SourceInputSel(STREAM_SECONDARY,PhysicalCh,0,0);
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }

            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.AspAchCtl = OPERATION_2;
            }
            break;

        //Set Source Scaling 
        case OPERATION_2:
            if((SYSTEM_FRONT == Type) || (SYSTEM_ALL == Type))
            {
                //Get ACH's Scaling Value
                ScalerVal = Audio_GetSourceScaler(Ach);

                //Set...Newly Scaler
                SubResult = Dirana_SetSrcScaler(SYSTEM_FRONT,ScalerVal);                
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.AspAchCtl = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Dirana_SetMixSrc
 * @brief      Set Mix Source
 * @param      uint8_t Src    
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Dirana_SetMixSrc(uint8_t Src,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    if(SRC_TYPE_NAVI_AUDIO == Src) //Ain3
    {
        Result = Dirana_DrvSetInput(STREAM_NAVI,INPUT_SRC_AIN23);
    }
    else if(SRC_TYPE_BT_PHONE == Src) //IIS0
    {
   #ifdef D_BT_CSR
        Result = Dirana_DrvSetInput(STREAM_PHONE,INPUT_SRC_AIN23);
   #else
        Result = Dirana_DrvSetInput(STREAM_PHONE,INPUT_SRC_IIS0);
   #endif
    }

    return (Result);    
}
/**********************************************************
 * @function    Dirana_ConfigMix
 * @brief      Config Mix: Src, Position, Gain
 * @param      uint8_t Src    
 *            uint8_t Type        
 *            int8_t Gain
 * @retval     Result
 **********************************************************/
uint8_t Dirana_ConfigMix(uint8_t Src,uint8_t Type,int8_t Gain)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t AddOnIndex;
    int8_t TmpGain = Gain;

    if(SRC_TYPE_NAVI_AUDIO == Src) //Ain3
    {
        switch(Type)
        {
            case MIX_TYPE_FL:
                AddOnIndex = P_MIX_NAV_FL;
                break;
                
            case MIX_TYPE_FR:
                AddOnIndex = P_MIX_NAV_FR;
                break;
        #if 0        
            case MIX_TYPE_RL:
                AddOnIndex = P_MIX_NAV_RL;
                break;
                
            case MIX_TYPE_RR:
                AddOnIndex = P_MIX_NAV_RR;
                break;
        #endif        
            case MIX_TYPE_FRONT:
                AddOnIndex = P_MIX_NAV_FRONT;
                break;
        #if 1        
            case MIX_TYPE_REAR:
                AddOnIndex = P_MIX_NAV_REAR;
                break;
                
            case MIX_TYPE_ALL:
                AddOnIndex = P_MIX_NAV_ALL;
                break;
        #endif        
        }
    }
    else if(SRC_TYPE_BT_PHONE == Src) //IIS2
    {
        switch(Type)
        {
            case MIX_TYPE_FL:
                AddOnIndex = P_MIX_PHONE_FL;
                break;
                
            case MIX_TYPE_FR:
                AddOnIndex = P_MIX_PHONE_FR;
                break;
    #if 0            
            case MIX_TYPE_RL:
                AddOnIndex = P_MIX_PHONE_RL;
                break;
                
            case MIX_TYPE_RR:
                AddOnIndex = P_MIX_PHONE_RR;
                break;
     #endif           
            case MIX_TYPE_FRONT:
                AddOnIndex = P_MIX_PHONE_FRONT;
                break;
                
            case MIX_TYPE_REAR:
                AddOnIndex = P_MIX_PHONE_REAR;
                break;
                
            case MIX_TYPE_ALL:
                AddOnIndex = P_MIX_PHONE_ALL;
                break;    
        }
    }

    if(MIX_TYPE_OFF == Type)
    {
        TmpGain = -100;    //Close Mix by Set Gain to Muted!
    }
    
    Result = Dirana_DrvSuperPositionGain(DIRANA_IIC_SET_IMPOSE, AddOnIndex,TmpGain);

    return (Result);    
}


#endif//D_AUDIO_ASP_DIRANA

