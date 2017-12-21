#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>

#define SHMSIZE 27

int main() {
	char c;
	int shmid;
	key_t key;
	char *shm, *s;
	key = 5678;
	
	if((shmid = shmget(key,SHMSIZE,IPC_CREAT|0666)) < 0) {
		perror("shmget");
		exit(1);
	}
	printf("SHM id for the process %d generated as : %d\n",getpid(),shmid);
	if ((shm = shmat(shmid,NULL,0)) == (char *)-1){
		perror("shmat");
		exit(1);
	}
	printf("shared memory attached successfully..\n");
	for(s=shm;*s!='#';s++)
		printf("%c  ",*s);
	putchar('\n');
	
	*shm = '*';
	printf("Its done from client side..\n");
	exit(0);
}
