/*
 * File name            : lcd.h
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Processor            : PIC18
 * Created on           : May 04, 2014, 9:39 AM
 * Description          : External Character LCD functions header file
 */

#ifndef LCD_H
#define	LCD_H

/* ______________________________   LCD Display Commands __________________________________________________*/

#define CLR_LCD                 0x01
#define DISP_ON_CURSOR_OFF      0x0C
#define DISP_OFF_CURSOR_ON      0x0A
#define FIRST_LINE              0x80
#define SECOND_LINE             0x1C
#define TWO_LINE_5X7            0x38

/*_____________________________LCD initialization function________________________________________*/
void lcd_init(void);

/*
 * Include          :       lcd.h
 * Description      :       Configures and Initializes the LCD.
 * Arguments        :       None
 * Returns          :       None
 */

/*_______________________________    LCD Command function   _______________________________________*/

void LCD_cmd(unsigned char c);

/*
 * Include          :       lcd.h
 * Description      :       Writes a command byte to LCD
 * Arguments        :       Command byte
 * Returns          :       None
 */

/*_____________________________LCD Data sending function header_____________________________________*/

void LCD_data(unsigned char c);

/*
 * Include          :       lcd.h
 * Description      :       Writes a data byte to LCD
 * Arguments        :       Data byte
 * Returns          :       None
 */

/*_____________________________LCD Display moving functions headers  ______________________________*/

void Move_Left(unsigned char n);

/*
 * Include          :       lcd.h
 * Description      :       Moving display towards left n positions
 * Arguments        :       Decimal number
 * Returns          :       None
 */


void Move_Right(unsigned char n);

/*
 * Include          :       lcd.h
 * Description      :       Moving display towards Right n positions
 * Arguments        :       Decimal number
 * Returns          :       None
 */
/*_____________________________LCD string write function________________________________________*/

void Write_LCD(unsigned char *str, unsigned char n);

/*
 * Include          :       lcd.h
 * Description      :       Writes a string to LCD
 * Arguments        :       Address of a string
 * Returns          :       None
 */

/*_____________________________LCD initialization function call________________________________________*/

void Write_TIME_LCD(char *str);

/*
 * Include          :       lcd.h
 * Description      :       Writes a string to LCD in formatted display
 * Arguments        :       Address of a string
 * Returns          :       None
 */

#endif	/* LCD_H */