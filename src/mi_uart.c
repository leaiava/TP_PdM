/*
 * mi_uart.c
 *
 *  Created on: Aug 5, 2021
 *      Author: lea
 */
#include "mi_uart.h"

void UART_inicializar(void){
	uartInit( UART_USB, UART_VELOCIDAD );
}

bool_t UART_getCmd(cmd_t* command){
	//! Dependencia de sapi.h donde esta uartReadByte
	return uartReadByte( UART_USB, (uint8_t*) command );
}

void UART_sendCmd(cmd_t command){

	uartWriteByte( UART_USB, (const uint8_t) command );
}

void UART_sendPacket(packet_t paquete){
	uint8_t aux;
	aux = (uint8_t) 0x00FF & (paquete.data_CH1 >>8 );
	uartWriteByte( UART_USB, aux);
	aux = (uint8_t) 0x00FF & paquete.data_CH1;
	uartWriteByte( UART_USB, aux);
	aux = (uint8_t) 0x00FF & (paquete.data_CH2 >>8 );
	uartWriteByte( UART_USB, aux);
	aux = (uint8_t) 0x00FF & paquete.data_CH2;
	uartWriteByte( UART_USB, aux);
	aux = (uint8_t) 0x00FF & (paquete.data_CH3 >>8 );
	uartWriteByte( UART_USB, aux);
	aux = (uint8_t) 0x00FF & paquete.data_CH3;
	uartWriteByte( UART_USB, aux);
}
