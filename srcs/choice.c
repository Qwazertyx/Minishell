#include "../incl/minishell.h"

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

void	ft_vpipe(t_var *tab, int nb)
{
	pid_t	pid;
	int		old;
	int		status;
	int		i;

	old = 0;
	i = 0;
	if (nb > 1)
	{
		while (i < nb)
			pid = multipipex(tab, nb, &old, i++);
		waitpid(pid, &status, 0);
		while (wait(NULL) != -1)
			;
	}
	else
	{
		if (!ft_strcmp(tab->cmd[0][0], "exit"))
		{
			dprintf(2, "=enter exit\n\n");
			ft_exit(tab, 0);
		}
		pid = fork();
		if (pid)
			return ;
		return (ft_choice(tab, 0));
	}
}

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

void	ft_choice(t_var *tab, int i)
{
	char	**s;
	int		fd;

	fd = 0;
	dprintf(2, "cmd = %s\\\n", tab->cmd[i][0]);
	if (tab->chevreg[i][0])
	{
		dprintf(2,"get chevreg\n");
		ft_chevreg(tab->chevreg[i], tab);
		dprintf(2, "=%s\n", tab->cmd[i][1]);
	}
	if (tab->chevred[i][0])
	{
		printf("get chevred\n");
		ft_chevred(tab->chevred[i]);
		dprintf(2, "=%s\n", tab->cmd[i][1]);
	}
	if (!ft_strcmp(tab->cmd[i][0], "echo"))
	{
		dprintf(2, "=enter echo\n\n");
		echomaster(tab->cmd[i][1]);
	}
	else if (!ft_strcmp(tab->cmd[i][0], "cd"))
	{
		dprintf(2, "=enter cd\n\n");
		mycd(tab->cmd[i]);
	}
	else if (!ft_strcmp(tab->cmd[i][0], "pwd"))
	{
		dprintf(2, "=enter pwd\n\n");
		ft_pwd();
	}
	else if (!ft_strcmp(tab->cmd[i][0], "export"))
	{
		dprintf(2, "=enter export\n\n");
		export(tab->cmd[i][1], tab);
	}
	else if (!ft_strcmp(tab->cmd[i][0], "unset"))
	{
		dprintf(2, "=enter unset\n\n");
		*tab->env = unset(tab->cmd[i], *tab->env);
	}
	else if (!ft_strcmp(tab->cmd[i][0], "env"))
	{
		dprintf(2, "=enter env\n\n");
		ft_env(*tab->env);
	}
	else if (!ft_strcmp(tab->cmd[i][0], "exit"))
	{
		dprintf(2, "=enter exit\n\n");
		ft_exit(tab, i);
	}
	else if (tab->cmd[i][0] == '\0')
		return ;
	else
	{
		dprintf(2, "=enter execve\n\n");
		s = ft_splitve(tab->cmd[i][1], ' ', tab->cmd[i][0]);
		if (!s)
		{
			ft_putstr_fd("Malloc error\n", 2);
			exit (1);
		}
		int	i = 0;
		while (s[i])
			dprintf(2, "split = %s\n", s[i++]);
		dprintf(2, "\n");
		execmaster(s, *tab->env);
	}
	exit(0);
}
