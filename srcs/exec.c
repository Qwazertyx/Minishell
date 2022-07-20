/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:04:54 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:04:55 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	execmaster(char **maincmd, char **env)
{
	if (!maincmd[0] || !maincmd[0][0])
		return (0);
	path(maincmd[0], env);
	if (env[0] && path(maincmd[0], env))
	{
		if (execve(path(maincmd[0], env), maincmd, env) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			perror(maincmd[0]);
			exit(126);
		}
	}
	else
		errorcmd(maincmd[0]);
	exit(0);
}
