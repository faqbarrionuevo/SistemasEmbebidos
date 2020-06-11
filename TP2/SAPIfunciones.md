## Funciones SAPI

Las funciones principales de la SAPI que se usan en este programa son

  

* void boardConfig( void );

* bool_t gpioRead( gpioMap_t pin )

* bool_t gpioWrite( gpioMap_t pin, bool_t value )

  
## boardConfig()
La primer función se encarga de inicializar los puertos de la EDU-CIAA. Inicializa los botones TEC1-4 como entradas GPIO y los leds LED0RGB y LED1-3 como salidas GPIO. Para esto se vale de la función de la SAPI:

  

* bool_t gpioInit( gpioMap_t pin, gpioInit_t config )

  

Esta función se encarga de inicializar un pin con una de las posibles configuraciones. Las posibles configuraciones están definidas en el siguiente tipo enumerativo:

  
```
typedef enum {

GPIO_INPUT, GPIO_OUTPUT,

GPIO_INPUT_PULLUP, GPIO_INPUT_PULLDOWN,

GPIO_INPUT_PULLUP_PULLDOWN,

GPIO_ENABLE

} gpioInit_t;
```
  

Para inicializar los puertos, gpioInit se vale de dos funciones de *NXP*:

  
```
STATIC INLINE void Chip_SCU_PinMux(uint8_t port, uint8_t pin, uint16_t mode, uint8_t func)

{
```

```
Chip_SCU_PinMuxSet(port, pin, (mode | (uint16_t) func));

}
```
  
```
STATIC INLINE void Chip_GPIO_SetDir(LPC_GPIO_T *pGPIO, uint8_t portNum, uint32_t bitValue, uint8_t out)

{

if (out) {

pGPIO->DIR[portNum] |= bitValue;

}

else {

pGPIO->DIR[portNum] &= ~bitValue;

}

}
```
  

Estas dos funciones acceden directamente a las estructuras de registros SCU y GPIO y cargan los registros necesarios para configurar los pines del modo deseado.

## gpioRead(pin)

La función gpioRead se utliza para leer el valor de un puerto GPIO. Ésta recibe el pin que se desea leer y devuelve el estado de dicho pin. Fundamentalmente esta función devuelve el siguiente valor:

  
```
ret_val = (bool_t) Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, gpioPort, gpioPin );
```
  

La función Chip_GPIO_ReadPortBit es una función de *NXP* que permite leer el valor de un puerto. Recibe la dirección de la estructura con la información de los puertos para poder acceder a la memoria de la EDU-CIAA y específicamente qué puerto y pin se desea leer.

  
```
STATIC INLINE bool Chip_GPIO_ReadPortBit(LPC_GPIO_T *pGPIO, uint32_t port, uint8_t pin)

{

return (bool) pGPIO->B[port][pin];

}
```
  

Esta función directamente accede al valor del pin que se desea leer, que se encuentra en la estructura de registros GPIO.

## gpioWrite(pin, value)

```
bool_t gpioWrite( gpioMap_t pin, bool_t value )
```
  

Esta función recibe el pin que se desea escribir y el valor que se desea escribir y devuelve dicho valor de ser posible la escritura. La línea de código en la que se escribe el pin es la siguiente:

  
```
Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, value);
```
  

Acá se utiliza la función Chip_GPIO_SetPinState de *NXP* que permite escribir un valor en un puerto gpio. El código de la función es el siguiente:

  
```
STATIC INLINE void Chip_GPIO_SetPinState(LPC_GPIO_T *pGPIO, uint8_t port, uint8_t pin, bool setting)

{

pGPIO->B[port][pin] = setting;

}
```
  

La función guarda en la estructura de registros GPIO el valor que se pide. Par ello recibe el puerto y pin que se desea escribir y el valor que se desea escribir. Además, requiere un puntero a la estructura de memoria de registros GPIO
