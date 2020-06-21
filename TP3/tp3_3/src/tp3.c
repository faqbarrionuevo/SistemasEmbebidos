/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

//Código correspondiente al punto 3 del TP3


// Inlcusiones
#include "../../tp3_3/inc/tp3.h"         // <= Su propia cabecera

#include <stdio.h>

#include "../../tp3_3/inc/myGpio.h"        // <= Biblioteca propia
#include "sapi_delay.h"
#include "sapi_uart.h"
//#include "sapi_sleep.h"
#include "board.h"

//------------------------------IMPORTANTE-----------------------------------------------------//

//PARA QUE EL CODIGO FUNCIONE SE DEBE DEFINIR EL SIGUIENTE MACRO (SAPI_USE_INTERRUPTS) EN sapi_uart.h
//PARA PODER USAR LAS INTERRUPCIONES UART

//#define SAPI_USE_INTERRUPTS   (HACERLO EN sapi_uart.h)

//------------------------------IMPORTANTE------------------------------------------------------//



//----------------------VARIABLES PARA ELEGIR QUE PUNTO PROBAR-------------------------------//
//Para probar punto A poner puntoa en 1, puntob en 0 y puntoc en 0
//Para probar punto B poner puntoa en 0, puntob en 1 y puntoc en 0
//Para probar punto C poner puntoa en 0, puntob en 1 y puntoc en 1

bool_t puntoa = 1;                          //Sin interrupcion
bool_t puntob = 0;                          //Con interrucpion por recepcion
bool_t puntoc = 0;                          //Con interrupciones y pulsadores

//PUNTO A: 3 CARACTERES PRENDEN Y APAGAN LOS 3 LEDS
//PUNTO B: 3 CARACTERES PRENDEN Y APAGAN LOS 3 LEDS, ESTA VEZ CON INTERRUPCION DE UART_RX
//PUNTO C: 3 CARACTERES PRENDEN Y APAGAN LOS 3 LEDS (CON INTERRUPCION UART_TX), Y ADEMAS ->
//         -> LOS 4 PULSADORES IMPRIMEN 4 CARACTERES DIFERENTES POR TERMINAL SERIE

//---------------------VARIABLES PARA ELEGIR QUE PUNTO PROBAR-------------------------------//


char c;

typedef enum {                //Tipo enumerativo para los estados de un boton
	STATE_BUTTON_UP,
	STATE_BUTTON_DOWN,
	STATE_BUTTON_FALLING,
	STATE_BUTTON_RISING
} buttonState_t;

buttonState_t estadoBoton1;    //Variable para indicar el estado del boton
buttonState_t estadoBoton2;    //Variable para indicar el estado del boton
buttonState_t estadoBoton3;    //Variable para indicar el estado del boton
buttonState_t estadoBoton4;    //Variable para indicar el estado del boton
delay_t actualizarBoton;

void butonNow1(myGpioMap_t boton);         //Funciones para actualizar el estado de los botones
void butonNow2(myGpioMap_t boton);
void butonNow3(myGpioMap_t boton);
void butonNow4(myGpioMap_t boton);
void inicializarBotones();                 //Funcion para inicializar los botones

void onRx(void *noUsado) {                //Funcion que se llamará cuando se interrumpa via UART_RX
	c = uartRxRead(UART_USB);
	printf("Caracter recibido: %c\r\n", c);
}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	myBoardConfig();
	SystemCoreClockUpdate();
	Board_Init();
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	if (puntoc) {
		delayInit(&actualizarBoton, 40);
		inicializarBotones();
	}

	uartConfig(UART_USB, 115200); //Inicializamos UART

	if (puntob) {
		uartCallbackSet(UART_USB, UART_RECEIVE, onRx, NULL); // Seteo un callback al evento de recepcion y habilito su interrupcion
		uartInterrupt(UART_USB, TRUE);                       // Habilito todas las interrupciones de UART_USB
	}

	//Variables donde guardar los datos leidos desde UART
	uint8_t datoLeido = 0;

	// ---------- REPETIR POR SIEMPRE --------------------------

	while (TRUE) {

		if (puntoa) {

			printf("Main menu: \r\n");
			printf("Para encender Led1: Presione A\r\n");
			printf("Para encender Led2: Presione B\r\n");
			printf("Para encender Led3: Presione 3\r\n");
			printf("Para apagar Led1: Presione D\r\n");
			printf("Para apagar Led2: Presione 5\r\n");
			printf("Para apagar Led3: Presione V\r\n");

			while (!uartReadByte(UART_USB, &datoLeido)) {     //Espero hasta que ingresen un dato

			}
		}

		if (puntoc) {
			if (delayRead(&actualizarBoton)) {                //Actualizamos estado de los boton todo el tiempo

						butonNow1(CIAA_BOARD_BUTTON1);

						butonNow2(CIAA_BOARD_BUTTON2);

						butonNow3(CIAA_BOARD_BUTTON3);

						butonNow4(CIAA_BOARD_BUTTON4);

					}
		}

		//Cuando ya llegó el dato

		if (puntob) {
			datoLeido = (uint8_t) c;                //Paso lo que recibí a la variable datoLeido para el switch (asi funciona para punto a b y c)
		}

		if(puntoa){
		uartWriteByte(UART_USB, datoLeido);        // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
		printf("\r\n");
		}



		switch (datoLeido) {

		case 'A':                                   //Prender Led1

			myGpioWrite(CIAA_BOARD_LED1, 1);

			break;
		case 'B':                                   //Prender Led2

			myGpioWrite(CIAA_BOARD_LED2, 1);

			break;
		case '3':                                   //Prender Led3

			myGpioWrite(CIAA_BOARD_LED3, 1);

			break;
		case 'D':                                   //Apagar Led1

			myGpioWrite(CIAA_BOARD_LED1, 0);

			break;
		case '5':                                   //Apagar Led2

			myGpioWrite(CIAA_BOARD_LED2, 0);

			break;
		case 'V':                                   //Apagar Led3

			myGpioWrite(CIAA_BOARD_LED3, 0);

			break;

		default:
			//printf("Caracter no valido\r\n");
			break;

		}

	}

	return 0;
}


void inicializarBotones() {                    //Inicializamos todos los botones en estado alto
	estadoBoton1 = STATE_BUTTON_UP;
	estadoBoton2 = STATE_BUTTON_UP;
	estadoBoton3 = STATE_BUTTON_UP;
	estadoBoton4 = STATE_BUTTON_UP;
}


void butonNow1(myGpioMap_t boton) {             //Procesar estado actual del boton

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

void butonNow2(myGpioMap_t boton) {             //Procesar estado actual del boton

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

		} else {
			estadoBoton2 = STATE_BUTTON_DOWN;
		}

		/* LEAVE */
		if (estadoBoton2 != STATE_BUTTON_RISING) {
			flagRising = 0;

			break;

			default:
			break;

		}

	}

}

void butonNow3(myGpioMap_t boton) {             //Procesar estado actual del boton

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

void butonNow4(myGpioMap_t boton) {             //Procesar estado actual del boton

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





