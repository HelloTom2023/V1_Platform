#ifndef _SYS_USER_H_
#define _SYS_USER_H_

#ifdef _SYS_USER_C_
#define _SYS_USER_
#else
#define _SYS_USER_ extern
#endif 
extern const uint8_t lc_bSrcKeyOpTransTab[OP_INPUT_N] ;
extern const uint16_t la_cSrcFlagDefault[];
_SYS_USER_ uint8_t SRC_InitHook(void);
_SYS_USER_ uint8_t SRC_MsgHandleHook(eSOURCE_TYPE eSrcType,eSOURCE_ZONE eZone,tMSG_BUF* tMsg,bool bActive);

#endif

