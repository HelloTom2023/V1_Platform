#include "..\..\..\User\src_user\config\inc.h"

#if 1
void I2CStart(tI2CHwCtlBlock *i2c)
{
    i2c->SDA_Dir(SOFTI2C_PORT_OUTPUT);
    i2c->SCL_Dir(SOFTI2C_PORT_OUTPUT);

    i2c->SDA_out(1);
    i2c->I2c_Delay();
    i2c->SCL_out(1);
    i2c->I2c_Delay();
    i2c->SDA_out(0);
    i2c->I2c_Delay();
    i2c->SCL_out(0);
    i2c->I2c_Delay();
}

void I2CStop(tI2CHwCtlBlock *i2c)
{
    i2c->SDA_Dir(SOFTI2C_PORT_OUTPUT);
    i2c->SDA_out(0);
    i2c->I2c_Delay();
    i2c->SCL_out(1);
    i2c->I2c_Delay();
    i2c->SDA_out(1);
    i2c->I2c_Delay();
}

uint8_t I2COut8Bit(tI2CHwCtlBlock *i2c, uint8_t outbyte)
{
    uint8_t i;
    uint16_t cnt = 0;
    i2c->SDA_Dir(SOFTI2C_PORT_OUTPUT);

    for(i = 0x80; i > 0; i >>= 1)
    {
        i2c->I2c_Delay();
        i2c->SCL_out(0);
        //i2c->I2c_Delay();
        if(outbyte & i)
            i2c->SDA_out(1);
        else
            i2c->SDA_out(0);
        //i2c->I2c_Delay();
        i2c->SCL_out(1);
    }
    i2c->I2c_Delay();
    i2c->SCL_out(0);

    //i2c->I2c_Delay();
    //i2c->SDA_out(1);
    i2c->SDA_Dir(SOFTI2C_PORT_INPUT);
    i2c->I2c_Delay();

    i2c->SCL_out(1);
    i2c->I2c_Delay();
    cnt = 5000;
    while(cnt--)
    {
        if(i2c->I2c_GetSDA())
        {
            i =I2C_ERROR;
        }
        else
        {
            i=I2C_OK;
	     break;
        }
    }
    i2c->SCL_out(0);
    i2c->I2c_Delay();
    return i;
}

uint8_t I2CIn8Bit(tI2CHwCtlBlock *i2c)
{
    uint8_t i =0,inbyte=0;

    i2c->SDA_Dir(SOFTI2C_PORT_INPUT);
    for(i = 0x80; i > 0; i >>= 1)
    {
        i2c->SCL_out(1);

        i2c->I2c_Delay();
        if(i2c->I2c_GetSDA())
        {
            inbyte |=i;
        }

        i2c->SCL_out(0);
        i2c->I2c_Delay();
    }
    return (inbyte);
}

void I2CAck(tI2CHwCtlBlock *i2c)
{
    i2c->SDA_Dir(SOFTI2C_PORT_OUTPUT);
    i2c->SDA_out(0);
    i2c->I2c_Delay();
    i2c->SCL_out(1);
    i2c->I2c_Delay();
    i2c->SCL_out(0);
    i2c->SDA_Dir(SOFTI2C_PORT_INPUT);
    i2c->I2c_Delay();

}

void I2CNAck(tI2CHwCtlBlock *i2c)
{
    i2c->SDA_Dir(SOFTI2C_PORT_OUTPUT);
    i2c->SDA_out(1);
    i2c->I2c_Delay();
    i2c->SCL_out(1);
    i2c->I2c_Delay();
    i2c->SCL_out(0);
    i2c->SDA_Dir(SOFTI2C_PORT_INPUT);
    i2c->I2c_Delay();
}

uint8_t SoftI2c_Write(uint8_t CAddr, tI2CHwCtlBlock *i2c, uint8_t Sid, uint8_t *pData, uint8_t len)
{
    uint8_t u8i= 0;
    uint8_t Ret = 0;
	
    i2c->addr=CAddr;
    I2CStart(i2c);
    Ret = I2COut8Bit(i2c, i2c->addr);
    Ret &= I2COut8Bit(i2c, Sid);

    for(u8i = 0; u8i < len; u8i ++)
    {
        Ret &= I2COut8Bit(i2c, pData[u8i]);
    }
    I2CStop(i2c);
    return Ret;
}

uint8_t SoftI2c_Read(uint8_t CAddr,tI2CHwCtlBlock *i2c, uint8_t Sid, uint8_t *pData, uint8_t len)
{
    uint8_t u8i= 0;
    uint8_t Ret = 0;
	
    i2c->addr=CAddr;
    I2CStart(i2c);
    Ret = I2COut8Bit(i2c, i2c->addr);
    Ret &= I2COut8Bit(i2c, Sid);
    I2CStart(i2c);
    Ret &= I2COut8Bit(i2c, i2c->addr|0x01);

    while(u8i < len)
    {
        pData[u8i]= I2CIn8Bit(i2c);
        u8i++;
        if(u8i <len)
        {
            I2CAck(i2c);
            Ret &= I2C_OK;
        }
        else
        {
            I2CNAck(i2c);
            Ret &= I2C_ERROR;
        }
    }
    I2CStop(i2c);
    return Ret;
}

/*************************************************************************************/
#else
void SoftI2c_Init(void)
{
    PMC3H0 = 0;     // io mode
    PMC3H1 = 0;
    PF3H0 = 1;      //OP output
    PF3H1 = 1;      //op output
    IIC_SCL_SET();
    IIC_SDA_SET();
}

void M_WAIT_1US(void)
{
    uint8_t i = 5;
    while(i-- > 0);
}

void I2CStart(void)
{
    //IIC_SDA_Config(OUTPUT_MODE);
    IIC_SDA_OUTPUT();
    //IIC_SCL_Config(OUTPUT_MODE);
    IIC_SCL_OUTPUT();
    IIC_SDA_SET();
    M_WAIT_1US();
    IIC_SCL_SET();
    M_WAIT_1US();
    IIC_SDA_CLR();
    M_WAIT_1US();
    IIC_SCL_CLR();
    M_WAIT_1US();
}

void I2CStop(void)
{
    //IIC_SDA_Config(OUTPUT_MODE);
    IIC_SDA_OUTPUT();
    IIC_SDA_CLR();
    M_WAIT_1US();
    IIC_SCL_SET();
    M_WAIT_1US();
    IIC_SDA_SET();
    M_WAIT_1US();

}

uint8_t I2COut8Bit(uint8_t outbyte)
{
    uint8_t i;
    uint8_t cnt = 0;
    //IIC_SDA_Config(OUTPUT_MODE);
    IIC_SDA_OUTPUT();
    for(i = 0x80; i > 0; i >>= 1)
    {
        M_WAIT_1US();
        IIC_SCL_CLR();
        M_WAIT_1US();
        if((outbyte & i) != 0)
            IIC_SDA_SET();
        else
            IIC_SDA_CLR();
        M_WAIT_1US();
        IIC_SCL_SET();
    }
    M_WAIT_1US();
    IIC_SCL_CLR();

    M_WAIT_1US();
    IIC_SDA_SET();
    //IIC_SDA_Config(INPUT_MODE);
    IIC_SDA_INPUT();
    M_WAIT_1US();

    IIC_SCL_SET();
    M_WAIT_1US();
    if(GetIICSDA())
    {
        i =I2C_ERROR;
    }
    else
    {
        i=I2C_OK;
    }

    IIC_SCL_CLR();

    M_WAIT_1US();
#if 0
    cnt = 0;            /*assure the SDA has been released by the slave */
    while(GetIICSDA() != Bit_SET)
    {
        cnt++;
        if(cnt>10)
        {
            break;  /*try 10 times most, otherwise,jump out the check routine */
        }
        M_WAIT_1US();   /*generate ACK SCL pulse */
        IIC_SCL_SET();
        M_WAIT_1US();
        IIC_SCL_CLR();
        M_WAIT_1US();
    }
#endif
    return i;
}
uint8_t I2CIn8Bit(void)
{
    uint8_t i =0,inbyte=0;

    //IIC_SDA_Config(INPUT_MODE);
    IIC_SDA_INPUT();
    for(i = 0x80; i > 0; i >>= 1)
    {
        IIC_SCL_SET();

        M_WAIT_1US();
        if(GetIICSDA())
        {
            inbyte |=i;
        }

        IIC_SCL_CLR();
        M_WAIT_1US();
    }

    return (inbyte);
}

void I2CAck(void)
{
    //IIC_SDA_Config(OUTPUT_MODE);
    IIC_SDA_OUTPUT();
    IIC_SDA_CLR();
    M_WAIT_1US();
    IIC_SCL_SET();
    M_WAIT_1US();
    IIC_SCL_CLR();
    //IIC_SDA_Config(INPUT_MODE);
    IIC_SDA_INPUT();
    M_WAIT_1US();

}
void I2CNAck(void)
{

    //IIC_SDA_Config(OUTPUT_MODE);
    IIC_SDA_OUTPUT();
    IIC_SDA_SET();
    M_WAIT_1US();
    IIC_SCL_SET();
    M_WAIT_1US();
    IIC_SCL_CLR();
    //IIC_SDA_Config(INPUT_MODE);
    IIC_SDA_INPUT();
    M_WAIT_1US();
}

void SoftI2c_Write(uint8_t Id, uint8_t Sid, uint8_t *pData, uint8_t len)
{
    uint8_t u8i= 0;
    uint8_t Ret = 0;

    I2CStart();
    Ret = I2COut8Bit(Id);
    Ret|= I2COut8Bit(Sid);

    for(u8i = 0; u8i < len; u8i ++)
    {
        Ret|= I2COut8Bit(pData[u8i]);
    }
    I2CStop();
}

uint8_t SoftI2c_Read(uint8_t Id, uint8_t Sid, uint8_t *pData, uint8_t len)
{
    uint8_t u8i= 0;
    uint8_t Ret = 0;

    I2CStart();
    Ret = I2COut8Bit(Id);
    Ret|= I2COut8Bit(Sid);
    I2CStart();
    Ret |= I2COut8Bit(Id|0x01);

    while(u8i < len)
    {
        pData[u8i]= I2CIn8Bit();
        u8i++;
        if(u8i <len)
        {
            I2CAck();
        }
        else
        {
            I2CNAck();
        }
    }
    I2CStop();
    return Ret;
}

#endif
