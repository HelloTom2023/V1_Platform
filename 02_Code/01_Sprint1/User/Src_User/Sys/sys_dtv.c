#define _DTV_C_
#include "..\config\inc.h"

#pragma section data "no_init" begin  

tSOURCE l_tSourceDTV;
#pragma section data "no_init" end
void SRC_DTVStart(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	PM_UnitPowerSet(PM_UNIT_DTV,ON);
}


void SRC_DTVStop(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	//PM_UnitPowerSet(PM_UNIT_DTV,OFF);
}

/**********************************************************
 * @function    SRC_DTVGloableMsgHandler
 * @brief      Message Handler
 * @param      NULL
 * @retval     NULL
 **********************************************************/
eSOURCE_MSG_RETURN SRC_DTVGloableMsgHandler(eSOURCE_TYPE eSrcType,tMSG_BUF* p_tMsg)
{
    	uint16_t Op = p_tMsg->iSid;
	uint8_t re = SRC_MSG_IGNORE;

	TEST(_T("DTV MSG:%x,%x,%x ",p_tMsg->Id,Op, p_tMsg->uData.a_cData[0]));
	switch(p_tMsg->Id)  
	{
	case MS_INPUT_KEY:
	case MS_INPUT_FIR:
	case MS_INPUT_RIR:
		#if 0
		switch(p_tMsg->uData.a_cData[0])
		{
		#ifdef CAN_INNER_ENABLE
		case CK_SEEK_DOWN:		/*PRE STATION */
		case CK_PRE:
			if((Op == OP_KEY_ACTION_SP||Op == OP_KEY_ACTION_LSP))
			{
				CANbus_InnerWriteDtvCmd(0x04);
			}
			re = TRUE;
			break;
		case CK_SEEK_UP:  		/* NEXT STATION */
		case CK_NEXT  :
			if((Op == OP_KEY_ACTION_SP||Op == OP_KEY_ACTION_LSP))
			{
				CANbus_InnerWriteDtvCmd(0x03);
			}
			re = TRUE;
			break;
		#endif
		default:
			break;
		}
		#else
		#endif
		break;
	case MS_PM_STATE:
		switch(Op)
		{
		case OP_PM_STATE_ON:
		case OP_PM_STATE_STANDBY:
			PM_UnitPowerSet(PM_UNIT_DTV,ON);
			break;
			
		case OP_PM_STATE_WAIT_SLEEP: //Do Nothing...
			break;
			
		default:
			PM_UnitPowerSet(PM_UNIT_DTV,OFF);
			break;
		}
		break;
	}
	return re;
}


eSOURCE_MSG_RETURN  SRC_DTVOption(eSOURCE_TYPE eSrcType,tMSG_BUF* p_tMsg)
{
    //hmi_printf(_T("-dtv-eSrcType:%d,%d,p_tMsg:%d 0x%x,a_cData:%d,%d,%d,%d\n",eSrcType,SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME)->eSrcType,p_tMsg->Id,p_tMsg->iSid,p_tMsg->uData.a_cData[0] ,p_tMsg->uData.a_cData[1],p_tMsg->uData.a_cData[2],p_tMsg->uData.a_cData[3] ));
    switch(p_tMsg->Id)
    {
	case MS_SRC_SET_FRONT_UIID:
			//if(p_tMsg->iSid == SRC_TYPE_DTV)
			{
				Video_SetChannel(SRC_ZONE_REAR,SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME),0);
			}
		break;
	case MS_PM_STATE:
            switch(p_tMsg->iSid)
            {
                case OP_PM_STATE_ON:
                    _SendMsgToHMI(MS_SYS_VIDEO_STATE,OP_DEV_STATE_NORMAL,NULL);
                     break;
               case OP_PM_STATE_STANDBY:
                    break;
                    
                case OP_PM_STATE_WAIT_SLEEP:
                    _SendMsgToVideo(MS_VIDEO_SET_OCH,SRC_TYPE_NUM,0);		
                   if(NULL != SRC_GetCurrentSrcInList(SRC_LIST_REAR))
                    Video_SetChannel(SRC_ZONE_REAR,SRC_GetCurrentSrcInList(SRC_LIST_TOP),0);
                    break;
                    
                default:
                    break;
            }
        	break;
        case MS_SYS_APU_INFO:
		if((p_tMsg->iSid == OP_DEV_STATE_NORMAL)&&(SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME)->eSrcType == SRC_TYPE_DTV))
                 Video_SetChannel(SRC_ZONE_REAR,SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME),0);
		break;
	default:
		break;
    }
   return 0;
}


const tSOURCE_CTRL_BLOCK lc_tSrcDTVAttri = 
{

    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    SRC_DTVStart,   /*p_fStart*/
    SRC_DTVStop,   /*p_fStop*/
    SRC_DTVGloableMsgHandler,   /*p_fSrcMsgHandle*/
    SRC_DTVOption,   /*p_fOption*/
};
#define _DTV_FLAG_   la_cSrcFlagDefault[SRC_TYPE_DTV]

void DTV_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceDTV,SOURCE_DTV,SRC_TYPE_DTV,"DTV",&lc_tSrcDTVAttri,SRC_PRI_NORMAL,_DTV_FLAG_,NULL);
}

