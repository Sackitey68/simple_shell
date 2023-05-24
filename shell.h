#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
void execute_ls(void);
void execute_userInput(char *userInput);
#include <sys/wait.h>
#include <sys/types.h>

#endif
