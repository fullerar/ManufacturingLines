/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase2
Date: Octorber 27, 2015
*/

#ifndef processing_c
#define processing_c

#include <stdio.h>

#include "processing.h"
#include "hardware.h"
#include "statemodel.h"// For the other states

// Create the object of the processing state
state_t PROCESSING = {
	default_event_handler,	//order_recieved
	invalid_payment,	//invalid_payment
        valid_payment,          //valid_payment
	default_event_handler,  //manuf_failed
        default_event_handler,  //manuf_completed
	default_event_handler,  //received
        default_event_handler,  //lost_package
	entry_to,		//entry
	default_action		//exit
};

state_t* valid_payment()
{
	
	return &MANUFACTURING;
}

state_t* invalid_payment()
{

	increment_Attempts();
	if (attempts >= LIMIT) 
    	{

		printf("Limit exceeded\n");
		printf("Current State is: ACCEPTING\n");
		return &ACCEPTING;
    	}

	return &PROCESSING;

}

void entry_to()
{
}

#endif
