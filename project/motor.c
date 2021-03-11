#include <MKL25Z4.h> 
#include "motor.h"
#include "constants.h"

int calculate_motor_period(
	int clock, int freq, int ps) {
	return clock / (freq * ps);
}  

int calculate_motor_duty_cycle(
	int clock, int freq, int ps, float dc) {
	return (int) (dc * (clock / (freq * ps)));
}  

void motor_init() {
	int ps = MOTOR_PS;
	int freq = MOTOR_FREQ;
	
	int pwm_period = calculate_motor_period(
		CLOCK_FREQ, freq, ps); 
	
	// Enable pwm for pin
	PORTD->PCR[LED_PTD2] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[LED_PTD2] |= PORT_PCR_MUX(4);
	PORTD->PCR[LED_PTD3] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[LED_PTD3] |= PORT_PCR_MUX(4);
	PORTD->PCR[LED_PTD4] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[LED_PTD4] |= PORT_PCR_MUX(4);
	PORTD->PCR[LED_PTD5] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[LED_PTD5] |= PORT_PCR_MUX(4);
	
	// Set to epwm
	TPM0->SC &= ~((
	  TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK)
	);
	TPM0->SC|= TPM_SC_PS(7);
	TPM0->SC |= TPM_SC_CMOD(1);
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	TPM0->MOD = pwm_period;
	
	TPM0_C2SC &= ~(
	  (TPM_CnSC_ELSB_MASK) | 
	  (TPM_CnSC_ELSA_MASK) | 
	  (TPM_CnSC_MSB_MASK) | 
	  (TPM_CnSC_MSA_MASK)
	);
	TPM0_C2SC |= (
	  TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)
	);
	TPM0_C3SC &= ~(
	  (TPM_CnSC_ELSB_MASK) | 
	  (TPM_CnSC_ELSA_MASK) | 
	  (TPM_CnSC_MSB_MASK) | 
	  (TPM_CnSC_MSA_MASK)
	);
	TPM0_C3SC |= (
	  TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)
	);
	TPM0_C4SC &= ~(
	  (TPM_CnSC_ELSB_MASK) | 
	  (TPM_CnSC_ELSA_MASK) | 
	  (TPM_CnSC_MSB_MASK) | 
	  (TPM_CnSC_MSA_MASK)
	);
	TPM0_C4SC |= (
	  TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)
	);
	TPM0_C5SC &= ~(
	  (TPM_CnSC_ELSB_MASK) | 
	  (TPM_CnSC_ELSA_MASK) | 
	  (TPM_CnSC_MSB_MASK) | 
	  (TPM_CnSC_MSA_MASK)
	);
	TPM0_C5SC |= (
	  TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)
	);
	
	TPM0_C2V = 0;
	TPM0_C3V = 0;
	TPM0_C4V = 0;
	TPM0_C5V = 0;
}


void motor_control(
	int a1, int a2, int b1, int b2) {
	// high for channels to drive car forward else low
	TPM0_C2V = a1;
	TPM0_C3V = a2;
	TPM0_C4V = b1;
	TPM0_C5V = b2;
}


void motor_forward_straight() {
  int left_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
  int right_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
	motor_control(MOTOR_DC0, left_dc, right_dc, MOTOR_DC0);
}

void motor_forward_left() {
  int left_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
  int right_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HALF); 
	motor_control(MOTOR_DC0, left_dc, right_dc, MOTOR_DC0);
}

void motor_forward_right() {
  int left_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HALF); 
  int right_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
	motor_control(MOTOR_DC0, left_dc, right_dc, MOTOR_DC0);
}

void motor_backward_left() {
  int left_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
  int right_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HALF); 
	motor_control(left_dc, MOTOR_DC0, MOTOR_DC0, right_dc);
}

void motor_backward_right() {
  int left_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HALF); 
  int right_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
	motor_control(left_dc, MOTOR_DC0, MOTOR_DC0, right_dc);
}

void motor_backward_straight() {
  int left_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
  int right_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
	motor_control(left_dc, MOTOR_DC0, MOTOR_DC0, right_dc);
}

void motor_stationary_left() {
  int left_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
  int right_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
	motor_control(left_dc, MOTOR_DC0, right_dc, MOTOR_DC0);
}

void motor_stationary_right() {
  int left_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
  int right_dc = calculate_motor_duty_cycle(
		CLOCK_FREQ, MOTOR_FREQ, MOTOR_PS, MOTOR_HIGH); 
	motor_control(MOTOR_DC0, left_dc, MOTOR_DC0, right_dc);
}


void motor_stop() {
	motor_control(MOTOR_DC0, MOTOR_DC0, MOTOR_DC0, MOTOR_DC0);
}
