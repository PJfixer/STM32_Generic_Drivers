/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: uart.c

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Provide functions to manage the STM32 UART device.
   Note : See STM32F100xx reference manual page 576

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 28.11.2014 - Authors: Name / Name
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "drv/uart-priv.h"


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
uart_dev_t    G_uart[C_UART_NB];

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
   FUNCTION: int32_t  F_usart_init

   --------------------------------------------------------------------------
   Purpose:
   Initialize STM32 USART  device
   

   --------------------------------------------------------------------------
   Description:
   This function initializes the USART 'i_id' with the passed address of the UART peripheral

   --------------------------------------------------------------------------
   Return value:
   0 : succes
   -1 : bad  device id  

-- -------------------------------------------------------------------------- */
int32_t  F_usart_init
(
    uint32_t i_id
   ,addr_t base_address
)
{
    
    if ( i_id >= C_UART_NB ) // if i_id is grater than the currently USART peripheral available on the board
    {
        return -1;
    }
    G_uart[i_id].reg = (uart_t *)base_address; // strore the passed address of the USART peripheral in the G_uart array
    
    /* Return success code */
    return 0;
}


/* -------------------------------------------------------------------------- --
   FUNCTION: int32_t  F_usart_setconfig

   --------------------------------------------------------------------------
   Purpose:
   Set the config on an USART
   

   --------------------------------------------------------------------------
   Description:
   This function set the config of an USART peripheral ( baudrate,parity,stop..)

   --------------------------------------------------------------------------
   Return value:
   0 : succes
   -1 : bad  device id  

-- -------------------------------------------------------------------------- */

int32_t F_usart_setconfig
(
    uint32_t i_id
   ,uart_config_t * i_config
)
{
    reg32_t *reg;
    uint32_t mantis = 0; // mantisse variable for baudrate calculation
    uint32_t fraction = 0; // fraction vriable for baudrate calculation
    
   if ( i_id >= C_UART_NB ) // if i_id is grater than the currently USART peripheral available on the board
    {
        return -1;
    }
    reg = &G_uart[i_id].reg->USART_CR1;  // first we configure the USART_CR1 register
    // set data length // p610
    M_bupdate32((*reg), FIELD_USART_UE, 1); // enable uart
    M_bupdate32((*reg), FIELD_USART_PARITY, i_config->parity); // set parity
    M_bupdate32((*reg), FIELD_USART_M, i_config->data_length); // set data lenght
    M_bupdate32((*reg), FIELD_USART_TE, 1);// enable TX
    M_bupdate32((*reg), FIELD_USART_RE, 1);// enable RX
    
    reg = &G_uart[i_id].reg->USART_CR2;   // then we configure the USART_CR2 register
    
    M_bupdate32((*reg), FIELD_USART_STOP, i_config->bitstop);  // configure stop bit
    
    mantis = _XTAL_ / (16 * i_config->bauderate); // calcul baudrate 
    fraction = _XTAL_ / i_config->bauderate; // calcul baudrate 
    
    reg = &G_uart[i_id].reg->USART_BRR;   // then we configure the USART_BRR register
    M_bupdate32((*reg), FIELD_USART_DIV_MANTISSA,mantis); //  set baudrate  FIELD_USART_DIV_MANTISSA
    M_bupdate32((*reg), FIELD_USART_DIV_FRACTION,fraction); // set baudrate FIELD_USART_DIV_FRACTION
    
    // 
    
    /* Return success code */
    return 0; 
}

/* -------------------------------------------------------------------------- --
   FUNCTION: int32_t  F_usart_putc

   --------------------------------------------------------------------------
   Purpose:
   Write one byte through USART
   

   --------------------------------------------------------------------------
   Description:
   This Function send one caracter passed in parameter through the USART 

   --------------------------------------------------------------------------
   Return value:
   0 : succes
   -1 : bad  device id  

-- -------------------------------------------------------------------------- */

int32_t F_usart_putc(uint32_t i_id,uint8_t data)
{
    reg32_t *reg; 
    
    if ( i_id >= C_UART_NB ) // if i_id is grater than the currently USART peripheral available on the board
    {
        return -1;
    }
    
    reg = &G_uart[i_id].reg->USART_SR;
    
    while(M_bget(*reg,FIELD_USART_TXE) == 0) // while  Transmit data register is not  empty (TXE == 0)
    {
        //wait till Transmit data register  is empty
    }
    
    //then send data 
     reg = &G_uart[i_id].reg->USART_DR;
     *reg = data ;
     
    return 0;
}



/* -------------------------------------------------------------------------- --
   FUNCTION: int32_t  F_usart_getc

   --------------------------------------------------------------------------
   Purpose:
   Read one byte from USART
   

   --------------------------------------------------------------------------
   Description:
   This Function read one byte from the USART 

   --------------------------------------------------------------------------
   Return value:
   0 : succes
   -1 : bad  device id  

-- -------------------------------------------------------------------------- */

int32_t F_usart_getc(uint32_t i_id)
{
    reg32_t *reg; 
    
    if ( i_id >= C_UART_NB ) // if i_id is grater than the currently USART peripheral available on the board
    {
        return -1;
    }
    
    reg = &G_uart[i_id].reg->USART_SR;
    
    while(M_bget(*reg,FIELD_USART_RXNE) == 0) // while no data available
    {
        //wait for incoming data 
    }
    
    //then read & return the data  
     reg = &G_uart[i_id].reg->USART_DR;
   
     
    return *reg ;
}



/* -------------------------------------------------------------------------- --
   FUNCTION:int32_t F_usart_Write

   --------------------------------------------------------------------------
   Purpose: send string or array of bytes
   
   

   --------------------------------------------------------------------------
   Description:
   this fuction send a const char * array passed in argument 

   --------------------------------------------------------------------------
   Return value:
   0 : succes
   -1 : bad  device id  

-- -------------------------------------------------------------------------- */

int32_t F_usart_Write(uint32_t i_id,const char * str) // quick & dirty 
{
    if ( i_id >= C_UART_NB ) // if i_id is grater than the currently USART peripheral available on the board
    {
        return -1;
    }
    while(*str) // for each caracter in str 
    {
            F_usart_putc( i_id,*str++); // call putc with the current caracter index
    }
    return 0;
}



