#include "..\config\inc.h"
#include "media_driver.h"

#ifdef MDI_COMM_TYPE_UART

tMEDIA_LINKER_BLOCK   l_tMediaLinkerCB; 

#define D_MEDIA_DRV_MSG_QUE_DEEP   40

#define _MEDIA_DRV_TASK_TIMING_    _4MS_
#define _MEDIA_DRV_CORE_TIMING_    _1MS_
#define _MEDIA_DRV_TASK_TICK_      _set_timing_xms_base_core_tick(_MEDIA_DRV_TASK_TIMING_)
#define _MEDIA_DRV_CORE_TICK_      _set_timing_core_tick_num(_MEDIA_DRV_CORE_TIMING_)

#define _set_timing_Xms_base_MDdriver_task(x)		(x/_MEDIA_DRV_CORE_TIMING_)

tTASK_CTRL_BLOCK l_tMediaDrvTaskCB;
uint8_t seriSendEn = ENABLE;

/******************************************************************************/

typedef enum
{
	COMM_STEP_IDLE,
	COMM_STEP_HEAD1,
	COMM_STEP_HEAD2,
	COMM_STEP_RCV,
	COMM_STEP_SEND_REQ,
	COMM_STEP_SEND,
	COMM_STEP_INIT,
	COMM_STEP_END,
}eCOMM_STEP;

typedef struct
{
	uint8_t   Port;
	uint8_t   RcvStep;
	uint8_t   TotalLength;
	uint8_t    RcvDataCnt;
	uint16_t    ChkSum;
	uint8_t   TimeOut;
	uint8_t   Timer;
	uint8_t*  pRcvBuffer;
	uint8_t   RcvBufferSize;
}CommRecvManagerStr;

typedef struct
{
	uint8_t    Port;
	uint8_t    SendStep;
	uint8_t    seriSendEn;
	uint8_t    Timer;
	uint8_t*	pSendBuff;
	uint8_t	SendBuffSize;
	uint8_t	TotalLength;
	uint8_t    CurSendNum;
}CommSendManagerStr;

uint8_t USART3_RxBuff[COMM_RXMSG_SIZE] ;

CommRecvManagerStr		HostRcvBuffManager;
CommSendManagerStr		HostSendBuffManager;

uint8_t MediaRxByteUartBuffer[MDI_RX_RINGBUFF_SIZE];
ByteBufferMangerStruct MediaRxHostByteBufferManager;

uint8_t IsrRxByteUartBuffer[MDI_ISR_RXBUFF_SIZE];
ByteBufferMangerStruct UartIsrRxByteBufferManager;



void Uart_RcvHostMsgInit(void)
{
	HostRcvBuffManager.Timer = 0;
	HostRcvBuffManager.Port = 0;
	HostRcvBuffManager.pRcvBuffer = USART3_RxBuff;
	HostRcvBuffManager.RcvBufferSize = COMM_RXMSG_SIZE;
	HostRcvBuffManager.RcvStep = COMM_STEP_IDLE;
	HostRcvBuffManager.ChkSum = 0x00;
	HostRcvBuffManager.TimeOut = _set_timing_Xms_base_MDdriver_task(10);

	/*创建串口消息帧字节BUFF */
	ByteDataBufferInit(&MediaRxHostByteBufferManager, &MediaRxByteUartBuffer, sizeof(MediaRxByteUartBuffer));
	/*创建串口字节流字节BUFF */
	ByteDataBufferInit(&UartIsrRxByteBufferManager, &IsrRxByteUartBuffer, sizeof(IsrRxByteUartBuffer));
}

void Uart_SendHostInit(void)
{
	HostSendBuffManager.Port = 0;
	HostSendBuffManager.CurSendNum= 0;
	HostSendBuffManager.pSendBuff = NULL;//USART3_TxBuff;
	HostSendBuffManager.SendBuffSize = COMM_TXMSG_SIZE;
	HostSendBuffManager.SendStep = COMM_STEP_IDLE;
}

void isrMDI_LinkerRX(void)
{
	uint8_t Data = UA3RX;

	if(UA3STR & 0x07)
	{
		//have some error!
		UA3STR &= ~0x07;
		return;
	}
	ByteDataBufferWriteByte(&UartIsrRxByteBufferManager, Data);
}


void MDI_RxByteDeal(void)
{
	uint8_t Data;
	
	while(!ByteDataBufferReadByte(&UartIsrRxByteBufferManager, &Data))
	{
		
		HostRcvBuffManager.Timer = HostRcvBuffManager.TimeOut;
		HostRcvBuffManager.ChkSum ^= Data;

		switch(HostRcvBuffManager.RcvStep)
		{
			case COMM_STEP_IDLE:
				if(Data == COMM_Head_1)
				{
					HostRcvBuffManager.ChkSum = Data;
					HostRcvBuffManager.RcvStep = COMM_STEP_HEAD1;
				}
				break;
			case COMM_STEP_HEAD1:
				if(Data == COMM_Head_2)
				{
					HostRcvBuffManager.RcvStep = COMM_STEP_RCV;
					HostRcvBuffManager.RcvDataCnt = 2;
					HostRcvBuffManager.TotalLength = 0;
				}
				else if(Data != COMM_Head_1)
				{
					HostRcvBuffManager.RcvStep = COMM_STEP_IDLE;
				}
				break;
			case COMM_STEP_RCV:
				
				if(HostRcvBuffManager.RcvDataCnt == 4)
				{
					if((Data>=7) &&(Data<COMM_RXMSG_SIZE))
					{
						HostRcvBuffManager.TotalLength = Data;
					}
					else
					{
						md_printf(_T("RCV len error,data =%x\n",Data));
						HostRcvBuffManager.RcvStep = COMM_STEP_IDLE;
						break;
					}
				}
				
				HostRcvBuffManager.pRcvBuffer[HostRcvBuffManager.RcvDataCnt-2] = Data;
				HostRcvBuffManager.RcvDataCnt ++;
				
				if(HostRcvBuffManager.RcvDataCnt== HostRcvBuffManager.TotalLength)
				{
					uint16_t tempData = (HostRcvBuffManager.pRcvBuffer[4]<<8)|HostRcvBuffManager.pRcvBuffer[3];
					HostRcvBuffManager.pRcvBuffer[4] = 0x00;
					HostRcvBuffManager.pRcvBuffer[3] = 0x00;
					HostRcvBuffManager.ChkSum = OS_CalCrc16(HostRcvBuffManager.pRcvBuffer, HostRcvBuffManager.TotalLength-2);
					
					if(HostRcvBuffManager.ChkSum == tempData)
					{
						ByteDataBufferWriteMsg(HostRcvBuffManager.pRcvBuffer, HostRcvBuffManager.TotalLength-2, &MediaRxHostByteBufferManager);
					}
					else
					{
						md_printf(_T("@@@@@@@@@@@!!Rcv = %x, Real = %x\n",tempData, HostRcvBuffManager.ChkSum));
					}
					HostRcvBuffManager.RcvStep = COMM_STEP_IDLE;
				}
				break;
			default:
				HostRcvBuffManager.RcvStep = COMM_STEP_IDLE;
				break;
		}
	}
}

void isrMDI_LinkerTX(void)
{
	seriSendEn = 1;
}

void MDI_LinkerInit(uint8_t bEn)
{
	v850_uart3_Init();
	if(bEn)
	{
		Uart_RcvHostMsgInit();
		Uart_SendHostInit();
		v850_uart3_Start();
	}
	else
	{
		v850_uart3_Stop();
	}
}

void MDI_LinkerRestart(void)
{
	v850_uart3_Init();
	v850_uart3_Start();
}
/*
 * 重新对发送缓冲区中的数据进行校验填充
 */
void MDI_ReChkPackage(void)
{
	uint16_t cCRC;
	uint8_t  cLen = l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_PKG_LEN];
	l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_CHKS1] = 0x00;
	l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_CHKS2] = 0x00;

	l_tMediaLinkerCB.tTxCB.cPkgID++;
	l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_PID]  = l_tMediaLinkerCB.tTxCB.cPkgID;
	
	cCRC = OS_CalCrc16(&l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_PID], cLen-2);

	l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_CHKS1] = cCRC&0xff;
	l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_CHKS2] = (cCRC>>8)&0xff;
}

void MDI_LinkerSendTxPackage(void)
{
	v850_uart3_Send( l_tMediaLinkerCB.tTxCB.a_cBuf, l_tMediaLinkerCB.tTxCB.cLen);
	l_tMediaLinkerCB.tLinkDevBlock.iTimer = 0;
}

void MDI_LinkerSendAck(uint8_t pid, uint8_t ack)
{
#if MDI_COMM_MODE_ACK_NONE == 0
	uint8_t buffer[7];
	uint16_t cCRC = 0;

	buffer[0] = D_MCU_DEV_ID;
	buffer[1] = D_APU_DEV_ID;
	buffer[2] = pid;
	buffer[3] = ack;
	buffer[4] = 0x07;
	buffer[5] = 0x00;
	buffer[6] = 0x00;
	
	cCRC = OS_CalCrc16(&buffer[2], 5);
	buffer[5] = cCRC&0xff;
	buffer[6] = (cCRC>>8)&0xff;

	v850_uart3_Send( buffer, 7);
#endif
}

/*handle the package from the CPU */
void MDI_LinkerRxPackageHandle(void)
{
	ByteBufferMangerStruct * pBuffer = &MediaRxHostByteBufferManager;
	uint8_t flag = 0;

	if(pBuffer->MsgNum >0)
	{
		uint8_t length;
		if(ByteDataBufferReadMsg(l_tMediaLinkerCB.tRxCB.a_cBuf, &length, pBuffer))
		{
		        #define _PID    l_tMediaLinkerCB.tRxCB.a_cBuf[0]
		        #define _GID    l_tMediaLinkerCB.tRxCB.a_cBuf[1]
		        #define _SID    l_tMediaLinkerCB.tRxCB.a_cBuf[5]
		        #define _DATA   &l_tMediaLinkerCB.tRxCB.a_cBuf[6]
		        #define _LEN    (l_tMediaLinkerCB.tRxCB.a_cBuf[2]-8) //除去包头长度
		        
			uint8_t  cGid = _GID - GID_APU2MCU_BASE;
		#if 1
			uint8_t cnt = 0;
			md_printf(_T("\nRX:"));
			for(cnt = 0; cnt<length; cnt++)
				md_printf(_T("-%x", l_tMediaLinkerCB.tRxCB.a_cBuf[cnt]));
			md_printf(_T("\n"));
		#endif
		      if(length>COMM_RXMSG_SIZE)
		      	{
				media_printf(_T("\nParce length  = %x, Error Occure\n", length));
			}
			MDI_RxPackgeHook(_GID,_SID,_DATA,_LEN);
			if(cGid < g_tMediaRxPkgAnalyzeFunctionTab.cNum)
		        {
		            _SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_LINKREQ,NULL);
		            if(l_tMediaLinkerCB.tLinkDevBlock.eState == LINKER_STATE_WAIT_RCV_ACK)
		            {
		            	//在等待应答期间，接收到数据帧，重发上一数据帧
		           	if(_PID == l_tMediaLinkerCB.tRxCB.cPrevPkgID)
		            	{
    					MDI_LinkerSendAck(_PID, D_LINKER_ACK);
					flag = 1;
				}
		            	MDI_LinkerSendTxPackage();
			     }
		            if(_PID != l_tMediaLinkerCB.tRxCB.cPrevPkgID)
		            {
		                fMEDIA_RXDATA_ANALYZE p_fRxAnalyze = g_tMediaRxPkgAnalyzeFunctionTab.pa_fFuntionTab[cGid];
		                
		                l_tMediaLinkerCB.tRxCB.cPrevPkgID = _PID;
		                
		                if(p_fRxAnalyze)
					p_fRxAnalyze(_SID,_DATA,_LEN);
		            }
		            if(!flag)
		            	{
					MDI_LinkerSendAck(_PID, D_LINKER_ACK);
				}
		        }
			 else
			 {
			 	switch(_GID)
			 	{
					case D_LINKER_ACK:		//ACK
					case D_LINKER_NSUPPORT:		//NACK(not support)
						if(l_tMediaLinkerCB.tLinkDevBlock.eState == LINKER_STATE_WAIT_RCV_ACK)
						{
							if(l_tMediaLinkerCB.tTxCB.cPkgID == _PID)
							{
								l_tMediaLinkerCB.tLinkDevBlock.eState = LINKER_STATE_IDLE;
								l_tMediaLinkerCB.tTxCB.cPkgID ++;
								l_tMediaLinkerCB.tTxCB.cReTxCnt = 0;
								md_printf(_T("RCV ACK OK\n"));
							}
							else
							{
								md_printf(_T("RCV ACK PID err: data = %x, need data = %x\n", _PID, l_tMediaLinkerCB.tTxCB.cPkgID));							
							}
						}
						else
						{
							md_printf(_T("RCV ACK --(no need)--\n"));
						}
						break;
					case D_LINKER_CHKERR:		//NACK(PARITY NG)
						MDI_ReChkPackage();
						MDI_LinkerSendTxPackage();
						break;
					case D_LINKER_BUSY:		//NACK(busy)
						l_tMediaLinkerCB.tLinkDevBlock.iTimer = 0;
						break;
					default:
						break;
				}
			 }
			 #undef _PID
		        #undef _GID
		        #undef _SID
		        #undef _DATA
		        #undef _LEN
		}
	}
}

void MDI_Printf(uint8_t* Data)
{
    uint8_t i = 0;
    media_printf(_T("------TX GID:%x SID:%x ",Data[TBBID_GID],Data[TBBID_SID]));
    for(i=0; i<(Data[TBBID_PKG_LEN]-8);i++)
    {
        media_printf(_T("D[%d]:%x ",i+8,Data[i+8]));
    }
    media_printf(_T("\n"));
}


void MDI_LinkerLoadDataToTxBuf(uint8_t gid,uint8_t sid,void* buf)		// bolte
{    
    MDI_TxPackgeHook(gid,sid,buf);
    if(gid < g_tMediaTxPkgGenerateFunctionTab.cNum)
    {
        fMEDIA_TXDATA_ANALYZE p_fTxGenerate = g_tMediaTxPkgGenerateFunctionTab.pa_fFuntionTab[gid];
        if(p_fTxGenerate)
        {
            uint8_t* ptx_buff = l_tMediaLinkerCB.tTxCB.a_cBuf;
            uint8_t cLen; 

            /*Get the number of what you want to send*/
            ptx_buff[TBBID_SID] = sid;
            cLen= p_fTxGenerate(sid,buf,&(ptx_buff[TBBID_SID]));
            if(cLen) 
            { 
		    uint16_t cCRC = 0;
		    cLen += 7;
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_SDEV] = D_MCU_DEV_ID;
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_RDEV] = D_APU_DEV_ID;
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_PID]  = l_tMediaLinkerCB.tTxCB.cPkgID;
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_GID]  = gid+GID_MCU2APU_BASE;
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_PKG_LEN] = cLen;
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_CHKS1] = 0x00;
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_CHKS2] = 0x00;

		    cCRC = OS_CalCrc16(&l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_PID], cLen-2);
		   
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_CHKS1] = cCRC&0xff;
		    l_tMediaLinkerCB.tTxCB.a_cBuf[TBBID_CHKS2] = (cCRC>>8)&0xff;
		    l_tMediaLinkerCB.tTxCB.cLen = cLen;
		    MDI_LinkerSendTxPackage();
		   
		#if MDI_COMM_MODE_ACK_NONE
		     l_tMediaLinkerCB.tLinkDevBlock.eState = LINKER_STATE_IDLE;
		#else
		     if(l_tMediaCB.uDevFlag.field.bTestMode)
		     {
			    l_tMediaLinkerCB.tLinkDevBlock.eState = LINKER_STATE_IDLE;
		     }
		     else
		     {
			    l_tMediaLinkerCB.tTxCB.cReTxCnt = 0;
			    l_tMediaLinkerCB.tLinkDevBlock.eState = LINKER_STATE_WAIT_RCV_ACK;
		     }
		#endif
            }
        } 
    }     
}




void MDI_LinkerDriverProc(void)
{             
    MDI_LinkerRxPackageHandle();                                       
    
    switch(l_tMediaLinkerCB.tLinkDevBlock.eState)
    {
        case LINKER_STATE_IDLE: 
		l_tMediaLinkerCB.tTxCB.cReTxCnt = 0;
        break;
	 case LINKER_STATE_WAIT_RCV_ACK:
		if(l_tMediaLinkerCB.tLinkDevBlock.iTimer> _set_timing_Xms_base_MDdriver_task(300))
		{
			l_tMediaLinkerCB.tLinkDevBlock.iTimer = 0;
			MDI_LinkerRestart();
			MDI_LinkerSendTxPackage();
			 l_tMediaLinkerCB.tTxCB.cReTxCnt ++;
			 if( (l_tMediaLinkerCB.tTxCB.cReTxCnt &0x07) == 0)
			 {
			 	// warn : used for debug.
			 	if(SysWorkStatusGrp.SysCommSpySwitch)
			 	{
					_SendFullMsgToAudio(MS_AUDIO_CMD,OP_AUD_BEEP_REQ,BEEP_TYPE_KEY_ACK,BEEP_ON,0,0);
			 	}
			 }
			 if(l_tMediaLinkerCB.tTxCB.cReTxCnt>=1000)
			 {
				//ERROR: TX DRIVER ERROR!!!!!!!!!
				l_tMediaLinkerCB.tLinkDevBlock.eState = LINKER_STATE_ERROR;
				l_tMediaLinkerCB.tTxCB.cReTxCnt = 0;
			 }
			 md_printf(_T("comm error: no ACK\n"));
		}
	 break;

        /*Timing err handle*/
        case LINKER_STATE_ERROR:  
	      _SendMsgToMedia(MS_SYS_APU_INFO,OP_DEV_STATE_RESET,NULL);
            md_printf(_T("Reset APU!\n"));
            l_tMediaLinkerCB.tLinkDevBlock.eState = LINKER_STATE_IDLE;
        break;

        /*Packege end,set delay for every packege*/
        case LINKER_STATE_END:
        default:      
		l_tMediaLinkerCB.tLinkDevBlock.eState = LINKER_STATE_IDLE;
	break;
    }
}

/*Communication init.it will init the buffer and the spi device*/
uint8_t MDI_DriverInit(void)
{
	API_MemClear((uint8_t *)&l_tMediaLinkerCB,sizeof(tMEDIA_LINKER_BLOCK));

	l_tMediaLinkerCB.tRxCB.cPrevPkgID = 0xff;
	l_tMediaLinkerCB.tLinkDevBlock.eState = LINKER_STATE_IDLE;
	l_tMediaLinkerCB.tLinkDevBlock.cErrNum = 0;
	MDI_LinkerInit(ON);
	return TRUE;
}

/*Stop communication.Init SPI line and stop spi hw!*/
uint8_t MDI_DriverDInit(void)
{
	MDI_LinkerInit(OFF);
	return TRUE;
}

/*Media task project*/
void MDI_DriverTask(EVENT iEvt,eTASK_STATE eState)
{
    if(eState == TASK_STATE_RUNNING)
    {
        if(iEvt & EVT_TASK_TICK_READY)
        {
           if(LINKER_STATE_IDLE == l_tMediaLinkerCB.tLinkDevBlock.eState)
            {
                if(iEvt & EVT_MSG_READY)
                {
                    tMSG_BUF tMsg;
                    if(QUE_ERR_NONE == OS_GetMsgDir(&l_tMediaDrvTaskCB,&tMsg))
                    {
                        MDI_LinkerLoadDataToTxBuf((uint8_t)tMsg.Id,(uint8_t)(tMsg.iSid),tMsg.uData.p_cData);
                    }
		     
                }
            }
        }
	if(iEvt & EVT_CORE_TICK_READY)
	{
		MDI_RxByteDeal();
		l_tMediaLinkerCB.tLinkDevBlock.iTimer ++;
		/*UART package inner bytes space inspector */
		if(HostRcvBuffManager.Timer>0)
		{
			HostRcvBuffManager.Timer--;
			if(!HostRcvBuffManager.Timer)
			{
				if(HostRcvBuffManager.RcvStep != COMM_STEP_IDLE)
				{
					HostRcvBuffManager.RcvStep = COMM_STEP_IDLE;
					//WARN: RCV timeout. start next package receive.
					 md_printf(_T("UART data receive timeout!\n"));
				}
			}
		}
	 }
        MDI_LinkerDriverProc();
    }
   
}
tRING_QUE l_tMediaDrvMsgQue;
tMSG_BUF la_tMediaDrvMsgBuf[D_MEDIA_DRV_MSG_QUE_DEEP];


const tTASK_BLOCK l_tMediaDrvTCB = {
    "MEDIA DRIVER",
    _MEDIA_DRV_TASK_TICK_,
    _MEDIA_DRV_CORE_TICK_,
    MDI_DriverTask,
    MDI_DriverInit,
    MDI_DriverDInit,
};

bool MDI_DriverCreate(void)
{

     return OS_TaskCreate(TASK_ID_MEDIA_DRV,
                         &l_tMediaDrvTaskCB,
                         &l_tMediaDrvTCB,
                         &l_tMediaDrvMsgQue,
                         la_tMediaDrvMsgBuf,
                         D_MEDIA_DRV_MSG_QUE_DEEP);
}

#endif

