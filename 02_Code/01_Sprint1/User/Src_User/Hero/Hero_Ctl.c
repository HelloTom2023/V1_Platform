/**********************************************************
 * @file        Hero_Ctl.c
 * @purpose    Hero Control
 * @version    0.01
 * @date        24. Aug. 2012
 * @author    Deefisher.Lyu
 * @brief        
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          24.Aug.2012        v0.01        created
 *  
  **********************************************************/
#define HERO_CTL_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= public variable ==================== */
#ifdef D_AUDIO_ASP_HERO    
/* ========================= private variable =================== */

//-Logistic Ach-, -Physical Ach-
static const HERO_ACH_TAB_STRUCT Tab_Ach_Hero[] =
{
    {(uint8_t)SRC_TYPE_TUNER,(uint8_t)INPUT_SOURCE_RADIO},
    {(uint8_t)SRC_TYPE_RDS_TA,(uint8_t)INPUT_SOURCE_RADIO},
    {(uint8_t)SRC_TYPE_F_AUX,(uint8_t)INPUT_SOURCE_AIN0},   // INPUT_SOURCE_AIN0->INPUT_SOURCE_AIN1
    {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_LOGO_AUDIO,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_CAR_TBOX,(uint8_t)INPUT_SOURCE_AIN2},
    {(uint8_t)SRC_TYPE_REAR_BOX,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_XM,(uint8_t)INPUT_SOURCE_AIN0},   
    {(uint8_t)SRC_TYPE_DTV,(uint8_t)INPUT_SOURCE_AIN1},// INPUT_SOURCE_AIN0->INPUT_SOURCE_AIN1
    {(uint8_t)SRC_TYPE_CAR_CDC,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_TV,(uint8_t)INPUT_SOURCE_AIN0},///?
    {(uint8_t)SRC_TYPE_MHL,(uint8_t)INPUT_SOURCE_AIN0},    //?
    
    {(uint8_t)SRC_TYPE_NAVI,(uint8_t)INPUT_SOURCE_AIN3},
    {(uint8_t)SRC_TYPE_NAVI_AUDIO,(uint8_t)INPUT_SOURCE_AIN3},
    {(uint8_t)SRC_TYPE_APP_TONE,(uint8_t)INPUT_SOURCE_IIS1},
    
    {(uint8_t)SRC_TYPE_VR,(uint8_t)INPUT_SOURCE_IIS1}, 
    {(uint8_t)SRC_TYPE_IPOD,(uint8_t)INPUT_SOURCE_IIS1},    
    {(uint8_t)SRC_TYPE_IPOD_AUDIO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_IPOD_VIDEO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_USB,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_USB_AUDIO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_USB_VIDEO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_THIRD_APP,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_SD,(uint8_t)INPUT_SOURCE_IIS1},
    //{(uint8_t)SRC_TYPE_SD_AUDIO,(uint8_t)INPUT_SOURCE_IIS1},
    //{(uint8_t)SRC_TYPE_SD_VIDEO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_MIRROR_LINK,(uint8_t)INPUT_SOURCE_IIS1},

    {(uint8_t)SRC_TYPE_BT_MUSIC,(uint8_t)INPUT_SOURCE_IIS1},
    
    {(uint8_t)SRC_TYPE_BT_PHONE,(uint8_t)INPUT_SOURCE_IIS1}, 

    {(uint8_t)SRC_TYPE_CDBOX,(uint8_t)INPUT_SOURCE_AIN0},		// CD-BOX Audio Channel = AIN0
    {(uint8_t)SRC_TYPE_DVD,(uint8_t)INPUT_SOURCE_SPDIF},
    {(uint8_t)SRC_TYPE_DISC_AUDIO,(uint8_t)INPUT_SOURCE_SPDIF},
    {(uint8_t)SRC_TYPE_DISC_VIDEO,(uint8_t)INPUT_SOURCE_SPDIF},//marks20150811
    {(uint8_t)SRC_TYPE_CAR_MEDIA,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_CAR_SYNC,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_CAR_OnSTAR,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_3G_PHONE,(uint8_t)INPUT_SOURCE_AIN0},

    {(uint8_t)SRC_TYPE_NUM,0x00},    //End Flag..
};

//-Logistic Ach-, -Physical Ach-
static const HERO_ACH_TAB_STRUCT Tab_Rach_Hero[] =
{
    {(uint8_t)SRC_TYPE_TUNER,(uint8_t)INPUT_SOURCE_RADIO},
    {(uint8_t)SRC_TYPE_RDS_TA,(uint8_t)INPUT_SOURCE_RADIO},
    {(uint8_t)SRC_TYPE_F_AUX,(uint8_t)INPUT_SOURCE_AIN0},    
    {(uint8_t)SRC_TYPE_R_AUX,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_XM,(uint8_t)INPUT_SOURCE_AIN0},   
    {(uint8_t)SRC_TYPE_DTV,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_TV,(uint8_t)INPUT_SOURCE_AIN0},
    {(uint8_t)SRC_TYPE_MHL,(uint8_t)INPUT_SOURCE_AIN1},    
    {(uint8_t)SRC_TYPE_NAVI,(uint8_t)INPUT_SOURCE_AIN2},
    {(uint8_t)SRC_TYPE_NAVI_AUDIO,(uint8_t)INPUT_SOURCE_AIN2},
    {(uint8_t)SRC_TYPE_IPOD,(uint8_t)INPUT_SOURCE_IIS1},    
    {(uint8_t)SRC_TYPE_IPOD_AUDIO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_IPOD_VIDEO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_USB,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_USB_AUDIO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_USB_VIDEO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_SD,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_SD_AUDIO,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_SD_VIDEO,(uint8_t)INPUT_SOURCE_IIS1},
#ifdef D_BT_CSR    
    {(uint8_t)SRC_TYPE_BT_MUSIC,(uint8_t)INPUT_SOURCE_IIS1},
    {(uint8_t)SRC_TYPE_BT_PHONE,(uint8_t)INPUT_SOURCE_AIN2},   
#else
    {(uint8_t)SRC_TYPE_BT_MUSIC,(uint8_t)INPUT_SOURCE_IIS2},
    {(uint8_t)SRC_TYPE_BT_PHONE,(uint8_t)INPUT_SOURCE_IIS2},   
#endif//D_BT_CSR
    {(uint8_t)SRC_TYPE_DVD,(uint8_t)INPUT_SOURCE_AIN0},//keilee20140606
    {(uint8_t)SRC_TYPE_DISC_AUDIO,(uint8_t)INPUT_SOURCE_SPDIF},
    {(uint8_t)SRC_TYPE_DISC_VIDEO,(uint8_t)INPUT_SOURCE_AIN0},//keilee20140606
    
    {(uint8_t)SRC_TYPE_NUM,0x00},    //End Flag..
};

/* ========================= Code Part =================== */

/**********************************************************
 * @function    Hero_GotoStep
 * @brief      Goto Specific Step
 * @param      uint8_t Step                    
 * @retval     None
 **********************************************************/
void Hero_GotoStep(uint8_t Step)
{
    sAudio.AspStep = Step;
    sHero.SubStep = 0;
    sHero.DrvLayerStep = 0;
    sHero.ThirdLayerStep = 0;
    
    sHero.FastMuteConfig = 0;
    sHero.LimiterFGS = 0;
}
/**********************************************************
 * @function    Hero_GotoStep
 * @brief      Goto Specific Step
 * @param      uint8_t Step                    
 * @retval     None
 **********************************************************/
void Hero_SubGotoStep(uint8_t Step)
{
    sHero.SubStep = Step;
    sHero.ThirdLayerStep = 0;
    sHero.DrvLayerStep = 0;
    sHero.FastMuteConfig = 0;
    sHero.LimiterFGS = 0;
}
/**********************************************************
 * @function    Hero_InitVariable
 * @brief      Initialize Hero's Variables
 * @param      None    
 * @retval     None
 **********************************************************/
void Hero_InitVariable(void)
{
    sAudio.AspStep = 0;    // Hero Control Variable
    sAudio.AspDelay = 0;

    sHero.DrvLayerStep = 0;    // Driver Control Variable
    sHero.DrvState = HERO_DRV_IDLE;
    sHero.DrvID = HERO_IIC_NULL;
    sHero.DrvLock = DRV_UNLOCK;
    sHero.LockID = HERO_IIC_NULL;
    
    sHero.MemTblStep = 0;
    sHero.ScratchStep = 0;
    sHero.InitDone = 0;
}
/**********************************************************
 * @function    Hero_OpenPower
 * @brief      Open Hero's Power
 *                 (HERO's Power is Opened default while System is running)
 * @param      None                    
 * @retval     Result
 **********************************************************/
uint8_t Hero_OpenPower(void)
{
    sHero.InitDone = 0;
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    Hero_Reset
 * @brief      Reset HERO
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_Reset(void)
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
        case HERO_RESET_CONFIG:
            sHero.InitDone = 0;
            IO_Set(IO_IDX_DSP_RESET,PIN_OUTPUT,INVALID);
            sAudio.AspDelay = HeroDelay(T20MS);
            Hero_GotoStep(HERO_RESET_ACTIVE);
            break;

        // Reset HERO
        case HERO_RESET_ACTIVE:
            IO_Set(IO_IDX_DSP_RESET,PIN_OUTPUT,VALID);
            sAudio.AspDelay = HeroDelay(T50MS);
            Hero_GotoStep(HERO_RESET_DEACTIVE);
            break;

        // Release Reset
        case HERO_RESET_DEACTIVE:
            IO_Set(IO_IDX_DSP_RESET,PIN_OUTPUT,INVALID);
            sAudio.AspDelay = HeroDelay(T100MS);    // Wait at least 60ms as UM required
            Hero_GotoStep(HERO_RESET_CHK_BUS);
            break;

        //Check IIC Bus
        case HERO_RESET_CHK_BUS:
            if(OS_TaskIsActive(TASK_ID_I2C1))
            {
                Hero_GotoStep(HERO_RESET_CHK_DEV);
            }
            else
            {
                SubResult = OS_TaskStart(TASK_ID_I2C1);
                if(TRUE == SubResult)
                {
                    Hero_GotoStep(HERO_RESET_CHK_DEV);
                }
                else
                {    //Re-Check Bus
                    sAudio.AspDelay = HeroDelay(T50MS);
                    sHero.ErrId = HERO_ERR_IIC_START;
                }
            }
            break;

        //Check Hero Device
        case HERO_RESET_CHK_DEV:
            sHero.I2cResult = I2C_RET_WAIT;
            QueueResult = I2C_CheckDevice(HERO_IIC,HERO_CS_ADDR,TRUE,(void *)Hero_CallBack_Common,I2C_350KBPS);    
            if(TRUE == QueueResult)  //Command Successfully Queued in IIC Buffer...
            {
                Hero_GotoStep(HERO_RESET_END);
            }
            else
            {    // Failed to Queue in IIC Buffer...  Retry Later...
                //...
                sHero.ErrId = HERO_ERR_IIC_QUEUE;
                sAudio.AspStep = 0;
            }
            break;    

        // Reset End
        case HERO_RESET_END:
            if(I2C_RET_SUCCESS == sHero.I2cResult)
            {
                sAudio.AspCheck = 0; //Asp Module Confirmed..
                Result = SUBLAYER_DONE;    
            }
            else if(I2C_RET_ERR == sHero.I2cResult)
            {
                sAudio.AspCheckCnt++;
                if(1 == sAudio.AspCheck
                   || sAudio.AspCheckCnt >sAudio.AspCheckNum)
                {
                    sAudio.AspStep = 0;
                    sAudio.AspDelay = 0;
                    sAudioKeep.AspModule = AUDIO_ASP_HERO;//AUDIO_ASP_DIRANA;
                    sAudio.AspCheckCnt = 0;  
                    sAudio.AspCheckNum ++;
                }
                else
                {
                    sAudio.AspStep = 0;
                    Result = SUBLAYER_ERROR;
                }
            }
            break;

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_Register
 * @brief      Initialize Hero Specific Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_Register(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(DelayNotExpired(sAudio.AspDelay))
    {
        return (SUBLAYER_DOING);
    }
    
    switch(sAudio.AspStep)
    {
        //Load Radio Improve Parameter A
        case HERO_REGISTER_RADIO_A:
        #ifdef D_HERO_V03    
            SubResult = Hero_Init_ImproveRadioA(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
        #endif//D_HERO_V03    
            {
                sAudio.AspDelay = HeroDelay(T4MS);
            #ifdef D_HERO_V03    
                Hero_GotoStep(HERO_REGISTER_AUDIO_A);
            #else
                Hero_GotoStep(HERO_REGISTER_KEYCODE);
            #endif//D_HERO_V03
            }
            break;
    
        //Load Audio Improve Parameter A
    #ifdef D_HERO_V03        
        case HERO_REGISTER_AUDIO_A:
            SubResult = Hero_Init_ImproveAudioA();
            if(SUBLAYER_DONE == SubResult)    
            {
                sAudio.AspDelay = HeroDelay(T4MS);
                Hero_GotoStep(HERO_REGISTER_RADIO_A2);
            }
            break;
    
        //Load Radio Improve Parameter A2
        case HERO_REGISTER_RADIO_A2:    
            SubResult = Hero_Init_ImproveRadioA2(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)            
            {
                sAudio.AspDelay = HeroDelay(T4MS);
                Hero_GotoStep(HERO_REGISTER_SPURIOUS_SIGNAL);
            }
            break;

        case HERO_REGISTER_SPURIOUS_SIGNAL:
            SubResult = Hero_Init_SpuriosSignal(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)    
            {
                sAudio.AspDelay = HeroDelay(T4MS);
                Hero_GotoStep(HERO_REGISTER_IIS_VCO);
            }
            break;

        case HERO_REGISTER_IIS_VCO:            
            SubResult = Hero_Init_IISVco(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)        
            {
                sAudio.AspDelay = HeroDelay(T4MS);
                Hero_GotoStep(HERO_REGISTER_KEYCODE);
            }
            break;
    #endif//D_HERO_V03            

        //Send KeyCode for Enhanced Functions
        case HERO_REGISTER_KEYCODE:
            SubResult = Hero_Keycode();
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.AspDelay = HeroDelay(T4MS);
                Hero_GotoStep(HERO_REGISTER_USECASE);
            }
            break;

        // Select UseCase for Audio Application
        case HERO_REGISTER_USECASE:
            SubResult = Hero_UserCase(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.AspDelay = HeroDelay(T4MS);
                Hero_GotoStep(HERO_REGISTER_ACTIVE);    
            }
            break;

        //GPIO Before Active    

        // Active Device
        case HERO_REGISTER_ACTIVE:
            SubResult = Hero_AcitveDevice(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.AspDelay = HeroDelay(T4MS);
            #ifdef D_HERO_V03    
                Hero_GotoStep(HERO_REGISTER_RADIO_B);    
            #else
                Hero_GotoStep(HERO_REGISTER_PERIPHERAL);
            #endif//D_HERO_V03
            }
            break;
            
    #ifdef D_HERO_V03    
        //Load Radio Improve Parameter B
        case HERO_REGISTER_RADIO_B:
            SubResult = Hero_Init_ImproveRadioB(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)    
            {
                Hero_GotoStep(HERO_REGISTER_AUDIO_B);    
            }
            break;

        //Load Audio Improve Parameter B
        case HERO_REGISTER_AUDIO_B:
            SubResult = Hero_Init_ImproveAudioB(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)    
            {
                Hero_GotoStep(HERO_REGISTER_PERIPHERAL);
            }    
            break;
    #endif //D_HERO_V03            

        //Config In/Out Mode
        case HERO_REGISTER_PERIPHERAL:
            SubResult = Hero_InitPeripheral(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_GotoStep(HERO_REGISTER_GPIO);    
            }
            break;    

        //Config GPIO
        case HERO_REGISTER_GPIO:
            SubResult = Hero_ConfigGpio(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_GotoStep(HERO_REGISTER_INIT_AUDIO);    
            }
            break;
            
        //Initialize Audio Settings
        case HERO_REGISTER_INIT_AUDIO:
            SubResult = Hero_InitAudio();
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_GotoStep(HERO_REGISTER_INIT_RADIO);
            }    
            break;
            
        case HERO_REGISTER_INIT_RADIO:
            SubResult = Hero_InitRadio();
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_GotoStep(HERO_REGISTER_AUDIO_C);
            }    
            break;
            
        case HERO_REGISTER_AUDIO_C:
        #ifdef D_HERO_V03        
            SubResult = Hero_Init_ImproveAudioC(I2C_RET_WAIT);
            if(SUBLAYER_DONE == SubResult)
        #endif    
            {
                Hero_GotoStep(HERO_REGISTER_TEST1);
            }    
            break;

        case HERO_REGISTER_TEST1:
            //SubResult = Hero_SourceInputSel(PrimaryStr,INPUT_SOURCE_RADIO,0,0);
            //if(SUBLAYER_DONE == SubResult)
            {
            //    sAudio.AspDelay = HeroDelay(T50MS);
                Hero_GotoStep(HERO_REGISTER_TEST2);
            }    
            break;

        case HERO_REGISTER_TEST2:
            SubResult = Hero_SoftMute(0xFCFF,MUTE_OFF);    
            
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_GotoStep(HERO_REGISTER_TEST3);
            }
            break;

        case HERO_REGISTER_TEST3:
            //SubResult = Hero_ReadCommon(0x22,0x00,2);
            //if(SUBLAYER_DONE == SubResult)
            {
                Hero_GotoStep(HERO_REGISTER_END);
            }
            break;

        case HERO_REGISTER_END:
            //SubResult = Audio_FastHardMute(MUTE_OFF);    
            //if(SUBLAYER_DONE == SubResult)
            {
                sHero.InitDone = 1;
                Result = SUBLAYER_DONE;
            }
            break;
            
        default:
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Hero_InitRadio
 * @brief      
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_InitRadio(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sHero.SubStep)
    {
        case OPERATION_0:
            SubResult = Hero_RadioConfigInit();    
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.SubStep = OPERATION_1;
            }
            break;

        case OPERATION_1:    
            SubResult = Hero_RadioInitAll();    
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.SubStep = OPERATION_2;
            }
            break;
            
        case OPERATION_2:
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
 * @function    Hero_InitRadio
 * @brief      
 * @param      None                
 * @retval     Result
 **********************************************************/
 uint8_t Hero_InitAudio(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sHero.SubStep)
    {
        case HERO_AUDIO_SCALING:
            SubResult = Hero_ScalingInit();    
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_CHANNEL_GAIN);
            }
            break;
            
        case HERO_AUDIO_CHANNEL_GAIN:
            SubResult = Hero_InitChanGain();    
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_AUDIO_POINTER);
            }
            break;
            
        case HERO_AUDIO_AUDIO_POINTER:
            SubResult = Hero_AudioPointer();    
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_LOUDNESS);
                sAudio.LoudnessMask = 0xFF;    //Set Loudness Mask: Inital and Set all!
                sAudio.LoudnessCtl = OPERATION_0;
            }
            break;
            
        case HERO_AUDIO_LOUDNESS:
            SubResult = Hero_SetLoudness();
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_VOLUME1);
            }
            break;
            
        case HERO_AUDIO_VOLUME1:
            SubResult = Hero_DrvSetVolume(30,SYSTEM_REAR);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_VOLUME2);
            }
            break;

        case HERO_AUDIO_VOLUME2:
            //SubResult = Hero_WriteMemWord(HERO_IIC_INIT_VOL,I2CDRV_X_MEM,HDSP_X_Vol_Boost12dB,(int32_t)0);
            //if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_BF);
                sAudio.BalFadCtl = 0;
                sAudio.BalFadMask = 0xFF;
            }
            break;
            
        case HERO_AUDIO_GSA:    // Spectrum
            break;

        case HERO_AUDIO_BF:
            SubResult = Hero_SetBalFad();        
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_TONE);
                sAudio.DrvBassStep = OPERATION_0;
            }
            break;

        //Retrieve Bass Setting    
        case HERO_AUDIO_TONE:
        case HERO_AUDIO_BASS:    
            SubResult = Hero_SetBass(sAudioDat.sBasic.sBass,SYSTEM_FRONT);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_MID);
                sAudio.DrvMidStep = OPERATION_0;
            }
            break;

        //Retrieve Middle Setting
        case HERO_AUDIO_MID:
            SubResult = Hero_SetMid(sAudioDat.sBasic.sMid,SYSTEM_FRONT);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_TREBLE);
                sAudio.DrvTrebleStep = OPERATION_0;                
            }
            break;

        //Retrieve Treble Setting
        case HERO_AUDIO_TREBLE:
            SubResult = Hero_SetTreble(sAudioDat.sBasic.sTreble,SYSTEM_FRONT);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_GEQ);
                sAudio.GeqMask = 0xFFFF;    //Set Geq Mask: Inital and Set all bands!
                sAudio.GeqStep = OPERATION_0;
            }
            break;
            
        case HERO_AUDIO_GEQ:
            SubResult = Hero_SetGeq();
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_PEQ);
                sAudio.XoverMask = 0xFF;
            }
            break;		
        case HERO_AUDIO_PEQ:
            SubResult = Hero_SetCrossOver();
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_DC_FILTER);
            }
            break;
            
        case HERO_AUDIO_DC_FILTER:
            SubResult = Hero_SetDcFilter(sAudioDat.sAdv.DcFilter,SYSTEM_FRONT);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_NAV_PHONE_FILTER);
            }
            break;
            
        case HERO_AUDIO_NAV_PHONE_FILTER:
            SubResult = Hero_NavPhoneFilterInit();
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.SubStep = HERO_AUDIO_COMP_EXP;
            }
            break;
            
        case HERO_AUDIO_COMP_EXP:
            sHero.SubStep = HERO_AUDIO_BEEP;
            break;
            
        case HERO_AUDIO_BEEP:
            SubResult = Hero_BeepInit();
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.SubStep = HERO_AUDIO_CLICKCLACK;
            }
            break;
            
        case HERO_AUDIO_CLICKCLACK:
            SubResult = Hero_CCInit();
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.SubStep = HERO_AUDIO_SRCSCALER;
            }
            break;

        case HERO_AUDIO_SRCSCALER:
            SubResult = Hero_SrcScalingInit();
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.SubStep = HERO_AUDIO_PHASE_SHIFT;
                sAudio.PhaseMask = 0;
            }
            break;

        //Phase Shifter
        case HERO_AUDIO_PHASE_SHIFT:
            SubResult = Hero_SetPhaseShifter();
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_UBASS);
                sAudio.UltraBassMask = 0xFF;
                sAudio.UltraBassCtl = 0;
            }
            break;

        case HERO_AUDIO_UBASS:
            SubResult = Hero_SetUltraBass();
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_POLYCHIME);
            }
            break;

        case HERO_AUDIO_POLYCHIME:
            Hero_SubGotoStep(HERO_AUDIO_DELAY);
            sAudio.DelayLineMask = 0xFF;
            sAudio.DelayCtl = 0;
            break;
            
        case HERO_AUDIO_DELAY:
            SubResult = Hero_DelayLine();
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_NAV_VOL);
            }
            break;

        case HERO_AUDIO_NAV_VOL:
            SubResult = Hero_NavPhoneVol(20,0);
            if(SUBLAYER_DONE == SubResult)
            {
                Hero_SubGotoStep(HERO_AUDIO_SUBWOOFER);
                sAudio.SwMask = 0xFF;
                sAudio.SwCtl = 0;
            }
            break;

        //SubWoofer    
        case HERO_AUDIO_SUBWOOFER:
            SubResult = Hero_SetSubwoofer();
            if(SUBLAYER_DONE == SubResult)
            {
                sHero.SubStep = HERO_AUDIO_END;
            }
            break;    
            
        case HERO_AUDIO_END:
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
 * @function    Hero_InitChannelGain
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_SourceInputSel(Audio_Stream_t stream,eAudio_InputSource Input,eInput_Analog_Mode mode,double scal )
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sAudio.SrcInputSelStep)
    {
        //Select Stream's Input
        case OPERATION_0:
            switch(stream)
            {
                case NavigationStr:
                    SubResult = Hero_DrvSetNavInput(Input);
                    break;
                    
                case PhoneStr:
                    SubResult = Hero_DrvSetPhoneInput(Input);
                    break;
                    
                default:
                    SubResult = Hero_DrvSetPSInput(stream,Input);
                    break;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.SrcInputSelStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            sAudio.SrcInputSelStep = OPERATION_0;
            Result = SUBLAYER_ERROR;
            break;
    }

    if(SUBLAYER_ERROR == SubResult)
    {
        Result = SUBLAYER_ERROR;    
        sAudio.SrcInputSelStep = OPERATION_0;
    }
    
    return (Result);    
}
/**********************************************************
 * @function    Hero_EasyProgrammWrite
 * @brief      Initial All Radio Registers
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Hero_GetAin(uint8_t Src, uint8_t Type)
{
    uint8_t Result = INPUT_SOURCE_SINE;
    uint8_t Temp = 0;
    HERO_ACH_TAB_STRUCT* pTmpAch;
    
    //Input Parameter Check...

    if(SYSTEM_FRONT == Type)
    {
        pTmpAch = (HERO_ACH_TAB_STRUCT*)(&(Tab_Ach_Hero[0]));
    }
    else if(SYSTEM_REAR == Type)
    {
        pTmpAch = (HERO_ACH_TAB_STRUCT*)(&(Tab_Rach_Hero[0]));
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

    return (Result);
}
/**********************************************************
 * @function    Hero_SwitchAch
 * @brief      Switch Hero's Ach
 * @param      uint8_t FrontAch
 *            uint8_t RearAch
 * @retval     Result
 **********************************************************/
 uint8_t Hero_SwitchAch(uint8_t Ach, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t PhysicalCh = 0xFF;
    int8_t ScalerVal;


	switch(sAudio.AspAchCtl)
	{
		//Switch Front System Channel 
		case OPERATION_0:
			if((SYSTEM_FRONT == Type) || (SYSTEM_ALL == Type))
			{
				//Get Front System New Logic Ach Config: transfer to Physical Ch
				PhysicalCh = Hero_GetAin(Ach,SYSTEM_FRONT);
				//Switch Front System Channel
				SubResult = Hero_SourceInputSel(PrimaryStr,PhysicalCh,(eInput_Analog_Mode)0,0);
			}
			else
			{
				SubResult = SUBLAYER_DONE;
			}

			if(SUBLAYER_DONE == SubResult)
			{
				sAudio.AspAchCtl = OPERATION_1;
			}
			break;

		//Switch Rear System Channel
		case OPERATION_1:
			if((SYSTEM_REAR == Type) || (SYSTEM_ALL == Type))
			{
				//Get Rear System New Logic Ach Config: transfer to Physical Ch
				PhysicalCh = Hero_GetAin(Ach,SYSTEM_REAR);    

				//Switch Rear System Channel
				SubResult = Hero_SourceInputSel(SecondaryStr,PhysicalCh,(eInput_Analog_Mode)0,0);
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
				SubResult = Hero_SetSrcScaler(SYSTEM_FRONT,ScalerVal);                
			}
			else
			{
				SubResult = SUBLAYER_DONE;
			}

			if(SUBLAYER_DONE == SubResult)
			{
			//	sAudio.AspAchCtl = OPERATION_0;
			//	Result = SUBLAYER_DONE;
				sAudio.AspAchCtl = OPERATION_3;
			}
			break;
		case OPERATION_3:
			if(Ach== SRC_TYPE_BT_PHONE)
			{
				#if 1		// 蓝牙电话 前面2个喇叭有声音
				if( (sAudioDat.sBasic.Fader != (0)) || 
				     (sAudioDat.sBasic.Balance != (AUDIO_BALANCE_MAX/2)))
				{
					sAudioDat.sBasic.Fader = 0;
					sAudioDat.sBasic.Balance = AUDIO_BALANCE_MAX/2;
					sAudio.BalFadMask |= (BF_MASK_FAD|BF_MASK_BAL);
					sAudio.AspAchCtl = OPERATION_4;
					audio_printf(_T("Setting BT Balance\n"));
				}
				#else		// 蓝牙电话 4个喇叭均有声音
				if( (sAudioDat.sBasic.Fader != (AUDIO_FADER_MAX/2)) || 
				     (sAudioDat.sBasic.Balance != (AUDIO_BALANCE_MAX/2)))
				{
					sAudioDat.sBasic.Fader = AUDIO_FADER_MAX/2;
					sAudioDat.sBasic.Balance = AUDIO_BALANCE_MAX/2;
					sAudio.BalFadMask |= (BF_MASK_FAD|BF_MASK_BAL);
					sAudio.AspAchCtl = OPERATION_4;
					audio_printf(_T("Setting BT Balance\n"));
				}
				#endif
			}
			else
			{
				if( (sAudioDat.sBasic.Fader != sAudio.Fader_Media) || 
				     (sAudioDat.sBasic.Balance != sAudio.Balance_media))
				{
					
					sAudioDat.sBasic.Fader = sAudio.Fader_Media;
					sAudioDat.sBasic.Balance = sAudio.Balance_media;
					sAudio.BalFadMask |= (BF_MASK_FAD|BF_MASK_BAL);
					sAudio.AspAchCtl = OPERATION_4;
					audio_printf(_T("Setting normal Balance\n"));
				}
			}
			if(sAudio.AspAchCtl  != OPERATION_4)
			{
				sAudio.AspAchCtl = OPERATION_5;
			}
			break;
		case OPERATION_4:
			SubResult = Audio_SetBalFad();
			if(SubResult == SUBLAYER_DONE)
			{
				sAudio.AspAchCtl = OPERATION_5;
			}
			break;
		case OPERATION_5:
			sAudio.AspAchCtl = OPERATION_0;
			Result = SUBLAYER_DONE;
			break;
	}	

    return (Result);
}

/**********************************************************
 * @function    Hero_SetMixSrc
 * @brief      Set Mix Source
 * @param      uint8_t Src    
 *            uint8_t Type
 * @retval     Result
 **********************************************************/
uint8_t Hero_SetMixSrc(uint8_t Src,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    if(SRC_TYPE_NAVI_AUDIO == Src) //Ain3
    {
        Result = Hero_DrvSetNavInput(INPUT_SOURCE_AIN3);
    }
    else if(SRC_TYPE_BT_PHONE == Src) //IIS2
    {
        Result = Hero_DrvSetPhoneInput(INPUT_SOURCE_IIS0);
    }

    return (Result);    
}
/**********************************************************
 * @function    Hero_ConfigMix
 * @brief      Config Mix: Src, Poszition, On/Off ,Gain
 * @param      uint8_t Src    
 *            uint8_t Type        
 *            int8_t Gain
 * @retval     Result
 **********************************************************/
uint8_t Hero_ConfigMix(uint8_t Src,uint8_t Type,int8_t Gain)
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
        #if 0        
            case MIX_TYPE_REAR:
                AddOnIndex = P_MIX_NAV_REAR;
                break;
                
            case MIX_TYPE_ALL:
                AddOnIndex = P_MIX_NAV_ALL;
                break;
        #endif        
        }
	//	AddOnIndex = P_MIX_NAV_FRONT;
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
                
            case MIX_TYPE_RL:
                AddOnIndex = P_MIX_PHONE_RL;
                break;
                
            case MIX_TYPE_RR:
                AddOnIndex = P_MIX_PHONE_RR;
                break;
                
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
        TmpGain = -100;
    }
    
    Result = Hero_DrvSuperPositionGain(HERO_IIC_SET_IMPOSE, AddOnIndex,TmpGain);

    return (Result);    
}
#endif

