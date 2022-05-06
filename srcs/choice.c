#include "../incl/minishell.h"

int	read_heredoc(t_var *tab, int *status, int nb)
{
	signal(SIGINT, useless_sig);
	signal(SIGQUIT, useless_sig);
	tab->heredocfd = ft_heredoctest(tab, tab->chevreg);
	wait(status);
	if (!(tab->cmd[nb - 1][0][0] == '.' && tab->cmd[nb - 1][0][1] == '/'))
	{
		signal(SIGINT, func_sig);
		signal(SIGQUIT, func_sig);
	}
}

pid_t	ft_vpipe(t_var *tab, int nb)
{
	pid_t	pid;
	int		old;
	int		status;
	int		i;

	old = 0;
	i = 0;
	g_exit = 0;
	read_heredoc(tab, &status, nb);
	if (status == 0)
	{
		if (nb > 1)
		{
			while (i < nb)
				pid = multipipex(tab, nb, &old, i++);
			return (pid);
		}
		else
			return (ft_choice(tab, 0, 1));
	}
	g_exit = WEXITSTATUS(status);
	return (0);
}

pid_t	ft_execve(t_var *tab, int i, pid_t pid, int fd[2])
{
	char	**s;

	if (pid)
		pid = fork();
	if (!pid)
	{
		s = ft_splitve(tab->cmd[i][1], ' ', tab->cmd[i][0]);
		if (!s)
		{
			ft_putstr_fd("Malloc error\n", 2);
			exit(1);
		}
		execmaster(s, *tab->env);
	}
	wait(NULL);
	dup2(fd[0], 0);
	return (pid);
}

void	ft_functions(t_var *tab, int i, pid_t pid, int fd[2])
{
	if (!ft_strcmp(tab->cmd[i][0], "echo"))
		echomaster(tab->cmd[i][1]);
	else if (!ft_strcmp(tab->cmd[i][0], "cd"))
		mycd(tab->cmd[i], *tab->env);
	else if (!ft_strcmp(tab->cmd[i][0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(tab->cmd[i][0], "export"))
		export(tab->cmd[i][1], tab);
	else if (!ft_strcmp(tab->cmd[i][0], "unset"))
		*tab->env = unset(tab->cmd[i], *tab->env);
	else if (!ft_strcmp(tab->cmd[i][0], "env"))
		ft_env(*tab->env);
	else if (!ft_strcmp(tab->cmd[i][0], "exit"))
		ft_exit(tab, i);
	else
		pid = ft_execve(tab, i, pid, fd);
}

int	ft_choice(t_var *tab, int i, pid_t pid)
{
	int	fd[2];

	all_chevre(tab, i, fd);
	if (fd && tab->cmd[i][0])
		ft_functions(tab, i, pid, fd);
	if (!pid)
		exit(0);
	ft_normal_fd(tab, fd, i);
	return (0);
}
