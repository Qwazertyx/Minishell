/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:42 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:43 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	callerror(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	ft_fatherpipex(int *fd, int nb, int *old, int i)
{
	if (*old != 0)
		close (*old);
	if (i < (nb - 1))
		*old = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
}

pid_t	multipipex(t_var *tab, int nb, int *old, int i)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid < 0)
	{
		perror("Minishell: fork");
		g_exit = 1;
		return (pid);
	}
	if (!pid)
	{
		dup2(*old, STDIN_FILENO);
		if (*old)
			close (*old);
		if (i < nb - 1)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		ft_choice(tab, i, pid);
	}
	else
		ft_fatherpipex(fd, nb, old, i);
	return (pid);
}
