#ifndef   _UDS_CAN_H
#define  _UDS_CAN_H

typedef struct
{
	uint8_t UseId;
	uint32_t TxMsgId;
	uint32_t RxPhyId;
	uint32_t RxFuncId;
}UDS_CAN_CFG;

extern UDS_CAN_CFG  UdsCANConfig;

UDS_EXTERN void 	Uds_CANConfigEnter(UDS_CAN_CFG *pCfgInput);
UDS_EXTERN void 	Uds_CANInit(void);
UDS_EXTERN void 	Uds_USDT_TxMsgHandle(USDT_PDU *pPDU);
UDS_EXTERN uint8_t 	Uds_CANMsgRcvHandler(CanMsgStruct *pMsg);
UDS_EXTERN void 	Uds_SessionControl_PosRsp(uint8_t RespCode);
UDS_EXTERN void 	Uds_Response_Negative(uint8_t  NegCode);
UDS_EXTERN void 	Uds_SendFlowConFrame(UDS_FS_TYPE Fs,uint8_t Bsize,uint8_t STmin);
UDS_EXTERN void 	Uds_SessionControl_PosRsp(uint8_t RespCode);
UDS_EXTERN void 	Uds_CommControl_PosRsp(uint8_t SubFunc);
UDS_EXTERN void 	Uds_EcuReset_PosRsp(uint8_t type);
UDS_EXTERN void 	Uds_ReadDataByPeriodId_PosRsp(void);
UDS_EXTERN void 	Uds_RDBPI_SendMsg(uint8_t FrameLen, uint8_t *pData);
UDS_EXTERN void 	Uds_WriteDataById_PosRsp(uint16_t Did);
UDS_EXTERN void 	Uds_TesterPresent_PosRsp(void);
/****************************************************************************
 * @function	Uds_ControlDTCSetting_PosRsp
 * @brief  	CDTCS service Positive Response message (use CAN bus)
 * @param  	SubFunc: response sub function				
 * @retval 	null
****************************************************************************/
UDS_EXTERN void 	Uds_ControlDTCSetting_PosRsp(uint8_t SubFunc);

/****************************************************************************
 * @function	Uds_ClearDTCInfo_PosRsp
 * @brief  	CDTCI service Positive Response message (use CAN bus)
 * @param  	null				
 * @retval 	null
****************************************************************************/
UDS_EXTERN void 	Uds_ClearDTCInfo_PosRsp(void);

/****************************************************************************
 * @function	Uds_ReadDTCInfo_PosRsp
 * @brief  	RDTCI service Positive Response message (use CAN bus)
 * @param  	pParam: pointer to the parameter buffer;
 *			len: parameter length
 *			subFunc: service subfunction.
 * @retval 	null
****************************************************************************/
UDS_EXTERN void 	Uds_ReadDTCInfo_PosRsp(uint8_t subFunc, uint8_t *pParam, uint8_t len);

/****************************************************************************
 * @function	Uds_RoutineControl_PosRsp
 * @brief  	Routine Control  service Positive Response message (use CAN bus)
 * @param  	SubFunc: sub function 
 *			id: Routine Id
 *			pParam: pointer to the parameter buffer;
 *			len: parameter length
 * @retval 	null
****************************************************************************/
UDS_EXTERN void 	Uds_RoutineControl_PosRsp(uint8_t SubFunc, uint16_t id, uint8_t*pParam, uint8_t ParamLen);

UDS_EXTERN void 	Uds_TransferData_PosRsp(uint8_t Sequence);
UDS_EXTERN void 	Uds_RequestTransferExit_PosRsp(void);

UDS_EXTERN void 	Uds_IOControl_PosRsp(uint8_t *pParam, uint8_t len);
UDS_EXTERN void 	Uds_RequestDownload_PosRsp(uint8_t blockSize);
UDS_EXTERN void 	Uds_SecurityAccess_PosRsp(uint8_t SubFunc, uint8_t SeedNum);
UDS_EXTERN void 	Uds_SendSingleFrameMsg(uint8_t len, uint8_t ServiceId, uint8_t *pParam);
UDS_EXTERN uint8_t 	Uds_SendFirstFrameMsg(USDT_PDU *pPDU);
UDS_EXTERN uint8_t 	Uds_SendContinueFrameMsg(USDT_PDU *pPDU, uint8_t *SendOverFlag);

#endif
/****************************************************************************
 * **                                        FILE END
****************************************************************************/


