#include<stdio.h>
#include<unistd.h>

int main()
{
	int pid;
	printf("Before fork the parent process = %ld\n",(long)getpid());
	pid = fork();
	if(pid == -1){
		printf("Failed to fork\n");
		return 0;
	}
	if(pid == 0){
		printf("I am child process %ld \n",(long)getpid());
	}
		
}
