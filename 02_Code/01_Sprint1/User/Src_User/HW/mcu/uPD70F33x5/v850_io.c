#include "v850_io_table.c"

void v850_io_init(void)
{
    uint8_t   idx;
    for(idx = 0;idx < PIN_N;idx++)
    {
        uint8_t tempIdx = lc_atPinDefTab[idx].cPinIdx;
        
	    uint8_t bInit = lc_atPinDefTab[idx].bInit;
	
        tPIN_REG* p_tReg = (tPIN_REG*)lc_atRegTab[tempIdx];
	    if(bInit == 0)  /*Default as input*/
	 	{
	 	    uint8_t n = (lc_atPinDefTab[idx].n<<1);
            *((uint8_t*)p_tReg->PMn) |= n;
	 	}
	 	else if(bInit == 1) /*Default as output 0*/
	 	{
	 	    uint8_t n =  ~(lc_atPinDefTab[idx].n<<1);
	 	    *((uint8_t*)p_tReg->Pn) &= n;
            *((uint8_t*)p_tReg->PMn) &= n;
            *((uint8_t*)p_tReg->Pn) &= n;
	 	}
	 	else if(bInit == 2) /*Default as output 1*/
	 	{
	 	    uint8_t n =  (lc_atPinDefTab[idx].n<<1);
	 	    *((uint8_t*)p_tReg->Pn) |= n;
            *((uint8_t*)p_tReg->PMn) &= (~n);
            *((uint8_t*)p_tReg->Pn) |= n;
	 	}
    }
}


bool  v850_get_pin(uint8_t idx,ePIN_DIRECTION dir)
{
    bool re = 0;
    tPIN_REG* p_tReg = (tPIN_REG*)lc_atRegTab[lc_atPinDefTab[idx].cPinIdx];
    uint8_t   n = lc_atPinDefTab[idx].n;

    
#define _PFn_ADD  (p_tReg->PFn)
#define _PMn_ADD  (p_tReg->PMn)
#define _Pn_ADD   (p_tReg->Pn)

    switch(n)
    {
        case 0:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit0 = od;
            ((tPIN_POS*)_PMn_ADD)->bit0 = dir;
            re = ((tPIN_POS*)_Pn_ADD)->bit0;
        break;
        case 1:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit1 = od;
            ((tPIN_POS*)_PMn_ADD)->bit1 = dir;
            re = ((tPIN_POS*)_Pn_ADD)->bit1;
        break;
        case 2:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit2 = od;
            ((tPIN_POS*)_PMn_ADD)->bit2 = dir;
            re = ((tPIN_POS*)_Pn_ADD)->bit2;
        break;
        case 3:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit3 = od;
            ((tPIN_POS*)_PMn_ADD)->bit3 = dir;
            re = ((tPIN_POS*)_Pn_ADD)->bit3;
        break;
        case 4:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit4 = od;
            ((tPIN_POS*)_PMn_ADD)->bit4 = dir;
            re = ((tPIN_POS*)_Pn_ADD)->bit4;
        break;
        case 5:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit5 = od;
            ((tPIN_POS*)_PMn_ADD)->bit5 = dir;
            re = ((tPIN_POS*)_Pn_ADD)->bit5;
        break;
        case 6:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit6 = od;
            ((tPIN_POS*)_PMn_ADD)->bit6 = dir;
            re = ((tPIN_POS*)_Pn_ADD)->bit6;
        break;
        case 7:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit7 = od;
            ((tPIN_POS*)_PMn_ADD)->bit7 = dir;
            re = ((tPIN_POS*)_Pn_ADD)->bit7;
        break;
    }
#undef _PFn_ADD
#undef _PMn_ADD
#undef _Pn_ADD
    return (re);
}

void  v850_set_pin(uint8_t idx,ePIN_DIRECTION dir/*,ePIN_OD_MODE od*/,bool pv)
{
    
    tPIN_REG* p_tReg = (tPIN_REG*)lc_atRegTab[lc_atPinDefTab[idx].cPinIdx];
    uint8_t   n = lc_atPinDefTab[idx].n;

#define _PFn_ADD  (p_tReg->PFn)
#define _PMCn_ADD  (p_tReg->PMCn)
#define _PMn_ADD  (p_tReg->PMn)
#define _Pn_ADD   (p_tReg->Pn)
    
    switch(n)   //先设值再设方向
    {
        case 0:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit0 = od;
            ((tPIN_POS*)_PMn_ADD)->bit0 = dir;
            ((tPIN_POS*)_Pn_ADD)->bit0 = pv;
            
            if(_PMCn_ADD)((tPIN_POS*)_PMCn_ADD)->bit0 = 0;
        break;
        case 1:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit1 = od;
            ((tPIN_POS*)_PMn_ADD)->bit1 = dir;
            ((tPIN_POS*)_Pn_ADD)->bit1 = pv;
            
            if(_PMCn_ADD)((tPIN_POS*)_PMCn_ADD)->bit1 = 0;
        break;
        case 2:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit2 = od;
            ((tPIN_POS*)_PMn_ADD)->bit2 = dir;
            ((tPIN_POS*)_Pn_ADD)->bit2 = pv;
            
            if(_PMCn_ADD)((tPIN_POS*)_PMCn_ADD)->bit2 = 0;
        break;
        case 3:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit3 = od;
            ((tPIN_POS*)_PMn_ADD)->bit3 = dir;
            ((tPIN_POS*)_Pn_ADD)->bit3 = pv;
            
            if(_PMCn_ADD)((tPIN_POS*)_PMCn_ADD)->bit3 = 0;
        break;
        case 4:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit4 = od;
            ((tPIN_POS*)_PMn_ADD)->bit4 = dir;
            ((tPIN_POS*)_Pn_ADD)->bit4 = pv;
            
            if(_PMCn_ADD)((tPIN_POS*)_PMCn_ADD)->bit4 = 0;
        break;
        case 5:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit5 = od;
            ((tPIN_POS*)_PMn_ADD)->bit5 = dir;
            ((tPIN_POS*)_Pn_ADD)->bit5 = pv;
            
            if(_PMCn_ADD)((tPIN_POS*)_PMCn_ADD)->bit5 = 0;
        break;
        case 6:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit6 = od;
            ((tPIN_POS*)_PMn_ADD)->bit6 = dir;
            ((tPIN_POS*)_Pn_ADD)->bit6 = pv; 
            
            if(_PMCn_ADD)((tPIN_POS*)_PMCn_ADD)->bit6 = 0;
        break;
        case 7:
            //if(_PFn_ADD)((tPIN_POS*)_PFn_ADD)->bit7 = od;
            ((tPIN_POS*)_PMn_ADD)->bit7 = dir;
            ((tPIN_POS*)_Pn_ADD)->bit7 = pv;
            
            if(_PMCn_ADD)((tPIN_POS*)_PMCn_ADD)->bit7 = 0;
        break;
    }
#undef _PFn_ADD
#undef _PMn_ADD
#undef _Pn_ADD
#undef _PMCn_ADD  

}


uint16_t v850_get_adc(uint8_t idx)
{
    uint16_t  iADValue;
    tADC_REG* p_tReg = (tADC_REG*)&tADC_reg;
    uint16_t* p_cData = (uint16_t*)(p_tReg->ADCBASEreg);
    uint16_t* pdir = (uint16_t*)(p_tReg->PMn);
    if(pdir)*pdir |= (1<<(idx));
    ADA0CE = 0;
    ADA0S = (idx);
    ADA0CE = 1;
    while(ADA0EF);
    iADValue = p_cData[idx]>>6;
    ADA0CE = 0;
    return (iADValue);
}


bool v850_set_pwm(uint8_t idx,uint8_t duty,uint32_t lFreq)
{
    bool re = TRUE;
    uint8_t dev_idx = 0;
    if(duty > 100) return FALSE;
    
    switch(idx)
    {
        case IO_PWM_PM_SNT_FREQ:    /*TOP61*/
            
            v850_tmp6_set_freq(lFreq);
            v850_tmp6_set_duty(duty);
            v850_tmp6_start(); 
            io_print(_T("PowerDC CTRL:Freq:%lx,duty:%d\n",lFreq,duty));
        break;
             
        case IO_PWM_FAN_CTRL:/*TOP41*/
        
            v850_tmp4_set_freq(lFreq);
            v850_tmp4_set_duty(duty);
            v850_tmp4_start();
            io_print(_T("FanCTRL:Freq:%d,duty:%d\n",lFreq,duty));
        break;
        
        case IO_PWM_KEY_LED:/*led_b_pwm  P50/TIQ01/KR0/TOQ01/RTP00 */
		case IO_PWM_PANEL_LED1:
		case IO_PWM_PANEL_LED2:/*P51/TIQ02/KR1/TOQ02*/
			if(idx == IO_PWM_KEY_LED)dev_idx = 1;
            else if(idx == IO_PWM_PANEL_LED1)dev_idx = 3;
            else dev_idx = 2;
			
            v850_tmq0_set_freq(lFreq);
            v850_tmq0_set_duty(dev_idx,duty);
            v850_tmq0_start();
            io_print(_T("LED(%d):Freq:%d,duty:%d\n",dev_idx,lFreq,duty));
			//hmi_printf(_T("LED(%d):Freq:%d,duty:%d\n",dev_idx,lFreq,duty));
        break;
        
        
        case IO_PWM_TFT_CTRL: /*TOP11/P35*/
            v850_tmp1_set_freq(lFreq);
            v850_tmp1_set_duty(duty);
            v850_tmp1_start();
            io_print(_T("TFT CTRL:duty:%d\n",duty));
        break;
       
    }
    return re;
}

void v850_pwm_init(void)
{
    PFC0 &= 0xfe;
    PMC0 &= 0xfe;
    PM0 |= 0x1;
    v850_tmp6_init();

    PFC9L |= 0x04;
    PFCE9L &= 0xfb;
    PMC9L &= 0xfb;
    PM9L |= 0x4;
    v850_tmp4_init();

    PFC5 |= 0x7;
    PFCE5 &= 0xf8;
    PMC5 &= 0xf8;
    PM5 |= 0x7;
    v850_tmq0_init();

    PFC3L &= 0xdf;
    PMC3L &= 0xdf;
    PM3L  |= 0x20;
    v850_tmp1_init();
}

////////////////////////////////////////////////////////////////////////////////
#define INTP4_EDGE_RISING_SEL           0x20    /* rising edge selected for INTP4 pin */
#define INTP4_EDGE_RISING_UNSEL         0x00    /* rising edge not selected for INTP4 pin */
#define INTP5_EDGE_RISING_SEL           0x40    /* rising edge selected for INTP5 pin */
#define INTP5_EDGE_RISING_UNSEL         0x00    /* rising edge not selected for INTP5 pin */
#define INTP4_EDGE_FALLING_SEL          0x20    /* falling edge selected for INTP4 pin */
#define INTP4_EDGE_FALLING_UNSEL        0x00    /* falling edge not selected for INTP4 pin */
#define INTP5_EDGE_FALLING_SEL          0x40    /* falling edge selected for INTP5 pin */
#define INTP5_EDGE_FALLING_UNSEL        0x00    /* falling edge not selected for INTP5 pin */
//
//ENCODE AB 中断
//
void v850_intp4_init(void)
{
    /* INTP4 Setting */
    PMK4 = 1;    /* INTP4 disable */
    PIF4 = 0;    /* INTP4 IF clear */
    /* Set INTP4 level 3 priority */
    PIC4 &= 0xF8;
    PIC4 |= 0x03;
    INTR9H |= INTP4_EDGE_RISING_SEL;
    INTF9H |= INTP4_EDGE_FALLING_SEL;
    /* INTP4 pin set */
    PFC9H |= 0x20;
    PMC9H |= 0x20;
}

void v850_intp4_enable(void)
{
    PIF4 = 0;        /* INTP4 IF clear */
    PMK4 = 0;        /* INTP4 enable */
}


//
//ENCODE CD 中断
//
void v850_intp5_init(void)
{
    /* INTP5 Setting */
    PMK5 = 1;    /* INTP5 disable */
    PIF5 = 0;    /* INTP5 IF clear */
    /* Set INTP5 level 4 priority */
    PIC5 &= 0xF8;
    PIC5 |= 0x04;
    INTR9H |= INTP5_EDGE_RISING_SEL;
    INTF9H |= INTP5_EDGE_FALLING_SEL;
    /* INTP5 pin set */
    PFC9H |= 0x40;
    PFCE9H &= 0xBF;
    PMC9H |= 0x40;
}
/*
**-----------------------------------------------------------------------------
**
**    Abstract:
**        This function INTP5 Clear interrupt flag and mask interrupt.
**
**    Parameters:
**        None
**
**    Returns:
**        None
**
**-----------------------------------------------------------------------------
*/
void v850_intp5_enable(void)
{
    PIF5 = 0;        /* INTP5 IF clear */
    PMK5 = 0;        /* INTP5 enable */
}

