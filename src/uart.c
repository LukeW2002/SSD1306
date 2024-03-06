
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>

#define XON 0x11
#define XOFF 0x13

volatile bool transimissionEnabled = true;

void sendXon(void)
{
	usart_send_blocking(USART2, XON);
}

void sendXoff(void)
{
	usart_send_blocking(USART2, XOFF);
}

void usartSoftwareFlow(void)
{
	if (usart_get_flag(USART2, USART_FLAG_RXNE))
	{
		char recievedData = usart_recv(USART2);
		switch (recievedData)
		{
		case XOFF:
			transimissionEnabled = false;
			break;
		
		default:
			transimissionEnabled = true;
			break;
		}
	}
}

void usartSendString(const char *str)
{
    while (*str)
    {
        usart_send_blocking(USART2, *str);
        str++;
    }
	usart_send_blocking(USART2, '\n');
	usart_send_blocking(USART2, '\r');
	usart_send_blocking(USART2, '\0');
}

void usartSendData(const char *str, int16_t data)
{
	if (transimissionEnabled)
	{

 	   while (*str)
 	   {
 	       usart_send_blocking(USART2, *str);
 	       str++;
 	   }
		char buffer[128];
		sprintf(buffer, "%d", data);
		char *ptr = buffer;
		while (*ptr)
		{
			usart_send_blocking(USART2, *ptr);
			ptr++;
		}
		usart_send_blocking(USART2, '\n');
		usart_send_blocking(USART2, '\r');
		usart_send_blocking(USART2, '\0');
	}
	else
	{
		sendXoff();
		while(!transimissionEnabled);
	}
}

int _write(int file, char *ptr, int len) 
{
    int i;
    for (i = 0; i < len; i++) {
        usart_send_blocking(USART2, ptr[i]);
    }
    return len;
}