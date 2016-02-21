#include <msp430.h> 
#include "LampHeaders/LampPinout.h"
#include "LampHeaders/GlobalConfig.h"
#include "LampHeaders/MsgAndStates.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	return 0;
}
