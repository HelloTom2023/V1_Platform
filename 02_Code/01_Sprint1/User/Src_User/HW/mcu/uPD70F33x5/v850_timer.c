/**********************************************************
 * @function    v850_tmm0 function!
 * @brief      This function for TMM). It is used to make the system time tick!
 * @param      none
 * @retval     none
 **********************************************************/

void v850_tmm0_init(void)
{
    TM0CE = 0;       /* TMM0 operation disable */
    TM0EQMK0 = 1;    /* INTTM0EQ0 interrupt disable */
    TM0EQIF0 = 0;    /* clear INTTM0EQ0 interrupt flag */
    
    TM0EQIC0 &= 0xF8;/* Set INTTM0EQ0 level 1 priority */
    TM0EQIC0 |= 0x06;
    TM0CTL0 = 0;     //Fxx=32m
    TM0CMP0 = (32000/D_CORE_TIMER_INT_NUM_IN_1MS)-1; //0.001/(1/32000000)- 1 = 31999 1mstick 15999->500us
}

void v850_tmm0_start(void)        
{
    TM0EQIF0 = 0;    /* clear INTTM0EQ0 interrupt flag */
    TM0EQMK0 = 0;    /* INTTM0EQ0 interrupt enable */
    TM0CE = 1;       /* TMM0 operation enable */
}

void v850_tmm0_stop(void)
{
    TM0CE = 0;       /* TMM0 operation disable */
    TM0EQMK0 = 1;    /* INTTM0EQ0 interrupt disable */
    TM0EQIF0 = 0;    /* clear INTTM0EQ0 interrupt flag */
}


/**********************************************************
 * @function    v850_tmp6 function TOP61 will output pwm!
 * @brief      This function for TMP6 . It is used to control DC_DC feq!
 * @param      none
 * @retval     none
 **********************************************************/

void v850_tmp6_init(void)
{
    TP6CE = 0;    /* TMP6 operation disable */
    TP6CCMK0 = 1;    /* INTTP6CC0 interrupt disable */
    TP6CCIF0 = 0;    /* clear INTTP6CC0 interrupt flag */
    TP6CCMK1 = 1;    /* INTTP6CC1 interrupt disable */
    TP6CCIF1 = 0;    /* clear INTTP6CC1 interrupt flag */
    TP6OVMK = 1;    /* INTTP6OV interrupt disable */
    TP6OVIF = 0;    /* clear INTTP6OV interrupt flag */
    /* PWM mode setting */
    TP6CTL0 = TMP_INTERNAL_CLOCK;
    TP6CTL1 = TMP_INTERNAL_CLOCK|TMP_MODE_PWM;
    TP6CCR0 = 0x3f;  //500K
    TP6CCR1 = 0;
    TP6IOC0 = TMP_OUTPUT1_NORMAL | TMP_OUTPUT1_ENABLE | TMP_OUTPUT0_NORMAL | TMP_OUTPUT0_DISABLE;
    
}


void v850_tmp6_start(void)
{
     if(0 == TP6CE)
     {
         TP6CE = 1;    /* TMp6 operation enable */
         /* TOP61 pin set */
         PFC0 |= 0x01;
         PMC0 |= 0x01;
     }
}

void v850_tmp6_stop(void)
{
    TP6CE = 0;    /* TMp6 operation disable */
    /* TOP61 pin set */
    PFC0 &= 0xfe;
    PMC0 &= 0xfe;
}

void v850_tmp6_set_freq(uint32_t freq)
{
    uint32_t tmp3 = (uint16_t)(32000000/freq);
    uint32_t tmp0 = TP6CCR0;
    
    if(tmp0 != tmp3 - 1)
    {
        uint32_t tmp1 = TP1CCR1;
        TP6CCR0 = tmp3-1;
        TP6CCR1 = (tmp3*tmp1)/(tmp0);
    }
    
}

void v850_tmp6_set_duty(uint8_t duty)
{
    uint32_t cycle = TP6CCR0 + 1;
    uint32_t reg = 0;
    
    reg = cycle * duty / 100;
    TP6CCR1 = (uint16_t)reg;
}

/**********************************************************
 * @function    v850_tmp6 function TOP41 will out put PWM! 
 * @brief      This function for TMP4 . It used to control Fan speed 
 * @param      none
 * @retval     none
 **********************************************************/

void v850_tmp4_init(void)
{
    TP4CE = 0;    /* TMP6 operation disable */
    TP4CCMK0 = 1;    /* INTTP6CC0 interrupt disable */
    TP4CCIF0 = 0;    /* clear INTTP6CC0 interrupt flag */
    TP4CCMK1 = 1;    /* INTTP6CC1 interrupt disable */
    TP4CCIF1 = 0;    /* clear INTTP6CC1 interrupt flag */
    TP4OVMK = 1;    /* INTTP6OV interrupt disable */
    TP4OVIF = 0;    /* clear INTTP6OV interrupt flag */
    /* PWM mode setting */
    TP4CTL0 = TMP_INTERNAL_CLOCK;
    TP4CTL1 = 4;
    TP4CCR0 = 0x3f;  //500K
    TP4CCR1 = 0;
    TP4IOC0 = TMP_OUTPUT1_INVERTED| TMP_OUTPUT1_ENABLE | TMP_OUTPUT0_NORMAL | TMP_OUTPUT0_DISABLE;
    
}



void v850_tmp4_start(void)
{
     if(0 == TP4CE)
     {
          TP4CE = 1;    /* TMP4 operation enable */
          /* TOP41 pin set */
          PFC9L  &= 0xFB;
          PFCE9L |= 0x04;
          PMC9L  |= 0x04;
      }
}

void v850_tmp4_stop(void)
{
    TP4CE = 0;    /* TMP4 operation disable */
    /* TOP41 pin set */
    PFC9L  |= 0x6;
    PFCE9L &= 0xfb;
    PMC9L  &= 0xfb;
}

void v850_tmp4_set_freq(uint32_t freq)
{
    uint32_t tmp3 = (uint16_t)(32000000/freq);
    uint32_t tmp0 = TP4CCR0;

    if(tmp0 != tmp3 - 1)
    {
        uint32_t tmp1 = TP4CCR1;
        TP4CCR0 = tmp3-1;
        TP4CCR1 = (tmp3*tmp1)/(tmp0);
    }
    
}


void v850_tmp4_set_duty(uint8_t duty)
{
    uint32_t cycle = TP4CCR0 + 1;
    uint32_t reg = 0;
    uint32_t tmp = TP4CCR1;
    
    reg = cycle * duty / 100;

    TP4CCR1 = (uint16_t)reg;
    

}

/**********************************************************
 * @function    v850_tmp6 function TOP81 will capture the wave!
 * @brief      This function for TMP8 .
 * @param      none
 * @retval     none
 **********************************************************/

void v850_tmp8_init(void)
{
    TP8CE = 0;    /* TMP8 operation disable */
    TP8CCMK0 = 1;    /* INTTP8CC0 interrupt disable */
    TP8CCIF0 = 0;    /* clear INTTP8CC0 interrupt flag */
    TP8CCMK1 = 1;    /* INTTP8CC1 interrupt disable */
    TP8CCIF1 = 0;    /* clear INTTP8CC1 interrupt flag */
    TP8OVMK = 1;    /* INTTP8OV interrupt disable */
    TP8OVIF = 0;    /* clear INTTP8OV interrupt flag */
    /* Set INTTP8CC0 lowest priority */
    TP8CCIC0 |= 0x07;
    /* Set INTTP8CC1 lowest priority */
    TP8CCIC1 |= 0x07;
    /* Free-running mode setting */
    TP8CTL0 = TMP_INTERNAL_CLOCK5;    /* fxx/32  1MHz */
    TP8CTL1 = TMP_INTERNAL_CLOCK | TMP_MODE_FREERUNNING;
    TP8OPT0 = TMP_CCR1_COMPARE | TMP_CCR0_CAPTURE;
    TP8IOC1 = TMP_INPUT1_EDGE_NONE | TMP_INPUT0_EDGE_BOTH;
    //TP8CCR0 = TMP8_CCR0_VALUE;
    //TP8CCR1 = TMP8_CCR1_VALUE;
    TP8IOC0 = TMP_OUTPUT1_NORMAL | TMP_OUTPUT1_DISABLE | TMP_OUTPUT0_NORMAL | TMP_OUTPUT0_ENABLE;
    /* TOP80 pin set */
    PFC6H &= ~0x10;
    PMC6H |= 0x10;
}



void v850_tmp8_set_captrue(void)
{
    TP8OPT0 |= TMP_CCR0_CAPTURE;    /* set capture mode */
    PFC6H   &= ~0x10;    
    PMC6H   |= 0x10;
    PM6H    |= 0x10;
}


/**********************************************************
 * @function    v850_tmp8_start
 * @brief      This function starts TMP8 counter.
 * @param      none
 * @retval     none
 **********************************************************/
void v850_tmp8_start(void)
{
    TP8CCIF0 = 0;    /* clear INTTP8CC0 interrupt flag */
    TP8CCMK0 = 0;    /* INTTP8CC0 interrupt enable */
    TP8CCMK1 = 1;    /* INTTP8CC1 interrupt Disable */
    TP8CCIF1 = 0;    /* clear INTTP8CC1 interrupt flag */
    TP8CE = 1;    /* TMP8 operation enable */
}


/**********************************************************
 * @function    v850_tmp8_stop
 * @brief      This function stops TMP8 counter.
 * @param      none
 * @retval     none
 **********************************************************/
void v850_tmp8_stop(void)
{
    TP8CE = 0;    /* TMP8 operation disable */
    TP8CCMK0 = 1;    /* INTTP8CC0 interrupt disable */
    TP8CCIF0 = 0;    /* clear INTTP8CC0 interrupt flag */
    TP8CCMK1 = 1;    /* INTTP8CC1 interrupt disable */
    TP8CCIF1 = 0;    /* clear INTTP8CC1 interrupt flag */
    PMC6H &= ~0x10;
}




/**********************************************************
 * @function    Timer5 is used to control the owc wave output!!
 * @function    v850_tmp5_init
 * @brief        TMP5 set.
 * @param    none
 * @retval    none
 **********************************************************/


void v850_tmp5_init(void)
{
    TP5CE = 0;    /* TMP5 operation disable */
    TP5CCMK0 = 1;    /* INTTP5CC0 interrupt disable */
    TP5CCIF0 = 0;    /* clear INTTP5CC0 interrupt flag */
    TP5CCMK1 = 1;    /* INTTP5CC1 interrupt disable */
    TP5CCIF1 = 0;    /* clear INTTP5CC1 interrupt flag */
    TP5OVMK = 1;    /* INTTP5OV interrupt disable */
    TP5OVIF = 0;    /* clear INTTP5OV interrupt flag */
    /* Set INTTP5CC0 lowest priority */
    TP5CCIC0 |= 0x07;
    /* Set INTTP5CC1 lowest priority */
    TP5CCIC1 |= 0x07;
    /* Set INTTP5OV lowest priority */
    TP5OVIC |= 0x07;
    /* Free-running mode setting */
    TP5CTL0 = TMP_INTERNAL_CLOCK5;
    TP5CTL1 = TMP_INTERNAL_CLOCK | TMP_MODE_FREERUNNING;
    TP5OPT0 = TMP_CCR1_COMPARE | TMP_CCR0_COMPARE;
    TP5IOC1 = TMP_INPUT1_EDGE_NONE | TMP_INPUT0_EDGE_NONE;
}


void v850_tmp5_start(void)
{
    TP5CCIF0 = 0;    /* clear INTTP5CC0 interrupt flag */
    TP5CCMK0 = 0;    /* INTTP5CC0 interrupt enable */
    TP5CCIF1 = 0;    /* clear INTTP5CC1 interrupt flag */
    TP5CCMK1 = 0;    /* INTTP5CC1 interrupt enable */
    TP5OVIF = 0;    /* clear INTTP5OV interrupt flag */
    TP5OVMK = 0;    /* INTTP5OV interrupt enable */
    TP5CE = 1;    /* TMP5 operation enable */
}


void v850_tmp5_stop(void)
{
    TP5CE = 0;    /* TMP5 operation disable */
    TP5CCMK0 = 1;    /* INTTP5CC0 interrupt disable */
    TP5CCIF0 = 0;    /* clear INTTP5CC0 interrupt flag */
    TP5CCMK1 = 1;    /* INTTP5CC1 interrupt disable */
    TP5CCIF1 = 0;    /* clear INTTP5CC1 interrupt flag */
    TP5OVMK = 1;    /* INTTP5OV interrupt disable */
    TP5OVIF = 0;    /* clear INTTP5OV interrupt flag */
}

void v850_tmp5_set_ccr0(int16_t iTiming)
{
    uint16_t iTmp = TP5CNT;
    TP5CCIF0 = 0;
    TP5CCR0 = iTmp + iTiming;
}

/**********************************************************
 * @function    v850_tmp1 set fuction TOP11 will output pwm!
 * @brief       TMP1 set.it is used to ctrl tft_bklight chip
 * @param    none
 * @retval    none
 **********************************************************/
void v850_tmp1_init(void)
{
    TP1CE = 0;    /* TMP0 operation disable */
    TP1CCMK0 = 1;    /* INTTP1CC0 interrupt disable */
    TP1CCIF0 = 0;    /* clear INTTP1CC0 interrupt flag */
    TP1CCMK1 = 1;    /* INTTP1CC1 interrupt disable */
    TP1CCIF1 = 0;    /* clear INTTP1CC1 interrupt flag */
    TP1OVMK = 1;    /* INTTP1OV interrupt disable */
    TP1OVIF = 0;    /* clear INTTP1OV interrupt flag */
    /* Set INTTP1CC0 lowest priority */
    TP1CCIC0 |= 0x07;
    /* Set INTTP1CC1 lowest priority */
    TP1CCIC1 |= 0x07;
    /* Set INTTP5OV lowest priority */
    TP1OVIC |= 0x07;
    /* PWM mode setting */
    TP1CCR0 = 0x3f;
    TP1CCR1 = 0;
    TP1CTL0 = TMP_INTERNAL_CLOCK;
    TP1CTL1 = TMP_INTERNAL_CLOCK | TMP_MODE_PWM;
    TP1IOC0 = TMP_OUTPUT1_NORMAL | TMP_OUTPUT1_ENABLE | TMP_OUTPUT0_NORMAL | TMP_OUTPUT0_DISABLE;
}


void v850_tmp1_start(void)
{
    if(0 == TP1CE)
    {
        TP1CE = 1;    /* TMP1 operation enable */
        /* TOP11 pin set */
        PFC3L |= 0x20;
        PMC3L |= 0x20;
    }
}


void v850_tmp1_stop(void)
{
    TP1CE = 0;    /* TMP1 operation disable */
    /* TOP11 pin set */
    PFC3L &= 0xdf;
    PMC3L &= 0xdf;
}

void v850_tmp1_set_freq(uint32_t freq)
{
    uint32_t tmp3 = (uint16_t)(32000000/freq);
    uint32_t tmp0 = TP1CCR0;

    if(tmp0 != tmp3 - 1)
    {
        uint32_t tmp1 = TP1CCR1;
        TP1CCR0 = tmp3-1;
        TP1CCR1 = (tmp3*tmp1)/(tmp0);
    }
    
}


void v850_tmp1_set_duty(uint8_t duty)
{
    uint32_t cycle = TP1CCR0 + 1;
    uint32_t reg = 0;
    uint32_t tmp = TP1CCR1;
    
    reg = cycle * duty / 100;

    TP1CCR1 = (uint16_t)reg;
    

}


/**********************************************************
 * @function    v850_tmq0 function! TOQ01~TOQ03 will output pwm!
 * @brief        TMQ0 set.
 * @param    none
 * @retval    none
 **********************************************************/

void v850_tmq0_init(void)
{
    unsigned int    u16temp;
    unsigned long u32temp;
    u32temp = (1000)-1;
    u16temp = (unsigned int) u32temp;
    
    TQ0CE = 0;    /* TMQ0 operation disable */
    TQ0CCMK0 = 1;    /* INTTQ0CC0 interrupt disable */
    TQ0CCIF0 = 0;    /* clear INTTQ0CC0 interrupt flag */
    TQ0CCMK1 = 1;    /* INTTQ0CC1 interrupt disable */
    TQ0CCIF1 = 0;    /* clear INTTQ0CC1 interrupt flag */
    TQ0CCMK2 = 1;    /* INTTQ0CC2 interrupt disable */
    TQ0CCIF2 = 0;    /* clear INTTQ0CC2 interrupt flag */
    TQ0CCMK3 = 1;    /* INTTQ0CC3 interrupt disable */
    TQ0CCIF3 = 0;    /* clear INTTQ0CC3 interrupt flag */
    TQ0OVMK = 1;    /* INTTQ0OV interrupt disable */
    TQ0OVIF = 0;    /* clear INTTQ0OV interrupt flag */
    /* PWM mode setting */
    TQ0CTL0 = TMQ_INTERNAL_CLOCK5;
    TQ0CTL1 = TMQ_INTERNAL_CLOCK | TMQ_MODE_PWM;
    TQ0CCR0 = 0x3f;
    TQ0CCR1 = 0;
    TQ0CCR2 = 0;
    TQ0CCR3 = 0;
    TQ0IOC0 = TMQ_OUTPUT3_NORMAL | TMQ_OUTPUT3_ENABLE \
              | TMQ_OUTPUT2_NORMAL | TMQ_OUTPUT2_ENABLE \
              | TMQ_OUTPUT1_NORMAL | TMQ_OUTPUT1_ENABLE \
              | TMQ_OUTPUT0_NORMAL | TMQ_OUTPUT0_DISABLE;

    
    TQ0CCR0 = u16temp; // 1/freq = X* (1/32000)
}

void v850_tmq0_start(void)
{
     if(0 == TQ0CE)
     {
         TQ0CE = 1;    /* TMQ0 operation enable */
     }
}

void v850_tmq0_stop(void)
{
    TQ0CE = 0;    /* TMQ0 operation disable */
    /* TOQ01 pin set */
    PFC5 |= 0x07;
    PFCE5 &= 0xf8;
    PMC5 &= 0xf8;
    PM5 |= 0x07;
}


void v850_tmq0_set_freq(uint32_t freq)
{
    
    uint32_t tmp3 = (uint16_t)(1000000/freq);
    uint32_t tmp0 = TQ0CCR0;
    
    if(tmp0 != tmp3 - 1)
    {
        uint32_t tmp1_1 = TQ0CCR1;
        uint32_t tmp1_2 = TQ0CCR2;
        uint32_t tmp1_3 = TQ0CCR3;
        TQ0CCR0 = tmp3-1;
        TQ0CCR2 = (tmp3*tmp1_2)/(tmp0);
        TQ0CCR3 = (tmp3*tmp1_3)/(tmp0);
        TQ0CCR1 = (tmp3*tmp1_1)/(tmp0);
    }
}

void v850_tmq0_set_duty(uint8_t idx,uint8_t duty)
{
    uint32_t cycle = TQ0CCR0 + 1;
    uint32_t reg = 0;
    uint32_t tmp = TQ0CCR1;
    
    reg = cycle * duty / 100;
    switch(idx)
    {
        case 1:
            TQ0CCR1 = (uint16_t)reg;  
            /* TOQ01 pin set */
            PFC5 &= 0xfe;
            PFCE5 |= 0x01;
            PMC5 |= 0x01;
            
        break;
        case 2:
            TQ0CCR2 = (uint16_t)reg;
            TQ0CCR1 = tmp;
            /* TOQ02 pin set */
            PFC5 &= 0xfd;
            PFCE5 |= 0x02;
            PMC5 |= 0x02;
        break;
        case 3:
            TQ0CCR3 = (uint16_t)reg;
            TQ0CCR1 = tmp;
            /* TOQ03 pin set */
            PFC5 &= 0xfb;
            PFCE5 |= 0x04;
            PMC5 |= 0x04;
        break;
    }
}


/*
**-----------------------------------------------------------------------------
**
**    Abstract:
**        This function initializes the TMP2 module.
**
**    Parameters:
**        None
**
**    Returns:
**        None
**
**-----------------------------------------------------------------------------
*/
void TMP2_Init(void)
{
    TP2CE = 0;    /* TMP2 operation disable */
    TP2CCMK0 = 1;    /* INTTP2CC0 interrupt disable */
    TP2CCIF0 = 0;    /* clear INTTP2CC0 interrupt flag */
    TP2CCMK1 = 1;    /* INTTP2CC1 interrupt disable */
    TP2CCIF1 = 0;    /* clear INTTP2CC1 interrupt flag */
    TP2OVMK = 1;    /* INTTP2OV interrupt disable */
    TP2OVIF = 0;    /* clear INTTP2OV interrupt flag */
    /* Set INTTP2CC1 level 4 priority */
    TP2CCIC1 &= 0xF8;
    TP2CCIC1 |= 0x04;
    /* Set INTTP2OV level 5 priority */
    TP2OVIC &= 0xF8;
    TP2OVIC |= 0x05;
    /* Free-running mode setting */
    TP2CTL0 = TMP_INTERNAL_CLOCK5;
    TP2CTL1 = TMP_INTERNAL_CLOCK | TMP_MODE_FREERUNNING;
    TP2OPT0 = TMP_CCR1_CAPTURE ;
    TP2IOC1 = TMP_INPUT1_EDGE_BOTH | TMP_INPUT0_EDGE_NONE;
    TP2CCR0 = 0xc7f;

    TP2IOC0 = TMP_OUTPUT1_NORMAL | TMP_OUTPUT1_DISABLE | TMP_OUTPUT0_NORMAL | TMP_OUTPUT0_DISABLE;

    /* TIP21 pin set */
    PM9L   |= 0x40 ;  //   INPUT_MODE; //?¡ìo??¡ì?¡ì???¡§o?¡ìo?
    
    PFC9L  &= 0xBF;
    PFCE9L |= 0x40;  //PFCE96 = 1   PFC96 = 0   ????TIP21?¡ìo??¡ì?¡ì?
    PMC9L  |= 0x40;   //????¡ì??1|??¡ì1???¡ì???a
}

/*
**-----------------------------------------------------------------------------
**
**    Abstract:
**        This function starts TMP2 counter.
**
**    Parameters:
**        None
**
**    Returns:
**        None
**
**-----------------------------------------------------------------------------
*/
void TMP2_Start(void)
{
    TP2CCIF1 = 0;    /* clear INTTP2CC1 interrupt flag */
    TP2CCMK1 = 0;    /* INTTP2CC1 interrupt enable */
    TP2OVIF = 0;    /* clear INTTP2OV interrupt flag */
    TP2OVMK = 0;    /* INTTP2OV interrupt enable */
    TP2CE = 1;    /* TMP2 operation enable */
}

/*
**-----------------------------------------------------------------------------
**
**    Abstract:
**        This function stops TMP2 counter.
**
**    Parameters:
**        None
**
**    Returns:
**        None
**
**-----------------------------------------------------------------------------
*/
void TMP2_Stop(void)
{
    TP2CE = 0;    /* TMP2 operation disable */
    TP2CCMK1 = 1;    /* INTTP2CC1 interrupt disable */
    TP2CCIF1 = 0;    /* clear INTTP2CC1 interrupt flag */
    TP2OVMK = 1;    /* INTTP2OV interrupt disable */
    TP2OVIF = 0;    /* clear INTTP2OV interrupt flag */
}



