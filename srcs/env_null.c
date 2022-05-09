#include "../incl/minishell.h"

char	*ft_joinsfree2(char *a, char *b)
{
	int		i;
	int		j;
	char	*s;

	s = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	if (s)
	{
		i = -1;
		j = -1;
		while (a && a[++i])
			s[i] = a[i];
		if (i == -1)
			i = 0;
		while (b && b[++j] && b[j] != '\n')
			s[i + j] = b[j];
		if (j != -1)
			s[i + j] = b[j];
		if ((b && b[j] && b[j] == '\n') || j == -1)
			j++;
		s[i + j] = '\0';
	}
	free(b);
	return (s);
}

char	**free_bf_i(char **env, int i)
{
	while (--i >= 0)
		free(env[i]);
	free(env);
	return (0);
}

char	**fill_null_env(void)
{
	char	**env;

	env = malloc(5 * sizeof(char *));
	if (!env)
		return (0);
	env[0] = ft_joinsfree2("PWD=", getcwd(NULL, 0));
	if (!env[0])
		return (free_bf_i(env, 0));
	env[1] = ft_strdup("SHLVL=1");
	if (!env[1])
		return (free_bf_i(env, 1));
	env[2] = ft_strdup("_=/usr/bin/env");
	if (!env[2])
		return (free_bf_i(env, 2));
	env[3] = ft_strdup("OLDPWD");
	if (!env[3])
		return (free_bf_i(env, 3));
	env[4] = 0;
	return (env);
}
