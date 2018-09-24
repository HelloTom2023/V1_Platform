///////////////////////////////////////////////////////////////////////////////
///////// system task id define ////////////////////////////////////////////////
#define TASK_ID_STOP_LVI_MASK    0x40  //Stop at LVI state
#define TASK_ID_STOP_NOMAL_MASK  0x80  //Stop at sleep and off state
#define TASK_ID_STOP_EN_MASK     (TASK_ID_STOP_NOMAL_MASK|TASK_ID_STOP_LVI_MASK)

#define TASK_ID_IDLE          0
#define TASK_ID_PWR           1
#define TASK_ID_HMI           2

#define TASK_ID_MEDIA         (3)
#define TASK_ID_MEDIA_COMM    (4 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_I2C1          (5 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_I2C2          (6 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_AUDIO         (7 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_VIDEO         (8 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_TUNER         (9 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_EEPROM        (10 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_SOURCE        (11 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_DISC          (12 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_CANBUS        (13 + TASK_ID_STOP_LVI_MASK)
#define TASK_ID_CANBOX        (14 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_TMC           (15 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_BUS            (16 + TASK_ID_STOP_LVI_MASK)
#define TASK_ID_FCT           (17 + TASK_ID_STOP_EN_MASK)
#define TASK_ID_MULT_FUNCTION	(18)//lkm20140321_edit
#define TASK_ID_I2C0                (19 + TASK_ID_STOP_EN_MASK)


//消息汇总。所有模块的消息，都是发送到HMI模块中转。
//消息命名格式



////////////////////////////////////////////////////////////////////////////////
#define MS_GLOBAL_MASK             0xf000 
#define MS_GLOBAL_SRC_DROP         0x8000   /*Src has ignored this msg*/
#define MS_GLOBAL_SRC_ANALYZE      0x9000   /*Src has analyzed this msg*/
#define MS_GLOBAL_SRC_PROHIBITE    0xA000   /*src has prohibited this msg*/


/*Support user's message id: 0~(~MS_GLOBAL_MASK)*/

#define MS_USER_MASK            (~MS_GLOBAL_MASK)
/*******************************************************************************/
typedef enum{
    MS_PM_START,         //0
    MS_PM_SET_STATE,
    MS_PM_STATE,
    MS_PM_AWAKE,            /*Param1:Machine awake from state:SLEEP/LVI/OFF;Param2:eOP_PM_AWAKE_EVENT*/
    MS_PM_TFT_INFO,
    MS_PM_TFT_BL_CMD,		/*TFT back light control */
    MS_PM_TFT_8836,

    MS_PM_END
}eMS_PM;
     
/*PM option*/
typedef enum{
    OP_PM_STATE_INVALID,      /*Invalid state,do nothing in this state*/
    OP_PM_STATE_ON,           /*Power Manager goto ON mode*/
    OP_PM_STATE_RESET,        /*Power Manager goto Reset mode*/
    OP_PM_STATE_STANDBY,      /*Power Manager goto Standby mode*/
    OP_PM_STATE_WAIT_SLEEP,   /*Power Manager goto WaitSleep mode*/
    OP_PM_STATE_SLEEP,        /*Power Manager goto SLEEP mode*/
    OP_PM_STATE_OFF,          /*Power Manager goto OFF mode*/
    OP_PM_STATE_BATERR,       /*Power Manager goto BATTERY Error mode*/
    OP_PM_STATE_ERR,          /*Power Manager goto ERR mode*/
    OP_PM_STATE_LVI,          /*Power Manager goto LVI(Low voltage interrupt) mode*/
    OP_PM_STATE_N
}eOP_PM_STATE;


typedef enum{
    OP_PM_AWAKE_NONE,
    OP_PM_AWAKE_ACC,
    OP_PM_AWAKE_PWRKEY,
    OP_PM_AWAKE_EJCKEY,
    OP_PM_AWAKE_DISCIN,

    
    OP_PM_AWAKE_BAT_ERR,
	OP_PM_AWAKE_ILL,//snake20160922
	
    OP_PM_AWAKE_EVT_N
}eOP_PM_AWAKE_EVENT;
/*******************************************************************************/

typedef enum{
    MS_UI_START   = MS_PM_END,    //7
    MS_UI_CMD,         
    MS_UI_SETTING,
    MS_UI_DOWNLOAD_INFO,
    MS_UI_UPLOAD_INFO,
    MS_UI_END
}eMS_UI;

/*Reference the media_msg.h */

/*******************************************************************************/
typedef enum{
    MS_INPUT_START    = MS_UI_END,  //12
    MS_INPUT_KEY,
    MS_INPUT_FIR,
    MS_INPUT_RIR,
    MS_INPUT_SWC,
    MS_INPUT_BUS,
    MS_INPUT_UI,
    MS_INPUT_TOUCH,
    MS_INPUT_REQDATA,
    MS_INPUT_APU_DEBUG_DATA,
    MS_INPUT_END
}eMS_INPUT;

/*key option*/
typedef enum{
    OP_KEY_ACTION_NONE ,      /* 0 Key action option  按键激活选项  */
    OP_KEY_ACTION_SP,         /*1 Key only included short press attribute is short pressed  短按键*/
    OP_KEY_ACTION_LP,         /*2 Key included long press attribute is long pressed 长按键  */
    OP_KEY_ACTION_SH,         /*3 Key only included short press attribute is hold pressed  短按保持*/
    OP_KEY_ACTION_LH ,        /*4 Key included long press attribute is hold pressed 长按保持  */
    OP_KEY_ACTION_LSP,        /*5 Key included long press attribute is short pressed 长按键在短按阶段   */
    OP_KEY_ACTION_SREL,       /*6 Key only included short press attribute is released after a short pressing  短按键功能生效之后释放  */
    OP_KEY_ACTION_SHREL,      /*7 Key only included short press attribute is released after a hold pressing 短按键功能生效之后保持了一段时间之后才释放的   */
    OP_KEY_ACTION_LREL,       /*8 Key included long press attribute is released after a long pressing   长按键功能生效之后释放  */
    OP_KEY_ACTION_LHREL,      /*9 Key included long press attribute is released after a hold pressing 长按键功能生效之后保持了一段时间之后才释放的   */
    OP_KEY_ACTION_LSREL,      /*10 Key included long press attribute is released after a short pressing长按键短按之后释放  */
    OP_ENCODE_TURN_LEFT,      /*11 Encode is turned left in one step*/
    OP_ENCODE_TURN_RIGHT,     /*12 Encode is turned right in one step*/

    OP_INPUT_N
}eOP_INPUT;
/*******************************************************************************/

typedef enum{
    MS_SYS_START  = MS_INPUT_END,   //20
    MS_SYS_DEV_TYPE,          /*System check devices(eSYS_DEV_IDX) itself.param1:eSYS_DEV_IDX param2: Devies type define*/
    MS_SYS_DEV_STATE,         /*Device(eSYS_DEV_IDX) state,param1:eSYS_DEV_IDX param2:eOP_DEV_STATE_TYPE Param3~4:define youself!*/
    MS_SYS_IO_INFO,           /*IO Device(IO_IDX_xxx) state,param1:io_idx param2:0/1 IO state*/
    MS_SYS_BUS_INFO,          /*Bus power state info,paramS:eOP_PM_STATE */
    MS_SYS_BUS_IO_INFO,       /*IO state based on BUS*/
    MS_SYS_DISC_INFO,         /*DISC state,param:eOP_DEV_STATE_TYPE,OP_DEV_STATE_AUTO = EJECT*/
    MS_SYS_APU_INFO,          /*APU state,param:eOP_DEV_STATE_TYPE*/
    MS_SYS_DEV_ON_APU_INFO,   /*Device on CPU state,param1:eSYS_DEV_IDX param2:eOP_DEV_STATE_TYPE Param3~4:define youself!*/
    MS_SYS_DEV_ON_MCU_INFO,   /*Device on MCU state(eMCU_DEV_IDX),param1:eMCU_DEV_IDX param2:eOP_DEV_STATE_TYPE Param3~4:define youself!*/
    MS_SYS_AUDIO_STATE,       /*Audio system state,Param1:eOP_DEV_STATE_TYPE*/
    MS_SYS_VIDEO_STATE,       /*video system state,Param1:eOP_DEV_STATE_TYPE*/
    MS_SYS_LOAD_FACTORY_INFO, /*Load default */
    
    MS_SYS_END
}eMS_SYS;

typedef enum{
    MCU_DEV_IDX_IO,
    MCU_DEV_IDX_UART,
    MCU_DEV_IDX_ADC,
    MCU_DEV_IDX_IIC,
    MCU_DEV_IDX_SPI,
    MCU_DEV_IDX_VPP,


    MCU_DEV_IDX_N
    
}eMCU_DEV_IDX;


typedef enum{
   OP_DEV_STATE_OFF,          /*device Off*/
   OP_DEV_STATE_NOCONNECT,    /*device is starting or ... not monted in sys yet*/
   OP_DEV_STATE_CONNECTED,    /*decice connected into sys*/
   OP_DEV_STATE_LOCK,         /*device is locked*/
   OP_DEV_STATE_NORMAL,       /*device is running normaly*/
   OP_DEV_STATE_SLEEP,        /*device is sleeped.*/

   OP_DEV_STATE_AUTO,         /*device run auto or defined by itself. */
   OP_DEV_STATE_TEST,         /*device is in testing state*/
   OP_DEV_STATE_UPDATA,       /*device is updating it's sw*/
   OP_DEV_STATE_ERR,          /*device is error*/
   OP_DEV_STATE_RESET,        /*device will be reseted*/
   OP_DEV_STATE_SLEEP_READY,
 //  --------------------------------
   OP_DEV_STATE_LINKREQ,
   OP_DEV_STATE_ENTER,
   OP_DEV_STATE_BOOTOK,
   OP_DEV_STATE_POWERON,
   OP_DEV_STATE_POWEROFF,
   OP_DEV_STATE_N
}eOP_DEV_STATE_TYPE;





typedef enum{
   
   DEV_IDX_APU,             /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_TUNER,           /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_AUDIOSWICHER,    /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_ATV,             /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_AMP,             /*0:NO Chip 0x01~0xXX:define*/
   
   DEV_IDX_SPEAK,           /*2 Bits define a state*/  
   DEV_IDX_EEPROM,          /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_TMC,             /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_CANADP,          /*0:NO device 0x01~0xXX:define*/
   DEV_IDX_HEADPLAYER,      /*0:NO device 0x01~0xXX:define*/
   DEV_IDX_ANT,             /*0:NO Speak 1:Error 2:Normal*/
   
   DEV_IDX_BT,              /*0:NO device 0x01~0xXX:define*/
   DEV_IDX_VIDSWITHER,      /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_DTV,             /*0:NO device 0x01~0xXX:define*/
   DEV_IDX_IPOD2DOT0,       /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_MHL,             /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_TBOX,            /*0:NO device 0x01~0xXX:define*/
   DEV_IDX_WIFI,            /*0:NO Chip/Chip OFF 0x01~0xXX:define,Chip ON*/
   DEV_IDX_TRIG,            /*0:NO Chip 0x01~0xXX:define*/
   DEV_IDX_MPEG,            /*0:NO device 0x01~0xXX:define*/
   
   DEV_IDX_BATTERY,         /*0xXX    Voltage value*/
   DEV_IDX_SWC,             /*0:NO use 0x01~.. The vehicel type!*/
   DEV_IDX_RADAR,           /*0:No device 0xXX:user define*/
   
   DEV_IDX_N
}eSYS_DEV_IDX;


/*******************************************************************************/

typedef enum{
    MS_SRC_START        = MS_SYS_END,      //33    
    MS_SRC_SYS_CMD,            /*Source system CMD.*/
    MS_SRC_DISTRIBUTE_CMD,     /*Cmd is not be translated by src sys_filter,distribute to all source */
    MS_SRC_SETTING,            /*Source setting*/
    MS_SRC_UPLOAD_INFO,        /*Source info whith will be updated to APU*/
    
    MS_SRC_SET_FRONT_UIID,     /*Set the front source based to set id*/
    MS_SRC_SET_REAR_UIID,      /*Set the rear source based to set id*/
    
    MS_SRC_SET_TOP_TYPE,       /*Set the top source based to set type. Param1: Src_type Param2:0/1=Clear/Set*/
    MS_SRC_SET_FLOAT_TYPE,       /*Set the overlay source based to set type.Param1: Src_type Param2:0/1=Clear/Set*/
    MS_SRC_SET_FRONT_TYPE,     /*Set the front source based to set type*/
    MS_SRC_SET_REAR_TYPE,      /*Set the rear source based to set type*/
    
    MS_SRC_END
}eMS_SRC;


typedef enum{
    OP_SRC_DATA_SYNC,        /*Sync data to CPU*/
    OP_SRC_FORCE_SW,         /*Force to initiate a sorce switching , and upload source id to cpu*/
    
    OP_SRC_SW_START,         /*Source switch start*/
    OP_SRC_SW_FINISH,        /*Source switch finish*/
    OP_SRC_SW_FAIL,          /*Source switch fail*/

    OP_SRC_LIST_ACTION,      /*A list insert or delet action is occured param1: list_type,p2:LastSrcType,P3:TargetSrcType*/
    OP_SRC_AUTO_NEXT,        /*Auto switch to next src*/
    
    OP_SRC_N
}eOP_SRC_CMD;

/*******************************************************************************/
typedef enum{
    MS_AUDIO_START       = MS_SRC_END,  //44
    MS_AUDIO_CMD,            /*Aud cmd,example: vol+,vol-,mute....refer to OP_AUDIO_...*/
    MS_AUDIO_SETTING,        /*Aud setting , exa EQ...*/
    MS_AUDIO_UPLOAD_INFO,    /*Upload the audio info to APU*/
    MS_AUDIO_SET_OCH,        /*Set the source as the output channal*/
    MS_AUDIO_SET_ICH,        /*Set the source as the input channal*/
    MS_AUDIO_IOCH_MAP,       /*Set the output/input channal,exa input channal A will be output on output_channal B*/
    
    MS_AUDIO_END
}eMS_AUDIO;

/*Reference the Audio_msg.h */


/*******************************************************************************/
/*Refer to eMS_AUD*/
typedef enum{
    MS_VIDEO_START       = MS_AUDIO_END,//51
    MS_VIDEO_CMD,
    MS_VIDEO_SETTING,
    MS_VIDEO_UPLOAD_INFO,
    MS_VIDEO_SET_OCH,
    MS_VIDEO_SET_ICH,
    MS_VIDEO_IOCH_MAP,

    MS_VIDEO_END
}eMS_VIDEO;

/*******************************************************************************/
/*refer to eMS_VIDEO*/
typedef enum{
    MS_HMI_START =     MS_VIDEO_END,//58
    MS_HMI_KEY_SETTING,
    MS_HMI_SWC_SETTING,
    MS_HMI_UI_SETTING,
    MS_HMI_IR_SETTING,
    MS_HMI_ENCODE_SETTING,
    MS_HMI_CAN_SETTING,
    MS_HMI_BUS_SETTING,

    MS_HMI_END
    
}eMS_HMI;


typedef enum{
    MS_EEP_START = MS_HMI_END,//66
    MS_EEP_LOAD_DEFAULT,  /*Other->EEP*/
    MS_EEP_READ_START,    /*Other->EEP*/
    MS_EEP_WRITE_START,   /*Other->EEP*/
    MS_EEP_LOAD_FACTORY,  /*Other->EEP*/

    MS_EEP_READ_RET,      /*EEP->Other  param-->EEP_OPTION_RET*/
    MS_EEP_WRITE_RET,     /*EEP->Other  param-->EEP_OPTION_RET*/
    MS_EEP_LOAD_FACT_RET, /*EEP->Other  param-->EEP_OPTION_RET*/

    MS_EEP_END,
    
}eMS_EEP;
/*******************************************************************************/
/*  BUS_ADP 模块发送给HMI的消息  */
/********************************************************************************/
typedef enum
{
    COM_BUSADP_START_GID0 =  MS_EEP_END ,//74
        
    COM_HANDSHAKE_GID1,            //????????ID
    COM_NULL_GID2,
    COM_CAR_STATUS_GID3,            //??????
    COM_CAR_CONTROL_GID4,        //??????
    COM_CHAR_DISP_GID5,            //????????
    COM_AIR_DISP_GID6,            //????ID
    COM_RADIO_GID7,                //????ID
    COM_CD_GID8,                    //??CD ID
    COM_IPOD_USB_GID9,            //??IPOD/USB?????
    COM_RADER_TPMS_GID10,        //?????????
    COM_BT_GID11,                    //????ID
    COM_STEER_GID12,                //????????
    COM_TIME_DISP_GID13,            //????????
    COM_CAR_AMP_GID14,            //????????
    COM_CAR_SET_GID15,            //GM??????
    COM_ONSTART_GID16,            //?????
    COM_SYNC_GID17,                //SYNC??
    COM_CAR_FACTORY_GID18,        //CAR_FACTORY??
    COM_360_BIRD_VIEW ,        // ??
    COM_BUSADP_END_GID1,             // 
    APU2HMI_BUS_ADP_GID80,
    BUS_ADP_IAP_GID0XE7  ,             //IAP????

    COM_MCU2APP_ADD_GID  , 
    COM_BUSADP_END_GID,
}BM2BA_ComID;

/*******************************************************************************/
/*  HMI 模块发送给BUS_ADP的消息  */
/********************************************************************************/
typedef enum
{
    APU2BA_START_GID = COM_BUSADP_END_GID,//98
    APU2BA_HMI_MSG_TO_BUS ,
    APU2BA_END_GID ,
}tAPU2MCU2BUS_COM;


/*******************************************************************************/
/*  FCT  模块发送给HMI的消息  */
/********************************************************************************/

typedef enum  fct_to_hmi_msg_enum
{
    OP_FCT_TO_HMI_START = APU2BA_END_GID ,//100
    OP_FCT_SOURCE_1 ,   //0x4f
    OP_FCT_FUNCTION_2 ,
    OP_FCT_MEDIA_3 ,
    OP_FCT_RADIO_4 ,
    OP_FCT_BT_5 ,
    OP_FCT_GPS_6 ,
    OP_FCT_KEY_7 ,
    OP_FCT_TMPS_8 ,
    OP_FCT_VOLUME_SET_9 ,
    OP_FCT_FAN_TEST_10 ,
    OP_FCT_AUDIO_SET_11 ,
    OP_FCT_VIDEO_SET_12 ,
    OP_FCT_WIFI_LINK_13 ,
    OP_FCT_BUS_14 ,
    OP_FCT_CUR_STATE_15 ,
    OP_FCT_E_DOG_16 ,
    OP_FCT_SEQ_NUM_17 ,
    OP_FCT_SOFT_VER_18 ,
    OP_FCT_APU_TX_RESULT  ,
    OP_FCT_TO_HMI_END,

}TO_PC_GLOBAL_ID;


/*******************************************************************************/
 /* 倒车轨迹 + 胎压*/
/*******************************************************************************/
 typedef enum
{
    LMS_TPMS_CMD_START = OP_FCT_TO_HMI_END   ,//120
    LMS_TPMS_CMD    ,        //        0x01    //WINCE --> MCU
    LMS_TPMS_UPLOAD ,        //        0x02    //MCU --> WINCE
    LMS_TPMS_CMD_END    ,
};


#ifdef D_CODE_FOR_JX			/*JiangXi HBS defined*/

typedef enum{
	MS_OTHER_START = LMS_TPMS_CMD_END,               //MS_VIDEO_END,//123
	MS_OTHER_VOLTAGE,
	MS_OTHER_AVM,
	MS_OTHER_END
}eMS_OTHER;

typedef enum{
	OP_OTHER_GO_LV,		/*from normal enter Low Voltage */
	OP_OTHER_EXIT_LV,		/*from Low Voltate enter normal state */
	OP_OTHER_GO_HV,		/*from normal enter High Voltage */
	OP_OTHER_EXIT_HV,		/*from High Voltage enter normal state */
	OP_OTHER_A,		/*(down) normal */
	OP_OTHER_B,		/*(down) close screen */
	OP_OTHER_C,		/*(down) close bus, LVI */
	OP_OTHER_D,		/*(up) before open bus */
	OP_OTHER_E,		/*(up) open bus*/
	OP_OTHER_F,		/*(up) open screen, enter normal */
	OP_OTHER_G,		/*(down) HVI, over 17.6V */
	OP_OTHER_H,		/*(up) enter HVI, over 18V*/
	OP_AVM_PRESS,
	OP_AVM_RELEASE,
	OP_OTHER_END,			/*over defination */
}eOP_OTHER_CMD;

#endif

