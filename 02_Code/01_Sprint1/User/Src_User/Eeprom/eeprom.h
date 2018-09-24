#ifndef _EEP_H_
#define _EEP_H_

#ifndef _EEP_C_
#define _EEP_    extern
#else
#define _EEP_ 
#endif

#if D_DEBUG_EEP && D_PRINT_EN
#define eep_printf(x)  x
#else
#define eep_printf(x)
#endif
#define D_EEP_CMD_QUE_DEEP   5
#define D_EEP_PAGE_LEN       16
#define D_EEP_DEV_ADDR       0xA0

#define D_EEP_MAX_NUM        0x200
#define D_EEP_ADDR_MASK      (D_EEP_MAX_NUM - 1)
#define D_EEP_ZONE_NUM       D_EEP_MAX_NUM/256

#define _EEP_TASK_TIMING_                   _4MS_
#define _EEP_CORE_TIMING_                   _1MS_
#define _EEP_TASK_TICK_                     _set_timing_xms_base_core_tick(_EEP_TASK_TIMING_)
#define _EEP_CORE_TICK_                     _set_timing_xms_base_core_tick(_EEP_CORE_TIMING_)
#define _set_timing_xms_base_eep_tick(x)        ((x/_EEP_TASK_TIMING_ - 1))
#define _set_timing_xms_base_eep_core_tick(x)   ((x/_EEP_CORE_TIMING_ - 1))

/******************************************************************************/
#define D_SETTING_HW_ID              0x00
#define D_SETTING_SYS_START_ADD      0x80
#define D_TUNER_START_ADD      (D_SETTING_SYS_START_ADD + D_EEP_PAGE_LEN*((sizeof(tSYS_ROM_DATA)/D_EEP_PAGE_LEN) + (1&&(sizeof(tSYS_ROM_DATA)%D_EEP_PAGE_LEN))))
#define D_AUDIO_START_ADD      (D_TUNER_START_ADD + D_EEP_PAGE_LEN*((sizeof(TUNER_DATUM_STRUCT)/D_EEP_PAGE_LEN) + (1&&(sizeof(TUNER_DATUM_STRUCT)%D_EEP_PAGE_LEN))))


typedef enum{
    EEP_ERR_NONE,
    EEP_ERR_NOTREADY,
    EEP_ERR_BUS_STOP,
    EEP_ERR_DEV_NOEXIST,
    EEP_ERR_TIME_OUT,
    EEP_ERR_QUEERR,
    EEP_ERR_DATA_CLASH,
    EEP_ERR_OTHER,

    EEP_ERR_NUM
}eEEPROM_ERROR;

typedef enum{
    EEP_OPTION_NONE,
    EEP_OPTION_NOTREADY,
    EEP_OPTION_BUSY,
    EEP_OPTION_WAIT,
    EEP_OPTION_COMPLETE,
    EEP_OPTION_READ_COMPLETE,
    EEP_OPTION_WRITE_COMPLETE,
    EEP_OPTION_IICERR,
    EEP_OPTION_TIMEOUT,
    EEP_OPTION_NOBLOCK,

    EEP_OPTION_NUM
}eEEP_OPTION_RET;

typedef enum{
    EEP_DATA_NOERR,
    EEP_DATA_NOBLOCK,
    EEP_DATA_OVF,
    EEP_DATA_ADDR_ERR,
    
    EEP_DATA_STATE_NUM
}eEEP_DATA_STATE;


typedef struct{
    uint8_t  cMin,cDef,cMax;
}tEEP_DATA_RANG;

typedef struct{
    bit_t         bWriting         :1;   /*1:This block is being Saved*/
    bit_t         bWriteReq        :1;   /*1:Save req*/

    bit_t         bReading        :1;   /*1:This block is being Readed*/
    bit_t         bReadReq        :1;   /*1:Read req*/

}tEEP_DATA_FLG;

typedef struct{
    uint8_t         cID;     /*Block ID,it is a mark of block.it must different*/
    uint8_t*        p_cBuf;   /*your data + 2 bytes checksum*/
    const tEEP_DATA_RANG* p_tDefData;

    uint16_t        iStartAddr;
    uint16_t        iLen;
    uint8_t         bLock;   /*This block will be locked,it can not be loaded default by Factory_Setting command*/

}tEEP_DATA;

typedef struct{
    tNODE            tBlockNode;
    const tEEP_DATA* p_tData;
    tEEP_DATA_FLG    tFlag;
    uint16_t         iOvfTimer;
    uint16_t         iWaitTimer;
    uint16_t         iZoneLen[D_EEP_ZONE_NUM];
    uint16_t         iZoneAddr[D_EEP_ZONE_NUM];
    uint8_t*         p_tZoneBuf[D_EEP_ZONE_NUM];

    uint8_t          cZoneStart;
    uint8_t          cZoneEnd;
    eEEP_OPTION_RET  eUsrRet;
}tEEP_DATA_BLOCK;
/*******************************************************************************/
/* EEPROM Block Table define*/

#define D_EEP_DATA_START_ADD      0x00
#define D_EEP_DATA_DEFLEN         0x10


#define D_EEP_PAGE_WRITE_DELAY    _set_timing_xms_base_eep_tick(10)
#define D_EEP_OPTION_TIME_OUT     _set_timing_xms_base_eep_tick(2000L)
#define D_EEP_WAIT_WRITE_TIME     _set_timing_xms_base_eep_tick(10000L)  /*Write the block after it be chaged  in this timing*/
#define D_EEP_WAIT_WRITE_TIME_S  _set_timing_xms_base_eep_tick(1000L) 

#define D_EEP_SYSSETDATA_ID      0
#define D_EEP_SYSSETDATA_ADDR    (D_EEP_DATA_START_ADD + D_EEP_PAGE_LEN *((D_EEP_DATA_DEFLEN/D_EEP_PAGE_LEN) + (1&&(D_EEP_DATA_DEFLEN%D_EEP_PAGE_LEN))))
#define D_EEP_SYSSETDATA_LEN     (sizeof(tSYS_SETTING_ROM_DATA))

#define D_EEP_SYSDATA_ID         1
#define D_EEP_SYSDATA_ADDR       (D_EEP_SYSSETDATA_ADDR + D_EEP_PAGE_LEN *((D_EEP_SYSSETDATA_LEN/D_EEP_PAGE_LEN) + (1&&(D_EEP_SYSSETDATA_LEN%D_EEP_PAGE_LEN))))
#define D_EEP_SYSDATA_LEN        (sizeof(tSYS_ROM_DATA))

#define D_EEP_SWCDATA_ID         2
#define D_EEP_SWCDATA_ADDR       (D_EEP_SYSDATA_ADDR + D_EEP_PAGE_LEN *((D_EEP_SYSDATA_LEN/D_EEP_PAGE_LEN) + (1&&(D_EEP_SYSDATA_LEN%D_EEP_PAGE_LEN))))
#define D_EEP_SWCDATA_LEN        (sizeof(tSWC_ROM_DATA))

#define D_EEP_AUDIO_ID           3
#define D_EEP_AUDIO_ADDR         (D_EEP_SWCDATA_ADDR + D_EEP_PAGE_LEN *((D_EEP_SWCDATA_LEN/D_EEP_PAGE_LEN) + (1&&(D_EEP_SWCDATA_LEN%D_EEP_PAGE_LEN))))
#define D_EEP_AUDIO_LEN          (sizeof(AUDIO_EEP_STRUCT))

#define D_EEP_CANBUS_ID	4
#define D_EEP_CANBUS_ADDR		(D_EEP_AUDIO_ADDR + D_EEP_PAGE_LEN *((D_EEP_AUDIO_LEN/D_EEP_PAGE_LEN) + (1&&(D_EEP_AUDIO_LEN%D_EEP_PAGE_LEN))))
#define  D_EEP_CANBUS_LEN		 (sizeof(tBUS_EEP_DATA))	
#define D_EEP_TPMS_LEN       	10//JUST for compile //(TPMS_UI_DATA_LENTH)

#ifdef ENABLE_UDS_DTC
#define D_EEP_UDSDTC_ID 	5
#define D_EEP_UDSDTC_ADDR    (D_EEP_CANBUS_ADDR + D_EEP_PAGE_LEN *((D_EEP_CANBUS_LEN/D_EEP_PAGE_LEN) + (1&&(D_EEP_CANBUS_LEN%D_EEP_PAGE_LEN))))
#define D_EEP_UDSDTC_LEN      (sizeof(UdsDTCMemStruc)) //size=21bytes
#else
#define D_EEP_UDSDTC_ID 		D_EEP_CANBUS_ID
#define D_EEP_UDSDTC_ADDR    D_EEP_CANBUS_ADDR
#define D_EEP_UDSDTC_LEN      	D_EEP_CANBUS_LEN
#endif


//#define D_EEP_TRACK_ID            5
//#define D_EEP_REV_TRACK_ADDR    (D_EEP_TPMS_ADDR + D_EEP_PAGE_LEN*((D_EEP_TPMS_LEN/D_EEP_PAGE_LEN) + (1&&(D_EEP_TPMS_LEN%D_EEP_PAGE_LEN))))
//#define D_EEP_REV_TRACK_LEN       (BACK_TRACK_DATA_LENTH)

/* If you add a block,please updata this difine like this :*/
/* MAX(D1,MAX(D2,MAX(D3,MAX(D4,...))))                     */
//#define D_MAX_BUFF_LEN           MAX(D_EEP_SYSSETDATA_LEN,MAX(D_EEP_SYSDATA_LEN,MAX(D_EEP_SWCDATA_LEN,MAX(D_EEP_AUDIO_LEN,D_EEP_TPMS_LEN ))))
#define D_MAX_BUFF_LEN1          MAX(D_EEP_SYSSETDATA_LEN,D_EEP_SYSDATA_LEN) 
#define D_MAX_BUFF_LEN2          MAX(D_MAX_BUFF_LEN1,D_EEP_SWCDATA_LEN) 
#define D_MAX_BUFF_LEN3          MAX(D_MAX_BUFF_LEN2,D_EEP_AUDIO_LEN) 
#define D_MAX_BUFF_LEN4           MAX(D_MAX_BUFF_LEN3,D_EEP_CANBUS_LEN)
#define D_MAX_BUFF_LEN			MAX(D_MAX_BUFF_LEN4,D_EEP_UDSDTC_LEN)

/*******************************************************************************
Use EEP service:
1: Create data block
#pragma section data "no_init" begin
uint8_t l_cTestData[121]; You data must be placed into "no_init" ram block.It's 
                          include 2 bytes checksum and 119 bytes data
#pragma section data "no_init" end


tEEP_DATA_BLOCK l_tEepTestCB;
const tEEP_DATA lc_tEepTestCB = {
    &l_cTestData,&l_iTestChk,NULL,0xA0,121
};

EEP_CreateEepDataBlock(&l_tEepTestCB,&lc_tEepTestCB);

2: Read: 
 Run EEP_ReadStart function,than put EEP_WaitOptionReturn in your function loop to check retrun value
3: Write:
 Run EEP_ReadStart function,if you want to wait Write return value, put EEP_WaitOptionReturn in your function loop to check retrun value


*******************************************************************************/

_EEP_  tTASK_CTRL_BLOCK g_tEepTaskCB;

#define _SendMsgToEEP(gid,sid,buf)  OS_PostMsgDir(&g_tEepTaskCB,(uint16_t)(gid),(uint16_t)(sid),(void*)(buf))

_EEP_  eEEPROM_ERROR   EEP_Write(uint16_t addr,uint8_t* p_cBuf,uint16_t iLen,uint8_t* p_cRet);
_EEP_  eEEPROM_ERROR   EEP_Read(uint16_t addr,uint8_t* p_cBuf,uint16_t iLen,uint8_t* p_cRet);

/*******************************************************************************
 *
 * @Function EEP_TaskCreate
 * @brief       Create the eeprom option task.
 * @param     none        
 * @retval     eTASK_ERROR ,see it's defination
 *
 *******************************************************************************/
_EEP_  uint8_t         EEP_TaskCreate(void);


/*******************************************************************************
 *
 * @Function EEP_CreateEepDataBlock
 * @brief       Create a eeprom data block.
 * @param     p_tEepBlock      data block ram point
                   p_tData            define the data attribute
 * @retval     eEEP_DATA_STATE ,see it's defination
 *
 *******************************************************************************/
_EEP_  eEEP_DATA_STATE EEP_CreateEepDataBlock(tEEP_DATA_BLOCK* p_tEepBlock,const tEEP_DATA * p_tData);

/*******************************************************************************
 *
 * @Function EEP_BlockCheck
 * @brief       verify the data and check_sum.
 * @param     p_tEepBlock      data block ram point
 * @retval     1:verify succesfully 0:failed
 *
 *******************************************************************************/
_EEP_  bool            EEP_BlockCheck        (tEEP_DATA_BLOCK* p_tEepBlock);

/*******************************************************************************
 *
 * @Function EEP_BlockEdit   
 * @brief       Edit a member value in the data block.
 * @param     p_tEepBlock      data block ram point
                   iOffSet              the member's position offset
                   cValue              the value will be set!
 * @retval     1:set succesfully 0:failed,my be this block is being writed now.
 *
 *******************************************************************************/
_EEP_  bool            EEP_BlockEdit         (tEEP_DATA_BLOCK* p_tEepBlock,uint16_t iOffSet,uint8_t cValue);

/*******************************************************************************
 *
 * @Function EEP_BlockLoadDefault   
 * @brief       load the block's default value
 * @param     p_tEepBlock      data block ram point
 * @retval     none
 *
 *******************************************************************************/
_EEP_  void            EEP_BlockLoadDefault  (tEEP_DATA_BLOCK* p_tEepBlock);

/*******************************************************************************
 *
 * @Function EEP_CreateBlockChkSum   
 * @brief       block's member is set,so you will set the new check_sum
 * @param     p_tEepBlock      data block ram point
 * @retval     none
 *
 *******************************************************************************/
_EEP_  void            EEP_CreateBlockChkSum (tEEP_DATA_BLOCK* p_tEepBlock);

/*******************************************************************************
 *
 * @Function EEP_ReadStart   
 * @brief       Start to read a block
 * @param     p_tEepBlock      data block ram point
 * @retval     1:succes  0:faile
 *
 *******************************************************************************/
_EEP_  bool            EEP_ReadStart         (tEEP_DATA_BLOCK* p_tEepBlock);

/*******************************************************************************
 *
 * @Function EEP_WriteStart   
 * @brief       block's member is set,so you will set the new check_sum
 * @param     p_tEepBlock      data block ram point
 *            iWaitTime        the eeprom option will be executed after this timing
 * @retval     1:succes  0:faile
 *
 *******************************************************************************/
_EEP_  bool            EEP_WriteStart        (tEEP_DATA_BLOCK* p_tEepBlock,uint16_t iWaitTime);

/*******************************************************************************
 *
 * @Function EEP_WaitOptionReturn   
 * @brief       Wait for the option result.
 * @param     p_tEepBlock      data block ram point
 *                 iOvfTime         if can't get a valid result in this timing,return timeout 
 * @retval     eEEP_OPTION_RET.  if the result is greater than EEP_OPTION_COMPLETE
                                                               EEP_OPTION_READ_COMPLETE
                                                               EEP_OPTION_WRITE_COMPLETE
 *                                            it means eeprom option is finish!
 
 *
 *******************************************************************************/
_EEP_  eEEP_OPTION_RET EEP_WaitOptionReturn  (tEEP_DATA_BLOCK* p_tEepBlock,uint16_t iOvfTime);

#endif

