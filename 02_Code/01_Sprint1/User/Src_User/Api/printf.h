#ifndef _PRINT_H_
#define _PRINT_H_

#ifdef _PRINT_C_
#define _PRINT_
#else 
#define _PRINT_    extern
#endif
typedef enum{
     DIGIT_TYPE_HEX = 16,
     DIGIT_TYPE_BCD = 10,
     DIGIT_TYPE_OCT = 8,
     DIGIT_TYPE_BIN = 2
}eDIGIT_TYPE;

typedef struct {
    uint8_t  max;
    uint8_t  cHead;
    uint8_t  cTail;
    uint8_t* p_cBuff;
}ring_buf_t;

extern const uint8_t Hex[];
_PRINT_ uint8_t  API_MemCompare ( uint8_t* pSrc,uint8_t* pTarg,uint16_t cSize );
_PRINT_ void   API_MemCopy    ( uint8_t* pSrc,uint8_t* pTarg,uint16_t cSize );
_PRINT_ void   API_MemClear   ( uint8_t* pMemery,uint16_t cSize );
_PRINT_ uint16_t API_StrLen     (uint8_t* pStr,uint16_t cMax);

_PRINT_ void   API_Int2Str    ( uint8_t* pStr,uint16_t cVal,uint8_t cLen,eDIGIT_TYPE eDataType );
_PRINT_ void   API_LoopDleay  (uint16_t n);


#if D_PRINT_EN 
_PRINT_ void _T( const char *pcFormat,... );
//_PRINT_ void API_DbgPrintf( const char *pcFormat,... );
//#define tr_printf(str)      API_DbgPrintf ## str //API_DbgPrintf //##连接符支持太差
//#define tr_printf(...)      API_DbgPrintf(__VA_ARGS__)           //也不支持c99规范
//根本原因就是编译器宏不支持可变参数
#if D_TEST_EN
//#define TEST           tr_printf //(API_DbgPrintf ## str)//
//#define ERROR          tr_printf //(API_DbgPrintf ## str)//
#define TEST(x)            x //(API_DbgPrintf ## str)//
#define ERROR(x)         x //(API_DbgPrintf ## str)//
#else
#define ERROR(str)
#define TEST(str)  
#endif


#else
#define tr_printf(str)  
#define tr_printf(str)  
#define TEST(str)   
#define ERROR(str)    

#endif
#endif


