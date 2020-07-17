/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/


/*En este codigo haremos uso de las librerias de la sapi */
/*Codigo correspondiente al punto 5 del TP3*/

//                     3V3 -/\/\/\-- A/D -/\/\/\-- 0v

// Inlcusiones
#include "sapi.h"
#include <string.h>

//Funciones
void reverse(char s[]);
void Myitoa(int m, char s[]);

/*-------------------DEFINES----------------------------*/
#define VALOR_DELAY              500

/*--------------Definicion de variables----------------*/
uint16_t muestra = 0;
static char buffer[10];
delay_t mydelay;

int main(void){

  boardConfig();                                 //Configuramos placa

  uartConfig( UART_USB, 115200 );                //Configuramos UART

  adcConfig( ADC_ENABLE );                       //Habilitacion ADC

  delayConfig( &mydelay, VALOR_DELAY );

   while(1) {


      if ( delayRead( &mydelay ) ){

        muestra = adcRead( CH1 );
        uartWriteString( UART_USB, "Valor ADC CH1: " );
        Myitoa(muestra, buffer);


        uartWriteString( UART_USB, buffer );
        uartWriteString( UART_USB, "\r\n" );
      }

   }

   return 0 ;
}

void reverse(char s[]){

 int i, j;
 char c;

 for (i = 0, j = strlen(s) - 1 ; i < j ; i++, j--) {
     c = s[i];
     s[i] = s[j];
     s[j] = c;
 }
}

void Myitoa(int m, char s[]){
   int j, sig;

   if ( (sig = m) < 0 )
       m = -m;
   j = 0;
   do{
       s[j++] = m % 10 + '0';
   } while ( (m /= 10) > 0 );
   if ( sig < 0 )
       s[j++] = '-';
   s[j] = '\0';
   reverse(s);
 }
