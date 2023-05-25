#include "main.h"

/**
 * token_len - function that loocates the delimiter
 * index marking the end of the first token
 * @str: the string that will be searched
 * @delim: delimiter character
 *
 * Return: delimiter index marking the end of
 * intitial token pointed to be str
 */
int token_len(char *str, char *delim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * count_tokens - function that counts the number of
 * delimited words contained in a string
 * @str: string to be searched
 * @delim: delimiter character
 *
 * Return: total counts of words contained within str
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - function that tokenizes a string
 * @line: the string
 * @delim: delimiter character to tokenize the string
 *
 * Return: pointer to array containing tokenized words
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, k, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (k = 0; k < tokens; k++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[k] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[k])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[k][l] = line[index];
			index++;
		}

		ptr[k][l] = '\0';
	}
	ptr[k] = NULL;
	ptr[k + 1] = NULL;

	return (ptr);
}
