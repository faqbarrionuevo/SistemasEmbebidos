---


---

<h1 id="trabajo-práctico-3--sistemas-embebidos">TRABAJO PRÁCTICO 3- SISTEMAS EMBEBIDOS</h1>
<h1 id="documentación-de-las-funciones-de-la-sapi">Documentación de las funciones de la sapi</h1>
<h2 id="ubicación">Ubicación</h2>
<p><img src="https://lh6.googleusercontent.com/7JRJv_pWqFumyqtvP8J9KPOnUcqaVpv08z1nogTSif5_nd1In-SkVyZMesTLO9bmsWWr_f05Y3wAoksitXp14OFtdgH_QfIrOY3tnFl0qUhOz1YsaHsM4bIfvB4vPLimDrT-9Q9j" alt=""></p>
<h2 id="uartconfig-uart_usb-115200-">uartConfig( UART_USB, 115200 )</h2>
<p>Esta función es la encargada de inicializar la UART, hay que pasarle que UART queremos inicializar, en este caso UART_USB, y el baud rate (115200).</p>
<p>Se encuentra en el archivo sapi_uart.c y utiliza las siguientes funciones:</p>
<ul>
<li>
<p>Chip_UART_Init</p>
</li>
<li>
<p>Chip_UART_SetBaud</p>
</li>
<li>
<p>Chip_UART_SetupFIFOS</p>
</li>
<li>
<p>Chip_UART_ReadByte</p>
</li>
<li>
<p>Chip_UART_TXEnable</p>
</li>
<li>
<p>Chip_SCU_PinMux</p>
</li>
<li>
<p>Chip_UART_SetRS485Flags</p>
</li>
</ul>
<h2 id="adcconfig-adc_enable-">adcConfig( ADC_ENABLE )</h2>
<p>Esta función es la encargada de configurar el ADC, y hay que pasarle la configuración deseada (Habilitado o Deshabilitado).</p>
<p>Se encuentra en el archivo sapi_adc.c y utiliza las siguietes funciones:</p>
<ul>
<li>
<p>Chip_ADC_Init</p>
</li>
<li>
<p>Chip_ADC_SetBurstCmd</p>
</li>
<li>
<p>Chip_ADC_SetSampleRate</p>
</li>
<li>
<p>Chip_ADC_EnableChannel</p>
</li>
<li>
<p>Chip_ADC_Int_SetChannelCmd</p>
</li>
<li>
<p>Chip_ADC_DeInit</p>
</li>
</ul>
<h2 id="dacconfig-dac_enable-">dacConfig( DAC_ENABLE )</h2>
<p>Esta función es la analoga de la anterior pero para el DAC.</p>
<p>Se encuenttra en el archivo sapi_dac.c y utiliza las siguientes funciones:</p>
<ul>
<li>
<p>Chip_Clock_EnableOpts</p>
</li>
<li>
<p>Chip_DAC_SetBias</p>
</li>
<li>
<p>Chip_DAC_ConfigDAConverterControl</p>
</li>
<li>
<p>Chip_DAC_UpdateValue</p>
</li>
<li>
<p>Chip_DAC_DeInit</p>
</li>
</ul>
<h2 id="delayconfig-delay-500-">delayConfig( &amp;delay, 500 )</h2>
<p>Función encargada de configurar un delay no bloqueante. Debemos pasarle un puntero y el tiempo de dalay requerido.</p>
<p>Se encuentra en el archivo sapi_delay.c</p>
<h2 id="muestra--adcread-ch1-">muestra = adcRead( CH1 )</h2>
<p>La función adcRead, obtiene el valor del canal que le pasemos, en este caso channel 1, y guardamos dicho valor en muestra, es decir, retorna el valor leido.</p>
<p>Se encuentra en el archivo sapi_delay.c y utiliza las siguientes funciones:</p>
<ul>
<li>
<p>Chip_ADC_EnableChannel</p>
</li>
<li>
<p>Chip_ADC_SetStartMode</p>
</li>
<li>
<p>Chip_ADC_ReadStatus</p>
</li>
<li>
<p>Chip_ADC_ReadValue</p>
</li>
<li>
<p>Chip_ADC_EnableChannel</p>
</li>
</ul>
<h2 id="uartreadbyte-uart_usb-dato-">uartReadByte( UART_USB, &amp;dato )</h2>
<p>Esta función lee 1 byte del RX del UART que le pasemos y lo guarda en dato, que es un puntero que también debemos pasarle.</p>
<p>Devuelve 1 en caso de que haya algo para leer, y cero en caso de que no. Una variable del tipo booleana.</p>
<p>Se encuentra en el archivo sapi_uart.c y utiliza las siguientes funciones:</p>
<ul>
<li>
<p>uartRxReady</p>
</li>
<li>
<p>uartRxRead</p>
</li>
</ul>
<h2 id="uartwritebyte-uart_usb-dato-">uartWriteByte( UART_USB, dato )</h2>
<p>Función que escribe un byte en el TX de la UART que le pasemos, escribe especificamente el dato que le damos en el segundo argumento.</p>
<p>Se encuentra en sapi_uart.c y utiliza las siguientes funciones:</p>
<ul>
<li>
<p>uartTxReady</p>
</li>
<li>
<p>uartTxWrite</p>
</li>
</ul>
<h2 id="uartwritestring-uart_usb-adc-ch1-value--">uartWriteString( UART_USB, "ADC CH1 value: " )</h2>
<p>Esta función manda por la UART que le pasemos en el primer argumento una cadena que le pasamos en el segundo.</p>
<p>Se encuentra en el archivo sapi_uart.c y utiliza las siguientes funciones:</p>
<ul>
<li>uartWriteByte</li>
</ul>
<h2 id="dacwrite-dac-muestra-">dacWrite( DAC, muestra )</h2>
<p>Función para escribir un valor en el DAC, el valor a pasarle en el segundo argumento deberá ser analogico, de 0 a 1023. Con el primer argumento le decimos en que DAC escribir.</p>
<p>Se encuentra en el archivo sapi_dac.c y utiliza las siguientes funciones:</p>
<ul>
<li>Chip_DAC_UpdateValue</li>
</ul>
<h2 id="uartcallbacksetuart_usb-uart_receive-onrx-null">uartCallbackSet(UART_USB, UART_RECEIVE, onRx, NULL)</h2>
<p>Función para setear callback a una interrupción en algún UART, en el primer argumento debemos pasarle el UART, en el segundo el evento por el cual queremos que se dispare dicha interrupción, en este caso al pasarle UART_RECEIVE será interrupción por recepción, en el tercer argumento le pasaremos el nombre de la función que se debe ejecutar al ocurrir la interrupción.</p>
<p>Se encuentra en el archivo sapi_uart.c y utiliza las siguientes funciones:</p>
<ul>
<li>Chip_UART_IntEnable</li>
</ul>
<h2 id="uartinterruptuart_usb-true">uartInterrupt(UART_USB, true)</h2>
<p>Función para habilitar el uso de interruciones en algún UART, debemos pasarle el UART y TRUE si queremos habilitarla, o FALSE si queremos deshabilitarla.</p>
<p>Se encuentra en el archivo sapi_uart.c y utiliza las siguientes funciones:</p>
<ul>
<li>
<p>NVIC_SetPriority</p>
</li>
<li>
<p>NVIC_EnableIRQ</p>
</li>
<li>
<p>NVIC_DisableIRQ</p>
</li>
</ul>

