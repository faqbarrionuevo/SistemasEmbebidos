#ifndef _my_gpio_h_
#define _my_gpio_h_

#ifndef FALSE
#define FALSE  0
#endif
#ifndef TRUE
#define TRUE   (!FALSE)
#endif

#define MY_CIAA_BOARD_BUTTON
#define MY_CIAA_BOARD_LED

// Tipo de datos que renombra un tipo basico
typedef uint8_t bool_t;

bool_t myGpioInit(gpioMap_t pin, gpioInit_t conf);
bool_t myGpioWrite(gpioMap_t pin, bool_t value);
bool_t myGpioRead(gpioMap_t pin);
void   myGpioObtainPinInit(gpioMap_t pin, );

typedef enum {
	FALSE, TRUE
} bool_t;

typedef enum {
TEC1,
TEC2,
TEC3,
TEC4,
LEDR,
LEDG,
LEDB,
LED1,
LED2,
LED3
} myGpioMap_t;

typedef enum {
	GPIO_INPUT, GPIO_OUTPUT,
	GPIO_ENABLE
} myGpioInit_t;

typedef enum {
	int8_t pinNamePortN;
	int8_t PinNamePinN;
	int8_t PinFunc;
	int8_t GpioPortN;
	int8_t GpioPinN;
} gpioPinInfo_t;

#endif
