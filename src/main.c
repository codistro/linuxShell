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
			bufferSize += SIZE;
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
		if(args[1]==NULL)
			printf("No path specified\n");
		else if(chdir(args[1]) != 0)
			printf("%s: No such file or directory\n",args[1]);
		return 1;
	}
	else if(strcmp("exit",args[0])==0){
		return 0;
	}
	else{
		int pid = fork();
		if(pid == 0){
			execvp(args[0],args);
		}
		else if(pid < 0)
			printf("UNEXPECTED_ERROR_OCCURED\n");
		else
			wait(NULL);
	}
	return 1;
}

void commandHistory(char **history,int n){
	for(int i = 0;i < n;i++)
		printf("%s\n",history[i]);
}

int main(int argc,char *argv[]){
	char *command;
	char **arguments;
	int result = 1;
	char *history[10];
	int h = 0;
	char cwd[CURRENT];
	system("clear");
	do{
		if(getcwd(cwd,CURRENT)!=NULL)
    		printf("%s$ ",cwd);
    	else
    		printf("ERROR_GETTING_CURRENT_DIRECTORY\n");
		command = readCommand();
		history[h] = command;
		h = (h + 1)%10;
		arguments = parse(command);
		if(strcmp("history",arguments[0])==0){
			commandHistory(history,h);
		}
		else
			result = execute(arguments);

		free(arguments);
	}while(result);

	return 0;
}
