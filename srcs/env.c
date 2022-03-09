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
	return (nb);
}

static int	*ft_nbcreate(char **env)
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

void	ft_env(char **env, t_var *tab)
{
	int	i;
	int	j;
	int	l;
	int	*nb;

	i = 0;
	while (env[i])
		i++;
	nb = ft_nbcreate(env);
	i = -1;
	l = 0;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
			l++;
		l++;
	}
	tab[0].output = malloc(l);
	i = -1;
	l = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j])
			tab[0].output[++l] = env[i][j];
		tab[0].output[++l] = '\n';
	}
	tab[0].output[l] = '\0';
}
