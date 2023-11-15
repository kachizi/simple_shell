/*
 * File: shell_procFile.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error_er, *hist_str_er;
	int len_er;

	hist_str_er = _itoa(hist);
	if (!hist_str_er)
		return (127);

	len_er = _strlen(name) + _strlen(hist_str_er) + _strlen(file_path) + 16;
	error_er = malloc(sizeof(char) * (len_er + 1));
	if (!error_er)
	{
		free(hist_str_er);
		return (127);
	}

	_strcpy(error_er, name);
	_strcat(error_er, ": ");
	_strcat(error_er, hist_str_er);
	_strcat(error_er, ": Can't open ");
	_strcat(error_er, file_path);
	_strcat(error_er, "\n");

	free(hist_str_er);
	write(STDERR_FILENO, error_er, len_er);
	free(error_er);
	return (127);
}

/**
 * proc_file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file_er, om_read, i;
	unsigned int line_size_er = 0;
	unsigned int old_size_er = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file_er = open(file_path, O_RDONLY);
	if (file_er == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size_er);
	if (!line)
		return (-1);
	do {
		om_read = read(file_er, buffer, 119);
		if (om_read == 0 && line_size_er == 0)
			return (*exe_ret);
		buffer[om_read] = '\0';
		line_size_er += om_read;
		line = _realloc(line, old_size_er, line_size_er);
		_strcat(line, buffer);
		old_size_er = line_size_er;
	} while (om_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size_er; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size_er && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size_er);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}
