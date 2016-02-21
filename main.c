#include <msp430.h> 
#include "LampHeaders/LampPinout.h"
#include "LampHeaders/GlobalConfig.h"
#include "LampHeaders/MsgAndStates.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    setClk(USCI_INPUT_CLK);

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


	for(;;) {}
}
