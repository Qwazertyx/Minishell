#include "../incl/minishell.h"

static	int	ft_strcmtri(char **env, int i)
{
	int	nb;
	int	j;

	nb = 0;
	j = -1;
	while (env[++j])
		if (ft_strcmp(env[i], env[j]) >= 0)
			nb++;
	return (nb - 1);
}

int	*ft_nbcreate(char **env)
{
	int	*nb;
	int	i;

	i = 0;
	while (env[i])
		i++;
	nb = malloc(sizeof(int) * (i + 1));
	i = 0;
	while (env[i])
	{
		nb[ft_strcmtri(env, i)] = i;
		i++;
	}
	return (nb);
}

void	ft_env(char **env)
{
	int	i;
	int	*nb;

	nb = ft_nbcreate(env);
	i = -1;
	while (env[++i])
		if (contains(env[nb[i]], '='))
			printf("%s\n", env[nb[i]]);
	free(nb);
}
