/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase3
Date: Nov 18, 2015
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

#include <errno.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shared.h"

void dispatch()
{
    int i;
    
    pid_t pid;
    pid_t superPID;

    int shmid;
    key_t shmkey;
    int shmflg;

	shared_data *s;

	char msgs1[40];
	char msgs2[40];
	char msgs3[40];

	int cap;
	int dur;

	printf("Current State is: MANUFACTURING\n");         
    printf("Dispatching factory lines.\n");

	shmkey = SHMEM_KEY;
     
    shmid = shmget(shmkey, SHMEM_SIZE, IPC_CREAT | 0660);
    if(shmid == -1)
    {
	    printf("Failed to create shared memory\n");
	    perror("Reason: ");
		exit(-1);
    }

    s = (shared_data *) shmat(shmid, NULL, 0);
    if(s == (shared_data *) -1)
    {
	    printf("Failed to attach shared memory\n");
		exit(-1);
	}

    sem_init(&(s->super), 1, 0);
    sem_init(&(s->print), 1, 0);
    sem_init(&(s->orderSize), 1, 1);

    s->order = order_size();
	s->initalorder = s->order;

    superPID = fork();
	if (superPID == -1)
	{
		printf("Supervisor fork failed\n");
		exit(-1);
	} 
    if(superPID == 0)
    {
		if(execlp("gnome-terminal", "SuperVterm", "-x", "/bin/bash", "-c", "./supervisor 5", NULL) < 0)
    	{
      		perror("execlp Supervisor Failed\n");
       		exit(-1);
		}
    }

    //fork children
    for (i=0; i<NUMLINES; i++)
    {
		cap = capacity();
    	dur = duration();

	    pid = fork();
		if (pid == -1)
		{
			printf("Factory line fork failed");
			exit(-1);
		} 
        if (pid == 0)
        {
      		snprintf(msgs1, 40, "%d", i);
      		snprintf(msgs2, 40, "%d", cap);
      		snprintf(msgs3, 40, "%d", dur);

           	if(execlp("./factory", "gffg" , msgs1, msgs2 , msgs3, NULL) < 0)
           	{
           		perror("execlp Client failed\n");
                exit(-1);
            }
        }
	}

	//Wait for all factory lines to finish
	sem_wait(&(s->super));

	//Inform supervisor to print factory line info
	sem_post(&(s->print));

	//Wait for report from supervisor
	sem_wait(&(s->super));

	//Delete shared memory and semaphores
	sem_destroy(&(s->super)); 
	sem_destroy(&(s->print));
	sem_destroy(&(s->orderSize));

	shmdt(s);
	shmctl(shmid, IPC_RMID, NULL);	    
}

void shutdown()
{
	printf("Shutting down factory lines.\n");
}

void set_Factory_Line(factory_line value)
{
    switch ( value ) 
    {
         case DISPATCH:
         	dispatch();
			break;
         case SHUT_DOWN:
			shutdown();
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
    printf("Current State is: PROCCESSING\n");
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

/*
void * threads(void * array)
{
    int cap = capacity(); 
    int dur_sec = duration(); 
    int dur_nano = dur_sec * 1000000;  
    int * i = (int *)array; 
    int iter = 0;
    int total = 0;

    struct timespec sec, nano;
    sec.tv_sec = dur_sec;
    nano.tv_nsec = dur_nano;

    printf("Manufacturing Line %d created - Capacity: %d - Duration (in milliseconds) %d\n"
            , *i, cap, dur_sec);

    while (s.order > 0)
    {
        nanosleep(&sec, &nano);
        sem_wait(&(s.super));
        
        if (s.order < cap) 
        {
            if (s.order < 0) 
            {
                s.order = 0;
            }
            else
                 total += s.order;
            {
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
        sem_post(&(s.super));    
    }
    
    printf("Line %d performed %d iterations and manufactured %d items\n"
            , *i, iter, total);
}
*/
#endif

