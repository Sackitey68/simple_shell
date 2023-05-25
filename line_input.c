#include "shell.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer that points previous allocated memory
 * @old_size: allocated space for ptr with size in byte
 * @new_size: new memory block with size in byte
 * Return: ptr if new_size == old_size, NULL
 * if new_size == 0 and ptr is not NULL and
 * a pointer pointing  reallocated memory block otherwise
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *memory;
	char *ptr_copy, *fill;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		memory = malloc(new_size);
		if (memory == NULL)
			return (NULL);

		return (memory);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	memory = malloc(sizeof(*ptr_copy) * new_size);
	if (memory == NULL)
	{
		free(ptr);
		return (NULL);
	}

	fill = memory;

	for (index = 0; index < old_size && index < new_size; index++)
		fill[index] = *ptr_copy++;

	free(ptr);
	return (memory);
}

/**
 * assign_lineptr - this reassigns the lineptr
 * variable for _getline function
 * @lineptr: a buffer to store temporal input string
 * @n: lineptr size
 * @buffer: string to assign to lineptr
 * @b: size of buffer
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 125)
			*n = b;
		else
			*n = 125;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 125)
			*n = b;
		else
			*n = 125;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - reads input from an input stream
 * @lineptr: input storage buffer
 * @n: lineptr size
 * @stream: stream to read 
 *
 * Return: number of bytes 
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int y;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 125);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		y = read(STDIN_FILENO, &c, 1);
		if (y == -1 || (y == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (y == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 125)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (y != 0)
		input = 0;
	return (ret);
}
