#define _CANBUS_C
#include "..\..\config\inc.h"
#include "..\..\CanIf\CanIf.h"
#include "..\..\Com\Com.h"
#include "..\..\ComUser\ComUser.h"
#include "..\..\CanTp\CanTp.h"
#include "..\..\Dcm\Dcm.h"

#ifdef CAN_MODULE_ENABLE

CanMsgStruct  CANRxMsgBuff;

CAN_USED_CFG  CANModuleCfg;
uint8_t TestPulse;
uint8_t CAN0WakePulse;
uint8_t Can_Vol_Reverse;   
uint8_t AvmExistFlag = 0;

typedef enum
{
    CAN_PM_IDLE,
    CAN_PM_WAIT_HALFSLEEP,
    CAN_PM_HALFSLEEP,
    CAN_PM_WAIT_SLEEP,
    CAN_PM_SLEEP,
    CAN_PM_NORMAL,
    CAN_PM_NORMAL_HIDE,
    CAN_PM_WAIT_BUS,
    CAN_PM_WAIT_SHUT,
    CAN_PM_LVI,
    CAN_PM_HVI,
    CAN_PM_UNNORMAL,
} eCAN_PM_STATE;

typedef struct
{
    uint16_t Timer1S;
	uint16_t WaitTimer1S;
    uint8_t Timer10ms;
    uint8_t state;
    uint8_t SysPmState;
    uint8_t LastState;
    uint8_t BattVoltState;
    uint8_t SysINH;
    uint8_t BusEnableFlag		:1;	/*Flag to indict CAN BUS on/off */
    uint8_t BusConnectFlag	:1;	/*when received CAN BUS , FLAG IS 1 */
    uint8_t LocalACC			:2;	/*local hardware ACC line signal */
    uint8_t BusACC			:2;	/*CAN BUS ACC signal */
    uint8_t SysWorkState		:2;	/*1- normal work, 0- sleep, 3- invalid  */
    uint8_t AccoffNotSleepFlag;
    uint8_t ACCOffTimer1S;		/* ACC OFF start timer, used for OP_PM_STATE_OFF command send */
    uint8_t SetAmpOnCnt;
    uint8_t SetAmpOffCnt;
} CanPMStateStruct;

/*
//snake20160816 move to canbus.h and set this extern
typedef struct
{
    uint8_t APUStatus;
    uint8_t ACC		:2;
    uint8_t SpiReady	:2;		//SPI comm is ready, could sync data 
} SysStatusStruct;
*/


CanPMStateStruct  CanPMState;


static void CANTask_MediaCanHandler(void);
static void CANTask_DataSync(void);
void CAN_EepRead(void);

#define BUS_SPECL_CODE		0x26
#define EEP_WRITE_DELAY	10
#define ACCOFF_TIMEOUT_S	120		/*ACC OFF timeout  setting */
#define BUSOFF_TIMEOUT_S   10

tEEP_DATA_BLOCK l_tEepBusCB;
const tEEP_DATA lc_tEepBusCB =
{
    D_EEP_CANBUS_ID,
    (uint8_t*)&l_tBusData,
    NULL,
    D_EEP_CANBUS_ADDR,
    sizeof(tBUS_EEP_DATA),
    1
};

#define CAN_EEP_IDLE			0
#define CAN_EEP_ERR				1
#define CAN_EEP_LOAD_REQ		2
#define CAN_EEP_LOAD_WAIT		3
#define CAN_EEP_WRITE_REQ		4
#define CAN_EEP_WRITE_WAIT	5
#define CAN_EEP_UNVALID		0xff		/*EEP IS unvalid */

typedef struct
{
    uint8_t 	OpState;
    uint8_t	TryCnt;
    uint8_t	Timer;
    uint8_t*	pBuffer;
	uint8_t Cnt;
} CAN_EEP_MANAGE_STRUCT;

CAN_EEP_MANAGE_STRUCT  	BusEepManager;
SysStatusStruct   SystemStatus;


//snake20160806 add param len
void CAN_LoadDefaultEOLByCarType(uint8_t *pData,uint8_t CarType,uint8_t len)
{
	uint8_t i;
	const uint8_t * pCarTypeDefaultEOL=NULL;
	if((NULL==pData)||(CarType>=CAR_TYPE_SEL_MAX))
	{
		return;
	}
	pCarTypeDefaultEOL=pUds_GetCarTypeDefaultEOL(CarType);
	if(NULL!=pCarTypeDefaultEOL)
	{
		Memory8Copy(pData, (uint8_t *)pCarTypeDefaultEOL, len);
	}
}

#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
void CANbus_VehicleVariableReset(void)
{
    l_tBusData.VehicleData1.Acc_desWarnMode = 0;
	l_tBusData.VehicleData1.Fcw_autobrakeEnable = 1;
	l_tBusData.VehicleData1.Fcw_crashWarnEnable = 1;
	l_tBusData.VehicleData1.Rcw_bsdEnable = 1;
	l_tBusData.VehicleData1.Rcw_ctaEnable = 1;
	l_tBusData.VehicleData1.Rcw_crashWarnEnable = 1;
	l_tBusData.VehicleData1.Ldw_sensitivity = 0;
	l_tBusData.VehicleData2.Ldw_hmaEnable = 0;
	l_tBusData.VehicleData2.Ldw_slaSwitch = 1;
}
#endif

uint8_t EOLArray[] = {0xF7,0x77,0x76,0x76,0x84,0x04,0x34,0x77,0x34,0x77,0x34,0x77,0x00,0x00,0x74,0x74,0xf7};
//通锟斤拷锟斤拷值锟斤拷锟斤拷取锟斤拷锟斤拷锟叫碉拷锟斤拷锟斤拷.
//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟皆拷锟斤拷锟饺碉拷时锟斤拷,取前锟斤拷锟斤拷锟斤拷锟斤拷锟�
uint8_t Get_ArrayIndex(uint8_t * pData, uint8_t Value, uint8_t len)
{
	uint8_t i = 0;
	for(i = 0;i < len;i++)//顺锟斤拷锟斤拷锟街革拷锟斤拷锟斤拷诖锟斤拷锟�...
	{
		if(*(pData+i) == Value)
		{
			return i;
		}
	}
	return 0xff;//没锟叫诧拷询锟斤拷锟斤拷鹊锟斤拷锟斤拷锟�
}
//通锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取锟斤拷锟斤拷锟叫碉拷值.
uint8_t Get_ArrayValue(uint8_t *pData,uint8_t Index)
{
	return *(pData+Index);
}



void CAN_LoadDefaultToEepRam(void)
{
    uint8_t cnt = 0;
	uint8_t index = 0;
#ifdef UDS_ENABLE_MACRO
    for(cnt =0; cnt< DID_F190_LENGTH; cnt++)
    {
        l_tBusData.DID_F190_DATA[cnt] = '0'+cnt;
    }
    cnt = 0;
    l_tBusData.DID_F18C_DATA[cnt++] = 23;
    l_tBusData.DID_F18C_DATA[cnt++] = 45;
    l_tBusData.DID_F18C_DATA[cnt++] = 67;
    l_tBusData.DID_F18C_DATA[cnt++] = 89;
    l_tBusData.DID_F18C_DATA[cnt++] = '0';
    l_tBusData.DID_F18C_DATA[cnt++] = '1';
    l_tBusData.DID_F18C_DATA[cnt++] = '2';
    l_tBusData.DID_F18C_DATA[cnt++] = '3';
    l_tBusData.DID_F18C_DATA[cnt++] = '4';
    l_tBusData.DID_F18C_DATA[cnt++] = '5';
    l_tBusData.DID_F18C_DATA[cnt++] = 16;
    l_tBusData.DID_F18C_DATA[cnt++] = 5;
    l_tBusData.DID_F18C_DATA[cnt++] = 30;

	/*-----------add it for exchanging machine ztqin 20150112----------*/
	for(cnt=0;cnt<DID_LEN_PHONE;cnt++)
	{
		l_tBusData.Phone[cnt]="13800138000"[cnt];
	} 

	//锟斤拷锟接讹拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟捷碉拷锟叫讹拷,锟斤拷锟节斤拷锟斤拷使锟斤拷锟斤拷一锟斤拷锟街斤拷...
	index = Get_ArrayIndex(EOLArray,l_tBusData.DID_F1FA_DATA[0],sizeof(EOLArray)/sizeof(EOLArray[0]));
	if((0xff == index) ||
		 ((0xff != index) && 
		  (l_tBusData.DID_F1FA_DATA[1] != 0) && (l_tBusData.DID_F1FA_DATA[2] != 0) && 
		  (l_tBusData.DID_F1FA_DATA[3] != 0) && (l_tBusData.DID_F1FA_DATA[4] != 0) && (l_tBusData.DID_F1FA_DATA[5] != 0)))
	{
		TaskCAN_debug(_T("[read fail]  index = %d,l_tBusData.DID_F1F8_DATA:%x %x %x %x %x %x\n",index,l_tBusData.DID_F1FA_DATA[0],l_tBusData.DID_F1FA_DATA[1],
			l_tBusData.DID_F1FA_DATA[2],l_tBusData.DID_F1FA_DATA[3],l_tBusData.DID_F1FA_DATA[4],l_tBusData.DID_F1FA_DATA[5]));
		CAN_LoadDefaultEOLByCarType(l_tBusData.DID_F1FA_DATA,CAR_TYPE,DID_F1FA_LENGTH);
		TaskCAN_debug(_T("[write new data]  CAN_LoadDefaultEOLByCarType:%x %x %x %x %x %x\n",l_tBusData.DID_F1FA_DATA[0],l_tBusData.DID_F1FA_DATA[1],
			l_tBusData.DID_F1FA_DATA[2],l_tBusData.DID_F1FA_DATA[3],l_tBusData.DID_F1FA_DATA[4],l_tBusData.DID_F1FA_DATA[5]	));
	}

	
#endif
	
#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
	CANbus_VehicleVariableReset();
#endif

	//snake20161017 GPS锟斤拷默锟较诧拷锟斤拷   默锟较讹拷位锟斤拷息为锟斤拷锟斤拷锟矫帮拷锟斤拷锟斤拷锟斤拷锟斤拷麓锟�
	GpsInfo.Longitude = 106617119;
	GpsInfo.Latitude= 29667951;
	GpsInfo.LatitudeFlag = 0;
	GpsInfo.LatitudeFlag= 0;
	GpsInfo.GpsValid = 1;

	
    l_tBusData.SpecialCode = BUS_SPECL_CODE;
}

uint8_t CanBus_GetEepOpState(void)
{
	return BusEepManager.OpState;
}

static uint8_t CanBus_ChkValidPhoneInfo(void *pData)
{
	uint8_t i;
	uint8_t RetValue=FALSE;
	tBUS_EEP_DATA *pChkData=(tBUS_EEP_DATA *)pData;
	
	if((NULL==pData)||(NULL==pChkData))
	{
		return RetValue;
	}
	for(i=0;i<DID_LEN_PHONE;i++)
	{
		if((pChkData->Phone[i]<'0')||(pChkData->Phone[i]>'9'))
		{
			break;
		}
	}
	if(i>=DID_LEN_PHONE)
	{
		RetValue=TRUE;
	}
	return RetValue;
}

#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
extern CarAccCtrlStruct	CAN_AccCtrlStr;
extern CarFcwStruct		CAN_FcwStr;
extern CarRcwStruct		CAN_RcwStr;
extern CarLdwSensStruct CAN_LdwStr;
extern CarLightDataStruct          CAN_CarLightDataStr;
extern uint8_t Body513Buff[8];
#endif

void CAN_EepManager(void)
{
    uint8_t temp = 0;
    switch(BusEepManager.OpState)
    {
    case CAN_EEP_IDLE:
        break;
    case CAN_EEP_LOAD_REQ:
        if(TRUE == EEP_ReadStart(&l_tEepBusCB))
        {
            BusEepManager.OpState = CAN_EEP_LOAD_WAIT;
        }
        break;
    case CAN_EEP_LOAD_WAIT:
        temp = EEP_WaitOptionReturn(&l_tEepBusCB, TIMER_10000MS);
        if(temp == EEP_OPTION_READ_COMPLETE)
        {
           if((EEP_BlockCheck(&l_tEepBusCB) == FALSE)
               ||(l_tBusData.SpecialCode != BUS_SPECL_CODE)
               ||(FALSE==CanBus_ChkValidPhoneInfo((void *)&l_tBusData)))
            {
				BusEepManager.Cnt++;
				TaskCAN_debug(_T("BusEepManager.Cnt = %d,l_tBusData.SpecialCode = %x,BUS_SPECL_CODE = %x\n",BusEepManager.Cnt,l_tBusData.SpecialCode,BUS_SPECL_CODE));
				if(BusEepManager.Cnt <= 3)
				{
				    l_tBusData.iCheckSum = 0x00;
			        BusEepManager.OpState = CAN_EEP_IDLE;
			        CAN_EepRead();
					TaskCAN_debug(_T("BusData verify fail......read again!!!!!!!!!!\n"));
					return;
				}
				else
				{
					BusEepManager.Cnt = 0;
	                CAN_LoadDefaultToEepRam();
	                EEP_CreateBlockChkSum(&l_tEepBusCB);
	                EEP_WriteStart(&l_tEepBusCB,EEP_WRITE_DELAY);
	                BusEepManager.OpState = CAN_EEP_WRITE_WAIT;
				}
            }
            else
            {
                BusEepManager.OpState = CAN_EEP_IDLE;
            }
#ifdef UDS_ENABLE_MACRO
	UdsFbl_LoadSysData(&l_tBusData);
	#if (PROJECT_CODE == CHANGAN_S401)
	CANAPI_LoadEOLInfo(DID_ID_F1F8,l_tBusData.DID_F1F8_DATA,DID_F1F8_LENGTH); 
	#elif (PROJECT_CODE == CHANGAN_R103_H15T)
	CANAPI_LoadEOLInfo(DID_ID_F1FA,l_tBusData.DID_F1FA_DATA,DID_F1FA_LENGTH); 
	#endif
	CanAPI_LoadTboxPhoneInfo(l_tBusData.Phone, DID_LEN_PHONE);
#endif
#if	D_CAN_VEHICLE_SET_STORE_IN_EEPROM
	CAN_AccCtrlStr.DesWarnMode = l_tBusData.VehicleData1.Acc_desWarnMode;
	CAN_FcwStr.FcwEnable = l_tBusData.VehicleData1.Fcw_crashWarnEnable;
	CAN_FcwStr.AutoBrakeEnable = l_tBusData.VehicleData1.Fcw_autobrakeEnable;
	CAN_RcwStr.BsdEnable = l_tBusData.VehicleData1.Rcw_bsdEnable;
	CAN_RcwStr.CtaEnable = l_tBusData.VehicleData1.Rcw_ctaEnable;
	CAN_RcwStr.RcwEnable = l_tBusData.VehicleData1.Rcw_crashWarnEnable;
	CAN_LdwStr.LdwSensDat = l_tBusData.VehicleData1.Ldw_sensitivity;
	CAN_LdwStr.SlaEnable = l_tBusData.VehicleData2.Ldw_slaSwitch;
	CAN_CarLightDataStr.HmaEnable = l_tBusData.VehicleData2.Ldw_hmaEnable;
	TaskCAN_debug(_T("CANUser GetCanbus vehicle set from eeprom\n"));
	memset(Body513Buff,0,8);
	CAN_Get_Body513Data();
#endif
        }
        else if( temp >= EEP_OPTION_IICERR)
        {
            BusEepManager.OpState = CAN_EEP_ERR;
            CAN_LoadDefaultToEepRam();
			#if (PROJECT_CODE == CHANGAN_S401)
				CANAPI_LoadEOLInfo(DID_ID_F1F8,l_tBusData.DID_F1F8_DATA,DID_F1F8_LENGTH); 
			#elif (PROJECT_CODE == CHANGAN_R103_H15T)
				CANAPI_LoadEOLInfo(DID_ID_FD01,l_tBusData.DID_F1F8_DATA,DID_FD01_LENGTH); 
			#endif	     
			CanAPI_LoadTboxPhoneInfo(l_tBusData.Phone, DID_LEN_PHONE);
            EEP_CreateBlockChkSum(&l_tEepBusCB);
            EEP_WriteStart(&l_tEepBusCB, EEP_WRITE_DELAY);
        }
        break;
    case CAN_EEP_WRITE_REQ:
        if(TRUE == EEP_WriteStart(&l_tEepBusCB, EEP_WRITE_DELAY))
        {
            BusEepManager.OpState = CAN_EEP_WRITE_WAIT;
        }
        break;
    case CAN_EEP_WRITE_WAIT:
        temp = EEP_WaitOptionReturn(&l_tEepBusCB, TIMER_10000MS);
        if( temp == EEP_OPTION_WRITE_COMPLETE)
        {
            BusEepManager.OpState = CAN_EEP_IDLE;
        }
        else if( temp >= EEP_OPTION_IICERR)
        {
            BusEepManager.OpState = CAN_EEP_ERR;
        }
        break;
    case CAN_EEP_ERR:
    case CAN_EEP_UNVALID:
        break;
    default:
        break;
    }
}

void CAN_EepRead(void)
{
    if((BusEepManager.OpState != CAN_EEP_ERR) &&
            (BusEepManager.OpState != CAN_EEP_IDLE))
        return;
    BusEepManager.OpState = CAN_EEP_LOAD_REQ;
}

#define WR_EEP_REQ    0
#define WR_EEP_NO_REQ  1
#if 1
//snake 20160515
//锟斤拷锟斤拷0,写锟斤拷晒锟�;锟斤拷锟斤拷锟斤拷锟斤拷,写锟斤拷失锟斤拷(锟斤拷锟节匡拷锟斤拷锟斤拷为写锟斤拷失锟杰的达拷锟斤拷锟斤拷锟�)
uint8_t CAN_EepStore(uint16_t DID, uint8_t *pData, uint8_t len)
{
	uint8_t EepStoreStep=WR_EEP_NO_REQ;
	if((BusEepManager.OpState != CAN_EEP_ERR) &&
		(BusEepManager.OpState != CAN_EEP_IDLE))
		return 1;//eep is busy
#ifdef UDS_ENABLE_MACRO
	TaskCAN_debug(_T("EEPStore:DID = 0x%lx,LEN = %d\n",DID,len));
	switch(DID)
	{
		case DID_ID_FD01:
			Memory8Copy(l_tBusData.DID_FD01_DATA, pData,len);//R103-H15T EOL
			break;
		case DID_ID_F184:
			Memory8Copy(l_tBusData.DID_F184_DATA, pData,len);
			break;
		case DID_ID_F18C:
			Memory8Copy(l_tBusData.DID_F18C_DATA, pData,len);
			break;			
		case DID_ID_F190:
			Memory8Copy(l_tBusData.DID_F190_DATA, pData,len);
			//CANTask_SendApiData(OMS_CAN_TX_CAR, OP_CAN_TX_CAR_VIN, 0);//snake 20160526 delete	
			break;
		case DID_ID_F1A0:
			Memory8Copy(l_tBusData.DID_F1A0_DATA, pData,len);
			break;			
		case DID_ID_F1A2:
			Memory8Copy(l_tBusData.DID_F1A2_DATA, pData,len);
			break;
		case DID_ID_F1FA://R103-H15T EOL
			Memory8Copy(l_tBusData.DID_F1FA_DATA, pData,len);
			TaskCAN_debug(_T("F1FA_DATA:%x %x %x %x %x %x\n",l_tBusData.DID_F1FA_DATA[0],l_tBusData.DID_F1FA_DATA[1],l_tBusData.DID_F1FA_DATA[2],
				l_tBusData.DID_F1FA_DATA[3],l_tBusData.DID_F1FA_DATA[4],l_tBusData.DID_F1FA_DATA[5]));
			break;
		case DID_ID_F1F8:
			Memory8Copy(l_tBusData.DID_F1F8_DATA, pData,len);
		case DID_ID_F101:
			Memory8Copy(l_tBusData.DID_F101_DATA, pData,len);//S401  EOL	
		default:
			return 2;//invalid DID
	}
#endif

	EEP_CreateBlockChkSum(&l_tEepBusCB);
	EEP_WriteStart(&l_tEepBusCB,1);//snake 20160515
	//BusEepManager.OpState = CAN_EEP_WRITE_REQ;
	return 0;
}

#else
void CAN_EepStore(uint16_t DID, uint8_t *pData, uint8_t len)
{
	 uint8_t EepStoreStep=WR_EEP_NO_REQ;
	if((BusEepManager.OpState != CAN_EEP_ERR) &&
		(BusEepManager.OpState != CAN_EEP_IDLE))
		return;

#ifdef UDS_ENABLE_MACRO
	switch(DID)
	{
		case DID_ID_FD01:
			Memory8Copy(l_tBusData.DID_FD01_DATA, pData,len);
			CANTask_SendApiData(OMS_CAN_TX_SYS, OP_CAN_TX_EOL, 0);
			EepStoreStep=WR_EEP_REQ;
			break;
			
		case DID_SN:
			Memory8Copy(l_tBusData.DID_F18C_DATA, pData,len);
			EepStoreStep=WR_EEP_REQ;
			break;
		case DID_VIN:
			Memory8Copy(l_tBusData.VIN, pData,len);
			CANTask_SendApiData(OMS_CAN_TX_CAR, OP_CAN_TX_CAR_VIN, 0);
			break;
		case DID_TBOXREGNUM:
			if(len<=DID_LEN_PHONE)
			{
				Memory8Copy(l_tBusData.Phone, pData,len);
				CanAPI_LoadTboxPhoneInfo(l_tBusData.Phone, DID_LEN_PHONE);
				CANTask_SendApiData(OMS_CAN_TX_CAR, OP_CAN_TX_TBOX_PHONE, 0);	
				EepStoreStep=WR_EEP_REQ;
			}
		break;
		default:
			return;
	}
#endif
	if(EepStoreStep==WR_EEP_REQ)
	{
		EEP_CreateBlockChkSum(&l_tEepBusCB);
		BusEepManager.OpState = CAN_EEP_WRITE_REQ;
	}

}

#endif 

#if D_CAN_VEHICLE_SET_STORE_IN_EEPROM
void CAN_VehicleEepStore(void)
{
	uint8_t EepStoreStep=WR_EEP_NO_REQ;
	if((BusEepManager.OpState != CAN_EEP_ERR) &&
		(BusEepManager.OpState != CAN_EEP_IDLE))
		return;
	
	EepStoreStep=WR_EEP_REQ;

	if(EepStoreStep==WR_EEP_REQ)
	{
		EEP_CreateBlockChkSum(&l_tEepBusCB);
		BusEepManager.OpState = CAN_EEP_WRITE_REQ;
	}


}
#endif



void TestIO1_Output(uint8_t mode, uint8_t level)
{
    if(mode == 0)
    {
        IO_Set(IO_IDX_TEST1,PIN_OUTPUT,level);
        TestPulse = level;
    }
    else
    {
        TestPulse = !TestPulse;
        IO_Set(IO_IDX_TEST1,PIN_OUTPUT,TestPulse);
    }
}

void CAN0_LocalWakeup(uint8_t type, uint8_t level)
{
    if(type == 0)
    {
        CAN0WakePulse = level;
    }
    else
    {
        CAN0WakePulse = !CAN0WakePulse;
    }
    IO_Set(IO_IDX_CAN0_WAKE,PIN_OUTPUT,CAN0WakePulse);

    //TaskCAN_debug(_T("CAN0 wake pulse:%d\n", CAN0WakePulse));
}

/****************************************************************************
 * @function	CAN_SoftTimerHandler
 * @brief  	CAN module Timer handler
 * @param  	null
 * @retval 	null
 * @attention:  place this function to the timebase fuction to tick it.
****************************************************************************/
void CAN_SoftTimerHandler(void)
{
    if(CANModuleCfg.UsedCANNum == 1)
    {
        CANbus_AppLayerSoftTimerDeal(CANModuleCfg.UsedCANId[0]);
    }
    else if(CANModuleCfg.UsedCANNum == 2)
    {
        CANbus_AppLayerSoftTimerDeal(CANModuleCfg.UsedCANId[0]);
        CANbus_AppLayerSoftTimerDeal(CANModuleCfg.UsedCANId[1]);
    }
    CANbus_AppLayerRealTimerDeal();
}

uint8_t CANTask_Init(void)
{
    TestPulse = 0;
    CANUser_InitParam(&CANModuleCfg);
    CANbus_AppLayerColdInit();
    sCANModule.BusOffMode[0] = 0;
    sCANModule.BusOffMode[1] = 0;
    sCANModule.CANMode[0] = CAN_APP_MODE_IDLE;
    sCANModule.CANMode[1] = CAN_APP_MODE_IDLE;
    sCANModule.SysState = CAN_SYS_OFF;
    sCANModule.DataSyncStatus = CAN_MSG_SYNC_NO;
    sCANModule.Ticks_Count = 0;
    sCANModule.DisVideo = 3;
    sCANModule.SpeedCnt = 0;

    SystemStatus.APUStatus = OP_DEV_STATE_OFF;
    SystemStatus.ACC = 3;
    SystemStatus.SpiReady = 0;

	//锟斤拷锟劫匡拷锟斤拷ACC锟斤拷锟斤拷BATT锟斤拷时锟斤拷,锟斤拷要锟斤拷锟铰斤拷锟叫筹拷始锟斤拷....
	Mult_Struct.AccState = 0;//snake20160926
	Mult_Struct.AccStateBK = 0;
	Mult_Struct.IllState = 0;
	Mult_Struct.IllStateBK = 0;
	Mult_Struct.ApuEnterSys = 0;
	Mult_Struct.ApuEnterSysBK = 0;
	
    CANUser_ParamColdInit();
    CAN_Api_Init();
    IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,INVALID);
    IO_Scan_Set(IO_IDX_LOCAL_ACC,VALID);
    TaskCAN_debug(_T("CANTask_Init()!\n"));
    CANbus_EnableCANTransceiver(CAN_ID_BODY, CAN_TRANSCEIVER_MODE_SLEEP);
    CANbus_EnableCANTransceiver(CAN_ID_INNER, CAN_TRANSCEIVER_MODE_SLEEP);
#ifdef NM_ENABLE_MACRO
    NM_InterfaceInit();
    IL_CanNM_Init();
	TaskCAN_debug(_T("CANTask_Init......Open NM_ENABLE_MACRO,init NM!!!!\n"));
#else  //snake2016116 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟杰碉拷时锟斤拷,ACC OFF,锟斤拷锟斤拷BATT,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷睡锟竭碉拷锟斤拷锟斤拷
	CANbus_DefaultInit(CAN_ID_BODY);		
	CANbus_StartupHandler(CAN_ID_BODY);
	//CANUser_StartSendInitMsg(CAN_ID_BODY);//锟斤拷锟斤拷CAN锟斤拷锟侥凤拷锟斤拷...
	//CANUser_TryToSendCANMsg(CAN_ID_BODY);
	TaskCAN_debug(_T("CANTask_Init......Close NM_ENABLE_MACRO,init canbus!!!!\n"));
#endif
    return TRUE;
}

uint8_t CANTask_WarmInit(void)
{
    CANbus_AppLayerColdInit();
    sCANModule.BusOffMode[0] = 0;
    sCANModule.BusOffMode[1] = 0;
    sCANModule.CANMode[0] = CAN_APP_MODE_IDLE;
    sCANModule.CANMode[1] = CAN_APP_MODE_IDLE;
    sCANModule.SysState = CAN_SYS_ON;
    sCANModule.DataSyncStatus = CAN_MSG_SYNC_NO;

    CanPMState.state = CAN_PM_IDLE;
    CanPMState.SysPmState = OP_PM_STATE_INVALID;
    CanPMState.Timer1S = 0;

    SystemStatus.APUStatus = OP_DEV_STATE_OFF;

    if(CANModuleCfg.UsedCANNum == 1)
    {
        CANbus_AppLayerReqSwitchMode(CANModuleCfg.UsedCANId[0], CAN_APP_MODE_START);
    }
    else if(CANModuleCfg.UsedCANNum == 2)
    {
        CANbus_AppLayerReqSwitchMode(CANModuleCfg.UsedCANId[0], CAN_APP_MODE_START);
        CANbus_AppLayerReqSwitchMode(CANModuleCfg.UsedCANId[1], CAN_APP_MODE_START);
    }

    CANUser_ParamColdInit();

    return TRUE;
}


void CANTask_PMInit(void)
{
	CanPMState.state = CAN_PM_IDLE;
	CanPMState.SysPmState = OP_PM_STATE_INVALID;
	CanPMState.LastState = OP_PM_STATE_INVALID;
	CanPMState.Timer1S = 0;
	CanPMState.BusEnableFlag = 0;
	CanPMState.BusConnectFlag = 0;
	CanPMState.SysWorkState = 0;
	CanPMState.LocalACC = 3;
	CanPMState.BusACC = 3;
	CanPMState.ACCOffTimer1S = 0;
	CanPMState.AccoffNotSleepFlag = 0;


	TaskCAN_debug(_T("CAN PM init!\n"));
}
 void CANTask_ShutDown(void);
uint8_t CANTask_DeInit(void)
{
#ifdef NM_ENABLE_MACRO
    IL_CanHM_Hardwave_Init(IL_CANNM_HARDWARE_SLEEP);
#else
    CANTask_ShutDown();
#endif
    TaskCAN_debug(_T("CANTask_DeInit()!\n"));
    CANTask_PMInit();
    return TRUE;
}

/****************************************************************************
 * @function	CAN_ReceiveMessageDisposal
 * @brief  	when CAN module receive a Message, disposal  it
 * @param  	null
 * @retval 	null
 * @attention:  null
****************************************************************************/
static void CAN_ReceiveMessageDisposal(void)
{
    if(!CANbus_AppLayerGetMsg(&CANRxMsgBuff))
    {
        CANUser_ReceiveCANMsgHandler(&CANRxMsgBuff);
    }
}

void CANTask_SendPMReqest(uint8_t ReqMode)
{
    _SendFullMsgToHMI(MS_SYS_BUS_INFO ,(OMS_CAN_TX_SYS<<8)|OP_CAN_TX_PM_REQ, ReqMode,0, 0,0);
    switch(ReqMode)
    {
    case OP_PM_STATE_OFF:
        TaskCAN_debug(_T("CAN Req PM : OFF\n"));
        break;
    case OP_PM_STATE_SLEEP:
        TaskCAN_debug(_T("CAN Req PM : SLEEP\n"));
        break;
    case OP_PM_STATE_WAIT_SLEEP:
        TaskCAN_debug(_T("CAN Req PM : WSLEEP\n"));
        break;
    case OP_PM_STATE_ON:
        TaskCAN_debug(_T("CAN Req PM : ON\n"));
        break;
    case OP_PM_STATE_STANDBY:
        TaskCAN_debug(_T("CAN Req PM : STANDBY\n"));
        break;
    default:
        break;
    }
}

void CANTask_SendPrjApiData(uint8_t param, uint8_t sid, uint8_t flag)
{
    void *point = NULL;
	uint8_t i;
	switch(sid)
	{
		case USERID_APU_TX_DVR_SETREQ:
			point  = (void *)pCAN_GetDvrData();
			break;
		case USERID_APU_TX_DVR_VER:
			point = (void *) pCAN_GetDvrVer();
			break;
		default:
			point = NULL;
	}

	if(point != NULL)
	{
		_SendMsgToHMI(MS_SYS_BUS_INFO ,(param<<8)| sid, point);
		TaskCAN_debug(_T("Prj DATA send to APU:param = 0x%x,sid=0x%x\n",param,sid));
	}

	#if 0
	point  = (void *)pCAN_GetDvrData();
	if(USERID_APU_TX_DVR_SETREQ==sid)
	{
		 if(point != NULL)
        	{
        		_SendMsgToHMI(MS_SYS_BUS_INFO ,(CAN_PRJ_ID_CHANA_S401<<8)| sid, point);
        	}
	}
	#endif
	
}

void CANTask_SendApiData(uint8_t param, uint8_t sid, uint8_t flag)
{
    void *point = NULL;

    if(flag == 0)
    {
        /* when sync have done, we can send message dircetly. or we should eject it */
        //if(sCANModule.DataSyncStatus != CAN_MSG_SYNC_END)
        if(sCANModule.DataSyncStatus == CAN_MSG_SYNC_NO)
        {
            return;
        }
    }
    switch(sid)
    {
	case OP_CAN_TX_EOL:
             point = (void *)pCAN_GetEOLStr();
			 TaskCAN_debug(_T("-----Send EOL Data to APU!!!!!!-----\n"));
            break;
	case OP_CAN_TX_CAR_LIGHT:
            point = (void *)pCAN_GetCarLightData();
            break;
        case OP_CAN_TX_CAR_WIPER:
            point = (void *)pCAN_GetCarWiperData();
            break;
	case OP_CAN_TX_FUEL_LEVEL:
            point = (void *)pCAN_GetCarFuelLevelData();
		break;
	case OP_CAN_TX_CAN_PM_DATA:
            point = (void *)pCAN_GetCarCanPmData();
		break;
	case OP_CAN_TX_DOOR_LOCK_INFO:
		point = (void *)pCAN_GetCarDoorLockData();
		break;
        case OP_CAN_TX_CAR_WINDOW:
            point = (void *)pCAN_GetCarWindowData();
            break;
        case OP_CAN_TX_CAR_DOOR:
            point = (void *)pCAN_GetDoorStateData();
            break;
        case OP_CAN_TX_CAR_SEAT:
            point = (void *)pCAN_GetSeatData();
            break;
        case OP_CAN_TX_CAR_RMIRROR:
            point = (void *)pCAN_GetRearMirrorData();
            break;
        case OP_CAN_TX_CAR_MAINTAIN:
            point = (void *)pCAN_GetCarMaintainState();
            break;
        case OP_CAN_TX_ECU_STATE:
            point = (void *)pCAN_GetEcuData();
            break;
	 case OP_CAN_TX_CAR_TBOX:
            point = (void *)pCAN_GetTBOXData();
            break;
        case OP_CAN_TX_CAR_ANGLE:
            point = (void *)pCAN_GetAngleData();
            break;
        case OP_CAN_TX_CAR_SPEED:
            point = (void *)pCAN_GetVehicleSpeed();
            break;
	 case OP_CAN_TX_CAR_SYS:
            point = (void *)pCAN_GetSystemData();
            break;
        case OP_CAN_TX_CAR_PEPS:
            point = (void *)pCAN_GetPEPSData();
            break;
        case OP_CAN_TX_CAR_ECO:
            point = (void *)pCAN_GetVehicleECOData();
            break;
        case OP_CAN_TX_CAR_VIN:
            point = (void *)pCAN_GetVINStr();
            break;
        case OP_CAN_TX_TBOX_TUID:
            point = (void *)pCAN_GetTboxTUIDData();
            break;
        case OP_CAN_TX_TBOX_PHONE:
            point = (void *)pCAN_GetCommonStr();
            break;
	case OP_CAN_TX_AC_FRONT:
            point = (void *)pCAN_GetFrontACData();
            break;
        case OP_CAN_TX_AC_REAR:
            point = (void *)pCAN_GetRearACData();
            break;
        case OP_CAN_TX_AC_OUTTEMP:
            point = (void *)pCAN_GetOutsideTempData();
            break;
        case OP_CAN_TX_AC_SEATHEAT:
            point = (void *)pCAN_GetSeatHeatData();
            break;
	case OP_CAN_TX_RADAR_DATA:
            point = (void *)pCAN_GetRadarData();
            break;
        case OP_CAN_TX_RADAR_STATE:
            point = (void *)pCAN_GetRadarStatusData();
            break;
	 case OP_CAN_TX_TPMS_DATA:
	 		//TaskCAN_debug(_T("---------tpms data send to apu!!!\n"));
            point = (void *)pCAN_GetTPMSData();
            break;
	 case OP_CAN_TX_DTV_STATE:
            point = (void *)pCAN_GetDTVStateData();
            break;
        case OP_CAN_TX_DTV_LIST:
        case OP_CAN_TX_DTV_CAST:
        case OP_CAN_TX_DTV_CA:
            point = (void *)pCAN_GetExtDtvInfoData();
            break;
        case OP_CAN_TX_DTV_VER:
            point = (void *)pCAN_GetDTVVersionData();
            break;
	case OP_CAN_TX_KCP_VER:
            point = (void *)pCAN_GetFCPVersionData();
            break;
	case OP_CAN_TX_AVM_INFO:
            point = (void *)pCAN_GetAVMData();
            break;
	case OP_CAN_TX_CAR_ODO:
		point = (void *)pCAN_GetODOData();
		break;
	case OP_CAN_TX_PRJ_SPCL:
	     point = pCANUser_GetApi(param);
	     break;
	case OP_CAN_TX_ACC_CONTROL_DATA:	// bolte
	     point = pCAN_GetVehicleAccCrlData();
		break;
	case OP_CAN_TX_FCW_DATA:
        TaskCAN_debug(_T("BOLTE:~~_SendMsgToHMI\n"));
	     point = pCAN_GetFcwData();
		break;
	case OP_CAN_TX_RCW_DATA:
	     point = pCAN_GetRcwData();
		break;
	case OP_CAN_ROAD_ASSISTANT:
	     point = pCAN_GetLdwData();
		break;
		
        default:
            break;
    }

    if(point != NULL)
    {
        _SendMsgToHMI(MS_SYS_BUS_INFO ,(OMS_CAN_TX_CAR<<8)| sid, point);
    }
}

/****************************************************************************
 * @function	CANTask_SendKnobInfo
 * @brief  	CAN module send knob information
 * @param  	1. type -0:SEL; -1: VOL
 *			2. dir	-0: left; -1: right
 *			3. diff: change differ value
 * @retval 	null
 * @attention:  called by function of Task_CANbus()
****************************************************************************/
void CANTask_SendKnobInfo(uint8_t type, uint8_t dir, uint8_t diff)
{
    _SendFullMsgToHMI(MS_SYS_BUS_INFO ,(OMS_CAN_TX_SYS<<8)|OP_CAN_TX_CAN_KNOB, type, dir, diff, 0);
}
/****************************************************************************
 * @function	CAN_Manager
 * @brief  	CAN module management
 * @param  	null
 * @retval 	null
 * @attention:  called by function of Task_CANbus()
****************************************************************************/
static  void CANTask_Manager(void)
{
    uint8_t CurMode = 0;
    if(CAN_SYS_OFF != sCANModule.SysState)
    {
        CAN_SoftTimerHandler();
        if(CANModuleCfg.UsedCANNum == 1)
        {
            CANbus_AppLayerHandler(CANModuleCfg.UsedCANId[0]);

        }
        else if(CANModuleCfg.UsedCANNum == 2)
        {

            CANbus_AppLayerHandler(CANModuleCfg.UsedCANId[0]);
            CANbus_AppLayerHandler(CANModuleCfg.UsedCANId[1]);
            CurMode = CANBus_AppLayerGetMode(CANModuleCfg.UsedCANId[1]);
            if(CurMode != sCANModule.CANMode[1])
            {
                sCANModule.CANMode[1] = CurMode;
                if(sCANModule.CANMode[1] == CAN_APP_MODE_ON)
                {
                    CANUser_StartSendInitMsg(CANModuleCfg.UsedCANId[1]);
                }
            }
        }

        if(CANModuleCfg.UsedCANNum !=0)
        {
            CurMode = CANBus_AppLayerGetMode(CANModuleCfg.UsedCANId[0]);
            if(CurMode != sCANModule.CANMode[0])
            {
                sCANModule.CANMode[0] = CurMode;
                if(sCANModule.CANMode[0] == CAN_APP_MODE_ON)
                {
                    CANUser_StartSendInitMsg(CANModuleCfg.UsedCANId[0]);
                }
            }
        }

        CANTask_DataSync();
#ifdef CAN_INNER_ENABLE
        CANbus_InnerLoop();
#endif
    }
    CAN_ReceiveMessageDisposal();
    CANTask_MediaCanHandler();
    CAN_EepManager();
    CANbus_InforOutputMain();
}

void CANTask_StartWork(void)
{
    uint8_t i = 0;
    uint8_t mode;
    if(sCANModule.SysState == CAN_SYS_ON)
    {
        return;
    }
    if(!OS_TaskIsActive(TASK_ID_CANBUS))
    {
        OS_TaskStart(TASK_ID_CANBUS);
    }

    for(i = 0; i<CANModuleCfg.UsedCANNum; i++)
    {
        CANbus_AppLayerReqSwitchMode(CANModuleCfg.UsedCANId[i], CAN_APP_MODE_START);
    }

    sCANModule.BusOffMode[0] = 0;
    sCANModule.BusOffMode[1] = 0;
    sCANModule.CANMode[0] = CAN_APP_MODE_IDLE;
    sCANModule.CANMode[1] = CAN_APP_MODE_IDLE;
    sCANModule.SysState = CAN_SYS_ON;
    sCANModule.DisVideo = 3;
    sCANModule.SpeedCnt = 0;
    CANUser_InitWorkOn();
    TaskCAN_debug(_T("CAN Task Start work\n"));
}

void CANTask_ShutDown(void)
{
    uint8_t i = 0;

    for(i = 0; i<CANModuleCfg.UsedCANNum; i++)
    {
        CANbus_AppLayerReqShutDown(CANModuleCfg.UsedCANId[i]);
        CANbus_AppLayerHandler(CANModuleCfg.UsedCANId[i]);
    }
    sCANModule.SysState = CAN_SYS_OFF;
    TaskCAN_debug(_T("CanTask ShutDown\n"));
}

/****************************************************************************
 * @function	CANTask_OtherMsgHandler
 * @brief  	deal with the message from Other module
 * @param  	Msg: message point
 * @retval 	null
 * @attention:  null
****************************************************************************/
void CANTask_OtherMsgHandler(tMSG_BUF* Msg)
{
    uint8_t IOStatus = IO_Get(IO_IDX_ACC_WAKE,PIN_INPUT,FALSE);//TRUE
    switch(Msg->iSid)
    {
    case OP_OTHER_B:
        TaskCAN_debug(_T("Rcv Other: B\n"));
        if(CanPMState.state != CAN_PM_UNNORMAL)
        {
            CanPMState.LastState = CanPMState.state;
            if(CanPMState.SysWorkState == 1)
            {
                CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
            }
            CanPMState.state = CAN_PM_UNNORMAL;
        }
        CanPMState.BusEnableFlag = 1;
		PanelLed_SwitchDeal(OFF);
        break;
    case OP_OTHER_C:			//DOWN TO LVI
        TaskCAN_debug(_T("Rcv Other: C\n"));
        if(sCANModule.SysState == CAN_SYS_ON)
        {
            CANTask_ShutDown();
        }
        if(CanPMState.state != CAN_PM_UNNORMAL)
        {
            CanPMState.LastState = CanPMState.state;
            CanPMState.state = CAN_PM_UNNORMAL;
        }
        CanPMState.BusEnableFlag = 0;
        CAN0_LocalWakeup(1,0);
		PanelLed_SwitchDeal(OFF);
        break;
    case OP_OTHER_D:
        TaskCAN_debug(_T("Rcv Other: D\n"));
        if(sCANModule.SysState == CAN_SYS_ON)
        {
            CANTask_ShutDown();
        }
        if(CanPMState.state != CAN_PM_UNNORMAL)
        {
            CanPMState.LastState = CanPMState.state;
            if(CanPMState.SysWorkState == 1)
            {
                CANTask_SendPMReqest(OP_PM_STATE_OFF);
            }
            CanPMState.state = CAN_PM_UNNORMAL;
        }
        CanPMState.BusEnableFlag = 0;
        break;
    case OP_OTHER_E:
        TaskCAN_debug(_T("Rcv Other: E\n"));
        if(CanPMState.state == CAN_PM_UNNORMAL)
        {
            if(IOStatus == 1)
            {
                if(sCANModule.SysState != CAN_SYS_ON)
                {
                    CANTask_StartWork();
                }
            }
        }
        CanPMState.BusEnableFlag = 1;
        break;
    case OP_OTHER_F:
    case OP_OTHER_A:
        if(Msg->iSid == OP_OTHER_F)
        {
            TaskCAN_debug(_T("Rcv Other: F\n"));
        }
        else
        {
            TaskCAN_debug(_T("Rcv Other: A\n"));
        }
		if(IO_Get(IO_IDX_LOCAL_ACC, PIN_INPUT,FALSE))
			PanelLed_SwitchDeal(ON);

		#if 0
        if(CanPMState.state == CAN_PM_UNNORMAL)
        {
            CanPMState.state = CanPMState.LastState;
            TaskCAN_debug(_T("Recoverd State:%d\n", CanPMState.state));
            if(IOStatus == 1)
            {
                if((CanPMState.state == CAN_PM_NORMAL) 		\
                        ||(CanPMState.state == CAN_PM_WAIT_HALFSLEEP)		\
                        ||(CanPMState.state == CAN_PM_WAIT_BUS))
                {
                    CANTask_SendPMReqest(OP_PM_STATE_ON);
                }
                if(sCANModule.SysState != CAN_SYS_ON)
                {
                    CANTask_StartWork();
                }
            }
            else
            {
                if(sCANModule.SysState == CAN_SYS_ON)
                {
                    CANTask_ShutDown();
                }
            }
        }
		#else
		CanPMState.state = CAN_PM_IDLE;
		#endif
        CanPMState.BusEnableFlag = 1;
        break;
    case OP_OTHER_G:	/*no used */
    case OP_OTHER_H:
        if(Msg->iSid == OP_OTHER_G)
        {
            TaskCAN_debug(_T("Rcv Other: G\n"));
        }
        else
        {
            TaskCAN_debug(_T("Rcv Other: H\n"));
			PanelLed_SwitchDeal(OFF);
        }
        if(CanPMState.state != CAN_PM_UNNORMAL)
        {
            CanPMState.LastState = CanPMState.state;

            if(sCANModule.SysState == CAN_SYS_ON)
            {
                CANTask_ShutDown();
            }
            if(CanPMState.SysWorkState == 1)
            {
                //CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
		   PM_EnterMode(PM_MODE_OFF); //bolte 锟斤拷压直锟接斤拷锟斤拷锟斤拷模式
	
            }
            CanPMState.state = CAN_PM_UNNORMAL;
        }
        CanPMState.BusEnableFlag = 0;
        break;
    default:
        break;
    }
#ifdef NM_ENABLE_MACRO
    if(CanPMState.BusEnableFlag)
    {
        gILCanNMBatFlag = 1;
    }
    else
    {
        gILCanNMBatFlag = 0;
    }
#endif
}
/****************************************************************************
 * @function	CANTask_SysOnValid
 * @brief  	CAN BUS System open valid state
 * @param
 * @retval 	0- not valid; 1- valid(HU could start screen and work)
 * @attention:  null
****************************************************************************/
uint8_t CANTask_BusConnectFlag(void)
{
    if(BodyECUStatus.AllECU_State)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/****************************************************************************
 * @function	CANTask_GetSysACCState
 * @brief  	CAN BUS System ACC state
 * @param
 * @retval 	0- ACC OFF; 1-ACC ON;
 * @attention:  null
****************************************************************************/
uint8_t CANTask_GetSysACCState(void)
{
    if(CANTask_BusConnectFlag())
    	{
   		 if(1 == CANTask_GetRemoteStartState())		// BOLTE:锟皆诧拷远锟斤拷锟斤拷锟斤拷HU锟斤拷锟斤拷锟斤拷远锟斤拷锟斤拷锟斤拷要锟斤拷HU锟斤拷锟斤拷睡锟斤拷
       		 return 0;
    	}
    if(CanPMState.LocalACC)		/*local ACC first */
    {
        return 1;
    }
#ifdef CAN_PM_ROUTINE_EN
    if(CANTask_BusConnectFlag())
    {
        CANVehicleStateStruct *	ptr = pCAN_GetVehicleState();
        if(ptr->CAN_Acc== 1)
        {
            return 1;
        }
    }
#endif
    return 0;
}
/****************************************************************************
 * @function	CANTask_GetSysLockState
 * @brief  	CAN BUS System lock state
 * @param
 * @retval 	0- unlock; 1-lock; other- unknown
 * @attention:  null
****************************************************************************/
uint8_t CANTask_GetSysLockState(void)
{
    if(CANTask_BusConnectFlag())
    {
        CANVehicleStateStruct *	ptr = pCAN_GetVehicleState();
        return (ptr->CAN_Lock);
    }
    else
    {
        return 1;		/*default lock state */
    }
}
/****************************************************************************
 * @function	CANTask_GetRemoteStartState
 * @brief  	get vehicle PEPS Remote startup status
 * @param
 * @retval 	0- not RS; 1-remote startup;
 * @attention  when remote startup, should not open system.
****************************************************************************/
uint8_t CANTask_GetRemoteStartState(void)
{
    if(CANTask_BusConnectFlag())
    {
        CANVehicleStateStruct *	ptr = pCAN_GetVehicleState();
        if(ptr->CAN_peps == 1)
        {
            return 1;
        }
    }
    return 0;
}
/****************************************************************************
 * @function	CANTask_SysStartupState
 * @brief  	CAN BUS System startup state(SLEEP---> START)
 * @param
 * @retval 	0- not startup; 1-hide startup; 2- normal startup.
 * @attention:  null
****************************************************************************/
uint8_t CANTask_SysStartupState(void)
{
    if(CANTask_GetRemoteStartState())
    {
        return 0;
    }
    if(CANTask_GetSysACCState() ==1)
    {
        return 2;
    }
    else if(CANTask_GetSysLockState() ==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/****************************************************************************
 * @function	CANTask_GetBusSleepState
 * @brief  	CAN BUS Get CAN-BUS sleep State
 * @param
 * @retval 	0- sleep state; 1- wakeup state
 * @attention:
****************************************************************************/
uint8_t CANTask_GetBusSleepState(void)
{
    uint8_t INH = IO_Get(IO_IDX_ACC_WAKE,PIN_INPUT,TRUE); //SystemStatus.ACC	
    uint8_t AccState = CanPMState.LocalACC;
	uint8_t IllState = SystemStatus.ILL;
    CanPMState.SysINH = INH;
	
    /*if(CanPMState.LocalACC==1)
    {
		return 1;
    }*/
    #ifdef D_ILL_WAKEUP
    if((IllState ==1) && (IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE)==0))// 小锟狡匡拷锟斤拷时锟斤拷,锟斤拷ACC  snake20160921
		return 2;
	#endif
	
    if(INH == 0)
    {
        /*锟斤拷ACC OFF锟斤拷时锟戒超时锟襟，诧拷锟杰癸拷确锟斤拷INH = 0;*/
        /*锟斤拷前时锟斤拷为6s, 锟斤拷ACC OFF锟斤拷锟斤拷OP_PM_STATE_WAIT_SLEEP锟斤拷锟斤拷锟斤拷
           锟斤拷时时锟戒。锟斤拷要锟斤拷锟紸CC OFF锟杰匡拷锟斤拷锟斤拷锟斤拷锟竭ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
           锟斤拷锟斤拷锟斤拷锟斤拷狻Ｊ憋拷锟街碉拷锟斤拷锟斤拷诤锟紸CCOFF_TIMEOUT_S锟斤拷锟斤拷锟斤拷*/
           /*//snake20161019
           //锟斤拷为锟斤拷始锟斤拷锟斤拷锟斤拷为0,锟斤拷锟斤拷锟斤拷锟叫碉拷时锟斤拷,锟斤拷没锟斤拷锟斤拷锟矫硷拷锟斤拷锟斤拷CanPMState.ACCOffTimer1S锟斤拷源锟斤拷锟斤拷锟斤拷啪头锟斤拷锟斤拷吮浠�,
           //锟斤拷锟斤拷,锟截伙拷时锟斤拷太锟斤拷,没锟叫帮拷锟斤拷锟斤拷时锟斤拷锟斤拷锟教斤拷锟斤拷锟接迟关伙拷...锟斤拷锟斤拷锟节斤拷锟斤拷时时锟斤拷锟斤拷卸媳锟街撅拷锟斤拷锟轿�1
           */
        if(CanPMState.ACCOffTimer1S == 1)
        {
        	TaskCAN_debug(_T("mcu Enter ACC OFF mode!!!\n"));
            return 0;
        }
    }

    return 1;

}
/****************************************************************************
 * @function	CANTask_SetCanPMStateStructState
 * @brief  	 set CanPMState.state Value
 * @param
 * @retval 	
 * @attention:  
****************************************************************************/
uint8_t CANTask_SetCanPMStateStructState(uint8_t state)
{
	uint8_t result = 0;
	if(state <= CAN_PM_UNNORMAL)
	{
		CanPMState.state = state;
		result = 1;  //set sucess
	}
	return result;
}

/****************************************************************************
 * @function	CANTask_GetCanPMStateStructState
 * @brief  	get CanPMState.state Value
 * @param
 * @retval 	 
 * @attention:   
****************************************************************************/
uint8_t CANTask_GetCanPMStateStructState(void)
{
	return CanPMState.state;
}

/****************************************************************************
 * @function	CANTask_SetCanPMSateStructACCOffTimer1S
 * @brief  	 set CanPMState.ACCOffTimer1S Value
 * @param
 * @retval 	
 * @attention:  
****************************************************************************/
void CANTask_SetCanPMSateStructACCOffTimer1S(uint8_t value)
{
	CanPMState.ACCOffTimer1S = value;
}

/****************************************************************************
 * @function	CANTask_GSetCanPMSateStructACCOffTimer1S
 * @brief  	get CanPMState.ACCOffTimer1S Value
 * @param
 * @retval 	 
 * @attention:   
****************************************************************************/
uint8_t CANTask_GSetCanPMSateStructACCOffTimer1S(void)
{
	return CanPMState.ACCOffTimer1S;
}

/****************************************************************************
 * @function	CANTask_SetCanPMSateStructWaitTimer1S
 * @brief  	 set CanPMState.WaitTimer1S Value
 * @param
 * @retval 	
 * @attention:  
****************************************************************************/
void CANTask_SetCanPMSateStructWaitTimer1S(uint8_t value)
{
	CanPMState.WaitTimer1S = value;
}

/****************************************************************************
 * @function	CANTask_GSetCanPMSateStructWaitTimer1S
 * @brief  	get CanPMState.WaitTimer1S Value
 * @param
 * @retval 	 
 * @attention:   
****************************************************************************/
uint8_t CANTask_GSetCanPMSateStructWaitTimer1S(void)
{
	return CanPMState.WaitTimer1S;
}


/****************************************************************************
 * @function	CANTask_PmRoutine
 * @brief  	CAN BUS Power Manager, control main PM.
 * @param
 * @retval 	null
 * @attention:  null
****************************************************************************/
//#define _CAN_PM_DBG
void CANTask_PmRoutine(void)
{
    uint8_t IOStatus = CANTask_GetBusSleepState();
    uint8_t temp = 0;
#ifdef _CAN_PM_DBG
    static uint8_t bakStatus = 0xff;
    static uint8_t bakAcc = 0xff;

    if(IOStatus != bakAcc)
    {
        bakAcc = IOStatus;
        TaskCAN_debug(_T("SysIO: %d\n", bakAcc));
    }
#endif

    CanPMState.LocalACC = IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE);
#ifdef NM_ENABLE_MACRO
    if(CANTask_GetSysACCState() ==1)
    {
        gsILCanNMNetWorkStatus.Bussleep = 0;
        gILCanNMLocalWakeupFlag = 1;
#ifdef CAN_INNER_ENABLE
        CANbus_InnerWriteAccStatus(1);		/*indictor ACC  = ON */
#endif
    }
    else
    {
        gsILCanNMNetWorkStatus.Bussleep = 1;
#ifdef CAN_INNER_ENABLE
        CANbus_InnerWriteAccStatus(0);		/*indictor ACC  = OFF */
#endif
    }
    if(0 == IO_Get(IO_IDX_ACC_WAKE,PIN_INPUT,FALSE))
    {
        if(!NM_NetNode.RealSleep)
        {
            NM_NetNode.RealSleep = 1;
            NM_NetNode.Wakeup = 0;
        }
    }
    else if(NM_NetNode.RealSleep)
    {
        NM_NetNode.RealSleep = 0;
        NM_NetNode.Wakeup = 1;        /*INH 0-->1, indictor wakeup */
    }
#endif
#ifdef CAN_PM_ROUTINE_EN
    switch(CanPMState.state)
    {
    case CAN_PM_HALFSLEEP:
        if(IOStatus == 0)
        {
            CANTask_SendPMReqest(OP_PM_STATE_OFF);
            CanPMState.state = CAN_PM_SLEEP;
        }
        else
        {
            temp = CANTask_SysStartupState();
            if(temp == 2)
            {
                CANTask_SendPMReqest(OP_PM_STATE_ON);
                CanPMState.state = CAN_PM_NORMAL;
            }
            else if((temp == 1) &&(CanPMState.AccoffNotSleepFlag==0))
            {
                CANTask_SendPMReqest(OP_PM_STATE_STANDBY);
                CanPMState.state = CAN_PM_NORMAL_HIDE;
            }
            else
            {
                if(CanPMState.Timer10ms == 0)
                {
                    CanPMState.Timer10ms = 10;
                    /*every 100ms check state */
                    if(CanPMState.SysWorkState == 1)
                    {
                        CANTask_SendPMReqest(OP_PM_STATE_SLEEP);
                    }
                }
            }
        }
        break;
    case CAN_PM_WAIT_HALFSLEEP:
#if 0		//锟斤拷WAIT_SLEEP模式锟铰ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟竭关伙拷锟斤拷锟斤拷锟斤拷2016-5-29 byzwl
        if(IOStatus == 0)
        {
            CANTask_SendPMReqest(OP_PM_STATE_OFF);
            CanPMState.state = CAN_PM_SLEEP;
        }
        else
#endif
        {
            if(CANTask_GetSysACCState() ==1)
            {

                CANTask_SendPMReqest(OP_PM_STATE_ON);
                CanPMState.state = CAN_PM_NORMAL;
            }
            else
            {
                if(CanPMState.Timer1S >= 600)
                {
                    CanPMState.Timer1S = 600;
                    CANTask_SendPMReqest(OP_PM_STATE_SLEEP);
                    CanPMState.state = CAN_PM_HALFSLEEP;
			CanPMState.AccoffNotSleepFlag = 1;
                }
                else if(CanPMState.Timer10ms == 0)
                {
                    CanPMState.Timer10ms = 10;
                    if(CanPMState.SysPmState == OP_PM_STATE_ON)
                    {
                        CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
                    }
                }
            }
        }
        break;
    case CAN_PM_NORMAL:
	{
		CarAVMDataStruct *pData = pCAN_GetAVMData();
		
	        if(IOStatus == 0)
	        {
	            CANTask_SendPMReqest(OP_PM_STATE_OFF);
	            CanPMState.state = CAN_PM_SLEEP;
	        }
	        else
	        {
	            if(CANTask_GetSysACCState() ==0)
				{
					if(pData->CarAVMReq == 1) // 锟斤拷全锟斤拷模式锟斤拷ACC锟斤拷锟剿筹拷全锟斤拷模式
					{
						CANUser_SetAvmOutCmd();
					}
					CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
					CanPMState.state = CAN_PM_WAIT_HALFSLEEP;
					CanPMState.Timer1S = 0;
					CanPMState.ACCOffTimer1S = ACCOFF_TIMEOUT_S;/*ACC OFF timer-out = 6S*/
					CanPMState.Timer10ms = 10;
				}
				//锟斤拷要锟斤拷锟斤拷锟斤拷ILL锟斤拷锟斤拷锟斤拷锟斤拷锟�,锟斤拷ACC锟斤拷锟竭硷拷 snake20160816
				
	            CanPMState.AccoffNotSleepFlag = 0;
	        }
    	}
        break;
    case CAN_PM_NORMAL_HIDE:
        if(IOStatus == 0)
        {
            CANTask_SendPMReqest(OP_PM_STATE_OFF);
            CanPMState.state = CAN_PM_SLEEP;
        }
        else
        {
            if(CANTask_GetSysACCState() ==1)
            {
                CANTask_SendPMReqest(OP_PM_STATE_ON);
                CanPMState.state = CAN_PM_NORMAL;
            }
            else if(CanPMState.Timer10ms == 0)
            {
                CanPMState.Timer10ms = 10;
                if(CanPMState.SysPmState != OP_PM_STATE_STANDBY)
                {
                    CANTask_SendPMReqest(OP_PM_STATE_STANDBY);
                }
            }
        }
        break;
    case CAN_PM_SLEEP:
    case CAN_PM_IDLE:
	CanPMState.AccoffNotSleepFlag = 0;
        if(IOStatus == 1)
        {
            if(sCANModule.SysState != CAN_SYS_ON)
            {
                CANTask_StartWork();
            }
            temp = CANTask_SysStartupState();
            if(temp == 2)
            {
                CANTask_SendPMReqest(OP_PM_STATE_ON);
                CanPMState.state = CAN_PM_NORMAL;
            }
            else if(temp == 1)
            {
                CANTask_SendPMReqest(OP_PM_STATE_STANDBY);
                CanPMState.state = CAN_PM_NORMAL_HIDE;
                CanPMState.Timer10ms = 10;
            }
            else
            {
                CANTask_SendPMReqest(OP_PM_STATE_SLEEP);
                CanPMState.state = CAN_PM_HALFSLEEP;
            }
        }
        else
        {
            if(CanPMState.SysWorkState == 1)
            {
                CANTask_SendPMReqest(OP_PM_STATE_OFF);
            }
            if(sCANModule.SysState == CAN_SYS_ON)
            {
                CANTask_ShutDown();
            }
        }
        break;
    case CAN_PM_UNNORMAL:
        if(CanPMState.BusEnableFlag && IOStatus)
        {
            if(sCANModule.SysState != CAN_SYS_ON)
            {
                CANTask_StartWork();
            }
        }
        else
        {
            if(sCANModule.SysState == CAN_SYS_ON)
            {
                CANTask_ShutDown();
            }
        }
        break;
    default:
        break;
    }
#else		/*not use CAN bus  PM logic,  */   //R103-H15T  use
    switch(CanPMState.state)
    {
    case CAN_PM_IDLE:
        CanPMState.state = CAN_PM_WAIT_BUS;
        CanPMState.Timer10ms = 5;
        break;
    case CAN_PM_NORMAL:
		/*if(CanPMState.LocalACC == 0)
		{
			CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
			CanPMState.state = CAN_PM_WAIT_SLEEP;
			CanPMState.ACCOffTimer1S = ACCOFF_TIMEOUT_S;
			
		}
		else
		{
			if(CanPMState.Timer10ms == 0)
			{
				CanPMState.Timer10ms = 20;
				if(CanPMState.SysWorkState != 1)
				{
					CANTask_SendPMReqest(OP_PM_STATE_ON);
				}
			}
		}*/


		if(IOStatus == 2)
		{
			if(l_tPwrCB.eMode != PM_MODE_WAIT_SLEEP)
			{
				CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
				CanPMState.state = CAN_PM_WAIT_HALFSLEEP;
			}
		}
		else if(IOStatus == 0)
		{
			CANTask_SendPMReqest(OP_PM_STATE_OFF);
			CANTask_ShutDown();
			CanPMState.state = CAN_PM_SLEEP;
		}
		else
		{
			if(!CanPMState.LocalACC)
			{
				CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
				CanPMState.state = CAN_PM_WAIT_SLEEP;
				CanPMState.ACCOffTimer1S = ACCOFF_TIMEOUT_S;
				CanPMState.WaitTimer1S = 0;
				
			}
			else		// CanPMState.LocalACC == 1
			{
				if(CanPMState.Timer10ms == 0)
				{
		               	CanPMState.Timer10ms = 100;
					if(CanPMState.SysPmState !=OP_PM_STATE_ON)
					{
						CANTask_SendPMReqest(OP_PM_STATE_ON);
					}
				}
			}
		}
		break;

	case CAN_PM_WAIT_HALFSLEEP://锟斤拷小锟狡碉拷时锟斤拷,锟截憋拷ACC锟斤拷状态....锟斤拷锟诫并停锟斤拷锟斤拷WAIT_SLEEP模式...
		if(CanPMState.LocalACC) //锟斤拷ACC,锟斤拷锟斤拷,锟斤拷锟斤拷
		{
			CANTask_SendPMReqest(OP_PM_STATE_ON);
			CanPMState.state = CAN_PM_NORMAL;
		}

		//if(IO_Get(IO_IDX_ILL_DET,PIN_INPUT,FALSE) == 0)//锟斤拷ILL
		if(!SystemStatus.ILL)
		{
			if(l_tPwrCB.eMode != PM_MODE_WAIT_SLEEP)
			CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
			CanPMState.state = CAN_PM_WAIT_SLEEP;
			CanPMState.ACCOffTimer1S = ACCOFF_TIMEOUT_S;
		}
		else
		{
			if(CanPMState.ACCOffTimer1S != 0)
				CanPMState.ACCOffTimer1S = 0;
		}
		break;
    case CAN_PM_WAIT_SLEEP:
		/*
		if(CanPMState.LocalACC == 0)
	  {
	  	if( CanPMState.ACCOffTimer1S == 0)
  		{
  			CANTask_SendPMReqest(OP_PM_STATE_OFF);
			CANTask_ShutDown();
	       	CanPMState.state = CAN_PM_SLEEP;
  		}
	  }
	  else
	  {
		 CANTask_SendPMReqest(OP_PM_STATE_ON);
	       CanPMState.state = CAN_PM_NORMAL;    
	  }
	  */

		if(IOStatus  == 2)
		{
			CanPMState.state = CAN_PM_WAIT_HALFSLEEP; 
		}
		else
		{
			if(!CanPMState.LocalACC)
			{
				if((CanPMState.ACCOffTimer1S == 0) && (CanPMState.WaitTimer1S == 0))
				{
					CANTask_SendPMReqest(OP_PM_STATE_OFF);
					CANTask_ShutDown();
					CanPMState.state = CAN_PM_SLEEP;
					CanPMState.WaitTimer1S = BUSOFF_TIMEOUT_S;
					TaskCAN_debug(_T("WAIT_SLEEP:-----timeout-----CANTask_ShutDown-----\n"));
				}
			}
			else
			{
				CANTask_SendPMReqest(OP_PM_STATE_ON);
				CanPMState.state = CAN_PM_NORMAL; 
			}
		}
		break;
    case CAN_PM_SLEEP://锟截憋拷ACC之锟斤拷,锟斤拷锟斤拷锟斤拷时锟斤拷锟阶刺�....
		/*
	 if(CanPMState.LocalACC == 1)
	  {
	  	CANTask_StartWork();
		CANTask_SendPMReqest(OP_PM_STATE_ON);
	       CanPMState.state = CAN_PM_NORMAL;    
	  }
	 else
	 {
		if(CanPMState.Timer10ms == 0)
            {
                CanPMState.Timer10ms = 20;
                if(CanPMState.SysWorkState == 1)
                {
                    CANTask_SendPMReqest(OP_PM_STATE_OFF);
                }
            }
	 }*/

		if(IOStatus==2)
		{
			CANTask_StartWork();//锟斤拷CAN锟斤拷锟斤拷...
			CANTask_SendPMReqest(OP_PM_STATE_ON);
			CanPMState.state = CAN_PM_HALFSLEEP;
			PanelLed_SwitchDeal(ON);//锟斤拷POWER锟斤拷锟斤拷锟斤拷
			TaskCAN_debug(_T("---In Sleep State:ILL ON Wake Up DVD!!!!\n\n"));
		}
		else
		{
			if(CanPMState.LocalACC == 1)
			{
				CANTask_StartWork();
				CANTask_SendPMReqest(OP_PM_STATE_ON);
				CanPMState.state = CAN_PM_NORMAL;    
			}
			else
			{
				//锟斤拷锟�1041锟斤拷INH锟斤拷锟斤拷
				if((IO_Get(IO_IDX_ACC_WAKE,PIN_INPUT,TRUE) == 1) && (CanPMState.WaitTimer1S == 0))
				{
					HMIStatusFlag.g_tCanbusWakeUpFlag = 1;
					CANTask_StartWork();
					//can锟斤拷锟斤拷锟秸凤拷 disable
					#ifdef UDS_ENABLE_MACRO
					UdsAppInfo.subControlType = COMM_DSRX_DSTX;
					UdsAppInfo.CommunicationType = COMM_TYPE_NCM_NWMCM;
					Uds_BusMsgConfig();
					#endif
					CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
					CanPMState.state = CAN_PM_WAIT_SLEEP;
					CanPMState.WaitTimer1S = BUSOFF_TIMEOUT_S;
					TaskCAN_debug(_T("SLEEP:--------INH = 1,CANTask_StartWork-----\n"));
				}
				if(CanPMState.Timer10ms == 0)
				{
					CanPMState.Timer10ms = 20;
					if(CanPMState.SysWorkState == 1)
					{
						CANTask_SendPMReqest(OP_PM_STATE_OFF);
					}
				}
				
			}
		}
	break;
	case CAN_PM_HALFSLEEP://小锟狡伙拷锟斤拷锟斤拷锟斤拷锟侥等达拷状态....
		if(CanPMState.LocalACC == 1)
		{
			CANTask_StartWork();
			if(l_tPwrCB.eMode != OP_PM_STATE_ON)
				CANTask_SendPMReqest(OP_PM_STATE_ON);

			PM_TftPowerSet(1,0);
			CanPMState.state = CAN_PM_NORMAL;
		}

		//if(IO_Get(IO_IDX_ILL_DET,PIN_INPUT,FALSE) == 0)
		if(!SystemStatus.ILL)
		{
			if(l_tPwrCB.eMode != PM_MODE_WAIT_SLEEP)
				CANTask_SendPMReqest(OP_PM_STATE_WAIT_SLEEP);
			CanPMState.state = CAN_PM_WAIT_SLEEP;
			CanPMState.ACCOffTimer1S = ACCOFF_TIMEOUT_S;
		}
		break;
    case CAN_PM_WAIT_BUS:
		if(IOStatus == 2)
		{

		}
		else
		{
			if(CanPMState.LocalACC == 1)
			{
				if(sCANModule.SysState != CAN_SYS_ON)
				{
					CANTask_StartWork();
				}
				CANTask_SendPMReqest(OP_PM_STATE_ON);
				CanPMState.state = CAN_PM_NORMAL;
			}
			else
			{
				CANTask_ShutDown();
				CANTask_SendPMReqest(OP_PM_STATE_OFF);
				CanPMState.state = CAN_PM_SLEEP;
			}
		}

		/*
        if(CanPMState.LocalACC == 1)
        {
            if(sCANModule.SysState != CAN_SYS_ON)
            {
                CANTask_StartWork();
            }
			CANTask_SendPMReqest(OP_PM_STATE_ON);
	       CanPMState.state = CAN_PM_NORMAL;
        }
        else
        {
            CANTask_ShutDown();
            CANTask_SendPMReqest(OP_PM_STATE_OFF);
	     CanPMState.state = CAN_PM_SLEEP;
        }
        */
        break;
    case CAN_PM_UNNORMAL:
        if(CanPMState.BusEnableFlag && CanPMState.LocalACC)
        {
            if(sCANModule.SysState != CAN_SYS_ON)
            {
                CANTask_StartWork();
            }
        }
        else
        {
            if(sCANModule.SysState == CAN_SYS_ON)
            {
                CANTask_ShutDown();
            }
        }
        break;
    default:
        break;
    }
#endif	//CAN_PM_ROUTINE_EN

#ifdef _CAN_PM_DBG
    if(CanPMState.state != bakStatus)
    {
        bakStatus = CanPMState.state;
        TaskCAN_debug(_T("CAN mode: %d\n", bakStatus));
    }
#endif
}

void CANTask_PMMsgHandler(tMSG_BUF* Msg)
{
    TaskCAN_debug(_T("CAN Rcv PM iSid: %d", (uint8_t )Msg->iSid));
    CanPMState.SysPmState =(uint8_t) Msg->iSid;

	/*
	//锟斤拷锟斤拷纬锟斤拷锟斤拷息,锟芥储锟斤拷no_init锟斤拷锟斤拷锟捷匡拷锟斤拷,锟斤拷写锟诫到EEPROM锟斤拷...
	//snake20161017 锟较碉拷之前,锟斤拷锟斤拷EEPROM锟斤拷写锟斤拷...
	//只锟斤拷锟节斤拷锟斤拷WAIT_SLEEP(锟斤拷锟斤拷锟接猴拷锟斤拷锟�)锟斤拷时锟斤拷,锟斤拷写EEPROM..锟斤拷止,锟届常锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷写锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷芯片锟较电导锟斤拷,写锟斤拷锟斤拷...
	if(Msg->iSid == OP_PM_STATE_WAIT_SLEEP)
	{
		uint8_t EepStoreStep=WR_EEP_NO_REQ;
		if((BusEepManager.OpState != CAN_EEP_ERR) &&
			(BusEepManager.OpState != CAN_EEP_IDLE))
			TaskCAN_debug(_T("CANbus Data write fail!!!!!\n"));
		else
		{
			EepStoreStep=WR_EEP_REQ;

			if(EepStoreStep==WR_EEP_REQ)
			{
				EEP_CreateBlockChkSum(&l_tEepBusCB);
				BusEepManager.OpState = CAN_EEP_WRITE_REQ;
				TaskCAN_debug(_T("CANbus Data write request sucessfull!!!!!\n"));
			}
		}
	}
	*/
	
    switch(Msg->iSid)
    {
    case OP_PM_STATE_ON:
        TaskCAN_debug(_T("--ON\n"));
        CanPMState.SysWorkState = 1;
        if(!OS_TaskIsActive(TASK_ID_CANBUS))
        {
            OS_TaskStart(TASK_ID_CANBUS);
			
        }
		#ifdef UDS_ENABLE_MACRO
		Uds_DTCSwitchInit();
		Uds_CommControlInit();
		TaskCAN_debug(_T("DTCSwitch and CommControl Reinit.......\n"));
		#endif
		
#ifdef CAN_INNER_ENABLE
        CANbus_EnableCANTransceiver(CAN_ID_INNER, CAN_TRANSCEIVER_MODE_NORMAL);
        CANbus_InnerWriteSysStatus(CAN_INNER_SYS_NORMAL);
#endif
        break;
    case OP_PM_STATE_STANDBY:
        TaskCAN_debug(_T("--STANDBY\n"));
        CanPMState.SysWorkState = 1;
        if(!OS_TaskIsActive(TASK_ID_CANBUS))
        {
            OS_TaskStart(TASK_ID_CANBUS);
        }
#ifdef CAN_INNER_ENABLE
        CANbus_InnerWriteSysStatus(CAN_INNER_SYS_STANDBY);
        CANbus_InnerWriteSourceType(0);
#endif
        break;
    case OP_PM_STATE_WAIT_SLEEP:
        CanPMState.SysWorkState = 0;
        TaskCAN_debug(_T("--WAIT SLEEP\n"));
        break;
    case OP_PM_STATE_SLEEP:
        CanPMState.SysWorkState = 0;
#ifdef CAN_INNER_ENABLE
        CANbus_InnerWriteSysStatus(CAN_INNER_SYS_SLEEP);
        CANbus_InnerWriteSourceType(0);
#endif
        TaskCAN_debug(_T("--SLEEP\n"));
        break;
    case OP_PM_STATE_OFF:
        CanPMState.SysWorkState = 0;
        SystemStatus.SpiReady = 0;
        sCANModule.DataSyncStatus = CAN_MSG_SYNC_NO;
        if(sCANModule.SysState == CAN_SYS_ON)
        {
            CANTask_ShutDown();
        }
        TaskCAN_debug(_T("--OFF\n"));
        break;
    case OP_PM_STATE_LVI:
        CanPMState.SysWorkState = 3;
        TaskCAN_debug(_T("--LVI\n"));
        break;
    case OP_PM_STATE_ERR:
        CanPMState.SysWorkState = 3;
        TaskCAN_debug(_T("--ERR\n"));
        break;
    case OP_PM_STATE_BATERR:		/*PM auto enter HV/LV threadhold */
        CanPMState.SysWorkState = 3;
        TaskCAN_debug(_T("--BAT ERR\n"));
        break;
    case OP_PM_STATE_RESET:
        CanPMState.SysWorkState = 3;
        TaskCAN_debug(_T("--RESET\n"));
        break;
    case OP_PM_STATE_INVALID:
        CanPMState.SysWorkState = 3;
        TaskCAN_debug(_T("--INVALID\n"));
        break;
    default:
        CanPMState.SysWorkState = 3;
        TaskCAN_debug(_T("--default\n"));
        break;
    }
}

void CANTask_SRCMsgHandler(tMSG_BUF *pMsg)
{
#ifdef CAN_INNER_ENABLE
    if(pMsg->iSid == OP_SRC_SW_START)
    {
        uint8_t temp = 0xff;
        switch(pMsg->uData.a_cData[1])
        {
        case SOURCE_TUNER:
            temp = 0x03;		//radio
            break;
        case SOURCE_DVD:
        case SOURCE_CDBOX:
        case SOURCE_DISC_VIDEO :
        case SOURCE_DISC_IMAGE :
            temp = 0x02;		//DVD
            break;
        case SOURCE_TV:
        case SOURCE_DTV:
            temp = 0x05;		//DTV
            break;
        case SOURCE_SD_AUDIO:
        case SOURCE_SD_VIDEO:
        case SOURCE_SD_IMAGE:
        case SOURCE_SD:
            temp = 0x06;		//SD
            break;
        case SOURCE_USB_AUDIO:
        case SOURCE_USB_VIDEO:
        case SOURCE_USB_IMAGE:
        case SOURCE_USB:
            temp = 0x04;		//USB
            break;
        case SOURCE_BT_MUSIC:
            temp = 0x07;		//BT
            break;
        case SOURCE_AVOFF:
        case SOURCE_SYS_STANDBY:
            temp = 0x00;		//NULL
            break;
        case SOURCE_DISC_AUDIO:
            temp = 0x01;		//CD
            break;
        case SOURCE_IPOD:
        case SOURCE_IPOD_AUDIO:
        case SOURCE_IPOD_VIDEO:
            temp= 0x09;		//IPOD
            break;
        case SOURCE_NAVI:
            //temp = 0x0A:		//NAVI
            break;
        default:
            temp = 0x0e;		//reserved
            break;
        }
        if(temp <=0x0f)
        {
            CANbus_InnerWriteSourceType(temp);
        }
    }
#endif
}

void CANTask_VehicleMsgHandler(uint8_t *pMsg)
{
    uint8_t  index = 0xff;

    switch(pMsg[0])
    {
    case OP_CAN_RX_VEHICLE_BACKCAR:		//CAM MODE
        index = 0;
        break;
    case OP_CAN_RX_VEHICLE_ATMOSPHER:
        index = 1;
        break;
    case OP_CAN_RX_VEHICLE_LAMP:
        index = 2;
        break;
    case OP_CAN_RX_VEHICLE_WINDOW_ALL:
    case OP_CAN_RX_VEHICLE_WINDOW_FL:
    case OP_CAN_RX_VEHICLE_WINDOW_FR:
    case OP_CAN_RX_VEHICLE_WINDOW_RL:
    case OP_CAN_RX_VEHICLE_WINDOW_RR:
    case OP_CAN_RX_VEHICLE_WINDOW_HEAD:
        index = 3;
        break;
    case OP_CAN_RX_VEHICLE_DOOR_ALL:
    case OP_CAN_RX_VEHICLE_DOOR_FL:
    case OP_CAN_RX_VEHICLE_DOOR_FR:
    case OP_CAN_RX_VEHICLE_DOOR_RL:
    case OP_CAN_RX_VEHICLE_DOOR_RR:
    case OP_CAN_RX_VEHICLE_DOOR_BAG:
    case OP_CAN_RX_VEHICLE_DOOR_ENGINE:
        index = 4;
        break;
    case OP_CAN_RX_VEHICLE_WIPER_FRONT:
    case OP_CAN_RX_VEHICLE_WIPER_REAR:
        index = 5;
        break;
    case OP_CAN_RX_VEHICLE_RMIR_LEFT:
    case OP_CAN_RX_VEHICLE_RMIR_RIGHT:
        index = 6;
        break;
    case OP_CAN_RX_VEHICLE_CRUISE:
        index = 7;
        break;
    case OP_CAN_RX_VEHICLE_MAINTAIN:
        index = 8;
        break;
    case OP_CAN_RX_VEHICLE_AVM:
    case OP_CAN_RX_BLIND_INOUT:
        index = 9;
        break;
    case OP_CAN_RX_VEHICLE_SEARCH:
        index = 0x0a;
        break;
    case OP_CAN_RX_TBOX_REQTUID:
    case OP_CAN_RX_TBOX_REGACK:
        index = 0x0b;
        break;

    case OP_CAN_RX_VEHICLE_AvmSlip:
        index = 0x0e;
    	break;


        /*-----------------------------------------------*/
    case OP_CAN_RX_ACR_FAC_SWITCH:
    case OP_CAN_RX_FAC_SWITCH:
    case OP_CAN_RX_RAC_SWITCH:
        index = 0X10;
        break;
    case OP_CAN_RX_ACR_FLAC_TEMP_ADJ:
    case OP_CAN_RX_FLAC_TEMP_ADJ:
    case OP_CAN_RX_FRAC_TEMP_ADJ:
    case OP_CAN_RX_RAC_TEMP_ADJ:
        index = 0X11;
        break;
    case OP_CAN_RX_ACR_FAC_WIND_MODE:
    case OP_CAN_RX_FAC_WIND_MODE:
    case OP_CAN_RX_RAC_WIND_MODE:
        index = 0X12;
        break;
    case OP_CAN_RX_ACR_FAC_WIND_LEVEL_ADJ:
    case OP_CAN_RX_FAC_WIND_LEVEL_ADJ:
    case OP_CAN_RX_RAC_WIND_LEVEL_ADJ:
        index = 0X13;
        break;
    case OP_CAN_RX_AC_REF_SWTICH:
        index = 0X14;
        break;
    case OP_CAN_RX_ACF_AUTO_SET:
    case OP_CAN_RX_ACR_AUTO_SET:
        index = 0X15;
        break;
    case OP_CAN_RX_ACR_AC_CIRCLE_MODE:
    case OP_CAN_RX_AC_CIRCLE_MODE:
        index = 0X16;
        break;
    case OP_CAN_RX_AC_WIND_REGION:
        index = 0X17;
        break;
    case OP_CAN_RX_ACR_AC_FRONT_DEFROST:
    case OP_CAN_RX_AC_FRONT_DEFROST:
    case OP_CAN_RX_AC_REAR_DEFROST:
        index = 0X18;
        break;
    case OP_CAN_RX_AC_GLASS_HEAT:
        index = 0X19;
        break;
    case OP_CAN_RX_AC_ECO_MODE:
        index = 0X1a;
        break;
    case OP_CAN_RX_AC_SENSOR:
        index = 0X1b;
        break;
    case OP_CAN_RX_AC_FILTER_SWITCH:
        index = 0X1c;
        break;
    case OP_CAN_RX_FLAC_SEATHEAT:
    case OP_CAN_RX_FRAC_SEATHEAT:
    case OP_CAN_RX_RAC_SEATHEAT:
        index = 0X1d;
        break;
    case OP_CAN_RX_AC_WIND_AUTOCTL:
	 index = 0x20;
	break;

    case OP_CAN_RX_VEHICLE_SetAmp:
        index = 0x21;
        break;
	case OP_CAN_RX_VEHICLE_Recover:
		index = 0x22;
		break;
	case OP_CAN_RX_VEHICLE_Seat:
		index = 0x23;
		break;
	
	case OP_CAN_RX_ACR_RESET:
		index = 0x24;
		break;
	case OP_CAN_RX_LIGHT_OFF_DELAY:
		index = 0x26;
		break;
	case OP_CAN_RX_TURN_BLINK_TIMES:
		index = 0x27;
		break;
	case OP_CAN_RX_KEY_DOOR_UNLOCK_MODE:
		index = 0x28;
		break;
	case OP_CAN_RX_DRIVE_DOOR_LOCK:
		index = 0x29;
		break;
	case OP_CAN_RX_PARK_DOOR_UNLOCK:
		index = 0x2a;
		break;
	case OP_CAN_RX_ACR_OPEN_AVM:
		 index=0x2b;
		break;		
/**************锟斤拷锟斤拷锟斤拷全**************/
	case OP_CAN_RX_ACC_OBJ_ENABLE:
		index = 0x2c;
		break;
	case OP_CAN_RX_FCW_ENABLE:
		index = 0x2d;
		break;
	case OP_CAN_RX_AUTO_BRAKE_ENABLE:
		index = 0x2e;
		break;
	case OP_CAN_RX_BSD_LCA_ENABLE:
		index = 0x2f;
		break;
	case OP_CAN_RX_CTA_ENABLE:		// BOLTE
		index = 0x31;
		break;
	case OP_CAN_RX_RCW_ENABLE:
		index = 0x32;
		break;
	case OP_CAN_RX_LDW_SENSITIVITY:
		index = 0x33;
		break;
	case OP_CAN_RX_SLA_SWITCH:			
		index = 0x34;
		break;
	case OP_CAN_RX_HMA_ENABLE:
		index = 0x35;
		break;
	case OP_CAN_RX_DRIVE_LIGHT_ENABLE:
		index = 0x36;
		break;
		
    }

    if(index >= CANUser_GetFuncTblSize())
    {
        return;
    }
    if(pCANUserFuncTbl[index] != 0)
    {
        pCANUserFuncTbl[index](&pMsg[0], 2);
    }
}

void CANTask_NAVIMsgHandler(uint8_t* pMsg)
{

    if(pCANUserFuncTbl[0x0f] != 0)
    {
        pCANUserFuncTbl[0x0f](&pMsg[0], 4);
    }
}

void CANTask_DTVMsgHandler(uint8_t* pMsg)
{
#ifdef CAN_INNER_ENABLE
    uint8_t cmd=  0xff;
    //buffer[1] = len;
    //buffer[2] = Gid;
    //buffer[3] = Sid;
    //buffer[4] = DTV cmd
    if(pMsg[0] == 0x00)		/*search */
    {
        cmd = 0x05;
    }
    else if(pMsg[0] == 0x01)	/*pre station*/
    {
        cmd = 0x04;
    }
    else if(pMsg[0] == 0x02)	/*next station*/
    {
        cmd = 0x03;
    }
    else if(pMsg[0] == 0x03)	/*request CA number */
    {
        cmd = 0x01;
    }
    else if(pMsg[0] == 0x04)	/*open broadcast */
    {
        cmd = 0x02;
    }
    else if(pMsg[0] <(0x04+20))	/*station index */
    {
        cmd = pMsg[0]-0x05+0x0a;
    }
    else if(pMsg[0] == 0xfe)		/* emergency broadcast test. */
    {
        cmd = 0x07;
    }
    else if(pMsg[0] == 0xff)		/*version */
    {
        CANTask_SendApiData(OMS_CAN_TX_DTV, OP_CAN_TX_DTV_VER, 1);
    }
    if(cmd <=0x1f)
    {
        CANbus_InnerWriteDtvCmd(cmd);
    }
#endif
}

void CANTask_EOLMsgHandler(uint8_t *pMsg)
{
/*
  *	 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷堑幕锟斤拷锟斤拷锟斤拷锟紸PU锟斤拷锟斤拷锟斤拷锟斤拷锟矫ｏ拷锟斤拷锟斤拷式
  *	锟斤拷一锟斤拷锟侥ｏ拷锟斤拷要锟斤拷锟芥到系统锟斤拷去锟斤拷
  */
  	#if (PROJECT_CODE == CHANGAN_S401)
		UdsFbl_StoreDIDToSystem(DID_ID_F1F8, pMsg, DID_F1F8_LENGTH);
	#elif (PROJECT_CODE == CHANGAN_R103_H15T)
		UdsFbl_StoreDIDToSystem(DID_ID_F1FA, pMsg, DID_F1FA_LENGTH);
	#endif
/*
  *	锟斤拷锟斤拷取锟斤拷锟斤拷锟斤拷要锟斤拷锟铰碉拷UDS FBL锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷萁峁癸拷校锟�
  *   锟皆憋拷锟斤拷锟斤拷锟斤拷锟街达拷卸锟饺★拷锟斤拷锟斤拷锟�
  */
       UdsFbl_LoadSysData(&l_tBusData);
}

void CANTask_HUSysMsgHandler(uint8_t* pMsg)
{
    switch(pMsg[0])
    {
    case SID_CAN_RX_SYS_STATE:
        break;
    case SID_CAN_RX_SYS_CLK:
        break;
    case SID_CAN_RX_AVM_SLIP:
        if(pCANUserFuncTbl[0x0e] != 0)
        {
            pCANUserFuncTbl[0x0e](&pMsg[1], 4);
        }
        break;
    case SID_CAN_RX_DATA_REQ:
        CANTask_SendApiData(pMsg[1],pMsg[2], 1);
        break;
	case OP_CAN_RX_VEHICLE_TBOX_VIN:
	{
       	if(NULL!=pCANUserFuncTbl[0x1e])
       	{
		pCANUserFuncTbl[0x1e](&pMsg[1], 17);
       	}
	}
	break;
	case OP_CAN_RX_VEHICLE_TBOX_PHONE:
	{
       	if(NULL!=pCANUserFuncTbl[0x1f])
       	{
		pCANUserFuncTbl[0x1f](&pMsg[1], 11);
       	}			
	}
	break;        
    default:
        break;
    }
}

static void CANTask_MediaCanHandler(void)
{
	ByteBufferMangerStruct * pBuffer = pCAN_GetMediaRxCANByteBuffer();

	if(pBuffer->MsgNum >0)
	{
		uint8_t Temp[MSG_BYTE_SIZE_MAX+10];
		if(ByteDataBufferReadMsg(&Temp[1], &Temp[0], pBuffer))
		{
			hmi_printf(_T("001------GID = %d,sid = %d,data:%d  %d\n",Temp[2],Temp[3],Temp[4],Temp[5]));
			//Temp[1] = len;
			//Temp[2] = Gid;
			//Temp[3] = Sid;
			//Temp[4] = setting command
			//Temp[5] = setting parameter.
			switch(Temp[2])
			{
				case LMS_CAN_RX_VEHICLE:
					CANTask_VehicleMsgHandler(&Temp[3]);
					break;
				case LMS_CAN_RX_NAVI:
					//CANTask_NAVIMsgHandler(&Temp[3]);
					break;
				case LMS_CAN_RX_DTV:
					CANTask_DTVMsgHandler(&Temp[3]);
					break;
				case LMS_CAN_RX_MEDIA:
					//CANTask_HUMediaMsgHandler(&Temp[3]);
					break;
				case LMS_CAN_RX_SYS:
					CANTask_HUSysMsgHandler(&Temp[3]);
					break;
				default:
					break;
			}
		}
		
	}
}


void CANTask_RxBusDataDeal(uint8_t cSid,uint8_t* p_cRxdata,uint8_t cLen)
{
	//TaskCAN_debug(_T("CANTask_RxBusDataDeal:cSid = %x,p_cRxdata[0] = %x\n",cSid,p_cRxdata[0]));
   if( (uint8_t)OP_LOAD_PRJS401_DATA == cSid)
	{
		switch(p_cRxdata[0])
		{
			case USERID_MCU_RX_DVR_SETREQ:
				CANUser_SetDvrInfo(OP_LOAD_PRJS401_DATA,p_cRxdata);
				break;
			default:
				break;
		}

	}
   else if((uint8_t)OP_LOAD_PRJR103H_INFO == cSid)
   	{
   		switch(p_cRxdata[0])
   		{
			case USERID_MCU_RX_DVR_SETREQ:
				CANUser_SetDvrInfo(OP_LOAD_PRJR103H_INFO,p_cRxdata);
				break;
			default:
				break;
   		}
   	}
}




/****************************************************************************
 * @function	CAN_MsgHandler
 * @brief  	deal with the message from other module
 * @param  	Msg: message point
 * @retval 	null
 * @attention:  null
****************************************************************************/
static void CANTask_MsgHandler(tMSG_BUF* Msg)
{
    uint8_t Temp[3];
    switch(Msg->Id)
    {
    case MS_PM_STATE:
        CANTask_PMMsgHandler(Msg);
        break;
    case MS_PM_AWAKE:			/*Awake from LVI mode */
        if(Msg->iSid == OP_PM_STATE_LVI)
        {
        }
        break;
    case MS_SYS_APU_INFO:
        SystemStatus.APUStatus = (Msg->iSid) &0xff;
        switch(SystemStatus.APUStatus)
        {
        case OP_DEV_STATE_NOCONNECT:
        case OP_DEV_STATE_OFF:
        case OP_DEV_STATE_SLEEP:
        case OP_DEV_STATE_UPDATA:
        case OP_DEV_STATE_ERR:
        case OP_DEV_STATE_RESET:
            SystemStatus.SpiReady = 0;
            break;
        case OP_DEV_STATE_CONNECTED:
            if(SystemStatus.SpiReady == 1)
            {
                sCANModule.DataSyncStatus = CAN_MSG_SYNC_NO;
            }
        case OP_DEV_STATE_NORMAL:
            SystemStatus.SpiReady = 1;
            break;
        default:
            break;
        }
        TaskCAN_debug(_T("sysAPUStatus:%x\n", SystemStatus.APUStatus));
        break;
#ifdef CAN_INNER_ENABLE
    case MS_AUDIO_UPLOAD_INFO:
        if(Msg->iSid == OP_AUDUP_VOL)
        {
            CANbus_InnerWriteVolume(Msg->uData.a_cData[0]);
        }
        else if(Msg->iSid == OP_AUDUP_MUTE)	/*MUTE STATE */
        {
            if(g_tMcuDevState.uIOState.bits.MuteOn)
            {
                CANbus_InnerWriteVolume(0x3E);
            }
            else
            {
                CANbus_InnerWriteVolume(sAudioKeep.SysVol);
            }
        }
        break;

    case MS_UI_UPLOAD_INFO:
        if(Msg->iSid == OP_INFO_RADIOINFO)
        {
            CANbus_InnerWriteRadioInfo();
        }
        break;

    case MS_SRC_SYS_CMD:
        CANTask_SRCMsgHandler(Msg);
        break;

#endif

    case MS_SYS_IO_INFO:
        if(Msg->iSid == IO_IDX_ACC_WAKE)
        {
            SystemStatus.ACC = (uint8_t)((uint32_t)(Msg->uData.p_cData));
	     	TaskCAN_debug(_T("CAN Rcv ACC state:%d\n", SystemStatus.ACC));
        }
		if(Msg->iSid == IO_IDX_ILL_DET)
		{
			SystemStatus.ILL = (uint8_t)((uint32_t)(Msg->uData.p_cData));
			TaskCAN_debug(_T("CAN Rcv ILL state:%d\n", SystemStatus.ILL));
		}
        break;

    case MS_OTHER_VOLTAGE:
        CANTask_OtherMsgHandler(Msg);
        break;

    case MS_OTHER_AVM://snake20160808  盲锟斤拷
    {
		CarAVMDataStruct *pData = pCAN_GetAVMData();

		/*
		if(!l_tMediaCB.uDevFlag.field.bUnLocked)//snake20160927 delete 同锟斤拷之前也锟斤拷锟皆斤拷锟斤拷盲锟斤拷...
		{
			return;
		}*/
		if(!HMIStatusFlag.g_tUpdataReverseParameter)//锟节碉拷锟斤拷锟斤拷时锟斤拷,锟斤拷锟斤拷应盲锟斤拷锟斤拷锟斤拷...
		if(1==CanPMState.SysWorkState)	
		{
			fTw8836.ADI7186OVERLAYDisable = 0;

			if( Msg->iSid == OP_AVM_PRESS )
			{
				//if(pData->BlindReq)
				if(g_tMcuDevState.uDetect.bits.Blind_Flag)
				{
					pData->BlindReq=0;
				}
				else if(g_tMcuDevState.uDetect.bits.Blind_Flag == 0)
				{
					pData->BlindReq=1;
					_SendMsgToSRC(MS_INPUT_UI,UICC_STOP_SEEK,NULL);//snake20161007 锟斤拷锟斤拷盲锟斤拷锟斤拷时锟斤拷停止锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
				}				
			}
			else if( Msg->iSid == OP_AVM_RELEASE) 
			{
				TaskCAN_debug(_T("----BlindReq Processing----,BlindReq=%x\n",pData->BlindReq));
				if(pData->BlindReq != pData->BlindReqBk)
				{
					pData->BlindReqBk = pData->BlindReq;
					HMIStatusFlag.g_tUpdataBlindParameter = 1;
					_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_CAMERA,pData->BlindReq);
					TaskCAN_debug(_T("Send Blind State to src!!!!!\n"));
				}
			}
		}
		else
		{
	        pData->BlindReq = 0;
			pData->BlindReqBk = 0;
			_SendMsgToSRC(MS_SRC_SET_TOP_TYPE,SRC_TYPE_CAMERA,pData->BlindReq);
		}

    }
    break;

    default:
        break;
    }
}

void TestSendDataToAPU(void)
{
    static uint16_t speed = 0;
    CarSpeedDataStruct	   *pSpeed =  pCAN_GetVehicleSpeed();

    speed++;
    pSpeed->SpeedHbyte = (speed>>8)&0xff;
    pSpeed->SpeedLbyte = speed&0xff;

    CANTask_SendApiData(OMS_CAN_TX_CAR,	OP_CAN_TX_CAR_MAINTAIN, 1);
    TaskCAN_debug(_T("Test Send Data To APU\n"));
}

void CANTask_DataSyncEndHook(void)
{
#ifdef CAN_API_DTV_EN
    if(pCAN_GetDTVStateData()->Exist)
    {
        if(!g_tMcuDevState.uConnetState.bits.DTV_Connected)
        {
            g_tMcuDevState.uConnetState.bits.DTV_Connected = 1;
             _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
        }
    }
    else if(!pCAN_GetDTVStateData()->Exist)
    {
        if(g_tMcuDevState.uConnetState.bits.DTV_Connected)
        {
            g_tMcuDevState.uConnetState.bits.DTV_Connected = 0;
            _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
        }
    }
#endif
}
void CANTask_DataSyncOn2(void)
{
#ifdef CAN_API_DTV_EN
    if(pCAN_GetDTVStateData()->Exist)
    {
        //request CA number
        CANbus_InnerWriteDtvCmd(0x01);
    }
#endif
}


/****************************************************************************
 * @function	CANTask_DataSync
 * @brief  	when APU start OK, send CAN bus data to APU
 * @param  	null
 * @retval 	null
 * @attention   null
****************************************************************************/
void CANTask_DataSync(void)
{
    static uint8_t timer = 0;
    static uint8_t HaveSyncNum = 0;

    switch(sCANModule.DataSyncStatus)
    {
    case CAN_MSG_SYNC_NO:		/* have not sync */
	  if((SystemStatus.SpiReady == 1)&&(BusEepManager.OpState==CAN_EEP_IDLE))
        {
            sCANModule.DataSyncStatus = CAN_MSG_SYNC_ON1;
            timer = TIMER_200MS;
            HaveSyncNum = 0;
            TaskCAN_debug(_T("CAN Data Sync Start!\n"));
        }
        break;
    case CAN_MSG_SYNC_ON1:
        if(timer == 0)
        {
            timer = TIMER_200MS;//TIMER_100MS;
            if(HaveSyncNum < CANUser_GetUsedMsgNum())
            {

                CANTask_SendApiData(CANUser_UsedMsgData[HaveSyncNum].OMS,
                                    CANUser_UsedMsgData[HaveSyncNum].op, 1);
                HaveSyncNum++;

                TaskCAN_debug(_T("CAN Data Sync num:%d\n", HaveSyncNum));
            }
            else
            {
                sCANModule.DataSyncStatus = CAN_MSG_SYNC_ON2;
            }
        }
        else
        {
            timer--;
        }
        break;
    case CAN_MSG_SYNC_ON2:
        CANTask_DataSyncOn2();
        sCANModule.DataSyncStatus = CAN_MSG_SYNC_END;
        TaskCAN_debug(_T("CAN Data Sync End!\n"));
        break;
    case CAN_MSG_SYNC_END:
        if(SystemStatus.SpiReady == 0)
        {
            sCANModule.DataSyncStatus = CAN_MSG_SYNC_NO;
        }
        else
        {
            CANTask_DataSyncEndHook();
        }
        break;
    default:
        break;
    }
}

void CANTask_SetAmpPower(void)
{
	uint8_t msg[5];
	
	if(CANTask_GetSysACCState() ==1)//acc  锟斤拷
	{
		CanPMState.SetAmpOffCnt=0;
		CanPMState.SetAmpOnCnt++;

		if(CanPMState.SetAmpOnCnt>200)
		CanPMState.SetAmpOnCnt=12;

		if((CanPMState.SetAmpOnCnt%2)&&(CanPMState.SetAmpOnCnt<10))
		{
			//锟斤拷锟矫癸拷锟脚斤拷锟斤拷锟斤拷
			CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_ON);
		}

		 if((CanPMState.SetAmpOnCnt%2)&&(CanPMState.SetAmpOnCnt>10))
		{
	                //锟斤拷锟矫癸拷锟脚解静锟斤拷
	                if(l_tMediaCB.uDevFlag.field.bDevConnect==0)
	                {
				CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_ON);
	                }
	                else
	                {
				if(sAudio.KeyMuteState)
					CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_ON);
				else
				{
					if(sAudio.StarUp &&  l_tMediaCB.uDevFlag.field.bUnLocked)
						CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_OFF);
					else
						CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_ON);
				}
	                }
		}
		else
		{
			CANUser_SetAmpCmd(AMP_TYPE_POW, AMP_POW_ON);
		}
	}
	
	if(CANTask_GetSysACCState() ==0)//acc 锟斤拷
	{
		CanPMState.SetAmpOnCnt=0;
		CanPMState.SetAmpOffCnt++;
		
		if(CanPMState.SetAmpOffCnt%2)
		{
	                //锟斤拷锟矫癸拷锟脚斤拷锟斤拷锟斤拷
			CANUser_SetAmpCmd(AMP_TYPE_MUTE, AMP_MUTE_ON);
		}
		else
		{
			CANUser_SetAmpCmd(AMP_TYPE_POW, AMP_POW_OFF);
		}
	}
}

void CANTask_dummy(void)
{

}
void CANTask_TimerHandler(void)
{

}
void CANbus_Task(EVENT iEvt,eTASK_STATE eState)
{
    if(iEvt & EVT_COLD_INIT)
    {
        //	CANTask_Init();
        //	CANTask_SendModuleState();
        TaskCAN_debug(_T("CAN task Cold Init!\n"));
    }
    if(iEvt & EVT_WARM_INIT)
    {
        //	CANTask_WarmInit();
        //	CANTask_SendModuleState();
        TaskCAN_debug(_T("CAN task warm Init!\n"));
    }

    if(iEvt & EVT_MSG_READY)
    {
        tMSG_BUF tMsg;
        if(QUE_ERR_NONE == OS_GetMsgDir(&g_tCanTaskCB,&tMsg))
        {
            CANTask_MsgHandler(&tMsg);

        }
        else
        {
            TaskCAN_debug(_T("QUE_ERR!\n"));
        }
    }

    if(eState == TASK_STATE_READY)
    {
        if(!OS_TaskIsActive(TASK_ID_CANBUS))
        {
            OS_TaskStart(TASK_ID_CANBUS);
        }
    }
    else if(eState == TASK_STATE_RUNNING)
    {
    	
        if(iEvt & EVT_TASK_TICK_READY)
        {
        	CANTask_TimerHandler();
            CANUser_TaskTickHook(2);
            IO_Scan(IO_IDX_LOCAL_ACC, PIN_INPUT);
            CANTask_Manager();

            CanIf_MainFunction();
            ComUser_MainFunction();
            CanTp_MainFunction();
            Dcm_MainFunction();

#ifdef NM_ENABLE_MACRO
            NM_AppMsgHandler(CAN_ID_BODY);
#else
		#ifdef UDS_ENABLE_MACRO //snake20161012 锟截憋拷锟斤拷锟斤拷锟斤拷锟斤拷锟�,也要锟斤拷锟斤拷uds
			Uds_ProtocolStackMain();
		#endif
#endif
            CANTask_PmRoutine();
			
	     sCANModule.Ticks_Count++;
            if(!(sCANModule.Ticks_Count%5))		// 2ms *5 = 10ms
            {
                if(CanPMState.Timer10ms>0)
                {
                    CanPMState.Timer10ms--;
                }
            }
            if(!(sCANModule.Ticks_Count%100))		// 2ms *100 = 200ms
                CANTask_SetAmpPower();

            if(sCANModule.Ticks_Count >=TIMER_1000MS)
            {
                sCANModule.Ticks_Count = 0;
                CanPMState.Timer1S++;

				//snake20170418
				//锟斤拷时锟斤拷锟斤拷,锟斤拷没锟斤拷锟揭碉拷锟斤拷锟斤拷锟斤拷原锟斤拷之前锟斤拷时锟斤拷锟斤拷锟矫�1S锟接凤拷锟斤拷一锟轿凤拷锟斤拷锟斤拷锟斤拷.
				CANUser_SendMsg500();
				CANUser_SendMsg501();
				
                if(CanPMState.ACCOffTimer1S>0)
                {
                    CanPMState.ACCOffTimer1S--;
                }
				if(CanPMState.WaitTimer1S>0)
					CanPMState.WaitTimer1S--;
                //TaskCAN_debug(_T("1S tick!\n"));
            }
		if(CanPmEnterStandbyFlg)
		{
			if(++CanPmRecTimer >= 1250)	// 2ms*1250 = 2.5s 锟脚号讹拷失2.5S锟斤拷锟皆讹拷锟斤拷锟斤拷
			{
				CanPmRecTimer = 0;
				CanPmEnterStandbyFlg = 0;
				CANTask_SendPMReqest(OP_PM_STATE_ON);//exit sleep mode
			}
		}
        }

        if(iEvt & EVT_CORE_TICK_READY)
        {
#ifdef NM_ENABLE_MACRO
            NM_AdpRoutine(CAN_ID_BODY);
	     //TestIO1_Output(1,0);
#endif
        }
	 if(iEvt & EVT_RTC_SECOND)
	 {
		    if(pCANUserFuncTbl[0x0c] != NULL)
		    {
		        pCANUserFuncTbl[0x0c](NULL, 0);
		    }
	 }
    }
    else if(eState == TASK_STATE_STOP)
    {
        if(!OS_TaskIsActive(TASK_ID_CANBUS))
        {
            OS_TaskStart(TASK_ID_CANBUS);
        }
    }
}


static const tTASK_BLOCK CANbus_TCB =
{
    "CANbus",
    _CANBUS_TASK_TICK_,
    _CANBUS_CORE_TICK_,
    CANbus_Task,
    CANTask_Init,
    CANTask_DeInit,
};


tRING_QUE 	CANTaskMsgQue;
tMSG_BUF	CANTaskMsgBuf[D_CANBUS_MSG_QUE_DEEP];
tTASK_CTRL_BLOCK g_tCanTaskCB;


bool CANbus_TaskCreate(void)
{

    CAN0_LocalWakeup(0,1);
    CANTask_PMInit();
	BusEepManager.Cnt = 0; //锟斤拷取锟斤拷锟斤拷锟侥筹拷始锟斤拷....
    l_tBusData.iCheckSum = 0x00;
    if(EEP_DATA_NOERR == EEP_CreateEepDataBlock(&l_tEepBusCB,&lc_tEepBusCB))
    {
        BusEepManager.OpState = CAN_EEP_IDLE;
        CAN_EepRead();
    }
    else
    {
        BusEepManager.OpState = CAN_EEP_UNVALID;
    }

    return OS_TaskCreate(TASK_ID_CANBUS,
                         &g_tCanTaskCB,
                         &CANbus_TCB,
                         &CANTaskMsgQue,
                         CANTaskMsgBuf,
                         D_CANBUS_MSG_QUE_DEEP);

}

#else
bool CANbus_TaskCreate(void)
{

}
#endif


