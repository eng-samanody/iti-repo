/* ---------------------------------------------------------------------------------------------------

[FILE NAME]:      < app.c >
[AUTHOR(S)]:      < Mohamed AbdelRaouf >
[DATE CREATED]:   < Mon 12/29/2014 >
[DESCRIPTION]:    < Application layer for this Project. it is required to call the lcd initialization function.  >

------------------------------------------------------------------------------------------------------- */

/*--------------------------------------------- INCLUDES -----------------------------------------------*/

#include "app.h"

/*------------------------------------- FUNCTION DEFINITIONS -------------------------------------------*/


void APP_init(void)
{
	/* Initialize LED Driver */
	LCD_init();
	_delay_ms(100);
}


void APP_start(void)
{
	//SET_BIT(DDRD,PD1) ;
	//SET_BIT(PORTD, PD1);
	APP_init();
	LCD_displayString("Hello TAREK :)");
	_delay_ms(1000);
	LCD_clear();
	LCD_dispalyAtRowColumn("RAOUF", 0 , 5);
	for (int i=0; i<4; i++)
	{
		LCD_sendCommand(LCD_SHIFT_RIGHT);
		_delay_ms(250);
	}
	for (int i=0; i<8; i++)
	{
		LCD_sendCommand(LCD_SHIFT_LEFT);
		_delay_ms(250);
	}
	_delay_ms(500);
	LCD_clear();
	LCD_dispalyAtRowColumn("ITI 35 :)", 1 , 3);
	_delay_ms(1000);
	LCD_clear();
}
/*******************************************************************************************************************/
