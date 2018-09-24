#define _USB_C_
#include "..\config\inc.h"



uint8_t l_cDvrSeriesRunFlag;
tSOURCE l_tSourceDVR;



void SRC_DvrStart(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
	TEST(_T("SRC_DvrStart\n"));

}


void SRC_DVRStop(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{	
	TEST(_T("SRC_DvrStop\n"));
}

eSOURCE_MSG_RETURN SRC_DVRMsgHandle(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive)
{
/*    	
    switch(tMsg->Id)  
    {
  	case MS_INPUT_KEY:
	  	switch(tMsg->uData.a_cData[0])
	  	{
	  		case CK_DISP:
		  		re = FALSE;
		  		break;
	  		default:
	  			break;
	  	}
		break;
	default:
		break;
     }
 */    
    return (SRC_MSG_IGNORE);
}


const tSOURCE_CTRL_BLOCK lc_tSrcDvrAttri = 
{
  
    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    SRC_DvrStart,   /*p_fStart*/
    SRC_DVRStop,   /*p_fStop*/
    SRC_DVRMsgHandle,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/
};


#define _DVR_FLAG_  la_cSrcFlagDefault[SRC_TYPE_DVR]

void Dvr_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceDVR,SOURCE_DVR,SRC_TYPE_DVR,"_DVR_",&lc_tSrcDvrAttri,SRC_PRI_NORMAL,_DVR_FLAG_,&l_cDvrSeriesRunFlag);

}




