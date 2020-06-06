---


---

<h1 id="migración-del-proyecto-app-a-tp2">Migración del proyecto app a TP2</h1>
<p>En este documento seguiremos los pasos para lograr una migración exitosa del proyecto examples/c/app a: examples/c/proyects/tp2.</p>
<p>Lo haremos dentro del eclipse, en el proyecto firmware v3.</p>
<h2 id="paso-1">Paso 1</h2>
<p>En examples/c crear la carpeta proyects, y dentro de esta carpeta crear una nueva llamada tp2.</p>
<p><img src="https://lh6.googleusercontent.com/nsxGt6eCFHxI3_CGDA3ExJqWOEseZTLhG-iEPg4zW3uB_skwfUCuws4eL0n7_YnhqoGQNmer06dudRGVlwbR9wRg0aJqDCUIA0QKasLYYjrCFiI_VRKBkynnBhFh-tXWxFr1AmcZ" alt=""></p>
<h2 id="paso-2">Paso 2</h2>
<p>Dentro de la carpeta tp2, crear las carpetas src e inc. Ademas también agregar el archivo <a href="http://config.mk">config.mk</a> (que se encuentra dentro de la carpeta app).</p>
<p><img src="https://lh6.googleusercontent.com/7Nt4tLz9gbF-8_p_kooY_R4KH5mPi1eXSVyKmHKk4CW3iuavf2gV82dGvF9BVKhR-a_i03DYYlfChC8hJen-YqjagEjil7RaJqu41DLzPFJFKAuMzj-1X1inIgpuTUHyPxJM9x3q" alt=""></p>
<h2 id="paso-3">Paso 3</h2>
<p>Copiar el archivo app.c de examples/c/app/src y pegarlo en examples/c/proyects/tp2/src.</p>
<p>También copiar de la misma carpeta de origen pero en inc el archivo app.h y pegagarlo en examples/c/proyects/tp2/inc. Cambiarle el nombre a ambos archivos a tp2.c y tp2.h</p>
<p>Luego dentro del archivo tp2.c cambiar el include #include “app.h” por #include “tp2.h”</p>
<h2 id="paso-4">Paso 4</h2>
<p>Ahora dando click derecho en firmware v3, crear un nuevo archivo con el nombre <a href="http://program.mk">program.mk</a></p>
<p><img src="https://lh5.googleusercontent.com/IJhBC_CCsOInjSDF1FIoPTqJtd3ND-QyJtVLGWoyZFh3N3OauqA7dFZzP1d8Q83ZnsA8JNVJ6DP7wyyFD8FZIIwrKRHnRvCpsIjnlutz5ZEqJnvkwoqu04WMQpn7u8r6JVJxUHwD" alt=""></p>
<p>Y dentro de él escribir lo siguiente:</p>
<p><img src="https://lh3.googleusercontent.com/RBE8fvU-Th15kezzlRF-oxFwhROT7nzF3vo0uoJHHepWHIHh-DSbRtmrEkYEr2iFNoo3L0YTlOalbdAQ2WtEG3RQOUC5ZTm4ne5XZl8T_8noFG0KlKmEyQsVD3ipXPv1vEc5Cxo-" alt=""></p>
<h2 id="paso-5">Paso 5</h2>
<p>Teniendo abierto tp2.c hacer click derecho en firmware v3 y elegir la opción Clean Proyect, cuando eso acabe hacer lo mismo pero esta vez elegir la opción Build Proyect.</p>
<p><img src="https://lh4.googleusercontent.com/nRN8LAFPAQst5aMO8QBq6dQEWC7MQA-PaWCWnon2S3gzY3I1ivWq46d92cIyUq7MBzF4P0up5LwuJufpCpFIKQrcHBaLp9G91n5KkkoMOxXo7aOtkeLZSuB5tkleQ4dgDo-WQlLg" alt=""></p>
<h2 id="paso-6">Paso 6</h2>
<p>Hacer nuevamente click derecho en firmware v3, y esta vez elegir la opción Debug As, y luego Debug configurations…</p>
<p><img src="https://lh5.googleusercontent.com/mvDYGMwbgD09EWZuZW8iI9elCBKD4LRvy3pCTO4UTN37xuwafFjTb7GidtPa-vFYg4SXxmi8gcvld4ay7F0C4kQQJxrLAdjJxD9CYgE8PORWlLsB2_zSXTWCsERnOL_huF3Ml41J" alt=""></p>
<p>Dentro de debug configurations, en la solapa main, tocar Search Project y elegir tp2.elf</p>
<p><img src="https://lh5.googleusercontent.com/aqeT-47tWXXpFVfMJmALFCocoPT8yKjIpfTBuy_Pkl5YAROTDeBaXVCfbbcON5Sv6XJNRRiJeW6VCpNHPR0X0foUCBXcQC1ZJ1jU6UP0GofPBfIo8OU5djrsI0_hpFfoVwGAGh3-" alt=""></p>
<p>Ahora clickear Ok y luego Debug. Si todo eso se hizo de forma correcta, significará que el proyecto fue migrado con éxito.</p>

