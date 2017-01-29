/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase3
Date: Nov 18, 2015
*/


#include <stdlib.h>
#include <stdio.h>
#include "hardware.h"
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

int msgget(key_t key, int msgflg);
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);


int main(int argc, char ** argv)
{     
	int shmid;
	key_t shmkey;
	msgBuf msg;
	shared_data *s;

    key_t msgQueKey;
    int queID;
    int msgStatus;

	int msgtype;

	int dur_array[5] = {0};
	int cap_array[5] = {0};
	int iter_array[5] = {0};
	int items_array[5] = {0};

	int x = 0;

	int i = 0;
	int line;

	int numberoflines = atoi(argv[1]);
	printf("I am the supervisor with %d factory lines\n", numberoflines);

	//get shared mem
	shmkey = SHMEM_KEY;
	shmid = shmget(shmkey, SHMEM_SIZE, 0660);
	if(shmid != -1)
	{
		printf("\nShared memory segment '0x%X' %s %d\n", shmkey, 
			"successfully created/Found with id=",shmid);
	}

	//attach to
	s = (shared_data *) shmat(shmid, NULL, 0660);
	if (s == (shared_data *) -1)
	{
		printf("Failed to attach to shared memory\n");
		exit(-1);
	}

	//get Que 
	msgQueKey = BASE_MAILBOX_NAME;
   	queID = msgget(msgQueKey, IPC_CREAT | 0600);
	if(queID < 0)
   	{
	   	printf("Failed to create mailbox %X queID %d \n", queID, msgQueKey);
    	perror("Reason: ");
		exit(-1);
   	}
	printf("Supervisor created msg que with id %d\n", queID);		
    while(numberoflines > 0)
    {
		msgStatus = msgrcv(queID, &msg, MSG_INFO_SIZE, 0, 0);
		if (msgStatus < 0)
		{
			printf("Failed to recieve message from queue\n");
			exit(-1);
		}
		msgtype = msg.info.msgtype;		//check type of messege from line
		line = msg.info.linenumber;
	

		if (msgtype == 1)
		{
			printf("Recieved production message from line %d\n", line);
			dur_array[line] = msg.info.dur;
			cap_array[line] = msg.info.cap;
			

			iter_array[line] += 1;
			items_array[line] += msg.info.itemsmade;

		}
		else if (msgtype == 2 )
		{
			printf("Recieved termination message from line %d\n", line);
			/*
			dur_array[line] = msg.info.dur;
			cap_array[line] = msg.info.cap;
			iter_array[line] = msg.info.iterations;
			items_array[line] = msg.info.itemsmade;
			*/
			numberoflines--;
		}
		else
		{
			//discard message
		}             
    }

	//Inform parent all factory lines are done
	sem_post(&(s->super));

	//Wait for permission to print info
	sem_wait(&(s->print));

	//order size, capcity and duration
	//number of iter and total items per line

	printf("Order Size: %d\n", (s->initalorder));

	for (i = 0; i < 5; i++)
	{	
		printf("Line %d - Capacity: %d - Duration: %d - Iterations: %d - Total Items Made: %d\n"
				, i+1, cap_array[i], dur_array[i], iter_array[i], items_array[i]);
	}

	//Inform parent that reports are done
	sem_post(&(s->super));

	msgctl(queID, IPC_RMID, NULL);

    return 0;       
}
