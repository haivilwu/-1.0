#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void IIC_Write_SCL(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)data);
}

void IIC_Write_SDA(uint8_t data)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)data);
}


uint8_t IIC_Read_SDA()
{
	uint8_t SDA_data;
	SDA_data=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	return SDA_data;
}

void IIC_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_Initstruct;
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
}

void IIC_start()
{
	IIC_Write_SDA(1);
	IIC_Write_SCL(1);
	IIC_Write_SDA(0);
	IIC_Write_SCL(0);
}

void IIC_Stop()
{
	IIC_Write_SDA(0);
	IIC_Write_SCL(1);
	IIC_Write_SDA(1);	
}

void IIC_Send_Byte(uint8_t data)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		IIC_Write_SDA(data&(0x80>>i));
		IIC_Write_SCL(1);
		IIC_Write_SCL(0);
	}
}

uint8_t IIC_Read_Byte()
{
	uint8_t i,data=0x00;
	for(i=0;i<8;i++)
	{
		IIC_Write_SDA(1);
		IIC_Write_SCL(1);
		if(IIC_Read_SDA()==1)
		{
			data|=(0x80>>i);
		}
		IIC_Write_SCL(0);
	}
	return data;
}

void IIC_Send_ACK(uint8_t ACK_Bit)
{
	IIC_Write_SDA(ACK_Bit);
	IIC_Write_SCL(1);
	IIC_Write_SCL(0);
}


uint8_t IIC_Read_ACK()
{
	uint8_t ACK_Bit=0x00;
	IIC_Write_SDA(1);
	IIC_Write_SCL(1);
	ACK_Bit=IIC_Read_SDA();
	IIC_Write_SCL(0);
	return ACK_Bit;
}

