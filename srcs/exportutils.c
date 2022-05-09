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
		while (cmd[i] && ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && \
		cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '/' || \
		cmd[i] == '_' || cmd[i] == '=' || cmd[i] == '.' || cmd[i] == ':' || \
		quot != 0))
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
	if (!new_tab)
		return (0);
	i = 0;
	while (tab && tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = ft_strdup(to_add);
	if (!new_tab[i])
		return (0);
	new_tab[i + 1] = 0;
	free(tab);
	return (new_tab);
}

void	export_exist(char *mod, char **env)
{
	int		i;
	char	*save;

	if (!contains(mod, '='))
		return ;
	i = 0;
	while (env[i])
	{
		if (ft_startcomparegal(mod, env[i]))
		{
			save = env[i];
			env[i] = ft_strdup(mod);
			if (!env[i])
			{
				ft_putstr_fd("malloc error\n", 2);
				env[i] = save;
				return ;
			}
		}
		i++;
	}
}

char	**parse_export(char *cmd, char **env, int i, char **final)
{
	char	**parsed;
	char	**returned;

	parsed = pre_parsexport(cmd);
	if (!parsed)
		return (0);
	while (parsed[i])
	{
		if (!ft_exist(parsed[i], env))
		{
			final = create_tab_parse(final, parsed[i++]);
			if (!final)
			{
				free_split(parsed);
				return (0);
			}
		}
		else
			export_exist(parsed[i++], env);
	}
	free_split(parsed);
	returned = add_export(final, env, 0);
	free_split(final);
	return (returned);
}
