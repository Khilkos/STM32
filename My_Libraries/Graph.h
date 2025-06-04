#ifndef _Graph_H
#define _Graph_H
#include "Config.h"


#ifdef STM32F4
//=============================================================
//

struct Button_struct
{
uint16_t button_X0;
uint16_t button_Y0;
uint16_t button_rect;
uint16_t button_lenght;
uint16_t button_height;
uint16_t button_frame_size;
uint16_t button_frame_light_color;
uint16_t button_frame_dark_color;
uint16_t button_color_State[4];
uint16_t button_TEXT_line_1_X_State[4];
uint16_t button_TEXT_line_1_Y_Stete[4];
uint8_t buttuon_TEXT_line_1_State[4][30];	
uint16_t buttuon_TEXT_line_1_Color_State[4];
uint16_t button_TEXT_line_2_X_State[4];
uint16_t button_TEXT_line_2_Y_Stete[4];
uint8_t buttuon_TEXT_line_2_State[4][30];		
uint16_t buttuon_TEXT_line_2_Color_State[4];	
uint8_t button_State;
_Bool button_update;	
};

extern struct Button_struct Button_init[20];

void TFT_Button_Draw (uint8_t number, uint8_t State);
void TFT_Scan_press_Button (uint16_t number);


//
//=============================================================
#endif



#ifdef STM32H7
//=============================================================
//
//
//=============================================================
#endif



#endif


