/***************************************************************
****************************************************************/
/*Can NM_OSEK Macro  Definitions*/
/***************************************************************/
#ifndef _IL_CANNM_MACRO_H_
#define _IL_CANNM_MACRO_H_

/**********************NM_OSEK_Macro.h************************/


/*调试定义*/
#define IL_CANNM_XIELC_STATE_FEEDBAKE                  ((unsigned char)1)
	/***********NM运行参数宏定义***********/
#define IL_CANNM_BASE_ADDRESS					0x400
#define IL_CANNM_LOCAL_ID						0x411
#define IL_CANNM_TTX_TIMEOUT					20
#define IL_CANNM_TTYP_TIMEOUT					100
#define IL_CANNM_TMAX_TIMEOUT					260
#define IL_CANNM_TERROR_TIMEOUT				1000
#define IL_CANNM_TWBS_TIMEOUT					1500
#define IL_CANNM_TX_LIMIT						8
#define IL_CANNM_RX_LIMIT						4
#define IL_CANNM_NODE_NUM_MAX					32
	/***********节点检测周期宏定义***********/
#define IL_CANNM_DETECT_NM							0      //检测节点数目

#define IL_CANNM_OFF                  ((unsigned char)0x00)
#define IL_CANNM_ON                   ((unsigned char)0x01)
#define IL_CANNM_SHUTDOWN             ((unsigned char)0x02)
#define IL_CANNM_INIT                 ((unsigned char)0x00)
#define IL_CANNM_AWAKE                ((unsigned char)0x01)

/*OpCode定义*/
#define IL_CANNM_ALIVE_MSG	   				((unsigned char)0x01)
#define IL_CANNM_RING_MSG	   					((unsigned char)0x02)
#define IL_CANNM_LIMPHOME_MSG	   				((unsigned char)0x04)
#define IL_CANNM_IND_LIMPHOME_MSG	   			((unsigned char)0x14)
#define IL_CANNM_IND_RING_MSG	  				((unsigned char)0x12)
#define IL_CANNM_ACK_RING_MSG	   				((unsigned char)0x32)
#define IL_CANNM_IND_ALIVE_MSG	   			((unsigned char)0x11)
#define IL_CANNM_BIT_IND_MSG	   				((unsigned char)0x10)
#define IL_CANNM_BIT_RING_MSG	   				((unsigned char)0x02)

/*其它宏定义*/
#define IL_CANNM_SOURCE_ID	   				((unsigned char)IL_CANNM_LOCAL_ID)
#define IL_CANNM_SEND_MSG_DLC					((unsigned char)0x08)

/*各种状态宏定义(sILCanNMNodeState)*/
#define IL_CANNM_NORMAL_RUN					((unsigned char)0x01)
#define IL_CANNM_NORMAL_PRESLEEP				((unsigned char)0x02)
#define IL_CANNM_NORMAL_WAITSLEEP				((unsigned char)0x04)
#define IL_CANNM_LIMPHOME_RUN					((unsigned char)0x10)
#define IL_CANNM_LIMPHOME_PRESLEEP			((unsigned char)0x20)
#define IL_CANNM_LIMPHOME_WAITSLEEP			((unsigned char)0x40)

/*硬件状态宏定义*/
#define IL_CANNM_HARDWARE_INIT				((unsigned char)0x01)
#define IL_CANNM_HARDWARE_SLEEP				((unsigned char)0x02)
#define IL_CANNM_HARDWARE_WAKEUP				((unsigned char)0x04)
#define IL_CANNM_HARDWARE_NORMAL				((unsigned char)0x08)

/*定时器设置宏定义*/
#define IL_CANNM_BIT_TIMER_CANCEL				((unsigned char)0x00)
#define IL_CANNM_BIT_TTYP_SET					((unsigned char)0x01)
#define IL_CANNM_BIT_TMAX_SET					((unsigned char)0x02)
#define IL_CANNM_BIT_TERROR_SET				((unsigned char)0x04)
#define IL_CANNM_BIT_TWBS_SET					((unsigned char)0x08)

/*各种状态需运行NM_FUNCTION是的标志*/
#define IL_CANNM_TTYP_TIMEOUT_FLAG									((unsigned char)0x01)
#define IL_CANNM_TMAX_TIMEOUT_FLAG									((unsigned char)0x02)
#define IL_CANNM_TERROR_TIMEOUT_FLAG								((unsigned char)0x04)
#define IL_CANNM_TWBS_TIMEOUT_FLAG									((unsigned char)0x08)
#define IL_CANNM_TRANSMIT_FLAG											((unsigned char)0x11)
#define IL_CANNM_GOTOSLEEP_FLAG											((unsigned char)0x12)
#define IL_CANNM_EXITSLEEP_FLAG											((unsigned char)0x21)

/*接收模块ID*/
#define IL_CANNM_ID_BCM									((unsigned char)0x00)
#define IL_CANNM_ID_IBC									((unsigned char)0x01)
#define IL_CANNM_ID_ESCL									((unsigned char)0x02)
#define IL_CANNM_ID_PEPS									((unsigned char)0x03)

/*CAN网络状态*/
#define IL_CANNM_BCM_BUS_OK										 			(0U)
#define IL_CANNM_BCM_NON_BUS_OFF								 				(1U)
#define IL_CANNM_BCM_BUS_OFF										 			(2U)
#define IL_CANNM_BCM_BUS_ERROR									 			(3U)
#define IL_CANNM_CAN_MODE_INIT										 		(0U)
#define IL_CANNM_CAN_MODE_NORMAL								 				(1U)
#define IL_CANNM_CAN_MODE_NORMALED										 	(2U)
#define IL_CANNM_CAN_MODE_SUCCESS												(3U)
 
#define IL_CANNM_NODE_DETECT_CYCLE_NUM_MAX							(5U)      //检测节点最大丢失次数

/*电源检测*/
#define IL_CANNM_BAT_FAULT_FLAG                         (0U)
#define IL_CANNM_BAT_NORMAL_FLAG                        (1U)

#define IL_CANNM_INIT_DELAY_TIMEOUT                      (120U)

typedef struct
{
  unsigned int Id;   
  unsigned char Dlc;
  unsigned char Data[8];
} Can_StdMsg_Typedef;


typedef volatile struct NM_Merker_struct
{
	unsigned char	Stable;
	unsigned char	Limphome;																							//跛行状态成功发送NM报文标志。
}
IL_CANNM_Merker_TypeDef;

typedef volatile struct NM_Config_struct
{
	unsigned char	Limphome;																							//网络是否处于Limphome状态标志。
}
IL_CANNM_Config_TypeDef;

typedef volatile struct NM_NetWorkStatus_struct
{
	unsigned char	Configurationstable;
	unsigned char	NMactive;
	unsigned char	Bussleep;
	unsigned char  NMStart;                  //网络管理开始运行标志
}
IL_CANNM_NetWorkStatus_TypeDef;


/**********************NM_OSEK_Varible.h************************/

/*************外部定义变量***************/
extern unsigned int		gILTiCanNMBase;
extern unsigned char		gILCanNMMsgTransitFlag;				//成功发送报文标志。
extern unsigned char		gILCanNMLocalWakeupFlag;         //本地唤醒标志；
extern unsigned char 		gILCanNMRemoteWakeupFlag;
extern unsigned char		gILCanNMNormalMsgActive;
extern unsigned char 	        gILCanNMCanBusOff;
extern unsigned char		gILCanNMHasSleeped;	//节点硬件状态，1：硬件初始化，2：睡眠，3：唤醒

extern unsigned int		sILCanNMTimer1ms;                 //NM的1ms定时
extern unsigned char 	sILCanNMTimeoutFlag;       	//Ttyp、Tmax、Terror、Twbs超时标志

/*BUS-OFF*/
extern IL_CANNM_NetWorkStatus_TypeDef gsILCanNMNetWorkStatus;

	/***********节点检测全局变量定义***********/

/*电压检测*/
extern unsigned char		gILCanNMBatFlag;

/**********************NM_OSEK_Function.h************************/

void IL_CanNM_Init(void);                                    //上电初始化时调用
void IL_CanNM_Function_Main(void);								//NM功能主函数，直接放在主函数中
extern  Can_StdMsg_Typedef IL_CanNM_RecMsgSave(void);
extern  unsigned char IL_CanHM_Hardwave_Init(unsigned char gCANHardwareState);

#endif
