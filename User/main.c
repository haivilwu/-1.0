#include "stm32f10x.h"
#include "KEY.h"
#include "Delay.h"
#include "OLED.h"
#include "IIC.h"

int main()
{
	key_init();
	OLED_Init();
	while(1)
	{
		display();
	}
}
