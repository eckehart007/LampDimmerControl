/*
 * MsgAndStates.h
 *
 *  Created on: 7 Dec 2015
 *      Author: Egert
 */

#ifndef MYHEADER_MSGANDSTATES_H_
#define MYHEADER_MSGANDSTATES_H_

//CONST
#define TRIAC1_FLAG					0
#define TRIAC2_FLAG					1


//TRIAC COMMANDS
#define COMM_TRIAC1						"TRIAC1"	//"% 100" 100 = duty % 0 -100%
#define COMM_TRIAC2						"TRIAC2"
#define COMM_SET_ALL_TRIACS_OFF			"ALL_TRIACS_OFF"
#define COMM_SET_ALL_TRIACS_ON			"ALL_TRIACS_ON"

//TRIAC MSG
#define MSG_TRIAC1_STATE			"TRIAC1 state is %d%s"
#define MSG_TRIAC2_STATE			"TRIAC2 state is %d%s"
#define MSG_SET_ALL_TRIACS_OFF		"All TRIACs are OFF ..\n"
#define MSG_SET_ALL_TRIACS_MAX		"All TRIACs are on 100% ..\n"

#endif /* MYHEADER_MSGANDSTATES_H_ */
