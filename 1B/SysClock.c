/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Mason Corey, Andrea Anez
 * Section: Thurs. 7-9:50PM
 * Lab: 1B
 */

#include "SysClock.h"

void System_Clock_Init(void) {
	// Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	// Select HSI as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while((RCC->CFGR & RCC_CFGR_SWS) == 0);
}
