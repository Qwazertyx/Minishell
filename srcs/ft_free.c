/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:24 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:25 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_free_i(t_var *p, char *a, int i, int j)
{
	while (j >= 0)
		free(p->cmd[i + 1][j--]);
	free(p->cmd[i + 1]);
	while (i >= 0)
	{
		j = 1;
		while (j >= 0)
			free(p->cmd[i][j--]);
		free(p->cmd[i--]);
	}
	free(p->cmd);
	free_cmd(p->chevred);
	free_cmd(p->chevreg);
	free(a);
	ft_putstr_fd("parse error\n", 2);
	return (0);
}

t_var	*free_returned(t_var *p, char *a)
{
	free(a);
	free_cmd(p->chevred);
	free_cmd(p->chevreg);
	return (NULL);
}

void	free_cmd(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd && cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j++]);
		}
		free(cmd[i++]);
	}
	free(cmd);
}

void	free_struc(t_var *p, int i)
{
	ft_close(p);
	free_cmd(p->cmd);
	free_cmd(p->chevred);
	free_cmd(p->chevreg);
	if (i == 1)
		free_cmd(p->env);
}

void	ft_close(t_var *p)
{
	int	i;

	i = 0;
	while (p->cmd[++i])
		if (p->heredocfd[i])
			close(p->heredocfd[i]);
	free(p->heredocfd);
}
