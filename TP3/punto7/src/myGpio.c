#include "myGpio.h"


//Vector global que contiene todas las posibles configuraciones que pueden adoptar los GPIO
static const gpioPinInfo_t gpioPinsInit[] = {

		//{PinNamePortN ,PinNamePinN, PinFUNC, GpioPortN, GpioPinN}

	      {1, 0, 0, 0, 4},   // 36   TEC1    TEC_1
	      {1, 1, 0, 0, 8},   // 37   TEC2    TEC_2
	      {1, 2, 0, 0, 9},   // 38   TEC3    TEC_3
	      {1, 6, 0, 1, 9},   // 39   TEC4    TEC_4

	      {2, 0, 4, 5, 0},   // 43   LEDR    LED0_R
	      {2, 1, 4, 5, 1},   // 44   LEDG    LED0_G
	      {2, 2, 4, 5, 2},   // 45   LEDB    LED0_B
	      {2,10, 0, 0,14},   // 40   LED1    LED1
	      {2,11, 0, 1,11},   // 41   LED2    LED2
	      {2,12, 0, 1,12},   // 42   LED3    LED3

};

void myBoardConfig(void) {

	// Funcion para asegurarse de que el clock este bien configurado
	SystemCoreClockUpdate();


	// Inicializar GPIOs
	myGpioInit( 0, GPIO_ENABLE );

	// Configuracion de pines de entrada para Teclas de la EDU-CIAA-NXP
	myGpioInit( myTEC1, GPIO_INPUT );
	myGpioInit( myTEC2, GPIO_INPUT );
	myGpioInit( myTEC3, GPIO_INPUT );
    myGpioInit( myTEC4, GPIO_INPUT );

	// Configuracion de pines de salida para Leds de la EDU-CIAA-NXP
	myGpioInit( myLEDR, GPIO_OUTPUT );
	myGpioInit( myLEDG, GPIO_OUTPUT );
	myGpioInit( myLEDB, GPIO_OUTPUT );
	myGpioInit( myLED1, GPIO_OUTPUT );
	myGpioInit( myLED2, GPIO_OUTPUT );
	myGpioInit( myLED3, GPIO_OUTPUT );
}


// Obtiene todos los datos requeridos del pin a configurar
void gpioObtainPinInit( myGpioMap_t pin,
                               int8_t *pinNamePort, int8_t *pinNamePin,
                               int8_t *func, int8_t *gpioPort,
                               int8_t *gpioPin )
{

   *pinNamePort = gpioPinsInit[pin].pinNamePortN;
   *pinNamePin  = gpioPinsInit[pin].PinNamePinN;
   *func        = gpioPinsInit[pin].PinFunc;
   *gpioPort    = gpioPinsInit[pin].GpioPortN;
   *gpioPin     = gpioPinsInit[pin].GpioPinN;
}



//Función para inicializar un pin GPIO
//Recibe el pin a configurar y la configuracion deseada
//Devuelve false en caso de configuración es invalida
bool_t myGpioInit(myGpioMap_t pin, myGpioInit_t conf) {

	bool_t retval = TRUE;

	int8_t pinNamePort = 0;
	int8_t pinNamePin = 0;
	int8_t func = 0;
	int8_t gpioPort = 0;
	int8_t gpioPin = 0;

	gpioObtainPinInit( pin, &pinNamePort, &pinNamePin, &func, &gpioPort, &gpioPin );

	switch(conf) {
		case GPIO_ENABLE:
			Chip_GPIO_Init(LPC_GPIO_PORT);
			break;

		case GPIO_INPUT:
			Chip_SCU_PinMux(
				 pinNamePort,
		         pinNamePin,
			     SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
			     func
			);
			Chip_GPIO_SetDir(LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_INPUT );
			break;

		case GPIO_OUTPUT:
		      Chip_SCU_PinMux(
		         pinNamePort,
			     pinNamePin,
			     SCU_MODE_INACT | SCU_MODE_ZIF_DIS | SCU_MODE_INBUFF_EN,
				 func
			  );
			  Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), GPIO_OUTPUT );
			  Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, 0);
			  break;

		default:
			return FALSE;
	}

	return retval;
}

//Función para escribir en un pin GPIO
void myGpioWrite(myGpioMap_t pin, bool_t value){

	    int8_t pinNamePort = 0;
		int8_t pinNamePin = 0;
		int8_t func = 0;
		int8_t gpioPort = 0;
		int8_t gpioPin = 0;

		gpioObtainPinInit( pin, &pinNamePort, &pinNamePin, &func, &gpioPort, &gpioPin );

		Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, value);
}
//Funcion para leer el contenido de un pin GPIO
bool_t myGpioRead(myGpioMap_t pin) {
	int8_t pinNamePort = 0;
	int8_t pinNamePin = 0;
	int8_t func = 0;
	int8_t gpioPort = 0;
	int8_t gpioPin = 0;

	gpioObtainPinInit(pin, &pinNamePort, &pinNamePin, &func, &gpioPort,
			&gpioPin);

	return (bool_t) Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, gpioPort, gpioPin);

}

// Cuenta la cantidad de ticks del clock que pasaron
static volatile uint32_t tick_count = 0;

void myDelay(uint32_t tk)
{
   uint32_t end = tick_count + tk;
   while(tick_count < end)
      __WFI();
}

// Funcion que se llama cada vez que pasa un ciclo de clock
void clock_callback(void)
{
   tick_count++;
}

