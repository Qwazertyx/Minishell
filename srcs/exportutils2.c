#include "../incl/minishell.h"

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
	char	**split;
	int		i;

	split = ft_splitve(cmd, ' ', "export");
	if (!split)
	{
		ft_putstr_fd("malloc error\n", 2);
		return ;
	}
	i = 0;
	while (split[++i])
	{
		if (!ft_isexportable(split[i]))
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(split[i], 2);
			ft_putstr_fd("\': not a valid indentifier\n", 2);
			g_exit = 1;
			free_split(split);
			return ;
		}
	}
	free_split(split);
	if (cmd)
	{
		new_env = parse_export(cmd, *p->env);
		if (!new_env)
		{
			ft_putstr_fd("malloc error\n", 2);
			return ;
		}
		*p->env = new_env;
	}
	else
		print_export(*p->env);
}

int	ft_strchr(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i] && a[i] != c)
		i++;
	if (a[i] && a[i] == c)
		return (i);
	return (-1);
}
