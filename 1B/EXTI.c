/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Mason Corey, Andrea Anez
 * Section: Thurs. 7-9:50PM
 * Lab: 1B
 */

#include "EXTI.h"
#include "LED.h"

void EXTI_Init(void) {
	// Initialize Joystick
	GPIOA->MODER &= ~GPIO_MODER_MODE0;
	GPIOA->MODER &= ~GPIO_MODER_MODE1;
	GPIOA->MODER &= ~GPIO_MODER_MODE2;
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD1_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_1;
	
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2_0;
	
	// Configure SYSCFG EXTI (YO I'M NOT SURE IF THIS IS THE RIGHT WAY TO DO THIS ASK THE TA)
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;
	
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;
	
	// Configure EXTI Trigger
	EXTI->FTSR1 |= EXTI_FTSR1_FT0;
	
	EXTI->FTSR1 |= EXTI_FTSR1_FT1;
	
	EXTI->FTSR1 |= EXTI_FTSR1_FT2;
	
	// Enable EXTI
	EXTI->IMR1 |= EXTI_IMR1_IM0;
	
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	
	// Configure and Enable in NVIC
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 0);
	
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_SetPriority(EXTI1_IRQn, 0);
	
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_SetPriority(EXTI2_IRQn, 0);

}

// Write Interrupt Handlers (look in startup_stm32l476xx.s to find the 
// interrupt handler names that you should use)
void EXTI0_IRQHandler()	{
	// Clear interrupt pending bit
	EXTI->PR1 |= EXTI_PR1_PIF0;
	// Define behavior that occurs when interrupt occurs
	Green_LED_Toggle();
	Red_LED_Toggle();
}

void EXTI1_IRQHandler()	{
	// Clear interrupt pending bit
	EXTI->PR1 |= EXTI_PR1_PIF1;
	// Define behavior that occurs when interrupt occurs
	Green_LED_Toggle();
}

void EXTI2_IRQHandler()	{
	// Clear interrupt pending bit
	EXTI->PR1 |= EXTI_PR1_PIF2;
	// Define behavior that occurs when interrupt occurs
	Red_LED_Toggle();
}

void ExampleInterruptHandler(void) {
	// Clear interrupt pending bit
	
	// Define behavior that occurs when interrupt occurs
}