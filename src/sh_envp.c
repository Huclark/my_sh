#include "sh.h"

/**
* sh_getenv - Retrieves the value of an environ variable by looping
*                through the environ array.
* @var_name: Environment variable prefix
* @envp: Environment variables
* Return: The environment variable's value
*/
char *sh_getenv(char *var_name, char **envp)
{
	int idx = 0;

	if (!var_name || !envp)
		return (NULL);

	while (envp[idx] != NULL)
	{
		if (string_n_cmp(envp[idx], var_name, stringlength(var_name)) == 0
			&& envp[idx][stringlength(var_name)] == '=')
			return (envp[idx] + stringlength(var_name) + 1);
		idx++;
	}
	return (NULL);
}
