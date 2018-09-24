#pragma section data "no_init" begin  
tSOURCE l_tSourceAVOff;
tSOURCE l_tSourceSleep;
tSOURCE l_tSourceRearOff;
tSOURCE l_tSourceStdby; 
tSOURCE l_tSourceLOGO;

#pragma section data "no_init" end

eSOURCE_MSG_RETURN SRC_OffSeries_MsgFilter(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive)
{
#if 0
    eSOURCE_MSG_RETURN re = SRC_MSG_IGNORE;
    uint16_t MsgSrc = tMsg->Id;
    uint16_t Op = tMsg->iSid;
    uint8_t Key = tMsg->uData.a_cData[0];

    if(!bActive)
		return SRC_MSG_IGNORE;
    

    if(eZone == SRC_ZONE_FRONT)
    {
        if((MsgSrc == MS_INPUT_KEY || MsgSrc == MS_INPUT_FIR))
        {
            if(SRC_TYPE_AVOFF == eSrcType)
            {
                	re = SRC_MSG_PROHIBITE;
              
                    if(Key == CK_POWER|| 
			   Key == CK_EJECT ||
			   Key == CK_DISP ||
			   Key == CK_MODE)
                    {
                       re = SRC_MSG_IGNORE;
                	}
                
            }
            else if(SRC_TYPE_SYS_STDBY == eSrcType)
            {
                re = SRC_MSG_PROHIBITE;
                if(Key == CK_POWER||
			Key == CK_EJECT)
                {
                    re = SRC_MSG_IGNORE;
                }
            }
            else if(SRC_TYPE_SLEEP == eSrcType)
            {
                re = SRC_MSG_PROHIBITE;
                if(Key == CK_POWER)
                {
                    re = SRC_MSG_IGNORE;
                }
            }
        }
    }
    return re ;
#else
	return SRC_MSG_IGNORE;
#endif
}

void SRC_AvOffStart(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	if(SRC_ZONE_FRONT == eZone)
	{
		src_printf(_T("Start AVOFF\n"));
		_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_APP_TONE,0);
		SysWorkStatusGrp.SysApuStandyMode = 1;

             if(sAudio.MixStatus & MIX_STATUS_NAVI)
            {
                Audio_MixQueueIn(SRC_TYPE_NAVI_AUDIO,MIX_TYPE_OFF);		
            }
			 IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,0);//snake20160928
	}
}


void SRC_AvOffStop(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
    if(SRC_ZONE_FRONT == eZone)
    {
        src_printf(_T("Exit AVOFF\n"));
		SysWorkStatusGrp.SysApuStandyMode = 0;
		if(sAudio.KeyMuteFlag & 0x01)
		{
			_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_MUTE,MUTE_OFF|SRC_TYPE_AVOFF,0,0,0);
		}
        _SendMsgToHMI(MS_SRC_SET_FRONT_TYPE,SRC_TYPE_AVOFF,FALSE);
       Audio_VariableCheck(); 
	   if(IO_Get(IO_IDX_ILL_DET,PIN_INPUT, FALSE))//snake20160928
	   	{
			IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,8);
	   	}
	   else
	   	{
			IO_Set(IO_IDX_PANEL_LED1,PIN_OUTPUT,95);
	   	}
    }
} 


const tSOURCE_CTRL_BLOCK lc_tSrcAVOffAttri = 
{
    
    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/
    SRC_AvOffStart,   /*p_fStart*/
    SRC_AvOffStop,   /*p_fStop*/
    SRC_OffSeries_MsgFilter,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};


const tSOURCE_CTRL_BLOCK lc_tSrcSleepAttri = 
{


    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    SRC_OffSeries_MsgFilter,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};




const tSOURCE_CTRL_BLOCK lc_tSrcStdbyAttri = 
{

    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    SRC_OffSeries_MsgFilter,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};



eSOURCE_MSG_RETURN SRC_Logo_MsgFilter(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive)
{
#if 0
	eSOURCE_MSG_RETURN re = SRC_MSG_PROHIBITE;
	
	 if(eZone == SRC_ZONE_FRONT)
	 {
		switch(tMsg->Id)  
		{
		    case MS_INPUT_KEY:
		    case MS_INPUT_FIR:
		        if((tMsg->uData.a_cData[0] == CK_EJECT) ||
			     (tMsg->uData.a_cData[0] == CK_POWER)||
			     (tMsg->uData.a_cData[0] == CK_DISP)||
			      (tMsg->uData.a_cData[0] == CK_MODE))
		        {
		                re = SRC_MSG_IGNORE;
		        }
		    	break;
		    default:
			break;
		}
	 }
    	return re;
#else
	return SRC_MSG_IGNORE;
#endif
}

const tSOURCE_CTRL_BLOCK lc_tSrcLogoAttri = 
{

    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    SRC_Logo_MsgFilter,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};




#define _STDBY_FLAG_     la_cSrcFlagDefault[SRC_TYPE_SYS_STDBY]
#define _AVOFF_FLAG_     la_cSrcFlagDefault[SRC_TYPE_AVOFF]
#define _SLEEP_FLAG_     la_cSrcFlagDefault[SRC_TYPE_SLEEP]
#define _LOGO_FLAG_      la_cSrcFlagDefault[SRC_TYPE_LOGO]


void AVOFF_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceStdby,SOURCE_NUM,SRC_TYPE_SYS_STDBY,"StandBy",&lc_tSrcStdbyAttri,SRC_PRI_SYS_STDBY,_STDBY_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceAVOff,SOURCE_AVOFF,SRC_TYPE_AVOFF,"AV OFF",&lc_tSrcAVOffAttri,SRC_PRI_NUM,_AVOFF_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceRearOff,SOURCE_NUM,SRC_TYPE_REAR_OFF,"RearOff",&lc_tSrcSleepAttri,SRC_PRI_TOP,_SLEEP_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceSleep,SOURCE_NUM,SRC_TYPE_SLEEP,"Sleep",&lc_tSrcSleepAttri,SRC_PRI_TOP,_SLEEP_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceLOGO,SOURCE_NUM,SRC_TYPE_LOGO,"LOGO",&lc_tSrcLogoAttri,SRC_PRI_LOGO,_LOGO_FLAG_,NULL);
}


