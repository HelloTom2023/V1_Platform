#ifndef _TEST_CASE_H
#define _TEST_CASE_H

#if D_DEBUG_TESTCASE && D_PRINT_EN
#define TCase_debug(x)  			x
#else
#define TCase_debug(x)
#endif

typedef struct{
	uint8_t Mode;
	uint16_t Timer;
	uint8_t Step;
	uint8_t Count;
	uint8_t Result;
	uint8_t param;	// 0- normal; 1- exception. bit0- ack; bit1-parity; 
}TEST_CASE_STR;

extern TEST_CASE_STR	MDITestCase;

extern void MDI_TestControl(uint8_t enable);
extern void MDI_TestRoutine(void);

#endif
