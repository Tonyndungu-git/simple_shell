#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LEN 1024

/**
 * main - function thats acts as a shell.
 * @argc: no of arguments.
 * @argv: pointer to list of arguments.
 */

int main(int argc, char *argv[])
{
	char line[MAX_LINE_LEN];
	char *args[MAX_LINE_LEN];
	int status;

	while (1)
	{
		write(1,"#cisfun$ ",10);
		if (fgets(line, MAX_LINE_LEN, stdin) == NULL)
		{
			break;
		}
		int arg_count = 0;

		char *token = strtok(line, " \n");
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " \n");
		}
		pid_t pid = fork();
		if (pid == 0) {
			args[arg_count] = NULL;
			execvp(args[0], args);
		} else if (pid > 0) {
			waitpid(pid, &status, 0);
		} else {
			write(2, "fork", 5);
			exit(1);
		}
	}
	return 0;
}
