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
				Dsp_UdsServiceCtrInfo.MachineState = DCM_SERVICE_STATUS_RUN;
			}
			break;
		}

		case DCM_SERVICE_STATUS_RUN:
		{
			/*Call Services handler function,and check return value*/

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
		/*Check the SID*/
		if(Dsp_SupportServiceList[i].SI == SID)
		{
			return i;
		}
		else if(Dsp_SupportServiceList[i].SI == 0xFF)
		{
			return 0xff;
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
 * @function	Dsp_ServicesFunction_0x10
 * @brief  		NULL
 * @param  		NULL
 * @retval 		NULL
 * @attention   NULL
****************************************************************************/
DCM_LOCAL_API uint8 Dsp_ServicesFunction_0x10(void)
{
	uint8 ret = E_NOT_OK;

	/**/

}




#endif /*_DCM_DSP_IMPLEMENT_H_*/
/*********************************File End*********************************/
