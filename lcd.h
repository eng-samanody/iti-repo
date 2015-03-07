/* ----------------------------------------------------------------------------------------------------
[FILE NAME]:      < lcd.h >
[AUTHOR(S)]:      < Mohamed AbdelRaouf >
[DATE CREATED]:   < Mon 12/29/2014 >
[DESCRIPTION]:    < the lcd file represents the layer that is responsiple for dealing with the lcd 
					it starts with defining the lcd connection details including the port and pin and 
					contains some functions that enable the other layers to deal with the lcd    >
------------------------------------------------------------------------------------------------------- */


#ifndef LCD_H_
#define LCD_H_

/*--------------------------------------------- INCLUDES -----------------------------------------------*/

#include "dio.h"

/*---------------------------------- DEFINITIONS AND CONFIGURATIONS ------------------------------------*/

/*
	using these definitions the user may configure the hardware connections between tHe LCD and the MCU pins
	this drivers allows the the LCD to operate in two different modes, first, the 8 bit mode where 8 bits are
	used to exchange data between the LCD and the MCU, the second is the 4 bit mode. Please be noted that this 
	driver allows flexibility of connecting the LCD to the MCU without any constraints. The user
	has the freedom of connecting the lCD pins to any port and and with any order as long they are
	explicitly defined in this section.
*/


/* set this value as 4 or 8 to changes between the two data modes*/
#define LCD_DATA_BUS_WIDTH 4

/* LCD CONTROL PINS */
#define LCD_RS_PORT 'D'
#define LCD_RS 5
#define LCD_RW_PORT 'C'
#define LCD_RW 1
#define LCD_EN_PORT 'A'
#define LCD_EN 0

/* LCD Data PINS */
#define LCD_D0_PORT 'D'
#define LCD_D0 0
#define LCD_D1_PORT 'D'
#define LCD_D1 1
#define LCD_D2_PORT 'C'
#define LCD_D2 6
#define LCD_D3_PORT 'C'
#define LCD_D3 7
#define LCD_D4_PORT 'C'
#define LCD_D4 4
#define LCD_D5_PORT 'B'
#define LCD_D5 5
#define LCD_D6_PORT 'A'
#define LCD_D6 7
#define LCD_D7_PORT 'A'
#define LCD_D7 6

/* LCD COMMON COMMANDS*/
#define LCD_FOUR_BIT_MODE 0x02
#define TWO_LINE_LCD 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define SET_CURSOR_LOCATION 0x80
#define LCD_CLEAR 0x01			/* Clear display */
#define LCD_RETURN_HOME	0x02	/* Return cursor to home position, returns a shifted display to its original position. Display data RAM is unaffected. */
#define LCD_CURSOR_OFF 0x0C		/* Turn off cursor */
#define CURSOR_ON 0x0E			/* Turn on cursor */
#define LCD_BLINK_CURSOR_ON	0x0F	/* Blink cursor on */
#define LCD_MOVE_CURSOR_LEFT 0x10	/* Move cursor left without changing display data RAM */
#define LCD_MOVE_CURSOR_RIGHT 0x14	/* Move cursor right without changing display data RAM */
#define LCD_TURN_ON	0x0C		/* Turn Lcd display on */
#define LCD_TURN_OFF 0x08		/* Turn Lcd display off */
#define LCD_SHIFT_LEFT	0x18	/* Shift display left without changing display data RAM */
#define LCD_SHIFT_RIGHT	0x1C	/* Shift display right without changing display data RAM */


/*---------------------------------------- FUNCTION DECLARATIONS ----------------------------------------*/


/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_init
[Description]  : This function is responsible for setting direction of the selected port
[Args]    : void
[Returns] : void
--------------------------------------------------------------------------------------------------------------- */
void LCD_init(void);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_sendCommand
[Description]  : This function is responsible for sending Commands to the LCD
[Args]    : uint8 a_command is the desired command that will be sent to the lcd
[Returns] : void
--------------------------------------------------------------------------------------------------------------- */
void LCD_sendCommand(uint8 a_command);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayCharacter
[Description]  : This function is responsible for displaying characters on the LCD
[Args]    : uint8 a_data is the desired character that will be sent to the LCD
[Returns] : void
--------------------------------------------------------------------------------------------------------------- */
void LCD_displayCharacter(uint8 a_data);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayString
[Description]  : This function is responsible for displaying characters on the LCD
[Args]    : const uint8 *  a_string_Ptr is the desired String that will be sent to the LCD
[Returns] : void
--------------------------------------------------------------------------------------------------------------- */
void LCD_displayString(const uint8 *  a_string_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayString
[Description]  : This function is responsible for displaying characters on the LCD
[Args]    : const uint8 *  a_string_Ptr is the desired String that will be sent to the LCD
[Returns] : void
--------------------------------------------------------------------------------------------------------------- */
void LCD_dispalyAtRowColumn(const uint8 *  a_string_Ptr, uint8 a_row, uint8 a_column);


/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_clear
[Description]  : This function is responsible for sending Clear Command to the LCD
[Args]    : void
[Returns] : void
--------------------------------------------------------------------------------------------------------------- */
void LCD_clear (void);


#endif /* LCD_H_ */