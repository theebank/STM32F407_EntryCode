#include "uart.h"
#include <stdbool.h>
#include <stdlib.h>

#define GPIOAEN				(0x1UL<< 0)
#define GPIODEN				(0x1UL<< 3U)

#define PIN12				(1U<<12)
#define LED_GREEN			PIN12

#define PIN13				(1U<<13)
#define LED_ORANGE			PIN13

#define PIN14				(1U<<14)
#define LED_RED				PIN14

#define PIN15				(1U<<15)
#define LED_BLUE			PIN15

void USART2_IRQHandler(void);
static void USART2_IRQ_callback(void);
bool compareElements(int original[], int testval, int curridx);
void flashLights(void);
void spinLights(void);
void handleLightInput(int curridx);



void toggleLights(){
	GPIOD->ODR ^= LED_GREEN;
	GPIOD->ODR ^= LED_ORANGE;
	GPIOD->ODR ^= LED_RED;
	GPIOD->ODR ^= LED_BLUE;
}
void LightsOn(){
	GPIOD->BSRR |= LED_GREEN;
	GPIOD->BSRR |= LED_ORANGE;
	GPIOD->BSRR |= LED_RED;
	GPIOD->BSRR |= LED_BLUE;
}
void LightsOff(){
	GPIOD->BSRR |= (1U<<28);
	GPIOD->BSRR |= (1U<<29);
	GPIOD->BSRR |= (1U<<30);
	GPIOD->BSRR |= (1U<<31);
}


char key;
int code[] = {0,8,1,0};
int curridx = -1;

int main(void){
	RCC->AHB1ENR |= GPIODEN;

	GPIOD->MODER |= (0x1UL<<24U);
	GPIOD->MODER &=~(1U<<25);

	GPIOD->MODER |= (0x1UL<<26U);
	GPIOD->MODER &=~(1U<<27);

	GPIOD->MODER |= (0x1UL<<28U);
	GPIOD->MODER &=~(1U<<29);

	GPIOD->MODER |= (0x1UL<<30U);
	GPIOD->MODER &=~(1U<<31);

	uart2_rx_interrupt_init();

		while(1)
		{

		}
}
static void USART2_IRQ_callback(void){
	key = USART2->DR;
	int comp = key-'0';
	if(compareElements(code,comp, curridx+1)){
		curridx = curridx +1;
		handleLightInput(curridx);

	}else{
		flashLights();
		curridx = -1;
	}
	for(int i = 0;i<100000;i++);
	if(curridx == 3){
		spinLights();
		curridx = -1;
	}


}
void USART2_IRQHandler(void){
//	check if rxne is set
	if(USART2->SR & SR_RXNE){
		USART2_IRQ_callback();

	}
}

void handleLightInput(int curridx){
	switch (curridx) {
		case 0:
			GPIOD->BSRR |= LED_GREEN;
			break;
		case 1:
			GPIOD->BSRR |= LED_ORANGE;
			break;
		case 2:
			GPIOD->BSRR |= LED_RED;
			break;
		case 3:
			GPIOD->BSRR |= LED_BLUE;
			break;
		default:
			LightsOff();
			break;
		}
}
void flashLights(void){
	for(int j  = 0;j<4;j++){
		LightsOn();
		for(int i = 0;i<100000;i++);
		LightsOff();
		for(int i = 0;i<100000;i++);
	}

}
void spinLights(void){
	for(int j = 0;j<4;j++){
		GPIOD->BSRR |= LED_GREEN;
		for(int i = 0;i<100000;i++);
		LightsOff();
		GPIOD->BSRR |= LED_ORANGE;
		for(int i = 0;i<100000;i++);
		LightsOff();
		GPIOD->BSRR |= LED_RED;
		for(int i = 0;i<100000;i++);
		LightsOff();
		GPIOD->BSRR |= LED_BLUE;
		for(int i = 0;i<100000;i++);
		LightsOff();
	}
}
bool compareElements(int original[], int testval, int curridx){
	if(original[curridx]==testval){
		return true;
	}else{
		return false;
	}
}
