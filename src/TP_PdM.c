/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * Date: 2021/08/05
 *===========================================================================*/

#include "TP_PdM.h"


int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   UART_inicializar();

   miADC_t miADCs;

   /*!
    * Hago que el SysTick interrumpa cada 0,1mS en vez de 1mS, para poder tener una frecuencia
    * de muestreo de 5KHz que equivale a 0,2mS
    */
   tickPowerSet( OFF );
   SysTick_Config( SystemCoreClock / 10000 );
   tickPowerSet( ON );
/*!
 * Inicializo la UI.
 * Inicializo la MEF que gobierna los estados.
 */
   UIinicializar();
   ADCinicializarMEF( &miADCs );

/*!
 * SuperLoop donde actualizo la MEF general y la UI.
 */
   while( true ) {

	   ADCactualizarMEF(&miADCs);

	   UIactualizar(&miADCs);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
