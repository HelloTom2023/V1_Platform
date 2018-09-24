/**********************************************************
 * @file        tw8836_ctrl.h
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
#ifndef TW8836_CTRL_H
#define TW8836_CTRL_H

#ifdef D_VIDEO_SWITCH_TW8836
#ifdef TW8836_CTRL
#define EXTERN
#else
#define EXTERN extern
#endif

#define TW8836_TICK_BASE        2
#define TW8836Delay(x)            (x)/TW8836_TICK_BASE

#define TW8836_GetInputCH()       sVideo.SysVch

#define TW8836_ALL_SRC_OPEN_GAMMA

//===========================================================================================
// Windows Finctions
//===========================================================================================
#define SPI_OSD_ST              0x00
#define SPI_WIN0_ST             0x20
#define SPI_WIN1_ST             0x40
#define SPI_WIN2_ST             0x50
#define SPI_WIN3_ST             0x60
#define SPI_WIN4_ST             0x70
#define SPI_WIN5_ST             0x80
#define SPI_WIN6_ST             0x90
#define SPI_WIN7_ST             0xA0
#define SPI_WIN8_ST             0xB0


#define SPI_OSDWIN_SCREEN               0x01
#define SPI_OSDWIN_BUFFERSTART          0x07
#define SPI_OSDWIN_BUFFERSTART_BIT      0x0A
#define SPI_OSDWIN_DISPSIZE             0x0A
#define SPI_OSDWIN_DISPOFFSET           0x0D
#define SPI_OSDWIN_ALPHA                0x0C    //430(42C+4), 44C
#define SPI_OSDWIN_LUT_PTR              0x0D    //431(42D+4), 44D
#define SPI_OSDWIN_FILLCOLOR            0x0E    //436(42E+8), 44E
#define SPI_OSDWIN_ANIMATION            0x12    //432

//UI Start
#define     offsetendbin  0x50000 //offset address for SPI writing
#define      ALL_LUTS               (offsetendbin+0x000000)
#define     PAM_BTN_MODE0      (offsetendbin+0x000400)
#define     PAM_BTN_MODE1      (offsetendbin+0x16B0)
#define     PAM_BTN_MODE2      (offsetendbin+0x002960)
#define     RADAR_CAMERA_BLEFT1_1       (offsetendbin+0x003C10)
#define     RADAR_CAMERA_BLEFT1_2       (offsetendbin+0x003F10)
#define     RADAR_CAMERA_BLEFT1_3       (offsetendbin+0x004210)
#define     RADAR_CAMERA_BLEFT2_1       (offsetendbin+0x004510)
#define     RADAR_CAMERA_BLEFT2_2       (offsetendbin+0x004B40)
#define     RADAR_CAMERA_BLEFT2_3      (offsetendbin+0x005170)
#define     RADAR_CAMERA_BRIGHT1_1       (offsetendbin+0x0057A0)
#define     RADAR_CAMERA_BRIGHT1_2       (offsetendbin+0x005AA0)
#define     RADAR_CAMERA_BRIGHT1_3       (offsetendbin+0x005DA0)
#define     RADAR_CAMERA_BRIGHT2_1       (offsetendbin+0x0060A0)
#define     RADAR_CAMERA_BRIGHT2_2       (offsetendbin+0x0066D0)
#define     RADAR_CAMERA_BRIGHT2_3       (offsetendbin+0x006D00)
#define     RADAR_CAMERA_FLEFT_1        (offsetendbin+0x007330)
#define     RADAR_CAMERA_FLEFT_2        (offsetendbin+0x007960)
#define     RADAR_CAMERA_FLEFT_3      (offsetendbin+0x007F90)
#define     RADAR_CAMERA_FRIGHT_1         (offsetendbin+0x0085C0)
#define     RADAR_CAMERA_FRIGHT_2        (offsetendbin+0x008BF0)
#define     RADAR_CAMERA_FRIGHT_3      (offsetendbin+0x009220)
#define     RADAR_CAMERA_ICON_CAR      (offsetendbin+0x000DC0)

//BMP size
#define PAM_BTN_PARK_W  92
#define PAM_BTN_PARK_H   52

#define RADAR_CAMERA_FLEFT_W  0x024
#define RADAR_CAMERA_FLEFT_H  0x02A

#define RADAR_CAMERA_FRIGHT_W 0x024
#define RADAR_CAMERA_FRIGHT_H 0x02A

#define RADAR_CAMERA_BLEFT1_W 0x018
#define RADAR_CAMERA_BLEFT1_H 0x021

#define RADAR_CAMERA_BLEFT2_W 0x024
#define RADAR_CAMERA_BLEFT2_H 0x02A

#define RADAR_CAMERA_BRIGHT1_W 0x018
#define RADAR_CAMERA_BRIGHT1_H 0x021

#define RADAR_CAMERA_BRIGHT2_W 0x024
#define RADAR_CAMERA_BRIGHT2_H 0x02A


#define WIN_ENA(x) (x)   // 0xN0
#define WIN_PIXLW 0x80
#define WIN_PERPIX 0x20
#define WIN_ALPHA_ENA 0x10
#define WIN_NUM(x) (x)

#define WIN_ALPHA(x) (x & 0x7f) // 0xNc

#define WIN_HS_HB(x) ((x>>8) & 0x07) // 0xN1
#define WIN_HS_LB(x) (x & 0xff)   // 0xN2
#define WIN_VS_HB(x) ((x>>4) & 0x70)
#define WIN_VS_LB(x) (x & 0xff)   // 0xN3

#define WIN_HL_HB(x) ((x>>8) & 0x0f)  // 0xN4
#define WIN_HL_LB(x) (x & 0xff)   // 0xN5
#define WIN_VL_HB(x) ((x>>4) & 0xf0)
#define WIN_VL_LB(x) (x & 0xff)   // 0xN6

#define WIN_BFM_AST_HB(x) ((x>>16) & 0xff)  // 0xN7
#define WIN_BFM_AST_MB(x) ((x>>8) & 0xff)   // 0xN8
#define WIN_BFM_AST_LB(x) (x & 0xff)   // 0xN9

#define WIN_BFM_HL_HB(x) ((x>>8) & 0x0f)  // 0xNa
#define WIN_BFM_HL_LB(x) (x & 0xff)  // 0xNb

#define WIN_TBLOFS(x) (x & 0x0f)  // 0xNd
#define WIN_FCOLOR(x) (x)   // 0xNe

#if 1
#define VIDEO_CVBS_NULL  0
#define VIDEO_CVBS_CAM1  1
#define VIDEO_CVBS_CAM2  2
#define VIDEO_CVBS_CAM3  3
#define VIDEO_CVBS_CAM4  4
#define VIDEO_CVBS_DTV  3
#define VIDEO_CVBS_AUX  4
#define VIDEO_CVBS_DVD  5
#else
#define VIDEO_CVBS_NULL  0
#define VIDEO_CVBS_CAM1  1
#define VIDEO_CVBS_CAM2  2
#define VIDEO_CVBS_DTV  3
#define VIDEO_CVBS_DVD  4
#endif

#define OSD_WIN_REGBUF 18
#define OSD_WIN_SPIADDR 5

#define Park_Bmp_Mode1    0
#define Park_Bmp_Mode2    1
#define Park_Bmp_Mode3    2
//-----------------------------------------------------------------------------

// Startup Steps
typedef enum Tw8836_register_step_enum
{
    TW8836_REGISTER_START = 0,
    TW8836_REGISTER_CLOCK,
    TW8836_REGISTER_SPIDMA,
    TW8836_REGISTER_TRIEN, /*Tristate all output pins*/
    TW8836_REGISTER_LVDS,
    TW8836_REGISTER_GAMMA,
    TW8836_REGISTER_LVDSTX,
    TW8836_REGISTER_OPEN_TFT,
    TW8836_REGISTER_SETCVBS1_START,
    TW8836_REGISTER_SETCVBS1_END,
    TW8836_REGISTER_SETCVBS2_START,
    TW8836_REGISTER_SETCVBS2_END,
     TW8836_REGISTER_SETCVBS3_START,
    TW8836_REGISTER_SETCVBS3_END,
    TW8836_REGISTER_END,
} TW8836_REGISTER_ENUM;


typedef enum
{
    e_NONE_INPUT_OUT_NULL = 0,
    e_LVDS_INPUT_LVDS_OUT = 1,
    e_CVBS_INPUT_LVDS_OUT,
    e_CVBS2_INPUT_LVDS_OUT,
    e_CVBS_INPUT_BT656_OUT,
} E_SCREENPARAMETERMODE;


typedef struct
{
    bit_t     RefreshStatus       :1;
    bit_t     ParkUiInit      :1;
    bit_t     CamPwr      :2;
    bit_t     ParkMode      :4;
    bit_t     ADI7186OSDFlag :1;
} tREVERSE_FLAG;

typedef union
{
    tREVERSE_FLAG OsdShow;
    uint8_t byte;
} uREVERSE_FLAG;

typedef struct
{
    TW8836_REGISTER_ENUM  DrvStep;
    uint8_t  LvdsOnStep;
    uint8_t  DrvSubStep;
    uint16_t  DrvDelay;
    uint8_t  ReadData;
	
    uint8_t  GammaCount;
    uint8_t OsdUpdateStep;
    uint8_t ADI7186OSDStep;
    uint8_t ADI7186DVRFlag;
    uint8_t ADI7186OVERLAYDisable;
	uint8_t ADI7186InitProgramme; //snake20161109初始化参数刷新完成标志...
    E_SCREENPARAMETERMODE  BackScreenMode;
    uint8_t  CvbsCurType;
    uREVERSE_FLAG  ReverseFlag;
   uint8_t OsdBuffData[65]; /*64+1*/
    uint16_t Tw8836_PacketId;
    uint8_t Tw8836_UpgradeOKFlage;
    uint8_t WriteRegStep;
    uint8_t ADI7186_OverlayFlag;
	uint8_t ADI7186_OverlayProgrammeFlag;
    uint8_t  ADI7186CvbsDetStep;
    uint8_t ADI7186_ReverseStartFlag;
    uint8_t ADI7186_ReverseStopFlag;
    uint8_t AVM_OsShowFlag;
    uint8_t  LockData;
    uint8_t  LockFlag;
    uint8_t  AINSEL;
	uint8_t CurrentCvbsChannel;
	uint8_t  ADI7186_ProgrammeOver;
} TW8836_STRUCT;

#define ReverseParkRefreshFlag  fTw8836.ReverseFlag.OsdShow.RefreshStatus
#define ReverseParkUiInit  fTw8836.ReverseFlag.OsdShow.ParkUiInit
#define ReverseParkModeFlag  fTw8836.ReverseFlag.OsdShow.ParkMode
#define ReversePwrFlag  fTw8836.ReverseFlag.OsdShow.CamPwr
#define ADIReversePwrFlag  fTw8836.ReverseFlag.OsdShow.ADI7186OSDFlag

EXTERN TW8836_STRUCT fTw8836;
EXTERN TW8836_STRUCT rTw8836;


EXTERN void Tw8836_InitVariable(void);
EXTERN uint8_t TW8836_ScreenParameterLoad(const uint8_t *RegSet,uint8_t num);
EXTERN uint8_t Tw8836_Regsiter(void);
EXTERN uint8_t Tw8836_DownloadOsdBmp(uint8_t winno, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t spi_addr, uint8_t En);
EXTERN void Tw8836_ShowOsd(void);
EXTERN void  TW8836_BackLight(uint8_t on);
EXTERN void TW8836_SetLvdsTxEnable(void);
EXTERN uint8_t ADI7186_SetRst(void);
EXTERN uint8_t ADI7186_ClearRst(void);   
EXTERN void ADI7186_Disposal(void);
EXTERN void ADI7186_CvbsLockDet();
#undef EXTERN

#endif

#endif

