/****************************************************************************
* File Name : CanTp.h
*
* Modules : CAN Transport Layer head file
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-09-25
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_CAN_TP_H
#define	_CAN_TP_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "CanTp_Type.h"
#include "CanTp_Cfg_Define.h"
#include "VFB_CanTp.h"


/*Macro definition AREA*/
#define _CAN_TP_C	/*define use CanTp.c*/

#ifndef _CAN_TP_C
#define CAN_TP_EXTERN_API
#define CAN_TP_LOCAL_API
#else
#define CAN_TP_EXTERN_API extern
#define CAN_TP_LOCAL_API static
#endif /*_CAN_TP_C*/





/*Variable Define AREA*/
//CanTp_CanMsgStruct_Type CanTp_CanRcvMsgBuffer[CANTP_RECEIVEBUFFERNUMBER];
CanTp_RecvPduControlInformation_Type CanTp_RecvPduCtrInfo;
uint8 CanTp_RecvPudBuffer[CANTP_RXDIAGPDUBUFFER_SIZE];

/*Function declaration AREA*/
/****************************************************************************
 * @function	CanTp_InitFunction
 * @brief  		init cantp parameters
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
CAN_TP_EXTERN_API void CanTp_InitFunction(void);

/****************************************************************************
 * @function	CanTp_RxIndicationFunction
 * @brief  		Indication the can to receive can message
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   Use this API send message to Can Transport Layer
****************************************************************************/
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_EXTERN_API uint8 CanTp_RxIndicationFunction(uint8 ChNo, uint MsgId, uint8* ptr_Data, uint8 Dlc);
#else
CAN_TP_EXTERN_API uint8 CanTp_RxIndicationFunction(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc);
#endif

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionSF
 * @brief  		Indication the can transport to receive can message with single frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionSF(uint8 ChNo, uint16 MsgId, uint8* ptr_Data, uint8 Dlc);
#else
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionSF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc);
#endif

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionFF
 * @brief  		Indication the can transport to receive can message with first frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
#if (CANTP_CANMESSAGEIDTYPE == STANDARD)
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFF(uint8 ChNo, uint16 MsgId, uint8* ptr_Data, uint8 Dlc);
#else
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc);
#endif

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionCF
 * @brief  		Indication the can transport to receive can message with consecutive frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionCF(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc);

/****************************************************************************
 * @function	CanTp_RxIndicationFunctionFC
 * @brief  		Indication the can transport to receive can message with Flow control frame
 * @param  		ChNo: input parameters,CAN channel index.
 *				MsgId : input parameters,the can message id
 *				ptr_Data : input parameters,the can message data
 *				Dlc : input parameters,the can message data length
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
CAN_TP_LOCAL_API uint8 CanTp_RxIndicationFunctionFC(uint8 ChNo, uint32 MsgId, uint8* ptr_Data, uint8 Dlc);


#endif /*_CAN_TP_H*/
/*********************************File End*********************************/
