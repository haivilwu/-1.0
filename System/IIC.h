#ifndef IIC_H
#define IIC_H
void IIC_Write_SCL(uint8_t data);
void IIC_Write_SDA(uint8_t data);
uint8_t IIC_Read_SDA(void);
void IIC_Init(void);
void IIC_start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t data);
uint8_t IIC_Read_Byte(void);
void IIC_Send_ACK(uint8_t ACK_Bit);
uint8_t IIC_Read_ACK(void);
#endif

