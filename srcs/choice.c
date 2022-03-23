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
	// s_chevred(tab[0].cmd[1], env);
	if (nb > 1)
	{
		printf("sheeeeeeesh\n");
		multipipex(tab, nb);
	}
	else
	{
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
	if (tab->chevred[0])
	{
		tab->fd = ft_chevred(tab->chevred);
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
		// exportmaster(tab->cmd[i][1], *tab->env);
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
		dprintf(2, "s = (%s)\n", tab->cmd[i][1]);
		s = ft_splitve(tab->cmd[i][1], ' ', tab->cmd[i][0]);
		int	i = 0;
		while (s[i])
			dprintf(2, "%s\n", s[i++]);
		execmaster(s, *tab->env);
	}
	exit(0);
}
