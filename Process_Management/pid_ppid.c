#include<stdio.h>
#include<unistd.h>

int main() {
printf("I am process %ld\n",(long)getpid());
printf("My Parent is %ld\n",(long)getppid());
system("ps -la");
}


