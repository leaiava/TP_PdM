/*=============================================================================
 * Author: Leandro Arrieta <leandroarrieta@gmail.com>
 * Date: 2021/08/05
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "TP_PdM.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

int main( void )
{
   // ----- Setup -----------------------------------
    // Read clock settings and update SystemCoreClock variable
    //SystemCoreClockUpdate();// Probar si hay que poner esto o no
	boardInit();

//   cyclesCounterConfig(EDU_CIAA_NXP_CLOCK_SPEED);
//  volatile  uint32_t cyclesElapsed = 0;
//  volatile uint32_t usElapsed = 0;
   // Inicializar UART_USB a 115200 baudios
   uartInit( UART_USB, 1152000 );
   adcConfig( ADC_ENABLE );
   miADC_t miADCs;

   UIinicializar();
   ADCinicializarMEF( &miADCs );

   // ----- Repeat for ever -------------------------
   while( true ) {
//	   cyclesCounterReset();
	   ADCactualizarMEF(&miADCs);

	   UIactualizar(miADCs.estado);
//	   cyclesElapsed = cyclesCounterRead();
//	   usElapsed = cyclesCounterToUs(cyclesElapsed);
	  // printf("\r\nMi estado es %d \r\n",miADCs.estado);
      //gpioToggle(LED);
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
