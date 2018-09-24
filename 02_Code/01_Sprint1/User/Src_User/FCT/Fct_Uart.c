#include "..\config\inc.h"
enum
{
    FCT_UART_LENGTH_ERR,
    FCT_UART_COUNT_ERR,
    FCT_UART_POINT_ERR,
    FCT_UART_DATA_ERR,
    FCT_UART_OK,
};

/**********************************************************
 * @function    FCT_SendDataResult
 * @brief       Data Result
 * @param      uint8_t *S_Data  data pointer
 *                   uint8_t Length    data length
 * @retval     None
 **********************************************************/
void FCT_SendDataResult (uint8_t S_MainCom ,  uint8_t S_SubCom, uint8_t *S_Data , uint8_t Length)
{
    uint8_t Count ;
    uint8_t S_CRC ;
    
    if (Length > 120)
        return ;
#if  D_FCT_WAIT_ACK_EN == 1      //test

    if (FCT_GetSendOKWaitAckFlag() == TRUE)
        return ;    
    if(FCT_GetRepeatFlag())
        return ;
#endif

    if(S_MainCom > OP_FCT_TO_HMI_START)
        S_MainCom  -= OP_FCT_TO_HMI_START;

    g_tFCT.tAckSystem.SendArray[0] = 0xEE;
    g_tFCT.tAckSystem.SendArray[1] = 0xFA;
    g_tFCT.tAckSystem.SendArray[2] = Length + 7 ;
    g_tFCT.tAckSystem.SendArray[3] = S_MainCom;
    g_tFCT.tAckSystem.SendArray[4] = S_SubCom;
    g_tFCT.tAckSystem.SendArray[5] = RETURN_DATA_RESULT ; 
    
    S_CRC =  0xFF;
    
    S_CRC ^=  g_tFCT.tAckSystem.SendArray[2] 
            ^  g_tFCT.tAckSystem.SendArray[3] 
            ^ g_tFCT.tAckSystem.SendArray[4]
            ^ g_tFCT.tAckSystem.SendArray[5];
    
    for(Count = 0 ; Count < Length ; Count++)
    {
        g_tFCT.tAckSystem.SendArray[Count + 6] = *S_Data;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[Count + 6] ;
        S_Data ++ ;
    }
    g_tFCT.tAckSystem.SendArray[Length + 6] = S_CRC;

     FCT_UARTA3_SendData(g_tFCT.tAckSystem.SendArray,g_tFCT.tAckSystem.SendArray[2]);
#if  D_FCT_WAIT_ACK_EN == 1      //test
    FCT_SetSendOKWaitAckFlag(TRUE);
    FCT_SetManagerState(WAIT_ACK_STATE);
#endif
}



/**********************************************************
 * @function    FCT_SendFullDataResult
 * @brief       Data Result
 * @param      uint8_t *S_Data  data pointer
 *                   uint8_t Length    data length
 * @retval     None
 **********************************************************/
void FCT_SendFullDataResult (uint8_t S_MainCom ,  uint8_t S_SubCom, uint8_t Data0 , uint8_t Data1 ,uint8_t Data2 ,uint8_t Data3,uint8_t Length)
{
    uint8_t Count ;
    uint8_t DataBackUp ;
    uint8_t S_CRC ;
    
    if (Length > 120)
        return ;
#if  D_FCT_WAIT_ACK_EN == 1      //test

    if (FCT_GetSendOKWaitAckFlag() == TRUE)
        return ;    
    if(FCT_GetRepeatFlag())
        return ;
#endif

    if(S_MainCom > OP_FCT_TO_HMI_START)
        S_MainCom  -= OP_FCT_TO_HMI_START;

    g_tFCT.tAckSystem.SendArray[0] = 0xEE;
    g_tFCT.tAckSystem.SendArray[1] = 0xFA;
    g_tFCT.tAckSystem.SendArray[2] = Length + 7 ;
    g_tFCT.tAckSystem.SendArray[3] = S_MainCom;
    g_tFCT.tAckSystem.SendArray[4] = S_SubCom;
    g_tFCT.tAckSystem.SendArray[5] = RETURN_DATA_RESULT ; 
    
    S_CRC =  0xFF;
    
    S_CRC ^=  g_tFCT.tAckSystem.SendArray[2] 
            ^  g_tFCT.tAckSystem.SendArray[3] 
            ^ g_tFCT.tAckSystem.SendArray[4]
            ^ g_tFCT.tAckSystem.SendArray[5];
    
    for(Count = 0 ; Count < Length ; Count++)
    {
	 if(Count == 0)   
		DataBackUp = Data0;
	 else if(Count == 1)   
		DataBackUp = Data1;
	 else if(Count == 2)   
		DataBackUp = Data2;
	 else if(Count == 3)   
		DataBackUp = Data3;
 
        g_tFCT.tAckSystem.SendArray[Count + 6] = DataBackUp;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[Count + 6] ;
    }

#if 0	
if(1 ==Length)
{
        g_tFCT.tAckSystem.SendArray[6] = Data0;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[6] ;
}
else if(2 ==Length)
{
        g_tFCT.tAckSystem.SendArray[6] = Data0;
        g_tFCT.tAckSystem.SendArray[7] = Data1;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[6] ;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[7] ;
}
else if(3 ==Length)
{
        g_tFCT.tAckSystem.SendArray[6] = Data0;
        g_tFCT.tAckSystem.SendArray[7] = Data1;
        g_tFCT.tAckSystem.SendArray[8] = Data2;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[6] ;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[7] ;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[8] ;
}
else if(4 ==Length)
{
        g_tFCT.tAckSystem.SendArray[6] = Data0;
        g_tFCT.tAckSystem.SendArray[7] = Data1;
        g_tFCT.tAckSystem.SendArray[8] = Data2;
        g_tFCT.tAckSystem.SendArray[9] = Data3;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[6] ;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[7] ;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[8] ;
        S_CRC ^=g_tFCT.tAckSystem.SendArray[9] ;
}
#endif
	
    g_tFCT.tAckSystem.SendArray[Length + 6] = S_CRC;

     FCT_UARTA3_SendData(g_tFCT.tAckSystem.SendArray,g_tFCT.tAckSystem.SendArray[2]);
#if  D_FCT_WAIT_ACK_EN == 1      //test
    FCT_SetSendOKWaitAckFlag(TRUE);
    FCT_SetManagerState(WAIT_ACK_STATE);
#endif
}



/**********************************************************
 * @function    FCT_SendAsk
 * @brief       
 * @param       
 *                    
 * @retval     None
 **********************************************************/
void FCT_SendAsk( uint8_t AskType, uint8_t Gid, uint8_t Sid)
{
    uint8_t Count ;
    uint8_t S_CRC ;

    if(Gid == 0x7F) // PC回来的应答消息，不需要回应答。
        return ;
    
    g_tFCT.tTopcTx.SAskArray[0] = 0xEE;
    g_tFCT.tTopcTx.SAskArray[1] = 0xFA;
    g_tFCT.tTopcTx.SAskArray[2] = 8;
    g_tFCT.tTopcTx.SAskArray[3] = 0x7F;
    g_tFCT.tTopcTx.SAskArray[4] = AskType;    
    g_tFCT.tTopcTx.SAskArray[5] = Gid;    
    g_tFCT.tTopcTx.SAskArray[6] = Sid;
    S_CRC = 0xFF;
    for(Count = 2 ; Count < 7 ; Count++)
    {
         S_CRC ^= g_tFCT.tTopcTx.SAskArray[Count];      
    }
    g_tFCT.tTopcTx.SAskArray[7] = S_CRC;

    FCT_UARTA3_SendData(g_tFCT.tTopcTx.SAskArray, g_tFCT.tTopcTx.SAskArray[2]);
}

/**********************************************************
 * @function    FCT_SendFCTEnter
 * @brief       
 * @param       
 *                    
 * @retval     None
 **********************************************************/
void FCT_SendFCTEnter(void )
{
    uint8_t Couent ;
#if  D_FCT_WAIT_ACK_EN == 1      //test
    if (FCT_GetSendOKWaitAckFlag() == TRUE)
        return ;    
    if(FCT_GetRepeatFlag())
        return ;
#endif
    g_tFCT.tAckSystem.SendArray[0] = 0xEE;
    g_tFCT.tAckSystem.SendArray[1] = 0xFA;
    g_tFCT.tAckSystem.SendArray[2] = 0x0D;
    g_tFCT.tAckSystem.SendArray[3] = 0x80;
    g_tFCT.tAckSystem.SendArray[4] = 0x01;
    g_tFCT.tAckSystem.SendArray[5] = 0x02;    
    g_tFCT.tAckSystem.SendArray[6] = 0x46;
    g_tFCT.tAckSystem.SendArray[7] = 0x43;
    g_tFCT.tAckSystem.SendArray[8] = 0x54;    
    g_tFCT.tAckSystem.SendArray[9] = 0x49;
    g_tFCT.tAckSystem.SendArray[10] = 0x4E;
    g_tFCT.tAckSystem.SendArray[11] = HQ10_DESIGN_TEAM;
    g_tFCT.tAckSystem.SendArray[12] = 0xFF;

    for(Couent = 2 ; Couent < 12; Couent ++)
        g_tFCT.tAckSystem.SendArray[12] ^= g_tFCT.tAckSystem.SendArray[Couent] ; 
    
    FCT_UARTA3_SendData(g_tFCT.tAckSystem.SendArray,g_tFCT.tAckSystem.SendArray[2]);
#if  D_FCT_WAIT_ACK_EN == 1      //test
    FCT_SetSendOKWaitAckFlag(TRUE);
#endif
}


/**********************************************************
 * @function    FCT_SendFCTOut
 * @brief       
 * @param       
 *                    
 * @retval     None
 **********************************************************/
void FCT_SendFCTOut(void )
{
    uint8_t Couent ;
#if  D_FCT_WAIT_ACK_EN == 1      //test
    if (FCT_GetSendOKWaitAckFlag() == TRUE)
        return ;    
    if(FCT_GetRepeatFlag())
        return ;
#endif
    g_tFCT.tAckSystem.SendArray[0] = 0xEE;
    g_tFCT.tAckSystem.SendArray[1] = 0xFA;
    g_tFCT.tAckSystem.SendArray[2] = 0x0C;
    g_tFCT.tAckSystem.SendArray[3] = 0x80;
    g_tFCT.tAckSystem.SendArray[4] = 0x02;
    g_tFCT.tAckSystem.SendArray[5] = 0x02;    
    g_tFCT.tAckSystem.SendArray[6] = 0x46;
    g_tFCT.tAckSystem.SendArray[7] = 0x43;
    g_tFCT.tAckSystem.SendArray[8] = 0x54;    
    g_tFCT.tAckSystem.SendArray[9] = 0x4E;
    g_tFCT.tAckSystem.SendArray[10] = 0x4F;
    g_tFCT.tAckSystem.SendArray[11] = 0xFF;    

    for(Couent = 2 ; Couent < 11; Couent ++)
        g_tFCT.tAckSystem.SendArray[11] ^= g_tFCT.tAckSystem.SendArray[Couent] ; 
    FCT_UARTA3_SendData(g_tFCT.tAckSystem.SendArray,g_tFCT.tAckSystem.SendArray[2]);
#if  D_FCT_WAIT_ACK_EN == 1      //test
    FCT_SetSendOKWaitAckFlag(TRUE);
#endif
}

/***********************************************************
*适应范围- PC给MCU指令后，MCU能够很快反应，返回数据，
*但是串口缓存中有数据还没有发送完，需要延迟处理
***********************************************************/
void FctReMsgDelayHandler(uint8_t * pMsgFct)
{
    uint8_t Gid;
    uint8_t Sid;
    Gid = pMsgFct[1];
    Sid = pMsgFct[2];
    if(((Gid == (OP_FCT_RADIO_4 - OP_FCT_TO_HMI_START) )&&(Sid == RETURN_CUR_FREQ ))
        ||((Gid == (OP_FCT_RADIO_4 - OP_FCT_TO_HMI_START) )&&(Sid == RDS_SATE ))
        ||((Gid == (OP_FCT_RADIO_4 - OP_FCT_TO_HMI_START) )&&(Sid == SET_FREQ ))
        ||(Gid == (OP_FCT_SOFT_VER_18 - OP_FCT_TO_HMI_START) )
        ||(Gid == OP_FCT_PASSWORD_128 )
       )
    {
        g_tFCT.tFctCount.cReMsgDelay = 7 ;
    }
}




/**********************************************************
 * @function    FCT_UartRecMessage
 * @brief      FCT_Uart   Rec   Data Message
 * @param       
 *                    
 * @retval     None
 **********************************************************/
void FCT_UartRecMessage (uint8_t R_Data)
{
    switch (g_tFCT.tUartRecDataStep)
    {
        case FCT_FRAME_HEAD_FIRST :
         {
            if(FCT_HEAD_FIRST == R_Data)
                g_tFCT.tUartRecDataStep = FCT_FRAME_HEAD_SECOND ;
         }
        break;
        case FCT_FRAME_HEAD_SECOND:
        {
            if(R_Data == FCT_HEAD_SECOND)
            {
                g_tFCT.tTomcuRx.RXCRC = 0xFF ;
                g_tFCT.tUartRecDataStep = FCT_FRAME_LENGH ;
            }
            else
                g_tFCT.tUartRecDataStep = FCT_FRAME_HEAD_FIRST ;
        }
        break;
        case FCT_FRAME_LENGH:
        {
            FCT_REC_FLAG = FALSE;
            g_tFCT.tTomcuRx.RxLength = R_Data ;    
            g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][0] = R_Data ;    
            g_tFCT.tTomcuRx.RxCount = 0 ;
            g_tFCT.tTomcuRx.RXCRC ^= R_Data ;
            g_tFCT.tUartRecDataStep = FCT_FRAME_DATA ;
        }
        break;
        case FCT_FRAME_DATA:
        {    
            if ((g_tFCT.tTomcuRx.RxCount + 4) < g_tFCT.tTomcuRx.RxLength)
            {
                g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][g_tFCT.tTomcuRx.RxCount + 1] = R_Data ;    
                g_tFCT.tTomcuRx.RXCRC ^= R_Data ;    
            }
            g_tFCT.tTomcuRx.RxCount ++ ;
            if ((g_tFCT.tTomcuRx.RxCount + 4) == g_tFCT.tTomcuRx.RxLength)
                g_tFCT.tUartRecDataStep = FCT_FRAME_CRC ;    
            
            if(PC_TO_FCT_GID == OP_FCT_ACK_127)
                g_tFCT.tUartRecDataStep = FCT_ACK_DATA ;
            
            if (PC_TO_FCT_GID == OP_FCT_PASSWORD_128)
                g_tFCT.tUartRecDataStep = FCT_PASSWORD_DATA ;                    
        }
        break;
        case FCT_FRAME_CRC:
        {
            if(g_tFCT.tTomcuRx.RXCRC == R_Data)
            {
                FCT_REC_FLAG = TRUE ;
                FCT_SendAsk(ACK_OK,PC_TO_FCT_GID,PC_TO_FCT_SID);
                FctReMsgDelayHandler(&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][0]));
                g_tFCT.tTomcuRx.cRxRecIndex ++ ;
                g_tFCT.tTomcuRx.cRxRecIndex %= TOMCU_RX_COM_SIZE ;
                
#if  D_FCT_WAIT_ACK_EN == 1      //test
                if( !(FCT_GetRepeatFlag()))
                    FCT_RepeatSendCountZero();
#endif                
            }    
            else
                FCT_SendAsk(ACK_CRC_ERROR,PC_TO_FCT_GID,PC_TO_FCT_SID);
            
            g_tFCT.tUartRecDataStep = FCT_FRAME_HEAD_FIRST ;        
        }
        break;
        
        case FCT_ACK_DATA:
        {    
            if ((g_tFCT.tTomcuRx.RxCount + 4) < g_tFCT.tTomcuRx.RxLength)
            {
                g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][g_tFCT.tTomcuRx.RxCount + 1] = R_Data ;    
                g_tFCT.tTomcuRx.RXCRC ^= R_Data ;    
            }    
            
            if(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][1] != OP_FCT_ACK_127)
                g_tFCT.tUartRecDataStep = FCT_FRAME_HEAD_FIRST ;    
            
            g_tFCT.tTomcuRx.RxCount ++ ;
            if ((g_tFCT.tTomcuRx.RxCount + 4) == g_tFCT.tTomcuRx.RxLength)
                g_tFCT.tUartRecDataStep = FCT_ACK_CRC ;    
        }
        break;
        case FCT_ACK_CRC:
        {
            if(g_tFCT.tTomcuRx.RXCRC == R_Data)
            {            
                if((PC_TO_FCT_SID == ACK_OK)
                    &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][3] == ACK_MAIN_COM)
                    &&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][4] == ACK_SUB_COM)
                   )
                {
                    FCT_SetSendOKWaitAckFlag(FALSE);
                    FCT_SetManagerState(WORK_STATE);
                    FCT_RepeatSendCountZero();
                }
                else
                {
                    FCT_SetRepSendCause(ACK_ERROR);
                    FCT_SetManagerState(REPEAT_STATE);
                }                
            }
            else
                g_tFCT.tUartRecDataStep = FCT_FRAME_HEAD_FIRST ;        
        }
        break;
        
        case FCT_PASSWORD_DATA:
        {    
            if ((g_tFCT.tTomcuRx.RxCount + 4) < g_tFCT.tTomcuRx.RxLength)
            {
                g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][g_tFCT.tTomcuRx.RxCount +1] = R_Data ;    
                g_tFCT.tTomcuRx.RXCRC ^= R_Data ;    
            }    
            
            if(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][1] != OP_FCT_PASSWORD_128)
                g_tFCT.tUartRecDataStep = FCT_FRAME_HEAD_FIRST ;    
            
            g_tFCT.tTomcuRx.RxCount ++ ;
            if ((g_tFCT.tTomcuRx.RxCount + 4) == g_tFCT.tTomcuRx.RxLength)
                g_tFCT.tUartRecDataStep = FCT_PASSWORD_CRC ;    
        }
        break;
        case FCT_PASSWORD_CRC:
        {
            if(g_tFCT.tTomcuRx.RXCRC == R_Data)
            {
                FCT_SetPasswordFlag(TRUE) ;
                FCT_SetManagerState(PASSWORD_STATE);
                FCT_SendAsk(ACK_OK,PC_TO_FCT_GID,PC_TO_FCT_SID);
                FctReMsgDelayHandler(&(g_tFCT.tTomcuRx.Ia_RxBuff[g_tFCT.tTomcuRx.cRxRecIndex][0]));
            }    
            g_tFCT.tUartRecDataStep = FCT_FRAME_HEAD_FIRST ;        
        }
        break;
        
        default :
        break;
    }
}



/*
**-----------------------------------------------------------------------------
**
**    Abstract:
**        This function sends UARTA3 data.
**
**    Parameters:
**        txbuf :    transfer buffer pointer
**        txnum :    buffer size
**
**    Returns:
**        MD_OK
**        MD_ARGERROR
**        MD_DATAEXISTS
**
**-----------------------------------------------------------------------------
*/
uint8_t FCT_UARTA3_SendData(uint8_t* txbuf, uint8_t txnum)
{
    MD_STATUS status = MD_OK;
    
    if (txnum < 1)
    {
        status = FCT_UART_LENGTH_ERR;
    }
    else
    {
        if (g_tFCT.tTopcTx.gpUarta3TxAddress != NULL)
            return FCT_UART_COUNT_ERR;
        if(g_tFCT.tTopcTx.gUarta3TxCnt != 0)
            return FCT_UART_POINT_ERR;

        g_tFCT.tTopcTx.gpUarta3TxAddress = txbuf;
        g_tFCT.tTopcTx.gUarta3TxCnt = txnum;
    
        if((UA3STR & 0x80) == 0)
        {
            UA3TMK = 1;    /* INTUA3T interrupt disable */
            UA3TX = *g_tFCT.tTopcTx.gpUarta3TxAddress;
            g_tFCT.tTopcTx.gpUarta3TxAddress++;
            g_tFCT.tTopcTx.gUarta3TxCnt--;
            UA3TMK = 0;    /* INTUA3T interrupt enable */
            status = FCT_UART_OK;
        }
        else
        {
            status = FCT_UART_DATA_ERR;
        }
    }

    return (status);
}

 void isrFCT_INTUA3R(void)
{
    uint8_t    rx_data;
    uint8_t    err_type;

    rx_data = UA3RX;
    err_type = (uint8_t)(UA3STR & 0x07);
    UA3STR = (uint8_t)~0x07;
    if (err_type != 0)
    {
        //UARTA3_ErrorCallback(err_type);
    }
    else
    {
        FCT_UartRecMessage(rx_data);
    }
}

/*
**-----------------------------------------------------------------------------
**
**    Abstract:
**        This function is INTUA3T interrupt service routine.
**
**    Parameters:
**        None
**
**    Returns:
**        None
**
**-----------------------------------------------------------------------------
*/
 void isrFCT_INTUA3T(void)
{
    if (g_tFCT.tTopcTx.gUarta3TxCnt > 0)
    {
        UA3TX = *g_tFCT.tTopcTx.gpUarta3TxAddress;
        g_tFCT.tTopcTx.gpUarta3TxAddress++;
        g_tFCT.tTopcTx.gUarta3TxCnt--;
    }
    else
    {
         g_tFCT.tTopcTx.gpUarta3TxAddress = NULL ;
    }
}


