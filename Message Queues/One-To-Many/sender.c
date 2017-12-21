// Multiple send by a sender process and multiple receiver processes receive single message.

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
	int mqid1;
	key_t mq1_key;
	
	//mqid = msgget(IPC_PRIVATE,0660);
	
	mq1_key = ftok("/bin/bash",1);
	if(mq1_key == -1) perror("ftok failed\n");	
	else  printf("mq1 key successfully created : %d\n",mq1_key);
	mqid1 = msgget(mq1_key,IPC_CREAT | 0660);
	if(mqid1 == -1)
		perror("msgget failed");
	else
		printf("message qid1 = %d\n",mqid1);
	strcpy(mess.buf,"Hello Process 1");
	mess.mtype = 1;
	printf("Sending Message 1....\n");
	if(msgsnd(mqid1,&mess,sizeof(mess),0) == -1)  perror("message send failed\n");
	else  printf("pid = %d, Message on msg queue %d: %s mtype: %ld\n",getpid(),mqid1,mess.buf,mess.mtype);

	strcpy(mess.buf,"Hello Process 2");
	mess.mtype = 2;
	
	printf("Sending Message 2....\n");
	if(msgsnd(mqid1,&mess,sizeof(mess),0) == -1)  perror("message send failed\n");
	else  printf("pid = %d, Message on msg queue %d: %s mtype: %ld\n",getpid(), mqid1,mess.buf,mess.mtype);

}


