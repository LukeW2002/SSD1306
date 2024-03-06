#ifndef i2c_h
#define i2c_h
#include <libopencm3/stm32/i2c.h>

uint16_t i2cReadSeq(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t *data, uint16_t len);
uint16_t i2cWriteSeq(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t *data, uint16_t len);

void i2cWriteReg(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t data);
uint8_t i2cReadReg(uint32_t i2c, uint16_t addr, uint8_t reg);

void i2cSetBitField(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base, uint8_t len, uint8_t data);
void i2cCleanBitField(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base, uint8_t len);
void i2cSetOneBit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base); 
void i2cCleanOneBit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base); 
#endif