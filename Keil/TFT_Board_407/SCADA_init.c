#include "SCADA_init.h"

void SCADA_init(void)
{
uint8_t num=0;
// 	0x9cd3 - ����� ����, ��� ������
//  0x5aeb - ����� �����, ��� ������	
//	0x1e63 - ������� ����
//	0xe8c3 - ������� ����
//	0xfde1 - ������ ����
//	0x9841 - ����� �������
//	0x7041 - ������ ����� �������	
//	0x0bc3 - ����� �������
//  0x0240 - ������ ����� �������
//	0x00ff - �����, ��� �������� �����
//	0xC480 - ����� ������

//Status_LED 0
//	
num=0;
Status_LED_init[num].Status_LED_X0=480;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------	
//Status_LED 1
//	
num=1;
Status_LED_init[num].Status_LED_X0=510;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 2
//	
num=2;
Status_LED_init[num].Status_LED_X0=540;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 3
//	
num=3;
Status_LED_init[num].Status_LED_X0=570;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 4
//	
num=4;
Status_LED_init[num].Status_LED_X0=600;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 5
//	
num=5;
Status_LED_init[num].Status_LED_X0=630;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 6
//	
num=6;
Status_LED_init[num].Status_LED_X0=660;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
//Status_LED 7
//	
num=7;
Status_LED_init[num].Status_LED_X0=690;
Status_LED_init[num].Status_LED_Y0=160;	
//-------------------------------------
	


//******************************************************************
	
//button 0	-------------------------------------------------- 
//������ ��������� ����1	
num=0;
Button_init[num].button_X0=300; //���������� X �������� ������ ���� ������
Button_init[num].button_Y0=100;	//���������� Y �������� ������ ���� ������
Button_init[num].button_rect=1;	//������ ����������� ����� ������
Button_init[num].button_lenght=100;	//����� ������
Button_init[num].button_height=40;	//������ ������
Button_init[num].button_frame_size=2;	//������� ����� ������ ������
Button_init[num].button_frame_light_color=0xc5f8;	//���� ������� (�������) ������� �����
Button_init[num].button_frame_dark_color=0x1062;	//���� ������ (������)������� �����

Button_init[num].button_color_State[0]=0x9cd3;	//���� ������, ��������� 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],"���� 1"); //����� ������ �����, ������ 1, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// ���� ������ ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"����");	//����� ������ �����, ������ 2, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// ���� ������ ������ 2, ��� ��������� 0
	
Button_init[num].button_color_State[1]=0x1e63;	//���� ������, ��������� 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],"���� 1"); //����� ������ �����, ������ 1, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// ���� ������ ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"���");	//����� ������ �����, ������ 2, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// ���� ������ ������ 2, ��� ��������� 1


//button1	---------------------------------------------------------
//������ ��������� ����2	
num=1;
Button_init[num].button_X0=420;
Button_init[num].button_Y0=100;
Button_init[num].button_rect=1;
Button_init[num].button_lenght=100;
Button_init[num].button_height=40;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//���� ������, ��������� 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],"���� 2"); //����� ������ �����, ������ 1, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// ���� ������ ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"����");	//����� ������ �����, ������ 2, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// ���� ������ ������ 2, ��� ��������� 0
	
Button_init[num].button_color_State[1]=0x1e63;	//���� ������, ��������� 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],"���� 2"); //����� ������ �����, ������ 1, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// ���� ������ ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"���");	//����� ������ �����, ������ 2, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// ���� ������ ������ 2, ��� ��������� 1

//button2	---------------------------------------------------------
//������ ��������� ����3	
num=2;
Button_init[num].button_X0=540;
Button_init[num].button_Y0=100;
Button_init[num].button_rect=1;
Button_init[num].button_lenght=100;
Button_init[num].button_height=40;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//���� ������, ��������� 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],"���� 3"); //����� ������ �����, ������ 1, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// ���� ������ ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"����");	//����� ������ �����, ������ 2, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// ���� ������ ������ 2, ��� ��������� 0
	
Button_init[num].button_color_State[1]=0x1e63;	//���� ������, ��������� 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],"���� 3"); //����� ������ �����, ������ 1, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// ���� ������ ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"���");	//����� ������ �����, ������ 2, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// ���� ������ ������ 2, ��� ��������� 1


//button3	---------------------------------------------------------
//������ ��������� ����4	
num=3;
Button_init[num].button_X0=660;
Button_init[num].button_Y0=100;
Button_init[num].button_rect=1;
Button_init[num].button_lenght=100;
Button_init[num].button_height=40;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//���� ������, ��������� 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],"���� 4"); //����� ������ �����, ������ 1, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// ���� ������ ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"����");	//����� ������ �����, ������ 2, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// ���� ������ ������ 2, ��� ��������� 0
	
Button_init[num].button_color_State[1]=0x1e63;	//���� ������, ��������� 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],"���� 4"); //����� ������ �����, ������ 1, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// ���� ������ ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"���");	//����� ������ �����, ������ 2, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// ���� ������ ������ 2, ��� ��������� 1

//button4	---------------------------------------------------------
//	
num=4;
Button_init[num].button_X0=400;
Button_init[num].button_Y0=160;
Button_init[num].button_rect=2;
Button_init[num].button_lenght=30;
Button_init[num].button_height=30;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//���� ������, ��������� 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],""); //����� ������ �����, ������ 1, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// ���� ������ ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"");	//����� ������ �����, ������ 2, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// ���� ������ ������ 2, ��� ��������� 0
	
Button_init[num].button_color_State[1]=0x1e63;	//���� ������, ��������� 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],""); //����� ������ �����, ������ 1, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// ���� ������ ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"");	//����� ������ �����, ������ 2, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// ���� ������ ������ 2, ��� ��������� 1

//button5	---------------------------------------------------------
//	
num=5;
Button_init[num].button_X0=500;
Button_init[num].button_Y0=160;
Button_init[num].button_rect=2;
Button_init[num].button_lenght=30;
Button_init[num].button_height=30;
Button_init[num].button_frame_size=2;
Button_init[num].button_frame_light_color=0xc5f8;
Button_init[num].button_frame_dark_color=0x1062;

Button_init[num].button_color_State[0]=0x9cd3;	//���� ������, ��������� 0
Button_init[num].button_TEXT_line_1_X_State[0]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_1_Y_Stete[0]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_1_State[0],""); //����� ������ �����, ������ 1, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_1_Color_State[0]=0x0000;	// ���� ������ ������ 1, ��� ��������� 0
Button_init[num].button_TEXT_line_2_X_State[0]=28;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 0
Button_init[num].button_TEXT_line_2_Y_Stete[0]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 0
sprintf(Button_init[num].buttuon_TEXT_line_2_State[0],"");	//����� ������ �����, ������ 2, ��� ��������� 0
Button_init[num].buttuon_TEXT_line_2_Color_State[0]=0x0000;	// ���� ������ ������ 2, ��� ��������� 0
	
Button_init[num].button_color_State[1]=0x1e63;	//���� ������, ��������� 1
Button_init[num].button_TEXT_line_1_X_State[1]=18; //�������� X ������������� ������ ������, ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_1_Y_Stete[1]=5;	//�������� Y ������������� ������ ������, ������ 1, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_1_State[1],""); //����� ������ �����, ������ 1, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_1_Color_State[1]=0x0000;	// ���� ������ ������ 1, ��� ��������� 1
Button_init[num].button_TEXT_line_2_X_State[1]=33;	//�������� X ������������� ������ ������, ������ 2, ��� ��������� 1
Button_init[num].button_TEXT_line_2_Y_Stete[1]=22;	//�������� Y ������������� ������ ������, ������ 2, ��� ��������� 1
sprintf(Button_init[num].buttuon_TEXT_line_2_State[1],"");	//����� ������ �����, ������ 2, ��� ��������� 1
Button_init[num].buttuon_TEXT_line_2_Color_State[1]=0x0000;	// ���� ������ ������ 2, ��� ��������� 1





}