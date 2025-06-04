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
void TFT_Draw_string_font_10x16 (uint16_t x_start, uint16_t y_start, uint8_t *str, uint16_t color )
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
//=======================================================================
void TFT_Draw_string_font_10x16_back_fone (uint16_t x_start, uint16_t y_start, uint8_t *str, uint16_t color, uint16_t color_back_fone)
{	while (*str!='\0')
	{	uint8_t    let=*str;
		for (uint8_t x=0; x<10; x++)
			{
					uint16_t	temp=font_10x16[let*10+x];
					for (uint8_t y=0; y<16; y++)
					{	if (temp & 0x01) SSD1963_dot(x_start+x,y_start+y,color);  else SSD1963_dot(x_start+x,y_start+y,color_back_fone); 
						temp>>=1;
					}
			}
		x_start+=11;
		str++;	
	}
}	
//========================================================================
void TFT_Set_Work_Area(uint16_t x,uint16_t y,uint16_t length,uint16_t size)
{
	LCD_CMD =(0x2a);
  LCD_DATA =((x >> 8) & 0xff);
  LCD_DATA =(x & 0xff);
  LCD_DATA =(((x+length-1) >> 8) & 0xff);
  LCD_DATA =((x+length-1) & 0xff);

  LCD_CMD = (0x002b);
  LCD_DATA =((y >> 8) & 0xff);
  LCD_DATA =(y & 0xff);
  LCD_DATA =(((y+size-1) >> 8) & 0xff);
  LCD_DATA =((y+size-1) & 0xff);
	
	LCD_CMD =(0x2c);
}	
//========================================================================	
//ф-ция рисует линию заданного цвета и размера
void TFT_Draw_Line (uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2, uint16_t size,uint16_t color)
{
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	int error2 = 0;
	
	for (;;)
	{
		TFT_Draw_Fill_Rectangle(x1,y1,size,size,color);
		
		if(x1 == x2 && y1 == y2)
		break;
		
		error2 = error * 2;
		
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		
		if(error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}
//================================================================================
//ф-ция рисует горизонтальную линию, указанной длины, толщины и цвета
void TFT_Draw_HLine(uint16_t x, uint16_t y, uint16_t length, uint16_t size, uint16_t color)
{
	uint16_t i=0;
	
	TFT_Set_Work_Area(x,y,length,size);
	for(i=0; i<(length*size); i++)
	//TFT_Write_Data(color);
	LCD_DATA =(color);
}
//==================================================================================
//ф-ция рисует вертикальную линию, указанной длины, толщины и цвета
void TFT_Draw_VLine(uint16_t x, uint16_t y, uint16_t length, uint16_t size, uint16_t color)
{
	uint16_t i=0;
	
	TFT_Set_Work_Area(x,y,size,length);
	for(i=0; i<(length*size); i++)
	//TFT_Write_Data(color);
	LCD_DATA =(color);
}
//==================================================================================
//ф-ция рисует прямоугольник, указанной длины, ширины, толщины линий и цвета
void TFT_Draw_Rectangle(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t size, uint16_t color)
{
	TFT_Draw_HLine(x, y, length, size, color);
	TFT_Draw_HLine(x, y + width, length, size, color);
	TFT_Draw_VLine(x, y, width, size, color);
	TFT_Draw_VLine(x + length - size, y, width, size, color);
}
//====================================================================================
//ф-ция рисует закрашенный прямоугольник, указанной длины, ширины, цвета
void TFT_Draw_Fill_Rectangle(uint16_t x, uint16_t y, uint16_t length, uint16_t hight, uint16_t color)
{
	uint32_t i=0;
	
	TFT_Set_Work_Area(x,y,length, hight);
	for(i=0; i < length*hight; i++)
	{
		//TFT_Write_Data(color);	//передаём кодировку цвета
			LCD_DATA =(color);
	}
}
//=====================================================================================
//ф-ция рисует окружность нужного радиуса, линией задданой толщины и выбранным цветом, также возможно 
//залить окружность нужным цветом для этого установить аргумент fill равным единице, иначе ноль
void TFT_Draw_Circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t fill, uint16_t size, uint16_t color)
{
	int a_,b_,P;
	a_ = 0;
	b_ = radius;
	P = 1 - radius;
	while (a_ <= b_)
	{
		if(fill == 1)
		{
			TFT_Draw_Fill_Rectangle(x-a_,y-b_,2*a_+1,2*b_+1,color);
			TFT_Draw_Fill_Rectangle(x-b_,y-a_,2*b_+1,2*a_+1,color);
		}
		else
		{
			TFT_Draw_Fill_Rectangle(a_+x, b_+y, size, size, color);
			TFT_Draw_Fill_Rectangle(b_+x, a_+y, size, size, color);
			TFT_Draw_Fill_Rectangle(x-a_, b_+y, size, size, color);
			TFT_Draw_Fill_Rectangle(x-b_, a_+y, size, size, color);
			TFT_Draw_Fill_Rectangle(b_+x, y-a_, size, size, color);
			TFT_Draw_Fill_Rectangle(a_+x, y-b_, size, size, color);
			TFT_Draw_Fill_Rectangle(x-a_, y-b_, size, size, color);
			TFT_Draw_Fill_Rectangle(x-b_, y-a_, size, size, color);
		}
		if (P < 0 )
		{
			P = (P + 3) + (2* a_);
			a_ ++;
		}
		else
		{
			P = (P + 5) + (2* (a_ - b_));
			a_ ++;
			b_ --;
		}
	}
}
//==========================================================================
//вспомогательная ф-ция для закругления краёв прямоугольника
void TFT_Draw_Circle_Helper( int16_t x0, int16_t y0, int16_t r, uint16_t cornername, uint16_t size, uint16_t color)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      TFT_Draw_Fill_Rectangle(x0 + x, y0 + y, size, size, color);
      TFT_Draw_Fill_Rectangle(x0 + y, y0 + x, size, size, color);
    }
    if (cornername & 0x2) {
      TFT_Draw_Fill_Rectangle(x0 + x, y0 - y, size, size, color);
      TFT_Draw_Fill_Rectangle(x0 + y, y0 - x, size, size, color);
    }
    if (cornername & 0x8) {
      TFT_Draw_Fill_Rectangle(x0 - y, y0 + x, size, size, color);
      TFT_Draw_Fill_Rectangle(x0 - x, y0 + y, size, size, color);
    }
    if (cornername & 0x1) {
      TFT_Draw_Fill_Rectangle(x0 - y, y0 - x, size, size, color);
      TFT_Draw_Fill_Rectangle(x0 - x, y0 - y, size, size, color);
    }
  }
}
//====================================================================
//ф-ция рисует прямоугольник заданной длины, ширины, радиусом закругления краёв, толщины линий и выбранным цветом
void TFT_Draw_Round_Rect(uint16_t x, uint16_t y, uint16_t length, uint16_t hight, uint16_t r, uint16_t size, uint16_t color)
{

  TFT_Draw_HLine(x+r  , y    , length-2*r, size, color); // Top
  TFT_Draw_HLine(x+r  , y+hight-1, length-2*r, size, color); // Bottom
  TFT_Draw_VLine(x    , y+r  , hight-2*r, size, color); // Left
  TFT_Draw_VLine(x+length-1, y+r  , hight-2*r, size, color); // Right

  TFT_Draw_Circle_Helper(x+r    , y+r    , r, 		 			1, size, color);
  TFT_Draw_Circle_Helper(x+length-r-1, y+r    , r, 			2, size, color);
  TFT_Draw_Circle_Helper(x+length-r-1, y+hight-r-1, r,  4, size, color);
  TFT_Draw_Circle_Helper(x+r    , y+hight-r-1, r, 			8, size, color);
}
//========================================================================
//вспомогательная ф-ция для закругления краёв закрашенного прямоугольника
void TFT_Draw_Fill_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) 
{

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      TFT_Draw_VLine(x0+x, y0-y, 2*y+1+delta, 1, color);
      TFT_Draw_VLine(x0+y, y0-x, 2*x+1+delta, 1, color);
    }
    if (cornername & 0x2) {
     TFT_Draw_VLine(x0-x, y0-y, 2*y+1+delta, 1, color);
     TFT_Draw_VLine(x0-y, y0-x, 2*x+1+delta, 1, color);
    }
  }
}
//===============================================================================
//ф-ция рисует закрашенный прямоугольник заданной длины, ширины, радиусом закругления краев и выбранным цветом
void TFT_Draw_Fill_Round_Rect(uint16_t x, uint16_t y, uint16_t length, uint16_t hight, uint16_t r, uint16_t color)
{
  TFT_Draw_Fill_Rectangle(x+r, y, length-2*r, hight, color);

  TFT_Draw_Fill_Circle_Helper(x+length-r-1, y+r, r, 1, hight-2*r-1, color);
  TFT_Draw_Fill_Circle_Helper(x+r    , y+r, r, 2, hight-2*r-1, color);
}
//===============================================================================
//ф-ция рисует треугольник по точкам с указанной толщиной линий и выбранным цветом
void TFT_Draw_Triangle( uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint16_t color)
{
	
	TFT_Draw_Line( x1, y1, x2, y2, color, size);
	TFT_Draw_Line( x2, y2, x3, y3, color, size);
	TFT_Draw_Line( x3, y3, x1, y1, color, size);
}
//=================================================================================
//ф-ция рисует символ нужного размера, цвета, на выбранном фоне, из указанной таблицы(это на случай если хочется использовать разные шрифты, но только размером 8х8)
void TFT_Draw_Char(uint16_t x, uint16_t y, uint16_t color, uint16_t phone,const uint8_t *table, uint8_t ascii, uint8_t size)
{
	uint8_t i,f = 0;
	
	
	for (i = 0; i < 8; i++)
	{
		for(f = 0; f < 8; f++)
		{
			if((*(table + 8*(ascii-0x20)+i)>>(7-f))&0x01)
			{
				 TFT_Draw_Fill_Rectangle(x+f*size, y+i*size, size, size, color);
			}
			else
			{	
				 TFT_Draw_Fill_Rectangle(x+f*size, y+i*size, size, size, phone);
			}
		}
	}
}
//===============================================================================
void TFT_Draw_image(uint16_t x, uint16_t y, uint16_t length, uint16_t hight, uint16_t *img)
{
uint32_t i=0;
	
	TFT_Set_Work_Area(x,y,length,hight);
	for(i=0; i<(length*hight); i++)
	LCD_DATA =*(img+i);
}