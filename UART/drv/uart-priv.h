/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: uart-priv.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Private data and prototype of STM32 UART driver.

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 28.11.2014 - Authors: Name / Name
   + first version

-- ========================================================================== */

#ifndef D_UART_PRIV_H
#define D_UART_PRIV_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "uart.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */
#ifndef C_UART_NB
#define C_UART_NB            3
#endif

/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */
/** see reference manual page 576 */
typedef struct {
    reg32_t USART_SR;
    reg32_t USART_DR;
    reg32_t USART_BRR;
    reg32_t USART_CR1;
    reg32_t USART_CR2;
    reg32_t USART_CR3;
    reg32_t USART_GTPR;
}uart_t;

typedef struct
{
  uart_t * reg;

} uart_dev_t; 

/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
//int32_t  F_uart_init        ( uint32_t i_id, addr_t base_address, ???? );
//int32_t  F_uart_setconfig   ( uint32_t i_id, uart_config_t * i_config );
//int32_t  F_uart_putc        ( uint32_t i_id, uint32_t value );
//int32_t  F_uart_getc        ( uint32_t i_id );


#endif /* D_UART_PRIV_H */
