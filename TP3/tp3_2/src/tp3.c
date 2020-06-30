/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

//Codigo correspondiente al punto 2 del TP3

// Inlcusiones
#include "../../tp3_2/inc/tp3.h"         // <= Su propia cabecera

#include <stdio.h>

#include "../../tp3_2/inc/myGpio.h"        // <= Biblioteca propia
#include "sapi_delay.h"
#include "sapi_uart.h"
#include "board.h"

static buttonStateStruct estadoBoton1;    //Variable para indicar el estado del boton 1
static buttonStateStruct estadoBoton2;    //Variable para indicar el estado del boton 2
static buttonStateStruct estadoBoton3;    //Variable para indicar el estado del boton 3
static buttonStateStruct estadoBoton4;    //Variable para indicar el estado del boton 4

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {

	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	myBoardConfig();
	SystemCoreClockUpdate();
	Board_Init();
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	delay_t actualizarBoton;
	delayInit(&actualizarBoton, 40);
	inicializarBotones();
	uartConfig(UART_USB, 115200); //Inicializamos UART

	// ---------- REPETIR POR SIEMPRE --------------------------

	while (TRUE) {

		// Actualizo botones cada actualizarBoton
		if (delayRead(&actualizarBoton)) {
			processButton(&estadoBoton1);
			processButton(&estadoBoton2);
			processButton(&estadoBoton3);
			processButton(&estadoBoton4);
		}

	}

	return 0;
}

void processButton(buttonStateStruct* button) {           //Procesar estado actual del boton

	switch (button->button_state) {

	case STATE_BUTTON_UP:

		if (!myGpioRead(button->button)) {
			button->button_state = STATE_BUTTON_FALLING;
		}
		break;

	case STATE_BUTTON_DOWN:
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(button->button)) {
			button->button_state = STATE_BUTTON_RISING;

		}
		break;

	case STATE_BUTTON_FALLING:
		/* ENTRY */
		if (button->flag_falling == 0) {
			button->flag_falling = 1;
			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (!myGpioRead(button->button)) {
			button->button_state = STATE_BUTTON_DOWN;
			myGpioWrite(button->led, 1);
			printf("F\r\n");

		} else {
			button->button_state = STATE_BUTTON_UP;
		}

		/* LEAVE */
		if (button->button_state != STATE_BUTTON_FALLING) {
			button->flag_falling = 0;
		}
		break;

	case STATE_BUTTON_RISING:
		/* ENTRY */
		if (button->flag_rising == 0) {
			button->flag_rising = 1;

			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(button->button)) {
			button->button_state = STATE_BUTTON_UP;
			myGpioWrite(button->led, 0); //Finalmente se dejó de presionar

		} else {
			button->button_state = STATE_BUTTON_DOWN;
		}

		/* LEAVE */
		if (button->button_state != STATE_BUTTON_RISING) {
			button->flag_rising = 0;

			break;

			default:
			break;

		}

	}

}

void inicializarBotones() {
	inicializarBoton(&estadoBoton1, CIAA_BOARD_BUTTON1, CIAA_BOARD_LEDR);
	inicializarBoton(&estadoBoton2, CIAA_BOARD_BUTTON2, CIAA_BOARD_LED1);
	inicializarBoton(&estadoBoton3, CIAA_BOARD_BUTTON3, CIAA_BOARD_LED2);
	inicializarBoton(&estadoBoton4, CIAA_BOARD_BUTTON4, CIAA_BOARD_LED3);
}

void inicializarBoton(buttonStateStruct* button_state, myGpioMap_t button, myGpioMap_t led) {
	button_state->button_state = STATE_BUTTON_UP;
	button_state->flag_falling = 0;
	button_state->flag_rising = 0;
	button_state->button = button;
	button_state->led = led;
}
