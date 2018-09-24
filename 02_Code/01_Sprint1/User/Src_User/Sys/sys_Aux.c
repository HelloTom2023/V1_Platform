#define _AUX_C_
#include "..\config\inc.h"

uint8_t SRC_AUXIsValid(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	#ifdef D_AUX_EOL
		EOLCfgStruct *pEOLCfg=pCAN_GetEOLStr();
		if(pEOLCfg->EOLState.bits.AUXSupport)
			return VALID;//g_tMcuDevState.uConnetState.bits.Aux_In;
	    return INVALID;
	#else
		return VALID;
	#endif
}


const tSOURCE_CTRL_BLOCK lc_tSrcAUXAttri = 
{
    
    /*function*/
    NULL,    /*p_fInit*/
    NULL,    /*p_fDataSync*/
    NULL,    /*p_fTask*/
    SRC_AUXIsValid,//NULL,    /*p_fIsValid*/ 
    NULL,   /*p_fStart*/
    NULL,   /*p_fStop*/
    NULL,    /*p_fSrcMsgHandle*/
    NULL,    /*p_fOption*/

};

tSOURCE l_tSourceFAUX;
tSOURCE l_tSourceRAUX;

#define _FAUX_FLAG_   la_cSrcFlagDefault[SRC_TYPE_F_AUX]
#define _RAUX_FLAG_   la_cSrcFlagDefault[SRC_TYPE_R_AUX]

void AUX_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceFAUX,SOURCE_F_AUX,SRC_TYPE_F_AUX,"FAux",&lc_tSrcAUXAttri,SRC_PRI_NORMAL,_FAUX_FLAG_,NULL);
    (void)SRC_Create(&l_tSourceRAUX,SOURCE_R_AUX,SRC_TYPE_R_AUX,"RAux",&lc_tSrcAUXAttri,SRC_PRI_NORMAL,_RAUX_FLAG_,NULL);
}

