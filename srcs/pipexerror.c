#include "../incl/minishell.h"

void	terminate(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	errorcmd(char *cmd)
{
	printf("Minishell: %s: command not found\n", cmd);
	// write(2, "Error: command not found\n", 25);
	exit(EXIT_FAILURE);
}

void	free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i++]);
	}
	free(args);
}
