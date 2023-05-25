#include "shell.h"

/**
 * token_len - function takes a string and a delimiter character input.
 * index marking the end of the first token
 * @str: the searched string
 * @delim: delimiter input character
 *
 * Return: index delimiter indicating end of
 * intitial token pointing to str
 */
int token_len(char *str, char *delim)
{
	int index = 0, length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length = length + 1;
		index = index + 1;
	}

	return (length);
}

/**
 * count_tokens - counts the number of delimited words in a string
 * @str: searched string
 * @delim: delimiter character
 * Return: total words counts contained within str
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, length = 0;

	for (index = 0; *(str + index); index++)
		length = length + 1;

	for (index = 0; index < length; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens = tokens + 1;
			index = index + token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - this function tokenizes a string
 * @line: concerned string
 * @delim: delimiter character tokenizes the string
 * Return: pointer to array that contains tokenized words
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, x, characters, y;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (x = 0; x < tokens; x++)
	{
		while (line[index] == *delim)
			index = index + 1;

		characters = token_len(line + index, delim);

		ptr[x] = malloc(sizeof(char) * (characters + 1));
		if (!ptr[x])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (y = 0; y < characters; y++)
		{
			ptr[x][y] = line[index];
			index++;
		}

		ptr[x][y] = '\0';
	}
	ptr[x] = NULL;
	ptr[x + 1] = NULL;

	return (ptr);
}
