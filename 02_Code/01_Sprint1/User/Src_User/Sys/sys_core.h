#ifndef _SRC_CORE_H_
#define _SRC_CORE_H_

#ifdef _SRC_CORE_C_
#define _SRC_CORE_
#else
#define _SRC_CORE_ extern
#endif



typedef enum {
    SOURCE_TUNER        = 0,
    SOURCE_DVD            = 1,    //Disc use one button on MainMenu.
    SOURCE_CDBOX            = 2,	// CD-BOX use this source
    SOURCE_TV            = 3,    //ATV
    SOURCE_NAVI            = 4,
    SOURCE_R_AUX        = 5,    //Rear AuxIn(Aux2)
    SOURCE_DTV            = 6,    //CMMB or DVBT,etc Digital TV.
    SOURCE_SD            = 7,    //SD use one button on MainMenu.
    SOURCE_XM            = 8,
    SOURCE_IPOD            = 9,    //iPod use one button on MainMenu.
    SOURCE_USB            = 10,    //USB use one button on MainMenu.
    SOURCE_CAMERA        = 11,
    SOURCE_F_AUX        = 12,    //Front AuxIn(Aux1)
    SOURCE_BT_MUSIC    = 13,     
    SOURCE_SIRIUS        = 14,
    SOURCE_HDRADIO        = 15,
    SOURCE_PANDORA        = 16,    
    SOURCE_THIRD_APP        = 17,    //Install applications which always need audio channel are all called SOURCE_THIRD_APP.
    SOURCE_AVOFF        = 18,    //System enter into Standby mode with clock GUI display.
    SOURCE_MHL          = 19,
    SOURCE_MIRROR_LINK  = 20,
    SOURCE_SYS_STANDBY  = 21,
    SOURCE_TBOX    = 22,
    SOURCE_RES_IN       = 23,
    SOURCE_DVR             =24,
    SOURCE_TTS		   =25,
    SOURCE_BT                =26,
    //If Disc/iPod/USB/SD were separated Audio/Video/Image, 
    //use the follow source id to replace SOURCE_DVD/SOURCE_IPOD/SOURCE_USB/SOURCE_SD
    SOURCE_DISC_AUDIO    = 30,
    SOURCE_DISC_VIDEO    = 31,
    SOURCE_DISC_IMAGE    = 32,
    SOURCE_IPOD_AUDIO    = 33,
    SOURCE_IPOD_VIDEO    = 34,
    SOURCE_USB_AUDIO    = 35,
    SOURCE_USB_VIDEO    = 36,
    SOURCE_USB_IMAGE    = 37,
    SOURCE_SD_AUDIO        = 38,
    SOURCE_SD_VIDEO        = 39,
    SOURCE_SD_IMAGE        = 40,

    SOURCE_CAR_SYNC        = 45,    //Ford Sync
    SOURCE_CAR_MEDIA    = 46,    //Original USB,iPod,Aux,BT phone, BT Music, etc
    SOURCE_CAR_CDC        = 47,    //Original CDC
    SOURCE_CAR_TUNER    = 48,    //Original Tuner
    SOURCE_ON_STAR        = 49,    //GM OnStar
    
    SOURCE_NUM            = 50,  // ²»ÇÐ»»Ô´
    SOURCE_N
}eSOURCE_ID;     //It Must by same as MPEG/Wince Setting



/*Source's id use in mcu interal system*/
typedef enum {
    SRC_TYPE_TUNER,
    SRC_TYPE_DVD,     
    SRC_TYPE_CDBOX,	// CD-BOX use this source type.
    SRC_TYPE_TV,    
    SRC_TYPE_NAVI,
    SRC_TYPE_R_AUX,  
    SRC_TYPE_DTV,  
    SRC_TYPE_SD ,    //SD use one button on MainMenu.
    SRC_TYPE_XM,
    SRC_TYPE_IPOD,    //iPod use one button on MainMenu.
    SRC_TYPE_USB,    //USB use one button on MainMenu.
    SRC_TYPE_CAMERA,  // Blind View Display
    SRC_TYPE_F_AUX,    //Front AuxIn(Aux1)
    SRC_TYPE_BT_MUSIC,  
    
    SRC_TYPE_SIRIUS,   //14
    SRC_TYPE_HDRADIO,
    SRC_TYPE_PANDORA,    
    SRC_TYPE_THIRD_APP,    //Install applications which always need audio channel are all called SRC_TYPE_THIRD_APP.
    SRC_TYPE_AVOFF,    //System enter into Standby mode with clock GUI display.
    SRC_TYPE_MHL,
    SRC_TYPE_MIRROR_LINK,
    
    SRC_TYPE_SYS_STDBY,
    SRC_TYPE_DVR,              //22
    //If Disc/iPod/USB/SD were separated Audio/Video/Image, 
    //use the follow source id to replace SRC_TYPE_DVD/SRC_TYPE_IPOD/SRC_TYPE_USB/SRC_TYPE_SD
    SRC_TYPE_DISC_AUDIO, 
    SRC_TYPE_DISC_VIDEO,
    SRC_TYPE_DISC_IMAGE,
    SRC_TYPE_IPOD_AUDIO,
    SRC_TYPE_IPOD_VIDEO,
    SRC_TYPE_USB_AUDIO,	//28
    SRC_TYPE_USB_VIDEO,
    SRC_TYPE_USB_IMAGE,
    SRC_TYPE_SD_AUDIO,
    SRC_TYPE_SD_VIDEO,
    SRC_TYPE_SD_IMAGE,
    
    SRC_TYPE_BT_PHONE,   	// 34                         
    SRC_TYPE_3G_PHONE,
    SRC_TYPE_RDS_TA,
    SRC_TYPE_NAVI_AUDIO, //When navi audio is insert_flg
    SRC_TYPE_REVERSE,    // 38

    SRC_TYPE_CAR_SYNC,
    SRC_TYPE_CAR_MEDIA,
    SRC_TYPE_CAR_CDC,
    SRC_TYPE_CAR_TUNER,
    SRC_TYPE_CAR_OnSTAR,

    SRC_TYPE_MONITOR_OFF,
    SRC_TYPE_SLEEP,
    SRC_TYPE_REAR_OFF,
    SRC_TYPE_APP_TONE,
    SRC_TYPE_VR,
    SRC_TYPE_LOGO,
    SRC_TYPE_LOGO_AUDIO,
    SRC_TYPE_RADAR,
    SRC_TYPE_CAR_TBOX, 
    SRC_TYPE_REAR_BOX,
    SRC_TYPE_NAVI_MIX,    //When navi audio is mix_flg
    SRC_TYPE_BIRDVIEW,
    
    SRC_TYPE_NUM

}eSOURCE_TYPE;           

typedef enum{
	SRC_PRI_TOP,
	SRC_PRI_TBOX,
	SRC_PRI_CAM,
	SRC_PRI_LOGO,
	SRC_PRI_BT,

	SRC_PRI_RDS,

	SRC_PRI_FLOAT,
	SRC_PRI_NORMAL,

	SRC_PRI_SYS_STDBY,
	SRC_PRI_NUM
}eSRC_PRIORITY;


/*List type define! Source lists have 4 types*/
/*Do not edit this enum*/
typedef enum{
    SRC_LIST_TOP,
    SRC_LIST_FLOAT,
    SRC_LIST_RUNTIME,
    SRC_LIST_REAR,
    SRC_LIST_SYSTEM,
    
    SRC_LIST_NUM
}eSOURCE_LIST_TYPE;

typedef enum{
    SRC_ZONE_FRONT,
    SRC_ZONE_REAR,
    SRC_ZONE_NUM
}eSOURCE_ZONE;


typedef enum{
    SRC_MSG_IGNORE,
    SRC_MSG_ANALYZE,
    SRC_MSG_PROHIBITE,

    SRC_MSG_RETURN_N
}eSOURCE_MSG_RETURN;


typedef void                (*fSRC_INIT)          (eSOURCE_TYPE);
typedef void                (*fSRC_TASK)          (eSOURCE_TYPE,EVENT,eTASK_STATE);

typedef bool                (*fSRC_IS_VALID)      (eSOURCE_TYPE,eSOURCE_ZONE);
typedef void                (*fSRC_OPTION)        (eSOURCE_TYPE,eSOURCE_ZONE);

typedef eSOURCE_MSG_RETURN  (*fSRC_MSG_FILTER)    (eSOURCE_TYPE,eSOURCE_ZONE,tMSG_BUF*,bool); 
typedef eSOURCE_MSG_RETURN  (*fSRC_GLOBAL_OPTION) (eSOURCE_TYPE,tMSG_BUF*);
typedef void                (*fSRC_DATA_SYNC)     (eSOURCE_TYPE);

/*Source statice attributes*/
#pragma pack(1)
typedef struct{    
    /*function area*/
    const fSRC_INIT            p_fInit;          /*Source's init function*/
    const fSRC_DATA_SYNC       p_fDataSync;      /*Source's data sync_fucntion*/
    const fSRC_TASK            p_fTask;          /*Source's runtime task*/
    
    const fSRC_IS_VALID        p_fIsValid ;      /*Source's is valid in runtime*/
    const fSRC_OPTION          p_fStart ;        /*Source start*/
    const fSRC_OPTION          p_fStop ;         /*Source stop\pause*/
    
    const fSRC_MSG_FILTER      p_fSrcMsgHandle;  /*Source's runtime_msg handle*/
    const fSRC_GLOBAL_OPTION   p_fOption;        /*Source's global option,for example: PM,device info,io info ...*/

}tSOURCE_CTRL_BLOCK;


#pragma pack(1)
typedef union{
    struct{
        bit_t        bRearEn    :1;   /*It can be placed into rear list*/
        bit_t        bFloat     :1;   /*It must placed into float list*/
        bit_t        bAudValid  :1;   /*Source audio is enable to output*/
        bit_t        bVidValid  :1;   /*Source video is enable to output*/
        bit_t        bUIHold    :1;   /*forbid ui switch when run_src is changed!*/
        bit_t        bUpSRC     :1;   /*updata source infomation to apu*/
        bit_t        bHoldMsg   :1;   /*If it is a top src,it will not distribute msg to lower src */
        bit_t        bIgnoreMsg :1;   /*If a higher priority source is existed,this source will ignore all msg distributed by higher src*/  
        bit_t        bBootStart :1;   /*If this src is can be started in boot time.set this flag*/
        bit_t        bStopAll   :1;   /*if this src insert a list,stop all src in this list*/
        bit_t        bIgnoreStop:1;   /*if this bit is 1,not stop the src when insert a bStopAll src*/
        bit_t        bMuteBeep  :1;   /*if this src prohibite some key or other input,it will not output fail beep*/
    }field;
    uint16_t byte;
}tSOURCE_FLG;

#define B_SRC_REAR_EN      _BIT0_
#define B_SRC_FLOAT        _BIT1_
#define B_SRC_AUDVALID     _BIT2_
#define B_SRC_VIDVALID     _BIT3_
#define B_SRC_SW_HOLD      _BIT4_
#define B_SRC_UI_UPDATA    _BIT5_ 
#define B_SRC_HOLD_HMSG    _BIT6_
#define B_SRC_IGNORE_HMSG  _BIT7_
#define B_SRC_BOOT_START   _BIT8_
#define B_SRC_STOP_FLAG    _BIT9_
#define B_SRC_IGNORE_STOP  _BIT10_
#define B_SRC_MUTE_BEEP    _BIT11_

/*Source attributes block,it's can be fixed*/
#pragma pack(1)
typedef struct _source{
    tNODE           tNode;             /*system list node 8B*/
    uint8_t*        p_cRunState;       /*Running state in different list 4B*/
    tSOURCE_FLG     tFlag;             /*Attribute flag 1B*/
    const char*     p_cName;           /*Name string 4B*/
    eSOURCE_TYPE    eSrcType;          /*Type 1B*/
    eSOURCE_ID      eSrcID;            /*UI ID 1B*/
    uint8_t         cPriority;         /*Priority of source 1B*/
    const tSOURCE_CTRL_BLOCK* p_tSCB;  /*Function block 4B*/
}tSOURCE;





#define D_SRC_FLOAT_MAX_NUM  5
#define D_SRC_RUN_MAX_NUM    8
#define D_SRC_HPRI_MAX_NUM   8
#define D_SRC_REAR_MAX_NUM   5





/*******************************************************************************
 * @function SRC_GetListHeadNode
 * @brief  Get the source list entry node point
 * @param      eListType              List type
 * @retval  The entry node point
 *******************************************************************************/ 
_SRC_CORE_ tNODE*     SRC_GetListHeadNode     ( eSOURCE_LIST_TYPE eListType );

/*******************************************************************************
 * @function SRC_ClearSrcList
 * @brief  Clear all sources in the list belong to special type
 * @param      eListType     The target list's type
 * @retval  NONE
 *******************************************************************************/ 
_SRC_CORE_ void       SRC_ClearSrcList        ( eSOURCE_LIST_TYPE eListType);

/*******************************************************************************
 * @function SRC_OperateSrcList
 * @brief  Insert or remove a source in the special list
 * @param      eListType     The target list's type
 *             p_tSrc        target source's point
 *             bInsert      1:Insert 0: remove
 * @retval  NONE
 *******************************************************************************/ 
_SRC_CORE_ void       SRC_OperateSrcList      ( eSOURCE_LIST_TYPE eListType,tSOURCE * p_tSrc,bool bInsert );


/*******************************************************************************
 * @function SRC_OperateSrcList
 * @brief  Insert or remove a source in the special list
 * @param      eListType     The target list's type
 *             p_tSrc        target source's point
 *             bEnable       1:Start Source 0: Stop Source
 * @retval  NONE
 *******************************************************************************/
_SRC_CORE_ void       SRC_Ctrl                ( tSOURCE* p_tSrc,eSOURCE_LIST_TYPE eListType,bool bEnable );

/*******************************************************************************
 * @function SRC_GetCurrentSrcInList
 * @brief  Get the top source's point in the special list. 
 * @param      eListType      The target list's type
 * @retval  Source's point
 *          NULL : source is not existed
 *******************************************************************************/
_SRC_CORE_ tSOURCE*   SRC_GetCurrentSrcInList ( eSOURCE_LIST_TYPE eListType );

/*******************************************************************************
 * @function SRC_GetSysSrcBaseType/SRC_GetSysSrcBaseID
 * @brief   Find the source point in system list,it's type/id is ..
 * @param   eSrcType      The target source's type
 *          eSrcID        The target source's id
 * @retval  Source's point
 *          NULL : source is not existed
 *******************************************************************************/
_SRC_CORE_ tSOURCE*   SRC_GetSysSrcBaseType    ( eSOURCE_TYPE eSrcType );
_SRC_CORE_ tSOURCE*   SRC_GetSysSrcBaseID      ( eSOURCE_ID eSrcID );
_SRC_CORE_ tSOURCE*   SRC_GetSrcBlockBaseType  (eSOURCE_TYPE eSrcType,eSOURCE_LIST_TYPE eListType);


/*******************************************************************************
 * @function SRC_CoreInit
 * @brief   Init all of the source list
 * @param   none
 * @retval  1
 *******************************************************************************/
_SRC_CORE_ bool       SRC_CoreInit             ( void );

/*******************************************************************************
 * @function SRC_Create
 * @brief   Creat a source 
 * @param   .. Source's attribute 
 * @retval  1: success 0: fail
 *******************************************************************************/
_SRC_CORE_ uint8_t    SRC_Create               ( tSOURCE* p_tSrc,  
                                                 eSOURCE_ID eSrcID,   
                                                 eSOURCE_TYPE eSrcType,
                                                 const char* p_cName,
                                                 const tSOURCE_CTRL_BLOCK* p_tSCB,
                                                 uint8_t cPriority,
                                                 uint16_t cFlag,    
                                                 uint8_t* p_cRunState );

#endif

