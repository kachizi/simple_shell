/*
 * File: shell_helper2.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *old_line_er, *new_line_er;
	char previous_er, current_er, next;
	size_t i, jer;
	ssize_t new_len_er;

	new_len_er = get_new_len(*line);
	if (new_len_er == read - 1)
		return;
	new_line_er = malloc(new_len_er + 1);
	if (!new_line_er)
		return;
	jer = 0;
	old_line_er = *line;
	for (i = 0; old_line_er[i]; i++)
	{
		current_er = old_line_er[i];
		next = old_line_er[i + 1];
		if (i != 0)
		{
			previous_er = old_line_er[i - 1];
			if (current_er == ';')
			{
				if (next == ';' && previous_er != ' ' && previous_er != ';')
				{
					new_line_er[jer++] = ' ';
					new_line_er[jer++] = ';';
					continue;
				}
				else if (previous_er == ';' && next != ' ')
				{
					new_line_er[jer++] = ';';
					new_line_er[jer++] = ' ';
					continue;
				}
				if (previous_er != ' ')
					new_line_er[jer++] = ' ';
				new_line_er[jer++] = ';';
				if (next != ' ')
					new_line_er[jer++] = ' ';
				continue;
			}
			else if (current_er == '&')
			{
				if (next == '&' && previous_er != ' ')
					new_line_er[jer++] = ' ';
				else if (previous_er == '&' && next != ' ')
				{
					new_line_er[jer++] = '&';
					new_line_er[jer++] = ' ';
					continue;
				}
			}
			else if (current_er == '|')
			{
				if (next == '|' && previous_er != ' ')
					new_line_er[jer++]  = ' ';
				else if (previous_er == '|' && next != ' ')
				{
					new_line_er[jer++] = '|';
					new_line_er[jer++] = ' ';
					continue;
				}
			}
		}
		else if (current_er == ';')
		{
			if (i != 0 && old_line_er[i - 1] != ' ')
				new_line_er[jer++] = ' ';
			new_line_er[jer++] = ';';
			if (next != ' ' && next != ';')
				new_line_er[jer++] = ' ';
			continue;
		}
		new_line_er[jer++] = old_line_er[i];
	}
	new_line_er[jer] = '\0';

	free(*line);
	*line = new_line_er;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_len_er = 0;
	char current_er, next_er;

	for (i = 0; line[i]; i++)
	{
		current_er = line[i];
		next_er = line[i + 1];
		if (current_er == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current_er == ';')
			{
				if (next_er == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len_er += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next_er != ' ')
				{
					new_len_er += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len_er++;
				if (next_er != ' ')
					new_len_er++;
			}
			else
				logical_ops(&line[i], &new_len_er);
		}
		else if (current_er == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len_er++;
			if (next_er != ' ' && next_er != ';')
				new_len_er++;
		}
		new_len_er++;
	}
	return (new_len_er);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous_er, current_er, next_er;

	previous_er = *(line - 1);
	current_er = *line;
	next_er = *(line + 1);

	if (current_er == '&')
	{
		if (next_er == '&' && previous_er != ' ')
			(*new_len)++;
		else if (previous_er == '&' && next_er != ' ')
			(*new_len)++;
	}
	else if (current_er == '|')
	{
		if (next_er == '|' && previous_er != ' ')
			(*new_len)++;
		else if (previous_er == '|' && next_er != ' ')
			(*new_len)++;
	}
}
