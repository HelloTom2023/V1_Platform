/**********************************************************
 * @file        Tw8836_OSD.h
 * @purpose
 * @version    0.01
 * @date      2015.06.10
 * @author    XL
 * @brief
 ***********************************************************
 *     History:
 *  <write/modify>        <time>        <version >    <desc>
 *  Deefisher.Lyu          02.Feb.2013        v0.01        created
 *
  **********************************************************/
#ifndef TW8836_OSD_H
#define TW8836_OSD_H

#ifdef D_VIDEO_SWITCH_TW8836
#ifdef TW8836_OSD
#define EXTERN
#else
#define EXTERN extern
#endif


//-----------------------------------------------------------------------------
//		SPI Read Mode
//-----------------------------------------------------------------------------
#define	SPI_READ_SLOW		0
#define SPI_READ_FAST 		1
#define SPI_READ_DUAL	 	2
#define SPI_READ_QUAD  		3
#define SPI_READ_DUALIO		4
#define SPI_READ_QUADIO		5

#define SPI_READ_MODE		SPI_READ_QUADIO//SPI_READ_QUAD
//--------------------
// SPI FLASH Vendor
//--------------------
#define SFLASH_VENDOR_MX	0	//MX25L12845(C2 20 18) -- defaut
#define SFLASH_VENDOR_EON	1	//EN25Q128 ID(1C 30 18)
#define SFLASH_VENDOR_WB	2
#define SFLASH_VENDOR_NUM	3	//STM(20 BA 18)
//--------------------
// SPI CLOCK
//--------------------
#define PCLK_SEL_PCLK		0
#define PCLK_SEL_PLL		1
#define SPI_CK_SEL_27M		0
#define SPI_CK_SEL_32K		1
#define SPI_CK_SEL_PCLK		2
#define SPI_CK_DIV_1P0		0
#define SPI_CK_DIV_1P5		1
#define SPI_CK_DIV_2P0		2
#define SPI_CK_DIV_2P5		3

#define SPI_WIN0_ST				0x20
#define SPI_WIN1_ST				0x40
#define SPI_WIN2_ST				0x50
#define SPI_WIN3_ST				0x60
#define SPI_WIN4_ST				0x70
#define SPI_WIN5_ST				0x80
#define SPI_WIN6_ST				0x90
#define SPI_WIN7_ST				0xA0
#define SPI_WIN8_ST				0xB0

#define CLKPLL_DIV_3P0		4
#define	SPI_OSDWIN_ENABLE		0x00
#define	SPI_OSDWIN_BUFFERSTART			0x07
#define SPI_OSDWIN_DISPSIZE				0x0A
#define SPI_OSDWIN_SCREEN				0x01
#define SPI_OSDWIN_DISPOFFSET			0x0D
#define	SPI_OSDWIN_ANIMATION			0x12    //432
#define SPI_OSDWIN_ALPHA				0x0C	//430(42C+4), 44C
#define SPI_OSDWIN_LUT_PTR				0x0D	//431(42D+4), 44D
#define SPI_OSDWIN_FILLCOLOR			0x0E	//436(42E+8), 44E
#define SPI_OSDWIN_HZOOM		0x00


//BMP size
#define W_CAR    0x002C//0x0028
#define H_CAR     0x0050//0x0050
#define PAM_BTN_MODE1_W  0x005C
#define PAM_BTN_MODE2_H   0x0034

//Press WIN
#define		PRESS_WIN		8
#define		PRESS_WIN2		2
#define		CAR_WIN		1

//LUT
#define		BG_LUT_OFFSET		0

#define     offsetendbin  0x50000 //offset address for SPI writing
//UI Start
#define     PAM_BTN_MODE3      (offsetendbin+0x003720)
#define     RADAR_CAMERA_ICON_CAR        ( offsetendbin+0x000400) //     ( offsetendbin+0x00E5EC) 
//LUTS
//#define     PAM_BTN_MODE3_LUTS                (offsetendbin+0x004010)
//#define      RADAR_CAMERA_ICON_CAR_LUTS  (offsetendbin+0x00F3AC)
#define      ALL_LUTS               (offsetendbin+0x000000)

#define REG500_MEAS_HSTART_MSB      	REG500
#define REG501_MEAS_HSTART_LSB      	REG501
#define REG502_MEAS_HLEN_MSB        	REG502
#define REG503_MEAS_HLEN_LSB        	REG503
#define REG505_MEAS_VSTART_MSB      	REG504
#define REG505_MEAS_VSTART_LSB      	REG505
#define REG506_MEAS_VLEN_MSB        	REG506
#define REG507_MEAS_VLEN_LSB        	REG507

uint8_t temp_SPI_Buffer[64];
uint8_t SpiFlash4ByteAddr;
uint8_t shadow_r4e0;
uint8_t shadow_r4e1;


EXTERN void TW8836_SpiMode(void);
EXTERN uint8_t SPI_SetModeByRegister( void );
EXTERN uint8_t SPI_QUADInit(void);	 
EXTERN void PclkoSetDiv(uint8_t pol, uint8_t div);
EXTERN void SspllSetFreqAndPll(uint64_t _PPF);
EXTERN void McuSpiClkSet(uint8_t PCLK_SEL,uint8_t SPI_CK_SEL,uint8_t SPI_CK_DIV) ;
EXTERN void	InitClock(void);
EXTERN void SOsdWinBuffClean(uint8_t hw);
EXTERN void SpiOsdWinHWEnable(uint8_t winno, uint8_t  en);
EXTERN void SpiOsdDisableRLC(uint8_t winno);
EXTERN void SpiOsdWinHWOffAll(uint8_t wait);
EXTERN void SpiOsdRLC(uint8_t winno,uint8_t dcnt, uint8_t ccnt);
EXTERN uint8_t Spi_Init(void);
EXTERN void SpiOsdSetDeValue(void);
EXTERN void SpiOsdEnable(uint8_t en);
EXTERN void OSDMixOrder( uint8_t font_first )	;
EXTERN void Download_OSD_Lut(uint8_t winno,uint64_t spi_addr, uint8_t Offset);
EXTERN void SpiOsdLoadLUT(uint8_t _winno, uint8_t type, uint32_t LutOffset, uint32_t size, uint64_t address);
EXTERN void SpiOsdIoLoadLUT(uint8_t type, uint32_t LutOffset, uint32_t size, uint64_t spiaddr);
EXTERN  void SPI_ReadData2xdata( uint64_t spiaddr, uint8_t *ptr, uint64_t cnt );
EXTERN  uint8_t McuSpiClkToPclk(uint8_t divider);
EXTERN  void McuSpiClkRestore(void);
EXTERN  void	Download_OSD_BMP(uint8_t winno, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint64_t spi_addr, uint8_t Offset, uint8_t En);
EXTERN  void SpiOsdWinImageLoc(uint8_t winno, uint64_t start);
EXTERN  void SpiOsdWinImageSizeWH (uint8_t winno, uint32_t w, uint32_t h); EXTERN  void SpiOsdWinImageSizeW(uint8_t winno, uint32_t w);
EXTERN  void SpiOsdWinScreen(uint8_t winno, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
EXTERN  void SpiOsdWin0ImageOffsetXY (uint32_t x, uint32_t y);
EXTERN  void SpiOsdWin0Animation(uint8_t mode, uint8_t FrameH, uint8_t FrameV, uint8_t Duration);
EXTERN  void	SpiOsdWinPixelAlpha( uint8_t winno, uint8_t alpha );
EXTERN  void SpiOsdWinPixelWidth(uint8_t winno, uint8_t bpp);
EXTERN  void SpiOsdWinLutOffset( uint8_t winno, uint32_t table_offset );
EXTERN  void SpiOsdWinBuffEnable(uint8_t winno, uint8_t en);
EXTERN  void SOsdWinBuffWrite2Hw(uint8_t start, uint8_t end);
EXTERN  void	SpiOsdWinFillColor( uint8_t winno, uint8_t color );
EXTERN  void SpiOsdWinHZoom(uint8_t winno, uint8_t en);
EXTERN  void MeasSetWindow( uint32_t x, uint32_t y, uint32_t w, uint32_t h );
EXTERN  void MeasSetField(uint8_t field);
EXTERN  void	InitMeasure(void);

#undef EXTERN
#if D_DEBUG_OSD&& D_PRINT_EN
#define OSD_printf(x)  x
#else
#define OSD_printf(x)
#endif
#endif
#endif




































