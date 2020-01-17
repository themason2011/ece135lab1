/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Mason Corey, Andrea Anez
 * Section: Thurs. 7-9:50PM
 * Lab: 1B
 */

#include "LED.h"

void LED_Init(void) {
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
}

void Red_LED_Off(void) {
	GPIOB->ODR &= ~GPIO_ODR_OD2; //Set red LED to LOW
}

void Red_LED_On(void) {
	GPIOB->ODR |= GPIO_ODR_OD2; //Set red LED to HIGH
}

void Red_LED_Toggle(void){
	GPIOB->ODR ^= GPIO_ODR_OD2; //Toggle red LED
}

void Green_LED_Off(void) {
	GPIOE->ODR &= ~GPIO_ODR_OD8; //Set green LED to LOW
}

void Green_LED_On(void) {
	GPIOE->ODR |= GPIO_ODR_OD8; //Set green LED to HIGH
}

void Green_LED_Toggle(void) {
	GPIOE->ODR ^= GPIO_ODR_OD8; //Toggle green LED
}
