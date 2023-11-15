/*
 * File: shell_environ.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment.
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_environ_er;
	size_t size;
	int index_er;

	for (size = 0; environ[size]; size++)
		;

	new_environ_er = malloc(sizeof(char *) * (size + 1));
	if (!new_environ_er)
		return (NULL);

	for (index_er = 0; environ[index_er]; index_er++)
	{
		new_environ_er[index_er] = malloc(_strlen(environ[index_er]) + 1);

		if (!new_environ_er[index_er])
		{
			for (index_er--; index_er >= 0; index_er--)
				free(new_environ_er[index_er]);
			free(new_environ_er);
			return (NULL);
		}
		_strcpy(new_environ_er[index_er], environ[index_er]);
	}
	new_environ_er[index_er] = NULL;

	return (new_environ_er);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int indexer;

	for (indexer = 0; environ[indexer]; indexer++)
		free(environ[indexer]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int indexer, len_er;

	len_er = _strlen(var);
	for (indexer = 0; environ[indexer]; indexer++)
	{
		if (_strncmp(var, environ[indexer], len_er) == 0)
			return (&environ[indexer]);
	}

	return (NULL);
}
