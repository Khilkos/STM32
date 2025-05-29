#include "main.h"
//#include "GPIO_setup.h"

#define TOUCH_Press !(GPIOE->IDR & 1<<4)

static uint32_t temp32=0;
static uint16_t temp16=0;
static uint8_t temp8=0;
static char String[300];
_Bool TOUCH_IRQ=0;
static uint16_t FPS_screen[10];
static uint16_t FPS_screen_temp;

static _Bool NEW_update=1;
static _Bool Button_1=0;
static _Bool Button_2=0;
static _Bool Button_3=0;
static _Bool Button_4=0;


static uint16_t temperature=0;

int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOHEN); // enable portA and portB clock

	Core_F4_init_HSE_full(6,168,2,7,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	
	
	GPIO_DO_setup(GPIOE,6,High);//LCD подсветка
	GPIO_DO_setup(GPIOE,0,High);//LCD_Reset
	GPIO_DO_setup(GPIOA,1,High);//Реле 1
	GPIO_DO_setup(GPIOA,3,High);//Реле 2
	GPIO_DO_setup(GPIOA,5,High);//Реле 3
	GPIO_DO_setup(GPIOA,7,High);//Реле 4	
	
	
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

FSMC_init();

GPIOE->BSRR = 1<<6;//включить подсветку дисплея
delay_ms(150);
GPIOE->BSRR = 1<<(0+16); //сброс дисплея
delay_ms(200);
GPIOE->BSRR = 1<<(0);
delay_ms(150);


I2C_STM32F4_init();
SSD1963_init();
SSD1963_ClearScreen(0xff);	
GT911_Init();	
DMA_F4_init();
USART_F4_init(USART_def);

TFT_Draw_image(10,200,320,240,&img);
//TFT_Draw_image(10,200,400,247,&img1);
//TFT_Draw_image(10,150,400,300,&img2);	
	while (1)
	{


	if (Button_1)	
	{if (!TIM1_Delay_3) {if (temp8<6)  {TFT_Draw_image(560,20,60,60,&(Vent_gif_2[temp8])); temp8++;} else temp8=0;  	TIM1_Delay_3 = 5;} }
			else TFT_Draw_image(560,20,60,60,&Vent_gif_2);
	
	if (!TIM1_Delay_2) {if (temp16 >=99) {temp16=0;} else temp16++; TIM1_Delay_2=10;}

	if (GPIOE->IDR & 1<<4) {TOUCH_IRQ=1;} else {TOUCH_IRQ=0;TouchCount = GT911_ReadTouch(&GT911Touch[0]);}
	
	
	if (TIM1_Delay_5) {FPS_screen_temp++;}
	if (!TIM1_Delay_5) {FPS_screen[0] = FPS_screen_temp; FPS_screen_temp=0; TIM1_Delay_5 = 1000;}

	if ((TOUCH_Press && !TIM1_Delay_4) || NEW_update) 
	{	NEW_update = 0;
		TIM1_Delay_4 = 1000;
		if ((GT911Touch[0].XCoordinate>680 && GT911Touch[0].XCoordinate<(680+100) && GT911Touch[0].YCoordinate>(20+80*0) && GT911Touch[0].YCoordinate<(20+80*0+60)))
					{if (Button_1) Button_1=0; else Button_1=1;}
		
		if ((GT911Touch[0].XCoordinate>680 && GT911Touch[0].XCoordinate<(680+100) && GT911Touch[0].YCoordinate>(20+80*1) && GT911Touch[0].YCoordinate<(20+80*1+60)))
					{if (Button_2) Button_2=0; else Button_2=1;}
		
		if ((GT911Touch[0].XCoordinate>680 && GT911Touch[0].XCoordinate<(680+100) && GT911Touch[0].YCoordinate>(20+80*2) && GT911Touch[0].YCoordinate<(20+80*2+60)))
					{if (Button_3) Button_3=0; else Button_3=1;}
		
		if ((GT911Touch[0].XCoordinate>680 && GT911Touch[0].XCoordinate<(680+100) && GT911Touch[0].YCoordinate>(20+80*3) && GT911Touch[0].YCoordinate<(20+80*3+60)))
					{if (Button_4) Button_4=0; else Button_4=1;}
		
		if (!Button_1) 
							{	//SSD1963_Horisontal_line(680,20,100,60,0xf800);
								TFT_Draw_Fill_Round_Rect(680,20+80*0,100,60,10,0xf800);
								sprintf(String,"РЕЛЕ 1");
								SSD1963_string_font_10x16(700,30,(uint8_t*)String,0xffff);
								sprintf(String,"ВЫКЛ");
								SSD1963_string_font_10x16(710,30+20,(uint8_t*)String,0xffff);
								GPIOA->BSRR = 1<<(1+16);
							}
					else 
							{	//SSD1963_Horisontal_line(680,20,100,60,0x7e0); 
								TFT_Draw_Fill_Round_Rect(680,20+80*0,100,60,10,0x7e0);
								sprintf(String,"РЕЛЕ 1");
								SSD1963_string_font_10x16(700,30,(uint8_t*)String,0x0000);
								sprintf(String,"ВКЛ");
								SSD1963_string_font_10x16(715,30+20,(uint8_t*)String,0x0000);
								GPIOA->BSRR = 1<<(1);
							}
				
		if (!Button_2) 
							{	//SSD1963_Horisontal_line(680,20,100,60,0xf800);
								TFT_Draw_Fill_Round_Rect(680,20+80*1,100,60,10,0xf800);
								sprintf(String,"РЕЛЕ 2");
								SSD1963_string_font_10x16(700,30+80*1,(uint8_t*)String,0xffff);
								sprintf(String,"ВЫКЛ");
								SSD1963_string_font_10x16(710,30+80*1+20,(uint8_t*)String,0xffff);
								GPIOA->BSRR = 1<<(3+16);
							}
					else 
							{	//SSD1963_Horisontal_line(680,20,100,60,0x7e0); 
								TFT_Draw_Fill_Round_Rect(680,20+80*1,100,60,10,0x7e0);
								sprintf(String,"РЕЛЕ 2");
								SSD1963_string_font_10x16(700,30+80*1,(uint8_t*)String,0x0000);
								sprintf(String,"ВКЛ");
								SSD1963_string_font_10x16(715,30+80*1+20,(uint8_t*)String,0x0000);
								GPIOA->BSRR = 1<<(3);
							}
		
			if (!Button_3) 
							{	//SSD1963_Horisontal_line(680,20,100,60,0xf800);
								TFT_Draw_Fill_Round_Rect(680,20+80*2,100,60,10,0xf800);
								sprintf(String,"РЕЛЕ 3");
								SSD1963_string_font_10x16(700,30+80*2,(uint8_t*)String,0xffff);
								sprintf(String,"ВЫКЛ");
								SSD1963_string_font_10x16(710,30+80*2+20,(uint8_t*)String,0xffff);
								GPIOA->BSRR = 1<<(5+16);
							}
					else 
							{	//SSD1963_Horisontal_line(680,20,100,60,0x7e0); 
								TFT_Draw_Fill_Round_Rect(680,20+80*2,100,60,10,0x7e0);
								sprintf(String,"РЕЛЕ 3");
								SSD1963_string_font_10x16(700,30+80*2,(uint8_t*)String,0x0000);
								sprintf(String,"ВКЛ");
								SSD1963_string_font_10x16(715,30+80*2+20,(uint8_t*)String,0x0000);
								GPIOA->BSRR = 1<<(5);
							}				
				
	if (!Button_4) 
							{	//SSD1963_Horisontal_line(680,20,100,60,0xf800);
								TFT_Draw_Fill_Round_Rect(680,20+80*3,100,60,10,0xf800);
								sprintf(String,"РЕЛЕ 4");
								SSD1963_string_font_10x16(700,30+80*3,(uint8_t*)String,0xffff);
								sprintf(String,"ВЫКЛ");
								SSD1963_string_font_10x16(710,30+80*3+20,(uint8_t*)String,0xffff);
								GPIOA->BSRR = 1<<(7+16);
							}
					else 
							{	//SSD1963_Horisontal_line(680,20,100,60,0x7e0); 
								TFT_Draw_Fill_Round_Rect(680,20+80*3,100,60,10,0x7e0);
								sprintf(String,"РЕЛЕ 4");
								SSD1963_string_font_10x16(700,30+80*3,(uint8_t*)String,0x0000);
								sprintf(String,"ВКЛ");
								SSD1963_string_font_10x16(715,30+80*3+20,(uint8_t*)String,0x0000);
								GPIOA->BSRR = 1<<(7);
							}											
							
		
	}
	//if (!TOUCH_Press) TOUCH_trip=0;
	
	
sprintf(String,"Позиция курсора X = %03d", GT911Touch[0].XCoordinate );	
SSD1963_string_font_10x16_back_fone(20,20,(uint8_t*)String,0xff00,0xff);

sprintf(String,"Позиция курсора Y = %03d",GT911Touch[0].YCoordinate);	
SSD1963_string_font_10x16_back_fone(20,20+16*1,(uint8_t*)String,0xff00,0xff);
	
sprintf(String,"Size = %03d",GT911Touch[0].Size);	
SSD1963_string_font_10x16_back_fone(20,20+16*2,(uint8_t*)String,0xff00,0xff);	
	
sprintf(String,"Touch_Status = %02x", Touch_status);	
SSD1963_string_font_10x16_back_fone(20,20+16*3,(uint8_t*)String,0xff00, 0xff);


sprintf(String,"Счетчик = %02d", temp16);	
SSD1963_string_font_10x16_back_fone(20,20+16*4,(uint8_t*)String,0xff00, 0xff);

if (GPIOE->IDR & 1<<4) {TOUCH_IRQ=1;} else {TOUCH_IRQ=0;}
sprintf(String,"Касание = %d", TOUCH_IRQ);	
SSD1963_string_font_10x16_back_fone(20,20+16*5,(uint8_t*)String,0xff00, 0xff);

sprintf(String,"Температура = %04.1f", temperature*0.1);	
SSD1963_string_font_10x16_back_fone(20,20+16*6,(uint8_t*)String,0xff00, 0xff);

sprintf(String,"FPS = %02d", FPS_screen[0]);	
SSD1963_string_font_10x16_back_fone(20,20+16*7,(uint8_t*)String,0xff00, 0xff);

//temperature = DS18B20_read_temperatur(USART_def);

TFT_Draw_Rectangle(398,398,104,62,2,0x0000);
TFT_Draw_Fill_Rectangle(400,400,100,60,0xFFFF);

TFT_Draw_Fill_Round_Rect(600,400,100,60,5,0x0000);

//TFT_Draw_image(10,200,320,240,&img);
}	
}
