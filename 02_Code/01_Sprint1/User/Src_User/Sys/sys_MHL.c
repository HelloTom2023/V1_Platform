#define _MHL_C_
#include "..\config\inc.h"

#pragma section data "no_init" begin  

tSOURCE l_tSourceMHL;
#pragma section data "no_init" end  

void SRC_MHLStart(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
    //IO_Set(io_idx_usb_sw1,PIN_OUTPUT,VALID);
    //IO_Set(io_idx_usb_sw2,PIN_OUTPUT,VALID);    
}


void SRC_MHLStop(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone)
{
    //IO_Set(io_idx_usb_sw1,PIN_OUTPUT,INVALID);
    //IO_Set(io_idx_usb_sw2,PIN_OUTPUT,INVALID);    
}


const tSOURCE_CTRL_BLOCK lc_tSrcMHLAttri = 
{
    
    /*function*/
    NULL,   /*p_fInit*/
    NULL,   /*p_fDataSync*/
    NULL,   /*p_fTask*/
    NULL,   /*p_fIsValid*/ 
    SRC_MHLStart,   /*p_fStart*/
    SRC_MHLStop,   /*p_fStop*/
    NULL,   /*p_fSrcMsgHandle*/
    NULL,   /*p_fOption*/

};

#define _MHL_FLAG_   la_cSrcFlagDefault[SRC_TYPE_MHL]

void MHL_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceMHL,SOURCE_MHL,SRC_TYPE_MHL,"MHL",&lc_tSrcMHLAttri,SRC_PRI_NORMAL,_MHL_FLAG_,NULL);
}


#pragma section data "no_init" begin  
tSOURCE l_tSourceMLink;
#pragma section data "no_init" end 



const tSOURCE_CTRL_BLOCK lc_tSrcMLinkAttri = 
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

#define _MLINK_FLAG_ la_cSrcFlagDefault[SRC_TYPE_MIRROR_LINK]
void MLink_CreateSrc(void)
{
    (void)SRC_Create(&l_tSourceMLink,SOURCE_MIRROR_LINK,SRC_TYPE_MIRROR_LINK,"Morror Link",&lc_tSrcMLinkAttri,SRC_PRI_NORMAL,_MLINK_FLAG_,NULL);
}


