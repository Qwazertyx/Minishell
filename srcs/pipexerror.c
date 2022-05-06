#include "../incl/minishell.h"

void	terminate(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	errorcmd(char *cmd)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
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
