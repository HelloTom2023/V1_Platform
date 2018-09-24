#ifndef _SOFT_I2C_H
#define _SOFT_I2C_H

typedef struct {    
   uint8_t		addr;
   uint8_t		State;
   void		(*I2c_Init)(void);
   void		(*SCL_Dir)(uint8_t);
   void		(*SDA_Dir)(uint8_t);
   void		(*SCL_out)(uint8_t);
   void		(*SDA_out)(uint8_t);  
   void		(*I2c_Delay)(void);
   uint8_t        (*I2c_GetSDA)(void); 
}tI2CHwCtlBlock;


#define	SOFTI2C_PORT_INPUT		0
#define	SOFTI2C_PORT_OUTPUT		1

#define I2C_ERROR		0
#define I2C_OK			1

extern uint8_t SoftI2c_Write(uint8_t CAddr,tI2CHwCtlBlock *i2c, uint8_t Sid, uint8_t *pData, uint8_t len);
extern uint8_t SoftI2c_Read(uint8_t CAddr,tI2CHwCtlBlock *i2c, uint8_t Sid, uint8_t *pData, uint8_t len);

#endif

