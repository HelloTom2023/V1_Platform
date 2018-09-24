/**********************************************************
 * @file        Audio_Tab.c
 * @purpose   Datum Tab For Audio
 * @version    0.01
 * @date        17. Dec. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *  Deefisher.Lyu          17.Dec.2013        v0.01        created
 *  
  **********************************************************/

//Beep Attribute:Repetition Setting
const uint8_t Tab_BeepRptAttri[] = 
{
    // MultiMedia Beep Type
    BEEP_RPT_ONCE,//BEEP_TYPE_ORDINARY = 0,        // Ordinary Beep 
    BEEP_RPT_ONCE,//BEEP_TYPE_KEY_ACK,        //Key Pressed Beep
    BEEP_RPT_ONCE,//BEEP_TYPE_KEY_NCK,        //Key Pressed Beep
    BEEP_RPT_ONCE,//BEEP_TYPE_TYRE_ALERT,

    //Car Body Beep Type
    BEEP_RPT_ONCE,//BEEP_TYPE_VALID_KEY,        // Short Beeping for Valid Special Original Key
    BEEP_RPT_ONCE,//BEEP_TYPE_INVALID_KEY,    // Long Beeping for Invalid Special Original Key
    BEEP_RPT_CONTINUOUS,//BEEP_TYPE_ALERT,
    BEEP_RPT_NUMERABLE,//BEEP_TYPE_SEATBELT,
    BEEP_RPT_CONTINUOUS,//BEEP_TYPE_CRUISE,
    BEEP_RPT_ONCE,//BEEP_TYPE_CONFIRMATION,
    BEEP_RPT_CONTINUOUS,//BEEP_TYPE_IGNITION,
    BEEP_RPT_ONCE,//BEEP_TYPE_USER,
};

//Mix Volume Attenuation
const uint8_t Tab_MixAttn[] =
{
    MIX_ATTN_LOW,MIX_ATTN_MID,MIX_ATTN_HIGH,
};

//Delay Line Preset
const uint8_t Tab_DelayPreset[] =
{
    //Small Car
    0x00,0x00,0x00,0x00,0x00,0x00,    //Preset Off
    S_FL_FL,S_FL_FR,S_FL_RL,S_FL_RR,S_FL_SWL,S_FL_SWR,    //FL
    S_FR_FL,S_FR_FR,S_FR_RL,S_FR_RR,S_FR_SWL,S_FR_SWR,    //FR
    S_RL_FL,S_RL_FR,S_RL_RL,S_RL_RR,S_RL_SWL,S_RL_SWR,     //RL
    S_RR_FL,S_RR_FR,S_RR_RL,S_RR_RR,S_RR_SWL,S_RR_SWR,     //RR    
    //Middle Car
    0x00,0x00,0x00,0x00,0x00,0x00,    //Preset Off
    M_FL_FL,M_FL_FR,M_FL_RL,M_FL_RR,M_FL_SWL,M_FL_SWR,    //FL
    M_FR_FL,M_FR_FR,M_FR_RL,M_FR_RR,M_FR_SWL,M_FR_SWR,    //FR
    M_RL_FL,M_RL_FR,M_RL_RL,M_RL_RR,M_RL_SWL,M_RL_SWR,     //RL
    M_RR_FL,M_RR_FR,M_RR_RL,M_RR_RR,M_RR_SWL,M_RR_SWR,     //RR     
    //Big Car
    0x00,0x00,0x00,0x00,0x00,0x00,    //Preset Off
    L_FL_FL,L_FL_FR,L_FL_RL,L_FL_RR,L_FL_SWL,L_FL_SWR,    //FL
    L_FR_FL,L_FR_FR,L_FR_RL,L_FR_RR,L_FR_SWL,L_FR_SWR,    //FR
    L_RL_FL,L_RL_FR,L_RL_RL,L_RL_RR,L_RL_SWL,L_RL_SWR,     //RL
    L_RR_FL,L_RR_FR,L_RR_RL,L_RR_RR,L_RR_SWL,L_RR_SWR,     //RR         
};

//Linear DB to Value, (10^(-x/20))
const uint16_t Tab_Db2Lin[] =	// vivid
{
    0x07FF,   /*  00dB =  1.00 */
    0x0721,   /* -01dB =  0.89 */
    0x065A,   /* -02dB    */
    0x05A8,   /* -03dB    */
    0x050A,   /* -04dB    */
    0x047D,   /* -05dB    */
    0x0400,   /* -06dB    */
    0x0390,   /* -07dB    */
    0x032D,   /* -08dB    */
    0x02D4,   /* -09dB    */
    0x0285,   /* -10dB    */
    0x023F,   /* -11dB    */
    0x0200,   /* -12dB    */
    0x01C8,   /* -13dB    */
    0x0196,   /* -14dB    */
    0x016A,   /* -15dB    */
    0x0143,   /* -16dB    */
    0x011F,   /* -17dB    */
    0x0100,   /* -18dB    */
    0x00E4,   /* -19dB    */
    0x00CB,   /* -20dB    */
    0x00B5,   /* -21dB    */
    0x00A1,   /* -22dB    */
    0x0090,   /* -23dB    */
    0x0080,   /* -24dB    */
    0x0072,   /* -25dB    */
    0x0066,   /* -26dB    */
    0x005B,   /* -27dB    */
    0x0051,   /* -28dB    */
    0x0048,   /* -29dB    */
    0x0040,   /* -30dB    */
    0x0039,   /* -31dB    */
    0x0033,   /* -32dB    */
    0x002D,   /* -33dB    */
    0x0028,   /* -34dB    */
    0x0024,   /* -35dB    */
    0x0020,   /* -36dB    */
    0x001D,   /* -37dB    */
    0x0019,   /* -38dB    */
    0x0017,   /* -39dB    */
    0x0014,   /* -40dB    */
    0x0012,   /* -41dB    */
    0x0010,   /* -42dB    */
    0x000E,   /* -43dB    */
    0x000D,   /* -44dB    */
    0x000B,   /* -45dB    */
    0x000A,   /* -46dB =  0.01 */
    0x0009,   /* -47dB =  0.00 */
    0x0008,   /* -48dB    */
    0x0007,   /* -49dB    */
    0x0006,   /* -50dB    */
    0x0006,   /* -51dB    */
    0x0005,   /* -52dB    */
    0x0004,   /* -53dB    */
    0x0004,   /* -54dB    */
    0x0004,   /* -55dB    */
    0x0003,   /* -56dB    */
    0x0003,   /* -57dB    */
    0x0003,   /* -58dB    */
    0x0002,   /* -59dB    */
    0x0002,   /* -60dB    */
    0x0002,   /* -61dB    */
    0x0002,   /* -62dB    */
    0x0001,   /* -63dB    */
    0x0001,   /* -64dB    */
    0x0001,   /* -65dB =  0.00 */
    0x0001,   /* -66dB =  0.00 */
    0x0001,   /* -67dB =  0.00 */
    0x0001,   /* -68dB =  0.00 */
    0x0001,   /* -69dB =  0.00 */
    0x0001,   /* -70dB =  0.00 */
    0x0001,   /* -71dB =  0.00 */
    0x0001,   /* -72dB =  0.00 */
    0x0000,   /* -73dB =  0.00 */
    0x0000,   /* -74dB =  0.00 */
    0x0000,   /* -75dB =  0.00 */
    0x0000,   /* -76dB =  0.00 */
    0x0000,   /* -77dB =  0.00 */
    0x0000,   /* -78dB =  0.00 */
    0x0000,   /* -79dB =  0.00 */
    0x0000,   /* -80dB =  0.00 */
    0x0000,   /* -81dB =  0.00 */
    0x0000,   /* -82dB =  0.00 */
    0x0000,   /* -83dB =  0.00 */
    0x0000,   /* -84dB =  0.00 */
    0x0000,   /* -85dB =  0.00 */
    0x0000,   /* -86dB =  0.00 */
    0x0000,   /* -87dB =  0.00 */
    0x0000,   /* -88dB =  0.00 */
    0x0000,   /* -89dB =  0.00 */
    0x0000,   /* -90dB =  0.00 */
    0x0000,   /* -91dB =  0.00 */
    0x0000,   /* -92dB =  0.00 */
    0x0000    /* -Infinite dB     */
};/* dB2Lin */

//Beep Volume
const uint8_t Tab_BeepVolume[] =
{
    BEEP_VOL_LOW,BEEP_VOL_MID,BEEP_VOL_HIGH,
};

//Navi&Phone Volume
const uint16_t Tab_NaviPhone_Vol[] =
{
/*12 ~3db*/
0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0805, 0x08E3, 0x09A9, 0x0A5A,
/*+2 ~-7db*/
0x0AE7, 0x0B83, 0x0C00, 0x0C6F, 0x0CD3, 0x0D2B, 0x0D7A, 0x0DC0, 0x0DFF, 0x0E37,
/*-8 ~-17db*/
0x0E68, 0x0E95, 0x0EBC, 0x0EDF, 0x0EFF, 0x0F1B, 0x0F34, 0x0F4A, 0x0F5E, 0x0F6F,
/*-18 ~-27db*/
0x0F7F, 0x0F8D, 0x0F9A, 0x0FA5, 0x0FAF, 0x0FB8, 0x0FBF, 0x0FC6, 0x0FCD, 0x0FD2,
/*-28 ~-36db*/
0x0FD7, 0x0FDC, 0x0FE0, 0x0FE3, 0x0FE6, 0x0FE9, 0x0FEC, 0x0FEE, 0x0FF0,0x0FF0,
0x0FF0,0x0FF0,
};

//Volume Db table
const int8_t Tab_VolDbLev[AUDIO_VOL_MAX + 1] = 	// vivid
{
    -73,        //0
    -60,
    -56,
    -52,
    -48, 
    -44,     //5
    -40, 
    -36,
    -33, 
    -30,    
    -27,        //10
    -24,
    -21, 
    -18, 
    -16, 
    -14,        //15 
    -12, 
    -10, 
    -8, 
    -6,
    -4,        //20
    -2, 
    0, 
    1, 
    2, 
    3,     //25
    4, 
    5, 
    6,
    7,
    8,    //30
    9, 
    10, 
    11,
    12,
    13,    //35
    14,
    15,
    16,
    17,
    18         
};

//Bass CF Table
const uint16_t Tab_Bass_CF[4] = 
{
    60,80,100,200,
};

//Middle CF Table
const uint16_t Tab_Middle_CF[4] = 
{
    500,800,1000,1500,
};

//Treble CF Table
const uint16_t Tab_Treble_CF[4] = 
{
    10000,12500,15000,17500,
};

//Balance Fader Attenuation Table
#if 0
const uint8_t Tab_BF_Atten[] = 
{
    0,2,4,6,8,12,16,24,32,42,
};
#endif
const uint8_t Tab_BF_Atten[] = 
{
    0,6,12,18,24,30,36,40,
};

//Filter's Q Table
const float Tab_Filter_Q[3] =
{
    0.7,1.0,1.5,
};

//Loudness: Bass Boost Curve
const uint8_t Tab_Loudness_B_Curve[] = 
{
    0,15,15,15,15,15,15,15,15,14,14,12,12,12,12,10,10,10,8,8,8,8,8,7,6,5,4,3,2,1,
    0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,5,4,3,2,1,0,0,    
};
//Loudness Treble Boost Curve
#ifdef D_AUDIO_ENABLE_LDT
const uint8_t Tab_Loudness_T_Curve[] = 
{
    0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,2,1,0,0,    
    0,10,10,10,10,10,10,10,10,9,9,8,8,8,8,7,7,7,6,6,6,6,6,5,4,3,2,1,0,0,
};
#endif//D_AUDIO_ENABLE_LDT
//Xover Cof
const uint8_t Tab_XoverCoF[] = 
{    //31 Should Be 31.5.....
    20,25,31,40,50,63,80,100,125,160,200
};

//Graphic Equalizer: 1/3 multiple Frequency step!!
const uint16_t Tab_Geq_Band_CF[GEQ_MAX_NUM * 3] = 
{
    40,50,63,           //Band 1
    80,100,125,
    160,200,250,
    320,400,500,
    630,800,1000,
    1250,1600,2000,
    2500,3200,4000,
    5000,6300,8000,   
    10000,12500,16000,   //Band Max: Band 9
};

//Graphic Equalizer Preset Table
const GEQ_PRESET_STRUCT Tab_Geq_Band[GEQ_MAX_NUM*GEQ_MODE_MAX] =
{
#if 0  //From Luo
     {62,0+AUDIO_GEQ_MAX/2},    //Flat
    {125,0+AUDIO_GEQ_MAX/2},
    {250,0+AUDIO_GEQ_MAX/2},
    {500,0+AUDIO_GEQ_MAX/2},
    {1000,0+AUDIO_GEQ_MAX/2},
    {2000,0+AUDIO_GEQ_MAX/2},
    {4000,0+AUDIO_GEQ_MAX/2},
    {8000,0+AUDIO_GEQ_MAX/2},
    {16000,0+AUDIO_GEQ_MAX/2},

     {62,7+AUDIO_GEQ_MAX/2},    //Pop
    {125,5+AUDIO_GEQ_MAX/2},
    {250,-2+AUDIO_GEQ_MAX/2},
    {500,3+AUDIO_GEQ_MAX/2},
    {1000,7+AUDIO_GEQ_MAX/2},
    {2000,-2+AUDIO_GEQ_MAX/2},
    {4000,4+AUDIO_GEQ_MAX/2},
    {8000,6+AUDIO_GEQ_MAX/2},
    {16000,5+AUDIO_GEQ_MAX/2},
    
     {62,7+AUDIO_GEQ_MAX/2},    //rock
    {125,9+AUDIO_GEQ_MAX/2},
    {250,-3+AUDIO_GEQ_MAX/2},
    {500,2+AUDIO_GEQ_MAX/2},
    {1000,-3+AUDIO_GEQ_MAX/2},
    {2000,-1+AUDIO_GEQ_MAX/2},
    {4000,6+AUDIO_GEQ_MAX/2},
    {8000,9+AUDIO_GEQ_MAX/2},
    {16000,7+AUDIO_GEQ_MAX/2},

     {62,5+AUDIO_GEQ_MAX/2},    //Jazz
    {125,5+AUDIO_GEQ_MAX/2},
    {250,1+AUDIO_GEQ_MAX/2},
    {500,-6+AUDIO_GEQ_MAX/2},
    {1000,3+AUDIO_GEQ_MAX/2},
    {2000,1+AUDIO_GEQ_MAX/2},
    {4000,4+AUDIO_GEQ_MAX/2},
    {8000,6+AUDIO_GEQ_MAX/2},
    {16000,2+AUDIO_GEQ_MAX/2},

     {62,8+AUDIO_GEQ_MAX/2},    //Clscl
    {125,3+AUDIO_GEQ_MAX/2},
    {250,1+AUDIO_GEQ_MAX/2},
    {500,0+AUDIO_GEQ_MAX/2},
    {1000,0+AUDIO_GEQ_MAX/2},
    {2000,1+AUDIO_GEQ_MAX/2},
    {4000,3+AUDIO_GEQ_MAX/2},
    {8000,8+AUDIO_GEQ_MAX/2},
    {16000,10+AUDIO_GEQ_MAX/2},
#else
    {60,0+AUDIO_GEQ_MAX/2},    //Flat
    {100,0+AUDIO_GEQ_MAX/2},
    {200,0+AUDIO_GEQ_MAX/2},
    {400,0+AUDIO_GEQ_MAX/2},
    {800,0+AUDIO_GEQ_MAX/2},
    {1600,0+AUDIO_GEQ_MAX/2},
    {3200,0+AUDIO_GEQ_MAX/2},
    {6400,0+AUDIO_GEQ_MAX/2},
    {10000,0+AUDIO_GEQ_MAX/2},

    {60,4+AUDIO_GEQ_MAX/2},
    {118,7+AUDIO_GEQ_MAX/2},    //Pop
    {200,4+AUDIO_GEQ_MAX/2},
    {573,-1+AUDIO_GEQ_MAX/2},
    {800,0+AUDIO_GEQ_MAX/2},
    {2000,1+AUDIO_GEQ_MAX/2},
    {4000,2+AUDIO_GEQ_MAX/2},
    {6000,4+AUDIO_GEQ_MAX/2},
    {9000,5+AUDIO_GEQ_MAX/2},

    {60,10+AUDIO_GEQ_MAX/2},    //Rock
    {100,7+AUDIO_GEQ_MAX/2},
    {200,3+AUDIO_GEQ_MAX/2},
    {400,1+AUDIO_GEQ_MAX/2},
    {800,0+AUDIO_GEQ_MAX/2},
    {1600,0+AUDIO_GEQ_MAX/2},
    {3200,1+AUDIO_GEQ_MAX/2},
    {6000,3+AUDIO_GEQ_MAX/2},
    {10000,2+AUDIO_GEQ_MAX/2},

    {60,12+AUDIO_GEQ_MAX/2},    //Jazz
    {90,10+AUDIO_GEQ_MAX/2},
    {200,4+AUDIO_GEQ_MAX/2},    
    {400,1+AUDIO_GEQ_MAX/2},
    {800,0+AUDIO_GEQ_MAX/2},
    {2000,1+AUDIO_GEQ_MAX/2},
    {3200,3+AUDIO_GEQ_MAX/2},
    {6000,6+AUDIO_GEQ_MAX/2},        
    {9000,8+AUDIO_GEQ_MAX/2},    

    {60,6+AUDIO_GEQ_MAX/2},    //Classicl
    {100,4+AUDIO_GEQ_MAX/2},
    {200,1+AUDIO_GEQ_MAX/2},
    {400,0+AUDIO_GEQ_MAX/2},
    {800,0+AUDIO_GEQ_MAX/2},
    {1260,1+AUDIO_GEQ_MAX/2},
    {2770,0+AUDIO_GEQ_MAX/2},
    {6000,2+AUDIO_GEQ_MAX/2},
    {9000,3+AUDIO_GEQ_MAX/2},

	{60,-5+AUDIO_GEQ_MAX/2},    //Speech
	{100,-4+AUDIO_GEQ_MAX/2},
	{260,4+AUDIO_GEQ_MAX/2},
	{600,2+AUDIO_GEQ_MAX/2},
	{1260,2+AUDIO_GEQ_MAX/2},
	{2000,4+AUDIO_GEQ_MAX/2},
	{3200,3+AUDIO_GEQ_MAX/2},
	{6400,-3+AUDIO_GEQ_MAX/2},
	{9000,-5+AUDIO_GEQ_MAX/2},   
#endif
};

//Fake GEQ Preset Curve
const PN_FILTER_STRUCT Tab_Geq_Preset_Filter[] = 
{
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},   
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},   

    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  //Pop
    {(AUDIO_GEQ_MAX/2+5),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+3),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+1),1,Q_1P0},   
    {(AUDIO_GEQ_MAX/2+4),1,Q_1P0},   

    {(AUDIO_GEQ_MAX/2+8),1,Q_1P0},  //Rock
    {(AUDIO_GEQ_MAX/2+7),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+3),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+3),1,Q_1P0},   
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},   
    
    {(AUDIO_GEQ_MAX/2+11),1,Q_1P0},  //Jazz
    {(AUDIO_GEQ_MAX/2+10),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+5),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+1),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+2),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+6),1,Q_1P0},   
    {(AUDIO_GEQ_MAX/2+5),1,Q_1P0},   

    {(AUDIO_GEQ_MAX/2+5),1,Q_1P0},  //Classical
    {(AUDIO_GEQ_MAX/2+4),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+2),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},  
    {(AUDIO_GEQ_MAX/2+0),1,Q_1P0},
    {(AUDIO_GEQ_MAX/2+2),1,Q_1P0},   
    {(AUDIO_GEQ_MAX/2+1),1,Q_1P0},   

	{(AUDIO_GEQ_MAX/2-4),1,Q_1P0},  //SPeech
	{(AUDIO_GEQ_MAX/2-3),1,Q_1P0},  
	{(AUDIO_GEQ_MAX/2+2),1,Q_1P0},
	{(AUDIO_GEQ_MAX/2+2),1,Q_1P0},  
	{(AUDIO_GEQ_MAX/2+2),1,Q_1P0},
	{(AUDIO_GEQ_MAX/2+3),1,Q_1P0},  
	{(AUDIO_GEQ_MAX/2+3),1,Q_1P0},
	{(AUDIO_GEQ_MAX/2-3),1,Q_1P0},   
	{(AUDIO_GEQ_MAX/2-4),1,Q_1P0},  
};

//Fake GEQ Preset Gain Curve
const uint8_t Tab_Geq_Preset_Gain[(GEQ_MAX_NUM*3)*GEQ_MODE_MAX] = 
{
    //Flat
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band1
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band2     
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band3    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band4    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band5    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band6
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band7
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band8  
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band9 
    
    //Pop
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+1), //Band1
    (AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+7), //Band2     
    (AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+2), //Band3    
    (AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band4    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band5    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band6
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band7
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+3), //Band8  
    (AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+4),(AUDIO_GEQ_MAX/2+2), //Band9 

    //Rock
    (AUDIO_GEQ_MAX/2+6),(AUDIO_GEQ_MAX/2+8),(AUDIO_GEQ_MAX/2+10), //Band1
    (AUDIO_GEQ_MAX/2+9),(AUDIO_GEQ_MAX/2+7),(AUDIO_GEQ_MAX/2+6), //Band2     
    (AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+2), //Band3    
    (AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band4    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band5    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band6
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+1), //Band7
    (AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+2), //Band8  
    (AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band9 
    
    //Jazz
    (AUDIO_GEQ_MAX/2+9),(AUDIO_GEQ_MAX/2+11),(AUDIO_GEQ_MAX/2+12), //Band1
    (AUDIO_GEQ_MAX/2+11),(AUDIO_GEQ_MAX/2+10),(AUDIO_GEQ_MAX/2+8), //Band2     
    (AUDIO_GEQ_MAX/2+7),(AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+4), //Band3    
    (AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+0), //Band4    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band5    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+1), //Band6
    (AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+3), //Band7
    (AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+6),(AUDIO_GEQ_MAX/2+7), //Band8  
    (AUDIO_GEQ_MAX/2+7),(AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+3), //Band9 

    //Classicl
    (AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+6), //Band1
    (AUDIO_GEQ_MAX/2+5),(AUDIO_GEQ_MAX/2+4),(AUDIO_GEQ_MAX/2+3), //Band2     
    (AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+1), //Band3    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band4    
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band5    
    (AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band6
    (AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+0), //Band7
    (AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+3), //Band8  
    (AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+1),(AUDIO_GEQ_MAX/2+0), //Band9 
    
    //Speech
	(AUDIO_GEQ_MAX/2-2),(AUDIO_GEQ_MAX/2-4),(AUDIO_GEQ_MAX/2-5), //Band1
	(AUDIO_GEQ_MAX/2-4),(AUDIO_GEQ_MAX/2-3),(AUDIO_GEQ_MAX/2-2), //Band2     
	(AUDIO_GEQ_MAX/2+0),(AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+4), //Band3    
	(AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+2), //Band4    
	(AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+2), //Band5    
	(AUDIO_GEQ_MAX/2+2),(AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+4), //Band6
	(AUDIO_GEQ_MAX/2+4),(AUDIO_GEQ_MAX/2+3),(AUDIO_GEQ_MAX/2+1), //Band7
	(AUDIO_GEQ_MAX/2-2),(AUDIO_GEQ_MAX/2-3),(AUDIO_GEQ_MAX/2-4), //Band8  
	(AUDIO_GEQ_MAX/2-5),(AUDIO_GEQ_MAX/2-4),(AUDIO_GEQ_MAX/2-3), //Band9 
};

#ifdef D_TONE_EQ
const GEQ_PRESET_STRUCT Tab_Tone_Eq[3*6] =  
{
    {100,0+AUDIO_BASS_MAX/2},    //Flat
    {1000,0+AUDIO_MID_MAX/2},
    {12500,0+AUDIO_TREBLE_MAX/2},

    {80,5+AUDIO_BASS_MAX/2},    //Pop
    {1500,-3+AUDIO_MID_MAX/2},
    {15000,3+AUDIO_TREBLE_MAX/2},

    {120,3+AUDIO_BASS_MAX/2},    //Rock
    {1000,-3+AUDIO_MID_MAX/2},
    {17500,3+AUDIO_TREBLE_MAX/2},

    {100,-2+AUDIO_BASS_MAX/2},    //Jazz
    {500,2+AUDIO_MID_MAX/2},
    {15000,3+AUDIO_TREBLE_MAX/2},

    {150,-3+AUDIO_BASS_MAX/2},    //Classicl
    {2000,2+AUDIO_MID_MAX/2},
    {12500,2+AUDIO_TREBLE_MAX/2},

    {100,-4+AUDIO_BASS_MAX/2},    //Speech
    {2000,4+AUDIO_MID_MAX/2},
    {9000,3+AUDIO_TREBLE_MAX/2},
};
#ifdef D_TUNER_EQ
//snake20160905   收音机的音效和多媒体区分进行单独的设置...
const GEQ_PRESET_STRUCT Tab_Tone_Tuner_Eq[3*6] =  
{
	//最后确认的效果:  高中低 -2  1  -4
	{100,-6+AUDIO_BASS_MAX/2},    //Flat  20160104 snake
    {1000,2+AUDIO_MID_MAX/2},
    {12500,-3+AUDIO_TREBLE_MAX/2},

    {80,5+AUDIO_BASS_MAX/2},    //Pop
    {1500,-3+AUDIO_MID_MAX/2},
    {15000,3+AUDIO_TREBLE_MAX/2},

    {120,3+AUDIO_BASS_MAX/2},    //Rock
    {1000,-3+AUDIO_MID_MAX/2},
    {17500,3+AUDIO_TREBLE_MAX/2},

    {100,-2+AUDIO_BASS_MAX/2},    //Jazz
    {500,2+AUDIO_MID_MAX/2},
    {15000,3+AUDIO_TREBLE_MAX/2},

    {150,-3+AUDIO_BASS_MAX/2},    //Classicl
    {2000,2+AUDIO_MID_MAX/2},
    {12500,2+AUDIO_TREBLE_MAX/2},

    {100,-4+AUDIO_BASS_MAX/2},    //Speech
    {2000,4+AUDIO_MID_MAX/2},
    {9000,3+AUDIO_TREBLE_MAX/2},
};
#endif


#endif//D_TONE_EQ

//Geq Max Gain Table
const uint8_t Tab_Geq_Max_Gain[/*GEQ_MODE_MAX*/] =
{
#if 0
    (0+AUDIO_GEQ_MAX/2),
    (7+AUDIO_GEQ_MAX/2),
    (10+AUDIO_GEQ_MAX/2),
    (12+AUDIO_GEQ_MAX/2),
    (6+AUDIO_GEQ_MAX/2),
#else
    (0+AUDIO_GEQ_MAX/2),
    (7+AUDIO_GEQ_MAX/2),
    (9+AUDIO_GEQ_MAX/2),
    (6+AUDIO_GEQ_MAX/2),
    (10+AUDIO_GEQ_MAX/2),
    (4+AUDIO_GEQ_MAX/2),
#endif    
};

#if 1
const XOVER_ATTRI_STRUCT Tab_Xover_Preset[3 * XOVER_PRESET_MAX] =
{
    {XOVER_LEVEL_0DB,XOVER_COF_80,XOVER_SLOPE_FLAT},  //F HPF
    {XOVER_LEVEL_0DB,XOVER_COF_80,XOVER_SLOPE_FLAT},    //R HPF
    {XOVER_LEVEL_0DB,XOVER_COF_80,XOVER_SLOPE_FLAT},    //SW LPF
    //Preset1  一组预设值中有三组数据，前喇叭 ， 后喇叭，中低音
    {-2+XOVER_LEVEL_0DB,XOVER_COF_40,XOVER_SLOPE_6},  //F HPF
    {-2+XOVER_LEVEL_0DB,XOVER_COF_40,XOVER_SLOPE_6},    //R HPF
    {-2+XOVER_LEVEL_0DB,XOVER_COF_80,XOVER_SLOPE_6},    //SW LPF
    //Preset2
    {-6+XOVER_LEVEL_0DB,XOVER_COF_31P5,XOVER_SLOPE_12},
    {-6+XOVER_LEVEL_0DB,XOVER_COF_31P5,XOVER_SLOPE_12},
    {-6+XOVER_LEVEL_0DB,XOVER_COF_100,XOVER_SLOPE_12},
    //Preset3
    {-10+XOVER_LEVEL_0DB,XOVER_COF_63,XOVER_SLOPE_18},
    {-10+XOVER_LEVEL_0DB,XOVER_COF_63,XOVER_SLOPE_18},
    {-10+XOVER_LEVEL_0DB,XOVER_COF_160,XOVER_SLOPE_18}, 
};

#endif

#if 0
const XOVER_ATTRI_STRUCT Tab_Xover_Preset[3 * XOVER_PRESET_MAX] =
{
    {XOVER_LEVEL_0DB,XOVER_COF_80,XOVER_SLOPE_FLAT},  //F HPF
    {XOVER_LEVEL_0DB,XOVER_COF_80,XOVER_SLOPE_FLAT},    //R HPF
    {XOVER_LEVEL_0DB,XOVER_COF_80,XOVER_SLOPE_FLAT},    //SW LPF
    //Preset1  一组预设值中有三组数据，前喇叭 ， 后喇叭，中低音
    {4+XOVER_LEVEL_0DB,XOVER_COF_40,XOVER_SLOPE_6},  //F HPF
    {4+XOVER_LEVEL_0DB,XOVER_COF_40,XOVER_SLOPE_6},    //R HPF
    {4+XOVER_LEVEL_0DB,XOVER_COF_80,XOVER_SLOPE_6},    //SW LPF
    //Preset2
    {-2+XOVER_LEVEL_0DB,XOVER_COF_31P5,XOVER_SLOPE_12},
    {-2+XOVER_LEVEL_0DB,XOVER_COF_31P5,XOVER_SLOPE_12},
    {-2+XOVER_LEVEL_0DB,XOVER_COF_100,XOVER_SLOPE_12},
    //Preset3
    {-6+XOVER_LEVEL_0DB,XOVER_COF_63,XOVER_SLOPE_18},
    {-6+XOVER_LEVEL_0DB,XOVER_COF_63,XOVER_SLOPE_18},
    {-6+XOVER_LEVEL_0DB,XOVER_COF_160,XOVER_SLOPE_18}, 
};

#endif
