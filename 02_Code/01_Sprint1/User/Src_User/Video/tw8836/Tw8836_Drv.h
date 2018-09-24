/**********************************************************
 * @file        TW8836_Drv.h
 * @purpose    Definition of Fms6501
 * @version    0.01
 * @date        02.Feb. 2013
 * @author    Deefisher.Lyu
 * @brief
 ***********************************************************
 *     History:                                                                       
 *  <write/modify>        <time>        <version >    <desc>           
 *    Deefisher.Lyu        02.Feb.2013              v0.01        created
 *  
  **********************************************************/
#ifndef TW8836_DRV_H
#define TW8836_DRV_H

#ifdef D_VIDEO_SWITCH_TW8836
#ifdef TW8836_DRV_C
#define EXTERN
#else
#define EXTERN extern
#endif

//#define TW8836_TEST_MODE
#define  SDP                              0x9000
#define  AFE                              0x4C00
#define  Burst_Lock                   0x59
#define  ADC_Switch                      0x03     

//==<<PAGE & TWBASE>>=================================================
#define PAGE0_GENERAL		0x00
#define PAGE0_OUTPUT		0x00	//0x007::0x00F & 0x01F
#define PAGE0_INPUT			0x00	//0x040::0x046
#define PAGE0_BT656			0x00	//0x047::0x04A
#define PAGE0_DTV			0x00	//0x050::0x05F
#define PAGE0_GPIO			0x00	//0x080::0x09E
#define PAGE0_MBIST			0x00	//0x0A0::0x0A4
#define PAGE0_TOUCH			0x00	//0x0B0::0x0B4
#define PAGE0_LOPOR			0x00	//0x0D4::0x0DF
#define PAGE0_LEDC			0x00	//0x0E0::0x0E6
#define PAGE0_DCDC			0x00	//0x0E8::0x0EC
#define PAGE0_VCOM			0x00	//0x0ED::0x0EE
#define PAGE0_SSPLL			0x00	//0x0F6::0x0FD
		
#define PAGE1_DECODER		0x0100	//0x101::0x142
#define PAGE1_VADC			0x0100	//0x1C0::0x1E7	include LLPLL
#define PAGE1_LLPLL			0x0100	//0x1C0::0x1E7	include LLPLL
#define PAGE2_SCALER		0x0200	//0x201::0x21E
#define PAGE2_TCON			0x0200	//0x240::0x24E
#define PAGE2_IMAGE			0x0200	//0x280::0x2BF
#define PAGE2_GAMMA			0x0200	//0x2E0::0x2E3 include LCDC
#define PAGE2_DITHER		0x0200	//0x2E4::0x2E4
#define PAGE2_RGBLEVEL		0x0200	//0x2F0::0x2F5
#define PAGE2_8BITPANEL		0x0200	//0x2F8::0x2F9
#define PAGE3_FOSD			0x0300	//0x300::0x354
#define PAGE4_SOSD			0x0400	//0x400::0x3BE
#define PAGE4_SPI			0x0400	//0x4C0::0x4DA include MCU
#define PAGE4_CLOCK			0x0400	//0x4E0::0x4EB
#define PAGE5_MEAS			0x0500	//0x500::0x545
#define PAGE6_LVDS			0x0600

#define TWBASE_SPI			0xC0	//note:Not a page. it is a offset.
#define TW88_FPLL0			0xF8
#define TW88_FPLL1			0xF9
#define TW88_FPLL2			0xFA
#define TW88_SSPLL_ANALOG	0xFD

/* ========================= public variable ==================== */
#ifdef D_TW8836_I2C0_EN

typedef enum tw8836_startup_enum
{
    TW8836_STARTUP_POWER = 0,    // Open ASP Power Supply
    TW8836_STARTUP_IICBUS,
    TW8836_STARTUP_RVER,
    TW8836_STARTUP_END,            // ASP Startup End
} TW8836_STARTUP_ENUM;

#define I2C_WRITE_INDEX 0
#define I2C_WRITE_DATA 1
#define I2C_RE_START 2
#define I2C_READ_DATA 3
#define I2C_STOP_READ_WRITE 4

typedef union{        
       uint8_t a_cData[sizeof(void*)];
       uint8_t *p_cData;
}uI2c_DATA;

typedef struct{
    uint8_t   gAddr;
    uint8_t   gPageIndex;
    uint8_t   gStatusFlag;
    uint8_t   gWRflag;
    uint8_t   gCnt;
    uint8_t   gLen;
    uint8_t   gFlag;
    uint8_t   *gBuffer;
    uint8_t   *gRData;
    uI2C_CALL_BACK  gCallBack;
}I2C_CMD_STRUCT;

typedef struct
{
    uint8_t  gDisposalStep;
    uint8_t  gRWStep;
    uint8_t  gResult;
    uint16_t gWriteCnt;
    uint8_t  gErrCnt;
    uint8_t   gWaitTimer;
    uI2c_DATA  gData;
}I2C_CTRL_STRUCT;

EXTERN I2C_CMD_STRUCT  I2CDevCmdBuf;
EXTERN I2C_CTRL_STRUCT  I2CDevCtrl;

#define TW8836_CS_ADDR     0x8A  
#define TW8836_I2C_Write(cIndex,cData,cNum,CallBack)  TW8836_I2C_Start(TW8836_CS_ADDR, cIndex,cData,cNum,CallBack,0)
#define TW8836_I2C_WritePage(cIndex,cData,cNum,CallBack)  TW8836_I2C_Start(TW8836_CS_ADDR, cIndex,cData,cNum,CallBack,0)
#define TW8836_I2C_Read(cIndex,cData,cNum,CallBack)  TW8836_I2C_Start(TW8836_CS_ADDR,cIndex, cData,cNum,CallBack,1)
#define TW8836_I2C_Write_1(cAddr,cIndex,cData,cNum,CallBack)  TW8836_I2C_Start(cAddr,cIndex,cData,cNum,CallBack,0) 
#define TW8836_I2C_Read_1(cAddr, cIndex, cData, cNum, CallBack)  TW8836_I2C_Start(cAddr,cIndex,cData,cNum,CallBack,1) 
EXTERN void Tw8836_WriteDisposal(void);
#else
#endif


#undef EXTERN

#endif


#endif

