#include "../incl/minishell.h"

int	mycd(char **path)
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
			perror("chdir() failed");
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
			perror("no HOME detected");
	}
	return (0);
}
