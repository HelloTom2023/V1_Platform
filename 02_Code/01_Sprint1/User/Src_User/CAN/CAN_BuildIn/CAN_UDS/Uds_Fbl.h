#ifndef _UDS_FBL_H_
#define _UDS_FBL_H_

UDS_EXTERN void UdsFbl_ResetSystem(uint8_t type);
UDS_EXTERN uint8_t  UdsFbl_StoreDIDToSystem(uint16_t DID, uint8_t *pData, uint8_t len);
UDS_EXTERN void UdsFbl_StoreDTCToSystem(void);
UDS_EXTERN uint8_t  UdsFbl_CheckAddressValid(uint32_t addr,   uint32_t size);

UDS_EXTERN void UdsFbl_LoadSysData(void *pData);
#endif
