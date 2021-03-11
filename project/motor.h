#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_PS 128
#define MOTOR_FREQ 400
#define MOTOR_HIGH 0.9
#define MOTOR_HALF 0.3
#define MOTOR_LOW 0
#define MOTOR_DC0 0

void motor_stop(void);
void motor_forward_straight(void);
void motor_forward_left(void);
void motor_forward_right(void);
void motor_backward_left(void);
void motor_backward_right(void);
void motor_backward_straight(void);
void motor_init(void);
void motor_control(int, int, int, int);
void motor_stationary_left(void);
void motor_stationary_right(void);

#endif
