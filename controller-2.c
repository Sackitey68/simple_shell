#include "shell.h"

/**
 * num_len - function calculates the length of number in terms of digits.
 * @num: Measured number
 * Return: the length of the digits
 */
int num_len(int num)
{
	unsigned int number1;
	int length = 1;

	if (num < 0)
	{
		length = length + 1;
		number1 = num * -1;
	}
	else
	{
		number1 = num;
	}
	while (number1 > 9)
	{
		length = length + 1;
		number1 /= 10;
	}

	return (length);
}

/**
 * _itoa - function that converts integer
 * into string representation
 * @num: the integer to converte into string
 * Return: converted string representation
 */
char *_itoa(int num)
{
	char *buffer;
	int length = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length = length - 1;
	do {
		buffer[length] = (num1 % 10) + '0';
		num1 /= 10;
		length = length - 1;
	} while (num1 > 0);

	return (buffer);
}


/**
 * create_error - This function Writes custom
 *  message based on the given error code
 * @args: array with arguments
 * @err: error value
 * Return: the error value
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
