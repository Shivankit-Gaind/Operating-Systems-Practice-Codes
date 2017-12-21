#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{
	pid_t childpid = 0;
	int i,n;
	if(argc != 2){
		fprintf(stderr,"Usage: %s processes \n",argv[0]);
		return 1;
	}
	n = atoi(argv[1]);
	for(i = 1; i<=n;i++)
		if(childpid = fork())
			//break;
			printf("Process i = %d, its pid = %ld \n",i,(long)getpid());
			
		else
			printf("Child Process i = %d, its pid = %ld \n",i,(long)getpid());
	
}


