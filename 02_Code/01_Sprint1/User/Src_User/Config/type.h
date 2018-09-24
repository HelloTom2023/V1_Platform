#ifndef _TYPE_H_
#define _TYPE_H_

#ifndef NULL
#define NULL          ((void*)0)
#endif

#ifndef null
#define null          ((void*)0)
#endif


#define TRUE          1
#define FALSE         0
#define true          1
#define false         0

#define ON            1
#define OFF           0
#define SET           1
#define CLR           0
#define HIGH          1
#define LOW           0   
#define VALID         1
#define INVALID       0
#define ENABLE        1
#define DISABLE       0


typedef void (* pFunc) (void);

typedef enum{
    BIT0  =0x01,
    BIT1  =0x02,
    BIT2  =0x04,
    BIT3  =0x08,
    BIT4  =0x10,
    BIT5  =0x20,
    BIT6  =0x40,
    BIT7  =0x80
}BYTE_POS;

#define _BIT0_    0x0001
#define _BIT1_    0x0002
#define _BIT2_    0x0004
#define _BIT3_    0x0008
#define _BIT4_    0x0010
#define _BIT5_    0x0020
#define _BIT6_    0x0040
#define _BIT7_    0x0080    
#define _BIT8_    0x0100
#define _BIT9_    0x0200
#define _BIT10_   0x0400
#define _BIT11_   0x0800
#define _BIT12_   0x1000
#define _BIT13_   0x2000
#define _BIT14_   0x4000
#define _BIT15_   0x8000

#define SET_BIT(byte,bitpos)       ((byte)|=(bitpos))
#define CLR_BIT(byte,bitpos)       ((byte)&=(~(bitpos)))
#define GET_BIT(byte,bitpos)       ((byte)&(bitpos))
#define GRT_RBIT(byte,bitpos)      ((byte)&(~(bitpos)))

#define SET_NBIT(byte,num)         ((byte)|=(1<<(num)))
#define CLR_NBIT(byte,num)         ((byte)&=(~(1<<(num))))
#define GET_NBIT(byte,num)         ((byte)&(1<<(num)))
#define GET_NRBIT(byte,num)        ((byte)&(~(1<<(num))))

#define SET_BIT_0(byte)            ((byte)|=(0x01))
#define SET_BIT_1(byte)            ((byte)|=(0x02))
#define SET_BIT_2(byte)            ((byte)|=(0x04))
#define SET_BIT_3(byte)            ((byte)|=(0x08))
#define SET_BIT_4(byte)            ((byte)|=(0x10))
#define SET_BIT_5(byte)            ((byte)|=(0x20))
#define SET_BIT_6(byte)            ((byte)|=(0x40))
#define SET_BIT_7(byte)            ((byte)|=(0x80))


#define MAX(x,y)                   ( ((x) > (y)) ? (x) : (y) )

#if 0
//typedef-----------------------------------------------------------------------
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed long  const sc32;  /* Read Only */
typedef signed short const sc16;  /* Read Only */
typedef signed char  const sc8;   /* Read Only */

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile signed long  const vsc32;  /* Read Only */
typedef volatile signed short const vsc16;  /* Read Only */
typedef volatile signed char  const vsc8;   /* Read Only */

typedef volatile unsigned long  vulong;
typedef volatile unsigned short vushort;
typedef volatile unsigned char  vuchar;

typedef unsigned long  ulong;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned char  bool;

typedef unsigned long  DWORD;
typedef unsigned short WORD;
typedef unsigned char  BYTE;

typedef unsigned long  u32;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

typedef unsigned long  UINT32;
typedef unsigned short UINT16;
typedef unsigned char  UINT8;


typedef unsigned long  const uc32;  /* Read Only */
typedef unsigned short const uc16;  /* Read Only */
typedef unsigned char  const uc8;   /* Read Only */

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */

typedef bool BOOL;
typedef unsigned char    U08;
typedef unsigned char    uint8_t;
typedef signed char    S08;
typedef signed char    S8;
typedef unsigned short    uint16_t;
typedef signed short    S16;
typedef unsigned long     U32;
typedef signed long     S32;
typedef double         DOUBLE;
typedef unsigned int BIT;

#endif
/* ISO(POSIX) define for 32bit cpu*/
typedef char char_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;
typedef unsigned char bool;
typedef unsigned  bit_t;

typedef struct {
    bit_t b0:1;
    bit_t b1:1;
    bit_t b2:1;
    bit_t b3:1;
    bit_t b4:1;
    bit_t b5:1;
    bit_t b6:1;
    bit_t b7:1;
}_8bit_field;


typedef union {
    unsigned char byte;
    struct {
        bit_t b0:1;
        bit_t b1:1;
        bit_t b2:1;
        bit_t b3:1;
        bit_t b4:1;
        bit_t b5:1;
        bit_t b6:1;
        bit_t b7:1;
    }field;
}byte_field;


typedef union {
    unsigned char byte[2];
    unsigned short word  ;
    struct {
        bit_t b0:1;
        bit_t b1:1;
        bit_t b2:1;
        bit_t b3:1;
        bit_t b4:1;
        bit_t b5:1;
        bit_t b6:1;
        bit_t b7:1;
        bit_t b8:1;
        bit_t b9:1;
        bit_t b10:1;
        bit_t b11:1;
        bit_t b12:1;
        bit_t b13:1;
        bit_t b14:1;
        bit_t b15:1;
    }field;
}word_field;

#define GET_MSC(word)              ((uint8_t)((uint16_t)word>>8))
#define GET_LSC(word)              ((uint8_t)word)


#endif

