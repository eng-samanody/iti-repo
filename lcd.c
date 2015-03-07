/* ----------------------------------------------------------------------------------------------------
[FILE NAME]:      < lcd.c >
[AUTHOR(S)]:      < Mohamed AbdelRaouf >
[DATE CREATED]:   < Mon 12/29/2014 >
[DESCRIPTION]:    < the lcd file represents the layer that is responsiple for dealing with the lcd 
					it starts with defining the lcd connection details including the port and pin and contains
					some functions that enable the other layers to deal with the lcd    >
------------------------------------------------------------------------------------------------------- */

/*--------------------------------------------- INCLUDES -----------------------------------------------*/

#include "lcd.h"

/*------------------------------------------ GLOBAL VARIABLES -------------------------------------------*/

/* LCD Data Port Configurations Structure */
static DioConfig g_s_lcdDataConfig[LCD_DATA_BUS_WIDTH];

/* LCD Control Port Configurations Structure */
static DioConfig g_s_lcdControlConfig[3];

/*------------------------------------- FUNCTION DEFINITIONS ---------------------------------------------*/

/* --------------------------------------------------------------------------------------------------------
[Function Name] : 	LCD_configurations
[Description]   : 	CalLed by the LCD_Init function (only) used to fill the LCD configurations structure
[Args]    :	void
[Returns] : void
----------------------------------------------------------------------------------------------------------- */
static void LCD_configurations()
{
	#if (LCD_DATA_BUS_WIDTH == 8)
		
		/* LCD DATA Port initialization */
		g_s_lcdDataConfig[0].port = LCD_D0_PORT;
		g_s_lcdDataConfig[0].pinNum = LCD_D0;
	
		g_s_lcdDataConfig[1].port = LCD_D1_PORT;
		g_s_lcdDataConfig[1].pinNum = LCD_D1;
	
		g_s_lcdDataConfig[2].port = LCD_D2_PORT;
		g_s_lcdDataConfig[2].pinNum = LCD_D2;
		
		g_s_lcdDataConfig[3].port = LCD_D3_PORT;
		g_s_lcdDataConfig[3].pinNum = LCD_D3;
		
		g_s_lcdDataConfig[4].port = LCD_D4_PORT;
		g_s_lcdDataConfig[4].pinNum = LCD_D4;
		
		g_s_lcdDataConfig[5].port = LCD_D5_PORT;
		g_s_lcdDataConfig[5].pinNum = LCD_D5;
		
		g_s_lcdDataConfig[6].port = LCD_D6_PORT;
		g_s_lcdDataConfig[6].pinNum = LCD_D6;
		
		g_s_lcdDataConfig[7].port = LCD_D7_PORT;
		g_s_lcdDataConfig[7].pinNum = LCD_D7;
		
		for (uint8 i = 0; i<8; i++)
		{
			g_s_lcdDataConfig[i].direction = OUTPUT;
			g_s_lcdDataConfig[i].pinValue = LOGIC_LOW;
			/* set LCD DATA Port directions */
			DIO_setDirection( & g_s_lcdDataConfig[i] );
		}	
		
	#elif (LCD_DATA_BUS_WIDTH == 4)
		
		g_s_lcdDataConfig[0].port = LCD_D4_PORT;
		g_s_lcdDataConfig[0].pinNum = LCD_D4;
	
		g_s_lcdDataConfig[1].port = LCD_D5_PORT;
		g_s_lcdDataConfig[1].pinNum = LCD_D5;
	
		g_s_lcdDataConfig[2].port = LCD_D6_PORT;
		g_s_lcdDataConfig[2].pinNum = LCD_D6;
	
		g_s_lcdDataConfig[3].port = LCD_D7_PORT;
		g_s_lcdDataConfig[3].pinNum = LCD_D7;
		
		for (uint8 i = 0 ; i < 4 ; i++)
		{
			g_s_lcdDataConfig[i].direction = OUTPUT;
			g_s_lcdDataConfig[i].pinValue = LOGIC_LOW;
			/* set LCD DATA Port directions */
			DIO_setDirection( & g_s_lcdDataConfig[i] );
		}
		
	#endif
	
	/* set LCD CONTROL Port initialization */
	g_s_lcdControlConfig[0].port = LCD_RS_PORT;
	g_s_lcdControlConfig[0].pinNum = LCD_RS;
	
	g_s_lcdControlConfig[1].port = LCD_RW_PORT;
	g_s_lcdControlConfig[1].pinNum = LCD_RW;
	
	g_s_lcdControlConfig[2].port = LCD_EN_PORT;
	g_s_lcdControlConfig[2].pinNum = LCD_EN;
	 
	for (uint8 i = 0 ; i < 3 ; i++)
	{
		/* LCD CONTROL Number */
		g_s_lcdControlConfig[i].direction = OUTPUT;
		g_s_lcdControlConfig[i].pinValue= LOGIC_LOW;
		/* set LCD CONTROL Port directions */
		DIO_setDirection( & g_s_lcdControlConfig[i] );
	}
}

/* --------------------------------------------------------------------------------------------------------
[Function Name] : 	writeCommand
[Description]   : 	CalLed by the LCD_sendCommand function (only) used to write the received command to the data port
[Args]    :	uint8 a_command : the desired command to be written to the Data Port
[Returns] : void
----------------------------------------------------------------------------------------------------------- */
static void writeCommand(uint8 a_command)
{
	/* Instruction Mode RS=0 */
	g_s_lcdControlConfig[0].pinValue = LOGIC_LOW;
	DIO_writePin( & g_s_lcdControlConfig[0] );
	
	/* write data to LCD so RW=0 */
	g_s_lcdControlConfig[1].pinValue = LOGIC_LOW;
	DIO_writePin( & g_s_lcdControlConfig[1] );
	
	/* delay for processing Tas = 50ns */
	_delay_ms(1);
	
	/* Enable LCD EN=1 */
	g_s_lcdControlConfig[2].pinValue = LOGIC_HIGH;
	DIO_writePin( & g_s_lcdControlConfig[2] );
	
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);
	
	//***********************************************************************************************************************
		
		for (int i = 0; i<LCD_DATA_BUS_WIDTH; i++ )
		{
			g_s_lcdDataConfig[i].pinValue = ((a_command>>i) & 1);
			DIO_writePin( & g_s_lcdDataConfig[i]);		
		}
		
	//***********************************************************************************************************************

	/* delay for processing Tdsw = 100ns */
	_delay_ms(10);
	
	/* disable LCD EN=0 */
	g_s_lcdControlConfig[2].pinValue = LOGIC_LOW;
	DIO_writePin( & g_s_lcdControlConfig[2] );
	
	/* delay for processing Th = 13ns */
	_delay_ms(1);
}

/* --------------------------------------------------------------------------------------------------------
[Function Name] : 	writeData
[Description]   : 	CalLed by the LCD_displayCharacter function (only) used to write the received data to the data port
[Args]    :	uint8 a_data : the desired data to be written to the Data Port
[Returns] : void
----------------------------------------------------------------------------------------------------------- */
static void writeData(uint8 a_data)
{
	/* Data Mode RS=1 */
	g_s_lcdControlConfig[0].pinValue = LOGIC_HIGH;
	DIO_writePin( & g_s_lcdControlConfig[0] );
	
	/* write data to LCD so RW=0 */
	g_s_lcdControlConfig[1].pinValue = LOGIC_LOW;
	DIO_writePin( & g_s_lcdControlConfig[1] );
	
	/* delay for processing Tas = 50ns */
	_delay_ms(1);
	
	/* Enable LCD EN=1 */
	g_s_lcdControlConfig[2].pinValue = LOGIC_HIGH;
	DIO_writePin( & g_s_lcdControlConfig[2] );
	
	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);
	
	/******************************************************************************************/

	for (int i = 0; i < LCD_DATA_BUS_WIDTH; i++ )
	{
		g_s_lcdDataConfig[i].pinValue = ((a_data>>i) & 1);
		DIO_writePin( & g_s_lcdDataConfig[i]);
	}
	
	/******************************************************************************************/
	
	/* delay for processing Tdsw = 100ns */
	_delay_ms(10);
	/* disable LCD EN=0 */
	g_s_lcdControlConfig[2].pinValue = LOGIC_LOW;
	DIO_writePin( & g_s_lcdControlConfig[2] );	
	/* delay for processing Th = 13ns */
	_delay_ms(1);
}

/* --------------------------------------------------------------------------------------------------------
[Function Name] : 	LCD_goToRowColumn
[Description]   : 	called by LCD_dispalyAtRowColumn the function to move the cursor position into the desired
					row and column
[Args]    :	uint8 a_row : the desired line
			uint8 a_column : the desired character index in the line
[Returns] : void
----------------------------------------------------------------------------------------------------------- */
static void LCD_goToRowColumn(uint8 a_row, uint8 a_column)
{
	volatile uint8 address;
	switch(a_row)
	{
		case 0: 
				address = a_column;
				break;
		case 1: 
				address = a_column + 0x40;
				break;
		case 2: 
				address = a_column + 0x10;
				break;
		case 3: 
				address = a_column + 0x50;
				break;
	}
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(address | 0x80);
}

void LCD_sendCommand(uint8 a_command)
{
	#if (LCD_DATA_BUS_WIDTH == 8)			
		writeCommand(a_command);		
	#elif (LCD_DATA_BUS_WIDTH == 4)		
		/* mask lower nibble because D4 --> D7 pins are used. */
		writeCommand(((a_command>>4) & 0x0F));
		/* shift 4-bit and mask */
		writeCommand(a_command & 0x0F);								
	#endif
}

void LCD_displayCharacter(uint8  a_data)
{
	#if (LCD_DATA_BUS_WIDTH == 8)
	/* out the required data char to the data bus D0 --> D7 */
	writeData(a_data);
	#elif (LCD_DATA_BUS_WIDTH == 4)
	/* mask High nibble because D4 --> D7 pins are used at D4 = PIN0 . */
	writeData(((a_data>>4) & 0x0F));
	/* shift 4-bit and mask */
	writeData(a_data & 0x0F);
	#endif
}

void LCD_init(void)
{
	/* fill the g_s_lcdConfig structure with the LCD configurations */
	LCD_configurations();
	
	#if (LCD_DATA_BUS_WIDTH == 8)
		
		/* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	
	#elif (LCD_DATA_BUS_WIDTH == 4)	
	
		LCD_sendCommand(LCD_FOUR_BIT_MODE);
		LCD_sendCommand(TWO_LINE_LCD);
	
	#endif
	
	/* cursor off */
	LCD_sendCommand(CURSOR_OFF);
	
	/* clear LCD at the beginning */
	LCD_sendCommand(LCD_CLEAR);
} 

void LCD_displayString(const uint8 *  a_string_Ptr)
{
	int i = 0;
	while(a_string_Ptr[i] != '\0')
	{
		LCD_displayCharacter(a_string_Ptr[i]);
		i++;
	}
}

void LCD_dispalyAtRowColumn(const uint8 *  a_string_Ptr, uint8 a_row, uint8 a_column)
{
	LCD_goToRowColumn( a_row, a_column);
	LCD_displayString( a_string_Ptr);
}

void LCD_clear (void)
{
	LCD_sendCommand(LCD_CLEAR);
}