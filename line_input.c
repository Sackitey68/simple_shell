#include "main.h"

/**
 * _realloc - function that reallocates a memory
 * block using malloc and free
 * @ptr: pointer to previously allocated memory
 * @old_size: size in bytes of allocated space for ptr
 * @new_size: size in bytes for new memory block
 *
 * Return: ptr if new_size == old_size, NULL
 * if new_size == 0 and ptr is not NULL and
 * a pointer to reallocated memory block if otherwise
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = mem;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return (mem);
}

/**
 * assign_lineptr - function that reassigns the lineptr
 * variable for _getline
 * @lineptr: a buffer to store input string
 * @n: size of lineptr
 * @buffer: string to assign to the lineptr
 * @b: buffer size
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - function that reads input from a stream
 * @lineptr: buffer to store input
 * @n: The size of lineptr
 * @stream: stream to read from
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int e;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		e = read(STDIN_FILENO, &c, 1);
		if (e == -1 || (e == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (e == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (e != 0)
		input = 0;
	return (ret);
}
