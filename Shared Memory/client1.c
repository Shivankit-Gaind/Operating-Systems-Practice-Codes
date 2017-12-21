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
	
	for(i=0;i<5;i++){
		printf("Number received from server: %d \n",shm->a[i]);
		shm->sum= shm->sum + shm->a[i];
	}
	printf("sum of 10 numbers processed in client is: %d\n",shm->sum);
	shm->end = '*';
}

/*Output
mayuri@mayuri-laptop:~/Documents/IPC_OS/shared_memory$ ./server 
shm key successfully created : 17104901
SHM id for the process 2160 generated as : 983064
shared memory attached successfully..
Sum received from client: 180
mayuri@mayuri-laptop:~/Documents/IPC_OS/shared_memory$ ./server 
shm key successfully created : 17104901
SHM id for the process 2201 generated as : 983064
shared memory attached successfully..
______________________________________________________________________________________

mayuri@mayuri-laptop:~/Documents/IPC_OS/shared_memory$ ./client1 
shm key successfully created : 17104901
SHM id for the process 2221 generated as : 983064
shared memory attached successfully..
Number received from server: 11 
Number received from server: 12 
Number received from server: 13 
Number received from server: 14 
Number received from server: 15 
Number received from server: 21 
Number received from server: 22 
Number received from server: 23 
Number received from server: 24 
Number received from server: 25 
sum of 10 numbers processed in client is: 180
mayuri@mayuri-laptop:~/Documents/IPC_OS/shared_memory$ 

______________________________________________________________________________________
Server output  

Sum received from client: 180
mayuri@mayuri-laptop:~/Documents/IPC_OS/shared_memory$ 
*/

