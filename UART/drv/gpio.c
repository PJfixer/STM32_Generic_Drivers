/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: gpio.c

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Provide functions to manage the STM32 GPIO device.
     Note : See STM32F100xx reference manual page 99

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 21.11.2014 - Authors: Name / Name
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "drv/gpio-priv.h"


/**-------------------------------------------------------------------------- --
   Local constants
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Local macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Local types
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Static variables
-- -------------------------------------------------------------------------- */
gpio_dev_t    G_gpio[C_GPIO_NB];


/**-------------------------------------------------------------------------- --
   Private functions prototypes
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Private functions prototypes
-- -------------------------------------------------------------------------- */
/** without object */


/**========================================================================== --
   Private functions
-- ========================================================================== */
/** without object */


/**========================================================================== --
   Public functions
-- ========================================================================== */

/* -------------------------------------------------------------------------- --
   FUNCTION:
   F_gpio_init

   --------------------------------------------------------------------------
   Purpose:
   Initialize STM32 GPIO device

   --------------------------------------------------------------------------
   Description:
   This function initializes the GPIO 'i_id' in function of parameters.
     
   --------------------------------------------------------------------------
   Return value:
   0, in nominal case
     ...

-- -------------------------------------------------------------------------- */
int32_t  F_gpio_init(
    uint32_t    i_id            /* device identifier  */
   ,addr_t      i_base_address  /* base address of GPIO registers */
)
{
    /* Local variables */
    // ...
    
    /* Interrupt processing if device identifier is out of range */
    if ( i_id >= C_GPIO_NB )
    {
        return -1;
    }

    /* Set base address of xps_gpio */
    G_gpio[i_id].reg = (gpio_t *)i_base_address;

    /* Return success code */
    return 0;
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   F_gpio_setconfig

   --------------------------------------------------------------------------
   Purpose:
   Configure STM32 GPIO device

   --------------------------------------------------------------------------
   Description:
   This function configures the channel 'i_channel_id' of GPIO 'i_id' in 
     function of 'i_config' data.
     
   --------------------------------------------------------------------------
   Return value:
   0, in nominal case
     ...

-- -------------------------------------------------------------------------- */
int32_t  F_gpio_setconfig
(
    uint32_t            i_id            /* device identifier  */
   ,uint32_t            i_channel_id    /* channel identifier */
   ,gpio_config_t *     i_config        /* configuration data */
)
{
	
    /* Local variables */
	reg8_t val ;
	reg8_t msb;
	reg8_t lsb; 
	 /*End Local variables */
     
      if ( i_id >= C_GPIO_NB )
    {
        return -1; // if ID is greater than available GPIO port
    }

	
	if(i_channel_id <= 7) // configure gpio 0 to 7
	{
		msb = 3+(i_channel_id*4); // determine the proper msb
		lsb = 0+(i_channel_id*4); // determine the proper lsb
		
		val = (i_config->mode|((i_config->cnf<<2))) ; // set up 4 bits mask CNF|MODE before write it 
		
		G_gpio[i_id].reg->GPIO_CRL = M_field_reg(G_gpio[i_id].reg->GPIO_CRL
												,(msb)
												,(lsb)
												,val
												);
	}
	else // configure gpio 8 to 15
	{
		msb = 3+((i_channel_id*4)-32); // determine the proper msb
		lsb = 0+((i_channel_id*4)-32); // determine the proper lsb
		
		val = (i_config->mode|((i_config->cnf<<2))) ; // set up 4 bits mask CNF|MODE before write it 
		
		G_gpio[i_id].reg->GPIO_CRH = M_field_reg(G_gpio[i_id].reg->GPIO_CRH
												,(msb)
												,(lsb)
												,val
												);
	}


	 
	 
	  
    /* Return success code */
    return 0;
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   F_gpio_write

   --------------------------------------------------------------------------
   Purpose:
   Set discrete state

   --------------------------------------------------------------------------
   Description:
   This function sets the output 'i_channel' of GPIO 'i_id' to 'i_state'.
     
   --------------------------------------------------------------------------
   Return value:
   Résultat de l'ecriture

-- -------------------------------------------------------------------------- */
int32_t F_gpio_write
(
    uint32_t    i_id                /* device identifier  */
   ,uint32_t    i_channel_id        /* channel identifier */
   ,uint32_t    i_state             /* value to set on output channel */
)
{
 


    /* Local variables */
	reg8_t msb;
	reg8_t lsb; 
	 /*End Local variables */
	
    	 if ( i_id >= C_GPIO_NB )
    {
        return -1; // if ID is greater than available GPIO port
    }
	 if ( i_channel_id >= 15 )
    {
        return -2; // if i_channel_id is greater than available GPIOs 
    }
	
		msb = (i_channel_id); // determine the proper msb
		lsb = (i_channel_id); // determine the proper lsb
		
		G_gpio[i_id].reg->GPIO_ODR = M_field_reg(G_gpio[i_id].reg->GPIO_ODR  //write i_state value on the proper i_channel_id GPIO 
												,(msb)
												,(lsb)
												,i_state
												);
	



	 
	 
	  
    /* Return success code */
    return 0;

}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   F_gpio_read

   --------------------------------------------------------------------------
   Purpose:
   Get discrete state

   --------------------------------------------------------------------------
   Description:
   This function returns the state of channel 'i_channel_id' of GPIO 'i_id'.

   --------------------------------------------------------------------------
   Return value:
     0 or 1, discrete state
   -1, if failed

-- -------------------------------------------------------------------------- */
int32_t  F_gpio_read
(
    uint32_t    i_id            /* device identifier  */
   ,uint32_t    i_channel_id    /* channel identifier */
)
{
 
    /* Local variables */
	reg8_t msb;
	reg8_t lsb; 
	 /*End Local variables */
	
      if ( i_id >= C_GPIO_NB )
    {
        return -1; // if ID is greater than available GPIO port
    }
	 if ( i_channel_id >= 15 )
    {
        return -2; // if i_channel_id is greater than available GPIOs 
    }

	
    msb = (i_channel_id); // determine the proper msb
    lsb = (i_channel_id); // determine the proper lsb
    
    return M_field_get(G_gpio[i_id].reg->GPIO_IDR,msb,lsb); // return the value of i_channel_id GPIO
	



	 
	 
	 
}
