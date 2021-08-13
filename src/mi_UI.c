/*
 * mi_UI.c
 *
 *  Created on: Aug 12, 2021
 *      Author: lea
 */
#include "mi_UI.h"


void UIinicializar(void){
	for (int i=0; i<6 ;i++){
		ledApagar(LEDR + i);
	}
	return;
}

void UIactualizar(mis_estados_t estado){

	static delay_t myDelay;

	switch (estado){

	case ESTADO_STANDBY:{
		ledApagar (LED2);
		if(delayRead(&myDelay)){
			if( ledEstaEncendido(LED1)){
				ledApagar(LED1);
				delayWrite( &myDelay , TIEMPO_APAGADO_STANDBY );
			}
			else {
				ledEncender(LED1);
				delayWrite( &myDelay , TIEMPO_ENCENDIDO_STANDBY );
			}
		}
	}
	break;

	case ESTADO_CONECTADO:{
		ledEncender(LED1);
		ledApagar (LED2);
	}
	break;
	case ESTADO_CONFIGURANDO:{
		ledApagar (LED2);
		if(delayRead(&myDelay)){
			if( ledEstaEncendido(LED1)){
				ledApagar(LED1);
				delayWrite( &myDelay , TIEMPO_DESTELLO_CONFIGURANDO );
			}
			else {
				ledEncender(LED1);
				delayWrite( &myDelay , TIEMPO_DESTELLO_CONFIGURANDO );
			}
		}
	}
	break;
	case ESTADO_LISTO_PARA_ADQUIRIR:{
		ledApagar (LED1);
		ledEncender(LED2);
	}
	break;

	case ESTADO_ADQUIRIENDO:{
		ledApagar (LED1);
			if(delayRead(&myDelay)){
				if( ledEstaEncendido(LED2)){
					ledApagar(LED2);
					delayWrite( &myDelay , TIEMPO_APAGADO_ADQUIRIENDO );
				}
				else {
					ledEncender(LED2);
					delayWrite( &myDelay , TIEMPO_ENCENDIDO_ADQUIRIENDO );
				}
			}
		}
	break;
	default:;
	}
}

static bool_t ledApagar(gpioMap_t LedaApagar ){

	bool_t resp = true;

	if( (LedaApagar<LEDR)||(LedaApagar>LED3))	//!< verifico que sea un Led válido
		return(false);
	resp &= gpioWrite( LedaApagar, OFF );   //!< apago led
	resp &= !gpioRead( LedaApagar );		//!< verifico que se haya apagado
	return(resp);
}

static bool_t ledEncender(gpioMap_t LedaEncender){

	if( (LedaEncender<LEDR)||(LedaEncender>LED3))	//!<verifico que sea un Led válido
		return(false);
	gpioWrite( LedaEncender, ON );				//!<prendo el led
	return( gpioRead(LedaEncender) );	//!< verifico que se haya prendido
}

static bool_t ledEstaEncendido(gpioMap_t Led){

	return( gpioRead(Led) );
}

