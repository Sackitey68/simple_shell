#include "shell.h"
/**
 * execute_userInput - Responsible for Executing the input provided by the user.
 * @userInput: The input string the user entered.
 * pid_t pid;: pid is of type pid_t is used to store the process ID
 */
void execute_userInput(char *userInput)
{
	/* These variables are used for tokenizing the user input and storing the program path and arguments.*/
	char *tokens, *argv[MAX_LEN];
	int tokenCount = 0, /* tokenCount keeps track of the number of tokens*/
	int status; /* status is used to store the exit status of the child process.*/
	pid_t pid;

	/* tokenize the user input to get the program path and the arguments */
	tokens = strtok(userInput, " ");

	while (tokens != NULL && tokenCount < MAX_LEN - 1)
	{
		argv[tokenCount] = tokens;
		tokenCount++;
		tokens = strtok(NULL, " ");
	}
	argv[tokenCount] = NULL;

	if (strcmp(argv[0], "ls") == 0 && argv[1] == NULL)
	{
		execute_ls();
		return;
	}

	pid = fork();
	/* The fork call creates a new process, duplicating the current process.*/
	if (pid == -1)
	{
		perror("process not created\n");
		return;
		/* f fork returns -1, it means an error occurred while creating the child process*/
	}
	else if (pid == 0)
	{
		printf("Executing program: %s\n", argv[0]);
		if (execve(userInput, argv, NULL) == -1)
		{
			perror("Execution failed");
			exit(1);
			/* If execve returns -1, an error occurred during execution*/
		}
	}
	else
	{
		wait(&status);
	}
}

