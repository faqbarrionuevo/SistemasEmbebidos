/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

//Codigo correspondiente al TP3 punto 2

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

void butonNow(myGpioMap_t boton);
void inicializarBotones();

// Crear varias variables del tipo booleano
bool_t buttonValue = OFF;
bool_t ledValue = OFF;

buttonState_t estadoBoton;    //Variable para indicar el estado del boton

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
			butonNow(CIAA_BOARD_BUTTON1);
			while (estadoBoton != STATE_BUTTON_UP) { //No se irá mientras el botón siga presionado
				butonNow(CIAA_BOARD_BUTTON1);
				if (estadoBoton == STATE_BUTTON_UP) { //Justo la ultima iteración
					printf("F\r\n");
				}
			}
			butonNow(CIAA_BOARD_BUTTON2);
			while (estadoBoton != STATE_BUTTON_UP) {
				butonNow(CIAA_BOARD_BUTTON2);
				if (estadoBoton == STATE_BUTTON_UP) { //Justo la ultima iteración
					printf("A\r\n");
				}
			}
			butonNow(CIAA_BOARD_BUTTON3);
			while (estadoBoton != STATE_BUTTON_UP) {
				butonNow(CIAA_BOARD_BUTTON3);
				if (estadoBoton == STATE_BUTTON_UP) { //Justo la ultima iteración
					printf("C\r\n");
				}
			}
			butonNow(CIAA_BOARD_BUTTON4);
			while (estadoBoton != STATE_BUTTON_UP) {
				butonNow(CIAA_BOARD_BUTTON4);
				if (estadoBoton == STATE_BUTTON_UP) { //Justo la ultima iteración
					printf("U\r\n");
				}
			}
		}

	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}

void inicializarBotones() {
	estadoBoton = STATE_BUTTON_UP;
}

void butonNow(myGpioMap_t boton) {                       //Procesar estado actual del boton

	static bool_t flagFalling = 0;
	static bool_t flagRising = 0;

	static uint8_t contFalling = 0;
	static uint8_t contRising = 0;

	switch (estadoBoton) {

	case STATE_BUTTON_UP:

		if (!myGpioRead(boton)) {
			estadoBoton = STATE_BUTTON_FALLING;
		}
		break;

	case STATE_BUTTON_DOWN:
		/* CHECK TRANSITION CONDITIONS */
		if (myGpioRead(boton)) {
			estadoBoton = STATE_BUTTON_RISING;

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
			estadoBoton = STATE_BUTTON_DOWN;

			if (boton == CIAA_BOARD_BUTTON1) {
				myGpioWrite(CIAA_BOARD_LEDR, 1);
			}
			if (boton == CIAA_BOARD_BUTTON2) {
				myGpioWrite(CIAA_BOARD_LED1, 1);
			}
			if (boton == CIAA_BOARD_BUTTON3) {
				myGpioWrite(CIAA_BOARD_LED2, 1);
			}
			if (boton == CIAA_BOARD_BUTTON4) {
				myGpioWrite(CIAA_BOARD_LED3, 1);
			}

		} else {
			estadoBoton = STATE_BUTTON_UP;
		}

		/* LEAVE */
		if (estadoBoton != STATE_BUTTON_FALLING) {
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
			estadoBoton = STATE_BUTTON_UP;

			if (boton == CIAA_BOARD_BUTTON1) {
				myGpioWrite(CIAA_BOARD_LEDR, 0); //Finalmente se dejo de presionar

			}
			if (boton == CIAA_BOARD_BUTTON2) {
				myGpioWrite(CIAA_BOARD_LED1, 0); //Finalmente se dejo  de presionar
			}
			if (boton == CIAA_BOARD_BUTTON3) {
				myGpioWrite(CIAA_BOARD_LED2, 0); //Finalmente se dejo de presionar
			}
			if (boton == CIAA_BOARD_BUTTON4) {
				myGpioWrite(CIAA_BOARD_LED3, 0); //Finalmente se dejo de presionar
			}

		} else {
			estadoBoton = STATE_BUTTON_DOWN;
		}

		/* LEAVE */
		if (estadoBoton != STATE_BUTTON_RISING) {
			flagRising = 0;
			//myGpioWrite(myLED2, 0);

			break;

			default:
			break;

		}

	}

}



