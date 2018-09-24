 #ifndef  FCT_MSG_H 
 #define  FCT_MSG_H 
#if 0
typedef enum  fct_to_PC_msg_enum
{
    OP_FCT_TO_HMI_START,
    OP_FCT_SOURCE_1 ,
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
    OP_FCT_TO_HMI_END,
    //OP_FCT_ACK_127 = 127,
    //OP_FCT_PASSWORD_128 = 128 ,
}TO_PC_GLOBAL_ID;

#endif
//OP_FCT_SOURCE_1 
#define SOURCE_SW                1  /*1 源类型切换   */

//OP_FCT_FUNCTION_2 
#define FUNCTION_SW                1  /*2 功能切换   */

//OP_FCT_MEDIA_3 
#define MEDIA_CONTROL            1  /*多媒体控制   */
#define SELECTED_SONG            1  /*3 选择指定歌曲   */
#define MEDIA_51_TRACK_SW        2  /*5 5.1声道切换   */
#define MEDIA_SEEK                3  /*4 媒体搜素功能   */

//OP_FCT_RADIO_4 
#define SELECTED_FM_OR_AM        1  /*6 选择FM 或AM  */
#define SELECTED_PRESET            2  /*7 选择预存台 */
#define RADIO_SEEK                3  /*8 RADIO  搜素功能 */
#define SET_FREQ                    4  /*9 设置指定频点  */
#define RDS_SATE                    5  /*10 RDS状态 */
#define RETURN_CUR_FREQ	6  /*11 返回当前频点  */
#define STEREO_MONO_SW		7  /*立体声单声道切换  */
#define DX_LOC_SW			8  /* 远  程台，近程台切换  */



//OP_FCT_BT_5 
#define BT_SW    1  /*12 配对界面  */
#define RET_MAC_ADDRESS            2  /*13 请求MAC地址  */
#define RET_LINK_STATE           3  /*15 返回连接状态   */
#define RET_WRITE_BT_NAME        4  /*14 改写车机蓝牙名称  */
#define RET_VER_ADD_NAME    5  /*16 返回蓝牙版本，MAC地址，名称   */
#define PLAY_MUICE_BT            6  /*17 蓝牙音乐播放  */
#define DIAL_UP                     7  /*18 拨号  */
#define RF_QUALITY                8  /*19 返回RF信号强度   */

//OP_FCT_GPS_6 
#define LONGITUDE_LATITUDE        1  /*20 经纬度   */
#define SIMULATE_NAV            2  /*21 模拟导航   */
#define RET_INFO                    3  /*22 依次返回信号强度: 卫星颗数，内置FLASH已占用容量，
                                    主机当前所处的经纬度  */
#define RET_INERTIA_NAV_INFO    4  /*23 返回惯性导航信息:角速度，加速度   */
#define CHECK_TMC_INFO            5  /*24 检测TMC信息   */

//OP_FCT_KEY_7 
#define RET_KEY_VAL                1  /*25 返回按键值(方向盘，面板按键)   */


//OP_FCT_TMPS_8 
#define PARTNERSHIP_RET_INFO    1  /*26 配对并返回四个传感器的信息 */


//OP_FCT_VOLUME_SET_9 
#define SET_SYS_VOLUME            1  /*27 设置系统音量   */

//OP_FCT_FAN_TEST_10 
#define FAN_SW                    1  /*28 风扇开关   */
#define FAN_GEAR                    2  /*29  风扇档位  */

//OP_FCT_AUDIO_SET_11 
#define AUDIO_SET                1  /*30 设置音频信息   */

//OP_FCT_VIDEO_SET_12 
#define VIDEO_SET                1  /*31 设置视频信息   */

//OP_FCT_WIFI_LINK_13 
#define WIFI_SW                1  /*WIFI模块开 */
#define WIFI_LINK_AP        2  /*32 连接到AP   */
#define WIFI_SIGNAL_INTENSITY    3  /*33 信号强度  */

//OP_FCT_BUS_14 
#define BUS_ILL                    1  /*35 总线ILL   */
#define BUS_ACC                    2  /*34 总线ACC   */
#define BUS_KEY                    3  /*36 总线KEY   */

//OP_FCT_CUR_STATE_15 
#define CUR_STATE                1  /*37 依次返回当前音量值，工作模式，机器温度   */

//OP_FCT_E_DOG_16 
#define E_DOG                    1  /*38 电子狗   */

//OP_FCT_SEQ_NUM_17 
#define SEQ_NUM                    1  /*39 序列号  */

//OP_FCT_SOFT_VER_18 
#define SOFT_OS_VER                1  /*OS 软件版本*/
#define SOFT_BOOT_VER            2  /*BOOT 软件版本*/
#define SOFT_APP_VER            3  /*APP 软件版本*/
#define SOFT_MCU_VER            4  /*MCU 软件版本*/
#define SOFT_MPEG_VER            5  /*MPEG 软件版本*/
#define SOFT_MAP_VER            6  /*MAP 软件版本*/
#define SOFT_DIVX_VER            7  /*DIVX 软件版本*/
#define SOFT_UUID_VER            8  /*UUID 软件版本*/
#define SOFT_WIFI_MAC_VER        9  /*WIFI_MAC 软件版本*/


#define OP_FCT_ACK_127               127 
#define ACK_OK                        0  /*消息正确   */
#define ACK_COM_NOT_DEFINE            1  /*消息错误指令功能未定义   */
#define ACK_SUB_COM_NOT_DEFINE    2  /*消息错误指令子功能未定义   */
#define ACK_CRC_ERROR                3  /*消息错误 校验和出错  */
#define ACK_DATA_FRAME_ERROR        4  /*消息错误数据包错误   */


#define OP_FCT_PASSWORD_128      128
#define FCT_START                1  /*FCT 开始 测试   */
#define FCT_OVER                    2  /*FCT 结束测试   */

#if 0
#define OMS_OP_FCT_SOURCE_1        ((HMS_FCT_PART<<8)|OP_FCT_SOURCE_1)
#define OMS_OP_FCT_FUNCTION_2         ((HMS_FCT_PART<<8)|OP_FCT_FUNCTION_2)
#define OMS_OP_FCT_MEDIA_3          ((HMS_FCT_PART<<8)|OP_FCT_MEDIA_3)
#define OMS_OP_FCT_RADIO_4          ((HMS_FCT_PART<<8)|OP_FCT_RADIO_4)
#define OMS_OP_FCT_BT_5              ((HMS_FCT_PART<<8)|OP_FCT_BT_5)
#define OMS_OP_FCT_GPS_6              ((HMS_FCT_PART<<8)|OP_FCT_GPS_6)
#define OMS_OP_FCT_KEY_7              ((HMS_FCT_PART<<8)|OP_FCT_KEY_7)
#define OMS_OP_FCT_TMPS_8              ((HMS_FCT_PART<<8)|OP_FCT_TMPS_8)
#define OMS_OP_FCT_VOLUME_SET_9      ((HMS_FCT_PART<<8)|OP_FCT_VOLUME_SET_9)
#define OMS_OP_FCT_FAN_TEST_10      ((HMS_FCT_PART<<8)|OP_FCT_FAN_TEST_10)
#define OMS_OP_FCT_AUDIO_SET_11      ((HMS_FCT_PART<<8)|OP_FCT_AUDIO_SET_11)
#define OMS_OP_FCT_VIDEO_SET_12      ((HMS_FCT_PART<<8)|OP_FCT_VIDEO_SET_12)
#define OMS_OP_FCT_WIFI_LINK_13      ((HMS_FCT_PART<<8)|OP_FCT_WIFI_LINK_13)
#define OMS_OP_FCT_BUS_14              ((HMS_FCT_PART<<8)|OP_FCT_BUS_14)
#define OMS_OP_FCT_CUR_STATE_15      ((HMS_FCT_PART<<8)|OP_FCT_CUR_STATE_15)
#define OMS_OP_FCT_E_DOG_16          ((HMS_FCT_PART<<8)|OP_FCT_E_DOG_16)
#define OMS_OP_FCT_SEQ_NUM_17      ((HMS_FCT_PART<<8)|OP_FCT_SEQ_NUM_17)
#define OMS_OP_FCT_SOFT_VER_18      ((HMS_FCT_PART<<8)|OP_FCT_SOFT_VER_18)
#endif
typedef  enum ApuFctComTXType
{
	APU_FCT_TEST_START = 0x01,
	APU_FCT_TEST_FINISHED,
	APU_FCT_LOAD_FACTORY,
}APU_FCT_COM_TX_TYPE;

typedef enum ApuFctFuncSw
{
	APU_FCT_FUNC_EXIT,
	APU_FCT_FUNC_ENTER,
}APU_FCT_FUNC_SW;

 enum 
{
	APU_FCT_FUNC_SWC,
	APU_FCT_FUNC_REVERSE,
	APU_FCT_FUNC_TPMS ,
	APU_FCT_FUNC_BT ,
	APU_FCT_FUNC_SET ,
	APU_FCT_FUNC_ONE_KEY ,
	APU_FCT_FUNC_VR ,
	APU_FCT_FUNC_RESET ,
	APU_FCT_FUNC_SCREEN_ADJ ,
	APU_FCT_FUNC_WIFI ,
	APU_FCT_FUNC_KEY ,
	APU_FCT_FUNC_E_DOG ,
	APU_FCT_FUNC_MAX ,
};



/* 源切换  */
#define MCU_TX_FCT_COM     1

/* 功能切换  */
#define MCU_TX_FCT_FUNC_SWITCH     2

/* 多媒体控制*/
#define MCU_TX_FCT_MEDIA_CTL          3
#define APU_FCT_SEL_TRACK			1
#define APU_FCT_2CH_AND_6CH_SW	2
#define APU_FCT_DVD_SCREEN_SCALE	3

/* BT 测试*/
#define MCU_TX_FCT_BT_TEST          4
#define APU_FCT_BT_ON_OFF			0//Open or Close BT device;
#define APU_FCT_BT_REQ_MAC			1//Request BT Mac address;
#define APU_FCT_BT_REQ_BT_STATE	2 //Request BT state;
#define APU_FCT_BT_CHG_BT_NAME	3 //Change BT device name;
#define APU_FCT_BT_REQ_BT_NAME	4 //Request BT device name;
#define APU_FCT_BT_REQ_BT_VERSION	5 //Request BT software version;
#define APU_FCT_BT_DIAL_CALL		6//Send a phone number for dial;
#define APU_FCT_BT_REQ_RF_QUALITY	7//Request RF quality: emission and received signal strength.

/* GPS  测试*/
#define MCU_TX_FCT_GPS_TEST          5
#define APU_FCT_GPS_SIMULATA_ROUTE		0 //Simulate route;
#define APU_FCT_GPS_REQ_RET_QUALITY		1 //Request return GPS quality;
#define APU_FCT_GPS_REQ_RET_GYRO_INFO		2 //Request return gyro info;
#define APU_FCT_GPS_REQ_RET_TMC_INFO		3//Request return TMC info;

/* 视频设置*/
#define MCU_TX_FCT_VIDEO_SET          7
#define APU_FCT_VIDEO_SET_BRIGHTNESS		1 //Simulate route;
#define APU_FCT_VIDEO_SET_CONTRAST		2 //Simulate route;
#define APU_FCT_VIDEO_SET_CHROMA			3 //Simulate route;

/* WIFI 测试*/
#define MCU_TX_FCT_WIFI_TEST		8
#define APU_FCT_WIFI_ON_OFF		0 //Open or Close WiFi device;
#define APU_FCT_WIFI_LINK_AP		1//Inform Apu to connects a special AP;
#define APU_FCT_WIFI_REQ_ISSI		2 //Request WiFi signal strength.

/* 软件版本*/
#define MCU_TX_FCT_REQ_VER		9
#define APU_FCT_VERSION_OS			0//OS version;
#define APU_FCT_VERSION_BOOT		1//Boot version;
#define APU_FCT_VERSION_APP		2//App version;
#define APU_FCT_VERSION_MPEG		3//MPEG version;
#define APU_FCT_VERSION_MAP		4//Navigation Map version;

/*FCT测试 APU TX MCU*/

#define APU_TX_MCU_RESULT_BASIC	2
typedef enum
{
	FCT_TEST_SOURCE_SWITCH, //FCT test: source switch.
	FCT_TEST_SWC_STUDY_FUNC = 10, //FCT test: SWC Study function.
	FCT_TEST_REVERSE, //FCT test: Reverse function.
	FCT_TEST_SETUP_MENU, //FCT test: Setup function.
	FCT_TEST_VOICE_ASSIST, //FCT test: Voice Recognation function.
	FCT_TEST_BT_FUNC, //FCT test: Bluetooth function.
	FCT_TEST_WIFI_FUNC, //FCT test: Bluetooth function.
	FCT_TEST_ONE_KEY_NAVI, //FCT test: One Key Navi function.
	FCT_TEST_MEDIA_SEL_TRACK = 20, //FCT test: Media Player select track.
	FCT_TEST_2_6_CH_SW, //FCT test: DVD 2CH and 6CH switch.
	FCT_TEST_DVD_DISP_SW, //FCT test: DVD 16:9 and 4:3 switch.
	FCT_TEST_BRIGHTNESS_SET = 40, //FCT test: Screen brightness set.
	FCT_TEST_CONTRAST_SET, //FCT test: Screen contrast set.
	FCT_TEST_CHROMA_SET, //FCT test: Screen chroma set.
	FCT_TEST_TYPE_MAX,
} BASIC_TEST_TYPE;

typedef enum
{
	FCT_TEST_RESULT_FAIL, // 0 FCT test fail
	FCT_TEST_RESULT_SUCCESS, // 1 FCT test success.
	FCT_TEST_RESULT_WITH_DATA, // 2 FCT test with data type result.
	FCT_TEST_RESULT_UNSUPPORT, // 3 FCT test unspoort function.
	FCT_TEST_RESULT_MAX,
} FCT_TEST_RESULT_TYPE;

typedef enum
{
	FCT_BT_TEST_RESULT_MAC, //BT FCT test result: MAC Address.
	FCT_BT_TEST_RESULT_NAME, //BT FCT test result: Device Name.
	FCT_BT_TEST_RESULT_VERSION, //BT FCT test result: Software version.
	FCT_BT_TEST_RESULT_RF_QUALITY, //BT FCT test result: Signal Strength.
	FCT_BT_TEST_RESULT_MAX,
} FCT_BT_TEST_RESULT;

typedef enum
{
	FCT_GPS_TEST_RESULT_QUALITY, //GPS FCT test result: Receive quality.
	FCT_GPS_TEST_RESULT_GYRO, //GPS FCT test result: Current Gyro info.
	FCT_GPS_TEST_RESULT_TMC, //GPS FCT test result: Receive TMC info.
	FCT_GPS_TEST_RESULT_MAX,
} FCT_GPS_TEST_RESULT;
typedef enum
{
	FCT_WIFI_TEST_RESULT_QUALITY, //WiFi FCT test result: Receive quality.
	FCT_WIFI_TEST_RESULT_MAX,
} FCT_WIFI_TEST_RESULT;
typedef enum
{
	FCT_VERSION_OS, //OS version;
	FCT_VERSION_BOOT, //Boot version;
	FCT_VERSION_APP, //App version;
	FCT_VERSION_MPEG, //MPEG version;
	FCT_VERSION_MAP, //Navigation Map version;
}FCT_VERSION_TYPE;


#endif

