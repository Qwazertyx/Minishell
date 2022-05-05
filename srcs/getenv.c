#include "../incl/minishell.h"

int	ft_startcomparegal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=')
	{
		if (!s2[i] || s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_startcompare(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1[i])
		return (0);
	while (s1[i])
	{
		if (!s2[i] || s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_getenv(char	*var, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] && !ft_startcompare(var, env[i]))
		i++;
	if (!env[i])
		return (NULL);
	j = 0;
	if (ft_strchr(env[i], '=') == -1)
		return (NULL);
	while (env[i][j] && env[i][j] != '=')
		j++;
	return (&env[i][j + 1]);
}

int	ft_existcompare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=')
	{
		if (!s2[i] || s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_exist(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_existcompare(var, env[i]))
		i++;
	if (!env[i])
		return (0);
	return (1);
}
