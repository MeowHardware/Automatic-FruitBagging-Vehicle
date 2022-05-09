#ifndef __STM32PCA9685_H
#define __STM32PCA9685_H	

#include "stm32f1xx_hal.h"

#define PCA9685_adrr 0x40

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

void PCA9685_Reset(I2C_HandleTypeDef *h);
void PCA9685_Go(void);
void SetPWMFreq(float freq);
void SetPWM(uint32_t num,uint32_t on,uint32_t off);
uint8_t PCA9685_read(uint8_t startAddress);

void PCA9685_write(uint8_t startAddress, uint8_t buffer);

#endif

