/*
Authors: Laura VanDyke and Andrew Fuller
TermProject-Phase3
Date: Nov 18, 2015
*/


#ifndef shared_h
#define shared_h

#define MSG_INFO_SIZE (sizeof(msgBuf) - sizeof(long))
#define BASE_MAILBOX_NAME 0x20667
#define NUMLINES 5
#define SHMEM_KEY 0x100888
#define SHMEM_SIZE sizeof(msgBuf)

typedef struct {
	long mtype;   
	struct {
		pid_t sender;
		int linenumber;
		int msgtype;		//1 = production, 2 = termination
		int cap;
		int dur;
		int itemsmade;
	} info;
} msgBuf;

typedef struct{
	int order;
	int initalorder;
    sem_t super;
    sem_t print;
    sem_t orderSize;
} shared_data;

#endif
