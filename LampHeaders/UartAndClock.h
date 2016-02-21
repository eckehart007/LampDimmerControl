/*
 * UartAndClock.h
 *
 *  Created on: 21 Feb 2016
 *      Author: Egert
 */

#ifndef LAMPHEADERS_UARTANDCLOCK_H_
#define LAMPHEADERS_UARTANDCLOCK_H_

/* UART and Clock parameters */
#define RX_BUFFER_SIZE			(32)
#define USCI_INPUT_CLK      	(8000000)
#define USCI_BAUD_RATE			(9600)
#define USCI_DATABITS			(8)

/* BAUD calculations
 * http://embedded-funk.net/writing-c-code-smartly-1-using-your-c-preprocessor-as-your-calculator */
#define USCI_DIV_INT              (USCI_INPUT_CLK/USCI_BAUD_RATE)
#define USCI_BR0_VAL              (USCI_DIV_INT & 0x00FF)
#define USCI_BR1_VAL              ((USCI_DIV_INT >> 8) & 0xFF)

#define USCI_DIV_FRAC_NUMERATOR   (USCI_INPUT_CLK - (USCI_DIV_INT*USCI_BAUD_RATE))
#define USCI_DIV_FRAC_NUM_X_8     (USCI_DIV_FRAC_NUMERATOR*8)
#define USCI_DIV_FRAC_X_8         (USCI_DIV_FRAC_NUM_X_8/USCI_BAUD_RATE)

#if (((USCI_DIV_FRAC_NUM_X_8-(USCI_DIV_FRAC_X_8*USCI_BAUD_RATE))*10)/USCI_BAUD_RATE < 5)
#define USCI_BRS_VAL              (USCI_DIV_FRAC_X_8<< 1)
#else
#define USCI_BRS_VAL              ((USCI_DIV_FRAC_X_8+1)<< 1)
#endif

//PROTO
extern void setClk(long clockSpeed);
extern void initUart(void);
extern unsigned char uart_getc();
extern void uart_gets(char* uartMsg);
extern void uart_putc(unsigned char c);
extern void uart_puts(char *str);

/* This flag is to be used by other modules to check and see
 * if a new transmission has happened.
*/
extern volatile unsigned int rx_flag;


#endif /* LAMPHEADERS_UARTANDCLOCK_H_ */
