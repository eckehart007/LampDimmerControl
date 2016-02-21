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

extern void initTriacs(void) {
	CLRBIT(P1SEL, TRIAC1);
	CLRBIT(P2SEL, TRIAC2);
	CLRBIT(P1SEL, (0x00));
	CLRBIT(P2SEL, (0x00));
	CLRBIT(P1DIR, (0x00));
	CLRBIT(P2DIR, (0x00));
	SETBIT(P1DIR, TRIAC1);
	SETBIT(P2DIR, TRIAC2);
	SETBIT(P1DIR, TRIAC1);
	SETBIT(P2DIR, TRIAC2);
}



