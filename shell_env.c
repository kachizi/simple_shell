/*
 * File: shell_env.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int index_er;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index_om = 0; environ[index_er]; index_er++)
	{
		write(STDOUT_FILENO, environ[index_er], _strlen(environ[index_er]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var_er = NULL, **new_environment, *new_val_er;
	size_t size;
	int index_er;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_val_er = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val_er)
		return (create_error(args, -1));
	_strcpy(new_val_er, args[0]);
	_strcat(new_val_er, "=");
	_strcat(new_val_er, args[1]);

	env_var_er = _getenv(args[0]);
	if (env_var_er)
	{
		free(*env_var_er);
		*env_var_er = new_val_er;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environment = malloc(sizeof(char *) * (size + 2));
	if (!new_environment)
	{
		free(new_val_er);
		return (create_error(args, -1));
	}

	for (index_er = 0; environ[index_er]; index_er++)
		new_environment[index_er] = environ[index_er];

	free(environ);
	environ = new_environment;
	environ[index_er] = new_val_er;
	environ[index_er + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var_er, **new_environment;
	size_t size;
	int index_er, index_er2;

	if (!args[0])
		return (create_error(args, -1));
	env_var_er = _getenv(args[0]);
	if (!env_var_er)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environment = malloc(sizeof(char *) * size);
	if (!new_environment)
		return (create_error(args, -1));

	for (index_er = 0, index_er2 = 0; environ[index_er]; index_er++)
	{
		if (*env_var_er == environ[index_er])
		{
			free(*env_var_er);
			continue;
		}
		new_environment[index_er2] = environ[index_er];
		index_er2++;
	}
	free(environ);
	environ = new_environment;
	environ[size - 1] = NULL;

	return (0);
}
