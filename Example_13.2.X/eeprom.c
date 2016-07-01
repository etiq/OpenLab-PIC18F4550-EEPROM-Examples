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
#endif

#define Reload ((20000000/100000)/4-1);                            /* MSSP Baud Rate Reload Register value             */

#pragma idata idata_1
unsigned char s_1[]="\n\rInvalid";
unsigned char new_ln[3] = "\n\r";
unsigned char s_2[]="Enter the Address (page 1 - 8)";
unsigned char s_3[]="Enter the Offset (1 - ";
unsigned char s_4[]="Enter the Address (page No.1 - 8)";
unsigned char s_5[]="Enter the Offset (1 - ", s_6[]="\n\rPage ";
unsigned char s_7[]=" 16bytes\r\t\t";
unsigned char s_8[]="\r\t\t\tpage ";
unsigned char s_9[]=" 16bytes\n\r";
#pragma idata idata_6
unsigned char s_10[]="\n\rErase EEPROM\r\t\t - (press '1') All data will be lost..!\n\rErase a page\r\t\t - (press '2')";
#pragma idata idata_7
unsigned char s_11[]="\n\rSelect write/read/erase/exit? press w/r/d/e";

#pragma idata

#pragma udata udata1
unsigned char c,i;
unsigned char str[33];
#pragma udata
/*


unsigned char s_1[]="\n\rInvalid", s_2[]="Enter the Address (page 1 - 8)", s_3[]="Enter the Offset (1 - ";
unsigned char s_4[]="Enter the Address (page No.1 - 8)", s_5[]="Enter the Offset (1 - ", s_6[]="\n\rPage ",s_7[]=" 16bytes\r\t\t";
unsigned char s_8[]="\r\t\t\tpage ",s_9[]=" 16bytes\n\r",s_10[]="\n\rErase EEPROM   (press '1')\n\r\tLocation (press '2')";
unsigned char s_11[]="\n\rSelect write/read/erase/exit? press w/r/d/e";


*/

void NewLINE(void)
{
Write_str(new_ln);
}

unsigned char Select(unsigned char sign, unsigned char range_1, unsigned char range_2)
{
    NewLINE();
    if(sign=='n')
      {
        do
        {
        c = ReadUART();
        Write(c);
        c = c - '0';
        if(!((c>=range_1)&&(c<=range_2)))
          Write_str(s_1);
        }while(!((c>=range_1)&&(c<=range_2)));
      }
      else
      {
      c = ReadUART();                                            /* Reading a Byte through USART module              */                                         /* Writing a string through USART module            */
      Write(c);                                                  /* Writing a single byte through USART module       */
      }
      NewLINE();
      return(c);
}

/*___________________________________     EEPROM WRITE FUNCTION   _____________________________________________*/

void WriteEEPROM(unsigned char Control, unsigned char Address, unsigned char *str)
    {
    unsigned char k=0;
    while((*str != '\0') && (k!=16))
        {
        EEByteWrite(Control, Address, *str);                    /* EEPROM single Byte writing function call             */
        ReadBUF();                                              /* Clearing buffer register                             */
        EEAckPolling(0xA0);
        Address++;
        str++;
        k++;
        }
    }

/*___________________________________________     EEPROM READ FUNCTION   _____________________________________________*/

void ReadEEPROM(unsigned char Control, unsigned char Address, unsigned char *str)
    {
    unsigned char i = 0, c;
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

void EraseEEPROM(unsigned char p)
{
unsigned char n=0, m=0, i=0, j=0;
if(p=='z')
  {
    while(n!=128)
    {
     while(i!=16)
      {
      EEByteWrite(0xA0, n, ' ');                               /* Writing blank spaces to the EEPROM (Erasing)     */
      ReadBUF();
      EEAckPolling(0xA0);
      n++;
      i++;
      }
      i=0;
    }
  }
else if(p=='x')
  {
  Write_str(s_2);
  n=Select('n',1,8);                                             /* Receive a Byte ('n' represents decimal number)  */
  Write_str(s_3);                  							     /* Enter the Offset(displacement)through which writing progress   */
  Write((8-(n-1))+'0');
  Write(')');
  m=Select('n',1,8-(n-1));
  n--;
  n=n*16;
  j=0;
  while(j!=m)
    {
    while(i!=16)
      {
      EEByteWrite(0xA0, n, ' ');                                 /* Writing blank spaces to the EEPROM (Erasing)     */
      ReadBUF();
      EEAckPolling(0xA0);
      i++;
      n++;
      }
    i = 0;
    j++;
//    n = n+16;                                                   /* Selecting next page of EEPROM                    */
    }
  }
}

/*_________________________________________   STRING clearing Function   ____________________________________________*/

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
        Clear_str(str, 32);                                         /* String clearing function call                    */
        n=n+16;                                                     /* Selecting next page of EEPROM                    */
        i++;
        }
}

/*________________________________________EEPROM page Writing function__________________________________________*/

void WriteEEPROM_DATA(void)
{
  unsigned char n=0, m=0, j=0, b=0;
  Write_str(s_2);         /* Enter the address of the page from which writing to be started */
  n=Select('n',1,8);                                          /* Receive a Byte ('n' represents decimal number)                 */
  Write_str(s_3);                  /* Enter the Offset(displacement)through which writing progress   */
  Write((8-(n-1))+'0');
  Write(')');
  m=Select('n',1,8-(n-1));
  b=n;
  n--;
  n=n*16;
  j=0;
 //EraseEEPROM('z');                                            /* Erase EEPROM memory function call                */
  while(j!=m)
    {                                                           /* Reading a string through USART module            */
        Write_str(s_6);                                 /* Writing a string through USART module            */
        Write((b+'0'));
        Write_str(s_7);
        Read_str_(str);
        delay_ms(1);
        WriteEEPROM(0xA0, n, str);                                  /* Writing n'th Address location of EEPROM          */
        delay_ms(1);
        Clear_str(str, 32);                                         /* String clearing function call                    */
        n=n+16;                                                     /* Selecting next page of EEPROM                    */
        j++;
        b++;
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

/*_________________________________________Module RUN ___________________________________________*/

void EEPROM_RUN(void)
    {
    unsigned char n = 0,i=0,d,j;
    do{
        Write_str(s_11);  /*     Writing a string through USART module            */
        d = RCREG;
        c = Select(0,0,0);
        if((c == 'w')||(c =='W'))
        WriteEEPROM_DATA();                                        /* EEPROM page write function call                  */
        else if((c == 'r')||(c =='R'))
            {
            j=0;
            while(j!=8)
                {
                ReadEEPROM(0xA0, n, str);                          /* EEPROM Read from an Address function call        */
                delay_ms(1);                                       /* Milli sec. delay function call                   */
                j++;                                            /* Selecting next page of EEPROM                    */
                n=n+16;
                Write_str(str);
                Write_str(s_8);                                      /* Writing a string through USART module            */
                Write((j+'0'));
                Write_str(s_9);
                Clear_str(str, 32);
                }
            }
        else if((c == 'd')||(c =='D'))
        {
        Write_str(s_10);
        c = Select('n',1,2);
        switch(c)
            {
            case 1 : EraseEEPROM('z');                            /* Erase entire memory                             */
                        break;
            case 2 : EraseEEPROM('x');                            /* Erase a specific location                       */
                        break;
        }
        }
      else if((c == 'e')||(c =='E'))
        break;
    }while((c!='e')&&(c!='E')&&(c!='r')&&(c!='R')&&(c!='w')&&(c!='W') &&(c!='d')&&(c!='D')); /* Testing whether exit choice has been entered or not*/
  }                                                                 /* by user                                             */