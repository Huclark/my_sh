#include "sh.h"

char **parse_line1(char *cli_arg);

data dh;

/**
 * sh_loop - Displays a type prompt.
 *           Reads and executes command and parameters from command line.
 *           Displays type prompt again each time a
 *           command has been executed.
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Array of pointers to Environment Variables
 * Return: Loop status or exit status code
 */
int sh_loop(int argc, char **argv, char **envp)
{
	int status;
	int fd = STDIN_FILENO; /* Set file descriptor to 0 */

	dh.line_no = 0;

	if (argc > 1) /* Assume we are reading from a file if true */
	{
		fd = open(argv[1], O_RDONLY); /* Open file */

		if (fd == -1) /* Handle errors */
		{
			if (errno == EACCES)
				file_err_msg(argv, "Permission denied\n");
			else
				file_err_msg(argv, "No such file\n");
			exit(2);
		}
	}

	/* Check if shell is used in interactive mode or not */
	if (isatty(STDIN_FILENO))
		status = interactive(argv, fd, envp); /* interactive loop */

	else /* Non-interactive mode */
		status = non_interactive(argv, fd, envp);

	/* If we are reading from a file close the file */
	if (fd != STDIN_FILENO)
		close(fd);

	return (status);
}


/**
 * interactive -  Starts the shell in interactive mode
 * @argv: Argument vector
 * @fd: File descriptor to read from
 * @envp: An array of pointers to Environment variables
 * Return: Always exit status (loop_status)
*/
int interactive(char **argv, int fd, char **envp)
{
	char **arg_parse1, **arg_parse2, *cli_arg1, *cli_arg2, *cli_arg3;
	int status;

	dh.line_no = 1;
	dh.loop_status = 1;

	do {
		_puts(">>> "); /* Shell prompt */
		fflush(stdout); /* To ensure prompt is always printed to stdout first */

		/* Get user input and return as string */
		while ((cli_arg1 = sh_input(fd)) != NULL)
		{
			cli_arg2 = stringdup(cli_arg1);
			cli_arg3 = stringdup(cli_arg1);

			/* Parse string into array of commands & parameters */
			arg_parse1 = parse_line1(cli_arg1);
			arg_parse2 = parse_line2(cli_arg2);

			/* Execute commands */
			status = sh_exec(arg_parse1, arg_parse2, argv, envp);

			/* Free memory allocated */
			free_loop(cli_arg1, cli_arg2, cli_arg3, arg_parse1, arg_parse2);
		}
		dh.line_no++; /* Handle line count */
	} while (dh.loop_status);

	return (status);
}


/**
 * non_interactive -  Starts the shell in interactive mode
 * @argv: Argument vector
 * @fd: File descriptor to read from
 * @envp: An array of pointers to Environment variables
 * Return: Always exit status (loop_status)
*/
int non_interactive(char **argv, int fd, char **envp)
{
	char **arg_parse1, **arg_parse2, *cli_arg1, *cli_arg2, *cli_arg3;
	int status;

	dh.line_no = 1;

	/* Get user input and return as string */
	cli_arg1 = sh_input(fd);
	cli_arg2 = stringdup(cli_arg1);
	cli_arg3 = stringdup(cli_arg1);

	/* Parse string into an array of commands & parameters */
	arg_parse1 = parse_line1(cli_arg1);
	arg_parse2 = parse_line2(cli_arg2);

	/* Execute commands */
	status = sh_exec(arg_parse1, arg_parse2, argv, envp);

	/* Free memory allocated */
	free_loop(cli_arg1, cli_arg2, cli_arg3, arg_parse1, arg_parse2);
	return (status);
}


/**
 * parse_line1 - Separates the command string into
 *              commands and parameters
 * @cli_arg: Command string from stdin
 * Return: A null-terminated array of token strings.
*/
char **parse_line1(char *cli_arg)
{
	char **tkn_buf, **tkn_cpy, *tkn_str;
	unsigned int buflength = TOKEN_BUFFER, ptn_size = 0;

	if (find_char(cli_arg, ';') != NULL)
		return (NULL);

	tkn_buf = malloc(sizeof(char *) * buflength);
	if (!tkn_buf)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}

	tkn_str = strtok_delims(cli_arg, DELIMITERS);

	while (tkn_str)
	{
		tkn_buf[ptn_size] = tkn_str;
		ptn_size++;

		if (ptn_size >= buflength)
		{
			buflength += TOKEN_BUFFER;
			tkn_cpy = tkn_buf;
			tkn_buf = sh_realloc(tkn_buf, buflength, sizeof(char *) * buflength);

			if (!tkn_buf)
			{
				free(tkn_cpy);
				perror("Failed to re-allocate memory");
				return (NULL);
			}
		}
		tkn_str = strtok_delims(NULL, DELIMITERS);
	}
	tkn_buf[ptn_size] = NULL;
	return (tkn_buf);
}


/**
 * parse_line2 - Separates the command string into
 *              commands and parameters
 * @cli_arg: Command string from stdin
 * Return: A null-terminated array of token strings.
*/
char **parse_line2(char *cli_arg)
{
	char **tkn_buf, **tkn_cpy, *tkn_str;
	unsigned int buflength = TOKEN_BUFFER, ptn_size = 0;

	if (find_char(cli_arg, ';') == NULL)
		return (NULL);

	tkn_buf = malloc(sizeof(char *) * buflength);

	if (!tkn_buf)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	tkn_str = strtok_delims(cli_arg, ";");

	while (tkn_str)
	{
		tkn_buf[ptn_size] = tkn_str;
		ptn_size++;

		if (ptn_size >= buflength)
		{
			buflength += TOKEN_BUFFER;
			tkn_cpy = tkn_buf;
			tkn_buf = sh_realloc(tkn_buf, buflength, sizeof(char *) * buflength);

			if (!tkn_buf)
			{
				free(tkn_cpy);
				perror("Failed to re-allocate memory");
				return (NULL);
			}
		}
		tkn_str = strtok_delims(NULL, ";");
	}
	tkn_buf[ptn_size] = NULL;

	return (tkn_buf);
}
