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
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API void Dsp_MainFunction(void)
{
	switch(Dsp_UdsServiceCtrInfo.MachineState)
	{
		case DCM_SERVICE_STATUS_IDLE:
		{
			/*doing nothing*/
			break;
		}

		case DCM_SERVICE_STATUS_REQ:
		{
			Dcm_Debug_OutputInfo(_T("Dsp received Request PDU,SID = 0x%x\n",Dsp_UdsServiceCtrInfo.SI));
			/*Check the service id is define in this version*/
			Dsp_UdsServiceCtrInfo.Index = Dsp_CheckServicesIsSupport(Dsp_UdsServiceCtrInfo.SI);
			if(0xFF == Dsp_UdsServiceCtrInfo.Index)
			{
				/*Response NRC11 serviceNotSupported*/
			}
			else
			{
				/*notification DCM PDU to application layer and check the notification result*/
				Dsp_UdsServiceCtrInfo.MachineState = DCM_SERVICE_STATUS_RUN;
				Dcm_Debug_OutputInfo(_T("SID check OK,will perform diagnostic services...\n\n"));
			}
			break;
		}

		case DCM_SERVICE_STATUS_RUN:
		{
			uint8 ret = E_NOT_OK;

			Dcm_Debug_OutputInfo(_T("Perform diagnostic services in the time....SID = 0x%x\n\n",Dsp_UdsServiceCtrInfo.SI));

			/*Call Services handler function*/
			ret = Dsp_ServicesFunction_Process();
			/*Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_POSITIVE;
			Dcm_PosResPDU.SI = Dcm_ReqPDU.SI;
			Dcm_PosResPDU.SubFunc = Dcm_ReqPDU.SubFunc;
			Dcm_PosResPDU.DataLength = 0x04;
			Dcm_PosResPDU.Data[0] =	0x31;
			Dcm_PosResPDU.Data[1] =	0x32;
			Dcm_PosResPDU.Data[2] =	0x33;
			Dcm_PosResPDU.Data[3] =	0x34;*/

			/*Check the diagnostic services process return value*/
			if((E_OK == ret) || (E_NOT_OK == ret))
			{
				Dsp_UdsServiceCtrInfo.MachineState = DCM_SERVICE_STATUS_COMPLETED;
			}
			else
			{
				/*Doing nothing*/
			}
			break;
		}

		case DCM_SERVICE_STATUS_COMPLETED:
		{
			Dcm_Debug_OutputInfo(_T("DCM_SERVICE_STATUS_COMPLETED....SID = 0x%x\n\n",Dsp_UdsServiceCtrInfo.SI));
			/*Check the response type*/
			if(DCM_RESPONSE_TYPE_POSITIVE == Dsp_UdsServiceCtrInfo.ResType)
			{
				/*update response PDU,and request send frame*/
				Dsp_TxDiagResponsePositivePDU();
				Dsp_UdsServiceCtrInfo.MachineState = DCM_SERVICE_STATUS_IDLE;
			}
			else if(DCM_RESPONSE_TYPE_NEGATIVE == Dsp_UdsServiceCtrInfo.ResType)
			{
				Dsp_UdsServiceCtrInfo.MachineState = DCM_SERVICE_STATUS_IDLE;
			}
			else if(DCM_RESPONSE_TYPE_NOTTXNRC == Dsp_UdsServiceCtrInfo.ResType)
			{
				Dsp_UdsServiceCtrInfo.MachineState = DCM_SERVICE_STATUS_IDLE;
			}

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
 * @param  		NULL
 * @retval 		ret : function execute result
 * @attention   null
****************************************************************************/
DCM_EXTERN_API uint8 Dsp_TxDiagResponsePositivePDU(void)
{
	uint8 Data[128]= {0x00};

	Data[0] = Dcm_PosResPDU.SI + 0x40;
	Data[1] = Dcm_PosResPDU.SubFunc;
	memcpy(&Data[2],Dcm_PosResPDU.Data,Dcm_PosResPDU.DataLength);

	Dcm_TxDiagResponseInfo(0x00, Dcm_PosResPDU.DataLength+2, Data);
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
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_Process(void)
{
	uint8 ret = E_NOT_OK;

	switch(Dsp_UdsServiceCtrInfo.SI)
	{
		case DCM_SID_DSC:
		{
			ret = Dsp_ServicesFunction_DiagnosticSessionControl();
			break;
		}

		case DCM_SID_ER:
		{
			ret = Dsp_ServicesFunction_ECUReset();
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
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_DiagnosticSessionControl(void)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint16 P2Server = 0x00;
	uint16 P2_Server = 0x00;

	Dcm_Debug_OutputInfo(_T("Start Run DiagnosticSessionControl Service.......SubId = 0x%x\n",Dcm_ReqPDU.SubFunc));

	/*Check the SID support in active session,NRC7F Check*/
	if(E_NOT_OK == Dsp_CheckServicesIsSupportInActiveSession(Dsp_Services_0x10_SupportFunctionList))
	{
		/*Check the request pdu type*/
		if(DCM_REQ_TYPE_FUNC == Dsp_UdsServiceCtrInfo.ReqType)
		{
			Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NOTTXNRC;
			Dcm_NegResPDU.NRC = 0x00;
		}
		else
		{
			Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NEGATIVE;
			Dcm_NegResPDU.NRC = DCM_NRC_SNSIAS;
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
	if(Dcm_ReqPDU.DataLength < 0x02)
	{
		/*Response NRC13*/
		Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NEGATIVE;
		Dcm_NegResPDU.NRC = DCM_NRC_IMLOIF;
		return ret;
		Dcm_Debug_OutputInfo(_T("NRC13\n\n"));
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the sub function support in active session,NRC7E Check*/
	if(E_NOT_OK == Dsp_CheckSubFunctionIsSupportInActiveSession(Dsp_Services_0x10_SupportFunctionList,Dcm_ReqPDU.SubFunc))
	{
		/*Check the request pdu type*/
		if(DCM_REQ_TYPE_FUNC == Dsp_UdsServiceCtrInfo.ReqType)
		{
			Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NOTTXNRC;
			Dcm_NegResPDU.NRC = 0x00;
		}
		else
		{
			Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NEGATIVE;
			Dcm_NegResPDU.NRC = DCM_NRC_SFNISAS;
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
	Index = Dsp_CheckSubFunctionIsSupport(Dsp_Services_0x10_SupportFunctionList,Dcm_ReqPDU.SubFunc);
	/*Get P2Server and P2*Server parameters*/
	switch(Index)
	{
		case 0x00:
		{
			P2Server = Dsp_GetSessionP2ServerMax(0);
			P2_Server = Dsp_GetSessionP2_ServerMax(0);
			break;
		}
		case 0x01:
		{
			P2Server = Dsp_GetSessionP2ServerMax(1);
			P2_Server = Dsp_GetSessionP2_ServerMax(1);
			break;
		}
		case 0x02:
		{
			P2Server = Dsp_GetSessionP2ServerMax(2);
			P2_Server = Dsp_GetSessionP2_ServerMax(2);
			break;
		}
		case 0x03:
		{
			P2Server = Dsp_GetSessionP2ServerMax(3);
			P2_Server = Dsp_GetSessionP2_ServerMax(3);
			break;
		}
		case 0x04:
		{
			P2Server = Dsp_GetSessionP2ServerMax(4);
			P2_Server = Dsp_GetSessionP2_ServerMax(4);
			break;
		}
		case 0x05:
		{
			P2Server = Dsp_GetSessionP2ServerMax(5);
			P2_Server = Dsp_GetSessionP2_ServerMax(5);
			break;
		}
		case 0x06:
		{
			P2Server = Dsp_GetSessionP2ServerMax(6);
			P2_Server = Dsp_GetSessionP2_ServerMax(6);
			break;
		}
		case 0x07:
		{
			P2Server = Dsp_GetSessionP2ServerMax(7);
			P2_Server = Dsp_GetSessionP2_ServerMax(7);
			break;
		}
		default:
		{
			return ret;
		}
	}

	/*Perform function*/
	/*Set session type*/
	Dsl_SetSessionType(Dcm_ReqPDU.SubFunc);
	/*Update Positive Response PDU*/
	Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_POSITIVE;
	Dcm_PosResPDU.SI = Dcm_ReqPDU.SI;
	Dcm_PosResPDU.SubFunc = Dcm_ReqPDU.SubFunc;
	Dcm_PosResPDU.DataLength = 0x04;
	Dcm_PosResPDU.Data[0] =	(uint8)CommFunc_BitShiftRigth(P2Server,0x08);
	Dcm_PosResPDU.Data[1] =	(uint8)P2Server;
	Dcm_PosResPDU.Data[2] =	(uint8)CommFunc_BitShiftRigth(P2_Server,0x08);
	Dcm_PosResPDU.Data[3] =	(uint8)P2_Server;

	/*reset dsl parameters*/
	/*
	 * add code
	 * */

	ret = E_OK;

	Dcm_Debug_OutputInfo(_T("DiagnosticSessionControl perform completed.......SubId = 0x%x\n",Dcm_ReqPDU.SubFunc));

	return ret;
}

/****************************************************************************
 * @function	Dsp_ServicesFunction_ECUReset
 * @brief  		Diagnostic service $11 handling
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_ECUReset(void)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;

	/*Check the SID support in active session,NRC7F Check*/
	if(E_NOT_OK == Dsp_CheckServicesIsSupportInActiveSession(Dsp_Services_0x11_SupportFunctionList))
	{
		/*Check the request pdu type*/
		if(DCM_REQ_TYPE_FUNC == Dsp_UdsServiceCtrInfo.ReqType)
		{
			Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NOTTXNRC;
			Dcm_NegResPDU.NRC = 0x00;
		}
		else
		{
			Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NEGATIVE;
			Dcm_NegResPDU.NRC = DCM_NRC_SNSIAS;
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
	if(Dcm_ReqPDU.DataLength < 0x02)
	{
		/*Response NRC13*/
		Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NEGATIVE;
		Dcm_NegResPDU.NRC = DCM_NRC_IMLOIF;
		return ret;
	}
	else
	{
		/*Doing nothing*/
	}

	/*Check the sub function support in active session,NRC7E Check*/
	if(E_NOT_OK == Dsp_CheckSubFunctionIsSupportInActiveSession(Dsp_Services_0x11_SupportFunctionList,Dcm_ReqPDU.SubFunc))
	{
		/*Check the request pdu type*/
		if(DCM_REQ_TYPE_FUNC == Dsp_UdsServiceCtrInfo.ReqType)
		{
			Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NOTTXNRC;
			Dcm_NegResPDU.NRC = 0x00;
		}
		else
		{
			Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_NEGATIVE;
			Dcm_NegResPDU.NRC = DCM_NRC_SFNISAS;
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
	Index = Dsp_CheckSubFunctionIsSupport(Dsp_Services_0x10_SupportFunctionList,Dcm_ReqPDU.SubFunc);

	/*Perform function*/
	/*Set session type*/
	Dsl_SetSessionType(Dcm_ReqPDU.SubFunc);
	/*Update Positive Response PDU*/
	Dsp_UdsServiceCtrInfo.ResType = DCM_RESPONSE_TYPE_POSITIVE;
	Dcm_PosResPDU.SI = Dcm_ReqPDU.SI;
	Dcm_PosResPDU.SubFunc = Dcm_ReqPDU.SubFunc;
	Dcm_PosResPDU.DataLength  =	0x00;

	/*reset dsl parameters*/
	/*
	 * add code
	 * */

	ret = E_OK;

	return ret;
}

#endif /*_DCM_DSP_IMPLEMENT_H_*/
/*********************************File End*********************************/
