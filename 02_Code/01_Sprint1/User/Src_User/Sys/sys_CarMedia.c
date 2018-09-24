#define _CARMEDIA_C_
#include "..\config\inc.h"

#if 0

#pragma section data "no_init" begin  

tSOURCE l_tSourceCarMedia;
tSOURCE l_tSourceCarSYNC;
tSOURCE l_tSourceCarOnStar;
tSOURCE l_tSourceCarCDC;
tSOURCE l_tSourceCarTuner;
#pragma section data "no_init" end


#define _CARMEDIA_FLAG_   la_cSrcFlagDefault[SRC_TYPE_CAR_MEDIA]


void CarMedia_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceCarMedia,SOURCE_CAR_MEDIA,SRC_TYPE_CAR_MEDIA,"CarMedia",NULL,SRC_PRI_NORMAL,_CARMEDIA_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceCarSYNC,SOURCE_CAR_SYNC,SRC_TYPE_CAR_SYNC,"CarSYNC",NULL,SRC_PRI_NORMAL,_CARMEDIA_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceCarCDC,SOURCE_CAR_CDC,SRC_TYPE_CAR_CDC,"CarCDC",NULL,SRC_PRI_NORMAL,_CARMEDIA_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceCarOnStar,SOURCE_ON_STAR,SRC_TYPE_CAR_OnSTAR,"CarOnStar",NULL,SRC_PRI_NORMAL,_CARMEDIA_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceCarTuner,SOURCE_CAR_TUNER,SRC_TYPE_CAR_TUNER,"CarTuner",NULL,SRC_PRI_NORMAL,_CARMEDIA_FLAG_,NULL);
    
}

#endif

