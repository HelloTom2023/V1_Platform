#include "..\..\..\config\inc.h"
//寄存器向量表    
const tI2C_REG_ADD lc_tI2CRegAddTab[]={
    {
        (void*)0xFFFFFD80,(void*)0xFFFFFD82,
        (void*)0xFFFFFD84,(void*)0xFFFFFD8A,
        (void*)0xFFFFFD86,(void*)0xFFFFFD83,
        (void*)0xFFFFFD85,(void*)0xFFFFF16A,

        (void*)0xFFFFF407,(void*)0xFFFFF427,
        (void*)0xFFFFF447,(void*)0xFFFFFC67,
        (void*)0xFFFFF467,NULL,
        BIT1,BIT0,
    },  //I2C0
    {
        (void*)0xFFFFFD90,(void*)0xFFFFFD92,
        (void*)0xFFFFFD94,(void*)0xFFFFFD9A,
        (void*)0xFFFFFD96,(void*)0xFFFFFD93,
        (void*)0xFFFFFD95,(void*)0xFFFFF152,
        
        (void*)0xFFFFF408,(void*)0xFFFFF428,
        (void*)0xFFFFF448,(void*)0xFFFFFC68,
        (void*)0xFFFFF468,NULL,

        BIT1,BIT0,
    },  //I2C1
    {
        (void*)0xFFFFFDA0,(void*)0xFFFFFDA2,
        (void*)0xFFFFFDA4,(void*)0xFFFFFDAA,
        (void*)0xFFFFFDA6,(void*)0xFFFFFDA3,
        (void*)0xFFFFFDA5,(void*)0xFFFFF166,

        (void*)0xFFFFF412,(void*)0xFFFFF432,
        (void*)0xFFFFF452,(void*)0xFFFFFC72,
        (void*)0xFFFFF472,(void*)0xFFFFF712,

        BIT1,BIT0,
    },  //I2C2
    
};


tI2C_CMD_BLOCK la_tI2CDevCmdBuf[I2CN];
eI2C_SPEED la_eI2CDevSpeed[I2CN];

/*Return the device register block*/
tI2C_REG_ADD* i2c_get_reg_tab(eI2C_TYPE eType)
{
    return (tI2C_REG_ADD*)&lc_tI2CRegAddTab[eType];
}

/*Return the device command buff pointer*/
tI2C_CMD_BLOCK* i2c_get_dev_buf(eI2C_TYPE eType)
{
    return (tI2C_CMD_BLOCK*)&la_tI2CDevCmdBuf[eType];
}

/*Set i2c bus speed*/
void I2C_DeviceSetSpeed(eI2C_TYPE eType,eI2C_SPEED eSpeed) 
{

    if(eType >= I2CN)return;
    if(eSpeed >= I2C_SPEED_n) eSpeed = I2C_96KBPS;
    if(la_eI2CDevSpeed[eType] != eSpeed)
    {
    
           void* regCLn = lc_tI2CRegAddTab[eType].CLn_reg;
           void* regXn = lc_tI2CRegAddTab[eType].Xn_reg;

           switch(eSpeed)
           {
               case I2C_74KBPS:
                   /* set colock select register */
                   /* actually 74418 BPS */
                   *(uint8_t*)regOCKS1  = IIC_SELECTED3;
                   *(uint8_t*)regCLn  = IICCL_INITIALVALUE |  IIC_MODE_STANDARD | IIC_CLOCK1;
                   *(uint8_t*)regXn  = IIC_EXPENSION0;
                   break;
               case I2C_96KBPS:
               
                   /* set colock select register */
                   /* actually 96969 BPS */
                   *(uint8_t*)regOCKS1 = IIC_SELECTED3;
                   *(uint8_t*)regCLn = IICCL_INITIALVALUE |  IIC_MODE_STANDARD | IIC_CLOCK3;
                   *(uint8_t*)regXn = IIC_EXPENSION0;    
                   break;
                   
               case I2C_350KBPS:
       
                   /* set colock select register */
                   /* actually 355555 BPS */
                   *(uint8_t*)regOCKS1 = IIC_SELECTED3;
                   *(uint8_t*)regCLn = IICCL_INITIALVALUE |  IIC_MODE_HIGHSPEED | IIC_CLOCK3;
                   *(uint8_t*)regXn = IIC_EXPENSION0;
                   break;
       
               default:
                   ;
       
           }
           la_eI2CDevSpeed[eType] = eSpeed;
    }
}




bool I2C_DeviceInit(eI2C_TYPE eType,bool bstop)
{
	tI2C_REG_ADD* p_tReg = (tI2C_REG_ADD*)(&lc_tI2CRegAddTab[eType]);
	uint8_t io_pos = (p_tReg->SCL|p_tReg->SDA);
	uint8_t io_mask = (~io_pos);
	uint8_t re;
	uint8_t timer = 200;

	((byte_field*)(p_tReg->Cn_reg))->field.b7 = 0; //IICE1 = 0;     /* IIC1 disable */

	API_MemClear((uint8_t*)&la_tI2CDevCmdBuf[eType],sizeof(tI2C_CMD_BLOCK));/*Clear cmd buff*/

	/*Check i2c io state*/
	*(uint8_t*)(p_tReg->PFC_reg) &= io_mask;
	if(p_tReg->PFCE_reg)*(uint8_t*)(p_tReg->PFCE_reg) &= io_mask;
	*(uint8_t*)(p_tReg->PF_reg) &= io_mask;
	*(uint8_t*)(p_tReg->PMC_reg) &= io_mask;   /*Select them as io fuction*/
	*(uint8_t*)(p_tReg->PM_reg) &= io_mask;    /*Set io in output state*/

	*(uint8_t*)p_tReg->P_reg &= io_mask;       /*set io to low*/
	API_LoopDleay(20);                         /*delay for bus timing*/
	*(uint8_t*)p_tReg->P_reg |= (p_tReg->SCL);
	API_LoopDleay(20);
	*(uint8_t*)p_tReg->P_reg |= (p_tReg->SDA);
	API_LoopDleay(20);                         /*Create a stop timing*/


	if(bstop)
	{
		*(uint8_t*)(p_tReg->PM_reg) |= io_pos; /*Set io to input*/
		return TRUE;
	}

	/*Check bus is idle*/
	re = (*(uint8_t*)p_tReg->P_reg & p_tReg->SCL
	&& *(uint8_t*)p_tReg->P_reg & p_tReg->SDA);

    while((!re) && (timer)) 	/* wait sda\scl set high about 10ms,or else going run forward*/
    {	
      timer--;
    	API_LoopDleay(200);
    re = (*(uint8_t*)p_tReg->P_reg & p_tReg->SCL
         && *(uint8_t*)p_tReg->P_reg & p_tReg->SDA);
		
    }
    if(1)
    {
        /*Init i2c*/        
        ((byte_field*)(p_tReg->ICn_reg))->field.b6 = 1;//IICMK1 = 1;    /* INTIIC1 interrupt disable bit6*/
        ((byte_field*)(p_tReg->ICn_reg))->field.b7 = 0;//IICIF1 = 0;    /* clear INTIIC1 interrupt flag bit7*/
    
        /*Set interrupt priority*/
        ((byte_field*)(p_tReg->ICn_reg))->byte &= 0xF8;//IICIC1 &= 0xF8;
        ((byte_field*)(p_tReg->ICn_reg))->byte |= 0x03;//IICIC1 |= 0x03;
    
        /*set io in i2c state*/
        *(uint8_t*)(p_tReg->PFC_reg) |= io_pos;
        if(p_tReg->PFCE_reg)*(uint8_t*)(p_tReg->PFCE_reg) |= io_pos;
        *(uint8_t*)(p_tReg->PF_reg) |= io_pos;
        *(uint8_t*)(p_tReg->PMC_reg) |= io_pos;
    
        I2C_DeviceSetSpeed(eType,I2C_350KBPS);
    
        *(uint8_t*)p_tReg->SVAn_reg = 0x10;
        ((byte_field*)(p_tReg->Fn_reg))->field.b1 = 1; //STCEN1 = 1;//Fn bit1
        ((byte_field*)(p_tReg->Fn_reg))->field.b0 = 1; //IICRSV1 = 1;//Fn bit0 disable bus reserve state
        ((byte_field*)(p_tReg->Cn_reg))->field.b4 = 0; //SPIE1 = 0;//Cn bit4 disable interrupt for stop condition
        ((byte_field*)(p_tReg->Cn_reg))->field.b3 = 1; //WTIM1 = 1;//Cn bit3 interrupt at 9th clk falling edge
        ((byte_field*)(p_tReg->Cn_reg))->field.b2 = 1; //ACKE1 = 1;//Cn bit2 enable ack
        ((byte_field*)(p_tReg->ICn_reg))->field.b6 = 0; //IICMK1 = 0;//ICn bit6  enable the INTIIC1
    
        ((byte_field*)(p_tReg->Cn_reg))->field.b7 = 1; //IICE1 = 1;        /* Cn bit7 enable I2C1 */
        ((byte_field*)(p_tReg->Cn_reg))->field.b6 = 1; //LREL1 = 1;        /* Cn bit6 exit from the current communication operation and sets standby mode */

    }

	return re;
}


/*Release the bus line for a new set*/
uint8_t I2C_DeviceRelease(eI2C_TYPE eType)
{
       bool re = TRUE;
    tI2C_REG_ADD* p_tReg = (tI2C_REG_ADD*)(&lc_tI2CRegAddTab[eType]);
    /* Bus check */
    ((byte_field*)(p_tReg->ICn_reg))->field.b6 = 1;//IICMK1 = 1;    /* INTIIC0 interrupt disable */
    if (((byte_field*)(p_tReg->Fn_reg))->field.b6 == 1) //IICBSY1
    {
        /* bus busy */
        ((byte_field*)(p_tReg->ICn_reg))->field.b6 = 0;//IICMK1 = 0;    /* INTIIC0 interrupt enable */    
        re = FALSE;
    }
    else
    {
        /* Trigger check */
        //if (SPT1 == 1 || STT1 == 1)
        if(((byte_field*)(p_tReg->Cn_reg))->field.b0 == 1
           || ((byte_field*)(p_tReg->Cn_reg))->field.b1 == 1 )//
        {
            ((byte_field*)(p_tReg->ICn_reg))->field.b6 = 0;//IICMK1 = 0;    /* INTIIC0 interrupt enable */    
            re = FALSE;
        }
    }

    if(FALSE == re ) //主端释放总线，等待从端释放
    {
        ((byte_field*)(p_tReg->Fn_reg))->field.b1 = 1; //STCEN1 = 1;//Fn bit1/* enable start condition when stop condition don't  activate */
        ((byte_field*)(p_tReg->Cn_reg))->field.b3 = 1; //WTIM1 = 1;    /* enable start /stop condition operate */
    }
    return re;
}

uint8_t bakData = 0;

/*Start i2c than all options are handed in interrupt*/
uint8_t I2C_DeviceStart(eI2C_TYPE eType,tI2C_CMD_BLOCK* p_tI2CCmd,uint8_t* p_cErr)
{
    bool re = TRUE;
    uint16_t dly = D_WAIT_START_CONDITION_LOOP;
    tI2C_REG_ADD* p_tReg = (tI2C_REG_ADD*)(&lc_tI2CRegAddTab[eType]);
    if(eType == 0)
    {
	bakData = eType;
	}
	else  if(eType == 1)
    {
	bakData = eType;
	}
	else if(eType == 2)
    {
	bakData = eType;
	}
    if(I2C_DeviceRelease(eType))
    {
        /*Fill data into cmd buffer*/
        I2C_DeviceSetSpeed(eType,p_tI2CCmd->eSpeed);
        API_MemCopy((uint8_t*)p_tI2CCmd,(uint8_t*)&la_tI2CDevCmdBuf[eType],sizeof(tI2C_CMD_BLOCK));
        
        ((byte_field*)(p_tReg->Cn_reg))->field.b1 = 1; //STT1 = 1;    /* IIC0 start condition */
        ((byte_field*)(p_tReg->ICn_reg))->field.b6 = 0;//IICMK1 = 0;    /* INTIIC0 interrupt enable */    
        while( dly-- && ((byte_field*)(p_tReg->Fn_reg))->field.b7 == 1); /*delay some cir for start condition*/
        *p_cErr = I2C_ERR_NONE;
        if(0 == dly)
        {
            I2C_DeviceInit(eType,false);
            re = FALSE;
            *p_cErr = I2C_ERR_START;
        }
        else
        {
             
            ((byte_field*)(p_tReg->Cn_reg))->field.b3 = 1; //WTIM1 = 1;//Cn bit3 interrupt at 9th clk falling edge
            bakData = p_tI2CCmd->cAddr;
            *(uint8_t*)(p_tReg->Dn_reg) = p_tI2CCmd->cAddr;    /* send address */
            
            re = TRUE;
        }
        
    }
    else
    {
        re = FALSE;
        *p_cErr = I2C_ERR_BUSY;
    }

    return (re);
}
#ifdef D_TW8836_I2C0_EN
extern  uint8_t ADI7186SoftResetFlag;
void isrI2C0_Comm(void)
{
    I2C_CMD_STRUCT* p_IIcCmd = &I2CDevCmdBuf;
    uint8_t tCnt;

    /* Control for communication  */
    if ((IICBSY0 == 0) && (p_IIcCmd->gCnt != 0))
    {
        p_IIcCmd->gCallBack.p_fFunc(I2C_RET_ERR);
    }
    /* Control for sended address */
    else
    {
        switch(p_IIcCmd->gStatusFlag)
        {
            case I2C_WRITE_INDEX:
                if(ACKD0 == 1)
                {
                    if(TRC0 == 1)
                    {
                        WTIM0 = 1;
                        IIC0 = p_IIcCmd->gPageIndex;
			    if(1 == p_IIcCmd->gWRflag)
				{
				  p_IIcCmd->gStatusFlag = I2C_RE_START;
			    	}
			    else
				{
				  p_IIcCmd->gStatusFlag = I2C_WRITE_DATA;
			    	}
                    }
                }
                else
                {
                    p_IIcCmd->gCallBack.p_fFunc(I2C_RET_NOSUBADDR);/*no ack*/
                }
                break;
            case I2C_WRITE_DATA:
                if (TRC0 == 1)
                {
                    if ((ACKD0 == 0) && (p_IIcCmd->gCnt != 0))
                    {
                        p_IIcCmd->gCallBack.p_fFunc(I2C_RET_TIMEOUT);   /*no ack*/
                    }
                    else
                    {
                        if(p_IIcCmd->gCnt < p_IIcCmd->gLen)
                        {
                          if(1 == p_IIcCmd->gFlag)
                         {
                            tCnt = p_IIcCmd->gCnt;
                         }
			     else
			    {
                            tCnt = (p_IIcCmd->gCnt*3)+2;
			    }
				 if((p_IIcCmd->gPageIndex == 0xff )&&
				 	(p_IIcCmd->gAddr == 0xc0) &&
				 	(p_IIcCmd->gBuffer[tCnt]==0x80))
				 {
					ADI7186SoftResetFlag = 1;
				 }
                            IIC0 = p_IIcCmd->gBuffer[tCnt];
				 p_IIcCmd->gCnt++;	
                        }
                        else
                        {
                            SPT0 = 1;
                            p_IIcCmd->gCallBack.p_fFunc(I2C_RET_SUCCESS);
                        }
                    }
                }
                break;
            case I2C_RE_START:
                if(ACKD0 == 1)
                {
                    if(TRC0 == 1)
                    {
                        WTIM0 = 1;
                        STT0 = 1;   /* IIC0 send start condition */
                        /* Wait */
                        if(1 == STCF0);//NOP
                        IIC0 = (p_IIcCmd->gAddr | 0x01);
                    }
                    else
                    {
                        /*send address and get ack*/
                        p_IIcCmd->gStatusFlag = I2C_READ_DATA;   /* address complete */
                        ACKE0 = 1;
                        WTIM0 = 0;
                        WREL0 = 1;
                    }
                }
                else
                {
                    p_IIcCmd->gCallBack.p_fFunc(I2C_RET_NOSUBADDR);/*no ack*/
                }
                break;
            case I2C_READ_DATA:
                    p_IIcCmd->gRData[p_IIcCmd->gCnt] = IIC0;
                    p_IIcCmd->gCnt++;
                    if(p_IIcCmd->gCnt >= p_IIcCmd->gLen)
                    {
                        ACKE0 = 0;
                        WREL0 = 1;
                        WTIM0=1;

                        SPT0 = 1;
                        p_IIcCmd->gCallBack.p_fFunc(I2C_RET_SUCCESS);
                    }
                    else
                    {
                        WREL0 = 1;
                    }
                break;
            case I2C_STOP_READ_WRITE:
                ACKE0 = 0;
                WREL0 = 1;
                WTIM0=1;
                SPT0 = 1;
                p_IIcCmd->gStatusFlag = I2C_WRITE_INDEX;
                break;
				
        }

    }
}

#else
void isrI2C0_Comm(void)
{
    tI2C_CTRL_BLOCK* p_tI2CCtrlBlock = I2C_GetCtrlBlock(I2C0);
    tI2C_CMD_BLOCK* p_tI2CCmd = &la_tI2CDevCmdBuf[I2C0];
    IICIF0 = 0;

     if (IICBSY0 == 0 && p_tI2CCtrlBlock->eState != I2C_STATE_WAIT_STOP)
     {
         p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
         p_tI2CCtrlBlock->eErr = I2C_ERR_STOP;
         return;
     }
     switch(p_tI2CCtrlBlock->eState)
     {
         case I2C_STATE_WAIT_TRANSE:
             switch(p_tI2CCmd->eCmd)
             {
                 case I2C_CMD_CHK:
                     if(ACKD0)
                     {
                         /*Get ack*/
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                     }
                     else 
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_IDLE;
                         p_tI2CCtrlBlock->eErr = I2C_ERR_ADD;
                     }
                     SPT0 = 1; 
                     SPIE0 = 1; /*Open stop_interrupt*/
                      
                 break;
                 case I2C_CMD_WRITE_DEFAULT:
                 if(TRC0)
                 { 
                     if(p_tI2CCtrlBlock->cByteCnt >= p_tI2CCmd->cLen)
                     { 
                         /*Send data complete,open stop_interrupt*/
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                         SPT0 = 1;
                         SPIE0 = 1; 
                        
                     }
                     else 
                     {
                         if(ACKD0)
                         {
                             /*Send data*/
                             uint8_t* p_cData;
                             if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                             {
                                 p_cData = (p_tI2CCmd->uData.p_cBuff);
                             }
                             else
                             {
                                 p_cData = (p_tI2CCmd->uData.a_cBuff);
                             }
        
                             IIC0 = p_cData[p_tI2CCtrlBlock->cByteCnt];
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt ++;
                 }    
                 break;

                 case I2C_CMD_WRITE_SUBADD:
                 /*Tx State*/
                 if(TRC0)
                 { 
                     if(p_tI2CCtrlBlock->cByteCnt > p_tI2CCmd->cLen)
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                         SPT0 = 1;
                         SPIE0 = 1; 
                         
                     }
                     else 
                     {
                         /*Send data complete,open stop_interrupt*/
                         if(ACKD0)
                         {
                             if(p_tI2CCtrlBlock->cByteCnt == 0)IIC0 = p_tI2CCmd->eSubAddr;
                             else
                             {
                                 uint8_t* p_cData;
                                 if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                                 {
                                     p_cData = (p_tI2CCmd->uData.p_cBuff);
                                 }
                                 else
                                 {
                                     p_cData = (p_tI2CCmd->uData.a_cBuff);
                                 }
            
                                 IIC0 = p_cData[p_tI2CCtrlBlock->cByteCnt - 1];
                             }
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt ++;
                 }    
                 break;
                 case I2C_CMD_READ_DEFAULT:

                     if(p_tI2CCtrlBlock->cByteCnt == 0)
                     {
                         /*send address and get ack*/
                         if(ACKD0 && 0 == TRC0)
                         {
                             /*master release the bus,wait slaver release*/
                             ACKE0 = 1;
                             WTIM0 = 0;
                             WREL0 = 1;
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     else
                     {
                         /*Rx data*/
                         uint8_t* p_cData;
                         if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                         {
                             p_cData = (p_tI2CCmd->uData.p_cBuff);
                         }
                         else
                         {
                             p_cData = (p_tI2CCmd->uData.a_cBuff);
                         }
                         if(p_tI2CCmd->cLen)p_cData[p_tI2CCtrlBlock->cByteCnt-1] = IIC0;
                         
                         if(p_tI2CCtrlBlock->cByteCnt >= p_tI2CCmd->cLen)
                         {
                             /*Rx end and general stop timing,Open stop_interrupt*/
                             ACKE0 = 0;
                             WREL0 = 1;
                             WTIM0 = 1;
                             p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                             SPT0 = 1;
                             SPIE0 = 1;
                             
                         }
                         else
                         {
                             WREL0 = 1;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt++;
                 
                 break;
                 case I2C_CMD_READ_SUBADD:

                 /*Get ack*/
                 if(ACKD0 && TRC0)
                 {
                     /*Send subaddress*/
                     if(p_tI2CCtrlBlock->cByteCnt == 0)
                     {
                         IIC0 = p_tI2CCmd->eSubAddr;
                         p_tI2CCtrlBlock->cByteCnt++;
                     }
                     else
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_REPEAT_START;
                     }
                     
                 }
                 else 
                 {
                     p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                     p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                 }
                 
                 break;
             }
         break;




         case I2C_STATE_WAIT_STOP:
             SPIE0 = 0;    /*Close stop_interrupt*/
             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
         break;
     }
}
#endif

void isrI2C1_Comm(void)
{
     tI2C_CTRL_BLOCK* p_tI2CCtrlBlock = I2C_GetCtrlBlock(I2C1);
     tI2C_CMD_BLOCK* p_tI2CCmd = &la_tI2CDevCmdBuf[I2C1];
     IICIF1 = 0;
#if 0
     if(ALD1)
     {
         p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
         p_tI2CCtrlBlock->eErr = I2C_ERR_STOP;
         return;
     }
#endif

     if (IICBSY1 == 0 && p_tI2CCtrlBlock->eState != I2C_STATE_WAIT_STOP)
     {
         p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
         p_tI2CCtrlBlock->eErr = I2C_ERR_STOP;
         return;
     }
     switch(p_tI2CCtrlBlock->eState)
     {
         case I2C_STATE_WAIT_TRANSE:
             switch(p_tI2CCmd->eCmd)
             {
                 case I2C_CMD_CHK:
                     if(ACKD1)
                     {
                         /*Get ack*/
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                     }
                     else 
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_IDLE;
                         p_tI2CCtrlBlock->eErr = I2C_ERR_ADD;
                     }
                     SPT1 = 1; 
                     SPIE1 = 1; /*Open stop_interrupt*/
                      
                 break;
                 case I2C_CMD_WRITE_DEFAULT:
                 if(TRC1)
                 { 
                     if(p_tI2CCtrlBlock->cByteCnt >= p_tI2CCmd->cLen)
                     { 
                         /*Send data complete,open stop_interrupt*/
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                         SPT1 = 1;
                         SPIE1 = 1; 
                        
                     }
                     else 
                     {
                         if(ACKD1)
                         {
                             /*Send data*/
                             uint8_t* p_cData;
                             if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                             {
                                 p_cData = (p_tI2CCmd->uData.p_cBuff);
                             }
                             else
                             {
                                 p_cData = (p_tI2CCmd->uData.a_cBuff);
                             }
        
                             IIC1 = p_cData[p_tI2CCtrlBlock->cByteCnt];
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt ++;
                 }    
                 break;

                 case I2C_CMD_WRITE_SUBADD:
                 /*Tx State*/
                 if(TRC1)
                 { 
                     if(p_tI2CCtrlBlock->cByteCnt > p_tI2CCmd->cLen)
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                         SPT1 = 1;
                         SPIE1 = 1; 
                         
                     }
                     else 
                     {
                         /*Send data complete,open stop_interrupt*/
                         if(ACKD1)
                         {
                             if(p_tI2CCtrlBlock->cByteCnt == 0)IIC1 = p_tI2CCmd->eSubAddr;
                             else
                             {
                                 uint8_t* p_cData;
                                 if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                                 {
                                     p_cData = (p_tI2CCmd->uData.p_cBuff);
                                 }
                                 else
                                 {
                                     p_cData = (p_tI2CCmd->uData.a_cBuff);
                                 }
            
                                 IIC1 = p_cData[p_tI2CCtrlBlock->cByteCnt - 1];
                             }
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt ++;
                 }    
                 break;
                 case I2C_CMD_READ_DEFAULT:

                     if(p_tI2CCtrlBlock->cByteCnt == 0)
                     {
                         /*send address and get ack*/
                         if(ACKD1 && 0 == TRC1)
                         {
                             /*master release the bus,wait slaver release*/
                             ACKE1 = 1;
                             WTIM1 = 0;
                             WREL1 = 1;
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     else
                     {
                         /*Rx data*/
                         uint8_t* p_cData;
                         if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                         {
                             p_cData = (p_tI2CCmd->uData.p_cBuff);
                         }
                         else
                         {
                             p_cData = (p_tI2CCmd->uData.a_cBuff);
                         }
                         if(p_tI2CCmd->cLen)p_cData[p_tI2CCtrlBlock->cByteCnt-1] = IIC1;
                         
                         if(p_tI2CCtrlBlock->cByteCnt >= p_tI2CCmd->cLen)
                         {
                             /*Rx end and general stop timing,Open stop_interrupt*/
                             ACKE1 = 0;
                             WREL1 = 1;
                             WTIM1 = 1;
                             p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                             SPT1 = 1;
                             SPIE1 = 1;
                             
                         }
                         else
                         {
                             WREL1 = 1;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt++;
                 
                 break;
                 case I2C_CMD_READ_SUBADD:

                 /*Get ack*/
                 if(ACKD1 && TRC1)
                 {
                     /*Send subaddress*/
                     if(p_tI2CCtrlBlock->cByteCnt == 0)
                     {
                         IIC1 = p_tI2CCmd->eSubAddr;
                         p_tI2CCtrlBlock->cByteCnt++;
                     }
                     else
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_REPEAT_START;
                     }
                     
                 }
                 else 
                 {
                     p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                     p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                 }
                 
                 break;
             }
         break;




         case I2C_STATE_WAIT_STOP:
             SPIE1 = 0;    /*Close stop_interrupt*/
             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
         break;
     }
}

void isrI2C2_Comm(void)
{
     tI2C_CTRL_BLOCK* p_tI2CCtrlBlock = I2C_GetCtrlBlock(I2C2);
     tI2C_CMD_BLOCK* p_tI2CCmd = &la_tI2CDevCmdBuf[I2C2];
     IICIF2 = 0;
#if 0
    if(ALD2)
     {
         p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
         p_tI2CCtrlBlock->eErr = I2C_ERR_STOP;
         return;
     }
#endif

     if (IICBSY2 == 0 && p_tI2CCtrlBlock->eState !=I2C_STATE_WAIT_STOP)
     {
         p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
         p_tI2CCtrlBlock->eErr = I2C_ERR_STOP;
         return;
     }
     switch(p_tI2CCtrlBlock->eState)
     {
         case I2C_STATE_WAIT_TRANSE:
             switch(p_tI2CCmd->eCmd)
             {
                 case I2C_CMD_CHK:
                     if(ACKD2)
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                     }
                     else 
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_IDLE;
                         p_tI2CCtrlBlock->eErr = I2C_ERR_ADD;
                     }
                     SPT2 = 1; 
                     SPIE2 = 1; 
                      
                 break;
                 case I2C_CMD_WRITE_DEFAULT:
                 if(TRC2)
                 { 
                     if(p_tI2CCtrlBlock->cByteCnt >= p_tI2CCmd->cLen)
                     { 
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                         SPT2 = 1;
                         SPIE2 = 1;  
                        
                     }
                     else 
                     {
                         if(ACKD2)
                         {
                             uint8_t* p_cData;
                             if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                             {
                                 p_cData = (p_tI2CCmd->uData.p_cBuff);
                             }
                             else
                             {
                                 p_cData = (p_tI2CCmd->uData.a_cBuff);
                             }
        
                             IIC2 = p_cData[p_tI2CCtrlBlock->cByteCnt];
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt ++;
                 }    
                 break;

                 case I2C_CMD_WRITE_SUBADD:
                 if(TRC2)
                 { 
                     if(p_tI2CCtrlBlock->cByteCnt > p_tI2CCmd->cLen)
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                         SPT2 = 1;
                         SPIE2 = 1;  
                         
                     }
                     else 
                     {
                         if(ACKD2)
                         {
                             if(p_tI2CCtrlBlock->cByteCnt == 0)IIC2 = p_tI2CCmd->eSubAddr;
                             else
                             {
                                 uint8_t* p_cData;
                                 if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                                 {
                                     p_cData = (p_tI2CCmd->uData.p_cBuff);
                                 }
                                 else
                                 {
                                     p_cData = (p_tI2CCmd->uData.a_cBuff);
                                 }
            
                                 IIC2 = p_cData[p_tI2CCtrlBlock->cByteCnt - 1];
                             }
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt ++;
                 }    
                 break;
                 case I2C_CMD_READ_DEFAULT:

                     if(p_tI2CCtrlBlock->cByteCnt == 0)
                     {
                         if(ACKD2 && 0 == TRC2)
                         {
                             ACKE2 = 1;
                             WTIM2 = 0;
                             WREL2 = 1;
                         }
                         else
                         {
                             p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                         }
                     }
                     else
                     {
                         uint8_t* p_cData;
                         if(p_tI2CCmd->uFlag.tField.bDataIsPoint)
                         {
                             p_cData = (p_tI2CCmd->uData.p_cBuff);
                         }
                         else
                         {
                             p_cData = (p_tI2CCmd->uData.a_cBuff);
                         }
                         p_cData[p_tI2CCtrlBlock->cByteCnt-1] = IIC2;
                         
                         if(p_tI2CCtrlBlock->cByteCnt >= p_tI2CCmd->cLen)
                         {
                             ACKE2 = 0;
                             WREL2 = 1;
                             WTIM2 = 1;
                             p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_STOP;
                             SPT2 = 1;
                             SPIE2 = 1;
                             
                         }
                         else
                         {
                             WREL2 = 1;
                         }
                     }
                     p_tI2CCtrlBlock->cByteCnt++;
                 
                 break;
                 case I2C_CMD_READ_SUBADD:
                 if(ACKD2 && TRC2)
                 {
                     if(p_tI2CCtrlBlock->cByteCnt == 0)
                     {
                         IIC2 = p_tI2CCmd->eSubAddr;
                     }
                     else
                     {
                         p_tI2CCtrlBlock->eState = I2C_STATE_REPEAT_START;
                     }
                     p_tI2CCtrlBlock->cByteCnt++;
                 }
                 else 
                 {
                     p_tI2CCtrlBlock->eErr = I2C_ERR_ACK;
                     p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                 }
                 
                 break;
             }
         break;




         case I2C_STATE_WAIT_STOP:
             SPIE2 = 0;     
             p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
         break;
     }
}

#if 0
//产生停止条件
void i2c_stop(tI2C_REG_ADD* p_tReg)
{
    //((byte_field*)(((tI2C_REG_ADD*)&(lc_tI2CRegAddTab[eType]))->Cn_reg))->field.b0 = 1; //SPTn = 1
    ((byte_field*)(p_tReg->Cn_reg))->field.b0 = 1;
}

//是否允许停止信号产生中断
void i2c_stop_int_en(tI2C_REG_ADD* p_tReg,uint8_t en)
{ 
    ((byte_field*)(p_tReg->Cn_reg))->field.b3 = en;
}


//控制是否发出ACK
void i2c_set_ack(tI2C_REG_ADD* p_tReg,uint8_t ack)
{
    //((byte_field*)(((tI2C_REG_ADD*)&(lc_tI2CRegAddTab[eType]))->Cn_reg))->field.b2 = ack; //ACKEn
    ((byte_field*)(p_tReg->Cn_reg))->field.b2 = ack;
}

//察看是否检测到有ACK
bool i2c_get_ack(tI2C_REG_ADD* p_tReg)
{
    //return ((byte_field*)(((tI2C_REG_ADD*)&(lc_tI2CRegAddTab[eType]))->Sn_reg))->field.b2; //ACKDn
    return ((byte_field*)(p_tReg->Sn_reg))->field.b2;
}

//取得移位寄存器数据
uint8_t i2c_get_byte(tI2C_REG_ADD* p_tReg)
{
    return (*(uint8_t*)(p_tReg->Dn_reg));
}

//向移位寄存器中写数据
void i2c_send_byte(tI2C_REG_ADD* p_tReg,uint8_t data)
{ 
    (*(uint8_t*)(p_tReg->Dn_reg)) = data;
}

#endif


