#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

#define END_OF_FILE -2
#define EXIT -3

char *name;
extern char **environ;
int hist;

/**
 * struct builtin_s - struct type defining builtin inputs.
 * @name: name associated with builtin inputs
 * @f: A function pointer that points to the builtin input function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct list_s - struct type for  a linked list.
 * @dir: path of directory.
 * @next: A pointer that points to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct alias_s - A struct for aliases.
 * @name: name of alias.
 * @value: value of alias.
 * @next: A pointer that points to another struct alias_s.
 */
typedef struct alias_s
{
	char *value;
	char *name;
	struct alias_s *next;
} alias_t;

alias_t *aliases;

int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);

list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, const char *src);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

int (*get_builtin(char *command))(char **args, char **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_exit(char **args, char **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);

char **_getenv(const char *var);
void free_env(void);
char **_copyenv(void);

int proc_file_commands(char *file_path, int *exe_ret);

alias_t *add_alias_end(alias_t **head, char *name, char *value);
list_t *add_node_end(list_t **head, char *dir);
void free_alias_list(alias_t *head);
void free_list(list_t *head);

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

#endif
