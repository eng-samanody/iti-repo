/* ---------------------------------------------------------------------------------------------------

[FILE NAME]:      < app.h >
[AUTHOR(S)]:      < Mohamed AbdelRaouf >
[DATE CREATED]:   < Mon 12/29/2014 >
[DESCRIPTION]:    < Application layer for this Project. it is required to make the led on when a button is pressed.  >

------------------------------------------------------------------------------------------------------- */



#ifndef APP_H_
#define APP_H_

/*--------------------------------------------- INCLUDES -----------------------------------------------*/

#include "lcd.h"

/*------------------------------------- FUNCTION DEFINITIONS ---------------------------------------------*/

/* --------------------------------------------------------------------------------------------------------
[Function Name] : 	APP_init
[Description]   : 	the function is responsible for the hardware initialization by calling
					initialization function of both the LCD
[Args]    :	void
[Returns] : void
--------------------------------------------------------------------------------------------------------- */
void APP_init(void);

/* --------------------------------------------------------------------------------------------------------
[Function Name] : 	appStart
[Description]   : 	the function is responsible for implementing the main business of the project it simply
					detect the state of the button by calling the buttonGetState function and toggles the
					led upon any change in the button state
[Args]    : void
[Returns] : void
--------------------------------------------------------------------------------------------------------- */
void APP_start(void);


#endif /* APP_H_ */
/*******************************************************************************************************************/