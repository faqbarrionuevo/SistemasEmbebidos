Las estructuras que representan los periféricos SCU y GPIO son las siguientes:

  

typedef struct {  /*!< GPIO_PORT Structure */

__IO uint32_t SFSP[16][32];

__I uint32_t RESERVED0[256];

__IO uint32_t SFSCLK[4];

__I uint32_t RESERVED16[28];

__IO uint32_t SFSUSB;

__IO uint32_t SFSI2C0;

__IO uint32_t ENAIO[3];

__I uint32_t RESERVED17[27];

__IO uint32_t EMCDELAYCLK;

__I uint32_t RESERVED18[63];

__IO uint32_t PINTSEL[2];

} LPC_SCU_T;

  

En esta estructura se puede ver el campo SFSP, en el cual se encuentran los registros que permiten seleccionar la función de cada pin y algunas otras opciones como la selección de resistencias de pull up.

  

typedef struct {  /*!< GPIO_PORT Structure */

__IO uint8_t B[128][32];

__IO uint32_t W[32][32];

__IO uint32_t DIR[32];

__IO uint32_t MASK[32];

__IO uint32_t PIN[32];

__IO uint32_t MPIN[32];

__IO uint32_t SET[32];

__O uint32_t CLR[32];

__O uint32_t NOT[32];

} LPC_GPIO_T;

  

En esta estructura los primeros dos campos representan los registros GPIO en Bytes o en Words. El campo de DIR es el que permite seleccionar los pines como entrada o salida GPIO. Luego hay otros campos que permiten realizar operaciones sobre los registros GPIO.
