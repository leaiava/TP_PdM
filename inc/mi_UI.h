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

#define TIEMPO_ENCENDIDO_STANDBY		50
#define TIEMPO_APAGADO_STANDBY			1000
#define TIEMPO_DESTELLO_CONFIGURANDO	100
#define TIEMPO_ENCENDIDO_ADQUIRIENDO	800
#define TIEMPO_APAGADO_ADQUIRIENDO		100

/*!
 * @Brief Apaga todos los leds.
 *
 */
void UIinicializar(void);

void UIactualizar(mis_estados_t estado);

/*!
 * @Brief Apagar un led en particular
 * Recibe led a apagar
 * Devuelve 1 si pudo apagar el led
 * Devuelve 0 en caso de error
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
static bool_t ledEstaEncendido(gpioMap_t Led);

#endif /* _UI_H_ */
