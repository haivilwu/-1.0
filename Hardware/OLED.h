#ifndef __OLED_H
#define __OLED_H



void OLED_Init(void);//I2c���ų�ʼ��&OLED��ʼ��
void OLED_WriteCommand(uint8_t Command);//OLEDд����
void OLED_WriteData(uint8_t Data);//OLEDд����
void OLED_display_Address(uint8_t x_start,uint8_t x_terminate,uint8_t y_start,uint8_t y_terminate);//��ֱѰַģʽ�µ�Ѱַ
void OLED_Clear(void);//OLED����
void OLED_video_memory_(void);//OLED�Դ�
void Local_clearance(uint8_t y,uint8_t x,uint8_t Height,uint8_t width);//ҳ�ֲ����
void Display_picture(uint8_t y,uint8_t x,uint8_t Height,uint8_t width,const uint8_t *p);//��ʾͼƬ
void Display_single_number(uint8_t y,uint8_t x,uint16_t number,uint8_t type);//ָ��ҳ��ʾһ������
void Display_multiple_number(uint8_t y,uint8_t x,uint16_t number,uint8_t length,uint8_t type);//ָ��ҳ��ʾ�������
void Display_char(short y,short x,const uint8_t *char_);//��ʾ�ַ���
uint8_t GetPixel_For_Scroll(short x,short y,const uint8_t *bmp,uint8_t w);//дһ����
void SetPixel_For_Scroll(short X,short Y,short x,short y,uint8_t set_pixel);//��һ����
void number(uint8_t y,uint8_t x,uint8_t length,uint16_t number);//ָ������ʾ����
void Local_clearance_1(uint8_t y,uint8_t x,uint8_t y1,uint8_t x1,uint8_t data);//ָ�������
void Display_picture1(uint8_t y,uint8_t x,uint8_t Height,uint8_t width,const uint8_t *p,uint8_t w);//ָ������ʾͼƬ
void Draw_BMP_For_Scroll(uint8_t X,uint8_t Y,uint8_t high,uint8_t wide,const uint8_t *bmp,uint16_t num,uint16_t end_line);//ͼƬ����
void display(void);
#endif
