/*
Recomendacion de Gemini para las funciones de botones
## ## El Rol de Cada Input

1.  **Potenciómetro:** Es ideal para ajustes **analógicos** o **incrementales**. Su función será siempre **ajustar un valor**.
2.  **Botón 1 ("MODE"):** Será tu botón **global** principal. Su única misión es **cambiar de aplicación**.
3.  **Botón 2 ("OK / SELECT"):** Será el botón de **acción principal** dentro de cada app.
4.  **Botón 3 ("UP / +"):** Será un botón **contextual** para **aumentar** un valor o navegar hacia arriba.
5.  **Botón 4 ("DOWN / -"):** Será un botón **contextual** para **disminuir** un valor o navegar hacia abajo.

---
## ## Funcionamiento Global del Dispositivo

### ### Cambiar de Aplicación

* **Pulsación corta del botón "MODE":** Rota entre las aplicaciones en un ciclo definido: `Reloj -> Pomodoro -> Alarma -> Spotify -> Reloj...`
    * El `AppManager` se encargará de esta lógica en su método `handleInputs()`. Cada vez que se presiona "MODE", simplemente cambia el valor de `_activeApp` a la siguiente en la lista.

---
## ## Funcionamiento Contextual (Dentro de Cada App)

Aquí es donde tu `AppManager` delega el manejo de los inputs a la aplicación activa.

### ### 1. App: Reloj y Temperatura ⌚
* **Función Principal:** Solo mostrar información.
* **Potenciómetro:** Sin función activa.
* **Botón OK / SELECT:** Entra al modo "Ajustar Alarma" (una transición rápida a la app de Alarma).
* **Botones UP / DOWN:** Sin función activa.

### ### 2. App: Pomodoro 🍅
* **Función Principal:** Gestionar la sesión.
* **Potenciómetro:** Sin función activa.
* **Botón OK / SELECT:** Actúa como tu `buttonStartPause()`. Inicia, pausa o reanuda la sesión.
* **Botones UP / DOWN:** El **botón UP** actúa como `buttonSkip()`. El botón DOWN no tiene función.
    * **Pulsación larga en OK / SELECT:** Podría abrir un menú para re-configurar la sesión actual (llamar a `setUpSession`).

### ### 3. App: Alarma Despertador ⏰
* **Función Principal:** Configurar y gestionar la alarma.
* **Potenciómetro:** En el modo de ajuste, **modifica el valor seleccionado** (horas o minutos) de forma rápida.
* **Botón OK / SELECT:** Tiene varios roles:
    * Desde la vista principal, entra al modo "Ajustar Alarma".
    * Dentro del modo de ajuste, **cambia el foco** entre horas y minutos.
    * Cuando la alarma está sonando, actúa como **"Snooze"**.
* **Botones UP / DOWN:**
    * Dentro del modo de ajuste, **aumentan/disminuyen** el valor seleccionado (si no se usa el potenciómetro).
    * Cuando la alarma está sonando, el **botón DOWN** actúa como **"Stop"**.

### ### 4. App: Spotify 🎵
* **Función Principal:** Controlar la reproducción.
* **Potenciómetro:** Controla el **volumen**.
* **Botón OK / SELECT:** Actúa como **Play / Pausa**.
* **Botones UP / DOWN:** Actúan como **Canción Siguiente / Canción Anterior**.

Este diseño jerárquico es potente porque le da al usuario un modelo mental claro: el botón "MODE" es para moverse *entre* aplicaciones, y los otros controles funcionan *dentro* de la aplicación activa. Es un sistema escalable y fácil de entender.



*/