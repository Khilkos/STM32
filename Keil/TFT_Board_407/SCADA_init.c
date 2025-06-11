#include "SCADA_init.h"

void SCADA_init(void)
{
uint8_t num=0;
// 	0x9cd3 - серый цвет, фон кнопок
//  0x5aeb - темно серый, для кнопок	
//	0x1e63 - зеленый цвет
//	0xe8c3 - красный цвет
//	0xfde1 - желтый цвет
//	0x9841 - темно красный
//	0x7041 - сильно темно красный	
//	0x0bc3 - темно зеленый
//  0x0240 - сильно темно зеленый
//	0x00ff - синий, фон рабочего стола
//	0xC480 - темно желтый

//Status_LED 0
//	
num=0;
Status_LED_init[num].Status_LED_X0=480;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------	
//Status_LED 1
//	
num=1;
Status_LED_init[num].Status_LED_X0=510;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 2
//	
num=2;
Status_LED_init[num].Status_LED_X0=540;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 3
//	
num=3;
Status_LED_init[num].Status_LED_X0=570;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 4
//	
num=4;
Status_LED_init[num].Status_LED_X0=600;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 5
//	
num=5;
Status_LED_init[num].Status_LED_X0=630;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 6
//	
num=6;
Status_LED_init[num].Status_LED_X0=660;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 7
//	
num=7;
Status_LED_init[num].Status_LED_X0=690;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
	


//******************************************************************
	
//button 0	-------------------------------------------------- 
//кнопка включания РЕЛЕ1	
num=0;
Button_init[num].button_X0=300; //координата X верхнего левого угла кнопки
Button_init[num].button_Y0=100;	//координата Y верхнего левого угла кнопки
Button_init[num].button_rect=1;	//радиус закругления углов кнопки
Button_init[num].button_lenght=100;	//длина кнопки
Button_init[num].button_height=40;	//высота кнопки
Button_init[num].button_frame_size=2;	//толщина рамки вокруг кнопки
Button_init[num].button_frame_light_color=0xc5f8;	//цвет светлой (верхней) стороны рамки
Button_init[num].button_frame_dark_color=0x1062;	//увет темной (нижней)стороны рамки

Button_init[num].button_color_State[0]=0x9cd3;	//цвет кнопки, состояние 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],"РЕЛЕ 1"); //текст внутри нопки, строка 1, при состоянии 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// цвет текста строка 1, при состоянии 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//смещение X отностительно кнопки текста, строка 2, при состоянии 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"ВЫКЛ");	//текст внутри нопки, строка 2, при состоянии 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// цвет текста строка 2, при состоянии 0
	
Button_init[num].button_color_State[1]=0x1e63;	//цвет кнопки, состояние 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],"РЕЛЕ 1"); //текст внутри нопки, строка 1, при состоянии 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// цвет текста строка 1, при состоянии 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//смещение X отностительно кнопки текста, строка 2, при состоянии 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"ВКЛ");	//текст внутри нопки, строка 2, при состоянии 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// цвет текста строка 2, при состоянии 1


//button1	---------------------------------------------------------
//кнопка включания РЕЛЕ2	
num=1;
Button_init[num].button_X0=420;
Button_init[num].button_Y0=100;
Button_init[num].button_rect=1;
Button_init[num].button_lenght=100;
Button_init[num].button_height=40;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//цвет кнопки, состояние 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],"РЕЛЕ 2"); //текст внутри нопки, строка 1, при состоянии 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// цвет текста строка 1, при состоянии 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//смещение X отностительно кнопки текста, строка 2, при состоянии 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"ВЫКЛ");	//текст внутри нопки, строка 2, при состоянии 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// цвет текста строка 2, при состоянии 0
	
Button_init[num].button_color_State[1]=0x1e63;	//цвет кнопки, состояние 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],"РЕЛЕ 2"); //текст внутри нопки, строка 1, при состоянии 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// цвет текста строка 1, при состоянии 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//смещение X отностительно кнопки текста, строка 2, при состоянии 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"ВКЛ");	//текст внутри нопки, строка 2, при состоянии 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// цвет текста строка 2, при состоянии 1

//button2	---------------------------------------------------------
//кнопка включания РЕЛЕ3	
num=2;
Button_init[num].button_X0=540;
Button_init[num].button_Y0=100;
Button_init[num].button_rect=1;
Button_init[num].button_lenght=100;
Button_init[num].button_height=40;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//цвет кнопки, состояние 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],"РЕЛЕ 3"); //текст внутри нопки, строка 1, при состоянии 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// цвет текста строка 1, при состоянии 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//смещение X отностительно кнопки текста, строка 2, при состоянии 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"ВЫКЛ");	//текст внутри нопки, строка 2, при состоянии 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// цвет текста строка 2, при состоянии 0
	
Button_init[num].button_color_State[1]=0x1e63;	//цвет кнопки, состояние 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],"РЕЛЕ 3"); //текст внутри нопки, строка 1, при состоянии 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// цвет текста строка 1, при состоянии 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//смещение X отностительно кнопки текста, строка 2, при состоянии 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"ВКЛ");	//текст внутри нопки, строка 2, при состоянии 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// цвет текста строка 2, при состоянии 1


//button3	---------------------------------------------------------
//кнопка включания РЕЛЕ4	
num=3;
Button_init[num].button_X0=660;
Button_init[num].button_Y0=100;
Button_init[num].button_rect=1;
Button_init[num].button_lenght=100;
Button_init[num].button_height=40;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//цвет кнопки, состояние 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],"РЕЛЕ 4"); //текст внутри нопки, строка 1, при состоянии 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// цвет текста строка 1, при состоянии 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//смещение X отностительно кнопки текста, строка 2, при состоянии 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"ВЫКЛ");	//текст внутри нопки, строка 2, при состоянии 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// цвет текста строка 2, при состоянии 0
	
Button_init[num].button_color_State[1]=0x1e63;	//цвет кнопки, состояние 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],"РЕЛЕ 4"); //текст внутри нопки, строка 1, при состоянии 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// цвет текста строка 1, при состоянии 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//смещение X отностительно кнопки текста, строка 2, при состоянии 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"ВКЛ");	//текст внутри нопки, строка 2, при состоянии 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// цвет текста строка 2, при состоянии 1

//button4	---------------------------------------------------------
//	
num=4;
Button_init[num].button_X0=400;
Button_init[num].button_Y0=160;
Button_init[num].button_rect=2;
Button_init[num].button_lenght=30;
Button_init[num].button_height=30;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//цвет кнопки, состояние 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],""); //текст внутри нопки, строка 1, при состоянии 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// цвет текста строка 1, при состоянии 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//смещение X отностительно кнопки текста, строка 2, при состоянии 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"");	//текст внутри нопки, строка 2, при состоянии 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// цвет текста строка 2, при состоянии 0
	
Button_init[num].button_color_State[1]=0x1e63;	//цвет кнопки, состояние 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],""); //текст внутри нопки, строка 1, при состоянии 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// цвет текста строка 1, при состоянии 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//смещение X отностительно кнопки текста, строка 2, при состоянии 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"");	//текст внутри нопки, строка 2, при состоянии 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// цвет текста строка 2, при состоянии 1

//button5	---------------------------------------------------------
//	
num=5;
Button_init[num].button_X0=500;
Button_init[num].button_Y0=160;
Button_init[num].button_rect=2;
Button_init[num].button_lenght=30;
Button_init[num].button_height=30;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//цвет кнопки, состояние 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],""); //текст внутри нопки, строка 1, при состоянии 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// цвет текста строка 1, при состоянии 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//смещение X отностительно кнопки текста, строка 2, при состоянии 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"");	//текст внутри нопки, строка 2, при состоянии 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// цвет текста строка 2, при состоянии 0
	
Button_init[num].button_color_State[1]=0x1e63;	//цвет кнопки, состояние 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //смещение X отностительно кнопки текста, строка 1, при состоянии 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//смещение Y отностительно кнопки текста, строка 1, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],""); //текст внутри нопки, строка 1, при состоянии 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// цвет текста строка 1, при состоянии 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//смещение X отностительно кнопки текста, строка 2, при состоянии 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//смещение Y отностительно кнопки текста, строка 2, при состоянии 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"");	//текст внутри нопки, строка 2, при состоянии 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// цвет текста строка 2, при состоянии 1





}