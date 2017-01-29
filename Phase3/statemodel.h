/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase3
Date: Nov 18, 2015
*/

#ifndef statemodel_h
#define statemodel_h

#include <stdlib.h>
#include "hardware.h"
#include "state.h"

//Declare the states used in the model

extern state_t ACCEPTING;
extern state_t PROCESSING;
extern state_t MANUFACTURING;
extern state_t SHIPPING;

#define LIMIT 3
int attempts;

//Declare all of the functions

void handle_event(event current_event);

#endif
