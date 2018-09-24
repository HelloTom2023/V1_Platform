void v850_spi1_init(void)
{
//spi通讯
    CB1PWR = 0;    /* CSIB1 disable */
    CB1TMK = 1;    /* INTCB1T disable */
    CB1TIF = 0;    /* INTCB1T IF clear */
    CB1RMK = 1;    /* INTCB1R disable */
    CB1RIF = 0;    /* INTCB1R IF clear */
    /* Set INTCB1T level 1 priority */
    CB1TIC &= 0xF8;
    CB1TIC |= 0x01;
    /* Set INTCB1R level 2 priority */
    CB1RIC &= 0xF8;
    CB1RIC |= 0x02;
    CB1CTL1 = CSIB_DATA_TIMING1 | CSIB_CLOCK_4;
    CB1CTL2 = CSIB_DATA_LENGTH_8;
    CB1CTL0 = CSIB_TRANSMIT_ENABLE | CSIB_RECEIVE_ENABLE | CSIB_DATA_MSB | CSIB_MODE_CONTINUOUS | CSIB_STARTTRG_VALID;
    /* SCKB1 pin set */
    PFC9H |= 0x02;
    PMC9H |= 0x02;
    /* SOB1 pin set */
    PFC9H |= 0x01;
    PMC9H |= 0x01;
    /* SIB1 pin set */
    PFC9L |= 0x80;
    PFCE9L &= 0x7F;
    PMC9L |= 0x80;

    /*SPI_CPU_IRQ = INTP6 Setting */
    PMK6 = 1;    /* INTP6 disable */
    PIF6 = 0;    /* INTP6 IF clear */
    /* Set INTP6 level 1 priority */
    PIC6 &= 0xF8;
    PIC6 |= 0x01;
    INTR9H |= 0x80;   //上升沿中断
    INTF9H |= 0x80;   //下降沿中断
    /* INTP6 pin set */
    PFC9H |= 0x80;
    PFCE9H &= 0x7F;
    PMC9H |= 0x80;

    //pin dir set
    PM9H |= 0x80; //PM9H.7 = 1;irq
    PM9H &= 0xfc; //PM9H.0 = 0;PM9H.1 = 0;
    PM9L |= 0x80; //PM9L.7 =1;
    PMCM &= 0xdf; //PCM.5 = 0;
}


void v850_spi1_enable(void)
{
    CB1RIF = 0;    /* INTCB1R IF clear */
    CB1RMK = 0;    /* INTCB1R enable */
    CB1TIF = 0;    /* INTCB1T IF clear */
    CB1TMK = 0;    /* INTCB1T enable */
    CB1PWR = 1;    /* CSIB1 enable */
}

void v850_spi1_disable(void)
{
    CB1PWR = 0;    /* CSIB1 disable */
    CB1RMK = 1;    /* INTCB1R disable */
    CB1RIF = 0;    /* INTCB1R IF clear */
    CB1TMK = 1;    /* INTCB1T disable */
    CB1TIF = 0;    /* INTCB1T IF clear */
    /* SCKB1 pin set */
    PFC9H &= 0xfd;
    PMC9H &= 0xfd;
    PM9H |= 0x02;
    /* SOB1 pin set */
    PFC9H &= 0xfe;
    PMC9H &= 0xfe;
    PM9H |= 0x01;
    /* SIB1 pin set */
    PFC9L &= 0x7f;
    PFCE9L &= 0x7F;
    PMC9L &= 0x7f;
    PM9L |= 0x80;
}

void v850_spi1_tx_start(uint8_t data)
{
    CB1TX = data;
}

void v850_spi1_irq_enable(void)
{
    PIF6 = 0;        /* INTP6 IF clear */
    PMK6 = 0;        /* INTP6 enable */
}

void v850_spi1_irq_disable(void)
{
    PMK6 = 1;        /* INTP6 disable */
    PIF6 = 0;        /* INTP6 IF clear */
}
