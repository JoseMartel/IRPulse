#ifndef __DEV_H__
#define __DEV_H__

#define F_CPU 32768 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

void CLK_Init(void);
void GPIO_Init(void);
void ADC_Init(void);
void TIM_Init(void);
void LP_Init(void);
void ADC_Stop(void);
uint16_t ADC_Read(uint8_t channel);
void TCB_Init(void);
uint8_t getReadFlag(void);
void setReadFlag(uint8_t value);
void write_PULSE0(int8_t value);
void write_PULSE1(int8_t value);
void write_ENABLE0(uint8_t value);
void write_ENABLE1(uint8_t value);
#endif // __DEV_H__