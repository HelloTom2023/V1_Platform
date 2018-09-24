/*
    DMA Source Address Register n (DSAnH)
*/
/* Setting area of DMA transfer source address (IRn) */
#define DMA_SRC_AREA_EXMEMORIO            0x0000    /* DMA transfer source is external memory or on-chip peripheral I/O */
#define DMA_SRC_AREA_INRAM                0x8000    /* DMA transfer source is internal RAM */

/*    
    DMA Destination Address Register n (DDAnH)
*/
/* Setting area of DMA destination address (IRn) */
#define DMA_DST_AREA_EXMEMORIO            0x0000    /* DMA destination is external memory or on-chip peripheral I/O */
#define DMA_DST_AREA_INRAM                0x8000    /* DMA destination is internal RAM */

/*
    DMA Addressing Control Register n (DADCn)
*/
/* Setting of transfer data size (DSn0) */
#define DMA_DATA_SIZE_8                    0x0000    /* 8 bits */
#define    DMA_DATA_SIZE_16                0x4000    /* 16 bits */
/* Setting of count direction of the transfer source address (SADn0, SADn1) */
#define DMA_SRC_DIR_INC                    0x0000    /* count direction of transfer source address is increased */
#define DMA_SRC_DIR_DEC                    0x0040    /* count direction of transfer source address is decreased */
#define DMA_SRC_DIR_FIX                    0x0080    /* count direction of transfer source address is fixed */
/* Setting of count direction of the destination address (DADn0, DADn1) */
#define DMA_DST_DIR_INC                    0x0000    /* count direction of destination address is increased */
#define DMA_DST_DIR_DEC                    0x0010    /* count direction of destination address is decreased */
#define DMA_DST_DIR_FIX                    0x0020    /* count direction of destination address is fixed */

/*
    DMA Channel Control Register (DCHCn) 
*/
/* DMA transfer status */
#define DMA_TRANSFER_UNDEREXEC            0x00    /* DMA transfer have not completed */
#define DMA_TRANSFER_COMPLETED            0x80    /* DMA transfer have completed */
/* Setting of DMA initialization (INITn) */
#define DMA_INIT_DISABLE                0x00    /* disable DMA initialization */
#define DMA_INIT_ENABLE                    0x04    /* enable DMA initialization (Enn = 0)*/
/* Setting of DMA software startup trigger(STGn) */
#define DMA_SOFTWARE_TRIGGER_DISABLE    0x00    /* can't be triggerred by software */
#define DMA_SOFTWARE_TRIGGER_ENABLE        0x02    /* can be triggerred by software (TCn =0, Enn = 0) */
/* DMA operation enable flag */
#define DMA_OPERATION_DISABLE            0x00    /* DMA transfer disabled */
#define DMA_OPERATION_ENABLE            0x01    /* DMA transfer enabled */ 

/*
    DMA Trigger Factor Register n (DTFRn)
*/
/* Selection of DMA stat source(IFCn0~5) */
#define DMA_TRIGGER_INTDISABLE            0x00    /* disables DMA transfer by interrupt */
#define DMA_TRIGGER_INTP0                0x01    /* external interrupt 0 */
#define DMA_TRIGGER_INTP1                0x02    /* external interrupt 1 */
#define DMA_TRIGGER_INTP2                0x03    /* external interrupt 2 */
#define DMA_TRIGGER_INTP3                0x04    /* external interrupt 3 */
#define DMA_TRIGGER_INTP4                0x05    /* external interrupt 4 */
#define DMA_TRIGGER_INTP5                0x06    /* external interrupt 5 */
#define DMA_TRIGGER_INTP6                0x07    /* external interrupt 6 */
#define DMA_TRIGGER_INTP7                0x08    /* external interrupt 7 */
#define DMA_TRIGGER_INTTQ0OV            0x09    /* TMQ0 overflow */
#define DMA_TRIGGER_INTTQ0CC0            0x0A    /* TMQ0 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTQ0CC1            0x0B    /* TMQ0 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTQ0CC2            0x0C    /* TMQ0 capture 2 / compare 2 match */
#define DMA_TRIGGER_INTTQ0CC3            0x0D    /* TMQ0 capture 3 / compare 3 match */
#define DMA_TRIGGER_INTTP0OV            0x0E    /* TMP0 overflow */
#define DMA_TRIGGER_INTTP0CC0            0x0F    /* TMP0 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP0CC1            0x10    /* TMP0 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTP1OV            0x11    /* TMP1 overflow */
#define DMA_TRIGGER_INTTP1CC0            0x12    /* TMP1 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP1CC1            0x13    /* TMP1 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTP2OV            0x14    /* TMP2 overflow */
#define DMA_TRIGGER_INTTP2CC0            0x15    /* TMP2 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP2CC1            0x16    /* TMP2 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTP3CC0            0x17    /* TMP3 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP3CC1            0x18    /* TMP3 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTP4CC0            0x19    /* TMP4 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP4CC1            0x1A    /* TMP4 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTP5CC0            0x1B    /* TMP5 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP5CC1            0x1C    /* TMP5 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTM0EQ0            0x1D    /* TMM0 compare match */
#define DMA_TRIGGER_INTCB0R_INTIIC1        0x1E    /* CSIB0 reception completion / CSIB0 reception error / IIC1 transfer completion */
#define DMA_TRIGGER_INTCB0T                0x1F    /* CSIB0 consecutive transmission write enable */
#define DMA_TRIGGER_INTCB1R                0x20    /* CSIB1 reception completion / CSIB1 reception error */
#define DMA_TRIGGER_INTCB1T                0x21    /* CSIB1 consecutive transmission write enable */
#define DMA_TRIGGER_INTCB2R                0x22    /* CSIB2 reception completion / CSIB2 reception error */
#define DMA_TRIGGER_INTCB2T                0x23    /* CSIB2 consecutive transmission write enable */
#define DMA_TRIGGER_INTCB3R                0x24    /* CSIB3 reception completion / CSIB3 reception error */
#define DMA_TRIGGER_INTCB3T                0x25    /* CSIB3 consecutive transmission write enable */
#define DMA_TRIGGER_INTUA0R_INTCB4R        0x26    /* UARTA0 reception completion / CSIB4 reception completion / CSIB4 reception error */
#define DMA_TRIGGER_INTUA0T_INTCB4T        0x27    /* UARTA0 consecutive transmission enable / CSIB4 consecutive transmission write enable */
#define DMA_TRIGGER_INTUA1R_INTIIC2        0x28    /* UARTA1 reception completion / IIC2 transfer completion */
#define DMA_TRIGGER_INTUA1T                0x29    /* UARTA1 consecutive transmission enable */
#define DMA_TRIGGER_INTUA2R_INTIIC0        0x2A    /* UARTA2 reception completion / IIC0 transfer completion */
#define DMA_TRIGGER_INTUA2T                0x2B    /* UARTA2 consecutive transmission enable */
#define DMA_TRIGGER_INTAD                0x2C    /* A/D conversion completion */
#define DMA_TRIGGER_INTKR                0x2D    /* key return interrupt */
#define DMA_TRIGGER_INTERR                0x2E    /* IEBus error */
#define DMA_TRIGGER_INTSTA                0x2F    /* IEBus status */
#define DMA_TRIGGER_INTIE1                0x30    /* IEBus data interrupt */
#define DMA_TRIGGER_INTP8                0x31    /* external interrupt 8 */
#define DMA_TRIGGER_INTTP6CC0            0x32    /* TMP6 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP6CC1            0x33    /* TMP6 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTP7CC0            0x34    /* TMP7 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP7CC1            0x35    /* TMP7 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTTP8CC0            0x36    /* TMP8 capture 0 / compare 0 match */
#define DMA_TRIGGER_INTTP8CC1            0x37    /* TMP8 capture 1 / compare 1 match */
#define DMA_TRIGGER_INTCB5R                0x38    /* CSIB5 reception completion / CSIB5 reception error */
#define DMA_TRIGGER_INTCB5T                0x39    /* CSIB5 consecutive transmission write enable */
#define DMA_TRIGGER_INTUA3R                0x3A    /* UARTA3 consecutive reception completion */
#define DMA_TRIGGER_INTUA3T                0x3B    /* UARTA3 consecutive transmission enable */

/*
     Usable address area range 
*/
/* Fixed peripheral I/O area */
#define DMA_FIXIO_STARTADDR                0x3FFF000
#define DMA_FIXIO_ENDADDR                0x3FFFFFF
/* Programmable peripheral I/O area */
#define DMA_PROIO_STARTADDR                0x3FEC000
#define DMA_PROIO_ENDADDR                0x3FEEFFF
/* External memory area */
#define DMA_EXMEM0_STARTADDR            0x100000
#define DMA_EXMEM0_ENDADDR                0x1FFFFF
#define DMA_EXMEM1_STARTADDR            0x200000
#define DMA_EXMEM1_ENDADDR                0x3FFFFF
#define DMA_EXMEM2_STARTADDR            0x400000
#define DMA_EXMEM2_ENDADDR                0x7FFFFF
#define DMA_EXMEM3_STARTADDR            0x800000
#define DMA_EXMEM3_ENDADDR                0xFFFFFF
/* Internal RAM area */
#define    DMA_RAM_STARTADDR                0x3FF5000
#define DMA_RAM_ENDADDR                    0x3FFEFFF

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define    DMA0_SRC_ADDRESS_HIGH            0x3ff
#define    DMA0_SRC_ADDRESS_LOW            0x5000
#define    DMA0_DST_ADDRESS_HIGH            0x3ff
#define    DMA0_DST_ADDRESS_LOW            0xfd16
#define    DMA0_NUM_COUNT                    0x7f
#define    DMA1_SRC_ADDRESS_HIGH            0x3ff
#define    DMA1_SRC_ADDRESS_LOW            0xfd14
#define    DMA1_DST_ADDRESS_HIGH            0x3ff
#define    DMA1_DST_ADDRESS_LOW            0x6000
#define    DMA1_NUM_COUNT                    0x0
#define    DMA2_SRC_ADDRESS_HIGH            0x3ff
#define    DMA2_SRC_ADDRESS_LOW            0x5000
#define    DMA2_DST_ADDRESS_HIGH            0x3ff
#define    DMA2_DST_ADDRESS_LOW            0xfd36
#define    DMA2_NUM_COUNT                    0x7f
#define    DMA3_SRC_ADDRESS_HIGH            0x3ff
#define    DMA3_SRC_ADDRESS_LOW            0xfd34
#define    DMA3_DST_ADDRESS_HIGH            0x3ff
#define    DMA3_DST_ADDRESS_LOW            0x5000
#define    DMA3_NUM_COUNT                    0x7f


void v850_dma0_for_spi_tx(uint8_t* pbuf, uint16_t cLen, bool dummy)
{
    uint32_t temp;
    uint16_t add_h,add_l;
    E00 = 0;    /* DMA0 transfer disable */
    DMAMK0 = 1;    /* INTDMA0 disable */
    DMAIF0 = 0;    /* INTDMA0 IF clear */
    /* Set INTDMA level 1 priority */
    DMAIC0 &= 0xF8;
    DMAIC0 |= 0x01;
    INIT0 = 1;    /* enable DMA0 initialization */
    // set source address 
    temp = (uint32_t)pbuf;
    add_l = (uint16_t)temp;
    add_h = (uint16_t)(temp >> 16);
    add_h |= DMA_SRC_AREA_INRAM;
    DSA0H = add_h;
    DSA0L = add_l;
    // set  destination address
    DDA0H = DMA_DST_AREA_EXMEMORIO | DMA0_DST_ADDRESS_HIGH;
    DDA0L = DMA0_DST_ADDRESS_LOW;   //spi tx register
    DBC0  = cLen - 1;  //this is the DMA seting,'0' means trans 1 byte
    DADC0 = DMA_DATA_SIZE_8 |(dummy<<7)| DMA_DST_DIR_FIX;
    DTFR0 = DMA_TRIGGER_INTCB1T;

    DMAIF0 = 0;    /* INTDMA0 IF clear */
    DMAMK0 = 1;    /* INTDMA0 enable */    
    E00 = 1;    /* DMA0 transfer enable */
}



void v850_dma0_enable(void)
{
    DMAIF0 = 0;    /* INTDMA0 IF clear */
    DMAMK0 = 0;    /* INTDMA0 enable */    
    E00 = 1;    /* DMA0 transfer enable */
}


void v850_dma0_disable(void)
{
    E00 = 0;    /* DMA0 transfer disable */
    DMAMK0 = 1;    /* INTDMA0 disable */
    DMAIF0 = 0;    /* INTDMA0 IF clear */    
}
 

void v850_dma1_for_spi_rx(uint8_t* pbuf, uint16_t cLen)
{
    uint32_t temp;
    uint16_t add_h,add_l;
    E11 = 0;    /* DMA1 transfer disable */
    DMAMK1 = 1;    /* INTDMA1 disable */
    DMAIF1 = 0;    /* INTDMA1 IF clear */
    /* Set INTDMA level 2 priority */
    DMAIC1 &= 0xF8;
    DMAIC1 |= 0x02;
    INIT1 = 1;    /* enable DMA1 initialization */
    // set source address
    DSA1H = DMA_SRC_AREA_EXMEMORIO | DMA1_SRC_ADDRESS_HIGH;
    DSA1L = DMA1_SRC_ADDRESS_LOW;    //spi rx register

    //set destination address
    temp = (uint32_t)pbuf;
    add_l = (uint16_t)temp;
    add_h = (uint16_t)(temp >> 16);
    add_h |= DMA_SRC_AREA_INRAM;
    
    DDA1H = add_h;
    DDA1L = add_l;
    DBC1  = cLen - 1;
    DADC1 = DMA_DATA_SIZE_8 | DMA_SRC_DIR_FIX | DMA_DST_DIR_INC;
    DTFR1 = DMA_TRIGGER_INTCB1R;
    
    DMAIF1 = 0;    /* INTDMA1 IF clear */
    DMAMK1 = 0;    /* INTDMA1 enable */    
    E11 = 1;    /* DMA1 transfer enable */
    
}

void v850_dma1_enable(void)
{
    DMAIF1 = 0;    /* INTDMA1 IF clear */
    DMAMK1 = 0;    /* INTDMA1 enable */    
    E11 = 1;    /* DMA1 transfer enable */
}

void v850_dma1_disable(void)
{
    E11 = 0;    /* DMA1 transfer disable */
    DMAMK1 = 1;    /* INTDMA1 disable */
    DMAIF1 = 0;    /* INTDMA1 IF clear */    
}



