#include "shell.h"

/**
 * _copyenv - function creates  copy of the environment
 * Return: If error return NULL or a double pointer
 * pointing to new copy otherwise
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * free_env - function frees the memory allocated for copied environment
 * it frees the memory allocated for the environ array itself
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - gets the environmental variable from the PATH
 * @var: name of environmental variable
 * Return: NULL If environmental variable does not exist, or
 * a pointer pointing to environmental variable if otherwise
 */
char **_getenv(const char *var)
{
	int index, length;

	length = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], length) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
