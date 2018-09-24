/***********************( Copyright infomation )********************************
 * FILE      :
 * INFOMATIN :
 * VERSION   : v00
 * DATA      : 22/03, 2013
 * AUTHOR    : yangyan
 *
 * UPDATE    :
 * ---------------------------------------------
 *   | INFOMATION
 *   | VERSION
 *   | AUTHOR
 *   -------------------------------------------
 *     |  ......
 *     |  
 ******************************************************************************/

#define _PRINT_C_
#include "..\config\inc.h"


void  API_LoopDleay(uint16_t n)
{
   while(n--)
   {
       CLEAR_WATCHDOG();
   }
}

uint8_t API_MemCompare(uint8_t* pSrc,uint8_t* pTarg,uint16_t cSize)
{
    uint16_t i;
    for(i = 0; i < cSize ; i++)
    {
        if((*pSrc++) != (*pTarg++))return FALSE;
    }
    return TRUE;
}



void API_MemCopy(uint8_t* pSrc,uint8_t* pTarg,uint16_t cSize)
{
    uint16_t i;
    for (i = 0; i < cSize ; i++)
    {
        (*pTarg++) = ((*pSrc++));
    }
}





void API_MemClear(uint8_t * pMemery,uint16_t cSize)
{
    uint16_t i;
    for (i = 0; i < cSize ; i++)
    {
        (*pMemery++) = 0;
    }
}




uint16_t API_StrLen(uint8_t* pStr,uint16_t cMax)
{
    uint16_t i = 0;
    while(*pStr)
    {
        i++;
        pStr++;
        if(i >= cMax)break;
    }
    return i;
}




const uint8_t Hex[] = "0123456789ABCDEF";

void API_Int2Str(uint8_t* pStr, uint16_t cVal,uint8_t cLen,eDIGIT_TYPE eDataType )
{
    uint8_t i;
    long cBase;

    cBase = 1;
    for (i = 0; i < (cLen - 1); i++) {
        cBase *=(uint8_t)eDataType;
    }


    while (cBase > 0) {
        i=Hex[cVal / cBase];
        *pStr++ = i;
        cVal %= cBase;
        cBase  /= (uint8_t)eDataType;
    }
    *pStr ='\0';
}


////////////////////////////////////////////////////////////////////////////////
// 更新信息 : yangyan 08-12-02
// 函数名   :
// 功能描述 :
// 参数表   :
// 输出     :
//          ------------------------------------------
//          更新信息 :
//           ......
////////////////////////////////////////////////////////////////////////////////

#if D_PRINT_EN
#define _outchar cpu_putc


//void API_DbgPrintf( const char *pcFormat,...)
void _T( const char *pcFormat,...)
{ 
    va_list oPraList;  
    
    char  cData;
    char  cIdx;
    long  lValue;
    uint8_t cLen;
    uint8_t cCnt;
    uint32_t dwMask=1;

    //得到参数结构
    va_start(oPraList, pcFormat);

    while(1) 
    {
        
        //找出参数类型标示符 %
        switch( cData = *pcFormat++ ) 
        {
            case 0:
                goto DBG_END ;
            case '%':
                if( *pcFormat != '%' ) 
                {
                    break;
                }
                pcFormat++;
            case '\n':
                _outchar(0x0D);//插入一个回车键
            default:
                _outchar(cData);
                continue;
        }
        
        //取得参数的显示长度 如 %08x，显示长度为8
        
        cCnt = 0;
        cData = *pcFormat++;
        
        if( cData=='0' ) 
        {
            cData = *pcFormat++;
            cCnt = cData - '0';
            cData = *pcFormat++;
        }
        else if( cData>='0' && cData<='9' )
        {
            cCnt = cData - '0';
            cData = *pcFormat++;
        }
        
        //取得参数长度!(字节数)，默认 uint8_t,1字节
        
        cLen = 1;
        
        switch(cData)
        {
            case 'l':
            case 'L':
                cData = *pcFormat++; cLen = 4;
            break;
            case 'i':
            case 'I':
                cData = *pcFormat++; cLen = 2;
            break;
            default:
            break;
        }
        
        //取得参数值        
        switch( cData ) 
        {         
            case 'd':
            case 'u':
                switch (cLen) 
                {
                    case 1:
                         lValue = (uint8_t)va_arg( oPraList, uint8_t );
                    break;
                    
                    case 2:
                         lValue = (uint16_t)va_arg( oPraList, uint16_t );
                    break;
                    
                    case 4:
                         lValue = (uint32_t)va_arg( oPraList, uint32_t );
                    break;
                }
                
                if(cCnt==0) 
                {
                    if( lValue==0 ) { _outchar('0'); continue; }
                    
                    for(cCnt=0, dwMask=1; cCnt<12; cCnt++) 
                    {
                        if( (lValue/dwMask)==0 ) break;
                        
                        dwMask = dwMask*10;
                    }
                }
                
                for(cIdx=0, dwMask=1; cIdx<cCnt-1; cIdx++) dwMask = dwMask*10;
                
                while(1) 
                {
                    cData = (lValue / dwMask) + '0';
                    _outchar(cData);
                    
                    lValue = lValue % (dwMask);
                    dwMask = dwMask / 10;
                    
                    if( dwMask==0 )break;
                }
                
            continue;
            
            case 'x':
            case 'X':
            
                switch (cLen) 
                {
                    case 1: lValue = (uint8_t)va_arg( oPraList, uint8_t ); break;
                    case 2: lValue = (uint16_t)va_arg( oPraList, uint16_t ); break;
                    case 4: lValue = (uint32_t)va_arg( oPraList, uint32_t ); break;
                }
                
                //if(cCnt==0) 
                    cCnt = cLen*2;
                
                for(cIdx=0; cIdx<cCnt; cIdx++) 
                {
                    _outchar(Hex[(lValue >> (cCnt-cIdx-1)*4) & 0x000f]);
                }
            continue;
                
            case 's':
                
                    lValue = (uint32_t)va_arg( oPraList, uint32_t );
                    while(*(char*)lValue!='\0') {_outchar(*(char*)lValue++);}
            continue;
    
            case 'c':
                lValue = va_arg( oPraList, char );
                _outchar(lValue);
            continue;
            
            default:
                lValue = (uint16_t)va_arg( oPraList, int );
            continue;
        }
    }

    //释放
    DBG_END:
    va_end( oPraList );

}


#endif //DEF_DBUG_EN


