


//Tipos enumerativos, estructura y vectores que pide el TP2



//Tipo enumerativo para las diferentes configuraciones de los GPIO
typedef enum {
	PULL_UP,
	PULL_DOWN,
	OUTPUT,
	INPUT,

} gpioInit_t;


//Estructura para obtener los siguientes datos_
// -Puerto y pin a configurar del SCU
// -La funcion para que el pin anterior se configure como GPIO
// -Puerto y pin del GPIO utilizado
typedef struct {
	int8_t SCU_PORT;
	int8_t SCU_PIN;
	int8_t FUNC;
	int8_t GPIO_PORT;
	int8_t GPIO_PIN;
} conf_t;


//Vector global con todas las posibles configuraciones de la que pueden adoptar los GPIO
//Conforme a la estructura de arriba
const conf_t gpioPinsInit[] {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
}



//Tipo enumerativo para cada pin de la EDU CIAA que puede utilizarse como GPIO
typedef enum {

      // P1 header
      T_FIL1,
	  T_COL2,
	  T_COL0,
	  T_FIL2,
	  T_FIL3,
	  T_FIL0,
	  T_COL1,

      CAN_TD,
	  CAN_RD,
	  RS232_TXD,
	  RS232_RXD,

      // P2 header
      GPIO8,
	  GPIO7,
	  GPIO5,
	  GPIO3,
	  GPIO1,
      LCD1,
	  LCD2,
	  LCD3,
	  LCDRS,
	  LCD4,
      SPI_MISO,
      ENET_TXD1,
	  ENET_TXD0,
	  ENET_MDIO,
	  ENET_CRS_DV,
	  ENET_MDC,
	  ENET_TXEN,
	  ENET_RXD1,
	  GPIO6,
	  GPIO4,
	  GPIO2,
	  GPIO0,
      LCDEN,
      SPI_MOSI,
      ENET_RXD0,

      // Switches
      // 36   37     38     39
      TEC1,
	  TEC2,
	  TEC3,
	  TEC4,
      // Leds
      // 40   41     42     43     44     45
      LEDR,
	  LEDG,
	  LEDB,
	  LED1,
	  LED2,
	  LED3,

} gpioMap_t;







