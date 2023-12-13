#include "sh.h"

/**
* sh_exit - Handles the exit built-in command
* @argv: Argument vector
* @argv_tkn: Null-terminated list of commands and parameters
* @envp:  A pointer to the environment variables
* Return: 0 if there is no argument to "exit"
*         2 if argument is invalid
*         Exit status if a valid argument is passed to "exit"
*/
int sh_exit(char **argv, char **argv_tkn, char **envp)
{
	char *num_string;

	(void)envp;
	dh.loop_status = 0;

	if (argv_tkn[1])
	{
		num_string = argv_tkn[1];

		while (*num_string != '\0')
		{
			if (is_digit(*num_string) == 0)
			{
				exit_error_msg(argv[0], argv_tkn, "Illegal number");
				return (2);
			}
			num_string++;
		}
		return (atoi_(argv_tkn[1]));
	}
	else
		return (EXIT_SUCCESS);
}


/**
* sh_cd - Handles the cd built-in command
* @argv: Argument vector
* @argv_tkn: Null-terminated list of commands and parameters
* @envp: Environment variables
* Return: 0 on success, 2 if otherwise
*/
int sh_cd(char **argv, char **argv_tkn, char **envp)
{
	char *home = NULL, *prev_dir = NULL;
	char cwd_p[READ_BUFFER], cwd_c[READ_BUFFER], cwd_prevdir[READ_BUFFER];

	if (cwd_p == NULL || cwd_c == NULL)
		return (1);

	getcwd(cwd_p, sizeof(cwd_p));
	if (argv_tkn[1] == NULL || stringcompare(argv_tkn[1], "~") == 0)
	{
		home = getenv("HOME");
		chdir(home);
	}
	else if (stringcompare(argv_tkn[1], "-") == 0)
	{
		prev_dir = sh_getenv("OLDPWD", envp);
		chdir(prev_dir);
		getcwd(cwd_prevdir, sizeof(cwd_prevdir));
		_puts(cwd_prevdir);
		_putchar('\n');
	}
	else
	{
		if (chdir(argv_tkn[1]) != 0)
		{
			cd_error_msg(argv[0], argv_tkn, "can't cd to");
			return (2);
		}
	}
	setenv("OLDPWD", cwd_p, 1);
	getcwd(cwd_c, sizeof(cwd_c));
	setenv("PWD", cwd_c, 1);

	return (EXIT_SUCCESS);
}


/**
 * sh_env - Handles the "env" built-in command
 * @argv: Argument vector
 * @argv_tkn: Null-terminated list of commands and parameters
 * @envp: Environment variables
 * Return: 0 on success, 2 if otherwise
*/
int sh_env(char **argv, char **argv_tkn, char **envp)
{
	ssize_t idx = 0;

	(void)argv_tkn;
	(void)argv;

	while (envp[idx])
	{
		_puts(envp[idx]);
		_putchar('\n');
		idx++;
	}

	return (EXIT_SUCCESS);
}


/**
 * sh_setenv - setenv built-in command which adds or modifies
 *             an environment variable
 * @argv: Argument vector
 * @argv_tkn: Null-terminated list of commands and parameters
 * @envp: Environment variables
 * Return: 0 on success, 2 if otherwise
*/
int sh_setenv(char **argv, char **argv_tkn, char **envp)
{
	(void)envp;

	if (argv_tkn[1] == NULL || argv_tkn[2] == NULL)
	{
		error_msg(argv[0], argv_tkn, "Usage: setenv VARIABLE VALUE");
		return (2);
	}

	if (setenv(argv_tkn[1], argv_tkn[2], 1) != 0)
	{
		perror("Failed to set environment variable");
		return (2);
	}
	return (0);
}


/**
 * sh_unsetenv - unsetenv built-in command which removes
 *                     an environment variable
 * @argv: Argument vector
 * @argv_tkn: Null-terminated list of commands and parameters
 * @envp: Environment variables
 * Return: 0 on success, 2 if otherwise
*/
int sh_unsetenv(char **argv, char **argv_tkn, char **envp)
{
	(void)envp;

	if (argv_tkn[1] == NULL)
	{
		error_msg(argv[0], argv_tkn, "Usage: unsetenv VARIABLE");
		return (2);
	}

	if (unsetenv(argv_tkn[1]) != 0)
	{
		perror("Failed to set environment variable");
		return (2);
	}
	return (0);
}
