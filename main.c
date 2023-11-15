/*
 * File: main.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

void sig_handler(int sig);
int execute(char **args, char **front);

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args, char **front)
{
	pid_t child_pid_er;
	int status, flag_er = 0, ret = 0;
	char *command_er = args[0];

	if (command_er[0] != '/' && command_er[0] != '.')
	{
		flag_er = 1;
		command_er = get_location(command_er);
	}

	if (!command_er || (access(command_er, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_error(args, 126));
		else
			ret = (create_error(args, 127));
	}
	else
	{
		child_pid_er = fork();
		if (child_pid_er == -1)
		{
			if (flag_er)
				free(command_er);
			perror("Error child:");
			return (1);
		}
		if (child_pid_er == 0)
		{
			execve(command_er, args, environ);
			if (errno == EACCES)
				ret = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag_er)
		free(command_er);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn_er;
	int *exe_ret_er = &retn_er;
	char *prompt_er = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret_er = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exe_ret_er);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret_er);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(exe_ret_er);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret_er);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt_er, 2);
		ret = handle_args(exe_ret_er);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret_er);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret_er);
}
