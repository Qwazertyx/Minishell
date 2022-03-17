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

char	**add_export(char **cmd, char **env)
{
	int		i;
	char	**new_env;
	int		nb;

	nb = 0;
	i = 0;
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

char	*fill_export(char *cmd, int nb)
{
	char	quot;
	int		i;
	int		j;

	i = 0;
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

char	**pre_parsexport(char *cmd)
{
	char	**pre;
	char	quot;
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	quot = 0;
	while (cmd[i])
	{
		while (cmd[i] && ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A'
					&& cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9')
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
	pre = malloc(sizeof(char *) * (nb + 1));
	i = -1;
	while (++i < nb)
	{
		pre[i] = fill_export(cmd, i);
		pre[i] = only_noquote(pre[i]);
	}
	pre[i] = NULL;
	return (pre);
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
	free(tab);
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
	returned = add_export(final, env);
	return (returned);
}

void	print_export(char **env)
{
	int	i;
	int	j;
	int	*nb;
	int	q;

	nb = ft_nbcreate(env);
	i = 0;
	while (env[i])
	{
		j = 0;
		q = 0;
		write(1, "declare -x ", 11);
		while (env[nb[i]][j])
		{
			write(1, &env[nb[i]][j], 1);
			if (env[nb[i]][j] == '=' && q++ == 0)
				write(1, "\"", 1);
			j++;
		}
		if (q != 0)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
	free(nb);
}

int	only_onechar(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i])
		if (a[i++] != c)
			return (0);
	return (1);
}

void	export(char *cmd, t_var *p)
{
	char	**new_env;

	if (cmd)
	{
		new_env = parse_export(cmd, *p->env);
		*p->env = new_env;
	}
	else
		print_export(*p->env);
}
