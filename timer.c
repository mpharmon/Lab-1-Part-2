/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void delayUs(unsigned int delay){
  TMR1 = 0;// Reset Timer Register
  PR1 = (delay * 10) - 1;// Period Register; Exponents of uS and MHz cancel
  T1CONbits.TCKPS = 0;// Prescaler to 1
  IFS0bits.T1IF = 0;// Interrupt Flag Down
  IPC1bits.T1IP = 7;// Interrupt Priority Default
  T1CONbits.ON = 1;// Start Timer
  while(IFS0bits.T1IF == 0){};// Wait Loop
  IFS0bits.T1IF = 0;
}