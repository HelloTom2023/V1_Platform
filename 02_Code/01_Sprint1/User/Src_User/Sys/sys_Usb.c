#define _USB_C_
#include "..\config\inc.h"


uint8_t l_cUsbSeriesRunFlag;
#pragma section data "no_init" begin  

tSOURCE l_tSourceUsbAudio;
tSOURCE l_tSourceUsbVideo;
tSOURCE l_tSourceUsbImage;
tSOURCE l_tSourceUsb;
#pragma section data "no_init" end 


const tSOURCE_CTRL_BLOCK lc_tSrcUsbAttri = 
{
    
    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    NULL,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};


#define _USBVIDEO_FLAG_    la_cSrcFlagDefault[SRC_TYPE_USB_VIDEO]
#define _USBAUDIO_FLAG_    la_cSrcFlagDefault[SRC_TYPE_USB_AUDIO]
#define _USBIMG_FLAG_      la_cSrcFlagDefault[SRC_TYPE_USB_IMAGE]
#define _USB_FLAG_         la_cSrcFlagDefault[SRC_TYPE_USB]
 
void USB_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceUsbVideo,SOURCE_USB_VIDEO,SRC_TYPE_USB_VIDEO,"USB Video",&lc_tSrcUsbAttri,SRC_PRI_NORMAL,_USBVIDEO_FLAG_,&l_cUsbSeriesRunFlag);
    (void)SRC_Create(&l_tSourceUsbAudio,SOURCE_USB_AUDIO,SRC_TYPE_USB_AUDIO,"USB Audio",&lc_tSrcUsbAttri,SRC_PRI_NORMAL,_USBAUDIO_FLAG_,&l_cUsbSeriesRunFlag);
    (void)SRC_Create(&l_tSourceUsbImage,SOURCE_USB_IMAGE,SRC_TYPE_USB_IMAGE,"USB Image",&lc_tSrcUsbAttri,SRC_PRI_NORMAL,_USBIMG_FLAG_,&l_cUsbSeriesRunFlag);
    (void)SRC_Create(&l_tSourceUsb,SOURCE_USB,SRC_TYPE_USB,"USB",&lc_tSrcUsbAttri,SRC_PRI_NORMAL,_USB_FLAG_,&l_cUsbSeriesRunFlag);
}




uint8_t l_cSDSeriesRunFlag;
#pragma section data "no_init" begin  

tSOURCE l_tSourceSDAudio;
tSOURCE l_tSourceSDVideo;
tSOURCE l_tSourceSDImage;
tSOURCE l_tSourceSD;
#pragma section data "no_init" end


const tSOURCE_CTRL_BLOCK lc_tSrcSDAttri = 
{
  
    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    NULL,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};


#define _SDVIDEO_FLAG_  la_cSrcFlagDefault[SRC_TYPE_SD_VIDEO]
#define _SDAUDIO_FLAG_  la_cSrcFlagDefault[SRC_TYPE_SD_AUDIO]
#define _SDIMG_FLAG_    la_cSrcFlagDefault[SRC_TYPE_SD_IMAGE]
#define _SD_FLAG_       la_cSrcFlagDefault[SRC_TYPE_SD]

void SD_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceSDAudio,SOURCE_SD_AUDIO,SRC_TYPE_SD_AUDIO,"SD AUDIO",&lc_tSrcSDAttri,SRC_PRI_NORMAL,_SDAUDIO_FLAG_,&l_cSDSeriesRunFlag);
    (void)SRC_Create(&l_tSourceSDVideo,SOURCE_SD_VIDEO,SRC_TYPE_SD_VIDEO,"SD VIDEO",&lc_tSrcSDAttri,SRC_PRI_NORMAL,_SDVIDEO_FLAG_,&l_cSDSeriesRunFlag);
    (void)SRC_Create(&l_tSourceSDImage,SOURCE_SD_IMAGE,SRC_TYPE_SD_IMAGE,"SD IMAGE",&lc_tSrcSDAttri,SRC_PRI_NORMAL,_SDIMG_FLAG_,&l_cSDSeriesRunFlag);
    (void)SRC_Create(&l_tSourceSD,SOURCE_SD,SRC_TYPE_SD,"SD",&lc_tSrcSDAttri,SRC_PRI_NORMAL,_SD_FLAG_,&l_cSDSeriesRunFlag);
}




