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

```
typedef enum {
	CMD_HOLA = '1', //!< Iniciar la comunicación. - 1
	CMD_OK, //!< Se interpreto bien el comando recibido - 2
	CMD_NO_OK, //!< No se interpreto el comando recibido - 3
	CMD_CHAU, //!< Terminar comunicacion - 4
	CMD_CONFIG_INICIAR, //!< Inicia configuracion - 5
	CMD_CONFIG_TERMINAR, //!< Termina configuracion - 6
	CMD_CONFIG_CH1_ON, //!< Canal 1 habilitdo - 7
	CMD_CONFIG_CH1_OFF, //!< Canal 1 deshabilitado - 8
	CMD_CONFIG_CH2_ON, //!< Canal 2 habilitdo - 9
	CMD_CONFIG_CH2_OFF, //!< Canal 2 deshabilitado - :
	CMD_CONFIG_CH3_ON, //!< Canal 3 habilitdo - ;
	CMD_CONFIG_CH3_OFF, //!< Canal 3 deshabilitado - <
	CMD_CONFIG_FREC_1, //!< Configura ADC con frecuencia 1 - =
	CMD_CONFIG_FREC_2, //!< Configura ADC con frecuencia 2 - >
	CMD_CONFIG_FREC_3, //!< Configura ADC con frecuencia 3 - ?
	CMD_CONFIG_FREC_4, //!< Configura ADC con frecuencia 4 - @
	CMD_CONFIG_FREC_5, //!< Configura ADC con frecuencia 5 - A
	CMD_CONFIG_FREC_6, //!< Configura ADC con frecuencia 6 - B
	CMD_CONFIG_FREC_7, //!< Configura ADC con frecuencia 7 - C
	CMD_ADQUIRIR, //!< Inicia la adquisición - D
	CMD_PARAR, //!< Para la adquisición - E
	CMD_OCUPADO, //!< Respuesta si no puede atender un comando - F
	CMD_LEER_ESTADO, //!< Pregunta en que estado se encuentra - G
}cmd_t;
```
#### Principales funciones
```
void UART_inicializar(void);
bool_t UART_getCmd(cmd_t* command);
void UART_sendCmd(cmd_t command);
void UART_sendPacket(packet_t paquete);
```

### mi_ADC.c, mi_ADC.h
- Modulo que maneja la MEF y los ADCs.
- Mediante un enum en *mi_ADC.h* se definen los estados del dispositivo
```
typedef enum {
	ESTADO_STANDBY, //!< Estado inicial luego del reset
	ESTADO_CONECTADO, //!< Cuando establece conexión con un dispositivo externo
	ESTADO_CONFIGURANDO, //!< Estado para configurar cantidad de canales y frecuencia de sampling
	ESTADO_LISTO_PARA_ADQUIRIR, //!< Si tiene configurado una frecuencia de muestreo y canales a usar queda en este estado
	ESTADO_ADQUIRIENDO //!< Adquiriendo y enviando datos por la UART.
}mis_estados_t;
```
#### Principales funciones y estructuras
```
typedef struct{
	mis_estados_t estado; //!< Variable que contiene el estado del dispositivo
	bool_t	CH1; //!< Indica si el canal 1 esta encendido (TRUE) o apagado (FALSE)
	bool_t	CH2; //!< Indica si el canal 2 esta encendido (TRUE) o apagado (FALSE)
	bool_t	CH3; //!< Indica si el canal 3 esta encendido (TRUE) o apagado (FALSE)
	uint32_t frecuencia; //!< Indica la frecuencia de muestreo a utilizar
	packet_t paquete; //!< Variable para guardar los datos de los ADCs
	delay_t delay; //!< Guardo el delay necesario para obtener la frecuenia de muestreo configurada
	bool_t FlagComandoRecibido; //!< Flag que indica en TRUE cuando llegó un comando válido
}miADC_t;

void ADCinicializarMEF(miADC_t* ptrmiADCs);
void ADCactualizarMEF(miADC_t* ptrmiADCs);
static bool_t ADClisto(miADC_t* ptrmiADCs);
static void ADCguardarconfiguracion(miADC_t* ptrmiADCs, cmd_t command);
static void ADCadquirir(miADC_t* ptrmiADCs);
```

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


