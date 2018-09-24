/**********************************************************
 * @file        Tw8836_OSD.c
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
#define TW8836_OSD
/* ========================= File include ======================= */
#include "..\..\config\inc.h"

#ifdef D_VIDEO_SWITCH_TW8836
//==========================================
//win0: 0x420	animation
//win1: 0x440	background. low priority
//win2: 0x430
//..
//win8: 0x4B0	focused.    high priority
//----------------------------------------
uint8_t SpiWinBuff[10*0x10];
uint8_t SpiOsdWinBase[9] = { SPI_WIN0_ST, 
		SPI_WIN1_ST, SPI_WIN2_ST, SPI_WIN3_ST, SPI_WIN4_ST,
		SPI_WIN5_ST, SPI_WIN6_ST, SPI_WIN7_ST, SPI_WIN8_ST
		};

//----------------- SPI Mode Definition ---------------------

uint8_t DMAMODE_RW_FIX_REG = 0x64;
uint8_t DMAMODE_RW_INC_REG = 0x44;
uint8_t DMAMODE_R_XDATA = 0xc4;
uint8_t DMAMODE_W_XDATA = 0xc4;
uint8_t SPICMD_READ = 0x03;
uint8_t SPICMD_PROGRAM = 0x02;
uint8_t SPICMD_BYTES = 5;



/* ========================= File Funtion ======================= */

/**********************************************************
 * @function    TW8836_SpiMode
 * @brief      Set Spi mode
 * @param      None
 * @retval     Result
 **********************************************************/
void TW8836_SpiMode(void)
{
      TW8836_WritePage( PAGE4_SPI );
      TW8836_WriteData( PAGE4_SPI|TWBASE_SPI, SPI_READ_MODE );
      SPI_SetModeByRegister();
     OSD_printf(_T("TW8836_SpiMode_END\n"));
}

/**********************************************************
 * @function    SPI_SetModeByRegister
 * @brief      Match DMA mode with SPI-read
 * @param      None
 * @retval     Result
 **********************************************************/
uint8_t SPI_SetModeByRegister( void )
{
	uint8_t mod;

	TW8836_WritePage( PAGE4_SPI );
	mod = TW8836_Read( PAGE4_SPI|0xc0 ) & 0x07;
	OSD_printf(_T("mod%x\n",mod));

	switch( mod ) {
		case 0:	//--- Slow
			DMAMODE_RW_FIX_REG = 0x64;
			DMAMODE_RW_INC_REG = 0x44;
			DMAMODE_R_XDATA    = 0xc4;
			DMAMODE_W_XDATA    = 0xc4;
			SPICMD_READ        = 0x03;	SPICMD_BYTES = 4;
			SPICMD_PROGRAM     = 0x02;
			break;

		case 1:	//--- Fast
			DMAMODE_RW_FIX_REG = 0x65;
			DMAMODE_RW_INC_REG = 0x45;
			DMAMODE_R_XDATA    = 0xc5;
			DMAMODE_W_XDATA    = 0xc4;
			SPICMD_READ        = 0x0b;	SPICMD_BYTES = 5;
			SPICMD_PROGRAM     = 0x02;
			break;

		case 2:	//--- Dual
			DMAMODE_RW_FIX_REG = 0x65;
			DMAMODE_RW_INC_REG = 0x45;
			DMAMODE_R_XDATA    = 0xc5;
			DMAMODE_W_XDATA    = 0xc4;
			SPICMD_READ        = 0x3b;	SPICMD_BYTES = 5;
			SPICMD_PROGRAM     = 0x02;
			break;

		case 3:	//--- Quad
			DMAMODE_RW_FIX_REG = 0x65;
			DMAMODE_RW_INC_REG = 0x45;
			DMAMODE_R_XDATA    = 0xc5;
			DMAMODE_W_XDATA    = 0xc4;
			SPICMD_READ        = 0x6b;	SPICMD_BYTES = 5;
			SPICMD_PROGRAM     = 0x02;
			break;

		case 4:	//--- Dual-IO
			DMAMODE_RW_FIX_REG = 0x65;
			DMAMODE_RW_INC_REG = 0x45;
			DMAMODE_R_XDATA    = 0xc5;
			DMAMODE_W_XDATA    = 0xc4;
			SPICMD_READ        = 0xbb;	SPICMD_BYTES = 5;
			SPICMD_PROGRAM     = 0x02;
			break;

		case 5:	//--- Quad-IO
			DMAMODE_RW_FIX_REG = 0x67;
			DMAMODE_RW_INC_REG = 0x47;
			DMAMODE_R_XDATA    = 0xc7;	
			DMAMODE_W_XDATA    = 0xc4;
			SPICMD_READ        = 0xeb;	 SPICMD_BYTES = 7;
			SPICMD_PROGRAM     = 0x02;
			break;
 	}
	return mod;
}

/**********************************************************
 * @function    SPI_QUADInit
 * @brief      SPI FLASH Vendor
 * @param      None
 * @retval     Result
 **********************************************************/
uint8_t SPI_QUADInit(void)	  						//mnm
{
	uint8_t	temp;
	uint8_t ret=0;
       OSD_printf(_T("SPI_QUADInit_Start\n"));
	TW8836_WritePage( PAGE4_SPI );

	TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
	TW8836_WriteData( PAGE4_SPI|0xca, 0x9f );					// cmd, read Jedec ID
	TW8836_WriteData( PAGE4_SPI|0xc6, 0x04 );
	TW8836_WriteData( PAGE4_SPI|0xc7, 0xd0 );						// read buffer size 3

	TW8836_WriteData( PAGE4_SPI|0xda, 0 );
	TW8836_WriteData( PAGE4_SPI|0xc8, 0 );
	TW8836_WriteData( PAGE4_SPI|0xc9, 3 );						// read buffer size 3
	TW8836_WriteData( PAGE4_SPI|0xc4, 0x01 );					// start

	temp = TW8836_Read(PAGE4_SPI|0xd0);

	if ( (temp == 0xC2) || ( temp == 0x1c)) {		// for MX	&& EON  && STM
		if(temp ==0x1C)
			ret = SFLASH_VENDOR_EON;
		else
			ret = SFLASH_VENDOR_MX;

		TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
		TW8836_WriteData( PAGE4_SPI|0xca, 0x05 );					// cmd, read Status
		TW8836_WriteData( PAGE4_SPI|0xc9, 1 );						// read buffer size 1
		TW8836_WriteData( PAGE4_SPI|0xc4, 0x01 );					// start
		temp = TW8836_Read( PAGE4_SPI|0xd0 );	
		OSD_printf(_T("temp=%x\n",temp));// read status regisiter value
		if ( temp == 0 ) {

			TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
			TW8836_WriteData( PAGE4_SPI|0xca, 0x06 );					// cmd, write enable
			TW8836_WriteData( PAGE4_SPI|0xc9, 0 );						// read buffer size 1
			TW8836_WriteData( PAGE4_SPI|0xc4, 0x03 );					// start

			TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
			TW8836_WriteData( PAGE4_SPI|0xca, 0x05 );					// cmd, read Status
			TW8836_WriteData( PAGE4_SPI|0xc9, 1 );						// read buffer size 1
			TW8836_WriteData( PAGE4_SPI|0xc4, 0x01 );					// start
			temp = TW8836_Read( PAGE4_SPI|0x10 );					// read status regisiter value

			TW8836_WriteData( PAGE4_SPI|0xc3, 0x42 );					// mode, cmd-len 2
			TW8836_WriteData( PAGE4_SPI|0xca, 0x01 );					// cmd, write Status
			TW8836_WriteData( PAGE4_SPI|0xcb, 0x40 );					// cmd, en QAUD mode
			TW8836_WriteData( PAGE4_SPI|0xc9, 0 );						// read buffer size 1
			TW8836_WriteData( PAGE4_SPI|0xc4, 0x07 );					// start + write + busycheck

			TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
			TW8836_WriteData( PAGE4_SPI|0xca, 0x05 );					// cmd, read Status
			TW8836_WriteData( PAGE4_SPI|0xc9, 1 );						// read buffer size 1
			TW8836_WriteData( PAGE4_SPI|0xc4, 0x01 );					// start
			temp = TW8836_Read( PAGE4_SPI|0xd0 );					// read status regisiter value

			TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
			TW8836_WriteData( PAGE4_SPI|0xca, 0x06 );					// cmd, write disable
			TW8836_WriteData( PAGE4_SPI|0xc4, 0x01 );					// start
			
		}
	}
		else if ( temp == 0xEF ) {				// for WB
		ret = SFLASH_VENDOR_WB;
		TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
		TW8836_WriteData( PAGE4_SPI|0xca, 0x05 );					// cmd, read Status
		TW8836_WriteData( PAGE4_SPI|0xc9, 2 );						// read buffer size 1
		TW8836_WriteData( PAGE4_SPI|0xc4, 0x01 );					// start
		temp = TW8836_Read( PAGE4_SPI|0xd1 );					// read status regisiter value
		if ( temp == 0 ) {
			//Puts("\nEnable WB quad mode" );
			TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
			TW8836_WriteData( PAGE4_SPI|0xca, 0x06 );					// cmd, write enable
			TW8836_WriteData( PAGE4_SPI|0xc4, 0x01 );					// start

			TW8836_WriteData( PAGE4_SPI|0xc3, 0x43 );					// mode, cmd-len 1
			TW8836_WriteData( PAGE4_SPI|0xca, 0x01 );					// cmd, write Status
			TW8836_WriteData( PAGE4_SPI|0xcb, 0x00 );					// cmd, en QAUD mode
			TW8836_WriteData( PAGE4_SPI|0xcc, 0x02 );					// cmd, en QAUD mode
			TW8836_WriteData( PAGE4_SPI|0xc4, 0x01 );					// start
		}
	}
	else if(temp == 0x20 ) {				// for STM
		ret = SFLASH_VENDOR_NUM;
		//Puts("\nEnable Numonyx quad mode" );

		TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
		TW8836_WriteData( PAGE4_SPI|0xca, 0x06 );					// cmd, write enable
		TW8836_WriteData( PAGE4_SPI|0xc9, 0 );						// read buffer size 1
		TW8836_WriteData( PAGE4_SPI|0xc4, 0x03 );					// start

		TW8836_WriteData( PAGE4_SPI|0xc3, 0x43 );					// mode, cmd-len 1
		TW8836_WriteData( PAGE4_SPI|0xca, 0xB1 );					// cmd, write enable
		TW8836_WriteData( PAGE4_SPI|0xcb, 0x6F );
		TW8836_WriteData( PAGE4_SPI|0xcc, 0xFF );
		TW8836_WriteData( PAGE4_SPI|0xc9, 0 );						// read buffer size 1
		TW8836_WriteData( PAGE4_SPI|0xc4, 0x07 );					// start

		TW8836_WriteData( PAGE4_SPI|0xc3, 0x41 );					// mode, cmd-len 1
		TW8836_WriteData( PAGE4_SPI|0xca, 0x06 );					// cmd, write enable
		TW8836_WriteData( PAGE4_SPI|0xc9, 0 );						// read buffer size 1
		TW8836_WriteData( PAGE4_SPI|0xc4, 0x03 );					// start

		TW8836_WriteData( PAGE4_SPI|0xc3, 0x42 );					// mode, cmd-len 1
		TW8836_WriteData( PAGE4_SPI|0xca, 0x81 );					// cmd, write enable
		TW8836_WriteData( PAGE4_SPI|0xcb, 0x6B );
		TW8836_WriteData( PAGE4_SPI|0xc9, 0 );						// read buffer size 1
		TW8836_WriteData( PAGE4_SPI|0xc4, 0x07 );					// start

		//Puts("--DONE");
	}
	
	OSD_printf(_T("SPI_QUADInit_End\n"));
	return ret;
}

/**********************************************************
 * @function    PclkoSetDiv
 * @brief   pol - Pixel clock output polarity   div - Pixel clock output frequency division
 * @param      None
 * @retval     Result
 **********************************************************/
void PclkoSetDiv(uint8_t pol, uint8_t div)
{
	uint8_t value;
	TW8836_WritePage(PAGE2_SCALER);
	value = TW8836_Read(PAGE2_SCALER|0x0D);
	if(pol != 0xFF) {
		value &= 0xEC;
		if(pol) value |= 0x10;	
	}
	else {
		value &= 0xFC;
	}
	//D_Print(Printf("\nPclkoSetDiv(%bx,%bx) value:0x%bx|0x%bx",pol,div,value,div));
	TW8836_WriteData(PAGE2_SCALER|0x0D, value | div);
}

/**********************************************************
 * @function    SspllSetFreqAndPll
 * @brief   Set Freq
 * @param      None
 * @retval     Result
 **********************************************************/

void SspllSetFreqAndPll(uint64_t _PPF)
{
	uint8_t ppf, CURR, VCO, POST, i;
	uint64_t FPLL;
	
	uint8_t	val;	


	//D_Print(Printf("\nSspllSetFreqAndPll(%ld)",_PPF));
	ppf = _PPF/1000000L;		//base:1Hz

	//----- Frequency Range --------------------
	if     ( ppf < 27 )  { VCO=2; CURR=0; POST=2; }		// step = 0.5MHz
	else if( ppf < 54 )  { VCO=2; CURR=1; POST=1; }		// step = 1.0MHz
	else if( ppf < 108 ) { VCO=2; CURR=2; POST=0; }		// step = 1.0MHz
	else                 { VCO=3; CURR=3; POST=0; }		// step = 1.0MHz

	CURR = VCO+1;	//BK110721. Harry Suggest.

	//----- Get FBDN
	
	FPLL = _PPF/1000L;	//base:10Hz

	i = POST;
	for(; i>0; i-- )
		FPLL *= 2;

	FPLL <<= 12;
	
	FPLL = FPLL / 3375L;		//Base:1Hz

	//----- Setting Registers : below is different with 8806
	TW8836_WritePage(PAGE0_SSPLL);
	TW8836_WriteData( PAGE0_SSPLL|TW88_FPLL0, (FPLL>>16));
	TW8836_WriteData( PAGE0_SSPLL|TW88_FPLL1, (uint8_t)(FPLL>>8));
	TW8836_WriteData( PAGE0_SSPLL|TW88_FPLL2, (uint8_t)FPLL );
	TW8836_WriteData( PAGE0_SSPLL|TW88_SSPLL_ANALOG, (VCO<<4) | (POST<<6) |CURR );

	val =  TW8836_Read(PAGE0_SSPLL|0xFC);

	//D_Print(Printf("\nTW8835 0x0fC: %02bx ", ReadTW88(PAGE0_SSPLL|0xFC) ));
	//D_Print(Printf("\nTW8835 0x0fC&~0x80: %02bx ", ReadTW88(PAGE0_SSPLL|0xFC) & ~0x80 ));

	TW8836_WriteData( PAGE0_SSPLL|0xFC, TW8836_Read(PAGE0_SSPLL|0xFC) & ~0x80 );		// OFF PD_SSPLL(means PowerUP)

	//adjust clock divider depend on the clock. see SetDefaultPClock()
	PclkoSetDiv(1, (ppf+39) / 40 - 1); //0:div1, 1:div2, 2:div3	
}


/**********************************************************
 * @function    McuSpiClkSet
 * @brief   Spi Clk Control Register
 * @param      None
 * @retval     Result
 **********************************************************/
void McuSpiClkSet(uint8_t PCLK_SEL,uint8_t SPI_CK_SEL,uint8_t SPI_CK_DIV) 
{
	TW8836_WritePage(PAGE4_CLOCK);
	if(PCLK_SEL)	TW8836_WriteData(PAGE4_CLOCK|0xE0, TW8836_Read(PAGE4_CLOCK|0xE0) |  0x01);
	else			TW8836_WriteData(PAGE4_CLOCK|0xE0, TW8836_Read(PAGE4_CLOCK|0xE0) & ~0x01); 
	TW8836_WriteData(PAGE4_CLOCK|0xE1, (SPI_CK_SEL << 4) | SPI_CK_DIV);
}


/**********************************************************
 * @function    InitClock
 * @brief   InitClock
 * @param      None
 * @retval     Result
 **********************************************************/
void	InitClock(void)
{
 	//SspllSetFreqAndPll(85000000L);
	SspllSetFreqAndPll(72000000L);
	McuSpiClkSet(PCLK_SEL_PCLK,SPI_CK_SEL_PCLK,SPI_CK_DIV_1P0);
       OSD_printf(_T("InitClock_END\n"));
}

/**********************************************************
 * @function    SOsdWinBuffClean
 * @brief   clear all SpiWinBuff[]
 * @param      None
 * @retval     Result
 **********************************************************/
void SOsdWinBuffClean(uint8_t hw)
{
	uint8_t i,j;

	if(hw) {
		SpiOsdWinHWOffAll(1);
	 	SpiOsdRLC(0,0,0);	//disable RLE
	}

	for(i=0; i < 10; i++) {
		for(j=0; j < 0x0E; j++)
			SpiWinBuff[i*16+j]=0;
	}
}
/**********************************************************
 * @function    SpiOsdWinHWEnable
 * @brief   Enable SpiOsd Window
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdWinHWEnable(uint8_t winno, uint8_t  en)
{
	uint8_t index;
	uint8_t dat;

	index = SpiOsdWinBase[winno] + SPI_OSDWIN_ENABLE;

	TW8836_WritePage( PAGE4_SOSD );
	dat = TW8836_Read(PAGE4_SOSD|index);
	if( en ) 
	{
		TW8836_WriteData(PAGE4_SOSD|index, dat | 0x01);
	}
	else   
	{
		//TW8836_WaitVBlank(1);//osdtest
		TW8836_WriteData(PAGE4_SOSD|index, dat & 0xfe);
	}
}


/**********************************************************
 * @function    SpiOsdDisableRLC
 * @brief   SpiOsdDisableRLC
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdDisableRLC(uint8_t winno)
{
	TW8836_WritePage(PAGE4_SOSD );
	if(winno==1 || winno==2)
		TW8836_WriteData(REG406, (TW8836_Read(REG406) & 0x0F));
	else
		TW8836_WriteData(REG404, (TW8836_Read(REG404) & 0x0F));

}




/**********************************************************
 * @function    SpiOsdWinHWOffAll
 * @brief   
 * @param      None
 * @retval     Result
 **********************************************************/
 void SpiOsdWinHWOffAll(uint8_t wait)
{
	uint8_t i;
	//if(wait)//osdtest
		//TW8836_WaitVBlank(wait);//osdtest
//	SpiOsdEnableRLC(OFF);		//disable RLE
	for(i=0; i<= 8; i++)
	{
		SpiOsdWinHWEnable(i, 0);
	}
	for(i=0; i<= 8; i++)
	{
		SpiOsdDisableRLC(i);
	}
}

/**********************************************************
 * @function    SpiOsdRLC
 * @brief   
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdRLC(uint8_t winno,uint8_t dcnt, uint8_t ccnt)
{
	uint8_t val;
	val = ( winno<<4 );
	//7 means 8BPP with 128 color.
	if(dcnt==7)
		dcnt++;
	
	if( winno == 1 || winno == 2 )				//Group B
	{
		TW8836_WriteData(PAGE4_SOSD|0x07, (dcnt << 4) | (ccnt));
		TW8836_WriteData(PAGE4_SOSD|0x06, val); 		
	}
	else if( winno >= 3 && winno <= 8 )			//Group A
	{	
		TW8836_WriteData(PAGE4_SOSD|0x05, (dcnt << 4) | (ccnt));	
		TW8836_WriteData(PAGE4_SOSD|0x04, val); 	
	}
}

/**********************************************************
 * @function    SpiOsdSetDeValue
 * @brief   calculate the start position of spi osd
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdSetDeValue(void)
{
	uint32_t wTemp;
	uint8_t HDE,PCLKO;

	TW8836_WritePage( PAGE2_SCALER );
	HDE = TW8836_Read( PAGE2_SCALER|0x10 );				// HDE
	PCLKO = TW8836_Read(PAGE2_SCALER|0x0d) & 0x03;
	PCLKO = 1;

	wTemp = (uint32_t)HDE + PCLKO - 19;

	TW8836_WritePage( PAGE4_SOSD );
	TW8836_WriteData( PAGE4_SOSD|0x0E, (uint8_t)(wTemp>>8) );	// write SPI OSD DE value(high nibble)
	TW8836_WriteData( PAGE4_SOSD|0x0F, (uint8_t)wTemp );   		// write SPI OSD DE value(low byte)
	//dPrintf("\nSpiOsdDe:%04x",wTemp);		
}

/**********************************************************
 * @function    SpiOsdEnable
 * @brief   Enable SpiOsd
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdEnable(uint8_t en)
{
	uint8_t dat;
	TW8836_WritePage( PAGE4_SOSD );
	dat = TW8836_Read(0x00);
	if( en ) 
	{
		TW8836_WriteData(PAGE4_SOSD|0x00, dat | 0x04);
	}
	else 
	{
	       TW8836_WriteData(PAGE4_SOSD|0x00, dat & 0xfb);
	}
}

/**********************************************************
 * @function    OSDMixOrder
 * @brief  Spiosd and video mixing order 0 = spi first   1 = font first
 * @param      None
 * @retval     Result
 **********************************************************/
void	OSDMixOrder( uint8_t font_first )				
{
	uint8_t val;
	val =  TW8836_Read( PAGE4_SOSD | 0x00 );
	if( font_first == 0 )
		TW8836_WriteData( PAGE4_SOSD | 0x00, val & 0xfd  );
	else
		TW8836_WriteData( PAGE4_SOSD | 0x00, val | 0x02  );				
}


/**********************************************************
 * @function    Spi_Init
 * @brief   Spi_Init
 * @param      None
 * @retval     Result
 **********************************************************/
uint8_t Spi_Init(void)
{
	 uint8_t Result = SUBLAYER_DOING;
        uint8_t SubResult = SUBLAYER_DOING;
	//video_printf(_T("Spi_Init_Start\n"));
       switch(fTw8836.DrvspiInitStep)
       {
             case OPERATION_0:
		      SPI_QUADInit();
		      SubResult = SUBLAYER_DONE; 
                   if(SUBLAYER_DONE == SubResult)
                 {
                     fTw8836.DrvspiInitStep = OPERATION_1;
		
                  }
                     break;
	     case OPERATION_1:
			TW8836_SpiMode();
			if(TW8836_Read(REG4E1) & 0x30) 
	                {
                           TW8836_WriteData(REG0D4, 0x01);
                           TW8836_WriteData(REG0D4, 0x04);
                         }
	//----- Enable Chip Interrupt
	                     TW8836_WritePage( PAGE0_GENERAL );
	                     TW8836_WriteData( PAGE0_GENERAL|0x02, 0xFF );	// Clear Pending Interrupts
			  SubResult = SUBLAYER_DONE; 
	             if(SUBLAYER_DONE == SubResult)
                      {
                       fTw8836.DrvspiInitStep = OPERATION_2;
		
                       }
                      break;
	    case OPERATION_2:
			 InitClock();
			 SubResult = SUBLAYER_DONE; 
	             if(SUBLAYER_DONE == SubResult)
                      {
                      fTw8836.DrvspiInitStep = OPERATION_3;
		
                      }
		 break;
	  case OPERATION_3:
		 	SOsdWinBuffClean(0);
			 SubResult = SUBLAYER_DONE; 
	              if(SUBLAYER_DONE == SubResult)
                   {
                     fTw8836.DrvspiInitStep = OPERATION_4;
		
                    }
		 break;
        case OPERATION_4:
		 	SpiOsdSetDeValue();
			 SubResult = SUBLAYER_DONE; 
	     if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvspiInitStep = OPERATION_5;
		
            }
		 break;	
	case OPERATION_5:
		 SpiOsdEnable(ON);
		 SubResult = SUBLAYER_DONE; 
	     if(SUBLAYER_DONE == SubResult)
            {
                fTw8836.DrvspiInitStep = OPERATION_6;
		
            }
		 break;
	 case OPERATION_6:
		OSDMixOrder(0);
		 SubResult = SUBLAYER_DONE; 
	     if(SUBLAYER_DONE == SubResult)
            {
                 fTw8836.DrvspiInitStep=OPERATION_7;
		
            }
		 break;
        case OPERATION_7:
	   	InitMeasure();
		 OSD_printf(_T("SPI_INIT_OK\n"));
		 SubResult = SUBLAYER_DONE; 
	     if(SUBLAYER_DONE == SubResult)
            {
                Result=SUBLAYER_DONE;
		
            }
	   	
      default :
	  	break;

	   }
	   return Result;
	
}

/**********************************************************
 * @function    Download_OSD_Lut
 * @brief   Download OSD Lut
 * @param      None
 * @retval     Result
 **********************************************************/
void	Download_OSD_Lut(uint8_t winno,uint64_t spi_addr, uint8_t Offset)
{
	uint32_t lut_offset;	

	if(Offset==1)
		lut_offset = 0x100;
	else
		lut_offset = 0x000;

	//TW8836_WaitVBlank(1);//osdtest
	//SpiOsdLoadLUT(1,lut_offset,0x400, spi_addr);
	SpiOsdLoadLUT(winno,1,lut_offset,0x400, spi_addr);
}
/**********************************************************
 * @function    SpiOsdLoadLUT
 * @brief   SpiOsdLoadLUT
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdLoadLUT(uint8_t _winno, uint8_t type, uint32_t LutOffset, uint32_t size, uint64_t address)
{
	uint8_t reg;

	uint8_t winno;
	winno = _winno;

	if(type==0) {
		SpiOsdIoLoadLUT(type,0,0x400,address);
		return;
	}	

	//save clock mode & select PCLK	
	McuSpiClkToPclk(CLKPLL_DIV_3P0);	//with divider 1=2(54MHz)	try 3

	TW8836_WritePage(PAGE4_SOSD);

	//--- SPI-OSD config
	reg = 0;	//ReadTW88(REG410);
	if(LutOffset & 0x100) reg = 0x08;
	reg |= 0x80;									// LUT Write Mode.
	if(type==0)	reg |= 0x40;						// address ptr inc						
	else		reg |= 0x20;						// byte ptr inc.

	if(winno == 1 || winno == 2)					// if win1 or win2, 
		reg |= 0x04;								//	select group B LUT

	if(LutOffset > 0xff)   							
		reg |= 0x08;								
	TW8836_WriteData(REG410, reg);
	TW8836_WriteData(REG411, (uint8_t)LutOffset ); 			// LUT addr. set 0 on DMA

	//Spi Flash DMA
	TW8836_WriteData(REG4C0_SPIBASE+0x04, 0x00 );	// DMA stop	

	TW8836_WriteData(REG4C0_SPIBASE+0x03, 0x80 | SPICMD_BYTES + SpiFlash4ByteAddr); //LUT,Increase, 0x0B with 5 commands, 0xeb with 7 commands	           
	TW8836_WriteData(REG4C0_SPIBASE+0x0a, SPICMD_READ ); 			// SPI Command=R

	if(SpiFlash4ByteAddr) {
		TW8836_WriteData(REG4C0_SPIBASE+0x0b, (uint8_t)(address>>24) );
		TW8836_WriteData(REG4C0_SPIBASE+0x0c, (uint8_t)(address>>16) );
		TW8836_WriteData(REG4C0_SPIBASE+0x0d, (uint8_t)(address>>8) );
		TW8836_WriteData(REG4C0_SPIBASE+0x0e, (uint8_t)(address) );
	}
	else {
		TW8836_WriteData(REG4C0_SPIBASE+0x0b, (uint8_t)(address>>16) ); 	// SPI Addr
		TW8836_WriteData(REG4C0_SPIBASE+0x0c, (uint8_t)(address>>8) );
		TW8836_WriteData(REG4C0_SPIBASE+0x0d, (uint8_t)(address) ); 		//////00
	}

		TW8836_WriteData(REG4C0_SPIBASE+0x06, (uint8_t)(LutOffset >> 6) ); 	//LutOffset[8:6] -> R4C6[2:0]
		TW8836_WriteData(REG4C0_SPIBASE+0x07, (uint8_t)(LutOffset << 2) );	//LutOffset[5:0] -> R4C7[7:2] 

	TW8836_WriteData(REG4C0_SPIBASE+0x1a, 0x00 ); // DMA size
	TW8836_WriteData(REG4C0_SPIBASE+0x08, (uint8_t)(size >> 8) );
	TW8836_WriteData(REG4C0_SPIBASE+0x09, (uint8_t)size );

	if(winno==1 || winno==2) {
		TW8836_WriteData(REG410, TW8836_Read(REG410) | 0x04);	//indicate GROUP_B palette table. MAX size 256.
	}

	TW8836_WriteData(REG4C0_SPIBASE+0x04, 0x01 ); // DMA Start
	//restore clock mode
	McuSpiClkRestore();
}

/**********************************************************
 * @function    SpiOsdIoLoadLUT
 * @brief   SpiOsdIoLoadLUT
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdIoLoadLUT(uint8_t type, uint32_t LutOffset, uint32_t size, uint64_t spiaddr)
{
	uint8_t i,j,k;
	uint8_t R410_data;
	//dPrintf("\nSpiOsdIoLoadLUT%s LutLoc:%d size:%d 0x%06lx", type ? "S":" ", LutOffset, size, spiaddr);

	TW8836_WritePage( PAGE4_SOSD );

	//--- SPI-OSD config
	if(type==0)	R410_data = 0xC0;			// LUT Write Mode, En & address ptr inc.
	else		R410_data = 0xA0;			// LUT Write Mode, En & byte ptr inc.
	if(LutOffset >> 8)
		R410_data |= 0x04;
	
	if(type==0) {
		//
		//ignore size. it is always 0x400.(256*4)
		//		
		for(i=0; i < 4; i++) {	 
			TW8836_WriteData(PAGE4_SOSD|0x10, R410_data | i );	//assign byte ptr	
			TW8836_WriteData(PAGE4_SOSD|0x11, (uint8_t)LutOffset);	//reset address ptr.
			for(j=0; j<(256/64);j++) {
				SPI_ReadData2xdata( spiaddr + i*256 + j*64, temp_SPI_Buffer, 64 );
				for(k=0; k < 64; k++) {
					TW8836_WriteData(PAGE4_SOSD|0x12, temp_SPI_Buffer[k]);		//write data
				}
			}
		}
	}
	else {
		TW8836_WriteData(PAGE4_SOSD|0x10, R410_data);			//assign byte ptr. always start from 0.
		TW8836_WriteData(PAGE4_SOSD|0x11, (uint8_t)LutOffset);	//reset address ptr.

		for(i=0; i < (size / 64); i++ ) {	//min size is a 64(16*4)
			SPI_ReadData2xdata( spiaddr + i*64, temp_SPI_Buffer, 64 );
			for(k=0; k < 64; k++) {
				TW8836_WriteData(PAGE4_SOSD|0x12, temp_SPI_Buffer[k]);		//write data
			}
		}
	}
}

/**********************************************************
 * @function    SPI_ReadData2xdata
 * @brief   SPI --> Incremental XDATA
 * @param      None
 * @retval     Result
 **********************************************************/
 void SPI_ReadData2xdata( uint64_t spiaddr, uint8_t *ptr, uint64_t cnt )
{
	uint32_t xaddr;

	xaddr = (uint32_t)ptr;

	TW8836_WritePage( PAGE4_SPI );			// Set Page=4

	TW8836_WriteData( PAGE4_SPI|0xc3, DMAMODE_R_XDATA );			// Mode = SPI -> incremental xdata
	TW8836_WriteData( PAGE4_SPI|0xca, SPICMD_READ );				// Read Command
	TW8836_WriteData( PAGE4_SPI|0xcb, spiaddr>>16 );				// SPI address
	TW8836_WriteData( PAGE4_SPI|0xcc, spiaddr>>8 );				// SPI address
	TW8836_WriteData( PAGE4_SPI|0xcd, spiaddr );					// SPI address
 	TW8836_WriteData( PAGE4_SPI|0xc6, xaddr>>8 );				// Buffer address
	TW8836_WriteData( PAGE4_SPI|0xc7, xaddr );					// Buffer address

	TW8836_WriteData( PAGE4_SPI|0xda, cnt>>16 );					// Read count
 	TW8836_WriteData( PAGE4_SPI|0xc8, cnt>>8 );					// Read count
	TW8836_WriteData( PAGE4_SPI|0xc9, cnt );						// Read count

	TW8836_WriteData( PAGE4_SPI|0xC4, 0x01);						//DMA-Read start
}

/**********************************************************
 * @function    McuSpiClkToPclk
 * @brief   McuSpiClkToPclk
 * @param      None
 * @retval     Result
 **********************************************************/
uint8_t McuSpiClkToPclk(uint8_t divider)
{
	TW8836_WritePage(PAGE4_CLOCK);
	shadow_r4e0=TW8836_Read(PAGE4_CLOCK|0xE0);
	if(shadow_r4e0 & 0x01) {
		shadow_r4e1 = TW8836_Read(PAGE4_CLOCK|0xE1);
		TW8836_WriteData(PAGE4_CLOCK|0xE0, shadow_r4e0 & 0xFE);
		TW8836_WriteData(PAGE4_CLOCK|0xE1, 0x20 | divider);
		return 1;
	}
	return 0;
}

/**********************************************************
 * @function    McuSpiClkRestore
 * @brief   McuSpiClkRestore
 * @param      None
 * @retval     Result
 **********************************************************/
 void McuSpiClkRestore(void)
{
	if(shadow_r4e0 & 0x01) {
		TW8836_WritePage(PAGE4_CLOCK);
		TW8836_WriteData(PAGE4_CLOCK|0xE0, shadow_r4e0);
		TW8836_WriteData(PAGE4_CLOCK|0xE1, shadow_r4e1);
	}
}


/**********************************************************
 * @function    Download_OSD_BMP
 * @brief   Download_OSD_BMP
 * @param      None
 * @retval     Result
 **********************************************************/
void	Download_OSD_BMP(uint8_t winno, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint64_t spi_addr, uint8_t Offset, uint8_t En)
{
	uint32_t	temp_lut_offset;
	
	if(Offset==1)
		temp_lut_offset = 0x100;
	else
		temp_lut_offset = 0x000;

//	SpiOsdSetDeValue();	

	SpiOsdWinImageLoc(winno, spi_addr/16); 
	SpiOsdWinImageSizeWH( winno, w, h );
	SpiOsdWinScreen( winno, x, y, w, h );

	if(winno==0) {
		SpiOsdWin0ImageOffsetXY( 0, 0 );
		SpiOsdWin0Animation( 1, 0, 0, 0);
	}
	SpiOsdWinPixelAlpha( winno, ON );
	//SpiOsdWinGlobalAlpha( winno, 0);
	SpiOsdWinPixelWidth(winno, 8);

	
	SpiOsdWinLutOffset(winno, temp_lut_offset);

	SpiOsdWinBuffEnable( winno, En );
	
	TW8836_WaitVBlank(1);
	TW8836_WritePage(PAGE4_SOSD);
	if(winno != 0)
	{
		if(winno==(TW8836_Read(PAGE4_SOSD|0x06)&0x0f))
		{
			
			SpiOsdRLC( 0,0,0); //BK110217
		}
	}
	//update HW
	SOsdWinBuffWrite2Hw(winno, winno);

	SpiOsdWinFillColor(winno,0);
	SpiOsdWinHZoom(winno, 0);

	SpiOsdSetDeValue();
}

/**********************************************************
 * @function    SpiOsdWinImageLoc
 * @brief   WINx Image Location on SpiFlash	
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdWinImageLoc(uint8_t winno, uint64_t start)
{	
	uint8_t *data_p;

	if(winno) winno++;
	data_p = &SpiWinBuff[winno << 4];

	data_p += SPI_OSDWIN_BUFFERSTART;

	*data_p++ =  (uint8_t)(start>>16);				//+0x07
	*data_p++ =  (uint8_t)(start>>8);				//+0x08
	*data_p++ =  (uint8_t)start;					//+0x09
}


/**********************************************************
 * @function    SpiOsdWinImageSizeWH
 * @brief   WINx buff size	
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdWinImageSizeWH (uint8_t winno, uint32_t w, uint32_t h)
{
	uint8_t *data_p;
	uint8_t value;

	//WIN1to8 need only Width.
	if(winno) {
		SpiOsdWinImageSizeW(winno,w);
		return; 
	}

	//now only for WIN0
	data_p = SpiWinBuff;				   //Only WIN0
	data_p += SPI_OSDWIN_DISPSIZE;

	value = (uint8_t)(h >> 8);
	value <<= 4;
	value |= (uint8_t)( w>>8 );
	*data_p++ = value; 		//42A
	*data_p++ = (uint8_t)w;	//42B
	*data_p++ = (uint8_t)h;	//42C
}

/**********************************************************
 * @function    SpiOsdWinImageSizeW
 * @brief   WINBUFF	
 * @param      None
 * @retval     Result
 **********************************************************/
 void SpiOsdWinImageSizeW(uint8_t winno, uint32_t w)
{
	uint8_t *data_p;
	uint8_t value;

	data_p = &SpiWinBuff[(winno+1) << 4];	//No WIN0
	data_p += SPI_OSDWIN_DISPSIZE;

 	value = *data_p & 0xC0;

	*data_p++ = (uint8_t)(w>>8 | value);		//+0x0A
	*data_p++ = (uint8_t)w;					//+0x0B
}

/**********************************************************
 * @function    SpiOsdWinScreen
 * @brief   SpiOsdWinScreen	
 * @param      None
 * @retval     Result
 **********************************************************/
 void SpiOsdWinScreen(uint8_t winno, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
       uint8_t  *data_p;
	uint8_t value;

	if(winno) winno++;
	data_p = &SpiWinBuff[winno << 4];

	data_p += SPI_OSDWIN_SCREEN;
	value = (y >> 8);
	value <<= 4;
	value |= (x >> 8);
	*data_p++ = value;		//421	441...
	*data_p++ = (uint8_t)x;	//422	442... 	
	*data_p++ = (uint8_t)y;	//423	443...
	
	value = (h >> 8);
	value <<= 4;
	value |= (w >> 8);
	*data_p++ = value;		//424	444...
	*data_p++ = (uint8_t)w;	//425	445...	 	
	*data_p++ = (uint8_t)h;	//426	446...	 
}

/**********************************************************
 * @function    SpiOsdWin0ImageOffsetXY
 * @brief   SpiOsdWin0ImageOffsetXY	
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdWin0ImageOffsetXY (uint32_t x, uint32_t y)
{
	uint8_t value;
	uint8_t *data_p;

	data_p = SpiWinBuff;			//Only WIN0
	data_p += SPI_OSDWIN_DISPOFFSET;

	value  = (uint8_t)(y >> 8);
	value <<=4;
	value |= (uint8_t)(x >> 8);
	*data_p++ = value;
	*data_p++ = (uint8_t)x;
	*data_p++ = (uint8_t)y;
}
/**********************************************************
 * @function    SpiOsdWin0Animation
 * @brief   SpiOsdWin0Animation	
 * @param      None
 * @retval     Result
 **********************************************************/
 void SpiOsdWin0Animation(uint8_t mode, uint8_t FrameH, uint8_t FrameV, uint8_t Duration)
{
	uint8_t *data_p;

	data_p = SpiWinBuff;	  			//Only WIN0
	data_p += SPI_OSDWIN_ANIMATION;

	*data_p++ = FrameH;
	*data_p++ = FrameV;
	*data_p++ = Duration;

	*data_p &= 0x3f;
	*data_p |= (mode << 6);
}

/**********************************************************
 * @function    SpiOsdWinPixelAlpha
 * @brief   SpiOsdWinPixelAlpha	
 * @param      None
 * @retval     Result
 **********************************************************/
 void	SpiOsdWinPixelAlpha( uint8_t winno, uint8_t alpha )
{
	uint8_t *data_p;

	if(winno) winno++;
	data_p = &SpiWinBuff[winno << 4];

	if(alpha)	*data_p |= 0x30;
	else		*data_p &= 0xCF;

	data_p += SPI_OSDWIN_ALPHA;
	if(!winno)	data_p += 4;
	*data_p = alpha;
}
/**********************************************************
 * @function    SpiOsdWinPixelWidth
 * @brief   0:4bit, 1:6bit others:8bit
 * @param      None
 * @retval     Result
 **********************************************************/
 void SpiOsdWinPixelWidth(uint8_t winno, uint8_t bpp)
{
	uint8_t *data_p;
	uint8_t mode;

	if(bpp==4)	mode=0;
	else if(bpp==6) mode=1;
	else mode=2;	//7 and 8 use mode 2

	if(winno) 	winno++;
	data_p = &SpiWinBuff[winno << 4];

	*data_p &= 0x3f;
	*data_p |= (mode <<6);
}

/**********************************************************
 * @function    SpiOsdWinPixelWidth
 * @brief   0:4bit, 1:6bit others:8bit
 * @param      None
 * @retval     Result
 **********************************************************/
 void SpiOsdWinLutOffset( uint8_t winno, uint32_t table_offset )
{
	uint8_t *data_p;

	if(winno) winno++;
	data_p = &SpiWinBuff[winno << 4];
	data_p += SPI_OSDWIN_LUT_PTR;
	if(!winno) data_p += 4;
	
	//LUT offset use 5bit & 16 unit
	*data_p = table_offset >> 4;
}
/**********************************************************
 * @function    SpiOsdWinBuffEnable
 * @brief   SpiOsdWinBuffEnable
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdWinBuffEnable(uint8_t winno, uint8_t en)
{
	 uint8_t  *data_p;

	if(winno) winno++;
	data_p = &SpiWinBuff[winno << 4];

	if(en) *data_p |= 0x01;
	else   *data_p &= 0xfe;
}
/**********************************************************
 * @function    SpiOsdWinBuffEnable
 * @brief   SpiOsdWinBuffEnable
 * @param      None
 * @retval     Result
 **********************************************************/
 void SOsdWinBuffWrite2Hw(uint8_t start, uint8_t end)
{
	uint8_t i; //,j;
	uint8_t reg_i;
	uint8_t  *data_p;

	//dPrintf("\nSOsdWinBuffWrite2Hw(%bd,%bd)",start,end);

	if(start)	start++;
	if(end)		end++;

	//WaitVBlank(1);
	TW8836_WritePage( PAGE4_SOSD );
	data_p = &SpiWinBuff[start << 4];
//EA = 0;
	for(i=start; i <= end; i++) {
		reg_i = (i << 4) + 0x20;

		if(i==0)
		TW8836_WriteData(PAGE4_SOSD|reg_i++, (*data_p++)|0x02 );	//0
		else
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//0

		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//1
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//2
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//3
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//4
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//5
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//6
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//7
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//8
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//9
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//A
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//B
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//C
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//D
		TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//E
		if(i) {
			data_p++;						//F
		}
		else {
			TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//0F
			i++;
			TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//10
			TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//11
			TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//12
			TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//13
			TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//14
			TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//15
			TW8836_WriteData(PAGE4_SOSD|reg_i++, *data_p++);	//16
			reg_i+=9;
			data_p+=9;
		}
	}
//EA = 1;
}
/**********************************************************
 * @function    SpiOsdWinFillColor
 * @brief   color will be an offset from the LUT location that Window have. 
 * @param      None
 * @retval     Result
 **********************************************************/
 void	SpiOsdWinFillColor( uint8_t winno, uint8_t color )
{
	uint8_t	index;

	index = SpiOsdWinBase[winno];
	TW8836_WritePage( PAGE4_SOSD );

	if ( color ) {
		TW8836_WriteData( PAGE4_SOSD|index, (TW8836_Read( PAGE4_SOSD|index ) | 0x04));				// en Alpha & Global
	}
	else {
		TW8836_WriteData( PAGE4_SOSD|index, ( TW8836_Read( PAGE4_SOSD|index ) & 0xFB ) );				// dis Alpha & Global
	}
	index = SpiOsdWinBase[winno] + SPI_OSDWIN_FILLCOLOR;
	if(!winno)	index += 8;
	TW8836_WriteData( PAGE4_SOSD|index, color );
}

/**********************************************************
 * @function    SpiOsdWinHZoom
 * @brief   cSpiOsdWinHZoom
 * @param      None
 * @retval     Result
 **********************************************************/
void SpiOsdWinHZoom(uint8_t winno, uint8_t en)
{
	uint32_t index;
	uint8_t dat;

	index = SpiOsdWinBase[winno] + SPI_OSDWIN_HZOOM;

	TW8836_WritePage(PAGE4_SOSD );
	dat = TW8836_Read(PAGE4_SOSD|index);
	if( en ) 	TW8836_WriteData(PAGE4_SOSD|index, dat | 0x02);
	else     	TW8836_WriteData(PAGE4_SOSD|index, dat & ~0x02);

}

void MeasSetWindow( uint32_t x, uint32_t y, uint32_t w, uint32_t h )
{	
	//TW8835 needs minimum 2 Horizontal start position
	if(x < 2)
		x = 2;

	TW8836_WritePage(PAGE5_MEAS );
	TW8836_Write2Data(REG500_MEAS_HSTART_MSB, REG501_MEAS_HSTART_LSB, x);		
	TW8836_Write2Data(REG502_MEAS_HLEN_MSB,   REG503_MEAS_HLEN_LSB,   w);

	TW8836_Write2Data(REG505_MEAS_VSTART_MSB, REG505_MEAS_VSTART_LSB, y);		
	TW8836_Write2Data(REG506_MEAS_VLEN_MSB,   REG507_MEAS_VLEN_LSB,   h);
}

void MeasSetField(uint8_t field)
{
	TW8836_WritePage(PAGE5_MEAS );
	TW8836_WriteData(REG508, TW8836_Read(REG508) & 0xF3 | (field << 2) );	// Note:DO not turn on the start
}

void	InitMeasure(void)
{
	MeasSetWindow( 32, 32, 1600, 1200 );
	MeasSetField(2);					//both	
}
#endif












































