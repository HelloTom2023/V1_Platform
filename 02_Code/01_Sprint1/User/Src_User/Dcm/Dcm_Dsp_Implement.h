/****************************************************************************
* File Name : Dcm_Dsp_Implement.h
*
* Modules : Diagnostic communication management modules submodules
*           DSP : Diagnostic Service Processing
*                 Implement diagnostic service protocol function
*
* Summary :
*          Note : in this version,only implements one channel.
*
* Reference Documents :
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-08
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef	_DCM_DSP_IMPLEMENT_H_
#define	_DCM_DSP_IMPLEMENT_H_

/*Include head files AREA*/
#include "Dcm_Dsp_Interface.h"

/*Macro definition AREA*/




/*Variable Define AREA*/


/*Function declaration AREA*/
/****************************************************************************
 * @function	Dsp_MainFunction
 * @brief  		NULL
 * @param  		ChNo : Input parameters, bus channel.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsp_MainFunction(uint8 ChNo)
{
	switch(Dsp_UdsServiceCtrInfo[ChNo].MachineState)
	{
		case DCM_SERVICE_STATUS_IDLE:
		{
			/*doing nothing*/
			break;
		}

		case DCM_SERVICE_STATUS_REQ:
		{
			Dcm_Debug_OutputInfo(_T("Dsp received Request PDU,SID = 0x%x\n",Dsp_UdsServiceCtrInfo[ChNo].SI));
			/*Check the service id is define in this version*/
			Dsp_UdsServiceCtrInfo[ChNo].Index = Dsp_CheckServicesIsSupport(Dsp_UdsServiceCtrInfo[ChNo].SI);
			if(0xFF == Dsp_UdsServiceCtrInfo[ChNo].Index)
			{
				/*Response NRC11 serviceNotSupported*/
			}
			else
			{
				/*notification DCM PDU to application layer and check the notification result*/
				Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_RUN;
				Dcm_Debug_OutputInfo(_T("SID check OK,will perform diagnostic services...\n\n"));
			}
			break;
		}

		case DCM_SERVICE_STATUS_RUN:
		{
			uint8 ret = E_NOT_OK;

			Dcm_Debug_OutputInfo(_T("Perform diagnostic services in the time....SID = 0x%x\n\n",Dsp_UdsServiceCtrInfo[0].SI));

			/*Call Services handler function*/
			ret = Dsp_ServicesFunction_Process(ChNo);

			/*Check the diagnostic services process return value*/
			if((E_OK == ret) || (E_NOT_OK == ret))
			{
				Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_COMPLETED;
			}
			else
			{
				/*Doing nothing*/
			}
			break;
		}

		case DCM_SERVICE_STATUS_COMPLETED:
		{
			Dcm_Debug_OutputInfo(_T("DCM_SERVICE_STATUS_COMPLETED....SID = 0x%x\n\n",Dsp_UdsServiceCtrInfo[0].SI));
			/*Check the response type*/
			if(DCM_RESPONSE_TYPE_POSITIVE == Dsp_UdsServiceCtrInfo[ChNo].ResType)
			{
				/*update response PDU,and request send frame*/
				Dsp_TxDiagResponsePositivePDU(ChNo);
				Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_INITBUF;
			}
			else if(DCM_RESPONSE_TYPE_SUPPOSRSP == Dsp_UdsServiceCtrInfo[ChNo].ResType)
			{
				/*perform successful,but not send positive response to bus*/
				Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_INITBUF;
			}
			else if(DCM_RESPONSE_TYPE_NEGATIVE == Dsp_UdsServiceCtrInfo[ChNo].ResType)
			{
				Dsp_TxDiagResponseNegativePDU(ChNo,		\
						Dsp_UdsServiceCtrInfo[ChNo].SI,	\
						Dsp_UdsServiceCtrInfo[ChNo].NRC);

				Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_INITBUF;
			}
			else if(DCM_RESPONSE_TYPE_NOTTXNRC == Dsp_UdsServiceCtrInfo[ChNo].ResType)
			{
				Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_INITBUF;
			}

			break;
		}

		case DCM_SERVICE_STATUS_INITBUF:
		{
			Dsp_UdsServiceCtrInfo[ChNo].ChNo = ChNo;
			Dsp_UdsServiceCtrInfo[ChNo].Index = 0x00;
			Dsp_UdsServiceCtrInfo[ChNo].MachineState = DCM_SERVICE_STATUS_IDLE;
			Dsp_UdsServiceCtrInfo[ChNo].SI = 0x00;
			Dsp_UdsServiceCtrInfo[ChNo].SubFunc = 0x00;
			Dsp_UdsServiceCtrInfo[ChNo].ReqType = DCM_REQ_TYPE_NONE;
			Dsp_UdsServiceCtrInfo[ChNo].SPRMIB = 0x00;
			Dsp_UdsServiceCtrInfo[ChNo].ReqDL = 0x00;
			memset(Dsp_UdsServiceCtrInfo[ChNo].ReqData,0x00,DCM_REQBUFF_SIZE);
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_INIT;
			Dsp_UdsServiceCtrInfo[ChNo].PosResDL = 0x00;
			memset(Dsp_UdsServiceCtrInfo[ChNo].PosResData,0x00,DCM_POSRESBUF_SIZE);
			Dsp_UdsServiceCtrInfo[ChNo].NRC = 0x00;
			break;
		}

		case DCM_SERVICE_STATUS_ERROR:
		{
			/*Error handling*/
			/*Reserved*/
			break;
		}

		default:
		{
			/*doing noting*/
			break;
		}
	}
}

/****************************************************************************
 * @function	Dsp_TxDiagResponsePositivePDU
 * @brief  		NULL
 * @param  		ChNo : Input parameters, bus channel
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
DCM_EXTERN_API uint8 Dsp_TxDiagResponsePositivePDU(uint8 ChNo)
{
	uint8 ret = DCM_E_NOT_OK;
	uint8 Data[DCM_REQBUFF_SIZE+0x02]= {0x00};

	Data[0] = Dsp_UdsServiceCtrInfo[ChNo].SI + 0x40;
	Data[1] = Dsp_UdsServiceCtrInfo[ChNo].SubFunc;
	memcpy(&Data[2],Dsp_UdsServiceCtrInfo[ChNo].PosResData,Dsp_UdsServiceCtrInfo[ChNo].PosResDL);

	ret = Dcm_TxDiagResponseInfo(ChNo, Dsp_UdsServiceCtrInfo[ChNo].PosResDL+2, Data);
	return ret;
}

/****************************************************************************
 * @function	Dsp_TxDiagResponseNegativePDU
 * @brief  		NULL
 * @param  		ChNo : Input parameters, bus channel
 * 				SID : input parameters, services identifier.
 * 				NRC : Input parameters, NRC
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
DCM_EXTERN_API uint8 Dsp_TxDiagResponseNegativePDU(uint8 ChNo,uint8 SID,uint8 NRC)
{
	uint8 ret = DCM_E_NOT_OK;
	uint8 Data[3]= {0x00};

	Data[0] = 0x7F;
	Data[1] = SID;
	Data[2] = NRC;

	ret = Dcm_TxDiagResponseInfo(ChNo, 0X03, Data);
	return ret;
}

/****************************************************************************
 * @function	Dsp_CheckServicesIsSupport
 * @brief  		NULL
 * @param  		SID : Input parameters, diagnostic services id
 * @retval 		0xff : the SID not support.
 *              0x00 ~ 0xfe : the SID in the list index
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckServicesIsSupport(uint8 SID)
{
	uint8 i = 0x00;

	for(i = 0x00; ; i++)
	{
		/*Check if the list ends*/
		if(Dsp_SupportServiceList[i].Index == 0xFF)
		{
			return 0xff;
		}
		else
		{
			/*Doing nothing*/
		}

		/*Check the SID*/
		if(Dsp_SupportServiceList[i].SI == SID)
		{
			return i;
		}
		else
		{
			/*Doing nothing*/
		}
	}
}

/****************************************************************************
 * @function	Dsp_CheckSubFunctionIsSupport
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters
 * 				SubId : Input parameters, diagnostic services sub function id
 * @retval 		0xff : the sub id not support.
 *              0x00 ~ 0xfe : the sub id in the list index
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckSubFunctionIsSupport(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8 SubId)
{
	uint8 i = 0x00;

	for(i = 0x00; ; i++)
	{
		/*Check if the list ends*/
		if(ptr_Dcm_SubFunctionList[i].Index == 0xFF)
		{
			return 0xff;
		}
		else
		{
			/*Doing nothing*/
		}

		/*Check the SubId*/
		if(ptr_Dcm_SubFunctionList[i].SubId == SubId)
		{
			return i;
		}
		else
		{
			/*Doing nothing*/
		}
	}
}

/****************************************************************************
 * @function	Dsp_CheckServicesIsSupportInActiveSession
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters
 * @retval 		E_OK : Check OK
 * 				E_NOT_OK : Check failure
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckServicesIsSupportInActiveSession(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 CurrentSesType = 0x00;
	uint8 ServiceSesTypeMask = 0x00;

	/*Get currents session type*/
	Dsl_GetSessionType(&CurrentSesType);

	/*Get the index of the current session, have determined the location of the current session in the mask */
	Index = Dsp_CheckSubFunctionIsSupport(Dsp_Services_0x10_SupportFunctionList,CurrentSesType);
	/*Check the Index Range: the Index range is 0x00 ~ 0x07*/
	/*
	 * Reserved : Add Code
	 * */

	/*get services session types mask*/
	Dsp_GetServicesSessionTypeMask(ptr_Dcm_SubFunctionList,&ServiceSesTypeMask);

	Dcm_Debug_OutputInfo(_T("Dsp_CheckServicesIsSupportInActiveSession: CurrentSesType = 0x%x,Index = %d,ServiceSesTypeMask = 0x%x,current = 0x%x\n",	\
			CurrentSesType,Index,ServiceSesTypeMask,CommFunc_BitShiftLeft(0x01,(0x07-Index))));

	/*Check ths SID support in active session,NRC7F Check*/
	if(0x00 == (CommFunc_BitShiftLeft(0x01,(0x07-Index)) & ServiceSesTypeMask))
	{
		/*the service not support this session,shall be response NRC7F*/
		/*Response NRC7F*/
		ret = E_NOT_OK;
	}
	else
	{
		ret = E_OK;
	}

	return ret;
}

/****************************************************************************
 * @function	Dsp_CheckSubFunctionIsSupportInActiveSession
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters
 * 				SubId : Input parameters
 * @retval 		E_OK : Check OK
 * 				E_NOT_OK : Check failure
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_CheckSubFunctionIsSupportInActiveSession(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8 SubId)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 CurrentSesType = 0x00;
	uint8 SubFunctionSesTypeMask = 0x00;

	/*Get currents session type*/
	Dsl_GetSessionType(&CurrentSesType);

	/*Get the index of the current session, have determined the location of the current session in the mask */
	Index = Dsp_CheckSubFunctionIsSupport(Dsp_Services_0x10_SupportFunctionList,CurrentSesType);
	/*Check the Index Range: the Index range is 0x00 ~ 0x07*/
	/*
	 * Reserved : Add Code
	 * */

	/*get sub function session types mask*/
	Dsp_GetSubFunctionSessionTypeMask(ptr_Dcm_SubFunctionList,SubId,&SubFunctionSesTypeMask);

	Dcm_Debug_OutputInfo(_T("Dsp_CheckSubFunctionIsSupportInActiveSession: CurrentSesType = 0x%x,Index = %d,SubFunctionSesTypeMask = 0x%x,current = 0x%x\n",	\
				CurrentSesType,Index,SubFunctionSesTypeMask,CommFunc_BitShiftLeft(0x01,(0x07-Index))));

	/*Check ths sub function support in active session,NRC7E Check*/
	if(0x00 == (CommFunc_BitShiftLeft(0x01,(0x07-Index)) & SubFunctionSesTypeMask))
	{
		/*the sub function not support this session,shall be response NRC7E*/
		/*Response NRC7E*/
		ret = E_NOT_OK;
	}
	else
	{
		ret = E_OK;
	}

	return ret;
}

/****************************************************************************
 * @function	Dsp_GetServicesSessionTypeMask
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters,
 * 				ptr_SesTypeMask : output parameters,
 * @retval 		ret : function error event value
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_GetServicesSessionTypeMask(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8* ptr_SesTypeMask)
{
	uint8 ret = E_NOT_OK;
	uint8 i = 0x00;

	/*Check input parameters*/
	if((NULL == ptr_SesTypeMask) || (NULL == ptr_Dcm_SubFunctionList))
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	for(i = 0x00; ; i++)
	{
		/*Check if the list ends*/
		if(ptr_Dcm_SubFunctionList[i].Index == 0xFF)
		{
			ret = E_OK;
			return ret;
		}
		else
		{
			/*Get MASK*/
			*ptr_SesTypeMask |= ptr_Dcm_SubFunctionList[i].SupportSeesion;
			ret = E_OK;
			Dcm_Debug_OutputInfo(_T("Dsp_GetServicesSessionTypeMask: i = %d,SupportSeesion = 0x%x\n",i,ptr_Dcm_SubFunctionList[i].SupportSeesion));
		}
	}
	return ret;
}

/****************************************************************************
 * @function	Dsp_GetSubFunctionSessionTypeMask
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters,
 * 				SubId : Input parameters,
 * 				ptr_SesTypeMask : output parameters,
 * @retval 		ret : function error event value
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_GetSubFunctionSessionTypeMask(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8 SubId,uint8* ptr_SesTypeMask)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;

	/*Check input parameters*/
	if((NULL == ptr_SesTypeMask) || (NULL == ptr_Dcm_SubFunctionList))
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	Index = Dsp_CheckSubFunctionIsSupport(ptr_Dcm_SubFunctionList,SubId);
	/*Check the return value*/
	if(0xFF == Index)
	{
		ret = E_NOT_OK;
	}
	else
	{
		*ptr_SesTypeMask = ptr_Dcm_SubFunctionList[Index].SupportSeesion;
		ret = E_OK;
	}
	return ret;
}

/****************************************************************************
 * @function	Dsp_GetServicesSecurityLevelMask
 * @brief  		NULL
 * @param  		ptr_Dcm_SubFunctionList : Input parameters,
 * 				ptr_SecLevelMask : output parameters,
 * @retval 		ret : function error event value
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_GetServicesSecurityLevelMask(Dcm_SupportSubFunctionList_Struct_Type* ptr_Dcm_SubFunctionList,uint8* ptr_SecLevelMask)
{
	uint8 ret = E_NOT_OK;
	uint8 i = 0x00;

	/*Check input parameters*/
	if((NULL == ptr_SecLevelMask) || (NULL == ptr_Dcm_SubFunctionList))
	{
		ret = E_PARAM_NULLPTR;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	for(i = 0x00; ; )
	{
		/*Check if the list ends*/
		if(ptr_Dcm_SubFunctionList[i].Index == 0xFF)
		{
			ret = E_OK;
		}
		else
		{
			/*Get MASK*/
			*ptr_SecLevelMask |= ptr_Dcm_SubFunctionList[i].SupportSecurityLevel;
			ret = E_OK;
		}
	}
}

/****************************************************************************
 * @function	Dsp_ServicesFunction_Process
 * @brief  		process the diagnostic services
 * @param  		ChNo : Input parameters, bus channel
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_Process(uint8 ChNo)
{
	uint8 ret = E_NOT_OK;

	switch(Dsp_UdsServiceCtrInfo[ChNo].SI)
	{
		case DCM_SID_DSC:
		{
			ret = Dsp_ServicesFunction_DiagnosticSessionControl(ChNo);
			break;
		}

		case DCM_SID_ER:
		{
			ret = Dsp_ServicesFunction_ECUReset(ChNo);
			break;
		}

		default:
		{
			/*doing nothing*/
			break;
		}
	}

	return ret;
}

/****************************************************************************
 * @function	Dsp_ServicesFunction_DiagnosticSessionControl
 * @brief  		Diagnostic service $10 handling
 * @param  		ChNo : Input parameters, Bus channel
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_DiagnosticSessionControl(uint8 ChNo)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint16 P2Server = 0x00;
	uint16 P2_Server = 0x00;

	Dcm_Debug_OutputInfo(_T("Start Run DiagnosticSessionControl Service.......SubId = 0x%x\n",Dsp_UdsServiceCtrInfo[ChNo].SubFunc));

	/*Check the SID support in active session,NRC7F Check*/
	if(E_NOT_OK == Dsp_CheckServicesIsSupportInActiveSession(Dsp_Services_0x10_SupportFunctionList))
	{
		/*Check the request pdu type*/
		if(DCM_REQ_TYPE_FUNC == Dsp_UdsServiceCtrInfo[ChNo].ReqType)
		{
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NOTTXNRC;
			Dsp_UdsServiceCtrInfo[ChNo].NRC = 0x00;
		}
		else
		{
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NEGATIVE;
			Dsp_UdsServiceCtrInfo[ChNo].NRC = DCM_NRC_SNSIAS;
		}
		Dcm_Debug_OutputInfo(_T("NRC7F\n\n"));
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the s perform condition,NRC22*/
	/*
	 * Add code
	 * */

	/*minimum length check,NRC13 Check*/
	if(Dsp_UdsServiceCtrInfo[ChNo].ReqDL < 0x02)
	{
		/*Response NRC13*/
		Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NEGATIVE;
		Dsp_UdsServiceCtrInfo[ChNo].NRC = DCM_NRC_IMLOIF;
		return ret;
		Dcm_Debug_OutputInfo(_T("NRC13\n\n"));
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the sub function support in active session,NRC7E Check*/
	if(E_NOT_OK == Dsp_CheckSubFunctionIsSupportInActiveSession(Dsp_Services_0x10_SupportFunctionList,Dsp_UdsServiceCtrInfo[0].SubFunc))
	{
		/*Check the request pdu type*/
		if(DCM_REQ_TYPE_FUNC == Dsp_UdsServiceCtrInfo[ChNo].ReqType)
		{
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NOTTXNRC;
			Dsp_UdsServiceCtrInfo[ChNo].NRC = 0x00;
		}
		else
		{
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NEGATIVE;
			Dsp_UdsServiceCtrInfo[ChNo].NRC = DCM_NRC_SFNISAS;
		}
		Dcm_Debug_OutputInfo(_T("NRC7E\n\n"));
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the sub function perform condition,NRC22*/
	/*
	 * Add code
	 * */

	/*Get Sub function id in SupportFunctionList index*/
	Index = Dsp_CheckSubFunctionIsSupport(Dsp_Services_0x10_SupportFunctionList,Dsp_UdsServiceCtrInfo[ChNo].SubFunc);

	/*Get P2Server and P2_Server parameters*/
	Dsl_GetSessionP2ServerMax(Index,&P2Server);
	Dsl_GetSessionP2_ServerMax(Index,&P2_Server);

	/*Perform function*/
	/*Set session type*/
	Dsl_SetSessionType(Dsp_UdsServiceCtrInfo[ChNo].SubFunc);
	/*Update Positive Response PDU*/
	Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_POSITIVE;
	Dsp_UdsServiceCtrInfo[ChNo].PosResDL = 0x04;
	Dsp_UdsServiceCtrInfo[ChNo].PosResData[0] =	(uint8)CommFunc_BitShiftRigth(P2Server,0x08);
	Dsp_UdsServiceCtrInfo[ChNo].PosResData[1] =	(uint8)P2Server;
	Dsp_UdsServiceCtrInfo[ChNo].PosResData[2] =	(uint8)CommFunc_BitShiftRigth(P2_Server,0x08);
	Dsp_UdsServiceCtrInfo[ChNo].PosResData[3] =	(uint8)P2_Server;

	/*reset dsl parameters*/
	/*
	 * add code
	 * */

	ret = E_OK;

	Dcm_Debug_OutputInfo(_T("DiagnosticSessionControl perform completed.......SubId = 0x%x\n",Dsp_UdsServiceCtrInfo[ChNo].SubFunc));

	return ret;
}

/****************************************************************************
 * @function	Dsp_ServicesFunction_ECUReset
 * @brief  		Diagnostic service $11 handling
 * @param  		ChNo : Input parameters,Bus Channel.
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_ECUReset(uint8 ChNo)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;

	/*Check the SID support in active session,NRC7F Check*/
	if(E_NOT_OK == Dsp_CheckServicesIsSupportInActiveSession(Dsp_Services_0x11_SupportFunctionList))
	{
		/*Check the request pdu type*/
		if(DCM_REQ_TYPE_FUNC == Dsp_UdsServiceCtrInfo[ChNo].ReqType)
		{
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NOTTXNRC;
			Dsp_UdsServiceCtrInfo[ChNo].NRC = 0x00;
		}
		else
		{
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NEGATIVE;
			Dsp_UdsServiceCtrInfo[ChNo].NRC = DCM_NRC_SNSIAS;
		}
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the SID support in active security level£¬NRC33 Check*/
	/*
	 * Add Code
	 * */

	/*Check the s perform condition,NRC22*/
	/*
	 * Add code
	 * */

	/*minimum length check,NRC13 Check*/
	if(Dsp_UdsServiceCtrInfo[ChNo].ReqDL < 0x02)
	{
		/*Response NRC13*/
		Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NEGATIVE;
		Dsp_UdsServiceCtrInfo[ChNo].NRC = DCM_NRC_IMLOIF;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the sub function support in active session,NRC7E Check*/
	if(E_NOT_OK == Dsp_CheckSubFunctionIsSupportInActiveSession(Dsp_Services_0x11_SupportFunctionList,Dsp_UdsServiceCtrInfo[0].SubFunc))
	{
		/*Check the request pdu type*/
		if(DCM_REQ_TYPE_FUNC == Dsp_UdsServiceCtrInfo[ChNo].ReqType)
		{
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NOTTXNRC;
			Dsp_UdsServiceCtrInfo[ChNo].NRC = 0x00;
		}
		else
		{
			Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_NEGATIVE;
			Dsp_UdsServiceCtrInfo[ChNo].NRC = DCM_NRC_SFNISAS;
		}

		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the sub function support in active security level£¬NRC33 Check*/
	/*
	 * Add Code
	 * */

	/*Check the sub function perform condition,NRC22*/
	/*
	 * Add code
	 * */

	/*Get Sub function id in SupportFunctionList index*/
	Index = Dsp_CheckSubFunctionIsSupport(Dsp_Services_0x10_SupportFunctionList,Dsp_UdsServiceCtrInfo[ChNo].SubFunc);

	/*Perform function*/
	/*Set session type*/
	Dsl_SetSessionType(Dsp_UdsServiceCtrInfo[ChNo].SubFunc);
	/*Update Positive Response PDU*/
	Dsp_UdsServiceCtrInfo[ChNo].ResType = DCM_RESPONSE_TYPE_POSITIVE;;
	Dsp_UdsServiceCtrInfo[ChNo].PosResDL  =	0x00;

	/*reset dsl parameters*/
	/*
	 * add code
	 * */

	ret = E_OK;

	return ret;
}

#endif /*_DCM_DSP_IMPLEMENT_H_*/
/*********************************File End*********************************/
