/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

#ifndef _APP_H_
#define _APP_H_

/*==================[inclusiones]============================================*/
#include "myGpio.h"

/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[tipos de datos declarados por el usuario]===============*/

#define CIAA_BOARD_BUTTON1 myTEC1
#define CIAA_BOARD_LEDR myLEDR

#define CIAA_BOARD_BUTTON2 myTEC2
#define CIAA_BOARD_LED1 myLED1

#define CIAA_BOARD_BUTTON3 myTEC3
#define CIAA_BOARD_LED2 myLED2

#define CIAA_BOARD_BUTTON4 myTEC4
#define CIAA_BOARD_LED3 myLED3


/*==================[declaraciones de datos externos]========================*/
typedef enum {
	STATE_BUTTON_UP,
	STATE_BUTTON_DOWN,
	STATE_BUTTON_FALLING,
	STATE_BUTTON_RISING
} buttonState_t;

typedef struct {
	buttonState_t button_state;
	bool_t flag_falling;
	bool_t flag_rising;
	myGpioMap_t button;
	myGpioMap_t led;
} buttonStateStruct;

/*==================[declaraciones de funciones externas]====================*/
void processButton(buttonStateStruct* button);
void inicializarBotones();
void inicializarBoton(buttonStateStruct* button_state, myGpioMap_t button, myGpioMap_t led);

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _APP_H_ */
