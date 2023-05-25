#include "shell.h"

/**
 * cant_open - if file doesn't exist or lacks proper permissions
 * a cant open error.0
 * @file_path: Path to supposed file in the shell.
 *
 * Return: 130.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (130);

	length = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (130);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, length);
	free(error);
	return (130);
}

/**
 * file_commands - Takes a file and run the commands stored
 * @file_path: Path to file location
 * @exe_ret: Return value of last executed command file.
 *
 * Return: If file couldn't be opened - 130.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of last command line.
 */
int file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, m;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (m = 0; line[m] == '\n'; m++)
		line[m] = ' ';
	for (; m < line_size; m++)
	{
		if (line[m] == '\n')
		{
			line[m] = ';';
			for (m += 1; m < line_size && line[m] == '\n'; m++)
				line[m] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (m = 0; args[m]; m++)
	{
		if (_strncmp(args[m], ";", 1) == 0)
		{
			free(args[m]);
			args[m] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++m];
			m = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}
