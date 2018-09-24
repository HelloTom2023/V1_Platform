#define _HMI_C_
#include "..\config\inc.h"


/******************************************************************************/
//Audio Setting Index Map table
uint8_t const g_AudSetupIndexTbl[] =
{
    OP_AUD_SW_SET,
    OP_AUD_SW_COF,
    OP_AUD_SW_GAIN,   
    OP_AUD_SW_Q,
    OP_AUD_LOUD_SET,
    OP_AUD_LDB_COF,
    OP_AUD_LDT_CF,
    OP_AUD_FAD_SEL,
    OP_AUD_BAL_SEL,
    OP_AUD_BASS_GAIN_SEL,
    OP_AUD_MID_GAIN_SEL,
    OP_AUD_TREBLE_GAIN_SEL,
    OP_AUD_BASS_CF_SEL,
    OP_AUD_MID_CF_SEL,
    OP_AUD_TREBLE_CF_SEL,
    OP_AUD_BASS_Q_SEL,
    OP_AUD_MID_Q_SEL,
    OP_AUD_TREBLE_Q_SEL,
    OP_AUD_HINT_MEDIA,  // 0x12
    OP_AUD_SVOL_MEDIA,
    OP_AUD_HINT_PHONE,  // 0x14
    OP_AUD_SVOL_PHONE,
    OP_AUD_HINT_NAVI,
    OP_AUD_SVOL_NAVI,
    OP_AUD_HINT_APP,
    OP_AUD_SVOL_APP,
    0xFF,
    0xFF,
    OP_AUD_MIX_POS,
    OP_AUD_MIX_LEVEL,
    
};

//Audio Setting Index Map table
uint8_t const g_AspSetupIndexTbl[][2] =
{
    { OP_AUD_DELAY_PRESET ,0xff           },             
    { OP_AUD_DELAY_SPEAKER,CHANNEL_FL  },
    { OP_AUD_DELAY_SPEAKER,CHANNEL_FR  },        
    { OP_AUD_DELAY_SPEAKER,CHANNEL_RL  },     
    { OP_AUD_DELAY_SPEAKER,CHANNEL_RR  },     
    { OP_AUD_DELAY_SPEAKER,CHANNEL_SWL },
    { OP_AUD_DELAY_SPEAKER,CHANNEL_SWR },
    
    { OP_AUD_DC_SET       ,0xff           },
    
    { OP_AUD_PHASE_SHIFT  ,CHANNEL_FL  }, 
    { OP_AUD_PHASE_SHIFT  ,CHANNEL_FR  }, 
    { OP_AUD_PHASE_SHIFT  ,CHANNEL_RL  }, 
    { OP_AUD_PHASE_SHIFT  ,CHANNEL_RR  },
    { OP_AUD_PHASE_SHIFT  ,CHANNEL_SWL },
    { OP_AUD_PHASE_SHIFT  ,CHANNEL_SWR },
    
    { OP_AUD_XOVER_PRESET ,0xff           },
    
    { OP_AUD_XOVER_LEVEL  ,CO_CH_F_HPF },     //4Set Xover Channel's Level: + Channel+ Level            
    { OP_AUD_XOVER_COF      ,CO_CH_F_HPF },         //4 Set Xover Channel's CoF: + Channel+ CoF        
    { OP_AUD_XOVER_SLOPE  ,CO_CH_F_HPF },    //4 Set Xover Channel's Slope: + Channel+ Slope     
    
    { OP_AUD_XOVER_LEVEL  ,CO_CH_R_HPF },     //4Set Xover Channel's Level: + Channel+ Level            
    { OP_AUD_XOVER_COF      ,CO_CH_R_HPF },         //4 Set Xover Channel's CoF: + Channel+ CoF        
    { OP_AUD_XOVER_SLOPE  ,CO_CH_R_HPF },    //4 Set Xover Channel's Slope: + Channel+ Slope 
    
    { OP_AUD_XOVER_LEVEL  ,CO_CH_SW_LPF },      //4Set Xover Channel's Level: + Channel+ Level             
    { OP_AUD_XOVER_COF      ,CO_CH_SW_LPF },           //4 Set Xover Channel's CoF: + Channel+ CoF          
    { OP_AUD_XOVER_SLOPE  ,CO_CH_SW_LPF },      //4 Set Xover Channel's Slope: + Channel+ Slope         

    { OP_AUD_UBASS_SET      ,0xff           },
    { OP_AUD_UBASS_LEVEL  ,0xff           },
    { OP_AUD_BEEP_VOL      ,0xff           },
    { OP_AUD_CAR_STYLE  ,0xff           },
};

uint8_t const g_GeqSetupIndexTbl[][2] =
{
    { OP_AUD_GEQ_SEL      ,0xff           },
    
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_1   },
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_2   },
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_3   },
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_4   },
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_5   },
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_6   },
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_7   },
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_8   },
    { OP_AUD_GEQ_GAIN      ,EQ_BAND_9   },

    { OP_AUD_GEQ_CF     ,EQ_BAND_1     },
    { OP_AUD_GEQ_CF     ,EQ_BAND_2     },
    { OP_AUD_GEQ_CF     ,EQ_BAND_3     },
    { OP_AUD_GEQ_CF     ,EQ_BAND_4     },
    { OP_AUD_GEQ_CF     ,EQ_BAND_5     },
    { OP_AUD_GEQ_CF     ,EQ_BAND_6     },
    { OP_AUD_GEQ_CF     ,EQ_BAND_7     },
    { OP_AUD_GEQ_CF     ,EQ_BAND_8     },
    { OP_AUD_GEQ_CF     ,EQ_BAND_9     },

    
    { OP_AUD_GEQ_Q       ,EQ_BAND_1    },
    { OP_AUD_GEQ_Q       ,EQ_BAND_2    },
    { OP_AUD_GEQ_Q       ,EQ_BAND_3    },
    { OP_AUD_GEQ_Q       ,EQ_BAND_4    },
    { OP_AUD_GEQ_Q       ,EQ_BAND_5    },
    { OP_AUD_GEQ_Q       ,EQ_BAND_6    },
    { OP_AUD_GEQ_Q       ,EQ_BAND_7    },
    { OP_AUD_GEQ_Q       ,EQ_BAND_8    },
    { OP_AUD_GEQ_Q       ,EQ_BAND_9    },
    
    
    
};

/******************************************************************************/

tMSG_BUF la_tHmiMsgBuf[D_HMI_MSG_QUE_DEEP];
tRING_QUE l_tHmiMsgQue;
uint16_t McuPowerResetWaitTime = 0;
uint8_t McuResetStep = 0;
uint16_t McuResetWaitTime = 0;


uint8_t HMI_Init(void)
{
    McuResetStep = 0;
    //McuResetWaitTime = 0;
    McuPowerResetWaitTime = 0;
    HMI_KeyInit();
    return TRUE;
}

void HMI_AudioBlockSave(uint8_t AudioSetType, uint8_t Param)
{
	uint8_t UpFlag = 0;
	extern tEEP_DATA_BLOCK l_tEepSysRomData;
	switch(AudioSetType)
	{
		case OP_AUD_FAD_SEL:
			g_tSysRomData.tAudioBlock.Fader = Param;
			UpFlag = 1;
			break;
		case OP_AUD_BAL_SEL:
			g_tSysRomData.tAudioBlock.Balance = Param;
			UpFlag = 1;
			break;
		case OP_AUD_BASS_GAIN_SEL:
			g_tSysRomData.tAudioBlock.BassGain = Param;
			g_tSysRomData.tAudioBlock.Type = GEQ_MODE_CUSTOM;
			UpFlag = 1;
			break;
		case OP_AUD_MID_GAIN_SEL:
			g_tSysRomData.tAudioBlock.MidGain = Param;
			g_tSysRomData.tAudioBlock.Type = GEQ_MODE_CUSTOM;
			UpFlag = 1;
			break;
		case OP_AUD_TREBLE_GAIN_SEL:
			g_tSysRomData.tAudioBlock.TrebleGain = Param;
			g_tSysRomData.tAudioBlock.Type = GEQ_MODE_CUSTOM;
			UpFlag = 1;
			break;

		case OP_AUD_VOL_INC:
		case	OP_AUD_VOL_DEC:
			//在Audio_GetVolType()中写入eep
			break;
		case OP_AUD_SVOL_MEDIA:
			g_tSysRomData.tAudioBlock.SysVol = Param;
			UpFlag = 1;
			break;
		case OP_AUD_SVOL_PHONE:
			g_tSysRomData.tAudioBlock.BtVol = Param;
			UpFlag = 1;
			break;
		case OP_AUD_SVOL_NAVI:
			g_tSysRomData.tAudioBlock.NaviVol = Param;
			UpFlag = 1;
			break;

		default:
			break;
	}
        if(1==UpFlag)
        {
	    	g_tSysRomData.tScrBlock.cBaseBR= g_BKHandLevel;
	    	EEP_CreateBlockChkSum(&l_tEepSysRomData);
	    	EEP_WriteStart(&l_tEepSysRomData,1);
        }
}



void HMI_MediaHandle(tMSG_BUF* p_tMsg)
{
    uint16_t Op = (p_tMsg->iSid);
    uint8_t* p_data = p_tMsg->uData.a_cData;
    hmi_printf(_T("HMI_MediaHandle id=%d,sid=%d",p_tMsg->Id,p_tMsg->iSid));
    hmi_printf(_T("      data:%d,%d,%d,%d\n",p_data[0],p_data[1],p_data[2],p_data[3]));
    switch(p_tMsg->Id)
    {
        case MS_UI_UPLOAD_INFO:
            _SendMsgToMedia(MS_UI_UPLOAD_INFO,Op,p_tMsg->uData.p_cData);
        break;

        case MS_UI_SETTING:
            switch(p_tMsg->iSid)
            {
                case (uint8_t)OP_LOAD_SET_AUDIO:
                {
                    uint8_t bSettingIndex = p_data[0];
                    uint8_t Param = p_data[1];
				    uint8_t AudioSetType = g_AudSetupIndexTbl[bSettingIndex];
					hmi_printf(_T("------audio data  save to eeprom------\n"));
				    HMI_AudioBlockSave(AudioSetType, Param);
                    _SendFullMsgToAudio(MS_AUDIO_CMD, AudioSetType, Param,0,0,0);
                }
                break;

                case (uint8_t)OP_LOAD_SET_6CH_VOL:
                break;
                
                case (uint8_t)OP_LOAD_SET_GENERAL:

                    SYS_ExecGenSetting(p_data[0],p_data[1]);
                break;

                case (uint8_t)OP_LOAD_SET_ASP:
                {
                    uint8_t bSettingIndex = p_data[0];
                    uint8_t Param = p_data[1];
                    uint8_t type = g_AspSetupIndexTbl[bSettingIndex][1];
                    if(type == 0xff)type = Param;
                    _SendFullMsgToAudio(MS_AUDIO_CMD, g_AspSetupIndexTbl[bSettingIndex][0],type,Param,0,0);
                }
                break;

                case (uint8_t)OP_LOAD_SET_GEQ:
                {
                    uint8_t bSettingIndex = p_data[0];
                    uint8_t Param = p_data[1];
                    uint8_t type = g_GeqSetupIndexTbl[bSettingIndex][1];
                    if(type == 0xff)
		    {
			type = Param;
			g_tSysRomData.tAudioBlock.Type = Param;
			g_tSysRomData.tScrBlock.cBaseBR= g_BKHandLevel;
			EEP_CreateBlockChkSum(&l_tEepSysRomData);
			EEP_WriteStart(&l_tEepSysRomData,1);
		    }
                    _SendFullMsgToAudio(MS_AUDIO_CMD, g_GeqSetupIndexTbl[bSettingIndex][0],type,Param,0,0);
                }
                break;
                
                case (uint8_t)OP_LOAD_SET_PEQ:
                break;

                case (uint8_t)OP_LOAD_SET_CH_GAIN:
                {
                     uint8_t Op = 0;
                     uint8_t bSettingIndex = p_data[0];
                     uint8_t Param = p_data[1];
                     if(bSettingIndex < 19)Op  = OP_AUD_SRC_SCALER;
                     else 
                     {    
                          Op  = OP_AUD_CHANNEL_GAIN;
                          bSettingIndex -= 19;
                     }
                     _SendFullMsgToAudio(MS_AUDIO_CMD, Op ,bSettingIndex,Param,0,0);
                }
                break;

                case (uint8_t)OP_LOAD_SET_SCREEN:
                {
                    
                    uint8_t bSettingIndex = p_data[0] + SCR_ID_BL_LVE;
                    uint8_t Param = p_data[1];
		    g_tSysRomData.uGenBlock.tBlock.tFlag3.bAuto_Dimmer_Set = 0;			
                    SYS_ExecGenSetting(bSettingIndex,Param);
            	    g_BKHandLevel = Param;
                }
                break;

                case (uint8_t)OP_LOAD_SET_TUNERFREQ:
                    _SendMsgToSRC(MS_SRC_DISTRIBUTE_CMD,(SRC_TYPE_TUNER<<8)|OP_TUNER_SET_DIRECT_TUNE,p_tMsg->uData.p_cData);
                break;
		 case (uint8_t)OP_LOAD_SET_VEHICLE:
		 	break;
		 case (uint8_t)OP_LOAD_SET_DIGITALOVERLAY:
		 	if((fTw8836.CvbsCurType == VIDEO_CVBS_CAM1) || (fTw8836.CvbsCurType == VIDEO_CVBS_CAM2))
			{
				hmi_printf(_T("===========OP_LOAD_SET_DIGITALOVERLAY==========\n"));
				fTw8836.ADI7186_OverlayFlag = 1;
			}
		 	break;
	       case (uint8_t)OP_LOAD_SET_CAMLINEDEAL:
		   	   //uint8_t Park_Mode=(p_data[0]<<6);
		   	    SendParkModeToBus(p_data[0]);
			    hmi_printf(_T("p_data[0]=%d\n",p_data[0]));
			   break;	
		case (uint8_t)OP_LOAD_SET_REVERSESTART:
			   fTw8836.ADI7186_ReverseStartFlag=1;
			    fTw8836.AVM_OsShowFlag=1;
			    hmi_printf(_T("******REVERSESTART\n"));
			   break;
              case (uint8_t)OP_LOAD_SET_REVERSESTOP:
			   fTw8836.ADI7186_ReverseStopFlag=1;
			    fTw8836.AVM_OsShowFlag=0;
			    hmi_printf(_T("******REVERSESTOP\n"));
			  break;
           default:
                     break;
            }
        break;

    default:
        break;

    }
}

/****************************************************************************
 * @function	HMI_UiccHandle
 * @brief  	Handler UICC Message From APU
 * @param
 * @retval 	1- Message has been dealed; 0- not deal 
 * @attention:  null
****************************************************************************/
uint8_t HMI_UiccHandle(tMSG_BUF* p_tMsg)
{
    uint8_t param = 0;
    uint16_t Op = p_tMsg->iSid;
    uint8_t Ret = 1;

    switch(Op)
    {
        case UICC_VIDEO_SWEN:
            _SendMsgToVideo(MS_VIDEO_SET_OCH,SRC_TYPE_NUM,1);
        break;
        case UICC_FRONT_ZONE_TS:
        {
             uint8_t id = p_tMsg->uData.a_cData[0];
             if(id != SOURCE_SYS_STANDBY)
             {
             	hmi_printf(_T("SourceChange:%d\n",p_tMsg->uData.a_cData[0]));
				//if((id != SOURCE_SD) && (id != SOURCE_DVR))//snake20160920 delete ..snake20160919 切换到DVR的时候,不能切源,不然会造成DVR的时候,后台不能播放多媒体的声音   DVR用的源ID是source_sd
				{
					_SendMsgToSRC(MS_SRC_SET_FRONT_UIID,id,NULL);
				}
             }
        }
        break;
        case UICC_REAR_ZONE_TS:
        {
            uint8_t id = p_tMsg->uData.a_cData[0];
            if(id >= SOURCE_NUM)
            {
                _SendMsgToSRC(MS_SRC_SET_REAR_TYPE,SRC_TYPE_REAR_OFF,TRUE);	
            }
            else
            {
                _SendMsgToSRC(MS_SRC_SET_REAR_UIID,id,NULL);
            }
        }
        break;
        case UICC_BEEP_ONLY_TS:
			if(SysWorkStatusGrp.SysApuStandyMode) break;
            _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_ACK,BEEP_ON,0,0);
            break;

        case UICC_BEEP_FAIL_TS:
            _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_NCK,BEEP_ON,0,0);
            break;

        case UICC_MONITOR_OP:
	     if(p_tMsg->uData.a_cData[0] == 0x00)
	     {
	     	if((g_tMcuDevState.uIOState.bits.Reverse_Flag == 0) && (g_tMcuDevState.uDetect.bits.Blind_Flag== 0))
	        {
		        _SendMsgToPM(MS_PM_TFT_BL_CMD, TFT_BL_OFF, NULL);
	        }
	     }
	     else if(p_tMsg->uData.a_cData[0] == 0x01)
	     {
	     	//snake20161026在倒车和盲区的时候,开屏有MCU来决定,过滤开屏消息,防止出现图像重叠的问题...
	     	if((g_tMcuDevState.uIOState.bits.Reverse_Flag == 0) && (g_tMcuDevState.uDetect.bits.Blind_Flag== 0))
				_SendMsgToPM(MS_PM_TFT_BL_CMD, TFT_BL_ON, NULL); 
	     }
	    
        break;
		
        case UICC_BT_PHONE_AUDIO:
		_SendMsgToSRC(MS_INPUT_UI,UICC_STOP_SEEK,NULL); 
        _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MIX_REQ,SRC_TYPE_NAVI_AUDIO,0,0,0);	
		if(p_tMsg->uData.a_cData[0]==0)
		{
			_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_BT_PHONE,0);    
			SysWorkStatusGrp.SysBtCallFlag = 0;
		}
		else
		{
			_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_BT_PHONE,1);    
			SysWorkStatusGrp.SysBtCallFlag = 1;
		}
            break;

         case UICC_NAVI_AUDIO:
		if(SysWorkStatusGrp.SysApuStandyMode)  break;
        	g_tSysRomData.uGenBlock.tBlock.tFlag3.bNavi_Guidance_Mode=1;//forMIX keilee20140509
            if(2 == g_tSysRomData.uGenBlock.tBlock.tFlag3.bNavi_Guidance_Mode)  //Interrupt
            {
                _SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_NAVI_AUDIO,p_tMsg->uData.a_cData[0]); 
            }
            else if(1 == g_tSysRomData.uGenBlock.tBlock.tFlag3.bNavi_Guidance_Mode) // Mix
            {
                _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MIX_REQ,SRC_TYPE_NAVI_AUDIO,p_tMsg->uData.a_cData[0],0,0);	
            }
            break;
        case UICC_3G_PHONE_AUDIO:
        	_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MIX_REQ,SRC_TYPE_NAVI_AUDIO,0,0,0);	
             _SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_3G_PHONE,p_tMsg->uData.a_cData[0]);   
            break;
            

        case UICC_APP_PROMPT_TONE:
		if(SysWorkStatusGrp.SysApuStandyMode)  break;
              _SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_APP_TONE,p_tMsg->uData.a_cData[0]); 
         break;

        case UICC_VR_STATE:
            _SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_VR,p_tMsg->uData.a_cData[0]); 
            break;

        case UICC_MUTE:
		_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE,p_tMsg->uData.a_cData[0],0,0,0);
            break;

        case UICC_VOLUME_DOWN:
            _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_DEC,1,0,0,0);
            break;

        case UICC_VOLUME_UP:
            _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_INC,1,0,0,0);
        break;
	  case UICC_USB_MODE:
	  	if(p_tMsg->uData.a_cData[0] == 0x00)		//HOST MODE
	  	{
	  	 	IO_Set(IO_IDX_USB_HOST, PIN_OUTPUT,VALID); 
	  	}
		else if(p_tMsg->uData.a_cData[0] == 0x01)	// SLAVE MODE
		{
			IO_Set(IO_IDX_USB_HOST, PIN_OUTPUT,INVALID);
		}
		hmi_printf(_T("UICC_USB_MODE:%d\n",p_tMsg->uData.a_cData[0]));
	  break;
	  case UICC_INFO_REQ:
		OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_SYS_STATE_INFO,NULL);
	  	break;
	  case UICC_COMM_SPY:
	  	if(p_tMsg->uData.a_cData[0] == 0x00)
	  	{
	  		SysWorkStatusGrp.SysCommSpySwitch  = 0;
	  	}
		else if(p_tMsg->uData.a_cData[0] == 0x01)
		{
			SysWorkStatusGrp.SysCommSpySwitch  = 1;
		}
	  	break;
	 case UICC_SYS_RESTART:
	 	_SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_RESET,NULL);
	 	break;
	case UICC_DEFAULT_FACT:
		hmi_printf(_T("UICC_Factory_Setting:   %d   \n",p_tMsg->uData.a_cData[0]));
		if(p_tMsg->uData.a_cData[0] == 0x01)
		{
			if(l_tPwrCB.eEEPState == OP_DEV_STATE_NORMAL)
	     		{
				_SendMsgToHMI(MS_SYS_LOAD_FACTORY_INFO,0,NULL);
			}
			else
			{
				_SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_RESET,NULL);
			}
			
			_SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_TEST,NULL);		//Enter test mode.
		}
		else if(p_tMsg->uData.a_cData[0] == 0x00)
		{
			_SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_TEST,(void*)0xffff);	//exit test mode.
		}
		else if(p_tMsg->uData.a_cData[0] == 0x02)
		{
                     fTw8836.ADI7186OVERLAYDisable  = 1;//恢复出厂设置去掉overlay
		}
	    break;
	case UICC_TBOX_AUDIO:
		param = p_tMsg->uData.a_cData[0] && 1;
		_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_CAR_TBOX,param);
		break;
	case UICC_CAMERA:
		break;
	case UICC_OSD_OVERLAY:
		break;
        default:
            	Ret = 0;
        	break;

        
    }
	return Ret;
}


void HMI_TunerHandle(tMSG_BUF* p_tMsg)
{
    bool bUpload = TRUE;
    uint16_t Op =  (p_tMsg->iSid);
    void* p_vData =  p_tMsg->uData.p_cData;

    switch(Op)
    {
        case OP_TUNER_UPD_CURRENT_BAND:
            Op = OP_INFO_RADIOINFO;  //Radio Info Update
            _SendMsgToMedia(MS_UI_UPLOAD_INFO, Op, p_vData);

            Op = OP_INFO_RADIOPRESETFREQLIST; //Frequency List Update
            break; 

        case OP_TUNER_UPD_CURRENTLY:    
        case OP_TUNER_UPD_CURRENT_FREQ:
        case OP_TUNER_UPD_CURRENT_PRESET:    
        case OP_TUNER_UPD_SEEK_STATE:
        case OP_TUNER_UPD_VALID_HIGHLIGHT:    
            Op = OP_INFO_RADIOINFO; //Radio Info Update
            break;

        case OP_TUNER_UPD_PRESET_LIST:
        case OP_TUNER_UPD_ONE_PRESET:
            Op = OP_INFO_RADIOPRESETFREQLIST;//Frequency List Update
            break;

        case OP_TUNER_UPD_SIGNAL_STR:    
            Op = OP_INFO_RADIOSIGNALLEVEL;  //Signal Strength Update
            break;

        case OP_TUNER_UPD_VALID_LIST:
            Op = OP_INFO_RADIOSTATIONLIST; //Valid List Update
            break;
	 
        case OP_RDS_UPD_STATUS:
            Op = OP_INFO_RDS_INFO; //RDS Info Update
            break;
        case OP_RDS_UPD_PS_NAME:
            Op = OP_INFO_RDS_PS_NAME; //
            break;

        case OP_RDS_UPD_CURRENT_PTY:
            Op = OP_INFO_RDS_CURRPTY; //
            break;

        case OP_RDS_UPD_RT:
            Op = OP_INFO_RDS_RT_INFO; //
            break;  
		case OP_TUNER_UPD_AREA:
			Op = OP_INFO_RADIOAREA;
			break;
        default:
            bUpload = FALSE;
            break;
    }

    if(bUpload)
    {
        _SendMsgToMedia(MS_UI_UPLOAD_INFO, Op, p_vData);
        if(Op == OP_INFO_RADIOINFO)
        {
            _SendMsgToCanbus(MS_UI_UPLOAD_INFO, Op, p_vData);
        }
    }
}


void HMI_AudioHandle(tMSG_BUF* p_tMsg)
{
    uint16_t Op = (p_tMsg->iSid);
    uint8_t* p_vData =  p_tMsg->uData.a_cData;
    if(p_tMsg->Id == MS_AUDIO_UPLOAD_INFO)
    {
        switch(Op)
        {
               case OP_AUDUP_VOL:   // + Vol Value  + Vol Type (0 Sys; 1 Bt; 2 Navi)
               {
            		_SendFullMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_VOLUME,  p_vData[1],p_vData[0], 0, 0);
#ifdef CAN_MODULE_V850CAN        // use V850 mcu inner can module
            if(p_vData[1] == VOL_TYPE_SYS)/*send system volume to CAN module */
            {
                _SendMsgToCanbus(MS_AUDIO_UPLOAD_INFO, OP_AUDUP_VOL, p_tMsg->uData.p_cData);
            }
#endif
        }
        break;

        case OP_AUDUP_RVOL:
            break;

            case OP_AUDUP_MUTE:
                g_tMcuDevState.uIOState.bits.MuteOn = (p_vData[0] && 0x01);
                _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
#ifdef CAN_MODULE_V850CAN       // use V850 mcu inner can module
            _SendMsgToCanbus(MS_AUDIO_UPLOAD_INFO, OP_AUDUP_MUTE, p_tMsg->uData.p_cData);
#endif
                break;
    
            //Audio Basic Packet Update
            case OP_AUDUP_BASS:
            case OP_AUDUP_MID:
            case OP_AUDUP_TREBLE:
            case OP_AUDUP_TONE:
            case OP_AUDUP_BAL:
            case OP_AUDUP_FAD:
            case OP_AUDUP_BF:    
            case OP_AUDUP_LOUDNESS:
            case OP_AUDUP_SUBWOOFER:    
            case OP_AUDUP_BASIC:
            case OP_AUDUP_GEQ:				
                _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_AUDIOSETTING,p_tMsg->uData.p_cData);
                break;

            case OP_AUDUP_ADV:
            case OP_AUDUP_BEEP: 
            case OP_AUDUP_DC:    
            case OP_AUDUP_PHASESHIFT:
            case OP_AUDUP_DELAY:
            case OP_AUDUP_XOVER:
            case OP_AUDUP_UBASS:    
                _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_ASP_SETTING,p_tMsg->uData.p_cData);
            break;
            
            case OP_AUDUP_CHGAIN:
                _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_CH_GAIN,p_tMsg->uData.p_cData);
            break;
            default:
                break;
        }
    }
}

void HMI_PmMsgHandle(tMSG_BUF* p_tMsg)
{
    uint16_t Op = (p_tMsg->iSid);
    if(MS_PM_STATE == p_tMsg->Id)
    {
    	 switch(Op)
    	 {
    	 	case OP_PM_STATE_RESET:
		case OP_PM_STATE_OFF:
		case OP_PM_STATE_ERR:
		case OP_PM_STATE_SLEEP:
			SysWorkStatusGrp.SysBtCallFlag = 0;
			HMI_AutoTestInit();
			break;
		default:
			break;
	 }
        _SendMsgToSRC(MS_PM_STATE, Op, NULL);
        _SendMsgToMedia(MS_PM_STATE, Op, NULL);
        _SendMsgToAudio(MS_PM_STATE, Op, NULL);
        _SendMsgToVideo(MS_PM_STATE, Op, NULL);
        _SendMsgToTmc(MS_PM_STATE, Op, NULL);
 //       _SendMsgToDISC(MS_PM_STATE, Op, NULL);
        _InsertMsgToCANbus(MS_PM_STATE, Op, NULL);
        _SendMsgToMult_Func(MS_PM_STATE, Op,NULL);
    }
    else if(p_tMsg->Id == MS_PM_AWAKE)
    {
        switch(Op)
        {
            case OP_PM_AWAKE_DISCIN:
                _SendMsgToPM(MS_PM_AWAKE, OP_PM_AWAKE_DISCIN, NULL);
            break;
            case OP_PM_AWAKE_EJCKEY: 
                _SendMsgToPM(MS_PM_AWAKE, OP_PM_AWAKE_EJCKEY, NULL);
   //             _SendMsgToDISC(MS_PM_STATE, OP_PM_STATE_ON, NULL);
  //              _SendMsgToDISC(MS_SYS_DISC_INFO, OP_DEV_STATE_AUTO, NULL);
            break;
        default:
            break;
        }
#ifdef CAN_MODULE_V850CAN       // use V850 mcu inner can module
        _InsertMsgToCANbus(MS_PM_AWAKE, Op, NULL);
#endif
    }
	else if(p_tMsg->Id == MS_PM_TFT_BL_CMD)
	{
		/* TFT back light control command deal */
		_SendMsgToPM(MS_PM_TFT_BL_CMD, Op, NULL);
	}
}


void HMI_SourceHandle(tMSG_BUF* p_tMsg)
{
    uint16_t Op = p_tMsg->iSid;
    if(MS_SRC_SYS_CMD == p_tMsg->Id)
    {
        switch(Op)
        {
            case OP_SRC_SW_FINISH:		//NOT USED
               // _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD, UICC_FRONT_SRC+p_tMsg->uData.a_cData[0]
               //                   ,p_tMsg->uData.a_cData[1], 0, 0);
            break;
            case OP_SRC_SW_START:
                if(SRC_ZONE_FRONT == p_tMsg->uData.a_cData[0])
                {
                    _SendMsgToVideo(MS_VIDEO_SET_OCH,SRC_TYPE_NUM,0);
                }
		#ifdef CAN_MODULE_V850CAN     
		/*
		  * 仅将前端源发给CANBUS用于娱乐CAN处理，后台源不用发
		  */
		if(p_tMsg->uData.a_cData[0] == SRC_ZONE_FRONT)
		{
            		_InsertMsgToCANbus(MS_SRC_SYS_CMD, Op, p_tMsg->uData.p_cData);
		}
		#endif
            break;
            case OP_SRC_SW_FAIL:
            break;
            case OP_SRC_AUTO_NEXT:
               // _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD, UICC_SRC,0, 0, 0);
               // _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD, UICC_SRC,0, 0, 0);
                
            break;
            default:
			break; 
            
        }
    }
    else if(MS_SRC_UPLOAD_INFO == p_tMsg->Id)
    {
        eSOURCE_TYPE eSrc = (uint8_t)(Op>>8);
        switch(eSrc)
        {
        case SRC_TYPE_TUNER:
            HMI_TunerHandle(p_tMsg);
            break;

        default:
            break;
        }
  
    }
    else
    {
        _SendMsgToSRC(p_tMsg->Id,Op,p_tMsg->uData.p_cData);
    }
}

void HMI_CANHandle(tMSG_BUF* p_tMsg)
{
	uint8_t  OP=(p_tMsg->iSid>>8)&0xff;
	uint8_t  iSid=(uint8_t)p_tMsg->iSid;
       uint8_t* p_vData =  p_tMsg->uData.a_cData;
	switch(OP)
	{
		case OMS_CAN_TX_SYS:
			switch(iSid)
			{
				case OP_CAN_TX_CAN_KNOB:
					if(p_tMsg->uData.a_cData[0] == 0x00)	// sel 
					{
						if(p_tMsg->uData.a_cData[1] == 0x00)		//left rotate
						{
							 _SendFullMsgToHMI(MS_INPUT_KEY,OP_ENCODE_TURN_LEFT,\
		                            			CK_SEL_LEFT,0,OP_ENCODE_TURN_LEFT,0);
						}
						else   
						{
							 _SendFullMsgToHMI(MS_INPUT_KEY,OP_ENCODE_TURN_RIGHT,\
		                            			CK_SEL_RIGHT,0,OP_ENCODE_TURN_RIGHT,0);
						}
					}
					else if(p_tMsg->uData.a_cData[0] == 0x01)	// vol 
					{
						if(p_tMsg->uData.a_cData[1] == 0x00)		//left rotate
						{
							 _SendFullMsgToHMI(MS_INPUT_KEY,OP_ENCODE_TURN_LEFT,\
		                            			CK_VOL_DEC,0,OP_ENCODE_TURN_LEFT,0);
						}
						else
						{
							 _SendFullMsgToHMI(MS_INPUT_KEY,OP_ENCODE_TURN_RIGHT,\
		                            			CK_VOL_INC,0,OP_ENCODE_TURN_RIGHT,0);
						}
					}
					break;
				case OP_CAN_TX_PM_REQ:
					 _SendMsgToPM(MS_SYS_BUS_INFO,p_tMsg->uData.a_cData[0],NULL);
					break;
				default:
					break;
			}
			break;
		case OMS_CAN_TX_CAR:
			//TaskCAN_debug(_T("===OP_INFO_CANBUS_DATA\n"));
			_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_CANBUS_DATA, p_tMsg->uData.p_cData); 
			break;
		case CAN_PRJ_ID_CHANA_S401:
			TaskCAN_debug(_T("===CAN_PRJ_ID_CHANA_S401==\n"));
			_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_PRJ_DVRSTATE, p_tMsg->uData.p_cData); 
			break;
		case CAN_PRJ_ID_CHANA_R103H:
			//TaskCAN_debug(_T("===CAN_PRJ_ID_CHANA_R103H==\n"));
			_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_PRJ_DVRSTATE, p_tMsg->uData.p_cData); 
			break;
		default:
			break;
	}
}

extern uint8_t AvmExistFlag;


void HMI_SysHandle(tMSG_BUF* p_tMsg)
{
   uint16_t  iMsgType = p_tMsg->Id;
   uint16_t Op = p_tMsg->iSid;
   uint8_t msg[5];

   switch(iMsgType)
   {
       case MS_SYS_IO_INFO:
       {
			bool  bUpload = FALSE;
			uint8_t cData = (uint8_t)((uint32_t)(p_tMsg->uData.p_cData));
			uint8_t state = 0;
			switch(Op)
			{
				case IO_IDX_PARKING_DET:
					cData = cData || (!g_tSysRomData.uGenBlock.tBlock.tFlag4.bParking_Det_Mode);
					g_tMcuDevState.uIOState.bits.Car_Parking = cData;
					bUpload = TRUE;
					break;
				#ifdef D_ILL_ADC_CHECK
				case IO_IDX_ILL_DET:
					hmi_printf(_T("==IO_IDX_ILL_DET:%x\n",cData));	   
					if(cData < (LEVEL_VAILD - 1))//ill
					{
						g_tMcuDevState.uIOState.bits.Illumi_On = 1;
					}
					else if(cData == (LEVEL_VAILD - 1))//no ill
					{
						g_tMcuDevState.uIOState.bits.Illumi_On = 0;
					}
					SysWorkStatusGrp.SysILLlevel = cData;
					bUpload = TRUE;
					_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);
					
					break;
				#else
				case IO_IDX_ILL_DET:
					state = cData &1;
					g_tMcuDevState.uIOState.bits.Illumi_On = state;
					SysWorkStatusGrp.SysILLlevel = state?8:1;
					bUpload = TRUE;
					_SendMsgToCanbus(MS_SYS_IO_INFO,Op,p_tMsg->uData.p_cData);//snake20160921
					_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);
					hmi_printf(_T("ILL_In check IO:%x\n",cData));
					break;
				#endif
				
				case IO_IDX_REVERSE_DET:
					cData = cData && 1;
					hmi_printf(_T("HMI:Reverse IO:%x,g_tUpdataReverseParameter = %d,g_tUpdataBlindParameter = %d\n",cData,HMIStatusFlag.g_tUpdataReverseParameter,HMIStatusFlag.g_tUpdataBlindParameter));
					fTw8836.ADI7186OVERLAYDisable = 0;
					//if(IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE)==1)//只有ACC ON 才进倒车流程
					{
						if(AvmExistFlag == 0x00)
						{
							if(g_tMcuDevState.uIOState.bits.Reverse_Flag != cData)//snake20161205 频繁倒车,声音不恢复
							{
								Reverse_Flag = cData;
								HMIStatusFlag.g_tUpdataReverseParameter = 1; //开始切换倒车....
								_SendMsgToSRC(MS_INPUT_UI,UICC_STOP_SEEK,NULL);//snake20161008 注意,需要先停止搜索,在进行切源,不然会出现不能停止搜索的现象
								_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_REVERSE,cData);//全景下不用倒车流程
								hmi_printf(_T("Send Reverse State to src!!!!!\n"));
							}
						}
					}
					break;
               
               case IO_IDX_ACC_WAKE:
    		/* translate io  info to CAN module */
       	 	_SendMsgToCanbus(MS_SYS_IO_INFO,Op,p_tMsg->uData.p_cData);
			hmi_printf(_T("IO_IDX_ACC_WAKE=%x\n",cData));
               break;
	       case IO_IDX_LOCAL_ACC:
		   	cData = cData && 1;
			HMIStatusFlag.g_tCanbusWakeUpFlag = 0;
			if(cData == 0)
			{
				if(g_tMcuDevState.uIOState.bits.Reverse_Flag)
				{
					 _SendMsgToSRC(MS_SRC_SET_FLOAT_TYPE,SRC_TYPE_REVERSE,0);//ACC OFF倒车档退出倒车
				}
			}
			else
			{
				if(VIDEO_SYS_RUN != VideoGetSysState())
				{
					hmi_printf(_T("ACC ON..........Clear fTw8836.ADI7186InitProgramme!!!!!\n"));
					fTw8836.ADI7186InitProgramme = 0;
                    VideoSetSysState(VIDEO_SYS_STARTUP);
                    sVideo.FuncStep = VIDEO_FUNC_STARTUP;
				}
				 Reverse_Flag = 0;
				 //IO_ResetState(IO_IDX_REVERSE_DET,INVALID);
				hmi_printf(_T("ACC ON:fTw8836.ADI7186InitProgramme = %d,l_tMediaCB.eState = %d...........\n",fTw8836.ADI7186InitProgramme,l_tMediaCB.eState));				 
				#if 0
				if((fTw8836.ADI7186InitProgramme == 1) /*&& (l_tMediaCB.eState == MEDIA_STATE_RUNNING)*/)
				{
					PM_TftPowerSet(ON,0);
					g_tMcuDevState.uIOState.bits.LCD_Disp = 1;
					_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
					hmi_printf(_T("...........ACC ON,OPEN TFT................\n"));
				}
				#endif
			}
			//_SendMsgToSRC(MS_INPUT_UI,UICC_STOP_SEEK,NULL);//snake20161007 开关ACC的时候,退出自动搜索
		   hmi_printf(_T("LOCAL_ACC_State=%x\n",cData));
		 break;
               
        case IO_IDX_AUX_DET:
			state = cData &1;
			hmi_printf(_T("Aux_In check IO:%x\n",cData));
			if( g_tMcuDevState.uConnetState.bits.Aux_In != state)
			{
				g_tMcuDevState.uConnetState.bits.Aux_In = state;
				bUpload = TRUE;
			}
		break;

        case IO_IDX_AVM_DET://keilee20140618
			hmi_printf(_T("HMI:Blind IO:%x,g_tUpdataReverseParameter = %d,g_tUpdataBlindParameter = %d\n",cData,HMIStatusFlag.g_tUpdataReverseParameter,HMIStatusFlag.g_tUpdataBlindParameter));
          	//if(SRC_TYPE_AVOFF != SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME)->eSrcType)//snake20160927delete 不进行判断,提高盲区的优先级
          	{
	            if(cData)
	            {
	                _SendFullMsgToCanbus(MS_OTHER_AVM, OP_AVM_PRESS,0,0,0,0);
	            }
	            else
	            {
	                _SendFullMsgToCanbus(MS_OTHER_AVM, OP_AVM_RELEASE,0,0,0,0);
	            }
          	}
            break;

        case IO_IDX_BATTERY_DET:
            _SendMsgToMult_Func(IO_IDX_BATTERY_DET, cData,NULL);
            break;
	 case IO_IDX_DISC_IN_DET:
	 	state = cData &1;
		hmi_printf(_T("Disc_In check IO:%x\n",cData));
		if( g_tMcuDevState.uConnetState.bits.Disc_Inserted != state)
		{
			g_tMcuDevState.uConnetState.bits.Disc_Inserted = state;
			bUpload = TRUE;
		}
	 	break;

        default:
            break;
        }

           if(bUpload)
		{
			_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
		}

           _SendMsgToMedia(MS_SYS_IO_INFO,Op,p_tMsg->uData.p_cData);
           _SendMsgToPM(MS_SYS_IO_INFO,Op,p_tMsg->uData.p_cData);
           _SendMsgToSRC(MS_SYS_IO_INFO,Op,p_tMsg->uData.p_cData);
           _SendMsgToAudio(MS_SYS_IO_INFO,Op,p_tMsg->uData.p_cData);
       }
       break;
       
       case MS_SYS_AUDIO_STATE:
       case MS_SYS_VIDEO_STATE:
           _SendMsgToSRC(iMsgType,Op,NULL);
       break;
       
       case MS_SYS_BUS_INFO:
        HMI_CANHandle(p_tMsg);
        break;

    case MS_SYS_BUS_IO_INFO:
        _SendMsgToPM(MS_SYS_BUS_IO_INFO,Op,p_tMsg->uData.p_cData);
        break;

       case MS_SYS_DEV_TYPE:
           switch(Op)
           {
               case DEV_IDX_TUNER:
               break;
               case DEV_IDX_MPEG:
               {
                   _SendMsgToAudio(iMsgType,Op,p_tMsg->uData.p_cData);
               }
	        default:
	            break;
           }
       break;

       case MS_SYS_DEV_ON_APU_INFO:
        g_tApuDevState.tDevflag.word = Op;
       break;
       case MS_SYS_DEV_ON_MCU_INFO:
           //The divices on mcu internal state. 
           //for example,if all io init,please notice the MCU_DEV_IDX_IO state
           //if you want to reset the IO control block,you must set it after received the MCU_DEV_IDX_IO NORMAL state
           
       break;
       case MS_SYS_DEV_STATE:
           switch(Op)
           {
               case DEV_IDX_EEPROM:
                   _SendMsgToPM(MS_SYS_DEV_STATE,DEV_IDX_EEPROM,p_tMsg->uData.p_cData);
               break;
               case DEV_IDX_MPEG:
                   _SendMsgToPM(MS_SYS_DEV_STATE,DEV_IDX_EEPROM,p_tMsg->uData.p_cData);
               break;
	        case DEV_IDX_APU:
	            if((uint8_t)((uint32_t)p_tMsg->uData.p_cData) == OP_DEV_STATE_RESET)
	            {
				IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
				IO_Set(IO_IDX_TFT_EN_IO,PIN_OUTPUT,OFF);
				while(1);
	            }
               break;
           }
       break;
       
       case MS_SYS_APU_INFO:
		_SendMsgToSRC(MS_SYS_APU_INFO,Op,NULL);
		_SendMsgToPM(MS_SYS_APU_INFO,Op,NULL);
		_SendMsgToAudio(MS_SYS_APU_INFO,Op,NULL);
		_SendMsgToVideo(MS_SYS_APU_INFO,Op,NULL);
		_SendMsgToCanbus(MS_SYS_APU_INFO,Op,NULL);
        	break;

       case MS_SYS_DISC_INFO:
           _SendMsgToPM(MS_SYS_DISC_INFO,Op,NULL);
           if(OP_DEV_STATE_NORMAL == Op)
           {
              _SendMsgToAudio(MS_SYS_DISC_INFO,Op,NULL); 
           }
       break;

       case MS_SYS_LOAD_FACTORY_INFO:
           	_SendMsgToEEP(MS_EEP_LOAD_FACTORY,0,NULL);
           	_SendMsgToSRC(MS_SYS_LOAD_FACTORY_INFO,0,NULL);
           	_SendMsgToAudio(MS_SYS_LOAD_FACTORY_INFO,0,NULL);
           	_SendMsgToVideo(MS_SYS_LOAD_FACTORY_INFO,0,NULL);
        	_SendMsgToCanbus(MS_SYS_LOAD_FACTORY_INFO,0,NULL);

       break;
       
   }
   
}


void HMI_EEPMsgHandle(tMSG_BUF* p_tMsg)
{
    extern tEEP_DATA_BLOCK l_tEepSysRomData;
    uint8_t cMsgType = (uint8_t)(p_tMsg->Id);
    uint8_t Op = (uint8_t)p_tMsg->iSid;
    switch(cMsgType)
    {
        case MS_EEP_LOAD_FACT_RET:
            if(Op == EEP_OPTION_COMPLETE)
            {
                OS_ClearNoInitBlock();
                Audio_FastHardMute(ON);
                IO_Set(IO_IDX_TFT_EN_IO,PIN_OUTPUT,OFF);
	        API_LoopDleay(60000); 
	        IO_Set(IO_IDX_AMP_STANDBY,PIN_OUTPUT,VALID);
	        API_LoopDleay(60000);
		 API_LoopDleay(60000);
		 API_LoopDleay(60000);
                PM_UnitPowerSet(PM_UNIT_ALL,OFF);
                while(1){}
            }
        break;
        case MS_EEP_READ_RET:
        break;
        case MS_EEP_WRITE_RET:
        break;
    default:
        break;
    }
}

//发送给源的消息， 在源逻辑中没有处理的消息，在这个函数集中处理。
void HMI_UsrSrcDropMsgHandle(tMSG_BUF* p_tMsg)
{ 
    uint16_t iMsgType = (p_tMsg->Id & MS_USER_MASK);
    switch(iMsgType)
    {
        case MS_INPUT_UI:
            HMI_UiccHandle(p_tMsg);
        break;
        case MS_INPUT_KEY:
        case MS_INPUT_FIR:
        case MS_INPUT_RIR:
	     #if 0
            iMsgType = (uint8_t)(p_tMsg->iSid);
	     switch(p_tMsg->uData.a_cData[0])
            {
                case CK_VOL_INC:
			 if(OP_KEY_ACTION_SP == iMsgType
		               ||OP_KEY_ACTION_LSREL == iMsgType                 //短按处理
		               ||OP_ENCODE_TURN_LEFT == iMsgType
		               ||OP_ENCODE_TURN_RIGHT == iMsgType
		               ||OP_KEY_ACTION_SH == iMsgType
		               ||OP_KEY_ACTION_LH == iMsgType)
			 {
				_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_INC,1,0,0,0);
				_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_ACK,BEEP_ON,0,0);
			 }
                break;

                case CK_VOL_DEC:
	                 if(OP_KEY_ACTION_SP == iMsgType
		               ||OP_KEY_ACTION_LSREL == iMsgType                 //短按处理
		               ||OP_ENCODE_TURN_LEFT == iMsgType
		               ||OP_ENCODE_TURN_RIGHT == iMsgType
		               ||OP_KEY_ACTION_SH == iMsgType
		               ||OP_KEY_ACTION_LH == iMsgType)
			 {
				_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_DEC,1,0,0,0);
				_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_ACK,BEEP_ON,0,0);
			 }
                break;
                case CK_MUTE:
			 if(OP_KEY_ACTION_SP == iMsgType
		               ||OP_KEY_ACTION_LSREL == iMsgType
		               ||OP_KEY_ACTION_LHREL == iMsgType
		               ||OP_KEY_ACTION_LREL == iMsgType)
			 {
                 		_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE,0,0,0,0);
				_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_ACK,BEEP_ON,0,0);
			 }
		    
                break;
               default:
		     p_tMsg->Id &= MS_USER_MASK;
                  SendKeyMsgToMedia(p_tMsg);
                break;
	     	}   
	#else
	 p_tMsg->Id &= MS_USER_MASK;
        SendKeyMsgToMedia(p_tMsg);
	 AutoTestKeyCheck(p_tMsg);
	#endif
        break;

    default:
        break;

    }
}


void Mcu_Reset_Fun(tMSG_BUF* p_tMsg)
{
    uint16_t iMsgType = (p_tMsg->Id & MS_USER_MASK);
    // hmi_printf(_T("Mcu_Reset_Fun=%d,%d\n",iMsgType,(uint8_t)(p_tMsg->iSid)));
    switch(iMsgType)
    {
    case MS_INPUT_KEY:
        iMsgType = (uint8_t)(p_tMsg->iSid);
        if((OP_KEY_ACTION_LH == iMsgType) /*|| (OP_KEY_ACTION_SH == iMsgType) || (OP_KEY_ACTION_SP == iMsgType) || (OP_KEY_ACTION_LP == iMsgType)*/)
        {
            switch(p_tMsg->uData.a_cData[0])
            {
            case CK_POWER:
                switch(McuResetStep)
                {
                case 0:
                    McuPowerResetWaitTime=1;
                    McuResetStep++;
                    break;

                case 1:
                    if(McuPowerResetWaitTime > (15000/_HMI_CORE_TIMING_))
                    {
                        Audio_SoftMute(SYSTEM_FRONT,MUTE_ON);
                        McuResetStep++;
                    }
                    break;

                case 2:
                    if(McuPowerResetWaitTime > (18000/_HMI_CORE_TIMING_))
                    {
                       // OS_ClearNoInitBlock();
                       // g_tSysRomData.uGenBlock.tBlock.tFlag3.bAuto_Dimmer_Set=1;//default autodimmer=on ztqin 20150112
                        Audio_HardMute(SYSTEM_FRONT,MUTE_ON);
                        IO_Set(IO_IDX_TFT_EN_IO,PIN_OUTPUT,OFF);
                        PM_UnitPowerSet(PM_UNIT_APU,OFF);
                        McuResetStep = 0;
                        McuPowerResetWaitTime = 0;
                        while(1);
                    }
                    break;
                }
                break;

            default:
                break;
            }

        }
        else if((OP_KEY_ACTION_SREL == iMsgType)||(OP_KEY_ACTION_SHREL == iMsgType)||(OP_KEY_ACTION_LREL == iMsgType)||(OP_KEY_ACTION_LHREL == iMsgType) || (OP_KEY_ACTION_LSREL == iMsgType))
        {
            if(McuResetStep == 2)
            {
                Audio_SoftMute(SYSTEM_FRONT,MUTE_OFF);
            }
            McuResetStep = 0;
            McuPowerResetWaitTime = 0;
        }
        break;

    default:
        break;
    }
}

void Mcu_SendApuReqPackage(uint8_t Gid, uint8_t Sid)
{
	if(Gid >= GID_MCU2APU_BASE)
	{
		Gid = Gid - GID_MCU2APU_BASE;
	}
	else
	{
		return;
	}
	switch(Gid)
	{
		case GID_MCU_TX_SETTING:
			switch(Sid)
			{
				case SID_MCU_TX_GENERALSETTING:
					OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SETTING,
	 									SID_MCU_TX_GENERALSETTING,
	 									(void *)&(g_tSysRomData.uGenBlock));
					break;
				case SID_MCU_TX_AUDIOSETTING:
					_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_AUDIOSETTING,&sAudioDat.sBasic);
					break;
				case SID_MCU_TX_SCREENSETTING:
					OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SETTING,
	 									SID_MCU_TX_SCREENSETTING,
	 									(void *)&(g_tSysRomData.tScrBlock));
					break;
				case SID_MCU_TX_DEVELOP://snake20170216
					OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SETTING,
	 									SID_MCU_TX_DEVELOP,
	 									(void *)&(g_tSysRomData.DevelopFlag));
					break;
				default:
					break;
			}
			break;
		case GID_MCU_TX_SYS_INFO:
			switch(Sid)
			{
				case SID_MCU_TX_VERSION:
					OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_VERSION,NULL);
					break;
				case SID_MCU_TX_DEVICESTATUS:
					OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_DEVICESTATUS,(void *)&g_tMcuDevState);
					break;
				case SID_MCU_TX_SYS_TIME_BASE:
					OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_SYS_TIME_BASE,NULL);
					break;
				case SID_MCU_TX_VOL_ALL:
					OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_VOL_ALL,NULL);
					break;
				case SID_MCU_TX_SYS_STATE_INFO:
					OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_SYS_STATE_INFO,NULL);
					break;
				default:
					break;
			}
			break;
		case GID_MCU_TX_RADIO_DATA:
			switch(Sid)
			{
				case SID_MCU_TX_RADIOINFO:
					_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_RADIOINFO, &sTunerDat);
					break;
				case SID_MCU_TX_RADIOSIGNALLEVEL:
					_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_RADIOSIGNALLEVEL, &sTunerDat);
					break;
				case SID_MCU_TX_RADIOPRESETFREQLIST:
					_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_RADIOPRESETFREQLIST, &sTunerDat);
					break;
				case SID_MCU_TX_RADIOSTATIONLIST:
					_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_RADIOSTATIONLIST, &sTunerKeep);
					break;
				case SID_MCU_TX_RDS_INFO:
					_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_RDS_INFO, &sTunerDat);
					break;
				case SID_MCU_TX_RADIOAREA://snake20160215 收音区域的请求返回...
					_SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_RADIOAREA, &sTunerKeep);
					break;
				default:
					break;
			}
			break; 
		case GID_MCU_TX_CAN_INFO:
			if(Sid != OP_CAN_TX_PRJ_SPCL)
			{
				CANTask_SendApiData(0x00,Sid, 1);		// BOLTE
			}
			break; 
		case GID_MCU_TX_PRJ_INFO:
				CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_S401,Sid, 1);
			break; 	
		default:
			break;
	}
}

void HMI_UserInputMsgHandle(tMSG_BUF* p_tMsgBuf)
{
    uint16_t iID = (p_tMsgBuf->Id);
    uint16_t iMsgType;
    uint8_t i,cTmp;

    switch(iID)
    {
        case MS_INPUT_KEY:
        {
            eHMI_KEY_DEV eKeyDev = p_tMsgBuf->uData.a_cData[2];
            if(eKeyDev > HMI_KEY_TMP_START)
            {
                _SendMsgToHMI(MS_HMI_SWC_SETTING,OP_SWC_SET_LOGIC_VALUE,p_tMsgBuf->uData.p_cData);
                break;
            }
        	Mcu_Reset_Fun(p_tMsgBuf);
        }
        case MS_INPUT_FIR:
        case MS_INPUT_RIR:
             _SendMsgToSRC(p_tMsgBuf->Id,p_tMsgBuf->iSid,p_tMsgBuf->uData.p_cData); 
        break;
        case MS_INPUT_UI:
            if(!HMI_UiccHandle(p_tMsgBuf))
            {
		_SendMsgToSRC(p_tMsgBuf->Id,p_tMsgBuf->iSid,p_tMsgBuf->uData.p_cData);
	     }
        break;
	case MS_INPUT_REQDATA:
	   Mcu_SendApuReqPackage(p_tMsgBuf->iSid,p_tMsgBuf->uData.a_cData[0]);
	 break;
    default :
        break;
    }
}

void HMI_MsgHandle(tMSG_BUF* p_tMsg)
{
    uint16_t iUserMsgType = p_tMsg->Id;
    uint16_t iGlbMsgType = MS_GLOBAL_MASK & iUserMsgType;
    if(iGlbMsgType)
    {
        switch(iGlbMsgType)
        {
            case MS_GLOBAL_SRC_DROP:
                HMI_UsrSrcDropMsgHandle(p_tMsg);
            break;
            case MS_GLOBAL_SRC_ANALYZE:
              // _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_ACK,BEEP_ON,0,0);
            break;
            case MS_GLOBAL_SRC_PROHIBITE:
            {
                tSOURCE* p_tSrc = (tSOURCE*)(p_tMsg->uData.p_cData);
                if(!p_tSrc->tFlag.field.bMuteBeep)
                {
                //    _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_NCK,BEEP_ON,0,0);
                }
            }
            break;
            default:
		break;
        }
    }
    else
    {
        if(iUserMsgType > MS_PM_START && iUserMsgType < MS_PM_END)
        {
            HMI_PmMsgHandle(p_tMsg);
        }
        else if(iUserMsgType > MS_UI_START && iUserMsgType < MS_UI_END)
        {
            HMI_MediaHandle(p_tMsg);
        }
        else if(iUserMsgType > MS_INPUT_START && iUserMsgType < MS_INPUT_END)
        {
            HMI_UserInputMsgHandle(p_tMsg);
        }
        else if(iUserMsgType > MS_SRC_START && iUserMsgType < MS_SRC_END)
        {
            HMI_SourceHandle(p_tMsg);
        }
        else if(iUserMsgType > MS_SYS_START && iUserMsgType < MS_SYS_END)
        {
            HMI_SysHandle(p_tMsg);
        }
        else if(iUserMsgType > MS_AUDIO_START && iUserMsgType < MS_AUDIO_END)
        {
            HMI_AudioHandle(p_tMsg);
        }
        else if((iUserMsgType > OP_FCT_TO_HMI_START) && ( iUserMsgType < OP_FCT_TO_HMI_END) )
        {
	//      HMI_FCT_Handle(p_tMsg);
        }
        else if(iUserMsgType > MS_HMI_START && iUserMsgType < MS_HMI_END)
        {
            switch(iUserMsgType)
            {
                case MS_HMI_SWC_SETTING:
                    HMI_SWCMsgHandle(p_tMsg);
                break;
            }
        }
        else if(iUserMsgType > MS_EEP_START && iUserMsgType < MS_EEP_END)
        {
            HMI_EEPMsgHandle(p_tMsg);
        }
    }
    
}


void HMI_Task(EVENT iEvt,eTASK_STATE state)
{
    
    switch(state)
    {
        case TASK_STATE_RUNNING:
        
	        if(iEvt & EVT_CORE_TICK_READY)
	        {
	            if(McuPowerResetWaitTime>0)
	                McuPowerResetWaitTime++;
	        }
			if(iEvt & EVT_MSG_READY)
			{
			    tMSG_BUF tMsg;
			    if(QUE_ERR_NONE == OS_GetMsgDir(&g_tHmiTaskCB,&tMsg))
			    {
			        HMI_MsgHandle(&tMsg);
			    }
			}
            
            
            HMI_KeyTask(iEvt);

			break;
        case TASK_STATE_READY:
            if(iEvt & EVT_MSG_READY)
            {
                tMSG_BUF tMsg;
                if(QUE_ERR_NONE == OS_GetMsgDir(&g_tHmiTaskCB,&tMsg))
                {
                    if(tMsg.Id == MS_PM_STATE)
                    {
                        OS_TaskStart(TASK_ID_HMI);
                        /*Do not drop this msg*/
                        OS_InsertMsgDir(&g_tHmiTaskCB,tMsg.Id,tMsg.iSid,tMsg.uData.p_cData,TRUE);
                    }
                }
            }
        break;
        case TASK_STATE_STOP:
            if(!OS_TaskIsActive(TASK_ID_HMI))
            {
                 OS_TaskStart(TASK_ID_HMI);
            }
        break;
    }
    
}



static const tTASK_BLOCK lc_tHmiTaskCB =
{
    "HMI",
    _HMI_TASK_TICK_,
    _HMI_CORE_TICK_,
    HMI_Task,
    HMI_Init,
    NULL,
};


bool HMI_TaskCreate(void)
{
    return OS_TaskCreate(TASK_ID_HMI,&g_tHmiTaskCB,&lc_tHmiTaskCB,&l_tHmiMsgQue,la_tHmiMsgBuf,D_HMI_MSG_QUE_DEEP);
}


