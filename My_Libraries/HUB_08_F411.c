#include "HUB_08_F411.h"

void HUB_08_Send (void)
{
//	_Bool Bit=0;
	static uint8_t line_num;
	uint64_t line[16]={
		0x0ff00fffffffffff,
		0xf00f0fffffffffff,
		0xf00f0fffffffffff,
		0x0ff00fffffffffff,
		0x00000fffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff,
		0xffffffffffffffff
										};
GPIOA->BSRR=1<<4;
	if (line_num>15) line_num=0;
	if (line_num==0) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==1) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3+res);}
			else if(line_num==2) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3+res);}
			else if(line_num==3) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3+res);}
			else if(line_num==4) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==5) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==6) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==7) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3+res);}
			else if (line_num==8) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3);}
			else if (line_num==9) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3);}
			else if (line_num==10) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3);}
			else if (line_num==11) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2+res);GPIOA->BSRR=1<<(3);}
			else if (line_num==12) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3);}
			else if (line_num==13) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1+res);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3);}
			else if (line_num==14) {GPIOA->BSRR=1<<(0+res); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3);}
			else if (line_num==15) {GPIOA->BSRR=1<<(0); GPIOA->BSRR=1<<(1);GPIOA->BSRR=1<<(2);GPIOA->BSRR=1<<(3);}
																
	
	for (uint8_t i=0; i<64; i++)
		{
			if (line[line_num]&0x01) GPIOB->BSRR=1<<(13+res); else GPIOB->BSRR=1<<(13);
			//delay_ms(1);
			GPIOB->BSRR=1<<14;
			delay_us(1);
			GPIOB->BSRR=1<<(14+res);
			//delay_ms(1);
		//	if (Bit) Bit=0; else Bit=1;
			//	Bit^=1;
			line[line_num] >>=1;
		}

GPIOB->BSRR=1<<15;
delay_us(1);
GPIOB->BSRR=1UL<<(15+res);
GPIOA->BSRR=1UL<<(4+res);
line_num++;
}


