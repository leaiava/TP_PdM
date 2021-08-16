# TP_PdM
Trabajo Final de la Materia PdM de CESE Co15
### Plataforma embebida: 
EDU-CIAA_NXP
### DEPENDENCIA
sapi.h
## APLICACION
Sistema de registro de 3 señales analógicas. Mediante comandos recibidos por la UART_USB a 1152000 se configura el sistema (frecuencia de muestreo y cantidad de canales). Por la misma UART se transmiten los paquetes con las señales adquiridas. Se utilizan los leds LED1 y LED2 de la placa para indicar el estado del dispositivo.
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
Adquiriendo y enviando por la UART_USB según configuracion realizada previamente.
