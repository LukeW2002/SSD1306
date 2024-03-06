
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "firmwareMPU6050.h"
#include "uart.h"
#include "kalman.h"
#include "math.h"


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
	nvic_enable_irq(NVIC_USART2_IRQ);
	usart_enable_rx_interrupt(USART2);

	usart_enable(USART2);
}

static void gpioSetup(void)
{
	//USART
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2);

	//I2C
	gpio_mode_setup(I2C_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, I2C_SDA | I2C_SCL);
	gpio_set_output_options(I2C_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_25MHZ, I2C_SDA | I2C_SCL);
	gpio_set_af(I2C_PORT, GPIO_AF4, I2C_SDA | I2C_SCL);
}


static void i2cSetup(void)
{
	rcc_periph_reset_pulse(RST_I2C1);
	i2c_peripheral_disable(I2C1);

	i2c_set_standard_mode(I2C_PORT);
	i2c_set_clock_frequency(I2C_PORT, I2C_CR2_FREQ_8MHZ);
	i2c_set_ccr(I2C_PORT, 0x1);

	i2c_set_speed(I2C1, i2c_speed_fm_400k, 8);
	i2c_set_fast_mode(I2C1);
	i2c_enable_ack(I2C1);

	i2c_set_trise(I2C_PORT, 0x9);
	
	i2c_peripheral_enable(I2C1);
}

void kalmanInit(kalmanData *kf)
{

	///Initialisation
	setZeroVector(kf->X,  STATES);
	setZeroVector(kf->fx, STATES);
	setZeroVector(kf->hx, MEASURED);

	setZero(kf->P, 	STATES,   STATES);
	setZero(kf->Q, 	STATES,   STATES);
	setZero(kf->R, 	MEASURED, MEASURED);
	setZero(kf->K, 	STATES,   MEASURED);
	setZero(kf->F, 	STATES,   STATES);
	setZero(kf->H, 	MEASURED, STATES);
	setZero(kf->Ht, STATES,   STATES);
	setZero(kf->Ft, STATES,   STATES);
	setZero(kf->Pp, STATES,   STATES);
	//yaw bias is 0.001
	//Initial Values
	setIdentity(kf->P, STATES, STATES);
	setZero(&kf->F, STATES, STATES);
	setZeroVector(kf->fx, STATES);
	
	//H, F are handelled in the model step.
}

void scalarMultiplyMatrix(double scalar, double *matrix, uint8_t rowsM1, uint8_t colsM1)
{
	for( int i = 0; i < rowsM1; i++)
	{
		for( int j =0; j < colsM1; j++ )
		{
			matrix[i*colsM1 + j] *= scalar;
		}
	}
}

double *quanternion3Dproject(double *quanternion, double *vector, uint8_t dimension)
	//Needs to handle non 3d inputs
	//bad name
{
	double x = quanternion[0];
	double y = quanternion[1];
	double z = quanternion[2];
	double w = quanternion[3];

	double diagonal = w*w + x*x - y*y - z*z; 

	double projectionMatrix[MEASURED*MEASURED] =
	{
		diagonal, 2*(x*y - w*z), 2*(x*z + w*y),
		2*(x * y + w * z), diagonal, 2*(y*z - w *x),
		2*(x * z - w * y), 2*(w*x + y * z), diagonal 
	};

	double result[MEASURED] = {0}; 
	vectorMatrixMultiply(projectionMatrix, vector, result, MEASURED, MEASURED, MEASURED);

	return result;
}

void normalise(double *vector, double *result, uint8_t dimension)
{
	double sum = {0};
	for ( int j = dimension; 0 < j; j--)
	{
		sum += vector[j]*vector[j];
	};

	for (int i = 0; i < dimension; i++)	
	{
		vector[i] = (1/sum) * vector[i];
	};
}

void exteriorProduct(double *vector1, double *result, uint8_t dimension)
{
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			( j % 2 == 0 ? result[i] *= -vector1[j] : result[i] *= vector1[j]);
		}
	}
}

void eulerRodriguesQuanternion(kalmanData *kf, mpu_t *mpu)
{
	double sensor[3] = {0};
	for (int i = 0; i < 4; i++)
	{
		sensor[i] = mpu->sensorData[4+i];
	}

	double norm = sqrt( sensor[0] * sensor[0] + sensor[1] * sensor[1] + sensor[2] * sensor[2]);
	if (norm < 1e-6) 
	{
		//angular velocity is near enough 0. Avoids division by zero.
		return;
	}
	double angle = norm*dt;
	kf->Xp[0] += a
}

void model(kalmanData *kf, mpu_t *mpu, double *offset)
{
	// Be warned for all thee who enter here

	// We are going to have a state vector X = { q3, q2, q1, q0, bx, by, bz}. Where q3-q0 are quanternion components and bx,by,bz are the bias in the gyro

	// Process Model, modelling the dynamics of the systems based on time, good to look into quanternions and quanternion dynamics
	// The kinematics equation: q(t) = q(t-1) [x] exp( (\omega * dt) / 2 ). where [x] denotes the quanternion multiplication operator, exp is the vector form of the exponential
	// This defines the State Transition function, q(t) = f(q(t-1), u(t), dt). u(t) is control inputs and set to zero.
	// We are getting angular velocity as input, We first use euler-Rodrigues rotation formula to put it into quanternion form

	// Initialising kf->X as 0 vector
	


}


int main(void)
{
	// Initialise Ports
	clockSetup();
	gpioSetup();
	usartSetup();
	i2cSetup();
	printf("Everything is initialised...\r\n");

	// Initialise Sensors
	mpu_t mpu;
	mpu.i2c = I2C1;
	mpu.addr = 0x68;
	mpuSetup(&mpu);

	int16_t offset[6] = {0};
	int16_t sensorsRaw[6] = {0};
	double sensorsInit[6] = {0};
	memcpy(mpu.rawSensorData, sensorsRaw, sizeof(sensorsRaw));
	memcpy(mpu.sensorData, sensorsInit, sizeof(sensorsInit));

	calculateOffset(&mpu, offset);

	mpuFixData(&mpu, offset);
	kalmanData kf;
	kalmanInit(&kf);
	model(&kf, &mpu);
	while (1)
	{
		gpio_toggle(GPIOA, GPIO5 | GPIO2);
		mpuFixData(&mpu, offset);
		for (uint8_t i = 0; i < ARRAY_LENGTH(mpu.sensorData); i++)
		{
			(i < 3 ? usartSendData("Accel (x,y,z) data: ", mpu.sensorData[i]) : usartSendData("Gyro (x,y,z) Data: ", mpu.sensorData[i]));
		}
		delayMs(500);

	}

	return 0; //Never
}
