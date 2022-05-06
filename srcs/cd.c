#include "../incl/minishell.h"

void	mycd(char **path, char **env)
{
	int	i;

	if (path[1])
	{
		i = 0;
		while (path[1][i + 1])
			i++;
		if (path[1][i] && path[1][i] == ' ')
			path[1][i] = 0;
		if (chdir(path[1]) != 0)
		{
			perror("Minishell: cd: ");
			g_exit = 1;
		}
	}
	else
	{
		if (chdir(ft_getenv("HOME", env)) != 0)
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			g_exit = 1;
		}
	}
}
