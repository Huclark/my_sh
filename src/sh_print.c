#include "sh.h"

/**
 * _putchar - Prints a character to standard output
 * @ch: The character to print
 * Return: 1 on success and -1 on failure
 */
int _putchar(char ch)
{
	return (write(STDOUT_FILENO, &ch, 1));
}


/**
 * _eputchar - Prints a char character to standard error
 * @ch: The character to print
 * Return: 1 on success and -1 on failure
 */
int _eputchar(char ch)
{
	return (write(STDERR_FILENO, &ch, 1));
}


/**
 * _puts - Prints a string to standard output
 * @string: string input to print
 */
void _puts(char *string)
{
	int idx = 0;

	if (!string)
		return;
	while (string[idx] != '\0')
	{
		_putchar(string[idx]);
		idx++;
	}
}


/**
 * _eputs - Prints a string to standard error
 * @string: string input to print
 */
void _eputs(char *string)
{
	int idx = 0;

	if (string == NULL)
		return;
	while (string[idx] != '\0')
	{
		_eputchar(string[idx]);
		idx++;
	}
}


/**
 * print_numbers - Prints a decimal (integer) number (base 10) to a file stream
 * @num_to_print: the number to print
 * @fd: file stream
 * Return: number of characters printed
 */
int print_numbers(int num_to_print, int fd)
{
	int idx, __counter = 0;
	unsigned int absolute, curr_num;
	int (*putchar_ptr)(char) = _putchar;

	if (fd == STDERR_FILENO)
		putchar_ptr = _eputchar;

	if (num_to_print < 0)
	{
		absolute = -num_to_print;
		putchar_ptr('-');
		__counter++;
	}
	else
		absolute = num_to_print;
	curr_num = absolute;
	for (idx = 1000000000; idx > 1; idx /= 10)
	{
		if (absolute / idx)
		{
			putchar_ptr('0' + curr_num / idx);
			__counter++;
		}
		curr_num %= idx;
	}
	putchar_ptr('0' + curr_num);
	__counter++;

	return (__counter);
}
