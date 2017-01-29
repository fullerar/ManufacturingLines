/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase3
Date: Nov 18, 2015
*/

#ifndef manufacturing_c
#define manufacturing_c
#include <stdio.h>
#include "manufacturing.h"
#include "hardware.h"
#include "statemodel.h"


//Create the object of the manufacturing state
state_t MANUFACTURING = {
	default_event_handler,	//order_recieved
	default_event_handler,  //invalid_payment
    default_event_handler,  //valid_payment
	manuf_failed,		    //manuf_failed
    manuf_completed,	    //manuf_completed
	default_event_handler,  //received
    default_event_handler,  //lost_package
	entry_to,				//entry
	exit_from				//exit
};

state_t* manuf_failed()
{
	updateStats(FAIL);
	return &ACCEPTING;
}

state_t* manuf_completed()
{
    exit_from();
	charge_Client();
    return &SHIPPING;
}

void entry_to()
{
	set_Factory_Line(DISPATCH);
}

void exit_from()
{
	set_Factory_Line(SHUT_DOWN);
}

#endif
