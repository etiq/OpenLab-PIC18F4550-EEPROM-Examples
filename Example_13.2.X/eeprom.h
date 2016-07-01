/*
 * File name            : eeprom.h
*  Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Processor            : PIC18
 * Created on           : March 4, 2014, 6:04 PM
 * Description          : EEPROM Read/ Write functions header file
 */


#ifndef EEPROM_H
#define	EEPROM_H


/* ___________________________EEPROM Write function header_____________________________ */

void WriteEEPROM(unsigned char Control, unsigned char Address, unsigned char *str);

/*
 * Include          :       eeprom.h
 * Description      :       Writing a data byte to an address location
 * Arguments        :       Control byte, Address, Address of a string
 * Returns          :       None
 */

/* ___________________________EEPROM Read function header______________________________ */

void ReadEEPROM(unsigned char Control, unsigned char Address, unsigned char *str) ;

/*
 * Include          :       eeprom.h
 * Description      :       Reading a data byte from an address location
 * Arguments        :       Control byte, Address, Address of a string variable
 * Returns          :       None
 */
/* ___________________________String clear function header_____________________________ */

void Clear_str(unsigned char *str, unsigned char n);

/*
 * Include          :       eeprom.h
 * Description      :       Clears a string variable
 * Arguments        :       Address of a string
 * Returns          :       None
 */

/* ______________________EEPROM Page Read function header______________________________ */

void ReadEEPROM_DATA(void);

/*
 * Include          :       eeprom.h
 * Description      :       Reads the pages of EEPROM
 * Arguments        :       None
 * Returns          :       None
 */

/* ______________________EEPROM Page Write function header______________________________ */

void WriteEEPROM_DATA(void);

/*
 * Include          :       eeprom.h
 * Description      :       Writes the pages of EEPROM
 * Arguments        :       None
 * Returns          :       None
 */

/* ___________________________EEPROM Erase function header _____________________________ */

void EraseEEPROM(unsigned char p);

/*
 * Include          :       eeprom.h
 * Description      :       Erase all the pages of EEPROM
 * Arguments        :       None
 * Returns          :       None
 */

/* ___________________________EEPROM configuration function header______________________ */

void EEPROM_ON(void);

/*
 * Include          :       eeprom.h
 * Description      :       Configuring the I2C module
 * Arguments        :       None
 * Returns          :       None
 */

/* ________________________LCD Line selection Function____________________________________ */

void Display(unsigned char i);

/*
 * Include          :       eeprom.h
 * Description      :       LCD Line selection and Display function
 * Arguments        :       None
 * Returns          :       None
 */

/* ___________________________EEPROM Read/Write selection Function call____________________ */

void EEPROM_RUN(void);

/*
 * Include          :       eeprom.h
 * Description      :       Selects whether to perform Writing/ Reading EEPROM
 * Arguments        :       None
 * Returns          :       None
 */

#endif	/* EEPROM_H */

