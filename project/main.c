#include <MKL25Z4.h> 
#include <RTE_Components.h>
#include <cmsis_os2.h>
#include "constants.h"
#include "audio.h"
#include "led.h"
#include "motor.h"
#include "bluetooth.h"

uint32_t MSG_COUNT = 1;
volatile osMessageQueueId_t dataMsg;
volatile myDataPkt robotState;
osEventFlagsId_t connect_flag;
osMutexId_t myMutex;

void tBrain(void *argument) {
	bluetooth_init(BAUD_RATE);
	while(1);
}

void tMotorControl(void *argument) {
	motor_init();
	while(1) {
    if (robotState.cmd == CMD_MOVE) {
		  if (robotState.data == MOVE_FOWARD_STRAIGHT) {
			  motor_forward_straight();
		  } else if (robotState.data == MOVE_FORWARD_LEFT) {
			  motor_forward_left();
		  } else if (robotState.data == MOVE_FORWARD_RIGHT) {
			  motor_forward_right();
		  } else if (robotState.data == MOVE_BACKWARD_STRAIGHT) {
			  motor_backward_straight();
		  } else if (robotState.data == MOVE_BACKWARD_LEFT) {
			  motor_backward_left();
		  } else if (robotState.data == MOVE_BACKWARD_RIGHT) {
			  motor_backward_right();
		  } else if (robotState.data == MOVE_STATIONARY_LEFT) {
			  motor_stationary_left();
		  } else if (robotState.data == MOVE_STATIONARY_RIGHT) {
			  motor_stationary_right();
		  } else {
			  motor_stop();
		  }
	} else {
		motor_stop();
	}
	};
}

void tRedLED(void *argument) {
	red_led_init();
	while(1) {
		red_led_off();
		if (robotState.cmd == CMD_MOVE) {
		  osDelay(RED_LED_MOVE_DELAY);
		} else {
		  osDelay(RED_LED_STOP_DELAY);
		}
		red_led_on();
		if (robotState.cmd == CMD_MOVE) {
		  osDelay(RED_LED_MOVE_DELAY);
		} else {
		  osDelay(RED_LED_STOP_DELAY);
		}
	};
}

void tGreenLED(void *argument) {
	green_led_init();
	int counter = 0;
	while(1) {
		osMutexAcquire(myMutex, osWaitForever);
		if (robotState.cmd == CMD_MOVE) {
			counter = counter % 8;
		  green_led_running(counter);
			counter += 1;
		} else {
		  green_led_on();
			counter = 0;
		}
		osDelay(GREEN_LED_DELAY);
		osMutexRelease(myMutex);
	};
}

void tAudio(void *argument) {
	int counter = 0;
	int n_notes = UNDERWORLD_SIZE;
	const float dc = 0.1;
	
	while (1) {
		if (robotState.cmd == CMD_INIT) {
			continue;
		} else if (robotState.cmd == CMD_START) {
		  n_notes = UNDERWORLD_SIZE;
		} else if (robotState.cmd == CMD_END) {
			n_notes = GAME_OVER_SIZE;
		} else {
			n_notes = MAIN_THEME_SIZE;
		}
		
		counter = counter % n_notes;
		int pause_between_notes = 0;
		if (robotState.cmd == CMD_START) {
			pause_between_notes = play_underworld(counter, dc);
		} else if (robotState.cmd == CMD_END) {
			pause_between_notes = play_game_over(counter, dc);
		} else {
			pause_between_notes = play_main_theme(counter, dc);
		}
		
    osDelay(pause_between_notes);
		counter += 1;
	}
}

void tDecodeMsg(void *argument) {
	myDataPkt myData;
	
	while (1) {
		osMessageQueueGet(dataMsg, &myData, NULL, osWaitForever);
		robotState = myData;
		
		if (myData.cmd == CMD_START) {
			osEventFlagsSet(connect_flag, CONNECT_FLAG);
		}
	}
}

void tConnect(void *argument) {
	while (1) {
		osEventFlagsWait(connect_flag, CONNECT_FLAG, osFlagsWaitAny, osWaitForever);
		osMutexAcquire(myMutex, osWaitForever);
		green_led_off();
		osDelay(1000);
		green_led_on();
		osDelay(1000);
		green_led_off();
		osDelay(1000);
		green_led_on();
		osMutexRelease(myMutex);
	}
}

void clock_gating_init() {
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	
	SIM->SCGC5 |= (
		(SIM_SCGC5_PORTA_MASK) |
		(SIM_SCGC5_PORTB_MASK) | 
		(SIM_SCGC5_PORTC_MASK) | 
		(SIM_SCGC5_PORTD_MASK) |
		(SIM_SCGC5_PORTE_MASK) 
	);
}

void timer_gating_init () {
	/* select mcgfliclk as timer counter clock */
	SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
	
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;  
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;  
	
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
}

int main(void) {
	SystemCoreClockUpdate();
	clock_gating_init();
	timer_gating_init();
	
	robotState.cmd = CMD_INIT;
	robotState.data = MOVE_STOP;
	
	osKernelInitialize();
	
	osThreadNew(tBrain, NULL, NULL);
	osThreadNew(tMotorControl, NULL, NULL);
	osThreadNew(tRedLED, NULL, NULL);
	osThreadNew(tGreenLED, NULL, NULL);
	osThreadNew(tAudio, NULL, NULL);
	osThreadNew(tDecodeMsg, NULL, NULL);
	osThreadNew(tConnect, NULL, NULL);
	
	myMutex = osMutexNew(NULL);
	dataMsg = osMessageQueueNew(MSG_COUNT, sizeof(myDataPkt), NULL);
  connect_flag = osEventFlagsNew(NULL);
	
	osKernelStart();
	while(1);
}
