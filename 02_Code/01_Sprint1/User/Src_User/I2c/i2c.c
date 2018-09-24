#define _I2C_C_
#include "..\..\..\User\src_user\config\inc.h"

tI2C_CTRL_BLOCK la_tI2CCtrlBlock[I2CN];
tI2C_CMD_BLOCK  la_tI2CCmdBlock[I2CN][D_I2C_DEV_QUE_DEEP];
tI2C_CMD_BLOCK  la_tI2CCmdTmpBlock[I2CN];
tI2C_CMD_BLOCK  l_tI2CCmdTmpBuff;

void I2C_CmdQueInit(eI2C_TYPE eType)
{
    API_MemClear((uint8_t*)(&la_tI2CCtrlBlock[eType]),sizeof(tI2C_CTRL_BLOCK));
    la_tI2CCtrlBlock[eType].tCmdQue.p_vBuf = (void*)la_tI2CCmdBlock[eType];
    la_tI2CCtrlBlock[eType].tCmdQue.cMax = D_I2C_DEV_QUE_DEEP;
}

void I2C_CmdInit(eI2C_TYPE eType)
{
    API_MemClear((uint8_t*)(&la_tI2CCmdBlock[eType]),sizeof(tI2C_CMD_BLOCK));
}

uint8_t I2C_Init(eI2C_TYPE eType,bool bstop)
{
    uint8_t re;
    I2C_CmdQueInit(eType);
    I2C_CmdInit(eType);
    re = I2C_DeviceInit(eType,bstop);
    if(re)
    {
        if(bstop)la_tI2CCtrlBlock[eType].eState = I2C_STATE_OFF;
        else la_tI2CCtrlBlock[eType].eState = I2C_STATE_IDLE;
    }
    

    return re;
    
}

eQUE_ERROR I2C_PostCmd(eI2C_TYPE eType,tI2C_CMD_BLOCK* p_tI2CCmd)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    
    tI2C_CTRL_BLOCK* p_tI2CCtrlBlock = &la_tI2CCtrlBlock[eType];
    if(p_tI2CCmd && p_tI2CCtrlBlock->tCmdQue.p_vBuf)
    {

        re = OS_PostQueElement(&(p_tI2CCtrlBlock->tCmdQue), (void*)p_tI2CCmd,sizeof(tI2C_CMD_BLOCK));
       
        if(re == QUE_ERR_NONE)p_tI2CCtrlBlock->cCmdCnt ++;
        
    }
    return re;
}


eQUE_ERROR I2C_GetCmd(eI2C_TYPE eType,tI2C_CMD_BLOCK* p_tI2CCmd)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    tI2C_CTRL_BLOCK* p_tI2CCtrlBlock = &la_tI2CCtrlBlock[eType];
    if(p_tI2CCtrlBlock->tCmdQue.p_vBuf && p_tI2CCmd)
    {
        re = OS_GetQueElement(&(p_tI2CCtrlBlock->tCmdQue),(void*)p_tI2CCmd,sizeof(tI2C_CMD_BLOCK));
        if(re == QUE_ERR_NONE && p_tI2CCtrlBlock->cCmdCnt)p_tI2CCtrlBlock->cCmdCnt --;
    }
    return re;
}

tI2C_CTRL_BLOCK* I2C_GetCtrlBlock(eI2C_TYPE eType)
{
   return (tI2C_CTRL_BLOCK*)&la_tI2CCtrlBlock[eType];
}


uint8_t I2C_ExecCmd(eI2C_TYPE eType,tI2C_CMD_BLOCK* p_tI2CCmd)
{
    uint8_t re  = FALSE;
    if(la_tI2CCtrlBlock[eType].eState == I2C_STATE_OFF)return FALSE;

    
    if(!p_tI2CCmd->uFlag.tField.bCallBackIsFunc)
    {
        *(p_tI2CCmd->uCallBack.p_cRet) = I2C_RET_IDLE;
    }
    
    if( 0 == la_tI2CCtrlBlock[eType].cCmdCnt                    //队列中无命令
        && I2C_STATE_IDLE == la_tI2CCtrlBlock[eType].eState)     //且总线空闲状态，直接发送         
    {
        la_tI2CCtrlBlock[eType].cByteCnt = 0;
        la_tI2CCtrlBlock[eType].cTimer = 0;
        la_tI2CCtrlBlock[eType].eState = I2C_STATE_WAIT_TRANSE;   //先设置状态防止中断过快产生时状态还没转换
        re = I2C_DeviceStart(eType,p_tI2CCmd,(uint8_t*)&(la_tI2CCtrlBlock[eType].eErr));
        API_MemCopy((uint8_t*)p_tI2CCmd, (uint8_t*)&la_tI2CCmdTmpBlock[eType],sizeof(tI2C_CMD_BLOCK)); //此种情况必须保存命令到状态机的缓冲区
        if(FALSE == re)la_tI2CCtrlBlock[eType].eState = I2C_STATE_WAIT_RESUME;

        /*I2C State signal is send successfully,wait for sending data and return result*/
        if(0 == p_tI2CCmd->uFlag.tField.bCallBackIsFunc)
        {
            *(p_tI2CCmd->uCallBack.p_cRet) = I2C_RET_WAIT;  
        }
        else if(p_tI2CCmd->uCallBack.p_fFunc)
        {
            //p_tI2CCmd->uCallBack.p_fFunc(I2C_RET_WAIT);
        }

        re = TRUE;

    }
    else                                             //否则命令入队列
    {
        if(QUE_ERR_NONE == I2C_PostCmd(eType,p_tI2CCmd))
        {
            //la_tI2CCtrlBlock[eType].eErr = I2C_ERR_QUE;
            re = TRUE;
        }
    }

    

    return re;
}


uint8_t I2C_CheckDevice(eI2C_TYPE eType,uint8_t cAddr,bool bFuncPoint,
                        void* p_vCallBack,eI2C_SPEED eSpeed)
{
    l_tI2CCmdTmpBuff.cAddr = cAddr;
    l_tI2CCmdTmpBuff.eCmd = I2C_CMD_CHK;
    l_tI2CCmdTmpBuff.uFlag.cByte = (bFuncPoint);
    l_tI2CCmdTmpBuff.eSpeed = eSpeed;
    if(bFuncPoint)l_tI2CCmdTmpBuff.uCallBack.p_fFunc =(fCALL_BACK)p_vCallBack;
    else l_tI2CCmdTmpBuff.uCallBack.p_cRet = (uint8_t*)p_vCallBack;
    return I2C_ExecCmd(eType,&l_tI2CCmdTmpBuff);
}


uint8_t I2C_Write(eI2C_TYPE eType,uint8_t cAddr,
                bool bDataPiont,uint8_t* p_cData,uint8_t cLen,
                bool bFuncPoint,void* p_vCallBack,eI2C_SPEED eSpeed)
{
    l_tI2CCmdTmpBuff.cAddr = cAddr;
    l_tI2CCmdTmpBuff.eCmd = I2C_CMD_WRITE_DEFAULT;
    l_tI2CCmdTmpBuff.cLen = cLen;
    l_tI2CCmdTmpBuff.uFlag.cByte = (bDataPiont<<1|bFuncPoint);
    l_tI2CCmdTmpBuff.eSpeed = eSpeed;
    if(bDataPiont)l_tI2CCmdTmpBuff.uData.p_cBuff = p_cData;
    else API_MemCopy((uint8_t*)p_cData, (uint8_t*)(l_tI2CCmdTmpBuff.uData.a_cBuff),cLen);

    if(bFuncPoint)l_tI2CCmdTmpBuff.uCallBack.p_fFunc =(fCALL_BACK)p_vCallBack;
    else l_tI2CCmdTmpBuff.uCallBack.p_cRet = (uint8_t*)p_vCallBack;

    return  I2C_ExecCmd(eType,&l_tI2CCmdTmpBuff);
}





uint8_t I2C_Read(eI2C_TYPE eType,uint8_t cAddr,
               bool bDataPiont,uint8_t* p_cData,uint8_t cLen,
               bool bFuncPoint,void* p_vCallBack,eI2C_SPEED eSpeed)
{

    l_tI2CCmdTmpBuff.cAddr = cAddr|0x01;
    l_tI2CCmdTmpBuff.eCmd = I2C_CMD_READ_DEFAULT;
    l_tI2CCmdTmpBuff.cLen = cLen;
    
    l_tI2CCmdTmpBuff.uFlag.cByte = (bDataPiont<<1|bFuncPoint);
    l_tI2CCmdTmpBuff.eSpeed = eSpeed;
    
    if(bDataPiont)l_tI2CCmdTmpBuff.uData.p_cBuff = p_cData;
    else API_MemCopy((uint8_t*)p_cData, (uint8_t*)(l_tI2CCmdTmpBuff.uData.a_cBuff),cLen);

    if(bFuncPoint)l_tI2CCmdTmpBuff.uCallBack.p_fFunc =(fCALL_BACK)p_vCallBack;
    else l_tI2CCmdTmpBuff.uCallBack.p_cRet = (uint8_t*)p_vCallBack;
    

    return  I2C_ExecCmd(eType,&l_tI2CCmdTmpBuff);
}


uint8_t I2C_WriteToSubAdd(eI2C_TYPE eType,uint8_t cAddr,uint8_t subadd,
                          bool bDataPiont,uint8_t* p_cData,uint8_t cLen,
                          bool bFuncPoint,void* p_vCallBack,eI2C_SPEED eSpeed)
{
    l_tI2CCmdTmpBuff.cAddr = cAddr;
    l_tI2CCmdTmpBuff.eSubAddr = subadd;
    l_tI2CCmdTmpBuff.eCmd = I2C_CMD_WRITE_SUBADD;
    l_tI2CCmdTmpBuff.cLen = cLen;

    l_tI2CCmdTmpBuff.uFlag.cByte = (bDataPiont<<1|bFuncPoint);
    l_tI2CCmdTmpBuff.eSpeed = eSpeed;
    
    if(bDataPiont)l_tI2CCmdTmpBuff.uData.p_cBuff = p_cData;
    else API_MemCopy((uint8_t*)p_cData, (uint8_t*)(l_tI2CCmdTmpBuff.uData.a_cBuff),cLen);

    if(bFuncPoint)l_tI2CCmdTmpBuff.uCallBack.p_fFunc =(fCALL_BACK)p_vCallBack;
    else l_tI2CCmdTmpBuff.uCallBack.p_cRet = (uint8_t*)p_vCallBack;
        
    return  I2C_ExecCmd(eType,&l_tI2CCmdTmpBuff);

}

uint8_t I2C_ReadFromSubAdd(eI2C_TYPE eType,uint8_t cAddr,uint8_t subadd,
                            bool bDataPiont,uint8_t* p_cData,uint8_t cLen,
                            bool bFuncPoint,void* p_vCallBack,eI2C_SPEED eSpeed)
{
    l_tI2CCmdTmpBuff.cAddr = cAddr;
    l_tI2CCmdTmpBuff.eSubAddr = subadd;
    l_tI2CCmdTmpBuff.eCmd = I2C_CMD_READ_SUBADD;
    l_tI2CCmdTmpBuff.cLen = cLen;
    l_tI2CCmdTmpBuff.eSpeed = eSpeed;
    l_tI2CCmdTmpBuff.uFlag.cByte = (bDataPiont<<1|bFuncPoint);

    if(bDataPiont)l_tI2CCmdTmpBuff.uData.p_cBuff = p_cData;
    else API_MemCopy((uint8_t*)p_cData, (uint8_t*)(l_tI2CCmdTmpBuff.uData.a_cBuff),cLen);

    if(bFuncPoint)l_tI2CCmdTmpBuff.uCallBack.p_fFunc =(fCALL_BACK)p_vCallBack;
    else l_tI2CCmdTmpBuff.uCallBack.p_cRet = (uint8_t*)p_vCallBack;
     
    return  I2C_ExecCmd(eType,&l_tI2CCmdTmpBuff);
}

eI2C_ERROR I2C_GetLastErr(eI2C_TYPE eType)
{
    return la_tI2CCtrlBlock[eType].eErr;
}

void I2C_CoreProc(eI2C_TYPE eType)
{
    tI2C_CTRL_BLOCK* p_tI2CCtrlBlock = &la_tI2CCtrlBlock[eType];
    tI2C_CMD_BLOCK* p_tI2CCmd = &la_tI2CCmdTmpBlock[eType];
    switch(p_tI2CCtrlBlock->eState)
    {
        case I2C_STATE_IDLE:
            if(p_tI2CCtrlBlock->cCmdCnt)
            {
                I2C_GetCmd(eType,p_tI2CCmd);
                p_tI2CCtrlBlock->cTimer = 0;
                p_tI2CCtrlBlock->cByteCnt = 0;
                p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_RESUME;
                       
                 
            }
        break;
        case I2C_STATE_WAIT_TRANSE:
        case I2C_STATE_WAIT_STOP:
            if(p_tI2CCtrlBlock->cTimer > _set_timing_xms_base_i2c_core_tick(D_xMS(15)))
            {
                
                p_tI2CCtrlBlock->cTimer = 0;
                p_tI2CCtrlBlock->eErr = I2C_ERR_TIMEOUT;
                p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                ERROR(_T("I2C:TimeOut %d,add:%x\n",eType,p_tI2CCmd->cAddr));
            }
        break;
        case I2C_STATE_REPEAT_START:
            p_tI2CCmd->eCmd = I2C_CMD_READ_DEFAULT;
            p_tI2CCmd->cAddr |= 0x01;
            
            p_tI2CCtrlBlock->cByteCnt = 0;
            p_tI2CCtrlBlock->cTimer = 0;
            p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_RESUME;
        break;
        case I2C_STATE_WAIT_RESUME:
            p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_TRANSE;  //防中断先于下一条指令运行时产生
            if(I2C_DeviceStart(eType, p_tI2CCmd,(uint8_t*)&(p_tI2CCtrlBlock->eErr)))
            {
                p_tI2CCtrlBlock->eErr = I2C_ERR_NONE;
                if(0 == p_tI2CCmd->uFlag.tField.bCallBackIsFunc)
                {
                    *(p_tI2CCmd->uCallBack.p_cRet) = I2C_RET_WAIT;  //设置等待状态
                }
                else if(p_tI2CCmd->uCallBack.p_fFunc)
                {
                    //p_tI2CCmd->uCallBack.p_fFunc(I2C_RET_WAIT);
                }
                p_tI2CCtrlBlock->cTimer = 0;
                 
            }
            else p_tI2CCtrlBlock->eState = I2C_STATE_WAIT_RESUME;
            
            if(p_tI2CCtrlBlock->cTimer  > _set_timing_xms_base_i2c_core_tick(_8MS_))
            {
                p_tI2CCtrlBlock->eState = I2C_STATE_CALL_BACK;
                p_tI2CCtrlBlock->eErr = I2C_ERR_RESUME;
                ERROR(_T("I2C:ResumTimeOut %d,add:%x\n",eType,p_tI2CCmd->cAddr));
            }
        break;
        case I2C_STATE_CALL_BACK:
            p_tI2CCtrlBlock->eState = I2C_STATE_IDLE;
            if(0 == p_tI2CCmd->uFlag.tField.bCallBackIsFunc)
            {
                if(I2C_ERR_NONE == p_tI2CCtrlBlock->eErr)
                {
                    *(p_tI2CCmd->uCallBack.p_cRet) = I2C_RET_SUCCESS;
                }
                else
                {
                    *(p_tI2CCmd->uCallBack.p_cRet)= I2C_RET_ERR;
                    ERROR(_T("I2C:RetErr %d,add:%x\n",eType,p_tI2CCmd->cAddr));
                }
                
            }
            else 
            {
                uint8_t re = FALSE;
                if(p_tI2CCmd->uCallBack.p_fFunc) 
                {
                    if(I2C_ERR_NONE == p_tI2CCtrlBlock->eErr) //Unify Output of Callback Function and Return Parameter@Deefisher
                    {
                        re = p_tI2CCmd->uCallBack.p_fFunc(I2C_RET_SUCCESS);
                    }
                    else
                    {
                        re = p_tI2CCmd->uCallBack.p_fFunc(I2C_RET_ERR);
                        ERROR(_T("I2C:CallbackErr %d,add:%x\n",eType,p_tI2CCmd->cAddr));
                    }        
                }
                if(re || I2C_ERR_TIMEOUT == p_tI2CCtrlBlock->eErr)p_tI2CCtrlBlock->eState  = I2C_STATE_RESET;                          //call back 要求重启硬件
            }

        break;
        case I2C_STATE_RESET:
            if(p_tI2CCtrlBlock->cTimer > _set_timing_xms_base_i2c_core_tick(D_xMS(15)))
            {
                ERROR(_T("I2C_Reset"));
                I2C_DeviceInit(eType,FALSE);
                p_tI2CCtrlBlock->eState = I2C_STATE_IDLE;
            }
        break;
        
    }
}

////////////////////////////////////////////////////////////////////////////////

void I2C_Ch1Task(EVENT iEvt,eTASK_STATE eState)
{
    if(eState != TASK_STATE_RUNNING)return;
    
    if(EVT_CORE_TICK_READY & iEvt)
    {
        la_tI2CCtrlBlock[I2C1].cTimer++;
    }
    I2C_CoreProc(I2C1);
}

uint8_t I2C_Ch1Init(void)
{
    return I2C_Init(I2C1, FALSE);
}

uint8_t I2C_Ch1DInit(void)
{
    return I2C_Init(I2C1, TRUE);
}

uint8_t I2C_Ch1TaskStart(void)
{
    return OS_TaskStart(TASK_ID_I2C1);
}


static const tTASK_BLOCK sc_tI2CCh1TCB = {
    "I2C1",
    _I2C_TASK_TICK_,
    _I2C_CORE_TICK_,
    I2C_Ch1Task,
    I2C_Ch1Init,
    I2C_Ch1DInit,
};

////////////////////////////////////////////////////////////////////////////////
void I2C_Ch2Task(EVENT iEvt,eTASK_STATE eState)
{
    if(eState != TASK_STATE_RUNNING)return;

    if(EVT_CORE_TICK_READY & iEvt)
    {
        la_tI2CCtrlBlock[I2C2].cTimer++;
    }
    I2C_CoreProc(I2C2);
}

uint8_t I2C_Ch2Init(void)
{
    return I2C_Init(I2C2, FALSE);
}

uint8_t I2C_Ch2DInit(void)
{
    return I2C_Init(I2C2, TRUE);
}

uint8_t I2C_Ch2TaskStart(void)
{
    return OS_TaskStart(TASK_ID_I2C2);
}

static const tTASK_BLOCK sc_tI2CCh2TCB = {
    "I2C2",
    _I2C_TASK_TICK_,
    _I2C_CORE_TICK_,
    I2C_Ch2Task,
    I2C_Ch2Init,
    I2C_Ch2DInit,
};
#ifdef D_TW8836_I2C0_EN
////////////////////////////////////////////////////////////////////////////////
void I2C_Ch0Task(EVENT iEvt,eTASK_STATE eState)
{
    if(eState != TASK_STATE_RUNNING)return;

    if(EVT_CORE_TICK_READY & iEvt)
    {
        la_tI2CCtrlBlock[I2C0].cTimer++;
    }
  //  I2C_CoreProc(I2C0);
   Tw8836_WriteDisposal();
}

uint8_t I2C_Ch0Init(void)
{
    //return I2C_Init(I2C0, FALSE);
    return IIC0_Init();
}

uint8_t I2C_Ch0DInit(void)
{
    return I2C_Init(I2C0, TRUE);
}

uint8_t I2C_Ch0TaskStart(void)
{
    return OS_TaskStart(TASK_ID_I2C0);
}

static const tTASK_BLOCK sc_tI2CCh0TCB = {
    "I2C0",
    _I2C_TASK_TICK_,
    _I2C_CORE_TICK_,
    I2C_Ch0Task,
    I2C_Ch0Init,
    I2C_Ch0DInit,
};
#endif

void I2C_TaskCreate(void)
{
	OS_TaskCreate(TASK_ID_I2C1,&g_tI2C1TaskCB,&sc_tI2CCh1TCB,NULL,NULL,0);
       OS_TaskCreate(TASK_ID_I2C2,&g_tI2C2TaskCB,&sc_tI2CCh2TCB,NULL,NULL,0);
#ifdef D_TW8836_I2C0_EN
	OS_TaskCreate(TASK_ID_I2C0,&g_tI2C0TaskCB,&sc_tI2CCh0TCB,NULL,NULL,0);		//Add 2015-3-30
#endif
}

