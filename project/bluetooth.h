#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <RTE_Components.h>
#include <cmsis_os2.h>

#define BAUD_RATE 9600
#define UART2_INT_PRIO 128

void bluetooth_init(uint32_t);

#endif
