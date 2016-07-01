/*
 * File name            : i2c_.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Processor            : PIC18
 * Created on           : May 04, 2014, 4:21 PM
 * Description          : i2c functions source file
 */

#if defined(__18CXX)
#include <i2c.h>
#elif defined(__XC)
#include <plib\i2c.h>
#endif
#if defined(__XC) || defined(__18CXX)
#include "i2c_.h"
#include "delay.h"
#include "uart.h"
#endif


/*___________________________________Buuffer register clear function__________________________________________________________*/

void ReadBUF(void)                                                  /* Read function for clearing Buffer register           */
    {
    unsigned char c;
    c = SSPBUF;                                                     /* Reading out the buffer register to a variable        */
    c = SSPBUF;
    }


/*___________________________________I2C write function_______________________________________________________________________*/

void Write_I2C(unsigned char c)
{
    WriteI2C(c);                                                    /* I2C slave write function call                        */
    ReadBUF();                                                      /* Buffer clear function call                           */
}

/*_____________________________________I2C read function________________________________________________________________________*/

unsigned char Read(void)
    {
     unsigned char c;
     RestartI2C();                                                  /* Function call to Restart I2C bus                     */
     delay_ms(1);                                                   /* 1msec delay                                          */
     Write_I2C( 0xD1 );                                             /* Writing I2C slave address in read mode               */
     c = ReadI2C();                                                 /* Reading data from slave                              */
     ReadBUF();                                                     /* Buffer clear                                         */
     return(c);                                                     /* Reaturn data                                         */
    }




/* _________________________________________________I2C Read function from a specific address_____________________________________*/

unsigned char Read_From_Addr(unsigned char addr)
    {
     unsigned char c;
     StartI2C();
     delay_ms(1);
     Write_I2C(0xD0);
     Write_I2C(addr);
     RestartI2C();
     delay_ms(1);
     Write_I2C( 0xD1 );
     c = ReadI2C();
     ReadBUF();
     StopI2C();
     return(c);
    }

/*_________________________________I2C write function to a specific address____________________________________________________*/

void Write_to_Addr(unsigned char data, unsigned char addr)
     {
     StartI2C();
     ReadBUF();
     Write_I2C(0xD0);
     delay_ms(1);
     Write_I2C(addr);
     delay_ms(1);
     Write_I2C(data);
     delay_ms(1);
     StopI2C();
     delay_ms(200);
     }