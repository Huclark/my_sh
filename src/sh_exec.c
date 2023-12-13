#include "sh.h"

/**
 * sh_exec - Executes the parsed command
 * @argv_tkn1: Null-terminated array without ':'
 * @argv_tkn2: NUll_terminated array which handles ':'
 * @argv: Argument vector
 * @envp: Environment variables
 * Return: Always 1
*/
int sh_exec(char **argv_tkn1, char **argv_tkn2, char **argv, char **envp)
{
	int idx = 0, status;
	char **tkn;

	blt builtins[] = {
		{"cd", sh_cd},
		{"exit", sh_exit},
		{"env", sh_env},
		{"setenv", sh_setenv},
		{"unsetenv", sh_unsetenv},
		{NULL, NULL}
	};

	while (builtins[idx].command)
	{
		if (stringcompare(argv_tkn1[0], builtins[idx].command) == 0)
			return (builtins[idx].f(argv, argv_tkn1, envp));
		idx++;
	}

	if (argv_tkn2)
	{
		while (*argv_tkn2)
		{
			tkn = parse_line1(*argv_tkn2);
			status = sh_fork(tkn, argv, envp);
			free(tkn);
			argv_tkn2++;
		}
	}

	else if (argv_tkn1)
		status = sh_fork(argv_tkn1, argv, envp);
	return (status);
}


/**
 * sh_fork - Forks a child process and waits for it to execute
 *            a command and terminate
 * @argv_tkn: Null-terminated list of commands and parameters
 * @argv: Argument vector
 * @envp: Environment variables
 * Return: 1 on success, 0 if otherwise
*/
int sh_fork(char **argv_tkn, char **argv, char **envp)
{
	pid_t child_process;
	int ret_status;
	char *fullpath = find_command(argv_tkn, envp);

	if (fullpath == NULL)
	{
		error_msg(argv[0], argv_tkn, "not found");
		return (127);
	}

	child_process = fork();

	if (child_process == -1)
		perror("Fork failed");
	if (child_process == 0)
	{
		if (execve(fullpath, argv_tkn, envp) == -1)
		{
			if (errno == EACCES)
				file_err_msg(argv, "Permission denied\n");
			return (126);
		}
	}
	else
	{
		do {
			waitpid(child_process, &ret_status, WUNTRACED);
		} while (!WIFEXITED(ret_status) && !WIFSIGNALED(ret_status));
	}
	free(fullpath);
	return (0);
}


/**
* find_command - Searches PATH to find the full path to the executable command
* @argv_tkn: Array of nulll-terminated tokens
* @envp: Environment variables
* Return: The full path to command or Null if command is not found
*/
char *find_command(char **argv_tkn, char **envp)
{
	char *cmd_dir, *cmd_path, *path_cpy, *path = sh_getenv("PATH", envp);

	if (find_char(argv_tkn[0], '/') != NULL)
	{
		cmd_path = stringdup(argv_tkn[0]);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	else
	{
		cmd_path = malloc(stringlength(argv_tkn[0]) + 3);
		if (cmd_path == NULL)
			return (NULL);
		stringcopy(cmd_path, "./");
		stringconcat(cmd_path, argv_tkn[0]);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		if (path == NULL)
			return (NULL);
		path_cpy = stringdup(path);
		if (path_cpy == NULL)
			return (NULL);
		cmd_dir = strtok_delims(path_cpy, ":");
		while (cmd_dir != NULL)
		{
			cmd_path = find_exec_in_path(cmd_dir, argv_tkn[0]);
			if (cmd_path != NULL)
			{
				free(path_cpy);
				return (cmd_path);
			}
			cmd_dir = strtok_delims(NULL, ":");
		}
		free(path_cpy);
	}
	return (NULL);
}


/**
 * find_exec_in_path - Finds an executable in path
 * @dir: The directory to search
 * @command: The command to find
 * Return: The full path to the command if found or NULL if otherwise
*/
char *find_exec_in_path(char *dir, char *command)
{
	char *cmd_path = malloc(stringlength(dir) + stringlength(command) + 2);

	if (cmd_path == NULL)
		return (NULL);

	stringcopy(cmd_path, dir);
	stringconcat(cmd_path, "/");
	stringconcat(cmd_path, command);

	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);

	free(cmd_path);
	return (NULL);
}
