/*********************(         Copyright 2009        )************************
 * FILE      :
 * INFOMATIN : v850外设控制文件，参照PDF以及applet2生成的代码
 * VERSION   : v00
 * DATA      : 27/03, 2013
 * AUTHOR    : yangyan
 *
 * UPDATE    :
 * ---------------------------------------------
 *   | INFOMATION 
 *   | VERSION
 *   | AUTHOR
 *   -------------------------------------------
 *     |  ......
 *     |  
 ******************************************************************************/
 #include "v850_clock.c"
#include "v850_dma.c"
#include "v850_timer.c"
#include "v850_io.c"
//#include "v850_i2c.c"
#include "v850_spi.c"
#include "v850_uart.c"

void v850_adc_init(void)
{
    ADA0CE = 0;
    ADMK = 1;
    ADIF = 0;
    ADA0M0 = 0x20;
    ADA0M1 = 0x83; 

    ADA0PFM = 0;
}

void v850_adc_stop(void)
{
    ADA0CE = 0;
}
/*
**-----------------------------------------------------------------------------
** 
**cpu 低功耗状态。clock设置，状态设置，IO设置等等 
**
**-----------------------------------------------------------------------------
*/



void v850_enter_lp_mode(void)
{
	v850_tmm0_stop();
	v850_tmq0_stop();
	//v850_tmm0_stop();
	v850_tmp5_stop();

	v850_uart2_Stop();
	v850_tmp6_stop();
	v850_tmp4_stop();
	v850_tmp1_stop();

	v850_adc_stop();

	v850_set_clock_sleep();

	
}

void v850_sleep(void)
{ 
    uint16_t i;
    v850_set_clock_sleep();
    for(i = 0; i < 80; i++){}
}

void v850_awake(void)
{
    v850_clock_init();
    v850_adc_init();
    LVI_Init();
    LVI_Start();
}

void v850_EnterStop(void)
{
	uint8_t value;

	PSMR = 0x01;			//select mode = STOP mode

	v850_diable_dma_prepare();

	OSTS = 0x04;			// set OSC valid time.
	
	value = PSC|BIT1;		//STP = Standy mode

	PRCMD = value; 
	PSC = value;
	for(value = 0; value<8; value++)
	{
		NOP();
	}
}


void v850_Enter_Sub_Idle(void)
{
	uint8_t value;
	uint32_t cCnt;
	uint8_t cErrCnt;

	//cCnt = 1000; // max that 1/ Fxt
	//cErrCnt = 0;
	
	#if 1
	/**** Sub 时钟模式切换 ****/ 
	value = PCC|0x08;
	PRCMD = value;
	PCC = value;/* 选择Sub时钟Fxt */ 
	while( 1 )
	{   
		CLEAR_WATCHDOG();
		if( CLS == 1 )
		{ 
			break; 
		} 
	} 
	#else
	//v850_set_subclock_as_Fcpu();
	#endif
	
	P9H |= 0x10;//TEST if  CLS is success

	
	for(value = 0; value<8; value++)
	{
		NOP();
		//CLEAR_WATCHDOG();
	}


	/**** 主时钟停止 ****/ 
	SELPLL = 0;
	for(value = 0; value<8; value++)
	{
		NOP();
		//CLEAR_WATCHDOG();
	}
 	
	PLLON = 0; /* PLL停止 */ 
	PRCMD = 0x00; 
	MCK = 1;/* 主时钟停止 */ 

	
	/**** Sub IDLE模式切换 ****/ 
	PSMR = 0x02; 
	PRCMD = 0x00; 
	//PSC.1 = 1;    /* SubIDLE模式设定 */ 
	STP = 1;

	for(value = 0; value<8; value++)
	{
		NOP();
		//CLEAR_WATCHDOG();
	}
    
}



void v850_Enter_Sub_Idle_another(void)
{
	uint8_t value;

	//cpu_lowpower();
	v850_set_clock_sleep();
	
	//P9H |= 0x10;//TEST if  CLS is success
	/**** Sub IDLE模式切换 ****/ 
	PSMR = 0x02; 
	PRCMD = 0x00; 
	//PSC.1 = 1;    /* SubIDLE模式设定 */ 
	STP = 1;
	for(value = 0; value<8; value++)
	{
		NOP();
		//CLEAR_WATCHDOG();
	}
    
}

/*
**-----------------------------------------------------------------------------
** 
**cpu 初始化
**
**-----------------------------------------------------------------------------
*/


void v850_init(void)
{
    DI();
    v850_clock_init();
    LVI_Init();
    LVI_Start();
    v850_tmm0_init();

    v850_uart0_Init();
    v850_uart0_Start();
    v850_uart2_Init();
    v850_uart2_Start();
    v850_uart3_Init();
    v850_uart3_Start();
    v850_adc_init();
    v850_tmq0_init();
    v850_spi1_disable();
    EI();
    v850_tmm0_start();
    v850_tmp6_init();

	INTP0_Init();
	INTP3_Init();
	
	INTP3_Enable();//snake20160922
	
	PMCM&=(~0X02);
	PMCCM|=0X02;
/*
	PM6L &= (~0x08);
	PMC6L &= (~0x08);
	P6L |= 0x08;
	*/
	PM9H &= (~0X18) ;
	PMC9H &= (~0X18) ;
	PF9H &= (~0X18);
	P9H  &= (~0X18);
   
}


void  INTP3_Init(void)
{
	/* INTP3 Setting */
	PMK3 = 1;    /* INTP3 disable */
	PIF3 = 0;        /* INTP3 IF clear */

	/* Set INTP3 lowest priority */
	PIC3 |= 0x07;

	INTF0 |= 0x40;
	INTR0 &= (~0x40);//INTP3_EDGE_FALLING_SEL;

	/* INTP3 pin set */
	PMC0 |= 0x40;
}


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function INTP3 Clear interrupt flag and mask interrupt.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void INTP3_Enable(void)
{
	PIF3 = 0;		/* INTP3 IF clear */
	PMK3 = 0;		/* INTP3 enable */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function INTP3 Mask interrupt and clear interrupt flag.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void INTP3_Disable(void)
{
	PMK3 = 1;		/* INTP3 disable */
	PIF3 = 0;		/* INTP3 IF clear */
}




/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */

void INTP3_isr(void)
{
	g_flag_isr.bit1.flag_ill = 1;
	//g_flag_isr.bit1.flag_watchtime = 0;	

	//P9H  |= 0X18;
}

void  INTP0_Init(void)
{
	/* INTP0 Setting */
	PMK0 = 1;    /* INTP0 disable */
	PIF0 = 0;        /* INTP0 IF clear */

	/* Set INTP3 lowest priority */
	PIC0 |= 0x07;

	INTF0 &= (~0x08);
	INTR0 |= (~0x08);//INTP0_EDGE_RISING_SEL;

	/* INTP0 pin set */
	PMC0 |= 0x08;
}


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function INTP0 Clear interrupt flag and mask interrupt.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void INTP0_Enable(void)
{
	PIF0 = 0;		/* INTP0 IF clear */
	PMK0 = 0;		/* INTP0 enable */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function INTP0 Mask interrupt and clear interrupt flag.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void INTP0_Disable(void)
{
	PMK0 = 1;		/* INTP0 disable */
	PIF0 = 0;		/* INTP0 IF clear */
}

void INTP0_isr(void)
{
	g_flag_isr.bit1.flag_acc = 1;
	//g_flag_isr.bit1.flag_watchtime = 0;	

	//P9H  &= (~0X18);
}


void Disable_External_Interrupt(void)
{
	INTF0 = 0X00;
	INTR0 = 0x00;
	
	INTF3 = 0x00;
	INTR3 = 0x00;

	INTF8 = 0x00;
	INTR8 = 0x00;	

	INTF9H = 0x00;
	INTR9H = 0x00;	
}

void Close_Peripheral(void)
{
	v850_tmm0_stop();
	v850_tmq0_stop();
	//v850_tmm0_stop();
	v850_tmp5_stop();

	v850_uart2_Stop();
	v850_tmp6_stop();
	v850_tmp4_stop();
	v850_tmp1_stop();

	v850_adc_stop();

	v850_diable_dma_prepare();
}

void WakeUp_Mode(void)
{
	uint8_t value;
	
	value = 0X60;
	PRCMD = value;
	PSC = value;
}

void Disable_INTP0_Trigger(void)
{
	INTF0 &= (~0x08);
	INTR0 &= (~0x08);
}

void Disable_INTP3_Trigger(void)
{
	INTF0 &= (~0x40);
	INTR0 &= (~0x40);
}

void Enable_INTP0_Trigger(void)//INTP0_EDGE_RISING_SEL
{
	INTF0 &= (~0x08);
	INTR0 |= 0x08;
}

void Enable_INTP3_Trigger(void)//INTP3_EDGE_FALLING_SEL
{
	INTF0 |= 0x40;
	INTR0 &= (~0x40);
}

