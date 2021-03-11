
#include "MKL25Z4.h" 
#include "RTE_Components.h"
#include "cmsis_os2.h"

#ifndef LAB_SERVICE_H
#define LAB_SERVICE_H

extern osMessageQueueId_t redMsg, greenMsg, blueMsg;

extern osThreadId_t redLED_Id, greenLED_Id, blueLED_Id, control_Id;

extern osEventFlagsId_t led_flag;

extern uint32_t MSG_COUNT;

extern osSemaphoreId_t mySem;

typedef struct {
	uint8_t cmd;
	uint8_t data;
} myDataPkt;


void lab_two(void);
void lab_three(void);
void lab_four(void);
void lab_five(void);
void lab_six(void);
void lab_seven(void);
void lab_eight(void);
void lab_nine(void);
#endif
