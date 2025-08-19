#ifndef _Graph_H
#define _Graph_H
#include "Config.h"
#define Valve_Vertical 1
#define Valve_Horizontal 2


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
_Bool button_press;
uint16_t button_delay;	
};
//--------------------------
struct Ctrl_Console_struct
{
uint16_t Ctrl_console_X0;
uint16_t Ctrl_console_Y0;
uint16_t Ctrl_console_rect;
uint16_t Ctrl_console_lenght;
uint16_t Ctrl_console_height;
uint16_t Ctrl_console_frame_size;
uint16_t Ctrl_console_frame_light_color;
uint16_t Ctrl_console_frame_dark_color;
uint16_t Ctrl_console_color;
uint16_t Ctrl_console_TEXT_X;
uint16_t Ctrl_console_TEXT_Y;
uint8_t Ctrl_console_TEXT[30];	
uint16_t Ctrl_console_TEXT_Color;
_Bool Ctrl_console_visible;	
_Bool Ctrl_console_update;
_Bool Ctrl_console_Alarm;
_Bool Ctrl_console_manual_mode;
_Bool Ctrl_console_output_enable;	
_Bool Ctrl_console_Start_push;
_Bool Ctrl_console_Stop_push;	
	
};
//-------------------------------
struct Status_LED_struct
{
uint16_t Status_LED_X0;
uint16_t Status_LED_Y0;
};
//-------------------------------
struct Valve_struct
{
uint16_t Valve_X0;
uint16_t Valve_Y0;	
uint8_t Valve_orientation;
_Bool Valve_Press;
_Bool Valve_update;
};
//---------------------------------
struct Numpad_struct
{
uint16_t Numpad_X0;
uint16_t Numpad_Y0;
_Bool Numpad_Active;
_Bool Numpad_New;	
_Bool Numpad_0_key_press;
_Bool Numpad_1_key_press;	
_Bool Numpad_2_key_press;	
_Bool Numpad_3_key_press;
_Bool Numpad_4_key_press;	
_Bool Numpad_5_key_press;	
_Bool Numpad_6_key_press;	
_Bool Numpad_7_key_press;	
_Bool Numpad_8_key_press;	
_Bool Numpad_9_key_press;	
_Bool Numpad_Dot_key_press;
_Bool Numpad_Back_key_press;	
_Bool Numpad_Esc_key_press;	
_Bool Numpad_Enter_key_press;
	
_Bool Numpad_0_key_update;
_Bool Numpad_1_key_update;	
_Bool Numpad_2_key_update;	
_Bool Numpad_3_key_update;
_Bool Numpad_4_key_update;	
_Bool Numpad_5_key_update;	
_Bool Numpad_6_key_update;	
_Bool Numpad_7_key_update;	
_Bool Numpad_8_key_update;	
_Bool Numpad_9_key_update;	
_Bool Numpad_Dot_key_update;
_Bool Numpad_Back_key_update;	
_Bool Numpad_Esc_key_update;	
_Bool Numpad_Enter_key_update;	

uint16_t Numpad_0_key_delay;
uint16_t Numpad_1_key_delay;	
uint16_t Numpad_2_key_delay;	
uint16_t Numpad_3_key_delay;
uint16_t Numpad_4_key_delay;	
uint16_t Numpad_5_key_delay;	
uint16_t Numpad_6_key_delay;	
uint16_t Numpad_7_key_delay;	
uint16_t Numpad_8_key_delay;	
uint16_t Numpad_9_key_delay;	
uint16_t Numpad_Dot_key_delay;
uint16_t Numpad_Back_key_delay;	
uint16_t Numpad_Esc_key_delay;	
uint16_t Numpad_Enter_key_delay;
	
};


extern struct Button_struct Button_init[20];
extern struct Ctrl_Console_struct Ctrl_Console_init[20];
extern struct Status_LED_struct Status_LED_init[60];
extern struct Valve_struct Valve_init[30];
extern struct Numpad_struct Numpad_init[30];

extern volatile _Bool Screen_update;


void TFT_Button_Draw (uint8_t number, uint8_t State);
void TFT_Scan_press_Button (uint16_t number);
void TFT_Scan_press_Button_with_delay (uint16_t number, uint16_t delay);
void TFT_Ctrl_Console_Draw (uint16_t number);
void TFT_Scan_press_Ctrl_Console (uint16_t number);
void TFT_Status_LED (uint16_t number, uint16_t state);
void TFT_Valve_Draw (uint16_t number, uint16_t state);
void TFT_Scan_press_Valve (uint16_t number);
void TFT_Numpad (uint16_t number);
void TFT_Scan_Numpad (uint16_t number);



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


