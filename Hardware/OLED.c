#include "stm32f10x.h"
#include "OLED_Font.h"
#include "OLED.h"
#include "Delay.h"
#include "KEY.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/*引脚配置*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(x))
/*引脚初始化*/
void OLED_I2C_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//额外的一个时钟，不处理应答信号
	OLED_W_SCL(0);
}

/**
  * @brief  OLED写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLED写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */

void OLED_display_Address(uint8_t x_start,uint8_t x_terminate,uint8_t y_start,uint8_t y_terminate)
{
	OLED_WriteCommand(0x22);	//设置页地址命令
	OLED_WriteCommand(x_start);	//起始页地址
	OLED_WriteCommand(x_terminate);	//终止页地址
	OLED_WriteCommand(0x21);	//设置列地址命令
	OLED_WriteCommand(y_start);	//起始列地址
  OLED_WriteCommand(y_terminate);	//终止列地址
}
/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void)
{  
	uint16_t i;
	OLED_display_Address(0,7,0,127);
	for (i = 0; i <1024; i++)
	{
		OLED_WriteData(0x00);
	}
}

void OLED_Init(void)
{
	OLED_I2C_Init();			//端口初始化
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0x20);	//水平寻址
	OLED_WriteCommand(0x00);	//水平寻址
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0xf0);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);
  
	OLED_WriteCommand(0xAF);	//开启显示
	
	OLED_Clear();				//OLED清屏
}
void OLED_video_memory_()//oled显存
{  
	uint8_t *table=OLED_video_memory[0];
	uint16_t i;
	for (i = 0; i <1024; i++)
	{
		 OLED_WriteData(table[i]);
	}
}




/****************************************页局部清除************************************/
void Local_clearance(uint8_t y,uint8_t x,uint8_t Height,uint8_t width)
{
	uint8_t i,j;
	for(i=0;i<Height;i++)
	{
		for(j=0;j<width;j++)
		{
			OLED_video_memory[y+i][x+j]=0x00;
		}
	}
}
/****************************************页局部清除************************************/


/****************************************显示图片************************************/
void Display_picture(uint8_t y,uint8_t x,uint8_t Height,uint8_t width,const uint8_t *p)
{
	uint8_t i,j,data;
	for(i=0;i<Height;i++)
	{
		for(j=0;j<width;j++)
		{
			OLED_video_memory[i+y][j+x]=p[data];
			data++;
		}
	}
}
/****************************************显示图片************************************/

/****************************************求x的n次方************************************/
uint32_t x_power(uint32_t x,uint8_t power)
{
	uint32_t data=1;
	while(power--)
	{
		data*=x;
	}
	return data;
}
/****************************************求x的n次方************************************/

/****************************************显示一个数字************************************/
void Display_single_number(uint8_t y,uint8_t x,uint16_t number,uint8_t type)
{
	uint8_t i,j,data=0;
	if(type==16)
	{
		for(i=0;i<2;i++)
		{
			for(j=0;j<8;j++)
			{
				data++;
				OLED_video_memory[y+i][x+j]=F16X16[16+number][data-1];
			}
		}
	}
		if(type==8)
	{
		for(j=0;j<6;j++)
		{
			data++;
			OLED_video_memory[y][x+j]=char_5X7[number][data];
		}
	}
}
/****************************************显示多个数字************************************/


void Display_multiple_number(uint8_t y,uint8_t x,uint16_t number,uint8_t length,uint8_t type)
{
	uint8_t i;
	for(i=0;i<length;i++)
	{
		if(type==16)
		{
			Display_single_number(y,x+i*8,number/x_power(10,length-i-1)%10,type);
		}
		else
		{
			Display_single_number(y,x+i*6,number/x_power(10,length-i-1)%10,type);
		}
	}
}
/****************************************显示多个数字************************************/



/****************************************读一个位函数************************************/
/* x：在具体显示的位置之上进行写数据
	 y：在具体显示的位置之上进行写数据
	 *bmp： 要读取的图片
		w：要显示图片的宽
   set_pixel：判断写0写1
																																									*/
uint8_t GetPixel_For_Scroll(short x,short y,const uint8_t *bmp,uint8_t w)
{
	const uint8_t *p=bmp;
	/*指向要读的数组的首地址*/
	p+=x+(y/8)*w;	 /*指向要读取的像素点，比如有一个3x3的图片bmp[2][3]，我们要得到第2列
	//第2行的数据x=2+(y=2/1)*3=8;把bmp[2][3]换成bmp[8]，刚好是第2行第2列,可以画一个3x3
	的格子，这样便于理解*/
	if(*p>>(y%8)&0x01)return 1;
	/*对p指向的数据进行处理，比如*p=0x02;换成二进制:0000 0010，*p的每一个位都对应0~7行，
	向oled写数据是低位在前，右移1为0x01&=0x01；就是取最低位	*/
	return 0;
}
/****************************************读一个位函数************************************/

/****************************************写一个位函数************************************/
/* X：列具体显示位置
	 Y：行具体显示位置
	 x：在具体显示的位置之上进行写数据
	 y：在具体显示的位置之上进行写数据
   set_pixel：判断写0写1
																																									*/
void SetPixel_For_Scroll(short X,short Y,short x,short y,uint8_t set_pixel)
{
	if(set_pixel)//判断GetPixel_For_Scroll函数返回的数据
	{
		if((X+x<128&&Y+y<64&&X+x>0&&Y+y>0))
		OLED_video_memory[(Y+y)/8][X+x]|=(0x01<<((Y+y)%8));
		/*比如我们要往oled第18行64列写1,Y=16,y=2,X=64,x=0;(Y+y)/8=16,X=x=64,
		OLED_video_memory[16][64]=0x00;((Y+y)%8)=2,0x01<<2;0x04,0x00|0x04=0x04,
		二进制：0000 0100,每个位都对应一行16行64列0，17行64列0，18行64列1，这样
		就可以往oled第18行64列写1了*/
	}
	else
	{
		if((X+x<128&&Y+y<64&&X+x>0&&Y+y>0))
		OLED_video_memory[(Y+y)/8][X+x]&=~(0x01<<((Y+y)%8));
		/*比如我们要往oled第18行64列
		写0,Y=16,y=2,X=64,x=0;(Y+y)/8=16,X=x=64,OLED_video_memory[16][64]=0x08;
		((Y+y)%8)=2,0x01<<2;0x04,0x07&~0x04;
		0000 0111
	&	1111 1011
		0000 0011 
		每个位都对应一行
		16行64列1，17行64列1，18行64列0，这样就可以往oled第18行64列写0了*/
	}
}

/****************************************显示字符串************************************/
void Display_char(short y,short x,const uint8_t *char_)
{
	uint8_t i,j,k,data=0x00;
	for(k=0;char_[k] !='\0';k++)// 字符串数组都以‘\0’结尾
	{
		for(i=0;i<16;i++)
		{
			for(j=0;j<8;j++)
			{
				data=GetPixel_For_Scroll(j,i,F16X16[char_[k]-' '],8);
				if(data==1)
				SetPixel_For_Scroll(x+(k*8),y,j,i,data);
			}
		}
	}
}
/****************************************显示字符串************************************/



/****************************************指定点填充************************************/

void Local_clearance_1(uint8_t y,uint8_t x,uint8_t y1,uint8_t x1,uint8_t data)
{
	uint8_t i,j;
	for(i=0;i<y1;i++)
	{
			for(j=0;j<x1;j++)
			{
				if(x+j<128)
				SetPixel_For_Scroll(x,y,j,i,data);
			}
		
	}
}

/****************************************指定点反显************************************/
void specified_point_mirrored(uint8_t y,uint8_t x,uint8_t wide,uint8_t height)
{
	uint8_t i,j=0,data=0x00;
	for(i=0;i<height;i++)
	{
		for(j=0;j<wide;j++)
		{
			data=GetPixel_For_Scroll(x+j,y+i,OLED_video_memory[0],128);
			data=~data&0x01;
			SetPixel_For_Scroll(x,y,j,i,data);
		}
	}
}
/****************************************指定点反显************************************/


/****************************************指定点显示图片************************************/
void Display_picture1(uint8_t y,uint8_t x,uint8_t Height,uint8_t width,const uint8_t *p,uint8_t w)
{
	uint8_t i,j,data;
	for(i=0;i<Height;i++)
	{
		for(j=0;j<width;j++)
		{
			data=GetPixel_For_Scroll(j,i,p,w);
			if(data==1)
			SetPixel_For_Scroll(x,y,j,i,data);
		}
	}
}
/****************************************指定点显示图片************************************/

/****************************************选中标签************************************/
void Select_icon(short y,short x,short wide,uint8_t height,short index)
{
	static int  Anim_x=0, Anim_y=0, offs_x=0,offs_y=0;
	int X,Y;
	uint8_t i,j=0,t=0,data=0x00,speed=0;
	for(i=0;i<height;i++)
	{
		switch(i)//绘制选中标签棱角
		{
			case 0:
			t=j=4;break;
			case 1:
			t=j=3;break;
			case 2:
			t=j=2;break;
			case 3:
			t=j=1;break;
			
			case 13:
			t=j=1;break;
			case 14:
			t=j=2;break;
			case 15:
			t=j=3;break;
			case 16:
			t=j=4;break;
			default:t=j=0;break;
		}
		for(j=j;j<(offs_x)-t;j++)
		{
			data=GetPixel_For_Scroll(x+j,(y+offs_y)+i,OLED_video_memory[0],128);
			data=~data&0x01;//读现存然后将读到的数据取反再写回原位
			SetPixel_For_Scroll(x,y+offs_y,j,i,data);
		}
	}
			X = wide;	
			Y = index * 16;	
			if(X > Anim_x)
			{                                                   
				speed = ((X - Anim_x) / 3) + 1;
				if(speed > 16)
					speed = 16;
				Anim_x += speed;
				if(X <= Anim_x)
					Anim_x = X;
			}
			else if(X < Anim_x)
			{
				speed = ((Anim_x - X) / 3) + 1;
				if(speed > 16)
					speed = 16;
				Anim_x -= speed;
				if(Anim_x <= X)
					Anim_x = X;
			}
			if(Y > Anim_y)
			{
				speed = ((Y - Anim_y) / 3) + 1;
				if(speed > 8)
					speed = 8;
				Anim_y += speed;
				if(Y <= Anim_y)
					Anim_y = Y;
			}
			else if(Y < Anim_y)
			{
				speed = ((Anim_y - Y) / 3) + 1;
				if(speed > 8)
					speed = 8;
				Anim_y -= speed;
				if(Anim_y <= Y)
					Anim_y = Y;
			}
			offs_x=Anim_x;
			offs_y=Anim_y;
}
/****************************************选中标签************************************/



uint8_t *p[8]={"nb111\0","nb2\0","nb333\0","nb4\0","nb555\0","nb6\0","nb777\0","nb8\0"};

uint8_t a[]={48,32,48,32,48,32,48,32};
char c,f;
short d;
void display()
{
	short e=0x00;
	static short Anim_y;
	short Y;
	uint8_t speed=0x00;
	memset(OLED_video_memory,0,1024);//每次刷新把显出全部清屏
	if(!key_GetNum(GPIOA,GPIO_Pin_1))//按键
	{
		c>2&&d>-4?d-=1:d;//只有光标到底了最屏幕的最底部文字才能向上移动
		c<3?c++:c;//光标到达了屏幕的最底部，就不用移动光标了
		f<7?f++:f;
	}else
	if(!key_GetNum(GPIOA,GPIO_Pin_2))//按键
	{
		if(d<0)d+=1;//
		else c>0?c-=1:c;
		f>0?f--:f;
	}
	Y =  d * 16;
	if(Y > Anim_y)
	{
		speed = ((Y - Anim_y) / 3) + 1;//就是一个随着距离越近速度越来越低的算法，可通过调整除数的大小来调节非线性运动的速度
		if(speed > 8)
			speed = 8;
		Anim_y += speed;
		if(Y <= Anim_y)
			Anim_y = Y;
	}
	else if(Y < Anim_y)
	{
		speed = ((Anim_y - Y) / 3) + 1;
		if(speed > 8)
			speed = 8;
		Anim_y -= speed;
		if(Anim_y <= Y)
			Anim_y = Y;
	}
		e=Anim_y;
	for(uint8_t i=0;i<8;i++)//通过for循环来打印指针数组的字符串
	{
		if(e>-16&&e<64)//有效显示范围
		Display_char(e,4,p[i]);
		e+=16;
	}
	Select_icon(0,0,a[f],16,c);//让宽度存储在数组里通过变量来调用
	OLED_video_memory_();//oled缓存
}





