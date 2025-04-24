#include "FSMC.h"

#ifdef STM32F4
//=============================================================
//
void FSMC_init (void)
{
RCC->AHB3ENR |=RCC_AHB3ENR_FSMCEN;
	
FSMC_Bank1->BTCR[0] = 	0 << FSMC_BCR1_CBURSTRW_Pos 	| // write 0 - async 1 - sycnc
												0 << FSMC_BCR1_CPSIZE_Pos 		| // CRAM page size
												0 << FSMC_BCR1_ASYNCWAIT_Pos 	| // Wait signal during asynchronous transfers
												0 << FSMC_BCR1_EXTMOD_Pos 		| // Extended mode enable. Use BWTR register or no
												0 << FSMC_BCR1_WAITEN_Pos 		| // Wait enable bit.
												1 << FSMC_BCR1_WREN_Pos 			| // Write enable bit
												0 << FSMC_BCR1_WAITCFG_Pos 		| // Wait timing configuration. 0: NWAIT signal is active one data cycle
																												// before wait state 1: NWAIT signal is active during wait state
												0 << FSMC_BCR1_WRAPMOD_Pos 		| // Wrapped burst mode support
												0 << FSMC_BCR1_WAITPOL_Pos 		| // Wait signal polarity bit. 0: NWAIT active low. 1: NWAIT active high
												0 << FSMC_BCR1_BURSTEN_Pos 		| // Burst enable bit
												1 << FSMC_BCR1_FACCEN_Pos 		| // Flash access enable
												1 << FSMC_BCR1_MWID_Pos     	| // Memory databus width: 0 = 8b, 1 = 16b
												2 << FSMC_BCR1_MTYP_Pos 			| // Memory type: 0 = SRAM, 1 = CRAM, 2 = NOR
												0 << FSMC_BCR1_MUXEN_Pos 			| // Multiplexing Address/Data
												1 << FSMC_BCR1_MBKEN_Pos			;	// Memory bank enable bit

FSMC_Bank1->BTCR[1] =		0 << FSMC_BTR1_ACCMOD_Pos			| // Access mode 0 = A, 1 = B, 2 = C, 3 = D Use w/EXTMOD bit
												0 << FSMC_BTR1_DATLAT_Pos 		| // Data latency for synchronous NOR Flash memory 0(2CK)...F(17CK)
												1 << FSMC_BTR1_CLKDIV_Pos 		| // for FSMC_CLK signal 1 = HCLK/2, 2 = HCLK/3 ... F= HCLK/16	
												5 << FSMC_BTR1_BUSTURN_Pos 		| // Bus turnaround phase duration 0...F, расстояние между посылками
												5 << FSMC_BTR1_DATAST_Pos 		| // Data-phase duration 1..FF * 2 * HCLK, длительность фазы данных
												1 << FSMC_BTR1_ADDHLD_Pos 		| // Address-hold phase duration 1..F * 2 * HCLK, длительность фазы удержания адреса
												1 << FSMC_BTR1_ADDSET_Pos 		; // Address setup phase duration 0..F * HCLK, длительность фазы настройки адреса
 
  
}




//
//=============================================================
#endif



#ifdef STM32H7
//=============================================================
//
//
//=============================================================
#endif
