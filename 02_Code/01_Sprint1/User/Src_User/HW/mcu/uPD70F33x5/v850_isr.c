/***********************************************
*
* These code placed in the user section
* It's only a vertor service funtion entry to cheat the compiler,
* so close the mini_code option.
* If it is used by app, please fill it!
* 
************************************************/

//void irq_NMI(void){}               //(0x0010)
#define irq_NMI() isrPM_LviOccur()

void irq_INTWDT2(void){}           //(0x0020)
void irq_DBG0(void){}              //(0x0060)
void irq_ILGOP(void){}             //(0x0060)
void irq_INTLVI(void){}            //(0x0080)
//void irq_INTP0(void){}             //(0x0090)
#define irq_INTP0()		INTP0_isr()//(0x0090)
void irq_INTP1(void){}             //(0x00A0)
void irq_INTP2(void){}             //(0x00B0)
//void irq_INTP3(void){}             //(0x00C0)
#define irq_INTP3()		INTP3_isr()

void irq_INTP4(void)               //(0x00D0)
{
#if D_ENCODE_SCAN_IN_INT
    uint8_t cValue = (IO_GET_ENCODE_A)|(IO_GET_ENCODE_B<<2);
    isrHMI_ScanEncode(0, cValue);
#endif
}
void irq_INTP5(void)               //(0x00E0)
{
#if D_ENCODE_SCAN_IN_INT
    uint8_t cValue = (IO_GET_ENCODE_C>>1)|(IO_GET_ENCODE_D<<1);
    isrHMI_ScanEncode(1, cValue);
#endif
}
#ifdef  MDI_COMM_TYPE_UART
void irq_INTP6(void){}             //(0x00F0)
#else
#define irq_INTP6() isrMDI_LinkerSlaveIrq()
#endif

void irq_INTP7(void){}             //(0x0100)
void irq_INTTQ0OV(void){}          //(0x0110)
void irq_INTTQ0CC0(void){}         //(0x0120)
void irq_INTTQ0CC1(void){}         //(0x0130)
void irq_INTTQ0CC2(void){}         //(0x0140)
void irq_INTTQ0CC3(void){}         //(0x0150)
void irq_INTTP0OV(void){}          //(0x0160)
void irq_INTTP0CC0(void){}         //(0x0170)
void irq_INTTP0CC1(void){}         //(0x0180)
void irq_INTTP1OV(void){}          //(0x0190)
void irq_INTTP1CC0(void){}         //(0x01A0)
void irq_INTTP1CC1(void){}         //(0x01B0)

void irq_INTTP2OV(void){}          //(0x01C0)
void irq_INTTP2CC0(void){}         //(0x01D0)
void irq_INTTP2CC1(void){}         //(0x01E0)

void irq_INTTP3OV(void){}          //(0x01F0)
void irq_INTTP3CC0(void){}         //(0x0200)
void irq_INTTP3CC1(void){}         //(0x0210)
void irq_INTTP4OV(void){}          //(0x0220)
void irq_INTTP4CC0(void){}         //(0x0230)
void irq_INTTP4CC1(void){}         //(0x0240)
void irq_INTTP5OV(void){}          //(0x0250)

void irq_INTTP5CC0(void){}         //(0x0260)
//#define irq_INTTP5CC0()            isrDISC_Tx()

void irq_INTTP5CC1(void){}         //(0x0270)

//void irq_INTTM0EQ0(void){}         //(0x0280)
#define irq_INTTM0EQ0() isrOS_Tick()

//void irq_INTCB0R(void){}           //(0x0290)
//void irq_INTIIC1(void){}           //(0x0290)
#define irq_INTIIC1() isrI2C1_Comm()

void irq_INTCB0T(void){}           //(0x02A0)
void irq_INTCB1R(void){}           //(0x02B0)
void irq_INTCB1T(void){}           //(0x02C0)
void irq_INTCB2R(void){}           //(0x02D0)
void irq_INTCB2T(void){}           //(0x02E0)
void irq_INTCB3R(void){}           //(0x02F0)
void irq_INTCB3T(void){}           //(0x0300)
void irq_INTCB4R(void){}           //(0x0310)
//void irq_INTUA0R(void){}           //(0x0310)

void irq_INTCB4T(void){}           //(0x0320)
//void irq_INTUA0T(void){}           //(0x0320)

//void irq_INTIIC2(void){}           //(0x0330)
#define irq_INTIIC2() isrI2C2_Comm()
//void irq_INTUA1R(void){}           //(0x0330)

void irq_INTUA1T(void){}           //(0x0340)

#ifdef D_TW8836_I2C0_EN
#define irq_INTIIC0()	isrI2C0_Comm()
#else
void irq_INTIIC0(void){}           //(0x0350)
#endif

//void irq_INTUA2R(void){}           //(0x0350)
void irq_INTUA2T(void){}           //(0x0360)


void irq_INTAD(void){}             //(0x0370)
void irq_INTDMA0(void){}           //(0x0380)

#ifdef MDI_COMM_TYPE_UART
void irq_INTDMA1(void){}           //(0x0390)
#else
#define irq_INTDMA1() isrMDI_LinkerRxEnd()
#endif

void irq_INTDMA2(void){}           	//(0x03A0)
void irq_INTDMA3(void){}           	//(0x03B0)
void irq_INTKR(void){}             	//(0x03C0)
void irq_INTWTI(void){}            	//(0x03D0)

//void irq_INTWT(void){}             //(0x03E0)
#define irq_INTWT() 			isrOS_RTC()
//void irq_INTC0ERR(void){}          //(0x03F0)
#define irq_INTC0ERR()		CAN0_INTERR()
//void irq_INTC0WUP(void){}          //(0x0400)
#define irq_INTC0WUP()		CAN0_INTWUP()
//void irq_INTC0REC(void){}          //(0x0410)
#define irq_INTC0REC()		CAN0_INTREC()
//void irq_INTC0TRX(void){}          //(0x0420)
#define irq_INTC0TRX()		CAN0_INTTRX()
//void irq_INTC1ERR(void){}          //(0x0430)
#define irq_INTC1ERR()		CAN1_INTERR()
//void irq_INTC1WUP(void){}          //(0x0440)
#define irq_INTC1WUP()		CAN1_INTWUP()
//void irq_INTC1REC(void){}          //(0x0450)
#define irq_INTC1REC()		CAN1_INTREC()
//void irq_INTC1TRX(void){}          //(0x0460)
#define irq_INTC1TRX()		CAN1_INTTRX()
void irq_INTP8(void){}             //(0x0470)
void irq_INTTP6OV(void){}          //(0x0480)
void irq_INTTP6CC0(void){}         //(0x0490)
void irq_INTTP6CC1(void){}         //(0x04A0)
void irq_INTTP7OV(void){}          //(0x04B0)
void irq_INTTP7CC0(void){}         //(0x04C0)
void irq_INTTP7CC1(void){}         //(0x04D0)
void irq_INTTP8OV(void){}          //(0x04E0)

#if 0
void irq_INTTP8CC0(void)           //(0x04F0)
{
     
     /*isrDISC_Rx(TP8CCR0);*/
     uint16_t iTiming = TP8CCR0;    /* get current capture value */
     TP8CCIF0 = 0;
     isrDISC_Rx(iTiming); 
} 
#else
void irq_INTTP8CC0(void){}           //(0x04F0)
#endif

void irq_INTTP8CC1(void){}         //(0x0500)
void irq_INTCB5R(void){}           //(0x0510)
void irq_INTCB5T(void){}           //(0x0520)


#ifdef MDI_COMM_TYPE_UART
#define  irq_INTUA3R()   isrMDI_LinkerRX()   //(0x0530)
#else
void irq_INTUA3R(void){}           //(0x0530)
#endif


#ifdef MDI_COMM_TYPE_UART
#define irq_INTUA3T() isrMDI_LinkerTX()
#else
void irq_INTUA3T(void) {}		//(0x540)
#endif
/*******************************************************************************
*
* It's the function address in the vector_tab.
* It's address must be placed in isr section and must be hold 
*
*******************************************************************************/
#if _COMPILER_ == _IAR_EWV850_
/*IAR 会自动将中断服务程序放入ICODE区域*/
#else
#pragma text "isr_text"
#endif


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  NMI_vector               ////(0x0010)
#else
#pragma interrupt NMI isr_NMI
#endif
__interrupt void isr_NMI(void)
{
    irq_NMI();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTWDT2_vector           ////(0x0020)
#else
#pragma interrupt INTWDT2 isr_INTWDT2
#endif
__interrupt void isr_INTWDT2(void)
{
    irq_INTWDT2();
}

#if 0
#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  DBG0_vector              ////(0x0060)
//#pragma vector =  ILGOP_vector             ////(0x0060)
#else
#pragma interrupt DBG0 isr_DBG0
//#pragma interrupt ILGOP isr_ILGOP
#endif
__interrupt void isr_DBG0(void)
{
    irq_DBG0();
}
#endif


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTLVI_vector            ////(0x0080)
#else
#pragma interrupt INTLVI isr_INTLVI
#endif
__interrupt void isr_INTLVI(void)
{
    irq_INTLVI();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP0_vector             ////(0x0090)
#else
#pragma interrupt INTP0 isr_INTP0
#endif
__interrupt void isr_INTP0(void)
{
    irq_INTP0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP1_vector             ////(0x00A0)
#else
#pragma interrupt INTP1 isr_INTP1
#endif
__interrupt void isr_INTP1(void)
{
    irq_INTP1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP2_vector             ////(0x00B0)
#else
#pragma interrupt INTP2 isr_INTP2
#endif
__interrupt void isr_INTP2(void)
{
    irq_INTP2();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP3_vector             ////(0x00C0)
#else
#pragma interrupt INTP3 isr_INTP3
#endif
__interrupt void isr_INTP3(void)
{
    irq_INTP3();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP4_vector             ////(0x00D0)
#else
#pragma interrupt INTP4 isr_INTP4
#endif
__interrupt void isr_INTP4(void)
{
    irq_INTP4();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP5_vector             ////(0x00E0)
#else
#pragma interrupt INTP5 isr_INTP5
#endif
__interrupt void isr_INTP5(void)
{
    irq_INTP5();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP6_vector             ////(0x00F0)
#else
#pragma interrupt INTP6 isr_INTP6
#endif
__interrupt void isr_INTP6(void)
{
    irq_INTP6();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP7_vector             ////(0x0100)
#else
#pragma interrupt INTP7 isr_INTP7
#endif
__interrupt void isr_INTP7(void)
{
    irq_INTP7();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTQ0OV_vector          ////(0x0110)
#else
#pragma interrupt INTTQ0OV isr_INTTQ0OV
#endif
__interrupt void isr_INTTQ0OV(void)
{
    irq_INTTQ0OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTQ0CC0_vector         ////(0x0120)
#else
#pragma interrupt INTTQ0CC0 isr_INTTQ0CC0
#endif
__interrupt void isr_INTTQ0CC0(void)
{
    irq_INTTQ0CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTQ0CC1_vector         ////(0x0130)
#else
#pragma interrupt INTTQ0CC1 isr_INTTQ0CC1
#endif
__interrupt void isr_INTTQ0CC1(void)
{
    irq_INTTQ0CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTQ0CC2_vector         ////(0x0140)
#else
#pragma interrupt INTTQ0CC2 isr_INTTQ0CC2
#endif
__interrupt void isr_INTTQ0CC2(void)
{
    irq_INTTQ0CC2();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTQ0CC3_vector         ////(0x0150)
#else
#pragma interrupt INTTQ0CC3 isr_INTTQ0CC3
#endif
__interrupt void isr_INTTQ0CC3(void)
{
    irq_INTTQ0CC3();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP0OV_vector          ////(0x0160)
#else
#pragma interrupt INTTP0OV isr_INTTP0OV
#endif
__interrupt void isr_INTTP0OV(void)
{
    irq_INTTP0OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP0CC0_vector         ////(0x0170)
#else
#pragma interrupt INTTP0CC0 isr_INTTP0CC0
#endif
__interrupt void isr_INTTP0CC0(void)
{
    irq_INTTP0CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP0CC1_vector         ////(0x0180)
#else
#pragma interrupt INTTP0CC1 isr_INTTP0CC1
#endif
__interrupt void isr_INTTP0CC1(void)
{
    irq_INTTP0CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP1OV_vector          ////(0x0190)
#else
#pragma interrupt INTTP1OV isr_INTTP1OV
#endif
__interrupt void isr_INTTP1OV(void)
{
    irq_INTTP1OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP1CC0_vector         ////(0x01A0)
#else
#pragma interrupt INTTP1CC0 isr_INTTP1CC0
#endif
__interrupt void isr_INTTP1CC0(void)
{
    irq_INTTP1CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP1CC1_vector         ////(0x01B0)
#else
#pragma interrupt INTTP1CC1 isr_INTTP1CC1
#endif
__interrupt void isr_INTTP1CC1(void)
{
    irq_INTTP1CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP2OV_vector          ////(0x01C0)
#else
#pragma interrupt INTTP2OV isr_INTTP2OV
#endif
__interrupt void isr_INTTP2OV(void)
{
    irq_INTTP2OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP2CC0_vector         ////(0x01D0)
#else
#pragma interrupt INTTP2CC0 isr_INTTP2CC0
#endif
__interrupt void isr_INTTP2CC0(void)
{
    irq_INTTP2CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP2CC1_vector         ////(0x01E0)
#else
#pragma interrupt INTTP2CC1 isr_INTTP2CC1
#endif
__interrupt void isr_INTTP2CC1(void)
{
    irq_INTTP2CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP3OV_vector          ////(0x01F0)
#else
#pragma interrupt INTTP3OV isr_INTTP3OV
#endif
__interrupt void isr_INTTP3OV(void)
{
    irq_INTTP3OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP3CC0_vector         ////(0x0200)
#else
#pragma interrupt INTTP3CC0 isr_INTTP3CC0
#endif
__interrupt void isr_INTTP3CC0(void)
{
    irq_INTTP3CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP3CC1_vector         ////(0x0210)
#else
#pragma interrupt INTTP3CC1 isr_INTTP3CC1
#endif
__interrupt void isr_INTTP3CC1(void)
{
    irq_INTTP3CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP4OV_vector          ////(0x0220)
#else
#pragma interrupt INTTP4OV isr_INTTP4OV
#endif
__interrupt void isr_INTTP4OV(void)
{
    irq_INTTP4OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP4CC0_vector         ////(0x0230)
#else
#pragma interrupt INTTP4CC0 isr_INTTP4CC0
#endif
__interrupt void isr_INTTP4CC0(void)
{
    irq_INTTP4CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP4CC1_vector         ////(0x0240)
#else
#pragma interrupt INTTP4CC1 isr_INTTP4CC1
#endif
__interrupt void isr_INTTP4CC1(void)
{
    irq_INTTP4CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP5OV_vector          ////(0x0250)
#else
#pragma interrupt INTTP5OV isr_INTTP5OV
#endif
__interrupt void isr_INTTP5OV(void)
{
    irq_INTTP5OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP5CC0_vector         ////(0x0260)
#else
#pragma interrupt INTTP5CC0 isr_INTTP5CC0
#endif
__interrupt void isr_INTTP5CC0(void)
{
    irq_INTTP5CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP5CC1_vector         ////(0x0270)
#else
#pragma interrupt INTTP5CC1 isr_INTTP5CC1
#endif
__interrupt void isr_INTTP5CC1(void)
{
    irq_INTTP5CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTM0EQ0_vector         ////(0x0280)
#else
#pragma interrupt INTTM0EQ0 isr_INTTM0EQ0
#endif
__interrupt void isr_INTTM0EQ0(void)
{
    irq_INTTM0EQ0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB0R_vector           ////(0x0290)
//#pragma vector =  INTIIC1_vector           ////(0x0290)
#else
#pragma interrupt INTCB0R isr_INTCB0R_IIC1
//#pragma interrupt INTIIC1 isr_INTIIC1
#endif
__interrupt void isr_INTCB0R_IIC1(void)
{
    irq_INTIIC1();
}




#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB0T_vector           ////(0x02A0)
#else
#pragma interrupt INTCB0T isr_INTCB0T
#endif
__interrupt void isr_INTCB0T(void)
{
    irq_INTCB0T();
}

#if 0
#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB1R_vector           ////(0x02B0)
#else
#pragma interrupt INTCB1R isr_INTCB1R
#endif
__interrupt void isr_INTCB1R(void)
{
    irq_INTCB1R();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB1T_vector           ////(0x02C0)
#else
#pragma interrupt INTCB1T isr_INTCB1T
#endif
__interrupt void isr_INTCB1T(void)
{
    irq_INTCB1T();
}
#endif

#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB2R_vector           ////(0x02D0)
#else
#pragma interrupt INTCB2R isr_INTCB2R
#endif
__interrupt void isr_INTCB2R(void)
{
    irq_INTCB2R();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB2T_vector           ////(0x02E0)
#else
#pragma interrupt INTCB2T isr_INTCB2T
#endif
__interrupt void isr_INTCB2T(void)
{
    irq_INTCB2T();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB3R_vector           ////(0x02F0)
#else
#pragma interrupt INTCB3R isr_INTCB3R
#endif
__interrupt void isr_INTCB3R(void)
{
    irq_INTCB3R();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB3T_vector           ////(0x0300)
#else
#pragma interrupt INTCB3T isr_INTCB3T
#endif
__interrupt void isr_INTCB3T(void)
{
    irq_INTCB3T();
}

/*USE MINICUBE2 , must close it.*/

#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB4R_vector           ////(0x0310)
//#pragma vector =  INTUA0R_vector           ////(0x0310)
#else
#pragma interrupt INTCB4R isr_INTCB4R_UA0R
//#pragma interrupt INTUA0R isr_INTUA0R
#endif
__interrupt void isr_INTCB4R_UA0R(void)
{
    irq_INTCB4R();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB4T_vector           ////(0x0320)
//#pragma vector =  INTUA0T_vector           ////(0x0320)
#else
#pragma interrupt INTCB4T isr_INTCB4T_UA0T
//#pragma interrupt INTUA0T isr_INTUA0T
#endif
__interrupt void isr_INTCB4T_UA0T(void)
{
    irq_INTCB4T();
}



#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTIIC2_vector           ////(0x0330)
//#pragma vector =  INTUA1R_vector           ////(0x0330)
#else
#pragma interrupt INTIIC2 isr_INTIIC2_UA1R
//#pragma interrupt INTUA1R isr_INTUA1R
#endif
__interrupt void isr_INTIIC2_UA1R(void)
{
    irq_INTIIC2();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTUA1T_vector           ////(0x0340)
#else
#pragma interrupt INTUA1T isr_INTUA1T
#endif
__interrupt void isr_INTUA1T(void)
{
    irq_INTUA1T();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTIIC0_vector           ////(0x0350)
//#pragma vector =  INTUA2R_vector           ////(0x0350)
#else
#pragma interrupt INTIIC0 isr_INTIIC0_UA2R
//#pragma interrupt INTUA2R isr_INTUA2R
#endif
__interrupt void isr_INTIIC0_UA2R(void)
{
    irq_INTIIC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTUA2T_vector           ////(0x0360)
#else
#pragma interrupt INTUA2T isr_INTUA2T
#endif
__interrupt void isr_INTUA2T(void)
{
    irq_INTUA2T();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTAD_vector             ////(0x0370)
#else
#pragma interrupt INTAD isr_INTAD
#endif
__interrupt void isr_INTAD(void)
{
    irq_INTAD();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTDMA0_vector           ////(0x0380)
#else
#pragma interrupt INTDMA0 isr_INTDMA0
#endif
__interrupt void isr_INTDMA0(void)
{
    irq_INTDMA0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTDMA1_vector           ////(0x0390)
#else
#pragma interrupt INTDMA1 isr_INTDMA1
#endif
__interrupt void isr_INTDMA1(void)
{
    irq_INTDMA1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTDMA2_vector           ////(0x03A0)
#else
#pragma interrupt INTDMA2 isr_INTDMA2
#endif
__interrupt void isr_INTDMA2(void)
{
    irq_INTDMA2();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTDMA3_vector           ////(0x03B0)
#else
#pragma interrupt INTDMA3 isr_INTDMA3
#endif
__interrupt void isr_INTDMA3(void)
{
    irq_INTDMA3();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTKR_vector             ////(0x03C0)
#else
#pragma interrupt INTKR isr_INTKR
#endif
__interrupt void isr_INTKR(void)
{
    irq_INTKR();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTWTI_vector            ////(0x03D0)
#else
#pragma interrupt INTWTI isr_INTWTI
#endif
__interrupt void isr_INTWTI(void)
{
    irq_INTWTI();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTWT_vector             ////(0x03E0)
#else
#pragma interrupt INTWT isr_INTWT
#endif
__interrupt void isr_INTWT(void)
{
    irq_INTWT();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTC0ERR_vector          ////(0x03F0)
//#pragma vector =  INTERR_vector            ////(0x03F0)
#else
#pragma interrupt INTC0ERR isr_INTC0ERR
//#pragma interrupt INTERR isr_INTERR
#endif
__interrupt void isr_INTC0ERR(void)
{
    irq_INTC0ERR();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTC0WUP_vector          ////(0x0400)
//#pragma vector =  INTSTA_vector            ////(0x0400)
#else
#pragma interrupt INTC0WUP isr_INTC0WUP_STA
//#pragma interrupt INTC0WUP isr_INTSTA
#endif
__interrupt void isr_INTC0WUP_STA(void)
{
    irq_INTC0WUP();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTC0REC_vector          ////(0x0410)
//#pragma vector =  INTIE1_vector            ////(0x0410)
#else
#pragma interrupt INTC0REC isr_INTC0REC_IE1

//#pragma interrupt INTIE1 isr_INTIE1
#endif
__interrupt void isr_INTC0REC_IE1(void)
{
    irq_INTC0REC();
}



#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTC0TRX_vector          ////(0x0420)
//#pragma vector =  INTIE2_vector            ////(0x0420)
#else
#pragma interrupt INTC0TRX isr_INTC0TRX_IE2
//#pragma interrupt INTIE2 isr_INTIE2
#endif
__interrupt void isr_INTC0TRX_IE2(void)
{
    irq_INTC0TRX();
}

#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTP8_vector             ////(0x0470)
#else
#pragma interrupt INTP8 isr_INTP8
#endif
__interrupt void isr_INTP8(void)
{
    irq_INTP8();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP6OV_vector          ////(0x0480)
#else
#pragma interrupt INTTP6OV isr_INTTP6OV
#endif
__interrupt void isr_INTTP6OV(void)
{
    irq_INTTP6OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP6CC0_vector         ////(0x0490)
#else
#pragma interrupt INTTP6CC0 isr_INTTP6CC0
#endif
__interrupt void isr_INTTP6CC0(void)
{
    irq_INTTP6CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP6CC1_vector         ////(0x04A0)
#else
#pragma interrupt INTTP6CC1 isr_INTTP6CC1
#endif
__interrupt void isr_INTTP6CC1(void)
{
    irq_INTTP6CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP7OV_vector          ////(0x04B0)
#else
#pragma interrupt INTTP7OV isr_INTTP7OV
#endif
__interrupt void isr_INTTP7OV(void)
{
    irq_INTTP7OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP7CC0_vector         ////(0x04C0)
#else
#pragma interrupt INTTP7CC0 isr_INTTP7CC0
#endif
__interrupt void isr_INTTP7CC0(void)
{
    irq_INTTP7CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP7CC1_vector         ////(0x04D0)
#else
#pragma interrupt INTTP7CC1 isr_INTTP7CC1
#endif
__interrupt void isr_INTTP7CC1(void)
{
    irq_INTTP7CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP8OV_vector          ////(0x04E0)
#else
#pragma interrupt INTTP8OV isr_INTTP8OV
#endif
__interrupt void isr_INTTP8OV(void)
{
    irq_INTTP8OV();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP8CC0_vector         ////(0x04F0)
#else
#pragma interrupt INTTP8CC0 isr_INTTP8CC0
#endif
__interrupt void isr_INTTP8CC0(void)
{
    irq_INTTP8CC0();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTTP8CC1_vector         ////(0x0500)
#else
#pragma interrupt INTTP8CC1 isr_INTTP8CC1
#endif
__interrupt void isr_INTTP8CC1(void)
{
    irq_INTTP8CC1();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB5R_vector           ////(0x0510)
#else
#pragma interrupt INTCB5R isr_INTCB5R
#endif
__interrupt void isr_INTCB5R(void)
{
    irq_INTCB5R();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTCB5T_vector           ////(0x0520)
#else
#pragma interrupt INTCB5T isr_INTCB5T
#endif
__interrupt void isr_INTCB5T(void)
{
    irq_INTCB5T();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTUA3R_vector           ////(0x0530)
#else
#pragma interrupt INTUA3R isr_INTUA3R
#endif
__interrupt void isr_INTUA3R(void)
{
    irq_INTUA3R();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTUA3T_vector           ////(0x0540)
#else
#pragma interrupt INTUA3T isr_INTUA3T
#endif
__interrupt void isr_INTUA3T(void)
{
    irq_INTUA3T();
}



/*Add 3365 CAN1 interrupt vectors in the end of isr section*/
#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTC1ERR_vector          ////(0x0430)
#else
#pragma interrupt INTC1ERR isr_INTC1ERR
#endif
__interrupt void isr_INTC1ERR(void)
{
    irq_INTC1ERR();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTC1WUP_vector          ////(0x0440)
#else
#pragma interrupt INTC1WUP isr_INTC1WUP
#endif
__interrupt void isr_INTC1WUP(void)
{
    irq_INTC1WUP();
}


#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTC1REC_vector          ////(0x0450)
#else
#pragma interrupt INTC1REC isr_INTC1REC
#endif
__interrupt void isr_INTC1REC(void)
{
    irq_INTC1REC();
}



#if _COMPILER_ == _IAR_EWV850_
#pragma vector =  INTC1TRX_vector          ////(0x0460)
#else
#pragma interrupt INTC1TRX isr_INTC1TRX
#endif
__interrupt void isr_INTC1TRX(void)
{
    irq_INTC1TRX();
}


#if _COMPILER_ == _IAR_EWV850_
/*IAR 会自动将中断服务程序放入ICODE区域*/
#else
#pragma text  
#endif




