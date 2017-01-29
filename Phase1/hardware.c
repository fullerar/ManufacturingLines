/*
Names: Laura VanDyke and Andrew Fuller
TermProject-Phase1
Date: Octorber 11, 2015
*/
#ifndef hardware_c
#define hardware_c

#include <stdlib.h>
#include <stdio.h>
#include "hardware.h"
#include "statemodel.h"
#include "state.h"


#define LIMIT 3

static int attempts = 1;

void set_Factory_Line(factory_line value)
{
   switch ( value ) 
   {
      case DISPATCH:
	 printf("Current State is: MANUFACTURING\n");         
	 printf("Lines are running.\n");
         break;
      case SHUT_DOWN:
         printf("Lines are not running.\n"); 
         break;
   }
}


void set_Shipping_Result(delivery value)
{
   switch ( value )
   {
      case WARRANTY:
         printf("Starting warranty.\n");
         break;
      case REFUND:
         printf("Refund given.\n");
         break;
   }

	printf("Current State is: ACCEPTING\n");  
}

void updateStats(stats value)
{
    switch (value)
    {
	case FAIL:
             printf("Manufacturing failed.\n");
	     printf("Current State is: ACCEPTING\n");  
             break;
        case LOST:
             printf("Package lost.\n");
             break;
        case DONE:
             printf("Package delivered\n");
             break;
    }
}

void charge_Client()
{
    printf("Client has been charged.\n");
}

state_t* increment_Attempts()
{
    if (attempts < LIMIT) 
    {
        attempts++;
        printf("Attempt #%d\n", attempts-1);
        return &PROCESSING;
    }
    else
    {
	printf("Reached attempt limit. Must order again.\n");
	return &ACCEPTING;
    }
}

void resetAttempts()
{
    attempts = 1;
}

void getAddress()
{
    printf("Current State is: SHIPPING\n");	
    printf("Address recieved\n");
}
#endif
