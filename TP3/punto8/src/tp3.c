#include "tp3.h"

#include <stdio.h>

#include "sapi_delay.h"
#include "sapi_uart.h"
#include "board.h"

void onRx232(void* not_used);
void onRxUSB(void* not_used);

int main(void) {

	// Configuration

	myBoardConfig();
	SystemCoreClockUpdate();
	Board_Init();
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	uartConfig(UART_232, /*baud rate =*/ 115200);
	uartConfig(UART_USB, /*baud rate =*/ 115200);
	uartCallbackSet(UART_232, UART_RECEIVE, onRx232, NULL);
	uartCallbackSet(UART_USB, UART_RECEIVE, onRxUSB, NULL);
	uartInterrupt(UART_232, true);
	uartInterrupt(UART_USB, true);


	// Infinite loop

	while (TRUE) {
		// Wait for terminal to write and receive echo.
	}
	return 0;
}

void onRx232(void* not_used) {
	char char_received = uartRxRead(UART_232);
	uartWriteByte(UART_USB, char_received);
}

void onRxUSB(void* not_used) {
	char char_received = uartRxRead(UART_USB);
	uartWriteByte(UART_232, char_received);
	printf("%c\r\n", char_received);
}
