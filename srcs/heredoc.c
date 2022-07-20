/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:05:34 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/20 11:59:38 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*hdocparse(char	*s, char **env)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (s[i])
	{
		if (s[i] == '$')
		{
			str = ft_joinsfree(str, ft_dolar(&s[i + 1], env));
			if (!s)
				return (0);
			i += skip_dolar(&s[i + 1]) + 1;
		}
		else
			str = ft_joinc(str, s[i++]);
	}
	return (str);
}

void	ft_while_doublechevre(int *pipes[2], char ***file, int ij[2], char **e)
{
	char	*read;
	char	*parsed;

	dprintf(2, "==%d %d\n", pipes[1][ij[0]], pipes[0][ij[0]]);
	read = readline("> ");
	parsed = hdocparse(read, e);
	while (ft_strcmp(read, &file[ij[0]][ij[1]][2]))
	{
		if (ij[1] == whoislastdouble(file[ij[0]]))
		{
			dprintf(2, "%d écrit\n", pipes[1][ij[0]]);
			ft_putendl_fd(parsed, pipes[1][ij[0]]);
		}
		free(read);
		free(parsed);
		read = readline("> ");
		parsed = hdocparse(read, e);
	}
	free(read);
	free(parsed);
}

int	ft_doublechevre(int *pipes[2], char ***file, char **env)
{
	int		ij[2];

	ij[0] = -1;
	while (file[++ij[0]])
	{
		ij[1] = -1;
		while (file[ij[0]][++ij[1]])
			if (file[ij[0]][ij[1]][0] == '<')
				ft_while_doublechevre(pipes, file, ij, env);
		close(pipes[0][ij[0]]);
		close(pipes[1][ij[0]]);
	}
	return (0);
}

void	fill_pipes(char ***file, int *pipes[2])
{
	int	i;
	int	pip[2];

	i = 0;
	while (file[i])
		i++;
	pipes[0] = malloc((i + 1) * sizeof(int));
	pipes[1] = malloc((i + 1) * sizeof(int));
	i = -1;
	while (file[++i])
	{
		pipe(pip);
		pipes[0][i] = pip[0];
		pipes[1][i] = pip[1];
	}
	pipes[0][i] = 0;
	pipes[1][i] = 0;
}

int	*ft_heredoctest(char ***file, char **env)
{
	int		i;
	int		*pipes[2];
	pid_t	pid;

	fill_pipes(file, pipes);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, sig_heredoc);
		exit(ft_doublechevre(pipes, file, env));
	}
	else
	{
		i = -1;
		while (file[++i])
			close(pipes[1][i]);
		free(pipes[1]);
		return (pipes[0]);
	}
	return (0);
}
