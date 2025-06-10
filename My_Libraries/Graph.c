#include "Graph.h"

struct Button_struct Button_init[20];
struct Ctrl_Console_struct Ctrl_Console_init[20];

volatile _Bool Screen_update=0;
volatile static _Bool Push_trip=0; 

void TFT_Button_Draw (uint8_t number, uint8_t State)
{
uint16_t X0=Button_init[number].button_X0;
uint16_t Y0=Button_init[number].button_Y0;
uint16_t rect=Button_init[number].button_rect;
uint16_t lenght=Button_init[number].button_lenght;
uint16_t height=Button_init[number].button_height;
uint16_t frame_size=Button_init[number].button_frame_size;
uint16_t light_color=Button_init[number].button_frame_light_color;
uint16_t dark_color=Button_init[number].button_frame_dark_color;
uint16_t color=Button_init[number].button_color_State[State];	
	
TFT_Draw_Circle_Helper(X0+rect,Y0+rect,rect,1,frame_size,light_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+rect,rect,2,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+rect,Y0+height-rect-frame_size,rect,8,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+height-rect-frame_size,rect,4,frame_size,dark_color);
TFT_Draw_HLine(X0+rect,Y0,lenght-2*rect,frame_size,light_color);
TFT_Draw_HLine(X0+rect,Y0+height-frame_size,lenght-2*rect,frame_size,dark_color);
TFT_Draw_VLine(X0,Y0+rect,height-2*rect,frame_size,light_color);
TFT_Draw_VLine(X0+lenght-frame_size,Y0+rect,height-2*rect,frame_size,dark_color);
TFT_Draw_Fill_Round_Rect(X0+frame_size,Y0+frame_size,lenght-frame_size*2,height-frame_size*2,rect,color);

TFT_Draw_string_font_10x16(X0+Button_init[number].button_TEXT_line_1_X_State[State],Y0+Button_init[number].button_TEXT_line_1_Y_Stete[State], Button_init[number].buttuon_TEXT_line_1_State[State],Button_init[number].buttuon_TEXT_line_1_Color_State[State]);	
TFT_Draw_string_font_10x16(X0+Button_init[number].button_TEXT_line_2_X_State[State],Y0+Button_init[number].button_TEXT_line_2_Y_Stete[State], Button_init[number].buttuon_TEXT_line_2_State[State],Button_init[number].buttuon_TEXT_line_2_Color_State[State]);		
}
//--------------------------------------------------------------------------

void TFT_Scan_press_Button (uint16_t number)
{
uint16_t X=Button_init[number].button_X0;
uint16_t Y=Button_init[number].button_Y0;
uint16_t lenght=Button_init[number].button_lenght;
uint16_t height=Button_init[number].button_height;	
	
	
if ((GT911Touch[0].XCoordinate>X && GT911Touch[0].XCoordinate<(X+lenght) && GT911Touch[0].YCoordinate>Y && GT911Touch[0].YCoordinate<(Y+height)))
					{if (Button_init[number].button_State == 1) Button_init[number].button_State=0; else Button_init[number].button_State=1; Button_init[number].button_update=1;}
}
//---------------------------------------------------------------------------
void TFT_Ctrl_Console_Draw (uint16_t num)
{
uint8_t String[30];	
Ctrl_Console_init[num].Ctrl_console_update = 0;

	
uint16_t X0=Ctrl_Console_init[num].Ctrl_console_X0=400;
uint16_t Y0=Ctrl_Console_init[num].Ctrl_console_Y0=240;
uint16_t rect=Ctrl_Console_init[num].Ctrl_console_rect=4;
uint16_t lenght=Ctrl_Console_init[num].Ctrl_console_lenght=175;
uint16_t height=Ctrl_Console_init[num].Ctrl_console_height=115;
uint16_t frame_size=Ctrl_Console_init[num].Ctrl_console_frame_size=4;
uint16_t light_color=Ctrl_Console_init[num].Ctrl_console_frame_light_color=0xc5f8;
uint16_t dark_color=Ctrl_Console_init[num].Ctrl_console_frame_dark_color=0x1062;	
uint16_t color=Ctrl_Console_init[num].Ctrl_console_color	=0x9cd3;	//цвет консоли, состояние 0


Ctrl_Console_init[num].Ctrl_console_TEXT_X=8; //смещение текста по X отностительно консоли 
Ctrl_Console_init[num].Ctrl_console_TEXT_Y=5;	//смещение текста по Y отностительно консоли
sprintf(Ctrl_Console_init[num].Ctrl_console_TEXT,"Console"); //текст заголовок консоли
Ctrl_Console_init[num].Ctrl_console_TEXT_Color=0x0000;	// цвет текста 
	
	
	
TFT_Draw_Circle_Helper(X0+rect,Y0+rect,rect,1,frame_size,light_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+rect,rect,2,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+rect,Y0+height-rect-frame_size,rect,8,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+height-rect-frame_size,rect,4,frame_size,dark_color);
TFT_Draw_HLine(X0+rect,Y0,lenght-2*rect,frame_size,light_color);
TFT_Draw_HLine(X0+rect,Y0+height-frame_size,lenght-2*rect,frame_size,dark_color);
TFT_Draw_VLine(X0,Y0+rect,height-2*rect,frame_size,light_color);
TFT_Draw_VLine(X0+lenght-frame_size,Y0+rect,height-2*rect,frame_size,dark_color);
TFT_Draw_Fill_Round_Rect(X0+frame_size,Y0+frame_size,lenght-frame_size*2,height-frame_size*2,rect,color);

TFT_Draw_string_font_10x16(X0+Ctrl_Console_init[num].Ctrl_console_TEXT_X,Y0+Ctrl_Console_init[num].Ctrl_console_TEXT_Y, Ctrl_Console_init[num].Ctrl_console_TEXT,Ctrl_Console_init[num].Ctrl_console_TEXT_Color);	

//кнопка закрытия консоли
X0=Ctrl_Console_init[num].Ctrl_console_X0+145;
Y0=Ctrl_Console_init[num].Ctrl_console_Y0+2;
rect=2;
lenght=25;
height=25;
frame_size=2;
light_color=0xc5f8;
dark_color=0x1062;	
color=0xe8c3;	//цвет консоли, состояние 0

TFT_Draw_Circle_Helper(X0+rect,Y0+rect,rect,1,frame_size,light_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+rect,rect,2,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+rect,Y0+height-rect-frame_size,rect,8,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+height-rect-frame_size,rect,4,frame_size,dark_color);
TFT_Draw_HLine(X0+rect,Y0,lenght-2*rect,frame_size,light_color);
TFT_Draw_HLine(X0+rect,Y0+height-frame_size,lenght-2*rect,frame_size,dark_color);
TFT_Draw_VLine(X0,Y0+rect,height-2*rect,frame_size,light_color);
TFT_Draw_VLine(X0+lenght-frame_size,Y0+rect,height-2*rect,frame_size,dark_color);
TFT_Draw_Fill_Round_Rect(X0+frame_size,Y0+frame_size,lenght-frame_size*2,height-frame_size*2,rect,color);

TFT_Draw_Line(X0+5,Y0+5,X0+18,Y0+18,2,0xc5f8);
TFT_Draw_Line(X0+5,Y0+18,X0+18,Y0+5,2,0xc5f8);

//разделительная линия
TFT_Draw_HLine(Ctrl_Console_init[num].Ctrl_console_X0+5,Ctrl_Console_init[num].Ctrl_console_Y0+30,Ctrl_Console_init[num].Ctrl_console_lenght-10,4,0xc5f8);

//кнопка автомат/ручной
X0=Ctrl_Console_init[num].Ctrl_console_X0+10;
Y0=Ctrl_Console_init[num].Ctrl_console_Y0+55;
rect=10;
lenght=45;
height=45;
frame_size=2;
light_color=0xc5f8;
dark_color=0x1062;	
if (Ctrl_Console_init[num].Ctrl_console_manual_mode) color=0xC480; else color=0x5aeb;	//цвет кнопки

TFT_Draw_Circle_Helper(X0+rect,Y0+rect,rect,1,frame_size,light_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+rect,rect,2,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+rect,Y0+height-rect-frame_size,rect,8,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+height-rect-frame_size,rect,4,frame_size,dark_color);
TFT_Draw_HLine(X0+rect,Y0,lenght-2*rect,frame_size,light_color);
TFT_Draw_HLine(X0+rect,Y0+height-frame_size,lenght-2*rect,frame_size,dark_color);
TFT_Draw_VLine(X0,Y0+rect,height-2*rect,frame_size,light_color);
TFT_Draw_VLine(X0+lenght-frame_size,Y0+rect,height-2*rect,frame_size,dark_color);
TFT_Draw_Fill_Round_Rect(X0+frame_size,Y0+frame_size,lenght-frame_size*2,height-frame_size*2,rect,color);

sprintf(String,"Реж.");
TFT_Draw_string_font_10x16(Ctrl_Console_init[num].Ctrl_console_X0+14,Ctrl_Console_init[num].Ctrl_console_Y0+37, String,Ctrl_Console_init[num].Ctrl_console_TEXT_Color);

if (Ctrl_Console_init[num].Ctrl_console_manual_mode) 
		{	sprintf(String,"руч");
			TFT_Draw_string_font_10x16(Ctrl_Console_init[num].Ctrl_console_X0+16,Ctrl_Console_init[num].Ctrl_console_Y0+70, String,Ctrl_Console_init[num].Ctrl_console_TEXT_Color);
		}
	else
		{	sprintf(String,"авт");
			TFT_Draw_string_font_10x16(Ctrl_Console_init[num].Ctrl_console_X0+16,Ctrl_Console_init[num].Ctrl_console_Y0+70, String,Ctrl_Console_init[num].Ctrl_console_TEXT_Color);
		}

//кнопка Пуск
X0=Ctrl_Console_init[num].Ctrl_console_X0+10+55*1;
Y0=Ctrl_Console_init[num].Ctrl_console_Y0+55;
rect=10;
lenght=45;
height=45;
frame_size=2;
light_color=0xc5f8;
dark_color=0x1062;	
if (Ctrl_Console_init[num].Ctrl_console_manual_mode) {if (Ctrl_Console_init[num].Ctrl_console_Start_push) color = 0x0240; else color=0x0bc3;} else color=0x5aeb;	//цвет кнопки

TFT_Draw_Circle_Helper(X0+rect,Y0+rect,rect,1,frame_size,light_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+rect,rect,2,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+rect,Y0+height-rect-frame_size,rect,8,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+height-rect-frame_size,rect,4,frame_size,dark_color);
TFT_Draw_HLine(X0+rect,Y0,lenght-2*rect,frame_size,light_color);
TFT_Draw_HLine(X0+rect,Y0+height-frame_size,lenght-2*rect,frame_size,dark_color);
TFT_Draw_VLine(X0,Y0+rect,height-2*rect,frame_size,light_color);
TFT_Draw_VLine(X0+lenght-frame_size,Y0+rect,height-2*rect,frame_size,dark_color);
TFT_Draw_Fill_Round_Rect(X0+frame_size,Y0+frame_size,lenght-frame_size*2,height-frame_size*2,rect,color);

sprintf(String,"Пуск");
TFT_Draw_string_font_10x16(Ctrl_Console_init[num].Ctrl_console_X0+14+55*1,Ctrl_Console_init[num].Ctrl_console_Y0+37, String,Ctrl_Console_init[num].Ctrl_console_TEXT_Color);

if (Ctrl_Console_init[num].Ctrl_console_manual_mode) //пиктограмма внутри кнопки
	{		TFT_Draw_Circle(X0+21,Y0+21,14,0,3,0xc5f8); 
			TFT_Draw_VLine (X0+18,Y0+3,10,9,0x0bc3);
			TFT_Draw_VLine (X0+21,Y0+4,15,3,0xc5f8);
	}

//кнопка Стоп
X0=Ctrl_Console_init[num].Ctrl_console_X0+10+55*2;
Y0=Ctrl_Console_init[num].Ctrl_console_Y0+55;
rect=10;
lenght=45;
height=45;
frame_size=2;
light_color=0xc5f8;
dark_color=0x1062;	
if (Ctrl_Console_init[num].Ctrl_console_manual_mode) color=0x9841; else color=0x5aeb;	//цвет кнопки

TFT_Draw_Circle_Helper(X0+rect,Y0+rect,rect,1,frame_size,light_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+rect,rect,2,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+rect,Y0+height-rect-frame_size,rect,8,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+height-rect-frame_size,rect,4,frame_size,dark_color);
TFT_Draw_HLine(X0+rect,Y0,lenght-2*rect,frame_size,light_color);
TFT_Draw_HLine(X0+rect,Y0+height-frame_size,lenght-2*rect,frame_size,dark_color);
TFT_Draw_VLine(X0,Y0+rect,height-2*rect,frame_size,light_color);
TFT_Draw_VLine(X0+lenght-frame_size,Y0+rect,height-2*rect,frame_size,dark_color);
TFT_Draw_Fill_Round_Rect(X0+frame_size,Y0+frame_size,lenght-frame_size*2,height-frame_size*2,rect,color);

sprintf(String,"Стоп");
TFT_Draw_string_font_10x16(Ctrl_Console_init[num].Ctrl_console_X0+14+55*2,Ctrl_Console_init[num].Ctrl_console_Y0+37, String,Ctrl_Console_init[num].Ctrl_console_TEXT_Color);

if (Ctrl_Console_init[num].Ctrl_console_manual_mode) //пиктограмма внутри кнопки
	{		TFT_Draw_Circle(X0+21,Y0+21,14,0,3,0xc5f8); 
			TFT_Draw_VLine (X0+18,Y0+3,10,9,0x9841);
			TFT_Draw_VLine (X0+21,Y0+4,15,3,0xc5f8);
	}



}
//============================================================================================

void TFT_Scan_press_Ctrl_Console (uint16_t num)
{
uint16_t X, Y, lenght, height;

//кнопка закрытия консоли
X=Ctrl_Console_init[num].Ctrl_console_X0+145;	
Y=Ctrl_Console_init[num].Ctrl_console_Y0+2;	
lenght=25;
height=25;	
if ((GT911Touch[0].XCoordinate>X && GT911Touch[0].XCoordinate<(X+lenght) && GT911Touch[0].YCoordinate>Y && GT911Touch[0].YCoordinate<(Y+height))) {Ctrl_Console_init[num].Ctrl_console_visible=0; Screen_update=1;}

//кнопка Режим работы
X=Ctrl_Console_init[num].Ctrl_console_X0+10;	
Y=Ctrl_Console_init[num].Ctrl_console_Y0+55;	
lenght=45;
height=45;	
if ((GT911Touch[0].XCoordinate>X && GT911Touch[0].XCoordinate<(X+lenght) && GT911Touch[0].YCoordinate>Y && GT911Touch[0].YCoordinate<(Y+height))) 
	{if (Ctrl_Console_init[num].Ctrl_console_manual_mode == 1) Ctrl_Console_init[num].Ctrl_console_manual_mode=0; else Ctrl_Console_init[num].Ctrl_console_manual_mode=1; Ctrl_Console_init[num].Ctrl_console_update=1;}

if (Ctrl_Console_init[num].Ctrl_console_manual_mode)	
	{	//кнопка Пуск
		X=Ctrl_Console_init[num].Ctrl_console_X0+10+55*1;
		Y=Ctrl_Console_init[num].Ctrl_console_Y0+55;	
		lenght=45;
		height=45;	
		if ((GT911Touch[0].XCoordinate>X && GT911Touch[0].XCoordinate<(X+lenght) && GT911Touch[0].YCoordinate>Y && GT911Touch[0].YCoordinate<(Y+height))) 
				{Ctrl_Console_init[num].Ctrl_console_output_enable = 1; Ctrl_Console_init[num].Ctrl_console_update=1; Ctrl_Console_init[num].Ctrl_console_Start_push = 1;}
					else Ctrl_Console_init[num].Ctrl_console_Start_push =0;
		//кнопка Стоп
		X=Ctrl_Console_init[num].Ctrl_console_X0+10+55*2;
		Y=Ctrl_Console_init[num].Ctrl_console_Y0+55;	
		lenght=45;
		height=45;	
		if ((GT911Touch[0].XCoordinate>X && GT911Touch[0].XCoordinate<(X+lenght) && GT911Touch[0].YCoordinate>Y && GT911Touch[0].YCoordinate<(Y+height))) 
				{Ctrl_Console_init[num].Ctrl_console_output_enable = 0; Ctrl_Console_init[num].Ctrl_console_update=1;}	
		
		if (Push_trip && !Ctrl_Console_init[num].Ctrl_console_Start_push)	 Ctrl_Console_init[num].Ctrl_console_update=1;	
		Push_trip = Ctrl_Console_init[num].Ctrl_console_Start_push;
				
	
	}


}

