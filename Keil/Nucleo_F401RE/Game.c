#include "Game.h"
static uint8_t X,Y;
static uint8_t Line_Y1,Line_Y2,Line_Y3,Line_Y4,Line_Y5,Line_Y6=0;
static uint8_t Line_X1,Line_X2,Line_X3,Line_X4,Line_X5,Line_X6=0;
static uint8_t Line_delay=0;
static char String[100];
static uint32_t max=0;
static uint32_t min=4000;
static uint32_t temp=0;


void Game_Car_model (uint8_t X_poz, uint8_t Y_poz)
{
	//����� ������
Nokia_5110_Vertical_line (X_poz,Y_poz,10);
Nokia_5110_Horizontal_line(X_poz-3,Y_poz+9,7);
Nokia_5110_Horizontal_line(X_poz-3,Y_poz+2,7);	
//����� ������ ������
Nokia_5110_Vertical_line (X_poz-3,Y_poz+8,3);
Nokia_5110_Vertical_line (X_poz-5,Y_poz+8,3);
Nokia_5110_Horizontal_line(X_poz-5,Y_poz+8,3);	
Nokia_5110_Horizontal_line(X_poz-5,Y_poz+10,3);
//������ ������ ������
Nokia_5110_Vertical_line (X_poz+3,Y_poz+8,3);
Nokia_5110_Vertical_line (X_poz+5,Y_poz+8,3);
Nokia_5110_Horizontal_line(X_poz+3,Y_poz+8,3);	
Nokia_5110_Horizontal_line(X_poz+3,Y_poz+10,3);
//����� �������� ������
Nokia_5110_Vertical_line (X_poz-3,Y_poz+1,3);
Nokia_5110_Vertical_line (X_poz-5,Y_poz+1,3);
Nokia_5110_Horizontal_line(X_poz-5,Y_poz+1,3);	
Nokia_5110_Horizontal_line(X_poz-5,Y_poz+3,3);
//������ �������� ������
Nokia_5110_Vertical_line (X_poz+3,Y_poz+1,3);
Nokia_5110_Vertical_line (X_poz+5,Y_poz+1,3);
Nokia_5110_Horizontal_line(X_poz+3,Y_poz+1,3);	
Nokia_5110_Horizontal_line(X_poz+3,Y_poz+3,3);
}
//=======================================================
void Game_Car (void)
{
if (!TIM2_Delay_1) TIM2_Delay_1=75;
if (!TIM1_Delay_1) 
{		TIM1_Delay_1=100;
		if (Line_delay<85) Line_delay++;

		temp=ADC_ch[3];
		if (temp>1750) temp=1750;
		if (temp<1600) temp=1600;
	temp = (temp-1600)/2;
	
	
		if (Line_Y1<47 && (Line_delay>0) ) Line_Y1++; else {Line_Y1=0; Line_X1=(uint8_t)temp;}
		if (Line_Y2<47 && (Line_delay>12)) Line_Y2++; else {Line_Y2=0; Line_X2=(uint8_t)temp;}
		if (Line_Y3<47 && (Line_delay>24)) Line_Y3++; else {Line_Y3=0; Line_X3=(uint8_t)temp;}
		if (Line_Y4<47 && (Line_delay>36)) Line_Y4++; else {Line_Y4=0; Line_X4=(uint8_t)temp;}
		if (Line_Y5<47 && (Line_delay>48)) Line_Y5++; else {Line_Y5=0; Line_X5=(uint8_t)temp;}
		if (Line_Y6<47 && (Line_delay>60)) Line_Y6++; else {Line_Y6=0; Line_X6=(uint8_t)temp;}

	}
//Nokia_5110_Vertical_line(temp,0,6);
	sprintf (String,"%03d",temp );
Nokia_5110_String(0,0,(uint8_t*)String);
	
	//temp=ADC_ch[3];
if (max<temp) max=temp;
if (min>temp && temp!=0) min=temp;
	

sprintf (String,"min-%d",min);
Nokia_5110_String(0,8,(uint8_t*)String);
sprintf (String,"max-%d",max);
Nokia_5110_String(0,16,(uint8_t*)String);

	/*sprintf (String,"%d",Line_X4);
Nokia_5110_String(0,24,(uint8_t*)String);
sprintf (String,"%d",Line_X5);
Nokia_5110_String(0,32,(uint8_t*)String);
sprintf (String,"%d",Line_X6);
Nokia_5110_String(0,40,(uint8_t*)String);
*/
	//----����������� �� ������-----
Nokia_5110_Horizontal_line (Line_X1 ,Line_Y1,9);
if(Line_delay>12) Nokia_5110_Horizontal_line (Line_X2 ,Line_Y2,9);
if(Line_delay>24) Nokia_5110_Horizontal_line (Line_X3 ,Line_Y3,9);
if(Line_delay>36) Nokia_5110_Horizontal_line (Line_X4 ,Line_Y4,9);
if(Line_delay>48) Nokia_5110_Horizontal_line (Line_X5 ,Line_Y5,9);
if(Line_delay>60) Nokia_5110_Horizontal_line (Line_X6 ,Line_Y6,9);

//---���������� �������---------
		X=(uint8_t)(ADC_ch[1]/48);
		Y=(uint8_t)(48-ADC_ch[2]/84);
		X=(X<78) ? X: 78 ;
		X=(X<5) ? 5: X ;
		Y=(Y<37) ? Y: 37 ;
		Game_Car_model (X,Y);
//------------------------------
}



