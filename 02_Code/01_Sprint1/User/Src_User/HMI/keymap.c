////////////////////////////////////////////////////////////////////////////////
//扫描常数
#define D_ADKEY_CHNUM           2
#define D_ADSWHEEL_CHNUM        2
#define D_ENCODE_NUM            2

#define D_KEY_DELTA             8                //ADC允许误差值
#define D_NKEY                  0xFF-D_KEY_DELTA //ADC上无按键时，防止溢出
#define D_ZKEY                  D_KEY_DELTA      //ADC值为0扫描值，防止溢出    
#define D_ENCODE_DELTA          7                //ENCODE扫描允许误差值
#define D_SWCKEY_DELTA          8                //方向盘ADC允许误差值



////////////////////////////////////////////////////////////////////////////////



const tKEY_MAP lc_tKeyMap_CH1 = 
{
    _KEY_V_(0.1),    //当ADC为0时候，必须为此值，防止溢出
    _KEY_V_(3.3),
    _set_timing_xms_base_hmi_task_tick(60),
    5,

    {
	  {_KEY_V_(0.1),CK_EJECT},
        {_KEY_V_(1.0),CK_NAVI_ONEKEY},
        {_KEY_V_(1.7),CK_SEEK_DOWN},
        {_KEY_V_(2.2),CK_SEEK_UP }, 
        {_KEY_V_(2.7),CK_FMAM}, 
    },
};


const tKEY_MAP lc_tKeyMap_CH2 = 
{
    _KEY_V_(0.1),
    _KEY_V_(3.3),
    _set_timing_xms_base_hmi_task_tick(60),
    5,

    {  
	{_KEY_V_(0.1),CK_POWER},
        {66,CK_DISP },
       {118,CK_NAVI}, 
       {163,CK_USB},
      {207,CK_TEL}, 
    },
};


const tKEY_MAP lc_tKeyMap_CH3 = 
{
    _KEY_V_(0.1),
    _KEY_V_(3.3),
    _set_timing_xms_base_hmi_task_tick(60),
    3,

    {
    #if 0
	{_KEY_V_(1.51),CK_MUTE},
	{_KEY_V_(0.89),CK_VOL_INC},
	{_KEY_V_(0.42),CK_VOL_DEC},
	#else //snake20160823
	{_KEY_V_(1.50),CK_MUTE},// 1.95
	{_KEY_V_(0.42),CK_VOL_INC},// 1.28
	{_KEY_V_(0.89),CK_VOL_DEC},// 0.67
	#endif
    },
};

const tKEY_MAP lc_tKeyMap_CH4 = 
{
    _KEY_V_(0.1),
    _KEY_V_(3.3),
    _set_timing_xms_base_hmi_task_tick(60),
    #if 0
    4,

    {  
	{_KEY_V_(2.15),CK_VR},
	{_KEY_V_(1.50),CK_MODE},
	{_KEY_V_(0.42),CK_PRE},
	{_KEY_V_(0.88),CK_NEXT},
	//{_KEY_V_(0.42),CK_SEEK_UP},
	//{_KEY_V_(0.88),CK_SEEK_DOWN},
    },
    #else //snake20160823
	3,
    {  
	{_KEY_V_(1.50),CK_MODE },///1.95V
	{_KEY_V_(0.42),CK_PRE},///1.28V  // CK_SEEK_UP   //snake20160915
	{_KEY_V_(0.89),CK_NEXT },//0.67V // CK_SEEK_DOWN
    },
	#endif
};


const tKEY_MAP lc_tKeyMap_Bus = 
{
    _KEY_V_(0),
    _KEY_V_(3.3),
    _set_timing_xms_base_hmi_task_tick(60),
    18,
    {     
	{CK_MEDIA,CK_MEDIA},
	{CK_EJECT,CK_EJECT},
	{CK_FMAM,CK_FMAM},
	{CK_DISP,CK_DISP},
	{CK_MAIN_MENU,CK_MAIN_MENU},
	{CK_TEL,CK_TEL},
	{CK_NAVI,CK_NAVI},
	{CK_NAVI_ONEKEY, CK_NAVI_ONEKEY},
	{CK_POWER,CK_POWER},
	{CK_NEXT,CK_NEXT},
	{CK_PRE,CK_PRE},
	{CK_SCAN,CK_SCAN},	
	{CK_FB,CK_FB},
	{CK_FF,CK_FF},	
	{CK_SETUP,CK_SETUP},
	{CK_AUDIO,CK_AUDIO},	
	{CK_VOL_DEC,CK_VOL_DEC},
	{CK_VOL_INC,CK_VOL_INC},
    },
};


const tENCODE_CODE_BLOCK ca_tEncodeStateValueMap[]=   //4个状态,4个值,适用于电阻和IO两种方式
{
    {
        D_GET_ENCODE1_VALUE,
        {
            0x10,0x18,//01
            0x00,0x18,//00
            0x20,0x28,//10
            0x30,0x38,//11
        },
    },
    {
        D_GET_ENCODE2_VALUE,
        {
            0x10,0x18,//01
            0x00,0x18,//00
            0x20,0x28,//10
            0x30,0x38,//11
        },
    },
};

const uint8_t lca_cEncodeKeyMap[][3]=
{
     //turn left      turn right
    {CK_VOL_DEC,    CK_VOL_INC,    D_ENCODE_SPEED_CTRL},
    {CK_SEL_LEFT,    CK_SEL_RIGHT,      D_ENCODE_SPEED_CTRL},  
};


const uint8_t key_longpress_map[] = {CK_POWER,CK_NEXT,CK_PRE, CK_MODE,CK_FF,CK_FB,CK_VOL_INC, CK_VOL_DEC,CK_MUTE,CK_NONE};
const uint8_t key_sphold_map[] = {CK_VOL_DEC,CK_VOL_INC,CK_LEFT,CK_RIGHT,CK_NONE};
const uint8_t key_lphold_map[] = {CK_MODE,CK_MUTE,CK_SEEK_DOWN,CK_SEEK_UP,CK_NEXT,CK_PRE,CK_NONE};
const tKEY_MAP* const lc_tKeyMapPoint[]={&lc_tKeyMap_CH1,&lc_tKeyMap_CH2,&lc_tKeyMap_CH3,&lc_tKeyMap_CH4,&lc_tKeyMap_Bus};
const fGET_KEY_VALUE lc_pfKeyGetValue[] = {KEY_GetValueKey1,KEY_GetValueKey2,KEY_GetValueKey3,KEY_GetValueKey4,KEY_GetValueBus};


bool hmi_get_sphold_key_valid(uint8_t key)
{
    uint8_t re=0;
    uint8_t i;
    if(CK_NONE == key)return FALSE;

    for(i = 0;;i++)
    {
        if(key_sphold_map[i]==key){re = TRUE;break;}
        else if(key_sphold_map[i] == CK_NONE){break;}
    }

    return re;
}

bool hmi_get_lphold_key_valid(uint8_t key)
{
    uint8_t re=0;
    uint8_t i;
    if(CK_NONE == key)return FALSE;
    for(i = 0;;i++)
    {
        if(key_lphold_map[i] == key){re = TRUE;break;}
        else if(key_lphold_map[i] == CK_NONE){break;}
    }

    return re;
}

bool hmi_get_long_key_valid(uint8_t key)
{
    uint8_t re = FALSE;
    uint8_t i;
    if(CK_NONE == key)
		return FALSE;

    for(i = 0;;i++)
    {
        if(key_longpress_map[i] == key)
	{
		re = TRUE;
		break;
	}
        else if(key_longpress_map[i] == CK_NONE)
	{
		break;
	}
    }

    return re;
}

