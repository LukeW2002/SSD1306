#pragma once
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/exti.h>
#include "pentacom_font.h"


#define _set(x) (1 << (x))
#define _clear(x) ( ~(1 << x))

//ADAFRUIT SSD1306 DATASHEET
#define DEFAULT_ADDRESS 0x3C //p.20 8.1.5.2
#define DEFAULTBUFFER 1024
#define COMMAND 0x00
#define DATA 0x400
#define DATAONLY (uint8_t)0b01000000

//p.28 TABLE 9-1 COMMAND TABLE
#define SET_CONTRAST_CONTROL 0x81 // DOUBLE BYTE COMMAND TO SELECT 1 OUT OF 256 CONTRASTS STEPS. CONTRAST INCREASES AS THE VALUE INCREASES
#define RESET 0x7F
#define DISPLAY_ON_RAM  0xA4    // RESUME TO RAM CONTENT DISPLAY
#define DISPLAY_NO_RAM  0xA5    // OUPUT IGNORES RAM CONTENT
#define SET_NORMAL      0xA6    // NORMAL DISPLAY
#define SET_INVERSE     0xA7    // INVERSE DISPLAY
#define SET_DISPLAY_OFF 0xAE    // DISPLAY OFF (SLEEP)
#define SET_DISPLAY_ON  0xAF    // DISPLAY ON (NORMAL) 

//p.30 TABLE 9-3 ADDRESSING SETTING COMMAND
#define SET_MEMORY_ADDRESSING   0x20 // I think it defines how the scan lines are done
#define SET_COLUMN_ADDRESS      0x21 // DEFINES A COLUMN POINTER, USED TO DEFINE EACH PIXEL
#define SET_PAGE_MEMORY_ADDRESS 0x22 // SETS PAGE ADDRESS, DIFFERENT WAY OF DEFINING THE ARRAY

//p.31 TABLE 9-4 HARDWARE CONFIG
#define SET_MULTIPLEX_RATIO 0xA8 // How many rows of pixels are controlled simultaneously while scanning through the columns
#define SET_COM_PINS        0xDA // common pins are the row drivers used to select which row of pixels to active

//p.32 TABLE 9-5 TIMING
#define SET_DISPLAY_CLOCK 0xD5 
#define SET_PRE_CHARGE    0xD9   // small voltage applied to the leds pixels to fix any stuck pixels?
#define SET_VCOM          0xDB   // SETS COMMON VOLTAGE, EFFECTS MAINLY BATTERY AND BRIGHTNESS ETC

//CHARGE PUMP (no clue why this is on a seperate thing, see p.60)
#define SET_CHARGE_PUMP 0x8D // needs to be turned on, pumps the voltage up to the needed amount.

#define _IF_SB(i2c) ((I2C_SR1(i2c) & I2C_SR1_SB) == 0)      // IF START BIT IS NOT SET THEN RESULT IS ZERO INDICATING THAT START BIT HAS BEEN SENT
#define _IF_BTF(i2c) ((I2C_SR1(i2c) & I2C_SR1_BTF) == 0)    // IF BYTE TRANSFER FINISHED FLAG IS NOT SET THEN RESULT IS ZERO INDICATING TRANSFER IS NOT FINISHED
#define _IF_ADDR(i2c) ((I2C_SR1(i2c) & I2C_SR1_ADDR) == 0)  // IF ADDRESS FLAG IS NOT SET THEN RESULT IS ZERO INDICATING THAT ADDRESS HAS NOT BEEN SENT OR RECIEVED
#define _IF_TxE(i2c) ((I2C_SR1(i2c) & I2C_SR1_TxE) == 0)      // IF TRANSMIT BUFFER FLAG IS NOT SET THEN RESULT WILL BE NON ZERO INDICATING THAT THE TRANSMIT BUFFER IS READY FOR TRANSMISSION

typedef enum addressingMode
{
    Horizontal = 0b00,
    Vertical   = 0b01,
    Page       = 0b10,
    INVALID    = 0b11
} MODE;

typedef enum color 
{
    white = 0,
    black = 1
} color;

typedef enum wrap 
{
    nowrap,
    wrapDisplay,
    wrapCoord
} WrapType;


void start(void);
void stop(void);
void sendAddress(uint8_t spec);
void sendData(uint8_t spec, uint8_t data);
void displayOnOff (bool displaySwitch);
void setOscillatorFrequency(uint8_t value);
void setMultiplexRatio(uint8_t value);
void setInverse(bool inverseSwitch);
void chargePump(bool chargePumpSwitch);
void setConstrast(uint8_t value);
void setPrecharger(uint8_t value);
void setCompPinsConfig(uint8_t value);
void ledOnOff(bool ledSwitch);
void setVcomLevel(uint8_t value);
void setMemoryAddressingMode(MODE mode);
void setColumnAdress(uint8_t lower, uint8_t upper);
void setPageAdress(uint8_t lower, uint8_t upper);
void clear(void);
void refresh(void);
void init(uint32_t i2c, uint8_t address, uint8_t width, uint8_t height);

void ssd1306_drawVPattern(uint8_t x, int8_t y, uint8_t pattern); 
void ssd1306_drawWCharStr(uint8_t x, int8_t y, color color, WrapType wrType, wchar_t *str);


void usartSendString(const char *str);