#ifndef LED_H
#define LED_H

#define RED_LED_MOVE_DELAY 500
#define RED_LED_STOP_DELAY 250
#define GREEN_LED_DELAY 100

void green_led_init(void);
void green_led_running(int);
void green_led_on(void);
void green_led_off(void);
void red_led_init(void);
void red_led_toggle(void);
void red_led_off(void);
void red_led_on(void);

#endif
