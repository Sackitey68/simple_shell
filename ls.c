#include <dirent.h>
#include "shell.h"
/**
 * execute_ls - executes the built in ls command
 * Return: void
 */
void execute_ls(void)
{
	DIR *dir;
	struct dirent *file;
	int fd;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Error opening directory");
		return;
	}

	fd = fileno(stdout);

	while ((file = readdir(dir)) != NULL)
	{
		write(fd, file->d_name, strlen(file->d_name));
		write(fd, " ", 2);
	}
	write(fd, "\n", 1);
	closedir(dir);
}

