#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
void key_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_init;
	GPIO_init.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_init.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_init);
	
	GPIO_init.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_init.GPIO_Pin=GPIO_Pin_4;
	GPIO_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_init);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}


uint8_t key_GetNum(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	uint8_t keynum;
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==0)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		Delay_ms(20);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==0);
		keynum=0;
	}
	else
	{
	keynum=1;
	}
	return keynum;
}
