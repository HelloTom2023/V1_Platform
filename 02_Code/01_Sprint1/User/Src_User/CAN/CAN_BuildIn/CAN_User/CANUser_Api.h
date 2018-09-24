#ifndef _CANUSER_COMM_API_
#define _CANUSER_COMM_API_

#define CAN_PRJ_SID		0xff

#pragma pack(1)
/*------------------USER PROJECT SPECIAL COMMUNICATION PROTOCOL-------------------*/
/*------------------START ZONE------------------------------------------------------*/
typedef struct
{
	uint8_t LENGTH;
	uint8_t SID;
//	uint8_t PRJ;
	uint8_t UserID;		// user defined ID.
	uint8_t Data1;
	uint8_t Data2;
}UserPrjDemoDataStruct;
/*------------------USER PROJECT SPECIAL COMMUNICATION PROTOCOL-------------------*/
/*------------------END ZONE-------------------------------------------------------*/
#pragma pack(4)

extern void   CANUser_ApiInit(void);
extern void *pCANUser_GetApi(uint8_t param);

#endif
