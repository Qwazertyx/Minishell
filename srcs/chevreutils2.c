/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevreutils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:04:34 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/20 11:54:39 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	skip_next_word(char *s, char c)
{
	int		i;
	char	quot;

	i = 1;
	quot = 0;
	if (s[i] == c)
		i++;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i])
	{
		if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
			quot = s[i];
		else if (quot && quot == s[i])
			quot = 0;
		if (!quot && (s[i] == ' ' || s[i] == '|'))
			return (i);
		i++;
	}
	return (i);
}

int	has_a_single(char **chevre)
{
	int	i;

	i = 0;
	while (chevre[i] && chevre[i][0] != ' ')
		i++;
	if (chevre[i] && chevre[i][0] == ' ')
		return (1);
	return (0);
}

int	last_is_double(char **chevre)
{
	int	i;

	i = 0;
	while (chevre[i])
		i++;
	if (i > 0 && chevre[i - 1][0] != ' ')
		return (1);
	return (0);
}

int	all_chevre(t_var *tab, int i, int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
	if (last_is_double(tab->chevreg[i]))
	{
		fd[0] = dup(0);
		dprintf(2, "-%d\n", tab->heredocfd[i]);
		dup2(tab->heredocfd[i], 0);
	}
	else if (has_a_single(tab->chevreg[i]))
	{
		fd[0] = ft_chevreg(tab->chevreg[i], tab, i);
		if (!fd[0])
			return (0);
	}
	if (tab->chevred[i][0])
	{
		fd[1] = ft_chevred(tab->chevred[i]);
		if (!fd[1])
			return (0);
	}
	return (1);
}
