#include "sh.h"

ssize_t _getline(int fd, char **line);

/**
 * sh_input - Takes in user input and returns it as a string
 * @fd: File descriptor to read from
 * Return: User input
*/
char *sh_input(int fd)
{
	char *line;
	char *buffer;
	ssize_t bytesRead;
	int len;

	bytesRead = _getline(fd, &line);
	printf("%s\n", line);
	if (bytesRead != -1)
	{
		buffer = stringdup(line);
		if (!buffer)
		{
			if (fd != STDIN_FILENO)
				close(fd);
			perror("Failed to allocate memory");
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
	}
	else if (bytesRead == -1)
		return (NULL);

	while ((bytesRead = _getline(fd, &line)) != -1)
	{
		stringconcat(buffer, line);

		len = stringlength(buffer);
		buffer[len] = '\n';
		buffer[len + 1] = '\0';
		free(line);
	}
	if (stringcompare(buffer, "\n") == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}


/**
 * _getline - Reads characters from a file stream and stores bytes read
 *            in a buffer
 * @fd: File descriptor to read from
 * @line: A pointer to a character array
 * Return: Bytes read or -1 on failure
*/
ssize_t _getline(int fd, char **line)
{
	char *buffer;
	char ch;
	ssize_t br = 0;
	ssize_t buffer_size = READ_BUFFER;

	*line = malloc(buffer_size);
	if (!line)
	{
		perror("Failed to allocate memory");
		if (fd != STDIN_FILENO)
			close(fd);
		exit(EXIT_FAILURE);
	}

	buffer = *line;

	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
		{
			buffer[br] = '\0';
			return (br);
		}
		buffer[br++] = ch;

		if (br >= buffer_size - 1)
		{
			/* Increase buffer size */
			buffer_size += READ_BUFFER;

			/* Re-allocate memory for buffer */
			*line = sh_realloc(*line, buffer_size, sizeof(char) * buffer_size);

			/* Handle memory allocation failure */
			if (!*line)
			{
				perror("Failed to allocate memory");
				if (fd != STDIN_FILENO)
					close(fd);
				exit(EXIT_FAILURE);
			}
			/* Update buffer to point to the next available memory location */
			buffer = *line + br;
		}
	}
	if (br > 0)
	{
		buffer[br] = '\0';
		return (br);
	}
	free(*line);
	*line = NULL;
	return (-1); /* EOF */
}
