#pragma once
#include <libopencm3/stm32/usart.h>
void usartSendString(const char *str);
void usartSendData(const char *str, int16_t data);


void sendXon(void);
void sendXoff(void);
void usartSoftwareFlow(void);