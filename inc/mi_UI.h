/*
 * mi_UI.h
 *
 *  Created on: Aug 12, 2021
 *      Author: lea
 */

#ifndef _MI_UI_H_
#define _MI_UI_H_

#include "sapi.h"
#include "mi_ADC.h"
/*
 * Defines para manejar los tiempos de encedido/apagado de los leds
 * Los siguientes tiempos están expresados en mS*10
 */
#define TIEMPO_ENCENDIDO_STANDBY		500
#define TIEMPO_APAGADO_STANDBY			10000
#define TIEMPO_DESTELLO_CONFIGURANDO	1000
#define TIEMPO_ENCENDIDO_ADQUIRIENDO	5000
#define TIEMPO_APAGADO_ADQUIRIENDO		1000
#define TIEMPO_COMANDO_RECIBIDO			10000

/*!
 * @Brief Apaga todos los leds.
 *
 */
void UIinicializar(void);

/*!
 * @Brief Actualiza la MEF que maneja la interfaz de usuario
 * Utiliza los mimos estados que utiliza la MEF del ADC
 * @param ptrmiADCs Estructura que tiene toda la información del ADC
 *
 */
void UIactualizar(miADC_t* ptrmiADCs);

/*!
 * @Brief Apagar un led en particular
 * @param LedaApagar Recibe led a apagar
 * @return true si pudo apagar el led
 * @return false en caso de error
 */
static bool_t ledApagar(gpioMap_t LedaApagar );

/*!
 * @Brief Encender un led en particular
 * @param LedaEncender Led a encender
 * @return true si pudo encender el led
 * @return false en caso de error
 */
static bool_t ledEncender(gpioMap_t LedaEncender);

/*!
 * @Brief Verifica si un led en particular esta encendido
 * @param Led Led a verificar
 * @return true si el led esta encendido
 * @return false si el led esta apagado
 */
static bool_t ledLeer(gpioMap_t Led);

#endif /* _UI_H_ */
