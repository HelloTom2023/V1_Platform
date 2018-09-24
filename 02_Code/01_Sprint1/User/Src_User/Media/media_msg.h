/*MCU TX*/
typedef enum{
    GID_MCU_TX_CMD,           //0x0    //MCU send command to APU.    
    GID_MCU_TX_SETTING,       //0x1    //MCU send setting data to APU.    
    GID_MCU_TX_SYS_INFO,      //0x2    //Sys info: system volume, clock, version    
    GID_MCU_TX_RADIO_DATA,    //0x3    //Radio and RDS data.      
    GID_MCU_TX_SWC_DATA,      //0x4    //SWC data and state.    
    GID_MCU_TX_CAN_INFO,      //0x5    //Car bus information.    
    GID_MCU_TX_MCU_UPDATE,    //06    //For MCU software update.    
    GID_MCU_TX_8836_UPDATE,    //0x7   //For CAN adaptor software update.    
    GID_MCU_TX_FCT_TEST,      //0x8
    GID_MCU_TX_PRJ_INFO,     //0x09

    GID_MCU_TX_NUM,
    GID_MCU_TX_TEST           
}eGID_MCU_TX;     

#define SID_MCU_DEFAULT                		0x01
/*GID_MCU_TX_CMD SID define */
#define SID_MCU_TX_CMD                 		0x01    //MCU send CMD
#define SID_MCU_TX_QUERY_STATE         	0x02    //MCU query apu state
/*GID_MCU_TX_SETTING SID define */
#define SID_MCU_TX_SYSSETTING          0x01    //MCU send system setting to APU.
#define SID_MCU_TX_GENERALSETTING      0x02    //General setting: system¡¯s flag, time, etc.
#define SID_MCU_TX_AUDIOSETTING        0x03    //Normal Audio setting. 
#define SID_MCU_TX_ASP_SETTING         0x04    //ASP/DSP setting. 
#define SID_MCU_TX_GEQ_SETTING         0x05    //Graphic EQ setting of DSP.
#define SID_MCU_TX_PEQ_SETTING         0x06    //Parameter EQ setting of DSP.
#define SID_MCU_TX_SCREENSETTING       0x07    //Screen setting. Like screen title, TFT state.
#define SID_MCU_TX_6CH_VOLSETTING      0x08    //Volume setting of 6CH.
#define SID_MCU_TX_CH_GAIN             0x09    //Channel gain.
#define SID_MCU_TX_DEVELOP             0x0A

/*GID_MCU_TX_SYS_INFO define */
#define SID_MCU_TX_VOLUME              0x01    //MCU send system main volume value to APU.
#define SID_MCU_TX_SYSCLK              0x02    //Send system clock (Use MCU clock).
#define SID_MCU_TX_VERSION             0x03    //Send MCU software version to APU.
#define SID_MCU_TX_DEVICESTATUS        0x04    //Send device status which are controlled or detected by MCU
#define SID_MCU_TX_KEYSTATE		     0x05    //Send keyCode to APU. //modify 20150513
#define SID_MCU_TX_SYS_STATE_INFO      0x06	//
#define SID_MCU_TX_SYS_DEVICE_INFO     0x07//(no use)
#define SID_MCU_TX_SYS_TIME_BASE       0x08
#define SID_MCU_TX_VOL_ALL			0x09
/*GID_MCU_TX_RADIO_DATA define */
#define SID_MCU_TX_RADIOINFO           0x01    //Send Tuner information.
#define SID_MCU_TX_RADIOPRESETFREQLIST 0x02    //Send Tuner¡¯s Preset Frequency List.
#define SID_MCU_TX_RADIOSTATIONLIST    0x03    //Send Tuner¡¯s valid stations list.
#define SID_MCU_TX_RADIOSIGNALLEVEL    0x04    //Send Tuner signal meter.
#define SID_MCU_TX_RDS_INFO            0x05    //Send RDS information.
#define SID_MCU_TX_RDS_CURRPTY         0x06    //Send Current PTY.
#define SID_MCU_TX_RDS_PS_NAME         0x07    //Send PS Name of current station.
#define SID_MCU_TX_RDS_RT_INFO         0x08    //Send RDS broadcast text information.
#define SID_MCU_TX_RDS_PI_INFO         0x09    //Send PI code of preset.
#define SID_MCU_TX_RDS_PSNAMELIST      0x0A    //Send PS name list.
#define SID_MCU_TX_RADIOAREA            0x0B

/*GID_MCU_TX_SWC_DATA define */
#define SID_MCU_TX_SWC_RUNMODE         0x01    //Send SWC run mode.param: 0:save and Exit!,1: 
	#define OP_SWC_TX_RM_START             0x00
    	#define OP_SWC_TX_RM_FINISH            0x01  
#define SID_MCU_TX_SWC_KEYSTATE        0x02     //Send one key pair.To apu: 0xXX:Key AD sample is completed;To mcu:UICC_x to pair with the Key!!
    #define OP_SWC_TX_KS_ALLKEY            0x01 //sand all paired key to apu
    #define OP_SWC_TX_KS_REPAIR            0x02 //current key has paired.
    #define OP_SWC_TX_KS_REQ_UICC          0x03 //Key is ready,request pair function
    #define OP_SWC_TX_KS_REQ_NEXT          0x04 //current key is paired ok,requeset next key process
    #define OP_SWC_TX_KS_TIMEOUT           0x05 //time out to operate paired,do not save and exit 
    #define OP_SWC_TX_KS_NSUPPORT          0x06 //Don't support to paided any key!HW error !
#define SID_MCU_TX_SWC_ALLSETTING      0x03
#define SID_MCU_TX_SWC_ERROR_CODE      0x04

 /*GID_MCU_TX_MCU_UPDATE define */
#define SID_MCU_TX_REQ_UPDATE_CMD      0x01    //MCU request APU to update MCU.
#define SID_MCU_TX_UPDATE_CONFIRM      0x02    //MCU response APU¡¯s MCU update command.
#define SID_MCU_TX_UPDATE_REQKEY       0x03    //MCU request APU sends IAP Key.
#define SID_MCU_TX_UPDATE_REQDATA      0x04    //MCU request the update file packet.
#define SID_MCU_TX_UPDATE_REQRESET     0x05    //MCU request reset after receive the checksum.

 /*GID_MCU_TX_TW8836_UPDATE define */
#define SID_MCU_TX_8836_UPDATECONFIRM   0x01    //MCU transfer  confirm cmd to APU.
#define SID_MCU_TX_8836_REQUPDATEKEY    0x02    //MCU request  update key.
#define SID_MCU_TX_8836_REQUPDATEDATA   0x03    //MCU request  update file packet.

/*GID_MCU_TX_FCT_TEST define */
#define SID_MCU_TX_FCT_CMD				0x01
#define SID_MCU_TX_FCT_FUNCSWITCH		0x02
#define SID_MCU_TX_FCT_MEDIACONTROL	0x03
#define SID_MCU_TX_FCT_BLUETOOTH		0x04
#define SID_MCU_TX_FCT_GPS				0x05
#define SID_MCU_TX_FCT_TPMS			0x06
#define SID_MCU_TX_FCT_VIDEOSET		0x07
#define SID_MCU_TX_FCT_WIFI			0x08
#define SID_MCU_TX_FCT_REQVERSION		0x09

/*GID_MCU_TX_PRJ_INFO define */
#define SID_MCU_TX_DVR_STATE		0x01

/*MCU RX*/
//3 ==========APU==>MCU Group ID==========
typedef enum{
    GID_MCU_RX_CMD,                 //0x0     // Command from APU
    GID_MCU_RX_STATUS,              //0x1     // Report APU's Main status
    GID_MCU_RX_SETTING,             //0x2     // APU Set command 
    GID_MCU_RX_TIME_DATA,           //0x3     // Send GPS time and Data to MCU
    GID_MCU_RX_MEDIA_INFO,          //0x4     // Media Player information
    GID_MCU_RX_CAN_CTL,             //0x5     // CAN control infomation
    GID_MCU_RX_DEVICE_STATUS,       //0x6     // USB/SD/iPod etc. APU's device state info
    GID_MCU_RX_SWC_CTL,             //0x7     // Steering Wheel Controller run mode
    GID_MCU_RX_PRJ_SPCL,           //0x8     //special project 
    GID_MCU_RX_MCU_UPDATE,          //0x9     // Update MCU software
    GID_MCU_RX_8836_UPDATE,          //0xA     // Update CAN Adaptor software
    GID_MCU_RX_FCT_TEST,            //0xB     // For FCT Test
   
    GID_MCU_RX_NUM,
}eGID_MCU_RX;

/*For group which have one member*/
#define SID_MCU_RX_DEFAULT             0x01    // Default sub ID for APU Tx Group

/*GID_MCU_RX_CMD*/
#define SID_MCU_RX_COMMAND           0x01    //Command and parameter, see UICC_Def.h
#define SID_MCU_RX_REQPACKAGE		0x02	//Request Resend data package.		// bolte
#define SID_MCU_RX_APU_DEBUG_DATA 0x03	//Request send data that Apu decide	


/*GID_MCU_RX_STATUS*/
#define SID_MCU_RX_OS_STATUS         0x01    //APU report status to MCU.
#define SID_MCU_RX_OS_TYPE             0x02    //APU send OS type info to MCU
#define SID_MCU_RX_TOUCH_DATA	0x03	// APU send touch screen data information

/*GID_MCU_RX_SETTING*/
#define SID_MCU_RX_SET_AUDIO           0x01
#define SID_MCU_RX_SET_6CH_VOL       0x02
#define SID_MCU_RX_SET_GENERAL       0x03
#define SID_MCU_RX_SET_ASP             	  0x04
#define SID_MCU_RX_SET_GEQ               0x05
#define SID_MCU_RX_SET_PEQ               0x06
#define SID_MCU_RX_SET_RDS               0x07
#define SID_MCU_RX_SET_CH_GAIN         0x08
#define SID_MCU_RX_SET_SCREEN          0x09
#define SID_MCU_RX_SET_TUNERFREQ    0x0A
#define SID_MCU_RX_SET_VEHICLE         0x0B
#define SID_MCU_RX_SET_DIGITALOVERLAY  0x0C
#define SID_MCU_RX_SET_CAMLINEDEAL  0x0D
#define SID_MCU_RX_SET_REVERSESTART  0x0E
#define SID_MCU_RX_SET_REVERSESTOP  0x0F

/*GID_MCU_RX_TIME_DATA*/
#define SID_MCU_RX_GPS_TIME             0x01    //APU send GPS time to MCU.
#define SID_MCU_RX_DATE                    0x02    //APU send Data to MCU.
#define SID_MCU_RX_TIME_BASE           0x03 //SYSTEM rtc total second.

/*GID_MCU_RX_MEDIA_INFO*/
#define SID_MCU_RX_PLAY_INFO           0x01    //APU send media info for Can or little LCD.
#define SID_MCU_RX_PLAY_TIME           0x02    //send media play time for Can or little LCD.
#define SID_MCU_RX_PLAY_TITLE		  0x03

/*GID_MCU_RX_CAN_CTL*/
#define SID_MCU_RX_NAVI_CMD       	0x01    //APU send Air condition control command.
#define SID_MCU_RX_DTV_CMD       	0x02    //APU send Center control command.
#define SID_MCU_RX_EOL_CMD 			0x03    //APU send EOL data command.
#define SID_MCU_RX_UIKEY_CMD  		0x04    //APU send UI Key command.
#define SID_MCU_RX_Latitude_CMD 	0x05    //
#define SID_MCU_RX_NAVI_SPEED_LIMIT_CMD 0x06 //APU SEND NAVI SPEED LIMIT INFO
#define SID_MCU_RX_MAINTAIN_DATA_CMD 0x07 //APU SEND MOUNTMAIN DATA INFO
#define SID_MCU_RX_DATA_TIME_CMD      0x08

/*GID_MCU_RX_DEVICE_STATUS*/
#define SID_MCU_RX_DEVICESTATUS        0x01    //APU send device status to MCU.

/*GID_MCU_RX_SWC_CTL*/
#define SID_MCU_RX_SWC_RUNMODE         0x01    //APU send current run mode of SWC to MCU.
#define SWC_RX_OP_STD_START            	0x00
#define SWC_RX_OP_CLEAR                		0x01
#define SWC_RX_OP_SAVE                 		0x02
#define SWC_RX_OP_EXIT                 		0x03
#define SID_MCU_RX_SWC_KEYCODE         0x02    //APU send key code of SWC to MCU.


/*GID_MCU_RX_PRJ_SPCL*/
#define USERID_MCU_RX_DVR_SETREQ         0x01

/*GID_MCU_RX_MCU_UPDATE*/
#define SID_MCU_RX_MCU_UPDATECMD       0x01    //APU inform MCU enter update mode.
#define SID_MCU_RX_MCU_UPDATEKEY       0x02    //APU response MCU Update key.
#define SID_MCU_RX_MCU_UPDATEDATA      0x03    //APU send MCU update data.
#define SID_MCU_RX_MCU_UPDATECHECKSUM  0x04    //APU send update checksum to MCU.
#define SID_MCU_RX_MCU_UPDATERSTREADY  0x05    //APU send update reset ready to MCU.
#define SID_MCU_RX_MCU_UPDATE_CONFIG   0x06
/*GID_MCU_RX_TW8836_UPDATE*/
#define SID_MCU_RX_8836_UPDATECMD       0x01    //APU inform 8836 enter update mode.
#define SID_MCU_RX_8836_UPDATEKEY       0x02    //APU send 8836 update key.
#define SID_MCU_RX_8836_UPDATEDATA      0x03    //APU send 8836 update data.
#define SID_MCU_RX_8836_UPDATECHECKSUM  0x04    //Send 8836 update checksum to MCU.

/*GID_MCU_RX_FCT_TEST*/
#define SID_MCU_RX_AUTO_TEST				0x01
#define SID_MCU_RX_FCT_RESULT_BASIC		0x02
#define SID_MCU_RX_FCT_RESULT_BLUETOOTH	0x03
#define SID_MCU_RX_FCT_RESULT_GPS		0x04
#define SID_MCU_RX_FCT_RESULT_TPMS		0x05
#define SID_MCU_RX_FCT_RESULT_WIFI		0x06
#define SID_MCU_RX_FCT_RESULT_VERSION	0x07

/*Mcu upload info to APU*/
#define OP_INFO_SYSSETTING           ((SID_MCU_TX_SYSSETTING ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_GENERALSETTING     ((SID_MCU_TX_GENERALSETTING ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_AUDIOSETTING         ((SID_MCU_TX_AUDIOSETTING ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_ASP_SETTING          ((SID_MCU_TX_ASP_SETTING ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_GEQ_SETTING          ((SID_MCU_TX_GEQ_SETTING ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_PEQ_SETTING          ((SID_MCU_TX_PEQ_SETTING ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_SCREENSETTING        ((SID_MCU_TX_SCREENSETTING ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_6CH_VOLSETTING       ((SID_MCU_TX_6CH_VOLSETTING ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_CH_GAIN              	((SID_MCU_TX_CH_GAIN ) | (GID_MCU_TX_SETTING<<8))
#define OP_INFO_DEVELOP               ((SID_MCU_TX_DEVELOP ) | (GID_MCU_TX_SETTING<<8))


#define OP_INFO_VOLUME               ((SID_MCU_TX_VOLUME ) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_SYSCLK               ((SID_MCU_TX_SYSCLK ) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_VERSION              ((SID_MCU_TX_VERSION ) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_DEVICESTATUS         ((SID_MCU_TX_DEVICESTATUS ) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_KEYDATA		      ((SID_MCU_TX_KEYSTATE ) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_SYS_STATE_INFO      ((SID_MCU_TX_SYS_STATE_INFO ) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_SYS_DEVICE_INFO      ((SID_MCU_TX_SYS_DEVICE_INFO ) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_SYS_TIME_BASE        ((SID_MCU_TX_SYS_TIME_BASE ) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_SYS_VOL_ALL        ((SID_MCU_TX_VOL_ALL) | (GID_MCU_TX_SYS_INFO<<8))
#define OP_INFO_RADIOINFO            ((SID_MCU_TX_RADIOINFO ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RADIOPRESETFREQLIST  ((SID_MCU_TX_RADIOPRESETFREQLIST ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RADIOSTATIONLIST     ((SID_MCU_TX_RADIOSTATIONLIST ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RADIOSIGNALLEVEL     ((SID_MCU_TX_RADIOSIGNALLEVEL ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RDS_INFO             ((SID_MCU_TX_RDS_INFO ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RDS_CURRPTY          ((SID_MCU_TX_RDS_CURRPTY ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RDS_PS_NAME          ((SID_MCU_TX_RDS_PS_NAME ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RDS_RT_INFO          ((SID_MCU_TX_RDS_RT_INFO ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RDS_PI_INFO          ((SID_MCU_TX_RDS_PI_INFO ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RDS_PSNAMELIST       ((SID_MCU_TX_RDS_PSNAMELIST ) | (GID_MCU_TX_RADIO_DATA<<8))
#define OP_INFO_RADIOAREA             ((SID_MCU_TX_RADIOAREA) | (GID_MCU_TX_RADIO_DATA<<8))

#define OP_INFO_SWC_RUNMODE          ((SID_MCU_TX_SWC_RUNMODE) | (GID_MCU_TX_SWC_DATA<<8))
#define OP_INFO_SWC_KEY_STATE        ((SID_MCU_TX_SWC_KEYSTATE) | (GID_MCU_TX_SWC_DATA<<8))
#define OP_INFO_SWC_ALLSETTING       ((SID_MCU_TX_SWC_ALLSETTING) | (GID_MCU_TX_SWC_DATA<<8))
#define OP_INFO_SWC_ERROR_CODE       ((SID_MCU_TX_SWC_ERROR_CODE) | (GID_MCU_TX_SWC_DATA<<8))

#define OP_INFO_CANBUS_DATA          ((SID_MCU_DEFAULT)|(GID_MCU_TX_CAN_INFO<<8))
#define OP_INFO_REQ_UPDATE_CMD       ((SID_MCU_TX_REQ_UPDATE_CMD ) | (GID_MCU_TX_MCU_UPDATE<<8))
#define OP_INFO_UPDATE_CONFIRM       ((SID_MCU_TX_UPDATE_CONFIRM ) | (GID_MCU_TX_MCU_UPDATE<<8))
#define OP_INFO_UPDATE_REQKEY        ((SID_MCU_TX_UPDATE_REQKEY ) | (GID_MCU_TX_MCU_UPDATE<<8))
#define OP_INFO_UPDATE_REQDATA       ((SID_MCU_TX_UPDATE_REQDATA ) | (GID_MCU_TX_MCU_UPDATE<<8))
#define OP_INFO_UPDATE_REQRESET      ((SID_MCU_TX_UPDATE_REQRESET ) | (GID_MCU_TX_MCU_UPDATE<<8))
#define OP_INFO_8836_UPDATECONFIRM    ((SID_MCU_TX_8836_UPDATECONFIRM ) | (GID_MCU_TX_8836_UPDATE<<8))
#define OP_INFO_8836_REQUPDATEKEY     ((SID_MCU_TX_8836_REQUPDATEKEY ) | (GID_MCU_TX_8836_UPDATE<<8))
#define OP_INFO_8836_REQUPDATEDATA    ((SID_MCU_TX_8836_REQUPDATEDATA ) | (GID_MCU_TX_8836_UPDATE<<8))
#define OP_INFO_UICC_CMD             		((SID_MCU_TX_CMD ) | (GID_MCU_TX_CMD<<8))
#define OP_INFO_QUERY_APU_STATE      ((SID_MCU_TX_QUERY_STATE)|(GID_MCU_TX_CMD<<8))

#define OP_INFO_FCT_CMD				((SID_MCU_TX_FCT_CMD)|(GID_MCU_TX_FCT_TEST<<8))
#define OP_INFO_FCT_FUNCSWITCH	((SID_MCU_TX_FCT_FUNCSWITCH)|(GID_MCU_TX_FCT_TEST<<8))
#define OP_INFO_FCT_MEDIACONTROL	((SID_MCU_TX_FCT_MEDIACONTROL)|(GID_MCU_TX_FCT_TEST<<8))
#define OP_INFO_FCT_BLUETOOTH		((SID_MCU_TX_FCT_BLUETOOTH)|(GID_MCU_TX_FCT_TEST<<8))
#define OP_INFO_FCT_GPS			((SID_MCU_TX_FCT_GPS)|(GID_MCU_TX_FCT_TEST<<8))
#define OP_INFO_FCT_TPMS		((SID_MCU_TX_FCT_TPMS)|(GID_MCU_TX_FCT_TEST<<8))
#define OP_INFO_FCT_VIDEOSET	((SID_MCU_TX_FCT_VIDEOSET)|(GID_MCU_TX_FCT_TEST<<8))
#define OP_INFO_FCT_WIFI		((SID_MCU_TX_FCT_WIFI)|(GID_MCU_TX_FCT_TEST<<8))
#define OP_INFO_FCT_REQVERSION	 ((SID_MCU_TX_FCT_REQVERSION)|(GID_MCU_TX_FCT_TEST<<8))

#define OP_INFO_PRJ_DVRSTATE	 ((SID_MCU_TX_DVR_STATE)|(GID_MCU_TX_PRJ_INFO<<8))

  

/*APU Download info to mcu*/
/*For group which have one member*/
#define OP_LOAD_COMMAND              ((SID_MCU_RX_COMMAND) | (GID_MCU_RX_CMD<<8))      //Command and parameter, see UICC emum

/*GID_MCU_RX_STATUS*/
#define OP_LOAD_OS_STATUS            ((SID_MCU_RX_OS_STATUS) | (GID_MCU_RX_STATUS<<8))  //APU report status to MCU.
#define OP_LOAD_OS_TYPE              ((SID_MCU_RX_OS_TYPE) | (GID_MCU_RX_SETTING<<8))    //APU send OS type info to MCU
/*GID_MCU_RX_SETTING*/
#define OP_LOAD_SET_AUDIO            ((SID_MCU_RX_SET_AUDIO) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_6CH_VOL          ((SID_MCU_RX_SET_6CH_VOL) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_GENERAL          ((SID_MCU_RX_SET_GENERAL) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_ASP              ((SID_MCU_RX_SET_ASP) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_GEQ              ((SID_MCU_RX_SET_GEQ) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_PEQ              ((SID_MCU_RX_SET_PEQ) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_RDS              ((SID_MCU_RX_SET_RDS) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_CH_GAIN          ((SID_MCU_RX_SET_CH_GAIN) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_SCREEN           ((SID_MCU_RX_SET_SCREEN) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_TUNERFREQ        ((SID_MCU_RX_SET_TUNERFREQ) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_VEHICLE		((SID_MCU_RX_SET_VEHICLE) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_DIGITALOVERLAY     ((SID_MCU_RX_SET_DIGITALOVERLAY) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_CAMLINEDEAL      ((SID_MCU_RX_SET_CAMLINEDEAL) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_REVERSESTART    ((SID_MCU_RX_SET_REVERSESTART) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_SET_REVERSESTOP       ((SID_MCU_RX_SET_REVERSESTOP) | (GID_MCU_RX_SETTING<<8))

/*GID_MCU_RX_TIME_DATA*/
#define OP_LOAD_RTC_GPS_TIME         ((SID_MCU_RX_GPS_TIME) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_RTC_DATE             ((SID_MCU_RX_DATE) | (GID_MCU_RX_SETTING<<8))
#define OP_LOAD_RTC_BASE             ((SID_MCU_RX_TIME_BASE) | (GID_MCU_RX_SETTING<<8))

/*GID_MCU_RX_TIME_DATA*/
#define OP_LOAD_GPS_TIME             ((SID_MCU_RX_GPS_TIME) | (GID_MCU_RX_TIME_DATA<<8))   //APU send GPS time to MCU.
#define OP_LOAD_DATE                 ((SID_MCU_RX_DATE) | (GID_MCU_RX_TIME_DATA<<8))    //APU send Data to MCU.

/*GID_MCU_RX_MEDIA_INFO*/
#define OP_LOAD_PLAY_INFO            ((SID_MCU_RX_PLAY_INFO) | (GID_MCU_RX_MEDIA_INFO<<8))    //APU send media info for Can or little LCD.
#define OP_LOAD_PLAY_TIME            ((SID_MCU_RX_PLAY_TIME) | (GID_MCU_RX_MEDIA_INFO<<8))    //send media play time for Can or little LCD.

/*GID_MCU_RX_DEVICE_STATUS*/
#define OP_LOAD_DEVICESTATUS         ((SID_MCU_RX_DEVICESTATUS) | (GID_MCU_RX_DEVICE_STATUS<<8))   //APU send device status to MCU.

/*GID_MCU_RX_SWC_CTL*/
#define OP_LOAD_SWC_RUNMODE          ((SID_MCU_RX_SWC_RUNMODE) | (GID_MCU_RX_SWC_CTL<<8))    //APU send current run mode of SWC to MCU.
#define OP_LOAD_SWC_KEYCODE          ((SID_MCU_RX_SWC_KEYCODE) | (GID_MCU_RX_SWC_CTL<<8))   //APU send key code of SWC to MCU.


/*GID_MCU_RX_PRJ_SPCL*/
#define OP_LOAD_PRJS401_DATA          ((CAN_PRJ_ID_CHANA_S401)|(GID_MCU_RX_PRJ_SPCL<<8))
#define OP_LOAD_PRJR103H_INFO			((CAN_PRJ_ID_CHANA_R103H)|(GID_MCU_RX_PRJ_SPCL<<8))

/*GID_MCU_RX_MCU_UPDATE*/
#define OP_LOAD_MCU_UPDATECMD        ((SID_MCU_RX_MCU_UPDATECMD) | (GID_MCU_RX_MCU_UPDATE<<8))    //APU inform MCU enter update mode.
#define OP_LOAD_MCU_UPDATEKEY        ((SID_MCU_RX_MCU_UPDATEKEY) | (GID_MCU_RX_MCU_UPDATE<<8))    //APU response MCU Update key.
#define OP_LOAD_MCU_UPDATEDATA       ((SID_MCU_RX_MCU_UPDATEDATA) | (GID_MCU_RX_MCU_UPDATE<<8))    //APU send MCU update data.
#define OP_LOAD_MCU_UPDATECHECKSUM   ((SID_MCU_RX_MCU_UPDATECHECKSUM) | (GID_MCU_RX_MCU_UPDATE<<8))   //APU send update checksum to MCU.
#define OP_LOAD_MCU_UPDATERSTREADY   ((SID_MCU_RX_MCU_UPDATERSTREADY) | (GID_MCU_RX_MCU_UPDATE<<8))  //APU send update reset ready to MCU.
#define OP_LOAD_MCU_UPDATECONFIG     ((SID_MCU_RX_MCU_UPDATE_CONFIG) | (GID_MCU_RX_MCU_UPDATE<<8))  


/*GID_MCU_RX_CAN_UPDATE*/
//#define OP_LOAD_CAN_UPDATECMD        ((SID_MCU_RX_CAN_UPDATECMD) | (GID_MCU_RX_CAN_UPDATE<<8))   //APU inform CAN enter update mode.
//#define OP_LOAD_CAN_UPDATEKEY        ((SID_MCU_RX_CAN_UPDATEKEY) | (GID_MCU_RX_CAN_UPDATE<<8))    //APU send CAN update key.
//#define OP_LOAD_CAN_UPDATEDATA       ((SID_MCU_RX_CAN_UPDATEDATA) | (GID_MCU_RX_CAN_UPDATE<<8))    //APU send CAN update data.
//#define OP_LOAD_CAN_UPDATECHECKSUM   ((SID_MCU_RX_CAN_UPDATECHECKSUM) | (GID_MCU_RX_CAN_UPDATE<<8))    //Send CAN update checksum to MCU.


