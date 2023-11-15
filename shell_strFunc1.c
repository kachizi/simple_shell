/*
 * File: shell_strFunc1.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length_om of the character string.
 */
int _strlen(const char *s)
{
	int length_er = 0;

	if (!s)
		return (length_er);
	for (length_er = 0; s[length_er]; length_er++)
		;
	return (length_er);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t iers;

	for (iers = 0; src[iers] != '\0'; iers++)
		dest[iers] = src[iers];
	dest[iers] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemper;
	const char *srcTemper;

	destTemper = dest;
	srcTemper =  src;

	while (*destTemper != '\0')
		destTemper++;

	while (*srcTemper != '\0')
		*destTemper++ = *srcTemper++;
	*destTemper = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len_er = _strlen(dest);
	size_t iers;

	for (iers = 0; iers < n && src[iers] != '\0'; iers++)
		dest[dest_len_er + iers] = src[iers];
	dest[dest_len_er + iers] = '\0';

	return (dest);
}
