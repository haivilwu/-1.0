#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void LED_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  GPIO_InitTypeDef GPIO_a1;
	  GPIO_a1.GPIO_Mode=GPIO_Mode_Out_PP;
	  GPIO_a1.GPIO_Pin=GPIO_Pin_All ;
	  GPIO_a1.GPIO_Speed=GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA,&GPIO_a1);
}


void Water_lamp(void)
{
		 GPIO_Write(GPIOA,~0x0001);
		 Delay_ms(500);
		GPIO_Write(GPIOA,~0x0002);
		 Delay_ms(500);
		GPIO_Write(GPIOA,~0x0004);
		 Delay_ms(500);
		GPIO_Write(GPIOA,~0x0008);
		 Delay_ms(500);
		GPIO_Write(GPIOA,~0x00010);
		 Delay_ms(500);
		GPIO_Write(GPIOA,~0x0020);
		 Delay_ms(500);
		GPIO_Write(GPIOA,~0x0040);
		 Delay_ms(500);
		GPIO_Write(GPIOA,~0x0080);
		 Delay_ms(500);
}
