#include "Open407_LCD.h"


void Open407_LCD_Init (void)
{

		LCD_CMD=0xCF;
		LCD_DATA = 0x00;
		LCD_DATA = 0xC1;
		LCD_DATA = 0x30;

		LCD_CMD=0xED;
		LCD_DATA =(0x64);
		LCD_DATA =(0x03);
		LCD_DATA =(0x12);
		LCD_DATA =(0x81);

		LCD_CMD=0xE8;
		LCD_DATA =(0x85);
		LCD_DATA = (0x00);
		LCD_DATA = (0x7A);

		LCD_CMD =0xCB;
		LCD_DATA = (0x39);
		LCD_DATA = (0x2C);
		LCD_DATA = (0x00);
		LCD_DATA = (0x34);
		LCD_DATA = (0x02);

		LCD_CMD =0xF7;
		LCD_DATA = (0x20);

		LCD_CMD =0xEA;
		LCD_DATA = (0x00);
		LCD_DATA = (0x00);

		LCD_CMD =0xC0; //Power control
		LCD_DATA = (0x21); //VRH[5:0]

		LCD_CMD =0xC1; //Power control
		LCD_DATA = (0x11); //SAP[2:0];BT[3:0]

		LCD_CMD =0xC5; //VCM control
		LCD_DATA = (0x31);//20
		LCD_DATA =(0x3C);

		LCD_CMD =0xC7; //VCM control2
		LCD_DATA = (0x90);//0x88

		LCD_CMD =0x36; // Memory Access Control
		LCD_DATA = (0x08);

		LCD_CMD =0x3A; // Memory Access Control
		LCD_DATA = (0x55);

		LCD_CMD =0xB1;
		LCD_DATA = (0x00);
		LCD_DATA = (0x12);//1b

		LCD_CMD =0xB6; // Display Function Control
		LCD_DATA = (0x0A);
		LCD_DATA = (0xA2);

		LCD_CMD =0xF2; // 3Gamma Function Disable
		LCD_DATA = (0x00);

		LCD_CMD =0x26; //Gamma curve selected
		LCD_DATA = (0x01);

		LCD_CMD =0xE0; //Set Gamma
		LCD_DATA = (0x0F);
		LCD_DATA = (0x20);
		LCD_DATA = (0x1d);
		LCD_DATA = (0x0b);
		LCD_DATA = (0x10);
		LCD_DATA = (0x0a);
		LCD_DATA = (0x49);
		LCD_DATA = (0xa9);
		LCD_DATA = (0x3b);
		LCD_DATA = (0x0a);
		LCD_DATA = (0x15);
		LCD_DATA = (0x06);
		LCD_DATA = (0x0c);
		LCD_DATA = (0x06);
		LCD_DATA = (0x00);

		LCD_CMD =0xE1; //Set Gamma
		LCD_DATA = (0x00);
		LCD_DATA = (0x1f);
		LCD_DATA = (0x22);
		LCD_DATA = (0x04);
		LCD_DATA = (0x0f);
		LCD_DATA = (0x05);
		LCD_DATA = (0x36);
		LCD_DATA = (0x46);
		LCD_DATA = (0x46);
		LCD_DATA = (0x05);
		LCD_DATA = (0x0b);
		LCD_DATA = (0x09);
		LCD_DATA = (0x33);
		LCD_DATA = (0x39);
		LCD_DATA = (0x0F);

		LCD_CMD =0x11; // Sleep out
		delay_ms(120);
		LCD_CMD =0x29; // Display on
		LCD_CMD =0x2c;
		
}

void Open407_SetArea(uint16_t x1, uint16_t width, uint16_t y1, uint16_t height)
{
  LCD_CMD =(0x2b);
  LCD_DATA =((x1 >> 8) & 0xff);
  LCD_DATA =(x1 & 0xff);
  LCD_DATA =(((x1+width) >> 8) & 0xff);
  LCD_DATA =((x1+width) & 0xff);

  LCD_CMD = (0x002a);
  LCD_DATA =((y1 >> 8) & 0xff);
  LCD_DATA =(y1 & 0xff);
  LCD_DATA =(((y1+height) >> 8) & 0xff);
  LCD_DATA =((y1+height) & 0xff);
	
	LCD_CMD =(0x2c);
}


//=====================================================================
void Open407_ClearScreen(uint16_t color)
{
 // unsigned int x,y;
  Open407_SetArea(0, 320-1 , 0, 240-1);
  for (uint32_t i=0; i<(320*240);i++) 
	LCD_DATA =(color);
 }

 void Open407_dot(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_CMD =(0x2b);
  LCD_DATA =(x >> 8);
  LCD_DATA =(x & 0xff);
 
  LCD_CMD = (0x002a);
  LCD_DATA =(((240-y) >> 8));
  LCD_DATA =((240-y) & 0xff);
  
	LCD_CMD = (0x002c);
LCD_DATA = color;	
}

//=======================================================================
void TFT_Draw_string_font_10x16_back_fone (uint16_t x_start, uint16_t y_start, uint8_t *str, uint16_t color, uint16_t color_back_fone)
{	while (*str!='\0')
	{	uint8_t    let=*str;
		for (uint8_t x=0; x<10; x++)
			{
					uint16_t	temp=font_10x16[let*10+x];
					for (uint8_t y=0; y<16; y++)
					{	if (temp & 0x01) Open407_dot(x_start+x,y_start+y,color);  else Open407_dot(x_start+x,y_start+y,color_back_fone); 
						temp>>=1;
					}
			}
		x_start+=11;
		str++;	
	}
}	

//=======================================================================
void TFT_Draw_string_font_5x8_back_fone (uint16_t x_start, uint16_t y_start, uint8_t *str, uint16_t color, uint16_t color_back_fone)
{	while (*str!='\0')
	{	uint8_t    let=*str;
		for (uint8_t x=0; x<5; x++)
			{
					uint16_t	temp=FontTable[let][x];
					for (uint8_t y=0; y<8; y++)
					{	if (temp & 0x01) Open407_dot(x_start+x,y_start+y,color);  else Open407_dot(x_start+x,y_start+y,color_back_fone); 
						temp>>=1;
					}
			}
		x_start+=6;
		str++;	
	}
}	