#include "../incl/minishell.h"

void	terminate(void)
{
	write(2, "Error\n", 6);
}

void	errorcmd(void)
{
	write(2, "Error: command not found\n", 25);
}

void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}
