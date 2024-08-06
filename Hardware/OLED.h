#ifndef __OLED_H
#define __OLED_H



void OLED_Init(void);//I2c引脚初始化&OLED初始化
void OLED_WriteCommand(uint8_t Command);//OLED写命令
void OLED_WriteData(uint8_t Data);//OLED写数据
void OLED_display_Address(uint8_t x_start,uint8_t x_terminate,uint8_t y_start,uint8_t y_terminate);//垂直寻址模式下的寻址
void OLED_Clear(void);//OLED清屏
void OLED_video_memory_(void);//OLED显存
void Local_clearance(uint8_t y,uint8_t x,uint8_t Height,uint8_t width);//页局部清除
void Display_picture(uint8_t y,uint8_t x,uint8_t Height,uint8_t width,const uint8_t *p);//显示图片
void Display_single_number(uint8_t y,uint8_t x,uint16_t number,uint8_t type);//指定页显示一个数字
void Display_multiple_number(uint8_t y,uint8_t x,uint16_t number,uint8_t length,uint8_t type);//指定页显示多个数字
void Display_char(short y,short x,const uint8_t *char_);//显示字符串
uint8_t GetPixel_For_Scroll(short x,short y,const uint8_t *bmp,uint8_t w);//写一个点
void SetPixel_For_Scroll(short X,short Y,short x,short y,uint8_t set_pixel);//读一个点
void number(uint8_t y,uint8_t x,uint8_t length,uint16_t number);//指定点显示数字
void Local_clearance_1(uint8_t y,uint8_t x,uint8_t y1,uint8_t x1,uint8_t data);//指定点填充
void Display_picture1(uint8_t y,uint8_t x,uint8_t Height,uint8_t width,const uint8_t *p,uint8_t w);//指定点显示图片
void Draw_BMP_For_Scroll(uint8_t X,uint8_t Y,uint8_t high,uint8_t wide,const uint8_t *bmp,uint16_t num,uint16_t end_line);//图片滚动
void display(void);
#endif
