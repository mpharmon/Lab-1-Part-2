/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define TRISx_INPUT   1
#define TRISx_OUTPUT  0

#define LCD_RS  LATCbits.LATC4
#define LCD_E   LATCbits.LATC2
#define LCD_D4  LATEbits.LATE7
#define LCD_D5  LATEbits.LATE5
#define LCD_D6  LATEbits.LATE3
#define LCD_D7  LATEbits.LATE1

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATE. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    // set the commandType (RS value)
    LATEbits.LATE0 = word&0x01;
    LATEbits.LATE2 = word&0x02;
    LATEbits.LATE4 = word&0x04;
    LATEbits.LATE6 = word&0x08;
    
    //enable
    //delay
    //disable
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c){
    //TODO:
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
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
}

/*
 * Clear the display.
 */
void clearLCD(){
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}