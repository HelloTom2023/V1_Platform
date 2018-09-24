
#define _SRC_C_
#include "..\..\..\User\src_user\config\inc.h"
//#include "..\..\..\..\Code_user\User\src_user\config\inc.h"

#pragma pack(1)
typedef struct {
    eSOURCE_SYS_STATE eState;
    uint8_t cTimer;
    union{
        struct{
            bit_t bUiStart  :1;
            bit_t bAudStart :1;
            bit_t bVidStart :1;
        }field;
        uint8_t byte;
    }uAVFlag;
}tSOURCE_MEM;


tSOURCE_MEM l_tSrcCB;

#pragma pack(1)
typedef union{
    tSOURCE* p_tArray[SRC_LIST_NUM - 1];
    struct{
        tSOURCE*  p_tTop;
        tSOURCE*  p_tFloat;
        tSOURCE*  p_tRun;
        tSOURCE*  p_tRear;
    }tBlock;
}uSRC_LIST_BLOCK;

#pragma pack(1)

typedef struct{  
   tSOURCE*        p_tFrontAudSrc;
   tSOURCE*        p_tFrontVidSrc;
   tSOURCE*        p_tRearAudSrc;
   tSOURCE*        p_tRearVidSrc;
   tSOURCE*  		p_tReqFrontSrc;
   tSOURCE*  		p_tReqRearSrc;
}tSYS_SRC_STR;

tSYS_SRC_STR	SysSrcStateStruct;
MEM_SOURCE    SysMemSource;
/*******************************************************************************
*Source switch fuction
*******************************************************************************/
void SRC_Change(eSOURCE_ZONE eZone,tSOURCE* p_tTagSrc)
{   
    if(NULL == p_tTagSrc)
		p_tTagSrc = SRC_GetSrcBlockBaseType(SRC_TYPE_SLEEP,SRC_LIST_SYSTEM);
    
    
    if( SRC_ZONE_FRONT == eZone)
    {
        if(p_tTagSrc->tFlag.field.bFloat)
        {
            SRC_OperateSrcList(SRC_LIST_FLOAT,p_tTagSrc,TRUE);
        }
        else
        {
            SRC_OperateSrcList(SRC_LIST_RUNTIME,p_tTagSrc,TRUE);
        }
    }
    else if(p_tTagSrc && p_tTagSrc->tFlag.field.bRearEn)
    {
        SRC_OperateSrcList(SRC_LIST_REAR,p_tTagSrc,TRUE);
    }
}



void SRC_ChangeBaseID(eSOURCE_ZONE eZone,eSOURCE_ID eSrcID)
{
    tSOURCE* p_tTagSrc ;
    if(eSrcID >= SOURCE_NUM)
		p_tTagSrc = NULL;
    else 
		p_tTagSrc = SRC_GetSysSrcBaseID(eSrcID);
    SRC_Change(eZone,p_tTagSrc);
}

void SRC_ChangeBaseType(eSOURCE_ZONE eZone,eSOURCE_TYPE eSrcType)
{
    tSOURCE* p_tTagSrc ;
    if(eSrcType >= SRC_TYPE_NUM)
		p_tTagSrc = NULL;
    else 
		p_tTagSrc = SRC_GetSysSrcBaseType(eSrcType);
    SRC_Change(eZone,p_tTagSrc);
}



void SRC_OperateListSrcBaseType(eSOURCE_TYPE eSrcType,eSOURCE_LIST_TYPE eListType,bool bInsert)
{
    tSOURCE* p_tSrc = SRC_GetSysSrcBaseType(eSrcType);		//在列表中找到基于此TYPE的源
    if(p_tSrc)
    {
        SRC_OperateSrcList(eListType,p_tSrc,bInsert);
    }
}
/******************************************************************************/
void SRC_Start(void)
{

	tSOURCE* p_tSrc = NULL;

	SRC_ClearSrcList(SRC_LIST_TOP);
	SRC_ClearSrcList(SRC_LIST_FLOAT);

	p_tSrc = SRC_GetSrcBlockBaseType(SRC_TYPE_LOGO,SRC_LIST_SYSTEM);
	SRC_OperateSrcList(SRC_LIST_TOP,p_tSrc,TRUE);
	p_tSrc = SRC_GetSrcBlockBaseType(SRC_TYPE_REAR_OFF,SRC_LIST_SYSTEM);
	SRC_OperateSrcList(SRC_LIST_REAR,p_tSrc,TRUE);
}

tSOURCE* SRC_GetFirstSrcBaseFlag(eSOURCE_LIST_TYPE eType,uint16_t iFlag)
{
    tSOURCE* p_tReSrc = NULL;
    
    tNODE* p_tSrcListNode = SRC_GetListHeadNode(eType);
    while(p_tSrcListNode)
    {
        tSOURCE* p_tListSrc = (tSOURCE*)(p_tSrcListNode->p_tElement);
        uint8_t  cFlag  = 0;
        if(p_tListSrc)
		cFlag = p_tListSrc->tFlag.byte;
        
        if(cFlag & iFlag)
        {
            p_tReSrc = p_tListSrc;
            break;
        }
        p_tSrcListNode = p_tSrcListNode->p_tNext;
    }
    return p_tReSrc;
}

tSOURCE *SRC_GetValidAudioSource(void)
{
	tSOURCE* pSrc;

	pSrc = SRC_GetFirstSrcBaseFlag(SRC_LIST_TOP, B_SRC_AUDVALID);

	if(pSrc == NULL)
	{
		pSrc = SRC_GetFirstSrcBaseFlag(SRC_LIST_FLOAT, B_SRC_AUDVALID);

		if(pSrc == NULL)
		{
			pSrc = SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME);
		}
	}
	return pSrc;
}

tSOURCE *SRC_GetValidVideoSource(void)
{
	tSOURCE* pSrc;

	pSrc = SRC_GetFirstSrcBaseFlag(SRC_LIST_TOP, B_SRC_VIDVALID);

	if(pSrc == NULL)
	{
		pSrc = SRC_GetFirstSrcBaseFlag(SRC_LIST_FLOAT, B_SRC_VIDVALID);

		if(pSrc == NULL)
		{
			pSrc = SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME);
		}
	}
	return pSrc;
}

void SRC_ScanAudioVideo(void)						    
{  
	tSYS_SRC_STR *p_tSysSrcState =  &SysSrcStateStruct;
	tSOURCE* pSrc;
	tSOURCE* pFrontAudSrc = NULL;

	if(l_tSrcCB.uAVFlag.field.bAudStart)
	{
		//Front Audio Change
		
		pFrontAudSrc = SRC_GetValidAudioSource();
		if(pFrontAudSrc)
		{
			if((pFrontAudSrc != p_tSysSrcState->p_tFrontAudSrc) &&(pFrontAudSrc->tFlag.field.bAudValid) )
			{
				if((l_tSrcCB.uAVFlag.field.bUiStart || pSrc->tFlag.field.bBootStart))
				{
					p_tSysSrcState->p_tFrontAudSrc = pFrontAudSrc;
					Audio_SetChannel(SRC_ZONE_FRONT,pFrontAudSrc,0);
				}
			}
		}
		else if(p_tSysSrcState->p_tFrontAudSrc != NULL)
		{
			p_tSysSrcState->p_tFrontAudSrc = NULL;
			Audio_SetChannel(SRC_ZONE_FRONT,NULL,0);
		}
#if 0
		// Rear Audio Change
		if(p_tSysSrcState->p_tReqRearSrc
			&&(p_tSysSrcState->p_tReqRearSrc != p_tSysSrcState->p_tRearAudSrc))
		{
			pSrc = p_tSysSrcState->p_tReqRearSrc;
			if(pSrc->tFlag.field.bAudValid)
			{
				if((l_tSrcCB.uAVFlag.field.bUiStart || pSrc->tFlag.field.bBootStart))
				{
					p_tSysSrcState->p_tRearAudSrc = pSrc;
					Audio_SetChannel(SRC_ZONE_REAR,pSrc,0);
				}
			}
		}
		else if((p_tSysSrcState->p_tReqRearSrc == NULL) &&(p_tSysSrcState->p_tRearAudSrc != NULL))
		{
			p_tSysSrcState->p_tRearAudSrc = NULL;
			Audio_SetChannel(SRC_ZONE_REAR,NULL,0);
		}
#endif
	}
	if(l_tSrcCB.uAVFlag.field.bVidStart)
	{
		//Front Video Change

		tSOURCE*  pFrontVidSrc = SRC_GetValidVideoSource();
		
		if(pFrontVidSrc)
		{
			if((pFrontVidSrc != p_tSysSrcState->p_tFrontVidSrc) && (pFrontVidSrc->tFlag.field.bVidValid))
			{
				p_tSysSrcState->p_tFrontVidSrc = pFrontVidSrc;
				Video_SetChannel(SRC_ZONE_FRONT,pFrontVidSrc,0);
			}
			else
			{
				//snake20161211 增加倒车和盲区切换锁,当切了源,不切通道的时候,将标志位清除...
				if((pFrontVidSrc->eSrcType == SRC_TYPE_CAMERA) 
					&& (SRC_GetSrcBlockBaseType(SRC_TYPE_REVERSE,SRC_LIST_TOP) == NULL) 
					&& (HMIStatusFlag.g_tUpdataReverseParameter))
				{
					HMIStatusFlag.g_tUpdataReverseParameter = 0;
					src_printf(_T("stop SRC_TYPE_REVERSE,clear HMIStatusFlag.g_tUpdataReverseParameter!!\n"));
				}

		 		if((pFrontVidSrc->eSrcType == SRC_TYPE_REVERSE) 
					&& (SRC_GetSrcBlockBaseType(SRC_TYPE_CAMERA,SRC_LIST_TOP) == NULL) 
					&& (HMIStatusFlag.g_tUpdataBlindParameter))
				{
					HMIStatusFlag.g_tUpdataBlindParameter = 0;
					src_printf(_T("stop SRC_TYPE_CAMERA,clear HMIStatusFlag.g_tUpdataBlindParameter!!\n"));
				}   
			}
		}
		else if(p_tSysSrcState->p_tFrontVidSrc != NULL)
		{
			p_tSysSrcState->p_tFrontVidSrc = NULL;
			Video_SetChannel(SRC_ZONE_FRONT,NULL,0);
		}
#if 0
		//Rear Video Change
		if(p_tSysSrcState->p_tReqRearSrc
			&&(p_tSysSrcState->p_tReqRearSrc != p_tSysSrcState->p_tRearVidSrc))
		{
			pSrc = p_tSysSrcState->p_tReqRearSrc;
			//if(pSrc->tFlag.field.bVidValid)
			{
				//if((l_tSrcCB.uAVFlag.field.bUiStart || pSrc->tFlag.field.bBootStart))
				{
					p_tSysSrcState->p_tRearVidSrc = pSrc;
					Video_SetChannel(SRC_ZONE_REAR,pSrc,0);
				}
			}
		}
		else if((p_tSysSrcState->p_tReqRearSrc == NULL) &&(p_tSysSrcState->p_tRearVidSrc != NULL))
		{
			p_tSysSrcState->p_tRearVidSrc = NULL;
			Video_SetChannel(SRC_ZONE_REAR,NULL,0);
		}
#endif
	}
}


void SRC_Scan(void)
{
    uint8_t i;
    tSOURCE* p_tSrc ;
  
    /*Check the top src of every list is valid or invalid*/
    for(i = SRC_LIST_TOP; i < SRC_LIST_SYSTEM; i++)
    {
        
        tNODE* p_tNode = SRC_GetListHeadNode(i);

        while(p_tNode)
        {
            p_tSrc = (tSOURCE*)p_tNode->p_tElement;
            p_tNode = p_tNode->p_tNext;

            if(p_tSrc && p_tSrc->p_tSCB && p_tSrc->p_tSCB->p_fIsValid)
            {
                if(!p_tSrc->p_tSCB->p_fIsValid(p_tSrc->eSrcType,SRC_ZONE_FRONT))
                {
                    /*If src is invalid,delet it from the list ,than get new top to check*/
                    ERROR(_T("Src in ID:%d is invalid in list %d\n",p_tSrc->eSrcID,i));
                    SRC_OperateSrcList(i,p_tSrc,FALSE);
                }
            }
        }
    }

    /*If run and rear list is empty,insert the default source !*/    
    p_tSrc = SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME);
    if(NULL == p_tSrc)
    {
        p_tSrc = SRC_GetSrcBlockBaseType(SRC_TYPE_TUNER,SRC_LIST_SYSTEM);
        SRC_OperateSrcList(SRC_LIST_RUNTIME,p_tSrc,TRUE);
    }
    if(SysMemSource.MediaSource != p_tSrc->eSrcID)
    {
    	SysMemSource.MediaSource = p_tSrc->eSrcID;
	_SendFullMsgToHMI(MS_SRC_SYS_CMD,OP_SRC_SW_START,SRC_ZONE_FRONT,p_tSrc->eSrcID,0,0);
    }

    p_tSrc = SRC_GetCurrentSrcInList(SRC_LIST_REAR);
    if(NULL == p_tSrc)
    {
        p_tSrc = SRC_GetSrcBlockBaseType(SRC_TYPE_REAR_OFF,SRC_LIST_SYSTEM);
        SRC_OperateSrcList(SRC_LIST_REAR,p_tSrc,TRUE);
    }
/*Get Front Request Source */
    p_tSrc = SRC_GetCurrentSrcInList(SRC_LIST_TOP);
    if(p_tSrc == NULL)
    {
	 p_tSrc = SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME);
    }
    SysSrcStateStruct.p_tReqFrontSrc = p_tSrc;
/*Get Rear Request Source */
    p_tSrc = SRC_GetCurrentSrcInList(SRC_LIST_REAR);
    SysSrcStateStruct.p_tReqRearSrc = p_tSrc;

}


/*Src Task in runtime state,sub task msg handle*/
void SRC_SubSystemRunTimeMsgHandle(tMSG_BUF* p_tMsgBuf)
{
    eSOURCE_LIST_TYPE eListType;
    tSOURCE* p_tTmpSrc;

    uint8_t bMsgPrevent = SRC_MSG_IGNORE;
    uint8_t bCheckSrc;
    tNODE* p_tNode = SRC_GetListHeadNode(SRC_LIST_TOP);

   
    for(eListType = SRC_LIST_TOP;eListType < SRC_LIST_REAR;eListType ++)
    {
        bCheckSrc = TRUE;
        while(bCheckSrc)
        {
            bCheckSrc = FALSE;
            if(bMsgPrevent == SRC_MSG_IGNORE)
            {
                
                if(eListType == SRC_LIST_TOP)
                {
                    p_tTmpSrc = NULL;
                    if(p_tNode)
                    {
                        p_tTmpSrc = (tSOURCE*)(p_tNode->p_tElement);
                        p_tNode = p_tNode->p_tNext;
                        bCheckSrc = TRUE;
                    }
                }
                else
                {
                    p_tTmpSrc = SRC_GetCurrentSrcInList(eListType);
                }
		   if(p_tTmpSrc)
                {
                    if(p_tTmpSrc->p_tSCB && p_tTmpSrc->p_tSCB->p_fSrcMsgHandle)
                    {
                    	eSOURCE_TYPE eSrcType = p_tTmpSrc->eSrcType;
				bMsgPrevent = p_tTmpSrc->p_tSCB->p_fSrcMsgHandle(eSrcType,SRC_ZONE_FRONT,p_tMsgBuf,TRUE);

				if(bMsgPrevent != SRC_MSG_IGNORE)
				{
					src_printf(_T("Msg has been dealed by src(type):%x\n",eSrcType));
					_SendMsgToHMI((MS_GLOBAL_SRC_ANALYZE)|(p_tMsgBuf->Id),p_tMsgBuf->iSid,p_tTmpSrc);
				}
				SRC_MsgHandleHook(eSrcType,SRC_ZONE_FRONT,p_tMsgBuf,TRUE);
			}
		   }
                
            }
        }
    }
    
    /*Rear source message handle*/
    p_tTmpSrc = SRC_GetCurrentSrcInList(SRC_LIST_REAR);
    if(p_tTmpSrc && p_tTmpSrc->p_tSCB && p_tTmpSrc->p_tSCB->p_fSrcMsgHandle)
    {
        (void)p_tTmpSrc->p_tSCB->p_fSrcMsgHandle(p_tTmpSrc->eSrcType,SRC_ZONE_REAR,p_tMsgBuf,TRUE);
    }
    
    /*User input message has not been prevented by active source,send back to HMI or drop*/
    if(SRC_MSG_IGNORE == bMsgPrevent)
    { 
        src_printf(_T("Src Msg return to HMI--\n"));
        _SendMsgToHMI((MS_GLOBAL_SRC_DROP)|(p_tMsgBuf->Id),p_tMsgBuf->iSid,p_tMsgBuf->uData.p_cData);
    }
}

void SRC_SubSystemGlobolMsgHandle(tMSG_BUF* p_tMsgBuf)
{
    tNODE* p_tNode = SRC_GetListHeadNode(SRC_LIST_SYSTEM);
    while(p_tNode)
    {
        tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
        if(p_tSrc)
        {
            if(p_tSrc->p_tSCB)
            {
                /*Src Option*/
                if( p_tSrc->p_tSCB->p_fOption)
                {                 
                    (void)p_tSrc->p_tSCB->p_fOption(p_tSrc->eSrcType,p_tMsgBuf);
                }
            }
            
        }
        p_tNode = p_tNode->p_tNext;
	 CLEAR_WATCHDOG();
    }
    
}


void SRC_SubSystemTask(EVENT iEvt,eTASK_STATE eState)
{
    tNODE* p_tNode = SRC_GetListHeadNode(SRC_LIST_SYSTEM);

    /*Scan all source task*/
    while(p_tNode)
    {
        tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);

        if(p_tSrc)
        {
            if(p_tSrc->p_tSCB)
            {
                /*Src sub_task*/
                if(p_tSrc->p_tSCB->p_fTask)
                {                
                    p_tSrc->p_tSCB->p_fTask(p_tSrc->eSrcType,iEvt,eState);                 
                }
            }
        }
        p_tNode = p_tNode->p_tNext;
	 CLEAR_WATCHDOG();
    }
}

void SRC_TestCase(void);
void SRC_SysProc(void)
{
    switch(l_tSrcCB.eState)
    {
        case SRCSYS_RUNNING:
       	SRC_Scan();
		SRC_ScanAudioVideo();
        	break;
        case SRCSYS_WAIT_START:
		SRC_Start();
		l_tSrcCB.eState = SRCSYS_RUNNING;
        	break;
        case SRCSYS_INIT:
		 src_printf(_T("SRCSYS_INIT enter\n"));
            	l_tSrcCB.eState = SRCSYS_WAIT_START;
        	break;
        default:
		break;
    }
	SRC_TestCase();
}



bool SRC_MsgHandle(tMSG_BUF* p_tMsgBuf)
{
    uint8_t bDisTributeMsg = FALSE;
    uint16_t Op = p_tMsgBuf->iSid;
    
    switch(p_tMsgBuf->Id)
    {   
        case MS_SRC_SET_FRONT_UIID:
			src_printf(_T("Src_Msg:id = %x, op = %x\n", p_tMsgBuf->Id, Op));
			SRC_ChangeBaseID(SRC_ZONE_FRONT,(eSOURCE_ID)((uint8_t)Op));
			//取消接收到AVOFF的切源消息的是MUTE,在切通道的时候进行mute...
			// request enter AVOFF source, send message to APU to update POWER on/off state.
			if(SOURCE_AVOFF == (uint8_t)Op && l_tMediaCB.uDevFlag.field.bUnLocked)
			{
				sAudio.KeyMuteState = 1;
				sAudio.bPowerOffMute = 1;
				sAudio.KeyMuteFlag &= (~(MUTE_OFF<< SYSTEM_FRONT));
				sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_ON;
				sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
				sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_HARD_MUTE;
				//Send Feedback to HMI,Update Display Immediately
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);
				_SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_POWEROFF,NULL);

			}
			if(	sAudio.bPowerOffMute
				&&(SOURCE_AVOFF != (uint8_t)Op))	   
			{
				sAudio.KeyMuteState = 0;
				sAudio.bPowerOffMute = 0;	
				sAudio.KeyMuteFlag &= (~(MUTE_ON << SYSTEM_FRONT));
				sAudio.KeyMuteReq[SYSTEM_FRONT] = MUTE_OFF;
				sAudio.KeyMuteDly[SYSTEM_FRONT] = 0;
				sAudio.KeyMuteStep[SYSTEM_FRONT] = AUDIO_MUTE_HARD_UNMUTE;
				//Send Feedback to HMI,Update Display Immediately
				_SendFullMsgToHMI(MS_AUDIO_UPLOAD_INFO,OP_AUDUP_MUTE,sAudio.KeyMuteFlag,SYSTEM_FRONT,0,0);
			}
			
			break;
        case MS_SRC_SET_REAR_UIID:
            SRC_ChangeBaseID(SRC_ZONE_REAR,(eSOURCE_ID)((uint8_t)Op));
        break;
	 case MS_SRC_SET_FLOAT_TYPE:
	 case MS_SRC_SET_TOP_TYPE:
        case MS_SRC_SET_FRONT_TYPE:
        case MS_SRC_SET_REAR_TYPE:
	      src_printf(_T("Src_Msg:id = %x, op = %x\n", p_tMsgBuf->Id, Op));
            SRC_OperateListSrcBaseType((eSOURCE_TYPE)((uint8_t)Op),
                                       (eSOURCE_LIST_TYPE)(p_tMsgBuf->Id - MS_SRC_SET_TOP_TYPE),
                                       (p_tMsgBuf->uData.p_cData != NULL));
	     
        break;
        
        case MS_SRC_SYS_CMD:
        break;
        
        case MS_SYS_APU_INFO:
		if(OP_DEV_STATE_NORMAL== Op)
		{
			if(l_tSrcCB.uAVFlag.field.bUiStart != TRUE)
			{
				l_tSrcCB.uAVFlag.field.bUiStart = TRUE;
				SRC_OperateListSrcBaseType(SRC_TYPE_LOGO,SRC_LIST_TOP,FALSE);
			}
		}
		else if((OP_DEV_STATE_NOCONNECT == Op) ||
			  (OP_DEV_STATE_SLEEP == Op) ||
			  (OP_DEV_STATE_ERR == Op) ||
			  (OP_DEV_STATE_RESET== Op) )
		{
			if(l_tSrcCB.uAVFlag.field.bUiStart == TRUE)
			{
				l_tSrcCB.uAVFlag.field.bUiStart = FALSE;
				l_tSrcCB.eState = SRCSYS_INIT;
			}
		}
		break;
        case MS_SYS_IO_INFO:
        break;
        case MS_SYS_AUDIO_STATE:
            if(OP_DEV_STATE_CONNECTED == Op || OP_DEV_STATE_NORMAL== Op)
            	{
			SysSrcStateStruct.p_tFrontAudSrc = NULL;
			l_tSrcCB.uAVFlag.field.bAudStart = TRUE;
            	}
            else
            	{
		 	l_tSrcCB.uAVFlag.field.bAudStart = FALSE;
            	}
        break;
        case MS_SYS_VIDEO_STATE:
            if(OP_DEV_STATE_CONNECTED == Op || OP_DEV_STATE_NORMAL== Op)
            	{
            		SysSrcStateStruct.p_tFrontVidSrc= NULL;
			l_tSrcCB.uAVFlag.field.bVidStart = TRUE;
		}
            else
            	{
			l_tSrcCB.uAVFlag.field.bVidStart = FALSE;
		}
        break;
        case MS_PM_STATE:
            switch(Op)
            {
                case OP_PM_STATE_STANDBY:
                    if(!OS_TaskIsActive(TASK_ID_SOURCE))
                    {
                        OS_TaskStart(TASK_ID_SOURCE);
                        src_printf(_T("SRC Task Start\n"));
                    }
                break;
                case OP_PM_STATE_ON:
                    if(!OS_TaskIsActive(TASK_ID_SOURCE))
                    {
                        OS_TaskStart(TASK_ID_SOURCE);
                    }
                   SRC_OperateListSrcBaseType(SRC_TYPE_SLEEP,SRC_LIST_REAR,FALSE);
                   SRC_OperateListSrcBaseType(SRC_TYPE_SLEEP,SRC_LIST_TOP,FALSE);
                break;
		   case OP_PM_STATE_BATERR:
                case OP_PM_STATE_WAIT_SLEEP:
                   SRC_OperateListSrcBaseType(SRC_TYPE_SLEEP,SRC_LIST_REAR,TRUE);
                   SRC_OperateListSrcBaseType(SRC_TYPE_SLEEP,SRC_LIST_TOP,TRUE);
                break;
                default:
                    if(OS_TaskIsActive(TASK_ID_SOURCE))
                    {
                        OS_TaskStop(TASK_ID_SOURCE);
                        src_printf(_T("SRC Task Stop\n"));
                    }
                    
                break;
            }
        break;
        case MS_INPUT_KEY:
        case MS_INPUT_SWC:
        case MS_INPUT_FIR:
        case MS_INPUT_BUS:
        case MS_INPUT_UI:
	 case MS_INPUT_TOUCH:
        case MS_SRC_DISTRIBUTE_CMD:
            bDisTributeMsg = TRUE && (l_tSrcCB.eState == SRCSYS_RUNNING);
            break;
    }

    return bDisTributeMsg;
}


typedef struct
{
	uint8_t TestCase;
	uint8_t LastCase;
}SRC_TCASE_STR;
SRC_TCASE_STR		SrcTestCaseStr;

void SRC_TestCase(void)
{
	if(SrcTestCaseStr.LastCase != SrcTestCaseStr.TestCase)
	{
		SrcTestCaseStr.LastCase = SrcTestCaseStr.TestCase;
		switch(SrcTestCaseStr.TestCase)
		{
			case 1:
				SRC_ChangeBaseID(SRC_ZONE_FRONT,SOURCE_TUNER);
				break;
			case 2:
				SRC_ChangeBaseID(SRC_ZONE_FRONT,SOURCE_DVD);
				break;
			case 3:
				 SRC_OperateListSrcBaseType(SRC_TYPE_BT_PHONE,
                                       						SRC_LIST_TOP,1);
				break;
			case 4:
				 SRC_OperateListSrcBaseType(SRC_TYPE_BT_PHONE,
                                       						SRC_LIST_TOP,0);
				break;
			case 5:
				 SRC_OperateListSrcBaseType(SRC_TYPE_CAR_TBOX,
                                       						SRC_LIST_TOP,1);
				break;
			case 6:
				 SRC_OperateListSrcBaseType(SRC_TYPE_CAR_TBOX,
                                       						SRC_LIST_TOP,0);
				break;
			case 7:
				l_tSrcCB.uAVFlag.field.bUiStart = TRUE;
				break;
			default:
				break;
		}
	}
}


#if D_DEBUG_SOURCE && D_PRINT_EN
void SRC_ListInfo(void)
{    
    static uint8_t cTimer;
    if(cTimer ++ > 10)
    {
        tNODE* p_tNode = SRC_GetListHeadNode(SRC_LIST_SYSTEM);
    #if 0
        /*Scan all sourcec task*/
        src_printf(_T("SYS SRC_LIST:\n"));
        while(p_tNode)
        {
            tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
    
            if(p_tSrc)
            {
                src_printf(_T("SRC:%lx ",(uint32_t)p_tSrc));
                src_printf(_T(p_tSrc->p_cName));
                src_printf(_T(" type:%d,id:%d runflag:%x\n",p_tSrc->eSrcType,p_tSrc->eSrcID,*(p_tSrc->p_cRunState)));
            }
            p_tNode = p_tNode->p_tNext;
        }
    #endif
        p_tNode = SRC_GetListHeadNode(SRC_LIST_RUNTIME);
    
        /*Scan all sourcec task*/
        src_printf(_T("RUNTIME SRC_LIST:\n"));
        while(p_tNode)
        {
            tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
    
            if(p_tSrc)
            {
                src_printf(_T("Node:%lx ",(uint32_t)p_tNode));
                src_printf(_T(p_tSrc->p_cName));
                src_printf(_T(" type %d,attr:%x runflag:%x\n",p_tSrc->eSrcType,p_tSrc->tFlag.byte,*(p_tSrc->p_cRunState)));
            }
            p_tNode = p_tNode->p_tNext;
        }

        p_tNode = SRC_GetListHeadNode(SRC_LIST_REAR);
    
        /*Scan all sourcec task*/
        src_printf(_T("REAR SRC_LIST:\n"));
        while(p_tNode)
        {
            tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
    
            if(p_tSrc)
            {
                src_printf(_T("Node:%lx ",(uint32_t)p_tNode));
                src_printf(_T(p_tSrc->p_cName));
                src_printf(_T(" type %d,attr:%x runflag:%x\n",p_tSrc->eSrcType,p_tSrc->tFlag.byte,*(p_tSrc->p_cRunState)));
               
            }
            p_tNode = p_tNode->p_tNext;
        }
    
         p_tNode = SRC_GetListHeadNode(SRC_LIST_FLOAT);
    
        /*Scan all sourcec task*/
        src_printf(_T("FLOAT SRC_LIST:\n"));
        while(p_tNode)
        {
            tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
    
            if(p_tSrc)
            {
                src_printf(_T("Node:%lx ",(uint32_t)p_tNode));
                src_printf(_T(p_tSrc->p_cName));
                src_printf(_T(" type %d,attr:%x runflag:%x\n",p_tSrc->eSrcType,p_tSrc->tFlag.byte,*(p_tSrc->p_cRunState)));
            }
            p_tNode = p_tNode->p_tNext;
        }
    
        p_tNode = SRC_GetListHeadNode(SRC_LIST_TOP);
    
        /*Scan all sourcec task*/
        src_printf(_T("HPRI SRC_LIST:\n"));
        while(p_tNode)
        {
            tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
    
            if(p_tSrc)
            {
                src_printf(_T("Node:%lx ",(uint32_t)p_tNode));
                src_printf(_T(p_tSrc->p_cName));
                src_printf(_T(" type %d,attr:%x runflag:%x\n",p_tSrc->eSrcType,p_tSrc->tFlag.byte,*(p_tSrc->p_cRunState)));
               
            }
            p_tNode = p_tNode->p_tNext;
        }

		src_printf(_T("\n\nReverse_Flag = %d,Blind_Flag = %d,CvbsChannelFlag = %d\n\n",g_tMcuDevState.uIOState.bits.Reverse_Flag,g_tMcuDevState.uDetect.bits.Blind_Flag,g_tMcuDevState.uDetect.bits.CvbsChannelFlag));

        cTimer = 0;
    }
}
#endif



void SRC_Task(EVENT iEvt,eTASK_STATE eState)
{
    tMSG_BUF tMsgBuf;


    if(iEvt & EVT_MSG_READY)
    {
        if(QUE_ERR_NONE == OS_GetMsgDir(&g_tSysSrcTaskCB,&tMsgBuf))
        {
            if(SRC_MsgHandle(&tMsgBuf))
            {
                SRC_SubSystemRunTimeMsgHandle(&tMsgBuf);
            }
            else
            { 
                switch(tMsgBuf.Id)
                {
                    case MS_INPUT_KEY:
                    case MS_INPUT_FIR:
                    case MS_INPUT_RIR:
                    case MS_INPUT_SWC:
                    case MS_INPUT_BUS:
			   _SendMsgToHMI((MS_GLOBAL_SRC_DROP)|(tMsgBuf.Id),tMsgBuf.iSid,tMsgBuf.uData.p_cData);
                    default:
                        SRC_SubSystemGlobolMsgHandle(&tMsgBuf);
                }
            }
        }
    }
    
#if D_DEBUG_SOURCE && D_PRINT_EN //snake20160918
    if(iEvt & EVT_RTC_SECOND)
    {
        SRC_ListInfo();
    }
#endif


    
    switch(eState)
    {
        case TASK_STATE_RUNNING:
            if(iEvt & EVT_TASK_TICK_READY)
            {
                /*Scan proc in a timer tick*/
                if(l_tSrcCB.cTimer)
                {
			l_tSrcCB.cTimer --;
                }
                else 
                {
                    l_tSrcCB.cTimer = _set_timing_xms_base_src_task_tick(8);
                    SRC_SysProc();
                }
            }
            SRC_SubSystemTask(iEvt,eState);
        break;
        case TASK_STATE_READY:
            if(iEvt & EVT_MSG_READY)
            {
                if(tMsgBuf.Id)
                {
                    if(!OS_TaskIsActive(TASK_ID_SOURCE))
                    {
                        OS_TaskStart(TASK_ID_SOURCE);
                        OS_InsertMsgDir(&g_tSysSrcTaskCB,tMsgBuf.Id,tMsgBuf.iSid,tMsgBuf.uData.p_cData,TRUE);
                        src_printf(_T("SRC Task Start\n"));
                    }
                }
            }
        break;
        case TASK_STATE_STOP:
        break;
    }
}

uint8_t SRC_Init(void)
{
    SRC_CoreInit();
    API_MemClear((uint8_t*)&l_tSrcCB,sizeof(tSOURCE_MEM));
    API_MemClear((uint8_t*)&SysSrcStateStruct,sizeof(tSYS_SRC_STR));
    API_MemClear((uint8_t*)&SysMemSource,sizeof(MEM_SOURCE));
    (void)SRC_InitHook();
    return 1;
}


uint8_t SRC_DeInit(void)
{
    tNODE* p_tNode = SRC_GetListHeadNode(SRC_LIST_SYSTEM);
    while(p_tNode)
    {
        tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
        if(p_tSrc&&p_tSrc->p_tSCB)
        {
            /*Src stop*/
            uint8_t* p_cFlag = p_tSrc->p_cRunState;
            if( p_tSrc->p_tSCB->p_fStop && (p_cFlag == NULL || *p_cFlag == 0))
            {                 
                p_tSrc->p_tSCB->p_fStop(p_tSrc->eSrcType,SRC_ZONE_NUM);
            }
            if(p_cFlag)*p_cFlag = 0;
        }
            
            
        p_tNode = p_tNode->p_tNext;
    }

    return 1;
    
}


////////////////////////////////////////////////////////////////////////////////
const tTASK_BLOCK lc_tSrcTaskCB = {
    "SOURCE",
    _SRC_TASK_TICK_,
    _SRC_CORE_TICK_,
    SRC_Task,
    SRC_Init,
    SRC_DeInit,
};

tRING_QUE l_tSrcMsgQue;
tMSG_BUF la_tSrcMsgBuf[D_SRC_MSG_QUE_DEEP];
extern void SRC_CoreColdInit(void);
uint8_t SRC_TaskCreate(void)
{
     SRC_CoreColdInit();
     SRC_CoreInit();
    return OS_TaskCreate(TASK_ID_SOURCE,&g_tSysSrcTaskCB,&lc_tSrcTaskCB,&l_tSrcMsgQue,la_tSrcMsgBuf,D_SRC_MSG_QUE_DEEP);
}





