#include "shell.h"
/**
 * main - serves as the entry point for the program
 * while(1) - means this loop will keep prompting the user for input until a break condition is met
 * Return: always 0 on success
 */
int main(void)
{
	char *userInput = NULL;
	size_t inputLength = 0;
	ssize_t readInput;

	while (1)
	{
		printf("#cisfun$ ");
		readInput = getline(&userInput, &inputLength, stdin);

		if (readInput == -1)
		{
			if (feof(stdin))
			{
				/*If feof(stdin) evaluates to true, it means the end of the input stream*/
				printf("\n");
				break;
			}
			perror("Input command not read");
			continue;
		}
		userInput[strcspn(userInput, "\n")] = '\0';

		if (userInput[0] == '\0')
		{
			continue;
		}
		execute_userInput(userInput);
	}
	free(userInput);
	return (0);
}
