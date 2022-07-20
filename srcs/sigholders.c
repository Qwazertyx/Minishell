/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigholders.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:06:14 by mlagrang          #+#    #+#             */
/*   Updated: 2022/07/19 13:06:15 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ctrl_c(int sig)
{
	char	*prompt;

	(void)sig;
	prompt = ft_strjoin(rl_prompt, rl_line_buffer);
	prompt = ft_joins(prompt, "  \b\b");
	if (sig == SIGINT)
	{
		ft_putendl_fd(prompt, 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	free(prompt);
	g_exit = 1;
}

void	ctrl_bs(int sig)
{
	char	s;

	(void) sig;
	rl_on_new_line();
	rl_redisplay();
	if (rl_point == ft_strlen(rl_line_buffer))
		write(2, "  \b\b", 4);
	else if (rl_point == ft_strlen(rl_line_buffer) - 1)
	{
		s = rl_line_buffer[rl_point];
		write (2, &s, 1);
		write(2, " \b\b", 3);
	}
}

void	sig_heredoc(int sig)
{
	char	*prompt;

	if (sig == SIGINT)
	{
		prompt = ft_strjoin(rl_prompt, rl_line_buffer);
		prompt = ft_joins(prompt, "  \b\b");
		ft_putendl_fd(prompt, 2);
		free(prompt);
		exit(1);
	}
}

void	func_sig(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3", 2);
	ft_putstr_fd("\n", 2);
	g_exit = 131;
	if (sig == SIGINT)
		g_exit = 130;
}

void	useless_sig(int sig)
{
	(void)sig;
	g_exit = 1;
}
