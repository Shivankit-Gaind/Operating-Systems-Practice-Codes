#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<error.h>
#include<string.h>

struct message_text {
	long mtype;
	char buf [200];
}mess;

int main() {
	int mqid1,mqid2;
	key_t mq1_key,mq2_key;
	mq1_key = ftok("/bin/bash",1);
	if(mq1_key == -1) perror("ftok failed\n");	
	else  printf("mq key successfully created : %d\n",mq1_key);
	mqid1 = msgget(mq1_key,IPC_CREAT | 0660);
	if(mqid1 == -1)
		perror("msgget failed");
	else
		printf("message qid = %d\n",mqid1);

	mq2_key = ftok("/bin/cat",1);
	if(mq2_key == -1) perror("ftok failed\n");	
	else  printf("mq key successfully created : %d\n",mq2_key);
	mqid2 = msgget(mq2_key,IPC_CREAT | 0660);
	if(mqid2 == -1)
		perror("msgget failed");
	else
		printf("message qid = %d\n",mqid2);

	printf("Receiving Message....\n");
	if(msgrcv(mqid1,mess.buf,sizeof(mess),0,0) == -1)  perror("message send failed\n");
	else  printf("pid = %d, Message received from msg queue %d: %s\n",getpid(),mqid1,mess.buf);

	printf("Sending Reply....\n");
	strcpy(mess.buf,"I am fine.");
	if(msgsnd(mqid2,mess.buf,sizeof(mess),0) == -1)  perror("Reply message send failed\n");
	else  printf("pid = %d, Reply Message on msg queue %d: %s\n",getpid(), mqid2,mess.buf);
}

