/**********************************************************
 * @file        Video_ADI7186.c
 * @purpose
 * @version    0.01
 * @date      2015.05.29
 * @author    xjh
 * @brief
 ***********************************************************
 *     History:
 *  <write/modify>        <time>        <version >    <desc>
 *  XJH               2015.05.29        v0.01        created
 *  XJH               2015.09.11        v0.02        MODIFY
  **********************************************************/
#define TW8836_CTRL
/* ========================= File include ======================= */
#include "..\..\config\inc.h"

#ifdef D_VIDEO_SWITCH_TW8836
//#include "Tw8836_gamma.c"
#include "Tw8836_SpiFlash.h"
#include "Tw8836_SpiQuad.h"
#include "Tw8836_SpiLoadLUT.h"

EXTERN const   uint8_t     SCREENDATA_LVDS_BT656_CVBS_ALL[] =
{
   // #include    "ADI7186_Arm_Bt656_Lvds_960_1280.h"
   #include    "ADI7186_LVDS_BT656_CVBS_800_480.h"
    0xFF, 0xFF, 0xFF,
};
EXTERN const   uint8_t     SCREENDATA_LVDS_ALL[] =
{
   // #include    "ADI7186_Arm_Bt656_Lvds_960_1280.h"
    0x4C, 0x03, 0x30,
    0xA4, 0xA5, 0x20,
    0xA4, 0xA6, 0x00, 
    0XA4, 0XB0, 0X05,

   	//DVR显示参数...
	0xA4, 0x60, 0x9F,
	0xA4, 0x61, 0x8F,
	0xA4, 0x62, 0xF6,//0xFB  

    0xFF, 0xFF, 0xFF,
};
EXTERN const   uint8_t     SCREENDATA_CVBS1_ALL[] =
{
    //#include    "ADI7186_Cvbs_In_Lvds_960_1280.h"
    0x4C, 0x03, 0x10,
    0xA4, 0xA6, 0x7F,   
    0xA4, 0xA5, 0x21,

	0xA4, 0x60, 0x9F,
	0xA4, 0x61, 0xC8,
	0xA4, 0x62, 0xF9,//0xFB
	
	0xC0, 0xFF, 0x04,//复位DDR 解决视频有的时候抖动的问题...
	
    0xFF, 0xFF, 0xFF,
};
EXTERN const   uint8_t     SCREENDATA_CBVS2_ALL[] =
{
    //#include    "ADI7186_Cvbs_In_Lvds_960_1280.h"
    0x4C, 0x03, 0x20,
    0xA4, 0xA6, 0x7F,   
    0xA4, 0xA5, 0x21,

	0xA4, 0x60, 0x9F,
	0xA4, 0x61, 0xC8,
	0xA4, 0x62, 0xF9,//0xFB

	0xC0, 0xFF, 0x04,
	
    0xFF, 0xFF, 0xFF,
};

EXTERN const   uint8_t     SCREENDATA_DVR_ALL[] =
{
    //#include     "ADI7186_CVBS_BT656_LVDS_DVR_800_480.h"
    0xA4, 0xA5, 0x20,
    0xFF, 0xFF, 0xFF,
};

EXTERN const uint8_t  *ScreenParameter[] =
{
    (const uint8_t*)(&(SCREENDATA_LVDS_ALL[0])),
    (const uint8_t*)(&(SCREENDATA_CVBS1_ALL[0])),
    (const uint8_t*)(&(SCREENDATA_CBVS2_ALL[0])),
    (const uint8_t*)(&(SCREENDATA_DVR_ALL[0])),
};

#if 0
const   uint8_t     Tw8836_Clock[] =
{
    0xFF, 0x00, // Page 00
    0xE7, 0x16/*0x96*/,
    0xE8, 0x00,
    0xE9, 0x9D,
    0xEA, 0xB0,
    0xEB, 0x40,
    0xEC, 0x30,
    0xED, 0x11,
    0xF6, 0x00,
    0xF7, 0x16,
    0xF8, 0x01,
    0xF9, 0x55,
    0xFA, 0x55,
    0xFB, 0x40,
    0xFC, 0x30,
    0xFD, 0x23,

    0xFF, 0x02, // Page 02
    0x0D, 0x90,
    0xFF, 0xFF,
};

const   uint8_t     Tw8836_TriEn[] =
{
    0xFF, 0x00, // Page 00
    0x08, 0xD6,
    0xFF, 0xFF,
};

const   uint8_t     Tw8836_LvdsTx[] =
{
    0xFF, 0x00, // Page 00
    0x08, 0xC6,

    0xFF, 0x06, // Page 06
    0x40, 0x0C,
    0x41, 0x00,
    0x42, 0x01,
    0x43, 0xC0,
    0x44, 0x00,
    0x46, 0x01,

    /*   0xFF, 0x02, // Page 02
       0xE0, 0x04,*/
    0xFF, 0xFF,
};

const uint8_t CvbsTypeTab[] =
{
  /* Ain1 Ain2 Ain3 Ain4 Ain5 Ain6*/
      0x81,0x82,0x83,0x84,0x85,0x86
};
#endif
/* ========================= File Funtion ======================= */

/**********************************************************
 * @function    Tw8836_InitVariable
 * @brief      Initialize Variable
 * @param      None
 * @retval     Result
 **********************************************************/
void Tw8836_InitVariable(void)
{
    video_printf(_T("---Tw8836_InitVariable in---\n"));
    fTw8836.DrvStep = 0;
	//fTw8836.ADI7186InitProgramme = 0;
    //fTw8836.LvdsOnStep = 0;
    fTw8836.DrvSubStep = 0;
    fTw8836.DrvDelay= 0;
    fTw8836.OsdUpdateStep=0;
    fTw8836.ADI7186OSDStep=0;
    fTw8836.Tw8836_UpgradeOKFlage=0;
    fTw8836.ADI7186DVRFlag=0;
    fTw8836.ADI7186OVERLAYDisable=0;
	
    fTw8836.BackScreenMode = e_NONE_INPUT_OUT_NULL;
    fTw8836.CvbsCurType = VIDEO_CVBS_NULL;
    fTw8836.ReverseFlag.byte = OFF;

    I2CDevCtrl.gDisposalStep = 0;
    I2CDevCtrl.gRWStep = 0;
    I2CDevCtrl.gResult = 0;
    I2CDevCtrl.gWriteCnt = 0;
    I2CDevCtrl.gErrCnt = 0;
    fTw8836.WriteRegStep=0;
    fTw8836.ADI7186_OverlayFlag=0;
	fTw8836.ADI7186_OverlayProgrammeFlag = 0;
	fTw8836.ADI7186_ProgrammeOver = 0;
    fTw8836.ADI7186CvbsDetStep=0;
    fTw8836.ADI7186_ReverseStartFlag=0;
    fTw8836.ADI7186_ReverseStopFlag=0;
    fTw8836.AVM_OsShowFlag=0;
    fTw8836.LockData=0;
    fTw8836.LockFlag=0;
    fTw8836.AINSEL=0;
	fTw8836.CurrentCvbsChannel = 0;
}

/**********************************************************
 * @function    ADI7186_CheckReady
 * @brief      Get ADI7186 Ready flag
 * @param      Null
 * @retval     Result
 **********************************************************/
uint8_t ADI7186_SetRst(void)            
{
    IO_Set(IO_IDX_7186_RESET_DUT1,PIN_OUTPUT,VALID);    
    return (SUBLAYER_DONE);
}
/**********************************************************
 * @function    ADI7186_CheckReady
 * @brief      Get ADI7186 Ready flag
 * @param      Null
 * @retval     Result
 **********************************************************/
uint8_t ADI7186_ClearRst(void)            
{
    IO_Set(IO_IDX_7186_RESET_DUT1,PIN_OUTPUT,INVALID);    
    return (SUBLAYER_DONE);
}
/**********************************************************

/**********************************************************
 * @function    TW8836_IICStartup
 * @brief      TW8836 IIC Startup
 *            include: Power ,Reset, Initialize
 * @param      None
 * @retval     result of execute
 **********************************************************/
uint8_t TW8836_DriverStartup(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    if(fTw8836.DrvDelay>0)
    {
        return (SUBLAYER_DOING);
    }

    switch(fTw8836.DrvSubStep)
    {
        case TW8836_STARTUP_POWER:
            IO_Set(IO_IDX_8836A_PWR,PIN_OUTPUT,VALID);
            fTw8836.DrvDelay = TW8836Delay(T200MS);
            fTw8836.DrvSubStep = TW8836_STARTUP_IICBUS;
            video_printf(_T("TW8836_STARTUP_POWER\n"));
            break;

        case TW8836_STARTUP_IICBUS:
            if(OS_TaskIsActive(TASK_ID_I2C0))
            {
                fTw8836.DrvSubStep = TW8836_STARTUP_RVER;
            }
            else
            {
                SubResult = OS_TaskStart(TASK_ID_I2C0);
                if(TRUE == SubResult)
                {
                    fTw8836.DrvSubStep = TW8836_STARTUP_RVER;
                }
                else
                {
                    //Re-Check Bus
                }
            }
            break;
        case TW8836_STARTUP_RVER:
           // SubResult = Tw8836_ReadCommon((PAGE0_GENERAL|0x01),&(fTw8836.ReadData),0);
               SubResult=SUBLAYER_DONE;
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = TW8836_STARTUP_POWER;
                Result = SUBLAYER_DONE;
                video_printf(_T("TW8836_STARTUP_END:%x\n",fTw8836.ReadData));
            }
	     else if(I2C_RET_SUCCESS < I2CDevCtrl.gResult)
	     	{
	     	    if(I2CDevCtrl.gErrCnt>=60)
	     	    	{
	     	    	   IO_Set(IO_IDX_8836A_PWR,PIN_OUTPUT,INVALID);
	     	    	   fTw8836.DrvDelay = TW8836Delay(T200MS);
	     	    	   fTw8836.DrvSubStep = TW8836_STARTUP_POWER;
	     	    	   I2CDevCtrl.gErrCnt = 0;
	     	    	}
	     	}
            break;
        default:
            break;
    }

    return (Result);
}


/**********************************************************
 * @function    Tw8836_Regsiter
 * @brief      Update All Tw6638's Register
 * @param      NULL
 * @retval     Result
 **********************************************************/
uint8_t Tw8836_Regsiter(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    CarAVMDataStruct *pData = pCAN_GetAVMData();

    switch(fTw8836.DrvStep)
    {
        case TW8836_REGISTER_START:
			//fTw8836.ADI7186InitProgramme = 0;
            SubResult = TW8836_DriverStartup();
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvStep = TW8836_REGISTER_CLOCK;
            }
            break;
        case TW8836_REGISTER_CLOCK:
            fTw8836.DrvStep = TW8836_REGISTER_SPIDMA;
            break;
        case TW8836_REGISTER_SPIDMA:
            fTw8836.DrvStep = TW8836_REGISTER_TRIEN;
            break;
        case TW8836_REGISTER_TRIEN:
            SubResult = SUBLAYER_DONE;
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvStep = TW8836_REGISTER_LVDS;
	     	  video_printf(_T("7186_Register write ---\n"));
            	}
            break;
        case TW8836_REGISTER_LVDS:
              SubResult = Tw8836_WriteCommon((uint8_t*)(&( SCREENDATA_LVDS_BT656_CVBS_ALL[0])));

            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvStep = TW8836_REGISTER_GAMMA;
                video_printf(_T("Tw8836_LVDS Register ok\n"));
            }
            break;
        case TW8836_REGISTER_GAMMA:
              SubResult = TW8836_WriteData(0xAC,0x00,0x2A);
            if(SUBLAYER_DONE == SubResult)
            {
            	#if 1   //snake20161013
                	//fTw8836.DrvStep =  TW8836_REGISTER_SETCVBS1_START;
                	fTw8836.DrvStep = TW8836_REGISTER_OPEN_TFT;
				#else
					fTw8836.DrvStep = TW8836_REGISTER_END;
				#endif
            }
            break;
		case TW8836_REGISTER_OPEN_TFT: //snake20161109
			if((l_tMediaCB.eState == MEDIA_STATE_RUNNING) && (IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE)))//等待MEDIA初始化成功...
			{
				PM_TftPowerSet(ON,0);
				video_printf(_T("ADI Init Programme Over....OPEN TFT\n"));
			}
			//else
				fTw8836.ADI7186InitProgramme = 1;
			fTw8836.DrvStep = TW8836_REGISTER_SETCVBS1_START;
			break;
		//snake20161013
		case    TW8836_REGISTER_SETCVBS1_START:
              SubResult = TW8836_WriteData(0x4c,0x03,0x10);
			  //注意,在写CVBS通道的时候,不能去写其他的寄存器,不然就会无效的...一定要等待图像稳定,才能去写其他的寄存器
            if(SUBLAYER_DONE == SubResult)
            {
				fTw8836.DrvDelay = TW8836Delay(T1S);  // 250ms
				fTw8836.DrvStep =  TW8836_REGISTER_SETCVBS1_END;
				video_printf(_T("7186 Init Round Set CVBS Channel:Set CVBS1 Success!!!!\n"));
            }
			break;

		case TW8836_REGISTER_SETCVBS1_END:
			if(fTw8836.DrvDelay == 0)
				fTw8836.DrvStep =  TW8836_REGISTER_SETCVBS2_START;
			break;
			
		case TW8836_REGISTER_SETCVBS2_START:
			SubResult = TW8836_WriteData(0x4c,0x03,0x20);
            if(SUBLAYER_DONE == SubResult)
            {
				fTw8836.DrvDelay = TW8836Delay(T1S);//snake延时时间和摄像头有关系   700ms
				fTw8836.DrvStep =  TW8836_REGISTER_SETCVBS2_END;
				video_printf(_T("7186 Init Round Set CVBS Channel:Set CVBS2 Success!!!!\n"));
            }
			break;
		case TW8836_REGISTER_SETCVBS2_END:
			if(fTw8836.DrvDelay == 0)
				fTw8836.DrvStep =  TW8836_REGISTER_END;
			break;
		case TW8836_REGISTER_SETCVBS3_START:
			SubResult = TW8836_WriteData(0x4c,0x03,0x30);
            if(SUBLAYER_DONE == SubResult)
            {
				fTw8836.DrvDelay = TW8836Delay(T200MS);//snake延时时间和摄像头有关系
				fTw8836.DrvStep =  TW8836_REGISTER_SETCVBS3_END;
				video_printf(_T("7186 Init Round Set CVBS Channel:Set CVBS3 Success!!!!\n"));
            }
			break;
		case TW8836_REGISTER_SETCVBS3_END:
			if(fTw8836.DrvDelay == 0)
				fTw8836.DrvStep =  TW8836_REGISTER_END;
			break;

			
        case TW8836_REGISTER_END:
                SubResult = SUBLAYER_DONE; //TW8836_PanelMute(OFF);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.BackScreenMode = e_LVDS_INPUT_LVDS_OUT;
		  		pData->ADIINITFlag=1;
                Result = SUBLAYER_DONE;
                video_printf(_T("7186 init end\n"));
            }
            break;
        default:
            Result = SUBLAYER_STEP_ERROR;
            break;

    }

    return (Result);
}

/**********************************************************
 * @function    Tw8836_GetVch
 * @brief      Transfer Logical VCH to Physical VCH of Tw8836
 * @param      uint8_t Vch
 * @retval     NULL
 **********************************************************/
uint8_t Tw8836_GetVch(uint8_t Vch, uint8_t Type)
{
    uint8_t tVideoMode=e_NONE_INPUT_OUT_NULL;
    //video_printf(_T("Tw8836_GetVch:%d,%d\n",Vch,Type));
    switch(Vch)
    {
    	case SRC_TYPE_CAMERA://snake20160810
        case SRC_TYPE_REVERSE:            //CVBS From Camera
         //Set Front System route
         	#ifdef D_REVERSV_FAST_ALL //snake20160906
	            if((SYSTEM_ALL == Type) || ((SYSTEM_FRONT == Type)))//全部使用快速倒车
	            {
	                tVideoMode = e_CVBS_INPUT_LVDS_OUT;
	            }
			#else
				if((SYSTEM_ALL == Type) || ((SYSTEM_FRONT == Type)))//区分快速倒车和正常倒车...
	            {
	            	if(!l_tMediaCB.uDevFlag.field.bUnLocked)
	                	tVideoMode = e_CVBS_INPUT_LVDS_OUT;
					else
						tVideoMode = e_CVBS_INPUT_BT656_OUT;
	            }
			#endif
            break;
        case SRC_TYPE_DVR:
            //Set Front System route
            if((SYSTEM_ALL == Type) || ((SYSTEM_FRONT == Type)))
            {
                tVideoMode = e_CVBS_INPUT_BT656_OUT;
            }
            break;
        case SRC_TYPE_DVD:            //yuv -656-Android LVDS
        case SRC_TYPE_DTV:            //CVBS -656-Android LVDS,default lvds
        default:    //Android LVDS
            if((SYSTEM_ALL == Type) || ((SYSTEM_FRONT == Type)))
            {
                tVideoMode = e_LVDS_INPUT_LVDS_OUT;
            }
            break;
    }

    return tVideoMode;
}

/**********************************************************
 * @function    Tw8836_GetCvbsType
 * @brief      Transfer Logical VCH to Physical VCH of Tw8836
 * @param      uint8_t Vch
 * @retval     NULL
 **********************************************************/
uint8_t Tw8836_GetCvbsType(uint8_t Vch)
{
    uint8_t tCvbsType = VIDEO_CVBS_NULL;
    switch(Vch)
    {
    	
        case SRC_TYPE_REVERSE:            //CVBS From Camera
            tCvbsType = VIDEO_CVBS_CAM1;
            break;
		case SRC_TYPE_CAMERA://snake20160810
        // SRC_TYPE_DVR://SRC_TYPE_CAMERA:
            tCvbsType = VIDEO_CVBS_CAM2;
		
            break;
		case SRC_TYPE_DVR://snake20160901 aux video channel use for dvr R103-H15T
			tCvbsType = VIDEO_CVBS_CAM3;
			break;
        case SRC_TYPE_DTV:            //CVBS From AK
            tCvbsType = VIDEO_CVBS_DTV;
            break;
        case SRC_TYPE_DVD:            //CVBS From AK
            tCvbsType = VIDEO_CVBS_DVD;
            break;
        default:
            break;
    }

    return tCvbsType;
}

/**********************************************************
 * @function    Tw8836_ScreenParameterUpdate
 * @brief
 * @param      uint8_t Vch
 * @retval     NULL
 **********************************************************/
static uint8_t GetCvbsType = VIDEO_CVBS_NULL;//snake20161025 时序差异导致不能按照目标的CVBS通道切换,而是切换到0,所以不能使用局部变量
static uint8_t VmodeIdex = 0;
uint8_t Tw8836_ScreenParameterUpdate(uint8_t Vch,uint8_t Vmode)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    
    if((fTw8836.DrvDelay)/*||(ON == ReverseParkRefreshFlag)*/)
    {
        return SUBLAYER_DOING;
    }

    switch(fTw8836.DrvSubStep)
    {
        case OPERATION_0:
            GetCvbsType = Tw8836_GetCvbsType(Vch);
            if((fTw8836.BackScreenMode == Vmode)&&(GetCvbsType == fTw8836.CvbsCurType))
            {
                fTw8836.DrvSubStep = OPERATION_6;
            }
            else
            {
                fTw8836.DrvSubStep = OPERATION_1;
				if(fTw8836.ADI7186_OverlayProgrammeFlag == 0)
					fTw8836.ADI7186_ProgrammeOver = 1;
				video_printf(_T("ADI7186 switch video channel start!!!!fTw8836.ADI7186_OverlayProgrammeFlag = %d,fTw8836.ADI7186_ProgrammeOver = %d\n",fTw8836.ADI7186_OverlayProgrammeFlag,fTw8836.ADI7186_ProgrammeOver));
			}
            fTw8836.CvbsCurType = GetCvbsType;
            break;
         case OPERATION_1:
		 	//只有进退倒车(盲区)的时候,才进行关屏操作 snake20160906
		 	#if 0
		    if(((Vmode == e_CVBS_INPUT_LVDS_OUT)&&(fTw8836.BackScreenMode == e_LVDS_INPUT_LVDS_OUT)) 
				|| ((Vmode == e_LVDS_INPUT_LVDS_OUT)&&(fTw8836.BackScreenMode == e_CVBS_INPUT_LVDS_OUT)))
			#else
		    if((Vmode == e_CVBS_INPUT_LVDS_OUT) || (Vmode == e_LVDS_INPUT_LVDS_OUT))
			#endif
			{
				PM_CloseBackLight_temp(TFT_BL_OFF);
			}		
			SubResult = SUBLAYER_DONE;
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_2;
            }
            break;
        case OPERATION_2:
           SubResult = SUBLAYER_DONE;
	       fTw8836.ReadData=3;	
            if(SubResult == SUBLAYER_DONE)
            {
                video_printf(_T("--pannel mute:%x --\n",fTw8836.ReadData));
                if(3 == fTw8836.ReadData)
                {	
                	#if 0 //snake20161025 
					if(fTw8836.BackScreenMode != Vmode)
                    {
                        fTw8836.DrvSubStep = OPERATION_3;
                    }
                    else
                    {
                    	if(fTw8836.CvbsCurType == GetCvbsType)
                        	fTw8836.DrvSubStep = OPERATION_4;
						else
							fTw8836.DrvSubStep = OPERATION_3;
                    }
					#else
						fTw8836.DrvSubStep = OPERATION_3;
					#endif
                }
                else
                {
                    fTw8836.DrvSubStep = OPERATION_1;
                }
            }
            break;	
	   case OPERATION_3:	
	   	#if 0
	      // SubResult = TW8836_WriteData(0xAC,0x00,0x2A);
	           //SubResult = SUBLAYER_DONE;
	     if(Vmode != e_LVDS_INPUT_LVDS_OUT)
	     {
	     	video_printf(_T("Set CVBS Channel:fTw8836.CvbsCurType = %d,GetCvbsType = %d\n",fTw8836.CvbsCurType,GetCvbsType));
			if(fTw8836.CvbsCurType == VIDEO_CVBS_CAM1)
				SubResult = TW8836_WriteData(0x4C,0x03,0x10);
			else if(fTw8836.CvbsCurType == VIDEO_CVBS_CAM2)
				SubResult = TW8836_WriteData(0x4C,0x03,0x20);
			else if(fTw8836.CvbsCurType == VIDEO_CVBS_CAM3)
				SubResult = TW8836_WriteData(0x4C,0x03,0x30);
			else if(fTw8836.CvbsCurType == VIDEO_CVBS_CAM4)
				SubResult = TW8836_WriteData(0x4C,0x03,0x40);		 
			else
				SubResult = SUBLAYER_DONE;//TW8836_WriteData(0x4C,0x03,0x00);//当在CVBS的时候,选择此通道会出现闪白条的现象...
				
	     }
		 else
		 	SubResult = SUBLAYER_DONE;
		 
			if(SUBLAYER_DONE == SubResult)
		    {
				fTw8836.DrvSubStep = OPERATION_4;
				//倒车和盲区之间切换,也刷写一下参数...
				/*if(fTw8836.BackScreenMode == Vmode)//snake20161007  倒车和盲区之间快速切换...
				{
					fTw8836.DrvDelay = TW8836Delay(T250MS);
					fTw8836.DrvSubStep = OPERATION_5;
				}*/
			}
		#endif
			if(Vmode != e_LVDS_INPUT_LVDS_OUT)
				VmodeIdex = Vmode + fTw8836.CvbsCurType - 1;
			else
				VmodeIdex = Vmode;
			video_printf(_T("---VmodeIdex = %d\n",VmodeIdex));
			
			//防止在叠加的时候,写参数,或者在写参数的时候,叠加...
			video_printf(_T("[OPERATION_3] fTw8836.ADI7186_ProgrammeOver = %d,fTw8836.ADI7186_OverlayProgrammeFlag = %d\n",fTw8836.ADI7186_ProgrammeOver,fTw8836.ADI7186_OverlayProgrammeFlag));
			if(fTw8836.ADI7186_OverlayProgrammeFlag == 0)
			{
				fTw8836.ADI7186_ProgrammeOver = 1;
			}
			else
			{
				fTw8836.ADI7186_OverlayProgrammeFlag = 0;
				fTw8836.DrvDelay = TW8836Delay(T50MS);// 50ms的超时,防止出现黑屏的现象...  互斥超时机制...
			}
			fTw8836.DrvSubStep = OPERATION_4;
            break;
        case OPERATION_4:
			fTw8836.ADI7186_ProgrammeOver = 1;
            SubResult = Tw8836_WriteCommon((uint8_t*)(ScreenParameter[VmodeIdex - 1]));
            if(SUBLAYER_DONE == SubResult)
            {      
				video_printf(_T("*********VmodeIdex= %d,Vmode=%x,fTw8836.CvbsCurType = %d--\n",VmodeIdex,Vmode,fTw8836.CvbsCurType));
				if(Vmode == e_CVBS_INPUT_LVDS_OUT)
				{
					#if 0
					if((!fTw8836.ADI7186FirstEnterCamera) && (SRC_TYPE_CAMERA == Vch))//snake20161013 第一次进盲区时间比较长...
					{
						fTw8836.ADI7186FirstEnterCamera = 1;
						fTw8836.DrvDelay = TW8836Delay(T700MS);
						video_printf(_T("[22222] MCU is First Enter Camera!!!!!!!!\n"));
					}
					else
					#endif
					//这个和ARM这边的执行时序也有关系,需要优化Android系统的速度...
					fTw8836.DrvDelay = TW8836Delay(T600MS); // 由350ms改成450ms.防止读写冲突
				}
				else if(Vmode == e_LVDS_INPUT_LVDS_OUT)
				{
					fTw8836.DrvDelay = TW8836Delay(T100MS);	
				}
				OS_ClearOsTick();
				fTw8836.DrvSubStep = OPERATION_5;
            }
            break;
        case OPERATION_5:
			#if 0 //snake20160906
			/*
			if(VIDEO_CVBS_NULL != fTw8836.CvbsCurType)
			{
				if(Vmode == e_CVBS_INPUT_LVDS_OUT)//倒车和盲区的时候用于在图片叠加 snake20160914
				if(l_tMediaCB.uDevFlag.field.bDevConnect==1)
				{
					SubResult = TW8836_WriteData(0xA4,0xA6,0x00);//叠加
				}
				else
				{
					SubResult = TW8836_WriteData(0xA4,0xA6,0x7f);//不叠加
				}
			}
			else
			{
				//SubResult = SUBLAYER_DONE;
					SubResult = TW8836_WriteData(0xA4,0xA6,0x00);//叠加
			}
			*/
			
			
            if(SUBLAYER_DONE == SubResult)
            {
            					fTw8836.DrvSubStep = OPERATION_6;					 
				PM_CloseBackLight_temp(TFT_BL_ON);
				_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);//upgrade backlight level


				/*if(( fTw8836.ADI7186_ReverseStartFlag==1)||(fTw8836.ADI7186_ReverseStopFlag==1)
					||(OS_GetOsTick() >=_APU_SEND_RVERSE_STATE_TIMEOUT)||(l_tMediaCB.uDevFlag.field.bDevConnect==0))
				{
					OS_ClearOsTick();
					fTw8836.DrvSubStep = OPERATION_6;			 			
					PM_CloseBackLight_temp(TFT_BL_ON);
					_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);//upgrade backlight level
					fTw8836.ADI7186_ReverseStartFlag=0;
					fTw8836.ADI7186_ReverseStopFlag=0;
					video_printf(_T("*****Open Backlight********\n"));
				}*/
            }
			#else
				if(fTw8836.DrvDelay == 0)
				{
					fTw8836.DrvSubStep = OPERATION_6;
					HMIStatusFlag.g_tUpdataReverseParameter = 0;
					HMIStatusFlag.g_tUpdataBlindParameter = 0;
					if(IO_Get(IO_IDX_LOCAL_ACC,PIN_INPUT,TRUE))//snake20161101
					{
						if(l_tMediaCB.eState == MEDIA_STATE_RUNNING)//先倒车,在开BATT....如果ARM初始化出现异常,就会出现白屏问题...
						{
							PM_CloseBackLight_temp(TFT_BL_ON);
						}
						else
							video_printf(_T("Enter Reverve or Camera,but Media state is not in RUNNING,not OPEN TFT\n"));
					}
					_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);//upgrade backlight level
				}
			#endif
            break;
        case OPERATION_6:
			/*
			if(VIDEO_CVBS_CAM1 == fTw8836.CvbsCurType)
			{
				ReverseParkRefreshFlag=1;    
				ADIReversePwrFlag=ON;
			}
			*/
            fTw8836.DrvSubStep = OPERATION_0;
            fTw8836.BackScreenMode = Vmode;
			fTw8836.ADI7186_ProgrammeOver = 0;
            Result = SUBLAYER_DONE;
            video_printf(_T("Tw8836_DrvSubStep END\n"));
            break;

        default:
            Result = SUBLAYER_STEP_ERROR;
            break;
    }

    return (Result);
}

/**********************************************************
 * @function    Tw8836_SwitchVch
 * @brief
 * @param      uint8_t Vch: Required Video Channel
 * @retval     result of execute
 **********************************************************/
uint8_t Tw8836_SwitchVch(uint8_t Vch, uint8_t Type)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t tVideoMode;

    //Get System New Logic Vch Config: transfer to Physical Ch
    tVideoMode = Tw8836_GetVch(Vch,Type);

    if(SRC_ZONE_REAR == Type)
    {
        video_printf(_T("Rear Tw8836_SwitchVch:%d,%d,%d return\n",fTw8836.CvbsCurType,fTw8836.BackScreenMode,tVideoMode));
        return SUBLAYER_DONE;
    }

	//video_printf(_T("-------Updata 7186 Parameter:Vch = %d,Type = %d,tVideoMode = %d\n",Vch,Type,tVideoMode));
    Result = Tw8836_ScreenParameterUpdate(Vch,tVideoMode);

#if D_DEBUG_VIDEO
    if(SUBLAYER_DONE == Result)
    {
        video_printf(_T("SwitchVch end :%d,%d\n",fTw8836.BackScreenMode,fTw8836.CvbsCurType));
    }
#endif
    return (Result);
}

/**********************************************************
 * @function    TW8836_SetLvdsTxEnable
 * @brief
 * @param      NULL
 * @retval     NULL
 **********************************************************/
void TW8836_SetLvdsTxEnable(void)
{
    fTw8836.LvdsOnStep = TW8836_REGISTER_LVDSTX;
}

/**********************************************************
 * @function    Tw8836_LvdsTxDisposal
 * @brief
 * @param
 * @retval
 **********************************************************/
void Tw8836_LvdsTxDisposal(void)
{
    uint8_t SubResult = SUBLAYER_DOING;

    if(TW8836_REGISTER_END != fTw8836.DrvStep)
    {
        return;
    }

    switch(fTw8836.LvdsOnStep)
    {
        case TW8836_REGISTER_LVDSTX:
            // SubResult = Tw8836_WriteCommon((uint8_t*)(&(Tw8836_LvdsTx[0])));
             // IO_Set(IO_IDX_TFT_POWER_EN, PIN_OUTPUT, VALID);
                 SubResult = SUBLAYER_DONE ;
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.LvdsOnStep = TW8836_REGISTER_END;
                sVideo.VchSwitchEn = 1;	
                //_SendMsgToVideo(MS_VIDEO_UPLOAD_INFO,0,NULL);
                video_printf(_T("Tw8836_LVDS ok\n"));
            }
            break;
        case TW8836_REGISTER_END:
	 default:
            break;
    }
}
/**********************************************************
 * @function    Tw8836_DownloadOsdBmp
 * @brief
 * @param
 * @retval     result of execute
 **********************************************************/


/**********************************************************
 * @function    Tw8836_ParkOsdRefresh
 * @brief
 * @param
 * @retval
 **********************************************************/
void Tw8836_ParkOsdRefresh(uint8_t winno, uint32_t spi_addr)
{
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t wStep=0;
    uint8_t OsdSpiAddr[OSD_WIN_SPIADDR];
    uint16_t WinReg;


    switch(fTw8836.OsdUpdateStep)
    {
        case OPERATION_0:
	 #if 0
            spi_addr /=16;
            fTw8836.OsdBuffData[0]=0xFF;
            fTw8836.OsdBuffData[1]=0x04;
            fTw8836.OsdBuffData[2]=(/*PAGE4_SOSD|*/WIN_NUM(winno));
            fTw8836.OsdBuffData[3]=WIN_PIXLW|WIN_PERPIX|WIN_ALPHA_ENA|WIN_ENA(0x00);
            fTw8836.OsdBuffData[4]=(/*PAGE4_SOSD|*/WIN_NUM(winno)|0x07);
            fTw8836.OsdBuffData[5]=WIN_BFM_AST_HB(spi_addr);   // image addr
            fTw8836.OsdBuffData[6]=(/*PAGE4_SOSD|*/WIN_NUM(winno)|0x08);
            fTw8836.OsdBuffData[7]=WIN_BFM_AST_MB(spi_addr);
            fTw8836.OsdBuffData[8]=(/*PAGE4_SOSD|*/WIN_NUM(winno)|0x09);
            fTw8836.OsdBuffData[9]=WIN_BFM_AST_LB(spi_addr);
            fTw8836.OsdBuffData[10]=(/*PAGE4_SOSD|*/WIN_NUM(winno));
            fTw8836.OsdBuffData[11]=fTw8836.OsdBuffData[3]|WIN_ENA(0x01);
            fTw8836.OsdBuffData[12]=0x00;
            fTw8836.OsdBuffData[13]=0x04;
            fTw8836.OsdBuffData[14]=0xFF;
            fTw8836.OsdBuffData[15]=0xFF;
           #endif
		   
            fTw8836.OsdUpdateStep = OPERATION_1;
            break;
        case OPERATION_1:
       //SubResult = Tw8836_WriteCommon((uint8_t*)(&(fTw8836.OsdBuffData[0])));
           SubResult = SUBLAYER_DONE;
            if(SUBLAYER_DONE == SubResult)
            {
                ReverseParkRefreshFlag = OFF;
                //_SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);
                fTw8836.OsdUpdateStep = OPERATION_0;
                video_printf(_T("ParkOsdRefresh\n"));
            }
            break;
    }

    //  video_printf(_T("--SubResult:%x--\n",TW8836_Read(PAGE4_SOSD|0x00)));
}

/**********************************************************
 * @function    Tw8836_ShowParkUi
 * @brief
 * @param
 * @retval
 **********************************************************/
void Tw8836_ShowParkUi(void)
{
    uint8_t SubResult = SUBLAYER_DOING;

    if(OFF == ReverseParkRefreshFlag)
    {
        return;
    }
    //video_printf(_T("Tw8836_ShowParkUi\n"));
    switch(ReverseParkUiInit)
    {
        case 0:
         //SubResult = Tw8836_WriteOneCommon((PAGE4_SOSD|0x00), 0x04,0);
	     SubResult = SUBLAYER_DONE;	
            if(SUBLAYER_DONE == SubResult)
            {
                ReverseParkUiInit = 1;
               // _SendMsgToPM(MS_PM_TFT_INFO,OP_DEV_STATE_UPDATA,NULL);
                ReverseParkRefreshFlag = OFF;
                video_printf(_T("Tw8836_ShowParkUi init\n"));
            }
            break;
        case 1:
            video_printf(_T("Tw8836_ShowParkUi %d\n",ReverseParkModeFlag));
            switch(ReverseParkModeFlag)
            {
                case 0:
                    Tw8836_ParkOsdRefresh(SPI_WIN1_ST,PAM_BTN_MODE0);
                    break;
                case 1:
                    Tw8836_ParkOsdRefresh(SPI_WIN1_ST,PAM_BTN_MODE1);
                    break;
                case 2:
                    Tw8836_ParkOsdRefresh(SPI_WIN1_ST,PAM_BTN_MODE2);
                    break;
            }
            break;
        default:
            break;
    }
}

/**********************************************************
 * @function    Tw8836_ShowOsd
 * @brief
 * @param
 * @retval     result of execute
 **********************************************************/
void Tw8836_ShowOsd(void)
{

    switch(fTw8836.CvbsCurType)
    {
        case VIDEO_CVBS_CAM1:            //CVBS From Camera
            Tw8836_ShowParkUi();
            break;
        default:
            break;
    }

}

/**********************************************************
 * @function    Tw8836_Disposal
 * @brief
 * @param
 * @retval
 **********************************************************/
void Tw8836_Disposal(void)
{
  
    //Tw8836_ShowOsd();
    Tw8836_LvdsTxDisposal();
    //Tw8836_UpgradeProcess();
     ADI7186_Disposal();
     ADI7186_CvbsLockDet();
}


void ADI7186_Disposal(void)
{

	uint8_t SubResult = SUBLAYER_DOING;
	if((fTw8836.ADI7186_OverlayFlag==1) && (fTw8836.ADI7186_ProgrammeOver == 0))
	{    
		fTw8836.ADI7186_OverlayProgrammeFlag = 1;
		if(SUBLAYER_DONE ==TW8836_WriteData(0xA4,0xA6,0x00))
		{
			fTw8836.ADI7186_OverlayFlag=0;
			fTw8836.ADI7186_OverlayProgrammeFlag = 0;
			video_printf(_T("Write DigitalOverLay Sucessfull!!!!!\n"));
		}
	}
		
	//ADI7186 切换DVR的视频通道
	if((g_tMcuDevState.uIOState.bits.Reverse_Flag == 0)&&(g_tMcuDevState.uDetect.bits.Blind_Flag == 0))
	{
		if(fTw8836.ADI7186DVRFlag==1)
		{
			#if 0 //snake20160905 新硬件的DVR使用CVBS_CAM3
				SubResult = TW8836_WriteData(0x4C,0x03,0x20);
			#else
				SubResult = TW8836_WriteData(0x4C,0x03,0x30);
			#endif
			if(SubResult ==SUBLAYER_DONE)
			{
				fTw8836.ADI7186DVRFlag=2;
			}
		}

	}
	else  
	{
		if(fTw8836.ADI7186OVERLAYDisable==1)
		{
			SubResult = TW8836_WriteData(0xA4,0xA6,0x7F);
			if(SubResult ==SUBLAYER_DONE)
			{
				fTw8836.ADI7186OVERLAYDisable=0;
				video_printf(_T("Write DigitalOverLay Sucessfull!!!!!....not show UI.....\n"));
			}
		}
	}
}

#if 1
uint8_t ReadCvbsChannelFlagCnt = 0;
uint8_t ReadCvbsChannelCnt = 0;
//uint8_t ReadLockFlagCnt = 0;
uint8_t ReadLockCnt = 0;
uint8_t ReadRegFlag = 0;
void ADI7186_CvbsLockDet(void)
{
	uint8_t Result = SUBLAYER_DOING;
	uint8_t SubResult = SUBLAYER_DOING;
	uint8_t CurrentCvbsChannel = 0;
	CarDvrDataStruct *pData = pCAN_GetDvrData();
	

	//读取寄存器,不能影响初始化的写操作;并且只有和ARM存在通信的时候,才有必要去读..
	if(!fTw8836.ADI7186InitProgramme)
		return;
	if(!l_tMediaCB.uDevFlag.field.bDevConnect)
		return;
	
	if((fTw8836.ADI7186DVRFlag == 2) 
		|| (g_tMcuDevState.uDetect.bits.Blind_Flag == 1) 
		|| (g_tMcuDevState.uIOState.bits.Reverse_Flag == 1))
	{		
		if((g_tMcuDevState.uIOState.bits.Reverse_Flag == 1) && (g_tMcuDevState.uDetect.bits.CvbsChannelFlag == 1))
			CurrentCvbsChannel = 0x10;
		else if((g_tMcuDevState.uDetect.bits.Blind_Flag == 1) && (g_tMcuDevState.uDetect.bits.CvbsChannelFlag == 2))
			CurrentCvbsChannel = 0x20;
		else if((fTw8836.ADI7186DVRFlag == 2) && (g_tMcuDevState.uDetect.bits.CvbsChannelFlag == 0))
			CurrentCvbsChannel = 0x30;
		else
			return;
		
		if(fTw8836.CurrentCvbsChannel != CurrentCvbsChannel)
		{
			video_printf(_T("CvbsChannel:%x---->%x,Start Check...\n",fTw8836.CurrentCvbsChannel,CurrentCvbsChannel));
			fTw8836.CurrentCvbsChannel = CurrentCvbsChannel;
			fTw8836.ADI7186CvbsDetStep = OPERATION_1;
			sVideo.VdDelay = VideoDelay(T400MS); // 由 350ms 改成 450ms
			//sVideo.VdDelay = 0;
			
		}
	}
	else
	{
		fTw8836.ADI7186CvbsDetStep = OPERATION_0;
		sVideo.VdDelay = 0;
	}

	//延时只能放在CVBS通道判断的后面..
	if(sVideo.VdDelay)
	{
		return;
	}
	
	switch(fTw8836.ADI7186CvbsDetStep)
	{
		case OPERATION_0:
			if((ReadRegFlag == 1) /*&& (I2CDevCtrl.gResult == I2C_RET_SUCCESS)*/) // 注意:在读的过程中,进行了切源,就会造成当前还在读,但是又要进行写的操作,所以就在这里停止读的操作...
			{
				I2CDevCtrl.gRWStep = 0;
				ReadRegFlag = 0;
				video_printf(_T("******************in read operate,but stop src.*****************\n"));
			}
			ReadCvbsChannelCnt = 0;
			fTw8836.CurrentCvbsChannel = 0;
			//pData->DVR_VideoSignalLockStatus = 0x0;//由于从各个界面进入DVR app都会发送open app的消息,但是不切通道,所以就不需要将其置为0
			g_tMcuDevState.uDetect.bits.CvbsChannelLock = 0x0;
			break;
		case OPERATION_1:
			if((I2CDevCtrl.gResult == I2C_RET_IDLE) || (I2CDevCtrl.gResult == I2C_RET_SUCCESS))
			{
				sVideo.VdDelay = VideoDelay(T150MS); 
				fTw8836.LockData=0;
				//pData->DVR_VideoSignalLockStatus = 0x0;
				//g_tMcuDevState.uDetect.bits.CvbsChannelLock = 0x0;
				fTw8836.ADI7186CvbsDetStep = OPERATION_2;
				video_printf(_T("------------------------\n"));
			}
			break;
		case OPERATION_2: //检测CVBS通道...
			//只有在操作成功之后,或者IIC空闲的状态下,才能进行读操作.
			//video_printf(_T("[1] read Channel...... I2CDevCtrl.gResult = %d\n",I2CDevCtrl.gResult));
			if((I2CDevCtrl.gResult <= I2C_RET_SUCCESS)/*(I2CDevCtrl.gResult == I2C_RET_IDLE) || (I2CDevCtrl.gResult == I2C_RET_SUCCESS)*/)
			{
				//video_printf(_T("read Channel...... I2CDevCtrl.gResult = %d\n",I2CDevCtrl.gResult));
				SubResult=Tw8836_ReadCommon(AFE|ADC_Switch, &fTw8836.AINSEL,0);
				ReadRegFlag = 1;
				//ReadCvbsChannelCnt = 0;
				if(SubResult==SUBLAYER_DONE)
				{
					ReadRegFlag = 0;
					video_printf(_T("fTw8836.AINSEL = %x,CurrentCvbsChannel = %x\n",fTw8836.AINSEL,CurrentCvbsChannel));	
					if(fTw8836.AINSEL == CurrentCvbsChannel)
					{
						fTw8836.ADI7186CvbsDetStep = OPERATION_3;
						ReadCvbsChannelFlagCnt = 0;
					}
					else
					{
						//连续读通道的时候,等待时间为500ms...
						fTw8836.ADI7186CvbsDetStep=OPERATION_1;
						sVideo.VdDelay = VideoDelay(T150MS);
						if(++ReadCvbsChannelFlagCnt >= 5)
						{
							fTw8836.ADI7186CvbsDetStep = OPERATION_5;
							ReadCvbsChannelFlagCnt = 0;
							video_printf(_T("Read Cvbs Channel Timeout.....\n"));
						}
					}
				}
			}
			else
			{	
				//判断IIC error的错误
				if(++ReadCvbsChannelCnt >= 10)
				{
					ReadCvbsChannelCnt = 0;
					fTw8836.ADI7186CvbsDetStep = OPERATION_5;
					video_printf(_T("stop read Channel...... I2CDevCtrl.gResult = %d\n",I2CDevCtrl.gResult));
				}
				else
				{
					fTw8836.ADI7186CvbsDetStep = OPERATION_1;
					video_printf(_T("read Channel......again... I2CDevCtrl.gResult = %d,ReadCvbsChannelCnt = %d\n",I2CDevCtrl.gResult,ReadCvbsChannelCnt));
				}
			}
			break;
		case OPERATION_3:
			if((I2CDevCtrl.gResult == I2C_RET_IDLE) || (I2CDevCtrl.gResult == I2C_RET_SUCCESS))
			{
				//video_printf(_T("read lock flag...... I2CDevCtrl.gResult = %d\n",I2CDevCtrl.gResult));
				//pData->DVR_VideoSignalLockStatus = 0x0;
				//g_tMcuDevState.uDetect.bits.CvbsChannelLock = 0x0;
				SubResult = Tw8836_ReadCommon(SDP|Burst_Lock, &fTw8836.LockData,0);
				ReadRegFlag = 1;
				ReadLockCnt = 0;
				if(SubResult==SUBLAYER_DONE)
				{	
					ReadRegFlag = 0;
					if((fTw8836.LockData&0x80) == 0x80)
					{
						fTw8836.LockFlag = 0x1;
					}
					else
					{
						fTw8836.LockFlag = 0x0;
					}

					if(CurrentCvbsChannel == 0x30)
					{
						if(pData->DVR_VideoSignalLockStatus != fTw8836.LockFlag)
						{
							pData->DVR_VideoSignalLockStatus = fTw8836.LockFlag;
							CANTask_SendPrjApiData(CAN_PRJ_ID_CHANA_R103H,USERID_APU_TX_DVR_SETREQ, 1);
						}
					}
					else
					{
						if(g_tMcuDevState.uDetect.bits.CvbsChannelLock != fTw8836.LockFlag)
						{
							g_tMcuDevState.uDetect.bits.CvbsChannelLock = fTw8836.LockFlag;
							_SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_DEVICESTATUS,&g_tMcuDevState);
						}
					}
					fTw8836.ADI7186CvbsDetStep = OPERATION_4;
					video_printf(_T("fTw8836.LockFlag = %x,CurrentCvbsChannel = %x\n",fTw8836.LockFlag,CurrentCvbsChannel));	
				}
			}
			else
			{
			}
			break;
			
		case OPERATION_4:
			sVideo.VdDelay = VideoDelay(T2S); 
			fTw8836.LockData = 0;
			fTw8836.ADI7186CvbsDetStep = OPERATION_3;
			break;
			
		case OPERATION_5:
			break;
			
		default:
			break;
	}
}
  
#endif

#endif


