/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase2
Date: Octorber 27, 2015
*/

#ifndef hardware_c
#define hardware_c

#include <stdlib.h>
#include <stdio.h>
#include "hardware.h"
#include "statemodel.h"
#include "state.h"
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>





static shared_order s;

void set_Factory_Line(factory_line value)
{
   int i;
   pthread_t tid[5];
   int * array = malloc(sizeof(array));

   sem_init(&(s.man_sem), 0, 1);

   switch ( value ) 
   {
		case DISPATCH:
	    	printf("Current State is: MANUFACTURING\n");         
	    	printf("Dispatching factory lines.\n");
        	s.order = order_size();
	    	printf("Order Size: %d\n", s.order);
	 	 
	    	for (i = 0; i < 5; i++)
	    	{
	        	array = malloc(sizeof(array));
	    		array[0] = i + 1;
	     		pthread_create(&tid[i], NULL, threads, (void *) array);
	 		}
         
	    	for (i = 0; i < 5; i++)
	    	{
	    		pthread_join(tid[i], NULL);
	 		}
	 	    sem_destroy(&(s.man_sem));

	 		if (s.order == 0) /* Lines completed the order */
            {
                printf("Order Complete\n");
            }
            else if (s.order > 0) /* Lines did not complete the order */
            {
                printf("Order Incomplete\n");
            }
            else /* Lines produced more than the order */
            {
                printf("Order Exceeded - Manufactured over specified order\n");
            }        	
            break;
      	case SHUT_DOWN:
        	printf("Shutting down factory lines.\n"); 
        	break;
	}
}


void set_Shipping_Result(delivery value)
{
	switch ( value )
    {
    	case WARRANTY:
        	printf("Starting warranty.\n");
        	printf("Updating stats with DONE.\n");
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
	     	set_Factory_Line(SHUT_DOWN);
	     	printf("Updating stats with FAIL.\n");
            printf("Current State is: ACCEPTING\n");
            break;
        case LOST:
            printf("Package lost.\n");
	     	printf("Updating stats with LOST.\n");
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
	attempts++;
	printf("Incrementing attempts.\n");

}

void resetAttempts()
{
    attempts = 0;
}

void getAddress()
{
    printf("Current State is: SHIPPING\n");	
    printf("Getting address\n");
}

int order_size()
{
    srandom(time(NULL));
    int min = 1000;
    int max = 2000;
    int r = random()%(max-min)+min;
    return r;
    
}

int capacity()
{
    int min = 10;
    int max = 50;
    int r = random()%(max-min)+min;
    return r;
}

int duration()
{
    int r = (random()%5) + 1;
    return r;
}

void * threads(void * array)
{
    int cap = capacity(); /* setting this thread's capcity */
    int dur = duration(); /* setting this thread's duration */
    int * i = (int *)array; /* number thread this is */
    int iter = 0;
    int total = 0;

    printf("Manufacturing Line %d created - Capacity: %d - Duration %d\n"
            , *i, cap, dur);
    while (s.order > 0)
    {
        if (s.order < cap) /* Items left are less than thread's capacity */
		{
            sleep(dur);
	    	sem_wait(&(s.man_sem));
            if (s.order < 0) /* Order has already been completed */
	    	{
				s.order = 0;
	    	}
	    	else
	    	{
           	    total += s.order;
	       		s.order -= s.order;
				iter++;
	    	}
	   		sem_post(&(s.man_sem));
		}
		else
        {
		    sleep(dur);
		    sem_wait(&(s.man_sem));
		    if (s.order < cap) /* Items left are less than thread's capacity */
		    {
				if (s.order < 0) /* Order has already been completed */
				{
				    s.order = 0;
				}
				else
				{
				    total += s.order;
		            s.order -= s.order;
				    iter++;
				}
			}
            else
		    {
				s.order -= cap;
				total += cap;
				iter++;
		    }
		    sem_post(&(s.man_sem));
		}    
    }
    
    printf("Line %d performed %d iterations and manufactured %d items\n"
            , *i, iter, total);
}
#endif
