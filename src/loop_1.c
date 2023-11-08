#include "sh.h"

/**
 * sh_loop - Displays a type prompt.
 *           Reads and executes command and parameters from command line.
 *           Displays type prompt again each time a
 *           command has been executed.
 * @argc: Argument count
 * @argv: Argument vector
 * Return: Loop status
*/
int sh_loop(int argc, char **argv)
{
	if (isatty(STDIN_FILENO))
	{
		return (interactive(argv));
	}
	else
	{
		return (non_interactive(argc, argv));
	}
}
