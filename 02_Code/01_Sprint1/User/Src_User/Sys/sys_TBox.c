#define _TBOX_C_
#include "..\config\inc.h"

typedef struct
{
	uint8_t SysMuteState		:1;
	uint8_t TboxWorkState	:2;	/*0- unwork, 1-work*/
	uint8_t Reserved			:5;
}TboxStateStruct;

TboxStateStruct   TboxStateInfo;

void SRC_TboxInit(eSOURCE_TYPE eType)
{
	TboxStateInfo.SysMuteState = 0;
	TboxStateInfo.TboxWorkState = 0;
}
void SRC_TboxStart(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	//TEST(_T("TboxStart:%d, %d ",eSrcType,eZone));
	TboxStateInfo.TboxWorkState = 1;
	/*next line: when Tbox start, exit navi audio , 2014-12-16 */
	_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MIX_REQ,SRC_TYPE_NAVI_AUDIO,0,0,0);
	if(g_tMcuDevState.uIOState.bits.MuteOn)
	{
		_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE,0,0,0,0);	
		TboxStateInfo.SysMuteState = 1;
	}
	else
	{
		TboxStateInfo.SysMuteState = 0;
	}
}

void SRC_TboxStop(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{	
	//TEST(_T("TboxStop:%d, %d ",eSrcType,eZone));
	if((TboxStateInfo.TboxWorkState==1)&&(TboxStateInfo.SysMuteState))
	{
		TboxStateInfo.SysMuteState = 0;
		_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE,0,0,0,0);
	}
	TboxStateInfo.TboxWorkState = 0;
}

eSOURCE_MSG_RETURN SRC_TboxMsgHandle(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive)
{
    uint8_t re = SRC_MSG_IGNORE;
    if(!bActive)
		return SRC_MSG_IGNORE;
    switch(tMsg->Id)  
    {
        case MS_INPUT_KEY:
        case MS_INPUT_FIR:
        case MS_INPUT_RIR:
		/*switch(tMsg->uData.a_cData[0])
		{
		case CK_MUTE: 
		case CK_VOL_DEC: 
		case CK_VOL_INC: 
		case CK_DISP:
			re = FALSE;
			break;
		default:
			break;
		}*/
            	break;
	 default:
		break;
    }
    return (re);
}

uint8_t l_cTboxSeriesRunFlag;
tSOURCE l_tSourceTbox;

const tSOURCE_CTRL_BLOCK lc_tSrcTboxAttri = 
{
    /*function*/
    SRC_TboxInit,    /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    SRC_TboxStart,   /*p_fStart*/
    SRC_TboxStop,   /*p_fStop*/
    SRC_TboxMsgHandle,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};

#define _TBOX_FLAG_    la_cSrcFlagDefault[SRC_TYPE_CAR_TBOX]

void Tbox_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceTbox,SOURCE_TBOX,SRC_TYPE_CAR_TBOX,"Tbox",&lc_tSrcTboxAttri,SRC_PRI_TBOX,_TBOX_FLAG_,&l_cTboxSeriesRunFlag);
}

