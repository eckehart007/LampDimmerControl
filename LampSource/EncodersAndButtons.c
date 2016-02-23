/*
 * EncodersAndButtons.c
 *
 *  Created on: 21 Feb 2016
 *      Author: Egert
 */

#include <msp430.h>
#include "../LampHeaders/GlobalConfig.h"
#include "../LampHeaders/EncodersAndButton.h"
#include "../LampHeaders/LampPinout.h"

/*
* Init BUTTON1
*/
extern void initButtons(void) {
	SETBIT(P1REN, SW1);
	SETBIT(P2REN, SW2);

	CLRBIT(P1DIR, SW1);
	CLRBIT(P2DIR, SW2);

	SETBIT(P1IE, SW1);		/* enable SW1 interrupt */
	SETBIT(P2IE, SW2);		/* enable SW2 interrupt */

	SETBIT(P1IES, SW1);		/* interrupt on high-to-low transition */
	SETBIT(P2IES, SW2);		/* interrupt on high-to-low transition */

	SETBIT(P1OUT, SW1);
	SETBIT(P2OUT, SW2);
}



extern void initEncoders(void) {
	SETBIT(P1REN, (ENCODER_1B + ENCODER_1A));
	SETBIT(P1REN, (ENCODER_2B + ENCODER_2A));

	CLRBIT(P1DIR, (ENCODER_1B + ENCODER_1A));
	CLRBIT(P1DIR, (ENCODER_2B + ENCODER_2A));

	SETBIT(P1IE, (ENCODER_1B + ENCODER_1A));		/* enable SW1 interrupt */
	SETBIT(P1IE, (ENCODER_2B + ENCODER_2A));		/* enable SW2 interrupt */

	SETBIT(P1IES, (ENCODER_1B + ENCODER_1A));		/* interrupt on high-to-low transition */
	SETBIT(P1IES, (ENCODER_2B + ENCODER_2A));		/* interrupt on high-to-low transition */

	SETBIT(P1OUT, (ENCODER_1B + ENCODER_1A));
	SETBIT(P1OUT, (ENCODER_2B + ENCODER_2A));
}

/* Port 1 interrupt to service the button press */
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void) {
	if(P1IFG & SW1) {
		CLRBIT(P1IFG, SW1); 			//Clear BUTTON1 interrupt flag
		TGLBIT(TRIAC1_PORT, TRIAC1);
	}
}

/* Port 2 interrupt to service the button press */
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void) {
	if(P2IFG & SW2) {
		CLRBIT(P2IFG, SW2);				//Clear BUTTON2 interrupt flag
		TGLBIT(TRIAC2_PORT, TRIAC2);
	}
}


