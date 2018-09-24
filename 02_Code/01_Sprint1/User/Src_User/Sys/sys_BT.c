#define _BT_C_
#include "..\config\inc.h"

uint8_t SRC_BTPhoneIsValid(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
    return g_tApuDevState.tDevflag.bits.bt;
}

uint8_t SRC_BTMusicIsValid(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
    return g_tApuDevState.tDevflag.bits.bt & 0x02;
}


eSOURCE_MSG_RETURN SRC_PhoneMsgHandle(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive)
{
#if 0
    uint8_t re = SRC_MSG_PROHIBITE;
    if(!bActive)
	return SRC_MSG_IGNORE;
    
    switch(tMsg->Id)  
    {
        case MS_INPUT_KEY:
        case MS_INPUT_FIR:
        case MS_INPUT_RIR:
			switch(tMsg->uData.a_cData[0])
			{
				case CK_VOL_DEC:
				case CK_VOL_INC: 
				case CK_MUTE:
				case CK_POWER:
				case CK_TEL:
				case CK_HANDUP:
				case CK_DISP:
				case CK_MODE:
				case CK_PRE:
				case CK_NEXT:
					re = SRC_MSG_IGNORE;
					break;
				default:    
					break;
			}
			break;
    }

    if(re)
    {
        src_printf(_T("Drop Key:%x,%x,%x\n",tMsg->Id,tMsg->iSid,tMsg->uData.a_cData[0]));
    }
    return (re);
#else
    return SRC_MSG_IGNORE;
#endif
}




uint8_t l_cBTSeriesRunFlag;
#pragma section data "no_init" begin  

tSOURCE l_tSourceBTMusic;
tSOURCE l_tSourceBTPhone;
tSOURCE l_tSource3GPhone;
#pragma section data "no_init" end

const tSOURCE_CTRL_BLOCK lc_tSrcBtMusicAttri = 
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

eSOURCE_MSG_RETURN  SRC_PhoneOption(eSOURCE_TYPE eSrcType,tMSG_BUF* p_tMsg)  /* xjh modify for OS ??D????¡¥¦Ì?¨º¡Ào¨°¨®D¨ª¡§?¡ã¡ê??¨²OS???¡¥o¨®¨¤??¨¤¡Á??¡¥¨¢??¨®o¨®?¦Ì¨ª32?¨º?¨¤??¨¤¨¦¨´¨°? */
{
	uint8_t re = SRC_MSG_IGNORE;

	return re;
}

const tSOURCE_CTRL_BLOCK lc_tSrcBtPhoneAttri = 
{

    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    SRC_PhoneMsgHandle,   /*p_fSrcMsgHandle*/
    SRC_PhoneOption,   /*p_fOption*/
};

const tSOURCE_CTRL_BLOCK lc_tSrc3GPhoneAttri = 
{


    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    SRC_PhoneMsgHandle,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};



#define _BTMUSIC_FLAG_    la_cSrcFlagDefault[SRC_TYPE_BT_MUSIC]
#define _BTPHONE_FLAG_    la_cSrcFlagDefault[SRC_TYPE_BT_PHONE]
#define _3GPHONE_FLAG_    la_cSrcFlagDefault[SRC_TYPE_3G_PHONE]


void BT_CreateSrc(void)
{
    SRC_Create(&l_tSourceBTMusic,SOURCE_BT_MUSIC,SRC_TYPE_BT_MUSIC,"BT Music",&lc_tSrcBtMusicAttri,SRC_PRI_NORMAL,_BTMUSIC_FLAG_,&l_cBTSeriesRunFlag);
    SRC_Create(&l_tSourceBTPhone,SOURCE_BT,SRC_TYPE_BT_PHONE,"BT PHONE",&lc_tSrcBtPhoneAttri,SRC_PRI_BT,_BTPHONE_FLAG_,&l_cBTSeriesRunFlag);
    SRC_Create(&l_tSource3GPhone,SOURCE_BT,SRC_TYPE_3G_PHONE,"3G PHONE",&lc_tSrc3GPhoneAttri,SRC_PRI_BT,_3GPHONE_FLAG_,NULL);
}

