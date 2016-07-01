/*
 * File name            : main.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_13.1 EEPROM_1
 * Created on           : May 03, 2014, 11:30 AM
 *                      : EEPROM Read/ write example (I2C protocol)
 *  
 * Example code configures I2C, initializes external character LCD and USART module.
 * Receiving 8 string data(16bytes) through UART, saving to EEPROM and displays each string on external character LCD
 */

/*
 * Read/ Write of 16*8 pages of EEPROM
 *
 * Connections
 * -----------
 * 1. Connect the PC serial port to DB9 port J21 of PIC board.
 * 2. Close the 2bit jumpers J22 and J23.
 *

 USART module PORT-PIN Configuration (TTL)
 -----------------------------------
    Tx     -       RC6
    Rx     -       RC7

 * Operation
 * ---------
 * 1. Open the hyper terminal and reset the controller.
 * 2. Listen to the terminal window and select an option from read/ write.
 * 3. If selected option is 'r' then microcontroller starts reading EEPROM. User can
 *    enter to EEPROM writing mode by selecting option 'w'.
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
#include "i2c_.h"
#include "eeprom.h"
#endif

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 20000000
#endif
#define Fosc 20000000                                                 /* External crystal frequency                              */
#define baud 9600                                                     /* UART baud rate                                          */
#define config_2 ((Fosc/baud/64)-1)

unsigned char config_1 = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW;
void main (void)
     {
     CMCON |= 7;                                                    /*      Analog comparators disabled                     */
     ADCON1=0x0F;                                                   /*      Setting all Analog inputs to digital IO         */
     ConfigUSART(config_1, config_2);                               /*      USART module configuration                      */
     EEPROM_ON();                                                   /*      I2C iniialization                               */
       while(1)
        {       
        EEPROM_RUN();                                               /*      Write/read the EEPROM                           */
        }
     }