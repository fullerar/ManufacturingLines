/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase3
Date: Nov 18, 2015
*/

#ifndef state_h
#define state_h

// Add an alias for a type to the global name space
typedef struct state state_t;

// Add an alias for even handlers
typedef state_t* event_handler(void);

// Add an alias for actions
typedef void action(void);

// Define the format of a state struct
struct state {
   event_handler* order_recieved;
   event_handler* invalid_payment;
   event_handler* valid_payment;
   event_handler* manuf_failed;
   event_handler* manuf_completed;
   event_handler* received;
   event_handler* lost_package;
   action* entry_to;
   action* exit_from;
};

// Declare vairables to hold pointer to the default event handler and
// the default action. They are extern because they are used in each
// of the individual state files but defined in state.c
extern state_t* default_event_handler();
extern void default_action();

#endif
