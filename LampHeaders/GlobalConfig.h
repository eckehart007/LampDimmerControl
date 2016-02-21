/*
 * GlobalConfig.h
 *
 *  Created on: 22 Nov 2015
 *      Author: Egert
 */

#ifndef MYHEADER_GLOBALCONFIG_H_
#define MYHEADER_GLOBALCONFIG_H_

#define	TRUE 	1
#define FALSE 	0

//
#define TIMER_A_DIVIDER			(8)			/* ID_3 */
#define TIMER_A_COUNTER0 		(62500)
#define TIMER_A_COUNTER1 		(7500)
#define PWM_PERIOD				(50)		/* 50Hz */

/* Macros */
#define SETBIT(port, bit) (port |= (bit))
#define CLRBIT(port, bit) (port &= ~(bit))
#define TGLBIT(port, bit) (port ^= (bit))

//Timer calc
#define TIMER_PRESCALED_CLK		(USCI_INPUT_CLK / TIMER_A_DIVIDER)
#define TIMER_A_FREQ0			(TIMER_PRESCALED_CLK / TIMER_A_COUNTER0)

//PWM
#define PWM_PERIOD_CCR			((TIMER_PRESCALED_CLK / PWM_PERIOD) - 1)		// PWM Period 50Hz = 20000

/* PROTOTYPES */
extern void initTimerA0(void);
extern void initLeds(void);
extern void blinkLeds(void);
extern void initButtons(void);
extern void debouncingCompleted(void);
//PWM
extern void initPwm(char pwm1_duty, char pwm2_duty);
static int dutyBasedCCR(char pwm1_duty);
extern void setPwm(char pwmPin, char pwm_duty);
extern void setAllPwmMax(void);
extern void setAllPwmOff(void);
extern void togglePWM1(void);
extern void togglePWM2(void);
//MAIN
void clrMsg(void);
void splitUartMsg(void);
//TRIACs
extern void initZeroCrossingDetect(void);
extern void initTriacs(void);
extern void triac1Off(void);
extern void triac1On(void);

/* Global VARIABLES */
/*  This flag is to be used by other modules to check and see
 * if button if pressed and bouncing is completed.
 */
extern volatile int buttonPress[2];

/* This flag is to be used by other modules to check and see
 * if a led blinking timer has reached specific time.
*/
extern volatile unsigned int timerFlag;

/* This flag is to be used by other modules to check and see
 * if a button debouncing timer has reached specific time.
*/
extern volatile unsigned int decouncingTimerFlag[2];


#endif /* MYHEADER_GLOBALCONFIG_H_ */
