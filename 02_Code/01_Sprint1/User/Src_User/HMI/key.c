/*********************( Copyright 2009  Kernel.yangyan )************************
 * FILE      :
 * INFOMATIN :
 * VERSION   : v00
 * DATA      : 10/20, 2009
 * AUTHOR    : kernel yang
 *
 * UPDATE    :
 * ---------------------------------------------
 *   | INFOMATION
 *   | VERSION
 *   | AUTHOR
 *   -------------------------------------------
 *     |  ......
 *     |  
 ******************************************************************************/
#define _KEYPAD_C_
#define _SWC_C_

#include "..\config\inc.h"         

typedef uint8_t (*fGET_KEY_VALUE)(void); 
typedef uint8_t (*fGET_ENCODE_VALUE)(void);


#pragma pack(1)
typedef struct {

    fGET_KEY_VALUE p_fGetValue;      //取得判断值
    tKEY_MAP tMap;                   //按键表
    
}tKEY_CODE_BLOCK; 

#pragma pack(1)
typedef struct {
     fGET_ENCODE_VALUE p_fGetValue;  //取得判断值
     uint8_t a_cMap[8];              //取值表
}tENCODE_CODE_BLOCK;

////////////////////////////////////////////////////////////////////////////////


typedef enum {
    KEY_STATE_IDLE,               //按键空闲
    KEY_STATE_ACTION,             //按键值变化
    KEY_STATE_SHORT_PRESS,        //按下
    KEY_STATE_SHORT_HOLD,         //持续按下
    KEY_STATE_LONG_PRESS,         //长按按下
    KEY_STATE_LONG_HOLD ,         //长按后持续
    KEY_STATE_RELEASE,            //按键弹起
    
    KEY_STATE_NUM
}eKEY_STATE;



#pragma pack(1)
typedef struct {
    
    fGET_KEY_VALUE p_fGetValue;      //取得判断值
    tKEY_MAP*      p_tMap;           //按键表
    uint8_t        cDevIdx;          //设备标示
    
    eKEY_STATE     eState;
    eKEY_STATE     eLastState;
    uint8_t        cPrevIdx;
    uint8_t        cMemKey;
    uint8_t        cKeySrc;
    uint16_t       iTimer;
    uint8_t        cKeyPhyValue;
}tKEY_CTRL_BLOCK;


//正交编码器状态，4个状态顺序排，适用于电阻和IO两种方式检测
typedef enum {
    ENCODE_STATE_LL, //全低
    ENCODE_STATE_LH, //低高
    ENCODE_STATE_HH, //全高
    ENCODE_STATE_HL, //高低
    
    ENCODE_STATE_NUM
}eENCODE_STATE;


#pragma pack(1)
typedef struct {
    eENCODE_STATE prev_state;
    eENCODE_STATE eState;
    uint8_t         cLeftCnt;
    uint8_t         cRightCnt;
    uint8_t         cDelayTimer;
    uint8_t         cQuickFlag;
    uint8_t         cDir;
}eECONDE_BLOCK;

static eECONDE_BLOCK         la_tEncode[D_ENC_KEY_CHANNEL_NUM];
static tKEY_CTRL_BLOCK       la_tKey[D_ALL_KEY_CHANNEL_NUM];
////////////////////////////////////////////////////////////////////////////////////
//填写按键表中用到的函数
uint8_t KEY_GetValueKey1(void)
{
    return IO_Get(IO_IDX_KEY1_DET,0,FALSE);
}

uint8_t KEY_GetValueKey2(void)
{
    return IO_Get(IO_IDX_KEY2_DET,0,FALSE);
}
uint8_t KEY_GetValueKey3(void)
{
    return IO_Get(IO_IDX_SWC2_DET,0,FALSE);
}

uint8_t KEY_GetValueKey4(void)
{
    return IO_Get(IO_IDX_SWC1_DET,0,FALSE);
}


uint8_t KEY_GetValueBus(void)
{
#ifdef CAN_MODULE_V850CAN		// use V850 mcu inner can module
	CANKeyStateStruct *pCANkey = pCAN_GetCANkeyState();
	
	if(pCANkey->keyState != 0)
	{
		return pCANkey->keyValue;
	}
	else
	{
		return CK_NONE;
	}
#else
	return CK_NONE;
#endif
}

uint8_t KEY_GetEncodeABValue(void)
{
    //uint8_t re = IO_Get(io_idx_vol_a,PIN_INPUT, FALSE);
    //re <<= 5;
    //re |= (IO_Get(io_idx_vol_b,PIN_INPUT, FALSE)<<4);
    uint8_t re = (IO_GET_ENCODE_A)|(IO_GET_ENCODE_B<<2);
    return re;
}

uint8_t KEY_GetEncodeCDValue(void)
{
    //uint8_t re = IO_Get(io_idx_tune_a,PIN_INPUT, FALSE);
    //re <<= 5;
    //re |= (IO_Get(io_idx_tune_b,PIN_INPUT, FALSE)<<4);
    uint8_t re = (IO_GET_ENCODE_C>>1)|(IO_GET_ENCODE_D<<1);
    return re;
}

#define D_GET_KEY_CH1_VALUE  KEY_GetValueKey1
#define D_GET_KEY_CH2_VALUE  KEY_GetValueKey2
#define D_GET_KEY_CH3_VALUE  KEY_GetValueKey3// keilee 20140619
#define D_GET_KEY_CH4_VALUE  KEY_GetValueKey4

#define D_GET_KEY_CH5_VALUE  KEY_GetValueBus


#if D_ENCODE_SCAN_IN_INT
#define D_GET_ENCODE1_VALUE  NULL
#define D_GET_ENCODE2_VALUE  NULL
#else
#define D_GET_ENCODE1_VALUE  KEY_GetEncodeABValue
#define D_GET_ENCODE2_VALUE  KEY_GetEncodeCDValue
#endif




/**********************************************************************************/
//按键表定义,SWC
#include "keymap.c"


/**********************************************************************************/
void HMI_CreatKeyScan(tKEY_CTRL_BLOCK* p_tKeyCB,
                      tKEY_MAP* p_tMap,
                      fGET_KEY_VALUE p_fGetValue,
                      uint8_t   cDevIdx)
{
    if(p_tKeyCB && p_fGetValue)
    {
        p_tKeyCB->p_fGetValue = p_fGetValue;
        p_tKeyCB->p_tMap = p_tMap;
        p_tKeyCB->cDevIdx = cDevIdx;
    }
}


uint8_t HMI_GetKeyIndex(tKEY_CTRL_BLOCK* p_tCB)
{
    uint8_t        cIdx = 0xff;
    uint8_t        cValue;
    uint8_t        cKeyOffset  = p_tCB->p_tMap->cAttr;   /*Key phy_value offset*/
    uint16_t       cValidTime  = (p_tCB->p_tMap->cValidTime) >> 1;  /*Key valid time*/
    uint8_t        cKeyNum     = p_tCB->p_tMap->cNum;   /*Scan key num*/
    
    cValue = p_tCB->p_fGetValue();
	#if 0
	if((cValue<250) &&(p_tCB->cDevIdx<4))
	{
		key_printf(_T("\r\nId = %x,value =%d",p_tCB->cDevIdx, cValue));
	}
	#endif
    if(cValue < cKeyOffset) 
	cValue = cKeyOffset;
    else if(cValue > 0xff - cKeyOffset)
	cValue = 0xff - cKeyOffset;


    p_tCB->iTimer ++;

    /*Wait for a stable physical value*/
    if((p_tCB->cKeyPhyValue > cValue - cKeyOffset  // fang dou
       && p_tCB->cKeyPhyValue < cValue + cKeyOffset)||(p_tCB->cKeyPhyValue == cValue))//添加总线数据判断
    {
        uint16_t tmp = ((uint16_t)(p_tCB->cKeyPhyValue)+(uint16_t)cValue)>>1;
        p_tCB->cKeyPhyValue = tmp;
        if(p_tCB->iTimer < cValidTime)return cIdx;
    }
    else
    {
        p_tCB->cKeyPhyValue = cValue;
        p_tCB->iTimer = 0;
        return cIdx;
    }

    if(cValue >= p_tCB->p_tMap->cIdleMax- cKeyOffset
        && cValue <= p_tCB->p_tMap->cIdleMax)
    {
        cIdx = cKeyNum;
    }
    else
    {
        for (cIdx = 0; cIdx < cKeyNum; cIdx ++)
        {    
            if ( ((p_tCB->p_tMap->tKeyMap[cIdx].cPhyValue - cKeyOffset)    <= cValue)
                  &&((p_tCB->p_tMap->tKeyMap[cIdx].cPhyValue + cKeyOffset) >= cValue))
            {    
                break;
            }
            
        }
    }

    return cIdx;
}
////////////////////////////////////////////////////////////////////////////////
// 更新信息 : kernel yang 08-12-02
// 函数名   :
// 功能描述 :
// 参数表   :
// 输出     :
//          ------------------------------------------
//          更新信息 :
//           ......
////////////////////////////////////////////////////////////////////////////////
uint8_t ModeCnt = 0,ModeFlag = 0;  //snake20170216
uint8_t MuteCnt = 0,MuteFlag = 0;
void HMI_ScanKey(tKEY_CTRL_BLOCK* p_tCB)
{
    uint8_t        cIdx;
    
    uint8_t        key        = CK_NONE;    
    uint8_t        eKeyOption = OP_KEY_ACTION_NONE;
    uint8_t        bLongPressFlg = FALSE;   /*Key phy_value offset*/
    
    uint16_t       cValidTime  = (p_tCB->p_tMap->cValidTime) >> 1;  /*Key valid time*/
    uint8_t        cKeyNum     = p_tCB->p_tMap->cNum;   /*Scan key num*/

    if(0 == cKeyNum || NULL == p_tCB->p_tMap || NULL == p_tCB->p_fGetValue)return;
 
    
    cIdx = HMI_GetKeyIndex(p_tCB);
    if(cIdx > cKeyNum)return;

    
    /*Key is changed*/
    if(cIdx != p_tCB->cPrevIdx)
    {
        if(p_tCB->cPrevIdx == cKeyNum
           && p_tCB->eState < KEY_STATE_SHORT_PRESS)
        {
            p_tCB->eState = KEY_STATE_ACTION;
            p_tCB->iTimer = 0;
            
        }
        else
        {
            if(p_tCB->eState > KEY_STATE_ACTION)
            {
                p_tCB->eLastState =  KEY_STATE_IDLE;
                if(p_tCB->eState > KEY_STATE_ACTION)
                {
                    p_tCB->eLastState = p_tCB->eState;
                }
                p_tCB->eState = KEY_STATE_RELEASE;
                cIdx = cKeyNum;
            }
        }
        p_tCB->cPrevIdx = cIdx;
        
    }
    
    if(cIdx < cKeyNum)
    {
        key = p_tCB->p_tMap->tKeyMap[cIdx].clogicValue;      //短按键值
        bLongPressFlg = hmi_get_long_key_valid(key);
    }
   
    switch(p_tCB->eState)
    {
        case KEY_STATE_ACTION:

            if(p_tCB->iTimer > cValidTime)
            {   
                p_tCB->iTimer = 0;
                if(cIdx < cKeyNum)
                {
                    /*Key is pressed,get the short key!*/
                    
                    p_tCB->eState = KEY_STATE_SHORT_PRESS;
                    p_tCB->cMemKey = key;               /*Save the valid key*/
                    p_tCB->cKeySrc = (cIdx);            /*Save the key idx*/
                    if(bLongPressFlg)
                    {
                        key_printf(_T("A bLongPressFlg is shotr pressed:%x->%x\n",p_tCB->cDevIdx,key)); 
                        eKeyOption = OP_KEY_ACTION_LSP;
						//开始按下按键
						if(g_tMcuDevState.uIOState.bits.FirstPowerOnFlag == 1) //冷启动有效
						{
							if(CK_MODE == key)
							{
								ModeFlag = 1;
								ModeCnt = 0;
							}
							if(CK_MUTE == key)
							{
								MuteFlag = 1;
								MuteCnt = 0;
							}
						}
                    }
                    else
                    {
                        key_printf(_T("Short press:%x \n",key)); 
                        eKeyOption = OP_KEY_ACTION_SP;
						if(CK_MODE == key)
						{
							ModeFlag = 0;
							ModeCnt = 0;
						}
						if(CK_MUTE == key)
						{
							MuteFlag = 0;
							MuteCnt = 0;
						}

                    }
                } 
                else     /*The phy_value is not in the key list, means the key is realsed!*/
                {
                    p_tCB->eState = KEY_STATE_RELEASE;  
                }
                
            }
        break;
        case KEY_STATE_SHORT_PRESS:
            if(bLongPressFlg)     
            {
                /*Long press is valid*/
                if(p_tCB->iTimer > (cValidTime<<5))
                {
                   p_tCB->iTimer = 0;
                   p_tCB->eState = KEY_STATE_LONG_PRESS;
                   key_printf(_T("Long press:%x \n",key)); 
                   eKeyOption = OP_KEY_ACTION_LP;
                }  
                
            }
            else    
            {
                /*Long press is invalid*/
                if(p_tCB->iTimer > (cValidTime<<3))
                {
                    p_tCB->eState = KEY_STATE_SHORT_HOLD;
                    p_tCB->iTimer = 0;
                }
            }
        break;
        case KEY_STATE_SHORT_HOLD:
            if(p_tCB->iTimer > cValidTime<<3)
            {
                p_tCB->iTimer = 0;
                key_printf(_T("Short press hold:%x->%x\n",p_tCB->cDevIdx,key));
                if(hmi_get_sphold_key_valid(key))eKeyOption = OP_KEY_ACTION_SH;
            }
        break;
        case KEY_STATE_LONG_PRESS:
            if(p_tCB->iTimer > cValidTime<<5)
            {
                p_tCB->iTimer = 0;
                p_tCB->eState = KEY_STATE_LONG_HOLD;
                key_printf(_T("[5] long press hold:%x->%x\n",p_tCB->cDevIdx,key));
                if(hmi_get_lphold_key_valid(key))eKeyOption = OP_KEY_ACTION_LH;

				//开始按下按键
				if(CK_MODE == key)
				{
					if(ModeFlag == 1)
					{
						ModeFlag = 2;
						ModeCnt = 0;
					}
				}
				if(CK_MUTE == key)
				{
					if(MuteFlag == 1)
					{
						MuteFlag = 2;
						MuteCnt = 0;
					}
				}
            }
        break;
        case KEY_STATE_LONG_HOLD:
            if(p_tCB->iTimer > cValidTime<<2)
            {
                p_tCB->iTimer = 0;
                
                eKeyOption = OP_KEY_ACTION_LH;
				//同意界面,长按这两个按键进入usb调试模式.
				//if(g_tMcuDevState.uIOState.bits.FirstPowerOnFlag == 1) //冷启动有效
				{
					if(CK_MODE == key) 	
					{
						if(ModeFlag == 2)
						{
							ModeCnt ++;
						}
					}
					if(CK_MUTE == key)
					{
						if(MuteFlag == 2)
							MuteCnt ++;
					}	

					if(((ModeFlag == 2) && (ModeCnt >= 10)) && ((MuteFlag == 2) && (MuteCnt >= 10)))
					{
						ModeFlag = 0;
						ModeCnt= 0;
						MuteFlag = 0;
						MuteCnt = 0;
						//if(!l_tMediaCB.uDevFlag.field.bUnLocked)//在同意界面之前检测到才有效,上报给OS...
						{
							//直接发送,在信息同步的时候,还会同步此消息...
							g_tSysRomData.DevelopFlag  = 1;
							_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVELOP,&(g_tSysRomData.DevelopFlag));
						}
					}
				}
                key_printf(_T("[2] long press hold:%x->%x\n",p_tCB->cDevIdx,key));
                
            }
        break;
        case KEY_STATE_RELEASE:
            key = p_tCB->cMemKey;
            if(CK_NONE == (uint8_t)key)
            {
                eKeyOption = OP_KEY_ACTION_NONE;
            }
            else
            {   
                switch(p_tCB->eLastState)
                {
                    case KEY_STATE_LONG_HOLD: eKeyOption = OP_KEY_ACTION_LHREL;break;
                    case KEY_STATE_LONG_PRESS: eKeyOption = OP_KEY_ACTION_LREL;break;
                    case KEY_STATE_SHORT_HOLD: eKeyOption = OP_KEY_ACTION_SHREL;break;
                    case KEY_STATE_SHORT_PRESS:
                        bLongPressFlg = hmi_get_long_key_valid(key);
                        if(bLongPressFlg)eKeyOption = OP_KEY_ACTION_LSREL;
                        else eKeyOption = OP_KEY_ACTION_SREL;
                    break;
                }
            }
            
            p_tCB->cMemKey = CK_NONE;
            p_tCB->eState = KEY_STATE_IDLE;
            key_printf(_T("relese key:%x->%x\n",p_tCB->cDevIdx,key));
        break;
        default:
        break;
    }
    
    
    if(eKeyOption)
    {
        _SendFullMsgToHMI(MS_INPUT_KEY,eKeyOption,key,p_tCB->cKeySrc,p_tCB->cDevIdx,0);
        key_printf(_T("key:%x-->Op:%d at dev %x idx:%d\n",key,eKeyOption,p_tCB->cDevIdx,p_tCB->cKeySrc));
    }

}

#define KEY_STATE_SHORE_PRESS		0
#define KEY_STATE_LONG_PRESS		1
#define KEY_STATE_LONG_RELEASE		2

#define KEY_ATTRI_SHORT_ONLY		0
#define KEY_ATTRI_LONG				1

eKEY_DATA_STATE KeyInfoStr;

void SendKeyMsgToMedia(tMSG_BUF* p_tMsg)
{
	CarAVMDataStruct *pData = pCAN_GetAVMData();
	
	if(p_tMsg->Id == MS_INPUT_KEY)
	{
		switch(p_tMsg->iSid)
		{
			case OP_KEY_ACTION_SP:
			case OP_ENCODE_TURN_LEFT:
			case OP_ENCODE_TURN_RIGHT:
				KeyInfoStr.keyState = KEY_STATE_SHORE_PRESS;
				KeyInfoStr.keyAttri = KEY_ATTRI_SHORT_ONLY;
				break;
			case OP_KEY_ACTION_LSP:
				KeyInfoStr.keyState = KEY_STATE_LONG_PRESS;
				KeyInfoStr.keyAttri = KEY_ATTRI_LONG;
				break;
			case OP_KEY_ACTION_LREL:
			case OP_KEY_ACTION_LHREL:
			case OP_KEY_ACTION_LSREL:
				KeyInfoStr.keyState = KEY_STATE_LONG_RELEASE;
				KeyInfoStr.keyAttri = KEY_ATTRI_LONG;
				break;
			default:
				return;
		}
		KeyInfoStr.keyCode = p_tMsg->uData.a_cData[0];

		if(p_tMsg->uData.a_cData[2]==HMI_KEY_DEV_SWC1)
		KeyInfoStr.keySource =  0x02;
		else if(p_tMsg->uData.a_cData[2]==HMI_KEY_DEV_SWC2)
		KeyInfoStr.keySource =  0x03;
		else if(p_tMsg->uData.a_cData[2]==HMI_KEY_DEV_BUSLINE)
		KeyInfoStr.keySource =  0x00;
		else if(p_tMsg->uData.a_cData[2]==HMI_KEY_DEV_KEY1)
		KeyInfoStr.keySource =  0x00;
		else if(p_tMsg->uData.a_cData[2]==HMI_KEY_DEV_KEY2)
		KeyInfoStr.keySource =  0x00;
		else
		KeyInfoStr.keySource =  p_tMsg->uData.a_cData[2];

		if(pData->CarAVMReq == 1)
		{
			//盲区不能过滤mode按键消息
			if(/*(KeyInfoStr.keyCode==CK_MODE)||*/(KeyInfoStr.keyCode==CK_VR))
			return;
		}

		//倒车状态下,不过滤方控静音(用作挂断电话) mode键(用作接听电话)
		if((g_tMcuDevState.uIOState.bits.Reverse_Flag)&&(KeyInfoStr.keyCode!=CK_PRE)&&(KeyInfoStr.keyCode!=CK_NEXT)&&(KeyInfoStr.keyCode!=CK_MUTE)&&(KeyInfoStr.keyCode!=CK_MODE))
		{
			return;
		}

		key_printf(_T("ReqSend Key:%x,%x,%x,%x\n",KeyInfoStr.keyCode,KeyInfoStr.keySource, KeyInfoStr.keyAttri,KeyInfoStr.keyState));
       _SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_KEYDATA,0,0,0,0);
	   	//清除标志  
		if((CK_MODE == KeyInfoStr.keyCode) || (CK_MUTE == KeyInfoStr.keyCode)) 	
		{
			if(KeyInfoStr.keyState == 2)//任何一个按键释放,就清除标志
			{
				ModeFlag = 0;
				ModeCnt = 0;
				MuteFlag = 0;
				MuteCnt = 0;
				key_printf(_T("----------clear-------\n"));
			}
		}

	}
}

AutoTestStruct	AutoTestChk;

void HMI_AutoTestInit(void)
{
	AutoTestChk.Timer = 0;
	AutoTestChk.EnterFlag = 0;
	AutoTestChk.MODEKeyState = 0;
	AutoTestChk.VRKeyState = 0;
	AutoTestChk.UsbModeStep = 0;
	AutoTestChk.UsbModeTimer = 0;
}

void HMI_SysAutoTestEnterCheck(void)
{
	if(AutoTestChk.EnterFlag == 1)
		return;
	if(l_tMediaCB.uDevFlag.field.bDevConnect)
		return;

	if(AutoTestChk.MODEKeyState && AutoTestChk.VRKeyState)
	{
		AutoTestChk.Timer++;

		if(AutoTestChk.Timer>= _set_timing_xms_base_hmi_task_tick(5000))
		{
			AutoTestChk.EnterFlag = 1;
			SysWorkStatusGrp.SysAutoTestEnter = 1;
			Mult_Struct.TestTuner = OPEN_TESTTUNER;
			hmi_printf(_T("HMI: AutoTest Enter = 1----\n"));
		}
	}
	else
	{
		AutoTestChk.Timer = 0;
	}
}

void AutoTestKeyCheck(tMSG_BUF* p_tMsg)
{
	if(AutoTestChk.EnterFlag == 1)
		return;
	if(p_tMsg->Id != MS_INPUT_KEY)
	{
		return;
	}

	switch(p_tMsg->iSid)
	{
		case OP_KEY_ACTION_SP:
		case OP_KEY_ACTION_LSP:
			if(p_tMsg->uData.a_cData[0] == CK_MODE)
			{
				AutoTestChk.MODEKeyState = 1;
			}
			else if(p_tMsg->uData.a_cData[0] == CK_MUTE)
			{
				AutoTestChk.VRKeyState = 1;
			}
			break;
		case OP_KEY_ACTION_SREL:
		case OP_KEY_ACTION_SHREL:
		case OP_KEY_ACTION_LREL:
		case OP_KEY_ACTION_LHREL:
		case OP_KEY_ACTION_LSREL:
			if(p_tMsg->uData.a_cData[0] == CK_MODE)
			{
				AutoTestChk.MODEKeyState = 0;
			}
			else if(p_tMsg->uData.a_cData[0] == CK_MUTE)
			{
				AutoTestChk.VRKeyState = 0;
			}
			break;
		default:
			break;
	}
}

/******************************************************************************/
#include "swc.c"
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
const uint8_t ca_cEncodeDirectionMap[4][4] = {
    //如果Encode控制结构中用有符号数，此数组中也可用有符号数，可节省一个记数器
#if 0 == D_ENCODE_SCAN_IN_INT
    {0,1,0,2},
    {2,0,1,0},
    {0,2,0,1},
    {1,0,2,0}
#else
    {0,0,2,1},
    {0,0,2,1},
    {2,1,0,0},
    {2,1,0,0}
#endif
};

void HMI_EncodeSet(bool bEN)
{
    uint8_t cValue;
    (void)IO_Get(IO_IDX_VOL_A,PIN_INPUT,INVALID);
    (void)IO_Get(IO_IDX_VOL_B,PIN_INPUT,INVALID);
    (void)IO_Get(IO_IDX_TUNE_A,PIN_INPUT,INVALID);
    (void)IO_Get(IO_IDX_TUNE_B,PIN_INPUT,INVALID);
    
    v850_intp4_init();
    v850_intp5_init();

    cValue = (IO_GET_ENCODE_A)|(IO_GET_ENCODE_B<<2);
    isrHMI_ScanEncode(0, cValue);
    cValue = (IO_GET_ENCODE_C>>1)|(IO_GET_ENCODE_D<<1);
    isrHMI_ScanEncode(1, cValue);

    la_tEncode[0].cLeftCnt = 0;
    la_tEncode[0].cRightCnt = 0;
    la_tEncode[1].cLeftCnt = 0;
    la_tEncode[1].cRightCnt = 0;
    if(bEN)
    {
        v850_intp4_enable();
        v850_intp5_enable();
    }
}



void isrHMI_ScanEncode(uint8_t cIdx,uint8_t cValue)
{
    const tENCODE_CODE_BLOCK* p_tEncode = &ca_tEncodeStateValueMap[cIdx];

    #if 0 == D_ENCODE_SCAN_IN_INT
    if(p_tEncode->p_fGetValue)cValue = p_tEncode->p_fGetValue();
    #endif
        
    if(cValue >= p_tEncode->a_cMap[0] //=少不了
       && cValue <= p_tEncode->a_cMap[1])
    {
        la_tEncode[cIdx].eState = ENCODE_STATE_LL;
    }
    else if(cValue >= p_tEncode->a_cMap[2] 
       && cValue <= p_tEncode->a_cMap[3])
    {
        la_tEncode[cIdx].eState = ENCODE_STATE_LH;
    }
    else if(cValue >= p_tEncode->a_cMap[4]
       && cValue <= p_tEncode->a_cMap[5])
    {
        la_tEncode[cIdx].eState = ENCODE_STATE_HH;
    }
    else if(cValue >= p_tEncode->a_cMap[6]
       && cValue <= p_tEncode->a_cMap[7] )
    {
        la_tEncode[cIdx].eState = ENCODE_STATE_HL;
    }

    if(la_tEncode[cIdx].eState != la_tEncode[cIdx].prev_state)
    {
        uint8_t temp = ca_cEncodeDirectionMap[la_tEncode[cIdx].prev_state][la_tEncode[cIdx].eState];
        if(1 == temp)la_tEncode[cIdx].cLeftCnt++;
        else if(2 == temp)la_tEncode[cIdx].cRightCnt++;
        la_tEncode[cIdx].prev_state = la_tEncode[cIdx].eState;
    }
    
}


void HMI_ScanEncode(uint8_t cIdx)
{
   uint8_t cOffset = lca_cEncodeKeyMap[cIdx][2];
   uint8_t bDir = OP_KEY_ACTION_NONE;
   if(la_tEncode[cIdx].cQuickFlag)la_tEncode[cIdx].cQuickFlag--;
   if(la_tEncode[cIdx].cDelayTimer ++ > _set_timing_xms_base_hmi_task_tick(80))
   {
       la_tEncode[cIdx].cDelayTimer = 0;
       if(la_tEncode[cIdx].cLeftCnt > la_tEncode[cIdx].cRightCnt)
       {
           if(la_tEncode[cIdx].cLeftCnt >= la_tEncode[cIdx].cRightCnt + cOffset)
           {
               bDir = OP_ENCODE_TURN_LEFT;
               encode_printf(_T("Enleft\n"));
           }
       }
       else if(la_tEncode[cIdx].cLeftCnt < la_tEncode[cIdx].cRightCnt)
       {
           if(la_tEncode[cIdx].cLeftCnt + cOffset <= la_tEncode[cIdx].cRightCnt)
           {
               bDir = OP_ENCODE_TURN_RIGHT;
               encode_printf(_T("Enright\n"));
           }
       }
       else
       {
           la_tEncode[cIdx].cLeftCnt = 0;
           la_tEncode[cIdx].cRightCnt = 0;
       }

       if(bDir)
       {
           la_tEncode[cIdx].cLeftCnt = 0;
           la_tEncode[cIdx].cRightCnt = 0;
           if(bDir != la_tEncode[cIdx].cDir)
           {
               la_tEncode[cIdx].cQuickFlag = 0;
               la_tEncode[cIdx].cDir = bDir;
           }
           _SendFullMsgToHMI(MS_INPUT_KEY,bDir,\
                             lca_cEncodeKeyMap[cIdx][bDir - OP_ENCODE_TURN_LEFT],0,\
                             HMI_KEY_DEV_ENCODE1+cIdx,\
                             la_tEncode[cIdx].cQuickFlag);
           la_tEncode[cIdx].cQuickFlag = _set_timing_xms_base_hmi_task_tick(500);
       }
   }      
}



////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 更新信息 : kernel yang 08-12-02
// 函数名   :
// 功能描述 :
// 参数表   :
// 输出     :
//          ------------------------------------------
//          更新信息 :
//           ......
////////////////////////////////////////////////////////////////////////////////


void HMI_KeyInit(void)
{
	API_MemClear((uint8_t*)la_tKey,(sizeof(tKEY_CTRL_BLOCK))*D_ALL_KEY_CHANNEL_NUM);
	API_MemClear((uint8_t*)la_tEncode,(sizeof(eECONDE_BLOCK))*D_ENCODE_NUM);

	HMI_CreatKeyScan(&la_tKey[0],(tKEY_MAP *)&lc_tKeyMap_CH1,KEY_GetValueKey1,HMI_KEY_DEV_KEY1);
	HMI_CreatKeyScan(&la_tKey[1],(tKEY_MAP *)&lc_tKeyMap_CH2,KEY_GetValueKey2,HMI_KEY_DEV_KEY2);
	HMI_CreatKeyScan(&la_tKey[2],(tKEY_MAP *)&lc_tKeyMap_CH3,KEY_GetValueKey3,HMI_KEY_DEV_SWC1);
	HMI_CreatKeyScan(&la_tKey[3],(tKEY_MAP *)&lc_tKeyMap_CH4,KEY_GetValueKey4,HMI_KEY_DEV_SWC2);//keilee 20140619
	HMI_CreatKeyScan(&la_tKey[4],(tKEY_MAP *)&lc_tKeyMap_Bus,KEY_GetValueBus,HMI_KEY_DEV_BUSLINE);

	IO_Get(IO_IDX_KEY1_DET,PIN_INPUT,INVALID);
	IO_Get(IO_IDX_KEY2_DET,PIN_INPUT,INVALID);
	HMI_SWCInit();
#if D_ENCODE_SCAN_IN_INT 
	HMI_EncodeSet(ON);    
#endif
}

////////////////////////////////////////////////////////////////////////////////
//按键扫描过程

void HMI_KeyTask(EVENT iEvt)
{
    if(iEvt & EVT_TASK_TICK_READY)
    {
        uint8_t i;
        for(i = 0;i < D_ALL_KEY_CHANNEL_NUM; i++)    
			HMI_ScanKey(&la_tKey[i]);        
        for(i = 0;i < 2; i++)
			HMI_ScanEncode(i);
        
#if 0 == D_ENCODE_SCAN_IN_INT
        for(i = 0;i < 2; i++)isrHMI_ScanEncode(i,i); 
#endif
	HMI_SysAutoTestEnterCheck();
    }
}

////////////////////////////////////////////////////////////////////////////////

 

