# Puerta Corrediza

  

**Consigna:**

![](https://lh3.googleusercontent.com/LeVLzlXlMbdbusbuisbSeMch_sZJrvqZlSAHV7-pih42RXNTrgjASpdSQVtsRzzGUR7qYNBoFieCIPKZbN5rxeMjFOGBk3rT3Zi7SfVLtwyAVVXO8GmzC_qdZTJVDA)

  

**Eventos:**

- in event evStartStop
- in event evModo
- in event evPAbierta
- in event evPCerrada

**Operaciones:**

- operation opEncenderLuz():void
- operation opApagarLuz():void
- operation opLED(c:integer):void
- operation opEncenderHorno(c:integer):void

**Variables:**

- var inModo:integer
- var inTimeSecs:integer
- var MODO:integer=0

**Constantes:**

- const inApagarHorno:integer = 0
- const inModoHorno:integer = 1
- const inModoGrill:integer = 2
- const inModoHornoYGrill:integer = 3
- const inTiempoInitSecs:integer = 30

**Señales:**

- event siCM
- event siLuzApagada
- event siLuzEncendida

# Capturas de los diagramas:

**Región principal:**

![](https://lh3.googleusercontent.com/TFO-0HujbZyVVmIPPpcheqe_VZ7plaUfhBRFdCCMVGne4vnM7TaJ0MBt_ZEClUi__yFfgaDNC72lYyd25x8ntaQHnGVTwAlfTjktiTEO65pO9553rWIqT-uNl0fj-w)

  
**Region de modos:**

![](https://lh6.googleusercontent.com/BIqrfw2J345KBBB3xqwkT_l6sdsmsfBYlxC4D5gUXcKzyzDlEKXEqrGZY-ofTsuQmb94kMJamuMc-zYCtFlqzj3nsloyywf_m-1_MbdYr4R12-PLWEnJJwEi9ZiQww)

**Region de luz:**

![](https://lh5.googleusercontent.com/2CDPAyjvrfmxK67JV-UuRye1k1c5t2tA6Ja2piGz-Pz6D_1vMgS-aclobQo8gnPufwrCLhyXEbeVYTRl07jCMheXAueP1fxOZ8ZZTDHfhK-FGhc7XyLHqaYgte7a8w)

 
**Regiones de Leds**

**![](https://lh3.googleusercontent.com/ZzuDpfhh92-1nnmB1fkG9G8QJMLbJ3v5mwYKs6HEELnk-X-GKAemiu4jFkGNTHAvws8Bl7UtlZ-VRNAF2mP7AYCZ962rVmwfSPkVnIqSPwFO9TruOgzoRsXOSe-tgA)**
