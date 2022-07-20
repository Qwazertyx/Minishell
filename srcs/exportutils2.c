/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:19 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:20 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	secu_export(char *cmd)
{
	int		i;
	char	**split;

	split = ft_splitquote(cmd, ' ');
	if (!split)
	{
		ft_putstr_fd("malloc error\n", 2);
		return (0);
	}
	i = -1;
	while (split[++i])
	{
		if (!ft_isexportable(split[i]))
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(split[i], 2);
			ft_putstr_fd("\': not a valid indentifier\n", 2);
			g_exit = 1;
			free_split(split);
			return (0);
		}
	}
	free_split(split);
	return (1);
}

void	export(char *cmd, t_var *p)
{
	char	**new_env;

	if (!secu_export(cmd))
		return ;
	if (cmd)
	{
		new_env = parse_export(cmd, *p->env, 0, NULL);
		if (!new_env)
			return (ft_putstr_fd("Error, env didn't change\n", 2));
		free(*p->env);
		*p->env = new_env;
	}
	else
		print_export(*p->env);
}

char	*only_noquote(char *a, int i, char *s, char quot)
{
	while (a && a[i])
	{
		if (quot == 0 && (a[i] == '\'' || a[i] == '\"'))
		{
			quot = a[i++];
			while (a[i] && a[i] != quot)
				s = ft_joinc(s, a[i++]);
			if (quot == a[i])
				quot = 0 * i++;
		}
		if (a[i])
		{
			s = ft_joinc(s, a[i]);
			if (!s)
				break ;
		}
		if (a[i])
			i++;
	}
	free(a);
	return (s);
}
