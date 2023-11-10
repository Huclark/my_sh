#include "sh.h"

/**
 * sh_input - Takes in user input and returns it as a string
 * @file_descriptor: File descriptor to read from
 * Return: User input
*/
char *sh_input(int file_descriptor)
{
	unsigned int buflength = READ_BUFFER, position_size = 0;
	int ch;
	char *line_buffer = malloc(sizeof(char) * buflength);

	if (line_buffer == NULL) /* If malloc fails */
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1) /* Infinite loop */
	{
		ch = sh_getchar(file_descriptor); /* Read character */

		/* Handling newline and EOF (Ctrl + D) when reading from stdin */
		if (file_descriptor == STDIN_FILENO && (ch == '\n' || ch == EOF))
		{
			/* Empty command or EOF case */
			if (position_size == 0 || ch == EOF)
			{
				free(line_buffer);
				return (NULL);
			}
			break;
		}
		/* If newline is encountered when reading from a file */
		else if (ch == '\n')
			continue;
		/* EOF when reading from a file*/
		else if (ch == EOF)
			break;
		/* Store character in buffer */
		line_buffer[position_size] = (char)ch;
		position_size++;

		/* Realloc if we hit size threshold */
		if (position_size >= buflength)
			refill_buffer(&position_size, &buflength, &line_buffer);
	}
	line_buffer[position_size] = '\0'; /* Null-terminate string */
	return (line_buffer);
}



/**
 * sh_getchar - Reads a character from stdin
 * @file_descriptor: The file descriptor to read from
 * Return: The character read (tyypecast as an int)
 *         Or EOF on failure or there is no character left
*/
int sh_getchar(int file_descriptor)
{
	char ch;

	if (read(file_descriptor, &ch, 1) == 1)
		return ((int)ch);
	else
		return (EOF);
}


/**
 * refill_buffer - Reallocates memory to a buffer
 * @position_size: Pointer to position_size
 * @buflength: Pointer to buflength
 * @line_buffer: Pointer to buffer
*/
void refill_buffer(unsigned int *position_size, unsigned int *buflength,
					char **line_buffer)
{
	/* Increase buffer size */
	*buflength += READ_BUFFER;

	/* Reallocate memory for buffer */
	*line_buffer = sh_realloc(*line_buffer, *buflength,
								sizeof(char) * *buflength);

	/* Handle memory allocation failure */
	if (*line_buffer == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
}
