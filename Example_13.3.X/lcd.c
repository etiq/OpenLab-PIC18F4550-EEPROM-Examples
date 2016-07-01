/*
 * File name            : lcd.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Processor            : PIC18
 * Created on           : May 05, 2014, 11:23 AM
 * Description          : lcd pin configuration functions source file
 */

#if defined(__XC)
        #include <xc.h>         /* XC General Include File */
#elif defined(__18CXX)
        #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(__18CXX)
#include "delay.h"
#endif

#define RS LATAbits.LATA2                               /* Register select pin definition                         */
#define RW LATAbits.LATA1                               /* Read/Write pin definition                              */
#define EN LATAbits.LATA0                               /* Enable  pin definition                                 */
#define DATA_PORT_ PORTD                                 /* DATA PORT definition                                   */
#define CTRL_PORT_DIR TRISA
#define DATA_PORT_DIR TRISD

void LCD_cmd(unsigned char c)
        {
        RS = 0;                                         /* Command mode selected                                   */
        DATA_PORT_ = c;
        RW = 0;                                         /* Write mode selected                                      */
        EN = 1;                                         /* Logic HIGH on Enable pin                                 */
        DelayFor18TCY();                                /* Delay for 18 cycles                                      */
        EN = 0;                                         /* Logic LOW on Enable pin                                  */
        DelayFor18TCY();                                /* Delay for 18 cycles                                      */
        }
void LCD_data(unsigned char c)
        {
        RS = 1;                                         /* Data mode selected                                       */
        DATA_PORT_ = c;
        RW = 0;                                         /* Write mode selected                                      */
        EN = 1;                                         /* Logic HIGH on Enable pin                                 */
        DelayFor18TCY();                                /* Delay for 18 cycles                                      */
        EN = 0;                                         /* Logic LOW on Enable pin                                  */
        DelayFor18TCY();                                /* Delay for 18 cycles                                      */
        }
void lcd_init(void)
       {
        CTRL_PORT_DIR = 0x00;                           /* Direction of control port as Output                      */
        DATA_PORT_DIR = 0x00;                           /* Direction of data port as Output                         */
        LCD_cmd(0x38);                                  /* LCD command - 5x7 matrix                                 */
        LCD_cmd(0x80);                                  /* LCD command - Force cursor to the bigining of first line */
        LCD_cmd(0x0C);                                  /* LCD command - Display ON, cursor OFF                     */
        LCD_cmd(0x01);                                  /* LCD command - Clear display                              */
        }
void Write_LCD(unsigned char *str, unsigned char n)
{
while(*str && n)
    {
        LCD_data(*str);                                 /* Passing address of a string to LCD data display function */
        str++;                                          /* Increments the address of a string variable              */
        n--;
}
}
void Move_Left(unsigned char n)
{
unsigned char i=0;
   while(i!=n)
    {
    LCD_cmd(0x18);                                      /* LCD command for moving entire display to the left        */
    delay_ms(200);                                      /* Milli seconds delay function call                        */
    i++;
    }
}
void Move_Right(unsigned char n)
    {
    unsigned char i;
    for(i=0;i<n;i++)
        {
        LCD_cmd(0x1c);                                  /* LCD command - Shift entire display to the Right                */
        delay_ms(200);
        }
    }
void Write_TIME_LCD(char *str)
{ unsigned char i=0;
LCD_cmd(0x80);                                          /* LCD command - Force cursor to the bigining of first line */
    while(i!=16)
    {
    LCD_data(*str);                                     /* Passing address of a string to LCD data display function */
    str++;                                              /* String variable address increment                        */
    i++;
    }
str++;                                                  /* String variable address increment                        */
i=17;
LCD_cmd(0xC0);                                          /* Force cursor to the bigining of the 2nd line             */
while(i!=32)
        {
        LCD_data(*str);                                 /* Passing address of a string to LCD data display function */
        str++;                                          /* String variable address increment                        */
        i++;                                            
        }
    }