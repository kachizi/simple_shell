/*
 * File: shell_helper.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t iers;

	for (iers = 0; args[iers] || args[iers + 1]; iers++)
		free(args[iers]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t iers = 0;
	char *buffer;
	ssize_t fileer;

	fileer = open("/proc/self/stat", O_RDONLY);
	if (fileer == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(fileer);
		return (NULL);
	}
	read(fileer, buffer, 120);
	while (buffer[iers] != ' ')
		iers++;
	buffer[iers] = '\0';

	close(fileer);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addrer;
	char *replacementer = NULL, *temp_er, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addrer = _getenv(var);
	free(var);
	if (var_addrer)
	{
		temp_er = *var_addrer;
		while (*temp_er != '=')
			temp_er++;
		temp_er++;
		replacementer = malloc(_strlen(temp_er) + 1);
		if (replacementer)
			_strcpy(replacementer, temp_er);
	}

	return (replacementer);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int jer, ker = 0, len;
	char *replacementer = NULL, *old_line_er = NULL, *new_line_er;

	old_line_er = *line;
	for (jer = 0; old_line_er[jer]; jer++)
	{
		if (old_line_er[jer] == '$' && old_line_er[jer + 1] &&
				old_line_er[jer + 1] != ' ')
		{
			if (old_line_er[jer + 1] == '$')
			{
				replacementer = get_pid();
				ker = jer + 2;
			}
			else if (old_line_er[jer + 1] == '?')
			{
				replacementer = _itoa(*exe_ret);
				ker = jer + 2;
			}
			else if (old_line_er[jer + 1])
			{
				/* extract the variable name to search for */
				for (ker = jer + 1; old_line_er[ker] &&
						old_line_er[ker] != '$' &&
						old_line_er[ker] != ' '; ker++)
					;
				len = ker - (jer + 1);
				replacementer = get_env_value(&old_line_er[jer + 1], len);
			}
			new_line_er = malloc(jer + _strlen(replacementer)
					  + _strlen(&old_line_er[ker]) + 1);
			if (!line)
				return;
			new_line_er[0] = '\0';
			_strncat(new_line_er, old_line_er, jer);
			if (replacementer)
			{
				_strcat(new_line_er, replacementer);
				free(replacementer);
				replacementer = NULL;
			}
			_strcat(new_line_er, &old_line_er[ker]);
			free(old_line_er);
			*line = new_line_er;
			old_line_er = new_line_er;
			jer = -1;
		}
	}
}
