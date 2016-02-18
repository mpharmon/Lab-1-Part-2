#include <xc.h>
#include "lcd.h"
#include "timer.h"
#include <string.h>

#define TRISx_INPUT   1
#define TRISx_OUTPUT  0

#define LCD_RS  LATCbits.LATC4
#define LCD_E   LATCbits.LATC2
#define LCD_D4  LATEbits.LATE1
#define LCD_D5  LATEbits.LATE3
#define LCD_D6  LATEbits.LATE5
#define LCD_D7  LATEbits.LATE7

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
  LCD_Write(c,1,100);
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

void LCD_Clear(){
  LCD_Write(0x1,0,2000);
  delayUs(1500);
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void LCD_MoveCursor(unsigned char x, unsigned char y){
  LCD_Write(0x80|((y >> 1) << 6)|(x - 1),0,100);
}

void LCD_Init(void){
  //Init LED
  TRISDbits.TRISD0 = TRISx_OUTPUT;
  LATDbits.LATD0 = 0;
  // Set Tristate Registers
  ANSELEbits.ANSE7 = 0;
  TRISCbits.TRISC4 = TRISx_OUTPUT;// LCD_RS
  TRISCbits.TRISC2 = TRISx_OUTPUT;// LCD_E
  TRISEbits.TRISE7 = TRISx_OUTPUT;// LCD_D7
  TRISEbits.TRISE5 = TRISx_OUTPUT;// LCD_D6
  TRISEbits.TRISE3 = TRISx_OUTPUT;// LCD_D5
  TRISEbits.TRISE1 = TRISx_OUTPUT;// LCD_D4
  
  //15mS Wait Required after Power On (delayUs takes maximum 5mS or 5000uS)
  delayUs(5000);delayUs(5000);delayUs(5000);
  
  //First Initialization Sequence
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 1;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(5000);
  
  //Second Initialization Sequence
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 1;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(150);
  
  //Third Initialization Sequence
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 1;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(10);
  
  //Set 4-bit Interface
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 1;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(10);
  
  //Function Set
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 1;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(10);
  LCD_RS = 0;
  LCD_D7 = 1;LCD_D6 = 1;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(1);
  
  //Turn Display Off
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(10);
  LCD_RS = 0;
  LCD_D7 = 1;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  
  //Clear Display
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(10);
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  
  //Entry Mode Set
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(10);
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 1;LCD_D5 = 1;LCD_D4 = 1;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  
  //Turn Display On, Cursor Off Blink Off
  LCD_RS = 0;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  delayUs(10);
  LCD_RS = 0;
  LCD_D7 = 1;LCD_D6 = 1;LCD_D5 = 0;LCD_D4 = 0;
  LCD_E = 1;
  delayUs(10);
  LCD_E = 0;
  LATDbits.LATD0 = 1;
}

void LCD_OtherTest(){
  LCD_RS = 1;
  /*  Write First 4-bits of Word  */
  LCD_D7 = 0;LCD_D6 = 1;LCD_D5 = 0;LCD_D4 = 0;
  //Enable
  LCD_E = 1;
  //Delay
  delayUs(10);
  //Disable
  LCD_E = 0;
  delayUs(10);
  /*  Write Last 4-bits of Word  */
  LCD_RS = 1;
  LCD_D7 = 0;LCD_D6 = 0;LCD_D5 = 0;LCD_D4 = 1;
  //Enable
  LCD_E = 1;
  //Delay
  delayUs(10);
  //Disable
  LCD_E = 0;
  
  int x = 0;
  for(x = 0; x < 100; x++) delayUs(100);
}
void LCD_Test(){
    int i = 0;
    LCD_PrintChar('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    LCD_Clear();
    LCD_PrintString("Hello!");
    LCD_MoveCursor(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    LCD_PrintString("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}