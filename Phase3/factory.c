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
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

int main(int argc, char ** argv)
{
	int shmid , tobemade;
	key_t shmkey;
	msgBuf msg;
	shared_data *s;

    key_t msgQueKey;
    int queID;
    int msgStatus;

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
	if(queID == -1)
   	{
	   	printf("Failed to create mailbox %X queID %d \n", queID, msgQueKey);
    	perror("Reason: ");
		exit(-1);
   	}


	int dur = atoi(argv[3]);
    int dur_nano = dur * 1000000;  
    int cap = atoi(argv[2]);
	int i = atoi(argv[1]);
	printf("This is factory line %d with cap= %d, dur= %d\n", i, cap, dur);
    int iter = 0;
    int total = 0;
	printf("factory line %d found superQue at %d\n", i, queID);

    struct timespec var;
    var.tv_nsec = dur_nano;
	var.tv_sec = 0;

	while (1)
    {
        sem_wait(&(s->orderSize));
		if(s->order <= 0)
		{
			sem_post(&(s->orderSize));
			break;
		}
		
        if (s->order < cap) 
			tobemade = s->order ;
		else
			tobemade = cap ;

		s->order -= tobemade ;
		sem_post(&(s->orderSize));

		nanosleep(&var, NULL);

		msg.info.msgtype = 1;	//production message
		//msg.info.sender = getpid();
		msg.info.linenumber = i;
		msg.info.cap = cap;
		msg.info.dur = dur;
        msg.info.itemsmade = tobemade ;
		msg.mtype = 1;

		msgStatus = msgsnd(queID, &msg, MSG_INFO_SIZE, 0);
		if (msgStatus < 0)
		{
			printf("Failed to send message to supervisor");
        	exit(-1); 
		}
  
    }
	// send termination msg
	printf(" factory line %d sending termination msg\n", i);
	msg.info.msgtype = 2;	//termation message
	msg.info.linenumber = i;
	msg.mtype = 1;

	msgStatus = msgsnd(queID, &msg, MSG_INFO_SIZE, 0);
	if (msgStatus < 0)
	{
			printf("Failed to send message to supervisor");
        	exit(-1); 
	}

}
