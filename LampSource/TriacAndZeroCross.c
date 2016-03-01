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

extern void initZeroCross(void) {
	SETBIT(P2REN, ZERO_CROSS);
	CLRBIT(P2DIR, ZERO_CROSS);
	SETBIT(P2IE, ZERO_CROSS);		/* enable SW1 interrupt */
	SETBIT(P2IES, ZERO_CROSS);		/* interrupt on high-to-low transition */
	SETBIT(P2OUT, ZERO_CROSS);
}

extern void tglTriac(char triacPin) {
	if (triacPin == TRIAC1) {
		while(zeroCross_flag == FALSE);
		uart_puts("TGL TRIAC1\n");
		TGLBIT(TRIAC1_PORT, TRIAC1);
		sw1_flag = FALSE;
		return;
	}
	if (triacPin == TRIAC2) {
		while(zeroCross_flag == FALSE);
		uart_puts("TGL TRIAC2\n");
		TGLBIT(TRIAC2_PORT, TRIAC2);
		sw2_flag = FALSE;
		return;
	}
}



