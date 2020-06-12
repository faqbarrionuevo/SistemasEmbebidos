/*============================================================================
 * Autor: Barrionuevo Facundo, Centofanti Ezequiel, Scheinkerman Lucas
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones
#include <stdio.h>
#include "../inc/tp2.h"         // <= Su propia cabecera
#include "sapi_delay.h"
#include "board.h"

//#include "../../../../libs/lpc_open/lpc_chip_43xx/inc/chip_lpc43xx.h"
#include "myGpio.h"        // <= Biblioteca propia

//Defines para la compilación condicional
#define TP2_1 (1)

#define TP2_2 (2)

#define TP2_3 (3)

#define TEST (TP2_1) //Aqui debe ir el numero de TP que queremos compilar / probar

#if (TEST == TP2_1)    //Entre este if y el #endif va el codigo correspodiente a TP2_1

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
      
      delay( 100 );
      
      /* Si pasaron 10 segundos comienza a funcionar el programa que copia las
         acciones en BOTON al LED. */
      
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
            delay( 250 );
            
         }
      } else {
         // Intercambiar el valor de CIAA_BOARD_LED
         myGpioToggle(CIAA_BOARD_LED);
      }
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

#endif

#if (TEST == TP2_2)

//Acá iría el codigo de TP2_2
//En este codigo se prueban las 3 funciones pedidas en TP2_1, por eso acá no hay código

#endif

#if (TEST == TP2_3)

//Acá iría el codigo de TP2_3
//En este codigo se prueban las 3 funciones pedidas en TP2_1, por eso acá no hay código

#endif



