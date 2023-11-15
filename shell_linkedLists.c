/*
 * File: shell_linkedLists.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node_er = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node_om)
		return (NULL);

	new_node_er->next = NULL;
	new_node_er->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node_er->name)
	{
		free(new_node_er);
		return (NULL);
	}
	new_node_er->value = value;
	_strcpy(new_node_er->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node_er;
	}
	else
		*head = new_node_er;

	return (new_node_er);
}

/**
 * add_node_end - Adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node_er = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node_er)
		return (NULL);

	new_node_er->dir = dir;
	new_node_er->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node_er;
	}
	else
		*head = new_node_er;

	return (new_node_er);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void free_alias_list(alias_t *head)
{
	alias_t *next_er;

	while (head)
	{
		next_er = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next_er;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void free_list(list_t *head)
{
	list_t *next_er;

	while (head)
	{
		next_er = head->next;
		free(head->dir);
		free(head);
		head = next_er;
	}
}
