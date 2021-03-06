/*
Names: Laura VanDyke and Andrew Fuller
TermProject-Phase1
Date: Octorber 11, 2015
*/
#ifndef accepting_c
#define accepting_c

#include "accepting.h"
#include "hardware.h"
#include "statemodel.h"

//Create the object of the accepting state
state_t ACCEPTING = {
	order_recieved,		//order_recieved
	default_event_handler,  //invalid_payment
        default_event_handler,  //valid_payment
	default_event_handler,  //manuf_failed
        default_event_handler,  //manuf_completed
	default_event_handler,  //received
        default_event_handler,  //lost_package
	default_action,		//entry
	default_action		//exit
};

state_t* order_recieved()
{
	resetAttempts();
	return &PROCESSING;
}

#endif
