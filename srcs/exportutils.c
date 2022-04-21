#include "../incl/minishell.h"

char	**pre_parsexport(char *cmd)
{
	char	quot;
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	quot = 0;
	while (cmd[i])
	{
		while (cmd[i] && ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' \
		&& cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9') \
		|| cmd[i] == '_' || cmd[i] == '=' || quot != 0))
		{
			i++;
			if (quot == 0 && (cmd[i] == '\'' || cmd[i] == '\"'))
				quot = cmd[i];
			else if ((quot != 0 && quot == cmd[i]))
				quot = 0 * i++;
		}
		if (++nb && cmd[i])
			i++;
	}
	return (utils_pre_parsexport(cmd, nb));
}

char	*end_parse(char *a)
{
	char	*s;
	int		i;
	int		nb;

	i = 0;
	while (a[i])
		i++;
	s = malloc(i + 1);
	nb = 0;
	i = 0;
	while (a[i])
	{
		s[i + nb] = a[i];
		if (a[i] == '=' && nb == 0)
			s[i + nb++] = '\"';
		i++;
	}
	s[i + nb] = '\"';
	s[i + ++nb] = '\0';
	return (s);
}

char	**create_tab_parse(char **tab, char *to_add)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = ft_strdup(to_add);
	new_tab[i + 1] = 0;
	free_split(tab);
	return (new_tab);
}

void	export_exist(char *mod, char **env)
{
	int	i;

	if (!contains(mod, '='))
		return ;
	i = 0;
	while (env[i])
	{
		if (ft_startcomparegal(mod, env[i]))
		{
			free(env[i]);
			env[i] = ft_strdup(mod);
		}
		i++;
	}
}

char	**parse_export(char *cmd, char **env)
{
	char	**parsed;
	char	**final;
	char	**returned;
	int		i;

	parsed = pre_parsexport(cmd);
	i = 0;
	final = NULL;
	while (parsed[i])
	{
		if (!ft_exist(parsed[i], env))
			final = create_tab_parse(final, parsed[i++]);
		else
			export_exist(parsed[i++], env);
	}
	free_split(parsed);
	if (!final)
		return (env);
	returned = add_export(final, env, 0);
	return (returned);
}
