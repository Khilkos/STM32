#include "SSD1963.h"

void SSD1963_init (void)
{
//LCD_init
LCD_CMD = 0xE2; 	//PLL multiplier, set PLL clock to 120M
LCD_DATA = 29;	//M = 29 - множитель
LCD_DATA = 2;	//N = 2 - делитель
LCD_DATA = 0x04;

LCD_CMD = 0xE0;	// PLL enable
LCD_DATA = 0x01;
delay_ms(10);

LCD_CMD = 0xE0;
LCD_DATA = 0x03; // now, use PLL output as system clock
delay_ms(10);

LCD_CMD = 0x01; // software reset
delay_ms(20);

LCD_CMD = 0xE6; //PLL setting for PCLK, depends on resolution
LCD_DATA = 0x03;	//30MHz
LCD_DATA = 0xff;
LCD_DATA = 0xff;

LCD_CMD = 0xB0; //LCD SPECIFICATION
LCD_DATA = 0x20; //24 bit TFT panel
LCD_DATA = 0x00; //Hsync+Vsync +DE mode  TFT mode
LCD_DATA = ((HDP>>8)&0xff); //Set HDP
LCD_DATA = (HDP&0xff);
LCD_DATA = ((VDP>>8)&0xff); //Set VDP
LCD_DATA = (VDP&0xff);
LCD_DATA = 0x00; //set RGB
LCD_DATA = 0x00; //set RGB

LCD_CMD =(0xB4);	//HSYNC
LCD_DATA = ((HT>>8)&0xff);  //Set HT
LCD_DATA = (HT&0xff);
LCD_DATA = ((HPS>>8)&0xff);  //Set HPS
LCD_DATA = (HPS&0xff);
LCD_DATA = (HPW);			   //Set HPW
LCD_DATA = ((LPS>>8)&0xff);  //Set LPS
LCD_DATA = (LPS&0xff);
LCD_DATA = (0x00);

LCD_CMD =(0xB6);	//VSYNC
LCD_DATA = ((VT>>8)&0xff);   //Set VT
LCD_DATA = (VT&0xff);
LCD_DATA = ((VPS>>8)&0xff);  //Set VPS
LCD_DATA = (VPS&0xff);
LCD_DATA = (VPW);		//Set VPW
LCD_DATA = ((FPS>>8)&0xff);  //Set FPS
LCD_DATA = (FPS&0xff);


//set GPIO value
LCD_CMD = 0xBA;
LCD_DATA = 0x05;

//set GPIO conf
LCD_CMD =(0xB8);
LCD_DATA = (0x07);    //GPIO is controlled by host GPIO[3:0]=output   GPIO[0]=1  LCD ON  GPIO[0]=1  LCD OFF 
LCD_DATA = (0x01);    //GPIO0 normal

//set adress mode
LCD_CMD = 0x36;
LCD_DATA = 0x00;

//pixel data interface
LCD_CMD = 0xf0;
LCD_DATA = 0x03;

delay_ms(5);

LCD_CMD = 0x29; // dislay ON

//set the dynamic black light configuration
LCD_CMD = 0xD0;
LCD_DATA = 0x0D;

LCD_CMD =(0x36); //rotation
LCD_DATA = (0);//RGB=BGR
}
//=====================================================================
void SSD1963_SetArea(uint16_t x1, uint16_t width, uint16_t y1, uint16_t height)
{
  LCD_CMD =(0x2a);
  LCD_DATA =((x1 >> 8) & 0xff);
  LCD_DATA =(x1 & 0xff);
  LCD_DATA =(((x1+width) >> 8) & 0xff);
  LCD_DATA =((x1+width) & 0xff);

  LCD_CMD = (0x002b);
  LCD_DATA =((y1 >> 8) & 0xff);
  LCD_DATA =(y1 & 0xff);
  LCD_DATA =(((y1+height) >> 8) & 0xff);
  LCD_DATA =((y1+height) & 0xff);
	
	LCD_CMD =(0x2c);
}
//=====================================================================
void SSD1963_ClearScreen(uint16_t color)
{
 // unsigned int x,y;
  SSD1963_SetArea(0, 800-1 , 0, 480-1);
  for (uint32_t i=0; i<(800*480);i++) 
	LCD_DATA =(color);
 }
//======================================================================

void SSD1963_dot(uint16_t x, uint16_t y, uint16_t color)
{
SSD1963_SetArea (x,0,y,0);
LCD_DATA = color;	
}
//======================================================================
void SSD1963_Vertical_line(uint16_t x, uint16_t y, uint16_t height, uint16_t thickness, uint16_t color)
{
	SSD1963_SetArea(x,thickness-1,y,height-1);
for (uint32_t i=0; i<(height*thickness); i++)
	{
		LCD_DATA =(color);	
	}

}
//=======================================================================
void SSD1963_Horisontal_line(uint16_t x, uint16_t y, uint16_t width, uint16_t thickness, uint16_t color)
{
	SSD1963_SetArea(x,width-1,y,thickness-1);
for (uint32_t i=0; i<(width*thickness); i++)
	{
		LCD_DATA =(color);
	}

}
//=======================================================================
void SSD1963_string_font_10x16 (uint16_t x_start, uint16_t y_start, uint8_t *str, uint16_t color )
{	while (*str!='\0')
	{	uint8_t    let=*str;
		for (uint8_t x=0; x<10; x++)
			{
					uint16_t	temp=font_10x16[let*10+x];
					for (uint8_t y=0; y<16; y++)
					{	if (temp & 0x01) SSD1963_dot(x_start+x,y_start+y,color); 
						temp>>=1;
					}
			}
		x_start+=11;
		str++;	
	}
}	
//========================================================================	
	



