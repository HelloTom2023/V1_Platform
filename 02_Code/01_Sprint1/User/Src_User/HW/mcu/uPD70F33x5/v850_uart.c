/*******************************************************************************
*-------------------------------------------------------------------------------
*
*  UART0   use for debug
*  BPS = 115200
*
*******************************************************************************/
void v850_uart0_Init(void)
{
#ifdef UART0_PRINT_ENABLE
	UA0TXE = 0;	/* disable transmission operation(uarta0) */
	UA0RXE = 0;	/* disable reception operation(uarta0) */
	UA0PWR = 0;	/* disable UARTA0 operation */
	UA0TMK = 1;	/* INTUA0T interrupt disable */
	UA0TIF = 0;	/* clear INTUA0T interrupt flag */
	UA0RMK = 1;	/* INTUA0R interrupt disable */
	UA0RIF = 0;	/* clear INTUA0R interrupt flag */
	/* Set INTUA0R lowest priority */
	UA0RIC |= 0x07;
	/* Set INTUA0T lowest priority */
	UA0TIC |= 0x07;
	#if 1
	UA0CTL1 = UARTA_BASECLK_FXX_1;
	UA0CTL2 = 139;			//bps = 115200 = 32M/(2*1*139)
	#else
	UA0CTL1 = UARTA_BASECLK_FXX_32;
	UA0CTL2 = 0x0d;			//bps = 38400 = 32M/(2*32*13)
	#endif
	UA0CTL0 = UARTA_TRANSFDIR_LSB | UARTA_PARITY_NONE | UARTA_DATALENGTH_8BIT | UARTA_STOPLENGTH_1BIT;
	UA0OPT0 = UARTA_UAnOPT0_INITIALVALUE | UARTA_TRAN_DATALEVEL_NORMAL | UARTA_REC_DATALEVEL_NORMAL;
	/* TXDA0 pin set */
	PFC3L &= 0xFE;
	PMC3L |= 0x01;
	/* RXDA0 pin set */
	PFC3L &= 0xFD;
	PMC3L |= 0x02;
#endif
}

void v850_uart0_Start(void)
{
#ifdef UART0_PRINT_ENABLE
	UA0TIF = 0;	/* clear INTUA0T interrupt flag */
	UA0TMK = 0;	/* INTUA0T interrupt enable */
	UA0RIF = 0;	/* clear INTUA0R interrupt flag */
	UA0RMK = 0;	/* INTUA0R interrupt enable */

	UA0PWR = 1;	/* enable UARTA0 operation */
	UA0TXE = 1;	/* enable transmission operation(uarta0) */
	UA0RXE = 1;	/* enable reception operation(uarta0) */
#endif
}

void v850_uart0_Stop(void)
{
#ifdef UART0_PRINT_ENABLE
	UA0TXE = 0;	/* disable transmission operation(uarta0) */
	UA0RXE = 0;	/* disable reception operation(uarta0) */
	UA0PWR = 0;	/* disable UARTA0 operation */
	UA0TMK = 1;	/* INTUA0T interrupt disable */
	UA0TIF = 0;	/* clear INTUA0T interrupt flag */
	UA0RMK = 1;	/* INTUA0R interrupt disable */
	UA0RIF = 0;	/* clear INTUA0R interrupt flag */
#endif
}
/*******************************************************************************
*-------------------------------------------------------------------------------
*
*  UART2   NO USE
*  BPS = ?
*
*******************************************************************************/
void v850_uart2_Init(void)
{

}

void v850_uart2_Start(void)
{

}

void v850_uart2_Stop(void)
{

}

/*******************************************************************************
*-------------------------------------------------------------------------------
*
*  UART3 Used for MCU<==>APU communication.
*  BPS = 115200
*
*******************************************************************************/
void v850_uart3_Init(void)
{
    UA3TXE = 0;    /* disable transmission operation(uarta3) */
    UA3RXE = 0;    /* disable reception operation(uarta3) */
    UA3PWR = 0;    /* disable UARTA3 operation */
    UA3TMK = 0;    /* INTUA3T interrupt disable */
    UA3TIF = 0;    /* clear INTUA3T interrupt flag */
    UA3RMK = 1;    /* INTUA3R interrupt disable */
    UA3RIF = 0;    /* clear INTUA3R interrupt flag */
    /* Set INTUA3R level 3 priority */
    UA3RIC &= 0xF8;
    UA3RIC |= 0x03;
    /* Set INTUA3T level 4 priority */
    UA3TIC &= 0xF8;
    UA3TIC |= 0x04;
    UA3CTL1 = UARTA_BASECLK_FXX_1; 
    UA3CTL2 =  139 ;//0x45 ;//UARTA3_BASECLK_DIVISION;
    UA3CTL0 = UARTA_TRANSFDIR_LSB | UARTA_PARITY_NONE | UARTA_DATALENGTH_8BIT | UARTA_STOPLENGTH_1BIT;
    UA3OPT0 = UARTA_UAnOPT0_INITIALVALUE | UARTA_TRAN_DATALEVEL_NORMAL | UARTA_REC_DATALEVEL_NORMAL;
    /* TXDA3 pin set */
    PMC8 |= 0x02;
    /* RXDA3 pin set */
    PMC8 |= 0x01;

}

void v850_uart3_Start(void)
{
    UA3TIF = 0;    /* clear INTUA3T interrupt flag */
    UA3TMK = 0;    /* INTUA3T interrupt disable */
    UA3RIF = 0;    /* clear INTUA3R interrupt flag */
    UA3RMK = 0;    /* INTUA3R interrupt enable */
    UA3PWR = 1;    /* enable UARTA3 operation */
    UA3TXE = 1;    /* enable transmission operation(uarta3) */
    UA3RXE = 1;    /* enable reception operation(uarta3) */

    /* TXDA3 pin set */
    PMC8 |= 0x02;
    /* RXDA3 pin set */
    PMC8 |= 0x01;
}

void v850_uart3_Stop(void)
{
    UA3TXE = 0;    /* disable transmission operation(uarta3) */
    UA3RXE = 0;    /* disable reception operation(uarta3) */
    UA3PWR = 0;    /* disable UARTA3 operation */
    UA3TMK = 1;    /* INTUA3T interrupt disable */
    UA3TIF = 0;    /* clear INTUA3T interrupt flag */
    UA3RMK = 1;    /* INTUA3R interrupt disable */
    UA3RIF = 0;    /* clear INTUA3R interrupt flag */

    PMC8 &= 0xfc;
    PM8 |= 0x03;
}


extern uint8_t seriSendEn;

void v850_uart3_Send(uint8_t *pData, uint8_t len)
{
	uint32_t cnt = 10000;
	uint8_t *ptr = pData;
	uint8_t i = 0;
	md_printf(_T("\nTX:-"));
	for(i = 0; i<len;i++)
	{
		cnt = 10000;
		while(UA3STR & 0x80)
		{
			cnt--;
			if(cnt)
			{
				if((cnt&0x0f) == 0)
				{
					CLEAR_WATCHDOG();
				}
			}
			else
			{
				MDI_LinkerInit(ENABLE);
				CLEAR_WATCHDOG();
				break;				
			}
		}
		md_printf(_T("%x-", *ptr));
		
		cnt = 10000;
//		if(i >0)
		{
			while(seriSendEn == 0)
			{
				{
					cnt--;
					if(cnt)
					{
						if((cnt&0x0f) == 0)
						{
							CLEAR_WATCHDOG();
						}
					}
					else
					{
						MDI_LinkerInit(ENABLE);
						CLEAR_WATCHDOG();
						break;				
					}
				}
					
			}
		}
		seriSendEn = 0;
		UA3TX = *ptr++;
		CLEAR_WATCHDOG();
	}
	md_printf(_T("\n"));
}
#if  (D_PRINT_EN == ON) 
#ifdef UART0_PRINT_ENABLE
void v850_putc(uint8_t d) {while(UA0STR & 0x80){};UA0TX = d;}
#endif
#endif
