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

/* Custom prototypes for loop */
int sh_loop(char **argv);


#endif
