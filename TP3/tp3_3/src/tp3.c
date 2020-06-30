/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

//Codigo correspondiente al punto 3 del TP3


// Inlcusiones
#include "../../tp3_3/inc/tp3.h"         // <= Su propia cabecera

#include <stdio.h>

#include "../../tp3_3/inc/myGpio.h"        // <= Biblioteca propia
#include "sapi_delay.h"
#include "sapi_uart.h"
#include "sapi_sleep.h"
#include "board.h"

//------------------------------IMPORTANTE-----------------------------------------------------//

//PARA QUE EL CODIGO FUNCIONE SE DEBE DEFINIR EL SIGUIENTE MACRO (SAPI_USE_INTERRUPTS) EN sapi_uart.h
//PARA PODER USAR LAS INTERRUPCIONES UART

//#define SAPI_USE_INTERRUPTS   (HACERLO EN sapi_uart.h)

//------------------------------IMPORTANTE------------------------------------------------------//



//----------------------VARIABLES PARA ELEGIR QUE PUNTO PROBAR-------------------------------//
//Para probar punto A poner PUNTO_A en 1, PUNTO_B en 0 y PUNTO_C en 0
//Para probar punto B poner PUNTO_A en 0, PUNTO_B en 1 y PUNTO_C en 0
//Para probar punto C poner PUNTO_A en 0, PUNTO_B en 0 y PUNTO_C en 1

#define  PUNTO_A  		0                    // Sin interrupcion
#define  PUNTO_B  		0                    // Con interrucpion por recepcion
#define  PUNTO_C        1                    // Con interrupciones y pulsadores

//PUNTO A: 3 CARACTERES PRENDEN Y APAGAN LOS 3 LEDS
//PUNTO B: 3 CARACTERES PRENDEN Y APAGAN LOS 3 LEDS, ESTA VEZ CON INTERRUPCION DE UART_RX
//PUNTO C: 3 CARACTERES PRENDEN Y APAGAN LOS 3 LEDS (CON INTERRUPCION UART_TX), Y ADEMAS ->
//         -> LOS 4 PULSADORES IMPRIMEN 4 CARACTERES DIFERENTES POR TERMINAL SERIE

//---------------------VARIABLES PARA ELEGIR QUE PUNTO PROBAR-------------------------------//

static char callback_char;

static const char newline[] = "\n";

buttonStateStruct estadoBoton1;    //Variable para indicar el estado del boton
buttonStateStruct estadoBoton2;    //Variable para indicar el estado del boton
buttonStateStruct estadoBoton3;    //Variable para indicar el estado del boton
buttonStateStruct estadoBoton4;    //Variable para indicar el estado del boton
delay_t actualizarBoton;

void onRxCallback(void *noUsado) {                //Funcion que se llamara cuando se interrumpa via UART_RX
	callback_char = uartRxRead(UART_USB);
	printf("Caracter recibido: %c%s", callback_char, newline);
}

void printMenu() {
	printf("%s %s", "Main menu:", newline);
	printf("%s %s", "Para encender Led1: Presione A", newline);
	printf("%s %s", "Para encender Led2: Presione B", newline);
	printf("%s %s", "Para encender Led3: Presione 3", newline);
	printf("%s %s", "Para apagar Led1: Presione D", newline);
	printf("%s %s", "Para apagar Led2: Presione 5", newline);
	printf("%s %s", "Para apagar Led3: Presione V", newline);
}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	myBoardConfig();
	SystemCoreClockUpdate();
	Board_Init();
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	if (PUNTO_C) {
		delayInit(&actualizarBoton, 40);
		inicializarBotones();
	}

	uartConfig(UART_USB, 115200); //Inicializamos UART

	if (PUNTO_B || PUNTO_C) {
		uartCallbackSet(UART_USB, UART_RECEIVE, onRxCallback, NULL); // Seteo un callback al evento de recepcion y habilito su interrupcion
		uartInterrupt(UART_USB, TRUE);                       		 // Habilito todas las interrupciones de UART_USB
	}

	//Variables donde guardar los datos leidos desde UART
	uint8_t datoLeido = 0;

	// ---------- REPETIR POR SIEMPRE --------------------------

	while (TRUE) {
		if (PUNTO_A) {
			printMenu();
			while (!uartReadByte(UART_USB, &datoLeido)) {     //Espero hasta que ingresen un dato
			}
		}

		if (PUNTO_C) {
			if (delayRead(&actualizarBoton)) {                //Actualizamos estado de los botones todo el tiempo
						processButton(&estadoBoton1);
						processButton(&estadoBoton2);
						processButton(&estadoBoton3);
						processButton(&estadoBoton4);

					}
		}

		//Cuando ya llego el dato

		if (PUNTO_B || PUNTO_C) {
			datoLeido = (uint8_t) callback_char;                //Paso lo que recibi a la variable datoLeido para el switch (asi funciona para punto a b y c)
		}

		if(PUNTO_A){
		uartWriteByte(UART_USB, datoLeido);        // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
		printf("\r\n");
		}

		switch (datoLeido) {
			case 'A':                                   //Prender Led1
			case 'a':
				myGpioWrite(CIAA_BOARD_LED1, 1);
				break;
			case 'B':                                   //Prender Led2
			case 'b':
				myGpioWrite(CIAA_BOARD_LED2, 1);
				break;
			case '3':                                   //Prender Led3
				myGpioWrite(CIAA_BOARD_LED3, 1);
				break;
			case 'D':    								//Apagar Led1
			case 'd':
				myGpioWrite(CIAA_BOARD_LED1, 0);
				break;
			case '5':                                   //Apagar Led2
				myGpioWrite(CIAA_BOARD_LED2, 0);
				break;
			case 'V':                                   //Apagar Led3
			case 'v':
				myGpioWrite(CIAA_BOARD_LED3, 0);
				break;
			default:
				//printf("Caracter no valido\r\n");
				break;
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





