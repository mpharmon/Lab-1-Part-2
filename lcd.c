#include <xc.h>
#include "lcd.h"
#include "timer.h"
#include <string.h>

#define TRISx_INPUT   1
#define TRISx_OUTPUT  0

#define LCD_RS  LATCbits.LATC4
#define LCD_E   LATCbits.LATC2
#define LCD_D4  LATEbits.LATE7
#define LCD_D5  LATEbits.LATE5
#define LCD_D6  LATEbits.LATE3
#define LCD_D7  LATEbits.LATE1

void LCD_Write(unsigned char word, unsigned int commandType, unsigned int delayAfter){
  /*  Set LCD_RS  */
  if(commandType == 0)LCD_RS = 0;
  else LCD_RS = 1;
  
  /*  Write First 4-bits of Word  */
  LCD_D7 = word&0x80;LCD_D6 = word&0x40;LCD_D5 = word&0x20;LCD_D4 = word&0x10;
  //Enable
  LCD_E = 1;
  //Delay
  delayUs(delayAfter);
  //Disable
  LCD_E = 0;
  
  /*  Write Last 4-bits of Word  */
  LCD_D7 = word&0x08;LCD_D6 = word&0x04;LCD_D5 = word&0x02;LCD_D4 = word&0x01;
  //Enable
  LCD_E = 1;
  //Delay
  delayUs(delayAfter);
  //Disable
  LCD_E = 0;  
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void LCD_PrintChar(char c){
  LCD_Write(c,1,50);
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void LCD_PrintString(const char* s) {
  int x = 0;
  for(x = 0;x<strlen(s);x++)LCD_PrintChar(s[x]);
}

void clearLCD(){
  
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void LCD_MoveCursor(unsigned char x, unsigned char y){
  
}

void initLCD(void){//Done
  // Set Tristate Registers
  TRISCbits.TRISC4 = TRISx_OUTPUT;// LCD_RS
  TRISCbits.TRISC2 = TRISx_OUTPUT;// LCD_E
  TRISEbits.TRISE7 = TRISx_OUTPUT;// LCD_D7
  TRISEbits.TRISE5 = TRISx_OUTPUT;// LCD_D6
  TRISEbits.TRISE3 = TRISx_OUTPUT;// LCD_D5
  TRISEbits.TRISE1 = TRISx_OUTPUT;// LCD_D4
  
  //15mS Wait Required after Power On (delayUs takes maximum 5mS or 5000uS)
  delayUs(5000);delayUs(5000);delayUs(5000);
  
  //First Initialization Sequence
  LCD_RS = 0;LCD_D7 = 1;LCD_D6 = 1;LCD_D5 = 1;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(5000);
  LCD_E = 0;
  
  //Second Initialization Sequence
  LCD_RS = 0;LCD_D7 = 1;LCD_D6 = 1;LCD_D5 = 1;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(200);
  LCD_E = 0;
  
  //Third Initialization Sequence
  LCD_RS = 0;LCD_D7 = 1;LCD_D6 = 1;LCD_D5 = 1;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  
  //Set 4-bit Interface
  LCD_RS = 0;LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 1;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  
  //Function Set
  LCD_RS = 0;LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 1;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  //NOTE: LCD_D6 May Need Changed to 1 
  LCD_RS = 0;LCD_D7 = 1;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  
  //Turn Display Off
  LCD_RS = 0;LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  LCD_RS = 0;LCD_D7 = 1;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  //Clear Display
  LCD_RS = 0;LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  LCD_RS = 0;LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  
  //Entry Mode Set
  LCD_RS = 0;LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  LCD_RS = 0;LCD_D7 = 0;LCD_D6 = 1;LCD_D5 = 1;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  
  //Turn Display On, Cursor Off Blink Off
  LCD_RS = 0;LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
  LCD_RS = 0;LCD_D7 = 1;LCD_D6 = 1;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(100);
  LCD_E = 0;
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    LCD_PrintChar('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    LCD_PrintString("Hello!");
    LCD_MoveCursor(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    LCD_PrintString("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}