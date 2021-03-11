#include "delay_service.h"

/* 
 * Delay program through cycles.
 * SystemCoreClock has a frequency of 20,971,520 Hz.
 * Setting duration to 0x0FFFFF = 1,048,575 delay 1/20 of a second.
*/
void delay_program(unsigned int duration) {
	unsigned int delay_counter = 0;
	while (1) {
		delay_counter++;
		if (delay_counter > duration) {
			delay_counter = 0;
			break;
		}
	}
}
