#include "main.h"

/**
 * error_126 - function that Creates an error
 * message for permission denied failures
 * @args: array of arguments passed
 *
 * Return: Error string
 */
char *error_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_127 - function that creates an error
 * message for command not found failures
 * @args: array of arguments passed
 *
 * Return: error string
 */
char *error_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
