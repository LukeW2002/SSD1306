#include <libopencm3/stm32/i2c.h>
#include "i2c.h"

uint16_t i2cReadSeq(uint32_t i2c, uint16_t address, uint8_t reg, uint8_t *data, uint16_t length)
{
    while ((I2C_SR2(i2c) & (I2C_SR2_BUSY)));;
    i2c_enable_ack(i2c);
    i2c_send_start(i2c);

    /* Check if the start bit is sent, is in master/slave mode or bus is busy*/
    while(!((I2C_SR1(i2c) & I2C_SR1_SB) & (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, address, I2C_WRITE);

    /* Check if Data register is empy, Address is recieved, master/slave mode or if bus is busy or if its a transmitter/reciever*/
    while(!( (I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_ADDR)) ) & (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)));

    i2c_send_data(i2c, reg);

    /* Check if Data register is empy, data is recieved, master/slave mode or if bus is busy or if its a transmitter/reciever*/
    while(!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) ) & (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)));

    i2c_send_start(i2c);

    /* Check if the start bit is sent and if the dataline is busy*/
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) & (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, address, I2C_READ);

    /* Check if address is recieved and dataline is buy*/
    while (!( (I2C_SR1(i2c) & (I2C_SR1_ADDR)) & (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    uint16_t i;
    for(i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            i2c_disable_ack(i2c);
            i2c_send_stop(i2c);
        }
        /* Checks if data register is empty*/
        while (!(I2C_SR1(i2c) & I2C_SR1_RxNE));
        data[i] = i2c_get_data(i2c);
    }

    /* Waits until data bus is free*/
    while ((I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY)));

    return ++i;
}

uint16_t i2cWriteSeq(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t *data, uint16_t len) {

    while ((I2C_SR2(i2c) & (I2C_SR2_BUSY)));

    i2c_enable_ack(i2c);
    i2c_send_start(i2c);

    /* Check if the start bit is sent, is in master/slave mode or bus is busy*/
    while (!((I2C_SR1(i2c) & I2C_SR1_SB) & (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))));

    i2c_send_7bit_address(i2c, addr, I2C_WRITE);

    /* Check if Data register is empy, Address is recieved, master/slave mode or if bus is busy or if its a transmitter/reciever*/
    while (!(  (I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_ADDR)) & (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)) ));

    i2c_send_data(i2c, reg);

    /* Check if Data register is empy, data is recieved, master/slave mode or if bus is busy or if its a transmitter/reciever*/
    while (!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) & (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA))));

    uint16_t i;
    for (i = 0; i < len; i++) {
        i2c_send_data(i2c, data[i]);

        /* Check if Data register is empy, data is recieved, master/slave mode or if bus is busy or if its a transmitter/reciever*/
        while (!((I2C_SR1(i2c) & (I2C_SR1_TxE | I2C_SR1_BTF)) &  (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA))));
    }

    i2c_send_stop(i2c);

    /* Waits until data bus is free*/
    while ((I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY)));

    return ++i;
}

void i2cWriteReg(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t data) {
    i2cWriteSeq(i2c, addr, reg, &data, 1);
}

uint8_t i2cReadReg(uint32_t i2c, uint16_t addr, uint8_t reg) {
    uint8_t data;
    i2cReadSeq(i2c, addr, reg, &data, 1);
    return data;
}

void i2cSetBitField(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base, uint8_t len, uint8_t data) 
{
    uint8_t rdata = 0;
    rdata = i2cReadReg(i2c, addr, reg);
    uint8_t mask = 0xFF & ((0xFF << (base + len)) | 0xFF >> (8 - base));
    rdata &= mask;
    data <<= base;
    data &= ~mask;
    rdata |= data;
    i2cWriteReg(i2c, addr, reg, rdata);
}

void i2cCleanBitField(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base, uint8_t len) 
{
    uint8_t rdata = 0;
    rdata = i2cReadReg(i2c, addr, reg);
    uint8_t mask = 0xFF & ((0xFF << (base + len)) | 0xFF >> (8 - base));
    rdata &= mask;
    i2cWriteReg(i2c, addr, reg, rdata);
}


void i2cSetOneBit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base) 
{
    uint8_t rdata = i2cReadReg(i2c, addr, reg);
    rdata |= (1 << base);
    i2cWriteReg(i2c, addr, reg, rdata);
}

void i2cCleanOneBit(uint32_t i2c, uint16_t addr, uint8_t reg, uint8_t base) 
{
    uint8_t rdata = i2cReadReg(i2c, addr, reg);
    rdata &= ~(1 << base);
    i2cWriteReg(i2c, addr, reg, rdata);
}
