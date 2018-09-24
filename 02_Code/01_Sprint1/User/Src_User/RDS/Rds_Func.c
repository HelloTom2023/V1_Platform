/**********************************************************
 * @file        Rds_Func.c
 * @purpose    
 * @version    0.01
 * @date        26.Mar. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          26.Mar.2013        v0.01        created
 *  
  **********************************************************/
#define RDS_FUNC_C
/* ========================= File include ======================= */
#include "..\config\inc.h"
/* ========================= Function Announcement  =================== */


/* ========================= public variable ==================== */

/* ========================= private variable =================== */


/* ========================= Code Part =================== */

/**********************************************************
 * @function    Rds_ChgFreq16To8
 * @brief      Change Frequency 
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Rds_ChgFreq16To8(uint16_t Freq)
{
    return ((Freq - 8750) / 10);
}
/**********************************************************
 * @function    Rds_InitInt
 * @brief      Rds Initial Interrupt
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_InitInt(void)
{
    /* INTP1 Setting */
    PMK1 = 1;    /* INTP1 disable */
    PIF1 = 0;        /* INTP1 IF clear */
    /* Set INTP1 level 3 priority */
    PIC1 &= 0xF8;
    PIC1 |= 0x03;
    INTR0 &= (~0x10);
    //INTR0 |= 0x00;//INTP1_EDGE_RISING_UNSEL;
    INTF0 |= 0x10;//INTP1_EDGE_FALLING_SEL;
    /* INTP1 pin set */
    PMC0 |= 0x10;

    PIF1 = 0;        /* INTP1 IF clear */
    PMK1 = 0;    /* INTP1 enable */
}
/**********************************************************
 * @function    Rds_Isr
 * @brief      Rds interrupt service function
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_Isr(void)
{
    if(RDS_SET_OFF == Tuner_Api_GetRdsSetting())
        return;

    if(VALID == (IO_Get(IO_IDX_RDS_INT0,PIN_INPUT,FALSE)))    //data available when LOW
    {
        sRds.bDataAvailable = 1;
    }
}
/**********************************************************
 * @function    Rds_RtClearBuff
 * @brief      Clear RT Related Parameter
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_RtClearBuff(void)
{
    uint8_t u8Tmp = 0;
    
    for(u8Tmp = 0; u8Tmp < 64; u8Tmp++)
    {
        sRds.RT[u8Tmp] = 0;
    }
    
    sRds.CntRT = 0;
    sRds.NumRT = 0;
    sRds.F_GetRTEmpty = 1;
}
/**********************************************************
 * @function    Rds_RtCheckDiff
 * @brief      Check RT Datum, Judge whether a different Packet
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Rds_RtCheckDiff(uint8_t OldDat,uint8_t NewDat)
{
    uint8_t u8Result = 0;

    if((0x00 != OldDat) && (OldDat != NewDat))
    {
        u8Result = 1;
    }
    
    return (u8Result);
}
/**********************************************************
 * @function    Rds_PushToLast
 * @brief      Fetch Block Datum
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_PushToLast(void)
{
    sRds.BlockLastA = sRds.BlockA; //Saved 
    sRds.BlockLastB = sRds.BlockB;
    sRds.BlockLastC = sRds.BlockC;
    sRds.BlockLastCp = sRds.BlockCp;
    sRds.BlockLastD = sRds.BlockD;

    sRds.F_BlockA = sRds.F_GetBlockA;
    sRds.F_BlockB = sRds.F_GetBlockB;
    sRds.F_BlockC = sRds.F_GetBlockC;
    sRds.F_BlockCp = sRds.F_GetBlockCp;
    sRds.F_BlockD = sRds.F_GetBlockD;
    
    sRds.F_GetBlockA = 0;
    sRds.F_GetBlockB = 0;
    sRds.F_GetBlockC = 0;
    sRds.F_GetBlockCp = 0;
    sRds.F_GetBlockD = 0;

    sRds.F_GetOneGroup = 1;
}
/**********************************************************
 * @function    Rds_AnalyseData
 * @brief      Analyse Received Blocks!
 * @param      None                
 * @retval     None
 **********************************************************/
void Rds_AnalyseData(void)
{
    uint8_t i;
    uint16_t Temp;
    U8_U16_UNION AFtemp;

    if((0 == sRds.bGotBlock) || (0 == sRds.F_GetOneGroup))
        return;

    sRds.F_GetOneGroup = 0;
    
    if(sRds.Level < 20) //Update Rds Level 
    {
        sRds.Level++;
    }
    
    if(sRds.F_BlockA && (sRds.BlockAQual <= 3))    
    {
        sRds.Pi = sRds.BlockLastA; //Get PI...

        //Consider a newly PI got while Get two times same    
        if(sRds.PiLast != sRds.Pi)
        {
            sRds.PiLast = sRds.Pi;    
        }
        else
        {
            if(sRds.PiValid != sRds.Pi)
            {
                sRds.PiValid = sRds.Pi;
                sRds.F_GetNewPi = 1;    //Get Newly PI while got same pi twice...    
            }
            if(0 == sRds.PiBackup) //Save Currently Station's Pi
            {
                sRds.PiBackup = sRds.PiValid;
            }
        }

    }
    
    if(AF_STEP_IDLE != sRds.AFCheckMode)
    {
        return;
    }
    
    if(sRds.F_BlockB && (sRds.BlockBQual <= RDS_ERR_LEVEL))
    {
        if(sRds.BlockBQual <= RDS_ERR_LEVEL) //Check Quality of Block B to avoid unconfirmed PTY
        {
            //Get PTY
            sRds.Pty = (uint8_t)((sRds.BlockLastB & 0x03E0) >> 5);
            if(sRds.PtyLast == sRds.Pty)
            {
                sRds.PtyValid = sRds.Pty;
                sRds.F_GetNewPty = 1;    //Output Newly Pty
            }
            sRds.PtyLast = sRds.Pty;
        }

        //Get TP Flag
        sRds.TP = (sRds.BlockLastB >> 10) & 0x0001;
        if(sRds.TPValid != sRds.TP)
        {
            sRds.TPValid = sRds.TP;
            sRds.F_GetNewTP = 1;
        }

        //Get Group
        sRds.Group = (uint8_t)(sRds.BlockLastB >> 11);

        //Get TA
        if(GroupType(G0) || GroupVersion(G15B))
        {
            sRds.TA = (sRds.BlockLastB >> 4) & 0x0001; 
            if(sRds.TAValid != sRds.TA)
            {
                sRds.TAValid = sRds.TA;
                sRds.F_GetNewTA = 1;
            }
        }
    }

    //Get PS...
    if(sRds.F_BlockB && (GroupType(G0)) && sRds.F_BlockD
        && (sRds.BlockBQual <= 3)  && (sRds.BlockDQual <= 3))    // PS
    {
        i = (uint8_t)(sRds.BlockLastB & 0x03);
        if(((sRds.BlockLastD & 0x00FF) >= 0x20)    && ((sRds.BlockLastD>>8) >= 0x20))
        {
            switch(i)
            {
                case 0:
                    sRds.F_PSGet0 = 1;                
                    sRds.PS[1] = (uint8_t)(sRds.BlockLastD & 0x00FF);
                    sRds.PS[0] = (uint8_t)(sRds.BlockLastD >> 8);
                    break;
                    
                case 1:
                    sRds.F_PSGet1 = 1;
                    sRds.PS[3] = (uint8_t)(sRds.BlockLastD & 0x00FF);
                    sRds.PS[2] = (uint8_t)(sRds.BlockLastD >> 8);
                    break;
                    
                case 2:
                    sRds.F_PSGet2 = 1;
                    sRds.PS[5] = (uint8_t)(sRds.BlockLastD & 0x00FF);
                    sRds.PS[4] = (uint8_t)(sRds.BlockLastD >> 8);
                    break;
                    
                case 3:
                    sRds.F_PSGet3 = 1;
                    sRds.PS[7] = (uint8_t)(sRds.BlockLastD & 0x00FF);
                    sRds.PS[6] = (uint8_t)(sRds.BlockLastD >> 8);
                    break;
            }
        }

        //Get a Whole PS?
        if(sRds.F_PSGet0 && sRds.F_PSGet1 && sRds.F_PSGet2 && sRds.F_PSGet3)
        {
            sRds.F_PSGet0 = 0;
            sRds.F_PSGet1 = 0;
            sRds.F_PSGet2 = 0;
            sRds.F_PSGet3 = 0;

            Temp = 0;
            for(i = 0; i < 8; i++)
            {
                Temp += sRds.PS[i];
            }

            //Validate newly PS while got it two times and same
            if((Temp != sRds.PSCRC)/* && (Temp == sRds.PSCRCTemp)*/)
            {
                sRds.PSCRC = Temp;
                sRds.F_GetNewPS = 1;
                sRds.F_PSExist = 1;
            }
            sRds.PSCRCTemp = Temp;
        }
    }

    //Time...
    if(sRds.F_BlockB && (GroupVersion(G4A)) && sRds.F_BlockC && sRds.F_BlockD)
    {
        if((sRds.BlockBQual <= 3) && (sRds.BlockCQual <= 3) && (sRds.BlockDQual <= 3)) 
        {
            sRds.TimeHour = (uint8_t)(sRds.BlockLastD >> 12) + ((uint8_t)(sRds.BlockLastC & 0x0001) << 4);
            sRds.TimeMin = (uint8_t)((sRds.BlockLastD&0x0FC0)>>6);

            sRds.MJD = ((sRds.BlockLastB & 0x0003) << 15) + (sRds.BlockLastC >> 1);

            Temp = (uint16_t)(sRds.TimeHour * 60) + (uint16_t)sRds.TimeMin + 1440;
            if(sRds.BlockLastD & 0x0020)
            {
                Temp -= ((sRds.BlockLastD & 0x001F) * 30);
            }
            else
            {
                Temp += ((sRds.BlockLastD & 0x001F) * 30);
            }
            Temp = (Temp % 1440);
            sRds.TimeHour = (Temp / 60);
            sRds.TimeMin = (Temp % 60);
            sRds.F_GetNewCT = 1;
        }
    }

    //Get AF List...
    if(sRds.F_BlockA && sRds.F_BlockB && sRds.F_BlockC && (GroupVersion(G0A)) 
        && (sRds.BlockAQual <= 2)    && (sRds.BlockBQual <= 2)    && (sRds.BlockCQual <= 2))
    {
        sRds.Pi = sRds.BlockLastA;

        if(sRds.Pi == sRds.PiBackup)
        {
            AFtemp.Dbyte = sRds.BlockLastC;

            //Filter For LF/MF
            if(AF_AM_TYPE == AFtemp.Byte[U_LOW_BYTE])
            {
                AFtemp.Byte[0] = 0xFF;
                AFtemp.Byte[1] = 0xFF;
            }

            //First In, Only Saved for next judgement
            if((sRds.AFMethod[0] == 0xFF) && (sRds.AFMethod[1]==0xFF))
            {
                sRds.AFMethod[0] = AFtemp.Byte[0];
                sRds.AFMethod[1] = AFtemp.Byte[1];
            }
            else
            {
                if((sRds.AFMethod[0] != 0xFE) && (sRds.AFMethod[1] != 0xFE))
                {
                    if(((sRds.AFMethod[0] == AFtemp.Byte[0])
                        || (sRds.AFMethod[1] == AFtemp.Byte[0])
                        || (sRds.AFMethod[0] == AFtemp.Byte[1]) 
                        || (sRds.AFMethod[1] == AFtemp.Byte[1]))
                        && ((sRds.AFMethod[0] != AFtemp.Byte[0]) 
                            || (sRds.AFMethod[1] != AFtemp.Byte[1])))
                    {
                        sRds.F_AFMethodB = 1;    // get method B
                    }
                    sRds.AFMethod[0] = 0xFE;    // sign method comfirmed
                    sRds.AFMethod[1] = 0xFE;
                }
                
                // for Different Region
                if(sRds.F_AFMethodB && (AFtemp.Byte[0] > AFtemp.Byte[1]))
                {
                    AFtemp.Byte[0] = 0xFF;
                    AFtemp.Byte[1] = 0xFF;
                }

                for(i = 0; i < 25; i++)
                {
                    if((AFtemp.Byte[0] == sRds.AF[i]) && (AFtemp.Byte[0] != 0xFF))
                        AFtemp.Byte[0] = 0xFF;
                }

                if((AFtemp.Byte[0] < 205) && sRds.AFNum < 25)
                {
                    sRds.AF[sRds.AFNum] = AFtemp.Byte[0];
                    sRds.AFNum++;
                    sRds.AFTimer = 50;
                    sRds.F_GetNewAF = 1;
                }

                for(i = 0; i < 25; i++)
                {
                    if((AFtemp.Byte[1] == sRds.AF[i]) && (AFtemp.Byte[1] != 0xFF))
                        AFtemp.Byte[1] = 0xFF;
                }
                
                if((AFtemp.Byte[1] < 205) && (sRds.AFNum < 25))
                {
                    sRds.AF[sRds.AFNum] = AFtemp.Byte[1];
                    sRds.AFNum++;
                    sRds.AFTimer = 50;
                    sRds.F_GetNewAF = 1;
                }

                if((sRds.AFTimer == 0) && (sRds.AFNum > 1) && sRds.F_GetNewAF)
                {
                    sRds.F_GetNewAF = 0;
                    sRds.F_GetAFList = 1;
                }
            }            
        }
    }

#ifdef D_RDS_EON_ENABLE
    if(sRds.F_BlockB && (GroupVersion(G14A)) && sRds.F_BlockC)
    {
        Temp = (sRds.BlockLastB & 0x000F);
        
        switch(Temp)    // EON PS
        {
            case 0:
                sRds.EONPS[1] = (uint8_t)(sRds.BlockLastC & 0x00FF);
                sRds.EONPS[0] = (uint8_t)(sRds.BlockLastC >> 8);
                break;
                
            case 1:
                sRds.EONPS[3] = (uint8_t)(sRds.BlockLastC & 0x00FF);
                sRds.EONPS[2] = (uint8_t)(sRds.BlockLastC >> 8);
                break;
                
            case 2:
                sRds.EONPS[5] = (uint8_t)(sRds.BlockLastC & 0x00FF);
                sRds.EONPS[4] = (uint8_t)(sRds.BlockLastC >> 8);
                break;
                
            case 3:
                sRds.EONPS[7] = (uint8_t)(sRds.BlockLastC & 0x00FF);
                sRds.EONPS[6] = (uint8_t)(sRds.BlockLastC >> 8);
                break;
            
            case 4:    // EON AF
                AFtemp.Dbyte = sRds.BlockLastC;
                for(i = 0; i < 25; i++)
                {
                    if(AFtemp.Byte[0] == sRds.EONAF[i])
                        AFtemp.Byte[0] = 0xFF;
                    if(AFtemp.Byte[1] == sRds.EONAF[i])
                        AFtemp.Byte[1] = 0xFF;
                }
                if(AFtemp.Byte[0] < 205)
                {
                    sRds.EONAF[sRds.EONAFNum] = AFtemp.Byte[0];
                    if(sRds.EONAFNum < 24)
                        sRds.EONAFNum++;
                    sRds.EONAFTimer = 100;
                    sRds.F_GetNewEONAF = 1;
                }
                if(AFtemp.Byte[1] < 205)
                {
                    sRds.EONAF[sRds.EONAFNum] = AFtemp.Byte[1];
                    if(sRds.EONAFNum < 24)
                        sRds.EONAFNum++;
                    sRds.EONAFTimer = 100;
                    sRds.F_GetNewEONAF = 1;
                }
                if((sRds.EONAFTimer == 0) && (sRds.EONAFNum > 1) && sRds.F_GetNewEONAF)
                {
                    sRds.F_GetNewEONAF = 0;
                    sRds.F_GetEONAFList = 1;
                }
                break;

            case 13:    // EON TA
                if(sRds.BlockLastC & 0x0001)
                {
                    sRds.EONTA = 1;
                }
                else
                {
                    sRds.EONTA = 0;
                }

                if(sRds.EONTALast != sRds.EONTA)
                {
                    sRds.EONTALast = sRds.EONTA;
                    sRds.F_GetNewEONTA = 1;
                }
                break;
        }        
    }

    if(sRds.F_BlockB && GroupType(G14))    // EON TP
    {
        if(sRds.BlockLastB & 0x0010)
            sRds.EONTP = 1;
        else
            sRds.EONTP = 0;
        
        if(sRds.EONTPLast != sRds.EONTP)
        {
            sRds.EONTPLast = sRds.EONTP;
            sRds.F_GetNewEONTP = 1;
        }
    }

    if(sRds.F_BlockB && GroupVersion(G14B))    // EON TA
    {
        if(sRds.BlockLastB & 0x0008)
        {
            sRds.EONTA = 1;
        }
        else
        {
            sRds.EONTA = 0;
        }
        
        if(sRds.EONTALast != sRds.EONTA)
        {
            sRds.EONTALast = sRds.EONTA;
            sRds.F_GetNewEONTA = 1;
        }
    }

    if(sRds.F_BlockD && GroupType(G14)) // EON PI
    {
        sRds.EONPI = sRds.BlockLastD;
    }
#endif//D_RDS_EON_ENABLE

    if(GroupVersion(G2A) && sRds.F_BlockB && sRds.F_BlockC && sRds.F_BlockD)
    {
        if((sRds.BlockBQual <= 1) && (sRds.BlockCQual <= 1) && (sRds.BlockDQual <= 1))
        {
            // A B Flag Change,Clear All
            if(sRds.BlockLastB & 0x0010) //B
            {
                if(RT_TYPE_AB != sRds.RT_Type)
                {
                    Rds_RtClearBuff();
                    sRds.RT_Type = RT_TYPE_AB;
                }
            }
            else    //A
            {
                if(RT_TYPE_AA != sRds.RT_Type)
                {
                    Rds_RtClearBuff();
                    sRds.RT_Type = RT_TYPE_AA;
                }
            }
            i = (uint8_t)(sRds.BlockLastB & 0x000F);

            // Check difference 
            if((Rds_RtCheckDiff(sRds.RT[i*4],(uint8_t)(sRds.BlockLastC >> 8)))
                ||(Rds_RtCheckDiff(sRds.RT[i*4+1],(uint8_t)(sRds.BlockLastC & 0x00FF)))
                ||(Rds_RtCheckDiff(sRds.RT[i*4+2],(uint8_t)(sRds.BlockLastD >> 8)))
                ||(Rds_RtCheckDiff(sRds.RT[i*4+3],(uint8_t)(sRds.BlockLastD & 0x00FF))))
            {
                Rds_RtClearBuff();
            }

            sRds.RT[i*4] = (uint8_t)(sRds.BlockLastC >> 8);
            sRds.RT[i*4+1] = (uint8_t)(sRds.BlockLastC & 0x00FF);
            sRds.RT[i*4+2] = (uint8_t)(sRds.BlockLastD >> 8);
            sRds.RT[i*4+3] = (uint8_t)(sRds.BlockLastD & 0x00FF);

            if(0x0D == sRds.RT[i*4])
            {
                sRds.CntRT = i*4;
                sRds.RT[i*4] = 0x00;
            }
            else if(0x0D == sRds.RT[i*4+1]) 
            {
                sRds.CntRT = i*4+1;
                sRds.RT[i*4 + 1] = 0x00;
            }
            else if(0x0D == sRds.RT[i*4+2])
            {
                sRds.CntRT = i*4+2;
                sRds.RT[i*4 + 2] = 0x00;
            }
            else if(0x0D == sRds.RT[i*4+3])
            {
                sRds.CntRT = i*4+3;
                sRds.RT[i*4 + 3] = 0x00;
            }
            else if(60 == i*4)
                sRds.CntRT = 64;
 
            for(i = 0; i < 64/*sRds.CntRT*/; i++ )
            {
                if(0x00 == sRds.RT[i])
                {
                    break;
                }
            }
            if((0 != i) && (i != sRds.NumRT))
            {
                sRds.NumRT = i;
                sRds.F_GetNewRT = 1;
            }
        }
    }
    
    // RT 2B
    if(GroupVersion(G2B) && sRds.F_BlockB && sRds.F_BlockD)
    {
        if((sRds.BlockBQual <= 1) && (sRds.BlockDQual <= 1))
        {
            // A B Flag Change,Clear All
            if(sRds.BlockLastB & 0x0010) //B
            {
                if(RT_TYPE_BB != sRds.RT_Type)
                {
                    Rds_RtClearBuff();
                    sRds.RT_Type = RT_TYPE_BB;
                }
            }
            else    //A
            {
                if(RT_TYPE_BA != sRds.RT_Type)
                {
                    Rds_RtClearBuff();
                    sRds.RT_Type = RT_TYPE_BA;
                }
            }
            i = (uint8_t)(sRds.BlockLastB & 0x000F);

            // Check difference 
            if((Rds_RtCheckDiff(sRds.RT[i*2],(uint8_t)(sRds.BlockLastD >> 8)))
            ||(Rds_RtCheckDiff(sRds.RT[i*2+1],(uint8_t)(sRds.BlockLastD & 0x00FF))))
            {
                Rds_RtClearBuff();
            }

            sRds.RT[i*2] = (uint8_t)(sRds.BlockLastD >> 8);
            sRds.RT[i*2+1] = (uint8_t)(sRds.BlockLastD & 0x00FF);

            if(0x0D == sRds.RT[i*2])
                {
                sRds.CntRT = i*2;
                sRds.RT[i*2] = 0;
                }
            else if(0x0D == sRds.RT[i*2+1])
                {
                sRds.CntRT = i*2+1;
                sRds.RT[i*2 + 1] = 0;
                }
            else if(30 == i*2)
                sRds.CntRT = 32;

            for(i = 0; i < 32/*sRds.CntRT*/; i++ )
            {
                if(0x00 == sRds.RT[i])
                {
                    break;
                }
            }
            if((0 != i) && (i != sRds.NumRT))
            {
                sRds.NumRT = i;
                sRds.F_GetNewRT = 1;
            }
        }
    }

    if(sRds.F_GetNewTA || sRds.F_GetNewTP || sRds.F_GetNewEONTA || sRds.F_GetNewEONTP)
    {
        sRds.StationNoRdsTimer = 30;  // 3S
        sRds.F_StationWithRds = 1;
    }
}
/**********************************************************
 * @function    Rds_ResetAll
 * @brief      Reset all of Rds
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Rds_ResetAll(void)
{
    uint8_t i;
    uint8_t SubResult = SUBLAYER_DOING;
    uint8_t Result = SUBLAYER_DOING;

    //Filters ~~~
    if((Tuner_Api_GetBand() > TUNER_FM_END) 
        || (RDS_SET_OFF == Tuner_Api_GetRdsSetting()))
    {
        return (SUBLAYER_DONE);
    }

    //Reset RDS decoder to speed up the resynchronization
    //Maybe Not Need because of automatic restart of RDS after tuning...
    //SubResult = Rds_ResetDecoder();    // Reset decoder , re-get rds information

    //if(SUBLAYER_DONE == SubResult)
    {
#ifdef D_TEST_RDS_ERR_RATE
        sRds.RdsErrCnt = 0;
        sRds.RdsTotalCnt = 0;
        sRds.RdsBlockTotalCnt = 0;
#endif//D_TEST_RDS_ERR_RATE

        //Block&Group Related
        sRds.FetchBlockCtl = OPERATION_0;    
    #ifdef D_RDS_REGULAR_READ    
        sRds.RegularReadDelay = 0;
    #endif//D_RDS_REGULAR_READ
        sRds.BlockCnt = 0;
        sRds.LastBlockCnt = 0;
        sRds.F_GetBlockA = 0;
        sRds.F_GetBlockB = 0;
        sRds.F_GetBlockC = 0;
        sRds.F_GetBlockCp = 0;
        sRds.F_GetBlockD = 0;
        sRds.F_BlockA = 0;
        sRds.F_BlockB = 0;
        sRds.F_BlockC = 0;
        sRds.F_BlockCp = 0;
        sRds.F_BlockD = 0;
        sRds.F_GetOneGroup = 0;

        //Station with Rds Flags....
        sRds.bGotBlock = 0;     
        sRds.F_StationWithRds = 0;
        //Rds Signal Status: Valid Group Receivd
        sRds.MaxLevel = 0;
        sRds.Level = 0;
        
        //Pi Related
        sRds.Pi = 0;
        sRds.PiValid = 0;
        sRds.PISeekTimer = 0;
        sRds.PiBackup = 0;  
        sRds.F_GetNewPi = 0;

        //PTY Related
        sRds.Pty = 0;
        sRds.PtyValid = 0;
        sRds.PtyLast = 0;
        sRds.F_GetNewPty = 0;

        //TA TP Related
        sRds.TA = 0;
        sRds.TAValid = 0;
        sRds.TP = 0;
        sRds.TPValid = 0;
        sRds.F_GetNewTP = 0;
        sRds.F_GetNewTA = 0;
        sRds.EONTA = 0;
        sRds.EONTALast = 0;
        sRds.EONTP = 0;
        sRds.EONTPLast = 0;
        sRds.F_GetNewEONTP = 0;
        sRds.F_GetNewEONTA = 0;

        //PS Related
        sRds.F_PSGet0 = 0;
        sRds.F_PSGet1 = 0;
        sRds.F_PSGet2 = 0;
        sRds.F_PSGet3 = 0;
        sRds.F_PSExist = 0;
        sRds.F_GetNewPS = 0;
        sRds.PSCRC = 0;
        sRds.PSCRCTemp = 0;

        //CT Related..
        sRds.F_GetNewCT = 0;

        sRds.AfDisableTimer = 30;    //Disalbe AF Function for 3 Seconds after tune to a newly station

        
    #ifdef D_RDS_PI_SEEK
        if(sRds.F_PISeek)
            return;
    #endif//D_RDS_PI_SEEK
        
    
        if(!sRds.F_InEONTASwitch) // Need ?
        {
            for(i = 1; i < 25; i++)
            {
                sRds.AF[i] = 0xFF;
                sRds.AFDisable[i] = 0;
            }
            sRds.F_AFMethodB = 0;
            sRds.AFMethod[0] = 0xFF;
            sRds.AFMethod[1] = 0xFF;
        }
    
    #ifdef D_RDS_EON_ENABLE
        sRds.EONAFNum = 0;
        sRds.F_EONEnable = 1;
        for(i = 0; i < 25; i++)
        {
            sRds.EONAF[i] = 0xFF;
        }
    #endif//D_RDS_EON_ENABLE

        if((Tuner_Api_GetBand() > TUNER_FM_END)
            || (Tuner_Api_GetRegion() == REGION_JAPAN)
            || (Tuner_Api_GetFreq() < 6500))
        {
            sRds.AF[0] = 0xFF; // maybe cause 113hz ERROR
        }
        else        // If it is xx.x5, AF[0] ???
        {
            sRds.AF[0] = Rds_ChgFreq16To8(Tuner_Api_GetFreq());
        }
            
        if(!sRds.F_InEONTASwitch)   // Need ?
            sRds.AFNum = 1;

        sRds.F_GetNewAF = 0;
        sRds.F_GetAFList = 0;

        sRds.F_GetNewPS = 1;   // add by deefisher for clear usage
        sRds.F_GetNewPty = 1;
        sRds.F_GetNewTP = 1;
        sRds.F_GetNewTA = 1;        
        for(i = 0; i < 8; i++)
            sRds.PS[i] = ' ';

        sRds.AFCheckMode = AF_STEP_IDLE;
        sRds.AF_CF_CheckTimer = 10;
        sRds.BreakAfStep = 0;
        sRds.bDissChanged = 0;

        sRds.CfQualStep = 0;
        sRds.AfQualStep = 0;

        Rds_RtClearBuff();
        sRds.F_GetNewRT = 1;

        sRds.AFCheckDisable1S = 90;
        sRds.PISeek100MS = 600;

        Result = SUBLAYER_DONE;
    }

    return (Result);
}
/**********************************************************
 * @function    Rds_AfChkInit
 * @brief      Initial Related before Af Check
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Rds_AfChkInit(void)
{
    uint8_t Result = SUBLAYER_DOING;    

    //Reset RDS decoder to speed up the resynchronization
        //Maybe Not Need because of automatic restart of RDS after tuning...
    Result = Rds_ResetDecoder();    

    if(SUBLAYER_DONE == Result)
    {
    #ifdef D_TEST_RDS_ERR_RATE
        sRds.RdsErrCnt = 0;
        sRds.RdsTotalCnt = 0;
    #endif//D_TEST_RDS_ERR_RATE    

        sRds.BlockCnt = 0;
        sRds.LastBlockCnt = 0;
        sRds.F_GetBlockA = 0;
        sRds.F_GetBlockB = 0;
        sRds.F_GetBlockC = 0;
        sRds.F_GetBlockCp = 0;
        sRds.F_GetBlockD = 0;
        sRds.F_BlockA = 0;
        sRds.F_BlockB = 0;
        sRds.F_BlockC = 0;
        sRds.F_BlockCp = 0;
        sRds.F_BlockD = 0;            
        sRds.F_GetOneGroup = 0;
        
        sRds.F_GetNewPi = 0;
        sRds.Pi = 0;
        sRds.PiLast = 0;
        sRds.PiValid = 0;
        sRds.F_StationWithRds = 0;
        sRds.bGotBlock = 0;
    }

    return (Result);
}
/**********************************************************
 * @function    Rds_CalcMJD
 * @brief      Calculate MJD 
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_CalcMJD(void)
{
    uint8_t Yp,Mp,Y,M,D,K;

    Yp = (uint8_t)((sRds.MJD - 15078.2) / 365.25);
    Mp = (uint8_t)((sRds.MJD - 14956.1 - (uint16_t)(Yp*365.25))/30.6001);
    D = (uint8_t)(sRds.MJD-14956-(uint16_t)(Yp* 365.25)-(uint16_t)(Mp*30.6001));
    if((14 == Mp) || (15 == Mp))
    K = 1;
    else
    K = 0;
    Y = Yp + K;
    M = Mp - 1 - K*12;

    if(((Y+1900) < 2000) || ((Y+1900) > 2099))    // restrict year to 2000~2099
        sRds.Year = 0xFF;
    else
        sRds.Year=(Y+1900)%100;
    sRds.Month=M;
    sRds.Date = D;
}
/**********************************************************
 * @function    Rds_AfChange
 * @brief      Swap AFs Position, 
 *            Related to : AF,Smeter and Disabled Timer
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_AfChange(uint8_t Num1,uint8_t Num2)
{
    uint16_t Temp;

    //Swap AF Frequency
    Temp = sRds.AF[Num1];
    sRds.AF[Num1] = sRds.AF[Num2];
    sRds.AF[Num2] = Temp;

    //Swap AF Smeter
    Temp = sRds.AFSmeter[Num1];
    sRds.AFSmeter[Num1] = sRds.AFSmeter[Num2];
    sRds.AFSmeter[Num2] = Temp;

    //Swap AF Disable Timer
    Temp = sRds.AFDisable[Num1];
    sRds.AFDisable[Num1] = sRds.AFDisable[Num2];
    sRds.AFDisable[Num2] = Temp;
}
/**********************************************************
 * @function    Rds_AfSort
 * @brief      Fetch Block Datum
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_AfSort(uint8_t bg)
{
    uint8_t i,j;

    for(i = bg; i < (sRds.AFNum - 1); i++)
    {
        for(j = (sRds.AFNum-1); j > i; j--)
        {
            if(sRds.AFSmeter[j] > sRds.AFSmeter[j-1])
            {
                Rds_AfChange(j,j-1);
            }
        }
    }
}
/**********************************************************
 * @function    Rds_BreakAfCheck
 * @brief      Break AF Check Actions:Use action will break 
 *            currently af steps
 * @param      None                
 * @retval     Result
 **********************************************************/
uint8_t Rds_BreakAfCheck(void)
{
    uint8_t Result = SUBLAYER_DOING;
    uint8_t SubResult = SUBLAYER_DOING;

    //Filters to Ignore this function...
    if((AF_STEP_IDLE == sRds.AFCheckMode) || (RDS_SET_OFF == Tuner_Api_GetRdsSetting())
        ||(Tuner_Api_GetBand() > TUNER_FM_END))
    {
        return (SUBLAYER_DONE);
    }
    
    switch(sRds.BreakAfStep)
    {
        case OPERATION_0:    // break out, go back to currently frequency    
            sRds.AFCheckMode = AF_STEP_CLOSING;
            SubResult = Rds_AF_Jump(sRds.AF[0]);
            if(SUBLAYER_DONE == SubResult)
            {
                sRds.BreakAfStep++;
            }
            break;

        // Switch DISS back to AUTO
        case OPERATION_1:
            if(sRds.bDissChanged == 1)
            {
                SubResult = Tuner_SetBw(0,0);    // Set DISS to AUto
            }
            else
            {
                SubResult = SUBLAYER_DONE;
            }
            if(SUBLAYER_DONE == SubResult)
            {
                sRds.bDissChanged = 0;    
                sRds.BreakAfStep++;
            }
            break;
            
        case OPERATION_2:
            SubResult = Rds_AfChkInit();
            if(SUBLAYER_DONE == SubResult)
            {
                sRds.BreakAfStep++;
            }
            break;

        case OPERATION_3:    // Check Unmute Done, Exit AF Break
            Rds_Mute(MUTE_OFF);
            sRds.AFCheckMode = AF_STEP_IDLE;
            sRds.BreakAfStep = 0;
            Result = SUBLAYER_DONE;
            break;
    }

    //Error Occurs!
    if(SubResult > SUBLAYER_DONE)
    {
        Result = SubResult;
    }
    
    return (Result);
}
/**********************************************************
 * @function    Rds_BreakAfCheck
 * @brief      Break AF Check Actions
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_BreakAFSearch(void)
{
    uint8_t i;
    
    if((sRds.AFCheckMode == AF_STEP_SEARCH_START)
        ||(sRds.AFCheckMode == AF_STEP_SEARCH_RDS)
        || (sRds.AFCheckMode == AF_STEP_SEARCH_PI))
    {
        sRds.AFCheckMode = AF_STEP_IDLE;
        
        for(i=0;i<25;i++)
        {
            if(sRds.AFFreqBackup==sRds.AF[i])
            {
                Rds_AfChange(0,i);
                break;
            }
        }
    }
}
/**********************************************************
 * @function    Rds_BreakAfCheck
 * @brief      Break AF Check Actions
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_AF(void)
{
    uint8_t Result;
    uint8_t i;

    //Check Station whether a Rds Station.....
    if(NotRdsStation)
    {
        if((0 == sRds.StationNoRdsTimer) && sRds.F_StationWithRds)
        {
            sRds.F_StationWithRds = 0;
            Rds_ClearTaFlags();
            Rds_ClearEonTaFlags();
        }
    }
    else
    {
        sRds.StationNoRdsTimer = 30;  // 3S
        sRds.F_StationWithRds = 1;
    }

    //CF Get&Check
    if(AF_SET_ON == Tuner_Api_GetAfSetting())
    {
        if(Tuner_Api_GetSeekState())
            return;
        
        //AF Function Delay Timer: If Timer is Set, Do Nothing
        //
        if(sRds.AfDisableTimer > 0)//|| (sRds.AFCheckMode = AF_STEP_CLOSING))
        {
            //Rds_BreakAfCheck();  // Not Used??!!!
        }
        else if((Tuner_Api_GetFreq() >= 8750) && (Tuner_Api_GetFreq() <= 10800)
            && (AF_STEP_IDLE == sRds.AFCheckMode) && (0 == sRds.AF_CF_CheckTimer))
        {                    
            sRds.BreakAfStep = 0;        

            Result = Rds_GetCFQual(4);
            if(SUBLAYER_DONE == Result)
            {
                sRds.AFSmeter[0] = Tuner_Api_GetCfLev();  
                sRds.CF_detuning = Tuner_Api_GetCfFof(); 
                sRds.CF_Adjchannel = Tuner_Api_GetCfAdj(); 
                sRds.CF_Multipath = Tuner_Api_GetCfMul();

                if((sRds.AFSmeter[0] < Smeter_DB40)
                    || (sRds.CF_Adjchannel > Adjchannel_TH)
                    || (sRds.CF_detuning > Detuning_TH)
                    || (sRds.CF_Multipath > Multipath_TH))
                {
                    if(sRds.AFSmeter[0] < Smeter_DB20)
                    {
                        sRds.AFCheckStartTimerSet = 10; // 2S Once for fast Check List;
                        sRds.AFCheckWaitTimerSet = 10; //100ms Once for fast Check Frequency;
                        sRds.Delta = (Smeter_DB4 - 1);    //-1 is because the smeter is not so linear to fs
                        if(sRds.AFCheckListDelay > sRds.AFCheckStartTimerSet)//speed up to activate  AF check when reception turn worse.
                            sRds.AFCheckListDelay = sRds.AFCheckStartTimerSet;
                        if(sRds.AFCheckWaitTimer > sRds.AFCheckWaitTimerSet)
                            sRds.AFCheckWaitTimer = sRds.AFCheckWaitTimerSet;
                    }
                    else 
                    {
                        sRds.AFCheckStartTimerSet = 80; // 8S Once for Slow Check List
                        sRds.AFCheckWaitTimerSet = 100; // 1S Once For Slow Check Frequency
                        sRds.Delta = (Smeter_DB4 * 2);
                    }
                    
                    if(sRds.AFCheckMode == AF_STEP_IDLE)
                    {
                        if(sRds.AFCheckWaitTimerSet == 0xFF)  //1 never come into
                            sRds.AFCheckMode = AF_STEP_SEARCH_START;
                        else if(sRds.AFCheckListDelay == 0)
                            sRds.AFCheckMode = AF_STEP_CHK_START;
                    }
                }
                else if((sRds.AFSmeter[0] > Smeter_DB40)
                    && (sRds.AFNum > 1)
                    && (!sRds.F_StationWithRds)
                    && (0 == sRds.AFSearchWaitTimer))
                {
                    Rds_SetAfSearch();
                    sRds.AFSearchWaitTimer = 50;
                }

                sRds.AF_CF_CheckTimer = 10;
                sRds.BreakAfStep = 0;
            }
        }
    }

    //AF Check Switch Search
    switch(sRds.AFCheckMode)
    {
        case AF_STEP_IDLE:
        case AF_STEP_CLOSING:
            break;
            
        case AF_STEP_CHK_START:
            if(sRds.AFNum > 1)
            {
                sRds.AFCheckPoint = 1;    
            #ifdef D_AF_FILTER                
                if(sRds.AF[sRds.AFCheckPoint] > 205)    
                {
                    for(i = 1; i < 24; i++)
                    {
                        sRds.AF[i] = sRds.AF[i + 1];         
                    }
                    sRds.AF[24] = 0xFF;    
                    sRds.AFNum--;
                    sRds.AFCheckMode = AF_STEP_IDLE;
                    break;
                }
            #endif        
                sRds.AFCheckMode = AF_STEP_CHK_GETCF;
                sTuner.GetCfQualCtl = 0; // Clear Get CF Quality Step
            }
            else
            {
                sRds.AFCheckMode=AF_STEP_IDLE;
            }
            break;
            
        case AF_STEP_CHK_GETCF:    
            //Check Disable....
            if(sRds.AFDisable[sRds.AFCheckPoint] > 0)
            {
                sRds.AFCheckMode = AF_STEP_CHK_WAIT;
                break;
            }
            
        #ifdef D_AF_FILTER
            if(sRds.AF[sRds.AFCheckPoint] > 205)     // new added for 0xFF AF switch by deefisher@20110617
            {
                for(i = sRds.AFCheckPoint; i < 24; i++)
                {
                    sRds.AF[i] = sRds.AF[i + 1];         
                }
                sRds.AF[24] = 0xFF;    
                sRds.AFNum--;
                sRds.AFCheckMode = AF_STEP_IDLE;
                break;
            }
        #endif    
        
            Result = Rds_GetCFQual(4);
            if(SUBLAYER_DONE == Result)
            {
                sRds.AFSmeter[0] = Tuner_Api_GetCfLev();  
                sRds.CF_detuning = Tuner_Api_GetCfFof(); 
                sRds.CF_Adjchannel = Tuner_Api_GetCfAdj(); 
                sRds.CF_Multipath = Tuner_Api_GetCfMul();

                sRds.AFCheckMode = AF_STEP_CHK_GETAF;    
                //Clear AF Qual Get Control
                sRds.AfQualStep = 0;
            }
            break;
        
        case AF_STEP_CHK_GETAF:  // CF compare with AF    
            Result = Rds_GetAfQual((sRds.AF[sRds.AFCheckPoint]*10 + 8750),2);
            if(SUBLAYER_DONE == Result)
            {
                sRds.AFSmeter[sRds.AFCheckPoint] = Tuner_Api_GetAfLev();
                sRds.AF_detuning = Tuner_Api_GetAfFof();
                sRds.AF_Adjchannel = Tuner_Api_GetAfAdj();
                sRds.AF_Multipath = Tuner_Api_GetAfMul();    
                sRds.AFCheckMode = AF_STEP_CHK_CMP;    
            }
            break;
            
        case AF_STEP_CHK_CMP: //Compare CF and AF    
            if(((sRds.AFSmeter[0] + sRds.Delta) < sRds.AFSmeter[sRds.AFCheckPoint])
                &&(sRds.AFSmeter[sRds.AFCheckPoint] > Smeter_DB20)
                &&(sRds.AF_detuning < Detuning_TH)
            #ifdef D_STRICT_AF_CHECK
                &&(sRds.AF_Adjchannel < Adjchannel_TH)
                &&(sRds.AF_Multipath < Multipath_TH)
            #endif
                )
            {
                sRds.AFCheckMode = AF_STEP_CHK_REGETAF;
                sRds.AfQualStep = 0; //Clear AF Qual Get Control
            }
            else
            {
                sRds.AFCheckMode = AF_STEP_CHK_WAIT;
                sRds.AFCheckWaitTimer = sRds.AFCheckWaitTimerSet;
            }
            break;

        case AF_STEP_CHK_REGETAF:
            if(SUBLAYER_DONE == Rds_GetAfQual((sRds.AF[sRds.AFCheckPoint]*10 + 8750),3))
            {
                sRds.AFSmeter[sRds.AFCheckPoint] = Tuner_Api_GetAfLev();
                sRds.AF_detuning = Tuner_Api_GetAfFof();
                sRds.AF_Adjchannel = Tuner_Api_GetAfAdj();
                sRds.AF_Multipath = Tuner_Api_GetAfMul();    
            
                if((sRds.AFSmeter[0]+sRds.Delta < sRds.AFSmeter[sRds.AFCheckPoint])
                    &&(sRds.AFSmeter[sRds.AFCheckPoint] > Smeter_DB20)
                    &&(sRds.AF_detuning < Detuning_TH)
                    &&(sRds.AF_Adjchannel < Adjchannel_TH)
                    &&(sRds.AF_Multipath < Multipath_TH))
                {
                    sRds.AFCheckMode = AF_STEP_CHK_SWITCH;
                    sRds.AFSwitchStep = 0;
                    sRds.AFSwitchDelay = 0;
                }
                else
                {
                    sRds.AFCheckMode = AF_STEP_CHK_WAIT;
                    sRds.AFCheckWaitTimer = sRds.AFCheckWaitTimerSet;
                }
            }
            break;

        case AF_STEP_CHK_SWITCH:
            Result = Rds_AfSwitch(0);
            if(SUBLAYER_DONE == Result)    
            {
                sRds.AFSwitchStep = 0;
                sRds.AFCheckMode = AF_STEP_CHK_RDS;
            }
            break;

        case AF_STEP_CHK_RDS:
            if(sRds.bGotBlock)
            {
                sRds.AFCheckMode = AF_STEP_CHK_PI;
                if(sRds.AFSmeter[sRds.AFCheckPoint] > Smeter_DB40)
                    sRds.AFCheckWaitTimer = 30;
                else
                    sRds.AFCheckWaitTimer = 60;
                break;
            }
            if(0 == sRds.AFCheckWaitTimer)
            {
                sRds.AFCheckMode = AF_STEP_CHK_BACK;
            }
            break;

        case AF_STEP_CHK_PI:  
            if((((sRds.Pi == sRds.PiBackup) && sRds.F_REGEnable)
                ||(((sRds.Pi & 0x00FF) == (sRds.PiBackup & 0x00FF)) && (!sRds.F_REGEnable)))
                && (0 != sRds.Pi))  
            {
                Rds_Mute(MUTE_OFF);
                Rds_AfChange(0,sRds.AFCheckPoint);
                sRds.AFCheckMode = AF_STEP_CHK_END;
                break;    
            }
            
            if(0 == sRds.AFCheckWaitTimer)
            {
                sRds.AFCheckMode = AF_STEP_CHK_BACK;
            }
            break;                

        case AF_STEP_CHK_BACK:
            Result = Rds_AfSwitch(1);
            if(SUBLAYER_DONE == Result)    
            {
                sRds.AFCheckMode = AF_STEP_CHK_WAIT;
                sRds.AFCheckWaitTimer = sRds.AFCheckWaitTimerSet;
                sRds.AFSwitchStep = 0;
            }
            break;
            
        case AF_STEP_CHK_WAIT:
            if(sRds.AFCheckWaitTimer > 0)
                break;
            if((sRds.AFCheckPoint < (sRds.AFNum-1)) && (sRds.AFNum > 1))
            {
                sRds.AFCheckPoint++;
            #ifdef D_DISA_DUMMY_PI
                if(sRds.AFDisable[sRds.AFCheckPoint])
                {
                    sRds.AFCheckMode = AF_STEP_CHK_WAIT;
                    break;
                }
                else
            #endif
                sRds.AFCheckMode = AF_STEP_CHK_GETCF;
            }
            else
            {
                sRds.AFCheckMode = AF_STEP_CHK_END;
            }
            break;

        case AF_STEP_CHK_END:
            if(sRds.AFNum > 1)
            {
                Rds_AfSort(1);
                if(sRds.bDissChanged == 1)    
                {
                    //Tuner_SetBw(0,0);    // Set DISS to AUto
                }
                sRds.bDissChanged = 0;
                
                // add by deefisher for display usage
                //Radio_UpdateMenu();      //////////////////////////////////////
                sTunerDat.sInfo.CurrentFreq = sRds.AF[0]*10+8750;
                sRds.AFSearchWaitTimer = 30;
            }
            sRds.AFCheckListDelay = sRds.AFCheckStartTimerSet;
            sRds.AFCheckMode = AF_STEP_IDLE;
            break;

        case AF_STEP_SEARCH_START:            
            if(sRds.AFNum > 1)
            {
                Rds_Mute(MUTE_ON);
                sRds.AFFreqBackup = sRds.AF[0];
                sRds.AFCheckWaitTimer = 7;  //15ms delay
                sRds.AFCheckMode = AF_STEP_SEARCH_QUEUE;
                sRds.AFCheckPoint=0;

                //Clear AF Qual Get Control
                sRds.AfQualStep = 0;
            }
            else
            {
                sRds.AFCheckMode = AF_STEP_IDLE;
            }
            break;

        case AF_STEP_SEARCH_QUEUE:
            if(sRds.AFCheckWaitTimer > 0)
                break;
            
            Result = Rds_GetAfQual((sRds.AF[sRds.AFCheckPoint]*10 + 8750),1);
            if(SUBLAYER_DONE == Result)
            {
                sRds.AFSmeter[sRds.AFCheckPoint] = Tuner_Api_GetAfLev();
                //Clear AF Qual Get Control
                sRds.AfQualStep = 0;
                sRds.AFCheckPoint++;
            }

            if(sRds.AFCheckPoint >= sRds.AFNum)
            {
                Rds_AfSort(0);
                sRds.AFCheckPoint = 0;
                sRds.AFCheckMode = AF_STEP_SEARCH_CHK;
            }
            break;

        case AF_STEP_SEARCH_CHK:
            if(sRds.AFCheckPoint >= sRds.AFNum)
            {
                for(i = 0; i < 25; i++)
                {
                    if(sRds.AFFreqBackup == sRds.AF[i])
                    {
                        Rds_AfChange(0,i);  // Get back Original Frequency
                        break;
                    }
                }
                sRds.AFCheckMode = AF_STEP_CHK_END;
                Rds_Mute(MUTE_OFF);
                break;
            }
            
            Result = Rds_GetAfQual((sRds.AF[sRds.AFCheckPoint]*10 + 8750),1);
            if(SUBLAYER_DONE == Result)
            {
                sRds.AFSmeter[sRds.AFCheckPoint] = Tuner_Api_GetAfLev();
                if((sRds.AFSmeter[sRds.AFCheckPoint] > Smeter_DB20) 
                    && (sRds.AF_detuning < Detuning_TH))
                {
                    sRds.AFCheckMode = AF_STEP_SEARCH_SWITCH;
                }
                else
                {
                    sRds.AFCheckPoint++;
                }
            }
            break;

        case AF_STEP_SEARCH_SWITCH:
            Result = Rds_AfSwitch(0);
            if(SUBLAYER_DONE == Result)
            {
                sRds.AFCheckMode = AF_STEP_SEARCH_RDS;
            }
            break;

        case AF_STEP_SEARCH_RDS:
            if(sRds.bGotBlock)
            {
                sRds.AFCheckMode=AF_STEP_SEARCH_PI;
                sRds.AFCheckWaitTimer = 50;/// audiostar debug
                break;
            }
            if(sRds.AFCheckWaitTimer == 0)
            {
                sRds.AFCheckPoint++;
                sRds.AFCheckMode = AF_STEP_SEARCH_CHK;
            }
            break;

        case AF_STEP_SEARCH_PI:
            if((((sRds.Pi == sRds.PiBackup) && sRds.F_REGEnable)
                ||(((sRds.Pi & 0x00FF) == (sRds.PiBackup & 0x00FF)) && (!sRds.F_REGEnable)))
                && (0 != sRds.Pi))
            {
                Rds_Mute(MUTE_OFF);
                Rds_AfChange(0,sRds.AFCheckPoint);
                sRds.AFCheckMode = AF_STEP_CHK_END;
                break;
            }
            
            if(sRds.AFCheckWaitTimer==0)
            {
                sRds.AFCheckPoint++;
                sRds.AFCheckMode = AF_STEP_SEARCH_CHK;
            }
            break;
    }
}
/**********************************************************
 * @function    Rds_ClearTaFlags
 * @brief      Clear TA Related Parameter
 * @param      None                
 * @retval     Result
 **********************************************************/
void Rds_ClearTaFlags(void)
{
    sRds.TA = 0;
    sRds.TAValid = 0;
    sRds.TP = 0;
    sRds.TPValid = 0;
    sRds.F_GetNewTP = 1;
    sRds.F_GetNewTA = 1;
}
/**********************************************************
 * @function    Rds_ClearEonTaFlags
 * @brief      Clear EON TA Related Parameters
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_ClearEonTaFlags(void)
{
    sRds.EONTA = 0;
    sRds.EONTALast = 0;
    sRds.EONTP = 0;
    sRds.EONTPLast = 0;
    sRds.F_GetNewEONTP = 1;
    sRds.F_GetNewEONTA = 1;
}
/**********************************************************
 * @function    Rds_Mute
 * @brief      Clear EON TA Related Parameters
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_Mute(uint8_t Type)
{
}
/**********************************************************
 * @function    Rds_SetAfSearch
 * @brief      Clear EON TA Related Parameters
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_SetAfSearch(void)
{
    //if(RDS.AFSearchWaitTimer>0)return;
    sRds.AFCheckStartTimerSet = 0;
    sRds.AFCheckWaitTimerSet = 0xFF;
    sRds.AFCheckMode = AF_STEP_SEARCH_START;
    sRds.AfDisableTimer = 0;    //Clear AF Disable Timer
    //Rds_Mute(MUTE_ON);
    sRds.AFSearchWaitTimer = 20;
}
/**********************************************************
 * @function    Rds_Timer1s
 * @brief      Rds Timer: 1S Tick
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_Timer1s(void)
{
    uint8_t i;
    
    for(i = 1; i < 25; i++)
    {
        if(sRds.AFDisable[i] > 0)
            sRds.AFDisable[i]--;
    }
    
    sRds.MaxLevel = sRds.Level;
    sRds.Level = 0;    
}
/**********************************************************
 * @function    Rds_Timer10ms
 * @brief      Rds Timer: 10ms Tick
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_Timer10ms(void)
{
    if(sRds.AFTimer)sRds.AFTimer--;
    if(sRds.AF_CF_CheckTimer)sRds.AF_CF_CheckTimer--;
#ifdef D_RDS_EON_ENABLE
    if(sRds.EONAFTimer)sRds.EONAFTimer--;
#endif//D_RDS_EON_ENABLE
    if(sRds.AFCheckWaitTimer)sRds.AFCheckWaitTimer--;
}
/**********************************************************
 * @function    Rds_Timer100ms
 * @brief      Rds Timer: 100ms Tick
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_Timer100ms(void)
{
    if(sRds.AfDisableTimer)    sRds.AfDisableTimer--;
    if(sRds.AFSearchWaitTimer)sRds.AFSearchWaitTimer--;
    if(sRds.StationNoRdsTimer)sRds.StationNoRdsTimer--;
    if(sRds.AFCheckListDelay)sRds.AFCheckListDelay--;    
    if(sRds.PISeekTimer > 1)
    {
        sRds.PISeekTimer--;
    }

    if(sRds.InTADelayTimer)sRds.InTADelayTimer--;
    if(sRds.EnterTADelayTimer)sRds.EnterTADelayTimer--;
    if(sRds.EnterEONTADelayTimer)sRds.EnterEONTADelayTimer--;
    if(sRds.TAWaitAFCheckTimer)sRds.TAWaitAFCheckTimer--;
}
/**********************************************************
 * @function    Rds_SetAfSearch
 * @brief      Clear EON TA Related Parameters
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_SwitchToTa(void)
{
    if(sRds.F_InTASwitch)
        return;
    
    sRds.F_InTASwitch = 1;
    sRds.InTADelayTimer = 10;
}
/**********************************************************
 * @function    Rds_SetAfSearch
 * @brief      Clear EON TA Related Parameters
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_TaSwitchBack(void)
{
    if(!sRds.F_InTASwitch)
        return;
    
    sRds.F_InTASwitch = 0;
    Rds_ClearTaFlags();
}
#if 0
/**********************************************************
 * @function    Rds_SetAfSearch
 * @brief      Clear EON TA Related Parameters
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_SwitchToEONTa(void)
{
    uint8_t i;
    
    if(sRds.F_InEONTASwitch)
        return;
    
    sRds.F_InEONTASwitch = 1;
    sRds.InTADelayTimer = 10;
    
    for(i = 0; i < 25; i++)
    {
        sRds.EONAFBackup[i] = sRds.AF[i];
        sRds.AF[i] = sRds.EONAF[i];
    }
    
    for(i = 0; i < 8; i++)
    {
        sRds.EONPSBackup[i] = sRds.PS[i];
        sRds.PS[i] = sRds.EONPS[i];
    }
    sRds.EONPIBackup = sRds.PI;
    sRds.PI = sRds.EONPI;
    sRds.EONAFNumBackup = sRds.AFNum;
    sRds.AFNum = sRds.EONAFNum;    
    
    sRds.PILast = sRds.PI;
    sRds.PIBackup = sRds.PI;

    //Rds_Mute(ENABLE);   // check it 
    Rds_Jump(sRds.AF[0]);
    Rds_SetAFSearch();
    Rds_ClearEonTaFlags();
    Rds_ClearTaFlags();
    Radio_UpdateMenu();    
}
/**********************************************************
 * @function    Rds_SetAfSearch
 * @brief      Clear EON TA Related Parameters
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_EONTaSwitchBack(void)
{
    unsigned char i;
    
    if(!sRds.F_InEONTASwitch)
        return;
    
    sRds.F_InEONTASwitch = 0;
    sRds.InTADelayTimer = 20;
    for(i = 0; i < 25; i++)
    {
        sRds.AF[i] = sRds.EONAFBackup[i];
    }
    for(i = 0; i < 8; i++)
    {
        sRds.PS[i] = sRds.EONPSBackup[i];
    }
    sRds.PI = sRds.EONPIBackup;
    sRds.AFNum = sRds.EONAFNumBackup;
    
    sRds.PILast=sRds.PI;
    sRds.PIBackup=sRds.PI;
    
    //Rds_Mute(ENABLE);
    Rds_AFJump(sRds.AF[0]);
    Rds_SetAFSearch();
    Rds_ClearEonTaFlags();
    Rds_ClearTaFlags();
    Radio_UpdateMenu();    
}
#endif
/**********************************************************
 * @function    Rds_Main
 * @brief      Rds Main Manager
 * @param      None                
 * @retval     Result
 **********************************************************/    
void Rds_Main(void)
{
    //Filter: states that no need rds disposal
    if((RDS_SET_OFF == (Tuner_Api_GetRdsSetting())) || ((Tuner_Api_GetBand()) > TUNER_FM_END))
    {
        return;
    }

    //Filter:
    if(TUNER_SYS_RUN != TunerGetSysState())
    {
        return;
    }  
 
    Rds_FetchBlockDat();    //Fetch Datum
    Rds_AnalyseData(); //Datum Analyse
    Rds_AF(); //Execute AF
}




