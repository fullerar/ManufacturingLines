/*
Names: Laura VanDyke and Andrew Fuller
TermProject-Phase2
Date: Octorber 27, 2015
*/

#ifndef driver_c
#define driver_c

#include "hardware.h"
#include "statemodel.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	char next_char;
	state_t* curr_state = &ACCEPTING;

	printf("Current state is: ACCEPTING\n");
	scanf("%c", &next_char);

	while(next_char != 'X')
	{
		if(next_char == 'O')
		{
			// order recieved event
			handle_event(ORDER_RCVD);
			if(curr_state == &ACCEPTING)
			{
				curr_state = &PROCESSING;
			}
			scanf("%c", &next_char);
		}
		else if(next_char == 'V')
		{
			//validated payment event
			handle_event(VALID_PYMNT);
			scanf("%c", &next_char);
		}
		else if(next_char == 'I')
		{
			//invalid payment event
			handle_event(INVALID_PYMNT);
			if(curr_state == &PROCESSING) 
			{
				//printf("Current State is: ACCEPTING\n");
			}
			scanf("%c", &next_char);
		}
		else if(next_char == 'F')
		{
			//manu failed event
			handle_event(MANUF_FAILED);
			if(curr_state == &MANUFACTURING) 
			{
				printf("Current State is: ACCEPTING\n");
				
			}			
			scanf("%c", &next_char);
		}
		else if(next_char == 'C')
		{
			//manu completed event
			handle_event(MANUF_COMPLETED);		
			scanf("%c", &next_char);
		}
		else if(next_char == 'R')
		{
			//shipped/recieved event
                        handle_event(RECEIVED);
			if(curr_state == &SHIPPING) 
			{
				printf("Current State is: ACCEPTING\n");
				
			}
			scanf("%c", &next_char);
		}
		else if(next_char == 'L')
		{
			//shipped lost event
			handle_event(LOST_PACKAGE);
			if(curr_state == &SHIPPING) 
			{
				printf("Current State is: ACCEPTING\n");
				
			}
			scanf("%c", &next_char);
		}
		else
		{
			/*printf("Invaild input, try again\n");*/
			scanf("%c", &next_char);
		}
	}
	return 0;
} 
#endif
