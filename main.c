/*  
 *  Class: ECE372a
 * 
 *  Group: 209
 *
 *  Lab: 1 Part 2
 * 
 *  File: main.c
 * 
 *  Member: Michael Harmon (Software)
 *          Abdul Rana (Hardware)
 *          James Beulke (System Integration)
 *          Ali Hassan (Quality Control)
 */

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    LCD_Init();
    //LCD_Clear();
    //int x = 0;
    //for(x = 0;x < 6 ;x++)LCD_OtherTest2();
    //LCD_MoveCursor(1,2);
    //for(x = 0;x < 3 ;x++)LCD_OtherTest2();
    while(1)
    {
      //LCD_OtherTest();
      LCD_Test();
      
    }
    return 0;
}
