/**********************************************************
 * @file        Audio_Func.c
 * @purpose    
 * @version    0.01
 * @date        24. July. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          24.July.2012        v0.01        created
 *  
  **********************************************************/
#define AUDIO_FUNC_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
#include "Audio_Tab.c"
/* ========================= public variable ==================== */

/* ========================= private variable =================== */

//const tEEP_DATA_RANG lc_tAudioDefData[] =
//{
//    {BEEP_VOL_SET_LOW,BEEP_VOL_SET_MID,BEEP_VOL_SET_HIGH},
//    {CAR_STYLE_SMALL, CAR_STYLE_MIDDLE,CAR_STYLE_BIG},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX}, //Tuner
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX}, //Dvd
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX}, 
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX}, 
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},  
//   // {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},  //Mirror Link  
//    {0,(AUDIO_SRC_SCALER_MAX / 2),SRC_SCALER_MAX},  //MHL  
//    {0,0,6},    
//    {0,0,6},    
//    {0,0,6},   
//    {0,0,6},    
//    {0,0,6},    
//    {0,0,6},    
//};

//tEEP_DATA_BLOCK l_tEepAudioRomData;

//const tEEP_DATA lc_tEepAudioRom = 
//{   
//    D_EEP_AUDIO_ID,
//    (uint8_t*)&sAudioEep,lc_tAudioDefData,
//    D_EEP_AUDIO_ADDR,D_EEP_AUDIO_LEN,0
//};

uint8_t  voltemp=0;


/* ========================= Code Part =================== */

/**********************************************************
 * @function    Audio_GotoMidStep
 * @brief      Switch Midlayer Function Control Step
 * @param      uint16_t x : Step Will Goto                    
 * @retval     None
 **********************************************************/
void Audio_GotoMidStep(uint8_t x)
{
    sAudio.MidStep = x;
    sAudio.AspStep = OPERATION_0;
}
/**********************************************************
 * @function    Audio_GotoSpecialStep
 * @brief      Switch Midlayer Function Control Step
 * @param      uint16_t x : Step Will Goto                    
 * @retval     None
 **********************************************************/
void Audio_GotoSpecialStep(uint8_t* Step,uint8_t x)
{
    *Step = x;
#ifdef D_AUDIO_ASP_HERO        
    sHero.SubStep = OPERATION_0;
#endif//D_AUDIO_ASP_HERO
}
/**********************************************************
 * @function    Audio_LoadDatum
 * @brief      Load Datum
 * @param      None                    
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_LoadDatum(void)
{
    uint8_t Result = SUBLAYER_DOING;

    if(DelayNotExpired(sAudio.FuncDelay))
        return (Result);
    
    switch(sAudio.MidStep)
    {
        //Check&Read Datum
        case AUDIO_LOAD_CHECK:
            if(OS_RamCheck((void*)&sAudioDat,(sizeof(AUDIO_DATUM_STRUCT)-sizeof(uint16_t)),
                           (void*)&(sAudioDat.CheckSum)))
            {
                /*Ram check OK, no need to load from eeprom*/
                sAudio.MidStep = AUDIO_LOAD_END;
            }
            else
            {
                sAudio.MidStep = AUDIO_LOAD_DEFAULT;
            }
            break;
       

        //Load Default Datum
        case AUDIO_LOAD_DEFAULT:
            Audio_ResetInfoVariable();
            OS_CreateRamChkBlock((void*)&sAudioDat,
                                (sizeof(AUDIO_DATUM_STRUCT)-sizeof(uint16_t)),
                                (void*)&(sAudioDat.CheckSum));
            sAudio.MidStep = AUDIO_LOAD_END;
            break;

        case AUDIO_LOAD_ERROR:
            sAudio.MidStep = AUDIO_LOAD_DEFAULT;
            break;

        case AUDIO_LOAD_END:
            Audio_InitVariable();
            Audio_VariableCheck();
            Result = SUBLAYER_DONE;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Audio_AmpStartup
 * @brief      AMP startup 
 *            include: Power ,Reset, Initialize
 * @param      None                    
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_AmpStartup(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sAudio.MidStep)
    {
        // Open AMP Power Supply
        case AMP_STARTUP_POWER:
            SubResult = Amp_OpenPower();
            if(SUBLAYER_DONE == SubResult)
            {
                Audio_GotoMidStep(AMP_STARTUP_RESET);
            }
            break;

        // Reset AMP Module
        case AMP_STARTUP_RESET:
            SubResult = Amp_Reset();
            if(SUBLAYER_DONE == SubResult)
            {
                Audio_GotoMidStep(AMP_STARTUP_REGISTER);
                if(MODULE_NONE == AmpCtl.Module)
                {
                    sAudio.MidStep = OPERATION_0;
                    Result = SUBLAYER_DONE;    // AMP Startup End
                }
			IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,INVALID);
            }
            break;

        // Initialize AMP Registers    
        case AMP_STARTUP_REGISTER:
            SubResult = Amp_Register();
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.MidStep = OPERATION_0;
                Result = SUBLAYER_DONE;    // AMP Startup End
            }
            break;
            
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.MidStep = OPERATION_0;
    }

    return (Result);
}
/**********************************************************
 * @function    Audio_AspStartup
 * @brief      ASP startup 
 *            include: Power ,Reset, Initialize    
 * @param      None                    
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_AspStartup(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sAudio.MidStep)
    {
        // Open ASP Power Supply
        case ASP_STARTUP_POWER:
            SubResult = Audio_Asp_OpenPwr();
            if(SUBLAYER_DONE == SubResult)
            {
                Audio_GotoMidStep(ASP_STARTUP_RESET);
            }
            break;

        // Reset ASP Module
        case ASP_STARTUP_RESET:
            SubResult = Audio_Asp_Reset();
            if(SUBLAYER_DONE == SubResult)
            {
                Audio_GotoMidStep(ASP_STARTUP_REGISTER);
            }
            break;

        // Initialize ASP Registers    
        case ASP_STARTUP_REGISTER:
            SubResult = Audio_Asp_Register();
            if(SUBLAYER_DONE == SubResult)
            {
                sAudio.MidStep = OPERATION_0;
                Result = SUBLAYER_DONE;
            }
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.MidStep = OPERATION_0;
    }    

    return (Result);
}
/**********************************************************
 * @function    Audio_SwitchStartup
 * @brief      Audio Matrix startup
 *            include: Power ,Reset, Initialize    
 * @param      None                    
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_SwitchStartup(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(sAudio.MidStep)
    {
        //Open Switch Power Supply
        case SWITCH_STARTUP_POWER:
            Switch_OpenPower();
            Audio_GotoMidStep(SWITCH_STARTUP_RESET);
            break;

        //Reset Switch Module
        case SWITCH_STARTUP_RESET:
            SubResult = Switch_Reset();
            if(SUBLAYER_DONE == SubResult)
            {
                Audio_GotoMidStep(SWITCH_STARTUP_REGISTER);
            }
            break;

        //Initialize Switch Registers    
        case SWITCH_STARTUP_REGISTER:
            SubResult = Switch_Register();
            if(SUBLAYER_DONE == SubResult)
            {
                Audio_GotoMidStep(SWITCH_STARTUP_END);
            }
            break;
            
        //Switch Startup End
        case SWITCH_STARTUP_END:
            sAudio.MidStep = OPERATION_0;
            Result = SUBLAYER_DONE;
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    //Sync Error Type and Feedback
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
        sAudio.MidStep = OPERATION_0;
    }

    return (Result);
}
uint8_t Audio_AdjustVolumeStep(void)
{
	uint8_t step =1;
	if(SysWorkStatusGrp.SysBtCallFlag)
	{
		step = 3;
	}
	else if(MIX_STATUS_NAVI & sAudio.MixStatus)
	{
		step = 1;
	}
	return step;
}
/**********************************************************
 * @function    Audio_InputLogic
 * @brief      Dispose the logic of input requirement
 *            Transfer logic operation to commonly operation
 * @param      tMSG_BUF* Msg                    
 * @retval     NULL
 **********************************************************/
void Audio_InputLogic(tMSG_BUF* pMsg)
{    
    #define MsgSid     pMsg->iSid    
    #define MsgDat     pMsg->uData.a_cData[0]
    #define MsgDat1     pMsg->uData.a_cData[0]
    #define MsgDat2     pMsg->uData.a_cData[1]
    #define MsgDat3     pMsg->uData.a_cData[2]

    audio_printf(_T("Audio_InputLogic sid=%d",MsgSid));
    audio_printf(_T("    Msgdat=%d,%d,%d,%d\n",MsgDat,MsgDat1,MsgDat2,MsgDat3));	
    sAudio.CommonCode = AUDIO_COMMON_NULL;

    switch(MsgSid)
    {
	//Front System Volume Increase
	case OP_AUD_VOL_INC:
		if(SRC_TYPE_AVOFF == sAudio.SysChannel)
		{
			if(0x00 == (sAudio.MixStatus & MIX_STATUS_NAVI))
				break;
		}
#ifndef D_CODE_FOR_JX
		if((SRC_TYPE_TUNER == sAudio.SysChannel) && (Tuner_Api_GetSeekState()) && (0x00 == (MIX_STATUS_NAVI & sAudio.MixStatus)))
		{
			break;
		}
#endif
		#if 0 //snake20160917 按下面板和方控的音量键,发送相同的消息,由MCU来区分设置的导航音量还是系统音量...
		if(sAudio.MixStatus & MIX_STATUS_NAVI)//snake20160917 
		{
			uint8_t step = Audio_AdjustVolumeStep();
			if((sAudioKeep.NaviVol + step) < AUDIO_VOL_MAX)
			{
				sAudioKeep.NaviVol+= step;
			}
			else
			{
				sAudioKeep.NaviVol = AUDIO_VOL_MAX;
			}

			_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_SVOL_NAVI,sAudioKeep.NaviVol,0,0,0);
		}
		else
		#endif
		{
	
			if(sAudioKeep.CurrentlyVol <= AUDIO_VOL_MAX) 
			{

				uint8_t step = Audio_AdjustVolumeStep();
				if(SysWorkStatusGrp.SysBtCallFlag)
				{
					if((sAudioKeep.CurrentlyVol + step) < 30)
					{
						sAudioKeep.CurrentlyVol+= step;
					}
					else
					{
						sAudioKeep.CurrentlyVol = 30;
					}
				}
				else
				{
					if((sAudioKeep.CurrentlyVol + step) < AUDIO_VOL_MAX)
					{
						sAudioKeep.CurrentlyVol+= step;
					}
					else
					{
						sAudioKeep.CurrentlyVol = AUDIO_VOL_MAX;
					}
				}

				sAudio.bNotDispVol = 0;
				//Check De-Mute while switching volume when muted
				if(MUTE_ON == (sAudio.KeyMuteFlag & (0x01 << SYSTEM_FRONT)))
				{
					sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_FRONT));
					sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_OFF;
					sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
					sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
					//Send Feedback to HMI,Update Display Immediately
					_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);
				}
				//else if((sAudio.KeyMuteStep[SYSTEM_FRONT] >= AUDIO_UNMUTE_START)
				//    && (sAudio.KeyMuteStep[SYSTEM_FRONT] < AUDIO_MUTE_END))
				else if(sAudio.KeyMuteStep[SYSTEM_FRONT] != AUDIO_MUTE_IDLE)
				{
				//Do Nothing while De-Muting
				}
				else
				{
					sAudio.CommonCode = AUDIO_COMMON_VOL;
				}
				if((SysWorkStatusGrp.SysBtCallFlag) &&(sAudioKeep.CurrentlyVol == AUDIO_VOL_MAX_BT))
				{
					_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,AUDIO_VOL_MAX_BT,Audio_GetVolType(),0,0);
				}
				else if(sAudioKeep.CurrentlyVol == AUDIO_VOL_MAX)
				{
					_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,AUDIO_VOL_MAX,Audio_GetVolType(),0,0);
				}
				
			}
		}
		break;

	//Front System Volume Decrease
	case OP_AUD_VOL_DEC:
		if(SRC_TYPE_AVOFF == sAudio.SysChannel)
		{
			if(0x00 == (sAudio.MixStatus & MIX_STATUS_NAVI))
			break;
		}
#ifndef D_CODE_FOR_JX
		if((SRC_TYPE_TUNER == sAudio.SysChannel) && (Tuner_Api_GetSeekState()) && (0x00 == (MIX_STATUS_NAVI & sAudio.MixStatus)))
		{
			break;
		}
#endif	
		#if 0 //snake2060917 按下面板和方控的音量键,发送相同的消息,由MCU来区分设置的导航音量还是系统音量...
		if(sAudio.MixStatus & MIX_STATUS_NAVI)//snake20160917   导航音量的加减....
		{
			uint8_t step = Audio_AdjustVolumeStep();
			if(sAudioKeep.NaviVol > step)
			{
				sAudioKeep.NaviVol -= step;
			}
			else
			{
				sAudioKeep.NaviVol = 0;
			}
			_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_SVOL_NAVI,sAudioKeep.NaviVol,0,0,0);
		}
		else
		#endif
		{
			if(sAudioKeep.CurrentlyVol)
			{
				uint8_t step = Audio_AdjustVolumeStep();
				if(sAudioKeep.CurrentlyVol > step)
				{
					sAudioKeep.CurrentlyVol -= step;
				}
				else
				{
					sAudioKeep.CurrentlyVol = 0;
				}

				if(sAudio.MixStatus & MIX_STATUS_NAVI)//snake20160917   导航音量的加减....
				{
					_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_SVOL_NAVI,sAudioKeep.CurrentlyVol,0,0,0);
					audio_printf(_T("-------------nvai vol----------------\n"));
				}

				else
				{
					sAudio.bNotDispVol = 0;
					//Check De-Mute while switching volume when muted
					if(MUTE_ON == (sAudio.KeyMuteFlag & (0x01 << SYSTEM_FRONT)))
					{
						sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_FRONT));
						sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_OFF;
						sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
						sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
						//Send Feedback to HMI,Update Display Immediately
						_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);
					}
					//else if((sAudio.KeyMuteStep[SYSTEM_FRONT] >= AUDIO_UNMUTE_START)
					//    && (sAudio.KeyMuteStep[SYSTEM_FRONT] < AUDIO_MUTE_END))
					else if(sAudio.KeyMuteStep[SYSTEM_FRONT] != AUDIO_MUTE_IDLE)    
					{
					//Do Nothing while De-Muting
					}
					else
					{
						sAudio.CommonCode = AUDIO_COMMON_VOL;
					}
				}
			}
			else if(!sAudioKeep.CurrentlyVol)
			{
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,0,Audio_GetVolType(),0,0);
			}
		}
		break;

        //Front System Volume Select    
        case OP_AUD_VOL_SEL:
		if(SRC_TYPE_NUM == sAudio.SysChannel)  // xjh ???ó?alogoê±?ì?ùμ13μóDéùò?ê?3?
			break;
		
		if(SRC_TYPE_AVOFF == sAudio.SysChannel)
		{
			if(0x00 == (sAudio.MixStatus & MIX_STATUS_NAVI))
			break;
		}
		
		if((MsgDat <= AUDIO_VOL_MAX) && ((MsgDat != sAudioKeep.CurrentlyVol) || (LOUDNESS_ON == sAudioDat.sBasic.sLoudnessMode)))
		{
			sAudioKeep.CurrentlyVol = MsgDat;
			
			if(0 == MsgDat2)
				sAudio.bNotDispVol = 0;
			else
				sAudio.bNotDispVol = 1;
			//Check De-Mute while switching volume when muted
			if(MUTE_ON == (sAudio.KeyMuteFlag & (0x01 << SYSTEM_FRONT)))
			{
				sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_FRONT));
				sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_OFF;
				sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
				sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
				//Send Feedback to HMI,Update Display Immediately
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);
			}
			else if((sAudio.KeyMuteStep[SYSTEM_FRONT] >= AUDIO_UNMUTE_START)&& (sAudio.KeyMuteStep[SYSTEM_FRONT] < AUDIO_MUTE_END))
			{
			//Do Nothing while De-Muting
			}
			else
			{
				sAudio.CommonCode = AUDIO_COMMON_VOL;
			}
		}
		break;

	//Set Startup Volume
	case OP_AUD_SVOL_SEL:    
		if(MsgDat <= AUDIO_VOL_MAX)
		{
		
		}
		break;

	case OP_AUD_SVOL_MEDIA: 
		if((MsgDat >= 0) && (MsgDat <= AUDIO_VOL_MAX)) 
		{
			sAudioDat.sBasicBK.DefaultMediaVolume = MsgDat;
			sAudioKeep.SysVol = MsgDat;

			if(MUTE_ON == (sAudio.KeyMuteFlag & (0x01 << SYSTEM_FRONT)))
			{
				sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_FRONT));
				sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_OFF;
				sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
				sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
				//Send Feedback to HMI,Update Display Immediately
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);
			}
			
			if((SRC_TYPE_BT_PHONE == sAudio.SysChannel)||(sAudio.MixStatus & MIX_STATUS_NAVI))
			{
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,sAudioKeep.SysVol,VOL_TYPE_SYS,0,0);
			}
			else
			{
				sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; //Fade in/out volume
				sAudio.HintVol = MsgDat;
			}
		}
		break;

	case OP_AUD_SVOL_PHONE:
		if((MsgDat >= 0) && (MsgDat <= AUDIO_VOL_MAX))
		{
			sAudioDat.sBasicBK.DefaultPhoneVol = MsgDat;
			sAudioKeep.BtVol = MsgDat;

			if(MUTE_ON == (sAudio.KeyMuteFlag & (0x01 << SYSTEM_FRONT)))
			{
				sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_FRONT));
				sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_OFF;
				sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
				sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
				//Send Feedback to HMI,Update Display Immediately
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);
			}
						
			if(SRC_TYPE_BT_PHONE != sAudio.SysChannel)
			{
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,sAudioKeep.BtVol,VOL_TYPE_BT,0,0);
			}
			else
			{
				sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; //Fade in/out volume
				sAudio.HintVol = MsgDat;
			}
		}
		break;

	case OP_AUD_SVOL_NAVI:
		if((MsgDat >= 0) && (MsgDat <= AUDIO_VOL_MAX))
		{
			sAudioDat.sBasicBK.DefaultNaviVol = MsgDat;
			sAudioKeep.NaviVol = MsgDat;

			if(MUTE_ON == (sAudio.KeyMuteFlag & (0x01 << SYSTEM_FRONT)))
			{
				sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_FRONT));
				sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_OFF;
				sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
				sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
				//Send Feedback to HMI,Update Display Immediately
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);
			}
						
			if(0 == (MIX_STATUS_NAVI & sAudio.MixStatus))
			{
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,sAudioKeep.NaviVol,VOL_TYPE_NAV,0,0);
			}
			else
			{
				sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; //Fade in/out volume
				sAudio.HintVol = MsgDat;
			}
		}
		break;

        case OP_AUD_SVOL_APP:
             if((MsgDat >= 0) && (MsgDat <= AUDIO_VOL_MAX))
            {
                sAudioDat.sBasicBK.DefaultPromptVol = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; //Fade in/out volume
              //  _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BASIC,&sAudioDat.sBasic);
                sAudio.HintVol = MsgDat;
            }
            break;

        case OP_AUD_HINT_MEDIA:
            if(0x01 == MsgDat)
            {
                sAudioDat.sBasicBK.sFlg.F_MediaVol_Set = 1;
                sAudioDat.sBasicBK.sFlg.F_PhoneVol_Set = 0;
                sAudioDat.sBasicBK.sFlg.F_NaviVol_Set = 0;
                sAudioDat.sBasicBK.sFlg.F_PromptVol_Set = 0;
                sAudio.HintVol = sAudioDat.sBasicBK.DefaultMediaVolume;
                sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; //Fade in/out volume
            }
            else
            {
                sAudioDat.sBasicBK.sFlg.F_MediaVol_Set = 0;
                sAudio.CommonCode = AUDIO_COMMON_HINT_EXIT; 
            }
            break;

        case OP_AUD_HINT_PHONE:
           if(0x01 == MsgDat)
            {
                sAudioDat.sBasicBK.sFlg.F_MediaVol_Set = 0;
                sAudioDat.sBasicBK.sFlg.F_PhoneVol_Set = 1;
                sAudioDat.sBasicBK.sFlg.F_NaviVol_Set = 0;
                sAudioDat.sBasicBK.sFlg.F_PromptVol_Set = 0;
                sAudio.HintVol = sAudioDat.sBasicBK.DefaultPhoneVol;
                sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; //Fade in/out volume
            }
            else
            {
                sAudioDat.sBasicBK.sFlg.F_PhoneVol_Set = 0;
                sAudio.CommonCode = AUDIO_COMMON_HINT_EXIT; 
            }
            break;

        case OP_AUD_HINT_NAVI:
           if(0x01 == MsgDat)
            {
                sAudioDat.sBasicBK.sFlg.F_MediaVol_Set = 0;
                sAudioDat.sBasicBK.sFlg.F_PhoneVol_Set = 0;
                sAudioDat.sBasicBK.sFlg.F_NaviVol_Set = 1;      
                sAudioDat.sBasicBK.sFlg.F_PromptVol_Set = 0;
                sAudio.HintVol = sAudioDat.sBasicBK.DefaultNaviVol;
                sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; //Fade in/out volume
            }
            else
            {
                sAudioDat.sBasicBK.sFlg.F_NaviVol_Set = 0;   
                sAudio.CommonCode = AUDIO_COMMON_HINT_EXIT; 
            }
            break;

        case OP_AUD_HINT_APP:
           if(0x01 == MsgDat)
            {
                sAudioDat.sBasicBK.sFlg.F_MediaVol_Set = 0;
                sAudioDat.sBasicBK.sFlg.F_PhoneVol_Set = 0;
                sAudioDat.sBasicBK.sFlg.F_NaviVol_Set = 0;   
                sAudioDat.sBasicBK.sFlg.F_PromptVol_Set = 1;
                sAudio.HintVol = sAudioDat.sBasicBK.DefaultPromptVol;
                sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; //Fade in/out volume
            }
            else
            {
                sAudioDat.sBasicBK.sFlg.F_PromptVol_Set = 0;
                sAudio.CommonCode = AUDIO_COMMON_HINT_EXIT; 
            }
            break;

        case OP_AUD_REVERSE_VOL:
            if((SRC_TYPE_BT_PHONE != sAudio.SysChannel) && (SRC_TYPE_3G_PHONE != sAudio.SysChannel))
            {
                if(sAudioKeep.CurrentlyVol > 15)
                {
                    sAudio.HintVol = 15;
                    sAudio.CommonCode = AUDIO_COMMON_HINT_VOL; 
                }
            }
            break;

        case OP_AUD_REVERSE_END:
            sAudio.CommonCode = AUDIO_COMMON_HINT_EXIT; 
            break;

        case OP_AUD_RVOL_INC:    
        case OP_AUD_RVOL_DEC:    
            break;
            
        //Rear System Volume Select    
        case OP_AUD_RVOL_SEL:    //Directly Change Rear system volume to selected value
            if((MsgDat <= AUDIO_VOL_MAX) && (MsgDat != sAudioKeep.RearVol))//If Newly required is same as currently, Ignore!
            {
                sAudioKeep.RearVol = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_REARVOL;
            }
            break;    

        //Volume Curve Delta
        case OP_AUD_VOL_CURVE:
            sAudioDat.sInfo.VolCurveDelta = MsgDat;
            break;

        //Key Mute: Front System
        case OP_AUD_MUTE:        //Key Mute
            if(SRC_TYPE_AVOFF == sAudio.SysChannel)
		{
			if(MsgDat != (MUTE_OFF|SRC_TYPE_AVOFF))
			{
				if(0x00 == (sAudio.MixStatus & MIX_STATUS_NAVI))
				{
					//_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_NCK,BEEP_ON,0,0);
					break;
				}
			}
		}

              if((MUTE_ON == ((sAudio.KeyMuteFlag >> SYSTEM_FRONT) & 0x01))&& (MsgDat == 0x01))
              {
                  sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_FRONT));
              }
              else if((MUTE_OFF == ((sAudio.KeyMuteFlag >> SYSTEM_FRONT) & 0x01))&&(MsgDat == 0x00))
              {
                  sAudio.KeyMuteFlag |= (MUTE_ON << SYSTEM_FRONT);
              }
	   
          //Send Feedback to HMI,Fresh Display Immediately
          //if(MsgDat2 != VOL_TYPE_BT)  // xjh modify for note 1 in svn
           _SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);

            sAudio.KeyMuteReq[SYSTEM_FRONT] = ((sAudio.KeyMuteFlag >> SYSTEM_FRONT) & 0x01);
            sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
            sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
            break;

        //Rear Key Mute..
        case OP_AUD_RMUTE:
            if(MUTE_ON == ((sAudio.KeyMuteFlag >> SYSTEM_REAR) & 0x01))  //Update Flag
            {
                sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_REAR));
            }
            else
            {
                sAudio.KeyMuteFlag |= (MUTE_ON << SYSTEM_REAR);
            }
            //Send Feedback to HMI,Fresh Display Immediately
            _SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_REAR,0,0);

            sAudio.KeyMuteReq[SYSTEM_REAR] = ((sAudio.KeyMuteFlag >> SYSTEM_REAR) & 0x01);
            sAudio.KeyMuteDly[SYSTEM_REAR] = 0;
            sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_IDLE;
            break;

        //Require for Mute
        case OP_AUD_MUTE_REQ:
        case OP_AUD_RMUTE_REQ:    
            Audio_MuteQueueIn(MsgDat1,MsgDat2,MsgDat3);
            break;

    //4 Beep Control : Start------                
        //Beep Requirement
        case OP_AUD_BEEP_REQ:
            if(BEEP_TYPE_SET_OFF != sAudioDat.sInfo.BeepType)
            {
                Audio_BeepQueueIn(MsgDat1,MsgDat2);
                if(BEEP_TYPE_KEY_NCK == MsgDat1)
                {
                    Audio_BeepQueueIn(MsgDat1,MsgDat2);
                }
            }
            break;
            
        //Config Beep Position
        case OP_AUD_BEEP_POS:
            if(MsgDat2 < MIX_TYPE_MAX)
            {
                sAudio.BeepSetupMask |= BEEP_MASK_POS;
                sAudioDat.sInfo.BeepPos = MsgDat2;  //Ignore Type Now, All use the same Beep Pos Setting
                //Check Currently Executing Config is Pos,if yes, stop,clear and re-config
                if(BEEP_SETUP_POS == sAudio.BeepSetupCtl)
                {
                    sAudio.BeepSetupMask |= BEEP_MASK_RECONFIG;  //Set Re-config Flag
                }
               // _SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BEEP,sAudioDat.sInfo.BeepType,sAudioDat.sAdv.BeepVol,sAudioDat.sInfo.BeepPos,0);
            }
            break;
        //Config Beep Volume
        case OP_AUD_BEEP_VOL:
            if(MsgDat2 < BEEP_VOL_SET_MAX)
            {
                sAudio.BeepSetupMask |= BEEP_MASK_VOL;
                sAudioDat.sAdv.BeepVol = MsgDat2; //Ignore Type Now, All use the same Beep Vol Setting
                //Check Currently Executing Config is Vol,if yes, stop,clear and re-config
                if(BEEP_SETUP_VOL == sAudio.BeepSetupCtl)
                {
                    sAudio.BeepSetupMask |= BEEP_MASK_RECONFIG; //Set Re-config Flag
                }
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BEEP,&sAudioDat.sAdv);
                //Audio_Variable2Eep();
            }
            break;

        //Config Beep Sub-Type: Only Saved...
        case OP_AUD_BEEP_SEL:
            if(MsgDat1 < BEEP_TYPE_SET_MAX)
            {
                sAudioDat.sInfo.BeepType = MsgDat1; 
                sAudio.BeepLast = BEEP_TYPE_NULL; //Clear Beep Last Memory
                if(BEEP_TYPE_SET_OFF == sAudioDat.sInfo.BeepType)
                {
                    sAudio.BeepCtl = BEEP_CTL_IDLE;
                    sAudio.BeepTail = 0;
                    sAudio.BeepHead = 0; 
                    sAudio.sBeepCurrent.Type = BEEP_TYPE_NULL; //Clear..
                }
                //_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BEEP,sAudioDat.sInfo.BeepType,sAudioDat.sAdv.BeepVol,sAudioDat.sInfo.BeepPos,0);
            }
            break;
    //4 Beep Control : End------    

        //System Bass Gain Increase
        case OP_AUD_BASS_GAIN_INC:
            if(sAudioDat.sBasic.sBass.Gain < AUDIO_BASS_MAX)
            {
                sAudioDat.sBasic.sBass.Gain++;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;

        //System Bass Gain Decrease    
        case OP_AUD_BASS_GAIN_DEC:
            if(sAudioDat.sBasic.sBass.Gain)
            {
                sAudioDat.sBasic.sBass.Gain--;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;
        
        //System Bass Gain Directly Select    
        case OP_AUD_BASS_GAIN_SEL:        //If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_BASS_MAX) && (MsgDat != sAudioDat.sBasic.sBass.Gain))
            {
#ifdef D_TONE_EQ
//		if(sAudioDat.sBasic.Type != GEQ_MODE_CUSTOM)
//		{
//			sAudioDat.sBasic.Type = GEQ_MODE_CUSTOM;
//			UserGeq[1].Gain =  sAudioDat.sBasic.sMid.Gain;
//			UserGeq[2].Gain =  sAudioDat.sBasic.sTreble.Gain;
//		}
		sAudioDat.sBasic.Type = GEQ_MODE_CUSTOM;
		UserGeq[0].Gain = MsgDat;
#endif
                sAudioDat.sBasic.sBass.Gain = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;

        //System Bass CF Increase        
        case OP_AUD_BASS_CF_INC:
            if(sAudioDat.sBasic.sBass.CF < AUDIO_BASS_CF_MAX)
            {
                sAudioDat.sBasic.sBass.CF++;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;    

        //System Bass CF Decrease        
        case OP_AUD_BASS_CF_DEC:
            if(sAudioDat.sBasic.sBass.CF)
            {
                sAudioDat.sBasic.sBass.CF--;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;

        //System Bass CF Directly Select    
        case OP_AUD_BASS_CF_SEL:        //If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_BASS_CF_MAX) && (MsgDat != sAudioDat.sBasic.sBass.CF))
            {
                sAudioDat.sBasic.sBass.CF = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;

        //System Bass Q Increase        
        case OP_AUD_BASS_Q_INC:
            if(sAudioDat.sBasic.sBass.Q < AUDIO_BASS_Q_MAX)
            {
                sAudioDat.sBasic.sBass.Q++;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;

        //System Bass Q Decrease        
        case OP_AUD_BASS_Q_DEC:
            if(sAudioDat.sBasic.sBass.Q)
            {
                sAudioDat.sBasic.sBass.Q--;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;

        //System Bass Q Directly Select
        case OP_AUD_BASS_Q_SEL:        //If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_BASS_Q_MAX) && (MsgDat != sAudioDat.sBasic.sBass.Q))
            {
                sAudioDat.sBasic.sBass.Q = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_BASS;
            }
            break;

        //System Middle Gain Increase    
        case OP_AUD_MID_GAIN_INC:
            if(sAudioDat.sBasic.sMid.Gain < AUDIO_MID_MAX)
            {
                sAudioDat.sBasic.sMid.Gain++;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;

        //System Middle Gain Increase        
        case OP_AUD_MID_GAIN_DEC:
            if(sAudioDat.sBasic.sMid.Gain)
            {
                sAudioDat.sBasic.sMid.Gain--;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;

        //System Middle Gain Directly Select
        case OP_AUD_MID_GAIN_SEL:        //If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_MID_MAX) && (MsgDat != sAudioDat.sBasic.sMid.Gain))
            {
#ifdef D_TONE_EQ
//		if(sAudioDat.sBasic.Type != GEQ_MODE_CUSTOM)
//		{
//			sAudioDat.sBasic.Type = GEQ_MODE_CUSTOM;
//			UserGeq[0].Gain =  sAudioDat.sBasic.sBass.Gain;
//			UserGeq[2].Gain =  sAudioDat.sBasic.sTreble.Gain;
//		}
		sAudioDat.sBasic.Type = GEQ_MODE_CUSTOM;
		UserGeq[1].Gain = MsgDat;
#endif
                sAudioDat.sBasic.sMid.Gain = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;

        //System Middle CF Increase        
        case OP_AUD_MID_CF_INC:
            if(sAudioDat.sBasic.sMid.CF < AUDIO_MID_CF_MAX)
            {
                sAudioDat.sBasic.sMid.CF++;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;    

        //System Middle CF Decrease        
        case OP_AUD_MID_CF_DEC:
            if(sAudioDat.sBasic.sMid.CF)
            {
                sAudioDat.sBasic.sMid.CF--;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;

        //System Middle CF Directly Select
        case OP_AUD_MID_CF_SEL:        //If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_MID_CF_MAX) && (MsgDat != sAudioDat.sBasic.sMid.CF))
            {
                sAudioDat.sBasic.sMid.CF = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;

        //System Middle Q Increase    
        case OP_AUD_MID_Q_INC:
            if(sAudioDat.sBasic.sMid.Q < AUDIO_MID_Q_MAX)
            {
                sAudioDat.sBasic.sMid.Q++;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;

        //System Middle Q Decrease        
        case OP_AUD_MID_Q_DEC:
            if(sAudioDat.sBasic.sMid.Q)
            {
                sAudioDat.sBasic.sMid.Q--;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;    

        //System Middle Q Directly Select
        case OP_AUD_MID_Q_SEL:            //If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_MID_Q_MAX) && (MsgDat != sAudioDat.sBasic.sMid.Q))
            {
                sAudioDat.sBasic.sMid.Q = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_MID;
            }
            break;

        //System Treble Gain Increase        
        case OP_AUD_TREBLE_GAIN_INC:
            if(sAudioDat.sBasic.sTreble.Gain < AUDIO_TREBLE_MAX)
            {
                sAudioDat.sBasic.sTreble.Gain++;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;

        //System Treble Gain Decrease        
        case OP_AUD_TREBLE_GAIN_DEC:
            if(sAudioDat.sBasic.sTreble.Gain)
            {
                sAudioDat.sBasic.sTreble.Gain--;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;

        //System Treble Gain Directly Select
        case OP_AUD_TREBLE_GAIN_SEL:        //If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_TREBLE_MAX) && (MsgDat != sAudioDat.sBasic.sTreble.Gain))
            {
#ifdef D_TONE_EQ
//		if(sAudioDat.sBasic.Type != GEQ_MODE_CUSTOM)
//		{
//			sAudioDat.sBasic.Type = GEQ_MODE_CUSTOM;
//			UserGeq[1].Gain =  sAudioDat.sBasic.sMid.Gain;
//			UserGeq[0].Gain =  sAudioDat.sBasic.sBass.Gain;
//		}
		sAudioDat.sBasic.Type = GEQ_MODE_CUSTOM;
		UserGeq[2].Gain = MsgDat;
#endif            
                sAudioDat.sBasic.sTreble.Gain = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;

        //System Treble CF Increase    
        case OP_AUD_TREBLE_CF_INC:
            if(sAudioDat.sBasic.sTreble.CF < AUDIO_TREBLE_CF_MAX)
            {
                sAudioDat.sBasic.sTreble.CF++;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;    

        //System Treble CF Decrease        
        case OP_AUD_TREBLE_CF_DEC:
            if(sAudioDat.sBasic.sTreble.CF)
            {
                sAudioDat.sBasic.sTreble.CF--;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;

        //System Treble CF Directly Select
        case OP_AUD_TREBLE_CF_SEL:    //If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_TREBLE_CF_MAX) && (MsgDat != sAudioDat.sBasic.sTreble.CF))
            {
                sAudioDat.sBasic.sTreble.CF = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;

        //System Treble Q Increase    
        case OP_AUD_TREBLE_Q_INC:
            if(sAudioDat.sBasic.sTreble.Q < AUDIO_TREBLE_Q_MAX)
            {
                sAudioDat.sBasic.sTreble.Q++;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;

        //System Treble Q Decrease        
        case OP_AUD_TREBLE_Q_DEC:
            if(sAudioDat.sBasic.sTreble.Q)
            {
                sAudioDat.sBasic.sTreble.Q--;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;    

        //System Treble Q Directly Select
        case OP_AUD_TREBLE_Q_SEL://If Newly required is same as currently, Ignore!
            if((MsgDat <= AUDIO_TREBLE_Q_MAX) && (MsgDat != sAudioDat.sBasic.sTreble.Q))
            {
                sAudioDat.sBasic.sTreble.Q = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_TREBLE;
            }
            break;
            
        //Balance Increase
        case OP_AUD_BAL_INC:
            if(sAudioDat.sBasic.Balance < AUDIO_BALANCE_MAX)
            {
                sAudioDat.sBasic.Balance++;
		            sAudio.Balance_media = 	sAudioDat.sBasic.Balance;
                sAudio.CommonCode = AUDIO_COMMON_BF;
                sAudio.BalFadMask |= BF_MASK_BAL;
            }
            break;
            
        //Balance Decrease
        case OP_AUD_BAL_DEC:
            if(sAudioDat.sBasic.Balance)
            {
                sAudioDat.sBasic.Balance--;
		            sAudio.Balance_media = 	sAudioDat.sBasic.Balance;
                sAudio.CommonCode = AUDIO_COMMON_BF;
                sAudio.BalFadMask |= BF_MASK_BAL;
            }
            break;

        //Balance Select
        case OP_AUD_BAL_SEL:    //If Newly required is same as currently, Ignore!
            if(((MsgDat) <= AUDIO_BALANCE_MAX) && ((MsgDat) != sAudioDat.sBasic.Balance))
            {
                sAudioDat.sBasic.Balance = MsgDat;
		            sAudio.Balance_media = sAudioDat.sBasic.Balance;
                sAudio.CommonCode = AUDIO_COMMON_BF;
                sAudio.BalFadMask |= BF_MASK_BAL;
            }
            break;
            
        //Fader Increase
        case OP_AUD_FAD_INC:
            if(sAudioDat.sBasic.Fader < AUDIO_FADER_MAX)
            {
                sAudioDat.sBasic.Fader++;
		  sAudio.Fader_Media = sAudioDat.sBasic.Fader;
                sAudio.CommonCode = AUDIO_COMMON_BF;
                sAudio.BalFadMask |= BF_MASK_FAD;
            }
            break;
            
        //Fader Decrease
        case OP_AUD_FAD_DEC:
            if(sAudioDat.sBasic.Fader)
            {
                sAudioDat.sBasic.Fader--;
		  sAudio.Fader_Media = sAudioDat.sBasic.Fader;
                sAudio.CommonCode = AUDIO_COMMON_BF;
                sAudio.BalFadMask |= BF_MASK_FAD;
            }
            break;
            
        //Fader Select
        case OP_AUD_FAD_SEL:    //If Newly required is same as currently, Ignore!
            if(((MsgDat) <= AUDIO_FADER_MAX) && ((MsgDat) != sAudioDat.sBasic.Fader))
            {
                sAudioDat.sBasic.Fader = MsgDat;
		            sAudio.Fader_Media = sAudioDat.sBasic.Fader;
                sAudio.CommonCode = AUDIO_COMMON_BF;
                sAudio.BalFadMask |= BF_MASK_FAD;
            }
            break;

        //Bal&Fad Preset Sel

        case OP_AUD_BF_PRESET:
		  if(sAudioDat.sBasic.Fader != (AUDIO_FADER_MAX/2))
		  {
                	sAudioDat.sBasic.Fader = AUDIO_FADER_MAX/2;
			sAudio.Fader_Media = sAudioDat.sBasic.Fader;
			sAudio.BalFadMask |=  BF_MASK_FAD;
			sAudio.CommonCode = AUDIO_COMMON_BF;
		  }
		  if(sAudioDat.sBasic.Balance != (AUDIO_BALANCE_MAX/2))
		  {
		  	sAudioDat.sBasic.Balance = AUDIO_BALANCE_MAX/2;
			sAudio.Balance_media = 	sAudioDat.sBasic.Balance;
			sAudio.BalFadMask |=  BF_MASK_BAL;
			sAudio.CommonCode = AUDIO_COMMON_BF;
		  }
            break;

        //Loudness On/Off Set
        case OP_AUD_LOUD_SET:
            if((MsgDat != sAudioDat.sBasic.sLoudnessMode) && (MsgDat <= LOUDNESS_ON))
            {
                sAudio.LoudnessMask |= LOUD_MASK_ON_OFF;
                sAudioDat.sBasic.sLoudnessMode = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_LOUDNESS;
                sAudio.LoudnessCtl = OPERATION_0;  //Reset Control Step, to re-do every step
                //Feedback to HMI to Sync Loudness
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_LOUDNESS,&sAudioDat.sBasic);
            }
            break;

        //Loudness Bass Cut off frequency
        case OP_AUD_LDB_COF:
            if((MsgDat < AUDIO_LOUD_B_COF_MAX) && (MsgDat != sAudioDat.sBasicBK.sLoudness.BassCutOff))
            {
                sAudio.LoudnessMask |= LOUD_MASK_BASS_COF;
                sAudioDat.sBasicBK.sLoudness.BassCutOff = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_LOUDNESS;
                sAudio.LoudnessCtl = OPERATION_0;  //Reset Control Step, to re-do every step
                //Feedback to HMI to Sync Loudness
               // _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_LOUDNESS,&sAudioDat.sBasic);
            }    
            break;

        //Loudness Treble Centre Frequency
        case OP_AUD_LDT_CF:
            if((MsgDat < AUDIO_LOUD_T_CF_MAX) && (MsgDat != sAudioDat.sBasicBK.sLoudness.TrebleCentre))
            {
                sAudio.LoudnessMask |= LOUD_MASK_TREBLE_CF;
                sAudioDat.sBasicBK.sLoudness.TrebleCentre = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_LOUDNESS;
                sAudio.LoudnessCtl = OPERATION_0;  //Reset Control Step, to re-do every step
                //Feedback to HMI to Sync Loudness
                //_SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_LOUDNESS,&sAudioDat.sBasic);
            }    
            break;    

        //Subwoofer: On, Off
        case OP_AUD_SW_SET:
            if((MsgDat <= SUBWOOFER_ON) && (MsgDat != sAudioDat.sBasic.sSubWooferSwitch))
            {
                sAudioDat.sBasic.sSubWooferSwitch = MsgDat;
                sAudio.SwCtl = OPERATION_0;
                sAudio.CommonCode = AUDIO_COMMON_SUBWOOFER;
                //Feedback to HMI to Sync SubWoofer
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_SUBWOOFER,&sAudioDat.sBasic);
            }
            break;

        //Subwoofer: Cut off Frequency
        case OP_AUD_SW_COF:    
            if((MsgDat <= AUDIO_SW_COF_MAX) && (MsgDat != sAudioDat.sBasicBK.sSubWoofer.CoF))
            {
                sAudioDat.sBasicBK.sSubWoofer.CoF = MsgDat;
                sAudio.SwCtl = OPERATION_0;
                sAudio.CommonCode = AUDIO_COMMON_SUBWOOFER;
                //Feedback to HMI to Sync SubWoofer
               // _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_SUBWOOFER,&sAudioDat.sBasic);
            }
            break;

        //Subwoofer: Gain
        case OP_AUD_SW_GAIN:
            if((MsgDat <= AUDIO_SW_GAIN_MAX) && (MsgDat != sAudioDat.sBasicBK.sSubWoofer.Level))
            {            
                sAudioDat.sBasicBK.sSubWoofer.Level = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_SUBWOOFER;
                sAudio.SwCtl = OPERATION_0;
                //Feedback to HMI to Sync SubWoofer
               // _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_SUBWOOFER,&sAudioDat.sBasic);
            }
            break;

        //Subwoofer: Q
        case OP_AUD_SW_Q:
            if((MsgDat <= AUDIO_SW_Q_MAX) && (MsgDat != sAudioDat.sBasicBK.sSubWoofer.Slope))
            {            
                sAudioDat.sBasicBK.sSubWoofer.Slope = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_SUBWOOFER;
                sAudio.SwCtl = OPERATION_0;
                //Feedback to HMI to Sync SubWoofer
                //_SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_SUBWOOFER,&sAudioDat.sBasic);
            }
            break;    

    //4CrossOver: Start
        //Select Xover Preset
        case OP_AUD_XOVER_PRESET:
            if((MsgDat <= XOVER_PRESET_MAX) && (MsgDat != sAudioDat.sAdv.XoverPreset))
            {
                uint8_t Temp;
                //Sync Newly Preset's Parameters
                sAudioDat.sAdv.XoverPreset = MsgDat;
                if(XOVER_PRESET_CUSTOM == sAudioDat.sAdv.XoverPreset)
                {
                    for(Temp = 0; Temp < 3; Temp++)
                    {
                        sAudioDat.sAdv.sCustomXover[Temp].Level = sAudioKeep.sBakXover[Temp].Level;
                        sAudioDat.sAdv.sCustomXover[Temp].CoF = sAudioKeep.sBakXover[Temp].CoF;
                        sAudioDat.sAdv.sCustomXover[Temp].Slope = sAudioKeep.sBakXover[Temp].Slope;
                    }
                }
                else
                {
                    for(Temp = 0; Temp < 3; Temp++)
                    {
                        sAudioDat.sAdv.sCustomXover[Temp].Level = Tab_Xover_Preset[sAudioDat.sAdv.XoverPreset * 3 + Temp].Level;
                        sAudioDat.sAdv.sCustomXover[Temp].CoF = Tab_Xover_Preset[sAudioDat.sAdv.XoverPreset * 3 + Temp].CoF;
                        sAudioDat.sAdv.sCustomXover[Temp].Slope = Tab_Xover_Preset[sAudioDat.sAdv.XoverPreset * 3 + Temp].Slope;
                    }
                }
                sAudio.XoverMask |= (XOVER_MASK_FRONT|XOVER_MASK_REAR|XOVER_MASK_SW); // 
                sAudio.CommonCode = AUDIO_COMMON_XOVER;
                sAudio.XoverCtl = OPERATION_0;
                //Feedback to HMI to Sync X Over
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_XOVER,&sAudioDat.sAdv);
            }
            break;

        //Set Xover's Level
        case OP_AUD_XOVER_LEVEL:
            if(MsgDat2 <= XOVER_LEVEL_MAX)
            {
                uint8_t Temp;
                if(XOVER_PRESET_CUSTOM != sAudioDat.sAdv.XoverPreset)
                {
                    for(Temp = 0; Temp < 3; Temp++)
                    {
                        sAudioKeep.sBakXover[Temp].Level = sAudioDat.sAdv.sCustomXover[Temp].Level;
                        sAudioKeep.sBakXover[Temp].CoF = sAudioDat.sAdv.sCustomXover[Temp].CoF;
                        sAudioKeep.sBakXover[Temp].Slope = sAudioDat.sAdv.sCustomXover[Temp].Slope;
                    }
                }
                sAudioDat.sAdv.XoverPreset = XOVER_PRESET_CUSTOM;
                sAudioDat.sAdv.sCustomXover[MsgDat1].Level = MsgDat2;
                sAudioKeep.sBakXover[MsgDat1].Level = MsgDat2;
                sAudio.XoverMask |= (0x01 << (MsgDat1 + 1));
                sAudio.CommonCode = AUDIO_COMMON_XOVER;
                sAudio.XoverCtl = OPERATION_0;
                //Feedback to HMI to Sync X Over
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_XOVER,&sAudioDat.sAdv);
            }
            break;

        //Set Cut Off Frequency
        case OP_AUD_XOVER_COF:
            if(MsgDat2 < XOVER_COF_MAX)
            {
                uint8_t Temp;
                if(XOVER_PRESET_CUSTOM != sAudioDat.sAdv.XoverPreset)
                {
                    for(Temp = 0; Temp < 3; Temp++)
                    {
                        sAudioKeep.sBakXover[Temp].Level = sAudioDat.sAdv.sCustomXover[Temp].Level;
                        sAudioKeep.sBakXover[Temp].CoF = sAudioDat.sAdv.sCustomXover[Temp].CoF;
                        sAudioKeep.sBakXover[Temp].Slope = sAudioDat.sAdv.sCustomXover[Temp].Slope;
                    }
                }
                sAudioDat.sAdv.XoverPreset = XOVER_PRESET_CUSTOM;
                sAudioDat.sAdv.sCustomXover[MsgDat1].CoF = MsgDat2;
                sAudioKeep.sBakXover[MsgDat1].CoF = MsgDat2;
                sAudio.XoverMask |= (0x01 << (MsgDat1 + 1));
                sAudio.CommonCode = AUDIO_COMMON_XOVER;
                sAudio.XoverCtl = OPERATION_0;
                //Feedback to HMI to Sync X Over
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_XOVER,&sAudioDat.sAdv);
            }
            break;

        //Set Slope
        case OP_AUD_XOVER_SLOPE:
	    if(MsgDat2 <= XOVER_SLOPE_MAX)
            {
                uint8_t Temp;
                if(XOVER_PRESET_CUSTOM != sAudioDat.sAdv.XoverPreset)
                {
                    for(Temp = 0; Temp < 3; Temp++)
                    {
                        sAudioKeep.sBakXover[Temp].Level = sAudioDat.sAdv.sCustomXover[Temp].Level;
                        sAudioKeep.sBakXover[Temp].CoF = sAudioDat.sAdv.sCustomXover[Temp].CoF;
                        sAudioKeep.sBakXover[Temp].Slope = sAudioDat.sAdv.sCustomXover[Temp].Slope;
                    }
                }
                sAudioDat.sAdv.XoverPreset = XOVER_PRESET_CUSTOM;
                sAudioDat.sAdv.sCustomXover[MsgDat1].Slope = MsgDat2;
                sAudioKeep.sBakXover[MsgDat1].Slope = MsgDat2;
                sAudio.XoverMask |= (0x01 << (MsgDat1 + 1));
                sAudio.CommonCode = AUDIO_COMMON_XOVER;
                sAudio.XoverCtl = OPERATION_0;
                //Feedback to HMI to Sync X Over
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_XOVER,&sAudioDat.sAdv);
            }
            break;
    //4 CrossOver: End            

        //GEQ Mode Increase
        case OP_AUD_GEQ_INC:
            if(sAudioDat.sBasic.Type < GEQ_MODE_MAX)
            {
                sAudioDat.sBasic.Type++;
                //Load Preset Datum to Output Buffer...
                
                sAudio.CommonCode = AUDIO_COMMON_GEQ;
                sAudio.GeqMask = 0xFFFF;
                sAudio.GeqStep = OPERATION_0; //Reset Control Step, to re-do every step
                //Feedback to HMI to EQ Setting
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_GEQ,&sAudioDat.sBasic);
            }
            break;

        //GEQ Mode Decrease
        case OP_AUD_GEQ_DEC:
            if(sAudioDat.sBasic.Type)
            {    
                sAudioDat.sBasic.Type--;
                //Load Preset Datum to Output Buffer...
                sAudio.CommonCode = AUDIO_COMMON_GEQ;
                sAudio.GeqMask = 0xFFFF;
                sAudio.GeqStep = OPERATION_0; //Reset Control Step, to re-do every step
                //Feedback to HMI to EQ Setting
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_GEQ,&sAudioDat.sBasic);
            }
            break;

        //GEQ Mode Directly Select
        case OP_AUD_GEQ_SEL:    //If Newly required is same as currently, Ignore!
            if((MsgDat <= GEQ_MODE_MAX) && (MsgDat != sAudioDat.sBasic.Type))
            {
                sAudioDat.sBasic.Type = MsgDat;
           #ifdef D_TONE_EQ
		//    if(GEQ_MODE_CUSTOM != sAudioDat.sBasic.Type)
		if( sAudioDat.sBasic.Type<=GEQ_MODE_SPEECH)		
		{
			#ifdef D_TUNER_EQ  //snake20160905
			if(sAudio.SysChannel == SRC_TYPE_TUNER)
			{
                sAudioDat.sBasic.sBass.Gain = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 0].Gain;
                sAudioDat.sBasic.sMid.Gain = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 1].Gain;
                sAudioDat.sBasic.sTreble.Gain = Tab_Tone_Tuner_Eq[3*sAudioDat.sBasic.Type + 2].Gain;
        	}
			else
			{
				sAudioDat.sBasic.sBass.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 0].Gain;
				sAudioDat.sBasic.sMid.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 1].Gain;
				sAudioDat.sBasic.sTreble.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 2].Gain;
			}
			#else
				sAudioDat.sBasic.sBass.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 0].Gain;
				sAudioDat.sBasic.sMid.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 1].Gain;
				sAudioDat.sBasic.sTreble.Gain = Tab_Tone_Eq[3*sAudioDat.sBasic.Type + 2].Gain;
			#endif
		}
		else //GEQ_MODE_CUSTOM
		{
			sAudioDat.sBasic.sBass.Gain = g_tSysRomData.tAudioBlock.BassGain;
			sAudioDat.sBasic.sMid.Gain = g_tSysRomData.tAudioBlock.MidGain;
			sAudioDat.sBasic.sTreble.Gain = g_tSysRomData.tAudioBlock.TrebleGain;
		}
		Audio_OpQueueIn(AUDIO_COMMON_BASS);
		Audio_OpQueueIn(AUDIO_COMMON_MID);
		Audio_OpQueueIn(AUDIO_COMMON_TREBLE);
           #else
		{
			uint8_t i;
			//Load Preset Datum to Output Buffer...
			if(GEQ_MODE_CUSTOM != sAudioDat.sBasic.Type)
			{
				for(i = 0; i < GEQ_MAX_NUM; i++)
				{
					sAudioDat.sGeq.sBuffer[i].CF = Tab_Geq_Preset_Filter[GEQ_MAX_NUM*sAudioDat.sBasic.Type + i].CF;
					sAudioDat.sGeq.sBuffer[i].Gain = Tab_Geq_Preset_Filter[GEQ_MAX_NUM*sAudioDat.sBasic.Type + i].Gain;
					sAudioDat.sGeq.sBuffer[i].Q = Tab_Geq_Preset_Filter[GEQ_MAX_NUM*sAudioDat.sBasic.Type + i].Q;
					sAudioDat.sGeq.GainTbl[3 * i + 0] = Tab_Geq_Preset_Gain[3*(GEQ_MAX_NUM*sAudioDat.sBasic.Type + i)+0];
					sAudioDat.sGeq.GainTbl[3 * i + 1] = Tab_Geq_Preset_Gain[3*(GEQ_MAX_NUM*sAudioDat.sBasic.Type + i)+1];
					sAudioDat.sGeq.GainTbl[3 * i + 2] = Tab_Geq_Preset_Gain[3*(GEQ_MAX_NUM*sAudioDat.sBasic.Type + i)+2];
				}
			}
			else
			{
				for(i = 0; i < GEQ_MAX_NUM; i++)
				{
					sAudioDat.sGeq.sBuffer[i].CF = sAudioKeep.sBakGeq[i].CF;
					sAudioDat.sGeq.sBuffer[i].Gain = sAudioKeep.sBakGeq[i].Gain;
					sAudioDat.sGeq.sBuffer[i].Q = sAudioKeep.sBakGeq[i].Q;
					sAudioDat.sGeq.GainTbl[3 * i + 0] = sAudioKeep.sBakGain[3 * i + 0];
					sAudioDat.sGeq.GainTbl[3 * i + 1] = sAudioKeep.sBakGain[3 * i + 1];
					sAudioDat.sGeq.GainTbl[3 * i + 2] = sAudioKeep.sBakGain[3 * i + 2];
				}
			}
		}
		sAudio.CommonCode = AUDIO_COMMON_GEQ;
		sAudio.GeqMask = 0xFFFE; //Update all but Initial
		sAudio.GeqStep = OPERATION_0; //Reset Control Step, to re-do every step
           #endif     
		//Feedback to HMI to EQ Setting
		_SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_GEQ,&sAudioDat.sBasic);
            }
            break;
        //Set newly GEQ_BAND's Gain
        case OP_AUD_GEQ_GAIN:
            if((MsgDat1 < GEQ_MAX_NUM) && (MsgDat2 <= AUDIO_GEQ_GAIN_MAX))
            {
                if(GEQ_MODE_CUSTOM != sAudioDat.sBasic.Type)
                {
                    uint8_t i;
                    for(i = 0; i < GEQ_MAX_NUM; i++)
                    {
                        sAudioKeep.sBakGeq[i].Gain = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGeq[i].CF = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGeq[i].Q = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGain[i+0] = sAudioDat.sGeq.GainTbl[i+0];
                        sAudioKeep.sBakGain[i+1] = sAudioDat.sGeq.GainTbl[i+1];
                        sAudioKeep.sBakGain[i+2] = sAudioDat.sGeq.GainTbl[i+2];
                     }
                }
                sAudioDat.sGeq.sBuffer[MsgDat1].Gain = MsgDat2;
                sAudioKeep.sBakGeq[MsgDat1].Gain = MsgDat2;
                sAudioDat.sGeq.GainTbl[3 * MsgDat1 + sAudioDat.sGeq.sBuffer[MsgDat1].CF] = MsgDat2;
                sAudioKeep.sBakGain[3 * MsgDat1 + sAudioDat.sGeq.sBuffer[MsgDat1].CF] = MsgDat2;
                sAudio.GeqMask |= (0x01 << (MsgDat1 + 1));
                sAudio.GeqStep = OPERATION_0; //Reset Control Step, to re-do every step
                sAudio.CommonCode = AUDIO_COMMON_GEQ;
                //Feedback to HMI to EQ Setting
		 _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_GEQ,&sAudioDat.sBasic);
            }
            break;

        //Set newly GEQ_BAND's Q
        case OP_AUD_GEQ_Q:
            if((MsgDat1 < GEQ_MAX_NUM) && (MsgDat2 <= AUDIO_GEQ_Q_MAX))
            {
                if(GEQ_MODE_CUSTOM != sAudioDat.sBasic.Type)
                {
                    uint8_t i;
                    for(i = 0; i < GEQ_MAX_NUM; i++)
                    {
                        sAudioKeep.sBakGeq[i].Gain = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGeq[i].CF = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGeq[i].Q = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGain[i+0] = sAudioDat.sGeq.GainTbl[i+0];
                        sAudioKeep.sBakGain[i+1] = sAudioDat.sGeq.GainTbl[i+1];
                        sAudioKeep.sBakGain[i+2] = sAudioDat.sGeq.GainTbl[i+2];
                     }
                }
                sAudioDat.sGeq.sBuffer[MsgDat1].Q = MsgDat2;
                sAudioKeep.sBakGeq[MsgDat1].Q = MsgDat2;
                sAudio.GeqMask |= (0x01 << (MsgDat1 + 1));
                sAudio.GeqStep = OPERATION_0; //Reset Control Step, to re-do every step
                sAudio.CommonCode = AUDIO_COMMON_GEQ;
                //Feedback to HMI to EQ Setting
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_GEQ,&sAudioDat.sBasic);
            }
            break;    

        //Set newly GEQ_BAND's CF
        case OP_AUD_GEQ_CF:
            if((MsgDat1 < GEQ_MAX_NUM) && (MsgDat2 <= AUDIO_GEQ_CF_MAX))
            {
                if(GEQ_MODE_CUSTOM != sAudioDat.sBasic.Type)
                {
                    uint8_t i;
                    for(i = 0; i < GEQ_MAX_NUM; i++)
                    {
                        sAudioKeep.sBakGeq[i].Gain = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGeq[i].CF = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGeq[i].Q = sAudioDat.sGeq.sBuffer[i].Gain;
                        sAudioKeep.sBakGain[i+0] = sAudioDat.sGeq.GainTbl[i+0];
                        sAudioKeep.sBakGain[i+1] = sAudioDat.sGeq.GainTbl[i+1];
                        sAudioKeep.sBakGain[i+2] = sAudioDat.sGeq.GainTbl[i+2];
                     }
                }
                sAudioDat.sGeq.sBuffer[MsgDat1].CF = MsgDat2;
                sAudioKeep.sBakGeq[MsgDat1].CF = MsgDat2;
                sAudio.GeqMask |= (0x01 << (MsgDat1 + 1));
                sAudio.GeqStep = OPERATION_0; //Reset Control Step, to re-do every step
                sAudio.CommonCode = AUDIO_COMMON_GEQ;
                //Feedback to HMI to EQ Setting
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_GEQ,&sAudioDat.sBasic);
            }
            break;    

        //Set DC Filter
        case OP_AUD_DC_SET:
            sAudioDat.sAdv.DcFilter = MsgDat;
            sAudio.CommonCode = AUDIO_COMMON_DC;
            //Feedback to HMI to Sync DC Filter Setting
            _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_DC,&sAudioDat.sAdv);
            break;    

        case OP_AUD_RDC_SET:
            break;

        //Select Delay Line Preset
        case OP_AUD_DELAY_PRESET:
            if((MsgDat <= DELAY_PRESET_MAX) && (MsgDat != sAudioDat.sAdv.DelayPreset))
            {
                sAudioDat.sAdv.DelayPreset = MsgDat;
                if(DELAY_PRESET_CUSTOM == sAudioDat.sAdv.DelayPreset)
                {
                    Memcpy_U8(sAudioKeep.BakDelay,sAudioDat.sAdv.DelayCustom,DELAY_LINE_MAX);
                }
                else
                {
                    Memcpy_U8((uint8_t *)(&Tab_DelayPreset[(sAudioDat.sAdv.CarStyle * DELAY_PRESET_MAX + sAudioDat.sAdv.DelayPreset) * DELAY_LINE_MAX]),sAudioDat.sAdv.DelayCustom,DELAY_LINE_MAX);
                }
                sAudio.DelayLineMask = 0x7F; //Reconfig All Delay Setting
                sAudio.DelayCtl = OPERATION_0;    //Reset Delay Ctl 
                sAudio.CommonCode = AUDIO_COMMON_DELAY;
                //Feedback to HMI to Sync Delay Setting
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_DELAY,&sAudioDat.sAdv);
            }
            break;

        //Save Currently Setting to Preset
    #if 0    
        case OP_AUD_DELAY_SAVE:
            if(MsgDat <= DELAY_PRESET_MAX)
            {
                sAudioDat.sAdv.DelayPreset = MsgDat;
                Memcpy_U8(sAudioDat.sAdv.DelayBuffer,&sAudioDat.sInfo.DelayCustom[(sAudioDat.sAdv.CarStyle * (DELAY_PRESET_MAX - 1) + sAudioDat.sAdv.DelayPreset - 1) * DELAY_LINE_MAX],DELAY_LINE_MAX);
                //Update Preset Display  //Feedback to HMI to Sync Delay Setting
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_DELAY,&sAudioDat.sAdv);
            }
            break;
    #endif
        //Set Specific Speaker's Delay
        case OP_AUD_DELAY_SPEAKER:
            if((MsgDat2 <= PRESET_VAL_MAX) && (MsgDat1 <= DELAY_LINE_MAX))
            {
                if(DELAY_PRESET_CUSTOM != sAudioDat.sAdv.DelayPreset)
                {
                    Memcpy_U8(sAudioDat.sAdv.DelayCustom,sAudioKeep.BakDelay,DELAY_LINE_MAX);
                }
                sAudioDat.sAdv.DelayPreset = DELAY_PRESET_CUSTOM;
                sAudioKeep.BakDelay[MsgDat1] = MsgDat2;
                sAudioDat.sAdv.DelayCustom[MsgDat1] = MsgDat2;
                sAudio.DelayLineMask |= (DELAY_MASK_FL << MsgDat1);
                sAudio.DelayCtl = OPERATION_0;    //Reset Delay Ctl 
                sAudio.CommonCode = AUDIO_COMMON_DELAY;
                //Feedback to HMI to Sync Delay Setting
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_DELAY,&sAudioDat.sAdv);
            }
            break;

        case OP_AUD_PHASE_SHIFT:
            if((MsgDat2 <= PHASE_SHIFT_ON) && (MsgDat1 <= CHANNEL_SWR))
            {
            #if 0    
                if(PHASE_SHIFT_ON == MsgDat2)
                {
                    sAudioDat.sInfo.PhaseShifter |= (0x01 << MsgDat1);
                }
                else
                {
                    sAudioDat.sInfo.PhaseShifter &= ~(0x01 << MsgDat1);
                }
            #else
                sAudioDat.sAdv.PhaseShifter[MsgDat1] = MsgDat2;
            #endif
                sAudio.CommonCode = AUDIO_COMMON_PHASESHIFT;
                sAudio.PhaseCtl = 0;
                sAudio.PhaseMask = 0x01;
                //Feedback to HMI to Sync Delay Setting
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_PHASESHIFT,&sAudioDat.sAdv);
            }
            break;

        //UltraBass Setting : On OFF
        case OP_AUD_UBASS_SET:
            if(MsgDat <= UBASS_ENABLE)
            {
                sAudioDat.sAdv.sUltraBass.Setting = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_UBASS;
                sAudio.UltraBassMask |= UBASS_MASK_ENABLE;
                //Feedback to HMI to Sync
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_UBASS,&sAudioDat.sAdv);
            }
            break;

        //UltraBass Enhancement Gain
        case OP_AUD_UBASS_LEVEL:
            if(MsgDat <= UBASS_BST_MAX)
            {
                sAudioDat.sAdv.sUltraBass.BoostLevel = MsgDat;
                sAudio.CommonCode = AUDIO_COMMON_UBASS;
                sAudio.UltraBassMask |= UBASS_MASK_LEVEL;
                //Feedback to HMI to Sync
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_UBASS,&sAudioDat.sAdv);
            }
            break;

        //UltraBass Scaler
        case OP_AUD_UBASS_SCALER:
        #if 0  //Closed, Use Dynamic Scaler Setting
            sAudioDat.sInfo.UbassTargetLev = MsgDat;
            sAudio.CommonCode = AUDIO_COMMON_UBASS;
            sAudio.UltraBassMask |= UBASS_MASK_SCALER;
            //Feedback to HMI to Sync
            _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_UBASS,&sAudioDat.sInfo);
        #endif
            break;

        case OP_AUD_CHANNEL_MODE:
            sAudioDat.sInfo.ChanModeSet = MsgDat;
            break;

        case OP_AUD_SW_CEN_SET:
            sAudioDat.sInfo.SwCenMode = MsgDat;
            break;

        //Set Newly Car Style
        case OP_AUD_CAR_STYLE:
            if(MsgDat < CAR_STYLE_MAX)
            {
                sAudioDat.sAdv.CarStyle = MsgDat;
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_ADV,&sAudioDat.sAdv);
                //Audio_Variable2Eep();
                //Sync Datum
                
            }
            break;    

        //Source Scaler
        case OP_AUD_SRC_SCALER:
            if((MsgDat2 <= SRC_SCALER_MAX) && (MsgDat1 < SS_SRC_MAX))
            {
                sAudioDat.sGain.ScalerTbl[MsgDat1] = MsgDat2;
                //Execute Immediately: !!! Only Execute next time go into  specific source
                if(1 == Audio_ChgScalerChk(MsgDat1))
                {
                    sAudio.CommonCode = AUDIO_COMMON_SRC_SCALER;
                }
                //Feedback
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_CHGAIN,&sAudioDat.sGain);
                //Audio_Variable2Eep();
            }
            break;   

        case OP_AUD_TUNER_SCALER:
            if(0 == MsgDat)//FM
            {
                if(sAudioDat.sGain.ScalerTbl[SS_SRC_TUNER] != ((AUDIO_SRC_SCALER_MAX / 2) - 2))
                {
                    sAudioDat.sGain.ScalerTbl[SS_SRC_TUNER] = ((AUDIO_SRC_SCALER_MAX / 2) - 2);
                    sAudio.CommonCode = AUDIO_COMMON_SRC_SCALER;
                }
            }
            else if(1 == MsgDat)//AM
            {
                if(sAudioDat.sGain.ScalerTbl[SS_SRC_TUNER] != ((AUDIO_SRC_SCALER_MAX / 2) - 1))
                {
                    sAudioDat.sGain.ScalerTbl[SS_SRC_TUNER] = ((AUDIO_SRC_SCALER_MAX / 2) - 1);
                    sAudio.CommonCode = AUDIO_COMMON_SRC_SCALER;
                }
            }
            break;   

        case OP_AUD_CHANNEL_GAIN:
            if((MsgDat1 <= CHANNEL_SWR) && (MsgDat2 <= 6))
            {
                sAudioDat.sGain.ChanGainTbl[MsgDat1] = MsgDat2;
                sAudio.ChanGainMask |= (0x01 << MsgDat1);
                sAudio.ChanGainCtl = 0;
                sAudio.CommonCode = AUDIO_COMMON_CHANGAIN;
                //Feedback
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_CHGAIN,&sAudioDat.sGain);
                //Audio_Variable2Eep();
            }
            break;

        case OP_AUD_CLICK_CLACK:
            Audio_CC_QueueIn(MsgDat1,MsgDat2);
            break;

   //4 Mix Attribute....     
        case OP_AUD_MIX_POS:        //Pos: FL,FR,Front
            if((MsgDat >= MIX_TYPE_FL) && (MsgDat <= MIX_TYPE_FRONT))
            {
                sAudioDat.sBasic.MixPos = MsgDat;
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BASIC,&sAudioDat.sBasic);
            }
            break;

        case OP_AUD_MIX_LEVEL:
            if((MsgDat > MIX_ATTN_SET_OFF) && (MsgDat <= MIX_ATTN_SET_HIGH))
            {
                sAudioDat.sBasic.MixAttn = MsgDat;
                _SendMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_BASIC,&sAudioDat.sBasic);
            }
            break;

        case OP_AUD_MIX_REQ:
		sAudioDat.sBasicBK.Mix_Set_Flag = MsgDat2;   // xjh add ó?ò?2￥±¨MUTE ON ??óDá￠?′MUTE
            if(1 == MsgDat2)
            {
                if((SRC_TYPE_BT_PHONE != sAudio.SysChannel) && (SRC_TYPE_3G_PHONE != sAudio.SysChannel)	\
					&& (SRC_TYPE_CAR_TBOX != sAudio.SysChannel))	//add tbox audio channel ,dont mix, 2014-12-16
                {
                    Audio_MixQueueIn(SRC_TYPE_NAVI_AUDIO,sAudioDat.sBasic.MixPos);// Mix In
                }
            }
            else
            {
                Audio_MixQueueIn(SRC_TYPE_NAVI_AUDIO,MIX_TYPE_OFF);//Mix Out
            }
            break;
         case OP_AUD_SYNC:
            Audio_VariableCheck();
            break;
           
        default:
            break;
    }
    
    //Queue In Valid Operation Triggerred by Message
    if(AUDIO_COMMON_NULL != sAudio.CommonCode)
    {
        Audio_OpQueueIn(sAudio.CommonCode);
    }

    #undef MsgSid 
    #undef MsgDat 
    #undef MsgDat1
    #undef MsgDat2 
    #undef MsgDat3 
}
/**********************************************************
 * @function    Audio_InputExecute
 * @brief      Execute Specific Action!!!!!!!!!!
 * @param      None                    
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_InputExecute(uint8_t Req)
{
    uint8_t Result = SUBLAYER_DOING;

    switch(Req)
    {
        //Set Front System Volume
        case AUDIO_COMMON_VOL:
		audio_printf(_T("SysCh: %d  \n",sAudio.SysChannel));

		//According Mix Status, Adjust rightly Volume
		if(MIX_STATUS_NAVI & sAudio.MixStatus) // BT Caling has highest priority
		{
			audio_printf(_T("SysNavi : %d  \n",sAudio.SysChannel));
			
			if((1 == g_tMcuDevState.uIOState.bits.Reverse_Flag) || (1 == g_tMcuDevState.uDetect.bits.Blind_Flag))
			{
				Result = Audio_SetVolume(sAudioKeep.CurrentlyVol,SYSTEM_FRONT);    
			}
			else
			{
				//Result = Audio_SetNaviVol(sAudioKeep.CurrentlyVol);
				Result = Audio_SetVolume(sAudioKeep.CurrentlyVol,SYSTEM_FRONT);    
			} 
		}
		else
		{
			Result = Audio_SetVolume(sAudioKeep.CurrentlyVol,SYSTEM_FRONT);    
		}			
		break;

        //Set Rear System Volume
        case AUDIO_COMMON_REARVOL:
            Result = Audio_SetVolume(sAudioKeep.RearVol,SYSTEM_REAR);
            break;

        //Set Bass
        case AUDIO_COMMON_BASS:
            Result = Audio_SetBass(sAudioDat.sBasic.sBass,SYSTEM_FRONT);
            break;

        //Set Middle
        case AUDIO_COMMON_MID:
            Result = Audio_SetMid(sAudioDat.sBasic.sMid,SYSTEM_FRONT);
            break;

        //Set Treble
        case AUDIO_COMMON_TREBLE:
            Result = Audio_SetTreble(sAudioDat.sBasic.sTreble,SYSTEM_FRONT);
            break;

        //Set Balance Fader
        case AUDIO_COMMON_BF:
            Result = Audio_SetBalFad();
            break;

        //Set Dc Filter
        case AUDIO_COMMON_DC:
            Result = Audio_SetDcFilter(sAudioDat.sAdv.DcFilter,SYSTEM_FRONT);
            break;

        //Set Delay Line
        case AUDIO_COMMON_DELAY:
            Result = Audio_SetDelayLine();
            break;

        //Set Graphic Equalizer
        case AUDIO_COMMON_GEQ:
            Result = Audio_SetGeq();
            break;

        //Set Parametric Equalizer
        case AUDIO_COMMON_PEQ:
            Result = Audio_SetPeq();
            break;

        //Set Phase Shifter
        case AUDIO_COMMON_PHASESHIFT:
            Result = Audio_SetPhaseShifter();
            break;

        //Set Loudness
        case AUDIO_COMMON_LOUDNESS:
            Result = Audio_SetLoudness();
            break;

        //Set Subwoofer
        case AUDIO_COMMON_SUBWOOFER:
            Result = Audio_SetSubwoofer();
            break;

        //Set Channel Gain
        case AUDIO_COMMON_CHANGAIN:
            Result = Audio_SetChanGain();
            break;

        //Set Ubass
        case AUDIO_COMMON_UBASS:
            Result = Audio_SetUltraBass();
            break;

        //Set Xover
        case AUDIO_COMMON_XOVER:
            Result = Audio_SetCrossOver();
            break;   
            
        //Fade In&Out Currently Volume
        case AUDIO_COMMON_HINT_VOL:  
		if(MIX_STATUS_NAVI & sAudio.MixStatus)
		{
			Result = Audio_SetNaviVol(sAudio.HintVol);
		}
		else
		{
			Result = Audio_SetVolume(sAudio.HintVol,SYSTEM_FRONT);  
		}     
           
		if(Result == SUBLAYER_DONE)
		{
               //_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_AVOL,sAudioKeep.SysVol,sAudioKeep.BtVol,sAudioKeep.NaviVol,0);
               sAudioKeep.CurrentlyVol = sAudio.HintVol;
		  sAudio.bNotDispVol = 1;
               _SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_VOL,sAudio.HintVol,Audio_GetVolType(),0,0);
               audio_printf(_T("HINT_VOL: %d,%d,%d,%d\n",sAudio.HintVol,sAudio.SysChannel,sAudio.MixStatus,sAudioKeep.CurrentlyVol));
		}
            break;

        case AUDIO_COMMON_HINT_EXIT:
            Result = Audio_SetVolume(sAudioKeep.CurrentlyVol,SYSTEM_FRONT);
            break;

        case AUDIO_COMMON_SRC_SCALER:
            Result = Audio_SetSrcScaler();
            break;
            
        //Do Nothing
        case AUDIO_COMMON_NULL:
        default:
            Result = SUBLAYER_DONE;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Audio_FastHardMute
 * @brief      Fast Hard Mute Control
 *                 Mute&Unmute Amp or Mute&Umute Audio Output 
 *                 Immediately
 * @param      uint8_t Mode : MUTE_ON   MUTE_OFF                    
 * @retval     Result of execute
 **********************************************************/
uint8_t Audio_FastHardMute(uint8_t Mode)
{
    uint8_t Result = SUBLAYER_DOING;

    if(MUTE_ON == Mode)
    {
    	//snake20160822  注意在开关机的时候,ST-BY和MUTE引脚的操作时序
        Result = Amp_Mute(MUTE_ON);
		
		//Rear System
		IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);//no use pin
		
		//Front System
		IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);//ST-BY
    }
    else
    {
        //Front System
        IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,INVALID);
        //Rear System
        IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,INVALID);//no use pin
        Result = Amp_Mute(MUTE_OFF);
    }
    
    return (Result);
}
/**********************************************************
 * @function    Audio_HardMute
 * @brief      Hard Mute Audio Output
 * @param      uint8_t Type
 *            uint8_t Channel
 * @retval     result of execute
 **********************************************************/
uint8_t Audio_HardMute(uint8_t Channel,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    //Front System Mute Control
    if((SYSTEM_FRONT == Channel) || (SYSTEM_ALL == Channel))
    {
        if(MUTE_ON == Type)
        {		
		if(MODULE_EXIST != AmpCtl.Module)  
		{
			#ifndef D_AMP_TDA7388//snake20160823 
			IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
			#endif
		}
		
		Result = Amp_Mute(MUTE_ON);
        }
        else
        {
		 #ifndef D_AMP_TDA7388//snake20160823 
		IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,INVALID);
		#endif

		Result = Amp_Mute(MUTE_OFF);
        }
    }

    //Rear System Mute Control
    if((SYSTEM_REAR == Channel) || (SYSTEM_ALL == Channel))
    {
        if(MUTE_ON == Type)
        {
            IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,VALID);
        }
        else
        {
            IO_Set(IO_IDX_REAR_MUTE,PIN_OUTPUT,INVALID);
        }
        Result = SUBLAYER_DONE;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Audio_MuteQueueIn
 * @brief      Queue New Mute Requirement into Buffer
 * @param      uint8_t TaskId    
 *              MUTE_TYPE_ENUM Type
 * @retval     NULL
 **********************************************************/
void Audio_MuteQueueIn(uint8_t Ach, MUTE_TYPE_ENUM Type, uint8_t Sys)
{
    //Queue New Requirement to Buffer
    sAudio.sMuteBuff[sAudio.MuteCtlTail].AchId = Ach;
    sAudio.sMuteBuff[sAudio.MuteCtlTail].MuteType = Type;
    sAudio.sMuteBuff[sAudio.MuteCtlTail].SysType = Sys;

    sAudio.MuteCtlTail++;
    if(sAudio.MuteCtlTail >= MUTE_BUFFER_MAX)
        sAudio.MuteCtlTail = 0;
}
/**********************************************************
 * @function    Audio_MuteQueueOut
 * @brief      Mute Disposed, Queue Out and Feedback
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_MuteQueueOut(void)
{
    //Queue Out Disposed Mute Requirement
    sAudio.MuteCtlHead++;
    if(sAudio.MuteCtlHead >= MUTE_BUFFER_MAX)
        sAudio.MuteCtlHead = 0;
}
/**********************************************************
 * @function    Audio_MuteExecute
 * @brief      Mute Action Implement
 * @param      uint8_t Ach
 *            uint8_t Type                
 * @retval     Result
 **********************************************************/
uint8_t Audio_MuteExecute(uint8_t Ach,uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;

    switch(Type)
    {
        case TYPE_F_KS_MUTE:
        case TYPE_F_S_MUTE:     //Do nothing but save state:1.keymute has set; 2. softmute has set
            if((MASK_F_KMUTE & sAudio.sAchAttri[Ach].MuteState)
                || (MASK_F_SMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_SoftMute(SYSTEM_FRONT,MUTE_ON);
            }
            break;

        case TYPE_R_KS_MUTE:
        case TYPE_R_S_MUTE:    
            if((MASK_R_KMUTE & sAudio.sAchAttri[Ach].MuteState)
                || (MASK_R_SMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_SoftMute(SYSTEM_REAR,MUTE_ON);
            }
            break;
            
        case TYPE_F_KH_MUTE:
        case TYPE_F_H_MUTE:
            if((MASK_F_HMUTE & sAudio.sAchAttri[Ach].MuteState)
                || (MASK_F_KMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_HardMute(SYSTEM_FRONT,MUTE_ON);
            }
            break;

        case TYPE_R_KH_MUTE:
        case TYPE_R_H_MUTE:
            if((MASK_R_HMUTE & sAudio.sAchAttri[Ach].MuteState)
                || (MASK_R_KMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_HardMute(SYSTEM_REAR,MUTE_ON);
            }
            break;    

        case TYPE_F_KS_UNMUTE:    //Do nothing but save state: 1. keymute already released; 2. softmute flag is set
            if(/*(0x00 == (MASK_F_KMUTE & sAudio.sAchAttri[Ach].MuteState))
                ||*/ (MASK_F_SMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_SoftMute(SYSTEM_FRONT,MUTE_OFF);
            }
            break;

        case TYPE_R_KS_UNMUTE:    
            if((0x00 == (MASK_R_KMUTE & sAudio.sAchAttri[Ach].MuteState))
                || (MASK_R_SMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_SoftMute(SYSTEM_REAR,MUTE_OFF);
            }
            break;    
            
        case TYPE_F_S_UNMUTE://Do nothing but save state: 1. softmute already released; 2. keymute flag is set
            if((0x00 == (MASK_F_SMUTE & sAudio.sAchAttri[Ach].MuteState))
                || (MASK_F_KMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_SoftMute(SYSTEM_FRONT,MUTE_OFF);
            }
            break;

        case TYPE_R_S_UNMUTE:
            if((0x00 == (MASK_R_SMUTE & sAudio.sAchAttri[Ach].MuteState))
                || (MASK_R_KMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_SoftMute(SYSTEM_REAR,MUTE_OFF);
            }
            break;    

        case TYPE_F_KH_UNMUTE:
            if(/*(0x00 == (MASK_F_KMUTE & sAudio.sAchAttri[Ach].MuteState))
                ||*/ (MASK_F_HMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_HardMute(SYSTEM_FRONT,MUTE_OFF);
            }
            break;

        case TYPE_R_KH_UNMUTE:
            if((0x00 == (MASK_R_KMUTE & sAudio.sAchAttri[Ach].MuteState))
                || (MASK_R_HMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_HardMute(SYSTEM_REAR,MUTE_OFF);
            }
            break;    

        case TYPE_F_H_UNMUTE:    
            if((0x00 == (MASK_F_HMUTE & sAudio.sAchAttri[Ach].MuteState))
                || (MASK_F_KMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_HardMute(SYSTEM_FRONT,MUTE_OFF);
            }
            break;

        case TYPE_R_H_UNMUTE:    
            if((0x00 == (MASK_R_HMUTE & sAudio.sAchAttri[Ach].MuteState))
                || (MASK_R_KMUTE & sAudio.sAchAttri[Ach].MuteState))
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_HardMute(SYSTEM_REAR,MUTE_OFF);
            }
            break;    

        case TYPE_F_CURRENT_MUTE:
            Result = Audio_SoftMute(SYSTEM_FRONT,MUTE_ON);
            break;

        case TYPE_F_CURRENT_UNMUTE:
            Result = Audio_SoftMute(SYSTEM_FRONT,MUTE_OFF);
            break;    

        case TYPE_R_CURRENT_MUTE:
            Result = Audio_SoftMute(SYSTEM_REAR,MUTE_ON);
            break;

        case TYPE_R_CURRENT_UNMUTE:
            Result = Audio_SoftMute(SYSTEM_REAR,MUTE_OFF);
            break;        

        default:
            Result = SUBLAYER_ERROR;
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Audio_MuteSyncState
 * @brief      Sync Mute State
 * @param      uint8_t Ach
 *            uint8_t Type
 * @retval     NULL
 **********************************************************/
void Audio_MuteSyncState(uint8_t Ach,uint8_t Type)
{
    switch(Type)
    {
        case TYPE_F_S_MUTE:     
            sAudio.sAchAttri[Ach].MuteState |= MASK_F_SMUTE;
            break;

        case TYPE_F_H_MUTE:
            sAudio.sAchAttri[Ach].MuteState |= MASK_F_HMUTE;
            break;

        case TYPE_F_S_UNMUTE:
            sAudio.sAchAttri[Ach].MuteState &= (~MASK_F_SMUTE);
            break;

        case TYPE_F_H_UNMUTE:    
            sAudio.sAchAttri[Ach].MuteState &= (~MASK_F_HMUTE);
            break;

        case TYPE_F_KS_MUTE:
            sAudio.KeyMuteState |= MASK_KMUTE_FS;
            break;
            
        case TYPE_F_KS_UNMUTE:
            sAudio.KeyMuteState &= (~MASK_KMUTE_FS);
            break;

        case TYPE_F_KH_MUTE:
            sAudio.KeyMuteState |= MASK_KMUTE_FH;
            break;
            
        case TYPE_F_KH_UNMUTE:
            sAudio.KeyMuteState &= (~MASK_KMUTE_FH);
            break;

        case TYPE_R_S_MUTE:     
            sAudio.sAchAttri[Ach].MuteState |= MASK_R_SMUTE;
            break;

        case TYPE_R_H_MUTE:
            sAudio.sAchAttri[Ach].MuteState |= MASK_R_HMUTE;
            break;

        case TYPE_R_S_UNMUTE:
            sAudio.sAchAttri[Ach].MuteState &= (~MASK_R_SMUTE);
            break;

        case TYPE_R_H_UNMUTE:    
            sAudio.sAchAttri[Ach].MuteState &= (~MASK_R_HMUTE);
            break;

        case TYPE_R_KS_MUTE:
            sAudio.KeyMuteState |= MASK_KMUTE_RS;
            break;
            
        case TYPE_R_KS_UNMUTE:
            sAudio.KeyMuteState &= (~MASK_KMUTE_RS);
            break;

        case TYPE_R_KH_MUTE:
            sAudio.KeyMuteState |= MASK_KMUTE_RH;
            break;
            
        case TYPE_R_KH_UNMUTE:
            sAudio.KeyMuteState &= (~MASK_KMUTE_RH);
            break;

        case TYPE_F_CURRENT_MUTE:
            sAudio.MuteState |= MASK_F_SMUTE;
            break;

        case TYPE_F_CURRENT_UNMUTE:
            sAudio.MuteState &= (~MASK_F_SMUTE);
            break;        

        case TYPE_R_CURRENT_MUTE:
            sAudio.MuteState |= MASK_R_SMUTE;
            break;

        case TYPE_R_CURRENT_UNMUTE:
            sAudio.MuteState &= (~MASK_R_SMUTE);
            break;        

        default:
            break;
    }
}
/**********************************************************
 * @function    Audio_MuteEvtDisposal
 * @brief      Disposal Mute Requirements
 * @param      NULL    
 * @retval     NULL
 **********************************************************/
void Audio_MuteEvtDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t TmpAch,TmpSys,TmpMute;

    //Filters 
    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }
    if(!(AUDIO_READY & sAudio.ReadyState))
    {
        return;
    }

    //Get Required ACH
    TmpAch = sAudio.sMuteBuff[sAudio.MuteCtlHead].AchId;
    TmpSys = sAudio.sMuteBuff[sAudio.MuteCtlHead].SysType;
    TmpMute = sAudio.sMuteBuff[sAudio.MuteCtlHead].MuteType;
        
    switch(sAudio.MuteEvtCtl)
    {
        //Idle, Waiting for newly requirement
        case MUTE_EVT_IDLE:
            if(sAudio.MuteCtlHead != sAudio.MuteCtlTail)    //Check Whether There is a Newly Requirement
            {
                sAudio.MuteEvtCtl = MUTE_EVT_FRONT;
                sAudio.SoftMuteStep = 0;
                //Newly Required is not Currently Channel: Only Save!
                if(((SYSTEM_FRONT == TmpSys) && (sAudio.SysChannel != TmpAch))
                    || ((SYSTEM_REAR == TmpSys) && (sAudio.RearChannel != TmpAch)))
                {
                    sAudio.MuteEvtCtl = MUTE_EVT_END;    //Not Currently,Do Nothing but Save State 
                }
            }
            break;

        //Set Front System Mute requirement
        case MUTE_EVT_FRONT:
            if(SYSTEM_FRONT != TmpSys)
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_MuteExecute(TmpAch,TmpMute);
            }
            if(SUBLAYER_DONE == Result)
            {
                sAudio.MuteEvtCtl = MUTE_EVT_REAR;
            }
            break;

        //Set Rear System Mute requirement
        case MUTE_EVT_REAR:
            if(SYSTEM_REAR != TmpSys)
            {
                Result = SUBLAYER_DONE;
            }
            else
            {
                Result = Audio_MuteExecute(TmpAch,TmpMute);    
            }
            if(SUBLAYER_DONE == Result)
            {
                sAudio.MuteEvtCtl = MUTE_EVT_END;
            }
            break;

        //Mute Evt Ends, Save and Feedback
        case MUTE_EVT_END:
            Audio_MuteSyncState(TmpAch,TmpMute);
            //Sync Line Out Mute State
//            if((sAudio.MuteState & MASK_F_HMUTE) || (sAudio.MuteState & MASK_F_SMUTE))
//            {
//                IO_Set(IO_IDX_LINE_MUTE,PIN_OUTPUT,VALID); //Line Out Mute
//            }
//            else
//            {
//                IO_Set(IO_IDX_LINE_MUTE,PIN_OUTPUT,INVALID); // Line Out De-Mute
//            }

            //Queue Out Currently Disposed Require
            Audio_MuteQueueOut();

            sAudio.MuteEvtCtl = MUTE_EVT_IDLE;
            break;

        default:
            break;
    }

    //Error Occurs!
    if(Result > SUBLAYER_DONE)
    {
        sAudio.MuteEvtCtl = MUTE_EVT_IDLE;
    }
}
#define MUTE_FADE_STEP		3
/**********************************************************
 * @function    Audio_KeyMuteDisposal
 * @brief      Mute Disposal
 *                 Only adapt to one requirement in each loop
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_KeyMuteDisposal(void)
{
	uint8_t Result = SUBLAYER_DOING,Vol_temp;
	uint8_t msg[5];
	
    //Filters 
    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }    
    if(!(AUDIO_READY & sAudio.ReadyState))
    {
        return;
    }

    switch(sAudio.KeyMuteStep[SYSTEM_FRONT])
    {
        // Mute Idle State, Do Nothing But Waiting For New Requirement
        case AUDIO_MUTE_IDLE:
            if(MUTE_NULL != sAudio.KeyMuteReq[SYSTEM_FRONT])    
            {
                if(MUTE_ON == sAudio.KeyMuteReq[SYSTEM_FRONT])
                {
                    sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_START;

			if(sAudio.MixStatus & MIX_STATUS_NAVI)
			{
				sAudio.MuteVol[SYSTEM_FRONT] = sAudioKeep.SysVol;
			}
			else
			{
				sAudio.MuteVol[SYSTEM_FRONT] = sAudioKeep.CurrentlyVol; 
			}
                }
                else
                {
                    sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_UNMUTE_START;
                    sAudio.MuteVol[SYSTEM_FRONT] = 0;    
                }
                sAudio.bFadeFlag = 0;                // Clear Fade Flag
                sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_NULL;    
            }
            break;

        // Volume Step Down Before Mute
        case AUDIO_MUTE_FADE_OUT:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_FRONT]))    
            {
                if(sAudio.MuteVol[SYSTEM_FRONT] >= MUTE_FADE_STEP)    //Step Decrease Volume 
                {
                	Vol_temp = sAudio.MuteVol[SYSTEM_FRONT]-MUTE_FADE_STEP;
                }
		  else  if(sAudio.MuteVol[SYSTEM_FRONT] != 0)
		  {
		  	Vol_temp = 0;
		  }
		   if(sAudio.MuteVol[SYSTEM_FRONT]>0)
		   {
			    if(0 == sAudio.bFadeFlag)
	                  {
	                        sAudio.MuteVol[SYSTEM_FRONT]=Vol_temp;
	                        sAudio.bFadeFlag = 1;
	                  }
		   }
            
                // Set the New Volume
                Result = Audio_SetVolume(sAudio.MuteVol[SYSTEM_FRONT],SYSTEM_FRONT);
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.KeyMuteDly[SYSTEM_FRONT] = AudioDelay(T60MS);
                    sAudio.bFadeFlag = 0;
                }
            
                //Volume Decreased to Zero! Fade Out End ?
                if((0 == sAudio.MuteVol[SYSTEM_FRONT]) && (0 == sAudio.bFadeFlag))
                {
                    sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_SOFT_MUTE;
                }
            }
            break;

        // Soft Mute Currently Audio Channel    
        case AUDIO_MUTE_SOFT_MUTE:
            Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_KS_MUTE,SYSTEM_FRONT);
            sAudio.KeyMuteDly[SYSTEM_FRONT] = AudioDelay(T30MS); // temporary time : for stable, against noise
            sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_SMUTE_CHK; //Goto Wait SoftMute Done!
            break;

        //Check SoftMute
        case AUDIO_MUTE_SMUTE_CHK:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_FRONT]))    
            {
                if(MASK_KMUTE_FS & sAudio.KeyMuteState) //SoftMute Done!
                {
                    sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_HARD_MUTE;
					sAudio.KeyMuteDly[SYSTEM_FRONT] = AudioDelay(T200MS); // temporary time : for stable, against noise
                }
                //Error Occurs!
            }
            break;

        // Hard Mute Amp or Audio Output    
        case AUDIO_MUTE_HARD_MUTE:
#if 0	
            //Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_KH_MUTE,SYSTEM_FRONT);
            //sAudio.KeyMuteDly[SYSTEM_FRONT] = AudioDelay(T30MS); // temporary time : for stable, against noise
            //sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_HMUTE_CHK;
            sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_END;  //Do not mute AMP ,cuz Beep....
#endif
		    if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_FRONT]))	
		    {

    	        Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_KH_MUTE,SYSTEM_FRONT);
                sAudio.KeyMuteDly[SYSTEM_FRONT] = AudioDelay(T30MS); // temporary time : for stable, against noise
                sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_HMUTE_CHK;
            }
		
            break;

        //Check HardMute
        case AUDIO_MUTE_HMUTE_CHK:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_FRONT]))    
            {
                if(MASK_KMUTE_FH & sAudio.KeyMuteState) //SoftMute Done!
                {
                    sAudio.MuteState |= MASK_F_KMUTE;
                    sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_END;
		    //外置功放进静音
		    CANUser_SetAmpCmd(AMP_TYPE_MUTE, MUTE_ON);
                }
                //Error Occurs!
            }
            break;

        case AUDIO_MUTE_SETVOL:
            // Set the New Volume
            Result = Audio_SetVolume(0,SYSTEM_FRONT);
            if(SUBLAYER_DONE == Result)
            {
                sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_HARD_UNMUTE;
                //外置功放解静音
		CANUser_SetAmpCmd(AMP_TYPE_MUTE, MUTE_OFF);
            }
            break;

        // Hard Unmute or Release Audio Output    
        case AUDIO_MUTE_HARD_UNMUTE:
            Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_KH_UNMUTE,SYSTEM_FRONT);
            sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_HUNMUTE_CHK;
            break;

        //Hard Unmute Check&Wait
        case AUDIO_MUTE_HUNMUTE_CHK:
            if(!(MASK_KMUTE_FH & sAudio.KeyMuteState)) //Hard Unmute Done!
            {
                sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_SOFT_UNMUTE;
            }
            break;

        // Soft Unmute    
        case AUDIO_MUTE_SOFT_UNMUTE:
            Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_KS_UNMUTE,SYSTEM_FRONT);
            sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_SUNMUTE_CHK;
            sAudio.KeyMuteDly[SYSTEM_FRONT] = AudioDelay(T150MS); 
            break;

        //Soft Unmute Check&Wait
        case AUDIO_MUTE_SUNMUTE_CHK:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_FRONT]))   
            {
                if(!(MASK_KMUTE_FS & sAudio.KeyMuteState)) //Hard Unmute Done!
                {
                    sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_FADE_IN;
    			//_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_ACK,BEEP_ON,0,0);
                }
            }
            break;
            
        // Volume Step Down Before Mute    
        case AUDIO_MUTE_FADE_IN:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_FRONT]))    
            {
                // Step Increase Volume
			if(sAudio.MixStatus & MIX_STATUS_NAVI)
			{
				Vol_temp = sAudioKeep.SysVol;
			}
			else
			{
				Vol_temp = sAudioKeep.CurrentlyVol;
			}
			
                if(Vol_temp > sAudio.MuteVol[SYSTEM_FRONT])
                {
                    if(0 == sAudio.bFadeFlag)
                    {
				if((sAudio.MuteVol[SYSTEM_FRONT]+MUTE_FADE_STEP)< Vol_temp)
				{
					sAudio.MuteVol[SYSTEM_FRONT]+= MUTE_FADE_STEP;
				}
				else
				{
					sAudio.MuteVol[SYSTEM_FRONT] = Vol_temp;
				}
				sAudio.bFadeFlag = 1;
                    }
                }
            
                // Set the New Volume
                Result = Audio_SetVolume(sAudio.MuteVol[SYSTEM_FRONT],SYSTEM_FRONT);
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.KeyMuteDly[SYSTEM_FRONT] = AudioDelay(T40MS);
                    sAudio.bFadeFlag = 0;
                }
            
                //Volume Retrieved !Fade In End ?
                if((sAudioKeep.CurrentlyVol <= sAudio.MuteVol[SYSTEM_FRONT]) && (0 == sAudio.bFadeFlag))
                {
                    sAudio.MuteState &= (~MASK_F_KMUTE);
                    sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_END;
                    //Re-Sync Volume
                    if(sAudioKeep.CurrentlyVol != sAudio.MuteVol[SYSTEM_FRONT])
                    {
                        Audio_OpQueueIn(AUDIO_COMMON_VOL);
                    }
                }
            }
            break;

        case AUDIO_MUTE_END:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_FRONT]))    
            {
                sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_NULL;    
                sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
                //Sync Line Out Mute State
//                if(sAudio.MuteState & MASK_F_KMUTE)
//                {
//                    IO_Set(IO_IDX_LINE_MUTE,PIN_OUTPUT,VALID); //Line Out Mute
//                }
//                else
//                {
//                    IO_Set(IO_IDX_LINE_MUTE,PIN_OUTPUT,INVALID); // Line Out De-Mute
//                }

            }
            break;
            
        default:
            sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
            break;
    }

    //Error Occurs
    if(Result > SUBLAYER_DONE)
    {
        sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_IDLE;
    }
}
/**********************************************************
 * @function    Audio_RearKeyMuteDisposal
 * @brief      Rear Key Mute Disposal
 *                 Only adapt to one requirement in each loop
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_RearKeyMuteDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;

    switch(sAudio.KeyMuteStep[SYSTEM_REAR])
    {
        // Mute Idle State, Do Nothing But Waiting For New Requirement
        case AUDIO_MUTE_IDLE:
            if(MUTE_NULL != sAudio.KeyMuteReq[SYSTEM_REAR])    
            {
                if(MUTE_ON == sAudio.KeyMuteReq[SYSTEM_REAR])        
                    sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_START;
                else
                    sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_UNMUTE_START;
                
                sAudio.bRearFadeFlag = 0;                // Clear Fade Flag
                sAudio.KeyMuteReq[SYSTEM_REAR] = MUTE_NULL;    
                sAudio.MuteVol[SYSTEM_REAR] = sAudioKeep.RearVol;    // Sync System Volume to Mute Volume
            }
            break;

        // Volume Step Down Before Mute
        case AUDIO_MUTE_FADE_OUT:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_REAR]))    
            {
                if(sAudio.MuteVol[SYSTEM_REAR] > 0)    //Step Decrease Volume 
                {
                    if(0 == sAudio.bRearFadeFlag)
                    {
                        sAudio.MuteVol[SYSTEM_REAR]--;
                        sAudio.bRearFadeFlag = 1;
                    }
                }
            
                // Set the New Volume
                Result = Audio_SetVolume(sAudio.MuteVol[SYSTEM_REAR],SYSTEM_REAR);
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.KeyMuteDly[SYSTEM_REAR] = AudioDelay(T30MS);
                    sAudio.bRearFadeFlag = 0;
                }
            
                //Volume Decreased to Zero! Fade Out End ?
                if((0 == sAudio.MuteVol[SYSTEM_REAR]) && (0 == sAudio.bRearFadeFlag))
                {
                    sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_SOFT_MUTE;
                }
            }
            break;

        // Soft Mute Currently Audio Channel    
        case AUDIO_MUTE_SOFT_MUTE:
            Audio_MuteQueueIn(sAudio.RearChannel,TYPE_R_KS_MUTE,SYSTEM_REAR);
            sAudio.KeyMuteDly[SYSTEM_REAR] = AudioDelay(T30MS); // temporary time : for stable, against noise
            sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_SMUTE_CHK;
            break;

        case AUDIO_MUTE_SMUTE_CHK:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_REAR]))    
            {
                if(MASK_KMUTE_RS & sAudio.KeyMuteState) //SoftMute Done!
                {
                    sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_HARD_MUTE;
                }
                //Error Occurs!
            }
            break;

        // Hard Mute Amp or Audio Output    
        case AUDIO_MUTE_HARD_MUTE:
            Audio_MuteQueueIn(sAudio.RearChannel,TYPE_R_KH_MUTE,SYSTEM_REAR);
            sAudio.KeyMuteDly[SYSTEM_REAR] = AudioDelay(T30MS); // temporary time : for stable, against noise
            sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_HMUTE_CHK;
            break;

        case AUDIO_MUTE_HMUTE_CHK:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_REAR]))    
            {
                if(MASK_KMUTE_RH & sAudio.KeyMuteState) 
                {
                    sAudio.MuteState |= MASK_R_KMUTE;
                    sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_END;
                }
                //Error Occurs!
            }
            break;
            
        // Hard Unmute or Release Audio Output    
        case AUDIO_MUTE_HARD_UNMUTE:
            Audio_MuteQueueIn(sAudio.RearChannel,TYPE_R_KH_UNMUTE,SYSTEM_REAR);
            sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_HUNMUTE_CHK;
            break;

        //Hard Unmute Check&Wait
        case AUDIO_MUTE_HUNMUTE_CHK:
            if(!(MASK_KMUTE_RH & sAudio.KeyMuteState)) //Hard Unmute Done!
            {
                sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_SOFT_UNMUTE;
            }
            break;

        // Soft Unmute    
        case AUDIO_MUTE_SOFT_UNMUTE:
            Audio_MuteQueueIn(sAudio.RearChannel,TYPE_R_KS_UNMUTE,SYSTEM_REAR);
            sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_SUNMUTE_CHK;
            break;

        //Soft Unmute Check&Wait
        case AUDIO_MUTE_SUNMUTE_CHK:
            if(!(MASK_KMUTE_RS & sAudio.KeyMuteState)) //Hard Unmute Done!
            {
                sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_FADE_IN;
            }
            break;
                
        // Volume Step Down Before Mute    
        case AUDIO_MUTE_FADE_IN:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_REAR]))    
            {
                // Step Increase Volume
                if(sAudioKeep.RearVol != sAudio.MuteVol[SYSTEM_REAR])
                {
                    if(0 == sAudio.bRearFadeFlag)
                    {
                        sAudio.MuteVol[SYSTEM_REAR]++;
                        sAudio.bRearFadeFlag = 1;
                    }
                }
            
                // Set the New Volume
                Result = Audio_SetVolume(sAudio.MuteVol[SYSTEM_REAR],SYSTEM_REAR);
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.KeyMuteDly[SYSTEM_REAR] = AudioDelay(T30MS);
                    sAudio.bRearFadeFlag = 0;
                }
            
                //Volume Retrieved !Fade In End ?
                if((sAudioKeep.RearVol == sAudio.MuteVol[SYSTEM_REAR]) && (0 == sAudio.bRearFadeFlag))
                {
                    sAudio.MuteState &= (~MASK_R_KMUTE);
                    sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_END;
                }
            }
            break;

        case AUDIO_MUTE_END:
            if(DelayHasExpired(sAudio.KeyMuteDly[SYSTEM_REAR]))    
            {
                sAudio.KeyMuteReq[SYSTEM_REAR] = MUTE_NULL;    
                sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_IDLE;
            }
            break;
            
        default:
            sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_IDLE;
            break;
    }
    //Error Occurs
    if(Result > SUBLAYER_DONE)
    {
        sAudio.KeyMuteStep[SYSTEM_REAR] = AUDIO_MUTE_IDLE;
    }
}


/**********************************************************
 * @function    Audio_MixDecayVolume
 * @brief      
 * @param      
 * @retval    
 **********************************************************/
void Audio_MixDecayVolume(void)
{
	audio_printf(_T("====Audio_MixDecayVolume:%d====\n",sAudio.MixStatus));
	if(MIX_STATUS_NAVI == sAudio.MixStatus)
	{
		if((sAudioKeep.CurrentlyVol > 12)&&(sAudioKeep.CurrentlyVol < 19))
		sAudioKeep.CurrentlyVol = 13;
		else if((sAudioKeep.CurrentlyVol > 18)&&(sAudioKeep.CurrentlyVol < 25))
		sAudioKeep.CurrentlyVol -= 6;
		else if(sAudioKeep.CurrentlyVol > 24)
		sAudioKeep.CurrentlyVol = 19;
		
		voltemp=sAudioKeep.SysVol;
	}
	else
	{
		// sAudioKeep.CurrentlyVol = sAudioKeep.SysVol;
	}
}

/**********************************************************
 * @function    Audio_SyncVolume
 * @brief      Currently Volume Sync with Specific Type Volume
 * @param      uint8_t Ach
 * @retval     NULL
 **********************************************************/
void Audio_SyncVolume(uint8_t Ach)
{
    audio_printf(_T(" ==Audio_SyncVolume---Ach=%d,CurrentlyVol=%d,BtVol=%d,SysVol=%d,NaviVol=%d \n",Ach,sAudioKeep.CurrentlyVol, sAudioKeep.BtVol,sAudioKeep.SysVol,sAudioKeep.NaviVol));
    switch(Ach)
    {
        case SRC_TYPE_NAVI:    //Sync Navi Volume
        case SRC_TYPE_NAVI_AUDIO:
		//sAudioKeep.CurrentlyVol = sAudioKeep.NaviVol;
		if(MIX_TYPE_FL == sAudio.sMixBuffer[sAudio.MixHead].Pos)
		{
			Audio_MixDecayVolume();
		}
            break;

        case SRC_TYPE_BT_PHONE:
        case SRC_TYPE_3G_PHONE:    
            sAudioKeep.CurrentlyVol = sAudioKeep.BtVol;
            break;    

	case SRC_TYPE_VR:
	case SRC_TYPE_APP_TONE:
		sAudioKeep.CurrentlyVol = sAudioKeep.SysVol;
		break;

        default:        //Sync System Volume
            sAudioKeep.CurrentlyVol = sAudioKeep.SysVol;
            break;
    }
		
	sAudio.bNotDispVol = 1;
	if((SRC_TYPE_BT_PHONE == Ach)||(SRC_TYPE_3G_PHONE == Ach))
	{
	
	}
	else
	{
		if((1 == g_tMcuDevState.uIOState.bits.Reverse_Flag) || (1 == g_tMcuDevState.uDetect.bits.Blind_Flag))
		{
			Can_Vol_Reverse = sAudioKeep.CurrentlyVol;
			sAudioKeep.CurrentlyVol = AUDIO_VOL_REVERSE;
		}
	}
}

#if 0
/**********************************************************
 * @function    Audio_BakupVolume
 * @brief      Bakup Specific Volume
 * @param      uint8_t Ach
 * @retval     NULL
 **********************************************************/
void Audio_BakupVolume(uint8_t Ach)
{
    switch(Ach)
    {
        case SRC_TYPE_NAVI:  //Bakup Navi Volume
        case SRC_TYPE_NAVI_AUDIO:
            sAudioKeep.NaviVol = sAudioKeep.CurrentlyVol;
            break;

        case SRC_TYPE_BT_PHONE:
        case SRC_TYPE_3G_PHONE:    
            sAudioKeep.BtVol = sAudioKeep.CurrentlyVol;
            break;    

        case SRC_TYPE_VR:
        case SRC_TYPE_APP_TONE:
            sAudioKeep.AppVol = sAudioKeep.CurrentlyVol;
            break;

        default:        //Bakup System Volume
            sAudioKeep.SysVol = sAudioKeep.CurrentlyVol;
            break;
    }
}

/**********************************************************
 * @function    Audio_AchQueueIn
 * @brief      Queue in Required ACH
 * @param      uint8_t Req
 *            uint8_t Type
 * @retval     NULL
 **********************************************************/
void Audio_AchQueueIn(uint8_t Req, uint8_t Type)
{
    switch(Type)
    {
        //Require for switching to an Insertable ACH
        case SYSTEM_INSERT:
            sAudio.AchActBuffer[Audio_GetPrioritySrcPos(Req)] = Req;
            break;

        //Require for removing an Insertable ACH:Clear Specific ActAch Buffer
        case SYSTEM_REMOVE:
            sAudio.AchActBuffer[Audio_GetPrioritySrcPos(Req)] = SRC_TYPE_NUM;
            break;

        //Front System Require for an Source ACH 
        case SYSTEM_FRONT:
            sAudio.AchActBuffer[ACH_SOURCE - 1] = Req ;
            break;

        //Rear System Require For an Source ACH
        case SYSTEM_REAR:
            sAudio.AchActRear = Req;
            break;

        //Front and Rear System Require for an Source ACH
        case SYSTEM_ALL:
            sAudio.AchActBuffer[ACH_SOURCE - 1] = Req ;
            sAudio.AchActRear = Req;
            break;        
    }
}
#endif
/**********************************************************
 * @function    Audio_SetChannel
 * @brief      Set a newly audio channel
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_SetChannel(eSOURCE_ZONE eZone,const tSOURCE* tSrc,uint8_t AudPri)
{
    uint8_t SrcId = SRC_TYPE_NUM;
    audio_printf(_T("---Audio_SetChannel:%d,%d---\n",tSrc->eSrcType,eZone));
	
    if(eZone == SRC_ZONE_FRONT)
    {
    	//g_tSysStateDbgInfo.CurAudioSource = tSrc->eSrcID;
		sAudio.CurrentAudioSourceId = tSrc->eSrcID;
    }
	
    if(NULL != tSrc) 
    {
        SrcId = tSrc->eSrcType;
        if(0xFF == AudPri)
        {
            if(SRC_ZONE_FRONT == eZone)
            {
                if(!((SRC_TYPE_CAMERA == SrcId) 
                    || ((SRC_TYPE_NAVI == SrcId) && (0x00 != g_tSysRomData.uGenBlock.tBlock.tFlag3.bNavi_Guidance_Mode))))
                {
                    sAudio.AchActBuffer[ACH_SOURCE] = SrcId ;
                }
            }
            else if(SRC_ZONE_REAR == eZone)
            {
                sAudio.AchActRear = SrcId;
            }   
        }
        else
        {
            if(SRC_ZONE_FRONT == eZone)
            {
                if(SRC_TYPE_LOGO != SrcId)
                {
                	sAudio.AchActBuffer[AudPri] = SrcId;
                }
            }
            else if(SRC_ZONE_REAR == eZone)
            {
                sAudio.AchActRear = SrcId;
            }   
        }
    }
    else
    {
        if(SRC_ZONE_REAR == eZone)
        {
            sAudio.AchActRear = SRC_TYPE_NUM;
        }
        else
        {
            sAudio.AchActBuffer[AudPri] = SRC_TYPE_NUM;
        }
    }
}


/**********************************************************
 * @function    Audio_FachSwitchDisposal
 * @brief      Front System Ach Switch Disposal
 *            Source Switch Triggerred by Ach Switch Command...
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
 #define _IO_SET_DEV_AUDIO   IO_IDX_N

void Audio_FachSwitchDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t Temp,FrontAct = SRC_TYPE_NUM;
    uint8_t MuteAttri;

    //Get Newly Front System Actived ACH
    for(Temp = 0; Temp < ACH_MAX; Temp++)
    {
        if(SRC_TYPE_NUM != sAudio.AchActBuffer[Temp])
        {
            FrontAct = sAudio.AchActBuffer[Temp];
            break;
        }
    }

    //Check Whether Need to Switch Front System ACH
    if(sAudio.SysChannel != FrontAct)
    {
        if(ACH_SWITCH_IDLE == sAudio.AchCtl[SYSTEM_FRONT]) //SYSTEM_REAR 状态错误，导致无法正常进入通道切换
        {
		sAudio.AchReqed[SYSTEM_FRONT] = FrontAct;
	#if 0	
		if((sAudio.SysChannel == SRC_TYPE_NUM)||(sAudio.SysChannel == SRC_TYPE_AVOFF))
		{

			Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_MUTE);  
		}
		else	
		{
			Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_FAD_OUT);  
		}
	#else
		Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_MUTE); 
	#endif
			
		sAudio.AchVol = sAudioKeep.SysVol;    // Sync System Volume to Mute Volume

		if((1 == g_tMcuDevState.uIOState.bits.Reverse_Flag) || (1 == g_tMcuDevState.uDetect.bits.Blind_Flag))
		{

			sAudio.AchVol = AUDIO_VOL_REVERSE;
		}
//            if(sAudio.MixStatus & MIX_STATUS_NAVI)
//            {
//                sAudio.AchVol = Tab_MixAttn[sAudioDat.sBasic.MixAttn - 1];
//            }
	     audio_printf(_T("Run FachSwitch:%x\n", FrontAct));
        }
    }

    if(AUDIO_MUTE_IDLE != sAudio.KeyMuteStep[SYSTEM_FRONT])
        return;

    //Switch Front System Ach
    switch(sAudio.AchCtl[SYSTEM_FRONT])
    {
        //Idle State , Wait For New Requirement
        case ACH_SWITCH_IDLE:        
            break;

        case ACH_SWITCH_FAD_OUT:
            if(DelayHasExpired(sAudio.AchDelay[SYSTEM_FRONT]))    
            {
                if(sAudio.AchVol > 0)    //Step Decrease Volume 
                {
                    if(0 == sAudio.AchFade)
                    {
                        sAudio.AchVol--;
                        sAudio.AchFade = 1;
                    }
                }
            
                // Set the New Volume
                Result = Audio_SetVolume(sAudio.AchVol,SYSTEM_FRONT);
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.AchDelay[SYSTEM_FRONT] = AudioDelay(T10MS);
                    sAudio.AchFade = 0;
                }
            
                //Volume Decreased to Zero! Fade Out End ?
                if((0 == sAudio.AchVol) && (0 == sAudio.AchFade))
                {
                    Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_MUTE);
                }
            }
            break;
            
        //Mute before Switching
        case ACH_SWITCH_MUTE:
            Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_CURRENT_MUTE,SYSTEM_FRONT);
            sAudio.AchDelay[SYSTEM_FRONT] = AudioDelay(T30MS);
            Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_SRC);
            break;

        //Deactive Currently Source and Active Newly Source when Muted.. 
        case ACH_SWITCH_SRC:
            if((MASK_F_SMUTE & sAudio.MuteState)
                || (DelayHasExpired(sAudio.AchDelay[SYSTEM_FRONT]))) //SoftMute Done!
            {
                sAudio.AchDelay[SYSTEM_FRONT] = AudioDelay(T10MS);
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_VCH);
            }
            break;

        //Switch VCH of Newly Source
        case ACH_SWITCH_VCH:
            if(sAudio.AchDelay[SYSTEM_FRONT])
                break;
            //Video_VchQueueIn(sAudio.AchReqed[SYSTEM_FRONT],SYSTEM_FRONT);
            if((SRC_TYPE_AVOFF == sAudio.AchReqed[SYSTEM_FRONT])
                || (SRC_TYPE_SYS_STDBY == sAudio.AchReqed[SYSTEM_FRONT])
                || (SRC_TYPE_SLEEP == sAudio.AchReqed[SYSTEM_FRONT])
                || (SRC_TYPE_CAMERA == sAudio.AchReqed[SYSTEM_FRONT])
                || (SRC_TYPE_REVERSE == sAudio.AchReqed[SYSTEM_FRONT]))
            {
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_DEMUTE);
            }
            else
            {
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_SWITCH);
            }
            break;
            
        //Change Switch's Related Channel
        case ACH_SWITCH_SWITCH:
            Result = Audio_SwitchSwitchAch(sAudio.AchReqed[SYSTEM_FRONT],SYSTEM_FRONT);
            if(SUBLAYER_DONE == Result)
            {
                if(SRC_TYPE_LOGO_AUDIO == sAudio.AchReqed[SYSTEM_FRONT])
                {
                    IO_Set(_IO_SET_DEV_AUDIO,PIN_OUTPUT,VALID);
                }
                else
                {
                    IO_Set(_IO_SET_DEV_AUDIO,PIN_OUTPUT,INVALID);
                }
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_ASP);
                sAudio.AspAchCtl = OPERATION_0;    
                sAudio.SrcInputSelStep = OPERATION_0;
            }
            break;
	
        //Change ASP Related Channel
        case ACH_SWITCH_ASP:
            Result = Audio_Asp_SwitchAch(sAudio.AchReqed[SYSTEM_FRONT],SYSTEM_FRONT);        
            if(SUBLAYER_DONE == Result)
            {
               // Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_DEMUTE);
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_VOL);
                if(SRC_TYPE_NUM != sAudio.AchReqed[SYSTEM_FRONT])
                {
                    Audio_SyncVolume(sAudio.AchReqed[SYSTEM_FRONT]); //Get Newly Ach's Volume Setting
                }
                else
                {
                    Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_END);
                }
            }
            break;

        //Switch to Newly Ach's Volume Setting
        case ACH_SWITCH_VOL:
		if((SRC_TYPE_APP_TONE == sAudio.AchReqed[SYSTEM_FRONT]) ||
		    (SRC_TYPE_VR== sAudio.AchReqed[SYSTEM_FRONT]))
	      	{ 
	      	 	if(SysWorkStatusGrp.SysBtCallFlag)
                    {
                   Result = Audio_SetVolume(sAudioKeep.BtVol,SYSTEM_FRONT);
	
                    }
			else
			{
			Result = Audio_SetVolume(sAudioKeep.CurrentlyVol,SYSTEM_FRONT);
			}	
		}
		 else
		 {
	    		Result = Audio_SetVolume(0,SYSTEM_FRONT);//SUBLAYER_DONE;
		 }
            if(SUBLAYER_DONE == Result)
            {
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_DEMUTE);
                //Clear Currently Channel Mute State
            }
            break;

        //Retrieve Mute State of Source(Actually ACH's Attribute)
        case ACH_SWITCH_DEMUTE:
            //Updated Currently Channel
            if(SRC_TYPE_NUM != sAudio.AchReqed[SYSTEM_FRONT])
            {
                sAudio.SysChannel = sAudio.AchReqed[SYSTEM_FRONT];
            }
            //Get Newly Channel's Mute State
            if((SRC_TYPE_AVOFF != sAudio.SysChannel)
                && (SRC_TYPE_SYS_STDBY != sAudio.SysChannel)
                && (SRC_TYPE_SLEEP != sAudio.SysChannel))
            {
                if(!sAudio.KeyMuteFlag)
                {
                    Audio_MuteQueueIn(sAudio.SysChannel,TYPE_F_CURRENT_UNMUTE,SYSTEM_FRONT);
                    sAudio.AchDelay[SYSTEM_FRONT] = AudioDelay(T10MS);
                }
            }
	     #if 0
	        if((SRC_TYPE_APP_TONE == sAudio.AchReqed[SYSTEM_FRONT]) ||
		    (SRC_TYPE_VR== sAudio.AchReqed[SYSTEM_FRONT]))
	      	{
			Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_TRANSITION);
		}
		else
		{
	            Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_FAD_IN);
		     //audio_printf(_T("Start FADE_IN!\n"));
		     sAudio.AchFade = 0;
		     sAudio.AchVol = 0;
		}
	     #else
		 Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_TRANSITION);
	     #endif
            break;

	case ACH_SWITCH_TRANSITION:
		if(DelayHasExpired(sAudio.AchDelay[SYSTEM_FRONT]))  
		{
			Result = Audio_SetVolume(sAudioKeep.CurrentlyVol,SYSTEM_FRONT);
			if(SUBLAYER_DONE == Result)
			{
				Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_END);
			}
		}
		break;
	case ACH_SWITCH_FAD_IN:
	     if(DelayHasExpired(sAudio.AchDelay[SYSTEM_FRONT]))    
            {
                 if(0 == sAudio.AchFade)
                {
                    sAudio.AchVol++;
                    sAudio.AchFade = 1;
		      audio_printf(_T("FADE_IN:%d\n", sAudio.AchVol));
                }
            
                // Set the New Volume
                Result = Audio_SetVolume(sAudio.AchVol,SYSTEM_FRONT);
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.AchDelay[SYSTEM_FRONT] = AudioDelay(T10MS);
                    sAudio.AchFade = 0;
                }
            
                //Volume increase to target value! Fade in End 
                  if((sAudioKeep.CurrentlyVol <= sAudio.AchVol) && (0 == sAudio.AchFade))
                {
                    Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_FRONT],ACH_SWITCH_END);
                }
            }
	    break;
        //Switch End, Save Newly Ach and FeedBack
	case ACH_SWITCH_END:
		if(sAudio.AchDelay[SYSTEM_FRONT])
			break;
		//snake20161222
 		if(g_tSysStateDbgInfo.CurAudioSource != sAudio.CurrentAudioSourceId)
 		{
			g_tSysStateDbgInfo.CurAudioSource = sAudio.CurrentAudioSourceId;
 		}

		 //sTunerKeep.bPausestate = 0;	
		 if((SRC_TYPE_TUNER == sAudio.SysChannel) && (sTunerKeep.bPausestate == 1))
		 {//收音暂停状态下，挂电话后保持收音暂停状态
			Result = Hero_SrcScalerToZero(SYSTEM_FRONT);
			if(SUBLAYER_DONE == Result)
			{
				sAudio.AchCtl[SYSTEM_FRONT] = ACH_SWITCH_IDLE;
				sAudio.AchReqed[SYSTEM_FRONT] = SRC_TYPE_NUM;
			}
			else
			{
                   		 sAudio.AchDelay[SYSTEM_FRONT] = AudioDelay(T10MS);
			}
		 }
		 else
		 {
			sAudio.AchCtl[SYSTEM_FRONT] = ACH_SWITCH_IDLE;
			sAudio.AchReqed[SYSTEM_FRONT] = SRC_TYPE_NUM;
		 }
		_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD, UICC_AUDIO_STATE, 0x01, 0, 0);
		audio_printf(_T("ACH_SWITCH_END\n"));
		break;

        default:
            sAudio.AchCtl[SYSTEM_FRONT] = ACH_SWITCH_IDLE;
            break;
    }
    //Error Occurs!
    if(Result > SUBLAYER_DONE)
    {
        sAudio.AchCtl[SYSTEM_FRONT] = ACH_SWITCH_IDLE;
    }
}
/**********************************************************
 * @function    Audio_RachSwitchDisposal
 * @brief      Rear Ach Switch Disposal
 *            Source Switch Triggerred by Ach Switch Command...
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_RachSwitchDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;

    //Filters 
    if(!(AUDIO_READY & sAudio.ReadyState))
    {
        return;
    }

    //Check Whether Need to Switch Rear System ACH
    if(sAudio.RearChannel != sAudio.AchActRear)
    {
        if((ACH_SWITCH_IDLE == sAudio.AchCtl[SYSTEM_FRONT]) && (ACH_SWITCH_IDLE == sAudio.AchCtl[SYSTEM_REAR]))
        {
            sAudio.AchReqed[SYSTEM_REAR] = sAudio.AchActRear;    
            Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_REAR],ACH_SWITCH_START);    
        }
    }

    //Switch Rear System Ach
    switch(sAudio.AchCtl[SYSTEM_REAR])
    {
        //Idle State , Wait For New Requirement
        case ACH_SWITCH_IDLE:        
            break;

        case ACH_SWITCH_FAD_OUT:
            Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_REAR],ACH_SWITCH_MUTE);
            break;

        //Mute before Switching
        case ACH_SWITCH_MUTE:
            Audio_MuteQueueIn(sAudio.RearChannel,TYPE_R_CURRENT_MUTE,SYSTEM_REAR);
            Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_REAR],ACH_SWITCH_SRC);
            break;

        //Deactive Currently Source and Active Newly Source when Muted.. 
        case ACH_SWITCH_SRC:
            if(MASK_R_SMUTE & sAudio.MuteState) //SoftMute Done!
            {
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_REAR],ACH_SWITCH_VCH);
            }
            break;

        //Switch VCH of Newly Source
        case ACH_SWITCH_VCH:
            //Video_VchQueueIn(sAudio.AchReqed[SYSTEM_REAR],SYSTEM_REAR);
            Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_REAR],ACH_SWITCH_SWITCH);
            break;
            
        //Change Switch's Related Channel
        case ACH_SWITCH_SWITCH:
            Result = Audio_SwitchSwitchAch(sAudio.AchReqed[SYSTEM_REAR],SYSTEM_REAR);
            if(SUBLAYER_DONE == Result)
            {
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_REAR],ACH_SWITCH_ASP);
                sAudio.AspAchCtl = 0;    
                sAudio.SrcInputSelStep = OPERATION_0;
            }
            break;

        //Change ASP Related Channel
        case ACH_SWITCH_ASP:
            Result = Audio_Asp_SwitchAch(sAudio.AchReqed[SYSTEM_REAR],SYSTEM_REAR);        
            if(SUBLAYER_DONE == Result)
            {
                Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_REAR],ACH_SWITCH_DEMUTE);
            }
            break;

        //Switch to Newly Ach's Volume Setting
        case ACH_SWITCH_VOL:
            break;

        //Retrieve Mute State of Source(Actually ACH's Attribute)
        case ACH_SWITCH_DEMUTE:
            //Clear Currently Channel Mute State

            //Updated Currently Channel
            //if(SRC_TYPE_NUM != sAudio.AchReqed[SYSTEM_REAR])
            {
                sAudio.RearChannel = sAudio.AchReqed[SYSTEM_REAR];
                //4 When De-Mute, The newly Volume Setting will be Implement
            }

            //Get Newly Channel's Mute State
            Audio_MuteQueueIn(sAudio.RearChannel,TYPE_R_CURRENT_UNMUTE,SYSTEM_REAR);
            Audio_GotoSpecialStep(&sAudio.AchCtl[SYSTEM_REAR],ACH_SWITCH_END);
            break;

        //Switch End, Save Newly Ach and FeedBack
        case ACH_SWITCH_END:
            //Clear State and Queue out 
            sAudio.AchCtl[SYSTEM_REAR] = ACH_SWITCH_IDLE;
            sAudio.AchReqed[SYSTEM_REAR] = SRC_TYPE_NUM;
            break;

        default:
            sAudio.AchCtl[SYSTEM_REAR] = ACH_SWITCH_IDLE;
            break;
    }
    //Error Occurs!
    if(Result > SUBLAYER_DONE)
    {
        sAudio.AchCtl[SYSTEM_REAR] = ACH_SWITCH_IDLE;
    }
}
/**********************************************************
 * @function    Audio_AchSwitchMgr
 * @brief      ACH Switch Manager: Front&Rear
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_AchSwitchMgr(void)
{
    //Filters 
    if(!(AUDIO_READY & sAudio.ReadyState))
    {
        return;
    }    
    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }
    //Front System Ach Switch
    Audio_FachSwitchDisposal();
    //Rear System Ach Switch
    Audio_RachSwitchDisposal();
}
/**********************************************************
 * @function    Audio_BeepInsert
 * @brief      Insert a Beep into ready buffer
 * @param      uint8_t Type
 * @retval     NULL
 **********************************************************/
void Audio_BeepInsert(uint8_t Type)
{
#if 1
    sAudio.sBeepBuffer[sAudio.BeepTail].Type = Type;
    sAudio.BeepTail++;
    if(sAudio.BeepTail >= BEEP_BUFFER_MAX)
    {
        sAudio.BeepTail = 0;
    }
#else
    uint8_t Temp,Counter;

    //Insert  Newly Beep 
    for(Temp = 0; Temp < BEEP_BUFFER_MAX; Temp++)
    {
        if(Type <= sAudio.sBeepBuffer[Temp].Type)
        {
            sAudio.sBeepBuffer[Temp].Type = Type;
            //sAudio.sBeepBuffer[Temp].Repetition = Repetition;
            break;
        }
    }

    if(Temp < BEEP_BUFFER_MAX)
    {
        //Re-Queue the ready buffer
        for(Counter = (BEEP_BUFFER_MAX - 1); Counter > Temp; Counter--)
        {
            sAudio.sBeepBuffer[Counter] = sAudio.sBeepBuffer[Counter - 1];
        }
    
        if(sAudio.BeepNum < BEEP_BUFFER_MAX)
            sAudio.BeepNum++;
        //else  //error happened!
    }
#endif    
}
/**********************************************************
 * @function    Audio_BeepDelete
 * @brief      Delete a beep from ready buffer
 * @param      uint8_t Type
 * @retval     NULL
 **********************************************************/
 void Audio_BeepDelete(uint8_t Type)
{
#if 1
    sAudio.BeepHead++;
    if(sAudio.BeepHead >= BEEP_BUFFER_MAX)
    {
        sAudio.BeepHead = 0;
    }
#else
    uint8_t Temp;

    //Find the needed  Beep 
    for(Temp = 0; Temp < BEEP_BUFFER_MAX; Temp++)
    {
        if(Type == sAudio.sBeepBuffer[Temp].Type)
        {
            break;
        }
    }

    //Delete while the desired beep is in the buffer
    if(Temp < BEEP_BUFFER_MAX)
    {
        //Delete and re-queue the list
        for(; Temp < (BEEP_BUFFER_MAX - 1); Temp++)
        {
            sAudio.sBeepBuffer[Temp] = sAudio.sBeepBuffer[Temp + 1];
        }

        sAudio.sBeepBuffer[BEEP_BUFFER_MAX - 1].Type = BEEP_TYPE_NULL;

        if(sAudio.BeepNum)
            sAudio.BeepNum--;
    }
    //Do Nothing, When the desired beep is not in the buffer
#endif    
}
/**********************************************************
 * @function    Audio_MuteQueueIn
 * @brief      Queue New Beep Requirement into Buffer
 * @param      uint8_t Type
 *            uint8_t Attri
 * @retval     NULL
 **********************************************************/
void Audio_BeepQueueIn(uint8_t Type, uint8_t Attri)
{
    if(Type > BEEP_TYPE_USER) //Ignore Requirement that beyond the type
        return;
#if 0
    //Audio_BeepInsert(Type);  //Insert Newly
#else
    //Got a Stop Beep Requirement
    if(BEEP_OFF == Attri)
    {
        if(Type == sAudio.sBeepCurrent.Type) //The Required is Running
        {
            //Goto Finish Currently
            sAudio.BeepCtl = BEEP_CTL_END;    
        }
        else
        {
            //Delete Required from ready buffer
            Audio_BeepDelete(Type);
        }
    }
    else     //Got a Beep Requirement
    {
        if(BEEP_TYPE_NULL == sAudio.sBeepCurrent.Type) //there is a beep beeping...
        {
            Audio_BeepInsert(Type);  //Insert Newly
        }
        else
        {
            if(Type < sAudio.sBeepCurrent.Type) //Newly Has high priority
            {
                //Stop Not Delete Currently and Insert Newly, 
                    //if Currently is Numerable ,Should be deleted
                sAudio.BeepCtl = BEEP_CTL_STOP;
                Audio_BeepInsert(Type);  //Insert Newly
            }
            else if(Type == sAudio.sBeepCurrent.Type)
            {
                // Do nothing...
            }
            else        
            {
                //Newly has low priority, only insert...while it is continuous...
                if(BEEP_RPT_CONTINUOUS == Tab_BeepRptAttri[Type])
                {
                    Audio_BeepInsert(Type); //Insert!!
                }
                //Do nothig but Desert newly when it is numerable...
            }    
        }
    }
#endif    
}
/**********************************************************
 * @function    Audio_BeepDisposal
 * @brief      Beep Control~~~
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_BeepDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }
    if(BEEP_TYPE_SET_OFF == sAudioDat.sInfo.BeepType)
    {
        return;  //Beep Off
    }

    switch(sAudio.BeepCtl)
    {
        //Idle State, Check Ready Buffer
        case BEEP_CTL_IDLE:
            if(sAudio.BeepHead != sAudio.BeepTail)    //There is a beep ready...
            {
                sAudio.sBeepCurrent = sAudio.sBeepBuffer[sAudio.BeepHead];
                sAudio.BeepCtl = BEEP_CTL_SET;
            }
            break;

        //Set Desired Beep
        case BEEP_CTL_SET:
            Result = Audio_Beep(sAudio.sBeepCurrent.Type); //Always Execute the priority beep
            if(SUBLAYER_DONE == Result)
            {
                sAudio.BeepDelay = AudioDelay(T50MS);
                sAudio.BeepCtl = BEEP_CTL_BEEPING;
            }
            break;

        //Beep and Check Sequencer status
        case BEEP_CTL_BEEPING:
            if(DelayHasExpired(sAudio.BeepDelay))
            {
                if(BEEP_RPT_CONTINUOUS == Tab_BeepRptAttri[sAudio.sBeepCurrent.Type])
                {
                    //If it is a Preset Chime ,Resend again
                }
                else
                {
                    sAudio.BeepCtl = BEEP_CTL_END;
                }
            }
            break;

        //Stop Currently Beep
        case BEEP_CTL_STOP:
            if(BEEP_RPT_ONCE != Tab_BeepRptAttri[sAudio.sBeepCurrent.Type])
            {
                Result = Audio_BeepStop();
            }
            else
            {
                Result = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == Result)
            {    
                sAudio.sBeepCurrent.Type = BEEP_TYPE_NULL;
                sAudio.BeepCtl = BEEP_CTL_IDLE;
            }
            break;

        //Ends Currently Beep    
        case BEEP_CTL_END:
            if(BEEP_RPT_ONCE != Tab_BeepRptAttri[sAudio.sBeepCurrent.Type])
            {
                Result = Audio_BeepStop();
            }
            else
            {
                Result = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == Result)
            {    
                Audio_BeepDelete(sAudio.sBeepCurrent.Type);
                sAudio.sBeepCurrent.Type = BEEP_TYPE_NULL;
                sAudio.BeepCtl = BEEP_CTL_IDLE;
            }
            break;
            
        default:
            break;
    }

    if(Result > SUBLAYER_DONE)
    {
        Audio_BeepDelete(sAudio.sBeepCurrent.Type);
        sAudio.sBeepCurrent.Type = BEEP_TYPE_NULL;
        sAudio.BeepCtl = BEEP_CTL_IDLE;
    }

    //Dispose Beep Config
    Audio_BeepConfig();
}
/**********************************************************
 * @function    Audio_BeepConfig
 * @brief      Config Beep Settings
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_BeepConfig(void)
{
    uint8_t Result = SUBLAYER_DOING;

    switch(sAudio.BeepSetupCtl)
    {
        //Idle: Check Mask Bit
        case BEEP_SETUP_IDLE:
            if(sAudio.BeepSetupMask)
            {
                sAudio.BeepSetupCtl = BEEP_SETUP_VOL;
            }
            break;
    
        //Setup Newly Volume
        case BEEP_SETUP_VOL:
            if(sAudio.BeepSetupMask & BEEP_MASK_VOL)
            {
                Result = Audio_BeepSetVol(sAudioDat.sAdv.BeepVol);
            }
            else
            {
                Result = SUBLAYER_DONE;
            }
            
            if(SUBLAYER_DONE == Result)
            {
                if(sAudio.BeepSetupMask & BEEP_MASK_RECONFIG) //Should Re-config currently
                {    
                    sAudio.BeepSetupMask &= (~BEEP_MASK_RECONFIG);
                }
                else
                {
                    sAudio.BeepSetupMask &= (~BEEP_MASK_VOL); //Finished,Clear The Mask Bit
                }
                sAudio.BeepSetupCtl = BEEP_SETUP_POS;
            }
            break;
            
        //Setup Newly Position
        case BEEP_SETUP_POS:
            if(sAudio.BeepSetupMask & BEEP_MASK_POS)
            {
                Result = Audio_BeepSetPos(sAudioDat.sInfo.BeepPos);
            }
            else
            {
                Result = SUBLAYER_DONE;
            }
            
            if(SUBLAYER_DONE == Result)
            {
                if(sAudio.BeepSetupMask & BEEP_MASK_RECONFIG) //Should Re-config currently
                {    
                    sAudio.BeepSetupMask &= (~BEEP_MASK_RECONFIG);
                }
                else
                {
                    sAudio.BeepSetupMask &= (~BEEP_MASK_POS); //Finished,Clear The Mask Bit
                }
                sAudio.BeepSetupCtl = BEEP_SETUP_IDLE;
            }
            break;
            
        default:
            sAudio.BeepSetupCtl = BEEP_SETUP_IDLE;
            break;
    }

    if(SUBLAYER_ERROR == Result)
    {
        sAudio.BeepSetupMask &= (~BEEP_MASK_RECONFIG);
        sAudio.BeepSetupCtl = BEEP_SETUP_IDLE;
    }
}
/**********************************************************
 * @function    Audio_ClickClack
 * @brief      Click Clack Control~~~
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_CC_QueueIn(uint8_t Flag, uint8_t Type)
{
    sAudio.ClickClackFlag = Flag;
    sAudio.ClickClackType = Type;
    if(CLICKCLACK_OFF == sAudio.ClickClackFlag)
    {
        if(CC_CTL_IDLE != sAudio.ClickClackCtl)
        {
            sAudio.ClickClackCtl = CC_CTL_DISABLE;
        }
    }
    else
    {
        sAudio.ClickClackCtl = CC_CTL_ENABLE;
    }
}
/**********************************************************
 * @function    Audio_ClickClack
 * @brief      Click Clack Control~~~
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_ClickClack(void)
{
    uint8_t Result = SUBLAYER_DOING;
    
    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }
    
    switch(sAudio.ClickClackCtl)
    {
        //Do Nothing
        case CC_CTL_IDLE:
            break;

        case CC_CTL_ENABLE:
            Result = Audio_CC_Enable();
            if(SUBLAYER_DONE == Result)
            {
                sAudio.ClickClackCtl = CC_CTL_CLICK;
            }
            break;

        case CC_CTL_CLICK:
            if(DelayHasExpired(sAudio.ClickClackDelay))
            {
                Result = Audio_SetClickClack(0);
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.ClickClackCtl = CC_CTL_CLACK;
                    //sAudio.ClickClackDelay = (sAudio.ClickClackType * 10);
                    sAudio.ClickClackDelay = AudioDelay(T400MS);
                }
            }
            break;

        case CC_CTL_CLACK:
            if(DelayHasExpired(sAudio.ClickClackDelay))
            {
                Result = Audio_SetClickClack(1);
                if(SUBLAYER_DONE == Result)
                { 
                    sAudio.ClickClackCtl = CC_CTL_CLICK;
                    //sAudio.ClickClackDelay = (sAudio.ClickClackType * 10);
                    sAudio.ClickClackDelay = AudioDelay(T400MS);
                }
            }
            break;

        case CC_CTL_DISABLE:
            Result = Audio_CC_Disable();
            if(SUBLAYER_DONE == Result)
            {
                sAudio.ClickClackCtl = CC_CTL_IDLE;
            }
            break;   
    }
    
    if(Result > SUBLAYER_DONE)
    {
        sAudio.ClickClackCtl = CC_CTL_IDLE;
    }    
}
/**********************************************************
 * @function    Audio_MuteQueueIn
 * @brief      Queue New Beep Requirement into Buffer
 * @param      uint8_t BeepType
 * @retval     NULL
 **********************************************************/
void Audio_MixQueueIn(uint8_t Src, uint8_t Pos)
{
    if(((SRC_TYPE_SYS_STDBY == sAudio.SysChannel) || (SRC_TYPE_SLEEP == sAudio.SysChannel)
        || (sAudio.KeyMuteFlag))
        && (MIX_TYPE_OFF != Pos))
    {
        return;
    }

    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }
    
#if 0   //System Volume Off when Mix 
    if(MIX_ATTN_SET_OFF == sAudioDat.sBasic.MixAttn)
    {
        //Clear Mix Buffer

        //Send Switch ACH Message

        return;
    }
#endif
    audio_printf(_T("Audio_MixQueIn:%x\n", Pos));
    sAudio.sMixBuffer[sAudio.MixTail].Src = Src;    
    //Mix Position: same as Setting in Setup menu
    sAudio.sMixBuffer[sAudio.MixTail].Pos = Pos;  
    if(MIX_TYPE_OFF != Pos)
    {
        sAudio.sMixBuffer[sAudio.MixTail].Pos = sAudioDat.sBasic.MixPos;    
    }
    sAudio.MixTail++;
    if(sAudio.MixTail >= MIX_BUFFER_MAX)
        sAudio.MixTail = 0;
}
/**********************************************************
 * @function    Audio_MixDisposal
 * @brief      Mix Control~~~
 *            Can Not Support Multi Mix at same time 
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_MixDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;

    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }

    if((SRC_TYPE_SYS_STDBY == sAudio.SysChannel) || (SRC_TYPE_SLEEP == sAudio.SysChannel))
    {
        if(sAudio.MixStatus & MIX_STATUS_NAVI)
        {
            //  Audio_MixQueueIn(SRC_TYPE_NAVI_AUDIO,sAudioDat.sBasic.MixPos);// Mix In
         Audio_MixQueueIn(SRC_TYPE_NAVI_AUDIO,MIX_TYPE_OFF);
        }
    }
    //Off means disable mix function and switch the whole channel
#if 0   //System Volume Off when Mix     
    if(MIX_ATTN_SET_OFF == sAudioDat.sBasic.MixAttn)
    {
        return;
    }
#endif    
    switch(sAudio.MixCtl)
    {
        //Idle, Waiting for Requirment
        case MIX_CTL_IDLE:
            if(sAudio.MixTail != sAudio.MixHead) 
            {
                sAudio.MixCtl = MIX_CTL_ROUTE;
                if(MIX_TYPE_OFF == sAudio.sMixBuffer[sAudio.MixHead].Pos)
                {
                    sAudio.MixCtl = MIX_CTL_POS; //Goto Off Mix...
                    if(!(sAudio.MixStatus & MIX_STATUS_NAVI))
                    {
                         sAudio.MixCtl = MIX_CTL_END;
                         break;
                    }
                    //Update Mix Status
                    if(SRC_TYPE_NAVI_AUDIO == sAudio.sMixBuffer[sAudio.MixHead].Src)
                    {
                        sAudio.MixStatus &= (~MIX_STATUS_NAVI);
                    }
                #if 0    
                    else if(SRC_TYPE_BT_PHONE == sAudio.sMixBuffer[sAudio.MixHead].Src)
                    {
                        sAudio.MixStatus &= (~MIX_STATUS_BT);
                    }
                #endif    
                    //4 Don't Consider Multi-Mix,Directly Go back to System Volume Setting
                    Audio_SyncVolume(sAudio.SysChannel); //Get System Volume Setting
                }
            }
            break;

        //Set Mix Route1:AK~~~
        case MIX_CTL_ROUTE:
            Result = Audio_SetMixRoute(sAudio.sMixBuffer[sAudio.MixHead].Src,sAudio.sMixBuffer[sAudio.MixHead].Pos);
            if(SUBLAYER_DONE == Result)
            {
                sAudio.MixCtl = MIX_CTL_SRC;
            }
            break;    

        //Set Mix Route2: DiRaNa
        case MIX_CTL_SRC:
            Result = Audio_SetMixSrc(sAudio.sMixBuffer[sAudio.MixHead].Src,sAudio.sMixBuffer[sAudio.MixHead].Pos);
            if(SUBLAYER_DONE == Result)
            {
                sAudio.MixCtl = MIX_CTL_POS;
            }
            break;

        //Set Mix Position( Include Gain)
        case MIX_CTL_POS:
            Result = Audio_SetMixPos(sAudio.sMixBuffer[sAudio.MixHead].Src,sAudio.sMixBuffer[sAudio.MixHead].Pos);
            if(SUBLAYER_DONE == Result)
            {
                sAudio.MixCtl = MIX_CTL_ATTN;
                if(MIX_TYPE_OFF != sAudio.sMixBuffer[sAudio.MixHead].Pos)
                {
                    if(sAudioKeep.CurrentlyVol <= Tab_MixAttn[sAudioDat.sBasic.MixAttn - 1])
                    {    //Do Nothing with System Volume, goto Set Mixer's Volume
                        sAudio.MixCtl = MIX_CTL_VOL; 
                    }
                    //Update Mix Status
                    if(SRC_TYPE_NAVI_AUDIO == sAudio.sMixBuffer[sAudio.MixHead].Src)
                    {
                        sAudio.MixStatus |= MIX_STATUS_NAVI;
                    }
                #if 0    
                    else if(SRC_TYPE_BT_PHONE == sAudio.sMixBuffer[sAudio.MixHead].Src)
                    {
                        sAudio.MixStatus |= MIX_STATUS_BT;
                    }
                #endif    
                    Audio_SyncVolume(sAudio.sMixBuffer[sAudio.MixHead].Src); //Get Mixer's Volume Setting
                }
            }
            break;

        //Set System Volume Attenuation
        case MIX_CTL_ATTN:
			#if 0 //snake20161226 倒车和盲区正常播报导航提示
			if((VALID == g_tMcuDevState.uIOState.bits.Reverse_Flag) || (INVALID == g_tMcuDevState.uDetect.bits.Blind_Flag)/*||(INVALID == BodyECUStatus.AVM_State)*/)
			{
				audio_printf(_T("-----break  Run MIX_CTL_END---\n"));
				break;
			}
			#endif
			
            if((MIX_TYPE_OFF == sAudio.sMixBuffer[sAudio.MixHead].Pos)&&(voltemp > 10))
            {
            #if 1
		 if(DelayHasExpired(sAudio.AchDelay[SYSTEM_FRONT]))    
              {
                // Step Increase Volume
                if(sAudioKeep.CurrentlyVol < voltemp)
                {
                    if(0 == sAudio.bFadeFlag)
                    {
                        sAudioKeep.CurrentlyVol++;
                        sAudio.bFadeFlag = 1;
                    }
                }
            
                // Set the New Volume
                Result = Audio_SetVolume(sAudioKeep.CurrentlyVol,SYSTEM_FRONT);
		   sAudio.bNotDispVol = 1;		
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.AchDelay[SYSTEM_FRONT] = AudioDelay(T40MS);
			 sAudio.MixCtl = MIX_CTL_ATTN; 		
                    sAudio.bFadeFlag = 0;
                }
            
                //Volume Retrieved !Fade In End ?
               
                if((sAudioKeep.CurrentlyVol >= voltemp) && (0 == sAudio.bFadeFlag))
                {
                    //Audio_OpQueueIn(AUDIO_COMMON_VOL);
			sAudio.MixCtl = MIX_CTL_VOL;//MIX_CTL_END;		
                }
            }
		#else
                //Retrieve Last System Volume..  //Use Message
                Audio_OpQueueIn(AUDIO_COMMON_VOL);
                sAudio.MixCtl = MIX_CTL_END;
		#endif
            }
            else
            {    //Attenuation System Volume
                //When Calling ,Do Not Decrease Currently Volume
                if((SRC_TYPE_BT_PHONE == sAudio.SysChannel) || (SRC_TYPE_3G_PHONE == sAudio.SysChannel))
                {
                   Result = SUBLAYER_DONE;  
                }
                else
                {
             #ifndef D_VOL_CHANA
                    Result = Audio_SetVolume(Tab_MixAttn[sAudioDat.sBasic.MixAttn - 1],SYSTEM_FRONT);
	      #else
			Result = SUBLAYER_DONE;  
             #endif
                }
                if(SUBLAYER_DONE == Result)
                {
                    sAudio.MixCtl = MIX_CTL_VOL; 
                }
            }

            if(MIX_TYPE_OFF == sAudio.sMixBuffer[sAudio.MixHead].Pos)
            {
                //Retrieve Last System Volume..  //Use Message
                Audio_OpQueueIn(AUDIO_COMMON_VOL);
                sAudio.MixCtl = MIX_CTL_END;
            }
            else
            {    //Attenuation System Volume
            	  if((SRC_TYPE_BT_PHONE == sAudio.SysChannel) || (SRC_TYPE_3G_PHONE == sAudio.SysChannel))
                {
                	//When Calling ,Do Not Decrease Currently Volume
                   Result = SUBLAYER_DONE;  
                }
                else
		  {
                    Result = Audio_SetVolume(Tab_MixAttn[sAudioDat.sBasic.MixAttn - 1],SYSTEM_FRONT);
                }
		  if(SUBLAYER_DONE == Result)
                {
                    sAudio.MixCtl = MIX_CTL_VOL; 
                }
            }
            break;

        //Set Mixer's Channel Volume (Navi Channel or Phone Channel)
        case MIX_CTL_VOL:
            //Set Mixer's Volume Setting  //Use Message
            {
                Audio_OpQueueIn(AUDIO_COMMON_VOL);
                Result = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == Result)
            {
                sAudio.MixCtl = MIX_CTL_END; 
            }
            break;

        case MIX_CTL_END:
            sAudio.MixHead++;
            if(sAudio.MixHead >= MIX_BUFFER_MAX)
            {
                sAudio.MixHead = 0;
            }
            sAudio.MixCtl = MIX_CTL_IDLE;
            break;
            
        default:
            break;
    }

    if(Result > SUBLAYER_DONE)
    {
        sAudio.MixCtl = MIX_CTL_IDLE;
    }
}
/**********************************************************
 * @function    Audio_GetSourceScaler
 * @brief      Get Specific ACH's Source Scaling Value
 * @param      uint8_t ACH                    
 * @retval     uint8_t Result
 **********************************************************/
uint8_t Audio_GetSourceScaler(uint8_t ACH)
{
    uint8_t Result;

    switch(ACH)
    {
        case SRC_TYPE_TUNER:
        case SRC_TYPE_RDS_TA:    
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_TUNER];
            break;

        case SRC_TYPE_DISC_AUDIO:
        case SRC_TYPE_DISC_VIDEO:
        case SRC_TYPE_DVD:    
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_DISC];
            break;
	case SRC_TYPE_CDBOX:
	     Result = sAudioDat.sGain.ScalerTbl[SS_SRC_CDBOX];
	     break;

        case SRC_TYPE_IPOD:
        case SRC_TYPE_IPOD_AUDIO:
        case SRC_TYPE_IPOD_VIDEO:
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_IPOD];
            break;

        case SRC_TYPE_USB:
        case SRC_TYPE_USB_VIDEO:
        case SRC_TYPE_USB_AUDIO:   
        case SRC_TYPE_SD:
        case SRC_TYPE_SD_VIDEO:
        case SRC_TYPE_SD_AUDIO:    
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_USB];
            break;

        case SRC_TYPE_BT_PHONE:
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_BT_PHONE];
            break;

        case SRC_TYPE_NAVI:
        case SRC_TYPE_NAVI_AUDIO:
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_NAVI];
            break;

        case SRC_TYPE_3G_PHONE:    //Temp Increase 3G Phone Source Gain
             Result = AUDIO_SRC_SCALER_MAX - 2;
            break;

        case SRC_TYPE_F_AUX:
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_F_AUX];
            break;

        case SRC_TYPE_R_AUX:
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_R_AUX];
            break;

         case SRC_TYPE_BT_MUSIC:   
            Result = sAudioDat.sGain.ScalerTbl[SS_SRC_BT_MUSIC];
            break;

        case SRC_TYPE_MHL: //For Clink
            Result = AUDIO_SRC_SCALER_MAX;//sAudioDat.sGain.ScalerTbl[SS_SRC_MHL];   
            break;

	case SRC_TYPE_DTV:
		Result = sAudioDat.sGain.ScalerTbl[SS_SRC_DTV];
		break;
	case SRC_TYPE_THIRD_APP:
		Result = sAudioDat.sGain.ScalerTbl[SS_SRC_THIRD_APP];
		break;
		
        default:
            Result = (AUDIO_SRC_SCALER_MAX / 2);
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Audio_ChgScalerChk
 * @brief      Check whether Change Currently Source Scaler
 * @param    uint8_t Src                
 * @retval     uint8_t Result
 **********************************************************/
uint8_t Audio_ChgScalerChk(uint8_t Src)
{
    uint8_t Result = 0;

    switch(sAudio.SysChannel)
    {
        case SRC_TYPE_TUNER:
        case SRC_TYPE_RDS_TA:    
            if(SS_SRC_TUNER == Src)
            {
                Result = 1;
            }
            break;

        case SRC_TYPE_DISC_AUDIO:
        case SRC_TYPE_DISC_VIDEO:
        case SRC_TYPE_DVD:    
            if(SS_SRC_DISC == Src)
            {
                Result = 1;
            }
            break;
	case SRC_TYPE_CDBOX:
	     if(SS_SRC_CDBOX== Src)
            {
                Result = 1;
            }
	     break;

        case SRC_TYPE_IPOD:
        case SRC_TYPE_IPOD_AUDIO:
        case SRC_TYPE_IPOD_VIDEO:
            if(SS_SRC_IPOD == Src)
            {
                Result = 1;
            }
            break;

        case SRC_TYPE_USB:
        case SRC_TYPE_USB_VIDEO:
        case SRC_TYPE_USB_AUDIO:   
        case SRC_TYPE_SD:
        case SRC_TYPE_SD_VIDEO:
        case SRC_TYPE_SD_AUDIO:   
            if(SS_SRC_USB == Src)
            {
                Result = 1;
            }
            break;

        case SRC_TYPE_BT_MUSIC:
        case SRC_TYPE_BT_PHONE:
            if(SS_SRC_BT_PHONE == Src)
            {
                Result = 1;
            }
            break;

        case SRC_TYPE_NAVI:
        case SRC_TYPE_NAVI_AUDIO:
            if(SS_SRC_NAVI == Src)
            {
                Result = 1;
            }            
            break;

        case SRC_TYPE_3G_PHONE:    //Temp Increase 3G Phone Source Gain
            break;
        case SRC_TYPE_R_AUX:    // 
            if(SS_SRC_R_AUX == Src)
            {
                Result = 1;
            }            
            break;
        case SRC_TYPE_F_AUX:    // 
            if(SS_SRC_F_AUX == Src)
            {
                Result = 1;
            }            
            break;

        default:
            break;
    }

    return (Result);
}
/**********************************************************
 * @function    Audio_OpQueueIn
 * @brief      Queue In Operation to Buffer
 * @param      uint8_t Op
 * @retval     NULL
 **********************************************************/
void Audio_OpQueueIn(uint8_t Op)
{
    sAudio.OpBuffer[sAudio.OpTail] = Op;    

    sAudio.OpTail++;
    if(sAudio.OpTail >= OP_BUFFER_MAX)
        sAudio.OpTail = 0;
}
/**********************************************************
 * @function    Audio_OpDisposal
 * @brief      Operation Disposal
 * @param      NULL                    
 * @retval     NULL
 **********************************************************/
void Audio_OpDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;

    //Filter:
    if(AUDIO_SYS_RUN != AudioGetSysState())
    {
        return;
    }
    
    switch(sAudio.OpCtl)
    {
        //Idle, Waiting for Requirment
        case OP_CTL_IDLE:
            if(sAudio.OpTail != sAudio.OpHead) 
            {
                sAudio.OpCtl = OP_CTL_EXECUTE;
                //Clear Specific Funcion module's control step
                sAudio.DrvVolStep = OPERATION_0; 
                sAudio.DrvBassStep = OPERATION_0;
                sAudio.DrvMidStep = OPERATION_0;
                sAudio.DrvTrebleStep = OPERATION_0;
                sAudio.BalFadCtl = OPERATION_0;
                sAudio.DelayCtl = OPERATION_0;
                sAudio.GeqStep = OPERATION_0;
                sAudio.PeqStep = OPERATION_0;
                sAudio.SwCtl = OPERATION_0;
                sAudio.XoverCtl = 0;
                sAudio.UltraBassCtl = 0;
                sAudio.ChanGainCtl = 0;
                sAudio.LoudnessCtl = 0;
            }
            break;

        //Execute Required Operation...
        case OP_CTL_EXECUTE:
            Result = Audio_InputExecute(sAudio.OpBuffer[sAudio.OpHead]);
            if(SUBLAYER_DONE == Result)
            {
                sAudio.OpCtl = OP_CTL_END;
            }
            break;

        //Required Operation is Done, Go to Next...
        case OP_CTL_END:    
            sAudio.OpHead++;
            if(sAudio.OpHead >= OP_BUFFER_MAX)
            {
                sAudio.OpHead = 0;
            }
            sAudio.OpCtl = OP_CTL_IDLE;
            break;
            
        default:
            break;
    }

    if(Result > SUBLAYER_DONE)
    {
        sAudio.OpCtl = OP_CTL_IDLE;
    }
}


