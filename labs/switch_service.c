#include "delay_service.h" 
#include "utils.h"
#include "switch_service.h"
#include "led_service.h"
#include "interrupt_service.h"
#include "MKL25Z4.h" 

void switch_button_init(void) {
	// enable clock for PortD
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	/* Select GPIO and enable pull-up resistors and interrupts on
	falling edges of pin connected to swtich
	*/
	PORTD->PCR[SWITCH_BUTTON_PIN] |= (PORT_PCR_MUX(1) |
	                                                        PORT_PCR_PS_MASK |
	                                                        PORT_PCR_PE_MASK |
	                                                        PORT_PCR_IRQC(0x0a));
	
	// Set  PORT D Switch bit to input
	PTD->PDDR &= ~MASK(SWITCH_BUTTON_PIN);
	
	// Enable Interrupts
	NVIC_SetPriority(PORTD_IRQn, 2);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
}


