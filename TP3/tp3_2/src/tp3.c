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

//#include "../../../../libs/lpc_open/lpc_chip_43xx/inc/chip_lpc43xx.h"

typedef enum {
	STATE_BUTTON_UP,
	STATE_BUTTON_DOWN,
	STATE_BUTTON_FALLING,
	STATE_BUTTON_RISING
} buttonState_t;

void butonNow1(myGpioMap_t boton);
void butonNow2(myGpioMap_t boton);
void butonNow3(myGpioMap_t boton);
void butonNow4(myGpioMap_t boton);
void inicializarBotones();

buttonState_t estadoBoton1;    //Variable para indicar el estado del boton
buttonState_t estadoBoton2;    //Variable para indicar el estado del boton
buttonState_t estadoBoton3;    //Variable para indicar el estado del boton
buttonState_t estadoBoton4;    //Variable para indicar el estado del boton

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

			butonNow1(CIAA_BOARD_BUTTON1);

			butonNow2(CIAA_BOARD_BUTTON2);

			butonNow3(CIAA_BOARD_BUTTON3);

			butonNow4(CIAA_BOARD_BUTTON4);
		}

	}

	return 0;
}

void butonNow1(myGpioMap_t boton) {           //Procesar estado actual del boton

	static bool_t flagFalling = 0;
	static bool_t flagRising = 0;

	switch (estadoBoton1) {

	case STATE_BUTTON_UP:

		if (!myGpioRead(boton)) {
			estadoBoton1 = STATE_BUTTON_FALLING;
		}
		break;

	case STATE_BUTTON_DOWN:
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton1 = STATE_BUTTON_RISING;

		}
		break;

	case STATE_BUTTON_FALLING:
		/* ENTRY */
		if (flagFalling == 0) {
			flagFalling = 1;
			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (!myGpioRead(boton)) {
			estadoBoton1 = STATE_BUTTON_DOWN;
			myGpioWrite(CIAA_BOARD_LEDR, 1);
			printf("F\r\n");

		} else {
			estadoBoton1 = STATE_BUTTON_UP;
		}

		/* LEAVE */
		if (estadoBoton1 != STATE_BUTTON_FALLING) {
			flagFalling = 0;
		}
		break;

	case STATE_BUTTON_RISING:
		/* ENTRY */
		if (flagRising == 0) {
			flagRising = 1;

			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton1 = STATE_BUTTON_UP;
			myGpioWrite(CIAA_BOARD_LEDR, 0); //Finalmente se dejó de presionar

		} else {
			estadoBoton1 = STATE_BUTTON_DOWN;
		}

		/* LEAVE */
		if (estadoBoton1 != STATE_BUTTON_RISING) {
			flagRising = 0;

			break;

			default:
			break;

		}

	}

}

void butonNow2(myGpioMap_t boton) {           //Procesar estado actual del boton

	static bool_t flagFalling = 0;
	static bool_t flagRising = 0;

	switch (estadoBoton2) {

	case STATE_BUTTON_UP:

		if (!myGpioRead(boton)) {
			estadoBoton2 = STATE_BUTTON_FALLING;
		}
		break;

	case STATE_BUTTON_DOWN:
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton2 = STATE_BUTTON_RISING;

		}
		break;

	case STATE_BUTTON_FALLING:
		/* ENTRY */
		if (flagFalling == 0) {
			flagFalling = 1;
			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (!myGpioRead(boton)) {
			estadoBoton2 = STATE_BUTTON_DOWN;
			myGpioWrite(CIAA_BOARD_LED1, 1);
			printf("A\r\n");

		} else {
			estadoBoton2 = STATE_BUTTON_UP;
		}

		/* LEAVE */
		if (estadoBoton2 != STATE_BUTTON_FALLING) {
			flagFalling = 0;
		}
		break;

	case STATE_BUTTON_RISING:
		/* ENTRY */
		if (flagRising == 0) {
			flagRising = 1;

			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton2 = STATE_BUTTON_UP;
			myGpioWrite(CIAA_BOARD_LED1, 0); //Finalmente se dejó de presionar

		} else {
			estadoBoton2 = STATE_BUTTON_DOWN;
		}

		/* LEAVE */
		if (estadoBoton2 != STATE_BUTTON_RISING) {
			flagRising = 0;
			//myGpioWrite(myLED2, 0);

			break;

			default:
			break;

		}

	}

}

void butonNow3(myGpioMap_t boton) {           //Procesar estado actual del boton

	static bool_t flagFalling = 0;
	static bool_t flagRising = 0;

	switch (estadoBoton3) {

	case STATE_BUTTON_UP:

		if (!myGpioRead(boton)) {
			estadoBoton3 = STATE_BUTTON_FALLING;
		}
		break;

	case STATE_BUTTON_DOWN:
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton3 = STATE_BUTTON_RISING;

		}
		break;

	case STATE_BUTTON_FALLING:
		/* ENTRY */
		if (flagFalling == 0) {
			flagFalling = 1;
			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (!myGpioRead(boton)) {
			estadoBoton3 = STATE_BUTTON_DOWN;
			myGpioWrite(CIAA_BOARD_LED2, 1);
			printf("C\r\n");

		} else {
			estadoBoton3 = STATE_BUTTON_UP;
		}

		/* LEAVE */
		if (estadoBoton3 != STATE_BUTTON_FALLING) {
			flagFalling = 0;
		}
		break;

	case STATE_BUTTON_RISING:
		/* ENTRY */
		if (flagRising == 0) {
			flagRising = 1;

			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton3 = STATE_BUTTON_UP;
			myGpioWrite(CIAA_BOARD_LED2, 0); //Finalmente se dejó de presionar

		} else {
			estadoBoton3 = STATE_BUTTON_DOWN;
		}

		/* LEAVE */
		if (estadoBoton3 != STATE_BUTTON_RISING) {
			flagRising = 0;

			break;

			default:
			break;

		}

	}

}

void butonNow4(myGpioMap_t boton) {           //Procesar estado actual del boton

	static bool_t flagFalling = 0;
	static bool_t flagRising = 0;

	switch (estadoBoton4) {

	case STATE_BUTTON_UP:

		if (!myGpioRead(boton)) {
			estadoBoton4 = STATE_BUTTON_FALLING;
		}
		break;

	case STATE_BUTTON_DOWN:
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton4 = STATE_BUTTON_RISING;

		}
		break;

	case STATE_BUTTON_FALLING:
		/* ENTRY */
		if (flagFalling == 0) {
			flagFalling = 1;
			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (!myGpioRead(boton)) {
			estadoBoton4 = STATE_BUTTON_DOWN;
			myGpioWrite(CIAA_BOARD_LED3, 1);
			printf("U\r\n");

		} else {
			estadoBoton4 = STATE_BUTTON_UP;
		}

		/* LEAVE */
		if (estadoBoton4 != STATE_BUTTON_FALLING) {
			flagFalling = 0;
		}
		break;

	case STATE_BUTTON_RISING:
		/* ENTRY */
		if (flagRising == 0) {
			flagRising = 1;

			break;
		}
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton4 = STATE_BUTTON_UP;
			myGpioWrite(CIAA_BOARD_LED3, 0); //Finalmente se dejó de presionar

		} else {
			estadoBoton4 = STATE_BUTTON_DOWN;
		}

		/* LEAVE */
		if (estadoBoton4 != STATE_BUTTON_RISING) {
			flagRising = 0;

			break;

			default:
			break;

		}

	}

}

void inicializarBotones() {
	estadoBoton1 = STATE_BUTTON_UP;
	estadoBoton2 = STATE_BUTTON_UP;
	estadoBoton3 = STATE_BUTTON_UP;
	estadoBoton4 = STATE_BUTTON_UP;
}
