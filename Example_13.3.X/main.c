/*
 * File name            : main.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Processor            : PIC18
 * Created on           : May 05, 2014, 10:34 AM
 * Description          : Example_13.3 EEPROM_3
 *                      : Example code initializes external character LCD, EEPROM and USART module.
 */

/*
 * Read/ Write of 16*8 pages of EEPROM
 *
 * Connections
 * -----------
 * 1. Connect the PC serial port to DB9 port J21 of PIC board.
 * 2. Close the 2bit jumpers J22 and J23.
 * 3. LCD PIN configurations
 *    ----------------------
 *  8 bit data
 *  Control PORT    -       PORTA
 *
 *  RA0     -       EN
 *  RA1     -       R/W
 *  RA2     -       RS
 *
 *  Data PORT       -       PORTD
 *
 * Operation
 * ---------
 * 1. Open the hyper terminal and reset the controller.
 * 2. Listen to the terminal window and select an option from read/ write.
 * 3. If selected option is 'r' then microcontroller starts reading EEPROM. User can
 *    enter to EEPROM writing mode by selecting option 'w'.
 * 4. LCD displays the data read from each page.
 *
*/

#if defined(__XC)
    #include <plib\usart.h>
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <usart.h>
#endif

#if defined(__XC) || defined(HI_TECH_C)
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#endif

#if defined(__XC) || defined(__18CXX)
#include "config.h"
#include "delay.h"
#include "uart.h"
#include "lcd.h"
#include "i2c_.h"
#include "eeprom.h"
#endif

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 20000000
#endif
#define Fosc 20000000                                                 /* External crystal frequency                              */
#define baud 9600                                                     /* UART baud rate                                          */
#define config_2 ((Fosc/baud/64)-1)

/*__________________________________________________________________________________________________________*/

unsigned char str[33];
unsigned char config_1 = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW;
void main (void)
    {
     CMCON |= 7;                                                    /*      Analog comparators disabled                     */
     ADCON1=0x0F;                                                   /*      Setting all Analog inputs to digital IO         */
     TRISD = 0x00;                                                  /*      Direction of PORTD as output                    */
     ConfigUSART(config_1, config_2);                               /*      USART module configuration                      */
     lcd_init();                                                    /*      LCD initialization                              */
     EEPROM_ON();                                                   /*      I2C iniialization                               */
       while(1)
        {       
	EEPROM_RUN();                                               /*      Write/read the EEPROM                           */
        }
     }