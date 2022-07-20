/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:06:03 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 16:22:45 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	c;

	c = 0;
	if (s)
	{
		while (s[c])
			c++;
		write(fd, s, c);
	}
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	contains(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i])
		if (a[i++] == c)
			return (1);
	return (0);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	c;

	c = 0;
	if (s)
	{
		while (s[c])
			c++;
		write(fd, s, c);
		write(fd, "\n", 1);
	}
}
