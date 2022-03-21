#include "../incl/minishell.h"

char	**delete_tab(char **cmd, char **env)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	i = 0;
	len = 0;
	while (env[i])
	{
		j = 0;
		while (cmd[j] && !ft_startcompare(cmd[j], env[i]))
			j++;
		if (cmd[j] && ft_startcompare(cmd[j], env[i]))
			i++;
		else
			len += 1 + 0 * i++;
	}
	new_env = malloc(sizeof(char **) * (len + 1));
	i = 0;
	len = 0;
	while (env[i])
	{
		j = 0;
		while (cmd[j] && !ft_startcompare(cmd[j], env[i]))
			j++;
		if (cmd[j] && ft_startcompare(cmd[j], env[i]))
			i++;
		else
			new_env[len++] = env[i++];
	}
	new_env[len] = 0;
	return (new_env);
}

char	**unset(char **cmd, char **env)
{
	char	**split;
	char	**returned;
	int		i;

	split = ft_splitve(cmd[1], ' ', cmd[0]);
	i = 0;
	while (split[++i])
	{
		if (!ft_isexportable(split[i]))
		{
			ft_putstr_fd("Minishell: unset: `", 2);
			ft_putstr_fd(split[i], 2);
			ft_putstr_fd("\': not a valid indentifier\n", 2);
			free_split(split);
			return (env);
		}
	}
	returned = delete_tab(split, env);
	free_split(split);
	return (returned);
}