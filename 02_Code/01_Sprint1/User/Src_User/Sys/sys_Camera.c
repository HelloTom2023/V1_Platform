#define _CAMERA_C_
#include "..\config\inc.h"

#define CAMERA_DELAY 35000  // 70S

#pragma section data "no_init" begin  
tSOURCE l_tSourceRadar;
tSOURCE l_tSourceCamera;
tSOURCE l_tSourceReverse;
#pragma section data "no_init" end  

uint8_t CamClosePwr;
uint16_t CamDelay;
	
void SendParkModeToBus(uint8_t mode)
{
	uint8_t msg[2];
	msg[0] = OP_CAN_RX_VEHICLE_BACKCAR;
	msg[1] = mode;
	CANTask_VehicleMsgHandler(msg);
}

void SendCoordinateToBus(void)
{
	uint8_t msg[5];
	msg[0] = OP_CAN_RX_VEHICLE_AvmSlip;
	msg[1] = ApuTouchInfo.PixX>>8;//x
	msg[2] = ApuTouchInfo.PixX>>0;
	msg[3] = ApuTouchInfo.PixY>>8;//y
	msg[4] = ApuTouchInfo.PixY>>0;
	msg[5] = ApuTouchInfo.State;
	CANTask_VehicleMsgHandler(msg);
}

void SRC_CameraStart(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
    CamClosePwr = 0;
	CamDelay = 0; 
	HMIStatusFlag.g_tBlindStatus = 1;
    PM_UnitPowerSet(PM_UNIT_RADAR,ON);
	g_tMcuDevState.uDetect.bits.Blind_Flag = 1;
	g_tMcuDevState.uDetect.bits.CvbsChannelFlag = 2;
	//g_tMcuDevState.uDetect.bits.CvbsChannelLock = 0; //信号锁定标志,在切源的时候,保持现状,不清除...
	fTw8836.CurrentCvbsChannel = 0;
		
	_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);

	if(!HMIStatusFlag.g_tReverseStatus)
	{
		if(l_tMediaCB.uDevFlag.field.bUnLocked)//同意之前无声音输出,所以不存在衰减的逻辑...
		if(!sAudio.KeyMuteFlag)
		{
			if(!SysWorkStatusGrp.SysBtCallFlag)
			{
				Can_Vol_Reverse = sAudioKeep.SysVol;

				if(Can_Vol_Reverse > AUDIO_VOL_REVERSE)
				{	
					_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_SEL,AUDIO_VOL_REVERSE,1,0,0);
				}
			}
		}
	}
    Camera_printf(_T("--------Open Camera Start!-----\n"));
}


void SRC_CameraStop(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	HMIStatusFlag.g_tBlindStatus = 0;
	
	CamDelay = CAMERA_DELAY;
	//PM_UnitPowerSet(PM_UNIT_RADAR,OFF);
	g_tMcuDevState.uDetect.bits.Blind_Flag = 0;
	//g_tMcuDevState.uDetect.bits.CvbsChannelLock = 0;
	fTw8836.CurrentCvbsChannel = 0;

	//在ACC OFF的时候,进行切源,但是不会切通道,所以需要将互斥标志清除..
	if(IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE) == 0)
		HMIStatusFlag.g_tUpdataBlindParameter = 0;

	if(!HMIStatusFlag.g_tReverseStatus)
	{
		CamClosePwr = 1;
		g_tMcuDevState.uDetect.bits.CvbsChannelFlag = 0;
		if(l_tMediaCB.uDevFlag.field.bUnLocked)
		if(!sAudio.KeyMuteFlag)
		{
			if(!SysWorkStatusGrp.SysBtCallFlag)
			{
				if(Can_Vol_Reverse > AUDIO_VOL_REVERSE)
				{
					_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_SEL,Can_Vol_Reverse,1,0,0);
				}
			}
		}
	}
	else
		g_tMcuDevState.uDetect.bits.CvbsChannelFlag = 1;

	_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);

    Camera_printf(_T("--------Open Camera Stop!-----\n"));
}

bool SRC_ReserveIsValid(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
    uint8_t re = IO_Get(IO_IDX_REVERSE_DET,PIN_INPUT,TRUE);
    return  re;
}


void SRC_ReverseStart(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	HMIStatusFlag.g_tReverseStatus = 1;
	g_tMcuDevState.uDetect.bits.CvbsChannelFlag = 1;
	CamClosePwr = 0;
	CamDelay = 0; 
	if(0 == ReversePwrFlag)
		ReversePwrFlag = 1;
	else
		ReversePwrFlag = 2;
	PM_UnitPowerSet(PM_UNIT_RADAR,ON);
	IO_Set(IO_IDX_REVERSE_OUT,PIN_OUTPUT,1);
	g_tMcuDevState.uIOState.bits.Reverse_Flag = 1;
	//g_tMcuDevState.uDetect.bits.CvbsChannelLock = 0;
	fTw8836.CurrentCvbsChannel = 0;
	_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
	SendParkModeToBus(ReverseParkModeFlag);
	Camera_printf(_T("SRC_ReverseStart()\n"));
	if(!HMIStatusFlag.g_tBlindStatus)
	{
		if(l_tMediaCB.uDevFlag.field.bUnLocked)
		if(!sAudio.KeyMuteFlag)
		{
			if(!SysWorkStatusGrp.SysBtCallFlag)
			{				
				Can_Vol_Reverse = sAudioKeep.SysVol;
				if(Can_Vol_Reverse > AUDIO_VOL_REVERSE)
				{	
					_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_SEL,AUDIO_VOL_REVERSE,1,0,0);
				}
			}
		}
	}
}


void SRC_ReverseStop(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	HMIStatusFlag.g_tReverseStatus = 0;
	IO_Set(IO_IDX_REVERSE_OUT,PIN_OUTPUT,0);
	g_tMcuDevState.uIOState.bits.Reverse_Flag = 0;
	//g_tMcuDevState.uDetect.bits.CvbsChannelLock = 0;
	fTw8836.CurrentCvbsChannel = 0;
	Camera_printf(_T("SRC_ReverseStop()\n"));
	CamDelay = CAMERA_DELAY; 

	if(IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE) == 0)
		HMIStatusFlag.g_tUpdataReverseParameter = 0;
	
	if(!HMIStatusFlag.g_tBlindStatus)
	{
		CamClosePwr = 1;
		g_tMcuDevState.uDetect.bits.CvbsChannelFlag = 0;
		if(l_tMediaCB.uDevFlag.field.bUnLocked)
		if(!sAudio.KeyMuteFlag)
		{
			if(!SysWorkStatusGrp.SysBtCallFlag)
			{
				if(Can_Vol_Reverse > AUDIO_VOL_REVERSE)
				{
					_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_VOL_SEL,Can_Vol_Reverse,1,0,0);
				}
			}
		}
	}
	else
		g_tMcuDevState.uDetect.bits.CvbsChannelFlag = 2;
	_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);

}


eSOURCE_MSG_RETURN SRC_ReverseMsgHandle(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive)
{
    eSOURCE_MSG_RETURN re = SRC_MSG_PROHIBITE;
    
    if(SRC_ZONE_FRONT == eZone)
    {
        switch(tMsg->Id)  
        {
            case MS_INPUT_KEY:
            case MS_INPUT_FIR:
#if 0
		switch(tMsg->uData.a_cData[0])
		{
		/*  case CK_EJECT:*/
		case CK_TEL:      
		case CK_HANDUP:      
		re = SRC_MSG_IGNORE;
		break;
		case CK_VOL_INC:
		case CK_VOL_DEC:
		if((SRC_TYPE_BT_PHONE == sAudio.SysChannel) || 
		(SRC_TYPE_3G_PHONE == sAudio.SysChannel))
		re = SRC_MSG_IGNORE;		//按键有效
		break;

		}
#else
		re = SRC_MSG_IGNORE;
#endif
        	   break;
	     case MS_INPUT_TOUCH:
		src_printf(_T("touch:%ld,%ld,%d\n",ApuTouchInfo.PixX,ApuTouchInfo.PixY,ApuTouchInfo.State));
		
		//Deal Touch Information.
		
		/*
		if(ApuTouchInfo.State == TouchState_Press)		//CLICK state
		{
			if((ApuTouchInfo.PixX > 630)&&(ApuTouchInfo.PixX < 730)&&(ApuTouchInfo.PixY > 410)&&(ApuTouchInfo.PixY < 470))
			{
				ReverseParkModeFlag++;
				if(ReverseParkModeFlag>2)
				{
					ReverseParkModeFlag=0;
				}
				//SendParkModeToBus(ReverseParkModeFlag);
				ReverseParkRefreshFlag=1;
			}
		}
		*/

		SendCoordinateToBus();
		break;
        }
    }
        
    return (re);
}

void Camera_Task(eSOURCE_TYPE eType,EVENT Evt, eTASK_STATE eState)
{

    if(Evt & EVT_TASK_TICK_READY)
    {
        if(CamDelay)
        {
            CamDelay--;
        }
        else
        {
            if(CamClosePwr)
            {
                PM_UnitPowerSet(PM_UNIT_RADAR,OFF);
		   		ReversePwrFlag = 0;
                CamClosePwr = 0;
				src_printf(_T(".............radar power off..........\n"));
            }
        }
    }
    
}

const tSOURCE_CTRL_BLOCK lc_tSrcCameraAttri = 
{
    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    Camera_Task,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    SRC_CameraStart,   /*p_fStart*/
    SRC_CameraStop,   /*p_fStop*/
    NULL,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};



const tSOURCE_CTRL_BLOCK lc_tSrcReversAttri = 
{
    
    /*function*/
    NULL,    /*p_fInit*/
    NULL,    /*p_fDataSync*/
    Camera_Task,    /*p_fTask*/
    NULL,    /*p_fIsValid*/ 
    SRC_ReverseStart,   /*p_fStart*/
    SRC_ReverseStop,   /*p_fStop*/
    SRC_ReverseMsgHandle,    /*p_fSrcMsgHandle*/
    NULL,    /*p_fOption*/

};


#define _CAMERA_FLAG_    la_cSrcFlagDefault[SRC_TYPE_CAMERA]
#define _REVERSE_FLAG_   la_cSrcFlagDefault[SRC_TYPE_REVERSE]


void Camera_CreateSrc(void)
{
	CarAVMDataStruct *pData = pCAN_GetAVMData();
    (void)SRC_Create(&l_tSourceCamera,SOURCE_CAMERA,SRC_TYPE_CAMERA,"Camera",&lc_tSrcCameraAttri,SRC_PRI_CAM,_CAMERA_FLAG_,NULL/*&l_cCameraSeriesRunFlag*/);
    (void)SRC_Create(&l_tSourceReverse,SOURCE_CAMERA,SRC_TYPE_REVERSE,"Reverse",&lc_tSrcReversAttri,SRC_PRI_CAM,_REVERSE_FLAG_,NULL/*&l_cCameraSeriesRunFlag*/);
	pData->BlindReq = 0;
	pData->BlindReqBk = 0;
	HMIStatusFlag.g_tUpdataBlindParameter = 0;
	HMIStatusFlag.g_tUpdataReverseParameter = 0;
}

