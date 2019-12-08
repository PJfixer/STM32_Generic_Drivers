/* ========================================================================== --
                     copyright, Polytech'Tours, 2016-2016

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
   ...

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: xx.11.2016 - Authors: First and last name
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"
#include "drv/gpio-priv.h"

/**-------------------------------------------------------------------------- --
   Local constants
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Local macros
-- -------------------------------------------------------------------------- */
/** without object */
#define GPIO_PORT_A_BASE  0x40010800 
#define GPIO_PORT_B_BASE  0x40010C00 
#define GPIO_PORT_C_BASE  0x40011000
#define GPIO_PORT_D_BASE  0x40011400
#define GPIO_PORT_E_BASE  0x40011800 
#define GPIO_PORT_F_BASE  0x40011C00 
#define GPIO_PORT_G_BASE  0x40012000 

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
   F_test_gpio

   --------------------------------------------------------------------------
   Purpose:
   Test GPIO driver

   --------------------------------------------------------------------------
   Description:
   This function checks GPIO driver.

   --------------------------------------------------------------------------
   Return value:
     0, in nominal case
     -1, otherwise

-- -------------------------------------------------------------------------- */
int  F_test_gpio  ( void )
{
    /* Local variables */
gpio_config_t conf;
int8_t i = 0;

uint8_t curr_read_PA0 = 0;
uint8_t last_read_PA0 = 0;

uint8_t curr_read_PA13 = 0;
uint8_t last_read_PA13 = 0;


//    /* see reference manual page 36 for GPIO mapping */
F_gpio_init(0,GPIO_PORT_A_BASE);  // init GPIO A to dev0-->  0 = GPIOA

F_gpio_init(1,GPIO_PORT_B_BASE); // init GPIO B to dev1-->  1 = GPIOB

conf.mode = INPUT_MODE; 
conf.cnf = INPUT_PULL_UP_DOWN;

F_gpio_setconfig(0,0,&conf); //set config PA0
F_gpio_setconfig(0,13,&conf); //set config PA13

conf.mode = OUTPUT_MODE_MAX_SPEED_50_MHZ; 
conf.cnf = GENERAL_PURPOSE_OUTPUT_PUSH_PULL;


for(i=0;i<16;i++) // fir GPIO from 0 to 15 set config 
{
    F_gpio_setconfig(1,i,&conf);
}
F_gpio_write       (1,0,1);

i=0;


while(1)
{
    curr_read_PA0 = F_gpio_read(0,0);  // read the current state of PA0
    curr_read_PA13 = F_gpio_read(0,13);  // read the current state of PA13
    
     //manage chenillard "overflow"
    if(i>16) 
    {
        i = 0;
    }
     if(i<0)
    {
        i = 15;
    }
     // end manage chenillard "overflow"
    
    if(last_read_PA0 == 1 && curr_read_PA0 == 0) // if detect failing edge on PA0
    {
        i++;
        
        F_gpio_write(1,i,1); // light the led
        F_gpio_write(1,i-1,0); // shutdown the previous led
    }
    if(last_read_PA13 == 1 && curr_read_PA13 == 0)// if detect failing edge on PA13
    {
        i--;
        F_gpio_write(1,i,1); // light the led
        F_gpio_write(1,i+1,0);// shutdown the previous led
    }
    
    last_read_PA0 = curr_read_PA0; // the current state becomme the last for the next cycle
    last_read_PA13 = curr_read_PA13; // the current state becomme the last for the next cycle
    
   

    
}






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


    /* check GPIO */
    F_test_gpio();
}
