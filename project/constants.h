#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <MKL25Z4.h> 
#include <RTE_Components.h>
#include <cmsis_os2.h>

// port a pins
#define LED_PTA1 1 // green led
#define LED_PTA2 2
#define LED_PTA4 4 // green led
#define LED_PTA5 5 // green led
#define LED_PTA12 12 // green led
#define LED_PTA13 13
#define LED_PTA16 16
#define LED_PTA17 17

// port b pins
#define LED_PTB0 0 // audio
#define LED_PTB1 1
#define LED_PTB2 2
#define LED_PTB3 3 // red led
#define LED_PTB8 8 // red led
#define LED_PTB9 9 // red led
#define LED_PTB10 10 // red led
#define LED_PTB11 11 // red led

// port c pins
#define LED_PTC0 0 // green led
#define LED_PTC1 1 // red led
#define LED_PTC2 2 // red led
#define LED_PTC3 3 // green led
#define LED_PTC4 4
#define LED_PTC5 5
#define LED_PTC6 6
#define LED_PTC7 7
#define LED_PTC8 8 // green led
#define LED_PTC9 9
#define LED_PTC10 10 // green led 
#define LED_PTC11 11
#define LED_PTC12 12
#define LED_PTC13 13
#define LED_PTC16 16
#define LED_PTC17 17

// port d pins
#define LED_PTD0 0 // 
#define LED_PTD1 1 // debug pin
#define LED_PTD2 2 // left motor
#define LED_PTD3 3 // left motor
#define LED_PTD4 4 // right motor
#define LED_PTD5 5 // right motor
#define LED_PTD6 6
#define LED_PTD7 7

// port e pins
#define LED_PTE0 0
#define LED_PTE1 1
#define LED_PTE2 2 // red led
#define LED_PTE3 3
#define LED_PTE4 4 
#define LED_PTE5 5 
#define LED_PTE20 20 
#define LED_PTE21 21
#define LED_PTE22 22 // uart tx pin
#define LED_PTE23 23 // uart rx pin
#define LED_PTE29 29 // red led
#define LED_PTE30 30 // red led

#define CONNECT_FLAG 0x0001

// robot states
#define CMD_INIT 0x00
#define CMD_START 0x01
#define CMD_STOP 0x02
#define CMD_MOVE 0x03
#define CMD_END 0x04

#define MOVE_STOP 0x00
#define MOVE_FOWARD_STRAIGHT 0x01
#define MOVE_FORWARD_LEFT 0x02
#define MOVE_FORWARD_RIGHT 0x03
#define MOVE_BACKWARD_STRAIGHT 0x04
#define MOVE_BACKWARD_LEFT 0x05
#define MOVE_BACKWARD_RIGHT 0x06
#define MOVE_STATIONARY_LEFT 0x07
#define MOVE_STATIONARY_RIGHT 0x08

typedef struct {
	uint8_t cmd;
	uint8_t data;
} myDataPkt;

extern uint32_t MSG_COUNT;
extern volatile osMessageQueueId_t dataMsg;

extern volatile myDataPkt cmd;

// debugging
#define LED_RED_PIN 18 
#define LED_GREEN_PIN 19 
#define LED_BLUE_PIN 1 

// misc
#define CLOCK_FREQ 48000000
#define MASK(x) (1 << (x))

void debug_led_init(void);
void debug_led_off(void);
void debug_led_red_on(void);
void debug_led_blue_on(void);
void debug_led_green_on(void);

#endif
