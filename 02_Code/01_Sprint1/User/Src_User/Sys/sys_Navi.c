#define _NAVI_C_
#include "..\config\inc.h"

uint8_t l_cNaviRunflag;

#pragma section data "no_init" begin  

tSOURCE l_tSourceNavi;
tSOURCE l_tSourceNaviMix;
tSOURCE l_tSourceNaviAudio;
tSOURCE l_tSourceAppTone;
tSOURCE l_tSourceVR;
tSOURCE l_tSourceThirdApp;
#pragma section data "no_init" end


eSOURCE_MSG_RETURN SRC_AppToneMsgHandle(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive)  // xjh modify for note 1 in svn
{
	uint8_t re = SRC_MSG_IGNORE;
	if(!bActive)
		return SRC_MSG_IGNORE;
	return (re);
}


eSOURCE_MSG_RETURN  SRC_AppToneOption(eSOURCE_TYPE eSrcType,tMSG_BUF* p_tMsg)  // xjh modify for note 1 in svn
{
	uint8_t re = SRC_MSG_IGNORE;
	switch(p_tMsg->Id)
	{
		case MS_SRC_SET_TOP_TYPE:
			if(p_tMsg->iSid == SRC_TYPE_APP_TONE)
			{
			   if(3 == p_tMsg->uData.a_cData[0])
				{
				   if(MUTE_ON == sAudio.KeyMuteFlag)
				    {
					 //_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE,0,VOL_TYPE_BT,0,0);
					 sAudio.ForceDeMute = 1;
				    }
				   re = SRC_MSG_ANALYZE;
			   	}
			}
			break;

		default:
			break;
	}
	return re;
}


const tSOURCE_CTRL_BLOCK lc_tSrcNaviAttri = 
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

const tSOURCE_CTRL_BLOCK lc_tSrcAppToneAttri = 
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

#define _NAVI_FLAG_             la_cSrcFlagDefault[SRC_TYPE_NAVI]
#define _NAVIAUDIO_FLAG_        la_cSrcFlagDefault[SRC_TYPE_NAVI_AUDIO]
#define _APP_FLAG_           la_cSrcFlagDefault[SRC_TYPE_THIRD_APP]

void Navi_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceNavi,SOURCE_NAVI,SRC_TYPE_NAVI,"NAVI",&lc_tSrcNaviAttri,SRC_PRI_NORMAL,_NAVI_FLAG_,&l_cNaviRunflag);
    (void)SRC_Create(&l_tSourceNaviMix,SOURCE_NUM,SRC_TYPE_NAVI_MIX,"NAVI",&lc_tSrcNaviAttri,SRC_PRI_NORMAL,0,&l_cNaviRunflag);
    (void)SRC_Create(&l_tSourceNaviAudio,SOURCE_NUM,SRC_TYPE_NAVI_AUDIO,"NAVI AUDIO",NULL,SRC_PRI_NORMAL,_NAVIAUDIO_FLAG_,&l_cNaviRunflag);    
    (void)SRC_Create(&l_tSourceAppTone,SOURCE_TTS,SRC_TYPE_APP_TONE,"APP TONE",NULL,SRC_PRI_NORMAL,_NAVIAUDIO_FLAG_,NULL);    
    (void)SRC_Create(&l_tSourceVR,SOURCE_TTS,SRC_TYPE_VR,"VR",NULL,SRC_PRI_NORMAL,_NAVIAUDIO_FLAG_,NULL);  
    (void)SRC_Create(&l_tSourceThirdApp,SOURCE_THIRD_APP,SRC_TYPE_THIRD_APP,"Third-APP",NULL,SRC_PRI_NORMAL,_APP_FLAG_,NULL);    
}

