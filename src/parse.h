#define DELIM " \t\n\r\a"
#define SIZE 10
char **parse(char *line){
	int bufferSize = SIZE;
	char **commands = (char**)malloc(sizeof(char*) * bufferSize);
	char *command;
	int position = 0;
	if(!commands){
		printf("ERROR_ALLOCATING_SPACE\n");
		exit(1);
	}
	command = strtok(line,DELIM);
	while(command!=NULL){
		commands[position++] = command;
		if(position>=bufferSize){
			bufferSize = bufferSize * 2;
			commands = (char**)realloc(commands,bufferSize);
			if(!commands){
				printf("ERROR_ALLOCATING_SPACE\n");
				exit(1);
			}
		}
		command = strtok(NULL,DELIM);
	}
	commands[position] = NULL;
	return commands;
}