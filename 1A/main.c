/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Mason Corey, Andrea Anez
 * Section: Thurs. 7-9:50PM
 * Lab: 1A
 */

#include "stm32l476xx.h"
 
void Init() {
	// Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	// Select HSI as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_HSI;
	while((RCC->CFGR & RCC_CFGR_SWS) == 0);
	
	// Enable GPIO Clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	// Initialize Red LED
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE2_1;
	
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT2;
	
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD2;
	
	
	// Initialize Green LED
	GPIOE->MODER |= GPIO_MODER_MODE8_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE8_1;
	
	GPIOE->OTYPER &= ~GPIO_OTYPER_OT8;
	
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD8;
	
	// Initialize Joystick
	GPIOA->MODER &= ~GPIO_MODER_MODE0;
	GPIOA->MODER &= ~GPIO_MODER_MODE1;
	GPIOA->MODER &= ~GPIO_MODER_MODE2;
	GPIOA->MODER &= ~GPIO_MODER_MODE3;
	GPIOA->MODER &= ~GPIO_MODER_MODE5;
	
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD1_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD5_1;
	
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD1_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD2_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD3_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5_0;
	
}
 
int main() {
	// Initialization
	Init();
	
	// Polling to Check for Button Presses
	while(1)	{
		//Check if PA0, PA1, PA2, PA3, or PA5 are on. If so, toggle things
		if((GPIOA->IDR & GPIO_IDR_IDR_0) == GPIO_IDR_IDR_0)	{
			//If center button is on, Toggle both LEDs
			GPIOB->ODR ^= GPIO_ODR_OD2; //Toggle red LED
			GPIOE->ODR ^= GPIO_ODR_OD8; //Toggle green LED
		}
		if((GPIOA->IDR & GPIO_IDR_IDR_1) == GPIO_IDR_IDR_1)	{
			//If left button is on, Toggle the green LED
			GPIOE->ODR ^= GPIO_ODR_OD8; //Toggle green LED
		}
		if((GPIOA->IDR & GPIO_IDR_IDR_2) == GPIO_IDR_IDR_2)	{
			//If right button is on, Toggle the red LED
			GPIOB->ODR ^= GPIO_ODR_OD2; //Toggle red LED
		}
		if((GPIOA->IDR & GPIO_IDR_IDR_3) == GPIO_IDR_IDR_3)	{
			//If up button is on, Set both LEDs to HIGH
			GPIOB->ODR |= GPIO_ODR_OD2; //Set red LED to HIGH
			GPIOE->ODR |= GPIO_ODR_OD8; //Set green LED to HIGH
		}
		if((GPIOA->IDR & GPIO_IDR_IDR_5) == GPIO_IDR_IDR_5)	{
			//If down button is on, Set both LEDs to LOW
			GPIOB->ODR &= ~GPIO_ODR_OD2; //Set red LED to LOW
			GPIOE->ODR &= ~GPIO_ODR_OD8; //Set green LED to LOW
		}
	}
	
	return 0;
}
