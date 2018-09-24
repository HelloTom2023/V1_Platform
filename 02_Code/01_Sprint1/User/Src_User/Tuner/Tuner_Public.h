/**********************************************************
 * @file        Tuner_Public.h
 * @purpose    Public Definitions of Tuner
 * @version    0.01
 * @date        27.May. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        27.May.2013              v0.01        created
 *  
  **********************************************************/
#ifndef TUNER_PUBLIC_H
#define TUNER_PUBLIC_H

//------------------------------------------------
//2Defs&Enuns:Start

//Region Def
typedef enum region_enum
{
    REGION_EUROPE = 0,
    REGION_OIRT,
    REGION_AUST,
    REGION_MID_EAST,
    REGION_USA1,
    REGION_USA2,
    REGION_USA3,
    REGION_USA4,
    REGION_ES_ASIA,
    REGION_JAPAN,
    REGION_S_AMERICA1,
    REGION_S_AMERICA2,
    REGION_MAX,
}REGION_ENUM;
#define REGION_START REGION_EUROPE
#ifdef R103_H15T_OVERSEAS
#define REGION_USER  REGION_S_AMERICA1
#else
#define REGION_USER  REGION_ES_ASIA
#endif

#define ANT_GAIN_0DB    0
#define ANT_GAIN_6DB    1
#define ANT_GAIN_12DB   2
#define ANT_GAIN_18DB   3
#define ANT_GAIN_24DB   4
#define ANT_GAIN_30DB   5
#define ANT_GAIN_36DB   6
#define ANT_GAIN_42DB   7


//2Defs&Enuns:End!
//------------------------------------------------







#endif//TUNER_PUBLIC_H

