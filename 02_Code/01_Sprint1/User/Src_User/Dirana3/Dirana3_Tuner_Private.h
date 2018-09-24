/**********************************************************
 * @file        Dirana3_Tuner_Private.h
 * @purpose    Definition of Dirana Tuner Part
 * @version    0.01
 * @date        24. Jan. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        24.Jan.2013              v0.01        created
 *  
  **********************************************************/
#ifndef DIRANA3_TUNER_PRIVATE_H
#define DIRANA3_TUNER_PRIVATE_H


//............................................................................................
//4Tuner Initial Registers---start

// Default
#define DIRANA_TUNER             0x40//0x00
#define DIRANA_OPT                 0x01 //PD On 0x01
#define DIRANA_RADIO             0xEA//0x4A     
#define DIRANA_SIGNAL            0x01 
#define DIRANA_BWCTRL          0x0A//0x05   
#define DIRANA_SPECIAL             0x00
#define DIRANA_RDS                 0x45    //Decorder Mode with Data available output
//0x0A
//0x0B
#define DIRANA_LEV_OFFSET          0x30  
#define DIRANA_SM_TIME         0x04//0x65
#define DIRANA_SM_DET             0x10    
#define DIRANA_SM_LEV             0x40//0x50//0x3A   
#define DIRANA_SM_NM             0x33    
#define DIRANA_SM_LIM            0x0A// 0x0F//0x0C    
#define DIRANA_HC_TIME         0x04//0x6E 
#define DIRANA_HC_DET             0xBF//0x35  
#define DIRANA_HC_LEV             0x33 
#define DIRANA_HC_NM             0x55//0x33  
#define DIRANA_HC_LIM             0x04//0x02  
#define DIRANA_HC_LOC             0x00//0x04
#define DIRANA_ST_TIME             0x04//0x72  
#define DIRANA_ST_DET             0x3F   
#define DIRANA_ST_LEV             0x4A  
#define DIRANA_ST_NM             0x44//0x33 
#define DIRANA_ST_LIM             0x00
#define DIRANA_STHB_DET         0x3F  
#define DIRANA_STHB_LNM         0x24//0x13  
//4Tuner Initial Registers---end
//............................................................................................

// Dirana Tuner Mode
#define DIRANA_MODE_STANDBY         0x00
#define DIRANA_MODE_PRESET         0x10
#define DIRANA_MODE_SEARCH         0x20
#define DIRANA_MODE_UPDATE         0x30
#define DIRANA_MODE_JUMP             0x40
#define DIRANA_MODE_CHECK         0x50
#define DIRANA_MODE_END             0x70

//Dirana Band Mode
#define DIRANA_BAND_FM         0x00
#define DIRANA_BAND_LW        0x01
#define DIRANA_BAND_MW        0x02
#define DIRANA_BAND_SW        0x03
#define DIRANA_BAND_WX        0x04
#define DIRANA_BAND_DAB3        0x05
#define DIRANA_BAND_DABL        0x06


// Dirana Read Register Definition
#define DIRANA_STATUS    0
#define DIRANA_LEVEL    1
#define DIRANA_USN        2
#define DIRANA_WAM        3
#define DIRANA_FOF        4
#define DIRANA_IFBW     5
#define DIRANA_MOD     6
#define DIRANA_RDS_STATUS    7
#define DIRANA_RDS_AH        8
#define DIRANA_RDS_AL        9
#define DIRANA_RDS_BH        10
#define DIRANA_RDS_BL        11
#define DIRANA_RDS_CH        12
#define DIRANA_RDS_CL        13
#define DIRANA_RDS_DH        14
#define DIRANA_RDS_DL        15
#define DIRANA_RDS_ERR        16
#define DIRANA_AGCATT     0x12
#define DIRANA_IDENT     0x15 

// Dirana Seek Threshold
#define DIRANA_FM_LEVEL        20       // 20dbuv
#define DIRANA_FM_LEV_TH    56    // 2*(NXP663X_FM_LEVEL+8))
#define DIRANA_FM_USN        20      // 20%    
#define DIRANA_FM_USN_TH    51    //((NXP663X_FM_USN*0xFF)/100)
#define DIRANA_FM_WAM         18      // 15%
#define DIRANA_FM_WAM_TH    45    //((NXP663X_FM_WAM*0xFF)/100)  ////switch WAM TH from 15% to 18% 
#define DIRANA_FM_FOF        10    // 10khz
#define DIRANA_FM_FOF_TH    10

#define DIRANA_FM_LOC_DELTA    45    //20DB

#define DIRANA_AM_LEVEL        50       // 25dbuv
#define DIRANA_AM_LEV_TH    116    // 2*(NXP663X_AM_LEVEL+8))
#define DIRANA_AM_FOF        15    // 1.5khz
#define DIRANA_AM_FOF_TH    15    

#define DIRANA_AM_LOC_DELTA    40    //20DB

#endif//DIRANA3_TUNER_PRIVATE_H

