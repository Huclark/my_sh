#include "sh.h"

/**
 * main - main function for shell program
 * @argc: Argument count
 * @argv: Argument vector
 * Return: The exit code (loop_status)
 */

int main(int argc, char **argv)
{
	return (sh_loop(argc, argv));
}
