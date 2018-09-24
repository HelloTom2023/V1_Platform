/**********************************************************
 * @file        Tw6638_Drv.c
 * @purpose
 * @version    0.01
 * @date      2015.05.29
 * @author    xjh
 * @brief
 ***********************************************************
 *     History:
 *  <write/modify>        <time>        <version >    <desc>
 *  Deefisher.Lyu          02.Feb.2013        v0.01        created
 *
  **********************************************************/
#define TW8836_DRV_C
/* ========================= File include ======================= */
#include "..\..\config\inc.h"

#ifdef D_VIDEO_SWITCH_TW8836

#define IIC0_MASTERADDRESS          0x10

#define  PMC3H0               	(((__IO_REG8_BIT*) (addr_PMC3H))->no0)
#define  PMC3H1              	(((__IO_REG8_BIT*) (addr_PMC3H))->no1)
#define  PF3H0               	(((__IO_REG8_BIT*) (addr_PF3H))->no0)
#define  PF3H1               	(((__IO_REG8_BIT*) (addr_PF3H))->no1)
#define  PM3H0               	(((__IO_REG8_BIT*) (addr_PM3H))->no0)
#define  PM3H1               	(((__IO_REG8_BIT*) (addr_PM3H))->no1)
#define  P3H0               	(((__IO_REG8_BIT*) (addr_P3H))->no0)
#define  P3H1               	(((__IO_REG8_BIT*) (addr_P3H))->no1)

#define IIC0_SDA			P3H0
#define IIC0_SCL			P3H1

#define IIC_WAIT_TIMEOUT	100

void I2C0_Delay(void)
{
    uint8_t i = 5;
    while(i-- > 0);
}

uint8_t IIC0_Init(void)
{
    IICE0 = 0;  /* IIC0 disable */
    IICMK0 = 1; /* INTIIC0 interrupt disable */
    IICIF0 = 0; /* clear INTIIC0 interrupt flag */
    /* Set INTIIC0 lowest priority */
    IICIC0 |= 0x07;
#if 0		//334kbps
    OCKS0 = IIC_SELECTED0;
    IICCL0 = IICCL_INITIALVALUE |  IIC_MODE_STANDARD | IIC_CLOCK0;
#else		//96kbps
    OCKS0 = IIC_SELECTED3;
    IICCL0 = IICCL_INITIALVALUE |  IIC_MODE_STANDARD | IIC_CLOCK3;
#endif
    IICX0 = IIC_EXPENSION0;
    SVA0 = IIC0_MASTERADDRESS;
    STCEN0 = 1;
    IICRSV0 = 1;
    SPIE0 = 0;
    WTIM0 = 1;
    ACKE0 = 1;
    IICMK0 = 0;
    /* SCL00 pin set */
    PFC3H |= 0x02;
    PF3H |= 0x02;
    PMC3H |= 0x02;
    /* SDA00 pin set */
    PFC3H |= 0x01;
    PF3H |= 0x01;
    PMC3H |= 0x01;

    return 1;
}


void I2C0_ReInit(void)
{
	IICE0 = 0;  /* IIC0 disable */
	IICMK0 = 1; /* INTIIC0 interrupt disable */
	IICIF0 = 0; /* clear INTIIC0 interrupt flag */
	
	PMC3H0 = 0;     // io mode		//SDA
	PMC3H1 = 0;					//SCL
	PF3H0 = 1;      //OP output
	PF3H1 = 1;      //op output
	
	IIC0_SCL =  0;
	IIC0_SDA = 0;
	I2C0_Delay();
	IIC0_SCL = 1;
	I2C0_Delay();
	IIC0_SDA = 1;
	I2C0_Delay();

	IIC0_Init();
}

uint8_t TW8836_I2C_Start(uint8_t cAddr,uint8_t iPage,uint8_t* p_cData,uint8_t cLen,void* p_vCallBack,uint8_t Flag)
{
    uint8_t status = I2C_ERR_NONE;
    uint8_t wait = 0x7f;

    IICE0 = 1;
    LREL0 = 1;
    /* bus check */
    IICMK0 = 1; /* INTIIC0 interrupt disable */
    if (IICBSY0 == 1)
    {
        /* bus busy */
        IICMK0 = 0; /* INTIIC0 interrupt enable */
        status = I2C_ERR_BUSY;
    }
    else
    {
        /* trigger check */
        if (SPT0 == 1 || STT0 == 1)
        {
            IICMK0 = 0; /* INTIIC0 interrupt enable */
            status = I2C_ERR_START;
        }
        else
        {
            STT0 = 1;   /* IIC0 send start condition */
            IICMK0 = 0; /* INTIIC0 interrupt enable */
            /* Wait */
            while((wait--)&&(1 == STCF0));

            /* Set parameter */
            I2CDevCmdBuf.gAddr = cAddr;
            I2CDevCmdBuf.gPageIndex = iPage;
            I2CDevCmdBuf.gStatusFlag = I2C_WRITE_INDEX;
            I2CDevCmdBuf.gWRflag = Flag;
            I2CDevCmdBuf.gCnt = 0;
            I2CDevCmdBuf.gLen = cLen;
            I2CDevCmdBuf.gBuffer = p_cData;
            I2CDevCmdBuf.gRData = p_cData;
            I2CDevCmdBuf.gCallBack.p_fFunc =(fCALL_BACK)p_vCallBack;
            IIC0 = I2CDevCmdBuf.gAddr; /* send address */
	     I2CDevCtrl.gWaitTimer = IIC_WAIT_TIMEOUT;
        }
    }

    return (status);

}


uint8_t TW8836_CallBack_Common(uint8_t Result)
{
    I2CDevCtrl.gResult = Result;
    return 0;
}


/**********************************************************
 * @function    Tw8836_WriteDisposal
 * @brief
 * @param
 * @retval     Result
 **********************************************************/
 uint8_t ADI7186SoftResetFlag = 0;
void Tw8836_WriteDisposal(void)
{
    uint8_t SubResult = I2C_ERR_NUM;
    uint8_t i = 0,j = 2,tCnt = 0,tBuff[64];
    uint8_t *pTemp = I2CDevCtrl.gData.p_cData;
    if(I2CDevCtrl.gWaitTimer>0)
    {
	I2CDevCtrl.gWaitTimer--;
    }
    switch(I2CDevCtrl.gDisposalStep)
    {
        case OPERATION_0:
            break;
        case OPERATION_1:
              pTemp += I2CDevCtrl.gWriteCnt;
		SubResult = TW8836_I2C_Write_1(pTemp[0],pTemp[1],&pTemp[0],1,(void *)TW8836_CallBack_Common);

            if(I2C_ERR_NONE == SubResult)
            {
                I2CDevCtrl.gWriteCnt+=3;
                I2CDevCtrl.gDisposalStep = OPERATION_2;
            }
            else
            {
                video_printf(_T("I2C Start :%d,%d,%d\n",I2CDevCtrl.gWriteCnt,I2CDevCtrl.gResult,SubResult));
            }
            break;
            //Check Result
        case OPERATION_2:
            if((I2C_RET_SUCCESS == I2CDevCtrl.gResult))
            {
                pTemp += I2CDevCtrl.gWriteCnt;
                if((0xff != pTemp[0])||(0xff != pTemp[1])||(0xff !=pTemp[2]))
                {
                    video_printf(_T("%x,%x,%x\n", pTemp[0], pTemp[1], pTemp[2]));
                    I2CDevCtrl.gResult = I2C_RET_WAIT;
                    I2CDevCtrl.gDisposalStep = OPERATION_1;
                }
                else
                {
                    I2CDevCtrl.gWriteCnt = 0;
                    I2CDevCtrl.gResult = I2C_RET_IDLE;
                    I2CDevCtrl.gDisposalStep = OPERATION_0;
			video_printf(_T(" Write7186 Over!!\n"));
                }
            }
            else if(I2C_RET_SUCCESS < I2CDevCtrl.gResult)
            {
                video_printf(_T("I2C RET :%d,%d,%d\n",I2CDevCtrl.gWriteCnt,I2CDevCtrl.gResult,I2CDevCmdBuf.gStatusFlag));
            }
	#if 1
	     else if((ACKD0 == 0) &&(ADI7186SoftResetFlag > 0)) 
	     {
	     		ADI7186SoftResetFlag++;
			if(ADI7186SoftResetFlag>5)
			{
				ADI7186SoftResetFlag = 0;
				SPT0 = 1;		// send STOP signal.
				I2CDevCtrl.gResult = I2C_RET_SUCCESS;
			}
	     }
	#endif
            break;
        case OPERATION_3:
            video_printf(_T("0x%x ",*(pTemp+1+I2CDevCtrl.gWriteCnt)));
            SubResult = TW8836_I2C_Write_1(pTemp[tCnt*3],pTemp[0],pTemp+1+I2CDevCtrl.gWriteCnt,1,(void *)TW8836_CallBack_Common);
            if(I2C_ERR_NONE == SubResult)
            {
                I2CDevCtrl.gDisposalStep = OPERATION_4;
            }
            else
            {
            }
            break;
            //Check Result
        case OPERATION_4:
            if(I2C_RET_SUCCESS == I2CDevCtrl.gResult)
            {
                I2CDevCtrl.gWriteCnt++;
                if(I2CDevCtrl.gWriteCnt>=64)
                {
                    I2CDevCtrl.gWriteCnt = 0;
                    I2CDevCtrl.gResult = I2C_RET_IDLE;
                    I2CDevCtrl.gDisposalStep = OPERATION_0;
                    video_printf(_T("\n"));
                }
                else
                {
                    I2CDevCtrl.gResult = I2C_RET_WAIT;
                    I2CDevCtrl.gDisposalStep = OPERATION_3;
                }
            }
            else if(I2C_RET_SUCCESS < I2CDevCtrl.gResult)
            {
                video_printf(_T("1.I2C RET :%d,%d,%d\n",I2CDevCtrl.gWriteCnt,I2CDevCtrl.gResult,I2CDevCmdBuf.gStatusFlag));
            }
            break;
        default:
            break;
    }

}

void Tw8836_WriteErrReset(void)
{
    if(I2CDevCtrl.gErrCnt<100)
    {
        I2CDevCtrl.gErrCnt++;
    }
    else
    {
        //I2CDevCmdBuf.gStatusFlag = I2C_STOP_READ_WRITE;
        I2C0_ReInit();
        I2CDevCtrl.gWriteCnt=0;
        I2CDevCtrl.gResult = I2C_RET_WAIT;
        I2CDevCtrl.gRWStep = OPERATION_0;
        I2CDevCtrl.gDisposalStep = OPERATION_0;
    }
    video_printf(_T("I2C RET TIMEOUT Err Reset:%d,%d\n",I2CDevCtrl.gWriteCnt,I2CDevCtrl.gDisposalStep));
}

void Tw8836_WriteStart(uint8_t  *tpData)
{
    video_printf(_T("UpdateStep start:%d\n",I2CDevCtrl.gWriteCnt));
    I2CDevCtrl.gData.p_cData = tpData;
    I2CDevCtrl.gResult = I2C_RET_WAIT;
    I2CDevCtrl.gDisposalStep = OPERATION_1;
    I2CDevCtrl.gWaitTimer = IIC_WAIT_TIMEOUT;
    video_printf(_T("Tw8836_SetTftParameter:%x,%x,%x\n",tpData[0],tpData[1],tpData[2]));
}

/**********************************************************
 * @function    Tw8836_WriteCommon
 * @brief
 * @param
 * @retval     Result
 **********************************************************/
uint8_t Tw8836_WriteCommon(uint8_t* pParam)
{
    uint8_t Result = SUBLAYER_DOING;
    if(I2CDevCtrl.gErrCnt>0)
    {
       if(I2C_RET_SUCCESS > I2CDevCtrl.gResult)
        {
          I2CDevCtrl.gErrCnt--;
          return (Result);
        }
    }
	
    switch(I2CDevCtrl.gRWStep)
    {
        case OPERATION_0:
            Tw8836_WriteStart(pParam);
            I2CDevCtrl.gRWStep = OPERATION_1;
            break;
            //Check Result
        case OPERATION_1:
            if(I2C_RET_IDLE == I2CDevCtrl.gResult)
            {
                I2CDevCtrl.gRWStep = OPERATION_0;
                I2CDevCtrl.gErrCnt=0;
                Result = SUBLAYER_DONE;
                video_printf(_T("Tw8836_UpdateParameter ok\n"));
            }
            else if(I2C_RET_SUCCESS < I2CDevCtrl.gResult)
            {
                Tw8836_WriteErrReset();
				I2CDevCtrl.gResult = I2C_RET_TIMEOUT;
                video_printf(_T("I2C RET TIMEOUT:%d,%d\n",I2CDevCtrl.gWriteCnt,I2CDevCtrl.gDisposalStep));
				return I2C_RET_TIMEOUT;
            }
	     else if(I2C_RET_WAIT == I2CDevCtrl.gResult)
	     {
			if(I2CDevCtrl.gWaitTimer==0)
			{
				Tw8836_WriteErrReset();
				I2CDevCtrl.gResult = I2C_RET_TIMEOUT;
				video_printf(_T("*******I2C RER WAIT TIMEOUT*******"));
				return I2C_RET_TIMEOUT;
			}
	     }
            break;

        default:
            break;
    }

    return (Result);
}

uint8_t Adi7186TempData[6];
uint8_t TW8836_WriteData(uint8_t Addr, uint16_t Reg, uint8_t param)
{
	Adi7186TempData[0] = Addr;
	Adi7186TempData[1] = Reg;
	Adi7186TempData[2] = param;
	Adi7186TempData[3] = 0xff;
	Adi7186TempData[4] = 0xff;
	Adi7186TempData[5] = 0xff;

	return Tw8836_WriteCommon(Adi7186TempData);
}

/**********************************************************
 * @function    Tw8836_AINCWriteCommon
 * @brief
 * @param
 * @retval     Result
 **********************************************************/
uint8_t Tw8836_AINCWriteCommon(uint16_t PageReg,uint8_t* pParam)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(I2CDevCtrl.gRWStep)
    {
        case OPERATION_0:
            I2CDevCtrl.gResult = I2C_RET_WAIT;
            I2CDevCtrl.gData.a_cData[0] = 0xff;
            I2CDevCtrl.gData.a_cData[1] = (uint8_t)(PageReg>>8)&0xFF;
            SubResult = TW8836_I2C_Write(I2CDevCtrl.gData.a_cData[0],(&(I2CDevCtrl.gData.a_cData[0])),1,(void *)TW8836_CallBack_Common);
            if(I2C_ERR_NONE == SubResult)
            {
                I2CDevCtrl.gRWStep = OPERATION_1;
            }
            else
            {
            }
            break;
        case OPERATION_1:
            if(I2C_RET_SUCCESS == I2CDevCtrl.gResult)
            {
#if 0
                uint8_t i;
                video_printf(_T("0x%x %lx\n",pParam[0], fTw8836.Tw8836_PacketId));
                for(i=1; i<65; i++)
                {
                    video_printf(_T("0x%x ",pParam[i]));
                }
                video_printf(_T("\n"));
#endif
                I2CDevCtrl.gData.p_cData = pParam;
                I2CDevCtrl.gResult = I2C_RET_WAIT;
                I2CDevCtrl.gDisposalStep = OPERATION_3;
                I2CDevCtrl.gRWStep = OPERATION_2;
                I2CDevCmdBuf.gFlag= 1;
                video_printf(_T("0x%x %lx\n",I2CDevCtrl.gData.p_cData[0], fTw8836.Tw8836_PacketId));
            }
            else if(I2C_RET_SUCCESS < I2CDevCtrl.gResult)
            {

            }
            break;
        case OPERATION_2:
            if(I2C_RET_IDLE == I2CDevCtrl.gResult)
            {
                I2CDevCtrl.gRWStep = OPERATION_0;
                I2CDevCmdBuf.gFlag= 0;
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_TIMEOUT == I2CDevCtrl.gResult)
            {
                video_printf(_T("I2C AINC TIMEOUT:%d,%d\n",I2CDevCtrl.gWriteCnt,I2CDevCtrl.gDisposalStep));
            }
            break;

        default:
            break;
    }

    return (Result);
}

uint8_t Tw8836_WriteOneCommon(uint16_t PageReg, uint8_t Param,uint8_t flag)
{
    uint8_t cAddr;
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    if(I2CDevCtrl.gErrCnt>0)
    {
       if(I2C_RET_SUCCESS > I2CDevCtrl.gResult)
        {
          I2CDevCtrl.gErrCnt--;
          return (Result);
        }
    }

    if(1 == flag)
    {
        if(I2CDevCtrl.gRWStep<OPERATION_3)
            I2CDevCtrl.gRWStep = OPERATION_2;
    }
    switch(I2CDevCtrl.gRWStep)
    {
        case OPERATION_0:
	     cAddr=(PageReg>>8)&0xFF;  //Device Id
            I2CDevCtrl.gData.a_cData[0] = PageReg&0xFF;  //Register
            I2CDevCtrl.gData.a_cData[1] = Param;  //Data
	     I2CDevCtrl.gResult = I2C_RET_WAIT;
            SubResult = TW8836_I2C_Write_1(cAddr,I2CDevCtrl.gData.a_cData[0],(&(I2CDevCtrl.gData.a_cData[0])),1,(void *)TW8836_CallBack_Common);
            if(I2C_ERR_NONE == SubResult)
            {
                I2CDevCtrl.gRWStep = OPERATION_1;
            }
            else
            {
            }
            break;
            //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == I2CDevCtrl.gResult)
            {
                I2CDevCtrl.gErrCnt=0;
                I2CDevCtrl.gRWStep = OPERATION_2;
                video_printf(_T("1.WriteOneCommon:%x,%x\n",I2CDevCtrl.gData.a_cData[0],I2CDevCmdBuf.gBuffer[1]));
            }
            else if(I2C_RET_SUCCESS < I2CDevCtrl.gResult)
            {
               Tw8836_WriteErrReset();
                TEST(_T("1.I2C ONE CMD RET TIMEOUT\n"));
            }
            break;
        case OPERATION_2:
	     cAddr = (PageReg>>8)&0xFF;
            I2CDevCtrl.gData.a_cData[0] = PageReg&0xFF;
            I2CDevCtrl.gData.a_cData[1] = Param;
            I2CDevCtrl.gResult = I2C_RET_WAIT;
            SubResult = TW8836_I2C_Write_1(cAddr,I2CDevCtrl.gData.a_cData[0],(&(I2CDevCtrl.gData.a_cData[0])),1,(void *)TW8836_CallBack_Common);
            if(I2C_ERR_NONE == SubResult)
            {
                I2CDevCtrl.gRWStep = OPERATION_3;
            }
            else
            {
            }
            break;
        case OPERATION_3:
            if(I2C_RET_SUCCESS == I2CDevCtrl.gResult)
            {
                I2CDevCtrl.gRWStep = OPERATION_0;
                I2CDevCtrl.gResult = I2C_RET_IDLE;
                I2CDevCtrl.gErrCnt=0;
                video_printf(_T("2.WriteOneCommon:%x,%x\n",I2CDevCtrl.gData.a_cData[0],I2CDevCmdBuf.gBuffer[1]));
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_SUCCESS < I2CDevCtrl.gResult)
            {
                Tw8836_WriteErrReset();
                TEST(_T("2.I2C ONE CMD RET TIMEOUT\n"));
            }
            break;

        default:
            break;
    }

    return (Result);
}

/**********************************************************
 * @function    Tw8836_ReadCommon
 * @brief      Commonly read from register
 * @param
 * @retval     result of execute
 **********************************************************/
uint8_t Tw8836_ReadCommon(uint16_t PageReg, uint8_t *pData,uint8_t flag)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t cAddr;

   #if 0
    if(I2CDevCtrl.gErrCnt>0)
    {
       if(I2C_RET_SUCCESS > I2CDevCtrl.gResult)
        {
          I2CDevCtrl.gErrCnt--;
          return (Result);
        }
    }
   #endif
    if(1 == flag)
    {
            I2CDevCtrl.gRWStep = OPERATION_0;
    }
    switch(I2CDevCtrl.gRWStep)
    {
        case OPERATION_0:
            cAddr=(PageReg>>8)&0xFF;
            I2CDevCtrl.gData.a_cData[0] = PageReg&0xFF;
	     I2CDevCtrl.gResult = I2C_RET_WAIT;
            SubResult = TW8836_I2C_Read_1(cAddr,I2CDevCtrl.gData.a_cData[0],pData,1,(void *)TW8836_CallBack_Common);
            if(I2C_ERR_NONE == SubResult)
            {
                I2CDevCtrl.gRWStep = OPERATION_1;
            }
            else
            {
            }
            break;
            //Check Result
        case OPERATION_1:
            if(I2C_RET_SUCCESS == I2CDevCtrl.gResult)
            {
                 I2CDevCtrl.gRWStep = OPERATION_0;
                I2CDevCtrl.gResult = I2C_RET_IDLE;
                I2CDevCtrl.gErrCnt=0;
                Result = SUBLAYER_DONE;
            }
            else if(I2C_RET_SUCCESS < I2CDevCtrl.gResult)
            {
                TEST(_T("[1] I2C READ write RET TIMEOUT\n"));
		  		Tw8836_WriteErrReset();
				I2CDevCtrl.gResult = I2C_RET_TIMEOUT;
				return I2C_RET_TIMEOUT;
		  
            }
	     else if(I2C_RET_WAIT == I2CDevCtrl.gResult)
	     {
		  if(I2CDevCtrl.gWaitTimer==0)
		  {
			Tw8836_WriteErrReset();
			I2CDevCtrl.gResult = I2C_RET_TIMEOUT;
			TEST(_T("[2] I2C READ write RET TIMEOUT\n"));
			return I2C_RET_TIMEOUT;
		  }
	     }
            break;

        default:
            break;
    }

    return (Result);
}

#endif
