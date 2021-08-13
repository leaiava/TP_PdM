/*
 * mi_ADC.c
 *
 *  Created on: Aug 5, 2021
 *      Author: lea
 */

#include "mi_ADC.h"

bool_t adcflag;
static uint16_t value;

void ADCConfigurar(miADC_t* ptrmiADCs){
/* Config ADC0 sample mode */
	 ADC_CLOCK_SETUP_T ADCSetup = {
		ADC_MAX_SAMPLE_RATE,   // ADC Sample rate:ADC_MAX_SAMPLE_RATE = 400KHz
		10,                    // ADC resolution: ADC_10BITS = 10
		0                      // ADC Burst Mode: (true or false)
	 };

	 Chip_ADC_Init( LPC_ADC0, &ADCSetup );
	 /* Disable burst mode */
	 Chip_ADC_SetBurstCmd( LPC_ADC0, DISABLE );
	 /* Set sample rate to 200KHz */
	 Chip_ADC_SetSampleRate( LPC_ADC0, &ADCSetup, ADC_MAX_SAMPLE_RATE/2 );
	 /* Disable all channels */
	 Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH1, DISABLE );
	 Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH1, DISABLE );

	 Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH2, DISABLE );
	 Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH2, DISABLE );

	 Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH3, DISABLE );
	 Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH3, DISABLE );

	 Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH4, DISABLE );
	 Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH4, DISABLE );

/*	ADC_CLOCK_SETUP_T ADCSetup;

	Chip_ADC_Init( LPC_ADC0, &ADCSetup );

	Chip_ADC_SetSampleRate(LPC_ADC0, &ADCSetup, 10000); //hardcodeo la frecuencia en 2000;

	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ptrmiADCs->CH1);	//!< ptrmiADCs->CH1 vale TRUE o FALSE idem a ENABLE o DISABLE
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH1, ENABLE);
//	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH2, ptrmiADCs->CH2);
//	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH2, ENABLE);
//	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH3, ptrmiADCs->CH3);
//	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH3, ENABLE);
//	Chip_ADC_SetBurstCmd(LPC_ADC0, (ptrmiADCs->CH1 || ptrmiADCs->CH2 || ptrmiADCs->CH3));//!< Si uno de los 3 canales esta habilitado, habilito el modo burst
	Chip_ADC_SetBurstCmd(LPC_ADC0, ENABLE);
	// De sapi_adc.c, lo copio como esta en void adcInit( adcInit_t config )
	{
	Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH4, DISABLE );
    Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH4, DISABLE );
    // For aditional ADC Inputs (Pablo Gomez)
    #if BOARD==edu_ciaa_nxp
    Chip_SCU_ADC_Channel_Config( 0, 4 );                      // Revisar codigo
    Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH5, DISABLE ); // Revisar codigo
	#endif
	}
	NVIC_EnableIRQ(ADC0_IRQn);
	*/
}

void ADCinicializarMEF(miADC_t* ptrmiADCs){
	ptrmiADCs->estado = ESTADO_STANDBY;
	ptrmiADCs->CH1 = false;
	ptrmiADCs->CH2 = false;
	ptrmiADCs->CH3 = false;
	ptrmiADCs->frecuencia = 0;
}

void ADCactualizarMEF(miADC_t* ptrmiADCs){
	cmd_t command;

	switch (ptrmiADCs->estado){

	case ESTADO_STANDBY:{

		if (UART_getCmd(&command) ){

			if (command == CMD_HOLA){
				UART_sendCmd(CMD_OK);
				ptrmiADCs->estado = ESTADO_CONECTADO;
			}
			else {
				UART_sendCmd(CMD_NO_OK);
			}
		}
	}
	break;

	case ESTADO_CONECTADO:{

		if (ADClisto(ptrmiADCs))
			ptrmiADCs->estado = ESTADO_LISTO_PARA_ADQUIRIR;

		if (UART_getCmd(&command) ){
			if (command == CMD_CONFIG_INICIAR){
				UART_sendCmd(CMD_OK);
				ptrmiADCs->estado = ESTADO_CONFIGURANDO;
			}
			else {
				UART_sendCmd(CMD_NO_OK);
			}
		}

	}
	break;
	case ESTADO_CONFIGURANDO:{

		if (UART_getCmd(&command) ){
			ADCguardarconfiguracion(ptrmiADCs,command);
			//ADCConfigurar(ptrmiADCs );
		}
	}
	break;
	case ESTADO_LISTO_PARA_ADQUIRIR:{

		if (UART_getCmd(&command) ){
			if (command == CMD_CONFIG_INICIAR){
				UART_sendCmd(CMD_OK);
				ptrmiADCs->estado = ESTADO_CONFIGURANDO;
			}
			else if (command == CMD_ADQUIRIR){
				UART_sendCmd(CMD_OK);
				ptrmiADCs->estado = ESTADO_ADQUIRIENDO;
			}
			else  {
				UART_sendCmd(CMD_NO_OK);
			}
		}
	}
	break;

	case ESTADO_ADQUIRIENDO:{

		if ( delayRead( &(ptrmiADCs->delay)) ){
			ADCadquirir(ptrmiADCs);
		UART_sendPacket(ptrmiADCs->paquete);
		}
/*
		if (ADCLeer(ptrmiADCs))
			UART_sendPacket(ptrmiADCs->paquete);

		if (adcflag){
			adcflag = false;
			ptrmiADCs->paquete.data_CH1 = value;
			UART_sendPacket(ptrmiADCs->paquete);
		}
		*/
		if (UART_getCmd(&command) ){
			if (command == CMD_PARAR){
				ptrmiADCs->estado = ESTADO_LISTO_PARA_ADQUIRIR;
			}
			else {
				UART_sendCmd(CMD_OCUPADO);
			}
		}
	}
	break;
	default:;
	}
}

static void ADCguardarconfiguracion(miADC_t* ptrmiADCs, cmd_t command){
	switch (command) {

	case CMD_CONFIG_CH1_OFF:{
		ptrmiADCs->CH1 = false;
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_CH1_ON:{
		ptrmiADCs->CH1 = true;
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_CH2_OFF:{
		ptrmiADCs->CH2 = false;
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_CH2_ON:{
		ptrmiADCs->CH2 = true;
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_CH3_OFF:{
		ptrmiADCs->CH3 = false;
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_CH3_ON:{
		ptrmiADCs->CH3 = true;
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_FREC_1:{
		ptrmiADCs->frecuencia = 1;
		delayInit( &(ptrmiADCs->delay), FRECUENCIA_MUESTREO_62_5 );
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_FREC_2:{
		ptrmiADCs->frecuencia = 2;
		delayInit( &(ptrmiADCs->delay), FRECUENCIA_MUESTREO_125 );
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_FREC_3:{
		ptrmiADCs->frecuencia = 3;
		delayInit( &(ptrmiADCs->delay), FRECUENCIA_MUESTREO_250 );
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_FREC_4:{
		ptrmiADCs->frecuencia = 4;
		delayInit( &(ptrmiADCs->delay), FRECUENCIA_MUESTREO_500 );
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_FREC_5:{
		ptrmiADCs->frecuencia = 5;
		delayInit( &(ptrmiADCs->delay), FRECUENCIA_MUESTREO_1000 );
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_FREC_6:{
		ptrmiADCs->frecuencia = 6;
		delayInit( &(ptrmiADCs->delay), FRECUENCIA_MUESTREO_2000 );
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_FREC_7:{
		ptrmiADCs->frecuencia = 7;
		delayInit( &(ptrmiADCs->delay), FRECUENCIA_MUESTREO_4000 );
		UART_sendCmd(CMD_OK);
	}
	break;
	case CMD_CONFIG_TERMINAR:{
		ptrmiADCs->estado = ESTADO_CONECTADO;
		UART_sendCmd(CMD_OK);
	}
	break;
	default:
		UART_sendCmd(CMD_NO_OK);
	break;
	}
	return;
}
void ADC0_IRQHandler (void)
{


   // entra, pero solo lee el valor para el CH1

   adcflag = true;
   value++;
//   NVIC_DisableIRQ(ADC0_IRQn);
   Chip_ADC_ReadValue( LPC_ADC0, ADC_CH1, &value );
//   Chip_ADC_ReadValue( LPC_ADC0, ADC_CH2, &value );
//   Chip_ADC_ReadValue( LPC_ADC0, ADC_CH3, &value );
//   NVIC_EnableIRQ(ADC0_IRQn);
}

static bool_t ADCLeer(miADC_t* ptrmiADCs){

	bool_t ret = false;

	if(ptrmiADCs->CH1){
		if (Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH1, ADC_DR_DONE_STAT) == SET){ // Pregunto si termino la conversion
			Chip_ADC_ReadValue( LPC_ADC0, ADC_CH1, &(ptrmiADCs->paquete.data_CH1) );
			ret = true;
		}
	}
	if(ptrmiADCs->CH2){
		if (Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH2, ADC_DR_DONE_STAT) == SET){ // Pregunto si termino la conversion
			Chip_ADC_ReadValue( LPC_ADC0, ADC_CH2, &(ptrmiADCs->paquete.data_CH2) );
			ret = true;
		}
	}if(ptrmiADCs->CH3){
		if (Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH3, ADC_DR_DONE_STAT) == SET){ // Pregunto si termino la conversion
			Chip_ADC_ReadValue( LPC_ADC0, ADC_CH3, &(ptrmiADCs->paquete.data_CH3) );
			ret = true;
		}
	}
	return ret;
}

static void ADCadquirir(miADC_t* ptrmiADCs){
	if(ptrmiADCs->CH1){
		ptrmiADCs->paquete.data_CH1 = adcRead(CH1);
	}
	if(ptrmiADCs->CH2){
		ptrmiADCs->paquete.data_CH2 = adcRead(CH2);
	}
	if(ptrmiADCs->CH3){
		ptrmiADCs->paquete.data_CH3 = adcRead(CH3);
	}

}

static bool_t ADClisto(miADC_t* ptrmiADCs){
	if ( ptrmiADCs->frecuencia == 0 )
		return false;
	if ( ptrmiADCs->CH1 || ptrmiADCs->CH2 || ptrmiADCs->CH3 )
		return true;
	else
		return false;
}
