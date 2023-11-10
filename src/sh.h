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

/* Custom prototypes for loop */
int sh_loop(int argc, char **argv);
int interactive(char **argv, int file_descriptor);
int non_interactive(char **argv, int file_descriptor);

/* Custom prototypes for reading user input */
char *sh_input(int file_descriptor);
int sh_getchar(int file_descriptor);
void refill_buffer(unsigned int *position_size, unsigned int *buflength,
					char **line_buffer);

/* MACROS */
#define READ_BUFFER		1024

#endif
