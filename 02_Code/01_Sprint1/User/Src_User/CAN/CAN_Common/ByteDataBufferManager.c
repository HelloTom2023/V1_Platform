#define _BYTEBUFFER_MAIN_C
#include "..\..\config\inc.h"

#define BYTEBUFFER_HEAD_H		0xff
#define BYTEBUFFER_HEAD_L		0xA5

void ByteDataBufferInit(ByteBufferMangerStruct *pByteBuffer, uint8_t *pDataBuffer, uint8_t DataBufferLength)
{
	pByteBuffer->BufferSize = DataBufferLength;
	pByteBuffer->Delta = 0;
	pByteBuffer->pDataBuffer = pDataBuffer;
	pByteBuffer->ReadPoint = 0;
	pByteBuffer->WritePoint = 0;
	pByteBuffer->MsgNum = 0;
}


void ByteDataBufferWriteByte(ByteBufferMangerStruct *pByteBuffer, uint8_t WrtData)
{
	uint8_t writepoint =  pByteBuffer->WritePoint;
	uint8_t *pBuffer = pByteBuffer->pDataBuffer;

	if(writepoint >= pByteBuffer->BufferSize)
	{
		writepoint = 0;
	}
	pBuffer[writepoint++] = WrtData;
	if(writepoint >= pByteBuffer->BufferSize)
	{
		writepoint = 0;
	}
	pByteBuffer->WritePoint = writepoint;
	pByteBuffer->Delta++;
}
uint8_t ByteDataBufferReadByte(ByteBufferMangerStruct *pByteBuffer, uint8_t *pReadByte)
{
	if((pByteBuffer ==NULL) ||(pReadByte == NULL))
	{
		return 2;
	}
	if(pByteBuffer->Delta > 0)
	{
		DI();
		*pReadByte = pByteBuffer->pDataBuffer[pByteBuffer->ReadPoint];
		pByteBuffer->ReadPoint++;
		pByteBuffer->Delta--;

		if(pByteBuffer->ReadPoint >= pByteBuffer->BufferSize)
		{
			pByteBuffer->ReadPoint = 0;
		}
		EI();
		return 0;
	}
	else
	{
		return 1;
	}
}
uint8_t ByteDataBufferWriteMsg(uint8_t *pDataBuffer, uint8_t DataLength, ByteBufferMangerStruct *pByteBuffer)
{

	uint8_t i = 0;
#if 0
	ByteDataBufferWriteByte(pByteBuffer, BYTEBUFFER_HEAD_H);
	ByteDataBufferWriteByte(pByteBuffer, BYTEBUFFER_HEAD_L);
#endif
	if(DataLength >MSG_BYTE_SIZE_MAX)
	{
		return 1;
	}
	i = MSG_BYTE_SIZE_MAX - pByteBuffer->Delta;	//计算BUFFER剩余空间
	if(i<(DataLength+1))
	{
		return 0;		//如果BUFFER 剩余空间不足以存储本包数据，则丢弃
	}
	ByteDataBufferWriteByte(pByteBuffer, DataLength);
	
	for(i = 0; i< DataLength; i++)
	{
		ByteDataBufferWriteByte(pByteBuffer, pDataBuffer[i]);
	}
	pByteBuffer->MsgNum++;
	return 0;
}


uint8_t ByteDataBufferGetByte(ByteBufferMangerStruct *pByteBuffer)
{
	uint8_t RetValue = pByteBuffer->pDataBuffer[pByteBuffer->ReadPoint];

	pByteBuffer->ReadPoint++;
	pByteBuffer->Delta--;

	if(pByteBuffer->ReadPoint >= pByteBuffer->BufferSize)
	{
		pByteBuffer->ReadPoint = 0;
	}

	return RetValue;
}
uint8_t ByteDataBufferReadMsg(uint8_t *pDataBuffer, uint8_t *pLen, ByteBufferMangerStruct *pByteBuffer)
{
	uint8_t i = 0;

	if(pByteBuffer->MsgNum == 0)
	{
		return 0;
	}
#if 0
	if(BYTEBUFFER_HEAD_H != ByteDataBufferGetByte(pByteBuffer))
	{
		/*search next header */
		return 0;
	}
	if(BYTEBUFFER_HEAD_L != ByteDataBufferGetByte(pByteBuffer))
	{
		/*search next header */
		return 0;
	}
#endif
	*pLen = ByteDataBufferGetByte(pByteBuffer);

	for(i = 0;i< *pLen; i++)
	{
		pDataBuffer[i] = ByteDataBufferGetByte(pByteBuffer);
	}
	DI();
	pByteBuffer->MsgNum --;
	EI();
	return *pLen;
}

