#include "..\config\inc.h"
#include "TestCase.h"


typedef enum{
	MEDIA_COMM_TEST_NONE,
	MEDIA_COMM_TEST_TXRX,
	MEDIA_COMM_TEST_ACK,
	MEDIA_COMM_TEST_PARITY,
	MEDIA_COMM_TEST_PRESS,
}eMEDIA_COMM_TEST_STEP;


TEST_CASE_STR	MDITestCase;

void MDI_TestInit(void)
{

	MDITestCase.Count = 0;
	MDITestCase.Mode = MEDIA_COMM_TEST_NONE;
	MDITestCase.param = 0;
	MDITestCase.Step = 0;
	MDITestCase.Timer = 0;
	
}

void MDI_TestControl(uint8_t enable)
{
	MDI_TestInit();
	if(enable)
	{
		MDITestCase.Mode = MEDIA_COMM_TEST_TXRX;
	}
	else
	{
		MDITestCase.Mode = MEDIA_COMM_TEST_NONE;
	}
}

void MDI_TestRoutine(void)
{
	if(MDITestCase.Timer>0)
	{
		MDITestCase.Timer--;
		return;
	}
	switch(MDITestCase.Mode)
	{
		case MEDIA_COMM_TEST_TXRX:
			switch(MDITestCase.Step)
			{
				case 0:
					TCase_debug(_T("MDI Comm Test Start!\n"));
					MDI_DriverInit();
					_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
					MDITestCase.Mode++;
					MDITestCase.Timer = 500;
					MDITestCase.Step = 0;
					break;
				case 1:
					break;
				default:
					break;
			}
			
			break;
		case MEDIA_COMM_TEST_ACK:
			
			switch(MDITestCase.Step)
			{
				case 0:
					TCase_debug(_T("MDI ACK Test Start!\n"));
					MDI_DriverInit();
					MDITestCase.param = BIT0;
					_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
					MDITestCase.Step = 1;
					MDITestCase.Timer = 6000;
					break;
				case 1:
					MDITestCase.param = 0;
					TCase_debug(_T("MDI ACK Test Recovery\n"));
					_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
					MDITestCase.Step = 0;
					MDITestCase.Mode++;
					MDITestCase.Timer = 500;
					break;
				default:
					break;
			}
			break;
		case MEDIA_COMM_TEST_PARITY:
			switch(MDITestCase.Step)
			{
				case 0:
					TCase_debug(_T("MDI PARITY Test Start!\n"));
					MDI_DriverInit();
					MDITestCase.param = BIT1;
					_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
					MDITestCase.Step = 1;
					MDITestCase.Timer = 5000;
					break;
				case 1:
					MDITestCase.param = 0;
					TCase_debug(_T("MDI PARITY Recovery\n"));
					_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
					MDITestCase.Step = 0;
					MDITestCase.Mode++;
					MDITestCase.Timer = 500;
					break;
				default:
					break;
			}
			break;
		case MEDIA_COMM_TEST_PRESS:
			switch(MDITestCase.Step)
			{
				case 0:
					TCase_debug(_T("MDI Press Test Start-100ms!\n"));
					MDI_DriverInit();
					_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
					MDITestCase.Step = 1;
					MDITestCase.Timer = 100;
					MDITestCase.Count = 1;
					break;
				case 1:
					if(MDITestCase.Count<100)
					{
						MDITestCase.Count++;
						_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
						MDITestCase.Timer = 100;
					}
					else
					{
						MDITestCase.Step = 2;
						TCase_debug(_T("MDI Press Test-10ms!\n"));
						MDITestCase.Count = 1;
						_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
						MDITestCase.Timer = 10;
					}
					break;
				case 2:
					if(MDITestCase.Count<100)
					{
						MDITestCase.Count++;
						_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
						MDITestCase.Timer = 10;
					}
					else
					{
						MDITestCase.Step = 3;
						TCase_debug(_T("MDI Press Test-5ms!\n"));
						MDITestCase.Count = 1;
						_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
						MDITestCase.Timer = 5;
					}
					break;
				case 3:
					if(MDITestCase.Count<100)
					{
						MDITestCase.Count++;
						_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
						MDITestCase.Timer = 5;
					}
					else
					{
						MDITestCase.Step = 4;
						TCase_debug(_T("MDI Press Test-2ms!\n"));
						MDITestCase.Count = 1;
						_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
						MDITestCase.Timer = 2;
					}
					break;
				case 4:
					if(MDITestCase.Count<100)
					{
						MDITestCase.Count++;
						_SendFullMsgToMedia(MS_UI_UPLOAD_INFO, OP_INFO_QUERY_APU_STATE, 0, 0, 0, 0);
						MDITestCase.Timer = 2;
					}
					else
					{
						MDITestCase.Mode = MEDIA_COMM_TEST_NONE;
						MDITestCase.Count = 0;
						MDITestCase.Step = 0;
						TCase_debug(_T("MDI Test Over!\n"));
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

