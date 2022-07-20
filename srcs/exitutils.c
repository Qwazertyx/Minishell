/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:01 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:02 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_strleni(char *a, int i)
{
	int	j;

	j = i;
	while (a[i])
		i++;
	return (i - j);
}

int	ft_strcmpi(char *a, char *b, int i)
{
	int	j;

	j = 0;
	while (a[i] && b[j] && a[i] == b[j])
		i += 1 + 0 * j++;
	return (a[i] - b[j]);
}
