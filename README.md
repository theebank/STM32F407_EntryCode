# STM32F407 Entry Code application

## Behaviour
If correct code is input into the USART Terminal, Lights will flash in a clockwise pattern, otherwise will flash all 4 lights at once 3 times.

## Design
Designed using Interrupts for the USART and Timer modules
Utilizes Custom driver written for the GPIO Module

## Hardware Required
- STM32F407 Discovery Board

- Choice of USART Connection: Female-Female Jumper Wires OR USB-TTL Serial Adapter with TX RX pin compatibility

## Hardware Setup
- Connect choice of USART connection as shown in STM32F407 Discovery Board User Manual
 
