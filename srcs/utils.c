/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:06:46 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:06:47 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_isexportable(char *s)
{
	int	i;

	if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z')
			|| s[0] == '_' || s[0] == '/'))
		return (0);
	i = -1;
	while (s[++i] && s[i] != '=')
		if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] < 'Z') \
		|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			return (0);
	return (1);
}

void	ft_normal_fd(int fd[2])
{
	wait(NULL);
	if (fd[0] > 0)
		dup2(fd[0], 0);
	if (fd[1] > 0)
		dup2(fd[1], 1);
}

char	*ft_strdup(char *a)
{
	int		i;
	char	*s;

	i = 0;
	if (!a)
		return (0);
	while (a[i])
		i++;
	s = malloc(i + 1);
	i = -1;
	while (a[++i])
		s[i] = a[i];
	s[i] = '\0';
	return (s);
}

char	*ft_strndup(char *a, int l)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc(l + 1);
	while (a[i] && i < l)
	{
		s[i] = a[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
