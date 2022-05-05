#include "../incl/minishell.h"

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

void	free_cmd(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd && cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j++]);
		}
		free(cmd[i++]);
	}
	free(cmd);
}

void	ft_close(t_var *p)
{
	int	i;

	i = 0;
	while (p->cmd[++i])
		if (p->heredocfd[i])
			close(p->heredocfd[i++]);
	free(p->heredocfd);
}

void	free_struc(t_var *p, int i)
{
	ft_close(p);
	free_cmd(p->cmd);
	free_cmd(p->chevred);
	free_cmd(p->chevreg);
	if (i == 1)
		free_cmd(p->env);
}

void	ft_while(t_var *parsed)
{
	char	*a;
	char	*tmp;
	int		nb;

	nb = 0;
	tmp = ft_prompt();
	// tmp = ft_strjoin2("🎃 ", tmp);
	a = readline(tmp);
	free(tmp);
	if (!a)
	{
		ft_putstr_fd("\b\bexit\n", 2);
		exit(0);
	}
	if (a[0])
	{
		add_history(a);
		if (is_input(a))
		{
			parsed = parse(a, parsed);
			if (!parsed)
			{
				// ft_putstr_fd("parse error\n", 2);
				return ;
			}
			while (parsed->cmd[nb])
				nb++;
			ft_vpipe(parsed, nb);
			wait (NULL);
			free_struc(parsed, 0);
		}
	}
	else
		free(a);
}

void	CtrlC(int sig)
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
	else
	{
		rl_redisplay();
				rl_on_new_line();
	}
	free(prompt);
}

void	CtrlB(int sig)
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
}

void	useless_sig(int sig)
{
	(void)sig;
}

int	main(int argc, char *argv[], char **envp)
{
	int		i;
	char	**env;
	t_var	struc;

	i = 0;
	while (envp[i])
		i++;
	env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		if (ft_startcompare("SHLVL", envp[i]))
			env[i] = ft_joinc(ft_strdup("SHLVL="),
					ft_atoi(ft_getenv("SHLVL", envp)) + 49);
		else
			env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = 0;
	struc.env = &env;
	(void) argc;
	(void) argv;
	while (1)
	{
		signal(SIGINT, CtrlC);
		signal(SIGQUIT, CtrlB);
		ft_while(&struc);
	}
}
