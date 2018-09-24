#ifndef  _MEDIA_USER_H_
#define  _MEDIA_USER_H_

#ifdef _MEDIA_USER_FUNC_C_
#define _MEDIA_USER_
#else
#define _MEDIA_USER_   extern
#endif

typedef enum{
    UI_OS_ANDROID,
    UI_OS_WINCE,
    UI_OS_OTHER,
    UI_OS_N
}eUI_OS_TYPE;

#pragma pack(1)
typedef union
{
    uint16_t word;
    uint8_t  byte[2];
    struct
    {
        //byte0
        bit_t ipod           :1;         // 0: DisConnected  1:Connected
        bit_t usb            :1;         // 0: DisConnected  1:Connected
        bit_t sd             :1;         // 0: DisConnected  1:Connected
        bit_t dvd            :1;         // 0: Not Disc          1:Disc In
        bit_t navi           :1;         // 0: DisConnected  1:Connected
        bit_t net            :1;         // 0: DisConnected  1:Connected
        bit_t dtv            :1;         // 0: DisConnected  1:Connected
        bit_t haradio        :1;         // 0: Current present is not HD, HD Icon Close.
                                          // 1: Current present is HD, HD Icon Open.
        //byte1
        bit_t bt             :2;         // 00: BT Closed, BT Icon change gray.
                                            // 01: BT On, BT open but disconnect, BT Icon blink.
                                            // 10: BT connected. BT Icon shine always.
        bit_t wifi           :1;         //  0: Closed          1: Open
        
        bit_t Sirius_State    :1;//0: Disconnected   1: Connected.
        bit_t XM_State    :1 ;//0: Disconnected   1: Connected.
        bit_t MHL_State:1;//0: Disconnected   1: Connected.
        bit_t MirrorLink_State:1;// Disconnected   1: Connected.
        bit_t rev            :1;
    }bits;
}tAPU_DEVICE_STATUS;

#pragma pack(1)
typedef struct{
    tAPU_DEVICE_STATUS tDevflag;
    eUI_OS_TYPE        eUiOSType;
    uint16_t           iCheckSum;
}tAPU_DEV_BLOCK;

typedef enum
{
    APU_LINKREQ = 0,        // 0 for power on process
    APU_SYS_ENTER,
    APU_OS_READY,                // 2 Send to MCU when the APU's main GUI was initialized. For informing 
                            // to start communication.
    APU_MAIN_MENU_ON,            // 3 The MainMenu of APU is opened
    APU_MAIN_MENU_OFF,        // 4 The MainMenu of APU is closed
    APU_SETUP_ON,                // 5 Setup menu is opened 
    APU_EQ_ON,                    // 6 EQ menu is opened
    APU_POWER_OFF_READY = 0x07,        // 7 The APU is ready to power off
    APU_IPOD_AUDIO_ANALOG,    // 8 Switch to iPod audio mode, and audio is analog output
    APU_IPOD_AUDIO_DIGITAL,    //9 Switch to iPod audio mode, and audio is digital output
    APU_WARN_MENU_ON = 0x0a,        // 10 

    APU_REQ_UPDATA,
    APU_UPDATA_START,
    APU_UPDATA_END,

    APU_SYSTEM_UNLOCK,
    APU_SYSTEM_LOCK,
    APU_TEST_MODE = 0xfe,
    APU_BOOT_OK = 0xff,
    APU_STATE_N
}APU_STATE_t;

typedef enum{
    OP_APU_WAIT_SLEEP_ON,
    OP_APU_WAIT_SLEEP_OFF,
    OP_APU_SLEEP_ON,
    OP_APU_WAKE_UP,

    APU_PM_OP_NUM
}eAPU_PM_OPTION;


////////////////////////////////////////////////////////////////////////////////
//UICC define

////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    UICC_NONE                = 0x00,            //Unused.
    /*-----------------NEXT just used for MCU inside-------------------*/
    UICC_REVERSE_REQ	= 0x01,			// MCU Inside only. 0- exit reverse; 1- request enter reverse.
    /*-----------------end-----------------------------------------*/
    UICC_FRONT_SRC            = 0x50,            //MCU==>APU. MCU inform APU to change Front Source, Param: SOURCE_ID                                        
    UICC_REAR_SRC              = 0x51,            //MCU==>APU. MCU inform APU to change Rear Source,  Param: SOURCE_ID
    UICC_OPEN_MENU           = 0x52,            //MCU==>APU. MCU inform APU to open menu. Param: Menu_Type; 
                                            //              Menu_Type: 
                                            //            0x01=MainMenu On;
                                            //            0x02=MainMenu Off; 
                                            //            0x03=Anti-theft password Menu, APU judge PW by itself, if password ok or error, send UICC_ANTITHEFT_PW to MCU; 
                                            //            0x04=Anti-theft Locked Menu.
                                            //            0x05=Warning Menu; 
                                            //            0x06=Standby Menu(Clock Display Menu);
    UICC_MEDIA_CTL		   = 0x53,
    UICC_POWER			   = 0x54,
    UICC_AUDIO_STATE	   = 0x55,
    UICC_TEST_CMD		   = 0X56,
    UICC_BT_CTL			   = 0x57,

    //For Tuner/RDS/HD Radio/DAB function.
    UICC_FREQ_LIST_TS        = 0xA0,         //APU==>MCU. Load or Save Program when click or Long press the Tuner frequency list item.   
                                        //             Param: high 4bit:    0: Load preset program 3: Save preset program;  low  4bit:    program number. 
    UICC_ASPS_LONG_TS        = 0xA1,        //APU==>MCU. Long press the AS/PS button on GUI for inform MCU to enter into AS state.
    UICC_BAND_TS            = 0xA2,        //APU==>MCU. Tuner Band switch(between FM1,FM2,FM3,AM1,AM2) when press Band button on GUI.  Param: None
    UICC_ASPS_TS            = 0xA3,        //APU==>MCU. Preset Scan start or stop when press PS button. Param: None
    UICC_PREV_TS            = 0xA4,        //APU==>MCU. Seek Previous program.    Param: None
    UICC_NEXT_TS            = 0xA5,        //APU==>MCU. Seek Next Program.    Param: None
    UICC_STEP_UP_TS            = 0xA6,        //APU==>MCU. Step to previous frequency. Param: None
    UICC_STEP_DOWN_TS       = 0xA7,        //APU==>MCU. Step to next frequency. Param: None
    UICC_SCAN_TS            = 0xA8,        //APU==>MCU. Start or Stop scan in all frequencies, play 10 seconds when scan a valid station. Param: none
    UICC_AF_TS                = 0xA9,        //APU==>MCU. Open or close Auto Frequency change function. Param: 0=Off, 1=On.
    UICC_TA_TS                = 0xAA,        //APU==>MCU. Open or close Set Traffic Annunciation function. Param: 0=Off, 1=On.
    UICC_REG_TS                = 0xAB,        //APU==>MCU. Open or close RDS REG function. Param: 0=Off, 1=On. 
    UICC_EON_TS                = 0xAC,        //APU==>MCU. Open or close RDS EON function. Param: 0=Off, 1=On.
    UICC_PTY_ENABLE_TS        = 0xAD,        //APU==>MCU. Reversed for PTY function on or off.
    UICC_PTY_TS                = 0xAE,        //APU==>MCU. Select PTY type and start PTY seek. Param: PTY_Type.
    UICC_LOC_TS                = 0xAF,        //APU==>MCU. LOC/DX switch. Param: None
    UICC_HD_TAG_TS            = 0xB0,        //APU==>MCU. Reversed for HD Radio Tag button function.
    UICC_PTY_SEEK_TS          = 0xB1,        
    
    UICC_PREV_PRESET_TS = 0xB2, //APU==>MCU. Previous preset. Param: None
    UICC_NEXT_PRESET_TS = 0xB3, //APU==>MCU. Next preset. Param: None
    UICC_RADIO_INFO_TS = 0xB4,	//APU==>MCU. Request update Radio infomation. Param: None.
    UICC_RADIO_PAUSE=0XB5,          //APU==>MCU.Request Pause Radio.Param:None
    UICC_STOP_SEEK		= 0xB6,	 //APU==>MCU.Request Stop Seeking.Param:None
   //System Operation.
    UICC_FRONT_ZONE_TS        = 0xC0,        //APU==>MCU. APU request Front Source change. Param: SOURCE_ID. //vivid
    UICC_REAR_ZONE_TS        = 0xC1,        //APU==>MCU. APU request Rear Source change.  Param: SOURCE_ID.
    UICC_BEEP_ONLY_TS        = 0xC2,        //APU==>MCU. Once Beep sound for button click.    Param: none.
    UICC_BEEP_FAIL_TS        = 0xC3,        //APU==>MCU. Twice Beep sound for fail button click. Param: none.
    UICC_MONITOR_OP        = 0xC4,       //APU==>MCU. APU inform MCU enter monitor off or on    Param: 0=monitor off, 1=monitor on.
    UICC_CELEBRATION        = 0xC5,        //APU==>MCU. APU inform MCU that touch screen celebration state. Param: 0=Start, 1=End. 
    UICC_VIDEO_SWEN         = 0xC6,        //APP video channel switch OK£¬request MCU video channel.
    UICC_MPEG_RESET            = 0xC7,        //APU==>MCU. APU request MCU to reset MPEG when MPEG occur abnormal or MPEG update completed.
    UICC_MPEG_MAIN_STATE    = 0xC8,        //APU==>MCU. APU transmit the main state of MPEG to MCU for eject disc operation. Param=MPEG_MAIN_SATE;                                                   

    UICC_BT_PHONE_AUDIO        = 0xC9,        //APU==>MCU. BT phone audio channel on or off. Inform MCU to switch audio channel to BT phone channel or not.
                                        //Param: 0=BT audio channel off, 1=BT phone audio channel on;

    UICC_APP_PROMPT_TONE         = 0xCA,        //APU==>MCU. BT A2DP audio channel on or off. Inform MCU to switch the audio channel to BT music channel or not.      
                                        //Param: 0=BT A2DP audio channel off, 1= BT A2DP channel on; 

    UICC_3G_PHONE_AUDIO     = 0xCB,       //APU==>MCU. Inform MCU switch audio channel to 3G audio channel. Param: 0=off, 1=3G phone on.

    UICC_BT_RESET            = 0xCC,       //APU==>MCU. Inform MCU to reset BT module when BT reset is controlled by MCU. Param: None

    UICC_BT_UPDATE            = 0xCD,       //APU==>MCU. Inform MCU to generate BT update timing sequence when BT need update(using Parrot BT module). Param: None
    UICC_NAVI_AUDIO            = 0xCE,        //APU==>MCU. Inform MCU to play NAV audio 1: navi audio on  0: navi audio off
    UICC_VR_STATE 			= 0xCF, //APU==>MCU. APU inform MCU the VR state. 0 = VR End, 1 = VR Begin.
    UICC_SYS_RESTART = 0xD0,			//APU==>MCU. After App copy updata files ok, app send this comm to notify mcu restart sys.bolte
    UICC_MUTE= 0xD1,
    UICC_VOLUME_DOWN = 0xD2,
    UICC_VOLUME_UP = 0xD3,
    UICC_USB_MODE = 0xD4,
    UICC_INFO_REQ = 0xD5, 		// APU==>MCU get mcu system state data.
    UICC_COMM_SPY = 0xD6,
    UICC_DEFAULT_FACT = 0xD7,	//APU==>MCU Recovery to factory default state.	// BOLTE
    UICC_TBOX_AUDIO = 0xD8,		//APU==>MCU. Inform MCU switch Tbox Audio channel.
    UICC_CAMERA = 0xD9,			//APU==>MCU Inform Enter or exit camera. 0x00-exit; 0x01-enter.
    UICC_OSD_OVERLAY = 0xDA,		//APU==>MCU. Inform MCU enable OSD overlay function.
    UICC_NUM = 0xff,
}UICC_DEF_ENUM;

typedef enum{
   TouchState_Press=0x01,
   TouchState_Left=0x02,
   TouchState_Right=0x03,
   TouchState_Up=0x04,
   TouchState_Down=0x05,
   TouchState_TwoSide=0x06,	
}TouchState;

typedef struct{
	uint16_t PixX;
	uint16_t PixY;
	TouchState State;
}TouchInfoStruct;

extern TouchInfoStruct	ApuTouchInfo;
#pragma section data "no_init" begin
_MEDIA_USER_ tAPU_DEV_BLOCK g_tApuDevState;
#pragma section data "no_init" end



////////////////////////////////////////////////////////////////////////////////
typedef void (*fMEDIA_RXDATA_ANALYZE)(uint8_t cSid,uint8_t* p_cRxData,uint8_t cLen);
typedef uint8_t (*fMEDIA_TXDATA_ANALYZE)(uint8_t cSid,void* p_cSrcBuf,uint8_t* p_cDstBuf);
typedef struct{
    uint8_t cNum;
    const fMEDIA_RXDATA_ANALYZE* pa_fFuntionTab;
}tMEDIA_RX_FUCNTION_BLOCK;

typedef struct{
    uint8_t cNum;
    const fMEDIA_TXDATA_ANALYZE* pa_fFuntionTab;
}tMEDIA_TX_FUCNTION_BLOCK;

extern const tMEDIA_RX_FUCNTION_BLOCK g_tMediaRxPkgAnalyzeFunctionTab;
extern const tMEDIA_TX_FUCNTION_BLOCK g_tMediaTxPkgGenerateFunctionTab;


_MEDIA_USER_ void  MDI_RxPackgeHook   (uint8_t gid,uint8_t sid,uint8_t* pd,uint8_t cLen);
_MEDIA_USER_ void  MDI_TxPackgeHook  (uint8_t gid,uint8_t sid,void* src_buf);


#endif

