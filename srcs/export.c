/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:09 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:10 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**env_cpy(char **env, char **cmd)
{
	int		i;
	int		nb;
	char	**new_env;

	nb = 0;
	i = 0;
	while (cmd && cmd[i])
		if (!ft_exist(cmd[i++], env))
			nb++;
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + nb + 1));
	if (!new_env)
		return (0);
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i] = NULL;
	return (new_env);
}

char	**add_export(char **cmd, char **env, int i)
{
	char	**new_env;
	int		nb;

	i = 0;
	while (env[i])
		i++;
	new_env = env_cpy(env, cmd);
	if (!new_env)
		return (0);
	nb = 0;
	while (cmd && cmd[nb])
	{
		while (cmd[nb] && ft_exist(cmd[nb], env))
			nb++;
		if (cmd[nb])
		{
			new_env[i] = ft_strdup(cmd[nb]);
			if (!new_env[i])
				return (0);
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
		while ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && \
		cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '_' \
		|| cmd[i] == '=' || cmd[i] == '.' || cmd[i] == '/' || cmd[i] == ':' \
		|| quot != 0)
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

char	**free_pre_parse(char **pre, int i)
{
	while (--i >= 0)
		free(pre[i]);
	free(pre);
	return (0);
}

char	**utils_pre_parsexport(char *cmd, int nb)
{
	char	**pre;
	int		i;

	pre = malloc(sizeof(char *) * (nb + 1));
	if (!pre)
		return (0);
	i = -1;
	while (++i < nb)
	{
		pre[i] = fill_export(cmd, i, 0);
		if (!pre[i])
			return (free_pre_parse(pre, i));
		pre[i] = only_noquote(pre[i], 0, 0, 0);
		if (!pre[i])
			return (free_pre_parse(pre, i));
	}
	pre[i] = NULL;
	return (pre);
}
