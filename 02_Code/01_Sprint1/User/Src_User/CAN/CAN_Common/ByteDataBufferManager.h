#ifndef _BYTE_BUFFER_MANAGER_H
#define _BYTE_BUFFER_MANAGER_H

#ifdef _BYTEBUFFER_MAIN_C
#define BYTEBUFF_EXTN
#else
#define BYTEBUFF_EXTN     extern
#endif

#define MSG_STATE_IDLE		0
#define MSG_STATE_READY		1


#define MSG_BYTE_SIZE_MAX	 100

typedef struct
{
	uint8_t  MsgNum;
	uint8_t  ReadPoint;
	uint8_t  WritePoint;
	uint8_t  Delta;
	uint8_t  BufferSize;
	uint8_t *pDataBuffer;
} ByteBufferMangerStruct;
BYTEBUFF_EXTN void 	ByteDataBufferInit(ByteBufferMangerStruct *pByteBuffer, uint8_t *pDataBuffer, uint8_t DataBufferLength);
BYTEBUFF_EXTN uint8_t ByteDataBufferWriteMsg(uint8_t *pDataBuffer, uint8_t DataLength, ByteBufferMangerStruct *pByteBuffer);
BYTEBUFF_EXTN uint8_t ByteDataBufferReadMsg(uint8_t *pDataBuffer, uint8_t *pLen, ByteBufferMangerStruct *pByteBuffer);
BYTEBUFF_EXTN uint8_t ByteDataBufferReadByte(ByteBufferMangerStruct *pByteBuffer, uint8_t *pReadByte);
BYTEBUFF_EXTN void 	ByteDataBufferWriteByte(ByteBufferMangerStruct *pByteBuffer, uint8_t WrtData);

#endif

