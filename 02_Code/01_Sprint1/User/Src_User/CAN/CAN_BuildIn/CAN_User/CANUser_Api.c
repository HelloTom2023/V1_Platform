#include  "..\..\config\inc.h"
UserPrjDemoDataStruct UserDemoData;

void CANUser_ApiInit(void)
{
	UserDemoData.LENGTH = sizeof(UserPrjDemoDataStruct);
	UserDemoData.SID = OP_CAN_TX_PRJ_SPCL;
	UserDemoData.UserID = 0x01;
	UserDemoData.Data1 = 0X10;
	UserDemoData.Data2 = 0x20;
}

void *pCANUser_GetApi(uint8_t param)
{
	void *ptr = NULL;

	switch(param)
	{
		case 0x01:
			ptr = &UserDemoData;
			break;
		default:
			break;
	}
	return ptr;
}
