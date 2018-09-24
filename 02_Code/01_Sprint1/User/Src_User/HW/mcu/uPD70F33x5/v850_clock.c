
/**********************************************************
 * @function    v850_diable_dma_prepare
 * @brief      
 *            Disable DMA prepare  for operate special register
 * @param      none
 * @retval     none
 **********************************************************/  
void v850_diable_dma_prepare(void)
{

    if(1 == DCHC0)
    {
        DCHC0 = 0;
    }
    if(1 == DCHC1)
    {
        DCHC1 = 0;
    }
    if(1 == DCHC2)
    {
        DCHC2 = 0;
    }
    if(1 == DCHC3)
    {
        DCHC3 = 0;
    }
}



/**********************************************************
 * @function    v850_enable_rc_clock
 * @brief      
 *            Enable RC clock for system
 * @param      none
 * @retval     none
 **********************************************************/  
bool v850_enable_rc_clock(uint32_t Counter)
{
    uint32_t cCnt;
    

    RSTOP = 0;      
    cCnt = Counter;
    while(1)
    {        
        CLEAR_WATCHDOG();
        if(cCnt)cCnt--;
        if(cCnt == 0)
        {
            break;
        }
    }
    return TRUE;
}


/**********************************************************
 * @function    v850_enable_rc_clock
 * @brief      
 *            Disable RC clock for system
 * @param      none
 * @retval     none
 **********************************************************/  
bool v850_disable_rc_clock(void)
{

    RSTOP = 1;
    return TRUE;

}


/**********************************************************
 * @function    v850_enable_main_clock
 * @brief      
 *            Enable main clock for system
 * @param      none
 * @retval     none
 **********************************************************/
bool v850_enable_main_clock(void)
{
    uint32_t cCnt;
    bool re;
    uint8_t cVal = 0;
    
    re = TRUE;
//    if((CCLS == 0) && (CLS == 0) &&((PCC & 0x03)==0))
//    return re;

    if(CLS == 1)
    {
        cCnt = 2;  /* > 2ms */
    }
    else
    {
        cCnt = 10000; /* >2ms */
    }
    cVal = PCC;
    cVal &= ~(CG_MAINCLK_STOP);        /* enable main clock */
    cVal &= ~0x07;
    cVal |= CG_CPUCLK_MAIN0; /* select fxx as fcpu */
    PRCMD = cVal;
    PCC = cVal;
    while(1)
    {
        CLEAR_WATCHDOG();
        if(cCnt)cCnt--;
        if(cCnt == 0)
        {
            break;
        }
    }

    return re;

}


/**********************************************************
 * @function    v850_diable_main_clock
 * @brief      
 *            Disable main clock for system
 * @param      none
 * @retval     none
 **********************************************************/
bool v850_diable_main_clock(void)
{
    bool re;
    uint8_t cVal = 0;
    
    re = TRUE;
    
    
    cVal = PCC;
    cVal |= CG_MAINCLK_STOP;
    PRCMD = cVal;
    PCC = cVal;
    
    return re;

}


/**********************************************************
 * @function    v850_set_main_clcok_for_Fcpu
 * @brief      
 *            set main clock as cpu freq
 * @param      none
 * @retval     
 *            TRUE:    set cpu freq success
 *            FALSE:     set cpu freq false
 **********************************************************/
bool v850_set_main_clcok_for_Fcpu(void)
{
    bool re;
    uint32_t cCnt;
    uint8_t cErrCnt;
    uint8_t cVal = 0;
    
    re = TRUE;

    
    cVal = PCC;
    cVal &= ~(0x08);    // Clr bit ck3
    PRCMD = cVal;
    PCC = cVal;
    
    cCnt = 400; // max that 1/ Fxt
    cErrCnt = 0;
    while(1)
    {
        CLEAR_WATCHDOG();
        if(cCnt)cCnt--;
        if(CLS == 0)    
            break;
        if(cCnt == 0)
        {
            cErrCnt++;
            cCnt = 400; // max that 1/ Fxt
            cVal = PCC;
            cVal &= ~(0x08);    // Clr bit ck3
            PRCMD = cVal;
            PCC = cVal;
    
            if(cErrCnt>3)
            {
                re = FALSE;
                break;
            }
        }
    }
    return re;
}


/**********************************************************
 * @function    v850_enable_PLL
 * @brief      
 *            enable PLL clock 
 * @param      
 *            lWaitCnt:     time out counter when setting PLL clock
 * @retval     
 *            TRUE:    enable PLL clock success
 *            FALSE:     enable PLL clock false
 **********************************************************/
bool v850_enable_PLL(uint32_t lWaitCnt)
{
    uint32_t cCnt;
    uint8_t cErrCnt;
    bool re;
    uint8_t cVal = 0;
    uint8_t LockTemp;
    PLLON = 0;
    PLLS = 0x03;
    cVal = CG_CKC_INITIALVALUE | CG_CPUCLK_8PLL;
    PRCMD = cVal;
    CKC = cVal;        
    PLLON = 1;
    cCnt = lWaitCnt; // max that 1/ Fxt
    cErrCnt = 0;
    while(1)
    {
        CLEAR_WATCHDOG();
        if(cCnt)cCnt--;
        NOP();
        LockTemp = LOCK;
        if(0 == LockTemp)
        {
            re = TRUE;
            break;
        }
        if(cCnt == 0)
        {
            cErrCnt++;
            cCnt = lWaitCnt; // max that 1/ Fxt
            PLLON = 0;
            PLLS = 0x03;
            cVal = CG_CKC_INITIALVALUE | CG_CPUCLK_8PLL;
            PRCMD = cVal;
            CKC = cVal;        
            PLLON = 1;
    
            if(cErrCnt>3)
            {
                re = FALSE;
                break;
            }
        }
    }
    return re;

}


/**********************************************************
 * @function    v850_disable_PLL
 * @brief      
 *            Disable PLL clock
 * @param      none
 * @retval     TRUE:    Disable PLL clock done
 **********************************************************/
bool v850_disable_PLL(void)
{
    PLLON = 0;
    return TRUE;
}


/**********************************************************
 * @function    v850_set_PLL_as_Fcpu
 * @brief      
 *            set PLL clock as cpu freq
 * @param      none
 * @retval     
 *            TRUE:    setting success
 *            FALSE:     setting false
 **********************************************************/
bool v850_set_PLL_as_Fcpu(void)
{
    bool LockTemp;
    LockTemp = LOCK;
    if(0 == LockTemp)
    {
        SELPLL = 1;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}




/**********************************************************
 * @function    v850_set_subclock_as_Fcpu
 * @brief      
 *            set sub clock as cpu freq
 * @param      none
 * @retval     
 *            TRUE:    setting success
 *            FALSE:     setting false
 **********************************************************/
bool v850_set_subclock_as_Fcpu(void)
{
    bool re;
    uint32_t cCnt;
    uint8_t cErrCnt;
    uint8_t cVal = 0;
    
    re = TRUE;
    
//    if(CLS == 1)    
//        return re;
    
    cVal = PCC;
    cVal |= 0x08;    // Set bit ck3
    PRCMD = cVal;
    PCC = cVal;
    
    cCnt = 1000; // max that 1/ Fxt
    cErrCnt = 0;
    while(1)
    {
        CLEAR_WATCHDOG();
        if(cCnt)cCnt--;
        if(CLS == 1)    
            break;
        if(cCnt == 0)
        {
            cErrCnt++;
            cCnt = 1000; // max that 1/ Fxt
            cVal = PCC;
            cVal |= 0x08;    // Set bit ck3
            PRCMD = cVal;
            PCC = cVal;
    
            if(cErrCnt>3)
            {
                re = FALSE;
                break;
            }
        }
    }
    return re;
}


/**********************************************************
 * @function    System_OtherClockSetting
 * @brief      
 *            setting the other parameter about colck
 * @param      none
 * @retval     none
 **********************************************************/
void v850_set_clock_other(void)
{
    uint8_t cVal = 0;
    
    PRSM0 = CG_FBRG_PRSM0;
    PRSCM0 = CG_FBRG_PRSCM0;
    BGCE0 = 1;

    /* Stand-by setting */
    cVal = CG_STANDBY_INTWDT2EN | CG_STANDBY_NMIEN | CG_STANDBY_MASKIEN;
    PRCMD = cVal;
    PSC = cVal;

    //WDT2 setting  
    //WDTM2 = 0x4f;
}







/**********************************************************
 * @function    v850_set_sleep
 * @brief      
 *            this function used to setting sub clock as system clock,
 *            for sleep mode
 * @param      none
 * @retval     0/1
 **********************************************************/
bool v850_set_clock_sleep( void )
{
    uint32_t DlyCnt=0;
    bool re;
    re = TRUE;
    v850_diable_dma_prepare    ();
    
    SELPLL = 0;
    for(DlyCnt = 0; DlyCnt<8; DlyCnt++)
    {
        NOP();
    }
    
    re = v850_disable_PLL();

    if(TRUE == re)
    {
        re = v850_set_subclock_as_Fcpu();
    }

    if(TRUE == re)
    {
        VSWC = 0x0;    // set system wait cntrol register as wait 0 for 32.768kHz system colck
        re = v850_diable_main_clock();
    }

    return re;
    
}










/*
**-----------------------------------------------------------------------------
** 时钟设置: 正常状态全速跑。低功耗状态请重设
** 4M晶振，32M主频，CPUclock 32M。PLL LOCK TIME 2048us 内部时钟220K开启
**-----------------------------------------------------------------------------
*/

void v850_clock_init(void)
{
    bool re;
    uint8_t cCnt = 100;
    re = FALSE;
    v850_diable_dma_prepare();

    VSWC = 0x11;  /* set system wait cntrol register as wait 2 for 32Mhz system colck*/
    OSTS = 0x03;  /*set fx shake stable time  as 4Mhz :2.048ms     5Mhz 1.638Mhz*/
    
    while(cCnt && !re)
    {
        cCnt --;
        re = v850_enable_main_clock();    // 2^13 = 8192 
    
        if(TRUE == re)
        {
            re = v850_set_main_clcok_for_Fcpu();
        }
    
        if(TRUE == re)
        {
            re = v850_enable_PLL(10000);
        }
    
        if(TRUE == re)
        {
            re = v850_set_PLL_as_Fcpu();
        }
    
        if(TRUE == re)
        {
            re = v850_disable_rc_clock();
        }
    
        if(TRUE == re)
        {
            v850_set_clock_other();
        }
    }

}

#define NMI_EDGE_RISING_SEL               0x04    /* rising edge selected for NMI pin */
#define NMI_EDGE_RISING_UNSEL             0x00    /* rising edge not selected for NMI pin */
#define NMI_EDGE_FALLING_SEL              0x04    /* falling edge selected for NMI pin */
#define NMI_EDGE_FALLING_UNSEL            0x00    /* falling edge not selected for NMI pin */

void LVI_Init(void)
{
	//屏蔽LVI的初始化
	//统一冷启动的时候,在Boot的时候,开启LVI功能
	//同步更新BOOT
	#if 0
	PRCMD = 0;
	LVION = 0;	/* LVI disable */
	LVIMK = 1;	/* INTLVI disable */
	LVIIF = 0;	/* INTLVI IF clear */
	LVIS = 0;
	#endif
}

MD_STATUS LVI_Start(void)
{
	return 0;
	#if 0
	MD_STATUS status = MD_OK;
	uint32_t i;
	
	/* LVI enable */
	PRCMD = 1;
	LVION = 1;
	/* Wait 0.2 ms */
	for( i = 0; i <= 100; i++ )
	{	
		NOP();	
	}
	/* Generate an internal reset signal */
	if (LVIF == 1)
	{
		status = MD_ERROR;
	}
	else
	{
		PRCMD = 1;
		LVIMD = 1;
	}

	return (status);
	#endif
}


void LVI_Stop(void)
{
	/* LVI disable */
	PRCMD = 0;
	LVION = 0;
}

void v850_nmi_lvi_enable(void)
{  
    /* NMI Setting */
    INTR0 |= NMI_EDGE_RISING_UNSEL;
    INTF0 |= NMI_EDGE_FALLING_SEL;
    /* NMI pin set */
    PMC0 |= 0x04;
    PM0 |= 4;
#if 0
    PRCMD = 0;
    LVION = 0;    /* LVI disable */
    LVIMK = 1;    /* INTLVI disable */
    LVIIF = 0;    /* INTLVI IF clear */
    /* Set INTLVI lowest priority */
    LVIIC |= 0x07;
    /* Generate interrupt signal INTLVI */
    PRCMD = 0;
    LVIMD = 0;
    LVIS = 0;

    
    
    /* LVI enable */
    PRCMD = 1;
    LVION = 1;
    /* Wait 0.2 ms */
    for( i = 0; i <= 8000; i++ )
    {    
        NOP();    
    }
    LVIIF = 0;    /* INTLVI IF clear */
    LVIMK = 0;    /* INTLVI enable */
#endif
}

void v850_nmi_lvi_disable(void)
{
     /* NMI Setting */
    INTR0 &= ~NMI_EDGE_RISING_SEL;
    INTF0 &= ~NMI_EDGE_FALLING_SEL;
    /* NMI pin set */
    PMC0 |= 0x04;
    PM0 |= 4;
#if 0
    PRCMD = 0;
    LVION = 0;    /* LVI disable */
    LVIMK = 1;    /* INTLVI disable */
    LVIIF = 0;    /* INTLVI IF clear */
    /* Set INTLVI lowest priority */
    LVIIC |= 0x07;
    /* Generate interrupt signal INTLVI */
    PRCMD = 0;
    LVIMD = 0;
    LVIS = 0;
#endif
}


/*
**-----------------------------------------------------------------------------
** 重置看门狗
**-----------------------------------------------------------------------------
*/
void v850_wdt2_reset(void)
{
    WDTE = 0xac;    /* restart watch dog timer2 */
}

void v850_wdt2_init(void)
{
    WDTM2 = WDT2_OPERMODE_RESET|WDT2_CLKMODE_SUBCLK|WDT2_CLOCK_SEL7;
}

/*
**-----------------------------------------------------------------------------
** 钟表定时器，500MS中断
**-----------------------------------------------------------------------------
*/
#define WT_CLOCK_SELECT_FXT            0x00    /* fW = fXT */
#define WT_CLOCK_SELECT_FBRG           0x80    /* fW = fBRG */
/* Selection of set time of watch flag (WTM2, WTM3) */
#define WT_WATCHFLAG_TIME_0            0x00    /* 2^14/fW */
#define WT_WATCHFLAG_TIME_1            0x04    /* 2^13/fW */
#define WT_WATCHFLAG_TIME_2            0x08    /* 2^5/fW */
#define WT_WATCHFLAG_TIME_3            0x0C    /* 2^4/fW */
/* Selection of watch timer interrupt time (WTM4~WTM6) */
#define WT_INTERVAL_TIME_0             0x00    /* 2^4/fW */
#define WT_INTERVAL_TIME_1             0x10    /* 2^5/fW */
#define WT_INTERVAL_TIME_2             0x20    /* 2^6/fW */
#define WT_INTERVAL_TIME_3             0x30    /* 2^7/fW */
#define WT_INTERVAL_TIME_4             0x40    /* 2^8/fW */
#define WT_INTERVAL_TIME_5             0x50    /* 2^9/fW */
#define WT_INTERVAL_TIME_6             0x60    /* 2^10/fW */
#define WT_INTERVAL_TIME_7             0x70    /* 2^11/fW */
/* Control of 5-bit counter operation (WTM1) */
#define WT_COUNTER_STOP                0x00    /* Clears after operation stops */
#define WT_COUNTER_START               0x02    /* Starts */
/* Watch timer operation enable (WTM0) */
#define WT_OPERATION_DISABLE           0x00    /* Stops operation (clears both prescaler and 5-bit counter) */
#define WT_OPERATION_ENABLE            0x01    /* Enables operation */


void v850_wt_init(void)
{
    WTM = 0x00;    /* watch timer stop */
    WTMK = 1;    /* INTWT disable */
    WTIF = 0;    /* INTWT IF clear */
    WTIMK = 1;    /* INTWTI disable */
    WTIIF = 0;    /* INTWTI IF clear */
    /* Set INTWT level 5 priority */
    WTIC &= 0xF8;
    WTIC |= 0x05;
    /* Set INTWTI lowest priority */
    WTIIC |= 0x07;
    WTM = WT_CLOCK_SELECT_FXT | WT_WATCHFLAG_TIME_0 | WT_INTERVAL_TIME_0;
    
    WTMK = 0;    /* INTWT enable */
    WTM |= (WT_COUNTER_START | WT_OPERATION_ENABLE);    /* watch timer start */
}

void v850_wt_stop(void)
{
    WTM = 0x00;
}



