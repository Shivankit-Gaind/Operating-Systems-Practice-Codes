#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include<unistd.h>


void remove_dir(char* y);

int main()
{
	long max= pathconf("/",_PC_PATH_MAX);
	char* name = (char*)malloc(max);
	strcpy(name,"/home/shivankit/Desktop/abc");
	chdir(name);
 	remove_dir(name);	
}

void remove_dir(char* y){

	//Printing the current directory
	long max= pathconf("/",_PC_PATH_MAX);	
	char *buff;
	buff=(char*)malloc(max);	
	getcwd(buff,max);
	printf("%s\n",buff);


	DIR* ds;
	DIR* x; 
	struct dirent *dir;
	
	ds = opendir(y);
	
	
	if(ds == NULL){
	    printf("Directory is not opened\n");
	    return;}
	else
	    printf("ds = %ld\n\n",(long int)ds);
	

	

	dir = readdir(ds);
	while(dir != NULL){		
		
		x = opendir(dir->d_name);
		
		if(x!=NULL){
			if(!(strcmp(dir->d_name,"."))==0 && !(strcmp(dir->d_name,".."))==0){
				//Form the name of the new directory
				char* new_name = (char*)malloc(max);
				strcpy(new_name,y);
				strcat(new_name,"/");
				strcat(new_name,dir->d_name);

				//Change the working directory to the one from which the files are to be removed
				chdir(new_name);
				remove_dir(new_name);
				chdir(buff);
			}
		}
		else{
			remove(dir->d_name);
		}

		dir = readdir(ds);
		
	}	
	
	int cld;
	if((cld = closedir(ds)) == 0)
		printf("Directory is successfully closed\n\n");
	else
	     printf("Directory is not successfully closed\n\n"); 
	rmdir(y);
}

