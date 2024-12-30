#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_PATH 1024

int run(char* line); 

int main(void)
{
	char line[MAX_PATH];
    char currentDir[MAX_PATH];

	while(1){
        if (getcwd(currentDir, sizeof(currentDir)) == NULL) {
            perror("getcwd() error");
            return 0;
        }

		printf("%s $", currentDir);     // Hint. Where are you?
		fgets( line, sizeof(line) - 1, stdin);
		if(run(line) == -1)
			break;
	}
	return 0;
}

int run(char* line) {
    char delims[] = " \r\n\t";
    char* tokens[128];
    int token_count;
    int i;
    int status;
    pid_t child;

    token_count = 2;
    tokens[0] = "ls";
    tokens[1] = "-al";
    tokens[2] = NULL;

	// Run process
    child = fork();
	if (child < 0){
		printf("Failed to fork()!");
		_exit(0);
	}

    if (child == 0) {
        execvp(tokens[0], tokens);
        printf("No such file\n");
        _exit(0);
    } else{
		wait(0);
	}
	return 1;
}
