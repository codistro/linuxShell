#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include "parse.h"
#define SIZE 10
#define CURRENT 1000
char *readCommand(){
	int bufferSize = SIZE;
	char *p = (char*)malloc(sizeof(char) * bufferSize);
	int position = 0;
	if(!p){
		printf("ERROR_ALLOCATING_SPACE\n");
		exit(1);
	}
	do{
		int c = getchar();
		p[position++] = c;
		if(c == EOF || c == '\n'){
			p[position] = '\0';
			return p;
		}
		if(position >= SIZE){
			bufferSize = bufferSize * 2;
			p = (char*)realloc(p,bufferSize);
			if(!p){
				printf("ERROR_ALLOCATING_SPACE\n");
				exit(1);
			}
		}		
	}while(1);
}

int execute(char** args){
	if(strcmp("cd",args[0])==0){
		if(chdir(args[1]) != 0)
			printf("UNEXPECTED_ERROR_OCCURED\n");
		return 1;
	}
	else if(strcmp("exit",args[0])==0){
		return 0;
	}
	int pid = fork();
	if(pid == 0){
		execvp(args[0],args);
	}
	else if(pid < 0)
		printf("UNEXPECTED_ERROR_OCCURED\n");
	else
		wait(NULL);
	return 1;
}

int main(int argc,char *argv[]){
	char *command;
	char **arguments;
	int result;
	char cwd[CURRENT];
	system("clear");
	do{
		if(getcwd(cwd,1000)!=NULL)
    		printf("%s$ ",cwd);
    	else
    		printf("ERROR_GETTING_CURRENT_DIRECTORY\n");
		command = readCommand();
		arguments = parse(command);
		result = execute(arguments);

		free(command);
		free(arguments);
	}while(result);

	return 0;
}
