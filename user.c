/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif



#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <pic16f628a.h>

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    CMCON = 0b111; //Disable PORTA Comparators  
    
    /* Setup analog functionality and port direction */

        /* Setup analog functionality and port direction */
    TRISA = 0b10000000; // PORTA All Outputs
    TRISB = 0b11110000; //RB7-RB4 as input
   
    /* Initialize peripherals */
    PORTA = 0b01111111;
    PORTB=0;
    
    /* Enable interrupts */
    INTCON = 0b10001000;  //RB7:RB4 interrupt enabled
    PIE1 = 0;
}

