/*
 * tp3.h
 *
 *  Created on: Jul 1, 2020
 *      Author: lucasjsch
 */

#ifndef EXAMPLES_C_PROJECTS_TP3_TP3_7_INC_TP3_H_
#define EXAMPLES_C_PROJECTS_TP3_TP3_7_INC_TP3_H_

#include "myGpio.h"
#include "utilities.h"

/*==================[Macros]====================*/

#define CIAA_BOARD_BUTTON1 myTEC1
#define CIAA_BOARD_LEDR myLEDR

#define CIAA_BOARD_BUTTON2 myTEC2
#define CIAA_BOARD_LED1 myLED1

#define CIAA_BOARD_BUTTON3 myTEC3
#define CIAA_BOARD_LED2 myLED2

#define CIAA_BOARD_BUTTON4 myTEC4
#define CIAA_BOARD_LED3 myLED3


typedef uint8_t bool_t;

/*==================[Tipos de datos]====================*/


/*==================[declaraciones de funciones]====================*/
void initButtons();
void initButton(buttonInfo_t* button_state,
				myGpioMap_t button,
				myGpioMap_t led,
				onButtonPressed_func out_data);

void myGpioWriteWrapper1(uint8_t gpio_map_data, uint8_t out_data);
void myGpioWriteWrapper2(uint8_t gpio_map_data, uint8_t out_data);
void myGpioWriteWrapper3(uint8_t gpio_map_data, uint8_t out_data);
void myGpioWriteWrapper4(uint8_t gpio_map_data, uint8_t out_data);


#endif /* EXAMPLES_C_PROJECTS_TP3_TP3_7_INC_TP3_H_ */
