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
			}
			break;
		}

		case DCM_SERVICE_STATUS_RUN:
		{
			uint8 ret = E_NOT_OK;

			/*Call Services handler function*/
			ret = Dsp_ServicesFunction_Process();

			/*Check the diagnostic services process return value*/

			break;
		}

		case DCM_SERVICE_STATUS_COMPLETED:
		{
			/*update response PDU,and request send frame*/
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

	for(i = 0x00; ; )
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

		/*Check the list length*/
		if(i >= (sizeof(Dsp_SupportServiceList) / sizeof(Dcm_SupportServiceList_Struct_Type)) )
		{
			return 0xff;
		}
		else
		{
			/*Doing nothing*/
		}

		/*Loop control*/
		i++;
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

	for(i = 0x00; ; )
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

		/*Check the list length*/
		if(i >= (sizeof(ptr_Dcm_SubFunctionList) / sizeof(Dcm_SupportSubFunctionList_Struct_Type)) )
		{
			return 0xff;
		}
		else
		{
			/*Doing nothing*/
		}

		/*Loop control*/
		i++;
	}
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

	for(i = 0x00; ; )
	{
		/*Check if the list ends*/
		if(ptr_Dcm_SubFunctionList[i].Index == 0xFF)
		{
			ret = E_OK;
		}
		else
		{
			/*Doing nothing*/
		}

		/*Check the list length*/
		if(i >= (sizeof(ptr_Dcm_SubFunctionList) / sizeof(Dcm_SupportSubFunctionList_Struct_Type)) )
		{
			ret = E_OK;
		}
		else
		{
			/*Doing nothing*/
		}

		/*Get MASK*/
		*ptr_SesTypeMask |= ptr_Dcm_SubFunctionList[i].SupportSeesion;

		/*Loop control*/
		i++;
	}
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
			/*Doing nothing*/
		}

		/*Check the list length*/
		if(i >= (sizeof(ptr_Dcm_SubFunctionList) / sizeof(Dcm_SupportSubFunctionList_Struct_Type)) )
		{
			ret = E_OK;
		}
		else
		{
			/*Doing nothing*/
		}

		/*Get MASK*/
		*ptr_SecLevelMask |= ptr_Dcm_SubFunctionList[i].SupportSecurityLevel;

		/*Loop control*/
		i++;
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

	switch(Dsp_SupportServiceList[Dsp_UdsServiceCtrInfo.Index].SI)
	{
		case DCM_SID_DSC:
		{
			break;
		}

		case DCM_SID_ER:
		{
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
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_DiagnosticSessionControl(void)
{
	uint8 ret = E_NOT_OK;
	uint8 Index = 0x00;
	uint8 CurrentSesType = 0x00;
	uint8 ServiceSesTypeMask = 0x00;

	/*Get currents session type*/
	Dsl_GetSeesionType(&CurrentSesType);

	/*Get currents session in the Dsp_Services_0x10_SupportFunctionList index*/
	Index = Dsp_CheckSubFunctionIsSupport(Dsp_Services_0x10_SupportFunctionList,CurrentSesType);
	/*get services session types mask*/
	Dsp_GetServicesSessionTypeMask(Dsp_Services_0x10_SupportFunctionList,&ServiceSesTypeMask);

	/*Check ths SID support in active session,NRC7F Check*/

	if(0x00 == (CommFunc_GetBitMask(Index) & ServiceSesTypeMask))
	{
		/*the service not support this session,shall be response NRC7F*/
		/*Response NRC7F*/
	}
	else
	{
		/*Doing nothing*/
	}

	/*minimum length check,NRC13 Check*/
	if(Dcm_ReqPDU.DataLength < 0x02)
	{
		/*Response NRC13*/
	}
	else
	{
		/*Doing nothing*/
	}

	return ret;
}


#endif /*_DCM_DSP_IMPLEMENT_H_*/
/*********************************File End*********************************/
