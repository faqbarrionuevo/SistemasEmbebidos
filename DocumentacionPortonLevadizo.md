---


---

<h1 id="portón-levadizo">Portón Levadizo</h1>
<h2 id="consigna">Consigna:</h2>
<p><img src="https://lh6.googleusercontent.com/IMSzavElGW2vu6otsqCmaRuk-_wQ370cvL0lqI2hAEby8OFj16cXbH47JlFOA9yaRCnsY4SEa_El6QooKsp8AJNeBTD0KPohMEA_ta00ixMH3_mKjYdfx2O0Z4igoJroZV16y3cH" alt=""></p>
<h2 id="eventos">Eventos:</h2>
<ul>
<li>
<p>in event evRemoto ; Indica la presión del botón del control remoto.</p>
</li>
<li>
<p>in event evAbrio ; Indica cuando el portón terminó de abrir.</p>
</li>
<li>
<p>in event evCerro ; Indica cuando el portón terminó de cerrar.</p>
</li>
</ul>
<h2 id="operaciones">Operaciones:</h2>
<ul>
<li>
<p>operation opMotor(Action:boolean, State:boolean):void ; Encenderá o apagará el motor según digan sus argumentos.</p>
</li>
<li>
<p>operation opLuzRoja(Action:boolean, State:boolean):void ; Encenderá o apagará la luz roja según digan sus argumentos.</p>
</li>
<li>
<p>operation opLuzVerde(Action:boolean, State:boolean):void ; Encenderá o apagará la luz verde según digan sus argumentos.</p>
</li>
</ul>
<h2 id="constantes">Constantes:</h2>
<ul>
<li>
<p>const OPEN:boolean = true ; Indicará que el portón debe abrirse.</p>
</li>
<li>
<p>const CLOSE:boolean = false ; Indicará que el portón debe cerrarse.</p>
</li>
<li>
<p>const ON:boolean = true ; Prenderá cierta función.</p>
</li>
<li>
<p>const OFF:boolean = false ; Apagará cierta función.</p>
</li>
<li>
<p>const ONoFF:boolean = true ; Prenderá o apagará cierta función.</p>
</li>
<li>
<p>const TOGGLE:boolean = false ; Para realizar el toggle.</p>
</li>
</ul>
<h2 id="señales">Señales:</h2>
<ul>
<li>
<p>event siTitilar ; Señal que indicará que una luz debe titilar.</p>
</li>
<li>
<p>event siNoTitilar ; Señal que indicará que una luz debe dejar de titilar.</p>
</li>
</ul>
<h2 id="capturas-de-los-diagramas">Capturas de los diagramas:</h2>
<h2 id="región-principal">Región principal:</h2>
<p><img src="https://lh5.googleusercontent.com/Mh7Pn-8fMXDcGiFeeqQ9OaGag67LSimYlL1gHYhpALqbmSXgOnYBKFjA8xGdyZQKJOFXNRlBgKd9Q_eMWuOslmTQ51c1zC-BoawVsI3jJui9EMBSXSvotswIjmhC-PQfrqKxHc8b" alt=""></p>
<h2 id="regiones-de-luces">Regiones de luces:</h2>
<p><img src="https://lh3.googleusercontent.com/NPGmc63MYZ3t9jeeJXXLcKdzCXN1nF6Rwu_5yp-lwp6_HdBhWP409r7VcKIqAT5Y5ftRvHm0GxFvKid9_8u3F67tGGlortbz3JHm1kv30-GPpF1soW_sa38ukD0ObhESNnEFiSi-" alt=""></p>

