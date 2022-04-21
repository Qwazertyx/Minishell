#include "../incl/minishell.h"

char	*only_noquote(char *a)
{
	int		i;
	char	*s;
	char	quot;

	i = 0;
	quot = 0;
	s = NULL;
	while (a && a[i])
	{
		if (quot == 0 && (a[i] == '\'' || a[i] == '\"'))
			quot = a[i++];
		else if (quot != 0 && quot == a[i])
			quot = 0 * i++;
		if (a[i])
			s = ft_joinc(s, a[i]);
		if (a[i])
			i++;
	}
	free(a);
	return (s);
}

char	**env_cpy(char **env, int nb)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + nb + 1));
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}

char	**add_export(char **cmd, char **env, int i)
{
	char	**new_env;
	int		nb;

	nb = 0;
	while (cmd[i])
		if (!ft_exist(cmd[i++], env))
			nb++;
	i = 0;
	while (env[i])
		i++;
	new_env = env_cpy(env, nb);
	nb = 0;
	while (cmd[nb])
	{
		while (cmd[nb] && ft_exist(cmd[nb], env))
			nb++;
		if (cmd[nb])
		{
			new_env[i] = ft_strdup(cmd[nb]);
			i = i + 1 + 0 * nb++;
		}
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*fill_export(char *cmd, int nb, int i)
{
	char	quot;
	int		j;

	quot = 0;
	while (cmd[i])
	{
		j = i;
		while ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A'
				&& cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9')
			|| cmd[i] == '_' || cmd[i] == '=' || quot != 0)
		{
			i++;
			if (quot == 0 && (cmd[i] == '\'' || cmd[i] == '\"'))
				quot = cmd[i];
			else if ((quot != 0 && quot == cmd[i]))
				quot = 0 * i++;
		}
		if (!nb)
			return (ft_strndup(&cmd[j], i - j));
		if (i != j)
			nb--;
		i++;
	}
	return (NULL);
}

char	**utils_pre_parsexport(char *cmd, int nb)
{
	char	**pre;
	int		i;

	pre = malloc(sizeof(char *) * (nb + 1));
	i = -1;
	while (++i < nb)
	{
		pre[i] = fill_export(cmd, i, 0);
		pre[i] = only_noquote(pre[i]);
	}
	pre[i] = NULL;
	return (pre);
}
