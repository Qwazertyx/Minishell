/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:14 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:15 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	exit_export(t_var *p, int i)
{
	while (p->env[++i])
		free(p->env[i]);
	i = 0;
	while (p->env[i])
		free(p->env[i++]);
	free_struc(p, 0);
	ft_putstr_fd("Error in env\n", 2);
	exit(1);
}
