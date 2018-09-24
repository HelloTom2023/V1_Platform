#define _CAN_SEGTRANS_C
#include "..\..\..\config\inc.h"

#ifdef CAN_MODULE_ENABLE
#ifdef CAN_INNER_ENABLE
SegTransCtlStruct		SegTransRxCtlInfo;
SegTransCtlStruct		SegTransTxCtlInfo;

uint8_t SegDataRxBuffer[SEG_BUFF_SIZE];
uint8_t SegDataTxBuffer[SEG_BUFF_SIZE];

void CANSeg_InitParam(void)
{
	SegTransRxCtlInfo.Timer = 0;
	SegTransRxCtlInfo.ReTryCnt = 0;
	SegTransRxCtlInfo.Routine = SEG_TRANS_IDLE;
	SegTransRxCtlInfo.BuffWriteIndex = 0;
	SegTransRxCtlInfo.CurTransDataNum = 0;
	SegTransRxCtlInfo.FrameIndex = 0;
	SegTransRxCtlInfo.TotalDataLength = 0;
	SegTransRxCtlInfo.SpiTransCtlBk.TotalPart = 0;
	SegTransRxCtlInfo.SpiTransCtlBk.CurPart = 0;
	SegTransRxCtlInfo.SpiTransCtlBk.CurPoint = 0;
	SegTransRxCtlInfo.SpiTransCtlBk.Delta = 0;
	SegTransRxCtlInfo.SpiTransCtlBk.NeedTransSize = 0;

	SegTransTxCtlInfo.Timer = 0;
	SegTransTxCtlInfo.Routine = SEG_TRANS_IDLE;
}

void CANSeg_TimerHandler(void)
{
	if(SegTransRxCtlInfo.Timer >0)
	{
		SegTransRxCtlInfo.Timer --;
	}
	if(SegTransTxCtlInfo.Timer >0)
	{
		SegTransTxCtlInfo.Timer --;
	}
}


void CANSeg_ReceiveMsgHook(CanMsgStruct *pMsg)
{
	uint16_t temp = (pMsg->Data[0] <<8)|(pMsg->Data[1]);
	
	if(SegTransRxCtlInfo.Routine == SEG_TRANS_IDLE)
	{
		if(temp == 0)
		{
			SegTrans_Dbg(_T("Inner Rcv FirstFrame\n"));
			SegTransRxCtlInfo.FrameIndex = 0;
			SegTransRxCtlInfo.ReTryCnt = 0;
			SegTransRxCtlInfo.MsgId = pMsg->CANMsgId;
			SegTransRxCtlInfo.SpecialMark = pMsg->Data[4];
			SegTransRxCtlInfo.TimeParam = pMsg->Data[5]/TIMER_BASE;
			SegTransRxCtlInfo.Timer = SegTransRxCtlInfo.TimeParam*5;
			SegTransRxCtlInfo.TotalDataLength =  (pMsg->Data[2]<<8)|(pMsg->Data[3]);
			SegTransRxCtlInfo.pDataBuffer = SegDataRxBuffer;
			if(SegTransRxCtlInfo.TotalDataLength>2)
			{
				SegTransRxCtlInfo.SpiTransCtlBk.TotalPart = SegTransRxCtlInfo.TotalDataLength/SPI_BLOCK_SIZE;
				if(SegTransRxCtlInfo.TotalDataLength % SPI_BLOCK_SIZE)
				{
					SegTransRxCtlInfo.SpiTransCtlBk.TotalPart++;
				}
				SegTransRxCtlInfo.SpiTransCtlBk.CurPart = 1;
				SegTransRxCtlInfo.SpiTransCtlBk.CurPoint = 0;
				SegTransRxCtlInfo.SpiTransCtlBk.Delta = 2;
				SegTransRxCtlInfo.CurTransDataNum = 2;
				SegTransRxCtlInfo.Routine = SEG_TRANS_RX_CF;
				Memory8Copy(SegTransRxCtlInfo.pDataBuffer, &pMsg->Data[6], 2);
				SegTransRxCtlInfo.BuffWriteIndex = 2;		//next write buffer position index
			}
			else// if(SegTransRxCtlInfo.TotalDataLength>0)
			{
				SegTransRxCtlInfo.SpiTransCtlBk.TotalPart = 1;
				SegTransRxCtlInfo.SpiTransCtlBk.CurPart = 1;
				SegTransRxCtlInfo.SpiTransCtlBk.CurPoint = 0;
				SegTransRxCtlInfo.SpiTransCtlBk.Delta = SegTransRxCtlInfo.TotalDataLength;
				SegTransRxCtlInfo.CurTransDataNum = SegTransRxCtlInfo.TotalDataLength;
				SegTransRxCtlInfo.Routine = SEG_TRANS_RX_END;
				Memory8Copy(SegTransRxCtlInfo.pDataBuffer, &pMsg->Data[6], SegTransRxCtlInfo.TotalDataLength);
				SegTransRxCtlInfo.BuffWriteIndex = SegTransRxCtlInfo.TotalDataLength;		//next write buffer position index
			}
		}
		else
		{
			CANbus_InnerReqSendMsg(SegTransRxCtlInfo.MsgId, 0);	/*request send current message from the FF.*/
		}
	}
	else if(SegTransRxCtlInfo.Routine == SEG_TRANS_RX_CF)
	{
		if(SegTransRxCtlInfo.MsgId == pMsg->CANMsgId)
		{
			SegTransRxCtlInfo.Timer = SegTransRxCtlInfo.TimeParam*5;
			if(temp == (SegTransRxCtlInfo.FrameIndex+1))
			{
				SegTransRxCtlInfo.FrameIndex = temp;
				SegTrans_Dbg(_T("Inner Rcv Frame:%x%x\n", temp>>8, temp&0xff));
				if((SegTransRxCtlInfo.BuffWriteIndex+6) >= SEG_BUFF_SIZE)
				{
					uint8_t bak = SEG_BUFF_SIZE - SegTransRxCtlInfo.BuffWriteIndex;
					Memory8Copy(&SegTransRxCtlInfo.pDataBuffer[SegTransRxCtlInfo.BuffWriteIndex], &(pMsg->Data[2]), bak);
					Memory8Copy(&SegTransRxCtlInfo.pDataBuffer[0], &(pMsg->Data[2+bak]), 6-bak);
					SegTransRxCtlInfo.BuffWriteIndex = 6-bak;
				}
				else
				{
					Memory8Copy(&SegTransRxCtlInfo.pDataBuffer[SegTransRxCtlInfo.BuffWriteIndex], &(pMsg->Data[2]), 6);
					SegTransRxCtlInfo.BuffWriteIndex += 6;
				}
				SegTransRxCtlInfo.CurTransDataNum  += 6;
				SegTransRxCtlInfo.SpiTransCtlBk.Delta+= 6;
				if(SegTransRxCtlInfo.CurTransDataNum>= SegTransRxCtlInfo.TotalDataLength)
				{
					SegTransRxCtlInfo.CurTransDataNum = SegTransRxCtlInfo.TotalDataLength;
					SegTransRxCtlInfo.Routine = SEG_TRANS_RX_END;
				}
			}
			else if(temp > (SegTransRxCtlInfo.FrameIndex+1))
			{
				SegTrans_Dbg(_T("Inner Rcv Frame:%x%x\n", temp>>8, temp&0xff));
				CANbus_InnerReqSendMsg(SegTransRxCtlInfo.MsgId, SegTransRxCtlInfo.FrameIndex+1);
			}
		}
	}

}

void CANSeg_Main(void)
{
	
	switch(SegTransRxCtlInfo.Routine)
	{
		case SEG_TRANS_IDLE:		// IDLE
			break;
		case SEG_TRANS_RX_FF:
			break;
		case SEG_TRANS_RX_CF:
			if(SegTransRxCtlInfo.Timer == 0)
			{
				// time out handler
				SegTrans_Dbg(_T("Inner Rcv TimeOut\n"));
				SegTransRxCtlInfo.Timer = SegTransRxCtlInfo.TimeParam*5;
				SegTransRxCtlInfo.ReTryCnt++;
				if(SegTransRxCtlInfo.ReTryCnt>5)
				{
					SegTransRxCtlInfo.ReTryCnt = 0;
					SegTransRxCtlInfo.Routine = SEG_TRANS_IDLE;
				}
				else
				{
					CANbus_InnerReqSendMsg(SegTransRxCtlInfo.MsgId, SegTransRxCtlInfo.FrameIndex+1);
				}
			}
			if(SegTransRxCtlInfo.SpiTransCtlBk.Delta>= SPI_BLOCK_SIZE)
			{
				SegTransRxCtlInfo.SpiTransCtlBk.NeedTransSize = SPI_BLOCK_SIZE;
				CANbus_InnerSendExtDataToApu(&SegTransRxCtlInfo);
				SegTransRxCtlInfo.SpiTransCtlBk.CurPart++;		/*add CurPart */
				if(SegTransRxCtlInfo.SpiTransCtlBk.CurPoint ==0)
				{
					SegTransRxCtlInfo.SpiTransCtlBk.CurPoint = SPI_BLOCK_SIZE;
				}
				else
				{
					SegTransRxCtlInfo.SpiTransCtlBk.CurPoint = 0;
				}
				SegTransRxCtlInfo.SpiTransCtlBk.Delta -=SPI_BLOCK_SIZE;
			}
			break;
		case SEG_TRANS_RX_END:
			// when receive an overall message, handler it.
			SegTransRxCtlInfo.SpiTransCtlBk.NeedTransSize = SegTransRxCtlInfo.SpiTransCtlBk.Delta;
			CANbus_InnerSendExtDataToApu(&SegTransRxCtlInfo);
			SegTransRxCtlInfo.Routine = SEG_TRANS_IDLE;
			break;
		case SEG_TRANS_RX_ERR:
			break;
		default:
			SegTransRxCtlInfo.Routine = SEG_TRANS_IDLE;
			break;
	}

	switch(SegTransTxCtlInfo.Routine)
	{
		case SEG_TRANS_IDLE:
			break;
		case SEG_TRANS_TX_FF:	
			CANbus_SegSendMsg(&SegTransTxCtlInfo);
			SegTransTxCtlInfo.Timer  = SEG_TX_TIME_DEFAULT/TIMER_BASE;
			SegTransTxCtlInfo.Routine = SEG_TRANS_TX_CF;
			break;
		case SEG_TRANS_TX_CF:
			if(SegTransTxCtlInfo.Timer == 0)
			{
				if(CANbus_SegSendMsg(&SegTransTxCtlInfo))
				{
					SegTransTxCtlInfo.Routine = SEG_TRANS_IDLE;
				}
				else
				{
					SegTransTxCtlInfo.Timer  = SEG_TX_TIME_DEFAULT/TIMER_BASE;
				}
			}
			break;
		case SEG_TRANS_TX_REQACK:
			break;
		default:
			SegTransTxCtlInfo.Routine = SEG_TRANS_IDLE;
			break;
	}
}

#endif
#endif
