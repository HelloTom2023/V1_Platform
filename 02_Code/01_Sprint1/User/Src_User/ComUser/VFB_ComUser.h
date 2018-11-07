/****************************************************************************
* File Name : VFB_ComUser.h
*
* Modules :
*
* Summary :
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-10-26
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_VFB_COM_USER_H
#define	_VFB_COM_USER_H

/*Include head files AREA*/
#include "..\Common\Common.h"
#include "ComUser_Cfg_Define.h"
#include "..\..\..\config\inc.h"
#include "..\Debug\Debug.h"
#include "..\Com\Com.h"


/*Macro definition AREA*/
/****************************************************************************
 * @function	ComUser_Com_ImmediatelyWriteTxSignalCh0
 * @brief
 * @param  		FormatType : Use Motorola Format
 * 				ChNo : Use Ch0
 * 				MsgId : input parameters
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : input parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
#define ComUser_Com_ImmediatelyWriteTxSignalCh0(MsgId,StartBit,Length,ptr_SignalValue)		Com_ImmediatelyWriteTxSignal(COM_USER_MESSAGE_FORMAT,0x00,MsgId,StartBit,Length,ptr_SignalValue)

/****************************************************************************
 * @function	ComUser_Com_ImmediatelyWriteTxSignalCh1
 * @brief
 * @param  		FormatType : Use Motorola Format
 * 				ChNo : Use Ch1
 * 				MsgId : input parameters
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : input parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
#define ComUser_Com_ImmediatelyWriteTxSignalCh1(MsgId,StartBit,Length,ptr_SignalValue)		Com_ImmediatelyWriteTxSignal(COM_USER_MESSAGE_FORMAT,0x01,MsgId,StartBit,Length,ptr_SignalValue)

/****************************************************************************
 * @function	Com_ReadRxSignalCh0
 * @brief
 * @param 		FormatType : Use Motorola Format
 * 				ChNo : Use Ch0
 * 				MsgId : input parameters
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : output parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
#define ComUser_Com_ReadRxSignalCh0(MsgId, StartBit, Length, ptr_SignalValue)		Com_ReadRxSignal(COM_USER_MESSAGE_FORMAT, 0x00, MsgId, StartBit, Length, ptr_SignalValue)

/****************************************************************************
 * @function	Com_ReadRxSignalCh1
 * @brief
 * @param 		FormatType : Use Motorola Format
 * 				ChNo : Use Ch1
 * 				MsgId : input parameters
 * 				StartBit : input parameters
 * 				Length : input parameters
 *				ptr_SignalValue : output parameters
 * @retval 		ret : function operate result
 * @attention   The function can improved in the future.
 * 				the parameters ptr_SignalValue can modify to data type automatic application
 * 				You can define the ptr_SignalValue data type is void,but the input parameters data type support uint8 or uint16 and etc.
****************************************************************************/
#define ComUser_Com_ReadRxSignalCh1(MsgId, StartBit, Length, ptr_SignalValue)		Com_ReadRxSignal(COM_USER_MESSAGE_FORMAT, 0x01, MsgId, StartBit, Length, ptr_SignalValue)

/****************************************************************************
 * @function	ComUser_Debug_OutputInfo
 * @brief
 * @param
 * @retval
 * @attention
****************************************************************************/
#define ComUser_Debug_OutputInfo(x)		Debug_ComUser_OutputInfo(x)



/*Function declaration AREA*/




#endif /*_VFB_COM_USER_H*/
/*********************************File End*********************************/
