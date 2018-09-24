#define _EEP_C_
#include "..\config\inc.h"


typedef enum{
    EEP_DEV_START,
    EEP_DEV_CHECK_DEV,
    EEP_DEV_WAIT_CHK,
    EEP_DEV_CHECK_NODEV,
    EEP_DEV_CHECK_BLOCK,
    
    EEP_DEV_LOAD,
    EEP_DEV_WAIT_LOAD,
    EEP_DEV_CHECK_LOAD,
    
    EEP_DEV_IDLE,
    
    EEP_DEV_READ,
    EEP_DEV_WAIT_READ,
    EEP_DEV_CHECK_RPAGE,
    

    EEP_DEV_WRITE,
    EEP_DEV_WAIT_WRITE,
    EEP_DEV_CHECK_WPAGE,
    EEP_DEV_CHECK_WBLOCK,

    EEP_DEV_LOAD_FACTORY,
    
    EEP_DEV_LF_WRITE,
    EEP_DEV_LF_WAIT_WRITE,
    EEP_DEV_LF_CHECK_WPAGE,
    EEP_DEV_LF_CHECK_WBLOCK,
    
    EEP_DEV_N
}eEEP_DEV_STATE;



#pragma pack(1)
typedef struct{
    uint8_t cDevAddr;
    uint8_t cSubAddr;
    uint8_t* p_cBuf;
    uint16_t iTotalLen;
    uint8_t* p_cRet;
    
}tEEP_CMD;

#pragma pack(1)
typedef struct{

    uint8_t cI2CBusState;
    tNODE* p_tCurrNode;
    eEEP_DEV_STATE eDevState;
    tEEP_CMD  tCmdBuf;

    uint16_t   iTimer;
    uint8_t   cDlyTimer;
    

    uint8_t cPageIdx;
    uint8_t cPageCnt;
    uint8_t cLastLen;

    uint8_t cZoneIdx;
    uint8_t cZoneEnd;

    tEEP_CMD  tTempCmd;
}tEEP_CTRL_BLOCK;

tNODE    l_tEepBlockStartNode; /*This param will be init by the clear ram code in boot block*/
tEEP_CTRL_BLOCK l_tEepCB;
uint8_t  l_tEEPWriteBuf[D_MAX_BUFF_LEN];  /*Only map a zone of a eeprom to save ram,don't map the whole one!! */

/*If the new block ADDR is valid , return FALSE*/
bool EEP_BlockAddrIsErr(const tEEP_DATA* p_tData)
{
    bool re = FALSE;
    tNODE* p_tNode = &l_tEepBlockStartNode;
    uint16_t  bTagEndAddr = p_tData->iStartAddr + p_tData->iLen - 1;
    eep_printf(_T("New bclock:star:%ix,end:%ix,ID:%d\n",p_tData->iStartAddr,bTagEndAddr,p_tData->cID));
    while(p_tNode->p_tNext)
    {
        tEEP_DATA_BLOCK* p_tTmpEepBlock = (tEEP_DATA_BLOCK*)(p_tNode->p_tNext->p_tElement);
        if(p_tTmpEepBlock)
        {
            bool temp = TRUE;
            uint16_t bTmpEndAddr = p_tTmpEepBlock->p_tData->iStartAddr + p_tTmpEepBlock->p_tData->iLen - 1;
            if(( p_tData->iStartAddr > bTmpEndAddr 
                 || bTagEndAddr < p_tTmpEepBlock->p_tData->iStartAddr)
               && p_tData->cID != p_tTmpEepBlock->p_tData->cID)
               
            {
                temp = FALSE;
                
            }

            re |= temp;
            if(re)
            {
                eep_printf(_T("block:%lx,star:%ix,end:%ix,ID:%d \n",(uint32_t)p_tTmpEepBlock,
                                                                    p_tTmpEepBlock->p_tData->iStartAddr,
                                                                    bTmpEndAddr,p_tTmpEepBlock->p_tData->cID));
                break;
            }
        }

        p_tNode = p_tNode->p_tNext;
    }

    return re;
}

eEEP_DATA_STATE EEP_CreateEepDataBlock(tEEP_DATA_BLOCK* p_tEepBlock,const tEEP_DATA* p_tData)
{
    eEEP_DATA_STATE re = EEP_DATA_NOBLOCK;
    
    
    if(p_tEepBlock && p_tData && p_tData->iLen)
    {
        uint16_t iTmpStartAddr = p_tData->iStartAddr;
        uint16_t iTmpEndtAddr = p_tData->iStartAddr + p_tData->iLen - 1;

        if(iTmpStartAddr&0x000F)re = EEP_DATA_ADDR_ERR;   /*addr must be N multiple of 16*/
        else if(iTmpStartAddr + p_tData->iLen > D_EEP_MAX_NUM)re = EEP_DATA_OVF;
        else if(EEP_BlockAddrIsErr(p_tData))re = EEP_DATA_ADDR_ERR;
        else
        {   
                            
            uint8_t cZoneIdx;
            uint8_t* p_tZoneBuf = p_tData->p_cBuf;
            uint16_t cZoneOffset = 0;
            tNODE* p_tNode =  &(l_tEepBlockStartNode);
            
            while(p_tNode->p_tNext) p_tNode = p_tNode->p_tNext;

            API_MemClear((uint8_t*)p_tEepBlock,sizeof(tEEP_DATA_BLOCK));

            p_tNode->p_tNext = &(p_tEepBlock->tBlockNode);
            p_tEepBlock->tBlockNode.p_tElement = (void*)p_tEepBlock;
            p_tEepBlock->cZoneStart = iTmpStartAddr>>8; 
            p_tEepBlock->cZoneEnd = iTmpEndtAddr>>8;
            p_tEepBlock->p_tData = p_tData;
            
            for(cZoneIdx = p_tEepBlock->cZoneStart;cZoneIdx <= p_tEepBlock->cZoneEnd;cZoneIdx++)
            {
                
                uint16_t iZoneEndAddr = 256*cZoneIdx + 255;
                uint16_t iZoneLen;
                if(iTmpEndtAddr > iZoneEndAddr)
                {
                    iZoneLen = iZoneEndAddr - iTmpStartAddr + 1;
                    p_tEepBlock->iZoneAddr[cZoneIdx] = iTmpStartAddr;
                    p_tEepBlock->iZoneLen[cZoneIdx] = iZoneLen;
                    p_tEepBlock->p_tZoneBuf[cZoneIdx] = p_tZoneBuf;
                    iTmpStartAddr = iZoneEndAddr + 1;
                    cZoneOffset = iZoneLen;
                    p_tZoneBuf = &p_tZoneBuf[cZoneOffset];
                }
                else 
                {
                    iZoneLen = iTmpEndtAddr - iTmpStartAddr + 1;
                    p_tEepBlock->iZoneAddr[cZoneIdx] = iTmpStartAddr;
                    p_tEepBlock->iZoneLen[cZoneIdx] = iZoneLen;
                    p_tEepBlock->p_tZoneBuf[cZoneIdx] = p_tZoneBuf;
                    break;
                }
            }
    
                
            
            re = EEP_DATA_NOERR;
        }
    }
    return re;
}

void EEP_CreateBlockChkSum(tEEP_DATA_BLOCK* p_tEepBlock)
{
    if(p_tEepBlock && p_tEepBlock->p_tData)
    {
        uint8_t* p_cBuf = p_tEepBlock->p_tData->p_cBuf;
        uint16_t iLen = p_tEepBlock->p_tData->iLen - sizeof(uint16_t);
        uint16_t* p_tChkSum = (uint16_t*)&(p_cBuf[iLen]);
        

        OS_CreateRamChkBlock((void*)p_cBuf,iLen,p_tChkSum);
        
    }
}




void EEP_CopyWriteZoneBuf(tEEP_DATA_BLOCK* p_tEepBlock)
{
    uint16_t iTotalLen = p_tEepBlock->p_tData->iLen;
    API_MemCopy(p_tEepBlock->p_tData->p_cBuf,l_tEEPWriteBuf,iTotalLen);
}


bool EEP_BlockCheck(tEEP_DATA_BLOCK* p_tEepBlock)
{
    uint8_t re = FALSE;
    if(p_tEepBlock && p_tEepBlock->p_tData)
    {
        uint8_t* p_cBuf = p_tEepBlock->p_tData->p_cBuf;
        const tEEP_DATA_RANG* p_tDefData = p_tEepBlock->p_tData->p_tDefData;
        uint16_t iLen = p_tEepBlock->p_tData->iLen - sizeof(uint16_t);
        uint16_t* p_tChkSum = (uint16_t*)&(p_cBuf[iLen]);
        uint16_t i;

        re = TRUE;
        if(p_tDefData)
        {
            for(i = 0;i < iLen ;i ++)
            {
                if(p_cBuf[i] < p_tDefData[i].cMin || p_cBuf[i] > p_tDefData[i].cMax)
                {
                    re = FALSE;
                }
            }
        }

        if(re)
        {
            re = FALSE;
            if(OS_RamCheck((void*)p_cBuf,iLen,p_tChkSum))
            {
                re = TRUE;
            }
        }

    }
    
    return re;
}

void EEP_BlockLoadDefault(tEEP_DATA_BLOCK* p_tEepBlock)
{
    if(p_tEepBlock && p_tEepBlock->p_tData)
    {
        uint8_t* p_cBuf = p_tEepBlock->p_tData->p_cBuf;
        const tEEP_DATA_RANG* p_tDefData = p_tEepBlock->p_tData->p_tDefData;
        uint16_t iLen = p_tEepBlock->p_tData->iLen - sizeof(uint16_t);
        uint16_t* p_tChkSum = (uint16_t*)&(p_cBuf[iLen]);
        uint16_t i;
        if(p_tDefData)
        {
            for(i = 0;i < iLen ;i ++)
            {
                p_cBuf[i] = p_tDefData[i].cDef;
            }
        }
        eep_printf(_T("Block load default data and you will save it\n"));
        OS_CreateRamChkBlock((void*)p_cBuf,iLen,p_tChkSum);
        
    }
}


bool EEP_BlockEdit(tEEP_DATA_BLOCK* p_tEepBlock,uint16_t iOffSet,uint8_t cValue)
{
    uint8_t re = FALSE;
    if(p_tEepBlock && p_tEepBlock->p_tData)
    {
        uint8_t* p_cBuf = p_tEepBlock->p_tData->p_cBuf;
        const tEEP_DATA_RANG* p_tDefData = p_tEepBlock->p_tData->p_tDefData;
        uint16_t iLen = p_tEepBlock->p_tData->iLen - sizeof(uint16_t);
        uint16_t* p_tChkSum = (uint16_t*)&(p_cBuf[iLen]);

        
        if(cValue < p_tDefData[iOffSet].cMin 
           && cValue > p_tDefData[iOffSet].cMax)
        {
            cValue = p_tDefData[iOffSet].cDef;
        }

        if(cValue != p_cBuf[iOffSet])
        {
            p_cBuf[iOffSet] = cValue;
            OS_CreateRamChkBlock((void*)p_cBuf,iLen,p_tChkSum);
            re = TRUE;
            eep_printf(_T("Block data is seted , plase save it\n"));
        }
    }

    return re;
}



void EEP_ReadBlock(tEEP_DATA_BLOCK* p_tEepBlock)
{

    switch(l_tEepCB.eDevState)
    {
        
        case EEP_DEV_READ:
        case EEP_DEV_LOAD:
             p_tEepBlock->tFlag.bReading  = TRUE;
             l_tEepCB.tCmdBuf.cDevAddr = D_EEP_DEV_ADDR|(((p_tEepBlock->iZoneAddr[p_tEepBlock->cZoneStart]&D_EEP_ADDR_MASK)>>8)<<1);
             l_tEepCB.tCmdBuf.cSubAddr = (uint8_t)p_tEepBlock->iZoneAddr[p_tEepBlock->cZoneStart];
             l_tEepCB.tCmdBuf.iTotalLen = p_tEepBlock->iZoneLen[p_tEepBlock->cZoneStart];
             l_tEepCB.tCmdBuf.p_cBuf = p_tEepBlock->p_tZoneBuf[p_tEepBlock->cZoneStart];
             l_tEepCB.tCmdBuf.p_cRet = &l_tEepCB.cI2CBusState;

             if(I2C_ReadFromSubAdd(I2C2,l_tEepCB.tCmdBuf.cDevAddr,l_tEepCB.tCmdBuf.cSubAddr
                                    ,TRUE,l_tEepCB.tCmdBuf.p_cBuf,l_tEepCB.tCmdBuf.iTotalLen
                                    ,FALSE,(void*)&(l_tEepCB.cI2CBusState),I2C_96KBPS))
             {
                 l_tEepCB.eDevState ++;
                 eep_printf(_T("II2 Option ok,wait read 0x%lx!\n",(uint32_t)p_tEepBlock));
             }

        break;
        
        case EEP_DEV_WAIT_READ:
        case EEP_DEV_WAIT_LOAD:
             if(I2C_RET_SUCCESS == l_tEepCB.cI2CBusState)
             {
                 eep_printf(_T("Read block OK,Data:"));
                 
#if D_DEBUG_EEP && D_PRINT_EN
                 {
                     uint8_t i = 0;
                     for(i = 0;i< l_tEepCB.tCmdBuf.iTotalLen;i++)
                     {
                         eep_printf(_T(" 0x%x",l_tEepCB.tCmdBuf.p_cBuf[i]));
                     }
                 }
                 eep_printf(_T("\n"));
#endif
                 /*Check Block*/
                 if(p_tEepBlock->cZoneStart < p_tEepBlock->cZoneEnd)
                 {
                     p_tEepBlock->cZoneStart ++;
                     l_tEepCB.eDevState --;
                     eep_printf(_T("Read block a next addr range\n"));
                 }
                 else
                 {
                     l_tEepCB.eDevState ++;
                     eep_printf(_T("Read block commplete\n"));
                     
                     p_tEepBlock->tFlag.bReading = FALSE;
                     p_tEepBlock->eUsrRet = EEP_OPTION_READ_COMPLETE;
                     _SendMsgToHMI(MS_EEP_READ_RET,EEP_OPTION_READ_COMPLETE,p_tEepBlock);
                 }
	         if(D_EEP_SYSDATA_ID==p_tEepBlock->p_tData->cID)
	         {
		  	g_BKHandLevel=g_tSysRomData.tScrBlock.cBaseBR;	
			sAudioDat.sBasic.Type=g_tSysRomData.tAudioBlock.Type;
			sAudioDat.sBasic.sBass.Gain=g_tSysRomData.tAudioBlock.BassGain;
			sAudioDat.sBasic.sMid.Gain=g_tSysRomData.tAudioBlock.MidGain;
			sAudioDat.sBasic.sTreble.Gain = g_tSysRomData.tAudioBlock.TrebleGain;

			
			sAudioDat.sBasic.Fader = g_tSysRomData.tAudioBlock.Fader;
			sAudio.Fader_Media = sAudioDat.sBasic.Fader;
    			
			sAudioDat.sBasic.Balance = g_tSysRomData.tAudioBlock.Balance;
			sAudio.Balance_media = sAudioDat.sBasic.Balance;
			
			sAudioDat.sBasicBK.DefaultMediaVolume =  g_tSysRomData.tAudioBlock.SysVol;
			sAudioKeep.SysVol =  g_tSysRomData.tAudioBlock.SysVol;

			sAudioDat.sBasicBK.DefaultNaviVol = g_tSysRomData.tAudioBlock.NaviVol;
			sAudioKeep.NaviVol=g_tSysRomData.tAudioBlock.NaviVol;

			 
			sAudioDat.sBasicBK.DefaultPhoneVol = g_tSysRomData.tAudioBlock.BtVol;
			sAudioKeep.BtVol = g_tSysRomData.tAudioBlock.BtVol;

			sAudioDat.sBasicBK.DefaultPromptVol = g_tSysRomData.tAudioBlock.AppVol;
			sAudioKeep.AppVol = sAudioDat.sBasicBK.DefaultPromptVol;
	         }
             }
             else
             {
                 if(I2C_RET_TIMEOUT == l_tEepCB.cI2CBusState
                     || I2C_RET_ERR == l_tEepCB.cI2CBusState)
                 {
                     l_tEepCB.eDevState ++;
                     p_tEepBlock->tFlag.bReading = FALSE;
                     p_tEepBlock->eUsrRet = EEP_OPTION_IICERR;
                     _SendMsgToHMI(MS_EEP_READ_RET,EEP_OPTION_IICERR,p_tEepBlock);
                     eep_printf(_T("II2 Err when Read page\n"));
                 }
             }
        break;
        
        case EEP_DEV_CHECK_RPAGE:
            l_tEepCB.eDevState = EEP_DEV_IDLE;
        break;

        case EEP_DEV_CHECK_LOAD:
            if(!EEP_BlockCheck(p_tEepBlock))       /*Need to Save data*/
            {
                EEP_BlockLoadDefault(p_tEepBlock);
                EEP_CreateBlockChkSum(p_tEepBlock);
                EEP_WriteStart(p_tEepBlock,D_EEP_WAIT_WRITE_TIME);
                
                eep_printf(_T("Readed data is overflow,auto fix it and write it \n"));
            }
            l_tEepCB.eDevState = EEP_DEV_CHECK_BLOCK;
        break;
  
    }    
                
     
}



void EEP_WriteBlock(tEEP_DATA_BLOCK* p_tEepBlock)
{

    switch(l_tEepCB.eDevState)
    {
        case EEP_DEV_WRITE:
        case EEP_DEV_LF_WRITE:
             p_tEepBlock->tFlag.bWriting  = TRUE;
             l_tEepCB.tCmdBuf.cDevAddr = D_EEP_DEV_ADDR|(((p_tEepBlock->iZoneAddr[p_tEepBlock->cZoneStart]&D_EEP_ADDR_MASK)>>8)<<1);
             l_tEepCB.tCmdBuf.cSubAddr = (uint8_t)p_tEepBlock->iZoneAddr[p_tEepBlock->cZoneStart];
             l_tEepCB.tCmdBuf.iTotalLen = p_tEepBlock->iZoneLen[p_tEepBlock->cZoneStart];
             //l_tEepCB.tCmdBuf.p_cBuf = p_tEepBlock->p_tZoneBuf[p_tEepBlock->cZoneStart];
             
             l_tEepCB.tCmdBuf.p_cRet = &l_tEepCB.cI2CBusState;
             {
                 uint8_t cWriteLen = D_EEP_PAGE_LEN;
                 l_tEepCB.cLastLen = l_tEepCB.tCmdBuf.iTotalLen%D_EEP_PAGE_LEN ;
                 l_tEepCB.cPageCnt = l_tEepCB.tCmdBuf.iTotalLen/D_EEP_PAGE_LEN;
                 if(l_tEepCB.cLastLen)l_tEepCB.cPageCnt ++;
                 if(l_tEepCB.cPageCnt == 1 && l_tEepCB.cLastLen)cWriteLen = l_tEepCB.cLastLen;
    
                 if(I2C_WriteToSubAdd(I2C2,l_tEepCB.tCmdBuf.cDevAddr,l_tEepCB.tCmdBuf.cSubAddr
                                    ,TRUE,l_tEepCB.tCmdBuf.p_cBuf,cWriteLen
                                    ,FALSE,(void*)&(l_tEepCB.cI2CBusState),I2C_96KBPS)
                 )
                 {
                     l_tEepCB.eDevState ++;
 #if D_DEBUG_EEP && D_PRINT_EN
                     eep_printf(_T("111Write block DATA to 0x%x-0x%x:\n",l_tEepCB.tCmdBuf.cDevAddr,l_tEepCB.tCmdBuf.cSubAddr));
                     {
                         uint8_t i = 0;
                         for(i = 0;i< cWriteLen;i++)
                         {
                             eep_printf(_T(" 0x%x",l_tEepCB.tCmdBuf.p_cBuf[i]));
                         }
                     }
                     eep_printf(_T("--OK\n"));
#endif
                     eep_printf(_T("II2 Option OK.Wait write: 0x%lx\n",p_tEepBlock));
                 }
    
            }
    
        break;
        
        case EEP_DEV_WAIT_WRITE:
        case EEP_DEV_LF_WAIT_WRITE:
             if(I2C_RET_SUCCESS == l_tEepCB.cI2CBusState)
             {
                 eep_printf(_T("Write one page data,scan next page\n"));
                 l_tEepCB.eDevState ++;
                 l_tEepCB.cPageCnt --;
                 l_tEepCB.cPageIdx ++;
                 l_tEepCB.cDlyTimer = 0; 
             }
             else
             {
                 if(I2C_RET_TIMEOUT == l_tEepCB.cI2CBusState
                     || I2C_RET_ERR == l_tEepCB.cI2CBusState)
                 {
                 
                     if(EEP_DEV_LF_CHECK_WBLOCK == l_tEepCB.eDevState)
                     {
                        l_tEepCB.eDevState = EEP_DEV_LOAD_FACTORY;
                        l_tEepCB.p_tCurrNode = l_tEepCB.p_tCurrNode->p_tNext;
                     }
                     else 
                     {
                         l_tEepCB.eDevState = EEP_DEV_IDLE;
                     }
                     
                     p_tEepBlock->tFlag.bWriting = FALSE;
                     p_tEepBlock->eUsrRet = EEP_OPTION_IICERR;
                     _SendMsgToHMI(MS_EEP_WRITE_RET,EEP_OPTION_IICERR,p_tEepBlock);
                     eep_printf(_T("II2 err when write page(P%d)\n",l_tEepCB.cPageIdx));
                 }
             }
        break;
        case EEP_DEV_CHECK_WPAGE:
        case EEP_DEV_LF_CHECK_WPAGE:    
            if(l_tEepCB.cPageCnt)
            {
                if(l_tEepCB.cDlyTimer ++ > D_EEP_PAGE_WRITE_DELAY);
                {
                    uint8_t cWriteLen = D_EEP_PAGE_LEN;
                    uint16_t iOffset = l_tEepCB.cPageIdx*D_EEP_PAGE_LEN;
                    if(l_tEepCB.cPageCnt == 1 && l_tEepCB.cLastLen)cWriteLen = l_tEepCB.cLastLen;
                   
    
                    if(I2C_WriteToSubAdd(I2C2,l_tEepCB.tCmdBuf.cDevAddr
                                       ,((uint8_t)iOffset + l_tEepCB.tCmdBuf.cSubAddr)
                                       ,TRUE,&(l_tEepCB.tCmdBuf.p_cBuf[iOffset]),cWriteLen
                                       ,FALSE,(void*)&(l_tEepCB.cI2CBusState),I2C_96KBPS)
                    )
                    {
#if D_DEBUG_EEP && D_PRINT_EN
                        eep_printf(_T("2Write block DATA to 0x%x-0x%x:\n",l_tEepCB.tCmdBuf.cDevAddr,((uint8_t)iOffset + l_tEepCB.tCmdBuf.cSubAddr)));
                        {
                            uint8_t i = 0;
                            for(i = 0;i< cWriteLen;i++)
                            {
                                eep_printf(_T(" 0x%x",l_tEepCB.tCmdBuf.p_cBuf[i+iOffset]));
                            }
                        }
                        eep_printf(_T("offset 0x%x--OK\n",iOffset));
#endif
                        l_tEepCB.eDevState --;
                        eep_printf(_T("Delay time to write next paga data\n"));
                    }
                  
                }
                 
            }
            else 
            {
                l_tEepCB.eDevState ++;
                eep_printf(_T("Write page(P%d) end,Check next add range eara\n",l_tEepCB.cPageIdx));
            }
        break;
    
        case EEP_DEV_CHECK_WBLOCK:
        case EEP_DEV_LF_CHECK_WBLOCK:

             if(p_tEepBlock->cZoneStart < p_tEepBlock->cZoneEnd)
             {
                 l_tEepCB.tCmdBuf.p_cBuf = &l_tEEPWriteBuf[p_tEepBlock->iZoneLen[p_tEepBlock->cZoneStart]];
                 p_tEepBlock->cZoneStart ++;
                 l_tEepCB.eDevState -= (EEP_DEV_CHECK_WBLOCK - EEP_DEV_WRITE);
                 l_tEepCB.cPageIdx = 0;
                 eep_printf(_T("-------Scan next addr zone\n"));
             }
             else
             {
                 
                 if(EEP_DEV_LF_CHECK_WBLOCK == l_tEepCB.eDevState)
                 {
                     l_tEepCB.eDevState = EEP_DEV_LOAD_FACTORY;
                     l_tEepCB.p_tCurrNode = l_tEepCB.p_tCurrNode->p_tNext;
                 }
                 else
                 {
                     l_tEepCB.eDevState = EEP_DEV_IDLE;
                 }
                 
                 p_tEepBlock->eUsrRet = EEP_OPTION_WRITE_COMPLETE;
                 p_tEepBlock->tFlag.bWriting = FALSE;
                 _SendMsgToHMI(MS_EEP_WRITE_RET,EEP_OPTION_WRITE_COMPLETE,p_tEepBlock);
                 eep_printf(_T("Write block commplete\n"));
             }
        break;
    
    }   
            
}


bool EEP_ReadStart(tEEP_DATA_BLOCK* p_tEepBlock)
{
    bool re = TRUE;
    if(p_tEepBlock)
    {
        p_tEepBlock->tFlag.bReadReq = TRUE;
        p_tEepBlock->eUsrRet = EEP_OPTION_WAIT;
        re = TRUE;
    }

    return re;
}


bool EEP_WriteStart(tEEP_DATA_BLOCK* p_tEepBlock,uint16_t iDelayTime)
{
    bool re = TRUE;
    if(p_tEepBlock)
    {
        re = FALSE;
        if(EEP_BlockCheck(p_tEepBlock))
        {
            p_tEepBlock->tFlag.bWriteReq = TRUE;
            p_tEepBlock->eUsrRet = EEP_OPTION_WAIT;
            p_tEepBlock->iWaitTimer = iDelayTime;
            re = TRUE;
        }
    }

    return re;
}

eEEP_OPTION_RET EEP_WaitOptionReturn(tEEP_DATA_BLOCK* p_tEepBlock,uint16_t iOvfTime)
{
    
    eEEP_OPTION_RET re = EEP_OPTION_NOBLOCK;
    if(p_tEepBlock && p_tEepBlock->p_tData)
    {
        re = p_tEepBlock->eUsrRet;
        if(p_tEepBlock->iOvfTimer ++ > iOvfTime)
        {
            re = EEP_OPTION_TIMEOUT;
        }
    }

    return re;
}



uint8_t EEP_Init(void)
{
    API_MemClear((uint8_t*)&l_tEepCB, sizeof(tEEP_CTRL_BLOCK));
    _SendMsgToHMI(MS_SYS_DEV_STATE,DEV_IDX_EEPROM,OP_DEV_STATE_OFF);
    return TRUE;
}



eEEPROM_ERROR EEP_Write(uint16_t iAddr,uint8_t* p_cBuf,uint16_t iLen,uint8_t* p_cRet)
{
    uint8_t re = EEP_ERR_NONE;
    
    return re;
}

eEEPROM_ERROR EEP_Read(uint16_t iAddr,uint8_t* p_cBuf,uint16_t iLen,uint8_t* p_cRet)
{
    uint8_t re = EEP_ERR_NONE;
    

    return re;
}


void EEP_Proc(void)
{
    switch(l_tEepCB.eDevState)
    {
        case EEP_DEV_START:
            if(OS_TaskIsActive(TASK_ID_I2C2))
            {
                l_tEepCB.eDevState++;
            }
            else if(l_tEepCB.iTimer++ > _set_timing_xms_base_eep_tick(50))
            {
                uint8_t re = OS_TaskStart(TASK_ID_I2C2);
                l_tEepCB.eDevState += re;
                l_tEepCB.iTimer = 0;
                l_tEepCB.cDlyTimer = 0;
            }
        break;
        case EEP_DEV_CHECK_DEV:
            I2C_CheckDevice(I2C2,D_EEP_DEV_ADDR,FALSE,(void*)&(l_tEepCB.cI2CBusState),I2C_96KBPS);
            l_tEepCB.iTimer = 0;
            l_tEepCB.eDevState++;
        break;
        case EEP_DEV_WAIT_CHK:
            if(I2C_RET_SUCCESS == l_tEepCB.cI2CBusState)
            {
                l_tEepCB.eDevState = EEP_DEV_CHECK_BLOCK;
                l_tEepCB.cI2CBusState = 0;
                l_tEepCB.iTimer = 0;
                l_tEepCB.p_tCurrNode = l_tEepBlockStartNode.p_tNext;
		  eep_printf(_T("EEP start check block\n"));
                
            }
            else if(l_tEepCB.iTimer++ > _set_timing_xms_base_eep_tick(100) )
            {
                eep_printf(_T("Cant find eep,check hw!!\n"));
                l_tEepCB.eDevState = EEP_DEV_CHECK_DEV;
                if(l_tEepCB.cDlyTimer ++ > 10)
                {
                    l_tEepCB.iTimer = 0;
                    l_tEepCB.eDevState = EEP_DEV_CHECK_NODEV;
                    _SendFullMsgToHMI(MS_SYS_DEV_STATE,DEV_IDX_EEPROM,OP_DEV_STATE_ERR,0,0,0);
                }
            }
        break;
        
        case EEP_DEV_CHECK_BLOCK:
            if(l_tEepCB.p_tCurrNode)
            {
                tEEP_DATA_BLOCK* p_tCurrBlcok= (tEEP_DATA_BLOCK*)(l_tEepCB.p_tCurrNode->p_tElement);
                if(p_tCurrBlcok)
                {
                    if(!EEP_BlockCheck(p_tCurrBlcok))
                    {
                        l_tEepCB.cI2CBusState = I2C_RET_IDLE;
                        l_tEepCB.eDevState = EEP_DEV_LOAD;
                        l_tEepCB.cPageCnt = 0;
                        l_tEepCB.cPageIdx = 0;
                        p_tCurrBlcok->tFlag.bReadReq = FALSE;
                        p_tCurrBlcok->cZoneStart = (p_tCurrBlcok->p_tData->iStartAddr)>>8;
                        p_tCurrBlcok->eUsrRet = EEP_OPTION_WAIT;
                        p_tCurrBlcok->iOvfTimer = 0;
			   eep_printf(_T("Power_on load block(%d) start\n",p_tCurrBlcok->p_tData->cID));
                        break;
                    }

                }
                l_tEepCB.p_tCurrNode = l_tEepCB.p_tCurrNode->p_tNext;
                
            }
            else
            {
                l_tEepCB.eDevState = EEP_DEV_IDLE;
                _SendMsgToHMI(MS_SYS_DEV_STATE,DEV_IDX_EEPROM,OP_DEV_STATE_NORMAL);
            }
        break;
        
        
        case EEP_DEV_CHECK_NODEV:
            if(l_tEepCB.iTimer++ > _set_timing_xms_base_eep_tick(500))l_tEepCB.eDevState = EEP_DEV_START;
        break;

        case EEP_DEV_IDLE:

            if(NULL == l_tEepCB.p_tCurrNode)
            {
               l_tEepCB.p_tCurrNode = l_tEepBlockStartNode.p_tNext;
            }
            else
            {
                tEEP_DATA_BLOCK* p_tCurrBlcok= (tEEP_DATA_BLOCK*)(l_tEepCB.p_tCurrNode->p_tElement);
                if(p_tCurrBlcok)
                {
                    if(p_tCurrBlcok->tFlag.bReadReq)
                    {
                        l_tEepCB.cI2CBusState = I2C_RET_IDLE;
                        l_tEepCB.eDevState = EEP_DEV_READ;
                        l_tEepCB.cPageCnt = 0;
                        l_tEepCB.cPageIdx = 0;
                        p_tCurrBlcok->iOvfTimer = 0;
                        p_tCurrBlcok->tFlag.bReadReq = FALSE;
                        p_tCurrBlcok->cZoneStart = (p_tCurrBlcok->p_tData->iStartAddr)>>8;
                        p_tCurrBlcok->eUsrRet = EEP_OPTION_WAIT;
                        eep_printf(_T("Read block(0x%lx) start\n",(uint32_t)p_tCurrBlcok));
                        break;
                    }
                    else if(p_tCurrBlcok->tFlag.bWriteReq)
                    {
                        if(p_tCurrBlcok->iWaitTimer)p_tCurrBlcok->iWaitTimer --;
                        else
                        {
                            l_tEepCB.cI2CBusState = I2C_RET_IDLE;
                            l_tEepCB.eDevState = EEP_DEV_WRITE;
                            l_tEepCB.cPageCnt = 0;
                            l_tEepCB.cPageIdx = 0;
                            p_tCurrBlcok->iOvfTimer = 0;
                            p_tCurrBlcok->tFlag.bWriteReq = FALSE;
                            p_tCurrBlcok->cZoneStart = (p_tCurrBlcok->p_tData->iStartAddr)>>8;
                            p_tCurrBlcok->eUsrRet = EEP_OPTION_WAIT;
                            EEP_CopyWriteZoneBuf(p_tCurrBlcok);
                            l_tEepCB.tCmdBuf.p_cBuf = l_tEEPWriteBuf;
                            eep_printf(_T("Write block(0x%lx) start\n",(uint32_t)p_tCurrBlcok));
                            break;
                        }
                    }
                }
                
                l_tEepCB.p_tCurrNode = l_tEepCB.p_tCurrNode->p_tNext;
            }

        break;
        
        case EEP_DEV_LOAD_FACTORY:
            if(NULL == l_tEepCB.p_tCurrNode)
            {
            #if 1
               _SendMsgToHMI(MS_EEP_LOAD_FACT_RET,EEP_OPTION_COMPLETE,NULL);
               l_tEepCB.eDevState = EEP_DEV_N;
	     #else
               EEP_Init();
	     #endif
               eep_printf(_T("EEP Load Fact OK!\n"));
            }
            else
            {
                tEEP_DATA_BLOCK* p_tCurrBlcok= (tEEP_DATA_BLOCK*)(l_tEepCB.p_tCurrNode->p_tElement);
                if(p_tCurrBlcok)
                {
                    if(!p_tCurrBlcok->p_tData->bLock)
                    {
                        
                            l_tEepCB.cI2CBusState = I2C_RET_IDLE;
                            l_tEepCB.eDevState ++;
                            l_tEepCB.cPageCnt = 0;
                            l_tEepCB.cPageIdx = 0;
                            p_tCurrBlcok->tFlag.bWriteReq = FALSE;
                            p_tCurrBlcok->cZoneStart = (p_tCurrBlcok->p_tData->iStartAddr)>>8;
                            p_tCurrBlcok->eUsrRet = EEP_OPTION_WAIT;
                            p_tCurrBlcok->iOvfTimer = 0;
                            p_tCurrBlcok->iWaitTimer = 0;
                            EEP_BlockLoadDefault(p_tCurrBlcok);
                            EEP_CopyWriteZoneBuf(p_tCurrBlcok);
                            l_tEepCB.tCmdBuf.p_cBuf = l_tEEPWriteBuf;
                            eep_printf(_T("block(0x%lx) start set factory\n",(uint32_t)p_tCurrBlcok));
                            break;
                    }
                }
                
                l_tEepCB.p_tCurrNode = l_tEepCB.p_tCurrNode->p_tNext;
            }

        break;
    
        
        default:
        {
            tEEP_DATA_BLOCK* p_tCurrBlcok = (tEEP_DATA_BLOCK*)(l_tEepCB.p_tCurrNode->p_tElement);
            EEP_ReadBlock(p_tCurrBlcok);
            EEP_WriteBlock(p_tCurrBlcok);
        } 
        
            
    }
}

void EEP_MsgHandle(tMSG_BUF* p_tMsg)
{
    uint16_t Id = p_tMsg->Id;
    uint16_t Op = p_tMsg->iSid;
    tEEP_DATA_BLOCK* p_tBlock = (tEEP_DATA_BLOCK*)(p_tMsg->uData.p_cData);
    switch(Id)
    {
        case MS_EEP_LOAD_FACTORY:
            if(l_tEepCB.eDevState == EEP_DEV_IDLE)
            {
                l_tEepCB.eDevState = EEP_DEV_LOAD_FACTORY;
                l_tEepCB.p_tCurrNode = l_tEepBlockStartNode.p_tNext;
            }
            else
            {
                _SendMsgToEEP(MS_EEP_LOAD_FACTORY,0,NULL);
            }
            eep_printf(_T("RX Fact CMD~~~\n"));
        break;
        case MS_EEP_WRITE_START:
            if(!EEP_WriteStart(p_tBlock,Op))
            {
                _SendMsgToEEP(MS_EEP_WRITE_START,Op,p_tBlock);
            }
        break;

        case MS_EEP_READ_START:
            if(!EEP_ReadStart(p_tBlock))
            {
                _SendMsgToEEP(MS_EEP_READ_START,Op,p_tBlock);
            }
        break;

        case MS_EEP_LOAD_DEFAULT:
            if(!p_tBlock->tFlag.bReading)
            {
                EEP_BlockLoadDefault(p_tBlock);
                EEP_WriteStart(p_tBlock,Op);
            }
            else
            {
                _SendMsgToEEP(MS_EEP_LOAD_DEFAULT,Op,p_tBlock);
            }
        break;

        case  MS_PM_STATE:
        break;
    }
    
}


void EEP_Task(EVENT iEvt,eTASK_STATE eState)
{ 

    extern tEEP_DATA_BLOCK l_tEepSysRomData;
     if(iEvt & EVT_COLD_INIT)
    {
        _SendMsgToEEP(MS_EEP_READ_START,0,&l_tEepSysRomData);
        TaskCAN_debug(_T("EEP task Cold Init!\n"));
    }
    if(iEvt & EVT_WARM_INIT)
    {
        _SendMsgToEEP(MS_EEP_READ_START,0,&l_tEepSysRomData);
        TaskCAN_debug(_T("EEP task warm Init!\n"));
    }	

    if(iEvt & EVT_MSG_READY)
    {
        tMSG_BUF tMsg;
        if(QUE_ERR_NONE == OS_GetMsgDir(&g_tEepTaskCB,&tMsg))
        {
            EEP_MsgHandle(&tMsg);
        }
    }
    
    if(eState == TASK_STATE_RUNNING)
    {
        if(iEvt & EVT_TASK_TICK_READY)
        {
		EEP_Proc();
        }
    }
}

 
tRING_QUE l_tEepMsgQue;
tMSG_BUF la_tEepMsgBuf[D_EEP_CMD_QUE_DEEP];


static const tTASK_BLOCK lc_tEepTaskCB = {
    "EEPROM",
    _EEP_TASK_TICK_,
    _EEP_CORE_TICK_,
    EEP_Task,
    EEP_Init,
    EEP_Init,
};


uint8_t EEP_TaskCreate(void)
{
    return (uint8_t)OS_TaskCreate(TASK_ID_EEPROM,
                                  &g_tEepTaskCB, 
                                  &lc_tEepTaskCB, 
                                  &l_tEepMsgQue, 
                                  la_tEepMsgBuf, 
                                  D_EEP_CMD_QUE_DEEP);
}

