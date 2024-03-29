#pragma once
#include <libopencm3/stm32/usart.h>

static void gpioSetup(void);
static void usartSetup(void);
static void clockSetup(void);
static void i2cSetup(void);
void i2cScan(void);

void usartSendString(const char *str);
void usartSendData(const char *str, int16_t data);


void sendXon(void);
void sendXoff(void);
void usartSoftwareFlow(void);
