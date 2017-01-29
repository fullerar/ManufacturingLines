
/*
Names: Laura VanDyke and Andrew Fuller
TermProject-Phase2
Date: Octorber 27, 2015
*/
#ifndef shipping_c
#define shipping_c


#include "state.h"
#include "hardware.h"
#include "statemodel.h" // For the other states
#include "shipping.h"

// Create the object of the shipping state
state_t SHIPPING = {
   	default_event_handler,	//order_recieved
	default_event_handler,	//invalid_payment
        default_event_handler,  //valid_payment
	default_event_handler,  //manuf_failed
        default_event_handler,  //manuf_completed
	received,  		//received
        lost_package,		//lost_package
	entry_to,		//entry
	default_action		//exit
};

state_t* received()
{
    updateStats(DONE);
    set_Shipping_Result(WARRANTY);
    return &ACCEPTING;
}

state_t* lost_package()
{
   updateStats(LOST);
   set_Shipping_Result(REFUND);
   return &ACCEPTING;
}

void entry_to()
{
   getAddress();
}

#endif
