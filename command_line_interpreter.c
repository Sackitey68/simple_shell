#include "shell.h"
/**
 * main - entry point
 * Return: always 0
 */
int main(void)
{
	char *command = NULL;
	size_t length = 0;
	ssize_t command_read;
	/*Ready to receive command from user*/
	while (1)
	{
		printf("SimpleShell$ ");
		command_read = getline(&command, &length, stdin);

		if (command_read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("Command not read");
			continue;
		}
		command[strcspn(command, "\n")] = '\0';

		if (command[0] == '\0')
		{
			continue;
		}
		execute_command(command);
	}
	free(command);
	return (0);
}
