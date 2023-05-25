#include "shell.h"
/**
 * execute_command - Executes the command provided by the user.
 * @command: The command string entered by the user.
 */
void execute_command(char *command)
{
	char *token, *argv[MAX_LEN];
	int count = 0, status;
	pid_t pid;

	/* tokenize the command to get the program path and the arguments */
	token = strtok(command, " ");

	while (token != NULL && count < MAX_LEN - 1)
	{
		argv[count] = token;
		count++;
		token = strtok(NULL, " ");
	}
	argv[count] = NULL;

	if (strcmp(argv[0], "ls") == 0 && argv[1] == NULL)
	{
		execute_ls();
		return;
	}
	/*Create a child process*/
	pid = fork();
	if (pid == -1)
	{
		perror("Process not created\n");
		return;
	}
	else if (pid == 0)
	{
		printf("Executing program: %s\n", argv[0]);
		if (execve(command, argv, NULL) == -1)
		{
			perror("Execution failed");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}

