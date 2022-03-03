#include "../incl/minishell.h"

void	ft_env(char **env)
{
	int	i;
	int	j;
	int	*nb;

	i = 0;
	while (env[i])
		i++;
	nb = malloc(sizeof(int) * i + 1);
	i = 0;
	while (env[i])
	{
		nb[i] = 0;
		j = -1;
		while (env[++j])
			if (ft_strcmp(env[i], env[j]) >= 0)
				nb[i]++;
		i++;
	}
	nb[i] = 0;
	i = 0;
	j = 1;
	while (nb[i])
	{
		if (nb[i] == j)
		{
			printf("%s\n", env[i]);
			i = 0 * j++;
		}
		else
			i++;
	}
}
