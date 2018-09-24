#define CANBUS_LOCAL_C
#include "..\..\..\config\inc.h"

#ifdef CAN_MODULE_ENABLE
#ifdef CAN_INNER_ENABLE

#pragma pack(1)
typedef struct
{
/*--------------DATA[0]-----------------*/
	uint8_t ControlMode	:2;
	uint8_t IllOn			:1;
	uint8_t SysStatus    		:3;
	uint8_t AccStatus		:2;
/*--------------DATA[1]-----------------*/
	uint8_t Reverse		:1;
	uint8_t RadioBand		:1;
	uint8_t IllLevel		:6;
/*--------------DATA[2]-----------------*/
	uint8_t DtvCmd		:5;
	uint8_t Language		:3;
/*--------------DATA[3]-----------------*/
	uint8_t IllType			:2;
	uint8_t Volume			:6;
/*--------------DATA[4]-----------------*/
	uint8_t MediaCmd		:5;
	uint8_t RadioStatus		:3;
/*--------------DATA[5]-----------------*/
	uint8_t Reserved1		:2;
	uint8_t MediaType		:2;
	uint8_t SourceType		:4;
/*--------------DATA[6]-----------------*/
	uint8_t MediaPlayStatus	:4;
	uint8_t MediaMode		:3;
	uint8_t Reserved2		:1;
}InnerCANMsgStruct;

#pragma pack(4)

InnerCANMsgStruct		HUInnerMsgBak;
CanMsgStruct			HUInnerCycleMsg;
ExtMediaDataStruct		CAN_ExtDtvInfoStr;
TIMER_STRUCT		InnerTimerStr;
HUMediaInfoStruct		HUMediaInfoStr;
uint8_t	InnerCANMsgSendflag;
uint8_t 	SegSendDataBuffer[100];

void CANbus_InnerInit(void)
{
	HUInnerCycleMsg.CAN_Id = CAN_ID_INNER;
	HUInnerCycleMsg.CANMsgId = CAN_TXID_INNER_HU_510;
	HUInnerCycleMsg.CANMsgDlc = 8;

	HUInnerCycleMsg.Data[0] = 0x38;
	HUInnerCycleMsg.Data[1] = 0xfc;
	HUInnerCycleMsg.Data[2] = 0x00;
	HUInnerCycleMsg.Data[3] = 0xfc;
	HUInnerCycleMsg.Data[4] = 0x00;	
	HUInnerCycleMsg.Data[5] = 0x00;
	HUInnerCycleMsg.Data[6] = 0x00;
	HUInnerCycleMsg.Data[7] = 0x00;

	HUInnerMsgBak.AccStatus = 0;
	HUInnerMsgBak.ControlMode = 0x0;
	HUInnerMsgBak.IllOn = 0;
	HUInnerMsgBak.SysStatus = 0x7;
	HUInnerMsgBak.IllLevel = 0x3f;
	HUInnerMsgBak.RadioBand = 0;
	HUInnerMsgBak.Reverse = 0;
	HUInnerMsgBak.DtvCmd = 0;
	HUInnerMsgBak.IllType = 0;
	HUInnerMsgBak.Language = 0;
	HUInnerMsgBak.MediaCmd = 0;
	HUInnerMsgBak.MediaMode = 0;
	HUInnerMsgBak.MediaPlayStatus = 0;
	HUInnerMsgBak.MediaType = 0;
	HUInnerMsgBak.RadioStatus = 0;
	HUInnerMsgBak.SourceType = 0;
	HUInnerMsgBak.Volume = 0x3f;

	HUMediaInfoStr.CurNo = 0x3fff;
	HUMediaInfoStr.TotalNo = 0x3fff;
	HUMediaInfoStr.PlaySecond = 0x3f;
	HUMediaInfoStr.PlayMinute = 0x3ff;
	HUMediaInfoStr.TotalSecond = 0x3f;
	HUMediaInfoStr.TotalMinute = 0x3ff;

	InnerCANMsgSendflag = 0;
	
	CANSeg_InitParam();
}

void CANbus_InnerFCPLostHandler(void)
{
	CANKeyStateStruct *pCANkey = pCAN_GetCANkeyState();
	pCANkey->keyValue = CK_NONE;
	pCANkey->keyState = 0;
}

void CANbus_InnerRHDLostHandler(uint8_t dir)
{
	if(dir == 0)
	{
		//
	}
	else if(dir == 1)
	{
		//
	}
}

void CANbus_InnerTimerHandler(void)
{
	CANSeg_TimerHandler();

	if(InnerTimerStr.DTV>0)
	{
		InnerTimerStr.DTV--;
		if(InnerTimerStr.DTV == 0)
		{
			//DTV lost has been dealed. reference CANbus_InnerLoop()
		}
	}
	if(InnerTimerStr.FCP>0)
	{
		InnerTimerStr.FCP--;
		if(InnerTimerStr.FCP == 0)
		{
			CANbus_InnerFCPLostHandler();
		}
	}
	if(InnerTimerStr.LRHD>0)
	{
		InnerTimerStr.LRHD--;
		if(InnerTimerStr.LRHD == 0)
		{
			CANbus_InnerRHDLostHandler(0);
		}
	}
	if(InnerTimerStr.RRHD>0)
	{
		InnerTimerStr.RRHD--;
		if(InnerTimerStr.RRHD == 0)
		{
			CANbus_InnerRHDLostHandler(1);
		}
	}
}

void CANbus_InnerReqSendCallBack(uint32_t TxMsgId)
{
	if(TxMsgId == CAN_TXID_INNER_HU_510)
	{
		if(InnerCANMsgSendflag == 1)			//req refresh
		{
			InnerCANMsgSendflag = 2;			//send msg
		}
		else if(InnerCANMsgSendflag == 2)
		{
			InnerCANMsgSendflag = 0;
			HUInnerMsgBak.DtvCmd = 0;
			HUInnerCycleMsg.Data[2] &= ~0x1f; 
			CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
		}
	}
}

void CANbus_SendApuCANState(uint8_t state)
{
	CANStateDataStruct *pstr = 	pCAN_GetCANSysStateStr();

	if(state == 0)		/* Deal done, idle state */
	{
		pstr->State &= ~0x01;
	}
	else				/* Busy state */
	{
		pstr->State |= 0x01;
	}
	CANTask_SendApiData(OMS_CAN_TX_SYS,OP_CAN_TX_CAN_STATE, 0);
}

void CANbus_InnerWriteAccStatus(uint8_t status)
{
	if(HUInnerMsgBak.AccStatus != status)
	{
		HUInnerMsgBak.AccStatus = status;
		HUInnerCycleMsg.Data[0] &= ~0xc0; 
		HUInnerCycleMsg.Data[0] |= (status<<6);
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}

void CANbus_InnerWriteSysStatus(uint8_t status)
{
	if(HUInnerMsgBak.SysStatus != status)
	{
		HUInnerMsgBak.SysStatus = status;
		HUInnerCycleMsg.Data[0] &= ~0x38; 
		HUInnerCycleMsg.Data[0] |= (status<<3);
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}

void CANbus_InnerWriteIllStatus(uint8_t ill)
{
	if(HUInnerMsgBak.IllOn != ill)
	{
		HUInnerMsgBak.IllOn = ill;
		HUInnerCycleMsg.Data[0] &= ~0x04; 
		HUInnerCycleMsg.Data[0] |= (ill<<2);
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}

void CANbus_InnerWriteControlMode(uint8_t mode)
{
	HUInnerCycleMsg.Data[0] &= ~0x03; 
	HUInnerCycleMsg.Data[0] |= mode;
	CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
}

void CANbus_InnerWriteIllLevel(uint8_t level)
{
	if(HUInnerMsgBak.IllLevel!= level)
	{
		HUInnerMsgBak.IllLevel= level;
		HUInnerCycleMsg.Data[1] &= ~0xfc; 
		HUInnerCycleMsg.Data[1] |= (level<<2);
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}

void CANbus_InnerWriteRadioBand(uint8_t band)
{
	if(HUInnerMsgBak.RadioBand!= band)
	{
		HUInnerMsgBak.RadioBand = band;
		HUInnerCycleMsg.Data[1] &= ~0x02; 
		HUInnerCycleMsg.Data[1] |= (band<<1);
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}
void CANbus_InnerWriteReverseStatus(uint8_t status)
{
	if(HUInnerMsgBak.Reverse != status)
	{
		HUInnerMsgBak.Reverse = status;
		HUInnerCycleMsg.Data[1] &= ~0x01; 
		HUInnerCycleMsg.Data[1] |= status;
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}

void CANbus_InnerWriteLanguage(uint8_t type)
{
	HUInnerCycleMsg.Data[2] &= ~0xe0; 
	HUInnerCycleMsg.Data[2] |= (type<<5);
	CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
}

void CANbus_InnerWriteDtvCmd(uint8_t cmd)
{	
	InnerCANMsgSendflag = 1;
	HUInnerCycleMsg.Data[2] &= ~0x1f; 
	HUInnerCycleMsg.Data[2] |= cmd;
	CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	SegTrans_Dbg(_T("Send DTV cmd: %d\n", cmd));
}


void CANbus_InnerWriteVolume(uint8_t volume)
{
	if(HUInnerMsgBak.Volume != volume)
	{
		HUInnerMsgBak.Volume = volume;
		HUInnerCycleMsg.Data[3] &= ~0xfc; 
		HUInnerCycleMsg.Data[3] |= (volume<<2);
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}

void CANbus_InnerWriteRadioStatus(uint8_t status)
{
	if(HUInnerMsgBak.RadioStatus != status)
	{
		HUInnerMsgBak.RadioStatus = status;
		HUInnerCycleMsg.Data[4] &= ~0xe0; 
		HUInnerCycleMsg.Data[4] |= (status<<5);
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}

void CANbus_InnerWriteSourceType(uint8_t type)
{
	if(HUInnerMsgBak.SourceType != type)
	{
		HUInnerMsgBak.SourceType = type;
		HUInnerCycleMsg.Data[5] &= ~0xf0; 
		HUInnerCycleMsg.Data[5] |= (type<<4);
		CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
	}
}

static void CANbus_InnerWriteRadioFreqInfo(void)
{
	CanMsgStruct TxMsg;
	uint16_t temp;
	uint8_t flag = 0;
	TxMsg.CAN_Id = CAN_ID_INNER;
	TxMsg.CANMsgId = CAN_TXID_INNER_HU_515;
	TxMsg.CANMsgDlc = 8;

	if(TUNER_BAND_FM)
	{
		temp = (TUNER_CURRENT_FREQ-6500)/10;
		TxMsg.Data[0] = (temp>>1)&0xff;
		TxMsg.Data[1] = 0xff;
		if((temp&0x01) == 0)
		{
			TxMsg.Data[1] &=~0x80;
		}
		TxMsg.Data[2] = 0xf0;
		flag = 1;
	}
	else if(TUNER_BAND_AM)
	{
		temp = TUNER_CURRENT_FREQ-531;
		TxMsg.Data[0] = 0xff;
		TxMsg.Data[1] = (temp>>4)&0x7f;
		TxMsg.Data[1] |= 0x80;
		TxMsg.Data[2] = (temp<<4)&0xf0;
		flag = 1;
	}

	TxMsg.Data[3] = 0x00;
	TxMsg.Data[4] = 0x00;
	TxMsg.Data[5] = 0x00;
	TxMsg.Data[6] = 0x00;
	TxMsg.Data[7] = 0x00;

	if(flag)
	{
		CANbus_AppLayerSendOneShotMsg(&TxMsg);
	}
	
}

void CANbus_InnerWriteRadioInfo(void)
{
	if(TUNER_BAND_FM)
	{
		CANbus_InnerWriteRadioBand(0);
	}
	else if(TUNER_BAND_AM)
	{

		CANbus_InnerWriteRadioBand(1);
	}
	
	CANbus_InnerWriteRadioFreqInfo();
}

static void CANbus_InnerSendMediaInfo(void)
{
	CanMsgStruct MediaInfoMsg;
	uint8_t  temp;
	
	MediaInfoMsg.CANMsgDlc = 8;
	MediaInfoMsg.CANMsgId = CAN_TXID_INNER_HU_516;
	MediaInfoMsg.CAN_Id = CAN_ID_INNER;
	MediaInfoMsg.Data[0] = (HUMediaInfoStr.CurNo>>6)&0xff;
	MediaInfoMsg.Data[1] = (HUMediaInfoStr.CurNo<<2) &0xff;
	MediaInfoMsg.Data[2] = (HUMediaInfoStr.TotalNo>>6) &0xff;
	MediaInfoMsg.Data[3] = (HUMediaInfoStr.TotalNo<<2) &0xff;
	temp = HUMediaInfoStr.PlaySecond<<2;
	temp |= (HUMediaInfoStr.PlayMinute>>8)&0x03;
	MediaInfoMsg.Data[4] = temp;
	MediaInfoMsg.Data[5] = HUMediaInfoStr.PlayMinute & 0xff;

	temp = HUMediaInfoStr.TotalSecond<<2;
	temp |= (HUMediaInfoStr.TotalMinute>>8)&0x03;
	MediaInfoMsg.Data[6] = temp;
	MediaInfoMsg.Data[7] = HUMediaInfoStr.TotalMinute & 0xff;
	
	CANbus_AppLayerSendOneShotMsg(&MediaInfoMsg);
	
}

void CANbus_InnerWritePlayInfo(uint8_t *pData)
{
	HUMediaInfoStr.CurNo =  (pData[1]<<8)|pData[0];
	HUMediaInfoStr.TotalNo=  (pData[3]<<8)|pData[2];
	CANbus_InnerSendMediaInfo();
}


void CANbus_InnerWritePlayTime(uint8_t *pData)
{
	HUMediaInfoStr.PlayMinute = (pData[2]<<8)|pData[1];
	HUMediaInfoStr.PlaySecond = pData[0];
	HUMediaInfoStr.TotalSecond = pData[3];
	HUMediaInfoStr.TotalMinute =  (pData[5]<<8)|pData[4];
	CANbus_InnerSendMediaInfo();
}

void CANbus_InnerWriteMediaTitle(uint8_t *pData)
{
	if(SegTransTxCtlInfo.Routine != SEG_TRANS_IDLE)
	{
		return;
	}
	CANbus_SendApuCANState(1);
	
	Memory8Copy(SegSendDataBuffer, pData+2, pData[1]);
	SegTransTxCtlInfo.MsgId = CAN_TXID_INNER_HU_517;
	SegTransTxCtlInfo.Routine = SEG_TRANS_TX_FF;
	SegTransTxCtlInfo.SpecialMark = 0x00;
	SegTransTxCtlInfo.TimeParam = SEG_TX_TIME_DEFAULT;
	SegTransTxCtlInfo.TotalDataLength = pData[1];
	SegTransTxCtlInfo.pDataBuffer = SegSendDataBuffer;
	SegTransTxCtlInfo.CurTransDataNum = 0;
}
/****************************************************************************
 * @function	CANbus_InnerStartSendMsg
 * @brief  	HU start send inner periodic message
 * @param  	flag
 * @retval 	null
 * @attention:  null
****************************************************************************/
void CANbus_InnerStartSendMsg(uint8_t flag)
{
	HUInnerCycleMsg.CAN_Id = CAN_ID_INNER;
	HUInnerCycleMsg.CANMsgId = CAN_TXID_INNER_HU_510;
	HUInnerCycleMsg.CANMsgDlc = 8;

	CANbus_AppLayerSendPeriodicMsg(&HUInnerCycleMsg, CAN_TX_INNER_CYCLE);
}

/****************************************************************************
 * @function	CANbus_InnerDTVHandler
 * @brief  	DTV CAN BUS message handler
 * @param  	pRxMsg: received message
 * @retval 	null
 * @attention:  null
****************************************************************************/
void CANbus_InnerDTVHandler(CanMsgStruct *pRxMsg)
{
	if(pRxMsg->CANMsgDlc!=8)
	{
		return;
	}
	if(pRxMsg->CANMsgId == CAN_RXID_INNER_DTV_0)
	{
		DTVStateInfoStruct* pState = pCAN_GetDTVStateData();
		uint8_t temp;
		uint8_t flag = 0;
		if(pState == NULL)
		{
			return;
		}
		if(!pState->Exist)
		{
			pState->Exist = 1;
			flag = 1;
		}
		if(pState->Broadcast != (pRxMsg->Data[0]>>7))
		{
			pState->Broadcast = (pRxMsg->Data[0]>>7);
			flag = 1;
		}
		if(pState->CurrentStationIndex != (pRxMsg->Data[1]>>3))
		{
			pState->CurrentStationIndex = (pRxMsg->Data[1]>>3);
			flag = 1;
		}
		temp = (pRxMsg->Data[0]>>1)&0x03;
		if(pState->StationType != temp)
		{
			pState->StationType = temp;
			flag = 1;
		}
		temp = (pRxMsg->Data[0]>>3)&0x03;
		if(pState->Signal != temp)
		{
			pState->Signal = temp;
			flag = 1;
		}
		temp = (pRxMsg->Data[2]>>3)&0x1f;
		if(pState->TotalStationNum != temp)
		{
			pState->TotalStationNum = temp;
			flag = 1;
		}
		temp = (pRxMsg->Data[0]>>5)&0x03;
		if(pState->WorkMode != temp)
		{
			pState->WorkMode = temp;
			flag = 1;
		}
		if(flag)
		{
			CANTask_SendApiData(OMS_CAN_TX_DTV,OP_CAN_TX_DTV_STATE, 0);
		}
	}
	else if(pRxMsg->CANMsgId == CAN_RXID_INNER_DTV_LIST)
	{
		CANSeg_ReceiveMsgHook(pRxMsg);
	}
	else if(pRxMsg->CANMsgId == CAN_RXID_INNER_DTV_CA)
	{
		CANSeg_ReceiveMsgHook(pRxMsg);
	}
	else if(pRxMsg->CANMsgId == CAN_RXID_INNER_DTV_CAST)
	{
		CANSeg_ReceiveMsgHook(pRxMsg);
	}
	else if(pRxMsg->CANMsgId == CAN_RXID_INNER_DTV_VER)
	{
		//version information
		uint8_t temp;
		DTVVersionStruct*ptr = pCAN_GetDTVVersionData();

		temp = (pRxMsg->Data[0]>>4);
		ptr->ModuleVersion[0] = temp+'A';
		temp = pRxMsg->Data[0]&0x0f;
		ptr->ModuleVersion[1] = temp+'0';
		ptr->ModuleVersion[2] = '.';
		temp = (pRxMsg->Data[1]>>4);
		ptr->ModuleVersion[3] = temp+'0';
		//--------------------------------//
		temp = (pRxMsg->Data[1]&0x0f);
		ptr->BoxVersion[0] = temp+'A';
		temp = pRxMsg->Data[2]>>4;
		ptr->BoxVersion[1] = temp+'0';
		ptr->BoxVersion[2] = '.';
		temp = (pRxMsg->Data[2]&0x0f);
		ptr->BoxVersion[3] = temp+'0';
	}
}

ExtMediaDataStruct*	pCAN_GetExtDtvInfoData(void)
{
	return (&CAN_ExtDtvInfoStr);
}

void CANbus_InnerSendExtDataToApu(SegTransCtlStruct *pStr)
{
	switch(pStr->MsgId)
	{
		case CAN_RXID_INNER_DTV_LIST:
			//CAN_ExtDtvInfoStr.GID = OMS_CAN_TX_DTV;
			CAN_ExtDtvInfoStr.SID = OP_CAN_TX_DTV_LIST;
			CAN_ExtDtvInfoStr.Ctl.length = 2;
			CAN_ExtDtvInfoStr.Ctl.Data[0] = pStr->SpecialMark;
			CAN_ExtDtvInfoStr.Ctl.Data[1] = pStr->SpiTransCtlBk.NeedTransSize;
			CAN_ExtDtvInfoStr.Info.pData = pStr->pDataBuffer+pStr->SpiTransCtlBk.CurPoint;
			CAN_ExtDtvInfoStr.Info.length = pStr->SpiTransCtlBk.NeedTransSize;
			CAN_ExtDtvInfoStr.LENGTH = CAN_ExtDtvInfoStr.Ctl.length+CAN_ExtDtvInfoStr.Info.length+2;
			CANTask_SendApiData(OMS_CAN_TX_DTV,CAN_ExtDtvInfoStr.SID, 1);  // 强制发送
			InnerCAN_Dbg(_T("Send DTV list\n"));
			break;
		case CAN_RXID_INNER_DTV_CA:
			//CAN_ExtDtvInfoStr.GID = OMS_CAN_TX_DTV;
			CAN_ExtDtvInfoStr.SID = OP_CAN_TX_DTV_CA;
			CAN_ExtDtvInfoStr.Ctl.length = 1;
			CAN_ExtDtvInfoStr.Ctl.Data[0] = pStr->SpiTransCtlBk.NeedTransSize;
			CAN_ExtDtvInfoStr.Info.pData = pStr->pDataBuffer+pStr->SpiTransCtlBk.CurPoint;
			CAN_ExtDtvInfoStr.Info.length = pStr->SpiTransCtlBk.NeedTransSize;
			CAN_ExtDtvInfoStr.LENGTH = CAN_ExtDtvInfoStr.Ctl.length+CAN_ExtDtvInfoStr.Info.length+2;
			CANTask_SendApiData(OMS_CAN_TX_DTV,CAN_ExtDtvInfoStr.SID, 0);
			InnerCAN_Dbg(_T("Send DTV CA\n"));
			break;
		case CAN_RXID_INNER_DTV_CAST:
			//CAN_ExtDtvInfoStr.GID = OMS_CAN_TX_DTV;
			CAN_ExtDtvInfoStr.SID = OP_CAN_TX_DTV_CAST;
			CAN_ExtDtvInfoStr.Ctl.length = 5;
			CAN_ExtDtvInfoStr.Ctl.Data[0] = pStr->TotalDataLength &0xff;
			CAN_ExtDtvInfoStr.Ctl.Data[1] = (pStr->TotalDataLength>>8) &0xff;
			CAN_ExtDtvInfoStr.Ctl.Data[2] = pStr->SpiTransCtlBk.TotalPart;
			CAN_ExtDtvInfoStr.Ctl.Data[3] = pStr->SpiTransCtlBk.CurPart;
			CAN_ExtDtvInfoStr.Ctl.Data[4] = pStr->SpiTransCtlBk.NeedTransSize;
			CAN_ExtDtvInfoStr.Info.pData = pStr->pDataBuffer+pStr->SpiTransCtlBk.CurPoint;
			CAN_ExtDtvInfoStr.Info.length = pStr->SpiTransCtlBk.NeedTransSize;
			CAN_ExtDtvInfoStr.LENGTH = CAN_ExtDtvInfoStr.Ctl.length+CAN_ExtDtvInfoStr.Info.length+2;
			CANTask_SendApiData(OMS_CAN_TX_DTV,CAN_ExtDtvInfoStr.SID, 0);
			InnerCAN_Dbg(_T("Send DTV Cast\n"));
			break;
		default:
			break;
	}

}

uint8_t CANbus_SegSendMsg(SegTransCtlStruct *pStr)
{
	CanMsgStruct TxMsg;
	uint8_t RetVal = 0;

	TxMsg.CANMsgDlc = 8;
	TxMsg.CANMsgId = pStr->MsgId;
	TxMsg.CAN_Id = CAN_ID_INNER;
	
	if(pStr->CurTransDataNum == 0)
	{
		pStr->FrameIndex = 0;
		pStr->CurTransDataNum = 2;
		TxMsg.Data[0] = 0;
		TxMsg.Data[1] = 0;
		TxMsg.Data[2] = (pStr->TotalDataLength>>8)&0xff;
		TxMsg.Data[3] = pStr->TotalDataLength &0xff;
		TxMsg.Data[4] = pStr->SpecialMark;
		TxMsg.Data[5] = pStr->TimeParam;
		TxMsg.Data[6] = pStr->pDataBuffer[0];
		TxMsg.Data[7] = pStr->pDataBuffer[1];
	}
	else
	{
		uint8_t temp = (pStr->TotalDataLength) - (pStr->CurTransDataNum);
		pStr->FrameIndex++;
		TxMsg.Data[0] = (pStr->FrameIndex>>8) & 0xff;
		TxMsg.Data[1] = pStr->FrameIndex & 0xff;
		if(temp>6)
		{
			Memory8Copy(&TxMsg.Data[2],  pStr->pDataBuffer+ pStr->CurTransDataNum, 6);
			pStr->CurTransDataNum += 6;	
		}
		else
		{
			CANbus_SendApuCANState(0);
			Memory8Copy(&TxMsg.Data[2],  pStr->pDataBuffer+ pStr->CurTransDataNum, temp);
			FillU8Memory(&TxMsg.Data[2+temp], 6-temp, 0x00);
			pStr->CurTransDataNum = pStr->TotalDataLength;
			RetVal = 1;
		}
	}
	CANbus_AppLayerSendOneShotMsg(&TxMsg);

	return RetVal;
}

void CANbus_InnerReqSendMsg(uint32_t MsgId, uint16_t index)
{
	uint8_t flag = 0;
	CanMsgStruct TxMsg;
	TxMsg.CANMsgDlc = 8;
	TxMsg.CANMsgId = CAN_TXID_INNER_HU_518;
	TxMsg.CAN_Id = CAN_ID_INNER;
	
	TxMsg.Data[1] = (index>>8)&0xff;
	TxMsg.Data[2] = index&0xff;
	TxMsg.Data[3] = 0x00;
	TxMsg.Data[4] = 0x00;
	TxMsg.Data[5] = 0x00;
	TxMsg.Data[6] = 0x00;
	TxMsg.Data[7] = 0x00;
	InnerCAN_Dbg(_T("\nInner ReqReSend!\n"));
	switch(MsgId)
	{
		case CAN_RXID_INNER_DTV_CAST:
			TxMsg.Data[0] = 0x15;
			flag = 1;
			break;
		case CAN_RXID_INNER_DTV_CA:
			TxMsg.Data[0] = 0x16;
			flag = 1;
			break;
		case CAN_RXID_INNER_DTV_LIST:
			if(SegTransRxCtlInfo.SpecialMark <= 0x14)
			{
				TxMsg.Data[0] = SegTransRxCtlInfo.SpecialMark;
				flag = 1;
			}
			break;
		default:
			break;
	}
	if(flag)
	{
		CANbus_AppLayerSendOneShotMsg(&TxMsg);
	}
	
}
/****************************************************************************
 * @function	CANbus_InnerFCPHandler
 * @brief  	FCP (Front Control Panel) CAN BUS message handler
 * @param  	pRxMsg: received message
 * @retval 	null
 * @attention:  null
****************************************************************************/
void CANbus_InnerFCPHandler(CanMsgStruct *pRxMsg)
{
	//按键值说明
	/*
	00 01 02 03 04 05 06 07  序号:		
	40 -- -- -- -- -- -- --  FM/AM: 	
	10 -- -- -- -- -- -- --  MEDIA: 	
	-- 40 -- -- -- -- -- --  NAVI:		
	-- 10 -- -- -- -- -- --  TEL: 		
	-- 04 -- -- -- -- -- --  MAIN:
	-- -- -- 10 -- -- -- --  出碟:		
	-- -- 40 -- -- -- -- --  上1曲短: 
	-- -- 80 -- -- -- -- --  上1曲短: 
	-- -- 10 -- -- -- -- --  下1曲长: 
	-- -- 20 -- -- -- -- --  下1曲长: 
	-- 01 -- -- -- -- -- --  DISP:		
	-- -- -- -- -- -- 1F --  VOL+:		
	-- -- -- -- -- -- 1D --  VOL-:		
	-- -- 04 -- -- -- -- --  MUTE:		
	-- -- 08 -- -- -- -- --  POWER: 	
	*/
	CarAVMDataStruct *pData = pCAN_GetAVMData();
	uint32_t CANkeyValue1 = (pRxMsg->Data[3] << 24) |(pRxMsg->Data[2] << 16) | \
						(pRxMsg->Data[1] << 8)	|(pRxMsg->Data[0]); 
	
	uint8_t 	CANkeyValue2 =	pRxMsg->Data[5];

	
	CANKeyStateStruct *pCANkey = pCAN_GetCANkeyState();
	FCPVersionStruct*ptr = pCAN_GetFCPVersionData();
	if(pRxMsg->CANMsgDlc!=8)
	{
		return;
	}

	pCANkey->keyState = 1;
	//InnerCAN_Dbg(_T("CANkeyValue1: %d\n", CANkeyValue1));

	if((Reverse_Flag)&&(CANkeyValue1!=(1<<18))&&(CANkeyValue1!= 0))
	{
		return;
	}

	switch(CANkeyValue1)
	{
		case 1<<0:	// VOL -
			CANTask_SendKnobInfo(1, 0, 1);
			pCANkey->keyState = 0;
			pCANkey->keyValue = CK_NONE;
			break;
			
		case 1<<2:	//VOL +
			CANTask_SendKnobInfo(1, 1, 1);
			pCANkey->keyState = 0;
			pCANkey->keyValue = CK_NONE;
			break;
			
		case 1<<4:	//MEDIA
			if(pData->CarAVMReq == 1)
			{
				CANUser_SetAvmOutCmd();
				//return;
			}
			pCANkey->keyValue = CK_MEDIA;
			break;
			
		case 1<<6:	//BAND
			if(pData->CarAVMReq == 1)
			{
				CANUser_SetAvmOutCmd();
				//return;
			}
			pCANkey->keyValue = CK_FMAM;
			break;
			
		case 1<<8:	//DISP
			if(pData->CarAVMReq == 1)
			{
				//CANUser_SetAvmOutCmd();
				return;
			}
			pCANkey->keyValue = CK_DISP;
			break;
			
		case 1<<10: 	//MAIN
			pCANkey->keyValue = CK_MAIN_MENU;
			break;
			
		case 1<<12: 	//TEL
			pCANkey->keyValue = CK_TEL;
			break;
				
		case 1<<14: 	//NAVI
			if(pData->CarAVMReq == 1)
			{
				CANUser_SetAvmOutCmd();
				//return;
			}
			pCANkey->keyValue = CK_NAVI;
			break;
			
		case 1<<16: 	//OneKey
			pCANkey->keyValue = CK_NAVI_ONEKEY;
			break;
			
		case 1<<18: 	//long power
			pCANkey->keyValue = CK_POWER; 
			break;
			
		case 1<<20: 	//short press: NEXT
			pCANkey->keyValue = CK_NEXT;
			break;
			
		case 1<<22: 	//short press: preview
			pCANkey->keyValue = CK_PRE;
			break;
			
		case 1<<24: 	//short press: SCAN
			pCANkey->keyValue = CK_SCAN;
			break;
			
		case 1<<26: 	//long press: TONE
			pCANkey->keyValue = CK_AUDIO;
			break;
			
		case 1<<28: 	//short press: EJECT
			pCANkey->keyValue = CK_EJECT;
			break;
			
		case 1<<30: 	//long press:SETUP_MENU
			pCANkey->keyValue = CK_SETUP;
			break;
			
		//旋钮处理
		case 0:
			switch(CANkeyValue2)
			{
				case 0x01:
				CANTask_SendKnobInfo(1, 1, 1);
				break;
				
				case 0x02:
				CANTask_SendKnobInfo(1, 0, 1);
				break;
			}
			pCANkey->keyValue = CK_NONE;
			pCANkey->keyState = 0;
			break;
			
		default:
			pCANkey->keyValue = CK_NONE;
			pCANkey->keyState = 0;
			break;
	}
	
	if(( (ptr->VerHighByte-'0')!=pRxMsg->Data[7]>>4)||((ptr->VerLowByte-'0')!=pRxMsg->Data[7]&0x0f))
	{
		//version information
		uint8_t temp;
		temp = (pRxMsg->Data[7]>>4);
		ptr->VerHighByte=temp+'0';
		temp = pRxMsg->Data[7]&0x0f;
		ptr->VerLowByte=temp+'0';
		CANTask_SendApiData(OMS_CAN_TX_KCP,OP_CAN_TX_KCP_VER, 0);
	}
}



void CANbus_InnerSourceSwitchCmd(uint8_t cmd)
{
	
}
void CANbus_InnerVolumeCmd(uint8_t cmd)
{
	uint8_t keyValue = CK_NONE;
	if(cmd == 1)
	{
		keyValue = CK_VOL_INC;
	}
	else if(cmd == 2)
	{
		keyValue = CK_VOL_DEC;
	}
	else if(cmd == 3)
	{
		keyValue = CK_MUTE;
	}
	if(keyValue != CK_NONE)
	{
		 _SendFullMsgToHMI(MS_INPUT_KEY,OP_KEY_ACTION_SREL,keyValue,5,1,0);
	}
}
void CANbus_InnerBandCmd(uint8_t cmd)
{

}

void CANbus_InnerRadioCmd(uint8_t cmd)
{
	uint8_t keyValue = CK_NONE;
	if(cmd == 1)
	{
		keyValue = CK_SEEK_UP;
	}
	else if(cmd == 2)
	{
		keyValue = CK_SCAN;
	}
	else if(cmd == 3)
	{
		keyValue = CK_AS;
	}
	else if(cmd == 4)
	{
		keyValue = CK_NEXT;
	}
	else if(cmd == 5)
	{
		keyValue = CK_PRE;
	}
	if(keyValue != CK_NONE)
	{
		 _SendFullMsgToHMI(MS_INPUT_KEY,OP_KEY_ACTION_SREL,keyValue,5,1,0);
	}

}

void CANbus_InnerMediaCmd(uint8_t cmd)
{
	uint8_t keyValue = CK_NONE;
	switch(cmd)
	{
		case 1:
			keyValue = CK_PLAY;
			break;
		case 2:		/*PAUSE */
			break;
		case 3:
			keyValue = CK_NEXT;
			break;
		case 4:
			keyValue = CK_PRE;
			break;
		case 5:
			keyValue = CK_FF;
			break;
		case 6:
			keyValue = CK_FB;
			break;
		case 7:
			keyValue = CK_EJECT;
			break;
		case 8:		/*FOLDER RANDOM */
			keyValue = CK_RDM;
			break;
		case 9:		/*ALL RANDOM */
			keyValue = CK_RDM;
			break;
		case 0x0A:		/*repeat ONE*/
			keyValue = CK_RPT;
			break;
		default:
			break;
	}
	
	if(keyValue != CK_NONE)
	{
		 _SendFullMsgToHMI(MS_INPUT_KEY,OP_KEY_ACTION_SREL,keyValue,5,1,0);
	}

}
void CANbus_InnerReqResendCmd(CanMsgStruct *pMsg)
{
	uint8_t cmd = pMsg->Data[0];
	uint16_t frame =  (pMsg->Data[1]<<8) | pMsg->Data[2];
}
/****************************************************************************
 * @function	CANbus_InnerRHDHandler
 * @brief  	RHD (Rear HeaD rest) CAN BUS message handler
 * @param  	pRxMsg: received message
 * @retval 	null
 * @attention:  null
****************************************************************************/
void CANbus_InnerRHDHandler(CanMsgStruct *pRxMsg)
{
	if(pRxMsg->CANMsgDlc!=8)
	{
		return;
	}
	if((pRxMsg->CANMsgId == CAN_RXID_INNER_LRHD_0) ||
	    (pRxMsg->CANMsgId == CAN_RXID_INNER_RRHD_0))
	{
		uint8_t cmd = 0;
		cmd = pRxMsg->Data[0]>>4;			/*source choose */
		if(cmd != 0)
		{
			CANbus_InnerSourceSwitchCmd(cmd);
		}
		cmd = (pRxMsg->Data[1]>>5) &0x03;	/*volume change */
		if(cmd != 0)
		{
			CANbus_InnerVolumeCmd(cmd);
		}

		cmd = (pRxMsg->Data[1]>>3) &0x03;	/*Band change */
		if(cmd != 0)
		{
			CANbus_InnerBandCmd(cmd);
		}

		cmd = pRxMsg->Data[1] &0x07;		/*Radio control command */
		if(cmd != 0)
		{
			CANbus_InnerRadioCmd(cmd);
		}

		cmd = (pRxMsg->Data[4]>>3) &0x1f;	/*Media control command */
		if(cmd != 0)
		{
			CANbus_InnerMediaCmd(cmd);
		}
	}
	else
	{
		CANbus_InnerReqResendCmd(pRxMsg);
	}
}

void CANbus_InnerLoop(void)
{
	uint8_t RadioStatusBak = 0xff;
	if(InnerTimerStr.DTV==0)
	{
		DTVStateInfoStruct* pState = pCAN_GetDTVStateData();
		#if DTV_DYNAMIC_CHK_EN			/*DTV dynamic code */
		if(pState->Exist)
		{
			DTVVersionStruct*ptr = pCAN_GetDTVVersionData();
			pState->Exist = 0;
			CANbus_NetLayerClearFilterBuff(CAN_RXID_DTV_FILTER);
			CANbus_NetLayerClearFilterBuff(CAN_RXID_DTV_VER_FILTER);
			CANTask_SendApiData(OMS_CAN_TX_DTV,OP_CAN_TX_DTV_STATE, 0);

			ptr->BoxVersion[0] = '-';
			ptr->BoxVersion[1] = '-';
			ptr->BoxVersion[2] = '-';
			ptr->BoxVersion[3] = '-';
			ptr->ModuleVersion[0] = '-';
			ptr->ModuleVersion[1] = '-';
			ptr->ModuleVersion[2] = '-';
			ptr->ModuleVersion[3] = '-';
		}
		#else
		/*if(!pState->Exist)			// default DTV is exist state.
		{
			pState->Exist = 1;
			CANTask_SendApiData(OMS_CAN_TX_DTV,OP_CAN_TX_DTV_STATE, 0);
		}*/
		#endif
		InnerTimerStr.DTV = TIMER_2000MS;
	}
	CANSeg_Main();

	if(TunerGetSysState() == TUNER_SYS_RUN)
	{
		if(RadioStatusBak != sTuner.uSeekState.SsTotal)
		{
			RadioStatusBak = sTuner.uSeekState.SsTotal;
			if(sTuner.uSeekState.SsTotal == 0)
			{
				CANbus_InnerWriteRadioStatus(4);
			}
			else if(sTuner.uSeekState.sSsBitMap.bSeek)
			{
				CANbus_InnerWriteRadioStatus(1);
			}
			else if(sTuner.uSeekState.sSsBitMap.bAutoMemSeek)
			{
				CANbus_InnerWriteRadioStatus(2);
			}
			else if(sTuner.uSeekState.sSsBitMap.bAutoScan)
			{
				CANbus_InnerWriteRadioStatus(3);
			}
		}
	}
	else
	{
		CANbus_InnerWriteRadioStatus(0);
	}
}
#endif
#endif

