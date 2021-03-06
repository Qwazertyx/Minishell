/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dolar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:04 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:05 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	stop_while(char c, char *legal)
{
	int	i;

	i = -1;
	while (legal[++i])
		if (legal[i] == c)
			return (1);
	return (0);
}

char	*ft_dolar(char *a, char **env)
{
	int		i;
	char	*s;
	char	*gete;

	i = 0;
	if (a[i] && a[i] == '?')
		return (ft_itoa((int)g_exit));
	while (a[i] && stop_while(a[i], \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		i++;
	s = malloc(i + 1);
	if (!s)
		return (0);
	i = -1;
	while (a[++i] && stop_while(a[i], \
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		s[i] = a[i];
	s[i] = '\0';
	if (i != 0)
		gete = ft_strdup(ft_getenv(s, env));
	else
		gete = ft_strdup("$");
	free(s);
	return (gete);
}

int	skip_dolar(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] && cmd[i] == '?')
		return (1);
	while (cmd[i] && stop_while(cmd[i],
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01233456789_"))
		i++;
	return (i);
}
