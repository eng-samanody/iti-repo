/* -------------------------------------------------------------------------------------------------------------
[FILE NAME]:      < dio.c >
[AUTHOR(S)]:      < Mohamed AbdelRaouf >
[DATE CREATED]:   < Mon 12/29/2014>
[DESCRIPTION]:    < The dio file includes all the functions that deals with the hardware of the chip
					such as setting ports direction, reading status and sending output values >
----------------------------------------------------------------------------------------------------------------- */

/*--------------------------------------------- INCLUDES ---------------------------------------------------------*/

#include "dio.h"

/*-------------------------------------------- FUNCTION DEFINITIONS ----------------------------------------------*/

void DIO_setDirection(const DioConfig * a_CONFIG_MSG_Ptr )
{
	volatile uint8 * DDR_Ptr;
	/* point to the required DDR Register */
	switch(a_CONFIG_MSG_Ptr->port)
	{
		case 'A': DDR_Ptr = &DDRA;
				  break;
		case 'B': DDR_Ptr = &DDRB;
				  break;
		case 'C': DDR_Ptr = &DDRC;
				  break;
		case 'D': DDR_Ptr = &DDRD;
				  break;
	}
	
	if( a_CONFIG_MSG_Ptr -> direction == OUTPUT )
	{
		/* set the corresponding bit in the DDR register to configure it as output pin */
		SET_BIT( *DDR_Ptr , a_CONFIG_MSG_Ptr->pinNum );
	}

	else if( a_CONFIG_MSG_Ptr -> direction == INPUT )
	{
		/* clear the corresponding bit in the DDR register to configure it as input pin */
		CLEAR_BIT( *DDR_Ptr , a_CONFIG_MSG_Ptr -> pinNum );
			
	}

}



void DIO_writePin(const DioConfig * a_STATE_Ptr)
{
	volatile uint8 * PORT_Ptr;
	/* point to the required PORT Register */
	switch(a_STATE_Ptr -> port)
	{
		case 'A': 
				  PORT_Ptr = &PORTA;
				  break;
		case 'B': 
				  PORT_Ptr = &PORTB;
				  break;
		case 'C': 
				  PORT_Ptr = &PORTC;
				  break;
		case 'D': 
				  PORT_Ptr = &PORTD;
				  break;
	}
	if( a_STATE_Ptr -> pinValue == LOGIC_HIGH )
	{
		/* set the corresponding pin in the PORT register */
		SET_BIT(*PORT_Ptr , a_STATE_Ptr -> pinNum);
	}
    else if(a_STATE_Ptr -> pinValue == LOGIC_LOW)
	{
		/* clear the corresponding pin in the PORT register */
        CLEAR_BIT( *PORT_Ptr , a_STATE_Ptr -> pinNum );
	}
}

void DIO_writePort(const uint8 a_port, uint8 a_portValue)
{
	volatile uint8 * PORT_Ptr;
	/* point to the required PORT Register */
	switch( a_port )
	{
		case 'A': 
				  PORT_Ptr = &PORTA;
				  break;
		case 'B': 
				  PORT_Ptr = &PORTB;
				  break;
		case 'C': 
				  PORT_Ptr = &PORTC;
				  break;
		case 'D': 
				  PORT_Ptr = &PORTD;
				  break;
	}
	
	*PORT_Ptr = a_portValue;
}


uint8 DIO_readPin( const DioConfig * a_STATE_Ptr )
{
	volatile uint8 * PIN_Ptr;
	uint8 output;
	/* point to the required PIN Register */
	switch( a_STATE_Ptr -> port )
	{
		case 'A': 
				  PIN_Ptr = &PORTA;
				  break;
		case 'B': 
				  PIN_Ptr = &PORTB;
				  break;
		case 'C': 
				  PIN_Ptr = &PORTC;
				  break;
		case 'D': 
				  PIN_Ptr = &PORTD;
				  break;
	}
	
	/* check if the corresponding bit is set in the PIN register */
	if(BIT_IS_SET( *PIN_Ptr, a_STATE_Ptr -> pinNum ))
	{
		output =  LOGIC_HIGH;
	}
	
	/* check if the corresponding bit is clear in the PIN register */
	else if(BIT_IS_CLEAR( *PIN_Ptr , a_STATE_Ptr -> pinNum ))
	{
		output = LOGIC_LOW;
	}
	return output;
}

uint8 DIO_readPort(uint8 a_port)
{
	volatile uint8 * PORT_Ptr;

	/* point to the required PPORT Register */
	switch( a_port )
	{
		case 'A':
		PORT_Ptr = &PORTA;
		break;
		case 'B':
		PORT_Ptr= &PORTB;
		break;
		case 'C':
		PORT_Ptr = &PORTC;
		break;
		case 'D':
		PORT_Ptr = &PORTD;
		break;
	}

	return *PORT_Ptr;
}

/********************************************************************************************************************/
