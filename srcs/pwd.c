/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:06:10 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:06:11 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_pwd(void)
{
	char	*a;

	a = NULL;
	a = getcwd(a, 1);
	ft_putendl_fd(a, 1);
	free(a);
}
