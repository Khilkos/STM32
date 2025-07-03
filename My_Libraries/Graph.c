#include "Graph.h"

struct Button_struct Button_init[20];
struct Ctrl_Console_struct Ctrl_Console_init[20];
struct Status_LED_struct Status_LED_init[60];
struct Valve_struct Valve_init[30];

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
			if (Ctrl_Console_init[num].Ctrl_console_Start_push) TFT_Draw_VLine (X0+18,Y0+3,10,9,0x0240); else TFT_Draw_VLine (X0+18,Y0+3,10,9,0x0bc3);
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
if (Ctrl_Console_init[num].Ctrl_console_manual_mode) {if (Ctrl_Console_init[num].Ctrl_console_Stop_push) color = 0x4820; else color=0x9841;} else color=0x5aeb;	//цвет кнопки

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
			if (Ctrl_Console_init[num].Ctrl_console_Stop_push) TFT_Draw_VLine (X0+18,Y0+3,10,9,0x4820); else TFT_Draw_VLine (X0+18,Y0+3,10,9,0x9841);
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
				{Ctrl_Console_init[num].Ctrl_console_output_enable = 0; Ctrl_Console_init[num].Ctrl_console_update=1; Ctrl_Console_init[num].Ctrl_console_Stop_push =1;}	
					else Ctrl_Console_init[num].Ctrl_console_Stop_push =0;
		if (Push_trip && !Ctrl_Console_init[num].Ctrl_console_Start_push)	 Ctrl_Console_init[num].Ctrl_console_update=1;	
		Push_trip = Ctrl_Console_init[num].Ctrl_console_Start_push | Ctrl_Console_init[num].Ctrl_console_Stop_push;
	}

}
//===================================================================
void TFT_Status_LED (uint16_t number, uint16_t state)
{
uint16_t X0=Status_LED_init[number].Status_LED_X0;
uint16_t Y0=Status_LED_init[number].Status_LED_Y0;
uint16_t rect=4;
uint16_t lenght=20;
uint16_t height=20;
uint16_t frame_size=2;
uint16_t light_color=0xc5f8;
uint16_t dark_color=0x1062;	
uint16_t color=0x9cd3;	

switch (state)
{
	case 0:
		color =0x9cd3; //светло серый, цвет кнопок
		break;
	case 1:
		color =0x5aeb; // - темно серый, для кнопок	
		break;
	case 2:
		color =0x1e63; //зеленый цвет
		break;
	case 3:
		color =0x0bc3;	//темно зеленый
		break;
	case 4:
		color =0x0240;	//сильно темно зеленый
		break;
	case 5:
		color =0xe8c3;	//красный цвет
		break;
	case 6:
		color =0x9841;	//темно красный
		break;
	case 7:
		color =0x7041;	//сильно темно красный	
		break;
	case 8:
		color =0xfde1;	//желтый цвет
		break;
	case 9:
		color =0xC480;	//темно желтый
		break;
	case 10:
		color =0x00ff;	//синий, фон рабочего стола
		break;

	default:
		color=0x0000; 
}	
	
TFT_Draw_Circle_Helper(X0+rect,Y0+rect,rect,1,frame_size,light_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+rect,rect,2,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+rect,Y0+height-rect-frame_size,rect,8,frame_size,dark_color);
TFT_Draw_Circle_Helper(X0+lenght-rect-frame_size,Y0+height-rect-frame_size,rect,4,frame_size,dark_color);
TFT_Draw_HLine(X0+rect,Y0,lenght-2*rect,frame_size,light_color);
TFT_Draw_HLine(X0+rect,Y0+height-frame_size,lenght-2*rect,frame_size,dark_color);
TFT_Draw_VLine(X0,Y0+rect,height-2*rect,frame_size,light_color);
TFT_Draw_VLine(X0+lenght-frame_size,Y0+rect,height-2*rect,frame_size,dark_color);
TFT_Draw_Fill_Round_Rect(X0+frame_size,Y0+frame_size,lenght-frame_size*2,height-frame_size*2,rect,color);	
}
//============================================================================

void TFT_Valve_H (uint16_t number, uint16_t state)
{
uint16_t X, Y, lenght, hight, light_color, dark_color, color, x1, x2, y1, y2=0;
X=Valve_init[number].Valve_X0;
Y=Valve_init[number].Valve_Y0;	
	
switch (state)
{
	case 0:
		color =0x9cd3; //светло серый, цвет кнопок
		break;
	case 1:
		color =0x5aeb; // - темно серый, для кнопок	
		break;
	case 2:
		color =0x1e63; //зеленый цвет
		break;
	case 3:
		color =0x0bc3;	//темно зеленый
		break;
	case 4:
		color =0x0240;	//сильно темно зеленый
		break;
	case 5:
		color =0xe8c3;	//красный цвет
		break;
	case 6:
		color =0x9841;	//темно красный
		break;
	case 7:
		color =0x7041;	//сильно темно красный	
		break;
	case 8:
		color =0xfde1;	//желтый цвет
		break;
	case 9:
		color =0xC480;	//темно желтый
		break;
	case 10:
		color =0x00ff;	//синий, фон рабочего стола
		break;

	default:
		color=0x0000; 
}		

lenght=50;
hight=25;		
light_color=0xc5f8;
dark_color=0x1062;

TFT_Draw_VLine (X,Y,hight,2,light_color);
TFT_Draw_VLine (X+lenght,Y+2,hight,2,dark_color);		
TFT_Draw_Line(X+2,Y,X+lenght,Y+hight,2,dark_color);
TFT_Draw_Line(X,Y+hight,X+lenght/2,Y+hight/2,2,dark_color);
TFT_Draw_Line (X+lenght/2+2,Y+hight/2,X+lenght,Y,2,light_color);

TFT_Draw_VLine(X+lenght/2,Y+2,hight/2-2,2,dark_color);
TFT_Draw_HLine(X+lenght/2-hight/4+1,Y-hight/2,hight/2-2,2,light_color);
TFT_Draw_VLine(X+lenght/2-hight/4+1,Y-hight/2+2,hight/2-2,2,light_color);
TFT_Draw_HLine(X+lenght/2-hight/4+1,Y,hight/2,2,dark_color);
TFT_Draw_VLine(X+lenght/2+hight/4+1-2,Y-hight/2,hight/2,2,dark_color);

TFT_Draw_Fill_Rectangle(X+lenght/2-hight/4+1+2,Y-hight/2+2,hight/2-4,hight/2-2,color);
//-------------------------------------------------------------------
x1=X+2;
y1=Y+2;
x2=X+lenght/2-4;
y2=Y+hight/2;

int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int error = deltaX - deltaY;
	int error2 = 0;
	uint16_t i =0;
	
	for (;;)
	{
		TFT_Draw_HLine (X+2,Y+2+i,x1-X,2,color);

		if(x1 == x2 && y1 == y2)
		break;
		
		error2 = error * 2;
		
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1++;
		}
		
		if(error2 < deltaX)
		{
			error += deltaX;
			y1++;
				i++;
		}
	}
//---------------------------------------------
	x1=X+2;
y1=Y+hight-2;
x2=X+lenght/2-4;
y2=Y+hight/2+2;


deltaX = abs(x2 - x1);
deltaY = abs(y2 - y1);
error = deltaX - deltaY;
error2 = 0;
i =0;
	for (;;)
	{
		TFT_Draw_HLine (X+2,Y+hight-4-i,x1-X,2,color);

		if(x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1++;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			y1--;
				i++;
		}
	}
//---------------------------------------------
//---------------------------------------------
	x1=X+lenght/2+6;
y1=Y+hight/2;
x2=X+lenght-2;
y2=Y+4;

	deltaX = abs(x2 - x1);
deltaY = abs(y2 - y1);
error = deltaX - deltaY;
error2 = 0;
i =0;

	for (;;)
	{
		TFT_Draw_HLine (x1,y1,X+lenght-x1,2,color);

		if(x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1++;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			y1--;
				i++;
		}
	}
	
//---------------------------------------------
	//---------------------------------------------
	x1=X+lenght/2+6;
y1=Y+hight/2;
x2=X+lenght-2;
y2=Y+hight-4;

deltaX = abs(x2 - x1);
deltaY = abs(y2 - y1);
error = deltaX - deltaY;
error2 = 0;
i =0;
	
	for (;;)
	{
		TFT_Draw_HLine (x1,y1,X+lenght-x1,2,color);
	
		if(x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1++;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			y1++;
				i++;
		}
	}
//---------------------------------------------

}

//==============================================================
void TFT_Valve_V (uint16_t number, uint16_t state)
{
uint16_t X, Y, lenght, hight, light_color, dark_color, color, x1, x2, y1, y2=0;
X=Valve_init[number].Valve_X0;
Y=Valve_init[number].Valve_Y0;	
	
switch (state)
{
	case 0:
		color =0x9cd3; //светло серый, цвет кнопок
		break;
	case 1:
		color =0x5aeb; // - темно серый, для кнопок	
		break;
	case 2:
		color =0x1e63; //зеленый цвет
		break;
	case 3:
		color =0x0bc3;	//темно зеленый
		break;
	case 4:
		color =0x0240;	//сильно темно зеленый
		break;
	case 5:
		color =0xe8c3;	//красный цвет
		break;
	case 6:
		color =0x9841;	//темно красный
		break;
	case 7:
		color =0x7041;	//сильно темно красный	
		break;
	case 8:
		color =0xfde1;	//желтый цвет
		break;
	case 9:
		color =0xC480;	//темно желтый
		break;
	case 10:
		color =0x00ff;	//синий, фон рабочего стола
		break;

	default:
		color=0x0000; 
}		

lenght=25;
hight=50;		
light_color=0xc5f8;
dark_color=0x1062;

TFT_Draw_HLine (X,Y,lenght,2,dark_color);
TFT_Draw_Line(X,Y+2,X+lenght/2,Y+hight/2,2,dark_color);
TFT_Draw_Line(X+lenght/2,Y+hight/2,X+lenght-2,Y+2,2,dark_color);

TFT_Draw_HLine (X,Y+hight,lenght,2,dark_color);		
TFT_Draw_Line(X,Y+hight-2,X+lenght/2,Y+hight/2,2,dark_color);
TFT_Draw_Line(X+lenght/2,Y+hight/2,X+lenght-2,Y+hight-2,2,dark_color);

TFT_Draw_HLine(X+lenght/2,Y+hight/2,lenght/2-2,2,dark_color);
TFT_Draw_HLine(X+lenght,Y+hight/2-lenght/4,lenght/2-2,2,light_color);
TFT_Draw_VLine(X+lenght-2,Y+hight/2-lenght/4,lenght/2,2,light_color);
TFT_Draw_HLine(X+lenght-2,Y+hight/2+lenght/4,lenght/2,2,dark_color);
TFT_Draw_VLine(X+lenght+lenght/2-2,Y+hight/2-lenght/4,lenght/2+2,2,dark_color);

TFT_Draw_Fill_Rectangle(X+lenght,Y+hight/2-lenght/4+2,lenght/2-2,lenght/2-2,color);



//---------------------------------------------
x1=X+2+1;
y1=Y+2;
x2=X+lenght/2+1;
y2=Y+hight/2-4;

int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int error = deltaX - deltaY;
	int error2 = 0;

	
	for (;;)
	{
		TFT_Draw_HLine (x1,y1,X+lenght/2-x1+1,2,color);
		//TFT_Draw_Fill_Rectangle(x1,y1,2,2,color);
		
		if(x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1++;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			y1++;
		}
	}
//---------------------------------------------

	
	//---------------------------------------------
x1=X+lenght/2-1;
y1=Y+hight/2-4;
x2=X+lenght-4-1;
y2=Y+2;

deltaX = abs(x2 - x1);
deltaY = abs(y2 - y1);
error = deltaX - deltaY;
error2 = 0;
	
	for (;;)
	{
		TFT_Draw_HLine (X+lenght/2,y1,x1-X-lenght/2+2,2,color);
		//TFT_Draw_Fill_Rectangle(x1,y1,2,2,color);
		
		if(x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1++;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			y1--;
			//	i++;
		}
	}
//---------------------------------------------

	
	//---------------------------------------------
x1=X+2+1;
y1=Y+hight-2;
x2=X+lenght/2+1;
y2=Y+hight/2+4;

deltaX = abs(x2 - x1);
deltaY = abs(y2 - y1);
error = deltaX - deltaY;
error2 = 0;
	
	for (;;)
	{
		TFT_Draw_HLine (x1,y1,X+lenght/2-x1+1,2,color);
		//TFT_Draw_Fill_Rectangle(x1,y1,2,2,color);
		
		if(x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1++;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			y1--;
			//	i++;
		}
	}
	
//---------------------------------------------
x1=X+lenght/2-1;
y1=Y+hight/2+4;
x2=X+lenght-4-1;
y2=Y+hight-2;

deltaX = abs(x2 - x1);
deltaY = abs(y2 - y1);
error = deltaX - deltaY;
error2 = 0;
	
	for (;;)
	{
		TFT_Draw_HLine (X+lenght/2,y1,x1-X-lenght/2+2,2,color);
		//TFT_Draw_Fill_Rectangle(x1,y1,2,2,color);
		
		if(x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1++;
		}
		if(error2 < deltaX)
		{
			error += deltaX;
			y1++;
			//	i++;
		}
	}


	
}
//===============================================================



