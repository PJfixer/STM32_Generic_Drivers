/* ========================================================================== --
                     copyright, Polytech'Tours, 2013-2013

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: main.c

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Main file of UART and GPIO drivers

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 22.11.2013 - Authors: Name / Name
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"
#include "drv/uart-priv.h"
#include "drv/gpio-priv.h"
#include "drv/rcc-priv.h"
#include "drv/afio-priv.h"

/**-------------------------------------------------------------------------- --
   Local constants
-- -------------------------------------------------------------------------- */
/** without object */
#define GPIO_PORT_A_BASE  0x40010800 

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
rcc_dev_t	G_rcc;
afio_dev_t  G_afio;

/**-------------------------------------------------------------------------- --
   Static variables
-- -------------------------------------------------------------------------- */
/** without object */


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

/* -------------------------------------------------------------------------- --
   FUNCTION:
   F_test_uart

   --------------------------------------------------------------------------
   Purpose:
   Test UART driver

   --------------------------------------------------------------------------
   Description:
   This function checks UART driver.

   --------------------------------------------------------------------------
   Return value:
     0, in nominal case
     -1, otherwise

-- -------------------------------------------------------------------------- */
int  F_test_uart  ( void )
{
    uint8_t ret = 0;
    uart_config_t config;    
    config.bauderate = 115200;
    config.bitstop = ONE_BITSTOP;
    config.data_length = DATA_8;
    config.parity = NONE;

    F_usart_init(USART_1, 0x40013800);
    F_usart_setconfig(USART_1, &config);
    
    ret = F_usart_getc(USART_1);
    
    F_usart_putc(USART_1,'P');
    
    F_usart_Write(USART_1,"hello world \n");

    /* Return success code */
    return 0;
}



/**========================================================================== --
   Public functions
-- ========================================================================== */


/* -------------------------------------------------------------------------- --
   FUNCTION:
   main

   --------------------------------------------------------------------------
   Purpose:
   Main function

   --------------------------------------------------------------------------
   Description:
   This function is the entry point of the software.

   --------------------------------------------------------------------------
   Return value:
     0

-- -------------------------------------------------------------------------- */
 int  main  ( void )
 {
    /* Local variables */
    /** without object */
    
    gpio_config_t conf; // gpio conf here (C90)
    
    G_rcc.base_address  = (rcc_t *)0x40021000;
    G_afio.base_address = (afio_t *)0x40010000;
    
    /* Enable clock for Alternate function I/O */
    G_rcc.base_address->APB2ENR |= 0x01;        /* RCC_APB2ENR_AFIOEN */

    /* Disable USART1 remap */
    /* It controls the mapping of USART1 TX and RX alternate functions on the GPIO ports */
    /* USART1.TX = PA.9, USART1.RX = PA.10 */
    G_afio.base_address->MAPR   &= ~(1 << 2);  

    // set USART pins  
  F_gpio_init(0,GPIO_PORT_A_BASE);  // init GPIO A to dev0-->  0 = GPIOA
   
   conf.mode = INPUT_MODE; 
   conf.cnf = FLOATING_INPUT;
   F_gpio_setconfig(0,10,&conf); //set config PA10 floating input for RX */
   
   conf.mode = OUTPUT_MODE_MAX_SPEED_50_MHZ; 
   conf.cnf = ALTERNATE_FUNCTION_OUTPUT_PUSH_PULL;
   F_gpio_setconfig(0,9,&conf); //set config PA9 ALTERNATE_FUNCTION_OUTPUT_PUSH_PULL for RX */
    
    
    /* Enable clock for USART1 */
    G_rcc.base_address->APB2ENR |= 0x01 << 14; /* RCC_APB2ENR_USART1EN; */

    /* Check UART */
    F_test_uart();
    return 0;
}
