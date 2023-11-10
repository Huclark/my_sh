#include "sh.h"

/**
 * sh_loop - Displays a type prompt.
 *           Reads and executes command and parameters from command line.
 *           Displays type prompt again each time a
 *           command has been executed.
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Loop status or EXIT_FAILURE
*/
int sh_loop(int argc, char **argv)
{
	int loop_status;
	int file_descriptor = STDIN_FILENO; /* Set file descriptor to 0*/

	if (argc > 1) /* Assume we are reading from a file if true */
	{
		file_descriptor = open(argv[1], O_RDONLY); /* Open file */

		if (file_descriptor == -1)/* Handle errors */
		{
			if (errno == EACCES)
				perror("File Permission denied");
			else
				perror("File not found");
			return (EXIT_FAILURE);
		}
	}

	/* Check if shell is used in interactive mode or not */
	if (isatty(STDIN_FILENO))
		loop_status = interactive(argv, file_descriptor); /* interactive loop */

	else /* Non-interactive mode */
		loop_status = non_interactive(argv, file_descriptor);

	/* If we are reading from a file close the file */
	if (file_descriptor != 0)
		close(file_descriptor);

	return (loop_status);
}


/**
 * interactive -  Starts the shell in interactive mode
 * @argv: Argument vector
 * @file_descriptor: File descriptor to read from
 * Return: Always exit status (loop_status)
*/
int interactive(char **argv, int file_descriptor)
{
	char **arg_parse1, **arg_parse2, *cli_arg1, *cli_arg2, *cli_arg3;
	int loop_status, line_count = 1;

	do {
		cust_puts(">>> "); /* Shell prompt */
		fflush(stdout); /* To ensure prompt is always printed to stdout first */

		/* Get user input and return as string */
		cli_arg1 = sh_input(file_descriptor);
		cli_arg2 = stringdup(cli_arg1);
		cli_arg3 = stringdup(cli_arg1);

		/* Parse string into array of commands & parameters */
		arg_parse1 = parse_line1(cli_arg1);
		arg_parse2 = parse_line2(cli_arg2);

		/* Handle exit built-in command */
		if (stringcompare(arg_parse1[0], "exit") == 0)
			loop_status = shell_exit(argv, arg_parse1, line_count);

		else /* Handle other commands */
			loop_status = shell_exec(arg_parse1, arg_parse2, argv,
										cli_arg3, line_count);

		/* Free memory allocated */
		free_loop(cli_arg1, cli_arg2, cli_arg3, arg_parse1, arg_parse2);

		line_count++; /* Handle line count */
		} while (loop_status == 1);

		return (loop_status);
}


/**
 * non_interactive -  Starts the shell in non-interactive mode
 * @argv: Argument vector
 * @file_descriptor: File descriptor to read from
 * Return: 0 on success or exit status (loop status)
*/
int non_interactive(char **argv, int file_descriptor)
{
	char **arg_parse1, **arg_parse2, *cli_arg1, *cli_arg2, *cli_arg3;
	int loop_status, line_count = 1;

	/* Get user input and return as string */
	cli_arg1 = sh_input(file_descriptor);
	cli_arg2 = stringdup(cli_arg1);
	cli_arg3 = stringdup(cli_arg1);

	/* Parse string into array of commands & parameters */
	arg_parse1 = parse_line1(cli_arg1);
	arg_parse2 = parse_line2(cli_arg2);

	/* Handle exit built-in command */
	if (stringcompare(arg_parse1[0], "exit") == 0)
	{
		loop_status = shell_exit(argv, arg_parse1, line_count);

		/* Free memory allocated */
		free_loop(&cli_arg1, &cli_arg2, &cli_arg3, &arg_parse1, &arg_parse2);

		return (loop_status);
	}
	else /* Handle other commands */
	{
		shell_exec(arg_parse1, arg_parse2, argv, cli_arg3, line_count);

		/* Free memory allocated */
		free_loop(&cli_arg1, &cli_arg2, &cli_arg3, &arg_parse1, &arg_parse2);

		return (EXIT_SUCCESS);
	}
}
