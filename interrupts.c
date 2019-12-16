/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#define _XTAL_FREQ 4000000 

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <pic16f628a.h>        /* For true/false definition */
#include <stdlib.h>

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

#define SWITCH_QUANTITY 168
#define DUTY_STEPS 1
int counter = 0;
unsigned char ii=0;  
unsigned char bit_counter = 0;
unsigned char old_state[5] =    {0,0,0,0,0};
unsigned char new_state[5] =    {1,1,1,1,1};
unsigned char delay[5] =        {   
                                    SWITCH_QUANTITY*DUTY_STEPS,
                                    SWITCH_QUANTITY*DUTY_STEPS,
                                    SWITCH_QUANTITY*DUTY_STEPS,
                                    SWITCH_QUANTITY*DUTY_STEPS,
                                    SWITCH_QUANTITY*DUTY_STEPS
                                }; //switching delay
unsigned char sample[5] = {
            0b11101110,
            0b01010101,
            0b10101011,
            0b01010101,
            0b01010101
};

void __interrupt () my_isr_routine (void)
{
    if (RBIF) {
        //PORTA=1;
        ii = 0;
        for (unsigned  char i=0; i<SWITCH_QUANTITY; i++) {
            //ii = i*DUTY_STEPS;
            if (i > delay[0]) { RA0=0; } else {RA0=1;};
            if (i > delay[1]) { RA1=0; } else {RA1=1;};
            if (i > delay[2]) { RA2=0; } else {RA2=1;};
            if (i > delay[3]) { RA3=0; } else {RA3=1;};
            if (i > delay[4]) { RA4=0; } else {RA4=1;};
            //__delay_us(35);
        };        

        // step open impulse delay for each channel
        for (char j=0; j<5; j++) {
            if (old_state[j]==0 && new_state[j]==0) {
                delay[j] = SWITCH_QUANTITY*DUTY_STEPS;
            } else if (old_state[j]==0 && new_state[j]==1) {
                delay[j]--;
                if (delay[j]==0) {
                    old_state[j]=1;
                };
            } else if (old_state[j]==1 && new_state[j]==0) {
                delay[j]++;
                if (delay[j]==SWITCH_QUANTITY*DUTY_STEPS) {
                    old_state[j]=0;
                };
            } else {
                delay[j]=0;
            };
        };
        
        counter++;
        if (counter==SWITCH_QUANTITY*DUTY_STEPS) {
            counter = 0;
            for (char j=0; j<5; j++) {
                //new_state[j] = (sample[j]>>bit_counter) & 0x00000001;
                new_state[j] = ((sample[j]>>bit_counter)|rand()) & 0b00000001;
            };
            bit_counter++; if (bit_counter>7) bit_counter=0;
        };
        
        PORTB; //read port before RBIF reset 
        RBIF = 0;
    };
    
};
#endif


