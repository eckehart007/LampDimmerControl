/*
 * UartAndClock.c
 *
 *  Created on: 20 Nov 2015
 *      Author: Egert
 *      reference http://longhornengineer.com/code/MSP430/UART/
 */

#include <msp430.h>
#include "../LampHeaders/GlobalConfig.h"
#include "../LampHeaders/LampPinout.h"
#include "../LampHeaders/MsgAndStates.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

/* VARIABLES */
volatile unsigned int tx_flag;			//Mailbox Flag for the tx_char.
volatile unsigned char tx_char;			//This char is the most current char to go into the UART

volatile unsigned int rx_flag;			//Mailbox Flag for the rx_char.

volatile unsigned int rxCount=0;
volatile char rxChar = 0;

/*
 * Set mcu clock
 */
extern void setClk(long clockSpeed) {
	switch (clockSpeed) {
		case 8000000:
			if (CALBC1_8MHZ != 0xFF) {
				DCOCTL    =   0;
				BCSCTL1   =   CALBC1_8MHZ;		/* Set range */
				DCOCTL    =   CALDCO_8MHZ;		/* Set DCO step + modulatino */
			}
			break;
		case 12000000:
			if (CALBC1_12MHZ != 0xFF) {
				DCOCTL    =   0;
				BCSCTL1   =   CALBC1_12MHZ;
				DCOCTL    =   CALDCO_12MHZ;
			}
			break;
		case 16000000:
			if (CALBC1_16MHZ != 0xFF) {
				DCOCTL    =   0;
				BCSCTL1   =   CALBC1_16MHZ;
				DCOCTL    =   CALDCO_16MHZ;
			}
			break;
		default:
			if (CALBC1_1MHZ != 0xFF) {
				DCOCTL    =   0;
				BCSCTL1   =   CALBC1_1MHZ;
				DCOCTL    =   CALDCO_1MHZ;
			}
			break;
	}
}

/*
 * set BAUD
 * Databits	8
 */
extern void initUart(void) {
	SETBIT(P1SEL, (RX_UART1 + TX_UART1));			/* P1.1 - RXD and P1.2 - TXD */
	SETBIT(P1SEL2, (RX_UART1 + TX_UART1));
	SETBIT(UCA0CTL1, (UCSSEL_2 + UCSWRST));			/* SMCLK */
	CLRBIT(UCA0CTL1, UC7BIT);						/* 8-bit data */

	/* 8x0.66666667 = 5, 0x5b, http://www.glitovsky.com/Tutorialv0_3.pdf page 87 */
	UCA0BR0 = USCI_BR0_VAL;
	UCA0BR1 = USCI_BR1_VAL;
	UCA0MCTL = USCI_BRS_VAL;						/* http://embedded-funk.net/writing-c-code-smartly-1-using-your-c-preprocessor-as-your-calculator */
	CLRBIT(UCA0CTL1, UCSWRST);						/* Take UCA0 out of reset */
	SETBIT(IE2, UCA0RXIE);							/* Enable USCI_A0 RX interrupt */
}

/*uart_getc
* Get a char from the UART. Waits till it gets one
* INPUT: None
* RETURN: Char from UART
*/
extern unsigned char uart_getc() {				//Waits for a valid char from the UART
	while (rx_flag == FALSE);		 			//Wait for rx_flag to be set
	rx_flag = FALSE;							//ACK rx_flag
    return rxChar;
}

/*uart_gets
* Get a string of known length from the UART. Strings terminate when enter is pressed or string buffer fills
* Will return when all the chars are received or a carriage return (\r) is received. Waits for the data.
* INPUT: Array pointer and length
* RETURN: None
*/
extern void uart_gets(char* uartMsg) {
	unsigned int i = 0;
	while((i < RX_BUFFER_SIZE))	{						//Grab data till the array fills
		uartMsg[i] = uart_getc();
		if((uartMsg[i] == '\r')
			 || (uartMsg[i]  == '\n')) {				//If we receive a \r the master wants to end
			for( ; i < RX_BUFFER_SIZE ; i++) {			//fill the rest of the string with \0 nul. Overwrites the \r with \0
				uartMsg[i] = '\0';
			}
			break;
		}
		i++;
	}
    return;
}

/*uart_putc
* Sends a char to the UART. Will wait if the UART is busy
* INPUT: Char to send
* RETURN: None
*/
extern void uart_putc(unsigned char c)
{
	tx_char = c;						//Put the char into the tx_char
	SETBIT(IE2, UCA0TXIE);				//Enable USCI_A0 TX interrupt
	while(tx_flag == FALSE);			//Have to wait for the TX buffer
	tx_flag = FALSE;					//Reset the tx_flag
	return;
}

/*uart_puts
* Sends a string to the UART. Will wait if the UART is busy
* INPUT: Pointer to String to send
* RETURN: None
*/
extern void uart_puts(char *str)				//Sends a String to the UART.
{
     while(*str) uart_putc(*str++);		//Advance though string till end
     return;
}

#pragma vector = USCIAB0TX_VECTOR		//UART TX USCI Interrupt
__interrupt void USCI0TX_ISR(void)
{
	UCA0TXBUF = tx_char;				//Copy char to the TX Buffer
	tx_flag = TRUE;						//ACK the tx_flag
	CLRBIT(IE2, UCA0TXIE);				//Turn off the interrupt to save CPU
}

/*
 * 	UART RX service routine
 *	Builds pString until end of string is reached
 *	and then wakes up controller.
*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void	USCI0RX_ISR(void)  {
	rxChar = UCA0RXBUF;					//Copy from RX buffer, in doing so we ACK the interrupt as well
	rx_flag = TRUE;						//Set the rx_flag to 1
	__low_power_mode_off_on_exit();
}
