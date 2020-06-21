#ifndef _my_gpio_h_
#define _my_gpio_h_

#include "stdint.h"
#include "chip.h"

#ifndef FALSE
#define FALSE  0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

#ifndef OFF
#define OFF 0
#endif
#ifndef ON
#define ON (!OFF)
#endif

// Funcion y modo (pag. 413 de User Manual)
#define SCU_MODE_PULLUP                 (0x0 << 3)   // Enable pull-up resistor at pad
#define SCU_MODE_INACT                  (0x2 << 3)   // Disable pull-down and pull-up resistor at resistor at pad
#define SCU_MODE_PULLDOWN               (0x3 << 3)   // Enable pull-down resistor at pad
#define SCU_MODE_INBUFF_EN              (0x1 << 6)   // Enable Input buffer
#define SCU_MODE_ZIF_DIS                (0x1 << 7)   // Disable input glitch filter
#define SCU_MODE_FUNC0                  0x0          // Selects pin function 0
#define SCU_MODE_FUNC1                  0x1          // Selects pin function 1
#define SCU_MODE_FUNC2                  0x2          // Selects pin function 2
#define SCU_MODE_FUNC3                  0x3          // Selects pin function 3
#define SCU_MODE_FUNC4                  0x4          // Selects pin function 4
#define SCU_MODE_FUNC5                  0x5          // Selects pin function 5

// Escalar utilizado para el computo de delays
#define TICKRATE_HZ (1000)

// Se define el callback del clock como la funcion
// clock_callback()
#ifndef TICK_OVER_RTOS
   #define tickerCallback clock_callback
#endif

// Tipo de dato utilizado a modo de booleano
typedef uint8_t bool_t;

typedef enum {
myTEC1,
myTEC2,
myTEC3,
myTEC4,
myLEDR,
myLEDG,
myLEDB,
myLED1,
myLED2,
myLED3
} myGpioMap_t;

typedef enum {
	GPIO_INPUT, GPIO_OUTPUT,
	GPIO_ENABLE
} myGpioInit_t;


typedef struct {
	int8_t pinNamePortN;
	int8_t PinNamePinN;
	int8_t PinFunc;
	int8_t GpioPortN;
	int8_t GpioPinN;
} gpioPinInfo_t;

// Tipo de dato usado para computo de delays.
typedef uint64_t tick_t;

// Inicializa cada puerto a utilizar en la aplicacion.
void myBoardConfig(void);

// Inicializa un puerto GPIO como input o output
bool_t myGpioInit(myGpioMap_t pin, myGpioInit_t conf);

// Escribe en un puerto GPIO
void myGpioWrite(myGpioMap_t pin, bool_t value);

// Lee un puerto GPIO
bool_t myGpioRead(myGpioMap_t pin);

// Llena los punteros con los valores de puertos, pines y funciones
// correspondientes al periferico que se desea utilizar.
// Es una funcion auxiliar que sirve para mapear facilmente perifericos
// a pines y puertos concretos.
void myGpioObtainPinInit(myGpioMap_t pin,
		int8_t *pinNamePort,
		int8_t *pinNamePin,
		int8_t *func,
		int8_t *gpioPort,
        int8_t *gpioPin );

// Callback para cada vez que pasa un ciclo de clock
void clock_callback(void);

// Funcion para realizar delay.
void myDelay(uint32_t tk);

#endif
