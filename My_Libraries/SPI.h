#ifndef __SPI_H
#define __SPI_H
#include "Config.h"

//#include "stm32f411xe.h"  //!!!!!!!!!!!!!!!!!!!
#include "main.h"


#define res 16

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
void SPI1_H7_init(void);
void SPI2_H7_init(void);



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

	
};

extern struct SPI_H7_init SPI_H7;

//-------------------------------------








#endif





