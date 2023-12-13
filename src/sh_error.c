#include "sh.h"

/**
* file_err_msg - Prints the error message for files to standard error
* @argv: Argument vector
* @msg: Error message
*/
void file_err_msg(char **argv, char *msg)
{
	_eputs(argv[0]);
	_eputs(": ");
	print_numbers(dh.line_no, STDERR_FILENO);
	_eputs(": cannot open ");
	_eputs(argv[1]);
	_eputs(": ");
	_eputs(msg);
}


/**
 * error_msg - Prints the same error output as sh (/bin/sh)
 * @prog_name: Program name
 * @argv_tkn: Null-terminated array of command and parameters
 * @msg: The error message string
*/
void error_msg(char *prog_name, char **argv_tkn, char *msg)
{
	_eputs(prog_name);
	_eputs(": ");
	print_numbers(dh.line_no, STDERR_FILENO);
	_eputs(": ");
	_eputs(argv_tkn[0]);
	_eputs(": ");
	_eputs(msg);
	_eputchar('\n');
}


/**
 * exit_error_msg - Prints the same error output as sh (/bin/sh) for "exit"
 * @prog_name: Program name
 * @argv_tkn: Null-terminated array of command and parameters
 * @msg: The error message string
*/
void exit_error_msg(char *prog_name, char **argv_tkn,
					char *msg)
{
	_eputs(prog_name);
	_eputs(": ");
	print_numbers(dh.line_no, STDERR_FILENO);
	_eputs(": ");
	_eputs(argv_tkn[0]);
	_eputs(": ");
	_eputs(msg);
	_eputs(": ");
	_eputs(argv_tkn[1]);
	_eputchar('\n');
}


/**
 * cd_error_msg - Prints the same error output as sh (/bin/sh) for "exit"
 * @prog_name: Program name
 * @argv_tkn: Null-terminated array of command and parameters
 * @msg: The error message string
*/
void cd_error_msg(char *prog_name, char **argv_tkn, char *msg)
{
	_eputs(prog_name);
	_eputs(": ");
	print_numbers(dh.line_no, STDERR_FILENO);
	_eputs(": ");
	_eputs(argv_tkn[0]);
	_eputs(": ");
	_eputs(msg);
	_eputchar(' ');
	_eputs(argv_tkn[1]);
	_eputchar('\n');
}
