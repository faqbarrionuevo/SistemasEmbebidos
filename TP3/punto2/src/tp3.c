#include "tp3.h"

#include <stdio.h>

#include "sapi_delay.h"
#include "sapi_uart.h"
#include "board.h"

#include "utilities.h"

static buttonInfo_t buttonState1;
static buttonInfo_t buttonState2;
static buttonInfo_t buttonState3;
static buttonInfo_t buttonState4;


int main(void) {

	// Configuration

	myBoardConfig();
	SystemCoreClockUpdate();
	Board_Init();
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	delay_t waitForButtonTime;
	delayInit(&waitForButtonTime, 40/*ms*/);
	initButtons();
	uartConfig(UART_USB, 115200); //Inicializamos UART

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
	initButton(&buttonState1, CIAA_BOARD_BUTTON1, CIAA_BOARD_LEDR, myGpioWriteWrapper1);
	initButton(&buttonState2, CIAA_BOARD_BUTTON2, CIAA_BOARD_LED1, myGpioWriteWrapper2);
	initButton(&buttonState3, CIAA_BOARD_BUTTON3, CIAA_BOARD_LED2, myGpioWriteWrapper3);
	initButton(&buttonState4, CIAA_BOARD_BUTTON4, CIAA_BOARD_LED3, myGpioWriteWrapper4);
}

void initButton(buttonInfo_t* button_state,
				myGpioMap_t button,
				myGpioMap_t led,
				onButtonPressed_func func) {
	button_state->button_state = STATE_BUTTON_UP;
	button_state->flag_falling = 0;
	button_state->flag_rising = 0;
	button_state->button = button;

	button_state->falling_info.outputDirectionOrFlag = led;
	button_state->falling_info.outputData = 1;
	button_state->falling_info.action = func;

	button_state->rising_info.outputDirectionOrFlag = led;
	button_state->rising_info.outputData = 0;
	button_state->rising_info.action = func;
}

void myGpioWriteWrapper1(uint8_t gpio_map_data, uint8_t out_data) {
	printf("1\r\n");
	return myGpioWrite(
			(myGpioMap_t)gpio_map_data,
			(bool_t)out_data);
}

void myGpioWriteWrapper2(uint8_t gpio_map_data, uint8_t out_data) {
	printf("2\r\n");
	return myGpioWrite(
			(myGpioMap_t)gpio_map_data,
			(bool_t)out_data);
}

void myGpioWriteWrapper3(uint8_t gpio_map_data, uint8_t out_data) {
	printf("3\r\n");
	return myGpioWrite(
			(myGpioMap_t)gpio_map_data,
			(bool_t)out_data);
}

void myGpioWriteWrapper4(uint8_t gpio_map_data, uint8_t out_data) {
	printf("4\r\n");
	return myGpioWrite(
			(myGpioMap_t)gpio_map_data,
			(bool_t)out_data);
}
