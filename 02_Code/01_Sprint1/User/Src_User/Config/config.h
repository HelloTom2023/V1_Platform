/*********************(    Copyright          2009    )************************
 * FILE      :
 * INFOMATIN :
 * VERSION   : v00
 * DATA      : 22/03, 2013
 * AUTHOR    : yangyan
 *
 * UPDATE    :
 * ---------------------------------------------
 *   | INFOMATION
 *   | VERSION: V10
 *   | AUTHOR:  zhaowenlong
 *   -------------------------------------------
 *     |  
 *     |  
 ******************************************************************************/

#ifndef  _CONFIG_H_
#define  _CONFIG_H_

#ifdef _CONFIG_C_
#define _CONFIG_
#else 
#define _CONFIG_ extern
#endif


#define D_SW_VER     221
#define D_HW_VER     204

////////////////////////////////////////////////////////////////////////////////
#define D_CLASSIC_APU_CTRL_IO   

#define _V850_upd3355_              0
#define _V850_upd3365_              1

#define _RENESAS_CUBE_          1
#define _IAR_EWV850_            0

#define _COMPILER_              _RENESAS_CUBE_
#define _CPU_TYPE_              _V850_upd3365_


//用于区分代码
#define CHANGAN_R103_H15T  1
#define CHANGAN_S401        2

#define PROJECT_CODE  CHANGAN_R103_H15T

#if (PROJECT_CODE == CHANGAN_R103_H15T)
//车型区分  Carcycle type
#define CAR_TYPE_AT   (1)  
#define CAR_TYPE_MT   (1) 
#endif

#define R103_H15T_OVERSEAS   //海外版开关


#define D_PRINT_EN       ON
#define D_CAN_VEHICLE_SET_STORE_IN_EEPROM	ON
#if D_PRINT_EN
#define UART0_PRINT_ENABLE
#endif


#if _COMPILER_ == _IAR_EWV850_
#define _volatile_
#else
#define _volatile_              volatile
#endif

#define D_USE_COMILER_REG_MAP   INVALID		/*use selfdefined register defination, not use the compiler define */

////////////////////////////////////////////////////////////////////////////////
extern const char ga_cSoftwareVer[] ;
extern const char ga_cBootVer[8];

/******************************************************************************/
//DEBUG
/******************************************************************************/
#define D_TEST_EN                    	0
#define D_DEBUG_HW                   	0   
#define D_DEBUG_CORE                 	1
#define D_DEBUG_I2C                  	0  
#define D_DEBUG_IR                   	0
#define D_DEBUG_ENCODE             0
#define D_DEBUG_KEY                  	0
#define D_DEBUG_SWC                  	0
#define D_DEBUG_HMI                  	1
#define D_DEBUG_POWER               1
#define D_DEBUG_IO                   	0
#define D_DEBUG_AUDIO               1
#define D_DEBUG_VIDEO                1
#define D_DEBUG_RADIO                1
#define D_DEBUG_TV                   	0
//Attention: In order to analysis system, MEDIA debug shouldn't close!!!!
#define D_DEBUG_MEDIA                1	/* open */
#define D_DEBUG_MEDIA_DRV        0      /* open */
#define D_DEBUG_LOADER              0
#define D_DEBUG_DVD                  	0
#define D_DEBUG_CANBUS             	1

#define D_DEBUG_SOURCE              1

#define D_DEBUG_EEP                  	1
#define D_DEBUG_DISC                 	0
#define D_DEBUG_MULT			1
#define D_DEBUG_AMP			0		/*Amplifier debug switch */
#define D_DEBUG_KEYTEST             0
#define D_DEBUG_TESTCASE		 0
#define D_DEBUG_UDS_DTC             0
#define D_DEBUG_OSD                          0
#define D_DEBUG_8836_Upgrade        0
#define D_DEBUG_Camera                  1
/*******use CAN BUS channel to transmit data*******************************/
#define CAN_DEBUG_AUDIO		0
/**************************************************************************/

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//#define D_BT_CSR
#define   D_CODE_FOR_JX
#define   D_VOL_CHANA  //keilee20140710
#define D_TW8836_I2C0_EN
#define USB_MODE_HOST		1
#define USB_MODE_DEVICE		0
#define USB_MODE_DEFAULT      USB_MODE_HOST			// Default USB Mode

//...................................................................................................
//2 Tuner Function Select Definitions : Start
typedef enum TUNER_MODULE_ENUM
{
    TUNER_MODULE_NULL = 0,
    TUNER_MODULE_TEF6635,    
    TUNER_MODULE_TEF6638,
    TUNER_MODULE_SAF775X,
    TUNER_MODULE_TDA7705,
    TUNER_MODULE_SI475X,
}tuner_module_enum;

// Two Tuner Module Supported
#define D_TUNER_MODULE_HERO        1    // Hero is Used 

#define D_TUNER_SEEK_A_CIRCLE    //Seek A Circle
#define D_TUNER_PSCAN_CURRENT_BAND    //Preset Scan: only scan currently band's preset
#define D_TUNER_AMS_CURRENT_BAND    //AMS: only auto store for currently band
//#define D_VSCAN_QUEUE_BASE_FS        //Valid Scan: Queue Valid Station base on Field Strength
#define D_VSCAN_QUEUE_BASE_ORDER        //Valid Scan: QUeue Valid Station base on order(from small station to big station)

#define D_TMC
#define D_TMC_MODULE_700X
#define D_TUNER_LIST		// Use LIST to send radio station.
#define D_TUNER_SCANBREAK


//2 Tuner Function Select Definitions : End
//....................................................................................................


//....................................................................................................
//3 Audio Function Selection Definitions:Start

//ASP Selection
#define D_AUDIO_ASP_HERO        1    // Tef6638 is Used 

#ifdef D_AUDIO_ASP_HERO
//#define D_HERO_V03 1        //Hero Version
#endif


//Audio Switch Selection

//Amp Selection
#define D_AMP_TDA7388   //  C
//#define D_AMP_TDF8546  //  A
//#define D_AMP_TDA75610


//#define D_ILL_ADC_CHECK   //ILL ADC CHECK snake20160822

#define D_REVERSV_FAST_ALL  //仅仅使用快速倒车...不区分快速倒车和正常倒车....snake20160906

#define D_TFT_OPEN_GRADIENT  //snake20160909  开屏使用渐变的方式...

#define D_TONE_EQ   1   //EQ Preset realized by Tone,  especially for JX
#define D_TUNER_EQ    //收音的音效单独设置  snake20160905

#define D_ILL_WAKEUP  //snake20161102 小灯唤醒主机
#define D_AUX_EOL     //AUX使用下线配置...

//3 Audio Function Selection Definitions:End
//....................................................................................................


//....................................................................................................
//3 Video Function Selection Definitions:Start

//#define D_VIDEO_SWITCH_FMS6501    1    //Fms6501 as the second switch
#define D_VIDEO_SWITCH_TW8836        //TW6638 as the second switch
#define D_VIDEO_SWITCH_ADI7186
//3 Video Function Selection Definitions:End
//....................................................................................................
#endif
