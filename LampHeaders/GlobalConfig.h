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

/* UART and Clock parameters */
#define RX_BUFFER_SIZE			(32)
#define USCI_INPUT_CLK      	(8000000)
#define USCI_BAUD_RATE			(9600)
#define USCI_DATABITS			(8)
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

/* BAUD calculations
 * http://embedded-funk.net/writing-c-code-smartly-1-using-your-c-preprocessor-as-your-calculator */
#define USCI_DIV_INT              (USCI_INPUT_CLK/USCI_BAUD_RATE)
#define USCI_BR0_VAL              (USCI_DIV_INT & 0x00FF)
#define USCI_BR1_VAL              ((USCI_DIV_INT >> 8) & 0xFF)

#define USCI_DIV_FRAC_NUMERATOR   (USCI_INPUT_CLK - (USCI_DIV_INT*USCI_BAUD_RATE))
#define USCI_DIV_FRAC_NUM_X_8     (USCI_DIV_FRAC_NUMERATOR*8)
#define USCI_DIV_FRAC_X_8         (USCI_DIV_FRAC_NUM_X_8/USCI_BAUD_RATE)

#if (((USCI_DIV_FRAC_NUM_X_8-(USCI_DIV_FRAC_X_8*USCI_BAUD_RATE))*10)/USCI_BAUD_RATE < 5)
#define USCI_BRS_VAL              (USCI_DIV_FRAC_X_8<< 1)
#else
#define USCI_BRS_VAL              ((USCI_DIV_FRAC_X_8+1)<< 1)
#endif

/* PROTOTYPES */
extern void setClk(long clockSpeed);
extern void initUart(void);
extern unsigned char uart_getc();
extern void uart_gets(char* uartMsg);
extern void uart_putc(unsigned char c);
extern void uart_puts(char *str);
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
 * if a new transmission has happened.
*/
extern volatile unsigned int rx_flag;

/* This flag is to be used by other modules to check and see
 * if a led blinking timer has reached specific time.
*/
extern volatile unsigned int timerFlag;

/* This flag is to be used by other modules to check and see
 * if a button debouncing timer has reached specific time.
*/
extern volatile unsigned int decouncingTimerFlag[2];


#endif /* MYHEADER_GLOBALCONFIG_H_ */
