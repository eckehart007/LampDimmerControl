#include <msp430.h> 
#include "LampHeaders/LampPinout.h"
#include "LampHeaders/GlobalConfig.h"
#include "LampHeaders/MsgAndStates.h"
#include "LampHeaders/UartAndClock.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    setClk(USCI_INPUT_CLK);
    initUart();
    initTriacs();

    __enable_interrupt();				//Interrupts Enabled

    /* UART */
    initUart();
    uart_puts("\n*************************\n");
    uart_puts("\tHello UART!\n");
    uart_puts("*************************\n");


	for(;;) {}
}
