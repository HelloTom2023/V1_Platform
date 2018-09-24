#ifndef  _MEDIA_DRIVER_H_
#define  _MEDIA_DRIVER_H_

#ifdef _MEDIA_DRIVER_C_
#define _MEDIA_DRIVER_
#else
#define _MEDIA_DRIVER_   extern
#endif

#if D_DEBUG_MEDIA_DRV && D_PRINT_EN
#define md_printf(x) x
#else
#define md_printf(x)
#endif
#define MDI_COMM_TYPE_UART

#define MDI_COMM_MODE_ACK_NONE		1	//在没有APU的情况下，MCU不需要APU的应答既可以工作。

#define TASK_ID_MEDIA_DRV          0xf1

#define GID_MCU2APU_BASE            0x10
#define GID_APU2MCU_BASE            0xB0

#define	COMM_TXMSG_SIZE		200 
#define	COMM_RXMSG_SIZE		100//64
#define  MDI_RX_RINGBUFF_SIZE	(COMM_RXMSG_SIZE*2)

#define MDI_ISR_RXBUFF_SIZE	100


#define COMM_Head_1   	0xa0
#define COMM_Head_2   	0x55

#define RX_INDEX_PKT		0
#define RX_INDEX_GID		1
#define RX_INDEX_LEN		2
#define RX_INDEX_CHK		3
#define RX_INDEX_SID		4
#define RX_INDEX_DATA		5

/*byte in rxbuff id and name*/
#define RBBID_CHKS         0
#define RBBID_SID          1
#define RBBID_D0           2
#define RBBID_D1           3
#define RBBID_D2           4
#define RBBID_D3           5

/*byte in txbuff id and name*/
#define TBBID_SDEV         0
#define TBBID_RDEV         1
#define TBBID_PID          2			//package sequence number
#define TBBID_GID          3
#define TBBID_PKG_LEN      4
#define TBBID_CHKS1         5
#define TBBID_CHKS2         6
//#define TBBID_DATA_LEN     7
#define TBBID_SID          7
#define TBBID_DATA          8


/*ACK data define*/
#define D_LINKER_ACK            0xff
#define D_LINKER_CHKERR           0xf0
#define D_LINKER_NSUPPORT       0xf3
#define D_LINKER_BUSY           0xfc


#define D_APU_DEV_ID       0xA0
#define D_MCU_DEV_ID       0x55

#define D_ACK_LEN            2
#define D_BUF_DEEP           3
#define D_MAX_IDX            (D_BUF_DEEP - 1)
#define D_DUMMY_DATA         0xff
#define D_CRC_BASE           0xff

typedef enum{
    LINKER_HW_NOERR,
    LINKER_HW_ERR_CS,               //cs 不能控制
    LINKER_HW_ERR_DATA_IRQ,              //irq 时序错乱。
    LINKER_HW_ERR_TRANS_DATA,       //irq 启动传输应答失败
    LINKER_HW_ERR_DATA_END,         //传输数据无结束信号
    LINKER_HW_ERR_ACK_IRQ,
    LINKER_HW_ERR_TANS_ACK,        //irq 启动传输应答失败

    LINKER_HW_ERR_ACK_END,          //ack 传输无结束信号
    LINKER_HW_ERR_NOWAIT_ACK,           //从端不等读ACK而直接申请发送数据
    LINKER_HW_ERR_DATA_DISARRAY,    //数据混乱错位
    LINKER_HW_ERR_NUM
    
}eLINKER_HWERR_TYPE;                  //硬件错误类型


typedef struct {
    uint8_t         cByteCnt;
    uint8_t         cLen;
    uint8_t         cCRC;
    uint8_t         cPkgCnt;
    uint8_t         cPrevPkgID;
    uint8_t         a_cBuf[COMM_RXMSG_SIZE];
    
}tLINKER_RX_CTRL_BLOCK;

typedef struct {
    uint8_t         cPkgCnt;
    uint8_t         cPkgID;
    uint8_t         a_cBuf[COMM_TXMSG_SIZE];
    uint8_t         cLen;
    uint16_t         cReTxCnt;
    
}tLINKER_TX_CTRL_BLOCK;

typedef enum{
    LINKER_STATE_IDLE,
    LINKER_STATE_SEND,
    LINKER_STATE_RCV,
    LINKER_STATE_WAIT_RCV_ACK, 
    LINKER_STATE_ERROR,
    LINKER_STATE_END,
    LINKER_STATE_NUM

}eLINKER_STATE;

typedef struct {
    eLINKER_STATE      eState;
    uint8_t            cErrNum;
    uint16_t           iTimer;
    uint8_t            cReqAckNum;
    uint8_t            cHwErr;
    uint8_t            cHwErrNum;
    
}tLINKER_DEV_BLOCk;



typedef struct {
    tLINKER_DEV_BLOCk     tLinkDevBlock;
    tLINKER_RX_CTRL_BLOCK tRxCB;
    tLINKER_TX_CTRL_BLOCK tTxCB;

}tMEDIA_LINKER_BLOCK;

extern 	tTASK_CTRL_BLOCK l_tMediaDrvTaskCB;
extern     tMEDIA_LINKER_BLOCK   l_tMediaLinkerCB; 

_MEDIA_DRIVER_	uint8_t MDI_DriverInit(void);
_MEDIA_DRIVER_ 	void    isrMDI_LinkerRX             (void);
_MEDIA_DRIVER_ 	void    isrMDI_LinkerTX             (void);



#endif

