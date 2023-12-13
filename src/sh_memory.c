#include "sh.h"

/**
* free_str - Ensures that strings pointers are freed properly
* @array: Array to free
*/

void free_str(char **array)
{
	int i = 0;

	if (!array)
		return;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}


/**
* sh_realloc - Replicates realloc function
* @prev_mem_ptr: Pointer to previously allocated memory
* @prev_size: size of previous memory
* @curr_size: size of current memory
* Return: pointer to old memory block
*/

void *sh_realloc(void *prev_mem_ptr, unsigned int prev_size,
						unsigned int curr_size)
{
	char *old_mem;

	if (!prev_mem_ptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(prev_mem_ptr), NULL);
	if (curr_size == prev_size)
		return (prev_mem_ptr);

	old_mem = malloc(curr_size);
	if (!old_mem)
		return (NULL);

	if (prev_size < curr_size)
		prev_size = prev_size;
	else
		prev_size = curr_size;

	while (prev_size--)
		old_mem[prev_size] = ((char *)prev_mem_ptr)[prev_size];
	free(prev_mem_ptr);
	return (old_mem);
}


/**
* free_loop - Frees memory in shell_loop
* @cli_arg1: cli_arg1
* @cli_arg2: cli_arg2
* @cli_arg3: cli_arg3
* @arg_parse1: arg_parse1
* @arg_parse2: arge_parse2
*/
void free_loop(char *cli_arg1, char *cli_arg2, char *cli_arg3,
				char **arg_parse1, char **arg_parse2)
{
	free(cli_arg1);
	free(cli_arg2);
	free(cli_arg3);
	free(arg_parse1);
	free(arg_parse2);
}
