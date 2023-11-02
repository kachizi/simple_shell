/*
 * File: shell_builtin.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tempers = aliases;
	int iers, reters = 0;
	char *value;

	if (!args[0])
	{
		while (tempers)
		{
			print_alias(tempers);
			tempers = tempers->next;
		}
		return (reters);
	}
	for (iers = 0; args[iers]; iers++)
	{
		tempers = aliases;
		value = _strchr(args[iers], '=');
		if (!value)
		{
			while (tempers)
			{
				if (_strcmp(args[iers], tempers->name) == 0)
				{
					print_alias(tempers);
					break;
				}
				tempers = tempers->next;
			}
			if (!tempers)
				reters = create_error(args + iers, 1);
		}
		else
			set_alias(args[iers], value);
	}
	return (reters);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temper = aliases;
	int len, jer, ker;
	char *new_valer;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_valer = malloc(sizeof(char) * (len + 1));
	if (!new_valer)
		return;
	for (jer = 0, ker = 0; value[jer]; jer++)
	{
		if (value[jer] != '\'' && value[jer] != '"')
			new_valer[ker++] = value[jer];
	}
	new_valer[ker] = '\0';
	while (temper)
	{
		if (_strcmp(var_name, temper->name) == 0)
		{
			free(temper->value);
			temper->value = new_valer;
			break;
		}
		temper = temper->next;
	}
	if (!temper)
		add_alias_end(&aliases, var_name, new_valer);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_stringer;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_stringer = malloc(sizeof(char) * (len + 1));
	if (!alias_stringer)
		return;
	_strcpy(alias_stringer, alias->name);
	_strcat(alias_stringer, "='");
	_strcat(alias_stringer, alias->value);
	_strcat(alias_stringer, "'\n");

	write(STDOUT_FILENO, alias_stringer, len);
	free(alias_stringer);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temper;
	int iers;
	char *new_valer;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (iers = 0; args[iers]; iers++)
	{
		temper = aliases;
		while (temper)
		{
			if (_strcmp(args[iers], temper->name) == 0)
			{
				new_valer = malloc(sizeof(char) * (_strlen(temper->value) + 1));
				if (!new_valer)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_valer, temper->value);
				free(args[iers]);
				args[iers] = new_valer;
				iers--;
				break;
			}
			temper = temper->next;
		}
	}

	return (args);
}
