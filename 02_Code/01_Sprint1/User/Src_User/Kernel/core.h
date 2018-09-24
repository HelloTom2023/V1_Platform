/*********************(    Copyright infomation 2013   )************************
 * FILE      :
 * INFOMATIN :
 * VERSION   : v00
 * DATA      : 26/03, 2013
 * AUTHOR    : Koller yang
 *
 * UPDATE    :
 * ---------------------------------------------
 *   | INFOMATION
 *   | VERSION
 *   | AUTHOR
 *   -------------------------------------------
 *     |  
 *     |  
 ******************************************************************************/



#ifndef  _CORE_H_
#define  _CORE_H_

#ifdef _CORE_C_
#define _CORE_
#else
#define _CORE_   extern
#endif

#if D_DEBUG_CORE && D_PRINT_EN
#define core_printf(x)  x  
#else
#define core_printf(x)
#endif

#ifndef NULL
#define NULL (void*)0
#endif

typedef unsigned short MSG_ID;
typedef unsigned short EVENT;
   

#define D_BASE_CORE_TICK                1
#define D_CORE_TIMER_INT_NUM_IN_1MS     4
#define D_xTICK(x)                      (x)
#define D_xMS(x)                        (x)
#define _1MS_                           (1)
#define _2MS_                           (2)                  
#define _3MS_                           (3)
#define _4MS_                           (4)
#define _5MS_                           (5)
#define _6MS_                           (6)
#define _7MS_                           (7)
#define _8MS_                           (8)
#define _9MS_                           (9)
#define _10MS_                          (10)

#if 0
1:先说指向const的指针，它的意思是指针指向的内容是不能被修改的。它有两种写法。
const int* p; （推荐）
int const* p;

第一种可以理解为，p是一个指针，它指向的内容是const int 类型。
p本身不用初始化它可以指向任何标示符，但它指向的内容是不能被改变的。

第二种很容易被理解成是p是一个指向int的const指针（指针本身不能被修改），但这样理解是错误的，
它也是表示的是指向const的指针（指针指向的内容是不能被修改的），它跟第一种表达的是一个意思。
为了避免混淆推荐大家用第一种。

2:再说const指针，它的意思是指针本身的值是不能被修改的。它只有一种写法
int* const p=一个地址; (因为指针本身的值是不能被修改的所以它必须被初始化）

这种形式可以被理解为，p是一个指针，这个指针是指向int 的const指针。
它指向的值是可以被改变的如*p=3;

3:还有一种情况是这个指针本身和它指向的内容都是不能被改变的，请往下看。
const int* const p=一个地址;
int const* const p=一个地址;
#endif

#define OS_HwRtcStop()     v850_wt_stop()
#define OS_HWRtcStart()    v850_wt_init()



#define _set_timing_core_tick_num(x)       (x)
#define _set_timing_xs_base_core_tick(x)   (D_CORE_TIMER_INT_NUM_IN_1MS*x*1000)
#define _set_timing_xms_base_core_tick(x)  (D_CORE_TIMER_INT_NUM_IN_1MS*x)
#define _set_timing_sec_base_rtc(x)        (x)


#define BIT_00                  0x0001
#define BIT_01                  0x0002
#define BIT_02                  0x0004
#define BIT_03                  0x0008
#define BIT_04                  0x0010
#define BIT_05                  0x0020
#define BIT_06                  0x0040
#define BIT_07                  0x0080
#define BIT_08                  0x0100
#define BIT_09                  0x0200
#define BIT_10                  0x0400
#define BIT_11                  0x0800
#define BIT_12                  0x1000
#define BIT_13                  0x2000
#define BIT_14                  0x4000
#define BIT_15                  0x8000


/*******************************************************************************
 * System event
 * User.s app can not Post this event but can get
 *******************************************************************************/
#define EVT_MSG_READY               		BIT_15         /*message entry*/
#define EVT_TASK_TICK_READY         BIT_14         /*Task's task timer timeout*/
#define EVT_CORE_TICK_READY         BIT_13         /*Task's core timer timeout*/
#define EVT_COLD_INIT               BIT_12         /*Cold init*/
#define EVT_WARM_INIT               BIT_11         /*Warm init*/
#define EVT_RTC_SECOND              BIT_10

#define EVT_LOCK_MASK               (EVT_MSG_READY|EVT_CORE_TICK_READY|EVT_COLD_INIT|EVT_WARM_INIT)

#define EVT_CLEAR_MASK             ((EVT_MSG_READY))

/*******************************************************************************
 * RTC Block
 *******************************************************************************/
 #pragma pack(1)
typedef struct{
    uint8_t cYearH;
    uint8_t cYearL;
    uint8_t cMonth;
    uint8_t cDay;
    uint8_t cHour;
    uint8_t cMin;
    uint8_t cSec;
}tRTC_BLOCK;


/*******************************************************************************
 * Message data
 *******************************************************************************/
typedef union{        
       uint8_t 	a_cData[sizeof(void*)];
       void*  	p_cData;
}uMSG_DATA;

/*******************************************************************************
 * Message struct
 * User Msg: Id = HMS_ + LMS_
 *           iSid = Option code
 *           uData = Param
 *           p_fCallBack = Call back this if Msg has been handled
 *******************************************************************************/
 #pragma pack(1)
typedef struct _msg_buf{
    MSG_ID           Id;
    uint16_t           iSid;
    uMSG_DATA        uData;
}tMSG_BUF;

typedef enum {
    QUE_ERR_NONE,
    QUE_ERR_EMPTY,
    QUE_ERR_FULL,
    QUE_ERR_NOQUE,
    QUE_ERR_NUM
}eQUE_ERROR;



typedef enum{
    TASK_ERR_NONE,
    TASK_ERR_NO_LINK,
    TASK_ERR_REPEAT_CREAT,
    TASK_ERR_NO_TASK_BLOCK,
    TASK_ERR_ID_ERR,

    TASK_ERR_NUM
}eTASK_ERROR;


/*******************************************************************************
 * list node struct
 *******************************************************************************/

typedef struct _list_node{
    struct _list_node* p_tPrev;     /*Link to previous node*/
    struct _list_node* p_tNext;     /*Link to next node*/
    void*              p_tElement;  /*link to list element*/
}tNODE;


/*******************************************************************************
 * Ring queue struct
 *******************************************************************************/
#pragma pack(1)
typedef struct{
    uint8_t    cHead;   /*Queue head position*/
    uint8_t    cTail;   /*Queue tail position*/
    uint8_t    cMax;    /*Queue element number*/
    eQUE_ERROR       eState;  /*Queue's state*/
    void*            p_vBuf;  /*Queue's element buff address*/
}tRING_QUE; 



/*******************************************************************************
 *Task State
 *******************************************************************************/

typedef enum{
    TASK_STATE_READY,     /*Task Create success,Wait to running*/
    TASK_STATE_RUNNING,   /*running state*/
    TASK_STATE_STOP,      /*stop state,TaskService is not running*/

    TASK_STATE_NUM
}eTASK_STATE;

#pragma pack(1)
typedef struct _tmr_block{
    struct _tmr_block* p_tNext;                   // 下一个定时器
    unsigned short     iCount;                    // 任务基准时间计数器
    unsigned short     iSpill;                    // 溢出设置  最小溢出时间:1*OS_TICK最大溢出时间:0xffff*OS_TICK
    void               (*p_fService)(void);       // 定时器服务程序
}tTMR_BLOCK;

/*******************************************************************************
 * Task attributy block
 *******************************************************************************/
#pragma pack(1)
typedef struct _task_block{    
    char*             p_cName;                  
    uint16_t	    iTaskSpill;            
    uint8_t           cCoreSpill;              
    void              (*p_fTaskService)(EVENT,eTASK_STATE);        
    uint8_t           (*p_fInit)(void);         
    uint8_t           (*p_fDInit)(void); 

}tTASK_BLOCK;

/*******************************************************************************
 * Task control block define
 *******************************************************************************/
#pragma pack(1)
typedef struct _task_node{
    tNODE                 tNode;       //任务节点标示
    uint8_t                 Id;        //任务ID
    const tTASK_BLOCK*    pc_tTCB;     //任务块
    eTASK_STATE           eState;      //任务状态

    uint8_t               cCoreTimer;  //同步内核tick定时器，用于runtime过程中的定时
    unsigned short        iTaskTimer;  //任务timer,不能用于任务自身进程,用于任务定时运行部分
    tRING_QUE*            p_tMsgQue;   //任务消息队列
    unsigned short        iEvt;        //任务事件
}tTASK_CTRL_BLOCK;

_CORE_ uint16_t 	OS_CalCrc16(uint8_t *ptr, uint16_t len);
/*******************************************************************************
 * @Function RTC and Tick handle
 * @brief      support the RTC and Tick service
 * @param      none        
 * @retval     none
 *******************************************************************************/
_CORE_ void          isrOS_RTC            (void);
_CORE_ void          isrOS_Tick           (void);


/*******************************************************************************
 * @Function OS_GetRTC/OS_SetRTC/OS_GetOsTick
 * @brief      get rtc ,fill to the tRTC_BLOCK
 * @param      tRTC_BLOCK* p_tRtc        
 * @retval     none
 *
 * @Function OS_GetWatchSecond/OS_ClearWatchSecond
 * Supply a second time_sevice when the CPU Clock is stop
 *******************************************************************************/
_CORE_ void          OS_GetRTC            (tRTC_BLOCK* p_tRtc);
_CORE_ void          OS_SetRTC            (tRTC_BLOCK* p_tRtc);
_CORE_ uint32_t      OS_GetWatchSecond    (void);
_CORE_ void          OS_SetWatchSecond    (uint32_t);
_CORE_ uint32_t      OS_GetOsTick         (void);
_CORE_ void 		 OS_ClearOsTick(void);


/*----------------------------------------------------------------------------------------*/
/*******************************************************************************
* In your softwear, some data only need to  initialize once.than they will be 
* savedin the ram,and will save to the EEPROM in a good time. you must save them 
* in a LOCKED ram. We give this ram block a name : "no_init"
* If you placed data into this block,they will hold themself in ram untill mcu 
* power off.
* For check this data,we also creat a checksum for each sub data block.ofcause,
* the checksum data also placed into a special block named "ram_chk"
* If the data block is not init,you must init or loader them from eeprom.
********************************************************************************/


/*******************************************************************************
 * @function    OS_RamCheck
 * @brief      Check the no init ram block is init or no
 * @param      void* p_vStartAdd   no_init ram start address
 *          uint16_t iSize        ram block size
 *          void* p_vChkSunAdd  the address save the ram block checksum                
 * @retval     seccess or fail
 *          0: this ram block is not init,system is srart in the first time
 *******************************************************************************/
_CORE_ bool          OS_RamCheck          (void* p_vStartAdd,uint16_t iSize,void* p_vChkSunAdd);


/*******************************************************************************
 * @function    OS_ClearRamChkElement
 * @brief      clear a ran check sum of a ram block, make this block in to init state
 * @param      void* p_vChkSunAdd     the address save the ram block checksum            
 * @retval     none
 *******************************************************************************/
_CORE_ void          OS_ClearRamChkElement(void* p_vChkSunAdd);
_CORE_ void          OS_ClearNoInitBlock(void);


/*******************************************************************************
 * @function    OS_CreateRamChkBlock
 * @brief      if init a no init block or change a element in the block.
 *          you must call this function to re_general a checksum.
 * @param      void* p_vStartAdd   no_init ram start address
 *          uint16_t iSize        ram block size
 *                 
 * @retval     none
 *******************************************************************************/
_CORE_ void          OS_CreateRamChkBlock  (void* p_vStartAdd,uint16_t iSize,void* p_vChkSunAdd);

/*----------------------------------------------------------------------------------------*/
/*******************************************************************************
 * @function    List service function
 * @brief  insert/delete a element of list    
 *           
 * @param      
 * @retval     none
 *******************************************************************************/

_CORE_ bool         OS_ListInsert        (tNODE* p_tTarg,tNODE* p_tNew,bool bHead);
_CORE_ bool         OS_ListDelete        (tNODE* p_tNode);
_CORE_ tNODE*       OS_ListGetHead       (tNODE* p_tNode);
_CORE_ tNODE*       OS_ListGetTail       (tNODE* p_tNode);

/*----------------------------------------------------------------------------------------*/

/*******************************************************************************
 * @function    QUEUE service function
 * @brief  insert/post/get a element to the queue   
 *           
 * @param      
 * @retval     eQUE_ERROR
 *******************************************************************************/
_CORE_ eQUE_ERROR    OS_InsertQueElement  (tRING_QUE * p_tQue, bool bHead, void * p_vBuf, uint16_t iBufLen);
_CORE_ eQUE_ERROR    OS_PostQueElement    (tRING_QUE * p_tQue, void * p_vBuf, uint16_t iBufLen);
_CORE_ eQUE_ERROR    OS_GetQueElement     (tRING_QUE * p_tQue, void * p_vBuf, uint16_t iBufLen);


/*******************************************************************************
 * @function    Message serveice function
 * @brief  insert/post/get a msg or Clear all msg of the TASK,user the  
 *         tTASK_CTRL_BLOCK* parameter type to updata the function productivity
 * @param      
 * @retval     eQUE_ERROR
 *******************************************************************************/
_CORE_ eQUE_ERROR    OS_InsertMsgDir      (tTASK_CTRL_BLOCK* p_tTask, MSG_ID Id,uint16_t iSid,void* p_vBuf,bool bHead);
_CORE_ eQUE_ERROR    OS_PostMsgDir        (tTASK_CTRL_BLOCK* p_tTask, MSG_ID Id,uint16_t iSid,void* p_pBuff);
_CORE_ eQUE_ERROR    OS_PostFullMsgDir    (tTASK_CTRL_BLOCK* p_tTask, MSG_ID Id,uint16_t iSid,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3);
_CORE_ eQUE_ERROR    OS_GetMsgDir         (tTASK_CTRL_BLOCK* p_tTask,tMSG_BUF* p_tBuff);
_CORE_ void          OS_ClrAllMsgDir      (tTASK_CTRL_BLOCK* p_tTask);


/*******************************************************************************
 * @function    Event serveice function
 * @brief  Post one event to TASK which ID is cTaskID/Post mass a evt to all task
 *           
 * @param      
 * @retval     Posting evt is seccessful(1) or failed(0)
 *******************************************************************************/
_CORE_ uint8_t       OS_PostEventDir      (tTASK_CTRL_BLOCK* p_tTask,EVENT iEvt);
_CORE_ void          OS_PostEventMass     (EVENT iEvt);
_CORE_ uint8_t       OS_PostEvent         (uint8_t cTaskID,EVENT iEvt);

/*----------------------------------------------------------------------------------------*/



/*******************************************************************************
 * @function    OS_TaskSchedule
 * @brief   It's your main function process after the cpu and os init.
 *           
 * @param      none
 * @retval     none
 *******************************************************************************/ 
_CORE_ void          OS_TaskSchedule      (void);

/*******************************************************************************
 * @function    OS_TaskCreate,OS_TaskListGetHead,OS_TaskListGetNext
 * @brief   Create a new Task.Link  all resource to the Task.
 *           
 * @param      uint8_t cTaskID,                 Task ID:1~254
            tTASK_CTRL_BLOCK* p_tTask,     Task cotrol parameter
 *          const tTASK_BLOCK* pc_tTCB,    Task attributy block
 *          tRING_QUE* pmsg_que,           Task Msg que pointer
 *          tMSG_BUF* msg_buf,             It's point to message ram of the task
 *          uint8_t msg_que_len              message ram size / que element number
 * @retval     eTASK_ERROR
 *******************************************************************************/ 
_CORE_ eTASK_ERROR   OS_TaskCreate         (uint8_t cTaskID,tTASK_CTRL_BLOCK* p_tTask,const tTASK_BLOCK* pc_tTCB,tRING_QUE* pmsg_que,tMSG_BUF* msg_buf,uint8_t msg_que_len);

/*******************************************************************************
 * @function     OS_TaskListGetHead,OS_TaskListGetNext
 * @brief   Get the head task point in the task list 
 *          Get the next task point of the "p_tTask" in the task list
 *           
 * @param      p_tTask 
 * @retval     Point of task
 *******************************************************************************/ 
_CORE_ tTASK_CTRL_BLOCK* OS_TaskListGetHead(void);
_CORE_ tTASK_CTRL_BLOCK* OS_TaskListGetNext(tTASK_CTRL_BLOCK* p_tTask);

/*******************************************************************************
 * @function    OS_TaskStart/OS_TaskDelet/OS_TaskStop
 * @brief   Start a Task. Set it's state to running_state,and call it's init func
 *          Delet a Task. it will not be called by OS_TaskSchedule
 *          Stop a Task. Set it's state to Stop_state and call it's de_init func
 * @param      uint8_t cTaskID,                 Task ID
 *             tTASK_CTRL_BLOCK* p_tTask        Task Control block
 * @retval     Task init function is running seccessfuly(1) or failed(0)
 *******************************************************************************/ 
_CORE_ uint8_t       OS_TaskStart         (uint8_t cTaskID);
_CORE_ uint8_t       OS_TaskStop          (uint8_t cTaskID);
//_CORE_ uint8_t       OS_TaskEmergHandle   (uint8_t cTaskID,bool bStopTask);

_CORE_ uint8_t       OS_TaskStartDir      (tTASK_CTRL_BLOCK* p_tTask);
_CORE_ uint8_t       OS_TaskStopDir       (tTASK_CTRL_BLOCK* p_tTask);
//_CORE_ uint8_t       OS_TaskEmergDir      (tTASK_CTRL_BLOCK* p_tTask,bool bStopTask);

_CORE_ void          OS_TaskDelete        (uint8_t cTaskID);


/*******************************************************************************
 * @function    OS_TaskIsActive/OS_TaskGetState
 * @brief      Task is in the Running state or no
 *             Get Task's state
 * @param      uint8_t cTaskID,                 Task ID
 *             tTASK_CTRL_BLOCK* p_tTask        Task control block
 * @retval     
 *******************************************************************************/ 
_CORE_ uint8_t       OS_TaskIsActive      (uint8_t cTaskID);
_CORE_ eTASK_STATE   OS_TaskGetState      (uint8_t cTaskID);

_CORE_ uint8_t       OS_TaskIsActiveDir   (tTASK_CTRL_BLOCK* p_tTask);
_CORE_ eTASK_STATE   OS_TaskGetStateDir   (tTASK_CTRL_BLOCK* p_tTask);



/*******************************************************************************
 * @function    OS_Init
 * @brief      Initialize the OS. Call this fuction after the CPU initial
 * @param      none
 * @retval     none
 *******************************************************************************/ 
_CORE_ void          OS_Init              (void);


#endif    /*  _CORE_H_   */

