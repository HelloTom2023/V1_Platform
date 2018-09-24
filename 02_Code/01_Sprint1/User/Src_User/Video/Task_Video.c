/**********************************************************
 * @file        Task_Video.c
 * @purpose
 * @version    0.01
 * @date        23.Oct. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:
 *  <write/modify>        <time>        <version >    <desc>
 *  Deefisher.Lyu          23.Oct.2012        v0.01        created
 *
  **********************************************************/
#define TASK_VIDEO_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= Function Announcement  =================== */
void Video_Func_Startup(void);
void Video_Func_Idle(void);
void Video_Func_PwrOff(void);
void Video_VchSwitchDisposal(void);
void Video_Detect(void);
/* ========================= public variable ==================== */

/* ========================= private variable =================== */
// Main Function Array
void (*const Tab_VideoFunc[])(void) =
{
    Video_Func_Startup,
    Video_Func_Idle,
    Video_Func_PwrOff,
};
/* ========================= Code Part =================== */

/**********************************************************
 * @function    Video_Func_Startup
 * @brief      Startup Video Related IC
 * @param      None
 * @retval     None
 **********************************************************/
void Video_Func_Startup(void)
{
    uint8_t Result = SUBLAYER_DOING;

    VideoSetSysState(VIDEO_SYS_STARTUP);
    switch(sVideo.FuncStep)
    {
            //Initialize Specific Parameters
        case VIDEO_STARTUP_INIT:
            video_printf(_T("VIDEO Startup %d\n",sVideo.FuncStep));
			fTw8836.ADI7186InitProgramme = 0;
			//if(g_tMcuDevState.uIOState.bits.LCD_Disp) //snake20161028 video初始化之前先关屏
			{
				PM_DisplayClose();
				l_tTftCB.eState = PM_TFT_BLOFF;
				l_tTftCB.TftTempCloseFlag = 1;
				g_tMcuDevState.uIOState.bits.LCD_Disp = 0;
			 	_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);//Updata to APU
			 	video_printf(_T("VIDEO Startup TFT OFF!!!!\n"));
			}
	#ifdef D_VIDEO_SWITCH_TW8836
            IO_Set(IO_IDX_8836A_PWR,PIN_OUTPUT,VALID);
	#endif
            sVideo.VchDelay = VideoDelay(T20MS); //Timeout
            sVideo.FuncStep = VIDEO_STARTUP_LOAD;
            break;
	case VIDEO_STARTUP_LOAD:
            if(sVideo.VchDelay)  //Delay 500ms before switch VCH
                break;
            Video_VariableInit();
            sVideo.FuncStep = VIDEO_ADI7186_RST1;
            break;
	case VIDEO_ADI7186_RST1:
		 Result = ADI7186_ClearRst();
		 video_printf(_T("7186 clearrst\n"));
		 if(SUBLAYER_DONE == Result)
		{
			sVideo.VchDelay = VideoDelay(T100MS);
			sVideo.FuncStep = VIDEO_ADI7186_RST2;
		}
	        break;
	case VIDEO_ADI7186_RST2:
               if(sVideo.VchDelay) 
                break;         
                Result = ADI7186_SetRst();
		 video_printf(_T("7186 Setrst\n"));
		 if(SUBLAYER_DONE == Result)
		{
			sVideo.VchDelay = VideoDelay(T300MS);
			sVideo.FuncStep = VIDEO_ADI7186_RST3;
		 }
	        break;
	case VIDEO_ADI7186_RST3:
               if(sVideo.VchDelay) 
                break;
	         video_printf(_T("7186 clearrst_1\n"));
                Result = ADI7186_ClearRst();
		TW8836_SetLvdsTxEnable();
	        if(SUBLAYER_DONE == Result)
		{
	        sVideo.FuncStep = VIDEO_STARTUP_SWITCH1;
		}
		sVideo.VchDelay = VideoDelay(T100MS);

            //First Video Switch Startup
        case VIDEO_STARTUP_SWITCH1:
               if(sVideo.VchDelay) 
                break;
            Result = Video_Switch1Startup();
            if(SUBLAYER_DONE == Result)
            {
                sVideo.FuncStep = VIDEO_STARTUP_SWITCH2;
            }
            break;

            //Second Video Switch Startup
        case VIDEO_STARTUP_SWITCH2:  
            Result = Video_Switch2Startup();
            if(SUBLAYER_DONE == Result)
            {
                sVideo.FuncStep = VIDEO_STARTUP_VSP;
            }
            break;

            //Video Signal Process IC Startup
        case VIDEO_STARTUP_VSP:
            Result = Video_VspStartup();
            if(SUBLAYER_DONE == Result)
            {
                sVideo.FuncStep = VIDEO_STARTUP_END;
            }
            break;

            //Startup Ends!
        case VIDEO_STARTUP_END:
            video_printf(_T("VIDEO Startup end\n"));
            sVideo.ReadyState = STATE_READY;
            //Feedback Video Power On Done!
            sVideo.FuncStep = VIDEO_FUNC_IDLE;
            _SendMsgToHMI(MS_SYS_VIDEO_STATE,OP_DEV_STATE_NORMAL,NULL);
            break;

        default:
            break;
    }

    //Error Occurs:Retry or Feedback to System
    if(Result > SUBLAYER_DONE)
    {

    }
}
/**********************************************************
 * @function    Video_Func_Idle
 * @brief      Video Idle State, Waiting for newly Actions
 * @param      None
 * @retval     None
 **********************************************************/
void Video_Func_Idle(void)
{
    VideoSetSysState(VIDEO_SYS_RUN);
}
/**********************************************************
 * @function    Video_Func_PwrOff
 * @brief      Video Task Power Off
 * @param      None
 * @retval     None
 **********************************************************/
void Video_Func_PwrOff(void)
{
    uint8_t Result = SUBLAYER_DOING;

    VideoSetSysState(VIDEO_SYS_PWROFF);
    switch(sVideo.FuncStep)
    {
            // Sort Currently Situation, and Initialize Some Parameters
        case VIDEO_PWROFF_SORT:
            video_printf(_T("VIDEO PwrOff %x\n",sVideo.FuncStep));
            _SendMsgToHMI(MS_SYS_VIDEO_STATE,OP_DEV_STATE_OFF,NULL);
            sVideo.ReadyState = 0;
            sVideo.FuncStep = VIDEO_PWROFF_SAVE;
            sVideo.VchDelay = VideoDelay(T200MS); //Timeout
            break;

            //Save Parameters to eeprom
        case VIDEO_PWROFF_SAVE:
            if(sVideo.VchDelay)  //Delay 500ms before switch VCH
                break;
            video_printf(_T("VIDEO PwrOff %x\n",sVideo.FuncStep));
	#ifdef D_VIDEO_SWITCH_TW8836
            IO_Set(IO_IDX_8836A_PWR,PIN_OUTPUT,INVALID);
	#endif	
            sVideo.FuncStep = VIDEO_PWROFF_POWER;
            break;

            //Close Related Power
        case VIDEO_PWROFF_POWER:
            sVideo.FuncStep = VIDEO_PWROFF_END;
            break;

            //Power Off Ends!
        case VIDEO_PWROFF_END:
            video_printf(_T("VIDEO PwrOff %x\n",sVideo.FuncStep));
            sVideo.FuncStep = VIDEO_FUNC_SLEEP;
            VideoSetSysState(VIDEO_SYS_SLEEP);
            OS_TaskStop(TASK_ID_VIDEO); // Stop Video Task
            break;

        default:
            video_printf(_T("VIDEO PwrOff %x\n",sVideo.FuncStep));
            Result = SUBLAYER_STEP_ERROR;
            break;
    }
}
/**********************************************************
 * @function    Video_Manager
 * @brief      Video Manager, Control main functions of video task
 * @param      None
 * @retval     None
 **********************************************************/
void Video_Manager(void)
{
    // Execute Video Functions while Task Not Sleep
    if(VIDEO_SYS_SLEEP != VideoGetSysState())
    {
        //Main Function Control
        (*Tab_VideoFunc[((sVideo.FuncStep >> 4) & 0x0F)])();

        // VCh Switch Disposal
        Video_VchSwitchDisposal();

        Tw8836_Disposal();
        // Video Signal Detect
        Video_Detect();
    }
}
/**********************************************************
 * @function    Video_VariableInit
 * @brief
 * @param      None
 * @retval     None
 **********************************************************/
void Video_VariableInit(void)
{
    uint8_t i;

    //Video Detect
    sVideo.DetFlag = VD_NO_VIDEO;

    //Vch Control
    sVideo.VchCtl = VCH_SWITCH_IDLE;
    for(i = 0; i < VCH_BUFFER_MAX; i++)
    {
        sVideo.ReqVch[i].Req = SRC_TYPE_NUM;
    }
    sVideo.VchHead = 0;
    sVideo.VchTail = 0;

    sVideo.SysVch = SRC_TYPE_NUM;
    sVideo.RearVch = SRC_TYPE_NUM;

#ifdef D_VIDEO_SWITCH_FMS6501
    Fms6501_InitVariable();
#endif//D_VIDEO_SWITCH_FMS6501
#ifdef D_VIDEO_SWITCH_TW8836
    Video_ModuleInit();
#endif//D_VIDEO_SWITCH_FMS6501

    sVideo.ReadyState = 0;
}
/**********************************************************
 * @function    Video_ColdInit
 * @brief      Cold Start, Reset All of Video
 * @param      None
 * @retval     None
 **********************************************************/
void Video_ColdInit(void)
{
    sVideo.FuncStep = VIDEO_FUNC_STARTUP;
    VideoSetSysState(VIDEO_SYS_SLEEP);
}
/**********************************************************
 * @function    Video_WarmInit
 * @brief      Warm Start, Initialize All of Video
 * @param      None
 * @retval     None
 **********************************************************/
void Video_WarmInit(void)
{
    sVideo.ReadyState = 0;
    sVideo.FuncStep = VIDEO_FUNC_STARTUP;
    VideoSetSysState(VIDEO_SYS_SLEEP);
}
/**********************************************************
 * @function    Video_MsgHandler
 * @brief      Dispose Messages received
 * @param      tMSG_BUF* Msg
 * @retval     None
 **********************************************************/
void Video_MsgHandler(tMSG_BUF* pMsg)
{
#define MsgId     pMsg->Id
#define MsgSid     pMsg->iSid

    video_printf(_T("VIDEO Msg %d,%d,%d\n",MsgId,MsgSid,VideoGetSysState()));
    switch(MsgId)
    {
            //4Power Manager Related Message
        case MS_PM_STATE:
            switch(MsgSid)
            {
                case OP_PM_STATE_ON:
					fTw8836.CurrentCvbsChannel = 0;//开启ACC之后,视频信号要重新锁定...防止在盲区或者倒车的情况下,
                case OP_PM_STATE_STANDBY:
                    if(!OS_TaskIsActive(TASK_ID_VIDEO))
                    {
                        OS_TaskStart(TASK_ID_VIDEO); // Start Video Task
                    }
					
					if(sVideo.PwrState == 0)
					{
	                    sVideo.PwrState = 1;
	                    sVideo.VchHead=0;
	                    sVideo.VchTail=0;
					}
					
                    //Goto Set System On
                    if(VIDEO_SYS_RUN != VideoGetSysState())
                    {
                        VideoSetSysState(VIDEO_SYS_STARTUP);
                        sVideo.FuncStep = VIDEO_FUNC_STARTUP;
                    }
                    break;

                case OP_PM_STATE_WAIT_SLEEP:
					break;
		  case OP_PM_STATE_BATERR:
                    sVideo.PwrState = 0;
                    break;

                default:
                    sVideo.PwrState = 0;
                    //Goto Shut Off Tuner and Close Power
                    if(VideoGetSysState() <= VIDEO_SYS_PWROFF)
                    {
                        VideoSetSysState(VIDEO_SYS_PWROFF);
                        sVideo.FuncStep = VIDEO_FUNC_PWROFF;
                        sVideo.VchSwitchEn = 0;
                    }
                    break;
            }
            break;
            //4Video Related Message

        case MS_VIDEO_SET_OCH:
            break;
        case MS_PM_TFT_8836:
		Video_LvdsOutEnable();
            video_printf(_T("--MS_PM_TFT_8836--\n"));
            break;
        case MS_SYS_APU_INFO:
		switch(MsgSid)
		{
			 case OP_DEV_STATE_NOCONNECT:
		        case OP_DEV_STATE_OFF:
		        case OP_DEV_STATE_SLEEP:
		        case OP_DEV_STATE_UPDATA:
		        case OP_DEV_STATE_ERR:
		        case OP_DEV_STATE_RESET:
				break;
			case OP_DEV_STATE_CONNECTED:  //APU 正常连接，可以正常进行UI叠加显示。
				break;
			default:
				break;
		}
            break;
        case MS_VIDEO_UPLOAD_INFO:
            //sVideo.VchSwitchEn = 1;
            break;
    }

#undef MsgId
#undef MsgSid
}
/**********************************************************
 * @function    Video_VchQueueIn
 * @brief      Queue in Required VCH
 * @param      uint8_t Req
 *            uint8_t Type
 * @retval     NULL
 **********************************************************/
//#define D_VCH_SAME_REPLACE // newly requirement will replace the specific one if they have same type
// close this definition, the requirement will implement one by one
void Video_VchQueueIn(uint8_t Req, uint8_t Type)
{
    uint8_t Temp = VCH_BUFFER_MAX;
	
    //Check Same Type
#ifdef D_VCH_SAME_REPLACE
    for(Temp = 0; Temp < VCH_BUFFER_MAX; Temp++)
    {
        if((SRC_TYPE_NUM != sVideo.ReqVch[Temp].Req) && (Type == sVideo.ReqVch[Temp].Type))
        {
            break;
        }
    }
#endif //D_ACH_SAME_REPLACE
    //Queue New Requirement to Buffer
    if(Temp >= VCH_BUFFER_MAX)
    {
    	//存在风险??????snake20161025
    	//当在切换视频的时候,下一个视频切换请求又来了,就会造成第二个视频切换不过去.
    	//所以在这里判断视频切换是否成功,切换不成功,就忽略本次切换,进行下一次视频的切换...
    	//只有前后两个源的优先级相同或者后面的源的优先级比前面的源的优先级高,才能打断当前源的通道切换过程...
    	//应该使用源的列表类型来进行判断,是否能够被打断...
		/*if(sVideo.VchCtl != VCH_SWITCH_IDLE) 
		{
			//if(sVideo.VchHead == sVideo.VchTail) sVideo.ReqVch[sVideo.VchTail].Req == sVideo.ReqVch[sVideo.VchHead].Req = SRC_TYPE_NUM
			//只有队列的头和尾不相等的时候,sVideo.VchCtl != VCH_SWITCH_IDLE...
			//sVideo.ReqVch[sVideo.VchHead].Req就是当前正常切换通道的源...			
			uint8_t i = 0;
			uint8_t CurrentSourceListType = SRC_LIST_NUM;
			uint8_t ReqSourceListType = SRC_LIST_NUM;
			for(i=0;i<SRC_LIST_NUM;i++)
			{
				tNODE* p_tNode = SRC_GetListHeadNode(i);
				tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
				if(p_tSrc->eSrcType == sVideo.ReqVch[sVideo.VchHead].Req)//正在切换通道的源...
					CurrentSourceListType = i;
				if(p_tSrc->eSrcType == Req)
					ReqSourceListType = i;
			}

			//video_printf(_T("----CurrentSourceListType = %d,ReqSourceListType = %d,sVideo.VchHead = %d,sVideo.VchTail = %d\n",CurrentSourceListType,ReqSourceListType,sVideo.VchHead,sVideo.VchTail));
			//video_printf(_T("----sVideo.ReqVch[sVideo.VchHead].Req = %d,sVideo.ReqVch[sVideo.VchTail].Req = %d,Req = %d\n",sVideo.ReqVch[sVideo.VchHead].Req,sVideo.ReqVch[sVideo.VchTail].Req,Req));

			//请求源的优先级比当前源的优先级要高或者相等才能打断...
			if(((ReqSourceListType > CurrentSourceListType) && (CurrentSourceListType != SRC_LIST_NUM)))
				video_printf(_T("Request Source priority is Low,not Stop Current Operation!!!!!\n"));
			else
			if(sVideo.ReqVch[sVideo.VchHead].Req != Req)//请求的源和当前正在切换的源,一致的时候,可以不用中断操作
			{
				//VCH_SWITCH_END
				sVideo.ReqVch[sVideo.VchHead].Req = SRC_TYPE_NUM;
	            //Clear State and Queue out
	            sVideo.VchHead++;
	            if(sVideo.VchHead >= VCH_BUFFER_MAX)
	            {
	                sVideo.VchHead = 0;
	            }
				video_printf(_T("-----fTw8836.DrvSubStep = %d,sVideo.VchCtl = %d......",fTw8836.DrvSubStep,sVideo.VchCtl));
				sVideo.VchCtl = VCH_SWITCH_IDLE;
				video_printf(_T("Video Channel changeing,stop Current Operation,Start next Operation!!!!!\n"));
			}
		}
		*/
        sVideo.ReqVch[sVideo.VchTail].Req = Req;
        sVideo.ReqVch[sVideo.VchTail].Type = Type;

        sVideo.VchTail++;
        if(sVideo.VchTail >= VCH_BUFFER_MAX)    //Roll Off~~Cycle
        {
            sVideo.VchTail = 0;
        }
		/*
		video_printf(_T("[1]  sVideo.VchHead = %d,sVideo.VchTail = %d\n",sVideo.VchHead,sVideo.VchTail));

		if(sVideo.VchTail == sVideo.VchHead)
		{
			sVideo.VchHead = sVideo.VchHead - 1;
		}
		
		video_printf(_T("[2] sVideo.VchHead = %d,sVideo.VchTail = %d\n",sVideo.VchHead,sVideo.VchTail));
		*/
    }
#ifdef D_VCH_SAME_REPLACE
    else
    {
        sVideo.ReqVch[Temp].Req = Req;
        sVideo.ReqVch[Temp].Type = Type;
        //if required is same as implementing one ,re-implement currently one use new setting
        if(sVideo.ReqVch[sVideo.VchHead].Type == Type)
        {
            sVideo.VchCtl = VCH_SWITCH_IDLE;
        }
    }
#endif //D_ACH_SAME_REPLACE
}
/**********************************************************
 * @function    Video_SetChannel
 * @brief      Set a newly Video channel
 * @param      NULL
 * @retval     NULL
 **********************************************************/
void Video_SetChannel(eSOURCE_ZONE eZone,const tSOURCE* tSrc,uint8_t VidPri)
{
    uint8_t SrcId = SRC_TYPE_NUM;
    uint8_t SysType = SYSTEM_FRONT;

    video_printf(_T("---Video_SetChannel:%d,%d---\n",tSrc->eSrcType,eZone));
    if(eZone == SRC_ZONE_FRONT)
    {
    	 //g_tSysStateDbgInfo.CurVideoSource = tSrc->eSrcID;
		 sVideo.CurrentVideoSourceId = tSrc->eSrcID;
    }
    if(NULL != tSrc)
    {
        SrcId = tSrc->eSrcType;
        if((SrcId == SRC_TYPE_SLEEP) || (SrcId == SRC_TYPE_SYS_STDBY))
        {
		SrcId = SRC_TYPE_AVOFF;
        }

        if(SRC_ZONE_REAR == eZone)
        {
            SysType = SYSTEM_REAR;
        }

        Video_VchQueueIn(SrcId,SysType);
    }
    else
    {
        SrcId = SRC_TYPE_NUM;
        if(SRC_ZONE_REAR == eZone)
        {
            SysType = SYSTEM_REAR;
        }
        Video_VchQueueIn(SrcId,SysType);
    }
    video_printf(_T("---Video_SetChannel end:%d,%d---\n",sVideo.VchHead,sVideo.VchTail));
}
/**********************************************************
 * @function    Video_VchSwitchDisposal
 * @brief      Switch VCH
 * @param      NULL
 * @retval     NULL
 **********************************************************/
void Video_VchSwitchDisposal(void)
{
    uint8_t Result = SUBLAYER_DOING;

    //Only Execute VCH Swich action while VideoTask Init Ready
    if(STATE_READY != (sVideo.ReadyState & 0x01))
        return;

    if(VIDEO_SYS_RUN != VideoGetSysState())
    {
        return;
    }
    if(0 == sVideo.PwrState)
    {
        return;
    }
	
    switch(sVideo.VchCtl)
    {
            //Idle State, Wait For Newly Input Requirement
        case VCH_SWITCH_IDLE:
            if(sVideo.VchHead != sVideo.VchTail)
            {
                video_printf(_T("---1.SwitchDisposal:%d,%d,%d---\n",sVideo.VchHead,sVideo.VchTail,sVideo.ReqVch[sVideo.VchHead].Type));
                sVideo.VchCtl = VCH_SWITCH_SWITCH1;
                sVideo.VchDelay = 0; //VideoDelay(T1P5S); //Timeout
            }
            break;

            //Change Switch1's Related Channel
        case VCH_SWITCH_SWITCH1:
            if(sVideo.VchDelay) //((sVideo.VchDelay) && (0 == sVideo.VchSwitchEn))  //Delay 500ms before switch VCH
                break;
            Result = Video_ChangeSwitch1Vch(sVideo.ReqVch[sVideo.VchHead].Req,sVideo.ReqVch[sVideo.VchHead].Type);
            if(SUBLAYER_DONE == Result)
            {
                sVideo.VchCtl = VCH_SWITCH_SWITCH2;
				//snake20161025
				//是否存在风险????
				//在重新切换通道的时候,判断ADV7186的切换是否完成????
				//没有完成的话,就停止本次切换,进行下一次切换...
				//增加中断IIC操作的判断....防止有的时候IIC参数不能正常的写入的问题
				/*if(fTw8836.DrvSubStep != 0)
				{
					fTw8836.DrvSubStep = 0;
					fTw8836.DrvDelay = 0;
					fTw8836.BackScreenMode = e_NONE_INPUT_OUT_NULL;
					I2CDevCtrl.gRWStep = OPERATION_0;//当IIC处于写的过程中,停止写操作....
					video_printf(_T("ADV7186 Setting,Stop Current Operation,Start next Operation!!!!!\n"));
				}*/          
			}
            break;

            //Change Switch2's Related Channel
        case VCH_SWITCH_SWITCH2:
            if(0 == sVideo.VchSwitchEn)
                break;
            Result = Video_ChangeSwitch2Vch(sVideo.ReqVch[sVideo.VchHead].Req,sVideo.ReqVch[sVideo.VchHead].Type);
            if(SUBLAYER_DONE == Result)
            {
                if(SYSTEM_REAR == sVideo.ReqVch[sVideo.VchHead].Type)
                    sVideo.VchCtl = VCH_SWITCH_END;
                else
                    sVideo.VchCtl = VCH_SWITCH_VSP;
            }
            break;

            //Change VSP Related Channel
        case VCH_SWITCH_VSP:
            Result = SUBLAYER_DONE;//Video_ChangeSwitch3Vch(sVideo.ReqVch[sVideo.VchHead].Req,sVideo.ReqVch[sVideo.VchHead].Type);
            if(SUBLAYER_DONE == Result)
            {
                sVideo.VchCtl = VCH_SWITCH_END;
            }
            break;

            // Switch End, Save Newly State and Feedback
        case VCH_SWITCH_END:
            //Updated Currently Channel
            if((SYSTEM_FRONT == sVideo.ReqVch[sVideo.VchHead].Type) || (SYSTEM_ALL == sVideo.ReqVch[sVideo.VchHead].Type))
            {
                sVideo.SysVch = sVideo.ReqVch[sVideo.VchHead].Req;
                sVideo.DetFlag = VD_NO_VIDEO;
            }
            if((SYSTEM_REAR == sVideo.ReqVch[sVideo.VchHead].Type) || (SYSTEM_ALL == sVideo.ReqVch[sVideo.VchHead].Type))
            {
                sVideo.RearVch = sVideo.ReqVch[sVideo.VchHead].Req;
            }

			//snake20161222
			if(g_tSysStateDbgInfo.CurVideoSource != sVideo.CurrentVideoSourceId)
			{
				g_tSysStateDbgInfo.CurVideoSource = sVideo.CurrentVideoSourceId;
				//OS_PostMsgDir(&l_tMediaDrvTaskCB,GID_MCU_TX_SYS_INFO,SID_MCU_TX_SYS_STATE_INFO,NULL);
			}
            //Feedback to HMI: Video Channel Switch Done!
            //Video_BackLight(ON);

            sVideo.VchCtl = VCH_SWITCH_IDLE;
            sVideo.ReqVch[sVideo.VchHead].Req = SRC_TYPE_NUM;
            //Clear State and Queue out
            sVideo.VchHead++;
            if(sVideo.VchHead >= VCH_BUFFER_MAX)
            {
                sVideo.VchHead = 0;
            }
            video_printf(_T("---2.SwitchDisposal:%d,%d---\n",sVideo.VchHead,sVideo.VchTail));
            break;

        default:
            sVideo.VchCtl = VCH_SWITCH_IDLE;
            break;
    }

    //Error Occurs:Retry or Feedback to System
    if(Result > SUBLAYER_DONE)
    {

    }
}
/**********************************************************
 * @function    Video_Detect
 * @brief      Detect Video Signal State
 * @param      NULL
 * @retval     NULL
 **********************************************************/
void Video_Detect(void)
{
    //Maybe Need judge dissension
    sVideo.DetFlag = Video_CheckVideo();
}


/**********************************************************
 * @function    Video_VirTimer
 * @brief      Virtual Timer: 2ms tick
 * @param      None
 * @retval     None
 **********************************************************/
void Video_VirTimer(void)
{
    if(sVideo.VchDelay)
        sVideo.VchDelay--;
    if(fTw8836.DrvDelay)
        fTw8836.DrvDelay--;
    if(sVideo.VdDelay)
        sVideo.VdDelay--;
}
/**********************************************************
 * @function    Video_Task
 * @brief      a periodic task for Video module
 * @param      EVENT Evt
 *                 eTASK_STATE eState
 * @retval     None
 **********************************************************/
void VID_Task(EVENT Evt,eTASK_STATE eState)
{
    if(Evt & EVT_COLD_INIT)    //Cold Start, Reset Parameters
    {
        Video_ColdInit();
    }

    if(Evt & EVT_WARM_INIT)    //Warm Start, Initialize Parameters
    {
        Video_WarmInit();
    }

    if(Evt & EVT_MSG_READY)
    {
        tMSG_BUF tMsg;
        if(QUE_ERR_NONE == OS_GetMsgDir(&g_tVidTaskCB,&tMsg))
        {
            Video_MsgHandler(&tMsg);
        }
    }


    switch(eState)
    {
        case TASK_STATE_READY:

            break;

        case TASK_STATE_RUNNING:
        case TASK_STATE_STOP:
            if(Evt & EVT_TASK_TICK_READY)
            {
                //Video Main Control
                Video_VirTimer();
                Video_Manager();
            }
            break;
    }
}

bool VID_Init(void)
{
    IO_Set(IO_IDX_DSP_AVDET,PIN_INPUT,VALID);
    IO_Set(IO_IDX_DVD_AUX_RGB,PIN_OUTPUT,INVALID);
    IO_Set(IO_IDX_MHL_AUX_SEL,PIN_OUTPUT,INVALID);  //Only For Hero  
    return (TRUE);
}

bool VID_DInit(void)
{
    IO_Set(IO_IDX_DSP_AVDET,PIN_INPUT,INVALID);
    IO_Set(IO_IDX_DVD_AUX_RGB,PIN_INPUT,INVALID);
    IO_Set(IO_IDX_MHL_AUX_SEL,PIN_INPUT,INVALID);  
    return (TRUE);
}



static const tTASK_BLOCK l_tVideoTCB =
{
    "VID",
    _VID_TASK_TICK_,
    _VID_CORE_TICK_,
    VID_Task,
    VID_Init,
    VID_DInit,
};

tRING_QUE l_tVidMsgQue;
tMSG_BUF la_tVidMsgBuf[ VIDEO_MSG_QUE_DEEP];

bool VID_TaskCreate(void)
{
    return OS_TaskCreate(TASK_ID_VIDEO,&g_tVidTaskCB,&l_tVideoTCB,&l_tVidMsgQue,la_tVidMsgBuf,VIDEO_MSG_QUE_DEEP);
}


