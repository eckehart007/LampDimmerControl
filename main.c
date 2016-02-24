//***************************************************************************************
/*
 *
 *	SW1 controls TRIAC1
 *	SW2 controls TRIAC2
 *	ENCODER1 right/left turn makes light brighter/fader with TRIAC1 phase control with ZeroCrossing
 *	ENCODER2 right/left turn makes light brighter/fader with TRIAC2 phase control with ZeroCrossing
 *	ZeroCrossing is detected with falling edge interrupt
 *	UART commands for TRIAC ON/OFF, CUSTOM BRIGHTNESS, BOTH ON/OFF
 *
 *  Egert Pärna
 *  20.11.2015
 *  Built with Code Composer Studio v6.1
 */
//***************************************************************************************

#include <msp430.h> 
#include "LampHeaders/LampPinout.h"
#include "LampHeaders/GlobalConfig.h"
#include "LampHeaders/MsgAndStates.h"
#include "LampHeaders/UartAndClock.h"
#include "LampHeaders/EncodersAndButton.h"
#include "LampHeaders/TriacAndZeroCross.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

//PROTO
void controlLeds(char state);

extern char pString[RX_BUFFER_SIZE] = "";
extern char * pString1 = '\0';
extern volatile char uartParameter = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    setClk(USCI_INPUT_CLK);
    initTriacs();
    initButtons();
    initEncoders();

    __enable_interrupt();				//Interrupts Enabled

    /* UART */
    initUart();
    uart_puts("\n*************************\n");
    uart_puts("\tHello UART!\n");
    uart_puts("*************************\n");


    /*
     * Non-stop loop
     */
	while (1) {
		_bis_SR_register(LPM0_bits);					// Enter LPM0, enable interrupts

		if (rx_flag == TRUE) {
			uart_gets(pString);
			splitUartMsg();
		}

		/* TRIAC CONTROL */
		if ((strcmp(pString1, COMM_TRIAC1) == 0) || sw1_flag) {
			tglTriac(TRIAC1);
		} else if ((strcmp(pString1, COMM_TRIAC2) == 0) || sw2_flag) {
			tglTriac(TRIAC2);
		} else if (ENCODER_1B_flag || ENCODER_1A_flag) {
			encoder1State();
		} else if (ENCODER_2B_flag || ENCODER_2A_flag) {
			encoder2State();
		} else {
			uart_puts("\nBAD\n");
		}

		//CLEAR UART MSG
		if (strlen(pString)) {
			clrMsg();
		}
	}
}

void splitUartMsg(void) {
	char * token = strtok(pString, " ");
	pString1 = token;
	token = strtok (NULL, " ");
	uartParameter = atoi(token);
}

void clrMsg(void) {
	memset(pString,0,sizeof(pString));
	memset(pString,0,sizeof(pString1));
	uartParameter = 0;
}
