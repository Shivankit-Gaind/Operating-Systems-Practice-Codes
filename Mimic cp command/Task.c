//To implement a cp command, a buffer intermediate is required

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(){
	char* dir_name = "Shivankit";
	int md = mkdir(dir_name,0777);
	if(md == 0)
		printf("Directory %s is created\n",dir_name);
	
	DIR* dr = opendir(dir_name);

	if(dr == NULL)
	    printf("directory %s is not opened\n",dir_name);
	else
		printf("ds = %x\n",dr);

	chdir(dir_name);
	long max= pathconf("/",_PC_PATH_MAX);	
	char *buff;
	buff=(char*)malloc(max);	
	getcwd(buff,max);
	printf("%s\n",buff);

	
	int fd = open("file1.txt", O_CREAT|O_WRONLY, 0777);
	
	//Converting data to char buffer
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	char* buffer = (char*)arr;
	
	//Writing data to the file
	int written = write(fd,buffer,40);
	//int written = write(fd,arr,40);
	close(fd);
	printf("%d\n",written);
	
	


	//Reading data back
	char buffer2[40];
	fd = open("file1.txt", O_CREAT|O_RDONLY);
	int nread = read(fd,buffer2,40);	
	printf("%d\n", nread);


	//Converting back to int data
	int* reading = (int*)buffer2; int i;
	for(i=0;i<10;i++)
		printf("%d\n",reading[i]);

	//Now write this back to another file to mimic the cp command


	return 0;
}

