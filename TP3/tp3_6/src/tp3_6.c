/*==================[inclusions]=============================================*/
#include "sapi.h"        // <= sAPI header

/*==================[declaraciones de funciones externas]====================*/
char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}


void setDacValue( uint8_t dato){

	uint16_t tensiones[10] = {0, 114, 228, 342, 456, 570, 684, 798, 912, 1023};

	switch (dato){

		case '0':
			dacWrite( DAC, tensiones[0]);
			break;
		case '1':
			dacWrite( DAC, tensiones[1]);
			break;
		case '2':
			dacWrite( DAC, tensiones[2]);
			break;
		case '3':
			dacWrite( DAC, tensiones[3]);
			break;
		case '4':
			dacWrite( DAC, tensiones[4]);
			break;
		case '5':
			dacWrite( DAC, tensiones[5]);
			break;
		case '6':
			dacWrite( DAC, tensiones[6]);
			break;
		case '7':
			dacWrite( DAC, tensiones[7]);
			break;
		case '8':
			dacWrite( DAC, tensiones[8]);
			break;
		case '9':
			dacWrite( DAC, tensiones[9]);
			break;
		default:
			break;

	}

}

/*==================[funcion principal]======================================*/
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar UART_USB a 115200 baudios */
   uartConfig( UART_USB, 115200 );

   /* Inicializar AnalogIO */
   adcConfig( ADC_ENABLE ); /* ADC */
   dacConfig( DAC_ENABLE ); /* DAC */

   /* -------------------------------------------- */

   /* Dato recibido por UART */
   uint8_t dato  = 0;

   /* Buffer */
   static char uartBuff[10];

   /* Variable para almacenar el valor leido del ADC CH1 */
   uint16_t muestra = 0;

   /* Variable de delay no bloqueante */
   delay_t delay1;

   /* Inicializar Retardo no bloqueante con tiempo en ms */
   delayConfig( &delay1, 500 );

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

	  // Si se recibe un byte de la UART_USB se guarda en la variable dato.
	  if(  uartReadByte( UART_USB, &dato ) ){

		  // Se setea la tension del DAC de acuerdo al dato.
		  setDacValue(dato);

   	  }

	  // Cada 500ms se lee el valor del ADC y se envía por la UART_USB
	  if ( delayRead( &delay1 ) ){

	           /* Lee la Entrada Analogica AI0 - ADC0 CH1 */
	           muestra = adcRead( CH1 );

	           /* Envía la primer parte del mnesaje a la Uart */
				uartWriteString( UART_USB, "ADC CH1 value: " );

				/* Conversion de muestra entera a ascii con base decimal */
				itoa( muestra, uartBuff, 10 ); /* 10 significa decimal */

				/* Enviar muestra y Enter */
				uartWriteString( UART_USB, uartBuff );
				uartWriteString( UART_USB, ";\r\n" );
	  }

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
