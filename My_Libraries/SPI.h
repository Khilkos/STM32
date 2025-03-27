#ifndef __SPI_H
#define __SPI_H
#include "Config.h"

//#include "stm32f411xe.h"  //!!!!!!!!!!!!!!!!!!!
#include "main.h"




#define SPI1_CS_ON GPIOA->BSRR = 1<<6
#define SPI1_CS_OFF GPIOA->BSRR = 1<<(6+16)

extern _Bool SPI1_DMA_buzy;
extern uint32_t SPI1_send_num;

void SPI_F411_init(void);
void SPI_F4_init(uint8_t SPI_speed);
void SPI1_F4_send_8bit (uint32_t size,uint8_t* buf);
//#define DMA2_Stream2_IRQHandler_define
//void DMA2_Stream2_IRQHandler_User(void);


//=======SPI_H7========================
void SPI_H7_init(void);




//-----------------------------------------------
//----------������������� SPI--------------------
//-----------------------------------------------
		//��������� ������ ������ SPI
//SPI_H7.SPI_Number = ;	//����� SPI, �������� SPI1
//SPI_H7.MBR = ; // �������� �������� ������� ��� SPI, �� 0=/2, 1=/4 ....7=/256 	
//SPI_H7.DSIZE = ; // ���������� ��� � ����� �� 3=4����, 4=5���, .... 31=32����.	
//SPI_H7.MASTER_bit = ; //����� SPI: 0-Slave, 1-Master	
//SPI_H7.COMM = ;	//����� ������ SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex	
//SPI_H7.FTHLV = ; // ������� ������ FIFO, ���������� ������ ������, �� 0=1����, 1=2���� ... 15=16����	
//SPI_H7.TSIZE =;	//���������� ������ � ����� ������� (�� ����� ��������� SS)	
	//��������� CLK
//SPI_H7.CPOL_bit =; //���������� CLK:	0-SCK ������ ����� 0 �� idle, 1-SCK ������ ����� 1 �� idle
//SPI_H7.CPHA_bit =; //���� CLK: 0-������ ������� �� ������� ������ CLK, 1-������ ������� �� ������� ������ CLK	
	//��������� ������ SS
//SPI_H7.SSM_bit =; // ����������� SS ���� SSM=1, ����������� ����� SSI, ���� SSM=0 - SS ����������� ���������
//SPI_H7.SSOE_bit =; //��������� ����������� ������ SS: 0 - ��������, 1-�������
//SPI_H7.SSIOP_bit = ; //����� ��������� ������ SS: 0-������ ������� ��� �������� SS, 1- ������� ������� ��� �������� SS	
//SPI_H7.SSOM_bit = ; //����� ������ ������ SS � MASTER mode
//SPI_H7.MSSI = ; //������ �� SS ������ ��������, �������� �� 0 �� 15 ������	
	//��������� DMA
//SPI_H7.Tx_DMA =;// ��������� ������ ��� �� �������� (Tx DMA stream enable): 1- �������, 0- ��������	
//SPI_H7.Rx_DMA =;// ��������� ������ ��� �� ����� (Rx DMA stream enable): 1- �������, 0- ��������
//
//SPI_H7_init();//������ SPI � ��������� �����������
//------------------------------------------------



struct SPI_H7_init{
SPI_TypeDef* SPI_Number; //����� SPI, �������� SPI1
_Bool SSM_bit; // ����������� SS ���� SSM=1, ����������� ����� SSI, ���� SSM=0 - SS ����������� ���������
uint8_t MBR; // �������� �������� ������� ��� SPI, �� 0=/2, 1=/4 ....7=/256 
uint8_t DSIZE; // ���������� ��� � ����� �� 3=4����, 4=5���, .... 31=32����.
uint8_t FTHLV; // ������� ������ FIFO, ���������� ������ ������, �� 0=1����, 1=2���� ... 15=16����
_Bool MASTER_bit; //����� SPI: 0-Slave, 1-Master
_Bool CPOL_bit; //���������� CLK:	0-SCK ������ ����� 0 �� idle, 1-SCK ������ ����� 1 �� idle
_Bool CPHA_bit; //���� CLK: 0-������ ������� �� ������� ������ CLK, 1-������ ������� �� ������� ������ CLK
_Bool SSOE_bit; //��������� ����������� ������ SS: 0 - ��������, 1-�������	
_Bool SSIOP_bit; //����� ��������� ������ SS: 0-������ ������� ��� �������� SS, 1- ������� ������� ��� �������� SS
_Bool SSOM_bit;	//����� ������ ������ SS � MASTER mode
uint8_t MSSI; //������ �� SS ������ ��������, �������� �� 0 �� 15 ������
uint8_t COMM; //����� ������ SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex
uint16_t TSIZE; //���������� ������ � ����� ������� (�� ����� ��������� SS)
_Bool Tx_DMA;// ��������� ������ ��� �� �������� (Tx DMA stream enable): 1- �������, 0- ��������	
_Bool Rx_DMA;// ��������� ������ ��� �� ����� (Rx DMA stream enable): 1- �������, 0- ��������

};

extern struct SPI_H7_init SPI_H7;

//-------------------------------------








#endif





