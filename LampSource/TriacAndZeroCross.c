/*
 * TRIAC.c
 *
 *  Created on: 21 Feb 2016
 *      Author: Egert
 */

#include <msp430.h>
#include "../LampHeaders/GlobalConfig.h"
#include "../LampHeaders/TriacAndZeroCross.h"
#include "../LampHeaders/LampPinout.h"
#include "../LampHeaders/MsgAndStates.h"
#include "../LampHeaders/UartAndClock.h"
#include "../LampHeaders/EncodersAndButton.h"
#include <stdio.h>
#include <string.h>

extern void initTriacs(void) {
	CLRBIT(P1SEL, TRIAC1);
	CLRBIT(P2SEL, TRIAC2);

	CLRBIT(P1SEL, (0x00));
	CLRBIT(P2SEL, (0x00));

	CLRBIT(P1DIR, (0x00));
	CLRBIT(P2DIR, (0x00));

	SETBIT(P1DIR, TRIAC1);
	SETBIT(P2DIR, TRIAC2);

	CLRBIT(P1OUT, TRIAC1);
	CLRBIT(P2OUT, TRIAC2);
}

extern void tglTriac(char triacPin) {
	//static char msg[32] = "";
	if (triacPin == TRIAC1) {
		/*
		if ((TRIAC1_PORT & TRIAC1) == 0) {
			sprintf(msg, COMM_TRIAC1, "ON", "%\n");
		}
		sprintf(msg, COMM_TRIAC1, "ON", "%\n");
		*/
		uart_puts("TGL TRIAC1\n");
		TGLBIT(TRIAC1_PORT, TRIAC1);
		sw1_flag = FALSE;
		return;
	}
	if (triacPin == TRIAC2) {
		/*
		if ((TRIAC2_PORT & TRIAC2) == 0) {
			sprintf(msg, COMM_TRIAC2, "ON", "%\n");
		}
		sprintf(msg, COMM_TRIAC2, "ON", "%\n");
		*/
		uart_puts("TGL TRIAC2\n");
		TGLBIT(TRIAC2_PORT, TRIAC2);
		sw2_flag = FALSE;
		return;
	}
}



