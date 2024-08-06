#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void key_init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef B12,A1;
	A1.GPIO_Mode=GPIO_Mode_Out_PP;
	A1.GPIO_Pin=GPIO_Pin_1;
	A1.GPIO_Speed=GPIO_Speed_50MHz;
	B12.GPIO_Mode=GPIO_Mode_IPD;
	B12.GPIO_Pin=GPIO_Pin_12;
	B12.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&B12);
	GPIO_Init(GPIOA,&A1);
}

uint8_t key_GetNum()
{
	uint8_t keynum;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1)
	{
		Delay_ms(10);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		Delay_ms(1000);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	return keynum;
}
