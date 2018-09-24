#ifndef CAN_NM_INTERFACE_H
#define CAN_NM_INTERFACE_H

#define NM_MSG_SEND_IDLE			0
#define NM_MSG_SEND_REQ			1
#define NM_MSG_SEND_END			2

#define CAN_NMMSG_BUFF_NUM	5

typedef struct
{
	uint8_t CAN_Id;
	CANAPP_MODE_ENUM 		opMode;
	uint8_t MsgSendStatus	:2;
	uint8_t FirstPowerOnFlag	:1;
	uint8_t BusOff            		:1;
	uint8_t RealSleep			:1;
	uint8_t Wakeup			:1;
	uint8_t Reserved			:2;
	uint8_t SleepCnt;
}NM_VAR_STRUCT;

extern NM_VAR_STRUCT   NM_NetNode;

extern Can_StdMsg_Typedef	GMsg_NM;
extern  void    NM_WriteMsgBuff(CanMsgStruct *pRxMessage);
extern void 	NM_InterfaceInit(void);
extern void 	NM_AdpRoutine(uint8_t CANCh);
extern void 	NM_AppMsgHandler(uint8_t CANCh);
extern uint8_t IL_CanHM_Hardwave_Init(uint8_t gCANHardwareState);
extern uint8_t IL_CanNMSendMsg(Can_StdMsg_Typedef  NM_Msg);

#endif

