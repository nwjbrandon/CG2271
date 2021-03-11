#include <MKL25Z4.h> 
#include "audio.h"
#include "constants.h"

// main theme melody
int main_theme_melody[MAIN_THEME_SIZE] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

// main theme tempo
int main_theme_tempo[MAIN_THEME_SIZE] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

// underworld melody
int underworld_melody[UNDERWORLD_SIZE] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

// underworld tempo
int underworld_tempo[UNDERWORLD_SIZE] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

int game_over_melody [GAME_OVER_SIZE] = {
  NOTE_C5, NOTE_G4, NOTE_E4, 
  NOTE_A4, NOTE_B4, NOTE_A4,
	NOTE_GS4, NOTE_AS4, NOTE_GS4,
  NOTE_G4, NOTE_D4, NOTE_E4,  
};

int game_over_tempo [GAME_OVER_SIZE] = {
	4, 4, 4, 
	8, 8, 8,
	8, 8, 8,
	8, 8, 2
};


int calculate_audio_period(
	int clock, int freq, int ps) {
	return clock / (freq * ps);
}  

int calculate_audio_duty_cycle(
	int clock, int freq, int ps, float dc) {
	return (int) (dc * (clock / (freq * ps)));
}  

void audio_init(int pwn_period, int pwm_duty_cycle) {	
	// Enable pwm for pin
	PORTB->PCR[LED_PTB0] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[LED_PTB0] |= PORT_PCR_MUX(3);

	// Set to epwm
	TPM1->SC &= ~((
	  TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK)
	);
	TPM1->SC|= TPM_SC_PS(7);
	TPM1->SC |= TPM_SC_CMOD(1);
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK);
	TPM1->MOD = pwn_period;
	TPM1_C0SC &= ~(
	  (TPM_CnSC_ELSB_MASK) | 
	  (TPM_CnSC_ELSA_MASK) | 
	  (TPM_CnSC_MSB_MASK) | 
	  (TPM_CnSC_MSA_MASK)
	);
	TPM1_C0SC |= (
	  TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)
	);
	TPM1_C0V = pwm_duty_cycle;
};

int play_main_theme(int counter, float dc) {
	const int ps = 128;
	
	const int pwm_period = calculate_audio_period(
		CLOCK_FREQ, main_theme_melody[counter], ps); 
  const int pwm_duty_cycle = calculate_audio_duty_cycle(
		CLOCK_FREQ, main_theme_melody[counter], ps, dc); 	
	
	audio_init(pwm_period, pwm_duty_cycle);
	
	int note_duration = 1000 / main_theme_tempo[counter];
	int pause_between_notes = note_duration * 1.30;
	return pause_between_notes;
};

int play_underworld(int counter, float dc) {
	const int ps = 128;
	
	const int pwm_period = calculate_audio_period(
		CLOCK_FREQ, underworld_melody[counter], ps); 
  const int pwm_duty_cycle = calculate_audio_duty_cycle(
		CLOCK_FREQ, underworld_melody[counter], ps, dc);
 	
	audio_init(pwm_period, pwm_duty_cycle);
	
	int note_duration = 1000 / underworld_tempo[counter];
	int pause_between_notes = note_duration * 1.30;
	return pause_between_notes;
};

int play_game_over(int counter, float dc) {
	const int ps = 128;
	
	const int pwm_period = calculate_audio_period(
		CLOCK_FREQ, game_over_melody[counter], ps); 
  const int pwm_duty_cycle = calculate_audio_duty_cycle(
		CLOCK_FREQ, game_over_melody[counter], ps, dc); 	
	
	audio_init(pwm_period, pwm_duty_cycle);
	
	int note_duration = 1000 / game_over_tempo[counter];
	int pause_between_notes = note_duration * 1.30;
	return pause_between_notes;
};



