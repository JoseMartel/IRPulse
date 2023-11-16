/*  Ultra low power IR pulse counter  */

/*  Device to counter pulse reflected using a 
    IR transmitter-receiver and a ATiny1616 running 
    at 32768 Hz in ultra low power and deep sleep
*/

/**********************************************
* Ultra low power IR pulse counter
*
* Device to counter pulse reflected using a 
* IR transmitter-receiver and a ATiny1616 running 
* at 32768 Hz in ultra low power and deep sleep
*
* Autor: Jose Martel
* [19/12/22]
*
**********************************************/

#include "main.h"

void main (void)
{
    uint16_t ADCValue0 = 0;
    uint16_t ADCValue1 = 0;

    CLK_Init();
    GPIO_Init();

    TCB_Init();
    LP_Init();
    
    sei();
    write_ENABLE0(1);
    write_ENABLE1(1);
    set_sleep_mode(SLEEP_MODE_STANDBY);

    while(1){

        write_ENABLE0(0);   /* Enable ADC */
        ADCValue0 = ADC_Read(7); 
        write_ENABLE0(1);   /* Disable ADC */
        if(ADCValue0 > 300) /* Configurable threshold  */
            write_PULSE0(1);
        else
            write_PULSE0(0);

        write_ENABLE1(0);
        ADCValue1 = ADC_Read(6);
        write_ENABLE1(1);
        if(ADCValue1 > 250)
            write_PULSE1(1);
        else
            write_PULSE1(0);
        
        sleep_enable();
        sei();
        sleep_cpu();
        sleep_disable();
    }
}

/* Wake up time period 2.48ms */