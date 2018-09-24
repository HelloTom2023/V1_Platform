/****************************************************************************
* copyright:		JC Coagent Co.ltd.
* filename:		CANbus_SegTrans.h
* Target MCU:		V850SJ3
* Module:
* Summary:		CAN segment transmit data header file
*----------------------------------------------------------------------------
* Author:			zhaowenlong
* version:			V0.1
* Date:			2014-2-24
* Description:		first version
*----------------------------------------------------------------------------
* Modify:			
* version:
* Date:
* Description:
****************************************************************************/
#ifndef _CANBUS_SEGTRANS_
#define _CANBUS_SEGTRANS_

#ifdef  _CAN_SEGTRANS_C
#define _SEGTRANS_ 
#else
#define _SEGTRANS_		extern
#endif

#if  D_PRINT_EN&&D_CANBUS_SEG_DBG_EN
#define SegTrans_Dbg(x)  			x
#else
#define SegTrans_Dbg(x)
#endif

#define SEG_TRANS_IDLE		0
#define SEG_TRANS_TX_FF		1
#define SEG_TRANS_TX_CF		2
#define SEG_TRANS_RX_FF		3
#define SEG_TRANS_RX_CF		4
#define SEG_TRANS_RX_END		5
#define SEG_TRANS_RX_ERR		6
#define SEG_TRANS_TX_REQACK	7

#define SPI_BLOCK_SIZE		64
#define SEG_BUFF_SIZE			(SPI_BLOCK_SIZE<<1)

#define SEG_TX_TIME_DEFAULT	20		/*20 MS */

typedef struct
{
	uint8_t 		TotalPart;
	uint8_t		CurPart;
	uint8_t		CurPoint;
	uint8_t  		Delta;
	uint8_t		NeedTransSize;
}SpiTransStruct;

typedef struct
{
	uint32_t		MsgId;
	uint16_t 		TotalDataLength;
	uint16_t 		FrameIndex;
	uint16_t		CurTransDataNum;
	uint8_t 		SpecialMark;
	uint8_t 		TimeParam;
	uint8_t 		Routine;
	uint16_t 		Timer;
	uint8_t		ReTryCnt;			/* try to transmit counter */
	uint8_t *		pDataBuffer;
	uint8_t		BuffWriteIndex;
	SpiTransStruct	SpiTransCtlBk;
}SegTransCtlStruct;


extern SegTransCtlStruct		SegTransRxCtlInfo;
extern SegTransCtlStruct		SegTransTxCtlInfo;

extern void CANSeg_InitParam(void);
extern void CANSeg_TimerHandler(void);
extern void CANSeg_ReceiveMsgHook(CanMsgStruct *pMsg);
extern void CANSeg_Main(void);
extern uint8_t CANbus_SegSendMsg(SegTransCtlStruct *pStr);

#endif
