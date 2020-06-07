/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones
#include <stdio.h>
#include "../inc/tp2.h"         // <= Su propia cabecera

#include "board.h"

//#include "../../../../libs/lpc_open/lpc_chip_43xx/inc/chip_lpc43xx.h"
#include "myGpio.h"        // <= Biblioteca propia

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   myBoardConfig();
   SystemCoreClockUpdate();
   Board_Init();
   SysTick_Config(SystemCoreClock / TICKRATE_HZ);

   // Crear varias variables del tipo booleano
   bool_t buttonValue = OFF;
   bool_t ledValue    = OFF;
   // Crear variable del tipo tick_t para contar tiempo
   tick_t timeCount   = 0;

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {

      /* Retardo bloqueante durante 100ms */
      
      myDelay( 100 );
      
      /* Si pasaron 10 segundos comienza a funcionar el programa que copia las
         acciones en BOTON al LED. Mientras espera titila el LED.  */
      
      timeCount++;      
      
      if( timeCount == 100 ){ // 100ms * 100 = 10s
         
         while( TRUE ) {
            
            /* Si se presiona CIAA_BOARD_BUTTON, enciende el CIAA_BOARD_LED */

            // Leer pin conectado al boton.
            buttonValue = myGpioRead( CIAA_BOARD_BUTTON );
            // Invertir el valor leido, pues lee un 0 (OFF) con boton
            // presionado y 1 (ON) al liberarla.
            buttonValue = !buttonValue;
            // Escribir el valor leido en el LED correspondiente.
            myGpioWrite( CIAA_BOARD_LED, buttonValue );

            /* Enviar a la salida estandar (UART_DEBUG) el estado del LED */
            
            // Leer el estado del pin conectado al led
            ledValue = myGpioRead( CIAA_BOARD_LED );
            // Chequear si el valor leido es encedido
            if( ledValue == ON ) {
               // Si esta encendido mostrar por UART_USB "LED encendido."
               printf( "LED encendido.\r\n" );
            } else {
               // Si esta apagado mostrar por UART_USB "LED apagado."
               printf( "LED apagado.\r\n" );
            }
            myDelay( 250 );
            
         }
      } else {
         // Intercambiar el valor de CIAA_BOARD_LED
         //myGpioToggle(CIAA_BOARD_LED);
      }
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
