/*
 * File: shell_errMsgs2.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **args)
{
	char *error_er, *hist_str_er;
	int len;

	hist_str_er = _itoa(hist);
	if (!hist_str_er)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str_er) + _strlen(args[0]) + 24;
	error_er = malloc(sizeof(char) * (len + 1));
	if (!error_er)
	{
		free(hist_str_er);
		return (NULL);
	}

	_strcpy(error_er, name);
	_strcat(error_er, ": ");
	_strcat(error_er, hist_str_er);
	_strcat(error_er, ": ");
	_strcat(error_er, args[0]);
	_strcat(error_er, ": Permission denied\n");

	free(hist_str_er);
	return (error_er);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_127(char **args)
{
	char *error_er, *hist_str_er;
	int len;

	hist_str_er = _itoa(hist);
	if (!hist_str_er)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str_er) + _strlen(args[0]) + 16;
	error_er = malloc(sizeof(char) * (len + 1));
	if (!error_er)
	{
		free(hist_str_er);
		return (NULL);
	}

	_strcpy(error_er, name);
	_strcat(error_er, ": ");
	_strcat(error_er, hist_str_er);
	_strcat(error_er, ": ");
	_strcat(error_er, args[0]);
	_strcat(error_er, ": not found\n");

	free(hist_str_er);
	return (error_er);
}
