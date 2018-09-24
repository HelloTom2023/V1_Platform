#ifndef _SYS_H_
#define _SYS_H_

#ifdef _SYS_C_
#define _SYS_
#else
#define _SYS_ extern
#endif

typedef struct{
    uint8_t cAPU;            /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cTuner;          /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cAudioSwicher;   /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cATV;            /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cAMP;            /*0:NO Chip 0x01~0xXX:define*/
    struct{
        bit_t cLF :2;      /*0:NO Speak 1:Error 2:Normal*/
        bit_t cRF :2;      /*0:NO Speak 1:Error 2:Normal*/
        bit_t cLR :2;      /*0:NO Speak 1:Error 2:Normal*/
        bit_t cRR :2;      /*0:NO Speak 1:Error 2:Normal*/
    }tSpeak;
    uint8_t cEeprom;         /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cTMC;            /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cCanAdp;         /*0:NO device 0x01~0xXX:define*/
    uint8_t cHeadPlayer;     /*0:NO device 0x01~0xXX:define*/
    uint8_t cAnt;            /*0:NO Speak 1:Error 2:Normal*/

    uint8_t cBt;             /*0:NO device 0x01~0xXX:define*/
    uint8_t cVidSwither;     /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cDTV;            /*0:NO device 0x01~0xXX:define*/
    uint8_t ciPod2Dot0;      /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cMHL;            /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cTBox;           /*0:NO device 0x01~0xXX:define*/
    uint8_t cWifi;           /*0:NO Chip/Chip OFF 0x01~0xXX:define,Chip ON*/
    uint8_t cTrig;           /*0:NO Chip 0x01~0xXX:define*/
    uint8_t cMpeg;           /*0:NO device 0x01~0xXX:define*/
    
    uint8_t cBattery;        /*0xXX  Voltage value*/
    
}tSYS_DEV_BLOCK;


typedef struct{
    eSYS_DEV_IDX eIdx;       /*Dev type*/
    char* p_cInfo;           /*Dev info,as:Version,MAC...*/
}tSYS_DEV_INFO;



/*Device state from apu*/

#pragma pack(1)
typedef struct 
{
    union
    {
        uint8_t byte;
        struct
        {
            bit_t DTV_Connected        :1;        // bit_t 0.
            bit_t Aux_In       		     :1;        // bit_t 1.
            bit_t Disc_Inserted           :2;        // bit_t 2.3
            bit_t HDRadio_Connected    :1;        // bit_t 4.
            bit_t DAB_Connected        :1;        // bit_t 5.
            bit_t TPMS_Connected       :1;        // bit_t 6.
            bit_t Radar_Connected      :1;        // bit_t 7.

        }bits;
    }uConnetState;

    union
    {
        uint8_t byte;
        struct
        {
            bit_t Illumi_On            :1;        // bit_t 0.
            bit_t Reverse_Flag         :1;        // bit_t 1.
            bit_t Car_Parking          :1;        // bit_t 2.
            bit_t Tbox_Connected        :1;        // bit_t 3.
            bit_t FirstPowerOnFlag     :1;        // bit_t 4.First Power On Flag. 1- First Power On; 0- not first Power On.
            bit_t PowerProtectState   :1;        // bit_t 5. 0- normal; 1- power protected. 
            bit_t MuteOn               :1;        // bit_t 6.
            bit_t LCD_Disp             :1;        // bit_t 7.

        }bits;
    }uIOState;
        
    union
    {
        uint8_t byte;
        struct
        {
             bit_t VideoDisable	    :1; /*bit0: 1: Video can't watch; 0: could watch */
             bit_t CameraVideoState :1; /*bit1: 1: Video source error; 0: Video source normal */
			 bit_t Blind_Flag:1;/*bit2: 1: enter  0:exit */
			 bit_t CvbsChannelFlag :2; //bit3~4  0:null  1:Reverse  2:blind  3:Reserve
			 bit_t CvbsChannelLock:1; //bit5  0:not lock  1:lock
             bit_t Reserve          :2;	
        }bits;
    }uDetect;
    union
    {
        uint8_t byte;
        struct
        {
            bit_t Reserve : 8;
        }bits;
    }uRev2;
}tDEV_ON_MCU_STATE;





/***********************************/


#pragma pack(1)
typedef struct 
{
    bit_t  bAuto_Open_EnFlag        :1;  //Bit0: Auto open LCD flag 1:On 0:Off 
    bit_t  bReverse_Mute_On         :1;  //Bit1: Mute when reverse function flag. 1:Open 0:Close.
    bit_t  bCamera_Mirror_Flag      :1;  // Camera mirror flag. 1:Mirror 0:Normal
    bit_t  bAuxInFormat_Flag        :2;  // AuxIn video format. 0:Auto,1:PAL,2:NTSC,3:SECAM
    bit_t  bDownmix_Flag            :1;  // 6CH flag. 1: 6CH 0:2CH
    bit_t  bRTC24Hour_Flag          :1;  // 24 hour format flag£¬0: 12 hour format, 1: 24 format.
    bit_t  bMotor_Exhibit_Flag      :1;  //Bit7: Auto open LCD angle flag. 1: Open LCD to last angle; 
                                            // 0: Open LCD to default angle.
}tSYS_FLAG1;

#pragma pack(1)
typedef struct
{
    bit_t  bRDS_CT_Set              :1;  // RDS auto reflash clock function. 0: Closed; 1: Opened.
    bit_t  bCan_Bright_Set          :1;  // Adjust brightness thru CAN function.  0: Off; 1: On.
    bit_t  bBeep_Flag               :2;  // Beep type.  0: Closed; 1: Lowering, 2:Melodious.
    bit_t  bExt_Tel_OnOff_Set       :2;  // External telephone on/off/mute set.  0: off; 1:On; 2:Mute.
    bit_t  bExt_Tel_Ch_Set          :1;  // External Telephone audio channel. 0: Left CH; 1: Right CH.
    bit_t  bActiveSound_Set         :1;  // Volume change following the speed change of vehicle function
                                            // 0: Off; 1: On.

}tSYS_FLAG2;    

#pragma pack(1)
typedef struct 
{
    bit_t  bAuxIn_SW_Set            :2;  // AuxIn Input Level.  0: Low gain; 1: Middle; 2: High.
    bit_t  bACC_LED_Set             :1;  // ACC LED indicate. 0: Close; 1: Open.
    bit_t  bNavi_Guidance_Mode      :2;  // Navi voice guidance mode. 0: Off; 1: Mix; 2: Interrupt.
    bit_t  bAuto_Dimmer_Set         :1;  // Auto Dimmer function. Unused.
    bit_t  bAuxIn_Source_Set        :1;  // AuxIn Source select. 0:input from rear; 1:input from front
    bit_t  bCamera_On_Off           :1;  // Reverse camera function. 0: On;  1: Off.
}tSYS_FLAG3;

#pragma pack(1)
typedef struct 
{
    bit_t  bKey_Color               :3;  // 0:Blue 1:Red 2:Amber 3:Green 4:White 5:violet
    bit_t  bAntennaSupply           :1;  // Original antenna supply. 0: Closed; 1: Opened.
    bit_t  bParking_Det_Mode        :2;  // Current detect mode of parking. Bit1-2 = '00': Don't detect
                                            // parking. '01': Parking detect use Level detect. '10': //Parking 
                                            // detect use Serial Pulse detect. '11': Parking detect from CAN
                                            // command.
    bit_t  bSecureCheck             :1;  //Check the security password
    bit_t  bBootPrayer              :1;  // Reserved for future use.
}tSYS_FLAG4; 

#pragma pack(1)
typedef struct 
{
	bit_t  SleepTimeSet             :2;
    bit_t  bReserved                :6;  // Reserved for future use.
}tSYS_FLAG5;


typedef enum
{
    GEN_ID_RADIO_AREA                = 0,
    GEN_ID_LOAD_FACTORY,
    GEN_ID_AUX_VIDEO_FORMAT,
    GEN_ID_OPEN_LCD,
    GEN_ID_CLOCK_MODE,
    GEN_ID_CLOCK_HOUR,                //5
    GEN_ID_CLOCK_MINUTE,
    GEN_ID_CAMERA_MIRROR_MODE,
    GEN_ID_RDS_CT_SET,
    GEN_ID_CAN_BRIGHT_ON_OFF,
    GEN_ID_CAN_BACK_LIGHT_LEVEL,    // 10
    GEN_ID_BEEP_SWITCH,
    GEN_ID_EXT_TEL_MUTE_SWITCH,         
    GEN_ID_EXT_TEL_AUDIO_CH_SET,
    GEN_ID_AUX_IN_LEVEL_SET,
    GEN_ID_REVERSE_CAMERA_ON_OFF,   // 15
    GEN_ID_AUTO_DIMMER,
    GEN_ID_AUX_IN_SOURCE_TYPE,         
    GEN_ID_KEY_COLOR_SET,
    GEN_ID_NAVI_VOICE_GUIDANCE_MODE,
    GEN_ID_ACTIVE_SOUND_SET,        // 20    
    GEN_ID_ACC_LED_SET,
    GEN_ID_PARKING_DET_MODE,
    GEN_ID_ORIGINAL_ANTENNA_SUPPLY,
    GEN_ID_ANTI_THEFT,
    GEN_ID_ANT_GAIN,				//25
    GEN_ID_FAN_TEST,		
    GEN_ID_AUTO_AGING,
    GEN_ID_TUNER_TEST,
    GEN_ID_KEYPAD_TEST,
    GEN_ID_PRAYER_CTL,			//no use
    GEN_ID_SET_SLEEP_TIMING,      //no use

    SCR_ID_BL_LVE,
    SCR_ID_TILT,
    SCR_ID_NIGHT_BL_LEV,


    GEN_ID_NUM
}GENERAL_SETTING_INDEX_ENUM;



#pragma pack(1)
typedef struct 
{
    tSYS_FLAG1     tFlag1;
    uint8_t        cRadioField;            // Radio field of Tuner
    tSYS_FLAG2     tFlag2;
    tSYS_FLAG3     tFlag3;
    tSYS_FLAG4     tFlag4;
    tSYS_FLAG5     tFlag5;
    uint8_t        AntGain;        //Antenna Gain Attn.

}tSYS_GENERAL_SETTING;
 

#pragma pack(1)
typedef union{
    tSYS_GENERAL_SETTING tBlock;
    uint8_t              aArray[sizeof(tSYS_GENERAL_SETTING)];   
}uSYS_GENERAL_SETTING;


/***********************************/
#pragma pack(1)
typedef struct {/*5Bytes*/ 
    uint8_t cBaseBR;
    uint8_t cTilt;   /*b0-b2:tilt,b3-b4:No use,b5:TV Sound,b6:no use,b7:TFT state*/
    uint8_t cNightBR,cDayBR;
    uint8_t cBRMode; /*0:auto 1:Day 2:Night*/
    uint8_t cContrast;
}tSYS_SCREEN_SETTING;


#pragma pack(1)
typedef struct {
     uint8_t Type;        //Currently EQ Type, Same as GEQ Preset
     uint8_t BassGain;    
     uint8_t MidGain;
     uint8_t TrebleGain;
     uint8_t Fader;
     uint8_t Balance;
     uint8_t SysVol;
     uint8_t NaviVol;
     uint8_t BtVol;
     uint8_t AppVol;
}tSYS_AUDIO_SETTING;
typedef struct{
    uSYS_GENERAL_SETTING uGenBlock;
    tSYS_SCREEN_SETTING  tScrBlock;
    tSYS_AUDIO_SETTING   tAudioBlock;
	uint8_t DevelopFlag;
    uint16_t iCheckSum;
}tSYS_ROM_DATA;

#pragma pack(1)
typedef union{
    uint8_t byte;
    struct{
        bit_t   bApuActiveCheck  :1;  /*def:0    ----1*/      
        bit_t   bApuPwrOnAtSleep :1;  /*def:1(other)/0(s301)----0*/
        bit_t   bApuDropSleep    :1;  /*def:0(Other)/1(s301)----1*/
        bit_t   bSleepInHSE      :1;   /*----1*/
	 bit_t   bSysPowerOn	   :1;  /*System Power On state = 1; Power Off state(standby state) = 0*/
    }field;
}uAPU_FUNC_CONFIG;


#pragma pack(1)
typedef struct{
     /*Add at 2014-04-08*/
    uint32_t       iWaitSleepTime;
    uint32_t       iWaitOffTime;
    uint32_t       iEconomyTime;
    uint8_t        bIllMode;  /*0:IO,1:PWM 2:RAM*/
    uint8_t        cBROffSet; /*cBROffSet: extern ILL*/
    
    /*********************/
    /** Add you setting data,It will not be cleard by "Factory" command     */
    /** If you add one or more, do not forget to add it's defaut value!!!.  */
    uint8_t        cTftPwmDuty_pwm[21],cTftPwmMin;
    uint8_t        cTftPwmDuty_offset[21],cTftBaseOffSet;
    uint8_t        cTftLedDuty_pwm[21],cTftLedPwmMin;
    /*********************/
    uint8_t TunerAntPwr;
    uAPU_FUNC_CONFIG  uApuFuncFlag;

    /*********************/
    uint16_t       iCheckSum;
    
}tSYS_SETTING_ROM_DATA;

typedef struct{
	uint8_t SysBtCallFlag		:1;		/*1: BT call status, 0: exit BT call */
	uint8_t SysCommSpySwitch   :1;     /*0: close; 1- open */
	uint8_t SysReverseReq		:1;  /*system Reverse Request */
	uint8_t SysApuStandyMode	:1;  /*APU standby(AVOFF) mode: 0- none; 1- standby mode */
	uint8_t SysAccState		:2;		/*System Acc State : 0-OFF; 1-ACC, 2-ON */
	uint8_t SysAutoTestEnter	:1;
	uint8_t FastCameraMode	:1;		/*quick(fast) camera(reverse) mode */
	
       uint8_t SysILLlevel;
}tSYS_STATE_DATA;

_SYS_ tSYS_STATE_DATA   SysWorkStatusGrp;
_SYS_ tDEV_ON_MCU_STATE g_tMcuDevState;
_SYS_ uint8_t Reverse_Flag;

#pragma section data "no_init" begin    

_SYS_ tSYS_ROM_DATA g_tSysRomData;
_SYS_ tSYS_SETTING_ROM_DATA g_tSysSettingRomData;


#pragma section data "no_init" end    

_SYS_ void SYS_Init(void);
_SYS_ void SYS_ExecGenSetting(uint8_t Idx,uint8_t Param);
_SYS_ void SYS_loadDefaultParam(tEEP_DATA *pBlock);


#endif

