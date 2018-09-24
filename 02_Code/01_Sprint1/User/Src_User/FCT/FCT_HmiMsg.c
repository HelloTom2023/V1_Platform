#include "..\config\inc.h"
uint8_t  cHandler;


//FCT Audio Setting Index Map table
uint8_t const g_FCTAudSetupIndexTbl[] =
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
    0xFF,  // 0x12
    OP_AUD_SVOL_MEDIA,
    0xFF,  // 0x14
    OP_AUD_SVOL_PHONE,
    0xFF,
    OP_AUD_SVOL_NAVI,
    
};

void FctSetSrcBackup(uint8_t SrcCur ) 
{
	g_tFCT.tDataBuf.SrcBackup = SrcCur ;
}

void HMI_FCT_Handle(tMSG_BUF* p_tMsg)
{
	uint8_t * P_a;
	#define  D_G_ID		(uint8_t)( p_tMsg->Id & 0x00ff)
	#define  D_S_ID		(uint8_t)( p_tMsg->iSid & 0x00ff)
	P_a = p_tMsg->uData.p_cData;

	g_tFCT.ptFctMsg.Id = (uint8_t)( p_tMsg->Id & 0x00ff) ;
	g_tFCT.ptFctMsg.iSid = D_S_ID;

	g_tFCT.ptFctMsg.uData.a_cData[0] = p_tMsg->uData.a_cData[0];
	g_tFCT.ptFctMsg.uData.a_cData[1] = p_tMsg->uData.a_cData[1];
	g_tFCT.ptFctMsg.uData.a_cData[2] = p_tMsg->uData.a_cData[2];
	g_tFCT.ptFctMsg.uData.a_cData[3] = p_tMsg->uData.a_cData[3];

	g_tFCT.tFctCount.u16TUpdataMsgToPcTimer = 25 ;
	
	switch(D_G_ID)
	{
		case OP_FCT_SOURCE_1 :
		{
			if (SOURCE_SW == D_S_ID)
			{
			if( g_tFCT.tDataBuf.SrcBackup == p_tMsg->uData.a_cData[0] )
				{
				 FCT_SendFullDataResult(OP_FCT_SOURCE_1,SOURCE_SW, p_tMsg->uData.a_cData[0],1,0,0,2 );
				}
			else
				{
				 _SendMsgToSRC(MS_SRC_SET_FRONT_UIID,p_tMsg->uData.a_cData[0],NULL);	 
				 g_tFCT.tDataBuf.SrcBackup = p_tMsg->uData.a_cData[0] ;
				}
			}
		}
		break;
		case OP_FCT_FUNCTION_2 :
		{
			 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_FUNCSWITCH, g_tFCT.ptFctMsg.uData.a_cData[0],0,0,0);
		}
		break;
		case OP_FCT_MEDIA_3 :
		{
			if(SELECTED_SONG == D_S_ID)
			{
#if 0
			uint8_t cTemp;
			if (p_tMsg->uData.a_cData[0] == 0 )
			cTemp =  UICC_SKIPF ;
			else 	if (p_tMsg->uData.a_cData[0] ==1 )
			cTemp =  UICC_SKIPB ;	
			_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_UICC_CMD,cTemp,0,0,0);
#endif
			 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_MEDIACONTROL, APU_FCT_SEL_TRACK,g_tFCT.ptFctMsg.uData.a_cData[0],0,0);

			}
			else if(MEDIA_SEEK == D_S_ID)
			{
			// _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_MEDIACONTROL, APU_FCT_2CH_AND_6CH_SW,p_tMsg->uData.a_cData[0],0,0);
			}
			else if(MEDIA_51_TRACK_SW == D_S_ID)
			{
			 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_MEDIACONTROL, APU_FCT_2CH_AND_6CH_SW,p_tMsg->uData.a_cData[0],0,0);
			}			
		}
		break;
		case OP_FCT_RADIO_4 :
		{			
			if(SELECTED_FM_OR_AM == D_S_ID)
			{
				uint8_t BandNum;
				if(p_tMsg->uData.a_cData[0] == 0)
					BandNum = TUNER_BAND_FM1 ;
				else 	if(p_tMsg->uData.a_cData[0] == 1)
					BandNum = TUNER_BAND_AM1 ;
				if((Tuner_Api_GetBand()) == BandNum)
					FCT_SetStateSameFlag(TRUE);
				
				_SendFullMsgToSRC(MS_SRC_DISTRIBUTE_CMD,(SRC_TYPE_TUNER<<8)|OP_TUNER_SET_BAND_SEL,BandNum,0,0,0);
			}
			else if(SELECTED_PRESET == D_S_ID)
			{
				uint8_t PresetNum;
				PresetNum = p_tMsg->uData.a_cData[0] ;
				if((Tuner_Api_GetPreset()) == PresetNum)
					FCT_SetStateSameFlag(TRUE);

				_SendFullMsgToSRC(MS_SRC_DISTRIBUTE_CMD,(SRC_TYPE_TUNER<<8)|(OP_TUNER_SET_PRESET1 + PresetNum - 1),0,0,0,0);
			}
			else if(RADIO_SEEK == D_S_ID)
			{
				uint8_t Temp;
				Temp = p_tMsg->uData.a_cData[0] ;
				
				if(Temp < 3)
					_SendFullMsgToSRC(MS_SRC_DISTRIBUTE_CMD,(SRC_TYPE_TUNER<<8)|(OP_TUNER_SET_SEEK_INC + Temp ),0,0,0,0);
				else if(Temp == 3)
				{
			            Tuner_StepChangeFreq(DIRECTION_UP);
			            sTuner.CommonCode = TUNER_COMMON_FREQ;
				}
				else if(Temp == 4)
				{
			            Tuner_StepChangeFreq(DIRECTION_DN);
			            sTuner.CommonCode = TUNER_COMMON_FREQ;
				}
			}
			else if(SET_FREQ == D_S_ID)
			{
				uint16_t u16Freq;   
				u16Freq = p_tMsg->uData.a_cData[0] ;
				u16Freq = (uint16_t)((u16Freq <<8) + p_tMsg->uData.a_cData[1]) ;
				if((Tuner_Api_GetFreq()) ==  u16Freq)
					FCT_SetStateSameFlag(TRUE);
				_SendFullMsgToSRC(MS_SRC_DISTRIBUTE_CMD, (SRC_TYPE_TUNER<<8)| OP_TUNER_SET_DIRECT_TUNE , p_tMsg->uData.a_cData[0],p_tMsg->uData.a_cData[1],0,0);
			}
			else if(RDS_SATE == D_S_ID)
			{
				uint8_t cCount;
				for (cCount = 0 ; cCount < 8 ; cCount++)
					g_tFCT.tDataBuf.RdsInfo_10[cCount] = sRds.PS[cCount] ;   //  sTuner.DispPS[Temp]
			
				_SendMsgToFCT(OP_FCT_RADIO_4, RDS_SATE,g_tFCT.tDataBuf.RdsInfo_10);
				
			}
			else if(RETURN_CUR_FREQ == D_S_ID)
			{
				uint16_t u16Freq ;
				u16Freq = Tuner_Api_GetFreq();		
			
				_SendFullMsgToFCT(OP_FCT_RADIO_4, RETURN_CUR_FREQ, (uint8_t)(u16Freq >>8),  (uint8_t)(u16Freq & 0x00ff),0,0);
			}	
			else if(STEREO_MONO_SW == D_S_ID)
			{
				_SendFullMsgToFCT(OP_FCT_RADIO_4, STEREO_MONO_SW,  sTuner.bStereoMono,0,0,0);
			}	
			else if(DX_LOC_SW == D_S_ID)
			{
			
			}		
		}
		break;
		case OP_FCT_BT_5 :
		{
			
			if(BT_SW == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_BLUETOOTH, APU_FCT_BT_ON_OFF, g_tFCT.ptFctMsg.uData.a_cData[0],0,0);
			}
			else if(RET_MAC_ADDRESS == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_BLUETOOTH, APU_FCT_BT_REQ_MAC, 0,0,0);
			}
			else if(RET_LINK_STATE == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_BLUETOOTH, APU_FCT_BT_REQ_BT_STATE, 0,0,0);
			}
			else if(RET_WRITE_BT_NAME == D_S_ID)
			{
				 _SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_BLUETOOTH, p_tMsg->uData.p_cData);
				 
			}
			else if(RET_VER_ADD_NAME == D_S_ID)
			{
				if(0 == g_tFCT.ptFctMsg.uData.a_cData[0])
					 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_BLUETOOTH, APU_FCT_BT_REQ_BT_VERSION, 0,0,0);
				else if(1 == g_tFCT.ptFctMsg.uData.a_cData[0])
					 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_BLUETOOTH, APU_FCT_BT_REQ_BT_NAME, 0,0,0);
			}
			else if(PLAY_MUICE_BT == D_S_ID)
			{
			}
			else if(DIAL_UP == D_S_ID)
			{
			}
			else if(RF_QUALITY == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_BLUETOOTH, APU_FCT_BT_REQ_RF_QUALITY, 0,0,0);
			}			
		}
		break;
		case OP_FCT_GPS_6 :
		{
			if(LONGITUDE_LATITUDE == D_S_ID)
			{
				 //_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_GPS, APU_FCT_BT_REQ_RF_QUALITY, 0,0,0);
			}
			else if (SIMULATE_NAV == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_GPS, APU_FCT_GPS_SIMULATA_ROUTE, 0,0,0);
			}
			else if (RET_INFO == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_GPS, APU_FCT_GPS_REQ_RET_QUALITY, 0,0,0);
			}
			else if (RET_INERTIA_NAV_INFO == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_GPS, APU_FCT_GPS_REQ_RET_GYRO_INFO, 0,0,0);
			}
			else if (CHECK_TMC_INFO == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_GPS, APU_FCT_GPS_REQ_RET_TMC_INFO, 0,0,0);
			}
		}
		break;
		case OP_FCT_KEY_7 :
		{
			
		}
		break;
		case OP_FCT_TMPS_8 :
		{
			
		}
		break;
		case OP_FCT_VOLUME_SET_9 :
		{
			if((Audio_Api_GetVolume()) ==  p_tMsg->uData.a_cData[0] )
			{
				FCT_SetStateSameFlag(TRUE);
			}
 			 _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_SEL,p_tMsg->uData.a_cData[0],0,0,0);
		}
		break;
		case OP_FCT_FAN_TEST_10 :
		{
			if (p_tMsg->uData.a_cData[0] == 0)
			{
				 PM_UnitPowerSet(PM_UNIT_FAN,OFF);
				 FCT_SetStateSameFlag(TRUE);
			}
			else if (p_tMsg->uData.a_cData[0] == 1)
			{
				 PM_UnitPowerSet(PM_UNIT_FAN,ON);
				 FCT_SetStateSameFlag(TRUE);
			}
		}
		break;
		case OP_FCT_AUDIO_SET_11 :
		{
			uint8_t  aArrayAudio[18];
			uint8_t  cArraySuffix;
			for(cArraySuffix = 0 ; cArraySuffix <18 ; cArraySuffix ++)
			{
			 	_SendFullMsgToAudio(MS_AUDIO_CMD , g_FCTAudSetupIndexTbl[cArraySuffix] , * (P_a + cArraySuffix),0,0,0);
			}
		}
		break;
		case OP_FCT_VIDEO_SET_12 :
		{
			 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_VIDEOSET, 
			 	p_tMsg->uData.a_cData[0], p_tMsg->uData.a_cData[1],p_tMsg->uData.a_cData[2],0);
		}
		break;
		case OP_FCT_WIFI_LINK_13 :
		{
			if(WIFI_SW == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_WIFI, APU_FCT_WIFI_ON_OFF, p_tMsg->uData.a_cData[0],0,0);
			}
			else if (WIFI_LINK_AP == D_S_ID)
			{
				 _SendMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_WIFI,p_tMsg->uData.p_cData);
			}
			else if (WIFI_SIGNAL_INTENSITY == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_WIFI, APU_FCT_WIFI_REQ_ISSI, 0,0,0);
			}
		}
		break;
		case OP_FCT_BUS_14 :
		{
			
		}
		break;
		case OP_FCT_CUR_STATE_15 :
		{
			
		}
		break;
		case OP_FCT_E_DOG_16 :
		{
			
		}
		break;
		case OP_FCT_SEQ_NUM_17 :
		{
			
		}
		break;
		case OP_FCT_SOFT_VER_18 :
		{
			if(1 == D_S_ID)
			{
				 _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_FCT_REQVERSION, p_tMsg->uData.a_cData[0], 0,0,0);
			}

		}
		break;
		case OP_FCT_APU_TX_RESULT :
		{
			if(SOFT_MCU_VER == D_S_ID)
			{
			//_SendMsgToFCT(OP_FCT_SOFT_VER_18, SOFT_MCU_VER,ga_cSoftwareVer);
			}

		}
		break;


		
		default:
			
		break;
	}
}

/***********************************************************
*适应范围- PC要求MCU转到某个状态，但是MCU本身就在这个状态， 
* 所有MCU不需要做任何处理，直接返回当前状态给PC
***********************************************************/


uint8_t  FCT_DataResultToPc(tMSG_BUF* p_tMsg)
{
	uint8_t * P_a;
	#define  D_G_ID		(uint8_t)( p_tMsg->Id & 0x00ff)
	#define  D_S_ID		(uint8_t)( p_tMsg->iSid & 0x00ff)
	
	 if((FCT_GetStateSameFlag()) == FALSE )
	 	return 1;

	if (((D_G_ID ) <= OP_FCT_TO_HMI_START) 
		|| ((D_G_ID ) >= OP_FCT_TO_HMI_END))
		return 1;
	P_a = p_tMsg->uData.p_cData;

	switch(D_G_ID)
	{
		case OP_FCT_SOURCE_1 :
		{
			if (SOURCE_SW == D_S_ID)
			{
			}
		}
		break;
		case OP_FCT_FUNCTION_2 :
		{
			
		}
		break;
		case OP_FCT_MEDIA_3 :
		{
			if(SELECTED_SONG == D_S_ID)
			{	
			
			}
			else if(MEDIA_SEEK == D_S_ID)
			{
			}
			else if(MEDIA_51_TRACK_SW == D_S_ID)
			{
			}			
		}
		break;
		case OP_FCT_RADIO_4 :
		{			
			if(SELECTED_FM_OR_AM == D_S_ID)
			{
			}
			else if(SELECTED_PRESET == D_S_ID)
			{
			}
			else if(RADIO_SEEK == D_S_ID)
			{
			}
			else if(SET_FREQ == D_S_ID)
			{
			}
			else if(RDS_SATE == D_S_ID)
			{
				P_a = g_tFCT.tDataBuf.RdsInfo_10 ;
			}
			else if(RETURN_CUR_FREQ == D_S_ID)
			{

			}		
		}
		break;
		case OP_FCT_BT_5 :
		{
			if(BT_SW == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(RET_MAC_ADDRESS == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(RET_WRITE_BT_NAME == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(RET_LINK_STATE == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(RET_VER_ADD_NAME == D_S_ID)
			{
				//P_a = g_tFCT.tDataBuf.BTVerMacAdd_16 ;
			}
			else if(PLAY_MUICE_BT == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(DIAL_UP == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(RF_QUALITY == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 100 ;
			}
		
		}
		break;
		case OP_FCT_GPS_6 :
		{			
			if(LONGITUDE_LATITUDE == D_S_ID)
			{		
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(SIMULATE_NAV == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(RET_INFO == D_S_ID)
			{
				P_a = g_tFCT.tDataBuf.GPSInfo_22 ;
			}
			else if(RET_INERTIA_NAV_INFO == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 11 ;
				p_tMsg->uData.a_cData[1] = 12 ;
			}
			else if(CHECK_TMC_INFO == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
		}
		break;
		case OP_FCT_KEY_7 :
		{
				p_tMsg->uData.a_cData[0] = 11 ;
		}
		break;
		case OP_FCT_TMPS_8 :
		{
				P_a = g_tFCT.tDataBuf.TmpsInfo_26 ;
		}
		break;
		case OP_FCT_VOLUME_SET_9 :
		{
		}
		break;
		case OP_FCT_FAN_TEST_10 :
		{
		}
		break;
		case OP_FCT_AUDIO_SET_11 :
		{
				P_a = g_tFCT.tDataBuf.AudioSet_30 ;
		}
		break;
		case OP_FCT_VIDEO_SET_12 :
		{
		}
		break;
		case OP_FCT_WIFI_LINK_13 :
		{
			if(WIFI_LINK_AP == D_S_ID)
			{		
				p_tMsg->uData.a_cData[0] = 1 ;
			}
			else if(WIFI_SIGNAL_INTENSITY == D_S_ID)
			{
				p_tMsg->uData.a_cData[0] = 1 ;
			}
		}
		break;
		case OP_FCT_BUS_14 :
		{
			if(BUS_ILL == D_S_ID)
			{		
				p_tMsg->uData.a_cData[0] = 1 ;
			}	
		}
		break;
		case OP_FCT_CUR_STATE_15 :
		{
				p_tMsg->uData.a_cData[0] = 1 ;
				p_tMsg->uData.a_cData[1] = 2 ;
				p_tMsg->uData.a_cData[2] = 3 ;
		}
		break;
		case OP_FCT_E_DOG_16 :
		{
			
		}
		break;
		case OP_FCT_SEQ_NUM_17 :
		{
				P_a = g_tFCT.tDataBuf.SeqNum_39 ;
		}
		break;
		case OP_FCT_SOFT_VER_18 :
		{
		}
		break;
		
		default:
			
		break;
	}
	
	FCT_HmiIdToPcId(D_G_ID, D_S_ID, p_tMsg);
	g_tFCT.ptFctMsg.Id = OP_FCT_TO_HMI_START;
	FCT_SetStateSameFlag(FALSE);
}


void FctMediaMsgHandler(uint8_t *pFctMedia)
{
	if((g_tFCT.ptFctMsg.Id == OP_FCT_MEDIA_3)&&(g_tFCT.ptFctMsg.iSid == SELECTED_SONG))
	{
		_SendFullMsgToFCT(OP_FCT_MEDIA_3, SELECTED_SONG, pFctMedia[3], pFctMedia[2],0,0);
	}
	else if((g_tFCT.ptFctMsg.Id == OP_FCT_MEDIA_3)&&(g_tFCT.ptFctMsg.iSid == MEDIA_SEEK))
	{
		_SendFullMsgToFCT(OP_FCT_MEDIA_3, MEDIA_SEEK, pFctMedia[1], 0,0,0);
	}
}

void FctBasicTestResult(uint8_t* p_cRxBuff,uint8_t cLen)
{
	uint8_t cResultType;
	cResultType = p_cRxBuff[0];
	switch(cResultType)
	{
		case FCT_TEST_SOURCE_SWITCH :
		{
			uint8_t Flag;
			Flag = FALSE;
			if(g_tFCT.tDataBuf.SrcBackup == p_cRxBuff[2])
				Flag = TRUE;
			_SendFullMsgToFCT(OP_FCT_SOURCE_1, SOURCE_SW, p_cRxBuff[2], Flag,0,0);
		}
		break;
		case FCT_TEST_SWC_STUDY_FUNC :
		{
			_SendFullMsgToFCT(OP_FCT_FUNCTION_2, FUNCTION_SW,APU_FCT_FUNC_SWC, p_cRxBuff[2], 0,0);
		}
		break;
		case FCT_TEST_REVERSE :
		{
			_SendFullMsgToFCT(OP_FCT_FUNCTION_2, FUNCTION_SW,APU_FCT_FUNC_REVERSE, p_cRxBuff[2], 0,0);
		}
		break;
		case FCT_TEST_SETUP_MENU :
		{
			_SendFullMsgToFCT(OP_FCT_FUNCTION_2, FUNCTION_SW,APU_FCT_FUNC_SET, p_cRxBuff[2], 0,0);
		}
		break;
		case FCT_TEST_VOICE_ASSIST :
		{
			_SendFullMsgToFCT(OP_FCT_FUNCTION_2, FUNCTION_SW,APU_FCT_FUNC_VR, p_cRxBuff[2], 0,0);
		}
		break;
		case FCT_TEST_BT_FUNC :
		{
			_SendFullMsgToFCT(OP_FCT_BT_5, BT_SW,p_cRxBuff[2], 0, 0,0);
		}
		break;
		case FCT_TEST_WIFI_FUNC :
		{
			_SendFullMsgToFCT(OP_FCT_WIFI_LINK_13, WIFI_SW,p_cRxBuff[2], 0, 0,0);
		}
		break;
		case FCT_TEST_ONE_KEY_NAVI :
		{
			_SendFullMsgToFCT(OP_FCT_FUNCTION_2, FUNCTION_SW,APU_FCT_FUNC_ONE_KEY, p_cRxBuff[2], 0,0);
		}
		break;
		case FCT_TEST_MEDIA_SEL_TRACK :
		{
			_SendFullMsgToFCT(OP_FCT_MEDIA_3, MEDIA_CONTROL,SELECTED_SONG ,p_cRxBuff[2], 0,0);
		}
		break;
		case FCT_TEST_2_6_CH_SW :
		{
			_SendFullMsgToFCT(OP_FCT_MEDIA_3, MEDIA_CONTROL, MEDIA_51_TRACK_SW,p_cRxBuff[2], 0,0);
		}
		break;
		case FCT_TEST_DVD_DISP_SW :
		{
			//_SendFullMsgToFCT(OP_FCT_MEDIA_3, MEDIA_51_TRACK_SW, p_cRxBuff[2], 0,0,0);
		}
		break;
		case FCT_TEST_BRIGHTNESS_SET :
		{
			g_tFCT.tDataBuf.VideoSet[0] = p_cRxBuff[2] ;
			_SendFullMsgToFCT(OP_FCT_VIDEO_SET_12, VIDEO_SET, g_tFCT.tDataBuf.VideoSet[0], g_tFCT.tDataBuf.VideoSet[1],g_tFCT.tDataBuf.VideoSet[2],0);
		}
		break;
		case FCT_TEST_CONTRAST_SET :
		{
			g_tFCT.tDataBuf.VideoSet[1] = p_cRxBuff[2] ;
			_SendFullMsgToFCT(OP_FCT_VIDEO_SET_12, VIDEO_SET, g_tFCT.tDataBuf.VideoSet[0], g_tFCT.tDataBuf.VideoSet[1],g_tFCT.tDataBuf.VideoSet[2],0);
		}
		break;
		case FCT_TEST_CHROMA_SET :
		{
			g_tFCT.tDataBuf.VideoSet[2] = p_cRxBuff[2] ;
			_SendFullMsgToFCT(OP_FCT_VIDEO_SET_12, VIDEO_SET, g_tFCT.tDataBuf.VideoSet[0], g_tFCT.tDataBuf.VideoSet[1],g_tFCT.tDataBuf.VideoSet[2],0);
		}
		break;
	}
}

void FctBtTestResult(uint8_t* p_cRxdata,uint8_t cLen)
{
	uint8_t cResultType;
	cResultType = p_cRxdata[0];
	switch(cResultType)
	{
	case FCT_BT_TEST_RESULT_MAC :
	{
        	g_tFCT.tDataBuf.BTMacAddL =  cLen - 1 ;
		_SendMsgToFCT(OP_FCT_BT_5, RET_MAC_ADDRESS, &p_cRxdata[1]);
	}
	break;
	case FCT_BT_TEST_RESULT_NAME :
	{
        	g_tFCT.tDataBuf.BTDevNameL =  cLen - 1 ;
		_SendMsgToFCT(OP_FCT_BT_5, RET_VER_ADD_NAME, &p_cRxdata[1]);
	}
	break;
	case FCT_BT_TEST_RESULT_VERSION :
	{
        	g_tFCT.tDataBuf.BTVerL =  cLen - 1 ;
		_SendMsgToFCT(OP_FCT_BT_5, RET_VER_ADD_NAME, &p_cRxdata[1]);
	}
	break;
	case FCT_BT_TEST_RESULT_RF_QUALITY :
	{
		_SendFullMsgToFCT(OP_FCT_BT_5, RF_QUALITY,  p_cRxdata[1],0,0,0);
	}
	break;
	}
}

void FctGpsTestResult(uint8_t* p_cRxdata,uint8_t cLen)
{
	uint8_t cResultType;
	cResultType = p_cRxdata[0];
	switch(cResultType)
	{
	case FCT_GPS_TEST_RESULT_QUALITY :
	{
        	g_tFCT.tDataBuf.GPSInfoL =  cLen - 1 ;
		_SendMsgToFCT(OP_FCT_GPS_6, RET_INFO, &p_cRxdata[1]);
	}
	break;
	case FCT_GPS_TEST_RESULT_GYRO :
	{
		_SendMsgToFCT(OP_FCT_GPS_6, RET_INERTIA_NAV_INFO, &p_cRxdata[1]);
	}
	break;
	case FCT_GPS_TEST_RESULT_TMC :
	{
		_SendMsgToFCT(OP_FCT_GPS_6, CHECK_TMC_INFO, &p_cRxdata[1]);
	}
	break;
	}
}
void FctVersionTestResult(uint8_t* p_cRxdata,uint8_t cLen)
{
	uint8_t cResultType;
	cResultType = p_cRxdata[0];
	switch(cResultType)
	{
	case FCT_VERSION_OS :
	case FCT_VERSION_BOOT :
	case FCT_VERSION_APP :
	case FCT_VERSION_MPEG :
	case FCT_VERSION_MAP :
	{
        	g_tFCT.tDataBuf.SoftVerL =  cLen ;
		_SendMsgToFCT(OP_FCT_SOFT_VER_18, SOFT_OS_VER, p_cRxdata);
	}
	break;
	}

	
}

uint8_t  aFctRxBuff[50] ;
void FctApuTxMcuMsg(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
	uint8_t  count ;
	if(cLen < 50)
	{
		for(count = 0 ; count < cLen ; count++)
			aFctRxBuff[count] = p_cRxdata[count];
	}

	switch(cSid)
	{
		case SID_MCU_RX_FCT_RESULT_BASIC :
		{
			FctBasicTestResult(aFctRxBuff,  cLen );
		}
		break;
		case SID_MCU_RX_FCT_RESULT_BLUETOOTH :
		{
			FctBtTestResult(aFctRxBuff,  cLen );
		}
		break;
		case SID_MCU_RX_FCT_RESULT_GPS :
		{
			FctGpsTestResult(aFctRxBuff,  cLen );
		}
		break;
		case SID_MCU_RX_FCT_RESULT_TPMS :
		{

		}
		break;
		case SID_MCU_RX_FCT_RESULT_WIFI :
		{
			if(FCT_WIFI_TEST_RESULT_QUALITY == p_cRxdata[0])
				_SendMsgToFCT(OP_FCT_WIFI_LINK_13, WIFI_SIGNAL_INTENSITY, &p_cRxdata[1]);
		}
		break;
		case SID_MCU_RX_FCT_RESULT_VERSION :
		{
			FctVersionTestResult(aFctRxBuff,  cLen );
		}
		break;
	}
}

