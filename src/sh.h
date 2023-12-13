#ifndef SH_H
#define SH_H

/* Standard library headers */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>

/**
 * struct data_hub - Data hub for program
 * @line_no: Number of iterations of shell
 * @loop_status: Handles the shell loop
*/
typedef struct data_hub
{
	int line_no;
	int loop_status;
} data;

/* Global data_hub struct variable */
extern data dh;

/**
 * struct sh_builtins - Handles built-in commands
 * @command: The built-in command
 * @f: A pointer to the function to handle the built-in command
 *
 * Description: Built-in commands and their functions
 * for the shell
 */
typedef struct sh_builtins
{
	char *command;
	int (*f)(char **, char **, char **);
} blt;

/* Custom functions for loop */
int sh_loop(int, char **, char **);
int interactive(char **, int, char **);
int non_interactive(char **, int, char **);
char **parse_line1(char *);
char **parse_line2(char *);
int sh_exec(char **, char **, char **, char **);
int sh_fork(char **, char **, char **);
char *find_command(char **, char **);
char *find_exec_in_path(char *, char *);

/* Custom functions for reading user input */
char *sh_input(int);
ssize_t _getline(int, char **);

/* Custom functions for built-in commands */
int sh_exit(char **, char **, char **);
int sh_cd(char **, char **, char **);
int sh_env(char **, char **, char **);
int sh_setenv(char **, char **, char **);
int sh_unsetenv(char **, char **, char **);

/* Custom functions for handling environment variables */
char *sh_getenv(char *, char **);

/* Custom functions for handling memory */
void free_str(char **);
void *sh_realloc(void *, unsigned int, unsigned int);
void free_loop(char *, char *, char *, char **, char **);

/* Custom functions for printing */
int _putchar(char);
int _eputchar(char);
void _puts(char *);
void _eputs(char *);
int print_numbers(int, int);

/* Custom functions for printing error messages to standard error */
void file_err_msg(char **, char *);
void error_msg(char *, char **, char *);
void exit_error_msg(char *, char **, char *);
void cd_error_msg(char *, char **, char *);

/* Custom functions for strings */
char *stringcopy(char *, char *);
int stringcompare(char *, char *);
int stringlength(char *);
char *stringconcat(char *, char *);
char *stringconcat2(char *, char *);
char *stringdup(const char *);
char *strtok_delims(char *, char *);
char *delim_checker(char *, int);
int sh_getchar(void);
char *itostr(int);
size_t atoi_(char *);
int string_n_cmp(const char *, const char *, int);
char *string_n_copy(char *, char *, int);
char *string_n_concat(char *, char *, int);
char *find_char(char *, char);
int is_digit(int);

/* MACROS */
#define READ_BUFFER		1024
#define TOKEN_BUFFER	1024
#define DELIMITERS		" \n\t\r"

#endif
