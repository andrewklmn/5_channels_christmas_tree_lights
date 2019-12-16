/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#define _XTAL_FREQ 4000000 
#include <stdlib.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <pic16f628a.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
#define DEMO_PERIOD 10
int timer_for_demo = 0;

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    srand(200);

    while(1)
    {
        if (RA7==1) {
            GIE = 0;
            PORTA = 0b00000000;
        } else {
            PORTA = 0b11111111;
            if (timer_for_demo==0) {
                GIE = 0;
                for (char k=0; k<4; k++) {
                    PORTA = 0b00011110;
                    __delay_ms(200);
                    PORTA = 0b00000000;
                    __delay_ms(200);
                    PORTA = 0b00010101;
                    __delay_ms(200);
                    PORTA = 0b00001010;
                    __delay_ms(200);
                    PORTA = 0b00011111;
                    __delay_ms(200);
                    PORTA = 0b00001111;
                    __delay_ms(200);
                    PORTA = 0b00010111;
                    __delay_ms(200);
                    PORTA = 0b00011011;
                    __delay_ms(200);
                    PORTA = 0b00011101;
                    __delay_ms(200);
                    PORTA = 0b00011110;
                    __delay_ms(200);
                    PORTA = 0b00010000;
                    __delay_ms(200);
                    PORTA = 0b00001000;
                    __delay_ms(200);
                    PORTA = 0b00000100;
                    __delay_ms(200);
                    PORTA = 0b00000010;
                    __delay_ms(200);
                    PORTA = 0b00000001;
                    __delay_ms(200);
                    PORTA = 0b00000000;
                    __delay_ms(200);
                    PORTA = 0b00000001;
                    __delay_ms(200);
                    PORTA = 0b00000011;
                    __delay_ms(200);
                    PORTA = 0b00000110;
                    __delay_ms(200);
                    PORTA = 0b00001100;
                    __delay_ms(200);
                    PORTA = 0b00011000;
                    __delay_ms(200);
                    PORTA = 0b00000111;
                    __delay_ms(200);
                    PORTA = 0b00010011;
                    __delay_ms(200);
                    PORTA = 0b00011001;
                    __delay_ms(200);
                    PORTA = 0b00011100;
                    __delay_ms(200);
                    PORTA = 0b00011110;
                    __delay_ms(200);
                };
                timer_for_demo=DEMO_PERIOD;
            };
            GIE = 1;
            __delay_ms(1000);
            timer_for_demo--;
        };
    };

};