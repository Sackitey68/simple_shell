#include "shell.h"

/**
 * shellby_alias - This is a Builtin line that either prints
 * all aliases, specific aliase, or to set an alias.
 * @args: an array of arguments.
 * @front: A double pointer pointing to begin args.
 *
 * Return: If error occurs -1.
 *         else - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int y;
	int remit = 0;
	char *valueIndex;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (remit);
	}
	for (y = 0; args[y]; y++)
	{
		temp = aliases;
		valueIndex = _strchr(args[y], '=');
		if (!valueIndex)
		{
			while (temp)
			{
				if (_strcmp(args[y], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				remit = create_error(args + y, 1);
		}
		else
			set_alias(args[y], valueIndex);
	}
	return (remit);
}

/**
 * set_alias - this will set either existing alias 'name' to new value,
 * @variable_name: is the  Name of the alias
 * @value: Value of the alias. character first is an '='
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int length, p, q;
	char *new_valueIndex;

	*value = '\0';
	value = value + 1;
	length = _strlen(value) - _strspn(value, "'\"");
	new_valueIndex = malloc(sizeof(char) * (length + 1));
	if (!new_valueIndex)
		return;
	for (p = 0, q = 0; value[p]; p++)
	{
		if (value[p] != '\'' && value[p] != '"')
			new_valueIndex[q++] = value[p];
	}
	new_valueIndex[q] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_valueIndex;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_valueIndex);
}

/**
 * print_alias - The alias is printed in the format name='value'.
 * @alias: this Pointer points  to alias.
 */
void print_alias(alias_t *alias)
{
	char *aliasString;
	int length = _strlen(alias->name) + _strlen(alias->value) + 4;

	aliasString = malloc(sizeof(char) * (length + 1));
	if (!aliasString)
		return;
	_strcpy(aliasString, alias->name);
	_strcat(aliasString, "='");
	_strcat(aliasString, alias->value);
	_strcat(aliasString, "'\n");

	write(STDOUT_FILENO, aliasString, length);
	free(aliasString);
}
/**
 * replace_aliases - replace any matching alias with their value
 * @args:All 2D pointer points to arguments.
 * Return:All 2D pointer points to arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int y;
	char *new_valueIndex;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (y = 0; args[y]; y++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[y], temp->name) == 0)
			{
				new_valueIndex = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_valueIndex)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_valueIndex, temp->value);
				free(args[y]);
				args[y] = new_valueIndex;
				y = y - 1;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
