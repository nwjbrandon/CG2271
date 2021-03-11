#include <MKL25Z4.h> 
#include "constants.h"

void debug_led_off() {
	PTB->PDOR |= MASK(LED_RED_PIN);
	PTB->PDOR |= MASK(LED_GREEN_PIN);
	PTD->PDOR &= ~MASK(LED_BLUE_PIN);
}

void debug_led_init() {
	PORTB->PCR[LED_RED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_RED_PIN] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[LED_GREEN_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_GREEN_PIN] |= PORT_PCR_MUX(1);
	
	PORTD->PCR[LED_BLUE_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[LED_BLUE_PIN] |= PORT_PCR_MUX(1);
	
	PTB->PDDR |= (MASK(LED_RED_PIN) | MASK(LED_GREEN_PIN));
	PTD->PDDR |= MASK(LED_BLUE_PIN);
	
	debug_led_off();
}

void debug_led_red_on() {
	PTB->PDOR &= ~MASK(LED_RED_PIN);
	PTB->PDOR |= MASK(LED_GREEN_PIN);
	PTD->PDOR |= MASK(LED_BLUE_PIN);
}

void debug_led_blue_on() {
	PTB->PDOR |= MASK(LED_RED_PIN);
	PTB->PDOR |= MASK(LED_GREEN_PIN);
	PTD->PDOR &= ~MASK(LED_BLUE_PIN);
}

void debug_led_green_on() {
	PTB->PDOR |= MASK(LED_RED_PIN);
	PTB->PDOR &= ~MASK(LED_GREEN_PIN);
	PTD->PDOR |= MASK(LED_BLUE_PIN);
}
