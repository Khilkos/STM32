#include "main.h"
//#include "GPIO_setup.h"

#define TOUCH_Press !(GPIOE->IDR & 1<<4)
static uint16_t X0, Y0, lenght, height;
static uint32_t temp32=0;
static uint16_t temp16=0;
static uint8_t temp8=0;
static uint8_t animation_count=0;
static _Bool animation_update=0;
static uint8_t String[300];
_Bool TOUCH_IRQ=0;
static uint16_t FPS_screen[10];
static uint16_t FPS_screen_temp;
static _Bool push_trip_main=0; 
static _Bool scan_push_back_front=0;
static _Bool Output_1=0;

static uint32_t ON_value=0;
static uint32_t OFF_value=0;

static uint16_t temperature=0;

int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOHEN); // enable portA and portB clock

	Core_F4_init_HSE_full(6,168,2,7,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	Timer2_F4_init(168000000,100);
	
	
	GPIO_DO_setup(GPIOE,6,High);//LCD подсветка
	GPIO_DO_setup(GPIOE,0,High);//LCD_Reset
	GPIO_DO_setup(GPIOA,1,High);//Реле 1
	GPIO_DO_setup(GPIOA,3,High);//Реле 2
	GPIO_DO_setup(GPIOA,5,High);//Реле 3
	GPIO_DO_setup(GPIOA,7,High);//Реле 4	
	
	GPIO_DO_setup(GPIOA,0,High);//Светодиод	
	
	
	GPIO_DO_setup(TOUCH_IRQ_GPIO,TOUCH_IRQ_PIN,High);// TOUCH_IRQ
	GPIO_DO_setup(TOUCH_RST_GPIO,TOUCH_RST_PIN,High);// TOUCH_RST
	
	GPIO_Alternate(GPIOB,6,Open_drain,High,Pull_up,AF4);//I2C1_SCL
	GPIO_Alternate(GPIOB,7,Open_drain,High,Pull_up,AF4);//I2C1_SDA
	
	GPIO_Alternate(GPIOA,9,Open_drain,High,Pull_up,AF7);// USART2 TX2
	GPIO_Alternate(GPIOA,10,Open_drain,High,Pull_up,AF7);// USART2 RX2	
	
	
	GPIO_Alternate(GPIOD,14,Push_pull,High,No_pull,AF12); //FSMC D0
	GPIO_Alternate(GPIOD,15,Push_pull,High,No_pull,AF12); //FSMC D1
	GPIO_Alternate(GPIOD,0,Push_pull,High,No_pull,AF12); //FSMC D2
	GPIO_Alternate(GPIOD,1,Push_pull,High,No_pull,AF12); //FSMC D3
	GPIO_Alternate(GPIOE,7,Push_pull,High,No_pull,AF12); //FSMC D4
	GPIO_Alternate(GPIOE,8,Push_pull,High,No_pull,AF12); //FSMC D5
	GPIO_Alternate(GPIOE,9,Push_pull,High,No_pull,AF12); //FSMC D6
	GPIO_Alternate(GPIOE,10,Push_pull,High,No_pull,AF12); //FSMC D7
	GPIO_Alternate(GPIOE,11,Push_pull,High,No_pull,AF12); //FSMC D8
	GPIO_Alternate(GPIOE,12,Push_pull,High,No_pull,AF12); //FSMC D9
	GPIO_Alternate(GPIOE,13,Push_pull,High,No_pull,AF12); //FSMC D10
	GPIO_Alternate(GPIOE,14,Push_pull,High,No_pull,AF12); //FSMC D11
	GPIO_Alternate(GPIOE,15,Push_pull,High,No_pull,AF12); //FSMC D12
	GPIO_Alternate(GPIOD,8,Push_pull,High,No_pull,AF12); //FSMC D13
	GPIO_Alternate(GPIOD,9,Push_pull,High,No_pull,AF12); //FSMC D14
	GPIO_Alternate(GPIOD,10,Push_pull,High,No_pull,AF12); //FSMC D15
	GPIO_Alternate(GPIOD,11,Push_pull,High,No_pull,AF12); //FSMC A16/RS
	GPIO_Alternate(GPIOD,4,Push_pull,High,No_pull,AF12); //FSMC NOE/RD
	GPIO_Alternate(GPIOD,5,Push_pull,High,No_pull,AF12); //FSMC NWE/WR
	GPIO_Alternate(GPIOD,7,Push_pull,High,Pull_down,AF12); //FSMC NE1/LCS
	
	//==========================
// DI
	GPIO_DI_setup(GPIOA,11,Pull_up); //DI0
	GPIO_DI_setup(GPIOA,15,Pull_up); //DI1
	GPIO_DI_setup(GPIOC,7,Pull_up); //DI2
	GPIO_DI_setup(GPIOB,1,Pull_up); //DI3
	GPIO_DI_setup(GPIOB,3,Pull_up); //DI4
	GPIO_DI_setup(GPIOB,5,Pull_up); //DI5
	GPIO_DI_setup(GPIOB,9,Pull_up); //DI6
	GPIO_DI_setup(GPIOB,11,Pull_up); //DI7
//==========================

FSMC_Low_init();

GPIOE->BSRR = 1<<6;//включить подсветку дисплея
delay_ms(150);
GPIOE->BSRR = 1<<(0+16); //сброс дисплея
delay_ms(200);
GPIOE->BSRR = 1<<(0);
delay_ms(150);


I2C_STM32F4_init();
SSD1963_init();
FSMC_Fast_init();
	
GT911_Init();	
DMA_F4_init();
USART_F4_init(USART_def);

SCADA_init();


Screen_update=1;
	Numpad_init[0].Numpad_Active=0;

	while (1)
	{
		
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Screen update BEGIN
		
	if (Screen_update)
	{		SSD1963_ClearScreen(0xff);
		//	TFT_Draw_image(10,200,320,240,&img);
			Button_init[0].button_update=1;
			Button_init[1].button_update=1;
			Button_init[2].button_update=1;
			Button_init[3].button_update=1;
			
			Valve_init[0].Valve_update = 1;
	
	Screen_update = 0;
	}
//Screen update END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//---------------------------------------------------------------------------------------------------	
	
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Touch scan Begin	
	GT911Touch[0].XCoordinate=0;		
	GT911Touch[0].YCoordinate=0;
	if (TOUCH_Press) TouchCount = GT911_ReadTouch(&GT911Touch[0]);
	
	if ((TOUCH_Press && !TIM1_Delay_4) || scan_push_back_front )  //Scan press with delay 
	{	if (scan_push_back_front) {GT911Touch[0].XCoordinate=0;		GT911Touch[0].YCoordinate=0;}
		else 
			TIM1_Delay_4 = 1000;
		push_trip_main=1;
		scan_push_back_front=0;
		
		TFT_Scan_press_Valve(0);
		if (Ctrl_Console_init[0].Ctrl_console_visible) TFT_Scan_press_Ctrl_Console(0);
		
		
	}
		else { if(push_trip_main && !TIM1_Delay_4) {scan_push_back_front =1; push_trip_main=0;}}

		
		TFT_Numpad();
	
		
	if (TOUCH_Press) //Scan press with out delay
	{	 
		__NOP();
		TFT_Scan_press_Button_with_delay(0,100);	
		TFT_Scan_press_Button_with_delay(1,100);
		TFT_Scan_press_Button_with_delay(2,100);
		TFT_Scan_press_Button_with_delay(3,100);
		
	
	}

	
	
//Touch scan END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<	

//-----------------------------------------------------------------------------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//animation BEGIN
	
	animation_update=0;
	if (!TIM1_Delay_3) {if (animation_count<5)  animation_count++; else animation_count=0; TIM1_Delay_3 = 5; animation_update=1;} 
	
	if (Button_init[0].button_State ==1 && animation_update)	
					TFT_Draw_image(Button_init[0].button_X0+20,20,60,60,&(Vent_gif_2[animation_count]));  
		else 	TFT_Draw_image(Button_init[0].button_X0+20,20,60,60,&Vent_gif_2);
	
	if (Button_init[1].button_State ==1 && animation_update)	
					TFT_Draw_image(Button_init[1].button_X0+20,20,60,60,&(Vent_gif_2[animation_count]));  
		else 	TFT_Draw_image(Button_init[1].button_X0+20,20,60,60,&Vent_gif_2);
	
	if (Button_init[2].button_State ==1 && animation_update)	
					TFT_Draw_image(Button_init[2].button_X0+20,20,60,60,&(Vent_gif_2[animation_count]));  
		else 	TFT_Draw_image(Button_init[2].button_X0+20,20,60,60,&Vent_gif_2);
	
	if (Button_init[3].button_State ==1 && animation_update)	
					TFT_Draw_image(Button_init[3].button_X0+20,20,60,60,&(Vent_gif_2[animation_count]));  
		else 	TFT_Draw_image(Button_init[3].button_X0+20,20,60,60,&Vent_gif_2);
	
	
	if (!TIM1_Delay_2) {if (temp16 >=999) {temp16=0;} else temp16++; TIM1_Delay_2=10;}

	if (GPIOE->IDR & 1<<4) {TOUCH_IRQ=1;} else {TOUCH_IRQ=0;}
	
	
	if (TIM1_Delay_5) {FPS_screen_temp++;}
	if (!TIM1_Delay_5) {FPS_screen[0] = FPS_screen_temp; FPS_screen_temp=0; TIM1_Delay_5 = 1000;}
//animation END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	
//---------------------------------------------------------------------------------------------------------------------------
	

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//String BEGIN 	
sprintf(String,"Позиция курсора X = %03d", GT911Touch[0].XCoordinate );	
TFT_Draw_string_font_10x16_back_fone(20,20,String,0xff00,0xff);

sprintf(String,"Позиция курсора Y = %03d",GT911Touch[0].YCoordinate);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*1,String,0xff00,0xff);
	
sprintf(String,"Size = %03d",GT911Touch[0].Size);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*2,String,0xff00,0xff);	
	
sprintf(String,"Touch_Status = %02x", Touch_status);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*3,String,0xff00, 0xff);


sprintf(String,"Счетчик = %3d", temp16);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*4,String,0xff00, 0xff);

if (GPIOE->IDR & 1<<4) {TOUCH_IRQ=1;} else {TOUCH_IRQ=0;}
sprintf(String,"Касание = %d", TOUCH_IRQ);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*5,String,0xff00, 0xff);

sprintf(String,"Температура = %02.1f", temperature*0.1);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*6,String,0xff00, 0xff);

sprintf(String,"FPS = %02d", FPS_screen[0]);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*7,String,0xff00, 0xff);

sprintf(String,"USART_FAULT = %d", usart_fault);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*8,String,0xff00, 0xff);

sprintf(String,"pulse_500ms = %d", pulse_500ms);	
TFT_Draw_string_font_10x16_back_fone(20,20+16*9,String,0xff00, 0xff);


		sprintf(String,"ON = %04d", ON_value);	
		X0=220;
		Y0=220;
		lenght =100;
		height = 16;
		TFT_Draw_string_font_10x16_back_fone(X0,Y0,String,0xff00, 0xff);
	if (Press_Area(X0,Y0,lenght,height) && !Numpad_init[0].Numpad_Active)
		{
			Numpad_init[0].Num_max = 3000;
			Numpad_init[0].Num_min = 0;
			Numpad_init[0].Value_adress = &ON_value;
			Numpad_init[0].Numpad_Active=1;
		}

		
		sprintf(String,"OFF = %04d", OFF_value);
		X0=220;
		Y0=280;
		lenght =100;
		height = 16;
		TFT_Draw_string_font_10x16_back_fone(X0,Y0,String,0xff00, 0xff);	
	if (Press_Area(X0,Y0,lenght,height) && !Numpad_init[0].Numpad_Active)
		{
			Numpad_init[0].Num_max = 2000;
			Numpad_init[0].Num_min = 0;
			Numpad_init[0].Value_adress = &OFF_value;
			Numpad_init[0].Numpad_Active=1;
		}

//String END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//---------------------------------------------------------------------------------------------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Status LED BEGIN

if (DI0) TFT_Status_LED (0,2); else TFT_Status_LED(0,1); 		
if (DI1) TFT_Status_LED (1,2); else TFT_Status_LED(1,1); 	
if (DI2) TFT_Status_LED (2,2); else TFT_Status_LED(2,1); 	
if (DI3) TFT_Status_LED (3,2); else TFT_Status_LED(3,1); 	
if (DI4) TFT_Status_LED (4,2); else TFT_Status_LED(4,1); 	
if (DI5) TFT_Status_LED (5,2); else TFT_Status_LED(5,1); 	
if (DI6) TFT_Status_LED (6,2); else TFT_Status_LED(6,1); 	
if (Output_1) TFT_Status_LED (7,2); else TFT_Status_LED(7,1); 	

		

//Status LED END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//----------------------------------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Valve Draw BEGIN

if (Valve_init[0].Valve_update)
		{	Valve_init[0].Valve_update=0;
			if (Ctrl_Console_init[0].Ctrl_console_output_enable)	TFT_Valve_Draw(0,2); else	TFT_Valve_Draw(0,1);
		}

//TFT_Valve_Draw(1,2);
//TFT_Valve_Draw(2,1);
//TFT_Valve_Draw(3,2);



//Valve Draw END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//----------------------------------------------------------

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Button Draw BEGIN

if (Button_init[0].button_update)
		{	Button_init[0].button_update=0;
			if (Button_init[0].button_State == 0) {TFT_Button_Draw(0,0); GPIOA->BSRR = 1<<(1+16);}
			if (Button_init[0].button_State == 1) {TFT_Button_Draw(0,1); GPIOA->BSRR = 1<<(1);}
		}

if (Button_init[1].button_update) 
		{Button_init[1].button_update=0;
			if (Button_init[1].button_State == 0) {TFT_Button_Draw(1,0); GPIOA->BSRR = 1<<(3+16);}
			if (Button_init[1].button_State == 1) {TFT_Button_Draw(1,1); GPIOA->BSRR = 1<<(3);}
		}

if (Button_init[2].button_update) 
		{Button_init[2].button_update=0;
			if (Button_init[2].button_State == 0) {TFT_Button_Draw(2,0); GPIOA->BSRR = 1<<(5+16);}
			if (Button_init[2].button_State == 1) {TFT_Button_Draw(2,1); GPIOA->BSRR = 1<<(5);}
		}

if (Button_init[3].button_update) 
		{Button_init[3].button_update=0;
			if (Button_init[3].button_State == 0) {TFT_Button_Draw(3,0); GPIOA->BSRR = 1<<(7+16);}
			if (Button_init[3].button_State == 1) {TFT_Button_Draw(3,1); GPIOA->BSRR = 1<<(7);}
		}

//Button Draw END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//----------------------------------------------------------
		
		
		
		
		
		
		
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//Action touch BEGIN
if (Button_init[0].button_press)
		{		Button_init[0].button_press=0;
				Button_init[0].button_update=1;	
				if (Button_init[0].button_State) Button_init[0].button_State = 0; else Button_init[0].button_State =1; 
		}

if (Button_init[1].button_press)
		{		Button_init[1].button_press=0;
				Button_init[1].button_update=1;	
				if (Button_init[1].button_State) Button_init[1].button_State = 0; else Button_init[1].button_State =1; 
		}
		
if (Button_init[2].button_press)
		{		Button_init[2].button_press=0;
				Button_init[2].button_update=1;	
				if (Button_init[2].button_State) Button_init[2].button_State = 0; else Button_init[2].button_State =1; 
		}
		
if (Button_init[3].button_press)
		{		Button_init[3].button_press=0;
				Button_init[3].button_update=1;	
				if (Button_init[3].button_State) Button_init[3].button_State = 0; else Button_init[3].button_State =1; 
		}		


if (Valve_init[0].Valve_Press) 
		{	Valve_init[0].Valve_Press=0; 
			Valve_init[0].Valve_update=1;
			Ctrl_Console_init[0].Ctrl_console_visible=1; Ctrl_Console_init[0].Ctrl_console_update=1;
		}
		
if (Ctrl_Console_init[0].Ctrl_console_visible && Ctrl_Console_init[0].Ctrl_console_update) 
		{	TFT_Ctrl_Console_Draw(0);
			Valve_init[0].Valve_update=1;
		}
		

//Action touch END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//-----------------------------------------------------------------------------------------------------------------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>		
//Programm BEGIN
//temperature = DS18B20_read_temperatur(USART_def);
		
if (temp16 >= ON_value && temp16 <= OFF_value) Output_1=1; else  Output_1 =0;		
		
		
//GPIOA->BSRR = 1<<0;		
//Program END
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

}	
}
