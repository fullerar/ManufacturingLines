/*
Names: Laura VanDyke and Andrew Fuller
TermProject-Phase1
Date: Octorber 11, 2015
*/
#ifndef manufacturing_h
#define manufacturing_h

#include "state.h"

//Declare all of the functions performed when in the manufacturing state
static state_t* manuf_failed();
static state_t* manuf_completed();
static void entry_to();
static void exit_from();

#endif
