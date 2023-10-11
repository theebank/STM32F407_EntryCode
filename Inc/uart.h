#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
/*
 * uart.h
 *
 *  Created on: Oct 11, 2023
 *      Author: TKuma
 */

#ifndef UART_H_
#define UART_H_

#define SR_RXNE				(1U<<5)
#define SR_TXE				(1U<<7)

void uart2_tx_init();
void uart2_write(int ch);
int __io_putchar(int ch);

void uart2_rxtx_init();
char uart2_read();

void uart2_rx_interrupt_init();
void uart2_tx_interrupt_init();


#endif /* UART_H_ */
