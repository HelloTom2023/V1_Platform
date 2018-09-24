#define _DISC_C_
#include "..\config\inc.h"

#pragma section data "no_init" begin  
tSOURCE tSourceCdBox;
tSOURCE tSourceDisc;
tSOURCE tSourceDiscAudio;
tSOURCE tSourceDiscVideo;
#pragma section data "no_init" end

uint8_t SRC_DiscIsValid(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
      return VALID;
}


eSOURCE_MSG_RETURN SRC_DiscOption(eSOURCE_TYPE eSrcType,tMSG_BUF* p_tMsg)
{
    switch(p_tMsg->Id)
    {
        case MS_SYS_IO_INFO:
        break;
	 case MS_PM_STATE:
            switch(p_tMsg->iSid)
            {
                case OP_PM_STATE_STANDBY:
                case OP_PM_STATE_ON:
                case OP_PM_STATE_WAIT_SLEEP:
                    IO_Set(IO_IDX_DVD_POWER,PIN_OUTPUT,VALID);  
			//IO_Set(IO_IDX_DVD_RESET,PIN_OUTPUT,INVALID);  
			src_printf(_T("Sys_Disc Power ON\n"));
                	break;
                default:
			IO_Set(IO_IDX_DVD_POWER,PIN_OUTPUT,INVALID);  
			//IO_Set(IO_IDX_DVD_RESET,PIN_OUTPUT,VALID); 
			src_printf(_T("Sys_Disc Power OFF\n"));
                	break;
            }
		break;
	default:
		break;
    }
    
    return 0;
}

/**********************************************************
 * @function    Dvd_Task
 * @brief      A Periodic task for Tuner module
 * @param      EVENT Evt
 *                 eTASK_STATE eState
 * @retval     NULL
 **********************************************************/
void Dvd_Task(eSOURCE_TYPE eType,EVENT Evt, eTASK_STATE eState)
{
    if(Evt & EVT_COLD_INIT)    //Cold Start, Reset Parameters
    {

    }

    if(Evt & EVT_WARM_INIT)    //Warm Start, Initialize Parameters
    {

    }
    
    if(Evt & EVT_TASK_TICK_READY)
    {
    }
    
    switch(eState)
    {
        case TASK_STATE_READY:

            break;

        case TASK_STATE_RUNNING:

            break;

        case TASK_STATE_STOP:

            break;    
    }
}


uint8_t l_tDiscSeriesRunFlag;
tSOURCE l_tSourceDisc;
tSOURCE l_tSourceDiscAudio;
tSOURCE l_tSourceDiscVideo;

const tSOURCE_CTRL_BLOCK lc_tSrcDiscAttri = 
{
    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    Dvd_Task,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    NULL,   /*p_fSrcMsgHandle*/
    SRC_DiscOption,   /*p_fOption*/
};
 
#define _DISCAUDIO_FLAG_  la_cSrcFlagDefault[SRC_TYPE_DISC_AUDIO]
#define _DISCVIDEO_FLAG_  la_cSrcFlagDefault[SRC_TYPE_DISC_VIDEO]
#define _DISC_FLAG_       la_cSrcFlagDefault[SRC_TYPE_DVD]
#define _CDBOX_FLAG_       la_cSrcFlagDefault[SRC_TYPE_CDBOX]

void Dvd_CreateSrc(void)
{
    (void)SRC_Create(&tSourceDiscAudio,SOURCE_DISC_AUDIO,SRC_TYPE_DISC_AUDIO,"DISC AUDIO",&lc_tSrcDiscAttri,SRC_PRI_NORMAL,_DISCAUDIO_FLAG_,&l_tDiscSeriesRunFlag);
    (void)SRC_Create(&tSourceDiscVideo,SOURCE_DISC_VIDEO,SRC_TYPE_DISC_VIDEO,"DISC VIDEO",&lc_tSrcDiscAttri,SRC_PRI_NORMAL,_DISCVIDEO_FLAG_,&l_tDiscSeriesRunFlag);    
    (void)SRC_Create(&tSourceDisc,SOURCE_DVD,SRC_TYPE_DVD,"DISC",&lc_tSrcDiscAttri,SRC_PRI_NORMAL,_DISC_FLAG_,&l_tDiscSeriesRunFlag);
    (void)SRC_Create(&tSourceCdBox,SOURCE_CDBOX,SRC_TYPE_CDBOX,"CD-BOX",&lc_tSrcDiscAttri,SRC_PRI_NORMAL,_CDBOX_FLAG_,&l_tDiscSeriesRunFlag);
}

