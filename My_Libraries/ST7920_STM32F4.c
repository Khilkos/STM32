#include "ST7920_STM32F4.h"

uint8_t img_scr[size_y][size_x];
extern const unsigned char FontTable[256][5];



//==========================================
//прототипы функций
//==========================================

//
void copy_to_img_scr (uint8_t y_pos, uint8_t x_pos, uint8_t y_size, uint8_t x_size, const unsigned char ar[][x_size/8]);
//копирование изображение из флеша в кадровый буфер, сначала координаты y, x-кратная 8, затем размер массива с изображением y,x-кратное 8 */
//

void digit (uint8_t y_pos, uint8_t x_pos,uint16_t data, uint8_t size, uint8_t dot_pos, uint8_t mask);
//вывод блока максимально из 5 чисел, с координатами y,x, само число, количество цифр не больше 5, количество цифр после запятой не больше 5, 
//позиция цифры которая будет мерцать с тактовой частотой переменной Bool pulse_1000ms
//
/*
char String[100];
sprintf(String,"Время %02d:%02d:%02d DS3231",hour, minutes,seconds );
	LCD_string(0,0,(uint8_t*)String);	

*/
//=========================================
//передача командт дисплею по SPI
//===========================================
void LCD_comand (unsigned char data)
{
	
//	uint8_t SREG_save=SREG;
//	cli ();
//	SPCR=(1<<SPE|1<<MSTR|1<<SPR0);
unsigned char temp;
GPIOA->BSRR=1<<CS;
SPI1->DR=0b11111000;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
	temp=data;
	temp&=0b11110000;
SPI1->DR=temp;
	while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
		temp=(unsigned char)(data<<4);	
SPI1->DR=temp;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
delay_us(5);
GPIOA->BSRR=(1<<(CS+res));
__NOP();
__NOP();
__NOP();
// SREG=SREG_save;
delay_us (21);
}

//============================================
//Передача данных дисплею по SPI
//=============================================
void LCD_data (unsigned char data)
{
//uint8_t SREG_save=SREG;
//cli ();
unsigned char temp;
GPIOA->BSRR=(1<<CS);
SPI1->DR=0b11111010;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
		temp=data;
		temp&=0b11110000;
SPI1->DR=temp;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
			temp=(unsigned char)(data<<4);
SPI1->DR=temp;
while (!(SPI1->SR&SPI_SR_TXE)) {__NOP();}
delay_us(5);
GPIOA->BSRR=(1<<(CS+res));
__NOP();
__NOP();
__NOP();
delay_us(21);
//	 SREG=SREG_save;
}


//======================================================
//Инициализация дисплея
//========================================================
void LCD_init(void)
{
	unsigned char count_x=0;
	unsigned char count_y=0;
		LCD_comand(0b00110110);
		for (count_y=0;count_y<=31;count_y++)
		{
			unsigned char temp_y=count_y;
			temp_y|=0b10000000;
			LCD_comand(temp_y);
			LCD_comand(0b10000000);
				for (count_x=0;count_x<=15;count_x++)
					{	LCD_data(0b00000000);
						LCD_data(0b00000000);
					}
		}
}

//========================================
//Вывод изображения на экран
//==========================================
void LCD_out (void)
{
	void *ptr = img_scr;
	uint32_t* arr=ptr;
	uint32_t size=(size_x*8*size_y)/32;
	unsigned char y_scr,x_scr;
	
//вывод первой половины экрана

for (y_scr=0;y_scr<32;y_scr++)
	{
	unsigned char temp_y=y_scr;
	temp_y|=0b10000000;
	LCD_comand(temp_y);
	LCD_comand(0b10000000);
		for (x_scr=0;x_scr<16;x_scr++)
		{
			unsigned char data=img_scr[y_scr][x_scr];
			LCD_data(data);
	//		img_scr[y_scr][x_scr]=0;
		}
	}
// вывод второй половины экрана
for (y_scr=0;y_scr<32;y_scr++)
{
	unsigned char temp_y=y_scr;
	temp_y|=0b10000000;
	LCD_comand(temp_y);
	LCD_comand(0b10001000);
	for (x_scr=0;x_scr<16;x_scr++)
	{
		unsigned char data=img_scr[y_scr+32][x_scr];
		LCD_data(data);
	//	img_scr[y_scr+32][x_scr]=0;
		
	}
}
//очистка кадрового буфера
		for (uint8_t i=0; i<(size-1);i++)
		{
				*(arr+i)=0;
		}
}
/*
//=============================================================
//перенос образа из шаблона в образ для дисплея img_scr
//===============================================================
void copy_to_img_scr (uint8_t y_pos, uint8_t x_pos, uint8_t y_size, uint8_t x_size, const unsigned char ar[][x_size/8])
{
	for (int temp_y=0;temp_y<y_size;temp_y++)
	{
		for (int temp_x=0;temp_x<(x_size/8);temp_x++)
		{
			img_scr[y_pos+temp_y][x_pos/8+temp_x]=pgm_read_byte(&(ar[temp_y][temp_x]));
		}
	}
}
*/
/*
//==========================================
//Отрисовка статус бар
//============================================
void status_bar (void)
{
	img_scr[63][15]=0b11111111;
	img_scr[62][15]=0b10000001;
	img_scr[0][15]=0b11111111;
	img_scr[1][15]=0b10000001;
	for (uint8_t i=2; i<62; i++)
	{
		if (ADC_res/2.044*10/80>i) img_scr[63-i][15]=0b10111101;
		else img_scr[63-i][15]=0b10000001;
	}
}

*/

//=============================================================
//отрисовка линий функция line агументы y1,x1,y2,x2 -  начальные
// и конечные кооординаты трямой,требует библиотеки math.h
//==============================================================
void line (int y1, int x1, int y2, int x2)
{		volatile	int x_last=0;
		int xi;
		double d;
	if (y1>y2) {int m=x2; x2=x1; x1=m; m=y2; y2=y1; y1=m;}
	if ((y2-y1)==0){
		if (x2>=x1) {for (int i=x1; i!=x2+1;i++) img_scr[y1][i/8]|=(128>>i%8);}
		else {for (int i=x2; i!=x1+1;i++) img_scr[y1][i/8]|=(128>>i%8);}  }
		else{
			double k=(double)(x2-x1)/(y2-y1);
			for (int y=y1,tmp=0; y!=y2+1; y++, tmp++)
			{   double x=x1+k*tmp;
				d=round(x);
				xi=(int)d;
				//     printf ("x=%d    y=%d\n", xi,y);
				img_scr[y][xi/8]|=(128>>xi%8);
		
				if (xi==x1) x_last=xi;
				else{
					if ((x2-x1)>=0){
						for (int i=x_last+1; i<xi;i++)
						img_scr[y-1][i/8]|=(128>>i%8);
					x_last=xi;}
					else {
						for (int i=xi+1; i<x_last;i++)
						img_scr[y-1][i/8]|=(128>>i%8);
					x_last=xi;}
				}
			}
		}
	}

//==============================================================
//вывод точки на экран
//==============================================================
void dot (int y, int x)
{img_scr[y][x/8]|=(128>>x%8);}

//==============================================================
//погасить точку на экране
//==============================================================
void no_dot (int y, int x)
{img_scr[y][x/8]&=~(128>>x%8);}

//==============================================================
//вывод одной цифры, аргументы Y, X, int - цифра
//==============================================================
void digit_single (uint8_t y, uint8_t x, uint8_t dig)
{	unsigned char ch[2]="0";
		switch(dig)
	{	case 0: *ch='0';
		break;
		case 1: *ch='1';
		break;
		case 2: *ch='2';
		break;
		case 3: *ch='3';
		break;
		case 4: *ch='4';
		break;
		case 5: *ch='5';
		break;
		case 6: *ch='6';
		break;
		case 7: *ch='7';
		break;
		case 8: *ch='8';
		break;
		case 9:	*ch='9';
		break;
		default: *ch=' ';
	}
	LCD_string(y,x,(uint8_t*)&ch);
}
//=========================================================
//Вывод строки ASCII на экран 
//=========================================================
void LCD_string (int y, int x, uint8_t *str)
{	while (*str!='\0')
	{	unsigned char    let=*str;
		for (int k=0; k<5; k++)
		{	int temp=FontTable[let][k];
			//int temp=pgm_read_byte(&FontTable[let][k]);
			for ( int i=0; i<8; i++)
				{if (temp&(1<<7)) dot(y+7-i,x+k); else no_dot(y+7-i,x+k);
				temp=(temp<<1);}
		}
	x+=6;
	str++;
	}
}
//==================================
/*
//================================================================
//отрисовка блока из 5 цифр
//==================================================================
void digit (uint8_t y_pos, uint8_t x_pos,uint16_t data, uint8_t size, uint8_t dot_pos, uint8_t mask)
{	if (size>5) size=5;
	if (dot_pos>5) dot_pos=5;
	if (mask>5) mask=0;
	uint8_t ar_dig[5]={0,0,0,0,0};
	int32_t temp16=0;
		temp16=data;
		while((temp16-=10000)>=0) (*ar_dig)++;
		temp16+=10000;
		while((temp16-=1000)>=0) (*(ar_dig+1))++;
		temp16+=1000;
		while((temp16-=100)>=0) (*(ar_dig+2))++;
		temp16+=100;
		while((temp16-=10)>=0) (*(ar_dig+3))++;
		temp16+=10;
		*(ar_dig+4)=temp16;
	uint8_t k=0;
		for (uint8_t i=5-size; i<5;i++)
		{	if (5-i==dot_pos) {k=2;  dot(y_pos+7,x_pos+6*(i-5+size));}
				if (5-i==mask && pulse_1000ms && mask!=0) digit_single(y_pos,x_pos+6*(i-5+size)+k,10);
					else	digit_single(y_pos,x_pos+6*(i-5+size)+k,*(ar_dig+i));
		}
}
*/
//==============================================================
void ST7920_running_line(uint8_t *str, uint8_t Y_pos)
{	uint8_t X_size=128;
	static uint32_t HUB75_temp_screen_buf[8][4];
	static uint8_t HUB75_temp_buffet_update;
	static uint8_t HUB75_temp_buffer[8];
	static uint8_t* HUB75_running_let;
	for (uint8_t y=0; y<8; y++)
	{	for (uint8_t x=0; x<(X_size-1); x++) //32=64
		{	if(HUB75_temp_screen_buf[y][(x+1)/32]&(0x1UL<<(x+1)%32)) {HUB75_temp_screen_buf[y][x/32] |=(1<<x%32); dot(y+Y_pos,x); } else {HUB75_temp_screen_buf[y][x/32] &=~(1<<x%32); no_dot(y+Y_pos,x);}	
			if (x==(X_size-2)) 
				{	if (y==0) 
								{	if (HUB75_temp_buffet_update==0)
										{	    if (HUB75_running_let==0) HUB75_running_let=str;
											for (uint8_t x1=0; x1<5; x1++)
											{	for (uint8_t y1=0; y1<8;y1++)
												{if ( ((FontTable[*HUB75_running_let][x1]))&(1<<y1) ) HUB75_temp_buffer[y1]|=(1<<(6-x1));}
											}
											if (*HUB75_running_let!='\0')	 HUB75_running_let++; else HUB75_running_let=0;
										}
									if (HUB75_temp_buffet_update<5) HUB75_temp_buffet_update++; else HUB75_temp_buffet_update=0;	
								}
					
					if (HUB75_temp_buffer[y]&(1<<7)) HUB75_temp_screen_buf[y][x/32] |=(1<<x%32); else HUB75_temp_screen_buf[y][x/32] &=~(1<<x%32); 
					HUB75_temp_buffer[y]*=2; //сдвиг влево
				}
		}		
	}

}

//=========================================================
//Вывод строки ASCII на экран 
//=========================================================
void LCD_string_font_10x16 (int y, int x, uint8_t *str)
{	while (*str!='\0')
	{	unsigned char    let=*str;
		for (int k=0; k<10; k++)
		{	int temp= font_10x16[let*10+k];//FontTable[let][k];
			//int temp=pgm_read_byte(&FontTable[let][k]);
			for ( int i=0; i<16; i++)
				{if (temp&(1<<15)) dot(y+15-i,x+k); else no_dot(y+15-i,x+k);
				temp=(temp<<1);}
		}
	x+=11;
	str++;
	}
}
//==================================
