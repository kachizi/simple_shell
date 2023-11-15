/*
 * File: shell_help2.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - Displays information on the shellby builtin command 'env'.
 */
void help_env(void)
{
	char *msg_er = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg_er, _strlen(msg_er));
}

/**
 * help_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void help_setenv(void)
{
	char *msg_er = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg_er, _strlen(msg_er));
	msg_er = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg_er, _strlen(msg_er));
	msg_er = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg_er, _strlen(msg_er));
}

/**
 * help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *msg_er = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg_er, _strlen(msg_er));
	msg_er = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg_er, _strlen(msg_er));
	msg_er = "message to stderr.\n";
	write(STDOUT_FILENO, msg_er, _strlen(msg_er));
}
