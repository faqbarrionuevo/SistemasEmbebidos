# Puerta Corrediza

**Consigna:** 

 **![](https://lh6.googleusercontent.com/3xnGqZy-aR9fCmqxsVmrvt3uQc2znWsR0eEY0qpm-D4zGdd8SO1Io7he8D8hki5wkVCVgD9lqVModGKph_whSiblSkz5cWrh9PcuH-B-rv6USLlRGJI7tL2Vx-tFph3His9s1o0)**

**Eventos:**

•	in event evPresencia
•	in event evNoPresencia
•	in event evAbrio
•	in event evCerro

**Operaciones:** 

•	operation opMotor(Action:boolean, State:boolean):void
•	operation opLuzRoja(Action:boolean, State:boolean):void

**Constantes:** 

•	const OPEN:boolean = true
•	const CLOSE:boolean = false
•	const ON:boolean = true
•	const OFF:boolean = false
•	const ONoFF:boolean = true
•	const TOGGLE:boolean = false
•	const T_MOTOR_STOP_ms:integer = 500

**Señales:**

•	event siTitilar
•	event siNoTitilar

**Capturas de los diagramas:**

**Región principal:**
**![](https://lh3.googleusercontent.com/y8Br1Axsk5RNu0FGKFnQ-YZlMcozFcIdlVJBN_igBQHLNq2-OBAKHeBzmybJvtACdzC-sDHC4IzVjD7jrHITzcBQbEqC9saqWnZ0e8OGViq8x0d77SvOcBh5ZUjgMbYHMnM-JGY)**
**Regiones de luces:** 

**![](https://lh3.googleusercontent.com/_WFLRAcnbP1RmXY4-9Yck7psrC7oiFg21-nHtH9mwCNPQ21Tu3vXuo09j0CbV_zhI447w3Ulbheoaj0qEBi37ARU6UIeGcZottYHQ-vtHWnZNMkQaDZm-DG2k2LFbgaHLjU4u6c)**
