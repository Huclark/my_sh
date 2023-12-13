#include "sh.h"

/**
 * main - main function for shell program
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: An array of pointers to Environment Variables
 * Return: The exit code (loop_status)
 */

int main(int argc, char **argv, char **envp)
{
	return (sh_loop(argc, argv, envp));
}
