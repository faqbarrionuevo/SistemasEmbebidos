/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

//Código correspondiente al punto 4 del TP3
// Inlcusiones
#include "../../tp3_4/inc/tp3.h"         // <= Su propia cabecera

#include <stdio.h>

#include "sapi_uart.h"
#include "sapi_board.h"
#include "sapi_pwm.h"

//----------------------VARIABLES PARA ELEGIR QUE PUNTO PROBAR-------------------------------//
//Para probar punto A poner PUNTO_B en 0
//Para probar punto B poner PUNTO_B en 1

#define PUNTO_B  1                        //Subir y bajar brillo

//PUNTO A: 3 3 LEDS PRENDIDOS CON DIFERENTE BRILLO
//PUNTO B: 3 3 LEDS PRENDIDOS CON DIFERENTE BRILLO Y CARACTERES PARA AUMENTAR Y DISMINUIR EL MISMO

//---------------------VARIABLES PARA ELEGIR QUE PUNTO PROBAR-------------------------------//

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();
	SystemCoreClockUpdate();
	Board_Init();
	uartConfig(UART_USB, 115200); //Inicializamos UART

	//Variables donde guardar los datos leidos desde UART
	uint8_t datoLeido = 0;

	bool_t valor = 0;

	//Valores iniciales
	uint8_t dutyCycle1 = 10;       /* 0 a 255 */
	uint16_t dutyCycle2 = 100;
	uint16_t dutyCycle3 = 255;

	uint8_t pwmVal = 0;            /* 0 a 255 */

	/* Configurar PWM */
	valor = pwmConfig(0, PWM_ENABLE);                  //Configuro como ENEABLE

	valor = pwmConfig(PWM7, PWM_ENABLE_OUTPUT);        //LED1
	valor = pwmConfig(PWM8, PWM_ENABLE_OUTPUT);        //LED2
	valor = pwmConfig(PWM9, PWM_ENABLE_OUTPUT);        //LED3

	// ---------- REPETIR POR SIEMPRE --------------------------

	while (TRUE) {

		/* Usar PWM */
		valor = pwmWrite(PWM7, dutyCycle1);                //LED1
		pwmVal = pwmRead(PWM7);
		pwmWrite(PWM7, pwmVal);

		valor = pwmWrite(PWM8, dutyCycle2);                //LED2
		pwmVal = pwmRead(PWM8);
		pwmWrite(PWM8, pwmVal);

		valor = pwmWrite(PWM9, dutyCycle3);                //LED3
		pwmVal = pwmRead(PWM9);
		pwmWrite(PWM9, pwmVal);

		if (PUNTO_B) {

			printf("Main menu: \r\n");
			printf("Para aumentar brillo del Led1: Presione A\r\n");
			printf("Para aumentar brillo del Led2: Presione B\r\n");
			printf("Para aumentar brillo del Led3: Presione 3\r\n");
			printf("Para disminuir brillo del Led1: Presione D\r\n");
			printf("Para disminuir brillo del Led2: Presione 5\r\n");
			printf("Para disminuir brillo del Led3: Presione V\r\n");

			while (!uartReadByte(UART_USB, &datoLeido)) { //Espero hasta que ingresen un dato

			}

			//Cuando ya llegó el dato

			uartWriteByte(UART_USB, datoLeido); // Se reenvia el dato a la UART_USB realizando un eco de lo que llega
			printf("\r\n");

			switch (datoLeido) {

			case 'A':                                   //Prender Led1

				if (dutyCycle1 == MAX_DUTY)
					printf("Brillo al maximo\r\n");
				else
					dutyCycle1++;

				break;
			case 'B':                                   //Prender Led2

				if (dutyCycle2 == MAX_DUTY)
					printf("Brillo al maximo\r\n");
				else
					dutyCycle2++;

				break;
			case '3':                                   //Prender Led3

				if (dutyCycle3 == MAX_DUTY)
					printf("Brillo al maximo\r\n");
				else
					dutyCycle3++;

				break;
			case 'D':                                   //Apagar Led1

				if (dutyCycle1 == MIN_DUTY)
					printf("Brillo al minimo\r\n");
				else
					dutyCycle1--;

				break;
			case '5':                                   //Apagar Led2

				if (dutyCycle2 == MIN_DUTY)
					printf("Brillo al minimo\r\n");
				else
					dutyCycle2--;

				break;
			case 'V':                                   //Apagar Led3

				if (dutyCycle3 == MIN_DUTY)
					printf("Brillo al minimo\r\n");
				else
					dutyCycle3--;

				break;

			default:
				printf("Caracter no valido\r\n");
				break;

			}
		}

	}

	return 0;
}


