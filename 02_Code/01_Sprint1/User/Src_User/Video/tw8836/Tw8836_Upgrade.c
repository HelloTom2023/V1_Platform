/**********************************************************
 * @file        Tw8836_Upgrade.c
 * @purpose
 * @version    0.02
 * @date      2015.09.11
 * @author    XJH
 * @brief
 ***********************************************************
 *     History:
 *  <write/modify>        <time>        <version >    <desc>
 *  Deefisher.Lyu          02.Feb.2013        v0.01        created
 * *  XJH		          2015.09.11        v0.02        MODIFY
  **********************************************************/
#define Tw8836_Upgrade
/* ========================= File include ======================= */
#include "..\..\config\inc.h"
uint8_t rFlag = 0;

/**********************************************************
 * @function    Tw8836_ResetMcu
 * @brief
 * @param
 * @retval     result of execute
 **********************************************************/
uint8_t Tw8836_ResetMcu(uint8_t flag)
{
    uint8_t Result = SUBLAYER_DOING;
    switch(fTw8836.DrvSubStep)
    {
        case OPERATION_0:
            fTw8836.OsdBuffData[0]=0xff;
            fTw8836.OsdBuffData[1]=0x04;
            fTw8836.OsdBuffData[2]=0xED;
            fTw8836.OsdBuffData[3]=0x55;
            fTw8836.OsdBuffData[4]=0xED;
            fTw8836.OsdBuffData[5]=0xAA;
            fTw8836.OsdBuffData[6]=0xEC;
            fTw8836.OsdBuffData[7]=flag;
            fTw8836.OsdBuffData[8]=0xff;
            fTw8836.OsdBuffData[9]=0xff;
            fTw8836.DrvSubStep = OPERATION_1;
            break;
        case OPERATION_1:
            Result = Tw8836_WriteCommon((uint8_t*)(&(fTw8836.OsdBuffData[0])));
            if(SUBLAYER_DONE == Result)
            {
                fTw8836.DrvSubStep = OPERATION_0;
                Upgrade8836_printf(_T(" Tw8836_HoldMcu\n"));
            }
            break;
    }
    return Result;
}

uint8_t TW8836_SpiWriteEnable(uint8_t flag)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(fTw8836.DrvSubStep)
    {
        case OPERATION_9:
            fTw8836.OsdBuffData[0]=0xff;
            fTw8836.OsdBuffData[1]=0x04;
            fTw8836.OsdBuffData[2]=0xF3;
            fTw8836.OsdBuffData[3]=0xC1;
            fTw8836.OsdBuffData[4]=0xFA;
            fTw8836.OsdBuffData[5]=0x06;
            fTw8836.OsdBuffData[6]=0xF4;
            fTw8836.OsdBuffData[7]=0x03;
            fTw8836.OsdBuffData[8]=0xff;
            fTw8836.OsdBuffData[9]=0xff;
            fTw8836.DrvSubStep = OPERATION_10;
            video_printf(_T("SpiWriteEnable in\n"));
            break;
        case OPERATION_10:
            SubResult = Tw8836_WriteCommon((uint8_t*)(&(fTw8836.OsdBuffData[0])));
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_11;
            }
            break;
        case OPERATION_11:
            SubResult = Tw8836_ReadCommon((PAGE4_SOSD|0xF4),&(fTw8836.ReadData),1);
            if(SUBLAYER_DONE == SubResult)
            {
                video_printf(_T("SpiWriteEnable:%x,%d\n",fTw8836.ReadData,flag));
                if(0 == (fTw8836.ReadData & 0x01))
                {
                    if(1 == flag)
                    {
                        fTw8836.DrvSubStep = OPERATION_12;
                    }
                    else
                    {
                        Result=SUBLAYER_DONE;
                        fTw8836.DrvSubStep = OPERATION_0;
                    }
                }
                else
                {
                    //fTw8836.DrvSubStep = OPERATION_11;
                }
            }
            break;
    }
    return Result;
}

uint8_t Tw8836_BlockErase(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    switch(fTw8836.DrvSubStep)
    {
        case OPERATION_0:
            fTw8836.OsdBuffData[0]=0xff;
            fTw8836.OsdBuffData[1]=0x04;
            fTw8836.OsdBuffData[2]=0xF3;
            fTw8836.OsdBuffData[3]=0xC1;
            fTw8836.OsdBuffData[4]=0xFA;
            fTw8836.OsdBuffData[5]=0xC7;
            fTw8836.OsdBuffData[6]=0xF4;
            fTw8836.OsdBuffData[7]=0x07;
            fTw8836.OsdBuffData[8]=0xff;
            fTw8836.OsdBuffData[9]=0xff;
            fTw8836.DrvSubStep = OPERATION_1;
            video_printf(_T("BlockErase in\n"));
            break;
        case OPERATION_1:
            SubResult = Tw8836_WriteCommon((uint8_t*)(&(fTw8836.OsdBuffData[0])));
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_2;
            }
            break;
        case OPERATION_2:
            SubResult = Tw8836_ReadCommon((PAGE4_SOSD|0xF4),&(fTw8836.ReadData),1);
            if(SUBLAYER_DONE == SubResult)
            {
                video_printf(_T("BlockErase:%x\n",fTw8836.ReadData));
                if(0 == (fTw8836.ReadData & 0x01))
                {
                    Result=SUBLAYER_DONE;
                    fTw8836.DrvSubStep = OPERATION_0;
                }
                else
                {
                    // fTw8836.DrvSubStep = OPERATION_1;
                }
            }
            break;
    }

    return Result;
}

uint8_t TW8836_WriteInFlash(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;
    uint32_t Addr;

    switch(fTw8836.DrvSubStep)
    {
        case OPERATION_0:
            SubResult = Tw8836_WriteOneCommon((PAGE4_SOSD|0xc2), 0x01,0);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_1;
            }
            break;
        case OPERATION_1:
            SubResult = Tw8836_ReadCommon((PAGE4_SOSD|0xc2),&(fTw8836.ReadData),1);
            if(SUBLAYER_DONE == SubResult)
            {
                video_printf(_T("Write in flash case 1:%x\n",fTw8836.ReadData));
                if(0 == (fTw8836.ReadData & 0x02))
                {
                    //fTw8836.DrvSubStep = OPERATION_0;
                }
                else
                {
                    fTw8836.DrvSubStep = OPERATION_2;
                }
            }
            break;
        case OPERATION_2:
            SubResult = Tw8836_WriteOneCommon((PAGE4_SOSD|0xDB), 0x00,1);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_3;
            }
            break;
        case OPERATION_3:
            SubResult = Tw8836_WriteOneCommon((PAGE4_SOSD|0xDC), 0x00,1);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_5;
                fTw8836.OsdBuffData[0] = 0xDD;
            }
            break;
        case OPERATION_4:
            SubResult = Tw8836_WriteOneCommon((PAGE0_GENERAL|0x06), 0x26,0);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_5;
                // I2CDevCtrl.gRWStep = OPERATION_1;
                fTw8836.OsdBuffData[0] = 0xDD;
            }
            break;
        case OPERATION_5:
            if(0 == rFlag)
            {
                break;
            }
            SubResult = Tw8836_AINCWriteCommon((PAGE4_SOSD|0xDD),(uint8_t*)(&(fTw8836.OsdBuffData[0])));
            if(SUBLAYER_DONE == SubResult)
            {
                video_printf(_T("UpgradeOKFlage:%d\n",fTw8836.Tw8836_UpgradeOKFlage));
                fTw8836.DrvSubStep = OPERATION_7;
            }
            break;
        case OPERATION_6:
            SubResult = Tw8836_WriteOneCommon((PAGE0_GENERAL|0x06), 0x06,0);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_7;
            }
            break;
        case OPERATION_7:
            SubResult = Tw8836_WriteOneCommon((PAGE4_SOSD|0xc2), 0x00,0);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvSubStep = OPERATION_8;
            }
            break;
        case OPERATION_8:
            SubResult = Tw8836_ReadCommon((PAGE4_SOSD|0xc2),&(fTw8836.ReadData),1);
            if(SUBLAYER_DONE == SubResult)
            {
                video_printf(_T("Write in flash case 8:%x\n",fTw8836.ReadData));
                if(0x02 == (fTw8836.ReadData & 0x02))
                {
                    // fTw8836.DrvSubStep = OPERATION_7;
                }
                else
                {
                    //Result=SUBLAYER_DONE;
                    fTw8836.DrvSubStep = OPERATION_9;
                }
            }
            break;
        case OPERATION_9:
        case OPERATION_10:
        case OPERATION_11:
            TW8836_SpiWriteEnable(1);
            break;
        case OPERATION_12:
            Addr=offsetendbin+fTw8836.Tw8836_PacketId*0x40;
            Upgrade8836_printf(_T("Addr=%lx\n",Addr));
            fTw8836.OsdBuffData[0]=0xF6;
            fTw8836.OsdBuffData[1]=0x00;
            fTw8836.OsdBuffData[2]=0xF7;
            fTw8836.OsdBuffData[3]=0x00;
            fTw8836.OsdBuffData[4]=0xF3;
            fTw8836.OsdBuffData[5]=0xC4;

            fTw8836.OsdBuffData[6]=0xF5;
            fTw8836.OsdBuffData[7]=0x00;
            fTw8836.OsdBuffData[8]=0xF8;
            fTw8836.OsdBuffData[9]=0x00;
            fTw8836.OsdBuffData[10]=0xF9;
            fTw8836.OsdBuffData[11]=0x40;

            fTw8836.OsdBuffData[12]=0xFA;
            fTw8836.OsdBuffData[13]=0x02;
            fTw8836.OsdBuffData[14]=0xFB;
            fTw8836.OsdBuffData[15]=((Addr>>16)&0xff);
            fTw8836.OsdBuffData[16]=0xFC;
            fTw8836.OsdBuffData[17]=((Addr>>8)&0xff);
            fTw8836.OsdBuffData[18]=0xFD;
            fTw8836.OsdBuffData[19]=(Addr&0xff) ;
            fTw8836.OsdBuffData[20]=0xF4;
            fTw8836.OsdBuffData[21]=0x12;
            fTw8836.OsdBuffData[22]=0xF4;
            fTw8836.OsdBuffData[23]=0x13;
            fTw8836.OsdBuffData[24]=0xFF;
            fTw8836.OsdBuffData[25]=0xFF;

            fTw8836.DrvSubStep = OPERATION_13;
            break;
        case OPERATION_13:
            SubResult = Tw8836_WriteCommon((uint8_t*)(&(fTw8836.OsdBuffData[0])));
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.Tw8836_PacketId++;
                if(1 == fTw8836.Tw8836_UpgradeOKFlage)
                {
                    _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_8836_REQUPDATEDATA,NULL);
                    rFlag=0;
                }
                fTw8836.DrvSubStep = OPERATION_14;
            }
            break;
        case OPERATION_14:
            SubResult = Tw8836_ReadCommon((PAGE4_SOSD|0xF4),&(fTw8836.ReadData),1);
            if(SUBLAYER_DONE == SubResult)
            {
                video_printf(_T("Write in flash case 11:%x\n",fTw8836.ReadData));
                if(0x01 == (fTw8836.ReadData & 0x01))
                {
                    // fTw8836.DrvSubStep = OPERATION_13;
                }
                else
                {
                    fTw8836.DrvSubStep = OPERATION_0;
                    if(2 == fTw8836.Tw8836_UpgradeOKFlage)
                        Result=SUBLAYER_DONE;
                }
            }
            break;
    }

    return Result;
}

void Tw8836_UpgradeInit(void)
{
    fTw8836.Tw8836_PacketId=0;
    fTw8836.Tw8836_UpgradeOKFlage=1;
    fTw8836.OsdUpdateStep = OPERATION_1;
}

void Tw8836_SetUpgradeStatus(uint8_t tStatus)
{
    uint8_t i;
    switch(tStatus)
    {
        case UPGRADE_INIT:
            Tw8836_UpgradeInit();
            break;
        case UPGRADE_DATA:
            fTw8836.OsdUpdateStep = OPERATION_4;
            rFlag=1;
#if 0
            for(i=1; i<65; i++)
            {
                video_printf(_T("0x%x ",fTw8836.OsdBuffData[i]));
            }
            video_printf(_T("\n"));
#endif
            break;
        case UPGRADE_END:
            fTw8836.Tw8836_UpgradeOKFlage = 2;       
            break;
    }
}

void Tw8836_UpgradeProcess(void)
{
    uint8_t SubResult=SUBLAYER_DOING;
    if(0 == fTw8836.Tw8836_UpgradeOKFlage)
    	{
    	   return;
    	}
    switch(fTw8836.OsdUpdateStep)
    {
        case OPERATION_0:
            break;
        case OPERATION_1:
            SubResult = Tw8836_ResetMcu(0x00);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.OsdUpdateStep = OPERATION_2;
                fTw8836.DrvSubStep = OPERATION_9;
            }
            break;
        case OPERATION_2:
            SubResult = TW8836_SpiWriteEnable(0);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.OsdUpdateStep = OPERATION_3;
            }
            break;
        case OPERATION_3:
            SubResult = Tw8836_BlockErase();
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.OsdUpdateStep = OPERATION_0;
                _SendMsgToMedia(MS_UI_UPLOAD_INFO,OP_INFO_8836_REQUPDATEDATA,NULL);
                rFlag=0;
                video_printf(_T("Block Erase end:%d,%d\n",I2CDevCtrl.gResult,I2CDevCtrl.gRWStep));
            }
            break;
        case OPERATION_4:
            SubResult = TW8836_WriteInFlash();
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.OsdUpdateStep = OPERATION_5;
            }
            break;
        case OPERATION_5:
            SubResult = Tw8836_ResetMcu(0x01);
            if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.OsdUpdateStep = OPERATION_0;
		   fTw8836.Tw8836_UpgradeOKFlage = 0;
            }
            break;

    }
}

