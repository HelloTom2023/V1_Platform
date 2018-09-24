#include "..\..\..\config\inc.h"

#ifdef UDS_ENABLE_MACRO
/****************************************************************************
 * @function	UdsFbl_ResetSystem
 * @brief  	According UDS ECUR type to execute  Reset operation.
 * @param  	null
 * @retval 	null
****************************************************************************/
void UdsFbl_ResetSystem(uint8_t type)
{
	if(type == UDS_ECUR_SOFT)
	{
		while(1);				/*wait WDT reset */
	}
	else if(type == UDS_ECUR_HARD)
	{
		
	}
	else if(type == UDS_ECUR_KEYOFFON)
	{
		
	}
}
/****************************************************************************
 * @function	UdsFbl_StoreDIDToSystem
 * @brief  	Store the UDS DID to the machine,normally wirte it to the non-volatile memory
 *			such as EEPROM
 * @param  	DID: the DID
 *			pData: the DID data buffer
 *			len:  the buffer data length.
 * @retval 	1- write faild; 0- write succeed
****************************************************************************/
uint8_t UdsFbl_StoreDIDToSystem(uint16_t DID, uint8_t *pData, uint8_t len)
{
	if(DID == DID_ID_F1F8)// S401 EOL
	{
		/*send EOL data to APU */
		CANAPI_LoadEOLInfo(DID,pData, len);
	}
	else if(DID == DID_TBOXREGNUM)
	{
		CanAPI_LoadTboxPhoneInfo(pData, len);
	}
	else if(DID == DID_ID_F1FA)//R103-H15T EOL
	{
		/*send EOL data to APU */
		CANAPI_LoadEOLInfo(DID,pData, len);
	}
	return CAN_EepStore(DID, pData, len);//snake20160803
}

void UdsFbl_StoreDTCToSystem(void)
{
#ifdef ENABLE_UDS_DTC
	uint8_t i=0;
	UdsDTCProcStruct *pUdsDTC=UdsDTC_GetUdsDTCAddr();

	if(NULL==pUdsDTC)
	{
		return;
	}
	for(i=0;i<DTC_ID_VALID_END;i++)
	{
		UdsDTC_EepWriteReq(pUdsDTC->pDiagnoseItem[i].DTCDevIdx);
	}
#endif	
}

/****************************************************************************
 * @function	UdsFbl_CheckAddressValid
 * @brief  	check address block validity
 * @param  	addr: start address
 *			size:   address block size.
 * @retval 	1- address is valid, 0- address is unvalid.
****************************************************************************/
uint8_t  UdsFbl_CheckAddressValid(uint32_t addr,   uint32_t size)
{
	return 1;
}

void UdsFbl_LoadSysData(void *ptr)
{
	uint8_t i = 0;
	tBUS_EEP_DATA *pData = (tBUS_EEP_DATA*)ptr;
	DID_STRUCT *pTable = Uds_GetDIDCfgTable();
	uint8_t index = Uds_GetDidIndex(DID_ID_F1F8);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->DID_F1F8_DATA, pTable[index].ByteLen);
	}

	index = Uds_GetDidIndex(DID_ID_FD01);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->DID_FD01_DATA, pTable[index].ByteLen);
	}

	
	index = Uds_GetDidIndex(DID_ID_F190);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->DID_F190_DATA, pTable[index].ByteLen);
	}

	index = Uds_GetDidIndex(DID_ID_F184);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->DID_F184_DATA, pTable[index].ByteLen);
	}

	index = Uds_GetDidIndex(DID_ID_F1A0);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->DID_F1A0_DATA, pTable[index].ByteLen);
	}

	index = Uds_GetDidIndex(DID_ID_F1A2);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->DID_F1A2_DATA, pTable[index].ByteLen);
	}

	index = Uds_GetDidIndex(DID_ID_F1FA);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->DID_F1FA_DATA, pTable[index].ByteLen);
	}

	index = Uds_GetDidIndex(DID_ID_F101);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->DID_F101_DATA, pTable[index].ByteLen);
	}

	index = Uds_GetDidIndex(DID_ID_F18C);
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
#if 0	// 先不考虑从EEPROM读取
		Memory8Copy(pTable[index].pParam, pData->DID_F18C_DATA, pTable[index].ByteLen);
#endif		
	}
	index = Uds_GetDidIndex(DID_TBOXREGNUM);//add it for exchanging machine ztqin 20150112
	if(pTable[index].Attribute == ATTRI_WRITE)
	{
		Memory8Copy(pTable[index].pParam, pData->Phone, pTable[index].ByteLen);
	}	
}
#endif
/****************************************************************************
 * 							END OF FILE
****************************************************************************/
