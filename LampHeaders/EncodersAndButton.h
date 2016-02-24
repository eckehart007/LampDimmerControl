/*
 * EncodersAndButton.h
 *
 *  Created on: 21 Feb 2016
 *      Author: Egert
 */

#ifndef LAMPHEADERS_ENCODERSANDBUTTON_H_
#define LAMPHEADERS_ENCODERSANDBUTTON_H_

//PROTO
extern void initButtons(void);
extern void initEncoders(void);
extern void encoder1State(void);
extern void encoder2State(void);

//VAR
extern unsigned char sw1_flag;
extern unsigned char sw2_flag;

extern unsigned char ENCODER_1B_flag;
extern unsigned char ENCODER_1A_flag;
extern unsigned char ENCODER1_COUNT;

extern unsigned char ENCODER_2B_flag;
extern unsigned char ENCODER_2A_flag;
extern unsigned char ENCODE2_COUNT;

#endif /* LAMPHEADERS_ENCODERSANDBUTTON_H_ */
