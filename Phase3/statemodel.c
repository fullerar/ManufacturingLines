/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase3
Date: Nov 18, 2015
*/

#ifndef statemodel_c
#define statemodel_c

#include "statemodel.h"
#include <stdlib.h>

//Define the initial state.
static state_t* current_state = &ACCEPTING;

void handle_event( event current_event )
{
	state_t* next_state;

	next_state = NULL;
	switch( current_event ) //exit current_state and have the appropriate effect
	{
		case ORDER_RCVD:
			next_state = current_state->order_recieved();
			break;
		case INVALID_PYMNT:
			next_state = current_state->invalid_payment();
			break;
		case VALID_PYMNT:
			next_state = current_state->valid_payment();
			break;
		case MANUF_FAILED:
			next_state = current_state->manuf_failed();
			break;
        	case MANUF_COMPLETED:
       			next_state = current_state->manuf_completed();
            		break;
        	case RECEIVED:
            		next_state = current_state->received();
            		break;
        	case LOST_PACKAGE:
            		next_state = current_state->lost_package();
            		break;
	}

	if( next_state != NULL )
	{
		current_state = next_state; //change states
		current_state->entry_to(); //enter the new state
	}
}
#endif
