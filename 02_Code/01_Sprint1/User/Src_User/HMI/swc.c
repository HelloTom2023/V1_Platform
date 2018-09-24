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

//#define _SWC_C_
//#include "..\config\inc.h"

extern void HMI_ScanKey(tKEY_CTRL_BLOCK* p_tCB);


//方向盘设置
typedef enum {
    SWC_STATE_WAIT,
    SWC_STATE_IDLE,
    SWC_STATE_SET_PLUSRES_FOR_IDLE_VAL,
    SWC_STATE_CHECK_IDLE_VAL,
    
    SWC_STATE_CHECK_KEY_ACTION,
    SWC_STATE_SET_PLUSRES_FOR_KEY,
    SWC_STATE_CHECK_KEY_VAL,
    SWC_STATE_SET_TEMP_RES,
    SWC_STATE_GET_TEMP_RES_KEY_VALUE,
    SWC_STATE_CHECK_ALL_RES,
    
    SWC_STATE_WAIT_PAIR,

    SWC_STATE_EXIT,
    SWC_STATE_TIMEOUT,
    SWC_STATE_SAVESETTING,
    SWC_STATE_N
    
}eSWC_STATE;

typedef enum{
    SWC_KYEID_1,
    SWC_KYEID_2,
    SWC_KYEID_3,
    SWC_KYEID_4,
    SWC_KYEID_5,
    SWC_KYEID_6,
    SWC_KYEID_7,
    SWC_KYEID_8,
    SWC_KYEID_9,
    SWC_KYEID_10,
    SWC_KYEID_11,
    SWC_KYEID_12,
    SWC_KYEID_13,
    SWC_KYEID_14,
    SWC_KYEID_15,
    SWC_KYEID_16,

    SWC_KYEID_N,
    
}eSWC_KEY_IDX;



typedef struct {
    uint16_t    iTimer;
    uint32_t    lTimer;
    uint8_t     cPlusResIdx;
    uint8_t     cPairUicc;
    uint8_t     cScanChIdx;
    uint8_t     cScanCnt;
    uint8_t     cTotalKey;
    
    uint8_t         cIdleVal[D_SWC_KEY_CHANNEL_NUM][D_SWC_PLUS_RESISTANCE_NUM];
    uint8_t         cRepIdx[D_SWC_KEY_CHANNEL_NUM][D_SWC_PLUS_RESISTANCE_NUM];
    uint8_t         cKeyNum[D_SWC_KEY_CHANNEL_NUM][D_SWC_PLUS_RESISTANCE_NUM];
    uint8_t         bNewKey[D_SWC_KEY_CHANNEL_NUM][D_SWC_PLUS_RESISTANCE_NUM];
    tKEY_LOGIC_MAP  tTmpKey[D_SWC_KEY_CHANNEL_NUM][D_SWC_PLUS_RESISTANCE_NUM][16];
    uint8_t         cTempAdValue[3];
    
    
    eSWC_STATE  eState;
    

}tSWC_CTRL_BLOCK;



tSWC_CTRL_BLOCK l_tSwcCB;

#pragma section data "no_init" begin    
tSWC_ROM_DATA   l_tSwcRomData;
#pragma section data "no_init" end

tEEP_DATA_BLOCK l_tSwcEepData;


static tKEY_CTRL_BLOCK       la_tSWCKeyCB[D_SWC_KEY_CHANNEL_NUM];




const tEEP_DATA_RANG lc_tSwcDefData[] = {
    {0,0,0x02},
    {0,0,0x02},

    {_KEY_V_(0), _KEY_V_(0.1), _KEY_V_(3.3)},
    {_KEY_V_(0), _KEY_V_(3.3), _KEY_V_(3.3)},
    {0,_set_timing_xms_base_hmi_task_tick(60),0xff},
    {0,4,14},

    

    {0,_KEY_V_(0.1 ),0xff},{0,CK_NEXT,0xff},
    {0,_KEY_V_(0.82),0xff},{0,CK_PRE,0xff},
    {0,_KEY_V_(1.66),0xff},{0,CK_VOL_INC,0xff},
    {0,_KEY_V_(2.51),0xff},{0,CK_VOL_DEC,0xff},
    {0,_KEY_V_(0.8 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(1.0 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(1.4 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(1.7 ),0xff},{0,CK_POWER,0xff}, 
    {0,_KEY_V_(1.9 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.1 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.4 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.6 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.8 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(3.0 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.8 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(3.0 ),0xff},{0,CK_POWER,0xff},


    
    {_KEY_V_(0), _KEY_V_(0.1), _KEY_V_(3.3)},
    {_KEY_V_(0), _KEY_V_(3.3), _KEY_V_(3.3)},
    {0,_set_timing_xms_base_hmi_task_tick(60),0xff},
    {0,3,14},
 
    {0,_KEY_V_(0.1 ),0xff},{0,CK_MODE,0xff},
    {0,_KEY_V_(0.22),0xff},{0,CK_HANDUP,0xff},
    {0,_KEY_V_(0.58),0xff},{0,CK_TEL,0xff},
    {0,_KEY_V_(2.48),0xff},{0,CK_MUTE,0xff},
    {0,_KEY_V_(0.8 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(1.0 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(1.4 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(1.7 ),0xff},{0,CK_POWER,0xff},//{_KEY_V_(1.7),CK_MAIN_MENU},
    {0,_KEY_V_(1.9 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.1 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.4 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.6 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.8 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(3.0 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(2.8 ),0xff},{0,CK_POWER,0xff},
    {0,_KEY_V_(3.0 ),0xff},{0,CK_POWER,0xff},
};

const tKEY_MAP lc_tSwcTmpInit = {
    _KEY_V_(0.1),_KEY_V_(3.3),
    _set_timing_xms_base_hmi_task_tick(60),
    16,
    {
        {_KEY_V_(0.1),SWC_KYEID_1},
        {_KEY_V_(0.3),SWC_KYEID_2},
        {_KEY_V_(0.5),SWC_KYEID_3},
        {_KEY_V_(0.7),SWC_KYEID_4},
        {_KEY_V_(0.9),SWC_KYEID_5},
        {_KEY_V_(1.1),SWC_KYEID_6},
        {_KEY_V_(1.3),SWC_KYEID_7},
        {_KEY_V_(1.5),SWC_KYEID_8},
        {_KEY_V_(1.7),SWC_KYEID_9},
        {_KEY_V_(1.9),SWC_KYEID_10},
        {_KEY_V_(2.1),SWC_KYEID_11},
        {_KEY_V_(2.3),SWC_KYEID_12},
        {_KEY_V_(2.5),SWC_KYEID_13},
        {_KEY_V_(2.7),SWC_KYEID_14},
        {_KEY_V_(2.9),SWC_KYEID_15},
        {_KEY_V_(3.1),SWC_KYEID_16},
    },
};


const tEEP_DATA lc_tEepSwcRom = {
    D_EEP_SWCDATA_ID,
    (uint8_t*)&l_tSwcRomData,lc_tSwcDefData,
    D_EEP_SWCDATA_ADDR,D_EEP_SWCDATA_LEN,0
};


uint8_t SWC_GetKey1Value(void)
{
    return IO_Get(IO_IDX_SWC1_DET,0,FALSE);
}

uint8_t SWC_GetKey2Value(void)
{
    return IO_Get(IO_IDX_SWC2_DET,0,FALSE);
}

void SWC_SetPlusResistance(uint8_t cIdx,uint8_t cType)
{
    if(cIdx == 0)
    {
        IO_Set(IO_IDX_SWC_SEL1,PIN_OUTPUT,cType);
    }
    else
    {
        IO_Set(IO_IDX_SWC_SEL2,PIN_OUTPUT,cType);
    }
}

void HMI_SWCMsgHandle(tMSG_BUF* p_tMsg)
{
    uint8_t  cMsg = (uint8_t)((uint32_t)(p_tMsg->uData.p_cData));
    uint16_t Op = p_tMsg->iSid;
    switch(Op)
    {
        case OP_SWC_SET_MODE:
            switch(cMsg)
            {
                case SWC_RX_MODE_START:
                    l_tSwcCB.cPlusResIdx = 0;
                    l_tSwcCB.eState = SWC_STATE_SET_PLUSRES_FOR_IDLE_VAL;
                    
                break;
                case SWC_RX_MODE_CLEAR:
                if(l_tSwcCB.eState <= SWC_STATE_IDLE)
                {   
                    uint8_t i;
                    for(i = 0; i< D_SWC_KEY_CHANNEL_NUM;i++)
                    {
                        l_tSwcRomData.tSwcLogicMap[i].cNum = 0;
                    }
                    EEP_CreateBlockChkSum(&l_tSwcEepData);
                    EEP_WriteStart(&l_tSwcEepData,0);
                }
                else
                {
                    uint8_t i,j;
                    for(i = 0; i< D_SWC_KEY_CHANNEL_NUM;i++)
                        for(j=0;j<D_SWC_PLUS_RESISTANCE_NUM;j++)l_tSwcCB.cKeyNum[i][j] = 0;
                    
                }

                l_tSwcCB.eState = SWC_STATE_SET_PLUSRES_FOR_IDLE_VAL;
                
                break;
                case SWC_RX_MODE_EXIT:
                {
                    l_tSwcCB.eState = SWC_STATE_EXIT;                    
                }
                case SWC_RX_MODE_SAVE:
                {   
                    l_tSwcCB.eState = SWC_STATE_SAVESETTING;  
                }     
                break;
            }
            l_tSwcCB.lTimer = 0;
        break;
        case OP_SWC_SET_UICC:
        {
            
            l_tSwcCB.cPairUicc =  cMsg;
            l_tSwcCB.lTimer = 0;
            if(UICC_NONE == cMsg)
            {
                l_tSwcCB.cPlusResIdx = 0;
                l_tSwcCB.eState = SWC_STATE_SET_PLUSRES_FOR_IDLE_VAL;
            } 
            l_tSwcCB.lTimer = 0;
        }
        break;
        case OP_SWC_SET_LOGIC_VALUE:
        break;
    }
}


void HMI_SWCRomDataInit(void)
{
    (void)EEP_CreateEepDataBlock(&l_tSwcEepData,&lc_tEepSwcRom);
}


void HMI_SWCProc(void)
{

#define _SWC_ResIdx            l_tSwcCB.cPlusResIdx
#define _SWC_CHIdx             l_tSwcCB.cScanChIdx
#define _SWC_IdleKeyValue(i,j) l_tSwcCB.cIdleVal[i][j]
#define _SWC_RepIdx(i,j)       l_tSwcCB.cRepIdx[i][j]
#define _SWC_KeyNum(i,j)       l_tSwcCB.cKeyNum[i][j]
#define _SWC_NewKey(i,j)       l_tSwcCB.bNewKey[i][j]
#define _SWC_TmpVol(i,j,k)     l_tSwcCB.tTmpKey[i][j][k].cPhyValue
#define _SWC_TmpUicc(i,j,k)    l_tSwcCB.tTmpKey[i][j][k].clogicValue


    uint16_t tmp;
    
    switch(l_tSwcCB.eState)
    {
        case SWC_STATE_WAIT:
            if(l_tSwcCB.iTimer++ > _set_timing_xms_base_hmi_task_tick(100))
            {
                if(EEP_BlockCheck(&l_tSwcEepData))
                {
                    l_tSwcCB.eState  = SWC_STATE_IDLE;
                    SWC_SetPlusResistance(0,l_tSwcRomData.cResistanceIdx[0]);
                    SWC_SetPlusResistance(1,l_tSwcRomData.cResistanceIdx[1]);
                }
                l_tSwcCB.iTimer = 0;
            }
        break;
        
        case SWC_STATE_IDLE:
            for(tmp = 0; tmp < D_SWC_KEY_CHANNEL_NUM; tmp ++)
            {
                HMI_ScanKey(&la_tSWCKeyCB[tmp]);
            }
        break;
        
        case SWC_STATE_SET_PLUSRES_FOR_IDLE_VAL:
        {
            uint8_t i;
            
            l_tSwcCB.iTimer = 0;
            l_tSwcCB.eState ++;
            l_tSwcCB.cScanCnt = 0;
            for(i = 0;i< D_SWC_KEY_CHANNEL_NUM;i++)//获取无按键状态特征
            {
				SWC_SetPlusResistance(i,_SWC_ResIdx);
				_SWC_KeyNum(i,_SWC_ResIdx) = 0;
            }
        }
        break;
        case SWC_STATE_CHECK_IDLE_VAL:
            {
                 uint8_t i,cAdValue;
                 for(i = 0;i< D_SWC_KEY_CHANNEL_NUM;i++)//获取无按键状态特征
                 {
                     const tKEY_CTRL_BLOCK* p_tBlock = &la_tSWCKeyCB[i];
                     uint8_t delta = p_tBlock->p_tMap->cAttr;
                     
                     cAdValue = p_tBlock->p_fGetValue();
                     
                     if(cAdValue >=0xff - delta)cAdValue = 0xff - delta;
                     else if(cAdValue <= delta)cAdValue = delta;
    
                     if(l_tSwcCB.iTimer)
                     {
                         tmp = (_SWC_IdleKeyValue(i,_SWC_ResIdx)+cAdValue)>>1;
                         _SWC_IdleKeyValue(i,_SWC_ResIdx) = tmp;
                     }
                     else
                     {
                         _SWC_IdleKeyValue(i,_SWC_ResIdx)= cAdValue;
                     }
                     
                 }
                 
                 if(l_tSwcCB.iTimer++ > _set_timing_xms_base_hmi_task_tick(100))
                 {
                     _SWC_ResIdx ++;
                     if(_SWC_ResIdx < D_SWC_PLUS_RESISTANCE_NUM)
                     {
                         l_tSwcCB.eState --;
                     }
                     else
                     {
                         l_tSwcCB.eState ++;
                         l_tSwcCB.cScanCnt = 0;
                         l_tSwcCB.iTimer = 0;
                         _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_RUNMODE,OP_SWC_TX_RM_START);
                         _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_ALLSETTING,(uint8_t*)&l_tSwcRomData.tSwcLogicMap);
                         /*Init study temp buffer*/
                        
                     }
                     
                 }
                 
            }
        break;

        case SWC_STATE_CHECK_KEY_ACTION:
            if(D_SWC_KEY_CHANNEL_NUM <= l_tSwcCB.cScanChIdx )l_tSwcCB.cScanChIdx = 0;
            l_tSwcCB.iTimer = 0 ;
            l_tSwcCB.eState ++;
        break;
        case SWC_STATE_SET_PLUSRES_FOR_KEY:
            l_tSwcCB.iTimer = 0 ;
            if(_SWC_ResIdx >= D_SWC_PLUS_RESISTANCE_NUM)
            {
                _SWC_ResIdx = 0;
                l_tSwcCB.cScanChIdx++;
                l_tSwcCB.eState = SWC_STATE_CHECK_KEY_ACTION;
            }
            else
            {
                l_tSwcCB.eState ++;
            }
            SWC_SetPlusResistance(l_tSwcCB.cScanChIdx,_SWC_ResIdx);

        break;
        case SWC_STATE_CHECK_KEY_VAL:
            {                
                tKEY_CTRL_BLOCK* p_tBlock = &la_tSWCKeyCB[_SWC_CHIdx];
                     
                uint8_t delta = p_tBlock->p_tMap->cAttr;
                uint8_t cCurrIdx = _SWC_KeyNum(_SWC_CHIdx,_SWC_ResIdx);
                uint8_t cAdcValue = p_tBlock->p_fGetValue();
                l_tSwcCB.cScanCnt ++;
                
                if(cAdcValue >= 0xff - delta)cAdcValue = 0xff - delta;   //边界 检测
                else if(cAdcValue <= delta)cAdcValue = delta;
                 
                //---------------------------------------------------------
                if(l_tSwcCB.iTimer == 0)
                { 
                    l_tSwcCB.cTempAdValue[0] = cAdcValue;
                }
                else if(l_tSwcCB.iTimer < _set_timing_xms_base_hmi_task_tick(20))
                {
                    tmp = (l_tSwcCB.cTempAdValue[0] + cAdcValue)>>1;
                    l_tSwcCB.cTempAdValue[0] = tmp;
                    l_tSwcCB.cTempAdValue[1] = cAdcValue;
                }
                else if(l_tSwcCB.iTimer < _set_timing_xms_base_hmi_task_tick(80))
                {
                    tmp = (l_tSwcCB.cTempAdValue[1] + cAdcValue)>>1;
                    l_tSwcCB.cTempAdValue[1] = tmp;
                    l_tSwcCB.cTempAdValue[2] = cAdcValue;
                }
                else if(l_tSwcCB.iTimer < _set_timing_xms_base_hmi_task_tick(100))
                {
                    tmp = (l_tSwcCB.cTempAdValue[2] + cAdcValue)>>1;
                    l_tSwcCB.cTempAdValue[2] = tmp;
                }
                else
                {     
                    if( (l_tSwcCB.cTempAdValue[0] <= l_tSwcCB.cTempAdValue[1] + delta
                         && l_tSwcCB.cTempAdValue[0] >= l_tSwcCB.cTempAdValue[1] - delta)
                       &&(l_tSwcCB.cTempAdValue[1] <= l_tSwcCB.cTempAdValue[2] + delta
                         && l_tSwcCB.cTempAdValue[1] >= l_tSwcCB.cTempAdValue[2] - delta))
                    {
                    
                        cAdcValue = l_tSwcCB.cTempAdValue[1] ;
                        _SWC_TmpVol(_SWC_CHIdx,_SWC_ResIdx,cCurrIdx) = cAdcValue;
                        l_tSwcCB.iTimer = 0;
                        if( cAdcValue < _SWC_IdleKeyValue(_SWC_CHIdx,_SWC_ResIdx)-delta
                            || cAdcValue > _SWC_IdleKeyValue(_SWC_CHIdx,_SWC_ResIdx)+delta) //不是无按键状态
                        {
                            
                            l_tSwcCB.eState = SWC_STATE_SET_TEMP_RES;
                            swc_printf(_T("CH:%d have a key action,ADC = 0x%x res = %d\n",_SWC_CHIdx,cAdcValue,_SWC_ResIdx));
                            _SWC_ResIdx = 0;
                        }
                        else
                        {
                            l_tSwcCB.eState = SWC_STATE_SET_PLUSRES_FOR_KEY;
    						_SWC_ResIdx ++ ;
                        }
                    }
                    else
                    { 
                        l_tSwcCB.eState = SWC_STATE_SET_PLUSRES_FOR_KEY;
    				    _SWC_ResIdx ++ ;
                    }
                }

                l_tSwcCB.iTimer ++;
            }
        break;
        case SWC_STATE_SET_TEMP_RES:
        {
            if(_SWC_ResIdx < D_SWC_PLUS_RESISTANCE_NUM)
            {
                SWC_SetPlusResistance(l_tSwcCB.cScanChIdx,_SWC_ResIdx);
                l_tSwcCB.eState++;
                l_tSwcCB.iTimer = 0;
            }
            else
            {
                l_tSwcCB.eState = SWC_STATE_CHECK_ALL_RES;
                l_tSwcCB.iTimer = 0;
            }
        }
        break;
        case SWC_STATE_GET_TEMP_RES_KEY_VALUE:
        {                
            tKEY_CTRL_BLOCK* p_tBlock = &la_tSWCKeyCB[_SWC_CHIdx];
                 
            uint8_t delta = p_tBlock->p_tMap->cAttr;
            uint8_t cCurrIdx = _SWC_KeyNum(_SWC_CHIdx,_SWC_ResIdx);
            uint8_t cAdcValue = p_tBlock->p_fGetValue();
            l_tSwcCB.cScanCnt ++;
            
            if(cAdcValue >= 0xff - delta)cAdcValue = 0xff - delta;   //边界 检测
            else if(cAdcValue <= delta)cAdcValue = delta;
             
            //---------------------------------------------------------
            if(l_tSwcCB.iTimer == 0)
            { 
                l_tSwcCB.cTempAdValue[0] = cAdcValue;
            }
            else if(l_tSwcCB.iTimer < _set_timing_xms_base_hmi_task_tick(20))
            {
                tmp = (l_tSwcCB.cTempAdValue[0] + cAdcValue)>>1;
                l_tSwcCB.cTempAdValue[0] = tmp;
                l_tSwcCB.cTempAdValue[1] = cAdcValue;
            }
            else if(l_tSwcCB.iTimer < _set_timing_xms_base_hmi_task_tick(80))
            {
                tmp = (l_tSwcCB.cTempAdValue[1] + cAdcValue)>>1;
                l_tSwcCB.cTempAdValue[1] = tmp;
                l_tSwcCB.cTempAdValue[2] = cAdcValue;
            }
            else if(l_tSwcCB.iTimer < _set_timing_xms_base_hmi_task_tick(100))
            {
                tmp = (l_tSwcCB.cTempAdValue[2] + cAdcValue)>>1;
                l_tSwcCB.cTempAdValue[2] = tmp;
            }
            else
            {     
                if( (l_tSwcCB.cTempAdValue[0] <= l_tSwcCB.cTempAdValue[1] + delta
                     && l_tSwcCB.cTempAdValue[0] >= l_tSwcCB.cTempAdValue[1] - delta)
                   &&(l_tSwcCB.cTempAdValue[1] <= l_tSwcCB.cTempAdValue[2] + delta
                     && l_tSwcCB.cTempAdValue[1] >= l_tSwcCB.cTempAdValue[2] - delta))
                {
                
                    cAdcValue = l_tSwcCB.cTempAdValue[1] ;
                    _SWC_TmpVol(_SWC_CHIdx,_SWC_ResIdx,cCurrIdx) = cAdcValue;
                    l_tSwcCB.iTimer = 0;                        
                    l_tSwcCB.eState = SWC_STATE_SET_TEMP_RES;
                    _SWC_ResIdx ++;
                }
                else
                { 
                    l_tSwcCB.eState = SWC_STATE_SET_PLUSRES_FOR_KEY;
				    _SWC_ResIdx = 0 ;
                }
            }

            l_tSwcCB.iTimer ++;
        }
           
        break;
        case SWC_STATE_CHECK_ALL_RES:
        {                
            
            const tKEY_CTRL_BLOCK* p_tBlock = &la_tSWCKeyCB[_SWC_CHIdx];
            uint8_t delta = p_tBlock->p_tMap->cAttr;
            
            uint8_t bRepeat = 0;
            uint8_t cUicc = UICC_NONE;
            uint8_t i,j;
            for(j = 0;j< D_SWC_PLUS_RESISTANCE_NUM;j++)
            {
                uint8_t cCurrIdx = _SWC_KeyNum(_SWC_CHIdx,j);
                uint8_t cAdValue = _SWC_TmpVol(_SWC_CHIdx,j,cCurrIdx);
                for(i = 0;i < cCurrIdx;i++)
                {
                    if(cAdValue < _SWC_TmpVol(_SWC_CHIdx,j,i) + delta
                       && cAdValue > _SWC_TmpVol(_SWC_CHIdx,j,i) - delta)
                    {
                        bRepeat ++;
                        _SWC_RepIdx(_SWC_CHIdx,j) = i;
                        //cUicc = la_CodeKeyToUICCMap[ _SWC_TmpUicc(_SWC_CHIdx,j,i)];
                        break;
                    }
                }
            }
            
            if(bRepeat == D_SWC_PLUS_RESISTANCE_NUM)
            {
                l_tSwcCB.eState = SWC_STATE_WAIT_PAIR;
                _SendFullMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_KEY_STATE,OP_SWC_TX_KS_REPAIR,cUicc,0,0);
            }
            else
            {
                for(j = 0;j< D_SWC_PLUS_RESISTANCE_NUM;j++)
                {
                    _SWC_RepIdx(_SWC_CHIdx,j) = _SWC_KeyNum(_SWC_CHIdx,j);
                    _SWC_KeyNum(_SWC_CHIdx,j)++;
                }
                
                if(_SWC_KeyNum(_SWC_CHIdx,j) < D_SWC_KEY_MAX_NUM_ON_CH)
                {
                    _SendFullMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_KEY_STATE,OP_SWC_TX_KS_REQ_UICC,0,0,0);
                    l_tSwcCB.eState = SWC_STATE_WAIT_PAIR;
                }
                else
                {
                    _SendFullMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_KEY_STATE,OP_SWC_TX_KS_NSUPPORT,0,0,0);
                    l_tSwcCB.eState = SWC_STATE_IDLE;
                }
            }
            
            l_tSwcCB.lTimer = 0;
        }
        break;
        
        
        case SWC_STATE_WAIT_PAIR:
            if(CK_NONE != l_tSwcCB.cPairUicc)
            {
                uint8_t i,cKeyCode=CK_NONE; 
              /* for(i = 0; i < CK_NUM;i++)
               {
                   if(la_CodeKeyToUICCMap[i] == l_tSwcCB.cPairUicc)
                   {
                       cKeyCode = i;
                       break;
                   }
               }*/
               
                for(i = 0;i< D_SWC_PLUS_RESISTANCE_NUM;i++)
                {
                    _SWC_TmpUicc(_SWC_CHIdx,i,_SWC_RepIdx(_SWC_CHIdx,i)) = cKeyCode;
                }
                _SendFullMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_KEY_STATE,OP_SWC_TX_KS_REQ_NEXT,l_tSwcCB.cPairUicc,0,0);

                l_tSwcCB.cPairUicc = CK_NONE;
                l_tSwcCB.iTimer = 0;
                l_tSwcCB.eState = SWC_STATE_SET_PLUSRES_FOR_KEY;
                
            }
        break;
        
        case SWC_STATE_EXIT:
        {
            uint8_t i,j;
            _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_RUNMODE,OP_SWC_TX_RM_FINISH);
            l_tSwcCB.eState = SWC_STATE_IDLE;
            for(i = 0; i< D_SWC_KEY_CHANNEL_NUM;i++)
                for(j=0;j<D_SWC_PLUS_RESISTANCE_NUM;j++)_SWC_KeyNum(i,j) = 0;
        }
        break;
        case SWC_STATE_TIMEOUT:
        {
            uint8_t i,j;
            _SendFullMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_KEY_STATE,OP_SWC_TX_KS_TIMEOUT,0,0,0);
            l_tSwcCB.eState = SWC_STATE_IDLE;
            l_tSwcCB.lTimer = 0;
            for(i = 0; i< D_SWC_KEY_CHANNEL_NUM;i++)
                for(j=0;j<D_SWC_PLUS_RESISTANCE_NUM;j++)_SWC_KeyNum(i,j) = 0;
        }
        break;
        case SWC_STATE_SAVESETTING:
        {
            const tKEY_CTRL_BLOCK* p_tBlock = &la_tSWCKeyCB[_SWC_CHIdx];
            uint8_t delta = p_tBlock->p_tMap->cAttr;
            uint8_t i,j;
            uint8_t cMixDelta[D_SWC_KEY_CHANNEL_NUM][D_SWC_PLUS_RESISTANCE_NUM];
            uint8_t cChValidIdx[D_SWC_KEY_CHANNEL_NUM];
            //get every min delate;
            for(i = 0;i< D_SWC_KEY_CHANNEL_NUM;i++)
            { 
                cChValidIdx[i] = 0xff;
                for(j = 0;j < D_SWC_PLUS_RESISTANCE_NUM;j++)
                {
                    uint8_t cKn1 = _SWC_KeyNum(i,j);
                    uint8_t cKn2 = _SWC_KeyNum(i,j);
                    uint8_t n1,n2;
					uint8_t cAdValue = _SWC_IdleKeyValue(i,j);
					cMixDelta[i][j] = 0xff;
					
                    for(n1= 0; n1 < cKn1; n1++)
                    {
                        uint8_t tmpKey1 = _SWC_TmpVol(i,j,n1);
                        uint8_t tmpdelta;
                        for(n2= 0; n2 < cKn2; n2++)
                        {
                            CLEAR_WATCHDOG();
                            if(n1!=n2)
                            {
                                if(tmpKey1 > _SWC_TmpVol(i,j,n2))tmpdelta = tmpKey1 - _SWC_TmpVol(i,j,n2);
                                else tmpdelta =  _SWC_TmpVol(i,j,n2) - tmpKey1 ;

                                if(tmpdelta < cMixDelta[i][j]) cMixDelta[i][j] = tmpdelta; 
                            }
                        }
                    }
                }
            }

            //get the channel which delate is max
            for(i = 0;i< D_SWC_KEY_CHANNEL_NUM;i++)
            {
                uint8_t tmpDelate = 0;
                for(j = 0;j < D_SWC_PLUS_RESISTANCE_NUM;j++)
                {
                    if(_SWC_KeyNum(i,j))
                    {
                        if(tmpDelate < cMixDelta[i][j])
                        {
                            tmpDelate = cMixDelta[i][j];
                        }
                    }
                    if(delta < tmpDelate)cChValidIdx[i] = j;
                    swc_printf(_T("SWC CH %d bigger delate is :%d\n",i,tmpDelate));
                }
            }

            //save data:
            for(i = 0;i < D_SWC_KEY_CHANNEL_NUM;i++)
            {   
                uint8_t idx = cChValidIdx[i];
                l_tSwcRomData.tSwcLogicMap[i].cNum = 0;
                if(idx < D_SWC_PLUS_RESISTANCE_NUM)
                {
                    
                    l_tSwcRomData.cResistanceIdx[i] = idx;
                    l_tSwcRomData.tSwcLogicMap[i].cNum = _SWC_KeyNum(i,idx);
                    swc_printf(_T("SWC CH Select res idx:%d\n",idx));
                    for(j = 0;j < _SWC_KeyNum(i,idx);j++)
                    {
                        l_tSwcRomData.tSwcLogicMap[i].tKeyMap[j].cPhyValue = _SWC_TmpVol(i,idx,j);
                        l_tSwcRomData.tSwcLogicMap[i].tKeyMap[j].clogicValue = _SWC_TmpUicc(i,idx,j);
                    }
                    _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_RUNMODE,OP_SWC_TX_RM_FINISH);
                }
                else if(_SWC_KeyNum(i,idx))
                {
                    //Error. cant get the swc key
                    _SendFullMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_SWC_KEY_STATE,OP_SWC_TX_KS_NSUPPORT,0,0,0);
                }

                for(j=0;j<D_SWC_PLUS_RESISTANCE_NUM;j++)_SWC_KeyNum(i,j) = 0;
            }
            EEP_CreateBlockChkSum(&l_tSwcEepData);
            EEP_WriteStart(&l_tSwcEepData,0);
            l_tSwcCB.eState = 0;

        }
        break;        

    }

#undef _SWC_ResIdx             
#undef _SWC_CHIdx  
#undef _SWC_KeyNum    
#undef _SWC_IdleKeyValue 
#undef _SWC_TmpVol    
#undef _SWC_TmpUicc    

    if(l_tSwcCB.eState > SWC_STATE_CHECK_IDLE_VAL)
    {
        if(l_tSwcCB.lTimer ++ > _set_timing_xms_base_hmi_task_tick(30000))//30s time out
        {
                l_tSwcCB.eState = SWC_STATE_TIMEOUT;
        }
    }

}






void HMI_SWCInit(void)
{
    
	IO_Get(IO_IDX_SWC1_DET,PIN_INPUT,INVALID);
	IO_Get(IO_IDX_SWC2_DET,PIN_INPUT,INVALID);
    API_MemClear((uint8_t*)&l_tSwcCB,sizeof(tSWC_CTRL_BLOCK));
    HMI_CreatKeyScan(&la_tSWCKeyCB[0],(tKEY_MAP *)&l_tSwcRomData.tSwcLogicMap[0],SWC_GetKey1Value,HMI_KEY_DEV_SWC1);
    HMI_CreatKeyScan(&la_tSWCKeyCB[1],(tKEY_MAP *)&l_tSwcRomData.tSwcLogicMap[1],SWC_GetKey2Value,HMI_KEY_DEV_SWC2);
}





