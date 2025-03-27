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
//----------инициализация SPI--------------------
//-----------------------------------------------
		//настройка режима работы SPI
//SPI_H7.SPI_Number = ;	//Выбор SPI, например SPI1
//SPI_H7.MBR = ; // делитель тактовой частоты для SPI, от 0=/2, 1=/4 ....7=/256 	
//SPI_H7.DSIZE = ; // количество бит в кадре от 3=4бита, 4=5бит, .... 31=32бита.	
//SPI_H7.MASTER_bit = ; //режим SPI: 0-Slave, 1-Master	
//SPI_H7.COMM = ;	//режим работы SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex	
//SPI_H7.FTHLV = ; // уровень поорга FIFO, количество кадров данных, от 0=1кадр, 1=2кадр ... 15=16кадр	
//SPI_H7.TSIZE =;	//количество кадров в одной посылке (во время активного SS)	
	//настройка CLK
//SPI_H7.CPOL_bit =; //полярность CLK:	0-SCK сигнал когда 0 на idle, 1-SCK сигнал когда 1 на idle
//SPI_H7.CPHA_bit =; //фаза CLK: 0-захват сигнала по первому фронту CLK, 1-захват сигнала по фторому фронту CLK	
	//настройка вывода SS
//SPI_H7.SSM_bit =; // программный SS если SSM=1, управляется битом SSI, если SSM=0 - SS управляется аппаратно
//SPI_H7.SSOE_bit =; //включение аппаратного выхода SS: 0 - выключен, 1-включен
//SPI_H7.SSIOP_bit = ; //выбор активного уровня SS: 0-низкий уровень это активный SS, 1- высокий уровень это активный SS	
//SPI_H7.SSOM_bit = ; //режим работы выхода SS в MASTER mode
//SPI_H7.MSSI = ; //отступ от SS начала передачи, значение от 0 до 15 тактов	
	//настройка DMA
//SPI_H7.Tx_DMA =;// включение потока ДМА на передачу (Tx DMA stream enable): 1- включен, 0- выключен	
//SPI_H7.Rx_DMA =;// включение потока ДМА на прием (Rx DMA stream enable): 1- включен, 0- выключен
//
//SPI_H7_init();//запуск SPI с заданными параметрами
//------------------------------------------------



struct SPI_H7_init{
SPI_TypeDef* SPI_Number; //Выбор SPI, например SPI1
_Bool SSM_bit; // программный SS если SSM=1, управляется битом SSI, если SSM=0 - SS управляется аппаратно
uint8_t MBR; // делитель тактовой частоты для SPI, от 0=/2, 1=/4 ....7=/256 
uint8_t DSIZE; // количество бит в кадре от 3=4бита, 4=5бит, .... 31=32бита.
uint8_t FTHLV; // уровень поорга FIFO, количество кадров данных, от 0=1кадр, 1=2кадр ... 15=16кадр
_Bool MASTER_bit; //режим SPI: 0-Slave, 1-Master
_Bool CPOL_bit; //полярность CLK:	0-SCK сигнал когда 0 на idle, 1-SCK сигнал когда 1 на idle
_Bool CPHA_bit; //фаза CLK: 0-захват сигнала по первому фронту CLK, 1-захват сигнала по фторому фронту CLK
_Bool SSOE_bit; //включение аппаратного выхода SS: 0 - выключен, 1-включен	
_Bool SSIOP_bit; //выбор активного уровня SS: 0-низкий уровень это активный SS, 1- высокий уровень это активный SS
_Bool SSOM_bit;	//режим работы выхода SS в MASTER mode
uint8_t MSSI; //отступ от SS начала передачи, значение от 0 до 15 тактов
uint8_t COMM; //режим работы SPI: 0-full_duplex, 1-simplex_transmitter, 2-simplex_receiver, 3-half_duplex
uint16_t TSIZE; //количество кадров в одной посылке (во время активного SS)
_Bool Tx_DMA;// включение потока ДМА на передачу (Tx DMA stream enable): 1- включен, 0- выключен	
_Bool Rx_DMA;// включение потока ДМА на прием (Rx DMA stream enable): 1- включен, 0- выключен

};

extern struct SPI_H7_init SPI_H7;

//-------------------------------------








#endif





