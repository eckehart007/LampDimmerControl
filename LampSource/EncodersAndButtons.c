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
#include "../LampHeaders/MsgAndStates.h"
#include "../LampHeaders/UartAndClock.h"
#include <stdio.h>
#include <string.h>

/* VARIABLES */
unsigned char sw1_flag = FALSE;
unsigned char sw2_flag = FALSE;
unsigned char zeroCross_flag = FALSE;
unsigned char zeroCross_count = 0;

unsigned char ENCODER_1B_flag = FALSE;
unsigned char ENCODER_1A_flag = FALSE;
unsigned char ENCODER1_COUNT = 0;

unsigned char ENCODER_2B_flag = FALSE;
unsigned char ENCODER_2A_flag = FALSE;
unsigned char ENCODER2_COUNT = 0;

extern unsigned char triac1_timer_flag = FALSE;
extern unsigned char triac2_timer_flag = FALSE;

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
	SETBIT(P2REN, (ENCODER_2B + ENCODER_2A));

	CLRBIT(P1DIR, (ENCODER_1B + ENCODER_1A));
	CLRBIT(P2DIR, (ENCODER_2B + ENCODER_2A));

	SETBIT(P1IE, (ENCODER_1B + ENCODER_1A));		/* enable SW1 interrupt */
	SETBIT(P2IE, (ENCODER_2B + ENCODER_2A));		/* enable SW2 interrupt */

	CLRBIT(P1IES, (ENCODER_1B + ENCODER_1A));		/* interrupt on low-to-high transition */
	CLRBIT(P2IES, (ENCODER_2B + ENCODER_2A));		/* interrupt on low-to-high transition */

	SETBIT(P1OUT, (ENCODER_1B + ENCODER_1A));
	SETBIT(P2OUT, (ENCODER_2B + ENCODER_2A));
}

extern void encoder1State(void) {
	ENCODER_1A_flag = FALSE;
	ENCODER_1B_flag = FALSE;
	static char msg[32] = "";
	sprintf(msg, "ENCODER1:%d\n", ENCODER1_COUNT);
	uart_puts(msg);
}
extern void encoder2State(void) {
	ENCODER_2A_flag = FALSE;
	ENCODER_2B_flag = FALSE;
	static char msg[32] = "";
	sprintf(msg, "ENCODER2:%d\n", ENCODER2_COUNT);
	uart_puts(msg);
}

/*
 * Init Timer A0
 */
extern void initTimerA0(void) {
	SETBIT(TA0CTL, (TASSEL_2 | MC_2 | ID_3));		/* SMCLK, count Up,  divider 8 */
	SETBIT(TA1CTL, (TASSEL_2 | MC_2 | ID_3));		/* SMCLK, count Up,  divider 8 */

	/* Triac1 ZeroCrossing timer */
	TA0CCR0 = 10000; 								/* 8000000/8/10000 = 100Hz = 10ms */
	CLRBIT(TA0CCTL0, (CCIE));						/* Disable Timer */

	/* Triac2 ZeroCrossing timer */
    TA1CCR0 = 10000; 								/* 8000000/8/10000 = 100Hz = 10ms */
    CLRBIT(TA1CCTL0, (CCIE));						/* Disable Timer */
}

/* Port 1 interrupt to service the button press */
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void) {
	if(P1IFG & SW1) {
		CLRBIT(P1IFG, SW1); 			//Clear BUTTON1 interrupt flag
		sw1_flag = TRUE;
	} else if (P1IFG & ENCODER_1B) {
		CLRBIT(P1IFG, ENCODER_1B);
		if (Encoder1_PORT & ENCODER_1A) {
			ENCODER_1A_flag = TRUE;
			if (ENCODER1_COUNT == 23) {
				ENCODER1_COUNT = 0;
			} else {
				ENCODER1_COUNT++;
			}
		}
	} else if (P1IFG & ENCODER_1A) {
		CLRBIT(P1IFG, ENCODER_1A);
		if (Encoder1_PORT & ENCODER_1B) {
			ENCODER_1A_flag = TRUE;
			if (ENCODER1_COUNT == 0) {
				ENCODER1_COUNT = 23;
			} else {
				ENCODER1_COUNT--;
			}
		}
	}
	__low_power_mode_off_on_exit();
}

/* Port 2 interrupt to service the button press */
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void) {
	if(P2IFG & SW2) {
		CLRBIT(P2IFG, SW2);				//Clear BUTTON2 interrupt flag
		sw2_flag = TRUE;
	} else if (P2IFG & ENCODER_2B) {
		CLRBIT(P2IFG, ENCODER_2B);
		if (Encoder2_PORT & ENCODER_2A) {
			ENCODER_2A_flag = TRUE;
			if (ENCODER2_COUNT == 23) {
				ENCODER2_COUNT = 0;
			} else {
				ENCODER2_COUNT++;
			}
		}
	} else if (P2IFG & ENCODER_2A) {
		CLRBIT(P2IFG, ENCODER_2A);
		if (Encoder2_PORT & ENCODER_2B) {
			ENCODER_2A_flag = TRUE;
			if (ENCODER2_COUNT == 0) {
				ENCODER2_COUNT = 23;
			} else {
				ENCODER2_COUNT--;
			}
		}
	} else if (P2IFG & ZERO_CROSS) {
		CLRBIT(P2IFG, ZERO_CROSS);
		zeroCross_flag = TRUE;
		zeroCross_count++;
	}
	__low_power_mode_off_on_exit();
}

/*
 * TRIAC1 timer
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void	Timer0_A0 (void) {
	triac1_timer_flag = TRUE;
	__low_power_mode_off_on_exit();
}

/*
 * TRIAC2 timer
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void	Timer1_A0 (void) {
	triac2_timer_flag = TRUE;
	__low_power_mode_off_on_exit();
}

