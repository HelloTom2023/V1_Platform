#define _CORE_C_
#include "..\..\..\User\src_user\config\inc.h"

   

/*******************************************************************************
*List function
*******************************************************************************/


/*******************************************************************************
*Function: Insert a new node to the list
*          It will placed in front or behind of the target node
*******************************************************************************/
bool OS_ListInsert(tNODE* p_tTarg,tNODE* p_tNew,bool bHead)
{
    uint8_t re = FALSE;
    if(p_tTarg && p_tNew)
    {   
        
        if(p_tTarg != p_tNew)
        {
            if(FALSE == bHead)
            {
                /*set the new node as the next node of the target node*/
                p_tNew->p_tPrev = p_tTarg;
                if(p_tTarg->p_tNext)p_tTarg->p_tNext->p_tPrev = p_tNew;
                p_tNew->p_tNext = p_tTarg->p_tNext;
                p_tTarg->p_tNext = p_tNew;
            }
            else
            {
            
                /*set the new node as the prev node of the target node*/
                p_tNew->p_tPrev = p_tTarg->p_tPrev;
                if(p_tTarg->p_tPrev)p_tTarg->p_tPrev->p_tNext = p_tNew;
                p_tTarg->p_tPrev = p_tNew;
                p_tNew->p_tNext = p_tTarg;
            }
            
        }
        
        re = TRUE;
    }

    return re;
}


/*******************************************************************************
*Function: Remove the node from the list
*******************************************************************************/

bool OS_ListDelete(tNODE* p_tNode)
{
    uint8_t re = FALSE;
    if(p_tNode)
    {
        if(p_tNode->p_tPrev)p_tNode->p_tPrev->p_tNext = p_tNode->p_tNext;
        if(p_tNode->p_tNext)p_tNode->p_tNext->p_tPrev = p_tNode->p_tPrev;

        p_tNode->p_tNext = NULL;
        p_tNode->p_tPrev = NULL;
        p_tNode->p_tElement = NULL;
        re = TRUE;
	 src_printf(_T(" OS_ListDelete\n"));
    }
    return re;
}

/*******************************************************************************
*Function: Get the node in head of the list
*           
*******************************************************************************/

tNODE* OS_ListGetHead(tNODE* p_tNode)
{
    tNODE* p_tTempNode = NULL;
    if(p_tNode)
    {   
        p_tTempNode = p_tNode;
        while(p_tTempNode->p_tPrev)
        {
            p_tTempNode = p_tTempNode->p_tPrev;
        }
    }

    return p_tTempNode;
}


/*******************************************************************************
*Function: Get the node in tail of the list
*           
*******************************************************************************/

tNODE* OS_ListGetTail(tNODE* p_tNode)
{
    tNODE* p_tTempNode = NULL;
    if(p_tNode)
    {   
        p_tTempNode = p_tNode;
        while(p_tTempNode->p_tNext)
        {
            p_tTempNode = p_tTempNode->p_tNext;
        }
    }

    return p_tTempNode;
}


/*******************************************************************************
*
*RingQue function
*
*******************************************************************************/
eQUE_ERROR OS_InsertQueElement(tRING_QUE* p_tQue,bool bHead,void* p_vBuf,uint16_t iBufLen)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    ENTER_CRITICAL();
    if(p_tQue && p_tQue->p_vBuf)
    {
        uint16_t i;
        void* p_vBuffAdd ;
        if( QUE_ERR_FULL == p_tQue->eState )                             //队列满则直接覆盖一个消息,如有必要,可以给消息定义优先级
        {
            uint16_t i;
            if(bHead)
            {
                if( (p_tQue->cMax- 1) == p_tQue->cHead) p_tQue->cHead = 0;
                else p_tQue->cHead ++;                                   //删除头消息
            }
            else
            {
                if(0 == p_tQue->cTail)p_tQue->cTail = p_tQue->cMax - 1;
                else p_tQue->cTail --;                                   //删除尾消息
            }
            
        
        }
        
        p_tQue->eState = QUE_ERR_NONE;
        
        if( 0 == p_tQue->cHead )p_tQue->cHead = p_tQue->cMax - 1 ;      //将队列头指针前移
        else p_tQue->cHead -- ;

        p_vBuffAdd = (void*)((uint32_t)p_tQue->p_vBuf + ((uint32_t)p_tQue->cHead)*(uint32_t)iBufLen); 
        API_MemCopy((uint8_t *)p_vBuf,(uint8_t *)p_vBuffAdd,iBufLen);
       
        
        
        if( p_tQue->cHead == p_tQue->cTail )
        {
            p_tQue->eState = QUE_ERR_FULL;
        }
        
        EXIT_CRITICAL();
        re = QUE_ERR_NONE;
    }

    return re;
}

eQUE_ERROR OS_PostQueElement(tRING_QUE* p_tQue,void* p_vBuf,uint16_t iBufLen)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(p_tQue && p_tQue->p_vBuf)
    {
        ENTER_CRITICAL();
        if( QUE_ERR_FULL == p_tQue->eState  )                          //如果队列满，直接返回错误
        {
            EXIT_CRITICAL();
            ERROR(_T("PostQueue is Full:\n",(uint32_t)p_tQue));
            re = QUE_ERR_FULL;
        }
        else
        {
            void* p_vBuffAdd = (void*)((uint32_t)p_tQue->p_vBuf + ((uint32_t)p_tQue->cTail)*(uint32_t)iBufLen);

            p_tQue->eState  = QUE_ERR_NONE;
        
            API_MemCopy((uint8_t *)p_vBuf,(uint8_t*)p_vBuffAdd,iBufLen);
        
            p_tQue->cTail ++ ; 
            if( p_tQue->cMax == p_tQue->cTail) p_tQue->cTail = 0;     //更新底部计数器
            
        
            if( p_tQue->cHead == p_tQue->cTail )
            {
                p_tQue->eState  = QUE_ERR_FULL;
                ERROR(_T("Queue is in cMax->%lx\n",(uint32_t)p_tQue));
            }
        
            EXIT_CRITICAL();
            re = QUE_ERR_NONE;
        }
    }

    return re;
}

eQUE_ERROR OS_GetQueElement(tRING_QUE* p_tQue,void* p_vBuf,uint16_t iBufLen)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(p_tQue && p_tQue->p_vBuf)
    {
        ENTER_CRITICAL();
        
        if( QUE_ERR_EMPTY == p_tQue->eState  )                         //队列为空 
        {
            EXIT_CRITICAL();
            API_MemClear((uint8_t *)p_vBuf,iBufLen);
            re = QUE_ERR_EMPTY;
        }
        else
        {
            void* p_vBuffAdd = (void*)((uint32_t)p_tQue->p_vBuf + ((uint32_t)p_tQue->cHead)*(uint32_t)iBufLen);           
            p_tQue->eState  = QUE_ERR_NONE;
            
            API_MemCopy((uint8_t*)p_vBuffAdd,(uint8_t *)p_vBuf,iBufLen);
            
            p_tQue->cHead ++ ;
            if( p_tQue->cMax  == p_tQue->cHead ) p_tQue->cHead = 0;   //更新头计数器
            
        
            if(p_tQue->cHead == p_tQue->cTail )
            {
                p_tQue->eState  = QUE_ERR_EMPTY;
            }
            EXIT_CRITICAL();
            re = QUE_ERR_NONE;
        }
    }

    return re;
}

/*******************************************************************************
*RTC fuction block
*           
*******************************************************************************/


/*RTC block*/
#pragma pack(1)
typedef struct{
    uint8_t cHour;
    uint8_t cMinute;
    uint8_t cSecond;
    uint32_t lSysWatchSec;
    uint8_t cTmpSec;
    uint8_t cIntCnt;
}tRTC;

#pragma section data "no_init" begin    
tRTC l_tRtcBlock;
#pragma section data "no_init" end    

void isrOS_RTC(void)
{
	l_tRtcBlock.cIntCnt++;
	if(l_tRtcBlock.cIntCnt & 0x01)
	{
		l_tRtcBlock.lSysWatchSec ++;
	}
}

void OS_GetRTC(tRTC_BLOCK* p_tRtc)
{
    p_tRtc->cHour = l_tRtcBlock.cHour;
    p_tRtc->cMin = l_tRtcBlock.cMinute;
    p_tRtc->cSec = l_tRtcBlock.cSecond;
}


void OS_SetRTC(tRTC_BLOCK* p_tRtc)
{
    OS_HwRtcStop();
    l_tRtcBlock.cIntCnt = 1;
    l_tRtcBlock.cHour = p_tRtc->cHour;
    l_tRtcBlock.cMinute = p_tRtc->cMin;
    l_tRtcBlock.cSecond = p_tRtc->cSec;
    OS_HWRtcStart();
}



void OS_RTCHandle(void)
{
    l_tRtcBlock.cSecond = l_tRtcBlock.lSysWatchSec%60;
    if(l_tRtcBlock.cSecond != l_tRtcBlock.cTmpSec)
    {
        l_tRtcBlock.cMinute = (l_tRtcBlock.lSysWatchSec/60)%60;
        l_tRtcBlock.cHour = (l_tRtcBlock.lSysWatchSec/3600)%24;
        
        //core_printf(_T("____RTC:%d-%d-%d____\n",l_tRtcBlock.cHour,l_tRtcBlock.cMinute,l_tRtcBlock.cSecond));
        if(l_tRtcBlock.cSecond == 0)
        	core_printf(_T("____RTC:%d-%d-%d____\n",l_tRtcBlock.cHour,l_tRtcBlock.cMinute,l_tRtcBlock.cSecond));
        l_tRtcBlock.cTmpSec = l_tRtcBlock.cSecond;
        
        OS_PostEventMass(EVT_RTC_SECOND);
    }   
}


uint32_t OS_GetWatchSecond(void)
{
    return l_tRtcBlock.lSysWatchSec;
}

void OS_SetWatchSecond(uint32_t lSec)
{
    l_tRtcBlock.lSysWatchSec = lSec;
}

/*******************************************************************************
 * Task fuction block
 *******************************************************************************/




/*Task system start element*/
#pragma pack(1)
typedef struct core_contro_block{ 
    tNODE              tStartNode;
    tTASK_CTRL_BLOCK   tIdleTask;
    uint32_t           wIdleTimer;
    uint8_t            bOSActive;
    
    uint32_t           wOsTimerTick;
    uint8_t            cTaskNum;
}tCORE_BLOCK;

tCORE_BLOCK l_tCore;


#if _COMPILER_ == _IAR_EWV850_
const uint8_t lc_ColdStartFlgTab[8] = {'4','9','7','8','4','9','5','5'};
#else
#pragma section const "app_flag" begin
const uint8_t lc_ColdStartFlgTab[8] = {'4','9','7','8','4','9','5','5'};
#pragma section const "app_flag" end
#endif



/*Check ram block,It's can't to be init by boot*/
#if _COMPILER_ == _IAR_EWV850_
__no_init uint8_t l_RamColdStartFlgTab[8];
#elif _COMPILER_ == _RENESAS_CUBE_
#pragma section data "no_init" begin
uint8_t l_RamColdStartFlgTab[8];
uint16_t l_iRamChkFlg ;
#pragma section data "no_init" end
#else
uint8_t l_RamColdStartFlgTab[8];
#endif 


uint32_t OS_GetOsTick(void)
{
    return l_tCore.wOsTimerTick;
}

void OS_ClearOsTick(void)
{
	 l_tCore.wOsTimerTick = 0;
}

#if 1		/*Use hardware CRC calculate CRC Value */

uint16_t OS_CalCrc16(uint8_t *ptr, uint16_t len) 
{
	uint16_t crc = 0;
	uint8_t da;

	while(len--) 
	{
		da = (uint8_t)(crc>>8); 
		crc <<= 8; 
		CRCD = 0x0000;
		CRCIN = da^*ptr;
		crc ^= CRCD;
		ptr++;
	}

	return (crc);
}

#else	/*Use Searching table calculate CRC Value */
const uint16_t CRC16Tabl[256] = {
0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF, 
0x8C48, 0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7, 
0x1081, 0x0108, 0x3393, 0x221A, 0x56A5, 0x472C, 0x75B7, 0x643E, 
0x9CC9, 0x8D40, 0xBFDB, 0xAE52, 0xDAED, 0xCB64, 0xF9FF, 0xE876, 
0x2102, 0x308B, 0x0210, 0x1399, 0x6726, 0x76AF, 0x4434, 0x55BD, 
0xAD4A, 0xBCC3, 0x8E58, 0x9FD1, 0xEB6E, 0xFAE7, 0xC87C, 0xD9F5, 
0x3183, 0x200A, 0x1291, 0x0318, 0x77A7, 0x662E, 0x54B5, 0x453C, 
0xBDCB, 0xAC42, 0x9ED9, 0x8F50, 0xFBEF, 0xEA66, 0xD8FD, 0xC974, 
0x4204, 0x538D, 0x6116, 0x709F, 0x0420, 0x15A9, 0x2732, 0x36BB, 
0xCE4C, 0xDFC5, 0xED5E, 0xFCD7, 0x8868, 0x99E1, 0xAB7A, 0xBAF3, 
0x5285, 0x430C, 0x7197, 0x601E, 0x14A1, 0x0528, 0x37B3, 0x263A, 
0xDECD, 0xCF44, 0xFDDF, 0xEC56, 0x98E9, 0x8960, 0xBBFB, 0xAA72, 
0x6306, 0x728F, 0x4014, 0x519D, 0x2522, 0x34AB, 0x0630, 0x17B9, 
0xEF4E, 0xFEC7, 0xCC5C, 0xDDD5, 0xA96A, 0xB8E3, 0x8A78, 0x9BF1, 
0x7387, 0x620E, 0x5095, 0x411C, 0x35A3, 0x242A, 0x16B1, 0x0738, 
0xFFCF, 0xEE46, 0xDCDD, 0xCD54, 0xB9EB, 0xA862, 0x9AF9, 0x8B70, 
0x8408, 0x9581, 0xA71A, 0xB693, 0xC22C, 0xD3A5, 0xE13E, 0xF0B7, 
0x0840, 0x19C9, 0x2B52, 0x3ADB, 0x4E64, 0x5FED, 0x6D76, 0x7CFF, 
0x9489, 0x8500, 0xB79B, 0xA612, 0xD2AD, 0xC324, 0xF1BF, 0xE036, 
0x18C1, 0x0948, 0x3BD3, 0x2A5A, 0x5EE5, 0x4F6C, 0x7DF7, 0x6C7E, 
0xA50A, 0xB483, 0x8618, 0x9791, 0xE32E, 0xF2A7, 0xC03C, 0xD1B5, 
0x2942, 0x38CB, 0x0A50, 0x1BD9, 0x6F66, 0x7EEF, 0x4C74, 0x5DFD, 
0xB58B, 0xA402, 0x9699, 0x8710, 0xF3AF, 0xE226, 0xD0BD, 0xC134, 
0x39C3, 0x284A, 0x1AD1, 0x0B58, 0x7FE7, 0x6E6E, 0x5CF5, 0x4D7C, 
0xC60C, 0xD785, 0xE51E, 0xF497, 0x8028, 0x91A1, 0xA33A, 0xB2B3, 
0x4A44, 0x5BCD, 0x6956, 0x78DF, 0x0C60, 0x1DE9, 0x2F72, 0x3EFB, 
0xD68D, 0xC704, 0xF59F, 0xE416, 0x90A9, 0x8120, 0xB3BB, 0xA232, 
0x5AC5, 0x4B4C, 0x79D7, 0x685E, 0x1CE1, 0x0D68, 0x3FF3, 0x2E7A, 
0xE70E, 0xF687, 0xC41C, 0xD595, 0xA12A, 0xB0A3, 0x8238, 0x93B1, 
0x6B46, 0x7ACF, 0x4854, 0x59DD, 0x2D62, 0x3CEB, 0x0E70, 0x1FF9, 
0xF78F, 0xE606, 0xD49D, 0xC514, 0xB1AB, 0xA022, 0x92B9, 0x8330, 
0x7BC7, 0x6A4E, 0x58D5, 0x495C, 0x3DE3, 0x2C6A, 0x1EF1, 0x0F78,

};

uint16_t OS_CalCrc16(uint8_t *ptr, uint16_t len) 
{
	uint16_t crc = 0;
	uint8_t da;

	while(len--) 
	{
		da = (uint8_t)(crc>>8); 
		crc <<= 8; 
		crc ^= CRC16Tabl[da^*ptr]; 
		ptr++;
	}

	return (crc);
}

#endif

void CRC16_TableGenerate(void)
{
	uint8_t i = 0;
	uint16_t CRC = 0;
	core_printf(_T("CRC16_TABLE:\n"));
	for(i = 0;i<=255;i++)
	{
		if((i%8) == 0)
		{
			core_printf(_T("\n", CRC));
		}
		CRC = OS_CalCrc16(&i, 1);
		core_printf(_T("0x%x%x, ", (CRC>>8), (CRC&0xff)));
	}
}

/*******************************************************************************
 * Ram check fuction block
 *******************************************************************************/
bool OS_RamCheck(void* p_vStartAdd,uint16_t iSize,void* p_vChkSunAdd)
{
    uint16_t i;
    uint8_t cChkSum = 0x55;
    uint8_t* p_cData = (uint8_t*)p_vStartAdd;
    uint32_t sAdd,eAdd;
    
    if(NULL == p_vStartAdd || NULL == p_vChkSunAdd)return TRUE;
    
    OS_GetNoInitRamSectionAdd(&sAdd,&eAdd);
    if((uint32_t)p_vStartAdd < sAdd || (uint32_t)p_vStartAdd > eAdd)return FALSE;
    if((uint32_t)p_vChkSunAdd < sAdd || (uint32_t)p_vChkSunAdd > eAdd)return FALSE;
    
#if 0    
    for(i = 0; i < iSize ; i++)
    {
        cChkSum ^= *p_cData++ ;
    }
    return ((*((uint16_t*)p_vChkSunAdd)) == (cChkSum |((cChkSum ^ 0xaa)<<8)));
#else
    if((*((uint16_t*)p_vChkSunAdd)) == (OS_CalCrc16(p_cData, iSize)^0xaaaa))
    {
	return 1;
    }
    return 0;
#endif
}

/*******************************************************************************
 * Ram check fuction block
 *******************************************************************************/


void OS_ClearNoInitBlock(void)
{
    OS_ClearNoInitRamSectiont();
}


void OS_ClearRamChkElement(void* p_vChkSunAdd)
{
    if(p_vChkSunAdd)
    {
        *((uint16_t*)p_vChkSunAdd) += 0x0f;
    }
}


void OS_CreateRamChkBlock(void* p_vStartAdd,uint16_t iSize,void* p_vChkSunAdd)
{
    uint16_t i;
    uint8_t cChkSum = 0x55;
    uint8_t* p_cData = (uint8_t*)p_vStartAdd;
    uint32_t sAdd,eAdd;
    
    if(NULL == p_vStartAdd || NULL == p_vChkSunAdd)return ;
    
    OS_GetNoInitRamSectionAdd(&sAdd,&eAdd);
    if((uint32_t)p_vStartAdd < sAdd || (uint32_t)p_vStartAdd > eAdd)return ;
    if((uint32_t)p_vChkSunAdd < sAdd || (uint32_t)p_vChkSunAdd > eAdd)return ;
#if 0    
    for(i = 0; i < iSize ; i++)
    {
        cChkSum ^= *p_cData++ ;
    }

    *((uint16_t*)p_vChkSunAdd) = cChkSum |((cChkSum ^ 0xaa)<<8);

#else
    *((uint16_t*)p_vChkSunAdd) = OS_CalCrc16(p_cData, iSize)^0xaaaa;

#endif
}



void OS_CoreStartCheck(void)
{
    uint8_t i;
    tNODE* p_tTaskNode = &l_tCore.tStartNode;
    EVENT iEvt = 0;
    

    if(OS_RamCheck((void*)l_RamColdStartFlgTab,8,(void*)&l_iRamChkFlg))
    {
        iEvt = EVT_WARM_INIT;
    }
    else
    {
        iEvt = EVT_COLD_INIT;
        for(i = 0; i < 8; i++)
        {
            l_RamColdStartFlgTab[i] = lc_ColdStartFlgTab[i];
        }
        OS_CreateRamChkBlock((void*)l_RamColdStartFlgTab,8,(void*)&l_iRamChkFlg);
        API_MemClear((uint8_t*)&l_tRtcBlock,sizeof(tRTC));
    }
    


    while(p_tTaskNode)                                          
    {
        tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(p_tTaskNode->p_tElement);
        if(p_tTCB)
        {
            ENTER_CRITICAL();
            p_tTCB = (tTASK_CTRL_BLOCK*)(p_tTaskNode->p_tElement);
            p_tTCB->iEvt |= iEvt;
            EXIT_CRITICAL();
        }
        p_tTaskNode = p_tTaskNode->p_tNext;
    }

}


/*******************************************************************************
 * Fuction: System time tick
 *******************************************************************************/

void isrOS_Tick(void)
{
    volatile tNODE* p_tTaskNode = &l_tCore.tStartNode;
    uint8_t cTaskNum = l_tCore.cTaskNum + 1;    /*Add the idle task*/
    while(cTaskNum)
    {
        tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(p_tTaskNode->p_tElement);
        if(p_tTCB)
        {
            if(p_tTCB->iTaskTimer)p_tTCB->iTaskTimer --;   
            if(p_tTCB->cCoreTimer)p_tTCB->cCoreTimer --;
        }
                 
        if(p_tTaskNode->p_tNext)                                   /*Go to next task*/
        {
            p_tTaskNode = p_tTaskNode->p_tNext;                    /*Set next task*/
        }
        else 
        {
            p_tTaskNode = &l_tCore.tStartNode;                     /*Ready to next loop*/  
            break;
        }

        cTaskNum --;
    }
    l_tCore.wOsTimerTick ++;
}



void Task_IdleSpy(EVENT iEvt,eTASK_STATE eState)
{   
    if(iEvt & EVT_TASK_TICK_READY)
    {
        l_tCore.wIdleTimer++; 

        OS_RTCHandle();
    }
    
}


const tTASK_BLOCK lc_tTaskSpyCB ={
    "SPY",
    _set_timing_xms_base_core_tick(200),
    _set_timing_xms_base_core_tick(50),
    Task_IdleSpy,
    NULL,
    NULL,
};

/*******************************************************************************
 * Fuction : Init the task system
 *******************************************************************************/
void OS_Init(void)
{
    l_tCore.tStartNode.p_tNext = (tNODE*)0;
    l_tCore.tStartNode.p_tPrev = (tNODE*)0;
    l_tCore.tStartNode.p_tElement = (void*)&(l_tCore.tIdleTask);
    l_tCore.bOSActive = FALSE;
    API_MemClear((uint8_t*)&(l_tCore.tIdleTask), (sizeof(tTASK_CTRL_BLOCK)));
    l_tCore.tIdleTask.pc_tTCB = &lc_tTaskSpyCB;
    l_tCore.tIdleTask.Id = 0xff;
    OS_HWRtcStart();

}


/*******************************************************************************
 * Fuction : Check the task is existed or no
 *******************************************************************************/

tNODE* OS_TaskGetNode(uint8_t Id)
{
    tNODE* p_tNode = NULL;
    tNODE* pstart_node = &(l_tCore.tStartNode);
    while(pstart_node)          
    {
        tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(pstart_node->p_tElement);
        if(p_tTCB && p_tTCB->Id == Id)             /*Compare the id*/
        { 
            p_tNode = pstart_node;
            break;
        }
        else pstart_node = pstart_node->p_tNext;   /*check next task*/

    }

    return p_tNode;
}

/*******************************************************************************
 * Fuction : Get the task control block point
 *******************************************************************************/

tTASK_CTRL_BLOCK* OS_TaskGetBlock(uint8_t Id)
{
    tTASK_CTRL_BLOCK* p_tTask = NULL;
    tNODE* p_tNode = OS_TaskGetNode(Id);
    if(p_tNode)p_tTask = (tTASK_CTRL_BLOCK*)(p_tNode->p_tElement);

    return p_tTask;
}

/*******************************************************************************
 * Fuction : Task system schedule.
 *******************************************************************************/
void OS_TaskSchedule(void)
{
    
    OS_CoreStartCheck();
    l_tCore.bOSActive = 1;

  
  
    while(l_tCore.bOSActive)
    {
        uint8_t cTaskNum = l_tCore.cTaskNum + 1;    /*Add the idle task*/
        tNODE* p_tTaskNode = &l_tCore.tStartNode;
        CLEAR_WATCHDOG();
        l_tCore.bOSActive = 1;
        
            
        while(cTaskNum)
        {
            tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(p_tTaskNode->p_tElement);

            if(p_tTCB && p_tTCB->pc_tTCB)                                       /*Task is exist*/           
            {
                
                if(p_tTCB->pc_tTCB->p_fTaskService)                             /*Task thread is exist*/
                {   
                    EVENT iEvt; 
                    ENTER_CRITICAL();
                    iEvt = p_tTCB->iEvt;                                        /*Get event*/
                    EXIT_CRITICAL();
                    if(iEvt)
                    {
                        ENTER_CRITICAL();
                        p_tTCB->iEvt &= EVT_CLEAR_MASK;                         /*Clear events whitch are in the task control block*/
                        EXIT_CRITICAL();
                        /*If your app cannot handle the event immediately,please save it to cache*/
                        p_tTCB->pc_tTCB->p_fTaskService(iEvt,p_tTCB->eState);
                    }
                    
                    
                }
                if(0 == p_tTCB->cCoreTimer)
                {   
                    ENTER_CRITICAL();
                    p_tTCB->iEvt |= EVT_CORE_TICK_READY; 
                    EXIT_CRITICAL();
                    p_tTCB->cCoreTimer = p_tTCB->pc_tTCB->cCoreSpill;
                }
                
                if(0 == p_tTCB->iTaskTimer)                                     /*Task delay ready*/
                {
                    ENTER_CRITICAL();                                           
                    p_tTCB->iEvt |= EVT_TASK_TICK_READY;                        /*Send event*/
                    EXIT_CRITICAL();
                    p_tTCB->iTaskTimer = p_tTCB->pc_tTCB->iTaskSpill;           /*Reset the task delay*/
                }
               
            }
            
            if(p_tTaskNode->p_tNext)                                            /*Find next task*/
            {
                p_tTaskNode = p_tTaskNode->p_tNext;                             /*Set next task to run*/
            }
            else 
            {
                break;                                                          /*A run loop is completed,restart a new loop*/
            }

            cTaskNum --;
        }
    }

    
}



/*******************************************************************************
 * Fuction : Create a task.
 *******************************************************************************/
eTASK_ERROR OS_TaskCreate(uint8_t              cTaskID,
                         tTASK_CTRL_BLOCK*    p_tTask,
                         const tTASK_BLOCK*   pc_tTCB,
                         tRING_QUE*           p_tMsgQue,
                         tMSG_BUF*            p_tMsgBuf,
                         uint8_t              cQueLen)
{
    tNODE* p_tTmpNode = NULL;
    tNODE* p_tNode = OS_TaskGetNode(cTaskID);                /*The task is exist?*/
    
    eTASK_ERROR re = TASK_ERR_NONE;
    if((const tTASK_BLOCK*)0 == pc_tTCB) 
    {
        re = TASK_ERR_NO_LINK;                               /*No PTCB link to the task*/
    }
    else if(0 == cTaskID || 0xff ==  cTaskID)
    {
        re = TASK_ERR_ID_ERR;
    }
    else if(NULL == p_tTask)
    {
        re = TASK_ERR_NO_TASK_BLOCK;
    }
    else 
    {

        if(p_tNode)
        {
            p_tNode = NULL;
            re = TASK_ERR_REPEAT_CREAT;                      /*Task is created*/
        }
        else
        {
            p_tNode = &(p_tTask->tNode);
        }

        if(p_tNode)
        {
            /*Task block init*/
            p_tTask->Id = cTaskID;
            p_tTask->pc_tTCB = pc_tTCB;
            p_tTask->p_tMsgQue = p_tMsgQue;
            p_tTask->iEvt = 0;
            p_tTask->iTaskTimer = pc_tTCB->iTaskSpill;
            p_tTask->cCoreTimer = pc_tTCB->cCoreSpill;
            p_tTask->eState = TASK_STATE_READY;

            if(p_tTask->p_tMsgQue)
            {
                p_tTask->p_tMsgQue->cHead = 0;
                p_tTask->p_tMsgQue->cTail = 0;
                p_tTask->p_tMsgQue->p_vBuf = (void*)p_tMsgBuf;
                p_tTask->p_tMsgQue->cMax  = cQueLen;
                p_tTask->p_tMsgQue->eState = QUE_ERR_EMPTY;
            }
            p_tNode->p_tElement = (void*)p_tTask;
            p_tTmpNode = OS_ListGetTail(&(l_tCore.tStartNode));
           
            /*Insert the task to list*/
            if(OS_ListInsert(p_tTmpNode,p_tNode,FALSE))
            {
                l_tCore.cTaskNum ++;
                core_printf(_T("CreateTask:"));
                core_printf(_T(p_tTask->pc_tTCB->p_cName));
                core_printf(_T(" ,ID=%d,ret = %d,NUM = %d\n",cTaskID,re,l_tCore.cTaskNum));
            }
        }
    }
    return re;
}

/*******************************************************************************
 * Fuction : Delete a task
 *******************************************************************************/

void OS_TaskDelete(uint8_t cTaskID)  
{
    tNODE* p_tNode = OS_TaskGetNode(cTaskID);
    if(p_tNode && cTaskID < 0xff)
    {
        tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(p_tNode->p_tElement);

        /*Delet node*/
        if(OS_ListDelete(p_tNode))l_tCore.cTaskNum --;
        
        if(p_tTCB->pc_tTCB->p_fDInit)(void)p_tTCB->pc_tTCB->p_fDInit();                     
        
        API_MemClear((uint8_t *)p_tTCB,sizeof(tTASK_CTRL_BLOCK));

        core_printf(_T("DELET Task:"));
        core_printf(_T(p_tTCB->pc_tTCB->p_cName));
        core_printf(_T(" ,ID=%d\n",cTaskID));
    }
}

/*******************************************************************************
 * Fuction : Get Task list element 
 *******************************************************************************/
tTASK_CTRL_BLOCK* OS_TaskListGetHead(void)
{
    tTASK_CTRL_BLOCK* p_tTemp = NULL;
    if(l_tCore.tStartNode.p_tNext)
    {
        p_tTemp = (tTASK_CTRL_BLOCK*)(l_tCore.tStartNode.p_tNext->p_tElement);
    }
    return p_tTemp;
}

tTASK_CTRL_BLOCK* OS_TaskListGetNext(tTASK_CTRL_BLOCK* p_tTask)
{
    tTASK_CTRL_BLOCK* p_tTemp = NULL;
    if(p_tTask)
    {
        tNODE* p_tNode = OS_TaskGetNode(p_tTask->Id);
        if(p_tNode && p_tNode->p_tNext)
        {
             p_tTemp = (tTASK_CTRL_BLOCK*)(p_tNode->p_tNext->p_tElement);
        }
        
    }
    return p_tTemp;
}



/*******************************************************************************
 * Fuction : Start or Stop a task
 *******************************************************************************/
uint8_t OS_TaskStartDir(tTASK_CTRL_BLOCK* p_tTCB)
{
    uint8_t re = TRUE;
    if(p_tTCB)
    {
        core_printf(_T("Start Task:"));
        core_printf(_T(p_tTCB->pc_tTCB->p_cName));
        
        if(p_tTCB->eState != TASK_STATE_RUNNING)
        {
            eTASK_STATE eState = p_tTCB->eState;
            p_tTCB->eState = TASK_STATE_RUNNING;
            /*Clear Msg*/
            if(p_tTCB->p_tMsgQue)
            {
                ENTER_CRITICAL();
                p_tTCB->p_tMsgQue->eState = QUE_ERR_EMPTY;
                p_tTCB->p_tMsgQue->cHead = p_tTCB->p_tMsgQue->cTail;
                p_tTCB->iEvt &= (~EVT_MSG_READY);
                EXIT_CRITICAL();
            }
            /*Init task*/
            if(p_tTCB->pc_tTCB->p_fInit)
            {
                core_printf(_T(" Run Init_Func,"));
                if(!p_tTCB->pc_tTCB->p_fInit())
                {
                    re = FALSE;
                    p_tTCB->eState = eState;
                    core_printf(_T("Start failue "));
                }
            }

            
        }

        core_printf(_T(" ,ID=%d\n",p_tTCB->Id));
    }
    return re;
}

uint8_t OS_TaskStart(uint8_t cTaskID)
{
    uint8_t re = TRUE;
    tNODE* p_tNode = OS_TaskGetNode(cTaskID);

    if(p_tNode && p_tNode->p_tPrev)
    {
        
        tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(p_tNode->p_tElement);
        re = OS_TaskStartDir(p_tTCB);
        
    }

    return re;
}

uint8_t OS_TaskStopDir(tTASK_CTRL_BLOCK* p_tTCB)
{
    uint8_t re = TRUE;
    if(p_tTCB)
    {
        core_printf(_T("Stop Task:"));
        core_printf(_T(p_tTCB->pc_tTCB->p_cName));
        
        if(p_tTCB->eState != TASK_STATE_STOP)
        {
            eTASK_STATE eState = p_tTCB->eState;
            p_tTCB->eState = TASK_STATE_STOP;
            if(p_tTCB->pc_tTCB->p_fDInit)
            {
                core_printf(_T(" Run DINIT_FUNC "));
                if(!p_tTCB->pc_tTCB->p_fDInit())
                {
                    re = FALSE;
                    p_tTCB->eState = eState;
                    core_printf(_T(" Stop failue "));
                }
            }
        }

        
        core_printf(_T(" ,ID=%d\n",p_tTCB->Id));
    }

    return re;
}


uint8_t OS_TaskStop(uint8_t cTaskID)
{
    uint8_t re = TRUE;
    tNODE* p_tNode = OS_TaskGetNode(cTaskID);
    if(p_tNode && p_tNode->p_tPrev && p_tNode->p_tElement)
    {
        tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(p_tNode->p_tElement);
        re = OS_TaskStopDir(p_tTCB);
    }

    return re;
}

#if 0
uint8_t  OS_TaskEmergDir(tTASK_CTRL_BLOCK* p_tTCB,bool bStopTask)
{
    uint8_t re = TRUE;
    if(p_tTCB)
    {
        core_printf(_T("Task:"));
        core_printf(_T(p_tTCB->pc_tTCB->p_cName));
        
        if(p_tTCB->pc_tTCB->p_fEmerg)
        {
            core_printf(_T(" Run EMERGNCY Hanle "));
            re = p_tTCB->pc_tTCB->p_fEmerg();
        }

        if(p_tTCB->pc_tTCB->p_fDinit)
        {
            core_printf(_T(" and Run Dinit func "));
            re = re && p_tTCB->pc_tTCB->p_fDinit();
        }
        
        core_printf(_T(" ,ID=%d\n",p_tTCB->Id));
    }

    return re;
}


uint8_t  OS_TaskEmergHandle (uint8_t cTaskID,bool bStopTask)
{
    uint8_t re = TRUE;
    tNODE* p_tNode = OS_TaskGetNode(cTaskID);
    if(p_tNode && p_tNode->p_tPrev && p_tNode->p_tElement)
    {
        tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(p_tNode->p_tElement);
        re = OS_TaskEmergDir(p_tTCB, bStopTask);
    }

    return re;
}
#endif

/*******************************************************************************
 * Fuction : Check the task state
 *******************************************************************************/
uint8_t OS_TaskIsActiveDir(tTASK_CTRL_BLOCK* p_tTask)
{
    return (p_tTask 
            && p_tTask->eState == TASK_STATE_RUNNING);
}

eTASK_STATE OS_TaskGetStateDir(tTASK_CTRL_BLOCK* p_tTask)
{
    eTASK_STATE re = TASK_STATE_STOP;
    if(p_tTask)re = p_tTask->eState;
    return re;
}


uint8_t OS_TaskIsActive(uint8_t cTaskID)
{
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);
    return (p_tTask 
            && p_tTask->eState == TASK_STATE_RUNNING);
}

eTASK_STATE OS_TaskGetState(uint8_t cTaskID)
{
    eTASK_STATE re = TASK_STATE_STOP;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);
    if(p_tTask)re = p_tTask->eState;
    return re;
}




/*******************************************************************************
 * System massage fuction block
 *******************************************************************************/

eQUE_ERROR OS_InsertMsgDir (tTASK_CTRL_BLOCK* p_tTask, MSG_ID Id,uint16_t iSid,void* p_vBuf,bool bHead)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(p_tTask)
    {
        tMSG_BUF tMsgBuf ;
        tMsgBuf.Id = Id;
        tMsgBuf.iSid = iSid;
        tMsgBuf.uData.p_cData = p_vBuf;


        re = OS_InsertQueElement(p_tTask->p_tMsgQue, bHead,(void*)&tMsgBuf,sizeof(tMSG_BUF));
        if(re == QUE_ERR_NONE)
        {
            ENTER_CRITICAL();
            p_tTask->iEvt |=(EVT_MSG_READY);
            EXIT_CRITICAL();
        }
    }
    return re;
}

eQUE_ERROR OS_InsertMsg (uint8_t cTaskID, MSG_ID Id,uint16_t iSid,void* p_vBuf,bool bHead)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);

    re = OS_InsertMsgDir(p_tTask,Id,iSid,p_vBuf,bHead);
    return re;
}

eQUE_ERROR OS_PostMsgDir (tTASK_CTRL_BLOCK* p_tTask, MSG_ID Id,uint16_t iSid,void* p_vBuf)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(p_tTask)
    {
        tMSG_BUF tMsgBuf ;
        tMsgBuf.Id = Id;
        tMsgBuf.iSid = iSid;
        tMsgBuf.uData.p_cData = p_vBuf;


        re = OS_PostQueElement(p_tTask->p_tMsgQue,(void*)&tMsgBuf,sizeof(tMSG_BUF));
        if(re == QUE_ERR_NONE)
        {
            ENTER_CRITICAL();
            p_tTask->iEvt |=(EVT_MSG_READY);
            EXIT_CRITICAL();
        }
    }
    return re;
}

eQUE_ERROR OS_PostMsg (uint8_t cTaskID, MSG_ID Id,uint16_t iSid,void* p_vBuf)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);
    
    re = OS_PostMsgDir(p_tTask,Id,iSid,p_vBuf);
    return re;
}


eQUE_ERROR OS_PostFullMsgDir (tTASK_CTRL_BLOCK* p_tTask, MSG_ID Id,uint16_t iSid,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(p_tTask)
    {
        tMSG_BUF tMsgBuf ;
        tMsgBuf.Id = Id;
        tMsgBuf.iSid = iSid;
        tMsgBuf.uData.a_cData[0] = d0;
        tMsgBuf.uData.a_cData[1] = d1;
        tMsgBuf.uData.a_cData[2] = d2;
        tMsgBuf.uData.a_cData[3] = d3;


        re = OS_PostQueElement(p_tTask->p_tMsgQue,(void*)&tMsgBuf,sizeof(tMSG_BUF));
        if(re == QUE_ERR_NONE)
        {
            ENTER_CRITICAL();
            p_tTask->iEvt |=(EVT_MSG_READY);
            EXIT_CRITICAL();
        }
    }
    return re;
}


eQUE_ERROR OS_PostFullMsg (uint8_t cTaskID, MSG_ID Id,uint16_t iSid,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3)
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);

    re = OS_PostFullMsgDir(p_tTask,Id,iSid,d0,d1,d2,d3);
    return re;
}

eQUE_ERROR OS_GetMsgDir (tTASK_CTRL_BLOCK* p_tTask,tMSG_BUF* p_tBuf )
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    if(p_tTask)
    {
        re = OS_GetQueElement(p_tTask->p_tMsgQue,(void*)p_tBuf,sizeof(tMSG_BUF));
        if( QUE_ERR_EMPTY == p_tTask->p_tMsgQue->eState )
        {
            ENTER_CRITICAL();
            p_tTask->iEvt &=(~(EVT_MSG_READY));
            EXIT_CRITICAL();
        }
    }
    return re;
}

eQUE_ERROR OS_GetMsg (uint8_t cTaskID,tMSG_BUF* p_tBuf )
{
    eQUE_ERROR re = QUE_ERR_NOQUE;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);

    re = OS_GetMsgDir(p_tTask,p_tBuf);
    return re;
}

void OS_ClrAllMsgDir(tTASK_CTRL_BLOCK* p_tTask)
{
    if(p_tTask && p_tTask->p_tMsgQue)
    {
        ENTER_CRITICAL();
        p_tTask->p_tMsgQue->cHead = p_tTask->p_tMsgQue->cTail;
        p_tTask->p_tMsgQue->eState = QUE_ERR_EMPTY;
        p_tTask->iEvt &= (~EVT_MSG_READY);
        EXIT_CRITICAL();
        
    }
}


void OS_ClrAllMsg(uint8_t cTaskID)
{
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);
    OS_ClrAllMsgDir(p_tTask);
}



/*******************************************************************************
 * System event fuction block
 *******************************************************************************/

void OS_PostEventMass(EVENT iEvt) 
{
    tNODE* p_tTaskNode = &l_tCore.tStartNode;
    if(!(EVT_LOCK_MASK & iEvt))
    {
        while(p_tTaskNode->p_tNext)                                          
        {
            tTASK_CTRL_BLOCK* p_tTCB = (tTASK_CTRL_BLOCK*)(p_tTaskNode->p_tElement);
            ENTER_CRITICAL();
            p_tTaskNode = p_tTaskNode->p_tNext; 
            p_tTCB->iEvt |= iEvt;
            EXIT_CRITICAL();
        }
    }
}

uint8_t OS_PostEventDir(tTASK_CTRL_BLOCK* p_tTask,EVENT iEvt)
{
    uint8_t re = FALSE;
    if (iEvt && p_tTask)
    {
        if(!(EVT_LOCK_MASK & iEvt))                                             /*You can't opreat the system event*/
        {
            ENTER_CRITICAL();
            p_tTask->iEvt |= iEvt;
            EXIT_CRITICAL();
            re = TRUE;
        }
    }

    return re;
}

uint8_t OS_PostEvent(uint8_t cTaskID,EVENT iEvt)
{
    uint8_t re = FALSE;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);
    re = OS_PostEventDir(p_tTask,iEvt);

    return re;
}


EVENT OS_GetEventDir(tTASK_CTRL_BLOCK* p_tTask)
{
    EVENT re_evt = 0;
    if(p_tTask)
    {
        ENTER_CRITICAL();
        re_evt = p_tTask->iEvt;
        EXIT_CRITICAL();
    }
    return re_evt;
}

EVENT OS_GetEvent(uint8_t cTaskID)
{
    EVENT re_evt = 0;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);
    re_evt = OS_GetEventDir(p_tTask);
    return re_evt;
}

uint8_t OS_ClearEventDir(tTASK_CTRL_BLOCK* p_tTask, EVENT iEvt)
{
    uint8_t re = FALSE;
    if (iEvt && p_tTask)
    {
        ENTER_CRITICAL();
        p_tTask->iEvt &= (~iEvt);
        EXIT_CRITICAL();
        re = TRUE;
    }

    return re;
}

uint8_t OS_ClearEvent(uint8_t cTaskID, EVENT iEvt)
{
    uint8_t re = FALSE;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);
    re = OS_ClearEventDir(p_tTask,iEvt);

    return re;
}


uint8_t OS_ClearAllEventDir(tTASK_CTRL_BLOCK* p_tTask)
{
    uint8_t re = FALSE;
    if (p_tTask)
    {
        ENTER_CRITICAL();
        p_tTask->iEvt = 0;
        EXIT_CRITICAL();
        re = TRUE;
    }

    return re;
}

uint8_t OS_ClearAllEvent(uint8_t cTaskID)
{
    uint8_t re = FALSE;
    tTASK_CTRL_BLOCK* p_tTask = OS_TaskGetBlock(cTaskID);
    re = OS_ClearAllEventDir(p_tTask);

    return re;
}


/***end***/

