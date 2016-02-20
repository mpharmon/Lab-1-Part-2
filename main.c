// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"


// ******************************************************************************************* //

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
