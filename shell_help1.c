/*
 * File: shell_help1.c
 * Auth: lUCY OUMA
 *       PESSY KAPERE
 */

#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - Displays all possible builtin shellby commands.
 */
void help_all(void)
{
	char *msger = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msger, _strlen(msger));
}

/**
 * help_alias - Displays information on the shellby builtin command 'alias'.
 */
void help_alias(void)
{
	char *msger = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msger, _strlen(msger));
}

/**
 * help_cd - Displays information on the shellby builtin command 'cd'.
 */
void help_cd(void)
{
	char *msger = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "after a change of directory.\n";
	write(STDOUT_FILENO, msger, _strlen(msger));
}

/**
 * help_exit - Displays information on the shellby builtin command 'exit'.
 */
void help_exit(void)
{
	char *msger = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = " exit 0.\n";
	write(STDOUT_FILENO, msger, _strlen(msger));
}

/**
 * help_help - Displays information on the shellby builtin command 'help'.
 */
void help_help(void)
{
	char *msger = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msger, _strlen(msger));
	msger = "builtin command.\n";
	write(STDOUT_FILENO, msger, _strlen(msger));
}
