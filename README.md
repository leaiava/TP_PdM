# TP_PdM
Trabajo Final de la Materia PdM de CESE Co15
### AUTOR:
- L. Arrieta
### Plataforma embebida: 
- EDU-CIAA_NXP
### DEPENDENCIA
- sapi.h
## APLICACION
Sistema de registro de 3 señales analógicas. Mediante comandos recibidos por la *UART_USB* a 1152000 se configura el sistema (frecuencia de muestreo y cantidad de canales). Por la misma UART se transmiten los paquetes con las señales adquiridas. Se utilizan los leds *LED1* y *LED2* de la placa para indicar el estado del dispositivo.

La documentación se realiza con Doxygen.
## DIAGRAMA DE ESTADOS
![Diagrama de Estado](/img/MEF_TPFinal_PdM.jpg)
## LISTA DE ESTADOS
- __STAND_BY:__
  Estado inicial de bajo consumo(no implementado el bajo consumo). Escucha comandos por la UART
- __CONECTADO:__
Conectado con equipo de registro al recibir comando __"HOLA"__
- __CONFIGURANDO:__ 
Acepta comandos para configurar los canales a adquirir y la frecuencia de muestreo.
- __LISTO PARA ADQUIRIR:__
Si tiene configurado algún canal para adquirir y la frecuencia de muestreo pasa solo a este estado
- __ADQUIRIENDO:__
Adquiriendo y enviando por la *UART_USB* según configuracion realizada previamente.
## MODULOS
### mi_uart.c, mi_uart.h
- Modulo que maneja la comunicación por la UART.
- Mediante un enum en *mi_uart.h* se definen los comandos aceptados.

### mi_ADC.c, mi_ADC.h
- Modulo que maneja la MEF y los ADCs.
- Mediante un enum en *mi_ADC.h* se definen los estados del dispositivo

### mi_UI.c,mi_UI.h
- Modulo que maneja la interfaz de usuario.
Lee el estado de la MEF para indicar a través de los leds el estado
- __STAND_BY:__
  Lo indica con un pequeño destello del *LED1*
- __CONECTADO:__
 Lo indica con el *LED1* prendido
- __CONFIGURANDO:__ 
Lo indica con un destello rápido del *LED1*
- __LISTO PARA ADQUIRIR:__
Lo indica con el *LED2* prendido
- __ADQUIRIENDO:__
Lo indica con el *LED2* mayormente prendido y un pequeño destello.

Cuando se recibe un parámetro se contesta con el comando __OK__ y se prende el *LED2* por 1segundo.
Todos los tiempos están definidos en un define en *mi_UI.h* .


