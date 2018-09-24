/**********************************************************
 * @file        Rds_Decoder_Dirana3.h
 * @purpose    
 * @version    0.01
 * @date        26. Mar. 2012
 * @author    Deefisher.Lyu
 * @brief        
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          26.Mar.2012        v0.01        created
 *  
  **********************************************************/
#ifndef RDS_FUNC_H
#define RDS_FUNC_H

#ifdef RDS_FUNC_C
#define EXTERN
#else
#define EXTERN extern 
#endif//RDS_FUNC_C


// According to the Mcu, high/low maybe change
#define U_HIGH_BYTE    1
#define U_LOW_BYTE    0


typedef enum af_check_step_enum
{
    AF_STEP_IDLE = 0,
    AF_STEP_CHK_START,    
    AF_STEP_CHK_GETCF,    
    AF_STEP_CHK_GETAF,
    AF_STEP_CHK_CMP,
    AF_STEP_CHK_REGETAF,
    AF_STEP_CHK_SWITCH,    
    AF_STEP_CHK_RDS,
    AF_STEP_CHK_PI,
    AF_STEP_CHK_BACK,
    AF_STEP_CHK_WAIT,       //10
    AF_STEP_CHK_END,
    AF_STEP_SEARCH_START,
    AF_STEP_SEARCH_QUEUE,
    AF_STEP_SEARCH_CHK,
    AF_STEP_SEARCH_SWITCH,
    AF_STEP_SEARCH_RDS,
    AF_STEP_SEARCH_PI,                
    AF_STEP_CLOSING,                    
}AF_STEP_ENUM;


#define AFS_NUM_START    224        // 0 AFs
#define AFS_NUM_END    249        // 25 AFs    
#define AFS_NUM_MASK    224


#define AF_AM_TYPE  250    //Signs  LF/MF Frequency Follow




typedef union u8_u16_union
{
    uint8_t Byte[2];   
    uint16_t Dbyte;
}U8_U16_UNION;

typedef struct EONMapStruct
{
    uint16_t ONPI;
    uint8_t EONMapNum;
    uint8_t TNFreq[10];
    uint8_t ONFreq[10];
}EONMapT;

typedef struct rds_struct 
{
#ifdef D_TEST_RDS_ERR_RATE
    uint16_t RdsErrCnt;        //Recieved Error Rds Block 
    uint16_t RdsTotalCnt;        //Recieved Total Rds Block
    uint16_t RdsBlockTotalCnt;
#endif//D_TEST_RDS_ERR_RATE

    //Control Parameters
    uint8_t FetchBlockCtl;    //Fetch Rds Block Step...

    //Block Parameters
    uint16_t BlockA;
    uint16_t BlockB;
    uint16_t BlockC;
    uint16_t BlockCp;
    uint16_t BlockD;
    uint16_t BlockLastA;
    uint16_t BlockLastB;
    uint16_t BlockLastC;
    uint16_t BlockLastCp;
    uint16_t BlockLastD;
    uint8_t BlockCnt;
    uint8_t LastBlockCnt;
    uint8_t BlockAQual;        //Block Quality: judge Rds Error Byte...
    uint8_t BlockBQual;
    uint8_t BlockCQual;
    uint8_t BlockDQual;
    bit_t F_GetOneGroup:1;
    bit_t F_GetBlockA:1;
    bit_t F_GetBlockB:1;
    bit_t F_GetBlockC:1;
    bit_t F_GetBlockCp:1;
    bit_t F_GetBlockD:1;
    bit_t F_BlockA:1;
    bit_t F_BlockB:1;
    bit_t F_BlockC:1;
    bit_t F_BlockCp:1;
    bit_t F_BlockD:1;
    bit_t bGotBlock:1;    //Sign: Got a Valid Rds Block at least...
    bit_t F_StationWithRds:1;    //Sign:Station whether with rds information
    uint8_t StationNoRdsTimer; //Timer to check a station not received  rds information 
    uint8_t Level;        //Sign: Rds Signal Level, Number of received valid rds group...
    uint8_t MaxLevel;
    uint8_t Group;    //Currently Got Group Type...

    //PI Related Parameters
    uint16_t Pi;
    uint16_t PiLast;
    uint16_t PiValid;
    uint16_t PiFast;// First Pi
    uint16_t PiBackup;
    uint16_t PISeekBackup;
    uint16_t PISeekTimer;

    //PTY Parameter
    uint8_t Pty;
    uint8_t PtyValid;
    uint8_t PtyLast;
    
    //TA TP
    bit_t TP:1;
    bit_t TPValid:1;
    bit_t TA:1;
    bit_t TAValid:1;
    bit_t EONTP:1;
    bit_t EONTPLast:1;
    bit_t EONTA:1;
    bit_t EONTALast:1;

    //Time Date
    uint8_t TimeHour;
    uint8_t TimeMin;
    uint32_t MJD;
    uint8_t Year;
    uint8_t Month;
    uint8_t Date;
    uint8_t Week;


    //PS...
    uint8_t PS[8];
    uint16_t PSCRC;
    uint16_t PSCRCTemp;

    //AF Related...
    uint8_t AF[25];
    uint8_t AFNum;

    uint16_t FreqAF;    //temporary af switched frequency

    uint8_t AFFreqBackup;
    
    uint8_t AFTimer;
    uint8_t AFSwitchStep;
    uint8_t AFSwitchDelay;
    uint8_t AFCheckMode;
    uint8_t AFCheckPoint;    //Currently AFs Check point... 
    uint8_t AFCheckListDelay;    // Delay Between two List
    uint8_t AFCheckStartTimerSet;
    uint8_t AFCheckWaitTimer;    // Delay Between two frequency
    uint8_t AFCheckWaitTimerSet;
    uint8_t AFSearchWaitTimer;

    uint8_t AfDisableTimer;    //Timer for :Disable AF Function temporary...
    uint8_t AFCheckDisable1S;
    uint16_t PISeek100MS;

    uint8_t AFSmeterLevel;
    uint8_t AF_CF_CheckTimer;   // check current freq every 100MS
    uint8_t AFSmeter[25];
    
    
    uint8_t CF_detuning;
    uint8_t CF_Multipath;
    uint8_t CF_Adjchannel;

    uint8_t AF_detuning;
    uint8_t AF_Multipath;
    uint8_t AF_Adjchannel;

    //uint8_t AFQuality[25];
    uint16_t AFDisable[25];
    uint8_t AFMethod[2];
    


    uint8_t Delta;

    uint8_t InTADelayTimer;
    uint8_t TAWaitAFCheckTimer;
    uint8_t EnterTADelayTimer;
    uint8_t EnterEONTADelayTimer;

    
    uint8_t AF_CF_CheckStep; //Check Currently Frequency Step
    uint8_t BreakAfStep;

    uint8_t CfQualStep;    //Get CF Quality Step
    uint8_t CfQualNum;    // Get Cf Qulity Number

    uint8_t AfQualStep;    //Get AF Quality Step
    uint8_t AfQualNum;    // Get Af Qulity Number
    uint8_t AfQualDelay;
    uint8_t AfQualCnt;
    
#ifdef D_RDS_EON_ENABLE
    uint8_t    EONAF[25];
    uint8_t    EONAFNum;
    uint8_t    EONAFTimer;
    uint16_t EONPI;
    uint8_t EONPS[8];
    
    uint8_t    EONAFBackup[25];
    EONMapT EONMapList[5];
    uint8_t EONPINum;
    uint8_t    EONAFNumBackup;
    uint8_t    EONAFTimerBackup;
    uint16_t EONPIBackup;
    uint8_t EONPSBackup[8];
#endif//D_RDS_EON_ENABLE

    uint8_t RegularReadDelay;        //Regular Read Delay
    
    bit_t F_AFMethodB:1;

    bit_t F_GetNewPi:1;
    bit_t F_GetNewPty:1;
    bit_t F_GetNewTP:1;
    bit_t F_GetNewTA:1;
    bit_t F_GetNewEONTP:1;
    bit_t F_GetNewEONTA:1;
    bit_t F_PSGet0:1;
    bit_t F_PSGet1:1;
    bit_t F_PSGet2:1;
    bit_t F_PSGet3:1;
    bit_t F_PSExist:1;
    bit_t F_GetNewPS:1;
    bit_t F_GetNewCT:1;


    bit_t F_GetNewAF:1;
    bit_t F_GetAFList:1;
    bit_t F_GetEONAFList:1;
    bit_t F_GetEONMapList:1;
    bit_t F_GetNewRT:1;
    bit_t F_GetRTEmpty:1;
    bit_t F_RTABFlag:1;
    bit_t F_GetNewEONAF:1;
    bit_t F_REGEnable:1;
    bit_t F_EONEnable:1;
    bit_t bDataAvailable:1;
    bit_t F_PIMuteEnable:1;
    bit_t F_PISeek:1;

    bit_t F_InEONTASwitch:1;
    bit_t Sing_Flag:1;
    bit_t rds_remain:1;
    bit_t bDissChanged:1;    
    bit_t F_InTASwitch:1;
    
    uint8_t RT[64];
    uint8_t NumRT;    // RadioText Number
    uint8_t CntRT;
    uint8_t RT_Type;
    

    bit_t IconDisp:1;
#ifdef D_RDS_PI_SEEK
    uint8_t PISeekEnable;
#endif
} RDS_STRUCT;


#define PTY_NONE 0

#define TYPE_A    0x00
#define TYPE_B    0x01

#define G0        (uint8_t)0
#define G0A         (G0 | TYPE_A)
#define G0B        (G0 | TYPE_B)
#define G1        (uint8_t)(1 << 1)
#define G1A         (G1 | TYPE_A)
#define G1B        (G1 | TYPE_B)
#define G2        (uint8_t)(2 << 1)
#define G2A         (G2 | TYPE_A)
#define G2B        (G2 | TYPE_B)
#define G3        (uint8_t)(3 << 1)
#define G3A         (G3 | TYPE_A)
#define G3B        (G3 | TYPE_B)
#define G4        (uint8_t)(4 << 1)
#define G4A         (G4 | TYPE_A)
#define G4B        (G4 | TYPE_B)
#define G5        (uint8_t)(5 << 1)
#define G5A         (G5 | TYPE_A)
#define G5B        (G5 | TYPE_B)
#define G6        (uint8_t)(6 << 1)
#define G6A         (G6 | TYPE_A)
#define G6B        (G6 | TYPE_B)
#define G7        (uint8_t)(7 << 1)
#define G7A         (G7 | TYPE_A)
#define G7B        (G7 | TYPE_B)
#define G8        (uint8_t)(8 << 1)
#define G8A         (G8 | TYPE_A)
#define G8B        (G8 | TYPE_B)
#define G9        (uint8_t)(9 << 1)
#define G9A         (G9 | TYPE_A)
#define G9B        (G9 | TYPE_B)
#define G10        (uint8_t)(10 << 1)
#define G10A        (G10 | TYPE_A)
#define G10B        (G10 | TYPE_B)
#define G11        (uint8_t)(11 << 1)
#define G11A        (G11 | TYPE_A)
#define G11B        (G11 | TYPE_B)
#define G12        (uint8_t)(12 << 1)
#define G12A         (G12 | TYPE_A)
#define G12B        (G12 | TYPE_B)
#define G13        (uint8_t)(13 << 1)
#define G13A         (G13 | TYPE_A)
#define G13B        (G13 | TYPE_B)
#define G14        (uint8_t)(14 << 1)
#define G14A         (G14 | TYPE_A)
#define G14B        (G14 | TYPE_B)
#define G15        (uint8_t)(15 << 1)
#define G15A         (G15 | TYPE_A)
#define G15B        (G15 | TYPE_B)

#define GroupType(x)    (x == (sRds.Group & 0xFE))
#define GroupVersion(x)    (x == sRds.Group)

#define RdsStation        (sRds.MaxLevel>4)
#define NotRdsStation        (sRds.MaxLevel<5)

#define RT_TYPE_AA       0x01
#define RT_TYPE_AB       0x02
#define RT_TYPE_BA       0x03
#define RT_TYPE_BB       0x04
#define RT_TYPE_NULL    0x00




//--------------------------------------------------
//2Declare: Start

EXTERN RDS_STRUCT sRds;

EXTERN void Rds_PushToLast(void);
EXTERN uint8_t Rds_AfChkInit(void);
EXTERN void Rds_Mute(uint8_t Type);
EXTERN void Rds_ClearTaFlags(void);
EXTERN void Rds_ClearEonTaFlags(void);
EXTERN void Rds_SetAfSearch(void);
EXTERN void Rds_Timer10ms(void);
EXTERN void Rds_Timer100ms(void);
EXTERN void Rds_Timer1s(void);
EXTERN uint8_t Rds_ResetAll(void);
EXTERN void Rds_Main(void);
EXTERN void Rds_SwitchToTa(void);
EXTERN void Rds_TaSwitchBack(void);

//2Declare: End!
//--------------------------------------------------

#undef EXTERN

#endif//RDS_FUNC_H

