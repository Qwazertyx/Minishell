/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:27 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:05:28 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*ft_joinc(char *s1, char c)
{
	int		i;
	char	*s;

	i = 0;
	while (s1 && s1[i])
		i++;
	s = malloc(i + 2);
	if (s)
	{
		i = -1;
		while (s1 && s1[++i])
			s[i] = s1[i];
		if (i == -1)
			i = 0;
		s[i] = c;
		s[i + 1] = '\0';
	}
	free(s1);
	return (s);
}

char	*ft_joins(char *a, char *b)
{
	int		i;
	int		j;
	char	*s;

	i = ft_strlen(a);
	j = ft_strlen(b);
	s = malloc(i + j + 1);
	if (s)
	{
		i = -1;
		j = -1;
		while (a && a[++i])
			s[i] = a[i];
		if (i == -1)
			i = 0;
		while (b && b[++j] && b[j] != '\n')
			s[i + j] = b[j];
		if (j != -1)
			s[i + j] = b[j];
		if ((b && b[j] && b[j] == '\n') || j == -1)
			j++;
		s[i + j] = '\0';
	}
	free(a);
	return (s);
}

char	*ft_joinsfree(char *a, char *b)
{
	int		i;
	int		j;
	char	*s;

	s = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	if (s)
	{
		i = -1;
		j = -1;
		while (a && a[++i])
			s[i] = a[i];
		if (i == -1)
			i = 0;
		while (b && b[++j] && b[j] != '\n')
			s[i + j] = b[j];
		if (j != -1)
			s[i + j] = b[j];
		if ((b && b[j] && b[j] == '\n') || j == -1)
			j++;
		s[i + j] = '\0';
	}
	free(a);
	free(b);
	return (s);
}

char	*fill_ft_noquote(char *a, int len)
{
	char	*s;
	char	quot;
	int		i;

	s = malloc(len + 1);
	if (!s)
		return (0);
	len = 0;
	i = 0;
	while (a[i])
	{
		if (quot == 0 && (a[i] == '\'' || a[i] == '\"'))
			quot = a[i++];
		else if (quot != 0 && quot == a[i])
			quot = 0 * i++;
		else
			s[len++] = a[i++];
	}
	s[len] = '\0';
	return (s);
}

char	*ft_noquote(char *a)
{
	char	quot;
	int		i;
	int		len;

	i = 0;
	quot = 0;
	len = 0;
	while (a[i])
	{
		if (quot == 0 && (a[i] == '\'' || a[i] == '\"'))
			quot = a[i++];
		else if (quot != 0 && quot == a[i])
			quot = 0 * i++;
		else
			i = i + 1 + 0 * len++;
	}
	return (fill_ft_noquote(a, len));
}
