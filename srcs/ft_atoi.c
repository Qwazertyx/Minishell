/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:22 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:23 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	p;
	int	c;

	i = 0;
	p = 1;
	c = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			p = p * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		c = c * 10 + (str[i] - 48);
		i++;
	}
	return (c * p);
}

char	*remp(char *tab, int nb, int l, int s)
{
	long int	n;

	n = nb;
	if (n < 0)
		n = n * -1;
	while (l-- > s)
	{
		tab[l] = (n % 10) + '0';
		n = n / 10;
	}
	if (l == 0)
		tab[0] = '-';
	return (tab);
}

char	*ft_itoa(int n)
{
	int				l;
	int				s;
	long int		nb;
	char			*a;

	l = 0;
	s = 0;
	nb = n;
	if (n < 0)
		nb = nb * -1 + s++;
	while (nb > 0)
	{
		nb = nb / 10;
		l++;
	}
	if (n == 0)
		l = 1;
	a = malloc(l + s + 1);
	if (!a)
		return (0);
	a[l + s] = '\0';
	return (remp(a, n, l + s, s));
}
