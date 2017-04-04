#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include "parse.h"
#define SIZE 1
char *readCommand(){
	int bufferSize = SIZE;
	char *p = malloc(sizeof(char) * bufferSize);
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
			p = realloc(p,bufferSize);
			if(!p){
				printf("ERROR_ALLOCATING_SPACE\n");
				exit(1);
			}
		}		
	}while(1);
}
int main(int argc,char *argv[]){
	system("clear");
	while(1){
		printf("linuxShell($) ");
		char *line = readCommand();
		char **args = parse(line);
		int pid = fork();
		if(pid == 0){
			execvp(args[0],args);
		}
		if(pid < 0){
			printf("error\n");
		}
		if(pid > 0){
			wait(NULL);
		}
	}
	return 0;
}
