/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:06:49 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:06:50 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_verifchevred(t_var *p)
{
	int		i;
	int		j;

	i = -1;
	while (p->chevred[++i])
	{
		j = -1;
		while (p->chevred[i][++j])
		{
			if (!p->chevred[i][j][2])
				return (0);
		}
	}
	return (1);
}

int	ft_verifchevreg(t_var *p)
{
	int		i;
	int		j;

	i = -1;
	while (p->chevreg[++i])
	{
		j = -1;
		while (p->chevreg[i][++j])
		{
			if (!p->chevreg[i][j][2])
				return (0);
		}
	}
	return (1);
}

int	ft_verifchevre(t_var *p)
{
	if (!ft_verifchevred(p) || !ft_verifchevreg(p))
	{
		ft_putstr_fd("Minishell: syntax error\n", 2);
		return (0);
	}
	return (1);
}

int	is_input(char *s)
{
	int		i;
	char	quot;

	i = 0;
	quot = 0;
	while (s[i])
	{
		if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
			quot = s[i];
		else if (quot == s[i])
			quot = 0;
		i++;
	}
	if (quot != 0)
	{
		ft_putstr_fd("Missing ", 2);
		write(2, &quot, 1);
		ft_putstr_fd(" quote\n", 2);
		free(s);
		return (0);
	}
	return (1);
}

int	nb_doublt(char *a)
{
	int		i;
	int		nb;
	char	quot;

	nb = 0;
	i = -1;
	quot = 0;
	while (a[++i])
	{
		if ((a[i] == '\'' || a[i] == '\"') && quot == 0)
			quot = a[i];
		else if ((a[i] == '\'' || a[i] == '\"') && quot != 0)
			quot = 0;
		if (a[i] == '|' && quot == 0)
			nb++;
	}
	return (nb + 1);
}
