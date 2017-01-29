/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase3
Date: Nov 18, 2015
*/

#ifndef driver_c
#define driver_c

#include "hardware.h"
#include "statemodel.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	char next_char;
	bool running;
	running = true;
	state_t* curr_state = &ACCEPTING;

	printf("Current state is: ACCEPTING\n");

	while(running) {

		scanf("%c", &next_char);

		switch(next_char) {
			case 'O':
				handle_event(ORDER_RCVD);
				scanf("%c", &next_char);
				break;
			case 'V':
				handle_event(VALID_PYMNT);
				scanf("%c", &next_char);
				break;
			case 'I':
				handle_event(INVALID_PYMNT);
				scanf("%c", &next_char);
				break;
			case 'F':
				handle_event(MANUF_FAILED);
				scanf("%c", &next_char);
				break;
			case 'C':
				handle_event(MANUF_COMPLETED);
				scanf("%c", &next_char);
				break;
			case 'R':
				handle_event(RECEIVED);
				scanf("%c", &next_char);
				break;
			case 'L':
				handle_event(LOST_PACKAGE);
				scanf("%c", &next_char);
				break;
			case 'X':
				running = false;
				break;
	
		} //switch
	} //while
} //main
		






#endif










