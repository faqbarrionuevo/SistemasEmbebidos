---


---

<h1 id="sistema-de-bloqueo-lorawan">Sistema de bloqueo LoRaWAN</h1>
<h2 id="descripción">Descripción</h2>
<p>En este proyecto se propone realizar un sistema de bloqueo para tranqueras controlado por una red LoRaWAN. Un dispositivo capaz de controlar el bloqueo o desbloqueo de un candado de forma remota.</p>
<p>Se llevará a cabo en un módulo xDot de Multitech, constará de un pulsador, leds, un buzzer, un servo motor, una batería y un teclado. El dispositivo estará inicialmente “cerrado” hasta que una persona quiera abrir. Ésta deberá pulsar el botón, lo que hará que el dispositivo intente asociarse a la red (máximo 3 intentos), si lo logra, enviará una solicitud de apertura a un servidor. El dispositivo esperará la respuesta durante un periodo de tiempo predefinido y de no recibir respuesta se habilitará el ingreso vía clave, que se detalla a continuación. Si se acepta la petición, el candado se abrirá. Si el dispositivo se encuentra abierto durante mucho tiempo se disparará una alarma, así como también habrá un tiempo fijo que esperará el ingreso vía clave, y si este no se concreta se irá a dormir.</p>
<p>Para realizar el ingreso vía clave se contará con un teclado, para que en el caso en que haya fallos en la conexión con el GateWay o algún otro error en la red, el usuario pueda ingresar un clave única que abrira la puerta.</p>
<p>El sistema operará con indicaciones led y alertas auditivas (buzzer) para indicar su estado, es decir, fallo en la conexión con GateWay, solicitud de apertura denegada o aceptada, etc.</p>
<p>En este archivo veremos el esquema de funcionamiento del sistema. En él se incluyen las funcionalidades de los leds, el buzzer, el servo motor y el teclado matricial (que está incluído en el diagrama principal y se activa mediante una operación, no tiene una región propia).</p>
<h2 id="estados">Estados</h2>
<ul>
<li>
<p>SLEEP ; Estado en el que el dispositivo estará en modo sleep.</p>
</li>
<li>
<p>ASOCIACION ; Estado en el que el dispositivo intentará asociarse a la red.</p>
</li>
<li>
<p>ENVIAR SOLICITUD ; En este estado el sistema enviará la solicitud de apertura y esperará la respuesta.</p>
</li>
<li>
<p>ABRIENDO ; Estado en el que estará mientras se esté abriendo.</p>
</li>
<li>
<p>ABIERTO ; Mientras esté abierto permanecerá en este estado.</p>
</li>
<li>
<p>INGRESO CLAVE ; Estado en el que estará mientras espera el ingreso de la clave.</p>
</li>
<li>
<p>APAGAR LEDS ; En este estado se apagarán los leds que se encuentren prendidos antes de ir a modo sleep.</p>
</li>
</ul>
<h2 id="estados-buzzer">Estados Buzzer</h2>
<ul>
<li>
<p>OFF ; Mientras se encuentre en este estado que buzzer estará apagado.</p>
</li>
<li>
<p>AGUDO CORTO ; En este estado el buzzer realizará un sonido agudo de corta duración (1 seg).</p>
</li>
<li>
<p>AGUDO LARGO ; En este estado el buzzer realizará un sonido agudo de más larga duración (3 seg).</p>
</li>
<li>
<p>GRAVE CORTO ; En este estado el buzzer realizará un sonido grave de corta duración (1 seg).</p>
</li>
<li>
<p>GRAVE LARGO ; En este estado el buzzer realizará un sonido grave de más larga duración (3 seg).</p>
</li>
<li>
<p>ALARMA ; Aquí el buzzer estará reproduciendo la alarma que se dispara si el sistema queda abierto por mucho tiempo.</p>
</li>
</ul>
<h2 id="estados-leds">Estados Leds</h2>
<ul>
<li>
<p>APAGADA ; La luz del led correspondiente estará apagada.</p>
</li>
<li>
<p>ENCENDIDA ; La luz del led correspondiente estará encendida.</p>
</li>
<li>
<p>TOGGLE ; El led correspondiente estará en estado de toggle.</p>
</li>
</ul>
<h2 id="estados-servo">Estados Servo</h2>
<ul>
<li>
<p>CERRADO ; En este estado el servo se encuentra en la posición tal que el sistema está cerrado.</p>
</li>
<li>
<p>ABRIENDO ; Estará en este estado mientras el dispositivo se esté abriendo.</p>
</li>
<li>
<p>ABIERTO ; Estará en este estado cuando el dispositivo se haya abierto totalmente.</p>
</li>
</ul>
<h2 id="eventos">Eventos</h2>
<ul>
<li>
<p>in event evBotonApertura ; Evento de presión del botón que solicita la apertura.</p>
</li>
<li>
<p>in event evAsociacionCorrecta ; Evento de asociación correcta del xDot.</p>
</li>
<li>
<p>in event evAsociacionIncorrecta ; Evento de asociación incorrecta del xDot.</p>
</li>
<li>
<p>in event evSolicitudAceptada ; Evento de solicitud de apertura aceptada.</p>
</li>
<li>
<p>in event evSolicitudNoAceptada ; Evento de solicitud de apertura no aceptada.</p>
</li>
<li>
<p>in event evErrorEnvio ; Evento de error en el envío de la solicitud de apertura.</p>
</li>
<li>
<p>in event evDesbordeTimerEspera ; Evento de desborde en el timer de espera para la respuesta a la solicitud de apertura.</p>
</li>
<li>
<p>in event evClaveCorrecta ; Evento de ingreso de clave correcta.</p>
</li>
<li>
<p>in event evClaveIncorrecta ; Evento de ingreso de clave incorrecta.</p>
</li>
<li>
<p>in event evDesbordeTimerAbierto ; Evento que se da cuanto el sistema se encuentra abierto más allá del tiempo permitido.</p>
</li>
<li>
<p>in event evDesbordeTimerEsperaTeclado ; Evento que se da cuando se espera el ingreso de la clave por un tiempo mayor al permitido.</p>
</li>
<li>
<p>in event evAbrio ; Evento que se dará cuando el sistema haya abierto, habrá un final de carrera con un pulsador, la presión de ese pulsador será la que sipare este evento.</p>
</li>
<li>
<p>in event evCierre ; Evento de cierre del sistema (será de manera manual).</p>
</li>
</ul>
<h2 id="operaciones">Operaciones</h2>
<ul>
<li>
<p>operation opAbrir(Action:boolean, Status:boolean): void ; Operación para abrir.</p>
</li>
<li>
<p>operation opAlarma(Action:boolean, Status:boolean): void ; Operación para prender o apagar la alarma según se lo indique.</p>
</li>
<li>
<p>operation opHabilitarTeclado(Action:boolean, Status:boolean):void ; Operación para habilitar o deshabilitar el teclado, es decir, el ingreso de la clave.</p>
</li>
<li>
<p>operation opEnviarSolicitud():void ; Operación para enviar la solicitud de apertura.</p>
</li>
<li>
<p>operation opAsociacion():void ; Operación para realizar la asociación.</p>
</li>
<li>
<p>operation opLuzRoja(Action:boolean, State:boolean):void ; Operacion para usar el led rojo según se indique en sus argumentos.</p>
</li>
<li>
<p>operation opLuzVerde(Action:boolean, State:boolean):void ; Operación para usar el led verde según se indique en sus argumentos.</p>
</li>
<li>
<p>operation opLuzAmarilla(Action:boolean, State:boolean):void ; Operación para usar el led Amarillo según se indique en sus argumentos.</p>
</li>
<li>
<p>operation opBuzzer(Action:boolean, State:boolean):void ; Operación para activar o desactivar el buzzer.</p>
</li>
</ul>
<h2 id="constantes">Constantes</h2>
<ul>
<li>
<p>const ABRIR: boolean = true ; Para indicar que se debe abrir.</p>
</li>
<li>
<p>const APAGADO: boolean = true ; Para indicar que se debe apagar el buzzer.</p>
</li>
<li>
<p>const ALARMA: boolean = true ; Para indicar al buzzer que debe encender la alarma.</p>
</li>
<li>
<p>const AGUDOCORTO: boolean = true ; Para indicar al buzzer qué sonido debe reproducir.</p>
</li>
<li>
<p>const AGUDOLARGO: boolean = true ; Para indicar al buzzer qué sonido debe reproducir.</p>
</li>
<li>
<p>const GRAVECORTO: boolean = true ; Para indicar al buzzer qué sonido debe reproducir.</p>
</li>
<li>
<p>const GRAVELARGO: boolean = true ; Para indicar al buzzer qué sonido debe reproducir.</p>
</li>
<li>
<p>const TECLADO: boolean = true ; Para indicar inicio del teclado.</p>
</li>
<li>
<p>const ON: boolean = true ; Para prender determinado periférico.</p>
</li>
<li>
<p>const OFF: boolean = false ; Para apagar determinado periférico.</p>
</li>
<li>
<p>const TOGGLE:boolean = false ; Indicará que se debe hacer toggle.</p>
</li>
<li>
<p>const ONoFF:boolean = true ; Para indicar que se debe prender o apagar determinado periférico.</p>
</li>
</ul>
<h2 id="variables">Variables</h2>
<ul>
<li>
<p>var viIntento:integer = 0 ; Variable para contar el número de intentos de asociación fallidos.</p>
</li>
<li>
<p>var abierto:boolean = false ; Esta variable hace las veces de botón de fin de carrera, e indicará cuando está abierto (true) y cuando está cerrado (false).</p>
</li>
</ul>
<h2 id="señales">Señales</h2>
<ul>
<li>
<p>event siTitilarAmarillo ; Señal para indicar que debe titilar el led amarillo.</p>
</li>
<li>
<p>event siNoTitilarAmarillo ; Señal para indicar que debe dejar de titilar el led amarillo.</p>
</li>
<li>
<p>event siPrenderVerde ; Señal para indicar que se debe prender el led verde.</p>
</li>
<li>
<p>event siApagarVerde ; Señal para indicar que se debe apagar el led verde.</p>
</li>
<li>
<p>event siTitilaVerde ; Señal para indicar que debe titilar el led verde.</p>
</li>
<li>
<p>event siPrenderRojo ; Señal para indicar que se debe prender el led rojo.</p>
</li>
<li>
<p>event siApagarRojo ; Señal para indicar que se debe apagar el led rojo.</p>
</li>
<li>
<p>event siTitilaRojo ; Señal para indicar que el led rojo debe titilar.</p>
</li>
</ul>
<h2 id="capturas-de-los-diagramas-de-estado">Capturas de los diagramas de estado</h2>
<h2 id="región-principal">Región principal</h2>
<p><img src="https://lh4.googleusercontent.com/dEFwmUsWOm9uNELIcMnA5Yv53L-eAv7r4wb_lQSi4BaqFOX_lG1veiNegBSb8qQXpOyKXHy5dBnUsq6YIsJd6q6ZhWgH0AOMYkFN96eNKDAC37buBFd5FyPEZVN0lt1xvPcS7Kbu" alt=""></p>
<h2 id="buzzer">Buzzer</h2>
<p><img src="https://lh5.googleusercontent.com/YE_hqjROY3-Ck5du43usy1zmKaIfH5iQDnjOgOXjecOt3vBfp5LRVWsfSTyT_Vl-qvQMtfiNKj-H6rKgbztfQSUEmLfeQW0wn5zBgwXQXmJ_p3oBo5oNZd1A7-NCh8rSdnoUStQS" alt=""></p>
<h2 id="leds">Leds</h2>
<p><img src="https://lh6.googleusercontent.com/axSbAFK8p70ucF8tFzxBi5TUpCDcFhCZv8CyQOF2UdIbHTjAPCnuPn0xu5j-gsh3jPZYnKtfcXbB0jcVSHFCUMQIIhyFbirzqNsuC3N2WgxKI7nlkhGhoNJVJ1ib0wTcP3uKNyJS" alt=""></p>
<p><img src="https://lh5.googleusercontent.com/ROKukx64dIEUVWN2iInirOBJjL2IBYcHZdCwkgoJCphNjjkcuDIGSEdDQdw3ZE3CsCL4fmdxvHSOWPm30d5lbDeuVagYcPt2gUBxUKjleRxBKTYNHLRjXWVsVH8llNoQ9pBsTzwc" alt=""></p>
<p><img src="https://lh3.googleusercontent.com/rfiL62ow5GfoLfvZfJIL676Wf0Scg9N9yefN7brbxhHUTzQWP2S9ttRMdEpEH0Rf2WntHRyeVKOFzB6uOSEaqlAT_BRJgUk-P88SuB37YuKNy-cUx16eT4OSkGb9cUD7uhm4yabR" alt=""></p>
<h2 id="servo">Servo</h2>
<p><img src="https://lh4.googleusercontent.com/R5qdEgraIbqgb2aUtpZ-iqjHazkjbI6mXFs3J7_QoYeEa5Wxc7TQpFl__AfQfMV7Et7MoGbCoxEWINzn5_cOZheHh8gtL6erJZ-TXBkvNzR3CXTsdJlCcpU2Ljk7TW17AQAE-8_v" alt=""></p>

