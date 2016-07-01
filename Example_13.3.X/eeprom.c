/*
 * File name            : eeprom.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Processor            : PIC18
 * Created on           : October 30, 2013, 12:36 PM
 * Description          : eeprom functions declaration source file
 */

#if defined(__XC)
#include <plib\i2c.h>
#elif defined(__18CXX)
#include <i2c.h>
#endif

#if defined(__XC) || defined(__18CXX)

#include "i2c_.h"
#include "uart.h"
#include "delay.h"
#include "eeprom.h"
#include "lcd.h"
#endif

#define Reload ((20000000/100000)/4-1);                               /* MSSP Baud Rate Reload Register value                    */

extern unsigned char str[33];
unsigned char blank[17] = "                ";
unsigned char c,i;
unsigned char s_1[]= "\n\rDo you want to write/read/exit? press w/r/e", s_2[] = "PRESS w/r/e";
unsigned char newLINE[]  ="\n\r", s_3[]="Exit...";

/*___________________________________     EEPROM WRITE FUNCTION   _____________________________________________*/

void WriteEEPROM(unsigned char Control, unsigned char Address, unsigned char *str)
    {
    while(*str != '\0')
        {
        EEByteWrite(Control, Address, *str);                    /* EEPROM single Byte writing function call             */
        ReadBUF();                                              /* Clearing buffer register                             */
        EEAckPolling(0xA0);
        Address++;
        str++;
        }
    }

/*___________________________________________     EEPROM READ FUNCTION   _____________________________________________*/

void ReadEEPROM(unsigned char Control, unsigned char Address, unsigned char *str)
    {
    unsigned char i = 0,c;
    while(i!=16)
        {
        c = EERandomRead(Control, Address);                     /* EEPROM single Byte Reading from a random address     */
        ReadBUF();                                              /* Clearing buffer register                             */
        *str = c;
        Address++;                                              /* EEPROM Address increment                             */
        i++;
        str++;                                                  /* String variable Address increment                                      */
        }
    }

/*_______________________________________    EEPROM MEMORY ERASING FUNCTION   _______________________________________*/

void EraseEEPROM(void)
{
  unsigned char n=0,i = 0;
  while(n!=128)
    {
      while(i!=16)
      {
      EEByteWrite(0xA0, n, ' ');                                /* Writing blank spaces to the EEPROM (Erasing)   */
      i++;
      }
      i=0;
      n=n+16;                                                  /* Selecting next page of EEPROM                    */
     }
}

/*_____________________________________________STRING clearing Function_______________________________________________*/
void Clear_str(unsigned char *str, unsigned char n)
{
    unsigned char i=0;
    while((i!=n) && (*str))
    {
    *str = ' ';                                                     /* Writing blank spaces to the string variable(Erasing)   */
    i++;
    str++;                                                          /* Address increment                                      */
    }
}

/*________________________________________EEPROM page Reading function__________________________________________*/

void ReadEEPROM_DATA(void)
{
 unsigned char n = 0, i=0;
    while(n!=128)
        {
        ReadEEPROM(0xA0, n, str);
        delay_ms(1);
        Write_str(str);                                             /* Writing a string through USART module            */
        Write_str(newLINE);
		if(i!=8)
        {
        Write_LCD(str, 16);                                         /* Writing a string to External LCD module          */
        }
        Clear_str(str, 32);                                         /* String clearing function call                    */
        n=n+16;                                                     /* Selecting next page of EEPROM                    */
        i++;
        }
}
/*________________________________________EEPROM page Writing function__________________________________________*/

void WriteEEPROM_DATA(void)
{
    unsigned char n = 0;
    EraseEEPROM();                                                  /* Erase EEPROM memory function call                */
    while(n!=128)
        {
        Write_str(newLINE);                                         /* Writing a string through USART module            */
        Read_str_(str);                                             /* Reading a string through USART module            */
        delay_ms(1);
        WriteEEPROM(0xA0, n, str);                                  /* Writing n'th Address location of EEPROM          */
        delay_ms(1);
        Clear_str(str, 32);                                         /* String clearing function call                    */
        n=n+16;                                                     /* Selecting next page of EEPROM                    */
        }
}

/*___________________________________________________________________________________________*/

void EEPROM_ON(void)
    {
    SSPADD = Reload;
    CloseI2C();
    OpenI2C(MASTER, SLEW_ON);                                   /*                  Initialize I2C module                       */
    SSPADD = 0x0B;                                              /*                  ((20000000/400000)/4-1)                     */
    }

void Display(unsigned char i)
{
  if(i==0)
    {
    LCD_cmd(0x80);                                          /* LCD command - Force the cursor to the begining of 1nd Line   */
    Write_LCD(str, 16);
    LCD_cmd(0xc0);                                          /* LCD command - Force the cursor to the begining of 1st Line   */
    Write_LCD(str+16, 16);                                  /* Writing a string to External LCD module                      */
    Delay_s(2);
    LCD_cmd(0x80);
//    Write_LCD(blank, 16);
//    Write_LCD(str+16, 16);
//    LCD_cmd(0xc0);
//    Write_LCD(blank, 16);
  }
    else
    {
    LCD_cmd(0xc0);                                          /* LCD command - Force the cursor to the begining of 2st Line   */
    Write_LCD(str, 16);                                         /* Writing a string to External LCD module                      */
    Delay_s(2);                                             /* Sec delay function call                                      */
    LCD_cmd(0x80);
    Write_LCD(blank , 16);
    Write_LCD(str, 16);
    LCD_cmd(0xc0);
    Write_LCD(blank, 16);
    }
    Delay_s(2);
}
/*_________________________________________Module RUN ___________________________________________*/

void EEPROM_RUN(void)
    {
    unsigned char n = 0,i=0,d;
    do{
        n = 0;
        LCD_cmd(0x82);
        LCD_cmd(CLR_LCD);
        Write_LCD(s_2, 16);
        Write_str(s_1);  					   /* Writing a string through USART module            */
        d = RCREG;
        c = ReadUART();                                            /* Reading a string through USART module            */
        Write_str(newLINE);   	                                   /* Writing a string through USART module            */
        Write(c);                                                  /* Writing a single byte through USART module       */
        Write_str(newLINE);
        if((c == 'w')||(c =='W'))
        WriteEEPROM_DATA();                                        /* EEPROM page write function call                  */
        else if((c == 'r')||(c =='R'))
            {
            while(n!=128)
                {
                ReadEEPROM(0xA0, n, str);                          /* EEPROM Read from an Address function call        */
                delay_ms(1);                                       /* Milli sec. delay function call                   */
                n=n+16;                                            /* Selecting next page of EEPROM                    */
                ReadEEPROM(0xA0, n, str+16);                       /* EEPROM Read from an Address function call        */
                delay_ms(1);                                       /* Milli sec. delay function call                   */
            if(i==0)
             {
                Display(0);                                        /* LCD Line selected display function call          */
                i=0;
             }
             else
                Display(1);                                        /* LCD Line selected display function call          */
                Write_str(str);
                Write_str(newLINE);                                 /* Writing a string through USART module            */
                Clear_str(str, 32);
                }
            }
        else if((c == 'e')||(c =='E'))
            {
            LCD_cmd(0x01);
            LCD_cmd(0x84);                                   /* LCD command - Shift entire display to the Right   */
            Write_LCD(s_3, 7);                              /* Writing a string through USART module             */
            Delay_s(1);                                       /* Sec delay function call                           */
            LCD_cmd(0x01);                                   /* LCD command - clear display                       */
            break;
            }
    }while((c!='e')&&(c!='E'));                             /* Testing whether exit choice has been entered or not*/
}                                                            /* by user                                             */