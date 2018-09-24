/**********************************************************
 * @file        Hero_Tuner_Private.h
 * @purpose    Definition of Hero Tuner Part
 * @version    0.01
 * @date        03. SEP. 2012
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        03.SEP.2012              v0.01        created
 *  
  **********************************************************/
#ifndef HERO_TUNER_PRIVATE_H
#define HERO_TUNER_PRIVATE_H


//............................................................................................
//4Tuner Initial Registers---start

#if 0//DEBUG_TUNER
// Europe Optimal Version
#define NXP663X_TUNER             0x40
#define NXP663X_OPT             0x00
#define NXP663X_RADIO             0xAA//0xC8     
#define NXP663X_SIGNAL            0x01 
#define NXP663X_BWCTRL          0x09   
#define NXP663X_SPECIAL         0x00
#define NXP663X_RDS             0x41
#define NXP663X_LEV_OFFSET      0x30  
#define NXP663X_SM_TIME         0x25
#define NXP663X_SM_DET         0x13    
#define NXP663X_SM_LEV             0x41  
#define NXP663X_SM_NM            0x65// 0x35    
#define NXP663X_SM_LIM             0x09    
#define NXP663X_HC_TIME         0x2D 
#define NXP663X_HC_DET        0x7F// 0x3F  
#define NXP663X_HC_LEV             0x33 
#define NXP663X_HC_NM             0x65  
#define NXP663X_HC_LIM            0x12// 0x01  
#define NXP663X_HC_LOC         0x05
#define NXP663X_ST_TIME         0x75  
#define NXP663X_ST_DET             0x7F//0x3F   
#define NXP663X_ST_LEV            0x42// 0x4A  
#define NXP663X_ST_NM             0x33 
#define NXP663X_ST_LIM             0x00
#define NXP663X_STHB_DET       0x7F//  0x3F  
#define NXP663X_STHB_LNM        0x12// 0x13  

#define NXP663X_FM_TUNER 
#define NXP663X_FM_OPT 
#define NXP663X_FM_RADIO 
#define NXP663X_FM_SIGNAL  
#define NXP663X_FM_BWCTRL 
#define NXP663X_FM_SPECIAL 
#define NXP663X_FM_RDS         0x45   // Decoder Mode, Interrupt Output
#define NXP663X_FM_LEV_OFFSET 
#define NXP663X_FM_SM_TIME 
#define NXP663X_FM_SM_DET 
#define NXP663X_FM_SM_LEV 
#define NXP663X_FM_SM_NM 
#define NXP663X_FM_SM_LIM     
#define NXP663X_FM_HC_TIME  
#define NXP663X_FM_HC_DET 
#define NXP663X_FM_HC_LEV 
#define NXP663X_FM_HC_NM 
#define NXP663X_FM_HC_LIM     
#define NXP663X_FM_HC_LOC 
#define NXP663X_FM_ST_TIME  
#define NXP663X_FM_ST_DET 
#define NXP663X_FM_ST_LEV 
#define NXP663X_FM_ST_NM 
#define NXP663X_FM_ST_LIM 
#define NXP663X_FM_STHB_DET 
#define NXP663X_FM_STHB_LNM 

#define NXP663X_AM_TUNER         0x0A
#define NXP663X_AM_OPT
#define NXP663X_AM_RADIO
#define NXP663X_AM_SIGNAL         0x06   //50hz ~  2Khz
#define NXP663X_AM_BWCTRL
#define NXP663X_AM_SPECIAL
#define NXP663X_AM_RDS
#define NXP663X_AM_LEV_OFFSET
#define NXP663X_AM_SM_TIME
#define NXP663X_AM_SM_DET
#define NXP663X_AM_SM_LEV         0x40
#define NXP663X_AM_SM_NM
#define NXP663X_AM_SM_LIM         0x04
#define NXP663X_AM_HC_TIME     0x12
#define NXP663X_AM_HC_DET 
#define NXP663X_AM_HC_LEV         0x5B
#define NXP663X_AM_HC_NM
#define NXP663X_AM_HC_LIM
#define NXP663X_AM_HC_LOC         0x05
#define NXP663X_AM_ST_TIME 
#define NXP663X_AM_ST_DET
#define NXP663X_AM_ST_LEV
#define NXP663X_AM_ST_NM
#define NXP663X_AM_ST_LIM
#define NXP663X_AM_STHB_DET
#define NXP663X_AM_STHB_LNM
//4Tuner Initial Registers---end
#else 
// Europe Optimal Version

#define NXP663X_TUNER             0x00
#define NXP663X_OPT               0x00
#define NXP663X_RADIO             0xEE  
#define NXP663X_SIGNAL            0x01 
#define NXP663X_BWCTRL            0x07   
#define NXP663X_SPECIAL           0x00
#define NXP663X_RDS               0x45
#define NXP663X_LEV_OFFSET        0x30  
#define NXP663X_SM_TIME           0x05
#define NXP663X_SM_DET            0x15    
#define NXP663X_SM_LEV            0x3A   
#define NXP663X_SM_NM             0x32    
#define NXP663X_SM_LIM            0x0A    
#define NXP663X_HC_TIME           0x2A 
#define NXP663X_HC_DET            0x3F  
#define NXP663X_HC_LEV            0x42 
#define NXP663X_HC_NM             0x66  
#define NXP663X_HC_LIM            0x00  
#define NXP663X_HC_LOC            0x00
#define NXP663X_ST_TIME           0x00  
#define NXP663X_ST_DET            0x35   
#define NXP663X_ST_LEV            0x22  
#define NXP663X_ST_NM             0x22 
#define NXP663X_ST_LIM            0x00
#define NXP663X_STHB_DET          0x3F  
#define NXP663X_STHB_LNM          0x11 

#if 0

#define NXP663X_FM_TUNER             0x00
#define NXP663X_FM_OPT               0x00
#define NXP663X_FM_RADIO             0xEE  
#define NXP663X_FM_SIGNAL            0x01 
#define NXP663X_FM_BWCTRL            0x0B//0x07   
#define NXP663X_FM_SPECIAL           0x00
#define NXP663X_FM_RDS               0x41//0x45
#define NXP663X_FM_LEV_OFFSET        0x29//36//28//0x30  
#define NXP663X_FM_SM_TIME           	0x6A//0x05
#define NXP663X_FM_SM_DET            	0x15    
#define NXP663X_FM_SM_LEV            	0x52//0x3A   
#define NXP663X_FM_SM_NM                0x44//	0x77//0x32     //keilee20150717
#define NXP663X_FM_SM_LIM            	0x09//0x0A    
#define NXP663X_FM_HC_TIME           	0x4A//0x0A//0x2A   //keilee20150716
#define NXP663X_FM_HC_DET               0x10//	0X1F//0xFF//0x3F //keilee20150716  20150717
#define NXP663X_FM_HC_LEV            	0X52//0x77//0x42    //keilee20150716
#define NXP663X_FM_HC_NM             	0X55//0X77//0x66     //keilee20150716
#define NXP663X_FM_HC_LIM            	0X12//0x10//0x00    //keilee20150716
#define NXP663X_FM_HC_LOC            	0x00
#define NXP663X_FM_ST_TIME           	0x05//0x00  
#define NXP663X_FM_ST_DET            	0xFF//0x35   
#define NXP663X_FM_ST_LEV            	0x7E//0x22  
#define NXP663X_FM_ST_NM             	0x77//0x22 
#define NXP663X_FM_ST_LIM            	0x00
#define NXP663X_FM_STHB_DET          	0xFF  
#define NXP663X_FM_STHB_LNM          	0x23//0x11 
S401 20160707 长安验收
#else
// S401 20160707 长安验收
#define NXP663X_FM_TUNER             0x00
#define NXP663X_FM_OPT               0x00
#define NXP663X_FM_RADIO             0xEA  
#define NXP663X_FM_SIGNAL            0x01 
#define NXP663X_FM_BWCTRL            0x0A//0x07   
#define NXP663X_FM_SPECIAL           0x00
#define NXP663X_FM_RDS               0x41//0x45
#define NXP663X_FM_LEV_OFFSET        0x30//36//28//0x30  
#define NXP663X_FM_SM_TIME           	0x6A//0x05
#define NXP663X_FM_SM_DET            	0x15    
#define NXP663X_FM_SM_LEV            	0x52//0x3A   
#define NXP663X_FM_SM_NM                0x77//	0x77//0x32     //keilee20150717
#define NXP663X_FM_SM_LIM            	0x09//0x0A    
#define NXP663X_FM_HC_TIME           	0x0A//0x0A//0x2A   //keilee20150716
#define NXP663X_FM_HC_DET               0x1F//	0X1F//0xFF//0x3F //keilee20150716  20150717
#define NXP663X_FM_HC_LEV            	0X53//0x77//0x42    //keilee20150716
#define NXP663X_FM_HC_NM             	0X77//0X77//0x66     //keilee20150716
#define NXP663X_FM_HC_LIM            	0X02//0x10//0x00    //keilee20150716
#define NXP663X_FM_HC_LOC            	0x00
#define NXP663X_FM_ST_TIME           	0x05//0x00  
#define NXP663X_FM_ST_DET            	0x3F//0x35   
#define NXP663X_FM_ST_LEV            	0x6E//0x22  
#define NXP663X_FM_ST_NM             	0x77//0x22 
#define NXP663X_FM_ST_LIM            	0x10
#define NXP663X_FM_STHB_DET          	0x3F  
#define NXP663X_FM_STHB_LNM          	0x23//0x11 

#endif


#define NXP663X_AM_TUNER             0x0A
#define NXP663X_AM_OPT               0x00
#define NXP663X_AM_RADIO             0xE8//0xC8//lkm20140417_edit     
#define NXP663X_AM_SIGNAL            0x06//0x0A//AM high pass: 50 Hz 
#define NXP663X_AM_BWCTRL            0x05   
#define NXP663X_AM_SPECIAL           0x00
#define NXP663X_AM_RDS               0x41
#define NXP663X_AM_LEV_OFFSET        37//0x30  
#define NXP663X_AM_SM_TIME           0x25
#define NXP663X_AM_SM_DET            0x13    
#define NXP663X_AM_SM_LEV            0x40   
#define NXP663X_AM_SM_NM             0x35    
#define NXP663X_AM_SM_LIM            0x04    
#define NXP663X_AM_HC_TIME           0x12 
#define NXP663X_AM_HC_DET            0x3F  
#define NXP663X_AM_HC_LEV            0x5B 
#define NXP663X_AM_HC_NM             0x55  
#define NXP663X_AM_HC_LIM            0x01  
#define NXP663X_AM_HC_LOC            0x05
#define NXP663X_AM_ST_TIME           0x75  
#define NXP663X_AM_ST_DET            0x3F   
#define NXP663X_AM_ST_LEV            0x4A  
#define NXP663X_AM_ST_NM             0x33 
#define NXP663X_AM_ST_LIM            0x00
#define NXP663X_AM_STHB_DET          0x3F  
#define NXP663X_AM_STHB_LNM          0x13    
//4Tuner Initial Registers---end
#endif
//............................................................................................

// Hero tuner mode
#define HERO_MODE_PWRDN         0
#define HERO_MODE_PRESET             0x10
#define HERO_MODE_SEARCH             0x20
#define HERO_MODE_UPDATE         0x30
#define HERO_MODE_JUMP             0x40
#define HERO_MODE_CHECK             0x50

// Hero Read Register Definition
#define HERO_STATUS    0
#define HERO_LEVEL    1
#define HERO_USN        2
#define HERO_WAM        3
#define HERO_FOF        4
#define HERO_IFBW     5
#define HERO_MOD     6
#define HERO_RDS_STATUS    7
#define HERO_RDS_AH        8
#define HERO_RDS_AL        9
#define HERO_RDS_BH        10
#define HERO_RDS_BL        11
#define HERO_RDS_CH        12
#define HERO_RDS_CL        13
#define HERO_RDS_DH        14
#define HERO_RDS_DL        15
#define HERO_RDS_ERR        16
#define HERO_AGCATT     0x12
#define HERO_IDENT     0x15 

// Hero Seek Threshold
#define HERO_FM_LEVEL        	20       // 20dbuv  一般为25左右
#define HERO_FM_LEV_TH   	0x38  //0x3E//0x20//56    //(LEV*0.5 -8 dbuv)//lkm20140409_edit
#define HERO_FM_USN        	20      // 20%    
#define HERO_FM_USN_TH   	0x60//0x88//51    //((NXP663X_FM_USN*0xFF)/100)//lkm20140409_edit   默认一般7.8十
#define HERO_FM_WAM        	18// 15      // 15%
#define HERO_FM_WAM_TH    	0x55//0x60//0x84//38    //((NXP663X_FM_WAM*0xFF)/100)//lkm20140409_edit  默认一般7.8十
#define HERO_FM_FOF        	10    // 10khz
#define HERO_FM_FOF_TH     	10//lkm20140409_edit

#define HERO_AM_LEVEL       	47// 36       // 25dbuv
#define HERO_AM_LEV_TH   	106//110// 88
#define HERO_AM_FOF        	15    // 1.5khz
#define HERO_AM_FOF_TH    	15    

#define HERO_AM_LOC_DELTA    40    //20DB
#define HERO_FM_LOC_DELTA    40    //20DB


//LEV = (DB+8)*2
#define HERO_SIGSTR_10DB    ((10+8)*2)
#define HERO_SIGSTR_15DB    ((15+8)*2)
#define HERO_SIGSTR_20DB    ((20+8)*2)
#define HERO_SIGSTR_25DB    ((25+8)*2)
#define HERO_SIGSTR_30DB    ((30+8)*2)
#define HERO_SIGSTR_35DB    ((35+8)*2)
#define HERO_SIGSTR_40DB    ((40+8)*2)
#define HERO_SIGSTR_45DB    ((45+8)*2)
#define HERO_SIGSTR_50DB    ((50+8)*2)
#define HERO_SIGSTR_55DB    ((55+8)*2)
#define HERO_SIGSTR_60DB    ((60+8)*2)

#define HERO_USN_LEV0        ((255 * 15) / 100)
#define HERO_USN_LEV1        ((255 * 25) / 100)
#define HERO_USN_LEV2        ((255 * 35) / 100)
#define HERO_USN_LEV3        ((255 * 45) / 100)

#define HERO_WAM_LEV0        ((255 * 15) / 100)
#define HERO_WAM_LEV1        ((255 * 25) / 100)
#define HERO_WAM_LEV2        ((255 * 35) / 100)
#define HERO_WAM_LEV3        ((255 * 45) / 100)

#define HERO_SIGSTR_FM_LEV0        HERO_SIGSTR_15DB
#define HERO_SIGSTR_FM_LEV1        HERO_SIGSTR_30DB    
#define HERO_SIGSTR_FM_LEV2        HERO_SIGSTR_45DB

#define HERO_SIGSTR_AM_LEV0        HERO_SIGSTR_35DB
#define HERO_SIGSTR_AM_LEV1        HERO_SIGSTR_45DB    
#define HERO_SIGSTR_AM_LEV2        HERO_SIGSTR_55DB

#endif//HERO_TUNER_PRIVATE_H

