#include "Graph.h"

struct Button_struct Button_init[20];

void TFT_Button_Draw (uint8_t number, uint8_t State)
{
uint16_t button_X0=Button_init[number].button_X0;
uint16_t button_Y0=Button_init[number].button_Y0;
uint16_t button_rect=Button_init[number].button_rect;
uint16_t button_lenght=Button_init[number].button_lenght;
uint16_t button_height=Button_init[number].button_height;
uint16_t button_frame_size=Button_init[number].button_frame_size;
uint16_t button_light_color=Button_init[number].button_frame_light_color;
uint16_t button_dark_color=Button_init[number].button_frame_dark_color;
uint16_t button_color=Button_init[number].button_color_State[State];	
	
TFT_Draw_Circle_Helper(button_X0+button_rect,button_Y0+button_rect,button_rect,1,button_frame_size,button_light_color);
TFT_Draw_Circle_Helper(button_X0+button_lenght-button_rect-button_frame_size,button_Y0+button_rect,button_rect,2,button_frame_size,button_dark_color);
TFT_Draw_Circle_Helper(button_X0+button_rect,button_Y0+button_height-button_rect-button_frame_size,button_rect,8,button_frame_size,button_dark_color);
TFT_Draw_Circle_Helper(button_X0+button_lenght-button_rect-button_frame_size,button_Y0+button_height-button_rect-button_frame_size,button_rect,4,button_frame_size,button_dark_color);
TFT_Draw_HLine(button_X0+button_rect,button_Y0,button_lenght-2*button_rect,button_frame_size,button_light_color);
TFT_Draw_HLine(button_X0+button_rect,button_Y0+button_height-button_frame_size,button_lenght-2*button_rect,button_frame_size,button_dark_color);
TFT_Draw_VLine(button_X0,button_Y0+button_rect,button_height-2*button_rect,button_frame_size,button_light_color);
TFT_Draw_VLine(button_X0+button_lenght-button_frame_size,button_Y0+button_rect,button_height-2*button_rect,button_frame_size,button_dark_color);
TFT_Draw_Fill_Round_Rect(button_X0+button_frame_size,button_Y0+button_frame_size,button_lenght-button_frame_size*2,button_height-button_frame_size*2,button_rect,button_color);

TFT_Draw_string_font_10x16(button_X0+Button_init[number].button_TEXT_line_1_X_State[State],button_Y0+Button_init[number].button_TEXT_line_1_Y_Stete[State], Button_init[number].buttuon_TEXT_line_1_State[State],Button_init[number].buttuon_TEXT_line_1_Color_State[State]);	
TFT_Draw_string_font_10x16(button_X0+Button_init[number].button_TEXT_line_2_X_State[State],button_Y0+Button_init[number].button_TEXT_line_2_Y_Stete[State], Button_init[number].buttuon_TEXT_line_2_State[State],Button_init[number].buttuon_TEXT_line_2_Color_State[State]);		
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



