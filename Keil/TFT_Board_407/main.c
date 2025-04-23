#include "main.h"
//#include "GPIO_setup.h"


int main(void)
{
	RCC->AHB1ENR |= ( RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN); // enable portA and portB clock

	Core_F4_init_HSE_full(6,168,2,4,1,4,2); 
	SysTick_F4_Init (168);
	Timer1_F4_init(168000000,1000);
	FSMC_init();
	
	GPIO_DO_setup(GPIOE,6,High);
	GPIO_DO_setup(GPIOE,0,High);//LCD_Reset
GPIO_DO_setup(GPIOA,1,High);	
	
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

	GPIOE->BSRR = 1<<6;
//		GPIOA->BSRR = 1<<1;
	GPIOE->BSRR = 1<<(0+16);
	delay_us(10);
	GPIOE->BSRR = 1<<(0);
	delay_ms(10);
	
	
//LCD_init
LCD->LCD_REG = 0xE2; 	//PLL multiplier, set PLL clock to 120M
LCD->LCD_RAM = 29;	//M = 29 - множитель
LCD->LCD_RAM = 2;	//N = 2 - делитель
LCD->LCD_RAM = 0x54;

LCD->LCD_REG = 0xE0;	// PLL enable
LCD->LCD_RAM = 0x01;
delay_ms(10);

LCD->LCD_REG = 0xE0;
LCD->LCD_RAM = 0x03; // now, use PLL output as system clock
delay_ms(10);

LCD->LCD_REG = 0x01; // software reset
delay_ms(20);

LCD->LCD_REG = 0xE6; //PLL setting for PCLK, depends on resolution
LCD->LCD_RAM = 0x03;
LCD->LCD_RAM = 0x33;
LCD->LCD_RAM = 0x33;

LCD->LCD_REG = 0xB0; //LCD SPECIFICATION
LCD->LCD_RAM = 0x20; //24 bit TFT panel
LCD->LCD_RAM = 0x00; //Hsync+Vsync +DE mode  TFT mode
LCD->LCD_RAM = 0x03; //Set HDP
LCD->LCD_RAM = 0x1F;
LCD->LCD_RAM = 0x01; //Set VDP
LCD->LCD_RAM = 0xDF;
LCD->LCD_RAM = 0x00; //set RGB

LCD->LCD_REG =(0xB4);	//HSYNC
LCD->LCD_RAM = (0x04);  //Set HT
LCD->LCD_RAM = (0x1f);
LCD->LCD_RAM = (0x00);  //Set HPS
LCD->LCD_RAM = (0xd2);
LCD->LCD_RAM = (0x00);			   //Set HPW
LCD->LCD_RAM = (0x00);  //Set HPS
LCD->LCD_RAM = (0x00);
LCD->LCD_RAM = (0x00);

LCD->LCD_REG =(0xB6);	//VSYNC
LCD->LCD_RAM = (0x02);   //Set VT
LCD->LCD_RAM = (0x0c);
LCD->LCD_RAM = (0x00);  //Set VPS
LCD->LCD_RAM = (0x22);
LCD->LCD_RAM = (0x00);		//Set VPW
LCD->LCD_RAM = (0x00);  //Set FPS
LCD->LCD_RAM = (0x00);

LCD->LCD_REG =(0xB8);
LCD->LCD_RAM = (0x0f);    //GPIO is controlled by host GPIO[3:0]=output   GPIO[0]=1  LCD ON  GPIO[0]=1  LCD OFF 
LCD->LCD_RAM = (0x01);    //GPIO0 normal

LCD->LCD_REG =(0xBA);
LCD->LCD_RAM = (0x01);    //GPIO[0] out 1 --- LCD display on/off control PIN

LCD->LCD_REG =(0x36); //rotation
LCD->LCD_RAM = (0xC0);//RGB=BGR

LCD->LCD_REG =(0x3A); //Set the current pixel format for RGB image data
LCD->LCD_RAM = (0x50);//16-bit/pixel

LCD->LCD_REG =(0xF0); //Pixel Data Interface Format
LCD->LCD_RAM = (0x03);//16-bit(565 format) data 

LCD->LCD_REG =(0xBC); 
LCD->LCD_RAM = (0x40);//contrast value
LCD->LCD_RAM = (0x80);//brightness value
LCD->LCD_RAM = (0x40);//saturation value
LCD->LCD_RAM = (0x01);//Post Processor Enable

	delay_ms(5);

LCD->LCD_REG =(0x29); //display on


LCD->LCD_REG =(0xBE); //set PWM for B/L
LCD->LCD_RAM = (0x06);
LCD->LCD_RAM = (0x80);
LCD->LCD_RAM = (0x01);
LCD->LCD_RAM = (0xf0);
LCD->LCD_RAM = (0x00);
LCD->LCD_RAM = (0x00);

LCD->LCD_REG =(0xd0); 
LCD->LCD_RAM = (0x0d);


	
	while (1)
	{
			
	if (!TIM1_Delay_1) {if (GPIOA->IDR & 1<<1) GPIOA->BSRR = 1<<(1+16); else GPIOA->BSRR = 1<<1;  	TIM1_Delay_1 = 250;}
		
		
	}
	
}

////////////////////////////////////////////////////
void LCD_CmdWrite(const uint16_t Command)
{
 LCD->LCD_REG = Command;
}
void LCD_DataWrite(const uint16_t Data)
{
 LCD->LCD_RAM = Data;
}
void LCD_WriteReg(const uint8_t LCD_Reg, const uint16_t LCD_RegValue)
{
 LCD->LCD_REG = LCD_Reg;
 LCD->LCD_RAM = LCD_RegValue;
}
