#include "Game.h"
static uint8_t X,Y;
static uint8_t Line_Y1,Line_Y2,Line_Y3,Line_Y4,Line_Y5,Line_Y6=0;
static uint8_t Line_X1,Line_X2,Line_X3,Line_X4,Line_X5,Line_X6=0;
static uint8_t Line_delay=0;


void Game_Car_model (uint8_t X_poz, uint8_t Y_poz)
{
	//шасси машины
Nokia_5110_Vertical_line (X_poz,Y_poz,10);
Nokia_5110_Horizontal_line(X_poz-3,Y_poz+9,7);
Nokia_5110_Horizontal_line(X_poz-3,Y_poz+2,7);	
//левое заднее колесо
Nokia_5110_Vertical_line (X_poz-3,Y_poz+8,3);
Nokia_5110_Vertical_line (X_poz-5,Y_poz+8,3);
Nokia_5110_Horizontal_line(X_poz-5,Y_poz+8,3);	
Nokia_5110_Horizontal_line(X_poz-5,Y_poz+10,3);
//правое заднее колесо
Nokia_5110_Vertical_line (X_poz+3,Y_poz+8,3);
Nokia_5110_Vertical_line (X_poz+5,Y_poz+8,3);
Nokia_5110_Horizontal_line(X_poz+3,Y_poz+8,3);	
Nokia_5110_Horizontal_line(X_poz+3,Y_poz+10,3);
//левое переднее колесо
Nokia_5110_Vertical_line (X_poz-3,Y_poz+1,3);
Nokia_5110_Vertical_line (X_poz-5,Y_poz+1,3);
Nokia_5110_Horizontal_line(X_poz-5,Y_poz+1,3);	
Nokia_5110_Horizontal_line(X_poz-5,Y_poz+3,3);
//правое переднее колесо
Nokia_5110_Vertical_line (X_poz+3,Y_poz+1,3);
Nokia_5110_Vertical_line (X_poz+5,Y_poz+1,3);
Nokia_5110_Horizontal_line(X_poz+3,Y_poz+1,3);	
Nokia_5110_Horizontal_line(X_poz+3,Y_poz+3,3);
}
//=======================================================
void Game_Car (void)
{
if (!Delay_2) Delay_2=75;
if (!Delay_1) 
{		Delay_1=100;
		if (Line_delay<85) Line_delay++;
	
		if (Line_Y1<47 && (Line_delay>0) ) Line_Y1++; else {Line_Y1=0; Line_X1=(uint8_t)Delay_2;}
		if (Line_Y2<47 && (Line_delay>7)) Line_Y2++; else {Line_Y2=0; Line_X2=(uint8_t)Delay_2;}
		if (Line_Y3<47 && (Line_delay>15)) Line_Y3++; else {Line_Y3=0; Line_X3=(uint8_t)Delay_2;}
		if (Line_Y4<47 && (Line_delay>23)) Line_Y4++; else {Line_Y4=0; Line_X4=(uint8_t)Delay_2;}
		if (Line_Y5<47 && (Line_delay>29)) Line_Y5++; else {Line_Y5=0; Line_X5=(uint8_t)Delay_2;}
		if (Line_Y6<47 && (Line_delay>35)) Line_Y6++; else {Line_Y6=0; Line_X6=(uint8_t)Delay_2;}
}

//----препятствия на дороге-----
Nokia_5110_Horizontal_line (Line_X1 ,Line_Y1,9);
if(Line_delay>7) Nokia_5110_Horizontal_line (Line_X2 ,Line_Y2,9);
if(Line_delay>15) Nokia_5110_Horizontal_line (Line_X3 ,Line_Y3,9);
if(Line_delay>23) Nokia_5110_Horizontal_line (Line_X4 ,Line_Y4,9);
if(Line_delay>29) Nokia_5110_Horizontal_line (Line_X5 ,Line_Y5,9);
if(Line_delay>35) Nokia_5110_Horizontal_line (Line_X6 ,Line_Y6,9);

//---управление машиной---------
		X=(uint8_t)(ADC_ch[0]/48);
		Y=(uint8_t)(48-ADC_ch[1]/84);
		X=(X<78) ? X: 78 ;
		X=(X<5) ? 5: X ;
		Y=(Y<37) ? Y: 37 ;
		Game_Car_model (X,Y);
//------------------------------
}



