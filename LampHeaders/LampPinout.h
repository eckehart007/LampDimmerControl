/*
 * LampPinout.h
 *
 *  Created on: 21 Feb 2016
 *      Author: Egert
 *
 */

#ifndef LAMPHEADERS_LAMPPINOUT_H_
#define LAMPHEADERS_LAMPPINOUT_H_

/* OUTPUTS */
#define TRIAC1_PORT		(P1OUT)
#define	TRIAC1			(BIT6)		//Pin 14 - P1.6/TA0.1
#define TRIAC2_PORT		(P1OUT)
#define TRIAC2			(BIT5)		//Pin 13 - P2.5/TA1.2

/* INPUTS */
#define ZERO_CROSS_PORT	(P2IN)
#define ZERO_CROSS		(BIT4)		//Pin 12 P2.4/TA1.2

#define Encoder_PORT	(P1IN)
#define SW1				(BIT3)		//Pin 5 - P1.3/
#define	ENCODER_1B		(BIT4)		//Pin 6 - P1.4
#define	ENCODER_1A		(BIT5)		//Pin 7 - P1.5/TA0.0
#define SW2				(BIT0)		//Pin 8 - P2.0/TA1.0
#define	ENCODER_2B		(BIT1)		//Pin 9 - P2.1/TA1.1
#define	ENCODER_2A		(BIT2)		//Pin 10 - P2.2/TA1.1

/* COMMUNICATION */
#define	RX_UART1	(BIT1)					//Pin 3 P1.1/TA0.0/UCA0RXD
#define TX_UART1	(BIT2)					//Pin 4 P1.2/TA0.1/UCA0TXD

#endif /* LAMPHEADERS_LAMPPINOUT_H_ */
