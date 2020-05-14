---


---

<h1 id="escalera-mecánica">Escalera Mecánica</h1>
<h2 id="consigna">Consigna:</h2>
<p><img src="https://lh6.googleusercontent.com/YSecMkvKPss2T-YVn43yP1OtvINNU905wNDSscHXJbgdWAyZQMgF43QhHzrItfPuALVBb6o3fyFdGlNV4s4EjvmtCiJZgGXCETffkMXX4v3ABX8SExrMbpXIYzf83dClQQXYWr7F" alt=""></p>
<h2 id="complejización-del-modelo">Complejización del modelo</h2>
<p>Para complejizar el modelo, se le añadieron luces en ambos extremos de la escalera, es decir, luces como parte del sensor 1 y otras luces como parte del sensor 2.</p>
<p>Las que funcionan de la siguiente manera:</p>
<ul>
<li>
<p>Cuando la escalera esté en STOP, las luces verdes de ambos sensores estarán encendidas, mostrando que la escalera está ‘Libre’.</p>
</li>
<li>
<p>Cuando la escalera esté en movimiento, las luces rojas de ambos sensores comenzarán a titilar indicando que la escalera está en uso.</p>
</li>
</ul>
<p>Para continuar complejizando este modelo, también se le añadió el caso en que más de una persona quiera subir o bajar. En este caso se le agrega un sistema de conteo de personas en la escalera. Pasaremos a explicarlo con un ejemplo:</p>
<p>Si hay una persona subiendo y antes de que ésta llegue al final otra comienza a subir, entonces la escalera no se detendrá hasta que ambas lleguen a bajarse. Esto se extiende a N personas y análogamente para casos de bajada.</p>
<h2 id="eventos">Eventos</h2>
<ul>
<li>
<p>in event evPresionS1 ; Se activa al activarse el sensor de presión 1, en este caso el de abajo.</p>
</li>
<li>
<p>in event evPresionS2 ; Se activa al activarse el sensor de presión 2, en este caso el de arriba.</p>
</li>
</ul>
<h2 id="operaciones">Operaciones</h2>
<ul>
<li>
<p>operation opSubir(Action:boolean, Status:boolean): void ; Activa la escalera en la dirección correspondiente para subir.</p>
</li>
<li>
<p>operation opBajar(Action:boolean, Status:boolean): void ; Activa la escalera en la dirección correspondiente para bajar.</p>
</li>
<li>
<p>operation opStop(Action:boolean, Status:boolean): void ; Hace frenar a la escalera.</p>
</li>
<li>
<p>operation opLuzRojaS1(Action:boolean, State:boolean):void ; Activa la luz roja del sensor 1 en la acción que corresponda.</p>
</li>
<li>
<p>operation opLuzVerdeS1(Action:boolean, State:boolean):void ; Activa la luz verde del sensor 1 en la acción que corresponda.</p>
</li>
<li>
<p>operation opLuzRojaS2(Action:boolean, State:boolean):void ; Activa la luz roja del sensor 2 en la acción que corresponda.</p>
</li>
<li>
<p>operation opLuzVerdeS2(Action:boolean, State:boolean):void ; Activa la luz verde del sensor 2 en la acción que corresponda.</p>
</li>
</ul>
<h2 id="constantes">Constantes</h2>
<ul>
<li>
<p>const ON: boolean = true ; Para encender una función.</p>
</li>
<li>
<p>const OFF: boolean = false ; Para apagar una función.</p>
</li>
<li>
<p>const ONoFF:boolean = true ; Encender o apagar una función.</p>
</li>
<li>
<p>const TOGGLE:boolean = false ; Para realizar el toggle.</p>
</li>
<li>
<p>const SUBIR: boolean = true ; Indica que la escalera debe subir.</p>
</li>
<li>
<p>const BAJAR: boolean = false ; Indica que la escalera debe bajar.</p>
</li>
<li>
<p>const STOP: boolean = true ; Indica que la escalera debe parar.</p>
</li>
</ul>
<h2 id="variables">Variables</h2>
<ul>
<li>var personas: integer = 1 ; Variable para el conteo de personas.</li>
</ul>
<h2 id="señales">Señales</h2>
<ul>
<li>
<p>event siRojo ; Señal que activa la luz roja.</p>
</li>
<li>
<p>event siVerde ; Señal que activa la luz verde.</p>
</li>
</ul>
<h2 id="capturas-de-los-diagramas">Capturas de los diagramas</h2>
<h2 id="región-principal">Región principal</h2>
<p><img src="https://lh6.googleusercontent.com/ywEhhxOVh8BSxWREv_cr6Yb9Cl86DaeMyhH7tOIAHdCLa64GLeZ-cDyEE6_uITaVO2mvm-XxVb0IZkLiWdkqHjZzR1Z1KeTG26TpuF_f07HLyXlwtcUxRiNVB7QVZDh0nVyTKPFo" alt=""></p>
<h2 id="región-de-las-luces">Región de las luces</h2>
<p><img src="https://lh4.googleusercontent.com/20BSjHuJaO0HnlWb0ja6XHG22rMqhD2atvUQDx_6eHn1PJ0X9cMs5VQC-8SNVVDhqtvMQhTFhP20IRYz9ScqxajLuC8JyrSBYyVv1Wo0uxB-i-pgdNIGpwI82b_BPotpDMlS3ETh" alt=""></p>

