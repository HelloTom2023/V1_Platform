#ifndef AMP_DRV_H
#define AMP_DRV_H

// Struct
typedef struct amp_struct
{
    uint8_t Ready;     //device ready to control    
    uint8_t Module;
    //Driver Control
    uint8_t DrvStep;        //Driver Control Step
    uint8_t DrvResult;    //Driver Execute Result 
    uint8_t DrvOverTime;
    uint8_t DrvBuff[5];
    uint8_t DrvRead[5];
    // Ak Control
    uint8_t Step;
    uint16_t Delay;
    uint8_t ChkCnt;
}AMP_STRUCT;

#define AMP_TICK_BASE        2
#define AmpDelay(x)            (x)/AMP_TICK_BASE

typedef enum amp_rst_step_enum
{
    AMP_RST_CHK_BUS = 0,        //Check BUS Status
    AMP_RST_CHK_DEV,        // Check Device Status
    AMP_RST_END,            // Reset End
}AMP_RST_STEP_ENUM;

#ifdef D_AMP_TDF8546
#define AMP_CS_ADDR      0xD4    //  Chip Selection Address     
#endif
#ifdef D_AMP_TDA75610
#define AMP_CS_ADDR      0xD8    //  Chip Selection Address     
#endif
#define AMP_IIC    		I2C2    //  Used I2c Port

#ifdef 	D_AMP_TDA7388
#define Amp_WritePdat(Dat,Num,CallBack) (SUBLAYER_DONE)
#define Amp_Read(Dat,Num,CallBack)  (SUBLAYER_DONE)
#else
#define Amp_WritePdat(Dat,Num,CallBack) I2C_Write(AMP_IIC,AMP_CS_ADDR,TRUE,Dat,Num,TRUE,CallBack,I2C_74KBPS)
#define Amp_Read(Dat,Num,CallBack)  I2C_Read(AMP_IIC,AMP_CS_ADDR,TRUE,Dat,Num,TRUE,CallBack,I2C_74KBPS)
#endif

extern AMP_STRUCT AmpCtl;
extern uint8_t Amp_CallBack_Common(uint8_t Result);
extern uint8_t Amp_WriteCommon(uint8_t* Dat, uint8_t Num);
extern uint8_t Amp_ReadCommon(uint8_t num);
extern void 	Amp_InitVariable(void);
extern void Amp_TimerDeal(void);

extern uint8_t Amp_OpenPower(void);
extern uint8_t Amp_Reset(void);
extern uint8_t Amp_Register(void);
extern uint8_t Amp_Mute(uint8_t Mode);
extern void 	Amp_Detect(void);

#endif
