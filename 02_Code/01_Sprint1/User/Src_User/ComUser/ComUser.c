/****************************************************************************
* File Name : ComUser.c
*
* Modules : Communication user modules source file
*
* Summary : 1.handle application message
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

/*Include head files AREA*/
#include "ComUser.h"



/*Macro definition AREA*/




/*Variable declaration AREA*/


/*Function implement AREA*/
/****************************************************************************
 * @function	ComUser_Init
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_Init(void)
{

}

/****************************************************************************
 * @function	ComUser_MainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_MainFunction(void)
{
	ComUser_RxMainFunction();
	ComUser_TxMainFunction();
}

/****************************************************************************
 * @function	ComUser_RxMainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
uint8 Dvr_CurrentPage_bk = 0x00;
uint8 Dvr_TotalPage_bk = 0x00;
uint8 ReadSignalRet_Dvr_CurrentPage_bk = 0x00;
uint8 ProcessCounter = 0x00;
COM_USER_EXTERN_API void ComUser_RxMainFunction(void)
{
	/*Send signal*/
	static uint8 DVD_DVR_CommandList = 0x00;
	/*Recv signal */
	uint8 Dvr_CurrentPage = 0x00;
	uint8 Dvr_TotalPage = 0x00;
	uint8 ReadSignalRet_Dvr_CurrentPage = 0x00;


	/*Read DVR_CurrentPage signal value*/
	ReadSignalRet_Dvr_CurrentPage = ComUser_Com_ReadRxSignalCh0(0x612,56,8,&Dvr_CurrentPage);
	/*Read DVR_TotalPage signal value*/
	ComUser_Com_ReadRxSignalCh0(0x612,48,8,&Dvr_TotalPage);

	if(ReadSignalRet_Dvr_CurrentPage_bk != ReadSignalRet_Dvr_CurrentPage)
	{
		ReadSignalRet_Dvr_CurrentPage_bk = ReadSignalRet_Dvr_CurrentPage;

		if(0x0a == ReadSignalRet_Dvr_CurrentPage)
		{
			ComUser_Debug_OutputInfo(_T("Message DVR612 is timeout!!!\n"));
			ComUser_Debug_OutputInfo(_T("timeout value : Dvr_CurrentPage = %x\n",Dvr_CurrentPage));
		}
		else
		{
			/*Doing nothing*/
		}
	}
	else
	{
		/*Doing nothing*/
	}

	ProcessCounter++;
	if(ProcessCounter >= 250)
	{
		ProcessCounter = 0x00;
		ComUser_Debug_OutputInfo(_T("Signal value : Dvr_TotalPage = %d,Dvr_CurrentPage = %d,ReadSignalRet_Dvr_CurrentPage = %x\n",\
				Dvr_TotalPage,Dvr_CurrentPage,ReadSignalRet_Dvr_CurrentPage));
	}

	if((Dvr_CurrentPage_bk != Dvr_CurrentPage) || (Dvr_TotalPage_bk != Dvr_TotalPage))
	{
		DVD_DVR_CommandList++;

		Dvr_CurrentPage_bk = Dvr_CurrentPage;
		Dvr_TotalPage_bk = Dvr_TotalPage;
		ComUser_Debug_OutputInfo(_T("Recv Signal : Dvr_TotalPage = %d,Dvr_CurrentPage = %d\n",Dvr_TotalPage,Dvr_CurrentPage));

		ComUser_Com_ImmediatelyWriteTxSignalCh0(0x2F8,18,6,&DVD_DVR_CommandList);

		ComUser_Debug_OutputInfo(_T("Send Signal : DVD_DVR_CommandList = %d \n",DVD_DVR_CommandList));
	}
}

/****************************************************************************
 * @function	ComUser_RxMainFunction
 * @brief  		NULL
 * @param		NULL
 * @retval		NULL
 * @attention   NULL
****************************************************************************/
COM_USER_EXTERN_API void ComUser_TxMainFunction(void)
{

}

/*********************************File End*********************************/
