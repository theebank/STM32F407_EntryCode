/*
 * timer.c
 *
 *  Created on: Oct 11, 2023
 *      Author: TKuma
 */



#include "stm32f4xx.h"


#define TIM2EN		(1U<<0)
#define CR1_EN		(1U<<0)

#define DIER_UIE	(1U<<0)


void tim2_1hz_interrupt_init(void){
//	enable clock access
	RCC->APB1ENR |= TIM2EN;
//set prescaler value
	TIM2->PSC = 1600 - 1;

//	set autoreload value
	TIM2->ARR = 10000 - 1;
//	clear counter
	TIM2->CNT = 0;
//	enable timer
	TIM2->CR1 |= CR1_EN;

//	enable tim interrupt
	TIM2->DIER |= DIER_UIE;
//	enable timer interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);

}
void tim2_1hz_init(){
//	enable clock access
	RCC->APB1ENR |= TIM2EN;
//set prescaler value
	TIM2->PSC = 1600 - 1;

//	set autoreload value
	TIM2->ARR = 10000 - 1;
//	clear counter
	TIM2->CNT = 0;
//	enable timer
	TIM2->CR1 |= CR1_EN;

}

