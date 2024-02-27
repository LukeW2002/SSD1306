
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/usart.h>

#include "main.h"
#include "firmwareSSD1306.h"

#define I2C_PORT GPIOB
#define I2C_SCL GPIO8
#define I2C_SDA GPIO9

static void clockSetup(void)
{
	//USART
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_USART2);

	//I2C
	rcc_periph_clock_enable(RCC_I2C1);
	rcc_periph_clock_enable(RCC_GPIOB);
}

static void usartSetup(void)
{
	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
	usart_enable(USART2);
}

static void gpioSetup(void)
{
	//USART
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

	//I2C
	gpio_mode_setup(I2C_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, I2C_SDA | I2C_SCL);
	gpio_set_af(I2C_PORT, GPIO_AF4, I2C_SDA | I2C_SCL);
}


static void i2cSetup(void)
{
	rcc_periph_reset_pulse(RST_I2C1);
	i2c_peripheral_disable(I2C1);

	i2c_set_speed(I2C1, i2c_speed_fm_400k, 8);
	i2c_set_fast_mode(I2C1);
	
	i2c_peripheral_enable(I2C1);
}



int main(void)
{
	int i;

	clockSetup();
	gpioSetup();
	usartSetup();
    usartSendString("USART initialised\n\r");
	i2cSetup();
    usartSendString("I2C initialised!\n\r");
	init(I2C1, 0x3C, 128, 32);
    usartSendString("Worked!\n\r");

	while (1) {
		gpio_toggle(GPIOA, GPIO5);	/* LED on/off */
		for (i = 0; i < 300000; i++) {	/* Wait a bit. */
			__asm__("NOP");
		}
	}

	return 0;
}
