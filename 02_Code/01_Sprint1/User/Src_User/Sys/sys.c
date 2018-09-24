#define _SYS_C_
#include "..\config\inc.h"

#define D_WAITSLEEP_TIME  _set_timing_sec_base_pwr_task_tick(6)
#define D_WAITOFF_TIME    _set_timing_sec_base_rtc(16)
#define D_ECONOMY_TIME    _set_timing_sec_base_pwr_task_tick(60*60)
uint8_t Reverse_Flag=0;


const tEEP_DATA_RANG lc_tSysDefData[]={
	/**************GENERAL Setting***************/
    {0,             0,      0xff},
    {0, REGION_EUROPE,REGION_MAX},
    {0,(BEEP_DEFAULT_TYPE<<2),0xff},
    {0,0x28,0xff},
    {0,10,0xff},
    {0,0,0x3f},
    {0,0,7},
	/****************SCREEN Setting*****************/
    {0,10,10},
    {0,60,100},
    {0,15,100},
    {0,60,100},
    {0,0,2},
    {0,50,100},
	/*************AUDIO Setting*********************/    
    {0,  GEQ_MODE_STANDARD,      GEQ_MODE_MAX},//EQ TYPE    Float
    {0,  AUDIO_BASS_MAX/2,       AUDIO_BASS_MAX},//sBassGain
    {0,  AUDIO_MID_MAX/2,        AUDIO_MID_MAX},//sMidGain
    {0,  AUDIO_TREBLE_MAX/2,     AUDIO_TREBLE_MAX},//sMidGain
    {0,  AUDIO_FADER_MAX/2,      AUDIO_FADER_MAX},//Fader
    {0,  AUDIO_BALANCE_MAX/2,    AUDIO_BALANCE_MAX},//Balance
    {0,  AUDIO_VOL_DEFULT_SYS,   AUDIO_VOL_MAX},//SysVol
    {0,  AUDIO_VOL_DEFULT_NAVI,  AUDIO_VOL_MAX},//NaviVol
    {0,  15,    30},//BtVol
    {0,  AUDIO_VOL_DEFULT_APP,   AUDIO_VOL_MAX},//AppVol
};


const tEEP_DATA_RANG lc_tSysSettingDefData[]={
    {0,(uint8_t)(D_WAITSLEEP_TIME),0xff},
    {0,(uint8_t)(D_WAITSLEEP_TIME>>8),0xff},
    {0,(uint8_t)(D_WAITSLEEP_TIME>>16),0xff},
    {0,(uint8_t)(D_WAITSLEEP_TIME>>24),0xff},
    
    {0,(uint8_t)(D_WAITOFF_TIME),0xff},
    {0,(uint8_t)(D_WAITOFF_TIME>>8),0xff},
    {0,(uint8_t)(D_WAITOFF_TIME>>16),0xff},
    {0,(uint8_t)(D_WAITOFF_TIME>>24),0xff},
    
    {0,(uint8_t)(D_ECONOMY_TIME),0xff},
    {0,(uint8_t)(D_ECONOMY_TIME>>8),0xff},
    {0,(uint8_t)(D_ECONOMY_TIME>>16),0xff},
    {0,(uint8_t)(D_ECONOMY_TIME>>24),0xff},

    {0,1,1},
    {0,30,50},
    
    /*Add your data default value*/
    {5,5,100},{5,10,100},{5,15,100},{5,20,100},{5,25,100},
    {5,30,100},{5,35,100},{5,40,100},{5,45,100},{5,50,100},{5,55,100},
    {5,60,100},{5,65,100},{5,70,100},{5,75,100},{5,80,100},
    {5,85,100},{5,90,100},{5,95,100},{5,100,100},{5,100,100},
    {5,5,20},

    {5,5,100},{5,10,100},{5,15,100},{5,20,100},{5,25,100},
    {5,30,100},{5,35,100},{5,40,100},{5,45,100},{5,50,100},{5,55,100},
    {5,60,100},{5,65,100},{5,70,100},{5,75,100},{5,80,100},
    {5,85,100},{5,90,100},{5,95,100},{5,100,100},{5,100,100},
    {30,50,50},

    {5,5,100},{5,10,100},{5,15,100},{5,20,100},{5,25,100},
    {5,30,100},{5,35,100},{5,40,100},{5,45,100},{5,50,100},{5,55,100},
    {5,60,100},{5,65,100},{5,70,100},{5,75,100},{5,80,100},
    {5,85,100},{5,90,100},{5,95,100},{5,100,100},{5,100,100},
    {5,5,20},
    {0,1,1}, //Tuner Antenna Power
    {0,5|0x08|0x10,0xFF},//APU_FUNC_CONFIG
};

tEEP_DATA_BLOCK l_tEepSysRomData;
tEEP_DATA_BLOCK l_tEepSysSettingRomData;

const tEEP_DATA lc_tEepSysRom = {
    D_EEP_SYSDATA_ID,
    (uint8_t*)&g_tSysRomData,lc_tSysDefData,
    D_EEP_SYSDATA_ADDR,D_EEP_SYSDATA_LEN,0
};

const tEEP_DATA lc_tEepSysSettingRom = {
    D_EEP_SYSSETDATA_ID,
    (uint8_t*)&g_tSysSettingRomData,lc_tSysSettingDefData,
    D_EEP_SYSSETDATA_ADDR,D_EEP_SYSSETDATA_LEN,1
};
/****************************************************************************
 * @function	SYS_loadDefaultParam
 * @brief  	在不对原HQ10平台EEPROM部分做改动的情况下，将对应
 *			的参数加载到内存中，并进行校验部分
 * @param  	不对原数据结构做改动!!!!!!!!!!!			
 * @retval 	null
****************************************************************************/
void SYS_loadDefaultParam(tEEP_DATA *pBlock)
{
	uint8_t i = 0;
	uint8_t len = pBlock->iLen-2;
	for(i = 0;i<len;i++)
	{
		pBlock->p_cBuf[i] = pBlock->p_tDefData[i].cDef;
	}
	OS_CreateRamChkBlock(pBlock->p_cBuf, len , &pBlock->p_cBuf[len]);	
}

void SYS_BlockEdit(tEEP_DATA *pBlock,uint16_t iOffSet,uint8_t cValue)
{
        uint8_t* p_cBuf = pBlock->p_cBuf;
        uint16_t iLen =pBlock->iLen - sizeof(uint16_t);
        uint16_t* p_tChkSum = (uint16_t*)&(p_cBuf[iLen]);

        if(cValue != p_cBuf[iOffSet])
        {
            p_cBuf[iOffSet] = cValue;
            OS_CreateRamChkBlock((void*)p_cBuf,iLen,p_tChkSum);
        }
}


void SYS_Init(void)
{
	g_BKAutoLevel  = 0;
        g_BKHandLevel = 7;
	EEP_CreateEepDataBlock(&l_tEepSysRomData,&lc_tEepSysRom);
//	EEP_CreateEepDataBlock(&l_tEepSysSettingRomData,&lc_tEepSysSettingRom);
	SYS_loadDefaultParam((tEEP_DATA *)&lc_tEepSysSettingRom);

	g_tMcuDevState.uIOState.byte = 0;
	g_tMcuDevState.uConnetState.byte = 0;
	g_tMcuDevState.uDetect.byte = 0;
	g_tMcuDevState.uIOState.bits.FirstPowerOnFlag = 1;
	g_tMcuDevState.uDetect.bits.VideoDisable = 0;
	SysWorkStatusGrp.SysBtCallFlag = 0;
	SysWorkStatusGrp.SysILLlevel = LEVEL_VAILD - 1;
	SysWorkStatusGrp.SysCommSpySwitch = 0;
	SysWorkStatusGrp.SysApuStandyMode = 0;
	SysWorkStatusGrp.SysAutoTestEnter = 0;
}



/*******************************************************************************
* SYS seting block
*******************************************************************************/
void SYS_ExecGenSetting(uint8_t Idx,uint8_t Param)
{
    uint8_t bUpload = 1;
    uint8_t bSaveFlag = 1;
    switch(Idx)
    {
        case GEN_ID_RADIO_AREA:
		#ifdef R103_H15T_OVERSEAS //snake20170215 只有海外版才能设置收音区域
			if(g_tSysRomData.uGenBlock.tBlock.cRadioField != Param)
			{
				g_tSysRomData.uGenBlock.tBlock.cRadioField = Param;
				Tuner_SetRadioArea(Param);
			}
			_SendMsgToHMI(MS_SRC_UPLOAD_INFO,/*(SRC_TYPE_TUNER<<8)|*/OP_TUNER_UPD_AREA,&sTunerKeep);
		#endif
        break;

        case GEN_ID_LOAD_FACTORY:
            _SendMsgToHMI(MS_SYS_LOAD_FACTORY_INFO,0,NULL);
            bSaveFlag = 0;
        break;

        case GEN_ID_BEEP_SWITCH:
	      if(g_tSysRomData.uGenBlock.tBlock.tFlag2.bBeep_Flag != Param)
	       {
			g_tSysRomData.uGenBlock.tBlock.tFlag2.bBeep_Flag = Param;
			bSaveFlag = 1;
	       }
            _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_SEL,Param,0,0,0);

        break;

        case GEN_ID_AUX_IN_LEVEL_SET:
            g_tSysRomData.uGenBlock.tBlock.tFlag3.bAuxIn_SW_Set = (Param&0x03);
        break;
        case GEN_ID_AUX_IN_SOURCE_TYPE:
            g_tSysRomData.uGenBlock.tBlock.tFlag3.bAuxIn_Source_Set = (Param&1);
        break;
        case GEN_ID_ACTIVE_SOUND_SET:
            g_tSysRomData.uGenBlock.tBlock.tFlag2.bActiveSound_Set = (Param&1);
        break;
       
        case GEN_ID_AUX_VIDEO_FORMAT:
            g_tSysRomData.uGenBlock.tBlock.tFlag1.bAuxInFormat_Flag = (Param&3);
        break;
        case GEN_ID_OPEN_LCD:
            g_tSysRomData.uGenBlock.tBlock.tFlag1.bAuto_Open_EnFlag = (Param&1);
        break;
        case GEN_ID_CLOCK_MODE:
            g_tSysRomData.uGenBlock.tBlock.tFlag1.bRTC24Hour_Flag = (Param&1);
        break;
        case GEN_ID_CLOCK_HOUR:
        //    g_tSysRomData.uGenBlock.tBlock.cHour = Param;
            bSaveFlag = 0;
	     bUpload = 0;
        break;
        case GEN_ID_CLOCK_MINUTE:
       //     g_tSysRomData.uGenBlock.tBlock.cMin = Param;
            bSaveFlag = 0;
	     bUpload = 0;
        break;
        case GEN_ID_CAMERA_MIRROR_MODE:
            g_tSysRomData.uGenBlock.tBlock.tFlag1.bCamera_Mirror_Flag = (Param&1);
        break;
        case GEN_ID_RDS_CT_SET:
            g_tSysRomData.uGenBlock.tBlock.tFlag2.bRDS_CT_Set = (Param&1);
        break;
        case GEN_ID_CAN_BRIGHT_ON_OFF:
            g_tSysRomData.uGenBlock.tBlock.tFlag2.bCan_Bright_Set = (Param&1);
        break;
        case GEN_ID_CAN_BACK_LIGHT_LEVEL:
            g_tSysRomData.uGenBlock.tBlock.tFlag2.bCan_Bright_Set = (Param&1);
        break;
        
        case GEN_ID_EXT_TEL_MUTE_SWITCH: 
            g_tSysRomData.uGenBlock.tBlock.tFlag2.bExt_Tel_OnOff_Set = (Param&3);
        break;
        case GEN_ID_EXT_TEL_AUDIO_CH_SET:
            g_tSysRomData.uGenBlock.tBlock.tFlag2.bExt_Tel_Ch_Set = (Param&1);
        break;
        
        case GEN_ID_REVERSE_CAMERA_ON_OFF:
             g_tSysRomData.uGenBlock.tBlock.tFlag3.bCamera_On_Off = (Param&1);
        break;
        case GEN_ID_AUTO_DIMMER://调光器,调节亮度
            g_tSysRomData.uGenBlock.tBlock.tFlag3.bAuto_Dimmer_Set = (Param&1);
		_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);//upgrade backlight level after changing mode 
        break;
        
        case GEN_ID_KEY_COLOR_SET:
            g_tSysRomData.uGenBlock.tBlock.tFlag4.bKey_Color = (Param&3);
        break;
        case GEN_ID_NAVI_VOICE_GUIDANCE_MODE:
            g_tSysRomData.uGenBlock.tBlock.tFlag3.bNavi_Guidance_Mode = (Param&3);
            _SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_NAVI_AUDIO,FALSE); 
            _SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MIX_REQ,SRC_TYPE_NAVI_AUDIO,0,0,0);
        break;

        case GEN_ID_ACC_LED_SET:
             g_tSysRomData.uGenBlock.tBlock.tFlag3.bACC_LED_Set = (Param&1);
        break;
        case GEN_ID_PARKING_DET_MODE:
        {
          //   uint8_t temp = IO_Get(IO_IDX_PARKING_DET,PIN_INPUT,TRUE);
             g_tSysRomData.uGenBlock.tBlock.tFlag4.bParking_Det_Mode = (Param&3);
         //    _SendMsgToHMI(MS_SYS_IO_INFO,IO_IDX_PARKING_DET,temp);
        }
        break;
        case GEN_ID_ORIGINAL_ANTENNA_SUPPLY:
             g_tSysRomData.uGenBlock.tBlock.tFlag4.bAntennaSupply = (Param&1);
        break;

        case GEN_ID_ANTI_THEFT:
		g_tSysRomData.uGenBlock.tBlock.tFlag4.bSecureCheck = 0; //(Param&1);
            break;

        case GEN_ID_ANT_GAIN:
            g_tSysRomData.uGenBlock.tBlock.AntGain = Param;
            break;
	case GEN_ID_FAN_TEST:
	     _SendMsgToHMI(MS_SYS_IO_INFO,IO_IDX_TEMP_DET, Param);
	     bUpload = 0;
	     bSaveFlag = 0; 
	     break;
	case GEN_ID_TUNER_TEST:
	     Mult_Struct.TestTuner = Param;
	     bUpload = 0;
	     bSaveFlag = 0; 
	     break;
	case GEN_ID_AUTO_AGING:
	case GEN_ID_KEYPAD_TEST:
	     bUpload = 0;
	     bSaveFlag = 0; 
	     break;
	case GEN_ID_PRAYER_CTL:
		g_tSysRomData.uGenBlock.tBlock.tFlag4.bBootPrayer = (Param&1);
		break;
        case GEN_ID_SET_SLEEP_TIMING:
            g_tSysRomData.uGenBlock.tBlock.tFlag5.SleepTimeSet = (Param&3);
            break;
        case SCR_ID_BL_LVE:
        case SCR_ID_TILT:
        case SCR_ID_NIGHT_BL_LEV:
        {	
	   		g_tSysRomData.tScrBlock.cBaseBR= Param;
			if(g_tSysRomData.tScrBlock.cBaseBR > D_TFT_BL_LEV_NUM)//snake20160922 范围判断  
				g_tSysRomData.tScrBlock.cBaseBR = D_TFT_BL_LEV_NUM;
            _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SCREENSETTING,&(g_tSysRomData.tScrBlock));
            if(Idx == SCR_ID_BL_LVE)
            {
                _SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,Param);
		     	bSaveFlag = 1;//snake20160927 存储和上传
		     	bUpload = 1;
	     	}
        }
        break;
        default:
            bSaveFlag = 0;
	     	bUpload = 0;
		break;
       
    }
	if(bSaveFlag)
	{
		//g_tSysRomData.tScrBlock.cBaseBR= g_BKHandLevel;//snake20160927 delete 没有使用调光器...
		EEP_CreateBlockChkSum(&l_tEepSysRomData);
		EEP_WriteStart(&l_tEepSysRomData,1);
	}
	if(bUpload)
	{
    		_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_GENERALSETTING,&(g_tSysRomData.uGenBlock));
	}
}


