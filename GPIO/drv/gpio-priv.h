/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: gpio-priv.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   STM32 GPIO driver data and prototype that shall be accessed only by basic 
   software.

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 21.11.2014 - Authors: Name / Name
   + first version

-- ========================================================================== */

#ifndef D_GPIOPRIV_H
#define D_GPIOPRIV_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "gpio.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */

/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */
/** see reference manual page 99 */
typedef struct
{
  reg32_t GPIO_CRL;     /* Port configuration register low */
  reg32_t GPIO_CRH;
  reg32_t GPIO_IDR;
  reg32_t GPIO_ODR;
  reg32_t GPIO_BSRR;
  reg32_t GPIO_BRR;
  reg32_t GPIO_LCKR;

} gpio_t;       /* GPIO registers description */

    /** ------------------------------------------------------------------ */

typedef struct
{
  gpio_t * reg;

} gpio_dev_t;   /* GPIO device data */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
int32_t  F_gpio_init        ( uint32_t i_id, addr_t base_address );
int32_t  F_gpio_setconfig   ( uint32_t i_id, uint32_t i_channel_id, gpio_config_t * i_config);
int32_t  F_gpio_write       ( uint32_t i_id, uint32_t i_channel_id, uint32_t value);
int32_t  F_gpio_read        ( uint32_t i_id, uint32_t i_channel_id );    


#endif /* D_GPIOPRIV_H */
