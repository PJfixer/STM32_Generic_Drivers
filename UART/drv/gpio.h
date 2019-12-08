 /* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: gpio.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   STM32 GPIO driver data that can be shared by application and basic software.

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 21.11.2014 - Authors: Name / Name
   + first version

-- ========================================================================== */

#ifndef D_GPIO_H
#define D_GPIO_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */
#ifndef C_GPIO_NB
#define C_GPIO_NB            7
#endif




/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */



	/**------------------------------------------------------------------ */

 typedef enum {
	 // input mode
     ANALOG_MODE = 0x00,
     FLOATING_INPUT = 0x01,
     INPUT_PULL_UP_DOWN = 0x02,
     RESERVED = 0x03,
	 //output mode (MODE[1:0] > 00):
	 GENERAL_PURPOSE_OUTPUT_PUSH_PULL = 0x00,
	 GENERAL_PURPOSE_OUTPUT_OPEN_DRAIN = 0x01,
	 ALTERNATE_FUNCTION_OUTPUT_PUSH_PULL = 0x02,
	 ALTERNATE_FUNCTION_OUTPUT_OPEN_DRAIN = 0x03
	 
 }gpio_cnf_t; // Doc ID 16188 Rev 4 page 110

	/**------------------------------------------------------------------ */

 typedef enum {
      INPUT_MODE = 0x00,
	  OUTPUT_MODE_MAX_SPEED_10_MHZ = 0x01,
	  OUTPUT_MODE_MAX_SPEED_2_MHZ = 0x02,
	  OUTPUT_MODE_MAX_SPEED_50_MHZ = 0x03
 }gpio_mode_t; // Doc ID 16188 Rev 4 page 110

	/**------------------------------------------------------------------ */
 
typedef struct
{
	gpio_cnf_t cnf;
	gpio_mode_t mode;
	
} gpio_config_t;


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
/** without object */


#endif /* D_GPIO_H */
