#include <stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include<sys/types.h>	
#include<unistd.h>
#include <fcntl.h>
int main(){int file_desc = open("dup.txt", O_CREAT | O_WRONLY,0777);
if(file_desc < 0)
printf("Error opening the file\n");
int copy_desc = dup(file_desc);
printf("%d\n",write(copy_desc,"This will be output to the file named dup.txt\n", 46));
printf("%d\n",write(file_desc,"This will also be output to the file named dup.txt\n", 51));
return 0;}
