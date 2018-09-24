
#define _SRC_CORE_C_
#include "..\..\..\User\src_user\config\inc.h"
//#include "..\..\..\..\Code_user\User\src_user\config\inc.h"

/*******************************************************************************
*
*This block use list api to operate the source list.
*If you want to use system source in a list, It allways is the next node of head.
*
*******************************************************************************/

#pragma pack(1)
typedef struct{
    uint8_t cNum;
    tNODE*  p_tStartNode;
    tNODE*  p_tNodeBuff;
}tSRC_LIST;

typedef struct{

    tNODE   tRunStartNode,a_tRunNode[D_SRC_RUN_MAX_NUM];
    tNODE   tFloatStartNode,a_tFloatNode[D_SRC_FLOAT_MAX_NUM];
    tNODE   tHpriStartNode,a_tHpriNode[D_SRC_HPRI_MAX_NUM];
    tNODE   tRearStartNode,a_tRearNode[D_SRC_REAR_MAX_NUM];
    uint16_t  iSysSrcChkSum;
    
}tSYS_SOURCE_BLOCK;

#pragma section data "no_init" begin    
tSYS_SOURCE_BLOCK l_tSysSrcBlcok;
tNODE   l_tSysStartNode;
#pragma section data "no_init" end    

const tSRC_LIST la_cSrcListNum[] = 
{    
    {D_SRC_HPRI_MAX_NUM,&l_tSysSrcBlcok.tHpriStartNode,l_tSysSrcBlcok.a_tHpriNode},
    {D_SRC_FLOAT_MAX_NUM,&l_tSysSrcBlcok.tFloatStartNode,l_tSysSrcBlcok.a_tFloatNode},
    {D_SRC_RUN_MAX_NUM,&l_tSysSrcBlcok.tRunStartNode,l_tSysSrcBlcok.a_tRunNode},
    {D_SRC_REAR_MAX_NUM,&l_tSysSrcBlcok.tRearStartNode,l_tSysSrcBlcok.a_tRearNode},
    {SRC_TYPE_NUM,&l_tSysStartNode,NULL},
};

tNODE* SRC_GetIdleNode(eSOURCE_LIST_TYPE eListType)
{
    uint8_t i = 0;
    tNODE* p_tIdleNode = NULL;
    tNODE* p_tPool = la_cSrcListNum[eListType].p_tNodeBuff;
    uint8_t cSize = la_cSrcListNum[eListType].cNum;
    if(p_tPool)
    {
        for(i = 0; i < cSize; i ++)
        {
            if(NULL == p_tPool[i].p_tPrev
                && NULL == p_tPool[i].p_tNext
                && NULL == p_tPool[i].p_tElement)
            { 
                p_tIdleNode = &(p_tPool[i]);
                break;
            }
        }
    }
    return p_tIdleNode;
}

tNODE* SRC_GetSrcNode(tSOURCE* p_tSrc,eSOURCE_LIST_TYPE eListType)
{
    uint8_t i = 0;
    tNODE* p_tNode = NULL;
    tNODE* p_tStart = la_cSrcListNum[eListType].p_tStartNode;
    uint8_t cSize = la_cSrcListNum[eListType].cNum;
    if(p_tStart)
    {
        tNODE* p_tSrcNode = p_tStart->p_tNext;
        while(p_tSrcNode && i < cSize)
        {
            if(p_tSrc == ((tSOURCE*)(p_tSrcNode->p_tElement)))
            {
                p_tNode = p_tSrcNode;
                break;
            }
            else p_tSrcNode = p_tSrcNode->p_tNext;
            i++;
        }
    }

    return p_tNode;
}


tNODE* SRC_GetSrcNodeBaseType(eSOURCE_TYPE eSrcType,eSOURCE_LIST_TYPE eListType)
{
    uint8_t i = 0;
    tNODE* p_tNode = NULL;
    tNODE* p_tStart = la_cSrcListNum[eListType].p_tStartNode;
    uint8_t cSize = la_cSrcListNum[eListType].cNum;
    if(p_tStart)
    {
        tNODE* p_tSrcNode = p_tStart->p_tNext;
        while(p_tSrcNode && i < cSize)
        {
            if(eSrcType == ((tSOURCE*)(p_tSrcNode->p_tElement))->eSrcType)
            {
                p_tNode = p_tSrcNode;
                break;
            }
            else 
	     {
		   p_tSrcNode = p_tSrcNode->p_tNext;
            }
            i++;
        }
    }

    return p_tNode;
}


tSOURCE* SRC_GetSrcBlockBaseType(eSOURCE_TYPE eSrcType,eSOURCE_LIST_TYPE eListType)
{
    tSOURCE* p_tSrc = NULL;
    tNODE* p_tSrcNode = SRC_GetSrcNodeBaseType(eSrcType,eListType);
    if(p_tSrcNode)
    {
        p_tSrc = (tSOURCE*)(p_tSrcNode->p_tElement);
    }

    return p_tSrc;
}

tNODE* SRC_GetSrcNodeBaseID(eSOURCE_ID eSrcID,eSOURCE_LIST_TYPE eListType)
{
    uint8_t i = 0;
    tNODE* p_tNode = NULL;
    tNODE* p_tStart = la_cSrcListNum[eListType].p_tStartNode;
    uint8_t cSize = la_cSrcListNum[eListType].cNum;
    if(p_tStart)
    {
        tNODE* p_tSrcNode = p_tStart->p_tNext;
        while(p_tSrcNode && i < cSize)
        {
            tSOURCE* tTmpSrc = (tSOURCE*)(p_tSrcNode->p_tElement);
            if(tTmpSrc && eSrcID == tTmpSrc->eSrcID)
            {
                p_tNode = p_tSrcNode;
                src_printf(_T("ID_%x source is Exist in listType:%x\n",eSrcID, eListType));
                break;
            }
            else p_tSrcNode = p_tSrcNode->p_tNext;
            i++;
        }
    }

    return p_tNode;
}

/*
* mark: la_cSrcListNum[eListType].p_tStartNode->p_tNext has the current source.
*/

tSOURCE* SRC_GetCurrentSrcInList(eSOURCE_LIST_TYPE eListType)
{
    tSOURCE* p_tSrc = NULL;
    
    tNODE* p_tSrcNode = la_cSrcListNum[eListType].p_tStartNode->p_tNext;
    if(p_tSrcNode)
		p_tSrc = (tSOURCE*)(p_tSrcNode->p_tElement);
    
    return p_tSrc;
}

tNODE* SRC_GetListHeadNode(eSOURCE_LIST_TYPE eListType)
{
    tNODE* re = NULL;
    if(eListType < SRC_LIST_NUM)re = la_cSrcListNum[eListType].p_tStartNode->p_tNext;
    return re;
}



tSOURCE* SRC_GetSysSrcBaseType(eSOURCE_TYPE eSrcType)
{
    tSOURCE* p_tSrc = NULL;
    tNODE* p_tNode = SRC_GetSrcNodeBaseType(eSrcType,SRC_LIST_SYSTEM);
    if(p_tNode)
	p_tSrc = (tSOURCE*)(p_tNode->p_tElement);

    return p_tSrc;
}

tSOURCE* SRC_GetSysSrcBaseID(eSOURCE_ID eSrcID)
{
    tSOURCE* p_tSrc = NULL;
    tNODE* p_tNode = SRC_GetSrcNodeBaseID(eSrcID,SRC_LIST_SYSTEM);
    if(p_tNode)
		p_tSrc = (tSOURCE*)(p_tNode->p_tElement);

    return p_tSrc;
}





uint8_t SRC_Create(tSOURCE* p_tSrc,  
                   eSOURCE_ID eSrcID,   
                   eSOURCE_TYPE eSrcType,
                   const char* p_cName,
                   const tSOURCE_CTRL_BLOCK* p_tSCB,
                   uint8_t cPriority,  
                   uint16_t cFlag,  
                   uint8_t* p_cRunState)
{
    uint8_t i = 0;
    uint8_t re = FALSE;
    tNODE* p_tHead = &l_tSysStartNode;
    
    if(p_tSrc )
    {
        /*Clear current node*/
        p_tSrc->tNode.p_tNext = NULL;
        p_tSrc->tNode.p_tPrev = NULL;

        /*Get the tail node*/
        while(p_tHead->p_tNext && i <= SOURCE_NUM)
        {
           // src_printf(_T("node handle:%lx,",(uint32_t)(p_tHead->p_tNext)));
          //  src_printf(_T("Src:TYPE %d ",((tSOURCE*)p_tHead->p_tNext->p_tElement)->eSrcType)); 
          //  src_printf(_T(((tSOURCE*)p_tHead->p_tNext->p_tElement)->p_cName)); 
         //   src_printf(_T(" is scan!\n"));
            p_tHead = p_tHead->p_tNext;
            i++;
        }
	 CLEAR_WATCHDOG();
        src_printf(_T("sourcelist size is %d, review %d sources in it\n",SOURCE_NUM,i));
        p_tSrc->eSrcID = eSrcID;
        p_tSrc->eSrcType = eSrcType;
        p_tSrc->p_cName = p_cName;
        p_tSrc->p_tSCB = p_tSCB;
        p_tSrc->p_cRunState = p_cRunState;
        p_tSrc->tFlag.byte = cFlag;
        p_tSrc->cPriority = cPriority;

        if(p_cRunState)*p_cRunState = 0;
        
        /*Resend the SRC list node*/
        if(OS_ListInsert(p_tHead,&(p_tSrc->tNode),FALSE))  // place the new node to the list rear.
        {
            p_tSrc->tNode.p_tElement =(void*)p_tSrc;
            src_printf(_T("Src:TYPE %d ",eSrcType)); 
            src_printf(_T(p_cName)); 
            src_printf(_T(" is created! init it\n"));
            re = TRUE;
        }

        if(re && p_tSCB)
        {
            if(p_tSCB->p_fInit)p_tSCB->p_fInit(eSrcType);
        }

    }

    return re;
}

void SRC_Delete(tSOURCE* p_tSrc,eSOURCE_LIST_TYPE eListType)
{
    if(p_tSrc)
    {
        tNODE* p_tSrcNode = SRC_GetSrcNode(p_tSrc,eListType); 
        if(p_tSrcNode)
        {
            SRC_Ctrl((tSOURCE *)(p_tSrcNode->p_tElement),eListType,DISABLE);
            OS_ListDelete(p_tSrcNode);
        }
    }
}


uint8_t SRC_CheckMutex(tSOURCE* p_tSrc,eSOURCE_ZONE eZone)
{
    uint8_t re = FALSE;
    if(eZone == SRC_ZONE_FRONT)
    {
        tSOURCE* p_tRearSrc = SRC_GetCurrentSrcInList(SRC_LIST_REAR);
        if( p_tRearSrc && p_tSrc
            && p_tSrc != p_tRearSrc)
        {
            /*The source which will be inserted to FRONT is running in REAR*/
            if( p_tSrc->p_cRunState
                && p_tRearSrc->p_cRunState == p_tSrc->p_cRunState)
            {
                re = TRUE;
            }
            
            /*No Mutex,delete it in rear list*/
            if(re == FALSE)
		SRC_Delete(p_tSrc,SRC_LIST_REAR);
        }
    }
    else if(eZone == SRC_ZONE_REAR)
    {
        tSOURCE* p_tFrontSrc = SRC_GetCurrentSrcInList(SRC_LIST_RUNTIME);
        if( p_tFrontSrc && p_tSrc
            && p_tSrc != p_tFrontSrc)
        {
            if( p_tSrc->p_cRunState
                && p_tFrontSrc->p_cRunState == p_tSrc->p_cRunState)
            {
                re = TRUE;
            }
            /*No Mutex,delete it in runtime list*/
            if(re == FALSE)
		SRC_Delete(p_tSrc,SRC_LIST_RUNTIME);
        }
        
    }

    return re;
}


/*执行对应源的启动和停止操作，同时更新源的FLAG标志位*/

void SRC_Ctrl(tSOURCE* p_tSrc,eSOURCE_LIST_TYPE eListType,bool bEnable)
{
    if(p_tSrc && p_tSrc->p_tSCB && eListType < SRC_LIST_SYSTEM)
    {
        eSOURCE_ZONE eZone = SRC_ZONE_FRONT;
        uint8_t* p_cFlag = p_tSrc->p_cRunState;
        
        if(eListType == SRC_LIST_REAR)eZone = SRC_ZONE_REAR;
        
        src_printf(_T(p_tSrc->p_cName));
        src_printf(_T(" in list:%d",eListType));
        
        if(bEnable)    /*Source start*/
        {
            
            src_printf(_T(" Start!"));
            /*Src_stop function is valid ande it is in stop state*/
            if( p_tSrc->p_tSCB->p_fStart
                && (NULL == p_cFlag || 0 == *p_cFlag))
            {
                 p_tSrc->p_tSCB->p_fStart(p_tSrc->eSrcType,eZone);
                 src_printf(_T(" Run start function!"));
            }
            
            if(p_cFlag)*p_cFlag |= (1<<eListType);
            src_printf(_T("flag:%x\n",*p_cFlag));
        }
        else          /*Source stop*/
        {
            src_printf(_T(" Stop!"));
            if(p_cFlag)*p_cFlag &=~(1<<eListType);

            /*Src_stop function is valid ande it is in running state*/
            if( p_tSrc->p_tSCB->p_fStop
                && (NULL == p_cFlag || 0 == *p_cFlag))
            {
                 p_tSrc->p_tSCB->p_fStop(p_tSrc->eSrcType,eZone);
                 src_printf(_T(" Run stopt function!"));
            }
            src_printf(_T("flag:%x\n",*p_cFlag));
        }

        src_printf(_T("\n"));
    }
}

/*Operate the src list.
It have a bug.When insert a src to a full high priority list,must compear the value of priority.
But I do noting,so we must set the D_SRC_HPRI_MAX_NUM is the MAX we using*/
void SRC_OperateSrcList(eSOURCE_LIST_TYPE eListType,tSOURCE* p_tSrc,bool bInsert)
{
    tNODE* p_tNodeHead = la_cSrcListNum[eListType].p_tStartNode;
    
    if(p_tSrc && p_tNodeHead)
    {
        
        tNODE* p_tSrcNode = SRC_GetSrcNodeBaseType(p_tSrc->eSrcType,eListType);
        if(bInsert)
        {
            uint8_t bStart = FALSE;
            uint8_t dir = FALSE;
            tNODE* p_tTargNode = p_tNodeHead;
            eSOURCE_ZONE eZone = SRC_ZONE_FRONT;
			
            if(eListType == SRC_LIST_REAR)
            {
	 	   eZone = SRC_ZONE_REAR;
            }

            /*if rear and front is mutex,do nothing*/
            if(SRC_CheckMutex(p_tSrc,eZone))
            {
                _SendMsgToHMI(MS_SRC_SYS_CMD,OP_SRC_SW_FAIL,p_tSrc->eSrcType);
                src_printf(_T(p_tSrc->p_cName));
                src_printf(_T(" Source is Mutex!!\n"));
            }
            else
            {
                
                /*The src is exist in tht list,than delete it*/
                if(p_tSrcNode)
                {            
                    OS_ListDelete(p_tSrcNode);
		      src_printf(_T(" src exist ,delete node\n"));
                    p_tSrcNode = NULL;                   
                }
                    
                p_tSrcNode = SRC_GetIdleNode(eListType);
    
                /*if not enough idle node*/
                if(NULL == p_tSrcNode)
                {
                    src_printf(_T(" There are not enough Idle Node\n"));
                    /*Find the tail node*/
                    p_tSrcNode = OS_ListGetTail(p_tNodeHead);
                    
                    /*Check this src,than stop it or no!*/
                    if(SRC_LIST_RUNTIME > eListType && p_tSrcNode)
                    {
                        SRC_Ctrl((tSOURCE*)(p_tSrcNode->p_tElement),eListType,DISABLE);
                    }
    
                    /*Delete tail node*/
                    OS_ListDelete(p_tSrcNode);    
                }
    
                /*If the list is high priority or float list,must be inserted  in order of src's priority*/
                if(SRC_LIST_TOP == eListType)
                {
                    /*Get the SOURCE it's priority is not min than the source you want to insert*/
                    
                    while(p_tTargNode->p_tNext)
                    {   
                        tSOURCE* p_tTagSrc;
                        p_tTargNode = p_tTargNode->p_tNext;  /*Get the fist valid source node*/
                        p_tTagSrc = ((tSOURCE*)(p_tTargNode->p_tElement));
                        
                        if(p_tTagSrc )
                        {
                            if(p_tTagSrc->cPriority>= p_tSrc->cPriority)
                            {
                                dir = TRUE;/*Insert direction is head*/
                                break;
                            }
                        }
                    }
    
                    
                }
                else
                {
                    /*In run or rear list,if insert one src,stop the last valid src*/
                    if(p_tNodeHead->p_tNext)
                    {
                        tSOURCE* p_tTagSrc = ((tSOURCE*)(p_tNodeHead->p_tNext->p_tElement));
                     //   if(!(p_tSrc->tFlag.field.bStopAll
                     //      && p_tTagSrc->tFlag.field.bIgnoreStop))
                        {
                            SRC_Ctrl(p_tTagSrc,eListType,DISABLE);
                        }
                    }
                }
    
                /*Insert the src_node*/
                if(OS_ListInsert(p_tTargNode,p_tSrcNode,dir))
                {
                    src_printf(_T("%d list insert ele:%lx,SRC:%lx\n",eListType,(uint32_t)p_tSrcNode,(uint32_t)p_tSrcNode->p_tElement));
                    p_tSrcNode->p_tElement =(void*)p_tSrc;
                    SRC_Ctrl(p_tSrc,eListType,ENABLE);
                }
            }
        }
        else
        {
            /*Check the node is the first valid node?*/
            if(SRC_LIST_RUNTIME == eListType
               || SRC_LIST_REAR == eListType)
            {
               if(p_tSrcNode && p_tSrcNode == p_tNodeHead->p_tNext)
                {
                    if(p_tSrcNode->p_tNext)
                    {
                        SRC_Ctrl((tSOURCE*)(p_tSrcNode->p_tNext->p_tElement),eListType,ENABLE);
                    }
                }
            }
            /*Stop the source*/
            if(p_tSrcNode)
			SRC_Ctrl((tSOURCE*)(p_tSrcNode->p_tElement),eListType,DISABLE);

            /*Delete current node*/
            OS_ListDelete(p_tSrcNode);
           
        }

        OS_CreateRamChkBlock((void*)(&l_tSysSrcBlcok)
                              ,sizeof(tSYS_SOURCE_BLOCK)- sizeof(uint16_t)
                              ,(void*)&(l_tSysSrcBlcok.iSysSrcChkSum));
    }
}

void SRC_ClearSrcList(eSOURCE_LIST_TYPE eListType)
{
    uint8_t cSize = la_cSrcListNum[eListType].cNum;
    tNODE* p_tNode = la_cSrcListNum[eListType].p_tStartNode->p_tNext;

    while(p_tNode && cSize)
    {
        tSOURCE* p_tSrc = (tSOURCE*)(p_tNode->p_tElement);
        SRC_Ctrl(p_tSrc,eListType,DISABLE);
        p_tNode = p_tNode->p_tNext;
        cSize -- ;
    }

    la_cSrcListNum[eListType].p_tStartNode->p_tNext = NULL;
    la_cSrcListNum[eListType].p_tStartNode->p_tPrev = NULL;
    if(la_cSrcListNum[eListType].p_tNodeBuff)
    {
        API_MemClear((uint8_t*)(la_cSrcListNum[eListType].p_tNodeBuff),sizeof(tNODE)*cSize);
    }
    OS_CreateRamChkBlock((void*)(&l_tSysSrcBlcok)
                          ,sizeof(tSYS_SOURCE_BLOCK)- sizeof(uint16_t)
                          ,(void*)&(l_tSysSrcBlcok.iSysSrcChkSum));
    ERROR(_T("Clear list %d\n",eListType));
}


bool SRC_CoreInit(void)
{
    if(!OS_RamCheck((void*)(&l_tSysSrcBlcok)
                     ,sizeof(tSYS_SOURCE_BLOCK)- sizeof(uint16_t)
                     ,(void*)&(l_tSysSrcBlcok.iSysSrcChkSum))
      )
    {
        API_MemClear((uint8_t*)&l_tSysSrcBlcok,sizeof(tSYS_SOURCE_BLOCK));
        OS_CreateRamChkBlock((void*)(&l_tSysSrcBlcok)
                              ,sizeof(tSYS_SOURCE_BLOCK)- sizeof(uint16_t)
                              ,(void*)&(l_tSysSrcBlcok.iSysSrcChkSum));
         ERROR(_T("Init source list data/n"));
    }
    
    l_tSysStartNode.p_tNext = NULL;
    l_tSysStartNode.p_tPrev = NULL;

    return 1;
}

void SRC_CoreColdInit(void)
{
	 API_MemClear((uint8_t*)&l_tSysSrcBlcok,sizeof(tSYS_SOURCE_BLOCK));
	 l_tSysStartNode.p_tNext = NULL;
        l_tSysStartNode.p_tPrev = NULL;
}





