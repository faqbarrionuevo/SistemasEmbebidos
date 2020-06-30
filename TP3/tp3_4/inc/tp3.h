/*============================================================================
 * Licencia:
 * Autor:
 * Fecha:
 *===========================================================================*/

#ifndef _TP3_H_
#define _TP3_H_

/*==================[inclusiones]============================================*/
#include <stdio.h>
/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[tipos de datos declarados por el usuario]===============*/

#define MAX_DUTY 255
#define MIN_DUTY 0

/*==================[declaraciones de datos externos]========================*/

/*==================[declaraciones de funciones externas]====================*/
void procesarDato(uint8_t datoLeido, uint8_t* dutyCycle1, uint16_t* dutyCycle2, uint16_t* dutyCycle3);

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _APP_H_ */
