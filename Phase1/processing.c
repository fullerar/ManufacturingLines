/*
Names: Laura VanDyke and Andrew Fuller
TermProject-Phase1
Date: Octorber 11, 2015
*/
#ifndef processing_c
#define processing_c

#include "processing.h"
#include "hardware.h"
#include "statemodel.h" // For the other states

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
}

void entry_to()
{
}

#endif
