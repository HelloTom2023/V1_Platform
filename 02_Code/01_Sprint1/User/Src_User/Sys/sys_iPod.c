#define _IPOD_C_
#include "..\config\inc.h"


uint8_t l_iPodSeriesRunflag;

#pragma section data "no_init" begin  
tSOURCE l_tSourceiPod;
tSOURCE l_tSourceiPodAudio;
tSOURCE l_tSourceiPodVideo;
#pragma section data "no_init" end


const tSOURCE_CTRL_BLOCK lc_tSrciPodAttri = 
{

    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    NULL,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};

#define _iPODAUDIO_FLAG_    la_cSrcFlagDefault[SRC_TYPE_IPOD_AUDIO]
#define _iPODVIDEO_FLAG_    la_cSrcFlagDefault[SRC_TYPE_IPOD_VIDEO]
#define _iPOD_FLAG_         la_cSrcFlagDefault[SRC_TYPE_IPOD]

void iPod_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceiPodAudio,SOURCE_IPOD_AUDIO,SRC_TYPE_IPOD_AUDIO,"iPodAudio",&lc_tSrciPodAttri,SRC_PRI_NORMAL,_iPODAUDIO_FLAG_,&l_iPodSeriesRunflag);
    (void)SRC_Create(&l_tSourceiPodVideo,SOURCE_IPOD_VIDEO,SRC_TYPE_IPOD_VIDEO,"iPodVideo",&lc_tSrciPodAttri,SRC_PRI_NORMAL,_iPODVIDEO_FLAG_,&l_iPodSeriesRunflag);    
    (void)SRC_Create(&l_tSourceiPod,SOURCE_IPOD,SRC_TYPE_IPOD,"iPod",&lc_tSrciPodAttri,SRC_PRI_NORMAL,_iPOD_FLAG_,&l_iPodSeriesRunflag);
}

