
#define OP_AUD_NULL            0                
#define OP_AUD_SYNC            1                
#define OP_AUD_VOL_INC         2             //Currently Volume Control    
#define OP_AUD_VOL_DEC         3                
#define OP_AUD_VOL_SEL         4             //4:+ Front VolVal    
#define OP_AUD_RVOL_INC        5                
#define OP_AUD_RVOL_DEC        6                
#define OP_AUD_RVOL_SEL        7    //4    :+  Rear VolVal        
#define OP_AUD_SVOL_SEL        8    //4    Set Startup Volume: +VolVal        
#define OP_AUD_VOL_CURVE       9    //4     Set Volume Curve Delta : + Delta Value        
#define OP_AUD_MUTE            10            //Front System Key Mute    
#define OP_AUD_RMUTE           11            //Rear System Key Mute    
#define OP_AUD_MUTE_REQ        12        //4 Front System Required for Mute Control : +ACH + Mute Type + System        
#define OP_AUD_RMUTE_REQ       13        //4 Rear System Required for Mute Control : +ACH + Mute Type + System        
#define OP_AUD_BEEP_REQ        14        //4 Require for Beeping : +Beep Type + Attri; Attri : ON/ OFF        
#define OP_AUD_BEEP_POS        15        //4 Beep Position: +Beep Type + Pos( FL  FR FRONT ALL)   // Setting type        
#define OP_AUD_BEEP_VOL        16        //4 Beep Volume : +Beep Type + Vol Val        
#define OP_AUD_BEEP_SEL        17        //4Select Sub Type: +Beep Type + Sub-Type        
#define OP_AUD_BASS_GAIN_INC   18        //Bass Gain Control        
#define OP_AUD_BASS_GAIN_DEC   19                
#define OP_AUD_BASS_GAIN_SEL   20    //4     :+ Bass Gain Value        
#define OP_AUD_BASS_CF_INC     21        //Bass Centre Frequency Control        
#define OP_AUD_BASS_CF_DEC     22                
#define OP_AUD_BASS_CF_SEL     23        //4 :+ Bass CF Value        
#define OP_AUD_BASS_Q_INC      24        // Bass Q Control        
#define OP_AUD_BASS_Q_DEC      25                
#define OP_AUD_BASS_Q_SEL      26        //4 :+ Bass Q Value        
#define OP_AUD_MID_GAIN_INC    27                
#define OP_AUD_MID_GAIN_DEC    28                
#define OP_AUD_MID_GAIN_SEL    29            //4:+ Middle Gain Value    
#define OP_AUD_MID_CF_INC      30                
#define OP_AUD_MID_CF_DEC      31                
#define OP_AUD_MID_CF_SEL      32        //4:+ Middle CF Value        
#define OP_AUD_MID_Q_INC       33                
#define OP_AUD_MID_Q_DEC       34                
#define OP_AUD_MID_Q_SEL       35        //4:+ Middle Q Value        
#define OP_AUD_TREBLE_GAIN_INC 36                
#define OP_AUD_TREBLE_GAIN_DEC 37                
#define OP_AUD_TREBLE_GAIN_SEL 38        //4:+ Treble Gain Value        
#define OP_AUD_TREBLE_CF_INC   39                
#define OP_AUD_TREBLE_CF_DEC   40                
#define OP_AUD_TREBLE_CF_SEL   41    //4:+ Treble CF Value            
#define OP_AUD_TREBLE_Q_INC    42                
#define OP_AUD_TREBLE_Q_DEC    43                
#define OP_AUD_TREBLE_Q_SEL    44    //4:+ Treble Q Value            
#define OP_AUD_BF_PRESET       45        //4:+ Bal&Fad Preset Value        
#define OP_AUD_BAL_INC         46                
#define OP_AUD_BAL_DEC         47                
#define OP_AUD_BAL_SEL         48        //4:+ Balance Value        
#define OP_AUD_FAD_INC         49                
#define OP_AUD_FAD_DEC         50                
#define OP_AUD_FAD_SEL         51            //4 :+ Fader Value    
#define OP_AUD_LOUD_SET        52        //4Loudness On/Off: + Loudness Setting        
#define OP_AUD_LDB_COF         53            //4LDB Cut off Frequency Select: + Cut off frequency    
#define OP_AUD_LDT_CF          54            //4LDT Centre frequency select: + Centre frequency    
#define OP_AUD_SW_SET          55            //4SubWoofer Setting: On OFF    
#define OP_AUD_SW_COF          56            //4Set SubWoofer Cut-Off Frequency: + CoF    
#define OP_AUD_SW_GAIN         57        //4Set SubWoofer Gain: + Gain        
#define OP_AUD_SW_Q            58            //4Set SubWoofer Q: + Q    
#define OP_AUD_XOVER_CHANNEL   59    //Select Xover Channel: + Channel            
#define OP_AUD_XOVER_PRESET    60    //4Select Xover Preset: + Preset            
#define OP_AUD_XOVER_LEVEL     61    //4Set Xover Channel's Level: + Channel+ Level            
#define OP_AUD_XOVER_COF       62        //4 Set Xover Channel's CoF: + Channel+ CoF        
#define OP_AUD_XOVER_SLOPE     63    //4 Set Xover Channel's Slope: + Channel+ Slope            
#define OP_AUD_GEQ_INC         64            //GEQ Type Increase    
#define OP_AUD_GEQ_DEC         65            //GEQ Type Decrease    
#define OP_AUD_GEQ_SEL         66            //4GEQ Type Select:+ GEQ Type    
#define OP_AUD_GEQ_GAIN        67        //4Set GEQ Band Gain: + Band ID + Value(Logic Value)        
#define OP_AUD_GEQ_Q           68            //4Set GEQ Band Q: + Band ID + Value(Logic Value)    
#define OP_AUD_GEQ_CF          69            //4Set GEQ Band CF: + Band ID + Value  (Logic Value)    
#define OP_AUD_DC_SET          70        //4    Set Front DC Filter: + Value(0: OFF)    
#define OP_AUD_RDC_SET         71        //4    Set Rear DC Filter: +Value(0: Off)    
#define OP_AUD_DELAY_LINE      72        //Set One Delay Line        
#define OP_AUD_DELAY_PRESET    73    //Select Delay Line Preset + Preset Number            
#define OP_AUD_DELAY_SPEAKER   74    //Set Specific Speaker's Delay: + Speaker+ Delay            
#define OP_AUD_DELAY_SAVE      75        //Save Currently Delay Setting to Preset: + Preset Number        
#define OP_AUD_DELAY_ACTIVE    76    //Active Speaker Setting            
#define OP_AUD_PHASE_SHIFT     77        //4    Set Phase Shifter: + Channel + Type(ON OFF)    
#define OP_AUD_UBASS_SET       78    //4        : +ON/OFF    
#define OP_AUD_UBASS_LEVEL     79        //4    : + Level    
#define OP_AUD_UBASS_SCALER    80    //4    : +Scaler        
#define OP_AUD_CHANNEL_MODE    81        //4  5.1 Channel Mode : + Mode (0:2ch 1:5.1Ch)        
#define OP_AUD_CAR_STYLE       82            //4Car Style Select : + Style    
#define OP_AUD_SRC_SCALER      83    //4        Set Source Scaler:+ Source + Value    
#define OP_AUD_CHANNEL_GAIN    84        //4: +Channel +Gain        
#define OP_AUD_ACH_SWITCH      85            //4Switch to newly ACH: +ACH +TYPE(ALLFront RearInsertRemove)    
#define OP_AUD_MIX_REQ         86                //4 Audio Mix: +Mix Source + Mix Type(OFFFL FR FRONTRLRRREAR ALL)
#define OP_AUD_MIX_POS         87                
#define OP_AUD_MIX_LEVEL       88                
#define OP_AUD_PEQ_SEL         89                
#define OP_AUD_PEQ_FL_G        90        //Set PEQ Band Gain: + Band ID + Value        
#define OP_AUD_PEQ_FL_Q        91            //Set PEQ Band Q: + Band ID + Value    
#define OP_AUD_PEQ_FL_CF       92            //Set PEQ Band CF: + Band ID + Value  (Logic Value)    
#define OP_AUD_PEQ_FR_G        93        //Set PEQ Band Gain: + Band ID + Value        
#define OP_AUD_PEQ_FR_Q        94            //Set PEQ Band Q: + Band ID + Value    
#define OP_AUD_PEQ_FR_CF       95            //Set PEQ Band CF: + Band ID + Value  (Logic Value)    
#define OP_AUD_PEQ_F_G         96        //Set PEQ Band Gain: + Band ID + Value        
#define OP_AUD_PEQ_F_Q         97            //Set PEQ Band Q: + Band ID + Value    
#define OP_AUD_PEQ_F_CF        98            //Set PEQ Band CF: + Band ID + Value  (Logic Value)    
#define OP_AUD_PEQ_RL_G        99        //Set PEQ Band Gain: + Band ID + Value        
#define OP_AUD_PEQ_RL_Q        100            //Set PEQ Band Q: + Band ID + Value    
#define OP_AUD_PEQ_RL_CF       101            //Set PEQ Band CF: + Band ID + Value  (Logic Value)    
#define OP_AUD_PEQ_RR_G        102        //Set PEQ Band Gain: + Band ID + Value        
#define OP_AUD_PEQ_RR_Q        103            //Set PEQ Band Q: + Band ID + Value    
#define OP_AUD_PEQ_RR_CF       104            //Set PEQ Band CF: + Band ID + Value  (Logic Value)    
#define OP_AUD_PEQ_R_G         105        //Set PEQ Band Gain: + Band ID + Value        
#define OP_AUD_PEQ_R_Q         106            //Set PEQ Band Q: + Band ID + Value    
#define OP_AUD_PEQ_R_CF        107            //Set PEQ Band CF: + Band ID + Value  (Logic Value)    
#define OP_AUD_SVOL_MEDIA       108     //+ Media Startup Volume
#define OP_AUD_SVOL_PHONE       109     // + Phone Startup Volume
#define OP_AUD_SVOL_NAVI            110     // + Navi Startup Volume
#define OP_AUD_NAVI_MODE        111     // + Navi Audio Mode...
#define OP_AUD_CLICK_CLACK      112     // + Flag + Type
#define OP_AUD_SW_CEN_SET      113   // + Setting 
#define OP_AUD_HINT_MEDIA       114
#define OP_AUD_HINT_PHONE       115
#define OP_AUD_HINT_NAVI        116
#define OP_AUD_SVOL_APP         117
#define OP_AUD_HINT_APP         118
#define OP_AUD_TUNER_SCALER     119 // + Mode(AM or Not)  : especially for Hero-Tuner 
#define OP_AUD_REVERSE_VOL     120  //Reverse : Volume down
#define OP_AUD_REVERSE_END     121  //Reverse end: volume back
#define OP_AUD_AVC_LEVEL		122

#define OP_AUD_CH_SEL          199       //set channel ZONE + LOGIC CHANNEL


#define OP_AUDUP_NULL          200  
#define OP_AUDUP_MUTE          201    //4+Mute State+Type(Front or Rear)
#define OP_AUDUP_VOL            202      //4 + Vol + Type
#define OP_AUDUP_RVOL            203    //Update Rear System Volume : + Vol
#define OP_AUDUP_BASIC         204    
#define OP_AUDUP_BASS          205    
#define OP_AUDUP_MID           206    
#define OP_AUDUP_TREBLE        207    
#define OP_AUDUP_TONE          208
#define OP_AUDUP_BAL           209
#define OP_AUDUP_FAD           210
#define OP_AUDUP_BF            212
#define OP_AUDUP_LOUDNESS      211
#define OP_AUDUP_SUBWOOFER     213
#define OP_AUDUP_BEEP          214 //4 Beep Setting: + Beep Type + Beep Vol + Beep Pos    
#define OP_AUDUP_GEQ           215
#define OP_AUDUP_DC            216 //DC Filter: + Value + Type
#define OP_AUDUP_PHASESHIFT    217
#define OP_AUDUP_DELAY         218
#define OP_AUDUP_XOVER         219
#define OP_AUDUP_UBASS         220
#define OP_AUDUP_CHGAIN        221
#define OP_AUDUP_ADV                222


