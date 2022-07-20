/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchrcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:06:39 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:06:40 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

pid_t	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	if (!a || !b)
		return (0);
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

int	ft_strchrquot(char *s, char c, char c2)
{
	int		i;
	char	quot;

	i = 0;
	quot = 0;
	while (s && s[i])
	{
		if (quot == 0 && (s[i] == '\'' || s[i] == '\"'))
			quot = s[i];
		else if (s[i] == quot)
			quot = 0;
		if (quot == 0 && s[i] == c && (c2 == 0 || (s[i + 1] && s[i + 1] == c2)))
			return (i + 1);
		i++;
	}
	return (-1);
}

int	ft_strchr(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i] && a[i] != c)
		i++;
	if (a[i] && a[i] == c)
		return (i);
	return (-1);
}
