/****************************************************************************
* File Name : CanIf.h
*
* Modules : CAN Interface Layer head file
*
* Summary : 1.The file is Can interface layer head file.
* 			2.The file user define Can interface layer type and variables.
* 			3.The module between CAN Driver and CanTP modules.
*
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-26
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_CAN_IF_H
#define	_CAN_IF_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "CanIf_Type.h"
#include "CanIf_Cfg_Define.h"
#include "CanIf_Cfg_Table.h"
#include "VFB_CanIf.h"


/*Macro definition AREA*/
#define _CAN_IF_C	/*define use CanIf.c*/

#ifndef _CAN_IF_C
#define CAN_IF_API_CALL
#define CAN_IF_API_LOCAL
#else
#define CAN_IF_EXTERN_API extern
#define CAN_IF_LOCAL_API static
#endif /*_CAN_TP_C*/


/*Variable declaration AREA*/
CanIf_CanMsgStruct_Type CanIf_CanRecvMsgBuff[CANIF_RECEIVEBUFFERNUMBER];
CanIf_BuffControlInformation_Type CanIf_CanRecvMsgBuffCtrInfo;
CanIf_CanMsgTxManagementControlInfomation_Type CanIf_CanTxMsgCtrInfo;

/*Function declaration AREA*/
/****************************************************************************
 * @function	CanIf_Init
 * @brief  		can interface layer init function.
 * @param  		NULL
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API void CanIf_Init(void);

/****************************************************************************
 * @function	CanIf_MainFunction
 * @brief  		can interface layer main function.
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API void CanIf_MainFunction(void);

/****************************************************************************
 * @function	CANbus_RecvInterruptCallBack
 * @brief  		the CAN BUS receive interrupt call back function.
 * @param  		ChNo: input parameters,CAN channel index.
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_RecvInterruptCallback(uint8 ChNo);

/****************************************************************************
 * @function	CanIf_SendInterruptCallback
 * @brief  		the CAN BUS send interrupt call back function.
 * @param  		ChNo: input parameters,CAN channel index.
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_IF_EXTERN_API uint8 CanIf_SendInterruptCallback(uint8 ChNo);

#if ((CANIF_RECEIVERMESSAGEDLCCHECK == ENABLE) || (CANIF_RECEIVERMESSAGEDLCCHECK == ENABLE))
/****************************************************************************
 * @function	CanIf_RecvSoftFilter
 * @brief  		can receive message software filter.
 * 				the function filter rules base on can message id and DLC .
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_IF_LOCAL_API uint8 CanIf_RecvSoftFilterDlcCheck(uint8 chno, uint16 MsgId, uint8* ptr_Data, uint8 Dlc);
#else
CAN_IF_LOCAL_API uint8 CanIf_RecvSoftFilterDlcCheck(uint8 chno, uint32 MsgId, uint8* ptr_Data, uint8 Dlc);
#endif
#endif

/****************************************************************************
 * @function	CanIf_WriteRecvBuffer
 * @brief  		write can message to canif buffer
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_IF_LOCAL_API uint8 CanIf_WriteRecvBuffer(uint8 chno, uint16 MsgId, uint8* ptr_Data, uint8 Dlc);
#else
CAN_IF_LOCAL_API uint8 CanIf_WriteRecvBuffer(uint8 chno, uint32 MsgId, uint8* ptr_Data, uint8 Dlc);
#endif

/****************************************************************************
 * @function	CanIf_ReadRecvBuffer
 * @brief  		read can message to canif buffer
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   NULL
****************************************************************************/
#if (CANIF_CANMESSAGEIDTYPE == STANDARD)
CAN_IF_LOCAL_API uint8 CanIf_ReadRecvBuffer(uint8* ptr_chno, uint16* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc);
#else
CAN_IF_LOCAL_API uint8 CanIf_ReadRecvBuffer(uint8* ptr_chno, uint32* ptr_MsgId, uint8* ptr_Data, uint8* ptr_Dlc);
#endif

/****************************************************************************
 * @function	CanIf_MainFunction
 * @brief  		the can interface layer receive message main function
 * @param
 * @retval
 * @attention   null
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_RxMainFunction(void);

/****************************************************************************
 * @function	CanIf_TxMainFunction
 * @brief  		the can interface layer transmit message main function
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxMainFunction(void);

/****************************************************************************
 * @function	CanIf_TxMainFunction
 * @brief  		the can interface layer transmit message main function
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxManagementFunction(void);

/****************************************************************************
 * @function	CanIf_TxTimerHandleFunction
 * @brief  		the can interface layer handle the tx message timer and counter
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_TxTimerHandleFunction(void);

/****************************************************************************
 * @function	CanIf_CanControllerTxHardwareBuffIndexVaildCheck
 * @brief  		can interface layer check can controller Tx hardware buffer Index
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
CAN_IF_LOCAL_API void CanIf_CanControllerTxHardwareBuffIndexVaildCheck(uint8* bufNo);

#endif /*_CAN_IF_H*/
/*********************************File End*********************************/
