#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>


struct shared_memory{ int a[10]; int sum; char end;};
int main() {
	char c;
	int shmid,i;
	key_t key;
	struct shared_memory *shm, *s;

	key = ftok("/bin/bash",1);
	if(key == -1) perror("ftok failed\n");	
	else  printf("shm key successfully created : %d\n",key);
	
	if((shmid = shmget(key,sizeof(struct shared_memory),IPC_CREAT|0666)) < 0) {
		perror("shmget");
		exit(1);
	}
	printf("SHM id for the process %d generated as : %d\n",getpid(),shmid);
	if ((shm = (struct shared_memory *)shmat(shmid,NULL,0)) == (struct shared_memory *)-1){
		perror("shmat");
		exit(1);
	}
	printf("shared memory attached successfully..\n");
	
	for(i=5;i<10;i++){
		printf("Number received from server: %d \n",shm->a[i]);
		shm->sum= shm->sum + shm->a[i];
	}
	printf("sum of 10 numbers processed in client is: %d\n",shm->sum);
	shm->end = '*';
}
