/*
*******************************************************************************
**
**  This device driver was created by Applilet2 for V850ES/Sx3
**  32-Bit Single-Chip Microcontrollers
**
**  Copyright(C) NEC Electronics Corporation 2002 - 2013
**  All rights reserved by NEC Electronics Corporation.
**
**  This program should be used on your own responsibility.
**  NEC Electronics Corporation assumes no responsibility for any losses
**  incurred by customers or third parties arising from the use of this file.
**
**  Filename :	can_drv.c
**  Abstract :	This file implements device driver for CAN module.
**  APIlib :	Applilet2 for V850ES/Sx3 V2.41 [28 Apr. 2008]
**
**  Device :	uPD70F3355
**
**  Compiler :	CA850
**
**  Creation date:	2013-4-23
**  
*******************************************************************************
*/
#define _CAN_MODULE_C
#include "..\..\..\config\inc.h"
#include "..\..\..\Can_V850\VFB_Can_V850.h"

#ifdef CAN_MODULE_ENABLE

#if D_PRINT_EN && D_CANBUS_DRV_DBG_EN
#define	CANDrv_DebugOut(x)		x
#else
#define	CANDrv_DebugOut(x)
#endif


/*  Baud rate setup information */
typedef struct CAN_ChBpsInf {
	uint8_t	CnGMCS;	/* CnGMCS */
	uint8_t	CnBRP;	/* CnBRP */
	uint16_t	CnBTR;	/* CnBTR */
} CAN_ChBpsInf;

/*  Programmable I/O register for CAN macro */
/* aFCAN global register */
typedef struct CAN_GlbRegType
{										/*													(offset) */
	volatile uint16_t		GMCTRL;			/* CAN global macro control register						(+ 0x00) */
	volatile uint8_t			GMCS;			/* CAN global macro clock selection register					(+ 0x02) */
	volatile uint8_t			DummyGlb1;		/* <<< Dummy >>>									(+ 0x03) */
	volatile uint16_t		DummyGlb2;		/* <<< Dummy >>>									(+ 0x04) */
	volatile uint16_t		GMABT;			/* CAN global macro automatic block transmission register		(+ 0x06) */
	volatile uint8_t			GMABTD;			/* CAN global macro automatic block transmission delay register	(+ 0x08) */
} CAN_GlbRegType;

/* aFCAN module register */
typedef struct CAN_ChRegType
{										/*													(offset) */
	volatile uint16_t		MASK1L;			/* CAN module mask 1 register							(+ 0x00) */
	volatile uint16_t		MASK1H;			/* CAN module mask 1 register							(+ 0x02) */
	volatile uint16_t		MASK2L;			/* CAN module mask 2 register							(+ 0x04) */
	volatile uint16_t		MASK2H;			/* CAN module mask 2 register							(+ 0x06) */
	volatile uint16_t		MASK3L;			/* CAN module mask 3 register							(+ 0x08) */
	volatile uint16_t		MASK3H;			/* CAN module mask 3 register							(+ 0x0a) */
	volatile uint16_t		MASK4L;			/* CAN module mask 4 register							(+ 0x0c) */
	volatile uint16_t		MASK4H;			/* CAN module mask 4 register							(+ 0x0e) */
	volatile uint16_t		CTRL;			/* CAN module control register							(+ 0x10) */
	volatile uint8_t		LEC;					/* CAN module last error code register						(+ 0x12) */
	volatile uint8_t		INFO;				/* CAN module information register						(+ 0x13) */
	volatile uint16_t		ERC;				/* CAN module error counter								(+ 0x14) */
	volatile uint16_t		IE;				/* CAN module interrupt enable register						(+ 0x16) */
	volatile uint16_t		INTS;			/* CAN module interupt status register						(+ 0x18) */
	volatile uint8_t		BRP;					/* CAN module bit-rate prescaler register					(+ 0x1a) */
	volatile uint8_t		DummyCh1;			/* <<< Dummy >>>									(+ 0x1b) */
	volatile uint16_t		BTR;				/* CAN bit-rate register									(+ 0x1c) */
	volatile uint8_t		LIPT;				/* CAN module last in-pointer register						(+ 0x1e) */
	volatile uint8_t		DummyCh2;			/* <<< Dummy >>>									(+ 0x1b) */
	volatile uint16_t		RGPT;			/* CAN module receive history list get pointer register			(+ 0x20) */
	volatile uint8_t		LOPT;				/* CAN module last out-pointer register						(+ 0x22) */
	volatile uint8_t		DummyCh3;			/* <<< Dummy >>>									(+ 0x23) */
	volatile uint16_t		TGPT;			/* CAN module transmit history list get pointer register			(+ 0x24) */
	volatile uint16_t		TS;				/* CAN module time dtamp register							(+ 0x26) */
} CAN_ChRegType;

/* aFCAN message buffer register */
typedef struct CAN_MsgRegType
{										/*												(offset) */
	volatile uint8_t		MDATA[8];			/* Message data byte registers (8bit)					(+ 0x00) */
	volatile uint8_t		MDLC;				/* Message data length code register					(+ 0x08) */
	volatile uint8_t		MCONF;				/* Message configuration register						(+ 0x09) */
	volatile uint16_t		MIDL;			/* Message identifier registers							(+ 0x0a) */
	volatile uint16_t		MIDH;			/* Message identifier registers							(+ 0x0c) */
	volatile uint16_t		MCTRL;			/* Message control register							(+ 0x0e) */
	volatile uint8_t		DummyMsg[16];		/* <<< Dummy : You can't delete this member.>>>		(+ 0x10) */
} CAN_MsgRegType;


/* aFCAN global register */
typedef struct CAN_RegBaseAddr
{
	CAN_GlbRegType*		pGlbRegBaseAddr;	/* CAN global register base address */
	CAN_ChRegType*		pChRegBaseAddr;	/* CAN module register base address */
	CAN_MsgRegType*		pMsgRegBaseAddr;	/* CAN message buffer register base address */
} CAN_RegBaseAddr;

/* aFCAN message buffer register type2 (for CnMDATAxxm) */
typedef struct CAN_MsgRegType2
{										/*												(offset) */
	volatile uint16_t		MDATA[4];		/* Message data short registers	(16bit)				(+ 0x00) */
	volatile uint8_t			MDLC;			/* Message data length code register					(+ 0x08) */
	volatile uint8_t			MCONF;			/* Message configuration register						(+ 0x09) */
	volatile uint16_t		MIDL;			/* Message identifier registers							(+ 0x0a) */
	volatile uint16_t		MIDH;			/* Message identifier registers							(+ 0x0c) */
	volatile uint16_t		MCTRL;			/* Message control register							(+ 0x0e) */
	volatile uint8_t			DummyMsg[16];	/* <<< Dummy : You can't delete this member. >>>		(+ 0x10) */
} CAN_MsgRegType2;

/*  [Channel] gcCanChIniMask[] */
/*  [Channel] Number of mask register */
#define	CAN_NUM_OF_MASK	(4)
#define	MSK_MASKH			(0x1fff0000)
#define	MSK_MASKL			(0x0000ffff)

/*  CAN-ID format mode */
#define	CAN_CANID_EXT				(0x80000000)
#define	CAN_CANID_STD_MSK			(0x000007ff)
#define	CAN_CANID_EXT_MSK			(0x1fffffff)


/*  [Channel] _cdc_u1g_ch_ini_int[] */
#define	CAN_INICH_INT_SET_TX		(0x0100)
#define	CAN_INICH_INT_SET_RX		(0x0200)
#define	CAN_INICH_INT_SET_ERRSTS	(0x0400)
#define	CAN_INICH_INT_SET_PRTERR	(0x0800)
#define	CAN_INICH_INT_SET_ARBLST	(0x1000)
#define	CAN_INICH_INT_SET_WAKUP	(0x2000)
#define	CAN_INICH_INT_CLR_TX		(0x0001)
#define	CAN_INICH_INT_CLR_RX		(0x0002)
#define	CAN_INICH_INT_CLR_ERRSTS	(0x0004)
#define	CAN_INICH_INT_CLR_PRTERR	(0x0008)
#define	CAN_INICH_INT_CLR_ARBLST	(0x0010)
#define	CAN_INICH_INT_CLR_WAKUP	(0x0020)

/*  [Message] gcCanBufIniAtr1[] */
#define	CAN_INIMSG_ADDRTYP_USE		(0x01)	/* CnCONFm.MA0-2 */
#define	CAN_INIMSG_MSGTYP_TX		(0x00)	/* CnCONFm.MT0-2 */
#define	CAN_INIMSG_MSGTYP_RX		(0x08)
#define	CAN_INIMSG_MSGTYP_MSK1		(0x10)
#define	CAN_INIMSG_MSGTYP_MSK2		(0x18)
#define	CAN_INIMSG_MSGTYP_MSK3		(0x20)
#define	CAN_INIMSG_MSGTYP_MSK4		(0x28)
#define	CAN_INIMSG_FRMTYP_DAT		(0x00)	/* CnCONFm.RTR */
#define	CAN_INIMSG_FRMTYP_RMT		(0x40)
#define	CAN_INIMSG_OVRWRT			(0x80)	/* CnCONFm.OWS */

/*  [Message] gcCanBufIniAtr2[] */
#define	CAN_INIMSG_IE				(0x80)	/* CnCTRLm.IE(*) */
											/* M_CTRLm.IE(*) */
#define	MSK_MTx				(0x38)
#define	CHK_MTx_TX			(0x00)


/*  [Message] gcCanBufIniAtr2[] */
#define	MSK_DLC				(0x0f)
#define	MSK_IE				(0x80)


/*  [Message] gcCanChIniMacro[] */
#define	MSK_TSEN			(0x0101)
#define	MSK_TSSEL			(0x0202)
#define	MSK_TSLOCK			(0x0404)
#define	MSK_AL				(0x4040)
#define	MSK_CCERC			(0x8000)
#define	MSK_REG_L			(0x00ff)


/*  [Message] gcCanBufIniCanId[] */
#define	MSK_CANIDH			(0xffff0000)
#define	MSK_CANIDL			(0x0000ffff)

/*  CAN data length */
#define	LEN_CANDATA			(8)


/*
 *		CAN register macro code (for aFCAN)
 */
/*  [Register] CnGMCTRL */
#define	MSK_GOM			(0x0001)
#define	CLR_GOM				(0x0001)
#define	SET_GOM				(0x0100)
#define	SET_EFSD			(0x0200)

/*  [Register] CnCTRL */
#define	MSK_OPMODE			(0x0007)
#define	MSK_PSMODE			(0x0018)
#define	CHK_INIT			(0x0000)
#define	CHK_NORM			(0x0001)
#define	CHK_ABT				(0x0002)
#define	CHK_RXONLY			(0x0003)
#define	CHK_SSHT			(0x0004)
#define	CHK_SELF			(0x0005)
#define	SET_INIT				(0x0007)
#define	SET_NORM			(0x0100)
#define   SET_CCERC			(0x8000)
#define   SET_AL				(0x4000)
#define   CLR_PSMODE			(0x0018)
#define   CLR_VALID			(0x0020)

/*  [Register] CnINTS */
#define	MSK_CINTS0			(0x0001)
#define	MSK_CINTS1			(0x0002)
#define	MSK_CINTS2			(0x0004)
#define	MSK_CINTS3			(0x0008)
#define	MSK_CINTS4			(0x0010)
#define	MSK_CINTS5			(0x0020)

/*  [Register] CnINFO */
#define	MSK_RECS			(0x03)
#define	MSK_TECS			(0x0c)
#define	MSK_BOFF			(0x10)

/*  [Register] CnMCTRLm */
#define	MSK_RDY				(0x0001)
#define	CLR_RDY				(0x0001)
#define	SET_RDY				(0x0100)
#define	MSK_TRQ				(0x0002)
#define	CLR_TRQ				(0x0002)
#define	SET_TRQ				(0x0200)
#define	MSK_DN				(0x0004)
#define	CLR_DN				(0x0004)
#define	SET_DN				(0x0400)
#define	CLR_IE				(0x0008)
#define	SET_IE				(0x0800)
#define	CLR_MOW			(0x0010)
#define	MSK_MUC				(0x2000)

/*  [Register] CnMCONFm */
#define	MSK_MAx				(0x07)
#define	CLR_MAx				(0xf8)

/*  CAN status clear macro */
#define	CAN_ERR_CLR_STS				(0x0004)	/* CAN error status */
#define	CAN_ERR_CLR_PRT				(0x0008)	/* CAN protocol error */
#define	CAN_ERR_CLR_ABL				(0x0010)	/* Arbitration lost */
#define	CAN_ERR_CLR_WAK			(0x0020)	/* Wakeup */


/* Infomation of CAN IOR base address */
#define	CAN_STP_PIO_CAN_BASE_ADDR	0x03FEC000

const CAN_RegBaseAddr	gcCanRegBaseAddr[2] = {
	/* Channel 0 */
	{
		/* CAN global register */
		(CAN_GlbRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x0),
		/* CAN module register */
		(CAN_ChRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x40),
		/* CAN message buffer */
		(CAN_MsgRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x100)
	},
	/* Channel 1 */
	{
		/* CAN global register */
		(CAN_GlbRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x600),
		/* CAN module register */
		(CAN_ChRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x640),
		/* CAN message buffer */
		(CAN_MsgRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x700)
	}
	
};

#if 0
#if CAN0_NUM_OF_DRVBUF>32
#error   "CAN0 message number  over the max num!"
#endif
#if CAN1_NUM_OF_DRVBUF>32
#error   "CAN1 message number  over the max num!"
#endif
#endif

/****************************************************************************
 * @function	CANbus_EnableCANTransceiver
 * @brief  	This function eanble the CAN transceiver to enter mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			mode: CAN_TRANSCEIVER_MODE_NORMAL//CAN_TRANSCEIVER_MODE_LISTEN_ONLY
 *				CAN_TRANSCEIVER_MODE_STANDBY//CAN_TRANSCEIVER_MODE_SLEEP
 * @retval 	null
 * @attention   null
****************************************************************************/
void CANbus_EnableCANTransceiver(uint8_t chno, uint8_t mode)
{
	if(chno==0)
	{
		CAN0_Transceiver_WorkModeSel(mode);
	}
	else
	{
		CAN1_Transceiver_WorkModeSel(mode);
	}
}

void    CANbus_SetMaskConfig(CAN_INIT_STRUCT *pInitParam, CAN_MsgRegType2 *pMsgReg)
{
	volatile uint16_t *	pChMaskAddr;
	uint32_t			canbuf_ini_canid;
	uint16_t   		tempValue;
	uint8_t 			i = 0;
	uint8_t                 	Regvalue;

	CAN_MsgRegType2*pCheckRegAddr ;
	
	if(!pInitParam->validFlag)
	{
		return;
	}

	if(pInitParam->can_Id > 1)
	{
		return;
	}

	if(pInitParam->MASKValidNum == 0)
	{
		return;
	}

	if(pInitParam->MASKValidNum > 4 )
	{
		return;
	}
	pCheckRegAddr = (CAN_MsgRegType2*)gcCanRegBaseAddr[pInitParam->can_Id].pMsgRegBaseAddr;
	if((pMsgReg< pCheckRegAddr) ||(pMsgReg>= &pCheckRegAddr[32]))
	{
		return;
	}

	pChMaskAddr =  (volatile uint16_t *)(gcCanRegBaseAddr[pInitParam->can_Id].pChRegBaseAddr);
		
	for(i = 0; i<pInitParam->MASKValidNum; i++)
	{
		tempValue = pInitParam->can_RecvMASK[i];
		*pChMaskAddr++ =  0xffff;			//MASKL
		*pChMaskAddr++ =  ((tempValue<<2)|0x03) & 0x1fff;		//MASKH

		if(i == 0)
		{
			Regvalue = CAN_INIMSG_MSGTYP_MSK1;
		}
		else if(i == 1)
		{
			Regvalue = CAN_INIMSG_MSGTYP_MSK2;
		}
		else if(i == 2)
		{
			Regvalue = CAN_INIMSG_MSGTYP_MSK3;
		}
		else if(i == 3)
		{
			Regvalue = CAN_INIMSG_MSGTYP_MSK4;
		}

		pMsgReg->MCONF = CAN_INIMSG_ADDRTYP_USE | Regvalue | 
				     CAN_INIMSG_FRMTYP_DAT | CAN_INIMSG_OVRWRT;
		pMsgReg->MDLC =1;		/* Set CnMDLCm resister */
		canbuf_ini_canid = (pInitParam->can_RecvFilterCmp[i])<<18;
		pMsgReg->MIDH = (uint16_t)((canbuf_ini_canid & MSK_CANIDH) >> 16);
		pMsgReg->MIDL =  (uint16_t)(canbuf_ini_canid & MSK_CANIDL);

		pMsgReg->MCTRL = (uint16_t)(CLR_MOW | SET_IE | CLR_DN | CLR_TRQ);

		pMsgReg->MCTRL = SET_RDY;	/* Set RDY bit */

		pMsgReg++;
	}
}

uint8_t CANbus_ChRegInit(CAN_INIT_STRUCT *pInitParam)
{
	volatile CAN_ChRegType*	pChRegType;
	volatile CAN_GlbRegType*	pGlbRegType;
	volatile CAN_MsgRegType*	pMsgRegType;
	volatile CAN_MsgRegType2*	pMsgRegTypeBuf;

	CAN_ChBpsInf		BpsBuffer;

	uint8_t	bufno;
	uint8_t    temp;
	uint8_t 	can_id;

	if(!pInitParam->validFlag)
	{
		return 1;
	}

	if(pInitParam->can_Id > 1)
	{
		return 1;
	}
	if(pInitParam->can_BpsType > CAN_BPS_500K)
	{
		return 1;
	}
	if(pInitParam->can_RecvFilterNum>CAN_RCV_FILTER_MAX)
	{
		return 1;
	}

	temp = pInitParam->can_RecvFilterNum + pInitParam->can_SendBuffNum;

	if(temp>32)
	{
		return 1;
	}

	/* Set CAN module register address */
	pChRegType = (volatile CAN_ChRegType*)(gcCanRegBaseAddr[pInitParam->can_Id].pChRegBaseAddr);
	/* Set CAN global register address */
	pGlbRegType = (volatile CAN_GlbRegType*)(gcCanRegBaseAddr[pInitParam->can_Id].pGlbRegBaseAddr);
	/* Set CAN message buffer register address */
	pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[pInitParam->can_Id].pMsgRegBaseAddr);
	
	/* Check init mode */
	if ((pChRegType->CTRL & MSK_OPMODE) != CHK_INIT)
	{
		return 2;
	}
	
	/* Set baudrate */
	switch(pInitParam->can_BpsType)
	{
		case CAN_BPS_100K:
			BpsBuffer.CnBRP = 0x0F;
			BpsBuffer.CnBTR = 0x140d;
			break;
		case CAN_BPS_125K:
			BpsBuffer.CnBRP = 0x0f;
			//BpsBuffer.CnBTR = 0x130a;		/*2 TQ*/
			BpsBuffer.CnBTR = 0x230a;			/*3 TQ*/
			break;
		case CAN_BPS_250K:
			BpsBuffer.CnBRP = 0x0F;
			BpsBuffer.CnBTR = 0x1104;
			break;
		case CAN_BPS_500K:
			BpsBuffer.CnBRP = 0x03;
			BpsBuffer.CnBTR = 0x130a;
			break;
		default:
			return 1;
	}
	pChRegType->BRP = BpsBuffer.CnBRP;
	pChRegType->BTR = BpsBuffer.CnBTR;
	/* Set channel interrupt */
	pChRegType->IE = CAN_INICH_INT_SET_WAKUP |	\
					CAN_INICH_INT_CLR_ARBLST |	\
					CAN_INICH_INT_CLR_PRTERR |	\
					CAN_INICH_INT_CLR_ERRSTS |	\
					CAN_INICH_INT_SET_RX |	\
					CAN_INICH_INT_SET_TX;
	/* Set mask resister */
	{
		pChRegType->MASK1L =  (uint16_t)(0x1FFFFFFF & MSK_MASKL);
		pChRegType->MASK1H = (uint16_t)((0x1FFFFFFF & MSK_MASKH) >> 16);
		pChRegType->MASK2L =  (uint16_t)(0x1FFFFFFF & MSK_MASKL);
		pChRegType->MASK2H = (uint16_t)((0x1FFFFFFF & MSK_MASKH) >> 16);
		pChRegType->MASK3L =  (uint16_t)(0x1FFFFFFF & MSK_MASKL);
		pChRegType->MASK3H = (uint16_t)((0x1FFFFFFF & MSK_MASKH) >> 16);
		pChRegType->MASK4L =  (uint16_t)(0x1FFFFFFF & MSK_MASKL);
		pChRegType->MASK4H = (uint16_t)((0x1FFFFFFF & MSK_MASKH) >> 16);
	}
	/* Set error counter clear bit and the action of arbitration lost */
	//pChRegType->CTRL = (uint16_t)(MSK_REG_L & (MSK_AL | MSK_CCERC));
	pChRegType->CTRL = CLR_PSMODE;
	pChRegType->CTRL = (SET_AL | SET_CCERC|CLR_VALID);
	pChRegType->LEC = 0x00;			/*0603-pm17:00 */

	if(pChRegType->CTRL & CLR_VALID)
	{
		pChRegType->CTRL = CLR_VALID;
	}

	/* Set ABT delay */
	pGlbRegType->GMABTD = 0x00;

	/* Loop all message buffer */
	for( bufno = 0; bufno < 32; bufno++ ) 
	{
		pMsgRegType[bufno].MCTRL = CLR_RDY;	/* Clear RDY bit */
		pMsgRegType[bufno].MCONF &= CLR_MAx;	/* Clear MA0 bit */
		pMsgRegType[bufno].MCTRL = (uint16_t)(CLR_TRQ | CLR_DN|CLR_IE);	/* Clear TRQ, DN bit */
	}
	temp = pInitParam->can_RecvFilterNum + pInitParam->can_SendBuffNum;
	for( bufno = 0; bufno < temp; bufno++ ) 
	{

		pMsgRegTypeBuf = (volatile CAN_MsgRegType2*)&pMsgRegType[bufno];
		
		if((bufno < pInitParam->can_SendBuffNum))
		{	// send buffer parameter
			pMsgRegTypeBuf->MCONF = CAN_INIMSG_ADDRTYP_USE | CAN_INIMSG_MSGTYP_TX | 
						     CAN_INIMSG_FRMTYP_DAT;

			pMsgRegTypeBuf->MDLC =8;		/* Set CnMDLCm resister */
			/* Set CnMDATAm resister */
			(pMsgRegTypeBuf->MDATA)[0] = 0;
			(pMsgRegTypeBuf->MDATA)[1] = 0;
			(pMsgRegTypeBuf->MDATA)[2] = 0;
			(pMsgRegTypeBuf->MDATA)[3] = 0;
			#if CAN_INT_TX_EN
			if(bufno ==0)
			{
				pMsgRegTypeBuf->MCTRL = (uint16_t)(CLR_MOW | SET_IE | CLR_DN | CLR_TRQ);
			}
			else
			#endif
			{
				pMsgRegTypeBuf->MCTRL = (uint16_t)(CLR_MOW | CLR_IE | CLR_DN | CLR_TRQ);
			}
		}
		else 
		{
			uint32_t		canbuf_ini_canid;
			pMsgRegTypeBuf->MCONF = CAN_INIMSG_ADDRTYP_USE | CAN_INIMSG_MSGTYP_RX | 
						     CAN_INIMSG_FRMTYP_DAT | CAN_INIMSG_OVRWRT;
			pMsgRegTypeBuf->MDLC =1;		/* Set CnMDLCm resister */
			canbuf_ini_canid = (pInitParam->can_RecvFilter[bufno-pInitParam->can_SendBuffNum])<<18;
			pMsgRegTypeBuf->MIDH = (uint16_t)((canbuf_ini_canid & MSK_CANIDH) >> 16);
			pMsgRegTypeBuf->MIDL =  (uint16_t)(canbuf_ini_canid & MSK_CANIDL);

			pMsgRegTypeBuf->MCTRL = (uint16_t)(CLR_MOW | SET_IE | CLR_DN | CLR_TRQ);
		}
		pMsgRegTypeBuf->MCTRL = SET_RDY;	/* Set RDY bit */
	}
	CANbus_SetMaskConfig(pInitParam, (CAN_MsgRegType2*)&pMsgRegType[temp]);
	return 0;

}

/****************************************************************************
 * @function	CANbus_ChSetInitMode
 * @brief  	This function setting  the CAN controller to enter initialization  mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_ChSetInitMode(uint8_t chno)
{
	if(chno>= CAN_IDMAX)
	{
		return 1;
	}
	else
	{
		volatile CAN_ChRegType*pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
		/* Check not init mode */
		if ((pChRegType->CTRL & MSK_OPMODE) == CHK_INIT) 
		{
			//
		}
		else
		{
			/* Set normal mode */
			pChRegType->CTRL = SET_INIT;
		}
	}

	return 0;
}

/****************************************************************************
 * @function	CANbus_GetMode
 * @brief  	This function acquires the CAN channel's operation mode and power-saving mode.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_GetMode(uint8_t chno)
{
	if(chno>= CAN_IDMAX)
	{
		return 0xff;
	}
	else
	{
		volatile CAN_ChRegType*		pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);		
		/* Get operation mode and power save mode (Set return value) */
		return ((uint8_t)(pChRegType->CTRL & (MSK_OPMODE | MSK_PSMODE)));
	}
}
/****************************************************************************
 * @function	CANbus_EnterSleepMode
 * @brief  	This function acquires the CAN controller enter to sleep mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_EnterSleepMode(uint8_t chno)
{
	volatile CAN_ChRegType*pChRegType;

	if(chno>= CAN_IDMAX)
	{
		return 1;
	}

	/* Set CAN module register address */
	pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);		
	/* Get operation mode and power save mode (Set return value) */
	pChRegType->CTRL = 0x0810;	

	return 0;
}
/****************************************************************************
 * @function	CANbus_ExitSleepMode
 * @brief  	This function acquires the CAN controller exit sleep mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_ExitSleepMode(uint8_t chno)
{
	volatile CAN_ChRegType*pChRegType;

	if(chno>= CAN_IDMAX)
	{
		return 1;
	}

	/* Set CAN module register address */
	pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);		
	/* Get operation mode and power save mode (Set return value) */
	pChRegType->CTRL = 0x0018;	

	if((pChRegType->CTRL &0x0018) == 0x00)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

uint8_t CANbus_SetWorkMode(uint8_t chno, uint8_t mode)
{
	if(chno>= CAN_IDMAX)
	{
		return 1;
	}
	else
	{
		volatile CAN_ChRegType*pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType*)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
		/* Check init mode */
		if ((pChRegType->CTRL & MSK_OPMODE) != 0x0000)     /* init mode judge */
		{
			return 2;
		}
		else
		{
			if(mode == CAN_WORKMODE_NORMAL)
			{
				pChRegType->CTRL = 0x0100;	/* Set normal mode */
			}
			else if(mode == CAN_WORKMODE_LISTENONLY)
			{
				pChRegType->CTRL = 0x0304;	/* Set listen only  mode */
			}
			else if(mode  == CAN_WORKMODE_TEST)
			{
				pChRegType->CTRL = 0x0502;	/* Set selftest mode */
			}
		}
	}

	return 0;
}

/****************************************************************************
 * @function	CANbus_SetNormalMode
 * @brief  	This function setting  the CAN controller to enter normal mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_SetNormalMode(uint8_t chno)
{
	return CANbus_SetWorkMode(chno, CAN_WORKMODE_NORMAL);
}
/****************************************************************************
 * @function	CANbus_SetListenOnlyMode
 * @brief  	This function setting  the CAN controller to enter listen only mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   just read bus data, not send data.
****************************************************************************/
uint8_t CANbus_SetListenOnlyMode(uint8_t chno)
{
	return CANbus_SetWorkMode(chno, CAN_WORKMODE_LISTENONLY);
}
/****************************************************************************
 * @function	CANbus_SetSelfTestMode
 * @brief  	This function setting  the CAN controller to enter Self-test mode
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_SetSelfTestMode(uint8_t chno)
{
	return CANbus_SetWorkMode(chno, CAN_WORKMODE_TEST);
}
/****************************************************************************
 * @function	CANbus_MsgGetDatDlc
 * @brief  	This function acquires the data and data length from the CAN  message buffer.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 *			p_data :	start address of area for storing message data
 *			p_dlc :	Start address of area for storing message length
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_MsgGetDatDlc(uint8_t chno, uint8_t bufno, uint8_t* p_data, uint8_t* p_dlc)
{
	if(chno>= CAN_IDMAX)
	{
		return 1;
	}
	else
	{
		volatile CAN_MsgRegType*	pMsgRegType;
		volatile CAN_MsgRegType*	pMsgRegTypeBuf;

		/* Set CAN message buffer register address */
		pMsgRegType = (volatile CAN_MsgRegType*)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
		/* Set CAN message buffer[n] register address */
		pMsgRegTypeBuf = &pMsgRegType[bufno];
		/* Check parameter (Use CAN Buffer No) */
		if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
		{
			return 2;
		}
		/* Check DN bit */
		else if ((pMsgRegTypeBuf->MCTRL & MSK_DN) == 0) 
		{
			return 3;
		}			
		/* Clear DN bit */
		else
		{
			pMsgRegTypeBuf->MCTRL = CLR_DN;

			*p_dlc = (uint8_t)(pMsgRegTypeBuf->MDLC & MSK_DLC);	/* Get dlc */
			/* Get message data */
			{
				uint8_t	data_cnt;
				
				for( data_cnt = (uint8_t)0; ((data_cnt < *p_dlc) && (data_cnt < (uint8_t)LEN_CANDATA)); data_cnt++ ) 
				{
					*(p_data + (uint32_t)data_cnt) = (pMsgRegTypeBuf->MDATA[data_cnt]);
				}
			}
		}
	}

	return 0;
}

/****************************************************************************
 * @function	CANbus_MsgGetIdDataDlc
 * @brief  	This function acquires the CAN-ID.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 *			canid :	start address of area for storing CAN-ID
 *			p_data :	start address of area for storing message data
 *			dlc :	start address of area for storing message length
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_MsgGetIdDataDlc(uint8_t chno, uint8_t bufno, uint32_t* p_canid, uint8_t* p_data, uint8_t* p_dlc)
{
	uint8_t status = 0;

	/* Check channel No Max/Min */
	if(chno>= CAN_IDMAX)
	{
		status = 1;
	}
	else
	{
		volatile CAN_MsgRegType*	pMsgRegType;
		volatile CAN_MsgRegType*	pMsgRegTypeBuf;

		/* Set CAN message buffer register address */
		pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
		/* Set CAN message buffer[n] register address */
		pMsgRegTypeBuf = &pMsgRegType[bufno];
		/* Check parameter (Use CAN Buffer No)  */
		if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
		{
			status = 2;
		}
		/* Check DN bit */
		else if ((pMsgRegTypeBuf->MCTRL & MSK_DN) == 0) 
		{
			status = 3;
		}
		else
		{
			uint32_t midl, midh;
			
			/* Clear DN bit */
			pMsgRegTypeBuf->MCTRL = CLR_DN;
			/* Get CAN id */				
            		midl = (uint32_t)(pMsgRegTypeBuf->MIDL);
            		midh = ((uint32_t)(pMsgRegTypeBuf->MIDH));
			*p_canid = (midh&0x1fff) >>2;            // 2013.4.25 by weillion 
			/* Get dlc */
			*p_dlc = (uint8_t)(pMsgRegTypeBuf->MDLC & MSK_DLC);
			/* Get message data */
			{
				uint8_t	data_cnt;
				
				for( data_cnt = (uint8_t)0; ((data_cnt < *p_dlc) && (data_cnt < (uint8_t)LEN_CANDATA)); data_cnt++ )
				{
					*(p_data + (uint32_t)data_cnt) = (pMsgRegTypeBuf->MDATA[data_cnt]);
				}
			}		
		}
	}

	return (status);
}

/****************************************************************************
 * @function	CANbus_MsgSetDat
 * @brief  	This function sets data to the CAN channel's message buffer.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 *			p_data :	start address of area for storing message data
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_MsgSetDat(uint8_t chno, uint8_t bufno, uint8_t* p_data)
{
	uint8_t status = 0;

	/* Check channel No Max/Min */
	if(chno>= CAN_IDMAX)
	{
		status = 1;
	}
	else
	{
		volatile CAN_MsgRegType*	pMsgRegType;
		volatile CAN_MsgRegType*	pMsgRegTypeBuf;

		/* Set CAN message buffer register address */
		pMsgRegType = (volatile CAN_MsgRegType*)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
		/* Set CAN message buffer[n] register address */
		pMsgRegTypeBuf = &pMsgRegType[bufno];
		/* Check parameter (Use CAN Buffer No)  */
		if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
		{
			status = 2;
		}
		/* Check TRQ bit */
		else if ((pMsgRegTypeBuf->MCTRL & MSK_TRQ) != 0) 
		{
			status = 3;
		}
		else
		{
			/* Check RDY bit */
			pMsgRegTypeBuf->MCTRL = CLR_RDY;	/* Clear RDY bit */
			if ((pMsgRegTypeBuf->MCTRL & MSK_RDY) != 0) 
			{
				status = 4;
			}
			else
			{
				uint8_t	dlc_msk;

				dlc_msk = (uint8_t)(pMsgRegTypeBuf->MDLC & MSK_DLC);	/* Get dlc */
				/* Set message data */
				{
					uint8_t	data_cnt;

					for( data_cnt = (uint8_t)0; ((data_cnt < (uint8_t)dlc_msk) && (data_cnt < (uint8_t)LEN_CANDATA)); data_cnt++ )
					{
						pMsgRegTypeBuf->MDATA[data_cnt] = *(p_data + (uint32_t)data_cnt);
					}
				}					
				pMsgRegTypeBuf->MCTRL = SET_RDY;	/* Set RDY bit */
			}
		}
	}

	return (status);
}

/****************************************************************************
 * @function	CANbus_MsgSetIdDataDlc
 * @brief  	This function sets the CAN-ID, data and data length to the CAN  message buffer.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 *			p_data :	start address of area for storing message data
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_MsgSetIdDataDlc(uint8_t chno, uint8_t bufno, uint32_t canid, uint8_t* p_data, uint8_t dlc)
{
	uint8_t status = 0;

	/* Check channel No Max/Min */
	if(chno>= CAN_IDMAX)
	{
		status = 1;
	}
	else
	{
		volatile CAN_MsgRegType*	pMsgRegType;
		volatile CAN_MsgRegType*	pMsgRegTypeBuf;

		/* Set CAN message buffer register address */
		pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
		/* Set CAN message buffer[n] register address */
		pMsgRegTypeBuf = &pMsgRegType[bufno];
		/* Check parameter (Use CAN Buffer No)  */
		if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
		{
			status = 2;
		}
		/* Check TRQ bit */
		else if ((pMsgRegTypeBuf->MCTRL & MSK_TRQ) != 0) 
		{
			status = 3;
		}
		else
		{
			/* Check RDY bit */
			pMsgRegTypeBuf->MCTRL = CLR_RDY;	/* Clear RDY bit */
			if ((pMsgRegTypeBuf->MCTRL & MSK_RDY) != 0) 
			{
				status = 4;
			}
			else
			{
				/* Set CAN id */
				pMsgRegTypeBuf->MIDH = (uint16_t)(canid  << 2);
				pMsgRegTypeBuf->MIDL = 0x0000;
				{
					uint8_t	dlc_msk;

					/* Set dlc */
					pMsgRegTypeBuf->MDLC = (uint8_t)(dlc_msk = (uint8_t)(dlc & MSK_DLC));
					/* Set message data */
					{
						uint8_t	data_cnt;

						for( data_cnt = (uint8_t)0; ((data_cnt < (uint8_t)dlc_msk) && (data_cnt < (uint8_t)LEN_CANDATA)); data_cnt++ )
						{
							pMsgRegTypeBuf->MDATA[data_cnt] = *(p_data + (uint32_t)data_cnt);
						}
					}
					/* Set RDY bit */
					pMsgRegTypeBuf->MCTRL = SET_RDY;
				}
			}
		}
	}

	return (status);
}

/****************************************************************************
 * @function	CANbus_MsgTxReq
 * @brief  	This function sets the transmit request bit in the CAN channel's message buffer.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 *			bufno :	buffer number
 * @retval 	0: ok, other: fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_MsgTxReq(uint8_t chno, uint8_t bufno)
{
	uint8_t status = 0;

	/* Check channel No Max/Min */
	if(chno>= CAN_IDMAX)
	{
		status = 1;
	}
	else
	{			
		volatile CAN_MsgRegType*	pMsgRegType;
		volatile CAN_MsgRegType*	pMsgRegTypeBuf;

		/* Set CAN message buffer register address */
		pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
		/* Set CAN message buffer[n] register address */
		pMsgRegTypeBuf = &pMsgRegType[bufno];
		/* Check parameter (Use CAN Buffer No)  */
		if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
		{
			status = 2;
		}
		else
		{
			/* Check RDY bit */
			if ((pMsgRegTypeBuf->MCTRL & MSK_RDY) == 0) 
			{
				status = 3;
			}
			else
			{
				pMsgRegTypeBuf->MCTRL = SET_TRQ;	/* Set TRQ bit */
			}
		}
	}
	return (status);
}
/****************************************************************************
 * @function	CANbus_ChGetBusStatus
 * @brief  	This function acquires the CAN channel's bus status.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	return INFO value
 * @attention   null
****************************************************************************/
uint8_t CANbus_ChGetBusStatus(uint8_t chno)
{
	uint8_t status = 0xff;

	/* Check channel No Max/Min */
	if(chno< CAN_IDMAX)
	{
		volatile CAN_ChRegType*	pChRegType;
		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
		status = ((uint8_t)(pChRegType->INFO & (MSK_BOFF | MSK_TECS | MSK_RECS)));
	}
	
	return (status);
}
/****************************************************************************
 * @function	CANbus_IsBusOffStatus
 * @brief  	This function acquires the BUS off stauts
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: bus ok, 1: busoff
 * @attention   null
****************************************************************************/
uint8_t CANbus_IsBusOffStatus(uint8_t chno)
{
	uint8_t status = CANbus_ChGetBusStatus(chno);

	if(status & MSK_BOFF)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************
 * @function	CANbus_ChShutDown
 * @brief  	This function forcibly shuts down CAN-controller.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: OK, other : fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_ChShutDown(uint8_t chno)
{
	uint8_t status = 0;

	/* Check channel No Max/Min */
	if(chno>= CAN_IDMAX)
	{
		status = 1;
	}
	else
	{
		volatile CAN_GlbRegType*	pGlbRegType;
		/* Set CAN global register address */
		pGlbRegType = (volatile CAN_GlbRegType*)(gcCanRegBaseAddr[chno].pGlbRegBaseAddr);	
		pGlbRegType->GMCTRL = SET_EFSD;	/* Set EFSD bit */
		pGlbRegType->GMCTRL = CLR_GOM;	/* Clear GOM bit */		
		/* Check GOM bit */
		if ((pGlbRegType->GMCTRL & MSK_GOM) != 0) 
		{
			status = 2;
			CANDrv_DebugOut(_T("Canbus_ChShutDown failed:%x", chno));
		}
	}
	return (status);
}
void CANbus_IntDisable(uint8_t chno)
{
	BPC = 0x8ffb;		/* Enable Progarmmable IO for CAN */
	if(chno == 0)
	{
		WUPMK0 = 1;	/* INTC0WUP disable */
		WUPIF0 = 0;	/* INTC0WUP IF clear */
		ERRMK0 = 1;	/* INTC0ERR disable */
		ERRIF0 = 0;	/* INTC0ERR IF clear */
		RECMK0 = 1;	/* INTC0REC disable */
		RECIF0 = 0;	/* INTC0REC IF clear */
		TRXMK0 = 1;	/* INTC0TRX disable */
		TRXIF0 = 0;	/* INTC0TRX IF clear */
	}
	else
	{
		//#ifdef CAN_DUAL_VERSION
		#if _CPU_TYPE_  == _V850_upd3365_
		WUPMK1 = 1;	/* INTC1WUP disable */
		WUPIF1 = 0;	/* INTC1WUP IF clear */
		ERRMK1 = 1;	/* INTC1ERR disable */
		ERRIF1 = 0;	/* INTC1ERR IF clear */
		RECMK1 = 1;	/* INTC1REC disable */
		RECIF1 = 0;	/* INTC1REC IF clear */
		TRXMK1 = 1;	/* INTC1TRX disable */
		TRXIF1 = 0;	/* INTC1TRX IF clear */
		#endif
	}
}
/****************************************************************************
 * @function	CANbus_Init
 * @brief  	This function initializes the CAN module. the port, interrput as so on
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	null
 * @attention   null
****************************************************************************/
void CANbus_Init(uint8_t chno)
{
	BPC = 0x8ffb;		/* Enable Progarmmable IO for CAN */
	if(chno == 0)
	{
		WUPMK0 = 1;	/* INTC0WUP disable */
		WUPIF0 = 0;	/* INTC0WUP IF clear */
		ERRMK0 = 1;	/* INTC0ERR disable */
		ERRIF0 = 0;	/* INTC0ERR IF clear */
		RECMK0 = 1;	/* INTC0REC disable */
		RECIF0 = 0;	/* INTC0REC IF clear */
		TRXMK0 = 1;	/* INTC0TRX disable */
		TRXIF0 = 0;	/* INTC0TRX IF clear */
		#if 1
		/* Set INTC0WUP lowest priority */
		//WUPIC0 |= 0x07;				
		//WUPMK0 = 0;	/* INTC0WUP enable */
		/* Set INTC0ERR lowest priority */
		//ERRIC0 |= 0x07;
		//ERRMK0 = 0;	/* INTC0ERR enable */
		/* Set INTC0REC level 1 priority */
		RECIC0 &= 0xF8;
		RECIC0 |= 0x01;
		RECMK0 = 0;	/* INTC0REC enable */
		#if CAN_INT_TX_EN
		/* Set INTC0TRX lowest priority */
		TRXIC0 |= 0x02;
		TRXMK0 = 0;	/* INTC0TRX enable */
		#endif
		/*******************/
		C0INTS = 0x3f;   /*CLEAR*/
		#endif
		/* CRXD0 pin set */
		PFC3L &= 0x7F;
		PMC3L |= 0x80;
		/* CTXD0 pin set */
		PFC3L &= 0xBF;
		PMC3L |= 0x40;
	}
	else
	{
		//#ifdef CAN_DUAL_VERSION
		#if _CPU_TYPE_  == _V850_upd3365_
		WUPMK1 = 1;	/* INTC1WUP disable */
		WUPIF1 = 0;	/* INTC1WUP IF clear */
		ERRMK1 = 1;	/* INTC1ERR disable */
		ERRIF1 = 0;	/* INTC1ERR IF clear */
		RECMK1 = 1;	/* INTC1REC disable */
		RECIF1 = 0;	/* INTC1REC IF clear */
		TRXMK1 = 1;	/* INTC1TRX disable */
		TRXIF1 = 0;	/* INTC1TRX IF clear */
		#if 1
		/* Set INTC1WUP lowest priority */
		//WUPIC1 |= 0x07;
		//WUPMK1 = 0;	/* INTC1WUP enable */
		/* Set INTC1ERR lowest priority */
		//ERRIC1 |= 0x07;
		//ERRMK1 = 0;	/* INTC1ERR enable */
		/* Set INTC1REC level 1 priority */
		RECIC1 &= 0xF8;
		RECIC1 |= 0x01;
		RECMK1 = 0;	/* INTC1REC enable */
		#if CAN_INT_TX_EN
		/* Set INTC1TRX lowest priority */
		TRXIC1 |= 0x02;
		TRXMK1 = 0;	/* INTC1TRX enable */
		#endif
		/*******************/
		C1INTS = 0x3f;   /*CLEAR*/
		#endif
		/* CRXD1 pin set */
		PFC3L &= 0xEF;
		PFCE3L |= 0x10;
		PMC3L |= 0x10;
		/* CTXD1 pin set */
		PFC3L &= 0xF7;
		PFCE3L |= 0x08;
		PMC3L |= 0x08;
		#endif
	}
}

void CANbus_DefaultInit(uint8_t chno)
{
		CANbus_IntDisable(chno);
		CANbus_ChShutDown(chno);
}
/****************************************************************************
 * @function	CANbus_GetIntBuffNumber
 * @brief  	This function acquires the CAN message buffer index when receive inttrupt accor
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0~31
 * @attention   null
****************************************************************************/
uint8_t CANbus_GetIntBuffNumber(uint8_t chno)
{
	volatile CAN_ChRegType*	pChRegType;
	pChRegType = (volatile CAN_ChRegType*)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
	
	return pChRegType->LIPT;
}
/****************************************************************************
 * @function	CANbus_ErrorDeal
 * @brief  	This function deal the error state
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	null
 * @attention   null
****************************************************************************/
void CANbus_ErrorDeal(uint8_t chno)
{
	volatile CAN_ChRegType*	pChRegType;
	pChRegType = (volatile CAN_ChRegType*)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
	if((pChRegType->INFO) & 0x10)	//BOFF=1;
	{
	}
	else
	{
	}
	pChRegType->INTS = 0x1c;		//clear error interrupt flag
}
/****************************************************************************
 * @function	CANbus_ChEnable
 * @brief  	This function enable the CAN Controller channal
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	0: OK, other : fault
 * @attention   null
****************************************************************************/
uint8_t CANbus_ChEnable(uint8_t chno, CAN_INIT_STRUCT *pInitParam)
{
	BPC = 0x8ffb;		/* Enable Progarmmable IO for CAN */
	/* Check channel No Max/Min */
	if(chno>= CAN_IDMAX)
	{
		return 1;
	}
	else
	{
		volatile CAN_GlbRegType*	pGlbRegType;

		/* Set CAN global register address */
		pGlbRegType = (volatile CAN_GlbRegType *)(gcCanRegBaseAddr[chno].pGlbRegBaseAddr);
		/* Check GOM bit */
	//	if ((pGlbRegType->GMCTRL & MSK_GOM) != 0) 
		//{
			// no operation
	//	}
		/* Set CAN clock */
	//	else
	//	{
			pGlbRegType->GMCS = 0x00; //gcCanChIniBps[chno].CnGMCS;
			pGlbRegType->GMCTRL = SET_GOM;	/* Start CAN controller */
	//	}
	}
	
	CANbus_ChSetInitMode(chno);

	return CANbus_ChRegInit(pInitParam);

}
/****************************************************************************
 * @function	CANbus_RecoveryFromBusOff
 * @brief  	This function recovery the CAN transceiver from the busoff state.
 * @param  	chno: CAN_ID0, CAN_ID1(CAN_ID1 used for dual cantroller version only)	
 * @retval 	null
 * @attention   null
****************************************************************************/
void CANbus_RecoveryFromBusOff(uint8_t chno)
{
	if(chno>= CAN_IDMAX)
	{
		return;
	}
	else
	{
		volatile CAN_ChRegType*pChRegType;
		pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);

		CANbus_ChSetInitMode(chno);
		
		pChRegType->CTRL = 0x8000;           		//clear ccerc BIT
		pChRegType->INTS = 0x003f;                         //clear all interrupt

		CANbus_SetNormalMode(chno);
	}
}
/****************************************************************************
 * @function	CAN0_INTWUP
 * @brief  	This function is wakeup interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
 void CAN0_INTWUP(void)
{
	CANWakeupStatus |= _U8_BIT0;
	C0INTS = 0x20;
}

/****************************************************************************
 * @function	CAN0_INTREC
 * @brief  	This function is receive interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
void CAN0_INTREC(void)
{	
	//uint8_t bak = RECMK1;
	//RECMK1 = 1;	/* INTC1REC disable */
	C0INTS = 0x02;
	Can_V850_CanIf_RecvInterruptCallback(CAN_ID0);
	//CANbus_RecvInterruptCallBack(CAN_ID0);
	//RECMK1 = bak;	/*recovery INTC1REC  */
}
/****************************************************************************
 * @function	CAN0_INTTRX
 * @brief  	This function is send complete interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
void CAN0_INTTRX(void)
{
	CANbus_Ch0SendInterruptCallBack();

	C0INTS = 0x01;
}
/****************************************************************************
 * @function	CAN0_INTERR
 * @brief  	This function is error interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
void CAN0_INTERR(void)
{
	C0INTS = 0x1c;		//clear error interrupt flag
}

/****************************************************************************
 * @function	CAN1_INTWUP
 * @brief  	This function is wakeup  interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
void CAN1_INTWUP(void)
{
	CANWakeupStatus |= _U8_BIT1;
	C1INTS = 0x20;
}

/****************************************************************************
 * @function	CAN1_INTREC
 * @brief  	This function is receive interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
void CAN1_INTREC(void)
{
	//uint8_t bak = RECMK0;
	//RECMK0 = 1;		/* INTC0REC disable */
	C1INTS = 0x02;
	CANbus_RecvInterruptCallBack(CAN_ID1);
	//RECMK0 = bak;	/* recovery INTC0REC  */
}
/****************************************************************************
 * @function	CAN1_INTTRX
 * @brief  	This function is send complete interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
void CAN1_INTTRX(void)
{
	CANbus_Ch1SendInterruptCallBack();
	C1INTS = 0x01;
}

/****************************************************************************
 * @function	CAN1_INTERR
 * @brief  	This function is error interrupt service routine.
 * @param  	null		
 * @retval 	null
 * @attention   null
****************************************************************************/
void CAN1_INTERR(void)
{
	C1INTS = 0x1c;		//clear error interrupt flag
}
#else

 void CAN0_INTWUP(void)
{
}
void CAN0_INTREC(void)
{	
}
void CAN0_INTTRX(void)
{
}
void CAN0_INTERR(void)
{
}
void CAN1_INTWUP(void)
{
}
void CAN1_INTREC(void)
{
}
void CAN1_INTTRX(void)
{
}
void CAN1_INTERR(void)
{
}

#endif
/****************************************************************************
***                                                FILE END
****************************************************************************/


