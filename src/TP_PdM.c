/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * Date: 2021/08/05
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "TP_PdM.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   uartInit( UART_USB, 1152000 );
   adcConfig( ADC_ENABLE );

   miADC_t miADCs;

   /*!
    * Hago que el SysTick interrumpa cada 0,1mS para poder tener una frecuencia
    * de muestreo de 5KHz que equivale a 0,2mS
    */
   tickPowerSet( OFF );
   SysTick_Config( SystemCoreClock / 10000 );
   tickPowerSet( ON );

   UIinicializar();
   ADCinicializarMEF( &miADCs );

   // ----- Repeat for ever -------------------------
   while( true ) {

	   ADCactualizarMEF(&miADCs);

	   UIactualizar(&miADCs);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
