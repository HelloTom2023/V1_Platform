#define _SYS_USER_C_
#include "..\config\inc.h"

const uint16_t la_cSrcFlagDefault[] = {
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// TUNER,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// DVD,     
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// CD-BOX,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// TV,    
    B_SRC_UI_UPDATA|B_SRC_FLOAT,// NAVI,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// R_AUX,  
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// DTV,  
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// SD ,    //SD use one button on MainMenu.
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// XM,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// IPOD,    //iPod use one button on MainMenu.
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// USB,    //USB use one button on MainMenu.
    B_SRC_BOOT_START|B_SRC_VIDVALID|B_SRC_HOLD_HMSG,// Camera,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// F_AUX,    //Front AuxIn(Aux1)
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// BT_MUSIC,   //Attention: APU unused this ID. APU enter directly into BT menu when press BT button on MainMenu.
    
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// SIRIUS,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// HDRADIO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// PANDORA,    
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// INTERNET,    //Install applications which always need audio channel are all called ,// INTERNET.
    B_SRC_IGNORE_HMSG|B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// AVOFF,    //System enter into Standby mode with clock GUI display.
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// MHL,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// MIRROR_LINK,
    
    B_SRC_BOOT_START|B_SRC_HOLD_HMSG|B_SRC_SW_HOLD|B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// SYS_STDBY,
    B_SRC_UI_UPDATA|B_SRC_VIDVALID,// DVR
	
    //If Disc/iPod/USB/SD were separated Audio/Video/Image, 
    //use the follow source id to replace ,// DVD/,// IPOD/,// USB/,// SD
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// DISC_AUDIO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// DISC_VIDEO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// DISC_IMAGE,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// IPOD_AUDIO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// IPOD_VIDEO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// USB_AUDIO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// USB_VIDEO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// USB_IMAGE,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// SD_AUDIO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// SD_VIDEO,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// SD_IMAGE,
    
    B_SRC_HOLD_HMSG|B_SRC_AUDVALID,// BT_PHONE,                            
    B_SRC_HOLD_HMSG|B_SRC_AUDVALID,// 3G_PHONE,
    B_SRC_HOLD_HMSG|B_SRC_SW_HOLD|B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,// RDS_TA,
    B_SRC_AUDVALID,// NAVI_AUDIO,
    B_SRC_BOOT_START|B_SRC_VIDVALID|B_SRC_HOLD_HMSG,// REVERSE,
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,   //CAR_SYNC
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,   //CAR_Media
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,   //CAR_CDC
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,   //CAR_TUNER
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,   //CAR_OnSTAR
    0,//B_SRC_HOLD_HMSG,// MONITOR_OFF,
    B_SRC_BOOT_START|B_SRC_HOLD_HMSG|B_SRC_SW_HOLD|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// SLEEP,
    B_SRC_BOOT_START|B_SRC_HOLD_HMSG|B_SRC_SW_HOLD|B_SRC_AUDVALID|B_SRC_VIDVALID|B_SRC_REAR_EN,// REAR_OFF,
    B_SRC_AUDVALID|B_SRC_VIDVALID,   //APP_TONE
    B_SRC_AUDVALID|B_SRC_VIDVALID,   //VR
    B_SRC_BOOT_START|B_SRC_AUDVALID|B_SRC_HOLD_HMSG|B_SRC_MUTE_BEEP, //LOGO
    B_SRC_BOOT_START|B_SRC_HOLD_HMSG|B_SRC_AUDVALID|B_SRC_MUTE_BEEP,//LOGO_AUDIO
    B_SRC_BOOT_START|B_SRC_HOLD_HMSG,// RADAR,
    B_SRC_BOOT_START|B_SRC_HOLD_HMSG|B_SRC_AUDVALID,  //CAR_TBOX
    B_SRC_UI_UPDATA|B_SRC_AUDVALID|B_SRC_VIDVALID,  //REAR_BOX
    0,//NAVI_MIX
    B_SRC_BOOT_START|B_SRC_HOLD_HMSG,// SRC_TYPE_BIRDVIEW,

    0xff,// NUM,

};           

const uint8_t lc_bSrcKeyOpTransTab[OP_INPUT_N] = {
    0,    /*OP_KEY_ACTION_NONE ,       Key action option*/
    1,    /*OP_KEY_ACTION_SP,         Key only included short press attrubity is short pressed*/
    1,    /*OP_KEY_ACTION_LP,          Key included long press attrubity is long pressed*/
    0,    /*OP_KEY_ACTION_SH,         Key only included short press attrubity is hold pressed*/
    0,    /*OP_KEY_ACTION_LH ,        Key included long press attrubity is hold pressed*/
    0,    /*OP_KEY_ACTION_LSP,         Key included long press attrubity is short pressed*/
    0,    /*OP_KEY_ACTION_SREL,       Key only included short press attrubity is released after a short pressing*/
    0,    /*OP_KEY_ACTION_SHREL,       Key only included short press attrubity is released after a hold pressing*/
    0,    /*OP_KEY_ACTION_LREL,        Key included long press attrubity is released after a long pressing*/
    0,    /*OP_KEY_ACTION_LHREL,      Key included long press attrubity is released after a hold pressing*/
    1,    /*OP_KEY_ACTION_LSREL,       Key included long press attrubity is released after a short pressing*/
    2,    /*OP_ENCODE_TURN_LEFT,       Encode is turned left in one step*/
    2,    /*OP_ENCODE_TURN_RIGHT,      Encode is turned right in one step*/
};

#include "sys_avoff.c"
#include "sys_aux.c"
#include "sys_bt.c"
#include "sys_camera.c"
#include "sys_disc.c"
#include "sys_dtv.c"
#include "sys_ipod.c"
#include "sys_mhl.c"
#include "sys_navi.c"
#include "sys_usb.c"
#include "sys_carmedia.c"
#include "sys_TBox.c"
#include "sys_Dvr.c"

uint8_t SRC_InitHook(void)
{
	//Create your source
	Tuner_CreateSrc();
	USB_CreateSrc();
	SD_CreateSrc();
	AUX_CreateSrc();
	iPod_CreateSrc();
	MHL_CreateSrc();
	Camera_CreateSrc();
	BT_CreateSrc();
	Dvd_CreateSrc();
	Navi_CreateSrc();
	DTV_CreateSrc();
	MLink_CreateSrc();
	AVOFF_CreateSrc();
	//CarMedia_CreateSrc();
	Tbox_CreateSrc();
	Dvr_CreateSrc();
	return TRUE;
}

uint8_t SRC_MsgHandleHook(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive)
{
   uint8_t re = FALSE;
   
   return re; 
}

