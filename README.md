---


---

<h1 id="tp1---sistemas-embebidos">TP1 - SISTEMAS EMBEBIDOS</h1>
<h2 id="grupo-3">Grupo 3</h2>
<ul>
<li>Barrionuevo Facundo, Padrón: 99280.</li>
<li>Centofanti Ezequiel, Padrón: 100941.</li>
<li>Scheinkerman Lucas, Padrón: 100047.</li>
</ul>

# Instalación de herramientas

**MCUXpresso**

Se instaló el IDE MCUXpresso desde la web de NXP: [https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE](https://www.nxp.com/design/software/development-software/mcuxpresso-software-and-tools/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE). Para acceder a la descarga es necesario crearse una cuenta de NXP. Una vez descargado se ejecuta y se instala el software.

**eGit**

Se abre el Eclipse Marketplace desde la ventana de help del MCUXpresso y se procede a buscar y descargar la herramienta EGit.

**![](https://lh4.googleusercontent.com/PALqcFbkOBLzXytERsyd-SnJMVuCpd0ufQoUYMMxG0BqelmNIRpdeF-3gW2mCdWj6-KA-UHpIGdMwu53zFJcfFq9nDYA-PgomipbRrCbvmG45SbLwmH9HaxjH24gUDnFTPc4vQNB)**

**Yakindu**

Del mismo modo se busca e instala la herramienta de Yakindu Statecharts Tools.

**![](https://lh4.googleusercontent.com/OZvIy2rU03EjeewHex70rP6I9JtDGeYVjwOinBq1vbaxthhHJ-8IT7S83Y9en2AiseQffLeHV2hSFWMUSSItSQSkT90pJ6lYHtbfGqu-WDIG_PwN9aDIaS3OdG2et19jR3x2urzY)**

**Licencia de Yakindu**

Para poder utilizar libremente las herramientas de Yakindu se debe pedir una licencia en la pagina oficial.
[https://www.itemis.com/en/yakindu/state-machine/licenses](https://www.itemis.com/en/yakindu/state-machine/licenses)
**![](https://lh5.googleusercontent.com/M5t7GSxmZa_f-em7E4ts0eqV7OUMnwWQ6g9ZXiPgpCwTalVAdXOPR2oAyR6feqojm5MlYo7xriuhhOMRe9M-Ahh6wY6HaWWDjXWTQWVe9bvQCQu5wSyDKK3FdO7S2RwnnZqRDbAO)**

Se accede a una licencia académica sin costo. Luego de unos días se recibe el archivo (.lic) que se debe cargar en el MCUXpresso.

**Activación de licencia**

En el entorno de desarrollo de MCUXpresso nos dirigimos a la ventana de Window>Preferences. Luego en el apartado YAKINDU Licences cargamos el archivo (.lic) provisto por Yakindu.

**![](https://lh3.googleusercontent.com/t6hf3ncwjAxnYLMwWFKxPoDNbiut_xm4pwTOdxUKZdYgpyrmjzHcWnTUG8J4hL60KYP_LSPzonOBuC1fyJiho5hQS5uNYNgM5r8B_u01hyKx514QQxxi2TuYxsSufs82ISpEanK9)**

Una vez realizado este paso es posible utilizar las herramientas instaladas.

# Prueba de Yakindu

Se abre en el MCUXpresso el archivo toggle.sct que se encuentra en la carpeta: firmware_v3\examples\c\sapi\statecharts\1_toggle

Para simularlo hace clic derecho y se selecciona la opción RunAs>StatechartSimulation.

**![](https://lh3.googleusercontent.com/Z9ltFppJHIy7zgW_w37GYCom4WAMQD_Cac5tiUWuga1IbZJWDz3e5r0St7oFLfNw59kpojdS-nLECn3uRhvxFlYIrHgH2ilEAKcyIDuQ_msF1BVvxCPGyNv3H6eLrpq1hKnxnulG)**

Se puede ver el diagrama en la pantalla principal y a derecha el menú con los eventos para simular.
