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
   Public data and prototype of STM32 UART driver.

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 28.11.2014 - Authors: Name / Name
   + first version

-- ========================================================================== */

#ifndef D_UART_H
#define D_UART_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */
/** without object */
#define _XTAL_ 8000000

/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
// CUSTOM FILED

#define FIELD_USART_PARITY 10,9 // custom field with [FIELD_UART_PCE,FIELD_UART_PS]

// SR

#define FIELD_USART_CTS       9,9 /*     CTS: CTS flag
                                        This bit is set by hardware when the nCTS input toggles, if the CTSE bit is set. It is cleared
                                        by software (by writing it to 0). An interrupt is generated if CTSIE=1 in the USART_CR3
                                        register.
                                        0: No change occurred on the nCTS status line
                                        1: A change occurred on the nCTS status line
                                        This bit is not available for UART4 & UART5.*/

#define FIELD_USART_LBD       8,8 /*     LBD: LIN break detection flag
                                        This bit is set by hardware when the LIN break is detected. It is cleared by software (by
                                        writing it to 0). An interrupt is generated if LBDIE = 1 in the USART_CR2 register.
                                        0: LIN Break not detected
                                        1: LIN break detected
                                        Note: An interrupt is generated when LBD=1 if LBDIE=1*/ 

#define FIELD_USART_TXE       7,7 /*     TXE: Transmit data register empty
                                        This bit is set by hardware when the content of the TDR register has been transferred into
                                        the shift register. An interrupt is generated if the TXEIE bit =1 in the USART_CR1 register. It
                                        is cleared by a write to the USART_DR register.
                                        0: Data is not transferred to the shift register
                                        1: Data is transferred to the shift register)
                                        Note: This bit is used during single buffer transmission.*/

#define FIELD_USART_TC        6,6 /*     TC: Transmission complete
                                        This bit is set by hardware if the transmission of a frame containing data is complete and if
                                        TXE is set. An interrupt is generated if TCIE=1 in the USART_CR1 register. It is cleared by a
                                        software sequence (a read from the USART_SR register followed by a write to the
                                        USART_DR register). The TC bit can also be cleared by writing a '0' to it. This clearing
                                        sequence is recommended only for multibuffer communication.
                                        0: Transmission is not complete
                                        1: Transmission is complete*/

#define FIELD_USART_RXNE      5,5 /*     RXNE: Read data register not empty
                                        This bit is set by hardware when the content of the RDR shift register has been transferred to
                                        the USART_DR register. An interrupt is generated if RXNEIE=1 in the USART_CR1 register.
                                        It is cleared by a read to the USART_DR register. The RXNE flag can also be cleared by
                                        writing a zero to it. This clearing sequence is recommended only for multibuffer
                                        communication.
                                        0: Data is not received
                                        1: Received data is ready to be read.*/

#define FIELD_USART_IDLE      4,4 /*     IDLE: IDLE line detected
                                        This bit is set by hardware when an Idle Line is detected. An interrupt is generated if the
                                        IDLEIE=1 in the USART_CR1 register. It is cleared by a software sequence (an read to the
                                        USART_SR register followed by a read to the USART_DR register).
                                        0: No Idle Line is detected
                                        1: Idle Line is detected
                                        Note: The IDLE bit will not be set again until the RXNE bit has been set itself (i.e. a new idle
                                        line occurs).*/ 

#define FIELD_USART_OE        3,3 /*     ORE: Overrun error
                                        This bit is set by hardware when the word currently being received in the shift register is
                                        ready to be transferred into the RDR register while RXNE=1. An interrupt is generated if
                                        RXNEIE=1 in the USART_CR1 register. It is cleared by a software sequence (an read to the
                                        USART_SR register followed by a read to the USART_DR register).
                                        0: No Overrun error
                                        1: Overrun error is detected
                                        Note: When this bit is set, the RDR register content will not be lost but the shift register will be
                                        overwritten. An interrupt is generated on ORE flag in case of Multi Buffer
                                        communication if the EIE bit is set.*/

#define FIELD_USART_NE        2,2 /*     NE: Noise error flag
                                        This bit is set by hardware when noise is detected on a received frame. It is cleared by a
                                        software sequence (an read to the USART_SR register followed by a read to the
                                        USART_DR register).
                                        0: No noise is detected
                                        1: Noise is detected
                                        Note: This bit does not generate interrupt as it appears at the same time as the RXNE bit
                                        which itself generates an interrupting interrupt is generated on NE flag in case of Multi
                                        Buffer communication if the EIE bit is set.*/

#define FIELD_USART_FE        1,1 /*     FE: Framing error
                                        This bit is set by hardware when a de-synchronization, excessive noise or a break character
                                        is detected. It is cleared by a software sequence (an read to the USART_SR register
                                        followed by a read to the USART_DR register).
                                        0: No Framing error is detected
                                        1: Framing error or break character is detected
                                        Note: This bit does not generate interrupt as it appears at the same time as the RXNE bit
                                        which itself generates an interrupt. If the word currently being transferred causes both
                                        frame error and overrun error, it will be transferred and only the ORE bit will be set.
                                        An interrupt is generated on FE flag in case of Multi Buffer communication if the EIE bit
                                        is set.*/

#define FIELD_USART_PE        0,0 /*     PE: Parity error
                                        This bit is set by hardware when a parity error occurs in receiver mode. It is cleared by a
                                        software sequence (a read to the status register followed by a read to the USART_DR data
                                        register). The software must wait for the RXNE flag to be set before clearing the PE bit.
                                        An interrupt is generated if PEIE = 1 in the USART_CR1 register.
                                        0: No parity error
                                        1: Parity error*/


// CR1 p611
#define FIELD_USART_UE       13,13 /*    UE: USART enable
                                        When this bit is cleared the USART prescalers and outputs are stopped and the end of the
                                        current
                                        byte transfer in order to reduce power consumption. This bit is set and cleared by software.
                                        0: USART prescaler and outputs disabled
                                        1: USART enabled */
                                        
#define FIELD_USART_M        12,12 /*    M: Word length
                                        This bit determines the word length. It is set or cleared by software.
                                        0: 1 Start bit, 8 Data bits, n Stop bit
                                        1: 1 Start bit, 9 Data bits, n Stop bit
                                        Note: The M bit must not be modified during a data transfer (both transmission and reception)*/
                                        
#define FIELD_USART_WAKE     11,11 /*    WAKE: Wakeup method
                                        This bit determines the USART wakeup method, it is set or cleared by software.
                                        0: Idle Line
                                        1: Address Mark */
                                         
#define FIELD_USART_PCE      10,10 /*    PCE: Parity control enable
                                        This bit selects the hardware parity control (generation and detection). When the parity
                                        control is enabled, the computed parity is inserted at the MSB position (9th bit if M=1; 8th bit
                                        if M=0) and parity is checked on the received data. This bit is set and cleared by software.
                                        Once it is set, PCE is active after the current byte (in reception and in transmission).
                                        0: Parity control disabled
                                        1: Parity control enabled */
#define FIELD_USART_PS       9,9 /*      PS: Parity selection
                                        This bit selects the odd or even parity when the parity generation/detection is enabled (PCE
                                        bit set). It is set and cleared by software. The parity will be selected after the current byte.
                                        0: Even parity
                                        1: Odd parity*/

#define FIELD_USART_PEIE     8,8 /*      PEIE: PE interrupt enable
                                        This bit is set and cleared by software.
                                        0: Interrupt is inhibited
                                        1: A USART interrupt is generated whenever PE=1 in the USART_SR register*/
#define FIELD_USART_TXEIE    7,7 /*      TXEIE: TXE interrupt enable
                                        This bit is set and cleared by software.
                                        0: Interrupt is inhibited
                                        1: A USART interrupt is generated whenever TXE=1 in the USART_SR register*/
                                        
#define FIELD_USART_TCIE     6,6 /*      TCIE: Transmission complete interrupt enable
                                        This bit is set and cleared by software.
                                        0: Interrupt is inhibited
                                        1: A USART interrupt is generated whenever TC=1 in the USART_SR register*/
                                        
#define FIELD_USART_RXNEIE   5,5 /*      RXNEIE: RXNE interrupt enable
                                        This bit is set and cleared by software.
                                        0: Interrupt is inhibited
                                        1: A USART interrupt is generated whenever ORE=1 or RXNE=1 in the USART_SR register*/

#define FIELD_USART_IDLEIE   4,4 /*      IDLEIE: IDLE interrupt enable
                                        This bit is set and cleared by software.
                                        0: Interrupt is inhibited
                                        1: A USART interrupt is generated whenever IDLE=1 in the USART_SR register*/

#define FIELD_USART_TE       3,3 /*      TE: Transmitter enable
                                        This bit enables the transmitter. It is set and cleared by software.
                                        0: Transmitter is disabled
                                        1: Transmitter is enabled
                                        Note: 1: During transmission, a “0” pulse on the TE bit (“0” followed by “1”) sends a preamble
                                        (idle line) after the current word, except in smartcard mode.
                                        2: When TE is set there is a 1 bit-time delay before the transmission starts.*/
                                        
#define FIELD_USART_RE       2,2 /*      RE: Receiver enable
                                        This bit enables the receiver. It is set and cleared by software.
                                        0: Receiver is disabled
                                        1: Receiver is enabled and begins searching for a start bit*/
                                        
#define FIELD_USART_RWU      1,1 /*      RWU: Receiver wakeup
                                        This bit determines if the USART is in mute mode or not. It is set and cleared by software and
                                        can be cleared by hardware when a wakeup sequence is recognized.
                                        0: Receiver in active mode
                                        1: Receiver in mute mode
                                        Note: 1: Before selecting Mute mode (by setting the RWU bit) the USART must first receive a
                                        data byte, otherwise it cannot function in Mute mode with wakeup by Idle line detection.
                                        2: In Address Mark Detection wakeup configuration (WAKE bit=1) the RWU bit cannot
                                        be modified by software while the RXNE bit is set.*/
                                        
#define FIELD_USART_SBK      0,0 /*      SBK: Send break
                                        This bit set is used to send break characters. It can be set and cleared by software. It should
                                        be set by software, and will be reset by hardware during the stop bit of break.
                                        0: No break character is transmitted
                                        1: Break character will be transmitted*/

// CR2 p613

#define FIELD_USART_LINEN    14,14 /*    LINEN: LIN mode enable
                                        This bit is set and cleared by software.
                                        0: LIN mode disabled
                                        1: LIN mode enabled
                                        The LIN mode enables the capability to send LIN Synch Breaks (13 low bits) using the SBK
                                        bit in the USART_CR1 register, and to detect LIN Sync breaks.*/

#define FIELD_USART_STOP     13,12 /*    STOP: STOP bits
                                        These bits are used for programming the stop bits.
                                        00: 1 Stop bit
                                        01: 0.5 Stop bit
                                        10: 2 Stop bits
                                        11: 1.5 Stop bit
                                        The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.*/
                                        
#define FIELD_USART_CLKEN    11,11 /*    CLKEN: Clock enable
                                        This bit allows the user to enable the CK pin.
                                        0: CK pin disabled
                                        1: CK pin enabled
                                        This bit is not available for UART4 & UART5.*/

#define FIELD_USART_CPOL     10,10 /*    CPOL: Clock polarity
                                        This bit allows the user to select the polarity of the clock output on the CK pin in synchronous
                                        mode. It works in conjunction with the CPHA bit to produce the desired clock/data
                                        relationship
                                        0: Steady low value on CK pin outside transmission window.
                                        1: Steady high value on CK pin outside transmission window.
                                        This bit is not available for UART4 & UART5.*/
                                        
#define FIELD_USART_CPHA     9,9 /*      CPHA: Clock phase
                                        This bit allows the user to select the phase of the clock output on the CK pin in synchronous
                                        mode. It works in conjunction with the CPOL bit to produce the desired clock/data
                                        relationship (see figures 254 to 255)
                                        0: The first clock transition is the first data capture edge.
                                        1: The second clock transition is the first data capture edge.
                                        This bit is not available for UART4 & UART5.*/
                                        
#define FIELD_USART_LBCL     8,8 /*      LBCL: Last bit clock pulse
                                        This bit allows the user to select whether the clock pulse associated with the last data bit
                                        transmitted (MSB) has to be output on the CK pin in synchronous mode.
                                        0: The clock pulse of the last data bit is not output to the CK pin
                                        1: The clock pulse of the last data bit is output to the CK pin
                                        The last bit is the 8th or 9th data bit transmitted depending on the 8 or 9 bit format selected
                                        by the M bit in the USART_CR1 register.
                                        This bit is not available for UART4 & UART5.*/

#define FIELD_USART_LBDIE    6,6 /*      LBDIE: LIN break detection interrupt enable
                                        Break interrupt mask (break detection using break delimiter).
                                        0: Interrupt is inhibited
                                        1: An interrupt is generated whenever LBD=1 in the USART_SR register*/ 
                                        
#define FIELD_USART_LBDL     5,5 /*      LBDL: lin break detection length
                                        This bit is for selection between 11 bit or 10 bit break detection.
                                        0: 10 bit break detection
                                        1: 11 bit break detection */
                                        
#define FIELD_USART_ADD      3,0 /*      ADD[3:0]: Address of the USART node
                                        This bit-field gives the address of the USART node.
                                        This is used in multiprocessor communication during mute mode, for wake up with address
                                        mark detection.*/

// CR3 p614

#define FIELD_USART_CTSIE    10,10 /*    Bit 10 CTSIE: CTS interrupt enable
                                        0: Interrupt is inhibited
                                        1: An interrupt is generated whenever CTS=1 in the USART_SR register
                                        This bit is not available for UART4 & UART5. */

#define FIELD_USART_CTSE     9,9 /*      CTSE: CTS enable
                                        0: CTS hardware flow control disabled
                                        1: CTS mode enabled, data is only transmitted when the nCTS input is asserted (tied to 0). If
                                        the nCTS input is deasserted while a data is being transmitted, then the transmission is
                                        completed before stopping. If a data is written into the data register while nCTS is asserted,
                                        the transmission is postponed until nCTS is asserted.
                                        This bit is not available for UART4 & UART5. */

#define FIELD_USART_RTSE     8,8 /*      RTSE: RTS enable
                                        0: RTS hardware flow control disabled
                                        1: RTS interrupt enabled, data is only requested when there is space in the receive buffer.
                                        The transmission of data is expected to cease after the current character has been
                                        transmitted. The nRTS output is asserted (tied to 0) when a data can be received.
                                        This bit is not available for UART4 & UART5. */
                                        
#define FIELD_USART_DMAT     7,7 /*      DMAT: DMA enable transmitter
                                        This bit is set/reset by software
                                        1: DMA mode is enabled for transmission
                                        0: DMA mode is disabled for transmission
                                        This bit is not available for UART5.*/
                                        
#define FIELD_USART_DMAR     6,6 /*      DMAR: DMA enable receiver
                                        This bit is set/reset by software
                                        1: DMA mode is enabled for reception
                                        0: DMA mode is disabled for reception
                                        This bit is not available for UART5. */
                                        
    #define FIELD_USART_SCEN     5,5 /*  SCEN: Smartcard mode enable
                                        This bit is used for enabling Smartcard mode.
                                        0: Smartcard Mode disabled
                                        1: Smartcard Mode enabled
                                        This bit is not available for UART4 & UART5.*/
                                    
#define FIELD_USART_NACK     4,4 /*      NACK: Smartcard NACK enable
                                        0: NACK transmission in case of parity error is disabled
                                        1: NACK transmission during parity error is enabled
                                        This bit is not available for UART4 & UART5.*/

#define FIELD_USART_HDSEL    3,3 /*      HDSEL: Half-duplex selection
                                        Selection of Single-wire Half-duplex mode
                                        0: Half duplex mode is not selected
                                        1: Half duplex mode is selected*/
                                        
#define FIELD_USART_IRLP     2,2 /*      IRLP: IrDA low-power
                                        This bit is used for selecting between normal and low-power IrDA modes
                                        0: Normal mode
                                        1: Low-power mode*/
                                        
#define FIELD_USART_IREN     1,1 /*      IREN: IrDA mode enable
                                        This bit is set and cleared by software.
                                        0: IrDA disabled
                                        1: IrDA enabled*/
                                        
#define FIELD_USART_EIE      0,0 /*      EIE: Error interrupt enable
                                        Error Interrupt Enable Bit is required to enable interrupt generation in case of a framing error,
                                        overrun error or noise error (FE=1 or ORE=1 or NE=1 in the USART_SR register) in case of
                                        Multi Buffer Communication (DMAR=1 in the USART_CR3 register).
                                        0: Interrupt is inhibited
                                        1: An interrupt is generated whenever DMAR=1 in the USART_CR3 register and FE=1 or
                                        ORE=1 or NE=1 in the USART_SR register.*/

// BRR p610
#define FIELD_USART_DIV_MANTISSA     15,4    /*  DIV_Mantissa[11:0]: mantissa of USARTDIV
                                                These 12 bits define the mantissa of the USART Divider (USARTDIV)*/
#define FIELD_USART_DIV_FRACTION      3,0    /*  DIV_Fraction[3:0]: fraction of USARTDIV
                                                These 4 bits define the fraction of the USART Divider (USARTDIV)*/

// DR p610
#define FIELD_USART_DR                8,0    /*  DR[8:0]: Data value
                                                Contains the Received or Transmitted data character, depending on whether it is read from
                                                or written to.
                                                The Data register performs a double function (read and write) since it is composed of two
                                                registers, one for transmission (TDR) and one for reception (RDR)
                                                The TDR register provides the parallel interface between the internal bus and the output
                                                shift register (see Figure 1).
                                                The RDR register provides the parallel interface between the input shift register and the
                                                internal bus.
                                                When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register), the
                                                value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect because
                                                it is replaced by the parity.
                                                When receiving with the parity enabled, the value read in the MSB bit is the received parity
                                                bit.*/





/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */

typedef enum {
     USART_1 = 1
    ,USART_2 = 2
    ,USART_3 = 3
} uart_x_t;

typedef enum {
     NONE = 0
    ,ODD = 3
    ,EVEN = 2
} uart_parity_t;

typedef enum {
     DATA_8 = 0
    ,DATA_9 = 1
} uart_datalength_t;

typedef enum {
     ONE_BITSTOP = 0
    ,HALF_BITSTOP = 1
    ,TWO_BITSTOP = 2
    ,ONE_HALF_BITSTOP = 3    
} uart_bitstop_t;

typedef struct {
    uint32_t bauderate;
    uart_parity_t parity;
    uart_bitstop_t bitstop;
    uart_datalength_t data_length;
} uart_config_t;


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
int32_t  F_usart_init        ( uint32_t i_id, addr_t base_address);
int32_t  F_usart_setconfig   ( uint32_t i_id, uart_config_t * i_config );
int32_t F_usart_putc         (uint32_t i_id,uint8_t data);
int32_t F_usart_getc(uint32_t i_id);
int32_t F_usart_Write(uint32_t i_id,const char * str); // quick & dirty 

#endif /* D_UART_H */
