#include<stdio.h>
#include<unistd.h>

int main()
{
	int x,pid;
	x = 0;
	int mypid = getpid();
	printf("Before fork value of x = %d in parent process = %ld\n",x,(long)getpid());
	pid = fork();
	if(pid == -1){
		printf("Failed to fork\n");
		return 0;
	}
	if(pid == 0){
		x = 1;
		printf("I am child process %ld and my x is %d\n",(long)getpid(),x);
	}
	else{
		x = 2;
		printf("I am parent process %ld and my x is %d\n",(long)getpid(),x);
	}

		
}

