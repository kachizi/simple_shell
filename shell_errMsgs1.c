/*
 * File: shell_errMsgs1.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */


#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **args)
{
	char *error, *hist_str_er;
	int len_er;

	hist_str_er = _itoa(hist);
	if (!hist_str_er)
		return (NULL);

	args--;
	len_er = _strlen(name) + _strlen(hist_str_er) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len_er + 1));
	if (!error)
	{
		free(hist_str_er);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str_er);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str_er);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_1(char **args)
{
	char *error;
	int len_er;

	len_er = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len_er + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **args)
{
	char *errorer, *hist_str_er;
	int len_er;

	hist_str_er = _itoa(hist);
	if (!hist_str_er)
		return (NULL);

	len_er = _strlen(name) + _strlen(hist_str_er) + _strlen(args[0]) + 27;
	errorer = malloc(sizeof(char) * (len_er + 1));
	if (!errorer)
	{
		free(hist_str_er);
		return (NULL);
	}

	_strcpy(errorer, name);
	_strcat(errorer, ": ");
	_strcat(errorer, hist_str_er);
	_strcat(errorer, ": exit: Illegal number: ");
	_strcat(errorer, args[0]);
	_strcat(errorer, "\n");

	free(hist_str_er);
	return (errorer);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 * Return: The error string.
 */
char *error_2_cd(char **args)
{
	char *errorer, *hist_str_er;
	int len_er;

	hist_str_er = _itoa(hist);
	if (!hist_str_er)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len_er = _strlen(name) + _strlen(hist_str_er) + _strlen(args[0]) + 24;
	errorer = malloc(sizeof(char) * (len_er + 1));
	if (!errorer)
	{
		free(hist_str_er);
		return (NULL);
	}

	_strcpy(errorer, name);
	_strcat(errorer, ": ");
	_strcat(errorer, hist_str_er);
	if (args[0][0] == '-')
		_strcat(errorer, ": cd: Illegal option ");
	else
		_strcat(errorer, ": cd: can't cd to ");
	_strcat(errorer, args[0]);
	_strcat(errorer, "\n");

	free(hist_str_er);
	return (errorer);
}

/**
 * error_2_syntax - Creates an error message for syntax erroroms.
 * @args: An array of arguments passed to the command.
 * Return: The errorom string.
 */
char *error_2_syntax(char **args)
{
	char *errorer, *hist_str_er;
	int len_er;

	hist_str_er = _itoa(hist);
	if (!hist_str_er)
		return (NULL);

	len_er = _strlen(name) + _strlen(hist_str_er) + _strlen(args[0]) + 33;
	errorer = malloc(sizeof(char) * (len_er + 1));
	if (!errorer)
	{
		free(hist_str_er);
		return (NULL);
	}

	_strcpy(errorer, name);
	_strcat(errorer, ": ");
	_strcat(errorer, hist_str_er);
	_strcat(errorer, ": Syntax errorer: \"");
	_strcat(errorer, args[0]);
	_strcat(errorer, "\" unexpected\n");

	free(hist_str_er);
	return (errorer);
}
