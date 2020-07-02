#include "tp3.h"

#include <stdio.h>

#include "utilities.h"
#include "sapi_delay.h"
#include "sapi_uart.h"
#include "board.h"

/**********************************************************/
// Configuration for this program
#define PUNTO_A 1
#define PUNTO_B 0
/**********************************************************/



static buttonInfo_t buttonState1;
static buttonInfo_t buttonState2;
static buttonInfo_t buttonState3;
static buttonInfo_t buttonState4;

//bool_t receivedDataFromUart(uint8_t* data);

void nullFunc(uint8_t, uint8_t);

static uint8_t data_received;

void onRx(void* not_used);

void uartWriteByteWrapper(uint8_t uart_flag, uint8_t data);

int main(void) {

	// Configuration

	myBoardConfig();
	SystemCoreClockUpdate();
	Board_Init();
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	delay_t waitForButtonTime;
	delayInit(&waitForButtonTime, 40/*ms*/);
	initButtons();
	uartConfig(UART_232, /*baud rate =*/ 115200);
	uartCallbackSet(UART_232, UART_RECEIVE, onRx, NULL);
	uartInterrupt(UART_232, true);


	// Infinite loop

	while (TRUE) {
		if (delayRead(&waitForButtonTime)) {
			processButton(&buttonState1);
			processButton(&buttonState2);
			processButton(&buttonState3);
			processButton(&buttonState4);
		}
	}
	return 0;
}

void initButtons() {
	initButton(&buttonState1, CIAA_BOARD_BUTTON1, '1');
	initButton(&buttonState2, CIAA_BOARD_BUTTON2, '2');
	initButton(&buttonState3, CIAA_BOARD_BUTTON3, '3');
	initButton(&buttonState4, CIAA_BOARD_BUTTON4, '4');
}

void initButton(buttonInfo_t* button_info,
				myGpioMap_t button,
				uint8_t char_to_send) {
	button_info->button_state = STATE_BUTTON_UP;
	button_info->flag_falling = 0;
	button_info->flag_rising = 0;
	button_info->button = button;

	button_info->falling_info.outputDirectionOrFlag = UART_232;
	button_info->falling_info.outputData = char_to_send;
	button_info->falling_info.action = uartWriteByteWrapper;

	button_info->rising_info.outputDirectionOrFlag = 0;
	button_info->rising_info.outputData = 0;
	button_info->rising_info.action = nullFunc;

	button_info->reading_func = myGpioRead;
}

void uartWriteByteWrapper(uint8_t uart_flag, uint8_t data) {
	return uartWriteByte(uart_flag, (char)data);
}


/*bool_t receivedDataFromUart(uint8_t* data) {
	return (uartReadByte(UART_232, data)) ||
		   (uartReadByte(UART_232, data)) ||
		   (uartReadByte(UART_232, data)) ||
		   (uartReadByte(UART_232, data));
}*/

void nullFunc(uint8_t a, uint8_t b){}

void onRx(void* not_used) {
	char char_received = uartRxRead(UART_232);
	switch(char_received) {
		case '1':
			myGpioWrite(CIAA_BOARD_LEDR, 1);
			myGpioWrite(CIAA_BOARD_LED1, 1);
			break;
		case '2':
			myGpioWrite(CIAA_BOARD_LED2, 1);
			myGpioWrite(CIAA_BOARD_LED3, 1);
			break;
		case '3':
			myGpioWrite(CIAA_BOARD_LEDR, 0);
			myGpioWrite(CIAA_BOARD_LED1, 0);
			break;
		case '4':
			myGpioWrite(CIAA_BOARD_LED2, 0);
			myGpioWrite(CIAA_BOARD_LED3, 0);
			break;
	}
}
