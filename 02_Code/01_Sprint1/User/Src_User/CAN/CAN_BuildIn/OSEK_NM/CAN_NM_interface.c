#include "..\..\..\config\inc.h"

#if CAN_NM_DBG_EN && D_PRINT_EN
#define NM_debug(x)  			x
#else
#define NM_debug(x)
#endif

#ifdef NM_ENABLE_MACRO

Can_StdMsg_Typedef	GMsg_NM;
NM_VAR_STRUCT   NM_NetNode;

unsigned int		gILTiCanNMBase;
unsigned char		gILCanNMMsgTransitFlag;				//成功发送报文标志。
unsigned char		gILCanNMLocalWakeupFlag;         //本地唤醒标志；
unsigned char 		gILCanNMRemoteWakeupFlag;
unsigned char		gILCanNMNormalMsgActive;
unsigned char 	       gILCanNMCanBusOff;
unsigned char		gILCanNMHasSleeped;	//节点硬件状态，1：硬件初始化，2：睡眠，3：唤醒
unsigned char		gILCanNMBatFlag;
IL_CANNM_NetWorkStatus_TypeDef gsILCanNMNetWorkStatus;

BuffPointStruct   	NM_RxBuffPointManage;
CanMsgStruct 		NM_MsgRxBuf[CAN_NMMSG_BUFF_NUM];
/******************************************************************/
// Add Code, used for Send Error count;  2016-10-21
static uint16_t  SendErrorCnt = 0;
/******************************************************************/
CanMsgStruct *  NM_ReadMsgBuffer(void)
{
	uint8_t i;
	CanMsgStruct * pRxMessage = NULL;

	if(NM_RxBuffPointManage.ReceivedNum==0)
	{
		return NULL;
	}
	
	i = NM_RxBuffPointManage.Point_read;

	pRxMessage = &NM_MsgRxBuf[i];

	CAN_ENTER_CRITICAL_REGION();
	NM_RxBuffPointManage.ReceivedNum--;
	i++;
	if(i>=CAN_NMMSG_BUFF_NUM)
	{
		i = 0;
	}
	NM_RxBuffPointManage.Point_read = i;
	CAN_EXIT_CRITICAL_REGION();	
	return pRxMessage;
}
void  NM_WriteMsgBuff(CanMsgStruct *pRxMessage)
{
	uint8_t index = NM_RxBuffPointManage.Point_write;
	uint8_t j = 0;

	NM_MsgRxBuf[index].CAN_Id  = pRxMessage->CAN_Id;
	NM_MsgRxBuf[index].CANMsgId = pRxMessage->CANMsgId;
	NM_MsgRxBuf[index].CANMsgDlc = pRxMessage->CANMsgDlc;
	
	for(j = 0;j<pRxMessage->CANMsgDlc;j++)
	{
		NM_MsgRxBuf[index].Data[j] = pRxMessage->Data[j];
	}
	index++;
	if(index>=CAN_NMMSG_BUFF_NUM)
	{
		index = 0;
	}
	NM_RxBuffPointManage.Point_write = index;
	NM_RxBuffPointManage.ReceivedNum++;
	if(NM_RxBuffPointManage.ReceivedNum>CAN_NMMSG_BUFF_NUM)
	{
		NM_RxBuffPointManage.ReceivedNum = CAN_NMMSG_BUFF_NUM;
		NM_RxBuffPointManage.Point_read = NM_RxBuffPointManage.Point_write;
	}
	//NM_debug(_T("NM_msg_write:%d\n", NM_RxBuffPointManage.ReceivedNum));
}

uint8_t IL_CanHM_Hardwave_Init(uint8_t gCANHardwareState)
{
	switch(gCANHardwareState)
	{
		case IL_CANNM_HARDWARE_INIT:    /*init*/
			NM_debug(_T("NM_req_init\n"));
/*****************************************************************************/
/*add Code  for Default, 2016-10-21 */
			CANbus_DefaultInit(NM_NetNode.CAN_Id);			// Add this code!!!
/*****************************************************************************/
			CANbus_StartupHandler(NM_NetNode.CAN_Id);
			CANUser_StartSendInitMsg(NM_NetNode.CAN_Id);
			CANUser_TryToSendCANMsg(NM_NetNode.CAN_Id);
			NM_NetNode.opMode = CAN_APP_MODE_ON;
			break;
		case IL_CANNM_HARDWARE_SLEEP:		/*Enter Sleep*/
			NM_debug(_T("NM_req_sleep\n"));
			CANbus_NetLayerStopAllSend(NM_NetNode.CAN_Id);
			CANbus_AppLayerReqSwitchMode(NM_NetNode.CAN_Id, CAN_APP_MODE_SLEEP);
			#ifdef UDS_ENABLE_MACRO
			if(NM_NetNode.CAN_Id == UdsCANConfig.UseId)
			{
				Uds_Close();
			}
			#endif
			NM_NetNode.opMode = CAN_APP_MODE_PRESLEEP;
			NM_NetNode.SleepCnt = 0;
			break;
		case IL_CANNM_HARDWARE_WAKEUP:	/*BusAwake*/
			NM_debug(_T("NM_req_wakeup\n"));
			//IO_Set(IO_IDX_CAN0_WAKE,PIN_OUTPUT,0);
			CAN0_LocalWakeup(1, 0);
			CANbus_AppLayerReqSwitchMode(NM_NetNode.CAN_Id, CAN_APP_MODE_START);
			CANbus_AppLayerHandler(NM_NetNode.CAN_Id);
			NM_NetNode.opMode = CAN_APP_MODE_ON;
			
			break;
		case IL_CANNM_HARDWARE_NORMAL:	/*Enter Normal mode */
			NM_debug(_T("NM_req_normal\n"));
			NM_NetNode.opMode = CAN_APP_MODE_ON;
			break;
		default:
			break;
	}
	return 1;		/*Return OK */
}


void NM_AdpRoutine(uint8_t CANCh)
{
	switch(NM_NetNode.opMode)
	{
		case CAN_APP_MODE_ON:
			if(CANbus_IsBusOffStatus(CANCh))
			{
				if(!NM_NetNode.BusOff)
				{
					NM_NetNode.BusOff = 1;
					gILCanNMCanBusOff = IL_CANNM_BCM_BUS_OFF;
					#ifdef UDS_ENABLE_MACRO
						Uds_UpdateDTCStatus(DTC_ID_BODY_BUS_OFF, DTC_AVILABILITY_MASK);
						Uds_UpdateDTCStatus(DTC_ID_PT_BUS_OFF, DTC_AVILABILITY_MASK);
					#endif
					NM_debug(_T("NM_can_busoff\n"));
					CANbus_EnableCANTransceiver(CANCh, CAN_TRANSCEIVER_MODE_SLEEP);
					CANbus_DefaultInit(CANCh);
					CANbus_StartupHandler(CANCh);
					CAN0_LocalWakeup(1, 0);

					if(!CANTask_GetSysACCState())
					{
					/* 在BUSOFF的情况下，如果ACC off满足休眠条件
					  * 主动的请求休眠20140828
					  */
						IL_CanHM_Hardwave_Init(IL_CANNM_HARDWARE_SLEEP);
					       IL_CanNM_Init();
					}
				}
			}
			else
			{
				if(NM_NetNode.BusOff)
				{
					NM_NetNode.BusOff = 0;
					gILCanNMCanBusOff = IL_CANNM_BCM_BUS_OK;
					NM_debug(_T("NM_can_Recovery\n"));
				}
			}
			
			break;
		case CAN_APP_MODE_BUSOFF:
			break;
		case CAN_APP_MODE_SLEEP:
			if(CANbus_NetLayerGetWakeupStatus(CANCh))
			{
				CANbus_NetLayerClearWakeupStatus(CANCh);
				gILCanNMRemoteWakeupFlag = 1;
				NM_debug(_T("NM_can_wakeup1\n"));
			}
			else
			{
				if(NM_NetNode.Wakeup)
				{
					gILCanNMRemoteWakeupFlag = 1;
					NM_debug(_T("NM_can_wakeup2\n"));
				}
			}
			break;
		case CAN_APP_MODE_PRESLEEP:
			if(NM_NetNode.RealSleep)
			{
				NM_NetNode.opMode = CAN_APP_MODE_SLEEP;
				NM_debug(_T("NM_can_sleep\n"));
			}
			else
			{
				NM_NetNode.SleepCnt++;
				if(NM_NetNode.SleepCnt>=10)		/* 10x5MS = 50MS */
				{
					gILCanNMRemoteWakeupFlag = 1;
					NM_debug(_T("NM_can_CntWake\n"));
				}
			}
			break;
		default:
			break;
	}
	if((!NM_NetNode.BusOff) || (CANTask_GetSysACCState()))
	{
		IL_CanNM_Function_Main();
	}
}

void NM_AppMsgHandler(uint8_t CANCh)
{
	if((NM_NetNode.opMode == CAN_APP_MODE_ON) 	\
		&&(NM_NetNode.BusOff == 0))
	{
		CANbus_NetLayerSendManager(CANCh);
		#ifdef UDS_ENABLE_MACRO
		if(CANCh == UdsCANConfig.UseId)
		{
			Uds_ProtocolStackMain();
		}
		#endif
	}
}

Can_StdMsg_Typedef IL_CanNM_RecMsgSave(void)
{
	CanMsgStruct *pRxMessage = NM_ReadMsgBuffer();
	if(pRxMessage != NULL)  
	{
		GMsg_NM.Id = pRxMessage->CANMsgId;
		GMsg_NM.Dlc = pRxMessage->CANMsgDlc;
		Memory8Copy(GMsg_NM.Data, pRxMessage->Data, pRxMessage->CANMsgDlc);
		NM_debug(_T("NM_get_msg\n"));
	}
	else
	{
		GMsg_NM.Id = 0;
	}

	return GMsg_NM;
}

uint8_t IL_CanNMSendMsg(Can_StdMsg_Typedef  NM_Msg)
{
	#if 0
		return 1;	//snake20160818 not send 411 msg to canbus
	#else
	CanMsgStruct NmTxMsg;
	NmTxMsg.CANMsgDlc = NM_Msg.Dlc;
	NmTxMsg.CANMsgId = NM_Msg.Id;
	NmTxMsg.CAN_Id = NM_NetNode.CAN_Id;
	Memory8Copy(NmTxMsg.Data, NM_Msg.Data, NM_Msg.Dlc);
	NM_debug(_T("\nNM_msg_Send:"));
/******************************************************************/
// Add Code, used for Send Error count;  2016-10-21
	if(NM_NetNode.MsgSendStatus == NM_MSG_SEND_REQ)
	{
		SendErrorCnt++;
	}
	else
	{
		if(SendErrorCnt>0)
		{
			SendErrorCnt--;
		}
	}
	if(SendErrorCnt>5)
	{
		SendErrorCnt = 0;
		NM_debug(_T("NM Send Error >5\n"));
		IL_CanHM_Hardwave_Init(IL_CANNM_HARDWARE_INIT);
	}
/*****************************************************************/
	if(!CANbus_AppLayerSendNMMsg(&NmTxMsg))
	{
		NM_NetNode.MsgSendStatus =NM_MSG_SEND_REQ;
		gILCanNMMsgTransitFlag = 0;
		//NM_debug(_T("1\n"));
		return 1;	/*send ok */
	}
	//NM_debug(_T("0\n"));
	return 0;		/*reject to send.*/
	#endif
}
extern CANAppLayerStruct 	CanAppLayerState[CAN_IDMAX];
void NM_InterfaceInit(void)
{
	CanAppLayerState[CAN_ID_BODY].CANopMode = CAN_APP_MODE_ON;

	NM_NetNode.CAN_Id = CAN_ID_BODY;
	NM_NetNode.MsgSendStatus = NM_MSG_SEND_IDLE;
	NM_NetNode.FirstPowerOnFlag = 1;
	NM_NetNode.opMode = CAN_APP_MODE_IDLE;
	NM_NetNode.BusOff = 0;
	NM_NetNode.Wakeup = 0;
	NM_NetNode.SleepCnt = 0;
	
	gILCanNMLocalWakeupFlag = 0;
	gILCanNMRemoteWakeupFlag = 0;
	gILTiCanNMBase = 0;
	gILCanNMMsgTransitFlag = 0;
	gILCanNMCanBusOff = 0;
	gILCanNMBatFlag = 1;

	NM_RxBuffPointManage.Point_read = 0;
	NM_RxBuffPointManage.Point_write = 0;
	NM_RxBuffPointManage.ReceivedNum = 0;
/******************************************************************/
// Add Code, used for Send Error count;  2016-10-21
	SendErrorCnt = 0;
/******************************************************************/

}
#endif


