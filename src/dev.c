/**********************************************
* Abstraction layer for ATiny1616
*
* Function for manage register for config low  
* power clock, sleed mode and ADC.
*
* Autor: Jose Martel
* [19/12/22]
*
**********************************************/


#include "dev.h"

uint8_t ReadFlag = 1;

void GPIO_Init(void)
{
    PORTB.DIR |= PIN0_bm; // Output PULSE0
    PORTB.DIR |= PIN1_bm; // Output PULSE1

    PORTC.DIR |= PIN0_bm; // Output EN0
    PORTC.DIR |= PIN1_bm; // Output EN1
}

void CLK_Init(void) 
{   
    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLB &= ~CLKCTRL_PEN_bm;

    CPU_CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCULP32K_gc;

    while (CLKCTRL.MCLKSTATUS & CLKCTRL_SOSC_bm)
    {
        ;
    }

}

void LP_Init(void)
{   
    SLPCTRL_CTRLA = SLPCTRL_SMODE_STDBY_gc | SLPCTRL_SEN_bm;
}

void ADC_Init(void)
{
    ADC0.CTRLA |= ADC_ENABLE_bm;
    // Config default values
}

void ADC_Stop(void)
{   
    // Disable ADC
    ADC0.CTRLA &= ~ADC_ENABLE_bm;
}

uint16_t ADC_Read(uint8_t channel){

    uint16_t rValue;

    ADC0.MUXPOS = (channel & 0x1F);
    ADC0.CTRLA |= ADC_ENABLE_bm;
    ADC0.COMMAND |= ADC_STCONV_bm;

    while(ADC0.COMMAND & ADC_STCONV_bm){}
    ADC0.CTRLA &= ~ADC_ENABLE_bm;

    rValue = ADC0_RES;
    return rValue;
}

void TCB_Init(void){
    TCB0_CCMP = 3276; // Top value 
    //TCB0.CTRLA |= TCB_ENABLE_bm | TCB_RUNSTDBY_bm; // Running in sleep mode & start counter
    TCB0.CTRLA = TCB_CLKSEL_CLKDIV1_gc | TCB_ENABLE_bm | TCB_RUNSTDBY_bm;
    TCB0.INTCTRL = TCB_CAPT_bm;
}

uint8_t getReadFlag(void){
    return ReadFlag;
}

void setReadFlag(uint8_t value){
    ReadFlag = value;
}

void write_PULSE1(int8_t value){

    if(value == 1)
        PORTB.OUT |= PIN1_bm;
    else
        PORTB.OUT &= ~(PIN1_bm);
    
}

void write_PULSE0(int8_t value){

    if(value == 1)
        PORTB.OUT |= PIN0_bm;
    else
        PORTB.OUT &= ~(PIN0_bm);

}

void write_ENABLE0(uint8_t value){

    if(value == 1)
        PORTC.OUT |= PIN0_bm;
    else
        PORTC.OUT &= ~(PIN0_bm);

}

void write_ENABLE1(uint8_t value){

    if(value == 1)
        PORTC.OUT |= PIN1_bm;
    else
        PORTC.OUT &= ~(PIN1_bm);

}

ISR(TCB0_INT_vect)
{   
    TCB0.INTFLAGS = TCB_CAPT_bm;
    // PORTB.IN = PIN1_bm;
    //setReadFlag(1);
}