#ifndef SHELL_H
#define SHELL_H

#define MAX_LEN 1024

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
void execute_ls(void);
void execute_command(char *command);
#endif /* SHELL_H */
